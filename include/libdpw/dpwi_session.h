/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpwi_session.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	session manager
	
	@author	Yuki Hayashi(hayashi_yuki@nintendo.co.jp)
	
	@version
		@li
*/

#ifndef _DPWI_COMMON_SESSION_H_
#define _DPWI_COMMON_SESSION_H_

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/

//!< セッションステータス
typedef enum{
	DPWI_COMMON_SESSION_STATE_CANCELED,			//!< キャンセル
	DPWI_COMMON_SESSION_STATE_ERROR,			//!< エラー発生<
	DPWI_COMMON_SESSION_STATE_INITIAL,			//!< 初期状態
	DPWI_COMMON_SESSION_STATE_REQUEST,			//!< リクエスト発行
	DPWI_COMMON_SESSION_STATE_GETTING_TOKEN,	//!< トークン取得中
	DPWI_COMMON_SESSION_STATE_GOT_TOKEN,		//!< トークン取得完了
	DPWI_COMMON_SESSION_STATE_SENDING_DATA,		//!< データ送信中
	DPWI_COMMON_SESSION_STATE_COMPLETED			//!< 完了
}DpwiSessionState;

//!< 関数返り値
typedef enum{

	DPWI_COMMON_SESSION_SUCCESS,				//!< 正常終了
	DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED,	//!< 未初期化
	DPWI_COMMON_SESSION_ERROR_NOMEMORY			//!< メモリー不足

}DpwiSessionResult;

typedef enum{

	DPWI_COMMON_SESSION_ERROR_IN_ERROR,				//!<  0: エラー発生中 
	DPWI_COMMON_SESSION_ERROR_INVALID_POST,			//!<  1: 無効な送信 
	DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY,	//!<  2: メモリ不足 
	DPWI_COMMON_SESSION_ERROR_INVALID_FILE_NAME,	//!<  3: 無効なファイル名 
	DPWI_COMMON_SESSION_ERROR_INVALID_BUFFER_SIZE,	//!<  4: 無効なバッファサイズ 
	DPWI_COMMON_SESSION_ERROR_INVALID_URL,			//!<  5: 無効なURL
	DPWI_COMMON_SESSION_ERROR_UNSPECIFIED_ERROR,	//!<  6: その他のエラー

	DPWI_COMMON_SESSION_ERROR_SUCCESS,				//!<  7: ファイル取得成功 
	DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY,		//!<  8: メモリ割り当て失敗 
	DPWI_COMMON_SESSION_ERROR_BUFFER_OVERFLOW,		//!<  9: 供給されたバッファが小さすぎるため、ファイルの取得失敗 
	DPWI_COMMON_SESSION_ERROR_PARSE_URL_FAILED,		//!< 10: URL解析エラー 
	DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED,	//!< 11: ホスト名検索失敗 
	DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED,		//!< 12: ソケットの作成、初期化、読み出し、書き込み失敗 
	DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED,		//!< 13: HTTPサーバへの接続失敗 
	DPWI_COMMON_SESSION_ERROR_BAD_RESPONSE,			//!< 14: HTTPサーバからのレスポンスの解析エラー 
	DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED,		//!< 15: HTTPサーバのリクエスト拒否 
	DPWI_COMMON_SESSION_ERROR_UNAUTHORIZED,			//!< 16: ファイル取得未許可 
	DPWI_COMMON_SESSION_ERROR_FORBIDDEN,			//!< 17: HTTPサーバのファイル送信拒否 
	DPWI_COMMON_SESSION_ERROR_FILE_NOT_FOUND,		//!< 18: HTTPサーバ上のファイル検索失敗 
	DPWI_COMMON_SESSION_ERROR_SERVER_ERROR,			//!< 19: HTTPサーバ内部エラー 
	DPWI_COMMON_SESSION_ERROR_FILE_WRITE_FAILED,	//!< 20: ローカルファイルへの書き込みエラー 
	DPWI_COMMON_SESSION_ERROR_FILE_READ_FAILED,		//!< 21: ローカルファイルからの読み出しエラー 
	DPWI_COMMON_SESSION_ERROR_FILE_INCOMPLETE,		//!< 22: ダウンロードの中断 
	DPWI_COMMON_SESSION_ERROR_FILE_TOO_BIG,			//!< 23: ファイルが大きすぎるためダウンロード不可能 
	DPWI_COMMON_SESSION_ERROR_ENCRYPTION_ERROR,		//!< 24: 暗号化エラー 
	DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR,			//!< 25: メモリ割り当て失敗 

	DPWI_COMMON_SESSION_ERROR_CHECKSUM,				//!< 26: COMMON層: チェックサムの不一致
	DPWI_COMMON_SESSION_ERROR_PID,					//!< 27: COMMON層: PIDの不一致
	DPWI_COMMON_SESSION_ERROR_DATA_LENGTH, 			//!< 28: COMMON層: データの長さが不正
	DPWI_COMMON_SESSION_ERROR_TOKEN_NOT_FOUND,		//!< 29: COMMON層: トークンがない
	DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED,		//!< 30: COMMON層: トークンの有効期限切れ
	DPWI_COMMON_SESSION_ERROR_INCORRECT_HASH,		//!< 31: COMMON層: ハッシュが合わない
	DPWI_COMMON_SESSION_ERROR_BUFFER_OVER			//!< 32: COMMON層: 受信バッファをオーバーした

}DpwiHttpError;

/*-----------------------------------------------------------------------*
					関数プロトタイプ宣言
 *-----------------------------------------------------------------------*/

void DpwiSessionInitialize( void );
void DpwiSessionShutdown( void );
void DpwiSessionCancel( void );
DpwiSessionState DpwiSessionThink( void );
DpwiSessionResult DpwiSessionRequest(	const u8* url,
										int pid,
										const void* data,
										int len,
										u8* resbuf,
										int buflen );
DpwiHttpError DpwiGetLastError( void );
int DpwiGetResponseSize( void );


#ifdef __cplusplus
}
#endif

#endif
