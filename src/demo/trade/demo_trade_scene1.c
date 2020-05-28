//============================================================================================
/**
 * @file	demo_trade_scene1.c
 * @brief	ポケモン交換デモ（シーン１:DSからボールが出てきて画面上方へ向かって加速）
 * @author	taya
 * @date	2006.04.12
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



DECLARE_VALUE(fx32,	DSIN_START_RATIO,		0x480);		// 初期拡縮率
DECLARE_VALUE(fx32,	DSIN_RATIO_START_SPEED,	0x0001);	// 初期拡縮速度
DECLARE_VALUE(fx32,	DSIN_RATIO_AC,			0x128);		// 拡縮加速度

DECLARE_VALUE(fx32, BALL_SCALE,				0x00001c00);
DECLARE_VALUE(fx32, BALL_YPOS_OFS,			0xfffe6800);

DECLARE_VALUE(fx32,	BALLMOVE_Z_RANGE_MAX,	0x00014000);
DECLARE_VALUE(fx32,	BALLMOVE_X_RANGE_MAX,	0x00029000);
DECLARE_VALUE(fx32,	BALLMOVE_1ST_STOP_YPOS,		(-8<<FX32_SHIFT));
DECLARE_VALUE(fx32,	BALLMOVE_1ST_STOP_FRAMES,	30);
DECLARE_VALUE(fx32,	BALLMOVE_SPIN_SPEED_MAX,	0x4000);
DECLARE_VALUE(fx32,	BALLMOVE_SPIN_SPEED_MIN,	0x0d00);

DECLARE_VALUE(fx32, BALLMOVE_2ND_AC,			0x200);
DECLARE_VALUE(fx32, CAMERA_X_ANGLE,				0xebe0);
DECLARE_VALUE(fx32, CAMERA_DISTANCE,			0x243800);

DECLARE_VALUE(fx32, BALLMOVE_RISE_START_YPOS,			(-128<<FX32_SHIFT));
DECLARE_VALUE(fx32, BALLMOVE_RISE_CENTER_YPOS,			0xfffef000);
DECLARE_VALUE(s32,  BALLMOVE_RISE_FRAMES,				20);
DECLARE_VALUE(fx32, BALLMOVE_RISE_SCALE,				0x2000);
DECLARE_VALUE(s32,	BALLMOVE_CENTER_WAIT,				110);
DECLARE_VALUE(fx32, BALLMOVE_CENTER_NEXT_YPOS,			0xfffc5800);
DECLARE_VALUE(fx32, BALLMOVE_CENTER_NEXT_MOVE_FRAMES,	53);
DECLARE_VALUE(fx32, BALLMOVE_CENTER_NEXT_WAIT_FRAMES,	1);
DECLARE_VALUE(fx32, BALLMOVE_END_SPEED,					0x20000);


DECLARE_VALUE(fx32, BGSCROLL_AC,			0x120);
DECLARE_VALUE(fx32, BGSCROLL_MAX,			(512<<FX32_SHIFT));

DECLARE_VALUE(s32,	EFFECTLINE_DISP_WAIT,	12);
DECLARE_VALUE(fx32, EFFECTLINE_SPEED,		0x00021000);
DECLARE_VALUE(fx32, EFFECTLINE_RANDOM_SEED,	0x035947d1);

//----------------------------------------------
/**
 *	定数
 */ 
//----------------------------------------------
enum {
	BALL_DEFAULT_X = 0,
	BALL_DEFAULT_Y = (-30 << FX32_SHIFT),
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


// アクターＩＤ
enum {
	ACT_LINE_MAX = 20,
};


// BGキャラ配置
enum {
	WIN_DISP_X = 2,
	WIN_DISP_Y = 19,
	WIN_WIDTH = 27,
	WIN_HEIGHT = 4,
	WIN_CHAR_SIZE = WIN_WIDTH*WIN_HEIGHT,

	CHARPOS_CLEAR = 0,
	CHARPOS_WIN = 1,
	CHARPOS_WIN_FRAME = CHARPOS_WIN + WIN_CHAR_SIZE,

	PAL_WIN = 1,
	PAL_WIN_FRAME,
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
	DT3DOBJ*	obj;
	DT3DMAN*	dt3dMan;

	VecFx32		defaultPos;
	VecFx32		pos;
	VecFx16		rot;

	fx32		y_pos;
	fx32		y_speed;
	fx32		y_ac;
	fx32		end_y;

	fx32		x_range;
	fx32		z_range;
	fx32		x_range_add;
	fx32		z_range_add;
	fx32		next_x_range;
	fx32		next_z_range;
	u32			spin_move_timer;

	s16			spin_rot;
	s16			spin_rot_speed;
	s16			spin_rot_next_speed;
	s16			spin_rot_ac;

	BALL_ROT_SPEED	rotSpeed[3];

	u32			spin_rot_timer;

