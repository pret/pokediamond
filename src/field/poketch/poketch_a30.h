//============================================================================================
/**
 * @file	poketch_a30.h
 * @bfief	�|�P�b�`�i�A�v��No30�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A30_H_
#define _POKETCH_A30_H_


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
typedef	struct _POKETCH_A30_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A30_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A30_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A30_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A30_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A30_DeleteViewWork(VIEWWORK* wk);

#endif
