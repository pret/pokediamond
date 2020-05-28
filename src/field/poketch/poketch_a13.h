//============================================================================================
/**
 * @file	poketch_a13.h
 * @bfief	ポケッチ（アプリNo13:トレーナーランチャー）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A13_H_
#define _POKETCH_A13_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_BUTTON_PUSH,
	CMD_BUTTON_RELEASE,
};
//====================================================
// ボタン種類
//====================================================
enum {
	BUTTON_ZUKAN,
	BUTTON_POKEMON,
	BUTTON_BAG,
	BUTTON_CARD,
	BUTTON_REPORT,
	BUTTON_CONFIG,

	BUTTON_MAX,
};

//====================================================
// ボタンレイアウト
//====================================================

enum {
	BUTTON_SCREEN_WIDTH = 6,
	BUTTON_SCREEN_HEIGHT = 6,

	BUTTON0_SCRNPOS_X = 2,
	BUTTON0_SCRNPOS_Y = 2,
	BUTTON1_SCRNPOS_X = 20,
	BUTTON1_SCRNPOS_Y = 2,
	BUTTON2_SCRNPOS_X = 2,
	BUTTON2_SCRNPOS_Y = 9,
	BUTTON3_SCRNPOS_X = 20,
	BUTTON3_SCRNPOS_Y = 9,
	BUTTON4_SCRNPOS_X = 2,
	BUTTON4_SCRNPOS_Y = 16,
	BUTTON5_SCRNPOS_X = 20,
	BUTTON5_SCRNPOS_Y = 16,

	BUTTON0_TOP    = BUTTON0_SCRNPOS_Y * 8,
	BUTTON0_BOTTOM = BUTTON0_TOP + (BUTTON_SCREEN_HEIGHT*8),
	BUTTON0_LEFT   = BUTTON0_SCRNPOS_X * 8,
	BUTTON0_RIGHT  = BUTTON0_LEFT + (BUTTON_SCREEN_WIDTH*8),

	BUTTON1_TOP    = BUTTON1_SCRNPOS_Y * 8,
	BUTTON1_BOTTOM = BUTTON1_TOP + (BUTTON_SCREEN_HEIGHT*8),
	BUTTON1_LEFT   = BUTTON1_SCRNPOS_X * 8,
	BUTTON1_RIGHT  = BUTTON1_LEFT + (BUTTON_SCREEN_WIDTH*8),

	BUTTON2_TOP    = BUTTON2_SCRNPOS_Y * 8,
	BUTTON2_BOTTOM = BUTTON2_TOP + (BUTTON_SCREEN_HEIGHT*8),
	BUTTON2_LEFT   = BUTTON2_SCRNPOS_X * 8,
	BUTTON2_RIGHT  = BUTTON2_LEFT + (BUTTON_SCREEN_WIDTH*8),

	BUTTON3_TOP    = BUTTON3_SCRNPOS_Y * 8,
	BUTTON3_BOTTOM = BUTTON3_TOP + (BUTTON_SCREEN_HEIGHT*8),
	BUTTON3_LEFT   = BUTTON3_SCRNPOS_X * 8,
	BUTTON3_RIGHT  = BUTTON3_LEFT + (BUTTON_SCREEN_WIDTH*8),

	BUTTON4_TOP    = BUTTON4_SCRNPOS_Y * 8,
	BUTTON4_BOTTOM = BUTTON4_TOP + (BUTTON_SCREEN_HEIGHT*8),
	BUTTON4_LEFT   = BUTTON4_SCRNPOS_X * 8,
	BUTTON4_RIGHT  = BUTTON4_LEFT + (BUTTON_SCREEN_WIDTH*8),

	BUTTON5_TOP    = BUTTON5_SCRNPOS_Y * 8,
	BUTTON5_BOTTOM = BUTTON5_TOP + (BUTTON_SCREEN_HEIGHT*8),
	BUTTON5_LEFT   = BUTTON5_SCRNPOS_X * 8,
	BUTTON5_RIGHT  = BUTTON5_LEFT + (BUTTON_SCREEN_WIDTH*8),

};


//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u32 dmy;

	BOOL  button_enable_flag[ BUTTON_MAX ];

	u16  button_id;	///< 操作されているボタンのインデックス

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A13_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A13_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A13_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A13_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A13_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A13_DeleteViewWork(VIEWWORK* wk);

#endif
