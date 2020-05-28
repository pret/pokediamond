//=============================================================================
/**
 * @file	comm_state.h
 * @brief	�ʐM��Ԃ��Ǘ�����T�[�r�X  �ʐM�̏�ʂɂ���
 *          �X���b�h�̂ЂƂƂ��ē����A�����̒ʐM��Ԃ⑼�̋@���
 *          �J�n��I�����Ǘ�����
 *          communication�����݂̂��Ĉړ�
 * @author	k.ohno
 * @date    2006.01.12
 */
//=============================================================================

#ifndef __COMM_STATE_H__
#define __COMM_STATE_H__

#include "savedata/savedata.h"
#include "savedata/regulation.h"


//==============================================================================
// extern�錾
//==============================================================================
#ifdef PM_DEBUG
extern void DebugOhnoCommDebugUnderNo(int no);
extern void DebugOhnoCommDebugUnderParentOnly(int no);
extern void DebugOhnoCommDebugUnderChildOnly(int no);
#endif


extern BOOL CommStateIsInitialize(void);
// �n���ɓ���ꍇ�̏��� �X�e�[�g���n���p�ɕύX�����
extern void CommStateEnterUnderGround(SAVEDATA* pSaveData);
// �n�����ł�ꍇ�̏��� �X�e�[�g�������Ȃ��ɕύX�����
extern void CommStateExitUnderGround(void);
// �n���ɂ����Đڑ���STATE�Ȃ̂��ǂ����Ԃ�
extern BOOL CommIsUnderGroundConnectingState(void);
// �n���ɂ�����RESET�X�e�[�g�Ȃ̂��ǂ���
extern BOOL CommIsUnderResetState(void);
// �n���ɂ����Ĕ閧��n�ɓ���ׂɐؒf���s��
extern void CommStateUnderGroundOfflineSecretBase(void);
// �閧��n����o�Ă�����ڑ��������s��
extern void CommStateUnderGroundOnlineSecretBase(void);
// �n���̃r�[�R�����W���ĊJ
extern void CommStateUnderRestart(void);
// �n���̃r�[�R�����W���ĊJ
extern void CommStateUnderParentRestart(void);
// �n��������~��Ԃɂ���
extern void CommStaetUnderPause(BOOL bFlg);
// �������@��X�^�[�g
extern void CommStateUnderGroundDigFossilStart(void);
extern void CommStateUnderGroundDigFossilEnd(void);


// �o�g�����ɐe�ɂȂ�ꍇ�̏����J�n
#ifdef PM_DEBUG
extern void CommStateEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi, int soloDebugNo);
#else
extern void CommStateEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi);
#endif
// �o�g�����Ɏq�ɂȂ�ꍇ�̏����J�n
#ifdef PM_DEBUG
extern void CommStateEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi, int soloDebugNo);
#else
extern void CommStateEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi);
#endif
// �o�g�����ɐe�����߂��ۂ̎q�@�̏���
extern void CommStateConnectBattleChild(int connectIndex);
// �o�g�����Ɏq�@���ċN�����鎞�̏���
extern void CommStateRebootBattleChild(void);
// �I�������葱��
extern void CommStateExitBattle(void);
// �o�g���ڑ���STATE�Ȃ̂��ǂ����Ԃ�
extern BOOL CommIsBattleConnectingState(void);

/// ���j�I�����[���Ńr�[�R���̎��W
extern void CommStateUnionBconCollection(SAVEDATA* pSaveData);
/// ���j�I���q�@�ɂȂ�\��Ȃ̂ŒN���Ȃ���Ȃ�
extern void CommStateChildReserve(void);
/// ���j�I�����[���ŉ�b�J�n
extern void CommStateUnionTalkStart(void);
/// ���j�I�����[���Őڑ��J�n 
extern void CommStateUnionConnectStart(int index);
/// �ڑ��������ǂ���
extern int CommStateIsUnionConnectSuccess(void);
/// �e�@�Ƃ��Đڑ����Ă��邩�ǂ���
extern BOOL CommStateIsUnionParentConnectSuccess(void);
/// �r�[�R�����W�ĊJ
extern void CommStateUnionBconCollectionRestart(void);
/// �r�[�R�����W�ĊJ�̗���ɖ߂������ǂ���
extern BOOL CommStateUnionIsRestartSuccess(void);
// �I�������葱��
extern void CommStateExitUnion(void);
/// �ꎞ��~
extern void CommStateUnionPause(void);
/// ���j�I�����[�����̐ڑ����[�h�ɖ߂�
extern void CommStateUnionAppEnd(void);
/// �u���j�I�����[���A�v���P�[�V�����v�Ƃ����ڑ����[�h�ɕς���
extern void CommStateUnionAppStart(void);






