//============================================================================================
/**
 * @file	wifi_mystery_figt.c
 * @bfief	WiFi �ӂ����ȁ@���������
 * @author	Satoshi Mitsuhara
 * @date	06.06.23
 *
 * $Id: wifi_mystery_gift.c,v 1.18 2006/08/12 06:29:26 mitsuhara Exp $
 */
//============================================================================================
#include <dwc.h>

#include "system/heapdefine.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/wm_icon.h"
#include "wifi/dwc_rap.h"

#include "comm_mystery_gift.h"
#include "mysterylib.h"

// �R���p�C����`

#define NETCONFIG_USE_HEAP		1
#define USE_AUTHSERVER_RELEASE			// �{�ԃT�[�o�֐ڑ�

// �����̂܂�ROM�ɓ����Ɗ댯�Ȃ̂ŁA��ňÍ������l���悤�ˁc
#define WIFI_ND_LOGIN_NAME		"ADAJ"			// ���O�C����
#ifdef USE_AUTHSERVER_RELEASE
#define WIFI_ND_LOGIN_PASSWD		"E3npkZwqAHyGCNVb"	// �p�X���[�h(�{�ԃT�[�o)
#else
#define WIFI_ND_LOGIN_PASSWD		"XqQPTBt56uEndmND"	// �p�X���[�h(�e�X�g�T�[�o)
#endif

#define WIFI_FILE_ATTR1			""
#define WIFI_FILE_ATTR2			""
#define WIFI_FILE_ATTR3			""

// -- ND �Ɋ֘A�����萔 --

enum {
  WIFI_MYSTERYGIFT_COMM_INIT = WIFI_MYSTERYGIFT_BASE,// ���C�u����������
  WIFI_MYSTERYGIFT_COMM_INIT_WAIT,		// ���C�u�����̏���������������܂ő҂�

  WIFI_MYSTERYGIFT_CONNECT_INET,		// �C���^�[�l�b�g�ւ̐ڑ�����
  WIFI_MYSTERYGIFT_CONNECT_WAIT_INET,		// �ڑ������܂ő҂�

  WIFI_MYSTERYGIFT_NASLOGIN_START,		// �F�؃T�[�o�[�փ��O�C���J�n
  WIFI_MYSTERYGIFT_NASLOGIN_WAIT,		// �F�؃T�[�o�[�փ��O�C�������܂ő҂�
  
  WIFI_MYSTERYGIFT_NDLIB_INIT,			// �_�E�����[�h�����J�n
  WIFI_MYSTERYGIFT_SET_ATTR,			// �t�@�C���A�N�Z�X�����̐ݒ�
  WIFI_MYSTERYGIFT_GET_FILENUM,			// �T�[�o�[�ɂ���t�@�C�����𓾂�
  WIFI_MYSTERYGIFT_GET_FILELIST,		// �T�[�o�[�ɂ���t�@�C�����X�g�𓾂�
  WIFI_MYSTERYGIFT_GET_FILE,			// �t�@�C�����擾�J�n
  WIFI_MYSTERYGIFT_GETTING_FILE,		// �t�@�C���擾��

  WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL,		// �_�E�����[�h�����[�U�[���L�����Z������
  WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE,		// �_�E�����[�h����I��
  WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_LOOP,		// �G���[�����҂�
  WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_WAIT,		// callback���Ăяo�����܂ŏ�����҂�
  WIFI_MYSTERYGIFT_DOWNLOAD_ERROR,		// �G���[�\����̕��A����
  
  WIFI_MYSTERYGIFT_WAIT_CALLBACK1,		// �R�[���o�b�N�������Ă΂��܂ő҂�
  WIFI_MYSTERYGIFT_WAIT_CALLBACK2,		// �R�[���o�b�N�������Ă΂��܂ő҂�

  WIFI_MYSTERYGIFT_MAX
};


