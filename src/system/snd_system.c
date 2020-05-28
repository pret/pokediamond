//==============================================================================================
/**
 * @file	snd_system.c
 * @brief	サウンドシステム
 * @author	Satoshi Nohara
 * @date	2005.11.08
 *
 * ●snd_tool,snd_play,(main)からのみアクセスされる
 * snd_system
 *     |
 *     |
 * ●データセットなどの処理をまとめた	●再生、停止などの処理をまとめた
 * snd_tool								snd_play
 *     |
 *     |
 * ●各種デモから呼ばれる(主にフィールドイベント)
 * fld_bgm
 *
 * ＜メモ＞
 * 戦闘でゲームオーバーになって、ポケセンに戻る時などは、
 * Snd_PauseClearAllを呼んで、ポーズフラグをクリアしないといけない！
 */
//==============================================================================================
#include "common.h"
#include "snd_system.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "src_os_print.h"

#include "savedata/savedata.h"
#include "savedata/perapvoice.h"
#include "savedata/config.h"


//==============================================================================================
//
//	定義
//
//==============================================================================================
//sound_data.smapのサイズより少し大きめに確保する
#define SOUND_HEAP_SIZE		(0xbbc00)				//サウンドヒープサイズ(約750k)
//#define SOUND_HEAP_SIZE	(0xbd000)				//サウンドヒープサイズ(約750k)
//#define SOUND_HEAP_SIZE	(0xc0000)				//サウンドヒープサイズ(約750k)
//#define SOUND_HEAP_SIZE	(0x80000)				//サウンドヒープサイズ(約500k)


//==============================================================================================
//
//	構造体宣言
//
//==============================================================================================
//サウンドシステムワーク
struct _SND_WORK{

	//システム関連
	NNSSndArc arc;									//サウンドアーカイブ
	NNSSndHeapHandle heap;							//サウンドヒープハンドル
	u8 sndHeap[ SOUND_HEAP_SIZE ];					//サウンドヒープ
	NNSSndHandle Handle[ SND_HANDLE_MAX ];			//サウンドハンドル
	NNSSndWaveOutHandle sWaveOutHandle[2];			//波形ハンドル
	const NNSSndArcBankInfo* info;					//バンク情報構造体

	//キャプチャ関連
	u8 sCaptureBuffer[ CAPTURE_BUFSIZE ] ATTRIBUTE_ALIGN(32);	//キャプチャバッファ
	EffectCallbackInfo callbackInfo;				//エフェクトのコールバック変数

#ifdef STREAM_ON
	//ストリーム関連
	NNSSndStrmHandle strmHandle;
#endif
	
	u16 seq;										//シーケンス
	u8	ctrl_bgm_flag;								//フィールドBGM固定フラグ(セーブされない)
	u8	dmy101;

	int fade_count;									//フェードカウンター
	int next_wait;									//次のBGMを鳴らすまでのウェイト
	int next_frame;									//次のBGMのフェードインフレーム

	u16 now_bgm_no;									//今のBGMナンバー
	u16 next_bgm_no;								//次のBGMナンバー

	u8	field_pause_flag;							//PLAYER_FIELDをポーズしているかフラグ
	u8	bgm_pause_flag;								//PLAYER_BGMをポーズしているかフラグ
	u16 me_wait;									//MEウェイト

	u8  reverse_flag;								//逆再生使用フラグ
	u8  waveout_ch_normal_flag;						//波形で使用するCHを確保したかフラグ
	u8  waveout_ch_chorus_flag;						//波形で使用するCHを確保したかフラグ(CHORUS)
	u8  chorus_flag;								//コーラス使用フラグ

	u8  bank_flag;									//昼か夜かフラグ
	//u8	wavearc_count;							//読み込んだ波形アーカイブ数
	u8	filter_size;								//フィルターサイズ
	u8	scene_main;									//現在のメインシーン
	u8  scene_sub;									//現在のサブシーン

	int heap_save[SND_HEAP_SAVE_MAX];				//サウンドヒープ階層レベル

	u8	perap_play_flag;							//ペラップの録音した鳴き声を再生しているかフラグ
	u8	perap_default_flag;							//ペラップのデフォルトの鳴き声を再生するフラグ
	u16	zone_bgm;									//ゾーンBGMナンバー

