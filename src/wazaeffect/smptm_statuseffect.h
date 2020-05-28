//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		smptm_statuseffect.h
 *	@brief		サンプル ステータス エフェクト
 *	@author		tomoya takahashi
 *	@data		2005.12.16
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __SMPTM_STATUSEFFECT_H__
#define __SMPTM_STATUSEFFECT_H__

#include "system/clact_tool.h"
#include "system/softsprite.h"

#undef GLOBAL
#ifdef	__SMPTM_STATUSEFFECT_H_GLOBAL
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
// 必要なGRAPHICSデータ
typedef struct{
	SOFT_SPRITE*		ss;
	CATS_SYS_PTR		csp;
	PALETTE_FADE_PTR	pfd;
} SMPTM_GRAPHIC_PARAM;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ステータス　エフェクト　開始
 *
 *	@param	status			ステータス
 *	@param	client_type		クライアントタイプ
 *	@param	p_end			終了チェックフラグ
 *	@param	gra				グラフィックパラメータ
 *	@param	heap			使用ヒープ
 *
 *	@return	none
 *
 * status
 *		STATUS_NORMAL	(0)		//状態異常なし
 * 		STATUS_NEMURI	(1)		//眠り
 *		STATUS_DOKU		(2)		//毒
 *		STATUS_YAKEDO	(3)		//やけど
 * 		STATUS_KOORI	(4)		//こおり
 *		STATUS_MAHI		(5)		//まひ
 *
 * p_end
 *		TRUE	終了
 *		FALSE	エフェクト中
 */
//-----------------------------------------------------------------------------
GLOBAL void STATUSEFF_SampStart( int status, int client_type, BOOL* p_end, const SMPTM_GRAPHIC_PARAM* cp_gra, int heap );

#if 0
// デバッグ
GLOBAL void Debug_SmpTm( WE_SYS_PTR we_sys );
#endif

#undef	GLOBAL
#endif		// __SMPTM_STATUSEFFECT_H__
