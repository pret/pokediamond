//=============================================================================
/**
 * @file	comm_state.c
 * @brief	�ʐM��Ԃ��Ǘ�����T�[�r�X  �ʐM�̏�ʂɂ���
 *          �X���b�h�̂ЂƂƂ��ē����A�����̒ʐM��Ԃ⑼�̋@���
 *          �J�n��I�����Ǘ�����
 *          �t�B�[���h�Ǘ������Ȃ�������������񂱂��Ɉ��z��...2006.01.12
 * @author	k.ohno
 * @date    2006.01.12
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "wh.h"
#include "comm_local.h"
#include "system/gamedata.h"
#include "system/pm_str.h"

#include "wifi/dwc_rap.h"   //WIFI
#include "system/snd_tool.h"  //sndTOOL

#include  "communication/wm_icon.h"

//==============================================================================
//	�^�錾
//==============================================================================
// �R�[���o�b�N�֐��̏���
typedef void (*PTRStateFunc)(void);

//==============================================================================
// ���[�N
//==============================================================================

typedef struct{
    void* pWifiFriendStatus;
    u8 select[6];
    MATHRandContext32 sRand; ///< �e�q�@�l�S�V�G�[�V�����p�����L�[
    PTRStateFunc state;
    SAVEDATA* pSaveData;
    MYSTATUS* pMyStatus;
    const REGULATION* pReg;
    int errorCode;
    u16 reConnectTime;  // �Đڑ����Ɏg�p����^�C�}�[
    u16 timer;
#ifdef PM_DEBUG		// Debug ROM
    u16 debugTimer;
#endif
    u8 limitNum;      // ��t�����������ꍇ��LIMIT��
    u8 negotiation;   // �ڑ��F��
    u8 connectIndex;   // �q�@���ڑ�����e�@��index�ԍ�
    u8 serviceNo;      // �ʐM�T�[�r�X�ԍ�
    u8 regulationNo;   // �R���e�X�g��ʂ����߂�ԍ�
#ifdef PM_DEBUG		// Debug ROM
    u8 soloDebugNo;
    u8 bDebugStart;
#endif
    u8 disconnectIndex;  //wifi�ؒf���� �e�@�q�@
    u8 wifiTargetNo;   // WIFI�ڑ����s���l�̔ԍ�
    u8 bFirstParent;   // �J��Ԃ��e�q�؂�ւ����s���ꍇ�̍ŏ��̐e���
    u8 bDisconnectError; // �ؒf�G���[���G���[�ɂ���Ƃ�TRUE
    u8 bErrorAuto;     // �����G���[�����N��TRUE
    u8 bWorldWifi;     // DPW�������Ă���ꍇ
    u8 ResetStateType;    // �G���[��Ԃɓ���\�t�g�E�G�A���Z�b�g��҂��
    u8 bUnionPause;    // ���j�I�����[���Őڑ���h�������ꍇ
    u8 partyGameBit;   // ���Ђ�GGID���E��
    u8 bParentOnly;   // �e�@��Ԃɂ����Ȃ�Ȃ�
    u8 bChildOnly;   // �q�@��Ԃɂ����Ȃ�Ȃ�
    u8 bNotConnect;   // �ʐM��ԂɑJ�ڂ��Ȃ�
    u8 bWifiDisconnect; //WIFI�ؒf�p �R�}���h�󂯎�����ꍇ��1
    u8 stateError;         //�G���[�����ɂ���ꍇ1�ȏ�
    u8 bPauseFlg;
} _COMM_STATE_WORK;

static _COMM_STATE_WORK* _pCommState = NULL;  ///<�@���[�N�\���̂̃|�C���^

//==============================================================================
// ��`
//==============================================================================

#define _HEAPSIZE_BATTLE           (0x7080)  // �o�g���@�̈�
#define _HEAPSIZE_UNDERGROUND      (0xE000)  // �n���̈�
#define _HEAPSIZE_UNION            (0x7080)  // ���j�I�����[���̈�
#define _HEAPSIZE_POKETCH          (0x7000)  // �ۂ������@�̈�
#define _HEAPSIZE_PARTY            (0x7000)  // �p�[�e�B�[�T�[�`
#define _HEAPSIZE_WIFI            (0x2A000+0x7000)  //DWCRAP ���g�p����̈�
#define _HEAPSIZE_DPW              (0x100)   // ���E�����@�^���[�p

#define _PACKETSIZE_BATTLE         (512)//(1376)  // �o�g���@�̈�
#define _PACKETSIZE_UNDERGROUND     (500)  // �n���̈�
#define _PACKETSIZE_UNION          (512)//(1280)  // ���j�I�����[���̈�
#define _PACKETSIZE_POKETCH          (32)  // �ۂ������̈�
#define _PACKETSIZE_PARTY         (32)  // �ۂ������̈�


#define _START_TIME (50)     // �J�n����
#define _CHILD_P_SEARCH_TIME (32) ///�q�@�Ƃ��Đe��T������
#define _PARENT_WAIT_TIME (40) ///�e�Ƃ��Ă̂�т�҂���
#define _FINALIZE_TIME (2)
#define _EXIT_SENDING_TIME (5)
#define _EXIT_SENDING_TIME2 (15)
#define _PARENT_END_TIME (2)
#define _SEND_NAME_TIME (10)
#define _PARENTSCAN_PA (3)  // �e�@�Ƃ��Č�������m����1/3

#define _RETRY_COUNT_UNION  (3)  // ���j�I�����[���Ŏq�@���ڑ��ɗv�����

#define _TCB_COMMCHECK_PRT   (10)    ///< �t�B�[���h������ʐM�̊Ď����[�`����PRI


#define _NEGOTIATION_OK (1)      // �ڑ��m�F����
#define _NEGOTIATION_CHECK (0)   // �ڑ��m�F��
#define _NEGOTIATION_NG (2)     // �ڑ����s



//==============================================================================
// static�錾
//==============================================================================

// �X�e�[�g�̏�����

static void _changeStateDebug(PTRStateFunc state, int time, int line);  // �X�e�[�g��ύX����
static void _changeState(PTRStateFunc state, int time);  // �X�e�[�g��ύX����

#ifdef PM_DEBUG
#if 1
#define   _CHANGE_STATE(state, time)  _changeStateDebug(state, time, __LINE__)
#else
#define   _CHANGE_STATE(state, time)  _changeState(state, time)
#endif
#else  //PM_DEBUG
#define   _CHANGE_STATE(state, time)  _changeState(state, time)
#endif //PM_DEBUG


// �n���֘A�X�e�[�g
static void _underStart(void);           // �q�@�̏����� + �V�X�e���̏�����
static void _underChildPInit(void);      // �q�@�̏�����
static void _underChildFInit(void);
static void _underChildPSearching(void); // �q�@���e�@��T���Ă���
static void _underChildForceConnect(void); // �q�@���e�@�ɋ����ɐڑ���
static void _underChildConnecting(void);   // �q�@���e�@�ɐڑ���
static void _underChildConnect(void);    // �q�@�Ƃ��Đڑ���
static void _underChildReset(void);
static void _underChildFinalize(void);   // �q�@�ɂȂ�Ȃ������̂ŏI��������
static void _underParentFinalize(void);  // �e�@�ɂȂ�Ȃ������̂ŏI��������
static void _underParentInit(void);      // �e�@�Ƃ��ď�����
static void _underParentWait(void);      // �e�@�Ƃ��đҋ@���
static void _underParentConnectInit(void); // �ڑ������̂ŏ�������
static void _underParentConnect(void);   // �e�@�Ƃ��Đڑ���
static void _stateUnderGroundConnectEnd(void);  // �n���ؒf
static void _underSBReset(void);


// �o�g���֘A�X�e�[�g
static void _battleParentInit(void);     // �퓬�p�e�@�Ƃ��ď�����
static void _battleParentWaiting(void);  // �퓬�p�e�@�Ƃ��đҋ@��
static void _battleParentMoveRoomEnter(void);  // �퓬�O�̕����ɓ����đҋ@��
static void _battleParentMoveRoom(void);  // �퓬�O�̕����ɓ����đҋ@��
static void _battleParentSendName(void);  // �����̖��O���݂�Ȃɑ��M
static void _battleParentReTry(void);   // �퓬�p�e�@�𒆒f

static void _battleChildInit(void);     // �퓬�p�q�@�Ƃ��ď�����
static void _battleChildBconScanning(void);  // �퓬�p�q�@�Ƃ��Đe�@�I��
static void _battleChildConnecting(void);  // �ڑ������炢��
static void _battleChildSendName(void);  // �����̖��O���݂�Ȃɑ��M
static void _battleChildWaiting(void);  // �_�C���N�g�p�q�@�ҋ@��
static void _battleChildMoveRoomEnter(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleChildMoveRoom(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleChildReTry(void);   // �q�@�𒆒f
static void _battleChildReInit(void);   // �q�@���ċN��
static void _battleChildReset(void);
static void _battleChildReConnect(void);
static void _underChildOnline(void);


// UNION���[���֘A�X�e�[�g
static void _unionStart(void);
static void _unionChildSearching(void);
static void _unionChildFinalize(void);
static void _unionParentInit(void);
static void _unionParentWait(void);
static void _unionChildRestart(void);
static void _unionChildNegotiation(void);

static void _unionForceConnectStart(void);
static void _unionForceConnectStart2(void);
static void _unionForceConnect(void);
static void _unionChildConnecting(void);
static void _unionChildConnectSuccess(void);
static void _unionChildConnectFailed(void);
static void _unionChildReset(void);
static void _unionParentConnect(void);
static void _unionParentPause(void);

static void _mysteryParentInit(void);
static void _mysteryChildInit(void);

// ���̑���ʓI�ȃX�e�[�g
static void _stateNone(void);            // �������Ȃ�
static void _stateConnectError(void);    // �ڑ��G���[���
static void _stateEnd(void);             // �I������
static void _stateConnectChildEndWait(void);   // �q�@�̏I����҂��ďI���
static void _stateConnectChildEnd(void);
static void _stateConnectEnd(void);      // �ؒf�����J�n
static void _stateConnectAutoEnd(void);  // �����ؒf�����J�n


// WIFI�p
static void _wifiBattleLogin(void);
static void _stateWifiLogout(void);


// �l�S�V�G�[�V�����p�m�FKEY
static u8 _negotiationMsg[]={"FREAK"};
static u8 _negotiationMsgReturnOK[]={" GAME"};
static u8 _negotiationMsgReturnNG[]={" FULL"};


#ifdef PM_DEBUG
static u8 _debugConnectNo = 0;
static u8 _debugParentOnly = 0;
static u8 _debugChildOnly = 0;

void DebugOhnoCommDebugUnderNo(int no)
{
    _debugConnectNo = no;
}

void DebugOhnoCommDebugUnderParentOnly(int no)
{
    _debugParentOnly = no;
}

void DebugOhnoCommDebugUnderChildOnly(int no)
{
    _debugChildOnly = no;
}

#endif //PM_DEBUG

//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏���������
 * @param   MYSTATUS* pMyStatus
 * @retval  none
 */
//==============================================================================

static void _commStateInitialize(SAVEDATA* pSaveData,int serviceNo)
{
    void* pWork;

    if(_pCommState!=NULL){   // ���łɓ��쒆�̏ꍇ�K�v�Ȃ�
        return;
    }
    CommVRAMDInitialize();
    // ������
    _pCommState = (_COMM_STATE_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_STATE_WORK));
    MI_CpuFill8(_pCommState, 0, sizeof(_COMM_STATE_WORK));
    _pCommState->timer = _START_TIME;
    _pCommState->bFirstParent = TRUE;  // �e�̏��߂Ă̋N���̏ꍇTRUE
    _pCommState->pSaveData = pSaveData;
    _pCommState->pMyStatus = SaveData_GetMyStatus(pSaveData);
    _pCommState->limitNum = COMM_MODE_UNION_NUM_MIN + 1;   // ��l�͍Œ�ł��ڑ��\
    _pCommState->negotiation = _NEGOTIATION_CHECK;
    _pCommState->bUnionPause = FALSE;
    _pCommState->serviceNo = serviceNo;
    //_pCommState->bWifi = FALSE;
    CommRandSeedInitialize(&_pCommState->sRand);
    CommCommandInitialize(NULL, 0, NULL);

    if((serviceNo != COMM_MODE_UNION) && (serviceNo != COMM_MODE_PARTY) &&
       (serviceNo != COMM_MODE_MYSTERY)){
        WirelessIconEasy();
    }
}


