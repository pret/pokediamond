//============================================================================================
/**
 * @file	demo_ending_scene1.c
 * @brief	�G���f�B���O�f���i�V�[���P�F���Ă���j
 * @author	taya
 * @date	2006.06.05
 */
//============================================================================================
#include "common.h"

#include "demo_ending_common.h"


//==============================================================
// Const
//==============================================================
enum {

	#ifndef DEBUG_FASTMODE
	SCENE_FRAMES = 60 * 30,
	#else
	SCENE_FRAMES = 30,
	#endif


	BG_MOVE_LEN = -24,
	BG_DEFAULT_XOFS = 256,
};


//==============================================================
// Work
//==============================================================

typedef struct {

	ENDING_DEMO_WORK*	mainWork;
	GF_BGL_INI*		bgl;
	CLACT_WORK_PTR	heroActor;

	fx32   scrollOfs;
	fx32   scrollAdd;

	int  timer;
	int  subSeq;

}SCENE1_WORK;


//==============================================================
// Prototype
//==============================================================
static BOOL setup_bg( SCENE1_WORK* wk, int* seq );
static void cleanup_bg( SCENE1_WORK* wk );




//------------------------------------------------------------------
/**
 * �V�[���P�F�����������J�n
 *
 * @param   mainWork		
 * @param   bgl		
 *
 * @retval  void*		
 */
//------------------------------------------------------------------
void* Ending_Scene1Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl )
{
	SCENE1_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(SCENE1_WORK) );
	if( wk )
	{
		wk->mainWork = mainWork;
		wk->bgl = bgl;
		wk->timer = 0;
		wk->subSeq = 0;
		wk->heroActor = Ending_GetHeroActor( mainWork );

		wk->scrollOfs = 0;
		wk->scrollAdd = (BG_MOVE_LEN << FX32_SHIFT) / SCENE_FRAMES;
	}
	return wk;
}
//------------------------------------------------------------------
/**
 * �V�[���P�F�������I���҂�
 *
 * @param   wk_ptr		
 *
 * @retval  BOOL		TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL Ending_Scene1InitWait( void* wk_ptr, int* seq )
{
	SCENE1_WORK* wk = wk_ptr;

	if( setup_bg( wk, seq ) )
	{
		CLACT_AnmChg( wk->heroActor, ENDING_PLAYER_ANM_EVENING );
		CLACT_SetDrawFlag( wk->heroActor, TRUE );
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * �V�[���P�F�I������
 *
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
BOOL Ending_Scene1Quit( void* wk_ptr, int* seq )
{
	SCENE1_WORK* wk = wk_ptr;

	cleanup_bg( wk );
	sys_FreeMemoryEz( wk );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * �V�[���P�F���C��
 *
 * @param   wk_ptr		
 * @param   seq		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL Ending_Scene1Main( void* wk_ptr, int* seq )
{
	enum {
		BG_1TO2_FRAMES = 210,
		BG_2TO3_FRAMES = 210,
		AFTER_BGCHANGE_FRAMES = 210,
		BGCHANGE_FRAMES = 90,
	};

	SCENE1_WORK* wk = wk_ptr;

	{
		int ofs;
		wk->scrollOfs += wk->scrollAdd;
		ofs = BG_DEFAULT_XOFS + (wk->scrollOfs >> FX32_SHIFT);
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, ofs );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_X_SET, ofs );
	}

	switch( *seq ){
	case 0:
		if( ++(wk->timer) >= SCENE_FRAMES )
		{
			ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
				SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
			(*seq)++;
		}
		break;

	case 1:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			CLACT_SetDrawFlag( wk->heroActor, FALSE );
			return TRUE;
		}
		break;

	}
	return FALSE;
}




static BOOL setup_bg( SCENE1_WORK* wk, int* seq )
{
	static const GF_BGL_BGCNT_HEADER header2 = {
		BG_DEFAULT_XOFS, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
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
		ArcUtil_PalSetEx(ARC_ENDING, NARC_ending_endbg01_nclr, PALTYPE_MAIN_BG, 0,
				COMMON_BG_PALPOS*0x20, (16-COMMON_BG_PALPOS)*0x20, HEAPID_ENDING_DEMO );

		ArcUtil_PalSetEx(ARC_ENDING, NARC_ending_endbg01_nclr, PALTYPE_SUB_BG, 0,
				COMMON_BG_PALPOS*0x20, (16-COMMON_BG_PALPOS)*0x20, HEAPID_ENDING_DEMO );

		(*seq)++;
		break;

	case 2:
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg00_d_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg00_u_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 3:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg00_d_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 4:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg00_u_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	default:
		// �|���S���ʂƂQ�c�ʂɃA���`�G�C���A�X��������悤��
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE , GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, 16, 0 );
		return TRUE;
	}
	return FALSE;
}

static void cleanup_bg( SCENE1_WORK* wk )
{
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_S );

//	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
//	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_S );
}
