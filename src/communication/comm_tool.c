//=============================================================================
/**
 * @file	comm_tool.c
 * @brief	�ʐM���g�����ėp�֐�
 * @author	Katsumi Ohno
 * @date    2006.03.14
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "system/snd_tool.h"


//�ėp�f�[�^�̂P�p�P�b�g
#define _TEMPDATA_SIZE (70)

//==============================================================================
// static�錾
//==============================================================================

typedef struct _COMM_TOOL_WORK_t COMM_TOOL_WORK;


typedef struct{
    u8 no;
    u8 listNo;
}_ListResult;

typedef struct _COMM_TOOL_WORK_t{
    // ���X�g
    _ListResult listNo[COMM_MACHINE_MAX];     // �����R�}���h�p
    u8 timingSync[COMM_MACHINE_MAX];     // �����R�}���h�p
    //------------------  temp�f�[�^�p�o�b�t�@
    u8 tempWork[COMM_MACHINE_MAX][_TEMPDATA_SIZE];
    u8 tempRecv[COMM_MACHINE_MAX];
    //-------------------
    u8 timingSyncEnd;     // �����R�}���h�p
    u8 timingSyncMy;  // ������������NO
    u8 timingSend;
};

static COMM_TOOL_WORK* _pCT = NULL;  ///<�@���[�N�\���̂̃|�C���^


//==============================================================================
/**
 * ������
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommToolInitialize(int heapID)
{
    int i;
    
    if(!_pCT){
        _pCT = sys_AllocMemory(heapID,sizeof(COMM_TOOL_WORK));
        MI_CpuFill8(_pCT,0,sizeof(COMM_TOOL_WORK));
    }


    for(i = 0; i< COMM_MACHINE_MAX;i++){
        _pCT->timingSync[i]=0xff;     // �����R�}���h�p
    }
    _pCT->timingSyncEnd = 0xff;     // �����R�}���h�p
    _pCT->timingSyncMy = 0xff;
    _pCT->timingSend = FALSE;

}

//==============================================================================
/**
 * �J��
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommToolFinalize(void)
{
    sys_FreeMemoryEz(_pCT);
    _pCT = NULL;
}

//==============================================================================
/**
 * �m�F
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

BOOL CommToolIsInitialize(void)
{
    if(_pCT){
        return TRUE;
    }
    return FALSE;
}


//==============================================================================
/**
 * �^�C�~���O�R�}���h����M����   CS_TIMING_SYNC
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommRecvTimingSync(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    u8 syncNo = pBuff[0];
    u8 sendBuff[2];
    int i;

    if(CommGetCurrentID() == COMM_PARENT_ID){
        sendBuff[0] = netID;
        sendBuff[1] = syncNo;
        CommSendFixSizeData_ServerSide(CS_TIMING_SYNC_INFO, &sendBuff);
        OHNO_PRINT("������M %d %d\n",netID,syncNo);
        _pCT->timingSync[netID] = syncNo;     // �����R�}���h�p
        for(i = 0; i < COMM_MACHINE_MAX; i++){
            if(CommIsConnect(i)){
                if(syncNo != _pCT->timingSync[i]){
                    // �������Ă��Ȃ�
                    return;
                }
            }
        }
        CommSendFixSizeData_ServerSide(CS_TIMING_SYNC_END, &syncNo);
    }
}


//==============================================================================
/**
 * �^�C�~���O�R�}���hINFO����M����   CS_TIMING_SYNC_INFO
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommRecvTimingSyncInfo(int netID, int size, void* pData, void* pWork)
{
    // �q�@���󋵂�c���ł���悤�ɃR�}���h�������Ă���
    u8* pBuff = pData;
    
    _pCT->timingSync[pBuff[0]] = pBuff[1];     // �����R�}���h�p
}

//==============================================================================
/**
 * �^�C�~���O�R�}���hEND����M����   CS_TIMING_SYNC_END
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommRecvTimingSyncEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    u8 syncNo = pBuff[0];

    OHNO_PRINT("�S�������R�}���h��M %d %d\n", syncNo);
    _pCT->timingSyncEnd = syncNo;     // �����R�}���h�p
}

//==============================================================================
/**
 * �^�C�~���O�R�}���h�𔭍s����
 * @param   no   �^�C�~���O��肽���ԍ�
 * @retval  none
 */
