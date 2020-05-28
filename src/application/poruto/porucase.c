/**
 *	@file	porucase.c
 *	@brief	ポルトケース　プロセスメイン
 *	@author	Miyuki Iwasawa
 *	@date	06.03.11
 */

#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/buflen.h"
#include "system/window.h"
#include "system/brightness.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/wipe.h"
#include "system/window.h"
#include "gflib/touchpanel.h"

#include "application/app_tool.h"
#include "savedata/poruto_util.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_poruto_select.h"
#include "porusys.h"
#include "poru_act.h"
#include "porucase_bmp.h"
#include "poru_gra.naix"

//===========================================
//プロトタイプ
//===========================================
PROC_RESULT PoruCase_Init(PROC* proc,int* seq);
PROC_RESULT PoruCase_Main(PROC* proc,int* seq);
PROC_RESULT PoruCase_End(PROC* proc,int* seq);

static int PoruCaseMain(PORU_CASE_WORK* wk);

static int PoruCaseResInit(PORU_CASE_WORK* wk);
static int PoruCaseResRelease(PORU_CASE_WORK* wk);
static void PoruCase_VBankSet(void);

static void PoruCase_BGLInit(PORU_CASE_WORK* wk);
static void PoruCase_BGLRelease(PORU_CASE_WORK* wk);
static void PoruCase_2DGraInit(PORU_CASE_WORK* wk);
static void PoruCase_2DGraRelease(PORU_CASE_WORK* wk);
static void PoruCase_BmpWinAdd(PORU_CASE_WORK* wk);
static void PoruCase_BmpWinDel(PORU_CASE_WORK* wk);
static void PoruCase_MsgManagerGet(PORU_CASE_WORK* wk);
static void PoruCase_MsgManagerRelease(PORU_CASE_WORK* wk);
static void PoruCase_MakeActor(PORU_CASE_WORK* wk);
static void PoruCase_DelActor(PORU_CASE_WORK* wk);

static int PoruCaseMode_SelectPoruto(PORU_CASE_WORK* wk);
static int PoruCaseMode_MenuInit(PORU_CASE_WORK* wk);
static int PoruCaseMode_MenuWait(PORU_CASE_WORK* wk);
static int PoruCaseMode_YNSet(PORU_CASE_WORK* wk);
static int PoruCaseMode_YNWait(PORU_CASE_WORK* wk);
static int PoruCaseMode_Del(PORU_CASE_WORK* wk);

typedef int (*PCaseSubFunc)(PORU_CASE_WORK* wk);

static const PCaseSubFunc caseMainFunc[] = {
 PoruCaseMode_SelectPoruto,
 PoruCaseMode_MenuInit,
 PoruCaseMode_MenuWait,
 PoruCaseMode_YNSet,
 PoruCaseMode_YNWait,
 PoruCaseMode_Del,
};

//=========================================================
//プロセス定義
//=========================================================
/**
 *	@brief	ポルトケース呼び出し
 */
PROC_RESULT PoruCase_Init(PROC* proc,int* seq)
{
	PORU_CASE_WORK* wk = NULL;
	PORUTO_PARAM* pp = PROC_GetParentWork(proc);

	HeapStatePush();

	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_PORUTO_CASE,0x20000);
	
	wk = PROC_AllocWork(proc,sizeof(PORU_CASE_WORK),HEAPID_PORUTO_CASE);
	MI_CpuClear8(wk,sizeof(PORU_CASE_WORK));

	wk->heapID = HEAPID_PORUTO_CASE;
	wk->param = pp;
	wk->viewMode = pp->ret_view;	//PVIEW_SPICY;//PVIEW_ALL;	///初めは全部
	wk->tp_f = BACT_ST_INI;		///初期状態

	return PROC_RES_FINISH;
}

/**
 *	@brief	ポルトケースメイン
 */
