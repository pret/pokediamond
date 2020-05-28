//=============================================================================
/**
 * @file	field_event.c
 * @brief	フィールドイベント制御
 * @author	tamada
 * @date	2005.07.22
 */
//=============================================================================

#include "common.h"
#include "fieldsys.h"

#include "field_event.h"

//=============================================================================
//=============================================================================
enum {
	HEAPID_LOCAL = HEAPID_EVENT,
};
//-----------------------------------------------------------------------------
/**
 * ゲーム内イベントコントロール用ワーク定義
 */
//-----------------------------------------------------------------------------
typedef struct _GMEVENT_CONTROL{
	GMEVENT_CONTROL * parent;
	GMEVENT_FUNC	func;	///<制御関数へのポインタ
	int seq;				///<シーケンスワーク
	void * work;			///<制御関数毎に固有ワークへのポインタ
	int lwk_size;
	void * lwk;
	FIELDSYS_WORK * repw;	///<フィールド全体制御ワークへのポインタ（なるべく参照したくない）
	EVENT_WORK * event_work;	///<イベントで使用するワーク
};

//=============================================================================
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	イベント生成
 * @param	repw
 * @param	event_func	イベント制御関数へのポインタ
 * @param	work		イベント制御関数の使用するワークへのポインタ
 * @return	GMEVENT_CONTROL	生成したイベントへのポインタ
 *
 */
//------------------------------------------------------------------
static GMEVENT_CONTROL * Event_Create(FIELDSYS_WORK * repw, GMEVENT_FUNC event_func, void * work)
{
	GMEVENT_CONTROL * event;
	event = sys_AllocMemoryLo(HEAPID_LOCAL, sizeof(GMEVENT_CONTROL));
	event->parent = NULL;
	event->func = event_func;
	event->seq = 0;
	event->work = work;
	event->lwk_size = 0;
	event->lwk = NULL;
	event->repw = repw;
	event->event_work = sys_AllocMemoryLo(HEAPID_LOCAL, sizeof(EVENT_WORK));
	return event;
}

//------------------------------------------------------------------
/**
 * @brief	イベント設定
 * @param	repw
 * @param	event_func	イベント制御関数へのポインタ
 * @param	work		イベント制御関数の使用するワークへのポインタ
 * @return	GMEVENT_CONTROL	生成したイベント
 */
//------------------------------------------------------------------
GMEVENT_CONTROL * FieldEvent_Set(FIELDSYS_WORK * repw, GMEVENT_FUNC event_func, void * work)
{
	GMEVENT_CONTROL * event;
	GF_ASSERT(repw->event == NULL);
//	GF_ASSERT((sys_GetHeapState(HEAPID_LOCAL) >> 32) == 0);
	event = Event_Create(repw, event_func, work);
	repw->event = event;
	return event;
}
//------------------------------------------------------------------
/**
 * @brief	イベント切替
 * @param	event		イベント制御ワークへのポインタ
 * @param	next_func	次のイベント制御関数へのポインタ
 * @param	work		次のイベント制御関数の使用するワークへのポインタ
 */
//------------------------------------------------------------------
void FieldEvent_Change(GMEVENT_CONTROL * event, GMEVENT_FUNC next_func, void * work)
{
	event->func = next_func;
	event->seq = 0;
	event->work = work;
	if (event->lwk != 0 || event->lwk != NULL) {
		sys_FreeMemoryEz(event->lwk);
		event->lwk_size = 0;
		event->lwk = NULL;
	}
}
//------------------------------------------------------------------
/**
 * @brief	サブイベント呼び出し
 * @param	parent		親イベントへのポインタ
 * @param	event_func	イベント制御関数へのポインタ
 * @param	work		イベント制御関数の使用するワークへのポインタ
 * @return	GMEVENT_CONTROL	生成したイベント
 *
 * イベントからサブイベントのコールを呼び出す
 */
//------------------------------------------------------------------
GMEVENT_CONTROL * FieldEvent_Call(GMEVENT_CONTROL * parent, GMEVENT_FUNC sub_func, void * work)
{
	GMEVENT_CONTROL * event;
	event = Event_Create(parent->repw, sub_func, work);
	event->parent = parent;
	parent->repw->event = event;
	return event;
}

//=============================================================================
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	イベント制御
 * @param	repw
 * @retval	TRUE	イベント終了
 * @retval	FALSE	イベント継続中
 */
