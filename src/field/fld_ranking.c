/**
 *	@file	fld_ranking.c
 *	@brief	フィールド　ギネスランキング表示
 *	@author	Miyuki Iwasawa
 *	@date	06.06.06
 */
#include "common.h"
#include "fld_bmp.h"
#include "fntsys.h"
#include "talk_msg.h"
#include "fieldmap.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/brightness.h"
#include "system/wipe.h"
#include "system/buflen.h"
#include "system/pm_str.h"
#include "system/arc_util.h"
#include "system/pmfprint.h"
#include "system/snd_tool.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"
#include "field/fieldsys.h"
#include "field/field.h"
#include "field/field_event.h"
#include "field_clact.h"
#include "application/app_tool.h"

#include "savedata/guinness.h"
#include "msgdata/msg_ranking.h"
#include "msgdata/msg.naix"

#define __FLD_RANKING_H_GLOBAL
#include "fld_ranking.h"
#include "field/ranking.naix"

#define RANKLIST_MAX	(7)	///<ランキングリストの最大数

#define UNITBUF_NUM	(7)		///<単位系メッセージバッファ数
#define MSGBUF_NUM	(3)		///<メッセージ系バッファ数

#define RANKING_ACTMAX	(2)	///<アクター数
typedef struct _RANK_MSG{
	MSGDATA_MANAGER*	pMan;

	WORDSET* wset;	//ワーク
	STRBUF*	tmp;	//汎用
	STRBUF* ebuf;	//とじる
	STRBUF* sbuf;	//どの記録を
	STRBUF* dbuf;	//記録を消す
	STRBUF* nbuf;	//名前
	STRBUF*	ubuf[UNITBUF_NUM];	//単位
	STRBUF*	rbuf[6];
	STRBUF*	gbuf[6];
	STRBUF*	mbuf[MSGBUF_NUM];
}RANK_MSG;

typedef struct _RANK{
	GNS_RECORD*	rp;	//レコードデータへのポインタ
	u16	valid_f;	//有効無効フラグ
	u8	my_id;		//自分のデータへのindex
}RANK;

typedef struct _RANK_LIST{
	int		num;	//リストの項目数
	RANK	list[RANKLIST_MAX];
}RANK_LIST;

typedef struct _RANK_UNIT{
	u32	max;	///<最大値
	u16	keta;	///<桁数
	u16	unit;	///<単位系ナンバー
}RANK_UNIT;

typedef struct _RANKING_VIEW_MAIN{
	int	heapID;
	int* end_flag;
	int	main_seq;
	int	seq;

	u16	bg0_pri;	///<BG0のプライオリティ保存
	u16	bg2_pri;	///<BG2のプライオリティ保存
	u16	mode;		///<呼び出しモード
	u8	dataType;	///<データタイプ
	u8	grpType;	///<グループタイプ
	u8	blockNum;	///<ブロック数
	u8	gnsIdx;		///<ギネスブロックアクセスIndex
		
	u16	msg_spd;	///<コンフィグメッセージスピード
	u16	win_type;	///<コンフィグウィンドウタイプ

	u8	msgIdx;
	u8	sel_block;		///<選んだブロック
	u8	sel_data;		///<選んだデータ
	u8	rec_list_num;	///<現在の表示レコードリストの数
	u16	blk_list;
	u16	blk_cur;
	u16	rec_list;
	u16	rec_cur;
	RANK_MSG	msgDat;	///<メッセージ関連データ

	BMPLIST_HEADER	bmplist_h;
	BMPLIST_WORK*	blistWk; 
	BMPLIST_DATA*	menulist; 
	BMPMENU_WORK*	ynmenu_wk;
	
	FIELDSYS_WORK*	fsys;
	GF_BGL_INI* bgl;
	GF_BGL_BMPWIN	bmpwin;
	GF_BGL_BMPWIN	msgwin;
	GF_BGL_BMPWIN	expwin;
	GF_BGL_BMPWIN	win[3];
	FIELD_CLACT		fcat;
	CATS_ACT_PTR	act[2];

	GUINNESS*		gnsSave;
	GNS_RANKING*	rank[7];
	RANK_LIST*		viewList;
	RANK*			pNRank;
	u8				list_idx[6];
}RANKING_VIEW_MAIN;

typedef struct _RANKING_VIEW_EVENT{
	int	seq;
	u16	mode;
	RANKING_VIEW_MAIN* app_wk;
}RANKING_VIEW_EVENT;


//----------------------------------------------
//定数定義
//----------------------------------------------
#define WORDSET_RANKING_BUFLEN	(38*2)

#define RANK_MENU_EXIT	(0xFFFF)
enum{
 RANK_SEQ_INIT,
 RANK_SEQ_DATA_INIT,
 RANK_SEQ_BLOCK_START,
 RANK_SEQ_BLOCK_MAIN,
 RANK_SEQ_RECORD_START,
 RANK_SEQ_RECORD_MAIN,
 RANK_SEQ_RECORD_DEL_MAIN,
 RANK_SEQ_RECORD_DEL,
 RANK_SEQ_RECORD_DEL_NG,
 RANK_SEQ_MAIN,
 RANK_SEQ_DATA_RELEASE,
 RANK_SEQ_END,
 RANK_SEQ_EXIT,
};

#define TALK_FCOL	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE))
#define TALK_NCOL	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL))
#define BMPL_MENU_WIN_CGX	(MENU_WIN_CGX_NUM)
#define BMPL_TALK_WIN_CGX	(TALK_WIN_CGX_NUM)
#define BMPL_MENU_WIN_PAL	(FLD_MENUFRAME_PAL)
#define BMPL_TALK_WIN_PAL	(FLD_MESFRAME_PAL)

//会話ウィンドウ
#define BMPL_TALK_PX	(FLD_MSG_WIN_PX)
#define BMPL_TALK_PY	(FLD_MSG_WIN_PY)
#define BMPL_TALK_SX	(FLD_MSG_WIN_SX)
#define BMPL_TALK_SY	(FLD_MSG_WIN_SY)
#define BMPL_TALK_PAL	(FLD_MSG_WIN_PAL)
#define BMPL_TALK_CGX	(BMPL_MENU_WIN_CGX-BMPL_TALK_SX*BMPL_TALK_SY)

