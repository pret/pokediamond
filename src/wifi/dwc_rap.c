//=============================================================================
/**
 * @file	dwc_rap.c
 * @bfief	DWCラッパー。オーバーレイモジュールに置くもの
 * @author	kazuki yoshihara
 * @date	06/02/23
 */
//=============================================================================

#include "common.h"
#include "communication/comm_def.h"
#include "communication/comm_state.h"
#include "wifi/dwc_rap.h"
#include "wifi/vchat.h"
#include "system/pm_debug_wifi.h"
#include <vct.h>


// 何秒間通信が届かないとタイムアウトと判断するか
#define MYDWC_TIMEOUTSEC 10


// 何フレーム送信がないと、KEEP_ALIVEトークンを送るか。
#define KEEPALIVE_TOKEN_TIME 120

// ボイスチャットを利用する場合は定義する。
#define MYDWC_USEVCHA

#ifdef MYDWC_USEVCHA
// 接続して自動的にボイスチャットをスタートさせる場合に定義する。
#define VCHAT_AUTOSTQART
#endif

//#define YOSHIHARA_VCHAT_ONOFFTEST


// ヒープ領域の最大使用量を監視する場合定義
#define CHEAK_HEAPSPACE

// デバッグ出力を大量に吐き出す場合定義
//#define DEBUGPRINT_ON

#ifdef DEBUGPRINT_ON
#define MYDWC_DEBUGPRINT(...) \
    (void) ((OS_TPrintf(__VA_ARGS__)))
#else
#define MYDWC_DEBUGPRINT(...)           ((void) 0)
#endif



// テスト用サーバに繋ぐときに定義
//#define USE_AUTHSERVER_DEVELOP

// フレンドリストのサイズ
#define FRIENDLIST_MAXSIZE 32

// １フレームに何人分のデータを更新するか。
#define FRIENDINFO_UPDATA_PERFRAME 4

// WiFiで使うHeapのサイズ(128Kバイト、仮）+7000
#define MYDWC_HEAPSIZE (0x2B000)

#define MYDWC_HEAPID HEAPID_WIFIMENU

// この辺はテスト用。正式に割り当てられたら、指定する。
#define GAME_NAME        "pokemondpds"  // 使用するゲーム名
#define GAME_SECRET_KEY  "1vTlwb"  // 使用するシークレットキー
#define GAME_PRODUCTID   10727         // 使用するプロダクトID

#define SIZE_RECV_BUFFER (4 * 1024)
#define SIZE_SEND_BUFFER 256

typedef struct
{
	u8 recvBuffer[ SIZE_RECV_BUFFER ];
	u8 sendBuffer[ SIZE_SEND_BUFFER ];
	DWCFriendData *keyList;  // DWC形式の友達リスト	
	DWCFriendsMatchControl stDwcCnt;    // DWC制御構造体	
    DWCUserData *myUserData;		// DWCのユーザデータ（自分のデータ）
	DWCInetControl stConnCtrl;
    SAVEDATA* pSaveData;   // 2006.04.07 k.ohno  セーブデータを保持
	
	void *heapPtr;
	NNSFndHeapHandle headHandle;

	MYDWCReceiverFunc serverCallback;
	MYDWCReceiverFunc clientCallback;
	
	void (*fetalErrorCallback)(int);
	
	u8 friend_status[FRIENDLIST_MAXSIZE];
	void *friendinfo;	
	int infosize;	
	u32 friendupdate_index;	
	
	int state;
	int matching_type;
	
	int sendbufflag;
	
	int op_aid;			// 相手のaid
	
	int heapID;
	
	int isvchat;
	int friendindex;
	BOOL newFriendConnect;  // 接続してきたらTRUE 2006.05.24 k.ohno
    BOOL bDelay;     // 遅延テスト
    BOOL bVChat;     // VCHATONOFFテスト
	
	int vchatcodec;
	
	int timeoutflag;
	
	int sendintervaltime;		// 前回データを送信してからのフレーム数。
	
	int myvchaton;				// 自分のボイスチャットがオンかオフか
	int opvchaton;				// 相手のボイスチャットがオンかオフか
	
	u8 myseqno;				// 自分が送信するパケットのシーケンスNo
	u8 opseqno;				// 相手が最後に送ってきたパケットのシーケンスNo
    u8 bHeapError;  // HEAP確保失敗の場合
	
	u16 firstflag;
	
	// テスト用
	int s_param;
} MYDWC_WORK;

// ボイスチャットのトークンと混合しないようにするため、
// ボイスチャットと違う３２バイトの数字をパケットの先頭につける。
#define MYDWC_PACKETYPE_MASK 0x000000ff
#define MYDWC_PACKET_VCHAT_MASK 0x00000100
#define MYDWC_PACKET_VCHAT_SHIFT 8
#define MYDWC_PACKET_SEQNO_POS 2

#define MYDWC_GAME_PACKET 0x0001

// タイムアウト処理を防ぐため、一定時間送信がない場合、
// からのデータを送る。そのときの数字
#define MYDWC_KEEPALIVE_PACKET 0x0002

enum{
	MDSTATE_INIT,	
	MDSTATE_CONNECTING,
	MDSTATE_CONNECTED,
	MDSTATE_TRYLOGIN,
	MDSTATE_LOGIN,
	
	MDSTATE_MATCHING,
	MDSTATE_CANCEL,	
	MDSTATE_MATCHED,	
	MDSTATE_CANCELFINISH,	
	
	MDSTATE_FAIL,			// 2006.7.4 yoshihara追加
	MDSTATE_FAILFINISH,	
	
	MDSTATE_ERROR,
	MDSTATE_ERROR_FM,
	MDSTATE_ERROR_DISCONNECT,
	MDSTATE_ERROR_FETAL,
	
	MDSTATE_DISCONNECTTING,	
	MDSTATE_DISCONNECT,	
	
	MDSTATE_TIMEOUT,
	
	MDSTATE_LAST
};

enum {
	MDTYPE_RANDOM,
	MDTYPE_PARENT,
	MDTYPE_CHILD
};
	

void *_dWork_temp = NULL;
static MYDWC_WORK *_dWork = NULL;


static void LoginCallback(DWCError error, int profileID, void *param);
static void UpdateServersCallback(DWCError error, BOOL isChanged, void* param);
static void FriendStatusCallback(int index, u8 status, const char* statusString, void* param);
static void DeleteFriendListCallback(int deletedIndex, int srcIndex, void* param);
static void BuddyFriendCallback(int index, void* param);

static void ConnectToAnybodyCallback(DWCError error, BOOL cancel, void* param);
static void SendDoneCallback( int size, u8 aid );
static void UserRecvCallback( u8 aid, u8* buffer, int size );
static void ConnectionClosedCallback(DWCError error, BOOL isLocal, BOOL isServer, u8  aid, int index, void* param);
//static int handleError();
static int EvaluateAnybodyCallback(int index, void* param);

static void recvTimeoutCallback(u8 aid);

static void mydwc_updateFriendInfo( );

#ifdef _WIFI_DEBUG_TUUSHIN

#define _USER_PARAM_MAGIC (55)

static void _NNSFndHeapVisitor(void* memBlock, NNSFndHeapHandle heap, u32 userParam)
{
    if(userParam == _USER_PARAM_MAGIC){
        GF_ASSERT(NNS_FndCheckExpHeap(heap, NNS_FND_HEAP_ERROR_PRINT));
        GF_ASSERT(NNS_FndCheckForMBlockExpHeap(memBlock, heap, NNS_FND_HEAP_ERROR_PRINT));
    }
}

#endif


//==============================================================================
/**
 * インターネットへ接続開始
 * @param   userdata 自分のログインデータへのポインタ
 * @param   list フレンドリストの先頭ポインタ
 * @retval  MYDWC_STARTCONNECT_OK … OK
 * @retval  MYDWC_STARTCONNECT_FIRST … 初めて接続する場合。（メッセージ表示の必要有
 * @retval  MYDWC_STARTCONNECT_DIFFERENTDS … 異なるＤＳで接続しようしてる場合。（要警告）
 */
