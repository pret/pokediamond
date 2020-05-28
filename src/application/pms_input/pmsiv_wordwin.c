//============================================================================================
/**
 * @file	pmsiv_wordwin.c
 * @bfief	簡易会話入力画面（描画下請け：単語表示ウィンドウ）
 * @author	taya
 * @date	06.02.10
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
#include "msgdata\msg_pms_category.h"
#include "msgdata\msg.naix"


#include "pms_input_prv.h"
#include "pms_input_view.h"
#include "pmsiv_tool.h"

//======================================================================
enum {
	INPUTAREA_PALTYPE_MAX = 10,

	STR_TMPBUF_LEN = 128,	// 表示前のテンポラリとして使用。最大文字数。
};

enum {
	CLEAR_CHARPOS = 0,


	WORDWIN_XORG = 4,
	WORDWIN_YORG = 0,
	WORDWIN_WIDTH = 26,
	WORDWIN_HEIGHT = 32,
	WORDWIN_CHARPOS = CLEAR_CHARPOS+1,


	WORDWIN_DISP_LINE_MAX = 5,
	WORDWIN_DISP_COL_MAX = 2,
	WORDWIN_DISP_WORD_MAX = WORDWIN_DISP_LINE_MAX * WORDWIN_DISP_COL_MAX,

	WORDWIN_WRITE_LINE_INIT = 48,
	WORDWIN_WRITE_LINE_MAX = 256,
	WORDWIN_WRITE_LINE_UNIT = 16,
	WORDWIN_WRITE_LINE_ROUND_BORDER = WORDWIN_WRITE_LINE_MAX - WORDWIN_WRITE_LINE_UNIT,

	WORDWIN_WRITE_OX = 0,
	WORDWIN_WRITE_OY = 0,
	WORDWIN_WRITE_X_MARGIN = 112,
	WORDWIN_WRITE_Y_MARGIN = 24,
	WORDWIN_WRITE_PAGE_HEIGHT = WORDWIN_DISP_LINE_MAX * WORDWIN_WRITE_Y_MARGIN,

	WORDWIN_SCROLL_WAIT_UNIT = PMSI_FRAMES(2),


	// 折り返し前の一時的な文字列描画領域用
	WORD_TMPWIN_WIDTH = 12,
	WORD_TMPWIN_HEIGHT = 2,

	// カーソル描画位置
	CURSOR_WIDTH = 12*8,
	CURSOR_HEIGHT = 16,
	CURSOR_OX = (WORDWIN_XORG*8)+(CURSOR_WIDTH/2) - 8,
	CURSOR_OY = (WORDWIN_YORG*8)+(WORDWIN_WRITE_LINE_INIT)+(CURSOR_HEIGHT/2),
	CURSOR_X_MARGIN = (CURSOR_WIDTH+16),
	CURSOR_Y_MARGIN = WORDWIN_WRITE_Y_MARGIN,

	ARROW_UP_X = 240,
	ARROW_UP_Y = 64,
	ARROW_DOWN_X = 240,
	ARROW_DOWN_Y = 144,

};

enum {
	WORD_COL_LETTER = 0x01,
	WORD_COL_SHADOW = 0x02,
	WORD_COL_GROUND = 0x00,
};

//======================================================================

//======================================================================
//--------------------------------------------------------------
/**
 *	
 */
//--------------------------------------------------------------
struct _PMSIV_WORDWIN {
	PMS_INPUT_VIEW*        vwk;
	const PMS_INPUT_WORK*  mwk;
	const PMS_INPUT_DATA*  dwk;

	GF_BGL_INI*    bgl;
	GF_BGL_BMPWIN  win;
	GF_BGL_BMPWIN  tmp_win;

	CLACT_WORK_PTR  cursor_actor;
	CLACT_WORK_PTR  up_arrow_actor;
	CLACT_WORK_PTR  down_arrow_actor;
	STRBUF*         tmpbuf;

	PMSIV_TOOL_BLEND_WORK   blend_work;
	PMSIV_TOOL_SCROLL_WORK  scroll_work;
	u32                     eff_seq;

	GXWndPlane	winout_backup;
	int         win_visible_backup;

