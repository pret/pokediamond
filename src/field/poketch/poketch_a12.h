//============================================================================================
/**
 * @file	poketch_a12.h
 * @bfief	ポケッチ（アプリNo12）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A12_H_
#define _POKETCH_A12_H_


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
typedef	struct _POKETCH_A12_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A12_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A12_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A12_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A12_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A12_DeleteViewWork(VIEWWORK* wk);

#endif
