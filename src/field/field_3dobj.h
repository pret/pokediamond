//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_3dobj.h
 *	@brief		フィールド３Dオブジェクト簡易作成
 *	@author		tomoya takahashi
 *	@data		2006.04.25
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_3DOBJ_H__
#define __FIELD_3DOBJ_H__

#include <nnsys.h>

#undef GLOBAL
#ifdef	__FIELD_3DOBJ_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *	【使用上の注意】
 *		・nsb～に2つ以上のものをくっつけて入れることも出来ます。
 *		　しかしこのシステムでは、
 *		　その中のインデックス0番目のものをいつも適用します。
 *
 *		・圧縮に非対応です。
 */
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	回転方向定数
//=====================================
enum{
	FLD_3DROTA_WAY_X,
	FLD_3DROTA_WAY_Y,
	FLD_3DROTA_WAY_Z,
	FLD_3DROTA_WAY_NUM,
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	３Dオブジェクト
//	モデル　テクスチャ
//	種類に１つでよいものです。
//=====================================
typedef struct {
	void*					pResMdl;		// モデルﾃﾞｰﾀ
	NNSG3dResMdlSet*		pModelSet;		// モデルセット
	NNSG3dResMdl*			pModel;			// モデルリソース
	NNSG3dResTex*			pMdlTex;		// モデルに貼り付けるテクスチャ
} FLD_3DOBJ_MDL;

//-------------------------------------
//	３Dオブジェクト
//	アニメ
//	種類に１つでよいものです。
//=====================================
typedef struct {
	void*					pResAnm;		// アニメリソース
	void*					pOneResAnm;		// 1つ切り取ったリソース
	NNSG3dAnmObj*			pAnmObj;			// アニメーションオブジェ
	fx32 frame;
	BOOL res_copy;
} FLD_3DOBJ_ANM;

//-------------------------------------
//	３D描画オブジェクト
//	出したいオブジェクトの数分必要なものです。
//=====================================
typedef struct {
	NNSG3dRenderObj			render;		// レンダーオブジェクト
	VecFx32 matrix;	// 座標
	VecFx32 scale;	// 拡縮
	BOOL	draw_flg;	// 描画フラグ
	u16		rota[ FLD_3DROTA_WAY_NUM ];// 回転角X
	u16		dummy;
} FLD_3DOBJ;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
// モデル
GLOBAL void FLD_3DObjMdlLoad( FLD_3DOBJ_MDL* p_mdl, u32 arc_idx, u32 data_idx, u32 heap );
GLOBAL void FLD_3DObjMdlDelete( FLD_3DOBJ_MDL* p_mdl );

// アニメ
GLOBAL void FLD_3DObjAnmLoad( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, u32 arc_idx, u32 data_idx, u32 heap, NNSFndAllocator* pallocator );
GLOBAL void FLD_3DObjAnmLoad_Data( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, void* p_data, NNSFndAllocator* pallocator );
GLOBAL void FLD_3DObjAnmDelete( FLD_3DOBJ_ANM* p_anm, NNSFndAllocator* pallocator );
GLOBAL BOOL FLD_3DObjAnmNoLoop( FLD_3DOBJ_ANM* p_anm, fx32 add );
GLOBAL void FLD_3DObjAnmLoop( FLD_3DOBJ_ANM* p_anm, fx32 add );
GLOBAL void FLD_3DObjAnmSet( FLD_3DOBJ_ANM* p_anm, fx32 num );
GLOBAL fx32 FLD_3DObjAnmGet( const FLD_3DOBJ_ANM* cp_anm );

// 描画オブジェ
GLOBAL void FLD_3DObjInit( FLD_3DOBJ* p_draw, FLD_3DOBJ_MDL* cp_mdl );
GLOBAL void FLD_3DObjAddAnm( FLD_3DOBJ* p_draw, FLD_3DOBJ_ANM* p_anm );
GLOBAL void FLD_3DObjDraw( FLD_3DOBJ* p_draw );
GLOBAL void FLD_3DObjSetDraw( FLD_3DOBJ* p_draw, BOOL flag );
GLOBAL BOOL FLD_3DObjGetDraw( const FLD_3DOBJ* cp_draw );
GLOBAL void FLD_3DObjSetMatrix( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
GLOBAL void FLD_3DObjGetMatrix( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
GLOBAL void FLD_3DObjSetScale( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
GLOBAL void FLD_3DObjGetScale( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
GLOBAL void FLD_3DObjSetRota( FLD_3DOBJ* p_draw, u16 rota, u32 way );
GLOBAL u16 FLD_3DObjGetRota( FLD_3DOBJ* p_draw, u32 way );



#undef	GLOBAL
#endif		// __FIELD_3DOBJ_H__