//------------------------------------------------------------------
BOOL FieldEvent_Control(FIELDSYS_WORK * fsys)
{
	if (fsys->event == NULL) {
		return FALSE;
	}
	while (fsys->event->func(fsys->event) == TRUE) {
		GMEVENT_CONTROL * parent;
		parent = fsys->event->parent;
		if (fsys->event->lwk) {
			sys_FreeMemoryEz(fsys->event->lwk);
		}
		sys_FreeMemoryEz(fsys->event->event_work);
		sys_FreeMemoryEz(fsys->event);
		fsys->event = parent;
		if (parent == NULL) {
//			GF_ASSERT((sys_GetHeapState(HEAPID_LOCAL) >> 32) == 0);
			return TRUE;
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	イベント起動中チェック
 * @param	fsys	フィールド制御ワークへのポインタ
 * @retval	TRUE	イベント起動中
 * @retval	FALSE	イベントなし
 */
//------------------------------------------------------------------
BOOL FieldEvent_Check(FIELDSYS_WORK * fsys)
{
	return (fsys->event != NULL);
}

//=============================================================================
//
//	イベントコマンド
//
//=============================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------

//------------------------------------------------------------------
/**
 * @brief	サブプロセス動作終了待ち
 * @param	fsys	フィールド制御ワークへのポインタ
 * @retval	TRUE	サブプロセス動作中
 * @retval	FALSE	サブプロセス終了
 */
//------------------------------------------------------------------
BOOL FieldEvent_Cmd_WaitSubProcEnd(FIELDSYS_WORK * fsys)
{
	if (GameSystem_CheckFieldProcExists(fsys) || GameSystem_CheckSubProcExists(fsys)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
//------------------------------------------------------------------
void FieldEvent_Cmd_SetMapProc(FIELDSYS_WORK * fsys)
{
	GameSystem_CreateFieldProc(fsys);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
BOOL FieldEvent_Cmd_WaitMapProcStart(FIELDSYS_WORK * fsys)
{
	if (GameSystem_CheckFieldMain(fsys)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//=============================================================================
//
//=============================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
typedef struct {
	int seq;
	const PROC_DATA * proc_data;
	void * param;
}EV_SUBPROC_WORK;
//------------------------------------------------------------------
/**
 * @brief	サブイベント：サブプロセス呼び出し
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		サブイベント終了
 * @retval	FALSE		サブイベント継続中
 */
//------------------------------------------------------------------
static BOOL GMEVENT_Sub_CallSubProc(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SUBPROC_WORK * esw = FieldEvent_GetSpecialWork(event);
	switch (esw->seq) {
	case 0:
		GameSystem_StartSubProc(fsys, esw->proc_data, esw->param);
		esw->seq ++;
		break;
	case 1:
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			break;
		}
		sys_FreeMemoryEz(esw);
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：サブプロセス呼び出し
 * @param	event		イベント制御ワークへのポインタ
 * @param	proc_data	プロセス定義データへのポインタ
 * @param	param		パラメータへのポインタ
 *
 * サブプロセスを呼び出して終了を待つ
 */
//------------------------------------------------------------------
void EventCmd_CallSubProc(GMEVENT_CONTROL * event, const PROC_DATA * proc_data, void * param)
{
	EV_SUBPROC_WORK * esw = sys_AllocMemoryLo(HEAPID_LOCAL, sizeof(EV_SUBPROC_WORK));
	esw->seq = 0;
	esw->proc_data = proc_data;
	esw->param = param;
	FieldEvent_Call(event, GMEVENT_Sub_CallSubProc, esw);
}

//=============================================================================
//
//
//
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	フィールド制御ワークへのポインタ取得
 * @param	event		イベント制御ワークへのポインタ
 * @return	FIELDSYS_WORK	フィールド制御ワークへのポインタ
 *
 * フィールド制御ワークはフィールドでは最上位のワークエリアとなる。
 * この領域に直接参照することは「フィールド内でのグローバル変数へのアクセス」と
 * 等しい。グローバル変数へのアクセスはなるべく避けるべきなので、この関数は
 * なるべく使用しないようにしたい。
 *
 * まずはプログラム構造を概念的に切り分けることを優先するため、
 * 基本的に必要な変数などへのアクセスは関数経由にする。
 * その上で不要なものは削除していき、速度的な問題がある場合はポインタ直接参照を
 * 考える。
 *
 */
//------------------------------------------------------------------
FIELDSYS_WORK * FieldEvent_GetFieldSysWork(GMEVENT_CONTROL * event)
{
	return event->repw;
}

//------------------------------------------------------------------
/**
 * @brief	フィールドイベント個別のワークへのポインタ
 * @param	event		イベント制御ワークへのポインタ
 * @return	各イベント用ワーク
 */
//------------------------------------------------------------------
void * FieldEvent_GetSpecialWork(GMEVENT_CONTROL * event)
{
	return event->work;
}

//------------------------------------------------------------------
/**
 * @brief	シーケンスワークの取得
 * @param	event		イベント制御ワークへのポインタ
 * @return	シーケンスワークへのポインタ
 */
//------------------------------------------------------------------
int * FieldEvent_GetSeqWork(GMEVENT_CONTROL * event)
{
	return &event->seq;
}
//------------------------------------------------------------------
/**
 * @brief	ローカルワークの取得
 * @param	event		イベント制御ワークへのポインタ
 * @param	size		ローカルワークのサイズ指定	
 * @return	void*		ローカルワークへのポインタ
 *
 * そのイベントから抜けたときに自動解放されるワークを取得できる。
 * イベント終了時、およびイベント切替（FieldEvent_Change）のタイミングで
 * 解放される。
 */
//------------------------------------------------------------------
void * FieldEvent_GetLocalWork(GMEVENT_CONTROL * event, int size)
{
	if (event->lwk == NULL && event->lwk_size == 0) {
		event->lwk_size = size;
		event->lwk = sys_AllocMemoryLo(HEAPID_LOCAL, size);
		MI_CpuClear8(event->lwk, size);
	} else {
		GF_ASSERT(event->lwk_size == size);
	}
	return event->lwk;
}

//------------------------------------------------------------------
/**
 * @brief	イベントで使用するワークを取得
 * @param	fsys	フィールシステム
 * @return	イベント用ワーク
 */
//------------------------------------------------------------------
EVENT_WORK * Event_GetEventWork(FIELDSYS_WORK * fsys)
{
	return fsys->event->event_work;
}


//------------------------------------------------------------------
/**
 * @brief	話かけOBJを取得
 * @param	event		イベント制御ワークへのポインタ
 * @return	話かけOBJ
 */
//------------------------------------------------------------------
#if 0
FIELD_OBJ_PTR Event_GetTargetObj( GMEVENT_CONTROL * event )
{
	return event->event_work->targetobj;
}
#endif

//------------------------------------------------------------------
/**
 * @brief	話かけBGを取得
 * @param	event		イベント制御ワークへのポインタ
 * @return	話かけBG
 */
//------------------------------------------------------------------
u32 Event_GetTargetBg( GMEVENT_CONTROL * event )
{
	return event->event_work->targetbg;
}

