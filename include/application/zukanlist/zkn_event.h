//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event.h
 *	@brief		アプリケーション変更　図鑑終了などのイベント管理
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __ZKN_EVENT_H__
#define __ZKN_EVENT_H__

#undef GLOBAL
#ifdef	__ZKN_EVENT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

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
//		イベント関数に渡される構造体
//=====================================
typedef struct {
	int seq;
	void* p_work;			// イベント内部ワーク
	void* p_data;			// イベント外部から受け取りデータ
} ZKN_EVENT_WORK;

//----------------------------------------------------------------------------
/**
 *
 *	@brief		イベント関数ポインタ
 *
 *	@param		ワーク
 *
 *	@retval		TRUE	イベント終了
 *	@retval		FALSE	イベント続行
 *
 *
 */
//-----------------------------------------------------------------------------
typedef BOOL (*ZKN_EVENT_FUNC)( ZKN_EVENT_WORK*  p_work );


//-------------------------------------
//		イベント管理構造体
//=====================================
typedef struct {
	int key_msk;			// イベント実行キーマスク
	ZKN_EVENT_FUNC func;	// 実行イベント関数
	ZKN_EVENT_WORK work;	// イベントワーク
} ZKN_EVENT_DATA;


//-------------------------------------
//		イベント管理システム
//=====================================
typedef struct _ZKN_EVENT_SYS*			ZKN_EVENT_SYS_PTR;
typedef const struct _ZKN_EVENT_SYS*	CONST_ZKN_EVENT_SYS_PTR;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_EVENT_SYS_PTR ZKN_EVENT_MemoryAlloc( int heap );
GLOBAL void ZKN_EVENT_Init( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* p_event_data, int event_num );
GLOBAL const ZKN_EVENT_DATA* ZKN_EVENT_Main( ZKN_EVENT_SYS_PTR event, int event_key );
GLOBAL BOOL ZKN_EVENT_DoCheck( ZKN_EVENT_SYS_PTR event );


#undef	GLOBAL
#endif		// __ZKN_EVENT_H__