PROC_RESULT PoruCase_Main(PROC* proc,int* seq)
{
	PORU_CASE_WORK* wk = (PORU_CASE_WORK*)PROC_GetWork(proc);

	if(PoruCaseMain(wk)){
		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	ポルトケース終了
 */
PROC_RESULT PoruCase_End(PROC* proc,int* seq)
{
	PORU_CASE_WORK* wk = (PORU_CASE_WORK*)PROC_GetWork(proc);

	//上位ワークへ戻り値を格納
	wk->param->selID = wk->selectID;
	wk->param->ret_mode = wk->ret_mode;
	wk->param->ret_view = wk->viewMode;
	wk->param->listPos = wk->listPos;
	wk->param->curPos = wk->curPos;
	
	//ワーク解放
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(wk->heapID);
	
	sys_DeleteHeap(wk->heapID);

	return PROC_RES_FINISH;
}

/**
 *	@brief	ポルトケースメイン
 */
static int PoruCaseMain(PORU_CASE_WORK* wk)
{
	switch(wk->seq){
	case 0:
		//Blank関数リセット
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);	
		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		WIPE_ResetWndMask(WIPE_DISP_MAIN);
		WIPE_ResetWndMask(WIPE_DISP_SUB);

		//タッチパネル初期化
		InitTPSystem();
		InitTPNoBuff(4);
		break;
	case 1:
		if(!PoruCaseResInit(wk)){
			return FALSE;
		}
		wk->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEIN,
				WIPE_TYPE_FADEIN,0x0000,COMM_BRIGHTNESS_SYNC,1,wk->heapID
				);
		break;
	case 2:
		PoruCase_ActorMain(wk);
		if(!WIPE_SYS_EndCheck()){
			return FALSE;
		}
		break;
	case 3:
		PoruCase_ActorMain(wk);
		if((caseMainFunc[wk->selMode])(wk) == FALSE){
			return FALSE;
		}
		wk->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,0x0000,COMM_BRIGHTNESS_SYNC,1,wk->heapID
				);
		
		break;
	case 4:
		PoruCase_ActorMain(wk);
		if(!WIPE_SYS_EndCheck()){
			return FALSE;
		}
		break;
	case 5:
		if(!PoruCaseResRelease(wk)){
			return FALSE;
		}
		break;
	case 6:
		//タッチパネル終了
		StopTP();

		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		sys_VBlankFuncChange(NULL, NULL);
		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);	
		break;
	default:
		return TRUE;
	}
	wk->seq++;
	return FALSE;
}

/**
 *	@brief	ポルトケースVBlank関数
 */