	BOOL		pauseFlag;
	BOOL		riseFlag;
	int			timer;

}BALL_MOVE_WORK;


typedef struct {
	DEMO_TRADE_WORK*  mainWork;
	int seq;
	int timer;

	DEMO_TRADE_CELLANIM		clpack;
	CLACT_WORK_PTR			act[ACT_LINE_MAX][2];	// 縦に長いOBJが回り込み表示されてしまうので２分割してる
	u32						randSeed;

	GF_BGL_INI*				bgl;
	DT_WAVE_PALANM_CTRL*	palAnimCtrl;
	BOOL					palAnimRunFlag;
	DT_DSIMG_AFFINE_CTRL*	dsinCtrl;
	volatile BOOL			dsinEndFlag;

	DT3DMAN*				dt3dMan;
	DT3DOBJ*				objBall;

	BALL_MOVE_WORK			ballMoveWork;
	TCB_PTR					ballMoveTask;

	TCB_PTR					backScrollTask;

	BOOL		main_sub_switch_flag;

}SCENE1_WORK;


//==============================================================
// Prototype
//==============================================================
static void main_tail_proc( SCENE1_WORK* wk );
static int subseq_setup( SCENE1_WORK* wk, int* seq );
static int subseq_ds_in( SCENE1_WORK* wk, int* seq );
static int subseq_ball_appear( SCENE1_WORK* wk, int* seq );
static int subseq_ball_rise( SCENE1_WORK* wk, int* seq );
static void setup_bg_params( SCENE1_WORK* wk );
static void cleanup_bg_params( SCENE1_WORK* wk );
static void setup_3d_graphics( SCENE1_WORK* wk );
static void cleanup_3d_graphics( SCENE1_WORK* wk );
static void setup_actors( SCENE1_WORK* wk);
static void cleanup_actors( SCENE1_WORK* wk );
static void switch_main_sub( SCENE1_WORK* wk );
static void scene1_vwait_task( TCB_PTR tcb, void* wk_adrs );
static void effline_disp_task( TCB_PTR tcb, void* wk_adrs );
static void delete_effline_disp_task( TCB_PTR tcb );
static void start_background_scroll_task( SCENE1_WORK* wk, TCB_PTR* pTcb );
static void background_scroll_task( TCB_PTR tcb, void* wk_adrs );
static void delete_background_scroll_task( TCB_PTR tcb );
static void start_ballobj_alpha_task( DT3DOBJ* obj, int startAlpha, int endAlpha, int wait );
static void obj_alpha_task(TCB_PTR tcb, void* wk_adrs);
static TCB_PTR setup_ballmove_task( SCENE1_WORK* wk );
static void ballmove_set_spinspeed_shift(BALL_MOVE_WORK* bwk, fx32 next_speed, int frames );
static void ballmove_set_spinrange_shift(BALL_MOVE_WORK* bwk, fx32 next_x, fx32 next_z, int frames );
static void ballmove_rotspeed_shift( BALL_MOVE_WORK* bwk, int dim, fx32 next_speed, int frames );
static void ballmove_spin_move(BALL_MOVE_WORK* bwk );
static void ballmove_task_01(TCB_PTR tcb, void* wk_adrs);
static void ballmove_task_02(TCB_PTR tcb, void* wk_adrs);
static BOOL check_ballmove_pause( TCB_PTR tcb );
static BOOL check_ballmove_rise( TCB_PTR tcb );
static void set_ballmove_rise( TCB_PTR tcb );
static void ballmove_task_03(TCB_PTR tcb, void* wk_adrs);
static void ballmove_task_04(TCB_PTR tcb, void* wk_adrs);
static void ballmove_task_05(TCB_PTR tcb, void* wk_adrs);
static void ballmove_task_06(TCB_PTR tcb, void* wk_adrs);
static void ballmove_task_07(TCB_PTR tcb, void* wk_adrs);
static void ballmove_task_08(TCB_PTR tcb, void* wk_adrs);


//------------------------------------------------------------------
/**
 * シーン１ワーク構築
 *
 * @param   mainWork		
 *
 * @retval  void*		作成したシーン用ワークポインタ
 */
//------------------------------------------------------------------
void* DemoTrade_Scene1Init( DEMO_TRADE_WORK* mainWork )
{
	SCENE1_WORK* wk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(SCENE1_WORK) );
	if( wk )
	{
		int i;

		wk->mainWork = mainWork;
		wk->seq = 0;
		wk->bgl = DemoTrade_GetBgl(mainWork);
		wk->dt3dMan = NULL;
		wk->palAnimCtrl = NULL;
		wk->dsinCtrl = NULL;
		wk->ballMoveTask = NULL;
		wk->backScrollTask = NULL;
		wk->randSeed = gf_mtRand();

		wk->dsinEndFlag = FALSE;

		wk->main_sub_switch_flag = FALSE;
		VWaitTCB_Add( scene1_vwait_task, wk, 0 );
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
void DemoTrade_Scene1Quit( void* wk_adrs )
{
    OSIntrMode oldIntr;
	SCENE1_WORK* wk;

	oldIntr = OS_DisableInterrupts();

	wk = wk_adrs;
	if( wk )
	{
		int i;

		cleanup_bg_params( wk );
		cleanup_3d_graphics( wk );
		cleanup_actors( wk );

		if( wk->ballMoveTask )
		{
			TCB_Delete(wk->ballMoveTask);
		}

		if( wk->backScrollTask )
		{
			delete_background_scroll_task( wk->backScrollTask );
		}

		gf_mtSrand( wk->randSeed );

		sys_FreeMemoryEz( wk );
	}

	OS_RestoreInterrupts( oldIntr );
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
BOOL DemoTrade_Scene1Main( void* wk_adrs, int* seq )
{
	static int (* const subseq[])(SCENE1_WORK*, int*) = {
		subseq_setup,
		subseq_ds_in,
		subseq_ball_appear,
		subseq_ball_rise,
	};

	SCENE1_WORK* wk = wk_adrs;

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
static void main_tail_proc( SCENE1_WORK* wk )
{
	if( wk->dt3dMan )
	{
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
static int subseq_setup( SCENE1_WORK* wk, int* seq )
{
	setup_bg_params( wk );
	setup_3d_graphics( wk );
	setup_actors( wk );
	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 8, 1, HEAPID_DEMO_TRADE_SUB );
	return TRUE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：DSイメージがキュッと表示される
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_ds_in( SCENE1_WORK* wk, int* seq )
{
	static int c = 0;

	switch( *seq ){
	case 0:
		if( WIPE_SYS_EndCheck() )
		{
			c = 0;
			(*seq)++;
		}
		break;

	case 1:
		if( c < 30 )
		{
			c++;
			OS_TPrintf("%02d : dsinEnd  adrs:%08x, val=%d\n", c, &(wk->dsinEndFlag), wk->dsinEndFlag);
		}
		if( wk->dsinEndFlag )
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：ボールがジワッと出てきて上画面へ
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int subseq_ball_appear( SCENE1_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		wk->timer = 0;
		(*seq)++;
		break;

	case 1:
		if( ++(wk->timer) > 8 )
		{
			start_ballobj_alpha_task( wk->objBall, 0, DT3D_ALPHA_MAX, 24 );
			wk->ballMoveTask = setup_ballmove_task( wk );
			DT3D_SetObjAlpha( wk->objBall, 0 );
			DT3D_SetObjDrawFlag( wk->objBall, TRUE );
			(*seq)++;
		}
		break;

	case 2:
		if( check_ballmove_rise( wk->ballMoveTask ) )
		{
			(*seq)++;
		}
		break;

	case 3:
		if( check_ballmove_pause( wk->ballMoveTask ) )
		{
			(*seq)++;
		}
		break;

	case 4:
		switch_main_sub( wk );
		return TRUE;

	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * サブシーケンス：ボールが上画面に移り、上昇していく
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int subseq_ball_rise( SCENE1_WORK* wk, int* seq )
{
	enum {
		BOLL_SPEEDUP_SE_FRAME = 40,
	};

	switch( *seq ){
	case 0:
		set_ballmove_rise( wk->ballMoveTask );
		wk->timer = 0;
		(*seq)++;
		break;
	case 1:
		if(++(wk->timer) > 2 )
		{
			wk->timer = 0;
			DT_WavePalAnm_StopReq( wk->palAnimCtrl );
			(*seq)++;
		}
		break;
	case 2:
		if( wk->palAnimRunFlag  == FALSE )
		{
			start_background_scroll_task( wk, &(wk->backScrollTask) );
			(*seq)++;
		}
		break;
	case 3:
		if( wk->timer < BOLL_SPEEDUP_SE_FRAME )
		{
			if( ++(wk->timer) == BOLL_SPEEDUP_SE_FRAME )
			{
				Snd_SePlay( SE_KOUKAN_BALL_MOVE );
			}
		}
		if( check_ballmove_pause( wk->ballMoveTask ) )
		{
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, 4, 1, HEAPID_DEMO_TRADE_SUB );
			(*seq)++;
		}
		#ifdef RUNTIME_ADJUST
		if( sys.cont & PAD_BUTTON_L ){ if(DT_adjustValue32(&BALLMOVE_2ND_AC, 0x10, sys.repeat, "Ball 2nd Ac")) break; }
		if( sys.cont & PAD_BUTTON_R ){ if(DT_adjustValue32(&BALL_YPOS_OFS, 0x400, sys.repeat, "Init Y ofs")) break; }
		if( sys.cont & PAD_BUTTON_Y ){ if(DT_adjustValue32(&BALLMOVE_CENTER_NEXT_MOVE_FRAMES, 0x01, sys.repeat, "down move Frames")) break; }
		if( sys.cont & PAD_BUTTON_X ){ if(DT_adjustValue32(&BALLMOVE_CENTER_WAIT, 0x01, sys.repeat, "center Wait Frames")) break; }
		if( sys.cont & PAD_BUTTON_START ){ if(DT_adjustValue32(&BALLMOVE_CENTER_NEXT_WAIT_FRAMES, 0x01, sys.repeat, "down wait Frames")) break; }
		if( sys.cont & PAD_BUTTON_A ){ if(DT_adjustValue32(&BALLMOVE_CENTER_NEXT_YPOS, 0x800, sys.repeat, "down Ypos")) break; }
		if( sys.cont & PAD_BUTTON_B ){ if(DT_adjustValue32(&BALLMOVE_END_SPEED, 0x800, sys.repeat, "end speed")) break; }
		#endif
		break;
	case 4:
		if( WIPE_SYS_EndCheck() )
		{
			return TRUE;
		}
	}
	return FALSE;
}



//==============================================================================================
//==============================================================================================

static void setup_bg_params( SCENE1_WORK* wk )
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

	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

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
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_scene1_ds_lz_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_scene1_ds_lz_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );

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
//	ArcUtil_PalSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_wave_nclr, PALTYPE_MAIN_BG_EX, 0x6000, 0x60, HEAPID_DEMO_TRADE_SUB);
//	ArcUtil_PalSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_wave_nclr, PALTYPE_SUB_BG_EX, 0x6000, 0x60, HEAPID_DEMO_TRADE_SUB);

//	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME2_M );
//	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME2_S );

	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, -256 );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_S, VISIBLE_OFF );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 0 );
	wk->palAnimCtrl = DT_WavePalAnm_Start(&(wk->palAnimRunFlag), 1);
	wk->dsinCtrl = DT_DSAff_Start( wk->bgl, DSIN_START_RATIO, 0x1000, DSIN_RATIO_START_SPEED, DSIN_RATIO_AC, 0, &(wk->dsinEndFlag) );
}
static void cleanup_bg_params( SCENE1_WORK* wk )
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



static void setup_3d_graphics( SCENE1_WORK* wk )
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
						BALL_DEFAULT_X, BALL_DEFAULT_Y+BALL_YPOS_OFS, BALL_DEFAULT_Z , FALSE );

	{
		static CAMERA_ANGLE  angle;

		angle.x = CAMERA_X_ANGLE;
		angle.y = 0;
		angle.z = 0;
		DT3D_SetCameraAngleRev( wk->dt3dMan, &angle );

//		DT3D_SetCameraDistance( wk->dt3dMan, CAMERA_DISTANCE );
		
	}

	DT3D_SetObjScale( wk->objBall, BALL_SCALE );
}

static void cleanup_3d_graphics( SCENE1_WORK* wk )
{
	if( wk->dt3dMan )
	{
		DT3DMAN_Delete( wk->dt3dMan );
	}
}


//==============================================================================================
//==============================================================================================

static void setup_actors( SCENE1_WORK* wk)
{
	NNSG2dImagePaletteProxy	palProxy;
	NNSG2dImageProxy		imgProxy;
	CLACT_HEADER			header;
	int i;
	fx32 x, y;

	DemoTrade_LoadCellAnimDatas( &wk->clpack, ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade02_lz_ncer, NARC_demo_trade_trade02_lz_nanr );

	NNS_G2dInitImagePaletteProxy(&palProxy);
	NNS_G2dInitImageProxy(&imgProxy);

	ArcUtil_CharSysLoad(ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj02_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DMAIN, 0, HEAPID_DEMO_TRADE_SUB, &imgProxy );

	ArcUtil_CharSysLoad(ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj02_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DSUB, 0, HEAPID_DEMO_TRADE_SUB, &imgProxy );

	ArcUtil_PalSysLoad( ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj02_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 0,
					HEAPID_DEMO_TRADE_SUB, &palProxy );

	ArcUtil_PalSysLoad( ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj02_nclr, NNS_G2D_VRAM_TYPE_2DSUB, 0,
					HEAPID_DEMO_TRADE_SUB, &palProxy );

	DemoTrade_SetActHeader( &header, &wk->clpack, &imgProxy, &palProxy, 1 );

	gf_mtSrand( EFFECTLINE_RANDOM_SEED );
	for(i=0; i<ACT_LINE_MAX;i++)
	{
		x = LINE_XPOS_MIN+(gf_mtRand() % LINE_XPOS_RANGE);
		y = LINE_YPOS_MIN+(gf_mtRand() % LINE_YPOS_RANGE);

		wk->act[i][0] = DemoTrade_AddActor( wk->mainWork, &header, x, y, 0, NNS_G2D_VRAM_TYPE_2DMAIN );
		wk->act[i][1] = DemoTrade_AddActor( wk->mainWork, &header, x, y+LINE_ACTOR_YDIFF, 0, NNS_G2D_VRAM_TYPE_2DMAIN );

		CLACT_AnmChg(wk->act[i][0],0);
		CLACT_AnmChg(wk->act[i][1],1);
		CLACT_SetDrawFlag( wk->act[i][0], FALSE );
		CLACT_SetDrawFlag( wk->act[i][1], FALSE );
	}
}

static void cleanup_actors( SCENE1_WORK* wk )
{
	int i;

	for(i=0; i<ACT_LINE_MAX; i++)
	{
		if(wk->act[i][0])
		{
			CLACT_Delete(wk->act[i][0]);
		}
		if(wk->act[i][1])
		{
			CLACT_Delete(wk->act[i][1]);
		}
	}
	DemoTrade_UnloadCellAnimDatas( &wk->clpack );
}

//==============================================================================================
// メイン・サブLCD切り替え
//==============================================================================================

static void switch_main_sub( SCENE1_WORK* wk )
{
	wk->main_sub_switch_flag = TRUE;
}

static void scene1_vwait_task( TCB_PTR tcb, void* wk_adrs )
{
	SCENE1_WORK* wk = wk_adrs;

	if( wk->main_sub_switch_flag )
	{
		wk->main_sub_switch_flag = FALSE;

		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, -256 );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, 0 );
		GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_OFF );
		GF_BGL_VisibleSet( GF_BGL_FRAME3_S, VISIBLE_ON );
		GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
		TCB_Delete( tcb );
	}
}


