/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpw_tr.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DP WiFi Trade ライブラリ
	
	@author	kitayama(kitayama_shigetoshi@nintendo.co.jp)
	
	@version beta16 (2006/7/27)
		@li Dpw_Tr_ReturnAsync() を追加しました。ポケモンを引き取る際にはDpw_Tr_ReturnAsync()
			を使用し、Dpw_Tr_DeleteAsync()は交換済みのデータを削除する場合にのみ使用してください。
	@version beta14 (2006/7/5)
		@li サーバーアップデート中にアクセスした場合、::DPW_TR_ERROR_SERVER_TIMEOUTエラーになるようにしました。
	@version beta13 (2006/6/30)
		@li Dpw_Tr_TradeAsync() で正しくサーバーからのレスポンスを受け取れていなかったバグを修正しました。
	@version beta12 (2006/6/15)
		@li ::DPW_TR_ERROR_ILLEGAL_DATA, ::DPW_TR_ERROR_CHEAT_DATA, ::DPW_TR_ERROR_NG_POKEMON_NAME, ::DPW_TR_ERROR_NG_PARENT_NAME, ::DPW_TR_ERROR_NG_MAIL_NAME, ::DPW_TR_ERROR_NG_OWNER_NAME が、 Dpw_Tr_Data::name を特定の値にしたときに返るようにしました。
	@version beta11 (2006/6/9)
		@li ::DPW_TR_ERROR_SERVER_TIMEOUT の際のエラー表示を細かくしました。
	@version beta10	(2006/5/23)
		@li Dpw_Tr_Data::friend_keyを削除しました。
	@version beta9	(2006/5/22)
		@li Dpw_Tr_Init() に引数 friend_key を追加しました。
		@li Dpw_Tr_Data::friend_keyを追加しました。
	@version beta7	(2006/5/15)
		@li Dpw_Tr_Data::genderを追加しました。
	@version beta6	(2006/5/8)
		@li ::DPW_TR_GENDER_NONE のコメントを修正しました。
		@li Dpw_Tr_PokemonSearchData を追加しました。
		@li Dpw_Tr_Data::wantSimple の型を Dpw_Tr_PokemonSearchData へ変更しました。
		@li Dpw_Tr_DownloadMatchDataAsync() の引数を変更しました。
		@li Dpw_Tr_Db_InitServer(), Dpw_Tr_Db_UpdateServer(), Dpw_Tr_Db_ShuffleServerData() でエラー処理が誤っていたバグを修正しました。
		@li Dpw_Tr_Data::postDate, Dpw_Tr_Data::tradeDate へ入る月が、1マイナスされた値になっていたバグを修正しました。
	@version beta5	(2006/4/27)
		@li ::DPW_TR_ERROR_NG_TRAINER_NAMEを廃止し、::DPW_TR_ERROR_NG_PARENT_NAMEと::DPW_TR_ERROR_NG_OWNER_NAMEを追加しました。
		@li ハンドルしていなかった内部エラーがあった問題を修正しました。
	@version beta3	(2006/4/10)
		@li Dpw_Tr_PokemonData のサイズを変更しました。
		@li Dpw_Tr_Data::comment を削除しました。
		@li Dpw_Tr_Data::trainerID を追加しました。
		@li Dpw_Tr_Data::langCode を追加しました。	
		@li 特定のタイミングで Dpw_Tr_CancelAsync() を呼ぶと止まっていた不具合を修正しました。
	@version beta2	(2006/3/27)
		@li Dpw_Tr_DownloadMatchDataAsync() で検索されるデータをランダムに変更しました。
			異なるPIDでは、異なる検索結果となります。
		@li HTTPライブラリのレイヤーでエラーが起こったときに、エラーをクリアできていなかった不具合を修正しました。
		@li 関数のコメントに、返ってくるエラーの種類を追加しました。
		@li Dpw_Tr_Data::trainerType が交換されるようにしました。
		@li Dpw_Tr_Data::mail を削除しました。
		@li Dpw_Tr_PokemonData の大きさを172バイトに変更しました。
		@li ::DpwTrError で、NGワードに関するエラーを細分化しました。
		@li Dpw_Tr_Db_ShuffleServerData() を追加しました。
	@version beta1	(2006/3/17)
		@li 初版をリリースしました。
