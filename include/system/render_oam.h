//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		render_oam.h
 *@brief	レンダラー用グローバルOAMマネージャシステム
 *@author	tomoya takahashi
 *@data		2005.09.09
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __RENDER_OAM_H__
#define __RENDER_OAM_H__

#include "renderer_pack.h"

#undef GLOBAL
#ifdef	__RENDER_OAM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
enum{
	REND_OAM_MAIN,
	REND_OAM_SUB,
};

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
 *@brief	レンダラが使うOAMマネージャの作成
 *
 *@param	mainOamStart		メインOAM管理開始番号
 *@param	mainOamNum			メインOAM管理数
 *@param	mainAffineStart		メインアフィン管理開始番号
 *@param	mainAffineNum		メインアフィン管理数
 *@param	subOamStart			サブOAM管理開始番号
 *@param	subOamNum			サブOAM管理数
 *@param	subAffineStart		サブアフィン管理開始番号
 *@param	subAffineNum		サブアフィン管理数
 *@param	heap				使用ヒープ
 *
 *@return	none
 *
 * ここで作成されたOAMマネージャを皆で使用する事になります。
 *
 * メイン面の0～4を通信アイコンが使用するため　
 * 何もしなくてもデフォルトで通信用に確保します
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void	REND_OAMInit(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap);



//----------------------------------------------------------------------------
/**
 *
 *@brief	レンダラ用のグローバルOAMマネージャデータを破棄
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAM_Delete(void);


//----------------------------------------------------------------------------
/**
 *
 *@brief	サーフェースを初期化
 *
 *@param	pSurface		初期化するサーフェースの実体のポインタ
 *@param	pRect			サーフェースの矩形
 *@param	type			サーフェースタイプ
 *@param	pSetRenderer	このサーフェースを設定するレンダラー（設定しないときは　NULL）
 *
 *@return	none
 *
 * レンダラを使用するときはこの関数でサーフェースを初期化する
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAM_SetSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer);

//----------------------------------------------------------------------------
/**
 *
 *@brief	レンダラが使用するOAMマネージャのOAM転送を行います。
 *
 *@param	none
 *
 *@return	none
 *
 * 全体で１回行うだけで大丈夫です。
 * この関数を１フレームで複数回呼ぶと正常に表示されません。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAMTrans(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	レンダラ用のグローバルOAMマネージャデータが作成済みかチェック
 *
 *@param	none
 *
 *@retval	TURE		作成されている
 *@retval	FALSE		作成されていない
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL REND_OAM_Live(void);

//----------------------------------------------------------------------------
/**
 *	@brief	OAMマネージャインスタンス取得
 *
 *	@param	flag	メイン画面用かサブ画面用か
 *
 *	@return	OAMマネージャーインスタンス
 *
 * flag
	REND_OAM_MAIN,		// メイン画面
	REND_OAM_SUB,		// サブ画面
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dOamManagerInstance* REND_OAM_GetOamManagerInstance( int flag );


//-----------------------------------------------------------------------------
/**
 *		OAMマネージャを使用しないが、汎用的に使用できる関数
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAM_UtilOamRamClear_Main( int heap );
GLOBAL void REND_OAM_UtilOamRamClear_Sub( int heap );


#undef	GLOBAL
#endif		// __RENDER_OAM_H__

