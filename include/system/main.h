//=============================================================================
/**
 * @file	main.h
 * @brief
 * @author	GAME FREAK inc.
 * @date	2005.12.12
 */
//=============================================================================

#ifndef	__MAIN_H__
#define	__MAIN_H__

#include "system/savedata_def.h"
#include "system/procsys.h"

//-------------------------------------------------------------------------------
//�\�t�g�E�G�A���Z�b�g�̎��
//-------------------------------------------------------------------------------
#define _SOFT_RESET_NORMAL    (0)  ///< �d����������OS_GetResetParameter�͂O��Ԃ��܂�
#define _SOFT_RESET_NETERROR  (1)  ///< �ʐM�G���[�̎�

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
typedef struct {
	int select_id;
	BOOL comm_error_flag;
	SAVEDATA * savedata;
}MAINWORK;

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
extern void Main_Init(void);
extern void Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);

extern void Main_InitRandom(void);
#endif	//__MAIN_H__
