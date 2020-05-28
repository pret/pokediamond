//============================================================================================
/**
 * @file	record_corner.h
 * @bfief	���R�[�h�R�[�i�[����
 * @author	Akito Mori
 * @date	06.03.26
 */
//============================================================================================
#ifndef _RECORD_CORNER_H_
#define _RECORD_CORNER_H_

#include "savedata/savedata_def.h"
#include "field/comm_union_view_common.h"
#include "savedata/config.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"
//============================================================================================
//	��`
//============================================================================================

// �v���Z�X��`�f�[�^
extern PROC_RESULT RecordCornerProc_Init( PROC * proc, int * seq );
extern PROC_RESULT RecordCornerProc_Main( PROC * proc, int * seq );
extern PROC_RESULT RecordCornerProc_End( PROC * proc, int * seq );

// �|�C���^�Q�Ƃ����ł��郌�R�[�h�R�[�i�[���[�N�\����
typedef struct RECORD_WORK RECORD_WORK;	

///	�O������󂯎�郌�R�[�h�R�[�i�[�����ɕK�v�ȃ��[�N
typedef struct {
	SAVEDATA 			*sv;
	COMM_UNIONROOM_VIEW *union_view;
	CONFIG				*config;
	RECORD				*record;
	FNOTE_DATA			*fnote;
}RECORD_INPUT_PARAM;


#endif
