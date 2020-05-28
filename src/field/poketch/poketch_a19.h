//============================================================================================
/**
 * @file	poketch_a19.h
 * @bfief	�|�P�b�`�i�A�v��No19:���u�e�X�^�[�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A19_H_
#define _POKETCH_A19_H_

#include "system\gamedata.h"	// TEMOTI_POKEMAX�Q�Ƃ̂���
#include "poketch_prv.h"

//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_BUTTON_PUSH,
	CMD_BUTTON_FREE,
	CMD_CHANGE_POKE_L,
	CMD_CHANGE_POKE_R,
	CMD_ANM_PLAY,
};

//====================================================
// �{�^�����C�A�E�g
//====================================================
enum {
	LOVE_BUTTON_WIDTH = 40,
	LOVE_BUTTON_HEIGHT = 40,

	LOVE_BUTTON_X = POKETCH_MONITOR_CENTER_X,
	LOVE_BUTTON_Y = 148,

	LOVE_BUTTON_TOP    = LOVE_BUTTON_Y-(LOVE_BUTTON_HEIGHT/2),
	LOVE_BUTTON_BOTTOM = LOVE_BUTTON_Y+(LOVE_BUTTON_HEIGHT/2),
	LOVE_BUTTON_LEFT   = LOVE_BUTTON_X-(LOVE_BUTTON_WIDTH/2),
	LOVE_BUTTON_RIGHT  = LOVE_BUTTON_X+(LOVE_BUTTON_WIDTH/2),
};

//====================================================
// �������x���i��ĉ������d�l�ɍ��킹�邽�߂����Ȃ��Ă���j
//====================================================
enum {
	LOVE_AFFINITY_LV_0 = 3,
	LOVE_AFFINITY_LV_1 = 2,
	LOVE_AFFINITY_LV_2 = 1,
	LOVE_AFFINITY_LV_3 = 0,
};

//====================================================
// �|�P�������EID
//====================================================
enum {
	LOVE_POKE_L = 0,
	LOVE_POKE_R,
};

//====================================================
// �`��p�����[�^
//====================================================
typedef struct {

	u32    pokeImgArcIndex[ TEMOTI_POKEMAX ];
	u16    pokeMonsNo[ TEMOTI_POKEMAX ];
	u16    pokeForm[ TEMOTI_POKEMAX ];

	u8     poke_count;
	u8     affinity_lv;
	u8     poke_id_L;
	u8     poke_id_R;


}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A19_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A19_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A19_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A19_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A19_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A19_DeleteViewWork(VIEWWORK* wk);

#endif
