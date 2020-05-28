//============================================================================================
/**
 * @file	demo_ending_list.c
 * @brief	エンディングデモ　スタッフリスト処理
 * @author	taya
 * @date	2006.05.22
 */
//============================================================================================
#include "common.h"
#include "gflib\bg_system.h"
#include "gflib\strbuf.h"
#include "system\fontproc.h"

#include "demo_ending_common.h"
#include "demo_ending_list.h"



#define __STAFFLIST_DAT__
#include "stafflist.dat"

enum {
	STRBUF_SIZE = 256,
	LIST_PRINT_OX = 32,
	LIST_PRINT_FONT = FONT_SYSTEM,
	LIST_LINE_HEIGHT = 16,

	WINDOW_WIDTH = 32,
	WINDOW_HEIGHT = 32,

};


typedef enum {
	LISTSEQ_READ,		///< まだ読む
	LISTSEQ_ALLREAD,	///< もう読むものが無い
	LISTSEQ_ALLOUT,		///< もう全部スクロールアウトした
}LISTSEQ;



struct _ENDING_LIST_WORK {
	int		topLine;
	int		bottomLine;
	int		bgFrame;

	int		nextDispListPos;
	int		nextEraseListPos;
	BOOL	listEndFlag;
	BOOL	transReq;

	LISTSEQ	listSeq;

	GF_BGL_INI*		bgl;
	GF_BGL_BMPWIN*	win;
	GF_BGL_BMPWIN*	tmpwin;

	MSGDATA_MANAGER*	msgMan;
	STRBUF*		strbuf;

	TCB_PTR		task;
};




//==============================================================
// Prototype
//==============================================================
static void ListWorkTask( TCB_PTR tcb, void* wk_adrs );




//------------------------------------------------------------------
/**
 * リスト処理ワーク作成
 *
 * @param   bgl				
 * @param   startLine		
 * @param   bgFrame		
 * @param   msgMan		
 *
 * @retval  ENDING_LIST_WORK*		
 */
//------------------------------------------------------------------
ENDING_LIST_WORK* Ending_ListWork_Create( GF_BGL_INI* bgl, int startLine, int bgFrame, int palPos, MSGDATA_MANAGER* msgMan )
{
	ENDING_LIST_WORK* wk = sys_AllocMemory( HEAPID_ENDING_DEMO, sizeof(ENDING_LIST_WORK) );
	if( wk )
	{
		wk->bgl = bgl;
		wk->topLine = startLine;
		wk->bottomLine = startLine + 192;
		wk->bgFrame = bgFrame;
		wk->msgMan = msgMan;

		wk->nextDispListPos = 0;
		wk->nextEraseListPos = 0;
		wk->listEndFlag = FALSE;
		wk->transReq = FALSE;

		wk->listSeq = LISTSEQ_READ;

		wk->strbuf = STRBUF_Create( STRBUF_SIZE, HEAPID_ENDING_DEMO );

		wk->win = GF_BGL_BmpWinAllocGet( HEAPID_ENDING_DEMO, 1 );
		GF_BGL_BmpWinAdd( bgl, wk->win, bgFrame, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, palPos, 0 );
		GF_BGL_BmpWinDataFill( wk->win, 0x00 );
		GF_BGL_BmpWinMakeScrn( wk->win );
		GF_BGL_BmpWinOn( wk->win );

		wk->tmpwin = GF_BGL_BmpWinAllocGet( HEAPID_ENDING_DEMO, 1 );
		GF_BGL_BmpWinAdd( bgl, wk->tmpwin, bgFrame, 0, 0, WINDOW_WIDTH, 2, palPos, 0 );

		wk->task = VWaitTCB_Add( ListWorkTask, wk, 0 );
	}
	return wk;
}

//------------------------------------------------------------------
/**
 * リスト処理ワーク削除
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void Ending_ListWork_Delete( ENDING_LIST_WORK* wk )
{
	if( wk->task )
	{
		TCB_Delete( wk->task );
	}

	STRBUF_Delete( wk->strbuf );

	GF_BGL_BmpWinDel( wk->win );
	GF_BGL_BmpWinDel( wk->tmpwin );

	sys_FreeMemoryEz( wk->win );
	sys_FreeMemoryEz( wk->tmpwin );
	sys_FreeMemoryEz( wk );
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 * @param   height		
 *
 */
