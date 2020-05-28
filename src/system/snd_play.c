//==============================================================================================
/**
 * @file	snd_play.c
 * @brief	サウンド再生関数
 * @author	Satoshi Nohara
 * @date	2005.06.09
 *
 *	＜メモ＞
 * ポケモンナンバーと、鳴き声シーケンスデータの並びが同じか確認する！
 * (全国図鑑ナンバーに対応しているらしい。050722一之瀬さんより)
 *
 *	波形再生(逆再生)を使用している技の最後に、FreeChannelを入れる！
 */
//==============================================================================================
#include "common.h"
#include "snd_system.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "poketool/monsno.h"


#ifdef PM_DEBUG
//BGMをOFFにする処理
u8 debug_bgm_flag;
void Snd_DebugBgmFlagSet( u8 sw );
static BOOL Snd_DebugBgmFlagCheck();
#endif

//==============================================================================================
//
//	定義
//
//==============================================================================================
#define	SND_ME_COMMON_WAIT		(15)			//ME共通ウェイト値

//鳴き声パターンのパラメータ定義
#define VOICE_SMALL_VOL			(90)			//音量小さめ
#define DEFAULT_RELEASE			(0)				//キーオフ後のリリース

//#define W_HYPER_VOICE_PITCH	(32768+16384)	//技「ハイパーボイス」のピッチ
//#define W_HYPER_VOICE_PITCH	(32768+8192)	//技「ハイパーボイス」のピッチ
//#define W_HYPER_VOICE_PITCH	(32768+4096)	//技「ハイパーボイス」のピッチ
//#define W_HYPER_VOICE_PITCH	(32768+3072)	//技「ハイパーボイス」のピッチ
//#define W_HYPER_VOICE_PITCH	(32768+2048)	//技「ハイパーボイス」のピッチ
#define W_HYPER_VOICE_PITCH		(32768+1536)	//技「ハイパーボイス」のピッチ

//#define W_NAKIGOE_PITCH		(32768+16384)	//技「鳴き声」のピッチ
//#define W_NAKIGOE_PITCH		(32768-8192)	//技「鳴き声」のピッチ
#define W_NAKIGOE_PITCH			(32768-6144)	//技「鳴き声」のピッチ


//==============================================================================================
//
//	構造体宣言
//
//==============================================================================================
//ポケモン鳴き声再生時間ワーク
typedef struct{
	int length;
	TCB_PTR	tcb;
}SND_PMVOICE_LENGTH_WORK;


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
BOOL Snd_BgmPlayBasicData( u16 no );
BOOL Snd_BgmPlay( u16 no );
static void Snd_BgmPlayCommon_01( u16 seq_no, int handle_no );
static BOOL Snd_BgmPlay_PlayerBgm( u16 no, u8 player_no, int type );
static BOOL Snd_BgmPlay_PlayerField( u16 no, u8 player_no, int type );
BOOL Snd_PlayerFieldDemoBgmPlay( u8 scene, u16 no );
void Snd_BgmStop( u16 no, int frame );
static void Snd_BgmStopSub(void);
void Snd_BgmFadeIn( int vol, int frame, int flag );
void Snd_BgmFadeOut( int vol, int frame );
int Snd_FadeCheck();
int Snd_BgmPlayCheck( u16 no );
void Snd_Stop(void);
void Snd_StopEx(void);

BOOL Snd_SePlay( u16 no );
BOOL Snd_SePlayPan( u16 no, int pan );
void Snd_SeStopBySeqNo( u16 no, int frame );
void Snd_SeStop( int type, int frame );
int Snd_SePlayCheck( u16 no );
int Snd_SePlayCheckAll(void);
void Snd_SePanSet( u16 no, u16 bitmask, int pan );
void Snd_SePanSetAll( int pan );

static void Snd_PMVoiceVolSet( u16 seq_no, int handle_no, int vol );
BOOL Snd_PMVoicePlay( u16 no );
void Snd_PMVoiceStop( int frame );
int Snd_PMVoicePlayCheck(void);
BOOL Snd_PMVoicePlayEx( int ptn, u16 no, int pan, int vol, int heap_id );
static u8 Snd_PMVoiceLengthChk();
void Snd_PMVoiceLengthSet(int length, int heap_id );
static void Snd_PMVoiceLengthMainTCB( TCB_PTR tcb, void* wk );
void Snd_PMVoiceLengthTcbDel();
static BOOL Snd_ChorusPlay( u16 no, s8 chorus );
static BOOL Snd_ChorusPlayReverse( u16 no, s8 chorus, int vol, int pan, int heap_id );

BOOL Snd_MePlay( u16 no );
int Snd_MePlayCheck(void);
static void Snd_MeStop( int frame );
int Snd_MePlayCheckBgmPlay(void);
static void Snd_MeWaitSet( u16 no );


//==============================================================================================
//
//	BGM関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BANK_BASICで作成したBGM再生(全てロード済みデータを再生)
 *
 * @param	no		BGMナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 *
 * データのロード処理が入りません。通常は使用しません。
 */
//--------------------------------------------------------------
BOOL Snd_BgmPlayBasicData( u16 no )
{
	int ret;
	u8 player_no= Snd_GetPlayerNo(no);					//seqナンバーから、プレイヤーナンバーを取得
	int type	= Snd_GetHandleNoByPlayerNo(player_no);	//playerナンバーから、ハンドルナンバーを取得

	//BANK_BASICで作成しておいて、SEQのみをロードする形だと、
	//サブシーンが呼ばれることがあると、SEQは消されてしまう！
	//進化画面は技忘れ画面を呼び出し戻ってくるので、
	//ポケモンリストのサブシーンが呼ばれるのでダメ！

	//ハンドルのアドレスを取得して、再生
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );

	//再生失敗チェック
	if( ret == 0 ){
		OS_Printf( "BGM 再生失敗\tno = %d\n", no );
	}

	Snd_BgmPlayCommon_01( no, type );
	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	BGM再生(SEの上に積んだデータを開放して、BGMデータのロードを行う)
 *
 * @param	no		BGMナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_BgmPlay( u16 no )
{
	int ret;
	u8 player_no = Snd_GetPlayerNo(no);				//seqナンバーから、プレイヤーナンバーを取得
	int type = Snd_GetHandleNoByPlayerNo(player_no);//playerナンバーから、ハンドルナンバーを取得

	if( player_no == PLAYER_BGM ){										//"サウンドヒープ"
		ret = Snd_BgmPlay_PlayerBgm( no, player_no, type );
	}else if( player_no == PLAYER_FIELD ){								//"プレイヤーヒープ"
		ret = Snd_BgmPlay_PlayerField( no, player_no, type );
	}else{
		GF_ASSERT( (0) && "再生しようとしているBGMナンバーが不正です！" );
		return FALSE;
	}

	//バンク切り替えるかフラグをリセット
	Snd_BankFlagSet( SND_BANK_CONTINUE );		//クリア = 継続

	//再生失敗チェック
	if( ret == 0 ){
		OS_Printf( "BGM 再生失敗\tno = %d\n", no );
	}

	Snd_BgmPlayCommon_01( no, type );
	return ret;
}

