/**
 * @version "$Id: mprequest.c,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mprequest.c
 * @brief �����ʐM���C�u���� ��ԑJ�ڊ֐�
 * 
 */
#include "mpconnect.h"
#include "mprequest.h"
#include "mpcallback.h"
#include "mpdata.h"
#include "mpdebug.h"

/**
 * PORT�ʐM���s��
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestSetMPData(const void *buf, u32 size, u16 aid_bitmap)
{
  WMErrCode result;

  MpPrintf("MpSetMPData start. data: %08x (%x) size %d\n", *(u32 *)buf, buf, size);

  result = WM_SetMPDataToPort(MpCallbackSetMPDataToPort,
			      buf, (u16)size, aid_bitmap, (u16)MpGetPort(), MP_DEFAULT_PORT_PRIO);
  
  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpSetMPData() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
  return TRUE;
}



/**
 * �����f�o�C�X���g�p�\�ȏ�Ԃɂ���
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestEnable(void)
{
  WMErrCode result;

  MpPrintf("MpRequestEnable() start.\n");

  result = WM_Enable(MpCallbackEnable);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestEnable() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else 
    return TRUE;
}


/**
 * �����f�o�C�X���g�p�s�̏�Ԃɂ���
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestDisable(void)
{
  WMErrCode result;

  MpPrintf("MpRequestDisable() start.\n");

  result = WM_Disable(MpCallbackDisable);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("WL_Disable() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestDisable() error");    
    
    return FALSE;
  } else
    return TRUE;
}


/**
 * �w��`�����l���̓d�g�g�p���𑪒�
 *
 * @param �`�����l���ԍ��i1,7,13�j 
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestSearchChannel(u32 channel)
{
  WMErrCode result;

  MpPrintf("MpRequestSearchChannel() channel %d.\n", channel);

  result = WM_MeasureChannel(MpCallbackSearchChannel, MP_MEASURE_MODE, MP_MEASURE_ED_THRESHOLD, (u16)channel, MP_MEASURE_TIME);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpSearchChannel() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;  
}

  
/**
 * �e�@�Ƃ��ĕK�v�ȃp�����[�^��ݒ�
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestSetParentParameter(void)
{
  WMErrCode result;

  WMParentParam *param = MpGetParentParameter();
  MpUserGameInfo *info = MpGetUserGameInfo();
  MpDataParentMP *parent_data = MpGetDataParentMP();

  /* MpRequestSearchChannel�ŒT�����ꂽ�`�����l���ԍ����w�� */
  param->channel = parent_data->channel;
  
  param->userGameInfo = (u16*)info;
  param->userGameInfoLength = (u16)MpGetUserGameInfoSize();

  MpPrintf("MpRequestSetParentParameter() channel %d start.\n", param->channel);

  result = WM_SetParentParameter(MpCallbackSetParentParameter, param);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpSetParentParameter() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * �e�@�Ƃ��Ċ����J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestStartParent(void)
{
  WMErrCode result;

  MpPrintf("MpRequestStartParent() start.\n");

  result = WM_StartParent(MpCallbackStartParent);

  if (result != WM_ERRCODE_OPERATING) {

    MpPrintf("MpRequestStartParent() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * �q�@�Ƃ��Đe�@�̃X�L�����J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestStartScan(void)
{
  WMErrCode result;

  MpPrintf("MpRequestStartScan() start.\n");

  result = WM_StartScan(MpCallbackStartScan, MpGetScanParameter());

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartScan() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
   return FALSE;
  } else
    return TRUE;
}


/**
 * �q�@�Ƃ��ē���̐e�@�̃X�L�����J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestStartScan2(void)
{
  WMErrCode result;

  MpPrintf("MpRequestStartScan2() start.\n");

  {
    WMScanParam *scan_param = MpGetScanParameter();
    MpDataChildMP *dcmp = MpGetDataChildMP();

    /* �ڑ����MAC�A�h���X���w�肷�� */
    scan_param->bssid[0] = dcmp->user_list[dcmp->select].mac_vendor.u.data[0];
    scan_param->bssid[1] = dcmp->user_list[dcmp->select].mac_vendor.u.data[1];
    scan_param->bssid[2] = dcmp->user_list[dcmp->select].mac_addr.u.data[0];
    scan_param->bssid[3] = dcmp->user_list[dcmp->select].mac_addr.u.data[1];
    scan_param->bssid[4] = dcmp->user_list[dcmp->select].mac_addr.u.data[2];
    scan_param->bssid[5] = dcmp->user_list[dcmp->select].mac_addr.u.data[3];
  }
  
  result = WM_StartScan(MpCallbackStartScan2, MpGetScanParameter());

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartScan2() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
   return FALSE;
  } else
    return TRUE;
}


