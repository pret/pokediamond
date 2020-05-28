#include "common.h"
#include "trcard_obj.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "trainer_case.naix"

#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// 0
#define SUB_LCD		( GF_BGL_SUB_DISP )		// 1

//** CharManager PlttManager用 **//
#define TR_CARD_CHAR_CONT_NUM				(1)
#define TR_CARD_CHAR_VRAMTRANS_MAIN_SIZE	(2048)
#define TR_CARD_CHAR_VRAMTRANS_SUB_SIZE		(0)
#define TR_CARD_PLTT_CONT_NUM				(2)
#define TR_CARD_PALETTE_NUM					(9)	//パレット9本
#define TR_CARD_BADGE_PALETTE_NUM			(4)	//パレット4本

#define BTN_EFF_POS_X	(12*8)
#define BTN_EFF_POS_Y	(17*8)


typedef struct BADGE_POS_tag{
	int x;
	int y;
}BADGE_POS;

//リソースマネージャー登録数テーブル
static const u8 ResEntryNumTbl[RESOURCE_NUM] = {
	1,			//キャラリソース
	2,			//パレットリソース
	1,			//セルリソース
	1,			//セルアニメリソース
};

static const BADGE_POS BadgePos[] = {
	{8*3,8*5},
	{8*10,8*5},
	{8*17,8*5},
	{8*24,8*5},
	{8*3,8*(12-3)},
	{8*10,8*(12-3)},
	{8*17,8*(12-3)},
	{8*24,8*(12-3)},
};

static const BADGE_POS StarPos[] = {
	{8*3,8*5},
	{8*10,8*5},
	{8*17,8*5},
	{8*24,8*5},
	{8*3,8*12},
	{8*10,8*12},
	{8*17,8*12},
	{8*24,8*12},
};

static void InitCharPlttManager(void);

