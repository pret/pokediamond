//============================================================================================
/**
 * @file	demo_trade_scene4.c
 * @brief	ポケモン交換デモ（シーン４：空からボールがドーンと落ちてくる）
 * @author	taya
 * @date	2006.04.18
 */
//============================================================================================
#include "demo_trade_common.h"
#include "demo_trade_3d.h"

#include "gflib\msg_print.h"
#include "gflib\calctool.h"
#include "system\window.h"
#include "system\font_arc.h"
#include "communication\wm_icon.h"

#include "..\ev_pokeselect.naix"

//======================================================================================================
//======================================================================================================
//======================================================================================================
// 動作を見ながら調整したいパラメータ群
//======================================================================================================

#ifdef RUNTIME_ADJUST
#define	DECLARE_VALUE(type, name, value)	static type name = value
#else
#define	DECLARE_VALUE(type, name, value)	enum { name = value }
#endif


DECLARE_VALUE( s16,		CAMERA_1ST_ANGLE,			0x18e3);	// これはシーン２と同じで良い
DECLARE_VALUE( s16,		CAMERA_2ND_ADD_ANGLE,		0x1150);

DECLARE_VALUE( fx32,	BALL_X_RANGE,				0x012800);
DECLARE_VALUE( fx32,	BALL_Y_RANGE,				0x018c00);
DECLARE_VALUE( fx32,	BALL_X_RANGE_MIN,			0x000800);
DECLARE_VALUE( fx32,	BALL_Y_RANGE_MIN,			0x000800);
DECLARE_VALUE( fx32,	BALL_SCALE_MIN,				0x000200);
DECLARE_VALUE( s32,		SPIN_SHRINK_FRAMES,			12);


DECLARE_VALUE( fx16,	BALL_SPIN_ROT_INIT,			0xd870);
DECLARE_VALUE( fx16,	BALL_SPIN_ROT_SPEED,		0xf550);

//DECLARE_VALUE( fx32,	BALL_END_Y,					0xfff50e00);
//DECLARE_VALUE( fx32,	BALL_END_Z,					0x000e2000);
DECLARE_VALUE( fx32,	BALL_END_Y,					0xfff3ce00);
DECLARE_VALUE( fx32,	BALL_END_Z,					0x000c9000);

DECLARE_VALUE( fx32,	BALL_DEFAULT_Y,				0x003d6c00);
DECLARE_VALUE( fx32,	BALL_DEFAULT_Z,				0xffe44000);

//DECLARE_VALUE( s32,		BALL_MOVE_FRAMES,			60);
DECLARE_VALUE( s32,		BALL_MOVE_FRAMES,			70);

DECLARE_VALUE( fx16,	BALL_START_X_ROT,			0x2000);

static BOOL SpinEnableFlag = TRUE;

//----------------------------------------------
/**
 *	定数
 */ 
//----------------------------------------------
enum {

	LINE_XPOS_MIN = 12,
	LINE_XPOS_MAX = 244,
	LINE_YPOS_MIN = -28,
	LINE_YPOS_MAX = (192*2)+DT_LCD_DIFF,
	LINE_XPOS_RANGE = (LINE_XPOS_MAX-LINE_XPOS_MIN),
	LINE_YPOS_RANGE = (LINE_YPOS_MAX-LINE_YPOS_MIN),

	LINE_YPOS_MIN_FX32 = (LINE_YPOS_MIN<<FX32_SHIFT),
	LINE_YPOS_MAX_FX32 = (LINE_YPOS_MAX<<FX32_SHIFT),

	LINE_ACTOR_YDIFF = 56,
	LINE_ACTOR_YDIFF_FX32 = LINE_ACTOR_YDIFF<<FX32_SHIFT,
};


enum {
	ACTID_STAR = 0,
	ACTID_MAX,
};

