//============================================================================================
/**
 * @file	fnote_mem.h
 * @brief	冒険ノート　データ管理処理
 * @author	Hiroyuki Nakamura
 * @date	2006.03.06
 */
//============================================================================================
#ifndef F_NOTE_MEM_H
#define F_NOTE_MEM_H
#undef GLOBAL
#ifdef F_NOTE_MEM_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
// 項目
#define	FNOTE_TYPE_START		( 0 )	// 開始
#define	FNOTE_TYPE_ACTION		( 1 )	// 行動
#define	FNOTE_TYPE_POKEMON		( 2 )	// ポケモン
#define	FNOTE_TYPE_TRAINER		( 3 )	// トレーナー
#define	FNOTE_TYPE_SIO			( 4 )	// 通信

// データID
#define	FNOTE_ID_MYHOUSE		( 1 )		// 行動：自宅
#define	FNOTE_ID_LABO			( 2 )		// 行動：研究所
#define	FNOTE_ID_POKECENTER		( 3 )		// 行動：ポケモンセンター
#define	FNOTE_ID_FDSHOP_BUY		( 4 )		// 行動：ショップ・買う
#define	FNOTE_ID_FDSHOP_BUY2	( 5 )		// 行動：ショップ・買う（複数）
#define	FNOTE_ID_FDSHOP_SALE	( 6 )		// 行動：ショップ・売る
#define	FNOTE_ID_FDSHOP_SALE2	( 7 )		// 行動：ショップ・売る（複数）
#define	FNOTE_ID_FDSHOP_TRADE	( 8 )		// 行動：ショップ・売買
#define	FNOTE_ID_GYMBEFORE		( 9 )		// 行動：ジム（リーダーを倒す前）
#define	FNOTE_ID_GYMAFTER		( 10 )		// 行動：ジム（リーダーを倒した後）
#define	FNOTE_ID_SITENNOU		( 11 )		// 行動：四天王
#define	FNOTE_ID_CHAMPION		( 12 )		// 行動：チャンピオン
#define	FNOTE_ID_CITY			( 13 )		// 行動：街
#define	FNOTE_ID_DUNGEON		( 14 )		// 行動：ダンジョン
#define	FNOTE_ID_BUILD			( 15 )		// 行動：建物
#define	FNOTE_ID_GAMECORNER		( 16 )		// 行動：ゲームコーナー
#define	FNOTE_ID_SAFARIZONE		( 17 )		// 行動：サファリゾーン
#define	FNOTE_ID_ITEMGET		( 18 )		// 行動：アイテム取得
/** ポケモンリストと同じ並びにすること！ **/
#define	FNOTE_ID_IAIGIRI		( 19 )		// 行動：技・いあいぎり
#define	FNOTE_ID_SORAWOTOBU		( 20 )		// 行動：技・そらをとぶ
#define	FNOTE_ID_NAMINORI		( 21 )		// 行動：技・なみのり
#define	FNOTE_ID_KAIRIKI		( 22 )		// 行動：技・かいりき
#define	FNOTE_ID_KIRIBARAI		( 23 )		// 行動：技・きりばらい
#define	FNOTE_ID_IWAKUDAKI		( 24 )		// 行動：技・いわくだき
#define	FNOTE_ID_TAKINOBORI		( 25 )		// 行動：技・たきのぼり
#define	FNOTE_ID_ROCKCLIMB		( 26 )		// 行動：技・ロッククライム
#define	FNOTE_ID_FLASH			( 27 )		// 行動：技・フラッシュ
#define	FNOTE_ID_TELEPORT		( 28 )		// 行動：技・テレポート
#define	FNOTE_ID_ANAWOHORU		( 29 )		// 行動：技・あなをほる
#define	FNOTE_ID_AMAIKAORI		( 30 )		// 行動：技・あまいかおり
#define	FNOTE_ID_OSYABERI		( 31 )		// 行動：技・おしゃべり（ダミー）
#define	FNOTE_ID_MIRUKUNOMI		( 32 )		// 行動：技・ミルクのみ
#define	FNOTE_ID_TAMAGOUMI		( 33 )		// 行動：技・タマゴうみ

