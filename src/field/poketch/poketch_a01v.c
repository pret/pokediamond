//============================================================================================
/**
 * @file	poketch_a01v.c
 * @bfief	ポケッチ（アプリNo01 ストップウォッチ）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "system\snd_tool.h"

#include "field\poketch.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a01.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

#define OAM_START_NUM	(0)
#define USE_OAM_MAX		(10)
#define OAM_USE_NUM		(64)

#define OBJ_NUM_CHAROFS		(0)
#define OBJ_NUM_CHARSIZE	(2*4)

//==============================================================
// Button Type
//==============================================================
enum {
	BTN_BGIMG_FREE,
	BTN_BGIMG_PUSH,
	BTN_BGIMG_EFF1,
	BTN_BGIMG_EFF2,
	BTN_BGIMG_EFF3,
	BTN_BGIMG_BLACKPUSH,
	BTN_BGIMG_BLACKFREE,

	BTN_BGIMG_NULL,
};

//==============================================================
// Cell ID
//==============================================================

enum {
	ACT_HOUR0 = 0,
	ACT_HOUR1,
	ACT_MIN0,
	ACT_MIN1,
	ACT_SEC0,
	ACT_SEC1,
	ACT_MSEC0,
	ACT_MSEC1,
	ACT_EYE,
	ACT_USE_MAX,

	ACT_NUM_START = ACT_HOUR0,
	ACT_NUM_END = ACT_MSEC1,
};


enum {
	ANMSEQ_NUM0,
	ANMSEQ_NUM1,
	ANMSEQ_NUM2,
	ANMSEQ_NUM3,
	ANMSEQ_NUM4,
	ANMSEQ_NUM5,
	ANMSEQ_NUM6,
	ANMSEQ_NUM7,
	ANMSEQ_NUM8,
	ANMSEQ_NUM9,
	ANMSEQ_EYE_FREE,
	ANMSEQ_EYE_PUSH,
	ANMSEQ_EYE_COUNT,
	ANMSEQ_EYE_RESET1,
	ANMSEQ_EYE_RESET2,
	ANMSEQ_EYE_BOMB,
	ANMSEQ_EYE_BURN,
};

enum {
	OAMPRI_NUM = 0,
	OAMPRI_EFF,
	OAMPRI_EYE,
};

//====================================================
// Obj Param
//====================================================
#define  OBJ_NUMBER_YPOS	(40)
#define  OBJ_NUMBER_WIDTH	(16)
#define  OBJ_HOUR_XPOS		(32)
#define  OBJ_MIN_XPOS		(80)
#define  OBJ_SEC_XPOS		(128)
#define  OBJ_MSEC_XPOS		(176)

#define  OBJ_EYE_YPOS		(96)
#define  OBJ_EYE_XPOS		(112)

//====================================================
// bg param
//====================================================
#define BG_PALNO	(0)

#define BG_CHAR_WIDTH	(37)
#define BTN_CHAR_TOP	(2)
#define BTN_CHAR_WIDTH	(5)
#define BTN_CHAR_HEIGHT	(11)

#define BTN_SCRN_XORG	(9)
#define BTN_SCRN_YORG	(9)

//==============================================================
// コマンドワーク
//==============================================================
typedef struct {
	u16 time;
	u8  btn_prog;
	u8  btn_state;
}BTN_EFFECT_WORK;

//==============================================================
// メインワーク
//==============================================================
struct _POKETCH_A01_VIEWWORK {
	const  POKETCH_A01_VIEW_PARAM*  vpara;
	GF_BGL_INI*                     bgl;
	POKETCH_CMD_STORE		cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	NNSG2dOamManagerInstance*   oamm;

	PACT_CLANM_PACK    stopwatch_clpack;
	PACT_CLANM_PACK    numobj_clpack;
	PACTSYS*           actsys;

	PACT*       act[ ACT_USE_MAX ];

	TCB_PTR		tcb;
};



//==============================================================
// Prototype
//==============================================================
static void PoketchA01ViewMain(TCB_PTR tcb, void *wk_adrs );
static void CounterUpdate( POKETCH_A01_VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK *cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static BOOL LoadObjDatas( POKETCH_A01_VIEWWORK *vwk );
static void SetupObj( POKETCH_A01_VIEWWORK *vwk, const POKETCH_A01_VIEW_PARAM* vpara );
static void CmdButtonUpdate( TCB_PTR tcb, void *wk_adrs );
static void BtnUpdateFree( TCB_PTR tcb, void *wk_adrs );
static void BtnUpdatePush( TCB_PTR tcb, void *wk_adrs );
static void BtnUpdateCount( TCB_PTR tcb, void *wk_adrs );
static void BtnUpdateReset1( TCB_PTR tcb, void *wk_adrs );
static void BtnUpdateReset2( TCB_PTR tcb, void *wk_adrs );
static void BtnUpdateBomb( TCB_PTR tcb, void *wk_adrs );
static void BtnUpdateBurn( TCB_PTR tcb, void *wk_adrs );
static BOOL BtnEffectProg( BTN_EFFECT_WORK *wk, u32 time );
static void ButtonScrnMake( GF_BGL_INI* bgl, u32 btn );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void DeleteAllObj( POKETCH_A01_VIEWWORK* wk );

extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);



//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A01_SetViewWork(POKETCH_A01_VIEWWORK **wk_ptr, const POKETCH_A01_VIEW_PARAM *vpara, GF_BGL_INI* bgl)
{
	POKETCH_A01_VIEWWORK *wk = (POKETCH_A01_VIEWWORK*)sys_AllocMemory(POKETCH_APP_VIEW_HEAPID, sizeof(POKETCH_A01_VIEWWORK));

	if(wk != NULL)
	{
		wk->vpara = vpara;
		wk->actsys = PoketchGetActSys();
		wk->bgl = GF_BGL_BglIniAlloc( POKETCH_APP_VIEW_HEAPID );

		if( wk->bgl == NULL )
		{
			return FALSE;
		}

		if( PACT_TOOL_LoadCellDatas(&wk->stopwatch_clpack, ARC_POKETCH_IMG,
			NARC_poketch_stop_ncer, NARC_poketch_stop_nanr, POKETCH_APP_VIEW_HEAPID )
		){
			if( PACT_TOOL_LoadCellDatas(&wk->numobj_clpack, ARC_POKETCH_IMG,
				NARC_poketch_numobj_ncer, NARC_poketch_numobj_nanr, POKETCH_APP_VIEW_HEAPID )
			){
				PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
				wk->tcb = NULL;

				*wk_ptr = wk;

				return TRUE;
			}
			else
			{
				PACT_TOOL_UnloadCellDatas( &(wk->stopwatch_clpack) );
			}
		}
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * ワーク削除
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void Poketch_A01_DeleteViewWork( POKETCH_A01_VIEWWORK* wk )
{
	if( wk )
	{
		if( wk->bgl )
		{
			sys_FreeMemoryEz( wk->bgl );
		}
		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * メインタスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PoketchA01ViewMain(TCB_PTR tcb, void *wk_adrs )
{
	POKETCH_A01_VIEWWORK *wk = (POKETCH_A01_VIEWWORK*)wk_adrs;

	CounterUpdate( wk );
}

static void CounterUpdate( POKETCH_A01_VIEWWORK* wk )
{
	u32 u, l;

	CP_SetDiv32_32( wk->vpara->hour, 10 );
	u = CP_GetDivResult32();
	l = CP_GetDivRemainder32();
	PACT_ChangeAnmSeq( wk->act[ACT_HOUR0], ANMSEQ_NUM0 + u );
	PACT_ChangeAnmSeq( wk->act[ACT_HOUR1], ANMSEQ_NUM0 + l );

	CP_SetDiv32_32( wk->vpara->min, 10 );
	u = CP_GetDivResult32();
	l = CP_GetDivRemainder32();
	PACT_ChangeAnmSeq( wk->act[ACT_MIN0], ANMSEQ_NUM0 + u );
	PACT_ChangeAnmSeq( wk->act[ACT_MIN1], ANMSEQ_NUM0 + l );

	CP_SetDiv32_32( wk->vpara->sec, 10 );
	u = CP_GetDivResult32();
	l = CP_GetDivRemainder32();
	PACT_ChangeAnmSeq( wk->act[ACT_SEC0], ANMSEQ_NUM0 + u );
	PACT_ChangeAnmSeq( wk->act[ACT_SEC1], ANMSEQ_NUM0 + l );

	CP_SetDiv32_32( wk->vpara->msec, 10 );
	u = CP_GetDivResult32();
	l = CP_GetDivRemainder32();
	PACT_ChangeAnmSeq( wk->act[ACT_MSEC0], ANMSEQ_NUM0 + u );
	PACT_ChangeAnmSeq( wk->act[ACT_MSEC1], ANMSEQ_NUM0 + l );
}

//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------

static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_BTN_UPDATE, CmdButtonUpdate, sizeof( BTN_EFFECT_WORK ) },
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
void Poketch_A01_SetViewCommand(POKETCH_A01_VIEWWORK *wk, u32 cmd)
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
BOOL Poketch_A01_WaitViewCommand(POKETCH_A01_VIEWWORK *wk, u32 cmd)
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
BOOL Poketch_A01_WaitViewCommandAll(POKETCH_A01_VIEWWORK *wk)
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
static void DeleteCommand(POKETCH_CMD_WORK *cwk)
{
	POKETCH_A01_VIEWWORK *wk = PoketchViewTool_GetViewWork(cwk);
	PoketchViewTool_DelCommand( wk->cmd_store, cwk );
}

//------------------------------------------------------------------
/**
 * コマンド：画面構築
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
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
	POKETCH_A01_VIEWWORK*  vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet(ARC_POKETCH_IMG, NARC_poketch_stopbg_ncgr, vwk->bgl,
							USE_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	ArcUtil_ScrnSet(ARC_POKETCH_IMG, NARC_poketch_stop_nscr, vwk->bgl,
							USE_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PoketchView_SetBaseColorPalette(0, 0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );


	// -----
	{
		POKETCH_A01_VIEWWORK* wk = PoketchViewTool_GetViewWork( wk_ptr );
		const POKETCH_A01_VIEW_PARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );
		LoadObjDatas( wk );
		SetupObj( wk, vpara );
		vwk->tcb = TCB_Add( PoketchA01ViewMain, vwk, POKETCH_GRAPHIC_TASKPRI + 1 );

		CounterUpdate( wk );
		if( vpara->counter_action_flag )
		{
			Poketch_A01_SetViewCommand( wk, CMD_BTN_UPDATE );
		}
	}


	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);

	DeleteCommand( wk_ptr );

}
//------------------------------------------------------------------
/**
 * OBJに使うキャラ・パレットをVRAMにロード
 *
 * @param   vwk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL LoadObjDatas( POKETCH_A01_VIEWWORK *vwk )
{
	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_numobj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_stopobj_ncgr, OBJTYPE_SUB, 80*0x20, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	return TRUE;
}
//------------------------------------------------------------------
/**
 * OBJ初期化
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
static void SetupObj( POKETCH_A01_VIEWWORK *vwk, const POKETCH_A01_VIEW_PARAM* vpara )
{
	static const PACT_ADD_PARAM param[] = {
		{
			{  FX32INT(OBJ_HOUR_XPOS), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{  FX32INT(OBJ_HOUR_XPOS+OBJ_NUMBER_WIDTH), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{  FX32INT(OBJ_MIN_XPOS), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{ FX32INT(OBJ_MIN_XPOS+OBJ_NUMBER_WIDTH), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{  FX32INT(OBJ_SEC_XPOS), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{ FX32INT(OBJ_SEC_XPOS+OBJ_NUMBER_WIDTH), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{  FX32INT(OBJ_MSEC_XPOS), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{ FX32INT(OBJ_MSEC_XPOS+OBJ_NUMBER_WIDTH), FX32INT(OBJ_NUMBER_YPOS) },
			ANMSEQ_NUM0, 0, BGPRI2, OAMPRI_NUM, FALSE,
		},{
			{ FX32INT(OBJ_EYE_XPOS), FX32INT(OBJ_EYE_YPOS) },
			ANMSEQ_EYE_FREE, 0, BGPRI2, OAMPRI_EYE, FALSE,
		}
	};

	u32 i;

	for(i = ACT_NUM_START; i <= ACT_NUM_END; i++)
	{
		vwk->act[ACT_NUM_START+i] = PACT_Add( vwk->actsys, &param[i], &vwk->numobj_clpack );
	}

	vwk->act[ACT_EYE] = PACT_Add( vwk->actsys, &param[i], &vwk->stopwatch_clpack );
	if( vpara->counter_action_flag == FALSE )
	{
		PACT_SetVanish( vwk->act[ ACT_EYE], TRUE );
	}
}



//------------------------------------------------------------------
/**
 * コマンド：ボタン状態更新
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 */
//------------------------------------------------------------------
static void CmdButtonUpdate( TCB_PTR tcb, void *wk_adrs )
{
	static void (* const tcb_tbl[])( TCB_PTR, void* ) = {
		BtnUpdateFree,
		BtnUpdatePush,
		BtnUpdateCount,
		BtnUpdateReset1,
		BtnUpdateReset2,
		BtnUpdateBomb,
		BtnUpdateBurn,
	};

	const POKETCH_A01_VIEW_PARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );

	TCB_ChangeFunc( tcb, tcb_tbl[ vpara->btn ] );
	tcb_tbl[ vpara->btn ]( tcb, wk_adrs );
}

