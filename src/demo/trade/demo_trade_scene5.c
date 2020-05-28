//============================================================================================
/**
 * @file	demo_trade_scene5.c
 * @brief	ポケモン交換デモ（シーン５：落ちてきたボールがDSの中にスーッと消える）
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

#include "..\ev_pokeselect.naix"


//======================================================================================================
//======================================================================================================
//======================================================================================================
// 動作を見ながら調整したいパラメータ群
//======================================================================================================

#ifdef		RUNTIME_ADJUST
#define	DECLARE_VALUE(type, name, value)	static type name = value
#else
#define	DECLARE_VALUE(type, name, value)	enum { name = value }
#endif


DECLARE_VALUE(s32,		BG_MAIN_START_YOFS,		-384);
DECLARE_VALUE(s32,		BG_MAIN_END_YOFS,		   0);
DECLARE_VALUE(s32,		BG_SUB_START_YOFS,		-192);
DECLARE_VALUE(s32,		BG_SUB_END_YOFS,		 192);
DECLARE_VALUE(s32,		BG_SCROLL_FRAMES,		40);

DECLARE_VALUE(fx32,		BALL_START_YPOS,	(140 << FX32_SHIFT));
DECLARE_VALUE(fx32,		BALL_END_YPOS,		0x00032000);
DECLARE_VALUE(s32,		BALL_MOVE_FRAMES,	16);

DECLARE_VALUE(fx32,		DSOUT_END_RATIO,		0x400);
DECLARE_VALUE(fx32,		DSOUT_START_SPEED,		1);
DECLARE_VALUE(fx32,		DSOUT_RATIO_AC,			0x128);



//----------------------------------------------
/**
 *	定数
 */ 
