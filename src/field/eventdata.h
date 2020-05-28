//============================================================================================
/**
 * @file	eventdata.h
 * @brief	イベント起動チェック用データ定義ヘッダ
 * @date	2005.10.14
 *
 * 2005.10.18	check_data.h-->eventdata.hにリネームした
 */
//============================================================================================
#ifndef	__EVENTDATA_H__
#define	__EVENTDATA_H__

#include "check_data.h"
#include "encount_dat.h"

extern void EventData_Sys_Create(FIELDSYS_WORK * fsys, int heapID);
extern void EventData_Sys_Delete(FIELDSYS_WORK * fsys);

extern const BG_TALK_DATA * EventData_GetNowBgTalkData(const FIELDSYS_WORK * fsys);
extern int EventData_GetNowBgTalkDataSize(const FIELDSYS_WORK * fsys);
extern int EventData_GetNowConnectDataSize(const FIELDSYS_WORK * fsys);
extern int EventData_SearchNowConnectIDByXZ(const FIELDSYS_WORK * fsys, int x, int z);
extern const CONNECT_DATA * EventData_GetNowConnectDataByID(const FIELDSYS_WORK * fsys, int door_id);
extern int EventData_GetNowPosEventDataSize(const FIELDSYS_WORK * fsys);
extern const POS_EVENT_DATA * EventData_GetNowPosEventData(const FIELDSYS_WORK * fsys);
extern void EventData_LoadEncountData(ENCOUNT_DATA *enc_data, int zone_id);
//------------------------------------------------------------------
/**
 * @brief	npc_count取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	"npc_count"
 */
//------------------------------------------------------------------
extern u32 EventData_GetNpcCount(const FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
/**
 * @brief	npc_data取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	"npc_data"
 */
//------------------------------------------------------------------
extern const FIELD_OBJ_H* EventData_GetNpcData(const FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
/**
 * @brief	npc_dataの座標を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	gx		グリッドX
 * @param	gz		グリッドZ
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
extern BOOL EventData_NpcDataPosChange(FIELDSYS_WORK * fsys, int id, u16 gx, u16 gz );

//------------------------------------------------------------------
/**
 * @brief	npc_dataの方向を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	dir		方向
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
extern BOOL EventData_NpcDataDirChange(FIELDSYS_WORK * fsys, int id, int dir );

//------------------------------------------------------------------
/**
 * @brief	npc_dataの動作コードを書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	mv		動作コード
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
extern BOOL EventData_NpcDataMoveCodeChange(FIELDSYS_WORK * fsys, int id, int mv );

//------------------------------------------------------------------
/**
 * @brief	connect_dataの座標を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	x		セットするX
 * @param	z		セットするZ
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
extern BOOL EventData_ConnectDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );

//------------------------------------------------------------------
/**
 * @brief	connect_dataの接続先ゾーンIDを書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	zone	セットするゾーン
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
extern BOOL EventData_ConnectDataZoneChange(FIELDSYS_WORK * fsys, u16 id, u16 zone );

//------------------------------------------------------------------
/**
 * @brief	bg_dataの座標を書き換える
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	id		検索するID
 * @param	x		セットするX
 * @param	z		セットするZ
 * @return	"TRUE=成功、FALSE=失敗"
 */
//------------------------------------------------------------------
extern BOOL EventData_BgDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );

extern void EventData_LoadZoneData(FIELDSYS_WORK * fsys, int zone_id);
extern void EventData_SetFieldOBJ(FIELDSYS_WORK * fsys);

extern const ENCOUNT_DATA * EventData_GetEncountData(const FIELDSYS_WORK * fsys);
extern void * EventData_GetSpecialScript(const FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
/**
 * 地下に潜ることが出来る座標かどうかをチェック
 *
 * @param   fsys		フィールド制御ワークへのポインタ
 * @param   gx			チェックするＸ座標
 * @param   gz			チェックするＺ座標
 *
 * @retval  BOOL		"TRUE=潜ることができる FALSE=できない"
 */
//------------------------------------------------------------------
extern BOOL EventData_CheckIntoUGPos( const FIELDSYS_WORK* fsys, u16 gx, u16 gz );


#endif	/*	__EVENTDATA_H__ */
