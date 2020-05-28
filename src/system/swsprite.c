//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		swsprite.c
 *	@brief		ソフトウェアスプライト表示システム
 *	@author		tomoya takahashi
 *	@data		2005.09.13
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "string.h"

#define __SESPRITE_H_GLOBAL
#include "include/system/swsprite.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define	PLTT_16_SIZE	(32)		// 16色パレットサイズ

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	キャラクタデータ
//
//=====================================
typedef struct SWSP_CHAR_tag{
	NNSGfdTexKey		vramKey;	// 使用Vram領域
	NNSG2dImageProxy	imgProxy;	// imageプロクシ
} SWSP_CHAR;

//-------------------------------------
//	
//	パレットデータ
//	
//=====================================
typedef struct SWSP_PLTT_tag{
	NNSGfdPlttKey			vramKey;	// 使用Vram領域
	NNSG2dImagePaletteProxy	imgProxy;	// imageプロクシ
} SWSP_PLTT;

//-------------------------------------
//	
//	ソフトウェアスプライト表示データ
//	を１つにまとめたオブジェクトデータ
//	
//=====================================
typedef struct SWSP_OBJ_tag{
	NNSG2dSVec2		matrix;					// 表示位置
	NNSG2dSVec2		center;					// 中心座標
    NNSG2dSVec2		size;					// サイズ
	fx32			scale_x;				// ｘ拡大値
	fx32			scale_y;				// ｙ拡大値
	int				priority;				// 表示優先順位
	int				rotZ;					// 回転角Z
	BOOL			use;					// 使用中か
	BOOL			draw;					// 表示するか
	NNSG2dImageAttr* tex_attr;				// テクスチャアトリビュート
	u32				tex_addr;				// テクスチャアドレス
	u32				pltt_addr;				// パレットアドレス
	u32				pltt_offs;				// 16色時
	BOOL			flipH;					// Hフリップ
	BOOL			flipV;					// Vフリップ
	GXRgb			diffcolor;				// ディフューズカラー
	u8				alpha;					// アルファ
} SWSP_OBJ;

//-------------------------------------
//	
//	imageClip用
//	ソフトウェアスプライト描画システム
//	データ格納構造体
//=====================================
typedef struct SWSP_SYS_tag{
	SWSP_OBJ*	obj_tbl;		// オブジェテーブル
	int				obj_num;		// オブジェテーブル数
	SWSP_CHAR*	char_tbl;		// キャラクタテーブル
	int				char_num;		// キャラクタテーブル数
	SWSP_PLTT*	pltt_tbl;		// パレットテーブル
	int				pltt_num;		// パレットテーブル数

}SWSP_SYS;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void cleanSys( SWSP_SYS* data );
static void cleanObj( SWSP_OBJ* data );
static void cleanChar( SWSP_CHAR* data );
static void cleanPltt( SWSP_PLTT* data );

static void darwObj( SWSP_OBJ* data );

static SWSP_OBJ* makeObjData( int num, int heap );
static SWSP_CHAR* makeCharData( int num, int heap );
static SWSP_PLTT* makePlttData( int num, int heap );

static SWSP_OBJ* getCleanObj( SWSP_SYS* sys );
static SWSP_CHAR* getCleanChar( SWSP_SYS* sys );
static SWSP_PLTT* getCleanPltt( SWSP_SYS* sys );

static NNSGfdTexKey getCharVramKey( NNSG2dCharacterData* pChar );
static NNSGfdPlttKey getPlttVramKey( int pltt_num );
static void transCharData( NNSG2dCharacterData* pChar, NNSGfdTexKey vramKey, NNSG2dImageProxy* proxy );
static void transPlttData( NNSG2dPaletteData* pPltt, NNSGfdPlttKey vramKey, NNSG2dImagePaletteProxy* proxy );

// スプライトデータ設定、取得関数
static void setSpriteData( SWSP_OBJ_PTR obj, const SWSP_ADDDATA* add );

