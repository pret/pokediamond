//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		zkn_height_gram.h
 *	@brief		ポケモン高さ　重さデータアクセス
 *	@author		tomoya takahashi 
 *	@data		2006.02.02
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_HEIGHT_GRAM_H__
#define __ZKN_HEIGHT_GRAM_H__

#undef GLOBAL
#ifdef	__ZKN_HEIGHT_GRAM_H_GLOBAL
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
//	データタイプ
//=====================================
enum{
	ZKN_HEIGHT_GRAM_TYPE_MAN,	// 主人公男時
	ZKN_HEIGHT_GRAM_TYPE_GIRL,	// 主人公女時
};


// 拡縮値基準値
#define ZKN_HEIGHT_SCALDE_DEF	( 0x100 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
typedef struct _ZKN_HEIGHT_GRAM* ZKN_HEIGHT_GRAM_PTR;
typedef const struct _ZKN_HEIGHT_GRAM* CONST_ZKN_HEIGHT_GRAM_PTR;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_HEIGHT_GRAM_PTR ZKN_HEIGHTGRAM_Alloc( int heap );
GLOBAL void ZKN_HEIGHTGRAM_Free( ZKN_HEIGHT_GRAM_PTR p_heightgram );

GLOBAL void ZKN_HEIGHTGRAM_Load( ZKN_HEIGHT_GRAM_PTR p_heightgram, int type, int heap );
GLOBAL void ZKN_HEIGHTGRAM_Release( ZKN_HEIGHT_GRAM_PTR p_heightgram );

GLOBAL int ZKN_HEIGHTGRAM_GetHeight( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no );
GLOBAL int ZKN_HEIGHTGRAM_GetGram( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no );

GLOBAL short ZKN_HEIGHTGRAM_GetHeightY_hero( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no );
GLOBAL short ZKN_HEIGHTGRAM_GetHeightY_poke( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no );
GLOBAL short ZKN_HEIGHTGRAM_GetHeightScale_hero( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no );
GLOBAL short ZKN_HEIGHTGRAM_GetHeightScale_poke( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no );


#undef	GLOBAL
#endif		// __ZKN_HEIGHT_GRAM_H__

