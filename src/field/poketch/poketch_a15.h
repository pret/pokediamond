//============================================================================================
/**
 * @file	poketch_a15.h
 * @bfief	�|�P�b�`�i�A�v��No15:�����Ă�J�����j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A15_H_
#define _POKETCH_A15_H_


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

	u8    poke_count;
	u8    tamago_flag;

	u32   poke_img_arc_idx[2];
    u32   poke_level[2];
    u32   poke_sex[2];
	u16   poke_monsno[2];
	u16   poke_form[2];


}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A15_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A15_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A15_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A15_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A15_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A15_DeleteViewWork(VIEWWORK* wk);

#endif
