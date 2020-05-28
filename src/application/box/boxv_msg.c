//============================================================================================
/**
 * @file	boxv_msg.c
 * @brief	ボックス操作画面　描画下請け（メッセージ・メニュー関連）
 * @author	taya
 * @date	2005.09.27
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\fontproc.h"
#include  "system\msgdata.h"
#include  "system\bmp_menu.h"
#include  "system\wordset.h"
#include  "system\window.h"
#include  "msgdata\msg.naix"
#include  "msgdata\msg_boxmenu.h"

#include  "system\winframe.naix"
#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"

//------------------------------------------------------------
/**
 *  consts
 */
//------------------------------------------------------------

/// ウィンドウタイプ
enum {
	WIN_MSG,
	WIN_MENU,
	WIN_MAX,
};

/// ウィンドウパラメータ
enum {
	// Frame 9 char
	MENU_FRAME_CHAROFS = 512,
	MENU_FRAME_CHARSIZE = 9,

	MSG_FRAME_CHAROFS = MENU_FRAME_CHAROFS + MENU_FRAME_CHARSIZE,
	MSG_FRAME_CHARSIZE = 18,

	// Msg 60 char
	WIN_MSG_CHAROFS = MSG_FRAME_CHAROFS + MSG_FRAME_CHARSIZE,
	WIN_MSG_X = 2,
	WIN_MSG_Y = 21,
	WIN_MSG_WIDTH = 27,
	WIN_MSG_HEIGHT = 2,
	WIN_MSG_SIZE = WIN_MSG_WIDTH * WIN_MSG_HEIGHT,

	// Menu 162 char
	WIN_MENU_CHAROFS = WIN_MSG_CHAROFS + WIN_MSG_SIZE,
	WIN_MENU_WIDTH = 10,
	WIN_MENU_HEIGHT = BOXAPP_MENU_ELEMS_MAX*2,
	WIN_MENU_Y_BOTTOM = 18,
	WIN_MENU_Y = WIN_MENU_Y_BOTTOM - (WIN_MENU_HEIGHT-1),
	WIN_MENU_X = 31 - WIN_MENU_WIDTH,


	MSG_PAL_GROUND = 0x0f,

	MENU_PAL_GROUND = 0x0f,
	MENU_PAL_LETTER = 0x0b,
	MENU_PAL_SHADOW = 0x0c,

	WIN_MENU_LINE_HEIGHT = 16,
	WIN_MENU_WRITE_XMARGIN = 10,
	WIN_MENU_MARKING_YMARGIN = 4,
	WIN_MENU_MARKING_XMARGIN = ((WIN_MENU_WIDTH*8)/2)-4,
};

//==============================================================
// Prototype
//==============================================================
static void MsgWindowFrameWrite( GF_BGL_INI* bgl, u32 frm, u32 posx, u32 posy, u32 sizx, u32 sizy );
static void MarkingStatePrint( MSG_VIEW_WORK* wk, GF_BGL_BMPWIN* win, u8 mark, u32 pos );
static void MenuWinScrnWrite( MSG_VIEW_WORK* wk, u32 elems );
static void WinFrameScrnWrite( GF_BGL_INI* bgl, u32 frm, u32 posx, u32 posy, u32 sizx, u32 sizy );
static void MenuWinScrnErase( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );
static void MsgWinScrnErase( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );



//------------------------------------------------------------------
/**
 * 初期化処理
 *
 * @param   wk			ワークポインタ
 * @param   vwk			描画ワーク
 * @param   vpara		描画パラメータ
 * @param   bgl			BGLシステムワーク
 * @param   actsys		アクターシステムワーク
 *
 * @retval  BOOL		TRUEで成功
 */
