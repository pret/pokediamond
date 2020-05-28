/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpw_bt.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DP WiFi Battle Tower ライブラリ
	
	@author	kitayama(kitayama_shigetoshi@nintendo.co.jp)
	
	@version beta15 (2006/7/7)
		@li ::Dpw_Bt_Player及び::Dpw_Bt_Leaderの性別を入れていた部分をビットフラグとし、
			性別フラグとNGネームフラグを持つようにしました。
	@version beta14 (2006/7/5)
		@li ルーム数の最大値::DPW_BT_ROOM_NUM_MAXを100に変更しました。
		@li サーバーアップデート中にアクセスした場合、::DPW_BT_ERROR_SERVER_TIMEOUTエラーになるようにしました。
	@version beta11 (2006/6/9)
		@li Dpw_Bt_UploadPlayerAsync() の引数 win が0のときにアサートになっていたバグを修正しました。
		@li ::DPW_BT_ERROR_SERVER_TIMEOUT の際のエラー表示を細かくしました。
	@version beta10	(2006/5/23)
		@li サーバーの初期化でルームデータが初期化されなくなりました。
		@li Dpw_Bt_Player::friend_keyを削除しました。
		@li Dpw_Bt_Leader::friend_keyを削除しました。
	@version beta9	(2006/5/22)
		@li Dpw_Bt_Init() に引数 friend_key を追加しました。
		@li Dpw_Bt_Player::friend_keyを追加しました。
		@li Dpw_Bt_Leader::friend_keyを追加しました。
		@li アップデート時に、リーダー候補が一人もいない場合もルームの更新が行われていたバグを修正しました。
	@version beta8	(2006/5/19)
		@li Dpw_Bt_PokemonData のサイズを変更しました。
	@version beta7	(2006/5/15)
		@li Dpw_Bt_Leader::genderを追加しました。
		@li Dpw_Bt_Player::genderを追加しました。
		@li Dpw_Bt_Player::playerNameにNGネームが含まれる場合、アップデート時に置き換えられるようになりました。
	@version beta6	(2006/5/8)
		@li ::DPW_BT_RANK_NUMを追加しました。
		@li Dpw_Bt_GetRoomNumAsync(), Dpw_Bt_DownloadRoomAsync(), Dpw_Bt_UploadPlayerAsync() で、引数rankの範囲チェックが誤っていた
			バグを修正しました。
		@li Dpw_Bt_Db_InitServer(), Dpw_Bt_Db_UpdateServer() でエラー処理が誤っていたバグを修正しました。
	@version beta5	(2006/4/27)
		@li ::DPW_BT_ROOM_NUM_MAXを追加しました。（暫定的に20としています。）
		@li ハンドルしていなかった内部エラーがあった問題を修正しました。
	@version beta4	(2006/4/17)
		@li Dpw_Bt_Leader::leaderMessage のサイズを変更しました。
		@li Dpw_Bt_Player::leaderMessage, Dpw_Bt_Player::message のサイズを変更しました。
	@version beta3	(2006/4/10)
		@li Dpw_Bt_PokemonData のサイズを変更しました。
		@li Dpw_Bt_Leader::versionCode, Dpw_Bt_Leader::langCode, Dpw_Bt_Leader::countryCode, Dpw_Bt_Leader::localCode を追加しました。
		@li Dpw_Bt_Player::versionCode, Dpw_Bt_Player::langCode, Dpw_Bt_Player::countryCode, Dpw_Bt_Player::localCode を追加しました。
		@li Dpw_Bt_Room::leader のサイズを変更しました。
		@li 特定のタイミングで Dpw_Bt_CancelAsync() を呼ぶと止まっていた不具合を修正しました。
	@version beta2	(2006/3/27)
		@li HTTPライブラリのレイヤーでエラーが起こったときに、エラーをクリアできていなかった不具合を修正しました。
		@li 関数のコメントに、返ってくるエラーの種類を追加しました。
		@li Dpw_Bt_PokemonData の大きさを172バイトに変更しました。
	@version beta1	(2006/3/17)
		@li 初版をリリースしました。
*/

#ifndef DPW_BT_H_
#define DPW_BT_H_

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

//! ランクの数
#define DPW_BT_RANK_NUM			10

//! ルーム数の最大値
#define DPW_BT_ROOM_NUM_MAX		100