typedef struct {
	void*			sceneWork;
	TCB_PTR			tcb;
	DT3DMAN*		dt3dMan;
	DT3DOBJ*		obj;
	VecFx32			pos;
	VecFx32			spin_vec;
	VecFx32			disp_pos;
	VecFx16			rot;

	fx32			y_speed;
	fx32			z_speed;

	fx32			spinXrange;
	fx32			spinYrange;
	fx32			spinXrangeAdd;
	fx32			spinYrangeAdd;
	fx32			spinXrangeNext;
	fx32			spinYrangeNext;
	fx32			scale;
	fx32			scaleAdd;
	fx32			scaleNext;
	int				spinRangeShrinkTimer;


	int				seq;
	int				timer;
	int				mv_timer;

	fx16			spin_rot;
	fx16			spin_speed;

}BALL_MOVE_WORK;


typedef struct {
	DEMO_TRADE_WORK*  mainWork;
	int seq;
	int timer;
	BOOL					main_sub_switch_flag;

	DEMO_TRADE_CELLANIM		clpack;
	CLACT_WORK_PTR			act[ACTID_MAX];

	GF_BGL_INI*				bgl;

	DT3DMAN*				dt3dMan;
	DT3DOBJ*				objBall;

	TCB_PTR					ballMoveTask;
	BALL_MOVE_WORK			ballMoveWork;

}SCENE_WORK;


//==============================================================
// Prototype
//==============================================================
static void main_tail_proc( SCENE_WORK* wk );
static int subseq_setup( SCENE_WORK* wk, int* seq );
static int subseq_ball_fall( SCENE_WORK* wk, int* seq );
static void setup_bg_params( SCENE_WORK* wk );
static void cleanup_bg_params( SCENE_WORK* wk );
static void setup_3d_graphics( SCENE_WORK* wk );
static void cleanup_3d_graphics( SCENE_WORK* wk );
static void setup_actors( SCENE_WORK* wk);
static void cleanup_actors( SCENE_WORK* wk );
static void init_ballMoveWork( BALL_MOVE_WORK* wk );
static void quit_ballMoveWork( BALL_MOVE_WORK* wk );
static void setup_ballMoveTask( SCENE_WORK* wk, BALL_MOVE_WORK* bwk );
static BOOL wait_ballMoveTask( BALL_MOVE_WORK* bwk );
static void ballSpinRangeShrinkReq( BALL_MOVE_WORK* bwk, fx32 nextXrange, fx32 nextYrange, fx32 nextScale, int frames );
static void ballSpinMove( BALL_MOVE_WORK* bwk );
static void ballMoveTask( TCB_PTR tcb, void* wk_adrs );
static void ballMoveTaskDebug( TCB_PTR tcb, void* wk_adrs );
static void switch_main_sub( SCENE_WORK* wk );
static void scene5_vblank( void* wk_adrs );


//------------------------------------------------------------------
/**
 * シーン４ワーク構築
 *
 * @param   mainWork		
 *
 * @retval  void*		作成したシーン用ワークポインタ
 */
