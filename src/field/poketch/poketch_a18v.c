//============================================================================================
/**
 * @file	poketch_a18v.c
 * @bfief	ポケッチ（アプリNo18:わざ相性チェッカー）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\msgdata.h"
#include "system\lib_pack.h"
#include "system\fontproc.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_poketch_aisyou.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a18.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)
#define USE_BG_PALNO	(0)

enum {
	ANMSEQ_BUTTON_FREE_L,
	ANMSEQ_BUTTON_PUSH_L,
	ANMSEQ_BUTTON_FREE_R,
	ANMSEQ_BUTTON_PUSH_R,
	ANMSEQ_EFFECT_ON,
	ANMSEQ_EFFECT_OFF,
};

enum {
	ACTID_BUTTON_ATTACK_L,
	ACTID_BUTTON_ATTACK_R,
	ACTID_BUTTON_DEFENCE0_L,
	ACTID_BUTTON_DEFENCE0_R,
	ACTID_BUTTON_DEFENCE1_L,
	ACTID_BUTTON_DEFENCE1_R,

	ACTID_BUTTON_MAX,

	ACTID_EFFECT_MAX = 5,
};

enum {
	ACTPOS_EFFECT_X = 44,
	ACTPOS_EFFECT_Y = 48,
	ACTSIZE_EFFECT_WIDTH = 8,
};

enum {
	TYPE_WIN_WIDTH = 6,
	TYPE_WIN_HEIGHT = 2,
	TYPE_WIN_CHARSIZE = TYPE_WIN_WIDTH * TYPE_WIN_HEIGHT,

	ATTACK_WIN_X = 6,
	ATTACK_WIN_Y = 15,
	DEFENCE0_WIN_X = 16,
	DEFENCE0_WIN_Y = 4,
	DEFENCE1_WIN_X = 16,
	DEFENCE1_WIN_Y = 8,

	INFO_WIN_X = 3,
	INFO_WIN_Y = 19,
	INFO_WIN_WIDTH = 22,
	INFO_WIN_HEIGHT = 2,
};

enum {
	PRINT_COL_LETTER = POKETCH_DEFAULTCOLOR_L4_POS,
	PRINT_COL_SHADOW = POKETCH_DEFAULTCOLOR_L4_POS,
	PRINT_COL_GROUND = POKETCH_DEFAULTCOLOR_L1_POS,
	PRINT_FONT_TYPE = FONT_SYSTEM,

	TMP_BUFFER_SIZE = 128,
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A18_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_button[ACTID_BUTTON_MAX];
	PACT*              act_effect[ACTID_EFFECT_MAX];
	PACT_CLANM_PACK    clpack;

	GF_BGL_BMPWIN      bmpwin_attack;
	GF_BGL_BMPWIN      bmpwin_defence0;
	GF_BGL_BMPWIN      bmpwin_defence1;
	GF_BGL_BMPWIN      bmpwin_info;

	MSGDATA_MANAGER*   mm_typename;
	MSGDATA_MANAGER*   mm_poketch_aisyou;
	STRBUF*            tmpbuf;
};




//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void setup_bmpwin( VIEWWORK* vwk, const VIEWPARAM* vpara, u32 charpos );
static void cleanup_bmpwin( VIEWWORK* vwk );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdButtonPush(TCB_PTR tcb, void* wk_adrs);
static void CmdButtonRelease(TCB_PTR tcb, void* wk_adrs);
static void CmdUpdateEffect(TCB_PTR tcb, void* wk_adrs);
static void update_effect( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void update_type_win( VIEWWORK* vwk, GF_BGL_BMPWIN* win, u32 type );
static void update_info_win( VIEWWORK* vwk, GF_BGL_BMPWIN* win, u32 eff_lv );
static void update_effect_actors( VIEWWORK* vwk, u32 eff_lv );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A18_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		wk->mm_typename = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_typename_dat, POKETCH_APP_VIEW_HEAPID );
		wk->mm_poketch_aisyou = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_poketch_aisyou_dat, POKETCH_APP_VIEW_HEAPID );
		wk->tmpbuf = STRBUF_Create(TMP_BUFFER_SIZE, POKETCH_APP_VIEW_HEAPID);

		setup_actors(wk);

		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}

static void setup_actors( VIEWWORK* wk )
{
	static const PACT_ADD_PARAM actparam_button[] = {
		{
			{  FX32INT(BUTTON_ATTACK_L_X), FX32INT(BUTTON_ATTACK_L_Y) },
			ANMSEQ_BUTTON_FREE_L, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(BUTTON_ATTACK_R_X), FX32INT(BUTTON_ATTACK_R_Y) },
			ANMSEQ_BUTTON_FREE_R, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(BUTTON_DEFENCE0_L_X), FX32INT(BUTTON_DEFENCE0_L_Y) },
			ANMSEQ_BUTTON_FREE_L, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(BUTTON_DEFENCE0_R_X), FX32INT(BUTTON_DEFENCE0_R_Y) },
			ANMSEQ_BUTTON_FREE_R, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(BUTTON_DEFENCE1_L_X), FX32INT(BUTTON_DEFENCE1_L_Y) },
			ANMSEQ_BUTTON_FREE_L, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(BUTTON_DEFENCE1_R_X), FX32INT(BUTTON_DEFENCE1_R_Y) },
			ANMSEQ_BUTTON_FREE_R, 0, BGPRI2, 0, FALSE,
		},
	};
	static const PACT_ADD_PARAM  actparam_effect = {
		{  FX32INT(ACTPOS_EFFECT_X), FX32INT(ACTPOS_EFFECT_Y) },
		ANMSEQ_EFFECT_OFF, 0, BGPRI2, 0, FALSE,
	};

	int i;

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_aisyo_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_aisyo_lz_ncer, NARC_poketch_aisyo_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	for(i=0; i<ACTID_BUTTON_MAX; i++)
	{
		wk->act_button[i] = PACT_Add(wk->actsys, &actparam_button[i], &wk->clpack);
	}

	for(i=0; i<ACTID_EFFECT_MAX; i++)
	{
		wk->act_effect[i] = PACT_Add(wk->actsys, &actparam_effect, &wk->clpack);
		PACT_SetPos( wk->act_effect[i], ((ACTPOS_EFFECT_X+ACTSIZE_EFFECT_WIDTH*i)<<FX32_SHIFT), ACTPOS_EFFECT_Y<<FX32_SHIFT );
	}
}

static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	for(i=0; i<ACTID_BUTTON_MAX; i++)
	{
		if( wk->act_button[i] )
		{
			PACT_Del( wk->actsys, wk->act_button[i] );
		}
	}
	for(i=0; i<ACTID_EFFECT_MAX; i++)
	{
		if( wk->act_effect[i] )
		{
			PACT_Del( wk->actsys, wk->act_effect[i] );
		}
	}


	PACT_TOOL_UnloadCellDatas(&wk->clpack);
}



//------------------------------------------------------------------
/**
 * ワーク削除
 *
 * @param   wk		確保したワークアドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A18_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		STRBUF_Delete( wk->tmpbuf );
		MSGMAN_Delete( wk->mm_typename );
		MSGMAN_Delete( wk->mm_poketch_aisyou );
		cleanup_actors( wk );
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
	{ CMD_BUTTON_PUSH, CmdButtonPush, 0 },
	{ CMD_BUTTON_RELEASE, CmdButtonRelease, 0 },
	{ CMD_UPDATE_EFFECT, CmdUpdateEffect, 0 },

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
void Poketch_A18_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A18_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A18_WaitViewCommandAll(VIEWWORK* wk)
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
	u32 charpos;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	charpos = ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_aisyo_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_aisyo_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	charpos /= 0x20;
	setup_bmpwin( vwk, vpara, charpos );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);

	DeleteCommand( wk_ptr );
}

static void setup_bmpwin( VIEWWORK* vwk, const VIEWPARAM* vpara, u32 charpos )
{
	GF_BGL_BmpWinAdd( vwk->bgl, &(vwk->bmpwin_attack), USE_BG_FRAME, ATTACK_WIN_X, ATTACK_WIN_Y,
					TYPE_WIN_WIDTH, TYPE_WIN_HEIGHT, USE_BG_PALNO, charpos );
	charpos += TYPE_WIN_CHARSIZE;

	GF_BGL_BmpWinAdd( vwk->bgl, &(vwk->bmpwin_defence0), USE_BG_FRAME, DEFENCE0_WIN_X, DEFENCE0_WIN_Y,
					TYPE_WIN_WIDTH, TYPE_WIN_HEIGHT, USE_BG_PALNO, charpos );
	charpos += TYPE_WIN_CHARSIZE;

	GF_BGL_BmpWinAdd( vwk->bgl, &(vwk->bmpwin_defence1), USE_BG_FRAME, DEFENCE1_WIN_X, DEFENCE1_WIN_Y,
					TYPE_WIN_WIDTH, TYPE_WIN_HEIGHT, USE_BG_PALNO, charpos );
	charpos += TYPE_WIN_CHARSIZE;

	GF_BGL_BmpWinAdd( vwk->bgl, &(vwk->bmpwin_info), USE_BG_FRAME, INFO_WIN_X, INFO_WIN_Y,
					INFO_WIN_WIDTH, INFO_WIN_HEIGHT, USE_BG_PALNO, charpos );


	GF_BGL_BmpWinMakeScrn(&(vwk->bmpwin_attack));
	GF_BGL_BmpWinMakeScrn(&(vwk->bmpwin_defence0));
	GF_BGL_BmpWinMakeScrn(&(vwk->bmpwin_defence1));
	GF_BGL_BmpWinMakeScrn(&(vwk->bmpwin_info));

	update_effect( vwk, vpara );
}

static void cleanup_bmpwin( VIEWWORK* vwk )
{
	GF_BGL_BmpWinDel(&(vwk->bmpwin_attack));
	GF_BGL_BmpWinDel(&(vwk->bmpwin_defence0));
	GF_BGL_BmpWinDel(&(vwk->bmpwin_defence1));
	GF_BGL_BmpWinDel(&(vwk->bmpwin_info));
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

	cleanup_bmpwin( vwk );
	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}


static void CmdButtonPush(TCB_PTR tcb, void* wk_adrs)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );
	u32 anmseq;

	anmseq = ( vpara->button_id & 1 )?  ANMSEQ_BUTTON_PUSH_R : ANMSEQ_BUTTON_PUSH_L;
	PACT_ChangeAnmSeq( vwk->act_button[vpara->button_id], anmseq );

	PoketchSePlay(POKETCH_SE_AISYOU_BUTTON);

	DeleteCommand(wk_adrs);
}
static void CmdButtonRelease(TCB_PTR tcb, void* wk_adrs)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );
	u32 anmseq;

	anmseq = ( vpara->button_id & 1 )?  ANMSEQ_BUTTON_FREE_R : ANMSEQ_BUTTON_FREE_L;
	PACT_ChangeAnmSeq( vwk->act_button[vpara->button_id], anmseq );

	DeleteCommand(wk_adrs);
}
static void CmdUpdateEffect(TCB_PTR tcb, void* wk_adrs)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_adrs );

	update_effect( vwk, vpara );

	DeleteCommand(wk_adrs);
}





static void update_effect( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	update_type_win( vwk, &(vwk->bmpwin_attack), vpara->attack_type );
	update_type_win( vwk, &(vwk->bmpwin_defence0), vpara->defence0_type );
	update_type_win( vwk, &(vwk->bmpwin_defence1), vpara->defence1_type );
	update_info_win( vwk, &(vwk->bmpwin_info), vpara->effect_lv );
	update_effect_actors( vwk, vpara->effect_lv );
}


static void update_type_win( VIEWWORK* vwk, GF_BGL_BMPWIN* win, u32 type )
{
	u32  str_width;

	GF_BGL_BmpWinDataFill( win, PRINT_COL_GROUND );

	if( type == AISYOU_TYPE_NULL )
	{
		MSGMAN_GetString( vwk->mm_poketch_aisyou, msg_type_null, vwk->tmpbuf );
	}
	else
	{
		MSGMAN_GetString( vwk->mm_typename, type, vwk->tmpbuf );
	}

	str_width = FontProc_GetPrintStrWidth( PRINT_FONT_TYPE, vwk->tmpbuf, 0 );

	GF_STR_PrintColor( win, PRINT_FONT_TYPE, vwk->tmpbuf, ((TYPE_WIN_WIDTH*8)-str_width)/2, 0, MSG_NO_PUT,
		GF_PRINTCOLOR_MAKE(PRINT_COL_LETTER,PRINT_COL_SHADOW,PRINT_COL_GROUND), NULL );

	GF_BGL_BmpWinCgxOn(win);
}

static void update_info_win( VIEWWORK* vwk, GF_BGL_BMPWIN* win, u32 eff_lv )
{
	GF_BGL_BmpWinDataFill( win, PRINT_COL_GROUND );

	MSGMAN_GetString( vwk->mm_poketch_aisyou, eff_lv, vwk->tmpbuf );
	GF_STR_PrintColor( win, PRINT_FONT_TYPE, vwk->tmpbuf, 0, 0, MSG_NO_PUT,
		GF_PRINTCOLOR_MAKE(PRINT_COL_LETTER,PRINT_COL_SHADOW,PRINT_COL_GROUND), NULL );
	GF_BGL_BmpWinCgxOn(win);
}

static void update_effect_actors( VIEWWORK* vwk, u32 eff_lv )
{
	u32 i;

	for(i=0; i<eff_lv; i++)
	{
		PACT_ChangeAnmSeq( vwk->act_effect[i], ANMSEQ_EFFECT_ON );
	}
	for( ; i<ACTID_EFFECT_MAX; i++)
	{
		PACT_ChangeAnmSeq( vwk->act_effect[i], ANMSEQ_EFFECT_OFF );
	}
}

