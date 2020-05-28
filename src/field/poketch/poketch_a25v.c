//============================================================================================
/**
 * @file	poketch_a25v.c
 * @bfief	ポケッチ（アプリNo25：カレンダー）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a25.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)

enum {
	FRM_NUMBER     = GF_BGL_FRAME2_S,
	FRM_BACKGROUND = GF_BGL_FRAME3_S,
};

enum {
	CHARCODE_CLEAR		= 0x82,
	CHARCODE_NORMAL_BG	= 0x83,
	CHARCODE_MARK_BG	= 0x8f,

	CGX_WIDTH = 12,
};



//==============================================================
// Work
//==============================================================
struct _POKETCH_A25_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_square;
	PACT_CLANM_PACK    clpack;

};


//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void set_square_actor_pos( PACT* act, u32 pos );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdUpdate( TCB_PTR tcb, void* wk_ptr );
static void setup_bg_screen( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void fill_bg_screen( GF_BGL_INI* bgl, u16 charcode, u32 pos );
static void setup_number_screen( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void write_month_screen( GF_BGL_INI* bgl, u32 month );
static void write_day_screen( GF_BGL_INI* bgl, u32 day, u32 pos );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A25_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
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
void Poketch_A25_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors( wk );
		sys_FreeMemoryEz( wk );
	}
}


static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM  actparam = {
		{  FX32INT(0), FX32INT(0) },
		0, 0, BGPRI2, 0, FALSE,
	};

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_calendar_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_calendar_lz_ncer, NARC_poketch_calendar_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	wk->act_square = PACT_Add( wk->actsys, &actparam, &wk->clpack );
	set_square_actor_pos( wk->act_square, vpara->day_param[vpara->today-1].pos );
}

static void set_square_actor_pos( PACT* act, u32 pos )
{
	fx32 x, y;

	x = (((TOUCH_SCRN_X_ORG + TOUCH_SCRN_X_DIFF * (pos % 7)) + 1) * 8) << FX32_SHIFT;
	y = (((TOUCH_SCRN_Y_ORG + TOUCH_SCRN_Y_DIFF * (pos / 7)) + 1) * 8) << FX32_SHIFT;

	PACT_SetPos( act, x, y );

}

static void cleanup_actors( VIEWWORK* wk )
{
	PACT_Del( wk->actsys, wk->act_square );
	PACT_TOOL_UnloadCellDatas( &(wk->clpack) );
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
void Poketch_A25_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A25_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A25_WaitViewCommandAll(VIEWWORK* wk)
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
	static const GF_BGL_BGCNT_HEADER header_num = {
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header_back = {
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;
	const VIEWPARAM* vpara;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, FRM_NUMBER, &header_num, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, FRM_BACKGROUND, &header_back,  GF_BGL_MODE_TEXT );

	setup_bg_screen( vwk, vpara );
	setup_number_screen( vwk, vpara );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_calendar_lz_ncgr, vwk->bgl, FRM_BACKGROUND, 0, 0, TRUE, HEAPID_POKETCH_APP );


	PoketchView_SetBaseColorPalette(0,0);

	GF_BGL_LoadScreenReq( vwk->bgl, FRM_NUMBER );
	GF_BGL_LoadScreenReq( vwk->bgl, FRM_BACKGROUND );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3);
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

	GF_BGL_BGControlExit( vwk->bgl, FRM_NUMBER );
	GF_BGL_BGControlExit( vwk->bgl, FRM_BACKGROUND );
	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * コマンド：マーキング更新
 *
 * @param   tcb		
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
static void CmdUpdate( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;
	const VIEWPARAM* vpara;
	u32 charcode;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	charcode = (vpara->day_param[vpara->update_day].mark)? CHARCODE_MARK_BG : CHARCODE_NORMAL_BG;
	fill_bg_screen( vwk->bgl, charcode, vpara->day_param[vpara->update_day].pos );
	GF_BGL_LoadScreenReq( vwk->bgl, FRM_BACKGROUND );

	DeleteCommand( wk_ptr );
}



//------------------------------------------------------------------
/**
 * 背景スクリーン初期状態セットアップ
 *
 * @param   vwk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void setup_bg_screen( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	u32 i;

	ArcUtil_ScrnSet(ARC_POKETCH_IMG, NARC_poketch_calendar_lz_nscr, vwk->bgl, FRM_BACKGROUND, 0, 0, TRUE, HEAPID_POKETCH_APP );

	for(i=0; i<vpara->last_day; i++)
	{
		if( vpara->day_param[i].mark )
		{
			fill_bg_screen( vwk->bgl, CHARCODE_MARK_BG, vpara->day_param[i].pos );
		}
	}
}
//------------------------------------------------------------------
/**
 * 背景スクリーンpos指定書き込み
 *
 * @param   bgl			
 * @param   charcode		
 * @param   pos			
 *
 */
