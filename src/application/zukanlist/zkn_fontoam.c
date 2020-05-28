//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fontoam.c
 *	@brief		図鑑フォントOAMシステム
 *	@author		tomoya takahashi
 *	@data		2006.01.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "msg_print.h"
#include "include/system/msgdata.h"
#include "include/system/fontproc.h"
#include "include/application/zukanlist/zkn_drawglb.h"


#define __ZKN_FONTOAM_H_GLOBAL
#include "include/application/zukanlist/zkn_fontoam.h"

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
//	FONT_OAMシステム
//=====================================
typedef struct _ZKN_FONTOAM_SYS{
	FONTOAM_SYS_PTR		fontoam_sys;	// フォントシステムデータ
	CLACT_SET_PTR		clact_set;		// セルアクターセット
	GF_BGL_INI*			p_bg;			// bgシステム
	ZKN_FONTOAM_DATA*	p_datatbl;		// データテーブル
	int		data_num;					// 登録可能数
	int		heap;						// 使用するヒープ
} ZKN_FONTOAM_SYS;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

static BOOL CheckFontOamDataLive( ZKN_FONTOAM_DATA* p_data );
static ZKN_FONTOAM_DATA* CleanFontOamDataGet( ZKN_FONTOAM_SYS_PTR fontoam_sys );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	フォントOAMシステム初期化
 *	
 *	@param	cp_init		初期化データ
 *
 *	@return	フォントOAMシステムデータ
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_SYS_PTR ZKN_FONTOAM_InitSys( const ZKN_FONTOAM_SYS_INIT* cp_init )
{
	ZKN_FONTOAM_SYS_PTR p_fontoam;

	// メモリ確保
	p_fontoam = sys_AllocMemory( cp_init->heap, sizeof(ZKN_FONTOAM_SYS) );
	GF_ASSERT( p_fontoam );
	memset( p_fontoam, 0, sizeof(ZKN_FONTOAM_SYS) );

	// フォントOAMシステム作成
	p_fontoam->fontoam_sys = FONTOAM_SysInit( cp_init->work_num, cp_init->heap );

	// データ格納ワーク作成
	p_fontoam->p_datatbl = sys_AllocMemory( cp_init->heap, sizeof(ZKN_FONTOAM_DATA) * cp_init->work_num );
	GF_ASSERT( p_fontoam->p_datatbl );
	memset( p_fontoam->p_datatbl, 0, sizeof(ZKN_FONTOAM_DATA) * cp_init->work_num );
	p_fontoam->data_num = cp_init->work_num;

	// セルアクターセット設定
	p_fontoam->clact_set = cp_init->clact_set;

	// BGL設定
	p_fontoam->p_bg = cp_init->p_bg;

	// ヒープID設定
	p_fontoam->heap	= cp_init->heap;

	return p_fontoam;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑フォントシステム破棄
 *
 *	@param	fontoam_sys		図鑑フォントシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_DeleteSys( ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_ASSERT( fontoam_sys );
	
	ZKN_FONTOAM_DeleteAll( fontoam_sys );

	sys_FreeMemoryEz( fontoam_sys->p_datatbl );

	FONTOAM_SysDelete( fontoam_sys->fontoam_sys );
	
	memset( fontoam_sys, 0, sizeof(ZKN_FONTOAM_SYS) );

	sys_FreeMemoryEz( fontoam_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	文字列OAM作成
 *
 *	@param	cp_init 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_DATA* ZKN_FONTOAM_Make( const ZKN_FONTOAM_INIT* cp_init )
{
	int char_size;

	// キャラクタデータ転送領域確保
	char_size = FONTOAM_NeedCharSize( cp_init->p_bmp, cp_init->draw_area, cp_init->heap ); 

	return ZKN_FONTOAM_MakeCharOfs( cp_init, char_size );
}

//----------------------------------------------------------------------------
/**
 *	@brief	転送領域データを指定した作成
 *	
 *	@param	cp_init			初期化データ
 *	@param	char_size		キャラクタサイズ	
 *
 *	@return	作成データ
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_DATA* ZKN_FONTOAM_MakeCharOfs( const ZKN_FONTOAM_INIT* cp_init, int char_size )
{
	FONTOAM_INIT fo_init;
	ZKN_FONTOAM_DATA* p_make_data;

	// 空いているテーブルを取得
	p_make_data = CleanFontOamDataGet( cp_init->zkn_fontoam );
	// あきなし
	GF_ASSERT( p_make_data );

	// キャラクタデータ転送領域確保
	CharVramAreaAlloc( char_size, CHARM_CONT_AREACONT, cp_init->draw_area, &p_make_data->char_data );
	
	// フォントOAM作成
	fo_init.fontoam_sys = cp_init->zkn_fontoam->fontoam_sys;
	fo_init.bmp			= cp_init->p_bmp;
	fo_init.clact_set	= cp_init->zkn_fontoam->clact_set;
	fo_init.pltt		= cp_init->pltt;
	fo_init.parent		= cp_init->parent;
	fo_init.char_ofs	= p_make_data->char_data.alloc_ofs;	
	fo_init.x			= cp_init->x;
	fo_init.y			= cp_init->y;
	fo_init.bg_pri		= cp_init->bg_pri;
	fo_init.soft_pri	= cp_init->soft_pri;
	fo_init.draw_area	= cp_init->draw_area;
	fo_init.heap		= cp_init->heap;
	p_make_data->p_fontoam = FONTOAM_Init( &fo_init );

	return p_make_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フォントOAMデータ破棄
 *
 *	@param	p_fontoam 
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_Delete( ZKN_FONTOAM_DATA* p_fontoam )
{
	// フォントデータ破棄
	FONTOAM_Delete( p_fontoam->p_fontoam );

	// キャラクタ管理領域破棄
	CharVramAreaFree( &p_fontoam->char_data );

	// 初期化
	memset( p_fontoam, 0, sizeof(ZKN_FONTOAM_DATA) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	管理しているFONTOAMデータ破棄
 *
 *	@param	fontoam_sys		 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_DeleteAll( ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	int i;		// ループ用

	// 全データ破棄
	for( i=0; i<fontoam_sys->data_num; i++ ){
		if( CheckFontOamDataLive( &fontoam_sys->p_datatbl[ i ] ) ){
			ZKN_FONTOAM_Delete( &fontoam_sys->p_datatbl[ i ] );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップウィンドウ作成
 *
 *	@param	fontoam_sys		フォントシステム
 *	@param	bmp_x			ビットマップサイズ	（キャラクタ）
 *	@param	bmp_y			ビットマップサイズ	（キャラクタ）
 *
 *	@return	ビットマップウィンドウ
 *
 *
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_FONTOAM_GetBmp( ZKN_FONTOAM_SYS_PTR fontoam_sys, int bmp_x, int bmp_y )
{
	GF_BGL_BMPWIN* p_bmp;
	
	p_bmp = GF_BGL_BmpWinAllocGet( fontoam_sys->heap, 1 );
	GF_BGL_BmpWinInit( p_bmp );
	GF_BGL_BmpWinObjAdd( fontoam_sys->p_bg, p_bmp, bmp_x, bmp_y, 0, 0 );

	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップウィンドウ破棄
 *
 *	@param	win		ビットマップウィンドウ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_DeleteBmp( GF_BGL_BMPWIN* win )
{
	GF_BGL_BmpWinFree( win, 1 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	文字列書き込み
 *
 *	@param	fontoam_sys	フォントOAMシステム
 *	@param	win			ウィンドウ	
 *	@param	dataID		データID
 *	@param	msgID		メッセージID
 *	@param	bmp_x		表示座標	（キャラクタ単位）
 *	@param	bmp_y		表示座標	（キャラクタ単位）
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_PrintBmpStr( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, u32 dataid, u32 msgid, int bmp_x, int bmp_y )
{
	MSGDATA_MANAGER* p_msg_data;
	STRBUF* p_str;

	p_msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, dataid, fontoam_sys->heap );
	GF_ASSERT( p_msg_data );
	p_str = MSGMAN_AllocString( p_msg_data, msgid );

	// 文字列書き込み
	GF_STR_PrintColor( win, FONT_BUTTON, p_str, bmp_x, bmp_y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );

	STRBUF_Delete( p_str );
	MSGMAN_Delete( p_msg_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップのある位置にSTRBUFの文字列を書き込む
 *
 *	@param	fontoam_sys	フォントOAMシステム
 *	@param	win			ウィンドウ	
 *	@param	str			文字列データ
 *	@param	bmp_x		表示座標	（キャラクタ単位）
 *	@param	bmp_y		表示座標	（キャラクタ単位）
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_PrintBmpStrBuf( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, STRBUF* str, int bmp_x, int bmp_y )
{
	// 文字列書き込み
	GF_STR_PrintColor( win, FONT_BUTTON, str, bmp_x, bmp_y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	引数のフォントOAMデータにデータが入っているかチェック
 *
 *	@param	p_data データ
 *
 *	@retval	TRUE		入っている
 *	@retval	FALSE		入っていない
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL CheckFontOamDataLive( ZKN_FONTOAM_DATA* p_data )
{
	if( p_data->p_fontoam ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	空いているFONTOAMデータ取得
 *
 *	@param	fontoam_sys		フォントOAMシステム
 *
 *	@return	カラのFONTOAMデータ 空いているテーブルが無いときNULL
 *	
 *
 */
//-----------------------------------------------------------------------------
static ZKN_FONTOAM_DATA* CleanFontOamDataGet( ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	int i;

	for( i=0; i<fontoam_sys->data_num; i++ ){
		if( CheckFontOamDataLive( &fontoam_sys->p_datatbl[ i ] ) == FALSE ){
			return &fontoam_sys->p_datatbl[ i ];
		}
	}


	return NULL;
}
