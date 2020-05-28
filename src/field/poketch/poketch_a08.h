//============================================================================================
/**
 * @file	poketch_a08.h
 * @bfief	ポケッチ（アプリNo08:ダウジングマシン）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A08_H_
#define _POKETCH_A08_H_

#include "field\script.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_RIPPLE_START,
};

//====================================================
// 定数
//====================================================
enum {
	FIND_POS_MAX = 8,		///< 位置判明アイテムの表示最大数


	HIT_GRID_MAX_X = ((HIDE_LIST_SX*2)+1),
	HIT_GRID_MAX_Y = ((HIDE_LIST_BOTTOM+HIDE_LIST_TOP)+1),

	ITEM_ICON_DIFF_X = 11,
	ITEM_ICON_DIFF_Y = 11,


	TOUCH_RANGE_LEFT = 24,
	TOUCH_RANGE_TOP = 24,
	TOUCH_RANGE_RIGHT = 200,
	TOUCH_RANGE_BOTTOM = 168,

	TOUCH_RANGE_CENTER_X = 112,
	TOUCH_RANGE_CENTER_Y = 101,


};


typedef enum {
	FIND_PATTERN_NONE,		///< アイテム発見できず
	FIND_PATTERN_EXIST,		///< アイテム発見。位置までは不明。
	FIND_PATTERN_POS,		///< アイテム発見。位置も判明。
}ITEM_FIND_PATTERN;

//====================================================
// アイテム発見位置
//====================================================
typedef struct {
	u16   x;
	u16   y;
	u16   lv;
}FIND_ITEM_POS;

//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u32  touch_x;
	u32  touch_y;
	ITEM_FIND_PATTERN  find_pattern;

	u32  find_pos_count;
	FIND_ITEM_POS  find_pos[ FIND_POS_MAX ];

	BOOL anm_stop_flag;

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A08_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A08_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A08_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A08_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A08_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A08_DeleteViewWork(VIEWWORK* wk);

extern void Poketch_A08_CalcGlidToLcdPos( int glid_x, int glid_y, int* lcd_x, int* lcd_y );


extern void Poketch_A08_StopRippleAnm( VIEWWORK* wk );

#endif
