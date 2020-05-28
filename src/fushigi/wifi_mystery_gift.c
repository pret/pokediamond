//============================================================================================
/**
 * @file	wifi_mystery_figt.c
 * @bfief	WiFi ふしぎな　おくりもの
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

// コンパイル定義

#define NETCONFIG_USE_HEAP		1
#define USE_AUTHSERVER_RELEASE			// 本番サーバへ接続

// ↓そのままROMに入れると危険なので、後で暗号化を考えようね…
#define WIFI_ND_LOGIN_NAME		"ADAJ"			// ログイン名
#ifdef USE_AUTHSERVER_RELEASE
#define WIFI_ND_LOGIN_PASSWD		"E3npkZwqAHyGCNVb"	// パスワード(本番サーバ)
#else
#define WIFI_ND_LOGIN_PASSWD		"XqQPTBt56uEndmND"	// パスワード(テストサーバ)
#endif

#define WIFI_FILE_ATTR1			""
#define WIFI_FILE_ATTR2			""
#define WIFI_FILE_ATTR3			""

// -- ND に関連した定数 --

enum {
  WIFI_MYSTERYGIFT_COMM_INIT = WIFI_MYSTERYGIFT_BASE,// ライブラリ初期化
  WIFI_MYSTERYGIFT_COMM_INIT_WAIT,		// ライブラリの初期化が完了するまで待つ

  WIFI_MYSTERYGIFT_CONNECT_INET,		// インターネットへの接続準備
  WIFI_MYSTERYGIFT_CONNECT_WAIT_INET,		// 接続されるまで待つ

  WIFI_MYSTERYGIFT_NASLOGIN_START,		// 認証サーバーへログイン開始
  WIFI_MYSTERYGIFT_NASLOGIN_WAIT,		// 認証サーバーへログイン完了まで待つ
  
  WIFI_MYSTERYGIFT_NDLIB_INIT,			// ダウンロード処理開始
  WIFI_MYSTERYGIFT_SET_ATTR,			// ファイルアクセス属性の設定
  WIFI_MYSTERYGIFT_GET_FILENUM,			// サーバーにあるファイル数を得る
  WIFI_MYSTERYGIFT_GET_FILELIST,		// サーバーにあるファイルリストを得る
  WIFI_MYSTERYGIFT_GET_FILE,			// ファイルを取得開始
  WIFI_MYSTERYGIFT_GETTING_FILE,		// ファイル取得中

  WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL,		// ダウンロードをユーザーがキャンセルした
  WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE,		// ダウンロード正常終了
  WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_LOOP,		// エラー処理待ち
  WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_WAIT,		// callbackが呼び出されるまで処理を待つ
  WIFI_MYSTERYGIFT_DOWNLOAD_ERROR,		// エラー表示後の復帰処理
  
  WIFI_MYSTERYGIFT_WAIT_CALLBACK1,		// コールバック処理が呼ばれるまで待つ
  WIFI_MYSTERYGIFT_WAIT_CALLBACK2,		// コールバック処理が呼ばれるまで待つ

  WIFI_MYSTERYGIFT_MAX
};


static u8 dwcWork[ DWC_INIT_WORK_SIZE ] ATTRIBUTE_ALIGN( 32 );
static BOOL callbackflag1;
static BOOL callbackflag2;
static wifi_result;
static DWCNdFileInfo fileInfo[ FILE_NUM ];

// プロトタイプ宣言
static void NdCleanupCallback( void );

// 本体はcomm_mystery_gift.c

int WifiMysteryGift_Main(PROC *proc, int *seq);


/*-------------------------------------------------------------------------*
 * Name        : AllocFunc
 * Description : メモリ確保関数
 * Arguments   : name  - 確保する名前
 *             : size  - 確保するサイズ
 *             : align - 確保するアライメント
 * Returns     : *void - 確保したポインタ
 *
 * sys_AllocMemoryは4byte境界で返ってくるため、それを無理やり32byte境界へ
 * アライメントし直す。
 * 返すアドレス-4の4byteに元のallocしたアドレスを保存しておいて、
 * freeする際にはその値を参照してフリーするようにしてある
 *-------------------------------------------------------------------------*/
