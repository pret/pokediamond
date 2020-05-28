#ifndef ___MPDEBUG_H___
#define ___MPDEBUG_H___
/**
 * @version "$Id: mpdebug.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpdebug.h
 * @brief MP�����ʐM�f�o�b�O�p�֐�
 * 
 */
#include "mpconnect.h"  

#ifdef __cplusplus
extern "C" {
#endif

  
/**
 * �w��X�e�[�^�X�𕶎���ŕԂ�
 */
extern const char* MpGetStatusString(MP_STATUS status);


/**
 * �G���[�R�[�h��\������
 *
 * @param WM���Ԃ��G���[�R�[�h
 */
extern void MpPrintErrorCode(WMErrCode code);


/**
 * �X�e�[�^�X�R�[�h��\������
 *
 * @param WM���Ԃ��X�e�[�^�X�R�[�h
 */
extern  void MpPrintStateCode(WMStateCode code);


/**
 * WMBssDesc�̓��e��\������
 */
extern void MpPrintBssDesc(WMBssDesc *desc);


/**
 * MpDataChildMP�̓��e��\������
 */
extern void MpPrintDataChildMP(MpDataChildMP *drmp);


/**
 * MpDataParentMP�̓��e��\������
 */
extern void MpPrintDataParentMP(MpDataParentMP *dpmp);
  

/**
 * MP_CONTROL_CODE�𕶎���Ԃ�
 */
extern const char* MpPrintControlCode(MP_CONTROL_CODE code);

       
/**
 * MpSendHeader�̓��e��\������
 */
extern void MpPrintSendHeader(MpSendHeader *header);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPDEBUG_H___
