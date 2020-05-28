//==============================================================================================
/**
 * @file	snd_perap.c
 * @brief	サウンド ペラップ関数
 * @author	Satoshi Nohara
 * @date	2006.04.15
 */
//==============================================================================================
#include "common.h"
#include "snd_system.h"
#include "system/snd_tool.h"
#include "savedata/savedata.h"				//
#include "savedata/perapvoice.h"			//
#include "poketool/monsno.h"


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
BOOL Snd_MainPerapCheck( void );

BOOL Snd_PerapVoiceCheck( const PERAPVOICE* perap );
BOOL Snd_PerapVoicePlayingCheck( const PERAPVOICE* perap );

BOOL Snd_PerapVoicePlaySub( const PERAPVOICE* perap, u32 sex, int vol, int pan );
void Snd_PerapVoiceStop( void );

MICResult Snd_PerapVoiceRecStart( void );
MICResult Snd_PerapVoiceRecStop( void );

void Snd_PerapVoiceDataSave( PERAPVOICE* perap );

void Snd_PerapVoiceDefaultFlagSet( u8 no );

BOOL Snd_PerapVoicePlay( PERAPVOICE* perap, u32 sex, int vol, int pan );

int Snd_PerapVoiceWazaParamGet( PERAPVOICE* perap );
BOOL Snd_PerapVoicePMVoiceTypeCheck( int type );


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define PERAP_SAMPLING_RATE		(2000)									//サンプリングレート
#define PERAP_SAMPLING_TIME		(1)										//サンプリングする時間
#define PERAP_SAMPLING_SIZE		(PERAP_SAMPLING_RATE * PERAP_SAMPLING_TIME)	//必要なデータ量

#define PERAP_MALE_WAVEOUT_SPD		(WAVEOUT_PLAY_SPDx1 - 4096)			//オスの再生スピード
#define PERAP_FEMALE_WAVEOUT_SPD	(WAVEOUT_PLAY_SPDx1 + 9192)			//メスの再生スピード
#define PERAP_WAVEOUT_SPD_RAND	(8192)									//再生スピードのランダム


//==============================================================================================
//
//	
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	サウンドメインから呼ばれる
 *			ぺラップの録音したデータの再生終了を監視してチャンネル開放をする
 *
 * @param	none
 *
 * @retval	"処理した=TRUE、何もしない=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_MainPerapCheck( void )
{
	u8* perap_play_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_PLAY_FLAG);

	//ペラップの録音した鳴き声を再生しているかフラグ
	if( *perap_play_flag == 1 ){

		//波形再生が終了していたら
		if( Snd_WaveOutIsPlaying(WAVEOUT_CH_NORMAL) == FALSE ){

			Snd_PerapVoiceStop();	//停止

			return TRUE;
		}
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ペラップの録音したデータが再生可能かチェック
 *
 * @param	no		ポケモンナンバー
 *
 * @retval	"再生可能=TRUE、再生不可=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoiceCheck( const PERAPVOICE* perap )
{
	u8* perap_default_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_DEFAULT_FLAG);

	//声データが存在するかどうかのチェック
	if( PERAPVOICE_GetExistFlag(perap) == FALSE ){
		return FALSE;
	}

	//デフォルトの鳴き声を再生するフラグのチェック
	if( *perap_default_flag == TRUE ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	ペラップの録音したデータを再生しているかチェック
 *
 * @param	no		ポケモンナンバー
 *
 * @retval	"再生中=TRUE、再生していない=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePlayingCheck( const PERAPVOICE* perap )
{
	u8* perap_play_flag		= Snd_GetParamAdrs( SND_W_ID_PERAP_PLAY_FLAG );

	if( *perap_play_flag == 0 ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	ペラップの録音したデータを再生
 *
 * @param	perap	PERAPVOICE型のポインタ
 * @param	sex		性別
 * @param	vol		ボリューム
 * @param	pan		パン
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePlaySub( const PERAPVOICE* perap, u32 sex, int vol, int pan )
{
	u16 add_spd;
	int ret,wave_pan;
	s8* sWaveBuffer			= Snd_GetWaveBufAdrs();
	u8* perap_play_flag		= Snd_GetParamAdrs( SND_W_ID_PERAP_PLAY_FLAG );

	//ペラップの録音したデータが再生不可能かチェック
	if( Snd_PerapVoiceCheck(perap) == FALSE ){
		return FALSE;
	}

	//シーケンス再生のパンは(-127 - 0 - 127)となっている
	//波形再生のパンは(0 - 64 - 127)となっている
	
	//波形再生パンを取得
	if( pan < 0 ){
		wave_pan = 64 + (pan / 2);		//0 - 64  にする
	}else{
		wave_pan = 64 + (pan / 2);		//64 - 127 にする
	}

	Snd_PMVoiceStop(0);		//鳴き声停止

	//再生終了前に、
	//再度この関数が呼ばれることがあるので、
	//一度停止してから、再生へ進むようにする
	Snd_PerapVoiceStop();

	//波形再生用チャンネルを確保する
	Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	//ランダムに音程を変える
	//gf_srand( sys.vsync_counter );
	add_spd = ( gf_rand() % PERAP_WAVEOUT_SPD_RAND );

	//声データの展開
	PERAPVOICE_ExpandVoiceData( sWaveBuffer, PERAPVOICE_GetVoiceData(perap) );

	{
		WAVEOUT_WORK waveout_wk;
		waveout_wk.handle			= Snd_WaveOutHandleGet(WAVEOUT_CH_NORMAL);	//波形再生ハンドル
		waveout_wk.format			= NNS_SND_WAVE_FORMAT_PCM8;		//波形データフォーマット

		waveout_wk.dataaddr			= Snd_GetWaveBufAdrs();			//波形データの先頭アドレス

		waveout_wk.loopFlag			= FALSE;						//ループフラグ
		waveout_wk.loopStartSample	= 0;							//ループ開始サンプル位置
		waveout_wk.samples			= PERAP_SAMPLING_SIZE;			//波形データのサンプル数
		waveout_wk.sampleRate		= PERAP_SAMPLING_RATE;			//波形データのサンプリングレート
		waveout_wk.volume			= vol;							//音量
		waveout_wk.speed			= (WAVEOUT_PLAY_SPDx1+add_spd);	//再生スピード
		waveout_wk.pan				= wave_pan;						//パン(0-127)
		ret = Snd_WaveOutStart( &waveout_wk, WAVEOUT_CH_NORMAL );

		//ボイスチャットの音量対応
		Snd_WaveOutSetVolume( WAVEOUT_CH_NORMAL, vol );
	}

#if 0
	//音程を変える
	if( ret == TRUE ){
		if( sex == PM_MALE ){
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, PERAP_MALE_WAVEOUT_SPD );	//オス
		}else{
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, PERAP_FEMALE_WAVEOUT_SPD );	//メス
		}
	}
#endif

	*perap_play_flag = 1;					//ぺラップの録音した鳴き声を再生しているフラグON
	Snd_PerapVoiceDefaultFlagSet( FALSE );	//ぺラップのデフォルトの鳴き声を再生するフラグOFF

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	ペラップの録音したデータを停止
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PerapVoiceStop( void )
{
	u8* ch_normal_flag	= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* perap_play_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_PLAY_FLAG);

	if( *ch_normal_flag == 1 ){										//CH確保していたら
		Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );				//buf開放
		Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );				//ch 開放
	}

	*perap_play_flag = 0;											//フラグクリア
	return;
}

