//============================================================================================
/**
 * @file	poketch_a26.h
 * @bfief	ポケッチ（アプリNo26）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A26_H_
#define _POKETCH_A26_H_


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
typedef	struct _POKETCH_A26_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A26_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A26_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A26_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A26_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A26_DeleteViewWork(VIEWWORK* wk);

#endif
