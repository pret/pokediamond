//=============================================================================
/**
 * @file	ug_manager.h
 * @brief	地下のサービスを統括するクラス
             １６×１６しか存在しないので、その分だけ確保してあります
 * @author	Katsumi Ohno
 * @date    2005.09.28  -> 2006.02.07 comm_underから名前変更
 */
//=============================================================================

#ifndef __UG_MANAGER_H__
#define __UG_MANAGER_H__

#include "communication/communication.h"
#include "system/msgdata.h"
#include "gflib/strbuf.h"
#include "../field_common.h"
#include "savedata/undergrounddata.h"  //SECRETBASEDATA
#include "ug_message.h"

#define COMM_UG_INVALID_GRID     (0xffff)
#define TCB_PRIORITY_NORMAL (100)

// レーダに返す状態
typedef enum{
  RADAR_TYPE_NONE,    // 表示なし
  RADAR_TYPE_MY,       // 自分の位置
  RADAR_TYPE_TARGET,    // 相手の位置
  RADAR_TYPE_SECLETBASE, // 秘密基地
  RADAR_TYPE_FLAG_NORMAL,  // ノーマルフラッグ
  RADAR_TYPE_FLAG_BLONZE,  // ブロンズフラッグ
  RADAR_TYPE_FLAG_SILVER,  // シルバーフラッグ
  RADAR_TYPE_FLAG_GOLD,   // ゴールドフラッグ
  RADAR_TYPE_FLAG_PLATINA,  // プラチナフラッグ
  RADAR_TYPE_BALL,        // たま
  RADAR_TYPE_TRAP,       // わな（人の置いたもの）
  RADAR_TYPE_TRAP_NATURAL,  // 天然のワナ
  RADAR_TYPE_FOSSIL        // 化石
} RADAR_DISP_TYPE_ENUM;


typedef struct{
    u16 xpos;
    u16 zpos;
} Grid;

// コールバック関数の書式
typedef Grid* (*PTRCommSearchFunc)(Grid* pGrid, int index);

extern COMM_MESSAGE* CommUnderGetMsgUnderWorld(void);
extern COMM_MESSAGE* CommUnderGetMsgUnderFlag(void);
extern COMM_MESSAGE* CommUnderGetMsgUnderShop(void);
extern COMM_MESSAGE* CommUnderGetMsgUnderEdit(void);
extern COMM_MESSAGE* CommUnderGetMsgUnderItem(void);

extern void CommUnderAllMsgForceDel(void);

extern void CommUnderOptionInitialize(FIELDSYS_WORK* pFSys);
extern void CommUnderOptionReset(void);
extern void CommUnderOptionReboot(void);
extern void CommUnderOptionReInit(FIELDSYS_WORK* pFSys);
extern BOOL CommUnderCheckPlace(int x,int y);
extern void CommUnderProcess(void);
extern void CommUnderItemSearchInitialize(int limit, PTRCommSearchFunc pFunc);
extern int CommUnderMatchItemTbl(Grid* pGrid);
extern int CommUnderSearchItemTbl(Grid* pGrid);
extern void UgMgrMenuCheck(void);
extern void UgMgrTalkCheck(u8 bTalkCheck);
extern void CommUnderRecvCheckAbutton(int netID, int size, void* pData, void* pWork);
extern BOOL CommUnderGetActionMessage(STRBUF* pStrBuf);
extern void CommUnderOptionFinalize(void);
///秘密基地範囲内にいるかどうか
extern BOOL UgSecretBaseIsSecretBasePlace(int x, int z);

#include "../comm_command_field.h"
#include "../comm_player.h"
#include "../comm_player_condition.h"
#include "ug_talk.h"
#include "ug_trap.h"
#include "ug_goods.h"
#include "ug_dig_stone.h"
#include "ug_dig_fossil.h"
#include "ug_secretbase.h"
#include "ug_bag.h"
#include "ug_pc.h"
#include "ug_record.h"
#include "ug_snd_def.h"

// 今からセットアップする秘密基地グッズデータを返す
extern SECRETBASEDATA* UgManUgSetupSecretBaseData(SAVEDATA * sv);
//   今からセットアップする秘密基地のXブロックを返す
extern int UgManUgSetupSecretBaseBlockX(void);
//   今からセットアップする秘密基地のZブロックを返す
extern int UgManUgSetupSecretBaseBlockZ(void);
// パケットサイズ
extern int CommUnderRecvCheckAbuttonSize(void);
// Aボタンを何度も押されないように
extern void UgMgrKeyCountDown(void);

extern void UgManagerRecvTouchResult1(int netID, int size, void* pData, void* pWork);
extern void UgManagerRecvTouchResult2(int netID, int size, void* pData, void* pWork);

extern int UgMgrGetDispPointX(int index);
extern int UgMgrGetDispPointZ(int index);
extern int UgMgrGetDispPointInfo(int index);

extern void UgMgrSetNoneRadarDisp(void);
extern void UgMgrSetMyTrapRadarDisp(void);
extern void UgMgrSetStoneRadarDisp(void);
extern void UgMgrSetTrapRadarDisp(void);
extern void UgMgrSetFossilRadarDisp(void);

extern void UgMgrSetTalkLog(int myNetID, int targetID);
extern void UgMgrSetTalkOtherLog(int myNetID);
extern void UgMgrSetPointLog(int myNetID, int num);
extern void UgMgrSetReturnLog(int myNetID);
extern void UgMgrStartReturnLog(int myNetID);

extern void UgMgrOpenRecordKey(u16 keyBaseName);
extern void UgMgrSetRecordKey(u16 windowName, u16 cursor, u16 line);
extern u16 UgMgrGetRecordKeyLine(u16 windowName);
extern u16 UgMgrGetRecordKeyCursor(u16 windowName);
extern void UgMgrEraseRecordKey(u16 windowName, u16 cursor, u16 line);

extern BOOL UgMgrRadarLogDouble(MYSTATUS* pMy, MYSTATUS* pTarget, int msgNo, STRBUF* pStrBuf);
extern BOOL UgMgrRadarLogSingle(MYSTATUS* pMy, int index, int msgNo, STRBUF* pStrBuf);

extern void UgMgrRecvNPCTalk(int netID, int size, void* pData, void* pWork);

typedef void (*ForceDeleteFunc)(TCB_PTR pTCB, void* work);

extern void UgMgrSetNowTCB(void* work,TCB_PTR pTCB, ForceDeleteFunc pFunc);
extern void UgMgrEndNowTCB(void);
extern BOOL UgMgrForceExitNowTCB(void);

extern BOOL UgMgrIsFirstMoveControlEnable(int netID);

extern BOOL UgMgrTouchCheck(void);


extern void UgInitialDataSend(void);
extern void UgInitialDataRecv(int netID, int size, void* pData, void* pWork);
extern int UgInitialDataSendSize(void);

extern void CommUgRecvChildStateNormal(int netID, int size, void* pData, void* pWork);
extern int CommUgGetChildStateNormalNum(void);


#define _NOTGET_TRAP_RESERVE (0x10)  // 罠を拾えない予定がある
#define _GET_STONE_RESERVE (0x20)  // 石を拾う予定がある

#endif //__UG_MANAGER_H__

