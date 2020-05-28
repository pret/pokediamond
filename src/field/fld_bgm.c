//==============================================================================================
/**
 * @file	fld_bgm.c
 * @brief	フィールドサウンド操作
 * @author	Satoshi Nohara
 * @date	2005.10.14
 */
//==============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "system/snd_tool.h"
#include "system/gamedata.h"		//POKE_NUM_MAX
#include "system/pm_rtc.h"			//GF_RTC_IsNightTime
#include "mapdefine.h"				//ZONE_ID_C01
#include "zonedata.h"				//ZoneData_GetBGMID
#include "player.h"					//HERO_FORM_SWIM
#include "sway_grass_enc.h"
#include "fld_bgm.h"
#include "field/situation_local.h"

#include "battle/battle_common.h"	//↓インクルードに必要
#include "poketool/tr_tool.h"
#include "battle/trtype_def.h"

#include "tr_bgm.dat"
#include "sysflag.h"


//==============================================================================================
//
//	変数
//
//==============================================================================================


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void Snd_GameOverSet();
void Snd_RestartSet( FIELDSYS_WORK* fsys );

//フィールドBGMナンバー取得
u16 Snd_FieldBgmNoGet( FIELDSYS_WORK* fsys, int zone_id );

//フィールドBGMナンバー取得(BASIC_BANKを除く)
u16 Snd_FieldBgmNoGetNonBasicBank( FIELDSYS_WORK* fsys, int zone_id );

//"ゾーンをまたぐ専用"フェードアウト → BGM再生(フィールド専用)
BOOL Snd_FadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode );

//"マップ遷移専用"　フェードアウト → BGM再生(フィールド専用)
static BOOL Snd_MapChangeFadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode );

//ev_mapchange.c用の関数
BOOL Snd_MapChangeFadeOutNextPlaySub( FIELDSYS_WORK* fsys, int zone_id, int mode );

//ローカル関数
static void Snd_BgmFadeOutTimeGet( FIELDSYS_WORK* fsys, int mode, int* frame, int* next_wait );

//BGMナンバー取得
u16 Snd_EyeBgmGet( int tr_id );
u16 Snd_BattleBgmGet( u32 fight_type, int tr_id );
u16 Snd_ZoneDataBgmNoGet( int zone_id );