//==============================================================================
int mydwc_startConnect(SAVEDATA* pSaveData, int heapID)
{
    // ヒープ領域からワーク領域を確保。
	GF_ASSERT( _dWork_temp == NULL );
#ifdef _WIFI_DEBUG_TUUSHIN
#ifdef DEBUGPRINT_ON
	DWC_SetReportLevel(DWC_REPORTFLAG_ALL);
#endif
#endif
    
    OS_TPrintf("dwcrasp   %d \n",sizeof(MYDWC_WORK) + 32);
    
	_dWork_temp = sys_AllocMemory(heapID, sizeof(MYDWC_WORK) + 32);
	_dWork = (MYDWC_WORK *)( ((u32)_dWork_temp + 31) / 32 * 32 );
    // 2006.04.07 k.ohno セーブデータポインタを保持
    _dWork->pSaveData = pSaveData;
	_dWork->serverCallback = NULL;
	_dWork->clientCallback = NULL;	
	_dWork->fetalErrorCallback = NULL;
	_dWork->state = MDSTATE_INIT;
	_dWork->heapID = heapID;
	_dWork->heapPtr = sys_AllocMemory(heapID, MYDWC_HEAPSIZE + 32);
	_dWork->headHandle = NNS_FndCreateExpHeap( (void *)( ((u32)_dWork->heapPtr + 31) / 32 * 32 ), MYDWC_HEAPSIZE);
	_dWork->vchatcodec = VCHAT_NONE;
	_dWork->friendindex = -1;
	_dWork->friendupdate_index = 0;
    _dWork->op_aid = -1;
    _dWork->newFriendConnect = -1;
    _dWork->bDelay = FALSE;
    _dWork->bVChat = TRUE;
    _dWork->bHeapError = FALSE;
    
    // 2006.7.22 yoshihara ここで、Seqnoをセット
    _dWork->myseqno = 0;
    _dWork->opseqno = 0;
    _dWork->myvchaton = 1;
    _dWork->opvchaton = 1;
    
    // 2006.04.07 k.ohno 引数変更 セーブデータから得る
    if(pSaveData!=NULL){
        _dWork->myUserData = WifiList_GetMyUserInfo(SaveData_GetWifiListData(_dWork->pSaveData));
        _dWork->keyList = (DWCFriendData*)WifiList_GetDwcDataPtr(SaveData_GetWifiListData(_dWork->pSaveData),0);
    }

#ifdef PM_DEBUG
    DWC_ReportUserData(_dWork->myUserData);
#endif

#ifdef DEBUG_ONLY_FOR_ohno
   if( !DWC_CheckUserData( _dWork->myUserData ) ){
       GF_ASSERT(0);  //修正確認のため入れてあるk.ohno
   }
#endif

	_dWork->friendinfo = NULL;
	{
		int i;
		for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
		{
			_dWork->friend_status[i] = DWC_STATUS_OFFLINE;
		}
	}
	

	// ユーザデータの状態をチェック。
	mydwc_showFriendInfo();	
	

	if( !DWC_CheckHasProfile( _dWork->myUserData ) ) 
	{
		// まだこのデータで一度もＷｉＦｉに繋いでいない。
		return MYDWC_STARTCONNECT_FIRST;
	}
	
	if( !DWC_CheckValidConsole( _dWork->myUserData ) )
	{
		// 本体情報が違う→違うＤＳで接続しようとしている。
		return 	MYDWC_STARTCONNECT_DIFFERENTDS;
	}
	


	return MYDWC_STARTCONNECT_OK;
}

//==============================================================================
/**
 * dwc_rap.cが確保した領域を開放する。
 * @param   none
 * @retval  none
 */
//==============================================================================
void mydwc_free()
{
    if(_dWork){

        NNS_FndDestroyExpHeap( _dWork->headHandle );
        sys_FreeMemory( _dWork->heapID, _dWork->heapPtr  );
        sys_FreeMemory( _dWork->heapID, _dWork_temp  );
        _dWork_temp = NULL;
        _dWork = NULL;
        OS_TPrintf("dwcrap終了\n");
    }
	DWC_ClearError();
}

//==============================================================================
/**
 * インターネット接続中に毎フレーム呼び出される関数
 * @param   userdata 自分のログインデータへのポインタ
 * @param   list フレンドリストの先頭ポインタ
 * @retval  正…接続完了。０…接続中。負…エラー（エラーコードが返る）
 */
//==============================================================================
int mydwc_connect()
{

    switch( _dWork->state )
	{
		case MDSTATE_INIT:
		// 初期状態
		{
		    // メモリ確保関数設定
		    DWC_SetMemFunc( mydwc_AllocFunc, mydwc_FreeFunc );
		    
		    // ネット接続初期化
            DWC_InitInetEx(&_dWork->stConnCtrl,COMM_DMA_NO,COMM_POWERMODE,COMM_SSL_PRIORITY);
		    
#if defined( USE_AUTHSERVER_DEVELOP )
		    DWC_SetAuthServer(DWC_CONNECTINET_AUTH_TEST);
#else
		    DWC_SetAuthServer(DWC_CONNECTINET_AUTH_RELEASE);
#endif
			
			// 非同期にネットに接続
			DWC_ConnectInetAsync();
			
			_dWork->state = MDSTATE_CONNECTING;
			_dWork->isvchat = 0;
		}
		
		case MDSTATE_CONNECTING:
		{
			// 安定した状況になるまで待つ。
			if( DWC_CheckInet() )
			{
				if( DWC_GetInetStatus() == DWC_CONNECTINET_STATE_CONNECTED )
				{
					_dWork->state = MDSTATE_CONNECTED;
				}
				else
				{
					_dWork->state = MDSTATE_ERROR;
				}
			}
			else
			{
				// 自動接続処理中
		        DWC_ProcessInet();
  
				break;	
			}
		}
		
		case MDSTATE_CONNECTED:
			// エラーがおこっていないか判定
			{
				int ret = mydwc_HandleError();
				if( ret < 0 ) return ret;
			}
			// ログインへ
			// とりあえず、友達リストは初期状態にしておく。   k.ohno 4.16修正
//			MI_CpuClear32( &(_dWork->keyList[0]), sizeof(_dWork->keyList) );

			// フレンドライブラリ初期化
		    DWC_InitFriendsMatch(&(_dWork->stDwcCnt), (_dWork->myUserData), 
		    			 GAME_PRODUCTID, GAME_NAME,
                         GAME_SECRET_KEY, 0, 0,
                         _dWork->keyList, FRIENDLIST_MAXSIZE);

            // とりあえず、IPLのユーザ名を使ってログイン
		    {
		    	// 自分のユーザ名を圧縮。
				OSOwnerInfo info;
				OS_GetOwnerInfo( &info );
			    DWC_LoginAsync( &(info.nickName[0]), NULL, LoginCallback, NULL);       
		    }
		    _dWork->state = MDSTATE_TRYLOGIN;
		
		case MDSTATE_TRYLOGIN:
			// ログインが完了するまで待つ。
			DWC_ProcessFriendsMatch();
			break;
			
		case MDSTATE_LOGIN:
            DWC_ProcessFriendsMatch();   // 2006.04.07 k.ohno ログインしただけの状態を持続する為
			return 1;
	}
	return mydwc_HandleError();	
}

//==============================================================================
/**
 * 受信したときのコールバックを設定する関数
 * @param client … クライアントとしてのコールバック関数
 * @param server … サーバとしてのコールバック関数
 * @retval  none
 */
//==============================================================================
void mydwc_setReceiver( MYDWCReceiverFunc server, MYDWCReceiverFunc client )
{
	_dWork->serverCallback = server;
	_dWork->clientCallback = client;	
}

//==============================================================================
/**
 * ランダム対戦を行う関数。ランダムマッチ中は数十フレーム処理が返ってこないことがある。
 * @retval  正…成功。０…失敗。
 */
//==============================================================================
static char randommatch_query[] = "gn = 'pe'";
int mydwc_startmatch( )
{
	if( _dWork->state != MDSTATE_LOGIN ) return 0;

    (void)DWC_AddMatchKeyString(0,"gn","pe");
                              
    _dWork->state = MDSTATE_MATCHING;
    DWC_ConnectToAnybodyAsync
    (
    	2,
        randommatch_query,
        ConnectToAnybodyCallback,
        NULL,
        EvaluateAnybodyCallback,
        NULL
    );
	_dWork->matching_type = MDTYPE_RANDOM;
    // 送信コールバックの設定	
    DWC_SetUserSendCallback( SendDoneCallback ); 

    // 受信コールバックの設定	
    DWC_SetUserRecvCallback( UserRecvCallback ); 
    
    // コネクションクローズコールバックを設定
    DWC_SetConnectionClosedCallback(ConnectionClosedCallback, NULL);
    
    // タイムアウトコールバックの設定
    DWC_SetUserRecvTimeoutCallback( recvTimeoutCallback );
    
    _dWork->sendbufflag = 0;
    
	// テスト用
	_dWork->s_param = 0;    
    
    return 1;    
}

// 2006.7.4 yoshihara 追加
static void finishcancel()
{
    if( _dWork->state == MDSTATE_FAIL ){
		_dWork->state = MDSTATE_FAILFINISH;
    }
    else
    {
		_dWork->state = MDSTATE_CANCELFINISH;
    }	
}

