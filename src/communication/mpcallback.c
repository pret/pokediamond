/**
 * @version "$Id: mpcallback.c,v 1.2 2006/07/19 04:48:04 mitsuhara Exp $"
 *
 * @file mpcallback.c
 * @brief �����ʐM���C�u���� ��ԑJ�ڃR�[���o�b�N�֐�
 * 
 */
#include "mpconnect.h"
#include "mpcallback.h"
#include "mprequest.h"
#include "mpdata.h"
#include "mpdebug.h"


/**
 * �G���[�����̂���Reset���s��IDLE�X�e�[�^�X�ֈڍs
 */
static void MpErrorToReset(void)
{
#ifdef MP_DEBUG
  SDK_ASSERTMSG(MpGetStatus() != MP_STATUS_INIT,  "MpErrorToReset() bad status %d\n", MpGetStatus());
  SDK_ASSERTMSG(MpGetStatus() != MP_STATUS_READY, "MpErrorToReset() bad status %d\n", MpGetStatus());
  SDK_ASSERTMSG(MpGetStatus() != MP_STATUS_STOP,  "MpErrorToReset() bad status %d\n", MpGetStatus());
#endif  
  
  MpSetStatus(MP_STATUS_ERROR);
  (void)MpRequestReset();
}


static MpMACAddData MpBssIDToMACAddData(u8 *bssid)
{
  return MpMACAddArrayToMACAddData(bssid);
}
static MpMACVendorData MpBssIDToMACVendorData(u8 *bssid)
{
  return MpMACAddArrayToMACVendorData(bssid);
}


/**
 * �I���v���̂���Reset���s��IDLE�X�e�[�^�X�ֈڍs
 */
static BOOL MpResetForEnd(void)
{
  if (MpGetRequestStatus() == MP_STATUS_END) {

    MpInternalData *id = MpGetInternalData();

    if (id->request_end_flag == FALSE) {

      MpPrintf("MpResetForEnd() request [END] to Reset\n");
      (void)MpRequestReset();
      id->request_end_flag = TRUE;
    }

    return TRUE;
  } else
    return FALSE;
}


// �w��AID�̎q�@�𖢐ڑ���Ԃɂ���
static void MpSetupDisconnectChid(u32 aid)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();
  int i;
  
  for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
    if ((parent_data->user_list[i].mac_addr.u.data32) && 
	(parent_data->user_list[i].aid == aid)) {
      parent_data->user_list[i].data_trans_ready = 0;
      parent_data->user_list[i].connect_flag = 0;
    }
  }
}  


static u32 MpGetNextChannel(void)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();

  MpPrintf("MpGetNextChannel() channel bitmap %x\n", parent_data->channel_bitmap);
  
  if (parent_data->channel_bitmap & 1) {
    parent_data->channel_bitmap &= ~1;
    return 1;
  } else if (parent_data->channel_bitmap & (1<<6)) {
    parent_data->channel_bitmap &= ~(1<<6);
    return 7;
  } else if (parent_data->channel_bitmap & (1<<12)) {
    parent_data->channel_bitmap &= ~(1<<12);
    return 13;
  } else
    return 0;
}


/**
 * �ʐM�`�����l������������
 */
static BOOL MpSetupSearchChannel(void)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();

  parent_data->status = MP_PARENT_MP_STATUS_SEARCH_CHANNEL;

  parent_data->channel_bitmap = WM_GetAllowedChannel();

  MpPrintf("MpSetupSearchChannel() allowd channel bitmap %x\n", parent_data->channel_bitmap);
  
  if ((parent_data->channel_bitmap == 0) || (parent_data->channel_bitmap == 0x8000)) 
    return FALSE;
  else {
    parent_data->busy_ratio = MP_MEASURE_BUSYRATIO_MAX;
    parent_data->channel = 0;
    return TRUE;
  }
}


/**
 * �e�@����ݒ�
 */
static void MpSetupParentParameter(void)
{
  WMParentParam *param = MpGetParentParameter();
  
  MpPrintf("MpSetupParentParameter()\n");
  
  // �r�[�R���Ԋu��K�x�Ȓl�ɐݒ�
  param->beaconPeriod = WM_GetDispersionBeaconPeriod();

  // tempID��ݒ�
  param->tgid = WM_GetNextTgid();
}


/**
 * �q�@�̃X�L��������ݒ� MpRequestStartScan�̑O�ɌĂ΂��
 */
static void MpSetupScanParameter(void)
{  
  WMScanParam *scan_param = MpGetScanParameter();

  MpPrintf("MpSetupScanParameter()\n");
  
  scan_param->scanBuf = MpGetBssDesc();
  scan_param->channel = MpGetParentParameter()->channel;

  // �T�����x���Ԃ�K�x�Ȓl�ɐݒ�
  scan_param->maxChannelTime = WM_GetDispersionScanPeriod();

  /* �u���[�h�L���X�g�A�h���X���w�肵�ANINTENDO�̑S�@��T������悤�ݒ� */
  scan_param->bssid[0] = 0xff;
  scan_param->bssid[1] = 0xff;
  scan_param->bssid[2] = 0xff;
  scan_param->bssid[3] = 0xff;
  scan_param->bssid[4] = 0xff;
  scan_param->bssid[5] = 0xff;
}


static void MpSetupNextScanCannel(void)
{
  WMScanParam *scan_param = MpGetScanParameter();  
  u16 allowed_channel;
  s32 i;

  allowed_channel = WM_GetAllowedChannel();
  
  if (allowed_channel == 0) return;
  
  for (i=0; i<16; i++) {
    if (allowed_channel & (0x0001 << ((scan_param->channel + i) % 16))) {
      scan_param->channel = (u16)(((scan_param->channel + i) % 16) + 1);

      MpPrintf("MpSetupNextScanChannel() NextChannle %d \n", scan_param->channel);

      break;
    }
  }
}



