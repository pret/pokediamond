//============================================================================================
/**
 * @file	poketch_a27v.c
 * @bfief	ポケッチ（アプリNo27:つうしんサーチャー）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "system\msgdata.h"
#include "system\fontproc.h"
#include "system\wordset.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_poketch_tusin.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a27.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)


enum {
	ACTID_DS_IMAGE,
	ACTID_WAVE,
	ACTID_ALART,
	ACTID_BAR,

	ACTID_MAX,
};

enum {
	ANMSEQ_BAR,
	ANMSEQ_WAVE,
	ANMSEQ_ALART,
	ANMSEQ_DS,
};

enum {
	ACTPOS_DSIMG_X = DSIMG_POS_X,
	ACTPOS_DSIMG_Y = DSIMG_POS_Y,
	ACTPOS_WAVE_X = ACTPOS_DSIMG_X,
	ACTPOS_WAVE_Y = ACTPOS_DSIMG_Y - 48,
	ACTPOS_ALART_X = ACTPOS_DSIMG_X,
	ACTPOS_ALART_Y = ACTPOS_DSIMG_Y - 48,
	ACTPOS_BAR_X = ACTPOS_DSIMG_X,
	ACTPOS_BAR_Y = ACTPOS_DSIMG_Y,

};


enum {
	PRINT_FONT    = FONT_SYSTEM,
	COLOR_LETTER  = POKETCH_DEFAULTCOLOR_L4_POS,
	COLOR_SHADOW  = POKETCH_DEFAULTCOLOR_L4_POS,
	COLOR_GROUND  = POKETCH_DEFAULTCOLOR_L1_POS,
	STR_TMPBUFFER_SIZE = 96,

	TOP_TITLE_PRINT_Y = 8,

	SEARCHING_STR_PRINT_X = 16,
	SEARCHING_STR_PRINT_Y = 16,

	ERR_STR_PRINT_X = 16,
	ERR_STR_PRINT_Y = 24,


	STATUS_PRINT_Y = 32,
	STATUS_PRINT_Y_MARGIN = 16,

	STATUS_TITLE_PRINT_X = 8,
	STATUS_NUM_PRINT_X   = 160,
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A27_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	GF_BGL_BMPWIN      bmpwin;

	PACTSYS*           actsys;
	PACT*              actor[ ACTID_MAX ];
	PACT_CLANM_PACK    clpack;

	MSGDATA_MANAGER*   mm;
	STRBUF*            tmpbuf;
};




//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdImgTop( TCB_PTR tcb, void* wk_ptr );
static void CmgImgSearching( TCB_PTR tcb, void* wk_ptr );
static void CmdImgErrorCantConnect( TCB_PTR tcb, void* wk_ptr );
static void CmdImgErrorDontMove( TCB_PTR tcb, void* wk_ptr );
static void CmdImgStatus( TCB_PTR tcb, void* wk_ptr );
static void CmdImgStatusUpdate( TCB_PTR tcb, void* wk_ptr );
static void print_bmp_top_title( VIEWWORK* vwk );
static void print_bmp_searching( VIEWWORK* vwk );
static void print_bmp_cant_connect( VIEWWORK* vwk );
static void print_bmp_dont_move( VIEWWORK* vwk );
static void print_bmp_status( VIEWWORK* vwk, const VIEWPARAM* vpara );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A27_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();
		wk->mm = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_poketch_tusin_dat, POKETCH_APP_VIEW_HEAPID);
		wk->tmpbuf = STRBUF_Create( STR_TMPBUFFER_SIZE, POKETCH_APP_VIEW_HEAPID );

		setup_actors(wk, vpara);

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
void Poketch_A27_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		STRBUF_Delete( wk->tmpbuf );
		MSGMAN_Delete( wk->mm );
		cleanup_actors( wk );
		sys_FreeMemoryEz( wk );
	}
}

static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM  actparam[] = {
		{ { FX32INT(ACTPOS_DSIMG_X), FX32INT(ACTPOS_DSIMG_Y) }, ANMSEQ_DS,		0, BGPRI2, 0, FALSE, },
		{ { FX32INT(ACTPOS_WAVE_X),  FX32INT(ACTPOS_WAVE_Y) }, 	ANMSEQ_WAVE,	0, BGPRI2, 0, FALSE, },
		{ { FX32INT(ACTPOS_ALART_X), FX32INT(ACTPOS_ALART_Y) },	ANMSEQ_ALART,	0, BGPRI2, 0, FALSE, },
		{ { FX32INT(ACTPOS_BAR_X),   FX32INT(ACTPOS_BAR_Y) },	ANMSEQ_BAR,		0, BGPRI2, 0, FALSE, },
	};

	int i;

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_tusin_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_tusin_lz_ncer, NARC_poketch_tusin_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	for(i=0; i<ACTID_MAX; i++)
	{
		wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack );
	}

	PACT_SetVanish( wk->actor[ACTID_WAVE], TRUE );
	PACT_SetVanish( wk->actor[ACTID_ALART], TRUE );
	PACT_SetVanish( wk->actor[ACTID_BAR], TRUE );

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
}



//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },
	{ CMD_IMG_TOP, CmdImgTop, 0 },
	{ CMD_IMG_SEARCHING, CmgImgSearching, 0 },
	{ CMD_IMG_ERROR_CANT_CONNECT, CmdImgErrorCantConnect, 0 },
	{ CMD_IMG_ERROR_DONT_MOVE, CmdImgErrorDontMove, 0 },
	{ CMD_IMG_STATUS, CmdImgStatus, 0 },
	{ CMD_IMG_STATUS_UPDATE, CmdImgStatusUpdate, 0 },

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
void Poketch_A27_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A27_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A27_WaitViewCommandAll(VIEWWORK* wk)
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
	u32 charno;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	charno = ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_tusin_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	charno /= 0x20;
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_tusin_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	GF_BGL_BmpWinAdd( vwk->bgl, &vwk->bmpwin, USE_BG_FRAME, POKETCH_MONITOR_SCRN_XORG, POKETCH_MONITOR_SCRN_YORG,
				POKETCH_MONITOR_SCRN_WIDTH, POKETCH_MONITOR_SCRN_HEIGHT, 0, charno );

	GF_BGL_BmpWinMakeScrn( &vwk->bmpwin );
	print_bmp_top_title( vwk );

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

	GF_BGL_BmpWinDel(&vwk->bmpwin);

	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}



static void CmdImgTop( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	PACT_SetVanish( vwk->actor[ACTID_DS_IMAGE],	FALSE );
	PACT_SetVanish( vwk->actor[ACTID_WAVE],		TRUE );
	PACT_SetVanish( vwk->actor[ACTID_ALART],	TRUE );
	PACT_SetVanish( vwk->actor[ACTID_BAR],		TRUE );

	print_bmp_top_title(vwk);

	PoketchSePlay(POKETCH_SE_TUSIN_SWITCH_MODE);

	DeleteCommand( wk_ptr );
}

static void CmgImgSearching( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	PACT_SetVanish( vwk->actor[ACTID_DS_IMAGE],	FALSE );
	PACT_SetVanish( vwk->actor[ACTID_WAVE],		FALSE );
	PACT_SetVanish( vwk->actor[ACTID_ALART],	TRUE );
	PACT_SetVanish( vwk->actor[ACTID_BAR],		TRUE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_WAVE],  ANMSEQ_WAVE );

	print_bmp_searching(vwk);

	PoketchSePlay(POKETCH_SE_TUSIN_SWITCH_MODE);

	DeleteCommand( wk_ptr );
}

static void CmdImgErrorCantConnect( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	PACT_SetVanish( vwk->actor[ACTID_DS_IMAGE],	FALSE );
	PACT_SetVanish( vwk->actor[ACTID_WAVE],		TRUE );
	PACT_SetVanish( vwk->actor[ACTID_ALART],	FALSE );
	PACT_SetVanish( vwk->actor[ACTID_BAR],		TRUE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_ALART],  ANMSEQ_ALART );

	print_bmp_cant_connect(vwk);

	PoketchSePlay(POKETCH_SE_TUSIN_SWITCH_MODE_ERR);

	DeleteCommand( wk_ptr );
}
static void CmdImgErrorDontMove( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	PACT_SetVanish( vwk->actor[ACTID_DS_IMAGE],	FALSE );
	PACT_SetVanish( vwk->actor[ACTID_WAVE],		TRUE );
	PACT_SetVanish( vwk->actor[ACTID_ALART],	FALSE );
	PACT_SetVanish( vwk->actor[ACTID_BAR],		TRUE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_ALART],  ANMSEQ_ALART );

	print_bmp_dont_move(vwk);

	PoketchSePlay(POKETCH_SE_TUSIN_SWITCH_MODE_ERR);

	DeleteCommand( wk_ptr );
}
static void CmdImgStatus( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	PACT_SetVanish( vwk->actor[ACTID_DS_IMAGE],	TRUE );
	PACT_SetVanish( vwk->actor[ACTID_WAVE],		TRUE );
	PACT_SetVanish( vwk->actor[ACTID_ALART],	TRUE );
	PACT_SetVanish( vwk->actor[ACTID_BAR],		FALSE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_BAR],  ANMSEQ_BAR );

	print_bmp_status(vwk, vpara);

	PoketchSePlay(POKETCH_SE_TUSIN_SWITCH_MODE);

	DeleteCommand( wk_ptr );

}
static void CmdImgStatusUpdate( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	print_bmp_status(vwk, vpara);

	DeleteCommand( wk_ptr );
}






static void print_bmp_top_title( VIEWWORK* vwk )
{
	u32 xpos;

	GF_BGL_BmpWinDataFill( &vwk->bmpwin, COLOR_GROUND );

	MSGMAN_GetString( vwk->mm, msg_top_title, vwk->tmpbuf );
	xpos = ((POKETCH_MONITOR_SCRN_WIDTH*8) - FontProc_GetPrintStrWidth( PRINT_FONT, vwk->tmpbuf, 0 ) ) / 2;

	GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, xpos, TOP_TITLE_PRINT_Y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );

}
static void print_bmp_searching( VIEWWORK* vwk )
{
	GF_BGL_BmpWinDataFill( &vwk->bmpwin, COLOR_GROUND );

	MSGMAN_GetString( vwk->mm, msg_searching, vwk->tmpbuf );

	GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, SEARCHING_STR_PRINT_X, SEARCHING_STR_PRINT_Y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );
}

static void print_bmp_cant_connect( VIEWWORK* vwk )
{
	u32 xpos;

	GF_BGL_BmpWinDataFill( &vwk->bmpwin, COLOR_GROUND );

	MSGMAN_GetString( vwk->mm, msg_err, vwk->tmpbuf );
	xpos = ((POKETCH_MONITOR_SCRN_WIDTH*8) - FontProc_GetPrintStrWidth( PRINT_FONT, vwk->tmpbuf, 0 ) ) / 2;
	GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, xpos, TOP_TITLE_PRINT_Y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	MSGMAN_GetString( vwk->mm, msg_err_cant_connect, vwk->tmpbuf );
	GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, ERR_STR_PRINT_X, ERR_STR_PRINT_Y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );
}
static void print_bmp_dont_move( VIEWWORK* vwk )
{
	u32 xpos;

	GF_BGL_BmpWinDataFill( &vwk->bmpwin, COLOR_GROUND );

	MSGMAN_GetString( vwk->mm, msg_err, vwk->tmpbuf );
	xpos = ((POKETCH_MONITOR_SCRN_WIDTH*8) - FontProc_GetPrintStrWidth( PRINT_FONT, vwk->tmpbuf, 0 ) ) / 2;
	GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, xpos, TOP_TITLE_PRINT_Y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	MSGMAN_GetString( vwk->mm, msg_err_dont_move, vwk->tmpbuf );
	GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, ERR_STR_PRINT_X, ERR_STR_PRINT_Y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );
}

static void print_bmp_status( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	// このテーブルの要素数は POKETCH_COMM_CATEGORY_MAX と一致させる必要がある
	static const u8 strid[] = {
		msg_category1,
		msg_category2,
		msg_category3,
		msg_category4,
	};

	u32 xpos;
	int i;

	GF_BGL_BmpWinDataFill( &vwk->bmpwin, COLOR_GROUND );

	MSGMAN_GetString( vwk->mm, msg_state_title, vwk->tmpbuf );
	xpos = ((POKETCH_MONITOR_SCRN_WIDTH*8) - FontProc_GetPrintStrWidth( PRINT_FONT, vwk->tmpbuf, 0 ) ) / 2;
	GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, xpos, TOP_TITLE_PRINT_Y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	for(i=0; i<POKETCH_COMM_CATEGORY_MAX; i++)
	{
		MSGMAN_GetString( vwk->mm, strid[i], vwk->tmpbuf );
		GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, 
						STATUS_TITLE_PRINT_X, STATUS_PRINT_Y + STATUS_PRINT_Y_MARGIN*i, MSG_NO_PUT, 
						GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

		STRBUF_SetNumber( vwk->tmpbuf, vpara->players_count[i], 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintColor( &vwk->bmpwin, PRINT_FONT, vwk->tmpbuf, 
						STATUS_NUM_PRINT_X, STATUS_PRINT_Y + STATUS_PRINT_Y_MARGIN*i, MSG_NO_PUT, 
						GF_PRINTCOLOR_MAKE(COLOR_LETTER,COLOR_SHADOW,COLOR_GROUND), NULL );

	}

	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );
}
