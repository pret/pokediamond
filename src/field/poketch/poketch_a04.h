//============================================================================================
/**
 * @file	poketch_a04.h
 * @bfief	ポケッチ（アプリNo04:アナログ時計） 　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A04_H_
#define _POKETCH_A04_H_


//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_TIME_UPDATE,
	CMD_BACKLIGHT_UPDATE,
	CMD_QUIT,
};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	RTCTime   time;
	u32       backlight;
}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A04_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A04_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A04_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A04_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A04_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A04_DeleteViewWork(VIEWWORK* wk);

#endif