//共通処理
static void Snd_BgmPlayCommon_01( u16 seq_no, int handle_no )
{
	Snd_NowBgmNoSet( seq_no );											//今のBGMナンバー更新
	Snd_VChatVolSet( seq_no, handle_no );								//ボイスチャット音量操作
	Snd_StatusSet( SND_STATUS_PLAY );									//ステータス(再生)
	return;
}

//PLAYER_BGMの再生処理
static BOOL Snd_BgmPlay_PlayerBgm( u16 no, u8 player_no, int type )
{
	int ret;

	//シーケンス、バンク、波形アーカイブロード
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SE) );		//BGMを開放
	Snd_ArcLoadSeq( no );
	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_BGM) );	//階層保存(BGMの後を消す)

#ifdef PM_DEBUG
	if( Snd_DebugBgmFlagCheck() == 1 ){
		return 0;
	}
#endif

	//ハンドルのアドレスを取得して、再生
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );
	return ret;
}

//PLAYER_FIELDの再生処理
static BOOL Snd_BgmPlay_PlayerField( u16 no, u8 player_no, int type )
{
	int field_seq_no;
	u8* bank_flag	= Snd_GetParamAdrs(SND_W_ID_BANK_FLAG);
	u16* zone_bgm	= Snd_GetParamAdrs(SND_W_ID_ZONE_BGM);

	//PLAYER_FIELDのBGMナンバー取得
	field_seq_no = Snd_GetSeqNo( Snd_HandleGet(SND_HANDLE_FIELD) );

	//(ハンドルが無効の時は"-1"が返る)
	//OS_Printf( "player_field_seq_no = %d\n", Snd_GetSeqNo(Snd_HandleGet(SND_HANDLE_FIELD)) );
		
	//再生しようとしているBGMナンバー、PLAYER_FIELDにすでに設定されているバンクナンバー
	Snd_FieldDataSetSub( no, Snd_GetBankNo(field_seq_no) );

#ifdef PM_DEBUG
	if( Snd_DebugBgmFlagCheck() == 1 ){
		return 0;
	}
#endif

	//ハンドルのアドレスを取得して、再生
#if 0
	return NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );
#else
	//BANK_BASICではなく、ゾーン曲のバンクを読み込むようにする！
	return NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(type), -1, Snd_GetBankNo(*zone_bgm), -1, no );
#endif
}

//--------------------------------------------------------------
/**
 * @brief	演出BGM再生(ライバル、サポート、つれてけ)
 *
 * @param	scene	シーン(場面)ナンバー
 * @param	no		BGMナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 *
 * 連れ歩きBGMなどで使用する！
 *
 * サブ画面を呼び出すとシーケンスデータが消えてしまうので注意！
 */
//--------------------------------------------------------------
BOOL Snd_PlayerFieldDemoBgmPlay( u8 scene, u16 no )
{
	int ret;

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "\n＜Snd_PlayerFieldPauseBgmPlay＞\n" );
#endif

	//SEQ_TSURETEKEは、PLAYER_BGMなので、
	//Snd_BgmPlayで処理すると、
	//BGM領域の開放が入るのでダメ！

	//フィールドシーンのみ対応
	if( scene != SND_SCENE_FIELD ){
		GF_ASSERT( (0) && "Snd_BgmPlayExは、SND_SCENE_FIELDのみ対応です！" );
		return FALSE;
	}

	//PLAYER_BGMのみ対応
	if( Snd_GetPlayerNo(no) != PLAYER_BGM ){
		GF_ASSERT( (0) && "Snd_BgmPlayExは、PLAYER_BGMのみ対応です！" );
		return FALSE;
	}

#ifdef PM_DEBUG
	if( Snd_DebugBgmFlagCheck() == 1 ){
		ret = 0;
	}else{

	//シーケンスのみロード(上に積むだけでヒープセーブはしない)
	ret = Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_SEQ );

	//SND_HANDLE_BGMのアドレスを取得して再生
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_BGM), no );

	}
#else
	//シーケンスのみロード(上に積むだけでヒープセーブはしない)
	ret = Snd_ArcLoadSeqEx( no, NNS_SND_ARC_LOAD_SEQ );

	//SND_HANDLE_BGMのアドレスを取得して再生
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_BGM), no );
#endif	//PM_DEBUG

	//再生失敗チェック
	if( ret == 0 ){
		OS_Printf( "Snd_PlayerFieldPauseBgmPlay 再生失敗\tno = %d\n", no );
	}

	Snd_NowBgmNoSet( no );													//今のBGMナンバー更新
	Snd_StatusSet( SND_STATUS_PLAY );										//ステータス(再生)
	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	BGM停止
 *
 * @param	no		BGMナンバー
 * @param	frame	指定したフレーム数かけて徐々に音量を落としていく
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BgmStop( u16 no, int frame )
{
	u8 player_no;
	int type;

	NNS_SndPlayerStopSeqBySeqNo( no, frame );

	//----------------------------------------------------------
	//サウンドハンドルに結びつけられているシーケンスを解放します。
	//シーケンスが結びつけられていない場合は、何もしません。
	//
	//シーケンスナンバーから、プレイヤーナンバーを取得、
	//プレイヤーナンバーから、ハンドルナンバーを取得
	player_no = Snd_GetPlayerNo( no );
	if( player_no != 0xff ){
		type = Snd_GetHandleNoByPlayerNo( player_no );
		NNS_SndHandleReleaseSeq( Snd_HandleGet(type) );
	}
	//
	//BGM停止のみに処理を入れています。(BGM以外のハンドルについては未対処)
	//
	//----------------------------------------------------------

	//追加処理は↓の関数に追加する！
	Snd_BgmStopSub();
	return;
}

