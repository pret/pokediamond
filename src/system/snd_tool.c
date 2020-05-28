//==============================================================================================
/**
 * @file	snd_tool.c
 * @brief	サウンドツール関数
 * @author	Satoshi Nohara
 * @date	2005.06.09
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
#include "poketool/monsno.h"

#include "communication/communication.h"


//量子化ビットタイプ8bit,サンプリングレート8k
//#define MIC_TYPE_8BIT_RATE_8K


//==============================================================================================
//
//	メモ
//
//==============================================================================================
#if 0
	//●スリープモードから復帰後の再生状態
	//スリープ前の再生状態と完全に一致するわけではない
	//一時的に音がおかしくなったり、音が飛んだりすることがある
	//これが問題になる時は、スリープ前に再生を停止し、
	//スリープ後に再生を再開するといった対処が必要になる
#endif


//==============================================================================================
//
//	定義
//
//==============================================================================================
//PLAYER_BGMの使用チャンネルのビット指定
#define PLAYER_BGM_NORMAL_CH	(0x07ff)		//通常の使用CH
#define PLAYER_BGM_EXTRA_CH		(0x7fff)		//特定のシーンのみ使用CH
#define SND_REVERB_NUM_OP		(30)//(40)//(50)//OPリバーブの値(0-63)
#define SND_REVERB_NUM_ED		(15)//(50)		//EDリバーブの値(0-63)

#define SND_CH_SET								//定義有効で使用可能チャンネルの操作をする


//==============================================================================================
//
//	変数
//
//==============================================================================================
//セーブする必要ありワーク(どの企画で必要か未定)
static s8 sWaveBuffer[ SWAVE_BUFFER_SIZE ] ATTRIBUTE_ALIGN(32);	//波形格納バッファ

static int mono_flag;										//モノラルフラグ


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void Snd_PlayerSetSeqArcNo( NNSSndHandle *p, int arc_no, int index );

void Snd_NowBgmNoSet( u16 no );
u16 Snd_NowBgmNoGet();
void Snd_NextBgmNoSet( u16 no );
u16 Snd_NextBgmNoGet();
void Snd_ZoneBgmSet( u16 bgm );

void Snd_DeleteHeapAfterBgm( void );
int Snd_GetHeapSaveLv( int type );
void Snd_SceneSet( u8 scene );

int Snd_LoadSeByScene( u8 scene );
BOOL Snd_DataSetByScene( u8 scene, u16 no, int flag );
static void Snd_DataSetSub( u8 scene );
static void Snd_FieldDataSet( u16 no, int flag );
static void Snd_FieldDataSet_PauseOffStart( u16 no, u16 player_field_seq_no );
void Snd_FieldDataSetSub( u16 no, u16 old_bank_no );
static void Snd_BattleDataSet( u16 no, int flag );
static void Snd_P2PDataSet( u16 no, int flag );
static void Snd_ContestDataSet( u16 no, int flag );
static void Snd_ConImageDataSet( u16 no, int flag );
static void Snd_AddSceneSeDataSet( u8 scene );
static void Snd_DemoDataSet( u8 scene, u16 no, int flag );
void Snd_EyeBgmSet( u16 no );
void Snd_HeapStateClear(void);

void Snd_PlayerPause( u8 player, BOOL flag );
void Snd_PauseClearAll();
void Snd_PlayerMoveVolume( int handle_no, int vol, int frame );
void Snd_AllPlayerMoveVolume( int vol, int frame );
void Snd_PlayerSetInitialVolume( int handle_no, int vol );
void Snd_VChatVolSet( int seq_no, int handle_no );
void Snd_PlayerSetInitialVolumeBySeqNo( u16 no, int vol );
BOOL Snd_ArcPlayerStartSeqEx( int handle_no, int player_no, u16 no );

int Snd_PlayerCountPlayingSeq( int player_no );
u8 Snd_GetPlayerNo( u16 no );
int Snd_GetSeqNo( NNSSndHandle *p );

const NNSSndArcBankInfo* Snd_GetBankInfo( int no );
u16 Snd_GetBankNo( int no );

static void MicCallback( MICResult /*result*/, void* /*arg*/ );
MICResult Snd_MicStartAutoSampling( MICAutoParam* p);
MICResult Snd_MicStopAutoSampling(void);

NNSSndWaveOutHandle * Snd_WaveOutHandleGet( u32 no );
BOOL Snd_WaveOutAllocChannel( u32 no );
void Snd_WaveOutFreeChannel( u32 no );
void Snd_WaveOutSetPan( u32 no, u8 pan );
void Snd_WaveOutSetSpeed( u32 no, u32 spd );
void Snd_WaveOutSetVolume( u32 no, int vol );
BOOL Snd_WaveOutStart( WAVEOUT_WORK* p, u32 ch );
void Snd_WaveOutStop( u32 no );
BOOL Snd_WaveOutIsPlaying( u32 no );

//逆再生
BOOL Snd_WaveOutStartReverse( u16 no, int vol, int pan, u32 ch, int heap_id );
BOOL Snd_WaveOutStartReverseChorus( int vol, int pan );
void Snd_WaveOutStopReverse( u32 );
static void Snd_BufReverse( u8* p, u32 size );

void Snd_CaptureCreateThread(void);
BOOL Snd_CaptureIsActive(void);
NNSSndCaptureType Snd_CaptureGetCaptureType(void);
void Snd_CaptureChangeOutputEffect( NNSSndCaptureOutputEffectType type );

void Snd_CaptureStartOutputEffect( NNSSndCaptureOutputEffectType type );
BOOL Snd_CaptureStartReverb( int vol );
void Snd_CaptureStopReverb( int frame );
void Snd_CaptureReverbVol( int vol, int frame );

BOOL Snd_CaptureStartEffect(void);
void Snd_CaptureStopEffect(void);
void Snd_CaptureEffectLevel( int level );
void EffectCallback( void* lp, void* rp, u32 len, NNSSndCaptureFormat format, void* arg );
void EffectCallback2( void* lp, void* rp, u32 len, NNSSndCaptureFormat format, void* arg );
static inline smp_t GetSample( smp_t* p, int x, int n, const EffectCallbackInfo* info );
static inline int abs( int x );
void SamplingCallback( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg );

void Snd_PlayerSetTrackMute( int handle_no, u16 bitmask, BOOL flag );
void Snd_PlayerSetTrackVolume( NNSSndHandle *p, u16 bitmask, int vol );
void Snd_PlayerSetTrackPitch( int handle_no, u16 bitmask, int pitch );
void Snd_PlayerSetTrackPitchBySeqNo( u16 no, u16 bitmask, int pitch );
void Snd_PlayerSetTrackPan( int handle_no, u16 bitmask, int pan );
void Snd_PlayerSetTempoRatio( int handle_no, int tempo );

void Snd_SetMonoFlag( BOOL flag );
void Snd_FadeCountSet( int frame );
int Snd_FadeCountCheck();
void Snd_NextWaitSet( int frame );
int Snd_NextWaitCheck();
//void Snd_SetMasterVolume( int vol );

void* Snd_GetWaveBufAdrs();

//デバック用
BOOL Snd_PlayerHeapCreate( int player_no, u32 size );

void Snd_BankFlagSet( int no );
u8 Snd_BankFlagGet();

BOOL Snd_FadeOutNextPlaySet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs );
BOOL Snd_FadeOutNextFadeInSet( u8 scene, u16 no, int frame, int next_wait, int next_frame, u8 flag, void* adrs );
static void Snd_FadeCommonSet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs );

BOOL Snd_PlayerWriteVariable( s16 num );
static void Snd_PlayerBgmChannelSet( u16 ch_bit );

void Snd_BgmChannelSetAndReverbSet( int flag );
static void Snd_FieldPauseOrStop( void );