//==============================================================================================
// 効果線表示
//==============================================================================================

typedef struct {
	TCB_PTR*		pMine;
	SCENE1_WORK*	sceneWork;
	BOOL			lineDispFlag[ACT_LINE_MAX];
	VecFx32			linePos[ACT_LINE_MAX];
	int timer;
	int count;
}EFFLINE_TASK_WORK;


 static void start_effline_disp_task( SCENE1_WORK* wk, TCB_PTR* pTcb, EFFLINE_TASK_WORK* twk )
{
	int i;

	twk->sceneWork = wk;
	twk->pMine = pTcb;
	twk->timer = 0;
	twk->count = 0;
	for(i=0; i<ACT_LINE_MAX; i++)
	{
		twk->lineDispFlag[i] = FALSE;
		twk->linePos[i] = *(CLACT_GetMatrix(wk->act[i][0]));
	}

	*(twk->pMine) = TCB_Add( effline_disp_task, twk, TASKPRI_DEFAULT );
	if( *(twk->pMine) == NULL )
	{
		sys_FreeMemoryEz( twk );
	}
}

static void effline_disp_task( TCB_PTR tcb, void* wk_adrs )
{
	EFFLINE_TASK_WORK* wk = wk_adrs;
	VecFx32  vec;
	int i;

	if( ++(wk->timer) > EFFECTLINE_DISP_WAIT )
	{
		wk->timer = 0;

		if( wk->count < ACT_LINE_MAX )
		{
			wk->lineDispFlag[wk->count] = TRUE;
			wk->count++;
		}
	}

#if 1
	for(i=0; i<ACT_LINE_MAX; i++)
	{
		wk->linePos[i].y += EFFECTLINE_SPEED;
		if( wk->linePos[i].y >= (LINE_YPOS_MAX<<FX32_SHIFT) )
		{
			wk->linePos[i].y = LINE_YPOS_MIN_FX32 + (wk->linePos[i].y - LINE_YPOS_MAX_FX32);
			if( wk->lineDispFlag[i] )
			{
				CLACT_SetDrawFlag( wk->sceneWork->act[i][0], TRUE );
				CLACT_SetDrawFlag( wk->sceneWork->act[i][1], TRUE );
			}
		}
		CLACT_SetMatrix( wk->sceneWork->act[i][0], &(wk->linePos[i]) );
		vec = wk->linePos[i];
		vec.y += LINE_ACTOR_YDIFF_FX32;
		CLACT_SetMatrix( wk->sceneWork->act[i][1], &vec );
	}
#else
	for(i=0; i<ACT_LINE_MAX; i++)
	{
		if(sys.repeat & PAD_KEY_UP )
		{
			VecFx32  vec;

			if( sys.cont & PAD_BUTTON_R )
			{
				wk->linePos[i].y -= (8*FX32_ONE);
			}
			else
			{
				wk->linePos[i].y -= FX32_ONE;
			}
			OS_TPrintf("line(%d) : x=%d, y=%d\n", i, (wk->linePos[i].x>>FX32_SHIFT), (wk->linePos[i].y>>FX32_SHIFT));
			CLACT_SetMatrix( wk->sceneWork->act[i][0], &(wk->linePos[i]) );
			vec = wk->linePos[i];
			vec.y += LINE_ACTOR_YDIFF_FX32;
			CLACT_SetMatrix( wk->sceneWork->act[i][1], &(vec) );

		}
		else if( sys.repeat & PAD_KEY_DOWN )
		{
			VecFx32  vec;
			if( sys.cont & PAD_BUTTON_R )
			{
				wk->linePos[i].y += (8*FX32_ONE);
			}
			else
			{
				wk->linePos[i].y += FX32_ONE;
			}
			OS_TPrintf("line(%d) : x=%d, y=%d\n", i, (wk->linePos[i].x>>FX32_SHIFT), (wk->linePos[i].y>>FX32_SHIFT));
			CLACT_SetMatrix( wk->sceneWork->act[i][0], &(wk->linePos[i]) );
			vec = wk->linePos[i];
			vec.y += LINE_ACTOR_YDIFF_FX32;
			CLACT_SetMatrix( wk->sceneWork->act[i][1], &(vec) );
			CLACT_SetMatrix( wk->sceneWork->act[i][1], &(vec) );
		}
		
	}
#endif



}

