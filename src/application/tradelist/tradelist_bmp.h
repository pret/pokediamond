//============================================================================================
/**
 * @file	tradelist_bmp.h
 * @bfief	ポケモン交換リスト画面BMP処理ヘッダ
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================

#ifndef __TRADELIST_BMP_H__
#define __TRADELIST_BMP_H__

extern void TradeList_BmpMessageSet(GF_BGL_INI *bgl, GF_BGL_BMPWIN *TradeListWin, CONFIG *config);
extern void TradeListBmpExit(GF_BGL_BMPWIN *win);
extern void TradeListPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int bmp_width, u32 wait, int print_sw, int y);
extern int TradeListWindowPrint(GF_BGL_BMPWIN *win, int msg, int font, MSGDATA_MANAGER *Man, WORDSET *WordSet);
extern u32  TradeListYesNoFunc(GF_BGL_INI * bgl, BMPMENU_WORK **menu, int *seq);
extern void TradeListWinWrite(GF_BGL_BMPWIN *win);
extern BMPLIST_WORK* TradeListMenuInit(BMPLIST_DATA* menulist, int count,GF_BGL_BMPWIN* pWin,GF_BGL_INI* bgl );

#endif