//==============================================================================================
//
//	プログラム
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	シーケンスアーカイブ番号を設定
 *
 * @param	p		サウンドハンドルのアドレス
 * @param	arc_no	シーケンスアーカイブ番号
 * @param	index	インデックス
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PlayerSetSeqArcNo( NNSSndHandle *p, int arc_no, int index )
{
	NNS_SndPlayerSetSeqArcNo( p, arc_no, index );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドBGM固定フラグセット(セーブはしない)
 *
 * @param	flag	1=BGM切り替わらない、0E=BGM切り替わる(通常)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CtrlBgmFlagSet( u8 flag )
{
	u8* ctrl_bgm_flag = Snd_GetParamAdrs(SND_W_ID_CTRL_BGM_FLAG);
	*ctrl_bgm_flag = flag;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドBGM固定フラグチェック(セーブはしない)
 *
 * @param	none
 *
 * @retval	"1=BGM切り替わらない、0E=BGM切り替わる(通常)"
 */
//--------------------------------------------------------------
u8 Snd_CtrlBgmFlagCheck( void )
{
	u8* ctrl_bgm_flag = Snd_GetParamAdrs(SND_W_ID_CTRL_BGM_FLAG);
	return *ctrl_bgm_flag;
}

//--------------------------------------------------------------
/**
 * @brief	今のBGMナンバー更新
 *
 * @param	no		更新するBGMナンバー
 *
 * @retval	none
 *
 * 次のBGMナンバー(next_bgm_no)をクリアしている！
 */
//--------------------------------------------------------------
void Snd_NowBgmNoSet( u16 no )
{
	u16* now_bgm_no = Snd_GetParamAdrs(SND_W_ID_NOW_BGM_NO);
	*now_bgm_no = no;
	Snd_NextBgmNoSet( 0 );			//注意！ 次のBGMナンバーをクリア！
	return;
}

//--------------------------------------------------------------
/**
 * @brief	今のBGMナンバー取得
 *
 * @param	none
 *
 * @retval	"今のBGMナンバー"
 */
//--------------------------------------------------------------
u16 Snd_NowBgmNoGet()
{
	u16* now_bgm_no = Snd_GetParamAdrs(SND_W_ID_NOW_BGM_NO);
	return *now_bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	次のBGMナンバー更新
 *
 * @param	no		更新するBGMナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_NextBgmNoSet( u16 no )
{
	u16* next_bgm_no = Snd_GetParamAdrs(SND_W_ID_NEXT_BGM_NO);
	*next_bgm_no = no;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	次のBGMナンバー取得
 *
 * @param	none
 *
 * @retval	"次のBGMナンバー"
 */
//--------------------------------------------------------------
u16 Snd_NextBgmNoGet()
{
	u16* next_bgm_no = Snd_GetParamAdrs(SND_W_ID_NEXT_BGM_NO);
	return *next_bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドバンクナンバーセット
 *
 * @param	bank_no		バンクナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_ZoneBgmSet( u16 bgm )
{
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);
	*zone_bgm		= bgm;
	return;
}


//==============================================================================================
//
//	サウンドデータのロード関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	シーンセット
 *
 * @param	scene	シーン
 *
 * @retval	none
 *
 * メインシーンをセットすると、
 * サブシーンは"SND_SCENE_DUMMY"にクリアされる
 */
//--------------------------------------------------------------
void Snd_SceneSet( u8 scene )
{
	u8* scene_main	= Snd_GetParamAdrs(SND_W_ID_SCENE_MAIN);
	u8* scene_sub	= Snd_GetParamAdrs(SND_W_ID_SCENE_SUB);

	if( scene < SND_SCENE_SUB ){
		*scene_main	= scene;			//メインシーン
		*scene_sub  = SND_SCENE_DUMMY;	//クリア
	}else{
		*scene_sub	= scene;			//サブシーン
	}

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n--------サウンド　シーン--------\n" );
	OS_Printf( "メイン = %d\n", *scene_main );
	OS_Printf( "サブ = %d\n", *scene_sub );
	OS_Printf( "\n--------------------------------\n\n" );
#endif

	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーンをキーにして、SEデータをロード
 *
 * @param	scene		シーン
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
int Snd_LoadSeByScene( u8 scene )
{
	int ret;

	//SEシーケンスグループ
	switch( scene ){

	//タイトル
	//AGB
	//世界交換(必ずフィールドにする！受付、専用画面で曲がかわらないので専用のロードはだめ！)
	//ふしぎなおくりもの(必ずフィールドにする！ug_20使用)
	//エンディング
	case SND_SCENE_TITLE:
	case SND_SCENE_AGB:
	//case SND_SCENE_WORLDTRADE:
	case SND_SCENE_HUSIGI:
	case SND_SCENE_ENDING:
		//専用の音がない時は、フィールドをロードしておく！
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );
		break;

	//オープニング
	//タマゴ孵化
	case SND_SCENE_OPENING:
	case SND_SCENE_EGG:
		ret = Snd_ArcLoadGroup( GROUP_SE_BATTLE );		//バトルの音が必要なので！
		break;

	//交換デモ
	case SND_SCENE_TRADE:
		ret = Snd_ArcLoadGroup( GROUP_SE_TRADE );
		break;

	//フィールド
	case SND_SCENE_FIELD:
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );
		break;

	//バトル
	case SND_SCENE_BATTLE:
		ret = Snd_ArcLoadGroup( GROUP_SE_BATTLE );
		break;

	//P2P
	case SND_SCENE_P2P:
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );
		break;

	//コンテスト
	case SND_SCENE_CONTEST:
		ret = Snd_ArcLoadGroup( GROUP_SE_CONTEST );
		break;

	//殿堂デモ
	case SND_SCENE_DENDOU:
		ret = Snd_ArcLoadGroup( GROUP_SE_FIELD );		//SEQ_SE_DP_SAVEが使用している！
		break;

	//料理
	case SND_SCENE_NUTMIXER:
		ret = Snd_ArcLoadGroup( GROUP_SE_NUTMIXER );
		break;

	//バッグ
	case SND_SCENE_SUB_BAG:
		ret = Snd_ArcLoadGroup( GROUP_SE_BAG );
		break;

	//スロット
	case SND_SCENE_SUB_SLOT:
		ret = Snd_ArcLoadGroup( GROUP_SE_SLOT );
		break;

	//名前入力
	case SND_SCENE_SUB_NAMEIN:
		ret = Snd_ArcLoadGroup( GROUP_SE_NAMEIN );
		break;

	//イメージクリップ
	case SND_SCENE_CON_IMAGE:	//コンテスト
	case SND_SCENE_SUB_IMAGE:
		ret = Snd_ArcLoadGroup( GROUP_SE_IMAGE );
		break;

	//図鑑
	case SND_SCENE_SUB_ZUKAN:
		ret = Snd_ArcLoadGroup( GROUP_SE_ZUKAN );
		break;

	//タウンマップ(注意！)
	//冒険ノート
	case SND_SCENE_SUB_TOWNMAP:
	case SND_SCENE_SUB_FNOTE:
		ret = Snd_ArcLoadBank( BANK_SE_TOWNMAP );			//バンクロード
		ret = Snd_ArcLoadWaveArc( WAVE_ARC_SE_TOWNMAP );	//波形アーカイブ
		break;

	//トレーナーカード
	case SND_SCENE_SUB_TRCARD:
		ret = Snd_ArcLoadGroup( GROUP_SE_TRCARD );
		break;

	//ポケモンリスト
	case SND_SCENE_SUB_POKELIST:
		ret = Snd_ArcLoadGroup( GROUP_SE_POKELIST );
		break;

	//化石掘り
	case SND_SCENE_SUB_DIG:
		ret = Snd_ArcLoadGroup( GROUP_SE_DIG );
		break;

	//カスタムボール
	case SND_SCENE_SUB_CUSTOM:
		ret = Snd_ArcLoadGroup( GROUP_SE_CUSTOM );
		break;

	//最初のポケモン選択
	case SND_SCENE_SUB_FIRSTPOKE:
		ret = Snd_ArcLoadGroup( GROUP_SE_BAG );			//注意：他のグループを使い回している！
		break;

	//ポケモンステータス
	case SND_SCENE_SUB_PST:
		ret = Snd_ArcLoadGroup( GROUP_SE_NAMEIN );		//注意：他のグループを使い回している！
		break;

	//簡易会話
	case SND_SCENE_SUB_PMS:
		ret = Snd_ArcLoadGroup( GROUP_SE_CUSTOM );		//注意：他のグループを使い回している！
		break;

	//クライマックス
	case SND_SCENE_SUB_CLIMAX:
		ret = Snd_ArcLoadGroup( GROUP_SE_CLIMAX );
		break;

	//船デモ(注意！)
	case SND_SCENE_SUB_SHIP:
		ret = Snd_ArcLoadBank( BANK_SE_SHIP );			//バンクロード
		ret = Snd_ArcLoadWaveArc( WAVE_ARC_SE_SHIP );	//波形アーカイブ
		break;

	//モロッコ号(注意！)
	case SND_SCENE_SUB_TRAIN:
		ret = Snd_ArcLoadBank( BANK_SE_TRAIN );			//バンクロード
		ret = Snd_ArcLoadWaveArc( WAVE_ARC_SE_TRAIN );	//波形アーカイブ
		break;

	//エラー
	defalut:
		GF_ASSERT( (0) && "シーンナンバーが不正です！" );
		ret = FALSE;
		break;
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	シーンをキーにして、サウンドデータセット
 *
 * @param	scene	シーン
 * @param	no		シーケンスナンバー
 * @param	flag	"未使用"
 *
 * @retval	"0=何もしない、1=データロード"
 *
 * 現在のシーンと、渡されたシーンが同じ時は、
 * サウンドデータをロードする必要がないので何もしない！
 */
//--------------------------------------------------------------
BOOL Snd_DataSetByScene( u8 scene, u16 no, int flag )
{
	u8* scene_main	= Snd_GetParamAdrs(SND_W_ID_SCENE_MAIN);
	u8* scene_sub	= Snd_GetParamAdrs(SND_W_ID_SCENE_SUB);
	u16* me_wait	= Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

	//シーンが同じ時は何もしない
	if( scene < SND_SCENE_SUB ){
		if( *scene_main == scene ){	
			return 0;
		}
	}else{
		if( *scene_sub == scene ){	
			return 0;
		}
	}

	//シーンセット
	Snd_SceneSet( scene );

	switch( scene ){

	//フィールド
	case SND_SCENE_FIELD:
		Snd_BgmChannelSetAndReverbSet( 0 );		//使用可能チャンネル操作、リバーブ設定(クリア)
		Snd_FieldDataSet( no, flag );

		//ME再生中に通信エラーなどで、ME開放が入らない状態だと、
		//Snd_MainでME使用中のままになってしまうので、
		//フィールドデータロードのタイミングで必ず落とすように応急処理を入れておく(06.07.27)
		(*me_wait) = 0;	//クリア
		break;

	//バトル
	case SND_SCENE_BATTLE:
		Snd_BattleDataSet( no, flag );
		break;

	//P2P
	case SND_SCENE_P2P:
		Snd_P2PDataSet( no, flag );
		break;

	//コンテスト
	case SND_SCENE_CONTEST:
		Snd_ContestDataSet( no, flag );
		break;

	//イメージクリップ(コンテスト)
	case SND_SCENE_CON_IMAGE:
		Snd_ConImageDataSet( no, flag );
		break;

	//サブ画面(BGMを引き継ぎ、SEを追加ロードする)
	case SND_SCENE_SUB_BAG:
	case SND_SCENE_SUB_NAMEIN:
	case SND_SCENE_SUB_IMAGE:
	case SND_SCENE_SUB_ZUKAN:
	case SND_SCENE_SUB_TOWNMAP:
	case SND_SCENE_SUB_TRCARD:
	case SND_SCENE_SUB_POKELIST:
	case SND_SCENE_SUB_DIG:
	case SND_SCENE_SUB_CUSTOM:
	case SND_SCENE_SUB_FIRSTPOKE:
	case SND_SCENE_SUB_PST:
	case SND_SCENE_SUB_PMS:
	case SND_SCENE_SUB_CLIMAX:
	case SND_SCENE_SUB_SHIP:
	case SND_SCENE_SUB_TRAIN:
	case SND_SCENE_SUB_SLOT:
	case SND_SCENE_SUB_FNOTE:
		/************/
		//追加していく
		/************/
		Snd_AddSceneSeDataSet( scene );
		break;

	//全て停止して、常駐以外をロードし直す
	case SND_SCENE_TITLE:
		Snd_BgmChannelSetAndReverbSet( 1 );		//使用可能チャンネル操作、リバーブ設定(セット)
		Snd_DemoDataSet( scene, no, flag );
		break;

	//全て停止して、常駐以外をロードし直す
	case SND_SCENE_ENDING:
		Snd_BgmChannelSetAndReverbSet( 2 );		//使用可能チャンネル操作、リバーブ設定(セット)
		Snd_DemoDataSet( scene, no, flag );
		break;

	//全て停止して、常駐以外をロードし直す
	case SND_SCENE_OPENING:
		Snd_BgmChannelSetAndReverbSet( 0 );		//使用可能チャンネル操作、リバーブ設定(クリア)
		Snd_DemoDataSet( scene, no, flag );
		break;

	//全て停止して、常駐以外をロードし直す
	case SND_SCENE_TRADE:
	case SND_SCENE_DENDOU:
	case SND_SCENE_AGB:
	case SND_SCENE_HUSIGI:
	case SND_SCENE_NUTMIXER:
	//case SND_SCENE_WORLDTRADE:
	case SND_SCENE_EGG:
		/************/
		//追加していく
		/************/
		Snd_DemoDataSet( scene, no, flag );
		break;

	//ポーズが必要なデモは別のセットコマンド作る
	//case SND_SCENE_DEMO:
		//break;

	//何もしない
	defalut:
		return 0;
	};

	return 1;		//データロード
}

//--------------------------------------------------------------
/**
 * @brief	サウンドデータセット共通処理
 *
 * @param	scene	シーン
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_DataSetSub( u8 scene )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

	Snd_HeapLoadState( *heap_save_global );						//常駐以外を消す
	//常駐は消さないので、再度階層を保存する必要はない！
	//Snd_HeapSaveState(&wk->heap_save[SND_HEAP_SAVE_GLOBAL]);	//階層保存(常駐以外を消す時に使用)
	
	//一応呼んでおく
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK));	//保存(常駐,bnk,SE以外消す)

	Snd_LoadSeByScene( scene );									//SEシーケンスグループ
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//階層保存(常駐、SE以外消す時使用)

	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールド画面に切り替わる時のサウンドデータセット
 *
 * @param	no		シーケンスナンバー
 * @param	flag	"未使用"
 *
 * @retval	none
 *
 * ＜データロード順＞
 * 常駐
 * SE
 * BGM(WAVEARC)
 *
 * シーケンス、バンクはプレイヤーヒープでロードしている！
 *
 * 戦闘でゲームオーバーになって、ポケセンに戻るときなどは、
 * Snd_PauseClearAllを呼んで、ポーズフラグをクリアしないといけない！
 */
//--------------------------------------------------------------
static void Snd_FieldDataSet( u16 no, int flag )
{
	int ret,player_seq_no;
	u16 bgm;
	u8* field_pause_flag	= Snd_GetParamAdrs(SND_W_ID_FIELD_PAUSE_FLAG);
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);
	u16* zone_bgm			= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜サウンドデータロード　フィールドシーン切り替わり＞\n" );
#endif


	//ポーズしていなくて、同じ曲を鳴らそうとしたら、BGM引継ぎにしている！

	//PLAYER_FIELDのBGMナンバー取得
	player_seq_no = Snd_GetSeqNo( Snd_HandleGet(SND_HANDLE_FIELD) );

	//PLAYER_FIELDをポーズしていない時
	if( *field_pause_flag == 0 ){
	
		//同じ曲を鳴らそうとした時
		if( player_seq_no == no ){

			//Snd_AddSceneSeDataSet( SND_SCENE_FIELD );			//SEを追加ロードする

			//PLAYER_FIELDを停止してから、別画面に行けば、
			//戻ってきたときに、BGMナンバー取得の値が変わるので、
			//FieldDataがロードされる！
			
			//次のBGMに自転車をセットしている状態で(フェードアウト中)
			//プレイヤーシーケンスナンバーは、まだ自転車になっていないので、
			//何もせずリターンしてしまう！なのでチェックを入れる
			if( Snd_NextBgmNoGet() != SEQ_BICYCLE ){
				return;		//注意！
			}
		}
	}

	//ポーズ復帰の分岐にも必要！
	//波形アーカイブのロードが必要なので！
	Snd_BankFlagSet( SND_BANK_CHANGE );							//バンク切り替えるかフラグをセット

	//手順(1)
	Snd_StopEx();												//フィールドBGMを抜かして全停止

	//PLAYER_FIELDをポーズしている時でも、
	//昼と夜が切り替わった時は、違う曲を鳴らすようにする！
	//その時は、ポーズフラグを落として、頭から違う曲を再生にいくようにする！(06.04.12)
	if( player_seq_no != no ){
		Snd_PlayerPause( PLAYER_FIELD, FALSE );					//フィールドBGM再開
		Snd_Stop();
	}

	//フィールドBGMをポーズしていたら解除する！
	if( *field_pause_flag == 1 ){

#if 1
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_BGM_BANK) );

		Snd_LoadSeByScene( SND_SCENE_FIELD );						//SEシーケンスグループ
		Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//階層保存(常駐、SE以外消す時)
#else

		//共通処理
		Snd_DataSetSub( SND_SCENE_FIELD );
#endif

		//昼と夜が切り替わって、違う曲を鳴らそうとした時は、
		//ポーズフラグを落として、頭から違う曲を再生にいくようにする！(06.04.12)
		if( player_seq_no != no ){
			Snd_PlayerPause( PLAYER_FIELD, FALSE );					//フィールドBGM再開
		}

		Snd_FieldDataSet_PauseOffStart( no, player_seq_no );
		return;
	}

#if 0	//snd_playの中で、Snd_FieldDataSetSubが呼ばれるので削除(06/07/11)

	//ポーズしていない時は、バンクも含め、常駐以外を消す

	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_GLOBAL) );		//常駐以外を消す

	Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_BANK );				//バンクロード
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK));	//保存(常駐,bnk,SE以外消す)
	
	Snd_LoadSeByScene( SND_SCENE_FIELD );								//SEシーケンスグループ
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//階層保存(常駐、SE以外消す時使用)
#endif

	//BGM再生(ステータス＝再生)
	Snd_BgmPlay( no );											//フィールドBGM再生

	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドBGMをポーズ解除する流れ
 *
 * @param	no					シーケンスナンバー
 * @param	player_field_seq_no	フィールドのシーケンスナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_FieldDataSet_PauseOffStart( u16 no, u16 player_field_seq_no )
{
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);
	u16 tmp_bank_no = Snd_GetBankNo(*zone_bgm);					//不正な値が入っていないかチェック

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "＜フィールドBGMポーズ解除！＞\n" );
#endif

#if 0
	//再生しようとしているBGMナンバー、PLAYER_FIELDにすでに設定されているバンクナンバー
	Snd_FieldDataSetSub( no, Snd_GetBankNo(player_field_seq_no) );
#else
	if( (tmp_bank_no != BANK_BGM_FIELD) && (tmp_bank_no != BANK_BGM_DUNGEON) ){
		Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_WAVE );				//波形アーカイブロード
		OS_Printf( "zone_bgm = %d\n", *zone_bgm );
		OS_Printf( "tmp_bank_no = %d\n", tmp_bank_no );
		GF_ASSERT( (0) && "bgm play : *zone_bgm error" );
	}else{
		Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_WAVE | NNS_SND_ARC_LOAD_BANK);//arc,bank
	}

	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM) );	//階層保存(BGMの後を消す)
#endif

	//ポーズ状態から復帰するには、バンクも再ロードする必要があるが、
	//プレイヤーヒープでバンクをロードしているので大丈夫！

	//Snd_NowBgmNoSet( Snd_GetSeqNo(Snd_HandleGet(SND_HANDLE_FIELD)) );	//今のBGMナンバーセット

	//プレイヤーヒープにBGM_FIELD_BANK(BGM_DUNGEON_BANK)が残っているのが前提！
	//これが出来ないシチュエーションがあったら、BGM_DUNGEON_BANKは廃止しないとダメ！
	
	Snd_PlayerPause( PLAYER_FIELD, FALSE );						//フィールドBGM再開
	Snd_BgmFadeIn( BGM_VOL_MAX, 40, BGM_FADEIN_START_VOL_MIN );	//フェードイン

	//バンク切り替えるかフラグをリセット
	Snd_BankFlagSet( SND_BANK_CONTINUE );					//クリア = 継続
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドデータセットの共通処理(snd_tool.c,snd_play.c)
 *
 * @param	no			シーケンスナンバー
 * @param	old_bank_no	フィールドのバンクナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_FieldDataSetSub( u16 no, u16 old_bank_no )
{
	u16 tmp_bank_no;
	u8* bank_flag	= Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);

	/*
	//PLAYER_FIELDで鳴らすBGMのバンク指定は注意する！
	//Snd_DataSetBySceneをした後に、BGMデータのロードが発生しないことが起きるので！
	//
	//BANK_BASICを指定していれば、ロードが入らなくても平気。
	//ゲーム開始時は、old_bank_noは0なので、必ず階層保存まで呼ばれる。
	*/

	//バンク切り替えるフラグがONになっているかチェック
	if( (*bank_flag == SND_BANK_CHANGE) || (old_bank_no == 0) ){

		//マップ遷移の時、バンクをロードする
		//ゾーンをまたぐ時、バンクをロードしない
		
		//シーケンス、バンクはプレイヤーヒープでロードしている！
#if 0
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SE) );		//BGMを開放
#else
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_GLOBAL) );	//常駐以外を消す

		Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_BANK );			//バンクロード
		Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK));//保存(常駐,bnk,SE以外消す)
	
		Snd_LoadSeByScene( SND_SCENE_FIELD );							//SEシーケンスグループ
		Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));		//保存(常駐、SE以外消す)
#endif

		//波乗り、ゆれ草状態で戦闘にいって、復帰すると、
		//読み込まれるデータは、BANK_BASICになってしまう！
		//ゾーンをまたいだ時、陸に上陸した時などに、
		//BANK_FIELD(BANK_DUNGEON)が読み込まれていないので、
		//BGM再生処理で失敗してしまうので、
		//保存しておいたゾーンの曲ナンバーを見て、
		//必要な波形をフェードアウト中にロードする

		tmp_bank_no = Snd_GetBankNo(*zone_bgm);				//不正な値が入っていないかチェック
		if( (tmp_bank_no != BANK_BGM_FIELD) && (tmp_bank_no != BANK_BGM_DUNGEON) ){
			Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_WAVE );				//波形アーカイブロード
			OS_Printf( "zone_bgm = %d\n", *zone_bgm );
			OS_Printf( "tmp_bank_no = %d\n", tmp_bank_no );
			GF_ASSERT( (0) && "bgm play : *zone_bgm error" );
		}else{
#if 1
			Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_WAVE );		//波形アーカイブロード
#else
	//		Snd_ArcLoadSeqEx( *zone_bgm, NNS_SND_ARC_LOAD_WAVE | NNS_SND_ARC_LOAD_BANK);//arc,bank
#endif
		}

		Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM) );	//階層保存(BGMの後を消す)
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	バトル画面に切り替わる時のサウンドデータセット
 *
 * @param	no		シーケンスナンバー
 * @param	flag	"未使用"
 *
 * @retval	none
 *
 * ＜データロード順＞
 * 常駐
 * SE
 * BGM
 */
