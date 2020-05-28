//============================================================================================
/**
 * @file	poketch_a16v.c
 * @bfief	ポケッチ（アプリNo16:ルーレット）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a16.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define IMG_BG_FRAME	(GF_BGL_FRAME2_S)
#define WIN_BG_FRAME	(GF_BGL_FRAME3_S)

#define BMPWIN_OX		(2)
#define BMPWIN_OY		(2)
#define BMPWIN_WIDTH	(20)
#define BMPWIN_HEIGHT	(19)
#define BMPWIN_CGX_BYTESIZE (BMPWIN_WIDTH*BMPWIN_HEIGHT*0x20)

#define BASE_PALNO	(0)

#define WRITE_COLOR	(0x01)
#define ERASE_COLOR	(0x04)

// アクターＩＤ
enum {
	ACTID_ARROW,
	ACTID_BUTTON_START,
	ACTID_BUTTON_STOP,
	ACTID_BUTTON_CLEAR,

	ACTID_MAX,
};
// アクターアニメＩＤ
enum {
	ANM_ARROW,
	ANM_START_FREE,
	ANM_START_PUSH,
	ANM_STOP_FREE,
	ANM_STOP_PUSH,
	ANM_CLEAR_FREE,
	ANM_CLEAR_PUSH,
};
// アクターレイアウト
enum {
	ACTPOS_ARROW_X = 96,
	ACTPOS_ARROW_Y = 96,
	ACTPOS_START_X = BUTTON_START_X,
	ACTPOS_START_Y = BUTTON_START_Y,
	ACTPOS_STOP_X  = BUTTON_STOP_X,
	ACTPOS_STOP_Y  = BUTTON_STOP_Y,
	ACTPOS_CLEAR_X = BUTTON_CLEAR_X,
	ACTPOS_CLEAR_Y = BUTTON_CLEAR_Y,

};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A16_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];


	PACTSYS*         actsys;
	PACT*            actor[ ACTID_MAX ];
	PACT_CLANM_PACK  clpack;

	GF_BGL_BMPWIN    bmpwin;
	u32              bmpwin_chartop;

	BOOL             arrow_quit_flag;	// 強制停止
	BOOL             arrow_stop_flag;	// ストップボタンでの停止
	BOOL             arrow_max_speed_flag;	// 最高速に達した

	u16              arrow_rot;
	u16              arrow_rot_speed;
	u32              arrow_rand_wait;
};



//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void setup_bmpwin( VIEWWORK* wk, u32 charno );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdPixelUpdate( TCB_PTR tcb, void* wk_ptr );
static void CmdPixelSet( TCB_PTR tcb, void* wk_ptr );
static void CmdPixelSetEnd( TCB_PTR tcb, void* wk_ptr );
static void CmdUpdateButton( TCB_PTR tcb, void* wk_ptr );
static void CmdClearPixels( TCB_PTR tcb, void* wk_ptr );
static void CmdStartArrow( TCB_PTR tcb, void* wk_ptr );
static void CmdStopArrow( TCB_PTR tcb, void* wk_ptr );




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A16_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		wk->arrow_rot = 0;

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
void Poketch_A16_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors( wk );
		sys_FreeMemoryEz( wk );
	}
}

static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM  actparam[] = {
		{  {FX32INT(ACTPOS_ARROW_X), FX32INT(ACTPOS_ARROW_Y)}, ANM_ARROW,      PACT_FLIP_OFF, BGPRI2, 0, TRUE, },
		{  {FX32INT(ACTPOS_START_X), FX32INT(ACTPOS_START_Y)}, ANM_START_FREE, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_STOP_X),  FX32INT(ACTPOS_STOP_Y)},  ANM_STOP_PUSH,  PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
		{  {FX32INT(ACTPOS_CLEAR_X), FX32INT(ACTPOS_CLEAR_Y)}, ANM_CLEAR_FREE, PACT_FLIP_OFF, BGPRI2, 0, FALSE, },
	};

	int i;

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_rlt_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_rlt_lz_ncer, NARC_poketch_rlt_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	for(i=0; i<ACTID_MAX; i++)
	{
		wk->actor[i] = PACT_Add( wk->actsys, &actparam[i], &wk->clpack );
	}
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
	{ CMD_PIXEL_UPDATE,  CmdPixelUpdate, 0 },
	{ CMD_PIXEL_SET,     CmdPixelSet, 0 },
	{ CMD_PIXEL_SET_END, CmdPixelSetEnd, 0 },

	{ CMD_UPDATE_BUTTON, CmdUpdateButton, 0 },
	{ CMD_CLEAR_PIXELS,  CmdClearPixels, 0 },
	{ CMD_START_ARROW,   CmdStartArrow, 0 },
	{ CMD_STOP_ARROW,    CmdStopArrow, 0 },
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
void Poketch_A16_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A16_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A16_WaitViewCommandAll(VIEWWORK* wk)
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
	u32 charno;

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, IMG_BG_FRAME, &img_bg_header, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, WIN_BG_FRAME, &win_bg_header, GF_BGL_MODE_TEXT );

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

	charno = ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_rlt_lz_ncgr, vwk->bgl, IMG_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID );
	charno /= 0x20;
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_rlt_lz_nscr, vwk->bgl, IMG_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID );
	PoketchView_SetBaseColorPalette(BASE_PALNO, 0);

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));

	setup_bmpwin( vwk, charno );

	GF_BGL_LoadScreenReq( vwk->bgl, WIN_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);

	DeleteCommand( wk_ptr );

	GF_ASSERT(sys_CheckHeapSafe(HEAPID_POKETCH_APP));
}
static void setup_bmpwin( VIEWWORK* wk, u32 charno )
{
	BMPWIN_DAT  windat = {
		WIN_BG_FRAME,
		BMPWIN_OX, BMPWIN_OY, BMPWIN_WIDTH, BMPWIN_HEIGHT,
		BASE_PALNO, 0,
	};

	wk->bmpwin_chartop = charno;
	windat.chrnum = charno;

	GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin, &windat );

	if( PoketchWork_LoadFast( wk->vpara->appNumber, wk->bmpwin.chrbuf, BMPWIN_CGX_BYTESIZE ) == FALSE )
	{
		GF_BGL_BmpWinDataFill( &wk->bmpwin, ERASE_COLOR );
	}
	GF_BGL_BmpWinMakeScrn( &wk->bmpwin );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin );

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

	switch(PoketchViewTool_GetSeq(wk_ptr)){
	case 0:
		vwk->arrow_quit_flag = TRUE;
		PoketchViewTool_FwdSeq(wk_ptr);
		break;
	case 1:
		PoketchWork_SaveFast( vwk->vpara->appNumber, vwk->bmpwin.chrbuf, BMPWIN_CGX_BYTESIZE );
		GF_BGL_BmpWinDel( &vwk->bmpwin );
		GF_BGL_BGControlExit( vwk->bgl, IMG_BG_FRAME );
		GF_BGL_BGControlExit( vwk->bgl, WIN_BG_FRAME );
		DeleteCommand( wk_ptr );
	}
}





//------------------------------------------------------------------
/**
 * コマンド：ピクセル状態更新
 *
 * @param   tcb		
 * @param   wk_adrs		
 */
