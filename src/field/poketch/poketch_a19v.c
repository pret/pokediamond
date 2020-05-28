//============================================================================================
/**
 * @file	poketch_a19v.c
 * @bfief	ポケッチ（アプリNo19:ラブテスター）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "poketool\pokeicon.h"

#include "poketch_a19.h"
#include "poketch_view.h"
#include "poketch_prv.h"

//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)
#define OBJ_PALNO_POKEICON	(1)

enum {
	ACTID_BUTTON,
	ACTID_HEART,
	ACTID_LOVECUSS_L,
	ACTID_LOVECUSS_R,
	ACTID_POKEMON_L,
	ACTID_POKEMON_R,

	ACTID_MAX,
};

enum {
	ANMSEQ_HEART_DEFAULT,
	ANMSEQ_HEART_LV1,
	ANMSEQ_HEART_LV2,
	ANMSEQ_HEART_LV3,
	ANMSEQ_HEART_FEVER,
	ANMSEQ_LOVECUSS_L,
	ANMSEQ_LOVECUSS_R,
	ANMSEQ_LOVECUSS_SINMOVE_L,
	ANMSEQ_LOVECUSS_SINMOVE_R,
	ANMSEQ_BUTTON_FREE,
	ANMSEQ_BUTTON_PUSH,
};

enum {
	ACTPOS_LOVECUSS_L_X = 48,
	ACTPOS_LOVECUSS_R_X = 176,
	ACTPOS_LOVECUSS_Y = 88,

	ACTPOS_HEART_X = POKETCH_MONITOR_CENTER_X,
	ACTPOS_HEART_Y = 32,

	ACTPOS_POKE_L_X = 48,
	ACTPOS_POKE_R_X = 176,
	ACTPOS_POKE_Y = 140,

};


//==============================================================
// Work
//==============================================================
struct _POKETCH_A19_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*     actsys;
	PACT*        actor[ ACTID_MAX ];

	PACT_CLANM_PACK    clpack;
	PACT_CLANM_PACK    clpack_pokeicon;

	u32          poke_charno_top;
	BOOL         force_stop_flag;


	const int* anm_tbl;
	u32 anm_seq;
	u32 anm_tblidx;
	fx32 anm_move;
	fx32 anm_move_val;
	fx32 anm_move_end;
	u32 anm_timer;

};



//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdButtonPush( TCB_PTR tcb, void* wk_ptr );
static void CmdButtonFree( TCB_PTR tcb, void* wk_ptr );
static void CmdChangePokeL( TCB_PTR tcb, void* wk_ptr );
static void CmdChangePokeR( TCB_PTR tcb, void* wk_ptr );
static void update_poke_actor( VIEWWORK* wk, u32 actID, u32 pos, u16 monsno, u16 poke_form );
static void reset_actors_pos( VIEWWORK* wk );
static void CmdAnmPlay( TCB_PTR tcb, void* wk_ptr );
static void start_anm( VIEWWORK* vwk, const VIEWPARAM* vpara );
static BOOL proc_anm( VIEWWORK* vwk, const VIEWPARAM* vpara );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A19_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
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
void Poketch_A19_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors( wk );
		sys_FreeMemoryEz( wk );
	}
}


//------------------------------------------------------------------
/**
 * アクターセットアップ
 *
 * @param   wk		
 */