//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏I������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateFinalize(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
//    TCB_Delete(_pCommState->pTcb);
    CommCommandFinalize();
    if(_pCommState->pWifiFriendStatus){
        sys_FreeMemoryEz(_pCommState->pWifiFriendStatus);
    }
    if(_pCommState->serviceNo >= COMM_MODE_BATTLE_SINGLE_WIFI){
        sys_DeleteHeap(HEAPID_WIFIMENU);
    }
    WirelessIconEasyEnd();
    CommVRAMDFinalize();
    sys_FreeMemoryEz(_pCommState);
    sys_DeleteHeap(HEAPID_COMMUNICATION);
    _pCommState = NULL;
}

//==============================================================================
/**
 * ������������ł��邩�ǂ���
 * @param   none
 * @retval  ����ł���ꍇTRUE
 */
//==============================================================================

BOOL CommStateIsInitialize(void)
{
    if(_pCommState){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �n���ɂ͂��������̒ʐM����
 * @param   MYSTATUS* pMyStatus
 * @retval  none
 */
//==============================================================================

void CommStateEnterUnderGround(SAVEDATA* pSaveData)
{
    if(_pCommState!=NULL){ // �Ȃ����Ă���ꍇ���͏��O����
        return;
    }
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_UNDERGROUND );
    _commStateInitialize(pSaveData,COMM_MODE_UNDERGROUND);
//    _pCommState->serviceNo = COMM_MODE_UNDERGROUND;
    _pCommState->regulationNo = 0;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = _debugConnectNo + SOLO_DEBUG_NO;
    _pCommState->bParentOnly = _debugParentOnly;
    _pCommState->bChildOnly = _debugChildOnly;
#endif
    // �n���X�e�[�g�̑J�ڂ̂��ߏ�����
    _CHANGE_STATE(_underStart, _START_TIME);
}

//==============================================================================
/**
 * �n�����o��ꍇ�̒ʐM����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateExitUnderGround(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    // �ؒf�X�e�[�g�Ɉڍs����  �����ɐ؂�Ȃ�
    CommSystemShutdown();
    _CHANGE_STATE(_stateUnderGroundConnectEnd, 0);
}

//==============================================================================
/**
 * �r�[�R�����W���ĊJ����
 * @param   MYSTATUS* pMyStatus
 * @retval  none
 */
//==============================================================================

void CommStateUnderRestart(void)
{
    CommSystemReset();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
    // ���邮��܂킷
    _pCommState->reConnectTime = CommGetCurrentID();
    _CHANGE_STATE(_underChildReset, 0);  // �G���[�I���̏ꍇRESET����
}

//==============================================================================
/**
 * �r�[�R�����W���~����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStaetUnderPause(BOOL bFlg)
{
    _pCommState->bPauseFlg = bFlg;
}


//==============================================================================
/**
 * �r�[�R�����W���ĊJ���� �e�@���̃��X�^�[��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underQueueReset(void)
{

    if(!CommMPSwitchParentChild()){
        return;
    }
    CommSystemReset();         // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
    _CHANGE_STATE(_underChildFinalize, 0);

    /*
    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    if(CommIsEmptyQueue_ServerSize()){
        CommSystemResetQueue_Server();
    }
    OHNO_PRINT("���M�L���[����\n");
       */
//    _CHANGE_STATE(_underChildFinalize, _FINALIZE_TIME);
}

void CommStateUnderParentRestart(void)
{
   // _CHANGE_STATE(_underQueueReset, 0);
    _CHANGE_STATE(_underChildFinalize, 0);

}


//==============================================================================
/**
 * �n���ɂ����ă��Z�b�g���Ȃ̂��ǂ����Ԃ�
 * @param   none
 * @retval  RESET���Ȃ�TRUE
 */
//==============================================================================