//==============================================================================
/**
 * ランダム対戦マッチング中に毎フレーム呼ばれる関数。
 * @retval  
 	STEPMATCH_CONTINUE…マッチング中
 	STEPMATCH_SUCCESS…成功
 	STEPMATCH_CANCEL…キャンセル
 	STEPMATCH_FAIL  …相手が親をやめたため、接続を中断
 	負…エラー発生
 */
//==============================================================================
int mydwc_stepmatch( int isCancel )
{
	switch ( _dWork->state )
	{
		case MDSTATE_MATCHING:
			// 現在探索中
			if( isCancel ) 
			{
				_dWork->state = MDSTATE_CANCEL;
			}
			// 2006.7.4 yoshihara修正 ここから
			// 子機の場合、つなぎにいってる親が現在もサーバモードかどうかチェックする。
			if( _dWork->matching_type == MDTYPE_CHILD )
			{
				if( _dWork->friendindex >= 0 ) // このifは念のため
				{
					if( _dWork->friend_status[_dWork->friendindex] != DWC_STATUS_MATCH_SC_SV )
					{
						OS_TPrintf("相手がサーバをやめてしまったので、キャンセルします。\n");
						// 既に親でなくなってしまっている。キャンセルへ移項
						_dWork->state = MDSTATE_FAIL;	
					}
				}
			}
			// 2006.7.4 yoshihara修正 ここまで
			
			break;
			
      case MDSTATE_CANCEL:
      case MDSTATE_FAIL:      
			if( _dWork->state == MDTYPE_RANDOM)
			{
				// ランダムマッチ
				// キャンセル処理中
				if( !DWC_CancelMatching() )
				{
				}
				break;
			} else {
				int ret;
				ret = DWC_CloseAllConnectionsHard();
				if( ret == 1 )
				{
					// 子機がいない→コールバック無しで終了
		            // 2006.7.4 yoshihara 修正
					finishcancel();	
				}
				else if (ret == 0)
				{
					// コールバックが帰ってきているはず
				}
				else
				{
		            // 2006.7.4 yoshihara 修正
					finishcancel();	
//					MYDWC_DEBUGPRINT("Now unable to disconnect.\n");
				}
			}
        break;    //@@OO   06.05.12追加
		case MDSTATE_MATCHED:
			// 完了。
			{
				_dWork->firstflag = 1;
#ifdef VCHAT_AUTOSTQART
			// yoshihara変更　06.6.15
//                if(_dWork->bVChat){
                    mydwc_startvchat();
//                }

                if(_dWork->bVChat)
                {
	                _dWork->myvchaton = 1;
                }
                else{
	                _dWork->myvchaton = 0;
                }

#else
				if( _dWork->vchatcodec != VCHAT_NONE ) mydwc_startvchat();
#endif
				return STEPMATCH_SUCCESS;	
			}
			break;
		case MDSTATE_CANCELFINISH:
			// ログイン直後の状態に
			_dWork->state = MDSTATE_LOGIN;
			_dWork->sendbufflag = 0;
            _dWork->newFriendConnect = -1;
            OS_TPrintf("キャンセル処理完了\n");
			return STEPMATCH_CANCEL;
		case MDSTATE_FAILFINISH:
			// ログイン直後の状態に
			_dWork->state = MDSTATE_LOGIN;
			_dWork->sendbufflag = 0;
            _dWork->newFriendConnect = -1;
            OS_TPrintf("フィニッシュ処理完了\n");
			return STEPMATCH_FAIL;			
		case MDSTATE_ERROR:
			{
				int ret;
				
				ret = mydwc_HandleError();
				return ret;
			}	
			
		default:
			break;		
//			return handleError();
	}
	return mydwc_step();	
		
//    DWC_ProcessFriendsMatch();  // DWC通信処理更新			
//	return handleError();
}



//==============================================================================
/**
 * サーバにデータ送信を行うことができるか
 * @retval  1 - 成功　 0 - 失敗（送信バッファが詰まっている等）
 */
//==============================================================================
BOOL mydwc_canSendToServer()
{
	return ( DWC_GetMyAID() == 0 || ( _dWork->sendbufflag == 0 && DWC_IsSendableReliable( 0 ) ) );
}

//==============================================================================
/**
 * クライアントにデータ送信を行うことができるか
 * @retval  1 - 成功　 0 - 失敗（送信バッファが詰まっている等）
 */
//==============================================================================
BOOL mydwc_canSendToClient()
{
	return ( _dWork->sendbufflag == 0 && DWC_IsSendableReliable( 1 ) );
}

//==============================================================================
/**
 * サーバにデータ送信を行う関数
 * @param   data - 送信するデータへのポインタ。size - 送信するデータのサイズ
 * @retval  1 - 成功　 0 - 失敗（送信バッファが詰まっている等）
 */
//==============================================================================
int mydwc_sendToServer(void *data, int size)
{
    if( !(size < SIZE_SEND_BUFFER) ){
        return 0;
    }

    
	MYDWC_DEBUGPRINT("mydwc_sendToServer(data=%d)\n", *((u32*)data));

	if( DWC_GetMyAID() == 0 )
	{
		// 自分が親
		// コールバック内で書き換えられる可能性を考え、dataをコピーしておく。
//		void *buf = mydwc_AllocFunc( NULL, size, 32 );
//		MI_CpuCopy8	( data, buf, size );
		
		// 自分自身のサーバ受信コールバックを呼び出す。
		if( _dWork->serverCallback != NULL ) _dWork->serverCallback(0, data, size);
		
		// コールバックを呼び出したらすぐに開放。
//		mydwc_FreeFunc( NULL, buf, size );
		
		return 1;
	}
	else
	{
		// 相手が親。相手に対してデータ送信。
		if( _dWork->sendbufflag || !DWC_IsSendableReliable( 0 ) ) // 送信バッファをチェック。
		{
			// 送信バッファがいっぱいなどで送れない。
			return 0;
		}
		
		// 送信バッファにコピー
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_GAME_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);
		_dWork->sendBuffer[MYDWC_PACKET_SEQNO_POS] = ++_dWork->myseqno;
		MI_CpuCopy8( data, &(_dWork->sendBuffer[4]), size );
		_dWork->sendbufflag = 1;
		
		// 親機に向けて送信
		DWC_SendReliable( 0, &(_dWork->sendBuffer[0]), size + 4);
//		OS_TPrintf("-");
		return 1;
	}
}

//==============================================================================
/**
 * 親機が子機にデータ送信を行う関数
 * @param   data - 送信するデータへのポインタ。size - 送信するデータのサイズ
 * @retval  1 - 成功　 0 - 失敗（送信バッファが詰まっている等）
 */
//==============================================================================
int mydwc_sendToClient(void *data, int size)
{
    if( !(size < SIZE_SEND_BUFFER) ){
        return 0;
    }
	// 親機しかこの動作は行わないはず。
    if( !(DWC_GetMyAID() == 0) ){
        return 0;
    }
	
	MYDWC_DEBUGPRINT("sendToClient(data=%d)\n", *((u32*)data));
	
	{
		// 相手に対してデータ送信。
		if( _dWork->sendbufflag || !DWC_IsSendableReliable( 1 ) ) // 送信バッファをチェック。
		{
            OS_TPrintf("wifi failed %d\n",size);
			// 送信バッファがいっぱいなどで送れない。
			return 0;
		}
		
		// 送信バッファにコピー
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_GAME_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);
		_dWork->sendBuffer[MYDWC_PACKET_SEQNO_POS] = ++_dWork->myseqno;
		MI_CpuCopy8( data, &(_dWork->sendBuffer[4]), size );
        _dWork->sendbufflag = 1;
		
		// 子機に向けて送信
        if(!DWC_SendReliable( 1, &(_dWork->sendBuffer[0]), size + 4)){
            OS_TPrintf("wifi failed %d\n",size);
			// 送信バッファがいっぱいなどで送れない。
            _dWork->sendbufflag = 0;
            return 0;
        }
//		OS_TPrintf("-");
	}	
	
	{
		// 自分に対して送信
//		// コールバック内で書き換えられる可能性を考え、dataをコピーしておく。
//		void *buf = mydwc_AllocFunc( NULL, size, 32 );
//		MI_CpuCopy8	( data, buf, size );
		
		// 自分自身のサーバ受信コールバックを呼び出す。
		if( _dWork->clientCallback != NULL ) _dWork->clientCallback(0, data, size);
		
		// コールバックを呼び出したらすぐに開放。
//		mydwc_FreeFunc( NULL, buf, size );
	}  
	
	return 1;
}
/*---------------------------------------------------------------------------*
  ログインコールバック関数
 *---------------------------------------------------------------------------*/
