//============================================================================================
/**
 * @file	poketch_a25.h
 * @bfief	ポケッチ（アプリNo25:カレンダー）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A25_H_
#define _POKETCH_A25_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_UPDATE,
};

enum {
	TOUCH_SCRN_X_ORG = 4,
	TOUCH_SCRN_Y_ORG = 5,
	TOUCH_SCRN_X_DIFF = 3,
	TOUCH_SCRN_Y_DIFF = 3,
	TOUCH_SCRN_X_RANGE = 2,
	TOUCH_SCRN_Y_RANGE = 2,
};

#define TOUCH_TOP(y)	(( TOUCH_SCRN_Y_ORG + TOUCH_SCRN_Y_DIFF*(y) ) * 8)
#define TOUCH_BOTTOM(y)	(( TOUCH_SCRN_Y_ORG + TOUCH_SCRN_Y_DIFF*(y) + TOUCH_SCRN_Y_RANGE) * 8)
#define TOUCH_LEFT(x)	(( TOUCH_SCRN_X_ORG + TOUCH_SCRN_X_DIFF*(x) ) * 8)
#define TOUCH_RIGHT(x)	(( TOUCH_SCRN_X_ORG + TOUCH_SCRN_X_DIFF*(x) + TOUCH_SCRN_X_RANGE) * 8)


//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	

	u32    month;				// 1～12
	u32    last_day;			// 28～31
	u32    today;				// 1～31

	struct  {
		u16  day;
		u8   pos;
		u8   mark;
	}day_param[31];

	u32		update_day;


}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A25_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A25_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A25_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A25_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A25_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A25_DeleteViewWork(VIEWWORK* wk);

#endif
