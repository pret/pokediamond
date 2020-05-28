//============================================================================================
/**
 * @file	poketch_a41.h
 * @bfief	�|�P�b�`�i�A�v��No41�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A41_H_
#define _POKETCH_A41_H_


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
typedef	struct _POKETCH_A41_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A41_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A41_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A41_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A41_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A41_DeleteViewWork(VIEWWORK* wk);

#endif
