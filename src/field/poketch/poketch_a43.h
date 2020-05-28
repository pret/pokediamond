//============================================================================================
/**
 * @file	poketch_a43.h
 * @bfief	ポケッチ（アプリNo43）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A43_H_
#define _POKETCH_A43_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u32 dmy;

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A43_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A43_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A43_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A43_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A43_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A43_DeleteViewWork(VIEWWORK* wk);

#endif
