//============================================================================================
/**
 * @file	ev_poketch.c
 * @brief	ポケッチ関連フィールドイベントの実処理
 * @date	2005.10.28
 * @author	taya
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "field\poketch.h"
#include "field\poketch_data.h"
#include "system\brightness.h"
#include "system\pm_overlay.h"
#include "savedata\savedata.h"
#include "system\render_oam.h"
#include "fieldmap_work.h"

#include "ev_poketch.h"

//============================================================================================
// ポケッチ取得イベント
//============================================================================================

//-----------------------------------------------------------------------------
/**
 * @brief	各種定数
 */
//-----------------------------------------------------------------------------
enum {
	GETPOKETCH_FADEOUT_TIME = 2,
	GETPOKETCH_FADEIN_TIME = 4,
};


//-----------------------------------------------------------------------------
/**
 * @brief	イベント制御ワーク
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
}EVENT_GETPOKETCH_WORK;


//------------------------------------------------------------------
/**
 * イベント実処理
 *
 * @param   event		イベントワークポインタ
 *
 * @retval  BOOL		TRUEで実行終了
 */
//------------------------------------------------------------------
static BOOL GMEVENT_Sub_GetPoketch(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_GETPOKETCH_WORK* wk = FieldEvent_GetSpecialWork(event);

	switch (wk->seq) {
	case 0:
		ChangeBrightnessRequest( GETPOKETCH_FADEOUT_TIME, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
			PLANEMASK_ALL, MASK_SUB_DISPLAY );
		wk->seq++;
		break;
	case 1:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY ) )
		{
			BeforePoketchQuitReq( fsys->bgl );
			wk->seq++;
		}
		break;
	case 2:
		if( BeforePoketchQuitWait( fsys->bgl ) )
		{
			POKETCH_DATA* pd = SaveData_GetPoketchData( fsys->savedata );

			Overlay_UnloadID( FS_OVERLAY_ID(ol_before_poketch) );
			Overlay_Load( FS_OVERLAY_ID(ol_poketch), OVERLAY_LOAD_NOT_SYNCHRONIZE );
			PoketchData_SetPoketchGetFlag( pd );

			PoketchInit( fsys, &fsys->fldmap->poketch, fsys->savedata, fsys->bgl, REND_OAM_GetOamManagerInstance(REND_OAM_SUB) );
			wk->seq++;
		}
		break;
	case 3:
		ChangeBrightnessRequest( GETPOKETCH_FADEIN_TIME, BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK,
			PLANEMASK_ALL, MASK_SUB_DISPLAY );
		wk->seq++;
		break;
	case 4:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY ) )
		{
			sys_FreeMemoryEz(wk);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベントサブコマンド：ポケッチ取得
 * @param	event		親イベントワークへのポインタ
 *
 * 下画面フェードアウト→ポケッチ取得フラグ切り替え→下画面再構築、フェードインまで
 */
//-----------------------------------------------------------------------------
void EventCmd_GetPoketch(GMEVENT_CONTROL* event)
{
	EVENT_GETPOKETCH_WORK *wk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_GETPOKETCH_WORK));
	wk->seq = 0;
	FieldEvent_Call(event, GMEVENT_Sub_GetPoketch, wk);
}


#ifdef PM_DEBUG
extern void EventCmd_DebugGetPoketch(FIELDSYS_WORK* fsys);	// Warning対処
void EventCmd_DebugGetPoketch(FIELDSYS_WORK* fsys)
{
	EVENT_GETPOKETCH_WORK *wk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_GETPOKETCH_WORK));
	wk->seq = 0;
	FieldEvent_Set(fsys, GMEVENT_Sub_GetPoketch, wk);
}
#endif

