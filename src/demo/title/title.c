//============================================================================================
/**
 * @file	title.c
 * @brief	タイトル画面
 * @author	Hiroyuki Nakamura
 * @date	2005.02.02
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"
#include "system/brightness.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "system/pm_rtc.h"
#include "system/main.h"
#include "system/savedata.h"
#include "system/fontproc.h"

#include "titledemo.naix"
#include "op_demo.naix"
#include "msgdata/msg.naix"

#include "field/field.h"
#include "demo/title.h"
#include "demo/opening/opening_sys.h"

#include "msgdata/msg_title.h"

extern const PROC_DATA BackupEraseProcData;
extern const PROC_DATA BackupLoadProcData;
//================================================================
//================================================================
//
//
//		タイトル
//
//
//================================================================
//================================================================
//----------------------------------
//型宣言
//----------------------------------
///	３Ｄモデル制御用構造体
typedef struct TITLE_3DWORK_tag
{
	int	Draw3Dsw;

	NNSG3dRenderObj			rndobj;
	NNSG3dResMdl*			resmdl;
	NNSG3dResFileHeader* 	rfhead;
	void*					resanm;
	NNSG3dAnmObj*			anmobj;
	NNSFndAllocator			allocater;

	VecFx32 trans;			//座標
	VecFx32 scale;			//スケール
	VecFx32	rotate;			//回転	

	GF_CAMERA_PTR camera_p;

	int		anm_flag;
}TITLE_3DWORK;

///	ロゴ回転デモ使用ワーク構造体
typedef struct TITLE_LOGODEMO_WORK_tag
{
	int seq;
	TITLE_3DWORK	logo;

}TITLE_LOGODEMO_WORK;

///	タイトル画面使用ワーク構造体
typedef struct TITLE_TITLEDEMO_WORK_tag
{
	int seq;
	TITLE_3DWORK	poke;
	u16		wait_counter;
	GF_BGL_BMPWIN	msgwin;

	VecFx32	camera_tpos;
	VecFx32	camera_cpos;

	BOOL	enable_flag;

	VecFx32	cp_st;
	VecFx32	cp_ed;

	VecFx32	tp_st;
	VecFx32	tp_ed;

	VecFx16	lv0;
	VecFx16	lv1;
	u16		l1ef;
	u16		l1efseq;

	fx32	c_speed;

}TITLE_TITLEDEMO_WORK;
			
///	タイトル全体制御用ワーク構造体
typedef struct TITLE_DEMO_WORK_tag
{
	int	heapID; 

	GF_BGL_INI*		bgl;	// BGマネージャ
	GF_G3DMAN*		g3Dman;	// 3Dマネージャ

	TITLE_LOGODEMO_WORK		logoDemo;
	TITLE_TITLEDEMO_WORK	titleDemo;

	u16		next_scene;
	int		enable_counter;
	int		connect_count;
	int		connect_num;

	int		main_timer;
}TITLE_DEMO_WORK;

///	３Ｄ描画エンジンスイッチ定義
typedef enum {
	DRAW3D_DISABLE = 0,	///<描画なし
	DRAW3D_BANISH,		///<消去→描画なし
	DRAW3D_ENABLE,		///<描画
};

typedef enum {
	DRAW3DANM_DISABLE = 0,	///<描画なし
	DRAW3DANM_STOP,			///<停止→描画なし
	DRAW3DANM_ENABLE,		///<描画
};

///	遷移先シーン定義
typedef enum {
	SCENE_ID_NOT_DECIDE = 0,		///<遷移先シーン未確定
	SCENE_ID_MENU,					///<遷移先シーン：通常メニュー
	SCENE_ID_ERASE,					///<遷移先シーン：バックアップ消去
	SCENE_ID_LOOP,					///<遷移先シーン：タイマーループ
	SCENE_ID_DEBUGMENU,				///<遷移先シーン：デバッグメニュー
}SCENE_ID;

enum{
	//タイトル画面
	TITLEDEMO_SEQ_TITLE_LOAD,
	TITLEDEMO_SEQ_TITLE_IN,
	TITLEDEMO_SEQ_TITLE_SOUNDSTART,
	TITLEDEMO_SEQ_TITLE_KEYCHECK,
	TITLEDEMO_SEQ_TITLE_EXITWAIT,
	TITLEDEMO_SEQ_TITLE_EXITWAIT2,
	TITLEDEMO_SEQ_TITLE_EXIT,
};

//----------------------------------
//関数宣言
//----------------------------------
extern void		Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);
FS_EXTERN_OVERLAY( d_startmenu );
FS_EXTERN_OVERLAY( title_debug );
FS_EXTERN_OVERLAY( startmenu );
FS_EXTERN_OVERLAY( title );
extern const PROC_DATA OpDemoProcData;

static PROC_RESULT Title_Init( PROC * proc, int * seq );
static PROC_RESULT Title_Main( PROC * proc, int * seq );
static PROC_RESULT Title_Exit( PROC * proc, int * seq );

static void TitleLogo_Demo_VBlank( void* work );
static void Title_VramBankSet( void );
static void Title2DBgSet( TITLE_DEMO_WORK* wk );
static void Title2DBgRelease( TITLE_DEMO_WORK* wk );

static void Title3D_Init( TITLE_DEMO_WORK* wk );
static void Title3D_Exit( TITLE_DEMO_WORK* wk );
static void Title3D_ModelLoad( TITLE_3DWORK* g3Dwk, int dataID, int texanmID, int heapID);
static void Title3D_ModelRelease( TITLE_3DWORK* g3Dwk );
static void Title3D_Draw( TITLE_3DWORK* g3Dwk );

static BOOL TitleDemoSkipCheck( void );

static BOOL TitleDemo_Init( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID );
static BOOL TitleDemo_DispOnEffect( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID );
static BOOL TitleDemo_Main( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID );
static BOOL TitleDemo_Exit( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID );

#ifdef PM_DEBUG
static void DebugControl( TITLE_TITLEDEMO_WORK* wk );
#endif
//----------------------------------
//マクロ宣言
//----------------------------------
#define KEYTRG( pattern ) ( ( sys.trg & ( pattern ) ) == ( pattern ) )
#define KEYCNT( pattern ) ( ( sys.cont & ( pattern ) ) == ( pattern ) )

#define VEC_SET( vec, vecx, vecy, vecz ) {					\
	vec.x = vecx;											\
	vec.y = vecy;											\
	vec.z = vecz;											\
}

#define FADE( pattern, col, heapID ) {						\
	WIPE_SYS_Start(	WIPE_PATTERN_WMS,pattern,pattern,col,	\
					WIPE_DEF_DIV,WIPE_DEF_SYNC,heapID);		\
}

#define MAINFRAME_ON( frame )		{ GF_Disp_GX_VisibleControl( frame, VISIBLE_ON ); }
#define MAINFRAME_OFF( frame )		{ GF_Disp_GX_VisibleControl( frame, VISIBLE_OFF ); }
#define SUBFRAME_ON( frame )		{ GF_Disp_GXS_VisibleControl( frame, VISIBLE_ON ); }
#define SUBFRAME_OFF( frame )		{ GF_Disp_GXS_VisibleControl( frame, VISIBLE_OFF ); }

#define FRAME_ALLOFF {				\
	MAINFRAME_OFF( GX_PLANEMASK_BG0 )	\
	MAINFRAME_OFF( GX_PLANEMASK_BG1 )	\
	MAINFRAME_OFF( GX_PLANEMASK_BG2 )	\
	MAINFRAME_OFF( GX_PLANEMASK_BG3 )	\
	SUBFRAME_OFF( GX_PLANEMASK_BG0 )	\
	SUBFRAME_OFF( GX_PLANEMASK_BG1 )	\
	SUBFRAME_OFF( GX_PLANEMASK_BG2 )	\
	SUBFRAME_OFF( GX_PLANEMASK_BG3 )	\
}
		
#define SEQ_RESET(seq)			{ seq = 0; }

#define TITLE_LOGO_FRAME			( GF_BGL_FRAME2_S )
#define TITLE_LOGO2_FRAME			( GF_BGL_FRAME1_S )
#define TITLE_PRSSTART_FRAME		( GF_BGL_FRAME0_S )
#define TITLE_CPRIGHT_FRAME			( GF_BGL_FRAME1_M )

#define TITLE_LOGO_FRAME_ON			{ SUBFRAME_ON( GX_PLANEMASK_BG2 ) }
#define TITLE_LOGO2_FRAME_ON		{ SUBFRAME_ON( GX_PLANEMASK_BG1 ) }
#define TITLE_PRSSTART_FRAME_ON		{ SUBFRAME_ON( GX_PLANEMASK_BG0 ) }
#define TITLE_CPRIGHT_FRAME_ON		{ MAINFRAME_ON( GX_PLANEMASK_BG1 ) }
#define TITLE_LOGO_FRAME_OFF		{ SUBFRAME_OFF( GX_PLANEMASK_BG2 ) }
#define TITLE_LOGO2_FRAME_OFF		{ SUBFRAME_OFF( GX_PLANEMASK_BG1 ) }
#define TITLE_PRSSTART_FRAME_OFF	{ SUBFRAME_OFF( GX_PLANEMASK_BG0 ) }
#define TITLE_CPRIGHT_FRAME_OFF		{ MAINFRAME_OFF( GX_PLANEMASK_BG1 ) }

#define TITLE_LOGO_PALTYPE			( PALTYPE_SUB_BG_EX )
#define TITLE_GF_PALTYPE			( PALTYPE_MAIN_BG )

//=================================================================================================
//
// ＰＲＯＣ定義テーブル
//
//=================================================================================================
const PROC_DATA TitleProcData = {
	Title_Init,
	Title_Main,
	Title_Exit,
	NO_OVERLAY_ID
};

//================================================================
//----------------------------------
//ＰＲＯＣ初期化
//----------------------------------
static PROC_RESULT Title_Init(PROC * proc, int * seq)
{
	TITLE_DEMO_WORK * wk;
	int	heapID;

#ifdef	PM_DEBUG
	OS_TPrintf("SYSTEM HEAP SIZE = %08x\n", sys_GetHeapFreeSize(HEAPID_BASE_SYSTEM));
#endif
	heapID = HEAPID_TITLE_DEMO;

	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_WHITE );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_WHITE );

	//カラー特殊効果無効
	G2S_BlendNone();
	G2_BlendNone();
	
	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrSet( NULL,NULL );		// HBlankセット

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);

	sys_KeyRepeatSpeedSet(4,8);
	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x40000 );

	wk = PROC_AllocWork(proc,sizeof(TITLE_DEMO_WORK),heapID);
	memset(wk,0,sizeof(TITLE_DEMO_WORK));

	wk->heapID = heapID;
	wk->next_scene = SCENE_ID_NOT_DECIDE;
	wk->main_timer = 0;

	Title_VramBankSet();
	Title2DBgSet(wk);
	Title3D_Init(wk);

	sys_VBlankFuncChange(TitleLogo_Demo_VBlank,(void*)wk);
	GF_Disp_DispOn();

	return	PROC_RES_FINISH;
}

//----------------------------------
//ＰＲＯＣメイン
//----------------------------------
static PROC_RESULT Title_Main(PROC * proc, int * seq)
{
	TITLE_DEMO_WORK * wk = PROC_GetWork( proc );

	switch(*seq){

	case TITLEDEMO_SEQ_TITLE_LOAD:
		if( TitleDemo_Init( &wk->titleDemo, wk->bgl, wk->heapID ) == TRUE){

			SEQ_RESET(wk->titleDemo.seq)

			if(sys.DS_Boot_Flag == FALSE){		//起動時以外は導入演出カット
#ifdef PM_DEBUG
				wk->enable_counter = 0;
#else
				wk->enable_counter = 30*1;	//1/30 frame * 1
#endif
				*seq = TITLEDEMO_SEQ_TITLE_SOUNDSTART;
			} else {
				wk->enable_counter = 0;
				sys.DS_Boot_Flag = FALSE;	//ブートフラグセット
				*seq = TITLEDEMO_SEQ_TITLE_IN;
			}
		}
		break;

	case TITLEDEMO_SEQ_TITLE_IN:
		if( TitleDemo_DispOnEffect( &wk->titleDemo, wk->bgl, wk->heapID ) == TRUE){
			SEQ_RESET(wk->titleDemo.seq)
			*seq = TITLEDEMO_SEQ_TITLE_SOUNDSTART;
		}
		break;
			
	case TITLEDEMO_SEQ_TITLE_SOUNDSTART:
		Snd_SceneSet( SND_SCENE_DUMMY );						//音楽シーンリセット
		Snd_DataSetByScene( SND_SCENE_TITLE, SEQ_TITLE01, 1 );	//タイトル画面
		*seq = TITLEDEMO_SEQ_TITLE_KEYCHECK;
		break;

	case TITLEDEMO_SEQ_TITLE_KEYCHECK:
		if( wk->enable_counter ){
			wk->enable_counter--;	//操作が可能になるまでのウェイト計測用カウンタ

			//開始時のみ約２秒くらいまでゲーム開始が出来ないようにする
			//(連打がきくと即タイトル画面を抜けてしまうので)
			wk->titleDemo.enable_flag = FALSE;
			TitleDemo_Main( &wk->titleDemo, wk->bgl, wk->heapID );
			break;
		} else {
			wk->titleDemo.enable_flag = TRUE;
			TitleDemo_Main( &wk->titleDemo, wk->bgl, wk->heapID );
		}
		wk->main_timer++;

		if( KEYTRG(PAD_BUTTON_A) || KEYTRG(PAD_BUTTON_START)){
			wk->next_scene = SCENE_ID_MENU;//開始メニューへ
			Snd_BgmFadeOut( 0, 60 );
			Snd_SePlay( SEQ_SE_DP_START );
			*seq = TITLEDEMO_SEQ_TITLE_EXITWAIT;
			break;
		}
		if( KEYCNT(PAD_BUTTON_B|PAD_KEY_UP|PAD_BUTTON_SELECT) ){
			wk->next_scene = SCENE_ID_ERASE;//バックアップ消去へ
			FADE(WIPE_TYPE_FADEOUT,WIPE_FADE_BLACK,wk->heapID)
			*seq = TITLEDEMO_SEQ_TITLE_EXIT;
			break;
		}
		if( wk->main_timer > 30*30 ){
			wk->next_scene = SCENE_ID_LOOP;//タイムアウトループ
			sys.DS_Boot_Flag = TRUE;	//ブートフラグリセット
			TITLE_PRSSTART_FRAME_OFF
			Snd_BgmFadeOut( 0, 60 );
			*seq = TITLEDEMO_SEQ_TITLE_EXITWAIT2;
			break;
		}

#ifdef PM_DEBUG
		DebugControl( &wk->titleDemo );

		if( KEYTRG(PAD_BUTTON_SELECT) ){
			wk->next_scene = SCENE_ID_DEBUGMENU;//デバッグメニューへ
			FADE(WIPE_TYPE_FADEOUT,WIPE_FADE_BLACK,wk->heapID)
			*seq = TITLEDEMO_SEQ_TITLE_EXIT;
			break;
		}
#endif
		break;
			
	case TITLEDEMO_SEQ_TITLE_EXITWAIT:
		wk->titleDemo.enable_flag = FALSE;
		TitleDemo_Main( &wk->titleDemo, wk->bgl, wk->heapID );

		if( Snd_FadeCheck() == 0 ){
			Snd_BgmStop( SEQ_TITLE01, 0 );	
			FADE(WIPE_TYPE_FADEOUT,WIPE_FADE_BLACK,wk->heapID)
			*seq = TITLEDEMO_SEQ_TITLE_EXIT;
		}
		break;

	case TITLEDEMO_SEQ_TITLE_EXITWAIT2:
		wk->titleDemo.enable_flag = FALSE;
		TitleDemo_Main( &wk->titleDemo, wk->bgl, wk->heapID );

		if( Snd_FadeCheck() == 0 ){
			Snd_BgmStop( SEQ_TITLE01, 0 );	
			FADE(WIPE_TYPE_FADEOUT,WIPE_FADE_WHITE,wk->heapID)
			*seq = TITLEDEMO_SEQ_TITLE_EXIT;
		}
		break;

	case TITLEDEMO_SEQ_TITLE_EXIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			if( TitleDemo_Exit( &wk->titleDemo, wk->bgl, wk->heapID ) == TRUE){
				return	PROC_RES_FINISH;
			}
		}
		break;
	}
	return	PROC_RES_CONTINUE;
}

//----------------------------------
//ＰＲＯＣ終了
//----------------------------------
static PROC_RESULT Title_Exit(PROC * proc, int * seq)
{
	TITLE_DEMO_WORK * wk = PROC_GetWork( proc );
	int heapID = wk->heapID;
	int next_scene = wk->next_scene;

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	Title3D_Exit( wk );
	Title2DBgRelease( wk );
	PROC_FreeWork( proc );				// ワーク開放

	sys_DeleteHeap( heapID );

	switch ( next_scene ) {
	default:
	case SCENE_ID_MENU:
		//Main_SetNextProc( FS_OVERLAY_ID( startmenu ), &StartMenuProcData );
		Main_SetNextProc( NO_OVERLAY_ID, &BackupLoadProcData );
		break;
	case SCENE_ID_ERASE:
		Main_SetNextProc( NO_OVERLAY_ID, &BackupEraseProcData );
		break;
	case SCENE_ID_LOOP:
		Snd_SceneSet( SND_SCENE_DUMMY );						//音楽シーンリセット
		Main_SetNextProc( FS_OVERLAY_ID( title ), &OpDemoProcData );
		break;

#ifdef PM_DEBUG
	case SCENE_ID_DEBUGMENU:
		Main_SetNextProc( FS_OVERLAY_ID(title_debug), &DebugTitleMenuProcData );
		break;
#endif
	}
	return	PROC_RES_FINISH;
}


//----------------------------------
//ＶＢＬＡＮＫ関数
//----------------------------------
static void TitleLogo_Demo_VBlank(void* work)
{
	TITLE_DEMO_WORK* wk = work;

	GF_BGL_VBlankFunc(wk->bgl);
}


//----------------------------------
//ＶＲＡＭ設定
//----------------------------------
static void Title_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_0123_H,	// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_NONE,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_NONE,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0_G				// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}


//----------------------------------
//
//	デモスキップ判定
//
//----------------------------------
static BOOL TitleDemoSkipCheck( void )
{
	if( KEYTRG(PAD_BUTTON_A) || KEYTRG(PAD_BUTTON_START) || KEYTRG(PAD_BUTTON_SELECT) ){
		return TRUE;
	}
	return FALSE;
}


//----------------------------------
//
//	３Ｄ初期化＆終了
//
//----------------------------------
static void Title3D_Init( TITLE_DEMO_WORK* wk )
{
	wk->g3Dman = GF_G3DMAN_Init(wk->heapID, 
			GF_G3DMAN_LNK, GF_G3DTEX_128K, GF_G3DMAN_LNK, GF_G3DPLT_64K, NULL );

	// ３Ｄ使用面の設定変更(プライオリティー)
    G2_SetBG0Priority(1);
}

static void Title3D_Exit( TITLE_DEMO_WORK* wk )
{
	GF_G3D_Exit( wk->g3Dman );
}

//----------------------------------
//
//	３Ｄデータ読み込み＆終了
//
//----------------------------------
static void Title3D_ModelLoad( TITLE_3DWORK* g3Dwk, int dataID, int texanmID, int heapID)
{
	void*			anm;
    NNSG3dResTex*	tex;

	sys_InitAllocator( &g3Dwk->allocater, heapID, 4 ); 

	g3Dwk->rfhead = ArchiveDataLoadMalloc(ARC_TITLE,dataID,heapID);
	g3Dwk->resanm = ArchiveDataLoadMalloc(ARC_TITLE,texanmID,heapID);
	simple_3DModelSetResFileAlready( &g3Dwk->rndobj, &g3Dwk->resmdl, &g3Dwk->rfhead );

	anm				= NNS_G3dGetAnmByIdx( g3Dwk->resanm, 0 );
	g3Dwk->anmobj	= NNS_G3dAllocAnmObj( &g3Dwk->allocater, anm, g3Dwk->resmdl );
    tex				= NNS_G3dGetTex( g3Dwk->rfhead );
	NNS_G3dAnmObjInit( g3Dwk->anmobj, anm, g3Dwk->resmdl, tex );
	NNS_G3dRenderObjAddAnmObj( &g3Dwk->rndobj, g3Dwk->anmobj );

	{
		//モデルデータパラメータ初期化
		VecFx32 init_trans	= { 0, 0, 0 };
		VecFx32 init_scale	= { FX32_ONE, FX32_ONE, FX32_ONE };
		VecFx32 init_rotate = { 0, 0, 0 };

		g3Dwk->trans	= init_trans;
		g3Dwk->scale	= init_scale;
		g3Dwk->rotate	= init_rotate;
	}
	g3Dwk->anm_flag = DRAW3DANM_DISABLE;
}

static void Title3D_ModelRelease(TITLE_3DWORK* g3Dwk)
{
	NNS_G3dFreeAnmObj( &g3Dwk->allocater, g3Dwk->anmobj ); 
	sys_FreeMemoryEz( g3Dwk->resanm );
	sys_FreeMemoryEz( g3Dwk->rfhead );
}


//----------------------------------
//
//	３Ｄ描画関数
//
//----------------------------------
static void Title3D_Draw( TITLE_3DWORK* g3Dwk )
{
	MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};

	switch( g3Dwk->Draw3Dsw ){

	case DRAW3D_DISABLE:
		break;

	case DRAW3D_BANISH:
		GF_G3X_Reset();
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
		g3Dwk->Draw3Dsw = DRAW3D_DISABLE;
		break;

	case DRAW3D_ENABLE:
		GF_G3X_Reset();
		GFC_CameraLookAt();

		VecFx32_to_MtxFx33(	&rotate_tmp,&g3Dwk->rotate);

		simple_3DModelDraw(	&g3Dwk->rndobj,
							&g3Dwk->trans,
							&rotate_tmp,
							&g3Dwk->scale);
#if 0
		if( g3Dwk->anm_flag == TRUE ){
			g3Dwk->anmobj->frame += (FX32_ONE);
			if( g3Dwk->anmobj->frame == NNS_G3dAnmObjGetNumFrame( g3Dwk->anmobj )){
				g3Dwk->anmobj->frame = 0;
			}
		}
#else
		switch( g3Dwk->anm_flag ){
		case DRAW3DANM_DISABLE:
			g3Dwk->anmobj->frame = 0;
			break;

		case DRAW3DANM_STOP:
			if( g3Dwk->anmobj->frame == 0 ){
				g3Dwk->anm_flag = DRAW3DANM_DISABLE;
				break;
			}

		case DRAW3DANM_ENABLE:
			g3Dwk->anmobj->frame += (FX32_ONE);
			if( g3Dwk->anmobj->frame == NNS_G3dAnmObjGetNumFrame( g3Dwk->anmobj )){
				g3Dwk->anmobj->frame = 0;
			}
			break;
		}
#endif
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
		break;
	}
}


//----------------------------------
//
//	２ＤＢＧ初期化＆終了
//
//----------------------------------
static void Title2DBgSet( TITLE_DEMO_WORK* wk )
{
	//BGライブラリ用メモリ確保
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	// BGシステム設定
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// PRESS START ＢＧ設定(0)
		GF_BGL_BGCNT_HEADER PrsSt_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x2800, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, TITLE_PRSSTART_FRAME, &PrsSt_Data, GF_BGL_MODE_TEXT );
	}
	{	// ダイヤ・パールロゴ ＢＧ設定(1)
		GF_BGL_BGCNT_HEADER DPlogo_Data = {
			0, 0, 0x1000, 0,
			GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, TITLE_LOGO2_FRAME, &DPlogo_Data, GF_BGL_MODE_TEXT );
	}
	{	// タイトルロゴ ＢＧ設定(2)
		GF_BGL_BGCNT_HEADER Titlelogo_Data = {
			0, 0, 0x1000, 0,
			GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x3800, GX_BG_CHARBASE_0x10000,
			GX_BG_EXTPLTT_23, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, TITLE_LOGO_FRAME, &Titlelogo_Data, GF_BGL_MODE_TEXT );
	}
	{	// GAMEFREAK inc ＢＧ設定(1)
		GF_BGL_BGCNT_HEADER GF_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x3800, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, TITLE_CPRIGHT_FRAME, &GF_Data, GF_BGL_MODE_TEXT );
	}

	{	// メインディスプレイ背景 ＢＧ設定(3)　
		GF_BGL_BGCNT_HEADER BackM_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &BackM_Data, GF_BGL_MODE_TEXT );
	}
	{	// サブディスプレイ背景 ＢＧ設定(3)　
		GF_BGL_BGCNT_HEADER BackS_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_S, &BackS_Data, GF_BGL_MODE_TEXT );
	}
	FRAME_ALLOFF

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0x0000 );	//背景色初期化（メイン画面）
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0x0000 );	//背景色初期化（サブ画面）
}

static void Title2DBgRelease( TITLE_DEMO_WORK* wk )
{
	FRAME_ALLOFF
	GF_BGL_BGControlExit( wk->bgl, TITLE_PRSSTART_FRAME );
	GF_BGL_BGControlExit( wk->bgl, TITLE_LOGO2_FRAME );
	GF_BGL_BGControlExit( wk->bgl, TITLE_LOGO_FRAME );
	GF_BGL_BGControlExit( wk->bgl, TITLE_CPRIGHT_FRAME );

	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_S );

	sys_FreeMemoryEz( wk->bgl );
}





//=================================================================================================
//
//	タイトル画面
//
//=================================================================================================
static void Title2DGraphicSet(GF_BGL_INI* ini,int heapID, TITLE_TITLEDEMO_WORK* wk );
static void Title2DGraphicRelease(GF_BGL_INI* ini,int heapID, TITLE_TITLEDEMO_WORK* wk );
static void TitleDemoDataGet( TITLE_TITLEDEMO_WORK* wk );
static void TitleDemoLight1Effect( TITLE_TITLEDEMO_WORK* wk );

//各種設定値（NitroViewer　で取得）
#define TD_TITLE_CAMERA_PERSPWAY		(0x0b60)
#define TD_TITLE_CAMERA_CLIP_NEAR		(0)
#define TD_TITLE_CAMERA_CLIP_FAR		(FX32_ONE*100)

#define DOTSIZE							(8)
#define PAL1DATA						(2)
#define PAL1SIZE						(16*PAL1DATA)

#define FLUSH_WIPE_DIV	( 5 )
#define FLUSH_WIPE_SYNC	( 2 )

#define FLUSH_SET( sync, to, from  )	{												\
	ChangeBrightnessRequest( sync, to, from,											\
		( /*GX_BLEND_PLANEMASK_BG0 |*/ GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 ),	\
		MASK_MAIN_DISPLAY );															\
	ChangeBrightnessRequest( sync, to, from,											\
		( GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 ),	\
		MASK_SUB_DISPLAY );																\
}

