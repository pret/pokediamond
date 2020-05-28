//============================================================================================
/**
 * @file	poketch_a47.h
 * @bfief	�|�P�b�`�i�A�v��No47�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A47_H_
#define _POKETCH_A47_H_


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,
};

//====================================================
// �`��p�����[�^
//====================================================
typedef struct {
	u32 dmy;

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A47_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A47_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A47_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A47_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A47_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A47_DeleteViewWork(VIEWWORK* wk);

#endif
