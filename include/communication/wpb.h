/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library - include
  File:     wpb.h

  2005 Ambrella
 *---------------------------------------------------------------------------*/

#ifndef WPB_H_
#define WPB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include <nitro/types.h>
#include <nitro/math.h>
#include <nitro/wm.h>

/*---------------------------------------------------------------------------*
    �\���̒�`
 *---------------------------------------------------------------------------*/

typedef enum WCStatus {
	WC_STATUS_READY = 0,               // ���������
	WC_STATUS_ERROR,                   // �ǂ��ɂ��Ȃ�Ȃ��G���[���
	WC_STATUS_BUSY,                    // ��ԑJ�ڒ��ɂ��r�W�[���
	WC_STATUS_PARENT,                  // �e�@�Ƃ��Đڑ��ςݏ��
	WC_STATUS_CHILD,                   // �q�@�Ƃ��Đڑ��ςݏ��
	WC_STATUS_END,                     // �I����� (Target�̂�)
	WC_STATUS_MAX
} WCStatus;

// API�̃R�[���o�b�N�ŕԂ��X�e�[�g�R�[�h
typedef enum WPBStateCode {
	WPB_STATECODE_START,        /* ����Ⴂ�ҋ@�J�n */
	WPB_STATECODE_PARENT_FOUND, /* �e�@�𔭌����� */
	WPB_STATECODE_CONNECTED,    /* �ڑ����� */
	WPB_STATECODE_EXCHANGED,    /* �f�[�^�������� */
	WPB_STATECODE_DISCONNECTED, /* �ؒf�ʒm */
	WPB_STATECODE_END,          /* ����Ⴂ�ҋ@�I�� */
	WPB_STATECODE_MAX
} WPBStateCode;

// �R�[���o�b�N�̈���
typedef struct WPBCallback {
	u16             state;               // �R�[���o�b�N�̔��������v�����
	u16             errcode;             // �񓯊������̌���
	u16             wlCmdID;             // �G���[�ƂȂ����R�}���h��ID
	u16             wlResult;            // �G���[�ƂȂ����v���R�[�h
	const WMBssDesc *bssDesc;            // ���������e�@���
	u16             bssDescCount;        // ���������e�@��
	u8              macAddress[WM_SIZE_BSSID]; // ����Ⴂ�����MAC�A�h���X
	const void      *extinfo;
	const void      *send_ptr;
	int             send_size;
	void            *recv_ptr;
	int             recv_size;
} WPBCallback;

// WPB API�̃R�[���o�b�N�̌^
typedef void (*WPBCallbackFunc)(WPBCallback *arg);

// ���[�N�G���A
#define PASS_PACKET_SIZE                 512
#define PASS_BUFFER_SIZE                 (PASS_PACKET_SIZE - 4)
#define WPBC_PARENT_DATA_SIZE_MAX        PASS_PACKET_SIZE
#define WPBC_CHILD_DATA_SIZE_MAX         PASS_PACKET_SIZE

#define WPB_RECEIVE_BUFFER \
	(MATH_MAX(WM_SIZE_MP_PARENT_RECEIVE_BUFFER(WPBC_PARENT_DATA_SIZE_MAX, \
											   1, FALSE), \
			  WM_SIZE_MP_CHILD_RECEIVE_BUFFER(WPBC_CHILD_DATA_SIZE_MAX, \
											  FALSE)))
#define WPB_SEND_BUFFER \
	(MATH_MAX(WM_SIZE_MP_PARENT_SEND_BUFFER(WPBC_PARENT_DATA_SIZE_MAX, \
											FALSE), \
			  WM_SIZE_MP_CHILD_SEND_BUFFER(WPBC_CHILD_DATA_SIZE_MAX, FALSE)))

typedef struct WPBBuf {
	WMParentParam pparaBuf;
	union {
		WMScanExParam param;
		u32           dummy[96 / sizeof(u32)]; /* fixme */
	} wmScanExParam;
	/* �X�L�����o�b�t�@ */
	u16           scanBuf[WM_SIZE_SCAN_EX_BUF / sizeof(u16) * 3];
	u16           recvBuf[WPB_RECEIVE_BUFFER / sizeof(u16)];
	u16           sendBuf[WPB_SEND_BUFFER / sizeof(u16)];
	u16           gameInfo[WM_SIZE_USER_GAMEINFO / sizeof(u16)];

	WPBCallbackFunc wpbCallback;
	WCStatus wcStatus;              // ���݂̏�Ԃ��Ǘ�
	WCStatus wcTarget;              // ��ԕύX�̖ڕW���Ǘ�
	BOOL     wcSendFlag;            // ���M�����t���O(�ʏ�MP���[�h��)
	u16      sChannel;
	u16      sChannelBusyRatio;
	BOOL     measure_channel_flag;
	/* �e�@������ */
	u16             child_found_num;
	u16             pad_1; /* padding */
	u16             *current_bssdesc_ptr;
	/* �ڑ����̐e�@BssDesc�|�C���^(�q�@�p�f�[�^) */
	const WMBssDesc *parent_bssdesc_ptr;
} WPBBuf;