//! Dpw_Bt_Callback の結果がエラーとなる場合の種別
typedef enum {
	DPW_BT_ERROR_SERVER_FULL = -1,		//!< サーバー容量オーバー
	DPW_BT_ERROR_SERVER_TIMEOUT = -2,	//!< サーバーからの応答がない
	DPW_BT_ERROR_ILLIGAL_REQUEST = -3,	//!< サーバへの不正な要求。不正な部屋番号を指定しています
	DPW_BT_ERROR_CANCEL	= -4,			//!< 処理が Dpw_Bt_CancelAsync() によってキャンセルされた
	DPW_BT_ERROR_FATAL = -5,			//!< 通信致命的エラー。電源の再投入が必要です
	DPW_BT_ERROR_DISCONNECTED = -6,		//!< 通信不能エラー。ライブラリの初期化が必要です。
	DPW_BT_ERROR_FAILURE = -7			//!< 通信失敗エラー。リトライしてください
} DpwBtError;

//! サーバーステータス
typedef enum {
	DPW_BT_STATUS_SERVER_OK,				//!< 正常
	DPW_BT_STATUS_SERVER_STOP_SERVICE,		//!< サービス一時停止中
	DPW_BT_STATUS_SERVER_FULL				//!< サーバー容量オーバー
} DpwBtServerStatus;

//! ポケモンのデータ。データの内容は見知しない
typedef struct {
	u8 data[56];		//!< ポケモンのデータ
} Dpw_Bt_PokemonData;

//! リーダーデータ構造体
typedef struct {
	u16 playerName[8];		//!< プレイヤー名
	u8 versionCode;			//!< バージョンコード
	u8 langCode;			//!< 言語コード
	u8 countryCode;			//!< 住んでいる国コード
	u8 localCode;			//!< 住んでいる地方コード
	u8 playerId[4];			//!< プレイヤーID
	s8 leaderMessage[8];	//!< リーダーメッセージ
	union{
		struct{
			u8 ngname_f	:1;	//!< NGネームフラグ
			u8 gender	:1;	//!< プレイヤーの性別フラグ
			u8			:6;	// あまり6bit
		};
		u8	  flags;
	};
	u8 padding;				// パディング
} Dpw_Bt_Leader;

//! プレイヤーデータ構造体
typedef struct {
	Dpw_Bt_PokemonData pokemon[3];	//!< ポケモンデータ
	u16 playerName[8];		//!< プレイヤー名
	u8 versionCode;			//!< バージョンコード
	u8 langCode;			//!< 言語コード
	u8 countryCode;			//!< 住んでいる国コード
	u8 localCode;			//!< 住んでいる地方コード
	u8 playerId[4];			//!< プレイヤーID
	s8 leaderMessage[8];	//!< リーダーメッセージ
	union{
		struct{
			u8 ngname_f	:1;	//!< NGネームフラグ
			u8 gender	:1;	//!< プレイヤーの性別フラグ
			u8			:6;	// あまり6bit
		};
		u8	  flags;
	};
	u8 trainerType;			//!< トレーナータイプ
	s8 message[24];			//!< メッセージ
	u16 result;				//!< 成績
} Dpw_Bt_Player;

//! ルームデータ構造体
typedef struct {
	Dpw_Bt_Player player[7];	//!< プレイヤーデータ
	Dpw_Bt_Leader leader[30];	//!< リーダーデータ
} Dpw_Bt_Room;


/*-----------------------------------------------------------------------*
					グローバル変数定義
 *-----------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*
					関数外部宣言
 *-----------------------------------------------------------------------*/

extern void Dpw_Bt_Init(s32 pid, u64 friend_key);
extern void Dpw_Bt_Main(void);
extern void Dpw_Bt_End(void);
extern BOOL Dpw_Bt_IsAsyncEnd(void);
extern s32 Dpw_Bt_GetAsyncResult(void);
extern void Dpw_Bt_GetRoomNumAsync(s32 rank);
extern void Dpw_Bt_DownloadRoomAsync(s32 rank, s32 roomNo, Dpw_Bt_Room* roomData);
extern void Dpw_Bt_UploadPlayerAsync(s32 rank, s32 roomNo, s32 win, const Dpw_Bt_Player* player);
extern void Dpw_Bt_CancelAsync(void);
extern void Dpw_Bt_GetServerStateAsync(void);

#ifndef SDK_FINALROM
BOOL Dpw_Bt_Db_InitServer(void);
BOOL Dpw_Bt_Db_UpdateServer(void);
#else
#define Dpw_Bt_Db_InitServer( ... )		(NULL)
#define Dpw_Bt_Db_UpdateServer( ... )	(NULL)
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // DPW_BT_H_