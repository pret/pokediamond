//=============================================================================
/**
 * @file	comm_system.c
 * @brief	�ʐM�V�X�e��
 * @author	Katsumi Ohno
 * @date    2005.09.08
 */
//=============================================================================


#include "common.h"
#include "wh_config.h"
#include "wh.h"
#include "communication/communication.h"
#include "comm_local.h"

#include "system/pm_str.h"
#include "system/gamedata.h"  //PERSON_NAME_SIZE

#include "comm_ring_buff.h"
#include "comm_queue.h"
#include "system/savedata.h"
#include "savedata/regulation.h"
#include "system/pm_rtc.h"  //GF_RTC

#include "wifi/dwc_rap.h"   //WIFI

#define FREEZE_SORCE (0)
#define _SENDRECV_LIMIT  (3)  // ���M�Ǝ�M�̐������ꂽ�ꍇ���M��}������

//==============================================================================
// extern�錾
//==============================================================================

// �R���p�C�����Ƀ��[�j���O���o��̂Œ�`���Ă���
#include "communication/comm_system.h"



//==============================================================================
// ��`
//==============================================================================

// �N���C�A���g���M�p�L���[�̃o�b�t�@�T�C�Y    ����A�N���C�A���g��㩂̐���葽���؂��Ă���
#define _SENDQUEUE_NUM_MAX  (100)
#define _SENDQUEUE_NUM_NORMAL  (20)
// �T�[�o�[���M�p�L���[�̃o�b�t�@�T�C�Y    ����A㩂̐���葽���؂��Ă���
#define _SENDQUEUE_SERVER_NUM_MAX      (800)
#define _SENDQUEUE_SERVER_NUM_NORMAL      (280)

//�q�@���M�o�b�t�@�̃T�C�Y    �P�U��Ȃ��ꍇ�̔C�V���̐����o�C�g��
#define _SEND_BUFF_SIZE_CHILD  WH_MP_CHILD_DATA_SIZE
//�q�@���M�o�b�t�@�̃T�C�Y    �S��ȉ��ڑ����̑��M�o�C�g��
#define _SEND_BUFF_SIZE_4CHILD  WH_MP_4CHILD_DATA_SIZE
// �q�@RING���M�o�b�t�@�T�C�Y
#define _SEND_RINGBUFF_SIZE_CHILD  (_SEND_BUFF_SIZE_CHILD * 22)
//�e�@���M�o�b�t�@�̃T�C�Y
#define _SEND_BUFF_SIZE_PARENT  WH_MP_PARENT_DATA_SIZE
// �e�@RING���M�o�b�t�@�T�C�Y
#define _SEND_RINGBUFF_SIZE_PARENT  (_SEND_BUFF_SIZE_PARENT * 2)

// �q�@��M�o�b�t�@�̃T�C�Y
#define _RECV_BUFF_SIZE_CHILD  (_SEND_BUFF_SIZE_PARENT-1)
// �e�@��M�o�b�t�@�T�C�Y
#define _RECV_BUFF_SIZE_PARENT (_SEND_BUFF_SIZE_CHILD-1)



// ����������Ă��Ȃ��C�e���[�^�[�̐�
#define _NULL_ITERATE (-1)
// ���肦�Ȃ�ID
#define _INVALID_ID  (COMM_INVALID_ID)
// ���肦�Ȃ�HEADER
#define _INVALID_HEADER  (0xff)
// ���M�f�[�^���܂����炦�Ă��Ȃ�����
#define _NODATA_SEND  (0x0e)

//VBlank�����̃^�X�N�̃v���C�I���e�B�[
#define _PRIORITY_VBLANKFUNC (0)

// �ʐM�擪�o�C�g��BIT�̈Ӗ�
#define _SEND_NONE  (0x00)  // ���ő����ꍇ
#define _SEND_NEXT  (0x01)  // ���ő���Ȃ��ꍇ
#define _SEND_NO_DATA  (0x02)  // �L�[�f�[�^�[�ȊO�͖����ꍇ MP�q�@
#define _MP_DATA_HEADER (0x0b)  // �e�@MP�f�[�^�̏ꍇ�̔ԍ�  DS�̏ꍇ�� 0x00 or 0x01 or 0xfe or 0xff

#define _ACTION_COUNT_MOVE  (8)  // �ړ��L�[�𑗂�Ȃ�����

#define _PORT_DATA_RETRANSMISSION   (14)    // �ؒf����܂Ŗ����đ����s��  ��������g�p���Ă���
#define _PORT_DATA_PARENT         _PORT_DATA_RETRANSMISSION
#define _PORT_DATA_CHILD              _PORT_DATA_RETRANSMISSION

typedef enum{   // ���M���
    _SEND_CB_NONE,           // �Ȃɂ����Ă��Ȃ�
    _SEND_CB_FIRST_SEND,     // ����̒��ł̍ŏ��̑��M
    _SEND_CB_FIRST_SENDEND,  // �ŏ��̑��M�̃R�[���o�b�N������
    _SEND_CB_SECOND_SEND,    // ���荞�݂ł̑��M
    _SEND_CB_SECOND_SENDEND  // ���荞�݂ł̑��M�R�[���o�b�N������

};

typedef enum{   // ���M�`��
    _MP_MODE,    // �e�q�^
    _DS_MODE,    // ����^
    _CHANGE_MODE_DSMP,  // DS����MP�ɐ؂�ւ���
    _CHANGE_MODE_MPDS,  // MP����DS�ɐ؂�ւ���
};

typedef enum TrapKeyMode_e{
    _NONE_KEY,
    _RANDOM_KEY,
    _REVERSE_KEY,
};



//==============================================================================
// ���[�N
//==============================================================================

typedef struct{
    u8* pData;     ///< �f�[�^�|�C���^
    u16 size;       ///< �T�C�Y
    u8 command;    ///< �R�}���h
    u8 priority;   ///< �D�揇��  �������͑��M�����ǂ���
} _SEND_QUEUE;

typedef struct{
    int dataPoint; // ��M�o�b�t�@�\�񂪂���R�}���h�̃X�^�[�g�ʒu
    u8* pRecvBuff; // ��M�o�b�t�@�\�񂪂���R�}���h�̃X�^�[�g�ʒu
    u16 valSize;
    u8 valCommand;
} _RECV_COMMAND_PACK;


typedef struct{
    /// ----------------------------�q�@�p���e�@�pBUFF
    u8 sSendBuf[2][_SEND_BUFF_SIZE_4CHILD];          ///<  �q�@�̑��M�p�o�b�t�@
    u8 sSendBufRing[_SEND_RINGBUFF_SIZE_CHILD];  ///<  �q�@�̑��M�����O�o�b�t�@
    u8 sSendServerBuf[2][_SEND_BUFF_SIZE_PARENT];          ///<  �e�@�̑��M�p�o�b�t�@
    u8 sSendServerBufRing[_SEND_RINGBUFF_SIZE_PARENT];
    u8* pMidRecvBufRing;          ///< �󂯎��o�b�t�@���o�b�N�A�b�v���� DS��p
    u8* pServerRecvBufRing;       ///< �e�@����M�o�b�t�@
    u8* pRecvBufRing;             ///< �q�@���󂯎��o�b�t�@
    u8* pTmpBuff;                 ///< ��M�󂯓n���̂��߂̈ꎞ�o�b�t�@�|�C���^
    //----ring
    RingBuffWork sendRing;
    RingBuffWork recvRing;                      ///< �q�@�̎�M�����O�o�b�t�@
//    RingBuffWork recvRingUndo;                      ///< �q�@�̎�M�����O�o�b�t�@
    RingBuffWork recvMidRing[COMM_MACHINE_MAX];
    RingBuffWork sendServerRing;
    RingBuffWork recvServerRing[COMM_MACHINE_MAX];
//    RingBuffWork recvServerRingUndo[COMM_MACHINE_MAX];
    TCB_PTR pVBlankTCB;
    ///---que�֘A
    SEND_QUEUE_MANAGER sendQueueMgr;
    SEND_QUEUE_MANAGER sendQueueMgrServer;
    ///---��M�֘A
    _RECV_COMMAND_PACK recvCommServer[COMM_MACHINE_MAX];
    _RECV_COMMAND_PACK recvCommClient;
    
    ///------  pad�֘A
    MATHRandContext32 sRand;                    ///< �L�[�p�����L�[
    u16 cont[COMM_MACHINE_MAX];            ///< �Ǝ��L�[�V�F�A�����O
    u8 speed[COMM_MACHINE_MAX];             ///< ���x�𖈉񑗂�
    u16 sendCont;
    u8 sendKeyStop;
    u8 sendSpeed;
    u8 randPadType;   ///< �����ړ��Ɏg�p
    s8 randPadStep;   ///< �����ړ��Ɏg�p
    u16 oldPad;        ///< �����ړ��Ɏg�p
    //---------  �����֘A
    BOOL bWifiSendRecv;   // WIFI�̏ꍇ��������鎞�ƂƂ�Ȃ��Ƃ����K�v�Ȃ̂� �؂蕪����
    volatile int countSendRecv;   // ��������{�󂯎������| ��
    volatile int countSendRecvServer[COMM_MACHINE_MAX];   // ��������{�󂯎������| ��

#ifdef PM_DEBUG

    volatile int countSendNum;   // ��������{
    volatile int countRecvNum;   // �󂯎������{ ��
    volatile int countSendNumServer[COMM_MACHINE_MAX];   // ��������{ ��
    volatile int countRecvNumServer[COMM_MACHINE_MAX];   // �󂯎������{ ��
#endif
    
    //-------
    int packetSizeMax;
    u16 bitmap;   // �ڑ����Ă���@���BIT�Ǘ�
    
    //-------------------
//    u8 DSCountRecv[COMM_MACHINE_MAX];  // ���Ԋm�F�p
    u8 DSCount; // ���Ԋm�F�p
    u8 recvDSCatchFlg[COMM_MACHINE_MAX];  // �ʐM������������Ƃ��L�� DS�����p
    u8 bFirstCatch[COMM_MACHINE_MAX];  // �R�}���h���͂��߂Ă���������p

    u8 bPSendNoneRecv[COMM_MACHINE_MAX];        // �ŏ��̃R�[���o�b�N�𖳏�������

#ifdef PM_DEBUG
    u8 DebugAutoMove;
#endif
    u8 standNo[4];     // �퓬�̂Ƃ��̗������ʒu
   // u8 actionCount;
    u8 transmissionNum;
    u8 transmissionSend;
    u8 transmissionType;  // �ʐM�`�� DS��MP���̊Ǘ�
    u8 changeService;    // �ʐM�`�Ԃ̕ύX
    u8 sendSwitch;   // ���M�o�b�t�@�̃X�C�b�`�t���O
    u8 sendServerSwitch;   // ���M�o�b�t�@�̃X�C�b�`�t���O�i�T�[�o�p�j
    u8 timSendCond; // �L�[�𑗐M���ꍇ �ΐ핔����MENU�𓮂��Ȃ�����ׂɂ���
    u8 bFirstCatchP2C;
    u8 bSendNoneSend;        // �����R�}���h�𑗂�
    u8 bNextSendData;  ///
    u8 bNextSendDataServer;  ///
    u8 bAlone;    // ��l�ŒʐM�ł���悤�ɂ��郂�[�h�̎�TRUE
    u8 bWifiConnect; //WIFI�ʐM�\�ɂȂ�����TRUE
    u8 bResetState;
    u8 bError;  // �����s�\�Ȏ���TRUE
    u8 bShutDown;
    u8 bNotRecvCheck;
} _COMM_WORK_SYSTEM;

static _COMM_WORK_SYSTEM* _pComm = NULL;  ///<�@���[�N�\���̂̃|�C���^
// �e�@�ɂȂ�ꍇ��TGID �\���̂ɓ���Ă��Ȃ��̂�
// �ʐM���C�u�����[��؂����Ƃ��Ă��C���N�������g����������
static u16 _sTgid = 0;
// ���荞�݂Ńf�[�^���������邩�ǂ����̃t���O
static volatile u8 _bVSAccess = FALSE;

// ���M�������Ƃ��m�F���邽�߂̃t���O
static volatile u8 _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
// ����
static volatile u8 _sendCallBack = _SEND_CB_SECOND_SENDEND;


//==============================================================================
// static�錾
//==============================================================================

static void _commCommandInit(void);
static void _commMpVBlankIntr(TCB_PTR pTCB, void* pWork);
static void _dataMpStep(void);
static void _updateMpDataServer(void);
static void _dataMpServerStep(void);
static void _sendCallbackFunc(BOOL result);
static void _sendServerCallback(BOOL result);
static void _commRecvCallback(u16 aid, u16 *data, u16 size);
static void _commRecvParentCallback(u16 aid, u16 *data, u16 size);

static void _keyRand(void);
static void _updateMpData(void);

static void _recvDataFunc(void);
static void _recvDataServerFunc(void);
static BOOL _setSendData(u8* pSendBuff);
static void _setSendDataServer(u8* pSendBuff);

static BOOL _padDataRecv(u8* pRecvBuff, int netID);
static BOOL _padDataSend(u8* pSendBuff);

static BOOL _setSendQueue(_SEND_QUEUE* pSendQueue,
                          int command, const void* data, int size);
static int _getNowQueueDataSize(_SEND_QUEUE* pSendQueue);
static BOOL _sendQueueSet(void);
static BOOL _sendServerQueueSet(void);
static void _queueSet(int restSize);
static void _queueSetServer(int restSize);
static void _spritDataSendFunc(void);

static void _transmission(void);

#ifdef PM_DEBUG
static void _debugAutoMove(void);
#endif



#ifdef PM_DEBUG

extern int DebugCommGetNum(int id);
int DebugCommGetNum(int id)
{
    if(_pComm==NULL){
        return 0;
    }
    switch(id){
      case 0:
        return _pComm->countSendRecv;
      case 1:
        return _pComm->countSendRecvServer[0];
      case 2:
        return _pComm->countSendRecvServer[1];
      case 3:
        return _pComm->countSendRecvServer[2];
      case 4:
        return _pComm->countSendRecvServer[3];
      case 5:
        return _pComm->countSendNum;   // ��������{
      case 6:
        return _pComm->countRecvNum;   // �󂯎������{ ��
      case 7:
        return _pComm->countSendNumServer[0];   // ��������{ ��
      case 8:
        return _pComm->countSendNumServer[1];   // ��������{ ��
      case 9:
        return _pComm->countRecvNumServer[0];   // ��������{ ��
      case 10:
        return _pComm->countRecvNumServer[1];   // ��������{ ��
    }
    return 0;
}

