//============================================================================================
/**
 * @file	poketch_a06.h
 * @bfief	�|�P�b�`�i�A�v��No06�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A06_H_
#define _POKETCH_A06_H_

#include "system\gamedata.h"	// TEMOTI_POKEMAX
#include "poketool\poke_tool.h"	// POKEMON_PARAM

//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_UPDATE,
};

//====================================================
// �`��p�����[�^
//====================================================

typedef struct {
	int  poke_count;

	struct {
		u32  imgArcIdx;	// const �ɏo���Ȃ�PP��n���̂�����Ȃ̂Łc

		u16  monsno;
		u16  hp;
		u16  hp_max;
		u16  item;

		u16  sick_flag;
		u8   egg_flag;
		u8   form;

	}poke_param[TEMOTI_POKEMAX];

	u16    tp_cont;
	u16    tp_trg;
	u32    tp_x;
	u32    tp_y;

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A06_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A06_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A06_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A06_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A06_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A06_DeleteViewWork(VIEWWORK* wk);


extern u32 Poketch_A06_CheckTouchIconNum( u32 x, u32 y, u32 max );

#endif