//BGM停止サブ(通常はSnd_BgmStopを使用して下さい)
static void Snd_BgmStopSub(void)
{
	Snd_NowBgmNoSet( 0 );					//今のBGMナンバークリア
	Snd_NextBgmNoSet( 0 );					//次のBGMナンバークリア
	Snd_StatusSet( SND_STATUS_STOP );		//ステータス(停止)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	今のBGMをフェードイン
 *
 * @param	vol		フェードイン後のボリューム(0-127)
 * @param	frame	フレーム数
 * @param	flag	"BGM_FADEIN_START_VOL_NOW = 現在の音量からFADEIN"
 * @param	(flag)	"BGM_FADEIN_START_VOL_MIN = 音量0からFADEIN"
 *
 * @retval	none
 *
 * フェードカウンターをセットしています
 */
//--------------------------------------------------------------
void Snd_BgmFadeIn( int vol, int frame, int flag )
{
	u8 player_no;
	int type;
	u16 now_bgm_no = Snd_NowBgmNoGet();		//今のBGMナンバー取得

	//シーケンスナンバーから、プレイヤーナンバーを取得
	player_no = Snd_GetPlayerNo( now_bgm_no );
	if( player_no == 0xff ){
		return;		//現在のシーケンスナンバーが0なので何もしない！
	}

	//プレイヤーナンバーから、ハンドルナンバーを取得
	type = Snd_GetHandleNoByPlayerNo( player_no );

	//フェードインの開始音量を0にする時
	if( flag == BGM_FADEIN_START_VOL_MIN ){
		//ハンドルのアドレスを取得
		Snd_PlayerMoveVolume( type, 0, 0 );
	}

	Snd_PlayerMoveVolume( type, vol, frame );
	Snd_FadeCountSet( frame );				//フェードカウンターセット
	Snd_StatusSet( SND_STATUS_FADEIN );		//ステータス(フェードイン)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	今のBGMをフェードアウト
 *
 * @param	vol		フェードアウト後のボリューム(0-127)
 * @param	frame	フレーム数
 *
 * @retval	none
 *
 * フェードカウンターをセットしています
 */
//--------------------------------------------------------------
void Snd_BgmFadeOut( int vol, int frame )
{
	u8 player_no;
	int type;
	u16 now_bgm_no = Snd_NowBgmNoGet();		//今のBGMナンバー取得

	//シーケンスナンバーから、プレイヤーナンバーを取得
	player_no = Snd_GetPlayerNo( now_bgm_no );
	if( player_no == 0xff ){
		return;		//現在のシーケンスナンバーが0なので何もしない！
	}

	//すでにフェードアウト中の時は、ゾーンを行ったり来たりしても、
	//フェードアウト中のBGMはそのままにする！
	
	//フェード中でない時
	if( Snd_FadeCheck() == 0 ){

		//プレイヤーナンバーから、ハンドルナンバーを取得
		type = Snd_GetHandleNoByPlayerNo( player_no );

		//ハンドルのアドレスを取得
		Snd_PlayerMoveVolume( type, vol, frame );
		Snd_FadeCountSet( frame );			//フェードカウンターセット
	}

	Snd_StatusSet( SND_STATUS_FADEOUT );	//ステータス(フェードアウト)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フェード終了待ち
 *
 * @param	none
 *
 * @retval	"0=終了、0以外はフェードカウンターの値"
 */
//--------------------------------------------------------------
int Snd_FadeCheck()
{
	u16* fade_count = Snd_GetParamAdrs(SND_W_ID_FADE_COUNT);
	return (*fade_count);
}

//--------------------------------------------------------------
/**
 * @brief	BGM終了待ち
 *
 * @param	no		BGMナンバー
 *
 * @retval	"再生中=TRUE、再生終了=FALSE"
 */
//--------------------------------------------------------------
int Snd_BgmPlayCheck( u16 no )
{
	u8 player_no;;

	//シーケンスナンバーから、プレイヤーナンバーを取得
	player_no = Snd_GetPlayerNo( no );

	return Snd_PlayerCountPlayingSeq( player_no );
}

//--------------------------------------------------------------
/**
 * @brief	全ての再生中のシーケンスを停止
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_Stop(void)
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	NNS_SndPlayerStopSeqAll(0);										//全て

	//Snd_WaveOutStop → Snd_WaveOutHandleGet内で、
	//確保していないチャンネルにアクセスしようとすると、
	//アサートで止まるので、ここでチェックして呼ばないようにしている
	if( *ch_normal_flag == 1 ){										//確保フラグがONだったら
		Snd_WaveOutStop( WAVEOUT_CH_NORMAL );						//波形停止
	}

	if( *ch_chorus_flag == 1 ){										//確保フラグがONだったら
		Snd_WaveOutStop( WAVEOUT_CH_CHORUS );						//波形停止
	}

	Snd_StatusSet( SND_STATUS_STOP );								//ステータス(停止)
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドBGM以外の全ての再生中のシーケンスを停止
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_StopEx(void)
{
	int i;
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_BGM), 0 );		//フィールドBGM以外
	Snd_BgmStopSub();

	for( i=0; i < SE_HANDLE_MAX ;i++ ){			//SE
		Snd_SeStop( (SND_HANDLE_SE_1 + i), 0 ); 
	}

	Snd_PMVoiceStop(0);							//PV

	//Snd_WaveOutStop → Snd_WaveOutHandleGet内で、
	//確保していないチャンネルにアクセスしようとすると、
	//アサートで止まるので、ここでチェックして呼ばないようにしている
	if( *ch_normal_flag == 1 ){										//確保フラグがONだったら
		Snd_WaveOutStop( WAVEOUT_CH_NORMAL );						//波形停止
	}

	if( *ch_chorus_flag == 1 ){										//確保フラグがONだったら
		Snd_WaveOutStop( WAVEOUT_CH_CHORUS );						//波形停止
	}

	//フィールドBGMはポーズ、復帰するので、停止処理を呼んではいけない！
	//ポーズ状態のままにしておく！
	
	return;
}


//==============================================================================================
//
//	SE関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	SE再生 + パン操作
 *
 * @param	no		SEナンバー
 * @param	pan		-128 ～ 127
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_SePlayPan( u16 no, int pan )
{
	int ret;

	ret = Snd_SePlay( no );
	Snd_SePanSet( no, 0xffff, pan );

	return ret;
}


//--------------------------------------------------------------
/**
 * @brief	SE再生
 *
 * @param	no		SEナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
BOOL Snd_SePlay( u16 no )
{
	int type,ret;

	//OS_Printf( "\n***************SE 再生\tno = %d\n", no );

	//シーケンスナンバーから、SEのプレイヤーナンバーを取得、
	//SEのプレイヤーナンバーから、SEのハンドルナンバーを取得
	type = Snd_GetHandleNoByPlayerNo( Snd_GetPlayerNo(no) );

	//シーケンス再生
	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(type), no );
	Snd_VChatVolSet( no, type );										//ボイスチャット音量操作

	//再生失敗チェック
	if( ret == 0 ){
//#ifdef SOUND_OS_PRINT_ON
		OS_Printf( "SE 再生失敗\tno = %d\n", no );
//#endif
	}

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	SE停止(シーケンスナンバー指定版)
 *
 * @param	no		SE番号
 * @param	frame	指定したフレーム数かけて徐々に音量を落としていく
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_SeStopBySeqNo( u16 no, int frame )
{
	NNS_SndPlayerStopSeqBySeqNo( no, frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	SE停止(サウンドハンドル指定版)
 *
 * @param	type	サウンドハンドルタイプ
 * @param	frame	指定したフレーム数かけて徐々に音量を落としていく
 *
 * @retval	none
 *
 * サウンドハンドルが無効の場合は、何もしません。 
 */
//--------------------------------------------------------------
void Snd_SeStop( int type, int frame )
{
	NNS_SndPlayerStopSeq( Snd_HandleGet(type), frame );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	SE終了待ち
 *
 * @param	no		SEナンバー
 *
 * @retval	"再生中=TRUE、再生終了=FALSE"
 *
 * 指定したSEが終了しているかチェックではなく、
 * 指定したSEの使用するプレイヤーに、
 * 再生中のシーケンスがあるかのチェックです。
 */
//--------------------------------------------------------------
int Snd_SePlayCheck( u16 no )
{
	return Snd_PlayerCountPlayingSeq( Snd_GetPlayerNo(no) );

	//以下保留
	//(プレイヤーナンバーではなく、シーケンスナンバーでもチェックできる)
	//NNS_SndPlayerCountPlayingSeqBySeqNo関数は、
	//シーケンス番号seqNoを指定して、再生中のシーケンスの数を数えます。
	//これは、NNS_SndPlayerSetSeqNo関数でセットしたシーケンス番号が、
	//seqNoと同じであるシーケンスの数を数えます。 
}

//--------------------------------------------------------------
/**
 * @brief	全てのSE終了待ち
 *
 * @param	none
 *
 * @retval	"再生中=TRUE、再生終了=FALSE"
 */
//--------------------------------------------------------------
int Snd_SePlayCheckAll()
{
	int i;

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		if( Snd_PlayerCountPlayingSeq(PLAYER_SE_1+i) == TRUE ){
			return TRUE;
		}
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	SEのPAN(定位)を変更
 *
 * @param	no		SEナンバー
 * @param	bitmask	トラックビットマスク
 * @param	pan		-128 ～ 127
 *
 * @retval	none
 *
 * trackBitMaskで、設定するトラックを指定します。
 * 下位ビットから順に、トラック0、トラック1、トラック2、、、を表し、
 * ビットが立っているトラック全てに対して、パンを変更します。
 *
 * 例えば、トラック2とトラック5のパンを変更したい場合は、 
 * (1 << 2) | (1 << 5) すなわち、0x0024 とします。 
 */
//--------------------------------------------------------------
void Snd_SePanSet( u16 no, u16 bitmask, int pan )
{
	int type;

	//シーケンスナンバーから、SEのプレイヤーナンバーを取得、
	//SEのプレイヤーナンバーから、SEのハンドルナンバーを取得
	type = Snd_GetHandleNoByPlayerNo( Snd_GetPlayerNo(no) );

	NNS_SndPlayerSetTrackPan( Snd_HandleGet(type), bitmask, pan );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	全てのSEのPAN(定位)を変更
 *
 * @param	pan		-128 ～ 127
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_SePanSetAll( int pan )
{
	int type, i;

	//SEのプレイヤーナンバーから、SEのハンドルナンバーを取得
	type = Snd_GetHandleNoByPlayerNo( PLAYER_SE_1 );

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		NNS_SndPlayerSetTrackPan( Snd_HandleGet(type+i), 0xffff, pan );
	}

	return;
}


//==============================================================================================
//
//	ポケモン鳴き声関連
//
//	＜未対応＞
//	波形再生(逆再生)を使用している技の最後に、FreeChannelを入れる！
//
//==============================================================================================
 
//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声再生(内部で再生前に停止が呼ばれます)
 *
 * @param	no		ポケモンナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 *
 * 例外として、コーラスを使用する時は、停止は呼ばれません。
 *
 * ポケモンナンバーと、鳴き声シーケンスデータの並びが同じか確認する！
 * (全国図鑑ナンバーに対応しているらしい。050722一之瀬さんより)
 *
 * <メモ>
 * シーケンスアーカイブだと、プレイヤーヒープが使えない！
 * シーケンスだと、プレイヤーヒープが使える！
 */
//--------------------------------------------------------------
BOOL Snd_PMVoicePlay( u16 no )
{
	int ret;
	u8* chorus_flag			= Snd_GetParamAdrs( SND_W_ID_CHORUS_FLAG );
	PERAPVOICE** my_perap	= Snd_GetParamAdrs( SND_W_ID_MY_PERAP_PTR );

	//不正な値チェック
	if( no != MONSNO_PERAPPU ){								//デバックのためぺラップは例外にしておく
		if( (no > MONSNO_MAX) || (no == 0) ){
			//GF_ASSERT( (0) && "ポケモンナンバーが不正です！" );
			//return FALSE;	//エラー
			OS_Printf( "ポケモンナンバーが不正です！" );
			no = MONSNO_HUSIGIDANE;
		}
	}

#if 1
	//通信の時は、この関数は使用しない！

	//Snd_PerapVoicePlayで他人のぺラップ再生が出来なくて、
	//この関数にきた時は、default_flagが立っているので、
	//ここも再生できずに、通常の再生へ進む
	
	//ぺラップナンバーかチェック
	if( no == MONSNO_PERAPPU ){
		
		//自分のぺラップの録音したデータを再生
		if( Snd_PerapVoicePlaySub(*my_perap, PM_MALE, PV_VOL_MAX, 0) == TRUE ){	//性別対応する！
			//再生をしたのでフラグを落とす
			Snd_PerapVoiceDefaultFlagSet(FALSE);//ぺラップのデフォルトの鳴き声を再生するフラグOFF
			return TRUE;
		}
	}
#endif

	//コーラス使用フラグをチェック
	if( *chorus_flag == 0 ){
		//シーケンスが2つ再生されないように停止処理を呼ぶ
		Snd_PMVoiceStop(0);
#if 0
		ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_PMVOICE), no );
#else
		//容量削減
		//
		//sound_data.sarcにseqデータを記述しなくてもバンクナンバーを取得出来る。
		//(音量テーブルは別に持たないといけなくなるが5000byteぐらい削減出来る)
		//
		//だが、全国図鑑ナンバーが頻繁に変わることを想定すると、
		//色々な所でポケモンナンバーの順番が関連するのは対応し忘れのもとなので、
		//sound_data.sarcにseqデータも書く形で進める！
		//
		//音量をシーケンスデータで持ちたくないかも。。。
		//現状外から音量をもらって再生などの形なので、
		//基本の音量設定をいかすには、その値に対してどうするかを決めないといけない。
		//外は、個々のポケモンの音量設定があると思っていない形になっている。。。
		ret = NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(SND_HANDLE_PMVOICE), -1, no, -1, SEQ_PV );
#endif
		Snd_VChatVolSet( no, SND_HANDLE_PMVOICE );						//ボイスチャット音量操作
	}else{
		//シーケンスが2つ再生される
#if 0
		ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_CHORUS), no );
#else
		ret = NNS_SndArcPlayerStartSeqEx( Snd_HandleGet(SND_HANDLE_CHORUS), -1, no, -1, SEQ_PV );
#endif
		Snd_VChatVolSet( no, SND_HANDLE_CHORUS );						//ボイスチャット音量操作
	}

	//再生をしたのでフラグを落とす
	Snd_PerapVoiceDefaultFlagSet(FALSE);	//ぺラップのデフォルトの鳴き声を再生するフラグOFF

	//再生失敗チェック
	if( ret == 0 ){
		OS_Printf( "PMVOICE 再生失敗\tno = %d\n", no );
	}

	return ret;
}
 
