/**
 *	@file	porucase_bmp.c
 *	@brief	ポルトケースBMPウィンドウ制御
 *	@author Miyuki Iwasawa
 *	@date	06.03.15
 */

#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/buflen.h"
#include "system/window.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/window.h"
#include "system/poruto_name.h"
#include "system/pmfprint.h"
#include "application/app_tool.h"
#include "application/poru_tool.h"
#include "savedata/poruto_util.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_poruto_select.h"
#include "porusys.h"
#include "poru_act.h"
#include "porucase_bmp.h"

#define LV_OFS_X	(8)
#define PORULIST_MAX	(6)

static void PoruListCB_ForLine(BMPLIST_WORK* work,u32 param,u8 y);
static void PoruListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode );
static void MenuListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode );

static const BMPLIST_HEADER PoruListHeader = {
	NULL,					//表示文字データポインタ
	PoruListCB_ForMove,PoruListCB_ForLine,	//コールバック(カーソル移動ごと/一行ごと)
	NULL,					//GF_BGL_BMPWIN構造体データへのポインタ
	0,PORULIST_MAX,					//リスト項目数,表示最大項目数
	0,8,0,					//表示X座標(ラベル/項目/カーソル)
	0,						//表示Ｙ座標
	FBMP_COL_BLACK,FBMP_COL_NULL,FBMP_COL_BLK_SDW,		//文字色,背景色,影色
	0,0,				//文字間隔X,Y
//	BMPLIST_NO_SKIP,	//ページスキップタイプ
	BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
	FONT_SYSTEM,		//文字指定
	1,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	NULL,				//ワークポインタ
};
static const BMPLIST_HEADER MenuListHeader = {
	NULL,					//表示文字データポインタ
	MenuListCB_ForMove,NULL,	//コールバック(カーソル移動ごと/一行ごと)
	NULL,					//GF_BGL_BMPWIN構造体データへのポインタ
	0,3,					//リスト項目数,表示最大項目数
	0,8,0,					//表示X座標(ラベル/項目/カーソル)
	0,						//表示Ｙ座標
	FBMP_COL_BLACK,FBMP_COL_WHITE,FBMP_COL_BLK_SDW,		//文字色,背景色,影色
	0,0,				//文字間隔X,Y
	BMPLIST_NO_SKIP,	//ページスキップタイプ
	FONT_SYSTEM,		//文字指定
	0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	NULL,				//ワークポインタ
};

/**
 *	@brief	ポルトリストワーククリア
 */
static void porulist_linkClear(PORU_LIST* pl)
{
	pl->view = 0;
	pl->next = pl->prev = 0xFF;
}

/**
 * @brief	ポルトメッセージ描画
 */
static void poru_msgWrite(PORU_CASE_WORK* wk,STRBUF* msg,u8 spd,u8 win_f)
{
	GF_PRINTCOLOR col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE);

	//ウィンドウ描画
	if(win_f){
		BmpTalkWinWrite( &wk->win[WIN_MSG], WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL);
	}
	GF_BGL_BmpWinFill( &(wk->win[WIN_MSG]),WINCLR_COL(FBMP_COL_WHITE),
		0, 0,BMPL_MSG_SX*8,BMPL_MSG_SY*8);

	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	MsgPrintAutoFlagSet( MSG_SKIP_OFF );
	
	//メッセージ描画
	wk->msgIdx = GF_STR_PrintColor(
		&wk->win[WIN_MSG], FONT_TALK, msg,
		0, 0, spd, col, NULL );
}

/**
 *	@brief	ポルトリストのモード別要素数
 */
static u16 PoruList_GetListNum(PORUTO_PARAM* pp,PORU_CASE_WORK* wk)
{
	u16 i,count = 0;
	u8 mode,flag;
	PORU_LIST* pl;

	wk->startID = wk->endID = 0xFF;

	if(wk->viewMode == 5){
		mode = 0x1F;
	}else{
		mode = 1;
		for(i = 0;i < wk->viewMode;i++){
			mode <<= 1;
		}
	}
	
	for(i = 0;i < pp->porunum;i++){
		pl = &pp->list[i];
		porulist_linkClear(pl);
		if((!pl->valid) || pl->del){
			continue;
		}
		flag = (pl->flags & 0x1F);
		if((flag & mode) == 0){
			continue;
		}
		pl->view = 1;	//viewフラグOn

		//リストを繋ぐ
		if(wk->startID == 0xFF){
//			wk->startID = wk->endID = pl->myid;
			wk->startID = pl->myid;
		}else{
			pp->list[wk->endID].next = pl->myid;
		}
		pl->prev = wk->endID; 
		wk->endID = pl->myid;
		++count;
	}
	//循環リストを閉じる
//	pp->list[wk->endID].next = wk->startID;
//	pp->list[wk->startID].prev = wk->endID;
	
	//「やめる」項目分は必ず確保
	count += 1;
	
	return count;
}

