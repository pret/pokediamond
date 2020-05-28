//============================================================================================
/**
 * @file	poketch_a23.h
 * @bfief	ポケッチ（アプリNo23:きのみマップ）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A23_H_
#define _POKETCH_A23_H_

#include "poketch_map.h"

//====================================================
// 描画コマンド
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_SEED_UPDATE,
};

//====================================================
// 定数
//====================================================
enum {
	SEED_GRID_MAX = 64,
};

//====================================================
// 描画パラメータ
//====================================================
typedef struct {

	int player_x;
	int player_y;

	int seed_count;
	struct {
		u8  x;
		u8  y;
	}seed_pos[ SEED_GRID_MAX ];

	BOOL seed_vanish_flag;
	BOOL player_update_flag;

	BOOL hidemap_flag[ POKETCH_HIDEMAP_MAX ];

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A23_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A23_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A23_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A23_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A23_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A23_DeleteViewWork(VIEWWORK* wk);

#endif
