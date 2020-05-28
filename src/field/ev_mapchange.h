//============================================================================================
/**
 * @file	ev_mapchange.h
 * @brief	
 * @date	2005.08.01
 */
//============================================================================================

#ifndef	__EV_MAPCHANGE_H__
#define	__EV_MAPCHANGE_H__

#include "field_common.h"
#include "field_event.h"

//-----------------------------------------------------------------------------
//	3D面セット
//-----------------------------------------------------------------------------
extern void MapChg_Set3DDisplay(FIELDSYS_WORK *fsys);

//-----------------------------------------------------------------------------
//	イベント開始
//-----------------------------------------------------------------------------
extern void EventSet_FirstMapIn(FIELDSYS_WORK * fsys);
extern void EventSet_ContinueMapIn(FIELDSYS_WORK * fsys);
extern void EventSet_ErrorContinueMapIn(FIELDSYS_WORK * fsys);

//-----------------------------------------------------------------------------
//	簡易マップ移動
//-----------------------------------------------------------------------------
extern void EventSet_EasyMapChange(FIELDSYS_WORK * fsys,
		int zone, int door_id, int x, int z, int dir );
extern void EventSet_EasyMapChangeByLocation(FIELDSYS_WORK * fsys, const LOCATION_WORK * next);
extern void EventCmd_EasyMapChange(GMEVENT_CONTROL * event,
		int zone, int door_id, int x, int z, int dir );
extern void EventCmd_EasyMapChangeByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next);



//-----------------------------------------------------------------------------
//	タイトルへ戻るイベント（デバッグ用）
//-----------------------------------------------------------------------------
extern void EventSet_ReturnToTitle(FIELDSYS_WORK * fsys);


//-----------------------------------------------------------------------------
//	ユニオンルーム用マップ移動
//-----------------------------------------------------------------------------
extern void EventSet_UnionRoomMapChange(FIELDSYS_WORK * fsys);
extern void EventSet_UnionRoomMapChangeIn(FIELDSYS_WORK * fsys);
extern void EventSet_UnionRoomMapChangeOut(FIELDSYS_WORK * fsys);

extern void EventCmd_UnionRoomMapChangeOut(GMEVENT_CONTROL * event);
extern void EventCmd_UnionRoomMapChangeIn(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
//		通信対戦部屋用マップ移動
//-----------------------------------------------------------------------------
extern void EventCmd_ColosseumMapChangeIn(GMEVENT_CONTROL * event,
		int zone_id, int door_id, int x, int z, int dir);
extern void EventCmd_ColosseumMapChangeOut(GMEVENT_CONTROL * event);
extern void EventSet_ColosseumMapChangeOut(FIELDSYS_WORK * fsys);

//-----------------------------------------------------------------------------
//	イベント擬似コマンド
//-----------------------------------------------------------------------------
extern void EventCmd_FinishFieldMap(GMEVENT_CONTROL * event);
extern void EventCmd_StartFieldMap(GMEVENT_CONTROL * event);
extern void EventCmd_FieldFadeIn(GMEVENT_CONTROL * event);
extern void EventCmd_FieldFadeOut(GMEVENT_CONTROL * event);
extern void EventCmd_FadeOut_FinishField(GMEVENT_CONTROL * event);
extern void EventCmd_StartField_FadeIn(GMEVENT_CONTROL * event);
extern void EventCmd_MapChange(GMEVENT_CONTROL * event,
		int zone_id, int door_id, int x, int z, int dir);
extern void EventCmd_MapChangeByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next);
extern void EventCmd_UgJumpByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next);
extern void EventCmd_MapChangeFull(GMEVENT_CONTROL * event,
		int zone_id, int door_id, int x, int z, int dir);
extern void EventSet_MapChangeBySky(
		FIELDSYS_WORK * fsys,int zone, int door_id, int x, int z, int dir );
extern void EventChange_MapChangeBySky(
		GMEVENT_CONTROL *event, int zone, int door_id, int x, int z, int dir );
extern void EventChange_MapChangeByAnanuke(
	GMEVENT_CONTROL *event, const LOCATION_WORK *escape, u32 ana_type );
extern void EventCmd_WarpPoint(FIELDSYS_WORK * fsys, int zone, int door_id);


//ゲームオーバー関連
extern void EventCmd_NormalLose(GMEVENT_CONTROL * event);
extern BOOL GMEVENT_NormalGameOver(GMEVENT_CONTROL * event);

//ゲームクリア関連
extern void EventCmd_GameClear(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
//	地下用マップ移動
//-----------------------------------------------------------------------------
extern void ChangeUnderGroundDirect(FIELDSYS_WORK * fsys);
#ifdef PM_DEBUG
void Debug_ChangeUnderGroundDirect(FIELDSYS_WORK * fsys, int x, int z);
#endif //PM_DEBUG
extern void JumpUnderGroundDirect(FIELDSYS_WORK * fsys, const int inX, const int inZ);


extern BOOL GMEVENT_GroundToUnderGround(GMEVENT_CONTROL * event);
extern BOOL GMEVENT_UnderGroundToGround(GMEVENT_CONTROL * event);
extern GMEVENT_FUNC MapChg_GetUgChangeEvent(const FIELDSYS_WORK * fsys);
extern void * MakeUGChangeWork(FIELDSYS_WORK * fsys);


//-----------------------------------------------------------------------------
//		データ操作など
//-----------------------------------------------------------------------------
extern void FNoteStartDataSet( FIELDSYS_WORK * fsys );
extern void MapChg_UpdateGameData(FIELDSYS_WORK * fsys, BOOL walk_flag);

#endif	/* __EV_MAPCHANGE_H__ */