//----------------------------------------------
enum {
	BALL_DEFAULT_X = 0,
	BALL_DEFAULT_Y = (80 << FX32_SHIFT),
	BALL_DEFAULT_Z = 0,

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


typedef struct {
	fx16	speed;
	fx16	speed_add;
	fx16	speed_next;
	u16		timer;
}BALL_ROT_SPEED;

enum {
	BALL_ROT_X,
	BALL_ROT_Y,
	BALL_ROT_Z,
};


typedef struct {
	DEMO_TRADE_WORK*  mainWork;
	int seq;
	int timer;

	GF_BGL_INI*				bgl;
	DT_WAVE_PALANM_CTRL*	palAnimCtrl;
	BOOL					palAnimRunFlag;
	DT_DSIMG_AFFINE_CTRL*	dsinCtrl;
	volatile BOOL			dsOutEndFlag;

	DT3DMAN*				dt3dMan;
	DT3DOBJ*				objBall;
	VecFx16					ballRot;

	TCB_PTR					ballMoveTask;
	TCB_PTR					backScrollTask;
	TCB_PTR					ballAlphaTask;


}SCENE_WORK;


//==============================================================
// Prototype
//==============================================================
static void main_tail_proc( SCENE_WORK* wk );
static int subseq_setup( SCENE_WORK* wk, int* seq );
static int subseq_ds_in( SCENE_WORK* wk, int* seq );
static int subseq_ds_out( SCENE_WORK* wk, int* seq );
static void setup_bg_params( SCENE_WORK* wk );
static void cleanup_bg_params( SCENE_WORK* wk );
static void setup_3d_graphics( SCENE_WORK* wk );
static void cleanup_3d_graphics( SCENE_WORK* wk );
static void start_background_scroll_task( SCENE_WORK* wk, TCB_PTR* pTcb );
static void background_scroll_task( TCB_PTR tcb, void* wk_adrs );
static void delete_background_scroll_task( TCB_PTR tcb );
static void start_ballin_task( SCENE_WORK* swk, TCB_PTR* pTcb );
static void ball_in_task( TCB_PTR tcb, void* wk_adrs );
static void delete_ballin_task( TCB_PTR tcb );
static void start_ballobj_alpha_task( DT3DOBJ* obj, int startAlpha, int endAlpha, int wait, TCB_PTR* pTcb );
static void obj_alpha_task(TCB_PTR tcb, void* wk_adrs);
static void delete_ballobj_alpha_task( TCB_PTR tcb );


//------------------------------------------------------------------
/**
 * シーンワーク構築
 *
 * @param   mainWork		
 *
 * @retval  void*		作成したシーン用ワークポインタ
 */
//------------------------------------------------------------------
void* DemoTrade_Scene5Init( DEMO_TRADE_WORK* mainWork )
{
	SCENE_WORK* wk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(SCENE_WORK) );
	if( wk )
	{
		int i;

		wk->mainWork = mainWork;
		wk->seq = 0;
		wk->bgl = DemoTrade_GetBgl(mainWork);
		wk->dt3dMan = NULL;
		wk->palAnimCtrl = NULL;
		wk->palAnimRunFlag = FALSE;
		wk->dsinCtrl = NULL;
		wk->ballMoveTask = NULL;
		wk->backScrollTask = NULL;
		wk->ballAlphaTask = NULL;
	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン１ワーク破棄
 *
 * @param   void*		シーン用ワークポインタ
 */
//------------------------------------------------------------------
void DemoTrade_Scene5Quit( void* wk_adrs )
{
	SCENE_WORK* wk = wk_adrs;
	if( wk )
	{
		int i;

		cleanup_bg_params( wk );
		cleanup_3d_graphics( wk );

		if( wk->ballMoveTask )
		{
			delete_ballin_task(wk->ballMoveTask);
		}
		if( wk->backScrollTask )
		{
			delete_background_scroll_task( wk->backScrollTask );
		}
		if( wk->ballAlphaTask )
		{
			delete_ballobj_alpha_task( wk->ballAlphaTask );
		}

		sys_FreeMemoryEz( wk );
	}
}
//------------------------------------------------------------------
/**
 * シーン１メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEでシーン終了
 */
//------------------------------------------------------------------
BOOL DemoTrade_Scene5Main( void* wk_adrs, int* seq )
{
	static int (* const subseq[])(SCENE_WORK*, int*) = {
		subseq_setup,
		subseq_ds_in,
		subseq_ds_out,
	};

	SCENE_WORK* wk = wk_adrs;

	if( (*seq) < NELEMS(subseq) )
	{
		if( subseq[*seq](wk, &(wk->seq)) )
		{
			(*seq)++;
			wk->seq = 0;
		}

		main_tail_proc( wk );

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
	if( wk->dt3dMan )
	{
		wk->ballRot.y += 0x1000;
		DT3D_SetObjRot( wk->objBall, &(wk->ballRot) );

		G3X_Reset();

		DT3DMAN_Draw( wk->dt3dMan );

		/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	//	G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	}
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
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
			WIPE_FADE_WHITE, 8, 1, HEAPID_DEMO_TRADE_SUB );
	return TRUE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：DSイメージとボールがスクロールして入ってくる
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_ds_in( SCENE_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		if( WIPE_SYS_EndCheck() )
		{
			wk->timer = 0;
			start_ballin_task( wk, &(wk->ballMoveTask) );
			(*seq)++;
		}
		break;

	case 1:
		if( ++(wk->timer) > 8 )
		{
			start_background_scroll_task( wk, &(wk->backScrollTask) );
			(*seq)++;
		}
		break;

	case 2:
		if( wk->backScrollTask == NULL && wk->ballMoveTask == NULL)
		{
			(*seq)++;
		}
		break;

	case 3:
		wk->palAnimCtrl = DT_WavePalAnm_Start( &(wk->palAnimRunFlag), -1 );
		wk->timer = 0;
		(*seq)++;
		break;

	case 4:
		if( ++(wk->timer) > 30 )
		{
			start_ballobj_alpha_task( wk->objBall, 31, 0, 40, &(wk->ballAlphaTask) );
			(*seq)++;
		}
		break;

	case 5:
		if( (wk->ballAlphaTask == NULL) )
		{
			DT_WavePalAnm_StopReq( wk->palAnimCtrl );
			(*seq)++;
		}
		break;

	case 6:
		if( wk->palAnimRunFlag == FALSE )
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：DSイメージ拡大しつつフェードアウト
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_ds_out( SCENE_WORK* wk, int* seq )
{
	#ifdef PM_DEBUG
	static int c = 0;
	#endif

	switch(*seq){
	case 0:
		wk->dsinCtrl = DT_DSAff_Start( wk->bgl, 0x1000, DSOUT_END_RATIO, DSOUT_START_SPEED,
				DSOUT_RATIO_AC, 1, &(wk->dsOutEndFlag) );
		wk->timer=0;
		(*seq)++;
		break;

	case 1:
		if( ++(wk->timer) > 13 )
		{
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK,
					 8, 1, HEAPID_DEMO_TRADE_SUB );
			#ifdef PM_DEBUG
			c = 0;
			#endif
			(*seq)++;
		}
		break;

	case 2:
		#ifdef PM_DEBUG
		if( c < 30 )
		{
			c++;
			OS_TPrintf("%02d : dsOutEnd  adrs:%08x, val=%d\n", c, &(wk->dsOutEndFlag), wk->dsOutEndFlag);
		}
		#endif

		if( WIPE_SYS_EndCheck() && (wk->dsOutEndFlag) )
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
			GX_DISPMODE_GRAPHICS, GX_BGMODE_4, GX_BGMODE_4, GX_BG0_AS_3D,
	};

	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_1024x1024, GX_BG_COLORMODE_256,
		GX_BG_SCRBASE_0xb000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, TRUE, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header3 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
		GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000,
		GX_BG_EXTPLTT_01, 3, TRUE, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const u16 palOfs[] = {
		0x20, 0x60, 0xa0, 0xe0,
	};
	u32 bgType;

	GF_Disp_SetBank( &SetBankData );

	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &header2, GF_BGL_MODE_AFFINE );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_S, &header2, GF_BGL_MODE_AFFINE );

	{
		// 波形BGのオフセットがズレることがあるので割り込みを止めてみる…
		OSIntrMode  oldIntr = OS_DisableInterrupts();
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &header3, GF_BGL_MODE_256X16 );
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_S, &header3, GF_BGL_MODE_256X16 );
		OS_RestoreInterrupts( oldIntr );
	}

	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_ds_lz_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_ds_lz_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_scene5_ds_lz_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_scene5_ds_lz_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );

	bgType = DemoTrade_GetBGType(wk->mainWork);

	ArcUtil_PalSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_ds_nclr, PALTYPE_MAIN_BG, 0, 0x20, HEAPID_DEMO_TRADE_SUB);
	ArcUtil_PalSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_ds_nclr, PALTYPE_SUB_BG, 0, 0x20, HEAPID_DEMO_TRADE_SUB);
	ArcUtil_PalSetEx(ARC_DEMO_TRADE_GRA, NARC_demo_trade_ds_nclr, PALTYPE_MAIN_BG, palOfs[bgType], 0x20, 0x40, HEAPID_DEMO_TRADE_SUB);
	ArcUtil_PalSetEx(ARC_DEMO_TRADE_GRA, NARC_demo_trade_ds_nclr, PALTYPE_SUB_BG, palOfs[bgType], 0x20, 0x40, HEAPID_DEMO_TRADE_SUB);

	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_wave_lz_ncgr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_wave_lz_ncgr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_wave_lz_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_wave_lz_nscr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );

	// 拡張パレットスロット３（オフセットは0x6000）を黒く潰しておく
	{
		u8* tmp = sys_AllocMemory(HEAPID_DEMO_TRADE_SUB, DT_WAVE_PAL_SIZE);
		if(tmp)
		{
			MI_CpuClear32(tmp, DT_WAVE_PAL_SIZE);
			DC_FlushRange(tmp, DT_WAVE_PAL_SIZE);

			GX_BeginLoadBGExtPltt();
			GXS_BeginLoadBGExtPltt();

			GX_LoadBGExtPltt( tmp, 0x6000, DT_WAVE_PAL_SIZE );
			GXS_LoadBGExtPltt( tmp, 0x6000, DT_WAVE_PAL_SIZE );

			GX_EndLoadBGExtPltt();
			GXS_EndLoadBGExtPltt();

			sys_FreeMemoryEz(tmp);
		}
	}

	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, BG_MAIN_START_YOFS );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, BG_SUB_START_YOFS );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 67 );

	GF_BGL_VisibleSet( GF_BGL_FRAME3_S, VISIBLE_OFF );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

