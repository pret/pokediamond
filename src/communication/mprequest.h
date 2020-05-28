#ifndef ___MPREQUEST_H___
#define ___MPREQUEST_H___
/**
 * @version "$Id: mprequest.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mprequest.h
 * @brief �����ʐM���C�u���� ��ԑJ�ڊ֐�
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * PORT�ʐM���s��
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestSetMPData(const void *buf, u32 size, u16 aid_bitmap);

       
/**
 * �����f�o�C�X���g�p�\�ȏ�Ԃɂ���
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestEnable(void);


/**
 * �����f�o�C�X���g�p�s�̏�Ԃɂ���
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestDisable(void);
  

/**
 * �w��`�����l���̓d�g�g�p���𑪒�
 *
 * @param �`�����l���ԍ��i1,7,13�j 
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestSearchChannel(u32 channel);
  
       
/**
 * �e�@�Ƃ��ĕK�v�ȃp�����[�^��ݒ�
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestSetParentParameter(void);
  

/**
 * �e�@�Ƃ��Ċ����J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestStartParent(void);


/**
 * �q�@�Ƃ��Đe�@�̃X�L�����J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestStartScan(void);


/**
 * �q�@�Ƃ��ē���̐e�@�̃X�L�����J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestStartScan2(void);
  

/**
 * �q�@�̐e�@�X�L�����I��
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestEndScan(void);
  

/**
 * �e�@�ւ̐ڑ��J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestStartConnect(void);

  
/**
 * �ڑ�����
 *
 * @param �Ώ�AID
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestDisConnect(u16 aid);


/**
 * �����̎q�@�Ƃ̐ڑ����� �i�e�@��p�j
 *
 * @param �Ώ�AID�r�b�g�}�b�v
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestDisConnectChildren(u16 aid_bit);
  
       
/**
 * MP�ʐM���[�h�J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestStartMP(void);


/**
 * �����f�o�C�X�ɓd������
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestPowerOn(void);


/**
 * �����f�o�C�X�̓d��OFF
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestPowerOff(void);


/**
 * WM�����Z�b�g WM��READY�AIDLE�X�e�[�g�ȊO�S�ẴX�e�[�g����IDLE�X�e�[�g�Ɉڍs
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestReset(void);
  

/**
 * WM���I�� WM��IDLE�X�e�[�g���疳���@�\�S��~�Ɉڍs
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
extern BOOL MpRequestEnd(void);

       
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPREQUEST_H___
  

  