#endif

//==============================================================================
/**
 * �e�q���ʁA�ʐM�̏��������܂Ƃ߂�
 * @param   bAlloc          �������[�m�ۂ��邩�ǂ���
 * @param   packetSizeMax   �m�ۂ������p�P�b�g�T�C�Y
 * @retval  �������ɐ���������TRUE
 */
//==============================================================================

static BOOL _commInit(BOOL bAlloc, int packetSizeMax)
{
    void* pWork;
    int i;
    // �C�N�j���[�������l�b�g���[�N���C�u�����̍ď��������K�v�ȏꍇTRUE
    BOOL bReInit = FALSE;

    _bVSAccess = FALSE;  // ���荞�ݓ��ł̏������֎~

    if(bAlloc){
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
        if(_pComm!=NULL){  // ���łɏ��������Ă���ꍇ��return
            return TRUE;
        }
        CommToolInitialize(HEAPID_COMMUNICATION);
        OHNO_PRINT("_COMM_WORK_SYSTEM size %d \n", sizeof(_COMM_WORK_SYSTEM));
        _pComm = (_COMM_WORK_SYSTEM*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_WORK_SYSTEM));
        MI_CpuClear8(_pComm, sizeof(_COMM_WORK_SYSTEM));
        
        _pComm->packetSizeMax = packetSizeMax + 64;
        _pComm->transmissionType = _MP_MODE;
        _pComm->changeService = COMM_MODE_NONE;
//        _pComm->bAlone = FALSE;
        
        _pComm->pRecvBufRing = sys_AllocMemory(HEAPID_COMMUNICATION, _pComm->packetSizeMax*2); ///< �q�@���󂯎��o�b�t�@
        _pComm->pTmpBuff = sys_AllocMemory(HEAPID_COMMUNICATION, _pComm->packetSizeMax);  ///< ��M�󂯓n���̂��߂̈ꎞ�o�b�t�@
        _pComm->pServerRecvBufRing = sys_AllocMemory(HEAPID_COMMUNICATION, machineMax * _pComm->packetSizeMax);   ///< �󂯎��o�b�t�@���o�b�N�A�b�v����
        _pComm->pMidRecvBufRing = sys_AllocMemory(HEAPID_COMMUNICATION, machineMax * _pComm->packetSizeMax);   ///< �󂯎��o�b�t�@���o�b�N�A�b�v���� DS��p
        // �L���[�̏�����
        if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
            CommQueueManagerInitialize(&_pComm->sendQueueMgr, _SENDQUEUE_NUM_MAX, &_pComm->sendRing);
            CommQueueManagerInitialize(&_pComm->sendQueueMgrServer, _SENDQUEUE_SERVER_NUM_MAX, &_pComm->sendServerRing);
        }
        else{
            CommQueueManagerInitialize(&_pComm->sendQueueMgr, _SENDQUEUE_NUM_NORMAL, &_pComm->sendRing);
            CommQueueManagerInitialize(&_pComm->sendQueueMgrServer, _SENDQUEUE_SERVER_NUM_NORMAL, &_pComm->sendServerRing);
        }

#ifdef PM_DEBUG
//        CommQueueDebugTest();  // �L���[�̃v���O�����e�X�g
#endif
    }
    else{
        bReInit = TRUE;
        GF_ASSERT((_pComm) && "�؂�ւ��̎��͂��łɏ������ς�\n");
    }
    
#ifdef PM_DEBUG
    _pComm->DebugAutoMove = 0;
#endif
    _pComm->bitmap = 0;
    for(i =0; i < 4;i++){
        _pComm->standNo[i] = 0xff;
    }

    if(!bReInit){   // �R�}���h�̏�����
        _commCommandInit();
    }
    CommRandSeedInitialize(&_pComm->sRand);

    //************************************

    if(!bReInit){   // �v���Z�X�^�X�N�̍쐬
        // VBLANK
        _pComm->pVBlankTCB = VIntrTCB_Add(_commMpVBlankIntr, NULL, _PRIORITY_VBLANKFUNC);

    }
    _pComm->bWifiConnect = FALSE;
    return TRUE;
}


#ifdef PM_DEBUG
static u8 _sendDataNext=FALSE;
#endif


//==============================================================================
/**
 * �e�q���ʁA�ʐM�̃R�}���h�Ǘ��̏��������܂Ƃ߂�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandInit(void)
{
    void* pWork;
    int i;

    // ���[�N�̏�����
//    OHNO_PRINT("�R�}���h�ď�����\n");
    
    _pComm->randPadType = 0;
    _pComm->randPadStep = 0;
    _pComm->sendSwitch = 0;
    _pComm->sendServerSwitch = 0;
    
    // �e�@�݂̂̑���M
    {
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

        OHNO_PRINT("packet %d %d\n",_pComm->packetSizeMax,machineMax);
        MI_CpuFill8(_pComm->pServerRecvBufRing, 0, _pComm->packetSizeMax * machineMax);
        for(i = 0; i< machineMax;i++){
            CommRingInitialize(&_pComm->recvServerRing[i],
                               &_pComm->pServerRecvBufRing[i*_pComm->packetSizeMax],
                               _pComm->packetSizeMax);
//            CommRingInitialize(&_pComm->recvServerRingUndo[i],
//                               &_pComm->pServerRecvBufRing[i*_pComm->packetSizeMax],
//                               _pComm->packetSizeMax);
        }

        MI_CpuFill8(_pComm->pMidRecvBufRing, 0, _pComm->packetSizeMax * machineMax );
        for(i = 0; i < machineMax; i++){
            CommRingInitialize(&_pComm->recvMidRing[i],
                               &_pComm->pMidRecvBufRing[i * _pComm->packetSizeMax],
                               _pComm->packetSizeMax);
        }
    }
    MI_CpuFill8(_pComm->sSendServerBufRing, 0, _SEND_RINGBUFF_SIZE_PARENT);
    CommRingInitialize(&_pComm->sendServerRing, _pComm->sSendServerBufRing,
                       _SEND_RINGBUFF_SIZE_PARENT);
    for(i = 0; i < _SEND_BUFF_SIZE_PARENT; i++){
        _pComm->sSendServerBuf[0][i] = CS_NONE;
        _pComm->sSendServerBuf[1][i] = CS_NONE;
    }
    // �q�@�̑���M
    MI_CpuFill8(_pComm->sSendBufRing, 0, _SEND_RINGBUFF_SIZE_CHILD);
    CommRingInitialize(&_pComm->sendRing, _pComm->sSendBufRing, _SEND_RINGBUFF_SIZE_CHILD);

    _pComm->sSendBuf[0][0] = _INVALID_HEADER;
    _pComm->sSendBuf[1][0] = _INVALID_HEADER;
    for(i = 1;i < _SEND_BUFF_SIZE_4CHILD;i++){
        _pComm->sSendBuf[0][i] = CS_NONE;
        _pComm->sSendBuf[1][i] = CS_NONE;
    }
    MI_CpuFill8(_pComm->pRecvBufRing, 0, _pComm->packetSizeMax*2);
    CommRingInitialize(&_pComm->recvRing, _pComm->pRecvBufRing, _pComm->packetSizeMax*2);

    _pComm->bNextSendData = FALSE;
    _pComm->bNextSendDataServer = FALSE;
#ifdef PM_DEBUG
    _sendDataNext=FALSE;
#endif
    for(i = 0; i< COMM_MACHINE_MAX;i++){
  //      _pComm->DSCountRecv[i] = 0xff;
        _pComm->recvDSCatchFlg[i] = 0;  // �ʐM������������Ƃ��L��
        _pComm->bFirstCatch[i] = TRUE;
        _pComm->bPSendNoneRecv[i] = TRUE;
        _pComm->cont[i]=0;  ///< �Ǝ��L�[�V�F�A�����O
        //_pComm->contOld[i]=0;  ///< �Ǝ��L�[�V�F�A�����O
        //_pComm->trg[i]=0;   ///< �Ǝ��L�[�V�F�A�����O
        _pComm->recvCommServer[i].valCommand = CS_NONE;
        _pComm->recvCommServer[i].valSize = 0xffff;
        _pComm->recvCommServer[i].pRecvBuff = NULL;
        _pComm->recvCommServer[i].dataPoint = 0;
        _pComm->countSendRecvServer[i] = 0;
#ifdef PM_DEBUG
        _pComm->countSendNumServer[i] = 0;
        _pComm->countRecvNumServer[i] = 0;
#endif
    }
    _pComm->countSendRecv = 0;
#ifdef PM_DEBUG
    _pComm->countSendNum = 0;
    _pComm->countRecvNum = 0;
#endif
    _pComm->bWifiSendRecv = TRUE;
    _pComm->recvCommClient.valCommand = CS_NONE;
    _pComm->recvCommClient.valSize = 0xffff;
    _pComm->recvCommClient.pRecvBuff = NULL;
    _pComm->recvCommClient.dataPoint = 0;

    _pComm->bFirstCatchP2C = TRUE;
    _pComm->bSendNoneSend = TRUE;
    
    _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
    _sendCallBack = _SEND_CB_SECOND_SENDEND;

        // �L���[�̃��Z�b�g
    CommQueueManagerReset(&_pComm->sendQueueMgr);
    CommQueueManagerReset(&_pComm->sendQueueMgrServer);
    _pComm->bResetState = FALSE;
}

//==============================================================================
/**
 * �e�q���ʁADSMP����������ꍇ�ɌĂ΂��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandInitChange2(void)
{
    void* pWork;
    int i;

    _pComm->randPadType = 0;
    _pComm->randPadStep = 0;
//    _pComm->sendSwitch = 0;
//    _pComm->sendServerSwitch = 0;
    
    // �e�@�݂̂̑���M
    {
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

        OHNO_PRINT("packet %d %d\n",_pComm->packetSizeMax,machineMax);
        MI_CpuFill8(_pComm->pServerRecvBufRing, 0, _pComm->packetSizeMax * machineMax);
        for(i = 0; i< machineMax;i++){
            CommRingInitialize(&_pComm->recvServerRing[i],
                               &_pComm->pServerRecvBufRing[i*_pComm->packetSizeMax],
                               _pComm->packetSizeMax);
        }

        MI_CpuFill8(_pComm->pMidRecvBufRing, 0, _pComm->packetSizeMax * machineMax );
        for(i = 0; i < machineMax; i++){
            CommRingInitialize(&_pComm->recvMidRing[i],
                               &_pComm->pMidRecvBufRing[i * _pComm->packetSizeMax],
                               _pComm->packetSizeMax);
        }
    }
    MI_CpuFill8(_pComm->sSendServerBufRing, 0, _SEND_RINGBUFF_SIZE_PARENT);
    CommRingInitialize(&_pComm->sendServerRing, _pComm->sSendServerBufRing,
                       _SEND_RINGBUFF_SIZE_PARENT);
    for(i = 0; i < _SEND_BUFF_SIZE_PARENT; i++){
        _pComm->sSendServerBuf[0][i] = CS_NONE;
        _pComm->sSendServerBuf[1][i] = CS_NONE;
    }
    // �q�@�̑���M
    MI_CpuFill8(_pComm->sSendBufRing, 0, _SEND_RINGBUFF_SIZE_CHILD);
    CommRingInitialize(&_pComm->sendRing, _pComm->sSendBufRing, _SEND_RINGBUFF_SIZE_CHILD);

    _pComm->sSendBuf[0][0] = _INVALID_HEADER;
    _pComm->sSendBuf[1][0] = _INVALID_HEADER;
    for(i = 1;i < _SEND_BUFF_SIZE_4CHILD;i++){
        _pComm->sSendBuf[0][i] = CS_NONE;
        _pComm->sSendBuf[1][i] = CS_NONE;
    }
    MI_CpuFill8(_pComm->pRecvBufRing, 0, _pComm->packetSizeMax*2);
    CommRingInitialize(&_pComm->recvRing, _pComm->pRecvBufRing, _pComm->packetSizeMax*2);

    _pComm->bNextSendData = FALSE;
    _pComm->bNextSendDataServer = FALSE;
#ifdef PM_DEBUG
    _sendDataNext = FALSE;
#endif
    for(i = 0; i< COMM_MACHINE_MAX;i++){
        _pComm->recvDSCatchFlg[i] = 0;  // �ʐM������������Ƃ��L��
        _pComm->bFirstCatch[i] = TRUE;
        _pComm->bPSendNoneRecv[i] = TRUE;
        _pComm->cont[i]=0;  ///< �Ǝ��L�[�V�F�A�����O
        _pComm->recvCommServer[i].valCommand = CS_NONE;
        _pComm->recvCommServer[i].valSize = 0xffff;
        _pComm->recvCommServer[i].pRecvBuff = NULL;
        _pComm->recvCommServer[i].dataPoint = 0;
    }
    _pComm->bWifiSendRecv = TRUE;
    _pComm->recvCommClient.valCommand = CS_NONE;
    _pComm->recvCommClient.valSize = 0xffff;
    _pComm->recvCommClient.pRecvBuff = NULL;
    _pComm->recvCommClient.dataPoint = 0;

    _pComm->bFirstCatchP2C = TRUE;
    _pComm->bSendNoneSend = TRUE;
    
//    _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
//    _sendCallBack = _SEND_CB_SECOND_SENDEND;

        // �L���[�̃��Z�b�g
    CommQueueManagerReset(&_pComm->sendQueueMgr);
    CommQueueManagerReset(&_pComm->sendQueueMgrServer);
    _pComm->bResetState = FALSE;
}

//==============================================================================
/**
 * �w�肳�ꂽ�q�@�̗̈���N���A�[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _clearChildBuffers(int netID)
{
//    _pComm->DSCountRecv[netID] = 0xff;
    _pComm->recvDSCatchFlg[netID] = 0;  // �ʐM������������Ƃ��L�� DS�����p
    _pComm->bFirstCatch[netID] = TRUE;  // �R�}���h���͂��߂Ă���������p
    _pComm->countSendRecvServer[netID]=0;  //SERVER��M
    _pComm->bPSendNoneRecv[netID] = TRUE;  // �����

    CommRingInitialize(&_pComm->recvMidRing[netID],
                       &_pComm->pMidRecvBufRing[netID * _pComm->packetSizeMax],
                       _pComm->packetSizeMax);

    CommRingInitialize(&_pComm->recvServerRing[netID],
                       &_pComm->pServerRecvBufRing[netID * _pComm->packetSizeMax],
                       _pComm->packetSizeMax);

    _pComm->recvCommServer[netID].valCommand = CS_NONE;
    _pComm->recvCommServer[netID].valSize = 0xffff;
    _pComm->recvCommServer[netID].pRecvBuff = NULL;
    _pComm->recvCommServer[netID].dataPoint = 0;
}

//==============================================================================
/**
 * �w�肳�ꂽ�q�@�̗̈���N���A�[����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _connectFunc(void)
{
    int i;

    for(i = 1 ; i < COMM_MACHINE_MAX ; i++){
        if((!CommIsConnect(i)) && !_pComm->bFirstCatch[i]){
            if(!CommGetAloneMode()){
                OHNO_PRINT("��ڑ��ɂȂ������� %d\n",i);
                _clearChildBuffers(i);  // ��ڑ��ɂȂ�������
            }
        }
    }

}


//==============================================================================
/**
 * �e�@�̏��������s��
 * @param   work_area �@�V�X�e���Ŏg���������[�̈�
 *                      NULL�̏ꍇ���łɏ������ς݂Ƃ��ē���
 * @param   regulationNo  �Q�[���̎��
 * @param   bTGIDChange  �V�K�̃Q�[���̏������̏ꍇTRUE �Â��r�[�R���ł̌듮���h�����ߗp
 * @param   bEntry  �q�@���󂯓���邩�ǂ���
 * @retval  �������ɐ���������TRUE
 */
