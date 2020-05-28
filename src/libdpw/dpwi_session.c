/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpwi_session.c

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DPW internal session module
	
	@author	Yuki Hayashi(hayashi_yuki@nintendo.co.jp)
	
	@version
		@li
*/

#include <dwc.h>
#include "include/libdpw/dpwi_session.h"
#include "include/libdpw/dpwi_encrypt.h"

#ifdef _NITRO
#include "include/libdpw/dpwi_define.h"
#endif

#ifndef _NITRO
	#include "include/libdpw/dpwi_sha1.h"
#endif

/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/

#define HASH_LENGTH		40								// ハッシュの長さ
#define TOKEN_LENGTH	32								// トークンの長さ
#define KEY_LENGTH		20								// 秘密鍵の長さ
#define KEYTOKEN_LENGTH		(TOKEN_LENGTH + KEY_LENGTH + 1)	// 秘密鍵＋トークン

#define SECRET_KEY		"sAdeqWo3voLeC5r16DYv"			// 秘密鍵

#define COMMON_ERROR_MSG_LENGTH		22

#define COMMON_ERROR_CHECKSUM			"error: check sum      "
#define COMMON_ERROR_PID				"error: pid            "
#define COMMON_ERROR_DATA_LENGTH 		"error: data length    "
#define COMMON_ERROR_TOKEN_NOT_FOUND 	"error: token not found"
#define COMMON_ERROR_TOKEN_EXPIRED		"error: token expired  "
#define COMMON_ERROR_INCORRECT_HASH		"error: incorrect hash "

/*-----------------------------------------------------------------------*
					グローバル変数定義
 *-----------------------------------------------------------------------*/


/**
 * 
 * セッション情報を保持する構造体変数
 * 
 * [  base url ]?pid=[-----]&hash=[-----]&data=[-----------------------]
 * |                              |            |
 * |<- *request                   |<- *hash    |<- *data
 * 
 */

struct{

	DpwiSessionState	state;

	int		reqid;		//!< リクエスト識別子
	int		lasterr;	//!< ラストエラー
	int		reslen;		//!< レスポンスのデータサイズ

	int		pid;		//!< PID

	void*	srcbuf;		//!< 送信データバッファのポインタ
	int		srcbuflen;	//!< 送信データバッファのサイズ
	void*	resbuf;		//!< レスポンスデータ格納バッファのポインタ
	int		resbuflen;	//!< レスポンスデータ格納バッファのサイズ

	char*	request;	//!< リクエスト文字列
	char*	hash;		//!< リクエスト文字列中のハッシュ位置
	char*	data;		//!< リクエスト文字列中のデータ位置
	int		datasize;	//!< dataのサイズ

}g_session = { DPWI_COMMON_SESSION_STATE_ERROR, 0, 0, 0 };


static void setlasterror( int err ){

	switch( err ){
	// エラー発生中
	case DWC_GHTTP_IN_ERROR:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_IN_ERROR;
		break;
	// 無効な送信
	case DWC_GHTTP_INVALID_POST:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_POST;
		break;
	// メモリ不足
	case DWC_GHTTP_INSUFFICIENT_MEMORY:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY;
		break;
	// 無効なファイル名
	case DWC_GHTTP_INVALID_FILE_NAME:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_FILE_NAME;
		break;
	// 無効なバッファサイズ
	case DWC_GHTTP_INVALID_BUFFER_SIZE:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_BUFFER_SIZE;
		break;
	// 無効なURL
	case DWC_GHTTP_INVALID_URL:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_URL;
		break;
	// その他のエラー
	case DWC_GHTTP_UNSPECIFIED_ERROR:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_UNSPECIFIED_ERROR;
		break;
	// 成功
	default:
		g_session.lasterr = 0;
	}

}

