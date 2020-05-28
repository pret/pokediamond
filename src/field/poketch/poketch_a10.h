//============================================================================================
/**
 * @file	poketch_a10.h
 * @bfief	ポケッチ（アプリNo10:万歩計）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A10_H_
#define _POKETCH_A10_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_BUTTON_UPDATE,
	CMD_COUNTER_UPDATE,
};


enum {
	BUTTON_STATE_TOUCH,
	BUTTON_STATE_FREE,
};


enum {
	BUTTON_CENTER_X = 114,
	BUTTON_CENTER_Y = 128,

	BUTTON_WIDTH = 64,
	BUTTON_HEIGHT = 56,
};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u32   counter;
	u32   button_state;
}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A10_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A10_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A10_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A10_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A10_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A10_DeleteViewWork(VIEWWORK* wk);

#endif