static void LoginCallback(DWCError error, int profileID, void *param)
{
    BOOL result;

    // stUserDataが更新されているかどうかを確認。
    if ( DWC_CheckDirtyFlag( (_dWork->myUserData)) )
    {
	    // 必ずこのタイミングでチェックして、dirty flagが有効になっていたら、
	    // DWCUserDataをDSカードのバックアップに保存するようにしてください。
	    // 2006.04.07 k.ohno  セーブエリアに入れる
	    DWCUserData *userdata = NULL;
	    DWC_ClearDirtyFlag(_dWork->myUserData);
	    SaveData_SaveParts(_dWork->pSaveData, SVBLK_ID_NORMAL);  //セーブ中 k.ohno 06.06.05
	    
	//          userdata = WifiList_GetMyUserInfo(SaveData_GetWifiListData(_dWork->pSaveData));
	//          MI_CpuCopy32( &_dWork->myUserData, userdata,  sizeof(_dWork->myUserData) );	
	    OS_TPrintf("自分のフレンドコードが変更\n");
    }

    if (error == DWC_ERROR_NONE){
        // 認証成功、プロファイルID取得


       
        result = DWC_UpdateServersAsync(NULL, //（過去との互換性のため、必ずNULL)
                                        UpdateServersCallback, _dWork->myUserData,
                                        FriendStatusCallback, param,
                                        DeleteFriendListCallback, param);

        if (result == FALSE){
            // 呼んでもいい状態（ログインが完了していない状態）で呼んだ時のみ
            // FALSEが返ってくるので、普通はTRUE
            OS_TPrintf("DWC_UpdateServersAsync error teminated.\n");
            CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
            return;
        }

        // GameSpyサーバ上バディ成立コールバックを登録する
        DWC_SetBuddyFriendCallback(BuddyFriendCallback, NULL);
        
    }
    else
    {
        // 認証失敗
		_dWork->state = MDSTATE_ERROR;
    }
}

/*---------------------------------------------------------------------------*
  タイムアウトコールバック関数
 *---------------------------------------------------------------------------*/
static void recvTimeoutCallback(u8 aid)
{
	OS_TPrintf("タイムアウト - ");
	// コネクションを閉じる
	if( _dWork->timeoutflag )
	{
		OS_TPrintf("接続を切断します\n");
		DWC_CloseAllConnectionsHard( );
        _dWork->newFriendConnect = -1;
		// タイムアウト
		_dWork->state = MDSTATE_TIMEOUT;	
	}
}

/*---------------------------------------------------------------------------*
  GameSpyサーバアップデートコールバック関数
 *---------------------------------------------------------------------------*/
static void UpdateServersCallback(DWCError error, BOOL isChanged, void* param)
{
#pragma unused(param)
    if (error == DWC_ERROR_NONE){
        if (isChanged){
            // 友達リストが変更されていた
        }
       	_dWork->state = MDSTATE_LOGIN;		// ログイン完了  
    }
    else {
        // ログイン失敗扱いにしとく？
        _dWork->state = MDSTATE_ERROR;
    }
}


/*---------------------------------------------------------------------------*
  友達状態変化通知コールバック関数
 *---------------------------------------------------------------------------*/
static void FriendStatusCallback(int index, u8 status, const char* statusString, void* param)
{
#pragma unused(param)

    MYDWC_DEBUGPRINT("Friend[%d] changed status -> %d (statusString : %s).\n",
               index, status, statusString);
            
}


/*---------------------------------------------------------------------------*
  友達リスト削除コールバック関数
 *---------------------------------------------------------------------------*/
static void DeleteFriendListCallback(int deletedIndex, int srcIndex, void* param)
{
#pragma unused(param)
	// フレンドリストが削除された。
	
    MYDWC_DEBUGPRINT("friend[%d] was deleted (equal friend[%d]).\n",
               deletedIndex, srcIndex);

    OS_TPrintf("friend[%d] was deleted (equal friend[%d]).\n",
               deletedIndex, srcIndex);
    // 書き戻し
    MI_CpuCopy8(_dWork->keyList,WifiList_GetDwcDataPtr(SaveData_GetWifiListData(_dWork->pSaveData), 0),FRIENDLIST_MAXSIZE * sizeof(DWCFriendData));
    WifiList_DataMarge(SaveData_GetWifiListData(_dWork->pSaveData),
                       deletedIndex, srcIndex);

}


/*---------------------------------------------------------------------------*
  GameSpyバディ成立コールバック関数
 *---------------------------------------------------------------------------*/
static void BuddyFriendCallback(int index, void* param)
{
#pragma unused(param)

    MYDWC_DEBUGPRINT("I was authorized by friend[%d].\n", index);
}

static void setConnectionBuffer()
{
	_dWork->state = MDSTATE_MATCHED;
    // 受信バッファセット  // 二人対戦と決めうち
    if( DWC_GetMyAID() == 0 )
    {
        _dWork->op_aid = 1;
    } 
    else
    {
    	_dWork->op_aid = 0;
	}   
    DWC_SetRecvBuffer( _dWork->op_aid, &(_dWork->recvBuffer[0]), SIZE_RECV_BUFFER );	
   	DWC_SetRecvTimeoutTime( _dWork->op_aid, MYDWC_TIMEOUTSEC * 1000 );
	_dWork->timeoutflag = 0;
	_dWork->sendintervaltime = 0;

#ifdef PM_DEBUG  // デバッグ遅延
    if(_dWork->bDelay){
        DWC_SetRecvDelay( 1000, _dWork->op_aid );
    }
    else{
        DWC_SetRecvDelay( 0, _dWork->op_aid );
    }
#endif
}

/*---------------------------------------------------------------------------*
  友達無指定接続コールバック関数
 *---------------------------------------------------------------------------*/
static void ConnectToAnybodyCallback(DWCError error, BOOL cancel, void* param)
{
#pragma unused(param)
    if (error == DWC_ERROR_NONE){
        if (!cancel){
            // 見知らぬ人たちとのコネクション設立完了
            MYDWC_DEBUGPRINT("接続完了\n\n");
            setConnectionBuffer();
        }
        else {
            MYDWC_DEBUGPRINT("キャンセル完了\n");
            // ログイン後状態に戻る
            
            // 2006.7.4 yoshihara 修正
			finishcancel();	
        }
    }
    else {
        MYDWC_DEBUGPRINT("マッチング中にエラーが発生しました。 %d\n\n", error);
		_dWork->state = MDSTATE_ERROR; 
    }
}

/*---------------------------------------------------------------------------*
  友達無指定マッチング時プレイヤー評価コールバック関数
 *---------------------------------------------------------------------------*/
static int  EvaluateAnybodyCallback(int index, void* param)
{
#pragma unused(param, index)
	return 1;
}


/** -------------------------------------------------------------------------
  送信完了コールバック  
  ---------------------------------------------------------------------------*/
static void SendDoneCallback( int size, u8 aid )
{
#pragma unused(size)
	// 送信バッファをあける
	_dWork->sendbufflag = 0;
	_dWork->sendintervaltime = 0;
//	MYDWC_DEBUGPRINT( "送信\n" );
//	OS_TPrintf( "*" );
}

/** -------------------------------------------------------------------------
  受信完了コールバック  
  ---------------------------------------------------------------------------*/
