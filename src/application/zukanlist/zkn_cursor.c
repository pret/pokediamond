//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_cursor.c
 *	@brief		図鑑cursor動作システム
 *	@author		tomoya takahashi
 *	@data		2006.03.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "include/gflib/system.h"
#include "include/gflib/assert.h"
#include <string.h>

#define	__ZKN_CURSOR_H_GLOBAL
#include "include/application/zukanlist/zkn_cursor.h"

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
//	cursorシステム
//=====================================
typedef struct _ZKN_CURSOR {
	const ZKN_CURSOR_ONEDATA* p_data;
	int max_x;
	int max_y;
	int now_x;
	int now_y;
} ;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static int inline GetNowIdx( const ZKN_CURSOR* cp_cursor );
static int inline GetIdx( const ZKN_CURSOR* cp_cursor, int x, int y );
static void MoveXCursor( ZKN_CURSOR* p_cursor, int param );
static void MoveYCursor( ZKN_CURSOR* p_cursor, int param );

static void ZknCursorContAddX( ZKN_CURSOR* p_cursor, int param );
static void ZknCursorContAddY( ZKN_CURSOR* p_cursor, int param );
static void inline ZknCursorContSetX( ZKN_CURSOR* p_cursor, int param );
static void inline ZknCursorContSetY( ZKN_CURSOR* p_cursor, int param );
static void ZknCursorContSetContID( ZKN_CURSOR* p_cursor, int param );

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑CURSORシステムワーク確保
 *
 *	@param	heap	ヒープ
 *
 *	@return	CURSORシステムワーク
 */
