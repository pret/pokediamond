//=============================================================================
/**
 * @file	comm_secretbase_info.h
 * @brief	�n���̔閧��n�����Ǘ�����N���X
 * @author	Katsumi Ohno
 * @date    2005.10.04
 */
//=============================================================================

#ifndef __UG_SECRETBASE_H__
#define __UG_SECRETBASE_H__

#include "savedata/undergrounddata.h"

/// �閧��n��񏉊���
extern void CommSecretBaseInfoInitialize(void* pWork, FIELDSYS_WORK* pFSys);
extern void CommSecretBaseInfoReset(void);
extern void CommSecretBaseInfoReboot(void);
/// �閧��n��񏈗��I��
extern void CommSecretBaseInfoFinalize(void);
extern void CommSecretBaseInfoReInit(void);
extern void CommSecretBaseInfoParentDel(void);
/// ���[�N�S�̂̃T�C�Y��Ԃ�
extern int CommSecretBaseInfoGetWorkSize(void);
/// �Z�[�u�f�[�^���玩���̂�������쐬
extern void UgSecretBaseMakeMyAttr(FIELDSYS_WORK* pFSys);
/// �q�@���̃v���O����  �e�@�ɔ閧��n�𑗂�
extern void CommSecretBaseInfoChildSendStart(void);
/// �閧��n�f�[�^��M
extern void CommSecretBaseInfoRecvData(int netID, int size, void* pData, void* pWork);
/// �閧��n�f�[�^�T�C�Y
extern int CommSecretBaseInfoGetDataSize(void);
/// �e�@����閧��n�f�[�^���͂������ǂ���
extern BOOL CommSecretBaseInfoIsChildRecv(void);
/// �e�@����閧��n�f�[�^���͂����̂ŁA�t���O������
extern void CommSecretBaseResetChildRecv(void);

extern BOOL CommSecretBaseInfoIsPosRecv(void);

extern void CommSecretBaseResetPosRecv(void);

extern BOOL CommSecretBaseIsTraveling(int netID);

/// �閧��n�ړ����I���������Ƃ𑗐M
extern void CommSecretBaseInfoJumpEnd(void);
/// �閧��n�ړ����I���������Ƃ���M
extern void CommSecretBaseInfoRecvJumpEnd(int netID, int size, void* pData, void* pWork);

extern void UgSecretBaseRecvJumpEvent(int netID, int size, void* pData, void* pWork);

extern void UgSecretBaseRecvMoveFailed(int netID, int size, void* pData, void* pWork);

extern int UgSecretBaseRecvJumpEventSize(void);

extern void UgSecretBaseRecvJumpEventRes(int netID, int size, void* pData, void* pWork);

extern int UgSecretBaseRecvJumpEventResSize(void);

extern void CommSecretBaseInfoParentSendStart(int netID);

extern void CommSecretBaseInfoRecvData(int netID, int size, void* pData, void* pWork);
extern void CommSecretBaseInfoRecvDataServer(int netID, int size, void* pData, void* pWork);
extern void CommSecretBaseInfoRecvPos(int netID, int size, void* pData, void* pWork);
extern int CommSecretBaseInfoGetDataSize(void);
extern int CommSecretBaseInfoGetPosSize(void);

extern void CommSecretBaseInfoStepFunc(void);
extern BOOL CommSecretBaseSingleStepFunc(int playerId, int moveX, int moveZ);

extern BOOL CommSecretBaseInfoGetActionMessage(STRBUF* pStrBuf);

extern void CommSecretBaseInfoRecvRetJump(int netID, int size, void* pData, void* pWork);
extern int CommSecretBaseInfoGetRetJumpSize(void);

extern void CommSecretBaseDrillStart(void);
extern void CommSecretBaseRecvDrillStart(int netID, int size, void* pData, void* pWork);
extern void CommSecretBaseRecvDrillStartResult(int netID, int size, void* pData, void* pWork);
extern int CommSecretBaseDrillStartResultSize(void);

/// �ʐM���E�����l�̔閧��n������
extern void UgSecretBaseResetPlayer(int netID);
extern void UgSecretBaseDestroyPlayer(int netID);
extern void UgSecretBaseDestroyDoor(int netID);
extern void UgSecretBaseDestroyPlayerDontBaseIn(int netID);
/// �閧��n�̓��e����Ԃ�
extern SECRETBASEDATA* UgSetupSecretBaseData(SAVEDATA * sv);
///������Z�b�g�A�b�v����閧��n�̃u���b�N��Ԃ�
extern int UgSetupSecretBaseBlockX(void);
extern int UgSetupSecretBaseBlockZ(void);
/// �閧��n�O�b�Y������f�[�^���݂ĕ����邩�ǂ�������ׂ�
extern BOOL UgSecretBaseMoveing(int x, int z);
/// ���悤�����̉�b�X�^�[�g
extern int UgSecretBaseTalkStart(int messageNo);
/// ���悤�����̉�b�I���
extern void UgSecretBaseTalkEnd(void);
/// �O�b�Y�̖��O�����b�Z�[�W�ɕ\��������ꍇ�̊֐�
extern void UgSecretBaseTalkRegisterGoodsName(int type);
/// �����Q�������b�Z�[�W�ɕ\��������ꍇ�̊֐�
extern void UgSecretBaseTalkRegisterNum2(int number,int index);
/// A�{�^���ŃO�b�Y�̃`�F�b�N��������
extern BOOL UgSecretBaseGoodsCheck(int netID, Grid* pTouch);
/// A�{�^���ŃO�b�Y�̃`�F�b�N��������
extern void UgSecretBaseRecvGoodsCheck(int netID, int size, void* pData, void* pWork);
extern int UgSecretBaseGetRecvGoodsCheckSize(void);

extern void UgSecretBaseSetFlagGetLog(int netID, int targetPCNetID);
extern void UgSecretBaseSetFlagReverseLog(int myNetID);
extern void UgSecretBaseSetFlagConquerLog(int myNetID, int targetID);


extern int UgSBGetLVUPFlagRetSize(void);
extern void UgSBRecvLVUPFlagRet(int netID, int size, void* pData, void* pWork);
extern void UgSBRecvLVUPFlag(int netID, int size, void* pData, void* pWork);

// ����
extern BOOL UgSecretBaseTrapGoodsCheck(int netID);
// ���Z�b�g
extern BOOL UgSecretBaseTrapGoodsReset(int netID);

extern void UgSecretBaseRemovePlayer(int netID);
//
extern BOOL UgSecretBaseRemovePlayer_Client(int playerID, BOOL bRemove);

extern BOOL UgSecretBaseIsOtherEnter(void);

extern void UgSecretBaseErrorMoveTickets(void);
extern void UgSecretBaseErrorDisconnectTickets(void);
// �q�@���閧��n�ɂ����ꍇ�A��������O�ɂłĂ��炤
extern void UgSecretBaseFirstConnectChild(int netID);




extern int UgSecretBaseEscapePosX(void);
extern int UgSecretBaseEscapePosZ(void);
extern int UgSecretBaseEscapeDir(void);
extern void UgSecretBaseEscapePosSXSet(int netID,int x);
extern void UgSecretBaseEscapePosSZSet(int netID,int z);
extern void UgSecretBaseEscapeDirSet(int netID,int dir);

extern void UgSecretBaseBootOn(BOOL bOn);


#endif //__UG_SECRETBASE_H__
