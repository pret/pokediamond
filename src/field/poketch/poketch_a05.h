//============================================================================================
/**
 * @file	poketch_a05.h
 * @bfief	�|�P�b�`�i�h�b�g�A�[�g�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A05_H_
#define _POKETCH_A05_H_


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_FIELD_UPDATE,
	CMD_QUIT,
};

//====================================================
// �萔
//====================================================
enum {
	FIELD_XORG_CHAR = 2,
	FIELD_YORG_CHAR = 2,
	FIELD_XORG_PIXEL = FIELD_XORG_CHAR*8,
	FIELD_YORG_PIXEL = FIELD_YORG_CHAR*8,

	FIELD_WIDTH = 24,
	FIELD_HEIGHT = 20,
};


//====================================================
// �`��p�����[�^
//====================================================
typedef struct {
	u8    dot[FIELD_HEIGHT][FIELD_WIDTH];
}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A05_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A05_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A05_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A05_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A05_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A05_DeleteViewWork(VIEWWORK* wk);

#endif