//==============================================================================

void CommTimingSyncStart(u8 no)
{
    OHNO_PRINT("�R�}���h���s %d \n",no);
    _pCT->timingSyncMy = no;
    _pCT->timingSend = TRUE;
}

//==============================================================================
/**
 * �^�C�~���O�R�}���h�𑗐M
 * @param   no   �^�C�~���O��肽���ԍ�
 * @retval  none
 */
//==============================================================================


#ifdef PM_DEBUG
extern int DebugCommGetNum(int id);
static u8 _keytrg = 0;
#endif

void CommTimingSyncSend(void)
{
    if(_pCT){
        if(_pCT->timingSend){
            if(CommSendFixSizeData(CS_TIMING_SYNC, &_pCT->timingSyncMy)){
                OHNO_PRINT("�R�}���h���M %d \n",_pCT->timingSyncMy);
                _pCT->timingSend = FALSE;
            }
        }

#if 0
//#if (defined(DEBUG_ONLY_FOR_ohno) | defined(DEBUG_ONLY_FOR_tomoya_takahashi) | defined(DEBUG_ONLY_FOR_mituhara))
//#ifdef PM_DEBUG
        {
            if((sys.trg == PAD_BUTTON_B) && (_keytrg==3)){
                _keytrg = 4;
                Snd_SePlay(SEQ_SE_DP_DECIDE);
            }
            else if((sys.trg == PAD_BUTTON_B) && (_keytrg==2)){
                _keytrg = 3;
            }
            else if((sys.trg == PAD_BUTTON_R) && (_keytrg==1)){
                _keytrg = 2;
            }
            else if((sys.trg == PAD_BUTTON_L) && (_keytrg==0)){
                _keytrg = 1;
            }
            else if((sys.trg == PAD_BUTTON_START) && (_keytrg < 4)){
                _keytrg = 0;
            }

            if((sys.trg == PAD_BUTTON_L) && (_keytrg==4)){
                GF_ASSERT_MSG(0, "tim %d %d %d %d %d \n %d %d %d %d %d \n %d %d %d %d %d\n",_pCT->timingSyncMy,
                              _pCT->timingSync[0],_pCT->timingSync[1],
                              _pCT->timingSync[2],_pCT->timingSync[3],
                              DebugCommGetNum(0),DebugCommGetNum(1),DebugCommGetNum(2),
                              DebugCommGetNum(3),DebugCommGetNum(4),DebugCommGetNum(5),
                              DebugCommGetNum(6),DebugCommGetNum(7),
                              DebugCommGetNum(8),DebugCommGetNum(9),DebugCommGetNum(10));
                _keytrg = 0;
            }
        }
#endif
    }

}

//==============================================================================
/**
 * �^�C�~���O�R�}���h���͂������ǂ������m�F����
 * @param   no   �͂��ԍ�
 * @retval  �͂��Ă�����TRUE
 */
//==============================================================================

