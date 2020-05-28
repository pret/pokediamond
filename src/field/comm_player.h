//=============================================================================
/**
 * @file	comm_player.c
 * @bfief	�ʐM�ő��葤�̃v���[���[��\������
 * @author	katsumi ohno
 * @date	05/07/14
 */
//=============================================================================

#ifndef __COMM_PLAYER_H__
#define	__COMM_PLAYER_H__

// ���肦�Ȃ����W�̏ꍇ�̖߂�l
#define COMM_PLAYER_INVALID_GRID (0xffff)

/// �R�~���j�P�[�V�����v���[���[�Ǘ��}�l�[�W���[������
extern BOOL CommPlayerManagerInitialize(void* work_area, FIELDSYS_WORK* pFSys,BOOL bUnder);
/// �R�~���j�P�[�V�����v���[���[�Ǘ��}�l�[�W���[�I��
extern void CommPlayerManagerFinalize(BOOL bDel);

/// �ʐM�v���[���[������
extern void CommPlayerManagerReset(void);
/// �ʐM�v���[���[�𕜋A����
extern void CommPlayerManagerReboot(void);
/// ������COMM_PARENT_ID�ɂ��ǂ�
extern void CommPlayerManagerReInit(void);
/// �ً}��~
extern void CommPlayerManagerStop(void);
// �閧��n�֓��������Ă����̂Ńv���[���[������
extern void CommPlayerManagerDeletePlayers(void);

/// �����̃f�[�^�̏�����
extern void CommPlayerMyDataInitialize(void);
// �����ڑ������ۂ̃f�[�^���p��
extern void CommPlayerMyDataCopy(int netID);
// ���p���f�[�^���q�@�ɑ��M
extern void CommPlayerSendPosServer(BOOL bLiveMessage);


/// ���̃N���X�����������ꂽ���ǂ�����Ԃ�
extern BOOL CommPlayerManagerIsInitialize(void);
/// �����̈ʒu�𑗐M
extern void CommPlayerSendPosXZ(BOOL bLiveMessage,int xpos,int zpos);
/// �����̈ʒu�𑗐M
extern void CommPlayerSendPos(BOOL bLiveMessage);
/// �R�~���j�P�[�V�����v���[���[���[�N�Ǘ����[�N�T�C�Y
extern u32 CommPlayerGetWorkSize(void);
/// �J�[�h���̗v���R�}���h����M
extern void CommPlayerRecvReqCardInfo(int netID, void* pData);
/// �J�[�h���̎�M
extern void CommPlayerRecvCardInfo(int netID, int size, void* pData, void* pWork);
/// �J�[�h���̃T�C�Y��Ԃ�
extern int CommPlayerGetRecvCardInfoSize(void);
/// �ꏊ���̎�M
extern void CommPlayerRecvPlace(int netID, int size, void* pData, void* pWork);
/// �v���[���[������������M
extern void CommPlayerRecvDelete(int netID, int size, void* pBuff, void* pWork);
/// �ꏊ���̃T�C�Y��Ԃ�
extern int CommPlayerGetRecvPlaceSize(void);
/// ��b�𑗐M����
// �g���K�v�͂Ȃ��͂��Ȃ̂ŕ���
//extern void CommPlayerSendTalk(int targetID, int msgSize, u16* pMsg);
/// ��b�f�[�^����M����
extern void CommPlayerRecvTalk(int netID, int size, void* pData, void* pWork);
/// ��b�f�[�^����M����i�T�[�o�[���j
extern void CommPlayerRecvTalk_ServerSide(int netID, int size, void* pData, void* pWork);
/// ��~��ԉ���
extern void CommPlayerRecvFreezeEnd(int netID, int size, void* pData, void* pWork);

