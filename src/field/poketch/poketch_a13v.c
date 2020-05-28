//============================================================================================
/**
 * @file	poketch_a13v.c
 * @bfief	ポケッチ（アプリNo13:トレーナーランチャー）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a13.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

#define SCREEN_POS(x,y)		(((y)*32)+(x))

enum {
	BUTTON_SCREENPOS_0 = SCREEN_POS(BUTTON0_SCRNPOS_X, BUTTON0_SCRNPOS_Y),
	BUTTON_SCREENPOS_1 = SCREEN_POS(BUTTON1_SCRNPOS_X, BUTTON1_SCRNPOS_Y),
	BUTTON_SCREENPOS_2 = SCREEN_POS(BUTTON2_SCRNPOS_X, BUTTON2_SCRNPOS_Y),
	BUTTON_SCREENPOS_3 = SCREEN_POS(BUTTON3_SCRNPOS_X, BUTTON3_SCRNPOS_Y),
	BUTTON_SCREENPOS_4 = SCREEN_POS(BUTTON4_SCRNPOS_X, BUTTON4_SCRNPOS_Y),
	BUTTON_SCREENPOS_5 = SCREEN_POS(BUTTON5_SCRNPOS_X, BUTTON5_SCRNPOS_Y),

	BUTTON_CHARNO_UNIT = (BUTTON_SCREEN_WIDTH*BUTTON_SCREEN_HEIGHT),
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A13_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];
};



//====================================================
// bg map
//====================================================
#define TEST_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdButtonPush( TCB_PTR tcb, void* wk_ptr );
static void CmdButtonRelease( TCB_PTR tcb, void* wk_ptr );
static void write_button_screen( VIEWWORK* vwk, u32 button_pos, BOOL enable, BOOL press );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A13_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();

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
void Poketch_A13_DeleteViewWork( VIEWWORK* wk )
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
	{ CMD_BUTTON_PUSH, CmdButtonPush, 0 },
	{ CMD_BUTTON_RELEASE, CmdButtonRelease, 0 },
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
void Poketch_A13_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A13_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A13_WaitViewCommandAll(VIEWWORK* wk)
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
	int i;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_traner_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_traner_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	for(i=0; i<BUTTON_MAX; i++)
	{
		write_button_screen(vwk, i, vpara->button_enable_flag[i], FALSE );
	}

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


static void CmdButtonPush( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );


	write_button_screen( vwk, vpara->button_id, vpara->button_enable_flag[vpara->button_id], TRUE );
	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}

static void CmdButtonRelease( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	write_button_screen( vwk, vpara->button_id, vpara->button_enable_flag[vpara->button_id], FALSE );
	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}



//------------------------------------------------------------------
/**
 * ボタンイメージスクリーンをBG system内部バッファに描画
 *
 * @param   vwk			
 * @param   button_pos	
 * @param   enable		
 * @param   press		
 *
 */
//------------------------------------------------------------------
static void write_button_screen( VIEWWORK* vwk, u32 button_pos, BOOL enable, BOOL press )
{
	static const u16 button_screen_pos[] = {
		BUTTON_SCREENPOS_0,
		BUTTON_SCREENPOS_1,
		BUTTON_SCREENPOS_2,
		BUTTON_SCREENPOS_3,
		BUTTON_SCREENPOS_4,
		BUTTON_SCREENPOS_5,
	};

	u16*  scrn;
	int  x, y, charno;

	scrn = GF_BGL_ScreenAdrsGet( vwk->bgl, USE_BG_FRAME );
	scrn += button_screen_pos[button_pos];

	charno = (enable)? (BUTTON_CHARNO_UNIT*2)*(button_pos+1) : 0;
	if( press )
	{
		charno += BUTTON_CHARNO_UNIT;
	}

	for(y=0; y<BUTTON_SCREEN_HEIGHT; y++)
	{
		for(x=0; x<BUTTON_SCREEN_WIDTH; x++)
		{
			scrn[x] = charno++;
		}
		scrn += 32;
	}



}