//==============================================================================
BOOL CommParentModeInit(BOOL bAlloc, BOOL bTGIDChange, int packetSizeMax, BOOL bEntry)
{
    BOOL ret = TRUE;
    if(CommStateGetServiceNo() < COMM_MODE_BATTLE_SINGLE_WIFI){
        ret = CommMPParentInit(bAlloc, bTGIDChange, bEntry);
    }
    _commInit(bAlloc, packetSizeMax);
    return ret;
}

//==============================================================================
/**
 * �q�@�̏��������s��
 * @param   work_area �@�V�X�e���Ŏg���������[�̈�
 *                      NULL�̏ꍇ�͂��łɏ������ς݂Ƃ��Ĉ���
 * @param   regulationNo  �Q�[���̎��
 * @param   bBconInit  �r�[�R���f�[�^������������̂��ǂ���
 * @retval  �������ɐ���������TRUE
 */
//==============================================================================
BOOL CommChildModeInit(BOOL bAlloc, BOOL bBconInit, int packetSizeMax)
{
    BOOL ret = TRUE;

    if(COMM_MODE_BATTLE_SINGLE_WIFI > CommStateGetServiceNo()){
        ret = CommMPChildInit(bAlloc, bBconInit);
    }
    else{
    }
    _commInit(bAlloc, packetSizeMax);
    _sendCallBack = _SEND_CB_SECOND_SENDEND;

    return ret;
}

//==============================================================================
/**
 * �ʐM���[�h�ؑ�
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _transmissonTypeChange(void)
{
    int i;
    BOOL bChange = FALSE;

    // �x�����Ă鎞�ɕύX���Ȃ��悤�ɂ���
    if(CommGetCurrentID() == COMM_PARENT_ID){
        if(_sendCallBackServer != _SEND_CB_SECOND_SENDEND){
            return;
        }
    }
    else{
        if(_sendCallBack != _SEND_CB_SECOND_SENDEND){
            return;
        }
    }
    
    if(_pComm->transmissionType == _CHANGE_MODE_DSMP){
        _pComm->transmissionType = _MP_MODE;
        bChange=TRUE;
        OHNO_PRINT("MP���[�h�ɂȂ�܂���\n");
    }
    if(_pComm->transmissionType == _CHANGE_MODE_MPDS){
        _pComm->transmissionType = _DS_MODE;
        bChange=TRUE;
        OHNO_PRINT("DS���[�h�ɂȂ�܂���\n");
    }
    if(bChange){
        _commCommandInitChange2(); // �R�}���h�S������
        OHNO_PRINT("send Recv %d %d %d \n",_pComm->countSendRecv,_pComm->countSendRecvServer[0],_pComm->countSendRecvServer[1]);
    }

    _transmission();

}

//==============================================================================
/**
 * DS���[�h�ɐ؂�ւ���
 * @param   DS���[�h�œ����ꍇ_DS_MODE MP�œ����ꍇ_MP_MODE
 * @retval  none
 */
//==============================================================================


static void _commSetTransmissonType(int type)
{
    if((_pComm->transmissionType == _MP_MODE) && (type == _DS_MODE)){
        _pComm->transmissionType = _CHANGE_MODE_MPDS;
        return;
    }
    if((_pComm->transmissionType == _DS_MODE) && (type == _MP_MODE)){
        _pComm->transmissionType = _CHANGE_MODE_DSMP;
        return;
    }
}

void CommSetTransmissonTypeDS(void)
{
    _commSetTransmissonType(_DS_MODE);
}

void CommSetTransmissonTypeMP(void)
{
    _commSetTransmissonType(_MP_MODE);
}

//==============================================================================
/**
 * ���݂̃��[�h�̎擾
 * @param   none
 * @retval  _DS_MODE��_MP_MODE
 */
//==============================================================================

static int _transmissonType(void)
{
    if(_pComm->transmissionType == _CHANGE_MODE_DSMP){
        return _DS_MODE;
    }
    if(_pComm->transmissionType == _CHANGE_MODE_MPDS){
        return _MP_MODE;
    }
    return _pComm->transmissionType;
}

//==============================================================================
/**
 * ���� DS���[�h���ǂ���
 * @param   none
 * @retval  TRUE�Ȃ�DS
 */
//==============================================================================

BOOL CommIsTransmissonDSType(void)
{
    if(_DS_MODE == _transmissonType()){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �ʐM�ؒf���s��
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommFinalize(void)
{
    BOOL bEnd = FALSE;

    if(_pComm){
        if(COMM_MODE_BATTLE_SINGLE_WIFI <= CommStateGetServiceNo()){
            OHNO_PRINT("�ؒf------\n");
            mydwc_Logout();  // �ؒf
            bEnd = TRUE;
        }
        else{
            if(CommMPFinalize()){
                bEnd = TRUE;
            }
        }
    }
    if(bEnd){
        OHNO_PRINT("�ؒf----�J������--\n");
        CommToolFinalize();
        CommInfoFinalize();
        // VBLANK�^�X�N��؂�
        _bVSAccess = FALSE;  // ���荞�ݓ��ł̏������֎~
        OHNO_PRINT("VBLANK�^�X�N��؂�\n");
        TCB_Delete(_pComm->pVBlankTCB);
        _pComm->pVBlankTCB = NULL;
        sys_FreeMemoryEz(_pComm->pRecvBufRing);
        sys_FreeMemoryEz(_pComm->pTmpBuff);
        sys_FreeMemoryEz(_pComm->pServerRecvBufRing);
        sys_FreeMemoryEz(_pComm->pMidRecvBufRing);
        CommQueueManagerFinalize(&_pComm->sendQueueMgrServer);
        CommQueueManagerFinalize(&_pComm->sendQueueMgr);
        sys_FreeMemoryEz(_pComm);
        _pComm = NULL;
    }
}

//==============================================================================
/**
 * �q�@ ���O��ID�Őڑ�
 * @param   pNameBuf   �Ȃ��ɍs���������[�U�[�� 
 * @param   pokeID     �Ȃ��ɍs������ID
 * @retval  �e�@��񂪂Ȃ��ꍇ  CC_NOT_FOUND_PARENT_INFO
 * @retval  �ʐM�̓�����Ԃ��J�ڒ��ŁA�ڑ��ɂ����Ȃ��ꍇ  CC_BUSY_STATE
 * @retval  �ڑ��֐����Ăяo������ CC_CONNECT_STARTING
 */
//==============================================================================
//int CommChildNameAndIDConnect(STRBUF* pNameBuf,u32 pokeID)
//{
  //  return CommMPChildNameAndIDConnect(pNameBuf, pokeID);
//}

//==============================================================================
/**
 * �q�@ index�ڑ�
 * @param   index   �e�̃��X�g��index
 * @retval  �q�@�ڑ���e�@�ɑ�������TRUE
 */
//==============================================================================
BOOL CommChildIndexConnect(u16 index)
{
    return CommMPChildIndexConnect(index);
}

//==============================================================================
/**
 * �ʐM�������܂߂�VBLANK���荞�ݏ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commMpVBlankIntr(TCB_PTR pTCB, void* pWork)
{
    if(_bVSAccess){
        _updateMpData();     // �f�[�^����M
        if(((CommGetCurrentID() == COMM_PARENT_ID) && (CommIsConnect(COMM_PARENT_ID))) || CommGetAloneMode()){
            _updateMpDataServer();   // MP�ʐM�T�[�o�[��STEP����
        }
        _bVSAccess = FALSE;  // ���荞�ݓ��ł̏������֎~
    }
}


//==============================================================================
/**
 * �I���R�}���h����M�����烂�[�h�ɉ����ď������s�������ؒf����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _autoExitSystemFunc(void)
{
    if(!CommMPIsAutoExit()){
        return;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){   // �������e�̏ꍇ�݂�Ȃɋt�ԐM����
        if(CommMPIsChildsConnecting()){
            return;
        }
        CommFinalize();  // �I�������ɓ���
    }
    else{   //�q�@�̏ꍇ
        CommFinalize();  // �I�������ɓ���
    }
}

//==============================================================================
/**
 * �ʐM�f�[�^�̍X�V����  �f�[�^�����W
 *    main.c   ����  vblank��ɂ����ɌĂ΂��
 * @param   none
 * @retval  �f�[�^�V�F�A�����O���������Ȃ������ꍇFALSE
 */
//==============================================================================


BOOL CommUpdateData(void)
{
    int j;

    CommStateCheckFunc(); //commstate���^�X�N�������Ȃ����Ƃɂ����̂ł�����
    if(_pComm != NULL){
        
#if 0
        if(CommGetCurrentID() != -1){
            OHNO_PRINT("  RecvSend %d \n",_pComm->countSendRecv);
            if((CommGetCurrentID() == 0) || CommGetAloneMode()){
                for(j = 0;j < COMM_MACHINE_MAX;j++){
                    if(CommIsConnect(j) || (j == 0)){
                        OHNO_PRINT("  RecvSend %d  %d \n",j,_pComm->countSendRecvServer[j]);
                    }
                }
            }
        }
#endif
        if(!_pComm->bShutDown){

            _bVSAccess = FALSE;   // ���S�̂���VBlank���荞�݂ł̃A�N�Z�X�֎~�錾
            _transmissonTypeChange();  //�ʐM�؂�ւ�
            _pComm->sendCont |= (sys.cont & 0x7fff);  // �L�[�f�[�^�̎擾
#ifdef PM_DEBUG
            _debugAutoMove();
#endif
            _keyRand();

            _dataMpStep();
            _pComm->sendCont &= 0x8000;
            if(_transmissonType() == _MP_MODE){
                _recvDataFunc();    // �q�@�Ƃ��Ă̎󂯎�菈��
            }
            if((CommGetCurrentID() == COMM_PARENT_ID) && (CommIsConnect(COMM_PARENT_ID)) || CommGetAloneMode() ){
                // �T�[�o�[�Ƃ��Ă̏���
                _dataMpServerStep();
            }
            if((CommGetCurrentID() == COMM_PARENT_ID) || (_transmissonType() == _DS_MODE) || CommGetAloneMode() ){
                _recvDataServerFunc();  // �T�[�o�[���̎�M����
            }
            _bVSAccess = TRUE;  // ���̊��荞�ݎ��ł̏���������
        }
        CommMpProcess(_pComm->bitmap);
        if(CommGetCurrentID() == COMM_PARENT_ID){
            _connectFunc();
        }
        _autoExitSystemFunc();  // �����ؒf _pComm=NULL�ɂȂ�̂Œ���
    }
    else{
        CommMpProcess(0);
    }
    CommErrorDispCheck(HEAPID_BASE_SYSTEM);
    CommTimingSyncSend();
    return TRUE;
}


//==============================================================================
/**
 * �ʐM�o�b�t�@���N���A�[����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemReset(void)
{
    BOOL bAcc = _bVSAccess;

    OHNO_PRINT("CommSystemReset\n");
    _bVSAccess = FALSE;  // ���荞�ݓ��ł̏������֎~
    if(_pComm){
        _commCommandInit();
    }
    _bVSAccess = bAcc;
}

//==============================================================================
/**
 * DS���[�h�ŒʐM�o�b�t�@���N���A�[����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemResetDS(void)
{
    BOOL bAcc = _bVSAccess;

    OHNO_PRINT("CommSystemReset\n");
    _bVSAccess = FALSE;  // ���荞�ݓ��ł̏������֎~
    if(_pComm){
        _pComm->transmissionType = _DS_MODE;
        _commCommandInit();
    }
    _bVSAccess = bAcc;
}

//==============================================================================
/**
 * �ʐM�o�b�t�@���N���A�[����+�r�[�R���̏��������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemResetBattleChild(void)
{
    BOOL bAcc = _bVSAccess;

    OHNO_PRINT("CommSystemReset\n");
    _bVSAccess = FALSE;  // ���荞�ݓ��ł̏������֎~
    if(_pComm){
        _commCommandInit();
        ChildBconDataInit();
    }
    _bVSAccess = bAcc;
}

//==============================================================================
/**
 * �f�[�^���M����
 * @param   none
 * @retval  none
 */
//==============================================================================


static void _dataMpStep(void)
{
    if(_pComm->bSendNoneSend){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            if( _pComm->bWifiConnect ){
                if( mydwc_sendToServer( _pComm->sSendBuf[0], _SEND_BUFF_SIZE_4CHILD )){
                    _pComm->bSendNoneSend = FALSE;
                }
            }
        }
        else if(((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) &&
                 (CommIsConnect(CommGetCurrentID()))) || CommGetAloneMode()){
            _sendCallBack = _SEND_CB_NONE;
            _updateMpData();     // �f�[�^����M
            if(_sendCallBack != _SEND_CB_NONE){
                _pComm->bSendNoneSend = FALSE;
            }
        }
        return;
    }


    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        if( _pComm->bWifiConnect ){
            if( _pComm->bWifiSendRecv ){  // ����������Ă���ꍇ
                if( _pComm->countSendRecv > _SENDRECV_LIMIT ){  //���肷��
                    return;
                }
                if(_sendCallBack == _SEND_CB_SECOND_SENDEND){
                    _setSendData(_pComm->sSendBuf[0]);   // ����f�[�^�������O�o�b�t�@���獷���ւ���
                    _sendCallBack = _SEND_CB_FIRST_SENDEND;
                }
            }
            else{
                if(_sendCallBack == _SEND_CB_SECOND_SENDEND){
                    if(!_setSendData(_pComm->sSendBuf[0])){  // ����f�[�^�������O�o�b�t�@���獷���ւ���
                        return;  // �{���ɑ�����̂����������ꍇ
                    }
                    _sendCallBack = _SEND_CB_FIRST_SENDEND;
                }
            }
            if( mydwc_sendToServer( _pComm->sSendBuf[0], _SEND_BUFF_SIZE_4CHILD )){
//                if( !_pComm->bWifiSendRecv ){  // ����������ĂȂ��ꍇ
//                    DEBUG_DUMP(&_pComm->sSendBuf[0][0], 16,"sp0");
//                }
                _sendCallBack = _SEND_CB_SECOND_SENDEND;
                _pComm->countSendRecv++;  //wifi client
#ifdef PM_DEBUG
                _pComm->countSendNum++;
#endif
            }
            else{
            }
        }
    }
    else if(((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) &&
        (CommIsConnect(CommGetCurrentID()))) || CommGetAloneMode()){
        if(_sendCallBack != _SEND_CB_SECOND_SENDEND){  // 2�����������M�������Ă��Ȃ�
//            OHNO_PRINT("�ɂ��������Ƃ��ĂȂ� _sendCallBack\n");
            return;
        }
        if( _pComm->countSendRecv > _SENDRECV_LIMIT ){  //���肷��
//            OHNO_PRINT("�q�@���f�[�^���M�����Ȃ�\n");
            return;
        }
        _setSendData(_pComm->sSendBuf[_pComm->sendSwitch]);  // ����f�[�^�������O�o�b�t�@���獷���ւ���
        _setSendData(_pComm->sSendBuf[ 1 - _pComm->sendSwitch]);  // ����f�[�^�������O�o�b�t�@���獷���ւ���
        _sendCallBack = _SEND_CB_NONE;
        _updateMpData();     // �f�[�^����M
    }
}

