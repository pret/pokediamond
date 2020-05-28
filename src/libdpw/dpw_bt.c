/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpw_bt.c

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

#ifdef _NITRO
#include <nitroWiFi/socl.h>
#endif

#include "include/libdpw/dpw_bt.h"
#include "include/libdpw/dpwi_session.h"
#include "include/libdpw/dpwi_assert.h"

/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/

#ifdef DPW_SERVER_PUBLIC
#define BT_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"
#else
#ifdef DPW_SERVER_SUB
#define BT_SERVER_URL		"http://kiyoshi.servebeer.com/web/"
#else
#define BT_SERVER_URL		"http://sdkdev.gamespy.com/games/pokemondpds/web/"
#endif
#endif
//#define BT_SERVER_URL		"http://sdkdev.gamespy.com/games/mariokartds/web/"
//#define BT_SERVER_URL		"http://ishikawa.servebeer.com/web/"
//#define BT_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"

#define BT_URL_GETROOMNUM	(const u8*)(BT_SERVER_URL "battletower/roomnum.asp")
#define BT_URL_DOWNLOADROOM	(const u8*)(BT_SERVER_URL "battletower/download.asp")
#define BT_URL_UPLOADPLAYER	(const u8*)(BT_SERVER_URL "battletower/upload.asp")
#define BT_URL_GETSERVERSTATE (const u8*)(BT_SERVER_URL "battletower/info.asp")
#define BT_URL_INIT			(BT_SERVER_URL "battletower/init.asp")
#define BT_URL_UPDATE 		(BT_SERVER_URL "battletower/update.asp")

#ifdef _NITRO
// 構造体が想定のサイズとなっているかチェック
SDK_COMPILER_ASSERT(sizeof(Dpw_Bt_Leader) == 34);
SDK_COMPILER_ASSERT(sizeof(Dpw_Bt_Player) == 228);
SDK_COMPILER_ASSERT(sizeof(Dpw_Bt_Room) == sizeof(Dpw_Bt_Player) * 7 + sizeof(Dpw_Bt_Leader) * 30);
#endif

#define DB_HTTP_FLAG_NOT_COMPLETED	(-1)

#define BT_RESPONSE_SUCCESS			(1)
#define BT_RESPONSE_ILLIGAL_REQUEST	(2)
#define BT_RESPONSE_STOP_SERVICE	(3)
#define BT_RESPONSE_SERVER_FULL		(4)
#define BT_RESPONSE_SERVER_TIMEOUT	(5)

typedef enum {
	DPWi_BT_NOT_INIT,
	DPWi_BT_NORMAL,
	DPWi_BT_RROCESS_GETROOMNUM,
	DPWi_BT_CANCEL_GETROOMNUM,
	DPWi_BT_RROCESS_DOWNLOADROOM,
	DPWi_BT_CANCEL_DOWNLOADROOM,
	DPWi_BT_RROCESS_UPLOADPLAYER,
	DPWi_BT_CANCEL_UPLOADPLAYER,
	DPWi_BT_RROCESS_GETSERVERSTATE,
	DPWi_BT_CANCEL_GETSERVERSTATE,
	DPWi_BT_END_ASYNC
} DpwiBtState;

typedef struct {
	DpwiBtState state;		// ライブラリの状態
	s32 last_result;		// 最後に行った非同期処理の結果
	s32 pid;				// 使用するPID
	u64 friend_key;			// フレンドキー
	u8 send_buf[sizeof(Dpw_Bt_Player) + 11];	// 送信バッファ
	u8 recv_buf[2];			// 受信バッファ
	u8* user_recv_buf;		// ユーザーから与えられた受信バッファ
} DpwiBtCtrl;

/*-----------------------------------------------------------------------*
					関数プロトタイプ宣言
 *-----------------------------------------------------------------------*/

