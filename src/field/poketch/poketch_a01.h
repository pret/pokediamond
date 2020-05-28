//============================================================================================
/**
 * @file	poketch_a01.h
 * @bfief	ポケッチ（アプリNo01）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A01_H_
#define _POKETCH_A01_H_

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_BTN_UPDATE,
	CMD_COUNTER_UPDATE,
	CMD_QUIT,
};
//====================================================
// ボタン状態
//====================================================
typedef enum {
	BTN_STATE_FREE,
	BTN_STATE_TOUCH,
	BTN_STATE_COUNT,
	BTN_STATE_RESET1,
	BTN_STATE_RESET2,
	BTN_STATE_BOMB,
	BTN_STATE_BURN,

	BTN_STATE_QUIT,
}BTN_STATE;

//====================================================
// 描画パラメータ
//====================================================
typedef struct {

	BOOL counter_action_flag;
	BOOL counter_reset_flag;

	u32  msec;
	u32  sec;
	u32  min;
	u32  hour;

	BTN_STATE	btn;

}POKETCH_A01_VIEW_PARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A01_VIEWWORK  POKETCH_A01_VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A01_SetViewWork(POKETCH_A01_VIEWWORK **wk_ptr, const POKETCH_A01_VIEW_PARAM *vpara, GF_BGL_INI* bgl);
extern void Poketch_A01_SetViewCommand(POKETCH_A01_VIEWWORK *wk, u32 cmd);
extern BOOL Poketch_A01_WaitViewCommand(POKETCH_A01_VIEWWORK *wk, u32 cmd);
extern BOOL Poketch_A01_WaitViewCommandAll(POKETCH_A01_VIEWWORK *wk);
extern void Poketch_A01_DeleteViewWork( POKETCH_A01_VIEWWORK* wk );

#endif
