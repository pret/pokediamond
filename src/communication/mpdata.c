/**
 * @version "$Id: mpdata.c,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file twl_data.c
 * @brief �����ʐM���C�u���� �����f�[�^�Q�Ɗ֐�
 * 
 */
#include "mpconfig.h"
#include "mpdata.h"
#include "mpdebug.h"

#if 0
#include "../data/message/message_def.h"
#include "../data/message/wordtbl_def.h"
#endif

static MpInternalData MpData;

#define     DEFAULT_CHAN            1


__attribute__ ((aligned (32))) static WMParentParam MpDefaultParameter = {
  NULL, 0, 0,
  MP_GGID,			/* �Q�[���O���[�vID */
  0x0000,                       /* temporary ID */
  1,				/* �G���g���[���t���O */
  MP_CONNECT_CHILD_MAX,		/* �ő�ڑ��q�@�� */
  0,                            /* �}���`�u�[�g�t���O */
  0,                            /* �L�[�V�F�A�����O */
  0,                            /* �A�����M�t���O */
  MP_DEFAULT_BEACON_PERIOD,	/* beacon �Ԋu */
  {0, 0, 0, 0},			/* rdv1 */
  {0, 0, 0, 0, 0, 0, 0, 0},	/* rsv2 */
  0,				/* �ڑ��`�����l�� */
  MP_PARENT_DATA_SIZE,		/* �e�@���M�f�[�^�T�C�Y */
  MP_CHILD_DATA_SIZE		/* �q�@���M�f�[�^�T�C�Y */
};


/**
 * ���C�u�������ŕێ������WMParentParam��Ԃ�
 *
 * @return WMParentParam
 */
WMParentParam *MpGetParentParameter(void) { return &MpDefaultParameter; }


u32 MpGetConnectChildMax(void) { return (u32)MpDefaultParameter.maxEntry; }
void MpSetConnectChildMax(u32 num) { MpDefaultParameter.maxEntry = (u16)num; }



/**
 * �����Ŏg�p����f�[�^��Ԃ�
 *
 * @return TWL_InternalData
 */
MpInternalData *MpGetInternalData(void)
{
  return &MpData;
}


/**
 * �����X�e�[�^�X��Ԃ�
 *
 * @return MP_STATUS
 */
MP_STATUS MpGetStatus(void) { return (MP_STATUS)MpGetInternalData()->status; }


/**
 * �����X�e�[�^�X��ݒ肷��
 *
 * @param status TWL_STATUS 
 */
void MpSetStatus(MP_STATUS status) { MpGetInternalData()->status = (u8)status; }


/**
 * �v���X�e�[�^�X��Ԃ�
 *
 * @return MP_STATUS
 */
MP_STATUS MpGetRequestStatus(void) { return (MP_STATUS)MpGetInternalData()->request_status; }


/**
 * �v���X�e�[�^�X��ݒ肷��
 *
 * @param status TWL_STATUS 
 */
void MpSetRequestStatus(MP_STATUS status) { MpGetInternalData()->request_status = (u8)status; }


/**
 * �ʐM���[�h��Ԃ�
 *
 * @return MP_MODE
 */
MP_MODE MpGetMode(void) { return (MP_MODE)MpGetInternalData()->mode; }


/**
 * �ʐM���[�h��ݒ肷��
 *
 * @param mode MP_MODE
 */
void MpSetMode(MP_MODE mode) { MpGetInternalData()->mode = (u8)mode; }


/**
 * �ʐM�|�[�g��Ԃ�
 *
 * @return port 
 */
u32 MpGetPort(void) { return (u32)MpGetInternalData()->port; }


/**
 * �ʐM�|�[�g��ݒ肷��
 *
 * @param port 
 */
void MpSetPort(u32 port) { MpGetInternalData()->port = (u8)port; }


/**
 * �ʐM�`�����l����Ԃ�
 *
 * @return channel 
 */
u32 MpGetChannel(void) { return (u32)MpGetParentParameter()->channel; }


/**
 * �ʐM�`�����l����ݒ肷��
 *
 * @param channel 
 */
void MpSetChannel(u32 channel) { MpGetParentParameter()->channel= (u16)channel; }


/**
 * WMScanParam���擾����
 *
 * @return WMScanParam
 */
WMScanParam *MpGetScanParameter(void)
{
  return MpGetInternalData()->scan_parameter;
}


