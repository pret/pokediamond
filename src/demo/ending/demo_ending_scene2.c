//============================================================================================
/**
 * @file	demo_ending_scene2.c
 * @brief	エンディングデモ（シーン２：バッグのカットイン）
 * @author	taya
 * @date	2006.06.08
 */
//============================================================================================
#include "common.h"

#include "demo_ending_common.h"



//==============================================================
// Const
//==============================================================
enum {
	#ifndef DEBUG_FASTMODE
	SCENE_FRAMES = 24 * 30 + 15,
	#else
	SCENE_FRAMES = 30,
	#endif
};


//==============================================================
// Work
//==============================================================

typedef struct {

	ENDING_DEMO_WORK*	mainWork;
	GF_BGL_INI*		bgl;

	int  timer;
	int  subSeq;

}SCENE_WORK;


//==============================================================
// Prototype
//==============================================================
static BOOL setup_bg( SCENE_WORK* wk, int* seq );
static void cleanup_bg( SCENE_WORK* wk );




//------------------------------------------------------------------
/**
 * シーン２：初期化処理開始
 *
 * @param   mainWork		
 * @param   bgl		
 *
 * @retval  void*		
 */
//------------------------------------------------------------------
void* Ending_Scene2Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl )
{
	SCENE_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(SCENE_WORK) );
	if( wk )
	{
		wk->mainWork = mainWork;
		wk->bgl = bgl;
		wk->timer = 0;
		wk->subSeq = 0;
	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン２：初期化終了待ち
 *
 * @param   wk_ptr		
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Ending_Scene2InitWait( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	if( setup_bg( wk, seq ) )
	{
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーン２：終了処理
 *
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
BOOL Ending_Scene2Quit( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	cleanup_bg( wk );
	sys_FreeMemoryEz( wk );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * シーン２：メイン
 *
 * @param   wk_ptr		
 * @param   seq		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL Ending_Scene2Main( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	switch( *seq ){
	case 0:
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, FALSE);
		ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK,
			SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
		(*seq)++;
		break;

	case 1:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			(*seq)++;
		}
		break;

	case 2:
		if( ++(wk->timer) >= SCENE_FRAMES )
		{
			ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
				SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
			(*seq)++;
		}
		break;

	case 3:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, TRUE);
			return TRUE;
		}
		break;

	}
	return FALSE;
}




static BOOL setup_bg( SCENE_WORK* wk, int* seq )
{
	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	switch( *seq ){
	case 0:
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &header2, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_S, &header2, GF_BGL_MODE_TEXT );
		(*seq)++;
		break;

	case 1:
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg_cut_bag_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg_black_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 2:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg_cut_bag_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 3:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg_black_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	default:
		return TRUE;
	}
	return FALSE;
}

static void cleanup_bg( SCENE_WORK* wk )
{
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_S );
}
