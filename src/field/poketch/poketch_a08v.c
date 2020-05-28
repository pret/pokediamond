//============================================================================================
/**
 * @file	poketch_a08v.c
 * @bfief	ポケッチ（アプリNo08:ダウジングマシン）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a08.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

enum {
	ANMSEQ_RIPPLE,
	ANMSEQ_ITEM_LV0,
	ANMSEQ_ITEM_LV1,
	ANMSEQ_ITEM_LV2,
};



//==============================================================
// Work
//==============================================================
struct _POKETCH_A08_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_ripple;
	PACT*              act_item[ FIND_POS_MAX ];
	PACT_CLANM_PACK    clpack;

	BOOL               ripple_anm_flag;

	u16                palbuf[16];
};



//====================================================
// bg map
//====================================================
enum {
	DEFAULT_PALNO = 0,
	FADE1_PALNO = 0x0d,
	FADE2_PALNO = 0x0e,
};

//==============================================================
// Prototype
//==============================================================
static BOOL setup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdRippleStart(TCB_PTR tcb, void* wk_adrs );
static void ripple_proc_none(TCB_PTR tcb, void* wk_adrs );
static void ripple_proc_exist(TCB_PTR tcb, void* wk_adrs );
static void ripple_proc_pos(TCB_PTR tcb, void* wk_adrs );
static void setup_item_actors( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void start_item_actors( VIEWWORK* vwk, const VIEWPARAM* vpara );
static BOOL wait_item_actors_anm( VIEWWORK* vwk );
static void vanish_actors( VIEWWORK* vwk );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A08_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		int i;

		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->ripple_anm_flag = FALSE;

		wk->actsys = PoketchGetActSys();

		wk->act_ripple = NULL;
		for(i=0; i<FIND_POS_MAX; i++)
		{
			wk->act_item[i] = NULL;
		}

		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * アクターセットアップ
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで成功
 */
//------------------------------------------------------------------
static BOOL setup_actors( VIEWWORK* wk )
{
	static const PACT_ADD_PARAM act_param_ripple = {
		{  0, 0 },
		ANMSEQ_RIPPLE, 0, BGPRI2, 0, TRUE,
	};
	static const PACT_ADD_PARAM act_param_item = {
		{  0, 0 },
		ANMSEQ_ITEM_LV0, 0, BGPRI2, 1, FALSE,
	};


	if( PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
		NARC_poketch_sonar_ncer, NARC_poketch_sonar_nanr, POKETCH_APP_VIEW_HEAPID )
	){
		int i;

		ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_sonar_obj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

		wk->act_ripple = PACT_Add( wk->actsys, &act_param_ripple, &wk->clpack );
		PACT_SetVanish( wk->act_ripple, TRUE );

		for(i=0; i<FIND_POS_MAX; i++)
		{
			wk->act_item[i] = PACT_Add( wk->actsys, &act_param_item, &wk->clpack );
			PACT_SetVanish( wk->act_item[i], TRUE );
		}

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
void Poketch_A08_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		int i;
		for(i=0; i<FIND_POS_MAX; i++)
		{
			if( wk->act_item[i] )
			{
				PACT_Del( wk->actsys, wk->act_item[i] );
			}
		}
		if( wk->act_ripple )
		{
			PACT_Del( wk->actsys, wk->act_ripple );
		}
		PACT_TOOL_UnloadCellDatas( &(wk->clpack) );
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
	{ CMD_RIPPLE_START, CmdRippleStart, sizeof(u32) },
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
void Poketch_A08_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A08_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A08_WaitViewCommandAll(VIEWWORK* wk)
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
	void* load_p;
	NNSG2dPaletteData* pal;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_sonar_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_sonar_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(DEFAULT_PALNO,0);

	{
		PoketchView_GetColorPalette( vwk->palbuf );

		vwk->palbuf[POKETCH_DEFAULTCOLOR_L4_POS] = vwk->palbuf[POKETCH_DEFAULTCOLOR_L3_POS];
		DC_FlushRange( vwk->palbuf, sizeof(vwk->palbuf) );
		GXS_LoadOBJPltt( vwk->palbuf, FADE1_PALNO*0x20, 0x20 );

		vwk->palbuf[POKETCH_DEFAULTCOLOR_L4_POS] = vwk->palbuf[POKETCH_DEFAULTCOLOR_L2_POS];
		DC_FlushRange( vwk->palbuf, sizeof(vwk->palbuf) );
		GXS_LoadOBJPltt( vwk->palbuf, FADE2_PALNO*0x20, 0x20 );
	}

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);

	setup_actors( vwk );

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