	int    write_v_line;
	int    write_word_idx;
};


//==============================================================
// Prototype
//==============================================================
static void setup_actor( PMSIV_WORDWIN* wk );
static void clear_scroll_area( PMSIV_WORDWIN* wk, int vector );
static void init_write_params( PMSIV_WORDWIN* wk );
static void print_word( PMSIV_WORDWIN* wk, u32 wordnum, u32 v_line );




//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 * @param   mwk		
 * @param   dwk		
 *
 * @retval  PMSIV_WORDWIN*		
 */
//------------------------------------------------------------------
PMSIV_WORDWIN*  PMSIV_WORDWIN_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk )
{
	PMSIV_WORDWIN*  wk = sys_AllocMemory( HEAPID_PMS_INPUT_VIEW, sizeof(PMSIV_WORDWIN) );

	wk->vwk = vwk;
	wk->mwk = mwk;
	wk->dwk = dwk;

	wk->bgl = PMSIView_GetBGL(vwk);
	wk->tmpbuf = STRBUF_Create( BUFLEN_PMS_WORD, HEAPID_PMS_INPUT_VIEW );

	GF_BGL_BmpWinAdd( wk->bgl, &wk->win, FRM_MAIN_WORDWIN, WORDWIN_XORG, WORDWIN_YORG,
					WORDWIN_WIDTH, WORDWIN_HEIGHT, PALNUM_MAIN_WORDWIN, WORDWIN_CHARPOS );

	GF_BGL_BmpWinAdd( wk->bgl, &wk->tmp_win, FRM_MAIN_WORDWIN, 0, 0,
					WORD_TMPWIN_WIDTH, 4, PALNUM_MAIN_WORDWIN, WORDWIN_CHARPOS );


	wk->cursor_actor = NULL;
	wk->up_arrow_actor = NULL;
	wk->down_arrow_actor = NULL;


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
void PMSIV_WORDWIN_Delete( PMSIV_WORDWIN* wk )
{
	if( wk->cursor_actor )
	{
		CLACT_Delete( wk->cursor_actor );
	}
	if( wk->up_arrow_actor )
	{
		CLACT_Delete( wk->up_arrow_actor );
	}
	if( wk->down_arrow_actor )
	{
		CLACT_Delete( wk->down_arrow_actor );
	}
	if( wk->tmpbuf )
	{
		STRBUF_Delete( wk->tmpbuf );
	}

	GF_BGL_BmpWinDel( &(wk->tmp_win) );
	GF_BGL_BmpWinDel( &(wk->win) );

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
void PMSIV_WORDWIN_SetupGraphicDatas( PMSIV_WORDWIN* wk )
{
	GF_BGL_INI* bgl;
	u32 charpos;

	bgl = PMSIView_GetBGL( wk->vwk );

	GF_BGL_ClearCharSet( FRM_MAIN_WORDWIN, 0x20, CLEAR_CHARPOS*0x20, HEAPID_PMS_INPUT_VIEW );
	GF_BGL_ScrFill( bgl, FRM_MAIN_WORDWIN, CLEAR_CHARPOS, 0, 0, 32, 32, PALNUM_MAIN_WORDWIN );

	GF_BGL_BmpWinDataFill(&wk->win, WORD_COL_GROUND);
	GF_BGL_BmpWinMakeScrn(&wk->win);
	GF_BGL_BmpWinCgxOn(&wk->win);
	GF_BGL_LoadScreenReq( bgl, FRM_MAIN_WORDWIN );

	setup_actor( wk );

	GF_BGL_VisibleSet( FRM_MAIN_WORDWIN, FALSE );

}
static void setup_actor( PMSIV_WORDWIN* wk )
{
	CLACT_HEADER  header;

	PMSIView_SetupDefaultActHeader( wk->vwk, &header, PMSIV_LCD_MAIN, BGPRI_MAIN_WORDWIN );
	wk->cursor_actor = PMSIView_AddActor( wk->vwk, &header, CURSOR_OX, CURSOR_OY,
			ACTPRI_WORDWIN_CURSOR, NNS_G2D_VRAM_TYPE_2DMAIN );

	CLACT_AnmChg( wk->cursor_actor, ANM_WORDWIN_CURSOR_ACTIVE );
	CLACT_SetDrawFlag( wk->cursor_actor, FALSE );


	wk->up_arrow_actor = PMSIView_AddActor( wk->vwk, &header, ARROW_UP_X, ARROW_UP_Y,
			ACTPRI_WORDWIN_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN );
	CLACT_AnmChg( wk->up_arrow_actor, ANM_WORD_ARROW_UP );
	CLACT_SetDrawFlag( wk->up_arrow_actor, FALSE );

	wk->down_arrow_actor = PMSIView_AddActor( wk->vwk, &header, ARROW_DOWN_X, ARROW_DOWN_Y,
			ACTPRI_WORDWIN_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN );
	CLACT_AnmChg( wk->down_arrow_actor, ANM_WORD_ARROW_DOWN );
	CLACT_SetDrawFlag( wk->down_arrow_actor, FALSE );


}


//------------------------------------------------------------------
/**
 * 単語内容をBitmapWindowに描画
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_WORDWIN_SetupWord( PMSIV_WORDWIN* wk )
{
	u32 word_max, v_line, i;

	GF_BGL_BmpWinDataFill(&wk->win, WORD_COL_GROUND);
	init_write_params( wk );

	word_max = PMSI_GetCategoryWordMax( wk->mwk );
	if( word_max > WORDWIN_DISP_WORD_MAX )
	{
		word_max = WORDWIN_DISP_WORD_MAX;
	}

	v_line = wk->write_v_line;
	for(i=0; i<word_max; i++)
	{
		print_word( wk, i, v_line );
		if( i & 1 )
		{
			v_line += WORDWIN_WRITE_Y_MARGIN;
		}
	}

	

	GF_BGL_BmpWinCgxOn( &wk->win );

}



//------------------------------------------------------------------
/**
 * フェードインエフェクト開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_WORDWIN_StartFadeIn( PMSIV_WORDWIN* wk )
{
	G2_SetBlendAlpha( FRM_MAIN_WORDWIN_BLENDMASK, GX_BLEND_ALL, 0, 16 );
//G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, GX_BLEND_ALL, 6, 10 );
	GF_BGL_VisibleSet( FRM_MAIN_WORDWIN, TRUE );

	// 上下際のスクロール文字列を見られないようにウィンドウで隠す
	G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_ALL, TRUE);

	wk->winout_backup = G2_GetWndOutsidePlane();
	wk->win_visible_backup = GX_GetVisibleWnd();
	G2_SetWndOutsidePlane(GX_WND_PLANEMASK_ALL^FRM_MAIN_WORDWIN_WNDMASK, TRUE);
	G2_SetWnd1Position(0,46,255,176);
	GX_SetVisibleWnd( GX_WNDMASK_W1 );

	wk->eff_seq = 0;
	PMSIV_TOOL_SetupBlendWork( &wk->blend_work, FRM_MAIN_WORDWIN_BLENDMASK, GX_BLEND_ALL, 0, PMSIV_BLEND_MAX, PMSI_FRAMES(6) );
}
//------------------------------------------------------------------
/**
 * フェードインエフェクト終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL PMSIV_WORDWIN_WaitFadeIn( PMSIV_WORDWIN* wk )
{
	switch( wk->eff_seq ){
	case 0:
		if( PMSIV_TOOL_WaitBlend( &wk->blend_work ) )
		{
			return TRUE;
		}
		break;

	default:
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * フェードアウトエフェクト開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_WORDWIN_StartFadeOut( PMSIV_WORDWIN* wk )
{
	wk->eff_seq = 0;
	PMSIV_TOOL_SetupBlendWork( &wk->blend_work, FRM_MAIN_WORDWIN_BLENDMASK, GX_BLEND_ALL, PMSIV_BLEND_MAX, 0, PMSI_FRAMES(6) );
}
//------------------------------------------------------------------
/**
 * フェードアウトエフェクト終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL PMSIV_WORDWIN_WaitFadeOut( PMSIV_WORDWIN* wk )
{
	switch( wk->eff_seq ){
	case 0:
		if( PMSIV_TOOL_WaitBlend( &wk->blend_work ) )
		{
			GF_BGL_VisibleSet( FRM_MAIN_WORDWIN, FALSE );
			G2_SetWndOutsidePlane( wk->winout_backup.planeMask, wk->winout_backup.effect );
			GX_SetVisibleWnd( wk->win_visible_backup );
			return TRUE;
		}
		break;

	default:
		return TRUE;
	}
	return FALSE;
}







//------------------------------------------------------------------
/**
 * カーソル表示オンオフ
 *
 * @param   wk		
 * @param   flag		
 *
 */
//------------------------------------------------------------------
void PMSIV_WORDWIN_VisibleCursor( PMSIV_WORDWIN* wk, BOOL flag )
{
	CLACT_SetDrawFlag( wk->cursor_actor, flag );

	if( flag )
	{
		CLACT_SetDrawFlag( wk->up_arrow_actor, PMSI_GetWordWinUpArrowVisibleFlag(wk->mwk) );
		CLACT_SetDrawFlag( wk->down_arrow_actor, PMSI_GetWordWinDownArrowVisibleFlag(wk->mwk) );
	}
	else
	{
		CLACT_SetDrawFlag( wk->up_arrow_actor, FALSE );
		CLACT_SetDrawFlag( wk->down_arrow_actor, FALSE );
	}
}

//------------------------------------------------------------------
/**
 * カーソル移動
 *
 * @param   wk		
 * @param   pos		
 *
 */
//------------------------------------------------------------------
void PMSIV_WORDWIN_MoveCursor( PMSIV_WORDWIN* wk, u32 pos )
{
	VecFx32 mtx;
	u32 x, y;

	x = pos & 1;
	y = pos / 2;

	mtx.x = (CURSOR_OX + CURSOR_X_MARGIN * x ) * FX32_ONE;
	mtx.y = (CURSOR_OY + CURSOR_Y_MARGIN * y ) * FX32_ONE;
	mtx.z = 0;

	CLACT_SetMatrix( wk->cursor_actor, &mtx );
	CLACT_AnmChg( wk->cursor_actor, ANM_WORDWIN_CURSOR_ACTIVE );
}


//------------------------------------------------------------------
/**
 * スクロール開始
 *
 * @param   wk		
 * @param   vector		
 *
 */
//------------------------------------------------------------------
void PMSIV_WORDWIN_StartScroll( PMSIV_WORDWIN* wk, int vector )
{
	int next_v_line, next_word_idx, i, v_line, word_idx, write_word_max, scroll_wait;

	clear_scroll_area( wk, vector );

	next_word_idx = wk->write_word_idx + (vector * WORDWIN_DISP_COL_MAX);
	next_v_line = (wk->write_v_line + (vector * WORDWIN_WRITE_Y_MARGIN)) & 255;

	if( vector < 0 ){
		v_line = next_v_line;
		word_idx = next_word_idx;
		write_word_max = -(vector * WORDWIN_DISP_COL_MAX);
		scroll_wait = -( WORDWIN_SCROLL_WAIT_UNIT * vector );
	}else{
		v_line = (wk->write_v_line + WORDWIN_WRITE_PAGE_HEIGHT) & 255;
		word_idx = wk->write_word_idx + WORDWIN_DISP_WORD_MAX;
		write_word_max = vector * WORDWIN_DISP_COL_MAX;
		if( (write_word_max + word_idx) > PMSI_GetCategoryWordMax(wk->mwk) )
		{
			write_word_max--;
		}
		scroll_wait = WORDWIN_SCROLL_WAIT_UNIT * vector;
	}

	for(i=0; i<write_word_max; i++)
	{
		print_word( wk, word_idx+i, v_line );
		if( i & 1 )
		{
			v_line = (v_line + WORDWIN_WRITE_Y_MARGIN) & 255;
		}
	}


	wk->write_v_line = next_v_line;
	wk->write_word_idx = next_word_idx;

	GF_BGL_BmpWinCgxOn( &wk->win );

	PMSIV_TOOL_SetupScrollWork( &(wk->scroll_work), wk->bgl, FRM_MAIN_WORDWIN, PMSIV_TOOL_SCROLL_DIRECTION_Y,
		vector*WORDWIN_WRITE_Y_MARGIN, scroll_wait );

}

//------------------------------------------------------------------
/**
 * スクロール終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL PMSIV_WORDWIN_WaitScroll( PMSIV_WORDWIN* wk )
{
	if( PMSIV_TOOL_WaitScroll(&wk->scroll_work) )
	{
		CLACT_SetDrawFlag( wk->up_arrow_actor, PMSI_GetWordWinUpArrowVisibleFlag(wk->mwk) );
		CLACT_SetDrawFlag( wk->down_arrow_actor, PMSI_GetWordWinDownArrowVisibleFlag(wk->mwk) );
		return TRUE;
	}
	return FALSE;
}

static void clear_scroll_area( PMSIV_WORDWIN* wk, int vector )
{
	int  top, bottom;

	if( vector > 0 )
	{
		top = (wk->write_v_line + WORDWIN_WRITE_PAGE_HEIGHT) & 0xff;
		bottom = (top + (vector * WORDWIN_WRITE_Y_MARGIN)) & 0xff;
	}
	else
	{
		bottom = wk->write_v_line;
		top = (bottom + (vector * WORDWIN_WRITE_Y_MARGIN)) & 0xff;
	}

	if( top < bottom )
	{
		GF_BGL_BmpWinFill( &wk->win, WORD_COL_GROUND, 0, top, WORDWIN_WIDTH*8, (bottom-top) );
	}
	else
	{
		GF_BGL_BmpWinFill( &wk->win, WORD_COL_GROUND, 0, top, WORDWIN_WIDTH*8, 256-top );
		GF_BGL_BmpWinFill( &wk->win, WORD_COL_GROUND, 0, 0, WORDWIN_WIDTH*8, bottom );
	}
}



static void init_write_params( PMSIV_WORDWIN* wk )
{
	wk->write_v_line = WORDWIN_WRITE_LINE_INIT;
	wk->write_word_idx = 0;
	GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_WORDWIN, GF_BGL_SCROLL_Y_SET, 0 );
}


static void print_word( PMSIV_WORDWIN* wk, u32 wordnum, u32 v_line )
{
	PMSI_GetCategoryWord( wk->mwk, wordnum, wk->tmpbuf );

	if( v_line <= WORDWIN_WRITE_LINE_ROUND_BORDER )
	{
		GF_STR_PrintColor( &wk->win, PMSI_FONT_WORDWIN, wk->tmpbuf,
					WORDWIN_WRITE_OX + (wordnum&1)*WORDWIN_WRITE_X_MARGIN, v_line, MSG_NO_PUT,
					GF_PRINTCOLOR_MAKE(WORD_COL_LETTER, WORD_COL_SHADOW, WORD_COL_GROUND),
					NULL);
	}
	else
	{
		u32  write_v_range = WORDWIN_WRITE_LINE_MAX - v_line;
		GF_BGL_BmpWinDataFill( &wk->tmp_win, WORD_COL_GROUND );

		GF_STR_PrintColor( &wk->tmp_win, PMSI_FONT_WORDWIN, wk->tmpbuf,
					0, 0, MSG_NO_PUT,
					GF_PRINTCOLOR_MAKE(WORD_COL_LETTER, WORD_COL_SHADOW, WORD_COL_GROUND),
					NULL);

		GF_BGL_BmpWinPrint( &wk->win, wk->tmp_win.chrbuf, 0, 0,
				WORD_TMPWIN_WIDTH*8, WORD_TMPWIN_HEIGHT*8,
				WORDWIN_WRITE_OX + (wordnum&1)*WORDWIN_WRITE_X_MARGIN,   v_line,
				WORD_TMPWIN_WIDTH*8, write_v_range );


		GF_BGL_BmpWinPrint( &wk->win, wk->tmp_win.chrbuf, 0, write_v_range,
				WORD_TMPWIN_WIDTH*8, WORD_TMPWIN_HEIGHT*8,
				WORDWIN_WRITE_OX + (wordnum&1)*WORDWIN_WRITE_X_MARGIN,   0,
				WORD_TMPWIN_WIDTH*8, (WORD_TMPWIN_HEIGHT*8) - write_v_range );

	}



}