//-----------------------------------------------------------------------------
/**
*		グローバル関数実態
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	imageClip描画用ソフトウェアシステム初期化
 *
 *	@param	data		システム初期化データ
 *	@param	heap		使用ヒープ
 *
 *	@return	SWSPRITE_PTR	ソフトウェアシステムデータ
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_SYS_PTR SWSP_SysInit( const SWSP_SYSDATA* data )
{
	SWSP_SYS_PTR sys;
	int i;	// ループ用

	sys = sys_AllocMemory( data->heap, sizeof(SWSP_SYS) );
	GF_ASSERT( sys );

	// オブジェクトデータ作成
	sys->obj_tbl = makeObjData( data->obj_num, data->heap );
	sys->obj_num = data->obj_num;
	
	// キャラクタデータ作成
	sys->char_tbl = makeCharData( data->char_num, data->heap );
	sys->char_num = data->char_num;
	
	// パレットデータ作成
	sys->pltt_tbl = makePlttData( data->pltt_num, data->heap );
	sys->pltt_num = data->pltt_num;

	return sys;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライトシステム破棄
 *
 *	@param	data	ソフトウェアシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SysDelete( SWSP_SYS_PTR data )
{
	GF_ASSERT(data);
	GF_ASSERT(data->obj_tbl);
	GF_ASSERT(data->char_tbl);
	GF_ASSERT(data->pltt_tbl);

	// 全データ破棄
	sys_FreeMemoryEz( data->obj_tbl );
	sys_FreeMemoryEz( data->char_tbl );
	sys_FreeMemoryEz( data->pltt_tbl );
	sys_FreeMemoryEz( data );
	data = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		表示する
 *
 *	@param		data システム内の表示オブジェクトを表示する
 *
 *	@return		none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SysDraw( SWSP_SYS_PTR data )
{
	int i;		// ループ用
	

	G3_PushMtx();
	
	
	for( i=0;i<data->obj_num;i++ ){
		if(data->obj_tbl[ i ].draw){
			darwObj( data->obj_tbl + i );
		}
	}

	G3_PopMtx(1);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータの構造体サイズを返す
 *
 *	@param	none
 *
 *	@return	int	サイズ
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetCharDataSize( void )
{
	return sizeof( SWSP_CHAR );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ構造体のサイズを返す
 *
 *	@param	none
 *
 *	@return	int		サイズ
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetPlttDataSize( void )
{
	return sizeof( SWSP_PLTT );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトデータ構造体のサイズを取得する
 *
 *	@param	none
 *
 *	@return	int		サイズ
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetSpriteDataSize( void )
{
	return sizeof( SWSP_OBJ );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	配列でオブジェクトを格納する領域を用意したときの要素数のデータ取得用関数
 *
 *	@param	obj		オブジェクトポインタを格納している配列
 *	@param	no		取得する要素数
 *
 *	@return	SWSP_CHAR_PTR	要素のデータ
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_CHAR_PTR SWSP_GetCharDataNo( SWSP_CHAR_PTR obj, int no )
{
	return obj + no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	配列でオブジェクトを格納する領域を用意したときの要素数のデータ取得用関数
 *
 *	@param	obj		オブジェクトポインタを格納している配列
 *	@param	no		取得する要素数
 *
 *	@return	SWSP_PLTT_PTR	要素のデータ
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_PLTT_PTR SWSP_GetPlttDataNo( SWSP_PLTT_PTR obj, int no )
{
	return obj + no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	配列でオブジェクトを格納する領域を用意したときの要素数のデータ取得用関数
 *
 *	@param	obj		オブジェクトポインタを格納している配列
 *	@param	no		取得する要素数
 *
 *	@return	SWSP_OBJ_PTR	要素のデータ
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_OBJ_PTR SWSP_GetSpriteDataNo( SWSP_OBJ_PTR obj, int no )
{
	return obj + no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト用キャラクタデータを読み込む
 *
 *	@param	data	読み込むキャラクタデータ 
 *
 *	@return	SWSP_CHAR_PTR	読み込んだキャラクタデータ
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_CHAR_PTR SWSP_CharLoad( const SWSP_CHARDATA* data )
{
	SWSP_CHAR_PTR char_tbl;		// データ格納先

	// 空のキャラクタデータテーブル取得
	char_tbl = getCleanChar( data->s_sys );
	GF_ASSERT( char_tbl );

	// 2Dmapかチェック
	GF_ASSERT( data->res_file->mapingType == GX_OBJVRAMMODE_CHAR_2D );
	
	// キャラクタサイズのvramKeyを取得
	char_tbl->vramKey = getCharVramKey( data->res_file );	
	GF_ASSERT( char_tbl->vramKey );
	
	// vramkeyのアドレスにデータ転送
	transCharData( data->res_file, char_tbl->vramKey, &char_tbl->imgProxy );

	return char_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータ破棄
 *
 *	@param	data	キャラクタデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_CharDelete( SWSP_CHAR_PTR data )
{
	// VramKeyの解放
	NNS_GfdFreeTexVram( data->vramKey );

	// テーブルcleanアップ
	cleanChar( data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータ全破棄
 *
 *	@param	data		キャラクタデータを全部破棄するシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_CharDeleteAll( SWSP_SYS_PTR data )
{
	int i;		// ループ用

	for(i=0;i<data->char_num;i++){
		if( data->char_tbl[ i ].vramKey ){
			SWSP_CharDelete( data->char_tbl + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト用パレットデータを読み込む
 *
 *	@param	data	読み込むパレットデータ 
 *
 *	@return	SWSP_PLTT_PTR	読み込んだパレットデータ
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_PLTT_PTR SWSP_PlttLoad( const SWSP_PLTTDATA* data )
{
	SWSP_PLTT_PTR pltt_tbl;		// パレットデータ格納先

	// 空のパレットテーブル取得
	pltt_tbl = getCleanPltt( data->s_sys );
	GF_ASSERT( pltt_tbl );

	// VramKey取得
	pltt_tbl->vramKey = getPlttVramKey( data->load_num );
	GF_ASSERT(pltt_tbl->vramKey);

	// パレットデータ転送
	transPlttData( data->res_file, pltt_tbl->vramKey, &pltt_tbl->imgProxy );

	return pltt_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト用パレットデータ破棄
 *
 *	@param	data	破棄するパレットデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_PlttDelete( SWSP_PLTT_PTR data )
{
	// VramKeyの解放
	NNS_GfdFreePlttVram( data->vramKey );

	// テーブルcleanアップ
	cleanPltt( data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ全破棄
 *
 *	@param	data		パレットデータを全破棄するソフトウェアスプライトデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_PlttDeleteAll( SWSP_SYS_PTR data )
{
	int i;		// ループ用

	for(i=0;i<data->pltt_num;i++){
		if( data->pltt_tbl[ i ].vramKey ){
			SWSP_PlttDelete( data->pltt_tbl + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト表示登録
 *
 *	@param	add		登録データ
 *
 *	@return	SWSP_OBJ_PTR	ソフトウェアスプライトオブジェ
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_OBJ_PTR SWSP_Add( const SWSP_ADDDATA* add )
{
	SWSP_OBJ_PTR obj_tbl;	// データ格納先

	// 空いているテーブルを取得
	obj_tbl = getCleanObj( add->s_sys );
	GF_ASSERT( obj_tbl );

	// データ設定
	// 設定する
	setSpriteData( obj_tbl, add );

	// 使用中にする
	obj_tbl->use	= TRUE;
	obj_tbl->draw	= TRUE;

	return obj_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト表示データ破棄
 *
 *	@param	sp_obj 破棄するソフトウェアスプライトオブジェ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_Delete( SWSP_OBJ_PTR sp_obj )
{

	cleanObj( sp_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト表示データ全破棄
 *
 *	@param	sys		表示データオブジェを全破棄するソフトウェアスプライトシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_DeleteAll( SWSP_SYS_PTR sys )
{
	int i;		// ループ用

	for(i=0;i<sys->obj_num;i++){
		if( sys->obj_tbl[ i ].use ){
			SWSP_Delete( sys->obj_tbl + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトの表示/非表示設定
 *
 *	@param	obj		スプライトオブジェクト
 *	@param	draw	表示/表示		(TRUE / FALSE)
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteDraw( SWSP_OBJ_PTR obj, BOOL draw )
{
	GF_ASSERT( obj );
	obj->draw = draw;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトの表示/非表示を取得
 *
 *	@param	obj		スプライトオブジェクト
 *
 *	@retval	TRUE	表示
 *	@retval	FALSE	非表示
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL SWSP_GetSpriteDraw( SWSP_OBJ_PTR obj )
{
	GF_ASSERT( obj );
	return obj->draw;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト座標設定
 *
 *	@param	obj		オブジェ	
 *	@param	x		座標ｘ
 *	@param	y		座標ｙ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePos( SWSP_OBJ_PTR obj, s16 x, s16 y )
{
	obj->matrix.x = x;
	obj->matrix.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト座標を取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	NNSG2dSVec2 座標(メンバ s16 x  s16 y)
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpritePos( SWSP_OBJ_PTR obj )
{
	return obj->matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト中心座標設定
 *
 *	@param	obj		オブジェ	
 *	@param	x		座標ｘ
 *	@param	y		座標ｙ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteCenterPos( SWSP_OBJ_PTR obj, s16 x, s16 y )
{
	obj->center.x = x;
	obj->center.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト中心座標を取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	NNSG2dSVec2 座標(メンバ s16 x  s16 y)
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpriteCenterPos( SWSP_OBJ_PTR obj )
{
	return obj->center;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	拡大縮小値を設定
 *
 *	@param	obj		スプライトオブジェ
 *	@param	x		ｘ拡縮値
 *	@param	y		ｙ拡縮値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteScale( SWSP_OBJ_PTR obj, fx32 x, fx32 y )
{
	obj->scale_x = x;
	obj->scale_y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	拡大縮小値を取得
 *
 *	@param	obj		スプライトオブジェ
 *	@param	x		ｘ座標取得先
 *	@param	y		ｙ座標取得先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_GetSpriteScale( SWSP_OBJ_PTR obj, fx32* x, fx32* y )
{
	*x = obj->scale_x;
	*y = obj->scale_y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトサイズを設定
 *
 *	@param	obj		スプライトオブジェ
 *	@param	x		サイズｘ
 *	@param	y		サイズｙ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteSize( SWSP_OBJ_PTR obj, int x, int y )
{
	obj->size.x = x;
	obj->size.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトサイズを取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	NNSG2dSVec2	スプライトサイズ（メンバ s16 x s16 y）
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpriteSize( SWSP_OBJ_PTR obj )
{
	return obj->size;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト表示優先順位を設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	priority	表示優先順位
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePriority( SWSP_OBJ_PTR obj, int priority )
{
	obj->priority = priority;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトの表示優先順位を設定
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	int		表示優先順位
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetSpritePriority( SWSP_OBJ_PTR obj )
{
	return obj->priority;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのα値を設定
 *
 *	@param	obj		スプライトオブジェ
 *	@param	alpha	α値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteAlpha( SWSP_OBJ_PTR obj, u8 alpha )
{
	obj->alpha = alpha;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのα値を取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
u8 SWSP_GetSpriteAlpha( SWSP_OBJ_PTR obj )
{
	return obj->alpha;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		スプライトの色を設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	color		ディフューズカラー
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteDiffColor( SWSP_OBJ_PTR obj, GXRgb color )
{
	obj->diffcolor = color;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		スプライトのディフューズ色を取得
 *
 *	@param	obj			スプライトオブジェ
 *
 *	@retval	カラー
 */
