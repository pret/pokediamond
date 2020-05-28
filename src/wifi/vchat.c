//=============================================================================
/**
 * @file	vchat.c
 * @bfief	ボイスチャットラッパー。二人電話モード専用
 * @author	kazuki yoshihara
 * @date	06/02/27
 */
//=============================================================================

#include "common.h"
#include "wifi/dwc_rap.h"
#include "wifi/vchat.h"
#include <vct.h>

#define MYNNSFORMAT NNS_SND_STRM_FORMAT_PCM16

#define VCHAT_SAMPLING_RATE       8000   // Hz
#define SAMPLING_BYTE        2      // byte = 16bit
#define MAX_SAMPLING_TIME   68     // ms
#define MAX_CHANNELS 1
#define VCHAT_WAVE_SAMPLE ((int) (VCHAT_SAMPLING_RATE * MAX_SAMPLING_TIME * SAMPLING_BYTE) / 1000)

//#define VCFINFO_SHOW
//#define VCT_ERROR_NONE (VCT_SUCCESS)

// エコーキャンセル機能を使う場合は定義して下さい。（この場合はライブラリはさしかえて下さい）
#define USE_ECHOCANCEL

// マイクゲインを設定
#define MY_AMPGAIN PM_AMPGAIN_160
//#define MY_AMPGAIN PM_AMPGAIN_80
//#define MY_AMPGAIN PM_AMPGAIN_40
//#define MY_AMPGAIN PM_AMPGAIN_20

// 何フレームまで履歴を持って、チェックするか
#define HAWLING_CHECKFRAME 16

typedef struct{
	u8 stAudioBuffer[VCT_AUDIO_BUFFER_SIZE * VCT_DEFAULT_AUDIO_BUFFER_COUNT ];
	u8 sPlayBuffer[VCHAT_WAVE_SAMPLE * 2 * MAX_CHANNELS];
    // 無音サウンドとして渡す用のバッファ（常に０）
    u8 sSilentBuffer[VCHAT_WAVE_SAMPLE * 2 * MAX_CHANNELS];
	u8  *sRecBuffer;
	
	void (*disconnectCallback)();
	VCTSession sSession[2];
	int state;
	int off_flag;
	int heapID;
	struct NNSSndStrm sSndStream;
	VCTSession *session;
    u8 bSendVoice;
    u8 firstCallback;
    u16 dummy;
    MICAutoParam micParam;
    
    // ハウリング、クリップ検出まわり
    int hc_state;
    int hc_ampgain;
    int hc_ampchangeflag;
    int hc_seqcount;
    int hc_hawlingflag;			// 一度ハウリングしてから、まだ一度もキー入力がない。
    u16 hc_check[HAWLING_CHECKFRAME];
    int hc_index;
    
}MYVCT_WORK;

enum{
	VCTSTATE_INIT,
	VCTSTATE_WAIT,
	VCTSTATE_CALLING
};

static void* _vWork_temp;
static MYVCT_WORK* _vWork = NULL;

static void StartSoundLoop();

// 初期化処理。親子共通。セッション確立後に呼ばれる。
//
// 音声系の初期化（最初の１回のみ）
//

static u8 *_test_buffer;
static u32 _test_buffer_index;
#define TEST_BUFFER_SIZE 0x100000

static OSTick _tick_time;
static int _difftime = 0;

static void InitFirst()
{
    OS_TPrintf("Init sound system\n");
    // マイク関連の初期化
    //
    MIC_Init();
    PM_Init();

#if 0
	sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_VCTTEST, TEST_BUFFER_SIZE + 0x1000 );
	_test_buffer = sys_AllocMemory(HEAPID_VCTTEST, TEST_BUFFER_SIZE);
	MI_CpuClear8( _test_buffer, TEST_BUFFER_SIZE);
 	_test_buffer_index = 0;