#define FLUSH_WAIT	( (IsFinishedBrightnessChg( MASK_MAIN_DISPLAY ) == TRUE )			\
						 &&(IsFinishedBrightnessChg( MASK_SUB_DISPLAY ) == TRUE ) )

#define CAMERA_MOVE( now_pos, to_pos, speed, flag ) {		\
	if( now_pos > to_pos ){									\
		if( ( now_pos - to_pos ) > speed ){					\
			now_pos -= speed;								\
		} else {											\
			now_pos = to_pos;								\
		}													\
		flag = FALSE;										\
	} else if( now_pos < to_pos ){							\
		if( ( to_pos - now_pos ) > speed ){					\
			now_pos += speed;								\
		} else {											\
			now_pos = to_pos;								\
		}													\
		flag = FALSE;										\
	}														\
}

enum{
	TDSEQ_LIGHT1_INIT = 0,
	TDSEQ_LIGHT1_WAIT,
	TDSEQ_LIGHT1_UP,
	TDSEQ_LIGHT1_DOWN,
};
// メッセージウィンドウ
static const BMPWIN_DAT TitleMsgWinData =
	{ TITLE_PRSSTART_FRAME,2,18,28,2,2,1 };	//frame,startX,startY,sizeX,sizeY,palnum,cgxnum	

