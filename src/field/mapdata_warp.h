//============================================================================================
/**
 * @file	mapdata_warp.c
 * @brief	���[�v�p�f�[�^�֘A�w�b�_
 * @date	2005.12.19
 */
//============================================================================================

#ifndef	__MAPDATA_WARP_H__
#define	__MAPDATA_WARP_H__

#include "field_common.h"
#include "field/location.h"

//--------------------------------------------------------------------------------------------
//	���[�v�Ƃѐ�
//--------------------------------------------------------------------------------------------
extern void WARPDATA_GetWarpLocation(int warp_id, LOCATION_WORK * loc);
extern void WARPDATA_GetRevivalLocation(int warp_id, LOCATION_WORK * loc);
extern int WARPDATA_SearchByRoomID(int zone_id);
extern int WARPDATA_SearchByFieldID(int zone_id);
extern int WARPDATA_GetInitializeID(void);
extern int WARPDATA_SearchForFly(int zone_id, int gx, int gz);

//--------------------------------------------------------------------------------------------
//	�����t���O
//--------------------------------------------------------------------------------------------
extern void ARRIVEDATA_SetArriveFlag( FIELDSYS_WORK * fsys, int zone_id);
extern BOOL ARRIVEDATA_GetArriveFlag(FIELDSYS_WORK * fsys, int warp_id);

#endif	__MAPDATA_WARP_H__
