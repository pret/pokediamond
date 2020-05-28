//============================================================================================
/**
 * @file	comm_union_view_commmon.h
 * @brief	���j�I�����[��OBJ�`�惏�[�N���O�����珉�����ł���悤�ɕ�������
 * @date	2006.03.17
 */
//============================================================================================
#ifndef __COMM_UNION_VIEW_COMMON_H__
#define __COMM_UNION_VIEW_COMMON_H__

#include "field/fieldobj.h"


typedef struct UNION_CHAT_RINGBUF UNION_CHAT_RINGBUF;
typedef struct COMM_UNIONROOM_VIEW COMM_UNIONROOM_VIEW;

void UnionRoomView_ObjInit( COMM_UNIONROOM_VIEW *view );

// Obj��S�ĉB���i�����킯�ł͂Ȃ��j
extern void Union_BeaconObjAllVanish(FIELD_OBJ_SYS_PTR fldobjsys, COMM_UNIONROOM_VIEW *view);
extern void UnionRoomView_ObjAllRise( COMM_UNIONROOM_VIEW *view );


#endif