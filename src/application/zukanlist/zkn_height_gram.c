//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		zkn_height_gram.c
 *	@brief		ポケモン高さ　重さアクセス
 *	@author		tomoya takahashi 
 *	@data		2006.02.02
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "src/application/zukanlist/zkn_data/zukan_data.naix"

#define __ZKN_HEIGHT_GRAM_H_GLOBAL
#include "include/application/zukanlist/zkn_height_gram.h"

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
//	高さ重さ情報
//=====================================
typedef struct _ZKN_HEIGHT_GRAM{
	int* p_height;
	int* p_gram;

	// 描画関係
	short* p_height_y;
	short* p_height_y_poke;
	short* p_height_scale;
	short* p_height_scale_poke;
} ZKN_HEIGHT_GRAM;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static int* LoadHeight( int heap );
static int* LoadGram( int heap );
static void LoadHeightY_man( short** p_hero, short** p_poke, int heap );
static void LoadHeightY_girl( short** p_hero, short** p_poke, int heap );
static void LoadHeightScale_man( short** p_hero, short** p_poke, int heap );
static void LoadHeightScale_girl( short** p_hero, short** p_poke, int heap );

//----------------------------------------------------------------------------
/**
 *	@brief	高さ重さ情報格納エリア作成
 *
 *	@param	heap	使用ヒープ
 *
 *	@return	エリア
 */