//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声停止(サウンドハンドル指定版)
 *
 * @param	frame	指定したフレーム数かけて徐々に音量を落としていく
 *
 * @retval	none
 *
 * サウンドハンドルが無効の場合は、何もしません。 
 *
 * コーラス(鳴き声専用)サウンドハンドルも停止させています。
 *
 * 逆再生使用フラグが立っていたら、波形停止処理も呼ぶようにしている
 * ポケモンの鳴き声を停止する処理はこの関数を呼べばよい。
 */
//--------------------------------------------------------------
void Snd_PMVoiceStop( int frame )
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	u8* reverse_flag   = Snd_GetParamAdrs(SND_W_ID_REVERSE_FLAG);

	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_PMVOICE), frame );	//鳴き声
	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_CHORUS), frame );	//コーラス

	//Snd_WaveOutStopReverseの中でもチェックしているので削除(06.03.09)
	//if( *reverse_flag == 1 ){								//逆再生使用フラグが立っていたら

		if( *ch_normal_flag == 1 ){										//CH確保していたら
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );				//buf開放
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );				//ch 開放(06.07.17)
		}
		if( *ch_chorus_flag == 1 ){										//CH確保していたら
			Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );				//buf開放
			Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );				//ch 開放(06.07.17)
		}
	//}

	Snd_PerapVoiceStop();									//ペラップ再生中フラグのクリア

	return;
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声終了待ち
 *
 * @param	none
 *
 * @retval	"再生中=1以上、再生終了=0"
 */
