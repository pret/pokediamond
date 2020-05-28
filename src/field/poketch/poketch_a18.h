//============================================================================================
/**
 * @file	poketch_a18.h
 * @bfief	ポケッチ（アプリNo18:わざ相性チェッカー）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A18_H_
#define _POKETCH_A18_H_

#include "battle\battle_common.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_BUTTON_PUSH,
	CMD_BUTTON_RELEASE,
	CMD_UPDATE_EFFECT,
};

//====================================================
// ボタンＩＤ
//====================================================
enum {
	BUTTON_ID_ATTACK_L,
	BUTTON_ID_ATTACK_R,
	BUTTON_ID_DEFENCE0_L,
	BUTTON_ID_DEFENCE0_R,
	BUTTON_ID_DEFENCE1_L,
	BUTTON_ID_DEFENCE1_R,
};
//====================================================
// ボタンレイアウト
//====================================================
enum {
	// ボタンサイズ（ドット）
	BUTTON_WIDTH = 24,
	BUTTON_HEIGHT = 32,

	// ボタン中心（アクター配置用）
	BUTTON_ATTACK_L_X = 28,
	BUTTON_ATTACK_L_Y = 128,
	BUTTON_ATTACK_R_X = 116,
	BUTTON_ATTACK_R_Y = 128,

	BUTTON_DEFENCE0_L_X = 108,
	BUTTON_DEFENCE0_L_Y = 40,
	BUTTON_DEFENCE0_R_X = 196,
	BUTTON_DEFENCE0_R_Y = 40,

	BUTTON_DEFENCE1_L_X = 108,
	BUTTON_DEFENCE1_L_Y = 72,
	BUTTON_DEFENCE1_R_X = 196,
	BUTTON_DEFENCE1_R_Y = 72,

	// ボタン反応範囲（タッチパネル用）
	BUTTON_ATTACK_L_TOP    = BUTTON_ATTACK_L_Y - (BUTTON_HEIGHT/2),
	BUTTON_ATTACK_L_BOTTOM = BUTTON_ATTACK_L_Y + (BUTTON_HEIGHT/2),
	BUTTON_ATTACK_L_LEFT   = BUTTON_ATTACK_L_X - (BUTTON_WIDTH/2),
	BUTTON_ATTACK_L_RIGHT  = BUTTON_ATTACK_L_X + (BUTTON_WIDTH/2),
	BUTTON_ATTACK_R_TOP    = BUTTON_ATTACK_R_Y - (BUTTON_HEIGHT/2),
	BUTTON_ATTACK_R_BOTTOM = BUTTON_ATTACK_R_Y + (BUTTON_HEIGHT/2),
	BUTTON_ATTACK_R_LEFT   = BUTTON_ATTACK_R_X - (BUTTON_WIDTH/2),
	BUTTON_ATTACK_R_RIGHT  = BUTTON_ATTACK_R_X + (BUTTON_WIDTH/2),

	BUTTON_DEFENCE0_L_TOP    = BUTTON_DEFENCE0_L_Y - (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE0_L_BOTTOM = BUTTON_DEFENCE0_L_Y + (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE0_L_LEFT   = BUTTON_DEFENCE0_L_X - (BUTTON_WIDTH/2),
	BUTTON_DEFENCE0_L_RIGHT  = BUTTON_DEFENCE0_L_X + (BUTTON_WIDTH/2),
	BUTTON_DEFENCE0_R_TOP    = BUTTON_DEFENCE0_R_Y - (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE0_R_BOTTOM = BUTTON_DEFENCE0_R_Y + (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE0_R_LEFT   = BUTTON_DEFENCE0_R_X - (BUTTON_WIDTH/2),
	BUTTON_DEFENCE0_R_RIGHT  = BUTTON_DEFENCE0_R_X + (BUTTON_WIDTH/2),

	BUTTON_DEFENCE1_L_TOP    = BUTTON_DEFENCE1_L_Y - (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE1_L_BOTTOM = BUTTON_DEFENCE1_L_Y + (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE1_L_LEFT   = BUTTON_DEFENCE1_L_X - (BUTTON_WIDTH/2),
	BUTTON_DEFENCE1_L_RIGHT  = BUTTON_DEFENCE1_L_X + (BUTTON_WIDTH/2),
	BUTTON_DEFENCE1_R_TOP    = BUTTON_DEFENCE1_R_Y - (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE1_R_BOTTOM = BUTTON_DEFENCE1_R_Y + (BUTTON_HEIGHT/2),
	BUTTON_DEFENCE1_R_LEFT   = BUTTON_DEFENCE1_R_X - (BUTTON_WIDTH/2),
	BUTTON_DEFENCE1_R_RIGHT  = BUTTON_DEFENCE1_R_X + (BUTTON_WIDTH/2),

};
//====================================================
// その他の定数
//====================================================
enum {
	AISYOU_TYPE_MAX = AKU_TYPE + 1,		///< タイプ最大値
	AISYOU_TYPE_NULL = AISYOU_TYPE_MAX,	///< タイプ無効値
};


//====================================================
// 描画パラメータ
//====================================================
typedef struct {

	u32  button_id;

	u16  effect_lv;
	u16  attack_type;
	u16  defence0_type;
	u16  defence1_type;


}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A18_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A18_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A18_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A18_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A18_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A18_DeleteViewWork(VIEWWORK* wk);

#endif
