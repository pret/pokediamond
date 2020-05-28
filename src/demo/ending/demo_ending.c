//============================================================================================
/**
 * @file	demo_ending.c
 * @brief	エンディングデモ　メイン
 * @author	taya
 * @date	2006.05.22
 */
//============================================================================================
#include "common.h"
#include "gflib\camera.h"
#include "system\procsys.h"
#include "system\msgdata.h"
#include "system\font_arc.h"
#include "system\brightness.h"
#include "system\clact_util.h"
#include "system\render_oam.h"
#include "system\snd_tool.h"
#include "savedata\zukanwork.h"
#include "poketool\monsno.h"

#include "msgdata\msg.naix"


#include "demo_ending_common.h"
#include "demo_ending_list.h"

#include "demo\demo_ending.h"


enum {
	HEAPSIZE_ENDING_DEMO = 0x30000,

};

enum {
	HERO_DEFAULT_XPOS = 200,
	HERO_DEFAULT_YPOS = 144 + DIFF_MAIN_SUB_LCD,

	STAFFLIST_MAIN_DEFAULT_POS = -240,
	STAFFLIST_SUB_DEFAULT_POS = STAFFLIST_MAIN_DEFAULT_POS-192-16,
};

typedef struct {
	void*		modelLoadPtr;
	void*		animLoadPtr;

	NNSG3dRenderObj		renderObj;
	NNSG3dResMdlSet*	modelSet;
	NNSG3dResMdl*		model;
	NNSG3dResTex*		texture;
	NNSG3dAnmObj*		anim;
	NNSFndAllocator		allocator;

	VecFx32		pos;
	VecFx32		scale;
	VecFx16		rot;

	fx32		animFrame;
	fx32		animEndFrame;

}GROUND_OBJ;


typedef struct {
	void* mainWk;
	int   seq;

	fx32 ev;
	fx32 ev_add;

}DISP_ENDSTR_WORK;


struct _ENDING_DEMO_WORK{
	PROC*				proc;
	GF_BGL_INI*			bgl;
	ENDING_LIST_WORK*	listWork;
	ENDING_LIST_WORK*	listWorkSub;
	BOOL				listEndFlag;
	MSGDATA_MANAGER*	msgMan;

	ENDING_PROC_PARAM*   procParam;
	BOOL                 skipFlag;

	GF_CAMERA_PTR	camera;
	VecFx32			cameraTarget;
	CAMERA_ANGLE	cameraAngle;
	GROUND_OBJ		objGround;

	CLACT_SET_PTR				actsys;
	CLACT_U_EASYRENDER_DATA		renddata;

	NNSG2dImageProxy	heroImgProxy;
	NNSG2dImageProxy	circleImgProxy;
	NNSG2dImageProxy	starImgProxy;
	NNSG2dImagePaletteProxy		heroPalProxy;
	NNSG2dImagePaletteProxy		circlePalProxy;
	NNSG2dImagePaletteProxy		starPalProxy;

	CLACT_WORK_PTR		heroActor;
	ENDING_CLANM_PACK*	heroClAnim;

	POKE_ACT_PARAM		pokeActParam[ MONSNO_END ];
	int					pokeActCount;

	int		sceneNumber;
	int		sceneSeq;
	void*	sceneWork;

	TCB_PTR		vintr_task;
	DISP_ENDSTR_WORK   endstrWork;
};




//==============================================================
// Prototype
//==============================================================
static void ending_vblank( void* wk_adrs );
static void ending_vintr_task( TCB_PTR tcb, void* wk_adrs );
static void setup_bg( ENDING_DEMO_WORK* wk );
static void cleanup_bg( ENDING_DEMO_WORK* wk );
static void setup_3d( ENDING_DEMO_WORK* wk );
static void cleanup_3d( ENDING_DEMO_WORK* wk );
static void setup_3d_reg( ENDING_DEMO_WORK* wk );
static void setup_3d_camera( ENDING_DEMO_WORK* wk );
static void cleanup_3d_camera( ENDING_DEMO_WORK* wk );
static void setup_3d_model( ENDING_DEMO_WORK* wk );
static void cleanup_3d_model( ENDING_DEMO_WORK* wk );
static void inline make_rot_matrix( MtxFx33* rotMtx, const VecFx16* rot );
static BOOL adjust_value16( fx16* val, int key, int unit, const char* str );
static void draw_3d( ENDING_DEMO_WORK* wk );
static void setup_obj_graphics( ENDING_DEMO_WORK* wk );
static void setup_obj( ENDING_DEMO_WORK* wk );
static void cleanup_obj( ENDING_DEMO_WORK* wk );
static void bgchange_task( TCB_PTR tcb, void* wk_ptr );
static void setup_pokeActParam( ENDING_DEMO_WORK* wk );
static void disp_endstr_init( DISP_ENDSTR_WORK* wk, ENDING_DEMO_WORK* mainWk );
static BOOL disp_endstr( DISP_ENDSTR_WORK* wk );



//-------------------------------------------------
/**
 *	各シーンの初期化・メイン・終了関数テーブル
 */
//-------------------------------------------------
typedef void* (*pSceneInitProc)(ENDING_DEMO_WORK*, GF_BGL_INI*);
typedef BOOL  (*pSceneInitWaitProc)(void*, int* seq);
typedef BOOL  (*pSceneMainProc)(void*, int* seq);
typedef BOOL  (*pSceneQuitProc)(void*, int* seq);

