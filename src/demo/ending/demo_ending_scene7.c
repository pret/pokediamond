//============================================================================================
/**
 * @file	demo_ending_scene7.c
 * @brief	エンディングデモ（シーン７：帰宅）
 * @author	taya
 * @date	2006.06.08
 */
//============================================================================================
#include "common.h"

#include "demo_ending_common.h"



enum {
	STAR_LINE_DELAY_FRAMES = 5,


	PALANIM_LCD_MAIN = 0,
	PALANIM_LCD_SUB = 1,
};


typedef struct {
	int seq;
	int cnt;
	int timer;
	int move_frames;
	int wait_frames;

	VecFx32  pos;
	VecFx32  speed;
	VecFx32  linePos;
	VecFx32  prev_pos[STAR_LINE_DELAY_FRAMES];
	int      pos_p;
	BOOL     lineDispFlag;

	TCB_PTR	 tcb;
	void*    mainWork;


}STAR_MOVE_WORK;



typedef struct {

	ENDING_DEMO_WORK*	mainWork;
	GF_BGL_INI*		bgl;

	ENDING_BGCHANGE_WORK*   mainEffect;
	ENDING_BGCHANGE_WORK*   subEffect;

	CLACT_WORK_PTR	heroActor;

	CLACT_WORK_PTR	starActor;
	CLACT_WORK_PTR	lineActor;
	NNSG2dImageProxy		imgProxy;
	NNSG2dImagePaletteProxy	pltProxy;
	ENDING_CLANM_PACK*		clpack;

	void*				palLoadPtr;
	NNSG2dPaletteData*	palData;
	TCB_PTR				mainPalAnimTask;
	TCB_PTR				subPalAnimTask;

	STAR_MOVE_WORK   starMoveWork;


	int  timer;
	int  subSeq;

}SCENE_WORK;



enum {
	ANM_LINE,
	ANM_STAR,
};

//==============================================================
// Prototype
//==============================================================
static BOOL setup_braphics( SCENE_WORK* wk, int* seq );
static void cleanup_graphics( SCENE_WORK* wk );
static void init_star_act( SCENE_WORK* mainWork );
static void quit_star_act( SCENE_WORK* mainWork );
static void start_star_act( SCENE_WORK* mainWork );
static BOOL wait_star_act( SCENE_WORK* mainWork );
static void star_move_task( TCB_PTR tcb, void* wk_adrs );
static TCB_PTR AddPalAnimTask( const u8* animTbl, int tblSize, int interval, int lcd, const u16* palData );
static void DelPalAnimTask( TCB_PTR tcb );
static void PalAnimTask( TCB_PTR tcb, void* wk_adrs );




//------------------------------------------------------------------
/**
 * シーン７：初期化処理開始
 *
 * @param   mainWork		
 * @param   bgl		
 *
 * @retval  void*		
 */
