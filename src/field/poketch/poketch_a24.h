//============================================================================================
/**
 * @file	poketch_a24.h
 * @bfief	ポケッチ（アプリNo24:カラーチェンジャー）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A24_H_
#define _POKETCH_A24_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_UPDATE_BARPOS,
};

//====================================================
// スライドバー描画位置
//====================================================
enum {
	BAR_XORG = 56,
	BAR_YPOS = 148,

	BAR_MOVE_DIFF = 16,
};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {

	u32 bar_pos;

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A24_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A24_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A24_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A24_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A24_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A24_DeleteViewWork(VIEWWORK* wk);

#endif
