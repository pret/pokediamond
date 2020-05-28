//=============================================================================
/**
 * @file	comm_command.c
 * @brief	�f�[�^�𑗂邽�߂̃R�}���h���e�[�u�������Ă��܂�
 *          ���M���������e������ꍇ�A�����ɒǉ����Ă������ƂɂȂ�܂�
 *          comm_command.h �� enum �Ɠ������тł���K�v������܂�
 * @author	Katsumi Ohno
 * @date    2005.07.26
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"

#include "system/mystatus.h"

//==============================================================================
//  static��`
//==============================================================================
static void _commCommandRecvThrowOut(int netID, int size, void* pData, void* pWork);
static void _commCommandRecvThrowOutReq(int netID, int size, void* pData, void* pWork);
static void _commCommandRecvThrowOutEnd(int netID, int size, void* pData, void* pWork);
static int _getTwo(void);

// field/d_ohno.h�ɂ���f�o�b�O�p
extern void CommDebugRecvHugeData(int netID, int size, void* pData, void* pWork);


//==============================================================================
//	�e�[�u���錾
//  comm_shar.h �� enum �Ɠ����Ȃ�тɂ��Ă�������
//  CALLBACK���Ă΂ꂽ���Ȃ��ꍇ��NULL�������Ă�������
//  �R�}���h�̃T�C�Y��Ԃ��֐��������Ă��炦��ƒʐM���y���Ȃ�܂�
//  _getZero�̓T�C�Y�Ȃ���Ԃ��܂��B_getVariable�͉σf�[�^�g�p���Ɏg���܂�
//==============================================================================
static const CommPacketTbl _CommPacketTbl[] = {
    {NULL, _getZero, NULL},
    {NULL, _getZero, NULL},
    {CommRecvAutoExit, _getZero, NULL},
    {CommInfoRecvPlayerData, CommInfoGetPlayerDataSize, NULL},
    {CommInfoRecvArrayPlayerData, CommInfoGetPlayerDataSize, NULL},
    {CommInfoRecvEnd, _getZero, NULL},
    {CommRecvNegotiation, CommRecvGetNegotiationSize, NULL},
    {CommRecvNegotiationReturn, CommRecvGetNegotiationSize, NULL},
#ifdef PM_DEBUG
    {CommDebugRecvHugeData, _getVariable, NULL},
    {CommStateRecvDebugStart, _getZero, NULL},
#else
    {NULL, NULL, NULL},
    {NULL, NULL, NULL},
#endif
    {CommRecvDSMPChange, _getOne, NULL},
    {CommRecvDSMPChangeReq, _getOne, NULL},
    {CommRecvDSMPChangeEnd, _getOne, NULL},
    {_commCommandRecvThrowOut, _getZero, NULL},
    {_commCommandRecvThrowOutReq, _getZero, NULL},
    {_commCommandRecvThrowOutEnd, _getZero, NULL},
    {CommRecvTimingSync, _getOne, NULL},
    {CommRecvTimingSyncEnd, _getOne, NULL},
    {CommRecvTimingSyncInfo, _getTwo, NULL},
    {CommRecvListNo, CommGetListNoSize, NULL},
    {CommToolRecvTempData, CommToolGetTempDataSize, NULL},
    {CommRecvExit, _getZero, NULL},
};

typedef struct{
    const CommPacketTbl* pCommPacket;  ///< field��battle�̃R�}���h�̃e�[�u��
    int listNum;                       ///< _pCommPacket��list��
    void* pWork;                       ///< field��battle�̃��C���ɂȂ郏�[�N
    u8 bThrowOutReq[COMM_MACHINE_MAX];        ///< �R�}���h�������������t���O
    u8 bThrowOuted;    ///< �R�}���h����ւ����I��������TRUE
} _COMM_COMMAND_WORK;

static _COMM_COMMAND_WORK* _pCommandWork = NULL;


//--------------------------------------------------------------
/**
 * @brief   �R�}���h�e�[�u���̏�����
 * @param   pCommPacketLocal �Ăяo�����W���[����p�̃R�}���h�̌n
 * @param   listNum          �R�}���h��
 * @param   pWork            �Ăяo�����W���[����p�̃��[�N�G���A
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandInitialize(const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork)
{
    int i;
    
    if(!_pCommandWork){
        _pCommandWork = sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_COMMAND_WORK));
    }
    _pCommandWork->pCommPacket = pCommPacketLocal;
    _pCommandWork->listNum = listNum;
    _pCommandWork->pWork = pWork;


    for(i = 0 ; i < COMM_MACHINE_MAX; i++){
        _pCommandWork->bThrowOutReq[i] = FALSE;
    }
    _pCommandWork->bThrowOuted = FALSE;


}

//--------------------------------------------------------------
/**
 * @brief   �R�}���h�e�[�u���̏I������
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandFinalize( void )
{
    if(_pCommandWork){
        sys_FreeMemoryEz(_pCommandWork);
        _pCommandWork = NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief   �e�[�u���ɏ]�� ��M�R�[���o�b�N���Ăяo���܂�
 * @param   command         ��M�R�}���h
 * @param   netID           �l�b�g���[�NID
 * @param   size            ��M�f�[�^�T�C�Y
 * @param   pData           ��M�f�[�^
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandCallBack(int netID, int command, int size, void* pData)
{
    PTRCommRecvFunc func;

    if( command < CS_COMMAND_MAX ){
        func = _CommPacketTbl[command].callbackFunc;
    }
    else{
        GF_ASSERT_RETURN(_pCommandWork,);
        if(command > (_pCommandWork->listNum + CS_COMMAND_MAX)){
#ifdef DEBUG_ONLY_FOR_ohno
            OHNO_PRINT("command %d \n", command);
            GF_ASSERT(0 && "���݂��Ȃ��ʐM�R�}���h");
#endif
            CommSetError();
            return;  // �{�Ԃł̓R�}���h�Ȃ�����
        }
        func = _pCommandWork->pCommPacket[command - CS_COMMAND_MAX].callbackFunc;
    }
    if(func != NULL){
        if(_pCommandWork){
            func(netID, size, pData, _pCommandWork->pWork);
        }
        else{
            func(netID, size, pData, NULL);
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief   ��`���������R�}���h�̃T�C�Y��Ԃ��܂�
 * @param   command         �R�}���h
 * @retval  �f�[�^�̃T�C�Y   �ςȂ� COMM_VARIABLE_SIZE��Ԃ��܂�
 */
