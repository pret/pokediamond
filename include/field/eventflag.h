//============================================================================================
/**
 * @file	eventflag.h
 * @brief	セーブフラグ、ワーク操作
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
 * @brief	イベントワーク型定義
 */
//----------------------------------------------------------
typedef struct _EVENTWORK EVENTWORK;

//=============================================================================
//=============================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int EventWork_GetWorkSize(void);
extern EVENTWORK * EventWork_AllocWork(int heapID);
extern void EventWork_Init(EVENTWORK * evwk);

//----------------------------------------------------------
//	EVENTWORK操作のための関数
//----------------------------------------------------------
extern BOOL EventWork_CheckEventFlag( EVENTWORK * ev, u16 flag_no);
extern void EventWork_SetEventFlag( EVENTWORK * ev, u16 flag_no);
extern void EventWork_ResetEventFlag( EVENTWORK * ev, u16 flag_no);
extern u8 * EventWork_GetEventFlagAdrs( EVENTWORK * ev, u16 flag_no );
extern u16 * EventWork_GetEventWorkAdrs( EVENTWORK * ev, u16 work_no );

//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern EVENTWORK * SaveData_GetEventWork(SAVEDATA * sv);


#endif	//__EVENTFLAG_H__


