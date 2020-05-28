//============================================================================================
/**
 * @file	ev_fieldmap.c
 * @brief	フィールドマップ切替のイベントとその生成チェック
 * @date	2005.08.01
 * @date	2005.12.17	ev_mapchange.cから切り離し
 * @author	tamada
 */
//============================================================================================

#include "common.h"
#include "system/wipe.h"
#include "../fieldsys.h"

#include "../field_event.h"

#include "../fieldmap.h"

#include "../ev_mapchange.h"

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_FieldEnd(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フィールドプロセス終了
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_FinishFieldMap(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがないのに止めようとしている\n" && 0);
		return;
	}
	GameSystem_FinishFieldProc(fsys);
	FieldEvent_Call(event, GMEVENT_Sub_FieldEnd, NULL);
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_FieldStart(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フィールドプロセス開始
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_StartFieldMap(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	if (GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがあるのに開始しようとしている\n" && 0);
		return;
	}
	FieldEvent_Cmd_SetMapProc(fsys);
	FieldEvent_Call(event, GMEVENT_Sub_FieldStart, NULL);
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_WaitFade(GMEVENT_CONTROL * event)
{
//	BOOL *flg = FieldEvent_GetSpecialWork(event);
//	if ((*flg)) {
	if (WIPE_SYS_EndCheck()) {
//		sys_FreeMemoryEz(flg);
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フェードアウト
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_FieldFadeOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがないのにフェードを実行\n" && 0);
		return;
	}
	
	{
/*		BOOL *flg;
		flg = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(BOOL));//*/
		WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
            WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
//		FieldEvent_Call(event, GMEVENT_Sub_WaitFade, flg);
		FieldEvent_Call(event, GMEVENT_Sub_WaitFade, NULL);
	}
}


//============================================================================================
//============================================================================================

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フェードイン
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_FieldFadeIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがないのにフェードを実行\n" && 0);
		return;
	}

	{
/*		BOOL *flg;
		flg = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(BOOL));//*/
		WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
            WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
//		FieldEvent_Call(event, GMEVENT_Sub_WaitFade, flg);
		FieldEvent_Call(event, GMEVENT_Sub_WaitFade, NULL);
	}
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_FadeOut_FinishField(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		EventCmd_FieldFadeOut(event);
		(*seq) ++;
		break;
	case 1:
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フェードアウト→フィールドプロセス終了
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_FadeOut_FinishField(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_Sub_FadeOut_FinishField, NULL);
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_StartField_FadeIn(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	switch (*seq) {
	case 0:
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		//地名表示
		PlaceNameRequestByFsys(fsys);
		
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フィールドプロセス開始→フェードイン
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_StartField_FadeIn(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_Sub_StartField_FadeIn, NULL);
}

