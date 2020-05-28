/**
 * @version "$Id: mpconnect.c,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpconnect.c
 * @brief MP�����ʐM���C�u����
 * 
 */
#include "mpconnect.h"
#include "mpdata.h"
#include "mprequest.h"
#include "mpcallback.h"
#include "mpdebug.h"


/**
 * Indication�R�[���o�b�N�֐���ݒ肷��
 *
 * @return ���������������ꍇ��TRUE��Ԃ��A�G���[�̏ꍇ��FALSE��Ԃ�
 */
static BOOL MpSetIndicationCallback(void)
{
  WMErrCode result;

  MpPrintf("MpSetIndicationCallback() start.\n");

  result = WM_SetIndCallback(MpCallbackIndicate);

  if (result != WM_ERRCODE_SUCCESS) {
    MpPrintf("MpSetIndicationCallback() failed. ERRCODE: %x\n", result);
    MpSetStatus(MP_STATUS_ERROR);
    return FALSE;
  }
  
  MpPrintf("MpSetIndicationCallback() success.\n");

  return TRUE;
}


/**
 * MP�ʐM���J�n���� 
 */
static void MpStartMp(void)
{
  switch (MpGetStatus()) {
  case MP_STATUS_INIT:
  case MP_STATUS_STOP:
  case MP_STATUS_READY:
    (void)MpRequestEnable();
    break;
    
  default :
    MpPrintf("MpStartMp() fail state %d\n", MpGetStatus());
    //OS_Panic("MpStartMp() state %d error\n", MpGetStatus());
    break;
  }
}


static void MpSetMpData(const void *buf, u32 size, u16 aid_bitmap)
{
  const WMParentParam *parent_param = MpGetParentParameter();

  MpPrintf("MpSetParentData() start.\n");
  
  // ���M�f�[�^�T�C�Y�m�F
  if (size > parent_param->parentMaxSize) {
    MpPrintf("MpSetParentData() size over (%d/%d)\n", size, parent_param->parentMaxSize);
    return;
  }
  
  MpPrintf("MpSetParentData() call MpRequestSetMPData()\n");

  DC_FlushRange((void*)buf, size);

  (void)MpRequestSetMPData(buf, size, aid_bitmap);
}


/**   
 * ���M�ɕK�v�ȃo�b�t�@�T�C�Y�����߂�
 *
 * @return �o�b�t�@�̃o�C�g��
 */
static u32 MpGetSendBufferSize(void)
{
  u32 parent_size;
  u32 child_size;
  u32 size;
  
  parent_size = (u32)WM_SIZE_MP_PARENT_RECEIVE_BUFFER(MP_CHILD_DATA_SIZE, MP_CONNECT_CHILD_MAX, FALSE);
  child_size = (u32)WM_SIZE_MP_CHILD_RECEIVE_BUFFER(MP_PARENT_DATA_SIZE, FALSE);
  size = (parent_size > child_size) ? parent_size : child_size;

  return size;
}


/**
 * ��M�ɕK�v�ȃo�b�t�@�T�C�Y�����߂�
 *
 * @return �o�b�t�@�̃o�C�g��
 */
static u32 MpGetRecvBufferSize(void)
{
  u32 parent_size;
  u32 child_size;
  u32 size;
  
  parent_size = (s32)WM_SIZE_MP_PARENT_RECEIVE_BUFFER(MP_CHILD_DATA_SIZE, MP_CONNECT_CHILD_MAX, FALSE);
  child_size = (s32)WM_SIZE_MP_CHILD_RECEIVE_BUFFER(MP_PARENT_DATA_SIZE, FALSE);
  size =(parent_size > child_size) ? parent_size : child_size;

  return size;
}


/**
 * �������C�u�������g�p����o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�C�g��
 */
u32 MpGetBufferSize(void)
{
  u32 total_size = WM_SYSTEM_BUF_SIZE;
  MpPrintf("MpGetBufferSize() \n\tsystem buffer size \t%d\n", WM_SYSTEM_BUF_SIZE);
  
  total_size += MpGetSendBufferSize() << 1;
  MpPrintf("\tsend buffer size \t%d\n", MpGetSendBufferSize());
  MpPrintf("\ttrans (send) buffer size \t%d\n", MpGetSendBufferSize());

  total_size += MpGetRecvBufferSize() << 1;
  MpPrintf("\trecv buffer size \t%d\n", MpGetRecvBufferSize());
  MpPrintf("\ttrans (recv) buffer size \t%d\n", MpGetSendBufferSize());
  
  total_size += sizeof(WMBssDesc);
  MpPrintf("\tWMBssDesc size \t%d\n", sizeof(WMBssDesc));  

  total_size += sizeof(WMScanParam);
  MpPrintf("\tWMScanParam size \t%d\n", sizeof(WMScanParam));  

  total_size += 0x20;
  MpPrintf("\tfor align  size \t%d\n", 0x20);

  MpPrintf("\ttotal size \t%d\n", total_size);
  return total_size;
}