static const struct {
	pSceneInitProc		init;
	pSceneInitWaitProc	initWait;
	pSceneMainProc		main;
	pSceneQuitProc		quit;
}SubSceneProc[] = {
	{ Ending_Scene1Init, Ending_Scene1InitWait, Ending_Scene1Main, Ending_Scene1Quit },
	{ Ending_Scene2Init, Ending_Scene2InitWait, Ending_Scene2Main, Ending_Scene2Quit },
	{ Ending_Scene3Init, Ending_Scene3InitWait, Ending_Scene3Main, Ending_Scene3Quit },
	{ Ending_Scene4Init, Ending_Scene4InitWait, Ending_Scene4Main, Ending_Scene4Quit },
	{ Ending_Scene5Init, Ending_Scene5InitWait, Ending_Scene5Main, Ending_Scene5Quit },
	{ Ending_Scene6Init, Ending_Scene6InitWait, Ending_Scene6Main, Ending_Scene6Quit },
	{ Ending_Scene7Init, Ending_Scene7InitWait, Ending_Scene7Main, Ending_Scene7Quit },
};



//------------------------------------------------------------------
/**
 * エンディングデモPROC初期化
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT EndingDemoProc_Init( PROC * proc, int * seq )
{
	ENDING_DEMO_WORK* wk;

	switch( *seq ){
	case 0:
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_ENDING_DEMO, HEAPSIZE_ENDING_DEMO );
		wk = PROC_AllocWork( proc, sizeof(ENDING_DEMO_WORK), HEAPID_ENDING_DEMO );
		if( wk )
		{
			sys_VBlankFuncChange( NULL, NULL );
			sys_HBlankIntrStop();

			GF_Disp_GX_VisibleControlInit();
			GF_Disp_GXS_VisibleControlInit();
			GX_SetVisiblePlane( 0 );
			GXS_SetVisiblePlane( 0 );

			wk->procParam = PROC_GetParentWork( proc );
			wk->skipFlag = FALSE;

			NNS_G2dInitOamManagerModule();
			REND_OAMInit( 0, 128, 0, 32, 0, 128, 0, 32, HEAPID_ENDING_DEMO );

			wk->actsys = CLACT_U_SetEasyInit( 128, &wk->renddata, HEAPID_ENDING_DEMO );
			CLACT_U_SetMainSurfaceMatrix( &(wk->renddata), 0, (DIFF_MAIN_SUB_LCD<<FX32_SHIFT) );
			CLACT_U_SetSubSurfaceMatrix( &(wk->renddata), 0, 0 );

			wk->proc = proc;
			setup_bg( wk );
			setup_3d( wk );
			setup_obj( wk );
			setup_pokeActParam( wk );

			wk->msgMan = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_stafflist_dat, HEAPID_ENDING_DEMO );
			wk->listWork = Ending_ListWork_Create( wk->bgl, STAFFLIST_MAIN_DEFAULT_POS, GF_BGL_FRAME1_M, COMMOM_FONT_PALPOS, wk->msgMan );
			wk->listWorkSub = Ending_ListWork_Create( wk->bgl, STAFFLIST_SUB_DEFAULT_POS, GF_BGL_FRAME1_S, COMMOM_FONT_PALPOS, wk->msgMan );
			wk->listEndFlag = FALSE;

			wk->sceneNumber = 0;
			wk->sceneSeq = 0;
			wk->sceneWork = SubSceneProc[0].init( wk, wk->bgl );

			Snd_DataSetByScene( SND_SCENE_ENDING, SEQ_BLD_ENDING, 1 );	//エンディング曲再生
			
			wk->vintr_task = VIntrTCB_Add( ending_vintr_task, wk, TASKPRI_OAM_TRANS );
			sys_VBlankFuncChange( ending_vblank, wk );
		}
		(*seq)++;
		break;

	case 1:
		wk = PROC_GetWork( proc );
		if( SubSceneProc[0].initWait( wk->sceneWork, &(wk->sceneSeq) ) )
		{
			wk->sceneSeq = 0;
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
					 WIPE_FADE_BLACK, SCENE_FADE_FRAMES, 1, HEAPID_ENDING_DEMO );
			(*seq)++;
		}
		break;

	case 2:
		if( WIPE_SYS_EndCheck() )
		{
			return PROC_RES_FINISH;
		}
		break;
	}
	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * エンディングデモPROC終了
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT EndingDemoProc_Quit( PROC * proc, int * seq )
{
	ENDING_DEMO_WORK* wk = PROC_GetWork( proc );

	switch( *seq ){
	case 0:
		{
		    OSIntrMode  old;
			old = OS_DisableInterrupts();
			TCB_Delete( wk->vintr_task );
			OS_RestoreInterrupts( old );
		}
		sys_VBlankFuncChange( NULL, NULL );
		(*seq)++;
		break;

	case 1:

		Ending_ListWork_Delete( wk->listWorkSub );
		Ending_ListWork_Delete( wk->listWork );
		MSGMAN_Delete( wk->msgMan );

		cleanup_obj( wk );
		cleanup_3d( wk );
		cleanup_bg( wk );
		(*seq)++;
		break;

	case 2:
		CLACT_DestSet( wk->actsys );
		REND_OAM_Delete();
		(*seq)++;
		break;

	case 3:
		PROC_FreeWork( proc );
		sys_DeleteHeap( HEAPID_ENDING_DEMO );
		return PROC_RES_FINISH;
	}

	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * エンディングデモPROCメイン
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT EndingDemoProc_Main( PROC * proc, int * seq )
{
	enum {
		SEQ_MAIN_CTRL = 0,
		SEQ_SCENE_END,
		SEQ_CHANGE_SCENE_START,
		SEQ_WAIT_SCENE_INIT,

		SEQ_WAIT_STAFFROLL_OUT,
		SEQ_WAIT_KEY,
		SEQ_WAIT_FADEOUT,

		SEQ_SKIP_START,
		SEQ_SKIP_WAIT_SCENE_QUIT,
		SEQ_SKIP_WAIT_FADEOUT,
		SEQ_SKIP_WAIT_FADEIN,
	};

	ENDING_DEMO_WORK* wk = PROC_GetWork( proc );

	Ending_ListWork_Scroll( wk->listWork, 1 );
	wk->listEndFlag = Ending_ListWork_Scroll( wk->listWorkSub, 1 );

	switch (*seq) {
	case SEQ_MAIN_CTRL:
		if( wk->skipFlag == FALSE )
		{
			if( sys.trg & PAD_BUTTON_START )
			{
				if( wk->procParam->clearFlag )
				{
					WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
						WIPE_FADE_BLACK, 16, 1, HEAPID_ENDING_DEMO );
					wk->skipFlag = TRUE;
					(*seq) = SEQ_SKIP_START;
					break;
				}
			}
		}

		if( SubSceneProc[wk->sceneNumber].main( wk->sceneWork, &(wk->sceneSeq) ) )
		{
			wk->sceneSeq = 0;
			(*seq) = SEQ_SCENE_END;
		}
		break;

	case SEQ_SCENE_END:
		if( SubSceneProc[wk->sceneNumber].quit( wk->sceneWork, &wk->sceneSeq ) )
		{
			if( ++(wk->sceneNumber) < NELEMS(SubSceneProc) )
			{
				wk->sceneSeq = 0;
				(*seq) = SEQ_CHANGE_SCENE_START;
			}
			else
			{
				(*seq) = SEQ_WAIT_STAFFROLL_OUT;
			}
		}
		break;

	case SEQ_CHANGE_SCENE_START:
		wk->sceneWork = SubSceneProc[wk->sceneNumber].init( wk, wk->bgl );
		wk->sceneSeq = 0;
		(*seq) = SEQ_WAIT_SCENE_INIT;
		break;

	case SEQ_WAIT_SCENE_INIT:
		if( SubSceneProc[wk->sceneNumber].initWait(wk->sceneWork, &(wk->sceneSeq)) )
		{
			wk->sceneSeq = 0;
			(*seq) = SEQ_MAIN_CTRL;
		}
		break;

	case SEQ_WAIT_STAFFROLL_OUT:
		if( wk->listEndFlag )
		{
			(*seq) = SEQ_WAIT_KEY;
		}
		break;

	case SEQ_WAIT_KEY:
		if( sys.trg & (PAD_BUTTON_A|PAD_BUTTON_START) )
		{
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
				 WIPE_FADE_BLACK, 8, 1, HEAPID_ENDING_DEMO );
			(*seq) = SEQ_WAIT_FADEOUT;
		}
		break;

	case SEQ_WAIT_FADEOUT:
		if( WIPE_SYS_EndCheck() )
		{
			return PROC_RES_FINISH;
		}
		break;

	case SEQ_SKIP_START:
		if( WIPE_SYS_EndCheck() )
		{
			wk->sceneSeq = 0;
			(*seq) = SEQ_SKIP_WAIT_SCENE_QUIT;
		}
		break;

	case SEQ_SKIP_WAIT_SCENE_QUIT:
		if( SubSceneProc[wk->sceneNumber].quit(wk->sceneWork, &wk->sceneSeq) )
		{
			Ending_ListWork_WriteEndStr( wk->listWorkSub, TRUE );
			Ending_ListWork_WriteCopyLights( wk->listWork );

			GX_SetVisibleWnd(GX_WNDMASK_NONE);
			GXS_SetVisibleWnd(GX_WNDMASK_NONE);


			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
					 WIPE_FADE_BLACK, SCENE_FADE_FRAMES, 1, HEAPID_ENDING_DEMO );

			(*seq) = SEQ_SKIP_WAIT_FADEIN;
		}
		break;

	case SEQ_SKIP_WAIT_FADEIN:
		if( WIPE_SYS_EndCheck() )
		{
			(*seq) = SEQ_WAIT_KEY;
		}
		break;

	}
	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * VBlank
 *
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ending_vblank( void* wk_adrs )
{
	ENDING_DEMO_WORK* wk = wk_adrs;

	draw_3d( wk );
}

static void ending_vintr_task( TCB_PTR tcb, void* wk_adrs )
{
	ENDING_DEMO_WORK* wk = wk_adrs;

	CLACT_Draw( wk->actsys );
	REND_OAMTrans();
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_bg( ENDING_DEMO_WORK* wk )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};

	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
	};

	static const GF_BGL_BGCNT_HEADER header1 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x18000,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_ENDING_DEMO );

	GF_Disp_SetBank( &SetBankData );

	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	GX_SetGraphicsMode( GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D );

	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_M, &header1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_S, &header1, GF_BGL_MODE_TEXT );

	ArcUtil_PalSetEx( ARC_ENDING, NARC_ending_font_nclr, PALTYPE_MAIN_BG, COMMOM_FONT_PALPOS*0x20,
		COMMOM_FONT_PALPOS*0x20, 0x20, HEAPID_ENDING_DEMO);
	ArcUtil_PalSetEx( ARC_ENDING, NARC_ending_font_nclr, PALTYPE_SUB_BG,  COMMOM_FONT_PALPOS*0x20,
		COMMOM_FONT_PALPOS*0x20, 0x20, HEAPID_ENDING_DEMO);

	G2_BlendNone();
	G2S_BlendNone();

	// スタッフロールの可視範囲設定
	G2_SetWnd0Position( 0, 94, 255, 192 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_ALL ^ GX_WND_PLANEMASK_BG1, TRUE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_ALL, TRUE );

	G2S_SetWnd0Position( 0, 0, 255, 24 );
	G2S_SetWnd0InsidePlane( GX_WND_PLANEMASK_ALL ^ GX_WND_PLANEMASK_BG1, TRUE );
	G2S_SetWndOutsidePlane( GX_WND_PLANEMASK_ALL, TRUE );


	GX_SetVisibleWnd(GX_WNDMASK_W0);
	GXS_SetVisibleWnd(GX_WNDMASK_W0);
}

static void cleanup_bg( ENDING_DEMO_WORK* wk )
{
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_S );

	sys_FreeMemoryEz( wk->bgl );
}

//------------------------------------------------------------------
/**
 * 3D描画処理初期化
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_3d( ENDING_DEMO_WORK* wk )
{
	setup_3d_reg( wk );
	setup_3d_camera( wk );
	setup_3d_model( wk );
}

//------------------------------------------------------------------
/**
 * 3D描画処理終了
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void cleanup_3d( ENDING_DEMO_WORK* wk )
{
	cleanup_3d_model( wk );
	cleanup_3d_camera( wk );
}


//------------------------------------------------------------------
/**
 * 3D描画処理初期化サブ（NitroSystem, レジスタ関連）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_3d_reg( ENDING_DEMO_WORK* wk )
{
	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);

	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(FALSE);		// アルファブレンド　オン

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

    NNS_GfdInitFrmTexVramManager(1, TRUE);
    NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);
}

//------------------------------------------------------------------
/**
 * 3D描画処理初期化サブ（カメラ作成）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_3d_camera( ENDING_DEMO_WORK* wk )
{
	enum {
		CAMERA_PEARCE	= FX_GET_ROTA_NUM(22),
		CAMERA_DISTANCE	= (300 << FX32_SHIFT)
	};

	CAMERA_ANGLE angle;
	VecFx32 up;

	wk->camera = GFC_AllocCamera( HEAPID_ENDING_DEMO );

	wk->cameraTarget.x = 0;
	wk->cameraTarget.y = 0;
	wk->cameraTarget.z = 0;

	wk->cameraAngle.x = FX_GET_ROTA_NUM(0);
	wk->cameraAngle.y = FX_GET_ROTA_NUM(0);
	wk->cameraAngle.z = FX_GET_ROTA_NUM(0);

	GFC_InitCameraTDA( 
			&(wk->cameraTarget),
			CAMERA_DISTANCE,
			&(wk->cameraAngle),
			CAMERA_PEARCE,
			GF_CAMERA_PERSPECTIV,
			TRUE,	
			wk->camera
	);


	up.x = 0;
	up.y = FX32_ONE;
	up.z = 0;
	GFC_SetCamUp( &up, wk->camera );

	GFC_AttachCamera( wk->camera );

	GFC_SetCameraClip( (0<<FX32_SHIFT), (1000<<FX32_SHIFT), wk->camera );
}

//------------------------------------------------------------------
/**
 * 3D描画処理終了サブ（カメラ破棄）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void cleanup_3d_camera( ENDING_DEMO_WORK* wk )
{
	GFC_FreeCamera( wk->camera );
}

//------------------------------------------------------------------
/**
 * 3D描画処理初期化サブ（モデルデータ読み込み）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_3d_model( ENDING_DEMO_WORK* wk )
{
	GROUND_OBJ* grnd = &(wk->objGround);
	u32  loadSize;

	grnd->modelLoadPtr = ArcUtil_LoadEx( ARC_ENDING, NARC_ending_end_grand02_nsbmd, FALSE,
				 HEAPID_ENDING_DEMO, ALLOC_TOP, &loadSize );
	DC_FlushRange( grnd->modelLoadPtr, loadSize );

	if( grnd->modelLoadPtr )
	{
		VEC_Set( &(grnd->scale), FX32_ONE, FX32_ONE, FX32_ONE );
		VEC_Set( &(grnd->pos), 0, -114<<FX32_SHIFT, 0 );
		VEC_Fx16Set( &(grnd->rot), 0x0000, 0x0a50, 0x0050 );

		grnd->modelSet	= NNS_G3dGetMdlSet( grnd->modelLoadPtr );
		grnd->model		= NNS_G3dGetMdlByIdx( grnd->modelSet, 0 );
		grnd->texture	= NNS_G3dGetTex( grnd->modelLoadPtr );

		LoadVRAMTexture( grnd->texture );
		BindTexture( grnd->modelLoadPtr, grnd->texture );

		NNS_G3dRenderObjInit( &grnd->renderObj, grnd->model );


		grnd->animLoadPtr = ArcUtil_LoadEx( ARC_ENDING, NARC_ending_end_grand01_nsbta, FALSE,
				HEAPID_ENDING_DEMO, ALLOC_TOP, &loadSize );

		if( grnd->animLoadPtr )
		{
			void *animRes;

			DC_FlushRange( grnd->animLoadPtr, loadSize );
			sys_InitAllocator( &(grnd->allocator), HEAPID_ENDING_DEMO, 32 );

			animRes = NNS_G3dGetAnmByIdx( grnd->animLoadPtr, 0 );
			grnd->anim = NNS_G3dAllocAnmObj( &(grnd->allocator), animRes, grnd->model );
			NNS_G3dAnmObjInit( grnd->anim, animRes, grnd->model, grnd->texture );
			NNS_G3dRenderObjAddAnmObj( &grnd->renderObj, grnd->anim );

			grnd->animFrame = 0;
			grnd->animEndFrame = NNS_G3dAnmObjGetNumFrame( grnd->anim );
		}
	}
}

//------------------------------------------------------------------
/**
 * 3D描画処理初期化サブ（モデルデータ破棄）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void cleanup_3d_model( ENDING_DEMO_WORK* wk )
{
	GROUND_OBJ* grnd = &(wk->objGround);

	if( grnd->animLoadPtr )
	{
		NNS_G3dFreeAnmObj( &(grnd->allocator), grnd->anim );
		sys_FreeMemoryEz( grnd->animLoadPtr );
	}

	if( grnd->modelLoadPtr )
	{
		sys_FreeMemoryEz( grnd->modelLoadPtr );
	}

}

//------------------------------------------------------------------
/**
 * 3D描画用の回転行列を生成
 *
 * @param   rotMtx		
 * @param   rot		
 *
 * @retval  void inline		
 */