static void CmdRippleStart(TCB_PTR tcb, void* wk_adrs )
{
	static const TCB_FUNC  ripple_proc[] = {
		ripple_proc_none,
		ripple_proc_exist,
		ripple_proc_pos,
	};

	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM*  vpara = PoketchViewTool_GetViewParam( wk_adrs );
	u32* proc_ptn = PoketchViewTool_GetCmdWork( wk_adrs );

	if( PoketchViewTool_GetSeq( wk_adrs ) == 0 )
	{
		vwk->ripple_anm_flag = TRUE;
		*proc_ptn = vpara->find_pattern;
	}

	ripple_proc[ *proc_ptn ]( tcb, wk_adrs );

}
static void ripple_proc_none(TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		PACT_SetPos( vwk->act_ripple, vpara->touch_x << FX32_SHIFT, vpara->touch_y << FX32_SHIFT );
		PACT_SetVanish( vwk->act_ripple, FALSE );
		PACT_ChangeAnmSeq( vwk->act_ripple, ANMSEQ_RIPPLE );
		PoketchViewTool_FwdSeq( wk_adrs );
		break;

	case 1:
		if( vwk->ripple_anm_flag == FALSE )
		{
			vanish_actors( vwk );
			DeleteCommand( wk_adrs );
			break;
		}
		if( PACT_CheckAnmEnd( vwk->act_ripple ) )
		{
			vanish_actors( vwk );
			DeleteCommand( wk_adrs );
		}
		break;
	}
}
static void ripple_proc_exist(TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		PACT_SetPos( vwk->act_ripple, vpara->touch_x << FX32_SHIFT, vpara->touch_y << FX32_SHIFT );
		PACT_ChangeAnmSeq( vwk->act_ripple, ANMSEQ_RIPPLE );
		PACT_SetVanish( vwk->act_ripple, FALSE );
		PoketchViewTool_FwdSeq( wk_adrs );
		break;

	case 1:
		if( vwk->ripple_anm_flag == FALSE )
		{
			vanish_actors( vwk );
			DeleteCommand( wk_adrs );
			break;
		}
		if( PACT_CheckAnmEnd( vwk->act_ripple ) )
		{
			PACT_ChangeAnmSeq( vwk->act_ripple, ANMSEQ_RIPPLE );
		}
		break;
	}

}
static void ripple_proc_pos(TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		setup_item_actors( vwk, vpara );
		PACT_SetPos( vwk->act_ripple, vpara->touch_x << FX32_SHIFT, vpara->touch_y << FX32_SHIFT );
		PACT_ChangeAnmSeq( vwk->act_ripple, ANMSEQ_RIPPLE );
		PACT_SetVanish( vwk->act_ripple, FALSE );
		PoketchViewTool_FwdSeq( wk_adrs );
		break;

	case 1:
		if( vwk->ripple_anm_flag == FALSE )
		{
			vanish_actors( vwk );
			DeleteCommand( wk_adrs );
			return;
		}
		if( PACT_CheckAnmEnd( vwk->act_ripple ) )
		{
			start_item_actors( vwk, vpara );
			PoketchViewTool_FwdSeq( wk_adrs );
		}
		break;

	case 2:
		if( vwk->ripple_anm_flag == FALSE )
		{
			vanish_actors( vwk );
			DeleteCommand( wk_adrs );
			return;
		}
		if( wait_item_actors_anm( vwk ) )
		{
			PACT_ChangeAnmSeq( vwk->act_ripple, ANMSEQ_RIPPLE );
			PoketchViewTool_SetSeq( wk_adrs, 1 );
		}
		break;
	}
}

static void setup_item_actors( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	u32 i;
	for(i=0; i<vpara->find_pos_count; i++)
	{
		PACT_SetPos( vwk->act_item[i], (vpara->find_pos[i].x << FX32_SHIFT), (vpara->find_pos[i].y << FX32_SHIFT) );
	}
}


static void start_item_actors( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	u32 i, anmseq;

	for(i=0; i<vpara->find_pos_count; i++)
	{
		anmseq = ANMSEQ_ITEM_LV0 + vpara->find_pos[i].lv;
		// あり得ないはずだが一応…
		if( anmseq >= ANMSEQ_ITEM_LV2 )
		{
			anmseq = ANMSEQ_ITEM_LV2;
		}
		PACT_SetVanish( vwk->act_item[i], FALSE );
		PACT_ChangeAnmSeq( vwk->act_item[i], anmseq );
	}
}


static BOOL wait_item_actors_anm( VIEWWORK* vwk )
{
	return PACT_CheckAnmEnd( vwk->act_item[0] );
}


static void vanish_actors( VIEWWORK* vwk )
{
	int i;
	PACT_SetVanish( vwk->act_ripple, TRUE );
	for(i=0; i<FIND_POS_MAX; i++)
	{
		PACT_SetVanish( vwk->act_item[i], TRUE );
	}
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void Poketch_A08_StopRippleAnm( VIEWWORK* vwk )
{
	vanish_actors( vwk );
	vwk->ripple_anm_flag = FALSE;
}