//YNウィンドウ
#define BMPL_YESNO_PX	(FLD_YESNO_WIN_PX)
#define BMPL_YESNO_PY	(FLD_YESNO_WIN_PY)
#define BMPL_YESNO_SX	(FLD_YESNO_WIN_SX)
#define BMPL_YESNO_SY	(FLD_YESNO_WIN_SY)
#define BMPL_YESNO_PAL	(FLD_YESNO_WIN_PAL)
#define BMPL_YESNO_CGX	(BMPL_TALK_CGX-BMPL_YESNO_SX*BMPL_YESNO_SY)

//↓自前のウィンドウ
#define RANKING_CGX_START	(BMPL_YESNO_CGX)
#define RANKING_FRAME		(FLD_MBGFRM_FONT)
#define RANKING_FRAME2		(FLD_MBGFRM_EFFECT1)
#define RANKING_FPAL		(FLD_SYSFONT_PAL)

//Selectメニューウィンドウ
#define EXP_WIN_PX		(8)
#define EXP_WIN_PY		(14)
#define EXP_WIN_SX		(8)
#define EXP_WIN_SY		(2)
#define EXP_WIN_PAL		(RANKING_FPAL)
#define EXP_WIN_FRM		(RAINKING_FRAME)
#define EXP_WIN_CGX		(RANKING_CGX_START-(EXP_WIN_SX*EXP_WIN_SY))

//ブロックウィンドウ(Yサイズ可変)
#define LIST_WIN_PX		(4)
#define LIST_WIN_PY		(1)
#define LIST_WIN_SX		(24)
#define LIST_WIN_SY		(12)
#define LIST_WIN_PAL	(RANKING_FPAL)
#define LIST_WIN_FRM	(RANKING_FRAME2)
#define LIST_WIN_CGX01	(1)
#define LIST_WIN_CGX02	(1)
//#define LIST_WIN_CGX02	(EXP_WIN_CGX-(LIST_WIN_SX*LIST_WIN_SY))

#define FRAME2_CGX_NUM	(LIST_WIN_SX*(LIST_WIN_SY+2)+MENU_WIN_CGX_SIZE+1)

//=======================================
//アクター関連定義
//=======================================
#define RANKING_CHR_RES_MAX	(1)
#define RANKING_PAL_RES_MAX	(1)
#define RANKING_CEL_RES_MAX	(1)
#define RANKING_ANM_RES_MAX	(1)

enum {
	RANKING_CHR_H_ID_CURSOR	= 13528,
};
enum {
	RANKING_PAL_H_ID = 13528,
};
enum {
	RANKING_CEL_H_ID_CURSOR	= 13528,
};
enum {
	RANKING_ANM_H_ID_CURSOR	= 13528,
};

#define ACT_CURSOR	(0)
#define ACT_PANEL	(1)
#define ACT_RES_PAL_NUM	(3)

#define CURSOR_PX	(126)
#define CURSOR_PY	(16)
#define CURSOR_ANMNO	(0)
#define CURSOR_SPRI	(0)
#define CURSOR_PRI	(1)
#define CURSOR_PALT	(1)
#define CURSOR_PALF	(2)

#define PANEL_PX	(74)
#define PANEL_PY	(120)
#define PANEL_ANMNO	(1)
#define PANEL_SPRI	(1)
#define PANEL_PRI	(1)
#define PANEL_PAL	(0)

#define LIST_X_OFS	(8)
//------------------------------------------------------------------
///	項目リストデータ
//------------------------------------------------------------------
static const BMPLIST_HEADER RankingListHeader = {
	NULL,			//表示文字データポインタ
	NULL,			//カーソル移動ごとのコールバック関数
	NULL,			//１行ごとのコールバック関数
	NULL,			//GF_BGL_BMPWIN構造体データへのポインタ
	0,				//リスト項目数
	7,					//表示最大項目数
	2,					//ラベル表示Ｘ座標
	LIST_X_OFS,			//項目表示Ｘ座標
	1,					//カーソル表示Ｘ座標
	0,					//表示Ｙ座標
	FBMP_COL_BLACK,		//文字色
	FBMP_COL_WHITE,		//背景色
	FBMP_COL_BLK_SDW,	//文字影色
	0,					//文字間隔Ｘ
	0,					//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
	FONT_SYSTEM,		//文字指定
	1,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	NULL,				//ワークポインタ
};

///リスト描画単位系データ
static const RANK_UNIT unit_btl[] = {
 {9999,4,msg_count_00},
 {9999,4,msg_count_00},
 {9999,4,msg_count_00},
 {9999,4,msg_count_00},
 {9999,4,msg_count_00},
 {7,1,msg_count_01},
};
static const RANK_UNIT	unit_poke[] = {
 {999999,6,msg_count_04},
 {999999,6,msg_count_04},
 {999999,6,msg_count_03},
 {999999,6,msg_count_04},
};
static const RANK_UNIT unit_contest[] = {
 {9999,4,msg_count_06},
 {100,4,msg_count_05},
 {65535,5,msg_count_02},
};

static const RANK_UNIT* const unit_list[] = {
 unit_btl,unit_poke,unit_contest
};
//------------------------------------------------------------------
///	プロトタイプ
//------------------------------------------------------------------
static void ranking_GetSaveData(RANKING_VIEW_MAIN* wk,SAVEDATA* sv);
static void ranking_FreeSaveData(RANKING_VIEW_MAIN* wk);
static void ranking_GetMsgData(RANKING_VIEW_MAIN* wk);
static void ranking_FreeMsgData(RANKING_VIEW_MAIN* wk);
static void ranking_AddComWin(RANKING_VIEW_MAIN* wk);
static void ranking_DelComWin(RANKING_VIEW_MAIN* wk);
static void ranking_ActorInit(RANKING_VIEW_MAIN* wk);
static void ranking_ActorRelease(RANKING_VIEW_MAIN* wk);
static void ranking_BlockMenuStart(RANKING_VIEW_MAIN* wk,u16 list,u16 cur);
static void ranking_BlockMenuEnd(RANKING_VIEW_MAIN* wk);
static void ranking_CB_BlockListMove(BMPLIST_WORK * work, u32 param, u8 mode);
static void ranking_RecordDelMsgWrite(RANKING_VIEW_MAIN* wk);
static void ranking_DelModeStateWrite(RANKING_VIEW_MAIN* wk);
static void ranking_ViewModeStateWrite(RANKING_VIEW_MAIN* wk);
static void ranking_RecordMenuWrite(RANKING_VIEW_MAIN* wk,BOOL cur_f);
static void ranking_RecordMenuStart(RANKING_VIEW_MAIN* wk,u16 cur);
static void ranking_RecordMenuEnd(RANKING_VIEW_MAIN* wk);

