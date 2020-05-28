//=============================================================================
/**
 * @file	comm_field_state.c
 * @brief	�ʐM��Ԃ��Ǘ�����T�[�r�X  �ʐM�̏�ʂɂ���
 *          �X���b�h�̂ЂƂƂ��ē����A�����̒ʐM��Ԃ⑼�̋@���
 *          �J�n��I�����Ǘ�����
 *          �t�B�[���h��Œ��ڊǗ��������̂�communication����field�Ɉړ� 2005.09.28
 * @author	Katsumi Ohno
 * @date    2005.08.02
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "system/gamedata.h"
#include "system/pm_str.h"

#include "comm_field_state.h"
#include "underground/ug_manager.h"
#include "field/field.h"
#include "fieldsys.h"
#include "comm_command_field.h"
#include "comm_direct_counter.h"
#include "comm_vsroom.h"
#include "sysflag.h"

#include "script.h"							//StartFieldScript
#include "..\fielddata\script\common_scr_def.h"		//SCRID_TRAINER_MOVE_SCRIPT
#include "..\fielddata\script\connect_def.h"		//SCRID_CONNECT_COLOSSEUM
#include "../fielddata/script/battle_room_def.h"
#include "savedata/trainercard_data.h"
#include "application/trainer_card.h"
#include "tr_card_setup.h"
#include "system/wipe.h"
#include "system/pm_overlay.h"
#include "system/brightness.h"

#include "field/union_beacon_tool.h"
#include "field_encount.h"

#ifdef PM_DEBUG
#include "d_ohno.h"
#include "fld_debug.h"
#endif
//==============================================================================
//	�^�錾
//==============================================================================
// �R�[���o�b�N�֐��̏���
typedef void (*PTRStateFunc)(void);

#define _TRAINER_CARD_NUM_MAX (4)

//==============================================================================
// ���[�N
//==============================================================================

typedef struct{
    TR_CARD_DATA* pTRCard[_TRAINER_CARD_NUM_MAX];  // �g���[�i�[�J�[�h����M����o�b�t�@�̃|�C���^
    u8 bTRCard[_TRAINER_CARD_NUM_MAX];
    COMM_MESSAGE* pCMess;
    FIELDSYS_WORK* pFSys;
    MATHRandContext32 sRand; ///< �e�q�@�l�S�V�G�[�V�����p�����L�[
    PTRStateFunc state;
    TCB_PTR pTcb;
    u16 timer;
    u8 connectIndex;   // �q�@���ڑ�����e�@��index�ԍ�
    u8 bStalth;
    u8 bStateNoChange;
    u8 bUGOverlay;
    u8 bReturnBattle; // �o�g������߂��Ă����ꍇ�͂P �����Ă����ꍇ�͂O
    u8 bBattleMoveRoom; // �J�n�ʒu�ɂ������Ƃ���M

    POKEPARTY*  party;	// �~�b�N�X�o�g���p�p�[�e�B

#ifdef PM_DEBUG		// Debug ROM
    u16 debugTimer;
#endif
} _COMM_FSTATE_WORK;

static _COMM_FSTATE_WORK* _pCommFState = NULL;  ///<�@���[�N�\���̂̃|�C���^

//==============================================================================
// ��`
//==============================================================================
#define _START_TIME (50)     // �J�n����
#define _CHILD_P_SEARCH_TIME (12) ///�q�@�Ƃ��Đe��T������
#define _PARENT_WAIT_TIME (40) ///�e�Ƃ��Ă̂�т�҂���
#define _FINALIZE_TIME (2)
#define _EXIT_SENDING_TIME (5)
#define _PARENT_END_TIME (2)
#define _SEND_NAME_TIME (10)
#define _PARENTSCAN_PA (3)  // �e�@�Ƃ��Č�������m����1/3

#define _TCB_COMMCHECK_PRT   (10)    ///< �t�B�[���h������ʐM�̊Ď����[�`����PRI


//==============================================================================
// static�錾
//==============================================================================

// �X�e�[�g�̏�����

static void _commStateInitialize(FIELDSYS_WORK* pFSys);  // ������
static void _commCheckFunc(TCB_PTR tcb, void* work);  // �X�e�[�g�����s���Ă���^�X�N
static void _changeState(PTRStateFunc state, int time);  // �X�e�[�g��ύX����
static void _changeStateDebug(PTRStateFunc state, int time, int line);  // �X�e�[�g��ύX����

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
static void _underStart(void);           // ������ + �V�X�e���̏�����
static void _underOpenning(void);       //�C�x���g��
static void _underConnecttingAloneSend(void);  // �������]������
static void _underConnectting(void);     // �ڑ���
static void _underChildConnecting(void);   // �q�@���e�@�ɐڑ���
static void _underChildConnectInfoWait(void);  // �q�@�Ƃ��Đڑ��� info���W
static void _underChildConnectFlagWait(void);
static void _underChildConnectSecret(void);    // �q�@�Ƃ��Đڑ���
static void _underChildConnectDig(void);    // �q�@�Ƃ��Đڑ���
static void _underChildConnect(void);    // �q�@�Ƃ��Đڑ���
static void _underChildConnect_JumpFieldStart(void);    // �q�@�Ƃ��Đڑ��� Jump�J�n
static void _underChildConnect_JumpField(void);    // �q�@�Ƃ��Đڑ��� Jump��
static void _underChildConnect_JumpFieldEnd(void);    // �q�@�Ƃ��Đڑ��� Jump�����
static void _underParentRestart(void);
#if T1645_060815_FIX
static void _underParentRestartAloneWait(void);
#endif //T1645_060815_FIX
static void _underChildRestart(void);
static void _underChildRestart_Base(void);
static void _underChildStalth(void);

static void _underParentWait(void);      // �e�@�Ƃ��đҋ@���
static void _underParentConnect(void);   // �e�@�Ƃ��Đڑ���
static void _underParentConnect_JumpFieldStart(void);  // �e�@�Ƃ��Đڑ��� Jump�J�n
static void _underParentConnect_JumpField(void);  // �e�@�Ƃ��Đڑ��� Jump��
static void _underParentConnect_JumpFieldEnd(void);  // �e�@�Ƃ��Đڑ��� Jump�I���
static void _stateUnderGroundConnectEnd(void);  // �n���ؒf

static void _underSoloConnect_JumpFieldStart(void);    // solo�@�Ƃ��Đڑ��� Jump�J�n
static void _underSoloConnect_JumpField(void);    // solo�@�Ƃ��Đڑ��� Jump��
static void _underSoloConnect_JumpFieldEnd(void);    // solo�@�Ƃ��Đڑ��� Jump�����
static void _underStalthConnect_JumpFieldStart(void);    // stalth�@�Ƃ��Đڑ��� Jump�J�n
static void _underStalthConnect_JumpField(void);    // stalth�@�Ƃ��Đڑ��� Jump��
static void _underStalthConnect_JumpFieldEnd(void);    // stalth�@�Ƃ��Đڑ��� Jump�����

static void _underChildStalthDeadLoop(void);


// �o�g���֘A�X�e�[�g
static void _battleParentInit(void);     // �퓬�p�e�@�Ƃ��ď�����
static void _battleParentWaiting(void);  // �퓬�p�e�@�Ƃ��đҋ@��

static void _battleChildInit(void);     // �퓬�p�q�@�Ƃ��ď�����
static void _battleChildBconScanning(void);  // �퓬�p�q�@�Ƃ��Đe�@�I��
static void _battleChildConnecting(void);  // �ڑ������炢��
static void _battleChildSendName(void);  // �����̖��O���݂�Ȃɑ��M
static void _battleChildWaiting(void);  // �_�C���N�g�p�q�@�ҋ@��
static void _battleMoveRoomEnter(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleMoveRoomEnter2(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleMoveRoomReturn(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleMoveRoomReturn2(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleMoveRoomReturn3(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleMoveRoomWait(void);
static void _battleMoveRoom(void); // �퓬�O�̕����ɓ����đҋ@��
static void _battleChildReTry(void);   // �q�@�𒆒f
static void _battleChildReInit(void);   // �q�@���ċN��
static void _battleMoveRoomEnd_Tim(void);   //�o�g�����[���I�� �퓬�J�n
static void _battleMoveRoomEnd(void);   //�o�g�����[���I�� �퓬�J�n
static void _battleQuit(void);   //�o�g�����[�������I��
static void _trCardCopyEnd(void);
static void _dsChangeTiming(void);
static void _trCardCopyStart(void);
static void _dsChangeEndWaitStart(void);
static void _dsChangeEndWaitEnd(void);

// ���̑���ʓI�ȃX�e�[�g
static void _stateNone(void);            // �������Ȃ�
static void _stateConnectError(void);    // �ڑ��G���[���
static void _stateEnd(void);             // �I������
static void _stateConnectEnd(void);      // �ؒf�����J�n
static void _directEndTiming(void);
static void _directEndNoTiming(void);
static void _stateConnectAutoEnd(void);  // �����ؒf�����J�n
static void _underChildRebootFunc(void);

#ifdef PM_DEBUG		// Debug ROM
static void _debugTimerStart(void);   // �f�o�b�O�p
static void _debugTimerDisp(char* msg);
#else
static void _debugTimerStart(void){}   // �f�o�b�O�p
static void _debugTimerDisp(char* msg){}
#endif


//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏���������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commStateInitialize(FIELDSYS_WORK* pFSys)
{
    void* pWork;

    if(_pCommFState!=NULL){   // ���łɓ��쒆�̏ꍇ�K�v�Ȃ�
        return;
    }
    CommCommandFieldInitialize((void*)pFSys);
    // ������
    _pCommFState = (_COMM_FSTATE_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_FSTATE_WORK));
    MI_CpuFill8(_pCommFState, 0, sizeof(_COMM_FSTATE_WORK));
//    _pCommFState->state = NULL;   // �������Ȃ�
    _pCommFState->timer = _START_TIME;
    _pCommFState->pTcb = TCB_Add(_commCheckFunc, NULL, _TCB_COMMCHECK_PRT);
    _pCommFState->pFSys = pFSys;
    _pCommFState->party = NULL;
//    _pCommFState->bStalth = FALSE;
//    _pCommFState->bUGOverlay = FALSE;
//    _pCommFState->bStateNoChange = FALSE;
    _debugTimerStart();
    CommRandSeedInitialize(&_pCommFState->sRand);
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
    void* pWork;
    int i;

    if(_pCommFState==NULL){  // ���łɏI�����Ă���
        return;
    }
    TCB_Delete(_pCommFState->pTcb);

    for(i = 0;i < _TRAINER_CARD_NUM_MAX; i++){
        if(_pCommFState->pTRCard[i]){
            sys_FreeMemoryEz(_pCommFState->pTRCard[i]);
        }
//        sys_DeleteHeap(HEAPID_VSROOM);
    }

    if( _pCommFState->party )
    {
		sys_FreeMemoryEz( _pCommFState->party );
	}

    sys_FreeMemoryEz(_pCommFState);
//    sys_DeleteHeap(HEAPID_COMMUNICATION);
    _pCommFState = NULL;
}

//==============================================================================
/**
 * �n���ɂ͂��������̒ʐM����
 * @param   pFSys FIELDSYS_WORK
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterUnderGround(FIELDSYS_WORK* pFSys)
{
    if(_pCommFState!=NULL){ // �Ȃ����Ă���ꍇ���͏��O����
        return;
    }
    // �ڑ����s
    CommStateEnterUnderGround(GameSystem_GetSaveData(pFSys));
    _commStateInitialize(pFSys);
    sys_CreateHeap( HEAPID_BASE_APP, HEAPID_UNDERGROUND, 0xe800 );  //�O�b�Y���j���[�ł��Ȃ�m��
    if(!SysFlag_UgFirstCheck(SaveData_GetEventWork(_pCommFState->pFSys->savedata))){
        OS_TPrintf("����n���C�x���g\n");
        CommStateSetFirstEvent();
    }

}

//==============================================================================
/**
 * �n���ɂ͂����āA�t�B�[���h���n���ɕς�������̏���
 * @param   pFSys FIELDSYS_WORK
 * @retval  none
 */
