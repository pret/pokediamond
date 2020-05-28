//============================================================================================
/**
 * @file	pmsiv_category.c
 * @bfief	簡易会話入力画面（描画下請け：カテゴリ・イニシャル）
 * @author	taya
 * @date	06.02.10
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "gflib\strbuf_family.h"
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
#include "pmsi_initial_data.h"


//======================================================================
enum {
	INPUTAREA_PALTYPE_MAX = 10,

	STR_TMPBUF_LEN = 128,	// 表示前のテンポラリとして使用。最大文字数。

	HARD_WINDOW_TOP = 0,
	HARD_WINDOW_BOTTOM = 160,
	HARD_WINDOW_LEFT = 0,
	HARD_WINDOW_RIGHT = 255,
	HARD_WINDOW_BLDY = -10,

	BRIGHT_EFFECT_WAIT = PMSI_FRAMES(8),
};

enum {
	CATEGORY_WIN_WIDTH = 9,
	CATEGORY_WIN_HEIGHT = 2,
	CATEGORY_WIN_CHARSIZE = CATEGORY_WIN_WIDTH*CATEGORY_WIN_HEIGHT,

	CATEGORY_WIN_XORG = 1,
	CATEGORY_WIN_YORG = 9,
	CATEGORY_WIN_X_MARGIN = 1,
	CATEGORY_WIN_Y_MARGIN = 1,

	CATEGORY_WIN_ROWS = 3,

	INITIAL_WIN_XORG = 34,
	INITIAL_WIN_YORG = 10,
	INITIAL_WIN_WIDTH = 25,
	INITIAL_WIN_HEIGHT = 8,
	INITIAL_WIN_CHARSIZE = INITIAL_WIN_WIDTH*INITIAL_WIN_HEIGHT,

	BACK_WIN_WIDTH = 8,
	BACK_WIN_HEIGHT = 2,
	BACK_WIN_CHARSIZE = BACK_WIN_WIDTH*BACK_WIN_HEIGHT,

	CATEGORY_BACK_WIN_XORG = 12,
	CATEGORY_BACK_WIN_YORG = 21,
	INITIAL_BACK_WIN_XORG = 44,
	INITIAL_BACK_WIN_YORG = 21,

	// BG offset
	GROUPMODE_BG_XOFS = -4,
	INITIALMODE_BG_XOFS = 252,

	CATEGORY_BG_DISABLE_YOFS = 2,
	CATEGORY_BG_ENABLE_YOFS = 26,
	CATEGORY_BG_DISABLE_EFF_VECTOR = (CATEGORY_BG_DISABLE_YOFS - CATEGORY_BG_ENABLE_YOFS),
	CATEGORY_BG_ENABLE_EFF_VECTOR = (CATEGORY_BG_ENABLE_YOFS - CATEGORY_BG_DISABLE_YOFS),
	ENABLE_MOVE_FRAMES = PMSI_FRAMES(3),
	MODECHANGE_MOVE_FRAMES = PMSI_FRAMES(8),


	// OBJ pos
	CATEGORY_CURSOR_OX = ( (CATEGORY_WIN_XORG*8) + ((CATEGORY_WIN_WIDTH*8)/2) ) - GROUPMODE_BG_XOFS,
	CATEGORY_CURSOR_OY = ( (CATEGORY_WIN_YORG*8) + ((CATEGORY_WIN_HEIGHT*8)/2) ) - CATEGORY_BG_ENABLE_YOFS,
	CATEGORY_CURSOR_X_MARGIN = ((CATEGORY_WIN_WIDTH+CATEGORY_WIN_X_MARGIN)*8),
	CATEGORY_CURSOR_Y_MARGIN = ((CATEGORY_WIN_HEIGHT+CATEGORY_WIN_Y_MARGIN)*8),

	CATEGORY_CURSOR_BACK_XPOS = ((CATEGORY_BACK_WIN_XORG*8)+ (CATEGORY_WIN_WIDTH*8)/2),
	CATEGORY_CURSOR_BACK_YPOS = ((CATEGORY_BACK_WIN_YORG*8)+ (CATEGORY_WIN_HEIGHT*8)/2) - CATEGORY_BG_ENABLE_YOFS,

	INITIAL_CURSOR_OX = ((INITIAL_WIN_XORG-32)*8-GROUPMODE_BG_XOFS) + 6,
	INITIAL_CURSOR_OY = ((INITIAL_WIN_YORG*8)-CATEGORY_BG_ENABLE_YOFS) + 8,


};

enum {
	CATEGORY_WIN_COL_LETTER = 0x01,
	CATEGORY_WIN_COL_SHADOW = 0x02,
	CATEGORY_WIN_COL_GROUND = 0x0f,

	CATEGORY_WIN_UNKNOWN_COL_LETTER = 0x03,
	CATEGORY_WIN_UNKNOWN_COL_SHADOW = 0x04,
};


//======================================================================

//======================================================================
typedef struct {
	void*         parent_work;
	GF_BGL_INI*   bgl;

	fx32   pos;
	fx32   end_pos;
	fx32   add_value;
	u32    timer;
}SCROLL_WORK;

//--------------------------------------------------------------
/**
 *	
 */