void Dpw_Bt_Init(s32 pid, u64 friend_key);
void Dpw_Bt_Main(void);
void Dpw_Bt_End(void);
BOOL Dpw_Bt_IsAsyncEnd(void);
s32 Dpw_Bt_GetAsyncResult(void);
void Dpw_Bt_GetRoomNumAsync(s32 rank);
void Dpw_Bt_DownloadRoomAsync(s32 rank, s32 roomNo, Dpw_Bt_Room* roomData);
void Dpw_Bt_UploadPlayerAsync(s32 rank, s32 roomNo, s32 win, const Dpw_Bt_Player* player);
void Dpw_Bt_CancelAsync(void);
void Dpw_Bt_GetServerStateAsync(void);
static BOOL Dpwi_Bt_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize );
static DpwBtError Dpwi_Bt_HandleCommonError(DpwiHttpError error);
static void Dpwi_Db_GhttpCopleteCallback(const char* buf, int len, DWCGHTTPResult result, void* param);

/*-----------------------------------------------------------------------*
					グローバル変数定義
 *-----------------------------------------------------------------------*/

static DpwiBtCtrl dpw_bt;
static int db_ghttp_flag;

/*-----------------------------------------------------------------------*
					グローバル関数定義
 *-----------------------------------------------------------------------*/

/*!
	Dpw_Bt ライブラリを初期化します。全てのDpw_Bt の付く関数を実行する前にコールします。
	
	GSプロファイルIDは、 DWC_LoginAsync() 関数のコールバックで取得できる値で、サーバー側で一意にクライアント
	を判別するための値です。
	
	この関数をコールする際は、DWC ライブラリのインターネット接続関数でネットワークに接続してから行ってくだ
	さい。ただし、ログインを行っている必要はありません。
	
	@param[in] pid	自分のGSプロファイルID
	@param[in] friend_key	自分のフレンドキー。DWC_CreateFriendKey() で取得できます。
*/
void Dpw_Bt_Init(s32 pid, u64 friend_key) {

	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NOT_INIT, "dpw bt is already initialized.\n");

	dpw_bt.state = DPWi_BT_NORMAL;
	dpw_bt.last_result = 0;
	dpw_bt.pid = pid;
	dpw_bt.friend_key = friend_key;
}

/*!
	毎ゲームフレーム呼びだし、処理を進めます。
	
	利便性のため、この関数は常に呼び出すことができます。未初期化状態では何も行いません。
*/
void Dpw_Bt_Main(void) {
	
	switch (dpw_bt.state) {
	case DPWi_BT_NOT_INIT:
		break;
	case DPWi_BT_NORMAL:
		break;
	case DPWi_BT_RROCESS_GETROOMNUM:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			if (DpwiGetResponseSize() > 0) {
				dpw_bt.last_result = dpw_bt.recv_buf[0];
			} else {
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_RROCESS_DOWNLOADROOM:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Bt_Room)) {
				dpw_bt.last_result = 0;
			} else {
				switch (dpw_bt.user_recv_buf[0]) {
				case BT_RESPONSE_ILLIGAL_REQUEST:
					dpw_bt.last_result = DPW_BT_ERROR_ILLIGAL_REQUEST;
					break;
				case BT_RESPONSE_SERVER_TIMEOUT:
					dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_bt.user_recv_buf[0]);
					dpw_bt.last_result = DPW_BT_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_RROCESS_UPLOADPLAYER:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			switch (dpw_bt.recv_buf[0]) {
			case BT_RESPONSE_SUCCESS:
				dpw_bt.last_result = 0;
				break;
			case BT_RESPONSE_ILLIGAL_REQUEST:
				dpw_bt.last_result = DPW_BT_ERROR_ILLIGAL_REQUEST;
				break;
			case BT_RESPONSE_SERVER_FULL:
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_FULL;
				break;
			case BT_RESPONSE_SERVER_TIMEOUT:
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_bt.recv_buf[0]);
				dpw_bt.last_result = DPW_BT_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_RROCESS_GETSERVERSTATE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			switch (dpw_bt.recv_buf[0]) {
			case BT_RESPONSE_SUCCESS:
				dpw_bt.last_result = DPW_BT_STATUS_SERVER_OK;
				break;
			case BT_RESPONSE_STOP_SERVICE:
				dpw_bt.last_result = DPW_BT_STATUS_SERVER_STOP_SERVICE;
				break;
			case BT_RESPONSE_SERVER_FULL:
				dpw_bt.last_result = DPW_BT_STATUS_SERVER_FULL;
				break;
			case BT_RESPONSE_SERVER_TIMEOUT:
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_bt.recv_buf[0]);
				dpw_bt.last_result = DPW_BT_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_CANCEL_GETROOMNUM:
	case DPWi_BT_CANCEL_DOWNLOADROOM:
	case DPWi_BT_CANCEL_UPLOADPLAYER:
	case DPWi_BT_CANCEL_GETSERVERSTATE:
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_CANCEL;
		DpwiSessionShutdown();
		break;
	case DPWi_BT_END_ASYNC:
		break;
	}
}