static void delete_effline_disp_task( TCB_PTR tcb )
{
	if( tcb )
	{
		EFFLINE_TASK_WORK* wk = TCB_GetWork(tcb);
		*(wk->pMine) = NULL;
		TCB_Delete( tcb );
	}
}

//==============================================================================================
// 背景スクロール
//==============================================================================================
typedef struct {
	SCENE1_WORK* sceneWork;
	EFFLINE_TASK_WORK  lineTaskWork;
	GF_BGL_INI*	bgl;
	fx32		mainY;
	fx32		subY;
	fx32		speed;
	fx32		scroll_val;
	TCB_PTR*	ptr_mine;
	TCB_PTR		tcb_eff;
}BG_SCROLL_WORK;

static void start_background_scroll_task( SCENE1_WORK* wk, TCB_PTR* pTcb )
{
	BG_SCROLL_WORK*  twk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(BG_SCROLL_WORK) );
	if( twk )
	{
		twk->sceneWork = wk;
		twk->bgl = wk->bgl;

		twk->mainY = GF_BGL_ScrollGetY( twk->bgl, GF_BGL_FRAME2_M ) << FX32_SHIFT;
		twk->subY = GF_BGL_ScrollGetY( twk->bgl, GF_BGL_FRAME2_S ) << FX32_SHIFT;
		twk->speed = 0;
		twk->scroll_val = 0;
		twk->ptr_mine = pTcb;
		twk->tcb_eff = NULL;

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

	if( wk->scroll_val < BGSCROLL_MAX )
	{
		wk->speed += BGSCROLL_AC;
		wk->scroll_val += wk->speed;
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, (wk->mainY - wk->scroll_val) >> FX32_SHIFT );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_Y_SET, (wk->subY - wk->scroll_val) >> FX32_SHIFT );

		if( wk->scroll_val >= (128<<FX32_SHIFT) )
		{
			if( wk->tcb_eff == NULL )
			{
				start_effline_disp_task( wk->sceneWork, &(wk->tcb_eff), &(wk->lineTaskWork) );
			}
		}
	}
}

