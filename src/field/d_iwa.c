/**
 *	@file	d_iwa.c
 *	@brief	岩澤デバッグ用ソース
 *	@author	Miyuki Iwasawa
 *	@date	04.12.04
 * */

#ifdef PM_DEBUG

#include "common.h"
#include "fld_bmp.h"
#include "fntsys.h"
#include "talk_msg.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/wipe.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "field/fieldsys.h"
#include "field/field.h"
#include "field/ev_mapchange.h"
#include "field/fieldmap.h"
#include "field/zonedata.h"
#include "field/field_event.h"
#include "field/field_matrix.h"
#include "field/fld_mailbox.h"
#include "field/b_tower_ev.h"
#include "fielddata/maptable/zone_id.h"
#include "application/townmap.h"
#include "application/mailtool.h"
#include "application/poru_tool.h"
#include "application/nutmixer.h"
#include "field/fld_nmixer.h"
#include "script.h"
#include "fielddata/script/poruto_scr_def.h"
#include "fielddata/script/d31r0201_def.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_miyuki.h"
#include "savedata/guinness.h"

#include "d_iwa.h"

extern void FieldBitMapWinCgxSet( GF_BGL_INI * ini );
extern void DebugWifiBTower_DummyDataMake(SAVEDATA* sv);

#define DW0_CGX	(1)
#define DW0_SX	(12)
#define DW0_SY	(14)
#define DW0_CGXNUM	(DW0_SX*DW0_SY)
#define DW0_PAL	(FLD_SYSFONT_PAL)

static const BMPWIN_DAT d_miyuki_BmpDat[] = {
 {GF_BGL_FRAME3_M,  1,  1, DW0_SX, DW0_SY, DW0_PAL, DW0_CGX },
 { 0xFF, 0, 0, 0, 0, 0, 0 },
};

static void DebugMenuExit(TCB_PTR tcb,void* work);
//tmap
static void DebugSub_TMapNormalInit(void* work);
static void DebugSub_TMapJumpInit(void* work);
static void DebugSub_TMapBGInit(void* work);

//mail system
static void DebugSubMenu_MailBoxCall(TCB_PTR tcb,void* work);
static void DebugSub_MailCreateInit(void* work);
static void DebugSub_MailViewInit(void* work);

//poruto
static void DebugSub_PoruCaseInit(void* work);
static void DebugSub_PorutoDataMake(void* work,int mode);

//nut mixer
static void DebugSub_NutMixerLocal(void* work);

//------------------------------------------------------------------
///	メニューリストデータ
//------------------------------------------------------------------
typedef struct{
	u32	str_id;
	u32	param;
}MENU_PARAM;

static const MENU_PARAM MiyukiMenuList[] = {
	{ msg_label_script,	 BMPLIST_RABEL},			//ラベル01
	{ msg_tower_rndseed, 9},		//00:タワーランダムのたねいきなり同期
	{ msg_tower_roomf_clear, 10},		//00:タワーWifiルームフラグクリア
	{ msg_tower_guinness, 11},		//00:タワー ギネスホールデータをダミーで埋める
	{ msg_tower_wifidata, 12},		//00:タワー wifiダミーアップデートデータ作成 
	{ msg_tower_bpget, 13},		//00:タワー 500BPゲット
	{ msg_tower_bpget2, 14},		//00:タワー 9998BPゲット
	{ msg_label_tmap,	 BMPLIST_RABEL},			//ラベル01
	{ msg_dtmapN, (u32)DebugSub_TMapNormalInit},	//00:ワールドマップ
	{ msg_dtmapJ, (u32)DebugSub_TMapJumpInit},		//00:ワールドマップ
	{ msg_dtmapB, (u32)DebugSub_TMapBGInit},		//00:ワールドマップ
	{ msg_label_mail,	 BMPLIST_RABEL},			//ラベル02
	{ msg_dmailV, 2},		//00:メール見る
	{ msg_dmailC, 3},		//00:メール作成
	{ msg_label_poruto,	 BMPLIST_RABEL},			//ラベル03
	{ msg_porucase,4},		//00:ポルトケース
	{ msg_poru_allmake,5},	//00:ポルト
	{ msg_poru_alldel,6},		//00:ポルトケース
	{ msg_label_nutmixer,	 BMPLIST_RABEL},			//ラベル04
	{ msg_nmixer_local,7},		//00:ナッツミキサーローカル
	{ msg_nmixer_scr,8},		//00:ナッツミキサースクリプト
	{ msg_exit,		 0x00000001},		//00:閉じる
	{ msg_label_end,	 BMPLIST_RABEL},			//ラベル02
};