/**
 *	@brief	ポルトリストメニュー作成
 */
void PoruList_CreatePMenu(PORU_CASE_WORK* wk)
{
	u8 i = 0,next = 0;
	PORU_LIST* pl;
	
	wk->viewNum =  PoruList_GetListNum(wk->param,wk);
	
	//BMPリスト領域作成
	wk->plist = BMP_MENULIST_Create(wk->viewNum,wk->heapID);

//	for(i = wk->startID;i != 0xFF;i = next){
	for(i = wk->endID;i != 0xFF;i = next){
		pl = &(wk->param->list[i]);
		next = pl->prev;//pl->next;
		
		WORDSET_RegisterWord(wk->msgDat.wset,0,
				PorutoName_GetNameAdrByMan(wk->nameMan,pl->flavor),
				PM_MALE,FALSE,PM_LANG);
		WORDSET_RegisterNumber(wk->msgDat.wset,1,pl->level,2,
				NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.listbuf);
		BMP_MENULIST_AddString(wk->plist,wk->msgDat.tmp,pl->myid);

	//	BMP_MENULIST_AddString(wk->plist,
	//		PorutoName_GetNameAdrByMan(wk->nameMan,pl->flavor),pl->myid);
	}

	//「やめる」をリストに追加
	BMP_MENULIST_AddString(wk->plist,wk->msgDat.endbuf,0xFF);

	//BMPリストを初期化
	MI_CpuCopy8(&PoruListHeader,&wk->plist_h,sizeof(BMPLIST_HEADER));

	wk->curPos = wk->param->curPos;		//前回の位置を復帰
	wk->listPos = wk->param->listPos;

	//リスト数がひとつ減っていればカーソル位置をマイナス補正
	if(wk->param->ret_mode){
		if(wk->listPos == 0){
			if(wk->curPos != 0 && wk->curPos >= (wk->viewNum-1)){
				--wk->curPos;
			}
		}else{
			if(wk->listPos+PORULIST_MAX >= wk->viewNum){
				--wk->listPos;
			}
		}
		wk->param->ret_mode = 0;
	}
	wk->plist_h.win = &(wk->win[WIN_PLIST]);
	wk->plist_h.list = wk->plist;
	wk->plist_h.work = (void*)wk;
	wk->plist_h.count = wk->viewNum;

	//リスト追加
	wk->plist_cb_f = 0;
	wk->plist_wk = BmpListSet(&wk->plist_h,wk->listPos,wk->curPos,wk->heapID);
	wk->plist_cb_f = 1;
	//LV表示ウィンドウOn
//	GF_BGL_BmpWinOn(&wk->win[WIN_PLISTLV]);
}

/**
 *	@brief	ポルトリスト　メニューリスト削除
 */
void PoruList_DeletePMenu(PORU_CASE_WORK* wk,BOOL trans)
{
	//ウィンドウ領域初期化
	GF_BGL_BmpWinFill( &(wk->win[WIN_PLIST]),WINCLR_COL(FBMP_COL_NULL),
			0, 0,BMPL_PLIST_SX*8,BMPL_PLIST_SY*8);
//	GF_BGL_BmpWinFill( &(wk->win[WIN_PLISTLV]),WINCLR_COL(FBMP_COL_NULL),
//			0, 0,BMPL_PLISTLV_SX*8,BMPL_PLISTLV_SY*8);

	if(trans){
		GF_BGL_BmpWinOff(&wk->win[WIN_PLIST]);
//		GF_BGL_BmpWinOff(&wk->win[WIN_PLISTLV]);
	}

	//リスト解放
	BmpListExit(wk->plist_wk,&(wk->listPos),&(wk->curPos));
	BMP_MENULIST_Delete(wk->plist);

	//カーソル位置保存
	wk->param->listPos = wk->listPos;
	wk->param->curPos = wk->curPos;

	wk->plist_wk = NULL;
	wk->plist = NULL;
}

/**
 *	@brief	ポルトボタンプッシュ時処理
 */