//------------------------------------------------------------------
///	メインシーケンス
//------------------------------------------------------------------
/**
 *	@brief	全体初期化
 */
static int RankSeq_Init(RANKING_VIEW_EVENT* main,FIELDSYS_WORK* fsys,u16 mode) 
{
	RANKING_VIEW_MAIN *wk;
	SAVEDATA* sv = fsys->savedata;
	
	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_RANKING_VIEW,0x6000);
	HeapStatePush();

	wk = sys_AllocMemory( HEAPID_RANKING_VIEW,sizeof(RANKING_VIEW_MAIN));
	MI_CpuClear8(wk,sizeof(RANKING_VIEW_MAIN));

	wk->heapID = HEAPID_RANKING_VIEW;

	//データタイプとグループタイプを取得
	wk->dataType = mode%3;
	wk->grpType = mode/3;
	wk->blockNum = GNSRank_GetTypeBlockNum(wk->dataType);
	wk->gnsIdx	 = GNSRank_GetTypeGNSIDOfs(wk->dataType);
	wk->fsys = fsys;
	wk->bgl = fsys->bgl;

	//ギネスセーブデータへのポインタ取得
	wk->gnsSave = SaveData_GetGuinnessData(sv);

	//コンフィグ関連
	wk->msg_spd = CONFIG_GetMsgPrintSpeed(SaveData_GetConfig(sv));
	wk->win_type = CONFIG_GetWindowType(SaveData_GetConfig(sv));

	main->app_wk = wk;

	return RANK_SEQ_DATA_INIT;
}

/**
 *	@brief	全体終了処理
 */
static int RankSeq_End(RANKING_VIEW_EVENT* main)
{
	int i,j,ct,heapID;
	RANK*	lp;
	RANKING_VIEW_MAIN* wk = main->app_wk;

	//セーブデータ反映処理
	for(i = 0; i < wk->blockNum;i++){
		ct = 0;
		for(j = 0;j < wk->viewList[i].num;j++){
			lp = &(wk->viewList[i].list[j]);
			if(lp->my_id == 0xFF || lp->valid_f){
				continue;
			}
			//セーブデータ削除
			GuinnessData_DelRecord(wk->gnsSave,(wk->grpType*GNS_RECORD_NUM)+wk->gnsIdx+i,lp->my_id-ct);
			++ct;
		}
	}
	//メモリ解放
	heapID = wk->heapID;
	sys_FreeMemoryEz(wk);
	MI_CpuClear8(wk,sizeof(RANKING_VIEW_MAIN));

	//ヒープ解放
	HeapStatePop();
	HeapStateCheck(heapID);	
	sys_DeleteHeap(heapID);

	return RANK_SEQ_EXIT;
}
/**
 *	@brief	データ初期化
 */
static int RankSeq_DataInit(RANKING_VIEW_MAIN* wk,SAVEDATA* sv)
{
	ranking_GetSaveData(wk,sv);
	ranking_GetMsgData(wk);
	ranking_AddComWin(wk);
	ranking_ActorInit(wk);
	return RANK_SEQ_BLOCK_START;
//	return RANK_SEQ_DATA_RELEASE;
}

/**
 *	@brief	データ解放
 */
static int RankSeq_DataRelease(RANKING_VIEW_MAIN* wk)
{
	ranking_ActorRelease(wk);
	ranking_DelComWin(wk);
	ranking_FreeMsgData(wk);
	ranking_FreeSaveData(wk);
	return RANK_SEQ_END;
}

/**
 *	@brief	ブロック選択リスト初期化
 */
static int RankSeq_BlockListStart(RANKING_VIEW_MAIN* wk)
{
	ranking_BlockMenuStart(wk,wk->blk_list,wk->blk_cur);
	return RANK_SEQ_BLOCK_MAIN;
}

/**
 *	@brief	ブロック選択リストメイン
 */
static int RankSeq_BlockListMain(RANKING_VIEW_MAIN* wk)
{
	s32	ret_code;

	ret_code = BmpListMain(wk->blistWk);

	if(sys.trg & PAD_BUTTON_CANCEL){
		ranking_BlockMenuEnd(wk);
		return RANK_SEQ_DATA_RELEASE;
	}
	if(!(sys.trg & PAD_BUTTON_DECIDE)){
		return RANK_SEQ_BLOCK_MAIN;
	}

	switch(ret_code){
	case BMPMENU_NULL:
	case BMPMENU_CANCEL:
	case RANK_MENU_EXIT:
		ranking_BlockMenuEnd(wk);
		return RANK_SEQ_DATA_RELEASE;
	default:
		wk->sel_block = ret_code;
		wk->rec_cur = 0;
		ranking_BlockMenuEnd(wk);
		return RANK_SEQ_RECORD_START;
	}
	return RANK_SEQ_BLOCK_MAIN;
}

/**
 *	@brief	レコードメニュースタート
 */
static int RankSeq_RecordListStart(RANKING_VIEW_MAIN* wk)
{
	ranking_RecordMenuStart(wk,wk->rec_cur);
	return RANK_SEQ_RECORD_MAIN;
}

/**
 *	@brief	レコードメニューメイン
 */
static int RankSeq_RecordListMain(RANKING_VIEW_MAIN* wk)
{
	if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
		ranking_RecordMenuEnd(wk);
		return RANK_SEQ_BLOCK_START;
	}

	if(sys.trg & PAD_BUTTON_SELECT){
		ranking_DelModeStateWrite(wk);
		return RANK_SEQ_RECORD_DEL_MAIN;
	}

	return RANK_SEQ_RECORD_MAIN;
}

/**
 *	@brief	レコード削除メイン
 */
