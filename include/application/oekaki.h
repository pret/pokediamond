//============================================================================================
/**
 * @file	oekaki.h
 * @bfief	���G�����{�[�h��ʏ���
 * @author	Akito Mori
 * @date	06.02.13
 */
//============================================================================================
#ifndef _OEKAKI_H_
#define _OEKAKI_H_

//============================================================================================
//	��`
//============================================================================================

// �v���Z�X��`�f�[�^
extern PROC_RESULT OekakiProc_Init( PROC * proc, int * seq );
extern PROC_RESULT OekakiProc_Main( PROC * proc, int * seq );
extern PROC_RESULT OekakiProc_End( PROC * proc, int * seq );

// �|�C���^�Q�Ƃ����ł��邨�G�����{�[�h���[�N�\����
typedef struct OEKAKI_WORK OEKAKI_WORK;	

typedef struct{
	COMM_UNIONROOM_VIEW *view;
	FNOTE_DATA			*fnote;
	CONFIG				*config;
}OEKAKI_PARAM;

#endif