#define	FNOTE_ID_UG_FOSSIL		( 34 )		// 行動：地下・化石掘り
#define	FNOTE_ID_UG_BASE		( 35 )		// 行動：地下・秘密基地

#define	FNOTE_ID_POKEGET		( 1 )		// ポケモン：捕獲
#define	FNOTE_ID_POKEDOWN		( 2 )		// ポケモン：倒した

#define	FNOTE_ID_SB_SINGLE		( 1 )		// 通信：通信対戦・シングル
#define	FNOTE_ID_SB_DOUBLE		( 2 )		// 通信：通信対戦・ダブル
#define	FNOTE_ID_SB_MULTI		( 3 )		// 通信：通信対戦・マルチ
#define	FNOTE_ID_SB_MIX1		( 4 )		// 通信：通信対戦・ミックス1vs1
#define	FNOTE_ID_SB_MIX2		( 5 )		// 通信：通信対戦・ミックス2vs2
#define	FNOTE_ID_U_GREETING		( 6 )		// 通信：ユニオンルーム・挨拶
#define	FNOTE_ID_U_POKECHG		( 7 )		// 通信：ユニオンルーム・交換
#define	FNOTE_ID_U_PICTURE		( 8 )		// 通信：ユニオンルーム・お絵かき
#define	FNOTE_ID_U_MLTCHG		( 9 )		// 通信：ユニオンルーム・複数人交換
#define	FNOTE_ID_U_TRANSCEIVER	( 10 )		// 通信：ユニオンルーム・トランシーバー
#define	FNOTE_ID_U_BATTLE		( 11 )		// 通信：ユニオンルーム・対戦
#define	FNOTE_ID_RECORD			( 12 )		// 通信：レコードコーナー
#define	FNOTE_ID_CONTEST		( 13 )		// 通信：コンテスト
#define	FNOTE_ID_PORUTO			( 14 )		// 通信：ポルト作成
#define	FNOTE_ID_GTC			( 15 )		// 通信：GTC
#define	FNOTE_ID_BTLTOWER		( 16 )		// 通信：バトルタワー

// 勝敗
#define	FNOTE_RESULT_WIN		( 0 )	// 勝ち
#define	FNOTE_RESULT_LOSE		( 1 )	// 負け
#define	FNOTE_RESULT_DRAW		( 2 )	// 引き分け

// 技インデックス
#define	FNOTE_IAIGIRI			( FNOTE_ID_IAIGIRI-FNOTE_ID_IAIGIRI )		// いあいぎり
#define	FNOTE_SORAWOTOBU		( FNOTE_ID_SORAWOTOBU-FNOTE_ID_IAIGIRI )	// そらをとぶ
#define	FNOTE_NAMINORI			( FNOTE_ID_NAMINORI-FNOTE_ID_IAIGIRI )		// なみのり
#define	FNOTE_KAIRIKI			( FNOTE_ID_KAIRIKI-FNOTE_ID_IAIGIRI )		// かいりき
#define	FNOTE_KIRIBARAI			( FNOTE_ID_KIRIBARAI-FNOTE_ID_IAIGIRI )		// きりばらい
#define	FNOTE_IWAKUDAKI			( FNOTE_ID_IWAKUDAKI-FNOTE_ID_IAIGIRI )		// いわくだき
#define	FNOTE_TAKINOBORI		( FNOTE_ID_TAKINOBORI-FNOTE_ID_IAIGIRI )	// たきのぼり
#define	FNOTE_ROCKCLIMB			( FNOTE_ID_ROCKCLIMB-FNOTE_ID_IAIGIRI )		// ロッククライム
#define	FNOTE_FLASH				( FNOTE_ID_FLASH-FNOTE_ID_IAIGIRI )			// フラッシュ
#define	FNOTE_TELEPORT			( FNOTE_ID_TELEPORT-FNOTE_ID_IAIGIRI )		// テレポート
#define	FNOTE_ANAWOHORU			( FNOTE_ID_ANAWOHORU-FNOTE_ID_IAIGIRI )		// あなをほる
#define	FNOTE_AMAIKAORI			( FNOTE_ID_AMAIKAORI-FNOTE_ID_IAIGIRI )		// あまいかおり
#define	FNOTE_OSYABERI			( FNOTE_ID_OSYABERI-FNOTE_ID_IAIGIRI )		// おしゃべり（ダミー）
#define	FNOTE_MIRUKUNOMI		( FNOTE_ID_MIRUKUNOMI-FNOTE_ID_IAIGIRI )	// ミルクのみ
#define	FNOTE_TAMAGOUMI			( FNOTE_ID_TAMAGOUMI-FNOTE_ID_IAIGIRI )		// タマゴうみ


