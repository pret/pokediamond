//============================================================================================
/**
 * @file	fnote_mem.c
 * @brief	冒険ノート　データ管理処理
 * @author	Hiroyuki Nakamura
 * @date	2006.03.06
 */
//============================================================================================
#include "common.h"
#include "system/savedata.h"
#include "system/buflen.h"
#include "system/pm_rtc.h"
#include "savedata/mystatus.h"
#include "msgdata/msg_place_name.h"
#include "battle/trno_def.h"
#include "field/field_place_name.h"
#include "../field/mapdefine.h"
#include "../field/zonedata.h"
#include "../field/sysflag.h"

#define	FNOTE_MEM_H_GLOBAL
#include "savedata/fnote_mem.h"


//============================================================================================
//	定数定義
//============================================================================================

// セーブデータ本体
struct _FNOTE_DATA {
	FNOTE_WK_START	hed;			// 開始データ
// 4
	u32	action[FNOTE_ACTION_MAX];	// 行動
// 4+16
	FNOTE_WK_POKE	pokemon;		// ポケモン
// 4+16+4
	FNOTE_WK_TRAINER trainer;		// トレーナー
// 4+16+4+4
	u8	sio[FNOTE_SIO_MAX][42];		// 通信
// 4+16+4+4+84 = 112
};

// 特殊な建物データ
typedef struct {
	u32	name;		// 名前ID
	u32	type;		// 表示タイプ
}EX_BUILD_DATA;

// ジムテーブル
typedef struct {
	u32	tr;			// トレーナーID
	u16	zone;		// ゾーンID
	u16	badge;		// バッジフラグ
}GYM_TBL;


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void FNOTE_StartDataSave( FNOTE_DATA * dat, FNOTE_WK_START * wk );
static void FNOTE_ActionDataSave( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_PokemonDataSave( FNOTE_DATA * dat, FNOTE_WK_POKE * wk );
static void FNOTE_TrainerDataSave( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk );
static void FNOTE_SioDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk );

static u32 * FNOTE_ActionSavePosGet( u32 * action );
static u8 * FNOTE_SioSavePosGet( FNOTE_DATA * dat );
static void FNOTE_ActionIDDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionTrainerDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionSitennouDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionGymLeaderDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionMapDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionItemDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionSkillDataSave( u32 * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_SioBattleDataSave( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioUnionGreetDataSave( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioPokeChgDataSave( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioIDDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioContestDataSave( u8 * dat, FNOTE_WK_SIO * wk );

static void FNOTE_StrCopy( const STRCODE * str, STRCODE * buf, u32 siz );

static void FNOTE_StartDataGet( FNOTE_DATA * dat, FNOTE_WK_START * wk );
static void FNOTE_ActionDataGet( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk );
static void FNOTE_PokemonDataGet( FNOTE_DATA * dat, FNOTE_WK_POKE * wk );
static void FNOTE_TrainerDataGet( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk );
static void FNOTE_SioDataGet( FNOTE_DATA * dat, FNOTE_WK_SIO * wk );

static void FNOTE_ActionIDDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionTrainerDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionMapDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionItemDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_ActionSkillDataGet( u32 dat, FNOTE_WK_ACTION * wk );
static void FNOTE_SioBattleDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioUnionGreetDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioPokeChgDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioIDDataGet( u8 * dat, FNOTE_WK_SIO * wk );
static void FNOTE_SioContestDataGet( u8 * dat, FNOTE_WK_SIO * wk );

static u8 GymCheck( MYSTATUS * my, u32 zone_id );
static u8 TrainerCheck( u32 tr );


//============================================================================================
//	グローバル変数
//============================================================================================
// 特殊な建物テーブル
static const EX_BUILD_DATA BuildNameTable[] =
{
	{ MAPNAME_C1TV,				1 },	// テレビ　コトブキ
	{ MAPNAME_C1POKETCH,		0 },	// ポケッチカンパニー
	{ MAPNAME_C1GTC,			1 },	// ＧＴＣ
	{ MAPNAME_C1SCHOOL,			1 },	// トレーナーズスクール
	{ MAPNAME_C3HAKUBUTUKAN,	0 },	// たんこうはくぶつかん
	{ MAPNAME_T3FLOWER,			1 },	// フラワー　ショプ
	{ MAPNAME_C4BICYCLE,		1 },	// サイクル　ショップ
	{ MAPNAME_C5CONTEST,		1 },	// コンテストかいじょう
	{ MAPNAME_C5POFFINN,		1 },	// ポフィンハウス
//	{ MAPNAME_D11HIROBA,		0 },	// ふれあいひろば
	{ MAPNAME_C5BUILDING,		0 },	// いぶんかのたてもの
	{ MAPNAME_T4SODATEYA,		1 },	// ポケモンそだてや
	{ MAPNAME_C7DEPARTMENT,		0 },	// トバリデパート
	{ MAPNAME_C7GAME,			1 },	// ゲームコーナー
	{ MAPNAME_D26AZITO,			0 },	// ギンガだんアジト
	{ MAPNAME_C7TOSYOKAN,		0 },	// ミオ　としょかん
	{ MAPNAME_D20KISSAKI,		0 },	// キッサキしんでん
	{ MAPNAME_C8TODAI,			0 },	// シルベの　とうだい
	{ MAPNAME_C8ITIBA,			1 },	// ナギサ　いちば
	{ MAPNAME_D31TOWER,			1 },	// バトルタワー
	{ MAPNAME_R212YASIKI,		0 },	// ポケモンやしき
	{ MAPNAME_R213ASIATO,		1 },	// あしあとはかせのいえ
//	{ MAPNAME_D10POKEPARK,		1 },	// ポケパーク
	{ MAPNAME_R210KISSATEN,		0 },	// きっさてん
	{ MAPNAME_L02HOTEL,			0 },	// グランドレイク
	{ MAPNAME_L02RESTAURANT,	0 },	// レストラン
	{ MAPNAME_D2HATUDEN,		0 },	// たにまのはつでんしょ
	{ MAPNAME_D4TATARA,			0 },	// タタラせいてつじょ
	{ MAPNAME_D25YOUKAN,		0 }		// もりのようかん
};

// ジムテーブル
static const GYM_TBL GymTbl[] =
{
	{ LEADER1_01, ZONE_ID_C03GYM0101, BADGE_ID_C03 },	// クロガネ、いわくだき
	{ LEADER2_01, ZONE_ID_C04GYM0101, BADGE_ID_C04 },	// ハクタイ、いあいぎり
	{ LEADER3_01, ZONE_ID_C06GYM0101, BADGE_ID_C06 },	// ノモセ、きりばらい
	{ LEADER4_01, ZONE_ID_C07GYM0101, BADGE_ID_C07 },	// トバリ、そらをとぶ
	{ LEADER5_01, ZONE_ID_C05GYM0101, BADGE_ID_C05 },	// ヨスガ、なみのり
	{ LEADER6_01, ZONE_ID_C09GYM0101, BADGE_ID_C09 },	// キッサキ、ロッククライム
	{ LEADER7_01, ZONE_ID_C02GYM0101, BADGE_ID_C02 },	// ミオ、かいりき
	{ LEADER8_01, ZONE_ID_C08GYM0101, BADGE_ID_C08 }	// ナギサ、たきのぼり
};


//--------------------------------------------------------------------------------------------
/**
 * 冒険ノート用ワークのサイズ取得
 *
 * @param	none
 *
 * @return	ワークサイズ
 */
//--------------------------------------------------------------------------------------------
int FNOTE_GetWorkSize(void)
{
	return ( sizeof(FNOTE_DATA) * FNOTE_PAGE_MAX );
}

//--------------------------------------------------------------------------------------------
/**
 * 冒険ノート用ワーク初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_Init( FNOTE_DATA * dat )
{
	memset( dat, 0, sizeof(FNOTE_DATA) );
}

//--------------------------------------------------------------------------------------------
/**
 * 冒険ノート用ワーク初期化（全体）
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_InitAll( FNOTE_DATA * dat )
{
	memset( dat, 0, sizeof(FNOTE_DATA)*FNOTE_PAGE_MAX );
}

//--------------------------------------------------------------------------------------------
/**
 * セーブデータから冒険ノートのポインタを取得
 *
 * @param	sv		セーブデータ
 *
 * @return	冒険ノートデータ
 */
//--------------------------------------------------------------------------------------------
FNOTE_DATA * SaveData_GetFNote( SAVEDATA * sv )
{
	return SaveData_Get( sv, GMDATA_ID_FNOTE );
}

//--------------------------------------------------------------------------------------------
/**
 * セーブページ取得
 *
 * @param	dat		セーブデータ
 * @param	flg		セーブ許可フラグ ( TRUE = 許可 )
 *
 * @retval	"flg = TRUE : セーブページ"
 * @retval	"flg = FALSE : NULL"
 */
//--------------------------------------------------------------------------------------------
FNOTE_DATA * FNOTE_SavePageGet( FNOTE_DATA * dat, BOOL flg )
{
	RTCDate	rtc;
	s32	i;

	// セーブ許可チェック
	if( flg != TRUE ){ return NULL; }

	GF_RTC_GetDate( &rtc );

	if( dat[0].hed.month != 0 &&
		( dat[0].hed.year != rtc.year || dat[0].hed.month != rtc.month ||
		  dat[0].hed.day != rtc.day || dat[0].hed.week != rtc.week ) ){

		// データシフト
		for( i=FNOTE_PAGE_MAX-1; i>=1; i-- ){
			dat[i] = dat[i-1];
		}
		FNOTE_Init( &dat[0] );
	}
	return &dat[0];


/*
	// 日付が一致するデータを取得
	GF_RTC_GetDate( &rtc );
	for( i=0; i<FNOTE_PAGE_MAX; i++ ){
		if( dat[i].hed.year == rtc.year && dat[i].hed.month == rtc.month &&
			dat[i].hed.day == rtc.day && dat[i].hed.week == rtc.week ){

			return &dat[i];
		}
	}

	// データが無い場所を取得
	for( i=0; i<FNOTE_PAGE_MAX; i++ ){
		if( dat[i].hed.month == 0 ){
			return &dat[i];
		}
	}

	// 空きが無い場合は、シフトして後ろのデータを取得
	for( i=0; i<FNOTE_PAGE_MAX-1; i++ ){
		dat[i] = dat[i+1];
	}
	FNOTE_Init( &dat[i] );
	return &dat[i];
*/
}

//--------------------------------------------------------------------------------------------
/**
 * ゲーム開始時の冒険ノート表示チェック
 *
 * @param	dat		セーブデータ
 * @param	flg		セーブ許可フラグ ( TRUE = 許可 )
 *
 * @retval	"TRUE = 表示"
 * @retval	"FALSE = 表示しない"
 */
//--------------------------------------------------------------------------------------------
BOOL FNOTE_GameStartOpenCheck( FNOTE_DATA * dat, BOOL flg )
{
	RTCDate	note;
	RTCDate	now;
	int	ofs;

	// セーブ許可チェック
	if( flg != TRUE ){ return FALSE; }

	// 現在の時間
	GF_RTC_GetDate( &now );
	// 冒険ノートの最新の時間
	note.year  = dat[0].hed.year;
	note.month = dat[0].hed.month;
	note.day   = dat[0].hed.day;
	note.week  = dat[0].hed.week;

	ofs = GF_RTC_GetDaysOffset(&now) - GF_RTC_GetDaysOffset(&note);
	if( ofs == 0 ){
		if( now.year != note.year ){
			return TRUE;
		}
	}else if( ofs <= -2 ){
		return TRUE;
	}else if( ofs >= 2 ){
		return TRUE;
	}
	return FALSE;
}


//============================================================================================
//	データセーブ
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 回想セーブ
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするデータ
 * @param	type	記録タイプ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataSave( FNOTE_DATA * dat, void * wk, u8 type )
{
	if( dat != NULL ){
		switch( type ){
		case FNOTE_TYPE_START:		// 開始
			FNOTE_StartDataSave( dat, wk );
			break;

		case FNOTE_TYPE_ACTION:		// 行動
			FNOTE_ActionDataSave( dat, wk );
			break;

		case FNOTE_TYPE_POKEMON:	// ポケモン
			FNOTE_PokemonDataSave( dat, wk );
			break;

		case FNOTE_TYPE_TRAINER:	// トレーナー
			FNOTE_TrainerDataSave( dat, wk );
			break;

		case FNOTE_TYPE_SIO:		// 通信
			FNOTE_SioDataSave( dat, wk );
			break;
		}
	}
	sys_FreeMemoryEz( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * 開始データセーブ
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_StartDataSave( FNOTE_DATA * dat, FNOTE_WK_START * wk )
{
	if( dat->hed.year == wk->year && dat->hed.month == wk->month &&
		dat->hed.day == wk->day && dat->hed.week == wk->week ){
		return;
	}
	dat->hed = *wk;
}

//--------------------------------------------------------------------------------------------
/**
 * 行動データセーブ
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionDataSave( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk )
{
	switch( wk->id ){
	case FNOTE_ID_MYHOUSE:			// 行動：自宅
	case FNOTE_ID_LABO:				// 行動：研究所
	case FNOTE_ID_POKECENTER:		// 行動：ポケモンセンター
	case FNOTE_ID_FDSHOP_BUY:		// 行動：ショップ・買う
	case FNOTE_ID_FDSHOP_BUY2:		// 行動：ショップ・買う（複数）
	case FNOTE_ID_FDSHOP_SALE:		// 行動：ショップ・売る
	case FNOTE_ID_FDSHOP_SALE2:		// 行動：ショップ・売る（複数）
	case FNOTE_ID_FDSHOP_TRADE:		// 行動：ショップ・売買
	case FNOTE_ID_GAMECORNER:		// 行動：ゲームコーナー
	case FNOTE_ID_SAFARIZONE:		// 行動：サファリゾーン
	case FNOTE_ID_UG_FOSSIL:		// 行動：地下・化石掘り
	case FNOTE_ID_UG_BASE:			// 行動：地下・秘密基地
		FNOTE_ActionIDDataSave( dat->action, wk );
		break;

	case FNOTE_ID_GYMBEFORE:		// 行動：ジム（リーダーを倒す前）
	case FNOTE_ID_GYMAFTER:			// 行動：ジム（リーダーを倒した後）
		FNOTE_ActionGymLeaderDataSave( dat->action, wk );
		break;

	case FNOTE_ID_SITENNOU:			// 行動：四天王
		FNOTE_ActionSitennouDataSave( dat->action, wk );
		break;

	case FNOTE_ID_CHAMPION:			// 行動：チャンピオン
		FNOTE_ActionTrainerDataSave( dat->action, wk );
		break;

	case FNOTE_ID_CITY:				// 行動：街
	case FNOTE_ID_DUNGEON:			// 行動：ダンジョン
	case FNOTE_ID_BUILD:			// 行動：建物
		FNOTE_ActionMapDataSave( dat->action, wk );
		break;

	case FNOTE_ID_ITEMGET:			// 行動：アイテム取得
		FNOTE_ActionItemDataSave( dat->action, wk );
		break;

	case FNOTE_ID_IAIGIRI:			// 行動：技・いあいぎり
	case FNOTE_ID_SORAWOTOBU:		// 行動：技・そらをとぶ
	case FNOTE_ID_NAMINORI:			// 行動：技・なみのり
	case FNOTE_ID_KAIRIKI:			// 行動：技・かいりき
	case FNOTE_ID_FLASH:			// 行動：技・フラッシュ
	case FNOTE_ID_KIRIBARAI:		// 行動：技・きりばらい
	case FNOTE_ID_IWAKUDAKI:		// 行動：技・いわくだき
	case FNOTE_ID_TAKINOBORI:		// 行動：技・たきのぼり
	case FNOTE_ID_ROCKCLIMB:		// 行動：技・ロッククライム
	case FNOTE_ID_ANAWOHORU:		// 行動：技・あなをほる
	case FNOTE_ID_AMAIKAORI:		// 行動：技・あまいかおり
	case FNOTE_ID_TELEPORT:			// 行動：技・テレポート
	case FNOTE_ID_TAMAGOUMI:		// 行動：技・タマゴうみ
	case FNOTE_ID_MIRUKUNOMI:		// 行動：技・ミルクのみ
		FNOTE_ActionSkillDataSave( dat->action, wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンデータセーブ
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_PokemonDataSave( FNOTE_DATA * dat, FNOTE_WK_POKE * wk )
{
	dat->pokemon = *wk;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーデータセーブ
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_TrainerDataSave( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk )
{
	dat->trainer = *wk;
}

//--------------------------------------------------------------------------------------------
/**
 * 通信データセーブ
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk )
{
	u8 * sio = FNOTE_SioSavePosGet( dat );

	switch( wk->id ){
	case FNOTE_ID_SB_SINGLE:		// 通信：通信対戦・シングル
	case FNOTE_ID_SB_DOUBLE:		// 通信：通信対戦・ダブル
	case FNOTE_ID_SB_MULTI:			// 通信：通信対戦・マルチ
	case FNOTE_ID_SB_MIX1:			// 通信：通信対戦・ミックス1vs1
	case FNOTE_ID_SB_MIX2:			// 通信：通信対戦・ミックス2vs2
	case FNOTE_ID_U_BATTLE:			// 通信：ユニオンルーム・対戦
		FNOTE_SioBattleDataSave( sio, wk );
		break;

	case FNOTE_ID_U_GREETING:		// 通信：ユニオンルーム・挨拶
		FNOTE_SioUnionGreetDataSave( sio, wk );
		break;

	case FNOTE_ID_U_POKECHG:		// 通信：ユニオンルーム・交換
	case FNOTE_ID_U_MLTCHG:			// 通信：ユニオンルーム・複数人交換
	case FNOTE_ID_GTC:				// 通信：GTC
		FNOTE_SioPokeChgDataSave( sio, wk );
		break;

	case FNOTE_ID_U_PICTURE:		// 通信：ユニオンルーム・お絵かき
	case FNOTE_ID_U_TRANSCEIVER:	// 通信：ユニオンルーム・トランシーバー
	case FNOTE_ID_RECORD:			// 通信：レコードコーナー
	case FNOTE_ID_PORUTO:			// 通信：ポルト作成
	case FNOTE_ID_BTLTOWER:			// 通信：バトルタワー
		FNOTE_SioIDDataSave( dat, wk );
		break;

	case FNOTE_ID_CONTEST:			// 通信：コンテスト
		FNOTE_SioContestDataSave( sio, wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 行動データのセーブ位置取得
 *
 * @param	action	セーブデータ
 *
 * @return	セーブ位置
 */
//--------------------------------------------------------------------------------------------
static u32 * FNOTE_ActionSavePosGet( u32 * action )
{
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( ( action[i] & 0x3f ) == 0 ){
			return &action[i];
		}
	}

	for( i=0; i<FNOTE_ACTION_MAX-1; i++ ){
		action[i]  = action[i+1];
	}
	action[i] = 0;
	return &action[i];
}

//--------------------------------------------------------------------------------------------
/**
 * 通信データのセーブ位置取得
 *
 * @param	dat		セーブデータ
 *
 * @return	セーブ位置
 */
//--------------------------------------------------------------------------------------------
static u8 * FNOTE_SioSavePosGet( FNOTE_DATA * dat )
{
	u32	i;

	for( i=0; i<FNOTE_SIO_MAX; i++ ){
		if( dat->sio[i][0] == 0 ){
			return &dat->sio[i][0];
		}
	}

	for( i=0; i<FNOTE_SIO_MAX-1; i++ ){
		memcpy( &dat->sio[i][0], &dat->sio[i+1][0], 42 );
	}
	memset( &dat->sio[i][0], 0, 42 );
	return &dat->sio[i][0];
}


//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 行動：IDのみのもの ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 *
 * @li	*dat = ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionIDDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){
			break;
		}
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id ){ return; }
	}

	buf = FNOTE_ActionSavePosGet( dat );
	*buf = ( wk->id & 0x3f );
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 行動：チャンピオン ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ((trainer & 0x3ff) << 6) | (id & 0x3f)
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionTrainerDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 行動：四天王 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ((trainer & 0x3ff) << 6) | (id & 0x3f)
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionSitennouDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u16	map;
	u16	i;

	buf = NULL;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( ( dat[i] & 0x3f ) == FNOTE_ID_SITENNOU ){
			dat[i] = 0;
			for( i=i; i<FNOTE_ACTION_MAX-1; i++ ){
				dat[i] = dat[i+1];
			}
			break;
		}
	}

	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 行動：ジムリーダー ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ((trainer & 0x3ff) << 6) | (id & 0x3f)
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionGymLeaderDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u16	map;
	u16	i;

	buf = NULL;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( (dat[i]&0x3f) == FNOTE_ID_GYMBEFORE && ((dat[i]>>16)&0xffff) == wk->map ){
			dat[i] = 0;
			for( i=i; i<FNOTE_ACTION_MAX-1; i++ ){
				dat[i] = dat[i+1];
			}
			break;
		}
	}

	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 行動：街、ダンジョン、建物など ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 *
 * @li	*dat = (map << 16) | ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionMapDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){ break; }
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id && (dat[i-1]>>16) == wk->map ){
			return;
		}
	}
	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 行動：アイテム取得 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 *
 * @li	*dat = (item << 16 ) | ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionItemDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){ break; }
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id && (dat[i-1]>>16) == wk->item ){
			return;
		}
	}
	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->item << 16) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 行動：技 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 *
 * @li	*dat = ( id & 0x3f )
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionSkillDataSave( u32 * dat, FNOTE_WK_ACTION * wk )
{
	u32 * buf;
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		if( dat[i] == 0 ){ break; }
	}
	if( i != 0 ){
		if( (dat[i-1]&0x3f) == wk->id && (dat[i-1]>>16) == wk->map ){
			return;
		}
	}
	buf = FNOTE_ActionSavePosGet( dat );
	*buf = (wk->map << 16) | (wk->id & 0x3f);
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 通信：対戦 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioBattleDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = (wk->result<<2) | (wk->sex1<<1) | (wk->sex2);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->name2, (STRCODE *)&dat[18], 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 通信：ユニオンルーム・挨拶 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioUnionGreetDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = wk->sex1;
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 通信：交換 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioPokeChgDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = (wk->sex1 << 2) | (wk->poke_sex);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->nickname, (STRCODE *)&dat[18], 12 );
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 通信：バトルタワー ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioIDDataSave( FNOTE_DATA * dat, FNOTE_WK_SIO * wk )
{
	u32	i;
	u8 * buf;

	for( i=0; i<FNOTE_SIO_MAX; i++ ){
		if( dat->sio[i][0] == 0 ){
			break;
		}
	}
	if( i != 0 ){
		if( dat->sio[i-1][0] == wk->id ){ return; }
	}
	buf = FNOTE_SioSavePosGet( dat );
	buf[0] = wk->id;
}