/**
 * ���C�u����������
 *
 * @param init_desc �������f�[�^
 * @param buff ���C�u�����̎g�p����o�b�t�@�̃A�h���X���w�� MpGetBufferSize()�Ŏ擾����T�C�Y�̈悪�m�ۂ���Ă���K�v������
 */
void MpInit(MpInitDesc* init_desc, void* buff)
{
  WMParentParam *pp = MpGetParentParameter();
  MpInternalData *id = MpGetInternalData();

  /* �o�b�t�@��32byte�A���C�����g����Ă���K�v������ */
  void* org_buff = buff;
  u32 md = (u32)buff & 0x01F;
  MpPrintf("MpInit() buffer address %x ", buff);
  if (md) {
    md = 0x20 - ((u32)buff & 0x01F);
    buff = (void*)((u32)buff + md);
  }
  MpPrintf("(%x)\n", buff);

  
#if DEBUG_MP
  {
    u8 mac_addr[6];
    u32 i;
    
    OS_GetMacAddress(mac_addr);

    MpPrintf("MpInit() MAC address : ");
    for (i=0; i<sizeof(mac_addr); i++) MpPrintf("%02x ", mac_addr[i]);      
    MpPrintf("\n");

    MpPrintf("MpInit() send buffer size %d  recv buffer size %d\n",
	       MpGetSendBufferSize(),
	       MpGetRecvBufferSize());
  }
#endif
    

  /* �X�e�[�^�X������ */
  id->status = (u8)MP_STATUS_INIT;
  id->request_status = (u8)MP_STATUS_INIT;
  
  /* �ʐM���[�h������ */
  id->mode = (u8)MP_MODE_NONE;

  /* �ʐM�|�[�g�ԍ��ݒ� */
  id->port = MP_DEFAULT_PORT;
  
  /* GemID�ݒ� */
  id->ggid = MP_GGID;

  /* AID������ */
  id->aid = 0;
  
  /* WM���C�u�����p�o�b�t�@�ݒ� */
  id->lib_buff = buff;
  (u8*)buff += WM_SYSTEM_BUF_SIZE;
  
  /* ���M�o�b�t�@�p�������ݒ� */
  id->send_buff = buff;
  (u8*)buff += id->send_buff_size = MpGetSendBufferSize();
  
  /* ��M�o�b�t�@�p�������ݒ� */
  id->recv_buff = buff;
  (u8*)buff += id->recv_buff_size = MpGetRecvBufferSize();

  /* BssDesc�ݒ� */  
  id->bss_desc = buff;
  (u8*)buff += sizeof(WMBssDesc);

  /* WMScanParam�ݒ� */
  id->scan_parameter = buff;
  (u8*)buff += sizeof(WMScanParam);
  
  /* WM ���C�u���������� */
  (void)WM_Init(id->lib_buff, MP_DMA_NO);

  /* Indication�R�[���o�b�N�֐��ݒ� */
  id->indication_callback_flag = MpSetIndicationCallback();

  id->connect_flag = FALSE;
  id->disconnect_trigger = FALSE;
  
  id->request_end_flag = FALSE;
  id->is_end_flag = FALSE;
  
  /* �v���R�g��ID�ݒ� */
  id->user_game_info.header.data0.protocol_id = MP_PROTOCOL_ID;
  
  /* �v���R�g���o�[�W�����ݒ� */
  id->user_game_info.header.data0.protocol_version = MP_PROTOCOL_VERSION;

  /* ��������ʐݒ� */
  id->user_game_info.header.data0.encode_type = MP_ENCODE_TYPE_TYCHO;
  
  id->user_game_info.header.data1.game_id = init_desc->game_id;
  id->user_game_info.header.data1.game_version = init_desc->game_version;
  id->user_game_info.header.data1.language = init_desc->language;
  id->user_game_info.header.data1.connect_id = init_desc->connect_id;
  {
    const u16* name = init_desc->name;
    const u16* user_id = init_desc->user_id;
    u32 count = 0;
    while ((name) && (count < MP_USERGAMEINFO_NAME_LENGTH)) {
      id->user_game_info.data.name.data[count] = *name;
      id->user_game_info.data.user_id.data[count] = *user_id;
      count++;
      name++;
      user_id++;
    }
  }

  /* SSID�f�[�^������ */
  id->ssid_data.header = *(MpSsidHeader*)&id->user_game_info.header;
  
  /* �f�[�^�]���p�\���̂������� */
  MpInitTransData();
  MpGetTransData()->send_buff = buff;
  (u8*)buff += id->send_buff_size;
  MpGetTransData()->recv_buff = buff;
  (u8*)buff += id->recv_buff_size;

  MpPrintf("MpInit() use buff %x \n", (u32)buff - (u32)org_buff);
  
  /* TGID�ݒ�̂��ߍŏ��J���ǂ݁i�����RTC���g�p���邽�߁j */
  (void)WM_GetNextTgid();
}