#ifndef	__ASM_NO_DEF_	// ↓これ以降は、アセンブラでは無視
#include "system/savedata_def.h"
#include "system/buflen.h"
#include "savedata/mystatus.h"
#include "savedata/playtime.h"


typedef struct _FNOTE_DATA FNOTE_DATA;

// 開始データ
typedef struct {
	u32	year:7;		// 年
	u32	month:4;	// 月
	u32	week:3;		// 曜日
	u32	day:5;		// 日
	u32	start:13;	// 開始位置
}FNOTE_WK_START;

// 行動ワーク
typedef struct {
	u8	id;			// 回想ID
	u16	map;		// マップID
	u16	trainer;	// トレーナーID
	u16	item;		// アイテムID
}FNOTE_WK_ACTION;

// ポケモンワーク
typedef struct {
	u8	id;			// 回想ID
	u8	type:2;		// 表示タイプ
	u8	time:4;		// 時間
	u8	sex:2;		// 性別
	u16	mons;		// ポケモンID
}FNOTE_WK_POKE;

// トレーナーワーク
typedef struct {
	u16	id:1;		// 回想ID
	u16	trid:15;	// トレーナーID
	u16	map;		// マップID
}FNOTE_WK_TRAINER;

// 通信ワーク
typedef struct {
	u8	id;									// 回想ID
	u8	result:4;							// 勝敗
	u8	sex1:1;								// 通信相手１の性別
	u8	sex2:1;								// 通信相手２の性別
	u8	poke_sex:2;							// ポケモンの性別
	u16	name1[BUFLEN_PERSON_NAME];			// 通信相手１の名前
	u16	name2[BUFLEN_PERSON_NAME];			// 通信相手２の名前
	u16	nickname[BUFLEN_POKEMON_NAME];		// ポケモンのニックネーム
}FNOTE_WK_SIO;


#define	FNOTE_PAGE_MAX		( 10 )		///< 冒険ノートページMAX
#define	FNOTE_ACTION_MAX	( 4 )		///< 冒険ノート行動ワーク数
#define	FNOTE_SIO_MAX		( 2 )		///< 冒険ノート通信ワーク数



//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 冒険ノート用ワークのサイズ取得
 *
 * @param	none
 *
 * @return	ワークサイズ
 */
//--------------------------------------------------------------------------------------------
GLOBAL int FNOTE_GetWorkSize(void);

//--------------------------------------------------------------------------------------------
/**
 * 冒険ノート用ワーク初期化（全体）
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FNOTE_InitAll( FNOTE_DATA * dat );

//--------------------------------------------------------------------------------------------
/**
 * セーブデータから冒険ノートのポインタを取得
 *
 * @param	sv		セーブデータ
 *
 * @return	冒険ノートデータ
 */
