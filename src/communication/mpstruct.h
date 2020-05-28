#ifndef ___MPSTRUCT_H___
#define ___MPSTRUCT_H___
/**
 * @version "$Id: mpstruct.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpstruct.h
 * @brief MP�����ʐM���C�u���� �f�[�^��`
 * 
 */
#include "mpconfig.h"
 

#ifdef __cplusplus
extern "C" {
#endif

/* �v���g�R��ID */
#define		MP_PROTOCOL_ID			(0x0F)

/* �v���g�R���o�[�W���� */  
#define		MP_PROTOCOL_VERSION		(0x01)
  

#define		MP_RECV_READY_SEND_NUM		(3)
#define		MP_RECV_ACKNOWLEDGE_SEND_NUM	(4)

  
/* ���������� */  
typedef enum {
  MP_ENCODE_TYPE_NONE = 0,
  MP_ENCODE_TYPE_TYCHO,  
  MP_ENCODE_TYPE_NINTENDO_CRYPT,  
  MP_ENCODE_TYPE_END  
} MP_ENCODE_TYPE;

/* �ʐM����R�[�h */ 
typedef enum {
  MP_CONTROL_CODE_ACKNOWLEDGE,		/* ��M���� */
  MP_CONTROL_CODE_RETRY,		/* �đ��v�� */
  MP_CONTROL_CODE_DATA_CONTINUALLY,	/* �f�[�^�p�� */
  MP_CONTROL_CODE_DATA_END,		/* �f�[�^�I�� */
  MP_CONTROL_CODE_END
} MP_CONTROL_CODE;  

/* �]���f�[�^�w�b�_0 ����������Ȃ� */  
typedef struct {
  u32 protocol_id	: 8;	/* �v���g�R���ԍ� */
  u32 protocol_version	: 4;	/* �v���g�R���o�[�W���� */
  u32 encode_type	: 4;	/* ���������� MP_ENCODE_TYPE */
  u32 encode_data	: 16;	/* �����p�f�[�^ */    
} MpSendHeader0;		/* 4byte */

/* �]���f�[�^�w�b�_1 ����������� */    
typedef struct {
  u32 game_id		: 8;	/* �Q�[���^�C�g��ID */
  u32 game_version	: 4;	/* �Q�[���o�[�W���� */
  u32 language		: 4;	/* OS_LANGUAGE */
  u32 game_etc		: 16;	/* �Q�[���⑫��� */
} MpSendHeader1;		/* 4byte */
  
/* �]���f�[�^�w�b�_2 ����������� */    
typedef struct {
  u32 sequence_num	: 8;	/* �ʐM�V�[�P���X�ԍ� */
  u32 control_code	: 8;	/* �ʐM����R�[�h MP_CONTROL_CODE  */
  u32 crc		: 16;	/* �f�[�^CRC */
} MpSendHeader2;		/* 4byte */  

/* �]���f�[�^�w�b�_3 ����������� */    
typedef struct {
  u32 header_size	: 8;	/* �w�b�_�[�T�C�Y */
  u32 data_size		: 24;	/* �f�[�^�T�C�Y */
} MpSendHeader3;		/* 4byte */

/* �]���f�[�^�w�b�_4 �g���p�i���g�p�j*/    
typedef struct {
  u32 extend;
} MpSendHeader4;		/* 4byte */

/* �]���f�[�^�w�b�_ */  
typedef struct {
  MpSendHeader0 data0;
  MpSendHeader1 data1;
  MpSendHeader2 data2;
  MpSendHeader3 data3;
} MpSendHeader;			/* 16byte */

/* �r�[�R���f�[�^�w�b�_0 ����������Ȃ� */  
typedef struct {
  u32 protocol_id	: 8;	/* �v���g�R���ԍ� */
  u32 protocol_version	: 4;	/* �v���g�R���o�[�W���� */
  u32 encode_type	: 4;	/* ���������� MP_ENCODE_TYPE */
  u32 encode_data	: 16;	/* �����p�f�[�^ */    
} MpBeaconHeader0;		/* 4byte */
  
/* �r�[�R���f�[�^�w�b�_1 ����������Ȃ� */  
typedef struct {
  u32 game_id		: 8;	/* �Q�[���^�C�g��ID */
  u32 game_version	: 4;	/* �Q�[���o�[�W���� */
  u32 language		: 4;	/* OS_LANGUAGE */
  u32 connect_id	: 16;	/* �ڑ�ID */
} MpBeaconHeader1;		/* 4byte */

/* �r�[�R���f�[�^�w�b�_ */  
typedef struct {
  MpBeaconHeader0 data0;
  MpBeaconHeader1 data1;
} MpBeaconHeader;  
  

/* SSID�f�[�^�w�b�_0 ����������Ȃ� */  
typedef struct {
  u32 protocol_id	: 8;	/* �v���g�R���ԍ� */
  u32 protocol_version	: 4;	/* �v���g�R���o�[�W���� */
  u32 encode_type	: 4;	/* ���������� MP_ENCODE_TYPE */
  u32 encode_data	: 16;	/* �����p�f�[�^ */    
} MpSsidHeader0;		/* 4byte */
  
/* SSID�f�[�^�w�b�_1 ����������Ȃ� */  
typedef struct {
  u32 game_id		: 8;	/* �Q�[���^�C�g��ID */
  u32 game_version	: 4;	/* �Q�[���o�[�W���� */
  u32 language		: 4;	/* OS_LANGUAGE */
  u32 connect_id	: 16;	/* �ڑ�ID */
} MpSsidHeader1;		/* 4byte */

/* SSID�f�[�^�w�b�_ */  
typedef struct {
  MpSsidHeader0 data0;
  MpSsidHeader1 data1;
} MpSsidHeader;			/* 8byte */

  
/* SSID�f�[�^ */   
typedef struct {
  MpSsidHeader header;
  u8 dummy[24-8];
} MpSsidData;			/* 24byte */
  

/* ���[�U�[���i�[�p�o�b�t�@ */  
#define MP_USERGAMEINFO_NAME_LENGTH	(12)
typedef struct {
  u16 data[MP_USERGAMEINFO_NAME_LENGTH];
} MpUserName;			/* 24byte */

/* WMbssDesc�Ɋ܂܂��ڑ��f�[�^ */  
typedef struct {
  MpUserName name;		/* �����W���[�^�g���[�i�� */
  MpUserName user_id;		/* �����W���[�ԍ��^�g���[�i�ԍ� */
} MpUserGameInfoData;		/* 48byte */

/* WMbssDesc�f�[�^ */  
typedef struct {
  MpBeaconHeader	header;
  MpUserGameInfoData	data;
} MpUserGameInfo;  
  

#define	MP_SIZE_MAC_DATA	(4)	/* ���ʗpMAC�A�h���X�T�C�Y */
typedef struct {
  union {
    u8 data[MP_SIZE_MAC_DATA];
    u32 data32;
  } u;
} MpMACAddData;

#define	MP_SIZE_MAC_VENDOR_DATA	(2)	/* MAC�A�h���X�x���_ID�T�C�Y */
typedef struct {
  union {
    u8 data[MP_SIZE_MAC_VENDOR_DATA];
    u16 data16;
  } u;
} MpMACVendorData;

  
typedef enum {
  MP_TRANS_MODE_NONE,
  MP_TRANS_MODE_SEND,
  MP_TRANS_MODE_RECV,
  MP_TRANS_MODE_END
} MP_TRANS_MODE;

/* �f�[�^�]���X�e�[�^�X */
typedef enum {
  MP_TRANS_STATUS_ENABLE,	/*  */
  MP_TRANS_STATUS_WAIT,
  MP_TRANS_STATUS_SUCCESS,
  MP_TRANS_STATUS_READY,
  MP_TRANS_STATUS_END
} MP_TRANS_STATUS;
typedef struct {
  void *org_data;
  void *data;
  void *send_buff;
  void *recv_buff;
  u32 org_size;
  u32 size;
  vu8 mode;
  vu8 state;
  u8 time_out;
  u8 resend_count;
  u8 seq_num;
} MpTransData;

/* �q�@�X�e�[�^�X��` */  
typedef enum {
  MP_CHILD_MP_STATUS_READY = 0,
  MP_CHILD_MP_STATUS_SCAN_1,		/* �ŏ��ɐe�@�T�����邽�߂̃X�e�[�g */
  MP_CHILD_MP_STATUS_SCAN_2,		/* �I�������e�@�Ɛڑ����邽�߂̃X�e�[�g */
  MP_CHILD_MP_STATUS_MAX
} MP_CHILD_MP_STATUS;
  
/* �q�@���ێ�����e�@��� */ 
typedef struct {
  MpMACAddData	mac_addr;		/* 4byte */
  MpUserName	name;			/* 24byte */
  MpUserName	user_id;		/* 24byte */
  MpMACVendorData mac_vendor;		/* 2byte */
  u8		link_level;		/* 1byte */
  u8		data_trans_ready;	/* 1byte */
} MpDataConnectionUser;			/* 56byte */
  
/* MP�ʐM�i�q�@�j�p�f�[�^��` */  
typedef struct {
  MpDataConnectionUser user_list[MP_SIZE_RECEIVE_MP_PARENT_LIST]; /* 56*8byte */
  u16		time_count; 
  u8		scan_retry_count;
  u8		select : 4;	/* �C�ӂɑI�������e�@�ԍ� �iMP_CHILD_MP_STATUS_SCAN_2�ł̃X�L�����Ώہj */
  u8		status : 4;
} MpDataChildMP;		/* 452byte */

/* �e�@�X�e�[�^�X��` */  
typedef enum {
  MP_PARENT_MP_STATUS_READY = 0,
  MP_PARENT_MP_STATUS_SEARCH_CHANNEL,	/* �ʐM�Ɏg�p����`�����l���ݒ�X�e�[�g */  
  MP_PARENT_MP_STATUS_WAIT_CONNECT,	/* �ڑ����Ă���q�@�҂��X�e�[�g */
  MP_PARENT_MP_STATUS_MAX
} MP_PARENT_MP_STATUS;

  
/* �e�@���ێ�����q�@��� */ 
typedef struct {
  MpMACAddData	mac_addr;		/* 4byte */
  MpMACVendorData mac_vendor;		/* 2byte */
  u16		aid;			/* 2byte */
  u8		data_trans_ready;	/* 1byte */
  u8		data_trans_count;	/* 1byte */
  u8		connect_flag;		/* 1byte */
  u8		dummy;			/* 1byte */
} MpDataParentConnectionUser;		/* 12byte */
  
/* MP�ʐM�i�e�@�j�p�f�[�^��` */  
typedef struct {
  MpDataParentConnectionUser user_list[MP_SIZE_RECEIVE_MP_CHILD_LIST]; /* 8*12byte */
  u8 status;
  u8 busy_ratio;
  u16 channel_bitmap;
  u8 channel;
  u8 dummy[3];
} MpDataParentMP;		/* 104byte */

typedef union {
  MpDataParentMP	parent_mp;
  MpDataChildMP		child_mp;
} MpModeData;

/* �d�g�g�p���̍ő�i�����j�l */  
#define MP_MEASURE_BUSYRATIO_MAX	(102)
  

/**
 * �����X�e�[�^�X��`
 */  
typedef enum {
  MP_STATUS_INIT = 0,	/* ��������� */
  MP_STATUS_READY,	/* �ҋ@��� */
  MP_STATUS_STOP,	/* �d����������� */  
  MP_STATUS_IDLE,	/* �A�C�h����� */  
  MP_STATUS_ERROR,	/* �ǂ��ɂ��Ȃ�Ȃ��G���[��� */
  MP_STATUS_BUSY,	/* ��ԑJ�ڒ��ɂ��r�W�[��� */
  MP_STATUS_SCAN,	/* �e�@�̃X�L��������� �i�q�@��p�X�e�[�^�X�j*/
  MP_STATUS_ENDSCAN,	/* �X�L�����I����� �i�q�@��p�X�e�[�^�X�j*/
  MP_STATUS_PARENT,	/* �e�@�Ƃ��Đڑ��ςݏ�� */
  MP_STATUS_CHILD,	/* �q�@�Ƃ��Đڑ��ςݏ�� */
  MP_STATUS_PARENT_MP,	/* �e�@�Ƃ���MP�ʐM��� */
  MP_STATUS_CHILD_MP,	/* �q�@�Ƃ���MP�ʐM��� */
  MP_STATUS_END,	/* ���C�u�����I����� */
  MP_STATUS_MAX
} MP_STATUS;
  

/**
 * �ʐM�V�[�P���X�ԍ���`
 */  
typedef enum {
  MP_SEQUENCE_APP = 0,		/* �A�v���P�[�V���������R�Ɏg�p�ł���l */
  MP_SEQUENCE_APP_END	= 0xF0,	/* �A�v���P�[�V���������R�Ɏg�p�ł���l�̍Ō� */  
  MP_SEQUENCE_READY	= 0xFD,	/* �f�[�^���M�����V�[�P���X */
  MP_SEQUENCE_USER_DATA	= 0xFE,	/* ���[�U�|�f�[�^���M�V�[�P���X */
  MP_SEQUENCE_END
} MP_SEQUENCE;

  
typedef struct {

  /* ���݂̃X�e�[�^�X */
  u8 status;

  /* �ύX�v���X�e�[�^�X */
  u8 request_status;
  
  /* �ʐM���[�h */
  u8 mode;

  /* �ʐM�|�[�g */
  u8 port;
  
  /* GameID */
  u32 ggid;
  
  /* �ڕW�X�e�[�^�X */
  MP_STATUS target;

  /* AID */
  u16 aid;
  
  /* �Q�[���t���[���Ԋu */
  u16 frame_period;

  /* Indication�ʒm�p�R�[���o�b�N�ݒ�ς݃t���O */
  BOOL indication_callback_flag;     

  BOOL connect_flag;
  BOOL disconnect_trigger;
  
  BOOL request_end_flag;
  BOOL is_end_flag;
    
  
  WMScanParam* scan_parameter;
  WMBssDesc* bss_desc;
  
  u32 send_buff_size;
  u32 recv_buff_size;

  void *lib_buff;
  void *send_buff;
  void *recv_buff;

  MpUserGameInfo user_game_info;
  MpSsidData ssid_data;
  
  MpModeData mode_data;
  MpTransData trans_data;
  
} MpInternalData; 
  

  
  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPSTRUCT_H___
