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
#define MAX_SAMPLING_TIME   64     // ms
#define MAX_CHANNELS 1
#define VCHAT_WAVE_SAMPLE ((int) (VCHAT_SAMPLING_RATE * MAX_SAMPLING_TIME * SAMPLING_BYTE) / 1000)

//#define VCFINFO_SHOW
//#define VCT_ERROR_NONE (VCT_SUCCESS)


// マイクゲインを設定
#define MY_AMPGAIN PM_AMPGAIN_160
//#define MY_AMPGAIN PM_AMPGAIN_80
//#define MY_AMPGAIN PM_AMPGAIN_40
//#define MY_AMPGAIN PM_AMPGAIN_20


typedef struct{
	u8 stAudioBuffer[VCT_AUDIO_BUFFER_SIZE * VCT_DEFAULT_AUDIO_BUFFER_COUNT ];
	u8 sPlayBuffer[VCHAT_WAVE_SAMPLE * 2 * MAX_CHANNELS];
//	u8  sRecBuffer[VCHAT_WAVE_SAMPLE * 2 * MAX_CHANNELS];
	u8  *sRecBuffer;
	
	void (*disconnectCallback)();
	VCTSession sSession[2];
	int state;
	int heapID;
	struct NNSSndStrm sSndStream;
	VCTSession *session;
    u8 bSendVoice;
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
static void InitFirst()
{
    OS_TPrintf("Init sound system\n");
    // マイク関連の初期化
    //
    MIC_Init();
    PM_Init();
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

    OS_TPrintf("Init sound system done.\n");
}



//
// 音声処理コールバック（NitroSystem NNS_SndStrmを利用）
//
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

    start = OS_GetTick();
    
    // マイクからの入力を取得
    //
    micAddr = MIC_GetLastSamplingAddress();
    offset  = (u32)((u8*)micAddr - micSrc);

    if ( offset < length ) {
        micSrc = micSrc + length;
    }

    // 音声送受信は受信は常に行います。VADとSSPのステート管理によって、セッションがあるときのみ
    // 実際に送信・受信を行います。
    //
    // lengthは現在オーディオのサンプリングレート・ビット数に応じた32ms分にのみ対応しています。
    // （例：8KHz, 8Bit で256バイト）。それ以外のサイズを渡すとassertionします。
    //
    VCT_SendAudio(micSrc, length);

    for (ch = 0; ch < nChannels; ++ch) {
        VCT_ReceiveAudio(buffer[ch], length, ch, NULL);
    }
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
    VCT_Main();
    
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
			else
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
	    OS_TPrintf(".");
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

	VCT_SetCodec( codec );
	StartSoundLoop();

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
	if( _vWork->sSession == NULL || _vWork->state == VCTSTATE_INIT ) {
		myvct_free();
		return;
	}
	
	if( _vWork->state == VCTSTATE_WAIT )
	{
		// 会話要求を出してまだ返事が来る前。
		ret = VCT_Request( _vWork->sSession, VCT_REQUEST_CANCEL );
        if (ret != VCT_ERROR_NONE){                 // VCT_SUCCESS) {  2006.05.08 k.ohno 定義が変更？したらしいので変更
			OS_TPrintf("Can't request Cancel [%d]\n", ret);
			myvct_free();
			return;
		}			
	}

	// 会話中。会話終了要求を出す。
	ret = VCT_Request( _vWork->sSession, VCT_REQUEST_BYE );
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

