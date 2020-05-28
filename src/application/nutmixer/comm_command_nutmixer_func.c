//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		comm_command_nutmixer_func.h
 *	@brief		通信コールバック関数
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "nmix_game.h"
#include "communication/communication.h"
#include "comm_command_nutmixer.h"
#include "nmix_gameseq.h"

#define __COMM_COMMAND_NUTMIXER_FUNC_H_GLOBAL
#include "comm_command_nutmixer_func.h"


//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		通信初期化関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	通信の初期化
 */
//-----------------------------------------------------------------------------
void CommCommandNutMixerInitialize( NMIX_GAMEWORK* pWork, MYSTATUS* p_mystate )
{
	int playno;
	int i;

	// 通信状態チェック
	if( pWork->commpack_flg == NUTMIX_COMM_PACK_COMM ){
		// 通信人数取得
		pWork->comm_count = CommGetConnectNum();
	}else{
		// 非通信
		pWork->comm_count = 1;
	}
	OS_Printf( "comm_count = %d\n", pWork->comm_count );

	// 通信パックシステム動さ開始
	pWork->comm_work = NMIX_CommPack_CommandInitialize( 
			NutMixer_CommCommandTclGet(),
			NutMixer_CommCommandTblNumGet(),
			pWork,
			pWork->commpack_flg,
			pWork->heapID );


	memset( pWork->game_comm_pack.playno_netid, NUTMIXER_MEMBER_MAX, sizeof(u8) * NUTMIXER_MEMBER_MAX );
	
	if( pWork->commpack_flg == NUTMIX_COMM_PACK_COMM ){
		// プレイヤーナンバーー＞ネットID取得配列を作成
		// プレイヤーステータス取得
		playno = 0;
		for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){

			pWork->game_comm_pack.p_mystate[ i ] = CommInfoGetMyStatus( i );
			if( pWork->game_comm_pack.p_mystate[ i ] != NULL ){
				pWork->game_comm_pack.playno_netid[ playno ] = i;
				playno ++;
			}
		}
	}else{
		pWork->game_comm_pack.playno_netid[ 0 ] = 0;
		pWork->game_comm_pack.p_mystate[ 0 ] = p_mystate;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	通信の破棄
 */
//-----------------------------------------------------------------------------
void CommCommandNutMixerDest( NMIX_GAMEWORK* pWork )
{
	// 通信パックシステム破棄
	NMIX_CommPack_CommDelete( pWork->comm_work );
	pWork->comm_work = NULL;
}

//-----------------------------------------------------------------------------
/**
 *		ゲーム処理
 *		同期用
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム開始同期		子受信
 *
 *	@param	netID		接続番号
 *	@param	size		バッファサイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		システムワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameSysStart( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	OS_Printf( "親->子 ゲーム開始前処理開始\n" );
	// ゲーム前処理開始
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_BEFORE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム実処理　終了	子受信
 *
 *	@param	netID		接続番号
 *	@param	size		バッファサイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		システムワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameEnd( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	OS_Printf( "親->子 ゲーム終了\n" );
	// ゲーム実処理　終了へ
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_GAMEEND );
}

//-----------------------------------------------------------------------------
/**
 *		データ受信用
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	親からゲーム開始前情報を受け取る
 *
 *	@param	netID		接続ID
 *	@param	size		サイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		ワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameBeforeDataKo( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// バッファに格納
	memcpy( &p_game->game_comm_pack.get_ko_before_data, pBuff, size );

	// 親データを設定
	p_game->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya = p_game->game_comm_pack.get_ko_before_data.oya;

	OS_Printf( "親->子　スープα値 %d\n 方向エフェクト %d \n", p_game->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya.alpha_num, p_game->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya.rota_req_eff);


	OS_Printf( "親ー＞子 ゲーム開始前情報取得 0[%d] 1[%d] 2[%d] 3[%d] \n", 
			p_game->game_comm_pack.get_ko_before_data.before[0].nut_type,
			p_game->game_comm_pack.get_ko_before_data.before[1].nut_type,
			p_game->game_comm_pack.get_ko_before_data.before[2].nut_type,
			p_game->game_comm_pack.get_ko_before_data.before[3].nut_type );

	// ゲーム実処理開始
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_RES_LOAD );
}

//----------------------------------------------------------------------------
/**
 *	@brief	子から木の実データを取得
 *
 *	@param	netID		接続番号
 *	@param	size		バッファサイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		システムワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameBeforeData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;
	int i;
	int in_count;


	// 親のとき受け取る	
	// 親は、全て受け取ったら、子に木の実情報を転送
	if( NMIX_CommPack_CommGetCurrentID( p_game->comm_work ) == COMM_PARENT_ID ){
		// バッファに格納
		memcpy( &p_game->game_comm_pack.get_before_data[ netID ], pBuff, size );
		p_game->game_comm_pack.get_before_data_flg[ netID ] = TRUE;

		// 子に送るデータにも追加
		p_game->game_comm_pack.get_oya_ko_before_data.before[ netID ] = p_game->game_comm_pack.get_before_data[ netID ];

		OS_Printf( "子ー＞親 ゲーム開始前情報取得 netID[ %d ] nuts_data[ %d ]\n", netID, p_game->game_comm_pack.get_before_data[ netID ] );

		// 通信相手全員から来たかチェック
		in_count = 0;
		for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
			if( p_game->game_comm_pack.get_before_data_flg[ i ] == TRUE ){
				in_count ++;
			}
		}

		// 全員からきたら、ゲーム開始前情報転送
		if( in_count >= p_game->comm_count ){
			OS_Printf( "子にゲーム開始前情報転送 in_c=%d  comm_c=%d\n", in_count, p_game->comm_count );

			// 1回親の初期化データも渡す
			NMIX_DATA_OyaCommDataMake_Init( &p_game->oya_data,
					&p_game->game_comm_pack.get_oya_ko_before_data.oya, p_game->comm_count );	// 通信データ設定


			// データ転送
			NMIX_CommPack_CommSendData( CNM_MIXER_GAME_BEFOREDATA_KO,
					&p_game->game_comm_pack.get_oya_ko_before_data,
					CommNutMixerGetGameBeforeKoSize(),
					p_game->comm_work );
		}
	}

	
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲームデータを取得			親から子へ
 *
 *	@param	netID		接続番号
 *	@param	size		バッファサイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		システムワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// バッファに格納
	memcpy( &p_game->game_comm_pack.get_game_data[ netID ], pBuff, size );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム結果データを取得
 *
 *	@param	netID		接続番号
 *	@param	size		バッファサイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		システムワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameResultData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// バッファに格納
	memcpy( &p_game->game_comm_pack.get_result_data, pBuff, size );

	OS_Printf( "親ー＞子 ゲーム結果情報取得\n" );

	// 結果表示に以降
	NMIX_SetMainSeq( p_game, NMIX_GAME_MAINSEQ_RESULT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポルトデータ受信
 *
 *	@param	netID		接続番号
 *	@param	size		バッファサイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		システムワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerPorutoData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// バッファに格納
	memcpy( p_game->game_comm_pack.p_get_ko_poruto, pBuff, size );
	OS_Printf( "親ー＞子 ポルトデータ取得\n" );
}

//----------------------------------------------------------------------------
/**
 *	@brief	親から　ゲームをつづけるかを受け取る
 *
 *	@param	netID		接続ID
 *	@param	size		サイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		ワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameNextDataKo( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;

	// バッファに格納
	memcpy( &p_game->game_comm_pack.get_game_next, pBuff, size );

	OS_Printf( "親ー＞子 ゲーム終了 %d \n", p_game->game_comm_pack.get_game_next );

	
	// ゲーム処理完全　終了へ
	NMIX_SetMainSeq( p_game, NMIX_GAME_MIANSEQ_RES_RELEASE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	子からゲームをつづけたいか受け取る
 *
 *	@param	netID		接続ID
 *	@param	size		サイズ
 *	@param	pBuff		バッファ
 *	@param	pWork		ワーク
 */
//-----------------------------------------------------------------------------
void CommNutMixerGameNextData( int netID, int size, void* pBuff, void* pWork )
{
	NMIX_GAMEWORK* p_game = pWork;
	int i;
	int in_count;
	u8 send;

	// 親のとき受け取る	
	// 親は、全て受け取ったら、子に木の実情報を転送
	if( NMIX_CommPack_CommGetCurrentID( p_game->comm_work ) == COMM_PARENT_ID ){
		// バッファに格納
		memcpy( &p_game->game_comm_pack.game_next[ netID ], pBuff, size );
		p_game->game_comm_pack.get_next_data_flg[ netID ] = TRUE;

		OS_Printf( "子ー＞親 ゲーム終了データ netID[ %d ] next_data[ %d ]\n", netID, p_game->game_comm_pack.game_next[ netID ] );

		// 通信相手全員から来たかチェック
		in_count = 0;
		send = 1;	// 最初に続けるをいれておき　皆が1なら1 一人でも0なら0なので
					// ＆でチェックしていく
		for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
			if( p_game->game_comm_pack.get_next_data_flg[ i ] == TRUE ){
				send &= p_game->game_comm_pack.game_next[ i ];
				in_count ++;
			}
		}
		// 全員からきたら、ゲーム終了データ転送
		if( in_count >= p_game->comm_count ){
			OS_Printf( "子にゲーム終了データ転送 in_c=%d  comm_c=%d\n", in_count, p_game->comm_count );

			// データ転送
			NMIX_CommPack_CommSendData( CNM_MIXER_GAME_NEXT_KO,
					&send,
					CommNutMixerGetOneSize(),
					p_game->comm_work );
		}
	}
}


//-----------------------------------------------------------------------------
/**
 *			サイズ取得関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	0サイズ
 *	@return	サイズ
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetZeroSize( void )
{
	return 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	1サイズ
 *	@return	サイズ
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetOneSize( void )
{
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム前通信データ子が受け取るサイズ取得
 *	@return	サイズ
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameBeforeKoSize( void )
{
	return sizeof(NUTMIX_COMM_BEFORE_KO);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム前サイズ通信データサイズ取得
 *	@return	サイズ
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameBeforeSize( void )
{
	return sizeof(NUTMIX_GAME_BGFORE);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲームデータサイズ取得
 *	@return	サイズ
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameSize( void )
{
	return sizeof(NUTMIX_COMM_DATA);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム結果データサイズ取得
 *	@return	サイズ
 */
//-----------------------------------------------------------------------------
int CommNutMixerGetGameResultSize( void )
{
	return sizeof(NUTMIX_COMM_RESULT);
}