static u8 dwcWork[ DWC_INIT_WORK_SIZE ] ATTRIBUTE_ALIGN( 32 );
static BOOL callbackflag1;
static BOOL callbackflag2;
static wifi_result;
static DWCNdFileInfo fileInfo[ FILE_NUM ];

// �v���g�^�C�v�錾
static void NdCleanupCallback( void );

// �{�̂�comm_mystery_gift.c

int WifiMysteryGift_Main(PROC *proc, int *seq);


/*-------------------------------------------------------------------------*
 * Name        : AllocFunc
 * Description : �������m�ۊ֐�
 * Arguments   : name  - �m�ۂ��閼�O
 *             : size  - �m�ۂ���T�C�Y
 *             : align - �m�ۂ���A���C�����g
 * Returns     : *void - �m�ۂ����|�C���^
 *
 * sys_AllocMemory��4byte���E�ŕԂ��Ă��邽�߁A����𖳗����32byte���E��
 * �A���C�����g�������B
 * �Ԃ��A�h���X-4��4byte�Ɍ���alloc�����A�h���X��ۑ����Ă����āA
 * free����ۂɂ͂��̒l���Q�Ƃ��ăt���[����悤�ɂ��Ă���
 *-------------------------------------------------------------------------*/
static void* AllocFunc( DWCAllocType name, u32 size, int align )
{
#pragma unused( name, align )
  void *ptr;
  u32 *base;

  //  OS_TPrintf("org: %5d -> new: ", size);
  // �T�C�Y��32�o�C�g�A���C�����g���������Z����
  size = (((size + sizeof(void *)) + 32) & ~31) + 32;
  //  OS_TPrintf("%5d\n", size);
  // �������m��
  ptr = sys_AllocMemory(HEAPID_MYSTERYGIFT, size);
  // ptr��32�o�C�g���E�ɕύX��base�֒�`
  base = (u32 *)(((u32)ptr + 32) & ~31);
  // ����-4�o�C�g�ꏊ��free����ۂ̃A�h���X����
  base--;
  *base = (u32)ptr;
  //  OS_TPrintf("Alloc: %08X [%08X], %d [%2d]\n", ptr, base, size, align);
  // �A�v���֕Ԃ��l��32�o�C�g���E
  base++;
  return base;
}


/*-------------------------------------------------------------------------*
 * Name        : FreeFunc
 * Description : �������J���֐�
 * Arguments   : name - �J�����郁������
 *             : *ptr - ������郁�����̃|�C���^
 *             : size - �������T�C�Y
 * Returns     : None.
 *-------------------------------------------------------------------------*/
static void FreeFunc( DWCAllocType name, void* ptr, u32 size  )
{
#pragma unused( name, size )
  u32 *base;

  if(!ptr) return;
  base = (u32 *)((u32)ptr - 4);
  //  OS_Printf("Free: %08X [%08X]\n", ptr, *base);
  sys_FreeMemoryEz((void *)*base);
}