void PoruBtn_StateSet(PORU_CASE_WORK* wk,u8 idx,u8 state)
{
	switch(state){
	case BACT_ST_NULL:
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN);
		CLACT_SetAnmFlag(wk->pActBtn[idx],FALSE);
		GF_BGL_BmpWinShift(
				&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_D,
				2, WINCLR_COL(FBMP_COL_NULL) );
		break;
	case BACT_ST_01:
		CLACT_AnmReStart( wk->pActBtn[idx]);
		CLACT_SetAnmFlag(wk->pActBtn[idx],TRUE);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_U,
			4, WINCLR_COL(FBMP_COL_NULL) );
		
		wk->tp_f = BACT_ST_01;
		break;
	case BACT_ST_02:
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN+BACT_ST_01);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_D,
			2, WINCLR_COL(FBMP_COL_NULL) );

		wk->tp_f = BACT_ST_NULL;
		break;
	case BACT_ST_03:
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN+BACT_ST_02);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_U,
			2, WINCLR_COL(FBMP_COL_NULL) );

		wk->tp_f = BACT_ST_01;
		break;
	case BACT_ST_INI_PUSH:
		//ケース初期化時に押した状態にするコマンド
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN+BACT_ST_01);
		CLACT_SetAnmFlag(wk->pActBtn[idx],TRUE);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_U,
			2, WINCLR_COL(FBMP_COL_NULL) );

		wk->tp_f = BACT_ST_NULL;
		break;
	}
	GF_BGL_BmpWinOn(&wk->win[WIN_SW01+idx]);
}

/**
 *	@brief	ポルトリストソート
 */
void PoruList_SortMenu(PORU_CASE_WORK* wk,u8 mode)
{
	int siz;
	GF_PRINTCOLOR col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);

	//SE
	Snd_SePlay(PORUC_SE_BTN);
	
	//ボタンフォント&アニメ処理
	if(wk->tp_f != BACT_ST_INI){
		//現在のモードチェック
		if(mode == wk->viewMode){
			PoruBtn_StateSet(wk,mode,BACT_ST_03);
			return;
		}
		PoruBtn_StateSet(wk,wk->viewMode,BACT_ST_NULL);
	}
	PoruBtn_StateSet(wk,mode,BACT_ST_01);
	wk->viewMode = mode;
	PoruList_DeletePMenu(wk,FALSE);

	//カーソル位置リセット
	wk->listPos = wk->curPos = 0;
	wk->param->listPos = wk->param->curPos = 0;
	PoruList_CreatePMenu(wk);

	//下画面説明切り替え
	GF_BGL_BmpWinFill( &(wk->win[WIN_EXPS]),WINCLR_COL(FBMP_COL_NULL),
		0, 0,BMPL_EXPS_SX*8,BMPL_EXPS_SY*8);
	if(wk->viewMode == PVIEW_ALL){
		GF_BGL_BmpWinOn(&wk->win[WIN_EXPS]);
		return;
	}
	siz =	(BMPL_EXPS_SX*8)-
			FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.exbuf[wk->viewMode],0);

	GF_STR_PrintColor(
		&wk->win[WIN_EXPS], FONT_SYSTEM,
		wk->msgDat.exbuf[wk->viewMode],
		siz/2, 2, MSG_ALLPUT, col, NULL );
}

/**
 *	@brief	味マークアクターセット
 */
static void flaverActSet(PORU_CASE_WORK* wk,PORU_LIST* pl)
{
	u8 i = 0,flag = 0x01;

	if(pl == NULL){
		for(i = 0;i < 5;i++){
			CLACT_SetDrawFlag(wk->pActFmk[i], 0);
		}
		return;
	}
	for(i = 0;i < 5;i++){
		if(pl->flags&flag){
			CLACT_SetDrawFlag(wk->pActFmk[i], 1);
		}else{
			CLACT_SetDrawFlag(wk->pActFmk[i], 0);
		}
		flag <<= 1;
	}
}

/**
 *	@brief	ポルトリスト　メニューコールバッグ(一列表示ごと)
 *	
 *	@param	work	BMPリストで設定したワーク
 *	@param	index	BMPリストが使用しているウィンドウインデックス
 *	@param	param	BMPリストのパラメータ
 *	@param	y		Y座標
 *
 *	@return	none
 */
//--------------------------------------------------------------------------------------------
static void PoruListCB_ForLine(BMPLIST_WORK* work,u32 param,u8 y)
{
	PORU_CASE_WORK* wk = (PORU_CASE_WORK*)BmpListParamGet(work,BMPLIST_ID_WORK);
	GF_PRINTCOLOR col;
	
	col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);

