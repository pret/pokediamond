//============================================================================================
/**
 * @file	fushigi_data.h
 * @date	2006.04.28
 * @author	tamada / mitsuhara
 * @brief	ふしぎ通信用セーブデータ用ヘッダ
 */
//============================================================================================

#ifndef	__FUSHIGI_DATA_H__
#define	__FUSHIGI_DATA_H__

#include "common.h"
#include "savedata/savedata_def.h"
#include "savedata/regulation.h"
#include "poketool/poke_tool.h"

//============================================================================================
//
//			定義
//
//============================================================================================
//------------------------------------------------------------------
///		贈り物データの大きさ
//------------------------------------------------------------------
#define	GIFT_DATA_SIZE	256		// 配達員１つのサイズ

//------------------------------------------------------------------
///		贈り物データの個数
//------------------------------------------------------------------
#define GIFT_DELIVERY_MAX	8	// 配達員８つ
#define GIFT_CARD_MAX		3	// カードデータ３つ
#define	GIFT_DATA_MAX		8	//カードなし5件＋カードあり3件で8件分

//------------------------------------------------------------------
///		カード関係のサイズ定義
//------------------------------------------------------------------
#define GIFT_DATA_CARD_TITLE_MAX	36
#define GIFT_DATA_CARD_TEXT_MAX		250
#define GIFT_DATA_SCRIPT_MAX		(256+1024)


//------------------------------------------------------------------
///		贈り物データ構造体
//------------------------------------------------------------------
#define MYSTERYGIFT_TYPE_NONE		0	// 何も無い
#define MYSTERYGIFT_TYPE_POKEMON	1	// ポケモン
#define MYSTERYGIFT_TYPE_POKEEGG	2	// タマゴ
#define MYSTERYGIFT_TYPE_ITEM		3	// どうぐ
#define MYSTERYGIFT_TYPE_RULE		4	// ルール
#define MYSTERYGIFT_TYPE_GOODS		5	// グッズ
#define MYSTERYGIFT_TYPE_ACCESSORY	6	// アクセサリ
#define MYSTERYGIFT_TYPE_RANGEREGG	7	// マナフィーのタマゴ
#define MYSTERYGIFT_TYPE_MEMBERSCARD	8	// メンバーズカード
#define MYSTERYGIFT_TYPE_LETTER		9	// オーキドのてがみ
#define MYSTERYGIFT_TYPE_WHISTLE	10	// てんかいのふえ
#define MYSTERYGIFT_TYPE_POKETCH	11	// ポケッチ
#define MYSTERYGIFT_TYPE_CLEAR		255	// ふしぎ領域の強制クリア

#define MYSTERYGIFT_ACCTYPE_SEAL   1  // アクセサリーのシール
#define MYSTERYGIFT_ACCTYPE_CLIP   2  // アクセサリーのクリップ
#define MYSTERYGIFT_ACCTYPE_BG   3  // アクセサリーの背景

#define MYSTERYPOKE_PARENTNAME_THROW  0  // 親の名前をそのまま
#define MYSTERYPOKE_PARENTNAME_MY   1  // 親名を自分の名前に変える


//------------------------------------------------------------------
///		確定しているイベント番号
//------------------------------------------------------------------
#define MYSTERYGIFT_MANAFIEGG		1	// マナフィのたまご



// サイズ固定用構造体
typedef struct {
  u8 data[256];
} GIFT_PRESENT_ALL;

// ポケモン
typedef struct {
  u32 parentType;
  u8 data[236];		// sizeof(POKEMON_PARAM)	#####
  u8 ribbon[10];	// ribbon data
  u8 dummy[6];
} GIFT_PRESENT_POKEMON;

// タマゴ
typedef struct {
  u32 parentType;
  u8 data[236];		// sizeof(POKEMON_PARAM)	#####
  u8 ribbon[10];	// ribbon data
  u8 dummy[6];
} GIFT_PRESENT_POKEEGG;

// どうぐ
typedef struct {
  int itemNo;
} GIFT_PRESENT_ITEM;

// グッズ
typedef struct {
  int goodsNo;
} GIFT_PRESENT_GOODS;

// ルール(レギュレーション)
typedef struct {
  REGULATION regulation;
} GIFT_PRESENT_RULE;

// アクセサリ
typedef struct {
  int accType;
  int accNo;
} GIFT_PRESENT_ACCESSORY;

// マナフィーのタマゴ
typedef struct {
  int dummy;
} GIFT_PRESENT_RANGEREGG;