*/

#ifndef DPW_TR_H_
#define DPW_TR_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _NITRO
#include <dwc.h>
#else
#include <nitro.h>
#include <dwc.h>
#endif


#define DPW_SERVER_PUBLIC
//#define DPW_SERVER_SUB

/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/

//! 名前のサイズ
#define DPW_TR_NAME_SIZE 8

//! Dpw_Tr_DownloadMatchDataAsync() で取得可能なデータの最大値
#define DPW_TR_DOWNLOADMATCHDATA_MAX	7

//! Dpw_Tr_Callback の結果がエラーとなる場合の種別
typedef enum {
	DPW_TR_ERROR_SERVER_FULL = -1,		//!< サーバー容量オーバー
	DPW_TR_ERROR_SERVER_TIMEOUT = -2,	//!< サーバーからの応答がない
	DPW_TR_ERROR_NO_DATA = -3,			//!< サーバにデータが存在しない。データを復元してください。
	DPW_TR_ERROR_DATA_TIMEOUT = -4,		//!< 預けたデータのタイムアウト。タマゴを戻してください。
	DPW_TR_ERROR_ILLIGAL_REQUEST = -5,	//!< サーバへの不正な要求。既に預けているのに預けようとしたときなど。
	DPW_TR_ERROR_ILLEGAL_DATA = -6,		//!< アップロードされたデータが壊れている。
	DPW_TR_ERROR_CHEAT_DATA = -7,		//!< アップロードされたデータが不正
	DPW_TR_ERROR_NG_POKEMON_NAME = -8,	//!< アップロードされたポケモンの名前がNGワードを含んでいる
	DPW_TR_ERROR_NG_PARENT_NAME = -9,	//!< アップロードされたポケモンの親の名前がNGワードを含んでいる
	DPW_TR_ERROR_NG_MAIL_NAME = -10,	//!< アップロードされたメールの名前がNGワードを含んでいる
	DPW_TR_ERROR_NG_OWNER_NAME = -11,	//!< アップロードされた主人公名がNGワードを含んでいる
	DPW_TR_ERROR_CANCEL	= -12,			//!< 処理が Dpw_Tr_CancelAsync() によってキャンセルされた。
	DPW_TR_ERROR_FATAL = -13,			//!< 通信致命的エラー。電源の再投入が必要です
	DPW_TR_ERROR_DISCONNECTED = -14,	//!< 通信不能エラー。ライブラリの初期化が必要です。
	DPW_TR_ERROR_FAILURE = -15			//!< 通信失敗エラー。リトライしてください
} DpwTrError;

//! サーバーステータス
typedef enum {
	DPW_TR_STATUS_SERVER_OK,				//!< 正常
	DPW_TR_STATUS_SERVER_STOP_SERVICE,		//!< サービス一時停止中
	DPW_TR_STATUS_SERVER_FULL				//!< サーバー容量オーバー
} DpwTrServerStatus;

//! 日時構造体
typedef struct {
	u16 year;	//!< 年
	u8 month;	//!< 月
	u8 day;		//!< 日
	u8 hour;	//!< 時
	u8 minutes;	//!< 分
	u8 sec;		//!< 秒
	u8 padding;	// パディング
} Dpw_Tr_Date;

//! ポケモンの性別
typedef enum {
	DPW_TR_GENDER_MALE = 1,		//!< オス
	DPW_TR_GENDER_FEMALE = 2,	//!< メス
	DPW_TR_GENDER_NONE = 3		//!< 性別なし。検索時に性別を問わないようにするためには、この値を指定してください。
} Dpw_Tr_PokemonGender;

//! ポケモンデータのサーバー検索用構造体
typedef struct {
	s16 characterNo;	//!< キャラクタ番号
	s8 gender;			//!< 性別。 Dpw_Tr_PokemonGender の値になる。
	s8 level;			//!< レベル。
} Dpw_Tr_PokemonDataSimple;

