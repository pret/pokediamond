//============================================================================================
/**
 * @file	demo_ending_scene3.c
 * @brief	エンディングデモ（シーン３：ポケモンシルエット）
 * @author	taya
 * @date	2006.06.08
 */
//============================================================================================
#include "common.h"
#include "system\gra_tool.h"
#include "savedata\zukanwork.h"
#include "battle\graphic\batt_obj_def.h"

#include "demo_ending_common.h"



//==============================================================
// Const
//==============================================================
enum {
	#ifndef DEBUG_FASTMODE
	SCENE_FRAMES = 25 * 30 + 15,
	POKE_ADD_FRAMES = 100,
	#else
	SCENE_FRAMES = 30,
	POKE_ADD_FRAMES = 6,
	#endif

	DISP_POKE_MAX = 6,

	// ポケモンアクター１体分キャラ数
	POKE_ACT_CHARS = 100,
	POKE_ACT_CGX_BYTESIZE = POKE_ACT_CHARS * 0x20,
};


//==============================================================
// Work
//==============================================================

typedef struct {

	ENDING_DEMO_WORK*	mainWork;
	GF_BGL_INI*		bgl;

	ENDING_CLANM_PACK*		clpackCircle;
	ENDING_CLANM_PACK*		clpackPoke;
	NNSG2dImageProxy		imgProxyCircle;
	NNSG2dImagePaletteProxy	pltProxy;

	CLACT_WORK_PTR		actCircle[ DISP_POKE_MAX ];
	CLACT_WORK_PTR		actPoke[ DISP_POKE_MAX ];
	NNSG2dImageProxy	imgProxyPoke[ DISP_POKE_MAX ];
	TCB_PTR				taskPoke[ DISP_POKE_MAX ];
	TCB_PTR				taskPokeCtrl;

	const POKE_ACT_PARAM*  pokeParam;
	int		pokeCount;

	u8  pokeCgxBuf[ POKE_ACT_CGX_BYTESIZE ];

	int  timer;
	int  subSeq;

	u16	randSeed;
	u16	actCnt;


}SCENE_WORK;


//==============================================================
// Prototype
//==============================================================
static BOOL setup_graphics( SCENE_WORK* wk, int* seq );
static void cleanup_graphics( SCENE_WORK* wk );
static inline int  round_poke_num( SCENE_WORK* wk, int n );
static inline void get_sprite_arc( SOFT_SPRITE_ARC* arc, const POKE_ACT_PARAM* param );
static inline void trans_poke_cgx( SCENE_WORK* wk, int actID, int pokeID );
static void AddNewPokeActor( SCENE_WORK* wk, int num );
static void PokeMoveTask( TCB_PTR tcb, void* wk_ptr );
static void PokeCtrlTask( TCB_PTR tcb, void* wk_ptr );




//------------------------------------------------------------------
/**
 * シーン３：初期化処理開始
 *
 * @param   mainWork		
 * @param   bgl		
 *
 * @retval  void*		
 */
//------------------------------------------------------------------
void* Ending_Scene3Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl )
{
	SCENE_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(SCENE_WORK) );
	if( wk )
	{
		int i;

		wk->mainWork = mainWork;
		wk->bgl = bgl;
		wk->timer = 0;
		wk->subSeq = 0;

		wk->actCnt = 0;
		wk->randSeed = gf_rand();

		wk->pokeCount = EndingDemo_GetPokeActCount( mainWork );
		wk->pokeParam = EndingDemo_GetPokeActParamTable( mainWork );
		wk->taskPokeCtrl = TCB_Add( PokeCtrlTask, wk, 0 );

		wk->clpackPoke = NULL;
		wk->clpackCircle = NULL;

		for(i=0; i<DISP_POKE_MAX; i++)
		{
			wk->actPoke[i] = NULL;
			wk->actCircle[i] = NULL;
			wk->taskPoke[i] = NULL;
		}

	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン３：初期化終了待ち
 *
 * @param   wk_ptr		
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Ending_Scene3InitWait( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	if( setup_graphics( wk, seq ) )
	{
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーン３：終了処理
 *
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
BOOL Ending_Scene3Quit( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	gf_srand( wk->randSeed );

	cleanup_graphics( wk );
	sys_FreeMemoryEz( wk );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * シーン３：メイン
 *
 * @param   wk_ptr		
 * @param   seq		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL Ending_Scene3Main( void* wk_ptr, int* seq )
{
	SCENE_WORK* wk = wk_ptr;

	switch( *seq ){
	case 0:
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, FALSE);
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, FALSE);
		ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK,
			SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
		(*seq)++;
		break;

	case 1:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 2:
		if( wk->timer ==  0)
		{
			wk->timer = POKE_ADD_FRAMES;
			AddNewPokeActor( wk, wk->actCnt );
			if(++(wk->actCnt) >= DISP_POKE_MAX )
			{
				(*seq)++;
			}
		}
		else
		{
			wk->timer--;
		}
		break;

	case 3:
		if( ++(wk->timer) >= SCENE_FRAMES )
		{
			ChangeBrightnessRequest( SCENE_FADE_FRAMES, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
				SCENE_BRIGHT_PLANEMASK, MASK_DOUBLE_DISPLAY );
			(*seq)++;
		}
		break;

	default:
		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) )
		{
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, TRUE);
			GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, TRUE);
			return TRUE;
		}
		break;

	}
	return FALSE;
}