static void PoruCaseVBlank(void* work)
{
	PORU_CASE_WORK* wk = (PORU_CASE_WORK*)work;

	//アクター転送
	if(wk->pActSys != NULL){
		CATS_RenderOamTrans();
	}

	DoVramTransferManager();
//	NNS_GfdDoVramTransfer();	//VRam転送マネージャ実行
	GF_BGL_VBlankFunc( wk->bgl );
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//======================================================
//キー取得サブプロセス

/**
 *	@brief	タッチパネルチェック
 */
static int PoruCase_TPCheck(PORU_CASE_WORK* wk)
{
	int ret;
	u16 pat;
	static const RECT_HIT_TBL PoruCase_TpRect[] = {
//		{0,191,0,255},
		{TP_SPICY_NY-TP_SY,TP_SPICY_NY+TP_SY,TP_SPICY_NX-TP_SX,TP_SPICY_NX+TP_SX},
		{TP_ASTR_NY-TP_SY,TP_ASTR_NY+TP_SY,TP_ASTR_NX-TP_SX,TP_ASTR_NX+TP_SX},
		{TP_SWEET_NY-TP_SY,TP_SWEET_NY+TP_SY,TP_SWEET_NX-TP_SX,TP_SWEET_NX+TP_SX},
		{TP_BITTER_NY-TP_SY,TP_BITTER_NY+TP_SY,TP_BITTER_NX-TP_SX,TP_BITTER_NX+TP_SX},
		{TP_SOUR_NY-TP_SY,TP_SOUR_NY+TP_SY,TP_SOUR_NX-TP_SX,TP_SOUR_NX+TP_SX},
		{TP_ALL_NY-TP_SY,TP_ALL_NY+TP_SY,TP_ALL_NX-TP_SX,TP_ALL_NX+TP_SX},
		{RECT_HIT_END,0,0,0}
	};
	
	ret = GF_TP_RectHitTrg(PoruCase_TpRect);
	if(ret != RECT_HIT_NONE){
		return ret;
	}
	ret = GF_TP_RectHitCont(PoruCase_TpRect);
	if(ret == RECT_HIT_NONE){
		if(wk->tp_f == BACT_ST_01){
			PoruBtn_StateSet(wk,wk->viewMode,BACT_ST_02);
		}
	}
	return -1;
}

/**
 *	@brief	ポルト選択モードメイン
 */
static int PoruCaseMode_SelectPoruto(PORU_CASE_WORK* wk)
{
	u32	ret_code = BMPLIST_NULL;
	int tp_ret = 0;
	if(wk->plist_wk == NULL){
		return 0;
	}
		//タッチパネルチェック
	tp_ret = PoruCase_TPCheck(wk);
	
	if(sys.cont != 0){
		if(wk->tp_f == BACT_ST_NULL){
			//タッチパネルアニメ中でなければ通常キーチェック
			ret_code = BmpListMain(wk->plist_wk);
		}
	}else{
		if(tp_ret >= 0){
			PoruList_SortMenu(wk,(u8)tp_ret);
		}
		return FALSE;
	}

	if(ret_code == BMPLIST_NULL){
		return FALSE;
	}
	if(sys.trg & PAD_BUTTON_CANCEL){
		//SE
		Snd_SePlay(PORUC_SE_DECIDE);
		
		wk->selectID = 0xFF;
		wk->ret_mode = PCASE_RET_CANCEL;
		return TRUE;
	}
	
	if(sys.trg & PAD_BUTTON_DECIDE){
		//SE
		Snd_SePlay(PORUC_SE_DECIDE);
		
		switch(ret_code){
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
		case 0xFF:
			wk->selectID = 0xFF;
			wk->ret_mode = PCASE_RET_CANCEL;
			return TRUE;
		default:
			wk->selectID = ret_code;
			wk->selMode = PCASE_MODE_MSEL;
			return FALSE;
		}
	}
	return 0;
}

/**
 *	@brief	動作モード初期化メイン
 */
static int PoruCaseMode_MenuInit(PORU_CASE_WORK* wk)
{
	u32	ret_code;

	//カーソルの色を灰色に変える
	NAct_CursorChg(wk,TRUE);
	
	//メニューリスト作成&表示
	MenuList_Create(wk);
	wk->selMode = PCASE_MODE_MSELWAIT; 

	return FALSE;
}

/**
 *	@brief	動作モード選択メイン
 */
static int PoruCaseMode_MenuWait(PORU_CASE_WORK* wk)
{
	u32	ret_code;

	ret_code = BmpListMain(wk->mlist_wk);

	if(sys.trg & PAD_BUTTON_CANCEL){
		//SE
		Snd_SePlay(PORUC_SE_DECIDE);
		
		MenuList_Delete(wk);
		NAct_CursorChg(wk,FALSE);
		wk->selMode = PCASE_MODE_PSEL; 
		return FALSE;
	}
	
	if(sys.trg & PAD_BUTTON_DECIDE){
		//SE
		Snd_SePlay(PORUC_SE_DECIDE);
		
		switch(ret_code){
		case MLIST_PUT:
			wk->ret_mode = PCASE_RET_DECIDE;
			return TRUE;
		case MLIST_DEL:
			MenuList_Delete(wk);
			YesNoList_StartMsgSet(wk);
			wk->selMode = PCASE_MODE_YNSET; 
			break;
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
		default:
			MenuList_Delete(wk);
			NAct_CursorChg(wk,FALSE);
			wk->selMode = PCASE_MODE_PSEL; 
			break;
		}
	}
	return FALSE;
}

/**
 *	@brief	ポルトを捨てますかメッセージ描画待ち
 */
static int PoruCaseMode_YNSet(PORU_CASE_WORK* wk)
{
	if( GF_MSG_PrintEndCheck( wk->msgIdx )){
		return FALSE;
	}
	YesNoList_Create(wk);
	wk->selMode = PCASE_MODE_YNWAIT;
	return FALSE;
}

/**
 *	@brief	ポルトを捨てる選択待ち
 */
static int PoruCaseMode_YNWait(PORU_CASE_WORK* wk)
{
	//ポルトを捨てますか？
	switch( BmpYesNoSelectMain( wk->ynmenu_wk, wk->heapID) ){
	case 0:	//捨てる
		Snd_SePlay(PORUC_SE_DECIDE);
		YesNoList_DelMsgSet(wk);
		wk->selMode = PCASE_MODE_DEL; 
		return FALSE;
	case BMPMENU_CANCEL: //捨てない
		Snd_SePlay(PORUC_SE_DECIDE);
		BmpTalkWinClear( &wk->win[WIN_MSG], WINDOW_TRANS_ON);		
		wk->selMode = PCASE_MODE_MSEL; 
		return FALSE;
	}
	return FALSE;
}

/**
 *	@brief	ポルトを捨てるメッセージ待ち
 */
static int PoruCaseMode_Del(PORU_CASE_WORK* wk)
{
	if( GF_MSG_PrintEndCheck( wk->msgIdx )){
		return FALSE;
	}
	if((sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)) == 0){
		return FALSE;
	}
	BmpTalkWinClear( &wk->win[WIN_MSG], WINDOW_TRANS_OFF);		
	GF_BGL_BmpWinOff(&wk->win[WIN_MSG]);

	//選択したポルトの削除フラグをOn
	wk->param->list[wk->selectID].del = 1;
	wk->param->ret_mode = 1;	//リストをひとつ詰めるフラグon
	//リスト再生成
	PoruList_DeletePMenu(wk,FALSE);
	PoruList_CreatePMenu(wk);

	//カーソルの色を戻す
	NAct_CursorChg(wk,FALSE);
	wk->selMode = PCASE_MODE_PSEL;
	return FALSE;
}