/*!
	メモリの開放など終了処理を行います。
	
	この関数は、非同期処理を実行しているときにはコールすることができません。Dpw_Bt_IsAsyncEnd()で非同期処
	理の終了を確認してからコールしてください。
*/
void Dpw_Bt_End(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is running.\n");
	
	dpw_bt.state = DPWi_BT_NOT_INIT;
}

/*!
	Dpw_Btライブラリの非同期処理が終了しているか否かを返します。
	
	関数名に「Async」が付く関数をコールした際は、この関数を定期的にコールして、終了を確認してください。
	
	@retval TRUE	非同期処理が終了している
	@retval FALSE	非同期処理が終了していない
*/
BOOL Dpw_Bt_IsAsyncEnd(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	
	switch (dpw_bt.state) {
	case DPWi_BT_NORMAL:
		return TRUE;
		break;
	case DPWi_BT_END_ASYNC:
		dpw_bt.state = DPWi_BT_NORMAL;
		return TRUE;
		break;
	}

	return FALSE;
}

/*!
	直前の非同期処理の結果を取得します。
	Bpw_Bt_IsAsyncEnd() で終了を確認してから呼んでください。
	
	非同期処理を行った場合は、必ずこの関数で結果（特にエラーが起こっていないか）を確認してください。@n
	エラーの種類は非同期処理によって異なりますが、以下のエラーは共通です。
	
	@li ::DPW_BT_ERROR_SERVER_TIMEOUT
	@li ::DPW_BT_ERROR_CANCEL
	@li ::DPW_BT_ERROR_FATAL
	@li ::DPW_BT_ERROR_DISCONNECTED
	@li ::DPW_BT_ERROR_FAILURE
	
	@return	非同期処理の結果。負の値はエラーを示し、DpwBtErrorの値が返ります。
*/
s32 Dpw_Bt_GetAsyncResult(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	
	return dpw_bt.last_result;
}

