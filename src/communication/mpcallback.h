#ifndef ___MPCALLBACK_H___
#define ___MPCALLBACK_H___
/**
 * @version "$Id: mpcallback.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file twl_callback.h
 * @brief �����ʐM���C�u���� ��ԑJ�ڃR�[���o�b�N�֐�
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * Indication�R�[���o�b�N�֐�
 */
extern void MpCallbackIndicate(void *arg);
  

/**
 * MpRequestSetMPDataToPort�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackSetMPDataToPort(void *arg);


/**
 * MpRequestEnable�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackEnable(void *arg);

  
/**
 * MpRequestDisable�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackDisable(void *arg);


/**
 * MpRequestSearchChannel�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
extern void MpCallbackSearchChannel(void *arg);

       
/**
 * MpRequestSetParentParameter�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
extern void MpCallbackSetParentParameter(void *arg);

       
/**
 * MpRequestStartParent�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
extern void MpCallbackStartParent(void *arg);


/**
 * MpRequestStartScan�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
extern void MpCallbackStartScan(void *arg);


/**
 * MpRequestStartScan2�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
extern void MpCallbackStartScan2(void *arg);
  
  
/**
 * MpRequestEndScan�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackEndScan(void *arg);


/**
 * MpRequestStartConnect�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackStartConnect(void *arg);

  
/**
 * MpRequestDisConnect�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackDisConnect(void *arg);


/**
 * MpRequestDisConnectChildren�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackDisConnectChildren(void *arg);
  
       
/**
 * MpRequestStatMP�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackStartMP(void *arg);


/**
 * WM_SetPortCallback�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackReceiveData(void *arg);

  
/**
 * MpRequestPowerOn�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackPowerOn(void *arg);


/**
 * MpRequestPowerOff�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackPowerOff(void *arg);


/**
 * MpRequestReset�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackReset(void *arg);
  

/**
 * MpRequestEnd�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
extern void MpCallbackEnd(void *arg);


  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPCALLBACK_H___
  

  