static void* AllocFunc( DWCAllocType name, u32 size, int align )
{
#pragma unused( name, align )
  void *ptr;
  u32 *base;

  //  OS_TPrintf("org: %5d -> new: ", size);
  // サイズを32バイトアライメント分だけ加算する
  size = (((size + sizeof(void *)) + 32) & ~31) + 32;
  //  OS_TPrintf("%5d\n", size);
  // メモリ確保
  ptr = sys_AllocMemory(HEAPID_MYSTERYGIFT, size);
  // ptrを32バイト境界に変更しbaseへ定義
  base = (u32 *)(((u32)ptr + 32) & ~31);
  // その-4バイト場所にfreeする際のアドレスを代入
  base--;
  *base = (u32)ptr;
  //  OS_TPrintf("Alloc: %08X [%08X], %d [%2d]\n", ptr, base, size, align);
  // アプリへ返す値は32バイト境界
  base++;
  return base;
}


/*-------------------------------------------------------------------------*
 * Name        : FreeFunc
 * Description : メモリ開放関数
 * Arguments   : name - 開放するメモリ名
 *             : *ptr - 解放するメモリのポインタ
 *             : size - 解放するサイズ
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
 * @brief	復帰不可能なエラーが出た場合の処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static volatile BOOL cleanup_callback_flag;
static void cleanup_callback(void)
{
  cleanup_callback_flag = TRUE;
}
// こっちが登録
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
// エラーの対応処理(実態)
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
  WirelessIconEasyEnd();	// 通信アイコンを削除

  wk->wifi_errflag = FALSE;
  return WIFI_MYSTERYGIFT_DOWNLOAD_ERROR_WAIT;
}



//------------------------------------------------------------------
/**
 * @brief	インターネット接続の状態を調べる
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
  case DWC_CONNECTINET_STATE_ERROR:		// 接続失敗
#if 0
    // エラー表示
    err = DWC_GetLastError( &errcode );
    MIT_PRINTF( "   Error occurred %d %d.\n", err, errcode );
    wk->wifi_errmsg = mydwc_errorType(-errcode);
    wk->wifi_errcode = -errcode;
    DWC_ClearError();
    DWC_CleanupInet();
#endif
    break;
  case DWC_CONNECTINET_STATE_FATAL_ERROR:	// 接続失敗
    // 復帰不可能なエラーはCommStateWifiFusigiStart(...)が捕獲する
    break;
  case DWC_CONNECTINET_STATE_CONNECTED:		// 接続成功
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
 * @brief	コールバック処理を待つ
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
 * @brief	コールバック２処理を待つ
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
 * Description : ND用コールバック
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
    // ファイル数の取得でＨＴＴＰエラーが発生した場合はダウンロードサーバに繋がっていない可能性が高い
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
 * Description : DWC_NdCleanupAsync用コールバック
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
 * @brief	タイトルプロセス：メイン
 * @param	proc				プロセスへのポインタ
 * @param	seq				シーケンス用ワークへのポインタ
 * @return	ND_RESULT_EXECUTE		実行中
 * @return	ND_RESULT_COMPLETE		正常ダウンロード終了
 * @return	ND_RESULT_NOT_FOUND_FILES	ファイルが見つからなかった
 * @return	ND_RESULT_DOWNLOAD_CANCEL	ユーザーからキャンセルされた
 * @return	ND_RESULT_DOWNLOAD_ERROR	なんらかのエラーが起きた
 */