/**
 * ���M�o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�b�t�@�T�C�Y
 */
u32 MpGetSendBuffSize(void) { return MpGetInternalData()->send_buff_size; }


/**
 * ��M�o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�b�t�@�T�C�Y
 */
u32 MpGetRecvBuffSize(void) { return MpGetInternalData()->recv_buff_size; }


/**
 * ���M�o�b�t�@�̃A�h���X��Ԃ�
 *
 * @return �o�b�t�@�̃A�h���X
 */
void *MpGetSendBuff(void) { return MpGetInternalData()->send_buff; }


/**
 * ��M�o�b�t�@�̃A�h���X��Ԃ�
 *
 * @return �o�b�t�@�̃A�h���X
 */
void *MpGetRecvBuff(void) {  return MpGetInternalData()->recv_buff; }


/**
 * WMBssDesc�̃A�h���X��Ԃ�
 *
 * @return �A�h���X
 */
WMBssDesc *MpGetBssDesc(void) { return MpGetInternalData()->bss_desc; }


/**
 * AID���L�^
 *
 * @param aid AID
 */
void MpSetAid(u16 aid) { MpGetInternalData()->aid = aid; }


/**
 * AID��Ԃ�
 *
 * @return AID
 */
u16 MpGetAid(void) { return MpGetInternalData()->aid; }



BOOL MpIsConnectFlag(void) { return MpGetInternalData()->connect_flag; }
void MpSetIsConnectFlag(BOOL flag) { MpGetInternalData()->connect_flag = flag; }
void MpSetDisconnectTrigger(BOOL flag) { MpGetInternalData()->disconnect_trigger = flag; }
BOOL MpGetDisconnectTrigger(void) { return MpGetInternalData()->disconnect_trigger; }


void MpSetIsEnd(BOOL flag) { MpGetInternalData()->is_end_flag = flag; }


/**
 * ���[�h�ʃf�[�^�̃A�h���X��Ԃ�
 */
MpModeData *MpGetModeData(void) { return &MpGetInternalData()->mode_data; }


/**
 * �q�@��ԗp�f�[�^�̃A�h���X��Ԃ�
 */
MpDataChildMP *MpGetDataChildMP(void) { return &MpGetModeData()->child_mp; }


/**
 * �e�@��ԗp�f�[�^�̃A�h���X��Ԃ�
 */
MpDataParentMP *MpGetDataParentMP(void) { return &MpGetModeData()->parent_mp; }


/**
 * MpDataChildMP��������
 */
void MpInitDataChildMP(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  /* �S��0�N���A */
  MI_CpuClear8(dcmp, sizeof(MpDataChildMP));

  dcmp->time_count = 280;
}


/**
 * MpDataParentMP��������
 */
void MpInitDataParentMP(void)
{
  MpDataParentMP *dpmp = MpGetDataParentMP();

  /* �S��0�N���A */
  MI_CpuClear8(dpmp, sizeof(MpDataParentMP));
}


/**
 * MpTransData��Ԃ�
 */
MpTransData *MpGetTransData(void) { return &MpGetInternalData()->trans_data; }


/**
 * MpTransData��������
 */
void MpInitTransData(void)
{
  MpTransData *trans_data = MpGetTransData();
  trans_data->mode = MP_TRANS_MODE_NONE;
}


/**
 * GGID��Ԃ�
 */
u32 MpGetGameID(void) { return MpGetInternalData()->ggid; }


/**
 *
 */
u16 MpGetFramePeriod(void) { return MpGetInternalData()->frame_period; }


/**
 * �v���g�R��ID��Ԃ�
 */
u32 MpGetProtocolID(void)
{
  return (u32)MpGetInternalData()->user_game_info.header.data0.protocol_id;
}

/**
 * �v���g�R���o�[�W������Ԃ�
 */
u32 MpGetProtocolVersion(void)
{
  return (u32)MpGetInternalData()->user_game_info.header.data0.protocol_version;
}


/**
 * �ڑ�ID��Ԃ�
 */
u32 MpGetConnectID(void)
{
  return (u32)MpGetInternalData()->user_game_info.header.data1.connect_id;
}


/**
 * UserGameInfo�̃T�C�Y��Ԃ�
 *
 * @return UserGameInfo�̃T�C�Y
 */
u32 MpGetUserGameInfoSize(void)
{
  return sizeof(MpUserGameInfo);
}


