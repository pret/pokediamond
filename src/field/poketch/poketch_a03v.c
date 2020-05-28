//============================================================================================
/**
 * @file	poketch_a03v.c
 * @bfief	ポケッチ（アプリNo03：メモ帳）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "system\snd_tool.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a03.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(16)
#define IMG_BG_FRAME	(GF_BGL_FRAME2_S)
#define WIN_BG_FRAME	(GF_BGL_FRAME3_S)

#define BMPWIN_CHARTOP	(12)
#define BMPWIN_OX		(2)
#define BMPWIN_OY		(2)
#define BMPWIN_WIDTH	(20)
#define BMPWIN_HEIGHT	(19)

#define BMPWIN_CGX_BYTESIZE (BMPWIN_WIDTH*BMPWIN_HEIGHT*0x20)

#define BASE_PALNO	(0)

#define WRITE_COLOR	(0x01)
#define ERASE_COLOR	(0x04)

#define ERASE_RANGE	(8)		// 消しゴムモード時の有効ドット範囲

//====================================================
// ポケッチアクター関連定数
//====================================================
enum {
	ACT_ERASER_BUTTON,
	ACT_PEN_BUTTON,
	ACT_MAX,
};

enum {
	ANM_ERASER_OFF,
	ANM_ERASER_ON,
	ANM_PEN_OFF,
	ANM_PEN_ON,
};

enum {
	ACTPOS_ERASER_X = 192,
	ACTPOS_ERASER_Y = 56,
	ACTPOS_PEN_X = 192,
	ACTPOS_PEN_Y = 136,
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A03_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;

	PACT_CLANM_PACK    button_clpack;
	PACT*              act[ACT_MAX];

	GF_BGL_BMPWIN*     bmpwin;
};


//==============================================================
// Prototype
//==============================================================
static BOOL BmpWinSetup( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdButtonUpdate( TCB_PTR tcb, void* wk_ptr );
static void CmdPixelUpdate( TCB_PTR tcb, void* wk_ptr );
static void CmdPixelSet( TCB_PTR tcb, void* wk_ptr );
static void CmdPixelSetEnd( TCB_PTR tcb, void* wk_ptr );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void SetupObj( VIEWWORK *vwk );
static void DeleteAllObj( VIEWWORK* vwk );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A03_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		GF_ASSERT( sys_CheckHeapSafe( HEAPID_POKETCH_MAIN ) );
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		GF_ASSERT( sys_CheckHeapSafe( HEAPID_POKETCH_MAIN ) );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		GF_ASSERT( sys_CheckHeapSafe( HEAPID_POKETCH_MAIN ) );
		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}

static BOOL BmpWinSetup( VIEWWORK* wk )
{
	static const BMPWIN_DAT  windat = {
		WIN_BG_FRAME,
		BMPWIN_OX, BMPWIN_OY, BMPWIN_WIDTH, BMPWIN_HEIGHT,
		BASE_PALNO, BMPWIN_CHARTOP,
	};

	wk->bmpwin = GF_BGL_BmpWinAllocGet( HEAPID_POKETCH_APP, 1 );
	if( wk->bmpwin )
	{
		GF_BGL_BmpWinAddEx( wk->bgl, wk->bmpwin, &windat );

		if( PoketchWork_LoadFast( wk->vpara->appNumber, wk->bmpwin->chrbuf, BMPWIN_CGX_BYTESIZE ) == FALSE)
		{
			GF_BGL_BmpWinDataFill( wk->bmpwin, ERASE_COLOR );
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
void Poketch_A03_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		GF_ASSERT( sys_CheckHeapSafe( HEAPID_POKETCH_MAIN ) );
		if( wk->bmpwin )
		{
			PoketchWork_SaveFast( wk->vpara->appNumber, wk->bmpwin->chrbuf, BMPWIN_CGX_BYTESIZE );
			GF_BGL_BmpWinDel( wk->bmpwin );
			sys_FreeMemoryEz( wk->bmpwin );
		}
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
	{ CMD_BUTTON_UPDATE, CmdButtonUpdate, 0 },
	{ CMD_PIXEL_UPDATE, CmdPixelUpdate, 0 },
	{ CMD_PIXEL_SET, CmdPixelSet, 0 },
	{ CMD_PIXEL_SET_END, CmdPixelSetEnd, 0 },
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
void Poketch_A03_SetViewCommand(VIEWWORK* wk, u32 cmd)
{
//	extern void PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
	PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
//	PoketchViewTool_SetCommandVintr(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
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
BOOL Poketch_A03_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A03_WaitViewCommandAll(VIEWWORK* wk)
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
	static const GF_BGL_BGCNT_HEADER img_bg_header = {
		0, 0, 0, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER win_bg_header = {
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, IMG_BG_FRAME, &img_bg_header, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, WIN_BG_FRAME, &win_bg_header, GF_BGL_MODE_TEXT );

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_memo_ncgr, vwk->bgl, IMG_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_memo_nscr, vwk->bgl, IMG_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID );
	PoketchView_SetBaseColorPalette(BASE_PALNO, 0);

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

	BmpWinSetup( vwk );
	GF_BGL_BmpWinOn( vwk->bmpwin );

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

	SetupObj( vwk );

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

//	GF_BGL_LoadScreenReq( vwk->bgl, IMG_BG_FRAME );
	GF_BGL_LoadScreenReq( vwk->bgl, WIN_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);

	DeleteCommand( wk_ptr );

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));
}
//------------------------------------------------------------------
/**
 * コマンド：ボタン状態更新
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdButtonUpdate( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	if( vwk->vpara->touch_mode == TOUCHMODE_PEN )
	{
		PACT_ChangeAnmSeq( vwk->act[ACT_ERASER_BUTTON], ANM_ERASER_OFF );
		PACT_ChangeAnmSeq( vwk->act[ACT_PEN_BUTTON], ANM_PEN_ON );
	}
	else
	{
		PACT_ChangeAnmSeq( vwk->act[ACT_ERASER_BUTTON], ANM_ERASER_ON );
		PACT_ChangeAnmSeq( vwk->act[ACT_PEN_BUTTON], ANM_PEN_OFF );
	}

	PoketchSePlay( POKETCH_SE_MEMO_BUTTON );

	DeleteCommand( wk_ptr );
}
//------------------------------------------------------------------
/**
 * コマンド：ピクセル状態更新
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdPixelUpdate( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;
	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	GF_BGL_BmpWinCgxOn( vwk->bmpwin );
	DeleteCommand( wk_ptr );

}
static void CmdPixelSet( TCB_PTR tcb, void* wk_ptr )
{
	s32 x, y, col, charno;

	VIEWWORK* vwk;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	if( vwk->vpara->touch_mode == TOUCHMODE_ERASER )
	{
		// 消しゴムモードは広く
		int  rangeX, rangeY, charsizeX, charsizeY;

		rangeX = rangeY = ERASE_RANGE;
		x = (vwk->vpara->pixel_update_x * 2) - (ERASE_RANGE/2);
		y = (vwk->vpara->pixel_update_y * 2) - (ERASE_RANGE/2);

		// 範囲がマイナスになるなら補正（オーバーな時はBitmapWindowのクリップに任せる）
		if( x < 0 )
		{
			rangeX += x;
			x = 0;
		}
		if( y < 0 )
		{
			rangeY += y;
			y = 0;
		}

		GF_BGL_BmpWinFill( vwk->bmpwin, ERASE_COLOR, x, y, rangeX, rangeY );
		charno = ((y >> 3) * BMPWIN_WIDTH) + (x >> 3);
		charsizeX = (((x+rangeX-1) >> 3) - (x >> 3)) + 1;
		charsizeY = (((y+rangeY-1) >> 3) - (y >> 3)) + 1;

		while( charsizeY-- )
		{
			GXS_LoadBG3Char( (u8*)(vwk->bmpwin->chrbuf) + (charno*0x20), (BMPWIN_CHARTOP+charno)*0x20, charsizeX*0x20 ); 
			charno += BMPWIN_WIDTH;
		}

	}
	else
	{
		x = vwk->vpara->pixel_update_x * 2;
		y = vwk->vpara->pixel_update_y * 2;
		charno = ((y >> 3) * BMPWIN_WIDTH) + (x >> 3);
		GF_BGL_BmpWinFill( vwk->bmpwin, WRITE_COLOR, x, y, 2, 2 );
		GXS_LoadBG3Char( (u8*)(vwk->bmpwin->chrbuf) + (charno*0x20), (BMPWIN_CHARTOP+charno)*0x20, 0x20 ); 
	}

//	GF_BGL_BmpWinCgxOn( vwk->bmpwin );
//	GXS_LoadBG3Char( (u8*)(vwk->bmpwin->chrbuf) + (charno*0x20), (BMPWIN_CHARTOP+charno)*0x20, 0x20 ); 

	DeleteCommand( wk_ptr );

}
static void CmdPixelSetEnd( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;
	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	GF_BGL_BmpWinCgxOn( vwk->bmpwin );
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

	DeleteAllObj( vwk );
	GF_BGL_BGControlExit( vwk->bgl, IMG_BG_FRAME );
	GF_BGL_BGControlExit( vwk->bgl, WIN_BG_FRAME );
	DeleteCommand( wk_ptr );
}





//------------------------------------------------------------------
/**
 * OBJ初期化
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
static void SetupObj( VIEWWORK *vwk )
{
	static const PACT_ADD_PARAM param[] = {
		{
			{  FX32INT(ACTPOS_ERASER_X), FX32INT(ACTPOS_ERASER_Y) },
			ANM_ERASER_OFF, 0, BGPRI2, 0, FALSE,
		},{
			{  FX32INT(ACTPOS_PEN_X), FX32INT(ACTPOS_PEN_Y) },
			ANM_PEN_ON, 0, BGPRI2, 0, FALSE,
		},
	};

	ArcUtil_ObjCharSet( ARC_POKETCH_IMG, NARC_poketch_memo_obj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID );

	if( PACT_TOOL_LoadCellDatas( &vwk->button_clpack, ARC_POKETCH_IMG,
			NARC_poketch_memo_button_ncer, NARC_poketch_memo_button_nanr, POKETCH_APP_VIEW_HEAPID )
	)
	{
		int i;
		for(i = 0; i < ACT_MAX; i++)
		{
			vwk->act[i] = PACT_Add( vwk->actsys, &param[i], &vwk->button_clpack );
		}
	}

}
//------------------------------------------------------------------
/**
 * OBJ全削除
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void DeleteAllObj( VIEWWORK* vwk )
{
	u32 i;
	for(i = 0; i < ACT_MAX; i++)
	{
		PACT_Del( vwk->actsys, vwk->act[i] );
	}
	PACT_TOOL_UnloadCellDatas( &vwk->button_clpack );
}

