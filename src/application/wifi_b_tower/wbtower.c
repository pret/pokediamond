//============================================================================================
/**
 * @file	wbtower.c
 * @bfief	WIFIバトルタワー処理
 * @author	Akito Mori
 * @date	06.05.15
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_bt.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/pms_data.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_wifi_lobby.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/gf_date.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"


#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"

#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "system/bmp_menu.h"
#include "application/wbtower.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/wm_icon.h"
#include "field/fld_bmp.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"
#include "savedata/savedata.h"

#include "wifi/dwc_rap.h"

#include "wbtower_local.h"
#include "system/pm_overlay.h"



#include "msgdata/msg_ev_win.h"
#include "msgdata/msg_trname.h"

// SE用定義
#define WORLD_MOVE_SE		(SEQ_SE_DP_SELECT)
#define RECORD_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define RECORD_BS_SE		(SEQ_SE_DP_SELECT)


#define MYDWC_HEAPSIZE		0x20000
#include "../wifi_worldtrade/worldtrade.naix"			// グラフィックアーカイブ定義
//============================================================================================
//	定数定義
//============================================================================================



//============================================================================================
//	プロトタイプ宣言
//============================================================================================

/*** 関数プロトタイプ ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void InitWork( WBTOWER_WORK *wk, PROC *proc );
static void FreeWork( WBTOWER_WORK *wk );
static void char_pltt_manager_init(void);
static void InitCellActor(WBTOWER_WORK *wk);
static void SetCellActor(WBTOWER_WORK *wk);
static void CursorAppearUpDate(WBTOWER_WORK *wk, int arrow);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void RecordMessagePrint( WBTOWER_WORK *wk, int msgno, int wait );
static void FreeFunc(DWCAllocType name, void* ptr,  u32 size);
static void *AllocFunc( DWCAllocType name, u32   size, int align );
static void InitDpw( void *heapPtr, NNSFndHeapHandle heapHandle, DWCAllocEx alloc, DWCFreeEx free  );
static void InitCLACT( WBTOWER_WORK *wk );
static void FreeCLACT( WBTOWER_WORK *wk );


static NNSFndHeapHandle _wtHeapHandle;


//============================================================================================
//	関数テーブル定義
//============================================================================================

// 世界交換サブプロセス用関数配列定義
static int (*SubProcessTable[][3])(WBTOWER_WORK *wk, int seq)={
	{ WBTower_EnterInit,   WBTower_EnterMain,    WBTower_EnterEnd   },
//	{ WBTower_Upload_Init,  WBTower_Upload_Main,   WBTower_Upload_End  },
};


WBTOWER_WORK *debug_wbtower;

//============================================================================================
//	プロセス関数
//============================================================================================

#if 0


typedef struct {
	Dpw_Bt_Leader leader[30];
}TEST_BT_LEADER;

TEST_BT_LEADER TestBtLeader;

static void TestLeaderDataMake( TEST_BT_LEADER *leader )
{
	MSGDATA_MANAGER *msgman;
	STRBUF *name;
	int i;

	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trname_dat, HEAPID_WIFI_BATTLETOWER );

	for(i=0;i<30;i++){
		name = MSGMAN_AllocString( msgman, TR_TANPAN_01+i );
		STRBUF_GetStringCode( name, leader->leader[i].playerName,  6 );
		STRBUF_Delete(name);

		leader->leader[i].versionCode = PM_VERSION;
		leader->leader[i].langCode    = PM_LANG;
		leader->leader[i].countryCode = 0;
		leader->leader[i].localCode   = 0;
		leader->leader[i].playerId[0] = i+32;
		leader->leader[i].playerId[1] = 78;
		leader->leader[i].playerId[2] = 0;
		leader->leader[i].playerId[3] = 0;

		PMSDAT_Init( (PMS_DATA*)leader->leader[i].leaderMessage, PMS_TYPE_BATTLE_WON );
		
		TestBtLeader.leader[i].gender      = 0;

	}
	MSGMAN_Delete( msgman );

	OS_Printf("testbtleader size=%d\n", sizeof(TEST_BT_LEADER));

}
#endif

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT WBTowerProc_Init( PROC * proc, int * seq )
{
	WBTOWER_WORK * wk;
	
	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );


		// レコードコーナー用ヒープ作成
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFI_BATTLETOWER, 0x50000 );

		wk = PROC_AllocWork( proc, sizeof(WBTOWER_WORK), HEAPID_WIFI_BATTLETOWER );
		memset( wk, 0, sizeof(WBTOWER_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WIFI_BATTLETOWER );
		debug_wbtower = wk;
		
		// BG SYSTEM
		{	
			GF_BGL_SYS_HEADER BGsys_data = {
				GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
			};
			GF_BGL_InitBG( &BGsys_data );
		}
		
		
		// 文字列マネージャー生成
		wk->WordSet    		 = WORDSET_CreateEx( 11, WORDSET_DEFAULT_BUFLEN, HEAPID_WIFI_BATTLETOWER );
		wk->MsgManager       = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_bt_dat, HEAPID_WIFI_BATTLETOWER );
		wk->LobbyMsgManager  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_lobby_dat, HEAPID_WIFI_BATTLETOWER );
		wk->SystemMsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_system_dat, HEAPID_WIFI_BATTLETOWER );

		sys_KeyRepeatSpeedSet( 4, 8 );

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );

//	//	InitTPSystem();						// タッチパネルシステム初期化
//	//	InitTPNoBuff(2);


		// ワーク初期化
		InitWork( wk, proc );

		InitCLACT( wk );

		// サウンドデータロード(名前入力)(BGM引継ぎ)
		Snd_DataSetByScene( SND_SCENE_SUB_NAMEIN, 0, 0 );

		// DWCライブラリ（Wifi）に渡すためのワーク領域を確保
		wk->heapPtr    = sys_AllocMemory(HEAPID_WIFI_BATTLETOWER, MYDWC_HEAPSIZE + 32);
		wk->heapHandle = NNS_FndCreateExpHeap( (void *)( ((u32)wk->heapPtr + 31) / 32 * 32 ), MYDWC_HEAPSIZE);

		*seq = 1;
		break;
		
	case 1:
		DwcOverlayStart();

		DpwCommonOverlayStart();

		// イクニューモン転送
		CommVRAMDInitialize();


		(*seq) = SEQ_INIT_DPW;
		
//		TestLeaderDataMake( &TestBtLeader );
		
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------

PROC_RESULT WBTowerProc_Main( PROC * proc, int * seq )
{
	WBTOWER_WORK * wk  = PROC_GetWork( proc );
	int update;

	// 受信強度アイコン反映
	DWC_UpdateConnection();

	// 常駐関数呼び出し
	Dpw_Bt_Main();

	// Wifi受信強度反映
	DWC_UpdateConnection();

	switch( *seq ){
	// サブ処理初期化
	case SEQ_INIT_DPW:
//		InitDpw(wk->heapPtr, wk->heapHandle, AllocFunc, FreeFunc );
		if(CommIsVRAMDInitialize()){
			_wtHeapHandle = wk->heapHandle;
	

			// wifiメモリ管理関数呼び出し
			DWC_SetMemFunc( AllocFunc, FreeFunc );

			*seq = SEQ_INIT;
		}
		break;
	case SEQ_INIT:
		*seq = (*SubProcessTable[wk->sub_process][0])(wk, *seq);
		break;

	// サブ処理フェードイン待ち
	case SEQ_FADEIN:
		if( WIPE_SYS_EndCheck() ){
			*seq = SEQ_MAIN;
		}
		break;

	// サブ処理メイン
	case SEQ_MAIN:
		*seq = (*SubProcessTable[wk->sub_process][1])(wk, *seq);

		break;

	// サブ処理フェードアウト待ち
	case SEQ_FADEOUT:
		if( WIPE_SYS_EndCheck() ){
			// サブ処理解放(SEQ_INITに行くか、SEQ_OUTにいくかはおまかせ）
			*seq = (*SubProcessTable[wk->sub_process][2])(wk, *seq);
		}
		break;

	// 世界交換終了処理
	case SEQ_OUT:
		return PROC_RES_FINISH;
		break;
	}
	if(wk->clactSet!=NULL){
		CLACT_Draw( wk->clactSet );									// セルアクター常駐関数
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT WBTowerProc_End( PROC * proc, int * seq )
{
	WBTOWER_WORK  *wk    = PROC_GetWork( proc );
	int i;

	sys_FreeMemoryEz( wk->heapPtr );

	DpwCommonOverlayEnd();
	DwcOverlayEnd();

	// セルアクターリソース解放
	FreeCLACT( wk );


	// タッチパネルシステム終了
//	StopTP();							


	// メッセージマネージャー・ワードセットマネージャー解放
	
	MSGMAN_Delete( wk->SystemMsgManager );
	MSGMAN_Delete( wk->LobbyMsgManager );
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	// ワーク解放
	FreeWork( wk );

	// イクニューモン解放
	CommVRAMDFinalize();


	// BG_SYSTEM解放
	sys_FreeMemoryEz( wk->bgl );

	PROC_FreeWork( proc );				// PROCワーク開放

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_WIFI_BATTLETOWER );

	OS_Printf("バトルタワー結果 = %d\n",wk->param->result);

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * VBlank関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankFunc( void * work )
{
	// セルアクターVram転送マネージャー実行
	DoVramTransferManager();

	// レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//--------------------------------------------------------------------------------------------
/**
 * VRAM設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット

		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット

		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_0_B,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &tbl );

}




//------------------------------------------------------------------
/**
 * 世界交換ワーク初期化
 *
 * @param   wk		WBTOWER_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( WBTOWER_WORK *wk, PROC *proc )
{
	// 呼び出し時のパラメータを取得
	wk->param = (WBTOWER_PARAM*)PROC_GetParentWork( proc );

	wk->sub_process 	= WBTOWER_ENTER;
	WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );

}

//------------------------------------------------------------------
/**
 * $brief   ワーク解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( WBTOWER_WORK *wk )
{
	

}





//** CharManager PlttManager用 **//
#define WBTOWER_CHAR_CONT_NUM				(20)
#define WBTOWER_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define WBTOWER_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define WBTOWER_PLTT_CONT_NUM				(20)

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
static void char_pltt_manager_init(void)
{
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			WBTOWER_CHAR_CONT_NUM,
			WBTOWER_CHAR_VRAMTRANS_MAIN_SIZE,
			WBTOWER_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_WIFI_BATTLETOWER
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(WBTOWER_PLTT_CONT_NUM, HEAPID_WIFI_BATTLETOWER);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * レーダー画面用セルアクター初期化
 *
 * @param   wk		レーダー構造体のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(WBTOWER_WORK *wk)
{
	int i;
	
	
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 126,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 126,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			HEAPID_WIFI_BATTLETOWER);
	
	
	
	// セルアクター初期化
	wk->clactSet = CLACT_U_SetEasyInit( 10, &wk->renddata, HEAPID_WIFI_BATTLETOWER );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, WBTOWER_SUB_ACTOR_DISTANCE );

	
	//リソースマネージャー初期化
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_WIFI_BATTLETOWER);
	}


	//---------上画面用-------------------
	//chara読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
			ARC_WORLDTRADE_GRA, NARC_worldtrade_btower_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_WIFI_BATTLETOWER);

	//pal読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 3, HEAPID_WIFI_BATTLETOWER);

	//cell読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_btower_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_WIFI_BATTLETOWER);

	//同じ関数でanim読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_btower_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_WIFI_BATTLETOWER);


	//---------下画面用-------------------

