//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_playsys.h
 *	@brief		イメージクリッププレイヤーシステム
 *	@author		tomoya takahashi
 *	@data		2005.12.27
 *
 * イメージクリッププロックを作成して表示する以外の方法で
 * 表示するイメージクリッププレイヤー
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_PLAYSYS_H__
#define __IMC_PLAYSYS_H__
#include "bg_system.h"
#include "poketool/poke_tool.h"
#include "savedata/imageclip_data.h"

#undef GLOBAL
#ifdef	__IMC_PLAYSYS_H_GLOBAL
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
//-------------------------------------
//
//	イメージクリッププレイヤーシステム
//	
//=====================================
typedef struct _IMC_PLAYERSYS* IMC_PLAYERSYS_PTR;
typedef const struct _IMC_PLAYERSYS* CONST_IMC_PLAYERSYS_PTR;


//-------------------------------------
//	
//	初期化データ
//	
//=====================================
typedef struct {
	GF_BGL_INI* p_bg_ini;	// BGシステム	NOBGのときはNULLでOK
							// GF_BGL_FRAME2_Mのコントロールセットを内部で行います。
	int x;				// 全体の中心
	int y;				// 全体の中心
	int heap_id;		// 使用するヒープID
} IMC_PLAYERSYS_INIT;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププレイヤー生成
 *
 *	@param	cp_init		初期化データ
 *	@param	save_data	セーブデータ
 *
 *	@return	生成されたデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data );
GLOBAL IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data );
GLOBAL IMC_PLAYERSYS_PTR IMC_ContestPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data );
GLOBAL IMC_PLAYERSYS_PTR IMC_ContestPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププレイヤーメイン
 *
 *	@param	p_sys		イメージクリッププレイヤーシステム
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_PlayerMain( IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププレイヤー終了
 *
 *	@param	p_sys		イメージクリッププレイヤーシステム
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_PlayerEnd( IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank期間中に呼ぶ関数
 *
 *	@param	p_sys	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_PlayerVblank( IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	描画　フラグ
 *			TRUE　描画　		FALSE	非描画
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag );
GLOBAL BOOL IMC_Player_GetDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ描画　フラグ
 *			TRUE　描画　		FALSE	非描画
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetAcceDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag );
GLOBAL BOOL IMC_Player_GetAcceDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	座標 回転　拡縮
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y );
GLOBAL void IMC_Player_SetRota( IMC_PLAYERSYS_PTR p_sys, u16 rota );
GLOBAL void IMC_Player_SetScale( IMC_PLAYERSYS_PTR p_sys, fx32 x, fx32 y, fx32 z );
GLOBAL void IMC_Player_SetRotScaleCenterOfs( IMC_PLAYERSYS_PTR p_sys, int x, int y );
GLOBAL void IMC_Player_SetRotScaleCenterOfs( IMC_PLAYERSYS_PTR p_sys, int x, int y );

//-----------------------------------------------------------------------------
/**
 *	@brief	全体的な描画色
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetColor( IMC_PLAYERSYS_PTR p_sys, GXRgb color );
GLOBAL GXRgb IMC_Player_GetColor( CONST_IMC_PLAYERSYS_PTR cp_sys );

//-----------------------------------------------------------------------------
/**
 *	@brief	ポケモンを中心とした座標と中心オフセットの設定
 *
 *	@param	p_sys	ワーク
 *	@param	x		ｘ座標	（ここは左上ではなくポケモンの中心座標）
 *	@param	y		ｙ座標	（ここは左上ではなくポケモンの中心座標）
 *
 *	@param	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetPokeMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y );

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンの足跡座標を設定する
 *
 *	@param	p_sys	ワーク
 *	@param	x		ｘ座標	（ここは左上ではなくポケモンの足元座標）
 *	@param	y		ｙ座標	（ここは左上ではなくポケモンの足元座標）
 *	@param	height	そのポケモンの高さ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetPokeMatrix_Ground( IMC_PLAYERSYS_PTR p_sys, int x, int y, int height );


//-----------------------------------------------------------------------------
/**
 *	@brief	優先順位を設定	先頭のアクセサリの優先順位
 *
 *	@param	p_sys	ワーク
 *	@param	pri		ポケモンの優先順位（ソフトウェアスプライトの）
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetPriority( IMC_PLAYERSYS_PTR p_sys, int pri );
GLOBAL void IMC_Player_AddPriority( IMC_PLAYERSYS_PTR p_sys, int pri );



#ifdef PM_DEBUG
#include "include/system/procsys.h"

//-------------------------------------
//	イメージクリップ外部データ
//=====================================
typedef struct {
	// イメージクリップセーブ領域
	const IMC_TELEVISION_SAVEDATA* p_imc_one_data;
} IMC_PROC_PLAY_WORK;

// チェック用プロック
GLOBAL PROC_RESULT IMC_PlayTelevision_ProcInit( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_PlayTelevision_ProcMain( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_PlayTelevision_ProcEnd( PROC* proc, int* seq );
#endif

#undef	GLOBAL
#endif		// __IMC_PLAYSYS_H__

