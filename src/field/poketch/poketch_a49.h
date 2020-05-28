//============================================================================================
/**
 * @file	poketch_a49.h
 * @bfief	ポケッチ（アプリNo49）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A49_H_
#define _POKETCH_A49_H_


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
typedef	struct _POKETCH_A49_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A49_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A49_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A49_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A49_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A49_DeleteViewWork(VIEWWORK* wk);

#endif