static int RankSeq_RecordDelMain(RANKING_VIEW_MAIN* wk)
{
	RANK* rp;
	if(sys.trg & (PAD_BUTTON_CANCEL)){
		//削除モード終了
		ranking_ViewModeStateWrite(wk);
		return RANK_SEQ_RECORD_MAIN;
	}

	//本当に消しますか？
	if(sys.trg & PAD_BUTTON_DECIDE){
		wk->seq = 0;
		wk->pNRank = &(wk->viewList[wk->sel_block].list[wk->list_idx[wk->rec_cur]]);
		if(wk->pNRank->my_id == 0xFF){
			//自分なので消せない
			return RANK_SEQ_RECORD_DEL_NG;
		}
		//本当に消しますか？
		return RANK_SEQ_RECORD_DEL;
	}
	
	if(sys.trg & PAD_KEY_UP){
		if(wk->rec_cur > 0){
			--wk->rec_cur;
			CATS_ObjectPosSetCap(wk->act[ACT_CURSOR],CURSOR_PX,CURSOR_PY+16*wk->rec_cur);
		}
	}
	if(sys.trg & PAD_KEY_DOWN){
		if(wk->rec_cur < (wk->rec_list_num-1)){
			++wk->rec_cur;
			CATS_ObjectPosSetCap(wk->act[ACT_CURSOR],CURSOR_PX,CURSOR_PY+16*wk->rec_cur);
		}
	}
	
	return RANK_SEQ_RECORD_DEL_MAIN;
}

/**
 *	@brief	YNウィンドウ初期化
 */
static void ranking_YesNoInit(RANKING_VIEW_MAIN* wk)
{
	static const BMPWIN_DAT YesNoBmpWin = {
		RANKING_FRAME,BMPL_YESNO_PX,BMPL_YESNO_PY,BMPL_YESNO_SX,BMPL_YESNO_SY,
		BMPL_YESNO_PAL,BMPL_YESNO_CGX
	};

	wk->ynmenu_wk = BmpYesNoSelectInit(
				wk->bgl, &YesNoBmpWin, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, wk->heapID);
}

/**
 *	@brief	レコード削除フロー
 */
static int RankSeq_RecordDel(RANKING_VIEW_MAIN* wk)
{
	int ret = 0;
	
	switch(wk->seq){
	case 0:
		//本当に消しますかメッセージ描画
		GF_BGL_BmpWinDataFill(&wk->msgwin,APP_WINCLR_COL(FBMP_COL_WHITE));
		wk->msgIdx = GF_STR_PrintColor(&wk->msgwin, FONT_TALK,wk->msgDat.mbuf[1],
			0, 0, wk->msg_spd, TALK_FCOL, NULL );

		//選択カーソルを灰色に変更
		CATS_ObjectPaletteSetCap(wk->act[ACT_CURSOR],CURSOR_PALF);
		wk->seq++;
		break;
	case 1:
		//描画終了待ち
		if( GF_MSG_PrintEndCheck( wk->msgIdx )){
			break;
		}
		//yesnoウィンドウ描画
		ranking_YesNoInit(wk);
		wk->seq++;
		break;
	case 2:
		//yesno選択待ち
		switch( BmpYesNoSelectMain( wk->ynmenu_wk, wk->heapID) ){
		case 0:	//はい
	//		Snd_SePlay(PORUC_SE_DECIDE);
			wk->seq++;
			break;
		case BMPMENU_CANCEL: //いいえ
	//		Snd_SePlay(PORUC_SE_DECIDE);
			wk->seq = 0xFF;
			break;
		}
		break;
	case 3:
		//データの有効フラグを落とす
		wk->pNRank->valid_f = 0;
		//リスト再描画
		ranking_RecordMenuWrite(wk,TRUE);
		CATS_ObjectPaletteSetCap(wk->act[ACT_CURSOR],CURSOR_PALT);
		wk->seq = 0;
		return RANK_SEQ_RECORD_DEL_MAIN;
	case 0xFF:
		//やっぱ止めた
		ranking_RecordDelMsgWrite(wk);
		CATS_ObjectPaletteSetCap(wk->act[ACT_CURSOR],CURSOR_PALT);
		wk->seq = 0;
		return RANK_SEQ_RECORD_DEL_MAIN;
	}
	return RANK_SEQ_RECORD_DEL;
}

/**
 *	@brief	自分のデータは削除できません
 */
static int RankSeq_RecordDelNg(RANKING_VIEW_MAIN* wk)
{
	int ret = 0;
	
	switch(wk->seq){
	case 0:
		//自分のデータは消せませんメッセージ描画
		GF_BGL_BmpWinDataFill(&wk->msgwin,APP_WINCLR_COL(FBMP_COL_WHITE));
		wk->msgIdx = GF_STR_PrintColor(&wk->msgwin, FONT_TALK,wk->msgDat.mbuf[2],
			0, 0, wk->msg_spd, TALK_FCOL, NULL );
		//選択カーソルを灰色に変更
		CATS_ObjectPaletteSetCap(wk->act[ACT_CURSOR],CURSOR_PALF);
		wk->seq++;
		break;
	case 1:
		//描画終了待ち
		if( GF_MSG_PrintEndCheck( wk->msgIdx )){
			break;
		}
		wk->seq++;
		break;
	case 2:
		if(!(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL))){
			break;
		}
		//消す記録を選んでください
		ranking_RecordDelMsgWrite(wk);
		CATS_ObjectPaletteSetCap(wk->act[ACT_CURSOR],CURSOR_PALT);
		wk->seq = 0;
		return RANK_SEQ_RECORD_DEL_MAIN;
	}
	return RANK_SEQ_RECORD_DEL_NG;
}


/**
 *	@brief	モード別セーブデータ取得
 */
