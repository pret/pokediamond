//=============================================================================
/**
 * @file	ug_manager.h
 * @brief	�n���̃T�[�r�X�𓝊�����N���X
             �P�U�~�P�U�������݂��Ȃ��̂ŁA���̕������m�ۂ��Ă���܂�
 * @author	Katsumi Ohno
 * @date    2005.09.28  -> 2006.02.07 comm_under���疼�O�ύX
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

// ���[�_�ɕԂ����
typedef enum{
  RADAR_TYPE_NONE,    // �\���Ȃ�
  RADAR_TYPE_MY,       // �����̈ʒu
  RADAR_TYPE_TARGET,    // ����̈ʒu
  RADAR_TYPE_SECLETBASE, // �閧��n
  RADAR_TYPE_FLAG_NORMAL,  // �m�[�}���t���b�O
  RADAR_TYPE_FLAG_BLONZE,  // �u�����Y�t���b�O
  RADAR_TYPE_FLAG_SILVER,  // �V���o�[�t���b�O
  RADAR_TYPE_FLAG_GOLD,   // �S�[���h�t���b�O
  RADAR_TYPE_FLAG_PLATINA,  // �v���`�i�t���b�O
  RADAR_TYPE_BALL,        // ����
  RADAR_TYPE_TRAP,       // ��ȁi�l�̒u�������́j
  RADAR_TYPE_TRAP_NATURAL,  // �V�R�̃��i
  RADAR_TYPE_FOSSIL        // ����
} RADAR_DISP_TYPE_ENUM;


typedef struct{
    u16 xpos;
    u16 zpos;
} Grid;

// �R�[���o�b�N�֐��̏���
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
///�閧��n�͈͓��ɂ��邩�ǂ���
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

// ������Z�b�g�A�b�v����閧��n�O�b�Y�f�[�^��Ԃ�
extern SECRETBASEDATA* UgManUgSetupSecretBaseData(SAVEDATA * sv);
//   ������Z�b�g�A�b�v����閧��n��X�u���b�N��Ԃ�
extern int UgManUgSetupSecretBaseBlockX(void);
//   ������Z�b�g�A�b�v����閧��n��Z�u���b�N��Ԃ�
extern int UgManUgSetupSecretBaseBlockZ(void);
// �p�P�b�g�T�C�Y
extern int CommUnderRecvCheckAbuttonSize(void);
// A�{�^�������x��������Ȃ��悤��
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


#define _NOTGET_TRAP_RESERVE (0x10)  // 㩂��E���Ȃ��\�肪����
#define _GET_STONE_RESERVE (0x20)  // �΂��E���\�肪����

#endif //__UG_MANAGER_H__

