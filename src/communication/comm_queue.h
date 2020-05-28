//=============================================================================
/**
 * @file	comm_queue.h
 * @bfief	�i���M�j�L���[�̎d�g�݂��Ǘ�����֐�
 * @author	katsumi ohno
 * @date	06/01/29
 */
//=============================================================================

#ifndef __COMM_QUEUE_H__
#define __COMM_QUEUE_H__

#include "comm_ring_buff.h"

typedef struct _SEND_QUEUE SEND_QUEUE;

// �L���[�\����
struct _SEND_QUEUE{
    u8* pData;     ///< �f�[�^�A�h���X
    SEND_QUEUE* prev;      //
    SEND_QUEUE* next;
    u16 size;       ///< �T�C�Y
    u8 command;    ///< �R�}���h
    u8 bHeadSet:1;  ///< �w�b�_�[�𑗐M�����ꍇ�P �܂��̏ꍇ�O
    u8 bRing:1;     ///< �����O�o�b�t�@�g�p�̏ꍇ�P
} ;

typedef struct{
    u8* pData;
    int size;
} SEND_BUFF_DATA;



typedef struct{
    SEND_QUEUE* pTop;     // ���M�L���[�̏���
    SEND_QUEUE* pLast;    // ���M�L���[�̍Ō�
} SEND_TERMINATOR;



typedef struct{
    SEND_TERMINATOR fast;     // �������鑗�M�L���[
    SEND_TERMINATOR stock;    // ��ő���΂����L���[
    SEND_QUEUE* pNow;   // �������Ă���Œ��̃L���[
    RingBuffWork* pSendRing;  // �����O�o�b�t�@���[�N�|�C���^
    void* heapTop;   // �L���[HEAP
    int max;         // �L���[�̐�
} SEND_QUEUE_MANAGER;


// �L���[�ɉ��������Ă��邩�ǂ������m�F����
extern BOOL CommQueueIsEmpty(SEND_QUEUE_MANAGER* pQueueMgr);
// �L���[MANAGER�̏�����
extern void CommQueueManagerInitialize(SEND_QUEUE_MANAGER* pQueueMgr, int queueMax, RingBuffWork* pSendRing);
// �L���[�̒��g�����Z�b�g
extern void CommQueueManagerReset(SEND_QUEUE_MANAGER* pQueueMgr);
// �L���[MANAGER�̏I��
extern void CommQueueManagerFinalize(SEND_QUEUE_MANAGER* pQueueMgr);
// �L���[�Ƀf�[�^������
extern BOOL CommQueuePut(SEND_QUEUE_MANAGER* pQueueMgr,int command, u8* pDataArea, int size, BOOL bFast, BOOL bSave);
// �L���[����f�[�^���z���グ��
extern BOOL CommQueueGetData(SEND_QUEUE_MANAGER* pQueueMgr, SEND_BUFF_DATA *pSendBuff, BOOL bNextPlus);
// �R�}���h�����邩�ǂ������ׂ�
extern BOOL CommQueueIsCommand(SEND_QUEUE_MANAGER* pQueueMgr, int command);

extern int CommQueueGetNowNum(SEND_QUEUE_MANAGER* pQueueMgr);

#ifdef PM_DEBUG
extern void CommQueueDebugTest(void);
#endif

#endif// __COMM_QUEUE_H__