extern void CommStateSetPokemon(u8* sel);
// �R�s�[
extern void CommStateGetPokemon(u8* sel);

// �s�v�c�ʐM�e�@�̐ڑ�
extern void CommStateEnterMysteryParent(SAVEDATA* pSaveData, int serviceNo);
// �s�v�c�ʐM�q�@�̐ڑ�
extern void CommStateEnterMysteryChild(SAVEDATA* pSaveData, int serviceNo);


#ifdef PM_DEBUG
// �^�C�g������ʐM�f�o�b�O���s�����̊֐�
extern void CommStateDBattleConnect(BOOL bParent, int gameMode ,SAVEDATA* pSaveData);
// WIFI�X�e�[�g����
extern void CommStateWifiCheckFunc(void);

// �f�o�b�O�X�^�[�g�����낦��֐�
extern void CommStateRecvDebugStart(int netID, int size, void* pData, void* pWork);
// �퓬�V�[�P���X�ɐi��ł������ǂ���
extern BOOL CommStateDBattleIsReady(void);


#endif

// ���G�����f���悤�ڑ��ɕύX
extern void CommStateUnionPictureBoardChange(void);
//���G����state�Ɉڍs�����ꍇTRUE
extern BOOL CommStateIsUnionPictureBoardState(void);
// ���G�����q�@�Ƃ��Čq��
extern void CommStateUnionPictureBoardChild(int index);

// ���R�[�h�R�[�i�[�̏�Ԃɐ؂�ւ���
extern void CommStateUnionRecordCornerChange(void);
// ���R�[�h�R�[�i�[�q�@�Ƃ��Čq��
extern void CommStateUnionRecordCornerChild(int index);


/// �ڑ��m�F����
extern void CommRecvNegotiation(int netID, int size, void* pData, void* pWork);
/// �ڑ��m�F���� �e�@����̕Ԏ�
extern void CommRecvNegotiationReturn(int netID, int size, void* pData, void* pWork);
/// �ڑ��m�F�R�}���h�̃T�C�Y
extern int CommRecvGetNegotiationSize(void);

/// �����Ă���l�̐��𐧌�
extern void CommStateSetLimitNum(int num);
/// �ۂ������ڑ��J�n
extern void CommStateEnterPockchChild(SAVEDATA* pSaveData);
/// �ۂ����������葱��
extern void CommStateExitPoketch(void);
/// �ۂ������ɂ����ď����WSTATE�Ȃ̂��ǂ����Ԃ�
extern BOOL CommIsPoketchSearchingState(void);

// �p�[�e�B�[�Q�[�����
#define PARTYGAME_MYSTERY_BCON (0x01)
#define PARTYGAME_RANGER_BCON  (0x02)
#define PARTYGAME_WII_BCON     (0x04)
#define PARTYGAME_DOWNLOAD_BCON (0x08)

// * �p�[�e�B�[�Q�[�������̒ʐM�����J�n�i�q�@��Ԃ̂݁j
extern void CommStateEnterPartyGameScanChild(SAVEDATA* pSaveData);
// �p�[�e�B�[�Q�[���T�[�`�̏I������
extern void CommStateExitPartyGameScan(void);
// �E�����r�[�R����BIT��Ԃ�
extern u8 CommStateGetPartyGameBit(void);

/// ���Z�b�g�p�̒ʐM�ؒf
extern BOOL CommStateExitReset(void);

extern void CommStateCheckFunc(void);

// WIFI�o�g���ڑ��p�֐�
#ifdef PM_DEBUG
void CommStateWifiEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, int soloDebugNo);
#else
void CommStateWifiEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo);
#endif
#ifdef PM_DEBUG
void CommStateWifiEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, int soloDebugNo);
#else
void CommStateWifiEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo);
#endif
//

