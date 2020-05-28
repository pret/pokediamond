//=============================================================================
/**
 * @file	dwc_test.c
 * @bfief	DWCラッパーのテスト用
 * @date	06/02/24
 */
//=============================================================================

#include "common.h"
#include "wifi/dwc_test.h"
#include "wifi/dwc_rap.h"

#define MYDWC_HEAPID HEAPID_COMMUNICATION

#define SERVERBUF_SIZE 16

typedef struct{
	u32 aid;
	u32 data;
} T_SERVERCOM;

typedef struct
{
	// サーバに溜まっているデータのキュー
	T_SERVERCOM serverbuf[SERVERBUF_SIZE];
	
	int start;			// キューの先頭
	int end;			// キューの最後
	
	int state;
	int heapID;
	
	int ret;			// 接続情報
	
	MATHRandContext16 context;
	int index;
} DWCTEST_WORK;

static DWCTEST_WORK *_testWork;

enum {
	DWCTESTSTATE_INIT,
	DWCTESTSTATE_CONNECTING,
	DWCTESTSTATE_LOGIN,
	DWCTESTSTATE_MATCHING,
	DWCTESTSTATE_CANCELING,
	DWCTESTSTATE_CONNECT,
	DWCTESTSTATE_DISCONNECTING,
	DWCTESTSTATE_END,	
	DWCTESTSTATE_DISCONNECTED,
		
	DWCTESTSTATE_ERROR,
	DWCTESTSTATE_LAST
};

static void serverCallback(u16 aid, u16 *data, u16 size);
static void clientCallback(u16 aid, u16 *data, u16 size);
static void testMain();
static void fetal_error( int errorcode );

static u32 getRand32()
{
	u32 buffer[8];
	u32 ans;
	MATHCRC32Table table;
	MATH_CRC32InitTable( &table );

	OS_GetLowEntropyData( buffer );
	ans = MATH_CalcCRC32( &table, buffer, sizeof(buffer) );
	OS_TPrintf("my id = %d\n", ans);
	return ans;
}


void dwctest_init( int heapID )
{
	_testWork = (DWCTEST_WORK *) sys_AllocMemory( heapID, sizeof(DWCTEST_WORK) );
	_testWork->start = 0;
	_testWork->end = 0;
	_testWork->state = DWCTESTSTATE_INIT;
	_testWork->index = 0;
	_testWork->heapID = heapID;
	
	MATH_InitRand16( &_testWork->context, getRand32() );
}

static void dwctest_reinit(){
	_testWork->start = 0;
	_testWork->end = 0;
	_testWork->state = DWCTESTSTATE_INIT;
	_testWork->index = 0;
}

static const char* _mesType[] = {
	// エラーコードが１００００以下の場合は、エラーコードの表示の必要がない。
	"Wi-Fiコネクションに 接続できません。 詳しくは取扱説明書を ご覧ください。（エラーコード%d）",
	"お客様のWi-FiコネクションIDは長い間 使用されなかったため削除されました。 詳しくは取扱説明書をご覧ください。（エラーコード%d）",
	"このソフトの Wi-Fiコネクションサービスは 終了しました。 ご利用ありがとうございました。（エラーコード%d）",
	"接続できるアクセスポイントが 見つかりません。 Wi-Fiコネクション設定で 接続先の設定をご確認ください。（エラーコード%d）",
	"Wi-Fiコネクションに 接続できません。 Wi-Fiコネクション設定で 接続先の設定をご確認ください。（エラーコード%d）",
	"ニンテンドーWi-Fiコネクタに 接続できません。 Wi-Fiコネクション設定で ニンテンドーWi-Fiコネクタの 接続をご確認ください。（エラーコード%d）",
	"アクセスポイントが見つかりません。 アクセスポイントに近づいて もう一度おためしください。（エラーコード%d）",
	"Wi-Fiコネクションが混み合っているか サービスが停止しているために 接続できません。 しばらく待ってやり直してください。エラーコード%d）",
	"アクセスポイントが混み合っているため 接続できません。 しばらく待ってやり直してください。（エラーコード%d）",
	"Ｗｉ－Ｆｉコネクションが切断されました。（エラーコード：%d）",
	"ネットワークから切断されました。"
};