//--------------------------------------------------------------------------------------------
/**
 * データセーブ [ 通信：コンテスト ]
 *
 * @param	dat		セーブデータ
 * @param	wk		セーブするワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioContestDataSave( u8 * dat, FNOTE_WK_SIO * wk )
{
	dat[0] = wk->id;
	dat[1] = wk->result;
}


//============================================================================================
//	データ作成
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 日付・開始場所 ]
 *
 * @param	start	開始場所
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 *
 * @li	日付はRTCから取得
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_StartDataMake( u16 start, u32 heap )
{
	FNOTE_WK_START * wk;
	RTCDate	rtc;

	wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_START) );

	GF_RTC_GetDate( &rtc );

	wk->year  = rtc.year;
	wk->month = rtc.month;
	wk->day   = rtc.day;
	wk->week  = rtc.week;
	wk->start = start;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * 項目・行動用ワーク確保
 *
 * @param	heap	ヒープID
 *
 * @return	確保したワーク
 */
//--------------------------------------------------------------------------------------------
static FNOTE_WK_ACTION * FNOTE_ActionWorkAlloc( u32 heap )
{
	FNOTE_WK_ACTION * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_ACTION) );
	memset( wk, 0, sizeof(FNOTE_WK_ACTION) );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：自宅 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionHouseDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_MYHOUSE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：研究所 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionLaboDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_LABO;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ポケモンセンター ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_PokemonCenterDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_POKECENTER;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・買う ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopBuyDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_BUY;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・買う（複数） ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopBuy2DataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_BUY2;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・売る ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopSaleDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_SALE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・売る（複数） ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopSale2DataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_SALE2;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・売買 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionShopTradeDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_FDSHOP_TRADE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ジム（リーダーを倒す前）]
 *
 * @param	map		マップID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionGymBeforeDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_GYMBEFORE;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ジム（リーダーを倒した後） ]
 *
 * @param	map		マップID
 * @param	trainer	トレーナーID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionGymAfterDataMake( u16 map, u16 trainer, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id      = FNOTE_ID_GYMAFTER;
	wk->map     = map;
	wk->trainer = trainer;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：四天王 ]
 *
 * @param	trainer	トレーナーID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionSitenouDataMake( u16 trainer, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id      = FNOTE_ID_SITENNOU;
	wk->trainer = trainer;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：チャンピオン ]
 *
 * @param	trainer	トレーナーID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionChampionDataMake( u16 trainer, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id      = FNOTE_ID_CHAMPION;
	wk->trainer = trainer;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：街 ]
 *
 * @param	map		マップID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionCityDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_CITY;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ダンジョン ]
 *
 * @param	map		マップID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionDungeonDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_DUNGEON;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：建物 ]
 *
 * @param	map		マップID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionBuildDataMake( u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_BUILD;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ゲームコーナー ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionGameCornerDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_GAMECORNER;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：サファリゾーン ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionSafariDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_SAFARIZONE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：アイテム取得 ]
 *
 * @param	item	アイテムID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionItemDataMake( u16 item, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id   = FNOTE_ID_ITEMGET;
	wk->item = item;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：技 ]
 *
 * @param	waza	フィールド技番号
 * @param	map		マップID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionSkillDataMake( u8 waza, u16 map, u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id  = FNOTE_ID_IAIGIRI+waza;
	wk->map = map;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：地下・化石掘り ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionUGFossilDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_UG_FOSSIL;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：地下・秘密基地 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_ActionUGBaseDataMake( u32 heap )
{
	FNOTE_WK_ACTION * wk = FNOTE_ActionWorkAlloc( heap );
	wk->id = FNOTE_ID_UG_BASE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * 項目・ポケモン用ワーク確保
 *
 * @param	heap	ヒープID
 *
 * @return	確保したワーク
 */
//--------------------------------------------------------------------------------------------
static FNOTE_WK_POKE * FNOTE_PokeWorkAlloc( u32 heap )
{
	FNOTE_WK_POKE * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_POKE) );
	memset( wk, 0, sizeof(FNOTE_WK_POKE) );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ ポケモン：捕獲 ]
 *
 * @param	ptyme	プレイ時間
 * @param	mons	ポケモンID
 * @param	sex		性別
 * @param	time	時間帯
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_PokemonGetDataMake( const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap )
{
	FNOTE_WK_POKE * wk;
	u8	min;
	
	wk = FNOTE_PokeWorkAlloc( heap );
	wk->id   = FNOTE_ID_POKEGET;
	wk->mons = mons;
	wk->sex  = sex;
	wk->time = time;

	min = PLAYTIME_GetMinute( ptime ) / 10;
	if( min == 0 || min == 2 || min == 4 ){
		wk->type = 0;
	}else if( min == 1 || min == 3 ){
		wk->type = 1;
	}else{
		wk->type = 2;
	}

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ ポケモン：倒す ]
 *
 * @param	ptyme	プレイ時間
 * @param	mons	ポケモンID
 * @param	sex		性別
 * @param	time	時間帯
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_PokemonDownDataMake( const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap )
{
	FNOTE_WK_POKE * wk;
	u8	min;
	
	wk = FNOTE_PokeWorkAlloc( heap );
	wk->id   = FNOTE_ID_POKEDOWN;
	wk->mons = mons;
	wk->sex  = sex;
	wk->time = time;

	min = PLAYTIME_GetMinute( ptime ) / 10;
	if( min == 1 || min == 3 || min == 5 ){
		wk->type = 0;
	}else if( min == 2 || min == 4 ){
		wk->type = 1;
	}else{
		wk->type = 2;
	}

	return wk;
}