/*!
	現在オープンしているルーム数の取得を開始します。
	
	取得出来た場合は Dpw_Bt_GetAsyncResult() でルーム数が返されます。
	エラーが起こった場合は、共通のエラーのいずれかが返されます。
	
	@param[in] rank	ランク
*/
void Dpw_Bt_GetRoomNumAsync(s32 rank) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	DPW_MINMAX_TASSERT(rank, 1, DPW_BT_RANK_NUM);
	
	// セッション初期化
	DpwiSessionInitialize();

	dpw_bt.send_buf[0] = (u8)(rank - 1);	// サーバー側は0ベースなので、合わせる
	
	// 通信開始
	if (Dpwi_Bt_CallSessionRequest(BT_URL_GETROOMNUM, dpw_bt.send_buf, 1, dpw_bt.recv_buf, 2)) {
		dpw_bt.state = DPWi_BT_RROCESS_GETROOMNUM;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	ルームデータをダウンロードします。
	
	成功した場合、 Dpw_Bt_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_BT_ERROR_ILLIGAL_REQUEST	： ルーム番号の指定が誤っています。
	
	@param[in] rank	ランク
	@param[in] roomNo ルーム番号
	@param[out] roomData ダウンロードしたルームデータを記録するバッファ
*/
void Dpw_Bt_DownloadRoomAsync(s32 rank, s32 roomNo, Dpw_Bt_Room* roomData) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	DPW_MINMAX_TASSERT(rank, 1, DPW_BT_RANK_NUM);
	DPW_MINMAX_TASSERT(roomNo, 1, DPW_BT_ROOM_NUM_MAX);
	DPW_NULL_TASSERT(roomData);
	
	dpw_bt.user_recv_buf = (u8*)roomData;
	
	// セッション初期化
	DpwiSessionInitialize();

	dpw_bt.send_buf[0] = (u8)(rank - 1);	// サーバー側は0ベースなので、合わせる
	dpw_bt.send_buf[1] = (u8)(roomNo - 1);	// サーバー側は0ベースなので、合わせる
	
	// 通信開始
	if (Dpwi_Bt_CallSessionRequest(BT_URL_DOWNLOADROOM, dpw_bt.send_buf, 2, roomData, sizeof(Dpw_Bt_Room))) {
		dpw_bt.state = DPWi_BT_RROCESS_DOWNLOADROOM;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	プレイヤーデータをアップロードします。
	
	成功した場合、 Dpw_Bt_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_BT_ERROR_SERVER_FULL		： サーバーの容量オーバーです。
	@li ::DPW_BT_ERROR_ILLIGAL_REQUEST	： ルーム番号の指定が誤っています。
	
	@param[in] rank	ランク
	@param[in] roomNo	ルーム番号
	@param[in] win	プレイヤーの勝ち数
	@param[in] player	プレイヤーデータ。関数内でコピーしますので、静的に保持する必要はありません。
*/
void Dpw_Bt_UploadPlayerAsync(s32 rank, s32 roomNo, s32 win, const Dpw_Bt_Player* player) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	DPW_MINMAX_TASSERT(rank, 1, DPW_BT_RANK_NUM);
	DPW_MINMAX_TASSERT(roomNo, 1, DPW_BT_ROOM_NUM_MAX);
	DPW_MINMAX_TASSERT(win, 0, 7);
	DPW_NULL_TASSERT(player);
	
	// セッション初期化
	DpwiSessionInitialize();

	memcpy(&dpw_bt.send_buf[0], player, sizeof(Dpw_Bt_Player));
	dpw_bt.send_buf[sizeof(Dpw_Bt_Player)] = (u8)(rank - 1);	// サーバー側は0ベースなので、合わせる
	dpw_bt.send_buf[sizeof(Dpw_Bt_Player) + 1] = (u8)(roomNo - 1);	// サーバー側は0ベースなので、合わせる
	dpw_bt.send_buf[sizeof(Dpw_Bt_Player) + 2] = (u8)win;
	memcpy(&dpw_bt.send_buf[sizeof(Dpw_Bt_Player) + 3], &dpw_bt.friend_key, 8);
	
	// 通信開始
	if (Dpwi_Bt_CallSessionRequest(BT_URL_UPLOADPLAYER, dpw_bt.send_buf, sizeof(Dpw_Bt_Player) + 11, dpw_bt.recv_buf, 2)) {
		dpw_bt.state = DPWi_BT_RROCESS_UPLOADPLAYER;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Bt ライブラリで現在行われている非同期処理をキャンセルします。
	
	キャンセルした場合、 Dpw_Bt_GetAsyncResult() の返値は DPW_BT_ERROR_CANCEL となります。
	
	既に通信が終了していることもありますので、キャンセルは常に成功するとは限りません。
	キャンセルできたかどうかは、 Dpw_Bt_GetAsyncResult() の返値が DPW_BT_ERROR_CANCEL となっているかで判断してください。
	
	Dpw_Bt_CancelAsync()自体も非同期処理ですが、これをキャンセルすることはできません。
*/
void Dpw_Bt_CancelAsync(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	
	switch (dpw_bt.state) {
	case DPWi_BT_RROCESS_GETROOMNUM:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_GETROOMNUM;
		break;
	case DPWi_BT_RROCESS_DOWNLOADROOM:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_DOWNLOADROOM;
		break;
	case DPWi_BT_RROCESS_UPLOADPLAYER:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_UPLOADPLAYER;
		break;
	case DPWi_BT_RROCESS_GETSERVERSTATE:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_GETSERVERSTATE;
		break;
	}
}

/*!
	サーバー状態の調査を開始します。
	
	サーバーと正常に通信できた場合は、 Dpw_Bt_GetAsyncResult() で DpwBtServerStatus の値が返されます。
	
	正常に通信できなかった場合は、 共通のエラーのいずれかが返されます。
*/
void Dpw_Bt_GetServerStateAsync(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	
	// セッション初期化
	DpwiSessionInitialize();

	// 通信開始
	if (Dpwi_Bt_CallSessionRequest(BT_URL_GETSERVERSTATE, dpw_bt.send_buf, 0, dpw_bt.recv_buf, 2)) {
		dpw_bt.state = DPWi_BT_RROCESS_GETSERVERSTATE;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

#ifndef SDK_FINALROM
/*!
	バトルタワーのサーバ状態を初期化します。
	内部でブロックします。
	
	この関数は、デバッグ／テスト用です。FINALROMでは無効となります。
	
	@retval TRUE	初期化に成功した
	@retval FALSE	初期化に失敗した
*/
BOOL Dpw_Bt_Db_InitServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(BT_URL_INIT, Dpwi_Db_GhttpCopleteCallback, NULL);
	
	while (db_ghttp_flag == DB_HTTP_FLAG_NOT_COMPLETED) {
		
		if (!DWC_ProcessGHTTP()) {
			DWC_ClearError();
			return FALSE;
		}
		
		OS_Sleep(16);
	}
	
	DWC_ShutdownGHTTP();

	if (db_ghttp_flag == DWC_GHTTP_SUCCESS) {
		return TRUE;
	} else {
		DWC_ClearError();
		return FALSE;
	}
}
#endif

#ifndef SDK_FINALROM
/*!
	バトルタワーのサーバの一日一回のアップデート行います。
	内部でブロックします。
	
	この関数は、デバッグ／テスト用です。FINALROMでは無効となります。
*/
BOOL Dpw_Bt_Db_UpdateServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(BT_URL_UPDATE, Dpwi_Db_GhttpCopleteCallback, NULL);
	
	while (db_ghttp_flag == DB_HTTP_FLAG_NOT_COMPLETED) {
		
		if (!DWC_ProcessGHTTP()) {
			DWC_ClearError();
			return FALSE;
		}
		
		OS_Sleep(16);
	}
	
	DWC_ShutdownGHTTP();

	if (db_ghttp_flag == DWC_GHTTP_SUCCESS) {
		return TRUE;
	} else {
		DWC_ClearError();
		return FALSE;
	}
}
#endif

/*-----------------------------------------------------------------------*
					ローカル関数定義
 *-----------------------------------------------------------------------*/

static BOOL Dpwi_Bt_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize) {
	
	switch (DpwiSessionRequest(url, dpw_bt.pid, data, len, (u8*)resbuf, ressize)) {
	case DPWI_COMMON_SESSION_SUCCESS:				// 正常終了
		return TRUE;
		break;
	case DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED:	// 未初期化
		DPW_TASSERTMSG(FALSE, "common session not initialized.");
		break;
	case DPWI_COMMON_SESSION_ERROR_NOMEMORY:		// メモリー不足
		DPW_TASSERTMSG(FALSE, "common session memory shortage.");
		break;
	}
	
	return FALSE;
}

static DpwBtError Dpwi_Bt_HandleCommonError(DpwiHttpError error) {
	
	DpwBtError ret;
	
	OS_TPrintf("[DPW BT] ghttp error: %d\n", error);
	
	switch (error) {
	case DPWI_COMMON_SESSION_ERROR_IN_ERROR:			// エラー発生中 
	case DPWI_COMMON_SESSION_ERROR_INVALID_POST:		// 無効な送信 
	case DPWI_COMMON_SESSION_ERROR_INVALID_FILE_NAME:	// 無効なファイル名 
	case DPWI_COMMON_SESSION_ERROR_INVALID_BUFFER_SIZE:	// 無効なバッファサイズ 
	case DPWI_COMMON_SESSION_ERROR_INVALID_URL:			// 無効なURL
	case DPWI_COMMON_SESSION_ERROR_UNSPECIFIED_ERROR:	// その他のエラー
	case DPWI_COMMON_SESSION_ERROR_BUFFER_OVERFLOW:		// 供給されたバッファが小さすぎるため、ファイルの取得失敗 
	case DPWI_COMMON_SESSION_ERROR_PARSE_URL_FAILED:	// URL解析エラー 
//	case DPWI_COMMON_SESSION_ERROR_ENCRYPTION_ERROR:	// 暗号化エラー 
	case DPWI_COMMON_SESSION_ERROR_FILE_TOO_BIG:		// ファイルが大きすぎるためダウンロード不可能 
	case DPWI_COMMON_SESSION_ERROR_FILE_INCOMPLETE:		// ダウンロードの中断 
	case DPWI_COMMON_SESSION_ERROR_FILE_WRITE_FAILED:	// ローカルファイルへの書き込みエラー 
	case DPWI_COMMON_SESSION_ERROR_FILE_READ_FAILED:	// ローカルファイルからの読み出しエラー 
	case DPWI_COMMON_SESSION_ERROR_BAD_RESPONSE:		// HTTPサーバからのレスポンスの解析エラー 
	case DPWI_COMMON_SESSION_ERROR_BUFFER_OVER:			// COMMON層: 受信バッファをオーバーした
		DPW_TASSERTMSG(FALSE, "library internal error. please contact author.");
		ret = DPW_BT_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY:	// メモリ不足 
	case DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY:		// メモリ割り当て失敗 
	case DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR: 		// メモリ割り当て失敗 
		DPW_TASSERTMSG(FALSE, "common session memory shortage.");
		ret = DPW_BT_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED:	// ホスト名検索失敗 
		OS_TPrintf("[DPW BT] dns lookup failed.\n");
		ret = DPW_BT_ERROR_FAILURE;
		break;
	case DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED:		// ソケットの作成、初期化、読み出し、書き込み失敗 
	case DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED:		// HTTPサーバへの接続失敗 
		OS_TPrintf("[DPW BT] socket error.\n");
		ret = DPW_BT_ERROR_FAILURE;
		break;
	case DPWI_COMMON_SESSION_ERROR_UNAUTHORIZED:		// ファイル取得未許可 
	case DPWI_COMMON_SESSION_ERROR_FORBIDDEN:			// HTTPサーバのファイル送信拒否 
	case DPWI_COMMON_SESSION_ERROR_FILE_NOT_FOUND:		// HTTPサーバ上のファイル検索失敗 
	case DPWI_COMMON_SESSION_ERROR_SERVER_ERROR:		// HTTPサーバ内部エラー
	case DPWI_COMMON_SESSION_ERROR_CHECKSUM:			// COMMON層: チェックサムの不一致
	case DPWI_COMMON_SESSION_ERROR_PID:					// COMMON層: PIDの不一致
	case DPWI_COMMON_SESSION_ERROR_DATA_LENGTH: 		// COMMON層: データの長さが不正
	case DPWI_COMMON_SESSION_ERROR_TOKEN_NOT_FOUND:		// COMMON層: トークンがない
	case DPWI_COMMON_SESSION_ERROR_INCORRECT_HASH:		// COMMON層: ハッシュが合わない
		OS_TPrintf("[DPW BT] server internal error.  please contact server administrator.\n");
		ret = DPW_BT_ERROR_SERVER_TIMEOUT;
		break;
	case DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED:	// HTTPサーバのリクエスト拒否 
	case DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED:		// COMMON層: トークンの有効期限切れ
		OS_TPrintf("[DPW BT] server is now heavy.\n");
		ret = DPW_BT_ERROR_SERVER_TIMEOUT;
		break;
	default:
		DPW_TASSERTMSG(FALSE, "illigal ghttp error: %d", error);
		ret = DPW_BT_ERROR_FATAL;
		break;
	}
	
	// FATALエラーでない場合
	if (ret != DPW_BT_ERROR_FATAL) {
#ifdef _NITRO
		// NitroWiFiのレイヤーで無線が切れていないかチェックする
		if (WCM_GetPhase() != WCM_PHASE_DCF) {
			OS_TPrintf("[DPW BT] disconnected from access point.\n");
			ret = DPW_BT_ERROR_DISCONNECTED;
		}
#endif
		// DWCのエラー状態をクリアする
		DWC_ClearError();
	}
	
	return ret;
}

#ifndef SDK_FINALROM
static void Dpwi_Db_GhttpCopleteCallback(const char* buf, int len, DWCGHTTPResult result, void* param) {
#pragma unused(buf, len, param)
	
	db_ghttp_flag = result;
}
#endif