static void UserRecvCallback( u8 aid, u8* buffer, int size )
{
#pragma unused( aid, buffer, size )

//	OS_TPrintf("[%d,%d,%d,%d]", buffer[0], buffer[1], buffer[2], buffer[3]);

	u32 topcode;
	topcode = (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0];

	// 一度受信してはじめてタイムアウトを設定する。
	_dWork->timeoutflag = 1;

	// まず、先頭の４バイトをみて、ゲームの情報かどうかを判断
	if( (topcode & MYDWC_PACKETYPE_MASK) == MYDWC_GAME_PACKET ){
		if( topcode & MYDWC_PACKET_VCHAT_MASK ) 
		{
			// 相手のボイスチャットはオン
			_dWork->opvchaton = 1;		
		}
		else
		{
			// 相手のボイスチャットはオン
			_dWork->opvchaton = 0;		
		}
		
		// 2006.7.22 yoshihara追加。相手のシーケンスNoが飛び飛びになっていないか確認
        // 結果通信途中では検出できなかったのでコメントに変更 7.28 k.ohno
//		GF_ASSERT( _dWork->firstflag == 1 || buffer[MYDWC_PACKET_SEQNO_POS] == (u8)( _dWork->opseqno + 1 ) );
        _dWork->firstflag = 0;
		_dWork->opseqno = buffer[MYDWC_PACKET_SEQNO_POS];
		
		
	}
	else {
#ifdef MYDWC_USEVCHA		
		if( myvct_checkData( aid, buffer,size ) ) return;
#endif	
		// 無意味な情報（コネクションを保持するためのものと思われる）
		if( topcode & MYDWC_PACKET_VCHAT_MASK ) 
		{
			// 相手のボイスチャットはオン
			_dWork->opvchaton = 1;		
		}
		else
		{
			// 相手のボイスチャットはオン
			_dWork->opvchaton = 0;		
		}		
		return;
	}
	MYDWC_DEBUGPRINT( "受信(%d)\n",*((s32*)buffer) );
	_dWork->s_param = *((s32*)buffer);
	
	// アライメントを確実にするために、コピー
	{
		u16 *temp = (u16*)mydwc_AllocFunc( NULL, size - 4, 4);
        if(temp==NULL){
            return;
        }
        
		MI_CpuCopy8(buffer + 4, (void*)temp, size - 4);
		
		if( DWC_GetMyAID() == 0 )
		{	
			// 自分が親の場合…クライントからサーバに対して送られてきたものと判断。
			// サーバ用受信関数を呼び出す。
			if( _dWork->serverCallback != NULL ) _dWork->serverCallback(aid, temp, size-4);
		} else {
			// サーバからクライアントに対して送られてきたものと判断。	
			if( _dWork->clientCallback != NULL ) _dWork->clientCallback(aid, temp, size-4);
		}
		
		mydwc_FreeFunc(NULL, temp, size - 4);
	}
}

/*---------------------------------------------------------------------------*
  コネクションクローズコールバック関数
 *---------------------------------------------------------------------------*/
static void ConnectionClosedCallback(DWCError error,
                                     BOOL isLocal,
                                     BOOL isServer,
                                     u8  aid,
                                     int index,
                                     void* param)
{
#pragma unused(param, index)
    if (error == DWC_ERROR_NONE){

        if (!isLocal && isServer){
//            // サーバクライアント型マッチングで、自分がクライアントの時に、
//            // サーバがコネクションをクローズした。
        }
        
        if (DWC_GetNumConnectionHost() == 1){
            // 全てのコネクションがクローズされた場合         
          
            // キャンセル中ならば、キャンセルが完了した。
			if(	_dWork->state == MDSTATE_CANCEL )
			{
				_dWork->state = MDSTATE_CANCELFINISH;
			}
			else {
				_dWork->state = MDSTATE_DISCONNECT;
			}
			
			if( _dWork->isvchat )
			{
				// まだボイスチャットライブラリを解放していない場合。
				myvct_free();
			}
			
        }
        
        if (isLocal){
            MYDWC_DEBUGPRINT("Closed connection to aid %d (friendListIndex = %d) Rest %d.\n",
                       aid, index, DWC_GetNumConnectionHost());
        }
        else {
            MYDWC_DEBUGPRINT("Connection to aid %d (friendListIndex = %d) was closed. Rest %d.\n",
                       aid, index, DWC_GetNumConnectionHost());
        }
    }
    else {
        OS_TPrintf("Failed to close connections. %d\n\n", error);
    }
}

#ifdef CHEAK_HEAPSPACE
static int _heapspace = MYDWC_HEAPSIZE;
static int _heapmaxspace = MYDWC_HEAPSIZE;
#endif

/*---------------------------------------------------------------------------*
  メモリ確保関数
 *---------------------------------------------------------------------------*/
void*
mydwc_AllocFunc( DWCAllocType name, u32   size, int align )
{
#pragma unused( name )
    void * ptr;
    OSIntrMode old;

#ifdef _WIFI_DEBUG_TUUSHIN
#ifdef DEBUGPRINT_ON
    OS_TPrintf("HEAP取得(%d, %d) from %p %x\n", size, align, _dWork->headHandle, _dWork->headHandle->signature);
#endif
#endif
    
    old = OS_DisableInterrupts();
    ptr = NNS_FndAllocFromExpHeapEx( _dWork->headHandle, size, align );

    if(ptr == NULL){
#ifdef _WIFI_DEBUG_TUUSHIN
//        GF_ASSERT_MSG(ptr,"HEAP faqiled");
#endif
        // ヒープが無い場合の修正
        CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);  // エラーにする
        OS_RestoreInterrupts( old );
        return NULL;//sys_AllocMemory(HEAPID_COMMUNICATION,size);  // ニセモノをつかませARM9どまりを発生させない
    }

    
#ifdef CHEAK_HEAPSPACE
#ifdef _WIFI_DEBUG_TUUSHIN
    {
		int hspace = NNS_FndGetTotalFreeSizeForExpHeap( _dWork->headHandle );
		if( hspace < _heapspace )
		{
			OS_TPrintf("ヒープ残り：%d\n", hspace);
			_heapspace = hspace;
		}
	}
	{
		int maxspace = NNS_FndGetAllocatableSizeForExpHeap( _dWork->headHandle );
		if( maxspace < _heapmaxspace )
		{
			OS_TPrintf("ヒープ残り：%d\n", maxspace);
			_heapmaxspace = maxspace;
		}		
	}
#endif	
#endif	
    OS_RestoreInterrupts( old );
#ifdef DEBUGPRINT_ON
//	OS_TPrintf("dwc_rap:ヒープ取得（size = %d）：残り%d\n", size, NNS_FndGetTotalFreeSizeForExpHeap( _dWork->headHandle ) );
#endif
    return ptr;
}

/*---------------------------------------------------------------------------*
  メモリ開放関数
 *---------------------------------------------------------------------------*/
void
mydwc_FreeFunc( DWCAllocType name, void* ptr,  u32 size  )
{
#pragma unused( name, size )
    OSIntrMode old;

    if ( !ptr ) return;
//    OS_TPrintf("HEAP解放(%p) to %p\n", ptr, _dWork->headHandle);    
    old = OS_DisableInterrupts();
    NNS_FndFreeToExpHeap( _dWork->headHandle, ptr );
    OS_RestoreInterrupts( old );
}

//==============================================================================
/**
 * エラーが起こっていないかチェックし、エラーに応じて通信処理を閉じる処理をする。
 *  世界交換、世界バトルタワーで呼び出すために多少改造 k.ohno 06.06.08
 * @retval  ０…エラーなし。負…エラー
 * （エラーコードが返る。エラーコード０の場合はERRORCODE_0）
 */
//==============================================================================
int mydwc_HandleError(void)
{
	int errorCode;
	DWCErrorType myErrorType;
	int ret;
	

#ifdef _WIFI_DEBUG_TUUSHIN
    if(_dWork){
        OSIntrMode old;
        // ヒープテスト
        old = OS_DisableInterrupts();
        NNS_FndVisitAllocatedForExpHeap(_dWork->headHandle, _NNSFndHeapVisitor, _USER_PARAM_MAGIC);
        OS_RestoreInterrupts( old );
    }
#endif

    ret = DWC_GetLastErrorEx( &errorCode, &myErrorType );

	if( ret != 0 )
	{
		// 何らかのエラーが発生。
		OS_TPrintf("error occured!(%d, %d, %d)\n", ret, errorCode, myErrorType); 	
		
		switch(myErrorType)
		{
			case DWC_ETYPE_LIGHT:
				// ゲーム固有の表示のみで、エラーコード表示は必要ない。
				// DWC_ClearError()を呼び出せば、復帰可能。
				DWC_ClearError();
                if(ret >= DWC_ERROR_FRIENDS_SHORTAGE) return ret; // 軽度のエラーはそのまま返す k.ohno
				if( errorCode == 0 ) return ERRORCODE_0;
				break;
			case DWC_ETYPE_SHUTDOWN_FM:
				// DWC_ShutdownFriendsMatch()を呼び出して、FriendsMatch処理を終了する必要がある。
				// エラーコードの表示が必要。
				// この場合、とりあえずDWC_ETYPE_DISCONNECTと同じ処理をしておく。
			case DWC_ETYPE_DISCONNECT:
				//FriendsMatch処理中ならDWC_ShutdownFriendsMatch()を呼び出し、
				//更にDWC_CleanupInet()で通信の切断も行う必要がある。
				//エラーコードの表示が必要。 
				if(_dWork){
					switch( _dWork->state )
					{			
						case MDSTATE_TRYLOGIN:
						case MDSTATE_LOGIN:		
						case MDSTATE_MATCHING:
						case MDSTATE_CANCEL:
						case MDSTATE_MATCHED:
						case MDSTATE_CANCELFINISH:
						case MDSTATE_ERROR:
						case MDSTATE_TIMEOUT:
						case MDSTATE_DISCONNECTTING:
						case MDSTATE_DISCONNECT:
							DWC_ShutdownFriendsMatch(  );
						case MDSTATE_INIT:	
						case MDSTATE_CONNECTING:
						case MDSTATE_CONNECTED:
							// まだこの時点では、フレンドマッチライブラリは呼ばれていない。
							DWC_CleanupInet( );
					}
					
					DWC_ClearError();
				}
				if(_dWork){
                    _dWork->state = MDSTATE_ERROR_DISCONNECT;
                }
				if( errorCode == 0 ) return ERRORCODE_0;
				return errorCode;
				
			case DWC_ETYPE_FATAL:
				// FatalError相当なので、電源OFFを促す必要がある。
				if(_dWork){
                    _dWork->state = MDSTATE_ERROR_FETAL;
				// このコールバックから処理がかえってこないはず。
                    if( _dWork->fetalErrorCallback != NULL ){
                        _dWork->fetalErrorCallback( -errorCode );
                    }
                }
				
				if( errorCode == 0 ) return ERRORCODE_0;
				return errorCode;
				break;
		}
	}

    if(_dWork->bHeapError){
        return ERRORCODE_HEAP;        
    }
	return 0;
}

