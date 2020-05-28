//============================================================================================
/**
 * @file	demo_ending_scene5.c
 * @brief	エンディングデモ（シーン５：青空＆ピカチュウ雲）
 * @author	taya
 * @date	2006.06.02
 */
//============================================================================================
#include "common.h"

#include "demo_ending_common.h"





typedef struct {

	ENDING_DEMO_WORK*	mainWork;
	GF_BGL_INI*		bgl;

	ENDING_BGCHANGE_WORK*   mainEffect;
	ENDING_BGCHANGE_WORK*   subEffect;

	NNSG2dImageProxy		imgProxy;
	NNSG2dImagePaletteProxy	pltProxy;
	ENDING_CLANM_PACK*		clpack;

	CLACT_WORK_PTR	heroActor;
	CLACT_WORK_PTR	islandActor;

	fx32  cloudPos;
	fx32  cloudSpeed;
	fx32  islandPos;
	fx32  islandSpeed;

	int  timer;
	int  subSeq;

}SCENE_WORK;


//==============================================================
// Prototype
//==============================================================
static BOOL setup_graphic_datas( SCENE_WORK* wk, int* seq );
static void cleanup_graphic_datas( SCENE_WORK* wk );




//------------------------------------------------------------------
/**
 * シーン５：初期化処理開始
 *
 * @param   mainWork		
 * @param   bgl		
 *
 * @retval  void*		
 */
//------------------------------------------------------------------
void* Ending_Scene5Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl )
{
	SCENE_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(SCENE_WORK) );
	if( wk )
	{
		wk->mainWork = mainWork;
		wk->bgl = bgl;
		wk->timer = 0;
		wk->subSeq = 0;
		wk->heroActor = Ending_GetHeroActor(mainWork);

		wk->islandActor = NULL;
		wk->mainEffect = NULL;
		wk->subEffect = NULL;
		wk->clpack = NULL;

		wk->cloudPos = 0;
		wk->islandPos = 0;
	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン５：初期化終了待ち
 *
 * @param   wk_ptr		
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Ending_Scene5InitWait( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	if( setup_graphic_datas( wk, seq ) )
	{
		CLACT_AnmChg( wk->heroActor, ENDING_PLAYER_ANM_MORNING );
		CLACT_SetDrawFlag( wk->heroActor, TRUE );
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーン５：終了処理
 *
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
BOOL Ending_Scene5Quit( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	cleanup_graphic_datas( wk );
	sys_FreeMemoryEz( wk );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * シーン５：メイン
 *
 * @param   wk_ptr		
 * @param   seq		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL Ending_Scene5Main( void* wk_ptr, int* seq )
{
	enum {
		#ifndef DEBUG_FASTMODE
		BG_1TO2_FRAMES = 370,
		BG_2TO3_FRAMES = 270,
		AFTER_BGCHANGE_FRAMES = 300,
		BGCHANGE_FRAMES = 90,
		#else
		BG_1TO2_FRAMES = 30,
		BG_2TO3_FRAMES = 30,
		AFTER_BGCHANGE_FRAMES = 30,
		BGCHANGE_FRAMES = 10,
		#endif

		CLOUD_SPEED = 0x80,
		ISLAND_ACT_SPEED = 0x40,
	};

	SCENE_WORK* wk = wk_ptr;


	{
		int pos;

		wk->cloudPos += CLOUD_SPEED;
		pos = wk->cloudPos >> FX32_SHIFT;

		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, pos );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME2_S, GF_BGL_SCROLL_X_SET, pos );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, pos );
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_S, GF_BGL_SCROLL_X_SET, pos );
	}

	if( wk->islandActor )
	{
		VecFx32  pos = *CLACT_GetMatrix( wk->islandActor );
		pos.y -= ISLAND_ACT_SPEED;
		CLACT_SetMatrix( wk->islandActor, &pos );
	}

	switch( *seq ){
	case 0:
		ChangeBrightnessRequest( 16, BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK,
			SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
		(*seq)++;
		break;

	case 1:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			// ポリゴン面と２Ｄ面にアンチエイリアスがかかるように
			G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE , GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, 16, 0 );
			(*seq)++;
		}
		break;

	case 2:
		if( ++(wk->timer) >= BG_1TO2_FRAMES )
		{
			wk->mainEffect = Ending_BGChange_Start( wk->mainWork, 0, 0, BGCHANGE_FRAMES );
			wk->subEffect = Ending_BGChange_Start( wk->mainWork, 1, 0, BGCHANGE_FRAMES );
			(*seq)++;
		}
		break;

	case 3:
		if(	Ending_BGChange_Wait( wk->mainEffect )
		&&	Ending_BGChange_Wait( wk->subEffect )
		){
			Ending_BGChange_Quit( wk->mainEffect );
			Ending_BGChange_Quit( wk->subEffect );
			wk->mainEffect = NULL;
			wk->subEffect = NULL;

			ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg01_3d_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg01_3u_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg01_3d_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg01_3u_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );

			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 4:
		if( ++(wk->timer) >= BG_2TO3_FRAMES )
		{
			wk->mainEffect = Ending_BGChange_Start( wk->mainWork, 0, 1, BGCHANGE_FRAMES );
			wk->subEffect = Ending_BGChange_Start( wk->mainWork, 1, 1, BGCHANGE_FRAMES );
			(*seq)++;
		}
		break;

	case 5:
		if(	Ending_BGChange_Wait( wk->mainEffect )
		&&	Ending_BGChange_Wait( wk->subEffect )
		){
			Ending_BGChange_Quit( wk->mainEffect );
			Ending_BGChange_Quit( wk->subEffect );
			wk->mainEffect = NULL;
			wk->subEffect = NULL;
			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 6:
		if( ++(wk->timer) >= AFTER_BGCHANGE_FRAMES )
		{
			ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
				SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
			(*seq)++;
		}
		break;

	case 7:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			CLACT_SetDrawFlag( wk->heroActor, FALSE );
			return TRUE;
		}

	}
	return FALSE;
}