//=========================================================
//
/**
 *	@brief	ポルトケース　リソース初期化
 */
static int PoruCaseResInit(PORU_CASE_WORK* wk)
{
	switch(wk->sub_seq){
	case 0:
		PoruCase_BGLInit(wk);
		break;
	case 1:
		PoruCase_2DGraInit(wk);
		break;
	case 2:
		PoruCase_MsgManagerGet(wk);
		PoruCase_BmpWinAdd(wk);
		break;
	case 3:
		PoruCase_ActorInit(wk);
		break;
	case 4:
		PoruCase_MakeActor(wk);
		break;
	case 5:
		PoruList_CreatePMenu(wk);
		PoruBtn_StateSet(wk,wk->viewMode,BACT_ST_INI_PUSH);
		sys_VBlankFuncChange(PoruCaseVBlank, wk);
		wk->sub_seq = 0;
		return TRUE;
	}
	wk->sub_seq++;
	return FALSE;
}

/**
 *	@brief	ポルトケース　リソース初期化
 */
static int PoruCaseResRelease(PORU_CASE_WORK* wk)
{
	switch(wk->sub_seq){
	case 0:
		if(wk->mlist != NULL){
			MenuList_Delete(wk);
		}
		PoruList_DeletePMenu(wk,TRUE);
		break;
	case 1:
		PoruCase_DelActor(wk);
		PoruCase_ActorRelease(wk);
		break;
	case 2:
		PoruCase_BmpWinDel(wk);
		PoruCase_MsgManagerRelease(wk);
		break;
	case 3:
		PoruCase_2DGraRelease(wk);
		break;
	case 4:
		PoruCase_BGLRelease(wk);
		break;
	case 5:
		return TRUE;
	}
	wk->sub_seq++;
	return FALSE;
}

/**
 *	@brief	ポルトケースVramBank設定
 */
static void PoruCase_VBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

/**
 *	@brief	ポルトケース　BGL初期化
 */