/**
 * MP�ʐM���M���v���Z�X
 */
static void MpProcStatusMpSend(void)
{
  MpTransData *td = MpGetTransData();

  /* �Ԏ��҂����H */
  if (td->state == MP_TRANS_STATUS_WAIT) {

    if (--td->time_out > 0) return;

    /* ��莞�Ԍo�ߌ�ɍđ��M���� */ 
    MpPrintf("MpProcStatusMp() MODE_SEND TimeOut to ReSend\n");
    td->state = MP_TRANS_STATUS_ENABLE;
  }
    
  /* ���M�\���H */
  if (td->state == MP_TRANS_STATUS_ENABLE) {
    
    u32 send_size = MP_SEND_DATA_SIZE - MpGetSendHeaderSize();
    u32 size = send_size;
    
    MP_CONTROL_CODE cc = MP_CONTROL_CODE_DATA_END;
    
    MpPrintf("MpProcStatusMp() MODE_SEND : SendData data %x size %d CC %d \n",
	     td->data, size, cc);

    /* ���M�f�[�^���� */
    MpSetupSendData(td->send_buff, td->data, size, cc, td->seq_num);
    
    /* ���M�v�� */
    MpSetMpData(td->send_buff, size + MpGetSendHeaderSize(), 0xFFFF);

    /* �X�e�[�^�X��Ԏ��҂��ɐݒ� */
    td->state = MP_TRANS_STATUS_WAIT;	

    /* �Ԏ��҂��ł���t���[�����ݒ� */
    td->time_out = 60;
  }
}




/**
 * MP�ʐM��M���v���Z�X
 */
static void MpProcStatusMpRecv(void)
{
  MpTransData *td = MpGetTransData();

#if 0  
  /* ���M�\���H */
  if (td->state == MP_TRANS_STATUS_WAIT) {

    /* �Ԏ��҂� */ 
    if (--td->time_out > 0) return;

    MpPrintf("MpProcStatusMp() MODE_RECV TimeOut to ReSend\n");
    td->state = MP_TRANS_STATUS_ENABLE;
  }
#endif

  /* ���M�\���H */
  if (td->state == MP_TRANS_STATUS_ENABLE) {
  
    /* �f�[�^���M�V�[�P���X�̏ꍇ�̏��� */
    if (td->seq_num == (u8)MP_SEQUENCE_READY) {
      MpDataParentMP *parent_data = MpGetDataParentMP();
      int i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	if (parent_data->user_list[i].data_trans_count) {
	  MP_CONTROL_CODE cc = MP_CONTROL_CODE_ACKNOWLEDGE;

	  u16 send_bitmap = (u16)(1 << parent_data->user_list[i].aid);
	  
	  MpPrintf("MpProcStatusMp() MODE_RECV : DequenceReady SendData data %x size 0 aid %d, ControlCode %s \n",
		   td->data, parent_data->user_list[i].aid, MpPrintControlCode(cc));      
	  
	  /* ���M�f�[�^���� */
	  MpSetupSendData(td->send_buff, td->data, 0, cc, MP_SEQUENCE_READY);
	
	  /* ���M�v�� */
	  MpSetMpData(td->send_buff, MpGetSendHeaderSize(), send_bitmap);
	  
	  parent_data->user_list[i].data_trans_count--;
	  return;
	}
      }

      if (--td->time_out == 0)
	/* �S�Ă̕ԐM�ɉ����I�� */
	td->state = MP_TRANS_STATUS_SUCCESS;
      
    } else {

      /* �ʏ�̎�M���� */
      u32 send_size = MpGetSendBufferSize() - MpGetSendHeaderSize();
      MP_CONTROL_CODE cc;
      
      MpSendHeader *header = (MpSendHeader *)td->recv_buff;
      
      /* MpCallbackReceiveDataRecvMp()�Őݒ肳�ꂽ�ʐM�̐���R�[�h�擾 */
      cc = (MP_CONTROL_CODE)header->data2.control_code;
      
      // �ʐM�����̏ꍇ
      if (cc == MP_CONTROL_CODE_ACKNOWLEDGE) {
	
	// �����̘A�����S�ďI���������_��MP_TRANS_STATUS_SUCCESS�ɂ���
	if (td->resend_count == 0) {
	  td->state = MP_TRANS_STATUS_SUCCESS;
	  return;
	} else {
	  td->resend_count--;
	}
      }
      
      MpPrintf("MpProcStatusMp() MODE_RECV : SendData data %x size 0 ControlCode %s \n",
	       td->data, MpPrintControlCode(cc));      
      
      /* ���M�f�[�^���� */
      MpSetupSendData(td->send_buff, td->data, 0, cc, td->seq_num);
      
      /* ���M�v�� */
      MpSetMpData(td->send_buff, MpGetSendHeaderSize(), 0xFFFF);
    }
  }
  
}