//------------------------------------------------------------------
void* DemoTrade_Scene4Init( DEMO_TRADE_WORK* mainWork )
{
	SCENE_WORK* wk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(SCENE_WORK) );
	if( wk )
	{
		int i;

		wk->mainWork = mainWork;
		wk->seq = 0;
		wk->bgl = DemoTrade_GetBgl(mainWork);
		wk->dt3dMan = NULL;
		wk->main_sub_switch_flag = FALSE;
		init_ballMoveWork( &(wk->ballMoveWork) );

		sys_VBlankFuncChange( scene5_vblank, wk );
	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン４ワーク破棄
 *
 * @param   void*		シーン用ワークポインタ
 */
//------------------------------------------------------------------
void DemoTrade_Scene4Quit( void* wk_adrs )
{
	SCENE_WORK* wk = wk_adrs;
	if( wk )
	{
		int i;

		sys_VBlankFuncChange( NULL, NULL );

		cleanup_bg_params( wk );
		cleanup_3d_graphics( wk );
		cleanup_actors( wk );
		quit_ballMoveWork( &(wk->ballMoveWork) );

		sys_FreeMemoryEz( wk );
	}
}
//------------------------------------------------------------------
/**
 * シーン４メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEでシーン終了
 */
//------------------------------------------------------------------
BOOL DemoTrade_Scene4Main( void* wk_adrs, int* seq )
{
	static int (* const subseq[])(SCENE_WORK*, int*) = {
		subseq_setup,
		subseq_ball_fall,
	};

	SCENE_WORK* wk = wk_adrs;

	if( (*seq) < NELEMS(subseq) )
	{
		if( subseq[*seq](wk, &(wk->seq)) )
		{
			(*seq)++;
			wk->seq = 0;
		}

//		main_tail_proc( wk );

		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------
/**
 * メインの最後に呼ばれる
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void main_tail_proc( SCENE_WORK* wk )
{
}



//------------------------------------------------------------------
/**
 * サブシーケンス：グラフィックセットアップ
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_setup( SCENE_WORK* wk, int* seq )
{
	setup_bg_params( wk );
	setup_3d_graphics( wk );
	setup_actors( wk );

	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, 8, 1, HEAPID_DEMO_TRADE_SUB );
	return TRUE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：ボールがギューンと落ちてくる
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_ball_fall( SCENE_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		if( WIPE_SYS_EndCheck() )
		{
			CLACT_AnmChg( wk->act[ACTID_STAR], ANM_STAR );
			CLACT_SetDrawFlag( wk->act[ACTID_STAR], TRUE );
			(*seq)++;
		}
		break;
	case 1:
		if( CLACT_AnmActiveCheck( wk->act[ACTID_STAR] ) == FALSE )
		{
			Snd_SePlay( SE_BALL_FALL );
			setup_ballMoveTask( wk, &(wk->ballMoveWork) );
			DT3D_SetObjDrawFlag( wk->objBall, TRUE );
			(*seq)++;
		}
		break;
	case 2:
		if( wait_ballMoveTask( &(wk->ballMoveWork) ) )
		{
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, 16, 1, HEAPID_DEMO_TRADE_SUB );
			(*seq)++;
		}
		break;
	case 3:
		if( WIPE_SYS_EndCheck() )
		{
			return TRUE;
		}
		break;

	}
	return FALSE;
}

//==============================================================================================
//==============================================================================================

static void setup_bg_params( SCENE_WORK* wk )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_23_G,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_32_H,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_16_F,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};
	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
	};

	static const GF_BGL_BGCNT_HEADER header3 = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x512, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 3, TRUE, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	u32 scrnArcID, cgxArcID, palArcID, palOfs;

	GF_Disp_SetBank( &SetBankData );

	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &header3, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_S, &header3, GF_BGL_MODE_TEXT );

	switch( DemoTrade_GetBGType(wk->mainWork) ){
	case DEMO_TRADE_BGTYPE_MORNING:
	default:
		scrnArcID = NARC_demo_trade_sky_lz_nscr;
		cgxArcID = NARC_demo_trade_sky_lz_ncgr;
		palArcID = NARC_demo_trade_sky_nclr;
		palOfs = 0x00;
		break;

	case DEMO_TRADE_BGTYPE_EVENING:
		scrnArcID = NARC_demo_trade_sky_lz_nscr;
		cgxArcID = NARC_demo_trade_sky_lz_ncgr;
		palArcID = NARC_demo_trade_sky_nclr;
		palOfs = 0x20;
		break;

	case DEMO_TRADE_BGTYPE_NIGHT:
		scrnArcID = NARC_demo_trade_sky_lz_nscr;
		cgxArcID = NARC_demo_trade_sky_lz_ncgr;
		palArcID = NARC_demo_trade_sky_nclr;
		palOfs = 0x40;
		break;

	case DEMO_TRADE_BGTYPE_WIFI:
		scrnArcID = NARC_demo_trade_tube_lz_nscr;
		cgxArcID = NARC_demo_trade_tube_lz_ncgr;
		palArcID = NARC_demo_trade_tube_nclr;
		palOfs = 0x00;
		break;
	}


	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, cgxArcID, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, cgxArcID, wk->bgl, GF_BGL_FRAME3_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );

	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, scrnArcID, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, scrnArcID, wk->bgl, GF_BGL_FRAME3_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );

	ArcUtil_PalSetEx( ARC_DEMO_TRADE_GRA, palArcID, PALTYPE_MAIN_BG, palOfs, 0, 0x20, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_PalSetEx( ARC_DEMO_TRADE_GRA, palArcID, PALTYPE_SUB_BG,  palOfs, 0, 0x20, HEAPID_DEMO_TRADE_SUB );

	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET,   0 );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_S, GF_BGL_SCROLL_Y_SET, 256 );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

	// Vramバンク設定によってアイコンを作り直す必要がある
	WirelessIconEasy();
	WirelessIconEasy_HoldLCD( TRUE, HEAPID_DEMO_TRADE_MAIN );
}
static void cleanup_bg_params( SCENE_WORK* wk )
{
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_S );
}



static void setup_3d_graphics( SCENE_WORK* wk )
{
	static const GXRgb edge_color_table[ 8 ] = {
		GX_RGB(4,4,4),GX_RGB(4,4,4),GX_RGB(4,4,4),GX_RGB(4,4,4),
		GX_RGB(4,4,4),GX_RGB(4,4,4),GX_RGB(4,4,4),GX_RGB(4,4,4),
	};
	int i;

	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(TRUE);		// アルファブレンド　オン

	// エッジマーキング
	G3X_EdgeMarking(TRUE);
	G3X_SetEdgeColorTable( edge_color_table );

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(31, 31, 16),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

	// マネージャがテクスチャイメージスロットを指定スロット分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmTexVramManager(1, TRUE);
		
	// マネージャがパレットを16KB分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(0);

	wk->dt3dMan = DT3DMAN_Create(1, 0, 0, 0);
	wk->objBall = DT3D_AddObj( wk->dt3dMan, 0, ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_psel_nsbmd,
						0, 0, 0 , FALSE );

	{
		CAMERA_ANGLE  angle;

		angle.x = CAMERA_1ST_ANGLE;
		angle.y = 0;
		angle.z = 0;
		DT3D_SetCameraAngleRev( wk->dt3dMan, &angle );

		angle.x = CAMERA_2ND_ADD_ANGLE;
		DT3D_AddCameraAngleRot( wk->dt3dMan, &angle );

		DT3D_SetCameraParse( wk->dt3dMan, FX_GET_ROTA_NUM(22)/2 );
		{
			VecFx32  pos;
			DT3D_GetCameraPos( wk->dt3dMan, &pos );
		}
	}
}

static void cleanup_3d_graphics( SCENE_WORK* wk )
{
	if( wk->dt3dMan )
	{
		DT3DMAN_Delete( wk->dt3dMan );
	}
}


//==============================================================================================
//==============================================================================================

static void setup_actors( SCENE_WORK* wk)
{
	NNSG2dImagePaletteProxy	palProxy;
	NNSG2dImageProxy		imgProxy;
	CLACT_HEADER			header;
	int i;

	DemoTrade_LoadCellAnimDatas( &wk->clpack, ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade01_lz_ncer, NARC_demo_trade_trade01_lz_nanr );

	NNS_G2dInitImagePaletteProxy(&palProxy);
	NNS_G2dInitImageProxy(&imgProxy);

	ArcUtil_CharSysLoad( ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj01_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DMAIN, 0, HEAPID_DEMO_TRADE_SUB, &imgProxy );

	ArcUtil_PalSysLoad( ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj01_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 0,
					HEAPID_DEMO_TRADE_SUB, &palProxy );

	DemoTrade_SetActHeader( &header, &wk->clpack, &imgProxy, &palProxy, 1 );

	wk->act[ACTID_STAR] = DemoTrade_AddActor(wk->mainWork, &header, 128, 96, 0, NNS_G2D_VRAM_TYPE_2DMAIN );
	CLACT_SetDrawFlag( wk->act[ACTID_STAR], FALSE );
}

static void cleanup_actors( SCENE_WORK* wk )
{
	int i;

	for(i=0; i<ACTID_MAX; i++)
	{
		if(wk->act[i])
		{
			CLACT_Delete(wk->act[i]);
		}
	}
	DemoTrade_UnloadCellAnimDatas( &wk->clpack );
}

//==============================================================================================
// ボール移動タスク
//==============================================================================================
static void init_ballMoveWork( BALL_MOVE_WORK* wk )
{
	wk->tcb = NULL;
}
static void quit_ballMoveWork( BALL_MOVE_WORK* wk )
{
	if( wk->tcb )
	{
		TCB_Delete(wk->tcb);
		wk->tcb = NULL;
	}
}
static void setup_ballMoveTask( SCENE_WORK* wk, BALL_MOVE_WORK* bwk )
{
	bwk->sceneWork = wk;
	bwk->obj = wk->objBall;
	bwk->dt3dMan = wk->dt3dMan;

	bwk->pos.x = 0;
	bwk->pos.y = BALL_DEFAULT_Y;
	bwk->pos.z = BALL_DEFAULT_Z;
	bwk->spin_rot = BALL_SPIN_ROT_INIT;
	bwk->spin_speed = BALL_SPIN_ROT_SPEED;

	bwk->y_speed = (BALL_END_Y - BALL_DEFAULT_Y) / BALL_MOVE_FRAMES;
	bwk->z_speed = (BALL_END_Z - BALL_DEFAULT_Z) / BALL_MOVE_FRAMES;

	bwk->seq = 0;
	bwk->timer = 0;
	bwk->mv_timer = 0;

	bwk->rot.x = BALL_START_X_ROT;
	bwk->rot.y = 0xe000;
	bwk->rot.z = 0;
	DT3D_SetObjRot( bwk->obj, &bwk->rot );

	bwk->scale = BALL_SCALE_MIN;
	bwk->spinXrange = BALL_X_RANGE_MIN;
	bwk->spinYrange = BALL_Y_RANGE_MIN;
	bwk->spinRangeShrinkTimer = 0;

	ballSpinRangeShrinkReq( bwk, BALL_X_RANGE, BALL_Y_RANGE, FX32_ONE, SPIN_SHRINK_FRAMES );

	ballSpinMove( bwk );
	DT3D_SetObjPos( bwk->obj, &(bwk->disp_pos) );
	DT3D_GetObjRot( bwk->obj, &(bwk->rot) );

	bwk->tcb = TCB_Add( ballMoveTask, bwk, TASKPRI_DEFAULT );
}
static BOOL wait_ballMoveTask( BALL_MOVE_WORK* bwk )
{
	return (bwk->tcb == NULL);
}

static void ballSpinRangeShrinkReq( BALL_MOVE_WORK* bwk, fx32 nextXrange, fx32 nextYrange, fx32 nextScale, int frames )
{
	if (frames )
	{
		bwk->spinXrangeAdd = (nextXrange - bwk->spinXrange) / frames;
		bwk->spinYrangeAdd = (nextYrange - bwk->spinYrange) / frames;
		bwk->scaleAdd = (nextScale - bwk->scale) / frames;
		bwk->spinXrangeNext = nextXrange;
		bwk->spinYrangeNext = nextYrange;
		bwk->scaleNext = nextScale;
		bwk->spinRangeShrinkTimer = frames;
	}
}


static void ballSpinMove( BALL_MOVE_WORK* bwk )
{
	if( SpinEnableFlag )
	{
		int angle;

		angle = (u16)(bwk->spin_rot) / (65536/360);
		if(angle >= 360){ angle -= 360; }

		bwk->spin_rot -= bwk->spin_speed;

		if( bwk->spinRangeShrinkTimer )
		{
			bwk->spinRangeShrinkTimer--;
			if(bwk->spinRangeShrinkTimer)
			{
				bwk->spinXrange += bwk->spinXrangeAdd;
				bwk->spinYrange += bwk->spinYrangeAdd;
				bwk->scale += bwk->scaleAdd;
			}
			else
			{
				bwk->spinXrange = bwk->spinXrangeNext;
				bwk->spinYrange = bwk->spinYrangeNext;
				bwk->scale = bwk->scaleNext;
			}
			DT3D_SetObjScale( bwk->obj, bwk->scale );
		}

		bwk->spin_vec.x = FX_Mul( FixSinCosTbl[90+angle], bwk->spinXrange );
		bwk->spin_vec.y = FX_Mul( FixSinCosTbl[angle], bwk->spinYrange );
		bwk->spin_vec.z = 0;

		bwk->rot.x -= 0x300;
		DT3D_SetObjRot( bwk->obj, &(bwk->rot) );

		VEC_Add( &bwk->spin_vec, &bwk->pos, &bwk->disp_pos );
	}
	else
	{
		bwk->disp_pos = bwk->pos;
	}
}
static void ballMoveTask( TCB_PTR tcb, void* wk_adrs )
{
	BALL_MOVE_WORK* bwk = wk_adrs;

	if( bwk->mv_timer < BALL_MOVE_FRAMES )
	{
		bwk->mv_timer++;
	}

	switch( bwk->seq ){
	case 0:
		ballSpinMove( bwk );
		DT3D_SetObjPos( bwk->obj, &(bwk->disp_pos) );
		if( ++(bwk->mv_timer) >= SPIN_SHRINK_FRAMES )
		{
			bwk->mv_timer = 0;
			bwk->seq++;
		}
		break;
	case 1:
		if( DT3D_CheckObjVisible( bwk->obj ) == FALSE )
		{
			switch_main_sub( bwk->sceneWork );
			bwk->seq++;
		}
		else
		{
			bwk->pos.y += bwk->y_speed;
			bwk->pos.z += bwk->z_speed;
			ballSpinMove( bwk );
			DT3D_SetObjPos( bwk->obj, &(bwk->disp_pos) );
		}
		break;
	case 2:
		bwk->pos.y += bwk->y_speed;
		bwk->pos.z += bwk->z_speed;
		ballSpinMove( bwk );
		DT3D_SetObjPos( bwk->obj, &(bwk->disp_pos) );
		if( bwk->mv_timer >= BALL_MOVE_FRAMES )
		{
			DT3D_SetObjDrawFlag( bwk->obj, FALSE );
			bwk->timer = 0;
			bwk->seq++;
		}
		break;
	case 3:
		if(++(bwk->timer) > 8)
		{
			#if 0
			OS_TPrintf("seq quit\n");
			bwk->seq = 0;
			TCB_ChangeFunc(tcb, ballMoveTaskDebug);
			#else
			bwk->tcb = NULL;
			TCB_Delete(tcb);
			#endif
		}
		break;
	}
}

static void ballMoveTaskDebug( TCB_PTR tcb, void* wk_adrs )
{
	BALL_MOVE_WORK* bwk = wk_adrs;

	if( bwk->seq == 0 )
	{

		bwk->seq++;
	}

	#ifdef RUNTIME_ADJUST
	do{
		if( sys.cont & PAD_BUTTON_X ){ if(DT_adjustValue32(&BALL_END_Z, 0x800, sys.repeat, "Ball End Z")) break; }
		if( sys.cont & PAD_BUTTON_L ){ if(DT_adjustValue32(&BALL_END_Y, 0x800, sys.repeat, "Ball End Y")) break; }
//		if( sys.cont & PAD_BUTTON_X ){ if(DT_adjustValue32(&BALL_DEFAULT_Z, 0x800, sys.repeat, "Ball Default Z")) break; }
//		if( sys.cont & PAD_BUTTON_L ){ if(DT_adjustValue32(&BALL_DEFAULT_Y, 0x800, sys.repeat, "Ball Default Y")) break; }

		if( sys.cont & PAD_BUTTON_A ){ if(DT_adjustValue32(&BALL_X_RANGE_MIN, 0x400, sys.repeat, "Ball X Range")) break; }
		if( sys.cont & PAD_BUTTON_B ){ if(DT_adjustValue32(&BALL_Y_RANGE_MIN, 0x400, sys.repeat, "Ball Y Range")) break; }


		if( sys.cont & PAD_BUTTON_R ){ if(DT_adjustValue16(&BALL_SPIN_ROT_INIT, 0x10, sys.repeat, "X Rot Init")) break; }

//		if( sys.cont & PAD_BUTTON_L ){ if(DT_adjustValue16(&CAMERA_1ST_ANGLE, 0x10, sys.repeat, "Camera Angle")) break; }
//		if( sys.cont & PAD_BUTTON_R ){ if(DT_adjustValue16(&CAMERA_2ND_ADD_ANGLE, 0x10, sys.repeat, "Camera 2nd Angle")) break; }

		if( sys.cont & PAD_BUTTON_START ){ if(DT_adjustValue32(&BALL_MOVE_FRAMES, 0x01, sys.repeat, "Ball Move Frames")) break; }

		if( (sys.cont & PAD_BUTTON_L) && (sys.trg & PAD_BUTTON_R) )
		{
			SpinEnableFlag ^= 1;
			OS_TPrintf( "spin enable flag = %d\n", SpinEnableFlag );
			return;
		}

		if( sys.repeat & PAD_KEY_UP )
		{
			CAMERA_ANGLE  angle;

			angle.x = -CAMERA_2ND_ADD_ANGLE;
			angle.y = 0;
			angle.z = 0;
			OS_TPrintf("cam x angle = %04x\n", (u16)(angle.x));
			DT3D_AddCameraAngleRot( bwk->dt3dMan, &angle );
			return;
		}
		if( sys.repeat & PAD_KEY_DOWN )
		{
			CAMERA_ANGLE  angle;

			angle.x = CAMERA_2ND_ADD_ANGLE;
			angle.y = 0;
			angle.z = 0;
			OS_TPrintf("cam x angle = %04x\n", (u16)(angle.x));
			DT3D_AddCameraAngleRot( bwk->dt3dMan, &angle );
			return;
		}

		return;

	}while(0);
	#endif



	bwk->pos.y = BALL_DEFAULT_Y;
	bwk->pos.z = BALL_DEFAULT_Z;
	bwk->spin_rot = BALL_SPIN_ROT_INIT;
	ballSpinMove( bwk );
	DT3D_SetObjPos( bwk->obj, &bwk->disp_pos );
}


//==============================================================================================
// メイン・サブLCD切り替え
//==============================================================================================
static void switch_main_sub( SCENE_WORK* wk )
{
	wk->main_sub_switch_flag = TRUE;
}

static void scene5_vblank( void* wk_adrs )
{
	SCENE_WORK* wk = wk_adrs;

	if( wk->dt3dMan )
	{
		G3X_Reset();

		DT3DMAN_Draw( wk->dt3dMan );

		/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	//	G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	}

	if( wk->main_sub_switch_flag )
	{
		CAMERA_ANGLE  angle;

		angle.x = -CAMERA_2ND_ADD_ANGLE;
		angle.y = 0;
		angle.z = 0;

		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 256 );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_S, GF_BGL_SCROLL_Y_SET,   0 );

		DT3D_AddCameraAngleRot( wk->dt3dMan, &angle );

		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
		wk->main_sub_switch_flag = FALSE;
	}
}
