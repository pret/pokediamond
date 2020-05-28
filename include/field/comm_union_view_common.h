//============================================================================================
/**
 * @file	comm_union_view_commmon.h
 * @brief	ユニオンルームOBJ描画ワークを外部から初期化できるように分離した
 * @date	2006.03.17
 */
//============================================================================================
#ifndef __COMM_UNION_VIEW_COMMON_H__
#define __COMM_UNION_VIEW_COMMON_H__

#include "field/fieldobj.h"


typedef struct UNION_CHAT_RINGBUF UNION_CHAT_RINGBUF;
typedef struct COMM_UNIONROOM_VIEW COMM_UNIONROOM_VIEW;

void UnionRoomView_ObjInit( COMM_UNIONROOM_VIEW *view );

// Objを全て隠す（消すわけではない）
extern void Union_BeaconObjAllVanish(FIELD_OBJ_SYS_PTR fldobjsys, COMM_UNIONROOM_VIEW *view);
extern void UnionRoomView_ObjAllRise( COMM_UNIONROOM_VIEW *view );


#endif