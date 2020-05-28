//============================================================================================
/**
 * @file	pmsiv_button.c
 * @bfief	簡易会話入力画面（描画下請け：コマンドボタン）
 * @author	taya
 * @date	06.02.07
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "gflib\strbuf.h"
#include "system\arc_util.h"
#include "system\window.h"
#include "system\buflen.h"
#include "system\pms_word.h"
#include "system\winframe.naix"
#include "system\msgdata.h"
#include "msgdata\msg_pms_input_button.h"
#include "msgdata\msg.naix"


#include "pms_input_prv.h"
#include "pms_input_view.h"


//======================================================================

enum {
	DECIDE_WIN_X = 3,
	DECIDE_WIN_Y = 6,
	DECIDE_WIN_WIDTH = 10,
	DECIDE_WIN_HEIGHT = 2,
	DECIDE_WIN_CHARSIZE = DECIDE_WIN_WIDTH*DECIDE_WIN_HEIGHT,
	DECIDE_WIN_CHARPOS = 64,

	CANCEL_WIN_X = 19,
	CANCEL_WIN_Y = 6,
	CANCEL_WIN_WIDTH = 10,
	CANCEL_WIN_HEIGHT = 2,
	CANCEL_WIN_CHARPOS = DECIDE_WIN_CHARSIZE + DECIDE_WIN_CHARPOS,

	DECIDE_WIN_CX = (DECIDE_WIN_X + DECIDE_WIN_WIDTH/2)*8,
	DECIDE_WIN_CY = (DECIDE_WIN_Y + DECIDE_WIN_HEIGHT/2)*8,

	CANCEL_WIN_CX = (CANCEL_WIN_X + CANCEL_WIN_WIDTH/2)*8,
	CANCEL_WIN_CY = (CANCEL_WIN_Y + CANCEL_WIN_HEIGHT/2)*8,

	DECIDE_CURSOR_XPOS = ((DECIDE_WIN_X*8) + (DECIDE_WIN_WIDTH*8)/2),
	DECIDE_CURSOR_YPOS = ((DECIDE_WIN_Y*8) + (DECIDE_WIN_HEIGHT*8)/2),

	CANCEL_CURSOR_XPOS = ((CANCEL_WIN_X*8) + (CANCEL_WIN_WIDTH*8)/2),
	CANCEL_CURSOR_YPOS = ((CANCEL_WIN_Y*8) + (CANCEL_WIN_HEIGHT*8)/2),

};

enum {
	WIN_COL_LETTER = 0x01,
	WIN_COL_SHADOW = 0x02,
	WIN_COL_GROUND = 0x0e,
};

//======================================================================


//======================================================================
//--------------------------------------------------------------
/**
 *	
 */
//--------------------------------------------------------------
struct _PMSIV_BUTTON {
	PMS_INPUT_VIEW*        vwk;
	const PMS_INPUT_WORK*  mwk;
	const PMS_INPUT_DATA*  dwk;

	CLACT_WORK_PTR    cursor_actor;
};


//==============================================================
// Prototype
//==============================================================
static void setup_button_win( GF_BGL_INI* bgl, const BMPWIN_DAT* windat, u32 strID );
static void setup_obj( PMSIV_BUTTON* wk );




//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 * @param   mwk		
 * @param   dwk		
 *
 * @retval  PMSIV_BUTTON*		
 */