//------------------------------------------------------------------
BOOL Ending_ListWork_Scroll( ENDING_LIST_WORK* wk, int height )
{
	if( wk->listSeq == LISTSEQ_ALLOUT )
	{
		return TRUE;
	}
	else
	{
		int  nextBottomLine = wk->bottomLine + height;

		if( wk->listSeq == LISTSEQ_READ )
		{
			if( nextBottomLine >= StaffListDataTable[wk->nextDispListPos].height )
			{
				int xpos, ypos;

				MSGMAN_GetString( wk->msgMan, StaffListDataTable[wk->nextDispListPos].strID, wk->strbuf );
				if( StaffListDataTable[wk->nextDispListPos].centeringFlag )
				{
					xpos = (256 - FontProc_GetPrintStrWidth( LIST_PRINT_FONT, wk->strbuf, 0 )) / 2;
				}
				else
				{
					xpos = LIST_PRINT_OX;
				}

				ypos = StaffListDataTable[wk->nextDispListPos].height & 0xff;
				GF_STR_PrintColor( wk->win, LIST_PRINT_FONT, wk->strbuf, xpos, ypos,
					 MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0), NULL );

				if( ypos > (256 - LIST_LINE_HEIGHT) )
				{
					GF_BGL_BmpWinDataFill( wk->tmpwin, 0x00 );
					GF_STR_PrintColor( wk->tmpwin, LIST_PRINT_FONT, wk->strbuf, xpos, 0,
						MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,0), NULL );

					ypos = (LIST_LINE_HEIGHT) - (ypos - (256-LIST_LINE_HEIGHT));
					GF_BGL_BmpWinPrint( wk->win, wk->tmpwin->chrbuf, 0, ypos, wk->tmpwin->sizx*8, wk->tmpwin->sizy*8,
						0, 0, WINDOW_WIDTH*8, (LIST_LINE_HEIGHT-ypos) );
				}

				wk->transReq = TRUE;

				if( ++(wk->nextDispListPos) >= (NELEMS(StaffListDataTable)-1) )
				{
					wk->listSeq = LISTSEQ_ALLREAD;
				}
			}
		}
		wk->bottomLine = nextBottomLine;

		if( wk->topLine > (StaffListDataTable[wk->nextEraseListPos].height + LIST_LINE_HEIGHT) )
		{
			int ypos = StaffListDataTable[wk->nextEraseListPos].height & 0xff;

			if( ypos <= (256 - LIST_LINE_HEIGHT) )
			{
				GF_BGL_BmpWinFill( wk->win, 0x00, 0, ypos, WINDOW_WIDTH*8, LIST_LINE_HEIGHT );
			}
			else
			{
				int  a_h, b_h;
				a_h = LIST_LINE_HEIGHT - (ypos - (256-LIST_LINE_HEIGHT));
				b_h = LIST_LINE_HEIGHT - a_h;
				GF_BGL_BmpWinFill( wk->win, 0x00, 0, ypos, WINDOW_WIDTH*8, a_h );
				GF_BGL_BmpWinFill( wk->win, 0x00, 0, 0, WINDOW_WIDTH*8, b_h );
			}

			wk->transReq = TRUE;

			if( ++(wk->nextEraseListPos) >= NELEMS(StaffListDataTable) )
			{
				wk->listSeq = LISTSEQ_ALLOUT;
			}
		}
		wk->topLine += height;

		return FALSE;
	}
}




static void ListWorkTask( TCB_PTR tcb, void* wk_adrs )
{
	ENDING_LIST_WORK* wk = wk_adrs;

	if( wk->transReq )
	{
		GF_BGL_BmpWinCgxOn( wk->win );
		wk->transReq = FALSE;
	}

	{
		int pos = wk->topLine & 255;
		GF_BGL_ScrollSet( wk->bgl, wk->bgFrame, GF_BGL_SCROLL_Y_SET, pos );
	}
}



//================================================================================
//================================================================================
enum {
	ENDSTR_YPOS = 80,
	ENDSTR_LETTER_SPACE = 3,
};


//------------------------------------------------------------------
/**
 * リストスクロールアウト後に呼ばれ、「おわり」の文字を描画する
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void Ending_ListWork_WriteEndStr( ENDING_LIST_WORK* wk, BOOL fillFlag )
{
	GF_PRINTCOLOR  color;
	int p, xpos;

	wk->listSeq = LISTSEQ_ALLOUT;

	p = NELEMS(StaffListDataTable) - 1;

	if( fillFlag )
	{
		GF_BGL_BmpWinDataFill( wk->win, 15 );
		color = GF_PRINTCOLOR_MAKE(1,2,15);
	}
	else
	{
		color = GF_PRINTCOLOR_MAKE(1,2,0);
	}

	MSGMAN_GetString( wk->msgMan, StaffListDataTable[p].strID, wk->strbuf );
	xpos = (256 - FontProc_GetPrintStrWidth( LIST_PRINT_FONT, wk->strbuf, 0 )) / 2;

	wk->topLine = 0;
	GF_STR_PrintExpand( wk->win, LIST_PRINT_FONT, wk->strbuf, xpos, ENDSTR_YPOS,
			MSG_NO_PUT, color, ENDSTR_LETTER_SPACE, 0, NULL );

	GF_BGL_BmpWinCgxOn( wk->win );

}

//------------------------------------------------------------------
/**
 * スキップ時に呼ばれ、著作権表記の描画
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void Ending_ListWork_WriteCopyLights( ENDING_LIST_WORK* wk )
{
	wk->listSeq = LISTSEQ_ALLOUT;
	wk->topLine = 0;

	ArcUtil_ScrnSet( ARC_ENDING, NARC_ending_reserve_nscr, wk->bgl, wk->bgFrame, 0, 0, FALSE, HEAPID_ENDING_DEMO );
	ArcUtil_BgCharSet( ARC_ENDING, NARC_ending_reserve_ncgr, wk->bgl, wk->bgFrame, 0, 0, FALSE, HEAPID_ENDING_DEMO );
	ArcUtil_PalSet( ARC_ENDING, NARC_ending_reserve_nclr, PALTYPE_MAIN_BG, 0, 0x20, HEAPID_ENDING_DEMO );
}
