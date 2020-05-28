#ifndef ___MPDATA_H___
#define ___MPDATA_H___
/**
 * @version "$Id: mpdata.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpdata.h
 * @brief �����ʐM���C�u���� �����f�[�^�Q�Ɗ֐�
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "mpconnect.h"

/**
 * ���C�u�������ŕێ������WMParentParam��Ԃ�
 *
 * @return WMParentParam
 */
extern WMParentParam *MpGetParentParameter(void);

extern u32 MpGetConnectChildMax(void);
extern void MpSetConnectChildMax(u32 num);
  
/**
 * �����Ŏg�p����f�[�^��Ԃ�
 *
 * @return TWL_InternalData
 */
extern MpInternalData *MpGetInternalData(void);
  

/**
 * �����X�e�[�^�X��Ԃ�
 *
 * @return MP_STATUS
 */
extern MP_STATUS MpGetStatus(void);


/**
 * �����X�e�[�^�X��ݒ肷��
 *
 * @param status MP_STATUS 
 */
extern void MpSetStatus(MP_STATUS status);
  

/**
 * �v���X�e�[�^�X��Ԃ�
 *
 * @return MP_STATUS
 */
extern MP_STATUS MpGetRequestStatus(void);

  
/**
 * �v���X�e�[�^�X��ݒ肷��
 *
 * @param status TWL_STATUS 
 */
extern void MpSetRequestStatus(MP_STATUS status);

  
/**
 * �ʐM���[�h��Ԃ�
 *
 * @return MP_MODE
 */
extern MP_MODE MpGetMode(void);


/**
 * �ʐM���[�h��ݒ肷��
 *
 * @param status MP_MODE
 */
extern void MpSetMode(MP_MODE mode);


/**
 * �ʐM�|�[�g��Ԃ�
 *
 * @param port 
 */
extern u32 MpGetPort(void);


/**
 * �ʐM�|�[�g��ݒ肷��
 *
 * @param port 
 */
extern void MpSetPort(u32 port);
  

/**
 * �ʐM�`�����l����Ԃ�
 *
 * @return channel 
 */
extern u32 MpGetChannel(void);


/**
 * �ʐM�`�����l����ݒ肷��
 *
 * @param channel 
 */
extern void MpSetChannel(u32 channel);

  
/**
 * WMScanParam���擾����
 *
 * @return WMScanParam
 */
extern WMScanParam *MpGetScanParameter(void);
  

/**
 * ���M�o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�b�t�@�T�C�Y
 */
extern u32 MpGetSendBuffSize(void);


/**
 * ��M�o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�b�t�@�T�C�Y
 */
extern u32 MpGetRecvBuffSize(void);


/**
 * ���M�o�b�t�@�̃A�h���X��Ԃ�
 *
 * @return �o�b�t�@�̃A�h���X
 */
extern void *MpGetSendBuff(void);


/**
 * ��M�o�b�t�@�̃A�h���X��Ԃ�
 *
 * @return �o�b�t�@�̃A�h���X
 */
extern void *MpGetRecvBuff(void);


/**
 * WMBssDesc�̃A�h���X��Ԃ�
 *
 * @return �A�h���X
 */
extern WMBssDesc *MpGetBssDesc(void);


/**
 * AID���L�^
 *
 * @param aid AID
 */
extern void MpSetAid(u16 aid);


/**
 * AID��Ԃ�
 *
 * @return AID
 */
extern u16 MpGetAid(void);


  extern BOOL MpIsConnectFlag(void);
extern void MpSetIsConnectFlag(BOOL flag);
extern void MpSetDisconnectTrigger(BOOL flag);
extern BOOL MpGetDisconnectTrigger(void);
  
extern BOOL MpGetEndRequest(void);
extern void MpSetEndRequest(BOOL flag);
extern void MpSetIsEnd(BOOL flag);  

  
/**
 * ���[�h�ʃf�[�^�̃A�h���X��Ԃ�
 */
extern MpModeData *MpGetModeData(void);


/**
 * �q�@��ԗp�f�[�^�̃A�h���X��Ԃ�
 */
extern MpDataChildMP *MpGetDataChildMP(void);


/**
 * �e�@��ԗp�f�[�^�̃A�h���X��Ԃ�
 */
extern MpDataParentMP *MpGetDataParentMP(void);
  

