//============================================================================================
/**
 * @file	eventflag.h
 * @brief	�Z�[�u�t���O�A���[�N����
 * @author	Tamada
 * @author	Satoshi Nohara
 * @date	05.10.22
 */
//============================================================================================
#ifndef	__EVENTFLAG_H__
#define	__EVENTFLAG_H__

#include "system/savedata_def.h"


//=============================================================================
//=============================================================================
//----------------------------------------------------------
/**
 * @brief	�C�x���g���[�N�^��`
 */
//----------------------------------------------------------
typedef struct _EVENTWORK EVENTWORK;

//=============================================================================
//=============================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int EventWork_GetWorkSize(void);
extern EVENTWORK * EventWork_AllocWork(int heapID);
extern void EventWork_Init(EVENTWORK * evwk);

//----------------------------------------------------------
//	EVENTWORK����̂��߂̊֐�
//----------------------------------------------------------
extern BOOL EventWork_CheckEventFlag( EVENTWORK * ev, u16 flag_no);
extern void EventWork_SetEventFlag( EVENTWORK * ev, u16 flag_no);
extern void EventWork_ResetEventFlag( EVENTWORK * ev, u16 flag_no);
extern u8 * EventWork_GetEventFlagAdrs( EVENTWORK * ev, u16 flag_no );
extern u16 * EventWork_GetEventWorkAdrs( EVENTWORK * ev, u16 work_no );

//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern EVENTWORK * SaveData_GetEventWork(SAVEDATA * sv);


#endif	//__EVENTFLAG_H__