//------------------------------------------------------------------
/**
 * ボタン更新：解放状態のとき
 */
//------------------------------------------------------------------
static void BtnUpdateFree( TCB_PTR tcb, void *wk_adrs )
{
	POKETCH_A01_VIEWWORK* wk = PoketchViewTool_GetViewWork( wk_adrs );
	const POKETCH_A01_VIEW_PARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );

	PACT_SetVanish( wk->act[ACT_EYE], TRUE );
	ButtonScrnMake( wk->bgl, BTN_BGIMG_FREE );
	GF_BGL_LoadScreenReq( wk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * ボタン更新：押されてる時
 */
//------------------------------------------------------------------
static void BtnUpdatePush( TCB_PTR tcb, void *wk_adrs )
{
	POKETCH_A01_VIEWWORK* wk = PoketchViewTool_GetViewWork( wk_adrs );

	PACT_SetVanish( wk->act[ACT_EYE], FALSE );
	PACT_ChangeAnmSeq( wk->act[ACT_EYE], ANMSEQ_EYE_PUSH );

	ButtonScrnMake( wk->bgl, BTN_BGIMG_PUSH );
	GF_BGL_LoadScreenReq( wk->bgl, USE_BG_FRAME );
	PoketchSePlay( POKETCH_SE_STOPWATCH_PUSH );
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * ボタン更新：カウント中の時
 */
//------------------------------------------------------------------
static void BtnUpdateCount( TCB_PTR tcb, void *wk_adrs )
{
	const POKETCH_A01_VIEW_PARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );
	POKETCH_A01_VIEWWORK* wk = PoketchViewTool_GetViewWork( wk_adrs );

	if( vpara->btn != BTN_STATE_COUNT )
	{
		// クリーンアップ処理ここに描く
		DeleteCommand( wk_adrs );
		return;
	}

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		PACT_ChangeAnmSeq( wk->act[ACT_EYE], ANMSEQ_EYE_COUNT );
		ButtonScrnMake( wk->bgl, BTN_BGIMG_FREE );
		GF_BGL_LoadScreenReq( wk->bgl, USE_BG_FRAME );
		PoketchViewTool_FwdSeq( wk_adrs );
		break;

	case 1:
		// この辺でＯＢＪを動かす
		break;
	}
}
//------------------------------------------------------------------
/**
 * ボタン更新：リセット前エフェクト
 */
