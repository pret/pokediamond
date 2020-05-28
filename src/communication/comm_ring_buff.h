//=============================================================================
/**
 * @file	comm_ring_buff.h
 * @bfief	�����O�o�b�t�@�̎d�g�݂��Ǘ�����֐�
 * @author	katsumi ohno
 * @date	05/09/16
 */
//=============================================================================


#ifndef __COMM_RING_BUFF_H__
#define __COMM_RING_BUFF_H__

// �����O�o�b�t�@�\����
typedef struct{
    u8* pWork;
    s16 startPos;
    volatile s16 endPos;
    volatile s16 backupEndPos;
//    s16 backupStartPos;
    s16 size;
} RingBuffWork;

// �����O�o�b�t�@�̏�����
extern void CommRingInitialize(RingBuffWork* pRing, u8* pDataArea, int size);
// �����O�Ƀf�[�^������
extern void CommRingPuts(RingBuffWork* pRing, u8* pDataArea, int size,int line);
// �����O����f�[�^�𓾂�
extern int CommRingGets(RingBuffWork* pRing, u8* pDataArea, int size);
// �����O����1byte�f�[�^�𓾂�
extern u8 CommRingGetByte(RingBuffWork* pRing);
// �����O�Ƀf�[�^�����邩��������o�� �|�C���^�͕ς��Ȃ�
extern int CommRingChecks(RingBuffWork* pRing, u8* pDataArea, int size);
// �����O�T�C�Y�𓾂�
extern int CommRingDataSize(RingBuffWork* pRing);
// �����O�̎c��T�C�Y�𓾂�
extern int CommRingDataRestSize(RingBuffWork* pRing);

// �X�^�[�g�̃o�b�N�A�b�v����X�^�[�g��߂�
extern void CommRingStartPop(RingBuffWork* pRing);
// �X�^�[�g�̃o�b�N�A�b�v�փX�^�[�g������
extern void CommRingStartPush(RingBuffWork* pRing);
// End�ꏊ�����肩����
extern void CommRingEndChange(RingBuffWork* pRing);

#endif// __COMM_RING_BUFF_H__