// メンバーズカード
typedef struct {
  int itemNo;
} GIFT_PRESENT_MEMBERSCARD;

// オーキドのてがみ
typedef struct {
  int itemNo;
} GIFT_PRESENT_LETTER;

// てんかいのふえ
typedef struct {
  int itemNo;
} GIFT_PRESENT_WHISTLE;

// ポケッチ
typedef struct {
  int id;
} GIFT_PRESENT_POKETCH;

// ふしぎなおくりもの強制クリア
typedef struct {
  int dummy;
} GIFT_PRESENT_REMOVE;

typedef union {
  GIFT_PRESENT_ALL 		all;
  GIFT_PRESENT_POKEMON		pokemon;
  GIFT_PRESENT_POKEEGG		egg;
  GIFT_PRESENT_ITEM		item;
  GIFT_PRESENT_GOODS		goods;
  GIFT_PRESENT_RULE		rule;
  GIFT_PRESENT_ACCESSORY	accessory;
  GIFT_PRESENT_RANGEREGG	rangeregg;
  GIFT_PRESENT_MEMBERSCARD	memberscard;
  GIFT_PRESENT_LETTER		letter;
  GIFT_PRESENT_WHISTLE		whistle;
  GIFT_PRESENT_POKETCH		poketch;
  GIFT_PRESENT_REMOVE		remove;
} GIFT_PRESENT;



#define MYSTERYGIFT_DELIVERY	0
#define MYSTERYGIFT_CARD	1

#define MYSTERYGIFT_POKEICON	3

// ふしぎなおくりもの　ビーコンデータ
typedef struct {
  STRCODE event_name[GIFT_DATA_CARD_TITLE_MAX];	// イベントタイトル
  u32 version;					// 対象バージョン(０の場合は制限無しで配布)
  u16 event_id;					// イベントＩＤ(最大2048件まで)
  u8 only_one_flag: 1;				// １度だけ受信フラグ(0..何度でも受信可能 1..１回のみ)
  u8 access_point: 1;				// アクセスポイント(もしかして必要なくなった？)
  u8 have_card: 1;				// カード情報を含んでいるか(0..含んでいない  1..含んでる)
  u8 delivery_flag: 1;				// 配達員から受け取るものを含んでいるか
  u8 re_deal_flag: 1;				// 孫配布する事が可能か？(0..出来ない 1..出来る)
  u8 groundchild_flag: 1;			// 孫配布フラグ(0..違う 1..孫配布)
  u8 dummy: 2;
} GIFT_BEACON;

// 配達員(最大８つ)
typedef struct {
  u16 gift_type;
  u16 link : 2;					// カードへのリンク(0: リンク無し　1 .. 3:リンク)
  u16 dummy : 14;
  GIFT_PRESENT data;
} GIFT_DELIVERY;


// カード情報(最大３つ)
typedef struct {
  u16 gift_type;
  u16 dummy;					// 配達員へのリンク
  GIFT_PRESENT data;

  GIFT_BEACON beacon;				// ビーコン情報と同等の情報を持つ

  STRCODE event_text[GIFT_DATA_CARD_TEXT_MAX];	// 説明テキスト
  u8 re_deal_count;				// 再配布の回数(0～254、255は無制限)
  u16 pokemon_icon[MYSTERYGIFT_POKEICON];	// ポケモンアイコン３つ分

  // ↑配布するのはここまで
  // ↓この下はフラッシュにセーブする時のみ必要なデータ
  
  u8 re_dealed_count;				// 配布した回数
  s32 recv_date;				// 受信した時間
  
} GIFT_CARD;


typedef union {
  GIFT_DELIVERY deli;
  GIFT_CARD card;
} GIFT_DATA;


// 通信する際のパッケージ定義
// beacon.have_card == TRUE ならば data = card;
//                     FALSE ならば data = deli;
typedef struct {
  GIFT_BEACON beacon;
  GIFT_DATA data;
} GIFT_COMM_PACK;


//------------------------------------------------------------------
/**
 * @brief	ふしぎセーブデータへの不完全型定義
 */
//------------------------------------------------------------------
typedef struct FUSHIGI_DATA FUSHIGI_DATA;


//============================================================================================
//
//			外部参照
//
//============================================================================================
//------------------------------------------------------------------
//データサイズ取得
//------------------------------------------------------------------
extern int FUSHIGIDATA_GetWorkSize(void);

//------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------
extern void FUSHIGIDATA_Init(FUSHIGI_DATA * fd);

