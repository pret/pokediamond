//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_light.h
 *@brief	ライトコントローラ
 *@author	tomoya takahashi
 *@data		2005.04.01
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include <nitro.h>
#include "field_glb_state.h"

#ifndef __LIGHT_CONT_H__
#define	__LIGHT_CONT_H__

#undef	GLOBAL
#ifdef	__LIGHT_CONT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
#define		DEB_MATE_ADD		(FX16_CONST( 0.10f ))

enum { 
	LIGHT_TYPE1,	// 野外
	LIGHT_TYPE2,	// 室内
	LIGHT_TYPE3,	// イアエアイベント
	LIGHT_TYPE_MAX
};


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
typedef struct _LIGHT_CONT_SET* LIGHT_CONT_PTR;		// ライトシステムのデータポインタ
typedef const struct  _LIGHT_CONT_SET* CONST_LIGHT_CONT_PTR;		// ライトシステムのデータポインタ


//-------------------------------------
//	１ライトデータテーブル
//=====================================
typedef struct{
	u32			lightEnd;	// ライト次に変更時間
	
	u8			lightFlag;		// ライト描画フラグ
	GXRgb		lightColor[4];	// ライトの色
	VecFx16		lightVec[4];	// ライトの方向
	
	GXRgb		diffuse;		// ディフューズ色	（物体の色）
    GXRgb		ambient;		// アンビエント色	（環境光）
	GXRgb		specular;		// スペキュラー色	（光が強く当たったところの色）
	GXRgb		emission;		// 放射色
}LIGHT_CONT_DATA;



// モデルデータにライト設定がされていない物があるため、ライトフラグを設定するようにする
// しかし、窓の中が光っているのをチェックするときは、上のFIELD_LIGHT_MASKをオンにする
#define		FIELD_LIGHT_MASK	(GLST_LIGHTVEC_1|GLST_LIGHTVEC_2|GLST_LIGHTCOL_1|GLST_LIGHTCOL_2|GLST_DIFF|GLST_AMB|GLST_SPEC|GLST_EMI)		// field_glb_stateで設定するデータのマスク

//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
GLOBAL LIGHT_CONT_PTR InitLightCont(GLST_DATA_PTR glb, const u8 light_index/*const char* path*/);	// ライトシステムを初期化
GLOBAL void DellLightCont(LIGHT_CONT_PTR* pLight);					// ライトシステムを破棄

GLOBAL void MainLightCont(LIGHT_CONT_PTR Light);	// ライトを動かす
GLOBAL void SetLightContReflect( LIGHT_CONT_PTR Light, BOOL reflect );	// ライトデータをフィールドに反映させるか設定 TREU反映
GLOBAL BOOL GetLightContReflect( CONST_LIGHT_CONT_PTR Light );
GLOBAL void DataSetLightCont( const LIGHT_CONT_DATA* move, GLST_DATA_PTR pGlst );	// 1ライトデータ設定

GLOBAL void SetGlbLightMdl(NNSG3dResMdl* Mdl);	// モデルにグローバルステートのライトが反映するようにする
GLOBAL void RemGlbLightMdl(NNSG3dResMdl* Mdl);	// モデルがグローバルステートのライトを反映しないようにする


//----------------------------------------------------------------------------
/**
 * ●デバック用	僕が独断と偏見で夜か昼か判断しています
 *
 *	@brief	夜かチェック
 *
 *	@param	cont	ライトコントロールシステム
 *
 *	@retval	TRUE	夜
 *	@retval	FALSE	昼
 *
 *
 */
//-----------------------------------------------------------------------------
//GLOBAL BOOL GetLightNight( LIGHT_CONT_PTR cont );
GLOBAL BOOL GetLightNight( void );

//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
#undef	GLOBAL
#endif

