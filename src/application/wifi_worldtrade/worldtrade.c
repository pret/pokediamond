//============================================================================================
/**
 * @file	worldtrade.c
 * @bfief	世界交換メイン処理
 * @author	Akito Mori
 * @date	06.04.16
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
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
#include "application/worldtrade.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "field/fld_bmp.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"
#include "savedata/savedata.h"

#include "wifi/dwc_rap.h"

#include "worldtrade_local.h"
#include "system/pm_overlay.h"



#include "msgdata/msg_ev_win.h"

// SE用定義
#define WORLD_MOVE_SE		(SEQ_SE_DP_SELECT)
#define RECORD_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define RECORD_BS_SE		(SEQ_SE_DP_SELECT)

#define WORLDTRADE_WORDSET_BUFLEN	( 64 )

#define MYDWC_HEAPSIZE		0x20000
#include "worldtrade.naix"			// グラフィックアーカイブ定義
//============================================================================================
//	定数定義
//============================================================================================



//============================================================================================
//	プロトタイプ宣言
//============================================================================================

/*** 関数プロトタイプ ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void InitWork( WORLDTRADE_WORK *wk, PROC *proc );
static void FreeWork( WORLDTRADE_WORK *wk );
static void char_pltt_manager_init(void);
static void InitCellActor(WORLDTRADE_WORK *wk);
static void SetCellActor(WORLDTRADE_WORK *wk);
static void CursorAppearUpDate(WORLDTRADE_WORK *wk, int arrow);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void RecordMessagePrint( WORLDTRADE_WORK *wk, int msgno, int wait );
static void FreeFunc(DWCAllocType name, void* ptr,  u32 size);
static void *AllocFunc( DWCAllocType name, u32   size, int align );
static void InitDpw( void *heapPtr, NNSFndHeapHandle heapHandle, DWCAllocEx alloc, DWCFreeEx free  );
static void InitCLACT( WORLDTRADE_WORK *wk );
static void FreeCLACT( WORLDTRADE_WORK *wk );
static void ServerWaitTimeFunc( WORLDTRADE_WORK *wk );
static void BoxPokeNumGet( WORLDTRADE_WORK *wk );


static NNSFndHeapHandle _wtHeapHandle;


//============================================================================================
//	関数テーブル定義
//============================================================================================

// 世界交換サブプロセス用関数配列定義
static int (*SubProcessTable[][3])(WORLDTRADE_WORK *wk, int seq)={
	{ WorldTrade_Enter_Init,   WorldTrade_Enter_Main,    WorldTrade_Enter_End   },
	{ WorldTrade_Title_Init,   WorldTrade_Title_Main,    WorldTrade_Title_End   },
	{ WorldTrade_MyPoke_Init,  WorldTrade_MyPoke_Main,   WorldTrade_MyPoke_End  },
	{ WorldTrade_Partner_Init, WorldTrade_Partner_Main,  WorldTrade_Partner_End },
	{ WorldTrade_Search_Init,  WorldTrade_Search_Main,   WorldTrade_Search_End  },
	{ WorldTrade_Box_Init,     WorldTrade_Box_Main,      WorldTrade_Box_End     },
	{ WorldTrade_Deposit_Init, WorldTrade_Deposit_Main,  WorldTrade_Deposit_End },
	{ WorldTrade_Upload_Init,  WorldTrade_Upload_Main,   WorldTrade_Upload_End  },
	{ WorldTrade_Status_Init,  WorldTrade_Status_Main,   WorldTrade_Status_End  },
	{ WorldTrade_Demo_Init,    WorldTrade_Demo_Main,     WorldTrade_Demo_End  },
};


WORLDTRADE_WORK *debug_worldtrade;

//============================================================================================
//	プロセス関数
//============================================================================================



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
PROC_RESULT WorldTradeProc_Init( PROC * proc, int * seq )
{
	WORLDTRADE_WORK * wk;
	
	switch(*seq){
	case 0:
#ifdef PM_DEBUG	
		sys_GetHeapFreeSize( HEAPID_BASE_SYSTEM );
		sys_GetHeapFreeSize( HEAPID_BASE_APP );
#endif
		sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );


		// レコードコーナー用ヒープ作成
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WORLDTRADE, 0x70000 );

		wk = PROC_AllocWork( proc, sizeof(WORLDTRADE_WORK), HEAPID_WORLDTRADE );
		memset( wk, 0, sizeof(WORLDTRADE_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WORLDTRADE );
		debug_worldtrade = wk;
		
		// BG SYSTEM
		{	
			GF_BGL_SYS_HEADER BGsys_data = {
				GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
			};
			GF_BGL_InitBG( &BGsys_data );
		}
		
		
		// 文字列マネージャー生成
		wk->WordSet    		 = WORDSET_CreateEx( 11, WORLDTRADE_WORDSET_BUFLEN, HEAPID_WORLDTRADE );
		wk->MsgManager       = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_gtc_dat, HEAPID_WORLDTRADE );
		wk->LobbyMsgManager  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_lobby_dat, HEAPID_WORLDTRADE );
		wk->SystemMsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_system_dat, HEAPID_WORLDTRADE );
		wk->MonsNameManager  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_monsname_dat, HEAPID_WORLDTRADE );

		sys_KeyRepeatSpeedSet( 4, 8 );

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );

//	//	InitTPSystem();						// タッチパネルシステム初期化
//	//	InitTPNoBuff(2);


		// ワーク初期化
		InitWork( wk, proc );

		InitCLACT( wk );

		// サウンドデータロード(フィールド)
		Snd_DataSetByScene( SND_SCENE_FIELD, SEQ_BLD_BLD_GTC, 1 );

		// DWCライブラリ（Wifi）に渡すためのワーク領域を確保
		wk->heapPtr    = sys_AllocMemory(HEAPID_WORLDTRADE, MYDWC_HEAPSIZE + 32);
		wk->heapHandle = NNS_FndCreateExpHeap( (void *)( ((u32)wk->heapPtr + 31) / 32 * 32 ), MYDWC_HEAPSIZE);

		*seq = 1;
		break;
		
	case 1:
		DwcOverlayStart();

		DpwCommonOverlayStart();

		// イクニューモン転送
		CommVRAMDInitialize();


		(*seq) = SEQ_INIT_DPW;
		
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
}

static int debug_pal_no = 0;
static int debug_obj_no = 0;


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

PROC_RESULT WorldTradeProc_Main( PROC * proc, int * seq )
{
	WORLDTRADE_WORK * wk  = PROC_GetWork( proc );

	// 受信強度リンクを反映させる
	DWC_UpdateConnection();

	// Dpw_Tr_Main() だけは例外的にいつでも呼べる
	Dpw_Tr_Main();

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
		if(wk->subprocflag){
			FreeCLACT( wk );
			OS_Printf("OAMシステム臨時解放");
		}
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
			if(wk->subprocflag){
				InitCLACT( wk );
				WorldTrade_SubLcdActorAdd( wk, MyStatus_GetMySex(wk->param->mystatus) );
				WorldTrade_SubLcdMatchObjAppear( wk, wk->SearchResult, 0 );
				WorldTrade_SubLcdBgGraphicSet( wk );
				wk->subprocflag = 0;
				OS_Printf("OAMシステム臨時復帰");
			}
			*seq = (*SubProcessTable[wk->sub_process][2])(wk, *seq);
		}
		break;

	// 世界交換終了処理
	case SEQ_OUT:
		return PROC_RES_FINISH;
		break;
	}
	ServerWaitTimeFunc( wk );
	BoxPokeNumGet( wk );

	if(wk->clactSet!=NULL){
		CLACT_Draw( wk->clactSet );									// セルアクター常駐関数
	}

	return PROC_RES_CONTINUE;
}

#define DEFAULT_NAME_MAX		18

// ダイヤ・パールで変わるんだろう
#define MALE_NAME_START			0
#define FEMALE_NAME_START		18

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
PROC_RESULT WorldTradeProc_End( PROC * proc, int * seq )
{
	WORLDTRADE_WORK  *wk    = PROC_GetWork( proc );
	int i;

	sys_FreeMemoryEz( wk->heapPtr );

	DpwCommonOverlayEnd();
	DwcOverlayEnd();

	// セルアクターリソース解放
	FreeCLACT( wk );


	// タッチパネルシステム終了
//	StopTP();							


	// メッセージマネージャー・ワードセットマネージャー解放
	
	MSGMAN_Delete( wk->MonsNameManager );
	MSGMAN_Delete( wk->SystemMsgManager );
	MSGMAN_Delete( wk->LobbyMsgManager );
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	// ワーク解放
	FreeWork( wk );

	// イクニューモン解放
	CommVRAMDFinalize();


	// BG_SYSTEM解放
	sys_FreeMemoryEz( wk->bgl   );

	// 世界交換パラメータ解放
	sys_FreeMemoryEz( wk->param );

	PROC_FreeWork( proc );				// PROCワーク開放

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_WORLDTRADE );

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
	WORLDTRADE_WORK *wk = work;
	// VBlank中転送ファンクション実行
	if(wk->vfunc){
	  wk->vfunc(work);
	  wk->vfunc = NULL;
	}
  
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
 * @param   wk		WORLDTRADE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( WORLDTRADE_WORK *wk, PROC *proc )
{
	// 呼び出し時のパラメータを取得
	wk->param = (WORLDTRADE_PARAM*)PROC_GetParentWork( proc );

	wk->sub_process 	= WORLDTRADE_ENTER;
		WorldTrade_SubProcessChange( wk, WORLDTRADE_ENTER, 0 );
	wk->TitleCursorPos  = 0;

	wk->Search.characterNo 		 = 0;
	wk->Search.gender      		 = PARA_UNK+1;
	wk->Search.level_min   		 = 0;
	wk->Search.level_max   		 = 0;
	wk->SearchBackup.characterNo = 0;
	wk->demo_end           		 = 0;
	wk->BoxTrayNo		   		 = 18;
	wk->boxPokeNum			 	 = 0;
	wk->boxSearchFlag			 = 0;
	wk->SubLcdTouchOK			 = 0;
	wk->timeWaitWork             = NULL;
	
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
static void FreeWork( WORLDTRADE_WORK *wk )
{
	

}





//** CharManager PlttManager用 **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)

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
			RECORD_CHAR_CONT_NUM,
			RECORD_CHAR_VRAMTRANS_MAIN_SIZE,
			RECORD_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_WORLDTRADE
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(RECORD_PLTT_CONT_NUM, HEAPID_WORLDTRADE);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();
}


#define TRANS_POKEICON_COLOR_NUM	( 3*16 )
//------------------------------------------------------------------
/**
 * レーダー画面用セルアクター初期化
 *
 * @param   wk		レーダー構造体のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(WORLDTRADE_WORK *wk)
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
			HEAPID_WORLDTRADE);
	
	
	
	// セルアクター初期化
	wk->clactSet = CLACT_U_SetEasyInit( 72+6, &wk->renddata, HEAPID_WORLDTRADE );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//リソースマネージャー初期化
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->resMan[i] = CLACT_U_ResManagerInit(3, i, HEAPID_WORLDTRADE);
	}


	//---------上画面用-------------------
	//chara読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
			ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_WORLDTRADE);

	//pal読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 3, HEAPID_WORLDTRADE);

	//cell読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_WORLDTRADE);

	//同じ関数でanim読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_WORLDTRADE);


	//---------下画面用-------------------


	//chara読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_WORLDTRADE);

	//pal読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 9, HEAPID_WORLDTRADE);

	//cell読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_s_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_WORLDTRADE);

	//同じ関数でanim読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_s_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_WORLDTRADE);
	// リソースマネージャーから転送

	// Chara転送
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );
//	CLACT_U_CharManagerSet( wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );
//	CLACT_U_PlttManagerSet( wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES] );

	// ポケモンアイコン用パレットを一気に読み込んでVRAM転送する
	// ポケモンアイコンのパレットを暗くしたデータも作成して転送する
	{
		void              *buf;
		NNSG2dPaletteData *palData;
		int i,r,g,b;
		u16 *pal;
		
//		ArcUtil_PalSet( ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_MAIN_OBJ, POKEICON_PAL_OFFSET*0x20, 0, HEAPID_WORLDTRADE );
	
		buf = ArcUtil_PalDataGet( ARC_POKEICON, PokeIconPalArcIndexGet(), &palData, HEAPID_WORLDTRADE );
		DC_FlushRange( palData->pRawData, TRANS_POKEICON_COLOR_NUM*2 );
		GX_LoadOBJPltt( palData->pRawData, POKEICON_PAL_OFFSET*0x20, TRANS_POKEICON_COLOR_NUM*2 );
		
		pal = (u16*)palData->pRawData;
		for(i=0;i<TRANS_POKEICON_COLOR_NUM;i++){
			r = pal[i]>>10&0x1f;
			g = (pal[i]>>5)&0x1f;
			b = pal[i]&0x1f;

			r /=2;	g /= 2; b /=2;
			pal[i] = (r<<10)|(g<<5)|b;
		}

		DC_FlushRange( palData->pRawData, TRANS_POKEICON_COLOR_NUM*2 );
		GX_LoadOBJPltt( palData->pRawData, (POKEICON_PAL_OFFSET+3)*0x20, TRANS_POKEICON_COLOR_NUM*2 );

		sys_FreeMemoryEz(buf);
	}
}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

#define TRAINER_NAME_WIN_X		(  3 )
#define TRAINER1_NAME_WIN_Y		(  6 )
#define TRAINER2_NAME_WIN_Y		(  7 )

static const u16 obj_pos_tbl[][2]={
	{212,64},
	{187,77},
	{236,77},
	{194,120},
	{224,120},
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
void WorldTrade_MakeCLACT( CLACT_ADD *add, WORLDTRADE_WORK *wk, CLACT_HEADER *header, int param)
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
	add->heap		= HEAPID_WORLDTRADE;

}

//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			WORLDTRADE_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(WORLDTRADE_WORK *wk)
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
	
	// セルアクターヘッダ作成
	CLACT_U_MakeHeader(&wk->clActHeader_sub, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//メイン画面OBJ面ＯＮ
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//サブ画面OBJ面ＯＮ
	
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
BMPMENU_WORK *WorldTrade_BmpWinYesNoMake( GF_BGL_INI *bgl, int y, int yesno_bmp_cgx )
{
	BMPWIN_DAT yesnowin;

	yesnowin        = YesNoBmpWin;
	yesnowin.pos_y  = y;
	yesnowin.chrnum = yesno_bmp_cgx;

	return BmpYesNoSelectInit( bgl, &yesnowin, WORLDTRADE_MENUFRAME_CHR, WORLDTRADE_MENUFRAME_PAL, HEAPID_WORLDTRADE );
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
void WorldTrade_SetNextSeq( WORLDTRADE_WORK *wk, int to_seq, int next_seq )
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
void WorldTrade_SetNextProcess( WORLDTRADE_WORK *wk, int next_process )
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
void WorldTrade_ActPos( CLACT_WORK_PTR act, int x, int y )
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
int WorldTrade_WifiLinkLevel( void )
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
void WorldTrade_SubProcessChange( WORLDTRADE_WORK *wk, int subprccess, int mode )
{
	wk->sub_nextprocess  = subprccess;
	wk->sub_process_mode = mode;
}


//==============================================================================
/**
 * @brief   次のサブプロセスへ遷移する（一つ前を取っておく）
 *
 * @param   wk		
 *
 * @retval  none	
 */