//-----------------------------------------------------------------------------
ZKN_HEIGHT_GRAM_PTR ZKN_HEIGHTGRAM_Alloc( int heap )
{
	ZKN_HEIGHT_GRAM_PTR p_heightgram;

	p_heightgram = sys_AllocMemory( heap, sizeof(ZKN_HEIGHT_GRAM) );
	memset( p_heightgram, 0, sizeof(ZKN_HEIGHT_GRAM) );

	return p_heightgram;
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ重さ情報格納エリア破棄
 *
 *	@param	p_heightgram	破棄data
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_HEIGHTGRAM_Free( ZKN_HEIGHT_GRAM_PTR p_heightgram )
{
	GF_ASSERT( p_heightgram );

	sys_FreeMemoryEz( p_heightgram );
	p_heightgram = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ重さ情報読み込み
 *
 *	@param	p_heightgram	格納エリア
 *	@param	type			データタイプ
 *	@param	heap			ヒープ
 *
 *	@return	none
 *
 * type
 *		ZKN_HEIGHT_GRAM_TYPE_MAN,	// 主人公男
 *		ZKN_HEIGHT_GRAM_TYPE_GIRL,	// 主人公女
 *	
 */
//-----------------------------------------------------------------------------
void ZKN_HEIGHTGRAM_Load( ZKN_HEIGHT_GRAM_PTR p_heightgram, int type, int heap )
{
	GF_ASSERT( p_heightgram );

	// 読み込み済みですよ。
	GF_ASSERT(p_heightgram->p_height == NULL);
	GF_ASSERT(p_heightgram->p_gram == NULL);

	p_heightgram->p_height = LoadHeight( heap );
	p_heightgram->p_gram = LoadGram( heap );

	// 表示パラメータ
	if( type == ZKN_HEIGHT_GRAM_TYPE_MAN ){
		LoadHeightY_man( &p_heightgram->p_height_y, &p_heightgram->p_height_y_poke, heap );
		LoadHeightScale_man( &p_heightgram->p_height_scale, &p_heightgram->p_height_scale_poke, heap );
	}else{
		LoadHeightY_girl( &p_heightgram->p_height_y, &p_heightgram->p_height_y_poke, heap );
		LoadHeightScale_girl( &p_heightgram->p_height_scale, &p_heightgram->p_height_scale_poke, heap );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ重さ情報破棄
 *
 *	@param	p_heightgram	破棄data
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_HEIGHTGRAM_Release( ZKN_HEIGHT_GRAM_PTR p_heightgram )
{
	GF_ASSERT( p_heightgram->p_height );
	GF_ASSERT( p_heightgram->p_gram );
	
	sys_FreeMemoryEz( p_heightgram->p_height );
	sys_FreeMemoryEz( p_heightgram->p_gram );

	sys_FreeMemoryEz( p_heightgram->p_height_y );
	sys_FreeMemoryEz( p_heightgram->p_height_y_poke );
	sys_FreeMemoryEz( p_heightgram->p_height_scale );
	sys_FreeMemoryEz( p_heightgram->p_height_scale_poke );
	
	p_heightgram->p_height	= NULL;
	p_heightgram->p_gram	= NULL;
	p_heightgram->p_height_y = NULL;
	p_heightgram->p_height_y_poke = NULL;
	p_heightgram->p_height_scale = NULL;
	p_heightgram->p_height_scale_poke = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ情報取得
 *
 *	@param	cp_heightgram		高さ重さ情報
 *	@param	mons_no				モンスターナンバー
 *
 *	@return	高さを10倍した値
 */
//-----------------------------------------------------------------------------
int ZKN_HEIGHTGRAM_GetHeight( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height );
	return cp_heightgram->p_height[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	重さ情報取得
 *
 *	@param	cp_heightgram		高さ重さ情報
 *	@param	mons_no				モンスターナンバー
 *
 *	@return	重さを10倍した値
 */
//-----------------------------------------------------------------------------
int ZKN_HEIGHTGRAM_GetGram( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_gram );
	return cp_heightgram->p_gram[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ比べ　主人公の表示オフセット位置
 *
 *	@param	cp_heightgram		データワーク
 *	@param	mons_no				ポケモンナンバー
 *
 *	@return	オフセット値
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightY_hero( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_y );
	return cp_heightgram->p_height_y[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ比べ　ポケモンの表示オフセット位置
 *
 *	@param	cp_heightgram	データワーク
 *	@param	mons_no			モンスターナンバー 
 *
 *	@return	オフセット値
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightY_poke( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_y_poke );
	return cp_heightgram->p_height_y_poke[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ比べ　主人公拡縮値
 *
 *	@param	cp_heightgram	データワーク
 *	@param	mons_no			モンスターナンバー
 *	
 *	@return	拡縮値
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightScale_hero( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_scale );
	return cp_heightgram->p_height_scale[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ比べ　ポケモン拡縮値
 *
 *	@param	cp_heightgram	データワーク
 *	@param	mons_no			モンスターナンバー
 *	
 *	@return	拡縮値
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightScale_poke( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_scale_poke );
	return cp_heightgram->p_height_scale_poke[ mons_no ];
}







//----------------------------------------------------------------------------
/**
 *	@brief	高さデータ読み込み
 *
 *	@param	heap	ヒープ
 *
 *	@return	読み込みデータ
 */
//-----------------------------------------------------------------------------
static int* LoadHeight( int heap )
{
	void* buff;

	buff = ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_dat, FALSE, heap, ALLOC_TOP );
	

	return (int*)buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	重さデータ読み込み
 *
 *	@param	heap	ヒープ
 *
 *	@return	読み込みデータ
 */
//-----------------------------------------------------------------------------
static int* LoadGram( int heap )
{
	void* buff;

	buff = ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_gram_dat, FALSE, heap, ALLOC_TOP );

	return (int*)buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ表示時Y座標配列
 *
 *	@param	p_hero		主人公
 *	@param	p_poke		ポケモン
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightY_man( short** p_hero, short** p_poke, int heap )
{

	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_man_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_man_poke_dat, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ表示時Y座標配列
 *
 *	@param	p_hero		主人公
 *	@param	p_poke		ポケモン
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightY_girl( short** p_hero, short** p_poke, int heap )
{
	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_girl_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_girl_poke_dat, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ表示時拡縮値配列
 *
 *	@param	p_hero		主人公
 *	@param	p_poke		ポケモン
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightScale_man( short** p_hero, short** p_poke, int heap )
{
	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_man_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_man_poke_dat, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *	@brief	高さ表示時拡縮値配列
 *
 *	@param	p_hero		主人公
 *	@param	p_poke		ポケモン
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightScale_girl( short** p_hero, short** p_poke, int heap )
{
	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_girl_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_girl_poke_dat, FALSE, heap, ALLOC_TOP );
}	

