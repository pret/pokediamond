//============================================================================================
/**
 * @file	poketch_a27.h
 * @bfief	ポケッチ（アプリNo27:つうしんサーチャー）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A27_H_
#define _POKETCH_A27_H_

#include "poketch_prv.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_IMG_TOP,
	CMD_IMG_SEARCHING,
	CMD_IMG_ERROR_CANT_CONNECT,
	CMD_IMG_ERROR_DONT_MOVE,
	CMD_IMG_STATUS,
	CMD_IMG_STATUS_UPDATE,
};


enum {
	DSIMG_POS_X = POKETCH_MONITOR_CENTER_X,
	DSIMG_POS_Y = 150,
};


//====================================================
// 通信人数カウントカテゴリ
//====================================================
enum {
	POKETCH_COMM_CATEGORY_UNION,		///< ユニオンルーム
	POKETCH_COMM_CATEGORY_UG,			///< 炭坑
	POKETCH_COMM_CATEGORY_COLOSSEUM,	///< コロシアム
	POKETCH_COMM_CATEGORY_OTHER,		///< その他

	POKETCH_COMM_CATEGORY_MAX
};


//====================================================
// 描画パラメータ
//====================================================
typedef struct {

	int  players_count[ POKETCH_COMM_CATEGORY_MAX ];

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A27_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A27_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A27_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A27_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A27_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A27_DeleteViewWork(VIEWWORK* wk);

#endif
