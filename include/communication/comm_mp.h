//=============================================================================
/**
 * @file	comm_mp.h
 * @brief	�ʐM�̐ڑ����Ǘ����Ă���N���X  comm_system.c ���番��
 * @author	Katsumi Ohno
 * @date    2006.01.25
 */
//=============================================================================

#ifndef _COMM_MP_H_
#define _COMM_MP_H_


#include "gflib/tcb.h" //TCB_PTR�̂���
#include "savedata/mystatus.h" //MYSTATUS�̂���

//==============================================================================
// extern�錾
//==============================================================================

/// ������
extern void CommMPInitialize(MYSTATUS* pMyStatus);
/// �ʐM���Ă��邩�ǂ���
extern BOOL CommMPIsConnect(void);

//�e�@�̏����������܂��B�Ȃ��ɂ���q�@��҂��܂�
extern BOOL CommMPParentInit(BOOL bAlloc, BOOL bTGIDChange, BOOL bEntry);
// �q�@�̏����������܂��B�����ɐe�@��T���ɍs���܂�
extern BOOL CommMPChildInit(BOOL bAlloc, BOOL bBconInit);
/// �ʐM�I������
extern BOOL CommMPFinalize(void);
/// �ʐM���Ă��Ȃ������̂܂ܐ��ޏ���
extern void CommMPStealth(BOOL bStalth);
// ���������e�@�̐���Ԃ��܂�
extern int CommMPGetParentCount(void);
// �e�@�̃X�L�������X�g�ɍX�V���������ꍇTRUE
extern BOOL CommMPIsScanListChange(void);
// �e�@���E���t���O�����Z�b�g
extern void CommMPResetScanChangeFlag(void);
// �e�@�����݂Ȃ����Ă���䐔��Ԃ�
extern int CommMPGetParentConnectionNum(int index);
// �����Ɍq���ł����l�������炻��index��Ԃ��܂�
extern int CommMPGetFastConnectIndex(void);
// ���̒i�K�Ōq���ł����l�������炻��index��Ԃ��܂�
extern int CommMPGetNextConnectIndex(void);
// �e�@�̖��O��MYSTATUS�ŕԂ��܂��B
extern void CommMPGetParentName(int index, MYSTATUS* pMyStatus);
// �e�@��ID��Ԃ��܂�
extern u32 CommMPGetPokeID(int index);
// �q�@�@MP��ԂŐڑ�-- CC_CONNECT_STARTING���A���Ă����琬���ł�
extern int CommMPChildNameAndIDConnect(STRBUF* pStrBuff, u32 pokeID);
// �q�@�@�f�[�^�V�F�A�����O��ԂŐڑ�-- TRUE���A���Ă����琬���ł�
extern BOOL CommMPChildIndexConnect(u16 index);
// �q�@ �e�@��BCON�̃^�C���A�E�g���Ď����܂�
extern void CommMPParentBconCheck(void);

/// �ʐM�؂�ւ����s���i�e�q���]�ɕK�v�ȏ����j
extern BOOL CommMPSwitchParentChild(void);
/// �ʐM�ؒf���[�h�ɓ��������ǂ���
extern BOOL CommMPIsConnectStalth(void);
/// �q�@���Ȃ��������ǂ������m�F
extern BOOL CommMPIsChildsConnecting(void);
/// �e�@������ؒf�����ꍇTRUE
extern BOOL CommMPParentDisconnect(void);
/// VRAMD�̃C�N�j���[�������̂Ă�
extern void CommVRAMDFinalize(void);
/// VRAMD�̃C�N�j���[������ݒ�J�n���Ă���
extern BOOL CommIsVRAMDStart(void);
/// �ʐM�G���[���ǂ���
extern BOOL CommMPIsError(void);
/// ������������ł��邩�ǂ���
extern BOOL CommMPIsInitialize(void);
/// �q�@�����Ȃ������G���[�ɂ������ꍇ�Z�b�g����
extern void CommMPSetNoChildError(BOOL bOn);
/// �N�������������ɃG���[�ɂ������ꍇ�Z�b�g����
extern void CommMPSetDisconnectOtherError(BOOL bOn);

/// �r�[�R���f�[�^�𓾂�  �폜�\��
extern WMBssDesc* CommMPGetWMBssDesc(int index);
/// �r�[�R���̃f�[�^���N���A����
extern void ChildBconDataInit(void);
/// GF�r�[�R���f�[�^�𓾂�
extern _GF_BSS_DATA_INFO* CommMPGetGFBss(int index);
/// �r�[�R���f�[�^������  �폜�\��
extern void CommMPResetWMBssDesc(int index);
/// �r�[�R���f�[�^������
extern void CommMPResetGFBss(int index);


///������BCON��PMS�f�[�^������������ ���̊֐���CommMPFlashMyBss���ĂԂ��ƂŔ��f�����
extern void CommMPSetMyPMS(PMS_DATA* pPMS);
///������BCON�̃��M�����[�V�����f�[�^������������ ���̊֐���CommMPFlashMyBss���ĂԂ��ƂŔ��f�����
extern void CommMPSetMyRegulation(void* pRegulation);
///�r�[�R���f�[�^�Ɍ��݂̏󋵂𔽉f������
extern void CommMPFlashMyBss(void);

/// MYSTATUS�𓾂�
extern MYSTATUS* CommMPGetMyStatus(void);
/// BCON���Ɋ܂܂��MYSTATUS��Ԃ�
extern MYSTATUS* CommMPGetBconMyStatus(int index);

/// �����ؒf���[�h�ɓ��������ǂ�����Ԃ�
extern BOOL CommMPIsAutoExit(void);
/// �����ؒf���[�hON
extern void CommMPSetAutoExit(void);
/// WM�ʐM���A�C�h����Ԃɂ��邩�ǂ���
extern BOOL CommMPIsStateIdle(void);

extern void CommMPSetBackupMacAddress(u8* pMac, int netID);
/// �T�[�r�X�ԍ����擾����
extern int CommMPGetServiceNo(void);
/// ���C�t�^�C�������������� �܂��͌��ɖ߂�
extern void CommMPSetLifeTime(BOOL bMinimum);

/// �C�ӂ̃T�[�r�X�̗��p�Ґ���Ԃ��܂�
extern int CommMPGetServiceNumber(int serviceNo);
// �v���Z�X����
extern void CommMpProcess(u16 bitmap);
// �r�[�R���𑗂������ǂ�������
extern BOOL CommMPIsParentBeaconSent(void);

extern BOOL CommMPIsChildStateScan(void);

//   �r�[�R���f�[�^�Ɏ��R�Ƀf�[�^���ڂ��܂�
extern void CommMPSetBeaconTempData(void* pData);
//   �r�[�R���f�[�^����f�[�^�������o���܂�
extern const void* CommMPGetBeaconTempData(int index);

// �֘A�Q�[���̃r�[�R�����W
extern BOOL CommMPPartyGameScanChildInit(void);

// �ڑ����悤�Ƃ��Ă���`�����l���A�ڑ������`�����l���𓾂�
extern int CommMPGetChannel(void);

extern void * CommMPGetMyGFBss(void);
extern int CommMPGetBConUncacheTime(int index);

extern int CommBmpListPosBconIndexGet(int index);

#endif // _COMM_MP_H_

