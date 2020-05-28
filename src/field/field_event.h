//============================================================================================
/**
 * @file	field_event.h
 * @brief	フィールドイベント制御用ヘッダ
 * @author	tamada
 * @date	2005.07.22
 */
//============================================================================================

#ifndef	__FIELD_EVENT_H__
#define	__FIELD_EVENT_H__

#include "field_common.h"
#include "fieldobj.h"
#include "system/procsys.h"

//=============================================================================
//
//	型定義
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	フィールドイベント制御関数の型定義
 */
//-----------------------------------------------------------------------------
typedef BOOL (*GMEVENT_FUNC)(GMEVENT_CONTROL *);

typedef struct {
//	FIELD_OBJ_PTR targetobj;
	u32 targetbg;				//あとで削除
//	void * targetobj;
}EVENT_WORK;

//=============================================================================
//
//	関数外部参照
//
//=============================================================================

extern GMEVENT_CONTROL * FieldEvent_Set(FIELDSYS_WORK * repw, GMEVENT_FUNC event_func, void * work);
extern void FieldEvent_Change(GMEVENT_CONTROL * event, GMEVENT_FUNC next_func, void * work);
extern GMEVENT_CONTROL * FieldEvent_Call(GMEVENT_CONTROL * parent, GMEVENT_FUNC sub_func, void * work);

extern BOOL FieldEvent_Control(FIELDSYS_WORK * repw);
extern BOOL FieldEvent_Check(FIELDSYS_WORK * fsys);

extern FIELDSYS_WORK * FieldEvent_GetFieldSysWork(GMEVENT_CONTROL * event);
extern int * FieldEvent_GetSeqWork(GMEVENT_CONTROL * event);
extern void * FieldEvent_GetSpecialWork(GMEVENT_CONTROL * event);
extern void * FieldEvent_GetLocalWork(GMEVENT_CONTROL * event, int size);

extern EVENT_WORK * Event_GetEventWork(FIELDSYS_WORK * fsys);
//extern FIELD_OBJ_PTR Event_GetTargetObj( GMEVENT_CONTROL * event );
extern u32 Event_GetTargetBg( GMEVENT_CONTROL * event );

extern BOOL FieldEvent_Cmd_WaitSubProcEnd(FIELDSYS_WORK * fsys);
extern void FieldEvent_Cmd_SetMapProc(FIELDSYS_WORK * fsys);
extern BOOL FieldEvent_Cmd_WaitMapProcStart(FIELDSYS_WORK * fsys);

extern void EventCmd_CallSubProc(GMEVENT_CONTROL * event, const PROC_DATA * proc_data, void * param);


#endif /* __FIELD_EVENT_H__ */