static void MpProcStatusMp(void)
{
  MpTransData *td = MpGetTransData();

  switch (td->mode) {
  case MP_TRANS_MODE_SEND :
    MpProcStatusMpSend(); break;

  case MP_TRANS_MODE_RECV :
    MpProcStatusMpRecv(); break;
  }
}


static void MpProcChildMP(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  /* �����X�e�[�^�X�ɂ���ď����𕪊� */
  switch (MpGetStatus()) {    
    
  case MP_STATUS_SCAN :
    // �^�C���A�E�g�p�J�E���^�X�V
    if (dcmp->time_count) dcmp->time_count--;
    break;

  case MP_STATUS_CHILD_MP :
    MpProcStatusMp();
    break;
  default :
    break;
    
  }  
}

static void MpProcParentMP(void)
{
  /* �����X�e�[�^�X�ɂ���ď����𕪊� */
  switch (MpGetStatus()) {

  case MP_STATUS_PARENT_MP :
    MpProcStatusMp();
    break;

  default :
    break;
  }  
}



void MpProc(void)
{ 
  if (MpGetStatus() == MP_STATUS_END) return;

  //MpPrintf("Proc() Link %d\n", (u32)WM_GetLinkLevel());
  MpPrintf("AID %d Connect %d / %d \n", MpGetAid(), MpGetDataTransListNum(), MpGetConnectListNum());

  
  if (MpGetRequestStatus() == MP_STATUS_END) {
    if (MpGetStatus() == MP_STATUS_ENDSCAN) MpRequestReset();
    return;
  }
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
    MpProcChildMP(); break;

  case MP_MODE_PARENT_MP :
    MpProcParentMP(); break;
    
  default :
    {
      MpInternalData *id = MpGetInternalData();  

      /* �����X�e�[�^�X�ɂ���ď����𕪊� */
      switch (MpGetStatus()) {
	
      case MP_STATUS_INIT :	/* ��������̏�� �������Ȃ� */
	//MpPrintf("MpProc() status INIT\n");
	break;
      
      case MP_STATUS_READY :	/*  */
	//MpPrintf("MpProc() status READY\n");
	break;
	
      case MP_STATUS_BUSY:
	//MpPrintf("MpProc() status BUSY\n");    
	break;
	
      case MP_STATUS_SCAN :
      case MP_STATUS_ENDSCAN :
      
      break;
      
      case MP_STATUS_PARENT:
	break;
	
      case MP_STATUS_CHILD:
	//MpPrintf("MpProc() status CHILD\n");    
	break;
	
      default :
	//OS_Printf("MpProc() unknown status %d\n", MpGetStatus());
	;
      }
    }
  }
}


/**
 * �e�@�Ƃ��ĒʐM�J�n
 */
void MpRequestParent()
{
  // �e�@��p�f�[�^������
  MpInitDataParentMP();

  // MP�ʐM�J�n�i�e�@�j  
  MpSetMode(MP_MODE_PARENT_MP);
  MpStartMp();  
}


/**
 * �q�@�Ƃ��Đe�@�̃X�L�����J�n
 */
void MpRequestScan()
{
  // �q�@��p�f�[�^������
  MpInitDataChildMP();

  // MP�ʐM�J�n�i�q�@�j
  MpSetMode(MP_MODE_CHILD_MP);
  MpStartMp();  
}


/**
 * �e�@���X�g�̍ő吔���擾
 *
 * @return �ő吔
 */
static u32 MpGetParentListMax()
{
  return MP_SIZE_RECEIVE_MP_PARENT_LIST;
}


/**
 * �������ꂽ�e�@�̐���Ԃ�
 *
 * @return �e�@�̐�
 */
static u32 MpGetParentListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 list_count = 0;
  
#if DEBUG_MP
  if (mode != MP_MODE_CHILD_MP)
    OS_Panic("MpGetParentListNum() illegal mode (%d)\n", mode);
#endif

  /* MP�ʐM�i�q�@�j���[�h�̏ꍇ */
  if (mode == MP_MODE_CHILD_MP) {
    MpDataChildMP *dcmp = MpGetDataChildMP();

    /* �X�L�������^�X�L�����I���̃X�e�[�^�X�̏ꍇ�̂ݗL�� */
    if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_1) {

      /* MAC�A�h���X���L�^����Ă��鐔���v�� */ 
      u32 i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {

	if (dcmp->user_list[i].mac_addr.u.data32 != 0) list_count++;
      }
    }  
  }

  MpPrintf("MpGetParentListNum() find parent %d\n", list_count);
  
  return list_count;
}


/**
 * �w��ԍ��̐e�@�Ɛڑ��\�����ׂ�
 *
 * @param �e�@�ԍ�
 * @return �\�ȏꍇTRUE���Ԃ�
 */