//----------------------------------
// 初期化
//----------------------------------
static BOOL TitleDemo_Init( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID )
{
	TitleDemoDataGet( wk );

	Title2DGraphicSet(bgl,heapID,wk);

	if( CasetteVersion == VERSION_DIAMOND ){
		Title3D_ModelLoad( &wk->poke, 
							NARC_titledemo_title_iar_nsbmd, 
							NARC_titledemo_title_iar_nsbta, 
							heapID );
	} else {
		Title3D_ModelLoad( &wk->poke, 
							NARC_titledemo_title_air_nsbmd, 
							NARC_titledemo_title_air_nsbta, 
							heapID );
	}

    G3X_AntiAlias( TRUE );
	G3X_AlphaBlend( TRUE );		// アルファブレンド　オン
	{
		//カメラセット
		VEC_SET( wk->camera_tpos, wk->tp_st.x, wk->tp_st.y, wk->tp_st.z );
		VEC_SET( wk->camera_cpos, wk->cp_st.x, wk->cp_st.y, wk->cp_st.z );

		wk->poke.camera_p = GFC_AllocCamera(heapID);	//カメラ作成

		GFC_InitCameraTC( &wk->camera_tpos,&wk->camera_cpos,TD_TITLE_CAMERA_PERSPWAY,
							GF_CAMERA_PERSPECTIV,FALSE,wk->poke.camera_p);

		GFC_SetCameraClip(TD_TITLE_CAMERA_CLIP_NEAR,TD_TITLE_CAMERA_CLIP_FAR,wk->poke.camera_p);
		GFC_SetCameraView(GF_CAMERA_PERSPECTIV,wk->poke.camera_p);
		GFC_AttachCamera(wk->poke.camera_p);
	}
	{
		//ライトセット
		NNS_G3dGlbLightVector(0, wk->lv0.x, wk->lv0.y, wk->lv0.z );
		NNS_G3dGlbLightColor(0, 0x7fff);
		NNS_G3dGlbLightVector(1, wk->lv1.x, wk->lv1.y, wk->lv1.z );
		NNS_G3dGlbLightColor(1, 0x7fff);
	}
	{
		G3X_AntiAlias( TRUE );
	}

	//３Ｄ描画スイッチ反転
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();
	wk->poke.Draw3Dsw = DRAW3D_ENABLE;

	return TRUE;
}