static int _buffer;

static void _sendData(int param)
{
	_buffer = param;
	if( !DWC_IsSendableReliable( _dWork->op_aid ) ) // 送信バッファをチェック。
	{
		DWC_SendReliable( _dWork->op_aid, &(_buffer), 4 );
	}	
}

#ifdef YOSHIHARA_VCHAT_ONOFFTEST		

static u16 debug_trg;
static u16 debug_cont = 0;

static void vchat_onoff()
{
	{
	    u16 ReadData = PAD_Read();
	    debug_trg  = (u16)(ReadData & (ReadData ^ debug_cont));            // トリガ 入力
	    debug_cont = ReadData;      	
	}	
	
	if( debug_trg & PAD_BUTTON_R )
	{
		if( _dWork->myvchaton )
		{
			mydwc_VChatPause();
		}
		else
		{
			mydwc_VChatRestart();
		}
	}
}

#endif

static void sendKeepAlivePacket()
{
	
    OS_TPrintf("keep   %d %d\n",_dWork->sendbufflag,DWC_IsSendableReliable( 1-DWC_GetMyAID() ) );
    
	if( (_dWork->sendbufflag == 0) && DWC_IsSendableReliable( 1-DWC_GetMyAID() ) ) // 送信バッファをチェック。
	{
		_dWork->sendbufflag = 1;
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_KEEPALIVE_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);;
		DWC_SendReliable( _dWork->op_aid, &(_dWork->sendBuffer[0]), 4);
		_dWork->sendintervaltime = 0;
		OS_TPrintf("SEND KEEP ALIVE PACKET\n");	
	}	
}

// 通信確立後、毎フレーム呼び出してください。
//==============================================================================
/**
 * DWC通信処理更新を行う
 * @param none
 * @retval 0…正常, 負…エラー発生 1…タイムアウト 2…相手から切断された
 */
//==============================================================================
int mydwc_step()
{
	DWC_ProcessFriendsMatch();  // DWC通信処理更新
	mydwc_updateFriendInfo( );	
	
#ifdef MYDWC_USEVCHA
	if( _dWork->isvchat ) 
	{
#ifdef YOSHIHARA_VCHAT_ONOFFTEST		
		vchat_onoff();
#endif		
		if( _dWork->myvchaton == 1 && _dWork->opvchaton == 1 )
		{
			myvct_onVchat();
		}
		else
		{
			myvct_offVchat();
		}
				
		myvct_main();
	}
#endif
	if( _dWork->state == MDSTATE_TIMEOUT ) return 1;
	if( _dWork->state == MDSTATE_DISCONNECT ) return 2;
	
	if( _dWork->state == MDSTATE_MATCHED ) 
	{
		if( _dWork->sendintervaltime++ >= KEEPALIVE_TOKEN_TIME && _dWork->sendbufflag == 0) 
		{
			sendKeepAlivePacket();
		}
	}
	
	return mydwc_HandleError();
}

//==============================================================================
/**
 * aidを返します。接続するまでは-1を返します。
 * @retval  aid。ただし接続前は-1
 */
//==============================================================================
int mydwc_getaid()
{
    if(_dWork){
        if( _dWork->state == MDSTATE_MATCHED || _dWork->state == MDSTATE_DISCONNECTTING )
        {
            return DWC_GetMyAID();
        }
    }
	return -1;
}

// ボイスチャットの切断コールバック。
static void vct_endcallback(){
	_dWork->isvchat = 0;
}

//==============================================================================
/**
 * 通信確立後、ボイスチャットを開始します。
 * @param none
 * @retval none
 */
//==============================================================================
void mydwc_startvchat()
{
	switch( _dWork->vchatcodec ){
		case VCHAT_G711_ULAW:
			myvct_init( _dWork->heapID, VCT_CODEC_G711_ULAW );
		break;
		case VCHAT_2BIT_ADPCM:
			myvct_init( _dWork->heapID, VCT_CODEC_2BIT_ADPCM );
		break;
		case VCHAT_3BIT_ADPCM:
			myvct_init( _dWork->heapID, VCT_CODEC_3BIT_ADPCM );
		break;
		case VCHAT_4BIT_ADPCM:		
			myvct_init( _dWork->heapID, VCT_CODEC_4BIT_ADPCM );
		break;
		default:
			myvct_init( _dWork->heapID, VCT_CODEC_4BIT_ADPCM );   //VCT_CODEC_8BIT_RAW
		break;
	}
	myvct_setDisconnectCallback( vct_endcallback );
	_dWork->isvchat = 1;
}

//==============================================================================
/**
 * ボイスチャットのコーデックを指定します。
 * コネクション確立前にコーデックを指定しておくと、
 * コネクション確立時に自動的にボイスチャットを開始します。
 * @param コーデックのタイプ
 * @retval none
 */
//==============================================================================
void mydwc_setVchat(int codec){
	_dWork->vchatcodec = codec;

	if( _dWork->isvchat ){
		switch( _dWork->vchatcodec ){
			case VCHAT_G711_ULAW:
				myvct_setCodec( VCT_CODEC_G711_ULAW );
			break;
			case VCHAT_2BIT_ADPCM:
				myvct_setCodec( VCT_CODEC_2BIT_ADPCM );
			break;
			case VCHAT_3BIT_ADPCM:
				myvct_setCodec( VCT_CODEC_3BIT_ADPCM );
			break;
			case VCHAT_4BIT_ADPCM:		
				myvct_setCodec( VCT_CODEC_4BIT_ADPCM );
			break;
			case VCHAT_8BIT_RAW:
				myvct_setCodec( VCT_CODEC_8BIT_RAW );
			break;
		}
	}
}

//==============================================================================
/**
 * DWCエラー番号に対応するメッセージのIDを返します。
 * @param code - エラーコード（正の値を入れてください
 * @retval メッセージタイプ
 */
//==============================================================================
int mydwc_errorType(int code)
{
	int code100 = code / 100;
	if( code == 20100 ) return 0;
	if( code >= 20102 && code <= 20107 ) return 0;
	if( code == 20109 ) return 0;
	if( code >= 20111 && code <= 20999 ) return 0;
	if( code >= 52004 && code <= 52098 ) return 0;
	if( code >= 52104 && code <= 52198 ) return 0;
	if( code >= 52204 && code <= 52298 ) return 0;
	if( code100 == 523 ) return 0;
	if( code100 == 530 ) return 0;
	if( code100 == 531 ) return 0;
	if( code100 == 532 ) return 0;

    if( code == 20101 ) return 1;
	if( code / 1000 == 23 ) return 1;

	if( code == 20108 ) return 2;

	if( code == 20110 ) return 3;

	if( code100 == 512 ) return 4;

	if( code100 == 500 ) return 5;
    
	if( code == 51099 ) return 6;
	if( code >= 51100 && code <= 51102 ) return 6;
	if( code >= 51104 && code <= 51198 ) return 6;
	if( code >= 51300 && code <= 51398 ) return 6;

	if( code == 51103 ) return 7;

	if( code >= 52000 && code <= 52003 ) return 8;
	if( code >= 52100 && code <= 52103 ) return 8;
	if( code >= 52200 && code <= 52203 ) return 8;

	if( code == 80430 ) return 9;

	if( code >= 60000 && code < 99999 ) return 10;

    if( code < 10000 ) return 11; // エラーコードが１００００以下の場合は、エラーコードの表示の必要がない。

    return -1;
}

