//=============================================================================
/**
 * @file	comm_ring_buff.c
 * @bfief	�����O�o�b�t�@�̎d�g�݂��Ǘ�����֐�
 * @author	katsumi ohno
 * @date	05/09/16
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"
#include "comm_ring_buff.h"



static int _ringPos(RingBuffWork* pRing,int i);

//==============================================================================
/**
 * �����O�o�b�t�@�Ǘ��\���̏�����
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @param   pDataArea    �����O�o�b�t�@�������[
 * @param   size         �����O�o�b�t�@�������[�T�C�Y
 * @retval  none
 */
//==============================================================================
void CommRingInitialize(RingBuffWork* pRing, u8* pDataArea, int size)
{
    pRing->pWork = pDataArea;
    pRing->size = size;
    pRing->startPos = 0;
    pRing->endPos = 0;
    pRing->backupEndPos = 0;
//    pRing->backupStartPos = 0;
}

//==============================================================================
/**
 * �����O�o�b�t�@�ɏ�������
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @param   pDataArea    �������ރf�[�^
 * @param   size         �������݃T�C�Y
 * @param   bUsed  ���̃����O���g�p���炵��
 * @retval  none
 */
//==============================================================================
void CommRingPuts(RingBuffWork* pRing, u8* pDataArea, int size,int line)
{
    int i,j;

    // ������ASSERT�Ɉ���������Ƃ������Ƃ�
    // �������x�����Ă���̂ɁA�ʐM�͖�sync����̂�
    // �X�g�b�N����o�b�t�@���܂ł��ӂ��ƁA�����Ŏ~�܂�܂��B
    // �ʐM�̃o�b�t�@�𑝂₷���A���̕����̏����𕪒f���邩�A�Ώ����K�v�ł��B
    // �ŏI�I�ɂ͂��̃G���[������ƒʐM��ؒf���܂��B
    if(CommRingDataRestSize(pRing) <= size){
#ifdef DEBUG_ONLY_FOR_ohno
        OHNO_PRINT("%d %d line %d \n",CommRingDataRestSize(pRing),size,line);
        GF_ASSERT_MSG(0,"CommRingOVER %d %d",CommRingDataRestSize(pRing),size);
#endif
        CommSetError();
        return;
    }
    j = 0;
    for(i = pRing->backupEndPos; i < pRing->backupEndPos + size; i++,j++){
        GF_ASSERT(pDataArea);
        pRing->pWork[_ringPos( pRing, i )] = pDataArea[j];
    }
    pRing->backupEndPos = _ringPos( pRing, i );
}

//==============================================================================
/**
 * �����O�o�b�t�@����f�[�^�𓾂�
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @param   pDataArea    �ǂݍ��݃o�b�t�@
 * @param   size         �ǂݍ��݃o�b�t�@�T�C�Y
 * @retval  ���ۂɓǂݍ��񂾃f�[�^
 */
//==============================================================================
int CommRingGets(RingBuffWork* pRing, u8* pDataArea, int size)
{
    int i,j;

    i = CommRingChecks(pRing, pDataArea, size);
    pRing->startPos = _ringPos( pRing, pRing->startPos + i);
//    OHNO_PRINT("++++++ �o�b�t�@���炾���� %d %d  %d byte\n", pRing->startPos, pRing->endPos, i);
    return i;
}

//==============================================================================
/**
 * �����O�o�b�t�@����1byte�f�[�^�𓾂�
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @retval  1byte�̃f�[�^ �����O�Ƀf�[�^���Ȃ��Ƃ���0(�s��)
 */
//==============================================================================
u8 CommRingGetByte(RingBuffWork* pRing)
{
    u8 byte;

    CommRingGets(pRing, &byte, 1);
    return byte;
}

//==============================================================================
/**
 * �����O�o�b�t�@�̃f�[�^����  �ǂݍ��ނ����ňʒu��i�߂Ȃ�
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @param   pDataArea    �ǂݍ��݃o�b�t�@
 * @param   size         �ǂݍ��݃o�b�t�@�T�C�Y
 * @retval  ���ۂɓǂݍ��񂾃f�[�^
 */
//==============================================================================
int CommRingChecks(RingBuffWork* pRing, u8* pDataArea, int size)
{
    int i,j;

    j = 0;
    for(i = pRing->startPos; i < pRing->startPos + size; i++,j++){
        if(pRing->endPos == _ringPos( pRing,i )){
            return j;
        }
        pDataArea[j] = pRing->pWork[_ringPos( pRing,i )];
    }
    return j;
}

//==============================================================================
/**
 * �����O�o�b�t�@�̃f�[�^�����������Ă��邩����
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @retval  �f�[�^�T�C�Y
 */
//==============================================================================
int CommRingDataSize(RingBuffWork* pRing)
{
    if(pRing->startPos > pRing->endPos){
        return (pRing->size + pRing->endPos - pRing->startPos);
    }
    return (pRing->endPos - pRing->startPos);
}

//==============================================================================
/**
 * �����O�o�b�t�@�̃f�[�^���ǂ̂��炢���܂��Ă��邩����
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @retval  ���ۂɓǂݍ��񂾃f�[�^
 */
//==============================================================================
int CommRingDataRestSize(RingBuffWork* pRing)
{
    return (pRing->size - CommRingDataSize(pRing));
}

//==============================================================================
/**
 * �J�E���^�[���o�b�N�A�b�v����
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @retval  nono
 */
//==============================================================================
//void CommRingStartPush(RingBuffWork* pRing)
//{
//    pRing->backupStartPos = pRing->startPos;
//}

//==============================================================================
/**
 * �J�E���^�[���o�b�N�A�b�v����
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @retval  nono
 */
//==============================================================================
//void CommRingStartPop(RingBuffWork* pRing)
//{
//    pRing->startPos = pRing->backupStartPos;
//}

//==============================================================================
/**
 * ring�T�C�Y�̏ꏊ
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @retval  
 */
//==============================================================================
int _ringPos(RingBuffWork* pRing,int i)
{
    return i % pRing->size;

}

//==============================================================================
/**
 * �J�E���^�[�ꏊ�����肩����
 * @param   pRing        �����O�o�b�t�@�Ǘ��|�C���^
 * @retval  nono
 */
//==============================================================================
void CommRingEndChange(RingBuffWork* pRing)
{
    pRing->endPos = pRing->backupEndPos;
}