//----------------------------------
// 導入
//----------------------------------
static void Title2DGraphicSetEffect(GF_BGL_INI* ini,int heapID, TITLE_TITLEDEMO_WORK* wk );
enum{
	TDSEQ_TITLE_EF_STARTWAIT = 0,			//開始ウェイト
	TDSEQ_TITLE_EF_DISPON,					//描画開始
	TDSEQ_TITLE_EF_FLUSH0_1,				//フラッシュ(通常→白)
	TDSEQ_TITLE_EF_FLUSH0_2,				//フラッシュ(白→通常)
	TDSEQ_TITLE_EF_FLUSHWAIT,				//フラッシュウェイト
	TDSEQ_TITLE_EF_FLUSH1_1,				//フラッシュ(通常→白)
	TDSEQ_TITLE_EF_FLUSH1_2,				//フラッシュ(白→通常)
	TDSEQ_TITLE_EF_CAMERAMOVESTART,			//カメラ移動開始ウエイト
	TDSEQ_TITLE_EF_CAMERAMOVE,				//カメラ移動
	TDSEQ_TITLE_EF_CAMERAMOVE_END,			//カメラ移動終了
};

static BOOL TitleDemo_DispOnEffect( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID )
{
	BOOL result = FALSE;

	if( TitleDemoSkipCheck() == TRUE ){	//スキップ判定
		WIPE_SYS_ExeEnd();				//ワイプ強制解除
		return TRUE;
	}

	switch(wk->seq){

	case TDSEQ_TITLE_EF_STARTWAIT:
		MAINFRAME_ON(GX_PLANEMASK_BG0)	//３Ｄ面ＯＮ
		MAINFRAME_ON(GX_PLANEMASK_BG3)	//MainDisp背景ＯＮ
		TITLE_LOGO2_FRAME_ON

		wk->l1efseq = TDSEQ_LIGHT1_INIT;
		wk->wait_counter = 15;
		WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEIN,WIPE_TYPE_FADEIN,
						WIPE_FADE_WHITE, 15, 3, heapID );

		wk->seq = TDSEQ_TITLE_EF_DISPON;
		break;

	case TDSEQ_TITLE_EF_DISPON:
		if(WIPE_SYS_EndCheck() == TRUE){	//輝度変更待ち
			if( wk->wait_counter ){
				wk->wait_counter--;
			} else {
				wk->wait_counter = 2;
				wk->seq = TDSEQ_TITLE_EF_FLUSH0_1;
			}		
		}
		break;

	case TDSEQ_TITLE_EF_FLUSH0_1:
		if( FLUSH_WAIT ){	//輝度変更待ち
			if(wk->wait_counter){
				FLUSH_SET( 10, BRIGHTNESS_WHITE, BRIGHTNESS_NORMAL )
				wk->l1efseq = TDSEQ_LIGHT1_UP;

				wk->wait_counter--;
				wk->seq = TDSEQ_TITLE_EF_FLUSH0_2;
			}else{
				wk->wait_counter = 0;
				wk->seq = TDSEQ_TITLE_EF_FLUSHWAIT;
			}
		}
		break;

	case TDSEQ_TITLE_EF_FLUSH0_2:
		if( FLUSH_WAIT ){	//輝度変更待ち
			FLUSH_SET( 10, BRIGHTNESS_NORMAL, BRIGHTNESS_WHITE )
			wk->l1efseq = TDSEQ_LIGHT1_DOWN;

			wk->seq = TDSEQ_TITLE_EF_FLUSH0_1;
		}
		break;

	case TDSEQ_TITLE_EF_FLUSHWAIT:
		if( wk->wait_counter ){
			wk->wait_counter--;
		} else {
			wk->wait_counter = 1;
			wk->seq = TDSEQ_TITLE_EF_FLUSH1_1;
		}
		break;

	case TDSEQ_TITLE_EF_FLUSH1_1:
		if(WIPE_SYS_EndCheck() == TRUE){	//輝度変更待ち
			if(wk->wait_counter){
				WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEOUT,WIPE_TYPE_FADEOUT,
								WIPE_FADE_WHITE,FLUSH_WIPE_DIV,FLUSH_WIPE_SYNC,heapID);
				wk->l1efseq = TDSEQ_LIGHT1_UP;

				wk->wait_counter--;
				wk->seq = TDSEQ_TITLE_EF_FLUSH1_2;
			}else{
				wk->wait_counter = 40;
				wk->seq = TDSEQ_TITLE_EF_CAMERAMOVESTART;
			}
		}
		break;

	case TDSEQ_TITLE_EF_FLUSH1_2:
		if(WIPE_SYS_EndCheck() == TRUE){	//輝度変更待ち
			Title2DGraphicSetEffect(bgl,heapID,wk);
			WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEIN,WIPE_TYPE_FADEIN,
							WIPE_FADE_WHITE,16,3,heapID);
			wk->seq = TDSEQ_TITLE_EF_FLUSH1_1;
		}
		break;

	case TDSEQ_TITLE_EF_CAMERAMOVESTART:
		if( wk->wait_counter ){
			wk->wait_counter--;
			if( wk->wait_counter == 15 ){
				wk->poke.anm_flag = DRAW3DANM_ENABLE;
			}
		} else {
			wk->seq = TDSEQ_TITLE_EF_CAMERAMOVE;
		}
		break;

	case TDSEQ_TITLE_EF_CAMERAMOVE:
		{
			BOOL move_flag = TRUE;

			CAMERA_MOVE( wk->camera_tpos.x, wk->tp_ed.x, wk->c_speed, move_flag )
			CAMERA_MOVE( wk->camera_tpos.y, wk->tp_ed.y, wk->c_speed, move_flag )
			CAMERA_MOVE( wk->camera_tpos.z, wk->tp_ed.z, wk->c_speed, move_flag )

			CAMERA_MOVE( wk->camera_cpos.x, wk->cp_ed.x, wk->c_speed, move_flag )
			CAMERA_MOVE( wk->camera_cpos.y, wk->cp_ed.y, wk->c_speed, move_flag )
			CAMERA_MOVE( wk->camera_cpos.z, wk->cp_ed.z, wk->c_speed, move_flag )

			//カメラの位置と焦点を設定
			GFC_SetLookTarget( &wk->camera_tpos, wk->poke.camera_p );
			GFC_SetCameraPos( &wk->camera_cpos, wk->poke.camera_p );

			if( move_flag == TRUE ){
				TITLE_LOGO_FRAME_ON
				TITLE_LOGO2_FRAME_OFF
				TITLE_CPRIGHT_FRAME_ON
				SUBFRAME_ON(GX_PLANEMASK_BG3)
				wk->wait_counter = 90;
				wk->poke.anm_flag = DRAW3DANM_STOP;
				wk->seq = TDSEQ_TITLE_EF_CAMERAMOVE_END;
			}
		}
		break;

	case TDSEQ_TITLE_EF_CAMERAMOVE_END:
		if(wk->wait_counter){
			wk->wait_counter--;
		} else {
			result = TRUE;
		}
		break;
	}
	TitleDemoLight1Effect( wk );
	Title3D_Draw(&wk->poke);

	return result;
}

