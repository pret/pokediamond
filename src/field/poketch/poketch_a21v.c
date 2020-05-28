//============================================================================================
/**
 * @file	poketch_a21v.c
 * @bfief	ポケッチ（アプリNo21:キッチンタイマー）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a21.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

//-------------------------
// アクターID
//-------------------------
enum {
	ACTID_ARM_L,
	ACTID_ARM_R,
	ACTID_START,
	ACTID_STOP,
	ACTID_RESET,
	ACTID_UP_MIN10,
	ACTID_UP_MIN1,
	ACTID_UP_SEC10,
	ACTID_UP_SEC1,
	ACTID_DOWN_MIN10,
	ACTID_DOWN_MIN1,
	ACTID_DOWN_SEC10,
	ACTID_DOWN_SEC1,
	ACTID_MIN10,
	ACTID_MIN1,
	ACTID_SEC10,
	ACTID_SEC1,

	ACTID_MAX,

	ACTID_NUM_START = ACTID_MIN10,
	ACTID_NUM_END = ACTID_SEC1,
};
//-------------------------
// アニメID
//-------------------------
enum {
	ANM_ARM_R_UP,
	ANM_ARM_R_DOWN,
	ANM_ARM_L_UP,
	ANM_ARM_L_DOWN,
	ANM_ARROW,
	ANM_START_OFF,
	ANM_START_ON,
	ANM_STOP_OFF,
	ANM_STOP_ON,
	ANM_RESET_OFF,
	ANM_RESET_ON,
};

//-------------------------
// アクター配置
//-------------------------
enum {
	ACTPOS_ARM_L_X = 48,
	ACTPOS_ARM_L_Y = 56,
	ACTPOS_ARM_R_X = 176,
	ACTPOS_ARM_R_Y = 56,

	ACTPOS_NUM_BASE_Y = 112,
	ACTPOS_MIN10_X = 80,
	ACTPOS_MIN1_X = ACTPOS_MIN10_X + 16,
	ACTPOS_SEC10_X = 128,
	ACTPOS_SEC1_X = ACTPOS_SEC10_X + 16,


	ACTPOS_START_X = START_XPOS,
	ACTPOS_START_Y = START_YPOS,
	ACTPOS_STOP_X  = STOP_XPOS,
	ACTPOS_STOP_Y  = STOP_YPOS,
	ACTPOS_RESET_X = RESET_XPOS,
	ACTPOS_RESET_Y = RESET_YPOS,

	ACTPOS_MIN10_UP_X = MIN10_UP_XPOS,
	ACTPOS_MIN10_UP_Y = MIN10_UP_YPOS,
	ACTPOS_MIN10_DOWN_X = MIN10_DOWN_XPOS,
	ACTPOS_MIN10_DOWN_Y = MIN10_DOWN_YPOS,
	ACTPOS_MIN1_UP_X = MIN1_UP_XPOS,
	ACTPOS_MIN1_UP_Y = MIN1_UP_YPOS,
	ACTPOS_MIN1_DOWN_X = MIN1_DOWN_XPOS,
	ACTPOS_MIN1_DOWN_Y = MIN1_DOWN_YPOS,

	ACTPOS_SEC10_UP_X = SEC10_UP_XPOS,
	ACTPOS_SEC10_UP_Y = SEC10_UP_YPOS,
	ACTPOS_SEC10_DOWN_X = SEC10_DOWN_XPOS,
	ACTPOS_SEC10_DOWN_Y = SEC10_DOWN_YPOS,
	ACTPOS_SEC1_UP_X = SEC1_UP_XPOS,
	ACTPOS_SEC1_UP_Y = SEC1_UP_YPOS,
	ACTPOS_SEC1_DOWN_X = SEC1_DOWN_XPOS,
	ACTPOS_SEC1_DOWN_Y = SEC1_DOWN_YPOS,


};



//==============================================================
// Work
//==============================================================
struct _POKETCH_A21_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              actor[ACTID_MAX];
	PACT_CLANM_PACK    clpack;
	PACT_CLANM_PACK    clpack_num;


	BOOL  alarm_stop_flag;
	u32   alarm_timer;
	u32   alarm_anim_state;
};



//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdChangeInput( TCB_PTR tcb, void* wk_ptr );
static void CmdChangeCountDown( TCB_PTR tcb, void* wk_ptr );
static void CmdUpdateButton( TCB_PTR tcb, void* wk_ptr );
static void CmdUpdateNum( TCB_PTR tcb, void* wk_ptr );
static void CmdStartAlarm( TCB_PTR tcb, void* wk_ptr );
static void CmdStopAlarm( TCB_PTR tcb, void* wk_ptr );
static void update_button_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void update_num_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void vanish_arrow_actors( VIEWWORK* wk, BOOL flag );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A21_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		setup_actors(wk, vpara);

		if( wk->bgl != NULL )
		{
			*wk_ptr = wk;
			return TRUE;
		}
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
void Poketch_A21_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors(wk);
		sys_FreeMemoryEz( wk );
	}
}

static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	enum {
		CHAROFS_TOP = 80,	// 数字OBJ分
	};

	static const PACT_ADD_PARAM  actparam[] = {
		{  {FX32INT(ACTPOS_ARM_L_X), FX32INT(ACTPOS_ARM_L_Y)},  ANM_ARM_L_UP,  PACT_FLIP_OFF,   BGPRI2, 1, FALSE, },
		{  {FX32INT(ACTPOS_ARM_R_X), FX32INT(ACTPOS_ARM_R_Y)},  ANM_ARM_R_UP,  PACT_FLIP_OFF, BGPRI2, 1, FALSE, },

		{  {FX32INT(ACTPOS_START_X), FX32INT(ACTPOS_START_Y)},  ANM_START_OFF, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_STOP_X),  FX32INT(ACTPOS_STOP_Y)},   ANM_STOP_OFF,  PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_RESET_X), FX32INT(ACTPOS_RESET_Y)},  ANM_RESET_OFF, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },

		{  {FX32INT(ACTPOS_MIN10_UP_X),   FX32INT(ACTPOS_MIN10_UP_Y)},   ANM_ARROW, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN1_UP_X),    FX32INT(ACTPOS_MIN1_UP_Y)},    ANM_ARROW, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_SEC10_UP_X),   FX32INT(ACTPOS_SEC10_UP_Y)},   ANM_ARROW, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_SEC1_UP_X),    FX32INT(ACTPOS_SEC1_UP_Y)},    ANM_ARROW, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN10_DOWN_X), FX32INT(ACTPOS_MIN10_DOWN_Y)}, ANM_ARROW, PACT_FLIP_V, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN1_DOWN_X),  FX32INT(ACTPOS_MIN1_DOWN_Y)},  ANM_ARROW, PACT_FLIP_V, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_SEC10_DOWN_X), FX32INT(ACTPOS_SEC10_DOWN_Y)}, ANM_ARROW, PACT_FLIP_V, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_SEC1_DOWN_X),  FX32INT(ACTPOS_SEC1_DOWN_Y)},  ANM_ARROW, PACT_FLIP_V, BGPRI2, 0, FALSE, },


		{  {FX32INT(ACTPOS_MIN10_X), FX32INT(ACTPOS_NUM_BASE_Y)},   0,  PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN1_X),  FX32INT(ACTPOS_NUM_BASE_Y)},   0,  PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_SEC10_X), FX32INT(ACTPOS_NUM_BASE_Y)},   0,  PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_SEC1_X),  FX32INT(ACTPOS_NUM_BASE_Y)},   0,  PACT_FLIP_OFF, BGPRI2, 0, FALSE, },

	};

	int i;

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_numobj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_kitchen_obj_lz_ncgr, OBJTYPE_SUB, CHAROFS_TOP*0x20, 0, TRUE, POKETCH_APP_VIEW_HEAPID);


	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_kitchen_lz_ncer, NARC_poketch_kitchen_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	PACT_TOOL_LoadCellDatas(&wk->clpack_num, ARC_POKETCH_IMG,
				NARC_poketch_numobj_ncer, NARC_poketch_numobj_nanr, POKETCH_APP_VIEW_HEAPID );


	for(i=0; i<ACTID_MAX; i++)
	{
		if( i >= ACTID_NUM_START && i <= ACTID_NUM_END )
		{
			wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack_num );
		}
		else
		{
			wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack );
			PACT_SetCharOffset( wk->actor[i], CHAROFS_TOP );
		}
	}

	update_button_actors( wk, vpara );
	update_num_actors( wk, vpara );
	vanish_arrow_actors( wk, !(vpara->arrow_disp_flag) );

	wk->alarm_anim_state = 0;
}


static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	for(i=0; i<ACTID_MAX; i++)
	{
		if( wk->actor[i] )
		{
			PACT_Del( wk->actsys, wk->actor[i] );
		}
	}

	PACT_TOOL_UnloadCellDatas(&wk->clpack);
	PACT_TOOL_UnloadCellDatas(&wk->clpack_num);

}


//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },

	{ CMD_CHANGE_INPUT,		CmdChangeInput, 0 },
	{ CMD_CHANGE_COUNTDOWN,	CmdChangeCountDown, 0 },
	{ CMD_UPDATE_BUTTON,	CmdUpdateButton, 0 },
	{ CMD_UPDATE_NUM,		CmdUpdateNum, 0 },
	{ CMD_START_ALARM,		CmdStartAlarm, 0 },
	{ CMD_STOP_ALARM,		CmdStopAlarm, 0 },

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
void Poketch_A21_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A21_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A21_WaitViewCommandAll(VIEWWORK* wk)
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

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_kitchen_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_kitchen_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);


	switch( vwk->vpara->alarm_state ){
	case ALARM_STATE_ACT:
		Poketch_A21_SetViewCommand( vwk, CMD_START_ALARM );
		break;

	case ALARM_STATE_COUNTDOWN:
		PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_DOWN );
		PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_DOWN );
		break;

	case ALARM_STATE_ACT_PAUSE:
		if( vwk->vpara->alarm_pause_anim )
		{
			PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_UP );
			PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_DOWN );
		}
		else
		{
			PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_DOWN );
			PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_UP );
		}
		break;
	}

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
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		vwk->alarm_stop_flag = TRUE;
		PoketchViewTool_FwdSeq(wk_ptr);
		/* fallthru */
	case 1:
		if( Poketch_A21_WaitViewCommand( vwk, CMD_START_ALARM ) )
		{
			GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
			DeleteCommand( wk_ptr );
		}
	}
}