//--------------------------------------------------------------
struct _PMSIV_CATEGORY {
	PMS_INPUT_VIEW*        vwk;
	const PMS_INPUT_WORK*  mwk;
	const PMS_INPUT_DATA*  dwk;
	GF_BGL_INI*            bgl;

	u32            mode;
	u32            eff_seq;

	TCB_PTR        effect_task;
	PMSIV_TOOL_BLEND_WORK   blend_work;
	PMSIV_TOOL_SCROLL_WORK  scroll_work;

	CLACT_WORK_PTR  cursor_actor;

};


//==============================================================
// Prototype
//==============================================================
static u32 setup_group_window( PMSIV_CATEGORY* wk, GF_BGL_INI* bgl, u32 charpos );
static u32 setup_initial_window( PMSIV_CATEGORY* wk, GF_BGL_INI* bgl, u32 charpos );
static u32 setup_back_window( PMSIV_CATEGORY* wk, GF_BGL_INI* bgl, u32 charpos );
static void setup_actor( PMSIV_CATEGORY* wk );




//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 * @param   mwk		
 * @param   dwk		
 *
 * @retval  PMSIV_CATEGORY*		
 */
//------------------------------------------------------------------
PMSIV_CATEGORY*  PMSIV_CATEGORY_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk )
{
	PMSIV_CATEGORY*  wk = sys_AllocMemory( HEAPID_PMS_INPUT_VIEW, sizeof(PMSIV_CATEGORY) );

	wk->vwk = vwk;
	wk->mwk = mwk;
	wk->dwk = dwk;
	wk->bgl = PMSIView_GetBGL( vwk );

	wk->mode = CATEGORY_MODE_GROUP;

	wk->effect_task = NULL;

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
void PMSIV_CATEGORY_Delete( PMSIV_CATEGORY* wk )
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
void PMSIV_CATEGORY_SetupGraphicDatas( PMSIV_CATEGORY* wk )
{
	GF_BGL_INI* bgl;
	u32 charpos;

	bgl = PMSIView_GetBGL( wk->vwk );

	ArcUtil_ScrnSet(ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main1_lz_nscr, bgl,
		FRM_MAIN_CATEGORY, 0, 0, TRUE, HEAPID_PMS_INPUT_VIEW );

	charpos = ArcUtil_BgCharSet(ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main1_lz_ncgr, bgl,
		FRM_MAIN_CATEGORY, 0, 0, TRUE, HEAPID_PMS_INPUT_VIEW );
	charpos /= 0x20;

	charpos = setup_group_window( wk, bgl, charpos );
	charpos = setup_initial_window( wk, bgl, charpos );
	setup_back_window( wk, bgl, charpos );

	GF_BGL_ScrollSet( bgl, FRM_MAIN_CATEGORY, GF_BGL_SCROLL_X_SET, GROUPMODE_BG_XOFS );
	GF_BGL_ScrollSet( bgl, FRM_MAIN_CATEGORY, GF_BGL_SCROLL_Y_SET, CATEGORY_BG_DISABLE_YOFS );

	setup_actor( wk );


	// 選択できない状態ということを示すため、輝度を落としておく
	G2_SetBlendBrightness( FRM_MAIN_CATEGORY_BLENDMASK, HARD_WINDOW_BLDY );
	G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_ALL, TRUE);
	G2_SetWndOutsidePlane(GX_WND_PLANEMASK_ALL^FRM_MAIN_CATEGORY_WNDMASK, TRUE);
	G2_SetWnd0Position(0,0,255,160);
	GX_SetVisibleWnd( GX_WNDMASK_W0 );


	GF_BGL_LoadScreenReq( bgl, FRM_MAIN_CATEGORY );
}


