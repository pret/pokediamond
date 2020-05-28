//============================================================================================
/**
 * @file	poketch_a20v.c
 * @bfief	ポケッチ（アプリNo20:アラーム時計）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "poketool\monsno.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a20.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)


enum {
	ACTID_BUTTON,
	ACTID_EAR_L,
	ACTID_EAR_R,
	ACTID_EYE_L,
	ACTID_EYE_R,
	ACTID_HOUR_UP,
	ACTID_HOUR_DOWN,
	ACTID_MIN_UP,
	ACTID_MIN_DOWN,

	ACTID_HOUR0,
	ACTID_HOUR1,
	ACTID_MIN0,
	ACTID_MIN1,

	ACTID_MAX,

	ACTID_NUM_START = ACTID_HOUR0,
	ACTID_NUM_END = ACTID_MIN1,
};

enum {
	ANM_EAR_STOP,
	ANM_EAR_ALARM,
	ANM_BUTTON_OFF,
	ANM_BUTTON_ON,
	ANM_EYE_OPEN,
	ANM_EYE_CLOSE,
	ANM_ARROW,
};

enum {
	ACTPOS_BUTTON_X = 192,
	ACTPOS_BUTTON_Y = 104,
	ACTPOS_EAR_L_X = 48,
	ACTPOS_EAR_L_Y = 48,
	ACTPOS_EAR_R_X = 144,
	ACTPOS_EAR_R_Y = 48,
	ACTPOS_EYE_L_X = 56,
	ACTPOS_EYE_L_Y = 80,
	ACTPOS_EYE_R_X = 136,
	ACTPOS_EYE_R_Y = 80,

	ACTPOS_HOUR_UP_X = 72,
	ACTPOS_HOUR_UP_Y = 120,
	ACTPOS_HOUR_DOWN_X = 72,
	ACTPOS_HOUR_DOWN_Y = 164,
	ACTPOS_MIN_UP_X = 120,
	ACTPOS_MIN_UP_Y = 120,
	ACTPOS_MIN_DOWN_X = 120,
	ACTPOS_MIN_DOWN_Y = 164,

	ACTPOS_HOUR0_X = 64,
	ACTPOS_HOUR1_X = 80,
	ACTPOS_MIN0_X = 112,
	ACTPOS_MIN1_X = 128,
	ACTPOS_NUM_Y = 144,

};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A20_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*        actsys;
	PACT*           actor[ ACTID_MAX ];

	PACT_CLANM_PACK    clpack;
	PACT_CLANM_PACK    clpack_num;

	BOOL  alarm_stop_flag;

	u32   alarm_timer;
	u32   alarm_onoff;
};




//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void update_num_actors( VIEWWORK* wk, u32 hour, u32 min );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdChangeOn( TCB_PTR tcb, void* wk_ptr );
static void CmdChangeOff( TCB_PTR tcb, void* wk_ptr );
static void CmdUpdateTime( TCB_PTR tcb, void* wk_ptr );
static void CmdAlarm( TCB_PTR tcb, void* wk_ptr );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A20_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
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
void Poketch_A20_DeleteViewWork( VIEWWORK* wk )
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
		{  {FX32INT(ACTPOS_BUTTON_X), FX32INT(ACTPOS_BUTTON_Y)},  ANM_BUTTON_ON, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_EAR_L_X),  FX32INT(ACTPOS_EAR_L_Y)},   ANM_EAR_STOP, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_EAR_R_X),  FX32INT(ACTPOS_EAR_R_Y)},   ANM_EAR_STOP, PACT_FLIP_H, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_EYE_L_X),  FX32INT(ACTPOS_EYE_L_Y)},   ANM_EYE_OPEN, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_EYE_R_X),  FX32INT(ACTPOS_EYE_R_Y)},   ANM_EYE_OPEN, PACT_FLIP_H, BGPRI2, 0, FALSE, },

		{  {FX32INT(ACTPOS_HOUR_UP_X),FX32INT(ACTPOS_HOUR_UP_Y)}, ANM_ARROW, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_HOUR_DOWN_X),FX32INT(ACTPOS_HOUR_DOWN_Y)}, ANM_ARROW, PACT_FLIP_V, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN_UP_X),FX32INT(ACTPOS_MIN_UP_Y)}, ANM_ARROW, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN_DOWN_X),FX32INT(ACTPOS_MIN_DOWN_Y)}, ANM_ARROW, PACT_FLIP_V, BGPRI2, 0, FALSE, },

		{  {FX32INT(ACTPOS_HOUR0_X), FX32INT(ACTPOS_NUM_Y)},  0, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_HOUR1_X), FX32INT(ACTPOS_NUM_Y)},  0, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN0_X), FX32INT(ACTPOS_NUM_Y)},  0, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_MIN1_X), FX32INT(ACTPOS_NUM_Y)},  0, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },

	};

	int i;

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_numobj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_alarm_obj_lz_ncgr, OBJTYPE_SUB, CHAROFS_TOP*0x20, 0, TRUE, POKETCH_APP_VIEW_HEAPID);


	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_alarm_lz_ncer, NARC_poketch_alarm_lz_nanr, POKETCH_APP_VIEW_HEAPID );

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


	if( vpara->switch_on )
	{
		PACT_ChangeAnmSeq( wk->actor[ACTID_BUTTON], ANM_BUTTON_ON );
		PACT_ChangeAnmSeq( wk->actor[ACTID_EYE_L], ANM_EYE_CLOSE );
		PACT_ChangeAnmSeq( wk->actor[ACTID_EYE_R], ANM_EYE_CLOSE );

		PACT_SetVanish( wk->actor[ACTID_HOUR_UP], TRUE );
		PACT_SetVanish( wk->actor[ACTID_HOUR_DOWN], TRUE );
		PACT_SetVanish( wk->actor[ACTID_MIN_UP], TRUE );
		PACT_SetVanish( wk->actor[ACTID_MIN_DOWN], TRUE );
		update_num_actors( wk, vpara->hour_now, vpara->min_now );
	}
	else
	{
		PACT_ChangeAnmSeq( wk->actor[ACTID_BUTTON], ANM_BUTTON_OFF );
		PACT_ChangeAnmSeq( wk->actor[ACTID_EYE_L], ANM_EYE_CLOSE );
		PACT_ChangeAnmSeq( wk->actor[ACTID_EYE_R], ANM_EYE_OPEN );

		update_num_actors( wk, vpara->hour_set, vpara->min_set );
	}
}


static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	for(i=0; i<ACTID_MAX; i++)
	{
		if( wk->actor[i] )
		{
			PACT_Del(wk->actsys, wk->actor[i]);
		}
	}
	PACT_TOOL_UnloadCellDatas(&wk->clpack);
	PACT_TOOL_UnloadCellDatas(&wk->clpack_num);
}


static void update_num_actors( VIEWWORK* wk, u32 hour, u32 min )
{
	CP_SetDiv32_32( hour, 10 );
	PACT_ChangeAnmSeq( wk->actor[ACTID_HOUR0], CP_GetDivResult32() );
	PACT_ChangeAnmSeq( wk->actor[ACTID_HOUR1], CP_GetDivRemainder32() );

	CP_SetDiv32_32( min, 10 );
	PACT_ChangeAnmSeq( wk->actor[ACTID_MIN0], CP_GetDivResult32() );
	PACT_ChangeAnmSeq( wk->actor[ACTID_MIN1], CP_GetDivRemainder32() );
}





//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },

	{ CMD_CHANGE_ON,   CmdChangeOn, 0 },
	{ CMD_CHANGE_OFF,  CmdChangeOff, 0 },
	{ CMD_UPDATE_TIME, CmdUpdateTime, 0 },
	{ CMD_ALARM,       CmdAlarm, 0 },

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
void Poketch_A20_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A20_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A20_WaitViewCommandAll(VIEWWORK* wk)
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

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_alarm_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_alarm_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
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

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		Poketch_A20_ForceStopAlarm(vwk);
		PoketchViewTool_FwdSeq(wk_ptr);
		break;
	case 1:
		if( Poketch_A20_WaitViewCommand(vwk, CMD_ALARM) )
		{
			GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
			DeleteCommand( wk_ptr );
		}
		break;
	}
}




static void CmdChangeOn( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	PoketchSePlay( POKETCH_SE_ALARM_BUTTON );

	PACT_ChangeAnmSeq( vwk->actor[ACTID_BUTTON], ANM_BUTTON_ON );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EYE_L], ANM_EYE_CLOSE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EYE_R], ANM_EYE_CLOSE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EAR_L], ANM_EAR_STOP );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EAR_R], ANM_EAR_STOP );

	PACT_SetVanish( vwk->actor[ACTID_HOUR_UP], TRUE );
	PACT_SetVanish( vwk->actor[ACTID_HOUR_DOWN], TRUE );
	PACT_SetVanish( vwk->actor[ACTID_MIN_UP], TRUE );
	PACT_SetVanish( vwk->actor[ACTID_MIN_DOWN], TRUE );
	update_num_actors( vwk, vpara->hour_now, vpara->min_now );

	DeleteCommand( wk_ptr );
}
static void CmdChangeOff( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	PoketchSePlay( POKETCH_SE_ALARM_BUTTON );

	PACT_ChangeAnmSeq( vwk->actor[ACTID_BUTTON], ANM_BUTTON_OFF );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EYE_L], ANM_EYE_CLOSE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EYE_R], ANM_EYE_OPEN );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EAR_L], ANM_EAR_STOP );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_EAR_R], ANM_EAR_STOP );

	PACT_SetVanish( vwk->actor[ACTID_HOUR_UP], FALSE );
	PACT_SetVanish( vwk->actor[ACTID_HOUR_DOWN], FALSE );
	PACT_SetVanish( vwk->actor[ACTID_MIN_UP], FALSE );
	PACT_SetVanish( vwk->actor[ACTID_MIN_DOWN], FALSE );
	update_num_actors( vwk, vpara->hour_set, vpara->min_set );

	DeleteCommand( wk_ptr );
}
static void CmdUpdateTime( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	if( vpara->switch_on )
	{
		update_num_actors( vwk, vpara->hour_now, vpara->min_now );
	}
	else
	{
		update_num_actors( vwk, vpara->hour_set, vpara->min_set );
	}

	DeleteCommand( wk_ptr );
}


static void CmdAlarm( TCB_PTR tcb, void* wk_ptr )
{
	enum {
		VOICE_MONSNO = MONSNO_DOGOOMU,
		ONOFF_TIMER = 15,
	};

	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq( wk_ptr ) ){
	case 0:
		vwk->alarm_stop_flag = FALSE;
		PACT_ChangeAnmSeq( vwk->actor[ACTID_EYE_L], ANM_EYE_OPEN );
		PACT_ChangeAnmSeq( vwk->actor[ACTID_EYE_R], ANM_EYE_OPEN );
		PACT_ChangeAnmSeq( vwk->actor[ACTID_EAR_L], ANM_EAR_ALARM );
		PACT_ChangeAnmSeq( vwk->actor[ACTID_EAR_R], ANM_EAR_ALARM );
		PoketchSePlay( POKETCH_SE_ALARM_BUTTON );
		PoketchVoicePlay( VOICE_MONSNO );
		vwk->alarm_timer = 0;
		vwk->alarm_onoff = 0;
		PoketchViewTool_FwdSeq( wk_ptr );
		break;

	case 1:
		if( vwk->alarm_stop_flag )
		{
			PACT_SetVanish( vwk->actor[ACTID_HOUR0], FALSE );
			PACT_SetVanish( vwk->actor[ACTID_HOUR1], FALSE );
			PACT_SetVanish( vwk->actor[ACTID_MIN0], FALSE );
			PACT_SetVanish( vwk->actor[ACTID_MIN1], FALSE );

			DeleteCommand( wk_ptr );
			return;
		}
		if( Snd_PMVoicePlayCheck() == 0 )
		{
			PoketchVoicePlay( VOICE_MONSNO );
		}
		if(++(vwk->alarm_timer) >= ONOFF_TIMER)
		{
			vwk->alarm_timer = 0;
			vwk->alarm_onoff ^= 1;
			PACT_SetVanish( vwk->actor[ACTID_HOUR0], vwk->alarm_onoff );
			PACT_SetVanish( vwk->actor[ACTID_HOUR1], vwk->alarm_onoff );
			PACT_SetVanish( vwk->actor[ACTID_MIN0], vwk->alarm_onoff );
			PACT_SetVanish( vwk->actor[ACTID_MIN1], vwk->alarm_onoff );
		}
		break;
	}

}


//------------------------------------------------------------------
/**
 * アラーム動作の強制停止
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
void Poketch_A20_ForceStopAlarm( VIEWWORK* vwk )
{
	vwk->alarm_stop_flag = TRUE;
}