BOOL CommIsTimingSync(u8 no)
{
    if(_pCT==NULL){
        return TRUE;  // �ʐM���ĂȂ��ꍇ�������Ă���Ƃ݂Ȃ�
    }
    if(_pCT->timingSyncEnd == no){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �^�C�~���O�R�}���h���͂������ǂ������m�F����
 * @param   no   �͂��ԍ�
 * @retval  �͂��Ă�����TRUE
 */
//==============================================================================

int CommGetTimingSyncNo(int netID)
{
    return _pCT->timingSync[netID];
}

//------------------------------------------------------
/**
 * @brief   �I�����ʂ���M����֐�
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//------------------------------------------------------

void CommRecvListNo(int netID, int size, void* pData, void* pWork)
{
    _ListResult* pRet = pData;

    _pCT->listNo[netID].no = pRet->no;
    _pCT->listNo[netID].listNo = pRet->listNo;
}

//------------------------------------------------------
/**
 * @brief   �I�����ʂ�ʐM����R�}���h�T�C�Y
 * @param   no        �I�����j�[�N�ԍ�
 * @param   listNo    �I������  0-255
 * @retval  none
 */
//------------------------------------------------------

int CommGetListNoSize(void)
{
    return sizeof(_ListResult);
}

//------------------------------------------------------
/**
 * @brief   �I�����ʂ�ʐM����
 * @param   no        �I�����j�[�N�ԍ�
 * @param   listNo    �I������  0-255
 * @retval  none
 */
//------------------------------------------------------

void CommListSet(u8 no,u8 listNo)
{
    _ListResult ret;

    ret.no = no;
    ret.listNo = listNo;
    CommSendFixSizeData(CS_LIST_NO,&ret);
}

//------------------------------------------------------
/**
 * @brief   �I�����ʂ��󂯎��
 * @param   recvNetID   �ǂ̐l�̃f�[�^��҂��󂯂�̂�
 * @param   pBuff       ��M�o�b�t�@
 * @retval  �I������ �������� -1
 */
//------------------------------------------------------

int CommListGet(int netID, u8 no)
{
    if(!_pCT){
        return INVALID_LIST_NO;
    }
    if(_pCT->listNo[netID].no == no){
        return _pCT->listNo[netID].listNo;
    }
    return INVALID_LIST_NO;
}


//------------------------------------------------------
/**
 * @brief   �I�����ʂ�����
 * @param   none
 * @retval  none
 */
//------------------------------------------------------

void CommListReset(void)
{
    int i;

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        MI_CpuFill8(&_pCT->listNo[i], 0, sizeof(_ListResult));
    }
}

//==============================================================================
/**
 * �ڑ����ɑ���ɑ��肽���f�[�^������  10byte
 * @param   netID   id   �����̗\���ID
 * @param   pData   ���肽���f�[�^
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

void CommToolTempDataReset(void)
{
    int i;
    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _pCT->tempRecv[i] = FALSE;
    }

}

//==============================================================================
/**
 * �ڑ����ɑ���ɑ��肽���f�[�^������  10byte
 * @param   netID   id   �����̗\���ID
 * @param   pData   ���肽���f�[�^
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

BOOL CommToolSetTempData(int netID,const void* pData)
{
    if(_pCT){
        MI_CpuCopy8(pData, _pCT->tempWork[netID], _TEMPDATA_SIZE);
        CommSendFixSizeData(CS_TOOL_TEMP, _pCT->tempWork[netID]);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �ڑ����ɑ���ɑ������f�[�^�𓾂�  10byte
 * @param   netID   id   ����̗\���ID
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

const void* CommToolGetTempData(int netID)
{
    if(_pCT->tempRecv[netID]){
        return &_pCT->tempWork[netID];
    }
    return NULL;
}

//==============================================================================
/**
 * �e���|�����[�f�[�^����M����
 * @param   netID   id   ����̗\���ID
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

void CommToolRecvTempData(int netID, int size, void* pData, void* pWork)
{
    _pCT->tempRecv[netID] = TRUE;
    MI_CpuCopy8(pData, _pCT->tempWork[netID], _TEMPDATA_SIZE);
}

//==============================================================================
/**
 * �e���|�����[�f�[�^�T�C�Y��Ԃ�
 * @param   netID   id   ����̗\���ID
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

int CommToolGetTempDataSize(void)
{
    return _TEMPDATA_SIZE;
}
