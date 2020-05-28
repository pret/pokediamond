//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event.c
 *	@brief		アプリケーション変更　図鑑終了などのイベント管理
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define	__ZKN_EVENT_H_GLOBAL
#include "include/application/zukanlist/zkn_event.h"

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
//-------------------------------------
//		イベント管理システム
//=====================================
typedef struct _ZKN_EVENT_SYS{
	ZKN_EVENT_DATA* p_event_data;	// イベントデータ
	int event_num;					// イベント数
	ZKN_EVENT_DATA* p_event_do;		// 実行中のイベント
} ZKN_EVENT_SYS;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static BOOL EventDoCheck( ZKN_EVENT_SYS_PTR event );
static ZKN_EVENT_DATA* EventStartCheck( ZKN_EVENT_SYS_PTR event, int event_key );
static void EventDataSet( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* cp_event_data );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑イベントワークメモリ確保
 *
 *	@param	heap	使用ヒープ
 *
 *	@return	ワークポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_EVENT_MemoryAlloc( int heap )
{
	ZKN_EVENT_SYS_PTR event;

	event = sys_AllocMemory( heap, sizeof(ZKN_EVENT_SYS) );
	GF_ASSERT( event );
	memset( event, 0, sizeof(ZKN_EVENT_SYS) );

	return event;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑イベント初期化
 *
 *	@param	event			イベントワーク
 *	@param	p_event_data	イベントデータテーブル
 *	@param	event_num		イベントデータテーブル要素数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_Init( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* p_event_data, int event_num )
{
	GF_ASSERT( event );
	
	event->p_event_data		= p_event_data;
	event->event_num		= event_num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑イベントメイン
 *
 *	@param	event			イベントワーク
 *	@param	event_key		イベントキー
 *
 *	@return	実行中のイベントテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
const ZKN_EVENT_DATA* ZKN_EVENT_Main( ZKN_EVENT_SYS_PTR event, int event_key )
{
	ZKN_EVENT_DATA* p_event_data;
	BOOL ret;
	
	GF_ASSERT( event );

	// 実行中のものが無いときは
	// 何か実行するかチェックする
	if( EventDoCheck( event ) == FALSE ){

		// 実行開始チェック
		p_event_data = EventStartCheck( event, event_key );
		if( p_event_data ){
			EventDataSet( event, p_event_data );
		}
	}

	// 実行
	if( EventDoCheck( event ) == TRUE ){
		
		// イベント実行
		ret = event->p_event_do->func( &event->p_event_do->work );

		// 終了チェック
		if( ret == TRUE ){
			EventDataSet( event, NULL );
		}
	}

	return event->p_event_do;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベント実行中かチェック
 *
 *	@param	event	イベント
 *
 *	@retval	TRUE	イベント中
 *	@retval FALSE	イベントなし
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_DoCheck( ZKN_EVENT_SYS_PTR event )
{
	GF_ASSERT(event);

	if( event->p_event_do ){
		return TRUE;
	}

	return FALSE;
}




//-----------------------------------------------------------------------------
/**
 *			プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベント実行中かチェック
 *
 *	@param	event	イベントワーク
 *
 *	@retval	TRUE	実行中
 *	@retval	FALSE	実行していない
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL EventDoCheck( ZKN_EVENT_SYS_PTR event )
{
	if( event->p_event_do ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベント開始チェック
 *
 *	@param	event		イベントワーク
 *	@param	event_key	イベントキー
 *
 *	@return	開始するイベントデータテーブル	無いとき NULL
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* EventStartCheck( ZKN_EVENT_SYS_PTR event, int event_key )
{
	int i;		// ループ用

	for( i=0; i<event->event_num; i++ ){

		GF_ASSERT( event->p_event_data );
		
		if( event->p_event_data[ i ].key_msk & event_key ){

			return event->p_event_data + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベントデータ設定
 *
 *	@param	event			イベントワーク
 *	@param	p_event_data	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void EventDataSet( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* p_event_data )
{
	event->p_event_do = p_event_data;

	// シーケンスデータ初期化
	if( event->p_event_do ){
		event->p_event_do->work.seq = 0;
	}
}
