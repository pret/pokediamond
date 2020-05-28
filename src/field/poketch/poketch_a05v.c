//============================================================================================
/**
 * @file	poketch_a05v.c
 * @bfief	ポケッチ（アプリNo05）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a05.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

//==============================================================
// Work
//==============================================================
struct _POKETCH_A05_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];
};



//====================================================
// bg map
//====================================================
#define USE_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CgxDataSetup(GF_BGL_INI* bgl);
static void CmdFieldUpdate(TCB_PTR tcb, void* wk_adrs);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void ScreenUpdate(GF_BGL_INI* bgl, const VIEWPARAM* vpara );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A05_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
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
void Poketch_A05_DeleteViewWork( VIEWWORK* wk )
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
	{ CMD_FIELD_UPDATE, CmdFieldUpdate, 0 },
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
void Poketch_A05_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A05_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A05_WaitViewCommandAll(VIEWWORK* wk)
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

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	CgxDataSetup(vwk->bgl);
	ScreenUpdate(vwk->bgl, vwk->vpara);
	PoketchView_SetBaseColorPalette(USE_PALNO,0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);

	DeleteCommand( wk_ptr );

}
//------------------------------------------------------------------
/**
 * CGXデータ作成＆VRAM転送
 *
 * @param   bgl		
 *
 */
//------------------------------------------------------------------
static void CgxDataSetup(GF_BGL_INI* bgl)
{
	u8* buf = sys_AllocMemory(HEAPID_POKETCH_APP, 0x20*16);
	if(buf)
	{
		int i;
		u32 fillDat;
		for(i=0; i<16; i++)
		{
			fillDat = (i<<28)|(i<<24)|(i<<20)|(i<<16)|(i<<12)|(i<<8)|(i<<4)|i;
			MI_CpuFillFast( buf+i*0x20, fillDat, 0x20 );
		}
		GF_BGL_LoadCharacter(bgl, USE_BG_FRAME, buf, 0x20*16, 0);
		sys_FreeMemoryEz(buf);
	}
}


//------------------------------------------------------------------
/**
 * コマンド：ドット更新
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdFieldUpdate(TCB_PTR tcb, void* wk_adrs)
{
	VIEWWORK* vwk;

	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	ScreenUpdate(vwk->bgl, vwk->vpara);
	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
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





//------------------------------------------------------------------
/**
 * 描画パラメータに合わせてスクリーンデータ更新（転送しない）
 *
 * @param   bgl		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void ScreenUpdate(GF_BGL_INI* bgl, const VIEWPARAM* vpara )
{
	static const u8 palno[] = {
		POKETCH_DEFAULTCOLOR_L1_POS, POKETCH_DEFAULTCOLOR_L2_POS, POKETCH_DEFAULTCOLOR_L3_POS, POKETCH_DEFAULTCOLOR_L4_POS
	};
	int x, y, p;
	u16* screen = GF_BGL_ScreenAdrsGet(bgl, USE_BG_FRAME);

	screen += ((FIELD_YORG_CHAR*32)+FIELD_XORG_CHAR);
	for(y=0; y<FIELD_HEIGHT; y++)
	{
		for(x=0; x<FIELD_WIDTH; x++)
		{
			screen[x] = (USE_PALNO<<12)| palno[ (vpara->dot[y][x]-1) ];
		}
		screen += 32;
	}
}



