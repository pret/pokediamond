/**
 *	@file	townmap.c
 *	@brief	ワールドマップモジュール　メイン
 *	@outhor	Miyuki Iwasawa
 *	@date	05.09.07
 */
#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/brightness.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/wipe.h"
#include "system/buflen.h"
#include "gflib/touchpanel.h"
#include "field/field_matrix.h"
#include "field/field_place_name.h"
#include "application/app_tool.h"
#include "application/townmap.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_place_name.h"
#include "msgdata/msg_townmap.h"
#include "tmap.h"
#include "tmap_act.h"
#include "tmap_snd_def.h"

#define OSP_TMAP_HEAP_SIZE	0	//ヒープ使用状況OSプリント有効

//================================================================
///データ型定義エリア
//================================================================
enum{
 MSEQ_MAININIT,
 MSEQ_SUBINIT,
 MSEQ_FADEIN,
 MSEQ_FADEINWAIT,
 MSEQ_MAIN,
 MSEQ_FADEOUT,
 MSEQ_FADEOUTWAIT,
 MSEQ_PROC_END,
 MSEQ_END,
};

//プロトタイプ宣言　グローバル
//================================================================
///メイン呼び出し

//プロトタイプ宣言　ローカル
//================================================================
///オーバーレイプロセス
PROC_RESULT TMapProc_Init( PROC *proc,int *seq);
PROC_RESULT TMapProc_Main( PROC *proc,int *seq);
PROC_RESULT TMapProc_End( PROC *proc,int *seq);

///VBlank関連
static void TMapVBlank(void * work);
///VRAMバンク定義
static void TMapVramBankSet(void);
///プロセス
static int TMapInitCommon(TMAP_MAIN_DAT* wk);
static void TMapBGLSet(TMAP_MAIN_DAT* wk,GF_BGL_INI *ini);
static void TMapBgGrapSet(TMAP_MAIN_DAT* wk);
static void TMapBgGrapRelease(TMAP_MAIN_DAT* wk);
static void TMapEndCommon(TMAP_MAIN_DAT* wk);
static void TMapMainDraw(TMAP_MAIN_DAT* wk);


static int TMapSeq_MainInit(TMAP_MAIN_DAT* wk);
static int TMapSeq_SubInit(TMAP_MAIN_DAT* wk);
static int TMapSeq_FadeInWait(TMAP_MAIN_DAT* wk);
static int TMapSeq_Main(TMAP_MAIN_DAT* wk);
static int TMapSeq_FadeOutWait(TMAP_MAIN_DAT* wk);
static int TMapSeq_End(TMAP_MAIN_DAT* wk);

//================================================================
///データ定義エリア
//================================================================

