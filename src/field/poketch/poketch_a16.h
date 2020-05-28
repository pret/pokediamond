//============================================================================================
/**
 * @file	poketch_a16.h
 * @bfief	ポケッチ（アプリNo16:ルーレット）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A16_H_
#define _POKETCH_A16_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_PIXEL_UPDATE,
	CMD_PIXEL_SET,
	CMD_PIXEL_SET_END,

	CMD_UPDATE_BUTTON,
	CMD_CLEAR_PIXELS,
	CMD_START_ARROW,
	CMD_STOP_ARROW,
};

//====================================================
// 定数
//====================================================
enum {
	BUTTON_START_X = 187,
	BUTTON_START_Y = 50,
	BUTTON_STOP_X = 187,
	BUTTON_STOP_Y = 96,
	BUTTON_CLEAR_X = 187,
	BUTTON_CLEAR_Y = 142,

	BUTTON_TOUCH_RANGE_X = 40,
	BUTTON_TOUCH_RANGE_Y = 32,

	BUTTON_START_TOP    = BUTTON_START_Y - (BUTTON_TOUCH_RANGE_Y/2),
	BUTTON_START_BOTTOM = BUTTON_START_Y + (BUTTON_TOUCH_RANGE_Y/2),
	BUTTON_START_LEFT   = BUTTON_START_X - (BUTTON_TOUCH_RANGE_X/2),
	BUTTON_START_RIGHT  = BUTTON_START_X + (BUTTON_TOUCH_RANGE_X/2),
	BUTTON_STOP_TOP     = BUTTON_STOP_Y - (BUTTON_TOUCH_RANGE_Y/2),
	BUTTON_STOP_BOTTOM  = BUTTON_STOP_Y + (BUTTON_TOUCH_RANGE_Y/2),
	BUTTON_STOP_LEFT    = BUTTON_STOP_X - (BUTTON_TOUCH_RANGE_X/2),
	BUTTON_STOP_RIGHT   = BUTTON_STOP_X + (BUTTON_TOUCH_RANGE_X/2),
	BUTTON_CLEAR_TOP    = BUTTON_CLEAR_Y - (BUTTON_TOUCH_RANGE_Y/2),
	BUTTON_CLEAR_BOTTOM = BUTTON_CLEAR_Y + (BUTTON_TOUCH_RANGE_Y/2),
	BUTTON_CLEAR_LEFT   = BUTTON_CLEAR_X - (BUTTON_TOUCH_RANGE_X/2),
	BUTTON_CLEAR_RIGHT  = BUTTON_CLEAR_X + (BUTTON_TOUCH_RANGE_X/2),

};


enum TOUCH_MODE {
	TOUCHMODE_ERASER,
	TOUCHMODE_PEN,
};

enum {
	PIXEL_H_MAX = 156,
	PIXEL_V_MAX = 150,
};


//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u32  pixel_update_x;
	u32  pixel_update_y;
	u32  appNumber;

	u8   pixel[PIXEL_H_MAX][PIXEL_V_MAX];

	u8   start_button;
	u8   stop_button;
	u8   clear_button;

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A16_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A16_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A16_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A16_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A16_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A16_DeleteViewWork(VIEWWORK* wk);
extern BOOL Poketch_A16_WaitArrowMaxSpeed( VIEWWORK* wk );

#endif
