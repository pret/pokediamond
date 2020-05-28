//============================================================================================
/**
 * @file	poketch_a09.h
 * @bfief	�|�P�b�`�i�A�v��No09 : �J�E���^�[�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A09_H_
#define _POKETCH_A09_H_


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
	CMD_BUTTON_UPDATE,
	CMD_COUNTER_UPDATE,
};


enum {
	BUTTON_STATE_TOUCH,
	BUTTON_STATE_FREE,
};


enum {
	BUTTON_CENTER_X = 114,
	BUTTON_CENTER_Y = 128,

	BUTTON_WIDTH = 64,
	BUTTON_HEIGHT = 56,
};

//====================================================
// �`��p�����[�^
//====================================================
typedef struct {
	u32   counter;
	u32   button_state;
}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A09_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A09_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A09_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A09_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A09_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A09_DeleteViewWork(VIEWWORK* wk);

#endif
