/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpw_tr.c

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
		@li Dpw_Tr_Data::mail を削除し、 Dpw_Tr_Data::postData へ含めました。
		@li Dpw_Tr_PokemonData の大きさを172バイトに変更しました。
		@li ::DpwTrError で、NGワードに関するエラーを細分化しました。
		@li Dpw_Tr_Db_ShuffleServerData() を追加しました。
	@version beta1	(2006/3/17)
		@li 初版をリリースしました。
*/

#ifdef _NITRO
#include <nitroWiFi/socl.h>
#endif

#include "include/libdpw/dpw_tr.h"
#include "include/libdpw/dpwi_session.h"
#include "include/libdpw/dpwi_assert.h"

/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/

#ifdef DPW_SERVER_PUBLIC
#define TR_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"
#else
#ifdef DPW_SERVER_SUB
#define TR_SERVER_URL		"http://kiyoshi.servebeer.com/web/"
#else
#define TR_SERVER_URL		"http://sdkdev.gamespy.com/games/pokemondpds/web/"
#endif
#endif
//#define TR_SERVER_URL		"http://sdkdev.gamespy.com/games/mariokartds/web/"
//#define TR_SERVER_URL		"http://ishikawa.servebeer.com/web/"
//#define TR_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"

#ifdef _NITRO
// 構造体が想定のサイズとなっているかチェック
SDK_COMPILER_ASSERT(sizeof(Dpw_Tr_Data) == 292);
#endif

#define TR_URL_UPLOAD	((const unsigned char *)TR_SERVER_URL "worldexchange/post.asp")
#define TR_URL_UPLOADFINISH	((const unsigned char *)TR_SERVER_URL "worldexchange/post_finish.asp")
#define TR_URL_DOWNLOAD	((const unsigned char *)TR_SERVER_URL "worldexchange/get.asp")
#define TR_URL_GETUPLOADRESULT	((const unsigned char *)TR_SERVER_URL "worldexchange/result.asp")
#define TR_URL_DELETE	((const unsigned char *)TR_SERVER_URL "worldexchange/delete.asp")
#define TR_URL_RETURN	((const unsigned char *)TR_SERVER_URL "worldexchange/return.asp")
#define TR_URL_DOWNLOADMATCHDATA ((const unsigned char *)TR_SERVER_URL "worldexchange/search.asp")
#define TR_URL_TRADE	((const unsigned char *)TR_SERVER_URL "worldexchange/exchange.asp")
#define TR_URL_TRADEFINISH	((const unsigned char *)TR_SERVER_URL "worldexchange/exchange_finish.asp")
#define TR_URL_GETSERVERSTATE ((const unsigned char *)TR_SERVER_URL "worldexchange/info.asp")
#define TR_URL_INIT	((const char *)TR_SERVER_URL "worldexchange/init.asp")
#define TR_URL_UPDATE ((const char *)TR_SERVER_URL "worldexchange/update.asp")
#define TR_URL_SHUFFLE ((const char *)TR_SERVER_URL "worldexchange/shuffle.asp")

#define DB_HTTP_FLAG_NOT_COMPLETED	(-1)

#define TR_RESPONSE_SUCCESS	(1)
#define TR_RESPONSE_ILLIGAL_REQUEST	(2)
#define TR_RESPONSE_TIMEOUT	(3)
#define TR_RESPONSE_NOT_EXCHANGED (4)
#define TR_RESPONSE_NO_DATA (5)
#define TR_RESPONSE_STOP_SERVICE (6)
#define TR_RESPONSE_SERVER_FULL (7)
#define TR_RESPONSE_NG_POKEMON_NAME (8)
#define TR_RESPONSE_NG_PARENT_NAME (9)
#define TR_RESPONSE_NG_MAIL_NAME (10)
#define TR_RESPONSE_NG_OWNER_NAME (11)
#define TR_RESPONSE_ILLEGAL_DATA (12)
#define TR_RESPONSE_CHEAT_DATA (13)
#define TR_RESPONSE_SERVER_TIMEOUT (14)

