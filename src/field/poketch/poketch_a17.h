//============================================================================================
/**
 * @file	poketch_a17.h
 * @bfief	�|�P�b�`�i�A�v��No17:�R�C���g�X�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A17_H_
#define _POKETCH_A17_H_

#include "poketch_prv.h"

//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_TOSS,
};

//====================================================
// �萔
//====================================================
enum {
	COIN_DEFAULT_X = POKETCH_MONITOR_CENTER_X,		///< �R�C�������z�u���W�w
	COIN_DEFAULT_Y = 144,							///< �R�C�������z�u���W�x
};


//====================================================
// �`��p�����[�^
//====================================================
typedef struct {
	u32  result;	// 0:�\ 1:��

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A17_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A17_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A17_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A17_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A17_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A17_DeleteViewWork(VIEWWORK* wk);


#ifdef PM_DEBUG
extern void PA17DEBUG_AddCoinSpeed( fx32 add );
extern void PA17DEBUG_AddGravity( fx32 add );
#endif


#endif