//==============================================================================
/**
 * 通信を切断します。
 * @param sync … 0 = 自分から切断しにいく。1 = 相手が切断するのを待つ。
 * @retval 　　　 1 = 接続処理完了。0 = 切断処理中。
 */
//==============================================================================
int mydwc_disconnect( int sync )
{
	if( sync == 0 ){
        OS_TPrintf(" state %d \n",_dWork->state);
		switch( _dWork->state )
		{
            case MDSTATE_MATCHING:   // k.ohno 06.07.08  追加
            case MDSTATE_MATCHED:
			{
				if( _dWork->isvchat )
				{
					// ボイスチャット稼働中
					// 止める
                    OS_TPrintf("ボイスチャット稼働中 止める\n");
					myvct_endConnection();
					_dWork->state = MDSTATE_DISCONNECTTING;
				}
                else{// 稼動して無いなら終了
					DWC_CloseAllConnectionsHard( );
					_dWork->state = MDSTATE_DISCONNECT;
                    return 1;
                }
				break;
			}	
	
			case MDSTATE_DISCONNECTTING:
			{
				// ボイスチャットの終了を待っている状態
				if( _dWork->isvchat == 0 )
				{
					// ボイスチャットの切断完了。
					// 通信自体を切る。
                    OS_TPrintf("ボイスチャットの切断完了。\n");
					DWC_CloseAllConnectionsHard( );
					_dWork->state = MDSTATE_DISCONNECT;
					return 1;
				}
//                else{
//					myvct_endConnection();  //切断処理 k.ohno  ここでは呼ばないように修正
//                }
				break;
			}	
            case MDSTATE_LOGIN:     //親機切断時に動きを合わせるために追加 k.ohno 06.07.04
            case MDSTATE_ERROR_DISCONNECT:
			case MDSTATE_DISCONNECT:
			case MDSTATE_TIMEOUT:
			{
				return 1;
				break;
			}
		}
	} else {
		switch( _dWork->state )
		{
            case MDSTATE_LOGIN:     //親機切断時に動きを合わせるために追加 k.ohno 06.07.04
			case MDSTATE_DISCONNECT:
			case MDSTATE_TIMEOUT:
			{
				return 1;
				break;
			}			
		}		
	}
	
	return 0;
}

//==============================================================================
/**
 * 通信が切断した後、この関数を呼ぶことで内部状態をログイン直後の状態にします。
 * @param 	nonte
 * @retval  1 = 成功。0 = 失敗。
 */
//==============================================================================
int mydwc_returnLobby()
{
    if( _dWork->state == MDSTATE_DISCONNECT || _dWork->state == MDSTATE_TIMEOUT ) {
        _dWork->op_aid = -1;
        _dWork->state = MDSTATE_LOGIN;
        _dWork->newFriendConnect = -1;
        return 1;
	 }
	 return 0;
}

//==============================================================================
/**
 * fetal error発生時に呼ばれる関数、このコールバックの中で処理をとめて下さい。
 * @param 	nonte
 * @retval  1 = 成功。0 = 失敗。
 */
//==============================================================================
void mydwc_setFetalErrorCallback( void (*func)(int) )
{
    if(_dWork){
        _dWork->fetalErrorCallback = func;
    }
}



//-----2006.04.11 k.ohno
//==============================================================================
/**
 * ログアウトする
 * @param 	none
 * @retval  none
 */
//==============================================================================

void mydwc_Logout(void)
{
    DWC_ShutdownFriendsMatch();
    DWC_CleanupInet();
    myvct_free();
    mydwc_free();
}


//==============================================================================
/**
 * オンラインの友達がサーバにアップしている情報をおさめる配列を指定します。
 * この配列はmydwc_step, mydwc_stepmatchを呼び出した際に更新される可能性があります。
 * @param 	array - データをおさめる配列の先頭
 * @param 	size  - 一人あたりのデータサイズ
 * @retval  none
 */
//==============================================================================
void mydwc_setFriendStateBuffer( void *array, int size )
{
	_dWork->friendinfo = array;	
	_dWork->infosize = size;
	

}

// FRIENDINFO_UPDATA_PERFRAME人分のデータを更新する。
static void mydwc_updateFriendInfo( )
{
	int i;
	if( _dWork->friendinfo == NULL ) return;
	for(i = 0; i < FRIENDINFO_UPDATA_PERFRAME; i++)
	{
		int index = _dWork->friendupdate_index % FRIENDLIST_MAXSIZE;
		int size;
	
		if( DWC_IsBuddyFriendData( &(_dWork->keyList[index]) ) ) 
		{
			_dWork->friend_status[index] = 
				DWC_GetFriendStatusData( 
					&_dWork->keyList[ index ], 
					(void *)(((u32)_dWork->friendinfo) + _dWork->infosize * index),
					&size
				);
				
			if( size > _dWork->infosize )
			{
				OS_TPrintf("\n!!!!!!!!!!!!!!!size > _dWork->infosize!!!!!!!!!!!!!!!!\n");
			}
		}
			
		_dWork->friendupdate_index = (_dWork->friendupdate_index + 1) % FRIENDLIST_MAXSIZE;
	}
}

//==============================================================================
/**
 * 自分の状態をサーバにアップします。
 * @param 	data - データへのポインタ
 * @param 	size  - データサイズ
 * @retval  成功の可否
 */
//==============================================================================
BOOL mydwc_setMyInfo( const void *data, int size )
{
	OS_TPrintf("upload status change(%p, %d)\n", data, size);
	return DWC_SetOwnStatusData( data, size );
}

//==============================================================================
/**
 * 友達がサーバにアップしている情報を取得します（ローカルにキャッシュしてあるものを表示します）。
 * @param 	index フレンドリスト上の番号
 * @retval  データへのポインタ。中身は書き換えないで下さい。
 */
//==============================================================================
void *mydwc_getFriendInfo( int index )
{
	return (void *)(((u32)_dWork->friendinfo) + _dWork->infosize * index);
}

//==============================================================================
/**
 * 友達がサーバにアップしている情報を取得します（ローカルにキャッシュしてあるものを表示します）。
 * @param 	index フレンドリスト上の番号
 * @retval  友達の状態。DWC_GetFriendStatusDataの返り値と同じ
 */
//==============================================================================
u8 mydwc_getFriendStatus( int index )
{
	return _dWork->friend_status[index];
}


static void SetupGameServerCallback(DWCError error, BOOL cancel, BOOL self, BOOL isServer, int  index, void* param);
static void ConnectToGameServerCallback(DWCError error, BOOL cancel, BOOL self, BOOL isServer, int  index, void* param);
static void NewClientCallback(int index, void* param);

//==============================================================================
/**
 * ゲーム募集・参加を行う関数。
 * @target   負…自分でゲームを開催。０以上…接続しに行く相手の、フレンドリスト上の位置
 * @retval  正…成功。０…失敗。
 */
//==============================================================================
int mydwc_startgame( int target )
{
	if( _dWork->state != MDSTATE_LOGIN ) return 0;

	_dWork->friendindex = target;

	if ( target < 0 ){
	    DWC_SetupGameServerAsync(
	    	(u8)2,			// 二人対戦限定
	        SetupGameServerCallback,
	        NULL,
	        NewClientCallback,
	        NULL
	    );
	    
	    _dWork->matching_type = MDTYPE_PARENT;
    } else {
        DWC_ConnectToGameServerAsync(target,
                                     ConnectToGameServerCallback,
                                     NULL,
                                     NewClientCallback,
                                     NULL);	    
                                     
	    _dWork->matching_type = MDTYPE_CHILD;
    }

                              
    _dWork->state = MDSTATE_MATCHING;
  
    // 送信コールバックの設定	
    DWC_SetUserSendCallback( SendDoneCallback ); 

    // 受信コールバックの設定	
    DWC_SetUserRecvCallback( UserRecvCallback ); 
    
    // コネクションクローズコールバックを設定
    DWC_SetConnectionClosedCallback(ConnectionClosedCallback, NULL);
    
    // タイムアウトコールバックの設定
    DWC_SetUserRecvTimeoutCallback( recvTimeoutCallback );
    
    _dWork->sendbufflag = 0;
    
	// テスト用
	_dWork->s_param = 0;    

    
    return 1;    
}

//==============================================================================
/**
 * 今接続している友達のフレンドリスト上の位置を返します。
 * まだ、接続が完了していなくても友達番号を返すことがありますので、接続が
 * 完了したかの判定には使わないでください。
 * @retval  ０以上…友達番号。－１…まだ接続してない。
 */
//==============================================================================
int mydwc_getFriendIndex()
{
    if(_dWork){
        // 今接続している友達のフレンドリスト上の位置を返します。
        return _dWork->friendindex;
    }
    return -1;
}
/*---------------------------------------------------------------------------*
  ゲームサーバ起動コールバック関数
 *---------------------------------------------------------------------------*/
