//============================================================================================
/**
 * @file	poketch_a29v.c
 * @bfief	ポケッチ（アプリNo29:ポケモンヒストリー）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "system\msgdata.h"
#include "system\fontproc.h"
#include "poketool\pokeicon.h"

#include "msgdata\msg.naix"
#include "msgdata\msg_poketch_history.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a29.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

//==============================================================
// Work
//==============================================================
struct _POKETCH_A29_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              actor[ POKETCH_POKE_HISTORY_COUNT_MAX ];
	PACT_CLANM_PACK    clpack;

	u32			iconArcIdx[ POKETCH_POKE_HISTORY_COUNT_MAX ];

};



//====================================================
// bg map
//====================================================
#define USE_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );


//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A29_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
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
void Poketch_A29_DeleteViewWork( VIEWWORK* wk )
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
void Poketch_A29_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A29_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A29_WaitViewCommandAll(VIEWWORK* wk)
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
	const VIEWPARAM* vpara;
	GF_BGL_BMPWIN  bmpWin;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	GF_BGL_CharFill( vwk->bgl, USE_BG_FRAME, POKETCH_DEFAULTCOLOR_L1_POS, 1, 0 );
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, 0, 0, 0, 32, 24, USE_PALNO );
	PoketchView_SetBaseColorPalette( USE_PALNO, 0 );

	GF_BGL_BmpWinAdd( vwk->bgl, &bmpWin, USE_BG_FRAME, 
		POKETCH_MONITOR_SCRN_XORG, POKETCH_MONITOR_SCRN_YORG,
		POKETCH_MONITOR_SCRN_WIDTH, 2, USE_PALNO, 1 );

	GF_BGL_BmpWinDataFill( &bmpWin, POKETCH_DEFAULTCOLOR_L1_POS );
	GF_BGL_BmpWinMakeScrn( &bmpWin );
	{
		STRBUF* title = MSGDAT_GetStrDirectAlloc( ARC_MSG, NARC_msg_poketch_history_dat, msg_history_title, POKETCH_APP_VIEW_HEAPID );
		if( title )
		{
			GF_STR_PrintColor( &bmpWin, FONT_SYSTEM, title,
					(POKETCH_MONITOR_DOT_WIDTH - FontProc_GetPrintStrWidth(FONT_SYSTEM, title, 0)) / 2, 0,
					MSG_NO_PUT, GF_PRINTCOLOR_MAKE(POKETCH_DEFAULTCOLOR_L4_POS, POKETCH_DEFAULTCOLOR_L4_POS, POKETCH_DEFAULTCOLOR_L1_POS),
					NULL );

			GF_BGL_BmpWinCgxOn( &bmpWin );

			STRBUF_Delete( title );
		}
	}

	GF_BGL_BmpWinDel( &bmpWin );
	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

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



static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM  actparam[] = 
	{
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*0), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*0) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 12, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*1), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*0) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 11, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*2), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*0) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 10, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*3), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*0) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  9, TRUE },

		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*0), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*1) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  8, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*1), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*1) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  7, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*2), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*1) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  6, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*3), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*1) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  5, TRUE },

		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*0), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*2) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  4, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*1), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*2) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  3, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*2), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*2) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  2, TRUE },
		{ { FX32INT(ICONPOS_XORG+ICONPOS_XDIFF*3), FX32INT(ICONPOS_YORG+ICONPOS_YDIFF*2) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2,  1, TRUE },
	};

	int i;

	PoketchViewTool_SetupPokeIconPalette( 0 );

	PACT_TOOL_LoadCellDatas( &wk->clpack, ARC_POKETCH_IMG,
			NARC_poketch_pokeicon_ncer,NARC_poketch_pokeicon_nanr, POKETCH_APP_VIEW_HEAPID );

	for(i=0; i<vpara->pokeCount; i++)
	{
		wk->iconArcIdx[i] = PokeIconCgxArcIndexGetByMonsNumber( vpara->poke_param[i].monsno, FALSE, vpara->poke_param[i].iconPattern );
		wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack );
		PACT_SetCharOffset( wk->actor[i], i*16 );
		PACT_SetPalOffset( wk->actor[i],
			PokeIconPalNumGet(vpara->poke_param[i].monsno, vpara->poke_param[i].iconPattern, FALSE) );
	}
	for( ; i<POKETCH_POKE_HISTORY_COUNT_MAX; i++)
	{
		wk->actor[i] = NULL;
	}
	PoketchViewTool_SetupPokeIconCgx( 0, wk->iconArcIdx, vpara->pokeCount, FALSE );

}


static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	for(i=0; i<POKETCH_POKE_HISTORY_COUNT_MAX; i++)
	{
		if( wk->actor[i] != NULL)
		{
			PACT_Del( wk->actsys, wk->actor[i] );
			wk->actor[i] = NULL;
		}
	}

	PACT_TOOL_UnloadCellDatas( &wk->clpack );
}