static BOOL setup_graphics( SCENE_WORK* wk, int* seq )
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
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg_black_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_endbg_black_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 2:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg_black_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 3:
		ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_endbg_black_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, FALSE, HEAPID_ENDING_DEMO );
		(*seq)++;
		break;

	case 4:
		wk->clpackCircle = Ending_LoadCellAnim( ARC_ENDING, NARC_ending_poke_circle_ncer, NARC_ending_poke_circle_nanr );
		wk->clpackPoke = Ending_LoadCellAnim( ARC_BATT_OBJ, POKE_OAM_NCER, POKE_OAM_NANR );
		(*seq)++;
		break;

	case 5:
		{
			NNS_G2dInitImageProxy( &(wk->imgProxyCircle) );
			NNS_G2dInitImagePaletteProxy( &(wk->pltProxy) );

			ArcUtil_CharSysLoad( ARC_ENDING, NARC_ending_poke_circle_ncgr, FALSE, CHAR_MAP_1D,
				0, NNS_G2D_VRAM_TYPE_2DMAIN, OBJ_CHARPOS_POKE_CIRCLE*0x20, HEAPID_ENDING_DEMO, &wk->imgProxyCircle );
			ArcUtil_PalSysLoad( ARC_ENDING, NARC_ending_poke_circle_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 
				0, HEAPID_ENDING_DEMO, &(wk->pltProxy) );

			(*seq)++;
		}
		break;

	case 6:
		{
			CLACT_HEADER  header;
			int i;

			Ending_SetActHeader( &header, wk->clpackCircle, &(wk->imgProxyCircle), &(wk->pltProxy), 1 );

			for(i=0; i<DISP_POKE_MAX; i++)
			{
				wk->actCircle[i] = Ending_AddActor( wk->mainWork, &header, 0, 0, ACTPRI_CIRCLE, 
						NNS_G2D_VRAM_TYPE_2DMAIN, FALSE );
			}
			(*seq)++;
		}
		break;

	case 7:
		{
			void* loadPtr;
			NNSG2dCharacterData*	charData;

			loadPtr = ArcUtil_CharDataGet( ARC_BATT_OBJ, POKE_OAM_NCGR, FALSE, &charData, HEAPID_ENDING_DEMO );
			if( loadPtr )
			{
				int i;
				for(i=0; i<DISP_POKE_MAX; i++)
				{
					NNS_G2dInitImageProxy(&wk->imgProxyPoke[i]);
					NNS_G2dLoadImage1DMapping( charData, OBJ_CHARPOS_POKEMON*0x20 + POKE_ACT_CGX_BYTESIZE*i,
						NNS_G2D_VRAM_TYPE_2DMAIN, &wk->imgProxyPoke[i] );
				}
				sys_FreeMemoryEz( loadPtr );
			}
			(*seq)++;
		}
		break;

	case 8:
		{
			CLACT_HEADER  header;
			int i;

			for(i=0; i<DISP_POKE_MAX; i++)
			{
				Ending_SetActHeader( &header, wk->clpackPoke, &(wk->imgProxyPoke[i]), &(wk->pltProxy), 1 );
				wk->actPoke[i] = Ending_AddActor( wk->mainWork, &header, 0, 0, ACTPRI_POKEMON, 
						NNS_G2D_VRAM_TYPE_2DMAIN, FALSE );
				CLACT_PaletteOffsetChg( wk->actPoke[i], OBJ_PALPOS_POKE );
			}
			(*seq)++;
		}
		break;

	default:
