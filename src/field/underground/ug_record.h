//=============================================================================
/**
 * @file	ug_record.h
 * @bfief	�L�^���Ǘ�����N���X
 * @author	k.ohno
 * @date	06/01/31
 */
//=============================================================================

#ifndef __UG_RECORD_H__
#define __UG_RECORD_H__

#include "savedata/undergrounddata.h"

//==============================================================================
//	enum
//==============================================================================


/*
typedef enum{
  UNDER_FLAG_POINT_DELIVERY = 30,     //�n�^����n�ɂ���������	�{30
  UNDER_FLAG_POINT_DELIVERY_SECOND = 15, //�i��x�Ƃ������̂���n�^�j	�{15
  UNDER_FLAG_POINT_DIG_FOSSIL = 2, // ���΂𔭌@����	�{�Q
  UNDER_FLAG_POINT_SEND_GOODS = 5,  // �����������
  UNDER_FLAG_POINT_TALK = 1,       // ��b����
  UNDER_FLAG_POINT_QUESTION = 1,     // ��b�̎�����s��
  UNDER_FLAG_POINT_RESQUE = 5,     // ������
  UNDER_FLAG_POINT_CREATE_BASE = 3,  // ��n�����
  UNDER_FLAG_POINT_ENTER_UG = 1,   // �n���ɓ���
  UNDER_FLAG_POINT_WALK100 = 1,    // �n�����P�O�O����

} UnderFlagPoint_e;
*/

typedef enum{
  UNDER_FLAG_DEL,             // �����̂Ă�
  UNDER_FLAG_TARGET_GET,      // ����̊�n�̃n�^���Ƃ�	�{�P�O
  UNDER_FLAG_MYFLAG_LOSE,     // �����̊�n�̃n�^���Ƃ���	�[�P�O
  UNDER_FLAG_DELIVERY,        // �n�^����n�ɂ���������	�{�T�O
  UNDER_FLAG_DELIVERY_SECOND, //�i��x�Ƃ������̂���n�^�j	�{�Q�O
  UNDER_FLAG_RIP_OFF,    // �l�̃n�^�����΂�	�{�P�O
  UNDER_FLAG_RECAPTURE,  // �l�̃n�^���Ƃ肩����	�{�P�O
  UNDER_FLAG_STOLEN,     // �����Ă��n�^���Ƃ���	�[�P�O
  UNDER_FLAG_TRICK,      // �����㩂ɂ͂߂�	�{�R
  UNDER_FLAG_DECOY,      // 㩂ɂ͂߂���	�[�P
  UNDER_FLAG_DIG_FOSSIL, // ���΂𔭌@����	�{�Q
  UNDER_FLAG_NOTALK,    // �b���������Ȃ�
  UNDER_FLAG_NODIG,    // �E���Ȃ�
} UnderFlagState_e;



//==============================================================================
//	typedef
//==============================================================================

typedef struct _UNDER_RECORD  UNDER_RECORD;




//==============================================================================
//	extern
//==============================================================================

extern void UnderRecordInitialize(UNDER_RECORD* pRecord, SB_RECORD_DATA* pMyRec, SAVEDATA* pSaveData);
extern int UnderRecordGetWorkSize(void);
extern void UnderRecordFinalize(void);
extern void UnderRecordReset(void);
extern void UnderRecordReboot(void);


typedef void(*UgRecordEndCallBack)(void* pWork);

// �X�e�[�^�X���
extern void UgRecordStatusListStart(GF_BGL_INI* bgl, MYSTATUS* pMyStatus,
                                    UgRecordEndCallBack pFunc,void* pWork, BOOL bMyData);
extern void UgRecordUpdateMyData(void);

extern int UgRecordGetTargetDataSize(void);
extern void UgRecordSendMyData(int targetID);
extern void UgRecordRecvTargetData(int netID, int size, void* pData, void* pWork);
extern void UgRecordRecvTargetDataCall(int netID, int size, void* pData, void* pWork);
extern BOOL UgRecordIsTargetRecord(void);
extern void UgRecordResetTargetRecord(void);
extern void UgRecordGoodsMessage(SB_RECORD_DATA* pRec, int message);
// �����l��������
extern void* UgRecordFlagListStart(GF_BGL_INI* bgl, MYSTATUS* pMyStatus,UNDERGROUNDDATA* pUGData,
                                  UgRecordEndCallBack pFunc,void* pWork);
extern void UgRecordFlagListEnd(void* work);


#endif //__UG_RECORD_H__