BOOL MpGetConnectParentEnable(u32 num)
{
  if ((MpGetMode() == MP_MODE_CHILD_MP) && (MpGetStatus() == MP_STATUS_ENDSCAN)) {
    MpDataChildMP *dcmp = MpGetDataChildMP();
    if ((dcmp->status == MP_CHILD_MP_STATUS_SCAN_1) && (dcmp->user_list[num].mac_addr.u.data32))
      return TRUE;
  }

  return FALSE;
}


/**
 * �w��ԍ��̐e�@�Ɛڑ����� �ڑ��s�\�̏ꍇ�͉������Ȃ�
 *
 * @param �e�@�ԍ�
 */
void MpConnectParent(u32 num)
{
  /* MP�ʐM�i�q�@�j���[�h�̏ꍇ */
  if ((MpGetMode() == MP_MODE_CHILD_MP) && (MpGetStatus() == MP_STATUS_ENDSCAN)) {
    
    MpDataChildMP *dcmp = MpGetDataChildMP();

    if ((dcmp->status == MP_CHILD_MP_STATUS_SCAN_1) && (dcmp->user_list[num].mac_addr.u.data32)) {
    
      dcmp->select = (u8)num;
      dcmp->time_count = 120;

      //if (MpRequestStartScan2() == FALSE) MpErrorToReset();
      MpRequestStartScan2();
      
    }
  }  
}


/**
 * �e�@�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 */
void MpDisConnectParent(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_2) {
    if (MpIsConnectFlag()) MpRequestDisConnect(0);
  }
}


/**
 * �S�Ă̎q�@�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 */
void MpDisConnectChild(void)
{
  MpRequestDisConnectChildren(0xFFFF);
}



/**
 * �ڑ��ς݂̐e�@�ԍ���Ԃ� �ڑ���ԂɂȂ��ꍇ��MP_ERROR_CODE���Ԃ�
 *
 * @return �e�@�ԍ�
 */
u32 MpGetConnectParentNum(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_2) {
    return dcmp->select;
  }

  return MP_ERROR_CODE;
}


/**
 * �w��ڑ��ԍ��̐e�@�̖��O���擾
 *
 * @param num �e�@�ԍ�
 * @return ���O�iu16*�j
 */
u16* MpGetParentListName(u32 num)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();
  return (u16*)&dcmp->user_list[num].name;
}


/**
 * �w��ڑ��ԍ��̐e�@�̃��[�U�[ID���擾
 *
 * @param num �e�@�ԍ�
 * @return ���O�iu16*�j
 */
u16* MpGetParentListUserID(u32 num)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();
  return (u16*)&dcmp->user_list[num].user_id;
}


/**
 * �w��ڑ��ԍ��̐e�@��MAC�A�h���X���擾
 *
 * @param num �e�@�ԍ�
 * @return MAC�A�h���X
 */
static u32 MpGetParentListMacAddr(u32 num)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();
  return dcmp->user_list[num].mac_addr.u.data32;
}


/**
 * �q�@���X�g�̍ő吔���擾
 *
 * @return �ő吔
 */
static u32 MpGetChildListMax()
{
  return MP_SIZE_RECEIVE_MP_CHILD_LIST;
}


/**
 * �ڑ����ꂽ�q�@�̐���Ԃ�
 *
 * @return �q�@�̐�
 */
static u32 MpGetChildListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 list_count = 0;
  
#if DEBUG_MP
  if (mode != MP_MODE_PARENT_MP) OS_Panic("MpGetChildListNum() illegal mode (%d)\n", mode);
#endif

  /* MP�ʐM�i�e�@�j���[�h�̏ꍇ */
  if (mode == MP_MODE_PARENT_MP) {
    MpDataParentMP *parent_data = MpGetDataParentMP();

    /* �ڑ��҂����X�e�[�^�X�̏ꍇ�̂ݗL�� */
    if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

      /* MAC�A�h���X���L�^����Ă��鐔���v�� */ 
      u32 i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {

	if ((parent_data->user_list[i].mac_addr.u.data32 != 0) && 
	    (parent_data->user_list[i].connect_flag))
	  list_count++;
      }
    }  
  }

  MpPrintf("MpGetChildListNum() find child %d\n", list_count);
  
  return list_count;
}


/**
 * �f�[�^�ʐM�\�Ȏq�@�̐���Ԃ�
 *
 * @return �q�@�̐�
 */
static u32 MpGetEnableChildListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 list_count = 0;
  
#if DEBUG_MP
  if (mode != MP_MODE_PARENT_MP) OS_Panic("MpGetEnableChildListNum() illegal mode (%d)\n", mode);