//--------------------------------------------------------------------------------------------
/**
 * セルアクター初期化
 *
 * @param	wk	トレーナーカードOBJワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void InitTRCardCellActor( TR_CARD_OBJ_WORK *wk )
{
	int i;
//	initVramTransferManagerHeap( 32, HEAPID_TR_CARD );
		
	InitCharPlttManager();
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 128,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 128,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			HEAPID_TR_CARD);
	
	// セルアクター初期化
	wk->ClactSet = CLACT_U_SetEasyInit( TR_CARD_ACT_MAX, &wk->RendData, HEAPID_TR_CARD );
	
	//リソースマネージャー初期化
	for(i=0;i<RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, HEAPID_TR_CARD);
	}

	//chara読み込み
	wk->ResObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(
										wk->ResMan[CLACT_U_CHAR_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NCGR,
										FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_TR_CARD);

	//pal読み込み
	wk->ResObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NCLR,
										FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, TR_CARD_PALETTE_NUM, HEAPID_TR_CARD);

	//cell読み込み
	wk->ResObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELL_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NCER,
										FALSE, 1, CLACT_U_CELL_RES, HEAPID_TR_CARD);

	//同じ関数でanim読み込み
	wk->ResObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(
										wk->ResMan[CLACT_U_CELLANM_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge_NANR,
										FALSE, 1, CLACT_U_CELLANM_RES, HEAPID_TR_CARD);
							
	// リソースマネージャーから転送

	// Chara転送
	CLACT_U_CharManagerSet( wk->ResObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSet( wk->ResObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
#if 0
	{
		CLACT_U_RES_OBJ_PTR res_obj_badge_plt;
		//pal読み込み(バッジパレット)
		res_obj_badge_plt = CLACT_U_ResManagerResAddArcPltt(
										wk->ResMan[CLACT_U_PLTT_RES],
										ARC_TR_CASE_GRA, NARC_trainer_case_card_badge2_NCLR,
										FALSE, 2, NNS_G2D_VRAM_TYPE_2DMAIN, TR_CARD_BADGE_PALETTE_NUM, HEAPID_TR_CARD);
		// パレット転送
		CLACT_U_PlttManagerSet( res_obj_badge_plt );
	}
#endif
	{
		u8 i;
		ARCHANDLE* pal_handle;

		const int pal_arc_idx[TR_CARD_BADGE_ACT_MAX] = {
			NARC_trainer_case_card_badge2_0_NCLR,
			NARC_trainer_case_card_badge2_1_NCLR,
			NARC_trainer_case_card_badge2_2_NCLR,
			NARC_trainer_case_card_badge2_3_NCLR,
			NARC_trainer_case_card_badge2_4_NCLR,
			NARC_trainer_case_card_badge2_5_NCLR,
			NARC_trainer_case_card_badge2_6_NCLR,
			NARC_trainer_case_card_badge2_7_NCLR
		};
		//パレットアーカイブハンドルオープン
		pal_handle  = ArchiveDataHandleOpen( ARC_TR_CASE_GRA, HEAPID_TR_CARD);
		for (i=0;i<TR_CARD_BADGE_ACT_MAX;i++){
			wk->PalDataBuf[i] = ArchiveDataLoadAllocByHandle( pal_handle, pal_arc_idx[i], HEAPID_TR_CARD );
			if( wk->PalDataBuf[i] != NULL )
			{
				if( NNS_G2dGetUnpackedPaletteData( wk->PalDataBuf[i], &wk->PalData[i] ) == FALSE ){
					sys_FreeMemoryEz( wk->PalData[i] );
					GF_ASSERT(0);
				}
			}else{
				GF_ASSERT(0);
			}
		}
		//ハンドルクローズ
		ArchiveDataHandleClose( pal_handle );
	}
	
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターをセット
 *
 * @param	
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetTrCardActor( TR_CARD_OBJ_WORK *wk, const u8 *inBadgeDisp )
{
	int i;
	CLACT_HEADER			cl_act_header;
	
	// セルアクターヘッダ作成	
	CLACT_U_MakeHeader(	&cl_act_header,
						1, 1, 1, 1,
						CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
						0, 1,
						wk->ResMan[CLACT_U_CHAR_RES],
						wk->ResMan[CLACT_U_PLTT_RES],
						wk->ResMan[CLACT_U_CELL_RES],
						wk->ResMan[CLACT_U_CELLANM_RES],
						NULL,NULL);

	{
		//登録情報格納
		u8 ofs;
		CLACT_ADD add;

		add.ClActSet	= wk->ClactSet;
		add.ClActHeader	= &cl_act_header;

		add.mat.x		= 0;//FX32_CONST(32) ;
		add.mat.y		= 0;//FX32_CONST(96) ;		//画面は上下連続している
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 2;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_TR_CARD;

		//セルアクター表示開始

		// 下画面(メイン画面)
		//バッジ
		for(i=0;i<TR_CARD_BADGE_ACT_MAX;i++){
			add.mat.x = FX32_ONE * BadgePos[i].x;
			add.mat.y = FX32_ONE * BadgePos[i].y;
			wk->ClActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ClActWork[i],0);
			CLACT_AnmChg( wk->ClActWork[i], i );
			if (!inBadgeDisp[i]){
				CLACT_SetDrawFlag(wk->ClActWork[i], 0);	//非表示
			}
		}
		//キラキラ
		{
			ofs = TR_CARD_BADGE_ACT_MAX;
			for (i=0;i<TR_CARD_STAR_ACT_MAX;i++){
				add.mat.x = FX32_ONE * StarPos[i].x;
				add.mat.y = FX32_ONE * StarPos[i].y;
				add.pri	= 1;
				wk->ClActWork[ofs+i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(wk->ClActWork[ofs+i],1);
				CLACT_AnmChg( wk->ClActWork[ofs+i], 8 );
				CLACT_SetDrawFlag(wk->ClActWork[ofs+i], 0);	//非表示
			}
			ofs += TR_CARD_STAR_ACT_MAX;
			for (i=0;i<TR_CARD_GRATE_STAR_ACT_MAX;i++){
				add.mat.x = FX32_ONE * StarPos[i].x;
				add.mat.y = FX32_ONE * StarPos[i].y;
				add.pri	= 1;
				wk->ClActWork[ofs+i] = CLACT_Add(&add);
				CLACT_SetAnmFlag(wk->ClActWork[ofs+i],1);
				CLACT_AnmChg( wk->ClActWork[ofs+i], 9 );
				CLACT_SetDrawFlag(wk->ClActWork[ofs+i], 0);	//非表示
			}
		}
		ofs += TR_CARD_GRATE_STAR_ACT_MAX;
		//ボタンエフェクト
		{
			cl_act_header.priority = 0;
			add.mat.x = FX32_ONE * BTN_EFF_POS_X;
			add.mat.y = FX32_ONE * BTN_EFF_POS_Y;
			add.pri	= 0;
			wk->ClActWork[ofs] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ClActWork[ofs],0);
			CLACT_AnmChg( wk->ClActWork[ofs], 10 );
			CLACT_SetDrawFlag(wk->ClActWork[ofs], 0);	//非表示;
		}
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * 2Dセルオブジェクト解放
 *
 * @param	wk	オブジェクトワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void RereaseCellObject(TR_CARD_OBJ_WORK *wk)
{
	u8 i;
	//パレット解放
	for(i=0;i<TR_CARD_BADGE_ACT_MAX;i++){
		sys_FreeMemoryEz(wk->PalDataBuf[i]);
	}

	// セルアクターリソース解放

	// キャラ転送マネージャー破棄
	CLACT_U_CharManagerDelete(wk->ResObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);

	// パレット転送マネージャー破棄
	CLACT_U_PlttManagerDelete(wk->ResObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
		
	// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
	for(i=0;i<RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->ResMan[i]);
	}
	// セルアクターセット破棄
	CLACT_DestSet(wk->ClactSet);

	//OAMレンダラー破棄
	REND_OAM_Delete();

	DeleteCharManager();
	DeletePlttManager();

}

//--------------------------------------------------------------------------------------------
/**
 * バッジパレット変更
 *
 * @param	wk			OBJワーク
 * @param	inBadgeNo	バッジナンバー
 * @param	inOalNo		パレット番号
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetBadgePalette( TR_CARD_OBJ_WORK *wk, const u8 inBadgeNo, const u8 inPalNo )
{
	NNSG2dImagePaletteProxy *proxy;
	u32 palette_vram;
	u32 pal_ofs;
	u8 * adr;
	
	GF_ASSERT(inBadgeNo<TR_CARD_BADGE_ACT_MAX);
	GF_ASSERT(inPalNo<=3);
	
///	CLACT_PaletteNoChg( wk->ClActWork[inBadgeNo], inPalNo );

	proxy = CLACT_PaletteProxyGet( wk->ClActWork[inBadgeNo] );
	palette_vram = NNS_G2dGetImagePaletteLocation(proxy, NNS_G2D_VRAM_TYPE_2DMAIN);
	palette_vram += inBadgeNo*(16*2);
	adr = wk->PalData[inBadgeNo]->pRawData;
	DC_FlushRange( &adr[inPalNo*16*2], 16*2 );
	GX_LoadOBJPltt( &adr[inPalNo*16*2], palette_vram, 16*2 );	//32byte 1Palette
}

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
static void InitCharPlttManager(void)
{
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			TR_CARD_CHAR_CONT_NUM,
			TR_CARD_CHAR_VRAMTRANS_MAIN_SIZE,
			TR_CARD_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_TR_CARD
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(TR_CARD_PLTT_CONT_NUM, HEAPID_TR_CARD);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();

//	DellVramTransferManager();
}