//------------------------------------------------------------------
static void inline make_rot_matrix( MtxFx33* rotMtx, const VecFx16* rot )
{
	MtxFx33 tmpMtx;

	// 回転行列作成
	MTX_Identity33( rotMtx );
	MTX_RotX33( &tmpMtx, FX_SinIdx((u16)(rot->x)), FX_CosIdx((u16)(rot->x)) );
	MTX_Concat33( &tmpMtx, rotMtx, rotMtx );
	MTX_RotY33( &tmpMtx, FX_SinIdx((u16)(rot->y)), FX_CosIdx((u16)(rot->y)) );
	MTX_Concat33( &tmpMtx, rotMtx, rotMtx );
	MTX_RotZ33( &tmpMtx, FX_SinIdx((u16)(rot->z)), FX_CosIdx((u16)(rot->z)) );
	MTX_Concat33( &tmpMtx, rotMtx, rotMtx );
}


//------------------------------------------------------------------
/**
 * 3D描画
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void draw_3d( ENDING_DEMO_WORK* wk )
{
	enum {
		ANIM_SPEED = FX32_ONE / 2,
	};

	G3X_Reset();

	NNS_G3dGePushMtx();
	{
		GFC_CameraLookAt();

		{
			MtxFx33 rotMtx;
			GROUND_OBJ* obj = &(wk->objGround);

			make_rot_matrix( &rotMtx, &(obj->rot) );

			obj->animFrame += ANIM_SPEED;
			if( obj->animFrame >= obj->animEndFrame )
			{
				obj->animFrame -= obj->animEndFrame;
			}
			NNS_G3dAnmObjSetFrame( obj->anim, obj->animFrame );
			simple_3DModelDraw( &obj->renderObj, &obj->pos, &rotMtx, &obj->scale );
		}
	}
	NNS_G3dGePopMtx(1);

	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W );
}



//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 * @param   type		
 *
 */