//-----------------------------------------------------------------------------
GXRgb SWSP_GetSpriteDiffColor( SWSP_OBJ_PTR obj )
{
	return obj->diffcolor;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのテクスチャアトリビュートを設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	tex_attr	テクスチャアトリビュートポインタ
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteTexAttr( SWSP_OBJ_PTR obj, NNSG2dImageAttr* tex_attr )
{
	obj->tex_attr = tex_attr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのテクスチャアトリビュートを取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	NNSG2dImageAttr*	テクスチャアトリビュート
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageAttr* SWSP_GetSpriteTexAttr( SWSP_OBJ_PTR obj )
{
	return obj->tex_attr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャアドレス設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	tex_addr	テクスチャアドレス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteTexAddr( SWSP_OBJ_PTR obj, u32 tex_addr )
{
	obj->tex_addr = tex_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テクスチャアドレスを取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	u32		テクスチャアドレス
 *
 *
 */
//-----------------------------------------------------------------------------
u32 SWSP_GetSpriteTexAddr( SWSP_OBJ_PTR obj )
{
	return obj->tex_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのパレットアドレス設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	pltt_addr	パレットアドレス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePlttAddr( SWSP_OBJ_PTR obj, u32 pltt_addr )
{
	obj->pltt_addr = pltt_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのパレットアドレス取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	u32		パレットアドレス
 *
 *
 */
//-----------------------------------------------------------------------------
u32 SWSP_GetSpritePlttAddr( SWSP_OBJ_PTR obj )
{
	return obj->pltt_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットオフセット
 *
 *	@param	obj			スプライトオブジェ
 *	@param	pltt_offs	パレットオフセット
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePlttOffs( SWSP_OBJ_PTR obj, u32 pltt_offs )
{
	obj->pltt_offs = pltt_offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットオフセット取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	u32		オフセット
 *
 *
 */
//-----------------------------------------------------------------------------
u32 SWSP_GetSpritePlttOffs( SWSP_OBJ_PTR obj )
{
	return obj->pltt_offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトフリップ設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	flip_flg	フリップフラグ
 *	@param	flip		フリップさせるか	TRUE　させる　FALSE　させない
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteFlip( SWSP_OBJ_PTR obj, int flip_flg, BOOL flip )
{
	if(flip_flg == SWSP_FLIPH){
		obj->flipH = flip;
	}else{
		obj->flipV = flip;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		スプライトのフリップを取得
 *
 *	@param	obj			スプライトオブジェ
 *	@param	flip_flg	HVフリップフラグ
 *
 *	@return	BOOL	TRUE	フリップする	FALSE
 *
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL SWSP_GetSpriteFlip( SWSP_OBJ_PTR obj, int flip_flg )
{
	if(flip_flg == SWSP_FLIPH){
		return obj->flipH;
	}
	
	return obj->flipV;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転角zを設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	rota		設定する角度
 *
 *	@return
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteRotZ( SWSP_OBJ_PTR obj, u16 rota )
{
	obj->rotZ = rota;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転角度Zを取得
 *
 *	@param	obj			スプライトオブジェ
 *
 *	@return	u16		回転角度
 *
 *
 */
//-----------------------------------------------------------------------------
u16 SWSP_GetSpriteRotZ( SWSP_OBJ_PTR obj )
{
	return obj->rotZ;
}


#if 0

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトcolorを設定（ポリゴンcolor）
 *
 *	@param	obj		スプライトオブジェ
 *	@param	color	ポリゴンcolor
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteColor( SWSP_OBJ_PTR obj, GXRgb color )
{
	obj->sprite.basicParams.color = color;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトcolor取得
 *
 *	@param	obj		スプライトオブジェ
 *
 *	@return	GXRgb	colorデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb SWSP_GetSpriteColor( SWSP_OBJ_PTR obj )
{
	return obj->sprite.basicParams.color;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのUV値を設定
 *
 *	@param	obj			スプライトオブジェ
 *	@param	LR_flg		左上　右下フラグ
 *	@param	u			U値	（横）
 *	@param	v			V値	（縦）
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteUV( SWSP_OBJ_PTR obj, int LR_flg, fx32 u, f32 v )
{
	if( LR_flg == SWSP_UVUL ){
		obj->sprite.uvUL.x = u;
		obj->sprite.uvUL.y = v;
	}else{
		obj->sprite.uvLR.x = u;
		obj->sprite.uvLR.y = v;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトのUV値を取得
 *
 *	@param	obj			スプライトオブジェ
 *	@param	LR_flg		左上、右下フラグ
 *
 *	@return	NNSG2dFVec2 UV値	（メンバ x=u  y=v）
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dFVec2 SWSP_GetSpriteUV( SWSP_OBJ_PTR obj, int LR_flg  )
{
	if( LR_flg == SWSP_UVUL ){
		return obj->sprite.uvUL;
	}
	
	return obj->sprite.uvLR;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転の中心を設定
 *
 *	@param	obj		スプライトオブジェ
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteRotO( SWSP_OBJ_PTR obj, s16 x, s16 y )
{
	obj->sprite.rotO.x = x;
	obj->sprite.rotO.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトの回転中心座標の取得
 *
 *	@param	SWSP_OBJ_PTR obj	スプライトオブジェクト
 *
 *	@return	NNSG2dSVec2		回転中心座標	
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpriteRotO( SWSP_OBJ_PTR obj )
{
	return obj->sprite.rotO;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転角を設定
 *
 *	@param	obj
 *	@param	XYZ_flg
 *	@param	rota 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteRot( SWSP_OBJ_PTR obj, int XYZ_flg, u16 rota )
{
	switch(XYZ_flg){
	case SWSP_ROT_X:
		obj->sprite.rotX = rota;
		break;
	case SWSP_ROT_Y:
		obj->sprite.rotY = rota;
		break;
	case SWSP_ROT_Z:
		obj->sprite.basicParams.simpleParams.rotZ = rota;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転角度を取得
 *
 *	@param	obj			スプライトオブジェ
 *	@param	XYZ_flg		取得する回転角度のフラグ
 *
 *	@return	u16		回転角度
 *
 *
 */
//-----------------------------------------------------------------------------
u16 SWSP_GetSpriteRot( SWSP_OBJ_PTR obj, int XYZ_flg )
{
	switch(XYZ_flg){
	case SWSP_ROT_X:
		return obj->sprite.rotX;
		
	case SWSP_ROT_Y:
		return obj->sprite.rotY;
		
	case SWSP_ROT_Z:
		return obj->sprite.basicParams.simpleParams.rotZ;
	}

	return 0;
}
#endif

//-----------------------------------------------------------------------------
/**
*			プライベート関数郡		private
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアシステムデータ	クリア
 *
 *	@param	data	データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanSys( SWSP_SYS* data )
{
	memset( data, 0, sizeof(SWSP_SYS) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトデータ	クリア
 *
 *	@param	data	データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanObj( SWSP_OBJ* data )
{
	memset( data, 0, sizeof(SWSP_OBJ) );
	data->alpha	= 31;
	data->diffcolor = GX_RGB( 31, 31, 31 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータ	クリア
 *
 *	@param	data データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanChar( SWSP_CHAR* data )
{
	data->vramKey	= 0;
	NNS_G2dInitImageProxy( &data->imgProxy );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ	クリア
 *
 *	@param	data	データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanPltt( SWSP_PLTT* data )
{
	data->vramKey	= 0;
	NNS_G2dInitImagePaletteProxy( &data->imgProxy );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	SWSP_OBJテーブルの作成
 *
 *	@param	num		テーブル数
 *	
 *	@return	SWSP_OBJ*	テーブルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ* makeObjData( int num, int heap )
{
	SWSP_OBJ* data;
	int i;	// ループ用
	
	// オブジェクトデータ作成
	data = sys_AllocMemory( heap, sizeof(SWSP_OBJ) * num );
	GF_ASSERT( data );

	for(i=0;i<num;i++){
		cleanObj( data + i );
	}

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタテーブルを作成
 *
 *	@param	num		作成数
 *	@param	heap	使用ヒープ
 *
 *	@return	SWSP_CHAR*	作成したテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_CHAR* makeCharData( int num, int heap )
{
	SWSP_CHAR* data;
	int i;	// ループ用
	
	// オブジェクトデータ作成
	data = sys_AllocMemory( heap, sizeof(SWSP_CHAR) * num );
	GF_ASSERT( data );

	for(i=0;i<num;i++){
		cleanChar( data + i );
	}

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットテーブルを作成
 *
 *	@param	num		作成数
 *	@param	heap	使用ヒープ
 *
 *	@return	SWSP_PLTT*	作成したテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_PLTT* makePlttData( int num, int heap )
{
	SWSP_PLTT* data;
	int i;	// ループ用
	
	// オブジェクトデータ作成
	data = sys_AllocMemory( heap, sizeof(SWSP_PLTT) * num );
	GF_ASSERT( data );

	for(i=0;i<num;i++){
		cleanPltt( data + i );
	}

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	空のオブジェデータ取得
 *
 *	@param	sys		取得先スプライトシステムデータ
 *
 *	@return	SWSP_OBJ*	空のオブジェクトデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ* getCleanObj( SWSP_SYS* sys )
{
	int i;		// ループ用

	for(i=0;i<sys->obj_num;i++ ){
		if( sys->obj_tbl[ i ].use == FALSE ){
			return ( sys->obj_tbl + i );
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	空のキャラクタデータ取得
 *
 *	@param	sys		ソフトウェアスプライトシステムデータ
 *
 *	@return	SWSP_CHAR*	空のキャラクタデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_CHAR* getCleanChar( SWSP_SYS* sys )
{
	int i;		// ループ用

	for(i=0;i<sys->obj_num;i++ ){
		if( sys->char_tbl[ i ].vramKey == 0 ){
			return ( sys->char_tbl + i );
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	空のパレットデータ取得
 *
 *	@param	sys		ソフトウェアスプライトシステムデータ
 *
 *	@return	SWSP_PLTT*	空のパレット
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_PLTT* getCleanPltt( SWSP_SYS* sys )
{
	int i;		// ループ用

	for(i=0;i<sys->obj_num;i++ ){
		if( sys->pltt_tbl[ i ].vramKey == 0 ){
			return ( sys->pltt_tbl + i );
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータを転送する分のVramKeyを取得
 *
 *	@param	pChar	VramKeyを取得するキャラクタ
 *
 *	@return	NNSGfdTexKey	テクスチャ用VramKey
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSGfdTexKey getCharVramKey( NNSG2dCharacterData* pChar )
{
	return NNS_GfdAllocTexVram( pChar->szByte, FALSE, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレット本数からVramKeyを取得
 *
 *	@param	pltt_num	パレット本数（１６色で計算）
 *
 *	@return	NNSGfdPlttKey	パレットVramKey
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSGfdPlttKey getPlttVramKey( int pltt_num )
{ 
	return NNS_GfdAllocPlttVram( pltt_num * PLTT_16_SIZE, FALSE, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータ転送
 *
 *	@param	pChar		転送するキャラクタデータ
 *	@param	vramKey		転送先＆転送サイズ
 *	@param	proxy		プロクシ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void transCharData( NNSG2dCharacterData* pChar, NNSGfdTexKey vramKey, NNSG2dImageProxy* proxy )
{
	// キャラクタデータ転送
	NNS_G2dLoadImage2DMapping( 
			pChar,							// 転送キャラクタデータ
			NNS_GfdGetTexKeyAddr(vramKey),	// 転送先
			NNS_G2D_VRAM_TYPE_3DMAIN,		// 転送タイプ
			proxy );						// 転送データ格納先
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ転送
 *
 *	@param	pPltt		転送パレットデータ
 *	@param	vramKey		転送先＆転送サイズ
 *	@param	proxy		プロクシ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void transPlttData( NNSG2dPaletteData* pPltt, NNSGfdPlttKey vramKey, NNSG2dImagePaletteProxy* proxy )
{
	int tmp_size;		// 元サイズ保存
	
	// パレット転送データサイズを変更
	tmp_size = pPltt->szByte;
	pPltt->szByte = NNS_GfdGetPlttKeySize( vramKey );
	
	// パレットデータ転送
	NNS_G2dLoadPalette( 
			pPltt,
			NNS_GfdGetPlttKeyAddr( vramKey ),
			NNS_G2D_VRAM_TYPE_3DMAIN,
			proxy
			);

	// パレットサイズを戻す
	pPltt->szByte = tmp_size;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	１オブジェの表示
 *
 *	@param	data	オブジェデータ
 *	@param	z_offs	Zオフセット
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void darwObj( SWSP_OBJ* data )
{
	NNSG2dSVec2 uv0, uv1;
	
	G3_PushMtx();

	G3_MaterialColorDiffAmb(data->diffcolor,        // diffuse
							GX_RGB(31, 31, 31),        // ambient
							TRUE                       // use diffuse as vtx color if TRUE
							);

	G3_MaterialColorSpecEmi(GX_RGB(16, 16, 16),        // specular
							GX_RGB(0, 0, 0),           // emission
							FALSE                      // use shininess table if TRUE
							);
	
	
	// テクスチャ設定
	G3_TexImageParam( 
			data->tex_attr->fmt,		// テクスチャフォーマット
            GX_TEXGEN_TEXCOORD,         // テクスチャコード
            data->tex_attr->sizeS,      // テクスチャサイズ
            data->tex_attr->sizeT,      // テクスチャサイズ
            GX_TEXREPEAT_NONE,          // リピートさせるか
            GX_TEXFLIP_NONE,            // フリップさせるか
            data->tex_attr->plttUse,    // colorパレット０を抜け色にするか
            data->tex_addr              // テクスチャアドレス
            );

	// パレットフォーマットならば...
	G3_TexPlttBase( (u32)(data->pltt_addr + (32 * data->pltt_offs)), data->tex_attr->fmt );                                
	
	// ポリゴンアトリビュート設定
	G3_PolygonAttr(GX_LIGHTMASK_NONE,           // disable lights
                   GX_POLYGONMODE_MODULATE,     // modulation mode
                   GX_CULL_NONE,                // cull back
                   0,							// polygon ID(0 - 63)
                   data->alpha,                 // alpha(0 - 31)
                   0                // OR of GXPolygonAttrMisc's value
                   );	
	
	// フリップ
	if(data->flipH){
		uv0.x = data->size.x;
		uv1.x = 0;
	}else{
		uv1.x = data->size.x;
		uv0.x = 0;
	}
	
	if(data->flipV){
		uv0.y = data->size.y;
		uv1.y = 0;
	}else{
		uv1.y = data->size.y;
		uv0.y = 0;
	}
	
	// 中心座標で回転拡大
	G3_Translate( 
			(data->matrix.x + data->center.x) * FX32_ONE,
			(data->matrix.y + data->center.y) * FX32_ONE,
			data->priority * FX32_ONE );
	// Z軸回転
    G3_RotZ( FX_SinIdx( data->rotZ ), FX_CosIdx( data->rotZ ) );
	// 拡縮値
	G3_Scale( data->scale_x, data->scale_y, FX32_ONE );

	// 座標設定（左上）	イメージクリップなどで使用しているため左上を変更することはできない
	G3_Translate( 
			-data->center.x * FX32_ONE,
			-data->center.y * FX32_ONE,
			0 );

	
	// 描画
	NNS_G2dDrawSpriteFast( 
			0, 0, 0,
			data->size.x, data->size.y,
			uv0.x, uv0.y,
			uv1.x, uv1.y );

	G3_PopMtx(1);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトデータを設定する
 *
 *	@param	obj			オブジェクトデータ
 *	@param	add			登録データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setSpriteData( SWSP_OBJ* obj, const SWSP_ADDDATA* add )
{
	int i;
	int size_x, size_y;
	fx32 l_u, l_v;	// 左上UV
	fx32 r_u, r_v;	// 右下UV
	
	// UV値設定
	size_x = 8;
	for(i=0;i<add->p_char->imgProxy.attr.sizeS;i++){
		size_x *= 2;
	}//*/
	size_y = 8;
	for(i=0;i<add->p_char->imgProxy.attr.sizeT;i++){
		size_y *= 2;
	}//*/
	
	l_u = 0;
	l_v = 0;
	r_u = size_x << FX32_SHIFT;
	r_v = size_y << FX32_SHIFT;

	// 座標設定
	SWSP_SetSpritePos( obj, add->m_x, add->m_y );

	// 中心座標
	SWSP_SetSpriteCenterPos( obj, size_x / 2, size_y / 2 );

	// 拡縮値
	obj->scale_x = FX32_ONE;
	obj->scale_y = FX32_ONE;

	// サイズ設定
	SWSP_SetSpriteSize( obj, size_x, size_y );

	//　優先順位設定
	SWSP_SetSpritePriority( obj, add->pri );

	// α値設定
	SWSP_SetSpriteAlpha( obj, add->alpha );

	// テクスチャアトリビュート設定
	SWSP_SetSpriteTexAttr( obj, &add->p_char->imgProxy.attr );

	// テクスチャアドレス設定
	SWSP_SetSpriteTexAddr( obj, NNS_G2dGetImageLocation( &add->p_char->imgProxy, NNS_G2D_VRAM_TYPE_3DMAIN ) );

	// パレットアドレス設定
	SWSP_SetSpritePlttAddr( obj, NNS_G2dGetImagePaletteLocation( &add->p_pltt->imgProxy, NNS_G2D_VRAM_TYPE_3DMAIN ) );

	// パレットオフセット設定
	SWSP_SetSpritePlttOffs( obj, add->pltt_offs );
	

	// フリップ設定
	SWSP_SetSpriteFlip( obj, SWSP_FLIPH, FALSE );
	SWSP_SetSpriteFlip( obj, SWSP_FLIPV, FALSE );

	SWSP_SetSpriteRotZ( obj, add->rota );
}

