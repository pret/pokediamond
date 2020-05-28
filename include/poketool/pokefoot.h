//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		pokefoot.h
 *	@brief		ポケモン足跡グラフィックデータ取得関数
 *	@author		tomoya takahashi
 *	@data		2006.01.31
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __POKEFOOT_H__
#define __POKEFOOT_H__

#undef GLOBAL
#ifdef	__POKEFOOT_H_GLOBAL
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
 *	@return	ファイルデータ	破棄は各自
 * [allocType]
 *		ALLOC_TOP		ヒープ先頭から確保
 *		ALLOC_BOTTOM	ヒープ後方から確保
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootCharPtrGet( int mons_no, int heap, ALLOC_TYPE alloc_type );
//----------------------------------------------------------------------------
/**
 *	@brief	足跡パレットデータ取得
 *
 *	@param	heap	ヒープ
 *	@param	alloc_type	アロックタイプ
 *
 *	@return	ファイルデータ	破棄は各自
 * [allocType]
 *		ALLOC_TOP		ヒープ先頭から確保
 *		ALLOC_BOTTOM	ヒープ後方から確保
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootPlttPtrGet( int heap, ALLOC_TYPE alloc_type );
//----------------------------------------------------------------------------
/**
 *	@brief	足跡セルデータ取得
 *
 *	@param	heap	ヒープ
 *	@param	alloc_type	アロックタイプ
 *
 *	@return	ファイルデータ	破棄は各自
 * [allocType]
 *		ALLOC_TOP		ヒープ先頭から確保
 *		ALLOC_BOTTOM	ヒープ後方から確保
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootCellPtrGet( int heap, ALLOC_TYPE alloc_type );
//----------------------------------------------------------------------------
/**
 *	@brief	足跡セルアニメデータ取得
 *
 *	@param	heap	ヒープ
 *	@param	alloc_type	アロックタイプ
 *
 *	@return	ファイルデータ	破棄は各自
 * [allocType]
 *		ALLOC_TOP		ヒープ先頭から確保
 *		ALLOC_BOTTOM	ヒープ後方から確保
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootCellAnmPtrGet( int heap, ALLOC_TYPE alloc_type );

// アーカイブファイルIDX　データIDX
// キャラクタ　セル　セルアニメデータは圧縮されています
GLOBAL int PokeFootArcFileGet( void );
GLOBAL int PokeFootCharDataIdxGet( int mons_no );
GLOBAL int PokeFootPlttDataIdxGet( void );
GLOBAL int PokeFootCellDataIdxGet( void );
GLOBAL int PokeFootCellAnmDataIdxGet( void );


#undef	GLOBAL
#endif		// __POKEFOOT_H__