//==============================================================================

void CommFieldStateArrivalUnderGround(void)
{
    _pCommFState->bUGOverlay = TRUE;
    RECORD_Score_Add(SaveData_GetRecord(_pCommFState->pFSys->savedata), SCORE_ID_MINE_IN);

    CommUnderOptionInitialize(_pCommFState->pFSys);  // �n���T�[�r�X�̋N��

#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    
    _CHANGE_STATE(_underStart, 0);
}

//==============================================================================
/**
 * �n�����o��ꍇ�̒ʐM����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateExitUnderGround(void)
{
    if(_pCommFState==NULL){  // ���łɏI�����Ă���
        return;
    }
    // �ؒf�X�e�[�g�Ɉڍs����  �����ɐ؂�Ȃ�
    
    _CHANGE_STATE(_stateUnderGroundConnectEnd, 3);
}

//==============================================================================
/**
 * �n����ʐM��~�ɂ���ꍇ�̒ʐM����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateStalthUnderGround(void)
{
    OHNO_PRINT("stalth \n");
//    CommUnderOptionFinalize();  // �������͂���@@OO
    CommStateUnderGroundOfflineSecretBase();
    _CHANGE_STATE(_underChildStalth, 0);
}

//==============================================================================
/**
 * �n�����Đڑ�����ꍇ�̏���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthEndCheck(void)
{
    if(!CommMPIsConnectStalth()){
        CommSecretBaseInfoJumpEnd();
        _CHANGE_STATE(_underStart,0);
    }

}


void CommFieldStateUnderGroundReConnect(void)
{
//    CommSecretBaseInfoChildSendStart();
    //_underChildConnect_JumpFieldEnd();
    CommStateUnderGroundOnlineSecretBase();  // �ʐM��Ԃ�ONLINE�ɂ��ǂ�

    _CHANGE_STATE(_underStalthEndCheck,0);
//    _CHANGE_STATE(_underStart,1)
    
//    CommTrapInfoChildSendStart();  //Trap���������g�ɑ��M�J�n
//    _CHANGE_STATE(_underConnectting, _CHILD_P_SEARCH_TIME*2);
}

//==============================================================================
/**
 * �n����JUMP����ꍇ�̒ʐM����
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommStateJumpUnderGround(void)
{
    int i;
    u32 stateAddr = (u32)_pCommFState->state;
    u32 parentAddr = (u32)_underParentConnect;
    u32 childAddr = (u32)_underChildConnect;
    u32 soloAddr = (u32)_underConnectting;
    u32 stalthAddr = (u32)_underChildStalthDeadLoop;
    u32 jumpState[] = {
        (u32)_underParentConnect_JumpFieldStart,
        (u32)_underChildConnect_JumpFieldStart,
        (u32)_underSoloConnect_JumpFieldStart,
        (u32)_underStalthConnect_JumpFieldStart,
    };


    
    if(stateAddr == parentAddr){
        _CHANGE_STATE(_underParentConnect_JumpFieldStart, 0);
        return TRUE;
    }
    else if(childAddr == stateAddr){
        _CHANGE_STATE(_underChildConnect_JumpFieldStart, 0);
        return TRUE;
    }
    else if(soloAddr == stateAddr){
        _CHANGE_STATE(_underSoloConnect_JumpFieldStart, 0);
        return TRUE;
    }
    else if(stalthAddr == stateAddr){
        _CHANGE_STATE(_underStalthConnect_JumpFieldStart, 0);
        return TRUE;
    }
    for(i = 0 ; i < NELEMS(jumpState); i++){
        if(jumpState[i] == stateAddr){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �n����JUMP���I������ꍇ�̏��� �X�e�[�g��Active��ԂɂȂ�
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommStateJumpEndUnderGround(void)
{
    u32 stateAddr = (u32)_pCommFState->state;
    u32 parentAddr = (u32)_underParentConnect_JumpField;
    u32 childAddr = (u32)_underChildConnect_JumpField;
    u32 soloAddr = (u32)_underSoloConnect_JumpField;
    u32 stalthAddr = (u32)_underStalthConnect_JumpField;

    if(stateAddr == parentAddr){
        _CHANGE_STATE(_underParentConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    else if(childAddr == stateAddr){
        _CHANGE_STATE(_underChildConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    else if(soloAddr == stateAddr){
        _CHANGE_STATE(_underSoloConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    else if(stalthAddr == stateAddr){
        _CHANGE_STATE(_underStalthConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    {
//        GF_ASSERT(0 && "�z��O��state:�v�C��");
    }
    return FALSE;
}

//==============================================================================
/**
 * �ړ��\�X�e�[�g�Ȃ̂��ǂ����Ԃ�
 * @param   none
 * @retval  �ړ��\�Ȃ�TRUE
 */