/*
	//chara読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_WIFI_BATTLETOWER);

	//pal読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 9, HEAPID_WIFI_BATTLETOWER);

	//cell読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_s_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_WIFI_BATTLETOWER);

	//同じ関数でanim読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_s_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_WIFI_BATTLETOWER);
	// リソースマネージャーから転送
*/
	// Chara転送
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
//	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
//	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

	

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

#define TRAINER_NAME_WIN_X		(  3 )
#define TRAINER1_NAME_WIN_Y		(  6 )
#define TRAINER2_NAME_WIN_Y		(  7 )

static const u16 arrowtable[][2]={
	{ 232-8, 112-1    },
	{ 232-8, 112+16+1 },
};



//==============================================================================
/**
 * $brief   セルアクターヘッダ作成ルーチン
 *
 * @param   wk		
 * @param   add		
 * @param   param		
 *
 * @retval  none		
 */
//==============================================================================
void WBTower_MakeCLACT( CLACT_ADD *add, WBTOWER_WORK *wk, CLACT_HEADER *header, int param)
{
	add->ClActSet	  = wk->clactSet;
	add->ClActHeader  = header;

	add->mat.z		= 0;
	add->sca.x		= FX32_ONE;
	add->sca.y		= FX32_ONE;
	add->sca.z		= FX32_ONE;
	add->rot		= 0;
	add->pri		= 1;
	add->DrawArea	= param;
	add->heap		= HEAPID_WIFI_BATTLETOWER;

}

