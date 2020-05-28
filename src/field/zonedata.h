//============================================================================================
/**
 * @file	zonedata.h
 * @brief	ゾーン用データ
 * @date	2005.08.05
 *
 * 2005.10.18	本番用データに切り替えた
 */
//============================================================================================

#ifndef	__ZONEDATA_H__
#define	__ZONEDATA_H__

#include "field_common.h"

//------------------------------------------------------------------
//	ゾーンIDごとのデータ取得
//------------------------------------------------------------------
extern BOOL ZoneData_GetEncountFlag(int zone_id);
extern const u16 ZoneData_GetMatrixID(int zone_id);
extern const u16 ZoneData_GetAreaID(int zone_id);
extern const u16 ZoneData_GetMoveModelID(int zone_id);
extern u32 ZoneData_GetMsgArchiveID(int zone_id);
extern u32 ZoneData_GetScriptArchiveID(int zone_id);
extern u32 ZoneData_GetSpScriptArchiveID(int zone_id);
extern u16 ZoneData_GetDayBGMID(int zone_id);
extern u16 ZoneData_GetNightBGMID(int zone_id);
extern u32 ZoneData_GetEventID(int zone_id);
extern u32 ZoneData_GetEncountArchiveID(int zone_id);
extern u32 ZoneData_GetPlaceNameID(int zone_id);
extern u32 ZoneData_GetWeatherID(int zone_id);
extern u32 ZoneData_GetCameraID(int zone_id);
extern u32 ZoneData_GetBattleBGID(int zone_id);
extern BOOL ZoneData_GetEnableEscapeFlag(int zone_id);
extern BOOL ZoneData_GetEnableDashFlag(int zone_id);
extern BOOL ZoneData_GetEnableBicycleFlag(int zone_id);
extern BOOL ZoneData_GetEnableFlyFlag(int zone_id);

extern int ZoneData_CheckRange(int zone_id);

#define	ZoneData_GetBGMID	ZoneData_GetDayBGMID

#ifdef	PM_DEBUG
extern const char * ZoneData_GetZoneName(int zone_id);
#endif
//------------------------------------------------------------------
//	ゾーンIDによる各種判定ロジック
//------------------------------------------------------------------
extern BOOL ZoneData_GetEnableTeleportFlag(int zone_id);

extern BOOL ZoneData_IsSinouField(int zone_id);
extern BOOL ZoneData_IsPokecen(int zone_id);
extern BOOL ZoneData_IsDungeon(int zone_id);
extern BOOL ZoneData_IsRoom(int zone_id);
extern BOOL ZoneData_IsOutDoor(int zone_id);
extern BOOL ZoneData_IsCommPlayableZone(int zone_id);
extern BOOL ZoneData_IsUnionRoom(const int zone_id);

extern BOOL ZoneData_IsSpFishingZone(const int zone_id);
extern BOOL ZoneData_IsHillBackZone(const int zone_id);
extern BOOL ZoneData_IsNaturalPark(const int zone_id);
extern BOOL ZoneData_IsUseTenkainofueZone(const int zone_id);
extern BOOL ZoneData_IsPokecen2F(const int zone_id);

//------------------------------------------------------------------
//	ゾーンIDごとの各種データ取得
//	※全ゾーン分のデータを持っているわけではなく、一部のみ持っている
//------------------------------------------------------------------
extern int ZoneData_GetShinkaPlaceID(int zone_id);


#endif	/* __ZONEDATA_H__ */