static void delete_background_scroll_task( TCB_PTR tcb )
{
	if(tcb)
	{
		BG_SCROLL_WORK* wk = TCB_GetWork(tcb);
		*(wk->ptr_mine) = NULL;
		delete_effline_disp_task( wk->tcb_eff );
		sys_FreeMemoryEz( wk );
		TCB_Delete(tcb);
	}
}



//==============================================================================================
// ボール3DOBJの半透明度処理
//==============================================================================================
typedef struct {
	fx32  alpha;
	fx32  alpha_add;
	fx32  alpha_end;
	int   timer;
	DT3DOBJ*  obj;
}OBJ_ALPHA_WORK;


static void start_ballobj_alpha_task( DT3DOBJ* obj, int startAlpha, int endAlpha, int wait )
{
	OBJ_ALPHA_WORK*  twk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(OBJ_ALPHA_WORK) );
	if( twk )
	{
		twk->alpha = startAlpha << FX32_SHIFT;
		twk->alpha_end = endAlpha << FX32_SHIFT;
		twk->alpha_add = (twk->alpha_end - twk->alpha) / wait;
		twk->timer = wait;
		twk->obj = obj;
		DT3D_SetObjAlpha( obj, startAlpha );
		TCB_Add( obj_alpha_task, twk, TASKPRI_DEFAULT );
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
		sys_FreeMemoryEz(wk);
		TCB_Delete(tcb);
	}
}