//		gf_srand( 0x5413 );
		gf_srand( 0x3485 );
		return TRUE;
	}
	return FALSE;
}

static void cleanup_graphics( SCENE_WORK* wk )
{
	OSIntrMode  oldIntr;
	int i;

	oldIntr = OS_DisableInterrupts();

	for(i=0; i<DISP_POKE_MAX; i++)
	{
		if( wk->actCircle[i] )
		{
			CLACT_Delete( wk->actCircle[i] );
		}
		if( wk->actPoke[i] )
		{
			CLACT_Delete( wk->actPoke[i] );
		}
		if( wk->taskPoke[i] )
		{
			sys_FreeMemoryEz( TCB_GetWork(wk->taskPoke[i]) );
			TCB_Delete( wk->taskPoke[i] );
		}
	}

	if( wk->taskPokeCtrl )
	{
		TCB_Delete( wk->taskPokeCtrl );
	}

	if( wk->clpackCircle )
	{
		Ending_UnloadCellAnim( wk->clpackCircle );
	}
	if( wk->clpackPoke )
	{
		Ending_UnloadCellAnim( wk->clpackPoke );
	}

	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_S );

	OS_RestoreInterrupts( oldIntr );
}










typedef struct {
	int	seq;
	SCENE_WORK*  mainWk;

	int  id;
	int  pokeID;

	CLACT_WORK_PTR  actPoke;
	CLACT_WORK_PTR  actCircle;
	VecFx32         pos;
	fx32            speed;

	fx32		sinVal;
	fx32		sinAdd;
	fx32		ypos;
	fx32		height;

}POKEACT_CTRL;


enum {
	POKE_SPEED_MAX = FX32_CONST(0.8f),
	POKE_SPEED_MIN = FX32_CONST(0.4f),
	POKE_SPEED_DIFF = POKE_SPEED_MAX - POKE_SPEED_MIN,

	POKE_YPOS_MAX = DIFF_MAIN_SUB_LCD + 160,
	POKE_YPOS_MIN = DIFF_MAIN_SUB_LCD + 32,
	POKE_YPOS_RANGE = POKE_YPOS_MAX - POKE_YPOS_MIN,

	POKE_SINMOVE_SPEED_MAX = 4,
	POKE_SINMOVE_SPEED_MIN = 2,
	POKE_SINMOVE_SPEED_RANGE = POKE_SINMOVE_SPEED_MAX - POKE_SINMOVE_SPEED_MIN,

	POKE_SINMOVE_HEIGHT_MAX = 16,
	POKE_SINMOVE_HEIGHT_MIN = 4,
	POKE_SINMOVE_HEIGHT_RANGE = POKE_SINMOVE_HEIGHT_MAX - POKE_SINMOVE_HEIGHT_MIN,

};

enum {
	POKETASK_SEQ_STOP = 0,
	POKETASK_SEQ_MOVE,
};

static inline int  round_poke_num( SCENE_WORK* wk, int n )
{
	if( n >= wk->pokeCount )
	{
		return n % wk->pokeCount;
	}
	return n;
}
static inline void get_sprite_arc( SOFT_SPRITE_ARC* arc, const POKE_ACT_PARAM* param )
{
	PokeGraArcDataGet( arc, param->number, param->sex, PARA_FRONT, 0, param->form, param->rand );
}