#endif
    {
	    u32 ret;
	    ret = PM_SetAmp(PM_AMP_ON);
	    if( ret == PM_RESULT_SUCCESS )
	    {
		    OS_TPrintf("AMPをオンにしました。\n");
	    }
	    else
	    {
		    OS_TPrintf("AMPの初期化に失敗（%d）", ret);
	    }
    }

    {
	    u32 ret;
	    ret = PM_SetAmpGain(MY_AMPGAIN);
	    if( ret == PM_RESULT_SUCCESS )
	    {
		    OS_TPrintf("AMPのゲインを設定しました。\n");
	    }
	    else
	    {
		    OS_TPrintf("AMPのゲイン設定に失敗（%d）", ret);
	    }
    }
    
	_vWork->hc_state    = 0;
	_vWork->hc_seqcount = 0;    
	_vWork->hc_ampgain  = 0;
	_vWork->hc_ampchangeflag = 0;
	_vWork->hc_hawlingflag = 0;
	{
		int i;
		for( i = 0; i < HAWLING_CHECKFRAME; i++ )
		{
			_vWork->hc_check[i] = 0;
		}
    	_vWork->hc_index = 0;		
	}
	// 廃止になったと書いてあったので削除 2006/05/08 k.ohno
	//VCT_SetVADParams( MY_AMPGAIN, VCT_MIC_INTERNAL );
    //{  // プリントするだけなので削除 パラメーターもなくなっていた 2006/05/08 k.ohno
	//	VCTVADInfo outInfo;
	//	VCT_GetVADInfo( &outInfo );
		
	//	OS_TPrintf("soundLevel = %d, noiseLevel = %d\n", outInfo.soundLevel, outInfo.noiseLevel);
	//}
	VCT_EnableVAD( TRUE );
//	VCT_EnableVAD( FALSE );
    // サウンドシステムの初期化
    //
    NNS_SndInit();
    NNS_SndStrmInit(&_vWork->sSndStream);

	MI_CpuClearFast(_vWork->sSilentBuffer, sizeof(_vWork->sSilentBuffer) );
    OS_TPrintf("Init sound system done.\n");
    
    _difftime = 0;
}



#define HAWLING_SEQ_A 4
#define HAWLING_SEQ_B 8
#define HAWLING_SEQ_C 12
#define HAWLING_SEQ_D 100
#define HAWLING_SEQ_E 4
// ハウリング検出ルーチン
// HAWLING_SEQ_Aフレーム連続で規定値Aを超えた場合、マイクゲインを１段階下げる。
// さらにそのままHAWLING_SEQ_Bフレームハウリングが続いたら、
// HAWLING_SEQ_Cフレーム、マイクからの送信をとめる
// HAWLING_SEQ_Dフレーム連続で規定値Aを超えることなく、何か入力があればゲインを１段階上げる。
// 返り値が１なら、入力は０を。

#define HAWLING_BORDER_1 0x0300
#define HAWLING_BORDER_2 0x0200
#define HAWLING_BORDER_3 0x0100

#if 0
static int is_clip( int c1, int c2, int c3 )
{
	int ans = (c1 >= 5 || c2 >= 2 || c3 > 0 );
	OS_TPrintf("(%d, %d, %d) - %d\n", c1, c2, c3, ans);
	return ans;	
}
#else
static int is_clip( )
{
	int i;
	int count = 0;
	for(i = 0; i < HAWLING_CHECKFRAME; i++ )
	{
		count += _vWork->hc_check[i];
	}
	
	return (count >= 5 * HAWLING_CHECKFRAME);
}
#endif

static void change_gain(int d)
{
	if( d < 0 ) d = 0;
	if( d >= 4 ) d = 3;
	
	_vWork->hc_ampgain = d;
	_vWork->hc_ampchangeflag = 1;
}

// ゲーム入力があれば、ここに入れる。とりあえず、PAD_KEY_READの入力があればとしておく。
static int hasGameInput()
{
	return PAD_Read();	
}