//==============================================================================

BOOL CommIsUnderGroundMoveState(void)
{
    int i;
    u32 funcTbl[]={
        (u32)_battleMoveRoom,
        (u32)_underChildConnect,
        (u32)_underParentConnect,
        (u32)_underChildConnectInfoWait,
        (u32)_underChildConnectFlagWait,
        (u32)_underChildConnectSecret,
        (u32)_underChildConnectDig,
        (u32)_underChildConnect_JumpFieldStart,
        (u32)_underChildConnect_JumpField,
        (u32)_underChildConnect_JumpFieldEnd,
        (u32)_underParentConnect_JumpFieldStart,
        (u32)_underParentConnect_JumpField,
        (u32)_underParentConnect_JumpFieldEnd,
        0,
    };
    u32 stateAddr = (u32)_pCommFState->state;

    if(_pCommFState==NULL){  // ���łɏI�����Ă���
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
 * �o�g�����̐e�Ƃ��Ă̒ʐM�����J�n
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleParent(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
#ifdef PM_DEBUG
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE, SOLO_DEBUG_NO);
#else
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE);
#endif
    _commStateInitialize(pFSys);
    _CHANGE_STATE(_battleParentInit, 0);
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleChild(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
    // �ʐM�q�[�v�쐬
#ifdef PM_DEBUG
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE, SOLO_DEBUG_NO);
#else
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE);
#endif
    _commStateInitialize(pFSys);
    _CHANGE_STATE(_battleChildInit, 0);
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   connectIndex �ڑ�����e�@��Index
 * @retval  none
 */
//==============================================================================

