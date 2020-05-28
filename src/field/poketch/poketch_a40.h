//============================================================================================
/**
 * @file	poketch_a40.h
 * @bfief	�|�P�b�`�i�A�v��No40�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A40_H_
#define _POKETCH_A40_H_


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
typedef	struct _POKETCH_A40_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A40_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A40_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A40_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A40_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A40_DeleteViewWork(VIEWWORK* wk);

#endif