extern void CommPlayerRecvFixedTalk(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvFixedTalk_ServerSide(int netID, int size, void* pData, void* pWork);
extern int CommPlayerRecvFixedTalkSize(void);

extern BOOL CommPlayerIsMyMoveControl(void);
extern BOOL CommPlayerGetMoveControl(int netID);
extern void CommPlayerSetMoveControl(BOOL bMoveControl);
extern void CommPlayerSetMoveControl_Server(int netID, BOOL bMoveControl);
extern void CommPlayerRecvMoveControl(int netID, int size, void* pData, void* pWork);

// �g���b�v�ɂ������Ă��邩�ǂ���
extern BOOL CommPlayerIsTrapBind(int targetID);
extern void CommPlayerSetFEExclamationAdd(int netID);
extern void CommPlayerSetFEOkAdd(int netID);
extern void CommPlayerSetFENoneAdd(int netID);
/// �l�b�g���[�N�v���[���[�̈ړ�����
extern void CommPlayersMove(FIELDSYS_WORK * repw, BOOL bMoveControl);
/// �l�b�g���[�N�v���[���[�̈ړ������ɂȂ��Ă��邩�ǂ���
extern BOOL CommPlayerIsControl(void);
// ���̃v���[���[���Ȃ����Ă��邩�ǂ���
extern BOOL CommPlayerIsActive(int netID);

extern void CommPlayerHold_Control(void);

extern void CommPlayerBlowStart( int netID, int dir , BOOL bHit);
extern void CommPlayerBlowExit(int victimNetID);
extern void CommPlayerBlowFirst(int victimNetID);
extern void CommPlayerBlowAnimStart( int netID, int dir , BOOL bHit );
extern void CommPlayerBlowAnimStop( int netID );

extern void CommPlayerRecvIDPlace(int netID, int size, void* pBuff, void* pWork);
extern void CommPlayerClientMoveControl(int netID, int moveX, int moveZ, FIELDSYS_WORK* pFSys);
extern int CommPlayerGetRecvIDPlaceSize(void);

// �e�v���[���[�̍��W���擾���� S��������T�[�o�[

extern int CommPlayerGetPosDigFossilX(int netID);
extern int CommPlayerGetPosDigFossilZ(int netID);
extern int CommPlayerGetPosXDirAdd(int netID);
extern int CommPlayerGetPosZDirAdd(int netID);
extern int CommPlayerGetPosXOrg(int netID);
extern int CommPlayerGetPosZOrg(int netID);
extern int CommPlayerGetPosX(int netID);
extern int CommPlayerGetPosZ(int netID);
extern int CommPlayerGetDir(int netID);
extern int CommPlayerGetPosSXDirAdd(int netID);
extern int CommPlayerGetPosSZDirAdd(int netID);
extern int CommPlayerGetPosSX(int netID);
extern int CommPlayerGetPosSZ(int netID);
extern int CommPlayerGetPosSXOrg(int netID);
extern int CommPlayerGetPosSZOrg(int netID);
extern int CommPlayerGetSDir(int netID);
extern void CommPlayerSetLook_Server(int netID, int targetID);
extern void CommPlayerSetLook(int netID, int targetID);
// ��ԃZ�b�g
extern void CommPlayerSetCondition(int victimNetID, int condition);
extern void CommPlayerResetCondition(int victimNetID);
// ��n�ɒ��ڈړ�
extern void CommPlayerBaseTeleportClient(int netID, int x, int z, int dir);
extern void CommPlayerBaseTeleportServer(int netID, int x, int z, int dir);

extern void CommPlayerRecvCheckFieldMenuOpen(int netID, int size, void* pData, void* pWork);
extern int CommPlayerIsAlive(int xpos, int zpos);
extern void CommPlayerRecvResultFieldMenuOpen(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvResultUGMenuOpen(int netID, int size, void* pData, void* pWork);

extern BOOL CommPlayerCheckBattleJump(void);
extern void CommPlayerBattleDirSet(void);
extern BOOL CommPlayerMoveBattlePos(void);

extern BOOL CommPlayerDeliveryFlagData(int netID);
extern BOOL CommPlayerDeleteFlagData(int netID);
extern BOOL CommPlayerIsFlagData(int netID);
extern BOOL CommPlayerGetFlag(int myNetID, int targetNetID);
extern BOOL CommPlayerFlagTalkCheck(int netID, int targetID, BOOL bNPCTalk);
extern BOOL CommPlayerFlagDigCheck(int netID);
extern int CommPlayerRecvFlagStateServerRetGetSize(void);
extern void CommPlayerRecvFlagState(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvFlagStateServerRet(int netID, int size, void* pData, void* pWork);
// ���΂̕�����Ԃ�
extern int CommPlayerGetReverseDir(int dir);
// �������������ݒ肷��
extern void CommPlayerSetGiddyStep(int netID,int count);
extern void CommPlayerResetGiddyStep(int netID);

extern void CommPlayerSetHole(int netID,int count);
extern void CommPlayerResetHole(int netID);

extern int CommPlayerGetWalkCount(int netID);
extern void CommPlayerSetWalkCount(void);
extern int CommPlayerGetWalkCountServer(int netID);

extern void CommPlayerRecvOtherTalk(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvOtherTalk_ServerSide(int netID, int size, void* pData, void* pWork);

extern void CommPlayerDestroy(u8 netID, BOOL bExit,BOOL bDel);

extern void CommPlayerSetDir(int dir);
extern void CommPlayerSetClientDir(int netID, int dir);
extern int CommPlayerGetClientDir(int netID);

extern BOOL CommPlayerNPCHitCheck(int x,int z);

extern void CommPlayerHold(void);
extern void CommPlayerHoldEnd(void);

extern void CommPlayerHoldBit(int bit);
extern void CommPlayerHoldBitEnd(int bit);

extern void CommPlayerSetForcePos(void);
extern void CommPlayerFirstMoveEnable(void);
extern void CommPlayerFirstMoveDisable(void);

extern void CommPlayerRecvStartLineSet(int netID, int size, void* pData, void* pWork);

// ����̃n�^�f�[�^�𑗂�
extern int CommPlayerNowFlagSize(void);
extern u8* CommPlayerGetFlagRecvBuff( int netID, void* pWork, int size);
extern void CommPlayerNowFlagSend(void);
extern void CommPlayerRecvNowFlagDataReq(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvNowFlagDataArray(int netID, int size, void* pData, void* pWork);
extern int CommPlayerNowFlagDataArraySize(void);
extern void CommPlayerRecvNowFlagDataEnd(int netID, int size, void* pData, void* pWork);
extern BOOL CommPlayerIsNowFlagDataEnd(void);
extern void CommPlayerParentFlagDataReset(void);

extern void CommPlayerFlagChange(void);

extern void CommSetForceDir(void);

extern void CommPlayerHoldBitOff(void);

#define _HOLD_ALL (0)
#define _HOLD_FLAG_RIP_OFF (0x01)
#define _HOLD_FLAG_NO_TALK (0x02)
#define _HOLD_FLAG_STOLEN (0x04)
#define _HOLD_FLAG_STOLEN_MY (0x08)
#define _HOLD_TRAP (0x10)
#define _HOLD_FLAG_NO_DIG (0x20)
#define _HOLD_FLAG_PC_GET (0x40)
#define _HOLD_TOUCH (0x80)
#define _HOLD_FLAG_DEL (0x100)




#endif //__COMM_PLAYER_H__
