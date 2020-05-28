//============================================================================================
/**
 * @file	poketch_a00v.c
 * @bfief	ポケッチ（アプリNo00 = デジタル時計）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a00.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

#define NUM_SCR_SINGLE_WIDTH	(4)		///< 数字１個の横ｷｬﾗ数

#define NUM_SCR_WIDTH	(NUM_SCR_SINGLE_WIDTH*10)
#define NUM_SCR_HEIGHT	(9)
#define NUM_SCR_SIZE	(NUM_SCR_WIDTH*NUM_SCR_HEIGHT)

#define NUM_SCR_WRITE_YPOS			(7)
#define NUM_SCR_HOUR10_WRITE_XPOS	(3)
#define NUM_SCR_HOUR1_WRITE_XPOS	(NUM_SCR_HOUR10_WRITE_XPOS+(NUM_SCR_SINGLE_WIDTH+1))

#define NUM_SCR_MIN10_WRITE_XPOS	(15)
#define NUM_SCR_MIN1_WRITE_XPOS		(NUM_SCR_MIN10_WRITE_XPOS+(NUM_SCR_SINGLE_WIDTH+1))


//==============================================================
// Work
//==============================================================
struct _POKETCH_A00_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	u16					num_scrn[NUM_SCR_SIZE];
};



//====================================================
// bg map
//====================================================
#define USE_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void NumScreenDataCopy( const u16* src, u16* dst );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdTimeUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdBackLightUpdate(TCB_PTR tcb, void* wk_adrs );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void UpdateTimeScreen( VIEWWORK* vwk );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A00_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		NNSG2dScreenData* scrnDat;
		void* buf;

		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();


		buf = ArcUtil_ScrnDataGet( ARC_POKETCH_IMG, NARC_poketch_dwatch_num_nscr, TRUE, &scrnDat, HEAPID_POKETCH_APP );
		if( buf == NULL)
		{
			sys_FreeMemoryEz( wk );
			return FALSE;
		}
		NumScreenDataCopy( (const u16*)(scrnDat->rawData), wk->num_scrn );
		sys_FreeMemoryEz( buf );

		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 数字スクリーンデータを整形してコピーする
 * ※32キャラで折り返されてしまうため、そのままでは使いづらい。
 *
 * @param   src		g2dcvtrが吐きだしたスクリーンの先頭データ
 * @param   dst		コピー先バッファ
 *
 */
//------------------------------------------------------------------
static void NumScreenDataCopy( const u16* src, u16* dst )
{
	enum {
		NEXTBLOCK_OFS = 32*NUM_SCR_HEIGHT,
		NEXTBLOCK_TRANS_SIZE = (NUM_SCR_WIDTH - 32),
	};

	int i, ofs;

	ofs = NEXTBLOCK_OFS;
	for(i = 0; i < NUM_SCR_HEIGHT; i++)
	{
		MI_CpuCopy16( src, dst, 32*2 );
		MI_CpuCopy16( &src[ofs], &dst[32], NEXTBLOCK_TRANS_SIZE*2 );
		src += 32;
		dst += NUM_SCR_WIDTH;
		ofs = (ofs - 32 + NEXTBLOCK_TRANS_SIZE);
	}
}
//------------------------------------------------------------------
/**
 * ワーク削除
 *
 * @param   wk		確保したワークアドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A00_DeleteViewWork( VIEWWORK* wk )
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
	{ CMD_INIT,   CmdInit,   0 },
	{ CMD_TIME_UPDATE, CmdTimeUpdate, 0 },
	{ CMD_BACKLIGHT_UPDATE, CmdBackLightUpdate, 0 },
	{ CMD_QUIT,   CmdQuit,   0 },
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
void Poketch_A00_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A00_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A00_WaitViewCommandAll(VIEWWORK* wk)
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

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_dwatch_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
//	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, 0, 0, 0, 32, 24, USE_PALNO );
//void ArcUtil_ScrnSet(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_dwatch_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette( 0, 0 );

	UpdateTimeScreen( vwk );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);

	DeleteCommand( wk_ptr );

}
//------------------------------------------------------------------
/**
 * コマンド：時間更新
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdTimeUpdate( TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	UpdateTimeScreen( vwk );
	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：バックライト更新
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdBackLightUpdate(TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	if( vwk->vpara->backlight )
	{
		PoketchView_SetHighColorPalette(0,0);
	}
	else
	{
		PoketchView_SetBaseColorPalette(0,0);
	}
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
 * 時刻スクリーンを更新
 *
 * @param   vwk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void UpdateTimeScreen( VIEWWORK* vwk )
{
	u32 dig10, dig1;

	CP_SetDiv32_32( vwk->vpara->time.hour, 10 );
	dig10 = CP_GetDivResult32();
	dig1 = CP_GetDivRemainder32();

	GF_BGL_ScrWriteExpand( vwk->bgl, USE_BG_FRAME, NUM_SCR_HOUR10_WRITE_XPOS, NUM_SCR_WRITE_YPOS,
			NUM_SCR_SINGLE_WIDTH, NUM_SCR_HEIGHT, vwk->num_scrn, NUM_SCR_SINGLE_WIDTH*dig10, 0,
			NUM_SCR_WIDTH, NUM_SCR_HEIGHT );

	GF_BGL_ScrWriteExpand( vwk->bgl, USE_BG_FRAME, NUM_SCR_HOUR1_WRITE_XPOS, NUM_SCR_WRITE_YPOS,
			NUM_SCR_SINGLE_WIDTH, NUM_SCR_HEIGHT, vwk->num_scrn, NUM_SCR_SINGLE_WIDTH*dig1, 0,
			NUM_SCR_WIDTH, NUM_SCR_HEIGHT );


	CP_SetDiv32_32( vwk->vpara->time.minute, 10 );
	dig10 = CP_GetDivResult32();
	dig1 = CP_GetDivRemainder32();

	GF_BGL_ScrWriteExpand( vwk->bgl, USE_BG_FRAME, NUM_SCR_MIN10_WRITE_XPOS, NUM_SCR_WRITE_YPOS,
			NUM_SCR_SINGLE_WIDTH, NUM_SCR_HEIGHT, vwk->num_scrn, NUM_SCR_SINGLE_WIDTH*dig10, 0,
			NUM_SCR_WIDTH, NUM_SCR_HEIGHT );

	GF_BGL_ScrWriteExpand( vwk->bgl, USE_BG_FRAME, NUM_SCR_MIN1_WRITE_XPOS, NUM_SCR_WRITE_YPOS,
			NUM_SCR_SINGLE_WIDTH, NUM_SCR_HEIGHT, vwk->num_scrn, NUM_SCR_SINGLE_WIDTH*dig1, 0,
			NUM_SCR_WIDTH, NUM_SCR_HEIGHT );
}