//------------------------------------------------------------------
BOOL BoxAppView_MsgInit( MSG_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys,
	 MSGDATA_MANAGER* msgman_boxmes, const WORDSET* wordset, int winType )
{
	wk->vwk = vwk;
	wk->bgl = bgl;
	wk->vpara = vpara;
	wk->wordset = wordset;
	wk->wintype = winType;

	wk->msgman_boxmes = msgman_boxmes;
	wk->msgman_boxmenu = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_boxmenu_dat, HEAPID_BOX_VIEW );

	wk->buf = STRBUF_Create( BOX_MSG_MAXLEN, HEAPID_BOX_VIEW );
	wk->expand_buf = STRBUF_Create( BOX_MSG_MAXLEN, HEAPID_BOX_VIEW );

	wk->msgwin_disp_flag = FALSE;
	wk->menuwin_disp_flag = FALSE;

	wk->bmpwin = NULL;

	wk->markCharBuf = ArcUtil_CharDataGet( ARC_BOX_GRA, NARC_box_marking_lz_ncgr, TRUE, &(wk->markCharData), HEAPID_BOX_VIEW );
	if( ( wk->markCharBuf == NULL )
	||	( wk->buf == NULL )
	||	( wk->expand_buf == NULL )
	){
		return FALSE;
	}

	return TRUE;
}
//------------------------------------------------------------------
/**
 * 終了処理
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_MsgQuit( MSG_VIEW_WORK* wk )
{
	if( wk->bmpwin )
	{
		int i;
		for(i = 0; i < WIN_MAX; i++)
		{
			GF_BGL_BmpWinDel( &(wk->bmpwin[i]) );
		}
		if( wk->markCharBuf )
		{
			sys_FreeMemoryEz( wk->markCharBuf );
		}
		if( wk->msgman_boxmenu )
		{
			MSGMAN_Delete( wk->msgman_boxmenu );
		}
		if( wk->buf )
		{
			STRBUF_Delete( wk->buf );
		}
		if( wk->expand_buf )
		{
			STRBUF_Delete( wk->expand_buf );
		}
		sys_FreeMemoryEz( wk->bmpwin );
		wk->bmpwin = NULL;
	}
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_MsgSetup( MSG_VIEW_WORK* wk )
{
	static const BMPWIN_DAT  windat[] = {
		{
			FRM_MAIN_MESSAGE,
			WIN_MSG_X, WIN_MSG_Y, WIN_MSG_WIDTH, WIN_MSG_HEIGHT,
			PAL_MAIN_WINDOW, WIN_MSG_CHAROFS
		},{
			FRM_MAIN_MESSAGE,
			WIN_MENU_X, WIN_MENU_Y, WIN_MENU_WIDTH, WIN_MENU_HEIGHT,
			PAL_MAIN_WINDOW, WIN_MENU_CHAROFS
		}
	};

	wk->bmpwin = GF_BGL_BmpWinAllocGet( HEAPID_BOX_VIEW, WIN_MAX );
	if( wk->bmpwin )
	{
		int i;

		for(i = 0; i < WIN_MAX; i++)
		{
			GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin[i], &windat[i] );
		}
	}

	ArcUtil_BgCharSet( ARC_WINFRAME, NARC_winframe_system_ncgr, wk->bgl,
			FRM_MAIN_MESSAGE, MENU_FRAME_CHAROFS, 0, FALSE, HEAPID_BOX_VIEW );

	ArcUtil_PalSet( ARC_WINFRAME, NARC_winframe_system_nclr, PALTYPE_MAIN_BG, PAL_MAIN_WINDOW_FRAME*0x20, 0x20, HEAPID_BOX_VIEW );

	TalkWinGraphicSet( wk->bgl, FRM_MAIN_MESSAGE, MSG_FRAME_CHAROFS, PAL_MAIN_MESSAGE_FRAME,
						wk->wintype,	// まだプレイヤーがウィンドウタイプを設定できるようになっていないのでゼロを渡す
						HEAPID_BOX_VIEW );

}

//------------------------------------------------------------------
/**
 * メッセージ描画
 *
 * @param   wk		
 * @param   msg_id		
 *
 */
