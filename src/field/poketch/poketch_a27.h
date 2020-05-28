//============================================================================================
/**
 * @file	poketch_a27.h
 * @bfief	�|�P�b�`�i�A�v��No27:������T�[�`���[�j�@�����w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_A27_H_
#define _POKETCH_A27_H_

#include "poketch_prv.h"

//====================================================
// �`��R�}���h
//====================================================
enum {
	CMD_INIT,
	CMD_QUIT,

	CMD_IMG_TOP,
	CMD_IMG_SEARCHING,
	CMD_IMG_ERROR_CANT_CONNECT,
	CMD_IMG_ERROR_DONT_MOVE,
	CMD_IMG_STATUS,
	CMD_IMG_STATUS_UPDATE,
};


enum {
	DSIMG_POS_X = POKETCH_MONITOR_CENTER_X,
	DSIMG_POS_Y = 150,
};


//====================================================
// �ʐM�l���J�E���g�J�e�S��
//====================================================
enum {
	POKETCH_COMM_CATEGORY_UNION,		///< ���j�I�����[��
	POKETCH_COMM_CATEGORY_UG,			///< �Y�B
	POKETCH_COMM_CATEGORY_COLOSSEUM,	///< �R���V�A��
	POKETCH_COMM_CATEGORY_OTHER,		///< ���̑�

	POKETCH_COMM_CATEGORY_MAX
};


//====================================================
// �`��p�����[�^
//====================================================
typedef struct {

	int  players_count[ POKETCH_COMM_CATEGORY_MAX ];

}VIEWPARAM;

//====================================================
// �`��p�����[�^
//====================================================
typedef	struct _POKETCH_A27_VIEWWORK  VIEWWORK;

//====================================================
// �֐��v���g�^�C�v
//====================================================
extern BOOL Poketch_A27_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl );
extern void Poketch_A27_SetViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A27_WaitViewCommand(VIEWWORK* wk, u32 cmd);
extern BOOL Poketch_A27_WaitViewCommandAll(VIEWWORK* wk);
extern void Poketch_A27_DeleteViewWork(VIEWWORK* wk);

#endif