//==============================================================================
/**
 * ����RINGBUFF����q�@�S���ɋt���M���邽��buff�ɃR�s�[
 * @param   none
 * @retval  none
 */
//==============================================================================

static BOOL _copyDSData(int switchNo)
{
    int mcSize;
    int machineMax;
    int i,num,nosend = 0;

    mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
    machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
/*
    // ������
    for(i = 0; i < machineMax; i++){
        if(CommIsConnect(i) && (_pComm->recvDSCatchFlg[i] > 1) ){
            // OHNO_PRINT("--------------�ǂ��z�������� %d\n",i);
            //                        _pComm->sSendServerBuf[_pComm->sendServerSwitch][i*mcSize] = _NODATA_SEND;
        }
        if(CommIsConnect(i) && (_pComm->recvDSCatchFlg[i] == 0) ){
            OHNO_PRINT("--------------�ǂ��ʂ������� %d\n",i);
            _pComm->sSendServerBuf[switchNo][i * mcSize] = _NODATA_SEND;
            if(CommStateGetServiceNo() < COMM_MODE_BATTLE_SINGLE_WIFI){
                _sendCallBackServer--;
                return FALSE;
            }
        }
        _pComm->recvDSCatchFlg[i] = 0;
    }
   */
    /// ����RINGBUFF����q�@�S���ɋt���M���邽��buff�ɃR�s�[
    for(i = 0; i < machineMax; i++){
        CommRingEndChange(&_pComm->recvMidRing[i]);
        if(CommIsConnect(i)){
            _pComm->sSendServerBuf[switchNo][i * mcSize] = _NODATA_SEND;
        }
        num = CommRingGets(&_pComm->recvMidRing[i] ,
                     &_pComm->sSendServerBuf[switchNo][i*mcSize],
                     mcSize);
        if(_pComm->sSendServerBuf[switchNo][i * mcSize] == _NODATA_SEND){
            nosend++;
        }
    }
    if(nosend == machineMax){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 * �f�[�^���M����  �T�[�o�[��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _updateMpDataServer(void)
{
    int i;
    int debug=0;
    int mcSize ,machineMax;

    if(!_pComm){
        return;
    }
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        return;
    }
    
    mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
    machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
    if((_sendCallBackServer == _SEND_CB_FIRST_SENDEND) ||
       (_sendCallBackServer == _SEND_CB_NONE)){
        _sendCallBackServer++;
        
        if(_transmissonType() == _DS_MODE){
            _copyDSData(_pComm->sendServerSwitch);
        }
        if( (WH_GetSystemState() == WH_SYSSTATE_CONNECTED)  && !CommGetAloneMode()){
            if(!WH_SendData(_pComm->sSendServerBuf[_pComm->sendServerSwitch],
                            _SEND_BUFF_SIZE_PARENT,
                            _PORT_DATA_PARENT, _sendServerCallback)){
                _sendCallBackServer--;
            }
        }
        // ���M����
        if((_sendCallBackServer == _SEND_CB_FIRST_SEND) || (_sendCallBackServer == _SEND_CB_SECOND_SEND) ){

            for(i = 0; i < machineMax; i++){
                if(CommIsConnect(i)){
                    _pComm->countSendRecvServer[i]++; // �eMP���M
#ifdef PM_DEBUG
                    _pComm->countSendNumServer[i]++;
#endif
                }
                else if(CommGetAloneMode() && (i == 0)){
                    _pComm->countSendRecvServer[i]++; // �eMP���M
#ifdef PM_DEBUG
                    _pComm->countSendNumServer[i]++;
#endif
                }
            }

            // �e�@���g�Ɏq�@�̓����������邽�߂����ŃR�[���o�b�N���Ă�
            _commRecvCallback(COMM_PARENT_ID,
                              (u16*)_pComm->sSendServerBuf[ _pComm->sendServerSwitch ],
                              _SEND_BUFF_SIZE_PARENT);
            _pComm->sendServerSwitch = 1 - _pComm->sendServerSwitch;
        }
        for(i = 0; i < machineMax; i++){
            if(!CommIsConnect(i)){
                if(_transmissonType() == _DS_MODE){             // ������
                    _pComm->sSendServerBuf[_pComm->sendServerSwitch][i*mcSize] = _INVALID_HEADER;
                }
                else{
  //                        _clearChildBuffers(i);
                }
            }
        }
        if( (WH_GetSystemState() != WH_SYSSTATE_CONNECTED)  || CommGetAloneMode() ){
            // ���荞�݂������󋵂ł��������ׂ����ŃJ�E���g
            _sendCallBackServer++;
        }
    }
}

//==============================================================================
/**
 * �f�[�^���M����  �T�[�o�[��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _dataMpServerStep(void)
{
    int i;

    if(_pComm->bSendNoneSend){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            if( CommIsConnect(COMM_PARENT_ID) ){
                if( mydwc_sendToClient( _pComm->sSendServerBuf[0], WH_MP_4CHILD_DATA_SIZE*2 )){
                    _pComm->bSendNoneSend = FALSE;
                    return;
                }
            }
        }
        else if((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) || (CommGetAloneMode()) ){
            _updateMpDataServer();
            if(_sendCallBackServer == _SEND_CB_FIRST_SENDEND){
                _pComm->bSendNoneSend = FALSE;
                return;
            }
        }
    }

    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        if( CommIsConnect(COMM_PARENT_ID) ){
            if( _pComm->bWifiSendRecv ){  // ����������Ă���ꍇ
                if(_pComm->countSendRecvServer[1] > _SENDRECV_LIMIT){ // ���M�������̏ꍇ
                    return;
                }
                if(_pComm->countSendRecvServer[0] > _SENDRECV_LIMIT){ // ���M�������̏ꍇ
                    return;
                }
                if(_sendCallBackServer == _SEND_CB_SECOND_SENDEND){
                    if(_transmissonType() == _DS_MODE){
                        _copyDSData(0);  //DS�ʐM�Ȃ�R�s�[
                    }
                    _sendCallBackServer = _SEND_CB_FIRST_SENDEND;
                }
            }
            else{
                if(_sendCallBackServer == _SEND_CB_SECOND_SENDEND){
                    if(_transmissonType() == _DS_MODE){
                        if(!_copyDSData(0)){  //DS�ʐM�Ȃ�R�s�[
                            return;
                        }
                    }
                }
                _sendCallBackServer = _SEND_CB_FIRST_SENDEND;
            }

            if( mydwc_sendToClient( _pComm->sSendServerBuf[0], WH_MP_4CHILD_DATA_SIZE*2 )){
                OHNO_SP_PRINT("send %d \n",_pComm->sSendServerBuf[0][0]);
                _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
                _pComm->countSendRecvServer[0]++; // wifi server
                _pComm->countSendRecvServer[1]++; // wifi server
#ifdef PM_DEBUG
                _pComm->countSendNumServer[0]++;
                _pComm->countSendNumServer[1]++;
#endif
            }
            else{
                OHNO_PRINT("mydwc_sendToClient�Ɏ��s\n");
            }
        }
    }
    else if((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) || (CommGetAloneMode()) ){
        if(_sendCallBackServer != _SEND_CB_SECOND_SENDEND){
//            OHNO_PRINT("��񂤂��Ƃ��ĂȂ�_sendCallBackServer\n");
            return;
        }
        for(i = 1; i < COMM_MACHINE_MAX; i++){
            if(CommIsConnect(i)){
                if(_pComm->countSendRecvServer[i] > _SENDRECV_LIMIT){ // ���M�������̏ꍇ
                    //OHNO_PRINT("���M������%d \n",i);
                    return;
                }
            }
            else if((i == 0) && CommGetAloneMode()){
                if(_pComm->countSendRecvServer[0] > _SENDRECV_LIMIT){ // ���M�������̏ꍇ
                    return;
                }
            }
        }
//        if( _pComm->countSendRecv > _SENDRECV_LIMIT ){  //���肷��
  //          return;
    //    }
        if(_transmissonType() == _MP_MODE){  // DS���ɂ͂��ł�sSendServerBuf�Ƀf�[�^������
            _setSendDataServer(_pComm->sSendServerBuf[ _pComm->sendServerSwitch ]);  // ����f�[�^�������O�o�b�t�@���獷���ւ���
            _setSendDataServer(_pComm->sSendServerBuf[ 1 - _pComm->sendServerSwitch ]);  // ����f�[�^�������O�o�b�t�@���獷���ւ���
        }
        _sendCallBackServer = _SEND_CB_NONE;
        // �ŏ��̑��M����
        _updateMpDataServer();
    }
}

//==============================================================================
/**
 * �ʐM����M�������ɌĂ΂��R�[���o�b�N
 * @param   result  ���������s
 * @retval  none
 */
//==============================================================================

#ifdef PM_DEBUG
static u8 debugHeadData[COMM_MACHINE_MAX][100];
static int debugCnt[COMM_MACHINE_MAX]={0,0,0,0,0,0,0,0};
static u8 debugHeadDataC[5][100];
static int debugCntC = 0;
#endif



//#define WIFI_DUMP_TEST

// ��M�R�[���o�b�N�^ �q�@���̎�M�� �e�@��192byte�݂̂̎�M�ƂȂ�
void CommRecvCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;

#ifdef WIFI_DUMP_TEST
//    if((adr[0] & 0xf) != 0xe){
 //       DEBUG_DUMP(&adr[0], 38,"cr0");
//    }
//    if((adr[38] & 0xf) != 0xe){
  //DEBUG_DUMP(&adr[38], 38,"cr1");
//    }
#endif

    if(_pComm->bPSendNoneRecv[COMM_PARENT_ID]){
        _pComm->countSendRecv--;  //��M
#ifdef PM_DEBUG
        _pComm->countRecvNum++;
#endif
        _pComm->bPSendNoneRecv[COMM_PARENT_ID] = FALSE;
        return;
    }
    _commRecvCallback(aid, data, size);
}
// �����炪�{�� ��̂�rapper
static void _commRecvCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;
    int i;
    int recvSize = size;

    _pComm->countSendRecv--;  //��M
#ifdef PM_DEBUG
    _pComm->countRecvNum++;
#endif
    if(adr==NULL){
        return;
    }

#ifdef PM_DEBUG
    debugHeadDataC[0][debugCntC] = adr[0];
    debugHeadDataC[1][debugCntC] = adr[1];
    debugHeadDataC[2][debugCntC] = adr[2];
    debugHeadDataC[3][debugCntC] = adr[3];
    debugHeadDataC[4][debugCntC] = adr[4];
    debugCntC++;
    if(debugCntC == 100){
        debugCntC = 0;
    }
#endif

    
//    if( !_pComm->bWifiSendRecv ){  // ����������ĂȂ�
    //DEBUG_DUMP(&adr[0], 16,"cr0");
    //DEBUG_DUMP(&adr[38], 16,"cr1");
//    }
    if(adr[0] == _MP_DATA_HEADER){   ///MP�f�[�^�̏ꍇ
        if(_transmissonType() == _DS_MODE){
            OHNO_PRINT("DS�Ȃ̂�MP�f�[�^������ \n");
            return;
        }
        adr++;
        recvSize--;
    }
    else if(_transmissonType() == _MP_MODE){  //DS�f�[�^�̏ꍇ
        OHNO_PRINT("MP�Ȃ̂�DEP�f�[�^������ \n");
        return;
    }
    if((_pComm->bFirstCatchP2C) && (adr[0] & _SEND_NEXT)){
        // �܂������f�[�^������������Ƃ��Ȃ���ԂȂ̂ɘA���f�[�^������
        OHNO_PRINT("�A���f�[�^ child %d \n",aid);
        DEBUG_DUMP((u8*)data,24,"cr");
        return;
    }
#if 0
    DEBUG_DUMP(adr,24,"cr");
#endif
    _pComm->bFirstCatchP2C = FALSE;

    if(_transmissonType() == _DS_MODE){
        int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

        for(i = 0; i < machineMax; i++){
            if(adr[0] == _INVALID_HEADER){
                _pComm->bitmap = _pComm->bitmap & ~(1<<i);
//                _pComm->DSCountRecv[i] = 0xff;
            }
            else{
                _pComm->bitmap = _pComm->bitmap | (1<<i);
            }
            if(adr[0] == _INVALID_HEADER){
                adr += mcSize;
            }
            else if(adr[0] == _NODATA_SEND){
                adr += mcSize;
//                OHNO_PRINT("--------------����f�[�^�Ȃ� %d\n",i);
            }
            else if((_pComm->bFirstCatch[i]) && (adr[0] & _SEND_NEXT)){ // �܂������f�[�^������������Ƃ��Ȃ���ԂȂ̂ɘA���f�[�^������
                OHNO_PRINT("�A���f�[�^ parent %d \n",aid);
                adr += mcSize;
            }
            else{
#if 0
                u8 cnt = ((adr[0] >> 4)  & 0xf);
                if(_pComm->DSCountRecv[i] != 0xff){
                    if(cnt > _pComm->DSCountRecv[i]){
                        if((cnt-1)!=_pComm->DSCountRecv[i]){
                            OHNO_PRINT("�R�}���h����  %d %d %d\n",i,cnt-1,_pComm->DSCountRecv[i]);
                            DEBUG_DUMP((u8*)data,size,"�R�}���h����");
                            GF_ASSERT((cnt-1)==_pComm->DSCountRecv[i]);
                        }
                    }
                    else{
                        if((cnt!=0) || (_pComm->DSCountRecv[i]!=0xf)){
                            OHNO_PRINT("�R�}���h����  %d %d %d\n",i,cnt-1,_pComm->DSCountRecv[i]);
                            DEBUG_DUMP((u8*)data,size,"�R�}���h����");
                        }
                        GF_ASSERT((cnt==0) && (_pComm->DSCountRecv[i]==0xf));
                    }
                }
                _pComm->DSCountRecv[i] = cnt;
#endif
                adr++;
                CommRingPuts(&_pComm->recvServerRing[i], adr, mcSize-1, __LINE__);
                adr += (mcSize-1);
                _pComm->bFirstCatch[i]=FALSE;
            }
        }
    }
    else{   //MP�f�[�^
#if _COMMAND_TEST
        DEBUG_DUMP(adr,recvSize,"�q�@�f�[�^��M");
#endif
//        DEBUG_DUMP(adr,recvSize,"�q�@�f�[�^��M");
        
        adr++;      // �w�b�_�[�P�o�C�g�ǂݔ�΂�
        _pComm->bitmap = adr[0];
        _pComm->bitmap *= 256;
        adr++;   // Bitmap�Ł[��
        _pComm->bitmap += adr[0];
        adr++;   // Bitmap�Ł[��
        recvSize -= 3;
        //    OHNO_PRINT("bitmap %x\n",_pComm->bitmap);
        recvSize = adr[0]; 
        adr++;
        //if(recvSize > CommRingDataRestSize(&_pComm->recvRing)){
          //  GF_ASSERT_RETURN("Error:��M�I�[�o�[\n",);
        //}
        CommRingPuts(&_pComm->recvRing , adr, recvSize, __LINE__);
    }
}


//==============================================================================
/**
 * �ʐM����M�������ɌĂ΂��R�[���o�b�N
 * @param   result  ���������s
 * @retval  none
 */
//==============================================================================

// ��M�R�[���o�b�N�^  �e�@�p
void CommRecvParentCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;
#ifdef WIFI_DUMP_TEST
//   if((adr[0] & 0xf) != 0xe){
    if(aid == 1){
        DEBUG_DUMP(&adr[0], 38,"pr1");
        OHNO_PRINT("adr %x size %d\n",(u32)data, size);
    }
    else{
        DEBUG_DUMP(&adr[0], 38,"pr0");
    }
//   }
#endif

    if(_pComm->bPSendNoneRecv[aid]){
        _pComm->countSendRecvServer[aid]--;  //SERVER��M
#ifdef PM_DEBUG
        _pComm->countRecvNumServer[aid]++;
#endif
        _pComm->bPSendNoneRecv[aid] = FALSE;
        return;
    }


    _commRecvParentCallback(aid, data, size);
}


static void _commRecvParentCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;
    int i;

    _pComm->countSendRecvServer[aid]--;  //SERVER��M
#ifdef PM_DEBUG
    _pComm->countRecvNumServer[aid]++;
#endif
    if(adr==NULL){
        return;
    }

#ifdef PM_DEBUG
    debugHeadData[aid][debugCnt[aid]] = adr[0];
    debugCnt[aid]++;
    if(debugCnt[aid]==100){
        debugCnt[aid] = 0;
    }
#endif
    
    if((_pComm->bFirstCatch[aid]) && (adr[0] & _SEND_NEXT)){
        // �܂������f�[�^������������Ƃ��Ȃ���ԂȂ̂ɘA���f�[�^������
        OHNO_PRINT("�A���f�[�^ parent %d \n",aid);
        i = 0;
        DEBUG_DUMP(adr,12,"�A���f�[�^");
        return;
    }
    _pComm->bFirstCatch[aid] = FALSE;

    if(_transmissonType() == _DS_MODE){
        int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
#if 0
        if((aid == 1) && ((adr[0] & 0x0f)== _SEND_NEXT)){
           DEBUG_DUMP(&adr[1],mcSize-1,"poke");
        }
   //     if(aid == 0){
   //         DEBUG_DUMP(adr,mcSize,"�e�@��DS");
  //      }
#endif
#if 0
        for(i = 1;i < mcSize; i++){
            if(adr[i] != CS_NONE){  //�����������Ă��Ă���
                CommRingPuts(&_pComm->recvMidRing[aid] , adr, mcSize, __LINE__);
                //OHNO_SP_PRINT("middle %d %d\n",CommRingDataSize(&_pComm->recvMidRing[aid]),aid);
//                OHNO_PRINT(" �܂�܂ܒ��ԃ����O�ɓ���� %d %d \n", aid, CommRingDataSize(&_pComm->recvMidRing[aid]));
                break;
            }
        }
#endif
        if(!(adr[0] & _SEND_NO_DATA)){
            CommRingPuts(&_pComm->recvMidRing[aid] , adr, mcSize, __LINE__);
//            OHNO_PRINT("MidRing�̂���%d\n",CommRingDataRestSize(&_pComm->recvMidRing[aid]));
        }
        _pComm->recvDSCatchFlg[aid]++;  // �ʐM������������Ƃ��L��
    }else{   // MP���[�h
        _padDataRecv(adr, aid);
        if(adr[0] & _SEND_NO_DATA){   // �f�[�^������ۂ̏ꍇ�󂯎��Ȃ�
            return;
        }
        adr++;
        if(_RECV_BUFF_SIZE_PARENT > CommRingDataRestSize(&_pComm->recvServerRing[aid])){
            OHNO_PRINT("Error Throw:��M�I�[�o�[\n");
            return;
        }
//        if(aid==0)
//            DEBUG_DUMP(adr,_RECV_BUFF_SIZE_PARENT,"MP �󂯎����");
        CommRingPuts(&_pComm->recvServerRing[aid] , adr, _RECV_BUFF_SIZE_PARENT, __LINE__);
    }
}

