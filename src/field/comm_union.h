//=============================================================================
/**
 * @file	comm_union.h
 * @brief	ユニオンルーム制御処理
 * @author	Akito Mori
 * @date    2005.12.10
 */
//=============================================================================

#ifndef	__COMM_UNION_H__
#define	__COMM_UNION_H__

#include "system\wordset.h"

typedef struct COMM_UNIONROOM_WORK COMM_UNIONROOM_WORK;

extern COMM_UNIONROOM_WORK *Comm_UnionRoomInit(FIELDSYS_WORK* fSys);
extern FIELDSYS_WORK* Union_FielsSysPtrGet(COMM_UNIONROOM_WORK *cuw);
extern WMBssDesc* Union_BeaconPtrGet(COMM_UNIONROOM_WORK *cuw, int no);
extern PMS_DATA * Union_GetMyPmsData( COMM_UNIONROOM_WORK *cuw );

extern void Comm_UnionFinalize(FIELDSYS_WORK *fsys);
extern void _commCheckFunc(TCB_PTR tcb, void* work);
extern int  Union_ConnectIdSet(COMM_UNIONROOM_WORK *cuw, int no);
extern int  Union_ConnectStart( COMM_UNIONROOM_WORK *cuw, int objno, u16 type );
extern u32  Union_ConnectResultGet(COMM_UNIONROOM_WORK *cuw);
extern int  Union_GetTalkNumber( COMM_UNIONROOM_WORK *cuw, int no, int mode, WORDSET *wordset );
extern void Union_SetMyPmsData( COMM_UNIONROOM_WORK *cuw, PMS_DATA *pms );
extern void Union_CommWorkClear( COMM_UNIONROOM_WORK *cuw);
extern void Union_TrainerNameRegist( WORDSET *wordset, int type, int no, MYSTATUS *mystatus, PMSW_SAVEDATA *pmssave );
extern void *Union_GetTrainerCardWorkPtr( FIELDSYS_WORK *fsys );
extern void Comm_UnionRoomViewReturn( FIELDSYS_WORK *fsys );
extern int  Union_ConnectIndexGet(COMM_UNIONROOM_WORK *cuw);
extern int  Union_GetInfomationTalkNo( COMM_UNIONROOM_WORK *cuw,  WORDSET *wordset );
extern int  Union_GetCardTalkNo( WORDSET *wordset );
extern int  Union_CancelRecv( COMM_UNIONROOM_WORK *cuw );
extern int  Union_ParentSendCancel( COMM_UNIONROOM_WORK *cuw, int mes );
extern void Union_BattlePokeListResult( int flag );
extern void *Union_TrainerCardWorkInit( COMM_UNIONROOM_WORK *cuw );
extern void Union_trainerCardWorkFree( COMM_UNIONROOM_WORK *cuw );
extern void Union_SendTrainerCardData( COMM_UNIONROOM_WORK *cuw );
extern u16  Union_GetBattleStartCheckResult( COMM_UNIONROOM_WORK *cuw );

extern const u16 Union_GroupObjTable[];

// 最大子機接続人数
#define UNION_CONNECT_CHILD_MAX	( 4 )

// 最大接続人数
#define UNION_CONNECT_MAX		( UNION_CONNECT_CHILD_MAX+1 )

//--------------------------------------------------------------
// スクリプト用
//--------------------------------------------------------------

// スクリプトで実行した選択結果を貰う
extern void Union_ScriptResultGet( COMM_UNIONROOM_WORK *cuw, int var, u32 result);

// 親機のスタートを待つ
extern u32 Union_ParentStartCommandSet( COMM_UNIONROOM_WORK *cuw );

// 子機からもらった内容をスクリプトに返す
extern u32 Union_ChildSelectCommandSet(COMM_UNIONROOM_WORK *cuw);



//--------------------------------------------------------------
// 通信コールバック用
//--------------------------------------------------------------
extern void CommUnionRecvStatus(int netID, int size, void* pBuff, void* pWork);
extern void CommUnionRecvSelect(int netID, int size, void* pBuff, void* pWork);
extern void CommUnionRecvTalk(int netID, int size, void* pBuff, void* pWork);
extern void CommUnionRecvYes(int netID, int size, void* pBuff, void* pWork);
extern void CommUnionRecvNo(int netID, int size, void* pBuff, void* pWork);
extern void CommUnionStartNext(int netID ,int size, void* pBuff, void* pWork);
extern void CommUnionEndConnect(int netID ,int size, void* pBuff, void* pWork);
extern void CommUnionRecvTrainerCard(int netID ,int size, void* pBuff, void* pWork );
extern void CommUnionRecvBattlePokeListResult(int netID ,int size, void* pBuff, void* pWork );

extern u8* getTrainerCardRecvBuff( int netID, void* pWork, int size);


#endif  //__COMM_UNION_H__