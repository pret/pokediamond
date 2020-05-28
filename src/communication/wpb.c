#pragma showmessagenumber on
#pragma warning off (10370)
#pragma warning off (10317)

/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library
  File:     wpb.c

  2005 Ambrella
 *---------------------------------------------------------------------------*/
#include    "communication/wpb.h"

// �����define ����ƁA�����G���[�̏ꍇ�ł�Reset���đ��s����
#define FORCE_CONTINUE 1

/*---------------------------------------------------------------------------*
    �萔��`
 *---------------------------------------------------------------------------*/
#define     WC_DEFAULT_PORT             4       // �|�[�g�ԍ�( 4�`7 )
#define     WC_DEFAULT_PORT_PRIO        2       // �|�[�g�̗D��x( 0�`3 )

/*---------------------------------------------------------------------------*
    �\���̒�`
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    �����֐���`
 *---------------------------------------------------------------------------*/
static void WcCreateParentParameter(void);      // �e�@���ҏW
static void WcCreateScanParameter(void);        // �X�L�����ݒ�ҏW
static void WcSetNextScanChannel(void);

static void WcInit(WPBBuf *buf);
static void WcStartParent(void);              // �e�@�Ƃ��Ă̐ڑ��J�n
static void WcStartChild(void);               // �q�@�Ƃ��Ă̐ڑ��J�n
static void WcEnd(void);                      // ��������Ԃւ̈ڍs�J�n
static WCStatus WcGetStatus(void);            // WCStatus�^�̓�����Ԏ擾

// �e�@�Ƃ��Ă̑��M�f�[�^�Z�b�g
static void WcSetParentData(const void *buf, u16 size);
// �q�@�Ƃ��Ă̑��M�f�[�^�Z�b�g
static void WcSetChildData(const void *buf, u16 size);

static const WMBssDesc *WcBssid_GetParentBssdesc(void);

// WM�Ăяo���P�@�\�֐�
static BOOL Wc_Enable(void);
static BOOL Wc_Disable(void);
static BOOL Wc_PowerOn(void);
static BOOL Wc_PowerOff(void);
static BOOL Wc_SetIndCallback(void);
static BOOL Wc_Reset(void);
static BOOL Wc_SetParentParameter(void);
static BOOL Wc_StartParent(void);
static BOOL Wc_StartScan(void);
static BOOL Wc_EndScan(void);
static BOOL Wc_StartConnect(void);
static BOOL Wc_StartMP(void);
static BOOL Wc_SetMPData(const void *buf, u16 size);

static WMBssDesc *WcBssid_GetScanBuffer();
static u16  WcBssid_GetScanBufferSize();
static void WcBssid_AddFoundChild(const WMStartScanExCallback *arg); /* NEW */
static void WcBssid_ResetScanBuffer(); /* NEW */

// �v�����g�o�͗}���_�~�[�֐�
#define WC_DEBUG_PRINT

#ifdef  WC_DEBUG_PRINT
#define     WcDebugPrintf       OS_TPrintf
#else
#define     WcDebugPrintf(...)  ((void) 0)
#endif
//#define DEBUG

/*---------------------------------------------------------------------------*
    �����ϐ���`
 *---------------------------------------------------------------------------*/

static WPBBuf *wpbBuf;
static int finished = 0;
/************ ����Ⴂ�ʐM�֘A ******************/

#define WPBC_SCAN_TIME_MAX               150    // ms
#define WPBC_BEACON_PERIOD               90     // ms

#define WPBC_NUM_OF_CHILD         1

#define MAX_RATIO 100                  // �`�����l���g�p����0�`100�͈̔�

typedef enum {
	WPBC_RETURN_NONE = 0,
	WPBC_RETURN_CONTINUE,
	WPBC_RETURN_DONE,
	WPBC_RETURN_DISCONNECT,
	WPBC_RETURN_MAX
}
WpbcReturnCode;

/*---------------------------------------------------------------------------*
    �֐���`
 *---------------------------------------------------------------------------*/
// wc����Ăяo�����֐�
static void WPBC_MeasureEnd(void);
static void WPBC_BeaconSent(void);
static BOOL WPBC_GetMode(void);

static void WPBC_StartMpParent(void);
static int  WPBC_Connected(u16 aid, const u8 macAddress[], const u8 ssid[]);
static void WPBC_SetMPDataParent(void);
static void WPBC_Disconnect(u16 aid_bitmap);

static void WPBC_StartMpChild(void);
static void WPBC_SetMPDataChild(void);
static BOOL WPBC_IsActiveWPBC(void);
static int  WPBC_ParentReceiveCallback(u16 *data, u16 length);
static int  WPBC_ChildReceiveCallback(u16 *data, u16 length);

// WM����̃R�[���o�b�N�֐�
static void WcCb_Disconnect(void *arg);
static BOOL Wc_Disconnect(u16 aid);

static BOOL Wc_MeasureChannel(u16 channel);
static int NumOfAllowedChannels(void);
static int GetNextAllowedChannel(int current_channel);

/* �q�@�p�����[�^ */
static int child_scan_channel_count = 0;
static int child_scan_channel = 0;


static BOOL pass_active_flag = FALSE;


static WMStatus _wmstatus ATTRIBUTE_ALIGN(32);

static u16
wm_getstatus()
{
	(void)WM_ReadStatus(&_wmstatus);

	switch (_wmstatus.state) {
	case WM_STATE_READY:		OS_TPrintf("current state = WM_STATE_READY\n");		break;
	case WM_STATE_STOP:			OS_TPrintf("current state = WM_STATE_STOP\n");		break;
	case WM_STATE_IDLE:			OS_TPrintf("current state = WM_STATE_IDLE\n");		break;
	case WM_STATE_CLASS1:		OS_TPrintf("current state = WM_STATE_CLASS1\n");	break;
	case WM_STATE_TESTMODE:		OS_TPrintf("current state = WM_STATE_TESTMODE\n");	break;
	case WM_STATE_SCAN:			OS_TPrintf("current state = WM_STATE_SCAN\n");		break;
	case WM_STATE_CONNECT:		OS_TPrintf("current state = WM_STATE_CONNECT\n");	break;
	case WM_STATE_PARENT:		OS_TPrintf("current state = WM_STATE_PARENT\n");	break;
	case WM_STATE_CHILD:		OS_TPrintf("current state = WM_STATE_CHILD\n");		break;
	case WM_STATE_MP_PARENT:	OS_TPrintf("current state = WM_STATE_MP_PARENT\n");	break;
	case WM_STATE_MP_CHILD:		OS_TPrintf("current state = WM_STATE_MP_CHILD\n");	break;
	case WM_STATE_DCF_CHILD:	OS_TPrintf("current state = WM_STATE_DCF_CHILD\n");	break;
	default:					OS_TPrintf("current state = WM_STATE_MAX\n");		break;
	}

	return _wmstatus.state;
}

/*---------------------------------------------------------------------------*
    �����ϐ���`
 *---------------------------------------------------------------------------*/
static u16 ChannelListToChannel(u16 channelList)
{
	u16 i;
	for (i = 0; i < 16; i++) {
		if (channelList & (0x0001 << i)) {
			return (u16)(i + 1);
		}
	}
	return (u16)0;
}

static u16 ChannelToChannelList(int channel)
{
	u16 channelList;
	channelList = (u16)(1 << (channel - 1));
	return channelList;
}

/*===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         WcInit

  Description:  �����ʐM������������

  Returns:      None.
 *---------------------------------------------------------------------------*/
static WMParentParam wpbcDefaultParameter = {
	NULL, 0, 0,
	0,                                 // �Q�[���O���[�vID
	0x0000,                            // temporary ID (����+1�����)
	1,                                 // �G���g���[���t���O
	WPBC_NUM_OF_CHILD,                 // �ő�ڑ��q�@��
	0,                                 // �}���`�u�[�g�t���O
	0,                                 // �L�[�V�F�A�����O
	0,                                 // �A�����M�t���O
	WPBC_BEACON_PERIOD,                // beacon �Ԋu
	{0, 0, 0, 0},                      // ���[�U�[��
	{0, 0, 0, 0, 0, 0, 0, 0},          // �Q�[����
	1,                                 // �ڑ��`�����l��
	WPBC_PARENT_DATA_SIZE_MAX,         // �e�@���M�f�[�^�T�C�Y
	WPBC_CHILD_DATA_SIZE_MAX           // �q�@���M�f�[�^�T�C�Y
		// Reserves
};

static void WcInit(WPBBuf *buf)
{
	// WPB�p�������|�C���^
	wpbBuf = buf;
	// �X�e�[�g������
	wpbBuf->wcStatus = WC_STATUS_READY;
	// ���M�t���O������
	wpbBuf->wcSendFlag = FALSE;

	// �e�@�����L���b�V��Store���Ă����Ȃ��o�b�t�@�ɃR�s�[
	MI_CpuCopy32(&wpbcDefaultParameter, &wpbBuf->pparaBuf,
				 sizeof(WMParentParam));
	wpbBuf->pparaBuf.userGameInfo = wpbBuf->gameInfo;
}