//--------------------------------------------------------------------------------------------
GLOBAL FNOTE_DATA * SaveData_GetFNote( SAVEDATA * sv );

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
GLOBAL FNOTE_DATA * FNOTE_SavePageGet( FNOTE_DATA * dat, BOOL flg );

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
GLOBAL BOOL FNOTE_GameStartOpenCheck( FNOTE_DATA * dat, BOOL flg );

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
GLOBAL void FNOTE_DataSave( FNOTE_DATA * dat, void * wk, u8 type );

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
GLOBAL void * FNOTE_StartDataMake( u16 start, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：自宅 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionHouseDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：研究所 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionLaboDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ポケモンセンター ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_PokemonCenterDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・買う ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopBuyDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・買う（複数） ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopBuy2DataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・売る ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopSaleDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・売る（複数） ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopSale2DataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ショップ・売買 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionShopTradeDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ジム（リーダーを倒す前） ]
 *
 * @param	map		マップID
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionGymBeforeDataMake( u16 map, u32 heap );

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
GLOBAL void * FNOTE_ActionGymAfterDataMake( u16 map, u16 trainer, u32 heap );

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
GLOBAL void * FNOTE_ActionSitenouDataMake( u16 trainer, u32 heap );

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
GLOBAL void * FNOTE_ActionChampionDataMake( u16 trainer, u32 heap );

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
GLOBAL void * FNOTE_ActionCityDataMake( u16 map, u32 heap );

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
GLOBAL void * FNOTE_ActionDungeonDataMake( u16 map, u32 heap );

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
GLOBAL void * FNOTE_ActionBuildDataMake( u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：ゲームコーナー ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionGameCornerDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：サファリゾーン ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionSafariDataMake( u32 heap );

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
GLOBAL void * FNOTE_ActionItemDataMake( u16 item, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：技 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionSkillDataMake( u8 waza, u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：地下・化石掘り ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionUGFossilDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 行動：地下・秘密基地 ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_ActionUGBaseDataMake( u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ ポケモン：捕獲 ]
 *
 * @param	ptime	プレイ時間
 * @param	mons	ポケモンID
 * @param	sex		性別
 * @param	time	時間帯
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_PokemonGetDataMake(
					const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap );

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
GLOBAL void * FNOTE_PokemonDownDataMake(
					const PLAYTIME * ptime, u16 mons, u8 sex, u8 time, u32 heap );

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
GLOBAL void * FNOTE_TrainerDataMake( u16 map, u16 trainer, u32 heap );

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
GLOBAL void * FNOTE_SioSingleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

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
GLOBAL void * FNOTE_SioDoubleBtlDataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

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
GLOBAL void * FNOTE_SioMultiBtlDataMake(
				 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap );

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
GLOBAL void * FNOTE_SioMixBtl1DataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

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
GLOBAL void * FNOTE_SioMixBtl2DataMake(
				 STRCODE * name1, STRCODE * name2, u8 sex1, u8 sex2, u8 result, u32 heap );

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
GLOBAL void * FNOTE_SioUnionGreetDataMake( STRCODE * name, u8 sex, u32 heap );

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
GLOBAL void * FNOTE_SioUnionChangeDataMake(
				STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・お絵かき ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionPictureDataMake( u32 heap );

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
GLOBAL void * FNOTE_SioUnionMltChgDataMake( STRCODE * nickname, u8 poke_sex, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：ユニオンルーム・トランシーバー ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioUnionTransceiverDataMake( u32 heap );

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
GLOBAL void * FNOTE_SioUnionBattleDataMake( STRCODE * name, u8 sex, u8 result, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * データ作成 [ 通信：レコードコーナー ]
 *
 * @param	heap	ヒープID
 *
 * @return	作成したワーク
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * FNOTE_SioRecordDataMake( u32 heap );

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
GLOBAL void * FNOTE_SioContestDataMake( u8 result, u32 heap );

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
GLOBAL void * FNOTE_SioPorutoDataMake( u32 heap );

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
GLOBAL void * FNOTE_SioGTCDataMake(
				STRCODE * name, u8 sex, STRCODE * nickname, u8 poke_sex, u32 heap );

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
GLOBAL void * FNOTE_SioBattleTowerDataMake( u32 heap );

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
GLOBAL void FNOTE_DataGet( FNOTE_DATA * dat, void * wk, u8 type, u8 page );


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
GLOBAL void FNOTE_DataMakeSaveMapChg(
				MYSTATUS * my, FNOTE_DATA * dat, u32 now, u32 before, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * 特殊な建物の表示タイプ取得
 *
 * @param	name	名前ID
 *
 * @return	表示タイプ
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 FNOTE_ExBuildPutTypeGet( u32 name );

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
GLOBAL void FNOTE_DataMakeSaveCity( FNOTE_DATA * dat, u32 map, u32 heap );

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
GLOBAL void FNOTE_DataMakeSaveTrainer( FNOTE_DATA * dat, u16 map, u16 trainer, u32 heap );


#endif	__ASM_NO_DEF_

#undef GLOBAL
#endif	/* F_NOTE_MEM_H */