//------------------------------------------------------------------
static void BtnUpdateReset1( TCB_PTR tcb, void *wk_adrs )
{
	enum {
		BTN_UPDATE_TIME = 6,
	};

	const POKETCH_A01_VIEW_PARAM* vpara;
	POKETCH_A01_VIEWWORK* vwk;
	BTN_EFFECT_WORK *wk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );
	wk = PoketchViewTool_GetCmdWork( wk_adrs );

	if( vpara->btn != BTN_STATE_RESET1 )
	{
		// クリーンアップ処理ここに描く
		DeleteCommand( wk_adrs );
		return;
	}

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		wk->time = BTN_UPDATE_TIME;
		wk->btn_state = BTN_BGIMG_EFF1;
		wk->btn_prog = 0;
		PACT_ChangeAnmSeq( vwk->act[ACT_EYE], ANMSEQ_EYE_RESET1 );
		PoketchViewTool_FwdSeq( wk_adrs );
		/* fallthru */
	case 1:
		if( BtnEffectProg( wk, BTN_UPDATE_TIME ) )
		{
			PoketchSePlay( POKETCH_SE_STOPWATCH_PUSH );
			ButtonScrnMake( vwk->bgl, wk->btn_state );
			GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
		}
		break;
	}

}
//------------------------------------------------------------------
/**
 * ボタン更新：リセット確定エフェクト
 */