//--------------------------------------------------------------
/**
 * @brief	ペラップデータ録音開始(サウンドシステムの領域に一時保存する)
 *
 * @param	none
 *
 * @retval	"MIC_RESULT_SUCCESS		処理が正常に完了"
 * @retval	"それ以外				何らかの原因で失敗"
 */
//--------------------------------------------------------------
MICResult Snd_PerapVoiceRecStart( void )
{
	MICAutoParam mic;	//マイクパラメータ

	//波形再生用チャンネルを確保する
	//Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	mic.type			= MIC_SAMPLING_TYPE_SIGNED_8BIT;	//サンプリング種別

	//バッファは32バイトアラインされたアドレスでないとダメ！
	mic.buffer			= Snd_GetWaveBufAdrs();

	mic.size			= PERAP_SAMPLING_SIZE;

	if( (mic.size&0x1f) != 0 ){
		mic.size &= 0xffffffe0;
	}

	//代表的なサンプリングレートをARM7のタイマー周期に換算した値の定義
	//mic.rate			= MIC_SAMPLING_RATE_8K;
	mic.rate			= HW_CPU_CLOCK_ARM7 / PERAP_SAMPLING_RATE;

	//連続サンプリング時にバッファをループさせるフラグ
	mic.loop_enable		= FALSE;

	//バッファが飽和した際に呼び出すコールバック関数へのポインタ
	mic.full_callback	= NULL;

	//バッファが飽和した際に呼び出すコールバック関数へ渡す引数
	mic.full_arg		= NULL;

	return Snd_MicStartAutoSampling( &mic );		//録音開始
}

//--------------------------------------------------------------
/**
 * @brief	ペラップデータ録音停止
 *
 * @param	none
 *
 * @retval	"MIC_RESULT_SUCCESS		処理が正常に完了"
 * @retval	"それ以外				何らかの原因で失敗"
 */
//--------------------------------------------------------------
MICResult Snd_PerapVoiceRecStop( void )
{
	return Snd_MicStopAutoSampling();
}

//--------------------------------------------------------------
/**
 * @brief	録音したデータをセーブデータにセット
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PerapVoiceDataSave( PERAPVOICE* perap )
{
	PERAPVOICE_SetVoiceData( perap, (const s8*)Snd_GetWaveBufAdrs() );
	return;
}


/***********/
//停止、再生中かチェックも対応しているか確認！
/***********/


