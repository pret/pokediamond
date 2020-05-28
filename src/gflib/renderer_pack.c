//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		renderer_pack.c
 *@brief	レンダラーパック関数
 *@author	tomoya takahashi
 *@data		2005.09.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define __RENDERER_PACK_H_GLOBAL
#include "renderer_pack.h"

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
//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------


//----------------------------------------------------------------------------
/**
 *
 *@brief	レンダラー使用準備を行います。
 *
 *@param	p_renderer	レンダラーの実体のポインタ
 *@param	Zoffs		Zオフセットの増分
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_InitRenderer(NNSG2dRendererInstance* p_renderer, fx32 Zoffs)
{
	NNS_G2dInitRenderer( p_renderer );
	// Z オフセット増分を指定
	NNS_G2dSetRendererSpriteZoffset( p_renderer, Zoffs );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースを初期化
 *
 *@param	pSurface		初期化するサーフェースの実体のポインタ
 *@param	pRect			サーフェースの矩形
 *@param	OamSetFunc		OAM設定コールバック関数
 *@param	AffineSetFunc	アフィン行列設定コールバック関数
 *@param	cullFunc		カリングコールバック関数
 *@param	type			サーフェースタイプ
 *@param	pSetRenderer	このサーフェースを設定するレンダラー（設定しないときは　NULL）
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_InitSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dOamRegisterFunction OamSetFunc,
		NNSG2dAffineRegisterFunction AffineSetFunc,
		NNSG2dRndCellCullingFunction cullFunc,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer )
{
	NNS_G2dInitRenderSurface(pSurface);
	
	// 矩形設定
	pSurface->viewRect = *pRect;

	// コールバック関数
	pSurface->pFuncOamRegister          = OamSetFunc;
	pSurface->pFuncOamAffineRegister    = AffineSetFunc;
	pSurface->pFuncVisibilityCulling    = cullFunc;

	// 表示先
	pSurface->type                      = type;
	
	// レンダラーに設定
	if(pSetRenderer){
	    NNS_G2dAddRendererTargetSurface( pSetRenderer, pSurface );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースに矩形データを設定する
 *
 *@param	pSurface		サーフェース
 *@param	pRect			設定する矩形データ	
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceRect(NNSG2dRenderSurface* pSurface, NNSG2dViewRect* pRect)
{
	pSurface->viewRect = *pRect;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースにOAMの設定関数を設定
 *
 *@param	pSurface		サーフェース
 *@param	OamSetFunc		OAM設定関数
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceOamSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dOamRegisterFunction OamSetFunc)
{
	pSurface->pFuncOamRegister          = OamSetFunc;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースにアフィン行列の設定関数を設定
 *
 *@param	pSurface		サーフェース
 *@param	AffineSetFunc		アフィン行列設定関数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceAffineSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dAffineRegisterFunction AffineSetFunc)
{
	pSurface->pFuncOamAffineRegister    = AffineSetFunc;
}
	
//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースにカリング関数を設定
 *
 *@param	pSurface		サーフェース
 *@param	CullFunc		カリング関数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceCullingFunc(NNSG2dRenderSurface* pSurface, NNSG2dRndCellCullingFunction CullFunc)
{
	pSurface->pFuncVisibilityCulling    = CullFunc;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースタイプを設定
 *
 *@param	pSurface		サーフェース
 *@param	type			サーフェースタイプ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceType(NNSG2dRenderSurface* pSurface, NNSG2dSurfaceType type)
{
	pSurface->type = type;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースをレンダラーに設定
 *
 *@param	pSurface		サーフェース
 *@param	pSetRenderer	設定するレンダラー
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceRenderer(NNSG2dRenderSurface* pSurface, NNSG2dRendererInstance* pSetRenderer)
{
	NNS_G2dAddRendererTargetSurface( pSetRenderer, pSurface );
}

//-----------------------------------------------------------------------------
/**
 *@brief	サーフェイス内にセルがいるかをチェックし、カリングする
 *			カリングは共通でOKなので作成
 *
 *@param	pCell：判定対象のセル情報へのポインタ
 *@param	pMtx：判定対象のセルに適用される座標変換行列
 *@param	pViewRect：出力先サーフェイスの表示矩形
 *
 *@retval	対象セルを表示する：TRUE
 *@retval	対象セルを表示しない：FALSE
 *
 */
 //----------------------------------------------------------------------------
BOOL RNDP_CallBackCulling( const NNSG2dCellData* pCell, const MtxFx32* pMtx, const NNSG2dViewRect* pViewRect )
{
	// コンバータにより計算された境界球半径を取得する
	const NNSG2dCellBoundingRectS16* Rect = NNS_G2dGetCellBoundingRect( pCell );
    const fx32  R = NNS_G2dGetCellBoundingSphereR( pCell );

    // セルの表示位置原点を求める
    const fx32  px = pMtx->_20 - pViewRect->posTopLeft.x;
    const fx32  py = pMtx->_21 - pViewRect->posTopLeft.y;

	// セル矩形
	fx32  minY; 
	fx32  maxY; 
	fx32  minX; 
	fx32  maxX; 
	fx32  work;


	// セルの境界球を内包する矩形を求める
	// セル定義位置を中心位置にしたとき
	if( NNS_G2dCellHasBR( pCell ) == TRUE ){
		minY = Rect->minY << FX32_SHIFT;
		maxY = Rect->maxY << FX32_SHIFT;
		minX = Rect->minX << FX32_SHIFT;
		maxX = Rect->maxX << FX32_SHIFT;
	}else{
		minY = -R << FX32_SHIFT;
		maxY = R << FX32_SHIFT;
		minX = -R << FX32_SHIFT;
		maxX = R << FX32_SHIFT;
	}
	

	
	// 座標計算で行列計算後の座標に変換
	minY = FX_Mul(minY, pMtx->_01) + FX_Mul(minY, pMtx->_11) + py;
	maxY = FX_Mul(maxY, pMtx->_01) + FX_Mul(maxY, pMtx->_11) + py;
	
	minX = FX_Mul(minX, pMtx->_00) + FX_Mul(minX, pMtx->_10) + px;
	maxX = FX_Mul(maxX, pMtx->_00) + FX_Mul(maxX, pMtx->_10) + px;

	// 座標が逆転している可能性があるのでチェック
	if( maxY < minY ){
		work = maxY;
		maxY = minY;
		minY = work;
	}

	if( maxX < minX ){
		work = maxX;
		maxX = minX;
		minX = work;
	}

    if( (maxY > 0) && (minY < pViewRect->sizeView.y) ){
        if( (maxX > 0) && (minX < pViewRect->sizeView.x) ){
			return TRUE;
        }
    }
	
	return FALSE;
}