//------------------------------------------------------------------
void BoxAppView_MsgWrite( MSG_VIEW_WORK* wk, u32 msg_id )
{
	GF_BGL_BmpWinMakeScrn( &wk->bmpwin[WIN_MSG] );

//	WinFrameScrnWrite( wk->bgl, wk->bmpwin[WIN_MSG].frmnum, wk->bmpwin[WIN_MSG].posx, wk->bmpwin[WIN_MSG].posy,
//			wk->bmpwin[WIN_MSG].sizx, wk->bmpwin[WIN_MSG].sizy );

	MsgWindowFrameWrite( wk->bgl, wk->bmpwin[WIN_MSG].frmnum, wk->bmpwin[WIN_MSG].posx, wk->bmpwin[WIN_MSG].posy,
			wk->bmpwin[WIN_MSG].sizx, wk->bmpwin[WIN_MSG].sizy );

	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_MSG], MSG_PAL_GROUND );

	MSGMAN_GetString( wk->msgman_boxmes, msg_id, wk->buf );
	WORDSET_ExpandStr( wk->wordset, wk->expand_buf, wk->buf );
	GF_STR_PrintSimple( &(wk->bmpwin[WIN_MSG]), FONT_TALK, wk->expand_buf, 0, 0, MSG_NO_PUT, NULL );

	GF_BGL_BmpWinCgxOn( &(wk->bmpwin[WIN_MSG]) );
	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );

	wk->msgwin_disp_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * メッセージウィンドウフレームをスクリーンバッファに描画
 *
 * @param   bgl		
 * @param   frm		
 * @param   posx		
 * @param   posy		
 * @param   sizx		
 * @param   sizy		
 *
 */
//------------------------------------------------------------------
static void MsgWindowFrameWrite( GF_BGL_INI* bgl, u32 frm, u32 posx, u32 posy, u32 sizx, u32 sizy )
{
	u16* scrn;
	u32 i, p;

	scrn = GF_BGL_ScreenAdrsGet( bgl, frm );
	scrn += (((posy-1)*32)+(posx-2));

// 上辺
	scrn[0] = (PAL_MAIN_MESSAGE_FRAME << 12) | MSG_FRAME_CHAROFS;
	scrn[1] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS + 1);

	for(i=0; i<sizx; i++){
		scrn[2+i] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+2);
	}

	scrn[2+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+3);
	scrn[3+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+4);
	scrn[4+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+5);

// 左右辺
	scrn += 32;
	for(i=0; i<sizy; i++){
		scrn[0] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+6);
		scrn[1] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+7);
		scrn[2+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+9);
		scrn[3+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+10);
		scrn[4+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+11);
		scrn += 32;
	}

// 下辺
	scrn[0] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+12);
	scrn[1] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+13);
	for(i=0; i<sizx; i++){
		scrn[2+i] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+14);
	}
	scrn[2+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+15);
	scrn[3+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+16);
	scrn[4+sizx] = (PAL_MAIN_MESSAGE_FRAME << 12) | (MSG_FRAME_CHAROFS+17);

}
//------------------------------------------------------------------
/**
 * メニュー描画
 *
 * @param   wk			ワークポインタ
 * @param   menu		メニュー情報データ
 * @param   cursor		初期カーソル位置
 *
 */
//------------------------------------------------------------------
void BoxAppView_MenuWrite( MSG_VIEW_WORK* wk, const BOXAPP_MENU* menu )
{
	extern void DrawCursorImage(GF_BGL_BMPWIN* win, u32 x, u32 y);

	GF_BGL_BMPWIN* win;
	u32 ypos, i;

	if( wk->menuwin_disp_flag )
	{
		MenuWinScrnErase( wk->bgl, &wk->bmpwin[WIN_MENU] );
	}

	win = &(wk->bmpwin[WIN_MENU]);

	GF_BGL_BmpWinDataFill( win, MENU_PAL_GROUND );

	ypos = (BOXAPP_MENU_ELEMS_MAX - menu->cnt) * WIN_MENU_LINE_HEIGHT;
	for(i = 0; i < menu->cnt; i++)
	{
		if( menu->id[i] >=  BOXMENU_MARK1 && menu->id[i] <= BOXMENU_MARK6 )
		{
			MarkingStatePrint( wk, win, menu->mark, menu->id[i] - BOXMENU_MARK1 );
		}
		else
		{
			MSGMAN_GetString( wk->msgman_boxmenu, mes_boxmenu_03_01 + menu->id[i], wk->buf );
			GF_STR_PrintColor( win, FONT_SYSTEM, wk->buf, WIN_MENU_WRITE_XMARGIN, ypos, MSG_NO_PUT,
								GF_PRINTCOLOR_MAKE( MENU_PAL_LETTER, MENU_PAL_SHADOW, MENU_PAL_GROUND ),
								NULL );
		}
		ypos += WIN_MENU_LINE_HEIGHT;
	}

	BoxAppView_MenuCursorUpdate( wk, menu );

	MenuWinScrnWrite( wk, menu->cnt );
	GF_BGL_BmpWinCgxOn( win );
	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );

	wk->menuwin_disp_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * マーキング状態に応じてBitmapWindowにキャラ描画
 *
 * @param   wk				ワークポインタ
 * @param   win				BitmapWindow
 * @param   mark			マーキング状態
 * @param   mark_pos		描画位置
 *
 */
