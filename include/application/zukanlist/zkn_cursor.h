//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_cursor.h
 *	@brief		図鑑cursor動作システム
 *	@author		tomoya takahashi
 *	@data		2006.03.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_CURSOR_H__
#define __ZKN_CURSOR_H__

#undef GLOBAL
#ifdef	__ZKN_CURSOR_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	動作ID
//=====================================
enum{
	ZKN_CURSOR_MOVE_NORMAL,		// 通常処理
	ZKN_CURSOR_MOVE_STOP,		// ストップさせる
	ZKN_CURSOR_MOVE_SKIP,		// スキップさせる
};

//-------------------------------------
//	動作コマンド
//=====================================
enum{
	ZKN_CURSOR_CONT_ADD_X,		// X方向移動	
	ZKN_CURSOR_CONT_ADD_Y,		// Y方向移動	
	ZKN_CURSOR_CONT_SET_X,		// X方向設定	
	ZKN_CURSOR_CONT_SET_Y,		// Y方向設定	
	ZKN_CURSOR_CONT_SET_CONTID,	// 管理IDの位置にカーソルを移動
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	cursor1データ
//=====================================
typedef struct {
	int x;			// X座標
	int y;			// Y座標
	int size_x;		// Xサイズ
	int size_y;		// Yサイズ
	int movex_id;	// X方向動作ID
	int movey_id;	// Y方向動作ID
	int cont_id;	// ユーザー管理ID
} ZKN_CURSOR_ONEDATA;

// 管理システム
typedef struct _ZKN_CURSOR ZKN_CURSOR;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_CURSOR* ZKN_CURSOR_Alloc( int heap );
GLOBAL void ZKN_CURSOR_Free( ZKN_CURSOR* p_cursor );

GLOBAL void ZKN_CURSOR_Init( ZKN_CURSOR* p_cursor, const ZKN_CURSOR_ONEDATA* cp_data, int max_x, int max_y );
GLOBAL void ZKN_CURSOR_Cont( ZKN_CURSOR* p_cursor, int cont, int param );
GLOBAL int ZKN_CURSOR_GetContID( const ZKN_CURSOR* cp_cursor );
GLOBAL void ZKN_CURSOR_GetMat( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y );
GLOBAL void ZKN_CURSOR_GetSize( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y );

GLOBAL void ZKN_CURSOR_SetOneData( ZKN_CURSOR_ONEDATA* p_data, int x, int y, int size_x, int size_y, int movex_id, int movey_id, int cont_id );


//　描画関係
enum{
	ZKN_CURSOR_MAT_TOP_LEFT,
	ZKN_CURSOR_MAT_TOP_RIGHT,
	ZKN_CURSOR_MAT_BOTTOM_LEFT,
	ZKN_CURSOR_MAT_BOTTOM_RIGHT,
	ZKN_CURROS_MAT_RECT_NUM
};
GLOBAL void ZKN_CURSOR_GetRectMat( const ZKN_CURSOR* cp_cursor, int way, int* p_x, int* p_y );


//-----------------------------------------------------------------------------
/**
 *			汎用関数
 */
//-----------------------------------------------------------------------------
GLOBAL void ZKN_CURSOR_UTIL_GetRectMat( int way, int* p_x, int* p_y, int def_x, int def_y, int size_x, int size_y );

#undef	GLOBAL
#endif		// __ZKN_CURSOR_H__