//--------------------------------------------------------------
static void Snd_BattleDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜サウンドデータロード　バトルシーン切り替わり＞\n" );
#endif

	//フィールドBGMをポーズするか、停止するかを判別して処理
	Snd_FieldPauseOrStop();

#if 0
	//共通処理
	Snd_DataSetSub( SND_SCENE_BATTLE );
#else
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_BGM_BANK) );	//常駐とfield_bnk以外消す

	Snd_LoadSeByScene( SND_SCENE_BATTLE );							//SEシーケンスグループ
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE));	//階層保存(常駐、SE以外消す時使用)
#endif

	//フィールドBGMのシーケンス、バンクは、プレイヤーヒープで処理しているので、
	//停止処理を呼ばないと開放されない(ポーズ状態にしている)

	Snd_BankFlagSet( SND_BANK_CHANGE );							//バンク切り替えるかフラグをセット
	Snd_BgmPlay( no );											//BGM再生
	return;
}

//--------------------------------------------------------------
/**
 * @brief	P2P画面に切り替わる時のサウンドデータセット
 *
 * @param	no		シーケンスナンバー
 * @param	flag	"未使用"
 *
 * @retval	none
 *
 * ＜データロード順＞
 * 常駐
 * SE
 * BGM
 */
//--------------------------------------------------------------
static void Snd_P2PDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜サウンドデータロード　P2Pシーン切り替わり＞\n" );
#endif

	//手順(1)
	Snd_Stop();													//全停止

	//ポーズフラグを落とさないといけない！
	//Snd_PlayerPause( PLAYER_FIELD, FALSE );					//フィールドBGMポーズ解除
	
	//全てのポーズフラグクリア
	Snd_PauseClearAll();

	//共通処理
	Snd_DataSetSub( SND_SCENE_FIELD );

	//Snd_BankFlagSet( SND_BANK_CONTINUE );						//バンクそのまま継続
	Snd_BgmPlay( no );											//BGM再生
	return;
}

//--------------------------------------------------------------
/**
 * @brief	コンテスト画面に切り替わる時のサウンドデータセット
 *
 * @param	no		シーケンスナンバー
 * @param	flag	"未使用"
 *
 * @retval	none
 *
 * ＜データロード順＞
 * 常駐
 * SE
 * BGM
 *
 * 暫定で、バッグのサブシーンもロードしている
 */
//--------------------------------------------------------------
void Snd_ContestDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜サウンドデータロード　コンテストシーン切り替わり＞\n" );
#endif

	//手順(1)
	Snd_Stop();													//全停止

	//共通処理
	Snd_DataSetSub( SND_SCENE_CONTEST );

	Snd_BankFlagSet( SND_BANK_CHANGE );							//バンク切り替えるかフラグをセット
	Snd_BgmPlay( no );											//BGM再生

	/***********************************************************/
	//暫定処理
	//コンテストでバッグの音を使用しているので追加ロードしている
	/***********************************************************/
	//Snd_DataSetByScene( SND_SCENE_SUB_BAG, 0, 0 );	// サウンドデータロード(バッグ)(BGM引継ぎ)

	return;
}

//--------------------------------------------------------------
/**
 * @brief	イメージクリップ(コンテスト)画面に切り替わる時のサウンドデータセット
 *
 * @param	no		シーケンスナンバー
 * @param	flag	"未使用"
 *
 * @retval	none
 *
 * ＜データロード順＞
 * 常駐
 * SE
 * BGM
 *
 * 暫定で、バッグのサブシーンもロードしている
 */
//--------------------------------------------------------------
void Snd_ConImageDataSet( u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜サウンドデータロード　イメージクリップ(コンテスト)シーン切り替わり＞\n" );
#endif

	//手順(1)
	Snd_Stop();													//全停止

	//共通処理
	Snd_DataSetSub( SND_SCENE_CON_IMAGE );

	Snd_BankFlagSet( SND_BANK_CHANGE );							//バンク切り替えるかフラグをセット
	Snd_BgmPlay( no );											//BGM再生

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGMを引き継ぎ、SEを追加ロードする、切り替わりのサウンドデータセット
 *
 * @param	scene		シーン
 *
 * @retval	none
 *
 * ＜データロード順＞
 * 常駐
 * SE
 * BGM(WAVEARC)
 * ADD_SCENE_SE
 */
//--------------------------------------------------------------
static void Snd_AddSceneSeDataSet( u8 scene )
{
#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜サウンドデータロード %d 切り替わり サブ画面＞\n", scene );
#endif

	//共通処理
	//Snd_DataSetSub( scene );

	Snd_DeleteHeapAfterBgm();										//BGMの後ろを消す
	Snd_LoadSeByScene( scene );										//SEシーケンスグループ
	Snd_HeapSaveState(Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SUB_SE));	//階層保存(サブ画面の上を消す)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	デモ画面に切り替わる時のサウンドデータセット
 *
 * @param	scene	シーン
 * @param	no		シーケンスナンバー
 * @param	flag	"未使用"
 *
 * @retval	none
 *
 * ＜データロード順＞
 * 常駐
 * SE
 * BGM(SEQ,BANK,WAVEARC)
 */
//--------------------------------------------------------------
static void Snd_DemoDataSet( u8 scene, u16 no, int flag )
{
	int* heap_save_global	= Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "＜サウンドデータロード　デモシーン切り替わり＞\n" );
#endif

	//手順(1)
	Snd_Stop();													//全停止

	//共通処理
	Snd_DataSetSub( scene );

	//Snd_BankFlagSet( SND_BANK_CONTINUE );						//バンクそのまま継続
	Snd_BgmPlay( no );											//BGM再生

	return;
}

//--------------------------------------------------------------
/**
 * @brief	視線曲に切り替わる時のサウンドデータセット
 *
 * @param	no		シーケンスナンバー
 *
 * @retval	none
 *
 * FIELDから呼ばれることを前提としている！
 */
//--------------------------------------------------------------
void Snd_EyeBgmSet( u16 no )
{
	int ret;
	SND_WORK* wk	= Snd_GetSystemAdrs();

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜サウンドデータロード　視線曲切り替わり＞\n" );
#endif

	//BattleDataSetでシーンのセットをするので、
	//このタイミングでシーンをセットする必要はない！

	//フィールドBGMをポーズするか、停止するかを判別して処理
	Snd_FieldPauseOrStop();

	//Snd_BankFlagSet( SND_BANK_CONTINUE );						//バンクそのまま継続
	ret = Snd_BgmPlay( no );									//BGM再生

	return;
}

//--------------------------------------------------------------
/**
 * @brief	何もロードしていない状態にする(サウンドテストのみで使う)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_HeapStateClear(void)
{
	int* heap_save_start = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_START);
	Snd_HeapLoadState( *heap_save_start );
	//Snd_HeapSaveState( heap_save_start );		//階層保存(全て消す時に使用)
	return;
}


//==============================================================================================
//
//	ヒープ関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BGMの後ろのデータを消す
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_DeleteHeapAfterBgm( void )
{
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_BGM) );				//BGMの後ろを消す
	return;
}

//--------------------------------------------------------------
/**
 * @brief	階層レベルを取得
 *
 * @param	wk		SND_WORK型のアドレス
 * @param	type	階層レベル定義(snd_tool.h参照)
 *
 * @retval	"階層レベル"
 */
//--------------------------------------------------------------
int Snd_GetHeapSaveLv( int type )
{
	int* heap_save;
	SND_WORK* wk = Snd_GetSystemAdrs();

	if( type >= SND_HEAP_SAVE_MAX ){
		GF_ASSERT( (0) && "階層レベルが不正です！" );
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM);
		return *heap_save;
	}

	switch( type ){
	case SND_HEAP_SAVE_START:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_START);
		break;
	case SND_HEAP_SAVE_GLOBAL:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_GLOBAL);
		break;
	case SND_HEAP_SAVE_BGM_BANK:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM_BANK);
		break;
	case SND_HEAP_SAVE_SE:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE);
		break;
	case SND_HEAP_SAVE_BGM:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM);
		break;
	case SND_HEAP_SAVE_SUB_SE:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SUB_SE);
		break;
	case SND_HEAP_SAVE_ME:
		heap_save = Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_ME);
		break;
	};

	return *heap_save;
}


//==============================================================================================
//
//	シーケンス関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	シーケンスを一時停止または再開します。 
 *
 * @param	player	プレイヤーナンバー(sound_data.sadl参照)
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
void Snd_PlayerPause( u8 player, BOOL flag )
{
	u8 handle_no;
	u8* pause_flag;

	if( player == PLAYER_FIELD ){
		pause_flag	= Snd_GetParamAdrs( SND_W_ID_FIELD_PAUSE_FLAG );
		handle_no	= SND_HANDLE_FIELD;

	}else if( player == PLAYER_BGM ){
		pause_flag	= Snd_GetParamAdrs( SND_W_ID_BGM_PAUSE_FLAG );
		handle_no	= SND_HANDLE_BGM;

	}else{
		return;			//何もしない
	}

	//再開させるので、今のBGMナンバーにセットしなおす
	if( flag == FALSE ){
		Snd_NowBgmNoSet( Snd_GetSeqNo(Snd_HandleGet(handle_no)) );
	}

	NNS_SndPlayerPause( Snd_HandleGet(handle_no), flag );
	*pause_flag = flag;	//ポーズしているかフラグ
	return;
}

//--------------------------------------------------------------
/**
 * @brief	全てのポーズしているかフラグのクリア
 *
 * @param	none
 *
 * @retval	none
 *
 * 戦闘でゲームオーバーになって、ポケセンに戻るときなどに、
 * FieldDataSetを呼ぶ前に、ポーズフラグをクリアしないといけない！
 */