//------------------------------------------------------------------
void Ending_Change3dGroundType( ENDING_DEMO_WORK* wk, int type )
{
	static const u16 modelData[] = {
		NARC_ending_end_grand01_nsbmd,
		NARC_ending_end_grand02_nsbmd,
		NARC_ending_end_grand03_nsbmd,
	};

	GROUND_OBJ* grnd = &(wk->objGround);
	u32 loadSize;

	if( grnd->modelLoadPtr )
	{
		sys_FreeMemoryEz( grnd->modelLoadPtr );
	}

	grnd->modelLoadPtr = ArcUtil_LoadEx( ARC_ENDING, modelData[type], FALSE,
				 HEAPID_ENDING_DEMO, ALLOC_TOP, &loadSize );

	if( grnd->modelLoadPtr )
	{
		DC_FlushRange( grnd->modelLoadPtr, loadSize );

		VEC_Set( &(grnd->scale), FX32_ONE, FX32_ONE, FX32_ONE );
		VEC_Set( &(grnd->pos), 0, -114<<FX32_SHIFT, 0 );
		VEC_Fx16Set( &(grnd->rot), 0x0000, 0x0a50, 0x0050 );

		grnd->modelSet	= NNS_G3dGetMdlSet( grnd->modelLoadPtr );
		grnd->model		= NNS_G3dGetMdlByIdx( grnd->modelSet, 0 );
		grnd->texture	= NNS_G3dGetTex( grnd->modelLoadPtr );

		LoadVRAMTexture( grnd->texture );
		BindTexture( grnd->modelLoadPtr, grnd->texture );

		NNS_G3dRenderObjInit( &grnd->renderObj, grnd->model );
	}
	if( grnd->animLoadPtr )
	{
		void *animRes;

		animRes = NNS_G3dGetAnmByIdx( grnd->animLoadPtr, 0 );
		NNS_G3dAnmObjInit( grnd->anim, animRes, grnd->model, grnd->texture );
		NNS_G3dRenderObjAddAnmObj( &grnd->renderObj, grnd->anim );

		grnd->animFrame = 0;
		grnd->animEndFrame = NNS_G3dAnmObjGetNumFrame( grnd->anim );
	}

}