//==============================================================================================
// ボールOBJ移動処理
//==============================================================================================

static TCB_PTR setup_ballmove_task( SCENE1_WORK* wk )
{
	BALL_MOVE_WORK* bwk = &(wk->ballMoveWork);
	int i;

	DT3D_GetObjPos( wk->objBall, &bwk->defaultPos );
	DT3D_GetObjRot( wk->objBall, &bwk->rot );
	bwk->pos = bwk->defaultPos;

	bwk->dt3dMan = wk->dt3dMan;
	bwk->obj = wk->objBall;
	bwk->y_pos = bwk->defaultPos.y;
	bwk->y_speed = (BALLMOVE_1ST_STOP_YPOS-bwk->defaultPos.y) / BALLMOVE_1ST_STOP_FRAMES;
	bwk->timer = BALLMOVE_1ST_STOP_FRAMES;

	bwk->x_range = 0;
	bwk->z_range = 0;
	bwk->x_range_add = 0;
	bwk->z_range_add = 0;
	bwk->spin_rot = 0;
	bwk->spin_rot_speed = BALLMOVE_SPIN_SPEED_MAX;
	bwk->spin_rot_ac = 0;
	bwk->riseFlag = FALSE;

	for(i=0; i<3; i++)
	{
		bwk->rotSpeed[i].speed = 0;
		bwk->rotSpeed[i].speed_add = 0;
		bwk->rotSpeed[i].speed_next = 0;
		bwk->rotSpeed[i].timer = 0;
	}

	bwk->pauseFlag = FALSE;

	ballmove_set_spinspeed_shift( bwk, BALLMOVE_SPIN_SPEED_MIN, BALLMOVE_1ST_STOP_FRAMES );
	ballmove_set_spinrange_shift( bwk, BALLMOVE_X_RANGE_MAX, BALLMOVE_Z_RANGE_MAX, BALLMOVE_1ST_STOP_FRAMES );

	return TCB_Add( ballmove_task_01, bwk, TASKPRI_DEFAULT );
}
static void ballmove_set_spinspeed_shift(BALL_MOVE_WORK* bwk, fx32 next_speed, int frames )
{
	if( frames )
	{
		bwk->spin_rot_ac = (int)(next_speed - bwk->spin_rot_speed) / frames;
		bwk->spin_rot_speed += bwk->spin_rot_ac;
	}
	else
	{
		bwk->spin_rot_speed = next_speed;
	}
	bwk->spin_rot_next_speed = next_speed;
	bwk->spin_rot_timer = frames;
}
static void ballmove_set_spinrange_shift(BALL_MOVE_WORK* bwk, fx32 next_x, fx32 next_z, int frames )
{
	if( frames )
	{
		bwk->x_range_add = (next_x - bwk->x_range) / frames;
		bwk->z_range_add = (next_z - bwk->z_range) / frames;
		bwk->x_range += bwk->x_range_add;
		bwk->z_range += bwk->z_range_add;
		bwk->next_x_range = next_x;
		bwk->next_z_range = next_z;
	}
	bwk->spin_move_timer = frames;
}
static void ballmove_rotspeed_shift( BALL_MOVE_WORK* bwk, int dim, fx32 next_speed, int frames )
{
	if( frames )
	{
		bwk->rotSpeed[dim].speed_add = (next_speed - bwk->rotSpeed[dim].speed) / frames;
	}
	bwk->rotSpeed[dim].speed_next = next_speed;
	bwk->rotSpeed[dim].timer = frames;
}