BOOL CommIsUnderResetState(void)
{
    int i;
    u32 stateAddr = (u32)_pCommState->state;

    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return FALSE;
    }
    if(stateAddr == (u32)_underQueueReset){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �n���ɂ����Đڑ���STATE�Ȃ̂��ǂ����Ԃ�
 * @param   none
 * @retval  �ڑ����Ȃ�TRUE
 */
//==============================================================================

BOOL CommIsUnderGroundConnectingState(void)
{
    int i;
    u32 funcTbl[]={
        (u32)_underChildConnect,
        (u32)_underParentConnect,
        0,
    };
    u32 stateAddr = (u32)_pCommState->state;

    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return FALSE;
    }
    for(i = 0; funcTbl[i] != 0; i++ ){
        if(stateAddr == funcTbl[i]){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �ʐM��؂�閧��n�ɂ͂���
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnderGroundOfflineSecretBase(void)
{
    // �ؒf�X�e�[�g�Ɉڍs����  �����ɐ؂�Ȃ�
    _CHANGE_STATE(_underSBReset, 0);  // �G���[�I���̏ꍇRESET����
}

//==============================================================================
/**
 * �͂��߂̃C�x���g
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateSetFirstEvent(void)
{
    _pCommState->bNotConnect = TRUE;
}





//==============================================================================
/**
 * �ʐM���q���閧��n����߂�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnderGroundOnlineSecretBase(void)
{
    CommVRAMDInitialize();
    _CHANGE_STATE(_underChildOnline, 0);  // �G���[�I���̏ꍇRESET����
}

//==============================================================================
/**
 * �o�g�����̐e�Ƃ��Ă̒ʐM�����J�n
 * @param   pMyStatus  mystatus
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @param   regulationNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

#ifdef PM_DEBUG
void CommStateEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi, int soloDebugNo)
#else
void CommStateEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi)
#endif
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_BATTLE );
    _commStateInitialize(pSaveData,serviceNo);
//    _pCommState->serviceNo = serviceNo;
    _pCommState->regulationNo = regulationNo;
    _pCommState->pReg = pReg;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = soloDebugNo;
#endif
    _CHANGE_STATE(_battleParentInit, 0);
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

#ifdef PM_DEBUG
void CommStateEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg,BOOL bWifi, int soloDebugNo)
#else
void CommStateEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg,BOOL bWifi)
#endif
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_BATTLE );
    _commStateInitialize(pSaveData,serviceNo);
//    _pCommState->serviceNo = serviceNo;
    _pCommState->regulationNo = regulationNo;
    _pCommState->pReg = pReg;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = soloDebugNo;
#endif
    _CHANGE_STATE(_battleChildInit, 0);
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   connectIndex �ڑ�����e�@��Index
 * @retval  none
 */
//==============================================================================

void CommStateConnectBattleChild(int connectIndex)
{
    _pCommState->connectIndex = connectIndex;
    _CHANGE_STATE(_battleChildConnecting, 0);
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�ċN������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateRebootBattleChild(void)
{
    CommSystemResetBattleChild();
    _CHANGE_STATE(_battleChildReTry, 0);
}

//==============================================================================
/**
 * �o�g�����̒ʐM�����I���葱��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateExitBattle(void)
{
    if(_pCommState==NULL){
        return;      // ���łɏI�����Ă���ꍇ�͏��O
    }
    _CHANGE_STATE(_stateConnectEnd, _EXIT_SENDING_TIME);
    //_CHANGE_STATE(_stateConnectAutoEnd, _EXIT_SENDING_TIME);
}

//==============================================================================
/**
 * �q�@��t�ł��邩�ǂ���
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateSetEntryChildEnable(BOOL bEntry)
{
    WHSetEntry(bEntry);
}


//==============================================================================
/**
 * �o�g���ڑ���STATE�Ȃ̂��ǂ����Ԃ�
 * @param   none
 * @retval  �ڑ���TRUE
 */
//==============================================================================

BOOL CommIsBattleConnectingState(void)
{
    int i;
    u32 funcTbl[]={
        (u32)_battleParentWaiting,
        (u32)_battleChildWaiting,
        0,
    };
    u32 stateAddr = (u32)_pCommState->state;

    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return FALSE;
    }
    for(i = 0; funcTbl[i] != 0; i++ ){
        if(stateAddr == funcTbl[i]){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �r�[�R�����W���J�n����
 * @param   MYSTATUS* pMyStatus
 * @retval  none
 */
//==============================================================================

void CommStateUnionBconCollection(SAVEDATA* pSaveData)
{
    if(_pCommState!=NULL){ // �Ȃ����Ă���ꍇ���͏��O����
        return;
    }
    // �ʐM�q�[�v�쐬
    if(sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_UNION )==0){
		// �ʐM�q�[�v���쐬�ł��Ȃ������B
		// ���s�s�\(�d���؂�G���[�ցj
		CommFatalErrorFunc_NoNumber();

	}
    _commStateInitialize(pSaveData,COMM_MODE_UNION);
    _pCommState->serviceNo = COMM_MODE_UNION;
    _pCommState->regulationNo = 0;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = SOLO_DEBUG_NO;
#endif
    // �X�e�[�g�̑J�ڂ̂��ߏ�����
    _CHANGE_STATE(_unionStart, 0);
}


//==============================================================================
/**
 * ��b���J�n�����̂Ŏq�@�ڑ�
 * @param   �ڑ�����e�@index
 * @retval  none
 */
//==============================================================================

void CommStateUnionConnectStart(int index)
{
    _pCommState->connectIndex = index;
    _pCommState->reConnectTime = _RETRY_COUNT_UNION;
    WHParentConnectPause(TRUE);  // �e�@�ɂ͂Ȃ�Ȃ�
    WirelessIconEasy();
    _CHANGE_STATE(_unionForceConnectStart, 0);
}

//==============================================================================
/**
 * �q�@�ڑ��ɐ����������ǂ���
 * @param   none
 * @retval  �ڑ������O�@�������P�@���s���|�P
 */
//==============================================================================

int CommStateIsUnionConnectSuccess(void)
{
    u32 stateAddr;

    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return -1;
    }
    stateAddr = (u32)_pCommState->state;
    if(stateAddr == (u32)_unionChildConnectSuccess){
        return 1;
    }
    if(stateAddr == (u32)_unionChildConnectFailed){
        return -1;
    }
    return 0;
}

//==============================================================================
/**
 * �e�@�ڑ��ɐ����������ǂ���
 * @param   none
 * @retval  �ڑ����Ȃ�TRUE
 */
//==============================================================================

BOOL CommStateIsUnionParentConnectSuccess(void)
{
    u32 stateAddr;

    if(_pCommState==NULL){  // ���łɏI�����Ă��� �������͏��������܂�
        return FALSE;
    }
    stateAddr = (u32)_pCommState->state;
    if(stateAddr == (u32)_unionParentConnect){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �r�[�R�����W���ĊJ����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnionBconCollectionRestart(void)
{
	OS_TPrintf( "���X�^�[�g���܂����I\n" );

    WHParentConnectPause(FALSE);

	if( !(_pCommState->bDisconnectError == TRUE && _pCommState->bErrorAuto == TRUE) ||
		_pCommState->serviceNo == COMM_MODE_UNION ){
	   CommStateSetErrorCheck(FALSE,FALSE);
	}

    WirelessIconEasyEnd();
    _pCommState->serviceNo = COMM_MODE_UNION;
    OHNO_PRINT(">> UNION�r�[�R�����W�ĊJ\n");
    _pCommState->bUnionPause = FALSE;
    WH_SetMaxEntry(_pCommState->limitNum);

    if(CommGetCurrentID() == COMM_PARENT_ID){
        WHParentConnectPauseSystem(TRUE);
        _CHANGE_STATE(_stateConnectChildEndWait, _EXIT_SENDING_TIME2);
    }
    else{
        _CHANGE_STATE(_stateConnectChildEnd, _EXIT_SENDING_TIME);
    }
}

//==============================================================================
/**
 * �r�[�R�����W���ĊJ���m�F����
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommStateUnionIsRestartSuccess(void)
{
    u32 stateAddr;

    if(_pCommState==NULL){
        return TRUE;  // 
    }
    stateAddr = (u32)_pCommState->state;
    if(stateAddr == (u32)_unionChildFinalize){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 * UNIONROOM���o��ꍇ�̒ʐM����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateExitUnion(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    OHNO_SP_PRINT(">> UNION��������ؒf\n");
    // �ؒf�X�e�[�g�Ɉڍs����  �����ɐ؂�Ȃ�
    
    _CHANGE_STATE(_stateConnectEnd, _EXIT_SENDING_TIME);
}

//==============================================================================
/**
 * �q�@�Ƃ��ĂȂ���\��Ȃ̂ŁA�e�@�ɂ͂Ȃ�Ȃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateChildReserve(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    _pCommState->bUnionPause = TRUE;
    WHParentConnectPause(TRUE);
}

//==============================================================================
/**
 * UNIONROOM�ꎞ��~  �ĊJ��ReStart
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnionPause(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    OHNO_PRINT(">> UNIONROOM�ꎞ��~\n");
    _pCommState->bUnionPause = TRUE;
    WHParentConnectPause(TRUE);
    _CHANGE_STATE(_unionParentPause, 0);
}

//==============================================================================
/**
 * UNIONROOM�A�v���P�[�V�����X�^�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnionAppStart(void)
{
    _pCommState->serviceNo = COMM_MODE_UNION_APP;
}

//==============================================================================
/**
 * UNIONROOM�A�v���P�[�V�����G���h
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnionAppEnd(void)
{
    _pCommState->serviceNo = COMM_MODE_UNION;
}

//==============================================================================
/**
 * �s�v�c�ʐM�Ƃ��Ă̒ʐM�����J�n
 * @param   pMyStatus  mystatus
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @param   regulationNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

void CommStateEnterMysteryParent(SAVEDATA* pSaveData, int serviceNo)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_BATTLE );
    _commStateInitialize(pSaveData,serviceNo);
//    _pCommState->serviceNo = serviceNo;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = 0;
#endif
    _CHANGE_STATE(_mysteryParentInit, 0);
}

//==============================================================================
/**
 * �s�v�c�ʐM�̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

void CommStateEnterMysteryChild(SAVEDATA* pSaveData, int serviceNo)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_BATTLE );
    _commStateInitialize(pSaveData,serviceNo);
//    _pCommState->serviceNo = serviceNo;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = 0;
#endif
    _CHANGE_STATE(_mysteryChildInit, 0);
}


//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏���
 * @param
 * @retval  none
 */
//==============================================================================

void CommStateCheckFunc(void)
{

    if(_pCommState){
        if(_pCommState->state != NULL){
            PTRStateFunc state = _pCommState->state;
            state();
        }
    }
    if(CommStateIsWifiConnect()){
        WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - DWC_GetLinkLevel());
    }
    else if(CommMPIsInitialize()){
        WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - WM_GetLinkLevel());
    }
}

//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̕ύX
 * @param   state  �ς���X�e�[�g�̊֐�
 * @param   time   �X�e�[�g�ێ�����
 * @retval  none
 */
//==============================================================================

static void _changeState(PTRStateFunc state, int time)
{
    _pCommState->state = state;
    _pCommState->timer = time;
}

//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̕ύX
 * @param   state  �ς���X�e�[�g�̊֐�
 * @param   time   �X�e�[�g�ێ�����
 * @retval  none
 */
//==============================================================================
#ifdef PM_DEBUG
static void _changeStateDebug(PTRStateFunc state, int time, int line)
{
    OHNO_PRINT("comm_state: %d\n",line);
    _changeState(state, time);
}
#endif

//==============================================================================
/**
 * �n���X�^�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStart(void)
{
    void* pWork;

    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    if(!CommIsVRAMDInitialize()){
        return;  //
    }
    CommMPInitialize(_pCommState->pMyStatus);
    CommInfoInitialize(_pCommState->pSaveData, NULL);
    CommSetAloneMode(TRUE);
    CommEnableSendMoveData(); //commsystem�ɂ����Ă���L�[�f�[�^�̑��M������

    if(_pCommState->bParentOnly){
        if(CommParentModeInit(TRUE, _pCommState->bFirstParent, _PACKETSIZE_UNDERGROUND, TRUE))  {
            u32 rand = MATH_Rand32(&_pCommState->sRand, _PARENT_WAIT_TIME/2);
            _pCommState->bFirstParent = FALSE;
            _CHANGE_STATE(_underParentWait, _PARENT_WAIT_TIME/2+rand);
        }
    }
    else{
        // �܂��q�@�ɂȂ��Ă݂āA�e�@��T��  ���R�F�e�@�������炷�΂₭�Ȃ��邩��
        if(CommChildModeInit(TRUE, TRUE, _PACKETSIZE_UNDERGROUND)){
            if(_pCommState->bNotConnect){
                _CHANGE_STATE(_stateNone,0);
            }
            else{
                _CHANGE_STATE(_underChildPSearching, _CHILD_P_SEARCH_TIME*2);
            }
        }
    }
}

//==============================================================================
/**
 * ���Z�b�g��̍ăX�^�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildFInit(void)
{
    BOOL bSuccess;

    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    CommSetAloneMode(TRUE);  // ��ڑ����
    CommEnableSendMoveData(); //commsystem�ɂ����Ă���L�[�f�[�^�̑��M������

    if(_pCommState->bParentOnly){
        _CHANGE_STATE(_underParentInit, 0);
    }
    else{
        bSuccess = CommChildModeInit(FALSE, TRUE, _PACKETSIZE_UNDERGROUND);
        if(bSuccess){
            u32 rand = MATH_Rand32(&_pCommState->sRand, _CHILD_P_SEARCH_TIME*2);
            if(_pCommState->reConnectTime > 0){
                //OHNO_PRINT("�Đڑ����ԍl�� %d \n", _pCommState->reConnectTime);
                // �Đڑ����ԍl��
                rand = 2 * _CHILD_P_SEARCH_TIME * _pCommState->reConnectTime;
                _pCommState->reConnectTime = 0;
            }
            _CHANGE_STATE(_underChildPSearching, rand);
        }
    }
}

//==============================================================================
/**
 * �q�@�ăX�^�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildPInit(void)
{
    BOOL bSuccess;
    
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    bSuccess = CommChildModeInit(FALSE, FALSE, _PACKETSIZE_UNDERGROUND);
    if(bSuccess){
        u32 rand = MATH_Rand32(&_pCommState->sRand, _CHILD_P_SEARCH_TIME);
        _CHANGE_STATE(_underChildPSearching, _CHILD_P_SEARCH_TIME/2 + rand);
    }
}

//==============================================================================
/**
 * �q�@�ƂȂ��Đe�@��T����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildPSearching(void)
{
    int realParent;
    
    CommMPParentBconCheck();  // bcon�̌���

    if(_pCommState->bPauseFlg || _pCommState->bChildOnly){
        return;
    }
    
    realParent = CommMPGetFastConnectIndex();  //�Ȃ��������Ƃ�����l��������
    if(realParent != -1){
        _pCommState->connectIndex = realParent;  // �L��
        _CHANGE_STATE(_underChildForceConnect, _CHILD_P_SEARCH_TIME);
        OHNO_PRINT("�{�e�ɐڑ�\n");
        return;
    }
    if(_pCommState->timer != 0){
        _pCommState->timer--;
        return;
    }
    realParent = CommMPGetNextConnectIndex();  //�Ȃ��������Ƃ�����l��������
    if(realParent != -1){
        _pCommState->connectIndex = realParent;  // �L��
        _CHANGE_STATE(_underChildForceConnect, _CHILD_P_SEARCH_TIME);
        return;
    }


    // �e�����Ȃ��ꍇ ���������e�ɂȂ�
    _CHANGE_STATE(_underChildFinalize, 0);
}


//==============================================================================
/**
 * �ڕW�ƂȂ�e�@�ɑ΂��Đڑ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildForceConnect(void)
{
    //OHNO_PRINT("_underChildForceConnect...\n");
    CommMPParentBconCheck();  // bcon�̌���
    if(CommMPGetParentConnectionNum(_pCommState->connectIndex)!=0){ // �e���������Ă���ꍇ
        //OHNO_PRINT("�����ڑ���\n");
        if(CommChildIndexConnect(_pCommState->connectIndex)){  // �ڑ�����܂ŌĂё�����
            _CHANGE_STATE(_underChildConnecting, 100);
            return;
        }
    }
    if(CommIsError()){
        //OHNO_PRINT("�G���[�̏ꍇ�߂�\n");
        _CHANGE_STATE(_underChildFinalize, 0);
    }
    else if(_pCommState->timer!=0){
        _pCommState->timer--;
    }
    else{
        OHNO_PRINT("�ڑ����Ԑ؂�̏ꍇ�܂����ǂ�\n");
        _CHANGE_STATE(_underChildFinalize, 0);
    }
}



//==============================================================================
/**
 * �q�@�ƂȂ��Đڑ���
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _underChildConnecting(void)
{
    if(CommIsConnect(CommGetCurrentID())){   // �������g���ڑ����Ă��邱�Ƃ��m�F�ł�����
        CommSystemReset();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
        CommSetAloneMode(FALSE);
        CommEnableSendMoveData();
        //OHNO_PRINT("�q�@�ڑ�\n");
        _CHANGE_STATE(_underChildConnect, 0);
        return;
    }
    
    if(CommIsError()){
        OHNO_PRINT("�G���[�̏ꍇchange�ɂ��Ă݂�\n");
        _CHANGE_STATE(_underChildFinalize, 0);
        return;
    }
    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    // ���Ԑ؂�
    _CHANGE_STATE(_underChildFinalize, 0);
}

//==============================================================================
/**
 * �q�@�I�� ���e�ɕς��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildFinalize(void)
{
    if(!CommMPSwitchParentChild()){
        return;
    }
    _CHANGE_STATE(_underParentInit, 0);
//    OHNO_PRINT("�e�@�ɂȂ�ҋ@ \n");
}

//==============================================================================
/**
 * �e�@�I���@�m���Őe�@�ɂȂ邩�q�@�ɂȂ邩���߂�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentFinalize(void)
{
    if(!CommMPSwitchParentChild()){
        return;
    }
    _CHANGE_STATE(_underChildPInit, 0);
//    OHNO_PRINT("�q�@�ƂȂ茟�� %d\n", rand);
}

//==============================================================================
/**
 * �e�@�J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentInit(void)
{
    MYSTATUS* pMyStatus;
    
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    // �e�@�ɂȂ��Ă݂�
    CommSetAloneMode(TRUE); // 
    if(CommParentModeInit(FALSE, _pCommState->bFirstParent, _PACKETSIZE_UNDERGROUND, TRUE))  {
        u32 rand = MATH_Rand32(&_pCommState->sRand, _PARENT_WAIT_TIME/2);
        _pCommState->bFirstParent = FALSE;
        _CHANGE_STATE(_underParentWait, _PARENT_WAIT_TIME/2+rand);
    }
}

//==============================================================================
/**
 * �e�@�ɂȂ�A�q�@���ڑ����Ă���̂�҂�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentWait(void)
{
   if(CommIsChildsConnecting()){   // �����ȊO���Ȃ�������e�@�Œ�
       OHNO_PRINT("�����ȊO���Ȃ�������e�@�Œ�\n");
        _pCommState->bFirstParent = TRUE;  // �e�@�Ƃ��Čq�������̂Ńt���O��߂��Ă���
        _CHANGE_STATE(_underParentConnectInit, 0);
        return;
    }
    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    if(_pCommState->bParentOnly){
        return;
    }
    if( CommMPSwitchParentChild() ){
        _CHANGE_STATE(_underParentFinalize, _FINALIZE_TIME);
    }
}

//==============================================================================
/**
 * �e�@�Ƃ��Đڑ����������̂ŏ��������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnectInit(void)
{
    CommSetAloneMode(FALSE);
    CommMPSetNoChildError(TRUE);  // �q�@�����Ȃ��Ȃ�����Č������邽�߂�ERR�����ɂ���
    CommEnableSendMoveData();

    _CHANGE_STATE(_underParentConnect, 0);
}

//==============================================================================
/**
 * �e�@�Ƃ��Đڑ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect(void)
{
//    OHNO_PRINT("�e�@�Ƃ��Đڑ���\n");
    //    if(CommIsError()){
        // �e�q�����ɖ߂�
//        CommMPSwitchParentChild();
//        _CHANGE_STATE(_underChildFinalize, _FINALIZE_TIME);
//    }
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnect(void)
{
    /*
    // �e�@�����Ȃ��Ȃ�����I�����������ĕʐe��T���ɂ���
    if(CommMPParentDisconnect() || CommIsError()){
        if(CommMPParentDisconnect()){
            OHNO_PRINT("�e�@�ؒf ??  \n");
        }
        else{
            OHNO_PRINT("�G���[�ؒf   \n");
        }
//        _stateUnderGroundConnectEnd();
        CommSystemReset();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
        // ���邮��܂킷
        _pCommState->reConnectTime = CommGetCurrentID();
        _CHANGE_STATE(_underChildReset, 0);  // �G���[�I���̏ꍇRESET����
    }
       */
}


static void _underSBBoot(void)
{
    OHNO_PRINT("�I���̊m�F \n");
    if(_pCommState->serviceNo < COMM_MODE_BATTLE_SINGLE_WIFI){
        if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
            return;
        }
        CommSetAloneMode(TRUE);  // ��ڑ����
        CommEnableSendMoveData(); //commsystem�ɂ����Ă���L�[�f�[�^�̑��M������
        CommMPStealth(TRUE);  // �閧���ɐؒf
        OHNO_PRINT("�ʐM�؂ꂽ�͂� \n");
    }
    else{
    }
    _CHANGE_STATE(_stateNone, 0);
}

//==============================================================================
/**
 * �閧��nOFFLINE�p�Ƀ��Z�b�g�������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underSBReset(void)
{
    if(!CommMPSwitchParentChild()){
        return;
    }
    OHNO_PRINT("�ċN��    -- %d \n",CommGetCurrentID());
    CommSystemReset();         // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
    _CHANGE_STATE(_underSBBoot, 0);
}


//==============================================================================
/**
 * �C�N�j���[������������ʐM�N��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildOnline(void)
{
    if(!CommIsVRAMDInitialize()){
        return;  //
    }
    CommMPStealth(FALSE);

    CommSystemReset();         // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���

    OHNO_PRINT("�ċN��    -- %d \n",CommGetCurrentID());
    _CHANGE_STATE(_underChildFInit, 0);
}

//==============================================================================
/**
 * ���Z�b�g�������s���A�q�@�Ƃ��čċN��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildReset(void)
{
    if(!CommMPSwitchParentChild()){
        return;
    }
    OHNO_PRINT("�ċN��    -- %d \n",CommGetCurrentID());
    _CHANGE_STATE(_underChildFInit, 0);
}

//==============================================================================
/**
 * �e�@�Ƃ��ď��������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentInit(void)
{
    MYSTATUS* pMyStatus;
    
    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommMPInitialize(_pCommState->pMyStatus);
    CommInfoInitialize(_pCommState->pSaveData, _pCommState->pReg);

    if(CommParentModeInit(TRUE, TRUE, _PACKETSIZE_BATTLE,TRUE)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_battleParentSendName, 0);
    }
}


//==============================================================================
/**
 * �q�@�ҋ@���  �e�@��I��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentSendName(void)
{
    if(!CommIsConnect(CommGetCurrentID())){
        return;
    }
    _CHANGE_STATE(_battleParentWaiting, 0);
}

//==============================================================================
/**
 * �e�@�Ƃ��đҋ@��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentWaiting(void)
{
    if(!CommIsInitialize()){
        _CHANGE_STATE(_stateEnd,0);
    }
}

//==============================================================================
/**
 * �q�@�̏�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildInit(void)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommMPInitialize(_pCommState->pMyStatus);
    CommInfoInitialize(_pCommState->pSaveData, _pCommState->pReg);
    
    if(CommChildModeInit(TRUE, TRUE, _PACKETSIZE_BATTLE)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_battleChildBconScanning, 0);
    }
}

//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�r�[�R�����W��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildBconScanning(void)
{
    CommMPParentBconCheck();
}

//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�ɋ����炢��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildConnecting(void)
{
    CommMPParentBconCheck();
    if(CommChildIndexConnect(_pCommState->connectIndex)){  // �ڑ�����
        _CHANGE_STATE(_battleChildSendName, _SEND_NAME_TIME);
    }

}

//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�ɏ��𑗐M
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildSendName(void)
{

    if(CommIsError()){
        //OHNO_PRINT("�G���[�̏ꍇ�߂�\n");
        _CHANGE_STATE(_battleChildReset, 0);
    }

    
    if(CommIsConnect(CommGetCurrentID()) && ( COMM_PARENT_ID != CommGetCurrentID())){
        _CHANGE_STATE(_battleChildWaiting, 0);
    }
}

//==============================================================================
/**
 * �q�@���Z�b�g   
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildReset(void)
{
    CommMPSwitchParentChild();
    _CHANGE_STATE(_battleChildReConnect, _FINALIZE_TIME);
}

//==============================================================================
/**
 * �q�@����������I�����Đڑ�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildReConnect(void)
{
    MYSTATUS* pMyStatus;

    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    if(!CommMPIsStateIdle()){  /// �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    if(CommChildModeInit(FALSE, TRUE, _PACKETSIZE_BATTLE)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_battleChildConnecting, _SEND_NAME_TIME);
    }
}


//==============================================================================
/**
 * �q�@�ҋ@���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildWaiting(void)
{
    if(!CommIsInitialize()){
        _CHANGE_STATE(_stateEnd,0);
    }
}

//==============================================================================
/**
 * �q�@����������I��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildReTry(void)
{
    CommMPSwitchParentChild();
    _CHANGE_STATE(_battleChildReInit, _FINALIZE_TIME);
}

//==============================================================================
/**
 * �q�@����������I�����ċN����������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildReInit(void)
{
    MYSTATUS* pMyStatus;

    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    if(!CommMPIsStateIdle()){  /// �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    if(CommChildModeInit(FALSE, TRUE, _PACKETSIZE_BATTLE)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_battleChildBconScanning, _SEND_NAME_TIME);
    }
}

//==============================================================================
/**
 * �������Ȃ��X�e�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateNone(void)
{
    // �Ȃɂ����Ă��Ȃ�
}

//==============================================================================
/**
 * @brief �G���[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectError(void)
{
}

//==============================================================================
/**
 * @brief  �I��������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateEnd(void)
{
    if(CommIsInitialize()){
        return;
    }
    _stateFinalize();
}

//==============================================================================
/**
 * @brief  �n�����E�����J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateUnderGroundConnectEnd(void)
{
    _CHANGE_STATE(_stateConnectEnd, _EXIT_SENDING_TIME);
}

//==============================================================================
/**
 * @brief  �����I�������J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectAutoEnd(void)
{
    if(CommSendFixData(CS_AUTO_EXIT)){
        _CHANGE_STATE(_stateEnd, 0);
    }
}

//==============================================================================
/**
 * @brief   �ڑ��؂�ւ��̑O�ɐe�@�Ȃ�Α���̐ؒf���m�F����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectChildEndWait(void)
{
    if(CommGetConnectNum() <= 1){  // ���������̐ڑ��ɂȂ�����
        WHParentConnectPauseSystem(FALSE);
        CommSystemResetDS();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
        _CHANGE_STATE(_unionChildFinalize, 0);
    }
    if(_pCommState->timer != 0){
        _pCommState->timer--;
        return;
    }
    // ����
    WHParentConnectPauseSystem(FALSE);
    CommSystemResetDS();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
    _CHANGE_STATE(_unionChildFinalize, 0);
}

//==============================================================================
/**
 * @brief   �ڑ��؂�ւ��̑O�Ɏq�@�Ȃ�ΐ؂ꂽ���ɏ�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectChildEnd(void)
{
    if(!CommMPSwitchParentChild()){
        return;
    }
    CommSystemReset();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
    _CHANGE_STATE(_unionChildFinalize, 0);
}

//==============================================================================
/**
 * @brief  �I�������J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectEnd(void)
{
    if(_pCommState->timer != 0){
        _pCommState->timer--;
    }
    if(!CommMPSwitchParentChild()){
        return;
    }
    if(_pCommState->timer != 0){
        return;
    }
    OHNO_PRINT("�ؒf����");
    CommFinalize();
    _CHANGE_STATE(_stateEnd, 0);
}



//==============================================================================
/**
 * UNION�X�^�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionStart(void)
{
    void* pWork;

    if(!CommIsVRAMDInitialize()){
        return;  //
    }
    CommMPInitialize(_pCommState->pMyStatus);
    WH_SetMaxEntry(_pCommState->limitNum);
    CommInfoInitialize(_pCommState->pSaveData, NULL);
    
    // �܂��q�@�ɂȂ��Ă݂āA�e�@��T��   ���邮��񂵂�bcon�����߂�
    if(CommChildModeInit(TRUE, TRUE, _PACKETSIZE_UNION)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_unionChildSearching, _CHILD_P_SEARCH_TIME*2);
    }
}

//==============================================================================
/**
 * �q�@�ƂȂ��Đe�@��T����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionChildSearching(void)
{
    int realParent;

    CommMPParentBconCheck();  // bcon�̌���
    if(_pCommState->timer != 0){
        _pCommState->timer--;
        return;
    }

    if(!CommMPSwitchParentChild()){
        return;
    }
    OHNO_PRINT("�q�@�����\n");
    _CHANGE_STATE(_unionParentInit, 0);
}

//==============================================================================
/**
 * �q�@�I�� ���e�ɕς��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionChildFinalize(void)
{
    if(!CommMPSwitchParentChild()){
        return;
    }
    _CHANGE_STATE(_unionParentInit, 0);
}

//==============================================================================
/**
 * �e�@�J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionParentInit(void)
{
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    // �e�@�ɂȂ��Ă݂�
    if(CommParentModeInit(FALSE, _pCommState->bFirstParent, _PACKETSIZE_UNION,TRUE))  {
        u32 rand = MATH_Rand32(&_pCommState->sRand, _PARENT_WAIT_TIME*2);
        CommSetTransmissonTypeDS();
        _pCommState->bFirstParent = FALSE;
        OHNO_PRINT("�e�@\n");
        _CHANGE_STATE(_unionParentWait, 10000);
    }
}

//==============================================================================
/**
 * �e�@�ɂȂ�bcon���o
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionParentWait(void)
{
    if(CommMPIsParentBeaconSent()){  // �r�[�R���𑗂�I�������q�@�ɐ؂�ւ��
    }
    else{
        if(CommIsChildsConnecting()){   // �����ȊO���Ȃ�������e�@�Œ�
            OHNO_PRINT("�e�@ -- �Ȃ���\n");
            _pCommState->bFirstParent = TRUE;  // �e�@�Ƃ��Čq�������̂Ńt���O��߂��Ă���
            WirelessIconEasy();
            _CHANGE_STATE(_unionParentConnect, 0);
            return;
        }
        if(_pCommState->timer!=0){
            _pCommState->timer--;
            return;
        }
    }
    OHNO_PRINT("�e�@�����\n");
    if( CommMPSwitchParentChild() ){
        _CHANGE_STATE(_unionChildRestart, 0);
    }
}

//==============================================================================
/**
 * �q�@�ăX�^�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionChildRestart(void)
{
    u32 rand;
    
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    // ���x�̓r�[�R�����c�����܂�
    if(CommChildModeInit(FALSE, FALSE, _PACKETSIZE_UNION)){
        CommSetTransmissonTypeDS();
        rand = MATH_Rand32(&_pCommState->sRand, _CHILD_P_SEARCH_TIME);
        OHNO_PRINT("�q�@�J�n %d \n",rand);
        _CHANGE_STATE(_unionChildSearching, rand);
    }
}

//==============================================================================
/**
 * �b�������J�n�ŁA�q�@�ҋ@��ԂɂȂ�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionForceConnectStart(void)
{
    if(!CommMPSwitchParentChild()){  // ���̏�Ԃ��I��
        return;
    }
    _CHANGE_STATE(_unionForceConnectStart2, 0);
}


static void _unionForceConnectStart2(void)
{
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    // �q�@�ɂȂ�
    if(CommChildModeInit(FALSE, FALSE, _PACKETSIZE_UNION)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_unionForceConnect, 100);
    }
}

//==============================================================================
/**
 * �q�@�ƂȂ��ċ����ڑ�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionForceConnect(void)
{
    OHNO_PRINT("_unionForceConnect...\n");
    if(CommMPGetParentConnectionNum(_pCommState->connectIndex)!=0){ // �e���������Ă���ꍇ
        OHNO_PRINT("�����ڑ���\n");
        if(CommChildIndexConnect(_pCommState->connectIndex)){  // �ڑ�����܂ŌĂё�����
            _CHANGE_STATE(_unionChildConnecting, 100);
            return;
        }
    }
    if(CommIsError()){
        OHNO_PRINT("�G���[�̏ꍇ�ēx�d�؂�Ȃ���\n");
        _CHANGE_STATE(_unionChildReset, 0);
    }
    else if(_pCommState->timer!=0){
        _pCommState->timer--;
    }
    else{
        OHNO_PRINT("�ڑ����Ԑ؂�̏ꍇ�܂����ǂ�\n");
        _CHANGE_STATE(_unionChildReset, 0);
    }
}

//==============================================================================
/**
 * �q�@�ƂȂ��Đڑ���
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _unionChildConnecting(void)
{
    if(CommIsError()){
        OHNO_PRINT("------�G���[�̏ꍇReset\n");
        _CHANGE_STATE(_unionChildReset, 0);
        return;
    }
    if(CommIsConnect(CommGetCurrentID())){   // �������g���ڑ����Ă��邱�Ƃ��m�F�ł�����
        OHNO_PRINT("�q�@�ڑ�  �F�ؑ��M\n");
        _pCommState->negotiation = _NEGOTIATION_CHECK;
        CommSendFixSizeData(CS_COMM_NEGOTIATION, _negotiationMsg);
        _CHANGE_STATE(_unionChildNegotiation, 120);
        return;
    }
    
    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    // ���Ԑ؂�
    _CHANGE_STATE(_unionChildReset, 0);
}

//==============================================================================
/**
 * �q�@�ƂȂ��Đڑ���  �e�@�F�ؑ҂�
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _unionChildNegotiation(void)
{
    if(CommIsError()){
        OHNO_PRINT("------�G���[�̏ꍇReset\n");
        _CHANGE_STATE(_unionChildReset, 0);
        return;
    }
    if(_pCommState->negotiation == _NEGOTIATION_NG){
        OHNO_PRINT("�ڑ����s-----------------------\n");
        _CHANGE_STATE(_unionChildConnectFailed, 0);
        return;
    }
    if(_pCommState->negotiation == _NEGOTIATION_OK){
        OHNO_PRINT("�q�@�ڑ�  �F�؂����\n");
        CommInfoSendPokeData();
        _CHANGE_STATE(_unionChildConnectSuccess, 0);
        return;
    }
    
    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }
    OHNO_PRINT(" ���Ԑ؂� \n");
    _CHANGE_STATE(_unionChildReset, 0);
}



static void _unionChildConnectSuccess(void)
{
    if(CommIsError()){
        _CHANGE_STATE(_unionChildReset, 0);
        return;
    }
}

static void _unionChildConnectFailed(void)
{
}

static void _unionChildReset(void)
{
    _pCommState->negotiation = _NEGOTIATION_CHECK;
    if(!CommMPSwitchParentChild()){
        return;
    }

    if(_pCommState->reConnectTime != 0){
        _pCommState->reConnectTime--;
        _CHANGE_STATE(_unionForceConnectStart2, 0);
    }
    else{  // �Ȃ���Ȃ������̂Ŏ��s�X�e�[�g��
        _CHANGE_STATE(_unionChildConnectFailed, 0);
    }
}

//==============================================================================
/**
 * �e�Ƃ��Đڑ���
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _unionParentConnect(void)
{
    OHNO_PRINT("commisConnect %d\n",CommIsConnect(1));

    if(!CommIsChildsConnecting()){   // �����ȊO���Ȃ����ĂȂ��΂����������
        if(!CommStateGetErrorCheck()){
            OHNO_PRINT("�e�@�����ς�\n");
            if( CommMPSwitchParentChild() ){
                _CHANGE_STATE(_unionChildRestart, 0);
            }
        }
    }
    else{
        if(CommGetCurrentID() == COMM_PARENT_ID){
            CommInfoSendArray_ServerSide();  // �q�@����₢���킹����������info�𑗐M
        }
    }
    if(CommIsError()){
        if(!CommStateGetErrorCheck()){
            OHNO_PRINT("------�G���[�̏ꍇReset\n");
            _CHANGE_STATE(_unionChildReset, 0);
            return;
        }
    }
}

//==============================================================================
/**
 * �e�@�̂܂܈ꎞ��~
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _unionParentPause(void)
{
    u32 rand;
    
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    // �Ȃ���Ȃ��e�@�ɂȂ�
    if(CommParentModeInit(FALSE, _pCommState->bFirstParent, _PACKETSIZE_UNION, FALSE))  {
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_stateNone,0);
    }
}




static void _pictureBoardChangeParent(void);
static void _pictureBoardInitParent(void);
static void _pictureBoardParentWait(void);

static void _pictureBoardChangeChild(void);
static void _pictureBoardInitChild(void);
static void _pictureBoardForceConnect(void);
static void _pictureBoardChildConnecting(void);

//==============================================================================
/**
 * ���G�������[�h�Ɍq���Ȃ���
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnionPictureBoardChange(void)
{
    _pCommState->serviceNo = COMM_MODE_PICTURE;
    if(CommGetCurrentID() == COMM_PARENT_ID){
        u8 bDSMode = FALSE;
        CommSendFixSizeData(CS_DSMP_CHANGE, &bDSMode);  //�ړ����[�h�ɕύX����
//        _pCommState->limitNum = COMM_MODE_PICTURE_NUM_MAX+1;
    }
    else{
        u8 bDSMode = FALSE;
        CommSendFixSizeData(CS_DSMP_CHANGE, &bDSMode);  //�ړ����[�h�ɕύX����
    }
}

//==============================================================================
/**
 * ���G�������[�h�q�@�Ƃ��Čq��
 * @param   �ڑ�����e�@index
 * @retval  none
 */
//==============================================================================

void CommStateUnionPictureBoardChild(int index)
{
    _pCommState->connectIndex = index;
    _pCommState->reConnectTime = _RETRY_COUNT_UNION;
    _CHANGE_STATE(_pictureBoardChangeChild, 0);
    OHNO_PRINT("���G�����{�[�h�q�@�ڑ�\n");
}

//==============================================================================
/**
 * ���R�[�h�R�[�i�[�̏�Ԃɐ؂�ւ���
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateUnionRecordCornerChange(void)
{
    _pCommState->serviceNo = COMM_MODE_RECORD;
}

//==============================================================================
/**
 * ���R�[�h�R�[�i�[�q�@�Ƃ��Čq��
 * @param   �ڑ�����e�@index
 * @retval  none
 */
//==============================================================================

void CommStateUnionRecordCornerChild(int index)
{
    _pCommState->connectIndex = index;
    _pCommState->serviceNo = COMM_MODE_RECORD;
    _pCommState->reConnectTime = _RETRY_COUNT_UNION;
    WirelessIconEasy();
    _CHANGE_STATE(_unionForceConnectStart, 0);
}

//==============================================================================
/**
 * ���G����state�Ɉڍs�������ǂ����̊m�F
 * @param   none
 * @retval  ���G����state�Ɉڍs�����ꍇTRUE
 */
//==============================================================================

BOOL CommStateIsUnionPictureBoardState(void)
{
    u32 stateAddr = (u32)_pCommState->state;

    if(CommIsTransmissonDSType()){
        return FALSE;
    }
    if(stateAddr == (u32)_unionParentConnect){
        return TRUE;
    }
    if(stateAddr == (u32)_unionChildConnectSuccess){
        return TRUE;
    }
    return FALSE;
}


static void _pictureBoardChangeParent(void)
{
    if( CommMPSwitchParentChild() ){
        _CHANGE_STATE(_pictureBoardInitParent, 0);
    }
}

static void _pictureBoardInitParent(void)
{
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    OHNO_PRINT("���G�����e�ɕύX\n");
    _pCommState->serviceNo = COMM_MODE_PICTURE;
    if(CommParentModeInit(FALSE, FALSE, _PACKETSIZE_UNION,TRUE)) {
        CommSetTransmissonTypeMP();
        _CHANGE_STATE(_pictureBoardParentWait, 0);
    }
}


static void _pictureBoardParentWait(void)
{
    if(CommIsChildsConnecting()){   // �����ȊO���Ȃ�������e�@�Œ�
        _pCommState->bFirstParent = TRUE;  // �e�@�Ƃ��Čq�������̂Ńt���O��߂��Ă���
        CommInfoSendPokeData();
        _CHANGE_STATE(_unionParentConnect, 0);
    }
}


static void _pictureBoardChangeChild(void)
{
    if( CommMPSwitchParentChild() ){
        _CHANGE_STATE(_pictureBoardInitChild, 0);
    }
}

static void _pictureBoardInitChild(void)
{
    if(!CommMPIsStateIdle()){  // �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    _pCommState->serviceNo = COMM_MODE_PICTURE;
    if(CommChildModeInit(FALSE, FALSE, _PACKETSIZE_UNION)){
        CommSetTransmissonTypeMP();
        _CHANGE_STATE(_pictureBoardForceConnect, 100);
    }
}


//==============================================================================
/**
 * �q�@�ƂȂ��ċ����ڑ�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _pictureBoardForceConnect(void)
{
    OHNO_PRINT("_pictureBoardForceConnect...\n");
    if(CommMPGetParentConnectionNum(_pCommState->connectIndex)!=0){ // �e���������Ă���ꍇ
        OHNO_PRINT("BOARD�����ڑ���\n");
        if(CommChildIndexConnect(_pCommState->connectIndex)){  // �ڑ�����܂ŌĂё�����
            _CHANGE_STATE(_pictureBoardChildConnecting, 100);
            return;
        }
    }
    if(CommIsError() || (_pCommState->timer == 0)){
        _pCommState->reConnectTime--;
        if(_pCommState->reConnectTime==0){
            OHNO_PRINT("�ڑ����s %d \n",_pCommState->reConnectTime);
            _CHANGE_STATE(_unionChildConnectFailed, 0);
        }
        else{
            _CHANGE_STATE(_pictureBoardChangeChild, 0);
        }
    }
    else if(_pCommState->timer!=0){
        _pCommState->timer--;
    }
}

//==============================================================================
/**
 * �q�@�ƂȂ��Đڑ���
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _pictureBoardChildConnecting(void)
{
    if(_pCommState->timer > 90){
        _pCommState->timer--;
        return;
    }
    
    if(CommIsError()){
        _pCommState->reConnectTime--;
        if(_pCommState->reConnectTime==0){
            OHNO_PRINT("�ڑ����s %d \n",_pCommState->reConnectTime);
            _CHANGE_STATE(_unionChildConnectFailed, 0);
        }
        else{
            OHNO_PRINT("------�G���[�̏ꍇReset\n");
            _CHANGE_STATE(_pictureBoardChangeChild, 0);
        }
        return;
    }
    
    if(CommIsConnect(CommGetCurrentID())){   // �������g���ڑ����Ă��邱�Ƃ��m�F�ł�����
        OHNO_PRINT("�q�@�ڑ�\n");
        _CHANGE_STATE(_unionChildConnectSuccess, 0);
        return;
    }
    if(_pCommState->timer!=0){
        _pCommState->timer--;
        return;
    }

    _pCommState->reConnectTime--;
    OHNO_PRINT("�ڑ����s %d \n",_pCommState->reConnectTime);
    if(_pCommState->reConnectTime==0){
        _CHANGE_STATE(_unionChildConnectFailed, 0);
    }
    else{
        // ���Ԑ؂�
        _CHANGE_STATE(_pictureBoardChangeChild, 0);
    }
}

//==============================================================================
/**
 * �l�S�V�G�[�V�����p�R�[���o�b�N CS_COMM_NEGOTIATION
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommRecvNegotiation(int netID, int size, void* pData, void* pWork)
{
    int i;
    u8* pMsg = pData;
    BOOL bMatch = TRUE;

    OHNO_PRINT("------CommRecvNegotiation\n");

    if(CommGetCurrentID() != COMM_PARENT_ID){  // �e�@�̂ݔ��f�\
        return;
    }
    bMatch = TRUE;
    for(i = 0; i < sizeof(_negotiationMsg); i++){
        if(pMsg[i] != _negotiationMsg[i]){
            bMatch = FALSE;
            break;
        }
    }
    if(bMatch  && (!_pCommState->bUnionPause)){   // �q�@����ڑ��m�F������
//        if(CommGetConnectNum() <= _pCommState->limitNum){  // �w��ڑ��l����艺��邱��
            OHNO_PRINT("------�����𑗐M \n");
            _negotiationMsgReturnOK[0] = netID;
            CommSendFixSizeData_ServerSide(CS_COMM_NEGOTIATION_RETURN, _negotiationMsgReturnOK);
            return;
//        }
    }
    OHNO_PRINT("------���s�𑗐M %d %d\n",bMatch,_pCommState->bUnionPause);
    _negotiationMsgReturnNG[0] = netID;
    CommSendFixSizeData_ServerSide(CS_COMM_NEGOTIATION_RETURN, _negotiationMsgReturnNG);
}

//==============================================================================
/**
 * �l�S�V�G�[�V�����p�R�[���o�b�N CS_COMM_NEGOTIATION_RETURN
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommRecvNegotiationReturn(int netID, int size, void* pData, void* pWork)
{
    u8 id;
    int i;
    u8* pMsg = pData;
    BOOL bMatch = TRUE;

    for(i = 1; i < sizeof(_negotiationMsgReturnOK); i++){
        if(pMsg[i] != _negotiationMsgReturnOK[i]){
            bMatch = FALSE;
            break;
        }
    }
    if(bMatch){   // �e�@����ڑ��F�؂�����
        id = pMsg[0];
        if(id == CommGetCurrentID()){
            _pCommState->negotiation = _NEGOTIATION_OK;
        }
        return;
    }
    bMatch = TRUE;
    for(i = 1; i < sizeof(_negotiationMsgReturnNG); i++){
        if(pMsg[i] != _negotiationMsgReturnNG[i]){
            bMatch = FALSE;
            break;
        }
    }
    if(bMatch){   // �e�@����ڑ��ے肪����
        id = pMsg[0];
        OHNO_PRINT("�ڑ����ۃR�}���h������%d %d\n",id , CommGetCurrentID());
        if(id == (u8)CommGetCurrentID()){
            _pCommState->negotiation = _NEGOTIATION_NG;
        }
        return;
    }
}

//==============================================================================
/**
 * �l�S�V�G�[�V�����p�R�[���o�b�N
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

int CommRecvGetNegotiationSize(void)
{
    return sizeof(_negotiationMsg);
}


//==============================================================================
/**
 * �����Ă���l���𐧌�����
 * @param   �l��
 * @retval  none
 */
//==============================================================================

void CommStateSetLimitNum(int num)
{
    if(_pCommState){
        _pCommState->limitNum = num;
        WH_SetMaxEntry(num);
    }
}


//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�r�[�R�����W��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _poketchBconScanning(void)
{
    CommMPParentBconCheck();
}

//==============================================================================
/**
 * �|�P�b�`�q�@�̏�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _poketchChildInit(void)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommMPInitialize(_pCommState->pMyStatus);
    CommInfoInitialize(_pCommState->pSaveData, NULL);
    
    if(CommChildModeInit(TRUE, TRUE, _PACKETSIZE_POKETCH)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_poketchBconScanning, 0);
    }
}

//==============================================================================
/**
 * �ۂ������Ƃ��Ă̒ʐM�����J�n�i�q�@��Ԃ̂݁j
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

void CommStateEnterPockchChild(SAVEDATA* pSaveData)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_POKETCH );
    _commStateInitialize(pSaveData,COMM_MODE_POKETCH);
//    _pCommState->serviceNo = COMM_MODE_POKETCH;
    _pCommState->regulationNo = 0;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = 0;
#endif
    _CHANGE_STATE(_poketchChildInit, 0);
}

//==============================================================================
/**
 * �ۂ������Ƃ��Ă̏I������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateExitPoketch(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    OHNO_PRINT("��������ؒf\n");
    // �ؒf�X�e�[�g�Ɉڍs����  �����ɐ؂�Ȃ�
    _CHANGE_STATE(_stateConnectEnd, _EXIT_SENDING_TIME);
}

//==============================================================================
/**
 * �ʐM�T�[�`���[�ɂ����ď����WSTATE�Ȃ̂��ǂ����Ԃ�
 * @param   none
 * @retval  ���W���Ȃ�TRUE
 */
//==============================================================================

BOOL CommIsPoketchSearchingState(void)
{
    int i;
    u32 funcTbl[]={
        (u32)_poketchBconScanning,
        0,
    };
    u32 stateAddr = (u32)_pCommState->state;

    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return FALSE;
    }
    for(i = 0; funcTbl[i] != 0; i++ ){
        if(stateAddr == funcTbl[i]){
            return TRUE;
        }
    }
    return FALSE;
}


//==============================================================================
/**
 * PARTY�T�[�`callback
 * @param   ggid
 * @retval  none
 */
//==============================================================================

static void _callbackGGIDScan(u32 ggid,int serviceNo)
{
    switch(ggid){
      case _MYSTERY_GGID:
        if(serviceNo == COMM_MODE_MYSTERY){
            _pCommState->partyGameBit |= PARTYGAME_MYSTERY_BCON;
        }
        break;
      case _BCON_DOWNLOAD_GGID:
        _pCommState->partyGameBit |= PARTYGAME_MYSTERY_BCON;
        break;
      case _RANGER_GGID:
        _pCommState->partyGameBit |= PARTYGAME_RANGER_BCON;
        break;
      case _WII_GGID:
        _pCommState->partyGameBit |= PARTYGAME_WII_BCON;
        break;
    }
}

//==============================================================================
/**
 * PARTY�T�[�`�q�@�̏�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _partySearchChildInit(void)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommMPInitialize(_pCommState->pMyStatus);
    CommInfoInitialize(_pCommState->pSaveData, NULL);
    WHSetGGIDScanCallback(_callbackGGIDScan);
    
    if(CommChildModeInit(TRUE, TRUE, _PACKETSIZE_PARTY)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_poketchBconScanning, 0);
    }
}

//==============================================================================
/**
 * �p�[�e�B�[�Q�[�������̒ʐM�����J�n�i�q�@��Ԃ̂݁j
 * @param   SAVEDATA  savedata
 * @retval  none
 */
//==============================================================================

void CommStateEnterPartyGameScanChild(SAVEDATA* pSaveData)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_PARTY );
    _commStateInitialize(pSaveData,COMM_MODE_PARTY);
    _pCommState->regulationNo = 0;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = 0;
#endif
    _CHANGE_STATE(_partySearchChildInit, 0);
}

//==============================================================================
/**
 * �p�[�e�B�[�Q�[���T�[�`�̏I������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateExitPartyGameScan(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    OHNO_PRINT("��������ؒf\n");
    // �ؒf�X�e�[�g�Ɉڍs����  �����ɐ؂�Ȃ�
    _CHANGE_STATE(_stateConnectEnd, _EXIT_SENDING_TIME);
}

//==============================================================================
/**
 * �E�����r�[�R����BIT��Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

u8 CommStateGetPartyGameBit(void)
{
  return _pCommState->partyGameBit;
}

//==============================================================================
/**
 * ���Z�b�g�I������
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommStateExitReset(void)
{
    CommSystemShutdown();
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return TRUE;
    }
    if(_pCommState->serviceNo == COMM_MODE_DPW_WIFI || _pCommState->serviceNo == COMM_MODE_FUSIGI_WIFI){
        mydwc_Logout();
        return TRUE;
    }
    else if(CommStateIsWifiConnect()){
        OHNO_SP_PRINT(" ���O�A�E�g����\n");
        _CHANGE_STATE(_stateWifiLogout,0);  // ���O�A�E�g����
    }
    else{
        _CHANGE_STATE(_underSBReset, 0);  // �G���[�I���̏ꍇRESET����
    }
    return FALSE;
}

//==============================================================================
/**
 * �s�v�c�ʐM�e�@�Ƃ��ď��������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _mysteryParentInit(void)
{
    MYSTATUS* pMyStatus;
    
    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommMPInitialize(_pCommState->pMyStatus);
    CommInfoInitialize(_pCommState->pSaveData, NULL);

    if(CommParentModeInit(TRUE, TRUE, _PACKETSIZE_BATTLE,TRUE)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_battleParentSendName, 0);
    }
}

//==============================================================================
/**
 * �s�v�c�ʐM�q�@�̏�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _mysteryChildInit(void)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommMPInitialize(_pCommState->pMyStatus);
    CommInfoInitialize(_pCommState->pSaveData, NULL);
    
    if(CommChildModeInit(TRUE, TRUE, _PACKETSIZE_BATTLE)){
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_battleChildBconScanning, 0);
    }
}




//---------------------wifi


//==============================================================================
/**
 * �G���[�������������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleError(void){}

static void _wifiBattleTimeout(void)
{
   int ret;
    ret = mydwc_step();

	if( ret < 0 ){
        // �G���[�����B
        _CHANGE_STATE(_wifiBattleError, 0);
    }		
}

static void _wifiBattleDisconnect(void){}

static void _wifiBattleFailed(void){}

static int _wifiLinkLevel(void)
{
    return WM_LINK_LEVEL_3 - DWC_GetLinkLevel();
}

//==============================================================================
/**
 * �ڑ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleConnect(void)
{
    int ret,errCode;

    CommSetWifiConnect(TRUE);

    ret = mydwc_step();

    if(ret >= DWC_ERROR_FRIENDS_SHORTAGE){
        _CHANGE_STATE(_wifiBattleFailed, 0);
    }
    else if( ret < 0 ){
        // �G���[�����B
        _CHANGE_STATE(_wifiBattleError, 0);
    }		
    else if( ret == 1 ) {     // �^�C���A�E�g�i���肩��P�O�b�ȏチ�b�Z�[�W���͂��Ȃ��j
        _CHANGE_STATE(_wifiBattleTimeout, 0);
    }
    else if(ret == 2){
        OHNO_PRINT("�ؒf�G���[\n");
        if(_pCommState->bDisconnectError){
            _CHANGE_STATE(_wifiBattleError, 0);
        }
        else{
            _CHANGE_STATE(_wifiBattleDisconnect, 0);
        }
    }
}

//==============================================================================
/**
 * �G���[�R�[�h�R���o�[�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _errcodeConvert(int ret)
{
    // �G���[�����B	
    int errorcode;
    if( (ret == ERRORCODE_HEAP) || (ret == ERRORCODE_0)){
        errorcode = ret;
    }
    else {
        errorcode = -ret;
    }
    _pCommState->errorCode = errorcode;
    OS_TPrintf("�G���[���������܂����B�G���[�R�[�h(%d)\n", errorcode);
}


//==============================================================================
/**
 * �ΐ푊���T����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleMaching(void)
{
    int ret = mydwc_stepmatch( 0 );

    if(ret >= DWC_ERROR_FRIENDS_SHORTAGE){
        _CHANGE_STATE(_wifiBattleFailed, 0);
    }
    else if( ret < 0 ){
        _errcodeConvert(ret);
        _CHANGE_STATE(_wifiBattleError, 0);
    }
    else if ( ret == STEPMATCH_SUCCESS )  {
        OS_TPrintf("�ΐ푊�肪������܂����B\n");
        _CHANGE_STATE(_wifiBattleConnect, 0);
    }
    else if ( ret == STEPMATCH_CANCEL ){
        OS_TPrintf("�L�����Z�����܂����B\n");	
        _CHANGE_STATE(_wifiBattleDisconnect, 0);
    }
    else if( ret == STEPMATCH_FAIL){
        _CHANGE_STATE(_wifiBattleFailed, 0);
    }
    
}



//==============================================================================
/**
 * �L�����Z����  �e����߂鎞��؂�ւ��鎞�Ɏg�p
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleCanceling(void)
{

    int ret = mydwc_stepmatch( 1 );  // �L�����Z����
				
    if( ret < 0 ){
        // �G���[�����B
        _errcodeConvert(ret);
        _CHANGE_STATE(_wifiBattleError, 0);
    }
    else{
        if( mydwc_startgame( _pCommState->wifiTargetNo ) ){
            CommSystemReset();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
            if( _pCommState->wifiTargetNo < 0 ){
                OS_TPrintf("�Q�[���Q���҂��W���܂��B\n");
            } else {
                OS_TPrintf(" %d�Ԗڂ̗F�B�ɐڑ����܂��B\n", _pCommState->wifiTargetNo);	        
            }
            _CHANGE_STATE(_wifiBattleMaching, 0);
        }
        else{
            OHNO_PRINT(" ��Ԃ�ύX�ł��Ȃ����� ������������\n");
//            _CHANGE_STATE(_wifiBattleLogin, 0);  // ��Ԃ�ύX�ł��Ȃ�����
        }
    }
}

#define _VCT_TEST (1)

//==============================================================================
/**
 * �Q�[�����J�n����B// 2006.4.13 �g���ǉ�
 * @param   target: ���Ȃ�e�A�O�ȏ�Ȃ�Ȃ��ɂ����e�@�̔ԍ�
 * @retval  1. �����@�@0. ���s
 */
//==============================================================================
int CommWifiBattleStart( int target )
{
#if _VCT_TEST
	mydwc_setReceiver( CommRecvParentCallback, CommRecvCallback );
    _pCommState->wifiTargetNo = target;
    _CHANGE_STATE(_wifiBattleCanceling,0);  // ���̏�Ԃ�j��
    return 1;
#else

    if( _pCommState->state != _wifiBattleLogin ) return 0;
	
	mydwc_setReceiver( CommRecvParentCallback, CommRecvCallback );
	
    if( mydwc_startgame( target ) ){
	    if( target < 0 ){
	        OS_TPrintf("�Q�[���Q���҂��W���܂��B\n");
        } else {
	        OS_TPrintf("%d�Ԗڂ̗F�B�ɐڑ����܂��B\n", target);	        
        }
        _CHANGE_STATE(_wifiBattleMaching, 0);
        return 1;
    }	
    return 0;
#endif
}

//==============================================================================
/**
 * �}�b�`���O�������������ǂ����𔻒�
 * @param   target: ���Ȃ�e�A�O�ȏ�Ȃ�Ȃ��ɂ����e�@�̔ԍ�
 * @retval  1. �����@�@0. �ڑ���   2. �G���[��L�����Z���Œ��f
 */
//==============================================================================
int CommWifiIsMatched(void)
{
	if( _pCommState->state == _wifiBattleMaching ) return 0;
	if( _pCommState->state == _wifiBattleConnect ) return 1;
    if(  _pCommState->state == _wifiBattleTimeout ) return 3;
    if(  _pCommState->state == _wifiBattleDisconnect ) return 4;
    if(  _pCommState->state == _wifiBattleFailed ) return 5;
//	if( _pCommState->state == _wifiBattleError ) return 5;
    return 2;
}

//==============================================================================
/**
 * �e�@�Ƃ��đҋ@��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleLogin(void)
{
    mydwc_setReceiver( CommRecvParentCallback, CommRecvCallback );
    if( mydwc_startgame( -1 ) ){   //�ŏ���VCT�҂���ԂɂȂ�
        _pCommState->bWifiDisconnect = FALSE;
        CommSystemReset();   // ���܂ł̒ʐM�o�b�t�@���N���[���ɂ���
        OS_TPrintf("VCT�Q���҂��W���܂��B\n");
        _CHANGE_STATE(_wifiBattleMaching, 0);
    }
}

//==============================================================================
/**
 * �}�b�`���O���I������
 * @param   none
 * @retval  none
 */
//==============================================================================


static void _stateWifiMatchEnd(void)
{
    int ret;

    CommSetWifiConnect(FALSE);
    if(mydwc_disconnect( _pCommState->disconnectIndex )){
        mydwc_returnLobby();
        _CHANGE_STATE(_wifiBattleLogin, 0);
        return;
    }
    ret = mydwc_step();
    if( ret < 0 ){
        OHNO_PRINT(" �G���[�����B");
        _CHANGE_STATE(_wifiBattleError, 0);
    }
}

//==============================================================================
/**
 * WIFI�I���R�}���h   �q�@���e�@�ɂ�߂�悤�ɑ��M �Ԃ��肫�� CS_WIFI_EXIT
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommRecvExit(int netID, int size, void* pData, void* pWork)
{
    OHNO_PRINT("EXIT�R�}���h��M\n");
    if(CommGetCurrentID() == COMM_PARENT_ID){
        _pCommState->disconnectIndex = 0;
        _CHANGE_STATE(_stateWifiMatchEnd, 0);
    }
    else{
        _pCommState->disconnectIndex = 1;
        _CHANGE_STATE(_stateWifiMatchEnd, 0);
    }
    _pCommState->bWifiDisconnect = TRUE;
}

//==============================================================================
/**
 * Wifi�ؒf�R�}���h���󂯎�����ꍇTRUE
 * @param   none
 * @retval  WifiLogin�Ɉڍs�����ꍇTRUE
 */
//==============================================================================

BOOL CommStateIsWifiDisconnect(void)
{
    return _pCommState->bWifiDisconnect;
}

//==============================================================================
/**
 * WifiLogin�Ɉڍs�������ǂ����̊m�F
 * @param   none
 * @retval  WifiLogin�Ɉڍs�����ꍇTRUE
 */
//==============================================================================

BOOL CommStateIsWifiLoginState(void)
{
    u32 stateAddr = (u32)_pCommState->state;

    if(stateAddr == (u32)_wifiBattleLogin){
        return TRUE;
    }
    return FALSE;
}


BOOL CommStateIsWifiLoginMatchState(void)
{
    u32 stateAddr = (u32)_pCommState->state;

    if(stateAddr == (u32)_wifiBattleMaching){
        return TRUE;
    }
    else if(stateAddr == (u32)_wifiBattleLogin){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * WifiError�̏ꍇ���̔ԍ���Ԃ�  �G���[�ɂȂ��Ă邩�ǂ������m�F���Ă�������o������
 * @param   none
 * @retval  Error�ԍ�
 */
//==============================================================================

int CommStateGetWifiErrorNo(void)
{
    return _pCommState->errorCode;
}



//==============================================================================
/**
 * WIFI�Ń��O�A�E�g���s���ꍇ�̏���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateWifiLogout(void)
{
    int ret;
    
    CommSetWifiConnect(FALSE);
    if(mydwc_disconnect( 0 )){
        mydwc_returnLobby();
        _CHANGE_STATE(_stateConnectEnd, 0);
    }
    ret = mydwc_step();
    if( ret < 0 ){
        // �G���[�����B
        _CHANGE_STATE(_wifiBattleError, 0);
    }
}

//==============================================================================
/**
 * WIFI�Ń��O�A�E�g���s���ꍇ�̏�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateWifiLogout(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    sys_SoftResetOK(SOFTRESET_TYPE_WIFI);
    OHNO_SP_PRINT("��������ؒf\n");
    _CHANGE_STATE(_stateConnectEnd, _EXIT_SENDING_TIME);
}

//==============================================================================
/**
 * WIFI�Ń}�b�`���O��؂�ꍇ�̏���
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateWifiMatchEnd(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    _pCommState->disconnectIndex = 0;
    _CHANGE_STATE(_stateWifiMatchEnd, 0);
}

//==============================================================================
/**
 * WIFI�Ń}�b�`���O��؂�ꍇ�̏��� ��������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateWifiTradeMatchEnd(void)
{
    if(_pCommState==NULL){  // ���łɏI�����Ă���
        return;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){
        OHNO_PRINT("�e�͎����Ő؂�\n");
        _pCommState->disconnectIndex = 0;
    }
    else{
        OHNO_PRINT("�q�͑ҋ@����\n");
        _pCommState->disconnectIndex = 1;
    }
    _CHANGE_STATE(_stateWifiMatchEnd, 0);
}





void CommStateWifiBattleMatchEnd(void)
{
    u8 id = CommGetCurrentID();
    
    OHNO_PRINT("CS_WIFI_EXIT %d\n",id);
    CommSendFixSizeData(CS_WIFI_EXIT,&id);
}


//==============================================================================
/**
 * WifiError���ǂ���
 * @param   none
 * @retval  Error
 */
//==============================================================================

BOOL CommStateIsWifiError(void)
{
    if(_pCommState){
        u32 stateAddr = (u32)_pCommState->state;
        if(stateAddr == (u32)_wifiBattleError){
            return TRUE;
        }
        if((stateAddr == (u32)_wifiBattleTimeout) && _pCommState->bDisconnectError){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * ���E�����A���E�o�g���^���[�̊J�n  �G���[�Ǘ��p
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateWifiDPWStart(SAVEDATA* pSaveData)
{
    if(!_pCommState){
        sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_DPW );
        _pCommState = (_COMM_STATE_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_STATE_WORK));
        MI_CpuFill8(_pCommState, 0, sizeof(_COMM_STATE_WORK));
        _pCommState->serviceNo = COMM_MODE_DPW_WIFI;
        _pCommState->bWorldWifi = TRUE;
        _pCommState->pSaveData = pSaveData;
        CommStateSetErrorCheck(FALSE,TRUE);
        sys_SoftResetNG(SOFTRESET_TYPE_WIFI);
    }
}

//==============================================================================
/**
 * ���E�����A���E�o�g���^���[�̏I��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateWifiDPWEnd(void)
{
    if(_pCommState){
        sys_SoftResetOK(SOFTRESET_TYPE_WIFI);
        CommStateSetErrorCheck(FALSE,FALSE);
        sys_FreeMemoryEz(_pCommState);
        _pCommState = NULL;
        sys_DeleteHeap(HEAPID_COMMUNICATION);
    }
}

//==============================================================================
/**
 * ���E�ӂ�������  �G���[�Ǘ��p
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateWifiFusigiStart(SAVEDATA* pSaveData)
{
    if(!_pCommState){
        sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_DPW );
        _pCommState = (_COMM_STATE_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_STATE_WORK));
        MI_CpuFill8(_pCommState, 0, sizeof(_COMM_STATE_WORK));
        _pCommState->serviceNo = COMM_MODE_FUSIGI_WIFI;
        _pCommState->bWorldWifi = TRUE;
        _pCommState->pSaveData = pSaveData;
        CommStateSetErrorCheck(FALSE,TRUE);
        sys_SoftResetNG(SOFTRESET_TYPE_WIFI);
    }
}

//==============================================================================
/**
 * ���E�����A���E�o�g���^���[�̏I��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateWifiFusigiEnd(void)
{
    if(_pCommState){
        sys_SoftResetOK(SOFTRESET_TYPE_WIFI);
        CommStateSetErrorCheck(FALSE,FALSE);
        sys_FreeMemoryEz(_pCommState);
        _pCommState = NULL;
        sys_DeleteHeap(HEAPID_COMMUNICATION);
    }
}




//==============================================================================
/**
 * ���E�����A���E�o�g���^���[�ŃG���[���ǂ���
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommStateGetWifiDPWError(void)
{
	int errorCode,ret;
	DWCErrorType myErrorType;
    
    if(!_pCommState){
        return FALSE;
    }

    if((_pCommState->serviceNo == COMM_MODE_DPW_WIFI)){
        ret = DWC_GetLastErrorEx( &errorCode, &myErrorType );
        if(ret!=0){
            DWC_ClearError();
            return TRUE;
        }
    } else if(_pCommState->serviceNo == COMM_MODE_FUSIGI_WIFI){
        ret = DWC_GetLastErrorEx( &errorCode, &myErrorType );
        if(ret!=0){
	  if(myErrorType == DWC_ETYPE_FATAL){
	    OS_TPrintf("�G���[��ߊl: %d, %d\n", errorCode, myErrorType);
            return TRUE;
	  }
	}
    }
    return FALSE;
}


//==============================================================================
/**
 * �q�@�ҋ@���  �e�@��I��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleConnecting(void)
{
    // �ڑ���
    int ret = mydwc_connect();

    if( ret < 0 ){
        _errcodeConvert(ret);
        _CHANGE_STATE(_wifiBattleError, 0);
    }
    else if ( ret > 0 ) 
    {
        OS_TPrintf("WiFi�R�l�N�V�����ɐڑ����܂����B\n	");
        _CHANGE_STATE(_wifiBattleLogin, 0);
    }
}


//==============================================================================
/**
 * �e�@�Ƃ��ď��������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleParentInit(void)
{
    MYSTATUS* pMyStatus;
    
    if(!CommIsVRAMDInitialize()){
        return;
    }
    {
        sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_WIFIMENU, _HEAPSIZE_WIFI);
    }

    if(CommParentModeInit(TRUE, TRUE, _PACKETSIZE_BATTLE,TRUE)){
        mydwc_startConnect(_pCommState->pSaveData, HEAPID_WIFIMENU);
        mydwc_setFetalErrorCallback(CommFatalErrorFunc);

        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_wifiBattleConnecting, 0);
    }
}

//==============================================================================
/**
 * �q�@�̏�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _wifiBattleChildInit(void)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }

    {
        sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_WIFIMENU, _HEAPSIZE_WIFI);
    }
    
    if(CommChildModeInit(TRUE, TRUE, _PACKETSIZE_BATTLE)){
        mydwc_startConnect(_pCommState->pSaveData, HEAPID_WIFIMENU);
        CommSetTransmissonTypeDS();
        _CHANGE_STATE(_wifiBattleConnecting, 0);
    }
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

#ifdef PM_DEBUG
void CommStateWifiEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, int soloDebugNo)
#else
void CommStateWifiEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo)
#endif
{
    MYSTATUS* pMyStatus = SaveData_GetMyStatus(pSaveData);
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    sys_SoftResetNG(SOFTRESET_TYPE_WIFI);
    // �ʐM�q�[�v�쐬
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_BATTLE );
    _commStateInitialize(pSaveData,serviceNo);
//    _pCommState->serviceNo = serviceNo;
    _pCommState->regulationNo = regulationNo;
    _pCommState->pSaveData = pSaveData;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = soloDebugNo;
#endif
    
    _CHANGE_STATE(_wifiBattleChildInit, 0);
}


//==============================================================================
/**
 * �o�g�����̐e�Ƃ��Ă̒ʐM�����J�n
 * @param   pMyStatus  mystatus
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @param   regulationNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

#ifdef PM_DEBUG
void CommStateWifiEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, int soloDebugNo)
#else
void CommStateWifiEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo)
#endif
{
    MYSTATUS* pMyStatus = SaveData_GetMyStatus(pSaveData);
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_SoftResetNG(SOFTRESET_TYPE_WIFI);
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_BATTLE );
    _commStateInitialize(pSaveData,serviceNo);
//    _pCommState->serviceNo = serviceNo;
    _pCommState->regulationNo = regulationNo;
    _pCommState->pSaveData = pSaveData;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = soloDebugNo;
#endif
    _CHANGE_STATE(_wifiBattleParentInit, 0);
}

//==============================================================================
/**
 * WIFI���Ƀ��O�C������ׂ̒ʐM�J�n
 * @param   pSaveData
 * @retval  none
 */
//==============================================================================

void* CommStateWifiEnterLogin(SAVEDATA* pSaveData, int wifiFriendStatusSize)
{
    MYSTATUS* pMyStatus = SaveData_GetMyStatus(pSaveData);
    if(CommIsInitialize()){
        return NULL;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
    sys_SoftResetNG(SOFTRESET_TYPE_WIFI);
    sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_COMMUNICATION, _HEAPSIZE_BATTLE );
    _commStateInitialize(pSaveData,COMM_MODE_LOGIN_WIFI);
    _pCommState->pWifiFriendStatus = sys_AllocMemory( HEAPID_COMMUNICATION, wifiFriendStatusSize );
    MI_CpuFill8( _pCommState->pWifiFriendStatus, 0, wifiFriendStatusSize );
//    _pCommState->serviceNo = COMM_MODE_LOGIN_WIFI;
    _pCommState->regulationNo = 0;
    _pCommState->pSaveData = pSaveData;
#ifdef PM_DEBUG
    _pCommState->soloDebugNo = 0;
#endif

    
    _CHANGE_STATE(_wifiBattleParentInit, 0);
    return _pCommState->pWifiFriendStatus;
}

//==============================================================================
/**
 * WIFI�t�����h�pWORK��n��
 * @param   pSaveData
 * @retval  none
 */
//==============================================================================

void* CommStateGetMatchWork(void)
{
    return _pCommState->pWifiFriendStatus;
}

//==============================================================================
/**
 * ���������G���[�̌�����ʐM���������邩�ǂ�����ݒ�
 * @param   bFlg    �ؒf=�G���[�ɂ���
 * @param   bAuto  TRUE�Ō����J�n
 * @retval  none
 */
//==============================================================================

void CommStateSetErrorCheck(BOOL bFlg,BOOL bAuto)
{
    if(_pCommState){
        _pCommState->bDisconnectError = bFlg;
        _pCommState->bErrorAuto = bAuto;
        OHNO_PRINT("CommStateSetErrorCheck %d %d\n",_pCommState->bDisconnectError,_pCommState->bErrorAuto);
    }
    CommMPSetNoChildError(bFlg);  // �q�@�����Ȃ��Ȃ�����Č������邽�߂�ERR�����ɂ���
    CommMPSetDisconnectOtherError(bFlg);
}


//==============================================================================
/**
 * ���������G���[�̌�����ʐM���������邩�ǂ�����ݒ�
 * @param   bFlg  TRUE�Ō����J�n
 * @retval  none
 */
//==============================================================================

BOOL CommStateGetErrorCheck(void)
{
    if(_pCommState){
        if(_pCommState->stateError!=0){
            return TRUE;
        }
        return _pCommState->bErrorAuto;
    }
    return FALSE;
//    CommMPSetDisconnectOtherError(bFlg);
}


#ifdef PM_DEBUG
//==============================================================================
/**
 * �f�o�b�O�p�ʐM�ڑ��J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommStateRecvDebugStart(int netID, int size, void* pData, void* pWork)
{
    if(_pCommState){
        _pCommState->bDebugStart = TRUE;
    }
    OHNO_PRINT("�R�}���h����\n");
}

BOOL CommStateDBattleIsReady(void)
{
    if(_pCommState){
        return _pCommState->bDebugStart;
    }
    return FALSE;
}

static void _commConnectChildDebug(TCB_PTR tcb, void* work)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }
    if(CommMPGetGFBss(_pCommState->connectIndex)!=NULL){
        OHNO_PRINT("�f�o�b�O�q�@�ڑ��J�n\n");
        CommStateConnectBattleChild(_pCommState->connectIndex);  // �ڑ�
        TCB_Delete(tcb);
    }
}

static void _commConnectParentDebug(TCB_PTR tcb, void* work)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }
    if(CommGetConnectNum() == (CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1) ){
        OHNO_PRINT("�ڑ��l���ɒB����\n");
        CommSendFixData(CS_DEBUG_START);  // �S���ɃR�}���h���M
        TCB_Delete(tcb);
    }
}

void CommStateDBattleConnect(BOOL bParent, int gameMode, SAVEDATA* pSaveData)
{
    MYSTATUS* pMyStatus = SaveData_GetMyStatus(pSaveData);
    if(COMM_MODE_BATTLE_SINGLE_WIFI <= gameMode){
/*  ���͕���
        DwcOverlayStart();
        if(!bParent){
            CommStateWifiEnterBattleChild(pSaveData, gameMode, 0, SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
            _pCommState->connectIndex = 0;
            TCB_Add(_commConnectChildDebug, NULL, _TCB_COMMCHECK_PRT-2);
        }
        else{
            CommStateWifiEnterBattleParent(pSaveData, gameMode, 0, SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
            TCB_Add(_commConnectParentDebug, NULL, _TCB_COMMCHECK_PRT-2);
        }
   */
    }
    else{
        if(!bParent){
            CommStateEnterBattleChild(pSaveData, gameMode, 0, NULL, FALSE, SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
            _pCommState->connectIndex = 0;
            TCB_Add(_commConnectChildDebug, NULL, _TCB_COMMCHECK_PRT-1);
        }
        else{
            CommStateEnterBattleParent(pSaveData, gameMode, 0, NULL, FALSE, SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
            TCB_Add(_commConnectParentDebug, NULL, _TCB_COMMCHECK_PRT-1);
        }
    }
    _pCommState->bDebugStart = FALSE;
}

#endif //PM_DEBUG



int CommStateGetServiceNo(void)
{
    if(_pCommState){
        return _pCommState->serviceNo;
    }
    return COMM_MODE_BATTLE_SINGLE;
}

int CommStateGetRegulationNo(void)
{
    if(_pCommState){
        return _pCommState->regulationNo;
    }
    return COMM_REG_NORMAL;
}

void CommStateSetPokemon(u8* sel)
{
    MI_CpuCopy8(sel,_pCommState->select,NELEMS(_pCommState->select));

    OHNO_SP_PRINT("%d %d %d %d %d %d\n",sel[0],sel[1],sel[2],sel[3],sel[4],sel[5]);
}

void CommStateGetPokemon(u8* sel)
{
    MI_CpuCopy8(_pCommState->select,sel,NELEMS(_pCommState->select));
}


#ifdef PM_DEBUG
int CommStateGetSoloDebugNo(void)
{
    if(_pCommState){
        return _pCommState->soloDebugNo;
    }
    return 0;
}
#endif


//==============================================================================
/**
 * �ʐM��WIFI�ڑ����Ă��邩�ǂ�����Ԃ�
 * @param   none
 * @retval  �ڑ����Ă�����TRUE
 */
//==============================================================================

BOOL CommStateIsWifiConnect(void)
{
    if(CommStateGetServiceNo() < COMM_MODE_BATTLE_SINGLE_WIFI){
        return FALSE;
    }
    return TRUE;
}


//==============================================================================
/**
 * �G���[��Ԃɓ���
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSetErrorReset(u8 type)
{
    if(_pCommState){
        _pCommState->ResetStateType = type;
    }
}

//==============================================================================
/**
 * ���Z�b�g�G���[��ԂɂȂ������ǂ����m�F����
 * @param   none
 * @retval  ���Z�b�g�G���[��ԂȂ�TRUE
 */
//==============================================================================

u8 CommIsResetError(void)
{
    if(_pCommState){
        return _pCommState->ResetStateType;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   fatal�G���[�p�֐�  ���̊֐������甲�����Ȃ�
 * @param   no   �G���[�ԍ�
 * @retval  none
 */
//--------------------------------------------------------------

void CommFatalErrorFunc(int no)
{
    int i=0;
    
    ComErrorWarningResetCall(HEAPID_BASE_SYSTEM,COMM_ERRORTYPE_POWEROFF, no);
    while(1){
        i++;
    }
}

void CommFatalErrorFunc_NoNumber( void )
{
    int i=0;
    
    ComErrorWarningResetCall( HEAPID_BASE_SYSTEM, 4, 0 );
    while(1){
        i++;
    }
}

//--------------------------------------------------------------
/**
 * @brief   �G���[�����m���� �ʐM�G���[�p�E�C���h�E���o��
 * @param   heapID    �������[�m�ۂ���HEAPID
 * @param   bgl       GF_BGL_INI
 * @retval  none
 */
//--------------------------------------------------------------

void CommErrorCheck(int heapID, GF_BGL_INI* bgl)
{
// ���̊֐��ł͏������Ȃ����ƂɂȂ�܂���
}


//--------------------------------------------------------------
/**
 * @brief   �G���[�����m���� �ʐM�G���[�p�E�C���h�E���o��
 * @param   heapID    �������[�m�ۂ���HEAPID
 * @param   bgl       GF_BGL_INI
 * @retval  none
 */
//--------------------------------------------------------------

void CommErrorDispCheck(int heapID)
{
    if(CommStateGetErrorCheck()){
        if(CommIsError() || CommStateIsWifiError() || CommStateGetWifiDPWError()
           || (_pCommState->stateError!=0)){
            if(!CommIsResetError()){   // ���Z�b�g�G���[��ԂŖ����ꍇ
                OHNO_PRINT("�T�E���h�X�g�b�v\n");
                Snd_Stop();
                OHNO_PRINT("�Z�[�u�X�g�b�v\n");
                SaveData_DivSave_Cancel(_pCommState->pSaveData); // �Z�[�u���Ă���~�߂�
                sys.tp_auto_samp = 1;  // �T���v�����O���~�߂�

                OHNO_PRINT("�G���[�\��\n");
                if(_pCommState->stateError == COMM_ERROR_RESET_GTS){
                    CommSetErrorReset(COMM_ERROR_RESET_GTS);  // �G���[���Z�b�g��ԂɂȂ�
                }
                else if((_pCommState->serviceNo == COMM_MODE_FUSIGI_WIFI)
                   || (_pCommState->serviceNo == COMM_MODE_MYSTERY)){
                    CommSetErrorReset(COMM_ERROR_RESET_TITLE);  // �G���[���Z�b�g��ԂɂȂ�
                }
                else{
                    CommSetErrorReset(COMM_ERROR_RESET_SAVEPOINT);  // �G���[���Z�b�g��ԂɂȂ�
                }
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�b�g�ł����Ԃ��ǂ���
 * @param   none
 * @retval  TRUE �Ȃ烊�Z�b�g
 */
//--------------------------------------------------------------

BOOL CommStateIsResetEnd(void)
{
    if(CommMPIsConnectStalth() || !CommStateIsInitialize()){ // �ʐM�I��
        return TRUE;
    }
    if(!CommMPIsConnect()){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �G���[�ɂ���ꍇ���̊֐����ĂԂƃG���[�ɂȂ�܂�
 * @param   �G���[���
 * @retval  �󂯕t�����ꍇTRUE
 */
//==============================================================================

BOOL CommStateSetError(int no)
{

    if(_pCommState){
        _pCommState->stateError = no;
        CommSystemShutdown();
        return TRUE;
    }
    return FALSE;
}