static u32 setup_group_window( PMSIV_CATEGORY* wk, GF_BGL_INI* bgl, u32 charpos )
{
	int i, x, y;
	GF_BGL_BMPWIN win;
	MSGDATA_MANAGER* msgman;
	STRBUF* str;
	u32   print_color, print_xpos;

	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_pms_category_dat, HEAPID_PMS_INPUT_VIEW );

	x = CATEGORY_WIN_XORG;
	y = CATEGORY_WIN_YORG;

	for(i=0; i<CATEGORY_GROUP_MAX; i++)
	{
		if( (i!=0) && (i%CATEGORY_WIN_ROWS==0) )
		{
			x = CATEGORY_WIN_XORG;
			y += (CATEGORY_WIN_HEIGHT + CATEGORY_WIN_Y_MARGIN);
		}

		

		if( PMSI_DATA_GetGroupEnableWordCount(wk->dwk, i) )
		{
			str = MSGMAN_AllocString( msgman, pms_category_01+i );
			print_color = GF_PRINTCOLOR_MAKE(CATEGORY_WIN_COL_LETTER, CATEGORY_WIN_COL_SHADOW, CATEGORY_WIN_COL_GROUND);
		}
		else
		{
			str = MSGMAN_AllocString( msgman, pms_category_unknown );
			print_color = GF_PRINTCOLOR_MAKE(CATEGORY_WIN_UNKNOWN_COL_LETTER, CATEGORY_WIN_UNKNOWN_COL_SHADOW, CATEGORY_WIN_COL_GROUND);
		}

		GF_ASSERT(charpos < (1024-CATEGORY_WIN_CHARSIZE));
		GF_BGL_BmpWinAdd(	bgl, &win, FRM_MAIN_CATEGORY, 
						x, y, CATEGORY_WIN_WIDTH, CATEGORY_WIN_HEIGHT,
						PALNUM_MAIN_CATEGORY, charpos );

		GF_BGL_BmpWinDataFill( &win, CATEGORY_WIN_COL_GROUND );

		print_xpos = ((CATEGORY_WIN_WIDTH*8)-FontProc_GetPrintStrWidth(PMSI_FONT_CATEGORY, str, 0))/2;
		GF_STR_PrintColor( &win, PMSI_FONT_CATEGORY, str, print_xpos, 0, MSG_NO_PUT, print_color, NULL );

		GF_BGL_BmpWinMakeScrn(&win);
		GF_BGL_BmpWinCgxOn(&win);

		STRBUF_Delete(str);
		GF_BGL_BmpWinDel(&win);

		charpos += CATEGORY_WIN_CHARSIZE;
		x += (CATEGORY_WIN_WIDTH+CATEGORY_WIN_X_MARGIN);
	}

	MSGMAN_Delete(msgman);

	return charpos;
}

static u32 setup_initial_window( PMSIV_CATEGORY* wk, GF_BGL_INI* bgl, u32 charpos )
{
	GF_BGL_BMPWIN  win;
	STRBUF* buf;
	u32 print_color, initial_max, i, x, y;

	GF_ASSERT(charpos < (1024-INITIAL_WIN_CHARSIZE));

	GF_BGL_BmpWinAdd( bgl, &win, FRM_MAIN_CATEGORY, 
					INITIAL_WIN_XORG, INITIAL_WIN_YORG, INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT,
					PALNUM_MAIN_CATEGORY, charpos );
	charpos += INITIAL_WIN_CHARSIZE;


	buf = STRBUF_Create(4, HEAPID_PMS_INPUT_VIEW);

	GF_BGL_BmpWinDataFill( &win, CATEGORY_WIN_COL_GROUND );

	initial_max = PMSI_INITIAL_DAT_GetInitialMax();
	for(i=0; i<initial_max; i++)
	{
		PMSI_INITIAL_DAT_GetStr(i, buf);
		PMSI_INITIAL_DAT_GetPrintPos(i, &x, &y);

		if( PMSI_DATA_GetInitialEnableWordCount(wk->dwk, i) )
		{
			print_color = GF_PRINTCOLOR_MAKE(CATEGORY_WIN_COL_LETTER, CATEGORY_WIN_COL_SHADOW, CATEGORY_WIN_COL_GROUND);
		}
		else
		{
			print_color = GF_PRINTCOLOR_MAKE(CATEGORY_WIN_UNKNOWN_COL_LETTER, CATEGORY_WIN_UNKNOWN_COL_SHADOW, CATEGORY_WIN_COL_GROUND);
		}

		
		GF_STR_PrintColor( &win, PMSI_FONT_CATEGORY, buf, 
					x, y, MSG_NO_PUT,
					print_color,
					NULL);
	}

	GF_BGL_BmpWinCgxOn(&win);
	GF_BGL_BmpWinMakeScrn(&win);

	STRBUF_Delete(buf);
	GF_BGL_BmpWinDel(&win);

	return charpos;
}