static void ranking_GetSaveData(RANKING_VIEW_MAIN* wk,SAVEDATA* sv)
{
	int i,j,ct,flag;
	GNS_RANKING*	gp;
	
	//レコードリスト操作用メモリ取得
	wk->viewList = sys_AllocMemory(wk->heapID,sizeof(RANK_LIST)*wk->blockNum);
	MI_CpuClear8(wk->viewList,sizeof(RANK_LIST)*wk->blockNum);

	//自分のレコードデータ
	wk->rank[0] = GNSRank_AllocMyData(sv,wk->dataType,wk->heapID);

	//レコードランキングデータ
	for(i = 0;i < wk->blockNum;i++){
		wk->rank[i+1] = GNSRank_AllocRankingData(wk->gnsSave,
			(wk->grpType*GNS_RECORD_NUM)+wk->gnsIdx+i,wk->heapID);

		gp = wk->rank[i+1];
		ct = 0;
		flag = 0;
#if 1
		if(gp->num == 0){
			//自分だけ
			wk->viewList[i].list[0].rp = &(wk->rank[0]->rank[i]);
			wk->viewList[i].list[0].valid_f = 1;
			wk->viewList[i].list[0].my_id = 0xFF;
			wk->viewList[i].num = 1;
		}else{
			for(j = 0;j < gp->num;j++){
				if(	(flag == 0) && 
					(wk->rank[0]->rank[i].record >= gp->rank[j].record)){
					//自分を挿入
					wk->viewList[i].list[ct].rp = &(wk->rank[0]->rank[i]);
					wk->viewList[i].list[ct].valid_f = 1;
					wk->viewList[i].list[ct].my_id = 0xFF;
					++ct;
					wk->viewList[i].list[ct].rp = &(gp->rank[j]);
					wk->viewList[i].list[ct].valid_f = 1;
					wk->viewList[i].list[ct].my_id = j;
					flag = 1;
				}else{
					wk->viewList[i].list[ct].rp = &(gp->rank[j]);
					wk->viewList[i].list[ct].valid_f = 1;
					wk->viewList[i].list[ct].my_id = j;
				}
				++ct;
			}
			if(!flag){
				//最後に自分を追加
				wk->viewList[i].list[ct].rp = &(wk->rank[0]->rank[i]);
				wk->viewList[i].list[ct].valid_f = 1;
				wk->viewList[i].list[ct].my_id = 0xFF;
			}
			wk->viewList[i].num = gp->num+1;
		}
#endif
	}
}

/**
 *	@brief	セーブデータ取得領域解放
 */
static void ranking_FreeSaveData(RANKING_VIEW_MAIN* wk)
{
	int i;

	for(i = 0;i < wk->blockNum+1;i++){
		GNSRank_FreeRankingData(wk->rank[i]);
	}
	sys_FreeMemoryEz(wk->viewList);
}

/**
 *	@brief	メッセージデフォルトリソース取得
 */
static void ranking_GetMsgData(RANKING_VIEW_MAIN* wk)
{
	int i;
	
	wk->msgDat.pMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_ranking_dat,wk->heapID);
	
	wk->msgDat.wset = WORDSET_CreateEx(2,WORDSET_RANKING_BUFLEN,wk->heapID);

	//デフォルト文字列取得
	wk->msgDat.tmp = STRBUF_Create(WORDSET_RANKING_BUFLEN,wk->heapID);
	//とじる
	wk->msgDat.ebuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_end_00);
	//どの記録を
	wk->msgDat.sbuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_guide_00);
	//記録を消す
	wk->msgDat.dbuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_delete_00);
	//名前展開場所
	wk->msgDat.nbuf = MSGMAN_AllocString(wk->msgDat.pMan,msg_ranking_01);

	//ブロック選択リスト
	for(i = 0;i < wk->blockNum;i++){
		wk->msgDat.rbuf[i] = 
			MSGMAN_AllocString(wk->msgDat.pMan,msg_battle_00+wk->gnsIdx+i);	
		wk->msgDat.gbuf[i] = 
			MSGMAN_AllocString(wk->msgDat.pMan,msg_guide_01+wk->gnsIdx+i);	
	}
	//カウント
	for(i = 0;i < UNITBUF_NUM;i++){
		wk->msgDat.ubuf[i] = 
			MSGMAN_AllocString(wk->msgDat.pMan,msg_count_00+i);
	}
	//メッセージ
	for(i = 0;i< MSGBUF_NUM;i++){
		wk->msgDat.mbuf[i] = 
			MSGMAN_AllocString(wk->msgDat.pMan,msg_delete_01+i);
	}
}

/**
 *	@brief	メッセージデフォルトリソース破棄
 */
static void ranking_FreeMsgData(RANKING_VIEW_MAIN* wk)
{
	int i;

	for(i = 0;i < MSGBUF_NUM;i++){
		STRBUF_Delete(wk->msgDat.mbuf[i]);
	}
	for(i = 0;i < UNITBUF_NUM;i++){
		STRBUF_Delete(wk->msgDat.ubuf[i]);
	}
	for(i = 0;i < wk->blockNum;i++){
		STRBUF_Delete(wk->msgDat.rbuf[i]);
		STRBUF_Delete(wk->msgDat.gbuf[i]);
	}
	STRBUF_Delete(wk->msgDat.nbuf);
	STRBUF_Delete(wk->msgDat.dbuf);
	STRBUF_Delete(wk->msgDat.sbuf);
	STRBUF_Delete(wk->msgDat.ebuf);
	STRBUF_Delete(wk->msgDat.tmp);
	
	WORDSET_Delete(wk->msgDat.wset);
	MSGMAN_Delete(wk->msgDat.pMan);	
}

/**
 *	@brief	デフォルトウィンドウ追加
 */