static BOOL setup_graphic_datas( SCENE_WORK* wk, int* seq )
{
	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header3 = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x10000,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	switch( *seq ){
	case 0:
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &header2, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &header3, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_S, &header2, GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_S, &header3, GF_BGL_MODE_TEXT );
		(*seq)++;
		break;

	case 1:
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg01_1d_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg01_1u_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 2:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg01_1d_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 3:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg01_1u_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 4:
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg01_2d_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg01_2u_nscr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 5:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg01_2d_ncgr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 6:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg01_2u_ncgr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 7:
		{
			CLACT_HEADER header;

			wk->clpack = Ending_LoadCellAnim( ARC_ENDING, NARC_ending_endobj_01_ncer, NARC_ending_endobj_01_nanr );

			NNS_G2dInitImageProxy(&wk->imgProxy);
			ArcUtil_CharSysLoad( ARC_ENDING, NARC_ending_endobj_01_ncgr, FALSE, CHAR_MAP_1D, 0,
				NNS_G2D_VRAM_TYPE_2DMAIN, OBJ_CHARPOS_ISLAND*0x20, HEAPID_ENDING_DEMO, &wk->imgProxy );

			NNS_G2dInitImagePaletteProxy(&wk->pltProxy);
			ArcUtil_PalSysLoad( ARC_ENDING, NARC_ending_endobj_01_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 0,
				HEAPID_ENDING_DEMO, &(wk->pltProxy) );

			Ending_SetActHeader( &header, wk->clpack, &wk->imgProxy, &wk->pltProxy, 2 );

			wk->islandActor = Ending_AddActor( wk->mainWork, &header, 0, DIFF_MAIN_SUB_LCD+192, ACTPRI_ISLAND,
				NNS_G2D_VRAM_TYPE_2DMAIN, TRUE );
		}
		(*seq)++;
		break;

	case 8:
		Ending_Change3dGroundType( wk->mainWork, ENDING_GRND_MORNING );
		(*seq)++;
		break;

	default:
		return TRUE;
	}
	return FALSE;
}

static void cleanup_graphic_datas( SCENE_WORK* wk )
{
	if( wk->islandActor )
	{
		CLACT_Delete( wk->islandActor );
	}

	if( wk->mainEffect )
	{
		Ending_BGChange_Quit( wk->mainEffect );
	}
	if( wk->subEffect )
	{
		Ending_BGChange_Quit( wk->subEffect );
	}

	if( wk->clpack )
	{
		Ending_UnloadCellAnim( wk->clpack );
	}

	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_S );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_S );
}