//--------------------------------------------------------------
void Snd_PauseClearAll()
{
	u8* field_pause_flag	= Snd_GetParamAdrs( SND_W_ID_FIELD_PAUSE_FLAG );
	u8* bgm_pause_flag		= Snd_GetParamAdrs( SND_W_ID_BGM_PAUSE_FLAG );

	//追加された時の対応忘れを考えると配列で持っていたほうがよさそう
	//これ以上は増えないはずだが。。。
	
	*field_pause_flag = 0;
	*bgm_pause_flag = 0;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスのボリュームを徐々に変更する
 *
 * @param	p		サウンドハンドルのアドレス
 *
 * @retval	none
 *
 * framesが0の時、即座に現在のボリューム値が更新されます。
 * たとえば、現在のボリューム値とは無関係に、
 * ボリュームをある値から、別の値に時間変化させたい場合は、
 * まず、framesを0としてこの関数を呼びだして、現在のボリューム値を更新した後、
 * 再び同じ関数で、目標とするボリューム値を指定します。 
 *
 * シーケンススタート直後のボリューム値は0で、次の NNS_SndMain関数で、127 に変化します。
 * このため、シーケンススタート直後にこの関数を呼びだすと、
 * ボリューム0から徐々に指定のボリュームへ変化するような、フェードイン効果が得られます。 
 *
 * このボリューム値は、 NNS_SndPlayerSetVolume関数の値とは、独立して効果を発揮し、
 * 互いに重ね合わされます。ただし、フェードアウト中は、ここで設定した値は無視されます。 
 */
//--------------------------------------------------------------
void Snd_PlayerMoveVolume( int handle_no, int vol, int frame )
{
	NNS_SndPlayerMoveVolume( Snd_HandleGet(handle_no), vol, frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	全てのシーケンスのボリュームを変更する
 *
 * @param	p		サウンドハンドルのアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_AllPlayerMoveVolume( int vol, int frame )
{
	int i;

	for( i=0; i < SND_HANDLE_MAX ;i++ ){
		Snd_PlayerMoveVolume( i, vol, frame );
	}
	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスの初期ボリューム設定
 *
 * @param	p		サウンドハンドルのアドレス
 * @param	vol		ボリューム(0-127)
 *
 * @retval	none
 *
 * サウンドハンドルが無効の場合は、何もしません。 
 *
 * ボリュームのデフォルト値は、最大の127です。
 * この値の影響はシーケンス全体にかかります。
 *
 * この関数は、NNS_SndArcPlayerStartSeq*関数と NNS_SndArcPlayerStartSeqArc*関数内で
 * 呼びだされています。再度、この関数を呼びだすと、設定した値が上書きされます。
 * 上書きしたくない場合は、 NNS_SndPlayerSetVolume関数などを使ってください。
 *
 * 例
 * Snd_PMVoicePlay( no );
 * Snd_PlayerSetInitialVolume( handle_no. 30 );
 * ボリューム30で再生される
 *
 * そのあと、
 * Snd_PMVoicePlay( no );
 * デフォルトの値127で再生される(元に戻っている)
 *
 * 逆にいうと、常にボリューム30にしたかったら、
 * Snd_PlayerSetInitialVolume( handle_no. 30 );
 * を毎回セットする
 */
//--------------------------------------------------------------
void Snd_PlayerSetInitialVolume( int handle_no, int vol )
{
	//エラー回避
	if( vol < 0 ){
		vol = 0;
	}

	if( vol > 127 ){
		vol = 127;
	}

	//この関数は、NNS_SndArcPlayerStartSeq*関数と NNS_SndArcPlayerStartSeqArc*関数内で
	//呼びだされています。再度、この関数を呼びだすと、設定した値が上書きされます。
	//上書きしたくない場合は、 NNS_SndPlayerSetVolume関数などを使ってください。
	NNS_SndPlayerSetInitialVolume( Snd_HandleGet(handle_no), vol );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	ボイスチャット中の音量操作
 *
 * @param	seq_no		シーケンスナンバー
 * @param	handle_no	ハンドルナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_VChatVolSet( int seq_no, int handle_no )
{
	u8 vol;
	const NNSSndSeqParam* p = NNS_SndArcGetSeqParam( seq_no );	//シーケンスパラメータ取得

	switch( handle_no ){

	//鳴き声
	case SND_HANDLE_PMVOICE:
	case SND_HANDLE_CHORUS:
		vol = PV_VOL_MAX;
		break;

	//鳴き声以外
	default:
		//エラー回避
		if( p == NULL ){
			return;
		}

		vol = p->volume;
		break;
	};

	//ボイスチャット中かチェック
	if( CommIsVChat() == TRUE ){
		Snd_PlayerSetInitialVolume( handle_no, (vol / SND_VCHAT_VOL_LV) );	//音量半分(06.07.20)
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスの初期ボリューム設定(シーケンスナンバー指定版)
 *
 * @param	no		シーケンスナンバー
 * @param	vol		ボリューム(0-127)
 *
 * @retval	none
 *
 * サウンドハンドルが無効の場合は、何もしません。 
 *
 * ボリュームのデフォルト値は、最大の127です。
 * この値の影響はシーケンス全体にかかります。
 *
 * この関数は、NNS_SndArcPlayerStartSeq*関数と NNS_SndArcPlayerStartSeqArc*関数内で
 * 呼びだされています。再度、この関数を呼びだすと、設定した値が上書きされます。
 * 上書きしたくない場合は、 NNS_SndPlayerSetVolume関数などを使ってください。
 *
 * 例
 * Snd_PMVoicePlay( no );
 * Snd_PlayerSetInitialVolume( handle_no. 30 );
 * ボリューム30で再生される
 *
 * そのあと、
 * Snd_PMVoicePlay( no );
 * デフォルトの値127で再生される(元に戻っている)
 *
 * 逆にいうと、常にボリューム30にしたかったら、
 * Snd_PlayerSetInitialVolume( handle_no. 30 );
 * を毎回セットする
 */
//--------------------------------------------------------------
void Snd_PlayerSetInitialVolumeBySeqNo( u16 no, int vol )
{
	u8 player_no = Snd_GetPlayerNo(no);				//seqナンバーから、プレイヤーナンバーを取得
	int type = Snd_GetHandleNoByPlayerNo(player_no);//playerナンバーから、ハンドルナンバーを取得
	Snd_PlayerSetInitialVolume( type, vol );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスを再生(プレイヤー番号指定)
 *
 * @param	handle_no	サウンドハンドルナンバー
 * @param	player_no	プレイヤーナンバー
 * @param	no			BGMナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 *
 * 再生に成功すると、サウンドハンドルにシーケンスが結びつけられます。 
 *
 * シーケンスデータをプレイヤーヒープでロードする時は、
 * 容量が足りないと再生失敗する！
 */
//--------------------------------------------------------------
BOOL Snd_ArcPlayerStartSeqEx( int handle_no, int player_no, u16 no )
{
	return NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(handle_no), player_no, -1, -1, no );
}


//==============================================================================================
//
//	プレイヤー関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	再生中のシーケンスの数を返す
 *
 * @param	player_no	プレイヤー番号
 *
 * @retval	"再生中のシーケンスの数"
 *
 * PLAYER_FIELD	: フィールドBGM
 * PLAYER_ME 	: ME
 * PLAYER_SE_1 	: 効果音
 * PLAYER_SE_2 	: 効果音
 * PLAYER_SE_3 	: 効果音
 * PLAYER_SE_4 	: 効果音
 * PLAYER_PV	: ポケモン鳴き声
 * PLAYER_VOICE	: 音声
 * PLAYER_BGM	: フィールド以外BGM
 */
//--------------------------------------------------------------
int Snd_PlayerCountPlayingSeq( int player_no )
{
	//上限はチェックしていないので注意！
	if( player_no < 0 ){
		GF_ASSERT( (0) && "引数が不正です！" );
	}

	return NNS_SndPlayerCountPlayingSeqByPlayerNo( player_no );
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスナンバーからプレイヤーナンバー取得
 *
 * @param	no		シーケンスナンバー
 *
 * @retval	"プレイヤーナンバー、0xff=取得失敗"
 */
//--------------------------------------------------------------
u8 Snd_GetPlayerNo( u16 no )
{
	const NNSSndSeqParam* param;
	
	if( no == 0 ){
		//GF_ASSERT( (0) && "シーケンスナンバーが不正なのでプレイヤーナンバー取得失敗！" );
		return 0xff;	//エラー
	}

	//サウンドアーカイブ中の各シーケンスに対する、シーケンスパラメータ構造体を取得
	param = NNS_SndArcGetSeqParam( no );
	//OS_Printf( "プレイヤーナンバー = %d\n", param->playerNo );

	if( param == NULL ){
		//GF_ASSERT( (0) && "シーケンスナンバーが不正なのでプレイヤーナンバー取得失敗！" );
		OS_Printf( "シーケンスナンバーが不正なのでプレイヤーナンバー取得失敗！\n" );
		return 0xff;	//エラー
	}

	return param->playerNo;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドハンドルからシーケンスナンバーを取得
 *
 * @param	p			サウンドハンドルのアドレス
 *
 * @retval	"シーケンスナンバー、設定されていない時は-1"
 */
//--------------------------------------------------------------
int Snd_GetSeqNo( NNSSndHandle *p )
{
	return NNS_SndPlayerGetSeqNo( p );
}


//==============================================================================================
//
//	バンク関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	バンク情報構造体のアドレスを取得
 *
 * @param	no		シーケンスナンバー
 *
 * @retval	"バンク情報構造体のアドレス"
 */
//--------------------------------------------------------------
const NNSSndArcBankInfo* Snd_GetBankInfo( int no )
{
	const NNSSndArcBankInfo* info;

	info = NNS_SndArcGetBankInfo( Snd_GetBankNo(no) );

	//無効かチェック
	if( info == NULL ){
		OS_Printf( "バンク情報構造体のアドレスを取得出来ませんでした。\n" );
	}

	return info;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスナンバーからバンクナンバー取得
 *
 * @param	no		シーケンスナンバー
 *
 * @retval	"0=エラー、0以外=バンクナンバー"
 */
//--------------------------------------------------------------
u16 Snd_GetBankNo( int no )
{
	const NNSSndSeqParam* param;
	
	//サウンドアーカイブ中の各シーケンスに対する、シーケンスパラメータ構造体を取得
	param = NNS_SndArcGetSeqParam( no );
	if( param == NULL ){
		OS_Printf( "バンクナンバーが取得出来ませんでした。\n" );
		OS_Printf( "渡されたシーケンスナンバーは %d です。\n", no );
		return 0;
	}

	return param->bankNo;
}


//==============================================================================================
//
//	マイク関連
//
//==============================================================================================
      
//--------------------------------------------------------------
/**
 * @brief	マイクコールバック関数
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void MicCallback( MICResult /*result*/, void* /*arg*/ )
{
    OS_Printf( "Mic Callback Done\n" );
}

//--------------------------------------------------------------
/**
 * @brief	録音開始
 *
 * @param	p		MICAutoParam型のアドレス
 *
 * @retval	"MIC_RESULT_SUCCESS		処理が正常に完了"
 * @retval	"それ以外				何らかの原因で失敗"
 */
//--------------------------------------------------------------
MICResult Snd_MicStartAutoSampling( MICAutoParam* p )
{
	MICResult ret;

	ret = MIC_StartAutoSampling( p );

	if( ret != MIC_RESULT_SUCCESS ){
		OS_Printf( "マイク自動サンプリング開始が失敗しました！\n" );
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	録音停止
 *
 * @param	none
 *
 * @retval	"MIC_RESULT_SUCCESS		処理が正常に完了"
 * @retval	"それ以外				何らかの原因で失敗"
 */
//--------------------------------------------------------------
MICResult Snd_MicStopAutoSampling(void)
{
	MICResult ret;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ret = MIC_StopAutoSampling();

	if( ret != MIC_RESULT_SUCCESS ){
		OS_Printf( "マイク自動サンプリング停止が失敗しました！\n" );
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	手動録音
 * @param	type      サンプリングレートのタイプ
 * @param	heap      記録領域
 * @param	callback  記録した際のコールバック
 * @param	arg       コールバックに渡す引数ポインタ
 * @retval	"MIC_RESULT_SUCCESS		処理が正常に完了"
 * @retval	"それ以外				何らかの原因で失敗"
 */
//--------------------------------------------------------------
MICResult Snd_MicManualSampling(MICSamplingType type ,void* heap,MICCallback callback,void* arg)
{
	MICResult ret;

    ret = MIC_DoSamplingAsync( type, heap, callback, arg);
	if( ret != MIC_RESULT_SUCCESS ){
        OS_Printf( "マイク手動サンプリングが失敗\n" );
	}
	return ret;
}

//==============================================================================================
//
//	波形再生関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	波形ハンドルのアドレスを取得
 *
 * @param	no		使用しているチャンネルナンバー
 *
 * @retval	"波形ハンドルのアドレス"
 *
 * BGM		NNSSndHandle
 * 波形		NNSSndWaveOutHandle
 * ハンドルのタイプが違うので注意！
 */
//--------------------------------------------------------------
NNSSndWaveOutHandle * Snd_WaveOutHandleGet( u32 no )
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "チャンネルナンバーが不正です！" );
	}

	if( (no == WAVEOUT_CH_NORMAL) && (*ch_normal_flag == 0) ){	//確保フラグがOFFだったら
		GF_ASSERT( (0) && "確保していないNORMALハンドルにアクセスしています！" );
	}

	if( (no == WAVEOUT_CH_CHORUS) && (*ch_chorus_flag == 0) ){	//確保フラグがOFFだったら
		GF_ASSERT( (0) && "確保していないCHORUSハンドルにアクセスしています！" );
	}

	if( no == WAVEOUT_CH_NORMAL ){
		return Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_NORMAL);
	}else{
		return Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_CHORUS);
	}
}
 
//--------------------------------------------------------------
/**
 * @brief	波形再生用にチャンネルを確保する
 *
 * @param	no		使用するチャンネルナンバー
 *
 * @retval	BOOL	TRUE=成功、FALSE=失敗
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutAllocChannel( u32 no )
{
	u8* ch_normal_flag;
	u8* ch_chorus_flag;
	NNSSndWaveOutHandle* wave_handle;
	SND_WORK* wk = Snd_GetSystemAdrs();

	ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "チャンネルナンバーが不正です！" );
	}

	if( no == WAVEOUT_CH_NORMAL ){

		if( *ch_normal_flag == 0 ){		//確保フラグがOFFだったら

			//波形ハンドルのアドレス取得
			wave_handle = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_NORMAL);
			*wave_handle = NNS_SndWaveOutAllocChannel( no );			//CH確保

			if ( *wave_handle == NNS_SND_WAVEOUT_INVALID_HANDLE ) {
				OS_Printf("NNS_SndWaveOutAllocChannel is Failed\n");
				return FALSE;			//失敗
			}
			*ch_normal_flag = 1;		//確保フラグON
		}else{
			GF_ASSERT( (0) && "チャンネルを開放していないのに、確保しようとしています！" );
		}

	}else{

		if( *ch_chorus_flag == 0 ){		//確保フラグがOFFだったら

			wave_handle = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_HANDLE_CHORUS);
			*wave_handle = NNS_SndWaveOutAllocChannel( no );			//CH確保

			if ( *wave_handle == NNS_SND_WAVEOUT_INVALID_HANDLE ) {
				OS_Printf("NNS_SndWaveOutAllocChannel is Failed\n");
				return FALSE;			//失敗
			}
			*ch_chorus_flag = 1;		//確保フラグON
		}else{
			GF_ASSERT( (0) && "チャンネルを開放していないのに、確保しようとしています！" );
		}
	}

	return TRUE;		//成功
}
 
//--------------------------------------------------------------
/**
 * @brief	波形再生用のチャンネルを解放する
 *
 * @param	no		使用するチャンネルナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutFreeChannel( u32 no )
{
	NNSSndWaveOutHandle* wave_handle;
	SND_WORK* wk		= Snd_GetSystemAdrs();
	u8* ch_normal_flag	= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag	= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "チャンネルナンバーが不正です！" );
		return;
	}

	if( no == WAVEOUT_CH_NORMAL ){
		if( *ch_normal_flag == 1 ){	//確保フラグがONだったら

			wave_handle = Snd_WaveOutHandleGet(no);
			NNS_SndWaveOutFreeChannel( *wave_handle );
			*ch_normal_flag = 0;	//確保フラグOFF

		}else{
			GF_ASSERT( (0) && "確保されていないチャンネルを開放しようとしています！" );
		}
	}else{
		if( *ch_chorus_flag == 1 ){	//確保フラグがONだったら

			wave_handle = Snd_WaveOutHandleGet(no);
			NNS_SndWaveOutFreeChannel( *wave_handle );
			*ch_chorus_flag = 0;	//確保フラグOFF

		}else{
			GF_ASSERT( (0) && "確保されていないチャンネルを開放しようとしています！" );
		}
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	波形再生
 *
 * @param	p		WAVEOUT_WORK型のポインタ
 * @param	ch		使用するチャンネルナンバー(通常は、WAVEOUT_CH_NORMAL)
 *
 * @retval	BOOL	TRUE=成功、FALSE=失敗
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutStart( WAVEOUT_WORK* p, u32 ch )
{
	int ret;

	ret = NNS_SndWaveOutStart( *p->handle, p->format, p->dataaddr, p->loopFlag, p->loopStartSample,
								p->samples, p->sampleRate, p->volume, p->speed, p->pan );

	if( ret == FALSE ){
		OS_Printf( "波形再生失敗！\n" );

		//この関数が呼ばれる時は、必ずチャンネル確保しているはずなので、
		//再生に失敗した時は、開放処理を入れるようにする！
		Snd_WaveOutFreeChannel( ch );
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	波形停止
 *
 * @param	no		使用するチャンネルナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutStop( u32 no )
{
	NNS_SndWaveOutStop( *Snd_WaveOutHandleGet(no) );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	波形再生中かチェック
 *
 * @param	no		使用するチャンネルナンバー
 *
 * @retval	BOOL	TRUE=再生中、FALSE=再生中でない
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutIsPlaying( u32 no )
{
	return NNS_SndWaveOutIsPlaying( *Snd_WaveOutHandleGet(no) );
}

//--------------------------------------------------------------
/**
 * @brief	波形再生のPAN設定
 *
 * @param	no		使用するチャンネルナンバー
 * @param	pan		パンの値(0-127、64がcenter)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutSetPan( u32 no, u8 pan )
{
	u8 set_pan;

	if( pan > 127 ){
		set_pan = 127;
	}else{
		set_pan = pan;
	}

	NNS_SndWaveOutSetPan( *Snd_WaveOutHandleGet(no), set_pan );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	波形再生の再生スピード設定
 *
 * @param	no		使用するチャンネルナンバー
 * @param	spd		再生スピード
 *
 * @retval	none
 *
 * 2分の1倍速	(32768 / 2)
 * 1倍速		(32768)
 * 2倍速		(32768 * 2)
 * 3倍速		(32768 * 3)
 *
 * 再生スピードを速くすると、再生時間が短くなり、再生される音の高さが高くなります。 
 */
//--------------------------------------------------------------
void Snd_WaveOutSetSpeed( u32 no, u32 spd )
{
	NNS_SndWaveOutSetSpeed( *Snd_WaveOutHandleGet(no), spd );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	波形再生のボリューム変更
 *
 * @param	no		使用するチャンネルナンバー
 * @param	vol		ボリューム値(0-127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutSetVolume( u32 no, int vol )
{
	//ボイスチャット中かチェック
	if( CommIsVChat() == TRUE ){
		NNS_SndWaveOutSetVolume( *Snd_WaveOutHandleGet(no), (vol/SND_VCHAT_VOL_LV) );	//音量操作
	}else{
		NNS_SndWaveOutSetVolume( *Snd_WaveOutHandleGet(no), vol );
	}
	return;
}
 

//==============================================================================================
//
//	波形逆再生関連(ポケモンの鳴き声専用)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	逆再生のポケモン鳴き声を再生
 *
 * @param	no		ポケモンナンバー
 * @param	vol		ボリューム(0-127)
 * @param	pan		パン(0-127)
 * @param	ch		使用するチャンネルナンバー(通常は、WAVEOUT_CH_NORMAL)
 * @param	heap_id	ヒープID
 *
 * @retval	BOOL	TRUE=成功、FALSE=失敗
 *
 * 内部で逆再生用のバッファを確保しています。
 *
 * Snd_WaveOutStopReverse(...)を呼んで、バッファを開放してください。
 *
 * ポケモンナンバーと鳴き声の波形アーカイブナンバーが同じになるようにする！
 */
//--------------------------------------------------------------
BOOL Snd_WaveOutStartReverse( u16 no, int vol, int pan, u32 ch, int heap_id )
{
	u8* reverse_flag;
	const NNSSndArcWaveArcInfo* info;
	u32 size;
	int size2,ret;
	SND_WORK* wk = Snd_GetSystemAdrs();
	void** reverse_buf = Snd_GetParamAdrs(SND_W_ID_REVERSE_BUF);

	if( (ch != WAVEOUT_CH_NORMAL) && (ch != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "チャンネルナンバーが不正です！" );
	}

	//波形アーカイブ情報構造体NNSSndArcWaveArcInfoのポインタを返します。
	//info =  NNS_SndArcGetWaveArcInfo( WAVE_ARC_PV001 );
	info = NNS_SndArcGetWaveArcInfo( no );
	if( info == NULL ){
		GF_ASSERT( (0) && "無効な波形アーカイブ番号が指定されました！" );
		return FALSE;
	}

	//ファイルサイズ取得
	size = NNS_SndArcGetFileSize( info->fileId );
	if( size == 0 ){
		GF_ASSERT( (0) && "ファイルIDが無効です！" );
		return FALSE;
	}
	OS_Printf( "ファイルサイズ = %d\n", size );	//.smapと比較してみる

	//通常の逆再生だったら
	if( ch == WAVEOUT_CH_NORMAL ){
		//バッファ確保
		*reverse_buf = sys_AllocMemory( heap_id, size );
		if( *reverse_buf == NULL ){
			GF_ASSERT( (0) && "メモリ確保に失敗しました！" );
			return FALSE;
		}
		memset( *reverse_buf, 0, size );

		//サウンドアーカイブ中のファイルを読み込む
		size2 = NNS_SndArcReadFile( info->fileId, *reverse_buf, size, 0 );
		if( size2 == -1 ){
			GF_ASSERT( (0) && "読み込みに失敗しました！" );
			return FALSE;
		}

		//データを入れ替える
		Snd_BufReverse( *reverse_buf, size );
	}

	//WAVEOUT_WORK型にパラメータセット
	{
		WAVEOUT_WORK waveout_wk;
		waveout_wk.handle			= Snd_WaveOutHandleGet(ch);	//波形再生ハンドル
		waveout_wk.format			= NNS_SND_WAVE_FORMAT_PCM8;	//波形データフォーマット
		waveout_wk.dataaddr			= *reverse_buf;				//波形データの先頭アドレス
		waveout_wk.loopFlag			= FALSE;					//ループフラグ
		waveout_wk.loopStartSample	= 0;						//ループ開始サンプル位置
		waveout_wk.samples			= size;						//波形データのサンプル数
		waveout_wk.sampleRate		= 13379;					//波形データのサンプリングレート
		waveout_wk.volume			= vol;						//音量
		waveout_wk.speed			= 24576;					//再生スピード
		waveout_wk.pan				= pan;						//パン(0-127)

		//波形再生
		ret = Snd_WaveOutStart( &waveout_wk, ch );

		//ボイスチャットの音量対応
		Snd_WaveOutSetVolume( ch, vol );

		//BANKの設定を"PCM8"にするとうまくいく
	}

	reverse_flag = Snd_GetParamAdrs( SND_W_ID_REVERSE_FLAG );
	*reverse_flag = 1;	//逆再生使用フラグON

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	データを入れ替える
 *
 * @param	p		波形データを格納したバッファのポインタ
 * @param	size	波形データサイズ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_BufReverse( u8* p, u32 size )
{
	int i;
	u8 temp;

	//データを入れ替える( [0]-[MAX]、[1]-[MAX-1]... )
	for( i=0; i < (size / 2) ;i++ ){
		temp		= p[i];			//退避
		p[i]		= p[size-1-i];
		p[size-1-i]	= temp;
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	逆再生のポケモン鳴き声を停止してバッファを開放する
 *
 * @param	no		使用するチャンネルナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_WaveOutStopReverse( u32 no )
{
	SND_WORK* wk		= Snd_GetSystemAdrs();
	u8* reverse_flag	= Snd_GetParamAdrs(SND_W_ID_REVERSE_FLAG);
	void** reverse_buf	= Snd_GetParamAdrs(SND_W_ID_REVERSE_BUF);

	if( (no != WAVEOUT_CH_NORMAL) && (no != WAVEOUT_CH_CHORUS) ){
		GF_ASSERT( (0) && "チャンネルナンバーが不正です！" );
	}

	Snd_WaveOutStop( no );										//鳴き声停止

	//逆再生使用フラグ
	if( *reverse_flag == 1 ){									//逆再生使用フラグが立っていたら
		*reverse_flag = 0;										//逆再生使用フラグOFF
		sys_FreeMemoryEz( *reverse_buf );						//バッファ開放
	}

	return;
}


//==============================================================================================
//
//	キャプチャ関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	キャプチャースレッドを起動(とりあえず優先度は固定)
 *
 * @param	none
 *
 * @retval	none
 *
 * キャプチャースレッドを起動しておくと、キャプチャー処理がIRQハンドラではなく、
 * キャプチャースレッドで処理されるようになります。 
 *
 * スレッドの優先度threadPrioは、通常、ストリームスレッドよりも高く設定します。
 * 処理が遅れると、正常な再生が行われなくなりますので、注意してください。 
 */
//--------------------------------------------------------------
void Snd_CaptureCreateThread(void)
{
    NNS_SndCaptureCreateThread( CAPTURE_THREAD_PRIO );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	キャプチャが実行中か取得
 *
 * @param	none
 *
 * @retval	"TRUE=実行中、FALSE=実行していない"
 */
//--------------------------------------------------------------
BOOL Snd_CaptureIsActive(void)
{
	int type,ret;

	ret = NNS_SndCaptureIsActive();

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "キャプチャが有効か？ = %d\n", ret );

	//有効だったら、キャプチャタイプを表示
	if( ret == TRUE ){
		type = Snd_CaptureGetCaptureType();

		if( type == NNS_SND_CAPTURE_TYPE_REVERB ){
			OS_Printf( "現在のキャプチャは、NNS_SND_CAPTURE_TYPE_REVERB\n" );
		}else if( type == NNS_SND_CAPTURE_TYPE_EFFECT ){
			OS_Printf( "現在のキャプチャは、NNS_SND_CAPTURE_TYPE_EFFECT\n" );
		}else if( type == NNS_SND_CAPTURE_TYPE_SAMPLING ){
			OS_Printf( "現在のキャプチャは、NNS_SND_CAPTURE_TYPE_SAMPLING\n" );
		}
	}
#endif

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	実行中のキャプチャタイプを取得
 *
 * @param	none
 *
 * @retval	"NNS_SND_CAPTURE_TYPE_REVERB = リバーブ"
 * @retval	"NNS_SND_CAPTURE_TYPE_EFFECT = エフェクト"
 * @retval	"NNS_SND_CAPTURE_TYPE_SAMPLING = サンプリング"
 *
 * キャプチャーが実行中の時のみ呼びだすことができます。
 * キャプチャーが実行中かどうかを調べるためには、 NNS_SndCaptureIsActive関数を呼びだします。 
 */
//--------------------------------------------------------------
NNSSndCaptureType Snd_CaptureGetCaptureType(void)
{
	return NNS_SndCaptureGetCaptureType();
}

//--------------------------------------------------------------
/**
 * @brief	出力エフェクト処理を変更
 *
 * @param	none
 *
 * @retval	none
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL		何も処理しません(通常のステレオモード)
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO		モノラルモード 
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND	サラウンドモード 
 * DSスピーカーから出力させたときに、
 * スピーカー位置より広がって音を感じられるようにするエフェクトをかけます。
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE	ヘッドフォンモード 
 * ヘッドフォン使用時に、耳の負担を軽減するエフェクトをかけます。
 */
//--------------------------------------------------------------
void Snd_CaptureChangeOutputEffect( NNSSndCaptureOutputEffectType type )
{
	switch( type ){
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE:
		break;
	default:
		return;	//何もしない
	}

    NNS_SndCaptureChangeOutputEffect( type );
	return;
}
 

//==============================================================================================
//
//	キャプチャ　リバーブ
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	出力エフェクト処理を開始
 *
 * @param	none
 *
 * @retval	none
 *
 * キャプチャー機能を使ってミキサー出力をキャプチャし、
 * コールバック関数でエフェクト処理を行った後、最終音声として出力します。
 * エフェクト動作中は、16チャンネル中の2チャンネル（チャンネル1及びチャンネル3）を消費します。
 * チャンネル1またはチャンネル3が、シーケンスによって使用中の場合、
 * 発音中の音は強制的に停止させられます。 
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL		何も処理しません(通常のステレオモード)
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO		モノラルモード 
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND	サラウンドモード 
 * DSスピーカーから出力させたときに、
 * スピーカー位置より広がって音を感じられるようにするエフェクトをかけます。
 *
 * NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE	ヘッドフォンモード 
 * ヘッドフォン使用時に、耳の負担を軽減するエフェクトをかけます。
 */
//--------------------------------------------------------------
void Snd_CaptureStartOutputEffect( NNSSndCaptureOutputEffectType type )
{
	SND_WORK* wk	= Snd_GetSystemAdrs();
	s8* capture_buf = Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF);

	switch( type ){
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND:
	case NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE:
		//NNS_SndCaptureStartOutputEffect( wk->sCaptureBuffer, sizeof( wk->sCaptureBuffer ), type );
		NNS_SndCaptureStartOutputEffect( capture_buf, CAPTURE_BUFSIZE, type );
		break;
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	リバーブ　開始
 *
 * @param	vol		リバーブ成分のボリューム(0-63)
 *
 * @retval	BOOL	TRUE=成功、FALSE=失敗
 *
 * 音声を再生しながらこの関数を呼びだすと、再生される音が途切れます。 
 *
 * チャンネル1,3を使用するので注意！
 */
//--------------------------------------------------------------
BOOL Snd_CaptureStartReverb( int vol )
{
	SND_WORK* wk	= Snd_GetSystemAdrs();
	s8* capture_buf = Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF);

	//return NNS_SndCaptureStartReverb( wk->sCaptureBuffer, sizeof( wk->sCaptureBuffer ),
	return NNS_SndCaptureStartReverb( capture_buf, CAPTURE_BUFSIZE,
										CAPTURE_FORMAT, REVERB_SAMPLING_RATE, vol );

	//リバーブバッファが大きいほど、遅延時間が長くなり、深いリバーブがかかります。
	//サンプリングレートは、値が大きいほどリバーブ成分の音質は良くなりますが、
	//その分遅延時間は短くなります。遅延時間を変えたくない場合は、
	//リバーブバッファサイズを大きくする必要があります。
	//遅延時間＝bufsize / samplerate;
}

//--------------------------------------------------------------
/**
 * @brief	リバーブ　終了
 *
 * @param	frame	フレーム数
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CaptureStopReverb( int frame )
{
	NNS_SndCaptureStopReverb( frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	リバーブ　ボリューム変更
 *
 * @param	vol		リバーブ成分のボリューム(0-63)
 * @param	frame	フレーム数
 *
 * @retval	none
 *
 * frameで指定したフレーム数で、徐々に現在のボリューム値から、
 * volで指定したボリューム値へ変化します。  
 *
 * リバーブが動作していない場合は、何もしません。 
 */
//--------------------------------------------------------------
void Snd_CaptureReverbVol( int vol, int frame )
{
	NNS_SndCaptureSetReverbVolume( vol, frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	エフェクト開始
 *
 * @param	none
 *
 * @retval	BOOL	TRUE=成功、FALSE=失敗
 *
 * チャンネル1,3を使用するので注意！
 */
//--------------------------------------------------------------
BOOL Snd_CaptureStartEffect(void)
{
	SND_WORK* wk				= Snd_GetSystemAdrs();

	//MI_CpuClear8( &wk->callbackInfo, sizeof(wk->callbackInfo) );
	MI_CpuClear8( Snd_GetParamAdrs(SND_W_ID_CALLBACK_INFO), sizeof(EffectCallbackInfo) );

/*
	//return NNS_SndCaptureStartEffect( wk->sCaptureBuffer, sizeof( wk->sCaptureBuffer ),
	return NNS_SndCaptureStartEffect( wk->sCaptureBuffer, CAPTURE_BUFSIZE,
				CAPTURE_FORMAT, SAMPLING_RATE, 2, EffectCallback, &wk->callbackInfo );
*/

	//-----------------------------------------------------
	//サンプリングレートが低いと、キャプチャ機能を使う時に、
	//何も加工していなくても、音が悪くなるので注意！
	//-----------------------------------------------------

#if 1
	//return NNS_SndCaptureStartEffect( Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF),CAPTURE_BUFSIZE,
	//									CAPTURE_FORMAT, SAMPLING_RATE,2, 
	//								EffectCallback, Snd_GetParamAdrs(SND_W_ID_CALLBACK_INFO) );

	//テスト中(06.02.24)
	return NNS_SndCaptureStartEffect( Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF),CAPTURE_BUFSIZE,
										//NNS_SND_CAPTURE_FORMAT_PCM16, 16000,2, 
										NNS_SND_CAPTURE_FORMAT_PCM16, 22000,2, 
									EffectCallback2, Snd_GetParamAdrs(SND_W_ID_CALLBACK_INFO) );
#else
	 //start sampling
    (void)NNS_SndCaptureStartSampling( Snd_GetParamAdrs(SND_W_ID_CAPTURE_BUF),CAPTURE_BUFSIZE,
										CAPTURE_FORMAT,SAMPLING_RATE,2,
										SamplingCallback,NULL );
	return 0;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	エフェクト停止
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CaptureStopEffect(void)
{
	NNS_SndCaptureStopEffect();
	return;
}

//--------------------------------------------------------------
/**
 * @brief	エフェクトレベルの操作
 *
 * @param	level	レベル(0-8)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_CaptureEffectLevel( int level )
{
	u8* filter_size = Snd_GetParamAdrs(SND_W_ID_FILTER_SIZE);
	//未対応
	
	if( level > 8 ){
		level = 8;
	}else if( level < 0 ){
		level = 0;
	}

	*filter_size = level;
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	エフェクトのコールバック関数
 *
 * @param	bufferL_p	Lミキサー成分
 * @param	bufferR_p	Rミキサー成分
 * @param	len			バッファのサイズ
 * @param	format		NNS_SndCaptureStartEffect関数の引数(CAPTURE_FORMAT)と同じものが渡される
 * @param	arg			NNS_SndCaptureStartEffect関数の引数(callbackInfo)と同じものが渡される
 *
 * @retval	none
 *
 * 簡単なローパスフィルタ（移動平均）をかけて出力している
 *
 * 一定期間の間隔を定め、その間隔内の平均値を連続して計算することによって
 * 趨勢(すうせい)的な動向を知ろうとするもの。
 * (ある方向へと動く勢い )
 */
//--------------------------------------------------------------
static void EffectCallback( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg )
{
    smp_t* lp = (smp_t*)bufferL_p;
    smp_t* rp = (smp_t*)bufferR_p;
    EffectCallbackInfo* info = (EffectCallbackInfo*)arg;
    smp_t org[ FILTER_SIZE-1 ][2];

    int samples;
    int x;
    int i, j;
    
	//サンプルが8ビットPCMはそのまま
	//サンプルが16ビットPCMだったらバッファのサイズを半分にする
    samples = ( format == NNS_SND_CAPTURE_FORMAT_PCM8 ) ? len : ( len >> 1 );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\nSND_EFF=================================\n" );
	OS_Printf( "format = %d\n", format );			//0
	OS_Printf( "len = %d\n", len );					//1024
	OS_Printf( "samples = %d\n", samples );			//512
#endif
    
	//--------------------------------------------
	//例 バッファサイズ = 24 フィルターサイズ = 8
	//lp[0+24-8+1]=17
	//17,18,19,20,21,22,23を保存
	//--------------------------------------------
    //バッファの一番後ろから、フィルターサイズ分を保存
    for( i = 0; i < FILTER_SIZE-1; i++ ) {
        org[i][0] = lp[ i + samples - FILTER_SIZE + 1 ];
        org[i][1] = rp[ i + samples - FILTER_SIZE + 1 ];
		OS_Printf( "org[i][左] = %d\n", org[i][0] );
    }
    
	//--------------------------------------------
	//例 バッファサイズ = 24 フィルターサイズ = 8
    //for( i = 24 - 1; i >= 8 - 1 ; i-- ){
	//23...8まで処理する
	//--------------------------------------------
	//バッファの一番後ろから、フィルターサイズの値より小さくなるまで処理する
    for( i = samples - 1; i >= FILTER_SIZE - 1 ; i-- ){

		//--------------------------------------------
		//例 バッファサイズ = 24 フィルターサイズ = 8
		//x += lp[ 23 - 0 ];
		//(-0から-7まで)
		//x += lp[ 23 - 7 ];
		//フィルターサイズ分足していく
		//--------------------------------------------
		//Lミキサー成分
        x = 0;
        for( j = 0 ; j < FILTER_SIZE ; j++ ) {	//フィルターサイズ分足していく
            x += lp[ i - j ];
        }
        lp[ i ] = (smp_t)(x /= FILTER_SIZE);	//フィルターサイズで割り平均で上書きする
        
		//Rミキサー成分
        x = 0;
        for( j = 0 ; j < FILTER_SIZE ; j++ ) {	//フィルターサイズ分足していく
            x += rp[ i - j ];
        }
        rp[ i ] = (smp_t)(x /= FILTER_SIZE);	//フィルターサイズで割り平均で上書きする
    }
    
#if FILTER_SIZE >= 2    
	//--------------------------------------------
	//例 バッファサイズ = 24 フィルターサイズ = 8
    //for( i = 8 - 2; i >= 0 ; i-- ){
	//6...0まで処理する
	//--------------------------------------------
    for( i = FILTER_SIZE - 2 ; i >= 0 ; i-- ){

		//Lミキサー成分
        x = lp[ i ];
        for( j = 1 ; j < FILTER_SIZE ; j++ ) {	//フィルターサイズ分
            x += GetSample( lp, i-j, 0, info );
        }
        lp[ i ] = (smp_t)(x /= FILTER_SIZE);	//フィルターサイズで割り平均で上書きする
        
		//Rミキサー成分
        x = rp[ i ];
        for( j = 1 ; j < FILTER_SIZE ; j++ ) {
            x += GetSample( rp, i-j, 1, info );
        }
        rp[ i ] = (smp_t)(x /= FILTER_SIZE);	//フィルターサイズで割り平均で上書きする
    }
#endif
    
	//キャプチャが完成した領域のフィルタサイズ分を
	//保存しておいたデータで上書きする
	//(バッファの一番後ろから、フィルターサイズ分を保存しておいたデータ)
    for( i = 0; i < FILTER_SIZE-1; i++ ) {
        info->sample[i][0] = org[i][0];
        info->sample[i][1] = org[i][1];
    }

	//メインメモリに確実に書き込む
    DC_FlushRange( bufferL_p, len );
    DC_FlushRange( bufferR_p, len );

	//引数に渡されるバッファは、(この関数内ではinfo)
	//キャプチャが完了した領域を指しています。
	//この領域を修正することで、実際に出力される音を変更することができます。 
}
 
//--------------------------------------------------------------
/**
 * @brief	サンプルの値取得
 *
 * @param	p			ミキサー成分
 * @param	x			i-j
 * @param	n
 * @param	info		NNS_SndCaptureStartEffect関数の引数(callbackInfo)と同じものが渡される
 *
 * @retval	none
 */
//--------------------------------------------------------------
static inline smp_t GetSample( smp_t* p, int x, int n, const EffectCallbackInfo* info )
{
	//i-jが0以上の時は、ミキサー成分の値をそのまま返す
    if ( x >= 0 ){
		return p[x];
	}

	//i-jが0未満の時、x(i-j)の値を調整した値を取得
    x += FILTER_SIZE-1;
    return info->sample[x][n];
}

static inline int abs( int x )
{
    return x >= 0 ? x : -x;
}

void SamplingCallback( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg )
{
#pragma unused( arg )    
    smp_t* lp = (smp_t*)bufferL_p;
    smp_t* rp = (smp_t*)bufferR_p;
    u32 samples;
    long sum = 0;
    int i;
    
    samples = ( format == NNS_SND_CAPTURE_FORMAT_PCM8 ) ? len : ( len >> 1 );
    
    for( i = 0 ; i < samples ; i++ ) {
        sum += abs( lp[ i ] ) + abs( rp[ i ] );
    }

    sum /= samples * 2;

#if 1
    //for( i = 0 ; i < samples ; i++ ) {
	//	if( sum < ( abs(lp[i]) + abs(rp[i]) ) ){
			//lp[i] = lp[i] - (sum/10);
			//rp[i] = rp[i] - (sum/10);
	//		lp[i] = sum;
	//		rp[i] = sum;
	//	}
    //}
    for( i = 0 ; i < samples ; i++ ) {
		lp[i] += 1000;
		rp[i] += 1000;
	}

   	//メインメモリに確実に書き込む
    DC_FlushRange( bufferL_p, len );
    DC_FlushRange( bufferR_p, len );
#endif
 
    OS_Printf("output level : %5d\n", sum );
}


//==============================================================================================
//
//	トラック操作
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	トラックミュート
 *
 * @param	handle_no	サウンドハンドルナンバー
 * @param	bitmask		トラックビットマスク
 * @param	flag		TRUE=ミュート、FALSE=解除
 *
 * @retval	none
 *
 * trackBitMaskで、設定するトラックを指定します。
 * 下位ビットから順に、トラック0、トラック1、トラック2、、、を表し、
 * ビットが立っているトラック全てに対して、ミュートの設定を変更します。
 * 例えば、トラック2とトラック5のミュート設定を変更したい場合は、 
 * (1 << 2) | (1 << 5) すなわち、0x0024 とします。 
 */
//--------------------------------------------------------------
void Snd_PlayerSetTrackMute( int handle_no, u16 bitmask, BOOL flag )
{
	NNS_SndPlayerSetTrackMute( Snd_HandleGet(handle_no), bitmask, flag );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	トラックボリューム変更
 *
 * @param	p			サウンドハンドルのアドレス
 * @param	bitmask		トラックビットマスク
 * @param	vol			ボリューム
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PlayerSetTrackVolume( NNSSndHandle *p, u16 bitmask, int vol )
{
	NNS_SndPlayerSetTrackVolume( p, bitmask, vol );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	トラック音程変更
 *
 * @param	handle_no	サウンドハンドルナンバー
 * @param	bitmask		トラックビットマスク
 * @param	pitch		音程変化の値(-32768～32767)
 *
 * @retval	none
 *
 * pitchは正の値で高い方へ、負の値で低い方へ変化します。 
 * ±64でちょうど半音変化します。（呼ぶたびに効果が累積されるわけではありません)
 */
//--------------------------------------------------------------
void Snd_PlayerSetTrackPitch( int handle_no, u16 bitmask, int pitch )
{
	NNS_SndPlayerSetTrackPitch( Snd_HandleGet(handle_no), bitmask, pitch );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	トラック音程変更(シーケンスナンバー指定版)
 *
 * @param	no			シーケンスナンバー
 * @param	bitmask		トラックビットマスク
 * @param	pitch		音程変化の値(-32768～32767)
 *
 * @retval	none
 *
 * pitchは正の値で高い方へ、負の値で低い方へ変化します。 
 * ±64でちょうど半音変化します。（呼ぶたびに効果が累積されるわけではありません)
 */
//--------------------------------------------------------------
void Snd_PlayerSetTrackPitchBySeqNo( u16 no, u16 bitmask, int pitch )
{
	u8 player_no = Snd_GetPlayerNo(no);				//seqナンバーから、プレイヤーナンバーを取得
	int type = Snd_GetHandleNoByPlayerNo(player_no);//playerナンバーから、ハンドルナンバーを取得
	Snd_PlayerSetTrackPitch( type, bitmask, pitch );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	トラックパン変更
 *
 * @param	handle_no	サウンドハンドルナンバー
 * @param	bitmask		トラックビットマスク
 * @param	pan			パン変化の値(-128～127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PlayerSetTrackPan( int handle_no, u16 bitmask, int pan )
{
	NNS_SndPlayerSetTrackPan( Snd_HandleGet(handle_no), bitmask, pan );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	テンポ変更
 *
 * @param	handle_no	サウンドハンドルナンバー
 * @param	tempo		倍率(256=1倍)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PlayerSetTempoRatio( int handle_no, int tempo )
{
	NNS_SndPlayerSetTempoRatio( Snd_HandleGet(handle_no), tempo );
	return;
}


//==============================================================================================
//
//	その他関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	モノラルフラグを変更
 *
 * @param	flag	TRUE=モノラル、FALSE=ステレオ
 *
 * @retval	none
 *
 * デフォルトは、FALSEです。 
 *
 * モノラルフラグを有効にすると、パンの設定値を無視して、
 * 全ての発音が中央の定位で行われます。 
 */
//--------------------------------------------------------------
void Snd_SetMonoFlag( BOOL flag )
{
	NNS_SndSetMonoFlag( flag );
	mono_flag = flag;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フェードカウンターセット
 *
 * @param	frame		フレーム数
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_FadeCountSet( int frame )
{
	int* fade_count = Snd_GetParamAdrs(SND_W_ID_FADE_COUNT);
	*fade_count = frame;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	次のBGMを鳴らすまでのウェイトセット
 *
 * @param	frame		フレーム数
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_NextWaitSet( int frame )
{
	int* next_wait = Snd_GetParamAdrs(SND_W_ID_NEXT_WAIT);
	*next_wait = frame;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	次のBGMを鳴らすまでのウェイトチェック(カウンターを減らしています)
 *
 * @param	none
 *
 * @retval	"0=終了、0以外=カウンター値"
 */
//--------------------------------------------------------------
int Snd_NextWaitCheck()
{
	u16* next_wait = Snd_GetParamAdrs(SND_W_ID_NEXT_WAIT);

	if( *next_wait <= 0 ){
		*next_wait = 0;
		return 0;
	}

	(*next_wait)--;
	return *next_wait;
}

//--------------------------------------------------------------
/**
 * @brief	マスターボリューム設定(デフォルトは127)
 *
 * @param	vol		ボリューム(0-127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
#if 0
void Snd_SetMasterVolume( int vol )
{
	NNS_SndSetMasterVolume( vol );
	return;
}
#endif

//--------------------------------------------------------------
/**
 * @brief	波形格納バッファのアドレス取得(仮)
 *
 * @param	vol		ボリューム(0-127)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void* Snd_GetWaveBufAdrs(void)
{
	return &sWaveBuffer[0];
}

//--------------------------------------------------------------
/**
 * @brief	プレイヤーヒープを作成(snd_test.cでのみ使用)
 *
 * @param	player_no	プレイヤーナンバー
 * @param	size		プレイヤーヒープサイズ
 *
 * @retval	"TRUE=成功、FALSE=失敗"
 */
//--------------------------------------------------------------
BOOL Snd_PlayerHeapCreate( int player_no, u32 size )
{
	return NNS_SndPlayerCreateHeap( player_no, *( Snd_HeapHandleGet() ), size );
}


//==============================================================================================
//
//	ローカル関数
//
//==============================================================================================


//==============================================================================================
//
//	フィールドから切り替わる
//
//	１）戦闘に入る
//	２）部屋に入る
//	３）毒ゲームオーバー
//	４）自転車に乗った時
//	５）波乗りした時
//	他には何かあるか？？
//
//	段階的に変化する関数をすでに呼んでいる場合の対処を確認！(TCB以外でも)
//	→停止処理を呼ばないといけないなど。
//
//	メインがフィールドでなくなったら削除など
//
//==============================================================================================


//==============================================================================================
//
//	未使用・デバック関連
//
//==============================================================================================
#if 0
//--------------------------------------------------------------
/**
 * @brief	サウンドローカルワーク確保
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_LocalWorkCreate(void);
static void Snd_LocalWorkCreate(void)
{
	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(SND_LOCAL_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "サウンドローカルワーク確保失敗！" );
	}
	memset( wk, 0, sizeof(SND_LOCAL_WORK) );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	全てのサウンドヒープクリア(通常使用しない)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_HeapClear(void);
static void Snd_HeapClear(void)
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	NNS_SndHeapClear(wk->heap);
	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスを再生
 *
 * @param	p		サウンドハンドルのアドレス
 * @param	no		BGMナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 *
 * 再生に成功すると、サウンドハンドルにシーケンスが結びつけられます。 
 *
 * シーケンスデータをプレイヤーヒープでロードする時は、
 * 容量が足りないと再生失敗する！
 */
//--------------------------------------------------------------
static BOOL Snd_ArcPlayerStartSeq( NNSSndHandle *p, u16 no )
{
	return NNS_SndArcPlayerStartSeq( p, no );
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスアーカイブを再生
 *
 * @param	p		サウンドハンドルのアドレス
 * @param	arc_no	シーケンスアーカイブナンバー(シーケンスアーカイブの並び順)
 * @param	index	インデックス
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 *
 * 再生に成功すると、サウンドハンドルにシーケンスが結びつけられます。 
 *
 * 再生失敗の原因は、
 * シーケンスアーカイブ番号が無効
 * インデックス番号が無効 
 * 既に再生中のシーケンスよりも優先度が低い 
 * データがメモリ上に無い 
 * ヒープ領域が足りない(グループロードが失敗している)
 */
//--------------------------------------------------------------
BOOL Snd_ArcPlayerStartSeqArc( NNSSndHandle *p, int arc_no, int index )
{
	return NNS_SndArcPlayerStartSeqArc( p, arc_no, index );
}

//--------------------------------------------------------------
/**
 * @brief	指定プレイヤーのシーケンス最大同時再生数を設定(多重再生をしたい時に使用！)
 *
 * @param	player_no	プレイヤー番号
 * @param	no			シーケンス最大同時再生数
 *
 * @retval	"変更前のシーケンス最大同時再生数"
 *
 * PLAYER_FIELD	: フィールドBGM
 * PLAYER_ME 	: ME
 * PLAYER_SE_1 	: 効果音
 * PLAYER_SE_2 	: 効果音
 * PLAYER_SE_3 	: 効果音
 * PLAYER_SE_4 	: 効果音
 * PLAYER_PV	: ポケモン鳴き声
 * PLAYER_VOICE	: 音声
 * PLAYER_BGM	: フィールド以外BGM
 *
 * 使用後は、必ず元の設定に戻すようにして下さい！
 */
//--------------------------------------------------------------
static u8 Snd_PlayerSetPlayableSeqCount( int player_no, int no );
static u8 Snd_PlayerSetPlayableSeqCount( int player_no, int no )
{
	const NNSSndArcPlayerInfo* info;
	u8 ret;

	//注意！ サウンドアーカイブからの取得
	info = NNS_SndArcGetPlayerInfo( player_no );		//プレイヤー情報構造体取得
	ret = info->seqMax;									//退避

	NNS_SndPlayerSetPlayableSeqCount( player_no, no );

	return ret;											//変更前のシーケンス最大同時再生数
}
#endif


//==============================================================================================
//
//	ストリーム関数
//
//==============================================================================================
#ifdef STREAM_ON
//--------------------------------------------------------------
/**
 * @brief	ストリーム再生
 *
 * @param	no		ストリームナンバー
 *
 * @retval	none
 *
 * パン、ボリュームのみ操作出来る
 * (音程操作、コーラス効果は出来ないことになる！)
 */
//--------------------------------------------------------------
BOOL Snd_ArcStrmStart( u16 no );
BOOL Snd_ArcStrmStart( u16 no )
{
	SND_WORK* wk = Snd_GetSystemAdrs();
	(void)NNS_SndArcStrmStart( &wk->strmHandle, no, 0 );
	return;
}
#endif


//==============================================================================================
//
//	fld_bgmで使用する関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	バンク切り替えるかセット
 *
 * @param	no		0=昼、1=夜
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BankFlagSet( int no )
{
	u8* bank_flag	= Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	*bank_flag		= no;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	バンク切り替えるかフラグ取得
 *
 * @param	none
 *
 * @retval	"昼、1=夜"
 */
//--------------------------------------------------------------
u8 Snd_BankFlagGet()
{
	u8* bank_flag = Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	return (*bank_flag);
}

//--------------------------------------------------------------
/**
 * @brief	フェードアウト → BGM再生
 *
 * @param	scene		シーン(場面)ナンバー
 * @param	no			シーケンスナンバー
 * @param	frame		フレーム数
 * @param	next_wait	次のBGMを鳴らすまでのウェイト
 * @param	flag		0=昼、1=夜、0xff=無効(何もしない)
 * @param	adrs		フェードデータのアドレス
 *
 * @retval	"0=何もしない、1=開始"
 *
 * フェードカウンターをセットしています
 */
//--------------------------------------------------------------
BOOL Snd_FadeOutNextPlaySet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs )
{
	u8* scene_sub	= Snd_GetParamAdrs(SND_W_ID_SCENE_SUB);

	//フェード共通処理
	Snd_FadeCommonSet( scene, no, frame, next_wait, flag, adrs );
	
	//サブシーンをクリア
	*scene_sub = SND_SCENE_DUMMY;

	//ステータスを再セット
	Snd_StatusSet( SND_STATUS_FADEOUT_NEXT_PLAY );	//ステータス(フェードアウト→再生)
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	フェードアウト → BGMフェードイン
 *
 * @param	scene		シーン(場面)ナンバー
 * @param	no			シーケンスナンバー
 * @param	frame		フレーム数
 * @param	next_wait	次のBGMを鳴らすまでのウェイト
 * @param	next_frame	次のBGMのフェードインフレーム数
 * @param	flag		バンクを切り替えるか(SND_BANK_CONTINUE、SND_BANK_CHANGE)
 * @param	adrs		フェードデータのアドレス
 *
 * @retval	"0=何もしない、1=開始"
 *
 * フェードカウンターをセットしています
 */
//--------------------------------------------------------------
BOOL Snd_FadeOutNextFadeInSet( u8 scene, u16 no, int frame, int next_wait, int next_frame, u8 flag, void* adrs )
{
	int* next_frame_wk = Snd_GetParamAdrs(SND_W_ID_NEXT_FRAME);

	//フェード共通処理
	Snd_FadeCommonSet( scene, no, frame, next_wait, flag, adrs );
	
	*next_frame_wk = next_frame;						//次のBGMのフェードインフラーム数セット

	//ステータスを再セット
	Snd_StatusSet( SND_STATUS_FADEOUT_NEXT_FADEIN );	//ステータス(フェードアウト→フェードイン)
	return 1;
}

//共通処理
static void Snd_FadeCommonSet( u8 scene, u16 no, int frame, int next_wait, u8 flag, void* adrs )
{
	const NNSSndArcBankInfo** info		= Snd_GetParamAdrs(SND_W_ID_BANK_INFO);

	//フェードアウト開始(ステータス＝フェードアウト)
	Snd_BgmFadeOut( BGM_VOL_MIN, frame );

	//フェードアウト中の"今のBGMナンバー"は、必ず0が入っているようにする！
	
	//再度ゾーン切り替え処理が呼ばれるように、今のBGMナンバーをクリアする！
	Snd_NowBgmNoSet( 0 );							//今のBGMナンバーセット

	//次の(ゾーン)BGMナンバーをセットしておく
	Snd_NextBgmNoSet( no );							//次のBGMナンバーセット
	Snd_NextWaitSet( next_wait );					//次のBGMを鳴らすまでのウェイトセット

	//06.01.25削除
	//Snd_SceneSet( scene );						//変更するシーンセット
	
	*info		= Snd_GetBankInfo( no );			//バンク情報構造体セット

	Snd_BankFlagSet( flag );						//バンク切り替えるかセット
	return;
}


//==============================================================================================
//
//	d_noharaで使用する関数(デバック用)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	波形再生用のチャンネルを解放する(デバック処理)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_DebugNormalChannelFree()
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);

	if( *ch_normal_flag == 1 ){	//確保フラグがONだったら
		Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );
	}

	return;
}


//==============================================================================================
//
//	snd_testで使用する関数(デバック用)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	バンクロード
 *
 * @param	no		バンクナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_DebugLoadBank( u16 no )
{
	Snd_ArcLoadBank( no );
	return;
}


//==============================================================================================
//
//	波形関連(ポケモン図鑑の鳴き声画面で使用)
//
//	<nitro/snd.h>
//	typedef struct SNDWaveData
//
//==============================================================================================
const u8* Snd_WaveDataSampleAdrsGet( const SNDWaveData* p_data );
const u32 Snd_WaveDataSampleSizeGet( const SNDWaveData* p_data );
const SNDWaveData* Snd_ZukanWaveDataSet( int wave_arc_no );
static const SNDWaveData* Snd_WaveDataAdrsGet( int wave_arc_no );
u32 Snd_PlayerGetSampleTick( int handle_no, const SNDWaveData* p_data );
u32 Snd_ZukanPlayerGetSampleTick( int handle_no, const SNDWaveData* p_data, int pitch );
u32 Snd_PlayerGetTick( int handle_no );

//--------------------------------------------------------------
/**
 * @brief	波形データのアドレスからサンプルデータのアドレスを取得
 *
 * @param	p_data		波形データのアドレス
 *
 * @retval	"サンプルデータのアドレス、NULL=失敗"
 */
//--------------------------------------------------------------
const u8* Snd_WaveDataSampleAdrsGet( const SNDWaveData* p_data )
{
	if( p_data == NULL ){
		return NULL;
	}

	return &p_data->samples[0];
}

//--------------------------------------------------------------
/**
 * @brief	波形データのアドレスからサンプルデータの配列の大きさを取得
 *
 * @param	p_data		波形データのアドレス
 *
 * @retval	"サンプルデータの配列の大きさ、0=失敗"
 */
//--------------------------------------------------------------
const u32 Snd_WaveDataSampleSizeGet( const SNDWaveData* p_data )
{
	if( p_data == NULL ){
		return 0;
	}

	return (p_data->param.looplen);
}

//--------------------------------------------------------------
/**
 * @brief	波形データのアドレスを取得(図鑑専用)
 *
 * @param	wave_arc_no	波形アーカイブ番号(ポケモンナンバー)
 *
 * @retval	"波形データ構造体のアドレス、NULL=失敗"
 *
 * 1)BGMの後ろを開放
 * 2)波形アーカイブロード
 * の処理をしているので注意！
 */
//--------------------------------------------------------------
const SNDWaveData* Snd_ZukanWaveDataSet( int wave_arc_no )
{
	u16 monsno;

	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SUB_SE) );	//サブ画面SEの後ろを消す

	monsno = wave_arc_no;

	//不正な値チェック
	if( monsno != MONSNO_PERAPPU ){					//デバックのためぺラップは例外にしておく
		if( (wave_arc_no > MONSNO_MAX) || (wave_arc_no == 0) ){
			//GF_ASSERT( (0) && "ポケモンナンバーが不正です！" );
			//return FALSE;	//エラー
			OS_Printf( "ポケモンナンバーが不正です！" );
			monsno = MONSNO_HUSIGIDANE;
		}
	}

	//波形アーカイブロード(ロードしないと、あとの処理で失敗する！)
	Snd_ArcLoadWaveArc( monsno );

	//波形データのアドレス取得
	return Snd_WaveDataAdrsGet( monsno );
}

//--------------------------------------------------------------
/**
 * @brief	波形データのアドレスを取得
 *
 * @param	wave_arc_no	波形アーカイブ番号(ポケモンナンバー)
 *
 * @retval	"波形データ構造体のアドレス、NULL=失敗"
 */
//--------------------------------------------------------------
static const SNDWaveData* Snd_WaveDataAdrsGet( int wave_arc_no )
{
	u16 monsno;
	const NNSSndArcWaveArcInfo* wave_arc_info;
	SNDWaveArc* wave_arc		= NULL;
	const SNDWaveData** p_data	= Snd_GetParamAdrs(SND_W_ID_WAVE_DATA);

	monsno = wave_arc_no;

	//不正な値チェック
	if( monsno != MONSNO_PERAPPU ){					//デバックのためぺラップは例外にしておく
		if( (wave_arc_no > MONSNO_MAX) || (wave_arc_no == 0) ){
			//GF_ASSERT( (0) && "ポケモンナンバーが不正です！" );
			//return FALSE;	//エラー
			OS_Printf( "ポケモンナンバーが不正です！" );
			monsno = MONSNO_HUSIGIDANE;
		}
	}

	//波形アーカイブ情報構造体取得
    wave_arc_info = NNS_SndArcGetWaveArcInfo( monsno );
    if( wave_arc_info == NULL ){
		GF_ASSERT( (0) && "波形アーカイブナンバーが不正です！" );
		return NULL;
	}

	//ファイルIDから、波形アーカイブ情報構造体取得
	wave_arc = (SNDWaveArc*)NNS_SndArcGetFileAddress( wave_arc_info->fileId );
    if( wave_arc == NULL ){
		OS_Printf( "サウンドヒープが足りなくて、鳴き声ロードに失敗しました！\n" );
		OS_Printf( "ポケモンナンバー = %d\n", wave_arc_no );
		GF_ASSERT( (0) && "波形アーカイブナンバーが不正です！" );
		return NULL;
	}

	//SNDWaveData型の波形データのアドレスを取得
	*p_data = SND_GetWaveDataAddress( wave_arc, 0 );

	OS_Printf( "＜波形データ＞\n" );
	OS_Printf( "wave_data formt    = %d\n", (*p_data)->param.format );
	OS_Printf( "wave_data loopflag = %d\n", (*p_data)->param.loopflag );
	OS_Printf( "wave_data rate     = %d\n", (*p_data)->param.rate );
	OS_Printf( "wave_data timer    = %d\n", (*p_data)->param.timer );
	OS_Printf( "wave_data loopstart= %d\n", (*p_data)->param.loopstart );
	OS_Printf( "wave_data looplen  = %d\n", (*p_data)->param.looplen );

	return (*p_data);
}

//--------------------------------------------------------------
/**
 * @brief	波形データの再生しているサンプルデータ要素数を返す
 *
 * @param	handle_no	ハンドルナンバー
 * @param	p_data		波形データのアドレス
 *
 * @retval	"要素数"
 */
//--------------------------------------------------------------
u32 Snd_PlayerGetSampleTick( int handle_no, const SNDWaveData* p_data )
{
	u32 num;
	u32 tick = Snd_PlayerGetTick( handle_no );
	u32 max  = p_data->param.looplen;

	//num = (max / 32);		//再生終了した時のtickの値
	num = (tick * 32);		//再生している要素数
	if( num >= max ){
		num = 0;
	}

	return num;
}

//--------------------------------------------------------------
/**
 * @brief	波形データの再生しているサンプルデータ要素数を返す(図鑑用)
 *
 * @param	handle_no	ハンドルナンバー
 * @param	p_data		波形データのアドレス
 * @param	pitch		設定しているピッチ
 *
 * @retval	"要素数"
 */
//--------------------------------------------------------------
u32 Snd_ZukanPlayerGetSampleTick( int handle_no, const SNDWaveData* p_data, int pitch )
{
	int no;
	u32 num;
	u32 tick = Snd_PlayerGetTick( SND_HANDLE_PMVOICE );
	u32 max  = p_data->param.looplen;

#if 1
	//細かい計算はしていない、オクターブのみ対応
	
	no = pitch / (64*12);
	no = no * 2;

	if( no < 0 ){
		no = 32 / no * -1;	//正の値にする
	}else if( no == 0 ){
		no = 32;
	}else{
		no = 32 * no;
	}

	//OS_Printf( "no = %d\n", no );
#else
	no = 32;
#endif

	//num = (max / no);		//再生終了した時のtickの値
	num = (tick * no);		//再生している要素数
	if( num >= max ){
		num = 0;
	}

	//OS_Printf( "pitch = %d\n", pitch );
	//OS_Printf( "no = %d\n", no );
	//OS_Printf( "tick = %d\n", tick );
	//OS_Printf( "num = %d\n", num );

	return num;
}

//--------------------------------------------------------------
/**
 * @brief	ティック数取得
 *
 * @param	p_data		波形データのアドレス
 *
 * @retval	"ティック数"
 */
//--------------------------------------------------------------
u32 Snd_PlayerGetTick( int handle_no )
{
	u32 tick = NNS_SndPlayerGetTick( Snd_HandleGet(handle_no) );
	//OS_Printf( "tick = %d\n", tick );
	return tick;
}


















#define WAVE_8_BIT_CENTER		(128)			//8bit 切り替え(u8)
#define WAVE_16_BIT_CENTER		(0)				//16bit 切り替え(s16)

//ボーグラフ用の定義
enum{
	//だいたい"3"tickごとに呼ばれるので、32*3=96で100にしておく
	//WAVE_LEVEL_BEFORE_POS	=	(50),			//比較する差分の幅
	WAVE_LEVEL_BEFORE_POS	=	(100),			//比較する差分の幅
	//WAVE_LEVEL_BEFORE_POS	=	(150),			//比較する差分の幅
	//WAVE_LEVEL_BEFORE_POS	=	(200),			//比較する差分の幅

	//代入する要素数を決める間隔
	//間隔狭くするほど要素数[0]の数が少なくなる
	//
	//06.03.30テスト
	WAVE_LEVEL_HABA				=	(1),		//レベルを分ける間隔("0","1",...と分かれる)
	//
	//06.03.29以前
	//WAVE_LEVEL_HABA			=	(2),		//レベルを分ける間隔("0,1","2,3",...と分かれる)
	//
	//WAVE_LEVEL_HABA			=	(3),		//レベルを分ける間隔("0,1,2","3,4,5",...と分かれる)
	//WAVE_LEVEL_HABA		=	(4),				//レベルを分ける間隔(("0,1,2,3",...と分かれる)
	//WAVE_LEVEL_HABA		=	(8),				//レベルを分ける間隔(("0,1,2,3",...と分かれる)
};

//06.04.11
//代入する要素数を決める間隔をテーブルでもつようにして調整する！
#define WAVE_LEVEL_HABA_MAX	(9)
//static const u8 wave_level_haba[WAVE_LEVEL_HABA_MAX] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };	//前と同じ
//static const u8 wave_level_haba[WAVE_LEVEL_HABA_MAX] = { 1, 2, 4, 6, 7, 8, 9, 10, 11 };
static const u8 wave_level_haba[WAVE_LEVEL_HABA_MAX] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };


u32 Snd_ZukanPlayerGetTick();
void Snd_DebugWaveDataPut( const SNDWaveData* p_data, u32 start, u32 end );


//const SNDWaveData* snd_wave_data;				//波形データのポインタ

//再生終了したら、
//最後に取得したレベルから、
//少しずづレベルを落としていく
//--------------------------------------------------------------
/**
 * @brief	"デバック"　波形データ表示
 *
 * @param	start		表示するデータの開始位置
 * @param	end			表示するデータの終了位置
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_DebugWaveDataPut( const SNDWaveData* p_data, u32 start, u32 end )
{
	u32 i,data_size;
	u8 pos;
	//const SNDWaveData** p_data = Snd_GetParamAdrs(SND_W_ID_WAVE_DATA);

	//OS_Printf( "wave_data formt    = %d\n", (p_data)->param.format );
	//OS_Printf( "wave_data loopflag = %d\n", (p_data)->param.loopflag );
	//OS_Printf( "wave_data rate     = %d\n", (p_data)->param.rate );
	//OS_Printf( "wave_data timer    = %d\n", (p_data)->param.timer );
	//OS_Printf( "wave_data loopstart= %d\n", (p_data)->param.loopstart );
	//OS_Printf( "wave_data looplen  = %d\n", (p_data)->param.looplen );

	data_size = ( (p_data)->param.looplen );

	for( i=start;  i < end ;i++ ){

		//エラー回避
		if( i >= data_size ){
			return;
		}

		//--------------------------------
		//			データ	→	表示位置
		//			127			0
		//
		//			0			128
		//CENTER----0-----------128-------
		//			255			129
		//
		//			128			255
		//--------------------------------
		if( (p_data)->samples[i] == 255 ){								//255だったら
			pos = 129;													//表示129

		}else if( (p_data)->samples[i] < WAVE_8_BIT_CENTER ){				//0-127だったら
			pos = (128 - (p_data)->samples[i]);							//表示0-128

		}else{
			pos = (255 - ((p_data)->samples[i] - WAVE_8_BIT_CENTER));		//表示129-255
		}

		//OS_Printf( "(p_data)->samples[%d] = %d\n", i, pos );
		OS_Printf( "buf[%d] = %d;\n", i, pos );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	波形レベルセット(図鑑用)
 *
 * @param	p_data		波形データのアドレス
 * @param	buf			格納するバッファのポインタ
 * @param	max			格納するバッファの最大数
 * @param	pitch		設定しているピッチ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_ZukanWaveLevelSet_New( const SNDWaveData* p_data, u8* buf, int max, int pitch );
void Snd_ZukanWaveLevelSet_New( const SNDWaveData* p_data, u8* buf, int max, int pitch )
{
	int flag;
	int start;									//データをチェックする開始位置
	s8	status;									//現在の状態(+1=上、-1=下)
	int i,j,pos,count;							//計算用
	u32 tick = Snd_ZukanPlayerGetSampleTick( SND_HANDLE_PMVOICE, p_data, pitch );

	//[100]だったら、[50]～[100]をチェックする
	start = tick - WAVE_LEVEL_BEFORE_POS;
	if( start < 0 ){
		start = 0;								//補正
	}

	//初期化
	count = 0;
	pos	= 0;

	//現在の状態セット(128以下は上、それ以外は下)
	status = ((p_data)->samples[start] < 128 ) ? 1 : -1;

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n===========================\n" );
	OS_Printf( "チェック開始位置 start = %d\n", start );
	OS_Printf( "状態 1=上 -1=下 status = %d\n", status );
	OS_Printf( "チェック現在位置 tick = %d\n", tick );
#endif

	//開始位置から現在位置までチェックする
	//for( i=start; i < tick ;i++ ){
	//for( i=start; i < tick ;i+=max ){	//テスト！1ずづチェックではなく、間引いてチェックする
	//for( i=start; i < tick ;i+=(max/2) ){	//テスト！1ずづチェックではなく、間引いてチェックする
	for( i=start; i < tick ;i+=2 ){	//テスト！1ずづチェックではなく、間引いてチェックする
	
		flag = 0;

		if( status > 0 ){									//上にいて
			if( (p_data)->samples[i] > 128 ){				//下か？
				flag = 1;
			}else{
				count++;									//上のままなのでカウンタインクリメント
			}

		//}else if( status < 0 ){							//下にいて
		}else{												//下にいて
			if( (p_data)->samples[i] < 128 ){				//上か？
				flag = 1;
			}else{
				count++;									//下のままなのでカウンタインクリメント
			}
		}

		//センターをこえたので、レベルインクリメント
		if( flag == 1 ){
#if 0
			pos = (count / WAVE_LEVEL_HABA);
			//pos = (pos >= max) ? (max-1) : pos;		//補正(適当かも？)
#else
			for( j=0; j < WAVE_LEVEL_HABA_MAX ;j++ ){ 
				if( count < wave_level_haba[j] ){
					pos = j;
					break;
				}
			}

#endif

			//カットして(捨てて)しまってもいいかも？
			if( pos >= max ){
				pos = ( max - 1 );						//補正(適当かも？)
			}
			//------------------------------

			//バランスをとるために間隔狭すぎる成分は無視する
			if( count != 0 ){
				//要素数の手前が低
				//要素数の後ろが高
				buf[max - 1 - pos]++;						//レベルインクリメント
			}else{
#ifdef SOUND_OS_PRINT_ON
				OS_Printf( "▲count = 0 を無視しました！\n" );
#endif
			}

			count= 0;
			flag = 0;
			status = ((p_data)->samples[i] < 128 ) ? 1 : -1;
		}
	}

#ifdef SOUND_OS_PRINT_ON
	//デバック表示
	for( i=0; i < max ;i++ ){
		OS_Printf( "★補正前buf[%d] = %d\n", i, buf[i] );
	}
	OS_Printf( "\n------------\n" );
#endif

#if 0
	//補正テスト中
	
	//縦10段階に補正する
	for( i=0; i < max ;i++ ){
		if( buf[i] >= 100 ){
			buf[i] = 9;
		}else if( buf[i] >= 10){
			buf[i] /= 10;
		}
	}
#else

	//縦10段階に補正する
	for( i=0; i < max ;i++ ){
		if( buf[i] >= 10 ){
			buf[i] = 9;
		}
	}
#endif



#if 1

	//一番左からデータが入らなかった要素数を探して、
	//その隣のデータの半分のレベルを補正して代入

	for( i=0; i < (max-1) ;i++ ){
		if( (buf[i] == 0) && (buf[i+1] != 0) ){
			buf[i] = (buf[i+1] / 2);
			break;
		}
	}

#endif



#if 0
	//0が存在したら、となりのレベルを見て、補正する？
	//均一になりすぎてしまう？
	
	//間引きの間隔を広くしすぎると、そのデータがどうなるかが、運が強くなるのでだめ！
	//連続した形をある程度さけるために、+1,+2ぐらいの間引きはいいかも？
	
	//上が10段階なので、連続した形は避けないといけない。
#endif

#ifdef SOUND_OS_PRINT_ON
	//デバック表示
	for( i=0; i < max ;i++ ){
		OS_Printf( "■補正後buf[%d] = %d\n", i, buf[i] );
	}
	OS_Printf( "\n------------\n" );
#endif

	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	エフェクトのコールバック関数(図鑑鳴き声用)
 *
 * @param	bufferL_p	Lミキサー成分
 * @param	bufferR_p	Rミキサー成分
 * @param	len			バッファのサイズ
 * @param	format		NNS_SndCaptureStartEffect関数の引数(CAPTURE_FORMAT)と同じものが渡される
 * @param	arg			NNS_SndCaptureStartEffect関数の引数(callbackInfo)と同じものが渡される
 *
 * @retval	none
 *
 * 簡単なローパスフィルタ（移動平均）をかけて出力している
 *
 * 一定期間の間隔を定め、その間隔内の平均値を連続して計算することによって
 * 趨勢(すうせい)的な動向を知ろうとするもの。
 * (ある方向へと動く勢い )
 */
//--------------------------------------------------------------
static void EffectCallback2( void* bufferL_p, void* bufferR_p, u32 len, NNSSndCaptureFormat format, void* arg )
{
    smp_t org[ FILTER_SIZE ][2];
    smp_t* lp = (smp_t*)bufferL_p;
    smp_t* rp = (smp_t*)bufferR_p;
    EffectCallbackInfo* info = (EffectCallbackInfo*)arg;
	u8* filter_size = Snd_GetParamAdrs(SND_W_ID_FILTER_SIZE);

    int samples;
    int x;
    int i, j;
    
	//サンプルが8ビットPCMはそのまま
	//サンプルが16ビットPCMだったらバッファのサイズを半分にする
    samples = ( format == NNS_SND_CAPTURE_FORMAT_PCM8 ) ? len : ( len >> 1 );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n\n＜サウンド　キャプチャ　エフェクト＞\n" );
	OS_Printf( "format = %d\n", format );			//0
	OS_Printf( "len = %d\n", len );					//1024
	OS_Printf( "samples = %d\n", samples );			//
	OS_Printf( "\n" );
#endif
    
	if( (*filter_size) == 0 ){
		return;		//何もしない
	}

	//--------------------------------------------
	//例
	//	LRミキサー成分のサイズ(samples)	= 256 
	//	フィルターサイズ				= 8
	//
	//	lp[ 256 - 8 + i ]				= 248 + i
	//
	//	248,249,250,251,252,253,254,255を保存
	//--------------------------------------------
    //LRミキサー成分のけつから、フィルターサイズ分を保存
    for( i = 0; i < (*filter_size) ; i++ ) {
        org[i][0] = lp[ samples - (*filter_size) + i ];
        org[i][1] = rp[ samples - (*filter_size) + i ];
		OS_Printf( "org[%d][左] = %d\n", i, org[i][0] );
		OS_Printf( "org[%d][右] = %d\n", i, org[i][1] );
    }
    
	//--------------------------------------------
	//例 
	//	LRミキサー成分のサイズ		= 256
	//	フィルターサイズ			= 8
	//
    //	for( i = 256 - 1; i >= 8 - 1 ; i-- ){
	//	255...7まで処理する
	//--------------------------------------------
	//LRミキサー成分のけつから、フィルターサイズの値より小さくなるまで処理する
    for( i = samples - 1; i >= (*filter_size) - 1 ; i-- ){

		//--------------------------------------------
		//例 
		//	LRミキサー成分のサイズ		= 256
		//	フィルターサイズ			= 8
		//
		//	j = 0 ～ 7
		//	x += lp[ 255 - j ];
		//	lp[255],[254],...[248]までの値を足して、
		//	フィルターサイズで割り、平均の値を求める
		//--------------------------------------------
		//Lミキサー成分
        x = 0;
        for( j = 0 ; j < (*filter_size) ; j++ ) {	//フィルターサイズ分足していく
            x += lp[ i - j ];
        }
        lp[ i ] = (smp_t)(x /= (*filter_size));		//フィルターサイズで割り平均の値を求めて上書き
        
		//Rミキサー成分
        x = 0;
        for( j = 0 ; j < (*filter_size) ; j++ ) {	//フィルターサイズ分足していく
            x += rp[ i - j ];
        }
        rp[ i ] = (smp_t)(x /= (*filter_size));		//フィルターサイズで割り平均の値を求めて上書き
    }
    


#if 0
#if FILTER_SIZE >= 2    
	//--------------------------------------------
	//例 バッファサイズ = 24 フィルターサイズ = 8
    //for( i = 8 - 2; i >= 0 ; i-- ){
	//6...0まで処理する
	//--------------------------------------------
    for( i = (*filter_size) - 2 ; i >= 0 ; i-- ){

		//Lミキサー成分
        x = lp[ i ];
        for( j = 1 ; j < (*filter_size) ; j++ ) {	//フィルターサイズ分
            x += GetSample( lp, i-j, 0, info );
        }
        lp[ i ] = (smp_t)(x /= (*filter_size));	//フィルターサイズで割り平均で上書きする
        
		//Rミキサー成分
        x = rp[ i ];
        for( j = 1 ; j < (*filter_size) ; j++ ) {
            x += GetSample( rp, i-j, 1, info );
        }
        rp[ i ] = (smp_t)(x /= (*filter_size));	//フィルターサイズで割り平均で上書きする
    }
#endif
#endif
    



	//キャプチャが完成した領域のフィルタサイズ分を
	//保存しておいたデータで上書きする
	//(バッファの一番後ろから、フィルターサイズ分を保存しておいたデータ)
    for( i = 0; i < (*filter_size) ; i++ ) {
    	info->sample[i][0] = org[i][0];
		info->sample[i][1] = org[i][1];
    }

	//メインメモリに確実に書き込む
    DC_FlushRange( bufferL_p, samples );
    DC_FlushRange( bufferR_p, samples );

	//引数に渡されるバッファは、(この関数内ではinfo)
	//キャプチャが完了した領域を指しています。
	//この領域を修正することで、実際に出力される音を変更することができます。 
}

//--------------------------------------------------------------
/**
 * @brief	シーケンスローカルワークを変更する
 *
 * @param	num		シーケンスローカルワーク"0"にセットする値
 *
 * @retval	"成功=TRUE、失敗=FALSE"
 *
 * 色々出来そうだが、今回は使用を限定しておく！
 */
//--------------------------------------------------------------
BOOL Snd_PlayerWriteVariable( s16 num )
{
	return NNS_SndPlayerWriteVariable( Snd_HandleGet(SND_HANDLE_BGM), 0, num );
}

//--------------------------------------------------------------
/**
 * @brief	PLAYER_BGMの使用チャンネルを変更する
 *
 * @param	ch		使用チャンネルのビット指定
 *
 * @retval	none
 *
 * オープニング、エンディングのみで使用する！
 *
 * 14,15chを抜かして使用可能にする！
 */
//--------------------------------------------------------------
static void Snd_PlayerBgmChannelSet( u16 ch_bit )
{
	NNS_SndPlayerSetAllocatableChannel( PLAYER_BGM, ch_bit );
	return;
}

#if 0 
//--------------------------------------------------------------
/**
 * @brief	シーケンストラックの確保可能なチャンネルを変更
 *
 * @param	ch_bit			確保可能なチャンネルのビットフラグ
 *
 * @retval	none
 *
 * オープニング、エンディングのみで使用する！
 *
 * 14,15chを抜かして使用可能にする！
 */
//--------------------------------------------------------------
static void Snd_PlayerBgmChannelSet( u16 ch_bit )
{
	NNS_SndPlayerSetTrackAllocatableChannel( Snd_HandleGet(SND_HANDLE_BGM), ch_bit );
	return;
}
#endif

//--------------------------------------------------------------
/**
 * @brief	使用可能チャンネル操作、リバーブ設定
 *
 * @param	flag	2=セット(ED)、1=セット(OP)、0=クリア
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BgmChannelSetAndReverbSet( int flag )
{
#ifdef SND_CH_SET
	if( flag == 0 ){
		Snd_PlayerBgmChannelSet( PLAYER_BGM_NORMAL_CH );	//PLAYER_GMの使用チャンネルを元に戻す
		Snd_CaptureStopReverb( 0 );							//リバーブ停止
		//OS_Printf( "\n**********\nOP,ED リバーブ停止！\n*********\n" );
	}else if( flag == 1 ){
		Snd_PlayerBgmChannelSet( PLAYER_BGM_EXTRA_CH );	//OP、EDのみBGMの使用チャンネルを増やす
		if( Snd_CaptureStartReverb( SND_REVERB_NUM_OP ) == FALSE ){	//リバーブ開始
			OS_Printf( "\n**********\nOP,ED リバーブ失敗！\n*********\n" );
		}else{
			//OS_Printf( "\n**********\nOP,ED リバーブ開始！\n*********\n" );
		}
	}else{
		Snd_PlayerBgmChannelSet( PLAYER_BGM_EXTRA_CH );	//OP、EDのみBGMの使用チャンネルを増やす
		if( Snd_CaptureStartReverb( SND_REVERB_NUM_ED ) == FALSE ){	//リバーブ開始
			OS_Printf( "\n**********\nOP,ED リバーブ失敗！\n*********\n" );
		}else{
			//OS_Printf( "\n**********\nOP,ED リバーブ開始！\n*********\n" );
		}
	}

	Snd_CaptureIsActive();
#endif
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドBGMをポーズするか、停止するかを判別して処理
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_FieldPauseOrStop( void )
{
	//フェード中ではなく、
	//PLAYER_FIELDにシーケンスが設定されていて、
	//現在のBGMが「ゆれ草」でなかったら
	if( (Snd_FadeCheck() == 0) && 
		(Snd_GetSeqNo(Snd_HandleGet(SND_HANDLE_FIELD)) != -1) &&
		(Snd_NowBgmNoGet() != SEQ_KUSAGASA) ){

		Snd_StopEx();											//フィールドBGMを抜かして全停止
		Snd_PlayerPause( PLAYER_FIELD, TRUE );					//フィールドBGMポーズ

	}else{
		Snd_Stop();												//全停止
	}

	return;
}


//--------------------------------------------------------------
/**
 * @brief	プレイヤーの音量操作(デフォルトは127が設定されている)
 *
 * @param	player_no	プレイヤーナンバー
 * @param	volume		ボリューム
 *
 * @retval	none
 *
 * 使用後は、必ず127に戻してください！
 */
//--------------------------------------------------------------
void Snd_PlayerSetPlayerVolume( int player_no, int volume )
{
	NNS_SndPlayerSetPlayerVolume( player_no, volume );
	return;
}