//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			WBTOWER_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(WBTOWER_WORK *wk)
{
	int i;
	// セルアクターヘッダ作成
	CLACT_U_MakeHeader(&wk->clActHeader_main, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
	//まだ何も転送していないから

#if 0	
	// セルアクターヘッダ作成
	CLACT_U_MakeHeader(&wk->clActHeader_sub, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
#endif


	{
		//登録情報格納
		CLACT_ADD add;
		WBTower_MakeCLACT( &add, wk, &wk->clActHeader_main, NNS_G2D_VRAM_TYPE_2DMAIN );

		//セルアクター表示開始
		// 矢印２つ
		for(i=0;i<2;i++){
			add.mat.x = FX32_ONE *   arrowtable[i][0];
			add.mat.y = FX32_ONE *   arrowtable[i][1];
			wk->ArrowActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ArrowActWork[i],1);
			CLACT_AnmChg( wk->ArrowActWork[i], i );
			CLACT_SetDrawFlag( wk->ArrowActWork[i], 0 );
		}

	}	
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//メイン画面OBJ面ＯＮ
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//サブ画面OBJ面ＯＮ
	

	WirelessIconEasy();
}



// はい・いいえ
#define	BMP_YESNO_PX	( 23 )
#define	BMP_YESNO_PY	( 13 )
#define	BMP_YESNO_SX	( 7 )
#define	BMP_YESNO_SY	( 4 )
#define	BMP_YESNO_PAL	( 13 )

// はい・いいえ(ウインドウ用）
static const BMPWIN_DAT YesNoBmpWin = {
	GF_BGL_FRAME0_M, BMP_YESNO_PX, BMP_YESNO_PY,
	BMP_YESNO_SX, BMP_YESNO_SY, BMP_YESNO_PAL, 
	0, //後で指定する
};


//==============================================================================
/**
 * $brief   はい・いいえウインドウ登録
 *
 * @param   bgl		
 * @param   menuframe		
 * @param   y		
 * @param   yesno_bmp_cgx		
 *
 * @retval  BMPMENU_WORK *		
 */
//==============================================================================
BMPMENU_WORK *WBTower_BmpWinYesNoMake( GF_BGL_INI *bgl, int y, int yesno_bmp_cgx )
{
	BMPWIN_DAT yesnowin;

	yesnowin        = YesNoBmpWin;
	yesnowin.pos_y  = y;
	yesnowin.chrnum = yesno_bmp_cgx;

	return BmpYesNoSelectInit( bgl, &yesnowin, WBTOWER_MENUFRAME_CHR, WBTOWER_MENUFRAME_PAL, HEAPID_WIFI_BATTLETOWER );
}



//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 * @param   to_seq		
 * @param   next_seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WBTower_SetNextSeq( WBTOWER_WORK *wk, int to_seq, int next_seq )
{
	wk->subprocess_seq      = to_seq;
	wk->subprocess_nextseq  = next_seq;
}

//------------------------------------------------------------------
/**
 * $brief   サブプロセス終了時の次の行き先を入力する
 *
 * @param   wk		
 * @param   to_seq		
 * @param   next_seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WBTower_SetNextProcess( WBTOWER_WORK *wk, int next_process )
{
	wk->sub_nextprocess = next_process;
}

//==============================================================================
/**
 * $brief   CLACTの座標変更
 *
 * @param   act		アクターのポインタ
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//==============================================================================
void WBTower_ActPos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x );
	mat.y = FX32_CONST( y );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}


/*---------------------------------------------------------------------------*
  メモリ確保関数
 *---------------------------------------------------------------------------*/
static void *AllocFunc( DWCAllocType name, u32   size, int align )
{
#pragma unused( name )
    void * ptr;
    OSIntrMode old;
    old = OS_DisableInterrupts();
    ptr = NNS_FndAllocFromExpHeapEx( _wtHeapHandle, size, align );
    OS_RestoreInterrupts( old );
    if(ptr == NULL){
	}
	
    return ptr;
}

/*---------------------------------------------------------------------------*
  メモリ開放関数
 *---------------------------------------------------------------------------*/
static void FreeFunc(DWCAllocType name, void* ptr,  u32 size)
{
#pragma unused( name, size )
    OSIntrMode old;

    if ( !ptr ) return;
    old = OS_DisableInterrupts();
    NNS_FndFreeToExpHeap( _wtHeapHandle, ptr );
    OS_RestoreInterrupts( old );
}



//------------------------------------------------------------------
/**
 * $brief   NitroDpw_Tr初期化
 *
 * @param   heapPtr		
 * @param   headHandle		
 * @param   alloc		
 * @param   free		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitDpw( void *heapPtr, NNSFndHeapHandle heapHandle, DWCAllocEx alloc, DWCFreeEx free  )
{
	

	_wtHeapHandle = heapHandle;
	
	// イクニューモン転送
//	CommVRAMDInitialize();

	// wifiメモリ管理関数呼び出し
	DWC_SetMemFunc( alloc, free );


}






//==============================================================================
/**
 * $brief   WIFI接続状況取得
 *
 * @param   none		
 *
 * @retval  int		
 */
//==============================================================================
int WBTower_WifiLinkLevel( void )
{
    return WM_LINK_LEVEL_3 - DWC_GetLinkLevel();
}




//==============================================================================
/**
 * @brief   サブプロセスモードの切り替え指定
 *
 * @param   wk			
 * @param   subprccess	
 * @param   mode		
 *
 * @retval  none		
 */
//==============================================================================
void WBTower_SubProcessChange( WBTOWER_WORK *wk, int subprccess, int mode )
{
	wk->sub_nextprocess  = subprccess;
	wk->sub_process_mode = mode;
}
















//------------------------------------------------------------------
/**
 * @brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCLACT( WBTOWER_WORK *wk )
{

	// VRAM バンク設定
	VramBankSet();

	// OBJキャラ、パレットマネージャー初期化
	char_pltt_manager_init();

	// CellActorシステム初期化
	InitCellActor(wk);
		
	// CellActro表示登録
	SetCellActor(wk);


	// VBlank関数セット
	sys_VBlankFuncChange( VBlankFunc, NULL );	
}

//------------------------------------------------------------------
/**
 * @brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeCLACT( WBTOWER_WORK *wk )
{
	int i;
	// キャラ転送マネージャー破棄
	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
//	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);
//	CLACT_U_CharManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES]);

	// パレット転送マネージャー破棄
	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES]);
		
	// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
	for(i=0;i<CLACT_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->resMan[i]);
	}
	// セルアクターセット破棄
	CLACT_DestSet(wk->clactSet);
	wk->clactSet = NULL;

	//OAMレンダラー破棄
	REND_OAM_Delete();

	// リソース解放
	DeleteCharManager();
	DeletePlttManager();

}




