//==============================================================================================
// OBJセットアップ
//==============================================================================================

static void setup_obj_graphics( ENDING_DEMO_WORK* wk )
{
	static const struct {
		u16  ncg;
		u16  ncl;
		u16  nce;
		u16  nan;
	}PlayerGraphicID[] = {
		{
			NARC_ending_end_hero_m_ncgr, NARC_ending_end_hero_m_nclr,
			NARC_ending_end_hero_m_ncer, NARC_ending_end_hero_m_nanr,
		},{
			NARC_ending_end_hero_f_ncgr, NARC_ending_end_hero_f_nclr,
			NARC_ending_end_hero_f_ncer, NARC_ending_end_hero_f_nanr,
		}
	};
	int idx;

	NNS_G2dInitImageProxy( &(wk->heroImgProxy) );
	NNS_G2dInitImageProxy( &(wk->circleImgProxy) );
	NNS_G2dInitImageProxy( &(wk->starImgProxy) );

	NNS_G2dInitImagePaletteProxy( &(wk->heroPalProxy) );
	NNS_G2dInitImagePaletteProxy( &(wk->circlePalProxy) );
	NNS_G2dInitImagePaletteProxy( &(wk->starPalProxy) );

	idx = (wk->procParam->playerSex == PM_FEMALE);

	ArcUtil_CharSysLoad( ARC_ENDING, PlayerGraphicID[idx].ncg, FALSE, CHAR_MAP_1D,
			0, NNS_G2D_VRAM_TYPE_2DMAIN, OBJ_CHARPOS_HERO*0x20, HEAPID_ENDING_DEMO, &wk->heroImgProxy );

	ArcUtil_PalSysLoad( ARC_ENDING, PlayerGraphicID[idx].ncl, NNS_G2D_VRAM_TYPE_2DMAIN, 
			OBJ_PALPOS_HERO*0x20, HEAPID_ENDING_DEMO, &(wk->heroPalProxy) );

	wk->heroClAnim = Ending_LoadCellAnim( ARC_ENDING, PlayerGraphicID[idx].nce, PlayerGraphicID[idx].nan );

}


