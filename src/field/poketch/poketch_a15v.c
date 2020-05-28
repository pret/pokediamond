//============================================================================================
/**
 * @file	poketch_a15v.c
 * @bfief	ポケッチ（アプリNo15:そだてやカメラ）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "poketool\monsno.h"
#include "poketool\pokeicon.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a15.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)
#define OBJ_PALNO_POKEICON	(1)

enum {
	ACTID_POKE_L,
	ACTID_POKE_R,
	ACTID_TAMAGO,
	ACTID_LV_L_0,
	ACTID_LV_L_1,
	ACTID_LV_L_2,
	ACTID_LV_R_0,
	ACTID_LV_R_1,
	ACTID_LV_R_2,
	ACTID_SEX_L,
	ACTID_SEX_R,

	ACTID_MAX,
};

enum {
	ANM_N0,
	ANM_N1,
	ANM_N2,
	ANM_N3,
	ANM_N4,
	ANM_N5,
	ANM_N6,
	ANM_N7,
	ANM_N8,
	ANM_N9,
	ANM_OSU,
	ANM_MESU,
	ANM_UNKNOWN,
};

enum {
	ACTPOS_POKE_L_X = 56,
	ACTPOS_POKE_L_Y =128,
	ACTPOS_POKE_R_X = 168,
	ACTPOS_POKE_R_Y = 128,
	ACTPOS_TAMAGO_X = 112,
	ACTPOS_TAMAGO_Y = 136,

	ACTPOS_LV_WIDTH=16,
	ACTPOS_LV_Y = 40,
	ACTPOS_LV_L_0_X = 48,
	ACTPOS_LV_L_1_X = ACTPOS_LV_L_0_X+ACTPOS_LV_WIDTH*1,
	ACTPOS_LV_L_2_X = ACTPOS_LV_L_0_X+ACTPOS_LV_WIDTH*2,
	ACTPOS_SEX_L_X  = ACTPOS_LV_L_0_X+ACTPOS_LV_WIDTH*3,

	ACTPOS_LV_R_0_X = 152,
	ACTPOS_LV_R_1_X = ACTPOS_LV_R_0_X+ACTPOS_LV_WIDTH*1,
	ACTPOS_LV_R_2_X = ACTPOS_LV_R_0_X+ACTPOS_LV_WIDTH*2,
	ACTPOS_SEX_R_X  = ACTPOS_LV_R_0_X+ACTPOS_LV_WIDTH*3,

};


//==============================================================
// Work
//==============================================================
struct _POKETCH_A15_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              actor[ ACTID_MAX ];
	PACT_CLANM_PACK    clpack;
	PACT_CLANM_PACK    clpack_pokeicon;

	u32                poke_charno_top;

	u32                mosaic_lv;
	u32                mosaic_timer;
	BOOL               update_stop_flag;
	BOOL               mosaic_change_req;
	TCB_PTR            mosaicCtrlTask;
};


//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdUpdate(TCB_PTR tcb, void *wk_ptr);
static void set_mosaic_change_req( VIEWWORK* wk );
static void mosaic_ctrl_task( TCB_PTR tcb, void* wk_adrs );
static void setup_pokeicon_cgx( u32 charno_top, const VIEWPARAM* vpara );
static void update_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void update_level_actors( PACT** act, u32 lv );
static void update_sex_actors( PACT* act, u32 sex );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A15_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		wk->mosaic_change_req = FALSE;
		wk->mosaicCtrlTask = VWaitTCB_Add( mosaic_ctrl_task, wk, 0 );

		setup_actors( wk, vpara );

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
void Poketch_A15_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors(wk);
		TCB_Delete( wk->mosaicCtrlTask );
		sys_FreeMemoryEz( wk );
	}
}




//------------------------------------------------------------------
/**
 * アクターセットアップ
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM  actparam[] = {
		{ { FX32INT(ACTPOS_POKE_L_X), FX32INT(ACTPOS_POKE_L_Y) }, POKEICON_ANM_NORMAL_R, PACT_FLIP_OFF,  BGPRI2, 0, TRUE },
		{ { FX32INT(ACTPOS_POKE_R_X), FX32INT(ACTPOS_POKE_R_Y) }, POKEICON_ANM_NORMAL_L, PACT_FLIP_OFF,  BGPRI2, 0, TRUE },
		{ { FX32INT(ACTPOS_TAMAGO_X), FX32INT(ACTPOS_TAMAGO_Y) }, POKEICON_ANM_OFF_L, PACT_FLIP_OFF,  BGPRI2, 0, TRUE },
		{ { FX32INT(ACTPOS_LV_L_0_X), FX32INT(ACTPOS_LV_Y) }, ANM_N0, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
		{ { FX32INT(ACTPOS_LV_L_1_X), FX32INT(ACTPOS_LV_Y) }, ANM_N0, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
		{ { FX32INT(ACTPOS_LV_L_2_X), FX32INT(ACTPOS_LV_Y) }, ANM_N0, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
		{ { FX32INT(ACTPOS_LV_R_0_X), FX32INT(ACTPOS_LV_Y) }, ANM_N0, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
		{ { FX32INT(ACTPOS_LV_R_1_X), FX32INT(ACTPOS_LV_Y) }, ANM_N0, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
		{ { FX32INT(ACTPOS_LV_R_2_X), FX32INT(ACTPOS_LV_Y) }, ANM_N0, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
		{ { FX32INT(ACTPOS_SEX_L_X), FX32INT(ACTPOS_LV_Y) }, ANM_OSU, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
		{ { FX32INT(ACTPOS_SEX_R_X), FX32INT(ACTPOS_LV_Y) }, ANM_OSU, PACT_FLIP_OFF,  BGPRI2, 0, FALSE },
	};

	int i;
	u32 arc_idx[3];
	u32 charno;

	PoketchViewTool_SetupPokeIconPalette( OBJ_PALNO_POKEICON );

	charno = ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_sodate_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	charno /= 20;
	wk->poke_charno_top = charno;

	setup_pokeicon_cgx( charno, vpara );


	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_sodate_lz_ncer, NARC_poketch_sodate_lz_nanr, POKETCH_APP_VIEW_HEAPID );
	PACT_TOOL_LoadCellDatas( &wk->clpack_pokeicon, ARC_POKETCH_IMG,
			NARC_poketch_pokeicon_ncer,NARC_poketch_pokeicon_nanr, POKETCH_APP_VIEW_HEAPID );


	for(i=0; i<ACTID_MAX; i++)
	{
		if( i>=ACTID_POKE_L && i<=ACTID_TAMAGO )
		{
			wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack_pokeicon );
			PACT_SetCharOffset( wk->actor[i], charno+i*0x20 );
		}
		else
		{
			wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack );
		}

		PACT_SetMosaic( wk->actor[i], TRUE );
	}

	update_actors( wk, vpara );
}

//------------------------------------------------------------------
/**
 * アクター全削除
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
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

	PACT_TOOL_UnloadCellDatas( &wk->clpack_pokeicon );
	PACT_TOOL_UnloadCellDatas( &wk->clpack );
}




//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },
	{ CMD_UPDATE, CmdUpdate, 0 },
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
void Poketch_A15_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A15_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A15_WaitViewCommandAll(VIEWWORK* wk)
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

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_sodate_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_sodate_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	G2S_SetBGMosaicSize(0,0);
	G2S_SetOBJMosaicSize(0,0);

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
		vwk->update_stop_flag = TRUE;
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		if( Poketch_A15_WaitViewCommand( vwk, CMD_UPDATE ) )
		{
			G2S_SetBGMosaicSize(0,0);
			G2S_SetOBJMosaicSize(0,0);
			GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
			DeleteCommand( wk_ptr );
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * コマンド：画面更新処理
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdUpdate(TCB_PTR tcb, void *wk_ptr)
{
	enum {
		MOSAIC_LV_MAX = 10,
		MOSAIC_TIMER = 4,
	};

	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		vwk->update_stop_flag = FALSE;
		vwk->mosaic_timer = 0;
		vwk->mosaic_lv = MOSAIC_LV_MAX;
		set_mosaic_change_req( vwk );
		PoketchSePlay(POKETCH_SE_SODATE_UPDATE);
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		setup_pokeicon_cgx( vwk->poke_charno_top, vpara );
		update_actors( vwk, vpara );
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 2:
		if( vwk->update_stop_flag )
		{
			vwk->mosaic_lv = 0;
			set_mosaic_change_req( vwk );
			PoketchViewTool_FwdSeq( wk_ptr );
			break;
		}

		if(++(vwk->mosaic_timer) >= MOSAIC_TIMER )
		{
			vwk->mosaic_timer = 0;
			vwk->mosaic_lv--;
			set_mosaic_change_req( vwk );
			if( vwk->mosaic_lv == 0 )
			{
				PoketchViewTool_FwdSeq( wk_ptr );
			}
		}
		break;

	case 3:
		DeleteCommand( wk_ptr );
		break;
	}
}

static void set_mosaic_change_req( VIEWWORK* wk )
{
	wk->mosaic_change_req = TRUE;
}

static void mosaic_ctrl_task( TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* wk = wk_adrs;
	if( wk->mosaic_change_req )
	{
		G2S_SetBGMosaicSize(wk->mosaic_lv, wk->mosaic_lv);
		G2S_SetOBJMosaicSize(wk->mosaic_lv, wk->mosaic_lv);
		wk->mosaic_change_req = FALSE;
	}
}


//------------------------------------------------------------------
/**
 * ポケモンアイコン用CGX転送
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void setup_pokeicon_cgx( u32 charno_top, const VIEWPARAM* vpara )
{
	u32 tamago_arc_idx;
	u32 arc_idx[3];

	// タマゴの絵が出れば良いので、モンスターナンバーは適当
	tamago_arc_idx = PokeIconCgxArcIndexGetByMonsNumber( MONSNO_HUSIGIDANE, TRUE, 0 );

	arc_idx[0] = (vpara->poke_count > 0)? vpara->poke_img_arc_idx[0] : tamago_arc_idx;
	arc_idx[1] = (vpara->poke_count > 1)? vpara->poke_img_arc_idx[1] : tamago_arc_idx;
	arc_idx[2] = tamago_arc_idx;

	PoketchViewTool_SetupPokeIconCgx( charno_top, arc_idx, NELEMS(arc_idx), TRUE );
}


//------------------------------------------------------------------
/**
 * アクター状態更新
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void update_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	int i;
	BOOL vanish_flg;

	for(i=0; i<vpara->poke_count; i++)
	{
		PACT_SetPalOffset( wk->actor[ACTID_POKE_L+i],
			OBJ_PALNO_POKEICON + PokeIconPalNumGet(vpara->poke_monsno[i], vpara->poke_form[i], FALSE) );
	}
	PACT_SetPalOffset( wk->actor[ACTID_TAMAGO],
		OBJ_PALNO_POKEICON + PokeIconPalNumGet(MONSNO_HUSIGIDANE, 0, TRUE) );

	if( vpara->poke_count > 0 )
	{
		if( PokePersonalParaGet( vpara->poke_monsno[0], ID_PER_reverse ) )
		{
			PACT_ChangeAnmSeq( wk->actor[ACTID_POKE_L], POKEICON_ANM_NORMAL_L );
		}
		else
		{
			PACT_ChangeAnmSeq( wk->actor[ACTID_POKE_L], POKEICON_ANM_NORMAL_R );
		}
	}


	update_level_actors( &(wk->actor[ACTID_LV_L_0]), vpara->poke_level[0] );
	update_level_actors( &(wk->actor[ACTID_LV_R_0]), vpara->poke_level[1] );

	update_sex_actors( wk->actor[ACTID_SEX_L], vpara->poke_sex[0] );
	update_sex_actors( wk->actor[ACTID_SEX_R], vpara->poke_sex[1] );

	vanish_flg = (vpara->poke_count == 0);
	PACT_SetVanish( wk->actor[ACTID_POKE_L], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_LV_L_0], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_LV_L_1], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_LV_L_2], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_SEX_L], vanish_flg );

	vanish_flg = (vpara->poke_count <= 1);
	PACT_SetVanish( wk->actor[ACTID_POKE_R], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_LV_R_0], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_LV_R_1], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_LV_R_2], vanish_flg );
	PACT_SetVanish( wk->actor[ACTID_SEX_R], vanish_flg );

	PACT_SetVanish( wk->actor[ACTID_TAMAGO], (vpara->tamago_flag == FALSE) );
}

static void update_level_actors( PACT** act, u32 lv )
{
	u32 anmno[3];
	int i;

	if( lv > 100 )
	{
		lv = 100;
	}

	CP_SetDiv32_32( lv, 100 );
	anmno[0] = CP_GetDivResult32();

	CP_SetDiv32_32( CP_GetDivRemainder32(), 10 );
	anmno[1] = CP_GetDivResult32();
	anmno[2] = CP_GetDivRemainder32();

	for(i=0; i<3; i++)
	{
		PACT_ChangeAnmSeq( act[i], anmno[i] );
	}

	PACT_SetVanish( act[0], (lv<100) );
	PACT_SetVanish( act[1], (lv<10) );
}
static void update_sex_actors( PACT* act, u32 sex )
{
	switch( sex ){
	case PARA_MALE:
		PACT_ChangeAnmSeq( act, ANM_OSU );
		break;
	case PARA_FEMALE:
		PACT_ChangeAnmSeq( act, ANM_MESU );
		break;
	default:
		PACT_ChangeAnmSeq( act, ANM_UNKNOWN );
		break;
	}

}