//------------------------------------------------------------------
/**
 * @brief	���A�s�\�ȃG���[���o���ꍇ�̏���
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static volatile BOOL cleanup_callback_flag;
static void cleanup_callback(void)
{
  cleanup_callback_flag = TRUE;
}
// ���������o�^
static int WifiMysteryGift_DispError(MYSTERYGIFT_WORK *wk)
{
  DWCError err;
  DWCErrorType errtype;
  int errcode;

  err = DWC_GetLastErrorEx(&errcode, &errtype);

  OS_TPrintf("code: %d : type: %d\n", errcode, errtype);
  wk->wifi_errmsg = mydwc_errorType(-errcode);
  wk->wifi_errcode = -errcode;
  wk->wifi_errtype = errtype;
  wk->wifi_errflag = TRUE;
  cleanup_callback_flag = FALSE;
  SetTimeWaitIconEx(wk, FALSE);

  return WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_LOOP;
}
// �G���[�̑Ή�����(����)
static int WifiMysteryGift_ExecError(MYSTERYGIFT_WORK *wk)
{
  DWCInetResult result;
  
  switch(wk->wifi_errtype){
  case DWC_ETYPE_SHUTDOWN_ND:
  case DWC_ETYPE_DISCONNECT:
    result = DWC_GetInetStatus();
    //    if(result == DWC_CONNECT_STATE_OPERATED ||
    //       result == 
    //    DWC_NdCleanupAsync(cleanup_callback);
    cleanup_callback_flag = TRUE;
    break;
  default:		// #####
    cleanup_callback_flag = TRUE;
    break;
  }
  WirelessIconEasyEnd();	// �ʐM�A�C�R�����폜

  wk->wifi_errflag = FALSE;
  return WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_WAIT;
}



//------------------------------------------------------------------
/**
 * @brief	�C���^�[�l�b�g�ڑ��̏�Ԃ𒲂ׂ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL CheckWifiConnect(MYSTERYGIFT_WORK *wk)
{
  DWCApInfo apinfo;
  DWCError err;
  int  errcode, errmsg;
  

  switch(DWC_GetInetStatus()){
  case DWC_CONNECTINET_STATE_ERROR:		// �ڑ����s
#if 0
    // �G���[�\��
    err = DWC_GetLastError( &errcode );
    MIT_PRINTF( "   Error occurred %d %d.\n", err, errcode );
    wk->wifi_errmsg = mydwc_errorType(-errcode);
    wk->wifi_errcode = -errcode;
    DWC_ClearError();
    DWC_CleanupInet();
#endif
    break;
  case DWC_CONNECTINET_STATE_FATAL_ERROR:	// �ڑ����s
    // ���A�s�\�ȃG���[��CommStateWifiFusigiStart(...)���ߊl����
    break;
  case DWC_CONNECTINET_STATE_CONNECTED:		// �ڑ�����
    MIT_PRINTF( "   CONNECTED!!!.\n" );
    if( DWC_GetApInfo(&apinfo) == TRUE ) {
      MIT_PRINTF( "   DWCApInfo.aptype = %d\n", apinfo.aptype );
      MIT_PRINTF( "   DWCApInfo.area   = %d\n", apinfo.area );
      MIT_PRINTF( "   DWCApInfo.spotinfo = %s\n", apinfo.spotinfo );
      MIT_PRINTF( "   DWCApInfo.essid = %s\n", apinfo.essid );
      MIT_PRINTF( "   DWCApInfo.bssid = %02x:%02x:%02x:%02x:%02x:%02x\n",
		  apinfo.bssid[0], apinfo.bssid[1], apinfo.bssid[2], apinfo.bssid[3], apinfo.bssid[4], apinfo.bssid[5] );
    }
    else {
      MIT_PRINTF( "   Failed to get DWCApInfo\n" );
    }
    return TRUE;
    break;
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�R�[���o�b�N������҂�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void WaitNdCallBack(MYSTERYGIFT_WORK *wk, int *seq, int next_seq)
{
  callbackflag1 = FALSE;
  wk->wifi_next_seq = next_seq;
  *seq = WIFI_MYSTERYGIFT_WAIT_CALLBACK1;
}


//------------------------------------------------------------------
/**
 * @brief	�R�[���o�b�N�Q������҂�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void WaitNdCallBack2(MYSTERYGIFT_WORK *wk, int result, int *seq, int next_seq)
{
  callbackflag2 = FALSE;
  wifi_result = result;
  wk->wifi_next_seq = next_seq;
  *seq = WIFI_MYSTERYGIFT_WAIT_CALLBACK2;
  DWC_NdCleanupAsync( NdCleanupCallback );
}


/*-------------------------------------------------------------------------*
 * Name        : NdCallback
 * Description : ND�p�R�[���o�b�N
 * Arguments   : None.
 * Returns     : None.
 *-------------------------------------------------------------------------*/