//--------------------------------------------------------------------------------------------
int WifiMysteryGift_Main(PROC *proc, int *seq)
{
  int ret;
  DWCNasLoginState nasloginstate;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  // エラーが出ていたら処理する
  if(wk->wifi_errflag == TRUE)
    *seq = WifiMysteryGift_ExecError(wk);
  // Inet接続後は毎フレーム行う接続維持してるかチェック
  if(wk->wifi_check_func){
    if(wk->wifi_check_func() == TRUE)
      *seq = WifiMysteryGift_DispError(wk);
  }
  
  //  MIT_PRINTF("WIFI: %s\n", debugseqtbl[*seq - WIFI_MYSTERYGIFT_BASE]);
  
  switch(*seq){
  case WIFI_MYSTERYGIFT_COMM_INIT:
    // ライブラリ初期化
    CommVRAMDInitialize();
    DwcOverlayStart();
    *seq = WIFI_MYSTERYGIFT_COMM_INIT_WAIT;
    break;

  case WIFI_MYSTERYGIFT_COMM_INIT_WAIT:
    /// VRAMDへイクニューモンが入るのを待つ
    if(CommIsVRAMDInitialize()){
      // デバッグ表示レベル指定
      DWC_SetReportLevel((unsigned long)(DWC_REPORTFLAG_ALL & ~DWC_REPORTFLAG_QR2_REQ));
      // メモリ確保関数設定
      DWC_SetMemFunc( AllocFunc, FreeFunc );
      // エラー管理用処理の開始
      CommStateWifiFusigiStart(wk->sv);
      *seq = WIFI_MYSTERYGIFT_CONNECT_INET;
    }
    break;

    
  case WIFI_MYSTERYGIFT_CONNECT_INET:
    // インターネットへの接続処理
    DWC_InitInetEx(&wk->stConnCtrl,COMM_DMA_NO,COMM_POWERMODE,COMM_SSL_PRIORITY);

#if defined( USE_AUTHSERVER_RELEASE )
    DWC_SetAuthServer( DWC_CONNECTINET_AUTH_RELEASE );
#endif
    // 接続開始
    DWC_ConnectInetAsync();
    // 通信アイコンを表示
    WirelessIconEasy();
    *seq =  WIFI_MYSTERYGIFT_CONNECT_WAIT_INET;
    wk->wifi_cancel = FALSE;
    break;

  case WIFI_MYSTERYGIFT_CONNECT_WAIT_INET:		// #####
    // インターネット接続が終了するまで待つ
    if(DWC_CheckInet() == FALSE){
      // まだ接続処理が終了していない
      DWC_ProcessInet();
    } else {
      // 接続処理が終了した
      if(CheckWifiConnect(wk) == TRUE){
	MIT_PRINTF("Success.\n");
	if(wk->wifi_cancel == TRUE){
	  // ユーザーによるキャンセルが入っていた
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
    // ユーザーによるキャンセル
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
    // ログイン終了まで待つ
    nasloginstate = DWC_NASLoginProcess();

    if(nasloginstate == DWC_NASLOGIN_STATE_SUCCESS){
      *seq = WIFI_MYSTERYGIFT_NDLIB_INIT;			// ログイン成功
    } else if(nasloginstate == DWC_NASLOGIN_STATE_ERROR){
      *seq = WifiMysteryGift_DispError(wk);			// ログイン失敗
    } else if(nasloginstate == DWC_NASLOGIN_STATE_CANCELED){
      wifi_result = ND_RESULT_DOWNLOAD_CANCEL;
      *seq = WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE;		// キャンセル処理
    }
    // ユーザーによるキャンセル
    if(sys.trg & PAD_BUTTON_CANCEL)
      DWC_NASLoginAbort();
    break;
    
  case WIFI_MYSTERYGIFT_NDLIB_INIT:
    // Ndライブラリ初期化
    if(DWC_NdInitAsync( NdCallback, WIFI_ND_LOGIN_NAME, WIFI_ND_LOGIN_PASSWD ) == FALSE){
      OS_TPrintf( "DWC_NdInitAsync: Failed\n" );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    WaitNdCallBack(wk, seq, WIFI_MYSTERYGIFT_SET_ATTR);
    break;

  case WIFI_MYSTERYGIFT_SET_ATTR:
    // キャンセル処理が入っていれば抜ける
    if(wk->wifi_cancel == TRUE){
      WaitNdCallBack2(wk, ND_RESULT_DOWNLOAD_CANCEL, seq, WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL);
      break;
    }
    // ファイル属性の設定
    if(DWC_NdSetAttr(WIFI_FILE_ATTR1, WIFI_FILE_ATTR2, WIFI_FILE_ATTR3) == FALSE){
      OS_TPrintf( "DWC_NdSetAttr: Failed\n." );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    *seq = WIFI_MYSTERYGIFT_GET_FILENUM;
    break;
    
  case WIFI_MYSTERYGIFT_GET_FILENUM:
    // サーバーにおかれているファイルの数を得る
    if(DWC_NdGetFileListNumAsync(&wk->server_filenum) == FALSE){
      OS_TPrintf( "DWC_NdGetFileListNumAsync: Failed.\n" );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    WaitNdCallBack(wk, seq, WIFI_MYSTERYGIFT_GET_FILELIST);
    break;
    
  case WIFI_MYSTERYGIFT_GET_FILELIST:
    if(wk->server_filenum != 1){
      // ファイルが存在しなかった、または多すぎた場合
      WaitNdCallBack2(wk, ND_RESULT_NOT_FOUND_FILES, seq, WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE);
    } else {
      // ファイルが１つだけあった
      if(DWC_NdGetFileListAsync(fileInfo, 0, FILE_NUM) == FALSE){
	OS_TPrintf( "DWC_NdGetFileListNumAsync: Failed.\n" );
	*seq = WifiMysteryGift_DispError(wk);
	break;
      }
      WaitNdCallBack(wk, seq, WIFI_MYSTERYGIFT_GET_FILE);
    }
    break;

  case WIFI_MYSTERYGIFT_GET_FILE:
    // ファイル読み込み開始
    if(DWC_NdGetFileAsync( &fileInfo[ 0 ], wk->filebuffer, WIFI_MYSTERYFILE_SIZE) == FALSE){
      OS_TPrintf( "DWC_NdGetFileAsync: Failed.\n" );
      *seq = WifiMysteryGift_DispError(wk);
      break;
    }
    *seq = WIFI_MYSTERYGIFT_GETTING_FILE;
    wk->percent = 0;
    break;

  case WIFI_MYSTERYGIFT_GETTING_FILE:		// #####
    // ファイル読み込み中
    if(callbackflag1 == FALSE){
      // ファイル読み込み中

      if(sys.trg & PAD_BUTTON_CANCEL){
	// ダウンロードキャンセル
	WaitNdCallBack2(wk, ND_RESULT_DOWNLOAD_CANCEL, seq, WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL);
      } else {
	// 進行度を表示
	if(DWC_NdGetProgress( &wk->recived, &wk->contentlen ) == TRUE){
	  if(wk->percent != (wk->recived*100)/wk->contentlen){
	    wk->percent = (wk->recived*100)/wk->contentlen;
	    MIT_PRINTF( "Download %d/100\n", wk->percent );
	  }
	}
      }

    } else {
      if(wk->wifi_cancel == FALSE){
	// ファイル読み込み終了
	WaitNdCallBack2(wk, ND_RESULT_COMPLETE, seq, WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE);
      } else {
	// ダウンロードキャンセル
	WaitNdCallBack2(wk, ND_RESULT_DOWNLOAD_CANCEL, seq, WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE);
      }
    }
    break;

  case WIFI_MYSTERYGIFT_DOWNLOAD_CANCEL:
    if(DWC_NdCancelAsync() == FALSE){
      *seq = WIFI_MYSTERYGIFT_DOWNLOAD_COMPLETE;
    } else {
      wk->wifi_check_func = NULL;
      // 通信アイコンを削除
      WirelessIconEasyEnd();
      // エラー管理用処理の終了
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
      // 通信アイコンを削除
      WirelessIconEasyEnd();
      // エラー管理用処理の終了
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
      // エラー管理用処理の終了
      CommStateWifiDPWEnd();
      DwcOverlayEnd();
      CommVRAMDFinalize();

      return ND_RESULT_DOWNLOAD_ERROR;
    }
    break;
    

  case WIFI_MYSTERYGIFT_WAIT_CALLBACK1:		// #####
    // コールバック処理を待つ
    if(callbackflag1 == TRUE){
      callbackflag1 = FALSE;
      *seq = wk->wifi_next_seq;
    } else if(sys.trg & PAD_BUTTON_CANCEL){
      OS_TPrintf("キャンセルしました 3 \n");
      wk->wifi_cancel = TRUE;
    }
    break;

  case WIFI_MYSTERYGIFT_WAIT_CALLBACK2:
    // コールバック処理を待つ
    if(callbackflag2 == TRUE){
      callbackflag2 = FALSE;
      *seq = wk->wifi_next_seq;
    } else if(sys.trg & PAD_BUTTON_CANCEL){
      OS_TPrintf("キャンセルしました 3 \n");
      wk->wifi_cancel = TRUE;
    }
    break;
  }
  return ND_RESULT_EXECUTE;
}


/*  */
