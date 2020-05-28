//============================================================================================
/**
 * @file	demo_ending.h
 * @brief	�G���f�B���O�f��
 * @author	taya
 * @date	2006.06.01
 */
//============================================================================================
#ifndef __DEMO_ENDING_H__
#define __DEMO_ENDING_H__



typedef struct {

	int					playerSex;	///< �v���C���[����
	BOOL				clearFlag;	///< ��x�ł��G���f�B���O���������Ƃ����邩�H
	const ZUKAN_WORK*	zukanWork;	///< �}�Ӄ��[�N�|�C���^

}ENDING_PROC_PARAM;



extern PROC_RESULT EndingDemoProc_Init( PROC * proc, int * seq );
extern PROC_RESULT EndingDemoProc_Main( PROC * proc, int * seq );
extern PROC_RESULT EndingDemoProc_Quit( PROC * proc, int * seq );


#endif