static u32 setup_back_window( PMSIV_CATEGORY* wk, GF_BGL_INI* bgl, u32 charpos )
{
	static const struct {
		u16  x;
		u16  y;
	}winpos_tbl[] = {
		{ CATEGORY_BACK_WIN_XORG, CATEGORY_BACK_WIN_YORG },
		{ INITIAL_BACK_WIN_XORG, INITIAL_BACK_WIN_YORG },
	};
	GF_BGL_BMPWIN  win;
	MSGDATA_MANAGER* msgman;
	STRBUF* str;
	int i, print_xpos;

	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_pms_category_dat, HEAPID_PMS_INPUT_VIEW );
	str = MSGMAN_AllocString( msgman, pms_category_back);
	print_xpos = ((BACK_WIN_WIDTH*8)-FontProc_GetPrintStrWidth(PMSI_FONT_CATEGORY,str,0))/2;

	for(i=0; i<NELEMS(winpos_tbl); i++)
	{
		GF_ASSERT(charpos < (1024-BACK_WIN_CHARSIZE));

		GF_BGL_BmpWinAdd( bgl, &win, FRM_MAIN_CATEGORY, winpos_tbl[i].x, winpos_tbl[i].y,
					BACK_WIN_WIDTH, BACK_WIN_HEIGHT, PALNUM_MAIN_CATEGORY, charpos );

		GF_BGL_BmpWinDataFill( &win, CATEGORY_WIN_COL_GROUND );
		GF_STR_PrintColor( &win, PMSI_FONT_CATEGORY, str, print_xpos, 0, MSG_NO_PUT,
					GF_PRINTCOLOR_MAKE(CATEGORY_WIN_COL_LETTER, CATEGORY_WIN_COL_SHADOW, CATEGORY_WIN_COL_GROUND),
					NULL);

		GF_BGL_BmpWinMakeScrn(&win);
		GF_BGL_BmpWinCgxOn(&win);

		GF_BGL_BmpWinDel(&win);

		charpos += BACK_WIN_CHARSIZE;
	}

	STRBUF_Delete(str);
	MSGMAN_Delete(msgman);

	return charpos;
}

static void setup_actor( PMSIV_CATEGORY* wk )
{
	CLACT_HEADER  header;

	PMSIView_SetupDefaultActHeader( wk->vwk, &header, PMSIV_LCD_MAIN, BGPRI_MAIN_CATEGORY );
	wk->cursor_actor = PMSIView_AddActor( wk->vwk, &header, CATEGORY_CURSOR_OX, CATEGORY_CURSOR_OY,
			ACTPRI_CATEGORY_CURSOR, NNS_G2D_VRAM_TYPE_2DMAIN );

	CLACT_AnmChg( wk->cursor_actor, ANM_CATEGORY_CURSOR_ACTIVE );
	CLACT_SetDrawFlag( wk->cursor_actor, FALSE );

}


//======================================================================================
//======================================================================================