//------------------------------------------------------------------
void* Ending_Scene7Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl )
{
	SCENE_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(SCENE_WORK) );
	if( wk )
	{
		wk->mainWork = mainWork;
		wk->bgl = bgl;
		wk->timer = 0;
		wk->subSeq = 0;
		wk->heroActor = Ending_GetHeroActor(mainWork);

		wk->starActor = NULL;
		wk->lineActor = NULL;
		wk->clpack = NULL;
		wk->mainEffect = NULL;
		wk->subEffect = NULL;
		wk->mainPalAnimTask = NULL;
		wk->subPalAnimTask = NULL;

		wk->palLoadPtr = ArcUtil_PalDataGet( ARC_ENDING, NARC_ending_endbg01_nclr, &(wk->palData), HEAPID_ENDING_DEMO );
		if( wk->palLoadPtr )
		{
			DC_FlushRange( wk->palData->pRawData, COMMON_BGPAL_USE_SIZE*0x20 );
		}

		init_star_act( wk );
	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン７：初期化終了待ち
 *
 * @param   wk_ptr		
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Ending_Scene7InitWait( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	if( setup_braphics( wk, seq ) )
	{
		CLACT_AnmChg( wk->heroActor, ENDING_PLAYER_ANM_NIGHT );
		CLACT_SetDrawFlag( wk->heroActor, TRUE );
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーン７：終了処理
 *
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
BOOL Ending_Scene7Quit( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk;
	OSIntrMode  oldIntr;

	oldIntr = OS_DisableInterrupts();

	wk = wk_ptr;

	quit_star_act( wk );
	cleanup_graphics( wk );

	if( wk->palLoadPtr )
	{
		sys_FreeMemoryEz( wk->palLoadPtr );
	}

	sys_FreeMemoryEz( wk );

	OS_RestoreInterrupts( oldIntr );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * シーン７：メイン
 *
 * @param   wk_ptr		
 * @param   seq		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL Ending_Scene7Main( void* wk_ptr, int* seq )
{
	enum {
		#ifndef DEBUG_FASTMODE_SCENE7
		STAR_APPEAR_FRAMES = 240,
		BGCHANGE_1ST_FRAMES = 150,
		BGCHANGE_2ND_FRAMES = 200,
		AFTER_LISTEND_FRAMES = 90,
		AFTER_DISPEND_FRAMES = 150,
		AFTER_BLACKOUT_FRAMES = 45,
		BGCHANGE_EFFECT_FRAMES = 90,
		#else
		STAR_APPEAR_FRAMES = 6,
		BGCHANGE_1ST_FRAMES = 30,
		BGCHANGE_2ND_FRAMES = 30,
		AFTER_LISTEND_FRAMES = 10,
		AFTER_DISPEND_FRAMES = 10,
		AFTER_BLACKOUT_FRAMES = 5,
		BGCHANGE_EFFECT_FRAMES = 10,
		#endif
	};

	SCENE_WORK* wk = wk_ptr;

	switch( *seq ){
	case 0:
		ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK,
			SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
		(*seq)++;
		break;

	case 1:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			// ポリゴン面と２Ｄ面にアンチエイリアスがかかるように
			G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE , GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, 10, 0 );
			(*seq)++;
		}
		break;

	case 2:
		if( ++(wk->timer) >= STAR_APPEAR_FRAMES )
		{
			start_star_act( wk );
			(*seq)++;
		}
		break;

	case 3:
		if( wait_star_act( wk ) )
		{
			G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16 );
			G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16 );

			ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_2d_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_1u_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_2d_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_1u_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 4:
		if(++(wk->timer) > BGCHANGE_1ST_FRAMES)
		{
			wk->mainEffect = Ending_BGChange_Start( wk->mainWork, 0, 1, BGCHANGE_EFFECT_FRAMES );
			wk->subEffect = Ending_BGChange_Start( wk->mainWork, 1, 1, BGCHANGE_EFFECT_FRAMES );
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

			ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_3d_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_2u_nscr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_3d_ncgr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_2u_ncgr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );

			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 6:
		if( ++(wk->timer) >= BGCHANGE_2ND_FRAMES )
		{
			wk->mainEffect = Ending_BGChange_Start( wk->mainWork, 0, 0, BGCHANGE_EFFECT_FRAMES );
			wk->subEffect = Ending_BGChange_Start( wk->mainWork, 1, 0, BGCHANGE_EFFECT_FRAMES );
			(*seq)++;
		}
		break;

	case 7:
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

	case 8:
		if( Ending_GetListEndFlag( wk->mainWork ) )
		{
			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 9:
		if( ++(wk->timer) >= AFTER_LISTEND_FRAMES )
		{
			EndingDemo_DispEndString_Start( wk->mainWork );
			(*seq)++;
		}
		break;

	case 10:
		if( EndingDemo_DispEndString_Wait( wk->mainWork ) )
		{
			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 11:
		if( ++(wk->timer) >= AFTER_DISPEND_FRAMES )
		{
			ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
				SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
			(*seq)++;
		}
		break;

	case 12:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, FALSE);
			CLACT_SetDrawFlag( wk->heroActor, FALSE );

			ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_reserve_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_reserve_ncgr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
			ArcUtil_PalSet( ARC_ENDING, NARC_ending_reserve_nclr, PALTYPE_MAIN_BG, 0, 0x20, HEAPID_ENDING_DEMO );

			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 13:
		if( ++(wk->timer) >= AFTER_BLACKOUT_FRAMES )
		{
			ChangeBrightnessRequest( 16, BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK,
				SCENE_BRIGHT_PLANEMASK, MASK_MAIN_DISPLAY );
			(*seq)++;
		}
		break;

	case 14:
		if( IsFinishedBrightnessChg(MASK_MAIN_DISPLAY) )
		{
			return TRUE;
		}

	}
	return FALSE;
}




static BOOL setup_braphics( SCENE_WORK* wk, int* seq )
{
	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header3 = {
		0, 0, 0x0000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
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
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_1d_slit_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_1u_slit_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 2:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_1d_slit_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 3:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_1u_slit_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 4:
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_1d_nscr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg02_1u_nscr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 5:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_1d_ncgr, wk->bgl, GF_BGL_FRAME3_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 6:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg02_1u_ncgr, wk->bgl, GF_BGL_FRAME3_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 7:
		Ending_Change3dGroundType( wk->mainWork, ENDING_GRND_NIGHT );
		(*seq)++;
		break;

	case 8:
		{
			wk->clpack = Ending_LoadCellAnim( ARC_ENDING, NARC_ending_endobj_star_ncer, NARC_ending_endobj_star_nanr );

			NNS_G2dInitImageProxy(&wk->imgProxy);
			NNS_G2dInitImagePaletteProxy(&wk->pltProxy);

			ArcUtil_CharSysLoad( ARC_ENDING, NARC_ending_endobj_star_ncgr, FALSE, CHAR_MAP_1D, 0,
				NNS_G2D_VRAM_TYPE_2DMAIN, OBJ_CHARPOS_STAR*0x20, HEAPID_ENDING_DEMO, &wk->imgProxy );

			ArcUtil_PalSysLoad( ARC_ENDING, NARC_ending_endobj_star_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 0,
				HEAPID_ENDING_DEMO, &(wk->pltProxy) );
		}
		(*seq)++;
		break;

	case 9:
		{
			CLACT_HEADER header;

			ArcUtil_CharSysLoad( ARC_ENDING, NARC_ending_endobj_star_ncgr, FALSE, CHAR_MAP_1D, 0,
				NNS_G2D_VRAM_TYPE_2DSUB, OBJ_CHARPOS_STAR*0x20, HEAPID_ENDING_DEMO, &wk->imgProxy );

			ArcUtil_PalSysLoad( ARC_ENDING, NARC_ending_endobj_star_nclr, NNS_G2D_VRAM_TYPE_2DSUB, 0,
				HEAPID_ENDING_DEMO, &(wk->pltProxy) );

			Ending_SetActHeader( &header, wk->clpack, &wk->imgProxy, &wk->pltProxy, 2 );

			wk->starActor = Ending_AddActor( wk->mainWork, &header, 0, 0, ACTPRI_STAR, NNS_G2D_VRAM_TYPE_2DMAIN, FALSE );
			wk->lineActor = Ending_AddActor( wk->mainWork, &header, 0, 0, ACTPRI_STARLINE, NNS_G2D_VRAM_TYPE_2DMAIN, FALSE );

			CLACT_BGPriorityChg( wk->lineActor, 3 );
			CLACT_ObjModeSet( wk->lineActor, GX_OAM_MODE_XLU );
			CLACT_AnmChg( wk->lineActor, ANM_LINE ); 
		}
		(*seq)++;
		break;

	case 10:
		{
			static const u8 mainPalAnimTbl[] = { 9, 8, 7, 8 };
			static const u8 subPalAnimTbl[] = { 4, 5, 6, 5 };

			wk->mainPalAnimTask = AddPalAnimTask( mainPalAnimTbl, NELEMS(mainPalAnimTbl),
										 3, PALANIM_LCD_MAIN, wk->palData->pRawData );

			wk->subPalAnimTask = AddPalAnimTask( subPalAnimTbl, NELEMS(subPalAnimTbl),
										 5, PALANIM_LCD_SUB, wk->palData->pRawData );
			(*seq)++;
		}
		break;

	default:
		return TRUE;
	}
	return FALSE;
}

static void cleanup_graphics( SCENE_WORK* wk )
{
	if( wk->mainPalAnimTask )
	{
		DelPalAnimTask( wk->mainPalAnimTask );
	}
	if( wk->subPalAnimTask )
	{
		DelPalAnimTask( wk->subPalAnimTask );
	}

	if( wk->starActor )
	{
		CLACT_Delete( wk->starActor );
	}
	if( wk->lineActor )
	{
		CLACT_Delete( wk->lineActor );
	}

	if( wk->clpack )
	{
		Ending_UnloadCellAnim( wk->clpack );
	}

	if( wk->mainEffect )
	{
		Ending_BGChange_Quit( wk->mainEffect );
	}
	if( wk->subEffect )
	{
		Ending_BGChange_Quit( wk->subEffect );
	}

	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_S );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_S );
}