/*---------------------------------------------------------------------------*
  Name:         WcStartParent

  Description:  �e�@�Ƃ��Ė����ʐM���J�n����B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcStartParent(void)
{
	switch (wpbBuf->wcStatus) {
	case WC_STATUS_READY:
		// �e�@�Ƃ��ď������J�n
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_PARENT;   // �ڕW��Ԃ�"�e�@�ڑ����"��
		Wc_Enable();
		break ;
	case WC_STATUS_BUSY:
		// �ڕW��Ԃ��X�V
		wpbBuf->wcTarget = WC_STATUS_PARENT;   // �ڕW��Ԃ�"�e�@�ڑ����"��
		break ;
	case WC_STATUS_PARENT:
		// ���ɐe�@�Ȃ̂ŏ����Ȃ�
		break ;
	case WC_STATUS_CHILD:
		// ��U���Z�b�g����
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_PARENT;   // �ڕW��Ԃ�"�e�@�ڑ����"��
		Wc_Reset();
		break ;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcStartChild

  Description:  �q�@�Ƃ��Ė����ʐM���J�n����B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcStartChild(void)
{
	switch (wpbBuf->wcStatus) {
	case WC_STATUS_READY:
		// �q�@�Ƃ��ď������J�n
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_CHILD;    // �ڕW��Ԃ�"�q�@�ڑ����"��
		Wc_Enable();
		break ;
	case WC_STATUS_BUSY:
		// �ڕW��Ԃ��X�V
		wpbBuf->wcTarget = WC_STATUS_CHILD;    // �ڕW��Ԃ�"�q�@�ڑ����"��
		break ;
	case WC_STATUS_PARENT:
		// ��U���Z�b�g����
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_CHILD;    // �ڕW��Ԃ�"�q�@�ڑ����"��
		Wc_Reset();
		break ;
	case WC_STATUS_CHILD:
		// ���Ɏq�@�Ȃ̂ŏ����Ȃ�
		break ;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcEnd

  Description:  �ʐM�O�̏�Ԃɖ߂�

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcEnd(void)
{
	switch (wpbBuf->wcStatus) {
	case WC_STATUS_READY:
		WcDebugPrintf("WcEnd: status ready\n");
		// �ڕW��Ԃ��X�V
		wpbBuf->wcTarget = WC_STATUS_END;      // �ڕW��Ԃ�"END"��
		break ;
	case WC_STATUS_BUSY:
		WcDebugPrintf("WcEnd: status busy\n");
		// �ڕW��Ԃ��X�V
//		wpbBuf->wcTarget = WC_STATUS_READY;    // �ڕW��Ԃ�"READY"��
		wpbBuf->wcTarget = WC_STATUS_END;      // �ڕW��Ԃ�"END"��
		break ;
	case WC_STATUS_PARENT:
		WcDebugPrintf("WcEnd: status parent\n");
	case WC_STATUS_CHILD:
		WcDebugPrintf("WcEnd: status parent or child\n");

		// ���Z�b�g���邱�ƂŐڑ���ؒf����
		wpbBuf->wcStatus = WC_STATUS_BUSY;
//		wpbBuf->wcTarget = WC_STATUS_READY;    // �ڕW��Ԃ�"READY"��
		wpbBuf->wcTarget = WC_STATUS_END;      // �ڕW��Ԃ�"END"��
		Wc_Reset();
		break ;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcGetStatus

  Description:  �����ʐM�̌��݂̃X�e�[�g���擾����B

  Arguments:    None.

  Returns:      ���݂̃X�e�[�g��Ԃ��B
 *---------------------------------------------------------------------------*/
static WCStatus WcGetStatus(void)
{
	return wpbBuf->wcStatus;
}

/*---------------------------------------------------------------------------*
  Name:         WcSetParentData

  Description:  �e�@�Ƃ��đ��M����f�[�^��ݒ肷��B

  Arguments:    buf  - ���M����f�[�^�ւ̃|�C���^�B
                       (32-Byte Align ����Ă���K�v������)
                size - ���M����f�[�^�̃T�C�Y�B

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcSetParentData(const void *buf, u16 size)
{
	// ���M�f�[�^�T�C�Y�m�F
	if (size > wpbBuf->pparaBuf.parentMaxSize) {
		return ;
	}
	// �O�̑��M�̊������m�F
	if (wpbBuf->wcSendFlag) {
		wpbBuf->wcSendFlag = FALSE;
		Wc_SetMPData(buf, size);
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcSetChildData

  Description:  �q�@�Ƃ��đ��M����f�[�^��ݒ肷��B

  Arguments:    buf  - ���M����f�[�^�ւ̃|�C���^�B
                       (32-Byte Align ����Ă���K�v������)
                size - ���M����f�[�^�̃T�C�Y�B

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcSetChildData(const void *buf, u16 size)
{
	// ���M�f�[�^�T�C�Y�m�F
	if (size > wpbcDefaultParameter.childMaxSize) {
		return ;
	}
	// �O�̑��M�̊������m�F
	if (wpbBuf->wcSendFlag) {
		wpbBuf->wcSendFlag = FALSE;
		Wc_SetMPData(buf, size);
	}
}

/*===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         WcCreateParentParameter

  Description:  �e�@����ҏW����B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcCreateParentParameter(void)
{
	static u16 tempID;

	wpbBuf->pparaBuf.channel = wpbBuf->sChannel;
	WcDebugPrintf("  parent channel = %d.\n", wpbBuf->sChannel);
	// tempID���C���N�������g
	wpbBuf->pparaBuf.tgid = ++tempID;
}

/*---------------------------------------------------------------------------*
  Name:         WcCreateScanParameter

  Description:  �X�L�����ݒ����ҏW����B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcCreateScanParameter(void)
{
	WMScanExParam *p = &wpbBuf->wmScanExParam.param;

	p->maxChannelTime = WPBC_SCAN_TIME_MAX;
	child_scan_channel = GetNextAllowedChannel(child_scan_channel);
	p->channelList = ChannelToChannelList(child_scan_channel);
	p->scanBuf = WcBssid_GetScanBuffer();
	p->scanBufSize = WcBssid_GetScanBufferSize();
	p->scanType = WM_SCANTYPE_PASSIVE;
	p->ssidLength = 0;
	MI_CpuFill8(p->ssid, 0xff, sizeof p->ssid);

	// �u���[�h�L���X�g�A�h���X���w�肵�A�S�e�@��T������悤�ݒ�
	MI_CpuFill8(p->bssid, 0xff, sizeof p->bssid);
}

/*---------------------------------------------------------------------------*
  Name:         WcSetNextScanChannel

  Description:  �X�L�����ݒ���̃`�����l���w������̃`�����l���ɍX�V����B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcSetNextScanChannel(void)
{
	WMScanExParam *p = &wpbBuf->wmScanExParam.param;
	u16           allowedChannel = WM_GetAllowedChannel();
	s32           i;
	u16           channel;

	if (allowedChannel == 0) return ;

	channel = ChannelListToChannel(p->channelList);
	for (i = 0; i < 16; i++) {
		if (allowedChannel & 1 << (channel + i) % 16) {
			p->channelList = ChannelToChannelList(((channel + i) % 16) + 1);
			break ;
		}
	}
}

/*---------------------------------------------------------------------------*
  Name:         Wc_Enable

  Description:  WM_Enable�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_Enable�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_Enable(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Enable failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_Enable success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_Disable();
		break ;
	case WC_STATUS_PARENT:
	case WC_STATUS_CHILD:
		Wc_PowerOn();
		break ;
	}
}

static BOOL Wc_Enable(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_Enable start.\n");
	wmResult = WM_Enable(WcCb_Enable);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_Enable failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_Disable

  Description:  WM_Disable�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_Disable�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_Disable(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Disable failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_Disable success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
	default:
		wpbBuf->wcStatus = WC_STATUS_READY; // �����READY��ԂɑJ�ڊ���
		if (wpbBuf->wcTarget == WC_STATUS_END) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			if (wpbBuf->wpbCallback) {
				WPBCallback arg;

				MI_CpuClear32(&arg, sizeof arg);
				arg.state = WPB_STATECODE_END;
				arg.errcode = WM_ERRCODE_SUCCESS;
				wpbBuf->wpbCallback(&arg);
			}
		}
		OS_TPrintf("WM_Finish!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		WM_Finish();
		finished = 1;
		break ;
	case WC_STATUS_PARENT:
		OS_TPrintf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!REALLY? DISCONNECT AND PARENT\n");
		wpbBuf->wcStatus = WC_STATUS_READY;
		WcStartParent();
		break ;
	case WC_STATUS_CHILD:
		OS_TPrintf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!REALLY? DISCONNECT AND CHILD\n");
		wpbBuf->wcStatus = WC_STATUS_READY;
		WcStartChild();
		break ;
	}
}

static BOOL Wc_Disable(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_Disable start.\n");
	wmResult = WM_Disable(WcCb_Disable);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_Disable failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_PowerOn

  Description:  WM_PowerOn�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_PowerOn�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_PowerOn(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_PowerOn failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_PowerOn success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
	case WC_STATUS_READY:
		Wc_PowerOff();
		break ;
	case WC_STATUS_PARENT:
		if (Wc_SetIndCallback()) {
			if (wpbBuf->measure_channel_flag == TRUE) {
				wpbBuf->measure_channel_flag = FALSE;
				wpbBuf->sChannel = 0;
				wpbBuf->sChannelBusyRatio = MAX_RATIO + 1;

				Wc_MeasureChannel((u16)GetNextAllowedChannel(0));
				return ;
			}

			WcCreateParentParameter();
			if (!Wc_SetParentParameter()) {
				wpbBuf->wcTarget = WC_STATUS_READY; // �ڕW��Ԃ�"READY"��
				Wc_Reset();
			}
		}
		break ;
	case WC_STATUS_CHILD:
		if (TRUE == Wc_SetIndCallback()) {
			WcCreateScanParameter();
			if (!Wc_StartScan()) {
				wpbBuf->wcTarget = WC_STATUS_READY; // �ڕW��Ԃ�"READY"��
				Wc_Reset();
			}
		}
		break ;
	}
}

static BOOL Wc_PowerOn(void)
{
	WMErrCode wmResult;

	wpbBuf->measure_channel_flag = TRUE;

	WcDebugPrintf("> WM_PowerOn start.\n");
	wmResult = WM_PowerOn(WcCb_PowerOn);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_PowerOn failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_PowerOff

  Description:  WM_PowerOff�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_PowerOff�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_PowerOff(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_PowerOff failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_PowerOff success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_Disable();
		break ;
	case WC_STATUS_PARENT:
	case WC_STATUS_CHILD:
		Wc_PowerOn();
		break ;
	}
}

static BOOL Wc_PowerOff(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_PowerOff start.\n");
	wmResult = WM_PowerOff(WcCb_PowerOff);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_PowerOff failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_SetIndCallback

  Description:  WM_SetIndCallback�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_SetIndCallback�֐������������ꍇ��TRUE��Ԃ��B
                       ���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_Indicate(void *arg)
{
	WMindCallback *cb = (WMindCallback *)arg;
	if (cb->state != 16 && cb->state != 19 /* beacon recv */ ) {
		WcDebugPrintf("- Indication. STATE: %x ERR %d reason %d\n",
					  cb->state, cb->errcode, cb->reason);
	}
}