//------------------------------------------------------------------
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM  actparam[] = {
		{
			{  FX32INT(LOVE_BUTTON_X), FX32INT(LOVE_BUTTON_Y) },
			ANMSEQ_BUTTON_FREE, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(ACTPOS_HEART_X), FX32INT(ACTPOS_HEART_Y) },
			ANMSEQ_HEART_DEFAULT, 0, BGPRI2, 1, FALSE,
		},{
			{  FX32INT(ACTPOS_LOVECUSS_L_X), FX32INT(ACTPOS_LOVECUSS_Y) },
			ANMSEQ_LOVECUSS_L, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(ACTPOS_LOVECUSS_R_X), FX32INT(ACTPOS_LOVECUSS_Y) },
			ANMSEQ_LOVECUSS_R, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(ACTPOS_POKE_L_X), FX32INT(ACTPOS_POKE_Y) },
			POKEICON_ANM_OFF_R, 0, BGPRI2, 0, TRUE,
		},{
			{  FX32INT(ACTPOS_POKE_R_X), FX32INT(ACTPOS_POKE_Y) },
			POKEICON_ANM_OFF_L, 0, BGPRI2, 0, TRUE,
		}
	};


	int i;
	u32 charno;

	PoketchViewTool_SetupPokeIconPalette( OBJ_PALNO_POKEICON );

	charno = ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_love_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	charno /= 20;
	wk->poke_charno_top = charno;

	PoketchViewTool_SetupPokeIconCgx( charno, vpara->pokeImgArcIndex, vpara->poke_count, FALSE );

	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_love_lz_ncer, NARC_poketch_love_lz_nanr, POKETCH_APP_VIEW_HEAPID );
	PACT_TOOL_LoadCellDatas( &wk->clpack_pokeicon, ARC_POKETCH_IMG,
			NARC_poketch_pokeicon_ncer,NARC_poketch_pokeicon_nanr, POKETCH_APP_VIEW_HEAPID );


	for(i=0; i<ACTID_POKEMON_L; i++)
	{
		wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack );
	}
	for(   ; i<ACTID_MAX; i++)
	{
		wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack_pokeicon );
	}


	update_poke_actor( wk, ACTID_POKEMON_L, vpara->poke_id_L,
			vpara->pokeMonsNo[vpara->poke_id_L], vpara->pokeForm[vpara->poke_id_L] );
	update_poke_actor( wk, ACTID_POKEMON_R, vpara->poke_id_R,
			vpara->pokeMonsNo[vpara->poke_id_R], vpara->pokeForm[vpara->poke_id_R] );


	if( vpara->poke_count <= 1 )
	{
		PACT_SetVanish( wk->actor[ACTID_POKEMON_R], TRUE );
		PACT_SetVanish( wk->actor[ACTID_LOVECUSS_R], TRUE );
		PACT_ChangeAnmSeq( wk->actor[ACTID_BUTTON], ANMSEQ_BUTTON_PUSH );
	}

}


static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	PACT_TOOL_UnloadCellDatas(&wk->clpack_pokeicon);
	PACT_TOOL_UnloadCellDatas(&wk->clpack);

	for(i=0; i<ACTID_MAX; i++)
	{
		if( wk->actor[i] )
		{
			PACT_Del( wk->actsys, wk->actor[i] );
		}
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

	{ CMD_BUTTON_PUSH,  CmdButtonPush, 0 },
	{ CMD_BUTTON_FREE,  CmdButtonFree, 0 },
	{ CMD_CHANGE_POKE_L,CmdChangePokeL, 0 },
	{ CMD_CHANGE_POKE_R,CmdChangePokeR, 0 },

	{ CMD_ANM_PLAY, CmdAnmPlay, 0 },

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
void Poketch_A19_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A19_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A19_WaitViewCommandAll(VIEWWORK* wk)
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
	void* load_p;
	NNSG2dPaletteData* pal;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_love_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_love_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
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
		vwk->force_stop_flag = TRUE;
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		if( Poketch_A19_WaitViewCommand(vwk, CMD_ANM_PLAY) )
		{
			GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
			DeleteCommand( wk_ptr );
		}
		break;
	}
}





//------------------------------------------------------------------
/**
 * コマンド：ボタン押し状態に
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdButtonPush( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;
	const VIEWPARAM* vpara;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	PoketchSePlay( POKETCH_SE_LOVE_BUTTON );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_BUTTON], ANMSEQ_BUTTON_PUSH );

	DeleteCommand( wk_ptr );
}
//------------------------------------------------------------------
/**
 * コマンド：ボタン離し状態に
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdButtonFree( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;
	const VIEWPARAM* vpara;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	PACT_ChangeAnmSeq( vwk->actor[ACTID_BUTTON], ANMSEQ_BUTTON_FREE );

	DeleteCommand( wk_ptr );

}
//------------------------------------------------------------------
/**
 * コマンド：左側のポケモン切り替え
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdChangePokeL( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );
	int id;

	id = vpara->poke_id_L;
	PoketchSePlay( POKETCH_SE_LOVE_CHANGE_POKE );
	update_poke_actor( vwk, ACTID_POKEMON_L, id, vpara->pokeMonsNo[id], vpara->pokeForm[id] );
	reset_actors_pos( vwk );

	DeleteCommand( wk_ptr );

}
//------------------------------------------------------------------
/**
 * コマンド：右側のポケモン切り替え
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdChangePokeR( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );
	int id = vpara->poke_id_R;

	PoketchSePlay( POKETCH_SE_LOVE_CHANGE_POKE );
	update_poke_actor( vwk, ACTID_POKEMON_R, id, vpara->pokeMonsNo[id], vpara->pokeForm[id] );
	reset_actors_pos( vwk );

	DeleteCommand( wk_ptr );

}

//------------------------------------------------------------------
/**
 * ポケモンアクターのキャラ＆パレットオフセットを変えて表示変更
 *
 * @param   wk		
 * @param   act		
 * @param   pos		
 * @param   monsno		
 * @param   poke_form		
 *
 */