void dwctest_main(  )
{
	switch( _testWork->state )
	{
		case DWCTESTSTATE_INIT:
		{
			// 初期状態。
			_testWork->ret = mydwc_startConnect(NULL, _testWork->heapID);
			// フェータルエラー（再起不能のエラー）が発生した際に呼ばれる関数を指定します。
			mydwc_setFetalErrorCallback( fetal_error );
			_testWork->state = DWCTESTSTATE_CONNECTING;
			if( _testWork->ret == MYDWC_STARTCONNECT_OK )
			{
				OS_TPrintf("「Ｗｉ－Ｆｉコネクションに接続しますか？[Y/N]」\n");				
			} 
			else if ( _testWork->ret == MYDWC_STARTCONNECT_FIRST )
			{
				OS_TPrintf("「Ｗｉ－Ｆｉコネクションでは、ＤＳカードとＤＳ本体をセットで扱います。\n");
				OS_TPrintf("ご使用中のＤＳ本体でＷｉ－Ｆｉコネクションに接続しますか？[Y/N]」\n");
			} else if( _testWork->ret == MYDWC_STARTCONNECT_DIFFERENTDS ) {
				OS_TPrintf("「DS本体とDSカードのWi-Fiユーザ情報がちがうためWi-Fiコネクションに接続できません。」\n");
				OS_TPrintf("「DSカードに保存されているWi-Fiユーザ情報を更新しますか？これまでWi-Fiコネクションでお使いになられていたデータは失われてしまいます。[Y/N]」\n");
				OS_TPrintf("「(ゲーム独自の修復用情報表示)」\n");
				OS_TPrintf("「本当に更新してもよろしいですか？[Y/N]」\n");
			}
			OS_TPrintf("「Wi-Fiコネクションに接続しています。しばらくお待ちください。」\n");
			break;
		}
		
		case DWCTESTSTATE_CONNECTING:
		{
			// 接続中
			int ret = mydwc_connect();
			if( ret < 0 ){
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("Ａボタンを押すと再度接続を試みます。\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}
			else if ( ret > 0 ) 
			{
				if( _testWork->ret != MYDWC_STARTCONNECT_OK ) {				
					OS_TPrintf("「DSカードにご使用中のDS本体のWi-Fiユーザ情報を保存しました。今後Wi-Fiコネクションへの接続は、ご使用中のDS本体をご使用ください」\n");
				}
				OS_TPrintf("WiFiコネクションに接続しました。\n	");
				OS_TPrintf("Aボタンを押すとマッチングを開始します。\n");	
				_testWork->state = DWCTESTSTATE_LOGIN;
			}
			
			break;
		}
		
		case DWCTESTSTATE_LOGIN:
		{
			// 接続が完了した直後。
			int ret = mydwc_step( );
				
			if( ret < 0 ){ // エラー発生
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("Ａボタンを押すと再度接続を試みます。\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}			
			
			if(sys.trg & PAD_BUTTON_A)
			{
				// マッチングが完了するまでにコールバックを設定する必要があるので、ここでしておく、
				mydwc_setReceiver( serverCallback, clientCallback );
				// マッチングを自動的に開始する。	
				if( mydwc_startmatch( ) ){
					OS_TPrintf("マッチングを開始\n");
					_testWork->state = DWCTESTSTATE_MATCHING;
				}
			}
			break;
		}
		
		case DWCTESTSTATE_MATCHING:
		{
			int ret;
			if( sys.trg & PAD_BUTTON_B )
			{
				// マッチングキャンセル
				ret = mydwc_stepmatch( 1 );
			} 
			else
			{
				ret = mydwc_stepmatch( 0 );				
			}
				
			if( ret < 0 ){
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("Ａボタンを押すと再度接続を試みます。\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}
			else if ( ret == 1 ) 
			{
				OS_TPrintf("対戦相手が見つかりました。\n");
				_testWork->state = DWCTESTSTATE_CONNECT;
			}
			else if ( ret == 2 )
			{
				OS_TPrintf("キャンセルしました。\n");	
				OS_TPrintf("Aボタンを押すとマッチングを開始します。\n");	
				_testWork->state = DWCTESTSTATE_LOGIN;							
			}
			break;
		}
		
		case DWCTESTSTATE_DISCONNECTING:
		// 切断が完了するまで、毎フレームmydwc_disconnectを呼び出してください。
		// その後、mydwc_stepも呼ぶ必要があります。
		if( mydwc_disconnect( 0 ) ) {
			_testWork->state = DWCTESTSTATE_DISCONNECTED;
			break;
		}
		case DWCTESTSTATE_CONNECT:
		{
			// 接続完了後	
			int ret;
			
			if( (_testWork->state == DWCTESTSTATE_CONNECT) && (sys.trg & PAD_BUTTON_START) ){			
				_testWork->state = DWCTESTSTATE_DISCONNECTING;
				break;	
			}
			testMain();
			ret = mydwc_step();

			if( ret < 0 ){
				// エラー発生。
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("Ａボタンを押すと再度接続を試みます。\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}		
			else if( ret == 1 )
			{
				// タイムアウト（相手から１０秒以上メッセージが届かない）
				// 一定時間送信がない場合は、空のデータを内部で送信しています。
				OS_TPrintf("タイムアウトが発生しました。\n");	
				_testWork->state = DWCTESTSTATE_DISCONNECTED;			
			}
			else if(ret == 2)
			{
				// 切断された。
				OS_TPrintf("相手から切断されました。\n");
				_testWork->state = DWCTESTSTATE_DISCONNECTED;
			}	
			break;
		}
		
		case DWCTESTSTATE_DISCONNECTED:
		{
			// 切断完了。	
			OS_TPrintf("相手との通信が終了しました。\n");
			OS_TPrintf("Aボタンを押すと再度マッチングを開始します。\n");
			mydwc_returnLobby();
			_testWork->state = DWCTESTSTATE_LOGIN;			
		}
		
		case DWCTESTSTATE_ERROR:
		{
			if(sys.trg & PAD_BUTTON_A)
			{
				// 一度開放
				mydwc_free();
				
				dwctest_reinit();
			}
		}
		break;
	}
}

static void serverCallback(u16 aid, u16 *data, u16 size)
{
	// データを受信
	_testWork->serverbuf[_testWork->end].aid = aid;
	_testWork->serverbuf[_testWork->end].data = *((u32*)data);
	_testWork->end++;
	if( _testWork->end >= SERVERBUF_SIZE ) _testWork->end = 0;
	if( _testWork->end == _testWork->start )
	{
		// バッファオーバーフロー
		OS_TPrintf("!!!!!!!!!!!オーバーフロー!!!!!!!!!!!!!!!!");	
	}
}

static void clientCallback(u16 aid, u16 *data, u16 size)
{
	T_SERVERCOM *comm;
	
	comm = (T_SERVERCOM*) data;
	
	// 単に表示するだけ。
	if( comm->aid == 0 ){
		OS_TPrintf("%d\n", comm->data);
	}else{
		OS_TPrintf("        %d\n", comm->data);
	}
}

static void testMain()
{
	// サーバ用キューにデータが残っている場合、送信。
	if( _testWork->end != _testWork->start )
	{
		if( mydwc_sendToClient( &(_testWork->serverbuf[_testWork->start]), sizeof(T_SERVERCOM) ))
		{
			// 送信処理成功
			_testWork->start++;
			if( _testWork->start >= SERVERBUF_SIZE ) _testWork->start = 0;
		}
	}
	
	// ２０フレームに一度くらい、送信。
//	if( MATH_Rand16( &_testWork->context, 20 ) == 0 )
	// 何かボタンを押したら
	if( sys.trg )
	{
		if ( mydwc_sendToServer( &(_testWork->index), 4) )
		{
			_testWork->index++;
		}
	}
}

static void fetal_error( int errorcode ){
	OS_TPrintf(_mesType[mydwc_errorType(errorcode)], errorcode);
	OS_TPrintf("電源を切ってください。\n");	
	while(1){}
}