/**
 * MpDataChildMP��������
 */
extern void MpInitDataChildMP(void);

  
/**
 * MpDataParentMP��������
 */
extern void MpInitDataParentMP(void);
  

/**
 * MpTransData��Ԃ�
 */
extern MpTransData *MpGetTransData(void);


/**
 * MpTransData��������
 */
extern void MpInitTransData(void);
  

/**
 * GGID��Ԃ�
 */
extern u32 MpGetGameID(void);


/**
 *
 */
extern u16 MpGetFramePeriod(void);


/**
 * �v���g�R��ID��Ԃ�
 */
extern u32 MpGetProtocolID(void);

  
/**
 * �v���g�R���o�[�W������Ԃ�
 */
extern u32 MpGetProtocolVersion(void);

       
/**
 * �ڑ�ID��Ԃ�
 */
extern u32 MpGetConnectID(void);


/**
 * UserGameInfo�̃T�C�Y��Ԃ�
 *
 * @return UserGameInfo�̃T�C�Y
 */
extern u32 MpGetUserGameInfoSize(void);

  
/**
 * MpUserGameInfo��Ԃ�
 *
 * @return MpUserGameInfo�̃A�h���X
 */
extern MpUserGameInfo *MpGetUserGameInfo(void);


/**
 * MpSsidData��Ԃ�
 *
 * @return MpSsidData�̃A�h���X
 */
extern MpSsidData *MpGetSsidData(void);
  

/**
 * MAC�A�h���X���i�[�����z�񂩂�MpMACAddData�𐶐�
 *
 * @param mac_arry MAC�A�h���X�z��
 * @return�@MpMACAddData
 */
extern MpMACAddData MpMACAddArrayToMACAddData(u8 *mac_arry);


/**
 * MAC�A�h���X���i�[�����z�񂩂�MpMACVendorData�𐶐�
 *
 * @param mac_arry MAC�A�h���X�z��
 * @return�@MpMACVendorData
 */
extern MpMACVendorData MpMACAddArrayToMACVendorData(u8 *mac_arry);
  

/**
 * u32��MAC�A�h���X����ڑ�ID�𐶐�
 *
 * @param mac_addr MAC�A�h���X
 * @param high_code ���[�U�[�R�[�h��ʂ��i�[�����
 * @param low_code ���[�U�[�R�[�h���ʂ��i�[�����
 */
extern void MpMACAddressToConnectCode(u32 mac_addr, u32 *high_code, u32* low_code);


/**
 * u32��MAC�A�h���X����ڑ�ID�𕶎���Ƃ��Đ���
 *
 * @param mac_addr MAC�A�h���X
 * @return ������o�b�t�@�̃|�C���^
 */
extern const u16* MpConnectCodeToString(u32 mac_addr);
  
  
#if 0       
/**
 * ��ʉ��ʂ��ꂼ��̃��[�U�[�R�[�h����u32��MAC�A�h���X�𐶐�
 *
 * @param high_code ���[�U�[�R�[�h���
 * @param low_code ���[�U�[�R�[�h����
 * @return MAC�A�h���X
 */
extern u32 MpUserCodeToMACAddress(u32 high_code, u32 low_code);
#endif
  

/**
 * ���M�f�[�^�̃w�b�_�T�C�Y���擾 �i���݌Œ�j
 *
 * @return �o�C�g��
 */
extern u32 MpGetSendHeaderSize(void);

       
/**
 * ���M�p�f�[�^�𐶐�����
 *
 * @param buff �f�[�^�𐶐�����A�h���X
 * @param data ���M�p�f�[�^
 * @param data_size ���M�p�f�[�^�̃T�C�Y
 * @param control_code �ʐM����R�[�h
 * @param seq_num �ʐM�ԍ�
 */
extern void MpSetupSendData(void *buff, void *data, u32 data_size, MP_CONTROL_CODE control_code, u32 seq_num);


/**
 * ��M�����f�[�^�𕜍�����
 *
 * @param buff ��M�����f�[�^
 */
extern void MpDecodeRecvData(void *buff);


/**
 * ��M�����f�[�^��CRC���`�F�b�N����
 *
 * @return buff ��M�����f�[�^
 */
extern BOOL MpCheckRecvData(void *buff);

       
#ifdef  __cplusplus
}       /* extern "C" */
#endif


#endif // ___MPDATA_H___
  
