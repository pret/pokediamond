//============================================================================================
/**
 * @file	poketch_a22v.c
 * @bfief	ポケッチ（アプリNo22:マーキングマップ）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a22.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)


enum {
	ACTPRI_POINT_MARK = 0,
	ACTPRI_PLAYER_CURSOR,
	ACTPRI_MARK1,
	ACTPRI_MARK2,
	ACTPRI_MARK3,
	ACTPRI_MARK4,
	ACTPRI_MARK5,
	ACTPRI_MARK6,
	ACTPRI_MOVEPOKE,

	ACTPRI_HIDEMAP,
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A22_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_mark[ POKETCH_MAP_MARK_MAX ];
	PACT*              act_hidemap[ POKETCH_HIDEMAP_MAX ];
	PACT*              act_movepoke[ MOVE_POKE_MAX ];
	PACT*              act_cursor;
	PACT_CLANM_PACK    clpack;

	TCB_PTR            actorCtrlTask;

};


//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void ActorCtrlTask(TCB_PTR tcb, void* wk_adrs);




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A22_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		setup_actors( wk, vpara );

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
void Poketch_A22_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors( wk );
		sys_FreeMemoryEz( wk );
	}
}

static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	PACT_ADD_PARAM  actparam;

	int i, flg;
	u32 px, py;

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_pmap_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_pmap_lz_ncer, NARC_poketch_pmap_lz_nanr, POKETCH_APP_VIEW_HEAPID );


	actparam.flip = PACT_FLIP_OFF;
	actparam.bgpri = BGPRI2;
	actparam.affine_flag = FALSE;

	PoketchMap_GridToDot( vpara->player_x, vpara->player_y, &px, &py );
	actparam.pos.x = FX32INT(px);
	actparam.pos.y = FX32INT(py);
	actparam.oampri = ACTPRI_PLAYER_CURSOR;
	actparam.anmseq = POKETCH_MAPACT_ANMSEQ_PLAYERCURSOR;
	wk->act_cursor = PACT_Add(wk->actsys, &actparam, &(wk->clpack));


	actparam.affine_flag = TRUE;
	for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
	{
		actparam.pos.x = FX32INT(vpara->markpos[i].x);
		actparam.pos.y = FX32INT(vpara->markpos[i].y);
		actparam.oampri = ACTPRI_MARK1 + vpara->markpos[i].pri;
		actparam.anmseq = POKETCH_MAPACT_ANMSEQ_MARK1+i;

		wk->act_mark[i] = PACT_Add(wk->actsys, &actparam, &(wk->clpack));
	}

	for(i=0; i<POKETCH_HIDEMAP_MAX; i++)
	{
		PoketchMap_GetHideMapPos( i, &px, &py );
		actparam.pos.x = FX32INT(px);
		actparam.pos.y = FX32INT(py);
		actparam.oampri = ACTPRI_HIDEMAP;
		actparam.anmseq = POKETCH_MAPACT_ANMSEQ_HIDEMAP1 + i;
		wk->act_hidemap[i] = PACT_Add(wk->actsys, &actparam, &(wk->clpack));

		if( vpara->hidemap_flag[i] == FALSE )
		{
			PACT_SetVanish( wk->act_hidemap[i], TRUE );
		}
	}

	for(i=0; i<MOVE_POKE_MAX; i++)
	{
		flg = PoketchMap_GetMovePokePos( vpara->move_poke[i].zone_id, &px, &py );

		actparam.pos.x = FX32INT(px);
		actparam.pos.y = FX32INT(py);
		actparam.oampri = ACTPRI_MOVEPOKE;
		actparam.anmseq = POKETCH_MAPACT_ANMSEQ_MOVEPOKE;
		wk->act_movepoke[i] = PACT_Add(wk->actsys, &actparam, &(wk->clpack));

		if(	(vpara->move_poke[i].flag == FALSE)
		||	(flg == FALSE)
		){
			PACT_SetVanish( wk->act_movepoke[i], TRUE );
		}
	}

	wk->actorCtrlTask = TCB_Add(ActorCtrlTask, wk, POKETCH_APP_GRAPHIC_TASKPRI);
}

static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	TCB_Delete(wk->actorCtrlTask);

	for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
	{
		if( wk->act_mark[i] )
		{
			PACT_Del(wk->actsys, wk->act_mark[i]);
			wk->act_mark[i] = NULL;
		}
	}

	for(i=0; i<POKETCH_HIDEMAP_MAX; i++)
	{
		if( wk->act_hidemap[i] )
		{
			PACT_Del(wk->actsys, wk->act_hidemap[i]);
			wk->act_hidemap[i] = NULL;
		}
	}

	for(i=0; i<MOVE_POKE_MAX; i++)
	{
		if( wk->act_movepoke[i] )
		{
			PACT_Del( wk->actsys, wk->act_movepoke[i] );
			wk->act_movepoke[i] = NULL;
		}
	}

	PACT_Del(wk->actsys, wk->act_cursor);

	PACT_TOOL_UnloadCellDatas(&wk->clpack);
}



//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },
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
void Poketch_A22_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A22_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A22_WaitViewCommandAll(VIEWWORK* wk)
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
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;
	NNSG2dPaletteData* pal;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_pmap_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_pmap_mark_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

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

	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}






static void ActorCtrlTask(TCB_PTR tcb, void* wk_adrs)
{
	VIEWWORK* wk = wk_adrs;
	const VIEWPARAM* vpara = wk->vpara;
	int id;

	if( vpara->updateFlag )
	{
		int id = vpara->dragMarkID;

		if( vpara->markpos[id].point_flag )
		{
			PACT_SetOamPri( wk->actsys, wk->act_mark[id], ACTPRI_POINT_MARK );
			PACT_ChangeAnmSeq( wk->act_mark[id], POKETCH_MAPACT_ANMSEQ_MARK1_EXPAND + id );
		}
		else
		{
			PACT_SetOamPri( wk->actsys, wk->act_mark[id], ACTPRI_MARK1 + vpara->markpos[id].pri );
			PACT_ChangeAnmSeq( wk->act_mark[id], POKETCH_MAPACT_ANMSEQ_MARK1 + id );
		}
		PACT_SetPos( wk->act_mark[id], FX32INT(vpara->markpos[id].x), FX32INT(vpara->markpos[id].y) );
	}

	if( vpara->player_updateFlag )
	{
		u32 x, y, i;
		PoketchMap_GridToDot( vpara->player_x, vpara->player_y, &x, &y );
		PACT_SetPos( wk->act_cursor, FX32INT(x), FX32INT(y) );

		for(i=0; i<MOVE_POKE_MAX; i++)
		{
			if( vpara->move_poke[i].flag )
			{
				if( PoketchMap_GetMovePokePos( vpara->move_poke[i].zone_id, &x, &y ) )
				{
					PACT_SetPos( wk->act_movepoke[i], FX32INT(x), FX32INT(y) );
					PACT_SetVanish( wk->act_movepoke[i], FALSE );
				}
				else
				{
					PACT_SetVanish( wk->act_movepoke[i], TRUE );
				}
			}
			else
			{
				PACT_SetVanish( wk->act_movepoke[i], TRUE );
			}
		}
	}
}