/**
 * �q�@�̐e�@�X�L�����I��
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestEndScan(void)
{
  WMErrCode result;

  MpPrintf("MpRequestEndScan() start.\n");
  
  result = WM_EndScan(MpCallbackEndScan);
  
  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestEndScan() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;

  } else
    
    return TRUE;
}


/**
 * �e�@�ւ̐ڑ��J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestStartConnect(void)
{
  WMErrCode result;

  MpSsidData *ssid_data = MpGetSsidData();  
  
  MpPrintf("MpRequestStartConnect() start.\n");

  result = WM_StartConnect(MpCallbackStartConnect, MpGetBssDesc(), (const u8*)ssid_data);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartConnect() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * �ڑ�����
 *
 * @param �Ώ�AID
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestDisConnect(u16 aid)
{
  WMErrCode result;

  MpPrintf("MpRequestDisConnect() start. target AID %d\n", aid);

  result = WM_Disconnect(MpCallbackDisConnect, aid);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestDisConnect() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * �����̎q�@�Ƃ̐ڑ����� �i�e�@��p�j
 *
 * @param �Ώ�AID�r�b�g�}�b�v
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestDisConnectChildren(u16 aid_bit)
{
  WMErrCode result;

  MpPrintf("MpRequestDisConnectChildren() start. target AID bitmap %x\n", aid_bit);

  result = WM_DisconnectChildren(MpCallbackDisConnectChildren, aid_bit);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestDisConnect() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * MP�ʐM���[�h�J�n
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestStartMP(void)
{
  WMErrCode result;
  
  MpPrintf("MpRequestStartMP() start.\n");

  MpPrintf("MpRequestStartMP() SetPortCallback start.\n");
  result = WM_SetPortCallback(MP_DEFAULT_PORT, MpCallbackReceiveData, NULL);

  if (result == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpRequestStartMP() SetPortCallback success.\n");

  } else {

    MpPrintf("WL_RequestStartMP() SetPortCallback failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  }


  result = WM_StartMP(MpCallbackStartMP,
		      MpGetRecvBuff(),
		      (u16)MpGetRecvBuffSize(),
		      MpGetSendBuff(),
		      (u16)MpGetSendBuffSize(),
		      (u16)(MpGetParentParameter()->CS_Flag ? 0 : 1));

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartMP() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * �����f�o�C�X�ɓd������
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestPowerOn(void)
{
  WMErrCode result;

  MpPrintf("MpRequestPowerOn() start.\n");
  result = WM_PowerOn(MpCallbackPowerOn);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestPowerOn() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * �����f�o�C�X�̓d��OFF
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestPowerOff(void)
{
  WMErrCode result;

  MpPrintf("MpRequestPowerOff() start.\n");
  result = WM_PowerOff(MpCallbackPowerOff);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestPowerOff failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestPowerOff() error");

    return FALSE;
  } else
    return TRUE;
}



/**
 * WM�����Z�b�g WM��READY�AIDLE�X�e�[�g�ȊO�S�ẴX�e�[�g����IDLE�X�e�[�g�Ɉڍs
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestReset(void)
{
  WMErrCode result;

  MpPrintf("MpRequestReset() start.\n");
  result = WM_Reset(MpCallbackReset);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestReset() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestReset() error");
    
    return FALSE;
  } else
    return TRUE;
}


/**
 * WM���I�� WM��IDLE�X�e�[�g���疳���@�\�S��~�Ɉڍs
 *
 * @return �G���[�����������ꍇFALSE���Ԃ�
 */
BOOL MpRequestEnd(void)
{
  WMErrCode result;

  MpPrintf("MpRequestReset() start.\n");
  result = WM_End(MpCallbackEnd);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestEnd() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestEnd() error");
    
    return FALSE;
  } else
    return TRUE;
}

//


