//============================================================================================
/**
 * @file	mysign.h
 * @bfief	�����T�C���쐬����
 * @author	Akito Mori
 * @date	06.03.11
 */
//============================================================================================
#ifndef _MYSIGN_H_
#define _MYSIGN_H_

//============================================================================================
//	��`
//============================================================================================

// �v���Z�X��`�f�[�^
extern PROC_RESULT MySignProc_Init( PROC * proc, int * seq );
extern PROC_RESULT MySignProc_Main( PROC * proc, int * seq );
extern PROC_RESULT MySignProc_End( PROC * proc, int * seq );

// �|�C���^�Q�Ƃ����ł��邨�G�����{�[�h���[�N�\����
typedef struct MYSIGN_WORK MYSIGN_WORK;	



#endif