static void init_star_act( SCENE_WORK* mainWork )
{
	STAR_MOVE_WORK* wk = &mainWork->starMoveWork;
	wk->tcb = NULL;
}

static void quit_star_act( SCENE_WORK* mainWork )
{
	STAR_MOVE_WORK* wk = &mainWork->starMoveWork;
	if( wk->tcb )
	{
		TCB_Delete( wk->tcb );
	}
}

static void start_star_act( SCENE_WORK* mainWork )
{
	STAR_MOVE_WORK* wk = &mainWork->starMoveWork;

	wk->seq = 0;
	wk->cnt = 0;
	wk->timer = 0;
	wk->pos_p = 0;
	wk->mainWork = mainWork;
	wk->tcb = VIntrTCB_Add( star_move_task, wk, TASKPRI_SCENE7_STARMOVE );
}

static BOOL wait_star_act( SCENE_WORK* mainWork )
{
	STAR_MOVE_WORK* wk = &mainWork->starMoveWork;
	return (wk->tcb == NULL);
}


static void star_move_task( TCB_PTR tcb, void* wk_adrs )
{
	static const struct {
		int  start_x;
		int  start_y;
		int  end_x;
		int  end_y;
		int  move_frames;
		int  wait_frames;
	}StarActParam[] = {
		{  167,   0, 197,  96, 24, 90 },
		{   26,   0,  42, 129, 24, 120 },
		{   79,  40, 136, DIFF_MAIN_SUB_LCD+100,  24, 120 },
		{  144, 131, 240, DIFF_MAIN_SUB_LCD+133, 24, 30 },
	};

	STAR_MOVE_WORK* wk = wk_adrs;
	SCENE_WORK* mainWork = wk->mainWork;

	switch( wk->seq ){
	case 0:
		{
			VecFx32 tmpVec;
			fx32 x, y;

			x = (StarActParam[ wk->cnt ].start_x) << FX32_SHIFT;
			y = (StarActParam[ wk->cnt ].start_y) << FX32_SHIFT;
			VEC_Set( &wk->pos, x, y, 0 );

			wk->move_frames = StarActParam[ wk->cnt ].move_frames;
			wk->wait_frames = StarActParam[ wk->cnt ].wait_frames;
			wk->speed.x = ((StarActParam[ wk->cnt ].end_x << FX32_SHIFT) - x) / wk->move_frames;
			wk->speed.y = ((StarActParam[ wk->cnt ].end_y << FX32_SHIFT) - y) / wk->move_frames;
			wk->speed.z = 0;

			CLACT_SetMatrix( mainWork->starActor, &(wk->pos) );
			CLACT_SetDrawFlag( mainWork->starActor, TRUE );
			CLACT_AnmChg( mainWork->starActor, ANM_STAR );

			VEC_Normalize( &wk->speed, &tmpVec );
			VEC_MultAdd( FX32_CONST(-40), &tmpVec, &wk->pos, &wk->linePos );

			CLACT_SetMatrix( mainWork->lineActor, &wk->linePos );
			CLACT_SetDrawFlag( mainWork->lineActor, TRUE );

			wk->pos_p = 0;
			wk->seq++;
		}
		break;


	case 1:
		if( wk->move_frames )
		{
			VEC_Add( &wk->pos, &wk->speed, &wk->pos );
			VEC_Add( &wk->linePos, &wk->speed, &wk->linePos );
			CLACT_SetMatrix( mainWork->starActor, &wk->pos );
			CLACT_SetMatrix( mainWork->lineActor, &wk->linePos );
			wk->move_frames--;
			break;
		}
		wk->move_frames = 20;
		CLACT_SetDrawFlag( mainWork->starActor, FALSE );
		wk->seq++;
		/* fallthru */
	case 2:
		if( wk->move_frames )
		{
			VEC_Add( &wk->linePos, &wk->speed, &wk->linePos );
			CLACT_SetMatrix( mainWork->lineActor, &wk->linePos );
			wk->move_frames--;
		}
		else
		{
			CLACT_SetDrawFlag( mainWork->lineActor, FALSE );
			wk->seq++;
		}
		break;

	case 3:
		if( wk->wait_frames )
		{
			wk->wait_frames--;
		}
		else
		{
			if(++(wk->cnt) < NELEMS(StarActParam))
			{
				wk->seq = 0;
			}
			else
			{
				TCB_Delete( tcb );
				wk->tcb = NULL;
			}
		}
	}
}