static int check_hawling(s16 *data, int length)
{
    int i;
    u16 *ptr;
//    int c1 = 0;
//    int c2 = 0;
//    int c3 = 0;
    ptr = _vWork->hc_check + _vWork->hc_index;
    *ptr = 0;
    _vWork->hc_index = ( _vWork->hc_index + 1 ) % HAWLING_CHECKFRAME;
    for( i = 0; i < length / 2; i++)
    {
	    if( data[i] < -(0x8000 - HAWLING_BORDER_1) || data[i] > (0x8000 - HAWLING_BORDER_1)) (*ptr)++;
//    	if( data[i] < -(0x8000 - HAWLING_BORDER_1) || data[i] > (0x8000 - HAWLING_BORDER_1)) c1++;
//    	if( data[i] < -(0x8000 - HAWLING_BORDER_2) || data[i] > (0x8000 - HAWLING_BORDER_2)) c2++;
//    	if( data[i] < -(0x8000 - HAWLING_BORDER_3) || data[i] > (0x8000 - HAWLING_BORDER_3)) c3++;
    }
    
//    if( is_clip( c1, c2, c3 ) )
    if( is_clip( ) )
    {
    	if( _vWork->hc_state == 0 )
    	{
    		// 今までは正常
    		_vWork->hc_state = 1;
    		_vWork->hc_seqcount = 0;
    	}
    	else if( _vWork->hc_state == 1 )
    	{
    		// 前回も基準値越え
    		if( _vWork->hc_seqcount++ >= HAWLING_SEQ_A )
    		{
    			// HAWLING_SEQ_A以上基準値越え
    			// アンプを一段階下げる
    			change_gain( _vWork->hc_ampgain + 1 );
    			OS_TPrintf("音量の入力が一定時間規定値を超えてます。マイクのゲインを一段階下げます(%d)\n", _vWork->hc_ampgain);
	    		_vWork->hc_state = 2;
	    		_vWork->hc_seqcount = HAWLING_SEQ_E;
	    		_vWork->hc_hawlingflag = 1;
    		}
    	}
    	else if( _vWork->hc_state == 2 )
    	{
    		// ゲインが下がってからも連続して基準越え中
    		if( _vWork->hc_seqcount++ >= HAWLING_SEQ_B )
    		{
    			// いったん音を止めるモードへ移行
    			OS_TPrintf("ゲインを下げてもまだ規定値を超え続けています。ハウリングの恐れがあるので一旦マイクを止めます。(%d)\n", _vWork->hc_ampgain);
	    		_vWork->hc_state = 3;
	    		_vWork->hc_seqcount = 0;
    		}
    	}
    }
    else
    {
    	if( _vWork->hc_state == 0 )
    	{
    		// 正常
    		if( _vWork->hc_seqcount++ >= HAWLING_SEQ_D && (hasGameInput() || _vWork->hc_hawlingflag == 0) ) 
    		{
  				// ゲインを一段階上げる
  				if( _vWork->hc_ampgain > 0 )
  				{
	    			change_gain( _vWork->hc_ampgain - 1 );
	    			if( _vWork->hc_hawlingflag == 1 )
	    			{
		    			OS_TPrintf("一定時間規定をこえませんでしたので、キー入力と同時にゲインをあげました(%d)\n", _vWork->hc_ampgain);
			    		_vWork->hc_hawlingflag = 0;	    			
	    			}
	    			else
	    			{
		    			OS_TPrintf("一定時間規定をこえませんでしたので、ゲインをあげました(%d)\n", _vWork->hc_ampgain);
	    			}
	    				
  				}
	    		_vWork->hc_seqcount = 0;
    		}
    	}
    	else if( _vWork->hc_state == 1 ) 
    	{
    		// 前回は基準越え
    		_vWork->hc_state = 0; 
    		_vWork->hc_seqcount = 0;    		
    	}
    	else if (_vWork->hc_state == 2 )
    	{
    		if( _vWork->hc_seqcount-- <= 0 )
    		{
	    		_vWork->hc_state = 0; 
	    		_vWork->hc_seqcount = 0;    		
    		}
    	}
    	else if( _vWork->hc_state == 3 )
    	{
    		// 音をとめている最中
    		if( _vWork->hc_seqcount++ >= HAWLING_SEQ_C )
    		{
    			// 音止め終了
    			OS_TPrintf("マイク入力を復帰させます\n");
	    		_vWork->hc_state = 0; 
	    		_vWork->hc_seqcount = 0;        				
    		}
    	}
    }
    
//    OS_TPrintf("{%d-%d}\n", _vWork->hc_state, _vWork->hc_seqcount);
    
    if( _vWork->hc_state == 3 )
   	{
   		// 音をとめている最中
   		return 1;
   	}
   	
   	return 0;
}
//
// 音声処理コールバック（NitroSystem NNS_SndStrmを利用）
//
static void micCallback(MICResult result, void *arg)
{
#pragma unused(result, arg)
}