//----------------------------------
// メイン
//----------------------------------
enum{
	TDSEQ_TITLE_MAIN_DISPON = 0,		//描画開始
	TDSEQ_TITLE_MAIN_CONT,				//メイン演出
};

static BOOL TitleDemo_Main( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID )
{
	BOOL result = FALSE;

	switch(wk->seq){

	case TDSEQ_TITLE_MAIN_DISPON:
		//すべての描画をＯＮ(スキップされることを考慮)
		GFC_SetLookTarget( &wk->tp_ed, wk->poke.camera_p );
		GFC_SetCameraPos( &wk->cp_ed, wk->poke.camera_p );

		MAINFRAME_ON(GX_PLANEMASK_BG0)	//３Ｄ面ＯＮ
		MAINFRAME_ON(GX_PLANEMASK_BG3)	//MainDisp背景ＯＮ
		SUBFRAME_ON(GX_PLANEMASK_BG3)	//SubDisp背景ＯＮ

		TITLE_LOGO_FRAME_ON
		TITLE_LOGO2_FRAME_OFF
		TITLE_CPRIGHT_FRAME_ON

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );
		SetBrightness(  BRIGHTNESS_NORMAL, 
						(GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2),
						MASK_MAIN_DISPLAY );
		SetBrightness(  BRIGHTNESS_NORMAL, 
						(GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2),
						MASK_SUB_DISPLAY );
		wk->poke.anm_flag = DRAW3DANM_ENABLE;
		NNS_G3dGlbLightColor(1, 0x7fff);

		wk->wait_counter = 0;
		wk->seq = TDSEQ_TITLE_MAIN_CONT;
		break;

	case TDSEQ_TITLE_MAIN_CONT:
		if( wk->enable_flag == TRUE ){
			if(wk->wait_counter == 0 ){
				TITLE_PRSSTART_FRAME_ON
			}else if(wk->wait_counter == 0x10 ){
				TITLE_PRSSTART_FRAME_OFF
			}
		} else {
			TITLE_PRSSTART_FRAME_OFF
		}
		wk->wait_counter++;
		wk->wait_counter&=0x1f;
	
		result = TRUE;
		break;
	}
	Title3D_Draw(&wk->poke);

	return result;
}