//==============================================================================
void WorldTrade_SubProcessUpdate( WORLDTRADE_WORK *wk )
{
	wk->old_sub_process = wk->sub_process;
	wk->sub_process     = wk->sub_nextprocess;
	
}
//==============================================================================
/**
 * @brief   会話スピードをコンフィグデータから取得する
 *
 * @param   wk		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_GetTalkSpeed( WORLDTRADE_WORK *wk )
{
	return CONFIG_GetMsgPrintSpeed(wk->param->config);
}

//==============================================================================
/**
 * @brief   会話ウインドウの形状をコンフィグデータから取得する
 *
 * @param   wk		
 *
 * @retval  WINTYPE		
 */
//==============================================================================
WINTYPE WorldTrade_GetMesWinType( WORLDTRADE_WORK *wk )
{
	return CONFIG_GetWindowType( wk->param->config );
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
static void InitCLACT( WORLDTRADE_WORK *wk )
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
	sys_VBlankFuncChange( VBlankFunc, wk );
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
static void FreeCLACT( WORLDTRADE_WORK *wk )
{
	int i;

	// ユニオンＯＢＪグラフィックデータ解放
	FreeFieldObjData( wk );

	// キャラ転送マネージャー破棄
	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);
//	CLACT_U_CharManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES]);

	// パレット転送マネージャー破棄
	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
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


//------------------------------------------------------------------
/**
 * @brief   0になるまで１減らす
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ServerWaitTimeFunc( WORLDTRADE_WORK *wk )
{
	
	if(wk->serverWaitTime){
		wk->serverWaitTime--;
	}
}

//==============================================================================
/**
 * @brief   １syncに１トレイずつBOXの数を確認していくスタート
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_BoxPokeNumGetStart( WORLDTRADE_WORK *wk )
{
	wk->boxSearchFlag = 1;
	wk->boxPokeNum    = 0;
}


//------------------------------------------------------------------
/**
 * @brief   １syncに１トレイずつBOXの数を確認していく(常駐処理）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BoxPokeNumGet( WORLDTRADE_WORK *wk )
{
	if(wk->boxSearchFlag){
		wk->boxPokeNum += BOXDAT_GetPokeExistCount( wk->param->mybox, wk->boxSearchFlag-1 );
		wk->boxSearchFlag++;
		if(wk->boxSearchFlag==19){
			wk->boxSearchFlag = 0;
			OS_Printf("BOX総数は%d\n",wk->boxPokeNum);
		}

	}

}



//------------------------------------------------------------------
/**
 * @brief   時間アイコン追加
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WorldTrade_TimeIconAdd( WORLDTRADE_WORK *wk )
{
	wk->timeWaitWork = TimeWaitIconAdd( &wk->MsgWin, WORLDTRADE_MESFRAME_CHR );
}

//------------------------------------------------------------------
/**
 * @brief   時間アイコン消去（NULLチェックする）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WorldTrade_TimeIconDel( WORLDTRADE_WORK *wk )
{
	if(wk->timeWaitWork!=NULL){
		TimeWaitIconDel(wk->timeWaitWork);
		wk->timeWaitWork = NULL;
	}
}













