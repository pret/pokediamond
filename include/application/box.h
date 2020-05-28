//============================================================================================
/**
 * @file	box.h
 * @brief	�{�b�N�X��ʂ̌Ăяo���ɕK�v�Ȓ萔�E�֐�
 * @author	taya
 * @date	2005.09.09
 */
//============================================================================================
#ifndef __BOX_H__
#define __BOX_H__

#include "system\procsys.h"
#include "savedata\savedata_def.h"


#include "box_mode.h"

typedef int BOX_MODE;


//------------------------------------------------------
/**
 * �{�b�N�X���PROC�p�����[�^
 */
//------------------------------------------------------
typedef struct {
	// [in] 
	SAVEDATA*  savedata;
	BOX_MODE   mode;

	// [out]
	BOOL       modifiedFlag;	///< �{�b�N�X���e���ύX���ꂽ��TRUE������

}BOX_PROC_PARAM;


//------------------------------------------------------
/**
 * �{�b�N�X���PROC�֐�
 */
//------------------------------------------------------
extern PROC_RESULT BoxProc_Init( PROC * proc, int * seq );
extern PROC_RESULT BoxProc_Main( PROC* proc, int* seq );
extern PROC_RESULT BoxProc_End( PROC* proc, int* seq );


#endif