//------------------------------------------------------------------
/**
 * @brief	ふしぎデータへのポインタ取得
 */
//------------------------------------------------------------------
extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);

//------------------------------------------------------------------
/// 配達員データの取得
//------------------------------------------------------------------
extern GIFT_DELIVERY * FUSHIGIDATA_GetDeliData(FUSHIGI_DATA * fd, int index);
//------------------------------------------------------------------
/// 配達員データをセーブデータ登録
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_SetDeliData(FUSHIGI_DATA *fd, const void *p, int link);
//------------------------------------------------------------------
/// 配達員データを抹消する
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_RemoveDeliData(FUSHIGI_DATA *fd, int index);
//------------------------------------------------------------------
/// 配達員データがセーブできるかチェック
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_CheckDeliDataSpace(FUSHIGI_DATA *fd);
//------------------------------------------------------------------
/// 配達員データの存在チェック
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsExistsDelivery(const FUSHIGI_DATA * fd, int index);


//------------------------------------------------------------------
/// カードデータの取得
//------------------------------------------------------------------
extern GIFT_CARD *FUSHIGIDATA_GetCardData(FUSHIGI_DATA *fd, int index);
//------------------------------------------------------------------
/// カードデータをセーブデータ登録
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_SetCardData(FUSHIGI_DATA *fd, const void *p);
//------------------------------------------------------------------
/// カードデータを抹消する
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_RemoveCardData(FUSHIGI_DATA *fd, int index);
//------------------------------------------------------------------
/// カードデータがセーブできるかチェック
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_CheckCardDataSpace(FUSHIGI_DATA *fd);
//------------------------------------------------------------------
/// カードデータが存在するか返す
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsExistsCard(const FUSHIGI_DATA * fd, int index);
//------------------------------------------------------------------
/// セーブデータ内にカードデータが存在するか返す
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsExistsCardAll(const FUSHIGI_DATA *fd);

//------------------------------------------------------------------
///	指定のカードにリンクされている配達員が存在するか
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_GetCardLinkDeli(const FUSHIGI_DATA *fd, int index);

//------------------------------------------------------------------
///	指定カードにリンクされている配達員を削除
//------------------------------------------------------------------
extern void FUSHIGIDATA_RemoveCardLinkDeli(const FUSHIGI_DATA *fd, int index);

//------------------------------------------------------------------
/// 指定のイベントはすでにもらったか返す
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsEventRecvFlag(FUSHIGI_DATA * fd, int num);
//------------------------------------------------------------------
/// 指定のイベントもらったよフラグを立てる
//------------------------------------------------------------------
extern void FUSHIGIDATA_SetEventRecvFlag(FUSHIGI_DATA * fd, int num);
//------------------------------------------------------------------
///	ふしぎなおくりものを表示出来るか？
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsFushigiMenu(FUSHIGI_DATA *fd);
//------------------------------------------------------------------
///	ふしぎなおくりものの表示フラグをONにする
//------------------------------------------------------------------
extern void FUSHIGIDATA_SetFushigiMenu(FUSHIGI_DATA *fd);


//------------------------------------------------------------------
/// これ以下の関数を使うために必要な初期化
//------------------------------------------------------------------
extern void FUSHIGIDATA_InitSlot(SAVEDATA * sv, int heap_id);
//------------------------------------------------------------------
/// これ以下の関数を使い終わった後の後始末
//------------------------------------------------------------------
extern void FUSHIGIDATA_FinishSlot(SAVEDATA * sv, int flag);
//------------------------------------------------------------------
/// スロットにデータがあるか返す関数
//------------------------------------------------------------------
extern int FUSHIGIDATA_CheckSlotData(void);
//------------------------------------------------------------------
/// 一番若いデータは何なのかを返す
//------------------------------------------------------------------
extern int FUSHIGIDATA_GetSlotType(int index);
//------------------------------------------------------------------
/// 一番若いデータの構造体へのポインタを返す
//------------------------------------------------------------------
extern GIFT_PRESENT *FUSHIGIDATA_GetSlotPtr(int index);
//------------------------------------------------------------------
/// 指定のスロットを消去する
//------------------------------------------------------------------
extern void FUSHIGIDATA_RemoveSlot(int index);


//------------------------------------------------------------------
/// デバッグ用にポケモンデータをセットする関数
//------------------------------------------------------------------
extern void FUSHIGIDATA_DebugSetPokemon(void);

#endif	/* __FUSHIGI_DATA_H__ */