//==============================================================================
/**
 * �ʐM�𑗐M�����Ƃ��ɌĂ΂��R�[���o�b�N
 * @param   result  ���������s
 * @retval  none
 */
//==============================================================================

static void _sendCallbackFunc(BOOL result)
{
    if(result){
        _sendCallBack++;
    }
    else{
        GF_ASSERT_MSG(0,"send failed");
    }
}

//==============================================================================
/**
 * �ʐM�𑗐M�����Ƃ��ɌĂ΂��R�[���o�b�N 
 * @param   result  ���������s
 * @retval  none
 */
//==============================================================================

static void _sendServerCallback(BOOL result)
{
    if(result){
        _sendCallBackServer++;
    }
    else{
        GF_ASSERT_MSG(0,"send failed");
    }
}

//==============================================================================
/**
 * �f�[�^�̎��W
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _updateMpData(void)
{
    u16 i;
    u8 *adr;
    int size;

    if(!_pComm){
        return;
    }
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        return;
    }
    {
        int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
        if(CommGetAloneMode()){   // alone���[�h�̏ꍇ
            if((_sendCallBack == _SEND_CB_FIRST_SENDEND) || (_sendCallBack == _SEND_CB_NONE)){
                _sendCallBack++;
                _sendCallbackFunc(TRUE);
                // �q�@�̂ӂ�����镔��          // �e�@�͎����ŃR�[���o�b�N���Ă�
                _commRecvParentCallback(COMM_PARENT_ID, (u16*)_pComm->sSendBuf[_pComm->sendSwitch],
                                    mcSize);
                _pComm->sendSwitch = 1 - _pComm->sendSwitch;
                _pComm->countSendRecv++; // MP���M�e
#ifdef PM_DEBUG
                _pComm->countSendNum++;
#endif
                return;
            }
        }
        if(WH_GetSystemState() == WH_SYSSTATE_CONNECTED ){
            if(!CommIsConnect(CommGetCurrentID())){
                if(CommGetCurrentID()==1){
                    OHNO_PRINT("�������g�̐ڑ����܂�\n");
                }
                return;
            }
            if((_sendCallBack == _SEND_CB_FIRST_SENDEND) || (_sendCallBack == _SEND_CB_NONE)){
                // �q�@�f�[�^���M
                if(CommGetCurrentID() != COMM_PARENT_ID){
                    _sendCallBack++;
                    if(!WH_SendData(_pComm->sSendBuf[_pComm->sendSwitch],
                                    mcSize, _PORT_DATA_CHILD, _sendCallbackFunc)){
                        _sendCallBack--;
                        OHNO_PRINT("failed WH_SendData\n");
                    }
                    else{
                        _pComm->sendSwitch = 1 - _pComm->sendSwitch;
                        _pComm->countSendRecv++; // MP���M
#ifdef PM_DEBUG
                        _pComm->countSendNum++;
#endif
                    }
                }
                else if(WH_GetBitmap() & 0xfffe){         // �T�[�o�[�Ƃ��Ă̏��� �����ȊO�̒N���ɂȂ����Ă��鎞
                    _sendCallBack++;
                    _sendCallbackFunc(TRUE);
                    // �q�@�̂ӂ�����镔��          // �e�@�͎����ŃR�[���o�b�N���Ă�
                    _commRecvParentCallback(COMM_PARENT_ID, (u16*)_pComm->sSendBuf[_pComm->sendSwitch],
                                        mcSize);
                    _pComm->sendSwitch = 1 - _pComm->sendSwitch;
                    _pComm->countSendRecv++; // MP���M
#ifdef PM_DEBUG
                    _pComm->countSendNum++;
#endif
                }
            }
            else{
//                OHNO_PRINT("sendCallBack != _SEND_CB_FIRST_SENDE\n");
            }
        }
    }
}

//==============================================================================
/**
 * �L�[�̗����𔭐����� �L�[�����͂��ꂽ����������
 * @param   none
 * @retval  �G���[�̎�TRUE
 */
//==============================================================================

static void _keyRand(void)
{
    u16 pad = 0;

    if(_pComm->randPadType == _NONE_KEY){
        return;
    }
    if(!(_pComm->sendCont &
         (PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_KEY_UP|PAD_KEY_DOWN))){
        return;  // �L�[������ĂȂ��ꍇ�͂������g�p���Ȃ�
    }
    if(_pComm->randPadType == _REVERSE_KEY){   // ���o�[�X���[�h
        if(_pComm->sendCont & PAD_KEY_LEFT){
            pad |= PAD_KEY_RIGHT;
        }
        if(_pComm->sendCont & PAD_KEY_RIGHT){
            pad |= PAD_KEY_LEFT;
        }
        if(_pComm->sendCont & PAD_KEY_UP){
            pad |= PAD_KEY_DOWN;
        }
        if(_pComm->sendCont & PAD_KEY_DOWN){
            pad |= PAD_KEY_UP;
        }
    }
    else{
        if(_pComm->oldPad){   // �����_�����[�h
            pad = _pComm->oldPad;
            _pComm->randPadStep--;
            if(_pComm->randPadStep < 0){
                _pComm->oldPad = 0;
            }
        }
        else{
            switch(MATH_Rand32(&_pComm->sRand, 4)){
              case 0:
                pad = PAD_KEY_LEFT;
                break;
              case 1:
                pad = PAD_KEY_RIGHT;
                break;
              case 2:
                pad = PAD_KEY_UP;
                break;
              case 3:
                pad = PAD_KEY_DOWN;
                break;
            }
            _pComm->randPadStep = MATH_Rand32(&_pComm->sRand, 16);
            _pComm->oldPad = pad;
        }
    }
    _pComm->sendCont &= ~(PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_KEY_UP|PAD_KEY_DOWN);
    _pComm->sendCont += pad;
}

//==============================================================================
/**
 * �L�[�������_�����[�h�ɂ���
 * @param   none
 * @retval  �G���[�̎�TRUE
 */
//==============================================================================

void CommSetKeyRandMode(void)
{
    _pComm->randPadType = _RANDOM_KEY;
}

void CommSetKeyReverseMode(void)
{
    _pComm->randPadType = _REVERSE_KEY;
}

void CommResetKeyRandMode(void)
{
    _pComm->randPadType = _NONE_KEY;
}


#define _COMM_DIR_UP  (0x00)
#define _COMM_DIR_DOWN  (0x04)
#define _COMM_DIR_LEFT  (0x08)
#define _COMM_DIR_RIGHT  (0x0C)
#define _COMM_SEND_KEY   (0x10)


//==============================================================================
/**
 * @brief   sendBuff �O�̂��܂�BIT���g�p���� �L�[�f�[�^����M����
 *
 * @param   pRecvBuff  �󂯎��o�b�t�@
 * @param   netID      netID
 * @retval  ����FALSE�̂�
 */
//==============================================================================