static void SetupGameServerCallback(DWCError error,
                                    BOOL cancel,
                                    BOOL self,
                                    BOOL isServer,
                                    int  index,
                                    void* param)
{
#pragma unused(isServer, param, index)
    if (error == DWC_ERROR_NONE){
        if (!cancel){
            // ネットワークに新規クライアントが加わった
            OS_TPrintf("友達が接続してきました。（インデックス＝%d）\n", index);
			_dWork->friendindex = index;
            // バッファの確保
            setConnectionBuffer();
        }
        else 
        {
            if (self){
                // 自分がマッチングをキャンセルした
                OS_TPrintf("マッチングのキャンセルが完了しました。\n\n");
	            // ログイン後状態に戻る
//				s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH;  
            }
            else {
                // 繋いでいた子機が、接続をキャンセルした。
                OS_TPrintf("Client (friendListIndex = %d) canceled matching.\n\n", index);
                // 繋いできた子機がいなくなった。2006.7.3 yoshihara
                _dWork->newFriendConnect = -1;
            }
        }
    }
    else {
        // エラーが発生した。エラーコードは、step関数の中で拾う。
        OS_TPrintf("Game server error occured. %d\n\n", error);

//        s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH; 
    }
}

/*---------------------------------------------------------------------------*
  ゲームサーバ接続コールバック関数
 *---------------------------------------------------------------------------*/
static void ConnectToGameServerCallback(DWCError error,
                                        BOOL cancel,
                                        BOOL self,
                                        BOOL isServer,
                                        int  index,
                                        void* param)
{
#pragma unused(param)
    if (error == DWC_ERROR_NONE){
        if (!cancel){
            if (self){
                // 自分がゲームサーバとそこにできているネットワークへの接続に
                // 成功した場合
                OS_TPrintf("接続に成功しました\n\n");
            }
            else {
                // ネットワークに新規クライアントが加わった場合。
                // 二人対戦限定なので、ここにはこないはず。
            }

            // 受信バッファセット
            setConnectionBuffer();
        }
        else {
            if (self){
                // 自分がマッチングをキャンセルした
                OS_TPrintf("キャンセルが完了しました。\n\n");
                // ログイン後状態に戻る
//                s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH;  
            }
            else {
                if (isServer){
                    // ゲームサーバがマッチングをキャンセルした
                    OS_TPrintf("親が接続をキャンセルしました\n\n");
                    // マッチングを終了してログイン後状態に戻る
//                    s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH;
                }
                else {
                    // 他のクライアントがマッチングをキャンセルした。
                    // 二人対戦ならここにこないはず。
                }
            }
        }
    }
    else {
        // エラーが発生した。エラーコードは、step関数の中で拾う。
        OS_TPrintf("Game server error occured. %d\n\n", error);

        // もう一度最初から。おいおい処理
//        s_dwcstate = MYDWCSTATE_MATCH_ERRORFINISH; 
    }

//    s_blocking = 0;
}

/*---------------------------------------------------------------------------*
  サーバクライアント型マッチング時の新規接続クライアント通知コールバック関数
 *---------------------------------------------------------------------------*/
static void NewClientCallback(int index, void* param)
{
#pragma unused(param)
    // 新規接続クライアントの接続処理が終わるまでは、
    // コントローラ操作を禁止する
//    s_blocking = 1;

    _dWork->newFriendConnect = index;
    
    OS_TPrintf("新しい人が接続してきました。\n");
    if (index != -1){
        OS_TPrintf("友達[%d].\n", index);
    }
    else {
        OS_TPrintf("友達ではない.\n");
    }
}

//==============================================================================
/**
 * 音声のノイズカットレベルを調整します（外部からアクセスしたいので、こちらに）
 * @param   d … 今より閾値を下げるか、上げるか（下げるほど拾いやすくなる）
 * @retval  none
 */
//==============================================================================
void mydwc_changeVADLevel(int d)
{
//	myvct_changeVADLevel(d);
}

//==============================================================================
/**
 * 現在のフレンドリストを表示します。（デバッグ用）
 * @param 	none
 * @retval  none
 */
//==============================================================================
void mydwc_showFriendInfo()
{
	int i;
	
	if( !DWC_CheckHasProfile( _dWork->myUserData ) ) 
	{
		DWCFriendData token;
		u32 *ptr;

		DWC_CreateExchangeToken( _dWork->myUserData, &token ); 
		ptr = (u32*)&token;
		OS_TPrintf("まだ、プロファイルＩＤ取得前\nログインＩＤ:(%d, %d, %d)\n\n", ptr[0], ptr[1], ptr[2] );		
	}
	else
	{
		// 接続済み	
		DWCFriendData token;
		DWC_CreateExchangeToken( _dWork->myUserData, &token );
		OS_TPrintf("プロファイルＩＤ:%d \n\n", DWC_GetGsProfileId( _dWork->myUserData, &token ) );	
	}
	
	for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
	{
		int ret = DWC_GetFriendDataType( &(_dWork->keyList[i]) );
		u32 *ptr = (u32*)(&_dWork->keyList[i]);
		switch(ret)
		{
			case DWC_FRIENDDATA_LOGIN_ID:
				OS_TPrintf("%d:ログインＩＤ:(%d, %d, %d)",i, ptr[0], ptr[1], ptr[2] );
				break;

			case DWC_FRIENDDATA_FRIEND_KEY:
				OS_TPrintf("%d:フレンドコード:(%d)", i, DWC_GetGsProfileId( _dWork->myUserData, &_dWork->keyList[i] ) );			
				break;

			case DWC_FRIENDDATA_GS_PROFILE_ID:
				OS_TPrintf("%d:プロファイルＩＤ:(%d)", i, DWC_GetGsProfileId( _dWork->myUserData, &_dWork->keyList[ i ]) );
				break;

			case DWC_FRIENDDATA_NODATA:
			default:
				OS_TPrintf("%d:空", i);
				break;
		}			
		
		if( DWC_IsBuddyFriendData( &(_dWork->keyList[i]) ) )
		{
			OS_TPrintf("(両思い)");
		}
		OS_TPrintf("\n");
	}
}


// 送信したかどうかを返します
BOOL mydwc_IsSendVoiceAndInc(void)
{
    return myvct_IsSendVoiceAndInc();
}


//==============================================================================
/**
 * ボイスチャット状態かどうかを返します   k.ohno 06.05.23 07.22 フラグを交換
 * @retval  TRUE…ボイスチャット   FALSE…ボイスチャットではない 
 */
//==============================================================================
BOOL mydwc_IsVChat(void)
{
    if(_dWork){
        return _dWork->bVChat;
    }
    return FALSE;
}

//==============================================================================
/**
 * 接続してきたかどうかを返します    k.ohno 06.05.24
 * @retval  TRUE…接続開始なのでキー操作をブロック   FALSE…
 */
//==============================================================================
BOOL mydwc_IsNewPlayer(void)
{
    if(_dWork){
        return _dWork->newFriendConnect;
    }
    return FALSE;
}

//==============================================================================
/**
 * 接続してきたかどうかフラグを落とします k.ohno 06.08.04
 * @retval  none
 */
//==============================================================================
void mydwc_ResetNewPlayer(void)
{
    if(_dWork){
        _dWork->newFriendConnect = -1;
    }
}

//==============================================================================
/**
 * 遅延のONOFF     k.ohno 06.05.30
 */
//==============================================================================
BOOL mydwc_toggleDelay(void)
{
    _dWork->bDelay = 1 - _dWork->bDelay;
    return _dWork->bDelay;
}

//==============================================================================
/**
 * VCHATのONOFF     k.ohno 06.05.24
 */
//==============================================================================
void mydwc_setVChat(BOOL bVChat)
{
    _dWork->bVChat = bVChat;
}

static void sendPacket()
{
	if( _dWork->sendbufflag || !DWC_IsSendableReliable( DWC_GetMyAID() ) ) // 送信バッファをチェック。
	{
		_dWork->sendbufflag = 1;
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_KEEPALIVE_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);;
		DWC_SendReliable( _dWork->op_aid, &(_dWork->sendBuffer[0]), 4);
		_dWork->sendintervaltime = 0;
	}
}

void mydwc_VChatPause()
{
	if( _dWork->myvchaton != 0 )
	{
		_dWork->myvchaton = 0;
		sendPacket();
	}
}

void mydwc_VChatRestart()
{
	if( _dWork->myvchaton != 1 )
	{
		_dWork->myvchaton = 1;
		sendPacket();
	}
}