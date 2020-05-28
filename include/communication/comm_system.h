//=============================================================================
/**
 * @file	comm_system.h
 * @brief	�ʐM�V�X�e��
 * @author	Katsumi Ohno
 * @date    2005.07.08
 */
//=============================================================================

#ifndef _COMM_SYSTEM_H_
#define _COMM_SYSTEM_H_


#include "gflib/tcb.h" //TCB_PTR�̂���
#include "savedata/mystatus.h"

//==============================================================================
// extern�錾
//==============================================================================

// �K�v�ȃ��[�N�T�C�Y��Ԃ��܂� Alloc���ēn���Ă�������
extern u32 CommGetWorkSize(void);
//�e�@�̏����������܂��B�Ȃ��ɂ���q�@��҂��܂�
extern BOOL CommParentModeInit(BOOL bAlloc, BOOL bTGIDChange, int packetSizeMax, BOOL bEntry);
// �q�@�̏����������܂��B�����ɐe�@��T���ɍs���܂�
extern BOOL CommChildModeInit(BOOL bAlloc, BOOL bBconInit, int packetSizeMax);
// �p�[�e�B�[�Q�[����T���q�@�̏�����
extern BOOL CommChildPartyScanModeInit(BOOL bAlloc, BOOL bBconInit, int packetSizeMax);


/// ���܂�ǃo�b�t�@���N���A����
extern void CommSystemReset(void);
extern void CommSystemResetDS(void);
/// ���Z�b�g����
extern void CommSystemResetBattleChild(void);

extern void CommStopSendMoveData(BOOL bStop);

/// �ʐM�I������
extern void CommFinalize(void);
// ���������e�@�̐���Ԃ��܂�
extern int CommGetParentCount(void);
// �e�@�����݂Ȃ����Ă���䐔��Ԃ�
extern int CommGetParentConnectionNum(int index);
// �e�@�̃X�L�������X�g�ɍX�V���������ꍇTRUE
extern BOOL CommIsScanListChange(void);
// �q�@�@�f�[�^�V�F�A�����O��ԂŐڑ�-- CC_CONNECT_STARTING���A���Ă����琬���ł�
extern int CommChildNameAndIDConnect(STRBUF* pStrBuff, u32 pokeID);
// �q�@�@�f�[�^�V�F�A�����O��ԂŐڑ�-- TRUE���A���Ă����琬���ł�
extern BOOL CommChildIndexConnect(u16 index);
// �q�@ �e�@��BCON�̃^�C���A�E�g���Ď����܂�
extern void CommParentBconCheck(void);
// ���M��M�̏������s���܂��BVBlank�ɓ����Ă����Ăт܂��傤
extern BOOL CommUpdateData(void);
// ��M�R�[���o�b�N�q�@�p
extern void CommRecvCallback(u16 aid, u16 *data, u16 size);
/// ��M�R�[���o�b�N�e�@�p
extern void CommRecvParentCallback(u16 aid, u16 *data, u16 size);

// ������Ԃɂ���ĒʐM�ɕK�v�ȏ���������
extern void CommStateProcess(TCB_PTR tcb, void* work);
// �ʐM�����ǂ�����Ԃ�
extern BOOL CommIsConnect(u16 netID);
// ���M�o�b�t�@�̎c�ʂ𒲂ׂ܂�
extern int CommGetSendRestSize(void);
// �A�N�V�������s��ꂽ���Ƃ�ݒ肵�܂�
extern void CommActionCommandSet(void);
// �T�[�o���̑��M�o�b�t�@�̎c�ʂ𒲂ׂ܂�
extern int CommGetSendRestSize_ServerSide(void);
// ��M�f�[�^�ɖړI�̃R�}���h�����邩�ǂ�����������
extern BOOL CommGetRecvData_ServerSide(int netID,int chkCommand, int* retSize, u8* data);
// �ڑ��l���𒲂ׂ܂�
extern int CommGetConnectNum(void);
/// ���������Ă��邩�ǂ����𒲂ׂ܂�
extern BOOL CommIsInitialize(void);
/// �ʐM�؂�ւ����s���i�e�q���]�ɕK�v�ȏ����j
extern BOOL CommSwitchParentChild(void);