//--------------------------------------------------------------

int CommCommandGetPacketSize(int command)
{
    int size = 0;
    PTRCommRecvSizeFunc func;

    if( command < CS_COMMAND_MAX ){
        func = _CommPacketTbl[command].getSizeFunc;
    }
    else{
        GF_ASSERT(_pCommandWork);
        if(_pCommandWork==NULL){
            CommSetError();
            return size;  // �{�Ԃł̓G���[
        }
        if(command > (_pCommandWork->listNum + CS_COMMAND_MAX)){
#ifdef DEBUG_ONLY_FOR_ohno
            GF_ASSERT_MSG(0,"command %d ",command);
#endif
            CommSetError();
            return size;  // �{�Ԃł̓G���[
        }
        func = _pCommandWork->pCommPacket[command - CS_COMMAND_MAX].getSizeFunc;
    }
    if(func != NULL){
        size = func();
    }
    return size;
}

//--------------------------------------------------------------
/**
 * @brief   ��M�o�b�t�@�������Ă��邩�ǂ����̌���
 * @param   command         �R�}���h
 * @retval  �����Ă�Ȃ�TRUE
 */
//--------------------------------------------------------------

BOOL CommCommandCreateBuffCheck(int command)
{
    if( command < CS_COMMAND_MAX ){
        return ( _CommPacketTbl[command].getAddrFunc != NULL);
    }
    return (_pCommandWork->pCommPacket[command - CS_COMMAND_MAX].getAddrFunc != NULL);
}

//--------------------------------------------------------------
/**
 * @brief   
 * @param   command         �R�}���h
 * @retval  �����Ă�Ȃ�TRUE
 */
//--------------------------------------------------------------

void* CommCommandCreateBuffStart(int command,int netID, int size)
{
    PTRCommRecvBuffAddr func;

    if( command < CS_COMMAND_MAX ){
        func = _CommPacketTbl[command].getAddrFunc;
        return func(netID, NULL, size);
    }
    else{
        func = _pCommandWork->pCommPacket[command - CS_COMMAND_MAX].getAddrFunc;
        return func(netID, _pCommandWork->pWork, size);
    }
    return NULL;
}


//--------------------------------------------------------------
/**
 * @brief   �R�Ƃ��T�C�Y��Ԃ��܂�
 * @param   command         �R�}���h
 * @retval  �T�C�Y   �ςȂ� COMM_VARIABLE_SIZE Zero�͂O��Ԃ�
 */
//--------------------------------------------------------------
int _getVariable(void)
{
    return COMM_VARIABLE_SIZE;
}

int _getZero(void)
{
    return 0;
}

int _getOne(void)
{
    return 1;
}

static int _getTwo(void)
{
    return 2;
}


//--------------------------------------------------------------
/**
 * @brief   �R�}���h�e�[�u���̔p��
 * @param   none
 * @retval  ��t����������TRUE
 */
//--------------------------------------------------------------

BOOL CommCommandThrowOut(void)
{
    GF_ASSERT_RETURN(_pCommandWork, TRUE);

    _pCommandWork->bThrowOuted = FALSE;
    return CommSendFixData(CS_COMMAND_THROWOUT);
}


//==============================================================================
/**
 * �R�}���h�p���R�[���o�b�N
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandRecvThrowOut(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
//    OHNO_PRINT("CommRecvDSMPChange ��M\n");
    // �S���ɐ؂�ւ��M���𑗂�
    _pCommandWork->bThrowOutReq[netID] = TRUE;
    for(i = 0 ; i < COMM_MACHINE_MAX; i++){
        if(!CommIsConnect(i)){
            continue;
        }
        if(!_pCommandWork->bThrowOutReq[i]){
            return;
        }
    }
    CommSendData_ServerSide(CS_COMMAND_THROWOUT_REQ, NULL, 0);
}

//==============================================================================
/**
 * �R�}���h�p�����s�R�[���o�b�N
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandRecvThrowOutReq(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    _pCommandWork->pCommPacket = NULL;
    _pCommandWork->listNum = 0;
    _pCommandWork->pWork = NULL;
    _pCommandWork->bThrowOuted = TRUE;

    CommSendFixSizeData(CS_COMMAND_THROWOUT_END,pData);
}

//==============================================================================
/**
 * �R�}���h�p�������R�[���o�b�N
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandRecvThrowOutEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
    _pCommandWork->bThrowOutReq[netID] = FALSE;
}

//==============================================================================
/**
 * �R�}���h�����ł������ǂ������m�F����
 * @param   none
 * @retval  ��������������TRUE
 */
//==============================================================================

BOOL CommCommandIsThrowOuted(void)
{
    if(_pCommandWork){
        return _pCommandWork->bThrowOuted;
    }
    return FALSE;
}