static inline void trans_poke_cgx( SCENE_WORK* wk, int actID, int pokeID )
{
	static const CHANGES_INTO_DATA_RECT rect = {
		POKE_TEX_X,
		POKE_TEX_Y,
		POKE_TEX_W,
		POKE_TEX_H,
	};
	SOFT_SPRITE_ARC  arc;

	get_sprite_arc( &arc, &wk->pokeParam[pokeID] );

	ChangesInto_OAM_from_PokeTex_RC( arc.arc_no, arc.index_chr, HEAPID_ENDING_DEMO, &rect, wk->pokeCgxBuf );
	DC_FlushRange( wk->pokeCgxBuf, sizeof(wk->pokeCgxBuf) );
	GX_LoadOBJ( wk->pokeCgxBuf, OBJ_CHARPOS_POKEMON*0x20+POKE_ACT_CGX_BYTESIZE*actID, POKE_ACT_CGX_BYTESIZE );
}

static inline void set_poke_moveparam( POKEACT_CTRL* ctrl )
{
	ctrl->pos.x = (256+56)<<FX32_SHIFT;
	ctrl->pos.y = (POKE_YPOS_MIN + (gf_rand() % POKE_YPOS_RANGE)) << FX32_SHIFT;
	ctrl->pos.z = 0;
	ctrl->speed = POKE_SPEED_MIN + (gf_rand() % POKE_SPEED_DIFF);

	ctrl->ypos = ctrl->pos.y;
	ctrl->sinVal = 0;
	ctrl->sinAdd = (POKE_SINMOVE_SPEED_MIN + (gf_rand() % POKE_SINMOVE_SPEED_RANGE)) << FX32_SHIFT;
	ctrl->height = POKE_SINMOVE_HEIGHT_MIN + (gf_rand() % POKE_SINMOVE_HEIGHT_RANGE);
}


static void AddNewPokeActor( SCENE_WORK* wk, int num )
{
	POKEACT_CTRL* ctrl = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(POKEACT_CTRL) );
	if( ctrl )
	{
		ctrl->seq = POKETASK_SEQ_MOVE;
		ctrl->mainWk = wk;
		ctrl->id = num;
		ctrl->pokeID = round_poke_num(wk, num);
		ctrl->actCircle = wk->actCircle[num];
		ctrl->actPoke = wk->actPoke[num];

		trans_poke_cgx( wk, ctrl->id, ctrl->pokeID );
		set_poke_moveparam( ctrl );

		CLACT_SetMatrix( ctrl->actCircle, &ctrl->pos );
		CLACT_SetMatrix( ctrl->actPoke, &ctrl->pos );
		CLACT_SetDrawFlag( ctrl->actCircle, TRUE );
		CLACT_SetDrawFlag( ctrl->actPoke, TRUE );

		wk->taskPoke[num] = VIntrTCB_Add( PokeMoveTask, ctrl, TASKPRI_SCENE3_POKEMOVE);
	}
}


static void PokeMoveTask( TCB_PTR tcb, void* wk_ptr )
{
	POKEACT_CTRL* wk = wk_ptr;

	if( wk->seq == POKETASK_SEQ_MOVE )
	{
		int a;
		wk->sinVal += wk->sinAdd;
		if( wk->sinVal >= (360<<FX32_SHIFT) )
		{
			wk->sinVal -= (360<<FX32_SHIFT);
		}
		a = wk->sinVal >> FX32_SHIFT;
		wk->pos.y = wk->ypos + wk->height * FixSinCosTbl[a];
		wk->pos.x -= wk->speed;

		CLACT_SetMatrix( wk->actCircle, &wk->pos );
		CLACT_SetMatrix( wk->actPoke, &wk->pos );

		if( (wk->pos.x >> FX32_SHIFT) < -56 )
		{
			wk->seq = POKETASK_SEQ_STOP;
		}
	}
}





static void PokeCtrlTask( TCB_PTR tcb, void* wk_ptr )
{
	SCENE_WORK* wk = wk_ptr;
	int i;

	for(i=0; i<DISP_POKE_MAX; i++)
	{
		if( wk->taskPoke[i] )
		{
			POKEACT_CTRL* ctrl = TCB_GetWork( wk->taskPoke[i] );
			if( ctrl->seq == POKETASK_SEQ_STOP )
			{
				ctrl->pokeID = round_poke_num( wk, ctrl->pokeID + DISP_POKE_MAX );
				trans_poke_cgx( ctrl->mainWk, ctrl->id, ctrl->pokeID );
				set_poke_moveparam( ctrl );
				ctrl->seq = POKETASK_SEQ_MOVE;
			}
		}
	}
}

















