//============================================================================================
/**
 * @file	poketch_a34.h
 * @bfief	ポケッチ（アプリNo34）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A34_H_
#define _POKETCH_A34_H_


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
typedef	struct _POKETCH_A34_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A34_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A34_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A34_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A34_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A34_DeleteViewWork(VIEWWORK* wk);

#endif