	const SNDWaveData* wave_data;					//波形データのポインタ

	void* reverse_buf;								//逆再生用のバッファのポインタ

	int volume;										//BGMボリューム

	TCB_PTR length_tcb;								//鳴き声再生時間TCB

	PERAPVOICE*	my_perap_ptr;						//自分のぺラップボイスのポインタ
	PERAPVOICE*	perap_ptr[4];						//ぺラップボイスのポインタ
};


//==============================================================================================
//
//	定義
//
//==============================================================================================


//==============================================================================================
//
//	変数
//
//==============================================================================================
static SND_WORK snd_work;							//サウンドシステムワーク
static int snd_status;								//サウンドステータス

//使用しないかも。。
static NNSSndCaptureOutputEffectType stereo_mono;	//ステレオかモノラルか

//デバック用
u32 aki_size;										//サウンドヒープサイズ確認


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void Snd_AllInit( PERAPVOICE* perap, CONFIG* config );
void Snd_Main(void);
static void Snd_StatusCall(void);
void Snd_StatusSet( int status );
BOOL Snd_StatusCheck( int chg_status );
static BOOL Snd_MeUseCheck(void);

SND_WORK* Snd_GetSystemAdrs();
void* Snd_GetParamAdrs( int type );

int Snd_HeapSaveState(int* heap_lv);
void Snd_HeapLoadState( int level );
void Snd_UseHeapSizeOsPrint(void);
NNSSndHeapHandle* Snd_HeapHandleGet(void);

BOOL Snd_ArcLoadGroup( u16 no );
BOOL Snd_ArcLoadSeq( u16 no );
BOOL Snd_ArcLoadSeqEx( u16 no, u32 flag );
BOOL Snd_ArcLoadSeqArc( u16 no );
BOOL Snd_ArcLoadWaveArc( u16 no );
BOOL Snd_ArcLoadBank( u16 no );

NNSSndHandle * Snd_HandleGet( int type );
int Snd_GetHandleNoByPlayerNo( int player_no );

void Snd_PlayerPauseAll( BOOL flag );

//ローカル関数
static void Snd_WorkInit( SND_WORK* wk );
static void Snd_HandleInit( SND_WORK* wk );
static void Snd_GameStartLoad( SND_WORK* wk );
static void Snd_MicInit(void);

//PLAYER_BGMの停止、ハンドルリリース
static void Snd_PlayerBgmStop( void );


//==============================================================================================
//
//	プログラム
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	サウンド初期化
 *
 * @param	none
 *
 * @retval	none
 *
 * 他の全てのサウンド関数より先に呼びだしてください。
 * ただし、あらかじめ、OSを初期化しておく必要があります。 
 *
 * IRQ割り込みは有効にしてください。また、この関数の後で、
 * OS_SetIrqMask関数 などで割り込みの設定を上書きしないようにしてください。 
 */
//--------------------------------------------------------------
void Snd_AllInit( PERAPVOICE* perap, CONFIG* config )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	//Snd_LocalWorkCreate();				//サウンドローカルワーク確保
	
    NNS_SndInit();							//サウンドライブラリの初期化

	Snd_MicInit();							//MIC初期化

	Snd_WorkInit(wk);						//サウンドシステムワーク初期化

	//サウンドヒープの作成
    wk->heap = NNS_SndHeapCreate( &wk->sndHeap, sizeof(wk->sndHeap) );

	//サウンドアーカイブの初期化
    NNS_SndArcInit( &wk->arc, "data/sound/sound_data.sdat", wk->heap, FALSE );

	//プレイヤーのセットアップ
	//サウンドアーカイブ中で定義されているプレイヤー設定に基づきセットアップされる
    (void)NNS_SndArcPlayerSetup( wk->heap );

#ifdef STREAM_ON
	NNS_SndArcStrmInit( STREAM_THREAD_PRIO, wk->heap );

    NNS_SndStrmHandleInit( &wk->strmHandle );
#endif

    //サウンドハンドル初期化
    Snd_HandleInit(wk);

