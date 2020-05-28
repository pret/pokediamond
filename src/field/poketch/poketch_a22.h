//============================================================================================
/**
 * @file	poketch_a22.h
 * @bfief	ポケッチ（アプリNo22:マーキングマップ）　内部ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A22_H_
#define _POKETCH_A22_H_

#include "field\poketch_data.h"
#include "poketch_map.h"
#include "..\move_pokemon_def.h"

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

	int    player_x;
	int    player_y;
	BOOL   player_updateFlag;

	struct {
		u8  x;
		u8  y;
		u8  pri;
		u8  point_flag;
	}markpos[ POKETCH_MAP_MARK_MAX ];

	int  dragMarkID;
	BOOL updateFlag;

	BOOL  hidemap_flag[POKETCH_HIDEMAP_MAX];

	struct {
		BOOL  flag;
		int   zone_id;
	}move_poke[ MOVE_POKE_MAX ];

}VIEWPARAM;

//====================================================
// 描画パラメータ
//====================================================
typedef	struct _POKETCH_A22_VIEWWORK  VIEWWORK;

//====================================================
// 関数プロトタイプ
//====================================================
extern BOOL Poketch_A22_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A22_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A22_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A22_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A22_DeleteViewWork(VIEWWORK* wk);

#endif
