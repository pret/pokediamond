//============================================================================================
/**
 * @file	poketch_a17.h
 * @bfief	ポケッチ（アプリNo17:コイントス）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A17_H_
#define _POKETCH_A17_H_

#include "poketch_prv.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_TOSS,
};

//====================================================
// 定数
//====================================================
enum {
	COIN_DEFAULT_X = POKETCH_MONITOR_CENTER_X,		///< コイン初期配置座標Ｘ
	COIN_DEFAULT_Y = 144,							///< コイン初期配置座標Ｙ
};


//====================================================
// 描画パラメータ
//====================================================
typedef struct {
	u32  result;	// 0:表 1:裏

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A17_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A17_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A17_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A17_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A17_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A17_DeleteViewWork(VIEWWORK* wk);


#ifdef PM_DEBUG
extern void PA17DEBUG_AddCoinSpeed( fx32 add );
extern void PA17DEBUG_AddGravity( fx32 add );
#endif


#endif
