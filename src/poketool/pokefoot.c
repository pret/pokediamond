//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		pokefoot.c
 *	@brief		ポケモン足跡グラフィックデータ取得関数
 *	@author		tomoya takahashi
 *	@data		2006.01.31
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "include/system/arc_util.h"
#include "include/system/arc_tool.dat"
#include "include/poketool/monsno.h"

#define	__POKEFOOT_H_GLOBAL
#include "include/poketool/pokefoot.h"

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
#define POKEFOOT_ARC_PLTT		( 0 )		// パレットインデックス
#define POKEFOOT_ARC_CELL		( 2 )		// セルインデックス
#define POKEFOOT_ARC_CELLANM	( 1 )		// セルアニメインデックス
#define POKEFOOT_ARC_CHAR_DMMY	( 3 )		// poke_foot_000
#define POKEFOOT_ARC_CHAR_START	( 4	)		// キャラクタ開始インデックス

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
//----------------------------------------------------------------------------
/**
 *	@brief	モンスターナンバーから足跡キャラクタデータ取得
 *
 *	@param	mons_no		モンスターナンバー
 *	@param	heap		ヒープ
 *	@param	alloc_type	アロックタイプ
 *
 *	@return	ファイルデータ
 */
//-----------------------------------------------------------------------------
void* PokeFootCharPtrGet( int mons_no, int heap, ALLOC_TYPE alloc_type )
{	
	void* p_buff;
	
	GF_ASSERT( mons_no <= MONSNO_END );

	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_CHAR_DMMY + mons_no, TRUE, heap, alloc_type );

	// 取得失敗
	GF_ASSERT( p_buff );

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡パレットデータ取得
 *
 *	@param	heap	ヒープ
 *	@param	alloc_type	アロックタイプ
 *
 *	@return	ファイルデータ
 */
//-----------------------------------------------------------------------------
void* PokeFootPlttPtrGet( int heap, ALLOC_TYPE alloc_type )
{
	void* p_buff;
	
	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_PLTT, FALSE, heap, alloc_type );

	// 取得失敗
	GF_ASSERT( p_buff );

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡セルデータ取得
 *
 *	@param	heap	ヒープ
 *	@param	alloc_type	アロックタイプ
 *
 *	@return	ファイルデータ
 */
//-----------------------------------------------------------------------------
void* PokeFootCellPtrGet( int heap, ALLOC_TYPE alloc_type )
{
	void* p_buff;
	
	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_CELL, TRUE, heap, alloc_type );

	// 取得失敗
	GF_ASSERT( p_buff );

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡セルアニメデータ取得
 *
 *	@param	heap	ヒープ
 *	@param	alloc_type	アロックタイプ
 *
 *	@return	ファイルデータ
 */
//-----------------------------------------------------------------------------
void* PokeFootCellAnmPtrGet( int heap, ALLOC_TYPE alloc_type )
{
	void* p_buff;
	
	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_CELLANM, TRUE, heap, alloc_type );

	// 取得失敗
	GF_ASSERT( p_buff );

	return p_buff;
}



// アーカイブファイルIDX　データIDX
//----------------------------------------------------------------------------
/**
 *	@brief	アーカイブファイルIDX取得
 *
 *	@param	none	
 *
 *	@return	アーカイブファイルIDX
 */
//-----------------------------------------------------------------------------
int PokeFootArcFileGet( void )
{
	return ARC_POKEFOOT_GRA;
}

//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタデータIDX取得
 *
 *	@param	mons_no		モンスターナンバー
 *
 *	@return	キャラクタデータIDX
 */
//-----------------------------------------------------------------------------
int PokeFootCharDataIdxGet( int mons_no )
{
	return POKEFOOT_ARC_CHAR_DMMY + mons_no;
}
//----------------------------------------------------------------------------
/**
 *	@brief	パレットデータIDX取得
 *
 *	@param	none
 *
 *	@return	パレットデータIDX
 */
//-----------------------------------------------------------------------------
int PokeFootPlttDataIdxGet( void )
{
	return POKEFOOT_ARC_PLTT;
}
//----------------------------------------------------------------------------
/**
 *	@brief	セルデータIDX取得
 *
 *	@param	none
 *
 *	@return	セルデータIDX
 */
//-----------------------------------------------------------------------------
int PokeFootCellDataIdxGet( void )
{
	return POKEFOOT_ARC_CELL;
}
//----------------------------------------------------------------------------
/**
 *	@brief	セルアニメデータIDX取得
 *
 *	@param	none
 *
 *	@return	セルアニメデータIDX
 */
//-----------------------------------------------------------------------------
int PokeFootCellAnmDataIdxGet( void )
{
	return POKEFOOT_ARC_CELLANM;
}