//! ポケモンデータのサーバー検索条件構造体
typedef struct {
	s16 characterNo;	//!< キャラクタ番号
	s8 gender;			//!< 性別。 Dpw_Tr_PokemonGender の値になる。
	s8 level_min;		//!< レベルの下限。0は指定なし、1～100はそのレベル以上のポケモンという意味になる。
	s8 level_max;		//!< レベルの上限。0は指定なし、1～100はそのレベル以下のポケモンという意味になる。
	s8 padding;			// パディング
} Dpw_Tr_PokemonSearchData;

//! ポケモンのデータ。データの内容は見知しない
typedef struct {
	u8 data[236];		//!< ポケモンのデータ
} Dpw_Tr_PokemonData;

//! Dpw_Trライブラリでサーバーとやり取りされるメインデータ構造体
typedef struct {
	Dpw_Tr_PokemonData postData;			//!< 「預ける」ポケモンの詳細データ
	Dpw_Tr_PokemonDataSimple postSimple;	//!< 「預ける」ポケモンの簡略データ（サーバー検索用）
	Dpw_Tr_PokemonSearchData wantSimple;	//!< 「ほしい」ポケモンの簡略データ（サーバー検索用）
	u8 gender;								//!< 主人公の性別
	u8 padding;								// パディング
	Dpw_Tr_Date postDate;					//!< 預けた日時（サーバーにてセット）
	Dpw_Tr_Date tradeDate;					//!< 交換成立日時（サーバーにてセット）
	s32 id;									//!< このデータのID（サーバーにてセット）
	u16 name[DPW_TR_NAME_SIZE];				//!< 主人公名
	u16 trainerID;							//!< トレーナーのID
	u8 countryCode;							//!< 住んでいる国コード
	u8 localCode;							//!< 住んでいる地方コード
	u8 trainerType;							//!< トレーナータイプ
	s8 isTrade;								//!< 交換済みフラグ（サーバーにてセット）
	u8 versionCode;							//!< バージョンコード
	u8 langCode;							//!< 言語コード
} Dpw_Tr_Data;


/*-----------------------------------------------------------------------*
					グローバル変数定義
 *-----------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*
					関数外部宣言
 *-----------------------------------------------------------------------*/

extern void Dpw_Tr_Init(s32 pid, u64 friend_key);
extern void Dpw_Tr_Main(void);
extern void Dpw_Tr_End(void);
extern BOOL Dpw_Tr_IsAsyncEnd(void);
extern s32 Dpw_Tr_GetAsyncResult(void);
extern void Dpw_Tr_UploadAsync(const Dpw_Tr_Data* data);
extern void Dpw_Tr_UploadFinishAsync(void);
extern void Dpw_Tr_DownloadAsync(Dpw_Tr_Data* data);
extern void Dpw_Tr_GetUploadResultAsync(Dpw_Tr_Data* data);
extern void Dpw_Tr_DeleteAsync(void);
extern void Dpw_Tr_ReturnAsync(void);
extern void Dpw_Tr_CancelAsync(void);
extern void Dpw_Tr_DownloadMatchDataAsync(const Dpw_Tr_PokemonSearchData* searchData, s32 maxNum, Dpw_Tr_Data* downloadData);
extern void Dpw_Tr_TradeAsync(s32 id, const Dpw_Tr_Data* uploadData, Dpw_Tr_Data* downloadData);
extern void Dpw_Tr_TradeFinishAsync(void);
extern void Dpw_Tr_GetServerStateAsync(void);

#ifndef SDK_FINALROM
BOOL Dpw_Tr_Db_InitServer(void);
BOOL Dpw_Tr_Db_UpdateServer(void);
BOOL Dpw_Tr_Db_ShuffleServerData(void);
#else
#define Dpw_Tr_Db_InitServer( ... )		(NULL)
#define Dpw_Tr_Db_UpdateServer( ... )	(NULL)
#define Dpw_Tr_Db_ShuffleServerData( ... )	(NULL)
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // DPW_TR_H_