#ifdef SOUND_OS_PRINT_ON
	//aki_size = NNS_SndHeapGetFreeSize( wk->heap );
	aki_size = NNS_SndHeapGetSize( wk->heap );
	OS_Printf( "\n\n//========================================\n" );
	OS_Printf( "//\tサウンド\n" );
	OS_Printf( "//========================================\n" );
	OS_Printf( "＜総容量＞サウンドヒープ = %d\n", aki_size );

	OS_Printf( "\n↓プレイヤーヒープ割り当て分\n" );
	Snd_UseHeapSizeOsPrint();							//追加したサウンドヒープの容量を出力する

	OS_Printf( "＜ゲーム開始時のサウンドデータロード＞\n" );
#endif

	Snd_GameStartLoad(wk);								//ゲーム開始時のサウンドデータのロード

	//出力エフェクト設定
	stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL;	//通常のステレオモード
	//Snd_CaptureStartOutputEffect( stereo_mono );
	
	//自分のぺラップのポインタを常にもっておく(06.04.20)
	wk->my_perap_ptr = perap;

	//コンフィグ設定に変更
	Snd_SetMonoFlag( config->sound_mode );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドフレームワーク
 *
 * @param	none
 *
 * @retval	none
 *
 * 1フレームに1度呼び出しさえすれば、どこでコールしても構わない
 */
