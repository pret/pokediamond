//============================================================================================
/**
 * @file	poketch_a28.h
 * @bfief	ポケッチ（アプリNo28：ポケモンカウンター）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A28_H_
#define _POKETCH_A28_H_

#include "poketch_prv.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_UPDATE,
	CMD_TOUCH,
};

//====================================================
// アイコン配置
//====================================================
enum {
	ICON_NOW_XPOS = POKETCH_MONITOR_DOT_XORG + 80,
	ICON_NOW_YPOS = POKETCH_MONITOR_DOT_YORG + 16,

	ICON_RANK1_XPOS = POKETCH_MONITOR_DOT_XORG + 96,
	ICON_RANK1_YPOS = POKETCH_MONITOR_DOT_YORG + 64,
	ICON_RANK2_XPOS = ICON_RANK1_XPOS + 64,
	ICON_RANK2_YPOS = ICON_RANK1_YPOS + 16,
	ICON_RANK3_XPOS = ICON_RANK1_XPOS - 64,
	ICON_RANK3_YPOS = ICON_RANK1_YPOS + 24,

	ICON_TOUCH_WIDTH = 48,
	ICON_TOUCH_HEIGHT = 36,
};

#define ICON_TOP(y)		((y)-(ICON_TOUCH_HEIGHT/2))
#define ICON_BOTTOM(y)	((y)+(ICON_TOUCH_HEIGHT/2))
#define ICON_LEFT(x)	((x)-(ICON_TOUCH_WIDTH/2))
#define ICON_RIGHT(x)	((x)+(ICON_TOUCH_WIDTH/2))



//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	int now_monsno;
	int now_count;

	int rank_monsno[3];
	int rank_count[3];

	int rank_max;
	int touch_poke;

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A28_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A28_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A28_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A28_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A28_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A28_DeleteViewWork(VIEWWORK* wk);

#endif