static void ranking_AddComWin(RANKING_VIEW_MAIN* wk)
{
	//エフェクト用BG面を特別に使う
	GF_BGL_ClearCharSet(RANKING_FRAME2,32*FRAME2_CGX_NUM,0,wk->heapID);
	GF_BGL_ScrFill(wk->bgl,RANKING_FRAME2,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_LoadScreenV_Req(wk->bgl,RANKING_FRAME2);
	GF_BGL_VisibleSet(RANKING_FRAME2,VISIBLE_ON);
	wk->bg0_pri = GF_BGL_PriorityGet(wk->bgl,GF_BGL_FRAME0_M);
	wk->bg2_pri = GF_BGL_PriorityGet(wk->bgl,RANKING_FRAME2);
	GF_BGL_PrioritySet(GF_BGL_FRAME0_M,2);
	GF_BGL_PrioritySet(RANKING_FRAME2,1);
	
	//コモンウィンドウグラフィックセット
	TalkWinGraphicSet(wk->bgl,RANKING_FRAME,
			BMPL_TALK_WIN_CGX,BMPL_TALK_WIN_PAL,wk->win_type,wk->heapID);
	MenuWinGraphicSet(wk->bgl,RANKING_FRAME,
			BMPL_MENU_WIN_CGX,BMPL_MENU_WIN_PAL,MENU_TYPE_SYSTEM,wk->heapID);
	MenuWinGraphicSet(wk->bgl,RANKING_FRAME2,
			BMPL_MENU_WIN_CGX,BMPL_MENU_WIN_PAL,MENU_TYPE_SYSTEM,wk->heapID);

	SystemFontPaletteLoad(PALTYPE_MAIN_BG,FLD_SYSFONT_PAL*32,wk->heapID);
	TalkFontPaletteLoad(PALTYPE_MAIN_BG,FLD_MESFONT_PAL*32,wk->heapID);

	//会話ウィンドウ追加
	GF_BGL_BmpWinAdd(
			wk->bgl, &wk->msgwin, RANKING_FRAME,
			BMPL_TALK_PX,BMPL_TALK_PY,BMPL_TALK_SX,BMPL_TALK_SY,
			BMPL_TALK_PAL,BMPL_TALK_CGX);
	GF_BGL_BmpWinDataFill(&wk->msgwin,APP_WINCLR_COL(FBMP_COL_WHITE));
//	GF_BGL_BmpWinOn(&wk->msgwin);
}

/**
 *	@brief	デフォルトウィンドウ破棄
 */
static void ranking_DelComWin(RANKING_VIEW_MAIN* wk)
{
	BmpTalkWinClear( &wk->msgwin, WINDOW_TRANS_OFF);
	GF_BGL_BmpWinOff(&wk->msgwin);	
	GF_BGL_BmpWinDel(&wk->msgwin);
	
	//エフェクト面領域クリア
	GF_BGL_ClearCharSet(RANKING_FRAME2,32*FRAME2_CGX_NUM,0,wk->heapID);
	GF_BGL_ScrFill(wk->bgl,RANKING_FRAME2,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_LoadScreenV_Req(wk->bgl,RANKING_FRAME2);
	GF_BGL_VisibleSet(RANKING_FRAME2,VISIBLE_OFF);
	GF_BGL_PrioritySet(GF_BGL_FRAME0_M,wk->bg0_pri);
	GF_BGL_PrioritySet(RANKING_FRAME2,wk->bg2_pri);
}


/**
 *	@brief	アクター初期化
 */
static void ranking_ActorInit(RANKING_VIEW_MAIN* wk)
{
	int i;
	TCATS_RESOURCE_NUM_LIST	crnl = {
		RANKING_CHR_RES_MAX, RANKING_PAL_RES_MAX,
		RANKING_CEL_RES_MAX, RANKING_ANM_RES_MAX, 0, 0
	};

	static const TCATS_OBJECT_ADD_PARAM_S ActAddParam_S[] =
	{
		{	// 選択カーソル
			CURSOR_PX, CURSOR_PY, 0,
			CURSOR_ANMNO, CURSOR_SPRI, CURSOR_PALT, NNS_G2D_VRAM_TYPE_2DMAIN,
			{
				RANKING_CHR_H_ID_CURSOR, RANKING_PAL_H_ID,
				RANKING_CEL_H_ID_CURSOR, RANKING_ANM_H_ID_CURSOR, 0, 0,
			},
			CURSOR_PRI, 0
		},
		{	// 記録を消すパネル 
			PANEL_PX, PANEL_PY, 0,
			PANEL_ANMNO, PANEL_SPRI, PANEL_PAL, NNS_G2D_VRAM_TYPE_2DMAIN,
			{
				RANKING_CHR_H_ID_CURSOR, RANKING_PAL_H_ID,
				RANKING_CEL_H_ID_CURSOR, RANKING_ANM_H_ID_CURSOR, 0, 0,
			},
			PANEL_PRI, 0
		},
	};
	
	//フィールドセルアクター初期化
	FieldCellActSet_S( &wk->fcat, &crnl, RANKING_ACTMAX, wk->heapID);

	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_RANKING_GRA,NARC_ranking_ranking_nclr,
		0, ACT_RES_PAL_NUM, NNS_G2D_VRAM_TYPE_2DMAIN, RANKING_PAL_H_ID );

	FldClact_LoadResCellArc(
		&wk->fcat, ARC_RANKING_GRA, NARC_ranking_ranking_ncer,
		0, RANKING_CEL_H_ID_CURSOR );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_RANKING_GRA, NARC_ranking_ranking_nanr,
		0, RANKING_ANM_H_ID_CURSOR );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_RANKING_GRA, NARC_ranking_ranking_ncgr,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, RANKING_CHR_H_ID_CURSOR );

	for(i = 0;i < RANKING_ACTMAX;i++){
		wk->act[i] = FieldCellActAdd_S( &wk->fcat, &ActAddParam_S[i] );
	}
	//パネルの初期状態は非表示
	CATS_ObjectEnableCap(wk->act[ACT_PANEL],FALSE);
}
/**
 *	@brief	アクター削除
 */
static void ranking_ActorRelease(RANKING_VIEW_MAIN* wk)
{
	int i;

	for(i = 0;i < RANKING_ACTMAX;i++){
		if(wk->act[i] != NULL){
			CATS_ActorPointerDelete_S(wk->act[i]);
		}
	}
	FieldCellActDelete_S(&wk->fcat);
}

/**
 *	@brief	ブロックメニュー作成
 */
