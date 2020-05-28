//============================================================================================
/**
 * @file	poketch_a11.h
 * @bfief	ポケッチ（アプリNo11:バックライトスイッチ）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A11_H_
#define _POKETCH_A11_H_

#include "poketch_prv.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_UPDATE,
};

//====================================================
// ボタン位置
//====================================================
enum {
	BUTTON_CENTER_X = POKETCH_MONITOR_CENTER_X,
	BUTTON_CENTER_Y = 104,

	BUTTON_TOUCHAREA_HEIGHT = 32,
	BUTTON_TOUCHAREA_WIDTH  = 40,

	BUTTON_ON_CENTER_Y = BUTTON_CENTER_Y - 16,
	BUTTON_OFF_CENTER_Y = BUTTON_CENTER_Y + 16,

	BUTTON_ON_TOP     = BUTTON_ON_CENTER_Y - (BUTTON_TOUCHAREA_HEIGHT/2),
	BUTTON_ON_BOTTOM  = BUTTON_ON_CENTER_Y + (BUTTON_TOUCHAREA_HEIGHT/2),
	BUTTON_ON_LEFT    = BUTTON_CENTER_X - (BUTTON_TOUCHAREA_WIDTH/2),
	BUTTON_ON_RIGHT   = BUTTON_CENTER_X + (BUTTON_TOUCHAREA_WIDTH/2),

	BUTTON_OFF_TOP     = BUTTON_OFF_CENTER_Y - (BUTTON_TOUCHAREA_HEIGHT/2),
	BUTTON_OFF_BOTTOM  = BUTTON_OFF_CENTER_Y + (BUTTON_TOUCHAREA_HEIGHT/2),
	BUTTON_OFF_LEFT    = BUTTON_CENTER_X - (BUTTON_TOUCHAREA_WIDTH/2),
	BUTTON_OFF_RIGHT   = BUTTON_CENTER_X + (BUTTON_TOUCHAREA_WIDTH/2),

};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	BOOL	switch_on;

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A11_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A11_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A11_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A11_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A11_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A11_DeleteViewWork(VIEWWORK* wk);

#endif