static void CmdChangeInput( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	vanish_arrow_actors( vwk, FALSE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_UP );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_UP );
	DeleteCommand( wk_ptr );
}
static void CmdChangeCountDown( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	vanish_arrow_actors( vwk, TRUE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_DOWN );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_DOWN );
	DeleteCommand( wk_ptr );
}
static void CmdUpdateButton( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	update_button_actors( vwk, vpara );
	DeleteCommand( wk_ptr );
}

static void CmdUpdateNum( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	update_num_actors( vwk, vpara );
	DeleteCommand( wk_ptr );
}
static void CmdStartAlarm( TCB_PTR tcb, void* wk_ptr )
{
	enum {
		ANM_WAIT = 8,
	};

	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_UP );
		PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_UP );
		vwk->alarm_timer = 0;
		vwk->alarm_stop_flag = FALSE;
		PoketchViewTool_FwdSeq(wk_ptr);
		/* fallthru */
	case 1:
		if( vwk->alarm_stop_flag )
		{
			DeleteCommand(wk_ptr);
			return;
		}

		if( ++(vwk->alarm_timer) >= ANM_WAIT )
		{
			vwk->alarm_anim_state ^= 1;
			if( vwk->alarm_anim_state )
			{
				PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_UP );
				PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_DOWN );
			}
			else
			{
				PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_L], ANM_ARM_L_DOWN );
				PACT_ChangeAnmSeq( vwk->actor[ACTID_ARM_R], ANM_ARM_R_UP );
			}
			PoketchSePlay(POKETCH_SE_KITCHEN_POKO);
			vwk->alarm_timer = 0;
		}
		break;
	}
}
static void CmdStopAlarm( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		vwk->alarm_stop_flag = TRUE;
		PoketchViewTool_FwdSeq(wk_ptr);
		/* fallthru */
	case 1:
		if( Poketch_A21_WaitViewCommand( vwk, CMD_START_ALARM ) )
		{
			DeleteCommand( wk_ptr );
		}
		break;
	}
}