/// �p�b�h�R���g���[����Ԃ�
extern u16 CommGetPadCont(int netID);

/// �ړ����x������
extern void CommSetSpeed(u8 speed);
/// �ړ����x��Ԃ�
extern u8 CommGetSpeed(int netID);

// �e�@���E���t���O�����Z�b�g
extern void CommResetScanChangeFlag(void);
// �ړ��f�[�^�𑗐M���邱�Ƃ�������
extern void CommEnableSendMoveData(void);
// �ړ��f�[�^�𑗐M���邱�Ƃ��֎~����
extern void CommDisableSendMoveData(void);
// �ړ��f�[�^�𑗐M���邱�Ƃ������Ă��邩�ǂ����𓾂�
extern BOOL CommIsSendMoveData(void);


// �f�[�^�𑗂�
extern BOOL CommSendData(int command, const void* data, int size);
// ��e�ʃf�[�^�𑗂�
extern BOOL CommSendHugeData(int command, const void* data, int size);
// ��e�ʂŃT�C�Y�Œ�̃f�[�^�𑗂�
extern BOOL CommSendFixHugeSizeData(int command, const void* data);
/// �T�C�Y���Œ�̃f�[�^�𑗂�
extern BOOL CommSendFixSizeData(int command, const void* data);
/// �R�}���h�݂̂̃f�[�^�𑗂�
extern BOOL CommSendFixData(int command);
/// �T�[�o���̃f�[�^��S�q�@�ɑ���
extern BOOL CommSendData_ServerSide(int command, const void* data, int size);
// �T�[�o�[���֌Œ�T�C�Y�̃f�[�^�𑗂�
extern BOOL CommSendFixSizeData_ServerSide(int command, const void* data);
// �T�[�o�[�����e�ʃf�[�^�𑗂�
extern BOOL CommSendHugeData_ServerSide(int command, const void* data, int size);
// �T�[�o�[����T�C�Y�Œ�̑�e�ʃf�[�^�𑗂�
extern BOOL CommSendFixHugeSizeData_ServerSide(int command, const void* data);

// �L���[�ɑ���\��̃f�[�^�����߂�
extern BOOL CommSetSendQueue_ServerSide(int command, const void* data, int size);
// �L���[�ɑ���\��̃f�[�^�����߂�
extern BOOL CommSetSendQueue(int command, const void* data, int size);

/// �����_���ɃL�[�𔭐�������
extern void CommSetKeyRandMode(void);
extern void CommSetKeyReverseMode(void);
extern void CommResetKeyRandMode(void);

/// DS���[�hMP���[�h�̐؂�ւ�
extern void CommSetTransmissonTypeDS(void);
extern void CommSetTransmissonTypeMP(void);
extern int CommGetTransmissonType(void);
// �ʐM���[�h�ؑւ̃R�[���o�b�N
extern void CommRecvDSMPChange(int netID, int size, void* pData, void* pWork);
extern void CommRecvDSMPChangeReq(int netID, int size, void* pData, void* pWork);
extern void CommRecvDSMPChangeEnd(int netID, int size, void* pData, void* pWork);
// �����̋@��netID��Ԃ�
extern u16 CommGetCurrentID(void);