/**
 * MpUserGameInfo��Ԃ�
 *
 * @return MpUserGameInfo�̃A�h���X
 */
MpUserGameInfo *MpGetUserGameInfo(void)
{
  return &MpGetInternalData()->user_game_info;
}


/**
 * MpSsidData��Ԃ�
 *
 * @return MpSsidData�̃A�h���X
 */
MpSsidData *MpGetSsidData(void)
{
  return &MpGetInternalData()->ssid_data;
}


/**
 * MAC�A�h���X���i�[�����z�񂩂�MpMACAddData�𐶐�
 *
 * @param mac_arry MAC�A�h���X�z��
 * @return�@MpMACAddData
 */
MpMACAddData MpMACAddArrayToMACAddData(u8 *mac_arry)
{
  u32 i;
  MpMACAddData mac_bss;
  
  mac_bss.u.data32 = 0;
  for (i=0; i<MP_SIZE_MAC_DATA; i++) mac_bss.u.data[i] = mac_arry[i + 2];    

  return mac_bss;
}


/**
 * MAC�A�h���X���i�[�����z�񂩂�MpMACVendorData�𐶐�
 *
 * @param mac_arry MAC�A�h���X�z��
 * @return�@MpMACVendorData
 */
MpMACVendorData MpMACAddArrayToMACVendorData(u8 *mac_arry)
{
  u32 i;
  MpMACVendorData mac_bss;
  
  mac_bss.u.data16 = 0;
  for (i=0; i<MP_SIZE_MAC_VENDOR_DATA; i++) mac_bss.u.data[i] = mac_arry[i];    

  return mac_bss;
}


/**
 * u32��MAC�A�h���X����ڑ�ID�𐶐�
 *
 * @param mac_addr MAC�A�h���X
 * @param high_code ���[�U�[�R�[�h��ʂ��i�[�����
 * @param low_code ���[�U�[�R�[�h���ʂ��i�[�����
 */
void MpMACAddressToConnectCode(u32 mac_addr, u32 *high_code, u32* low_code)
{
  *high_code = mac_addr % 10000;
  *low_code = (mac_addr / 10000) % 10000;
}


/**
 * u32��MAC�A�h���X����ڑ�ID�𕶎���Ƃ��Đ���
 *
 * @param mac_addr MAC�A�h���X
 * @return ������o�b�t�@�̃|�C���^
 */
const u16* MpConnectCodeToString(u32 mac_addr)
{
#if 0
  static u16 string_buff[4+4+2];
  const int num0 = n0_;
  const int hyphen = bou_;
  const int endcode = EOM_;
  int code_count = 0;
  u32 hc,lc;

  MpMACAddressToConnectCode(mac_addr, &hc, &lc);

  //OS_Printf("HightCode %d LowCode %d\n", hc, lc);
  
  string_buff[code_count++] = (u16)((hc / 1000) + num0);
  hc %= 1000;
  string_buff[code_count++] = (u16)((hc / 100) + num0);
  hc %= 100;
  string_buff[code_count++] = (u16)((hc / 10) + num0);
  hc %= 10;
  string_buff[code_count++] = (u16)(hc + num0);

  string_buff[code_count++] = (u16)hyphen;

  string_buff[code_count++] = (u16)((lc / 1000) + num0);
  lc %= 1000;
  string_buff[code_count++] = (u16)((lc / 100) + num0);
  lc %= 100;
  string_buff[code_count++] = (u16)((lc / 10) + num0);
  lc %= 10;
  string_buff[code_count++] = (u16)(lc + num0);

  string_buff[code_count] = (u16)endcode;
  
  return string_buff;
#else
  return (u16 *)NULL;
#endif
}


#if 0
/**
 * ��ʉ��ʂ��ꂼ��̃��[�U�[�R�[�h����u32��MAC�A�h���X�𐶐�
 *
 * @param high_code ���[�U�[�R�[�h���
 * @param low_code ���[�U�[�R�[�h����
 * @return MAC�A�h���X
 */
u32 MpUserCodeToMACAddress(u32 high_code, u32 low_code)
{
  return high_code + low_code * 10000;
}
#endif

/**
 * ���M�f�[�^�̃w�b�_�T�C�Y���擾 �i���݌Œ�j
 *
 * @return �o�C�g��
 */
u32 MpGetSendHeaderSize(void)
{
  return sizeof(MpSendHeader);
}