void CommFieldStateConnectBattleChild(int connectIndex)
{
    _pCommFState->connectIndex = connectIndex;
    _CHANGE_STATE(_battleChildConnecting, 0);
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�ċN������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateRebootBattleChild(void)
{
    _CHANGE_STATE(_battleChildReTry, 0);
}

//==============================================================================
/**
 * �o�g�����Ɉړ��ł��镔���ɓ��鎞�̏���
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleRoom(FIELDSYS_WORK* pFSys)
{
    OHNO_PRINT("�����ɓ�����\n");
    WIPE_SetWndMask(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
    WIPE_SetWndMask(WIPE_DISP_SUB,WIPE_FADE_BLACK);
    CommStateSetErrorCheck(TRUE,TRUE);

    if(!CommStateIsInitialize()){  // �ʐM��ԂŖ����Ȃ�I���
        return;
    }
    if(_pCommFState==NULL){// �����ĂȂ��ꍇ���삳����
        _commStateInitialize(pFSys);
        _pCommFState->bReturnBattle = TRUE;
    }
    else{
        _pCommFState->bReturnBattle = FALSE;
    }
    _pCommFState->bBattleMoveRoom = FALSE;

    {  // �g���[�i�[�J�[�h�̃f�[�^����
        int i,id = CommGetCurrentID();
        MYSTATUS *my_st = CommInfoGetMyStatus(CommGetCurrentID());
        for(i = 0; i < CommGetConnectNum(); i++){
            if(_pCommFState->pTRCard[i]==NULL){
                _pCommFState->pTRCard[i] = sys_AllocMemory(HEAPID_BASE_SYSTEM,sizeof(TR_CARD_DATA));
            }
        }
        TRCSET_MakeTrainerInfo( BADGE_BRUSH_OFF, TIME_UPDATE_OFF, GYM_READER_MASK_NONE, UNION_TR_NONE,
//                                UnionView_GetTrainerInfo( MyStatus_GetMySex(my_st),
//                                                          MyStatus_GetTrainerView(my_st), UNIONVIEW_ICONINDEX ),
                                _pCommFState->pFSys,
                                _pCommFState->pTRCard[id] );
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_TR);
    _CHANGE_STATE(_trCardCopyStart, 0);
}

//==============================================================================
/**
 * �f�[�^�R�s�[���I��������ǂ���
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommFieldStateIsCopyEnd(void)
{
    if(_pCommFState->state == _trCardCopyStart){
        return FALSE;
    }
    if(_pCommFState->state == _trCardCopyEnd){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 * �o�g�����̒ʐM�����I���葱��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateExitBattle(void)
{
    if(_pCommFState==NULL){
        return;      // ���łɏI�����Ă���ꍇ�͏��O
    }
    CommStateSetErrorCheck(FALSE,FALSE);
    _CHANGE_STATE(_directEndNoTiming, _EXIT_SENDING_TIME);
}


//==============================================================================
/**
 * �o�g�����̒ʐM�����I���葱��  �Ō�ɓ���������ďI��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateExitBattleTiming(void)
{
    if(_pCommFState==NULL){
        return;      // ���łɏI�����Ă���ꍇ�͏��O
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_EXIT2);
    _CHANGE_STATE(_directEndTiming, _EXIT_SENDING_TIME);
}




//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏���
 * @param
 * @retval  none
 */
//==============================================================================

void _commCheckFunc(TCB_PTR tcb, void* work)
{
#ifdef PM_DEBUG
    _pCommFState->debugTimer++;
#endif

    if(_pCommFState==NULL){
        TCB_Delete(tcb);
    }
    else{
        if(_pCommFState->state != NULL){
            PTRStateFunc state = _pCommFState->state;
            if(!_pCommFState->bStateNoChange){
                state();
            }
        }
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
    _pCommFState->state = state;
    _pCommFState->timer = time;
}

#ifdef PM_DEBUG
static void _changeStateDebug(PTRStateFunc state, int time, int line)
{
    OHNO_PRINT("CF field_state: %d %d\n",line, CommGetCurrentID());
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
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(!CommIsInitialize()){
        return;  //
    }
//    if(!CommGetAloneMode()){   // alone���[�h�̏ꍇ
//        return;
//    }    
    CommUnderOptionReInit(_pCommFState->pFSys);  // �n���T�[�r�X�ēx������

    // �������g�ɂ������񑗂�
    CommInfoSendPokeData();
    CommPlayerSendPos(FALSE);
    CommTrapInfoChildSendStart();  //Trap���������g�ɑ��M�J�n
    CommSecretBaseInfoChildSendStart(); // �����̔閧��n�f�[�^�����̐e���ɑ��M�J�n

    if(!SysFlag_UgFirstCheck(SaveData_GetEventWork(_pCommFState->pFSys->savedata))){
        // �Ђ傤���悤�X�e�[�g
        _CHANGE_STATE(_underOpenning, 0);
    }
    else{
        CommPlayerFirstMoveEnable();
        _CHANGE_STATE(_underConnecttingAloneSend, _CHILD_P_SEARCH_TIME*2);
    }
}

//==============================================================================
/**
 * openiing���I���܂łȂɂ����Ȃ�  �Ȃ���Ȃ��悤�ɂ����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underOpenning(void)
{
    if(!SysFlag_UgFirstCheck(SaveData_GetEventWork(_pCommFState->pFSys->savedata))){
        return;
    }
    CommStateUnderRestart();
    CommPlayerFirstMoveEnable();
    
    _CHANGE_STATE(_underConnectting, _CHILD_P_SEARCH_TIME*2);
}



//==============================================================================
/**
 * �����Ŏ����Ƀf�[�^�𑗐M���I���܂ő҂�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underConnecttingAloneSend(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    _CHANGE_STATE(_underConnectting, _CHILD_P_SEARCH_TIME*2);
}

//==============================================================================
/**
 * �l�b�g���[�N���Ȃ���܂őҋ@
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underConnectting(void)
{
    CommUnderProcess();

    CommPlayerFirstMoveEnable();
    
    if(CommIsUnderGroundConnectingState()){  // �ڑ�����܂ŌĂё�����
        if(CommGetCurrentID() == COMM_PARENT_ID){
            OHNO_PRINT("�e�ɂȂ���\n");
            CommSecretBaseInfoParentDel();

            _CHANGE_STATE(_underParentWait, 60);
        }
        else{
            OHNO_PRINT("�q�ɂȂ���\n");
            _CHANGE_STATE(_underChildConnecting, 120);
        }
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
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }

    if(CommMPParentDisconnect() || CommIsError() || (_pCommFState->timer==0) ){
        CommStateUnderRestart();
        _CHANGE_STATE(_underChildRestart, 0);  // �q�@�ɂȂ�O�ɃG���[�ɂȂ���
    }
    else if(CommIsConnect(CommGetCurrentID())){   // �������g���ڑ����Ă��邱�Ƃ��m�F�ł�����
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
            if(CommGetSendRestSize() != COMM_COMMAND_SEND_SIZE_MAX){  // ��ɂȂ�܂ő҂� �^�C�}�[��
                return;
            }
        }
        UgMgrForceExitNowTCB();
        CommPlayerMyDataCopy( COMM_PARENT_ID );  // �e�f�[�^���玩���������Ă���
        CommTrapRecvForceEnd(COMM_PARENT_ID,0,NULL,NULL);  // 㩂��~�߂�
        UgTrapForceExit(COMM_PARENT_ID,TRUE);
        CommInfoDeletePlayer(COMM_PARENT_ID);   // �������e�������̂ł��������
        CommPlayerDestroy( COMM_PARENT_ID, FALSE, FALSE );
//        CommPlayerSendPos(FALSE);
        //_debugTimerDisp("�q�@�ڑ�----!!!-----");
        OHNO_PRINT("�q�@�ɂȂ��� %d \n",CommGetCurrentID());
        CommPlayerFirstMoveDisable();
        _CHANGE_STATE(_underChildConnectInfoWait, 10);
        return;
    }
//    _pCommFState->timer--;
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
    CommUnderProcess();

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }

    if(CommIsChildsConnecting() || (_pCommFState->timer==0)){
        // �����ȊO���Ȃ�������e�@�Œ�
        // �������͎q�@���ؒf���Ă��܂����ꍇ�̃^�C���A�E�g�G���[�I�Ɉړ�
        if(UgMgrForceExitNowTCB()){
            CommPlayerHoldEnd();
        }
        _debugTimerDisp("�e�@�ڑ�");
//        CommInfoSendPokeData();
        CommPlayerSendPos(FALSE);
//        CommTrapInfoChildSendStart();  //Trap���������g�ɑ��M�J�n
        CommPlayerNowFlagSend();
        CommSecretBaseInfoChildSendStart(); // �����̔閧��n�f�[�^�����̐e���ɑ��M�J�n
//        UgDigFossilPlayerInit();
        UgInitialDataSend();   // ���΁{�G�X�P�[�v�ꏊ�𑗐M
        _CHANGE_STATE(_underParentConnect, 0);
        return;
    }

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
    CommUnderProcess();

    // �S���ڑ����؂ꂽ�珄��ɖ߂邪�C�x���g���͋֎~
//    if((_pCommFState->pFSys->event != NULL) || UgSecretBaseIsMoveTickets()){  // �n���ړ��C�x���g���ɃX�e�[�g��ς���̂͋֎~
    if(_pCommFState->pFSys->event != NULL){  // �n���ړ��C�x���g���ɃX�e�[�g��ς���̂͋֎~
        return;
    }

    if(CommIsError() || !CommMPIsChildsConnecting() || ((!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode())) ){

        OHNO_PRINT("�Ȃ����q�@���ؒf���� %d %d\n",CommIsError(),CommMPIsChildsConnecting());
        
        // �閧��n����߂�E�C���h�E���o�Ă���Ɛe�@�̈ړ��t���O�������Ă���̂ł����Ń��Z�b�g
        UgSecretBaseResetPlayer(COMM_PARENT_ID); // �C�x���g�������ĂȂ��Ȃ烊�Z�b�g

        CommPlayerParentFlagDataReset();
        UgSecretBaseErrorMoveTickets();
        CommSendFixData(CF_TRAP_END_FORCE);    // �T�[�o�[������������
        UgTrapForceExit(CommGetCurrentID(),TRUE);
        UgMgrForceExitNowTCB();
        CommStateUnderParentRestart();
#if T1645_060815_FIX
        _CHANGE_STATE(_underParentRestartAloneWait, 0);
#else
        _CHANGE_STATE(_underParentRestart, 1);
#endif
    }
}

//==============================================================================
/**
 * �e�@�Ƃ��Đڑ���   �閧��n�ւ̈ړ��J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect_JumpFieldStart(void)
{
    //CommSecretBaseInfoReset();
    //CommTrapInfoReset();
    CommPlayerManagerReset();
    _CHANGE_STATE(_underParentConnect_JumpField, 0);
}

//==============================================================================
/**
 * �e�@�Ƃ��Đڑ���   �閧��n�ւ̈ړ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect_JumpField(void)
{
    CommUnderProcess();
}

//==============================================================================
/**
 * �e�@�Ƃ��Đڑ���   �閧��n�ւ̈ړ��I���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
    //CommSecretBaseInfoReboot();
    //CommTrapInfoReboot();
    CommPlayerManagerReboot();

#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    _CHANGE_STATE(_underParentConnect, 0);
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ��������Ă��ā@info�f�[�^���W�߂Ă���Ƃ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectInfoWait(void)
{
    if(_pCommFState->timer == 9){
        CommInfoSendPokeData();  //info�f�[�^�𑗂�
        UgInitialDataSend();   // ���΁{�G�X�P�[�v�ꏊ�𑗐M
    }
    if(_pCommFState->timer == 1){
        //UgDigFossilPlayerInit();// ���Ό@���Ă邩�ǂ����𑗂�
        CommPlayerSendPosServer(FALSE);  //�e�X�g
    }
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommInfoIsInfoCollected()){
        _debugTimerDisp("info�f�[�^��M����");
        CommPlayerNowFlagSend();
        _CHANGE_STATE(_underChildConnectFlagWait,200);
        return;
    }
    _underChildConnect();
}


//==============================================================================
/**
 * �q�@�Ƃ��Đڑ��������Ă��ā@�n�^�f�[�^�𑗂鏊
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectFlagWait(void)
{
    if(CommPlayerIsNowFlagDataEnd()){
        CommTrapInfoChildSendStart();  // 㩏�񑗐M
        _CHANGE_STATE(_underChildConnectSecret,0);
    }
    else{
        _underChildConnect();
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
        }
        else{
            // �^�C���A�E�g�ɂ��ؒf
            OHNO_PRINT("�����Ƃ��ĂȂ�\n");
            _underChildRebootFunc();
        }
    }
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ�  㩑��M����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectSecret(void)
{
    if(CommTrapInfoIsParentRecv()){
        _debugTimerDisp("�e�@㩃f�[�^�͂����炵��");
        CommTrapInfoResetParentRecv();
        CommSecretBaseInfoChildSendStart(); // �q�@�̔閧��n�f�[�^���M�J�n
        _CHANGE_STATE(_underChildConnectDig,0);
        return;
    }
    _underChildConnect();
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ� �閧��n���M����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectDig(void)
{
    if(CommSecretBaseInfoIsPosRecv()){
        _debugTimerDisp("�閧��n�̈ʒu������");
        CommSecretBaseResetPosRecv();
     //   CommPlayerSetMoveControl(TRUE);
        CommPlayerSendPos(TRUE);  // �L�������o���ׂɂ�����񑗂�@�e�X�g��
        CommSendFixData(CF_PLAYER_INIT_END);  // �����������𑗐M
        _CHANGE_STATE(_underChildConnect,0);
        return;
    }
    _underChildConnect();
}

#if T1645_060815_FIX

//==============================================================================
/**
 * �e�@�Ƃ��Đؒf������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentRestartAloneWait(void)
{
    if(!CommGetAloneMode()){
        OHNO_PRINT("s wait\n");
        return;
    }
    _CHANGE_STATE(_underParentRestart,10);
}

//==============================================================================
/**
 * �e�@�Ƃ��Đؒf������̂�҂�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentRestart(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        if(!CommIsEmptyQueue()){
            OHNO_PRINT("not e\n");
            return;
        }
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){  // �e�ɂȂ���
        OHNO_PRINT("�ăX�^�[�g\n");
        _CHANGE_STATE(_underStart, 0);
    }
}

#else

//==============================================================================
/**
 * �e�@�Ƃ��Đؒf������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentRestart(void)
{
//    if(CommIsUnderResetState()){
  //      return;
 //   }
//    if(!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode()){
    if(!CommGetAloneMode()){
        OHNO_PRINT("s wait\n");
        return;
    }
    if(!CommIsEmptyQueue()){
        OHNO_PRINT("not e\n");
        return;
    }
    
    if(CommGetCurrentID() == COMM_PARENT_ID){  // �e�ɂȂ���
        OHNO_PRINT("�ăX�^�[�g\n");
        _CHANGE_STATE(_underStart, 0);
    }
}

#endif //T1645_060815_FIX

//==============================================================================
/**
 * �q�@�Ƃ��Đؒf������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildRestart(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){  // �e�ɂȂ���
        OHNO_PRINT("�ăX�^�[�g\n");
        _CHANGE_STATE(_underStart, 0);
    }
}

static void _underChildRestart_Base(void)
{
    if(_pCommFState->pFSys->event == NULL ){  // �n���ړ��C�x���g�I��
        CommStateUnderRestart();  // �n���̒ʐM��e�q�؂�ւ���
        _CHANGE_STATE(_underChildRestart, 0);
    }
}



static void _underChildStalthDeadLoop(void)
{
    CommUnderProcess();
}

static void _underChildStalth(void)
{
    if(CommGetCurrentID() == COMM_PARENT_ID){
//        CommUnderOptionInitialize(_pCommFState->pFSys);  // �n���T�[�r�X�̋N��

        CommUnderOptionReInit(_pCommFState->pFSys);  // �n���T�[�r�X�ēx������

        // �������g�ɂ������񑗂�
        CommInfoSendPokeData();
        CommPlayerSendPos(FALSE);
        CommTrapInfoChildSendStart();  //Trap���������g�ɑ��M�J�n
        CommSecretBaseInfoChildSendStart(); // �����̔閧��n�f�[�^�����̐e���ɑ��M�J�n
        _CHANGE_STATE(_underChildStalthDeadLoop, 0);
    }
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ�����
 * @param   none
 * @retval  none
 */
//==============================================================================



//==============================================================================
/**
 * �q�@�Ƃ��Đڑ�����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildRebootFunc(void)
{
    UgTrapForceExit(CommGetCurrentID(),TRUE);
    if(UgSecretBaseRemovePlayer_Client(CommGetCurrentID(),TRUE)){
        CommPlayerManagerStop();  // �ړ���~
        UgMgrForceExitNowTCB();   // �o�^�C�x���g���I��������
        CommStateUnderRestart();  // �n���̒ʐM��e�q�؂�ւ���
        CommPlayerFlagChange();   // �����̃n�^��}���ւ���
        _CHANGE_STATE(_underChildRestart, 0);//
    }
    else{
        OHNO_PRINT("�ؒf�ċN�� %d\n",CommGetCurrentID());
        CommPlayerManagerStop();  // �ړ���~
        UgMgrForceExitNowTCB();   // �o�^�C�x���g���I��������
        CommStateUnderRestart();  // �n���̒ʐM��e�q�؂�ւ���
        CommPlayerFlagChange();   // �����̃n�^��}���ւ���
        _CHANGE_STATE(_underChildRestart, 0);
    }
}


static void _underChildConnect(void)
{
    CommUnderProcess();

    CommPlayerFirstMoveEnable();
    
    // �e�@�����Ȃ��Ȃ�����I�����������ĕʐe��T���ɂ���
    if(_pCommFState->pFSys->event != NULL ){  // �n���ړ��C�x���g���ɃX�e�[�g��ς���̂͋֎~
        return;
    }
    if(CommMPParentDisconnect() || CommIsError()){
        _underChildRebootFunc();  // �ċN��
    }
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnect_JumpFieldStart(void)
{
    //CommSecretBaseInfoReset();
    //CommTrapInfoReset();
    CommPlayerManagerReset();
    _CHANGE_STATE(_underChildConnect_JumpField,0);
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnect_JumpField(void)
{
    // �o���邾���������Ȃ�
    UgSecretBaseErrorDisconnectTickets();
}

//==============================================================================
/**
 * �q�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
 //   CommSecretBaseInfoReboot();
//    CommTrapInfoReboot();
    CommPlayerManagerReboot();
#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif

    if(CommMPParentDisconnect() || CommIsError()){
        OHNO_PRINT("�ؒf�ċN�� %d\n",CommGetCurrentID());
        
        CommSecretBaseInfoReInit();  // 
        CommPlayerManagerStop();  // �ړ���~
        UgMgrForceExitNowTCB();   // �o�^�C�x���g���I��������
        CommStateUnderRestart();  // �n���̒ʐM��e�q�؂�ւ���
        CommPlayerFlagChange();   // �����̃n�^��}���ւ���
        _CHANGE_STATE(_underChildRestart, 0);
    }
    else{
        _CHANGE_STATE(_underChildConnect, 0);
    }
}



//==============================================================================
/**
 * solo�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underSoloConnect_JumpFieldStart(void)
{
    CommPlayerManagerReset();
    _CHANGE_STATE(_underSoloConnect_JumpField,0);
}

//==============================================================================
/**
 * solo�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underSoloConnect_JumpField(void)
{
}

//==============================================================================
/**
 * solo�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underSoloConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
    CommPlayerManagerReboot();
#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    _CHANGE_STATE(_underConnectting, 0);
}

//==============================================================================
/**
 * stalth�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthConnect_JumpFieldStart(void)
{
    CommPlayerManagerDeletePlayers();
    _CHANGE_STATE(_underStalthConnect_JumpField,0);
}

//==============================================================================
/**
 * stalth�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthConnect_JumpField(void)
{
}

//==============================================================================
/**
 * solo�@�Ƃ��Đڑ����@�@�@JUMP����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
    CommPlayerManagerReboot();
#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    _CHANGE_STATE(_underChildStalthDeadLoop, 0);
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
    if(!CommIsConnect(CommGetCurrentID())){
//    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommChildListWindowOpen();
    CommInfoSendPokeData();
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
  //  if(CommGetCurrentID() == COMM_PARENT_ID){
    //    CommInfoSendArray_ServerSide();  // �q�@����₢���킹����������info�𑗐M
   // }
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
    
    CommParentSelectParentWindowOpen();
    _CHANGE_STATE(_battleChildBconScanning, 0);
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
//    CommParentBconCheck();
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
    CommStateConnectBattleChild(_pCommFState->connectIndex);
    _CHANGE_STATE(_battleChildSendName, 0);
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
    if(!CommIsBattleConnectingState()){
        return;
    }
    CommInfoSendPokeData();
    _CHANGE_STATE(_battleChildWaiting, 0);
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
    //Exit���󂯎������q�@�ؒf
}



//==============================================================================
/**
 * �q�@enter���  �ړ����[�����ɖ߂��Ă���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomReturn(void)
{
    void* pWork;
    if(CommIsTimingSync(DBC_TIM_BATTLE_DSEND)){
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommPlayerGetWorkSize());
        CommPlayerManagerInitialize(pWork, _pCommFState->pFSys, FALSE);
        CommPlayerFirstMoveEnable();
        CommDisableSendMoveData();  // �ړ��֎~
        CommTimingSyncStart(DBC_TIM_BATTLE_PAUSE);
        _CHANGE_STATE(_battleMoveRoomReturn2, 0);
        return;
    }
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }
    else{
        _pCommFState->timer=30;
        CommTimingSyncStart(DBC_TIM_BATTLE_DSEND);
    }
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomReturn2(void)
{
    if(CommGetCurrentID() == COMM_PARENT_ID){
        CommInfoSendArray_ServerSide();  // �q�@����₢���킹����������info�𑗐M
    }
    if(CommIsTimingSync(DBC_TIM_BATTLE_PAUSE)){
        
        WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
            WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );

        WIPE_ResetWndMask(WIPE_DISP_MAIN);
        WIPE_ResetWndMask(WIPE_DISP_SUB);

        CommPlayerManagerReboot();
        CommPlayerSendPos(FALSE);
        _CHANGE_STATE(_battleMoveRoomReturn3,1);
    }
}

static void _battleMoveRoomReturn4(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommIsTimingSync(DBC_TIM_BATTLE_BACK)){
        CommEnableSendMoveData();  // �ړ�OK
        _CHANGE_STATE(_battleMoveRoomWait,0);
    }
}


static void _battleMoveRoomReturn3(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){
        if(FALSE == CommPlayerMoveBattlePos()){
            return;
        }
        CommTimingSyncStart(DBC_TIM_BATTLE_BACK);
    }
    else{
        CommTimingSyncStart(DBC_TIM_BATTLE_BACK);
    }
    _CHANGE_STATE(_battleMoveRoomReturn4,20);
}


//==============================================================================
/**
 * �q�@enter���  �ړ����[�����ɂ͂����Ă���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnter(void)
{
    void* pWork;

    if(CommIsTimingSync(DBC_TIM_BATTLE_DSEND)){
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommPlayerGetWorkSize());
        CommPlayerManagerInitialize(pWork, _pCommFState->pFSys, FALSE);
        CommPlayerFirstMoveEnable();
        CommTimingSyncStart(DBC_TIM_BATTLE_PAUSE);
        _CHANGE_STATE(_battleMoveRoomEnter2, 0);
        return;
    }

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }
    else{
        _pCommFState->timer=30;
        CommTimingSyncStart(DBC_TIM_BATTLE_DSEND);
    }
    
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnter2(void)
{
    if(CommGetCurrentID() == COMM_PARENT_ID){
        CommInfoSendArray_ServerSide();  // �q�@����₢���킹����������info�𑗐M
    }
    if(CommIsTimingSync(DBC_TIM_BATTLE_PAUSE)){
        CommPlayerManagerReboot();
        CommPlayerSendPos(FALSE);
        {
            u8 bit = TRUE;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }

        WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
            WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
        WIPE_ResetWndMask(WIPE_DISP_MAIN);
        WIPE_ResetWndMask(WIPE_DISP_SUB);

        _CHANGE_STATE(_battleMoveRoom,0);
    }
}


static void _exitCheck(void)
{
    int i,k;

    for(i = 0;i < CommGetConnectNum();i++){
        if(i != CommGetCurrentID()){
            if(CommGetTimingSyncNo(i) == DBC_TIM_BATTLE_EXIT){
                if(_pCommFState->pFSys->event==NULL){
                    for(k = 0;k < _TRAINER_CARD_NUM_MAX; k++){
                        if(_pCommFState->pTRCard[k]){
                            sys_FreeMemoryEz(_pCommFState->pTRCard[k]);
                            _pCommFState->pTRCard[k]=NULL;
                        }
                    }
                    EventSet_Script( _pCommFState->pFSys, SCRID_BATTLE_ROOM_FORCEEND, NULL );
                }
            }
        }
    }
    CommErrorCheck(HEAPID_FIELD,_pCommFState->pFSys->bgl);
}


//==============================================================================
/**
 *  �ړ����[����  �L�����Z���������A�S������������̃R�[���o�b�N
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomWait(void)
{
    if(!CommPlayerCheckBattleJump()){
        _pCommFState->bBattleMoveRoom = FALSE;
        {
            u8 bit = TRUE;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }
        _CHANGE_STATE(_battleMoveRoom, 0);
    }
    _exitCheck();  // ��ĂɏI�����錟��
}

// �X�^�[�g���C�����̏I���R�[���o�b�N
static void _startLineCallBack(BOOL bStart, const POKEPARTY* party)
{
	if( party )
	{
		_pCommFState->party = PokeParty_AllocPartyWork( HEAPID_WORLD );
		PokeParty_Copy( party, _pCommFState->party );
    }

    if(bStart){
        _CHANGE_STATE(_battleMoveRoomEnd_Tim, 3);
    }
    else{  // ���������Ǔ����ꍇ
        {
            u8 bit = 3;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }
        _CHANGE_STATE(_battleMoveRoomWait, 0);
    }
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
    ��]�����đҋ@�C�x���g�N��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomNop(void)
{
    // �X�^�[�g���C���R�[���o�b�N�̕Ԏ���҂�
    _CHANGE_STATE(_battleMoveRoomWait,0);
}


static void _battleMoveRoomEventSet(void)
{
    if(CommSysIsMoveKey() || (0 != CommPlayerGetWalkCount(CommGetCurrentID()))){
        return;
    }

    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }
    CommPlayerHold();
    EventCmd_StartLine(_pCommFState->pFSys, _startLineCallBack);

    _CHANGE_STATE(_battleMoveRoomNop,0);
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoom(void)
{
    if( _pCommFState->bBattleMoveRoom ){  // �J�n�ʒu�ɂ������Ƃ���M
        _CHANGE_STATE(_battleMoveRoomEventSet, 5);  // �ړ��A�X�^�[�g���C���C�x���g
        {
            u8 bit = FALSE;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }
    }
    _exitCheck();
}

//CF_DIRECT_STARTPOS
void CommDirectRecvStartPos(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    if(pBuff[0] == CommGetCurrentID()){
        _pCommFState->bBattleMoveRoom = TRUE;
    }
}

BOOL CommDirectIsMoveState(void)
{
    if(_pCommFState ){
        if((_pCommFState->state == _battleMoveRoom) ||
           (_pCommFState->state == _battleMoveRoomWait)){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd(void)
{
    BOOL bDSMode = TRUE;
    int type;
    u8 sel[6];

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    type = FIGHT_TYPE_1vs1_SIO;
    switch(CommStateGetServiceNo()){
      case COMM_MODE_BATTLE_MULTI:
      case COMM_MODE_BATTLE_MIX_2ON2:
        type = FIGHT_TYPE_MULTI_SIO;
        break;
      case COMM_MODE_BATTLE_DOUBLE:
        type = FIGHT_TYPE_2vs2_SIO;
        break;
    }
    CommStateGetPokemon(sel);

	if( _pCommFState->party == NULL )
	{
		EventSet_CommDirectBattle(_pCommFState->pFSys,sel, type);
	}
	else
	{
		EventSet_CommDirectMixBattle( _pCommFState->pFSys, _pCommFState->party, type );
		sys_FreeMemoryEz( _pCommFState->party );
		_pCommFState->party = NULL;
	}

//    EventSet_Script( _pCommFState->pFSys, SCRID_CONNECT_COLOSSEUM_BATTLE_START, NULL );
//    CommPlayerManagerFinalize(FALSE);
//    CommSendFixSizeData(CS_DSMP_CHANGE, &bDSMode);  //�o�g�����[�h�ɕύX����
    _stateFinalize();
}



//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_4(void)
{
    if(CommIsTransmissonDSType()){
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
        }
        if(_pCommFState->timer  == 90){
            CommTimingSyncStart(DBC_TIM_BATTLE_DSOK);
        }
        if(CommIsTimingSync(DBC_TIM_BATTLE_DSOK)){
            _CHANGE_STATE(_battleMoveRoomEnd,0);
        }
    }
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_3(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommSetTransmissonTypeDS();
    _CHANGE_STATE(_battleMoveRoomEnd_4,120);
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_2(void)
{
    BOOL bDSMode = TRUE;

    if(CommIsTimingSync(DBC_TIM_BATTLE_MPDS)){
//        if(CommGetCurrentID() == COMM_PARENT_ID){
//            CommSendFixSizeData(CS_DSMP_CHANGE, &bDSMode);  //�o�g�����[�h�ɕύX����
//        }
        _CHANGE_STATE(_battleMoveRoomEnd_3,2);
    }
}

//==============================================================================
/**
 * �q�@�ҋ@���  �ړ����[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_Tim(void)
{
    BOOL bDSMode = TRUE;

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommPlayerManagerFinalize(FALSE);
    CommTimingSyncStart(DBC_TIM_BATTLE_MPDS);
    _CHANGE_STATE(_battleMoveRoomEnd_2,0);
}

//==============================================================================
/**
 * �G���[�ɂ��o�g���̋����I��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleQuit(void)
{
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
    CommStateRebootBattleChild();
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
    if(!CommMPIsStateIdle()){  /// �I��������������ƏI����Ă��邱�Ƃ��m�F
        return;
    }
    _CHANGE_STATE(_battleChildSendName, _SEND_NAME_TIME);
}






void CommDCRecvTrainerCard(int netID ,int size, void* pBuff, void* pWork )
{
    OHNO_SP_PRINT("CommDCRecvTrainerCard %d\n",netID);
    _pCommFState->bTRCard[netID] = TRUE;
}

u8* CommDCGetTrainerCardRecvBuff( int netID, void* pWork, int size)
{
    GF_ASSERT_RETURN(netID < _TRAINER_CARD_NUM_MAX,NULL);
    return (u8*)_pCommFState->pTRCard[netID];
}





//==============================================================================
/**
 * �f�[�^�V�F�A�����O���Ƀg���[�i�[�J�[�h���R�s�[������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _trCardCopyStart(void)
{
    int i,id = CommGetCurrentID();

    if(CommIsTimingSync(DBC_TIM_BATTLE_TR)){
        CommSendHugeData(CF_TRAINER_CARD, _pCommFState->pTRCard[id], sizeof(TR_CARD_DATA));
        _CHANGE_STATE(_trCardCopyEnd,0);
    }
}

//==============================================================================
/**
 * �f�[�^�V�F�A�����O���Ƀg���[�i�[�J�[�h���R�s�[������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _trCardCopyEnd(void)
{
    int i;

    for(i = 0; i < CommGetConnectNum(); i++){
        if(!_pCommFState->bTRCard[i]){
            return;
        }
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_DSCHANGE);
    _CHANGE_STATE(_dsChangeTiming,0);
}


static void _dsChangeEndWaitStart_3(void)
{

    if(!CommIsTransmissonDSType()){
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
        }
        if(_pCommFState->timer  == 90){
            CommTimingSyncStart(DBC_TIM_BATTLE_MPOK);
        }
        if(CommIsTimingSync(DBC_TIM_BATTLE_MPOK)){
            _CHANGE_STATE(_dsChangeEndWaitStart,0);
        }
    }


}


static void _dsChangeEndWaitStart_2(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommSetTransmissonTypeMP();
    _CHANGE_STATE(_dsChangeEndWaitStart_3,120);
}

static void _dsChangeTiming(void)
{
    if(CommIsTimingSync(DBC_TIM_BATTLE_DSCHANGE)){
        _CHANGE_STATE(_dsChangeEndWaitStart_2,2);
    }
}

static void _dsChangeEndWaitStart(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_DSEND);
    if(_pCommFState->bReturnBattle){
        _CHANGE_STATE(_battleMoveRoomReturn, 30);
    }
    else{
        _CHANGE_STATE(_battleMoveRoomEnter, 30);
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
    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }

    CommUnderOptionFinalize();
    CommStateExitUnderGround();

    sys_DeleteHeap(HEAPID_UNDERGROUND);

    _pCommFState->bUGOverlay = FALSE; // �n�����~�߂�

    _stateFinalize();   // state�͂����ŏI�� �ʐM�͌ォ��؂��
}

//==============================================================================
/**
 * @brief  �����I�������J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _directEndTiming(void)
{
    if(CommIsTimingSync(DBC_TIM_BATTLE_EXIT2)){
        CommStateSetErrorCheck(FALSE,FALSE);
        OHNO_PRINT("�I�������������---\n");
        CommPlayerManagerFinalize(TRUE);
        _CHANGE_STATE(_stateConnectAutoEnd, _EXIT_SENDING_TIME);
    }
}

//==============================================================================
/**
 * @brief  �����I�������J�n
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _directEndNoTiming(void)
{
    CommPlayerManagerFinalize(TRUE);
    _CHANGE_STATE(_stateConnectAutoEnd, _EXIT_SENDING_TIME);
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
    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }
//    if(CommIsConnect(CommGetConnectNum())){
//        CommSendFixData(CS_AUTO_EXIT);
  //  }
    //else{
        CommStateExitBattle();
        _CHANGE_STATE(_stateFinalize, 0);
   // }
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
    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }
    // �ؒf����
    CommFinalize();
    _CHANGE_STATE(_stateEnd, 0);
}

#ifdef PM_DEBUG
static void _debugTimerStart(void)
{
    _pCommFState->debugTimer=0;
}

static void _debugTimerDisp(char* msg)
{
    OHNO_PRINT("%s �J�n���� %d sync ������܂���\n", msg, _pCommFState->debugTimer * 2);
}

#endif


#ifdef PM_DEBUG


static BOOL GMEVENT_BattleDebug(GMEVENT_CONTROL * event)
{
    if(CommIsInitialize()){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�ɏ��𑗐M
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildWaiting_Debug(void)
{
    
    OHNO_PRINT("�ڑ������� CommGetConnectNum=%d CommMPGetServiceNo=%d \n",CommGetConnectNum(),CommStateGetServiceNo() );
    if(CommGetConnectNum() == (CommGetMaxEntry(CommStateGetServiceNo()))){
        CommDirectConnect_Debug();
        _CHANGE_STATE(_battleChildWaiting, 0);
    }
}

//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�ɏ��𑗐M
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildSendName_Debug(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(!CommIsConnect(CommGetCurrentID())){
        return;
    }
    CommInfoSendPokeData();
    _CHANGE_STATE(_battleChildWaiting_Debug, 0);
}

//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�ɋ����炢���i�f�o�b�O�j
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildConnecting_Debug(void)
{
    if(CommMPGetGFBss(_pCommFState->connectIndex)!=NULL){
        CommStateConnectBattleChild(_pCommFState->connectIndex);  // �ڑ�
        _CHANGE_STATE(_battleChildSendName_Debug, _SEND_NAME_TIME);
    }
}

//==============================================================================
/**
 * �o�g�����̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   connectIndex �ڑ�����e�@��Index
 * @retval  none
 */
//==============================================================================

void CommFieldStateConnectBattleChild_Debug( FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo, int connectIndex)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
#ifdef PM_DEBUG
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE, SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
#else
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE);
#endif
    _commStateInitialize(pFSys);
    _pCommFState->connectIndex = connectIndex;
    _CHANGE_STATE(_battleChildConnecting_Debug, 0);
}