//------------------------------------------------------------------
/**
 * ボタンアクターの状態更新
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void update_button_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	PACT_ChangeAnmSeq( wk->actor[ACTID_START], (vpara->button[0])? ANM_START_ON : ANM_START_OFF );
	PACT_ChangeAnmSeq( wk->actor[ACTID_STOP],  (vpara->button[1])?  ANM_STOP_ON  : ANM_STOP_OFF  );
	PACT_ChangeAnmSeq( wk->actor[ACTID_RESET], (vpara->button[2])? ANM_RESET_ON : ANM_RESET_OFF );
}
//------------------------------------------------------------------
/**
 * 数字アクターの状態更新
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void update_num_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	PACT_ChangeAnmSeq( wk->actor[ACTID_MIN10], vpara->min10);
	PACT_ChangeAnmSeq( wk->actor[ACTID_MIN1],  vpara->min1);
	PACT_ChangeAnmSeq( wk->actor[ACTID_SEC10], vpara->sec10);
	PACT_ChangeAnmSeq( wk->actor[ACTID_SEC1],  vpara->sec1);
}
//------------------------------------------------------------------
/**
 * 矢印アクターの表示オン・オフ
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void vanish_arrow_actors( VIEWWORK* wk, BOOL flag )
{
	PACT_SetVanish( wk->actor[ACTID_UP_MIN10], flag );
	PACT_SetVanish( wk->actor[ACTID_UP_MIN1], flag );
	PACT_SetVanish( wk->actor[ACTID_UP_SEC10], flag );
	PACT_SetVanish( wk->actor[ACTID_UP_SEC1], flag );
	PACT_SetVanish( wk->actor[ACTID_DOWN_MIN10], flag );
	PACT_SetVanish( wk->actor[ACTID_DOWN_MIN1], flag );
	PACT_SetVanish( wk->actor[ACTID_DOWN_SEC10], flag );
	PACT_SetVanish( wk->actor[ACTID_DOWN_SEC1], flag );
}





u32 Poketch_A21_GetAlarmAnimState( VIEWWORK* wk )
{
	return wk->alarm_anim_state;
}