typedef enum {
	DPWi_TR_NOT_INIT,
	DPWi_TR_NORMAL,
	DPWi_TR_RROCESS_UPLOAD,
	DPWi_TR_CANCEL_UPLOAD,
	DPWi_TR_RROCESS_UPLOADFINISH,
	DPWi_TR_CANCEL_UPLOADFINISH,
	DPWi_TR_RROCESS_DOWNLOAD,
	DPWi_TR_CANCEL_DOWNLOAD,
	DPWi_TR_RROCESS_GETUPLOADRESULT,
	DPWi_TR_CANCEL_GETUPLOADRESULT,
	DPWi_TR_RROCESS_DELETE,
	DPWi_TR_CANCEL_DELETE,
	DPWi_TR_RROCESS_RETURN,
	DPWi_TR_CANCEL_RETURN,
	DPWi_TR_RROCESS_DOWNLOADMATCHDATA,
	DPWi_TR_CANCEL_DOWNLOADMATCHDATA,
	DPWi_TR_RROCESS_TRADE,
	DPWi_TR_CANCEL_TRADE,
	DPWi_TR_RROCESS_TRADEFINISH,
	DPWi_TR_CANCEL_TRADEFINISH,
	DPWi_TR_RROCESS_GETSERVERSTATE,
	DPWi_TR_CANCEL_GETSERVERSTATE,
	DPWi_TR_END_ASYNC
} DpwiTrState;

typedef struct {
	DpwiTrState state;
	s32 last_result;
	s32 pid;
	u64 friend_key;
	u8 send_buf[sizeof(Dpw_Tr_Data) + 4];
	u8 recv_buf[4];
	u8* user_recv_buf;
} DpwiTrCtrl;

/*-----------------------------------------------------------------------*
					関数プロトタイプ宣言
 *-----------------------------------------------------------------------*/

void Dpw_Tr_Init(s32 pid, u64 friend_key);
void Dpw_Tr_Main(void);
void Dpw_Tr_End(void);
BOOL Dpw_Tr_IsAsyncEnd(void);
s32 Dpw_Tr_GetAsyncResult(void);
void Dpw_Tr_UploadAsync(const Dpw_Tr_Data* data);
void Dpw_Tr_UploadFinishAsync(void);
void Dpw_Tr_DownloadAsync(Dpw_Tr_Data* data);
void Dpw_Tr_GetUploadResultAsync(Dpw_Tr_Data* data);
void Dpw_Tr_DeleteAsync(void);
void Dpw_Tr_ReturnAsync(void);
void Dpw_Tr_CancelAsync(void);
void Dpw_Tr_DownloadMatchDataAsync(const Dpw_Tr_PokemonSearchData* searchData, s32 maxNum, Dpw_Tr_Data* downloadData);
void Dpw_Tr_TradeAsync(s32 id, const Dpw_Tr_Data* uploadData, Dpw_Tr_Data* downloadData);
void Dpw_Tr_TradeFinishAsync(void);
void Dpw_Tr_GetServerStateAsync(void);
static BOOL Dpwi_Tr_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize );
static DpwTrError Dpwi_Tr_HandleCommonError(DpwiHttpError error);
static void Dpwi_Db_GhttpCopleteCallback(const char* buf, int len, DWCGHTTPResult result, void* param);

/*-----------------------------------------------------------------------*
					グローバル変数定義
 *-----------------------------------------------------------------------*/

static DpwiTrCtrl dpw_tr;
static int db_ghttp_flag;

/*-----------------------------------------------------------------------*
					グローバル関数定義
 *-----------------------------------------------------------------------*/