//------------------------------------------------------------------
static void update_poke_actor( VIEWWORK* wk, u32 actID, u32 pos, u16 monsno, u16 poke_form )
{
	PACT* act = wk->actor[actID];
	u32 anim;

	if( actID == ACTID_POKEMON_R )
	{
		anim = POKEICON_ANM_OFF_L;
	}
	else
	{
		if( PokePersonalParaGet( monsno, ID_PER_reverse ) )
		{
			anim = POKEICON_ANM_OFF_L;
		}
		else
		{
			anim = POKEICON_ANM_OFF_R;
		}
	}

	PACT_ChangeAnmSeq( act, anim );
	PACT_SetCharOffset( act, wk->poke_charno_top + pos*16 );
	PACT_SetPalOffset( act, OBJ_PALNO_POKEICON +  PokeIconPalNumGet(monsno, poke_form, FALSE) );
}

static void reset_actors_pos( VIEWWORK* wk )
{
	PACT_SetPos( wk->actor[ACTID_LOVECUSS_L], FX32INT(ACTPOS_LOVECUSS_L_X), FX32INT(ACTPOS_LOVECUSS_Y) );
	PACT_SetPos( wk->actor[ACTID_LOVECUSS_R], FX32INT(ACTPOS_LOVECUSS_R_X), FX32INT(ACTPOS_LOVECUSS_Y) );
	PACT_ChangeAnmSeq( wk->actor[ACTID_LOVECUSS_L], ANMSEQ_LOVECUSS_L );
	PACT_ChangeAnmSeq( wk->actor[ACTID_LOVECUSS_R], ANMSEQ_LOVECUSS_R );

	PACT_ChangeAnmSeq( wk->actor[ACTID_HEART], ANMSEQ_HEART_DEFAULT );
}

