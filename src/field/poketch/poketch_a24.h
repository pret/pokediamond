//============================================================================================
/**
 * @file	poketch_a24.h
 * @bfief	�|�P�b�`�i�A�v��No24:�J���[�`�F���W���[�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A24_H_
#define _POKETCH_A24_H_


//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_UPDATE_BARPOS,
};

//====================================================
// �X���C�h�o�[�`��ʒu
//====================================================
enum {
	BAR_XORG = 56,
	BAR_YPOS = 148,

	BAR_MOVE_DIFF = 16,
};

//====================================================
// �`��p�����[�^
//====================================================
typedef struct {

	u32 bar_pos;

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A24_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A24_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A24_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A24_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A24_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A24_DeleteViewWork(VIEWWORK* wk);

#endif
