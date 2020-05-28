//============================================================================================
/**
 * @file	poketch_a28v.c
 * @bfief	ポケッチ（アプリNo28：ポケモンカウンター）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "poketool\pokeicon.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a28.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)
#define USE_BG_PALNO	(0)

enum {
	OBJ_PALPOS_NUM = 0,
	OBJ_PALPOS_POKE,	// ここから４個
};

enum {
	ACTID_POKE_NOW,
	ACTID_POKE_RANK1,
	ACTID_POKE_RANK2,
	ACTID_POKE_RANK3,

	ACTID_COUNT_NOW1,
	ACTID_COUNT_NOW2,
	ACTID_COUNT_NOW3,
	ACTID_COUNT_RANK1_1,
	ACTID_COUNT_RANK1_2,
	ACTID_COUNT_RANK1_3,
	ACTID_COUNT_RANK2_1,
	ACTID_COUNT_RANK2_2,
	ACTID_COUNT_RANK2_3,
	ACTID_COUNT_RANK3_1,
	ACTID_COUNT_RANK3_2,
	ACTID_COUNT_RANK3_3,

	ACTID_MAX,
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A28_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act[ACTID_MAX];
	PACT_CLANM_PACK    clpack_num;
	PACT_CLANM_PACK    clpack_poke;

	u32       arcIdx[4];

	PACT*     jumpAct;
	fx32      jumpDefYpos;
	fx32      jumpDefXpos;
	fx32      jumpYpos;

	u32       pokeIconCharPos;

};


//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdUpdate(TCB_PTR tcb, void *wk_ptr);
static void CmdTouch( TCB_PTR tcb, void* wk_ptr );
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void setanm_num_actors( PACT** act, u32 val );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A28_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワーク削除
 *
 * @param   wk		確保したワークアドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A28_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT,   CmdInit,   0 },
	{ CMD_QUIT,   CmdQuit,   0 },
	{ CMD_UPDATE, CmdUpdate, 0 },
	{ CMD_TOUCH,  CmdTouch,  0 },
	{ 0, NULL, 0 },
};


//------------------------------------------------------------------
/**
 * 描画コマンドのセット
 *
 * @param   cmd		コマンド
 * @param   view_wk_adrs	ワーク領域アドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A28_SetViewCommand(VIEWWORK* wk, u32 cmd)
{
	PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（単発）
 *
 * @param   cmd			コマンド
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A28_WaitViewCommand(VIEWWORK* wk, u32 cmd)
{
	return PoketchViewTool_WaitCommand(wk->cmd_store, cmd);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（全部）
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A28_WaitViewCommandAll(VIEWWORK* wk)
{
	return PoketchViewTool_WaitCommandAll(wk->cmd_store);
}



//------------------------------------------------------------------
/**
 * コマンド削除
 *
 * @param   cwk		コマンドワーク
 *
 */
//------------------------------------------------------------------
static void DeleteCommand(POKETCH_CMD_WORK* cwk)
{
	VIEWWORK *wk = PoketchViewTool_GetViewWork(cwk);
	PoketchViewTool_DelCommand( wk->cmd_store, cwk );
}

