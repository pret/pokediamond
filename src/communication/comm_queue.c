//=============================================================================
/**
 * @file	comm_queue.c
 * @bfief	�i���M�j�L���[�̎d�g�݂��Ǘ�����֐�
 * @author	katsumi ohno
 * @date	06/01/29
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"
#include "comm_queue.h"

//==============================================================================
/**
 * �J���Ă���L���[��Ԃ�
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @param   queueMax  �L���[��
 * @retval  none
 */
//==============================================================================

static SEND_QUEUE* _freeQueue(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_QUEUE* pFree = pQueueMgr->heapTop;
    int i;

    for(i = 0;i < pQueueMgr->max; i++){
        if(pFree->command == CS_FREE){
            return pFree;
        }
        pFree++;
    }
    return NULL;   // �R�}���h������
}

//==============================================================================
/**
 * �L���[�ɉ��������Ă��邩�ǂ������m�F����
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @retval  ��Ȃ��TRUE
 */
//==============================================================================

BOOL CommQueueIsEmpty(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_QUEUE* pFree = pQueueMgr->heapTop;
    int i;

    for(i = 0;i < pQueueMgr->max; i++){
        if(pFree->command != CS_FREE){
            return FALSE;
        }
        pFree++;
    }
    return TRUE;   // �R�}���h������
}

//==============================================================================
/**
 * �L���[�̐��𓾂�
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @retval  ��Ȃ��TRUE
 */
//==============================================================================

int CommQueueGetNowNum(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_QUEUE* pFree = pQueueMgr->heapTop;
    int i,j = 0;

    for(i = 0;i < pQueueMgr->max; i++){
        if(pFree->command != CS_FREE){
            j++;
        }
        pFree++;
    }
    return j;
}

//==============================================================================
/**
 * �L���[������
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @param   queueMax  �L���[��
 * @retval  none
 */
//==============================================================================