static void NdCallback(DWCNdCallbackReason reason, DWCNdError errpr, int servererror)
{
#pragma unused(reason)
#pragma unused(errpr)
#pragma unused(servererror)
  MIT_PRINTF("NdCallback: Called\n");
  switch(reason) {
  case DWC_ND_CBREASON_GETFILELISTNUM:
    MIT_PRINTF("DWC_ND_CBREASON_GETFILELISTNUM\n");
    break;
  case DWC_ND_CBREASON_GETFILELIST:
    MIT_PRINTF("DWC_ND_CBREASON_GETFILELIST\n");
    break;
  case DWC_ND_CBREASON_GETFILE:
    MIT_PRINTF("DWC_ND_CBREASON_GETFILE\n");
    break;
  case DWC_ND_CBREASON_INITIALIZE:
    MIT_PRINTF("DWC_ND_CBREASON_INITIALIZE\n");
    break;
  }
	
  switch(errpr) {
  case DWC_ND_ERROR_NONE:
    MIT_PRINTF("DWC_ND_NOERR\n");
    break;
  case DWC_ND_ERROR_ALLOC:
    MIT_PRINTF("DWC_ND_MEMERR\n");
    break;
  case DWC_ND_ERROR_BUSY:
    MIT_PRINTF("DWC_ND_BUSYERR\n");
    break;
  case DWC_ND_ERROR_HTTP:
    MIT_PRINTF("DWC_ND_HTTPERR\n");
    // �t�@�C�����̎擾�łg�s�s�o�G���[�����������ꍇ�̓_�E�����[�h�T�[�o�Ɍq�����Ă��Ȃ��\��������
    if( reason == DWC_ND_CBREASON_GETFILELISTNUM )
      {
	MIT_PRINTF( "It is not possible to connect download server.\n." );
	OS_Terminate();
      }
    break;
  case DWC_ND_ERROR_BUFFULL:
    MIT_PRINTF("DWC_ND_BUFFULLERR\n");
    break;
  case DWC_ND_ERROR_DLSERVER:
    MIT_PRINTF("DWC_ND_SERVERERR\n");
    break;
  case DWC_ND_ERROR_CANCELED:
    MIT_PRINTF("DWC_ND_CANCELERR\n");
    break;
  }
  MIT_PRINTF("errorcode = %d\n", servererror);
  callbackflag1 = TRUE;
}


/*-------------------------------------------------------------------------*
 * Name        : NdCleanupCallback
 * Description : DWC_NdCleanupAsync�p�R�[���o�b�N
 * Arguments   : None.
 * Returns     : None.
 *-------------------------------------------------------------------------*/