static void setup_obj( ENDING_DEMO_WORK* wk )
{
	setup_obj_graphics( wk );

	{
		CLACT_HEADER  header;

		Ending_SetActHeader( &header, wk->heroClAnim, &wk->heroImgProxy, &wk->heroPalProxy, 1 );

		wk->heroActor = Ending_AddActor( wk, &header, HERO_DEFAULT_XPOS, HERO_DEFAULT_YPOS, ACTPRI_HERO,
			NNS_G2D_VRAM_TYPE_2DMAIN, FALSE );

		CLACT_SetAnmFlag( wk->heroActor, TRUE );
		CLACT_SetAnmFrame( wk->heroActor, FX32_ONE );
	}

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, TRUE);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, TRUE);

}

static void cleanup_obj( ENDING_DEMO_WORK* wk )
{
	CLACT_Delete( wk->heroActor );
	Ending_UnloadCellAnim( wk->heroClAnim );
}

//==============================================================================================
// BG半透明切り替えエフェクト処理
//==============================================================================================

struct _ENDING_BGCHANGE_WORK {
	ENDING_DEMO_WORK*  mainWork;
	TCB_PTR  task;

	void (*setBlendFunc)(int, int, int, int);
	void (*changeBlendFunc)(int, int);

	int  seq;
	int  underFrame;
	int  overFrame;
	int  underPlane;
	int  overPlane;
	int  wait;

	fx32 ev;
	fx32 ev_add;
};


//------------------------------------------------------------------
/**
 * BG半透明切り替えエフェクト開始
 *
 * @param   mainWk		メインワークポインタ
 * @param   main_sub	0: MAINLCD / 1: SUBLCD
 * @param   priority	0: BG2→BG3 / 1: BG3->BG2
 * @param   wait		エフェクトに使うフレーム数
 *
 * @retval  ENDING_BGCHANGE_WORK*		エフェクト管理ワーク
 */
