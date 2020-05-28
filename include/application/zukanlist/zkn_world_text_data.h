//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_world_text_data.h
 *	@brief		図鑑世界テキストデータ　とゲーム内国コードをリンクさせるデータ
 *	@author		tomoya takahashi	
 *	@data		2006.03.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_WORLD_TEXT_DATA_H__
#define __ZKN_WORLD_TEXT_DATA_H__

#undef GLOBAL
#ifdef	__ZKN_WORLD_TEXT_DATA_H_GLOBAL
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
//	外国語テキスト用国コード
//=====================================
enum{
	ZKN_WORLD_TEXT_JAPAN,		// 日本
	ZKN_WORLD_TEXT_E,			// アメリカ
	ZKN_WORLD_TEXT_FRA,			// フランス
	ZKN_WORLD_TEXT_GER,			// ドイツ
	ZKN_WORLD_TEXT_ITA,			// イタリア
	ZKN_WORLD_TEXT_SPA,			// スペイン
	ZKN_WORLD_TEXT_NUM
};

#define ZKN_WORLD_TEXT_OUTWORLD_NUM	( ZKN_WORLD_TEXT_NUM-1  )	// 外国項目データの数
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

GLOBAL int ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( int lang_code );
GLOBAL int ZKN_WT_GetZKN_WORLD_TEXT_Code_LANG_Code( int world_text_code );
GLOBAL int ZKN_WT_GetMonsNo_TEXTVERPokeNum( int monsno );


#undef	GLOBAL
#endif		// __ZKN_WORLD_TEXT_DATA_H__