//	wk->palAnimCtrl = DT_WavePalAnm_Start(&(wk->palAnimRunFlag));
//	wk->dsinCtrl = DT_DSAff_Start( wk->bgl, DSIN_START_RATIO, 0x1000, DSIN_RATIO_START_SPEED, DSIN_RATIO_AC, 0, &(wk->dsOutEndFlag) );
}
static void cleanup_bg_params( SCENE_WORK* wk )
{
	if( wk->palAnimRunFlag )
	{
		DT_WavePalAnm_Quit(wk->palAnimCtrl);
	}

	GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
	GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_S);
	GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_M);
	GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_S);
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
						BALL_DEFAULT_X, BALL_START_YPOS, BALL_DEFAULT_Z , TRUE );

	{
		static CAMERA_ANGLE  angle;

		angle.x = 0;
		angle.y = 0;
		angle.z = 0;
		DT3D_SetCameraAngleRev( wk->dt3dMan, &angle );

		DT3D_SetCameraView( wk->dt3dMan, GF_CAMERA_ORTHO );
//		DT3D_SetCameraDistance( wk->dt3dMan, CAMERA_DISTANCE );
		
	}

	DT3D_SetObjScale( wk->objBall, 0x2000 );
	DT3D_GetObjRot( wk->objBall, &wk->ballRot );
}

