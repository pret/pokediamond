//=============================================================================
/**
 * @file	gf_gx.c
 * @brief	NitroSDKのGXライブラリのラッパー
 * @author	GAME FREAK Inc.
 * @date	2005.11.17
 */
//=============================================================================

#ifndef	__GF_GX_H__
#define	__GF_GX_H__
#include <nitro/gx.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//初期化
extern void GF_GX_Init(void);
//描画処理リセット
extern void GF_G3X_Reset(void);
//SwapBufferリクエスト
extern void GF_G3_RequestSwapBuffers(GXSortMode am, GXBufferMode zw);
//SwapBuffer実行
extern void GF_G3_SwapBuffers(void);

#endif	//__GF_GX_H__
