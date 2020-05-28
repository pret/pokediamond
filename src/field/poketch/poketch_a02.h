//============================================================================================
/**
 * @file	poketch_a02.h
 * @bfief	ポケッチ（アプリNo02：電卓）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A02_H_
#define _POKETCH_A02_H_

#include "poketch_realnum.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_BUTTON_PUSH,
	CMD_BUTTON_FREE,
	CMD_DISPNUM_1,
	CMD_DISPNUM_1_OPCLEAR,
	CMD_DISPNUM_2,
	CMD_DISPNUM_ANS,
	CMD_DISPNUM_ANS_OP,
	CMD_OPERATION,
	CMD_OVERFLOW,
	CMD_QUIT,

};

//====================================================
// ボタンＩＤ
//====================================================
typedef enum {
	BUTTON_0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,
	BUTTON_DOT,
	BUTTON_MINUS,
	BUTTON_PLUS,
	BUTTON_MUL,
	BUTTON_DIV,
	BUTTON_EQ,
	BUTTON_CLEAR,

	BUTTON_ID_MAX,

	BUTTON_ID_NULL = BUTTON_ID_MAX,
}BUTTON_ID;

typedef enum {
	OP_MINUS = BUTTON_MINUS,
	OP_PLUS = BUTTON_PLUS,
	OP_MUL = BUTTON_MUL,
	OP_DIV = BUTTON_DIV,
	OP_NULL = BUTTON_ID_MAX,

}OPERATION_CODE;

//====================================================
// その他の定数
//====================================================
enum {
	DISP_COLUMN_MAX = 10,		// 表示最大桁（マイナスや小数点も合わせて）
};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u16 btn_id;
	u16 operation;

	REAL_NUMBER *num1;
	REAL_NUMBER *num2;
	REAL_NUMBER *ans;

}POKETCH_A02_VIEW_PARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A02_VIEWWORK  POKETCH_A02_VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
BOOL Poketch_A02_SetViewWork(POKETCH_A02_VIEWWORK **wk_ptr, const POKETCH_A02_VIEW_PARAM *vpara, GF_BGL_INI* bgl);
extern void Poketch_A02_SetViewCommand(POKETCH_A02_VIEWWORK *wk, u32 cmd);
extern BOOL Poketch_A02_WaitViewCommand(POKETCH_A02_VIEWWORK *wk, u32 cmd);
extern BOOL Poketch_A02_WaitViewCommandAll(POKETCH_A02_VIEWWORK *wk);
extern void Poketch_AOO_DeleteViewWork( POKETCH_A02_VIEWWORK* wk );

#endif