#endif

  /* MP�ʐM�i�e�@�j���[�h�̏ꍇ */
  if (mode == MP_MODE_PARENT_MP) {
    MpDataParentMP *parent_data = MpGetDataParentMP();

    /* �ڑ��҂����X�e�[�^�X�̏ꍇ�̂ݗL�� */
    if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

      /* MAC�A�h���X���L�^����Ă��鐔���v�� */ 
      u32 i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
	if ((parent_data->user_list[i].mac_addr.u.data32 != 0) &&
	    (parent_data->user_list[i].data_trans_ready != 0) && 
	    (parent_data->user_list[i].connect_flag))
	  list_count++;
      }
    }  
  }
  
  MpPrintf("MpGetEnableChildListNum() find child %d\n", list_count);
  
  return list_count;
}


static u32 MpConnectNumToTransNum(u32 num)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();
  u32 list_count = 0;
  u32 i;

  for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
    if ((parent_data->user_list[i].mac_addr.u.data32 != 0) &&
	(parent_data->user_list[i].data_trans_ready != 0) &&
	(parent_data->user_list[i].connect_flag)) {
      
      if (list_count == num) return i;
      list_count++;
    }
  }
  return 0;
}


/**
 * �w��ڑ��ԍ��̎q�@��MAC�A�h���X���擾
 *
 * @param num �q�@�ԍ�
 * @return MAC�A�h���X
 */
static u32 MpGetChildListMacAddr(u32 num)
{
  MpDataParentMP *dpmp = MpGetDataParentMP();
  return dpmp->user_list[num].mac_addr.u.data32;
}


/**
 * �w��ԍ��ȊO�̎q�@�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 *
 * @param num �q�@�ԍ�
 */
void MpConnectOnlyChild(u32 num)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();

  MpPrintf("MpConnectOnlyChild() child num %d AID %d\n", num, parent_data->user_list[num].aid);
  
  if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

    u32 aid_bit = 0xFFFFFFFF;

    u32 mask = 1 << (parent_data->user_list[num].aid);

    aid_bit ^= mask;

    MpRequestDisConnectChildren((u16)aid_bit);
  }
}


/**
 * �w��MAC�A�h���X�̎q�@�ȊO�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 *
 * @param num �q�@��MAC�A�h���X
 */
void MpDataTransOnlyChild(u32 only_addr)
{
#if 1
  MpDataParentMP *parent_data = MpGetDataParentMP();
  u32 list_count = 0;
  u32 i;

  u32 aid_bit = 0;

  MpPrintf("MpDataTransOnlyChild() addr %x\n");
  
  for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {

    MpPrintf("No %02d addr %x trans ready %d connect flag %d aid %d\n",
	     i,
	     parent_data->user_list[i].mac_addr.u.data32,
	     parent_data->user_list[i].data_trans_ready,
	     parent_data->user_list[i].connect_flag,
	     parent_data->user_list[i].aid);

    if ((parent_data->user_list[i].mac_addr.u.data32 != 0) &&
	(parent_data->user_list[i].mac_addr.u.data32 != only_addr) && 
	//(parent_data->user_list[i].data_trans_ready != 0) &&
	(parent_data->user_list[i].connect_flag)) {

      u32 mask = 1 << (parent_data->user_list[i].aid);
      aid_bit |= mask;
    }
  }

  MpPrintf("MpDataTransOnlyChild() disconnect aid bitmap %x\n", aid_bit);

  if (aid_bit) MpRequestDisConnectChildren((u16)aid_bit);

#else  
  MpConnectOnlyChild(MpConnectNumToTransNum(num));
#endif
}


/**
 * �����N���x���擾
 *
 * @return �����N���x
 */
u32 MpGetConnectLinkLevel(void)
{
  MpInternalData *id = MpGetInternalData();
  
  if (!id->is_end_flag)
    return (u32)WM_GetLinkLevel();
  else
    return 0;
}


/**
 * �ڑ��\�ȍő吔���擾
 *
 * @return �ő吔
 */
u32 MpGetConnectListMax(void)
{
  MP_MODE mode = MpGetMode();
  u32 num;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    num = MpGetParentListMax();
    break;
  case MP_MODE_PARENT_MP :
    num = MpGetChildListMax();
    break;
  default :
    num = 0;
    break;
  }
  return num;
}


/**
 * �ڑ����ꂽ����Ԃ�
 *
 * @return �ڑ���
 */
u32 MpGetConnectListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 num;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    num = MpGetParentListNum();
    break;
  case MP_MODE_PARENT_MP :
    num = MpGetChildListNum();
    break;
  default :
    num = 0;
    break;
  }
  return num;
}


/**
 * �f�[�^�ʐM�\�Ȑ���Ԃ�
 *
 * @return �ڑ���
 */
u32 MpGetDataTransListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 num;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    num = 0;
    break;
  case MP_MODE_PARENT_MP :
    num = MpGetEnableChildListNum();
    break;
  default :
    num = 0;
    break;
  }
  return num;
}


/**
 * �w��ڑ��ԍ���MAC�A�h���X���擾
 *
 * @param num �ڑ��ԍ�
 * @return MAC�A�h���X
 */
