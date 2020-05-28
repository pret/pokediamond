//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_preview.h
 *	@brief		preview���
 *	@author		tomoya takahashi
 *	@data		2006.06.05
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_PREVIEW_H__
#define __IMC_PREVIEW_H__

#include "include/system/procsys.h"

#undef GLOBAL
#ifdef	__IMC_PREVIEW_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�e���r�@�R���e�X�g�@�t���O
//=====================================
enum{
	IMC_PREV_TV,
	IMC_PREV_CON,
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C���[�W�N���b�v�O���f�[�^
//=====================================
typedef struct {
	// �C���[�W�N���b�v�Z�[�u�̈�
	IMC_SAVEDATA* p_imc_data;
	u32 data_idx;	// �Z�[�u�f�[�^�z��C���f�b�N�X
	u32	prev_type;	// preview�^�C�v�@
					// IMC_PREV_TV,
					// IMC_PREV_CON,
} IMC_PROC_PREV_WORK;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT IMC_Prev_ProcInit( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_Prev_ProcMain( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_Prev_ProcEnd( PROC* proc, int* seq );


#undef	GLOBAL
#endif		// __IMC_PREVIEW_H__