//--------------------------------------------------------------
int Snd_PMVoicePlayCheck(void)
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	u8* reverse_flag   = Snd_GetParamAdrs(SND_W_ID_REVERSE_FLAG);

	//逆再生を使用している時は、波形再生中かをチェックするようにする！
	//if( *reverse_flag == 1 ){									//逆再生使用フラグが立っていたら
		if( *ch_normal_flag == 1 ){								//CH確保していたら
			return Snd_WaveOutIsPlaying( WAVEOUT_CH_NORMAL );
		}
		if( *ch_chorus_flag == 1 ){								//CH確保していたら
			return Snd_WaveOutIsPlaying( WAVEOUT_CH_CHORUS );
		}
	//}

	//OS_Printf( "play check %d\n", Snd_PlayerCountPlayingSeq( PLAYER_PV ) );
	return Snd_PlayerCountPlayingSeq( PLAYER_PV );
}


//==============================================================================================
//
//	ポケモン鳴き声パターン関連
//
//	<未対応>
//	技の終了のタイミングで、波形再生用に確保したチャンネルの開放をいれる！
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声再生(パターン指定版)
 *
 * @param	no		ポケモンナンバー
 * @param	pan		-128 ～ 127
 * @param	vol		ボリューム(0-127)
 * @param	ptn		パターン(snd_tool.h参照)
 * @param	heap_id	ヒープID
 *
 * @retval	"成功=TRUE、失敗=FALSE"(現状は、必ず成功になっている。。。)
 *
 * <メモ>
 * PITCH	ABG=256,DS=64が半音
 * CHORUS	ピッチの差(-64～64)
 *
 * 鳴き声を使用する技は、「なきごえ、ほえる、とおぼえ、ハイパーボイス」ぐらい。
 *
 * PLAYER_PVは、シーケンス同時最大数を2に設定している。
 * Snd_PMVoicePlay関数内で、再生処理前に停止処理を呼んで、
 * 2つのシーケンスが再生されないようにしている。
 * コーラスを使用する時は、wk->chorus_flagが立つので、
 * Snd_PMVoicePlay関数内で、フラグをみて、停止処理を呼ばないようにしている
 *
 * 使用していない引数には、"PV_PTN_PARAM_NONE"を渡しておいて下さい
 */
//--------------------------------------------------------------
BOOL Snd_PMVoicePlayEx( int ptn, u16 no, int pan, int vol, int heap_id )
{
	int wave_pan,chorus_vol;
	u16 monsno;
	u16	pitch;						//半音(64)
	//u8	release;				//キーオフ後のリリース指定用
	int ret1,ret2,ret3,ret4;
	u8* ch_normal_flag		= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag		= Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	u8* chorus_flag			= Snd_GetParamAdrs(SND_W_ID_CHORUS_FLAG);
	u8* perap_play_flag		= Snd_GetParamAdrs( SND_W_ID_PERAP_PLAY_FLAG );
	PERAPVOICE** my_perap	= Snd_GetParamAdrs( SND_W_ID_MY_PERAP_PTR );

	ret1 = 0;
	ret2 = 0;
	ret3 = 0;
	ret4 = 0;

	//シーケンス再生のパンは(-127 - 0 - 127)となっている
	//波形再生のパンは(0 - 64 - 127)となっている
	
	//波形再生パンを取得
	if( pan < 0 ){
		wave_pan = 64 + (pan / 2);		//0 - 64  にする
	}else{
		wave_pan = 64 + (pan / 2);		//64 - 127 にする
	}

	//コーラスの音量設定
	chorus_vol = vol - 30;
	if( chorus_vol <= 0 ){
		chorus_vol = 1;
	}

	//初期値代入
	//release	= DEFAULT_RELEASE;
	pitch = 0;

	*chorus_flag = 0;			//コーラス使用フラグOFF

	//チャンネルを確保していたら開放
	if( *ch_normal_flag == 1 ){
		Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );		//buf開放
		Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );		//ch 開放
	}
	if( *ch_chorus_flag == 1 ){
		Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );		//buf開放
		Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );		//ch 開放
	}

#if 1
	//不正な値チェック
	
	monsno = no;

	if( no != MONSNO_PERAPPU ){								//デバックのためぺラップは例外にしておく
		if( (no > MONSNO_MAX) || (no == 0) ){
			OS_Printf( "ポケモンナンバーが不正です！" );
			monsno = MONSNO_HUSIGIDANE;
		}
	}
#endif

#if 1
	//ぺラップだったら
	if( no == MONSNO_PERAPPU ){

		switch( ptn ){

		//自分のぺラップの録音したデータを再生
		case PV_NORMAL:		// = 0 通常再生
		case PV_HALF:		// = 1 再生時間短縮（２ｖｓ２バトルでポケモン登場時）
		case PV_FLDEVENT:	// = 2 怒ったポケモン（フィールドイベント）
		case PV_POKEDOWN:	// = 5 ポケモンがやられた時
		case PV_PINCHNORMAL:// =11 通常再生(元気なし)
		case PV_PINCHHALF:	// =12 再生時間短縮（２ｖｓ２バトルでポケモン登場時）(元気なし)

			Snd_PMVoicePlay( MONSNO_PERAPPU );

			//ぺラップの録音したデータを再生しているかフラグをチェック
			if( *perap_play_flag == 0 ){
				Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
				Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );				//音量操作
			}else{
				Snd_WaveOutSetPan( WAVEOUT_CH_NORMAL, wave_pan );
				Snd_WaveOutSetVolume( WAVEOUT_CH_NORMAL, vol );
			}
			return TRUE;		//注意！

		//上記以外は、デフォルトの鳴き声を再生する！
		default:
			Snd_PerapVoiceDefaultFlagSet(TRUE);	//ぺラップのデフォルトの鳴き声を再生するフラグON
			break;
		}
	}