static void NdCleanupCallback( void )
{
  MIT_PRINTF("--------------------------------\n");
  switch( wifi_result )
    {
    case ND_RESULT_COMPLETE:
      MIT_PRINTF("DWC_ND: finished - complete -\n");
      break;
    case ND_RESULT_NOT_FOUND_FILES:
      MIT_PRINTF("DWC_ND: finished - no files -\n");
      break;
    case ND_RESULT_DOWNLOAD_CANCEL:
      MIT_PRINTF("DWC_ND: finished - cancel -\n");
      break;
    }
  MIT_PRINTF("--------------------------------\n");
  callbackflag2 = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�F���C��
 * @param	proc				�v���Z�X�ւ̃|�C���^
 * @param	seq				�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	ND_RESULT_EXECUTE		���s��
 * @return	ND_RESULT_COMPLETE		����_�E�����[�h�I��
 * @return	ND_RESULT_NOT_FOUND_FILES	�t�@�C����������Ȃ�����
 * @return	ND_RESULT_DOWNLOAD_CANCEL	���[�U�[����L�����Z�����ꂽ
 * @return	ND_RESULT_DOWNLOAD_ERROR	�Ȃ�炩�̃G���[���N����
 */
//--------------------------------------------------------------------------------------------
int WifiMysteryGift_Main(PROC *proc, int *seq)
{
  int ret;
  DWCNasLoginState nasloginstate;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  // �G���[���o�Ă����珈������
  if(wk->wifi_errflag == TRUE)
    *seq = WifiMysteryGift_ExecError(wk);
  // Inet�ڑ���͖��t���[���s���ڑ��ێ����Ă邩�`�F�b�N
  if(wk->wifi_check_func){
    if(wk->wifi_check_func() == TRUE)
      *seq = WifiMysteryGift_DispError(wk);
  }
  
  //  MIT_PRINTF("WIFI: %s\n", debugseqtbl[*seq - WIFI_MYSTERYGIFT_BASE]);
  
  switch(*seq){
  case WIFI_MYSTERYGIFT_COMM_INIT:
    // ���C�u����������
    CommVRAMDInitialize();
    DwcOverlayStart();
    *seq = WIFI_MYSTERYGIFT_COMM_INIT_WAIT;
    break;

  case WIFI_MYSTERYGIFT_COMM_INIT_WAIT:
    /// VRAMD�փC�N�j���[����������̂�҂�
    if(CommIsVRAMDInitialize()){
      // �f�o�b�O�\�����x���w��
      DWC_SetReportLevel((unsigned long)(DWC_REPORTFLAG_ALL & ~DWC_REPORTFLAG_QR2_REQ));
      // �������m�ۊ֐��ݒ�
      DWC_SetMemFunc( AllocFunc, FreeFunc );
      // �G���[�Ǘ��p�����̊J�n
      CommStateWifiFusigiStart(wk->sv);
      *seq = WIFI_MYSTERYGIFT_CONNECT_INET;
    }
    break;

    
  case WIFI_MYSTERYGIFT_CONNECT_INET:
    // �C���^�[�l�b�g�ւ̐ڑ�����
    DWC_InitInetEx(&wk->stConnCtrl,COMM_DMA_NO,COMM_POWERMODE,COMM_SSL_PRIORITY);

#if defined( USE_AUTHSERVER_RELEASE )
    DWC_SetAuthServer( DWC_CONNECTINET_AUTH_RELEASE );
#endif
    // �ڑ��J�n
    DWC_ConnectInetAsync();
    // �ʐM�A�C�R����\��
    WirelessIconEasy();
    *seq =  WIFI_MYSTERYGIFT_CONNECT_WAIT_INET;
    wk->wifi_cancel = FALSE;
    break;

  case WIFI_MYSTERYGIFT_CONNECT_WAIT_INET:		// #####
    // �C���^�[�l�b�g�ڑ����I������܂ő҂�
    if(DWC_CheckInet() == FALSE){
      // �܂��ڑ��������I�����Ă��Ȃ�
      DWC_ProcessInet();
    } else {
      // �ڑ��������I������
      if(CheckWifiConnect(wk) == TRUE){
	MIT_PRINTF("Success.\n");
	if(wk->wifi_cancel == TRUE){
	  // ���[�U�[�ɂ��L�����Z���������Ă���
	  wifi_result = ND_RESULT_DOWNLOAD_CANCEL;
	  *seq = WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE;
	} else {
	  wk->wifi_check_func = DWC_UpdateConnection;
	  *seq = WIFI_MYSTERYGIFT_NASLOGIN_START;
	}
      } else {
	*seq = WifiMysteryGift_DispError(wk);
      }
    }
    // ���[�U�[�ɂ��L�����Z��
    if(sys.trg & PAD_BUTTON_CANCEL)
      wk->wifi_cancel = TRUE;
    break;

  case WIFI_MYSTERYGIFT_NASLOGIN_START:
    // NASLogin
    if(DWC_NASLoginAsync() == FALSE)
      *seq = WifiMysteryGift_DispError(wk);
    else
      *seq = WIFI_MYSTERYGIFT_NASLOGIN_WAIT;
    break;

  case WIFI_MYSTERYGIFT_NASLOGIN_WAIT:
    // ���O�C���I���܂ő҂�
    nasloginstate = DWC_NASLoginProcess();

    if(nasloginstate == DWC_NASLOGIN_STATE_SUCCESS){
      *seq = WIFI_MYSTERYGIFT_NDLIB_INIT;			// ���O�C������
    } else if(nasloginstate == DWC_NASLOGIN_STATE_ERROR){
      *seq = WifiMysteryGift_DispError(wk);			// ���O�C�����s
    } else if(nasloginstate == DWC_NASLOGIN_STATE_CANCELED){
      wifi_result = ND_RESULT_DOWNLOAD_CANCEL;
      *seq = WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE;		// �L�����Z������
    }
    // ���[�U�[�ɂ��L�����Z��
    if(sys.trg & PAD_BUTTON_CANCEL)
      DWC_NASLoginAbort();
    break;
    
  case WIFI_MYSTERYGIFT_NDLIB_INIT:
    // Nd���C�u����������
    if(DWC_NdInitAsync( NdCallback, WIFI_ND_LOGIN_NAME, WIFI_ND_LOGIN_PASSWD ) == FALSE){
      OS_TPrintf( "DWC_NdInitAsync: Failed\n" );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    WaitNdCallBack(wk, seq, WIFI_MYSTERYGIFT_SET_ATTR);
    break;

  case WIFI_MYSTERYGIFT_SET_ATTR:
    // �L�����Z�������������Ă���Δ�����
    if(wk->wifi_cancel == TRUE){
      WaitNdCallBack2(wk, ND_RESULT_DOWNLOAD_CANCEL, seq, WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL);
      break;
    }
    // �t�@�C�������̐ݒ�
    if(DWC_NdSetAttr(WIFI_FILE_ATTR1, WIFI_FILE_ATTR2, WIFI_FILE_ATTR3) == FALSE){
      OS_TPrintf( "DWC_NdSetAttr: Failed\n." );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    *seq = WIFI_MYSTERYGIFT_GET_FILENUM;
    break;
    
  case WIFI_MYSTERYGIFT_GET_FILENUM:
    // �T�[�o�[�ɂ�����Ă���t�@�C���̐��𓾂�
    if(DWC_NdGetFileListNumAsync(&wk->server_filenum) == FALSE){
      OS_TPrintf( "DWC_NdGetFileListNumAsync: Failed.\n" );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    WaitNdCallBack(wk, seq, WIFI_MYSTERYGIFT_GET_FILELIST);
    break;
    
  case WIFI_MYSTERYGIFT_GET_FILELIST:
    if(wk->server_filenum != 1){
      // �t�@�C�������݂��Ȃ������A�܂��͑��������ꍇ
      WaitNdCallBack2(wk, ND_RESULT_NOT_FOUND_FILES, seq, WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE);
    } else {
      // �t�@�C�����P����������
      if(DWC_NdGetFileListAsync(fileInfo, 0, FILE_NUM) == FALSE){
	OS_TPrintf( "DWC_NdGetFileListNumAsync: Failed.\n" );
	*seq = WifiMysteryGift_DispError(wk);
	break;
      }
      WaitNdCallBack(wk, seq, WIFI_MYSTERYGIFT_GET_FILE);
    }
    break;

  case WIFI_MYSTERYGIFT_GET_FILE:
    // �t�@�C���ǂݍ��݊J�n
    if(DWC_NdGetFileAsync( &fileInfo[ 0 ], wk->filebuffer, WIFI_MYSTERYFILE_SIZE) == FALSE){
      OS_TPrintf( "DWC_NdGetFileAsync: Failed.\n" );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    *seq = WIFI_MYSTERYGIFT_GETTING_FILE;
    wk->percent = 0;
    break;

  case WIFI_MYSTERYGIFT_GETTING_FILE:		// #####
    // �t�@�C���ǂݍ��ݒ�
    if(callbackflag1 == FALSE){
      // �t�@�C���ǂݍ��ݒ�

      if(sys.trg & PAD_BUTTON_CANCEL){
	// �_�E�����[�h�L�����Z��
	WaitNdCallBack2(wk, ND_RESULT_DOWNLOAD_CANCEL, seq, WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL);
      } else {
	// �i�s�x��\��
	if(DWC_NdGetProgress( &wk->recived, &wk->contentlen ) == TRUE){
	  if(wk->percent != (wk->recived*100)/wk->contentlen){
	    wk->percent = (wk->recived*100)/wk->contentlen;
	    MIT_PRINTF( "Download %d/100\n", wk->percent );
	  }
	}
      }

    } else {
      if(wk->wifi_cancel == FALSE){
	// �t�@�C���ǂݍ��ݏI��
	WaitNdCallBack2(wk, ND_RESULT_COMPLETE, seq, WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE);
      } else {
	// �_�E�����[�h�L�����Z��
	WaitNdCallBack2(wk, ND_RESULT_DOWNLOAD_CANCEL, seq, WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE);
      }
    }
    break;

  case WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL:
    if(DWC_NdCancelAsync() == FALSE){
      *seq = WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE;
    } else {
      wk->wifi_check_func = NULL;
      // �ʐM�A�C�R�����폜
      WirelessIconEasyEnd();
      // �G���[�Ǘ��p�����̏I��
      CommStateWifiFusigiEnd();
      DwcOverlayEnd();
      CommVRAMDFinalize();

      MIT_PRINTF("download cancel\n");
      return wifi_result;
    }
    break;
    
  case WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE:
    MIT_PRINTF("inet disabling...\n");
    if(DWC_CleanupInetAsync() == TRUE){
      wk->wifi_check_func = NULL;
      // �ʐM�A�C�R�����폜
      WirelessIconEasyEnd();
      // �G���[�Ǘ��p�����̏I��
      CommStateWifiDPWEnd();
      DwcOverlayEnd();
      CommVRAMDFinalize();

      MIT_PRINTF("Internet close complete\n");
      return wifi_result;
    }
    break;

  case WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_LOOP:
    break;
  case WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_WAIT:
    if(cleanup_callback_flag == TRUE){
      WifiMysteryGift_ErrorDisp(wk);
      if(wk->wifi_errtype == DWC_ETYPE_DISCONNECT)
	DWC_CleanupInet();
      *seq = WIFI_MYSTERYGIFT_DOWNLOAD_ERROR;
    }
    break;

  case WIFI_MYSTERYGIFT_DOWNLOAD_ERROR:
    if(sys.trg & PAD_BUTTON_DECIDE){

      wk->wifi_check_func = NULL;
      DWC_ClearError();
      // �G���[�Ǘ��p�����̏I��
      CommStateWifiDPWEnd();
      DwcOverlayEnd();
      CommVRAMDFinalize();

      return ND_RESULT_DOWNLOAD_ERROR;
    }
    break;
    

  case WIFI_MYSTERYGIFT_WAIT_CALLBACK1:		// #####
    // �R�[���o�b�N������҂�
    if(callbackflag1 == TRUE){
      callbackflag1 = FALSE;
      *seq = wk->wifi_next_seq;
    } else if(sys.trg & PAD_BUTTON_CANCEL){
      OS_TPrintf("�L�����Z�����܂��� 3 \n");
      wk->wifi_cancel = TRUE;
    }
    break;

  case WIFI_MYSTERYGIFT_WAIT_CALLBACK2:
    // �R�[���o�b�N������҂�
    if(callbackflag2 == TRUE){
      callbackflag2 = FALSE;
      *seq = wk->wifi_next_seq;
    } else if(sys.trg & PAD_BUTTON_CANCEL){
      OS_TPrintf("�L�����Z�����܂��� 3 \n");
      wk->wifi_cancel = TRUE;
    }
    break;
  }
  return ND_RESULT_EXECUTE;
}


/*  */