//----------------------------------
// 終了
//----------------------------------
static BOOL TitleDemo_Exit( TITLE_TITLEDEMO_WORK* wk, GF_BGL_INI* bgl,int heapID )
{
	GFC_FreeCamera(wk->poke.camera_p);				//カメラ開放
	Title3D_ModelRelease( &wk->poke );
	Title2DGraphicRelease(bgl,heapID,wk);
	G2_BlendNone();
	G3X_EdgeMarking(FALSE);

	//３Ｄ描画スイッチ復帰
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();

	return TRUE;
}

//----------------------------------
// ２ＤＢＧ読み込み
//----------------------------------
static void Title2DGraphicSet(GF_BGL_INI* ini,int heapID, TITLE_TITLEDEMO_WORK* wk )
{
	{	// 背景
		int palIDm,palIDs;

		ArcUtil_BgCharSet//上画面キャラ	(反転してるのでSubDisp)
			(ARC_TITLE,NARC_titledemo_title_back_m_NCGR,ini,GF_BGL_FRAME3_S,0,0,0,heapID);
		ArcUtil_BgCharSet	//下画面キャラ(反転してるのでMainDisp)
			(ARC_TITLE,NARC_titledemo_title_back_s_NCGR,ini,GF_BGL_FRAME3_M,0,0,0,heapID);
		ArcUtil_ScrnSet		//上画面スクリーン(反転してるのでSubDisp)
			(ARC_TITLE,NARC_titledemo_title_back_m_NSCR,ini,GF_BGL_FRAME3_S,0,0,0,heapID);
		ArcUtil_ScrnSet		//下画面スクリーン(反転してるのでMainDisp)
			(ARC_TITLE,NARC_titledemo_title_back_s_NSCR,ini,GF_BGL_FRAME3_M,0,0,0,heapID);

		if( CasetteVersion == VERSION_DIAMOND ){
			palIDm = NARC_titledemo_title_back_m_d_NCLR;
			palIDs = NARC_titledemo_title_back_s_d_NCLR;
		} else {
			palIDm = NARC_titledemo_title_back_m_p_NCLR;
			palIDs = NARC_titledemo_title_back_s_p_NCLR;
		}
		ArcUtil_PalSet(ARC_TITLE,palIDm,PALTYPE_SUB_BG,0,0,heapID);		//上画面パレット
		ArcUtil_PalSet(ARC_TITLE,palIDs,PALTYPE_MAIN_BG,0,0,heapID);	//下画面パレット
	}
	{	// ロゴ
		int cgxID,palID;

		if( CasetteVersion == VERSION_DIAMOND ){
			cgxID = NARC_titledemo_logo_d_NCGR;
			palID = NARC_titledemo_logo_d_NCLR;
		} else {
			cgxID = NARC_titledemo_logo_p_NCGR;
			palID = NARC_titledemo_logo_p_NCLR;
		}
		ArcUtil_BgCharSet(ARC_TITLE,cgxID,ini,TITLE_LOGO_FRAME,0,0,0,heapID);	//キャラ
		ArcUtil_PalSet(ARC_TITLE,palID,TITLE_LOGO_PALTYPE,EX_PAL_SLOT2_ADRS,0,heapID);
		ArcUtil_ScrnSet		//スクリーン
			(ARC_TITLE,NARC_titledemo_logo_NSCR,ini,TITLE_LOGO_FRAME,0,0,0,heapID);
	}
	{	// ロゴ２（モノトーン）
		ArcUtil_BgCharSet(	ARC_OP_DEMO,NARC_op_demo_g_logo2_NCGR,
							ini,TITLE_LOGO2_FRAME,0,0,0,heapID);	//キャラ
		ArcUtil_PalSet(		ARC_OP_DEMO,NARC_op_demo_g_logo2_NCLR,
							TITLE_LOGO_PALTYPE,EX_PAL_SLOT1_ADRS,0,heapID);
		ArcUtil_ScrnSet		//スクリーン
			(ARC_OP_DEMO,NARC_op_demo_g_logo_NSCR,ini,TITLE_LOGO2_FRAME,0,0,0,heapID);
	}
	{	// copyright
		ArcUtil_BgCharSet	//キャラ
			(ARC_TITLE,NARC_titledemo_title_cpright_NCGR,ini,TITLE_CPRIGHT_FRAME,0,0,0,heapID);
		ArcUtil_ScrnSet		//スクリーン
			(ARC_TITLE,NARC_titledemo_title_cpright_NSCR,ini,TITLE_CPRIGHT_FRAME,0,0,0,heapID);
		ArcUtil_PalSet		//パレット(ガイドウインドウ用込み)
			(ARC_TITLE,NARC_titledemo_title_cpright_NCLR,TITLE_GF_PALTYPE,32*1,32*3,heapID);
	}
	GF_BGL_BackGroundColorSet(GF_BGL_FRAME0_M,0x0000);
	GF_BGL_BackGroundColorSet(GF_BGL_FRAME0_S,0x0000);

	{	// ガイドメッセージ
		MSGDATA_MANAGER*	msg_man;
		STRBUF*				title_str;

		GF_BGL_ClearCharSet( TITLE_PRSSTART_FRAME, 32, 0, heapID );

		msg_man = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_title_dat,heapID );
		title_str = STRBUF_Create(64, heapID);

		//メッセージウインドウビットマップ作成
		GF_BGL_BmpWinAddEx(ini,&wk->msgwin,&TitleMsgWinData );
		//メッセージウインドウのクリア bmp,col,startX,startY,sizeX,sizeY
		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_NULL,0,0,28*DOTSIZE,2*DOTSIZE);
		//文字列の取得（Ａボタンを押してください）
		MSGMAN_GetString(msg_man,title_msg_01,title_str);
		//文字列の表示
		GF_STR_PrintExpand(&wk->msgwin,FONT_SYSTEM,title_str,0x28,0,MSG_ALLPUT,
							GF_PRINTCOLOR_MAKE(1, 1, FBMP_COL_NULL),1,0,NULL);

		STRBUF_Delete(title_str);
		MSGMAN_Delete(msg_man);
		{
			u16 letter = 0x0015;
			u16 shadow = 0x0015;

			GF_BGL_PaletteSet(TITLE_PRSSTART_FRAME,&letter,PAL1DATA,PAL1SIZE*2 + PAL1DATA*1);
			GF_BGL_PaletteSet(TITLE_PRSSTART_FRAME,&shadow,PAL1DATA,PAL1SIZE*2 + PAL1DATA*2);
		}
	}
}