static BOOL _padDataRecv(u8* pRecvBuff, int netID)
{
    int i;
    u8 keyBuff[2];

    _pComm->cont[netID] = 0;
    if(_COMM_SEND_KEY == (*pRecvBuff & _COMM_SEND_KEY)){
        keyBuff[ 0 ] = *pRecvBuff & 0x0c;
        if(keyBuff[ 0 ] == _COMM_DIR_UP){
            _pComm->cont[netID] |= PAD_KEY_UP;
        }
        else if(keyBuff[ 0 ] == _COMM_DIR_DOWN){
            _pComm->cont[netID] |= PAD_KEY_DOWN;
        }
        else if(keyBuff[ 0 ] == _COMM_DIR_LEFT){
            _pComm->cont[netID] |= PAD_KEY_LEFT;
        }
        else if(keyBuff[ 0 ] == _COMM_DIR_RIGHT){
            _pComm->cont[netID] |= PAD_KEY_RIGHT;
        }
        _pComm->speed[netID] = (*pRecvBuff >> 5) & 0x7;
    }
//    _pComm->trg[netID] = _pComm->contOld[netID] ^ _pComm->cont[netID];
  //  _pComm->contOld[netID] = _pComm->cont[netID];
    return TRUE;

    
#if 0
    // 1/60�̒ʐM���� pad��1/30�����K�v�Ȃ��̂ŊԈ�������
    _pComm->padGetSwitch[netID] = _pComm->padGetSwitch[netID] ? FALSE : TRUE;
    if(_pComm->padGetSwitch[netID]){
        return FALSE;
    }
    
    _pComm->cont[netID] = 0;
    keyBuff[0] = *pRecvBuff;

    // BIT�i�[
    for( i = 0; i < sizeof(_sendPadBit)/sizeof(u16); i++ ){
        if(keyBuff[ _sendPattern[i][0] ] & _sendPattern[i][1]){
            _pComm->cont[netID] |= _sendPadBit[i];
        }
    }
//    _pComm->trg[netID] = _pComm->contOld[netID] ^ _pComm->cont[netID];
//    _pComm->contOld[netID] = _pComm->cont[netID];
    return FALSE;
#endif
}

//==============================================================================
/**
 * @brief   �q�@���̃A�N�V�������s��ꂽ���Ƃ�ݒ�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommActionCommandSet(void)
{
//    _pComm->actionCount = _ACTION_COUNT_MOVE;
}

//==============================================================================
/**
 * @brief   sendBuff �O�̂��܂�BIT+1byte���g�p���� �L�[�f�[�^�𑗐M����
 *          �ړ��ɕK�v�ȕ����L�[ + Y �̂ݑ����Ă���  trg cont�𑗐M����̂�
 *          �L�[��������Ă���ꍇ�ɑ��M�ʂ�1byte�ω�����
 * @param   sendSwitch  ����o�b�t�@�̃X�C�b�`
 * @retval  1�o�C�g�������M����ꍇ1
 */
//==============================================================================

