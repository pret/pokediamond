//==============================================================================
/**
 * @file	d_tamada.c
 * @brief	デバッグ＆テスト処理（玉田）
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.28
 *
 *	test
 *	murakawa:test
 */
//==============================================================================

//branch test: commit for main

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"

#include "field_subproc.h"
#include "fld_debug.h"

#include "ev_mapchange.h"
#include "application/namein.h"

#ifdef	PM_DEBUG

//==============================================================================
//==============================================================================
#if 0
//--------------------------------------------------------------
/**
 * @brief	デバッグイベント：名前入力
 */
//--------------------------------------------------------------
static BOOL GMEVENT_DebugNameIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int * seq = FieldEvent_GetSpecialWork(event);

	switch (*seq) {
	case 0:
		EventCmd_FieldFadeOut(event);
		(*seq) ++;
		break;
	case 1:
		EventCmd_NameIn(event, NAMEIN_MYNAME, 0, 5, 0, NULL, NULL);
		(*seq) ++;
		break;
	case 2:
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(seq);
		return TRUE;
	}
	return FALSE;
}
#endif

//--------------------------------------------------------------
/**
 * @brief	デバッグイベント呼び出し
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		イベント指定
 */
//--------------------------------------------------------------
void Debug_EventSet_Tamada(FIELDSYS_WORK * fsys, int id)
{
	int * seq = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(int));
	*seq = 0;
	//FieldEvent_Set(fsys, GMEVENT_DebugNameIn, seq);
}



#endif	//PM_DEBUG