//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ トレーナー ]
 *
 * @param	map		マップID
 * @param	trainer	トレーナーID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_TrainerDataMake( u16 map, u16 trainer, u32 heap )
{
	FNOTE_WK_TRAINER * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_TRAINER) );
	wk->id   = 1;
	wk->map  = map;
	wk->trid = trainer;
	return wk;
}


//--------------------------------------------------------------------------------------------
/**
 * 項目・通信用ワーク確保
 *
 * @param	heap	ヒープID
 *
 * @return	確保したワーク
 */
//--------------------------------------------------------------------------------------------
static FNOTE_WK_SIO * FNOTE_SioWorkAlloc( u32 heap )
{
	FNOTE_WK_SIO * wk = sys_AllocMemory( heap, sizeof(FNOTE_WK_SIO) );
	memset( wk, 0, sizeof(FNOTE_WK_SIO) );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * 文字列コピー
 *
 * @param	str		コピーする文字列
 * @param	buf		格納先
 * @param	siz		文字数
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_StrCopy( const STRCODE * str, STRCODE * buf, u32 siz )
{
	u32	i;

	for( i=0; i<siz; i++ ){
		buf[i] = EOM_;
	}
	for( i=0; i<siz; i++ ){
		if( str[i] == EOM_ ){ break; }
		buf[i] = str[i];
	}
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：通信対戦・シングル ]
 *
 * @param	name	対戦相手の名前
 * @param	sex		対戦相手の性別
 * @param	result	勝敗
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioSingleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_SINGLE;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：通信対戦・ダブル ]
 *
 * @param	name	対戦相手の名前
 * @param	sex		対戦相手の性別
 * @param	result	勝敗
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioDoubleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_DOUBLE;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：通信対戦・マルチ ]
 *
 * @param	name1	対戦相手１の名前
 * @param	name2	対戦相手２の名前
 * @param	sex1	対戦相手１の性別
 * @param	sex2	対戦相手２の性別
 * @param	result	勝敗
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioMultiBtlDataMake(
		 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_MULTI;
	wk->result = result;
	wk->sex1   = sex1;
	wk->sex2   = sex2;
	FNOTE_StrCopy( name1, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( name2, wk->name2, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：通信対戦・ミックス1vs1 ]
 *
 * @param	name	対戦相手の名前
 * @param	sex		対戦相手の性別
 * @param	result	勝敗
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioMixBtl1DataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_MIX1;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：通信対戦・ミックス2vs2 ]
 *
 * @param	name1	対戦相手１の名前
 * @param	name2	対戦相手２の名前
 * @param	sex1	対戦相手１の性別
 * @param	sex2	対戦相手２の性別
 * @param	result	勝敗
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioMixBtl2DataMake(
		 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_SB_MIX2;
	wk->result = result;
	wk->sex1   = sex1;
	wk->sex2   = sex2;
	FNOTE_StrCopy( name1, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( name2, wk->name2, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・挨拶 ]
 *
 * @param	name	相手の名前
 * @param	sex		相手の性別
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionGreetDataMake( STRCODE * name, u8 sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id   = FNOTE_ID_U_GREETING;
	wk->sex1 = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・交換 ]
 *
 * @param	name		交換相手の名前
 * @param	sex			交換相手の性別
 * @param	nickname	交換できたポケモンのニックネーム
 * @param	poke_sex	交換できたポケモンの性別
 * @param	heap		ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionChangeDataMake(
		STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id       = FNOTE_ID_U_POKECHG;
	wk->sex1     = sex;
	wk->poke_sex = poke_sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( nickname, wk->nickname, BUFLEN_POKEMON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・お絵かき ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionPictureDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_U_PICTURE;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・複数人交換 ]
 *
 * @param	nickname	交換できたポケモンのニックネーム
 * @param	poke_sex	交換できたポケモンの性別
 * @param	heap		ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionMltChgDataMake( STRCODE * nickname, u8 poke_sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id       = FNOTE_ID_U_MLTCHG;
	wk->poke_sex = poke_sex;
	FNOTE_StrCopy( nickname, wk->nickname, BUFLEN_POKEMON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・トランシーバー ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionTransceiverDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_U_TRANSCEIVER;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・対戦 ]
 *
 * @param	name	対戦相手の名前
 * @param	sex		対戦相手の性別
 * @param	result	勝敗
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioUnionBattleDataMake( STRCODE * name, u8 sex, u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_U_BATTLE;
	wk->result = result;
	wk->sex1   = sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：レコードコーナー ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioRecordDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_RECORD;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：コンテスト ]
 *
 * @param	result	順位
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioContestDataMake( u8 result, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id     = FNOTE_ID_CONTEST;
	wk->result = result;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ポルト作成 ]
 *
 * @param	name	相手の名前
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioPorutoDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_PORUTO;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：GTC ]
 *
 * @param	name		交換相手の名前
 * @param	sex			交換相手の性別
 * @param	nickname	交換できたポケモンのニックネーム
 * @param	poke_sex	交換できたポケモンの性別
 * @param	heap		ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioGTCDataMake( STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id       = FNOTE_ID_GTC;
	wk->sex1     = sex;
	wk->poke_sex = poke_sex;
	FNOTE_StrCopy( name, wk->name1, BUFLEN_PERSON_NAME );
	FNOTE_StrCopy( nickname, wk->nickname, BUFLEN_POKEMON_NAME );
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：バトルタワー ]
 *
 * @param	name	相手の名前
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
void * FNOTE_SioBattleTowerDataMake( u32 heap )
{
	FNOTE_WK_SIO * wk = FNOTE_SioWorkAlloc( heap );
	wk->id = FNOTE_ID_BTLTOWER;
	return wk;
}


//============================================================================================
//	データ取得
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 回想データ取得
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 * @param	type	記録タイプ
 * @param	page	取得ページ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataGet( FNOTE_DATA * dat, void * wk, u8 type, u8 page )
{
	switch( type ){
	case FNOTE_TYPE_START:		// 開始
		FNOTE_StartDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_ACTION:		// 行動
		FNOTE_ActionDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_POKEMON:	// ポケモン
		FNOTE_PokemonDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_TRAINER:	// トレーナー
		FNOTE_TrainerDataGet( &dat[page], wk );
		break;

	case FNOTE_TYPE_SIO:		// 通信
		FNOTE_SioDataGet( &dat[page], wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 開始データ取得
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_StartDataGet( FNOTE_DATA * dat, FNOTE_WK_START * wk )
{
	*wk = dat->hed;
}

//--------------------------------------------------------------------------------------------
/**
 * 行動データ取得
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionDataGet( FNOTE_DATA * dat, FNOTE_WK_ACTION * wk )
{
	u32	i;

	for( i=0; i<FNOTE_ACTION_MAX; i++ ){
		memset( &wk[i], 0, sizeof(FNOTE_WK_ACTION) );
		switch( dat->action[i] & 0x3f ){
		case FNOTE_ID_MYHOUSE:			// 行動：自宅
		case FNOTE_ID_LABO:				// 行動：研究所
		case FNOTE_ID_POKECENTER:		// 行動：ポケモンセンター
		case FNOTE_ID_FDSHOP_BUY:		// 行動：ショップ・買う
		case FNOTE_ID_FDSHOP_BUY2:		// 行動：ショップ・買う（複数）
		case FNOTE_ID_FDSHOP_SALE:		// 行動：ショップ・売る
		case FNOTE_ID_FDSHOP_SALE2:		// 行動：ショップ・売る（複数）
		case FNOTE_ID_FDSHOP_TRADE:		// 行動：ショップ・売買
		case FNOTE_ID_GAMECORNER:		// 行動：ゲームコーナー
		case FNOTE_ID_SAFARIZONE:		// 行動：サファリゾーン
		case FNOTE_ID_UG_FOSSIL:		// 行動：地下・化石掘り
		case FNOTE_ID_UG_BASE:			// 行動：地下・秘密基地
			FNOTE_ActionIDDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_GYMBEFORE:		// 行動：ジム（リーダーを倒す前）
		case FNOTE_ID_GYMAFTER:			// 行動：ジム（リーダーを倒した後）
		case FNOTE_ID_SITENNOU:			// 行動：四天王
		case FNOTE_ID_CHAMPION:			// 行動：チャンピオン
			FNOTE_ActionTrainerDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_CITY:				// 行動：街
		case FNOTE_ID_DUNGEON:			// 行動：ダンジョン
		case FNOTE_ID_BUILD:			// 行動：建物
			FNOTE_ActionMapDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_ITEMGET:			// 行動：アイテム取得
			FNOTE_ActionItemDataGet( dat->action[i], &wk[i] );
			break;

		case FNOTE_ID_IAIGIRI:			// 行動：技・いあいぎり
		case FNOTE_ID_SORAWOTOBU:		// 行動：技・そらをとぶ
		case FNOTE_ID_NAMINORI:			// 行動：技・なみのり
		case FNOTE_ID_KAIRIKI:			// 行動：技・かいりき
		case FNOTE_ID_FLASH:			// 行動：技・フラッシュ
		case FNOTE_ID_KIRIBARAI:		// 行動：技・きりばらい
		case FNOTE_ID_IWAKUDAKI:		// 行動：技・いわくだき
		case FNOTE_ID_TAKINOBORI:		// 行動：技・たきのぼり
		case FNOTE_ID_ROCKCLIMB:		// 行動：技・ロッククライム
		case FNOTE_ID_ANAWOHORU:		// 行動：技・あなをほる
		case FNOTE_ID_AMAIKAORI:		// 行動：技・あまいかおり
		case FNOTE_ID_TELEPORT:			// 行動：技・テレポート
		case FNOTE_ID_TAMAGOUMI:		// 行動：技・タマゴうみ
		case FNOTE_ID_MIRUKUNOMI:		// 行動：技・ミルクのみ
			FNOTE_ActionSkillDataGet( dat->action[i], &wk[i] );
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンデータ取得
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_PokemonDataGet( FNOTE_DATA * dat, FNOTE_WK_POKE * wk )
{
	*wk = dat->pokemon;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーデータ取得
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_TrainerDataGet( FNOTE_DATA * dat, FNOTE_WK_TRAINER * wk )
{
	*wk = dat->trainer;
}

//--------------------------------------------------------------------------------------------
/**
 * 通信データ取得
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioDataGet( FNOTE_DATA * dat, FNOTE_WK_SIO * wk )
{
	u32	i;

	for( i=0; i<FNOTE_SIO_MAX; i++ ){
		memset( &wk[i], 0, sizeof(FNOTE_WK_SIO) );
		switch( dat->sio[i][0] ){
		case FNOTE_ID_SB_SINGLE:		// 通信：通信対戦・シングル
		case FNOTE_ID_SB_DOUBLE:		// 通信：通信対戦・ダブル
		case FNOTE_ID_SB_MULTI:			// 通信：通信対戦・マルチ
		case FNOTE_ID_SB_MIX1:			// 通信：通信対戦・ミックス1vs1
		case FNOTE_ID_SB_MIX2:			// 通信：通信対戦・ミックス2vs2
		case FNOTE_ID_U_BATTLE:			// 通信：ユニオンルーム・対戦
			FNOTE_SioBattleDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_U_GREETING:		// 通信：ユニオンルーム・挨拶
			FNOTE_SioUnionGreetDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_U_POKECHG:		// 通信：ユニオンルーム・交換
		case FNOTE_ID_U_MLTCHG:			// 通信：ユニオンルーム・複数人交換
		case FNOTE_ID_GTC:				// 通信：GTC
			FNOTE_SioPokeChgDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_U_PICTURE:		// 通信：ユニオンルーム・お絵かき
		case FNOTE_ID_U_TRANSCEIVER:	// 通信：ユニオンルーム・トランシーバー
		case FNOTE_ID_RECORD:			// 通信：レコードコーナー
		case FNOTE_ID_PORUTO:			// 通信：ポルト作成
		case FNOTE_ID_BTLTOWER:			// 通信：バトルタワー
			FNOTE_SioIDDataGet( &dat->sio[i][0], &wk[i] );
			break;

		case FNOTE_ID_CONTEST:			// 通信：コンテスト
			FNOTE_SioContestDataGet( &dat->sio[i][0], &wk[i] );
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 行動：IDのみのもの ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionIDDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = ( wk->id & 0x3f );
	wk->id = ( dat & 0x3f );
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 行動：ジムリーダー、四天王、チャンピオン ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionTrainerDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->map << 16) | ((wk->trainer & 0x3ff) << 6) | (wk->id & 0x3f);
	wk->id      = ( dat & 0x3f );
	wk->trainer = ( dat >> 6 ) & 0x3ff;
	wk->map     = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 行動：街、ダンジョン、建物など ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionMapDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->map << 16) | (wk->id & 0x3f);
	wk->id  = ( dat & 0x3f );
	wk->map = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 行動：アイテム取得 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionItemDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->item << 16) | (wk->id & 0x3f);
	wk->id   = ( dat & 0x3f );
	wk->item = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 行動：技 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_ActionSkillDataGet( u32 dat, FNOTE_WK_ACTION * wk )
{
//	*dat = (wk->map << 16) | (wk->id & 0x3f);
	wk->id  = ( dat & 0x3f );
	wk->map = ( dat >> 16 ) & 0xffff;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 通信：対戦 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioBattleDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = (wk->result<<2) | (wk->sex1<<1) | (wk->sex2);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->name2, (STRCODE *)&dat[18], 8 );
*/
	wk->id       = dat[0];
	wk->result   = ( dat[1] >> 2 ) & 0x1f;
	wk->sex1     = ( dat[1] >> 1 ) & 1;
	wk->sex2     = dat[1] & 1;
	FNOTE_StrCopy( (STRCODE *)&dat[2], wk->name1, 8 );
	FNOTE_StrCopy( (STRCODE *)&dat[18], wk->name2, 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 通信：ユニオンルーム・挨拶 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioUnionGreetDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = wk->sex1;
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
*/
	wk->id   = dat[0];
	wk->sex1 = dat[1];
	FNOTE_StrCopy( (STRCODE *)&dat[2], wk->name1, 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 通信：交換 ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioPokeChgDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = (wk->sex1 << 2) | (wk->poke_sex);
	FNOTE_StrCopy( wk->name1, (STRCODE *)&dat[2], 8 );
	FNOTE_StrCopy( wk->nickname, (STRCODE *)&dat[18], 12 );
*/
	wk->id       = dat[0];
	wk->sex1     = ( dat[1] >> 2 ) & 1;
	wk->poke_sex = dat[1] & 3;
	FNOTE_StrCopy( (STRCODE *)&dat[2], wk->name1, 8 );
	FNOTE_StrCopy( (STRCODE *)&dat[18], wk->nickname, 12 );
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 通信：バトルタワー ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioIDDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
//	dat[0] = wk->id;
	wk->id = dat[0];
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得 [ 通信：コンテスト ]
 *
 * @param	dat		セーブデータ
 * @param	wk		取得場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_SioContestDataGet( u8 * dat, FNOTE_WK_SIO * wk )
{
/*
	dat[0] = wk->id;
	dat[1] = wk->result;
*/
	wk->id     = dat[0];
	wk->result = dat[1];
}


//--------------------------------------------------------------------------------------------
/**
 * データ作成/セーブ [ 行動：自宅、研究所、建物、ダンジョンから出た ]
 *
 * @param	my		プレーヤーデータ
 * @param	dat		冒険ノートのセーブデータ
 * @param	now		現在のマップ
 * @param	before	前にいたマップ
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataMakeSaveMapChg( MYSTATUS * my, FNOTE_DATA * dat, u32 now, u32 before, u32 heap )
{
	void * buf;
	u32	i;

	buf = NULL;

	// ダンジョンから
	if( ZoneData_IsDungeon( before ) == TRUE ){
		// 屋外へ
		if( ZoneData_IsOutDoor( now ) == TRUE ){
//			buf = FNOTE_ActionDungeonDataMake( (u16)before, heap );
			buf = FNOTE_ActionDungeonDataMake( (u16)ZoneData_GetPlaceNameID(before), heap );
		}
	// 屋内から
	}else if( ZoneData_IsRoom( before ) == TRUE ){
		// 屋外へ
		if( ZoneData_IsOutDoor( now ) == TRUE ){
			// 自宅
			if( before == ZONE_ID_T01R0201 ){
				buf = FNOTE_ActionHouseDataMake( heap );
			// 研究所
			}else if( before == ZONE_ID_T02R0101 ){
				buf = FNOTE_ActionLaboDataMake( heap );
			// その他
			}else{
				u32	name = ZoneData_GetPlaceNameID( before );
				for( i=0; i<NELEMS(BuildNameTable); i++ ){
					if( name != BuildNameTable[i].name ){ continue; }
//					buf = FNOTE_ActionBuildDataMake( (u16)before, heap );
					buf = FNOTE_ActionBuildDataMake( (u16)name, heap );
				}
			}
		}
	// 屋外から
	}else if( ZoneData_IsOutDoor( before ) == TRUE ){
		// 屋内へ
		if( ZoneData_IsRoom( now ) == TRUE ){
			// ジム
			u8	gym = GymCheck( my, now );
			if( gym != 0xff ){
				buf = FNOTE_ActionGymBeforeDataMake( gym, heap );
			}
		}
	}

	if( buf != NULL ){
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 特殊な建物の表示タイプ取得
 *
 * @param	name	名前ID
 *
 * @return	表示タイプ
 */
//--------------------------------------------------------------------------------------------
u32 FNOTE_ExBuildPutTypeGet( u32 name )
{
	u32	i;

	for( i=0; i<NELEMS(BuildNameTable); i++ ){
		if( name != BuildNameTable[i].name ){ continue; }
		return BuildNameTable[i].type;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ジムチェック
 *
 * @param	my			プレーヤーデータ
 * @param	zone_id		ゾーンID
 *
 * @retval	"0xff != ジムID"
 * @retval	"0xff = ジム以外"
 */
//--------------------------------------------------------------------------------------------
static u8 GymCheck( MYSTATUS * my, u32 zone_id )
{
	u8	i;

	for( i=0; i<NELEMS(GymTbl); i++ ){
		if( GymTbl[i].zone == zone_id ){
			if( MyStatus_GetBadgeFlag( my, GymTbl[i].badge ) == FALSE ){
				return i;
			}
			break;
		}
	}
	return 0xff;
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成/セーブ [ 行動：街に到着 ]
 *
 * @param	dat		セーブデータ
 * @param	map		現在のマップ
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataMakeSaveCity( FNOTE_DATA * dat, u32 map, u32 heap )
{
	void * buf = FNOTE_ActionCityDataMake( (u16)map, heap );
	FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
}

//--------------------------------------------------------------------------------------------
/**
 * データ作成/セーブ [ 行動：ジムリーダー、チャンピオン、四天王 & トレーナー：トレーナー ]
 *
 * @param	dat			冒険ノートのセーブデータ
 * @param	map			ゾーンID
 * @param	trainer		トレーナーID
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FNOTE_DataMakeSaveTrainer( FNOTE_DATA * dat, u16 map, u16 trainer, u32 heap )
{
	void * buf;
	u8	ret;
	
	ret = TrainerCheck( trainer );

	// ジムリーダー
	if( ret < 8 ){
		buf = FNOTE_ActionGymAfterDataMake( ret, trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	// 四天王
	}else if( ret == 8 ){
		buf = FNOTE_ActionSitenouDataMake( trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	// チャンピオン
	}else if( ret == 9 ){
		buf = FNOTE_ActionChampionDataMake( trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_ACTION );
	// 普通のトレーナー
	}else{
		buf = FNOTE_TrainerDataMake( map, trainer, heap );
		FNOTE_DataSave( dat, buf, FNOTE_TYPE_TRAINER );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナータイプを取得
 *
 * @param	tr		トレーナーID
 *
 * @retval	"8 > ジムリーダー
 * @retval	"8 = 四天王"
 * @retval	"9 = チャンピオン"
 * @retval	"10 = 普通のトレーナー"
 */
//--------------------------------------------------------------------------------------------
static u8 TrainerCheck( u32 tr )
{
	u8	i;

	// ジムリーダー
	for( i=0; i<NELEMS(GymTbl); i++ ){
		if( GymTbl[i].tr == tr ){
			return i;
		}
	}
	// 四天王
	if( tr == BIGFOUR1_01 || tr == BIGFOUR2_01 || tr == BIGFOUR3_01 || tr == BIGFOUR4_01 ){
		return 8;
	}
	// チャンピオン
	if( tr == CHAMPION_01 ){
		return 9;
	}
	return 10;
}