u32 MpGetListMacAddr(u32 num)
{
  MP_MODE mode = MpGetMode();
  u32 mac;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    mac = MpGetParentListMacAddr(num);
    break;
  case MP_MODE_PARENT_MP :
    mac = MpGetChildListMacAddr(num);
    break;
  default :
    mac = 0;
    break;
  }
  return mac;
}


/**
 * �w��f�[�^�ʐM�ԍ���MAC�A�h���X���擾
 *
 * @param num �f�[�^�ʐM�ԍ�
 * @return MAC�A�h���X
 */
u32 MpGetTransMacAddr(u32 num)
{
  return MpGetListMacAddr(MpConnectNumToTransNum(num));
}


/**
 * �f�[�^�̑��M�������s��
 */
void MpSetSendRedy(void)
{
  MpTransData *trans_data = MpGetTransData();
  MpUserGameInfo *user_game_info = MpGetUserGameInfo();

  MpPrintf("MpSetSendReady() state %d \n", MpGetStatus());

  if (MpGetMode() == MP_MODE_CHILD_MP) {
  
    trans_data->mode     = MP_TRANS_MODE_SEND;
    trans_data->state    = MP_TRANS_STATUS_ENABLE;
    trans_data->org_data = (void*)&user_game_info->data;
    trans_data->data     = (void*)&user_game_info->data;
    trans_data->org_size = 0;
    trans_data->size     = 0;
    trans_data->time_out = 120;  
    trans_data->resend_count = 0;  
    trans_data->seq_num  = (u8)MP_SEQUENCE_READY;  
  }
}


/**
 * ���[�U�[�f�[�^�̑��M���s��
 */
void MpSetSendUserData(void)
{
  MpTransData *trans_data = MpGetTransData();
  MpUserGameInfo *user_game_info = MpGetUserGameInfo();
  
  trans_data->mode     = MP_TRANS_MODE_SEND;
  trans_data->state    = MP_TRANS_STATUS_ENABLE;
  trans_data->org_data = (void*)&user_game_info->data;
  trans_data->data     = (void*)&user_game_info->data;
  trans_data->org_size = sizeof(MpUserGameInfoData);
  trans_data->size     = sizeof(MpUserGameInfoData);
  trans_data->time_out = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num  = (u8)MP_SEQUENCE_USER_DATA;  
}


/**
 * �f�[�^�𑗐M���s��
 *
 * @param data �f�[�^���M�o�b�t�@
 * @param size ���M�T�C�Y
 * @param seq_num �ʐM�ԍ�
 */
void MpSetSendData(void *data, u32 size, u32 seq_num)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetSendData() state %d data %x size %d sequence %d\n", MpGetStatus(), data, size, seq_num);

  if ((MP_SEQUENCE)seq_num > MP_SEQUENCE_APP_END) {
    MpPrintf("MpSetSendData() sequence %d over\n", seq_num);
    return;
  }
  
  trans_data->mode     = MP_TRANS_MODE_SEND;
  trans_data->state    = MP_TRANS_STATUS_ENABLE;
  trans_data->org_data = data;
  trans_data->data     = data;
  trans_data->org_size = size;
  trans_data->size     = size;
  trans_data->time_out = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num  = (u8)seq_num;  
}


/**
 * ���[�U�[�f�[�^�̎�M�o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�C�g��
 */
u32 MpGetUserDataSize(void)
{
  return sizeof(MpUserGameInfoData);
}


/**
 * �f�[�^�̎�M�������s��
 */
void MpSetRecvReady(void)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetRecvReady() state %d \n", MpGetStatus());

  if (MpGetMode() == MP_MODE_PARENT_MP) {
  
    trans_data->mode         = MP_TRANS_MODE_RECV;
    trans_data->state        = MP_TRANS_STATUS_READY;
    trans_data->org_data     = NULL;
    trans_data->data         = NULL;
    trans_data->org_size     = 0;
    trans_data->size         = 0;
    trans_data->time_out     = 120;  
    trans_data->resend_count = 0;  
    trans_data->seq_num  = (u8)MP_SEQUENCE_READY;  
  }
}


/**
 * ���[�U�[�f�[�^�̎�M���s�� ��M�o�b�t�@�T�C�Y��sizeof(MpUserGameInfoData)
 *
 * @param data �f�[�^��M�o�b�t�@
 */
void MpSetRecvUserData(void *data)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetRecvUserData() state %d data %x size %d \n", MpGetStatus(), data, sizeof(MpUserGameInfoData));
  
  trans_data->mode         = MP_TRANS_MODE_RECV;
  trans_data->state        = MP_TRANS_STATUS_READY;
  trans_data->org_data     = data;
  trans_data->data         = data;
  trans_data->org_size     = sizeof(MpUserGameInfoData);
  trans_data->size         = 0;
  trans_data->time_out     = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num      = (u8)MP_SEQUENCE_USER_DATA;  
}