//------------------------------------------------------------------
ENDING_BGCHANGE_WORK*  Ending_BGChange_Start( ENDING_DEMO_WORK* mainWk, int main_sub, int priority, int wait )
{
	static const struct {
		int  underFrame;
		int  overFrame;
		int  underPlane;
		int  overPlane;
	}target[2][2] = {
		// MAIN
		{ 
			{ GF_BGL_FRAME2_M, GF_BGL_FRAME3_M, GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG3 },	// BG2 -> BG3
			{ GF_BGL_FRAME3_M, GF_BGL_FRAME2_M, GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG2 },	// BG3 -> BG2
		},
		// SUB
		{
			{ GF_BGL_FRAME2_S, GF_BGL_FRAME3_S, GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3 },	// BG2 -> BG3
			{ GF_BGL_FRAME3_S, GF_BGL_FRAME2_S, GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG2 },	// BG3 -> BG2
		}
	};

	ENDING_BGCHANGE_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(ENDING_BGCHANGE_WORK) );
	if( wk )
	{
		wk->mainWork = mainWk;
		wk->wait = wait;

		wk->underFrame = target[main_sub][priority].underFrame;
		wk->overFrame  = target[main_sub][priority].overFrame;
		wk->underPlane = target[main_sub][priority].underPlane;
		wk->overPlane  = target[main_sub][priority].overPlane;

		if( main_sub == 0)
		{
			wk->setBlendFunc = G2_SetBlendAlpha;
			wk->changeBlendFunc = G2_ChangeBlendAlpha;
		}
		else
		{
			wk->setBlendFunc = G2S_SetBlendAlpha;
			wk->changeBlendFunc = G2S_ChangeBlendAlpha;
		}

		wk->ev = 0;
		wk->ev_add = (16<<FX32_SHIFT) / wait;

		wk->seq = 0;

		wk->task = VWaitTCB_Add( bgchange_task, wk, TASKPRI_BGCHANGE_EFFECT );
	}
	return wk;
}


//------------------------------------------------------------------
/**
 * エフェクト本体タスク
 *
 * @param   tcb		
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
static void bgchange_task( TCB_PTR tcb, void* wk_ptr )
{
	ENDING_BGCHANGE_WORK* wk = wk_ptr;

	switch( wk->seq ){
	case 0:
		wk->setBlendFunc( wk->overPlane, wk->underPlane, 0, 16 );
		wk->seq++;
		break;
	case 1:
		GF_BGL_PrioritySet( wk->overFrame, 2 );
		GF_BGL_PrioritySet( wk->underFrame, 3 );
		wk->seq++;
		break;
	case 2:
		wk->ev += wk->ev_add;
		{
			int ev = wk->ev >> FX32_SHIFT;
			if( ev >= 16 ){ ev = 16;}
			wk->changeBlendFunc( ev, (16-ev) );
			if( ev >= 16 )
			{
				wk->task = NULL;
				TCB_Delete( tcb );
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * BG半透明切り替えエフェクト終了待ち
 *
 * @param   wk		エフェクト管理ワークポインタ
 *
 * @retval  BOOL	TRUEが返ったら終了
 */
//------------------------------------------------------------------
BOOL Ending_BGChange_Wait( ENDING_BGCHANGE_WORK* wk )
{
	return wk->task == NULL;
}

//------------------------------------------------------------------
/**
 * BG半透明切り替えエフェクトワークの破棄
 *
 * @param   wk		エフェクト管理ワークポインタ
 */
//------------------------------------------------------------------
void Ending_BGChange_Quit( ENDING_BGCHANGE_WORK* wk )
{
	sys_FreeMemoryEz( wk );
}

//==============================================================================================
// セルアニメデータ管理
//==============================================================================================

struct _ENDING_CLANM_PACK {
	void*  cellLoadPtr;
	void*  animLoadPtr;
	NNSG2dCellDataBank*  cellData;
	NNSG2dAnimBankData*  animData;
};


ENDING_CLANM_PACK*  Ending_LoadCellAnim( u32 arcID, u32 cellDatID, u32 animDatID )
{
	ENDING_CLANM_PACK* pack = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(ENDING_CLANM_PACK) );
	if( pack )
	{
		pack->cellLoadPtr = ArcUtil_CellBankDataGet( arcID, cellDatID, FALSE, &(pack->cellData), HEAPID_ENDING_DEMO );
		pack->animLoadPtr = ArcUtil_AnimBankDataGet( arcID, animDatID, FALSE, &(pack->animData), HEAPID_ENDING_DEMO );
	}
	return pack;
}

void Ending_UnloadCellAnim( ENDING_CLANM_PACK* pack )
{
	if( pack )
	{
		if( pack->cellLoadPtr )
		{
			sys_FreeMemoryEz( pack->cellLoadPtr );
		}
		if( pack->animLoadPtr )
		{
			sys_FreeMemoryEz( pack->animLoadPtr );
		}
		sys_FreeMemoryEz( pack );
	}
}



//==============================================================================================
// アクター管理
//==============================================================================================



void Ending_SetActHeader( CLACT_HEADER* header, ENDING_CLANM_PACK* res,
	NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* pltProxy, u32 bgPri )
{
	header->pImageProxy = imgProxy;
	header->pPaletteProxy = pltProxy;
	header->pCellBank = res->cellData;
	header->pAnimBank = res->animData;
	header->priority = bgPri;

	header->pCharData = NULL;
	header->pMCBank = NULL;
	header->pMCABank = NULL;
	header->flag = FALSE;
}


