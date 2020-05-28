//============================================================================================
/**
 * @file	map_jump.h
 * @brief	マップジャンプ制御
 * @date	2006.02.08
 * @author	Nozomu Saito
 */
//============================================================================================
#ifndef __MAP_JUMP_H__
#define __MAP_JUMP_H__

#include "field_common.h"
#include "field_event.h"

typedef BOOL (*MAP_JUMP_FUNC)(GMEVENT_CONTROL *);
typedef void (*MAP_JUMP_POS_SET)(FIELDSYS_WORK *);

extern void MJUMP_RequestWipe(	GMEVENT_CONTROL * event,
								int inPattern, int inMain,
								int inSub, u16 inCol,
								int inDiv, int inSync,
								int inHeap);

extern void MJUMP_ChangeMap(FIELDSYS_WORK * fsys, const int zone, const int door_id,
						const int inX, const int inZ, const int inDir, const int inType );
extern void MJUMP_ChangeMapByLocation(	FIELDSYS_WORK * fsys, const int zone, const int door_id,
										const int inX, const int inZ, const int inDir);
#endif //__MAP_JUMP_H__