//======================================================================================
// パレットアニメタスク
//======================================================================================

typedef struct {

	int timer;
	int interval;
	int pos;
	int posMax;
	int lcd;

	const u8*  animTbl;
	const u16* palData;

}PALANIM_WORK;


static TCB_PTR AddPalAnimTask( const u8* animTbl, int tblSize, int interval, int lcd, const u16* palData )
{
	PALANIM_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(PALANIM_WORK) );
	if( wk )
	{
		TCB_PTR tcb;

		wk->timer = 0;
		wk->pos = 0;

		wk->palData = palData;
		wk->animTbl = animTbl;
		wk->posMax = tblSize;
		wk->interval = interval;
		wk->lcd = lcd;

		tcb = VWaitTCB_Add( PalAnimTask, wk, TASKPRI_SCENE7_PALANIM );
		if( tcb == NULL )
		{
			sys_FreeMemoryEz( wk );
		}
		return tcb;
	}
	return NULL;
}

static void DelPalAnimTask( TCB_PTR tcb )
{
	if( tcb )
	{
		sys_FreeMemoryEz( TCB_GetWork( tcb ) );
		TCB_Delete( tcb );
	}
}


static void PalAnimTask( TCB_PTR tcb, void* wk_adrs )
{
	PALANIM_WORK* wk = wk_adrs;

	if( ++(wk->timer) > wk->interval )
	{
		int pos = (wk->animTbl[ wk->pos ] - COMMON_BG_PALPOS) * 16;

		if( wk->lcd == PALANIM_LCD_MAIN)
		{
			GX_LoadBGPltt( &wk->palData[ pos ], 0x0a*0x20, 0x20 );
		}
		else
		{
			GXS_LoadBGPltt( &wk->palData[ pos ], 0x0c*0x20, 0x20 );
		}

		if( ++(wk->pos) >= wk->posMax )
		{
			wk->pos = 0;
		}

		wk->timer = 0;
	}
}