//------------------------------------------------------------------
static void MarkingStatePrint( MSG_VIEW_WORK* wk, GF_BGL_BMPWIN* win, u8 mark, u32 pos )
{
	GF_BGL_BmpWinPrintEx( win, wk->markCharData->pRawData, 
					pos*8, ((mark & (1<<pos))? 0 : 8),
					48, 16,
					WIN_MENU_MARKING_XMARGIN, pos*WIN_MENU_LINE_HEIGHT+WIN_MENU_MARKING_YMARGIN,
					8, 8,
					0xff );
}
//------------------------------------------------------------------
/**
 * メニュー項目数に合わせてウィンドウスクリーン描画
 *
 * @param   elems		
 *
 */
//------------------------------------------------------------------
static void MenuWinScrnWrite( MSG_VIEW_WORK* wk, u32 elems )
{
	u16* scrn;
	u32 x, y,  charno, skip;

	scrn = GF_BGL_ScreenAdrsGet( wk->bgl, FRM_MAIN_MESSAGE );
	scrn += (WIN_MENU_Y * 32 + WIN_MENU_X);
	charno = WIN_MENU_CHAROFS;

	skip = BOXAPP_MENU_ELEMS_MAX - elems;
	scrn += (skip * 2 * 32);
	charno += (skip * 2 * WIN_MENU_WIDTH);

	for(y = 0; y < (elems*2); y++)
	{
		for(x = 0; x < WIN_MENU_WIDTH; x++)
		{
			scrn[x] = (PAL_MAIN_WINDOW << 12) | charno;
			charno++;
		}
		scrn += 32;
	}

	WinFrameScrnWrite( wk->bgl, FRM_MAIN_MESSAGE, WIN_MENU_X, WIN_MENU_Y+skip*2, WIN_MENU_WIDTH, elems*2 );
}
//------------------------------------------------------------------
/**
 * メッセージ・メニュー消去
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_MsgClear( MSG_VIEW_WORK* wk )
{
	if( wk->msgwin_disp_flag )
	{
		MsgWinScrnErase( wk->bgl, &wk->bmpwin[WIN_MSG] );
		wk->msgwin_disp_flag = FALSE;
	}
	if( wk->menuwin_disp_flag )
	{
		MenuWinScrnErase( wk->bgl, &wk->bmpwin[WIN_MENU] );
		wk->menuwin_disp_flag = FALSE;
	}
	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );
}

//------------------------------------------------------------------
/**
 * メニューのみ消去
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_MenuClear( MSG_VIEW_WORK* wk )
{
	if( wk->menuwin_disp_flag )
	{
		MenuWinScrnErase( wk->bgl, &wk->bmpwin[WIN_MENU] );
		wk->menuwin_disp_flag = FALSE;
	}
	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_MESSAGE );
}

//------------------------------------------------------------------
/**
 * カーソル位置更新
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_MenuCursorUpdate( MSG_VIEW_WORK* wk, const BOXAPP_MENU* menu )
{
	GF_BGL_BMPWIN* win;
	u32 pos;

	win = &(wk->bmpwin[WIN_MENU]);
	pos = (BOXAPP_MENU_ELEMS_MAX - menu->cnt) * WIN_MENU_LINE_HEIGHT;

	GF_BGL_BmpWinFill( win, MENU_PAL_GROUND, 0, pos, WIN_MENU_WRITE_XMARGIN, menu->cnt * WIN_MENU_LINE_HEIGHT );
	BmpWin_DrawCursorImage( win, 0, pos + (menu->pos * WIN_MENU_LINE_HEIGHT));

	GF_BGL_BmpWinCgxOn( win );
}

//------------------------------------------------------------------
/**
 * マーキング表示更新
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_MenuMarkUpdate( MSG_VIEW_WORK* wk, const BOXAPP_MENU* menu )
{
	GF_BGL_BMPWIN* win;
	int i;

	win = &(wk->bmpwin[WIN_MENU]);
	for(i=0; i<BOX_MARK_MAX; i++)
	{
		MarkingStatePrint( wk, win, menu->mark, i );
	}
	GF_BGL_BmpWinCgxOn( win );
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   bgl			
 * @param   frm			
 * @param   posx		
 * @param   posy		
 * @param   sizx		
 * @param   sizy		
 *
 */