#define BLIST_NUM	NELEMS(MiyukiMenuList)

///	リストシステムからのコールバック※一行表示ごと
static void	InfoCallBack(BMPLIST_WORK* lw,u32 param,u8 y)
{
	if(param == BMPLIST_RABEL){
		BmpListTmpColorChange(lw,FBMP_COL_BLU_SDW,FBMP_COL_BLACK,FBMP_COL_BLUE);
	}else{
		BmpListTmpColorChange(lw,FBMP_COL_WHITE,FBMP_COL_BLACK,FBMP_COL_BLK_SDW);
	}
}

//------------------------------------------------------------------
///	項目リストデータ
//------------------------------------------------------------------
static const BMPLIST_HEADER DebugListHeader = {
	NULL,			//表示文字データポインタ
	NULL,				//カーソル移動ごとのコールバック関数
	InfoCallBack,		//１行ごとのコールバック関数

	NULL,				//GF_BGL_BMPWIN構造体データへのポインタ
	BLIST_NUM,			//リスト項目数
	6,					//表示最大項目数
	2,					//ラベル表示Ｘ座標
	12,					//項目表示Ｘ座標
	1,					//カーソル表示Ｘ座標
	2,					//表示Ｙ座標
	FBMP_COL_WHITE,		//文字色
	FBMP_COL_BLACK,		//背景色
	FBMP_COL_BLK_SDW,	//文字影色
	0,					//文字間隔Ｘ
	1,					//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,	//ページスキップタイプ
	FONT_SYSTEM,		//文字指定
	0,					//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
	NULL,				//ワークポインタ
};

//プロトタイプ
void DebugMiyukiInit(void* fsys);
static void DebugMiyukiEnd(TCB_PTR tcb,void* work);

/**
 *	@brief	リスト初期化
 */