//==============================================================================
/**
 * �e�@�Ƃ��đҋ@��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentWaiting_Debug(void)
{
    if(CommIsChildsConnecting()){
        OHNO_PRINT("�ڑ������� CommGetConnectNum=%d CommMPGetServiceNo=%d \n",CommGetConnectNum(),CommStateGetServiceNo() );
        if(CommGetConnectNum() == (CommGetMaxEntry(CommStateGetServiceNo()))){
            CommDirectConnect_Debug();
            _CHANGE_STATE(_battleParentWaiting, 0);
        }
    }
}

//==============================================================================
/**
 * �q�@�ҋ@���  �e�@��I��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentSendName_Debug(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(!CommIsConnect(CommGetCurrentID())){
        return;
    }
    CommInfoSendPokeData();
    _CHANGE_STATE(_battleParentWaiting_Debug, 0);
}

//==============================================================================
/**
 * �e�@�Ƃ��ď��������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentInit_Debug(void)
{
    MYSTATUS* pMyStatus;
    
    if(!CommIsVRAMDInitialize()){
        return;
    }
    _CHANGE_STATE(_battleParentSendName_Debug, _SEND_NAME_TIME);
}

//==============================================================================
/**
 * �o�g�����̐e�Ƃ��Ă̒ʐM�����J�n
 * @param   pFSys  �t�B�[���h�\����
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @param   regulationNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleParent_Debug(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo)
{
    if(CommIsInitialize()){
        return;      // �Ȃ����Ă���ꍇ���͏��O����
    }
#ifdef PM_DEBUG
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE,
                               SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
#else
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE);
#endif
    _commStateInitialize(pFSys);
    _CHANGE_STATE(_battleParentInit_Debug, 0);

}

#endif


//==============================================================================
/**
 * @brief   ������Z�b�g�A�b�v����閧��n�O�b�Y�f�[�^��Ԃ�
 * @param   sv  SAVEDATA*
 * @retval  SECRETBASEDATA*
 */
//==============================================================================

SECRETBASEDATA* CommUgSetupSecretBaseData(SAVEDATA * sv)
{
    if(!_pCommFState || !_pCommFState->bUGOverlay){
        return NULL;
    }
    return UgManUgSetupSecretBaseData(sv);
}



BOOL CommFieldStateIsUnder(void)
{
    if(_pCommFState && _pCommFState->bUGOverlay){
        return TRUE;
    }
    return FALSE;
}

void CommStateFieldUnderOptionReset(void)
{
    if(_pCommFState && _pCommFState->bUGOverlay){
       // CommSystemRecvStop(TRUE);
    //    OHNO_PRINT("�ʐM�~�߂܂���\n");
        CommUnderOptionReset();
    }
}

void CommStateFieldUnderOptionReboot(void)
{
    if(_pCommFState && _pCommFState->bUGOverlay){
        CommUnderOptionReboot();
   //    OHNO_PRINT("�ʐM�����܂���\n");
       // CommSystemRecvStop(FALSE);
    }
}