static void Title2DGraphicSetEffect(GF_BGL_INI* ini,int heapID, TITLE_TITLEDEMO_WORK* wk )
{
	int cgxID,palID,scrID;

	if( wk->wait_counter == 0 ){
		if( CasetteVersion == VERSION_DIAMOND ){
			cgxID = NARC_op_demo_d_logo01_NCGR;
			palID = NARC_op_demo_d_logo01_NCLR;
			scrID = NARC_op_demo_d_logo01_NSCR;
		} else {
			cgxID = NARC_op_demo_P_logo01_NCGR;
			palID = NARC_op_demo_P_logo01_NCLR;
			scrID = NARC_op_demo_p_logo01_NSCR;
		}
		ArcUtil_BgCharSet( ARC_OP_DEMO, cgxID, ini, TITLE_LOGO2_FRAME, 0, 0, 0, heapID );
		ArcUtil_PalSet(	ARC_OP_DEMO, palID, TITLE_LOGO_PALTYPE, EX_PAL_SLOT1_ADRS, 0, heapID );
		ArcUtil_ScrnSet( ARC_OP_DEMO, scrID, ini, TITLE_LOGO2_FRAME, 0, 0, 0, heapID );
	}
}

static void Title2DGraphicRelease(GF_BGL_INI* ini,int heapID, TITLE_TITLEDEMO_WORK* wk )
{
	GF_BGL_BmpWinDel(&wk->msgwin);
}

//----------------------------------
// ライトエフェクト
//----------------------------------
#define LIGHT1_EF_SPEED (2)

static void TitleDemoLight1Effect( TITLE_TITLEDEMO_WORK* wk )
{
	switch( wk->l1efseq ){

	case TDSEQ_LIGHT1_INIT:
		wk->l1ef = 5;
		wk->l1efseq = TDSEQ_LIGHT1_WAIT;
		break;

	case TDSEQ_LIGHT1_WAIT:
		break;

	case TDSEQ_LIGHT1_UP:
		wk->l1ef += LIGHT1_EF_SPEED;
		if( wk->l1ef >= 0x1f ){
			wk->l1ef = 0x1f;
			wk->l1efseq = TDSEQ_LIGHT1_WAIT;
		}
		break;

	case TDSEQ_LIGHT1_DOWN:
		wk->l1ef -= LIGHT1_EF_SPEED;
		if( wk->l1ef <= 5 ){
			wk->l1ef = 5;
			wk->l1efseq = TDSEQ_LIGHT1_WAIT;
		}
		break;
	}
	NNS_G3dGlbLightColor( 1, 
		(((wk->l1ef<<0)&0x001f)|((wk->l1ef<<5)&0x03e0)|((wk->l1ef<<10)&0x7c00)) );
}