static BOOL _padDataSend(u8* pSendBuff)
{
    int i,k;
/*
    if(_pComm->actionCount != 0 ){
        _pComm->actionCount--;
        return FALSE;
    }
   */
#ifdef DEBUG_ONLY_FOR_ohno
    if(sys.cont & PAD_BUTTON_START){
        if(CommIsSendMoveData()==FALSE){
            OHNO_PRINT("CommIsSendMoveData()==FALSE\n");
        }
        else{
            OHNO_PRINT("CommIsSendMoveData()==TRUE\n");
        }
    }
#endif
    if(_pComm->sendKeyStop){
        return FALSE;
    }
    
    if(CommIsSendMoveData()==FALSE){
        return FALSE;  // ����̓p�b�h�f�[�^�͑��M���Ȃ�
    }
#if 0
    // BIT�i�[
    for( i = 0; i < sizeof(_sendPadBit)/sizeof(u16); i++ ){
        if(_pComm->sendCont & _sendPadBit[i]){
            pSendBuff[ _sendPattern[i][0] ] |= _sendPattern[i][1];
        }
    }
#endif
    if(_pComm->timSendCond){
        _pComm->timSendCond--;
    }
    if(_pComm->sendCont & PAD_KEY_UP){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_UP | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    else if(_pComm->sendCont & PAD_KEY_DOWN){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_DOWN | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    else if(_pComm->sendCont & PAD_KEY_LEFT){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_LEFT | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    else if(_pComm->sendCont & PAD_KEY_RIGHT){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_RIGHT | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    pSendBuff[ 0 ] |= (_pComm->sendSpeed << 5);
    return FALSE;
}

//==============================================================================
/**
 * ���M�L���[�ɂ��������̂𑗐M�o�b�t�@�ɓ����
 * @param   none
 * @retval  none
 */
//==============================================================================

static BOOL _setSendData(u8* pSendBuff)
{
    int i;
    int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
    int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
    if(_pComm->bNextSendData == FALSE){  // ���ő����ꍇ
        pSendBuff[0] = _SEND_NONE;
    }
    else{
        pSendBuff[0] = _SEND_NEXT;  // ���ő���Ȃ��ꍇ
    }
    if(_transmissonType() == _MP_MODE){  // DS���̓p�b�g�𑗂�BIT�������̂ő���Ȃ�
        _padDataSend(pSendBuff);  // �p�b�h�f�[�^�𑗐M����
    }
    _pComm->bNextSendData = FALSE;
#if 0
    if(CommQueueIsEmpty(&_pComm->sendQueueMgr) && (_transmissonType() == _MP_MODE)){
        pSendBuff[0] |= _SEND_NO_DATA;  // ����ۂȂ牽������Ȃ�
    }
#endif
    if(CommQueueIsEmpty(&_pComm->sendQueueMgr)){
        pSendBuff[0] |= _SEND_NO_DATA;  // ����ۂȂ牽������Ȃ�
        if(pSendBuff[0] == _SEND_NO_DATA){
            return FALSE;  // ������̂���������
        }
    }
    else{
        SEND_BUFF_DATA buffData;
        buffData.size = mcSize - 1;
        buffData.pData = &pSendBuff[1];
        if(!CommQueueGetData(&_pComm->sendQueueMgr, &buffData, TRUE)){
            _pComm->bNextSendData = TRUE;
        }
        if(_transmissonType() == _DS_MODE){
            _pComm->DSCount++;
//            OHNO_PRINT("DS�f�[�^�Z�b�g %d\n",_pComm->DSCount);
            pSendBuff[0] |= ((_pComm->DSCount << 4) & 0xf0);  //DS�ʐM���ԃJ�E���^
        }
    }
#if 0
    if(CommGetCurrentID()==0){
        DEBUG_DUMP(pSendBuff,mcSize,"_setSendData");
    }
#endif
    return TRUE;
}

//==============================================================================
/**
 * ���M�L���[�ɂ��������̂𑗐M�o�b�t�@�ɓ���� �T�[�o�[MP�ʐM�p
 * @param   pSendBuff ����鑗�M�o�b�t�@
 * @retval  none
 */
//==============================================================================



static void _setSendDataServer(u8* pSendBuff)
{
    int i;

    pSendBuff[0] = _MP_DATA_HEADER;

#ifdef PM_DEBUG
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        if(_sendDataNext != _pComm->bNextSendDataServer){
            GF_ASSERT(0);
        }
    }
#endif

    if(_pComm->bNextSendDataServer == FALSE){  // ���ő����ꍇ
        pSendBuff[1] = _SEND_NONE;
    }
    else{
        pSendBuff[1] = _SEND_NEXT;  // ���ő���Ȃ��ꍇ
    }

    {
        u16 bitmap = WH_GetBitmap();
        pSendBuff[2] = bitmap >> 8;
        pSendBuff[3] = bitmap & 0xff;

        {
            SEND_BUFF_DATA buffData;
            buffData.size = _SEND_BUFF_SIZE_PARENT - 5;
            buffData.pData = &pSendBuff[5];
            if(CommQueueGetData(&_pComm->sendQueueMgrServer, &buffData, FALSE)){
                _pComm->bNextSendDataServer = FALSE;
                pSendBuff[4] = (_SEND_BUFF_SIZE_PARENT - 5) - buffData.size;
            }
            else{
                _pComm->bNextSendDataServer = TRUE;
                pSendBuff[4] = _SEND_BUFF_SIZE_PARENT - 5;
            }
#ifdef PM_DEBUG
            _sendDataNext = _pComm->bNextSendDataServer;
#endif

        }
    }
#if 0
    DEBUG_DUMP(pSendBuff, _SEND_BUFF_SIZE_PARENT, "MP SERVER SEND");
#endif
}


//==============================================================================
/**
 * �q�@���M���\�b�h  �傫���T�C�Y�̃f�[�^�𑗐M����
 *     �o�b�N�A�b�v���Ȃ��̂� data�̒��g������������ƁA
 *     �������������̂𑗂��Ă��܂��\��������
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendHugeData(int command, const void* data, int size)
{
    if(!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode()){
        //        OHNO_PRINT("�ڑ����ĂȂ��đ���Ȃ�����\n");
        return FALSE;   // �ʐM��Ԃ������ꍇ����Ȃ�
    }
    if(CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, TRUE, FALSE)){
//        if(25 == command){
            //OHNO_SP_PRINT("%d ",CommGetCurrentID());
            //DEBUG_DUMP((u8*)data,size,"poke");
  //      }
#if _COMMAND_TEST
        OHNO_PRINT("<<<���M NetId=%d -- size%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("-�L��- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgr));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * �q�@���M���\�b�h
 * �e�@���f�[�^���q�@�S���ɑ��M����͕̂ʊ֐�
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendData(int command, const void* data, int size)
{
    OHNO_PRINT("< ���M %d %d\n", command,CommQueueGetNowNum(&_pComm->sendQueueMgr));
//    GF_ASSERT_RETURN(size < 256 && "CommSendHugeData���g���Ă�������",FALSE);
    if(!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode()){
        OHNO_PRINT("�ڑ����ĂȂ��đ���Ȃ�����\n");
        return FALSE;   // �ʐM��Ԃ������ꍇ����Ȃ�
    }
    if(CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, TRUE, TRUE)){
#if _COMMAND_TEST
        OHNO_PRINT("<<<���M NetId=%d -- size%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("-�L���[����- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgr));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}


//==============================================================================
/**
 * �e�@��p�T�[�o�[���M���\�b�h
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

static BOOL _data_ServerSide(int command, const void* data, int size, BOOL bCopy)
{
    if(CommGetCurrentID() != COMM_PARENT_ID){  // �e�@�ȊO�͎g���Ȃ�
        GF_ASSERT(0 && "�e�ȊO�͎g�p�s��");
        return FALSE;
    }
    if(!CommIsConnect(COMM_PARENT_ID)  && !CommGetAloneMode()){
//        OHNO_PRINT("�ڑ����ĂȂ��đ���Ȃ�����\n");
        return FALSE;   // �ʐM��Ԃ������ꍇ����Ȃ�
    }
    if(_transmissonType() == _DS_MODE){
        OHNO_PRINT("WARRNING: DS�ʐM��ԂȂ̂ɃT�[�o�[���M���g��ꂽ\n");
        return CommSendData(command, data, size);
    }

    if(CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, bCopy)){
#if _COMMAND_TEST
        OHNO_PRINT("<<S���M id=%d size=%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
//        DEBUG_DUMP(pSend, size, "S���M");
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * �e�@���M���\�b�h  �傫���T�C�Y�̃f�[�^�𑗐M����  �T�C�Y�Œ�
 *     �o�b�N�A�b�v���Ȃ��̂� data�̒��g������������ƁA
 *     �������������̂𑗂��Ă��܂��\��������
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendFixHugeSizeData_ServerSide(int command, const void* data)
{
    return CommSendHugeData_ServerSide(command, data, 0);
}

//==============================================================================
/**
 * �e�@���M���\�b�h  �傫���T�C�Y�̃f�[�^�𑗐M����
 *     �o�b�N�A�b�v���Ȃ��̂� data�̒��g������������ƁA
 *     �������������̂𑗂��Ă��܂��\��������
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendHugeData_ServerSide(int command, const void* data, int size)
{
    if(CommGetCurrentID() != COMM_PARENT_ID){  // �e�@�ȊO�͎g���Ȃ�
        GF_ASSERT(0 && "�e�ȊO�͎g�p�s��");
        return FALSE;
    }
    if(!CommIsConnect(COMM_PARENT_ID)  && !CommGetAloneMode()){
//        OHNO_PRINT("�ڑ����ĂȂ��đ���Ȃ�����\n");
        return FALSE;   // �ʐM��Ԃ������ꍇ����Ȃ�
    }
    if(_transmissonType() == _DS_MODE){
        OHNO_PRINT("WARRNING: DS�ʐM��ԂȂ̂ɃT�[�o�[���M���g��ꂽ\n");
        return CommSendHugeData(command, data, size);
    }

    if(CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, FALSE)){
#if 0
        OHNO_PRINT("<<S���M id=%d size=%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
//        DEBUG_DUMP(pSend, size, "S���M");
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("-�L������- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgrServer));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * �e�@��p�T�[�o�[���M���\�b�h
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendData_ServerSide(int command, const void* data, int size)
{
    if(CommGetCurrentID() != COMM_PARENT_ID){  // �e�@�ȊO�͎g���Ȃ�
        CommSetError();
//        GF_ASSERT(0 && "�e�ȊO�͎g�p�s��");
        return FALSE;
    }
    if(!CommIsConnect(COMM_PARENT_ID)  && !CommGetAloneMode()){
        OHNO_PRINT("�ڑ����ĂȂ��đ���Ȃ�����\n");
        return FALSE;   // �ʐM��Ԃ������ꍇ����Ȃ�
    }
    if(_transmissonType() == _DS_MODE){
        OHNO_PRINT("WARRNING: DS�ʐM��ԂȂ̂ɃT�[�o�[���M���g��ꂽ\n");
        return CommSendData(command, data, size);
    }

    if(CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, TRUE)){

//        OHNO_PRINT("qnum %d %d\n",command,CommQueueGetNowNum(&_pComm->sendQueueMgrServer));

#if _COMMAND_TEST
        OHNO_PRINT("<<S���M id=%d size=%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
//        DEBUG_DUMP(pSend, size, "S���M");
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("�L���[����- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgrServer));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * �e�@��p�T�[�o�[���M���\�b�h �T�C�Y�Œ��
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendFixSizeData_ServerSide(int command, const void* data)
{
    return CommSendData_ServerSide(command, data, 0);
}

//==============================================================================
/**
 * ���M�o�b�t�@�c��e��
 * @retval  �T�C�Y
 */
//==============================================================================

int CommGetSendRestSize(void)
{
    return CommRingDataRestSize(&_pComm->sendRing);
}

//==============================================================================
/**
 * �T�[�o���̑��M�o�b�t�@�c��e��
 * @retval  �T�C�Y
 */
//==============================================================================

int CommGetSendRestSize_ServerSide(void)
{
    return CommRingDataRestSize(&_pComm->sendServerRing);
}


static void _endCallBack(int netID,int command,int size,void* pTemp, _RECV_COMMAND_PACK* pRecvComm)
{
    CommCommandCallBack(netID, command, size, pTemp);
    pRecvComm->valCommand = CS_NONE;
    pRecvComm->valSize = 0xffff;
    pRecvComm->pRecvBuff = NULL;
    pRecvComm->dataPoint = 0;
}


//==============================================================================
/**
 * ��M�����f�[�^���v���Z�X���ɏ�������
 * @param   pRing  �����O�o�b�t�@�̃|�C���^
 * @param   netID     �������Ă���netID
 * @param   pTemp    �R�}���h���������邽�߂�temp�o�b�t�@
 * @retval  none
 */
//==============================================================================

static void _recvDataFuncSingle(RingBuffWork* pRing, int netID, u8* pTemp, BOOL bDebug, _RECV_COMMAND_PACK* pRecvComm)
{
    int size;
    u8 command;
    int bkPos;
    int realbyte;

    
    while( CommRingDataSize(pRing) != 0 ){
        bkPos = pRing->startPos;
        if(pRecvComm->valCommand != CS_NONE){
            command = pRecvComm->valCommand;
        }
        else{
            command = CommRingGetByte(pRing);
            if(command == CS_NONE){
                continue;
            }
        }
        bkPos = pRing->startPos;
        pRecvComm->valCommand = command;
//        OHNO_PRINT("c %d\n",command);
        if(bDebug){
            OHNO_PRINT(">>>cR %d %d %d\n", bkPos, CommRingDataSize(pRing), command);
        }
        if(pRecvComm->valSize != 0xffff){
            size = pRecvComm->valSize;
        }
        else{
            size = CommCommandGetPacketSize(command);
            if(_pComm->bError){
                return;
            }
            if(COMM_VARIABLE_SIZE == size){
                if( CommRingDataSize(pRing) < 1 ){  // �c��f�[�^��1�ȉ�������
                    pRing->startPos = bkPos;
                    break;
                }
                // �T�C�Y���Ȃ��ʐM�f�[�^�͂����ɃT�C�Y�������Ă���
                size = CommRingGetByte(pRing)*0x100;
                size += CommRingGetByte(pRing);
                OHNO_PRINT("��M�T�C�Y  %d\n",size);
                bkPos = pRing->startPos; // �Q�i�߂�
            }
            pRecvComm->valSize = size;
        }
        if(CommCommandCreateBuffCheck(command)){  // ��M�o�b�t�@������ꍇ
            if(pRecvComm->pRecvBuff==NULL){
                pRecvComm->pRecvBuff = CommCommandCreateBuffStart(command, netID, pRecvComm->valSize);
            }
            realbyte = CommRingGets(pRing, pTemp, size - pRecvComm->dataPoint);
//            OHNO_SP_PRINT("id %d -- rest %d\n",netID, size - pRecvComm->dataPoint);
            if(pRecvComm->pRecvBuff){
                MI_CpuCopy8(pTemp, &pRecvComm->pRecvBuff[pRecvComm->dataPoint], realbyte);
            }
            pRecvComm->dataPoint += realbyte;
            if(pRecvComm->dataPoint >= size ){

//                if(25 == command){
  //                  OHNO_SP_PRINT("%d ",netID);
    //                DEBUG_DUMP(pRecvComm->pRecvBuff,size,"recv");
      //          }
                
                _endCallBack(netID, command, size, pRecvComm->pRecvBuff, pRecvComm);
            }
        }
        else{
            if( CommRingDataSize(pRing) >= size ){
                if(bDebug){
                    OHNO_PRINT(">>>��M comm=%d id=%d -- size%d \n",command, netID, size);
                }
                CommRingGets(pRing, pTemp, size);
                _endCallBack(netID, command, size, (void*)pTemp, pRecvComm);
            }
            else{   // �܂��͂��Ă��Ȃ��傫���f�[�^�̏ꍇ�ʂ���
                //            OHNO_PRINT("�����҂� command %d size %d\n",command,size);
                pRing->startPos = bkPos;
                break;
            }
        }
    }
}

//==============================================================================
/**
 * ��M�����f�[�^���v���Z�X���ɏ�������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _recvDataFunc(void)
{
    int id = COMM_PARENT_ID;
    int size;
    u8 command;
    int bkPos;

    if(!_pComm){
        return;
    }
    if(_pComm->bNotRecvCheck){
        return;
    }

    CommRingEndChange(&_pComm->recvRing);
    if(CommRingDataSize(&_pComm->recvRing) > 0){
        // ��O�̈ʒu��ϐ��ɕۑ����Ă���
//        MI_CpuCopy8( &_pComm->recvRing,&_pComm->recvRingUndo, sizeof(RingBuffWork));
//        CommRingStartPush(&_pComm->recvRingUndo); //start�ʒu��ۑ�
#if 0
        OHNO_PRINT("-��͊J�n %d %d-%d\n",id,
                   _pComm->recvRing.startPos,_pComm->recvRing.endPos);
#endif
//        OHNO_PRINT("�q�@��� %d \n",id);
        _recvDataFuncSingle(&_pComm->recvRing, id, _pComm->pTmpBuff, TRUE, &_pComm->recvCommClient);
#if 0
        OHNO_PRINT("��� %d %d-%d\n",id,
                   _pComm->recvRing.startPos,_pComm->recvRing.endPos);
#endif
    }
}

//==============================================================================
/**
 * ��M�����f�[�^���v���Z�X���ɏ�������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _recvDataServerFunc(void)
{
    int id;
    int size;
    u8 command;
    int machineMax;

    if(!_pComm){
        return;
    }
    if(_pComm->bNotRecvCheck){
        return;
    }

    machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

    for(id = 0; id < machineMax; id++){
        CommRingEndChange(&_pComm->recvServerRing[id]);
        
        if(CommRingDataSize(&_pComm->recvServerRing[id]) > 0){
#if 0
            OHNO_PRINT("��͊J�n %d %d-%d\n",id,
                       _pComm->recvServerRing[id].startPos,_pComm->recvServerRing[id].endPos);
#endif
#if 0
            OHNO_PRINT("�e�@���q�@%d�����\n",id);
#endif
#if _COMMAND_TEST
    //        OHNO_PRINT("DS��� %d\n",id);
#endif
            // ��O�̈ʒu��ϐ��ɕۑ����Ă���
//            MI_CpuCopy8(&_pComm->recvServerRing[id],
  //                      &_pComm->recvServerRingUndo[id],
    //                    sizeof(RingBuffWork));
      //      CommRingStartPush(&_pComm->recvServerRingUndo[id]); //start�ʒu��ۑ�
//            OHNO_PRINT("�e�@���q�@%d�����\n",id);
            _recvDataFuncSingle(&_pComm->recvServerRing[id], id, _pComm->pTmpBuff, FALSE, &_pComm->recvCommServer[id]);
        }
    }
}

//==============================================================================
/**
 * �f�[�^�������Ă������m�F����B
 * @param   netID       �e�@��_PARENT_INDEX�@���͎q�@
 * @param   command     ���̃f�[�^�������Ă����̂��ǂ������ח���
 * @param   retSsize    �����Ă����f�[�^�̃T�C�Y������
 * @param   data        �����Ă����f�[�^
 * @retval  �R�}���h�̃f�[�^���݂�����TRUE
 */
//==============================================================================
#if 0
BOOL CommRecvData(int netID,int chkCommand, int* retSize, u8* data)
{
    if(FALSE == CommIsConnect(netID)){
        return FALSE;
    }
    if(_transmissonType() == _DS_MODE){
        return CommGetRecvData_ServerSide(netID,chkCommand,retSize,data);
    }
    return _getRecvDataSingle(&_pComm->recvRingUndo,
                              chkCommand, retSize, data, _pComm->pTmpBuff);
}
#endif

//==============================================================================
/**
 * �f�[�^�������Ă������m�F����B�T�[�o�[��p
 * @param   netID       machine index
 * @param   command     ���̃f�[�^�������Ă����̂��ǂ������ח���
 * @param   retSsize    �����Ă����f�[�^�̃T�C�Y������
 * @param   data        �����Ă����f�[�^
 * @retval  �R�}���h�̃f�[�^���݂�����TRUE
 */
//==============================================================================
#if 0
BOOL CommGetRecvData_ServerSide(int netID,int chkCommand, int* retSize, u8* data)
{
    if(FALSE == CommIsConnect(netID)){
        return FALSE;
    }
    return _getRecvDataSingle(&_pComm->recvServerRingUndo[netID],
                              chkCommand, retSize, data, _pComm->pTmpBuff);
}
#endif
//==============================================================================
/**
 * �ʐM�\��ԂȂ̂��ǂ�����Ԃ� �������R�}���h�ɂ��l�S�V�G�[�V�������܂��̏��
 * @param   �e�q�@��netID
 * @retval  TRUE  �ʐM�\    FALSE �ʐM�ؒf
 */
//==============================================================================
BOOL CommIsConnect(u16 netID)
{
    if(!_pComm){
        return FALSE;
    }
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        if(_pComm->bWifiConnect){
            int id = mydwc_getaid();
            if(-1 != id){
                if(netID == 0){
                    return TRUE;
                }
                else if(netID == 1){
                    return TRUE;
                }
            }
        }
        return FALSE;
    }
    if(!CommIsInitialize()){
        return FALSE;
    }
    if (WH_GetSystemState() != WH_SYSSTATE_CONNECTED) {
        return FALSE;
    }
    if(CommGetCurrentID()==netID){// ������ONLINE
        return TRUE;
    }
    else if(CommGetCurrentID()==COMM_PARENT_ID){  // �e�@�̂ݎq�@����LIB�œ�����
        u16 bitmap = WH_GetBitmap();
        if( bitmap & (1<<netID)){
            return TRUE;
        }
    }
    else if(_pComm->bitmap & (1<<netID)){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �ʐM�\��Ԃ̐l����Ԃ�
 * @param   none
 * @retval  �ڑ��l��
 */
//==============================================================================
int CommGetConnectNum(void)
{
    int num = 0,i;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(CommIsConnect(i)){
            num++;
        }
    }
    return num;
}

//==============================================================================
/**
 * ���������Ă��邩�ǂ�����Ԃ�
 * @param   none
 * @retval  �������I����Ă�����TRUE
 */
//==============================================================================
BOOL CommIsInitialize(void)
{
    if(_pComm){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            return TRUE;
        }
    }
    return CommMPIsInitialize();
}

//==============================================================================
/**
 * �ړ����x������
 * @param   speed
 * @retval  
 */
//==============================================================================

void CommSetSpeed(u8 speed)
{
    _pComm->sendSpeed = speed;
}

//==============================================================================
/**
 * �ړ����x��Ԃ�
 * @param   netID     �l�b�gID
 * @retval  key cond
 */
//==============================================================================
u8 CommGetSpeed(int netID)
{
    return _pComm->speed[netID];
}

//==============================================================================
/**
 * �p�b�h�R���g���[����Ԃ�
 * @param   netID     �l�b�gID
 * @retval  key cond
 */
//==============================================================================
u16 CommGetPadCont(int netID)
{
    int cnt;

    if(!_pComm){
        return 0;
    }
    cnt = _pComm->cont[netID];
    _pComm->cont[netID] = 0;
    return cnt;
}

//==============================================================================
/**
 * �p�b�h�𑗐M�\�ɂ���
 * @param   netID     �l�b�gID
 * @retval  key cond
 */
//==============================================================================
void CommEnableSendMoveData(void)
{
    if(_pComm){
        _pComm->sendCont |= 0x8000;
    }
}

//==============================================================================
/**
 * �p�b�h�𑗐M�s�ɂ���
 * @param   netID     �l�b�gID
 * @retval  key cond
 */
//==============================================================================
void CommDisableSendMoveData(void)
{
    if(_pComm){
        _pComm->sendCont = 0;
    }
}

//==============================================================================
/**
 * �p�b�h�𑗐M�s�ɂ���
 * @param   netID     �l�b�gID
 * @retval  key cond
 */
//==============================================================================
void CommStopSendMoveData(BOOL bStop)
{
    if(_pComm){
        _pComm->sendKeyStop = bStop;
    }
}

//==============================================================================
/**
 * �p�b�h�𑗐M�s�ɂ��Ă��邩�ǂ����𓾂�
 * @param   netID     �l�b�gID
 * @retval  key cond
 */
//==============================================================================
BOOL CommIsSendMoveData(void)
{
    if(_pComm){
        return (_pComm->sendCont & 0x8000);
    }
    return TRUE;
}

//==============================================================================
/**
 * �T�[�o�[������q�@�ɑ���ꍇ ���M�L���[�ւ̒ǉ�
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   sendNetID
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 *                     ���̃f�[�^�͐ÓI�łȂ���΂Ȃ�Ȃ�  �o�b�t�@�ɗ��߂Ȃ�����
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSetSendQueue_ServerSide(int command, const void* data, int size)
{
    if(_transmissonType() == _DS_MODE){
        return CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, TRUE, FALSE);
    }
    else{
        return CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, FALSE);
    }
}

//==============================================================================
/**
 * �N���C�A���g������e�@�ɑ���ꍇ ���M�L���[�ւ̒ǉ�
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 *                     ���̃f�[�^�͐ÓI�łȂ���΂Ȃ�Ȃ�  �o�b�t�@�ɗ��߂Ȃ�����
 * @param   byte       ���M��    �R�}���h�����̏ꍇ0
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSetSendQueue(int command, const void* data, int size)
{
    return CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, FALSE, FALSE);
}

enum{
    _TRANS_NONE,
    _TRANS_LOAD,
    _TRANS_LOAD_END,
    _TRANS_SEND,
    _TRANS_SEND_END,
};


static void _transmission(void)
{
    BOOL bCatch=FALSE;

    if(!_pComm){
        return;
    }
    
    switch(_pComm->transmissionNum){
      case _TRANS_LOAD:
        if(_transmissonType() == _DS_MODE){
            bCatch = CommSendFixSizeData(CS_DSMP_CHANGE_REQ,&_pComm->transmissionSend);
        }
        else{
            bCatch = CommSendData_ServerSide(CS_DSMP_CHANGE_REQ, &_pComm->transmissionSend, 1);
        }
        if(bCatch){
            _pComm->transmissionNum = _TRANS_LOAD_END;
        }
        break;
      case _TRANS_SEND:
        if(CommSendFixSizeData(CS_DSMP_CHANGE_END,&_pComm->transmissionSend)){
            _commSetTransmissonType(_pComm->transmissionSend);  // �؂�ւ���  �e�@�͂����Ő؂�ւ��Ȃ�
            _pComm->transmissionNum = _TRANS_NONE;
        }
        break;
    }

}

//==============================================================================
/**
 * DS�ʐMMP�ʐM�̐؂�ւ�  CS_DSMP_CHANGE
 * @param   none
 * @retval  �c�萔
 */
//==============================================================================

void CommRecvDSMPChange(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
    OHNO_PRINT("CommRecvDSMPChange ��M\n");
    _pComm->transmissionNum = _TRANS_LOAD;
    _pComm->transmissionSend = pBuff[0];
}

//==============================================================================
/**
 * DS�ʐMMP�ʐM�̐؂�ւ�
 * @param   none
 * @retval  �c�萔
 */
//==============================================================================

void CommRecvDSMPChangeReq(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() == COMM_PARENT_ID){
        return;
    }
    _pComm->transmissionSend = pBuff[0];
    _pComm->transmissionNum = _TRANS_SEND;
    OHNO_PRINT("CommRecvDSMPChangeReq ��M\n");
}

//==============================================================================
/**
 * DS�ʐMMP�ʐM�̐؂�ւ� �I������ CS_DSMP_CHANGE_END
 * @param   none
 * @retval  �c�萔
 */
//==============================================================================

void CommRecvDSMPChangeEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
    OHNO_PRINT("CommRecvDSMPChangeEND ��M\n");

    if(_pComm->transmissionNum == _TRANS_LOAD_END){
        _commSetTransmissonType(pBuff[0]);  // �؂�ւ���
        _pComm->transmissionNum = _TRANS_NONE;
    }
}