static void SndCallback(NNSSndStrmCallbackStatus sts,
                        int nChannels,
                        void* buffer[],
                        u32 length,
                        NNSSndStrmFormat format,
                        void* arg)
{
#pragma unused(format)

	OSTick      start;
    const void *micAddr;
    u32         offset;
    u8*         micSrc;
    u32         ch;

	
    micSrc = (u8*)arg;

 
    
    if (sts == NNS_SND_STRM_CALLBACK_SETUP) {
        for (ch = 0; ch < nChannels; ++ch) {
            MI_CpuClear8(buffer[ch], length);
        }
        return;
    }
    
#ifdef USE_ECHOCANCEL       
    if (_vWork->firstCallback) {
        MIC_StartAutoSamplingAsync( &(_vWork->micParam), micCallback, NULL);
        _vWork->firstCallback = 0;
    }
#endif    
       
    micAddr = MIC_GetLastSamplingAddress();
    offset  = (u32)((u8*)micAddr - micSrc);

    if ( offset < length ) {
        micSrc = micSrc + length;
    }

#if 0    
    MI_CpuCopy8( micSrc, _test_buffer + _test_buffer_index, length );
    _test_buffer_index += length;
#endif


	if( PAD_DetectFold() )
	{
		// DSを閉じた場合
   		micSrc = _vWork->sSilentBuffer;
	}

    // 音声送受信は受信は常に行います。VADとSSPのステート管理によって、セッションがあるときのみ
    // 実際に送信・受信を行います。
    //
    // lengthは現在オーディオのサンプリングレート・ビット数に応じた32ms分にのみ対応しています。
    // （例：8KHz, 8Bit で256バイト）。それ以外のサイズを渡すとassertionします。
    //
    
    if( _vWork->off_flag == 0 ) 
    {
#if 0	    
    	if( check_hawling((s16*)micSrc, length) )
    	{
    		micSrc = _vWork->sSilentBuffer;
    	}
#endif    	

	    VCT_SendAudio(micSrc, length);
	  
//	    OS_TPrintf("○");  
    }else{
//   	    OS_TPrintf("×");
    }  

    for (ch = 0; ch < nChannels; ++ch) {
        if( !VCT_ReceiveAudio(buffer[ch], length, ch, NULL) )
        {
        	// 音声データを受け取れなかった。
        	// バッファを０クリア
//        	MI_CpuClear32(buffer[ch], length);	
			//OS_TPrintf("音声データを受け取れませんでした。");
        	
        }
    }

#ifdef USE_ECHOCANCEL       
    VCT_SetSpeakerSamples(buffer[0], length);
#endif
     
    
    _vWork->bSendVoice = 2;	  
    return;
}



static void ClearSession(VCTSession *session);

/////////////////////////////////////////////////////////////////////////////////////
//
// 電話をかける。
//

static int startCall( u8 aid )
{
	BOOL ret;
	if (_vWork->session == NULL) {
        VCTSession *session = VCT_CreateSession(aid);
        if (session == NULL) {
            // セッションを使い切っている、またはaidが自分自身の場合
            // CraeteSession が失敗します
            OS_TPrintf("Can't create session!\n");
            return 0;
        }
	
        ret = VCT_Request(session, VCT_REQUEST_INVITE);
        if (ret != VCT_ERROR_NONE){                 // VCT_SUCCESS) {  2006.05.08 k.ohno 定義が変更？したらしいので変更
            OS_TPrintf("Can't request Invite [%d]\n", ret);
            VCT_DeleteSession(session);
            return 0;
        }
        else {
            _vWork->session = session;
        }
        
        return 1;
    }
    
    return 0;
}

