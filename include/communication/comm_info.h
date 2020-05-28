//=============================================================================
/**
 * @file	comm_info.h
 * @brief	�ʐM�œ�������~���Ă����N���X
 * @author	Katsumi Ohno
 * @date    2005.08.22
 */
//=============================================================================

#ifndef __COMM_INFO_H__
#define __COMM_INFO_H__

#include "savedata/mystatus.h"
#include "savedata/regulation.h"
#include "wifi/dwc_rap.h"

/// ������
extern void CommInfoInitialize(SAVEDATA* pSaveData, const REGULATION* pReg);
/// �J��
extern void CommInfoFinalize(void);
/// ���[�N�T�C�Y�𓾂�
extern int CommInfoGetWorkSize(void);
/// ������������ł��邩�ǂ����Ԃ�
extern BOOL CommInfoIsInitialize(void);
/// �|�P�����f�[�^�̑��M
extern void CommInfoSendPokeData(void);
/// �v���[���[�f�[�^�̃T�C�Y�𓾂�
extern int CommInfoGetPlayerDataSize(void);
/// �v���[���[�f�[�^�̎�M���I������
extern void CommInfoRecvEnd(int netID, int size, void* pData, void* pWork);
/// �v���[���[�����W�ߏI�����
extern BOOL CommInfoIsInfoCollected(void);
/// MyStatus�f�[�^����M����
extern void CommInfoRecvMyStatusData( int netID, int size, void* pData, void* pWork);
/// MyStatusArray�f�[�^����M����
extern void CommInfoRecvMyStatusArrayData( int netID, int size, void* pData, void* pWork);

/// �v���[���[�f�[�^����M����
extern void CommInfoRecvArrayPlayerData( int netID, int size, void* pData, void* pWork);
/// �v���[���[�f�[�^����M����
extern void CommInfoRecvPlayerData(int netID, int size, void* pData, void* pWork);

extern BOOL CommInfoSendArray_ServerSide(void);
extern BOOL CommInfoIsNewInfoData(void);


/// ���O�f�[�^�𓾂�
extern BOOL CommInfoGetName(int index, u16* name);
extern BOOL CommInfoIsBattleNewName(int netID);
/// ID�𕶎���œ���
extern BOOL CommInfoGetIDString(int index, u16* idStr);
/// ID�̃p�P�b�g�T�C�Y��Ԃ�
extern int CommInfoGetRecvPokeIDSize();
///   ��������
extern void CommInfoDeletePlayer(int netID);
///  �V���f�[�^���ǂ����𓾂�
extern BOOL CommInfoIsNewName(int netID);
///  �V�Ԓ��ԂƂ��ĔF�؂���
extern void CommInfoSetEntry(int netID);
/// �V�����o�^���ꂽ���Ƃ��O���ɓ`����
extern void CommInfoSetMessageEnd(int netID);
/// �V�������O�������Ă���ԍ���Ԃ�
extern int CommInfoGetNewNameID(void);
/// �����ɃG���g���[�����l�����A��
extern int CommInfoGetEntryNum(void);

extern void CommInfoFunc(void);
// �n���ɓ����Ă����󋵃��b�Z�[�W��Ԃ�
extern BOOL CommInfoGetActionMessage(u16* message);
// myStatus��Ԃ�
extern MYSTATUS* CommInfoGetMyStatus(int netID);
// DWC�t�����h�f�[�^��Ԃ�
extern DWCFriendData* CommInfoGetDWCFriendCode(int netID);
// �O���[�v����Ԃ�
extern STRCODE* CommInfoGetGroupName(int netID);
/// myNation��Ԃ�
extern int CommInfoGetMyNation(int netID);
/// myArea��Ԃ�
extern int CommInfoGetMyArea(int netID);
/// myPenalty��Ԃ�
extern int CommInfoGetMyPenalty(int netID);
// ���M�����[�V������Ԃ�
extern const REGULATION* CommInfoGetRegulation(int netID);
// �ڑ����Ă���l�̃��M�����[�V�������������ǂ�����������
extern BOOL CommInfoRegulationCheck(void);

// �ʐM�������񁕂������񌋉ʂ��ꎞ�L�^
extern void CommInfoWriteResult(SAVEDATA* pSaveData);
extern void CommInfoSetBattleResult(SAVEDATA* pSaveData, int bWin );
extern void CommInfoSetTradeResult(SAVEDATA* pSaveData, int num);


#define INVALID_NETID (0xff) ///< ������NetID

#endif  // __COMM_INFO_H__