// 完了コールバック関数
static void Completed(	const char* buf,
						int len,
						DWCGHTTPResult result,
						void* param )
{
#pragma unused(param)
	
	// GHTTPの処理を行っていないことを示すフラグを立てる
	g_session.reqid = -1;
	
	// ステートがエラーだったら終了
	//
	if( g_session.state == DPWI_COMMON_SESSION_STATE_ERROR ){

		return;

	}

	
	// HTTP通信の結果を処理
	//
	// HTTP GET 200 のレスポンスのみ処理
	// それ以外 404や500ではエラーを発生して終了する
	// 
	if ( result == DWC_GHTTP_SUCCESS ){

		switch( g_session.state ){

		// トークン取得
		//-------------------
		case DPWI_COMMON_SESSION_STATE_GETTING_TOKEN:

			// トークンのサイズが正しいかどうか
			//
			// 正しければハッシュを求め、データを暗号化して次の通信を行う準備
			// をする。
			// 
			if(len == TOKEN_LENGTH){

				//
				// メモリーをみみっちく節約する設計なのでわかりにくい・・・
				//
				int i;										// ループカウンタ
				u8* hashtmp = (u8*)(g_session.hash + 20);	// ハッシュ一時領域
				char data[KEYTOKEN_LENGTH];					// 秘密鍵＋トークン
				DpwiEncResult res;							// 暗号化結果
				const char hextbl[] = "0123456789abcdef";	// hex変換テーブル

				// 秘密鍵を格納
				strcpy( data, SECRET_KEY );

				// トークンを連結
				strncat( data, buf, (u32)len );
				
				// ハッシュ計算
				MATH_CalcSHA1((u8*)hashtmp, (const u8*)data, strlen(data));

				// パラメーター名追加
				// 
				// この時点ではrequestには"*?pid=****"まで書かれている
				// 
				strcat( g_session.request, "&hash=" );

				// hex変換
				//
				// 書き込み先はg_session.request中の"hash="の後40bytes
				// 
				for(i=0; i<20; i++){
					g_session.hash[i*2]   = hextbl[hashtmp[i] >> 4];
					g_session.hash[i*2+1] = hextbl[hashtmp[i] & 0x0f];
				}
				g_session.hash[HASH_LENGTH] = '\0';

				// URLにつなぐ
				strcat( g_session.request, "&data=" );


				// 送信データの暗号化
				// 
				// 暗号化されたデータはg_session.requestに直結される
				//
				res = DpwiEncrypt(	(u32)g_session.pid,
									(u8 *)g_session.srcbuf,
									g_session.srcbuflen,
									(u8 *)g_session.data,
									g_session.datasize );

				switch(res){

				// 成功
				case DPWI_COMMON_ENC_SUCCESS:
					break;

				// メモリー不足エラー
				case DPWI_COMMON_ENC_ERROR_NOMEMORY:
				case DPWI_COMMON_ENC_ERROR_NOBUFFER:

					// エラー
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

					return;
				}

				// 次のステートへ
				//
				// -> トークン取得完了ステート
				// 
				g_session.state = DPWI_COMMON_SESSION_STATE_GOT_TOKEN;

			}else{

				// エラー
				g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

			}

			break;


		// データ送信完了
		//-------------------
		case DPWI_COMMON_SESSION_STATE_SENDING_DATA:

			// レスポンスを取得
			//
			
			// エラーかどうかチェック
			if( len == COMMON_ERROR_MSG_LENGTH ){

				if( strncmp(buf, COMMON_ERROR_CHECKSUM, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_CHECKSUM;
					break;
				} else if (strncmp(buf, COMMON_ERROR_PID, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_PID;
					break;
				} else if (strncmp(buf, COMMON_ERROR_DATA_LENGTH, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_DATA_LENGTH;
					break;
				} else if (strncmp(buf, COMMON_ERROR_TOKEN_NOT_FOUND, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_TOKEN_NOT_FOUND;
					break;
				} else if (strncmp(buf, COMMON_ERROR_TOKEN_EXPIRED, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED;
					break;
				} else if (strncmp(buf, COMMON_ERROR_INCORRECT_HASH, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INCORRECT_HASH;
					break;
				}
			}

			// レスポンスバッファに収まるかをチェック
			// 
			if( len <= g_session.resbuflen ){

				// コピー
				memcpy(g_session.resbuf, buf, (u32)len);

				// 終了ステートへ
				g_session.state = DPWI_COMMON_SESSION_STATE_COMPLETED;

			}else{

				// レスポンスを格納するバッファサイズが足りない
				//
				// 一応書き込めるだけ書き込む
				// 全部書き込めなかったエラーは返す
				//

				// バッファサイズ分だけコピー
				memcpy(g_session.resbuf, buf, (u32)g_session.resbuflen );

				// エラーステートへ
				g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
				g_session.lasterr = DPWI_COMMON_SESSION_ERROR_BUFFER_OVER;
			}

			// レスポンスのサイズを保持
			g_session.reslen = len;

			break;

		}

	}else{

		// HTTPエラー
		//
		g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

		// エラーコードを判別
		switch ( result ){
		// メモリ割り当て失敗
		case DWC_GHTTP_OUT_OF_MEMORY:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY;
			break;
		// 供給されたバッファが小さすぎるため、ファイルの取得失敗 
		case DWC_GHTTP_BUFFER_OVERFLOW:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_BUFFER_OVERFLOW;
			break;
		// URL解析エラー
		case DWC_GHTTP_PARSE_URL_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_PARSE_URL_FAILED;
			break;
		// ホスト名検索失敗
		case DWC_GHTTP_HOST_LOOKUP_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED;
			break;
		// ソケットの作成、初期化、読み出し、書き込み失敗 
		case DWC_GHTTP_SOCKET_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED;
			break;
		// HTTPサーバへの接続失敗 
		case DWC_GHTTP_CONNECT_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED;
			break;
		// HTTPサーバからのレスポンスの解析エラー 
		case DWC_GHTTP_BAD_RESPONSE:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_BAD_RESPONSE;
			break;
		// HTTPサーバのリクエスト拒否 
		case DWC_GHTTP_REQUEST_REJECTED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED;
			break;
		// ファイル取得未許可 
		case DWC_GHTTP_UNAUTHORIZED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_UNAUTHORIZED;
			break;
		// HTTPサーバのファイル送信拒否 
		case DWC_GHTTP_FORBIDDEN:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FORBIDDEN;
			break;
		// HTTPサーバ上のファイル検索失敗 
		case DWC_GHTTP_FILE_NOT_FOUND:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FILE_NOT_FOUND;
			break;
		// HTTPサーバ内部エラー
		case DWC_GHTTP_SERVER_ERROR:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_SERVER_ERROR;
			break;
		// ダウンロードの中断
		case DWC_GHTTP_FILE_INCOMPLETE:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FILE_INCOMPLETE;
			break;
		// ファイルが大きすぎるためダウンロード不可能 
		case DWC_GHTTP_FILE_TOO_BIG:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FILE_TOO_BIG;
			break;
		// メモリーエラー
		case DWC_GHTTP_MEMORY_ERROR:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR;
			break;
		}
		
	}

}


/*!
	セッションを初期化します
	
	
*/
void DpwiSessionInitialize( void ){

	// ステータスフラグをセット
	g_session.state = DPWI_COMMON_SESSION_STATE_INITIAL;
	g_session.reqid = -1;

	// 初期化
	if ( !DWC_InitGHTTP(NULL) ){

		// GHTTPの初期化に失敗
		g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

	}

	return;

}


/*!
	リクエストを発行します
	
	セッションを確立して、データを送信し、レスポンスを受信します。
	
	@param[in]		url		スクリプトのURL
	@param[in]		pid		GameSpy Profile ID
	@param[in]		data	送信するデータ
	@param[in]		len		dataのサイズ
	@param[in]		resbuf	レスポンスを受け取るためのバッファ
	@param[in]		buflen	resbufのサイズ

	@retval	DPWI_COMMON_SESSION_SUCCESS					成功
	@retval	DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED	未初期化
	@retval	DPWI_COMMON_SESSION_ERROR_NOMEMORY			メモリー不足

*/
DpwiSessionResult DpwiSessionRequest(	const u8* url,
										int pid,
										const void* data,
										int len,
										u8* resbuf,
										int ressize ){


	// 初期化チェック
	if( g_session.state != DPWI_COMMON_SESSION_STATE_INITIAL )
		return DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED;

	// 各種変数を保持
	g_session.pid		= pid;
	g_session.srcbuf	= (void*)data;
	g_session.srcbuflen	= len;
	g_session.resbuf	= resbuf;
	g_session.resbuflen	= ressize;

	// リクエスト文字列用メモリーを確保
	// ( baseurllen + param[pid] + param[hash] + base64data + few more )
	g_session.request = (char*)DWC_Alloc( (DWCAllocType)DPWI_ALLOC,
									strlen((const char*)url)
									+ 68 + DpwiB64Size(8 + (u32)len) + 1);
	if( g_session.request == NULL )
		return DPWI_COMMON_SESSION_ERROR_NOMEMORY;

	// ベースＵＲＬとPIDをリクエストに格納
	sprintf( g_session.request, "%s?pid=%d", url, pid );

	// パラメーターのオフセットを保持
	//
	// メモリー節約のために同一バッファのポインタを保持する
	// 
	g_session.hash	= g_session.request + strlen(g_session.request)
						+ strlen("&hash=");
	g_session.data	= g_session.hash + HASH_LENGTH + strlen("&data=");
	g_session.datasize = (int)(DpwiB64Size(8 + (u32)len) + 1);


	// 開始
	g_session.state = DPWI_COMMON_SESSION_STATE_REQUEST;

	return DPWI_COMMON_SESSION_SUCCESS;
}


/*!
	非同期処理を進めます

	@return	セッションのステータス
*/
DpwiSessionState DpwiSessionThink( void ){

	BOOL result;

	switch( g_session.state ){

	// キャンセルされた
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_CANCELED:
		break;

	// エラー
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_ERROR:
		break;

	// 初期化後
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_INITIAL:
		break;

	// リクエスト準備完了
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_REQUEST:

		// トークン取得リクエスト送信
		g_session.reqid = DWC_GetGHTTPData(	g_session.request,
											Completed,
											&g_session );

		setlasterror( g_session.reqid );

		if( g_session.reqid >= 0 )
			g_session.state = DPWI_COMMON_SESSION_STATE_GETTING_TOKEN;
		else
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

		break;
	
	// トークン取得中
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_GETTING_TOKEN:

		result = DWC_ProcessGHTTP();

		if( !result ){
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
			break;
		}

		break;

	// トークン取得完了
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_GOT_TOKEN:

		// データ送信リクエスト送信
		g_session.reqid = DWC_GetGHTTPData(	g_session.request,
											Completed,
											&g_session );

		setlasterror( g_session.reqid );

		if( g_session.reqid >= 0 )
			g_session.state = DPWI_COMMON_SESSION_STATE_SENDING_DATA;
		else
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

		break;

	// データ送信中
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_SENDING_DATA:

		result = DWC_ProcessGHTTP();

		if( !result ){
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
			break;
		}

		break;

	// 処理完了
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_COMPLETED:
		break;
	}

	return g_session.state;
}


/*!
	セッションを中断します
	
	セッションを中断します
	
*/
void DpwiSessionCancel( void ){

	if( g_session.reqid >= 0 )
		DWC_CancelGHTTPRequest( g_session.reqid );

	g_session.state = DPWI_COMMON_SESSION_STATE_CANCELED;

	return;

}

/*!
	セッションを終了します
	
	セッションを終了してメモリーを解放します
	
*/
void DpwiSessionShutdown( void ){

	// メモリー開放
	if( g_session.request != NULL){
	
		DWC_Free( (DWCAllocType)DPWI_ALLOC, g_session.request, (u32)0 );
		g_session.request = NULL;

	}

	// GHTTP開放
	DWC_ShutdownGHTTP();

	// ステータスを無効にする
	g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

	return;

}


/*!
	最後のエラーを取得します
	
	
*/
DpwiHttpError DpwiGetLastError( void ){

	return (DpwiHttpError)g_session.lasterr;

}

/*!
	レスポンスのデータサイズを返します
	
	
*/
int DpwiGetResponseSize( void ){

	return g_session.reslen;

}