//-----------------------------------------------------------------------------
ZKN_CURSOR* ZKN_CURSOR_Alloc( int heap )
{
	ZKN_CURSOR* p_cursor;

	p_cursor = sys_AllocMemory( heap, sizeof(ZKN_CURSOR) );
	memset( p_cursor, 0, sizeof(ZKN_CURSOR) );

	return p_cursor;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑CURSORシステムワーク破棄
 *
 *	@param	p_cursor	CURSORシステムワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_Free( ZKN_CURSOR* p_cursor )
{
	sys_FreeMemoryEz( p_cursor );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑CURSORシステム初期化
 *
 *	@param	p_cursor	CURSORシステムワーク
 *	@param	cp_data		CURSORデータ
 *	@param	max_x		X方向データ数
 *	@param	max_y		Y方向データ数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_Init( ZKN_CURSOR* p_cursor, const ZKN_CURSOR_ONEDATA* cp_data, int max_x, int max_y )
{
	memset( p_cursor, 0, sizeof(ZKN_CURSOR) );
	p_cursor->p_data = cp_data;
	p_cursor->max_x = max_x;
	p_cursor->max_y	= max_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑CURSORシステムコントロール
 *
 *	@param	p_cursor	CURSORシステムワーク
 *	@param	cont		動作コマンド
 *	@param	param		動作値
 *
 *	@return	none	
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_Cont( ZKN_CURSOR* p_cursor, int cont, int param )
{
	int i;
	
	switch( cont ){
	case ZKN_CURSOR_CONT_ADD_X:		// X方向移動	
		ZknCursorContAddX( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_ADD_Y:		// Y方向移動	
		ZknCursorContAddY( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_SET_X:		// X方向設定	
		ZknCursorContSetX( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_SET_Y:		// Y方向設定	
		ZknCursorContSetY( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_SET_CONTID:	// 管理IDの位置にカーソルを移動
		ZknCursorContSetContID( p_cursor, param );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在いる位置の管理IDを取得
 *
 *	@param	cp_cursor	CURSORシステムワーク
 *
 *	@return	管理ID
 */
//-----------------------------------------------------------------------------
int ZKN_CURSOR_GetContID( const ZKN_CURSOR* cp_cursor )
{
	int now_idx;
	
	now_idx = GetNowIdx( cp_cursor );
	return cp_cursor->p_data[ now_idx ].cont_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在CURSOR位置の座標を取得
 *
 *	@param	cp_cursor	CURSORシステムワーク
 *	@param	p_x			X座標格納先
 *	@param	p_y			Y座標格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_GetMat( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y )
{
	int now_idx;
	
	now_idx = GetNowIdx( cp_cursor );
	
	*p_x = cp_cursor->p_data[ now_idx ].x;
	*p_y = cp_cursor->p_data[ now_idx ].y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在CURSOR位置の領域サイズを取得
 *
 *	@param	cp_cursor	CURSORシステムワーク
 *	@param	p_x			Xサイズ格納先
 *	@param	p_y			Yサイズ格納先
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_GetSize( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y )
{
	int now_idx;
	
	now_idx = GetNowIdx( cp_cursor );
	
	*p_x = cp_cursor->p_data[ now_idx ].size_x;
	*p_y = cp_cursor->p_data[ now_idx ].size_y;
}


//----------------------------------------------------------------------------
/**
 *	@brief	カーソル１データの内容を格納
 *
 *	@param	p_data		格納先
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	size_x		ｘサイズ
 *	@param	size_y		ｙサイズ
 *	@param	movex_id	X方向動作ID
 *	@param	movey_id	Y方向動作ID
 *	@param	cont_id		ユーザー管理ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_SetOneData( ZKN_CURSOR_ONEDATA* p_data, int x, int y, int size_x, int size_y, int movex_id, int movey_id, int cont_id )
{
	p_data->x = x;
	p_data->y = y;
	p_data->size_x = size_x;
	p_data->size_y = size_y;
	p_data->movex_id = movex_id;
	p_data->movey_id = movey_id;
	p_data->cont_id  = cont_id;
}


//----------------------------------------------------------------------------
/**
 *	@brief	4隅の座標を取得
 *
 *	@param	cp_cursor	カーソルシステムワーク
 *	@param	way			位置 
 *	@param	p_x			ｘ座標格納先
 *	@param	p_y			ｙ座標格納先
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_GetRectMat( const ZKN_CURSOR* cp_cursor, int way, int* p_x, int* p_y )
{
	int x, y;
	int size_x, size_y;

	// 座標の取得
	ZKN_CURSOR_GetMat( cp_cursor, &x, &y );

	// サイズの取得
	ZKN_CURSOR_GetSize( cp_cursor, &size_x, &size_y );

	// 座標を求める
	ZKN_CURSOR_UTIL_GetRectMat( way, p_x, p_y, x, y, size_x, size_y );
}


//----------------------------------------------------------------------------
/**
 *	@brief	サイズと中心座標から各位置の座標を取得
 *
 *	@param	way			方向
 *	@param	p_x			X座標格納先
 *	@param	p_y			Y座標格納先
 *	@param	def_x		中心X
 *	@param	def_y		中心Y
 *	@param	size_x		サイズX
 *	@param	size_y		サイズY
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_UTIL_GetRectMat( int way, int* p_x, int* p_y, int def_x, int def_y, int size_x, int size_y )
{
	// X座標設定
	if( (way == ZKN_CURSOR_MAT_TOP_LEFT) ||
		(way == ZKN_CURSOR_MAT_BOTTOM_LEFT) ){
		def_x -= size_x / 2;	
	}else{
		def_x += size_x / 2;	
	}
	
	// Y座標設定
	if( (way == ZKN_CURSOR_MAT_TOP_LEFT) ||
		(way == ZKN_CURSOR_MAT_TOP_RIGHT) ){
		def_y -= size_y / 2;	
	}else{
		def_y += size_y / 2;	
	}

	*p_x = def_x;
	*p_y = def_y;
}


//-----------------------------------------------------------------------------
/**
 *				プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	今のデータ配列要素数を取得
 *
 *	@param	cp_cursor	CURSORシステムワーク
 *
 *	@return	配列要素数
 */
//-----------------------------------------------------------------------------
static int inline GetNowIdx( const ZKN_CURSOR* cp_cursor )
{
	int now_idx;
	
	now_idx = cp_cursor->now_y * cp_cursor->max_x;
	now_idx += cp_cursor->now_x;

	return now_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	今のデータ配列要素数を取得
 *
 *	@param	cp_cursor	CURSORシステムワーク
 *	@param	x			取得したいX
 *	@param	y			取得したいY
 *
 *	最大サイズはcp_cursorのものを使用する
 *
 *	@return	配列要素数
 */
//-----------------------------------------------------------------------------
static int inline GetIdx( const ZKN_CURSOR* cp_cursor, int x, int y )
{
	int now_idx;
	
	now_idx = y * cp_cursor->max_x;
	now_idx += x;

	return now_idx;
}


//----------------------------------------------------------------------------
/**
 *	@brief	X方向にCURSORを動かす
 *
 *	@param	p_cursor	CURSORシステムワーク
 *	@param	param		動かす値	(-1 or 1)
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MoveXCursor( ZKN_CURSOR* p_cursor, int param )
{
	int move_x;
	const ZKN_CURSOR_ONEDATA* p_data;
	int data_idx;
	int move_param;

	GF_ASSERT( (param == -1) || (param == 1) );
	
	move_param = 0;

	// 設定座標を求める
	do{
		// 移動させる値を計算
		move_param += param;
		move_x = p_cursor->now_x + move_param;

		// 横最大数OR最低数を下回ったら終わり
		if( (move_x < 0) || (move_x >= p_cursor->max_x) ){
			break;
		}

		// 移動させるところのデータを取得
		data_idx = GetIdx( p_cursor, move_x, p_cursor->now_y );
		p_data = &p_cursor->p_data[ data_idx ];

	}while( p_data->movex_id == ZKN_CURSOR_MOVE_SKIP );

	// X動作有効範囲内なら値を設定
	if( (move_x >= 0) && (move_x < p_cursor->max_x) ){
		// 移動して大丈夫かチェック
		if( p_data->movex_id == ZKN_CURSOR_MOVE_NORMAL ){
			// 値を反映
			p_cursor->now_x = move_x;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief　Y方向にCURSORを動かす
 *
 *	@param	p_cursor	CURSORシステムワーク
 *	@param	param		動かす値	(-1 or 1)
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MoveYCursor( ZKN_CURSOR* p_cursor, int param )
{
	int move_y;
	const ZKN_CURSOR_ONEDATA* p_data;
	int data_idx;
	int move_param;

	GF_ASSERT( (param == -1) || (param == 1) );
	
	move_param = 0;

	// 設定座標を求める
	do{
		// 移動させる値を計算
		move_param += param;
		move_y = p_cursor->now_y + move_param;

		// 縦最大数OR最低数を下回ったら終わり
		if( (move_y < 0) || (move_y >= p_cursor->max_y) ){
			break;
		}

		// 移動させるところのデータを取得
		data_idx = GetIdx( p_cursor, p_cursor->now_x, move_y );
		p_data = &p_cursor->p_data[ data_idx ];

	}while( p_data->movey_id == ZKN_CURSOR_MOVE_SKIP );

	// X動作有効範囲内なら値を設定
	if( (move_y >= 0) && (move_y < p_cursor->max_y) ){
		// 移動して大丈夫かチェック
		if( p_data->movex_id == ZKN_CURSOR_MOVE_NORMAL ){
			// 値を反映
			p_cursor->now_y = move_y;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	X方向にparamの数だけ進む
 *
 *	@param	p_cursor	CURSORシステムワーク
 *	@param	param		進める値
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorContAddX( ZKN_CURSOR* p_cursor, int param )
{
	int i;
	int way;
	int abs;
	
	// プラスマイナスを求める
	abs = MATH_ABS( param );
	way = param / abs;
	
	for( i=0; i<abs; i++ ){
		MoveXCursor( p_cursor, way );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	Y方向にparamの数だけ進む
 *
 *	@param	p_cursor	CURSORシステムワーク
 *	@param	param		進める値
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorContAddY( ZKN_CURSOR* p_cursor, int param )
{
	int i;
	int way;
	int abs;
	
	// プラスマイナスを求める
	abs = MATH_ABS( param );
	way = param / abs;
	
	for( i=0; i<abs; i++ ){
		MoveYCursor( p_cursor, way );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル位置をparamにする
 *
 *	@param	p_cursor	CURSOR位置
 *	@param	param		設定値
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void inline ZknCursorContSetX( ZKN_CURSOR* p_cursor, int param )
{
	GF_ASSERT( (param >= 0) && (param < p_cursor->max_x) );	
	p_cursor->now_x = param;
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル位置をparamにする
 *
 *	@param	p_cursor	CURSOR位置
 *	@param	param		設定値
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void inline ZknCursorContSetY( ZKN_CURSOR* p_cursor, int param )
{
	GF_ASSERT( (param >= 0) && (param < p_cursor->max_y) );	
	p_cursor->now_y = param;
}

//----------------------------------------------------------------------------
/**
 *	@brief	paramの管理IDのCURSOR位置に移動
 *
 *	@param	p_cursor	CURSORシステムワーク
 *	@param	param		管理ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorContSetContID( ZKN_CURSOR* p_cursor, int param )
{
	int i;
	int data_num = p_cursor->max_x * p_cursor->max_y;

	for( i=0; i<data_num; i++ ){
		
		if( p_cursor->p_data[i].cont_id == param ){
			p_cursor->now_x = i % p_cursor->max_x;
			p_cursor->now_y = i / p_cursor->max_x;
			break;
		}
	}
}