//==============================================================================================
//
//	サウンドシステム内で、
//
//	●ぺラップナンバーかチェック
//	●デフォルトの鳴き声を鳴らすフラグをチェック
//
//	録音したデータを再生するかに対応される関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	ぺラップのデフォルトの鳴き声を再生するフラグ操作
 *
 * @param	no		フラグ操作
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PerapVoiceDefaultFlagSet( u8 no )
{
	u8* perap_default_flag	= Snd_GetParamAdrs(SND_W_ID_PERAP_DEFAULT_FLAG);
	*perap_default_flag		= no;
	return;
}


//==============================================================================================
//
//	通信確保されるぺラップデータのポインタを受け取り、再生する関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	ペラップの録音したデータを再生
 *
 * @param	perap	ペラップデータのポインタ
 * @param	sex		性別(PM_MALEなど)
 * @param	vol		ボリューム(0 ～ 127)
 * @param	pan		パン(-128 ～ 127)
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePlay( PERAPVOICE* perap, u32 sex, int vol, int pan )
{
	int ret;
	PERAPVOICE** my_p = Snd_GetParamAdrs( SND_W_ID_MY_PERAP_PTR );

	//ペラップの録音したデータ再生
	if( perap == NULL ){
		ret = Snd_PerapVoicePlaySub( *my_p, sex, vol, pan );		//エラー回避
	}else{
		ret = Snd_PerapVoicePlaySub( perap, sex, vol, pan );
	}

	//ぺラップの録音したデータ再生出来なかった時
	if( ret == FALSE ){
		Snd_PerapVoiceDefaultFlagSet( TRUE );			//デフォルトを再生する

		//ヒープIDを指定しているがメモリ確保はしていない！(PV_NORMAL固定なので)
		ret = Snd_PMVoicePlayEx( PV_NORMAL, MONSNO_PERAPPU, pan, vol, HEAPID_WORLD );
	}

	//Snd_PMVoicePlayExの中で、Snd_PerapVoicePlaySubが呼ばれるが、
	//それに渡されるのは、自分のぺラップデータなので、ひとまとめにしてはだめ！
	//default_flagが立っているので、自分ぺラップの再生にはいかず、
	//デフォルトの鳴き声がなるようになる！
	
	return ret;
}


//==============================================================================================
//
//	技「おしゃべり」
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	技のパラメータを取得
 *
 * @param	perap		ぺラップデータのポインタ
 *
 * @retval	"パラメータ 0～2"
 */
//--------------------------------------------------------------
int Snd_PerapVoiceWazaParamGet( PERAPVOICE* perap )
{
	const s8* voicedata;
	s8 num;

	//声データが存在するかどうかのチェック
	if( PERAPVOICE_GetExistFlag(perap) == FALSE ){
		return 0;
	}

	//要素数[15]を見てパラメータを決定する
	voicedata = PERAPVOICE_GetVoiceData(perap);
	num = voicedata[15];
	//OS_Printf( "voicedata[15] = %d\n", voicedata[15] );
	//OS_Printf( "num = %d\n", num );

	if( (-128 <= num) && (num < -30) ){
		return 1;
	}

	if( (30 <= num) && (num < 128) ){
		return 2;
	}

	return 0;
}


//--------------------------------------------------------------
/**
 * @brief	録音データ、デフォルトデータどちらを再生するかチェック
 *
 * @param	type		再生パターン
 *
 * @retval	"TRUE=録音したデータを再生する、FALSE=デフォルトの鳴き声を再生する"
 */
//--------------------------------------------------------------
BOOL Snd_PerapVoicePMVoiceTypeCheck( int type )
{
	switch( type ){
	case PV_NORMAL:				//通常再生
	case PV_HALF:				//再生時間短縮（２ｖｓ２バトルでポケモン登場時）
	//case PV_FLDEVENT:			//怒ったポケモン（フィールドイベント）
	//case PV_W_TOOBOE:			//技効果音・とおぼえ用
	//case PV_W_HYPER1:			//技効果音・ハイパーボイス用１
	case PV_POKEDOWN:			//ポケモンがやられた時
	//case PV_W_HYPER2:			//技効果音・ハイパーボイス用２
	//case PV_W_HOERU1:			//技効果音・ほえる１
	//case PV_W_HOERU2:			//技効果音・ほえる２
	//case PV_W_NAKIGOE1:		//技効果音・なきごえ１
	//case PV_W_NAKIGOE2:		//技効果音・なきごえ２
	case PV_PINCHNORMAL:		//通常再生(元気なし)
	case PV_PINCHHALF:			//再生時間短縮（２ｖｓ２バトルでポケモン登場時）(元気なし)
	//case PV_ZUKAN_CHORUS:		//図鑑コーラス再生(追加06.03.03)
	//case PV_ZUKAN_NORMAL:		//図鑑ノーマル再生(追加06.04.21)
		return TRUE;
	};

	return FALSE;
}