static void ballmove_spin_move(BALL_MOVE_WORK* bwk )
{
	#if 1
	int angle, i;

	if( bwk->spin_rot_timer )
	{
		bwk->spin_rot_timer--;
		if( bwk->spin_rot_timer )
		{
			bwk->spin_rot_speed += bwk->spin_rot_ac;
		}
		else
		{
			bwk->spin_rot_speed = bwk->spin_rot_next_speed;
		}
	}

	bwk->spin_rot += bwk->spin_rot_speed;
	angle = (u16)(bwk->spin_rot) / (65536/360);
	if(angle >= 360){ angle -= 360; }

	if( bwk->spin_move_timer )
	{
		bwk->x_range += bwk->x_range_add;
		bwk->z_range += bwk->z_range_add;
		bwk->spin_move_timer--;
		if( bwk->spin_move_timer == 0 )
		{
			bwk->x_range = bwk->next_x_range;
			bwk->z_range = bwk->next_z_range;
		}
	}


	bwk->pos.x = bwk->defaultPos.x + FX_Mul(FixSinCosTbl[angle+90],bwk->x_range);
	bwk->pos.z = bwk->defaultPos.z + FX_Mul(FixSinCosTbl[angle], bwk->z_range);
	#endif

	bwk->rot.y += bwk->spin_rot_speed;

	for(i=0; i<3; i++)
	{
		if( bwk->rotSpeed[i].timer )
		{
			bwk->rotSpeed[i].timer--;
			if(bwk->rotSpeed[i].timer == 0)
			{
				bwk->rotSpeed[i].speed = bwk->rotSpeed[i].speed_next;
			}
			else
			{
				bwk->rotSpeed[i].speed += bwk->rotSpeed[i].speed_add;
			}
		}

	}

	bwk->rot.x += bwk->rotSpeed[BALL_ROT_X].speed;
	bwk->rot.y += bwk->rotSpeed[BALL_ROT_Y].speed;
	bwk->rot.z += bwk->rotSpeed[BALL_ROT_Z].speed;
//	bwk->rot.z += 0x80;
}

//------------------------------------------------------------------
/**
 * 登場。DS画面からシュルルンと回りながら出てくる
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ballmove_task_01(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;
	int ym;

	if( bwk->timer )
	{
		bwk->y_pos += bwk->y_speed;
		bwk->pos.y = bwk->y_pos;
//		OS_TPrintf("1st ypos = 0x%08x\n", (u32)(bwk->pos.y));

		if( --(bwk->timer) <= 0 )
		{
			bwk->y_ac = BALLMOVE_2ND_AC;
			bwk->y_speed = 0;
			ballmove_set_spinrange_shift(bwk, 0x4000, 0x4000, 60);
			ballmove_rotspeed_shift( bwk, BALL_ROT_X, -0x800, 30 );
			bwk->riseFlag = TRUE;
			TCB_ChangeFunc(tcb, ballmove_task_02);
		}
	}

	ballmove_spin_move( bwk );
	DT3D_SetObjPos( bwk->obj, &(bwk->pos) );
	DT3D_SetObjRot( bwk->obj, &(bwk->rot) );

}
//------------------------------------------------------------------
/**
 * 回転幅を小さくしながら、画面上方へ消えていく
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ballmove_task_02(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;

	if( bwk->pauseFlag == FALSE )
	{
		bwk->y_speed += bwk->y_ac;
		bwk->y_pos += bwk->y_speed;
		bwk->pos.y = bwk->y_pos;
		ballmove_spin_move( bwk );

		DT3D_SetObjPos( bwk->obj, &(bwk->pos) );
		DT3D_SetObjRot( bwk->obj, &(bwk->rot) );

		if( DT3D_CheckObjVisible(bwk->obj) == FALSE )
		{
			DT3D_SetObjDrawFlag( bwk->obj, FALSE );
			bwk->pauseFlag = TRUE;
		}
	}
}
//------------------------------------------------------------------
/**
 * 下画面での移動処理終了し、一時停止状態になっているかチェック
 *
 * @param   tcb		
 *
 * @retval  BOOL	TRUEで一時停止中。
 */