//------------------------------------------------------------------
static void BtnUpdateReset2( TCB_PTR tcb, void *wk_adrs )
{
	enum {
		BTN_UPDATE_TIME = 3,
	};

	const POKETCH_A01_VIEW_PARAM* vpara;
	POKETCH_A01_VIEWWORK *vwk;
	BTN_EFFECT_WORK *wk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );
	wk = PoketchViewTool_GetCmdWork( wk_adrs );

	if( vpara->btn != BTN_STATE_RESET2 )
	{
		// クリーンアップ処理ここに描く
		DeleteCommand( wk_adrs );
		return;
	}

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		wk->time = BTN_UPDATE_TIME;
		wk->btn_state = BTN_BGIMG_EFF1;
		wk->btn_prog = 0;
		PACT_ChangeAnmSeq( vwk->act[ACT_EYE], ANMSEQ_EYE_RESET2 );
		PoketchViewTool_FwdSeq( wk_adrs );
		/* fallthru */
	case 1:
		if( BtnEffectProg( wk, BTN_UPDATE_TIME ) )
		{
			PoketchSePlay( POKETCH_SE_STOPWATCH_RESET );
			ButtonScrnMake( vwk->bgl, wk->btn_state );
			GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * ボタン更新：爆発エフェクト
 */
//------------------------------------------------------------------
static void BtnUpdateBomb( TCB_PTR tcb, void *wk_adrs )
{
	enum {
		BTN_UPDATE_TIME = 2,
	};

	const POKETCH_A01_VIEW_PARAM* vpara;
	POKETCH_A01_VIEWWORK *vwk;
	BTN_EFFECT_WORK *wk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );
	wk = PoketchViewTool_GetCmdWork( wk_adrs );

	if( vpara->btn != BTN_STATE_BOMB )
	{
		// クリーンアップ処理ここに描く
		DeleteCommand( wk_adrs );
		return;
	}

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		wk->time = 0;
		wk->btn_prog = 0;
		PACT_ChangeAnmSeq( vwk->act[ACT_EYE], ANMSEQ_EYE_BOMB );
		ButtonScrnMake( vwk->bgl, BTN_BGIMG_BLACKPUSH );
		GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
		PoketchSePlay( POKETCH_SE_STOPWATCH_BOMB );
		PoketchViewTool_FwdSeq( wk_adrs );
		/* fallthru */
	case 1:
		if( ++(wk->time) > BTN_UPDATE_TIME )
		{
			wk->time = 0;
			wk->btn_prog ^= 1;
			wk->btn_state = BTN_BGIMG_BLACKPUSH + wk->btn_prog;
			ButtonScrnMake( vwk->bgl, wk->btn_state );
			GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * ボタン更新：焦げエフェクト
 */
//------------------------------------------------------------------
static void BtnUpdateBurn( TCB_PTR tcb, void *wk_adrs )
{
	enum {
		EFF_WAIT_TIME = 80,
	};

	const POKETCH_A01_VIEW_PARAM* vpara;
	POKETCH_A01_VIEWWORK *vwk;
	BTN_EFFECT_WORK *wk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );
	wk = PoketchViewTool_GetCmdWork( wk_adrs );

	if( vpara->btn != BTN_STATE_BURN )
	{
		// クリーンアップ処理ここに描く
		DeleteCommand( wk_adrs );
		return;
	}

	switch( PoketchViewTool_GetSeq( wk_adrs ) ){
	case 0:
		PACT_ChangeAnmSeq( vwk->act[ACT_EYE], ANMSEQ_EYE_BURN );
		ButtonScrnMake( vwk->bgl, BTN_BGIMG_BLACKFREE );
		GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
		PoketchViewTool_FwdSeq( wk_adrs );
		wk->time = 0;
		/* fallthru */
	case 1:
		if(++(wk->time) > EFF_WAIT_TIME)
		{
			DeleteCommand(wk_adrs);
		}
		break;
	}

}
//------------------------------------------------------------------
/**
 * ボタンエフェクトアニメ更新処理
 *
 * @param   wk			ボタンエフェクトワーク
 * @param   time		更新させる時間（フレーム）
 *
 * @retval  BOOL		TRUEで更新あり
 */
//------------------------------------------------------------------
static BOOL BtnEffectProg( BTN_EFFECT_WORK *wk, u32 time )
{
	static const u8 state[] = {
		BTN_BGIMG_EFF1, BTN_BGIMG_EFF2, BTN_BGIMG_EFF3,
	};

	if(++(wk->time) > time)
	{
		wk->time = 0;
		if(++(wk->btn_prog) >= NELEMS(state))
		{
			wk->btn_prog = 0;
		}
		wk->btn_state = state[ wk->btn_prog ];
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * ボタンのスクリーン作成
 *
 * @param   btn		ボタン種類
 *
 */
//------------------------------------------------------------------
static void ButtonScrnMake( GF_BGL_INI* bgl, u32 btn )
{
	u16* scrn;
	u32 x, y;
	u16 charno;

	scrn = GF_BGL_ScreenAdrsGet( bgl, USE_BG_FRAME );
	scrn += ((BTN_SCRN_YORG * 32) + BTN_SCRN_XORG);
	charno = BTN_CHAR_TOP + btn * BTN_CHAR_WIDTH;

	for(y = 0; y < BTN_CHAR_HEIGHT; y++)
	{
		for(x = 0; x < BTN_CHAR_WIDTH; x++)
		{
			scrn[x] = ((BG_PALNO << 1) | (charno+x) );
			scrn[BTN_CHAR_WIDTH*2-1-x] = ((BG_PALNO << 1) | (charno+x) | GX_SCRFMT_TEXT_HF_MASK) ;
		}
		scrn += 32;
		charno += BG_CHAR_WIDTH;
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
	POKETCH_A01_VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	u32 seq = PoketchViewTool_GetSeq( wk_ptr );

	switch( seq ){
	case 0:
		DeleteAllObj( vwk );
		PoketchViewTool_FwdSeq( wk_ptr );
		/* fallthru */
	case 1:
		PACT_TOOL_UnloadCellDatas( &(vwk->stopwatch_clpack) );
		PACT_TOOL_UnloadCellDatas( &(vwk->numobj_clpack) );
		GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
		TCB_Delete( vwk->tcb );
		vwk->tcb = NULL;
		DeleteCommand( wk_ptr );
		break;
	}
}
static void DeleteAllObj( POKETCH_A01_VIEWWORK* wk )
{
	u32 i;
	for(i = ACT_HOUR0; i < ACT_USE_MAX; i++)
	{
		PACT_Del( wk->actsys, wk->act[i] );
	}
}