//------------------------------------------------------------------
static void CmdPixelUpdate( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;
	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );
	DeleteCommand( wk_ptr );

}
static void CmdPixelSet( TCB_PTR tcb, void* wk_ptr )
{
	s32 x, y, col, charno;

	VIEWWORK* vwk;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	x = vwk->vpara->pixel_update_x * 2;
	y = vwk->vpara->pixel_update_y * 2;
	charno = ((y >> 3) * BMPWIN_WIDTH) + (x >> 3);
	GF_BGL_BmpWinFill( &vwk->bmpwin, WRITE_COLOR, x, y, 2, 2 );
	GXS_LoadBG3Char( (u8*)(vwk->bmpwin.chrbuf) + (charno*0x20), (vwk->bmpwin_chartop+charno)*0x20, 0x20 ); 

	DeleteCommand( wk_ptr );

}
static void CmdPixelSetEnd( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk;
	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );
	DeleteCommand( wk_ptr );
}



//------------------------------------------------------------------
/**
 * コマンド：ボタン状態更新
 *
 * @param   tcb		
 * @param   wk_adrs		
 */
//------------------------------------------------------------------
static void CmdUpdateButton( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	PACT_ChangeAnmSeq( vwk->actor[ACTID_BUTTON_START], (vpara->start_button)? ANM_START_PUSH : ANM_START_FREE );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_BUTTON_STOP],  (vpara->stop_button)?  ANM_STOP_PUSH  : ANM_STOP_FREE  );
	PACT_ChangeAnmSeq( vwk->actor[ACTID_BUTTON_CLEAR], (vpara->clear_button)? ANM_CLEAR_PUSH : ANM_CLEAR_FREE );

	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * コマンド：描画領域クリア
 *
 * @param   tcb		
 * @param   wk_adrs		
 */