//------------------------------------------------------------------
static BOOL check_ballmove_pause( TCB_PTR tcb )
{
	BALL_MOVE_WORK* bwk = TCB_GetWork(tcb);
	return bwk->pauseFlag;
}
//------------------------------------------------------------------
/**
 * ボールが上画面へ向かって登り始めたかチェック
 *
 * @param   tcb		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL check_ballmove_rise( TCB_PTR tcb )
{
	BALL_MOVE_WORK* bwk = TCB_GetWork(tcb);
	return bwk->riseFlag;

}
//------------------------------------------------------------------
/**
 * 一時停止状態になっていたボール移動を、次の段階へ移す
 *
 * @param   tcb		
 *
 */
//------------------------------------------------------------------
static void set_ballmove_rise( TCB_PTR tcb )
{
	BALL_MOVE_WORK* bwk = TCB_GetWork(tcb);
	CAMERA_ANGLE  angle;

	bwk->pauseFlag = FALSE;
	angle.x = angle.y = angle.z = 0;

	DT3D_SetCameraView( bwk->dt3dMan, GF_CAMERA_ORTHO );
	DT3D_SetCameraAngleRev( bwk->dt3dMan, &angle );

	bwk->y_speed = (BALLMOVE_RISE_CENTER_YPOS - BALLMOVE_RISE_START_YPOS) / BALLMOVE_RISE_FRAMES;
	bwk->y_pos = BALLMOVE_RISE_START_YPOS + bwk->y_speed;
	bwk->timer = BALLMOVE_RISE_FRAMES;
	bwk->pos.y = bwk->y_pos;

	ballmove_set_spinrange_shift( bwk, 0x0000, 0x0000, 20 );
	ballmove_rotspeed_shift( bwk, BALL_ROT_Y, -(bwk->spin_rot_speed), 30 );
//	ballmove_rotspeed_shift( bwk, BALL_ROT_X, 0x100, 50 );
	ballmove_rotspeed_shift( bwk, BALL_ROT_Z, 0x100, 50 );
	DT3D_SetObjScale( bwk->obj, BALLMOVE_RISE_SCALE );
	DT3D_SetObjDrawFlag( bwk->obj, TRUE );

	TCB_ChangeFunc( tcb, ballmove_task_03 );
//	bwk->
}
static void ballmove_task_03(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;
	ballmove_spin_move( bwk );

	if( bwk->timer )
	{
		bwk->y_pos += bwk->y_speed;
		bwk->pos.y = bwk->y_pos;
		if( --(bwk->timer) == 0 )
		{
			TCB_ChangeFunc( tcb, ballmove_task_04 );
		}
	}

	DT3D_SetObjPos( bwk->obj, &(bwk->pos) );
	DT3D_SetObjRot( bwk->obj, &(bwk->rot) );

}
static void ballmove_task_04(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;
	ballmove_spin_move( bwk );

	
	if( ++(bwk->timer) > BALLMOVE_CENTER_WAIT)
	{
		bwk->y_speed = (BALLMOVE_CENTER_NEXT_YPOS - bwk->y_pos) / BALLMOVE_CENTER_NEXT_MOVE_FRAMES;
		bwk->timer = BALLMOVE_CENTER_NEXT_MOVE_FRAMES;
		TCB_ChangeFunc( tcb, ballmove_task_05 );
	}

	DT3D_SetObjPos( bwk->obj, &(bwk->pos) );
	DT3D_SetObjRot( bwk->obj, &(bwk->rot) );

}
static void ballmove_task_05(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;
	ballmove_spin_move( bwk );

	if( bwk->timer )
	{
		bwk->y_pos += bwk->y_speed;
		bwk->pos.y = bwk->y_pos;
		if( --(bwk->timer) == 0 )
		{
			TCB_ChangeFunc( tcb, ballmove_task_06 );
		}
	}

	DT3D_SetObjPos( bwk->obj, &(bwk->pos) );
	DT3D_SetObjRot( bwk->obj, &(bwk->rot) );
}
static void ballmove_task_06(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;
	ballmove_spin_move( bwk );

	if( ++(bwk->timer) >  BALLMOVE_CENTER_NEXT_WAIT_FRAMES)
	{
		bwk->y_speed = BALLMOVE_END_SPEED;
		TCB_ChangeFunc( tcb, ballmove_task_07 );
	}

	DT3D_SetObjPos( bwk->obj, &(bwk->pos) );
	DT3D_SetObjRot( bwk->obj, &(bwk->rot) );

}
static void ballmove_task_07(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;

	if( bwk->pauseFlag == FALSE )
	{
		ballmove_spin_move( bwk );

		bwk->y_pos += bwk->y_speed;
		bwk->pos.y = bwk->y_pos;
		DT3D_SetObjPos( bwk->obj, &(bwk->pos) );
		DT3D_SetObjRot( bwk->obj, &(bwk->rot) );
		if( DT3D_CheckObjVisible(bwk->obj) == FALSE )
		{
			bwk->pauseFlag = TRUE;
		}
	}
}
static void ballmove_task_08(TCB_PTR tcb, void* wk_adrs)
{
	BALL_MOVE_WORK* bwk = wk_adrs;
}

