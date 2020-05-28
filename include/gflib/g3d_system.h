//=============================================================================================
/**
 * @file	g3d_system.h
 * @brief	３Ｄ描画管理システムプログラム
 */
//=============================================================================================
#ifndef _G3D_SYSTEM_H_
#define _G3D_SYSTEM_H_

#undef GLOBAL
#ifdef __G3D_SYSTEM_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif


//=============================================================================================
//	型宣言
//=============================================================================================
/**
 * @brief	３Ｄシステムマネージャ構造体
 */
typedef struct GF_G3DMAN_tag
{
	int		heapID;		///<ヒープＩＤ

	void*	plt_memory;	///<パレットマネージャ用メモリ
	void*	tex_memory;	///<テクスチャマネージャ用メモリ

}GF_G3DMAN;

/**
 * @brief	マネージャモード定義	
 */
typedef enum {
	GF_G3DMAN_LNK = 0,		///<リンクドモード
	GF_G3DMAN_FRM,			///<フレームモード
}GF_G3DMAN_MODE;

/**
 * @brief	テクスチャマネージャサイズ定義	
 */
typedef enum {
	GF_G3DTEX_128K = 1,		///<128KB(1ブロック)
	GF_G3DTEX_256K = 2,		///<256KB(2ブロック)
	GF_G3DTEX_384K = 3,		///<384KB(3ブロック)
	GF_G3DTEX_512K = 4,		///<512KB(4ブロック)
}GF_G3DMAN_TEXSIZE;

/**
 * @brief	パレットマネージャサイズ定義	
 */
typedef enum {
	GF_G3DPLT_16K = 1,		///<16KB
	GF_G3DPLT_32K = 2,		///<32KB
	GF_G3DPLT_64K = 4,		///<64KB
	GF_G3DPLT_80K = 5,		///<80KB
	GF_G3DPLT_96K = 6,		///<96KB
}GF_G3DMAN_PLTSIZE;

/**
 * @brief	セットアップ関数型
 */
typedef void (*GF_G3DSETUP_FUNC)( void );

//=============================================================================================
//	設定関数
//=============================================================================================
//=============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * システムマネージャ設定
 *
 * @param	heapID			メモリ取得用ヒープエリア
 * @param	texmanMode		テクスチャマネージャ使用モード
 * @param	texmanSize		テクスチャマネージャ使用領域サイズ（byte）
 * @param	palmanMode		パレットマネージャ使用モード
 * @param	palmanSize		パレットマネージャ使用領域サイズ（byte）
 * @param	setUp			セットアップ関数(NULLの時はDefaultSetUp)
 *
 * @return	マネージャワークポインタ
 */
//--------------------------------------------------------------------------------------------
GLOBAL GF_G3DMAN*  GF_G3DMAN_Init(	u32 heapID, 
									GF_G3DMAN_MODE texmanMode, GF_G3DMAN_TEXSIZE texmanSize, 
									GF_G3DMAN_MODE pltmanMode, GF_G3DMAN_PLTSIZE pltmanSize,
									GF_G3DSETUP_FUNC setup );

//--------------------------------------------------------------------------------------------
/**
 * 終了
 *
 * @param	man		マネージャワークポインタ
 *
 * @return	none
 *
 */
//--------------------------------------------------------------------------------------------
GLOBAL void	GF_G3D_Exit( GF_G3DMAN*  man );

//------------------------------------------------------------------
//  高速３ＤＢＧ描画関数
//  
//  @param		object_p		レンダーＯＢＪ
//  @param		trans_p			トランスレート
//  @param		rot_p			ローテーション
//  @param		scale_p			スケール
//
//  @return		none
//  
//------------------------------------------------------------------
GLOBAL void GF_G3D_Draw_1mat1shape(	NNSG3dRenderObj* object_p,
									VecFx32* trans_p,
									MtxFx33* rot_p,
									VecFx32* scale_p);
#undef GLOBAL
#endif

