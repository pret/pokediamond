//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan.h
 *	@brief		図鑑サブ画面
 *	@author		tomoya takahashi	
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_H__
#define __ZKN_ZUKAN_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#include "include/application/zukanlist/zkn_zukan_common.h"

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_H_GLOBAL
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
	ZKN_ZUKAN_FADE_MODE_CHPOKELIST,	// ポケリストとの行き来
	ZKK_ZUKAN_FADE_MODE_NORMAL,		// 通常
	ZKK_ZUKAN_FADE_MODE_OTHER,		// その他画面へ
};

// ポケモンリスト座標
#define ZKN_ZUKAN_POKELIST_MAT_IX	( 172 )
#define ZKN_ZUKAN_POKELIST_MAT_IY	( 32 )

// ポケモングラフィック座標
#define ZKN_ZUKAN_POKEGRA_MAT_X	( 48 )
#define ZKN_ZUKAN_POKEGRA_MAT_Y	( 72 )


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑画面　グローバル変数
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ

	int poke_gra_move_x;					// ポケグラ動作先
	int poke_gra_move_y;					// ポケグラ動作先

	// 図鑑コモンアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;
	int					fade_mode;			// フェードモード

	int zukan_page;		// 表示図鑑ページ

	BOOL mons_snd_req;	// ポケモンの声リクエスト
} ZKN_ZUKAN_GLB;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_ZukanAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanAplDelete( ZKN_APL_DATA* p_data );

GLOBAL BOOL ZKN_ZukanAplPageAdd( ZKN_ZUKAN_GLB* p_data, int add );
GLOBAL BOOL ZKN_ZukanAplPageSet( ZKN_ZUKAN_GLB* p_data, int set );


// 捕獲図鑑画面用
GLOBAL GF_BGL_BMPWIN* ZknZukanPokeTypeTextBmpMake( ZKN_FONTOAM_SYS_PTR p_fontoamsys, int mons_no, int heap );
GLOBAL int ZknZukanClactTypeNoChg( int type );
GLOBAL void ZknZukanSetUpFontBg_Minute( GF_BGL_BMPWIN* p_bmp, int monsno, int heap, int page, u32 color_msk );

// ～ポケモン座標
#define ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_X	( -58 )
#define ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_Y	( -8 )
#define ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCX	( 16 )
#define ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCY	( 2 )
#define ZKN_ZUKAN_POKETYPE_TEXT_TBL_SEQ	( 0x11 )

// タイプアニメシーケンス
enum{
	ZKN_ZUKAN_POKETYPE_NORMAL = 0,
};

#undef	GLOBAL
#endif		// __ZKN_ZUKAN_H__

