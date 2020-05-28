//============================================================================================
/**
 * @file	poketch_a48.h
 * @bfief	ポケッチ（アプリNo48）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A48_H_
#define _POKETCH_A48_H_


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
typedef	struct _POKETCH_A48_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A48_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A48_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A48_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A48_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A48_DeleteViewWork(VIEWWORK* wk);

#endif
