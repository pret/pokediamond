//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		fog_sys.h
 *@brief	フォグシステム
 *@author	tomoya takahashi
 *@data		2005.04.27
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __FOG_SYS_H__
#define	__FOG_SYS_H__

#undef	GLOBAL
#ifdef	__FOG_SYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

#include "nnsys.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
#define	FOG_MDL_SET_CHECK

//-------------------------------------
//	コントロール定数
//=====================================
#define	FOG_SYS_FLAG	(1)		// on/offフラグ
#define	FOG_SYS_MODE	(1<<1)	// モード
#define	FOG_SYS_SLOPE	(1<<2)	// かかり具合
#define	FOG_SYS_OFFSET	(1<<3)	// オフセット
#define	FOG_SYS_RGB		(1<<4)	// 色
#define	FOG_SYS_ALPHA	(1<<5)	// α値
#define	FOG_SYS_TBL		(1<<6)	// フォグテーブル

#define	FOG_SYS_ALL		(0xffffffff)		// 全て

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
typedef struct _FOG_DATA* FOG_DATA_PTR;		// フォグデータポインタ


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	フォグデータ保存領域を作成
//-------------------------------------
GLOBAL FOG_DATA_PTR	FogSys_Init(void);
GLOBAL void	FogSys_Delete(FOG_DATA_PTR* pFogData);

//-------------------------------------
//	今のフォグの状態を取得
//-------------------------------------
GLOBAL BOOL GetFogFlag(FOG_DATA_PTR FogData);			// ON/OFF
GLOBAL int GetFogMode(FOG_DATA_PTR FogData);			// フォグモード
GLOBAL int GetFogSlope(FOG_DATA_PTR FogData);			// かかり具合
GLOBAL int GetFogOffset(FOG_DATA_PTR FogData);			// かかり始めるデプス値
GLOBAL GXRgb GetFogColor(FOG_DATA_PTR FogData);			// フォグカラー
GLOBAL int GetFogAlpha(FOG_DATA_PTR FogData);			// フォグα値
GLOBAL const char* GetFogTbl(FOG_DATA_PTR FogData);		// フォグテーブル

//-------------------------------------
//	フォグデータを設定
//-------------------------------------
GLOBAL void SetFogData(FOG_DATA_PTR FogData, int cont, BOOL flag, int fogMode, int fogSlope, int offset);	// フォグデータ
GLOBAL void SetFogColor(FOG_DATA_PTR FogData, int cont, GXRgb color, int alpha);	// フォグカラー
GLOBAL void SetFogTbl(FOG_DATA_PTR FogData, const char* fog_tbl);		// フォグテーブル
//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

