//============================================================================================
/**
 * @file	poketch_a07.h
 * @bfief	�|�P�b�`�i�A�v��No07�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A07_H_
#define _POKETCH_A07_H_

#include "system\gamedata.h"	// TEMOTI_POKEMAX
#include "poketool\poke_tool.h"	// POKEMON_PARAM


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
};

//====================================================
// �萔
//====================================================
enum {
	NATSUKI_LV_MAX = 6,
};

enum {
	REACTION_LIKE,
	REACTION_HATE,
	REACTION_NEUTRAL,
};

//====================================================
// �`��p�����[�^
//====================================================
typedef struct {

	int      poke_count;

	struct {
		u32		imgArcIdx;
		u16		monsno;
		u16		natsuki;
		u16		form;
		u8		reaction_type;
		u8		reaction_level;
	}poke_param[ TEMOTI_POKEMAX ];

	u16    tp_cont;
	u16    tp_trg;
	u32    tp_x;
	u32    tp_y;

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A07_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A07_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A07_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A07_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A07_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A07_DeleteViewWork(VIEWWORK* wk);

#endif