///モード別制御関数定義
extern int	TMapNormal_Init(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Build(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_FadeInSet(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_FadeOutSet(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_KeyIn(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Main(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Draw(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_Release(TMAP_MAIN_DAT* pMain);
extern int	TMapNormal_VBlank(TMAP_MAIN_DAT* pMain);
extern int	TMapJump_KeyIn(TMAP_MAIN_DAT* pMain);

extern int	TMapBG_FadeInSet(TMAP_MAIN_DAT* pMain);
extern int	TMapBG_FadeOutSet(TMAP_MAIN_DAT* pMain);
extern int	TMapBG_KeyIn(TMAP_MAIN_DAT* pMain);

const TMAP_SUB_PROC TMapSubProcData[TMAP_MODE_MAX] = {
 {
	TMapNormal_Init,
	TMapNormal_Build,
	TMapNormal_FadeInSet,
	TMapNormal_FadeOutSet,
	TMapNormal_KeyIn,
	TMapNormal_Main,
	TMapNormal_Draw,
	TMapNormal_Release,
	TMapNormal_VBlank,
 },
 {
	TMapNormal_Init,
	TMapNormal_Build,
	TMapNormal_FadeInSet,
	TMapNormal_FadeOutSet,
	TMapJump_KeyIn,
	TMapNormal_Main,
	TMapNormal_Draw,
	TMapNormal_Release,
	TMapNormal_VBlank,
 },
 {
	TMapNormal_Init,
	TMapNormal_Build,
	TMapBG_FadeInSet,
	TMapBG_FadeOutSet,
	TMapBG_KeyIn,
	TMapNormal_Main,
	TMapNormal_Draw,
	TMapNormal_Release,
	TMapNormal_VBlank,
 },
};

//--------------------------------------------------
///プログラムエリア
//----------------------------------------------------------------
/**
 *	@brief	ワールドマップ プロセス初期化
 *	@param	proc	プロセスデータ
 *	@param	seq		シーケンス
 *
 *	@return	処理状況
 */
PROC_RESULT TMapProc_Init( PROC *proc,int *seq)
{
	TMAP_IO_DAT dat;
	TMAP_MAIN_DAT *wk = NULL;
	TOWNMAP_PARAM * param = (TOWNMAP_PARAM*)PROC_GetParentWork(proc);

	//ワークエリア取得
	HeapStatePush();

	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_TOWNMAP,0x20000);
	TMAP_HEAP_PRINT("プロセス初期化開始");
	
	wk = PROC_AllocWork( proc,sizeof(TMAP_MAIN_DAT),HEAPID_TOWNMAP);
	memset(wk,0,sizeof(TMAP_MAIN_DAT));
	
	//パラメータ引継ぎ
	wk->param = param;
	if(param->mode < TMAP_MODE_MAX){
		wk->mode = param->mode;
	}else{
		wk->mode = TMAP_MNORMAL;
	}
	wk->mapView = param->view_f;	//配布マップ描画フラグ引継ぎ
	wk->heapID = HEAPID_TOWNMAP;

	//サウンド引継ぎ設定
	Snd_DataSetByScene( SND_SCENE_SUB_TOWNMAP, 0, 0 );

	TMAP_HEAP_PRINT("プロセス初期化終了");
	return PROC_RES_FINISH;
}

/**
 *	@brief	ワールドマップ プロセスメイン
 *	@param	proc	プロセスデータ
 *	@param	seq		シーケンス
 *
 *	@return	処理状況
 */
PROC_RESULT TMapProc_Main( PROC *proc,int *seq)
{
	TMAP_MAIN_DAT *wk = PROC_GetWork(proc);

	switch(wk->main_seq){
	case MSEQ_MAININIT:
		wk->main_seq = TMapSeq_MainInit(wk);
		break;
	case MSEQ_SUBINIT:
		wk->main_seq = TMapSeq_SubInit(wk);
		break;
	case MSEQ_FADEINWAIT:
		wk->main_seq = TMapSeq_FadeInWait(wk);
		TMapMainDraw(wk);
		break;
	case MSEQ_MAIN:
		wk->main_seq = TMapSeq_Main(wk);
		TMapMainDraw(wk);
		break;
	case MSEQ_FADEOUTWAIT:
		wk->main_seq = TMapSeq_FadeOutWait(wk);
		TMapMainDraw(wk);
		break;
	case MSEQ_END:
		wk->main_seq = TMapSeq_End(wk);
		break;
	case MSEQ_PROC_END:
		return PROC_RES_FINISH;	
	}
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	ワールドマップ プロセス終了
 *	@param	proc	プロセスデータ
 *	@param	seq		シーケンス
 *
 *	@return	処理状況
 */
PROC_RESULT TMapProc_End( PROC *proc,int *seq)
{
	int i = 0;

	TMAP_MAIN_DAT *wk = PROC_GetWork(proc);
	
	//ワークエリア解放
	PROC_FreeWork(proc);

	HeapStatePop();
	HeapStateCheck(wk->heapID);
	
	TMAP_HEAP_PRINT("プロセス終了");
	sys_DeleteHeap(HEAPID_TOWNMAP);
	return PROC_RES_FINISH;
}

/**
 *	@brief タウンマップモジュール
 */
static void TMapVBlank(void * work)
{
	TMAP_MAIN_DAT* wk = work;

	//サブシーケンス処理実行
	if(TMapSubProcData[wk->mode].vBlank != NULL){
		(TMapSubProcData[wk->mode].vBlank)(wk);	
	}
	
	NNS_GfdDoVramTransfer();	//VRam転送マネージャ実行
	TMapCellActorTrans(wk);
	GF_BGL_VBlankFunc( wk->bgl );
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

/**
 *	@brief タウンマップモジュール VRAM BANK Set
 */
static void TMapVramBankSet(void)
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
 *	@brief タウンマップ共通初期化
 *
 *	@param	wk	TMAP_MAIN_DAT*
 */
static int TMapInitCommon(TMAP_MAIN_DAT* wk)
{
	switch(wk->sub_seq){
	case 0:
		//Blank関数リセット
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);
		
		//自機位置取得
		if(wk->param->player_x == 0 && wk->param->player_z == 0){
			wk->gx = 3;
			wk->gz = 27;
		}else{
			wk->gx = wk->param->player_x/32;
			wk->gz = wk->param->player_z/32;
		}
		wk->cposX = wk->gx;
		wk->cposZ = wk->gz;

		//メッセージリソース取得
		wk->pMsgMap = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,
				NARC_msg_place_name_dat,wk->heapID);
		wk->pMsgTMap = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,
				NARC_msg_townmap_dat,wk->heapID);
		wk->placeName = STRBUF_Create(BUFLEN_PLACE_NAME,wk->heapID);
		
		//ゾーンリソース取得
		wk->pZone = InitFMZ(wk->heapID);

		//ブロックデータ取得
		wk->pBDat = TMapBlockDataLoad("data/tmap_block.dat",wk->heapID);
		break;
	case 1:
		//Bankセット
		TMapVramBankSet();

		//BG関連セット
		wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

		TMapBGLSet(wk,wk->bgl);
		TMapBgGrapSet(wk);
		
		//タッチパネル初期化
		InitTPSystem();
		InitTPNoBuff(4);

		//セルアクター初期化
		TMapCellActorInit(wk);
		break;
	case 2:
		sys_VBlankFuncChange(TMapVBlank, wk);	//VBlankSet

		//デフォルトキー取得関数セット
		wk->keyFunc = TMapSubProcData[wk->mode].keyIO;
		wk->sub_seq = 0;
		return TMAP_SEQ_FINISH;
	}
	wk->sub_seq++;
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	タウンマップ共通終了処理
 *	@param	wk	TMAP_MAIN_DAT*
 */
static void TMapEndCommon(TMAP_MAIN_DAT* wk)
{
	int i;

	//タッチパネル終了
	StopTP();

	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF);
	
	sys_VBlankFuncChange(NULL, NULL);
	sys_HBlankIntrStop();	//HBlank割り込み停止

	//セルアクター終了
	TMapCellActorRelease(wk);

	TMapBgGrapRelease(wk);
	for(i = 0;i < 8;i++){
		GF_BGL_BGControlExit( wk->bgl, i);
	}

	sys_FreeMemoryEz(wk->bgl);

	//ブロックデータ解放
	TMapBlockDataRelease(wk->pBDat);
	//ゾーンデータ解放
	FreeFMZ(wk->pZone);
	//メッセージマネージャー解放
	STRBUF_Delete(wk->placeName);
	MSGMAN_Delete(wk->pMsgTMap);
	MSGMAN_Delete(wk->pMsgMap);
}

/**
 *	@brief	タウンマップDraw
 */
static void TMapMainDraw(TMAP_MAIN_DAT* wk)
{
	//サブDraw
	(TMapSubProcData[wk->mode].draw)(wk);
	
	//アクター
	TMapCellActorMain(wk);
}
/**
 *	@brief	タウンマップ BGL設定
 */
static void TMapBGLSet(TMAP_MAIN_DAT* wk,GF_BGL_INI *ini)
{
	int i,frame;
	
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
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
		{	//MAIN BG2
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
		{	//MAIN BG3
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			3,0,0,FALSE},
		{	//SUB BG0
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//SUB BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
		{	//SUB BG2
			0,0,0x2000,0,GF_BGL_SCRSIZ_512x512,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
		{	//SUB BG3
			0,0,0x2000,0,GF_BGL_SCRSIZ_512x512,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xb000,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			3,0,0,FALSE},
	};
	frame = GF_BGL_FRAME0_M;
	for(i = 0;i < 8;i++){
		GF_BGL_BGControlSet(ini,frame,&(TextBgCntDat[i]),GF_BGL_MODE_TEXT);
		GF_BGL_ScrClear(ini,frame++);
	}
	}
	GF_BGL_ClearCharSet(GF_BGL_FRAME0_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME1_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME2_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME3_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME0_S,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME1_S,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME2_S,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME3_S,32,0,wk->heapID);
}

/**
 *	@brief	タウンマップ　2Dリソースファイル取得
 */
#define GRA_M01_NCGR	(NARC_tmap_gra_tmap01_ncgr)
#define GRA_S01_NCGR	(NARC_tmap_gra_tmap02_ncgr)
#define GRA_S02_NCGR	(NARC_tmap_gra_tmap02_sw_ncgr)

#define GRA_M01_NCLR	(NARC_tmap_gra_tmap01_nclr)
#define GRA_S01_NCLR	(NARC_tmap_gra_tmap02_nclr)

#define GRA_M_MLOAD	(NARC_tmap_gra_tmap01_mload_nscr)
#define GRA_M_BACK	(NARC_tmap_gra_tmap01_back_nscr)
#define GRA_M_DIS	(NARC_tmap_gra_tmap01_dis_nscr)
#define GRA_S_DM	(NARC_tmap_gra_tmap02_dm_nscr)
#define GRA_S_DR	(NARC_tmap_gra_tmap02_dr_nscr)
#define GRA_S_DSWM	(NARC_tmap_gra_tmap02_dswm_nscr)
#define GRA_S_SW	(NARC_tmap_gra_tmap02_sw_nscr)
#define GRA_S_DIS	(NARC_tmap_gra_tmap02_dis_nscr)

//#define GRA_
static void TMapBgGrapSet(TMAP_MAIN_DAT* wk)
{
	void* tmp;
	u32	size,arcID;
	ARCHANDLE* handle;

	arcID = ARC_TMAP_GRA;

	//アーカイブのハンドルを取得
	handle = ArchiveDataHandleOpen(ARC_TMAP_GRA,wk->heapID);

	//キャラクタデータ転送
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_M01_NCGR,GF_BGL_FRAME1_M,0,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_S01_NCGR,GF_BGL_FRAME2_S,0,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_S02_NCGR,GF_BGL_FRAME1_S,0,0,0);
	
	//パレット転送
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_M01_NCLR,PALTYPE_MAIN_BG,2,0,0);
	APP_ArcFileVramLoad(wk->bgl,wk->heapID,handle,
		arcID,GRA_S01_NCLR,PALTYPE_SUB_BG,2,0,0);

	//スクリーン
	wk->pScrBuf01 = APP_ArcScrFileUnpack(handle,arcID,GRA_M_MLOAD,&wk->pScr01,wk->heapID);
	wk->pScrBuf01_back = APP_ArcScrFileUnpack(handle,arcID,GRA_M_BACK,&wk->pScr01_back,wk->heapID);
	wk->pScrBuf01_dis = APP_ArcScrFileUnpack(handle,arcID,GRA_M_DIS,&wk->pScr01_dis,wk->heapID);

	wk->pScrBuf02_dm = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DM,&wk->pScr02_dm,wk->heapID);
	wk->pScrBuf02_dr = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DR,&wk->pScr02_dr,wk->heapID);
	wk->pScrBuf02_dswm = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DSWM,&wk->pScr02_dswm,wk->heapID);
	wk->pScrBuf02_sw = APP_ArcScrFileUnpack(handle,arcID,GRA_S_SW,&wk->pScr02_sw,wk->heapID);
	wk->pScrBuf02_dis = APP_ArcScrFileUnpack(handle,arcID,GRA_S_DIS,&wk->pScr02_dis,wk->heapID);
	
	//クローズ
	ArchiveDataHandleClose( handle );
	
	//フォント用パレットセット
	SystemFontPaletteLoad(PALTYPE_MAIN_BG,FONT_SYS_PAL*32,wk->heapID);
	SystemFontPaletteLoad(PALTYPE_SUB_BG,FONT_SYS_PAL*32,wk->heapID);
}

/**
 *	@brief	メイン2Dグラフィックリソース解放
 */
static void TMapBgGrapRelease(TMAP_MAIN_DAT* wk)
{
	sys_FreeMemoryEz(wk->pScrBuf02_dis);
	sys_FreeMemoryEz(wk->pScrBuf02_sw);
	sys_FreeMemoryEz(wk->pScrBuf02_dswm);
	sys_FreeMemoryEz(wk->pScrBuf02_dr);
	sys_FreeMemoryEz(wk->pScrBuf02_dm);
	sys_FreeMemoryEz(wk->pScrBuf01_dis);
	sys_FreeMemoryEz(wk->pScrBuf01_back);
	sys_FreeMemoryEz(wk->pScrBuf01);
}

//============================================================================================
//	シーケンス
//============================================================================================

/**
 *	@brief	メイン/サブメモリ初期化
 */
static int TMapSeq_MainInit(TMAP_MAIN_DAT* wk)
{
	//メイン初期化
	if(TMapInitCommon(wk) != TMAP_SEQ_FINISH){
		return PROC_RES_CONTINUE;	
	}
//	TMAP_HEAP_PRINT("メイン初期化終了");

	//サブメモリ初期取得
	(TMapSubProcData[wk->mode].init)(wk);
	return MSEQ_SUBINIT;
}

/**
 *	@brief	モード別リソース初期化
 */
static int TMapSeq_SubInit(TMAP_MAIN_DAT* wk)
{
	//モード別初期化
	if((TMapSubProcData[wk->mode].build)(wk) != TMAP_SEQ_FINISH){
		return MSEQ_SUBINIT;	
	}
	
	//モード別フェードイン呼び出し
	TMapSubProcData[wk->mode].fadein(wk);
	return MSEQ_FADEINWAIT;
}

/**
 *	@brief	フェードイン待ち
 */
static int TMapSeq_FadeInWait(TMAP_MAIN_DAT* wk)
{
	if(!WIPE_SYS_EndCheck()){
		return MSEQ_FADEINWAIT;
	}
	return MSEQ_MAIN;
}

/**
 *	@brief	モード別メインシーケンス終了待ち
 */
static int TMapSeq_Main(TMAP_MAIN_DAT* wk)
{
	//キー取得
	if( (wk->keyFunc)(wk) != TMAP_SEQ_FINISH){
		//サブメイン処理
		TMapSubProcData[wk->mode].main(wk);
		return MSEQ_MAIN;
	}
	//モード別フェードアウトリクエスト
	TMapSubProcData[wk->mode].fadeout(wk);
	return MSEQ_FADEOUTWAIT;
}

/**
 *	@brief	フェードアウト終了待ち
 */
static int TMapSeq_FadeOutWait(TMAP_MAIN_DAT* wk)
{
	if(WIPE_SYS_EndCheck()){
		//画面を黒く設定
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,GX_BLEND_PLANEMASK_NONE,31,0);
		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		WIPE_ResetWndMask(WIPE_DISP_MAIN);
		WIPE_ResetWndMask(WIPE_DISP_SUB);
		return MSEQ_END;
	}

	TMapSubProcData[wk->mode].main(wk);
	return MSEQ_FADEOUTWAIT;
}

/**
 *	@brief	メイン/サブ　初期メモリ解放
 */
static int TMapSeq_End(TMAP_MAIN_DAT* wk)
{
	//モード別解放
	(TMapSubProcData[wk->mode].release)(wk);
	
	//メインメモリ解放
	TMapEndCommon(wk);
//	TMAP_HEAP_PRINT("解放処理終了");
	return MSEQ_PROC_END;	
}

//============================================================================================
//	デバッグ
//============================================================================================