void DebugMiyukiViewInit(_DebugIwaWork* wp,void* fsys,u8 list,u8 cursor)
{
	int i;

	const MENU_PARAM* menuParam = MiyukiMenuList;
	int	size = NELEMS(MiyukiMenuList);
	wp->fsys =fsys;
	
	//BMPウィンドウ初期化(FieldSysの初期化データを取得)
	wp->pBglIni = FieldBglIniGet(fsys);
	
	//ウィンドウキャラクタセット
	FieldBitMapWinCgxSet(wp->pBglIni);

	GF_BGL_ScrFill(wp->pBglIni,GF_BGL_FRAME3_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_LoadScreenV_Req(wp->pBglIni,GF_BGL_FRAME3_M);

	//クリア
	memset(&(wp->bmpwin),0,sizeof(GF_BGL_BMPWIN));
	wp->List = list;

	//BMPMAPメニュー追加
	wp->menulist = BMP_MENULIST_Create(size,HEAPID_BASE_DEBUG);
	GF_BGL_BmpWinAddEx(wp->pBglIni,&(wp->bmpwin),d_miyuki_BmpDat);

	if(menuParam != NULL){
		MSGDATA_MANAGER* msgman;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
					NARC_msg_debug_miyuki_dat,HEAPID_BASE_DEBUG);

		for(i = 0;i < size;i++){
			BMP_MENULIST_AddArchiveString(wp->menulist,
				msgman, menuParam[i].str_id, menuParam[i].param );
		}
		MSGMAN_Delete(msgman);
	}else{
		STRCODE	tmpbuf[128];
		STRBUF	*mstr = STRBUF_Create(128,HEAPID_BASE_DEBUG);
		for(i = 0;i < size;i++){
			PM_strclear(tmpbuf,EOM_,128);
			STRBUF_Clear(mstr);
			
			//ゾーン名取得
			if(ASCIIcode2DSuni(0,(u8*)ZoneData_GetZoneName(i+2),tmpbuf)){
				tmpbuf[0] = EOM_;
			}
			STRBUF_SetStringCode(mstr,tmpbuf);
			BMP_MENULIST_AddString(wp->menulist,mstr,i+2);
		}
		STRBUF_Delete(mstr);
	}
	
	//BMPリスト設定
	memcpy(&(wp->bmplist_h),&DebugListHeader,sizeof(BMPLIST_HEADER));
	wp->Cursor = cursor;
	wp->bmplist_h.win = &(wp->bmpwin);
	wp->bmplist_h.list = wp->menulist;
	wp->bmplist_h.work = (void*)wp->blistWk;
	wp->bmplist_h.count = size;
	wp->blistWk = BmpListSet(&(wp->bmplist_h),wp->List,wp->Cursor,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	リスト解放
 */
void DebugMiyukiViewEnd(_DebugIwaWork* wp)
{
	//BMPWIN破棄
	GF_BGL_BmpWinOff(&(wp->bmpwin));	//WindowOFF
	//BMPリストの開放
	BmpListExit(wp->blistWk,&(wp->List),&(wp->Cursor));	//リスト破棄
	BMP_MENULIST_Delete(wp->menulist);	//メニュー文字列破棄
	GF_BGL_BmpWinDel(&(wp->bmpwin));	//BMPWindowDel
}

/**
 *	デバッグシステム初期化
 *
 *	u8	DebugMiyukiInit(void* fsys)
 *
 *	@param	void* FLD_DEB_DATへのポインタ
 *	@return none
 */
void DebugMiyukiInit(void* fsys)
{
	TCB_PTR	pTcb = NULL;
	_DebugIwaWork *wp = NULL;
	GF_BGL_INI *ini = NULL;

	//デバッグシステムメモリ確保
	wp = sys_AllocMemory(HEAPID_BASE_DEBUG,sizeof(_DebugIwaWork));

	if(wp == NULL){
		//ワークが確保できなれば何もしない
		OS_Printf("iwasawa debug menu create field\n");
		return;
	}
	memset(wp,0,sizeof(_DebugIwaWork));

	DebugMiyukiViewInit(wp,fsys,0,1);
	wp->seq = DMSEQ_FADEOUT;

	pTcb = TCB_Add(DebugMiyukiMain,wp,0);
}

//=============================================================================
/**
 *	デバッグシステムキー取得(メインタスク)
 *	void DebugMiyukiMain(u8 id);
 *
 *	@param	tcb	TCB_PTR	タスクブロックポインタ	
 *	@param	work	タスクワークポインタ	
 *	@return	none
 */
//=============================================================================
void DebugMiyukiMain(TCB_PTR tcb,void* work)
{
	s32	ret_code;
	TCB_FUNC	func;
	_DebugIwaWork	*wp;

	wp = (_DebugIwaWork*)work;

	ret_code = BmpListMain(wp->blistWk);

	//キー操作判定
	if(sys.trg & PAD_BUTTON_DECIDE){
		switch(ret_code){
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
			DebugMiyukiEnd(tcb,work);
			return;
		default:
			switch(ret_code){
			case 0:
				return;
			case 1:	//メニュー終了
				DebugMiyukiEnd(tcb,work);
				return;
			case 2:	//メール
			case 3:
				wp->ret_val = ret_code-1;
				DebugSubMenu_MailBoxCall(tcb,work);
				return;
			case 4:	//ポルトケース
				wp->UserFunc = DebugSub_PoruCaseInit;
				TCB_ChangeFunc(tcb,DebugMiyukiFuncCall);
				wp->func_mode = 2;
				return;
			case 5:	//ポルト満タン
				DebugSub_PorutoDataMake(wp,0);
				DebugMiyukiEnd(tcb,work);
				return;
			case 6:	//ポルト空っぽ
				DebugSub_PorutoDataMake(wp,1);
				DebugMiyukiEnd(tcb,work);
				return;
			case 7:	//ナッツミキサーローカル
				wp->UserFunc = DebugSub_NutMixerLocal;
				TCB_ChangeFunc(tcb,DebugMiyukiFuncCall);
				wp->func_mode = 0;
				return;
			case 8:	//ナッツミキサースクリプト
				EventSet_Script(wp->fsys,SCRID_PORUTO_SCR,NULL);
				DebugMiyukiEnd(tcb,work);
				return;
			case 9:	//タワースクリプト　ランダムの種いきなり同期
				BtlTower_UpdateDayRndSeed(wp->fsys->savedata);
	//			EventSet_Script(wp->fsys,SCRID_TOWER_GATE_LOCAL_01,NULL);
//				EventSet_Script(wp->fsys,SCRID_D31R0201_GIRL2_01,NULL);
				DebugMiyukiEnd(tcb,work);
				return;
			case 10:	//タワー wifiルームフラグクリア
				TowerWifiData_ClearRoomDataFlag(
					SaveData_GetTowerWifiData(wp->fsys->savedata));
				DebugMiyukiEnd(tcb,work);
				return;
			case 11:	//ギネスホール　デバッグ　記録一杯
				DebugGNSRank_MakeDmyRankingData(
					SaveData_GetGuinnessData(wp->fsys->savedata));
				return;
			case 12:	//wifiタワーダミーアップデートデータ作成
				DebugWifiBTower_DummyDataMake(wp->fsys->savedata);
				return;
			case 13:	//500BPゲット
				TowerScoreData_SetBattlePoint(
					SaveData_GetTowerScoreData(wp->fsys->savedata),500,BTWR_DATA_add);
				return;
			case 14:	//9998BPゲット
				TowerScoreData_SetBattlePoint(
					SaveData_GetTowerScoreData(wp->fsys->savedata),9998,BTWR_DATA_set);
				return;
			default:
				//関数ポインタ保存
				wp->UserFunc = (void*)ret_code;
				TCB_ChangeFunc(tcb,DebugMiyukiFuncCall);

				if(	ret_code == (u32)DebugSub_TMapNormalInit ||
					ret_code == (u32)DebugSub_TMapJumpInit ||
					ret_code == (u32)DebugSub_TMapBGInit){
					wp->func_mode = 1;
				}
			}
			return;
		}
		return;
	}
	//メニューキャンセル
	if(sys.trg & PAD_BUTTON_B){
		DebugMiyukiEnd(tcb,work);
		return;
	}
}

/**
 *	@brief	デバッグメニューの終了処理
 *
 *	デバッグメニュー用ワークとリストの破棄を行う
 *	@param	tcb		TCB_PTR:呼び出し元タスクブロックへのポインタ
 *	@param	work	void*:呼び出し元タスクブロックワークへのポインタ
 */
static void DebugMiyukiEnd(TCB_PTR tcb,void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	DebugMiyukiViewEnd(wp);

	//デバッグワークメモリ開放
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);

	//OBJ等の動作停止解除
	FieldSystemProc_SeqHoldEnd();
	return;
}

#if 0
static void DebugMiyukiSubMenuWait(TCB_PTR tcb,void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;
	
	if(!wp->ret_val){
		return;
	}
	wp->ret_val = 0;
	//デバッグメニュー復帰
	DebugMiyukiViewInit(wp,wp->fsys,wp->List,wp->Cursor);
	TCB_ChangeFunc(tcb,DebugMiyukiMain);
}
#endif
/**
 *	@brief	デバッグメニューを閉じる
 */
static void DebugMenuExit(TCB_PTR tcb,void* work)
{
	DebugMiyukiEnd(tcb,work);	
}

/**
 *	@brief	デバッグメニュー　タウンマップ呼び出し
 */
//extern void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode);

static void* DebugTMapCall(FIELDSYS_WORK* fsys,u8 mode)
{
	TOWNMAP_PARAM * tp;
	tp = sys_AllocMemoryLo(HEAPID_BASE_DEBUG, sizeof(TOWNMAP_PARAM));

	FieldTMap_CallDataSet(fsys,tp,mode);
	FieldTMap_SetProc( fsys, tp );
	return tp;
}
/**
 *	@brief	デバッグメニュー　タウンマップ呼び出しシーケンス初期化
 */
static void DebugSub_TMapNormalInit(void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	wp->subWork = DebugTMapCall(wp->fsys,TMAP_MNORMAL);
}
/**
 *	@brief	デバッグメニュー　タウンマップ呼び出しシーケンス初期化
 */
static void DebugSub_TMapJumpInit(void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	wp->subWork = DebugTMapCall(wp->fsys,TMAP_MJUMP);
}
/**
 *	@brief	デバッグメニュー　タウンマップ呼び出しシーケンス初期化
 */
static void DebugSub_TMapBGInit(void* work)
{
	_DebugIwaWork	*wp = (_DebugIwaWork*)work;

	wp->subWork = DebugTMapCall(wp->fsys,TMAP_MBG);
}

static void DebugSubMenu_MailBoxCall(TCB_PTR tcb,void* work)
{
	_DebugIwaWork *wp  =(_DebugIwaWork*)work;
	
	//デバッグメニューウィンドウ破棄
	DebugMiyukiViewEnd(wp);

	//メールボックスタスク登録
	MailBox_Call(wp->fsys,&(wp->ret_val));
	TCB_ChangeFunc(tcb,DebugMiyukiSubMenuWait);
	FieldSystemProc_SeqHold();
}

/**
 *	@brief	デバッグメニュー　メール作成呼び出し
 */
static void DebugSub_MailCreateInit(void* work)
{
	_DebugIwaWork *wp  =(_DebugIwaWork*)work;

	wp->subWork =  FieldMailCreate_InitCall( wp->fsys ,
		MAILBLOCK_TEMOTI,0,0,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	デバッグメニュー　メール描画呼び出し
 */
static void DebugSub_MailViewInit(void* work)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;

	wp->subWork =  FieldMailView_InitCall(wp->fsys,
		MAILBLOCK_TEMOTI,0,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	デバッグメニュー　ポルトケース呼び出し
 */
static void DebugSub_PoruCaseInit(void* work)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;
	wp->subWork = FieldPorutoCase_InitCall(wp->fsys,HEAPID_BASE_DEBUG);
}

/**
 *	@brief	デバッグメニュー　ポルトデータ作成
 */
static void DebugSub_PorutoDataMake(void* work,int mode)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;
	PORUTO_BLOCK* block = NULL;

	block = SaveData_GetPorutoBlock(GameSystem_GetSaveData(wp->fsys));

	if(mode == 0){
		PorutoDebug_AddRndData(block,100);
	}else{
		PorutoDebug_AllDataDelete(block);
	}
}

/**
 *	@brief	ナッツミキサー　ローカル
 */
static void DebugSub_NutMixerLocal(void* work)
{
	_DebugIwaWork *wp  = (_DebugIwaWork*)work;
	wp->subWork = FieldNutMixer_InitCall(wp->fsys,NUTMIXER_CALL_LOCAL,HEAPID_BASE_DEBUG);
}

#endif	//PM_DEBUG
