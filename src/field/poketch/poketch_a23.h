//============================================================================================
/**
 * @file	poketch_a23.h
 * @bfief	�|�P�b�`�i�A�v��No23:���̂݃}�b�v�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A23_H_
#define _POKETCH_A23_H_

#include "poketch_map.h"

//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_SEED_UPDATE,
};

//====================================================
// �萔
//====================================================
enum {
	SEED_GRID_MAX = 64,
};

//====================================================
// �`��p�����[�^
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
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A23_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A23_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A23_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A23_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A23_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A23_DeleteViewWork(VIEWWORK* wk);

#endif
