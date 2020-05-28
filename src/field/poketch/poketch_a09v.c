//============================================================================================
/**
 * @file	poketch_a09v.c
 * @bfief	ポケッチ（アプリNo09: カウンター）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a09.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

#define ACT_NUM_MAX		(4)

enum {
	ANMSEQ_BUTTON_FREE = 0,
	ANMSEQ_BUTTON_TOUCH,
};

enum {
	NUMACT_POS_X = (88 << FX32_SHIFT),
	NUMACT_WIDTH = (16 << FX32_SHIFT),
	NUMACT_POS_Y = (64 << FX32_SHIFT),
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A09_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_button;
	PACT*              act_num[ ACT_NUM_MAX ];
	PACT_CLANM_PACK    clpack_button;
	PACT_CLANM_PACK    clpack_num;

};



//====================================================
// bg map
//====================================================
#define TEST_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdButtonUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdCounterUpdate( TCB_PTR tcb, void* wk_adrs );
static void act_counter_update( VIEWWORK* vwk, const VIEWPARAM* vpara );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A09_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
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
void Poketch_A09_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors( wk );
		sys_FreeMemoryEz( wk );
	}
}



static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	enum {
		BUTTON_CHAROFS = 80,	// 数字OBJ分
	};

	static const PACT_ADD_PARAM  actparam_button = {
		{  FX32INT(BUTTON_CENTER_X), FX32INT(BUTTON_CENTER_Y) },
		ANMSEQ_BUTTON_FREE, 0, BGPRI2, 0, FALSE,
	};
	static const PACT_ADD_PARAM  actparam_num = {
		{  FX32INT(0), FX32INT(0) },
		0, 0, BGPRI2, 0, FALSE,
	};

	int i;

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_numobj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_counter_obj_lz_ncgr, OBJTYPE_SUB, BUTTON_CHAROFS*0x20, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack_button, ARC_POKETCH_IMG,
				NARC_poketch_counter_lz_ncer, NARC_poketch_counter_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	PACT_TOOL_LoadCellDatas(&wk->clpack_num, ARC_POKETCH_IMG,
				NARC_poketch_numobj_ncer, NARC_poketch_numobj_nanr, POKETCH_APP_VIEW_HEAPID );


	wk->act_button = PACT_Add( wk->actsys, &actparam_button, &wk->clpack_button );
	PACT_SetCharOffset( wk->act_button, BUTTON_CHAROFS );

	for(i=0; i<ACT_NUM_MAX; i++)
	{
		wk->act_num[i] = PACT_Add( wk->actsys, &actparam_num, &wk->clpack_num );
		PACT_SetPos( wk->act_num[i], NUMACT_POS_X+NUMACT_WIDTH*i, NUMACT_POS_Y );
	}
	act_counter_update( wk, vpara );

}

static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	PACT_Del( wk->actsys, wk->act_button );
	for(i=0; i<ACT_NUM_MAX; i++)
	{
		PACT_Del( wk->actsys, wk->act_num[i]);
	}

	PACT_TOOL_UnloadCellDatas( &(wk->clpack_button) );
	PACT_TOOL_UnloadCellDatas( &(wk->clpack_num) );
}


//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },
	{ CMD_BUTTON_UPDATE, CmdButtonUpdate, 0 },
	{ CMD_COUNTER_UPDATE,CmdCounterUpdate, 0 },

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
void Poketch_A09_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A09_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A09_WaitViewCommandAll(VIEWWORK* wk)
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

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_counter_bg_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_counter_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
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


static void CmdButtonUpdate( TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );

	switch( vwk->vpara->button_state ){
	case BUTTON_STATE_TOUCH:
		PoketchSePlay(POKETCH_SE_COUNTER_BUTTON);
		PACT_ChangeAnmSeq( vwk->act_button, ANMSEQ_BUTTON_TOUCH );
		break;

	case BUTTON_STATE_FREE:
		PACT_ChangeAnmSeq( vwk->act_button, ANMSEQ_BUTTON_FREE );
		break;
	}
	DeleteCommand( wk_adrs );

}

static void CmdCounterUpdate( TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );

	act_counter_update( vwk, vpara );

	DeleteCommand( wk_adrs );
}


static void act_counter_update( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	int i;
	u32 val, rem;

	val = vpara->counter;
	rem = 1000;

	for(i=0; i<ACT_NUM_MAX; i++)
	{
		CP_SetDiv32_32( val, rem );
		val = CP_GetDivResult32();

		PACT_ChangeAnmSeq( vwk->act_num[i], val );
		val = CP_GetDivRemainder32();
		rem /= 10;
	}
}