static void ranking_BlockMenuStart(RANKING_VIEW_MAIN* wk,u16 list,u16 cur)
{
	int i,size;

	size = wk->blockNum+1;
	wk->menulist = BMP_MENULIST_Create(size,wk->heapID);

	GF_BGL_BmpWinAdd(wk->bgl, &wk->bmpwin,LIST_WIN_FRM,LIST_WIN_PX,LIST_WIN_PY,
			LIST_WIN_SX,size*2,LIST_WIN_PAL,LIST_WIN_CGX01);
	GF_BGL_BmpWinDataFill(&wk->bmpwin,APP_WINCLR_COL(FBMP_COL_WHITE));

	for(i = 0;i < wk->blockNum;i++){
		BMP_MENULIST_AddString(wk->menulist,wk->msgDat.rbuf[i],i);
	}
	//閉じる追加
	BMP_MENULIST_AddString(wk->menulist,wk->msgDat.ebuf,RANK_MENU_EXIT);

	//BMPリスト設定
	MI_CpuCopy8((void*)&RankingListHeader,(void*)&(wk->bmplist_h),sizeof(BMPLIST_HEADER));
	wk->bmplist_h.win = &(wk->bmpwin);
	wk->bmplist_h.list = wk->menulist;
	wk->bmplist_h.work = (void*)wk;
	wk->bmplist_h.count = size;
	wk->bmplist_h.line_y = 0;
	wk->bmplist_h.call_back = ranking_CB_BlockListMove;
	wk->bmplist_h.icon = NULL;//mbox_CB_MailListLine;
	
	wk->blistWk = BmpListSet(&(wk->bmplist_h),list,cur,wk->heapID);
	BmpMenuWinWrite( &wk->bmpwin, WINDOW_TRANS_ON, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL );

	//どの記録を見ますか？メッセージ描画
	BmpTalkWinWrite( &wk->msgwin, WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL);		
	GF_BGL_BmpWinDataFill(&wk->msgwin,APP_WINCLR_COL(FBMP_COL_WHITE));
	GF_STR_PrintColor(
		&wk->msgwin, FONT_TALK,wk->msgDat.sbuf,
		0, 0, MSG_ALLPUT, TALK_FCOL, NULL );
	
	//カーソルアクター表示
	CATS_ObjectEnableCap(wk->act[ACT_CURSOR],TRUE);

	GF_BGL_LoadScreenV_Req(wk->bgl,RANKING_FRAME);
}

/**
 *	@brief	ブロックメニュー破棄
 */
static void ranking_BlockMenuEnd(RANKING_VIEW_MAIN* wk)
{
	//BMPリストの開放
	BmpListExit(wk->blistWk,&(wk->blk_list),&(wk->blk_cur));	//リスト破棄
	BMP_MENULIST_Delete(wk->menulist);	//メニュー文字列破棄

	GF_BGL_BmpWinOff(&(wk->bmpwin));	//WindowOFF	
	BmpMenuWinClear( &(wk->bmpwin),WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&(wk->bmpwin));	//BMP Window Del
	
	//カーソルアクターを隠す
	CATS_ObjectEnableCap(wk->act[ACT_CURSOR],FALSE);
	
	GF_BGL_LoadScreenV_Req(wk->bgl,RANKING_FRAME);	
}

/**
 *	@brief	ブロックメニュー　カーソル移動コールバック
 */
static void ranking_CB_BlockListMove(BMPLIST_WORK * work, u32 param, u8 mode)
{
	u16	scr,cur,ct;
	RANKING_VIEW_MAIN* wk = (RANKING_VIEW_MAIN*)BmpListParamGet(work,BMPLIST_ID_WORK);

	//カーソル移動
	BmpListPosGet( work, &scr, &cur );
	ct = BmpListParamGet(work,BMPLIST_ID_COUNT);

	CATS_ObjectPosSetCap(wk->act[ACT_CURSOR],CURSOR_PX,CURSOR_PY+16*(cur+scr));
}

/**
 *	@brief	消す記録を選んでくださいメッセージ描画
 */
static void ranking_RecordDelMsgWrite(RANKING_VIEW_MAIN* wk)
{
	//消したい記録を選んでください
	GF_BGL_BmpWinDataFill(&wk->msgwin,APP_WINCLR_COL(FBMP_COL_WHITE));
	GF_STR_PrintColor(&wk->msgwin, FONT_TALK,wk->msgDat.mbuf[0],
		0, 0, MSG_ALLPUT, TALK_FCOL, NULL );
}

/**
 *	@brief	削除モードスタート描画
 */
static void ranking_DelModeStateWrite(RANKING_VIEW_MAIN* wk)
{
//	ranking_RecordDelMsgWrite(wk);
	//消したい記録を選んでください
	ranking_RecordDelMsgWrite(wk);
	
	CATS_ObjectPosSetCap(wk->act[ACT_CURSOR],CURSOR_PX,CURSOR_PY+wk->rec_cur*16);
	CATS_ObjectEnableCap(wk->act[ACT_CURSOR],TRUE);	
}

/**
 *	@brief	レコード閲覧モードスタート描画
 */
static void ranking_ViewModeStateWrite(RANKING_VIEW_MAIN* wk)
{
	//ガイドメッセージ描画
	GF_BGL_BmpWinDataFill(&wk->msgwin,APP_WINCLR_COL(FBMP_COL_WHITE));
	GF_STR_PrintColor(
		&wk->msgwin, FONT_TALK,wk->msgDat.gbuf[wk->sel_block],
			0, 0, MSG_ALLPUT, TALK_FCOL, NULL );
	
//	CATS_ObjectPosSetCap(wk->act[ACT_CURSOR],CURSOR_PX,CURSOR_PY+wk->rec_cur*16);
	CATS_ObjectEnableCap(wk->act[ACT_CURSOR],FALSE);	
}

/**
 *	@brief レコードメニュー描画
 */
static void ranking_RecordMenuWrite(RANKING_VIEW_MAIN* wk,BOOL cur_f)
{
	int i,size,rank,ct,value,value2;
	RANK_LIST* lp;
	const RANK_UNIT*	up;
	
	lp = &(wk->viewList[wk->sel_block]);
	up = &(unit_list[wk->dataType][wk->sel_block]);
	
	GF_BGL_BmpWinDataFill(&wk->bmpwin,APP_WINCLR_COL(FBMP_COL_WHITE));

	size = lp->num;
	rank = 1;
	ct = 0;
	value2 = 0;
	for(i = 0;i < lp->num;i++){
		if(!lp->list[i].valid_f){
			continue;
		}
		//ランキングナンバーを算出
		value = lp->list[i].rp->record;
		if(value > up->max){
			value = up->max;
		}
		if(value < value2){
			++rank;
		}
		//ランキングと名前
		WORDSET_RegisterNumber(wk->msgDat.wset,0,rank,1,
					NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterWord( wk->msgDat.wset,1,
					lp->list[i].rp->name,PM_NEUTRAL,TRUE,PM_LANG);

		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.nbuf);
	
		GF_STR_PrintColor(&wk->bmpwin, FONT_SYSTEM,wk->msgDat.tmp,
			LIST_X_OFS, ct*16, MSG_NO_PUT, TALK_FCOL, NULL );

		//レコード
		WORDSET_RegisterNumber(wk->msgDat.wset,0,value,up->keta,
				NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,
				wk->msgDat.ubuf[up->unit-msg_count_00]);
		
		GF_STR_PrintColor(&wk->bmpwin, FONT_SYSTEM,wk->msgDat.tmp,
			(LIST_WIN_SX*8)-FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.tmp,0)-LIST_X_OFS,
			ct*16,
			MSG_NO_PUT, TALK_FCOL, NULL );

		wk->list_idx[ct] = i;
		value2 = value;	//ひとつ前の値を覚えておく
		if(++ct >= 6){
			break;	//描画するリストは6まで
		}
	}
	GF_BGL_BmpWinOn(&wk->bmpwin);
	
	//現在の表示レコード数を保存
	wk->rec_list_num = ct;
	//カーソル位置調整
	if((wk->rec_cur > 0 ) && (wk->rec_cur >= wk->rec_list_num)){
		wk->rec_cur--;
	}
	
	if(cur_f){	//削除モード
		ranking_DelModeStateWrite(wk);
	}else{	//閲覧モード
		ranking_ViewModeStateWrite(wk);
	}
}