static void PoruCase_BGLInit(PORU_CASE_WORK* wk)
{
	int i,frame;
	
	//VramBankセット
	PoruCase_VBankSet();

	//BGL初期化
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};
		GF_BGL_InitBG(&BGsys_data);
	}
	
	{
	GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
		{	//MAIN BG0
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//MAIN BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
		{	//MAIN BG2
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
		{	//MAIN BG3
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			3,0,0,FALSE},
		{	//SUB BG0
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//SUB BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
	};
		frame = GF_BGL_FRAME0_M;
		for(i = 0;i < 6;i++){
			GF_BGL_BGControlSet(wk->bgl,frame,&(TextBgCntDat[i]),GF_BGL_MODE_TEXT);
			GF_BGL_ScrClear(wk->bgl,frame);
			GF_BGL_ClearCharSet(frame,32,0,wk->heapID);
			++frame;
		}
	}
}

/**
 *	@brief	ポルトケース　BGL解放
 */
static void PoruCase_BGLRelease(PORU_CASE_WORK* wk)
{
	int i;

	for(i = 0; i <  6;i++){
		GF_BGL_BGControlExit( wk->bgl, i);	
	}
	sys_FreeMemoryEz(wk->bgl);
}

/**
 *	@brief	ポルトケース　BGリソース初期化
 */
static void PoruCase_2DGraInit(PORU_CASE_WORK* wk)
{
	ARCHANDLE* handle;

	//アーカイブハンドル取得
	handle = ArchiveDataHandleOpen(ARC_PORUTO_GRA,wk->heapID);

	//キャラクタ転送
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUTO_GRA,NARC_poru_gra_poru_bg_main_ncgr,
		GF_BGL_FRAME0_M,0,0,0);
	
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUTO_GRA,NARC_poru_gra_poru_bg_sub_ncgr,
		GF_BGL_FRAME1_S,0,0,0);

	//パレット転送
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUTO_GRA,NARC_poru_gra_poru_bg_nclr,
		GF_BGL_FRAME0_M,2,0x20*0x0C,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUTO_GRA,NARC_poru_gra_poru_bg_nclr,
		GF_BGL_FRAME0_S,2,0x20*0x0C,0);

	//スクリーン転送
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUTO_GRA,NARC_poru_gra_poru_bg_main_nscr,
		GF_BGL_FRAME3_M,1,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,
		handle,ARC_PORUTO_GRA,NARC_poru_gra_poru_bg_sub_nscr,
		GF_BGL_FRAME1_S,1,0,0);

	//ハンドル閉じる
	ArchiveDataHandleClose( handle );
	
	//スクリーン転送
	GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME3_M);
	GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME1_S);
}

/**
 *	@brief	ポルトケース　BGリソース初期化
 */
static void PoruCase_2DGraRelease(PORU_CASE_WORK* wk)
{
//	sys_FreeMemoryEz(wk->pScrBuf02);
//	sys_FreeMemoryEz(wk->pScrBuf01);
}

/**
 *	@brief	ポルトケース BMPWIN初期化
 */