//------------------------------------------------------------------
static void fill_bg_screen( GF_BGL_INI* bgl, u16 charcode, u32 pos )
{
	u32 x, y;

	x = TOUCH_SCRN_X_ORG + TOUCH_SCRN_X_DIFF * (pos % 7);
	y = TOUCH_SCRN_Y_ORG + TOUCH_SCRN_Y_DIFF * (pos / 7);

	GF_BGL_ScrFill( bgl, FRM_BACKGROUND, charcode, x, y, TOUCH_SCRN_X_RANGE, TOUCH_SCRN_Y_RANGE, 0 );
}




//------------------------------------------------------------------
/**
 * 数字スクリーン初期状態セットアップ
 *
 * @param   vwk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void setup_number_screen( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	u32 i;

	GF_BGL_ScrFill( vwk->bgl, FRM_NUMBER, CHARCODE_CLEAR, 0, 0, 32, 32, 0 );

	write_month_screen( vwk->bgl, vpara->month );

	for(i=0; i<vpara->last_day; i++)
	{
		write_day_screen( vwk->bgl, i+1, vpara->day_param[i].pos );
	}
}
//------------------------------------------------------------------
/**
 * 現在月データを数字スクリーンバッファに書き込み
 *
 * @param   bgl		
 * @param   month		
 *
 */
//------------------------------------------------------------------
static void write_month_screen( GF_BGL_INI* bgl, u32 month )
{
	enum {
		DST_SCRN_XPOS = 12,
		DST_SCRN_YPOS = 2,
	};
	static const u16 TopCharCode[12] = {
		0x00, 0x04, 0x08,
		0x18, 0x1c, 0x20,
		0x30, 0x34, 0x38,
		0x48, 0x4c, 0x50,
	};

	u32 charcode = TopCharCode[month-1];
	int x, y;

	for(y=0; y<2; y++)
	{
		for(x=0; x<4; x++)
		{
			GF_BGL_ScrFill( bgl, FRM_NUMBER, charcode+x, DST_SCRN_XPOS+x, DST_SCRN_YPOS+y, 1, 1, 0 );
		}
		charcode += CGX_WIDTH;
	}
}

//------------------------------------------------------------------
/**
 * 日付データを数字スクリーンバッファに書き込み
 *
 * @param   bgl		
 * @param   day		
 * @param   pos		
 *
 */
//------------------------------------------------------------------
static void write_day_screen( GF_BGL_INI* bgl, u32 day, u32 pos )
{
	static const u16 CharCode[2][10] = {
		{ 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69 },
		{ 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81 },
	};

	u32 x, y, d10, d1;
	int sunday;

	x = TOUCH_SCRN_X_ORG + TOUCH_SCRN_X_DIFF * (pos % 7);
	y = TOUCH_SCRN_Y_ORG + TOUCH_SCRN_Y_DIFF * (pos / 7);
	sunday = ((pos%7) == 0);

	d10 = day / 10;
	d1 = day % 10;

	if( d10 )
	{
		GF_BGL_ScrFill( bgl, FRM_NUMBER, CharCode[sunday][d10], x, y, 1, 1, 0 );
		GF_BGL_ScrFill( bgl, FRM_NUMBER, CharCode[sunday][d10]+CGX_WIDTH, x, y+1, 1, 1, 0 );
	}

	GF_BGL_ScrFill( bgl, FRM_NUMBER, CharCode[sunday][d1], x+1, y, 1, 1, 0 );
	GF_BGL_ScrFill( bgl, FRM_NUMBER, CharCode[sunday][d1]+CGX_WIDTH, x+1, y+1, 1, 1, 0 );


}