/**
 *	@brief	レコードメニュー作成
 */
static void ranking_RecordMenuStart(RANKING_VIEW_MAIN* wk,u16 cur)
{
	//メニュー用ウィンドウ追加
	GF_BGL_BmpWinAdd(wk->bgl, &wk->bmpwin,LIST_WIN_FRM,LIST_WIN_PX,LIST_WIN_PY,
			LIST_WIN_SX,LIST_WIN_SY,LIST_WIN_PAL,LIST_WIN_CGX02);
	
	//リスト描画
	BmpMenuWinWrite( &wk->bmpwin, WINDOW_TRANS_OFF, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL );
	ranking_RecordMenuWrite(wk,FALSE);

	//記録を消すパネル描画
	CATS_ObjectEnableCap(wk->act[ACT_PANEL],TRUE);
	
	//記録を消すウィンドウ追加
	GF_BGL_BmpWinAdd(
			wk->bgl, &wk->expwin, RANKING_FRAME,
			EXP_WIN_PX,EXP_WIN_PY,EXP_WIN_SX,EXP_WIN_SY,
			EXP_WIN_PAL,EXP_WIN_CGX);
	GF_BGL_BmpWinDataFill(&wk->expwin,APP_WINCLR_COL(FBMP_COL_NULL));
	GF_STR_PrintColor(
		&wk->expwin, FONT_SYSTEM,wk->msgDat.dbuf,
		0, 0, MSG_ALLPUT, TALK_NCOL, NULL );

	GF_BGL_LoadScreenV_Req(wk->bgl,RANKING_FRAME);
}

/**
 *	@brief	レコードメニュー破棄
 */
static void ranking_RecordMenuEnd(RANKING_VIEW_MAIN* wk)
{
	//リストウィンドウ消去
	GF_BGL_BmpWinOff(&wk->bmpwin);
	BmpMenuWinClear(&wk->bmpwin,WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&wk->bmpwin);

	//記録を消すボタン消去
	GF_BGL_BmpWinOff(&wk->expwin);	
	GF_BGL_BmpWinDel(&wk->expwin);	

	//カーソルアクターを隠す
	CATS_ObjectEnableCap(wk->act[ACT_CURSOR],FALSE);
	//パネルアクターを隠す
	CATS_ObjectEnableCap(wk->act[ACT_PANEL],FALSE);
}

//========================================================
//	スクリプトコマンド
//========================================================
//--------------------------------------------------------------
/**
 * @brief	ギネスランキング画面イベント 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
 */
//--------------------------------------------------------------
static BOOL RankingViewEvent_Main( GMEVENT_CONTROL *ev )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
	RANKING_VIEW_EVENT *main = FieldEvent_GetSpecialWork( ev );
	RANKING_VIEW_MAIN *wk = main->app_wk;

	switch (main->seq) {
	case RANK_SEQ_INIT:
		main->seq = RankSeq_Init(main,fsys,main->mode);
		break;
	case RANK_SEQ_DATA_INIT:
		main->seq = RankSeq_DataInit(main->app_wk,fsys->savedata);
		break;
	case RANK_SEQ_BLOCK_START:
		main->seq = RankSeq_BlockListStart(main->app_wk);
		CLACT_Draw(main->app_wk->fcat.cas);
		break;
	case RANK_SEQ_BLOCK_MAIN:
		main->seq = RankSeq_BlockListMain(main->app_wk);
		CLACT_Draw(main->app_wk->fcat.cas);
		break;
	case RANK_SEQ_RECORD_START:
		main->seq = RankSeq_RecordListStart(main->app_wk);
		CLACT_Draw(main->app_wk->fcat.cas);
		break;
	case RANK_SEQ_RECORD_MAIN:
		main->seq = RankSeq_RecordListMain(main->app_wk);
		CLACT_Draw(main->app_wk->fcat.cas);
		break;
	case RANK_SEQ_RECORD_DEL_MAIN:
		main->seq = RankSeq_RecordDelMain(main->app_wk);
		CLACT_Draw(main->app_wk->fcat.cas);
		break;
	case RANK_SEQ_RECORD_DEL:
		main->seq = RankSeq_RecordDel(main->app_wk);
		CLACT_Draw(main->app_wk->fcat.cas);
		break;
	case RANK_SEQ_RECORD_DEL_NG:
		main->seq = RankSeq_RecordDelNg(wk);
		CLACT_Draw(main->app_wk->fcat.cas);
		break;
	case RANK_SEQ_MAIN:
		if(!(sys.trg & PAD_BUTTON_DECIDE)){
			return FALSE;
		}
		main->seq = RANK_SEQ_DATA_RELEASE;
		break;
	case RANK_SEQ_DATA_RELEASE:
		main->seq = RankSeq_DataRelease(main->app_wk);
		break;
	case RANK_SEQ_END:
		main->seq = RankSeq_End(main);
		break;
	case RANK_SEQ_EXIT:
		sys_FreeMemoryEz(main);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ランキング画面サブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		移動方向
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_RankingViewCall( GMEVENT_CONTROL *event,u16 mode)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	RANKING_VIEW_EVENT* wk = sys_AllocMemory( HEAPID_WORLD,sizeof(RANKING_VIEW_EVENT));
	
	wk->seq = 0;
	wk->mode = mode;
	wk->app_wk = NULL;

	FieldEvent_Call( fsys->event, RankingViewEvent_Main, wk);
}