static int receiveCall( u8 aid )
{
	BOOL ret;
	if ( _vWork->session != NULL && _vWork->session->state == VCT_STATE_INCOMING ) {
         // 他の端末から会話要求があった場合、ここでOKを返してストリーミングを開始
        
        ret = VCT_Response(_vWork->session, VCT_RESPONSE_OK);
        if (ret != VCT_ERROR_NONE){                 // VCT_SUCCESS) {  2006.05.08 k.ohno 定義が変更？したらしいので変更
            OS_TPrintf("Can't send response OK [%d]\n", ret);
            return 0;
        }
        
        if( !VCT_StartStreaming(_vWork->session) )
        {
	        OS_TPrintf("can't start session! %d\n", _vWork->session->aid);
	        return 0;	        
        } else {
   	        OS_TPrintf("ストリーミングを開始します%d\n", _vWork->session->aid);	        
		}
	        
                
        return 1;
    }
    
    return 0;

}

/////////////////////////////////////////////////////////////////////////////////////
//
// VoiceChatのイベントコールバック関数
//
static void VoiceChatEventCallback(u8 aid, VCTEvent event, VCTSession *session, void *data)
{
#pragma unused(aid, data)
    
    int ret;

    switch (event) {
    case VCT_EVENT_INCOMING:
        if (_vWork->session) {
            OS_TPrintf("Return busy to %d\n", session->aid);
            ret = VCT_Response(session, VCT_RESPONSE_BUSY_HERE);
            VCT_DeleteSession(session);
            break;
        }
            
        OS_TPrintf("Invite From %d\n", session->aid);
        _vWork->session = session;
        break;

    case VCT_EVENT_RESPONDBYE:
        OS_TPrintf("Bye From %d\n", session->aid);
        ret = VCT_Response(session, VCT_RESPONSE_OK);
        if (ret != VCT_ERROR_NONE){                 // VCT_SUCCESS) {  2006.05.08 k.ohno 定義が変更？したらしいので変更
            OS_TPrintf("Can't send response Ok [%d]\n", ret);
        }
        ClearSession(session);
        myvct_free();
        break;

    case VCT_EVENT_DISCONNECTED:
        OS_TPrintf("Disconnected\n");
        ClearSession(session);
        myvct_free();
        break;

    case VCT_EVENT_CANCEL:
        OS_TPrintf("Cancel From %d\n", session->aid);
        ret = VCT_Response(session, VCT_RESPONSE_TERMINATED);
        if (ret != VCT_ERROR_NONE){                 // VCT_SUCCESS) {  2006.05.08 k.ohno 定義が変更？したらしいので変更
            OS_TPrintf("Can't send response RequestTerminated [%d]\n", ret);
        }
        ClearSession(session);
        break;

    case VCT_EVENT_CONNECTED:
        OS_TPrintf("200 OK From %d\n", session->aid);
        if( VCT_StartStreaming(session) )
        {
	        OS_TPrintf("ストリーミングを開始します%d\n", session->aid);	        
	        _vWork->state = VCTSTATE_CALLING;
        } else 
        {
	        OS_TPrintf("can't start session! %d\n", session->aid);	        
        }
        break;

    case VCT_EVENT_REJECT:
        OS_TPrintf("Reject From %d\n", session->aid);
        ClearSession(session);
        break;

    case VCT_EVENT_BUSY:
    case VCT_EVENT_TIMEOUT:
    case VCT_EVENT_ABORT:
        OS_TPrintf("Clear session by '%d'\n", event);
        ClearSession(session);
        break;

    default:
        OS_TPrintf(" not handler (%d)\n", event);
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//
// セッションのクリア
//
static void ClearSession(VCTSession *session)
{
    if (session == _vWork->session) {
        VCT_StopStreaming(session);
        VCT_DeleteSession(session);
        _vWork->session = NULL;
    }
    else {
        SDK_WARNING(FALSE, "What is this session??\n");
        VCT_DeleteSession(session);
    }
}


#ifdef VCFINFO_SHOW
static int s_count = 0;
#endif

// 毎フレーム呼ばれる。
void myvct_main( )
{
    // ゲームフレームに一度呼び出すメイン関数。
	OSTick      start;
    start = OS_GetTick(); 
//    OS_TPrintf("VCT_Main[%d]", OS_TicksToMicroSeconds32(start - _tick_time) );
    _difftime += OS_TicksToMicroSeconds32(start - _tick_time) - 1000 * 1000 / 60;
    if( _difftime < -10000 ) _difftime = 0;
    
    _tick_time = start;    
    VCT_Main();
    
    while( _difftime >= 1000 * 1000 / 60 )
    {
//	    OS_TPrintf("!");
	    VCT_Main();
	    _difftime -= 1000 * 1000 / 60 ;
    }
//    OS_TPrintf("\n");
	if( _vWork->hc_ampchangeflag )
	{
		switch(_vWork->hc_ampgain)
		{
			case 0:
				PM_SetAmpGain(PM_AMPGAIN_160);
				break;
			case 1:
				PM_SetAmpGain(PM_AMPGAIN_80);
				break;
			case 2:
				PM_SetAmpGain(PM_AMPGAIN_40);
				break;
			case 3:
				PM_SetAmpGain(PM_AMPGAIN_20);
				break;
		}
		_vWork->hc_ampchangeflag = 0;
	}
    
    
#ifdef VCFINFO_SHOW
    if( s_count++ % 60 == 0 )
    {
	    VCTVADInfo outInfo;
	    VCT_GetVADInfo( &outInfo );
	    OS_TPrintf("VCTVADInfo[%d][%d(%d,%d)]\n", outInfo.activity, outInfo.level, outInfo.Ts, outInfo.Tn);
    }
#endif	    
	switch( _vWork->state )
	{
		case VCTSTATE_INIT:
		{
			if( mydwc_getaid() == 0 ){
				// 親が電話をかける。
				if( startCall(1) ) {
					// 相手の反応待ち
					_vWork->state = VCTSTATE_WAIT;
				}
			}
			else if(mydwc_getaid() == 1)
			{
				// 親から電話がかかってくるのを待つ
				if( receiveCall(0) )
				{
					// かかってきた
					_vWork->state = VCTSTATE_CALLING;
				}
			}
			break;
		}
		
		case VCTSTATE_WAIT:
		 // 子機が電話に出るのを待っている。
		 break;
		 
		case VCTSTATE_CALLING:
			// 電話中
			break;
	}
}


BOOL myvct_checkData( int aid, void *data, int size )
{
	if( _vWork == NULL ) return FALSE;
	
	if( VCT_HandleData (aid, data, size ) ){
#ifdef VCFINFO_SHOW
	    OS_TPrintf(".");
#endif
	    return TRUE;
    }
	return FALSE;
}

static void* AllocFunc( u32 size )
{
	return mydwc_AllocFunc( NULL, size, 32 );
//	return sys_AllocMemory( _vWork->heapID, size );
}

static void FreeFunc(void *ptr, u32 size)
{
#pragma unused(size)
	mydwc_FreeFunc( NULL, ptr,  size  );
//	sys_FreeMemory(  _vWork->heapID, ptr );
}

static u8 _sRecBuffer[VCHAT_WAVE_SAMPLE * 2 * MAX_CHANNELS] ATTRIBUTE_ALIGN(32);

void *_audio_buffer;

void myvct_init( int heapID, int codec )
{
    u8 cArray[3] = {13, 13, 13};
    u32 length;
    BOOL ret;
       
	if( _vWork == NULL )
	{
		_vWork_temp = sys_AllocMemory( heapID, sizeof(MYVCT_WORK) + 32 );
		_vWork = (MYVCT_WORK *) (( (u32)_vWork_temp + 31 ) / 32 * 32);
		_vWork->heapID = heapID;
		_vWork->sRecBuffer = _sRecBuffer;
		_vWork->disconnectCallback = NULL;
		
		InitFirst();
	}
	
	// マイクの初期化
	
    length = (u32)(VCHAT_SAMPLING_RATE * VCT_AUDIO_FRAME_LENGTH * SAMPLING_BYTE) / 1000;
    
#ifdef USE_ECHOCANCEL	// 2006.7.28 エコーキャンセル対応のため。	     
    {
	    _vWork->micParam.type   = MIC_SAMPLING_TYPE_SIGNED_12BIT;
	    _vWork->micParam.buffer = _vWork->sRecBuffer;
	    _vWork->micParam.size   = length * 2;
	    _vWork->micParam.rate = (u32)((NNS_SND_STRM_TIMER_CLOCK / VCHAT_SAMPLING_RATE) * 64);
	    _vWork->micParam.loop_enable = TRUE;
	    _vWork->micParam.full_callback = NULL;
	    _vWork->micParam.full_arg = NULL;
	    _vWork->firstCallback = 1;
    }
#else
	{			
	    MICAutoParam micParam;
	    MICResult res;		
		    
	    micParam.type   = MIC_SAMPLING_TYPE_SIGNED_12BIT;
	    micParam.buffer = _vWork->sRecBuffer;
	    micParam.size   = length * 2;

	    micParam.rate = (u32)((NNS_SND_STRM_TIMER_CLOCK / VCHAT_SAMPLING_RATE) * 64);
//		micParam.rate = HW_CPU_CLOCK_ARM7 / VCHAT_SAMPLING_RATE;         // サンプリング周期( ARM7のクロック数 )
	    
	    micParam.loop_enable = TRUE;
	    micParam.full_callback = NULL;
	    micParam.full_arg = NULL;
   
	    res = MIC_StartAutoSampling(&micParam);
	    if( res != MIC_RESULT_SUCCESS ){
			OS_TPrintf("マイクのサンプリングを開始できません。(reason = %d)", res);   
	    }
	}
#endif	
        
    // サウンドストリーム再生の初期化。１対１会話限定
    NNS_SndStrmAllocChannel(&_vWork->sSndStream, 1, cArray);
    NNS_SndStrmSetVolume(&_vWork->sSndStream, 0);

    
    ret = NNS_SndStrmSetup(&_vWork->sSndStream,
                           NNS_SND_STRM_FORMAT_PCM16,
                           _vWork->sPlayBuffer,
                           length * 2 * 1,
                           NNS_SND_STRM_TIMER_CLOCK / VCHAT_SAMPLING_RATE,
                           2,
                           SndCallback,
                           _vWork->sRecBuffer);
    SDK_ASSERT(ret);
    
    _vWork->state = VCTSTATE_INIT;
	_vWork->session = NULL;
		
	{
	    VCTConfig config;
	    
	    config.mode         = VCT_MODE_PHONE;
	    config.session      = _vWork->sSession;
	    config.numSession   = 2;
	    config.aid          = mydwc_getaid();
	    config.callback     = VoiceChatEventCallback;
	    config.userData     = NULL;

		config.audioBuffer     = _vWork->stAudioBuffer;
		config.audioBufferSize = sizeof(_vWork->stAudioBuffer);
//		4 * VCT_AUDIO_BUFFER_SIZE;
	    
//	    config.alloc        = AllocFunc;
//	    config.free         = FreeFunc;
//	    config.numBuffer    = VCT_DEFAULT_AUDIO_BUFFER_COUNT;
//	    config.frameLength  = VCT_AUDIO_FRAME_LENGTH;

//	    OS_TPrintf("SDK %s\n", VCT_Version());  // なくなっているようなので削除 2005.05.08 k.ohno
	    
	    if (!VCT_Init(&config)) {
	        OS_TPrintf("ERROR: Can't initialize VoiceChat!!!\n");
	    }	    
	}

	_vWork->off_flag = 0;
	
	VCT_SetCodec( codec );
	StartSoundLoop();
	
#ifdef USE_ECHOCANCEL
    VCT_EnableEchoCancel( TRUE );
#endif
    return;	
}

static void StartSoundLoop()
{
    NNS_SndStrmStart(&_vWork->sSndStream);
}

void myvct_setCodec( int codec )
{
	VCT_SetCodec( codec );
}




//==============================================================================
/**
 * 会話終了要求をだします。まだ通話できていないときは即座に終了します。
 * myvct_setDisconnectCallbackで設定されたコールバックが呼び出されます。
 * @param   none
 * @retval  none
 */
//==============================================================================
void myvct_endConnection(){
	int ret;
	
	// まだ会話要求を出す前で、受け取る前
	if( _vWork->session == NULL || _vWork->state == VCTSTATE_INIT ) {  //sSession を session へ変更 k.ohno
		myvct_free();
		return;
	}
	
	if( _vWork->state == VCTSTATE_WAIT )
	{
		// 会話要求を出してまだ返事が来る前。
		ret = VCT_Request( _vWork->session, VCT_REQUEST_CANCEL );     //sSession を session へ変更 k.ohno
        if (ret != VCT_ERROR_NONE){                 // VCT_SUCCESS) {  2006.05.08 k.ohno 定義が変更？したらしいので変更
			OS_TPrintf("Can't request Cancel [%d]\n", ret);
			myvct_free();
			return;
		}			
	}

	// 会話中。会話終了要求を出す。
	ret = VCT_Request( _vWork->session, VCT_REQUEST_BYE );          //sSession を session へ変更 k.ohno
    if (ret != VCT_ERROR_NONE){                 // VCT_SUCCESS) {  2006.05.08 k.ohno 定義が変更？したらしいので変更
		OS_TPrintf("Can't request Bye [%d]\n", ret);
		myvct_free();
		return;
	}
	return;
}

//==============================================================================
/**
 * 会話終了処理完了コールバックを設定します。
 * 相手から切られた場合も呼び出されます。
 * この関数が呼び出される直前に、vchat.c用のワークが解放されます。
 * @param   none
 * @retval  none
 */
//==============================================================================
void myvct_setDisconnectCallback( void (*disconnectCallback)() )
{
	_vWork->disconnectCallback = disconnectCallback;
}

//==============================================================================
/**
 * ライブラリ終了処理
 * @param   none
 * @retval  none
 */
//==============================================================================
void myvct_free(){
	void (*callback)();
	
	if( _vWork_temp != NULL )
	{
		callback = _vWork->disconnectCallback;
		
		// マイクのサンプリングとストリームをとめる。
	    (void)MIC_StopAutoSampling();
	    NNS_SndStrmStop(&_vWork->sSndStream);	
		NNS_SndStrmFreeChannel(&_vWork->sSndStream);
	
		// VCTライブラリ終了処理	
		VCT_Cleanup();
		
		// メモリを解放
		sys_FreeMemory( _vWork->heapID, _vWork_temp  );
		_vWork_temp = NULL;
		_vWork = NULL;
		
		// コールバックの呼び出し。
		if( callback != NULL ) callback();
	}
}

//==============================================================================
/**
 * 音声のノイズカットレベルを調整します
 * @param   d … 今より閾値を下げるか、上げるか（下げるほど拾いやすくなる）
 * @retval  none
 */
//==============================================================================
void myvct_changeVADLevel(int d)
{
#if 0  // 任天堂吉原さんのTue, 02 May 2006 18:27:13 +0900メールにしたがって削除
    VCTVADInfo outInfo;
	VCT_GetVADInfo( &outInfo );
	if( outInfo.noiseLevel + d <= 0 )
	{
		OS_TPrintf("VADを無効にしました。\n");
		OS_TPrintf("soundLevel = %d, noiseLevel = %d\n", outInfo.soundLevel, outInfo.noiseLevel);
		VCT_EnableVAD( FALSE );
	}
	else
	{
		VCT_SetVADLevel( outInfo.soundLevel + d, outInfo.noiseLevel + d );		
		OS_TPrintf("変更[soundLevel = %d, noiseLevel = %d]\n", outInfo.soundLevel, outInfo.noiseLevel);
		VCT_EnableVAD( TRUE );
	}
	VCT_GetVADInfo( &outInfo );
#endif
}

//==============================================================================
/**
 * 音を拾ったのかどうかを調べる   k.ohno 作成
 * @param   
 * @retval  拾ったらTRUE
 */
//==============================================================================

BOOL myvct_IsSendVoiceAndInc(void)
{
    if(_vWork){
        VCTVADInfo outInfo;
        VCT_GetVADInfo( &outInfo );
        if(outInfo.scale > 2){
            return outInfo.activity;
        }
    }
    return FALSE;
}

void myvct_offVchat()
{
	_vWork->off_flag = 1;	
}

void myvct_onVchat()
{
	_vWork->off_flag = 0;	
}

BOOL myvct_isVchatOn(){
	return ( _vWork->off_flag == 0 );
}