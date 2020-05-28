//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		render_oam.c
 *@brief	レンダラー用グローバルOAMマネージャシステム
 *@author	tomoya takahashi
 *@data		2005.09.09
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "gflib/clact.h"

#define	__RENDER_OAM_H_GLOBAL
#include "include/system/render_oam.h"

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
//-------------------------------------
//	
//	グローバルOAMマネージャデータ
//	
//=====================================
typedef struct{
	NNSG2dOamManagerInstance MainMan;	// メインOAM
	NNSG2dOamManagerInstance SubMan;	// サブOAM
	int heap;
} REND_OAM_DATA;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static BOOL CallBackAddOamMain( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ );
static BOOL CallBackAddOamSub( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ );
static u16 CallBackAddAffineMain( const MtxFx22* mtx );
static u16 CallBackAddAffineSub( const MtxFx22* mtx );


// これは通信アイコン用を確保しません
static void	REND_OAMInit_Simple(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap);


//-----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
*/
//-----------------------------------------------------------------------------
static REND_OAM_DATA* RendOam;		//　レンダラで用のOAMデータ

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
 *
 * メイン面の0～4を通信アイコンが使用するため　
 * 何もしなくてもデフォルトで通信用に確保します
 *
 *
 */
//-----------------------------------------------------------------------------
void	REND_OAMInit(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap)
{
	int mo_start;
	int mo_num;
	int ma_start;
	int ma_num;
	
	// 必ず4～124の間の値にする
	if( mainOamStart < 4 ){
		mo_start = 4;

		if( mainOamNum > 124 ){
			mo_num	 = mainOamNum - (4 - mainOamStart);
		}else{
			mo_num = mainOamNum;
		}
	}else{
		mo_start = mainOamStart;
		mo_num	 = mainOamNum;
	}

	// 必ず1～31の間の値にする
	if( mainAffineStart < 1 ){
		ma_start = 1;

		if( mainAffineNum > 30 ){
			ma_num	 = mainAffineNum - (1 - mainAffineStart);
		}else{
			ma_num = mainAffineNum;
		}
	}else{
		ma_start = mainAffineStart;
		ma_num	 = mainAffineNum;
	}
	
	REND_OAMInit_Simple( mo_start, mo_num, ma_start, 
			ma_num,  subOamStart, subOamNum, subAffineStart, 
			subAffineNum, heap );
}

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
 */
//-----------------------------------------------------------------------------
static void	REND_OAMInit_Simple(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap)
{
	BOOL result;
	
	GF_ASSERT(RendOam == NULL);

	// グローバルデータ作成
	RendOam = sys_AllocMemory(heap, sizeof(REND_OAM_DATA));
	GF_ASSERT(RendOam);
	RendOam->heap = heap;

	// メインOAMバッファ作成
	result = NNS_G2dGetNewOamManagerInstance(
			&RendOam->MainMan,
			mainOamStart, mainOamNum,
			mainAffineStart, mainAffineNum,
			NNS_G2D_OAMTYPE_MAIN );

	GF_ASSERT( result );

	// サブOAMバッファ作成
	result = NNS_G2dGetNewOamManagerInstance(
			&RendOam->SubMan,
			subOamStart, subOamNum,
			subAffineStart, subAffineNum,
			NNS_G2D_OAMTYPE_SUB );

	GF_ASSERT( result );
}

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
void REND_OAMTrans(void)
{
	if(RendOam){
		NNS_G2dApplyAndResetOamManagerBuffer( &RendOam->MainMan );
		NNS_G2dApplyAndResetOamManagerBuffer( &RendOam->SubMan );
	}
}

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
void REND_OAM_Delete(void)
{
	GF_ASSERT(RendOam);
	
	// OAMレジスタ初期化
	REND_OAM_UtilOamRamClear_Main( RendOam->heap );	
	REND_OAM_UtilOamRamClear_Sub( RendOam->heap );	

	sys_FreeMemoryEz(RendOam);
	RendOam = NULL;
}

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
 *
 */
//-----------------------------------------------------------------------------
void REND_OAM_SetSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer)
{
	GF_ASSERT(RendOam&&("初期化されていません"));
	
	// サーフェース初期化
	if(type == NNS_G2D_SURFACETYPE_MAIN2D){
		RNDP_InitSurface(pSurface, pRect,
				CallBackAddOamMain, CallBackAddAffineMain,
				RNDP_CallBackCulling, type,
				pSetRenderer);
	}else{
		RNDP_InitSurface(pSurface, pRect,
				CallBackAddOamSub, CallBackAddAffineSub,
				RNDP_CallBackCulling, type,
				pSetRenderer);
	}
}

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
BOOL REND_OAM_Live(void)
{
	if(RendOam == NULL){
		return FALSE;
	}

	return TRUE;
}

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
NNSG2dOamManagerInstance* REND_OAM_GetOamManagerInstance( int flag )
{
	NNSG2dOamManagerInstance* p_ret;
	
	// 初期化されていません
	GF_ASSERT( RendOam );
	
	if( flag == REND_OAM_MAIN ){
		p_ret = &RendOam->MainMan;
	}else{
		p_ret = &RendOam->SubMan;
	}

	return p_ret;
}


//----------------------------------------------------------------------------
/**
 * [メイン画面用]
 *	@brief	OAMRAMのクリア
 *
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void REND_OAM_UtilOamRamClear_Main( int heap )
{
	CLACT_UtilOamRamClear_Main( heap );
}

//----------------------------------------------------------------------------
/**
 * [サブ画面用]
 *	@brief	OAMRAMのクリア
 *
 *	@param	heap	ヒープ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void REND_OAM_UtilOamRamClear_Sub( int heap )
{
	CLACT_UtilOamRamClear_Sub( heap );
}


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
	BOOL ret;
	ret = NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->MainMan, pOam, affineIndex );
	GF_ASSERT( ret );		// 登録オーバー

	return ret;
}

// サブ画面用
static BOOL CallBackAddOamSub( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ )
{
	BOOL ret;
    ret = NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->SubMan, pOam, affineIndex );
	GF_ASSERT( ret );		// 登録オーバー

	return ret;
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
	u16 ret;
    ret =  NNS_G2dEntryOamManagerAffine( &RendOam->MainMan, mtx );
	GF_ASSERT( ret != NNS_G2D_OAM_AFFINE_IDX_NONE );
	
	return ret;
}

// サブ画面用
static u16 CallBackAddAffineSub( const MtxFx22* mtx )
{
	u16 ret;
    ret = NNS_G2dEntryOamManagerAffine( &RendOam->SubMan, mtx );
	GF_ASSERT( ret != NNS_G2D_OAM_AFFINE_IDX_NONE );

	return ret;
}