static void cleanup_3d_graphics( SCENE_WORK* wk )
{
	if( wk->dt3dMan )
	{
		DT3DMAN_Delete( wk->dt3dMan );
		wk->dt3dMan = NULL;
	}
}




//==============================================================================================
// 背景スクロール
//==============================================================================================
typedef struct {
	SCENE_WORK* sceneWork;
	GF_BGL_INI*	bgl;
	int			timer;
	fx32		mainY;
	fx32		subY;
	fx32		speed;
	fx32		scroll_val;
	TCB_PTR*	ptr_mine;
	TCB_PTR		tcb_eff;
}BG_SCROLL_WORK;

static void start_background_scroll_task( SCENE_WORK* wk, TCB_PTR* pTcb )
{
	BG_SCROLL_WORK*  twk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(BG_SCROLL_WORK) );
	if( twk )
	{
		twk->sceneWork = wk;
		twk->bgl = wk->bgl;

		twk->mainY = BG_MAIN_START_YOFS << FX32_SHIFT;
		twk->subY = BG_SUB_START_YOFS << FX32_SHIFT;
		twk->speed = ((BG_MAIN_END_YOFS - BG_MAIN_START_YOFS) << FX32_SHIFT) / BG_SCROLL_FRAMES;
		twk->timer = BG_SCROLL_FRAMES;
		twk->ptr_mine = pTcb;

		*pTcb = VIntrTCB_Add( background_scroll_task, twk, VINTR_TASKPRI_DEFAULT );
		if( *pTcb == NULL )
		{
			sys_FreeMemoryEz(twk);
		}
	}
}

static void background_scroll_task( TCB_PTR tcb, void* wk_adrs )
{
	BG_SCROLL_WORK* wk = wk_adrs;

	if( wk->timer )
	{
		wk->mainY += wk->speed;
		wk->subY += wk->speed;
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, (wk->mainY >> FX32_SHIFT) );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, (wk->subY  >> FX32_SHIFT) );
		wk->timer--;
	}
	else
	{
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, BG_MAIN_END_YOFS );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, BG_SUB_END_YOFS  );
		delete_background_scroll_task( tcb );
	}
}