#if 0
	if(wk->plist_cb_f){	//初期化時以外なら処理する
		//データシフト
		if(sys.repeat & PAD_KEY_UP){
			GF_BGL_BmpWinShift(
				&wk->win[WIN_PLISTLV], GF_BGL_BMPWIN_SHIFT_D,
				16, WINCLR_COL(FBMP_COL_NULL) );
		}else if(sys.repeat & PAD_KEY_DOWN){
			GF_BGL_BmpWinShift(
				&wk->win[WIN_PLISTLV], GF_BGL_BMPWIN_SHIFT_U,
				16, WINCLR_COL(FBMP_COL_NULL) );
		}
	}

	//LV表示	
	if(param == 0xFF){
		GF_BGL_BmpWinFill( &(wk->win[WIN_PLISTLV]),WINCLR_COL(FBMP_COL_NULL),
			0, y,BMPL_PLISTLV_SX*8,16);
	}else{
		GF_STR_PrintColor(
			&wk->win[WIN_PLISTLV], FONT_SYSTEM, wk->param->list[param].lvbuf,
			LV_OFS_X, y, MSG_NO_PUT, col, NULL );
	}
#endif
}

//--------------------------------------------------------------------------------------------
/**
 *	@brief	ポルトリスト　メニューコールバッグ(カーソル移動ごと)
 *
 * @param	work	BMPリストで設定したワーク
 * @param	param	BMPリストのパラメータ
 * @param	mode	初期化時 = 1
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PoruListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode )
{
	PORU_CASE_WORK* wk = (PORU_CASE_WORK*)BmpListParamGet(work,BMPLIST_ID_WORK);
	GF_PRINTCOLOR col;
	u16 scr,cur;
	u8 taste = 0;

	col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);

	if(!mode){
		Snd_SePlay(PORUC_SE_SEL);
	}
	//カーソル移動
	BmpListPosGet( work, &scr, &cur );
	CATS_ObjectPosSet(wk->pAct[NACT_CURSOR],NACT_CUR_PX,cur*NACT_CUR_SY+NACT_CUR_PY);
	
	//矢印マーク描画コントロール
	if(scr == 0){
		CLACT_SetDrawFlag(wk->pAct[NACT_UP],FALSE);
	}else{
		CLACT_SetDrawFlag(wk->pAct[NACT_UP],TRUE);
	}
	if(scr < (wk->viewNum-PORULIST_MAX)){
		CLACT_SetDrawFlag(wk->pAct[NACT_DOWN],TRUE);
	}else{
		CLACT_SetDrawFlag(wk->pAct[NACT_DOWN],FALSE);
	}

	//なめらかさウィンドウ一旦クリア
	GF_BGL_BmpWinFill( &(wk->win[WIN_TASTE]),WINCLR_COL(FBMP_COL_NULL),
		0, 0,BMPL_TASTE_SX*8,BMPL_TASTE_SY*8);

	if(param == 0xFF){
		flaverActSet(wk,NULL);
		GF_BGL_BmpWinOn(&wk->win[WIN_TASTE]);
		CATS_ObjectEnableCap(wk->pOam->act,FALSE);
		return;
	}
	//マーク描画
	flaverActSet(wk,&wk->param->list[param]);
	
	//なめらかさ表示
	STRBUF_Clear(wk->msgDat.tmp);

	taste = wk->param->list[param].taste;
	if(taste > 99){
		taste = 99;
	}
	WORDSET_RegisterNumber(wk->msgDat.wset,0,taste,2,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.tbuf);		
	
	GF_STR_PrintColor(
		&wk->win[WIN_TASTE], FONT_SYSTEM, wk->msgDat.tmp,
		8, 0, MSG_ALLPUT, col, NULL );
	
	//ポルト画像更新
	PoruOam_ChangeFlavor(wk->poruMan,wk->pOam,wk->param->list[param].flavor);
	CATS_ObjectEnableCap(wk->pOam->act,TRUE);
}

/**
 *	@brief	メニューリスト作成
 */
void MenuList_Create(PORU_CASE_WORK* wk)
{
	u8 i = 0;
	
	//BMPリスト領域作成
	wk->mlist = BMP_MENULIST_Create(MLIST_MAX,wk->heapID);

	for(i = 0;i < MLIST_MAX;i++){
		BMP_MENULIST_AddArchiveString(wk->mlist,
			wk->msgMan,mes_p_select_02_01+i,i);
	}

	//BMPリストを初期化
	MI_CpuCopy8(&MenuListHeader,&wk->mlist_h,sizeof(BMPLIST_HEADER));

	wk->mlist_h.win = &(wk->win[WIN_MENU]);
	wk->mlist_h.list = wk->mlist;
	wk->mlist_h.work = (void*)wk;
	wk->mlist_h.count = MLIST_MAX;

	//ウィンドウフレーム描画
	BmpMenuWinWrite( &wk->win[WIN_MENU], WINDOW_TRANS_OFF, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL );

	//リスト追加
	wk->mlist_wk = BmpListSet(&wk->mlist_h,0,0,wk->heapID);
}