#endif

	switch( ptn ){

	// = 0 通常再生
	case PV_NORMAL:
		//----------------
		//play
		//pan,vol
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		break;

	// = 1 再生時間短縮（２ｖｓ２バトルでポケモン登場時）
	case PV_HALF:
		//----------------
		//play
		//pan,vol,length
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		Snd_PMVoiceLengthSet(20,heap_id);										//release = 225;
		break;

	// = 2 怒ったポケモン（フィールドイベント）
	case PV_FLDEVENT:		
		//----------------
		//play
		//pan,vol,pitch
		//
		//chorus
		//pan,vol
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		//release		= 225;
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );				//音量操作
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3840/6 );	//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 64 );			//ピッチ

		ret3 = Snd_ChorusPlay( monsno, 20 );								//コーラス(注意！)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_CHORUS, chorus_vol );			//音量操作
		break;

	// = 3 技効果音・とおぼえ用
	case PV_W_TOOBOE:	
		//----------------
		//play
		//pan,vol,length,pitch
		//
		//chorus
		//pan,vol
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		//Snd_PMVoiceLengthSet(15,heap_id);//(50);
		Snd_PMVoiceLengthSet(30,heap_id);//(50);								//release = 200;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 110 );			//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 120 );			//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 160 );			//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 192 );				//ピッチ

		//ret3 = Snd_ChorusPlay( monsno, 20 );									//コーラス(注意！)
		ret3 = Snd_ChorusPlay( monsno, 16 );									//コーラス(注意！)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_CHORUS, chorus_vol );				//音量操作
		break;

	// = 4 技効果音・ハイパーボイス用１
	case PV_W_HYPER1:		
		//----------------
		//reverse
		//
		//chorus
		//----------------
		ret2 = Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );
		ret2 = Snd_WaveOutStartReverse( monsno, vol, wave_pan, WAVEOUT_CH_NORMAL, heap_id );
		Snd_WaveOutSetPan( WAVEOUT_CH_NORMAL, wave_pan );					//パン
		//Snd_PMVoiceLengthSet(25,heap_id);									//release = 100;
		//Snd_PMVoiceLengthSet(20,heap_id);									//release = 100;
		Snd_PMVoiceLengthSet(15,heap_id);									//release = 100;
		Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, W_HYPER_VOICE_PITCH );

		//コーラス(注意！)
		//ret4 = Snd_ChorusPlayReverse(monsno, -64, VOICE_SMALL_VOL, wave_pan, heap_id);
		ret4 = Snd_ChorusPlayReverse(monsno, -64, chorus_vol, wave_pan, heap_id);
		Snd_WaveOutSetSpeed( WAVEOUT_CH_CHORUS, W_HYPER_VOICE_PITCH );
		break;

	// = 5 ポケモンがやられた時
	case PV_POKEDOWN:			
		//----------------
		//play
		//pan,vol,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3584/6 );		//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -224 );			//ピッチ
		break;

	// = 6 技効果音・ハイパーボイス用２
	case PV_W_HYPER2:			
		//----------------
		//play
		//pan,vol,pitch
		//
		//chorus
		//pan
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		//release		= 220;
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );						//音量操作
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );			//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 44 );					//ピッチ

		ret3 = Snd_ChorusPlay( monsno, -64 );	//コーラス(注意！)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_CHORUS, chorus_vol );					//音量操作
		break;

	// = 7 技効果音・ほえる１
	case PV_W_HOERU1:		
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		//Snd_PMVoiceLengthSet(10,heap_id);										//release = 100;
		Snd_PMVoiceLengthSet(11,heap_id);										//release = 100;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3584/6 );		//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -128 );			//ピッチ
		break;

	// = 8 技効果音・ほえる２
	case PV_W_HOERU2:			
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		Snd_PMVoiceLengthSet(60,heap_id);										//release = 225;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 60 );				//ピッチ
		break;

	// = 9 技効果音・なきごえ１
	case PV_W_NAKIGOE1:		
		//----------------
		//reverse
		//----------------
		ret2 = Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );
		ret2 = Snd_WaveOutStartReverse( monsno, vol, wave_pan, WAVEOUT_CH_NORMAL, heap_id );
		Snd_WaveOutSetPan( WAVEOUT_CH_NORMAL, wave_pan );						//パン
		//Snd_PMVoiceLengthSet(15,heap_id);
		Snd_PMVoiceLengthSet(13,heap_id);										//release = 125;
		Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, W_NAKIGOE_PITCH );
		break;

	// =10 技効果音・なきごえ２
	case PV_W_NAKIGOE2:			
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		Snd_PMVoiceLengthSet(100,heap_id);										//release = 225
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -96 );			//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -64 );			//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -21 );			//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -32 );			//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -48 );			//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -44 );				//ピッチ
		break;

	// =11 通常再生(元気なし)
	case PV_PINCHNORMAL:		
		//----------------
		//play
		//pan,vol,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -44 );			//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -96 );				//ピッチ
		break;

	// =12 再生時間短縮（２ｖｓ２バトルでポケモン登場時）(元気なし)
	case PV_PINCHHALF:		
		//----------------
		//play
		//pan,vol,length,pitch
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, pan );
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, vol );					//音量操作
		//Snd_PMVoiceLengthSet(20,heap_id);
		//Snd_PMVoiceLengthSet(15,heap_id);
		//Snd_PMVoiceLengthSet(13,heap_id);										//release = 225;
		Snd_PMVoiceLengthSet(20,heap_id);										//release = 225;
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 3904/6 );		//ピッチ
		//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -128 );			//ピッチ
		Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -96 );				//ピッチ
		break;	

	// =13 図鑑コーラス再生
	case PV_ZUKAN_CHORUS:		
		//----------------
		//play
		//
		//chorus
		//pan,vol
		//----------------
		Snd_PMVoicePlay( monsno );

		//注意！　ボリュームは固定
		Snd_PMVoiceVolSet( monsno, SND_HANDLE_PMVOICE, PV_VOL_MAX );			//音量操作

		Snd_ChorusPlay( monsno, SND_ZUKAN_PITCH_CHORUS );						//コーラス(注意！)
		Snd_PlayerSetTrackPan( SND_HANDLE_CHORUS, 0xffff, pan );

		//注意！　コーラスのボリュームを操作出来るようにする
		//Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, chorus_vol, 0 );			//コーラスボリューム
		Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, vol, 0 );					//コーラスボリューム
		break;

	// =14 図鑑ノーマル再生
	case PV_ZUKAN_NORMAL:		
		//----------------
		//play
		//----------------
		ret1 = Snd_PMVoicePlay( monsno );
		break;
	}

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "1)pv play ptn normal = %d\n", ret1 );
	OS_Printf( "2)pv play ptn reverse = %d\n", ret2 );
	OS_Printf( "3)pv play ptn chorus = %d\n", ret3 );
	OS_Printf( "4)pv play ptn reverse chorus = %d\n\n", ret4 );