extern void CommStateSetEntryChildEnable(BOOL bEntry);

//extern void CommStateSetDisconnectFlg(BOOL bFlg);
extern void CommStateSetErrorCheck(BOOL bFlg,BOOL bAuto);
//extern void CommStateSetErrorCheck(BOOL bFlg);
extern BOOL CommStateGetErrorCheck(void);

extern BOOL CommStateGetWifiDPWError(void);


extern void* CommStateWifiEnterLogin(SAVEDATA* pSaveData, int wifiFriendStatusSize);
extern void* CommStateGetMatchWork(void);
extern BOOL CommStateIsWifiLoginState(void);
extern BOOL CommStateIsWifiLoginMatchState(void);
extern void CommStateWifiMatchEnd(void);
extern void CommStateWifiTradeMatchEnd(void);
extern void CommStateWifiBattleMatchEnd(void);
extern BOOL CommStateIsWifiDisconnect(void);

extern int CommWifiWaitingCancel( void );

extern int CommStateGetServiceNo(void);
extern int CommStateGetRegulationNo(void);
#ifdef PM_DEBUG
extern int CommStateGetSoloDebugNo(void);
#endif

extern void CommStateWifiLogout(void);
extern int CommStateGetWifiErrorNo(void);
extern BOOL CommStateIsWifiError(void);

//�Q�[�����J�n����B// 2006.4.13 �g���ǉ�
extern int CommWifiBattleStart( int target );

//�}�b�`���O�������������ǂ����𔻒� // 2006.4.13 �g���ǉ�
extern int CommWifiIsMatched();

// �ʐM��WIFI�ڑ����Ă��邩�ǂ�����Ԃ�
extern BOOL CommStateIsWifiConnect(void);


extern void CommStateWifiDPWStart(SAVEDATA* pSaveData);
extern void CommStateWifiDPWEnd(void);

extern void CommStateWifiFusigiStart(SAVEDATA* pSaveData);
extern void CommStateWifiFusigiEnd(void);


#define COMM_ERROR_RESET_SAVEPOINT  (1)
#define COMM_ERROR_RESET_TITLE  (2)
#define COMM_ERROR_RESET_GTS  (3)
#define COMM_ERROR_RESET_OTHER (4)


// ���Z�b�g����G���[�����������ꍇ�ɌĂ�
extern void CommSetErrorReset(u8 type);
// ���Z�b�g����G���[�������������ǂ���
extern u8 CommIsResetError(void);

// fatal�G���[�֐�
extern void CommFatalErrorFunc(int no);
extern void CommFatalErrorFunc_NoNumber( void );


// �n���͂��߂̃C�x���g���s���ꍇ�ݒ�
extern void CommStateSetFirstEvent(void);

// WIFI����ؒf�v��
extern void CommRecvExit(int netID, int size, void* pData, void* pWork);

extern BOOL CommStateIsResetEnd(void);

extern void CommStateSetParentOnlyFlg(BOOL bFlg);


#define COMM_ERRORTYPE_ARESET (0)     // A�{�^���Ń��Z�b�g
#define COMM_ERRORTYPE_POWEROFF (1)   // �d����؂�Ȃ��Ƃ����Ȃ�
#define COMM_ERRORTYPE_TITLE (2)     // A�{�^���Ń��Z�b�g �^�C�g���߂�
#define COMM_ERRORTYPE_GTS (3)     // A�{�^���Ń��Z�b�g �Z�[�u�|�C���g�֖߂�

// �G���[�\���֐�
extern void ComErrorWarningResetCall( int heapID, int type, int code );
extern void DWClibWarningCall( int heapID, int error_msg_id );


// �G���[�ɂ���֐�   �ȉ��̔ԍ����g�p���Ă�������
//#define COMM_ERROR_RESET_SAVEPOINT  (1)
//#define COMM_ERROR_RESET_TITLE  (2)
//#define COMM_ERROR_RESET_GTS  (3)
//#define COMM_ERROR_RESET_OTHER (4)
extern BOOL CommStateSetError(int no);


#endif //__COMM_STATE_H__