/*!
	Dpw_Tr ライブラリを初期化します。全てのDpw_Tr の付く関数を実行する前にコールします。
	
	GSプロファイルIDは、 DWC_LoginAsync() 関数のコールバックで取得できる値で、サーバー側で一意にクライアント
	を判別するための値です。
	
	この関数をコールする際は、DWC ライブラリのインターネット接続関数でネットワークに接続してから行ってくだ
	さい。ただし、ログインを行っている必要はありません。
	
	@param[in] pid	自分のGSプロファイルID
	@param[in] friend_key	自分のフレンドキー。DWC_CreateFriendKey() で取得できます。
*/
void Dpw_Tr_Init(s32 pid, u64 friend_key) {
	
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NOT_INIT, "dpw tr is already initialized.\n");
	
	dpw_tr.state = DPWi_TR_NORMAL;
	dpw_tr.last_result = 0;
	dpw_tr.pid = pid;
	dpw_tr.friend_key = friend_key;
}

/*!
	毎ゲームフレーム呼びだし、処理を進めます。
	
	利便性のため、この関数は常に呼び出すことができます。未初期化状態では何も行いません。
*/
void Dpw_Tr_Main(void) {
	
	switch (dpw_tr.state) {
	case DPWi_TR_NOT_INIT:
		break;
	case DPWi_TR_NORMAL:
		break;
	case DPWi_TR_RROCESS_UPLOAD:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_SERVER_FULL:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_FULL;
				break;
			case TR_RESPONSE_ILLEGAL_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_ILLEGAL_DATA;
				break;
			case TR_RESPONSE_CHEAT_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_CHEAT_DATA;
				break;
			case TR_RESPONSE_NG_POKEMON_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_POKEMON_NAME;
				break;
			case TR_RESPONSE_NG_PARENT_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_PARENT_NAME;
				break;
			case TR_RESPONSE_NG_MAIL_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_MAIL_NAME;
				break;
			case TR_RESPONSE_NG_OWNER_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_OWNER_NAME;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_UPLOADFINISH:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_NO_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_DOWNLOAD:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Tr_Data)) {
				dpw_tr.last_result = 0;
			} else {
				switch (dpw_tr.user_recv_buf[0]) {
				case TR_RESPONSE_NO_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
					break;
				case TR_RESPONSE_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
					break;
				case TR_RESPONSE_SERVER_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
					dpw_tr.last_result = DPW_TR_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_GETUPLOADRESULT:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Tr_Data)) {
				dpw_tr.last_result = 1;
			} else {
				switch (dpw_tr.user_recv_buf[0]) {
				case TR_RESPONSE_NO_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
					break;
				case TR_RESPONSE_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
					break;
				case TR_RESPONSE_NOT_EXCHANGED:
					dpw_tr.last_result = 0;
					break;
				case TR_RESPONSE_SERVER_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
					dpw_tr.last_result = DPW_TR_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_DELETE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_NO_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_RETURN:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_NO_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_DOWNLOADMATCHDATA:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			{
				int response_size = DpwiGetResponseSize();
				
				if (response_size >= sizeof(Dpw_Tr_Data)) {
					// 帰ってきたサイズがsizeof(Dpw_Tr_Data)以上のときは、データが帰ってきている
					dpw_tr.last_result = (s32)(DpwiGetResponseSize() / sizeof(Dpw_Tr_Data));
				} else if (response_size == 0) {
					// 帰ってきたサイズが0のときは、見つからなかった
					dpw_tr.last_result = 0;
				} else {
					// それ以外のときはサーバーからのレスポンスコードによる
					switch (dpw_tr.user_recv_buf[0]) {
					case TR_RESPONSE_SERVER_TIMEOUT:
						dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
						break;
					default:
						DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
						dpw_tr.last_result = DPW_TR_ERROR_FATAL;
						break;
					}
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_TRADE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Tr_Data)) {
				dpw_tr.last_result = 0;
			} else {
				switch (dpw_tr.user_recv_buf[0]) {
				case TR_RESPONSE_ILLIGAL_REQUEST:
					dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
					break;
				case TR_RESPONSE_ILLEGAL_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_ILLEGAL_DATA;
					break;
				case TR_RESPONSE_CHEAT_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_CHEAT_DATA;
					break;
				case TR_RESPONSE_NG_POKEMON_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_POKEMON_NAME;
					break;
				case TR_RESPONSE_NG_PARENT_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_PARENT_NAME;
					break;
				case TR_RESPONSE_NG_MAIL_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_MAIL_NAME;
					break;
				case TR_RESPONSE_NG_OWNER_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_OWNER_NAME;
					break;
				case TR_RESPONSE_SERVER_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
					dpw_tr.last_result = DPW_TR_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_TRADEFINISH:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_GETSERVERSTATE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = DPW_TR_STATUS_SERVER_OK;
				break;
			case TR_RESPONSE_STOP_SERVICE:
				dpw_tr.last_result = DPW_TR_STATUS_SERVER_STOP_SERVICE;
				break;
			case TR_RESPONSE_SERVER_FULL:
				dpw_tr.last_result = DPW_TR_STATUS_SERVER_FULL;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_CANCEL_UPLOAD:
	case DPWi_TR_CANCEL_UPLOADFINISH:
	case DPWi_TR_CANCEL_DOWNLOAD:
	case DPWi_TR_CANCEL_GETUPLOADRESULT:
	case DPWi_TR_CANCEL_DELETE:
	case DPWi_TR_CANCEL_RETURN:
	case DPWi_TR_CANCEL_DOWNLOADMATCHDATA:
	case DPWi_TR_CANCEL_TRADE:
	case DPWi_TR_CANCEL_TRADEFINISH:
	case DPWi_TR_CANCEL_GETSERVERSTATE:
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_CANCEL;
		DpwiSessionShutdown();
		break;
	case DPWi_TR_END_ASYNC:
		break;
	}
}

/*!
	メモリの開放など終了処理を行います。
	
	この関数は、非同期処理を実行しているときにはコールすることができません。
	Dpw_Tr_IsAsyncEnd() で非同期処理の終了を確認してからコールしてください。
*/
void Dpw_Tr_End(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is running.\n");
	
	dpw_tr.state = DPWi_TR_NOT_INIT;
}

/*!
	Dpw_Trライブラリの非同期処理が終了しているか否かを返します。
	
	関数名に「Async」が付く関数をコールした際は、この関数を定期的にコールして、終了を確認してください。
	
	@retval TRUE	非同期処理が終了している
	@retval FALSE	非同期処理が終了していない
*/
BOOL Dpw_Tr_IsAsyncEnd(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	
	switch (dpw_tr.state) {
	case DPWi_TR_NORMAL:
		return TRUE;
		break;
	case DPWi_TR_END_ASYNC:
		dpw_tr.state = DPWi_TR_NORMAL;
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}

/*!
	直前の非同期処理の結果を取得します。
	Bpw_Tr_IsAsyncEnd() で終了を確認してからコールしてください。
	
	非同期処理を行った場合は、必ずこの関数で結果（特にエラーが起こっていないか）を確認してください。
	エラーの種類は非同期処理によって異なりますが、以下のエラーは共通です。
	
	@li ::DPW_TR_ERROR_SERVER_TIMEOUT
	@li ::DPW_TR_ERROR_CANCEL
	@li ::DPW_TR_ERROR_FATAL
	@li ::DPW_TR_ERROR_DISCONNECTED
	@li ::DPW_TR_ERROR_FAILURE
	
	@return	非同期処理の結果。負の値はエラーを示し、 ::DpwTrError の値が返ります。
*/
s32 Dpw_Tr_GetAsyncResult(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	
	return dpw_tr.last_result;
}

/*!
	ポケモンデータを預ける処理を開始します。
	
	成功した場合は、 Dpw_Tr_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_SERVER_FULL		： サーバーの容量オーバーです。
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		： 以前預けたデータがタイムアウトしています。タマゴを返してください。
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	： サーバーに既にデータがあります。 Dpw_Tr_DownloadAsync() で確認してください。
	@li ::DPW_TR_ERROR_ILLEGAL_DATA		： アップロードされたデータが壊れています。
	@li ::DPW_TR_ERROR_CHEAT_DATA		： アップロードされたデータが不正です。
	@li ::DPW_TR_ERROR_NG_POKEMON_NAME	： アップロードされたポケモンの名前がNGワードを含んでいます。
	@li ::DPW_TR_ERROR_NG_PARENT_NAME	： アップロードされたポケモンの親の名前がNGワードを含んでいます。
	@li ::DPW_TR_ERROR_NG_MAIL_NAME		： アップロードされたメールの名前がNGワードを含んでいます。
	@li ::DPW_TR_ERROR_NG_OWNER_NAME	： アップロードされた主人公名がNGワードを含んでいます。
	
	@param[in] data	アップロードするデータ。関数内でコピーしますので、静的に保持する必要はありません。
	
	@sa Dpw_Tr_UploadFinishAsync()
*/
void Dpw_Tr_UploadAsync(const Dpw_Tr_Data* data) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(data);
	
	memcpy(&dpw_tr.send_buf[0], data, sizeof(Dpw_Tr_Data));
	
	// セッション初期化
	DpwiSessionInitialize();

	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_UPLOAD, dpw_tr.send_buf, sizeof(Dpw_Tr_Data), dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_UPLOAD;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Tr_UploadAsync()でアップロードしたサーバー上のデータを有効にします。
	
	成功した場合、 Dpw_Tr_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_NO_DATA			： サーバーにデータが存在しません。データを復元してください。
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		： 以前預けたデータがタイムアウトしています。タマゴを返してください。
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	： サーバーに既にデータがあります。 Dpw_Tr_DownloadAsync() で確認してください。
	
	@sa Dpw_Tr_UploadAsync()
*/
void Dpw_Tr_UploadFinishAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// 自分のフレンドキーを送る
	memcpy(&dpw_tr.send_buf[0], &dpw_tr.friend_key, 8);
	
	// セッション初期化
	DpwiSessionInitialize();

	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_UPLOADFINISH, dpw_tr.send_buf, 8, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_UPLOADFINISH;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	自分が最後に預けたデータを取得します。
	
	成功した場合、 Dpw_Tr_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_NO_DATA			： サーバーにデータが存在しません。データを復元してください。
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		： 以前預けたデータがタイムアウトしています。タマゴを返してください。
	
	サーバーによって交換された後でも取得できます。
	Dpw_Tr_DeleteAsync() を実行した後は取得できません。
	
	@param[out] data	ダウンロードしたデータを記録するバッファ
*/
void Dpw_Tr_DownloadAsync(Dpw_Tr_Data* data) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(data);
	
	dpw_tr.user_recv_buf = (u8*)data;
	
	// セッション初期化
	DpwiSessionInitialize();
	
	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_DOWNLOAD, dpw_tr.send_buf, 0, data, sizeof(Dpw_Tr_Data))) {
		dpw_tr.state = DPWi_TR_RROCESS_DOWNLOAD;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	以前に預けたデータが交換されたかをサーバーに問い合わせ、交換されていれば
	交換されたデータのダウンロード処理を行います。
	
	交換が不成立なら0が、交換成立ならば1が Dpw_Tr_GetAsyncResult() で返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_NO_DATA			： サーバーにデータが存在しません。データを復元してください。
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		： 以前預けたデータがタイムアウトしています。タマゴを返してください。
	
	サーバーにて交換されるデータは、 Dpw_Tr_Data 型の以下のメンバです。それ以外は変更されません。
	
	@li Dpw_Tr_PokemonData postData;
	@li u8 gender;
	@li u16 name[DPW_TR_NAME_SIZE];
	@li u16 trainerID;
	@li u8 countryCode;
	@li s16 localCode;
	@li u8 trainerType;
	@li u8 versionCode;
	
	@param[out] data	ダウンロードしたデータを記録するバッファ
*/
void Dpw_Tr_GetUploadResultAsync(Dpw_Tr_Data* data) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(data);
	
	dpw_tr.user_recv_buf = (u8*)data;

	// セッション初期化
	DpwiSessionInitialize();
	
	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_GETUPLOADRESULT, dpw_tr.send_buf, 0, data, sizeof(Dpw_Tr_Data))) {
		dpw_tr.state = DPWi_TR_RROCESS_GETUPLOADRESULT;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	すでにアップロードされているデータの削除を行います。
	この関数は、交換済みのデータを削除する場合にのみ使用してください。
	
	成功した場合、 Dpw_Tr_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_NO_DATA			： サーバーにデータが存在しません。データを復元してください。
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		： 以前預けたデータがタイムアウトしています。タマゴを返してください。
*/
void Dpw_Tr_DeleteAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// セッション初期化
	DpwiSessionInitialize();
	
	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_DELETE, dpw_tr.send_buf, 0, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_DELETE;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	すでにアップロードされているデータの削除を行います。
	この関数は、サーバー上のデータが交換されていない場合のみ削除に成功します。
	
	成功した場合、 Dpw_Tr_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_NO_DATA			： サーバーにデータが存在しません。データを復元してください。
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		： 以前預けたデータがタイムアウトしています。タマゴを返してください。
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	： データが交換済みだったため、削除に失敗しました。 Dpw_Tr_DownloadAsync() で確認してください。
*/
void Dpw_Tr_ReturnAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// セッション初期化
	DpwiSessionInitialize();
	
	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_RETURN, dpw_tr.send_buf, 0, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_RETURN;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Trライブラリで現在行われている非同期処理をキャンセルします。
	
	キャンセルした場合、 Dpw_Tr_GetAsyncResult() の返値は DPW_TR_ERROR_CANCEL となります。
	
	既に通信が終了していることもありますので、キャンセルは常に成功するとは限りません。
	キャンセルできたかどうかは、 Dpw_Tr_GetAsyncResult() の返値が DPW_TR_ERROR_CANCEL となっているかで判断してください。
	
	Dpw_Tr_CancelAsync() 自体も非同期処理を行いますが、これをキャンセルすることはできません。
*/
void Dpw_Tr_CancelAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	
	switch (dpw_tr.state) {
	case DPWi_TR_RROCESS_UPLOAD:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_UPLOAD;
		break;
	case DPWi_TR_RROCESS_UPLOADFINISH:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_UPLOADFINISH;
		break;
	case DPWi_TR_RROCESS_DOWNLOAD:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_DOWNLOAD;
		break;
	case DPWi_TR_RROCESS_GETUPLOADRESULT:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_GETUPLOADRESULT;
		break;
	case DPWi_TR_RROCESS_DELETE:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_DELETE;
		break;
	case DPWi_TR_RROCESS_RETURN:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_RETURN;
		break;
	case DPWi_TR_RROCESS_DOWNLOADMATCHDATA:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_DOWNLOADMATCHDATA;
		break;
	case DPWi_TR_RROCESS_TRADE:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_TRADE;
		break;
	case DPWi_TR_RROCESS_TRADEFINISH:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_TRADEFINISH;
		break;
	case DPWi_TR_RROCESS_GETSERVERSTATE:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_GETSERVERSTATE;
		break;
	default:
		break;
	}
}