//----------------------------------
// バージョン分けデータ取得
//----------------------------------
//各種設定値（NitroViewer　で取得）

//ダイヤモンド
#define TD_TITLED_CMR_CPX_ST			(FX32_ONE * 0)
#define TD_TITLED_CMR_CPY_ST			(FX32_ONE * 65)//66)
#define TD_TITLED_CMR_CPZ_ST			(FX32_ONE * 72)//76)
#define TD_TITLED_CMR_TPX_ST			(FX32_ONE * 0)
#define TD_TITLED_CMR_TPY_ST			(FX32_ONE * 90)//128)
#define TD_TITLED_CMR_TPZ_ST			(FX32_ONE * 0)//-88)
	
#define TD_TITLED_CMR_CPX_ED			(FX32_ONE * 195)//332)
#define TD_TITLED_CMR_CPY_ED			(FX32_ONE * 32)//12)
#define TD_TITLED_CMR_CPZ_ED			(FX32_ONE * 246)//163)
#define TD_TITLED_CMR_TPX_ED			(FX32_ONE * -2)//-34)
#define TD_TITLED_CMR_TPY_ED			(FX32_ONE * 124)//122)
#define TD_TITLED_CMR_TPZ_ED			(FX32_ONE * -38)//-75)

#define TD_TITLED_L0_XV					(-2333)//(-1024)
#define TD_TITLED_L0_YV					(2603)//(0)
#define TD_TITLED_L0_ZV					(-2135)//(-4095)
#define TD_TITLED_L1_XV					(-2267)//(-1802)
#define TD_TITLED_L1_YV					(1953)//(2755)
#define TD_TITLED_L1_ZV					(-2797)//(-2438)

#define TD_TITLED_CMR_SPD				(FX32_ONE * 3)

#define TD_TITLED_ECOL_R				(1)
#define TD_TITLED_ECOL_G				(7)
#define TD_TITLED_ECOL_B				(9)

//パール
#define TD_TITLEP_CMR_CPX_ST			(FX32_ONE * -65)
#define TD_TITLEP_CMR_CPY_ST			(FX32_ONE * 41)
#define TD_TITLEP_CMR_CPZ_ST			(FX32_ONE * 19)
#define TD_TITLEP_CMR_TPX_ST			(FX32_ONE * 0)
#define TD_TITLEP_CMR_TPY_ST			(FX32_ONE * 11)
#define TD_TITLEP_CMR_TPZ_ST			(FX32_ONE * 18)
	
#define TD_TITLEP_CMR_CPX_ED			(FX32_ONE * -148)//-168)
#define TD_TITLEP_CMR_CPY_ED			(FX32_ONE * 58)//77)
#define TD_TITLEP_CMR_CPZ_ED			(FX32_ONE * 190)//178)
#define TD_TITLEP_CMR_TPX_ED			(FX32_ONE * 8)//0)
#define TD_TITLEP_CMR_TPY_ED			(FX32_ONE * -5)//-11)
#define TD_TITLEP_CMR_TPZ_ED			(FX32_ONE * 1)//16)

#define TD_TITLEP_L0_XV					(1619)//(4095)
#define TD_TITLEP_L0_YV					(-2276)//(-4095)
#define TD_TITLEP_L0_ZV					(-2296)//(1021)
#define TD_TITLEP_L1_XV					(2331)
#define TD_TITLEP_L1_YV					(-1183)
#define TD_TITLEP_L1_ZV					(3152)

#define TD_TITLEP_CMR_SPD				(FX32_ONE * 3)

#define TD_TITLEP_ECOL_R				(15)
#define TD_TITLEP_ECOL_G				(9)
#define TD_TITLEP_ECOL_B				(15)

static void TitleDemoDataGet( TITLE_TITLEDEMO_WORK* wk )
{
	if( CasetteVersion == VERSION_DIAMOND ){

		VEC_SET( wk->cp_st, TD_TITLED_CMR_CPX_ST, TD_TITLED_CMR_CPY_ST, TD_TITLED_CMR_CPZ_ST )
		VEC_SET( wk->cp_ed, TD_TITLED_CMR_CPX_ED, TD_TITLED_CMR_CPY_ED, TD_TITLED_CMR_CPZ_ED )

		VEC_SET( wk->tp_st, TD_TITLED_CMR_TPX_ST, TD_TITLED_CMR_TPY_ST, TD_TITLED_CMR_TPZ_ST )
		VEC_SET( wk->tp_ed, TD_TITLED_CMR_TPX_ED, TD_TITLED_CMR_TPY_ED, TD_TITLED_CMR_TPZ_ED )

		VEC_SET( wk->lv0, TD_TITLED_L0_XV, TD_TITLED_L0_YV, TD_TITLED_L0_ZV )
		VEC_SET( wk->lv1, TD_TITLED_L1_XV, TD_TITLED_L1_YV, TD_TITLED_L1_ZV )

		wk->c_speed = TD_TITLED_CMR_SPD;

	} else {

		VEC_SET( wk->cp_st, TD_TITLEP_CMR_CPX_ST, TD_TITLEP_CMR_CPY_ST, TD_TITLEP_CMR_CPZ_ST )
		VEC_SET( wk->cp_ed, TD_TITLEP_CMR_CPX_ED, TD_TITLEP_CMR_CPY_ED, TD_TITLEP_CMR_CPZ_ED )

		VEC_SET( wk->tp_st, TD_TITLEP_CMR_TPX_ST, TD_TITLEP_CMR_TPY_ST, TD_TITLEP_CMR_TPZ_ST )
		VEC_SET( wk->tp_ed, TD_TITLEP_CMR_TPX_ED, TD_TITLEP_CMR_TPY_ED, TD_TITLEP_CMR_TPZ_ED )

		VEC_SET( wk->lv0, TD_TITLEP_L0_XV, TD_TITLEP_L0_YV, TD_TITLEP_L0_ZV )
		VEC_SET( wk->lv1, TD_TITLEP_L1_XV, TD_TITLEP_L1_YV, TD_TITLEP_L1_ZV )

		wk->c_speed = TD_TITLEP_CMR_SPD;
	}
	{
		VecFx32 light0vec_tmp, light0vec;

		VEC_Subtract( &wk->tp_ed, &wk->cp_ed, &light0vec_tmp );
		VEC_Normalize( &light0vec_tmp, &light0vec );
		wk->lv0.x = light0vec.x;
		wk->lv0.y = light0vec.y;
		wk->lv0.z = light0vec.z;
	}
}




#ifdef PM_DEBUG
extern void SaveErrorWarningCall( int heapID, int msgID );
//----------------------------------
// デバッグ用
//----------------------------------
static void DebugControl( TITLE_TITLEDEMO_WORK* wk )
{
#if 0
	if( sys.trg & PAD_BUTTON_Y ){
		SaveErrorWarningCall(0,0);
	}
#endif
}
#endif