/**
 *	@brief	メニューリスト削除
 */
void MenuList_Delete(PORU_CASE_WORK* wk)
{
	u16 cur,list;
	
	//ウィンドウクリア
	BmpMenuWinClear(&(wk->win[WIN_MENU]),WINDOW_TRANS_ON);	
	GF_BGL_BmpWinOff(&wk->win[WIN_MENU]);

	//リスト解放
	BmpListExit(wk->mlist_wk,&list,&cur);
	BMP_MENULIST_Delete(wk->mlist);

	wk->mlist_wk = NULL;
	wk->mlist = NULL;
}

//--------------------------------------------------------------------------------------------
/**
 *	@brief	メニューリスト　メニューコールバッグ(カーソル移動ごと)
 *
 * @param	work	BMPリストで設定したワーク
 * @param	param	BMPリストのパラメータ
 * @param	mode	初期化時 = 1
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MenuListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode )
{
	if(!mode){
		Snd_SePlay(PORUC_SE_SEL);
	}
}

/**
 *	@brief	YesNoウィンドウ描画前メッセージ表示
 */
void YesNoList_StartMsgSet(PORU_CASE_WORK* wk)
{
	//ポルトを捨てますかメッセージ描画
	STRBUF_Clear(wk->msgDat.tmp);
	WORDSET_RegisterWord( wk->msgDat.wset,0,
			PorutoName_GetNameAdrByMan(wk->nameMan,wk->param->list[wk->selectID].flavor),
			PM_NEUTRAL,TRUE,PM_LANG);
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.qbuf);		

	poru_msgWrite(wk,wk->msgDat.tmp,wk->msgDat.msg_spd,TRUE);
}

/**
 *	@brief	ポルトを捨てますメッセージセット
 */
void YesNoList_DelMsgSet(PORU_CASE_WORK* wk)
{
	//ポルトを捨てますかメッセージ描画
	STRBUF_Clear(wk->msgDat.tmp);
	WORDSET_RegisterWord( wk->msgDat.wset,0,
			PorutoName_GetNameAdrByMan(wk->nameMan,wk->param->list[wk->selectID].flavor),
			PM_NEUTRAL,TRUE,PM_LANG);
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.dbuf);		

	poru_msgWrite(wk,wk->msgDat.tmp,wk->msgDat.msg_spd,FALSE);
}

/**
 *	@brief	YesNoウィンドウ初期化
 */
void YesNoList_Create(PORU_CASE_WORK* wk)
{
	// はい・いいえ
	static const BMPWIN_DAT YesNoBmpWin = {
		BMPL_MYN_FRM,BMPL_MYN_PX,BMPL_MYN_PY,BMPL_MYN_SX,BMPL_MYN_SY,
		BMPL_MYN_PAL,BMPL_MYN_CGX
	};

	wk->ynmenu_wk = BmpYesNoSelectInit(
				wk->bgl, &YesNoBmpWin, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, wk->heapID);
}

/**
 *	@brief	初期画面描画メッセージセット
 */
void PoruCase_DrawInitialMsg(PORU_CASE_WORK* wk)
{
	int siz,i;
	GF_PRINTCOLOR col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);
	GF_PRINTCOLOR scol = GF_PRINTCOLOR_MAKE(2,3,1);
//	GF_PRINTCOLOR scol = GF_PRINTCOLOR_MAKE(2,3,15);
	
	//タイトル描画
	GF_STR_PrintColor(
		&wk->win[WIN_EXPM], FONT_SYSTEM, wk->msgDat.sbuf,
		4, 0, MSG_ALLPUT, col, NULL );

	//ボタンメッセージ描画
	for(i = 0;i < PVIEW_MAX;i++){
		static const u8 ypos[] = {2,2,4,6,2,6};
		siz = (BMPL_SW01_SX*8)-
			  FontProc_GetPrintStrWidth(FONT_BUTTON,wk->msgDat.swbuf[i],0);
		GF_STR_PrintColor(
			&wk->win[WIN_SW01+i], FONT_BUTTON, wk->msgDat.swbuf[i],
			siz/2, ypos[i], MSG_ALLPUT, scol,NULL );
	}
}