CLACT_WORK_PTR Ending_AddActor( ENDING_DEMO_WORK* wk, CLACT_HEADER_PTR  actHeader, u32 x, u32 y, u32 actPri,
		 int drawArea, BOOL drawFlag )
{
	CLACT_ADD_SIMPLE  add;
	CLACT_WORK_PTR act;

	add.ClActSet = wk->actsys;
	add.ClActHeader = actHeader;
	add.mat.x = x * FX32_ONE;
	add.mat.y = y * FX32_ONE;
	add.mat.z = 0;
	add.pri = actPri;
	add.DrawArea = drawArea;
	add.heap = HEAPID_ENDING_DEMO;

	act = CLACT_AddSimple( &add );
	if( act )
	{
		CLACT_SetAnmFlag( act, TRUE );
		CLACT_SetAnmFrame( act, FX32_ONE );
		CLACT_SetDrawFlag( act, drawFlag );
	}
	return act;
}


CLACT_WORK_PTR  Ending_GetHeroActor( ENDING_DEMO_WORK* wk )
{
	return wk->heroActor;
}


//==============================================================================================
// 
//==============================================================================================

BOOL Ending_GetListEndFlag( ENDING_DEMO_WORK* wk )
{
	return wk->listEndFlag;
}

//==============================================================================================
// シーン３用にポケモンアクターパラメータをセットアップしておく
//（図鑑から捕まえた性別を取得する処理が重く、スタッフリストが流れている最中にやると処理落ちがバレる）
//==============================================================================================

static void setup_pokeActParam( ENDING_DEMO_WORK* wk )
{
	const ZUKAN_WORK* zw;
	int i, p;

	wk->pokeActCount = 3;	// 初期３体は必ず先頭に置くため、その分を空けておく
	zw = wk->procParam->zukanWork;

	for(i=1; i<MONSNO_END; i++)
	{
		// 初期３体スキップ
		if( (i==MONSNO_HIKOZARU) || (i==MONSNO_POTTYAMA) || (i==MONSNO_NAETORU) )
		{
			continue;
		}
		if( ZukanWork_GetPokeGetFlag( zw, i ) )
		{
			wk->pokeActParam[ wk->pokeActCount ].number = i;
			wk->pokeActParam[ wk->pokeActCount ].sex = ZukanWork_GetPokeSexFlag( zw, i, ZUKAN_WORK_SEX_FIRST );
			wk->pokeActParam[ wk->pokeActCount ].rand = gf_rand();
			wk->pokeActParam[ wk->pokeActCount ].form = ZukanWork_GetPokeForm( zw, i, 0 );
			wk->pokeActCount++;
		}
	}

	// 初期３体分を空けて、残りをシャッフル
	{
		POKE_ACT_PARAM  tmp;
		for(i=3; i<(wk->pokeActCount-1); i++)
		{
			p = 3 + gf_rand() % (wk->pokeActCount - i);
			tmp = wk->pokeActParam[i];
			wk->pokeActParam[i] = wk->pokeActParam[p];
			wk->pokeActParam[p] = tmp;
		}
	}

	// 初期３体を先頭に置く
	p = gf_rand() % 3;
	for(i=0; i<3; i++)
	{
		switch(p){
		case 0:  wk->pokeActParam[i].number = MONSNO_HIKOZARU; break;
		case 1:  wk->pokeActParam[i].number = MONSNO_POTTYAMA; break;
		case 2:  wk->pokeActParam[i].number = MONSNO_NAETORU;  break;
		}

		wk->pokeActParam[i].sex = ZukanWork_GetPokeSexFlag( zw, wk->pokeActParam[i].number, ZUKAN_WORK_SEX_FIRST );
		wk->pokeActParam[i].rand = gf_rand();
		wk->pokeActParam[i].form = ZukanWork_GetPokeForm( zw, wk->pokeActParam[i].number, 0 );
		if(++p >= 3){
			p = 0;
		}
	}
}

int EndingDemo_GetPokeActCount( ENDING_DEMO_WORK* wk )
{
	return wk->pokeActCount;
}

const POKE_ACT_PARAM* EndingDemo_GetPokeActParamTable( ENDING_DEMO_WORK* wk )
{
	return wk->pokeActParam;
}


//==============================================================================================
// シーン７の最後「おわり」を表示するための処理
//==============================================================================================

void EndingDemo_DispEndString_Start( ENDING_DEMO_WORK* wk )
{
	disp_endstr_init( &wk->endstrWork, wk );
}

BOOL EndingDemo_DispEndString_Wait( ENDING_DEMO_WORK* wk )
{
	return disp_endstr( &wk->endstrWork );
}


static void disp_endstr_init( DISP_ENDSTR_WORK* wk, ENDING_DEMO_WORK* mainWk )
{
	wk->seq = 0;
	wk->mainWk = mainWk;
	wk->ev = 0;
	wk->ev_add = (16 << FX32_SHIFT) / 64;
	G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_BG1, GX_BLEND_ALL, 0, 16 );
}

static BOOL disp_endstr( DISP_ENDSTR_WORK* wk )
{
	ENDING_DEMO_WORK* mainWk = wk->mainWk;

	switch( wk->seq ){
	case 0:
		Ending_ListWork_WriteEndStr( mainWk->listWorkSub, FALSE );
		wk->seq++;
		break;
	case 1:
		{
			int ev;
			wk->ev += wk->ev_add;
			ev = wk->ev >> FX32_SHIFT;
			if( ev >= 16 ){ ev = 16; }
			G2S_ChangeBlendAlpha( ev, (16-ev) );
			if( ev == 16 )
			{
				wk->seq++;
			}
		}
		break;

	default:
		return TRUE;
	}
	return FALSE;
}