//==============================================================================================
//
//	関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	ゲームオーバー時にする処理(field_encount.cから呼ばれる)
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_GameOverSet()
{
	//全ての再生中のシーケンスを停止
	Snd_Stop();

	//全てのポーズフラグクリア
	Snd_PauseClearAll();

	//フィールドシーンからフィールドシーンのロードがあるので、
	//一度シーンをクリアしてから、フィールドデータロードへ進む
	Snd_SceneSet( SND_SCENE_DUMMY );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	ゲームオーバー後に再開する時の処理(field_encount.cから呼ばれる)
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	none
 *
 * 未使用！
 */
//--------------------------------------------------------------
void Snd_RestartSet( FIELDSYS_WORK* fsys )
{
	u16 bgm_no;

	//フィールドシーンからフィールドシーンのロードがあるので、
	//一度シーンをクリアしてから、フィールドデータロードへ進む
	Snd_SceneSet( SND_SCENE_DUMMY );

	//フィールドデータロード
	bgm_no = Snd_FieldBgmNoGet( fsys, fsys->location->zone_id );
	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );

	//フェードイン
	Snd_BgmFadeIn(BGM_VOL_MAX, BGM_FADEIN_RESTART_TIME, BGM_FADEIN_START_VOL_MIN);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGM指定セット
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	bgm_no	BGMナンバー
 *
 * @retval	none
 *
 * マップ内限定のBGM指定がセットされる
 * 自転車BGMの制御などに使用
 */
//--------------------------------------------------------------
void Snd_FieldBgmSetSpecial( FIELDSYS_WORK* fsys, u16 bgm_no )
{
	u16* situation_bgm	= Situation_GetBGMWork( SaveData_GetSituation(fsys->savedata) );
	*situation_bgm		= bgm_no;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGM指定ゲット
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	"BGMナンバー"
 *
 * マップ内限定のBGM指定がセットされる
 * 自転車BGMの制御などに使用
 */
//--------------------------------------------------------------
u16 Snd_FieldBgmGetSpecial( FIELDSYS_WORK* fsys )
{
	u16* situation_bgm	= Situation_GetBGMWork( SaveData_GetSituation(fsys->savedata) );
	return (*situation_bgm);
}

//--------------------------------------------------------------
/**
 * @brief	BGM指定クリア
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	none
 *
 * マップ内限定のBGM指定がクリアされる
 * 自転車BGMの制御などに使用
 */
//--------------------------------------------------------------
void Snd_FieldBgmClearSpecial( FIELDSYS_WORK* fsys )
{
	u16* situation_bgm	= Situation_GetBGMWork( SaveData_GetSituation(fsys->savedata) );
	*situation_bgm		= 0;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドBGMナンバー取得
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	zone_id	ゾーンID
 *
 * @retval	"フィールドBGMナンバー"
 *
 * マップ管理表は直接見ないで、この関数を通してBGMナンバー取得する
 */
//--------------------------------------------------------------
u16 Snd_FieldBgmNoGet( FIELDSYS_WORK* fsys, int zone_id )
{
	PLAYER_STATE_PTR player;
	int status;
	u16 bgm_no,ret;

	player = fsys->player;
	status = Player_FormGet(player);

	//波乗り中かチェック
	if( status == HERO_FORM_SWIM ){
		return SEQ_NAMINORI;
	}

	//ゆれ草中かチェック
	if( SwayGrass_CheckValid(fsys->SwayGrass) == TRUE ){
		return SEQ_KUSAGASA;
	}

	//フィールドBGMナンバー取得(BASIC_BANKを除く)
	bgm_no = Snd_FieldBgmNoGetNonBasicBank( fsys, zone_id );

	/*
	INIT_CHANGEで、BmgSpecialSetを呼び出して、
	イベント曲切り替えを反映させようと思ったが、
	次のゾーンの曲フェードインが、
	次のゾーンのINIT_CHANGEより先にくるため出来ない！
	なので、次のゾーンIDは取得できているので、
	ここでイベントフラグを見てイベント曲に切り替える！(06.06.17)
	*/

	//特殊BGM指定がセットされていたら(自転車など)
	if( Snd_FieldBgmGetSpecial(fsys) != 0 ){
		bgm_no = Snd_FieldBgmGetSpecial( fsys );
	}

	return bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	フィールドBGMナンバー取得(BASIC_BANKを除く)
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	zone_id	ゾーンID
 *
 * @retval	"フィールドBGMナンバー"
 *
 * マップ遷移の時は、BASIC_BANKになるものを含めたくない
 * マップ遷移の時は、特殊指定はチェックする必要がない
 * マップ遷移の時は、自転車、なみのりは引き継ぐことはない
 */
//--------------------------------------------------------------
u16 Snd_FieldBgmNoGetNonBasicBank( FIELDSYS_WORK* fsys, int zone_id )
{
	u16 bgm_no,ret;

	//マップ管理表からBGMナンバーを返す
	if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=昼、TRUE=夜
		bgm_no = ZoneData_GetDayBGMID( zone_id );
	}else{
		bgm_no = ZoneData_GetNightBGMID( zone_id );
	}

	//イベントBGM切り替え
	ret = SysFlag_EventBgmGet( SaveData_GetEventWork(fsys->savedata), zone_id );
	if( ret != 0 ){
		bgm_no = ret;
	}

	return bgm_no;
}

//--------------------------------------------------------------
/**
 * @brief	"ゾーンをまたぐ専用"　フェードアウト → BGM再生(フィールド専用)
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	seq_no	シーケンスナンバー
 * @param	mode	モード(fld_bgm.h参照)
 *
 * @retval	"0=何もしない、1=開始"
 *
 * フィールド以外は、この関数を使用して下さい！
 * ●Snd_BgmFadeOutNextPlaySet(...);
 *
 * ゾーンをまたぐ専用です。道路、町のゾーンをまたぐ時に使用します。
 * マップ遷移には使用できません。
 */
//--------------------------------------------------------------
BOOL Snd_FadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode )
{
	PLAYER_STATE_PTR player;
	int frame,next_wait,status;

	player = fsys->player;
	status = Player_FormGet(player);

	//フィールドBGMを固定にするフラグチェック(セーブはしない)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return 0;		//何もしない
	}

	//変更するBGMナンバーが、今のBGMナンバーと同じかチェック
	if( seq_no == Snd_NowBgmNoGet(fsys) ){
		return 0;		//何もしない
	}

	//イベントで、連れ歩きBGMをPLAYER_BGMで鳴らしながら、マップ遷移すると、
	//PLAYER_FIELDがポーズ状態のままになっている！
	//ゾーン切り替え時はポーズを全てクリアしても問題ないはず！
	
	//全てのポーズフラグクリア
	Snd_PauseClearAll();

	//建物の出入りか、ゾーンをまたぐ時かによって、フェードアウト時間を変える！
	Snd_BgmFadeOutTimeGet( fsys, mode, &frame, &next_wait );

	if( (status == HERO_FORM_CYCLE_R) || (status == HERO_FORM_CYCLE_D) ){
		//自転車に乗っている時はフェードアウト→フェードイン(バンクそのまま継続)
		Snd_FadeOutNextFadeInSet(SND_SCENE_FIELD, seq_no, frame, next_wait, 
									BGM_FADEIN_CYCLE_TIME, SND_BANK_CONTINUE, NULL);
	}else{
		//通常はフェードアウト→開始(バンクそのまま継続)
		Snd_FadeOutNextPlaySet(SND_SCENE_FIELD, seq_no, frame, next_wait, SND_BANK_CONTINUE, NULL);
	}

	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	"マップ遷移専用"　フェードアウト → BGM再生(フィールド専用)
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	seq_no	シーケンスナンバー
 * @param	mode	モード(fld_bgm.h参照)
 *
 * @retval	"0=何もしない、1=開始"
 *
 * マップ遷移専用です。建物、ダンジョンに入る時に使用します。
 * 道路、町のゾーンをまたぐ時には使用できません。
 */
//--------------------------------------------------------------
static BOOL Snd_MapChangeFadeOutNextPlayCall( FIELDSYS_WORK* fsys, u16 seq_no, int mode )
{
	int frame,next_wait;

	/*

	//マップチェンジのコマンド内で、
	//
	//１、BGMが変更されるかチェック
	//２、変更される時は、
	//３、フェードアウト
	//４、フェードアウト待ち
	//ここまでと
	//１、次のBGMをロードして再生
	//に分けるとタイミングが取りやすいかも。
	//ただ、今はタイミング合っている。

	//あと、FLAG_CHANGEでサウンドワークのリクエストBGMにBGMナンバーを入れて、
	//それに値が入っていたら、そのBGMを鳴らせるようにしておくとよいかも。
	//Snd_FieldBgmNoGetで、イベントのチェックをかかず、スクリプトで全てかけるようになるので。
	
	*/

	//フィールドBGMを固定にするフラグチェック(セーブはしない)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return 0;		//何もしない
	}

	//変更するBGMナンバーが、今のBGMナンバーと同じかチェック
	if( seq_no == Snd_NowBgmNoGet(fsys) ){
		return 0;		//何もしない
	}

	//イベントで、連れ歩きBGMをPLAYER_BGMで鳴らしながら、マップ遷移すると、
	//PLAYER_FIELDがポーズ状態のままになっている！
	//ゾーン切り替え時はポーズを全てクリアしても問題ないはず！
	
	//全てのポーズフラグクリア
	Snd_PauseClearAll();

	//建物の出入りか、ゾーンをまたぐ時かによって、フェードアウト時間を変える！
	Snd_BgmFadeOutTimeGet( fsys, mode, &frame, &next_wait );

	//フェードアウト→開始(バンク切り替える)
	Snd_FadeOutNextPlaySet(SND_SCENE_FIELD, seq_no, frame, next_wait, SND_BANK_CHANGE, NULL);
	
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	"マップ遷移専用"　ev_mapchange.c用の関数
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	zone_id	ゾーンID
 * @param	mode	モード(fld_bgm.h参照)
 *
 * @retval	"0=何もしない、1=開始"
 *
 * マップ遷移専用です。建物、ダンジョンに入る時に使用します。
 * 道路、町のゾーンをまたぐ時には使用できません。
 */
//--------------------------------------------------------------
BOOL Snd_MapChangeFadeOutNextPlaySub( FIELDSYS_WORK* fsys, int zone_id, int mode )
{
	u16 bgm_no = Snd_FieldBgmNoGet( fsys, zone_id );
	Snd_ZoneBgmSet( Snd_ZoneDataBgmNoGet(zone_id) );				//ゾーンの曲をセット
	return Snd_MapChangeFadeOutNextPlayCall( fsys, bgm_no, mode );
}


//==============================================================================================
//
//	ローカル関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	フェードアウト時間取得
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	mode		モード(fld_bgm.h参照)
 * @param	frame		フェードアウトフレーム数を格納するポインタ
 * @param	next_wait	次のBGMを鳴らすまでのフレーム数を格納するポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_BgmFadeOutTimeGet( FIELDSYS_WORK* fsys, int mode, int* frame, int* next_wait )
{
	//マップ管理表で、ゾーンのタイプ(室内か、フィールドか、洞窟かなど)を
	//判別できるようになったら、引数のモードはいらないかも？

	//建物の出入りか、ゾーンをまたぐ時かによって、フェードアウト時間を変える！
	
	switch( mode ){

	//建物の出入り
	case BGM_FADE_ROOM_MODE:
		*frame		= BGM_FADE_ROOM_TIME;
		*next_wait	= 0;
		break;

	//フィールドの切り替え
	case BGM_FADE_FIELD_MODE:
		*frame		= BGM_FADE_FIELD_TIME;
		*next_wait	= 0;
		break;

	//洞窟の出入り
	case BGM_FADE_CAVE_MODE:
		*frame		= BGM_FADE_CAVE_TIME;
		*next_wait	= BGM_NEXT_WAIT_CAVE_TIME;
		break;

	//その他
	case BGM_FADE_OTHERS_MODE:
		*frame		= BGM_FADE_OTHERS_TIME;
		*next_wait	= 0;
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	トレーナー視線BGM取得(スクリプトから呼ばれる)
 *
 * @param	tr_id	トレーナーID
 *
 * @retval	none
 */
//--------------------------------------------------------------
u16 Snd_EyeBgmGet( int tr_id )
{
	u8 type;
	u16 bgm,i;

	type = (u8)TT_TrainerDataParaGet( tr_id, ID_TD_tr_type );

	bgm = SEQ_EYE_KID;	//保険

	for( i=0; i < TRTYPE_BGM_TBL_MAX ;i++ ){

		if( trtype_bgm_tbl[i][0] == type ){
			bgm = trtype_bgm_tbl[i][1];
			break;
		}
	}

	return bgm;
}

//--------------------------------------------------------------
/**
 * @brief	戦闘BGM取得
 *
 * @param	fight_type	戦闘種別フラグ
 * @param	tr_id		トレーナーID
 *
 * @retval	none
 */
//--------------------------------------------------------------
u16 Snd_BattleBgmGet( u32 fight_type, int tr_id )
{
	u8 type;
	u16 bgm = SEQ_BA_POKE;

	//野生ＯＲサファリ   k.ohno 通信対戦で止まるので修正

    //トレーナー
	if(fight_type == FIGHT_TYPE_TRAINER){

		type = (u8)TT_TrainerDataParaGet( tr_id, ID_TD_tr_type );

		switch( type ){

		//ジム
		case TRTYPE_LEADER1:
		case TRTYPE_LEADER2:
		case TRTYPE_LEADER3:
		case TRTYPE_LEADER4:
		case TRTYPE_LEADER5:
		case TRTYPE_LEADER6:
		case TRTYPE_LEADER7:
		case TRTYPE_LEADER8:
			bgm = SEQ_BA_GYM;
			break;

		//ギンガ団
		case TRTYPE_GINGAM:
		case TRTYPE_GINGAW:
			bgm = SEQ_BA_GINGA;
			break;

		//ギンガ団ボス
		case TRTYPE_GINGALEADER1:
		case TRTYPE_GINGALEADER2:
		case TRTYPE_GINGALEADER3:
			bgm = SEQ_BA_AKAGI;
			break;

		//トレーナー
		default:
			bgm = SEQ_BA_TRAIN;
			break;
		}
	}

	return bgm;
}

//--------------------------------------------------------------
/**
 * @brief	ゾーンデータのBGMナンバー取得
 *
 * @param	zone_id	ゾーンID
 *
 * @retval	"BGMナンバー"
 */
//--------------------------------------------------------------
u16 Snd_ZoneDataBgmNoGet( int zone_id )
{
	u16 bgm_no;

	//マップ管理表からBGMナンバーを返す
	if( GF_RTC_IsNightTime() == FALSE ){			//FALSE=昼、TRUE=夜
		bgm_no = ZoneData_GetDayBGMID( zone_id );
	}else{
		bgm_no = ZoneData_GetNightBGMID( zone_id );
	}

	return bgm_no;
}


//==============================================================================================
//
//	マップ遷移用(またぐ時は使用不可！)
//
//	ev_mapchange.c
//	map_jump.c
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	マップ遷移：ゾーン切り替える時にフェードアウト
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	zone_id		ゾーンID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_EvMapChangeBgmFadeCheck( FIELDSYS_WORK* fsys, int zone_id )
{
	//フィールドBGMを固定にするフラグチェック(セーブはしない)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return;
	}

	//フィールドBGMナンバー取得(BASIC_BANKを除く)
	if( Snd_NowBgmNoGet() != Snd_FieldBgmNoGetNonBasicBank(fsys,zone_id) ){
		Snd_BgmFadeOut( 0, BGM_FADE_MAPJUMP_TIME );
	}
	return;
}

//--------------------------------------------------------------
/**
 * @brief	マップ遷移：ゾーン切り替える時のBGM再生
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	zone_id		ゾーンID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_EvMapChangeBgmPlay( FIELDSYS_WORK* fsys, int zone_id )
{
	u16 bgm_no;

	//フィールドBGMを固定にするフラグチェック(セーブはしない)
	if( Snd_CtrlBgmFlagCheck() == 1 ){
		return;
	}

	Snd_SceneSet( SND_SCENE_DUMMY );

	//フィールドBGMナンバー取得(BASIC_BANKを除く)
	bgm_no = Snd_FieldBgmNoGetNonBasicBank( fsys, zone_id );

	Snd_ZoneBgmSet( bgm_no );		//ゾーン曲セット

	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );
	return;
}


//==============================================================================================
//
//	フィールド初期化用
//
//	fieldmap.c
//	fld_menu.c(進化後の復帰に使用)
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	フィールド初期化：サウンドデータセット
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	zone_id		ゾーンID
 *
 * @retval	none
 *
 * シーンが変更されない時は何もしない！
 */
//--------------------------------------------------------------
void Snd_FieldMapInitBgmPlay( FIELDSYS_WORK* fsys, int zone_id )
{
	u16 bgm_no;

	bgm_no = Snd_FieldBgmNoGet( fsys, zone_id );	//自転車BGMで復帰することもありえる！

	Snd_ZoneBgmSet( Snd_FieldBgmNoGetNonBasicBank(fsys,zone_id) );	//ゾーン曲セット

	//サウンドデータセット(シーンが変更されない時は何もしない)
	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );
	return;
}


