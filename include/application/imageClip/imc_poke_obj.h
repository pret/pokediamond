//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_poke_obj.h
 *	@brief		イメージクリップポケモン データ
 *	@author		tomoya takahashi
 *	@data		2005.09.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_POKE_OBJ_H__
#define __IMC_POKE_OBJ_H__

#include "system.h"
#include "system/gamedata.h"
#include "touchpanel.h"
#include "system/softsprite.h"
#include "poketool/poke_tool.h"
#include "include/application/imageClip/imc_drawsys.h"

#undef GLOBAL
#ifdef	__IMC_POKE_OBJ_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define IMC_POKE_INIT_X			(192)
#define IMC_POKE_INIT_Y			(56)
#define	IMC_POKE_DEFAULT_PRI	(0)

#define	IMC_POKE_ANM_NUM		(2)

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	食い込んでよいサイズテーブル
//	
//=====================================
typedef struct {
	u16	x_no;
	u16	y_no;
} IMC_POKE_INS_DAT;

//-------------------------------------
//	
//	イメージクリップポケモン構造体
//	
//=====================================
typedef struct {
	SOFT_SPRITE*		sprite;		// スプライトデータ

	TP_HIT_TBL hit_tbl;	// 当たり判定データ
	
	u8	ins_x;			// パレットに食い込んでよいサイズX
	u8	ins_y;			// パレットに食い込んでよいサイズY
	
	// ポケモンデータ
	POKEMON_PARAM* poke_para;
} IMC_POKE;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンのキャラクタデータを描画システムに登録
 *
 *	@param	poke_para		ポケモンパラメータ構造体
 *	@param	drawData		描画システムデータ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_CharSet( IMC_DRAW_DATA* drawData, SOFT_SPRITE_ARC* arc_data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ　ポケモンデータ作成
 *
 *	@param	poke			イメージクリップ　ポケモンデータ
 *	@param	sprite_man		ソフトウェアスプライトマネージャ
 *	@param	poke_para		ポケモンパラメータ構造体
 *	@param	arc_data		アーカイブファイルデータ
 *	@param	heap			ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_Init( IMC_POKE* poke,  SOFT_SPRITE_MANAGER* sprite_man, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ　ポケモンデータ破棄
 *
 *	@param	poke			イメージクリップ　ポケモンデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_Delete( IMC_POKE* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示優先順位を設定
 *
 *	@param	poke		ポケモンデータ
 *	@param	priority	優先順位
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_DrawPrioritySet( IMC_POKE* poke, int priority );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示優先順位を取得
 *
 *	@param	poke		ポケモンデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_POKE_DrawPriorityGet( IMC_POKE* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	座標を設定
 *
 *	@param	poke		ポケモンデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_MatrixSet( IMC_POKE* poke, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン座標を取得
 *
 *	@param	poke		ポケモンデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_MatrixGet( IMC_POKE* poke, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンサイズを取得
 *
 *	@param	poke		ポケモンデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_SizeGet( IMC_POKE* poke, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンとタッチパネルの当たり判定
 *
 *	@param	poke	ポケモンデータ
 *
 *	@retval	TRUE	あたり
 *	@retval	FALSE	あたらない
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHit( IMC_POKE* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンと指定座標の当たり判定
 *
 *	@param	poke	ポケモンデータ
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@retval	TRUE	あたり
 *	@retval	FALSE	あたらない
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHitSelf( IMC_POKE* poke, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を細かく行う
 *
 *	@param	poke		オブジェクトデータ
 *	@param	offs_x		左上からのオフセットｘ座標
 *	@param	offs_y		左上からのオフセットｙ座標
 *	@param	char_data	キャラクタデータ	
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった	（オフセット座標不定）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHitEx( IMC_POKE* poke, int* offs_x, int* offs_y, NNSG2dCharacterData* char_data );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を細かく行う	座標指定
 *
 *	@param	poke		オブジェクトデータ
 *	@param	x			左上からのオフセットｘ座標
 *	@param	y			左上からのオフセットｙ座標
 *	@param	char_data	キャラクタデータ	
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった	（オフセット座標不定）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHitExSelf( IMC_POKE* poke, int x, int y, NNSG2dCharacterData* char_data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンの食い込んでよいサイズを取得
 *
 *	@param	poke		オブジェクトデータ
 *	@param	ins_x		食い込んでよいサイズ取得領域
 *	@param	ins_y		食い込んでよいサイズ取得領域
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_InSizeGet( IMC_POKE* poke, int* ins_x, int* ins_y );

#undef	GLOBAL
#endif		// __IMC_POKE_OBJ_H__