/*!
	欲しいポケモンデータと合致したデータのダウンロードを開始します。
	
	成功した場合は Dpw_Tr_GetAsyncResult() でダウンロードされたデータ数(0-7)が返されます。
	エラーが起こった場合は、共通のエラーのいずれかが返されます。
	
	@param[in] searchData	検索するポケモンのデータ。関数内でコピーしますので、静的に保持する必要はありません。
	@param[in] maxNum	ダウンロードするポケモンデータの最大数(7まで)
	@param[out] downloadData	ダウンロードしたデータを記録するバッファ。maxNumで指定した数以上のサイズを用意してください。
*/
void Dpw_Tr_DownloadMatchDataAsync(const Dpw_Tr_PokemonSearchData* searchData, s32 maxNum, Dpw_Tr_Data* downloadData) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(searchData);
	DPW_MINMAX_TASSERT(maxNum, 1, 7);
	DPW_NULL_TASSERT(downloadData);
	
	dpw_tr.user_recv_buf = (u8*)downloadData;
	
	// セッション初期化
	DpwiSessionInitialize();
	
	memcpy(&dpw_tr.send_buf[0], searchData, sizeof(Dpw_Tr_PokemonSearchData));
	dpw_tr.send_buf[sizeof(Dpw_Tr_PokemonSearchData)] = (u8)maxNum;
	
	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_DOWNLOADMATCHDATA, dpw_tr.send_buf,
								   sizeof(Dpw_Tr_PokemonSearchData) + 1, downloadData, (int)sizeof(Dpw_Tr_Data)*maxNum))
	{
		dpw_tr.state = DPWi_TR_RROCESS_DOWNLOADMATCHDATA;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	サーバー上のid のデータと交換を開始します。
	
	uploadDataとdownloadDataには同じポインタを与えることができます。
	
	成功した場合、 Dpw_Tr_GetAsyncResult() で0が返され、downloadDataに交換したデータが入ります。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	： トレードが失敗しました。トレードを行う前の状態に戻してください。
	@li ::DPW_TR_ERROR_ILLEGAL_DATA		： アップロードされたデータが壊れています。
	@li ::DPW_TR_ERROR_CHEAT_DATA		： アップロードされたデータが不正です。
	@li ::DPW_TR_ERROR_NG_POKEMON_NAME	： アップロードされたポケモンの名前がNGワードを含んでいます。
	@li ::DPW_TR_ERROR_NG_PARENT_NAME	： アップロードされたポケモンの親の名前がNGワードを含んでいます。
	@li ::DPW_TR_ERROR_NG_MAIL_NAME		： アップロードされたメールの名前がNGワードを含んでいます。
	@li ::DPW_TR_ERROR_NG_OWNER_NAME	： アップロードされた主人公名がNGワードを含んでいます。
	
	@param[in] id	交換相手のID
	@param[in] uploadData	アップロードするデータ。関数内でコピーしますので、静的に保持する必要はありません。
	@param[out] downloadData	ダウンロードしたデータを記録するバッファ
	
	@sa Dpw_Tr_TradeFinish()
*/
void Dpw_Tr_TradeAsync(s32 id, const Dpw_Tr_Data* uploadData, Dpw_Tr_Data* downloadData) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(uploadData);
	DPW_NULL_TASSERT(downloadData);
	
	dpw_tr.user_recv_buf = (u8*)downloadData;
	
	// セッション初期化
	DpwiSessionInitialize();
	
	memcpy(&dpw_tr.send_buf[0], uploadData, sizeof(Dpw_Tr_Data));
//	memcpy(&((Dpw_Tr_Data*)dpw_tr.send_buf)->friend_key, &dpw_tr.friend_key, 8);
	*(s32*)(&dpw_tr.send_buf[sizeof(Dpw_Tr_Data)]) = id;
	
	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_TRADE, dpw_tr.send_buf, sizeof(Dpw_Tr_Data)+4, downloadData, sizeof(Dpw_Tr_Data))) {
		dpw_tr.state = DPWi_TR_RROCESS_TRADE;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Tr_TradeAsync() でアップロードしたサーバー上のデータを有効にします。
	
	成功した場合、 Dpw_Tr_GetAsyncResult() で0が返されます。
	エラーが起こった場合は、共通のエラーもしくは以下のエラーが返されます。
	
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	： トレードが失敗しました。トレードを行う前の状態に戻してください。
*/
void Dpw_Tr_TradeFinishAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// 自分のフレンドキーを送る
	memcpy(&dpw_tr.send_buf[0], &dpw_tr.friend_key, 8);
	
	// セッション初期化
	DpwiSessionInitialize();

	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_TRADEFINISH, dpw_tr.send_buf, 8, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_TRADEFINISH;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	サーバー状態の調査を開始します。
	
	サーバーと正常に通信できた場合は、 Dpw_Tr_GetAsyncResult() で DpwTrServerStatus の値が返されます。
	
	正常に通信できなかった場合は、 共通のエラーのいずれかが返されます。
*/
void Dpw_Tr_GetServerStateAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// セッション初期化
	DpwiSessionInitialize();

	// 通信開始
	if (Dpwi_Tr_CallSessionRequest(TR_URL_GETSERVERSTATE, dpw_tr.send_buf, 0, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_GETSERVERSTATE;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

#ifndef SDK_FINALROM
/*!
	世界通信交換のサーバ状態を初期化します。
	内部でブロックします。
	
	この関数は、デバッグ／テスト用です。FINALROMでは無効となります。
	
	@retval TRUE	初期化に成功した
	@retval FALSE	初期化に失敗した
*/
BOOL Dpw_Tr_Db_InitServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(TR_URL_INIT, Dpwi_Db_GhttpCopleteCallback, NULL);
	
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
	世界交換通信のサーバの一日一回のアップデートを行います。
	内部でブロックします。
	
	この関数は、デバッグ／テスト用です。FINALROMでは無効となります。
*/
BOOL Dpw_Tr_Db_UpdateServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(TR_URL_UPDATE, Dpwi_Db_GhttpCopleteCallback, NULL);
	
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
	世界通信交換の、預けられているポケモンが検索される順番を変更します。
	この処理は、製品版サーバーでは一日に一回行われる予定です。
	
	この関数は、デバッグ／テスト用です。FINALROMでは無効となります。
*/
BOOL Dpw_Tr_Db_ShuffleServerData(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(TR_URL_SHUFFLE, Dpwi_Db_GhttpCopleteCallback, NULL);
	
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

static BOOL Dpwi_Tr_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize) {
	
	switch (DpwiSessionRequest(url, dpw_tr.pid, data, len, (u8*)resbuf, ressize)) {
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

static DpwTrError Dpwi_Tr_HandleCommonError(DpwiHttpError error) {
	
	DpwTrError ret;
	
	OS_TPrintf("[DPW TR] ghttp error: %d\n", error);
	
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
		ret = DPW_TR_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY:	// メモリ不足 
	case DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY:		// メモリ割り当て失敗 
	case DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR: 		// メモリ割り当て失敗 
		DPW_TASSERTMSG(FALSE, "common session memory shortage.");
		ret = DPW_TR_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED:	// ホスト名検索失敗 
		OS_TPrintf("[DPW TR] dns lookup failed.\n");
		ret = DPW_TR_ERROR_FAILURE;
		break;
	case DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED:		// ソケットの作成、初期化、読み出し、書き込み失敗 
	case DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED:		// HTTPサーバへの接続失敗 
		OS_TPrintf("[DPW TR] socket error.\n");
		ret = DPW_TR_ERROR_FAILURE;
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
		OS_TPrintf("[DPW TR] server internal error.  please contact server administrator.\n");
		ret = DPW_TR_ERROR_SERVER_TIMEOUT;
		break;
	case DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED:	// HTTPサーバのリクエスト拒否 
	case DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED:		// COMMON層: トークンの有効期限切れ
		OS_TPrintf("[DPW TR] server is now heavy.\n");
		ret = DPW_TR_ERROR_SERVER_TIMEOUT;
		break;
	default:
		DPW_TASSERTMSG(FALSE, "illigal ghttp error: %d", error);
		ret = DPW_TR_ERROR_FATAL;
		break;
	}
	
	// FATALエラーでない場合
	if (ret != DPW_TR_ERROR_FATAL) {
#ifdef _NITRO
		// NitroWiFiのレイヤーで無線が切れていないかチェックする
		if (WCM_GetPhase() != WCM_PHASE_DCF) {
			OS_TPrintf("[DPW TR] disconnected from access point.\n");
			ret = DPW_TR_ERROR_DISCONNECTED;
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