//------------------------------------------------------------------
/**
 * コマンド：画面構築
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdInit(TCB_PTR tcb, void *wk_ptr)
{
	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;
	const VIEWPARAM* vpara;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_pcount_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_pcount_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	setup_actors( vwk, vpara );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);
	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * コマンド：終了処理
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdQuit(TCB_PTR tcb, void *wk_ptr)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	cleanup_actors( vwk );

	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * コマンド：更新
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdUpdate(TCB_PTR tcb, void *wk_ptr)
{
	VIEWWORK* wk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	if( vpara->now_monsno )
	{
		u32  arcIndex = PokeIconCgxArcIndexGetByMonsNumber( vpara->now_monsno, FALSE, 0 );

		PoketchViewTool_SetupPokeIconCgx( wk->pokeIconCharPos, &arcIndex, 1, TRUE );
		PACT_SetPalOffset( wk->act[ACTID_POKE_NOW], OBJ_PALPOS_POKE+PokeIconPalNumGet(vpara->now_monsno, 0, FALSE) );
		setanm_num_actors( &(wk->act[ACTID_COUNT_NOW1]), vpara->now_count );
	}
	else
	{
		int i;
		PACT_SetVanish( wk->act[ACTID_POKE_NOW], TRUE );
		for(i=0; i<3; i++)
		{
			PACT_SetVanish( wk->act[ACTID_COUNT_NOW1+i], TRUE );
		}
	}

	DeleteCommand( wk_ptr );
}

static void CmdTouch( TCB_PTR tcb, void* wk_ptr )
{
	enum {
		JUMP_FRAMES = 16,
		JUMP_HEIGHT = 24,
	};
	VIEWWORK* wk;
	const VIEWPARAM* vpara;
	int seq;

	wk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );
	seq = PoketchViewTool_GetSeq(wk_ptr);

	switch( seq ){
	case 0:
		{
			wk->jumpAct = wk->act[ACTID_POKE_RANK1 + vpara->touch_poke];
			PACT_GetPos( wk->jumpAct, &(wk->jumpDefXpos), &(wk->jumpDefYpos) );
		}
		PoketchVoicePlay( vpara->rank_monsno[ vpara->touch_poke ] );
		PACT_ChangeAnmSeq( wk->jumpAct, POKEICON_ANM_NORMAL_L );
		PoketchViewTool_FwdSeq( wk_ptr );
		seq++;

		/* fallthru */

	default:
		{
			int p;
			fx32 j;

			p = ((((180<<FX32_SHIFT)/JUMP_FRAMES) * seq) + FX32_HALF) >> FX32_SHIFT;
			j = FixSinCosTbl[p] * JUMP_HEIGHT;
			PACT_SetPos( wk->jumpAct, wk->jumpDefXpos, wk->jumpDefYpos - j );
		}
		PoketchViewTool_FwdSeq( wk_ptr );
		break;

	case JUMP_FRAMES:
		PACT_SetPos( wk->jumpAct, wk->jumpDefXpos, wk->jumpDefYpos );
		PACT_ChangeAnmSeq( wk->jumpAct, POKEICON_ANM_OFF_L );
		DeleteCommand( wk_ptr );
		break;
	}
}


enum {
	NUMPOS_NOW_X = POKETCH_MONITOR_DOT_XORG + 128,
	NUMPOS_NOW_Y = POKETCH_MONITOR_DOT_YORG + 24,

	NUMPOS_RANK1_X = ICON_RANK1_XPOS - 12,
	NUMPOS_RANK1_Y = POKETCH_MONITOR_DOT_YORG + 128,

	NUMPOS_RANK2_X = ICON_RANK2_XPOS - 12,
	NUMPOS_RANK2_Y = NUMPOS_RANK1_Y + 16,

	NUMPOS_RANK3_X = ICON_RANK3_XPOS - 12,
	NUMPOS_RANK3_Y = NUMPOS_RANK1_Y + 24,

	NUMACT_DIFF_X = 8,
};