static BOOL Wc_SetIndCallback(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetIndCallback start.\n");
	wmResult = WM_SetIndCallback(WcCb_Indicate);
	if (wmResult != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetIndCallback failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	WcDebugPrintf("< WM_SetIndCallback success.\n");
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_Reset

  Description:  WM_Reset�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_Reset�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_Reset(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Reset failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_Reset success. target=%d\n",wpbBuf->wcTarget);
	if (wpbBuf->wcTarget == WC_STATUS_READY) {
		WcDebugPrintf("WcCb_Reset: target is STATUS_READY\n");
		if (WPBC_IsActiveWPBC() == TRUE) {
			wpbBuf->wcTarget = WC_STATUS_PARENT;
		}
	} else if (wpbBuf->wcTarget == WC_STATUS_CHILD) {
		WcDebugPrintf("WcCb_Reset: target is STATUS_CHILD\n");

		child_scan_channel_count = 0;
//		WcBssid_ClearChildFoundChannel();
		WcBssid_ResetScanBuffer();
	}

	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_PowerOff();
		break ;
	case WC_STATUS_PARENT:
		WcCreateParentParameter();
		if (!Wc_SetParentParameter()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		WcCreateScanParameter();
		if (!Wc_StartScan()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	}
}

static void
WcCb_EndMP(void *arg)
{
	(void)&arg;
	Wc_Reset();
}

static void
WcCb_EndParent(void *arg)
{
	(void)&arg;
	Wc_Reset();
}

static BOOL Wc_Reset(void)
{
	WMErrCode wmResult;

	if (wpbBuf->wcStatus != WC_STATUS_BUSY &&
		wpbBuf->wcStatus != WC_STATUS_ERROR) {
		wpbBuf->wcStatus = WC_STATUS_BUSY;
	}
	WcDebugPrintf("Wc_Reset: start\n");

	switch (wm_getstatus()) {
	case WM_STATE_MP_PARENT:
		WcDebugPrintf("Wc_Reset: WM_EndMP\n");
		WM_EndMP(WcCb_EndMP);
		break;
	case WM_STATE_PARENT:
		OS_TPrintf("==================== BE CAREFUL! now in PARENT STATE\n");
		WM_EndParent(WcCb_EndParent);
		break;
	case WM_STATE_IDLE:
		if (wpbBuf->wcStatus == WC_STATUS_END) {
			Wc_PowerOff();
			break;
		}
	default:
		OS_TPrintf("exec WM_Reset: current wm status = %d\n",wm_getstatus());

		wmResult = WM_Reset(WcCb_Reset);
		if (wmResult != WM_ERRCODE_OPERATING) {
			WcDebugPrintf("< WM_Reset failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
			wpbBuf->wcStatus = WC_STATUS_ERROR;
			return FALSE;
		}
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_SetParentParameter

  Description:  WM_SetParentParameter�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_SetParentParameter�ɂ��񓯊�����������ɊJ�n�ł���
                       �ꍇ��TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_SetParentParameter(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetParentParameter failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	WcDebugPrintf("< WM_SetParentParameter success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_Reset();
		break ;
	case WC_STATUS_PARENT:
		if (!Wc_StartParent()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		wpbBuf->wcTarget = WC_STATUS_CHILD;
		// �q�@���[�h�Ɉڍs����ׂɈ�U���Z�b�g����
		Wc_Reset();
		break ;
	}
}

static BOOL Wc_SetParentParameter(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetParentParameter start.\n");
	wmResult = WM_SetParentParameter(WcCb_SetParentParameter,
									 &wpbBuf->pparaBuf);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_SetParentParameter failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_StartParent

  Description:  WM_StartParent�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_StartParent�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void disconnect_callback();

static void WcCb_StartParent(void *arg)
{
	WMstartParentCallback *cb = (WMstartParentCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_StartParent failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	switch (cb->state) {
	case WM_STATECODE_PARENT_START:
		WcDebugPrintf("< WM_StartParent success.\n");

		switch (wpbBuf->wcTarget) {
		case WC_STATUS_END:
		case WC_STATUS_READY:
			Wc_Reset();
			break ;
		case WC_STATUS_PARENT:
			if (!Wc_StartMP()) {
				wpbBuf->wcTarget = WC_STATUS_READY;
				Wc_Reset();
			}
			break ;
		case WC_STATUS_CHILD:
			wpbBuf->wcTarget = WC_STATUS_CHILD;
			// �q�@���[�h�Ɉڍs����ׂɈ�U���Z�b�g����
			Wc_Reset();
			break ;
		}
		break ;
	case WM_STATECODE_CONNECTED:
		WcDebugPrintf("- Child Connected.\n");
#ifdef MY_TEXT
		mfprintf(tc[2], "connected from aid = %d\n", cb->aid);
#endif
		if (WPBC_Connected(cb->aid, cb->macAddress, cb->ssid)
			== WPBC_RETURN_DISCONNECT) {
			Wc_Disconnect(cb->aid);
		}
		break ;
	case WM_STATECODE_BEACON_SENT:
	  //  WcDebugPrintf("- Beacon sent.\n");
		WPBC_BeaconSent();

		break ;
	case WM_STATECODE_DISCONNECTED:
		WcDebugPrintf("- Child disconnected.\n");
#ifdef MY_TEXT
		mfprintf(tc[2], "- Child disconnected. %d\n", cb->aid);
#endif
		disconnect_callback();
		WPBC_Disconnect((u16)(1 << cb->aid));
		// �R�[���o�b�N�̃`�F�[�����̏ꍇ�͂����ł�Wc_Reset���Ă΂Ȃ��B
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			//�e�@�ɂȂ�H�I���W�i���Ƃ������Ƃ���
			wpbBuf->wcTarget = WC_STATUS_PARENT;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_StartParent(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_StartParent start.\n");
	wmResult = WM_StartParent(WcCb_StartParent);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartParent failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_StartScan

  Description:  WM_StartScan�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_StartScan�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_StartScan(void *arg)
{
	WMstartScanExCallback *cb = (WMstartScanExCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_StartScan failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	WcDebugPrintf("< WM_StartScan success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
//		Wc_Reset();
//		break ;
	case WC_STATUS_PARENT:
		// �e�@���[�h�Ɉڍs����ׂɈ�UIDLE�ɖ߂�
		if (!Wc_EndScan()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		switch (cb->state) {
		case WM_STATECODE_PARENT_FOUND:
			// �e�@���i�[�o�b�t�@�̃L���b�V����j��
			DC_InvalidateRange(WcBssid_GetScanBuffer(),
							   WcBssid_GetScanBufferSize());
			WcBssid_AddFoundChild(cb);

			// Don't break here.
			// �����Ă������X�L���������s
		case WM_STATECODE_PARENT_NOT_FOUND:
			// �������X�L���������s����
			WcSetNextScanChannel();
			child_scan_channel_count++;

			if (child_scan_channel_count >= NumOfAllowedChannels()) {
				if (!Wc_EndScan()) {
					wpbBuf->wcTarget = WC_STATUS_READY;
					Wc_Reset();
				}
				break ;
			}
			WcCreateScanParameter();
			if (!Wc_StartScan()) {
				wpbBuf->wcTarget = WC_STATUS_READY;
				Wc_Reset();
			}
			break ;
		default:
			WcDebugPrintf("- Invalid state code. STATECODE: %x\n", cb->state);
			wpbBuf->wcStatus = WC_STATUS_BUSY;
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_StartScan(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_StartScan start.\n");
	wmResult = WM_StartScanEx(WcCb_StartScan, &wpbBuf->wmScanExParam.param);
	WcDebugPrintf("   channelList %04x\n",
				  &wpbBuf->wmScanExParam.param.channelList);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartScan failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_EndScan

  Description:  WM_EndScan�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_EndScan�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void set_buf(const WPBCallback *arg);
static void reset_buf();

static void WcCb_EndScan(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_EndScan failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	WcDebugPrintf("< WM_EndScan success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
	case WC_STATUS_READY:
		Wc_PowerOff();
		break ;
	case WC_STATUS_PARENT:
		WcCreateParentParameter();
		if (!Wc_SetParentParameter()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		if (wpbBuf->wpbCallback) {
			WPBCallback arg;

			MI_CpuClear32(&arg, sizeof arg);
			arg.state = WPB_STATECODE_PARENT_FOUND;
			arg.errcode = WM_ERRCODE_SUCCESS;
			arg.bssDesc = (const WMBssDesc *)wpbBuf->scanBuf;
			arg.bssDescCount = wpbBuf->child_found_num;
			wpbBuf->wpbCallback(&arg);
			if (arg.bssDesc && arg.send_ptr && arg.recv_ptr) {
				wpbBuf->parent_bssdesc_ptr = arg.bssDesc;
				set_buf(&arg);
				// �q�@�Ƃ��ăR�l�N�g�J�n
				if (!Wc_StartConnect()) {
					wpbBuf->wcTarget = WC_STATUS_READY;
					Wc_Reset();
				}
				break ;
			} else {
				reset_buf();
			}
		}
		/* �e�@�ɂȂ� */
		// wcTarget = WC_STATUS_READY;
		// WcStartParent();
		if (WPBC_GetMode() == TRUE) {
			wpbBuf->wcTarget = WC_STATUS_PARENT;
		}
		Wc_Reset();
		break ;
	}
}

static BOOL Wc_EndScan(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_EndScan start.\n");
	wmResult = WM_EndScan(WcCb_EndScan);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_EndScan failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_StartConnect

  Description:  WM_StartConnect�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_StartConnect�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_StartConnect(void *arg)
{
	WMstartConnectCallback *cb = (WMstartConnectCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_StartConnect failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		if (cb->errcode == WM_ERRCODE_NO_ENTRY) {
			WcDebugPrintf(" ! Parent doesn't accept entry now.\n");
		}
		if (cb->errcode == WM_ERRCODE_OVER_MAX_ENTRY) {
			WcDebugPrintf(" ! Over max entry of BSS group.\n");
		}
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
		Wc_Reset();
		break;
	case WC_STATUS_READY:
	case WC_STATUS_PARENT:
		WcDebugPrintf("< WM_StartConnect success.\n");
		// �ڕW��Ԃ�"�q�@"�łȂ��Ȃ����̂ŁA��U���Z�b�g����
		// �R�[���o�b�N�̃`�F�[�����̏ꍇ�͂����ł�Wc_Reset���Ă΂Ȃ��B
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		switch (cb->state) {
		case WM_STATECODE_CONNECT_START:
			// CONNECTED�ɂȂ�̂�҂̂ŁA�����Ȃ�
			break ;
		case WM_STATECODE_CONNECTED:
			// ���Ɏq�@�̏ꍇ�͉������Ȃ�
			if (wpbBuf->wcStatus == WC_STATUS_CHILD) {
				WcDebugPrintf("- Connected , but already child mode.\n");
			} else {
				// MP���J�n
				WcDebugPrintf("< WM_StartConnect success. to CHILD\n");
				if (!Wc_StartMP()) {
					wpbBuf->wcTarget = WC_STATUS_READY;
					Wc_Reset();
				}
			}
			break ;
		case WM_STATECODE_BEACON_LOST:
			WcDebugPrintf("- Beacon from parent lost.\n");
			// �r�[�R���������������ł̓��Z�b�g���Ȃ�
			break ;
		case WM_STATECODE_DISCONNECTED:
			WcDebugPrintf("- DisConnected from parent.\n");
#ifdef MY_TEXT
			mfprintf(tc[2], "1 disconnected by parent\n");
#endif
			disconnect_callback();
			wpbBuf->wcTarget = WC_STATUS_READY;
			// �R�[���o�b�N�̃`�F�[�����̏ꍇ�͂����ł�Wc_Reset���Ă΂Ȃ��B
			if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
				//�e�@�ɂȂ�H�I���W�i���Ƃ������Ƃ���
				wpbBuf->wcTarget = WC_STATUS_PARENT;
				Wc_Reset();
			}
			break ;
		default:
			WcDebugPrintf("< WM_StartConnect failed. Invalid state code. STATECODE: %x!!!!!!!!!!!!!!!!\n",
						  cb->state);
			wpbBuf->wcStatus = WC_STATUS_BUSY;
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_StartConnect(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_StartConnect start.\n");
	wmResult = WM_StartConnect(WcCb_StartConnect,
							   WcBssid_GetParentBssdesc(),
							   NULL);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartConnect failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:Wc_StartMP

  Description:  WM_StartMP�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_StartMP�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_StartMP(void *arg)
{
	WMstartMPCallback *cb = (WMstartMPCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		switch (cb->errcode) {
		case WM_ERRCODE_SEND_FAILED:
		case WM_ERRCODE_TIMEOUT:
			// ����M���������Ȃ������ꍇ��indicate
			// �Ȃɂ������ɍđ������̂�҂�
			break ;
		case WM_ERRCODE_INVALID_POLLBITMAP:
			// �������ł͂Ȃ� MP �ʐM���󂯎�����ꍇ�� indicate
			break ;
		default:
			WcDebugPrintf("< WM_StartMP failed. ERRCODE: %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
						  cb->errcode, cb->state);
			wpbBuf->wcStatus = WC_STATUS_BUSY;
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		return ;
	}
	switch (cb->state) {
	case WM_STATECODE_MP_START:
		WcDebugPrintf("< WM_StartMP success.\n");
		switch (wpbBuf->wcTarget) {
		case WC_STATUS_END:
		case WC_STATUS_READY:
OS_TPrintf("================================================================\n");
			WM_EndMP(WcCb_EndMP);
			break ;
		case WC_STATUS_PARENT:
		case WC_STATUS_CHILD:
			wpbBuf->wcSendFlag = TRUE;
			// �e(�q)�@�Ƃ��Ă̐ڑ�������Ɋ���
			wpbBuf->wcStatus = wpbBuf->wcTarget;
			if (wpbBuf->wcStatus == WC_STATUS_PARENT) {
				WPBC_StartMpParent();
			} else if (wpbBuf->wcStatus == WC_STATUS_CHILD) {
				WPBC_StartMpChild();
			}
			break ;
		}
		break ;
	case WM_STATECODE_MPEND_IND:
		// �e�@�Ƃ��Ă̑���M��������indicate
		break ;
	case WM_STATECODE_MP_IND:
		// �q�@�Ƃ��Ă̎�M��������indicate
		break ;
	}
}

static void WcCb_ReceiveData(void *arg)
{
	WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< Receive Data failedl. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", cb->errcode);
		return ;
	}
	switch (cb->state) {
	case WM_STATECODE_PORT_RECV:
		// �f�[�^��M
		switch (wpbBuf->wcStatus) {
		case WC_STATUS_PARENT:
			if (WPBC_ParentReceiveCallback(cb->data, cb->length)
				== WPBC_RETURN_DISCONNECT) {
				Wc_Disconnect(cb->aid);
				/* �ڑ����f�[�^��������������o�^ */
			}
			break ;
		case WC_STATUS_CHILD:
			if (WPBC_ChildReceiveCallback(cb->data, cb->length)
				== WPBC_RETURN_DISCONNECT) {
				Wc_Disconnect(0);
			}
			break ;
		default:
			break ;
		}
		break ;
	case WM_STATECODE_CONNECTED:
		// �ڑ��ʒm
		break ;
	case WM_STATECODE_DISCONNECTED:
		// �ؒf�ʒm
		switch (wpbBuf->wcStatus) {
		case WC_STATUS_PARENT:
#ifdef MY_TEXT
			mfprintf(tc[2], "disconnected by child %d\n", cb->aid);
#endif
			/* StartParent�̂ق��Œʒm */
//			WPBC_Disconnect((u16)(1 << cb->aid));
//			WPBC_ParentReceiveCallback(NULL, 0);
			break ;
		case WC_STATUS_CHILD:
#ifdef MY_TEXT
			mfprintf(tc[2], "disconnected by parent\n");
#endif
			WPBC_ChildReceiveCallback(NULL, 0);
			break ;
		}
		break ;
	default:
		WcDebugPrintf("< Receive Data success. STATE %d API %d ERR %d\n",
					  cb->state, cb->apiid, cb->errcode);
		break ;
	}
}

// static BOOL
BOOL Wc_StartMP(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetPortCallback start.\n");
	wmResult = WM_SetPortCallback(WC_DEFAULT_PORT, WcCb_ReceiveData, NULL);
	if (wmResult == WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetPortCallback success.\n");
	} else {
		WcDebugPrintf("< WM_SetPortCallback failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}

	wpbBuf->wcSendFlag = TRUE;

	WcDebugPrintf("> WM_StartMP start.\n");

	wmResult = WM_StartMP(WcCb_StartMP,
						  wpbBuf->recvBuf, (u16)WPB_RECEIVE_BUFFER,
						  wpbBuf->sendBuf, (u16)WPB_SEND_BUFFER,
						  0);

	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartMP failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_SetMPData

  Description:  WM_SetMPData�֐����Ăяo���B

  Arguments:    None.

  Returns:      BOOL - WM_SetMPData�ɂ��񓯊�����������ɊJ�n�ł����ꍇ��
                       TRUE��Ԃ��B���s�����ꍇ��FALSE��Ԃ��B
 *---------------------------------------------------------------------------*/
static void WcCb_SetMPData(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	// force End
	if (!pass_active_flag) {
		WcDebugPrintf("WcCb_SetMPData: -----------------------------------------------pass_active_flag=0; force end\n");
		wpbBuf->wcTarget = WC_STATUS_END;
		Wc_Reset();
		return;
	}


	wpbBuf->wcSendFlag = TRUE;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetMPData failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
	} else {
		WcDebugPrintf("< WM_SetMPData success.\n");
	}

	if (wpbBuf->wcTarget == WC_STATUS_END) {
		WcDebugPrintf("!!!!!!!!!!!!!!!!!WcCb_SetMPData: wcTarget is END. dont continue this process\n");
		Wc_Reset();
		return;
	}

	/* WM_ERRCODE_SEND_FAILED�̂Ƃ����Ăяo�� */
	if (wpbBuf->wcStatus == WC_STATUS_CHILD) {
		WPBC_SetMPDataChild();
	} else if (wpbBuf->wcStatus == WC_STATUS_PARENT) {
		WPBC_SetMPDataParent();
	}
}

static BOOL Wc_SetMPData(const void *buf, u16 size)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetMPData start. data: %08x\n", *(u32 *)buf);

	wmResult = WM_SetMPDataToPort(WcCb_SetMPData, buf, size, 0xffff,
								  WC_DEFAULT_PORT, WC_DEFAULT_PORT_PRIO);
	if (wmResult != WM_ERRCODE_OPERATING) {
		wpbBuf->wcSendFlag = TRUE;
		WcDebugPrintf("< WM_SetMPData failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*********** org-wc.c ***************/

static int NumOfAllowedChannels(void)
{
	int i, j;

	u16 allowedChannel = WM_GetAllowedChannel();
	for (i = 0, j = 0; i < 16; i++) {
		if ((allowedChannel >> i) & 0x01) {
			j++;
		}
	}
	return j;
}

static u16 next_channel(u16 chan)
{
	int ac = WM_GetAllowedChannel();

	while (++chan <= 14) {
		if (ac & 1 << chan - 1) return chan;
	}
	return 0;
}

static int GetNextAllowedChannel(int current_channel)
{
	int chan;

	chan = next_channel((u16)current_channel);
	if (chan) return chan;
	return next_channel(0);
}


static void WcCb_Disconnect(void *arg)
{
	WMDisconnectCallback *cb = (WMDisconnectCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Disconnect failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
#ifdef FORCE_CONTINUE
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			Wc_Reset();
		}
#else
		wpbBuf->wcStatus = WC_STATUS_ERROR;
#endif
		return ;
	}
	WcDebugPrintf("< WM_Disconnect success.\n");

	// force End
	if (!pass_active_flag) {
		WcDebugPrintf("WcCb_DISCONNECT: -----------------------------------------------pass_active_flag=0; force end\n");
		wpbBuf->wcTarget = WC_STATUS_END;
		Wc_Reset();
		return;
	}

	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
	case WC_STATUS_READY:
		Wc_Reset();
		break ;
	case WC_STATUS_PARENT:
#ifdef MY_TEXT
		mfprintf(tc[2], "diconnectedBitmap = %04X\n", cb->disconnectedBitmap);
#endif
		WPBC_Disconnect(cb->disconnectedBitmap);
		break ;
	case WC_STATUS_CHILD:
#ifdef MY_TEXT
		mfprintf(tc[2], "< WM_Disconnect success\n");
#endif
//		wpbBuf->wcTarget = WC_STATUS_PARENT;    // �ڕW��Ԃ�"�e�@�ڑ����"��
//		Wc_Reset();
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			wpbBuf->wcTarget = WC_STATUS_PARENT;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_Disconnect(u16 aid)
{
	int wmResult;

	WcDebugPrintf("> WM_Disconnect start.\n");
#ifdef DEBUG
	OS_TPrintf("WM_Disconnect call\n");
#endif
	wmResult = WM_Disconnect(WcCb_Disconnect, aid);

	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_Disconnect failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
#ifdef MY_TEXT
		mfprintf(tc[2], "< WM_Disconnect failed. ERRCODE: %x\n", wmResult);
#endif
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
    �d�g�g�p�����蕔��
 *---------------------------------------------------------------------------*/

static void WcCb_MeasureChannel(void *arg);

/* Wc_MeasureChannel */
static BOOL Wc_MeasureChannel(u16 channel)
{
#define WH_MEASURE_TIME         30     // 1�t���[���Ɉ��ʐM���Ă���d�g���E���邾���̊Ԋu(ms)
#define WH_MEASURE_CS_OR_ED     3      // �L�����A�Z���X��ED�l�̘_���a
#define WH_MEASURE_ED_THRESHOLD 17     // �����f�[�^�ɂ��o���I�ɗL���Ǝv���邨����ED臒l

	int wmResult;

	WcDebugPrintf("> WM_MeasureChannel start.\n");

#ifdef DEBUG
	OS_TPrintf("Channel = %d\n", channel);
#endif
	wmResult = WM_MeasureChannel(WcCb_MeasureChannel,   /* �R�[���o�b�N�ݒ� */
								 WH_MEASURE_CS_OR_ED,   /* CS or ED */
								 WH_MEASURE_ED_THRESHOLD,       /* ��2�������L�����A�Z���X�݂̂̏ꍇ�͖��� */
								 channel,       /* ����̌����`�����l�� */
								 WH_MEASURE_TIME);      /*�P�`�����l��������̒�������[ms] */

	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_MeasureChannel failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/* WcCb_MeasureChannel */
static void WcCb_MeasureChannel(void *arg)
{
	WMMeasureChannelCallback *cb = (WMMeasureChannelCallback *)arg;
	u16 channel;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< %s failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  __FUNCTION__, cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	/* ���g�p���̒Ⴂ�`�����l�����擾 (�����l 101% �Ȃ̂Ő擪�͕K���I��) */
	if (wpbBuf->sChannelBusyRatio > cb->ccaBusyRatio) {
		wpbBuf->sChannelBusyRatio = cb->ccaBusyRatio;
		wpbBuf->sChannel = cb->channel;
	}

	channel = next_channel(cb->channel);
	if (channel) {
		Wc_MeasureChannel(channel);
		return ;
	}
	WPBC_MeasureEnd();
	wpbBuf->wcTarget = WC_STATUS_PARENT;        // �ڕW��Ԃ�"�e�@�ڑ����"��
	Wc_Reset();
}

/*===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         WcBssid_GetScanBuffer

  Description:  �X�L�����o�b�t�@�𓾂�

  Arguments:    None.

  Returns:      WMBssDesc* - �X�L�����o�b�t�@�̃|�C���^
 *---------------------------------------------------------------------------*/
static WMBssDesc *WcBssid_GetScanBuffer()
{
	return (WMBssDesc *)wpbBuf->current_bssdesc_ptr;
}

static u16 WcBssid_GetScanBufferSize()
{
	int n = (u8 *)wpbBuf->scanBuf + sizeof wpbBuf->scanBuf
		- (u8 *)wpbBuf->current_bssdesc_ptr;

	if (n > WM_SIZE_SCAN_EX_BUF) {
		return WM_SIZE_SCAN_EX_BUF;
	} else {
		return (u16)n;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcBssid_AddFoundChild

  Description:  �X�L�������Č������e�@�̐����Z�b�g����

  Arguments:    arg     - �X�L��������

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcBssid_AddFoundChild(const WMStartScanExCallback *arg)
{
	if (arg->bssDescCount) {
		WMBssDesc *bssdesc = arg->bssDesc[arg->bssDescCount - 1];
		/* BssDesc�̃��[�h�� */
		int w = (u16 *)bssdesc - wpbBuf->current_bssdesc_ptr;
		int n = MATH_ROUNDUP(w + bssdesc->length, 16);

		bssdesc->length = (u16)(n - w);
		wpbBuf->current_bssdesc_ptr += n;
		wpbBuf->child_found_num += arg->bssDescCount;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcBssid_ResetScanBuffer

  Description:  �������e�@�̐����N���A����B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcBssid_ResetScanBuffer()
{
	wpbBuf->child_found_num = 0;
	wpbBuf->current_bssdesc_ptr = wpbBuf->scanBuf;
}

/*---------------------------------------------------------------------------*
  Name:         WcBssid_GetParentBssdesc

  Description:  �ڑ�����e�@��WMBssDesc�|�C���^��Ԃ�

  Arguments:    None.

  Returns:      WMBssDesc* - �e�@��WMBssDesc�|�C���^
 *---------------------------------------------------------------------------*/
static const WMBssDesc *WcBssid_GetParentBssdesc(void)
{
	return wpbBuf->parent_bssdesc_ptr;
}

/*---------------------------------------------------------------------------*
    �萔��`
 *---------------------------------------------------------------------------*/

#define REQUEST_DONE                          0xffff
#define REQUEST_NONE                          0xfffe
#define REQUEST_BYE                           0xfffd

#define HARDWARE_BUFFER_DUMMY_COUNT           3

#define MAX_PATTERN                           4
#define MAX_SEQ                               4

#define     PARENT_BEACON_SEND_COUNT_OUT  (900/WPBC_BEACON_PERIOD)


/*---------------------------------------------------------------------------*
    �\���̒�`
 *---------------------------------------------------------------------------*/
typedef struct {
	int      size;
	int      total_count;
	const u8 *user_send_data;
} PassData;

typedef struct {
	u16 req_count;
	u16 res_count;
	u8  buf[PASS_BUFFER_SIZE];
} PassBuffer;

typedef struct {
	u8 *user_recv_buffer;
	BOOL reset_done;
	BOOL send_done;
	BOOL recv_done;
	int hardware_buffer_count;
	PassBuffer send_buf;
	PassBuffer recv_buf;
	int pre_send_count;
	u32 recv_bitmap; /* mod32�Ń��[�v */
	int recv_bitmap_index;
} PassCtrl;


/********** �����f�[�^ ***********************************/

static u8 gSendBuf[512] ATTRIBUTE_ALIGN(32);    //���M�o�b�t�@

static PassData my_pass_data;
static PassCtrl pass_ctrl;

/* �e�@�p�����[�^ */
static u16 connected_bitmap = 0;
static int parent_beacon_sent_count;

static int start_pattern = 0;
static int current_pattern = 0;
static int current_seq = 0;


static BOOL pass_comm_pattern[MAX_PATTERN][MAX_SEQ] = {
	{TRUE, FALSE, TRUE, TRUE},         // FALSE -> �q�@
	{FALSE, TRUE, TRUE, TRUE},         // TRUE ->  �e�@
	{FALSE, TRUE, TRUE, TRUE},
	{TRUE, FALSE, TRUE, TRUE},
};

/*---------------------------------------------------------------------------*
    �}�N����`
 *---------------------------------------------------------------------------*/
static inline int div32(int a)
{
	return (a >> 5);
}

static inline int mod32(int a)
{
	return (a & 0x1f);
}

static inline int get_data_total_count(void)
{
	return my_pass_data.total_count;
}

/********** �����֐� *************************************/

/*---------------------------------------------------------------------------*
  Name:         pass_copy_to_structure

  Description:  WM��M�o�b�t�@����PassBuffer�\���̂ɃR�s�[����

  Arguments:    buf - WM��M�o�b�t�@
                pb  - PassBuffer�\����

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_copy_to_structure(u8 *buf, PassBuffer * pb)
{
	int i;

	pb->req_count = (u16)(((u32)(*buf++)) << 8);        /* HI */
	pb->req_count += (u16)(*buf++);    /* LO */

	pb->res_count = (u16)(((u32)(*buf++)) << 8);        /* HI */
	pb->res_count += (u16)(*buf++);    /* LO */

	for (i = 0; i < PASS_BUFFER_SIZE; i++) {
		pb->buf[i] = *buf++;
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_copy_to_buffer

  Description:  PassBuffer�\���̂���WM���M�o�b�t�@�ɃR�s�[����

  Arguments:    pb  - PassBuffer�\����
                buf - WM���M�o�b�t�@

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_copy_to_buffer(PassBuffer * pb, u8 *buf)
{
	int i;

	*buf++ = (u8)(((pb->req_count) >> 8) & 0xff);       /* HI */
	*buf++ = (u8)(pb->req_count & 0xff);        /* LO */

	*buf++ = (u8)(((pb->res_count) >> 8) & 0xff);       /* HI */
	*buf++ = (u8)(pb->res_count & 0xff);        /* LO */

	for (i = 0; i < PASS_BUFFER_SIZE; i++) {
		*buf++ = pb->buf[i];
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_BufToData

  Description:  PassBuffer�\���̂��烆�[�U�[��M�o�b�t�@�ɃR�s�[����

  Arguments:    pb  - PassBuffer�\����
                buf - ���[�U�[��M�o�b�t�@

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_BufToData(PassBuffer * pb, PassCtrl * pctrl)
{
	int res_count;
	u8  *src, *dest;

	res_count = (int)pb->res_count;
	src = pb->buf;

	if (pctrl->user_recv_buffer == NULL) {
		return ;
	}

	dest = pctrl->user_recv_buffer + (res_count * PASS_BUFFER_SIZE);
	if (res_count == get_data_total_count() - 1) {
		int mod = my_pass_data.size % PASS_BUFFER_SIZE;
		if (mod) {
			MI_CpuCopy8(src, dest, mod);
		} else {
			MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
		}
	} else {
		MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_DataToBuf

  Description:  ���[�U�[���M�o�b�t�@����PassBuffer�\���̂ɃR�s�[����

  Arguments:    seq_no - �V�[�P���X�ԍ�
                pb     - PassBuffer�\����
                buf    - ���[�U�[���M�o�b�t�@

  Returns:      None.    {TRUE, TRUE, FALSE, TRUE},

 *---------------------------------------------------------------------------*/
static void pass_DataToBuf(int seq_no, PassBuffer * pb, PassData * pd)
{
	const u8 *src;
	u8       *dest;

	pb->res_count = (u16)seq_no;

	if (seq_no != REQUEST_DONE && seq_no != REQUEST_NONE &&
		seq_no != REQUEST_BYE) {
		src = pd->user_send_data + (seq_no * PASS_BUFFER_SIZE);
		dest = pb->buf;
		if (seq_no == get_data_total_count() - 1) {
			int mod = my_pass_data.size % PASS_BUFFER_SIZE;
			if (mod) {
				MI_CpuCopy8(src, dest, mod);
			} else {
				MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
			}
		} else {
			MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
		}
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_init_recv_bitmap

  Description:  ��M�����r�b�g�}�b�v�̏�����

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_data_init_recv_bitmap()
{
	pass_ctrl.recv_bitmap = 0;
	pass_ctrl.recv_bitmap_index = 0;
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_set_recv_bitmap

  Description:  ��M�����r�b�g�}�b�v���Z�b�g����

  Arguments:    aid    - AID(AID���ƂɎ�M�o�b�t�@���Ǘ����Ă��邽��)
                seq_no - �V�[�P���X�ԍ�

  Returns:      BOOL   - FALSE/���łɃ`�F�b�N�ς�
 *---------------------------------------------------------------------------*/
static BOOL pass_data_set_recv_bitmap(int seq_no)
{
	if (seq_no < pass_ctrl.recv_bitmap_index) return FALSE;
	if (seq_no >= pass_ctrl.recv_bitmap_index + 32) return FALSE;
	if (pass_ctrl.recv_bitmap & 1 << seq_no % 32) return FALSE;
	pass_ctrl.recv_bitmap |= 1 << seq_no % 32;
	while (pass_ctrl.recv_bitmap & 1 << pass_ctrl.recv_bitmap_index % 32) {
		pass_ctrl.recv_bitmap &= ~(1 << pass_ctrl.recv_bitmap_index++ % 32);
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_get_recv_bitmap

  Description:  ��M�����r�b�g�}�b�v���`�F�b�N����

  Arguments:    seq_no - �V�[�P���X�ԍ�

  Returns:      None.
 *---------------------------------------------------------------------------*/
static BOOL pass_data_get_recv_bitmap(int seq_no)
{
	if (seq_no < pass_ctrl.recv_bitmap_index) return TRUE;
	if (seq_no >= pass_ctrl.recv_bitmap_index + 32) return FALSE;
	if (pass_ctrl.recv_bitmap & 1 << seq_no % 32) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_get_next_count

  Description:  ���ɑ���ɗv������V�[�P���X�ԍ��𓾂�

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static u16 pass_data_get_next_count()
{
	PassCtrl *pc = &pass_ctrl;
	int count;

	if (pc->recv_bitmap_index >= get_data_total_count()) {
		return REQUEST_DONE;          /* ���ׂĎ�M�ς� */
	}
	count = pc->pre_send_count;
	for (;;) {
		count++;
		if (count >= get_data_total_count() ||
			count >= pc->recv_bitmap_index + 32) {
			count = pc->recv_bitmap_index;
		}
		if (!pass_data_get_recv_bitmap(count)) {
			pc->pre_send_count = count;
			return (u16)count;
		}
		if (count == pc->pre_send_count) {
			/* �����ɗ��邱�Ƃ͂Ȃ��͂� */
			OS_TPrintf("Error ! %d %d %d %08X\n", pc->pre_send_count, pc->recv_bitmap_index, get_data_total_count(), pc->recv_bitmap);
			return REQUEST_DONE;          /* ���ׂĎ�M�ς� */
		}
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_InitBuf

  Description:  PassBuffer�\���̂̏�����

  Arguments:    pb - PassBuffer�\����

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_InitBuf(PassBuffer * pb)
{
	pb->res_count = REQUEST_NONE;
	//  pb->req_count = REQUEST_NONE;
	pb->req_count = 0;
	MI_CpuClear8(pb->buf, PASS_BUFFER_SIZE);
}


/*---------------------------------------------------------------------------*
  Name:         pass_ResetData

  Description:  �ɌĂяo�����֐��B

  Arguments:    None.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void pass_ResetData()
{
	PassCtrl *pc;
	pc = &pass_ctrl;

	pass_InitBuf(&(pc->send_buf));
	pass_InitBuf(&(pc->recv_buf));
	pass_data_init_recv_bitmap();
	pc->pre_send_count = REQUEST_NONE;
	pc->reset_done = TRUE;
	pc->send_done = FALSE;
	pc->recv_done = FALSE;
	pc->hardware_buffer_count = 0;
}


/*---------------------------------------------------------------------------*
    �O���֐�
 *---------------------------------------------------------------------------*/

static void WPBC_MeasureEnd(void)
{
	if (wpbBuf->wpbCallback) {
		WPBCallback arg;

		MI_CpuClear32(&arg, sizeof arg);
		arg.state = WPB_STATECODE_START;
		arg.errcode = WM_ERRCODE_SUCCESS;
		wpbBuf->wpbCallback(&arg);
	}
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_BeaconSent

  Description:  ���ꂿ�����ʐM�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_BeaconSent(void)
{
	parent_beacon_sent_count++;

	if (parent_beacon_sent_count > PARENT_BEACON_SEND_COUNT_OUT) {
		if (connected_bitmap == 0) {
			parent_beacon_sent_count = 0;

			if (WPBC_GetMode() == TRUE) {
				/* �e�@�̂܂� */
			} else {
				/* �q�@�ɂȂ� */
				WcStartChild();
			}
		}
	}
}


static BOOL WPBC_GetMode(void)
{
	current_seq++;
	if (current_seq > MAX_SEQ - 1) {
		current_seq = 0;
		current_pattern++;
		if (current_pattern > MAX_PATTERN - 1) {
			current_pattern = 0;
		}
		if (current_pattern == start_pattern) {
			start_pattern = (int)(OS_GetTick() % MAX_PATTERN);  /* �����̂��� */
			current_pattern = start_pattern;
		}
	}

	if (pass_comm_pattern[current_pattern][current_seq] == TRUE) {
#if 0
		OS_TPrintf("pat %d seq %d",current_pattern, current_seq );
		OS_TPrintf("P\n");
#endif
		return TRUE;
	} else {
#if 0
		OS_TPrintf("pat %d seq %d",current_pattern, current_seq );
		OS_TPrintf("C\n");
#endif
		return FALSE;
	}
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_StartMpParent

  Description:  ���ꂿ�����ʐM�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_StartMpParent(void)
{
	connected_bitmap = 0;
	parent_beacon_sent_count = 0;
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_ParentSendStep

  Description:  �e�@�Ƃ��Ďq�@�ւ̃f�[�^���M���ɌĂяo�����֐��B

  Arguments:    connected_bitmp - ���ݐڑ�����AID�r�b�g�}�b�v
                buf  - ���M�o�b�t�@�ւ̃|�C���^
                size - ���M�o�b�t�@�T�C�Y

  Returns:      ���M�f�[�^�T�C�Y
 *---------------------------------------------------------------------------*/
static int WPBC_ParentSendStep(int size)
{
#pragma unused(size)
	int send_size = 0;
	int send_buf_count;
	u8 *send_buf = gSendBuf;

	if (connected_bitmap == 0) {
		return 0;
	}

	/* ���ǂ̃��N�G�X�g�ԍ��̃Z�b�g */
	if (pass_ctrl.recv_done == TRUE) {
		if (pass_ctrl.reset_done) {
			pass_ctrl.send_buf.req_count = REQUEST_DONE;
		} else {
			pass_ctrl.send_buf.req_count = REQUEST_BYE;
		}
	} else {
		pass_ctrl.send_buf.req_count = pass_data_get_next_count();
		if (pass_ctrl.send_buf.req_count == REQUEST_DONE) {
			pass_ctrl.recv_done = TRUE;
		}
	}

	/* ����̃��N�G�X�g�ɑ΂���f�[�^�̃Z�b�g */
	if (pass_ctrl.send_done) {
		send_buf_count = REQUEST_NONE;
	} else {
		send_buf_count = pass_ctrl.recv_buf.req_count;
	}
	pass_DataToBuf(send_buf_count, &(pass_ctrl.send_buf), &my_pass_data);

	/* send_buf���瑗�M�o�b�t�@�ɃR�s�[ */
	pass_copy_to_buffer(&(pass_ctrl.send_buf), send_buf);

#ifdef DEBUG
	OS_TPrintf("parent send->%x req->%x\n", send_buf_count,
			   pass_ctrl.send_buf.req_count);
#endif
	send_size = PASS_PACKET_SIZE;

	if (send_size > 0) {
		if (send_size & 1) {
			WcSetParentData((void *)gSendBuf, (u16)(send_size + 1));
		} else {
			WcSetParentData((void *)gSendBuf, (u16)send_size);
		}
	}

	return send_size;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_Connected

  Description:  ���ꂿ�����ʐM�֐��B�e�Ƃ��đҋ@���Ɏq����ڑ����ꂽ

  Arguments:    aid.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void set_buf(const WPBCallback *arg)
{
	my_pass_data.total_count = (arg->recv_size / PASS_BUFFER_SIZE) + ((arg->recv_size % PASS_BUFFER_SIZE) ? 1 : 0);
	my_pass_data.size = arg->send_size;
	my_pass_data.user_send_data = arg->send_ptr;

	pass_ctrl.user_recv_buffer = arg->recv_ptr;

//        pass_ctrl[i].user_recv_buffer = &(((u8 *)recv_ptr)[i * send_size]);
//	pass_ctrl.keepalive = keepalive;
}

static void reset_buf()
{
	my_pass_data.total_count = 0;
	my_pass_data.size = 0;
	my_pass_data.user_send_data = NULL;

	pass_ctrl.user_recv_buffer = NULL;
}

static int WPBC_Connected(u16 aid, const u8 macAddress[], const u8 ssid[])
{
	int send_size;

	if (connected_bitmap != 0) {
		/* �ʂ̎q�@�ƒʐM���Ă���Ƃ��͑��M���Ȃ� */
		connected_bitmap |= (1 << aid);
	} else {
		connected_bitmap |= (1 << aid);
		pass_ctrl.reset_done = FALSE;
		pass_ctrl.recv_done = FALSE;
		if (wpbBuf->wpbCallback) {
			WPBCallback arg;
			int         i;

			MI_CpuClear32(&arg, sizeof arg);
			arg.state = WPB_STATECODE_CONNECTED;
			arg.errcode = WM_ERRCODE_SUCCESS;
			/* arg.bssDesc = NULL; */
			/* arg.recv_ptr = NULL; */
			for (i = 0; ; i++) {
				if (i == WM_SIZE_CHILD_SSID / sizeof(u32)) {
					/* arg.extinfo = NULL; */
					break ;
				}
				if (((const u32 *)ssid)[i] != 0) {
					arg.extinfo = ssid;
					break ;
				}
			}
			MI_CpuCopy8(macAddress, arg.macAddress, sizeof arg.macAddress);
			wpbBuf->wpbCallback(&arg);
			if (arg.send_ptr && arg.recv_ptr) {
				set_buf(&arg);
				pass_ResetData();
				send_size = WPBC_ParentSendStep(WPBC_PARENT_DATA_SIZE_MAX);
				return WPBC_RETURN_CONTINUE;
			} else {
				reset_buf();
			}
		}
	}
	return WPBC_RETURN_DISCONNECT;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_SetMPDataParent

  Description:  ���ꂿ�����ʐM�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_SetMPDataParent(void)
{
	WPBC_ParentSendStep(WPBC_PARENT_DATA_SIZE_MAX);
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_ParentReceiveCallback

  Description:  �e�@�Ƃ��Ďq�@����̃f�[�^��M���ɌĂяo�����֐��B

  Arguments:    buf    - ��M�f�[�^�ւ̃|�C���^ (NULL �Őؒf�ʒm)
                length  - ��M�f�[�^�̃T�C�Y

  Returns:      TRUE/FALSE - �f�[�^��������(TRUE)
 *---------------------------------------------------------------------------*/
static void disconnect_callback()
{
	if (!(pass_ctrl.reset_done == FALSE && pass_ctrl.recv_done)) {
		WPBCallback arg;

		pass_ctrl.reset_done = FALSE;
		pass_ctrl.recv_done = TRUE;
		MI_CpuClear32(&arg, sizeof arg);
		arg.state = WPB_STATECODE_DISCONNECTED;
		arg.errcode = WM_ERRCODE_SUCCESS;
		wpbBuf->wpbCallback(&arg);
	}
}

static int WPBC_ParentReceiveCallback(u16 *buf, u16 length)
{
	if (buf == NULL || length == 0) {
		return WPBC_RETURN_CONTINUE;   /* �ʐM���p������ */
	}

	/* �܂���M�o�b�t�@����pass_recv_buf�ɃR�s�[ */
	pass_copy_to_structure(((u8 *)buf), &(pass_ctrl.recv_buf));
	if (pass_ctrl.recv_buf.req_count == REQUEST_BYE) {
#ifdef DEBUG
		OS_TPrintf("parent : get REQUEST_BYE\n");
#endif
		disconnect_callback();
		return WPBC_RETURN_DISCONNECT;  /* �ʐM��ؒf���� */
	}
	if (pass_ctrl.reset_done == FALSE) {
		//    pass_ctrl[aid].recv_buf.req_count = REQUEST_NONE;
	} else {
		if (pass_ctrl.recv_done == FALSE) {
#ifdef DEBUG
			OS_TPrintf("parent recv->%x\n", pass_ctrl.recv_buf.res_count);
#endif
			if (pass_ctrl.recv_buf.res_count < get_data_total_count()) {
				/* ��M�����Ƀ`�F�b�N������ */
				if (TRUE == pass_data_set_recv_bitmap(pass_ctrl.recv_buf.res_count)) {
					/* ��M�f�[�^���Z�[�u */
					pass_BufToData(&(pass_ctrl.recv_buf), &pass_ctrl);
				}
			}
		} else {
			if (pass_ctrl.recv_buf.req_count == REQUEST_DONE) {
				pass_ctrl.send_done = TRUE;
			}
			if (pass_ctrl.send_done == TRUE) {
				/* ����������M�f�[�^�I���̏ꍇ */
				if (pass_ctrl.hardware_buffer_count < (HARDWARE_BUFFER_DUMMY_COUNT * 2)) {
					// �S�񂭂�܂ŕۗ�
					/* ����̂Ƃ肱�ڂ���h�� */
					pass_ctrl.hardware_buffer_count++;
					return WPBC_RETURN_CONTINUE;        /* �ʐM���p������ */
				}
				pass_ctrl.reset_done = FALSE;
				if (wpbBuf->wpbCallback) {
					WPBCallback arg;

					MI_CpuClear32(&arg, sizeof arg);
					arg.state = WPB_STATECODE_EXCHANGED;
					arg.errcode = WM_ERRCODE_SUCCESS;
					arg.bssDesc = NULL;
					wpbBuf->wpbCallback(&arg);
					if (arg.send_ptr && arg.recv_ptr) {
#ifdef DEBUG
						OS_TPrintf("Parent SetNext\n");
#endif
						set_buf(&arg);
						pass_ResetData();
						/* WPBC_ParentSendStep(WPBC_PARENT_DATA_SIZE_MAX); */
						return WPBC_RETURN_DONE;
					}
				}
				return WPBC_RETURN_CONTINUE;        /* �ʐM���p������ */
//				return WPBC_RETURN_DISCONNECT;  /* �ʐM��ؒf���� */
			}
		}
	}
	return WPBC_RETURN_CONTINUE;       /* �ʐM���p������ */
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_Disconnect

  Description:  ���ꂿ�����ʐM�֐�

  Arguments:    aid_bitmap.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_Disconnect(u16 aid_bitmap)
{
	connected_bitmap &= ~aid_bitmap;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_ChildSendStep

  Description:  �q�@�Ƃ��Đe�@����̃f�[�^��M���ɌĂяo�����֐��B

  Arguments:    None.

  Returns:      ���M�f�[�^�T�C�Y
 *---------------------------------------------------------------------------*/
static int WPBC_ChildSendStep(int size)
{
#pragma unused(size)
	int peer_request;

	/* ���ǂ̃��N�G�X�g�ԍ����Z�b�g */
	if (pass_ctrl.recv_done == TRUE) {
		if (pass_ctrl.reset_done) {
			pass_ctrl.send_buf.req_count = REQUEST_DONE;
		} else {
			pass_ctrl.send_buf.req_count = REQUEST_BYE;
		}
	} else {
		pass_ctrl.send_buf.req_count = pass_data_get_next_count();
		if (pass_ctrl.send_buf.req_count == REQUEST_DONE) {
			pass_ctrl.recv_done = TRUE;
		}
	}

	/* ����ǂ̃��N�G�X�g�ԍ��ɑ΂��ăf�[�^���Z�b�g */
	peer_request = (int)(pass_ctrl.recv_buf.req_count);
	pass_DataToBuf(peer_request, &(pass_ctrl.send_buf), &my_pass_data);

	/* send_buf���瑗�M�o�b�t�@�ɃR�s�[ */
	pass_copy_to_buffer(&(pass_ctrl.send_buf), gSendBuf);

#ifdef DEBUG
	OS_TPrintf("child send->%x req->%x\n", peer_request, pass_ctrl.send_buf.req_count);
#endif

	WcSetChildData((void *)gSendBuf, PASS_PACKET_SIZE);

	return PASS_PACKET_SIZE;           /* send size */
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_StartMpChild

  Description:  ���ꂿ�����ʐM�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_StartMpChild(void)
{
	pass_ResetData();

	WPBC_ChildSendStep(WPBC_CHILD_DATA_SIZE_MAX);
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_SetMPDataChild

  Description:  ���ꂿ�����ʐM�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_SetMPDataChild(void)
{
	int send_size;

	send_size = WPBC_ChildSendStep(WPBC_CHILD_DATA_SIZE_MAX);
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_ChildReceiveCallback

  Description:  �q�@�Ƃ��Đe�@����̃f�[�^��M���ɌĂяo�����֐��B

  Arguments:    buf     - ��M�f�[�^�ւ̃|�C���^ (NULL �Őؒf�ʒm)
                length  - ��M�f�[�^�̃T�C�Y

  Returns:      TRUE/FALSE - �f�[�^��������(TRUE)
 *---------------------------------------------------------------------------*/
static int WPBC_ChildReceiveCallback(u16 *buf, u16 length)
{
	if (buf == NULL || length == 0) {
		return WPBC_RETURN_CONTINUE;   /* �ʐM���p������ */
	}

#ifdef DEBUG
	OS_TPrintf("child recv->%x\n", pass_ctrl.recv_buf.res_count);
#endif

	/* �܂���M�o�b�t�@����pass_recv_buf�ɃR�s�[ */
	pass_copy_to_structure(((u8 *)buf), &(pass_ctrl.recv_buf));
	if (pass_ctrl.recv_buf.req_count == REQUEST_BYE) {
#ifdef DEBUG
		OS_TPrintf("child: get REQUEST_BYE\n");
#endif
		disconnect_callback();
		return WPBC_RETURN_DISCONNECT;  /* �ʐM��ؒf���� */
	}
	if (pass_ctrl.reset_done == FALSE) {
		//    pass_ctrl[MY_AID].recv_buf.req_count = REQUEST_NONE;
	} else {
		if (length < PASS_PACKET_SIZE) {
			// OS_TPrintf("length shortage aid %d = %d logical = %d\n",aid, length, PASS_PACKET_SIZE * aid );
			return WPBC_RETURN_CONTINUE;        /* �ʐM���p������ */
		}
		if (pass_ctrl.recv_done == FALSE) {
			if (pass_ctrl.recv_buf.res_count < get_data_total_count()) {
				/* ��M�����Ƀ`�F�b�N������ */
				if (TRUE == pass_data_set_recv_bitmap(pass_ctrl.recv_buf.res_count)) {
					pass_BufToData(&(pass_ctrl.recv_buf), &(pass_ctrl));
				}
			}
		} else {
			if (pass_ctrl.recv_buf.req_count == REQUEST_DONE) {
				pass_ctrl.send_done = TRUE;
			}
			if (pass_ctrl.send_done == TRUE) {
				/* ���ǂ����M�f�[�^�I���̏ꍇ */
				if (pass_ctrl.hardware_buffer_count < HARDWARE_BUFFER_DUMMY_COUNT) {
					// �Q�񂭂�܂ŕۗ�
					/* ����̂Ƃ肱�ڂ���h�� */
					pass_ctrl.hardware_buffer_count++;
					return WPBC_RETURN_CONTINUE;        /* �ʐM���p������ */
				}
				pass_ctrl.reset_done = FALSE;
				if (wpbBuf->wpbCallback) {
					WPBCallback arg;

					MI_CpuClear32(&arg, sizeof arg);
					arg.state = WPB_STATECODE_EXCHANGED;
					arg.errcode = WM_ERRCODE_SUCCESS;
					arg.bssDesc = WcBssid_GetParentBssdesc();
					wpbBuf->wpbCallback(&arg);
					if (arg.send_ptr && arg.recv_ptr) {
#ifdef DEBUG
						OS_TPrintf("Child SetNext\n");
#endif
						set_buf(&arg);
						pass_ResetData();
						/* WPBC_ChildSendStep(WPBC_CHILD_DATA_SIZE_MAX); */
						return WPBC_RETURN_DONE;
					}
				}
				return WPBC_RETURN_CONTINUE;        /* �ʐM���p������ */
//				return WPBC_RETURN_DISCONNECT;
			}
		}
	}
	return WPBC_RETURN_CONTINUE;       /* �ʐM���p������ */
}

/*===========================================================================*/
WMErrCode WPB_SetBuffer(WPBBuf *wpbBuf)
{
	if (!wpbBuf || ((u32)wpbBuf & 0x01f)) return WM_ERRCODE_INVALID_PARAM;

	WcInit(wpbBuf);
	return WM_ERRCODE_SUCCESS;
}

WMErrCode WPB_SetCallback(WPBCallbackFunc callback)
{
	if (!wpbBuf) return WM_ERRCODE_FAILED;

	wpbBuf->wpbCallback = callback;
	return WM_ERRCODE_SUCCESS;
}

WMErrCode WPB_SetGameInfo(const u16 *gameInfo,
						  u16       gameInfoLength,
						  u32       ggid)
{
	if (gameInfoLength > WM_SIZE_USER_GAMEINFO) {
		return WM_ERRCODE_INVALID_PARAM;
	}
	if (!wpbBuf) return WM_ERRCODE_FAILED;

	if (gameInfoLength) {
		MI_CpuCopy8(gameInfo, wpbBuf->pparaBuf.userGameInfo, gameInfoLength);
	}
	wpbBuf->pparaBuf.userGameInfoLength = gameInfoLength;
	wpbBuf->pparaBuf.ggid = ggid;

	return WM_ERRCODE_SUCCESS;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_Start

  Description:  ���ꂿ�����ʐM�J�n�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
WMErrCode WPB_Start()
{
	finished = 0;
	pass_active_flag = TRUE;
	WcStartParent();

	return WM_ERRCODE_SUCCESS;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_IsActiveWPBC

  Description:  ���ꂿ�����ʐM�J�n�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static BOOL WPBC_IsActiveWPBC(void)
{
	return pass_active_flag;
}

/*---------------------------------------------------------------------------*
  Name:         WPB_End

  Description:  ���ꂿ�����ʐM�I���֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
WMErrCode WPB_End(void)
{
	pass_active_flag = FALSE;
	WcEnd();                           /* PowerOff��ԂɂȂ� */
	return WM_ERRCODE_SUCCESS;
}


void WPB_ForceFinish(void)
{
	wpbBuf->wcTarget = WC_STATUS_END;
	Wc_PowerOff();
}

int
WPB_Finished(void)
{
	return finished;
}

/*---------------------------------------------------------------------------*
  Name:         WPB_TestParent

  Description:  ���ꂿ�����e�@�e�X�g�֐�

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
const WMBssDesc *WPB_TestParent(const WMBssDesc *bssDesc,
								int bssDescCount, u32 ggid)
{
	int i;
	int n = 0;
	const WMBssDesc *p = bssDesc;

	/* GGID ����v����e�@�𐔂��� */
	for (i = 0; i < bssDescCount; i++) {
		/* GameGroupID����v���邩���m�F */
		/* userGameInfo �� 4 �o�C�g�ȏ゠��A�ŏ��� 4 �o�C�g�� u32 �Ƃ��� */
		/* �ŏ�ʃr�b�g�� 0 �Ȃ狤�ʂ���Ⴂ�ɑΉ� */
		if (p->gameInfoLength >=
			(char *)&p->gameInfo.ggid - (char *)&p->gameInfo
			+ sizeof p->gameInfo.ggid &&
			p->gameInfo.ggid == ggid &&
			p->gameInfo.userGameInfoLength >= 4 &&
			(*(u32 *)p->gameInfo.userGameInfo & 1 << 31) == 0) {
			n++;
		}
		p = (const WMBssDesc *)((const u16 *)p + p->length);
	}
	if (!n) return NULL;
	n = OS_GetTickLo() % 263 % n; /* �[������ */
	p = bssDesc;
	for (i = 0; i < bssDescCount; i++) {
		/* GameGroupID����v���邩���m�F */
		/* userGameInfo �� 4 �o�C�g�ȏ゠��A�ŏ��� 4 �o�C�g�� u32 �Ƃ��� */
		/* �ŏ�ʃr�b�g�� 0 �Ȃ狤�ʂ���Ⴂ�ɑΉ� */
		if (p->gameInfoLength >=
			(char *)&p->gameInfo.ggid - (char *)&p->gameInfo
			+ sizeof p->gameInfo.ggid &&
			p->gameInfo.ggid == ggid &&
			p->gameInfo.userGameInfoLength >= 4 &&
			(*(u32 *)p->gameInfo.userGameInfo & 1 << 31) == 0) {
			if (!n) return p;
			n--;
		}
		p = (const WMBssDesc *)((const u16 *)p + p->length);
	}
	return NULL; /* �����ɂ͗��Ȃ��͂� */
}
/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