static void PoruCase_BmpWinAdd(PORU_CASE_WORK* wk)
{
	int i;
	
	static const struct{
		u8 frm,px,py,sx,sy,pal;
		u16	cgx;
	}windat[] = {
	 { BMPL_PLIST_FRM,BMPL_PLIST_PX,BMPL_PLIST_PY,BMPL_PLIST_SX,BMPL_PLIST_SY,
	   BMPL_PLIST_PAL,BMPL_PLIST_CGX},
//	 { BMPL_PLISTLV_FRM,BMPL_PLISTLV_PX,BMPL_PLISTLV_PY,BMPL_PLISTLV_SX,BMPL_PLISTLV_SY,
//	   BMPL_PLISTLV_PAL,BMPL_PLISTLV_CGX},
	 { BMPL_TASTE_FRM,BMPL_TASTE_PX,BMPL_TASTE_PY,BMPL_TASTE_SX,BMPL_TASTE_SY,
	   BMPL_TASTE_PAL,BMPL_TASTE_CGX},
	 { BMPL_MSG_FRM,BMPL_MSG_PX,BMPL_MSG_PY,BMPL_MSG_SX,BMPL_MSG_SY,
	   BMPL_MSG_PAL,BMPL_MSG_CGX},
	 { BMPL_MSEL_FRM,BMPL_MSEL_PX,BMPL_MSEL_PY,BMPL_MSEL_SX,BMPL_MSEL_SY,
	   BMPL_MSEL_PAL,BMPL_MSEL_CGX},
	 { BMPL_MYN_FRM,BMPL_MYN_PX,BMPL_MYN_PY,BMPL_MYN_SX,BMPL_MYN_SY,
	   BMPL_MYN_PAL,BMPL_MYN_CGX},
	 { BMPL_EXPM_FRM,BMPL_EXPM_PX,BMPL_EXPM_PY,BMPL_EXPM_SX,BMPL_EXPM_SY,
	   BMPL_EXPM_PAL,BMPL_EXPM_CGX},
	 { BMPL_EXPS_FRM,BMPL_EXPS_PX,BMPL_EXPS_PY,BMPL_EXPS_SX,BMPL_EXPS_SY,
	   BMPL_EXPS_PAL,BMPL_EXPS_CGX},
	 { BMPL_SW01_FRM,BMPL_SW01_PX,BMPL_SW01_PY,BMPL_SW01_SX,BMPL_SW01_SY,
	   BMPL_SW01_PAL,BMPL_SW01_CGX},
	 { BMPL_SW02_FRM,BMPL_SW02_PX,BMPL_SW02_PY,BMPL_SW02_SX,BMPL_SW02_SY,
	   BMPL_SW02_PAL,BMPL_SW02_CGX},
	 { BMPL_SW03_FRM,BMPL_SW03_PX,BMPL_SW03_PY,BMPL_SW03_SX,BMPL_SW03_SY,
	   BMPL_SW03_PAL,BMPL_SW03_CGX},
	 { BMPL_SW04_FRM,BMPL_SW04_PX,BMPL_SW04_PY,BMPL_SW04_SX,BMPL_SW04_SY,
	   BMPL_SW04_PAL,BMPL_SW04_CGX},
	 { BMPL_SW05_FRM,BMPL_SW05_PX,BMPL_SW05_PY,BMPL_SW05_SX,BMPL_SW05_SY,
	   BMPL_SW05_PAL,BMPL_SW05_CGX},
	 { BMPL_SW06_FRM,BMPL_SW06_PX,BMPL_SW06_PY,BMPL_SW06_SX,BMPL_SW06_SY,
	   BMPL_SW06_PAL,BMPL_SW06_CGX},
	};
	
	//ウィンドウ用キャラクタ転送
	MenuWinGraphicSet(wk->bgl, BMPL_MENU_WIN_FRM,
		BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, MENU_TYPE_SYSTEM, wk->heapID);
	TalkWinGraphicSet(wk->bgl,BMPL_TALK_WIN_FRM,
		BMPL_TALK_WIN_CGX,BMPL_TALK_WIN_PAL,
		CONFIG_GetWindowType(wk->param->configSave),wk->heapID);
	
	//メニューウィンドウ用フォントパレット転送
	SystemFontPaletteLoad(PALTYPE_MAIN_BG,SYSFONT_PAL*32,wk->heapID);
	TalkFontPaletteLoad(PALTYPE_MAIN_BG,MSGFONT_PAL*32,wk->heapID);
	SystemFontPaletteLoad(PALTYPE_SUB_BG,BTNFONT_PAL*32,wk->heapID);
	
	for(i = 0;i < WIN_MAX;i++){
		GF_BGL_BmpWinAdd(
			wk->bgl, &wk->win[i], windat[i].frm,
			windat[i].px, windat[i].py, windat[i].sx, windat[i].sy, windat[i].pal, windat[i].cgx );
		GF_BGL_BmpWinDataFill(&(wk->win[i]),FBMP_COL_NULL);
	}
	PoruCase_DrawInitialMsg(wk);
}