static void delete_background_scroll_task( TCB_PTR tcb )
{
	if(tcb)
	{
		BG_SCROLL_WORK* wk = TCB_GetWork(tcb);
		*(wk->ptr_mine) = NULL;
		DemoTrade_IRQ_FreeReq( wk );
		TCB_Delete(tcb);
	}
}
//==============================================================================================
// ボールOBJ移動処理
//==============================================================================================
typedef struct {
	TCB_PTR* pMine;
	int timer;
	DT3DOBJ* obj;
	VecFx32	pos;
	fx32  speed;

}BALL_MOVE_WORK;

static void start_ballin_task( SCENE_WORK* swk, TCB_PTR* pTcb )
{
	BALL_MOVE_WORK* wk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(BALL_MOVE_WORK) );
	if( wk )
	{
		wk->pMine = pTcb;
		wk->obj = swk->objBall;
		DT3D_GetObjPos( wk->obj, &wk->pos );
		wk->speed = (BALL_END_YPOS - wk->pos.y) / BALL_MOVE_FRAMES;
		wk->timer = BALL_MOVE_FRAMES;
		*pTcb = TCB_Add( ball_in_task, wk, TASKPRI_DEFAULT );
		if( *pTcb == NULL )
		{
			sys_FreeMemoryEz( wk );
		}
	}
}
static void ball_in_task( TCB_PTR tcb, void* wk_adrs )
{
	BALL_MOVE_WORK* wk = wk_adrs;

	if( wk->timer )
	{
		wk->pos.y += wk->speed;
		DT3D_SetObjPos( wk->obj, &wk->pos );
		wk->timer--;
	}
	else
	{
		wk->pos.y = BALL_END_YPOS;
		DT3D_SetObjPos( wk->obj, &wk->pos );
		delete_ballin_task( tcb );
	}
}

static void delete_ballin_task( TCB_PTR tcb )
{
	if( tcb )
	{
		BALL_MOVE_WORK* wk = TCB_GetWork(tcb);
		*(wk->pMine) = NULL;
		sys_FreeMemoryEz( wk );
		TCB_Delete(tcb);
	}
}

//==============================================================================================
// ボール3DOBJの半透明度処理
//==============================================================================================
typedef struct {
	TCB_PTR* pMine;
	fx32  alpha;
	fx32  alpha_add;
	fx32  alpha_end;
	int   timer;
	DT3DOBJ*  obj;
}OBJ_ALPHA_WORK;


static void start_ballobj_alpha_task( DT3DOBJ* obj, int startAlpha, int endAlpha, int wait, TCB_PTR* pTcb )
{
	OBJ_ALPHA_WORK*  twk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(OBJ_ALPHA_WORK) );
	if( twk )
	{
		twk->pMine = pTcb;
		twk->alpha = startAlpha << FX32_SHIFT;
		twk->alpha_end = endAlpha << FX32_SHIFT;
		twk->alpha_add = (twk->alpha_end - twk->alpha) / wait;
		twk->timer = wait;
		twk->obj = obj;
		DT3D_SetObjAlpha( obj, startAlpha );
		*pTcb = TCB_Add( obj_alpha_task, twk, TASKPRI_DEFAULT );
		if(*pTcb == NULL)
		{
			sys_FreeMemoryEz(twk);
		}
	}
	else
	{
		*pTcb = NULL;
	}
}
static void obj_alpha_task(TCB_PTR tcb, void* wk_adrs)
{
	OBJ_ALPHA_WORK* wk = wk_adrs;

	if( --(wk->timer) > 0 )
	{
		wk->alpha += wk->alpha_add;
		DT3D_SetObjAlpha( wk->obj, wk->alpha >> FX32_SHIFT );
	}
	else
	{
		DT3D_SetObjAlpha( wk->obj, wk->alpha_end >> FX32_SHIFT );
		delete_ballobj_alpha_task( tcb );
	}
}


static void delete_ballobj_alpha_task( TCB_PTR tcb )
{
	if( tcb )
	{
		OBJ_ALPHA_WORK* wk = TCB_GetWork( tcb );
		*(wk->pMine) = NULL;
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );
	}
}