//------------------------------------------------------------------
static void WinFrameScrnWrite( GF_BGL_INI* bgl, u32 frm, u32 posx, u32 posy, u32 sizx, u32 sizy )
{
	u16* scrn;
	u32 i;

	scrn = GF_BGL_ScreenAdrsGet( bgl, frm );

	scrn += (((posy-1)*32)+(posx-1));
	*scrn = (PAL_MAIN_WINDOW_FRAME << 12) | MENU_FRAME_CHAROFS;
	for(i=0; i<sizx; i++){
		scrn[i+1] = (PAL_MAIN_WINDOW_FRAME << 12) | (MENU_FRAME_CHAROFS+1);
	}
	scrn[sizx+1] = (PAL_MAIN_WINDOW_FRAME << 12) | (MENU_FRAME_CHAROFS+2);

	scrn += 32;
	for(i=0; i<sizy; i++){
		*scrn = (PAL_MAIN_WINDOW_FRAME << 12) | (MENU_FRAME_CHAROFS+3);
		scrn[sizx+1] = (PAL_MAIN_WINDOW_FRAME << 12) | (MENU_FRAME_CHAROFS+5);
		scrn += 32;
	}

	*scrn = (PAL_MAIN_WINDOW_FRAME << 12) | (MENU_FRAME_CHAROFS+6);
	for(i=0; i<sizx; i++){
		scrn[i+1] = (PAL_MAIN_WINDOW_FRAME << 12) | (MENU_FRAME_CHAROFS+7);
	}
	scrn[sizx+1] = (PAL_MAIN_WINDOW_FRAME << 12) | (MENU_FRAME_CHAROFS+8);

}
//------------------------------------------------------------------
/**
 * メニューウィンドウ周辺に配置されているフレームのスクリーンデータごと
 * バッファクリア（転送は行わない）
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
static void MenuWinScrnErase( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win )
{
	u16* scrn;
	u32 x, y, sizx, sizy;

	scrn = GF_BGL_ScreenAdrsGet( bgl, win->frmnum );
	scrn += (((win->posy-1)*32)+(win->posx-1));

	for(y=0; y<(win->sizy+2); y++)
	{
		for(x=0; x<(win->sizx+2); x++)
		{
			scrn[x] = 0x0000;
		}
		scrn += 32;
	}
}
//------------------------------------------------------------------
/**
 * メッセージウィンドウ周辺に配置されているフレームのスクリーンデータごと
 * バッファクリア（転送は行わない）
 *
 * @param   win		
 *
 */
//------------------------------------------------------------------
static void MsgWinScrnErase( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win )
{
	u16* scrn;
	u32 x, y, sizx, sizy;

	scrn = GF_BGL_ScreenAdrsGet( bgl, win->frmnum );
	scrn += (((win->posy-1)*32)+(win->posx-2));

	for(y=0; y<(win->sizy+2); y++)
	{
		for(x=0; x<(win->sizx+5); x++)
		{
			scrn[x] = 0x0000;
		}
		scrn += 32;
	}
}