//------------------------------------------------------------------
/**
 * カーソル表示オンオフ
 *
 * @param   wk		
 * @param   flag		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_VisibleCursor( PMSIV_CATEGORY* wk, BOOL flag )
{
	CLACT_SetDrawFlag( wk->cursor_actor, flag );

	if( flag )
	{
		if( PMSI_GetCategoryMode(wk->mwk) == CATEGORY_MODE_GROUP )
		{
			CLACT_AnmChg( wk->cursor_actor, ANM_CATEGORY_CURSOR_ACTIVE );
		}
		else
		{
			CLACT_AnmChg( wk->cursor_actor, ANM_INITIAL_CURSOR_ACTIVE );
		}
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
void PMSIV_CATEGORY_MoveCursor( PMSIV_CATEGORY* wk, u32 pos )
{
	VecFx32  mtx;
	u32  mode;
	u32  anm;

	mode = PMSI_GetCategoryMode(wk->mwk);
	mtx.z = 0;

	if( pos == CATEGORY_POS_BACK )
	{
		mtx.x = CATEGORY_CURSOR_BACK_XPOS;
		mtx.y = CATEGORY_CURSOR_BACK_YPOS;
		anm = ANM_CATEGORY_BACK_CURSOR_ACTIVE;
	}
	else
	{
		if( mode == CATEGORY_MODE_GROUP )
		{
			mtx.x = CATEGORY_CURSOR_OX + CATEGORY_CURSOR_X_MARGIN * (pos % CATEGORY_WIN_ROWS);
			mtx.y = CATEGORY_CURSOR_OY + CATEGORY_CURSOR_Y_MARGIN * (pos / CATEGORY_WIN_ROWS);
			anm = ANM_CATEGORY_CURSOR_ACTIVE;
		}
		else
		{
			u32 x, y;
			PMSI_INITIAL_DAT_GetPrintPos(pos, &x, &y);
			mtx.x = INITIAL_CURSOR_OX + x;
			mtx.y = INITIAL_CURSOR_OY + y;
			anm = ANM_INITIAL_CURSOR_ACTIVE;
		}
	}

	mtx.x *= FX32_ONE;
	mtx.y *= FX32_ONE;

	CLACT_SetMatrix( wk->cursor_actor, &mtx );
	CLACT_AnmChg( wk->cursor_actor, anm );
}

//------------------------------------------------------------------
/**
 * カテゴリ選択開始エフェクト開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_StartEnableBG( PMSIV_CATEGORY* wk )
{
	wk->eff_seq = 0;

	PMSIV_TOOL_SetupBrightWork( &(wk->blend_work), FRM_MAIN_CATEGORY_BLENDMASK, HARD_WINDOW_BLDY, 0, BRIGHT_EFFECT_WAIT );
}

//------------------------------------------------------------------
/**
 * カテゴリ選択開始エフェクト終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL PMSIV_CATEGORY_WaitEnableBG( PMSIV_CATEGORY* wk )
{
	switch( wk->eff_seq ){
	case 0:
		if( PMSIV_TOOL_WaitBright( (&wk->blend_work) ) )
		{
//			set_scroll_work( &(wk->scroll_work), wk, CATEGORY_BG_DISABLE_YOFS, CATEGORY_BG_ENABLE_YOFS, ENABLE_MOVE_FRAMES );

			PMSIV_TOOL_SetupScrollWork( &(wk->scroll_work), wk->bgl, FRM_MAIN_CATEGORY, PMSIV_TOOL_SCROLL_DIRECTION_Y,
						 CATEGORY_BG_ENABLE_EFF_VECTOR, ENABLE_MOVE_FRAMES );

//			start_effect_task( wk, bg_v_scroll_task, &(wk->scroll_work), VTASKPRI_COMMAND );
			wk->eff_seq++;
		}
		break;

	case 1:
		return PMSIV_TOOL_WaitScroll( &(wk->scroll_work) );
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * カテゴリ選択終了エフェクト開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_StartDisableBG( PMSIV_CATEGORY* wk )
{
	wk->eff_seq = 0;

	PMSIV_TOOL_SetupScrollWork( &(wk->scroll_work), wk->bgl, FRM_MAIN_CATEGORY, PMSIV_TOOL_SCROLL_DIRECTION_Y,
				 CATEGORY_BG_DISABLE_EFF_VECTOR, ENABLE_MOVE_FRAMES );

}

//------------------------------------------------------------------
/**
 * カテゴリ選択終了エフェクト終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL PMSIV_CATEGORY_WaitDisableBG( PMSIV_CATEGORY* wk )
{
	switch( wk->eff_seq ){
	case 0:
		if( PMSIV_TOOL_WaitScroll(&(wk->scroll_work)) )
		{
			PMSIV_TOOL_SetupBrightWork( &(wk->blend_work), FRM_MAIN_CATEGORY_BLENDMASK, 0, HARD_WINDOW_BLDY, BRIGHT_EFFECT_WAIT );
			wk->eff_seq++;
		}
		break;

	case 1:
		return PMSIV_TOOL_WaitBright( (&wk->blend_work) );
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * カテゴリ選択終了後の位置にBGオフセットを強制的に戻す
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_SetDisableBG( PMSIV_CATEGORY* wk )
{
	GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_CATEGORY, GF_BGL_SCROLL_Y_SET, CATEGORY_BG_DISABLE_YOFS );
}


//------------------------------------------------------------------
/**
 * カテゴリ選択ウィンドウ輝度ダウンエフェクト開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_StartBrightDown( PMSIV_CATEGORY* wk )
{
	PMSIV_TOOL_SetupBrightWork( &(wk->blend_work), FRM_MAIN_CATEGORY_BLENDMASK, 0, HARD_WINDOW_BLDY, BRIGHT_EFFECT_WAIT );
}
BOOL PMSIV_CATEGORY_WaitBrightDown( PMSIV_CATEGORY* wk )
{
	return PMSIV_TOOL_WaitBright(&(wk->blend_work));
}


//------------------------------------------------------------------
/**
 * カテゴリ選択ウィンドウフェードアウト開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_StartFadeOut( PMSIV_CATEGORY* wk )
{
	PMSIV_TOOL_SetupBlendWork( &wk->blend_work, FRM_MAIN_CATEGORY_BLENDMASK, GX_BLEND_ALL, PMSIV_BLEND_MAX, 0, PMSI_FRAMES(6) );
}

//------------------------------------------------------------------
/**
 * カテゴリ選択ウィンドウフェードアウト開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
BOOL PMSIV_CATEGORY_WaitFadeOut( PMSIV_CATEGORY* wk )
{
	if( PMSIV_TOOL_WaitBlend(&wk->blend_work) )
	{
		GF_BGL_VisibleSet( FRM_MAIN_CATEGORY, FALSE );
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * カテゴリ選択ウィンドウフェードイン開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_StartFadeIn( PMSIV_CATEGORY* wk )
{
	G2_SetBlendAlpha( FRM_MAIN_CATEGORY_BLENDMASK, GX_BLEND_ALL, 0, 16 );
	GF_BGL_VisibleSet( FRM_MAIN_CATEGORY, TRUE );

	PMSIV_TOOL_SetupBlendWork( &wk->blend_work, FRM_MAIN_CATEGORY_BLENDMASK, GX_BLEND_ALL, 0, PMSIV_BLEND_MAX, PMSI_FRAMES(6) );
}

//------------------------------------------------------------------
/**
 * カテゴリ選択ウィンドウフェードイン終了待ち
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
BOOL PMSIV_CATEGORY_WaitFadeIn( PMSIV_CATEGORY* wk )
{
	return PMSIV_TOOL_WaitBlend(&wk->blend_work);
}


//------------------------------------------------------------------
/**
 * カテゴリモードに応じてＢＧオフセットを変更（強制）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_ChangeModeBG( PMSIV_CATEGORY* wk )
{
	int xofs;

	if( PMSI_GetCategoryMode(wk->mwk) == CATEGORY_MODE_GROUP )
	{
		xofs = GROUPMODE_BG_XOFS;
	}
	else
	{
		xofs = INITIALMODE_BG_XOFS;
	}


	GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_CATEGORY, GF_BGL_SCROLL_X_SET, xofs );
}


//------------------------------------------------------------------
/**
 * カテゴリモードに応じてＢＧオフセット変更（エフェクトあり）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_CATEGORY_StartModeChange( PMSIV_CATEGORY* wk )
{
	int vector;

	if( PMSI_GetCategoryMode(wk->mwk) == CATEGORY_MODE_GROUP )
	{
		vector = (GROUPMODE_BG_XOFS - INITIALMODE_BG_XOFS);
	}
	else
	{
		vector = (INITIALMODE_BG_XOFS - GROUPMODE_BG_XOFS);
	}

	PMSIV_TOOL_SetupScrollWork( &(wk->scroll_work), wk->bgl, FRM_MAIN_CATEGORY, PMSIV_TOOL_SCROLL_DIRECTION_X,
				 vector, MODECHANGE_MOVE_FRAMES );

}

BOOL PMSIV_CATEGORY_WaitModeChange( PMSIV_CATEGORY* wk )
{
	return PMSIV_TOOL_WaitScroll( &(wk->scroll_work) );
}