static BOOL _deleteQueue(SEND_TERMINATOR* pTerm)
{
    if(pTerm->pTop != NULL){
        if(pTerm->pTop->next!= NULL){
            pTerm->pTop = pTerm->pTop->next;
            pTerm->pTop->prev = NULL;
        }
        else{
            pTerm->pTop = NULL;
            pTerm->pLast = NULL;
        }
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * ���M�f�[�^�̃w�b�_�[�������o�b�t�@�ɓ����
 * @param   pSendBuff   ���M�o�b�t�@�Ǘ��\���̃|�C���^
 * @param   byte        �Z�b�g����f�[�^
 * @retval  0�ɂȂ�����TRUE
 */
//==============================================================================

static BOOL _setSendData(SEND_BUFF_DATA* pSendBuff ,u8 byte)
{
    *pSendBuff->pData = byte;
    pSendBuff->pData++;
    pSendBuff->size--;
    if(pSendBuff->size==0){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * ���M�f�[�^�̃w�b�_�[�������o�b�t�@�ɓ����
 * @param   pQueue  �L���[�̃|�C���^
 * @param   pSendBuff   ���M�o�b�t�@�Ǘ��\���̃|�C���^
 * @retval  �~������FALSE
 */
//==============================================================================

static BOOL _dataHeadSet(SEND_QUEUE* pQueue, SEND_BUFF_DATA* pSendBuff)
{
    int cs = CommCommandGetPacketSize(pQueue->command);

    if( cs == COMM_VARIABLE_SIZE){
        if(pSendBuff->size < 3){
            pQueue->bHeadSet = FALSE;
            return TRUE;
        }
    }
    else{
        if(pSendBuff->size < 1){
            pQueue->bHeadSet = FALSE;
            return TRUE;
        }
    }
    _setSendData(pSendBuff,pQueue->command);
    if(cs == COMM_VARIABLE_SIZE){
        _setSendData(pSendBuff,(pQueue->size >> 8)  & 0xff);
        _setSendData(pSendBuff,pQueue->size & 0xff);
    }
    else{
        pQueue->size = cs;
    }
    pQueue->bHeadSet = TRUE;
    return FALSE;
}

//==============================================================================
/**
 * �L���[���瑗�M�o�b�t�@�Ɉڂ�
 * @param   pQueue  �L���[
 * @param   pSendBuff   ���M�o�b�t�@
 * @retval  �w�b�_�[������Ȃ������ꍇTRUE
 */
//==============================================================================

static BOOL _dataCopyQueue(SEND_QUEUE* pQueue, SEND_BUFF_DATA* pSendBuff, RingBuffWork* pSendRing, BOOL bNextPlus)
{
    int i;
    int size;
    int cs = CommCommandGetPacketSize(pQueue->command);
    if( cs == COMM_VARIABLE_SIZE){
        size = 3;
    }
    else{
        size = 1;
    }
    if((pSendBuff->size < (pQueue->size + size)) && (!bNextPlus)){  // �L���[�̂ق����ł����ꍇ
        return FALSE;
    }
    if(pQueue->bHeadSet != TRUE){
        if(_dataHeadSet(pQueue, pSendBuff)){
            return FALSE;
        }
    }
//    if((pSendBuff->size < pQueue->size) && (!bNextPlus)){  // �L���[�̂ق����ł����ꍇ
//        return FALSE;  // �O�Ɉړ�
//    }
    if(pSendBuff->size < pQueue->size){  // �L���[�̂ق����ł����ꍇ
        if(pQueue->bRing){
            CommRingGets(pSendRing, pSendBuff->pData, pSendBuff->size);
        }
        else{
          //  OHNO_PRINT("-----%x-%x--%d\n",(int)pQueue->pData, (int)pSendBuff->pData , pSendBuff->size);
//            MI_CpuCopy8( pQueue->pData, pSendBuff->pData, pSendBuff->size);
            
            for(i = 0;i < pSendBuff->size;i++){
                pSendBuff->pData[i] = pQueue->pData[i];
            }
        }
//        OHNO_PRINT("-----%d-%d--\n",pQueue->command, pQueue->size);
        
        pQueue->pData += pSendBuff->size;  // �A�h���X��i�߂�
        pQueue->size -= pSendBuff->size;  // ���M�T�C�Y���炷
        pSendBuff->size = -1;  // �c���-1�ɂ���
        return TRUE;
    }
    // �����������͏������ꍇ
    if(pQueue->bRing){
        CommRingGets(pSendRing, pSendBuff->pData, pQueue->size);
    }
    else{
        MI_CpuCopy8( pQueue->pData, pSendBuff->pData, pQueue->size);
    }
    pSendBuff->pData += pQueue->size;  // �A�h���X��i�߂�
    pSendBuff->size -= pQueue->size; // �T�C�Y�͌��炷
    return TRUE;
}


//==============================================================================
/**
 * �L���[��~����
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @param   command   ���M�R�}���h
 * @param   pDataArea  ���M�f�[�^
 * @param   size    �T�C�Y
 * @param   bFast  �D��x�������f�[�^?
 * @param   bSave  �ۑ����邩�ǂ���
 * @retval  �~������TRUE
 */
//==============================================================================

BOOL CommQueuePut(SEND_QUEUE_MANAGER* pQueueMgr,int command, u8* pDataArea, int size, BOOL bFast, BOOL bSave)
{
    SEND_QUEUE* pLast;
    SEND_QUEUE* pFree = _freeQueue(pQueueMgr);
    SEND_TERMINATOR* pTerm;
    int cSize;

    bFast = TRUE;
    if(pFree== NULL){
        OHNO_SP_PRINT("---�L���[������\n");
        return FALSE;
    }
    
    GF_ASSERT(size < 65534 && "65534�ȏ�͕���");
    cSize = CommCommandGetPacketSize(command);

    if(COMM_VARIABLE_SIZE == cSize){
        cSize = size;
    }
    if(bSave){
        int rest = CommRingDataRestSize(pQueueMgr->pSendRing);
        if((cSize+3) >= rest){  // ���M�o�b�t�@���I�[�o�[���Ă��܂�
            OHNO_PRINT("���M�o�b�t�@�I�[�o�[ com = %d size = %d / %d\n", command, cSize, rest);
            return FALSE;
        }
        CommRingPuts(pQueueMgr->pSendRing, pDataArea, cSize, __LINE__);
        CommRingEndChange(pQueueMgr->pSendRing);
        pFree->bRing = TRUE;
    }
    pFree->size = cSize;
    pFree->command = command;
    pFree->pData = pDataArea;
    if(bFast == TRUE){
        pTerm = &pQueueMgr->fast;
    }
    else{
        pTerm = &pQueueMgr->stock;
    }
    if(pTerm->pLast==NULL){
        pTerm->pLast = pFree;
        pTerm->pTop = pFree;
    }
    else{
        pTerm->pLast->next = pFree;
        pFree->prev = pTerm->pLast;
        pTerm->pLast = pFree;
    }
    return TRUE;
}

//==============================================================================
/**
 * �L���[���o��
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @param
 * @retval  none
 */
//==============================================================================

static SEND_QUEUE* _queueGet(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_TERMINATOR* pTerm;

    if(pQueueMgr->pNow != NULL){
        return pQueueMgr->pNow;
    }
    if(pQueueMgr->fast.pTop != NULL){
        return pQueueMgr->fast.pTop;
    }
    if(pQueueMgr->stock.pTop != NULL){
        return pQueueMgr->stock.pTop;
    }
    return NULL;
}


//==============================================================================
/**
 * �L���[�����莟�ɐi�߂�
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @param
 * @retval  none
 */
//==============================================================================

static void _queueNext(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_TERMINATOR* pTerm;

    if(pQueueMgr->pNow != NULL){
        pQueueMgr->pNow = NULL;
    }
    else{
        if(!_deleteQueue( &pQueueMgr->fast )){
            _deleteQueue( &pQueueMgr->stock );
        }
    }
}

//==============================================================================
/**
 * �w��o�C�g���o�b�t�@�ɓ����
 * @param   pQueueMgr  �L���[�}�l�[�W���[�̃|�C���^
 * @param   pSendBuff  ���M�o�b�t�@�\���̂̃|�C���^
 * @retval  �����f�[�^���Ȃ��ꍇTRUE �f�[�^���A�����Ă���ꍇFALSE
 */
//==============================================================================

BOOL CommQueueGetData(SEND_QUEUE_MANAGER* pQueueMgr, SEND_BUFF_DATA *pSendBuff, BOOL bNextPlus)
{
    int ret;
    int i;
    int bNextPlusFirst = TRUE;

    while(pSendBuff->size > 0){
        SEND_QUEUE* pQueue = _queueGet(pQueueMgr);
        if(NULL == pQueue){
            break;
        }
        _queueNext(pQueueMgr);
        // �w�b�_�[���M�ł��Ȃ�
        if(!_dataCopyQueue(pQueue, pSendBuff, pQueueMgr->pSendRing, bNextPlusFirst)){
            pQueueMgr->pNow = pQueue;  // ���̍ŏ��ő��M�ł���悤�ɃZ�b�g
            break;
        }
        if( -1 == pSendBuff->size ){  // �f�[�^���l�܂��Ă���ꍇ
            pQueueMgr->pNow = pQueue;  // ���̍ŏ��ő��M�ł���悤�ɃZ�b�g
            return FALSE;
        }
        else{
            MI_CpuFill8(pQueue, 0, sizeof(SEND_QUEUE));  // �L���[������
        }
        bNextPlusFirst = bNextPlus;
    }
    for(i = 0 ; i < pSendBuff->size; i++){
        *pSendBuff->pData = CS_NONE;
        pSendBuff->pData++;
    }
    return TRUE;
}



//==============================================================================
/**
 * �L���[MANAGER�̏�����
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @param   queueMax  �L���[��
 * @param   RingBuffWork ���f�[�^��ۑ�����ꍇ�̃����O�o�b�t�@���[�N
 * @retval  none
 */
//==============================================================================

void CommQueueManagerInitialize(SEND_QUEUE_MANAGER* pQueueMgr, int queueMax, RingBuffWork* pSendRing)
{
    MI_CpuFill8(pQueueMgr, 0 ,sizeof(SEND_QUEUE_MANAGER));
    pQueueMgr->heapTop = sys_AllocMemory(HEAPID_COMMUNICATION,
                                         sizeof(SEND_QUEUE)*queueMax);
    MI_CpuFill8(pQueueMgr->heapTop, 0 ,sizeof(SEND_QUEUE)*queueMax);
    pQueueMgr->max = queueMax;
    pQueueMgr->pSendRing = pSendRing;
}


//==============================================================================
/**
 * �L���[MANAGER�̃��Z�b�g
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommQueueManagerReset(SEND_QUEUE_MANAGER* pQueueMgr)
{
    MI_CpuFill8(pQueueMgr->heapTop, 0 ,sizeof(SEND_QUEUE) * pQueueMgr->max);
    pQueueMgr->fast.pTop = NULL;     // �������鑗�M�L���[
    pQueueMgr->fast.pLast = NULL;     // �������鑗�M�L���[
    pQueueMgr->stock.pTop = NULL;    // ��ő���΂����L���[
    pQueueMgr->stock.pLast = NULL;    // ��ő���΂����L���[
    pQueueMgr->pNow = NULL;   // �������Ă���Œ��̃L���[
}

//==============================================================================
/**
 * �L���[MANAGER�̏I��
 * @param   pQueueMgr �L���[�}�l�[�W���[�̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommQueueManagerFinalize(SEND_QUEUE_MANAGER* pQueueMgr)
{
    sys_FreeMemoryEz( pQueueMgr->heapTop );
}


//==============================================================================
/**
 * �L���[�����݂��邩�ǂ���
 * @param   pQueueMgr  �L���[�}�l�[�W���[�̃|�C���^
 * @param   command    ���ׂ�R�}���h
 * @retval  ��������TRUE
 */
//==============================================================================

BOOL CommQueueIsCommand(SEND_QUEUE_MANAGER* pQueueMgr, int command)
{
    int i;
    SEND_QUEUE* pNext = pQueueMgr->heapTop;

    for(i = 0; i < pQueueMgr->max; i++){
        if(pNext->command == command){
            return TRUE;
        }
        pNext++;
    }
    return FALSE;
}


//==============================================================================
/**
 * �L���[MANAGER�̃e�X�g
 * @param   none
 * @retval  none
 */
//==============================================================================
#ifdef PM_DEBUG

void CommQueueDebugTest(void)
{
    SEND_QUEUE_MANAGER mgr;
    u8 data1[30];
    u8 data2[22];
    SEND_BUFF_DATA buffData;
    u8 dummy[100];
    u8 ringbuff[50];
    int i;
    RingBuffWork sendRing;

    MI_CpuFill8(data1,2,30);
    MI_CpuFill8(data2,4,22);
    MI_CpuFill8(ringbuff,3,50);
    CommRingInitialize(&sendRing, ringbuff, 50);

    // �R�{�L���[�쐬
    CommQueueManagerInitialize(&mgr,3,&sendRing);

    // ----- �e�X�g�P
    CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 30, TRUE, TRUE);

    for(i = 0; i < 50; i++){
        if(i < 30){
            GF_ASSERT(ringbuff[i] == 2);
        }
        else{
            GF_ASSERT(ringbuff[i] == 3);
        }
    }

    
    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);

    buffData.size = 25;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size==-1);
    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == 0 && "i=1");
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 30 && "i=2");
        }
        else if(i < 25){
            GF_ASSERT(dummy[i] == 2 && "i<25");
        }
        else{
            GF_ASSERT(dummy[i] == 0xff && "i>=25");
        }
    }
    buffData.size = 25;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == (25-8));

    GF_ASSERT(mgr.pNow == NULL);
    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i < 8){
            GF_ASSERT(dummy[i] == 2 && "i < 5");
        }
        else if(i < 25){
            GF_ASSERT(dummy[i] == CS_NONE && "CS_NONE");
        }
        else{
            GF_ASSERT(dummy[i] == 0xff && "i >= 5");
        }
    }
    buffData.size = 25;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == (25));

    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i < 25){
            GF_ASSERT(dummy[i] == CS_NONE && "i<25 CS_NONE");
        }
        else{
            GF_ASSERT(dummy[i] == 0xff && "i  all");
        }
    }

    // �e�X�g�Q
    GF_ASSERT(CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 10, TRUE, FALSE));

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);
    GF_ASSERT(mgr.fast.pLast == mgr.fast.pTop);

    GF_ASSERT(CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data2, 10, TRUE, FALSE));

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pTop->next != NULL);
    GF_ASSERT(mgr.fast.pTop->next->next == NULL);


    GF_ASSERT(CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 10, TRUE, FALSE));

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pTop->next != NULL);
    GF_ASSERT(mgr.fast.pTop->next->next != NULL);

    // ����̓L���[�ɓ���Ȃ�
//    GF_ASSERT(!CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 10, TRUE, TRUE));


    buffData.size = 12;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == -1);

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);

    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == 0);
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 10);
        }
        else if(i < 12){
            GF_ASSERT(dummy[i] == 2);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }
    buffData.size = 12;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == -1);

    GF_ASSERT(mgr.pNow != NULL);
    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);

    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == 2);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 0);
        }
        else if(i == 3){
            GF_ASSERT(dummy[i] == 10);
        }
        else if(i < 12){
            GF_ASSERT(dummy[i] == 4);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }

    // �킴�Ə������ǂݍ��ނƁA���������������Ă���
    buffData.size = 4;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == 2);

    GF_ASSERT(mgr.pNow != NULL);
    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i < 2){
            GF_ASSERT(dummy[i] == 4);
        }
        else if(i < 4){
            GF_ASSERT(dummy[i] == CS_NONE);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }

    /// �Ō�͂R�Ԗڂ̃R�}���h������������Ă���
    buffData.size = 4;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == -1);

    GF_ASSERT(mgr.pNow != NULL);
    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == 0);
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 10);
        }
        else if(i < 4){
            GF_ASSERT(dummy[i] == 2);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }
    CommQueueManagerFinalize(&mgr);

//   GF_ASSERT(0 && "ok");  //�e�X�g����
}

#endif