#endif

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声　音量操作(鳴き声は外から音量をもらうので必要)
 *
 * @param	no			シーケンスナンバー
 * @param	handle_no	ハンドルナンバー
 * @param	vol			ボリューム
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_PMVoiceVolSet( u16 seq_no, int handle_no, int vol )
{
	//外からボリュームもらうので必要
	Snd_PlayerSetInitialVolume( handle_no, vol );

	//外からもらうボリュームとは関係なく、デフォルトの設定の半分にする
	Snd_VChatVolSet( seq_no, handle_no );									//ボイスチャット音量操作
	return;
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声再生時間セット(TCB追加)
 *
 * @param	no		シーケンスナンバー
 * @param	heap_id	ヒープID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PMVoiceLengthSet( int length, int heap_id )
{
	SND_PMVOICE_LENGTH_WORK* wk = NULL;
	TCB_PTR* length_tcb			= Snd_GetParamAdrs(SND_W_ID_LENGTH_TCB);

	//すでに登録されていたらTCB削除
	if( *length_tcb != NULL ){
		OS_Printf( "\n警告　ポケモン鳴き声\n" );
		OS_Printf( "再生時間操作TCBが終了していないのに、再度呼ばれています！\n" );
	}
	Snd_PMVoiceLengthTcbDel();

	wk = sys_AllocMemory( heap_id, sizeof(SND_PMVOICE_LENGTH_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "メモリ確保失敗！" );
		return;
	}
	memset( wk, 0, sizeof(SND_PMVOICE_LENGTH_WORK) );

	wk->length	= length;
	wk->tcb		= TCB_Add( Snd_PMVoiceLengthMainTCB, wk, 0 );
	*length_tcb = wk->tcb;
	return;
}

//この値より"length"が小さくなると音量を合わせて"0"にしていく
//#define SND_PMVOICE_LENGTH_VOL		(20)
//この値に"length"がなった時に音量を"0"になるようにセットする
#define SND_PMVOICE_LENGTH_VOL_SET		(10)
//--------------------------------------------------------------
/**
 * @brief	TCBメイン
 *
 * @param	tcb		TCB_PTR
 * @param	wk		ワークのアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_PMVoiceLengthMainTCB( TCB_PTR tcb, void* wk )
{
	u8* ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	u8* ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);
	SND_PMVOICE_LENGTH_WORK* swk = (SND_PMVOICE_LENGTH_WORK *)wk;

#if 1
	//音量も自然に小さくしていく
	//if( swk->length < SND_PMVOICE_LENGTH_VOL ){
	
	//音量が"0"になっていくようにセットする
	if( swk->length == SND_PMVOICE_LENGTH_VOL_SET ){
		Snd_PlayerMoveVolume( SND_HANDLE_PMVOICE, 0, swk->length );
		Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, 0, swk->length );
	}
#endif

	swk->length--;

#ifdef SOUND_OS_PRINT_ON
	//OS_Printf( "length = %d\n", swk->length );
#endif

	//鳴き声が終了していたら強制終了(06.04.12)
	if( Snd_PMVoicePlayCheck() == 0 ){
		swk->length = 0;
	}

	if( swk->length <= 0 ){

		//鳴き声を停止させる
		Snd_PMVoiceStop(0);

		//Snd_WaveOutStopReverseの中で、
		//逆再生使用フラグチェックをしているので、
		//ここでは、リバースチェックはしていない！(06.03.09)

		//波形再生　チャンネルを確保していたら開放
		if( *ch_normal_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );	//buf開放
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );	//ch 開放
		}
		if( *ch_chorus_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );	//buf開放
			Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );	//ch 開放
		}

		//TCB削除
		Snd_PMVoiceLengthTcbDel();
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声再生時間TCB削除
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PMVoiceLengthTcbDel()
{
	void* wk;
	TCB_PTR* length_tcb = Snd_GetParamAdrs(SND_W_ID_LENGTH_TCB);

	//登録されていたらTCB削除
	if( *length_tcb != NULL ){
		wk = TCB_GetWork( *length_tcb );
		TCB_Delete( *length_tcb );
		sys_FreeMemoryEz( wk );
	}

	*length_tcb = NULL;
	return;
}

#if 0
//--------------------------------------------------------------
/**
 * @brief	ポケモン鳴き声減衰セット(TCB追加)
 *
 * @param	no		シーケンスナンバー
 * @param	heap_id ヒープID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_PMVoiceReleaseSet(int reverse, u32 ch, int frame, int heap_id)
{
	int ret;
	SND_PMVOICE_RELEASE_WORK* wk = NULL;

	//すでに登録されていたらTCB削除
	ret = Snd_TCBDelSub( SND_TCB_PMVOICE_RELEASE );
	if( ret == TRUE ){
		OS_Printf( "\n警告　ポケモン鳴き声\n" );
		OS_Printf( "減衰操作TCBが終了していないのに、再度呼ばれています！\n" );
	}

	wk = sys_AllocMemory( heap_id, sizeof(SND_PMVOICE_RELEASE_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "メモリ確保失敗！" );
		return;
	}
	memset( wk, 0, sizeof(SND_PMVOICE_RELEASE_WORK) );

	if( reverse == 0 ){
		Snd_PlayerMoveVolume( SND_HANDLE_PMVOICE, 0, frame );
	}else{
		//注意！現状は127に固定にしている
		//現在のボリューム/frameの値をフレームごとに引いていく
		//Snd_WaveOutSetVolume( ch, int vol );
	}

	wk->reverse	= reverse;
	wk->frame	= frame;
	wk->count	= 0;

	wk->sub		= 127/frame;
	if( wk->sub == 0 ){
		wk->sub = 1;
	}

	wk->tcb		= TCB_Add( Snd_PMVoiceReleaseMainTCB, wk, 0 );
	*release_tcb= wk->tcb;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	TCBメイン
 *
 * @param	tcb		TCB_PTR
 * @param	wk		ワークのアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_PMVoiceReleaseMainTCB( TCB_PTR tcb, void* wk )
{
	u8* ch_normal_flag;
	u8* ch_chorus_flag;
	SND_PMVOICE_RELEASE_WORK *swk;

	swk = (SND_PMVOICE_RELEASE_WORK *)wk;
	ch_normal_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_NORMAL_FLAG);
	ch_chorus_flag = Snd_GetParamAdrs(SND_W_ID_WAVEOUT_CH_CHORUS_FLAG);

	if( swk->reverse == 1 ){
		if( swk->count < 255 ){
			swk->count++;
		}

		if( (swk->sub*swk->count) >= 127 )
			Snd_WaveOutSetVolume( ch, 0 );
		}else{
			//注意！現状は127に固定にしている
			//現在のボリューム/frameの値をフレームごとに引いていく
			Snd_WaveOutSetVolume( ch, 127-(swk->sub*swk->count) );
		}
	}
		
	swk->frame--;
	if( swk->frame <= 0 ){

		//シーケンス
		Snd_PMVoiceStop(0);

		//波形再生　チャンネルを確保していたら開放
		if( *ch_normal_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );
		}
		if( *ch_chorus_flag == 1 ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_CHORUS );
			Snd_WaveOutFreeChannel( WAVEOUT_CH_CHORUS );
		}

#if 0
		TCB_Delete( swk->tcb );
		sys_FreeMemoryEz( wk );
#else
		Snd_PMVoiceReleaseTcbDel();
#endif
	}

	return;
}
#endif



#if 0
	//----------------
	//あとで実験する！
	//----------------
	
	//モジュレーションデプステスト
	NNS_SndPlayerSetTrackModDepth( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 30 );
	//NNS_SndPlayerSetTrackModDepth( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 60 );
	//NNS_SndPlayerSetTrackModDepth( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 80 );
	
	//モジュレーションスピードテスト(0-255)
	//speedのデフォルトは16で、約6.4Hzに相当します。値が２倍になると、周波数も２倍になります。
	//NNS_SndPlayerSetTrackModSpeed( Snd_HandleGet(SND_HANDLE_PMVOICE), 0xffff, 80 );
#endif


//==============================================================================================
//
//	コーラス関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	コーラス処理(シーケンス再生)
 *
 * @param	none
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
static BOOL Snd_ChorusPlay( u16 no, s8 chorus )
{
	int ret;
	u8* chorus_flag = Snd_GetParamAdrs( SND_W_ID_CHORUS_FLAG );

	*chorus_flag = 1;	//コーラス使用フラグON

	Snd_PerapVoiceDefaultFlagSet(TRUE);	//ぺラップのデフォルトの鳴き声を再生するフラグON
	ret = Snd_PMVoicePlay( no );
	Snd_PlayerSetTrackPitch( SND_HANDLE_CHORUS, 0xffff, chorus );	//ピッチ

	return ret; 
}

//--------------------------------------------------------------
/**
 * @brief	コーラス処理(波形逆再生)
 *
 * @param	no
 * @param	chorus
 * @param	vol
 * @param	pan
 * @param	heap_id	ヒープID
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 */
//--------------------------------------------------------------
static BOOL Snd_ChorusPlayReverse( u16 no, s8 chorus, int vol, int pan, int heap_id )
{
	int ret;
	u8* chorus_flag = Snd_GetParamAdrs( SND_W_ID_CHORUS_FLAG );

	*chorus_flag = 1;	//コーラス使用フラグON

	ret = Snd_WaveOutAllocChannel( WAVEOUT_CH_CHORUS );
	ret = Snd_WaveOutStartReverse( no, vol, pan, WAVEOUT_CH_CHORUS, heap_id );	//注意！(コーラス)

	return ret; 
}


//==============================================================================================
//
//	ME関連
//	BGMの波形のみ開放して大丈夫(入れないと容量足りないか確認)
//
//	使用例1(ME終了後、BGM再開)
//	Snd_MePlay(bgm)
//	if( Snd_MePlayCheckBgmPlay(&wk) == FALSE ){
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BGMポーズ → ME再生
 *
 * @param	no			MEナンバー
 *
 * @retval	"再生成功=TRUE、失敗=FALSE"
 *
 * ウェイトワークにME共通ウェイト値がセットされます
 */
//--------------------------------------------------------------
BOOL Snd_MePlay( u16 no )
{
	u16 now_bgm_no;
	u8 player_no;
	int ret,i;
	const NNSSndArcBankInfo* info;									//バンク情報構造体
	info = Snd_GetBankInfo( no );									//バンク情報構造体取得

	Snd_MeWaitSet( no );											//ME共通ウェイト値セット

	//ポーズするプレイヤーは、今のBGMナンバーを鳴らしているプレイヤー！
	now_bgm_no = Snd_NowBgmNoGet();									//今のBGMナンバー取得
	player_no = Snd_GetPlayerNo( now_bgm_no );

	//現在のシーケンスナンバーが0でなかったら
	if( player_no != 0xff ){
		Snd_PlayerPause( player_no, TRUE );							//BGMポーズ
	}

	//ポーズ中は、波形データのみ開放してよい！
	
	//MEは、追加波形なし

	//サブ画面データをロードしている時があるので、MEデータのみの追加削除をする！
	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_ME) );	//ME追加、削除用

	//シーケンス、バンクデータをロード
	ret = Snd_ArcLoadSeqEx( no, (NNS_SND_ARC_LOAD_SEQ | NNS_SND_ARC_LOAD_BANK) );