/// �f�[�^����M�o�b�t�@�ɂ��邩�ǂ����m�F����
extern BOOL CommRecvData(int netID,int chkCommand, int* retSize, u8* data);
/// WH���C�u�����Ł@��Ԃ�IDLE�ɂȂ��Ă��邩�m�F����
extern BOOL CommIsWHStateIdle(void);
/// �q�@���Ȃ��������ǂ������m�F
extern BOOL CommIsChildsConnecting(void);
/// �e�@������ؒf�����ꍇTRUE
extern BOOL CommParentDisconnect(void);
/// VRAMD�ɃC�N�j���[����������
extern void CommVRAMDInitialize(void);
/// VRAMD�̃C�N�j���[����������̂�҂�
extern BOOL CommIsVRAMDInitialize(void);
/// �G���[���N�����TRUE��Ԃ�
extern BOOL CommIsError(void);
/// �q�@�����Ȃ������G���[�ɂ������ꍇ�Z�b�g����
extern void CommSetNoChildError(BOOL bOn);
/// �T�[�r�X�ɑΉ��������M�o�C�g���𓾂�
extern u16 CommGetServiceMaxChildSendByte(u16 serviceNo);
/// �ő�ڑ��l���𓾂�
extern int CommGetMaxEntry(int service);
/// �ŏ��ڑ��l���𓾂�
extern int CommGetMinEntry(int service);

/// DS�p��M�f�[�^��̓C�e���[�^�[ ������
extern void CommRecvDSIteratorInitialize(int netID);
/// DS�p��M�f�[�^��̓C�e���[�^�[ �f�[�^�����邩�ǂ���
extern BOOL CommRecvDSIteratorHasNext(int netID);
/// DS�p��M�f�[�^��̓C�e���[�^�[ �f�[�^�����o�����ɐi��
extern BOOL CommRecvDSIteratorNext(int netID,int *pCommand, int* pSize, u8* pData);
/// �r�[�R���f�[�^�𓾂�
extern WMBssDesc* CommGetWMBssDesc(int index);
/// �r�[�R���f�[�^������
extern void CommResetWMBssDesc(int index);
/// MYSTATUS�𓾂�
extern MYSTATUS* CommGetMyStatus(void);
/// BCON���Ɋ܂܂��MYSTATUS��Ԃ�
extern MYSTATUS* CommGetBconMyStatus(int index);
/// �����ؒf���[�h�ɓ��������ǂ�����Ԃ�
extern BOOL CommIsAutoExit(void);
/// �����ؒf���[�hON
extern void CommSetAutoExit(void);

/// ��l�ŒʐM���郂�[�h�̐ݒ�
extern void CommSetAloneMode(BOOL bAlone);
/// ��l�ŒʐM���郂�[�h���ǂ����̎擾
extern BOOL CommGetAloneMode(void);

extern void CommSetBackupMacAddress(u8* pMac, int netID);
/// �T�[�r�X�ԍ����擾����
extern int CommGetServiceNo(void);

/// �����̎��������
extern void CommRandSeedInitialize(MATHRandContext32* pRand);

/// �R�}���h�����M���ꂽ���ǂ����m�F
extern BOOL CommIsSendCommand_ServerSize(int command);
extern BOOL CommIsSendCommand(int command);


/// �L���[������ۂ��ǂ���
BOOL CommIsEmptyQueue_ServerSize(void);
/// �L���[������ۂ��ǂ���
BOOL CommIsEmptyQueue(void);
// DS���[�h���ǂ���
BOOL CommIsTransmissonDSType(void);


// �퓬�ɓ���O�̓G�����̗����ʒu��ݒ�
extern void CommSetStandNo(int no, int netID);
// �퓬�ɓ���O�̓G�����̗����ʒu�𓾂�
extern int CommGetStandNo(int netID);
//
extern void CommSetWifiBothNet(BOOL bFlg);


#ifdef PM_DEBUG
extern void CommSwitchAutoMove_Debug(void);
#endif

extern void CommSetWifiConnect(BOOL bConnect);

extern BOOL CommIsVChat(void);

extern BOOL CommSysIsMoveKey(void);

extern void CommSetError(void);

extern void CommSystemShutdown(void);

// 
extern BOOL CommLocalIsUnionGroup(int serviceNo);

// �L���[������
extern void CommSystemResetQueue_Server(void);

extern void CommSystemRecvStop(BOOL bFlg);

#endif // _COMM_SYSTEM_H_