//==============================================================================
/**
 * �����̋@��ID��Ԃ�
 * @param   
 * @retval  �����̋@��ID  �Ȃ����Ă��Ȃ��ꍇCOMM_PARENT_ID
 */
//==============================================================================

u16 CommGetCurrentID(void)
{
    if(_pComm){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            int id = mydwc_getaid();
            if(id != -1){
                return id;
            }
        }
        else if(CommGetAloneMode()){
            return COMM_PARENT_ID;
        }
        else{
            return WH_GetCurrentAid();
        }
    }
    return COMM_PARENT_ID;
}

//==============================================================================
/**
 * �ėp���M���\�b�h  ���M�T�C�Y�Œ�ł������傫���ꍇ
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendFixHugeSizeData(int command, const void* data)
{
    return CommSendHugeData(command, data, 0);
}

//==============================================================================
/**
 * �ėp���M���\�b�h  ���M�T�C�Y�Œ�̏ꍇ
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @param   data       ���M�������f�[�^ �Ȃ�����NULL
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendFixSizeData(int command, const void* data)
{
    return CommSendData(command, data, 0);
}

//==============================================================================
/**
 * �ėp���M���\�b�h  �R�}���h�ȊO���݂��Ȃ��ꍇ
 * @param   command    comm_sharing.h�ɒ�`�������x��
 * @retval  ���M�L���[�ɓ��������ǂ���
 */
//==============================================================================

BOOL CommSendFixData(int command)
{
    return CommSendData(command, NULL, 0);
}

//==============================================================================
/**
 * WH���C�u�����Ł@�ʐM��Ԃ�BIT���m�F
 * @param   none
 * @retval  �ڑ����킩��BIT�z��
 */
//==============================================================================

BOOL CommIsChildsConnecting(void)
{
    return CommMPIsChildsConnecting();
}

//==============================================================================
/**
 * �G���[��Ԃ��ǂ���
 * @param   none
 * @retval  �G���[�̎�TRUE
 */
//==============================================================================

BOOL CommIsError(void)
{
    if(CommGetAloneMode()){  // ��l���[�h�̏ꍇ�����̓G���[�ɂ��Ȃ�
        return FALSE;
    }
    if(_pComm){
        if(_pComm->bError){
            CommStateSetErrorCheck(TRUE,TRUE);
            return TRUE;
        }
    }
    return CommMPIsError();
}

//==============================================================================
/**
 * �T�[�r�X�ԍ��ɑΉ������q�@���Mbyte���𓾂܂�
 * �T�[�r�X�ԍ��� include/communication/comm_def.h�ɂ���܂�
 * @param   serviceNo �T�[�r�X�ԍ�
 * @retval  �q�@�䐔
 */
//==============================================================================

u16 CommGetServiceMaxChildSendByte(u16 serviceNo)
{
    if(CommLocalGetServiceMaxEntry(serviceNo) >= COMM_WIDE_BYTE_SEND_CHILDNUM){
        return _SEND_BUFF_SIZE_CHILD;
    }
    if(_transmissonType() == _MP_MODE){
        return _SEND_BUFF_SIZE_CHILD;
    }
    return _SEND_BUFF_SIZE_4CHILD;
}

//==============================================================================
/**
 * �ő�ڑ��l���𓾂�
 * @param   none
 * @retval  �ő�ڑ��l��
 */
//==============================================================================

int CommGetMaxEntry(int service)
{
    return CommLocalGetServiceMaxEntry(service)+1;
}

//==============================================================================
/**
 * �ŏ��ڑ��l���𓾂�
 * @param   none
 * @retval  �ŏ��ڑ��l��
 */
//==============================================================================

int CommGetMinEntry(int service)
{
    return CommLocalGetServiceMinEntry(service)+1;
}

//==============================================================================
/**
 * ��l�ʐM���[�h��ݒ�
 * @param   bAlone    ��l�ʐM���[�h
 * @retval  none
 */
//==============================================================================

void CommSetAloneMode(BOOL bAlone)
{
    if(_pComm){
        _pComm->bAlone = bAlone;
    }
}

//==============================================================================
/**
 * ��l�ʐM���[�h���ǂ������擾
 * @param   none
 * @retval  ��l�ʐM���[�h�̏ꍇTRUE
 */
//==============================================================================

BOOL CommGetAloneMode(void)
{
    if(_pComm){
        return _pComm->bAlone;
    }
    return FALSE;
}

//==============================================================================
/**
 * �����I���R�}���h��M
 * @param   callback�p����
 * @retval  none
 */
//==============================================================================

void CommRecvAutoExit(int netID, int size, void* pData, void* pWork)
{
    u8 dummy;

    OHNO_PRINT("CommRecvAutoExit ��M \n");
    if(!CommMPIsAutoExit()){
        if(CommGetCurrentID() == COMM_PARENT_ID){   // �������e�̏ꍇ�݂�Ȃɋt�ԐM����
            CommSendFixSizeData_ServerSide(CS_AUTO_EXIT, &dummy);
        }
    }
    CommMPSetAutoExit();
}

#ifdef PM_DEBUG

//==============================================================================
/**
 * �f�o�b�O�p�Ƀ_���v��\������
 * @param   adr           �\���������A�h���X
 * @param   length        ����
 * @param   pInfoStr      �\�����������b�Z�[�W
 * @retval  �T�[�r�X�ԍ�
 */
//==============================================================================

void CommDump_Debug(u8* adr, int length, char* pInfoStr)
{
    int i,j = 0;

    OHNO_PRINT("%s \n",pInfoStr);
    while(length){
        OHNO_PRINT(">> ");
        for(i = 0 ; i < 8 ; i++){
            OHNO_PRINT("%2x ",adr[j]);
            j++;
            if(j == length){
                break;
            }
        }
        OHNO_PRINT("\n");
        if(j == length){
            break;
        }
    }
    OHNO_PRINT(" --end\n");
}

//==============================================================================
/**
 * �f�o�b�O�I�[�g�ړ��؂�ւ�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSwitchAutoMove_Debug(void)
{
    _pComm->DebugAutoMove =
        (_pComm->DebugAutoMove) ? 0 : 1;
}

//==============================================================================
/**
 * �f�o�b�O�I�[�g�ړ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _debugAutoMove(void)
{
    if(_pComm->DebugAutoMove){
        _pComm->DebugAutoMove++;
        if(_pComm->DebugAutoMove==0){
            _pComm->DebugAutoMove++;
        }
        if(_pComm->DebugAutoMove & 0x08){
            _pComm->sendCont |= (PAD_KEY_LEFT | PAD_BUTTON_Y); //�_�b�V���ړ�
        }
        else{
            _pComm->sendCont |= (PAD_KEY_RIGHT | PAD_BUTTON_Y); //�_�b�V���ړ�
        }
    }
}
#endif

//==============================================================================
/**
 * WEP Key �̎�p�̗��������@�̏�����
 * @param   pRand  �����Ǘ��\����
 * @retval  none
 */
//==============================================================================

void CommRandSeedInitialize(MATHRandContext32* pRand)
{
    u64 randSeed = 0;
    RTCDate date;
    RTCTime time;
    
    GF_RTC_GetDateTime(&date, &time);
    randSeed = (((((((u64)date.year * 16ULL + date.month) * 32ULL)
                   + date.day) * 32ULL + time.hour) * 64ULL + time.minute)
                * 64ULL + (time.second + sys.vsync_counter));
    MATH_InitRand32(pRand, randSeed);
}


//==============================================================================
/**
 * ����̃R�}���h�𑗐M���I�������ǂ����𒲂ׂ� �T�[�o��
 * @param   command ���ׂ�R�}���h
 * @retval  �R�}���h���݂�����TRUE
 */
//==============================================================================


BOOL CommIsSendCommand_ServerSize(int command)
{
    return CommQueueIsCommand(&_pComm->sendQueueMgrServer, command);

}


//==============================================================================
/**
 * ����̃R�}���h�𑗐M���I�������ǂ����𒲂ׂ� �N���C�A���g��
 * @param   command ���ׂ�R�}���h
 * @retval  �R�}���h���݂�����TRUE
 */
//==============================================================================


BOOL CommIsSendCommand(int command)
{
    return CommQueueIsCommand(&_pComm->sendQueueMgr, command);

}


//==============================================================================
/**
 * �L���[������ۂ��ǂ��� �T�[�o�[��
 * @param   none
 * @retval  �R�}���h���݂�����FALSE
 */
//==============================================================================

BOOL CommIsEmptyQueue_ServerSize(void)
{
    return CommQueueIsEmpty(&_pComm->sendQueueMgrServer);

}

//==============================================================================
/**
 * �L���[������ۂ��ǂ���
 * @param   none
 * @retval  �R�}���h���݂�����FALSE
 */
//==============================================================================

BOOL CommIsEmptyQueue(void)
{
    return CommQueueIsEmpty(&_pComm->sendQueueMgr);

}

//==============================================================================
/**
 * wifi�ڑ��������ǂ�����ݒ肷��
 * @param   none
 * @retval  �R�}���h���݂�����FALSE
 */
//==============================================================================

void CommSetWifiConnect(BOOL bConnect)
{
    // �ʐM�ҋ@��Ԃɂ��邩�ǂ�����`����
    _pComm->bWifiConnect = bConnect;
}

//==============================================================================
/**
 * �퓬�ɓ���O�̓G�����̗����ʒu��ݒ�
 * @param   no   �����Ă����ʒu�̔ԍ��ɒ���������
 * @param   netID   �ʐM��ID
 * @retval  none
 */
//==============================================================================
void CommSetStandNo(int no,int netID)
{
    if(_pComm){
        _pComm->standNo[netID] = no;
        OHNO_PRINT("id = %d  �������Ă�Ƃ���� %d\n",netID,no);
    }
}

//==============================================================================
/**
 * �퓬�ɓ���O�̓G�����̗����ʒu�𓾂�
 * @param   netID �ʐM��ID
 * @retval  �����Ă����ʒu�̔ԍ��ɒ���������  0-3  0,2 vs 1,3
 */
//==============================================================================
int CommGetStandNo(int netID)
{
    if(_pComm){
        if(_pComm->standNo[netID] != 0xff){
            OHNO_PRINT("�����ʒu %d �΂� id%d\n",_pComm->standNo[netID], netID);
            return _pComm->standNo[netID];
        }
    }
    return netID;
}

//==============================================================================
/**
 * VCHAT��Ԃ��ǂ���
 * @param   none
 * @retval  VCHAT��ԂȂ�TRUE
 */
//==============================================================================

BOOL CommIsVChat(void)
{
    if(CommStateGetServiceNo() < COMM_MODE_BATTLE_SINGLE_WIFI){
        return FALSE;
    }
    return mydwc_IsVChat();

}

//==============================================================================
/**
 * WIFI�ʐM�𓯊��ʐM���邩�A�񓯊��ʐM���邩�̐؂�ւ����s��
 * @param   TRUE ���� FALSE �񓯊�
 * @retval  none
 */
//==============================================================================

void CommSetWifiBothNet(BOOL bFlg)
{
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        _pComm->bWifiSendRecv = bFlg;
        if(bFlg){
            _pComm->countSendRecv = 0;
            _pComm->countSendRecvServer[0] = 0;
            _pComm->countSendRecvServer[1] = 0;
        }
        OHNO_PRINT("oo�����؂�ւ� %d\n",bFlg);
    }
}

//==============================================================================
/**
 * �L�[�𑗂����̂��ǂ�������
 * @param   TRUE ���� FALSE �񓯊�
 * @retval  none
 */
//==============================================================================

BOOL CommSysIsMoveKey(void)
{
    if(_pComm->timSendCond){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �G���[�ɂ���ꍇTRUE
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSetError(void)
{
    _pComm->bError=TRUE;
}

//==============================================================================
/**
 * �ʐM���~�߂�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemShutdown(void)
{
    if(_pComm){
        _pComm->bShutDown = TRUE;
    }
}


void CommSystemResetQueue_Server(void)
{
    CommQueueManagerReset(&_pComm->sendQueueMgrServer);
}

void CommSystemRecvStop(BOOL bFlg)
{
    if(_pComm){
        _pComm->bNotRecvCheck = bFlg;
    }
}