/**
 * Indication�R�[���o�b�N�֐�
 */
void MpCallbackIndicate(void *arg)
{
  WMindCallback *cb = (WMindCallback *)arg;

  MpPrintf("MpCallbackIndicate() Indication. STATECODE: %x ", cb->state);

  MpPrintStateCode((WMStateCode)cb->state);
  
  if (cb->errcode == WM_ERRCODE_FIFO_ERROR) {
    // �����s�\�ȃG���[
    MpPrintf("MpCallbackIndicate() error\n");
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestSetMPDataToPort�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackSetMPDataToPort(void *arg)
 {
   //WMCallback *cb = (WMCallback *)arg;
   WMPortSendCallback *cb = (WMPortSendCallback *)arg;
   
   MpPrintf("MpCallbackSetMPDataToPort() ");
   MpPrintStateCode((WMStateCode)cb->state);
   
   if (cb->errcode == WM_ERRCODE_SUCCESS) {     
     MpPrintf("MpCallbackSetMPData() MpRequestSetMPData success.\n");
  } else {

    WMPortSendCallback *cb_PortSend = (WMPortSendCallback *)cb;
    MpPrintf("MpCallbackSetMPData() MpSetMPData failed. ERRCODE: %x %x %x restBitmap: %x\n", cb->errcode,
	       cb->wlCmdID, cb->wlResult, cb_PortSend->restBitmap);
    MpPrintErrorCode((WMErrCode)cb->errcode);
  }
  //if (wcBtCallback != NULL) (*wcBtCallback) (arg);
}


/**
 * MpRequestEnable�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackEnable(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackEnable() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackEnable() MpRequestEnable success.\n");

    // �X�e�[�^�X�ݒ�
    MpSetStatus(MP_STATUS_STOP);

    // �����I�����N�G�X�g���������ꍇ��Disable�Ɉڍs
    if (MpGetRequestStatus() == MP_STATUS_END) {
      MpPrintf("MpCallbackEnable() request [END] to Disable\n");
      MpRequestDisable();
      MpSetStatus(MP_STATUS_STOP);
      return;
    }
    
    // �����f�o�C�X�ɓd������
    if (MpRequestPowerOn() == FALSE) {
      MpRequestDisable();
      MpSetStatus(MP_STATUS_STOP);
      return;
    }

  } else {

    MpPrintf("MpCallbackEnable() MpRequestEnable failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpRequestDisable();

  }
}


/**
 * MpRequestDisable�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackDisable(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackDisable() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpCallbackDisable() MpRequestDisable success.\n");

    // �����I�����N�G�X�g���������ꍇ�͖������C�u�������I��
    if (MpGetRequestStatus() == MP_STATUS_END) {
      MpPrintf("MpCallbackDisable() request [END] to Finish\n");
      WM_Finish();
      MpSetStatus(MP_STATUS_END);

      // �������C�u�����̏I�����L�^
      MpSetIsEnd(TRUE);
      return;
    }

    MpSetStatus(MP_STATUS_READY);

  } else {
    
    MpPrintf("MpCallbackDisable() MpRequestDisable failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackDisable() MpRequestDisable callback error\n");
  }
}


/**
 * MpRequestSearchChannel�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
void MpCallbackSearchChannel(void *arg)
{
  WMMeasureChannelCallback *cb = (WMMeasureChannelCallback *)arg;

  MpPrintf("MpCallbackSearchChannel() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpDataParentMP *parent_data = MpGetDataParentMP();

    MpPrintf("MpCallbackSearchChannel() busy ratio %d (%d ch) / %d (%d ch)\n",
	     cb->ccaBusyRatio, cb->channel, parent_data->busy_ratio, parent_data->channel);
    
    if (parent_data->busy_ratio > cb->ccaBusyRatio) {
      parent_data->busy_ratio = (u8)cb->ccaBusyRatio;
      parent_data->channel = (u8)cb->channel;
    }

    {
      /* ���̃`�����l���擾 */
      u32 next_channel = MpGetNextChannel();

      MpPrintf("MpCallbackSearchChannel() next channel %d\n", next_channel);
      
      /* ���̃`�����l���̓d�g�g�p������ */
      if (next_channel) {	
	if (MpRequestSearchChannel(next_channel) == FALSE) MpErrorToReset();
      } else {

	/* �d�g�g�p���̒Ⴂ�`�����l�������������ꍇ�A�e�@�Ɉڍs */
	if (parent_data->busy_ratio < MP_MEASURE_BUSYRATIO_MAX) {
	
	  /* �e�@�p�̃p�����[�^�ݒ� */
	  MpSetupParentParameter();

	  /* �e�@�p�����[�^�ݒ�Ɉڍs */ 
	  if (MpRequestSetParentParameter() == FALSE) MpErrorToReset();
	} else
	  MpErrorToReset();
      }
    }
  } else {

    MpPrintf("MpCallbackSearchChannel() MpRequestSearchChannel failed. ERRCODE: %x %x %x\n",
	     cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestSetParentParameter�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
void MpCallbackSetParentParameter(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackSetParentParameter() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpCallbackSetParentParameter() MpRequestSetParentParameter() success.\n");

    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;
    
    if (MpRequestStartParent() == FALSE) MpErrorToReset();
    
  } else {
    
    MpPrintf("MpCallbackSetParentParameter() MpRequestSetParentParameter failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}



/**
 * MpRequestStartParent�̃R�[���o�b�N�֐�
 *
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
void MpCallbackStartParent(void *arg)
{
  WMstartParentCallback *cb = (WMstartParentCallback *)arg;

  MpPrintf("MpCallbackStartParent() ");
  MpPrintStateCode((WMStateCode)cb->state);
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpDataParentMP *parent_data = MpGetDataParentMP();

    /* �X�e�[�^�X��e�@�ڑ��ς݂ɐݒ� */
    MpSetStatus(MP_STATUS_PARENT);

    /* �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs */
    if (MpResetForEnd()) return;

    if (parent_data->status == MP_PARENT_MP_STATUS_SEARCH_CHANNEL)
      /* �e�@�X�e�[�^�X��ڑ��҂��� */
      parent_data->status = MP_PARENT_MP_STATUS_WAIT_CONNECT;
    
    switch (cb->state) {

    case WM_STATECODE_PARENT_START:
      MpPrintf("MpCallbackStartParent() MpRequestStartParent success.\n");
      
      if (MpRequestStartMP() == FALSE) MpErrorToReset();
      else MpSetAid(0);
      break;

    case WM_STATECODE_CONNECTED:
      MpPrintf("MpCallbackStartParent() Child Connected.\n");
      MpPrintDataParentMP(MpGetDataParentMP());
      
      if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

	MpSsidData *ssid = (MpSsidData *)cb->ssid;

	MpPrintf("MpCallbackStartParent() ParentState WAIT_CONNECT .\n");
	MpPrintf("MpCallbackStartParent() protcol %d(%d) ver %d(%d) connect id %d (%d)\n",
		 ssid->header.data0.protocol_id,
		 MpGetProtocolID(),
		 ssid->header.data0.protocol_version,
		 MpGetProtocolVersion(),
		 ssid->header.data1.connect_id,
		 MpGetConnectID());
	
	if (
	    /* �v���g�R��ID����v���邩 */
	    (ssid->header.data0.protocol_id == MpGetProtocolID()) &&
	    /* �Ή��\�ȃo�[�W������ */
	    (ssid->header.data0.protocol_version <= MpGetProtocolVersion()) &&
	    /* �ڑ�ID����v���邩���m�F */
	    (ssid->header.data1.connect_id == MpGetConnectID())) {

	  int i;
	  MpDataParentMP *parent_data = MpGetDataParentMP();	  
	  MpMACAddData mac_connect = MpBssIDToMACAddData(cb->macAddress);
	  MpMACVendorData vnd_connect = MpBssIDToMACVendorData(cb->macAddress);

	  for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	    MpMACAddData *mac_data = &parent_data->user_list[i].mac_addr;

	    /* ���o��MAC�A�h���X�̏ꍇ�p�X */
	    if (mac_data->u.data32 == mac_connect.u.data32) {
	      /* AID��ConnectFlag���Đݒ� */
	      parent_data->user_list[i].aid = cb->aid;
	      parent_data->user_list[i].connect_flag = 1;
	      break;
	    }
	    
	    /* ���L�^�̃o�b�t�@������΁A������MAC�A�h���X��AID���L�^ */
	    if (mac_data->u.data32 == 0) {
	      parent_data->user_list[i].mac_addr.u.data32 = mac_connect.u.data32;
	      parent_data->user_list[i].mac_vendor.u.data16 = vnd_connect.u.data16;
	      parent_data->user_list[i].aid = cb->aid;
	      parent_data->user_list[i].connect_flag = 1;
	      break;			
	    }
	  }
	}
      }
      break;

    case WM_STATECODE_BEACON_SENT:
      MpPrintf("MpCallbackStartParent() Beacon sent.\n");
      break;

    case WM_STATECODE_DISCONNECTED:
      MpPrintf("MpCallbackStartParent() Child disconnected.\n");
      MpSetupDisconnectChid((u32)cb->aid);
      break;
    }
  } else {
    
    MpPrintf("MpCallbackStartParent() MpRequestStartParent failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * �w�肳�ꂽbssid��MpMACAddData�ɒǉ�
 */
static BOOL MpReceiveMPAddParentAddr(WMstartScanCallback *cb, WMBssDesc *bss_desc)
{
  int i;
  MpDataChildMP *dcmp = MpGetDataChildMP();
  MpMACAddData mac_bss = MpBssIDToMACAddData(bss_desc->bssid);
  MpMACVendorData vnd_bss = MpBssIDToMACVendorData(bss_desc->bssid);

  for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
    MpMACAddData *mac_data = &dcmp->user_list[i].mac_addr;
    MpMACVendorData *vnd_data = &dcmp->user_list[i].mac_vendor;
    
    /* ���o��MAC�A�h���X�̏ꍇ�p�X */
    if ((mac_data->u.data32 == mac_bss.u.data32) && (vnd_data->u.data16 == vnd_bss.u.data16))
      return TRUE;

    /* ���L�^�̃o�b�t�@������΁A������MAC�A�h���X��UserName���L�^ */
    if (mac_data->u.data32 == 0) {
      dcmp->user_list[i].mac_addr.u.data32 = mac_bss.u.data32;
      dcmp->user_list[i].name = ((MpUserGameInfo*)bss_desc->gameInfo.userGameInfo)->data.name;
      dcmp->user_list[i].user_id = ((MpUserGameInfo*)bss_desc->gameInfo.userGameInfo)->data.user_id;
      dcmp->user_list[i].mac_vendor.u.data16 = vnd_bss.u.data16;
      dcmp->user_list[i].link_level = (u8)cb->linkLevel;
      return TRUE;
    }
  }

  /* �e�@���X�g����t�ɂȂ����ꍇ */
  return FALSE;
}


static void MpCallbackStartScanParentNotFound(void)
{
  /* �X�L�����̃p�����[�^��ύX */
  MpSetupNextScanCannel();

  /* �������X�L���������s���� */
  if (MpRequestStartScan() == FALSE) MpErrorToReset();
}


/**
 * MpCallbackStartScan�Őe�@���������ꂽ�ꍇ�̏���
 *
 * @param cb WM_StartScan�̃R�[���o�b�N�̈���
 * @return �ăX�L�������s���ꍇFALSE��Ԃ�
 */
static BOOL MpCallbackStartScanParentFound(WMstartScanCallback *cb)
{
  WMBssDesc *bss_desc = MpGetBssDesc();
  MpDataChildMP *child_data = MpGetDataChildMP();

  MpPrintf("MpCallbackStartScanParentFound() TimeCount %d\n", child_data->time_count);

  /* ���Z�b�g�v���̃`�F�b�N */
  if (MpResetForEnd()) return TRUE;

#if 1
  {
    int find_flag = 0;
    int i;
    for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
      MpMACAddData *mac_data = &child_data->user_list[i].mac_addr;
      if (mac_data->u.data32) {
	find_flag = 1;
	break;
      }
    }
  
    /* �^�C���A�E�g�̃`�F�b�N */
    if ((find_flag != 0) && (child_data->time_count == 0)) {
      
      /* EndScan�X�e�[�^�X�Ɉڍs */
      if (MpRequestEndScan() == FALSE) MpErrorToReset();
      return TRUE;
    }
  }
#endif
  
  /* �e�@���i�[�o�b�t�@�̃L���b�V����j�� */
  DC_InvalidateRange(bss_desc, sizeof(WMbssDesc));
  
  MpPrintDataChildMP(MpGetDataChildMP());	    
  MpPrintf("MpCallbackStartScanParentFound() InfoLength %d ScanGameID %x GameID %x\n",
	   bss_desc->gameInfoLength,
	   bss_desc->gameInfo.ggid,
	   MpGetGameID());
  
  /* GameGroupID����v���邩���m�F */
  if ((cb->gameInfoLength >= 8) && (bss_desc->gameInfo.ggid == MpGetGameID())) {
      
    MpUserGameInfo *info = (MpUserGameInfo*)bss_desc->gameInfo.userGameInfo;

    MpPrintf("MpCallbackStartScanParentFound() protcol %d(%d) ver %d(%d) connect id %d (%d)\n",
	     info->header.data0.protocol_id,
	     MpGetProtocolID(),
	     info->header.data0.protocol_version,
	     MpGetProtocolVersion(),
	     info->header.data1.connect_id,
	     MpGetConnectID());

    if (
	/* �v���g�R��ID����v���邩 */
	(info->header.data0.protocol_id == MpGetProtocolID()) &&
	/* �Ή��\�ȃo�[�W������ */
	(info->header.data0.protocol_version <= MpGetProtocolVersion()) &&
    	/* �ڑ�ID����v���邩���m�F */
	(info->header.data1.connect_id == MpGetConnectID())) {

      /* �ڑ��Ώۂ��L�� */
      if (MpReceiveMPAddParentAddr(cb, bss_desc)) {
	
	/* �e�@�����񐔂̏���ɒB�������m�F */
	MpDataChildMP *child_data = MpGetDataChildMP();
	if (++child_data->scan_retry_count > MP_NUM_RECEIVE_MP_RETRY) {
	    
	  MpPrintf("MpCallbackStartScanParentFound() over retry count (%d/%d)\n", child_data->scan_retry_count, MP_NUM_RECEIVE_MP_RETRY);

	  /* EndScan�X�e�[�^�X�Ɉڍs */
	  if (MpRequestEndScan() == FALSE) {
	    MpErrorToReset();
	    return TRUE;
	  }
	}
      } else {
	
	MpPrintf("MpCallbackStartScanParentFound() over parent list buff\n");
	
	/* �ڑ��Ώۂ������ς��ɂȂ����̂�EndScan�X�e�[�^�X�Ɉڍs */
	if (MpRequestEndScan() == FALSE) MpErrorToReset();
	return TRUE;
      }
    }
  }
  return FALSE;
}


/**
 * MpRequestStartScan�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
void MpCallbackStartScan(void *arg)
{
  WMstartScanCallback *cb = (WMstartScanCallback *)arg;
 
  MpPrintf("MpCallbackStartScan() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackStartScan() MpRequestStartScan success.\n");
    
    {
      WMBssDesc *bss_desc = MpGetBssDesc();
      MpPrintBssDesc(bss_desc);
    }
    
    /* �X�e�[�^�X���X�L�������ɐݒ� */
    MpSetStatus(MP_STATUS_SCAN);    

    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;
    
    /* ���[�h���̃X�e�[�^�X�ݒ� */
    switch (MpGetMode()) {
    case MP_MODE_CHILD_MP :
      {
	MpDataChildMP *dcmp = MpGetDataChildMP();
	dcmp->status = MP_CHILD_MP_STATUS_SCAN_1;
      }
      break;
    }
    
    switch (cb->state) {
      
    case WM_STATECODE_PARENT_FOUND :

      MpPrintf("MpCallbackStartScan() Callback MACAddr %02x %02x %02x %02x %02x %02x \n",
		 cb->macAddress[0],
		 cb->macAddress[1],
		 cb->macAddress[2],
		 cb->macAddress[3],
		 cb->macAddress[4],
		 cb->macAddress[5]);

      
      MpPrintf("MpCallbackStartScan() Callback GGID %x \n", cb->gameInfo.ggid);      
      
      if (MpCallbackStartScanParentFound(cb) != FALSE) break;

      // Don't break here.
      // �����Ă������X�L���������s
      
    case WM_STATECODE_PARENT_NOT_FOUND :
      MpCallbackStartScanParentNotFound();
      break;
	
    default :
      MpPrintf("- Invalid state code. STATECODE: %x\n", cb->state);
      MpPrintErrorCode((WMErrCode)cb->errcode);
      MpErrorToReset();
      break;
    }
  } else {
    MpPrintf("WM_CallbackStartScan() WM_RequestStartScan() failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpCallbackStartScan2�Őe�@���������ꂽ�ꍇ�̏���
 *
 * @param cb WM_StartScan�̃R�[���o�b�N�̈���
 * @return �ăX�L�������s���ꍇFALSE��Ԃ�
 */
static BOOL MpCallbackStartScan2ParentFound(void)
{
  WMBssDesc *bss_desc = MpGetBssDesc();
  MpDataChildMP *child_data = MpGetDataChildMP();
  WMParentParam *parent_param = MpGetParentParameter();

  MpPrintf("MpCallbackStartScan2ParentFound()\n");

  /* ���Z�b�g�v���̃`�F�b�N */
  if (MpResetForEnd()) return TRUE;

#if 0
  /* �^�C���A�E�g�̃`�F�b�N */
  if (child_data->time_count == 0) {

    /* EndScan�X�e�[�^�X�Ɉڍs */
    if (MpRequestEndScan() == FALSE) {
      MpErrorToReset();
    }
    return TRUE;
  }    
#endif
  
  /* �e�@���i�[�o�b�t�@�̃L���b�V����j�� */
  DC_InvalidateRange(bss_desc, sizeof(WMbssDesc));
  
  MpPrintDataChildMP(MpGetDataChildMP());
  
  /* GameGroupID����v���邩���m�F */
  if ((bss_desc->gameInfoLength >= 8) && (bss_desc->gameInfo.ggid == MpGetGameID())) {
      
    MpUserGameInfo *info = (MpUserGameInfo*)bss_desc->gameInfo.userGameInfo;

    if (
	/* �v���g�R��ID����v���邩 */
	(info->header.data0.protocol_id == MpGetProtocolID()) &&
	/* �Ή��\�ȃo�[�W������ */
	(info->header.data0.protocol_version <= MpGetProtocolVersion()) &&
    	/* �ڑ�ID����v���邩���m�F */
	(info->header.data1.connect_id == MpGetConnectID())) {
    
      /*  */
      MpMACAddData mac_bss = MpBssIDToMACAddData(bss_desc->bssid);
      MpMACAddData *mac_data = &child_data->user_list[child_data->select].mac_addr;
      
      if (mac_data->u.data32 == mac_bss.u.data32) {
	
	/* EndScan�X�e�[�^�X�Ɉڍs */
	if (MpRequestEndScan() == FALSE) MpErrorToReset();
	return TRUE;
      }
    }
  }
  return FALSE;
}
	

/**
 * MpRequestStartScan2�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\���� 
 */
void MpCallbackStartScan2(void *arg)
{
  WMstartScanCallback *cb = (WMstartScanCallback *)arg;
 
  MpPrintf("MpCallbackStartScan2() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpDataChildMP *dcmp = MpGetDataChildMP();
    MpPrintf("MpCallbackStartScan2() MpRequestStartScan2 success.\n");

    /* ���[�h���̃X�e�[�^�X�ݒ� */
    dcmp->status = MP_CHILD_MP_STATUS_SCAN_2;

     /* �X�e�[�^�X���X�L�������ɐݒ� */
    MpSetStatus(MP_STATUS_SCAN);    

    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;
    
    switch (cb->state) {
      
    case WM_STATECODE_PARENT_FOUND :

      if (MpCallbackStartScan2ParentFound() != FALSE) break;

      // Don't break here.
      // �����Ă������X�L���������s
      MpPrintf("MpCallbackStartScan2() ReScan start.\n");

      
    case WM_STATECODE_PARENT_NOT_FOUND :
      /* �X�L�����̃p�����[�^��ύX */
      MpSetupNextScanCannel();

      /* �������X�L���������s���� */
      if (MpRequestStartScan2() == FALSE) MpErrorToReset();
      break;
	
    default :
      MpPrintf("- Invalid state code. STATECODE: %x\n", cb->state);
      MpPrintErrorCode((WMErrCode)cb->errcode);
      MpErrorToReset();
      break;
    }
  } else {
    MpPrintf("WM_CallbackStartScan2() WM_RequestStartScan2() failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestEndScan�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackEndScan(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackEndScan() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("WM_CallbackEndScan() MpRequestEndScan success.\n");
    MpSetStatus(MP_STATUS_ENDSCAN);

    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;
    
    if (MpGetMode() == MP_MODE_CHILD_MP) {
      MpDataChildMP *dcmp = MpGetDataChildMP();

      /* �ڑ��J�n�̂��߂̃X�L������̏ꍇ */
      if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_2) {

	/* �q�@�Ƃ��ăR�l�N�g�J�n */
	if (MpRequestStartConnect() == FALSE) MpErrorToReset();
	else MpSetStatus(MP_STATUS_IDLE);
      }
    }    
  } else {

    MpPrintf("MpCallbackEndScan() MpCallbackEndScan failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestStartConnect�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackStartConnect(void *arg)
{
  WMstartConnectCallback *cb = (WMstartConnectCallback *)arg;

  MpPrintf("MpCallbackStartConnect() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackStartConnect() MpRequestStartConnect success.\n");    
    
    /* �X�e�[�^�X���q�@�ڑ����ɐݒ� */
    MpSetStatus(MP_STATUS_CHILD);    

    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;
    
    switch (cb->state) {
    case WM_STATECODE_CONNECT_START:
      // CONNECTED�ɂȂ�̂�҂̂ŁA�����Ȃ�
      break;

    case WM_STATECODE_CONNECTED:
      // ���蓖�Ă�ꂽAID��ޔ�
      MpSetAid(cb->aid);

      // �ڑ��ʒm
      MpSetIsConnectFlag(TRUE);
      MpSetDisconnectTrigger(FALSE);
      
#if 0      
      // ���Ɏq�@�̏ꍇ�͉������Ȃ�
      if (MpGetStatus() == MP_STATUS_CHILD) {
	MpPrintf("MpCallbackStartConnect() - Connected , but already child mode.\n");

      } else {

	/* MP�ʐM���J�n */
	MpPrintf("MpCallbackStartConnect() MpRequestStartConnect success.\n");
	if (MpRequestStartMP() == FALSE) MpErrorToReset();

      }
#else
      /* MP�ʐM���J�n */
      MpPrintf("MpCallbackStartConnect() MpRequestStartConnect success.\n");
      if (MpRequestStartMP() == FALSE) MpErrorToReset();
#endif      
      break;

    case WM_STATECODE_BEACON_LOST:
      MpPrintf("MpCallbackStartConnect() - Beacon from parent lost.\n");
      // �r�[�R���������������ł̓��Z�b�g���Ȃ�
      break;

    case WM_STATECODE_DISCONNECTED:
      MpPrintf("MpCallbackStartConnect() - DisConnected from parent.\n");

      if (MpIsConnectFlag()) MpSetDisconnectTrigger(TRUE);
      MpSetIsConnectFlag(FALSE);            
#if 0      
      if (MpGetStatus() != MP_STATUS_BUSY) {
	(void)MpRequestReset();
      }
#endif      
      break;

    default:
      MpPrintf("MpCallbackStartConnect() MpRequestStartConnect failed. Invalid state code. STATECODE: %x\n", cb->state);
      MpPrintErrorCode((WMErrCode)cb->errcode);
      MpErrorToReset();
    }
    
  } else {
    
    MpPrintf("MpCallbackStartConnect() MpRequestStartConnect failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    
    if (cb->errcode == WM_ERRCODE_NO_ENTRY) MpPrintf(" ! Parent doesn't accept entry now.\n");
    if (cb->errcode == WM_ERRCODE_OVER_MAX_ENTRY) MpPrintf(" ! Over max entry of BSS group.\n");

    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


static void MpCallbackNextStateFromIdele(void)
{
  switch (MpGetMode()) {
  case MP_MODE_PARENT_MP :

#if 0    
    /* �e�@�p�̃p�����[�^�ݒ� */
    MpSetupParentParameter();

    /* �e�@�p�����[�^�ݒ�Ɉڍs */ 
    if (MpRequestSetParentParameter() == FALSE) MpErrorToReset();
    else MpSetStatus(MP_STATUS_IDLE);

#else
    
    /* �ʐM�`�����l������������ */
    if ((MpSetupSearchChannel() != FALSE) &&
	(MpRequestSearchChannel(MpGetNextChannel()) != FALSE)) {
      MpDataParentMP *parent_data = MpGetDataParentMP();
      parent_data->status = MP_PARENT_MP_STATUS_SEARCH_CHANNEL;
      MpSetStatus(MP_STATUS_IDLE);
    } else
      MpErrorToReset();
#endif    
    break;

  case MP_MODE_CHILD_MP :

    /* �q�@�̃X�L�����J�n�p�p�����[�^�ݒ� */
    MpSetupScanParameter();

    /* �q�@�X�L�����Ɉڍs */
    if (MpRequestStartScan() == FALSE) MpErrorToReset();
    else MpSetStatus(MP_STATUS_IDLE);
    break;
  }
}


/**
 * MpRequestDisConnect�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackDisConnect(void *arg)
{
  WMDisconnectCallback *cb = (WMDisconnectCallback *)arg;

  MpPrintf("MpCallbackDisConnect()\n");

  /* �X�e�[�^�X��IDLE��� */
  MpSetStatus(MP_STATUS_IDLE);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackDisConnect() MpRequestDisConnect success.\n");    

    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;

    MpCallbackNextStateFromIdele();
    
    if (MpIsConnectFlag()) MpSetDisconnectTrigger(TRUE);
    MpSetIsConnectFlag(FALSE);            
    
  } else {
    MpPrintf("MpCallbacDisConnect() MpRequestDisConnect failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestDisConnectChildren�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackDisConnectChildren(void *arg)
{
  WMDisconnectCallback *cb = (WMDisconnectCallback *)arg;

  MpPrintf("MpCallbackDisConnectChildren()\n");

  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    u16 cb_bitmap = cb->disconnectedBitmap;
    int i;
    
    MpPrintf("MpCallbackDisConnectChildren() MpRequestDisConnectChildren success.\n");    
    MpPrintf("MpCallbackDisConnectChildren() disconnect bitmap %x.\n", cb_bitmap);

    for (i=1; i<16; i++) {
      u32 aid_bitmap = 1 << i;
      if (cb_bitmap & aid_bitmap)
	MpSetupDisconnectChid(i);
    }
    
    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;
  } else {
    MpPrintf("MpCallbacDisConnectChildren() MpRequestDisConnectChildren failed. ERRCODE: %x %x %x\n",
	     cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}



/**
 * MpRequestStatMP�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackStartMP(void *arg)
{
  WMstartMPCallback *cb = (WMstartMPCallback *)arg;

  MpPrintf("MpCallbackStartMP() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    if (cb->apiid == WM_APIID_START_MP) {
      if (MpResetForEnd()) return;
    }
    
    switch (MpGetMode()) {
    case MP_MODE_PARENT_MP :
      MpSetStatus(MP_STATUS_PARENT_MP); break;
    case MP_MODE_CHILD_MP :
      MpSetStatus(MP_STATUS_CHILD_MP); break;
    }
    
    switch (cb->state) {
    case WM_STATECODE_MP_START:
      MpPrintf("MpCallbackStartMP() MpRequestStartMP success.\n");
      //if (wcBtCallback != NULL) (*wcBtCallback) (arg);
      break;

    case WM_STATECODE_MPEND_IND:
      // �e�@�Ƃ��Ă̑���M��������indicate
      break;

    case WM_STATECODE_MP_IND:
      // �q�@�Ƃ��Ă̎�M��������indicate
      break;
    }
  } else {

    switch (cb->errcode) {

    case WM_ERRCODE_SEND_FAILED:
    case WM_ERRCODE_TIMEOUT:
      // ����M���������Ȃ������ꍇ��indicate
      // �Ȃɂ������ɍđ������̂�҂�
      break;      

    case WM_ERRCODE_INVALID_POLLBITMAP:
      // �������ł͂Ȃ� MP �ʐM���󂯎�����ꍇ�� indicate
      break;

    default:
      MpPrintf("WM_CallbackStartMP() MpRequestStartMP failed. ERRCODE: %x %x\n", cb->errcode, cb->state);
      MpErrorToReset();
    }
  }
}


static void MpUpdateSendData(void)
{
  MpTransData *td = MpGetTransData();  
  u32 send_size = MpGetSendBuffSize() - MpGetSendHeaderSize();

  /* �V�[�P���X�ԍ��X�V */
  //td->sequence_num++;
  
  if (td->size > send_size) {
    td->size -= send_size;
    (u8*)td->data += send_size;
  } else {
    td->size = 0;
  }
}



static void MpCallbackReceiveDataSendMp(WMPortRecvCallback *cb)
{
  MpTransData *td = MpGetTransData();

  MpPrintf("MpCallbackReceiveDataSendMp() TRANS MODE SEND trans status %d\n", td->state);  
  
  /* �����҂����H */
  if (td->state == MP_TRANS_STATUS_WAIT) {

    MpSendHeader *header = (MpSendHeader *)td->recv_buff;
    
    /* ��M�f�[�^�𕜍� */
    DC_FlushRange(cb->data, cb->length);	      
    MI_CpuCopy8(cb->data, td->recv_buff, cb->length);

    if (
	/* �v���g�R��ID����v���邩 */
	(header->data0.protocol_id == MpGetProtocolID()) &&
	/* �Ή��\�ȃo�[�W������ */
	(header->data0.protocol_version <= MpGetProtocolVersion())) {
      
      /* ��M�f�[�^�𕜍� */
      MpDecodeRecvData(td->recv_buff);

      /* �ʐM�ԍ�����v���Ă��邩 */
      if (header->data2.sequence_num != td->seq_num) return;
      
      MpPrintSendHeader((MpSendHeader *)td->recv_buff);
      
      /* �f�[�^��CRC�`�F�b�N */
      if ((MpCheckRecvData(td->recv_buff)) && 

	  /* �đ��v���ł͂Ȃ�*/
	  (header->data2.control_code != MP_CONTROL_CODE_RETRY)) {

	// ��M���m�F �ʐM����
	MpPrintf("MpCallbackReceiveData() TRANS MODE SEND recv success !!!\n");
	td->state = MP_TRANS_STATUS_SUCCESS;
      } else {

	/* ��M���s �i�đ��v��orCRC�G���[�j������x���M����*/
	td->state = MP_TRANS_STATUS_ENABLE;
      }
    }
  }
}



static void MppCallbackReceiveDataRecvMpReady(WMPortRecvCallback *cb)
{
  MpTransData *td = MpGetTransData();

  MpPrintf("MppCallbackReceiveDataRecvMpReady() MP_MODE_PARENT_MP only\n");

  if ((MpGetMode() == MP_MODE_PARENT_MP) && (td->state != MP_TRANS_STATUS_SUCCESS)) {
    
    MpSendHeader *header = (MpSendHeader *)td->recv_buff;
    
    DC_FlushRange(cb->data, cb->length);	      
    MI_CpuCopy8(cb->data, td->recv_buff, cb->length);

    if (
	/* �v���g�R��ID����v���邩 */
	(header->data0.protocol_id == MpGetProtocolID()) &&
	/* �Ή��\�ȃo�[�W������ */
	(header->data0.protocol_version <= MpGetProtocolVersion())) {
      
      /* ��M�f�[�^�𕜍� */
      MpDecodeRecvData(td->recv_buff);
      
      /* �ʐM�ԍ�����v���Ă��邩 */
      if (header->data2.sequence_num != MP_SEQUENCE_READY) return;
      else {
	MpDataParentMP *parent_data = MpGetDataParentMP();
	int i;

	for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	  if (parent_data->user_list[i].aid == cb->aid) {
	    
	    MpPrintf("MppCallbackReceiveDataRecvMpReady() find child AID %d\n", cb->aid);
	    
	    parent_data->user_list[i].data_trans_ready = 1;
	    parent_data->user_list[i].data_trans_count = MP_RECV_READY_SEND_NUM;
	    
	    td->time_out = 180;

	    td->state = MP_TRANS_STATUS_ENABLE;

	    break;
	  }
	}
      }
    }
  }
}


static void MpCallbackReceiveDataRecvMp(WMPortRecvCallback *cb)
{
  MpTransData *td = MpGetTransData();
  
  MpPrintf("MpCallbackReceiveDataRecvMp() PrintHeader TRANS MODE RECV\n");
    
  /* �f�[�^�]��������Ԃ��H */
  if (td->seq_num == MP_SEQUENCE_READY) {

    MppCallbackReceiveDataRecvMpReady(cb);

  } else {
     
    /* �����҂����H */
    if (((td->state == MP_TRANS_STATUS_WAIT) || (td->state == MP_TRANS_STATUS_READY)) && (td->resend_count == 0)) {
      
      MpSendHeader *header = (MpSendHeader *)td->recv_buff;
      
      DC_FlushRange(cb->data, cb->length);	      
      MI_CpuCopy8(cb->data, td->recv_buff, cb->length);
      
      if (
	  /* �v���g�R��ID����v���邩 */
	  (header->data0.protocol_id == MpGetProtocolID()) &&
	  /* �Ή��\�ȃo�[�W������ */
	  (header->data0.protocol_version <= MpGetProtocolVersion())) {
	
	/* ��M�f�[�^�𕜍� */
	MpDecodeRecvData(td->recv_buff);
      
	/* �ʐM�ԍ�����v���Ă��邩 */
	if (header->data2.sequence_num != td->seq_num) return;
	
	MpPrintSendHeader((MpSendHeader *)td->recv_buff);
	
	/* ���M�\�ɂ��� */
	td->state = MP_TRANS_STATUS_ENABLE;
	
	/* �f�[�^��CRC�`�F�b�N */
	if (MpCheckRecvData(td->recv_buff)) {
	  
	  MpPrintf("MpCallbackReceiveData() TRANS MODE RECV recv success\n");
	  
	  /* �f�[�^���M���� */
	  if (header->data2.sequence_num == MP_SEQUENCE_READY) {
	    MppCallbackReceiveDataRecvMpReady(cb);
	    
	  } else {
	    
	    /* ��M�o�b�t�@�Ƀf�[�^��]�� */
	    MI_CpuCopy8((u8*)td->recv_buff + header->data3.header_size, td->data, header->data3.data_size);
	  }
	  
	  /* ��M���� ���������|�𑗐M���� */
	  header->data2.control_code = MP_CONTROL_CODE_ACKNOWLEDGE;
	  
	  /* �����̑��M���s���񐔎w�� */
	  td->resend_count = MP_RECV_ACKNOWLEDGE_SEND_NUM;
	} else {
	  
	  /* CRC�G���[���������̂ōđ��v�� */
	  header->data2.control_code = MP_CONTROL_CODE_RETRY;
	}
      }
    }
  }
}


/**
 * WM_SetPortCallback�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackReceiveData(void *arg)
{
  WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;
  
  MpPrintf("MpCallbackReceiveData() ");
  MpPrintStateCode((WMStateCode)cb->state);

#if 0  
  // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
  if (MpGetRequestStatus() == MP_STATUS_END) {
    MpPrintf("MpCallbackReceiveData() request [END] to Reset\n");
    (void)MpRequestReset();
    return;
  }
#endif  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpCallbackReceiveData() MpRequestStartMP Receive Data success.\n");

    switch (cb->state) {

    case WM_STATECODE_PORT_RECV:

      // �f�[�^��M
      switch (MpGetStatus()) {

      case MP_STATUS_PARENT_MP:
      case MP_STATUS_CHILD_MP:
	{
	  MpTransData *td = MpGetTransData();

	  switch (td->mode) {
	  case MP_TRANS_MODE_SEND :
	    /* �f�[�^���M���[�h���H */
	    MpCallbackReceiveDataSendMp(cb); break;

	    /* �f�[�^��M���[�h���H */
	  case MP_TRANS_MODE_RECV :
	    MpCallbackReceiveDataRecvMp(cb); break;
	  }
	}
	break;
      }
      break;

    case WM_STATECODE_CONNECTED:


      // �ڑ��ʒm
      MpSetIsConnectFlag(TRUE);
      MpSetDisconnectTrigger(FALSE);
      break;

    case WM_STATECODE_DISCONNECTED:

      MpPrintf("MpCallbackReceiveData() Disconnect.\n");

      if (MpIsConnectFlag()) MpSetDisconnectTrigger(TRUE);
      
      // �ؒf�ʒm
      switch (MpGetStatus()) {
      case MP_STATUS_PARENT_MP:       
	// main���ɐؒf��ʒm
	//if (wcMpRecvCallback != NULL) wcMpRecvCallback(cb->aid, NULL, 0);
	MpSetupDisconnectChid((u32)cb->aid);
	break;

      case MP_STATUS_CHILD_MP:
	// main���ɐؒf��ʒm
	MpSetIsConnectFlag(FALSE);      
	break;
      }
      break;
    }
  } else {
    MpPrintf("MpCallbackReceiveData() MpRequestStartMP Receive Data failed. ERRCODE: %x\n", cb->errcode);
  }
}


/**
 * MpRequestPowerOn�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackPowerOn(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackPowerOn() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackPowerOn() MpRequestPowerOn success.\n");

    // �����I�����N�G�X�g���������ꍇ��Reset�Ɉڍs
    if (MpResetForEnd()) return;

    MpCallbackNextStateFromIdele();

  } else {
    MpPrintf("MpCallbackPowerOn() MpRequestPowerOn failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackPowerOn() callback error\n");

  }
}


/**
 * MpRequestPowerOff�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackPowerOff(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackPowerOff() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackPowerOff() MpRequestPowerOff success.\n");

    if (MpRequestDisable() == FALSE) {
      //OS_Panic("MpCallbackPowerOff() MpRequestDisable == FALSE\n");
      ;
    } else {

      /* �X�e�[�^�X���~��Ԃ� */
      MpSetStatus(MP_STATUS_STOP);
    }
      } else {

    MpPrintf("MpCallbacPoweOff() MpRequestPowerOff failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestReset�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackReset(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackReset() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackReset() MpRequestReset success.\n");

    /* AID���Z�b�g */
    MpSetAid(0);

    //if (wcBtCallback != NULL) (*wcBtCallback)(arg);

    if (MpGetRequestStatus() == MP_STATUS_END) {
      if (MpRequestEnd() == FALSE) {
	//OS_Panic("MpCallbackReset() MpRequestReset == FALSE\n");
	;
      } else
	MpSetStatus(MP_STATUS_IDLE);
    } else {
    
      if (MpRequestPowerOff() == FALSE) {
	//OS_Panic("MpCallbackReset() MpRequestReset == FALSE\n");
	;
      } else
	MpSetStatus(MP_STATUS_IDLE);
    }
  } else {
    MpPrintf("MpCallbackReset() MpRequestReset() failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackReset() callback error\n");
  }
}


/**
 * MpRequestEnd�̃R�[���o�b�N�֐�
 *
 * @param arg WM�񓯊������֐��p�\����
 */
void MpCallbackEnd(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackEnd() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackEnd() MpRequestEnd success.\n");
    MpSetStatus(MP_STATUS_END);

    // �������C�u�����̏I�����L�^
    MpSetIsEnd(TRUE);

  } else {
    MpPrintf("MpCallbackEnd() MpRequestEnd() failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackEnd() callback error\n");
  }
}


//
