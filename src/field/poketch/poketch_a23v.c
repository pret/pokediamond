//============================================================================================
/**
 * @file	poketch_a23v.c
 * @bfief	ポケッチ（アプリNo23:きのみマップ）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a23.h"

#include "system\msgdata.h"
#include "system\fontproc.h"
#include "msgdata\msg_poketch_kinomi.h"
#include "msgdata\msg.naix"

//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)


enum {
	ACTPRI_PLAYER_CURSOR,
	ACTPRI_SEED,
	ACTPRI_HIDEMAP,
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A23_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_player;
	PACT*              act_seed[ SEED_GRID_MAX ];
	PACT*              act_hidemap[ POKETCH_HIDEMAP_MAX ];
	PACT_CLANM_PACK    clpack;

	TCB_PTR            actorCtrlTask;
	BOOL               seed_vanish_flag;

	int mosaic_lv;
	int mosaic_timer;
	BOOL update_force_stop_flag;
};


//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void write_kinomi_str( VIEWWORK* vwk, u32 charpos );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdSeedUpdate( TCB_PTR tcb, void* wk_ptr );
static void setup_actors( VIEWWORK* wk );
static void update_seed_actors( VIEWWORK* wk );
static void cleanup_actors( VIEWWORK* wk );
static void ActorCtrlTask( TCB_PTR tcb, void* wk_adrs );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A23_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();
		wk->seed_vanish_flag = vpara->seed_vanish_flag;

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
void Poketch_A23_DeleteViewWork( VIEWWORK* wk )
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
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },
	{ CMD_SEED_UPDATE, CmdSeedUpdate, 0 },
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
void Poketch_A23_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A23_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A23_WaitViewCommandAll(VIEWWORK* wk)
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
		GX_BG_EXTPLTT_01, 2, 0, 0, TRUE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;
	NNSG2dPaletteData* pal;
	u32 charpos;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	G2S_SetBGMosaicSize(0,0);
	G2S_SetOBJMosaicSize(0,0);

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );


	charpos = ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_pmap_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	charpos /= 0x20;
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_pmap_kinomi_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	write_kinomi_str(vwk, charpos);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);

	setup_actors( vwk );

	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * 「きのみ」の文字列をBitmapWindowを使って描画する
 *
 * @param   vwk			ワークポインタ
 * @param   charpos		BitmapWindowが使って良い先頭キャラナンバー
 *
 */
//------------------------------------------------------------------
static void write_kinomi_str( VIEWWORK* vwk, u32 charpos )
{
	enum {
		WIN_OX = 18,
		WIN_OY = 20,
		WIN_WIDTH = 8,
		WIN_HEIGHT = 2,
	};

	GF_BGL_BMPWIN   win;
	STRBUF*         str;

	str = MSGDAT_GetStrDirectAlloc( ARC_MSG, NARC_msg_poketch_kinomi_dat, msg_kinomi, HEAPID_POKETCH_APP );
	if( str )
	{
		GF_BGL_BmpWinAdd( vwk->bgl, &win, USE_BG_FRAME, WIN_OX, WIN_OY, WIN_WIDTH, WIN_HEIGHT, 0, charpos );

		GF_BGL_BmpWinDataFill( &win, POKETCH_DEFAULTCOLOR_L1_POS );
		GF_STR_PrintColor( &win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT,
			GF_PRINTCOLOR_MAKE(POKETCH_DEFAULTCOLOR_L4_POS,POKETCH_DEFAULTCOLOR_L4_POS,POKETCH_DEFAULTCOLOR_L1_POS),
			NULL );

		GF_BGL_BmpWinMakeScrn(&win);
		GF_BGL_BmpWinCgxOn(&win);

		GF_BGL_BmpWinDel(&win);

		STRBUF_Delete(str);
	}
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

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		vwk->update_force_stop_flag = TRUE;
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		if( Poketch_A23_WaitViewCommand( vwk, CMD_SEED_UPDATE ) )
		{
			cleanup_actors( vwk );
			G2S_SetBGMosaicSize(0,0);
			G2S_SetOBJMosaicSize(0,0);
			GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
			DeleteCommand( wk_ptr );
		}
		break;
	}
}