//------------------------------------------------------------------
PMSIV_BUTTON*  PMSIV_BUTTON_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk )
{
	PMSIV_BUTTON*  wk = sys_AllocMemory( HEAPID_PMS_INPUT_VIEW, sizeof(PMSIV_BUTTON) );

	wk->vwk = vwk;
	wk->mwk = mwk;
	wk->dwk = dwk;

	wk->cursor_actor = NULL;

	return wk;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_BUTTON_Delete( PMSIV_BUTTON* wk )
{
	if( wk->cursor_actor )
	{
		CLACT_Delete( wk->cursor_actor );
	}
	sys_FreeMemoryEz( wk );
}



//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_BUTTON_SetupGraphicDatas( PMSIV_BUTTON* wk )
{
	static const BMPWIN_DAT  windat_decide = {
		FRM_MAIN_BUTTON,
		DECIDE_WIN_X, DECIDE_WIN_Y,
		DECIDE_WIN_WIDTH, DECIDE_WIN_HEIGHT,
		PALNUM_MAIN_BUTTON, DECIDE_WIN_CHARPOS
	};
	static const BMPWIN_DAT  windat_cancel = {
		FRM_MAIN_BUTTON,
		CANCEL_WIN_X, CANCEL_WIN_Y,
		CANCEL_WIN_WIDTH, CANCEL_WIN_HEIGHT,
		PALNUM_MAIN_BUTTON, CANCEL_WIN_CHARPOS
	};


	GF_BGL_INI* bgl;

	bgl = PMSIView_GetBGL( wk->vwk );

// screen, cgx
	ArcUtil_ScrnSet(ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main3_lz_nscr, bgl,
		FRM_MAIN_BUTTON, 0, 0, TRUE, HEAPID_PMS_INPUT_VIEW );

	ArcUtil_BgCharSet(ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main3_lz_ncgr, bgl,
		FRM_MAIN_BUTTON, 0, 0, TRUE, HEAPID_PMS_INPUT_VIEW );


// bmp window
	setup_button_win( bgl, &windat_decide, button_decide );
	setup_button_win( bgl, &windat_cancel, button_cancel );

	setup_obj( wk );

	GF_BGL_LoadScreenReq( bgl, FRM_MAIN_BUTTON );
}



static void setup_button_win( GF_BGL_INI* bgl, const BMPWIN_DAT* windat, u32 strID )
{
	GF_BGL_BMPWIN  win;
	STRBUF* str;
	u32 xpos;


	GF_BGL_BmpWinAddEx( bgl, &win, windat );
	GF_BGL_BmpWinMakeScrn( &win );
	GF_BGL_BmpWinDataFill( &win, WIN_COL_GROUND );

	str = MSGDAT_GetStrDirectAlloc( ARC_MSG, NARC_msg_pms_input_button_dat, strID, HEAPID_PMS_INPUT_VIEW );

	xpos = ((windat->siz_x*8) - FontProc_GetPrintStrWidth(PMSI_FONT_BUTTON, str, 0)) / 2;

	GF_STR_PrintColor( &win, PMSI_FONT_BUTTON, str, xpos, 0, MSG_NO_PUT,
			GF_PRINTCOLOR_MAKE(WIN_COL_LETTER, WIN_COL_SHADOW, WIN_COL_GROUND),
			NULL);

	GF_BGL_BmpWinCgxOn(&win);

	STRBUF_Delete(str);
	GF_BGL_BmpWinDel( &win );

}

static void setup_obj( PMSIV_BUTTON* wk )
{
	CLACT_HEADER  header;

	PMSIView_SetupDefaultActHeader( wk->vwk, &header, PMSIV_LCD_MAIN, BGPRI_MAIN_BUTTON );
	wk->cursor_actor = PMSIView_AddActor( wk->vwk, &header, DECIDE_CURSOR_XPOS, DECIDE_CURSOR_YPOS,
			ACTPRI_BUTTON_CURSOR, NNS_G2D_VRAM_TYPE_2DMAIN );

	CLACT_AnmChg( wk->cursor_actor, ANM_BUTTON_CURSOR_ACTIVE );
	CLACT_SetDrawFlag( wk->cursor_actor, FALSE );

}



//======================================================================================
//======================================================================================

void PMSIV_BUTTON_StopCursor( PMSIV_BUTTON* wk )
{
	CLACT_AnmChg( wk->cursor_actor, ANM_BUTTON_CURSOR_STOP );
}
void PMSIV_BUTTON_ActiveCursor( PMSIV_BUTTON* wk )
{
	CLACT_AnmChg( wk->cursor_actor, ANM_BUTTON_CURSOR_ACTIVE );
}
void PMSIV_BUTTON_VisibleCursor( PMSIV_BUTTON* wk, BOOL flag )
{
	CLACT_SetDrawFlag( wk->cursor_actor, flag );
}

BOOL PMSIV_BUTTON_GetCursorVisibleFlag( PMSIV_BUTTON* wk )
{
	return CLACT_GetDrawFlag( wk->cursor_actor );
}

void PMSIV_BUTTON_MoveCursor( PMSIV_BUTTON* wk, int pos )
{
	VecFx32  mtx;

	mtx.z = 0;

	switch( pos ){
	case BUTTON_POS_DECIDE:
	default:
		mtx.x = DECIDE_CURSOR_XPOS * FX32_ONE;
		mtx.y = DECIDE_CURSOR_YPOS * FX32_ONE;
		break;

	case BUTTON_POS_CANCEL:
		mtx.x = CANCEL_CURSOR_XPOS * FX32_ONE;
		mtx.y = CANCEL_CURSOR_YPOS * FX32_ONE;
		break;
	}

	CLACT_SetMatrix( wk->cursor_actor, &mtx );
	CLACT_AnmChg( wk->cursor_actor, ANM_BUTTON_CURSOR_ACTIVE );
}

//------------------------------------------------------------------
/**
 * 半透明時に透けて見えないように、ボタン画像をオフセットずらしで隠す
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_BUTTON_Hide( PMSIV_BUTTON* wk )
{
	GF_BGL_ScrollSet( PMSIView_GetBGL(wk->vwk), FRM_MAIN_BUTTON, GF_BGL_SCROLL_Y_SET, 64 );
}
//------------------------------------------------------------------
/**
 * ↑PMSIV_BUTTON_Hideでズラしたオフセットを戻す
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_BUTTON_Appear( PMSIV_BUTTON* wk )
{
	GF_BGL_ScrollSet( PMSIView_GetBGL(wk->vwk), FRM_MAIN_BUTTON, GF_BGL_SCROLL_Y_SET, 0 );
}





