//============================================================================================
/**
 * @file	demo_trade_scene3.c
 * @brief	ポケモン交換デモ（シーン３：ポケモンがすれ違う）
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

DECLARE_VALUE( s32,		RECV_START_VOFS,		  80 );
DECLARE_VALUE( s32,		RECV_END_VOFS,			 -48 );
DECLARE_VALUE( s32,		SEND_START_VOFS,		-384 );
DECLARE_VALUE( s32,		SEND_END_VOFS,			 -48 );
DECLARE_VALUE( s32,		MOVE_FRAMES,			  60 );


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

	PALNO_SENDPOKE = 14,
	PALNO_RECVPOKE = 15,
};



typedef struct {
	DEMO_TRADE_WORK*  mainWork;
	int seq;
	int timer;

	GF_BGL_INI*				bgl;

	fx32			send_yofs;
	fx32			recv_yofs;
	fx32			send_speed;
	fx32			recv_speed;
	BOOL			endFlag;

}SCENE_WORK;


//==============================================================
// Prototype
//==============================================================
static int subseq_setup( SCENE_WORK* wk, int* seq );
static int subseq_poke_cross( SCENE_WORK* wk, int* seq );
static void poke_cross_task( TCB_PTR tcb, void* wk_adrs );
static void setup_bg_params( SCENE_WORK* wk );
static void cleanup_bg_params( SCENE_WORK* wk );
static void set_bg_vofs( GF_BGL_INI* bgl, int send, int recv );


//------------------------------------------------------------------
/**
 * シーンワーク構築
 *
 * @param   mainWork		
 *
 * @retval  void*		作成したシーン用ワークポインタ
 */
//------------------------------------------------------------------
void* DemoTrade_Scene3Init( DEMO_TRADE_WORK* mainWork )
{
	SCENE_WORK* wk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(SCENE_WORK) );
	if( wk )
	{
		int i;

		wk->mainWork = mainWork;
		wk->seq = 0;
		wk->bgl = DemoTrade_GetBgl(mainWork);
	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン３ワーク破棄
 *
 * @param   void*		シーン用ワークポインタ
 */
//------------------------------------------------------------------
void DemoTrade_Scene3Quit( void* wk_adrs )
{
	SCENE_WORK* wk = wk_adrs;
	if( wk )
	{
		int i;

		cleanup_bg_params( wk );
		sys_FreeMemoryEz( wk );
	}
}
//------------------------------------------------------------------
/**
 * シーン３メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEでシーン終了
 */
//------------------------------------------------------------------
BOOL DemoTrade_Scene3Main( void* wk_adrs, int* seq )
{
	static int (* const subseq[])(SCENE_WORK*, int*) = {
		subseq_setup,
		subseq_poke_cross,
	};

	SCENE_WORK* wk = wk_adrs;

	if( (*seq) < NELEMS(subseq) )
	{
		if( subseq[*seq](wk, &(wk->seq)) )
		{
			(*seq)++;
			wk->seq = 0;
		}

		return FALSE;
	}
	return TRUE;
}
/*

アークID　ARC_BATT_BG

通常　POKE_SCREEN_N_NSCR
反転　POKE_SCREEN_F_NSCR

です。


battle/graphic/batt_bg_def.h
*/


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

	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, 8, 1, HEAPID_DEMO_TRADE_SUB );
	return TRUE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：ポケモンがすれ違う
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_poke_cross( SCENE_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		if( WIPE_SYS_EndCheck() )
		{
			wk->send_yofs = SEND_START_VOFS << FX32_SHIFT;
			wk->recv_yofs = RECV_START_VOFS << FX32_SHIFT;
			wk->send_speed = ((SEND_END_VOFS - SEND_START_VOFS) << FX32_SHIFT) / MOVE_FRAMES;
			wk->recv_speed = ((RECV_END_VOFS - RECV_START_VOFS) << FX32_SHIFT) / MOVE_FRAMES;
			wk->timer = MOVE_FRAMES;
			wk->endFlag = FALSE;
			VIntrTCB_Add( poke_cross_task, wk, VINTR_TASKPRI_DEFAULT );
			(*seq)++;
		}
		break;

	case 1:
		if( wk->endFlag )
		{
			Snd_SePlay( SE_POKE_CROSS );
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, 16, 1, HEAPID_DEMO_TRADE_SUB );
			(*seq)++;
		}
		break;

	case 2:
		if( WIPE_SYS_EndCheck() )
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}