/**
 * �f�[�^����M���s��
 *
 * @param data �f�[�^��M�o�b�t�@
 * @param size ��M�T�C�Y
 * @param seq_num �ʐM�ԍ�
 */
void MpSetRecvData(void *data, u32 size, u32 seq_num)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetRecvData() state %d data %x size %d sequence %d\n", MpGetStatus(), data, size, seq_num);

  if ((MP_SEQUENCE)seq_num > MP_SEQUENCE_APP_END) {
    MpPrintf("MpSetRecvData() sequence %d over\n", seq_num);
    return;
  }
  
  trans_data->mode         = MP_TRANS_MODE_RECV;
  trans_data->state        = MP_TRANS_STATUS_READY;
  trans_data->org_data     = data;
  trans_data->data         = data;
  trans_data->org_size     = size;
  trans_data->size         = 0;
  trans_data->time_out     = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num      = (u8)seq_num;  
}


/**
 * ���M�����f�[�^�̃T�C�Y���擾����
 *
 * @return ���M�o�C�g��
 */
u32 MpGetSendDataSize(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();
	  if (td->mode == MP_TRANS_MODE_SEND) size = td->org_size - td->size;
	}
	break;
      }
      
    }
    break;
  }
    
  return size;
}


/**
 * ��M�����f�[�^�̃T�C�Y���擾����
 *
 * @return ���M�o�C�g��
 */
u32 MpGetRecvDataSize(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();
	  if (td->mode == MP_TRANS_MODE_RECV) size = td->size;
	}
	break;
      }
      
    }
    break;
  }
    
  return size;
}


/**
 * �f�[�^���M���I�����������ׂ�
 *
 * @return �I�����Ă���ꍇTRUE���Ԃ�
 */
BOOL MpIsSendDataEnd(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();
	  if (td->state == MP_TRANS_STATUS_SUCCESS) return TRUE;
	}
	break;
      }
      
    }
    break;
  }
    
  return FALSE;
}


/**
 * �f�[�^��M���I�����������ׂ�
 *
 * @return �I�����Ă���ꍇTRUE���Ԃ�
 */
BOOL MpIsRecvDataEnd(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();

	  MpPrintf("MpIsRecvDataEnd() trans_state %d \n", td->state);

	  if (td->state == MP_TRANS_STATUS_SUCCESS) return TRUE;
	}
	break;
      }
      
    }
    break;
  }
    
  return FALSE;
}


BOOL MpIsRecvDataAcknowledge(void)
{
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();

	  if (td->state == MP_TRANS_STATUS_ENABLE) {
	    MpSendHeader *header = (MpSendHeader *)td->recv_buff;
	    if ((header->data2.control_code == MP_CONTROL_CODE_ACKNOWLEDGE) &&
		(td->resend_count < MP_RECV_ACKNOWLEDGE_SEND_NUM))
	      return TRUE;
	  }
	}
	break;
      }
    }
    break;
  }
  return FALSE;
}
	      

/**
 * �ڑ�����Ă����Ԃ����ׂ�
 *
 * @return �ڑ��������TRUE��Ԃ�
 */
BOOL MpIsConnect(void)
{
  switch (MpGetMode()) {
  case MP_MODE_PARENT_MP :
    {
      MpDataParentMP *parent_data = MpGetDataParentMP();
      int i;
      
      for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	if (parent_data->user_list[i].mac_addr.u.data32) { 
	  if (parent_data->user_list[i].connect_flag) return TRUE;
	}
      }
      return FALSE;
    }
    break;
  default :
    return MpIsConnectFlag();
    break;
  }
}


/**
 * �f�[�^�]���\�ȏ�Ԃ����ׂ�
 *
 * @return �ڑ��������TRUE��Ԃ�
 */
BOOL MpIsDataTrans(void)
{
  if (MpGetDataTransListNum()) return TRUE;
  else return FALSE;
}


/**
 * �������C�u������~�v��
 */
void MpRequestClose(void)
{
  MpPrintf("MpRequestClose state %d\n", MpGetStatus());

  //MpSetEndRequest(TRUE);  
  MpSetRequestStatus(MP_STATUS_END);
  
  switch (MpGetStatus()) {
  case MP_STATUS_INIT :
  case MP_STATUS_READY :
    WM_Finish();
    MpSetIsEnd(TRUE);
    break;
  case MP_STATUS_CHILD :
    if (!MpIsConnectFlag()) {
      MpInternalData *id = MpGetInternalData();
      MpRequestReset();
      id->request_end_flag = TRUE;
    }
    break;
  }
}


/**
 * �������C�u��������~���������ׂ�
 *
 * @return ��~��ԂɂȂ����ꍇTRUE���Ԃ�
 */
BOOL MpIsEnd(void)
{
  MpInternalData *id = MpGetInternalData();
  return id->is_end_flag;
}


//