/*---------------------------------------------------------------------------*
    �֐���`
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         WPB_SetBuffer

  Description:  ���C�u�����Ŏg�p����o�b�t�@���w�肷��B
                WPB_SetGameInfo�̑O�ɌĂяo���K�v������B

  Arguments:    wpbBuf       - �Ăяo�����ɂ���Ċm�ۂ��ꂽ�o�b�t�@�ւ̃|�C���^���w�肷��B
                               32�o�C�g�A���C������Ă���K�v������B

  Returns:      WMErrCode    -   �������ʂ�Ԃ��B
                WM_ERRCODE_SUCCESS       : ����������Ɋ���
                WM_ERRCODE_INVALID_PARAM : �֐��Ɏw�肵���p�����[�^���s��
 *---------------------------------------------------------------------------*/
WMErrCode WPB_SetBuffer(WPBBuf *wpbBuf);

/*---------------------------------------------------------------------------*
  Name:         WPB_SetCallback

  Description:  �R�[���o�b�N�֐���ݒ肷��B
                WPB_Start�̑O�ɌĂяo���K�v������B
                ���̊֐��̎��s�O�ɁAWPB_SetBuffer���Ăяo���K�v������B

  Arguments:    callback  -   ���[�U�[�ւ̃R�[���o�b�N�֐��i�C�x���g�������ɃR�[���o�b�N�����j

  Returns:      WMErrCode    -   �������ʂ�Ԃ��B
                WM_ERRCODE_SUCCESS       : ����������Ɋ���
                WM_ERRCODE_FAILED : �����Ɏ��s (WPB_SetBuffer���Ăяo����Ă��Ȃ�)
 *---------------------------------------------------------------------------*/
WMErrCode WPB_SetCallback(WPBCallbackFunc callback);

/*---------------------------------------------------------------------------*
  Name:         WPB_SetGameInfo

  Description:  �e�@�Ƃ��ĕK�v�ȃp�����[�^��ݒ肷��B
                WPB_Start���s�O�ɁA�K��1�x�Ăяo���K�v������B
                ����Ⴂ�ҋ@���ɂ��Ăяo����B
                ���̊֐��̎��s�O�ɁAWPB_SetBuffer���Ăяo���K�v������B

  Arguments:    gameInfo       -   ���[�U�[�Q�[�����ւ̃|�C���^���w�肷��B
                gameInfoLength -   ���[�U�[�Q�[�����̃T�C�Y���w�肷��B
                                   �ő�� 112 �o�C�g�܂Ŏw�肷�邱�Ƃ��ł���B
                ggid           -   �Q�[���O���[�vID���w�肷��B

  Returns:      WMErrCode    -   �������ʂ�Ԃ��B
                WM_ERRCODE_SUCCESS       : ����������Ɋ���
                WM_ERRCODE_FAILED : �����Ɏ��s (WPB_SetBuffer���Ăяo����Ă��Ȃ�)
                WM_ERRCODE_ILLEGAL_STATE : ���łɂ���Ⴂ�ڑ����m�����A�ʐM��
                WM_ERRCODE_INVALID_PARAM : �֐��Ɏw�肵���p�����[�^���s��
 *---------------------------------------------------------------------------*/
WMErrCode WPB_SetGameInfo(const u16 *gameInfo,
						  u16       gameInfoLength,
						  u32       ggid);
/*---------------------------------------------------------------------------*
  Name:         WPB_Start

  Description:  ����Ⴂ�ʐM�ҋ@��Ԃɂ���BWM��Ԃ�WM_READY�̂Ƃ��Ɏg�p�\�B
                ���̊֐��̎��s�O�ɁAWPB_SetGameInfo���Ăяo���K�v������B

  Arguments:    None.

  Returns:      WMErrCode    -   �������ʂ�Ԃ��B
                WM_ERRCODE_SUCCESS       : ����������Ɋ���
                WM_ERRCODE_ILLEGAL_STATE : ���łɂ���Ⴂ�ڑ����m�����A�ʐM��
                WM_ERRCODE_INVALID_PARAM : �֐��Ɏw�肵���p�����[�^���s��
 *---------------------------------------------------------------------------*/
WMErrCode WPB_Start();

/*---------------------------------------------------------------------------*
  Name:         WPB_End

  Description:  ����Ⴂ�ʐM�ҋ@��Ԃ��I������B
                �������j�b�g�ւ̓d���������~�߁AWM_READY �X�e�[�g�Ɉڍs����B

  Arguments:    None.

  Returns:      WMErrCode    -   �������ʂ�Ԃ��B
                WM_ERRCODE_SUCCESS       : ����������Ɋ���
                WM_ERRCODE_ILLEGAL_STATE : ����Ⴂ�ʐM�ҋ@���łȂ�
 *---------------------------------------------------------------------------*/
WMErrCode WPB_End(void);

int WPB_Finished(void);
void WPB_ForceFinish(void);


/*---------------------------------------------------------------------------*
  Name:         WPB_CheckParent

  Description:  �e�@���̃��X�g����AGGID ����v������̂�Ԃ��B
                �������݂����ꍇ�́A�����_���ɑI������B

  Arguments:    bssDesc       -  ���������e�@���̏W��
                bssDescCount  -  ���������e�@�̐�
                ggid          -  GGID

  Returns:      const WMBssDesc *  -  GGID ����v�����e�@����Ԃ��B��v������̂��Ȃ��ꍇ�� NULL ��Ԃ��B
 *---------------------------------------------------------------------------*/
const WMBssDesc *WPB_TestParent(const WMBssDesc *bssDesc,
								int bssDescCount, u32 ggid);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* WPB_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
