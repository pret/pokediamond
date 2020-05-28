//============================================================================================
/**
 * @file	poketch_main.h
 * @bfief	�|�P�b�`�i���C���j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_MAIN_H_
#define _POKETCH_MAIN_H_



//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_MAIN_INIT,
	CMD_MAIN_FIRSTOPEN,
	CMD_MAIN_EFFOPEN,
	CMD_MAIN_EFFOPEN2,
	CMD_MAIN_EFFCLOSE,
	CMD_MAIN_EFFCLOSE2,
	CMD_MAIN_BUTTONLOCK,
	CMD_MAIN_BUTTONPUSH,
	CMD_MAIN_BUTTONFREE,
	CMD_MAIN_SKIPNUM_DISP,
	CMD_MAIN_SKIPNUM_UPDATE,
	CMD_MAIN_SKIPNUM_END,
	CMD_MAIN_SLEEP,
	CMD_MAIN_WAKE,
	CMD_MAIN_QUIT,
};

//====================================================
// �`��p�p�����[�^
//====================================================
typedef struct {
	u32 app_pos;
}POKETCH_MAIN_VPARAM;

//====================================================
// �`�惂�W���[�����[�N�̌^�錾
//====================================================
typedef	struct _POKETCH_VIEW_WORK  POKETCH_VIEW_WORK;



//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL  Poketch_MAIN_SetViewWork(POKETCH_VIEW_WORK** wk_ptr, const POKETCH_MAIN_VPARAM *vpara, NNSG2dOamManagerInstance* oamm, CONTACT_WORK* cwk);
extern void Poketch_MAIN_DeleteViewWork( POKETCH_VIEW_WORK *wk );
extern void Poketch_MAIN_SetCommand(POKETCH_VIEW_WORK *wk, u32 cmd);
extern BOOL Poketch_MAIN_WaitCommand(POKETCH_VIEW_WORK *wk, u32 cmd);
extern BOOL Poketch_MAIN_WaitCommandAll(POKETCH_VIEW_WORK *wk);
extern POKETCH_VIEW_WORK* PoketchGetMainViewWork( void );

#endif