static void CmdSeedUpdate( TCB_PTR tcb, void* wk_ptr )
{
	enum {
		MOSAIC_LV_MAX = 6,
		MOSAIC_TIMER = 3,
	};

	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		vwk->mosaic_lv = MOSAIC_LV_MAX;
		vwk->mosaic_timer = 0;
		vwk->update_force_stop_flag = FALSE;
		G2S_SetBGMosaicSize(vwk->mosaic_lv, vwk->mosaic_lv);
		G2S_SetOBJMosaicSize(vwk->mosaic_lv, vwk->mosaic_lv);
		PoketchSePlay(POKETCH_SE_SODATE_UPDATE);
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		update_seed_actors( vwk );
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 2:
		if( vwk->update_force_stop_flag )
		{
			DeleteCommand( wk_ptr );
			break;
		}

		if(++(vwk->mosaic_timer) >= MOSAIC_TIMER )
		{
			vwk->mosaic_timer = 0;
			vwk->mosaic_lv--;
			G2S_SetBGMosaicSize(vwk->mosaic_lv, vwk->mosaic_lv);
			G2S_SetOBJMosaicSize(vwk->mosaic_lv, vwk->mosaic_lv);
			if( vwk->mosaic_lv == 0 )
			{
				DeleteCommand(wk_ptr);
			}
		}
		break;

	}
}





static void setup_actors( VIEWWORK* wk )
{
	const VIEWPARAM* vpara;
	PACT_ADD_PARAM  actparam;
	u32 px, py;
	int i;

	vpara = wk->vpara;

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
	wk->act_player = PACT_Add(wk->actsys, &actparam, &(wk->clpack));
	PACT_SetMosaic( wk->act_player, TRUE );

	actparam.oampri = ACTPRI_SEED;
	actparam.anmseq = POKETCH_MAPACT_ANMSEQ_SEED;
	actparam.pos.x = 0;
	actparam.pos.y = 0;
	for(i=0; i<SEED_GRID_MAX; i++)
	{
		wk->act_seed[i] = PACT_Add(wk->actsys, &actparam, &(wk->clpack));
		PACT_SetMosaic( wk->act_seed[i], TRUE );
	}
	update_seed_actors( wk );


	for(i=0; i<POKETCH_HIDEMAP_MAX; i++)
	{
		PoketchMap_GetHideMapPos( i, &px, &py );
		actparam.pos.x = FX32INT(px);
		actparam.pos.y = FX32INT(py);
		actparam.oampri = ACTPRI_HIDEMAP;
		actparam.anmseq = POKETCH_MAPACT_ANMSEQ_HIDEMAP1 + i;
		wk->act_hidemap[i] = PACT_Add(wk->actsys, &actparam, &(wk->clpack));
		PACT_SetMosaic( wk->act_hidemap[i], TRUE );

		if( vpara->hidemap_flag[i] == FALSE )
		{
			PACT_SetVanish( wk->act_hidemap[i], TRUE );
		}
	}


	wk->actorCtrlTask = TCB_Add(ActorCtrlTask, wk, POKETCH_APP_GRAPHIC_TASKPRI);
}

static void update_seed_actors( VIEWWORK* wk )
{
	u32 px, py;
	int i;

	for(i=0; i<wk->vpara->seed_count; i++)
	{
		PoketchMap_GridToDot( wk->vpara->seed_pos[i].x, wk->vpara->seed_pos[i].y, &px, &py );
		PACT_SetPos( wk->act_seed[i], FX32INT(px), FX32INT(py) );
		PACT_SetVanish( wk->act_seed[i], FALSE );
	}

	for( ; i<SEED_GRID_MAX; i++)
	{
		PACT_SetVanish( wk->act_seed[i], TRUE );
	}

}


static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	if( wk->actorCtrlTask )
	{
		TCB_Delete( wk->actorCtrlTask );
		wk->actorCtrlTask = NULL;
	}

	for(i=0; i<POKETCH_HIDEMAP_MAX; i++)
	{
		if( wk->act_hidemap[i] )
		{
			PACT_Del( wk->actsys, wk->act_hidemap[i] );
			wk->act_hidemap[i] = NULL;
		}
	}

	for(i=0; i<SEED_GRID_MAX; i++)
	{
		if( wk->act_seed[i] )
		{
			PACT_Del( wk->actsys, wk->act_seed[i] );
			wk->act_seed[i] = NULL;
		}
	}

	if( wk->act_player )
	{
		PACT_Del( wk->actsys, wk->act_player );
		wk->act_player = NULL;
	}

	PACT_TOOL_UnloadCellDatas(&wk->clpack);

}


static void ActorCtrlTask( TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* wk = wk_adrs;
	const VIEWPARAM* vpara = wk->vpara;

	if( vpara->player_update_flag )
	{
		u32 x, y;
		PoketchMap_GridToDot( vpara->player_x, vpara->player_y, &x, &y );
		PACT_SetPos( wk->act_player, FX32INT(x), FX32INT(y) );
	}
}