#ifdef SOUND_OS_PRINT_ON
	OS_Printf( "MEシーケンスデータロード = %d\n", ret );
#endif

	ret = NNS_SndArcPlayerStartSeq( Snd_HandleGet(SND_HANDLE_ME), no );
	Snd_VChatVolSet( no, SND_HANDLE_ME );							//ボイスチャット音量操作

	return ret;
}

//--------------------------------------------------------------
/**
 * @brief	ME終了待ち
 *
 * @param	none
 *
 * @retval	"再生中=TRUE、再生終了=FALSE"
 *
 * Snd_MePlay
 * Snd_MePlayCheck
 * ここまでだと解放処理が入っていない！
 * Snd_MeStopが必要！
 *
 * もしくは、
 * Snd_MePlay
 * Snd_MePlayCheckBgmPlay
 * で使う！
 */
//--------------------------------------------------------------
int Snd_MePlayCheck(void)
{
	u16* me_wait = Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

	if( Snd_PlayerCountPlayingSeq(PLAYER_ME) != 0 ){
		return TRUE;
	}

	if( *me_wait > 0 ){													//ウェイトチェック
		(*me_wait)--;
		return TRUE;													//ウェイト中
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ME停止
 *
 * @param	frame	指定したフレーム数かけて徐々に音量を落としていく
 *
 * @retval	none
 *
 * サウンドハンドルが無効の場合は、何もしません。 
 */
//--------------------------------------------------------------
static void Snd_MeStop( int frame )
{
	int no,type;
	u16 i;

	NNS_SndPlayerStopSeq( Snd_HandleGet(SND_HANDLE_ME), frame );	//ME停止

	//サブ画面データをロードしている時があるので、MEデータのみの追加削除をする！
	Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_ME) );		//ME追加、削除用
	
	return;
}

//--------------------------------------------------------------
/**
 * @brief	ME終了待ち → 終了後、ウェイトを入れてからBGMを復帰させる
 *
 * @param	none
 *
 * @retval	"ME再生中=TRUE、ウェイト中=TRUE、BGM再開=FALSE"
 */
//--------------------------------------------------------------
int Snd_MePlayCheckBgmPlay(void)
{
	u8 player_no;
	u16 now_bgm_no;
	u16* me_wait = Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

	//ME終了待ち
	if( Snd_MePlayCheck() == TRUE ){
		return TRUE;
	}

	Snd_MeStop( 0 );												//ME停止

	now_bgm_no = Snd_NowBgmNoGet();									//今のBGMナンバー取得
	player_no = Snd_GetPlayerNo( now_bgm_no );

	//現在のシーケンスナンバーが0でなかったら
	if( player_no != 0xff ){
		Snd_PlayerPause( player_no, FALSE );						//BGM再開
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ME共通ウェイト値セット
 *
 * @param	no			MEナンバー
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_MeWaitSet( u16 no )
{
	u16* me_wait = Snd_GetParamAdrs(SND_W_ID_ME_WAIT);

#if 0
	//MEごとの共通ウェイトを持ちたい時
	switch( no ){
	case SEQ_FANFA1:
		break;
	case SEQ_FANFA4:
		break;
	}
#endif

	(*me_wait) = SND_ME_COMMON_WAIT;
	return;						
}


//==============================================================================================
//
//	デバック関数
//
//==============================================================================================
#ifdef PM_DEBUG
//--------------------------------------------------------------
/**
 * @brief	デバック関数：BGMフラグのセット
 *
 * @param	sw		0=通常、1=BGMオフ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_DebugBgmFlagSet( u8 sw )
{
	debug_bgm_flag = sw;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	デバック関数：BGMフラグの取得
 *
 * @param	none
 *
 * @retval	"0=通常、1=BGMオフ"
 */
//--------------------------------------------------------------
static BOOL Snd_DebugBgmFlagCheck( void )
{
	return debug_bgm_flag;
}
#endif