/**
 * �������p����seed�l���擾����
 *
 * @return seed�l
 */
static u32 MpGetSeed()
{
  return  ((u32)(OS_GetTick() + GX_GetVCount()) & 0xFFFFFFFE) + 1;
}


/**
 * �����^���������s��
 *
 * @param seed �V�[�h
 * @param size �R�[�h������̈�̃T�C�Y
 * @param data �R�[�h������̈�̃A�h���X
 */
static u32 MpEncodeData(u32 seed, u32 size, void* data)
{
  u32 i;
  u32 *target = (u32*)data;
  MATHRandContext16 cont;
  
  MATH_InitRand16(&cont, seed);
  
  for (i=0; i<size/sizeof(u32); i++) {
    (*target) ^= ((MATH_Rand16(&cont, 0) << 16) | MATH_Rand16(&cont, 0));
    target++;
  }

  return cont.x;
}


/**
 * ���M�p�f�[�^�𐶐�����
 *
 * @param buff �f�[�^�𐶐�����A�h���X
 * @param data ���M�p�f�[�^
 * @param data_size ���M�p�f�[�^�̃T�C�Y
 * @param control_code �ʐM����R�[�h
 */
void MpSetupSendData(void *buff, void *data, u32 data_size, MP_CONTROL_CODE control_code, u32 seq_num)
{
  MpSendHeader *header = (MpSendHeader *)buff;
  MpUserGameInfo *info = MpGetUserGameInfo();

  header->data0.protocol_id      = info->header.data0.protocol_id;
  header->data0.protocol_version = info->header.data0.protocol_version;
  header->data0.encode_type      = info->header.data0.encode_type;
  header->data0.encode_data      = (u16)MpGetSeed();

  header->data1.game_id          = info->header.data1.game_id;
  header->data1.game_version     = info->header.data1.game_version;
  header->data1.language         = info->header.data1.language;
  header->data1.game_etc         = 0;

  header->data2.sequence_num     = (u8)seq_num;
  header->data2.control_code     = control_code;
  header->data2.crc              = SVC_GetCRC16(0, data, data_size);

  header->data3.header_size      = (u8)MpGetSendHeaderSize();
  header->data3.data_size        = data_size;

  if (data_size)
    MI_CpuCopy8(data, ((u8*)buff) + header->data3.header_size, data_size);

  MpPrintSendHeader(header);	
  
  if ((MP_ENCODE_TYPE)info->header.data0.encode_type == MP_ENCODE_TYPE_TYCHO)
    MpEncodeData(header->data0.encode_data,
		 data_size + header->data3.header_size - sizeof(MpSendHeader0),
		 &header->data1);
  
}


/**
 * ��M�����f�[�^�𕜍�����
 *
 * @param buff ��M�����f�[�^
 */
void MpDecodeRecvData(void *buff)
{
  MpSendHeader *header = (MpSendHeader *)buff;
  MpUserGameInfo *info = MpGetUserGameInfo();

  if ((MP_ENCODE_TYPE)header->data0.encode_type == MP_ENCODE_TYPE_TYCHO) {
    u32 seed;

    MpPrintf("MpDecodeRecvData() buff %x  encode seed %d\n", buff, header->data0.encode_data);
    
    /* �w�b�_�^�f�[�^�T�C�Y���擾���邽�߂�MpSendHeader1����MpSendHeader3�܂ł𕜍����� */
    seed = MpEncodeData(header->data0.encode_data,
			sizeof(MpSendHeader1) + sizeof(MpSendHeader2) + sizeof(MpSendHeader3),
			&header->data1);

    MpPrintf("\t header size %d  data size %d\n", header->data3.header_size, header->data3.data_size);

    /* �c��̃f�[�^�𕜍� */
    MpEncodeData(seed,
		 header->data3.header_size + header->data3.data_size - sizeof(MpSendHeader),
		 (void*)((u32)buff + sizeof(MpSendHeader)));
    
  }
}


/**
 * ��M�����f�[�^��CRC���`�F�b�N����
 *
 * @return buff ��M�����f�[�^
 */
BOOL MpCheckRecvData(void *buff)
{
  MpSendHeader *header = (MpSendHeader *)buff;

  u16 crc_val = SVC_GetCRC16(0, ((u8*)buff) + header->data3.header_size, header->data3.data_size);

  if (header->data2.crc == crc_val) return TRUE;
  else return FALSE;
    
}



//
