//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fight_text.h
 *	@brief		図鑑戦闘語のテキストデータ表示システム
 *	@author		tomoya takahashi
 *	@data		2006.03.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_FIGHT_TEXT_H__
#define __ZKN_FIGHT_TEXT_H__

#include "include/gflib/clact.h"
#include "include/system/palanm.h"
#include "include/gflib/bg_system.h"
#include "include/system/softsprite.h"

#include "include/application/zukanlist/zkn_zukan.h"

#undef GLOBAL
#ifdef	__ZKN_FIGHT_TEXT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// 回っているタスクの優先順位
#define ZKN_FIGHT_TCB_PRI		( 0 ) // タスク登録されたフレームはタスクのメインが通らないようにしておく必要があります

// ポケモングラフィック座標
#define ZKN_FIGHT_POKEGRA_MAT_X	( ZKN_ZUKAN_POKEGRA_MAT_X )
#define ZKN_FIGHT_POKEGRA_MAT_Y	( ZKN_ZUKAN_POKEGRA_MAT_Y )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑ファイトテキスト表示タスク
//=====================================
typedef struct {
	GF_BGL_INI*			p_bgl;		// BGL	(BGコントロールは再設定します)
	PALETTE_FADE_PTR	p_pfd;		// パレットフェード
	SOFT_SPRITE_MANAGER* p_ssm;		// ソフトウェアスプライト
	int					heap;		// 使用するヒープ
	POKEMON_PARAM*		p_pp;		// ポケモンパラメータ
	int					pokenum_mode;// ポケモンナンバーモード
	// PM_NUMBER_SHINOU:シンオウ   PM_NUMBER_ZENKOKU:全国
	


/*	SOFT_SPRITE* p_ssp;				// ソフトスプライトマネージャ
	int monsno;//*/
} ZKN_FIGHT_TEXT_PARAM;

typedef struct _ZKN_FIGHT_TEXT_DRAW		ZKN_FIGHT_TEXT_DRAW;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
// タスク生成
// ブラックアウト状態で渡してください
GLOBAL ZKN_FIGHT_TEXT_DRAW* ZKN_FIGHT_TextDrawReq( const ZKN_FIGHT_TEXT_PARAM* cp_param );

// 破棄
// 呼ばれた瞬間に破棄されます
GLOBAL void ZKN_FIGHT_TextDrawDelete( ZKN_FIGHT_TEXT_DRAW* p_data );

// フェードインまで完了したかチェック
GLOBAL BOOL ZKN_FIGHT_TexDrawEndCheck( const ZKN_FIGHT_TEXT_DRAW* cp_data );

// ソフトウェアスプライトを取得
GLOBAL SOFT_SPRITE* ZKN_FIGHT_TexDrawGetSsp( ZKN_FIGHT_TEXT_DRAW* p_data );

// パレットアニメONOFFフラグ
GLOBAL void ZKN_FIGHT_PalAnmFlagSet( ZKN_FIGHT_TEXT_DRAW* p_data, BOOL flag );
GLOBAL BOOL ZKN_FIGHT_PalAnmFlagGet( const ZKN_FIGHT_TEXT_DRAW* cp_data );

#undef	GLOBAL
#endif		// __ZKN_FIGHT_TEXT_H__

