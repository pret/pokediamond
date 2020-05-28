//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_textver.h
 *	@brief		図鑑言語バージョン
 *	@author		tomoya takahashi
 *	@data		2006.02.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_TEXTVER_H__
#define __ZKN_ZUKAN_TEXTVER_H__

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_TEXTVER_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
enum{
	ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST,	// ポケリストとの行き来
	ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL,		// 通常
	ZKK_ZUKANTEXTVER_FADE_MODE_OTHER,		// その他画面へ
};

// ポケモンリスト座標
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_IX	( 172 )
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_IY	( 32 )

// ポケモングラフィック座標
#define ZKN_ZUKANTEXTVER_POKEGRA_MAT_X	( 48 )
#define ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y	( 72 )


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
GLOBAL void ZKN_ZukanTextverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanTextverAplDelete( ZKN_APL_DATA* p_data );


// アプリデータ外部変更関数
GLOBAL void ZKN_ZukanTextverPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y );
GLOBAL void ZKN_ZukanTextverFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode );

// 次のページへ
GLOBAL BOOL ZKN_ZukanTexverPageAdd( ZKN_APL_DATA* p_data );
GLOBAL BOOL ZKN_ZukanTexverPageSet( ZKN_APL_DATA* p_data, int page );

// 国コード設定
GLOBAL void ZKN_ZukanTexverTypeSet( ZKN_APL_DATA* p_data, int lang );

#undef	GLOBAL
#endif		// __ZKN_ZUKAN_TEXTVER_H__