/**
 *	@brief	ポルトケース　BMPWIN解放
 */
static void PoruCase_BmpWinDel(PORU_CASE_WORK* wk)
{
	int i = 0;

	for(i = 0;i < WIN_MAX;i++){
		GF_BGL_BmpWinOff(&wk->win[i]);
		GF_BGL_BmpWinDel(&wk->win[i]);
	}
}

/**
 *	@brief	ポルトケース　メッセージマネージャ取得
 */
static void PoruCase_MsgManagerGet(PORU_CASE_WORK* wk)
{
	int i = 0;

	//ここでボタンフォントも追加しておく
	FontProc_LoadFont( FONT_BUTTON, wk->heapID );	
	
	wk->msgMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_poruto_select_dat,wk->heapID);
	
	//ポルト名マネージャ取得
	wk->nameMan = PorutoName_CreateManager(wk->heapID);

	wk->msgDat.wset = WORDSET_CreateEx(2,WORDSET_PORU_BUFLEN,wk->heapID);
	
	//デフォルト文字列取得
	wk->msgDat.tmp = STRBUF_Create(WORDSET_PORU_BUFLEN,wk->heapID);
	wk->msgDat.endbuf = MSGMAN_AllocString(wk->msgMan,mes_p_select_04_02);
	wk->msgDat.listbuf = MSGMAN_AllocString(wk->msgMan,msg_p_select_04_03);
	wk->msgDat.tbuf = MSGMAN_AllocString(wk->msgMan,mes_p_select_03_01);
	wk->msgDat.qbuf = MSGMAN_AllocString(wk->msgMan,mes_p_select_05_01);
	wk->msgDat.dbuf = MSGMAN_AllocString(wk->msgMan,mes_p_select_05_02);
	wk->msgDat.sbuf = MSGMAN_AllocString(wk->msgMan,mes_p_select_01_01);

	for(i = 0;i < PVIEW_MAX;i++){
		wk->msgDat.swbuf[i] = MSGMAN_AllocString(wk->msgMan,mes_p_select_07_01+i);
		if(i >= PVIEW_ALL){
			break;
		}
		wk->msgDat.exbuf[i] = MSGMAN_AllocString(wk->msgMan,mes_p_select_08_01+i);
	}

	//メッセージスピード取得
	wk->msgDat.msg_spd = CONFIG_GetMsgPrintSpeed(wk->param->configSave);
}

/**
 *	@brief	ポルトケース　メッセージマネージャ解放
 */
static void PoruCase_MsgManagerRelease(PORU_CASE_WORK* wk)
{
	int i = 0;
	
	for(i = 0;i < PVIEW_MAX;i++){
		STRBUF_Delete(wk->msgDat.swbuf[i]);
		if(i >= PVIEW_ALL){
			break;
		}
		STRBUF_Delete(wk->msgDat.exbuf[i]);
	}
	STRBUF_Delete(wk->msgDat.sbuf);
	STRBUF_Delete(wk->msgDat.dbuf);
	STRBUF_Delete(wk->msgDat.qbuf);
	STRBUF_Delete(wk->msgDat.tbuf);
	STRBUF_Delete(wk->msgDat.listbuf);
	STRBUF_Delete(wk->msgDat.endbuf);
	STRBUF_Delete(wk->msgDat.tmp);

	WORDSET_Delete(wk->msgDat.wset);
	
	PorutoName_ReleaseManager(wk->nameMan);
	MSGMAN_Delete(wk->msgMan);
	
	FontProc_UnloadFont( FONT_BUTTON );	
}

/**
 *	@biref	ポルトケース　アクター初期化
 */