static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM  actparam[] = 
	{
		{ { FX32INT(ICON_NOW_XPOS), FX32INT(ICON_NOW_YPOS) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 10, TRUE },
		{ { FX32INT(ICON_RANK1_XPOS), FX32INT(ICON_RANK1_YPOS) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 0, TRUE },
		{ { FX32INT(ICON_RANK2_XPOS), FX32INT(ICON_RANK2_YPOS) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 1, TRUE },
		{ { FX32INT(ICON_RANK3_XPOS), FX32INT(ICON_RANK3_YPOS) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 2, TRUE },

		{ { FX32INT(NUMPOS_NOW_X+NUMACT_DIFF_X*0), FX32INT(NUMPOS_NOW_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_NOW_X+NUMACT_DIFF_X*1), FX32INT(NUMPOS_NOW_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_NOW_X+NUMACT_DIFF_X*2), FX32INT(NUMPOS_NOW_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },

		{ { FX32INT(NUMPOS_RANK1_X+NUMACT_DIFF_X*0), FX32INT(NUMPOS_RANK1_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_RANK1_X+NUMACT_DIFF_X*1), FX32INT(NUMPOS_RANK1_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_RANK1_X+NUMACT_DIFF_X*2), FX32INT(NUMPOS_RANK1_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },

		{ { FX32INT(NUMPOS_RANK2_X+NUMACT_DIFF_X*0), FX32INT(NUMPOS_RANK2_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_RANK2_X+NUMACT_DIFF_X*1), FX32INT(NUMPOS_RANK2_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_RANK2_X+NUMACT_DIFF_X*2), FX32INT(NUMPOS_RANK2_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },

		{ { FX32INT(NUMPOS_RANK3_X+NUMACT_DIFF_X*0), FX32INT(NUMPOS_RANK3_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_RANK3_X+NUMACT_DIFF_X*1), FX32INT(NUMPOS_RANK3_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
		{ { FX32INT(NUMPOS_RANK3_X+NUMACT_DIFF_X*2), FX32INT(NUMPOS_RANK3_Y) }, 0, PACT_FLIP_OFF,  BGPRI2,  3, FALSE },
	};


	u32  charpos;
	u32  monsno[4];
	int i, j, n;

	PACT_TOOL_LoadCellDatas( &wk->clpack_poke, ARC_POKETCH_IMG,
			NARC_poketch_pokeicon_ncer,NARC_poketch_pokeicon_nanr, POKETCH_APP_VIEW_HEAPID );

	PACT_TOOL_LoadCellDatas( &wk->clpack_num, ARC_POKETCH_IMG,
			NARC_poketch_pcount_lz_ncer,NARC_poketch_pcount_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	charpos = ArcUtil_ObjCharSet( ARC_POKETCH_IMG, NARC_poketch_pcount_obj_lz_ncgr,
		OBJTYPE_SUB,  0, 0, TRUE, POKETCH_APP_VIEW_HEAPID );

	charpos /= 0x20;
	wk->pokeIconCharPos = charpos;

	monsno[0] = vpara->now_monsno;
	for(i=0; i<3; i++)
	{
		monsno[1+i] = vpara->rank_monsno[i];
	}
	for(i=0; i<4; i++)
	{
		// モンスターナンバー０でもダミーを作っておく（表示はしない）
		wk->arcIdx[i] = PokeIconCgxArcIndexGetByMonsNumber( ((monsno[i])? monsno[i] : 1), FALSE, 0 );
	}
	PoketchViewTool_SetupPokeIconCgx( charpos, wk->arcIdx, NELEMS(wk->arcIdx), TRUE );

	PoketchViewTool_SetupPokeIconPalette( OBJ_PALPOS_POKE );

	for(i=0; i<ACTID_MAX; i++)
	{
		wk->act[i] = NULL;
	}

	for(i=0; i<4; i++)
	{
		wk->act[ACTID_POKE_NOW+i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack_poke );
		PACT_SetCharOffset( wk->act[ACTID_POKE_NOW+i], charpos + i*32 );

		for(j=0; j<3; j++)
		{
			n = ACTID_COUNT_NOW1 + i*3 + j;
			wk->act[n] = PACT_Add( wk->actsys, &actparam[n], &wk->clpack_num );
		}

		if( monsno[i] == 0 )
		{
			PACT_SetVanish( wk->act[ACTID_POKE_NOW+i], TRUE );
			for(j=0; j<3; j++)
			{
				n = ACTID_COUNT_NOW1 + i*3 + j;
				PACT_SetVanish( wk->act[n], TRUE );
			}
		}
		else
		{
			PACT_SetPalOffset( wk->act[ACTID_POKE_NOW+i], OBJ_PALPOS_POKE+PokeIconPalNumGet(monsno[i], 0, FALSE) );
			setanm_num_actors( &(wk->act[ACTID_COUNT_NOW1 + i*3]), (i==0)? vpara->now_count : vpara->rank_count[i-1] );
		}
	}
}



static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	for(i=0; i<ACTID_MAX; i++)
	{
		if( wk->act[i] )
		{
			PACT_Del( wk->actsys, wk->act[i] );
			wk->act[i] = NULL;
		}
	}

	PACT_TOOL_UnloadCellDatas( &wk->clpack_poke );
	PACT_TOOL_UnloadCellDatas( &wk->clpack_num );

}


static void setanm_num_actors( PACT** act, u32 val )
{
	int i, rem, denom;
	BOOL flg = FALSE;

	if( val > 999 ){ val = 999; }

	for(i=0, denom=100; i<3; i++, denom/=10)
	{
		rem = val / denom;
		if( (flg == TRUE) || (rem != 0) || (i==2) )
		{
			PACT_ChangeAnmSeq( *act, rem );
			flg = TRUE;
		}
		else
		{
			PACT_SetVanish( *act, TRUE );
		}
		val -= ( rem * denom );
		act++;
	}
}