//------------------------------------------------------------------
static void CmdClearPixels( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BmpWinDataFill( &vwk->bmpwin, ERASE_COLOR );
	GF_BGL_BmpWinCgxOn( &vwk->bmpwin );

	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * コマンド：矢印回転開始
 *
 * @param   tcb		
 * @param   wk_adrs		
 */
//------------------------------------------------------------------
static void CmdStartArrow( TCB_PTR tcb, void* wk_ptr )
{
	enum {
		ARROW_SPEED_MAX = 0x3000,
		ARROW_SPEED_STOP_MAX = 0x1a00,
		ARROW_SPEED_AC = 0x150,
		ARROW_SPEED_DOWN_AC = 0x50,
	};

	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );
	u32 seq;

	seq = PoketchViewTool_GetSeq(wk_ptr);

	if( seq != 0 && vwk->arrow_quit_flag )
	{
		DeleteCommand( wk_ptr );
		return;
	}

	switch( seq ){
	case 0:
		vwk->arrow_rot += ARROW_SPEED_AC;
		vwk->arrow_rot_speed = ARROW_SPEED_AC;
		PACT_SetRotate( vwk->actor[ACTID_ARROW], vwk->arrow_rot );
		vwk->arrow_max_speed_flag = FALSE;
		vwk->arrow_stop_flag = FALSE;
		vwk->arrow_quit_flag = FALSE;
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		vwk->arrow_rot += vwk->arrow_rot_speed;
		PACT_SetRotate( vwk->actor[ACTID_ARROW], vwk->arrow_rot );

		vwk->arrow_rot_speed += ARROW_SPEED_AC;
		if( vwk->arrow_rot_speed >= ARROW_SPEED_MAX )
		{
			vwk->arrow_rot_speed = ARROW_SPEED_MAX;
			vwk->arrow_max_speed_flag = TRUE;
			PoketchViewTool_FwdSeq(wk_ptr);
		}
		break;

	case 2:
		vwk->arrow_rot += vwk->arrow_rot_speed;
		PACT_SetRotate( vwk->actor[ACTID_ARROW], vwk->arrow_rot );
		if( vwk->arrow_stop_flag )
		{
			vwk->arrow_rand_wait = gf_mtRand() & 7;	// 適当に7フレームの範囲くらいでウェイトを入れる
			if( vwk->arrow_rot_speed > ARROW_SPEED_STOP_MAX )
			{
				vwk->arrow_rot_speed = ARROW_SPEED_STOP_MAX;
			}
			PoketchViewTool_FwdSeq(wk_ptr);
		}
		break;

	case 3:
		vwk->arrow_rot += vwk->arrow_rot_speed;
		PACT_SetRotate( vwk->actor[ACTID_ARROW], vwk->arrow_rot );
		if( vwk->arrow_rand_wait == 0 )
		{
			vwk->arrow_rand_wait--;
		}
		else
		{
			PoketchViewTool_FwdSeq(wk_ptr);
		}
		break;

	case 4:
		if( vwk->arrow_rot_speed > ARROW_SPEED_DOWN_AC )
		{
			vwk->arrow_rot_speed -= ARROW_SPEED_DOWN_AC;
			vwk->arrow_rot += vwk->arrow_rot_speed;
			PACT_SetRotate( vwk->actor[ACTID_ARROW], vwk->arrow_rot );
		}
		else
		{
			vwk->arrow_rot_speed = 0;
			DeleteCommand( wk_ptr );
		}
		break;
	}

}


//------------------------------------------------------------------
/**
 * コマンド：矢印回転徐々に停止
 *
 * @param   tcb		
 * @param   wk_adrs		
 */
//------------------------------------------------------------------
static void CmdStopArrow( TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq(wk_ptr) ){
	case 0:
		vwk->arrow_stop_flag = TRUE;
		PoketchViewTool_FwdSeq(wk_ptr);
		break;

	case 1:
		if(Poketch_A16_WaitViewCommand(vwk, CMD_START_ARROW))
		{
			PoketchSePlay(POKETCH_SE_ROULETTE_STOP);
			DeleteCommand( wk_ptr );
		}
		break;
	}
}



//------------------------------------------------------------------
/**
 * 矢印回転後、最大スピードに達するのを待つ
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL Poketch_A16_WaitArrowMaxSpeed( VIEWWORK* wk )
{
	return wk->arrow_max_speed_flag;
}