//--------------------------------------------------------------
void Snd_Main(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	//ME使用中の時は、BGMステータス処理はしない！
	if( Snd_MeUseCheck() == FALSE ){

		//フェードカウントデクリメント
		if( wk->fade_count > 0 ){
			wk->fade_count--;
		}
	
		//サウンドステータス呼び出し
		Snd_StatusCall();
	}

	//ぺラップの録音した鳴き声を再生しているかフラグが立っていたら、
	//波形再生が終了しているかチェックして、波形再生チャンネルを開放する
	Snd_MainPerapCheck();

	NNS_SndMain();
	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドステータス呼び出し
 *
 * @param	status		ステータス(snd_system.h参照)
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_StatusCall(void)
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	switch( snd_status ){

	//初期化
	//case SND_STATUS_INIT:
	//	break;

	//停止
	case SND_STATUS_STOP:
		//何もしない
		break;

	//
	//case SND_STATUS_PLAYSTART:
	//	break;

	//再生
	case SND_STATUS_PLAY:
		Snd_StatusSet( SND_STATUS_PLAING );					//ステータス(再生中)
		break;

	//再生中
	case SND_STATUS_PLAING:
		//何もしない
		break;

	//フェードイン
	case SND_STATUS_FADEIN:
		if( Snd_FadeCheck() == 0 ){							//フェード終了していたら
			Snd_StatusSet( SND_STATUS_PLAING );				//ステータス(再生中)
		}
		break;

	//フェードアウト
	case SND_STATUS_FADEOUT:
		//無音にする時と、音量小さくする時がある！
		if( Snd_FadeCheck() == 0 ){							//フェード終了していたら
			Snd_StatusSet( SND_STATUS_PLAING );				//ステータス(再生中)
		}
		break;

	//
	//case SND_STATUS_FADENEXT:
	//	break;

	//
	//case SND_STATUS_FADENEXTFADE:
	//	break;

	//フェードアウト → BGM再生
	case SND_STATUS_FADEOUT_NEXT_PLAY:
		if( Snd_FadeCheck() == 0 ){							//フェード終了待ち
			if( Snd_NextWaitCheck() == 0 ){					//次のBGMを鳴らすまでのウェイトチェック

				//PLAYER_BGMを鳴らしながらマップ遷移した時の対応
				//PLAYER_BGMをポーズしておきたい状況は、
				//MEに限定され、MEは必ず停止、ポーズ解除がくる！
				//ここで必ず、PLAYER_BGMを停止しても問題ない！
				Snd_PlayerBgmStop();

				Snd_BgmPlay( wk->next_bgm_no );				//BGM再生(ステータス＝再生)
			}
		}
		break;

	//フェードアウト → BGMフェードイン
	case SND_STATUS_FADEOUT_NEXT_FADEIN:
		if( Snd_FadeCheck() == 0 ){							//フェード終了待ち
			if( Snd_NextWaitCheck() == 0 ){					//次のBGMを鳴らすまでのウェイトチェック

				//PLAYER_BGMを鳴らしながらマップ遷移した時の対応
				//PLAYER_BGMをポーズしておきたい状況は、
				//MEに限定され、MEは必ず停止、ポーズ解除がくる！
				//ここで必ず、PLAYER_BGMを停止しても問題ない！
				Snd_PlayerBgmStop();

				Snd_BgmPlay( wk->next_bgm_no );				//BGM再生(ステータス＝再生)

				//フェードイン(ステータス＝フェードイン)
				Snd_BgmFadeIn( BGM_VOL_MAX, wk->next_frame, BGM_FADEIN_START_VOL_MIN );
			}
		}
		break;

	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドステータスセット
 *
 * @param	status		ステータス(snd_system.h参照)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_StatusSet( int status )
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	wk->seq = 0;
	snd_status = status;

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n現在のサウンドステータス = %d\n\n", snd_status );
#endif

	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドステータスチェック
 *
 * @param	chg_status	ステータス(snd_system.h参照)
 *
 * @retval	"TRUE=許可、FALSE=不可"
 */
//--------------------------------------------------------------
BOOL Snd_StatusCheck( int chg_status )
{
	//ステータス(フェードアウト→再生)の時に、トラックフェードに切り替えることは不可！
	if( (snd_status == SND_STATUS_FADEOUT_NEXT_PLAY) && (chg_status == SND_STATUS_TRACKFADE ) ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	ME使用中かチェック
 *
 * @param	none
 *
 * @retval	"TRUE=使用中、FALSE=使用していない"
 */
//--------------------------------------------------------------
static BOOL Snd_MeUseCheck(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	if( Snd_PlayerCountPlayingSeq(PLAYER_ME) != 0 ){ return TRUE; }		//MEシーケンスチェック
	if( wk->me_wait != 0 ){ return TRUE; }								//MEウェイトチェック

	return FALSE;
}


//==============================================================================================
//
//	サウンドシステムワークアクセス関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	サウンドシステムワークのアドレスを取得
 *
 * @param	none
 *
 * @retval	"サウンドシステムワークのアドレス"
 */
//--------------------------------------------------------------
SND_WORK* Snd_GetSystemAdrs()
{
	return (SND_WORK*)&snd_work;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドシステムワークのメンバのアドレスを取得
 *
 * @param	type	メンバID
 *
 * @retval	"メンバのアドレス"
 */
//--------------------------------------------------------------
void* Snd_GetParamAdrs( int type )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	switch( type ){

	case SND_W_ID_CTRL_BGM_FLAG:				//フィールドBGM固定フラグ
		return &wk->ctrl_bgm_flag;

	case SND_W_ID_WAVEOUT_HANDLE_NORMAL:		//波形ハンドル
		return &wk->sWaveOutHandle[0];

	case SND_W_ID_WAVEOUT_HANDLE_CHORUS:		//波形ハンドル
		return &wk->sWaveOutHandle[1];

	case SND_W_ID_BANK_INFO:					//バンク情報構造体
		return &wk->info;

	case SND_W_ID_CAPTURE_BUF:					//キャプチャバッファ
		return &wk->sCaptureBuffer;

	case SND_W_ID_CALLBACK_INFO:				//エフェクトのコールバック変数
		return &wk->callbackInfo;

	case SND_W_ID_FADE_COUNT:					//フェードカウンター
		return &wk->fade_count;

	case SND_W_ID_NEXT_WAIT:					//次のBGMを鳴らすまでのウェイト
		return &wk->next_wait;

	case SND_W_ID_NEXT_FRAME:					//次のBGMのフェードインフレーム数
		return &wk->next_frame;

	case SND_W_ID_NOW_BGM_NO:					//今のBGMナンバー
		return &wk->now_bgm_no;					//セーブする必要あり！(あとで移動する)

	case SND_W_ID_NEXT_BGM_NO:					//次のBGMナンバー
		return &wk->next_bgm_no;				//セーブする必要あり！(あとで移動する)

	case SND_W_ID_FIELD_PAUSE_FLAG:				//PLAYER_FIELDをポーズしているかフラグ
		return &wk->field_pause_flag;

	case SND_W_ID_BGM_PAUSE_FLAG:				//PLAYER_BGMをポーズしているかフラグ
		return &wk->bgm_pause_flag;

	case SND_W_ID_ME_WAIT:						//MEウェイト
		return &wk->me_wait;

	case SND_W_ID_REVERSE_FLAG:					//逆再生使用フラグ
		return &wk->reverse_flag;

	case SND_W_ID_WAVEOUT_CH_NORMAL_FLAG:		//波形で使用するCHを確保したかフラグ
		return &wk->waveout_ch_normal_flag;

	case SND_W_ID_WAVEOUT_CH_CHORUS_FLAG:		//波形で使用するCHを確保したかフラグ(CHORUS)
		return &wk->waveout_ch_chorus_flag;

	case SND_W_ID_CHORUS_FLAG:					//コーラス使用フラグ
		return &wk->chorus_flag;

	case SND_W_ID_BANK_FLAG:					//バンク切り替えるかフラグ
		return &wk->bank_flag;

	case SND_W_ID_FILTER_SIZE:					//フィルターサイズ
		return &wk->filter_size;

	case SND_W_ID_SCENE_MAIN:					//現在のメインシーン
		return &wk->scene_main;

	case SND_W_ID_SCENE_SUB:					//現在のサブシーン
		return &wk->scene_sub;

	case SND_W_ID_HEAP_SAVE_START:				//サウンドヒープ階層レベル
		return &wk->heap_save[SND_HEAP_SAVE_START];

	case SND_W_ID_HEAP_SAVE_GLOBAL:				//サウンドヒープ階層レベル
		return &wk->heap_save[SND_HEAP_SAVE_GLOBAL];

	case SND_W_ID_HEAP_SAVE_BGM_BANK:			//サウンドヒープ階層レベル
		return &wk->heap_save[SND_HEAP_SAVE_BGM_BANK];

	case SND_W_ID_HEAP_SAVE_SE:					//サウンドヒープ階層レベル
		return &wk->heap_save[SND_HEAP_SAVE_SE];

	case SND_W_ID_HEAP_SAVE_BGM:				//サウンドヒープ階層レベル
		return &wk->heap_save[SND_HEAP_SAVE_BGM];

	case SND_W_ID_HEAP_SAVE_SUB_SE:				//サウンドヒープ階層レベル
		return &wk->heap_save[SND_HEAP_SAVE_SUB_SE];

	case SND_W_ID_HEAP_SAVE_ME:					//サウンドヒープ階層レベル
		return &wk->heap_save[SND_HEAP_SAVE_ME];

	case SND_W_ID_PERAP_PLAY_FLAG:				//ペラップの録音した鳴き声を再生しているかフラグ
		return &wk->perap_play_flag;

	case SND_W_ID_PERAP_DEFAULT_FLAG:			//ペラップのデフォルトの鳴き声を再生するフラグ
		return &wk->perap_default_flag;

	case SND_W_ID_ZONE_BGM:						//ゾーンBGMナンバー
		return &wk->zone_bgm;

	case SND_W_ID_WAVE_DATA:					//波形データのポインタ
		return &wk->wave_data;

	case SND_W_ID_REVERSE_BUF:					//逆再生用のバッファのポインタ
		return &wk->reverse_buf;

	case SND_W_ID_LENGTH_TCB:					//鳴き声再生時間TCB
		return &wk->length_tcb;

	case SND_W_ID_MY_PERAP_PTR:					//自分のぺラップボイスのポインタ
		return &wk->my_perap_ptr;

	case SND_W_ID_PERAP_PTR1:					//ぺラップボイスのポインタ
		return &wk->perap_ptr[0];

	case SND_W_ID_PERAP_PTR2:					//ぺラップボイスのポインタ
		return &wk->perap_ptr[1];

	case SND_W_ID_PERAP_PTR3:					//ぺラップボイスのポインタ
		return &wk->perap_ptr[2];

	case SND_W_ID_PERAP_PTR4:					//ぺラップボイスのポインタ
		return &wk->perap_ptr[3];
	};

	GF_ASSERT( (0) && "引数が不正です！" );
	return NULL;
}


//==============================================================================================
//
//	ヒープメモリ関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	メモリの状態を保存
 *
 * @param	heap_lv		保存後の状態の階層レベルをとっておくワークへのポインタ
 *						(NULLだと何もしない)
 *
 * @retval	"保存後の階層レベル、失敗すると-1"
 *
 * ヒープ作成直後の階層レベルは0で、この関数を呼ぶ毎に、階層レベルが１つ増えます。 
 * NNS_SndHeapLoadState関数を呼びだすことで、
 * 指定した階層レベルの保存直後の状態に復元させることができます。 
 *
 * 状態の保存には、ヒープを少し消費します。ヒープの空き容量が少ない場合は、関数に失敗します。 
 */
//--------------------------------------------------------------
int Snd_HeapSaveState( int* heap_lv )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ret = NNS_SndHeapSaveState(wk->heap);

	//失敗チェック
	if( ret == -1 ){
		GF_ASSERT( (0) && "NNS_SndHeapSaveState ERROR！" );
	}

	if( heap_lv != NULL ){
		*heap_lv = ret;
	}

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "状態保存にはヒープを消費します\n保存後の階層レベル = %d\n", ret );
	Snd_UseHeapSizeOsPrint();						//状態保存にはヒープを消費する
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	メモリの状態を復元
 *
 * @param	level	復元する階層レベル
 *
 * @retval	none
 *
 * NNS_SndHeapSaveState関数を呼んだ直後の状態に戻すことが出来る
 * すなわち、NNS_SndHeapSaveState関数を呼んだ後にロードしたデータが削除される
 * この時、ロード済みサウンドデータを使って再生されている音は止まりません
 */
//--------------------------------------------------------------
void Snd_HeapLoadState( int level )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	NNS_SndHeapLoadState( wk->heap, level );

#ifdef SOUND_OS_PRINT_ON
	Snd_UseHeapSizeOsPrint();	//追加したサウンドヒープの容量を出力する
#endif

	return;
}

//--------------------------------------------------------------
/**
 * @brief	追加したサウンドヒープの容量と、空き容量を出力する
 *
 * @param	none
 *
 * @retval	none
 *
 * プレイヤーヒープを確保すると、その分容量が減っているので注意！
 */
//--------------------------------------------------------------
void Snd_UseHeapSizeOsPrint(void)
{
	u32 size;
	SND_WORK* wk = Snd_GetSystemAdrs();

#ifdef SOUND_OS_PRINT_ON
	size = NNS_SndHeapGetFreeSize( wk->heap );							//現在の空き容量を取得

	//サイズ比較
	if( aki_size < size ){
		OS_Printf( "開放したサウンドヒープ量 = %d\n", (size-aki_size) );//開放した容量を表示
	}else if( aki_size == size ){
		OS_Printf( "サウンドヒープ量に変化なし\n" );
	}else{
		OS_Printf( "追加したサウンドヒープ量 = %d\n", (aki_size-size) );//追加した容量を表示
	}

	aki_size = size;
	OS_Printf( "サウンドヒープの空き容量 = %d\n\n", aki_size );			//空き容量を表示
#endif
	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドヒープのアドレスを取得
 *
 * @param	none
 *
 * @retval	"サウンドヒープのアドレス"
 */
//--------------------------------------------------------------
NNSSndHeapHandle* Snd_HeapHandleGet(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	return &wk->heap;
}


//==============================================================================================
//
//	データロード関連
//
//	snd_tool.c
//	FILED,BATTLEなどのデータセット関数から主に呼ばれる
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	グループロード
 *
 * @param	no		グループナンバー
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadGroup( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ret = NNS_SndArcLoadGroup( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "＜●グループロード＞ グループNo = %d 成功=TRUE、失敗=FALSE 結果=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//追加したサウンドヒープの容量を出力する
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスデータ、バンクデータ、波形データを(同時)にロード
 *
 * @param	no		シーケンスナンバー
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadSeq( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadSeq( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "＜▲シーケンスロード＞ シーケンスNo = %d 成功=TRUE、失敗=FALSE 結果=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//追加したサウンドヒープの容量を出力する
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスデータ、バンクデータ、波形データを(選んで)ロード
 *
 * @param	no		シーケンスナンバー
 * @param	flag	どのデータをロードするか
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 *
 * ＜ロード定義＞
 * シーケンスデータ	NNS_SND_ARC_LOAD_SEQ 
 * バンクデータ		NNS_SND_ARC_LOAD_BANK
 * 波形アーカイブ	NNS_SND_ARC_LOAD_WAVE
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadSeqEx( u16 no, u32 flag )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadSeqEx( no, flag, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "＜▲シーケンスロード特殊＞ シーケンスNo = %d 成功=TRUE、失敗=FALSE 結果=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//追加したサウンドヒープの容量を出力する
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスアーカイブをロード
 *
 * @param	no		シーケンスアーカイブナンバー
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 *
 * シーケンスアーカイブは、複数のバンクと関連があるため、
 * 自動的にバンクデータや波形データはロードされない
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadSeqArc( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadSeqArc( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "＜★シーケンスARCロード＞ SEQ_ARCNo = %d 成功=TRUE、失敗=FALSE 結果=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//追加したサウンドヒープの容量を出力する
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	波形アーカイブをロード
 *
 * @param	no		波形アーカイブナンバー
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadWaveArc( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadWaveArc( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf("＜◆波形アーカイブロード＞ バンクNo = %d 成功=TRUE、失敗=FALSE 結果=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//追加したサウンドヒープの容量を出力する
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	バンクデータをロード(必要な波形データもロードされる)
 *
 * @param	no		バンクナンバー
 * @param	heap	ヒープアドレス
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_ArcLoadBank( u16 no )
{
	int ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

    ret = NNS_SndArcLoadBank( no, wk->heap );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "＜■バンクロード＞ バンクNo = %d 成功=TRUE、失敗=FALSE 結果=%d\n", no, ret );
	Snd_UseHeapSizeOsPrint();							//追加したサウンドヒープの容量を出力する
#endif

	return ret;
}


//==============================================================================================
//
//	サウンドハンドル、波形ハンドル関連
//
//	snd_play.c
//	BGM,ME,SE,PMVOICEの再生関数から主に呼ばれる
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	サウンドハンドルのアドレスを取得
 *
 * @param	type	サウンドハンドルタイプ
 *
 * @retval	"サウンドハンドルのアドレス"
 */
//--------------------------------------------------------------
NNSSndHandle * Snd_HandleGet( int type )
{
	SND_WORK* wk = Snd_GetSystemAdrs();

	if( type >= SND_HANDLE_MAX ){
		GF_ASSERT( (0) && "サウンドハンドルタイプが不正です！" );
		type = SND_HANDLE_FIELD;
	}

	return &wk->Handle[type];
}

//--------------------------------------------------------------
/**
 * @brief	プレイヤーナンバーから、ハンドルナンバー取得(ハンドルのアドレスではないので注意！)
 *
 * @param	player_no	プレイヤーナンバー
 *
 * @retval	"ハンドルナンバー"
 */
//--------------------------------------------------------------
int Snd_GetHandleNoByPlayerNo( int player_no )
{
	int type;

	//SEハンドルナンバー取得
	switch( player_no ){

	case PLAYER_FIELD:
		type = SND_HANDLE_FIELD;				//フィールドBGMサウンドハンドル
		break;
		
	case PLAYER_PV:
		type = SND_HANDLE_PMVOICE;				//ポケモン鳴き声サウンドハンドル
		break;

	case PLAYER_ME:
		type = SND_HANDLE_ME;					//MEサウンドハンドル
		break;

	case PLAYER_SE_1:
		type = SND_HANDLE_SE_1;
		break;

	case PLAYER_SE_2:
		type = SND_HANDLE_SE_2;
		break;

	case PLAYER_SE_3:
		type = SND_HANDLE_SE_3;
		break;

	case PLAYER_SE_4:
		type = SND_HANDLE_SE_4;
		break;

	case PLAYER_BGM:
		type = SND_HANDLE_BGM;					//フィールド以外のBGMハンドル
		break;

	//case PLAYER_CHORUS:						//PLAYERとしては存在しない！
	//	type = SND_HANDLE_CHORUS;				//コーラス(鳴き声専用)ハンドル
	//	break;

	default:
		GF_ASSERT( (0) && "プレイヤーナンバーが不正です！" );
		type = SND_HANDLE_SE_1;					//エラー回避
		break;
	};

	return type;
}


//==============================================================================================
//
//	シーケンス関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	全ての再生中のシーケンスを一時停止または再開
 *
 * @param	flag	TRUE=一時停止、FALSE=再開
 *
 * @retval	none
 *
 * サウンドハンドルが無効の場合は、何もしません。 
 * 状態が変わらない場合、例えば、すでに一時停止状態の時に一時停止を行っても、何もしません。 
 *
 * 注意
 * 一時停止を行うと、発音中の音は強制的に停止させられます。
 * 再開を行っても、発音中の音が続きから再生されることはありませんので注意してください。
 * 再開後は、次のノートオンから音が鳴り始めます。 
 */
//--------------------------------------------------------------
void Snd_PlayerPauseAll( BOOL flag )
{
	NNS_SndPlayerPauseAll( flag );
	return;
}


//==============================================================================================
//
//	ローカル関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	サウンドシステムワークの初期化
 *
 * @param	wk		SND_WORK型のアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_WorkInit( SND_WORK* wk )
{
	int i;

	memset( wk, 0, sizeof(SND_WORK) );

	//階層レベル
	for( i=0; i < SND_HEAP_SAVE_MAX ;i++ ){
		//開始=1,常駐=2,BGM_BANK=3,SE=4,BGM=5,SUB_SE=6,ME=7
		wk->heap_save[i] = (i+1);						//初期値セット
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドハンドル初期化
 *
 * @param	wk		SND_WORK型のアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_HandleInit( SND_WORK* wk )
{
	int i;

	for( i=0; i < SND_HANDLE_MAX ;i++ ){
		NNS_SndHandleInit( &wk->Handle[i] );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	ゲーム開始時のサウンドデータのロード
 *
 * @param	wk		SND_WORK型のアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_GameStartLoad( SND_WORK* wk )
{
	int ret;

	//グループロード(成功=TRUE、失敗=FALSE)
	
	Snd_HeapSaveState(&wk->heap_save[SND_HEAP_SAVE_START]);		//階層保存(全て消す時に使用)
	ret = Snd_ArcLoadGroup( GROUP_GLOBAL );	//常駐

	//basic.bnkは、全常駐にしている
	
	Snd_HeapSaveState(&wk->heap_save[SND_HEAP_SAVE_GLOBAL]);	//階層保存(常駐以外を消す時に使用)

	//↓ここは、タイトル曲を読み込むことになる！
	//シーン(場面)が変わる時のサウンドデータセット
	//Snd_SceneDataSet( SND_SCENE_FIELD, SEQ_DP_TITLE, 0 );
	//title.cに同じ処理を入れてあるので外した

	return;
}

//--------------------------------------------------------------
/**
 * @brief	マイク初期化(とりあえずゲインなど固定)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_MicInit(void)
{
	//MIC_Init関数の初期化は、2回目以降の呼び出しは無効になるように、
	//内部フラグでチェックされています
    MIC_Init();								//MIC_API初期化
    
	//OS_Init()を呼ぶ場合は、その中から呼ばれますので必要ありません。
    //PM_Init();							//PMICマネージャ初期化(OS_INIT内でも呼ばれている)
	
    (void)PM_SetAmp( PM_AMP_ON );			//プログラマブルゲインアンプのスイッチON
    (void)PM_SetAmpGain( PM_AMPGAIN_80 );	//プログラマブルゲインアンプのゲインを設定

	return;
}

//--------------------------------------------------------------
/**
 * @brief	PLAYER_BGMの停止
 *
 * @param	none
 *
 * @retval	none
 *
 * サウンドハンドルに結びつけられているシーケンスを解放します。
 * シーケンスが結びつけられていない場合は、何もしません。
 *
 * PLAYERに対してのみ停止、リリースをしている
 */
//--------------------------------------------------------------
static void Snd_PlayerBgmStop( void )
{
	NNS_SndPlayerStopSeqByPlayerNo( PLAYER_BGM, 0 );
	NNS_SndHandleReleaseSeq( Snd_HandleGet(SND_HANDLE_BGM) );
	return;
}