//------------------------------------------------------------------
/**
 * コマンド：判定アニメスタート
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdAnmPlay( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );
	u32 seq = PoketchViewTool_GetSeq(wk_ptr);

	if( seq != 0 && vwk->force_stop_flag )
	{
		DeleteCommand( wk_ptr );
		return;
	}

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		vwk->force_stop_flag = FALSE;
		reset_actors_pos( vwk );
		start_anm( vwk, vpara );
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		if( proc_anm(vwk, vpara) )
		{
			DeleteCommand( wk_ptr );
		}
		break;
	}
}

//----------------------------------------------
// ラブカスさん簡易アニメコマンド
//----------------------------------------------

enum {
	ACMD_END = -1,			// 終了
	ACMD_MOVE = -2,			// 移動（フレーム数, 移動量）
	ACMD_R_MOVE = -3,		// 逆移動（フレーム数, 移動量）
	ACMD_WAIT = -4,			// ウェイト（フレーム数）
	ACMD_SE = -5,			// ＳＥ鳴らす（ＳＥナンバー）
	ACMD_FLIP = -6,			// 向き変更
	ACMD_ANM = -7,			// アクターのアニメ変更（アクターＩＤ，アニメナンバー）
	
};

static const int  anm_lv0[] = {
	ACMD_MOVE, 16, 16, ACMD_WAIT, 16, ACMD_FLIP, ACMD_SE, POKETCH_SE_LOVE_LV_0, ACMD_R_MOVE, 16, 16, ACMD_END,
};
static const int  anm_lv1[] = {
	ACMD_MOVE, 16, 16, ACMD_SE, POKETCH_SE_LOVE_MOVE_POKE_1, ACMD_END,
};
static const int  anm_lv2[] = {
	ACMD_MOVE, 16, 16, ACMD_SE, POKETCH_SE_LOVE_MOVE_POKE_1, 
	ACMD_MOVE, 16, 16, ACMD_SE, POKETCH_SE_LOVE_MOVE_POKE_2, 
	ACMD_END,
};
static const int  anm_lv3[] = {
	ACMD_MOVE, 16, 16, ACMD_SE, POKETCH_SE_LOVE_MOVE_POKE_1, 
	ACMD_MOVE, 16, 16, ACMD_SE, POKETCH_SE_LOVE_MOVE_POKE_2, 
	ACMD_MOVE, 16, 16, ACMD_SE, POKETCH_SE_LOVE_MOVE_POKE_3, 
	ACMD_WAIT, 16,
	ACMD_SE, POKETCH_SE_LOVE_LV_MAX,
	ACMD_ANM, ACTID_LOVECUSS_L, ANMSEQ_LOVECUSS_SINMOVE_L,
	ACMD_ANM, ACTID_LOVECUSS_R, ANMSEQ_LOVECUSS_SINMOVE_R,
	ACMD_ANM, ACTID_HEART, ANMSEQ_HEART_FEVER,
	ACMD_WAIT, 16,
	ACMD_END,
};


static void start_anm( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	vwk->anm_seq = 0;
	vwk->anm_tblidx = 0;
	vwk->anm_move = 0;
	vwk->anm_timer = 0;

	switch( vpara->affinity_lv ){
	case LOVE_AFFINITY_LV_0:
		vwk->anm_tbl = anm_lv0;
		break;
	case LOVE_AFFINITY_LV_1:
		vwk->anm_tbl = anm_lv1;
		PACT_ChangeAnmSeq( vwk->actor[ACTID_HEART], ANMSEQ_HEART_LV1 );
		break;
	case LOVE_AFFINITY_LV_2:
		vwk->anm_tbl = anm_lv2;
		PACT_ChangeAnmSeq( vwk->actor[ACTID_HEART], ANMSEQ_HEART_LV2 );
		break;
	case LOVE_AFFINITY_LV_3:
		vwk->anm_tbl = anm_lv3;
		PACT_ChangeAnmSeq( vwk->actor[ACTID_HEART], ANMSEQ_HEART_LV3 );
		break;
	}

	proc_anm( vwk, vpara );
}


static BOOL proc_anm( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	enum {
		SEQ_TBL,
		SEQ_MOVE,
		SEQ_WAIT,
	};

loop_top:

	switch( vwk->anm_seq ){
	case SEQ_TBL:
		while(vwk->anm_seq == SEQ_TBL)
		{
			switch( vwk->anm_tbl[vwk->anm_tblidx++] ){
			case ACMD_END:
				return TRUE;

			case ACMD_MOVE:
				vwk->anm_timer = vwk->anm_tbl[(vwk->anm_tblidx)++];
				vwk->anm_move_val = vwk->anm_tbl[(vwk->anm_tblidx)++];
				vwk->anm_move_val *= FX32_ONE;
				vwk->anm_move_end = vwk->anm_move + vwk->anm_move_val;
				vwk->anm_move_val /= vwk->anm_timer;
				vwk->anm_seq = SEQ_MOVE;
				break;

			case ACMD_R_MOVE:
				vwk->anm_timer = vwk->anm_tbl[(vwk->anm_tblidx)++];
				vwk->anm_move_val = vwk->anm_tbl[(vwk->anm_tblidx)++];
				vwk->anm_move_val *= FX32_ONE;
				vwk->anm_move_val *= -1;
				vwk->anm_move_end = vwk->anm_move + vwk->anm_move_val;
				vwk->anm_move_val /= vwk->anm_timer;
				vwk->anm_seq = SEQ_MOVE;
				break;

			case ACMD_WAIT:
				vwk->anm_timer = vwk->anm_tbl[(vwk->anm_tblidx)++];
				vwk->anm_seq = SEQ_WAIT;
				break;

			case ACMD_SE:
				PoketchSePlay( vwk->anm_tbl[(vwk->anm_tblidx)++] );
				break;

			case ACMD_FLIP:
				PACT_ChangeAnmSeq( vwk->actor[ACTID_LOVECUSS_L], ANMSEQ_LOVECUSS_R );
				PACT_ChangeAnmSeq( vwk->actor[ACTID_LOVECUSS_R], ANMSEQ_LOVECUSS_L );
				break;

			case ACMD_ANM:
				{
					u32 actid = vwk->anm_tbl[(vwk->anm_tblidx)++];
					u32 anmseq = vwk->anm_tbl[(vwk->anm_tblidx)++];
					PACT_ChangeAnmSeq( vwk->actor[actid], anmseq );
				}
				break;
			}
		}
		break;

	case SEQ_MOVE:
		if( vwk->anm_timer )
		{
			vwk->anm_timer--;
			if(vwk->anm_timer)
			{
				vwk->anm_move += vwk->anm_move_val;
			}
			else
			{
				vwk->anm_move = vwk->anm_move_end;
			}
			PACT_SetPos( vwk->actor[ACTID_LOVECUSS_L], FX32INT(ACTPOS_LOVECUSS_L_X)+vwk->anm_move, FX32INT(ACTPOS_LOVECUSS_Y) );
			PACT_SetPos( vwk->actor[ACTID_LOVECUSS_R], FX32INT(ACTPOS_LOVECUSS_R_X)-vwk->anm_move, FX32INT(ACTPOS_LOVECUSS_Y) );
		}
		if( vwk->anm_timer == 0 )
		{
			vwk->anm_seq = SEQ_TBL;
			goto loop_top;
		}
		break;

	case SEQ_WAIT:
		if( vwk->anm_timer )
		{
			vwk->anm_timer--;
		}
		else
		{
			vwk->anm_seq = SEQ_TBL;
			goto loop_top;
		}
		break;
	}

	return FALSE;
}

