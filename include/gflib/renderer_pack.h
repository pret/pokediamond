//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		renderer_pack.h
 *@brief	レンダラーパック関数
 *@author	tomoya takahashi
 *@data		2005.09.01
 *
 * レンダラはコールバックを使用しているため、グローバル領域が必要に
 * なってきてしまいます。
 *
 * 必要なグローバルデータはsystem/render_oamにまとめてあります。
 *　レンダラを使用するときは、system/render_oamも使用してください。
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __RENDERER_PACK_H__
#define __RENDERER_PACK_H__

#include "nnsys.h"

#undef GLOBAL
#ifdef	__RENDERER_PACK_H_GLOBAL
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
GLOBAL void RNDP_InitRenderer(NNSG2dRendererInstance* p_renderer, fx32 Zoffs);

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースを初期化
 *
 *@param	pSurface		初期化するサーフェースの実体のポインタ
 *@param	pRect			サーフェースの矩形
 *@param	OamSetFunc		OAM設定コールバック関数				作成例（　CallBackAddOamMain　が下にあります）
 *@param	AffineSetFunc	アフィン行列設定コールバック関数	作成例（　CallBackAddAffineMain　がしたにあります）
 *@param	cullFunc		カリングコールバック関数
 *@param	type			サーフェースタイプ
 *@param	pSetRenderer	このサーフェースを設定するレンダラー（設定しないときは　NULL）
 *
 *@return	none
 *
 * 
 * NNSG2dViewRect構造体
 *	typedef struct NNSG2dViewRect
	{
		NNSG2dFVec2            posTopLeft;      // 可視領域 左上位置
		NNSG2dFVec2            sizeView;        // ビューのサイズ
	}NNSG2dViewRect;
 *
 * NNSG2dFVec2構造体
	typedef struct NNSG2dFVec2
	{
		fx32     x;        
		fx32     y;
		
	}NNSG2dFVec2;
 * 
 *
 * サーフェースタイプ
	typedef enum NNSG2dSurfaceType
	{
		NNS_G2D_SURFACETYPE_MAIN3D = 0x00,  // 3D グラフィックスエンジン   を使用
		NNS_G2D_SURFACETYPE_MAIN2D = 0x01,  // 2D グラフィックスエンジン A を使用
		NNS_G2D_SURFACETYPE_SUB2D  = 0x02,  // 2D グラフィックスエンジン B を使用
		NNS_G2D_SURFACETYPE_MAX    = 0x03
		
	}NNSG2dSurfaceType;
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_InitSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dOamRegisterFunction OamSetFunc,
		NNSG2dAffineRegisterFunction AffineSetFunc,
		NNSG2dRndCellCullingFunction cullFunc,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer );

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
 * NNSG2dViewRect構造体
 *	typedef struct NNSG2dViewRect
	{
		NNSG2dFVec2            posTopLeft;      // 可視領域 左上位置
		NNSG2dFVec2            sizeView;        // ビューのサイズ
	}NNSG2dViewRect;
 *
 * NNSG2dFVec2構造体
	typedef struct NNSG2dFVec2
	{
		fx32     x;        
		fx32     y;
		
	}NNSG2dFVec2;
 * 
 * 
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceRect(NNSG2dRenderSurface* pSurface,NNSG2dViewRect* pRect);

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースにOAMの設定関数を設定
 *
 *@param	pSurface		サーフェース
 *@param	OamSetFunc		OAM設定関数			作成例（　CallBackAddOamMain　が下にあります）
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceOamSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dOamRegisterFunction OamSetFunc);

//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースにアフィン行列の設定関数を設定
 *
 *@param	pSurface		サーフェース
 *@param	AffineSetFunc		アフィン行列設定関数		作成例（　CallBackAddAffineMain　が下にあります）
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceAffineSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dAffineRegisterFunction AffineSetFunc);
	
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
GLOBAL void RNDP_SetSurfaceCullingFunc(NNSG2dRenderSurface* pSurface, NNSG2dRndCellCullingFunction CullFunc);

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
	typedef enum NNSG2dSurfaceType
	{
		NNS_G2D_SURFACETYPE_MAIN3D = 0x00,  // 3D グラフィックスエンジン   を使用
		NNS_G2D_SURFACETYPE_MAIN2D = 0x01,  // 2D グラフィックスエンジン A を使用
		NNS_G2D_SURFACETYPE_SUB2D  = 0x02,  // 2D グラフィックスエンジン B を使用
		NNS_G2D_SURFACETYPE_MAX    = 0x03
		
	}NNSG2dSurfaceType;
 *
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceType(NNSG2dRenderSurface* pSurface, NNSG2dSurfaceType type);

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
GLOBAL void RNDP_SetSurfaceRenderer(NNSG2dRenderSurface* pSurface, NNSG2dRendererInstance* pSetRenderer);


//-----------------------------------------------------------------------------
/**
 *@brief	サーフェイス内にセルがいるかをチェックし、カリングする
 *			カリングのコールバック関数は共通でOKなので作成
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
BOOL RNDP_CallBackCulling( const NNSG2dCellData* pCell, const MtxFx32* pMtx, const NNSG2dViewRect* pViewRect );


//-----------------------------------------------------------------------------
/**
*		コールバック関数作成例
*/
//-----------------------------------------------------------------------------
#if 0
//	Oam Affine 登録関数作成例
//-----------------------------------------------------------------------------
/**
 *@brief				OAMを追加するために呼ばれるコールバック関数
 *
 *@param	pOam：追加すべきOAMへのポインタ
 *@param	affineIndex：このOAMが使用するAffineインデックス
 *@param	BOOL ：倍角Affineかどうか
 *
 *@retval	成功：TRUE
 *@retval	失敗：FALSE
 *
 ----------------------------------------------------------------------------*/
// メイン画面用
static BOOL CallBackAddOamMain( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ )
{
	// OAMマネージャに引数で渡ってきたOAMデータを登録します。
	
	return NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->MainMan, pOam, affineIndex );
										//			↑メイン画面用OAMマネージャ
}

// サブ画面用
static BOOL CallBackAddOamSub( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ )
{
	// OAMマネージャに引数で渡ってきたOAMデータを登録します。
    return NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->SubMan, pOam, affineIndex );
										//			↑サブ画面用OAMマネージャ
}

//-----------------------------------------------------------------------------
/**
 *@brief	Affineパラメータを追加するために呼ばれる関数です。
 *
 *@param	mtx：追加すべきAffine変換行列へのポインタ
 *
 *@return	追加したAffineパラメータのIndex
 *
 */
 //----------------------------------------------------------------------------
// メイン画面用
static u16 CallBackAddAffineMain( const MtxFx22* mtx )
{
	// OAMマネージャに引数で渡ってきたアフィンパラメータを登録します。
    return NNS_G2dEntryOamManagerAffine( &RendOam->MainMan, mtx );
}

// サブ画面用
static u16 CallBackAddAffineSub( const MtxFx22* mtx )
{
	// OAMマネージャに引数で渡ってきたアフィンパラメータを登録します。
    return NNS_G2dEntryOamManagerAffine( &RendOam->SubMan, mtx );
}

#endif

#undef	GLOBAL
#endif		// __RENDERER_PACK_H__