static void poke_cross_task( TCB_PTR tcb, void* wk_adrs )
{
	SCENE_WORK* wk = wk_adrs;

	if(wk->timer)
	{
		wk->timer--;
		wk->send_yofs += wk->send_speed;
		wk->recv_yofs += wk->recv_speed;
		set_bg_vofs( wk->bgl, wk->send_yofs>>FX32_SHIFT, wk->recv_yofs>>FX32_SHIFT );
	}
	else
	{
		set_bg_vofs( wk->bgl, SEND_END_VOFS, RECV_END_VOFS );
		wk->endFlag = TRUE;
		TCB_Delete(tcb);
	}
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

	static const GF_BGL_BGCNT_HEADER header1 = {
		0, 0, 0x1000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x512, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 1, TRUE, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0x1000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x512, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000,
		GX_BG_EXTPLTT_01, 2, TRUE, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const GF_BGL_BGCNT_HEADER header3 = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000,
		GX_BG_EXTPLTT_01, 3, TRUE, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	enum {
		CLEAR_CHARPOS = 200,	// ポケモンキャラサイズ分空ける
	};

	GF_Disp_SetBank( &SetBankData );

	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_M, &header1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_S, &header1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &header2, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &header3, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_S, &header3, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_cross_lz_ncgr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_cross_lz_ncgr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_cross_lz_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_cross_lz_nscr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );

	ArcUtil_PalSet( ARC_DEMO_TRADE_GRA, NARC_demo_trade_cross_nclr, PALTYPE_MAIN_BG, 0, 0x20, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_PalSet( ARC_DEMO_TRADE_GRA, NARC_demo_trade_cross_nclr, PALTYPE_SUB_BG,  0, 0x20, HEAPID_DEMO_TRADE_SUB );

	GF_BGL_CharFill( wk->bgl, GF_BGL_FRAME1_M, 0x00, 1, CLEAR_CHARPOS );
	GF_BGL_CharFill( wk->bgl, GF_BGL_FRAME1_S, 0x00, 1, CLEAR_CHARPOS );
	GF_BGL_CharFill( wk->bgl, GF_BGL_FRAME2_M, 0x00, 1, CLEAR_CHARPOS );

	DemoTrade_TransPokeGraphic( wk->mainWork, 0, GF_BGL_FRAME1_M, PALNO_SENDPOKE, FALSE );
	DemoTrade_TransPokeGraphic( wk->mainWork, 0, GF_BGL_FRAME1_S, PALNO_SENDPOKE, FALSE );
	DemoTrade_TransPokeGraphic( wk->mainWork, 1, GF_BGL_FRAME2_M, PALNO_RECVPOKE, FALSE );

	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME1_M, CLEAR_CHARPOS, 0, 0, 32, 64, 0 );
	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME1_S, CLEAR_CHARPOS, 0, 0, 32, 64, 0 );
	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME2_M, CLEAR_CHARPOS, 0, 0, 32, 64, 0 );

	DemoTrade_SetupPokeScreen( wk->mainWork, 0, GF_BGL_FRAME1_M, PALNO_SENDPOKE, 20, 0 );
	DemoTrade_SetupPokeScreen( wk->mainWork, 0, GF_BGL_FRAME1_S, PALNO_SENDPOKE, 20, 0 );
	DemoTrade_SetupPokeScreen( wk->mainWork, 1, GF_BGL_FRAME2_M, PALNO_RECVPOKE,  2, 0 );

	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME1_M );
	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME1_S );
	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME2_M );

//	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_S, GF_BGL_SCROLL_Y_SET, 256 );

	set_bg_vofs( wk->bgl, RECV_START_VOFS, SEND_START_VOFS );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}
static void cleanup_bg_params( SCENE_WORK* wk )
{
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_S );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_S );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_S );
}


static void set_bg_vofs( GF_BGL_INI* bgl, int send, int recv )
{
	recv &= 0x1ff;
	send &= 0x1ff;

	GF_BGL_ScrollSet( bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, recv );

	GF_BGL_ScrollSet( bgl, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_SET, send );
	GF_BGL_ScrollSet( bgl, GF_BGL_FRAME1_S, GF_BGL_SCROLL_Y_SET, send+192 );//+DT_LCD_DIFF );
}