static void PoruCase_MakeActor(PORU_CASE_WORK* wk)
{
	int i;
	
	static const TCATS_OBJECT_ADD_PARAM	ActAddParam[] =
	{
		{	// カーソル
			0,	//ID
			NACT_CUR_PX, NACT_CUR_PY, 0,	//x,y,z
			NACT_CURSOR, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
		{	// 上矢印 
			0,	//ID
			NACT_UP_PX, NACT_UP_PY, 0,	//x,y,z
			NACT_UP, 2, 0, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
		{	// 上矢印 
			0,	//ID
			NACT_DOWN_PX, NACT_DOWN_PY, 0,	//x,y,z
			NACT_DOWN, 2, 0, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
		{	// 味マーク 
			0,	//ID
			10, 100, 0,	//x,y,z
			3, 3, 1, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
		{	// ボタン 
			1,	//ID
			10, 100, 0,	//x,y,z
			0, 1, 2, NNS_G2D_VRAM_TYPE_2DSUB,	//anmNO,pri,pal,d_area
			0, 0, 0, 0	//prm1,prm2,prm3,prm4
		},
	};

	for(i = 0;i < NORMAL_ACTMAX;i++){
		wk->pAct[i] = CATS_ObjectAdd( wk->pActSys,
				wk->pActRes,
				&ActAddParam[i] );

		CLACT_SetDrawFlag(wk->pAct[i], 1 );
	}
	CLACT_SetAnmFlag(wk->pAct[NACT_CURSOR], FALSE);
	CLACT_SetAnmFlag(wk->pAct[NACT_UP], TRUE);
	CLACT_SetAnmFlag(wk->pAct[NACT_DOWN], TRUE);

	for(i = 0;i < FMARK_ACTMAX;i++){
		static const struct{
			u16 x,y;
		}fmark[] = {
		 {40,19*8+4},{6*8+6,20*8+5},{6*8+1,22*8+4},{4*8-1,22*8+4},{3*8+2,20*8+5},
		};
		wk->pActFmk[i] = CATS_ObjectAdd( wk->pActSys,
				wk->pActRes,
				&ActAddParam[3] );
		CLACT_SetDrawFlag(wk->pActFmk[i], 1 );
		CLACT_AnmChg(wk->pActFmk[i],i+3);
		CATS_ObjectPosSet(wk->pActFmk[i],fmark[i].x,fmark[i].y);
		
	}
	for(i = 0;i < BUTTON_ACTMAX;i++){
		static const struct{
			u16 x,y;
		}bmark[] = {
		 {TP_SPICY_NX,TP_SPICY_NY},{TP_ASTR_NX,TP_ASTR_NY},
		 {TP_SWEET_NX,TP_SWEET_NY},{TP_BITTER_NX,TP_BITTER_NY},
		 {TP_SOUR_NX,TP_SOUR_NY},{TP_ALL_NX,TP_ALL_NY}
		};
		wk->pActBtn[i] = CATS_ObjectAdd( wk->pActSys,
				wk->pActRes,
				&ActAddParam[4] );

		CLACT_SetDrawFlag(wk->pActBtn[i], 1 );
		CLACT_AnmChg(wk->pActBtn[i],i*BACT_PTN);
		CLACT_SetAnmFrame(wk->pActBtn[i],FX32_CONST(2));
		CLACT_PaletteNoChg(wk->pActBtn[i],i+2);
		CLACT_SetAnmFlag(wk->pActBtn[i],FALSE);
		CATS_ObjectPosSet(wk->pActBtn[i],bmark[i].x,bmark[i].y);
	}

	//ポルトOAM追加
	wk->pOam = PoruOam_Add(wk->poruMan,0,
		231,76,0,1,0,PORUOAM_VT_MAIN);

	//一旦非表示
	CATS_ObjectEnableCap(wk->pOam->act,FALSE);	
}

/**
 *	@brief	ポルトケース　アクター削除
 */
static void PoruCase_DelActor(PORU_CASE_WORK* wk)
{
	int i;

	PoruOam_Del(wk->poruMan,wk->pOam);

	for(i = 0;i < BUTTON_ACTMAX;i++){
		CATS_ObjectDel(wk->pActBtn[i]);
	}
	for(i = 0;i < FMARK_ACTMAX;i++){
		CATS_ObjectDel(wk->pActFmk[i]);
	}
	for(i =0;i < NORMAL_ACTMAX;i++){
		CATS_ObjectDel(wk->pAct[i]);
	}
}
