//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_glb_state.h
 *@brief	フィールドオブジェに影響を与えるデータ郡	
 *@author	tomoya takahashi
 *@data		2005.06.07
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __FIELD_GLB_STATE_H__
#define	__FIELD_GLB_STATE_H__

#include "nnsys.h"

#undef	GLOBAL
#ifdef	__FIELD_GLB_STATE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
//---------------------------
//	グローバルステートに反映フラグ
//
//	何を反映させるかのフラグ
//===========================
enum{
	GLST_LIGHTVEC_1		=1,
	GLST_LIGHTVEC_2		=1<<1,
	GLST_LIGHTVEC_3		=1<<2,
	GLST_LIGHTVEC_4		=1<<3,
	GLST_LIGHTCOL_1		=1<<4,
	GLST_LIGHTCOL_2		=1<<5,
	GLST_LIGHTCOL_3		=1<<6,
	GLST_LIGHTCOL_4		=1<<7,
	GLST_DIFF			=1<<8,
	GLST_AMB			=1<<9,
	GLST_SPEC			=1<<10,
	GLST_EMI			=1<<11,
	GLST_LIGHT_FLAG		=1<<12,
	GLST_POLYGON_MODE	=1<<13,
	GLST_CULL_MODE		=1<<14,
	GLST_POLYGON_ID		=1<<15,
	GLST_ALPHA			=1<<16,
	GLST_FOG			=1<<17,
	GLST_DEPTH_TEST		=1<<18,
	GLST_1DOT			=1<<19,
	GLST_FAR_CLIP		=1<<20,
	GLST_XLDEPTH_UPDATE	=1<<21,
	GLST_ALL			=1<<22
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
typedef struct _GLST_DATA*	GLST_DATA_PTR;		// ライト・マテリアルのグローバル状態保存構造体ポインタ


// 他アプリケーションでこの構造体を使用したくなったので、外部公開
// GLST_DATA_PTRは、今から変えるのは大変なので、そのままにします。
//-------------------------------------
//	ライト・マテリアル
//	グローバル状態保存構造体
//=====================================
typedef struct _GLST_DATA{
	// ライト
	VecFx16	lightVec[4];	// ベクトル
	GXRgb	Color[4];		// 色
	
	// マテリアルカラー
	GXRgb	Diff;		// ディフューズ色	(0:赤 1:緑 2:青	各0～31)
	GXRgb	Amb;		// アンビエント色
	GXRgb	Spec;		// スペキュラー色
	GXRgb	Emi;		// エミッション色
	BOOL IsSetVtxColor;	// ディフューズ色を頂点カラーに使用するか
	BOOL IsShininess;	// 鏡面反射輝度テーブルを使用するか

	// ポリゴンアトリビュート
	int				LightFlag;			// ライトフラグ
	GXPolygonMode	polyMode;			// ポリゴンモード
	GXCull			cullMode;			// カリングモード
	int				polygonID;			// ポリゴンID
	int				alpha;				// アルファ
	int				misc;				// その他のフラグ
} GLST_DATA;



//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	保存領域の作成/破棄
//-------------------------------------
GLOBAL GLST_DATA_PTR GLST_Init(void);
GLOBAL void GLST_Delete(GLST_DATA_PTR* pGLST_Data);

//-------------------------------------
//	設定データを反映
//-------------------------------------
GLOBAL void GLST_Reflect(GLST_DATA_PTR GLST_Data, int flag);								// グローバルステートに反映させる
GLOBAL void GLST_ReflectMdl(GLST_DATA_PTR GLST_Data, NNSG3dResMdl* pMdl, int flag);			// モデルリソースに反映させる

//-------------------------------------
//	設定データ取得
//-------------------------------------
GLOBAL void GLST_GetRGB(GXRgb dat, u8* r, u8* g, u8* b);			// GXRgbの色を赤緑青に分解
//-- ライト --//
GLOBAL VecFx16 GLST_GetLightVector(GLST_DATA_PTR GLST_Data, int lightID);	// ライトベクトル
GLOBAL GXRgb GLST_GetLightColor(GLST_DATA_PTR GLST_Data, int lightID);		// ライトカラー

//-- マテリアル --//
GLOBAL GXRgb GLST_GetMaterialDiff(GLST_DATA_PTR GLST_Data);					// ディフューズ
GLOBAL BOOL GLST_GetMaterialDiffVtxColor(GLST_DATA_PTR GLST_Data);			// ディフューズ色を頂点カラーに使用するか
GLOBAL GXRgb GLST_GetMaterialAmb(GLST_DATA_PTR GLST_Data);					// アンビエント
GLOBAL GXRgb GLST_GetMaterialSpec(GLST_DATA_PTR GLST_Data);					// スペキュラー
GLOBAL BOOL GLST_GetMaterialSpecShininess(GLST_DATA_PTR GLST_Data);			// 鏡面反射輝度テーブルを使用するか
GLOBAL GXRgb GLST_GetMaterialEmi(GLST_DATA_PTR GLST_Data);					// エミッション

//-- モデルアトリビュート --//
GLOBAL int GLST_GetMdlLightFlag(GLST_DATA_PTR GLST_Data);			// ライトフラグ
GLOBAL GXPolygonMode GLST_GetMdlPolyMode(GLST_DATA_PTR GLST_Data);	// ポリゴンモード
GLOBAL GXCull GLST_GetMdlCullMode(GLST_DATA_PTR GLST_Data);			// カリングモード
GLOBAL int GLST_GetMdlPolyID(GLST_DATA_PTR GLST_Data);				// ポリゴンID
GLOBAL int GLST_GetMdlAlpha(GLST_DATA_PTR GLST_Data);				// α値
GLOBAL int GLST_GetMdlMisc(GLST_DATA_PTR GLST_Data);				// その他のフラグ


//-------------------------------------
// 値を設定
//-------------------------------------
//-- ライト --//
GLOBAL void GLST_LightVector(GLST_DATA_PTR GLST_Data, int lightID, fx16 x, fx16 y, fx16 z);	// ライトベクトルセット
GLOBAL void GLST_LightColor(GLST_DATA_PTR GLST_Data, int lightID, GXRgb rgb);				// ライトカラーセット

//-- マテリアル --//
GLOBAL void GLST_MaterialDiff(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsSetVtxColor, BOOL setDiffAmb);	// ディフューズ
GLOBAL void GLST_MaterialAmb(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setDiffAmb);						// アンビエント

GLOBAL void GLST_MaterialSpec(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsShininess, BOOL setSpecEmi);	// スペキュラー
GLOBAL void GLST_MaterialEmi(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setSpecEmi);						// エミッション

//-- モデルアトリビュート --//
GLOBAL void GLST_MdlLightFlag(GLST_DATA_PTR GLST_Data, int light, BOOL on_off, BOOL setPolyAttr);	// ライトフラグ
GLOBAL void GLST_MdlPolyMode(GLST_DATA_PTR GLST_Data, GXPolygonMode polyMode, BOOL setPolyAttr);	// ポリゴンモード
GLOBAL void GLST_MdlCullMode(GLST_DATA_PTR GLST_Data, GXCull cullMode, BOOL setPolyAttr);			// カリングモード
GLOBAL void GLST_MdlPolyID(GLST_DATA_PTR GLST_Data, int polygonID, BOOL setPolyAttr);				// ポリゴンID
GLOBAL void GLST_MdlAlpha(GLST_DATA_PTR GLST_Data, int alpha, BOOL setPolyAttr);					// α値
GLOBAL void GLST_MdlMisc(GLST_DATA_PTR GLST_Data, int flag, BOOL on_off, BOOL setPolyAttr);			// その他のフラグ

//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

