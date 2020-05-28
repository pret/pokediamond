//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_preview.h
 *	@brief		preview画面
 *	@author		tomoya takahashi
 *	@data		2006.06.05
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_PREVIEW_H__
#define __IMC_PREVIEW_H__

#include "include/system/procsys.h"

#undef GLOBAL
#ifdef	__IMC_PREVIEW_H_GLOBAL
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
//	テレビ　コンテスト　フラグ
//=====================================
enum{
	IMC_PREV_TV,
	IMC_PREV_CON,
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	イメージクリップ外部データ
//=====================================
typedef struct {
	// イメージクリップセーブ領域
	IMC_SAVEDATA* p_imc_data;
	u32 data_idx;	// セーブデータ配列インデックス
	u32	prev_type;	// previewタイプ　
					// IMC_PREV_TV,
					// IMC_PREV_CON,
} IMC_PROC_PREV_WORK;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT IMC_Prev_ProcInit( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_Prev_ProcMain( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_Prev_ProcEnd( PROC* proc, int* seq );


#undef	GLOBAL
#endif		// __IMC_PREVIEW_H__

