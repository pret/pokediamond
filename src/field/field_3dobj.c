//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_3dobj.c
 *	@brief		フィールド３Dオブジェクト簡易作成
 *	@author		tomoya takahashi
 *	@data		2006.04.25
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"


#include "include/system/arc_util.h"

#define	__FIELD_3DOBJ_H_GLOBAL
#include "field_3dobj.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// システム全体の初期化破棄タスク
#define FLD_3DOBJ_TEXTRANS_TCB_PRI	( 1024 )

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
static void FLD_3DObjMdlTransTcb( TCB_PTR tcb, void* p_work );
static void FLD_3DObjAnmDataLoad_Core( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, void* p_data, NNSFndAllocator* pallocator );


//----------------------------------------------------------------------------
/**
 *	@brief	３Dモデル読み込み
 *
 *	@param	p_mdl		モデルワーク
 *	@param	arc_idx		アーカイブID
 *	@param	data_idx	データIDX
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjMdlLoad( FLD_3DOBJ_MDL* p_mdl, u32 arc_idx, u32 data_idx, u32 heap )
{
	// モデルﾃﾞｰﾀ読み込み
	p_mdl->pResMdl = ArcUtil_Load( arc_idx, data_idx, FALSE, heap, ALLOC_TOP );

	// モデルﾃﾞｰﾀ取得
	p_mdl->pModelSet	= NNS_G3dGetMdlSet( p_mdl->pResMdl );
	p_mdl->pModel		= NNS_G3dGetMdlByIdx( p_mdl->pModelSet, 0 );
	p_mdl->pMdlTex		= NNS_G3dGetTex( p_mdl->pResMdl );
	
	if( p_mdl->pMdlTex ){
		// テクスチャデータ転送
		VWaitTCB_Add( FLD_3DObjMdlTransTcb, p_mdl, FLD_3DOBJ_TEXTRANS_TCB_PRI );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	モデル転送タスク
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_3DObjMdlTransTcb( TCB_PTR tcb, void* p_work )
{
	FLD_3DOBJ_MDL* p_mdl = p_work;

	// モデルﾃﾞｰﾀを転送
	LoadVRAMTexture( p_mdl->pMdlTex );
	BindTexture( p_mdl->pResMdl, p_mdl->pMdlTex );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	モデルワーク破棄
 *
 *	@param	p_mdl モデルワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjMdlDelete( FLD_3DOBJ_MDL* p_mdl )
{
	NNSG3dTexKey texKey;
	NNSG3dTexKey tex4x4Key;
	NNSG3dPlttKey plttKey;

	
	if( p_mdl->pMdlTex ){
		//VramKey破棄
		NNS_G3dTexReleaseTexKey( p_mdl->pMdlTex, &texKey, &tex4x4Key );
		NNS_GfdFreeTexVram( texKey );	
		NNS_GfdFreeTexVram( tex4x4Key );	

		plttKey = NNS_G3dPlttReleasePlttKey( p_mdl->pMdlTex );
		NNS_GfdFreePlttVram( plttKey );
	}
	
	// 全リソース破棄
	if(p_mdl->pResMdl){
		sys_FreeMemoryEz( p_mdl->pResMdl );
	}
	memset( p_mdl, 0, sizeof(FLD_3DOBJ_MDL) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dアニメデータ読み込み
 *
 *	@param	p_anm		アニメワーク
 *	@param	cp_mdl		モデルワーク
 *	@param	arc_idx		アーカイブファイルID
 *	@param	data_idx	データIDX
 *	@param	heap		ヒープ
 *	@param	pallocator	アロケータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjAnmLoad( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, u32 arc_idx, u32 data_idx, u32 heap, NNSFndAllocator* pallocator )
{
	void* p_data;
	// アニメﾃﾞｰﾀ読み込み
	p_data = ArcUtil_Load( arc_idx, data_idx, FALSE, heap, ALLOC_TOP );
	FLD_3DObjAnmDataLoad_Core( p_anm, cp_mdl, p_data, pallocator );
	p_anm->res_copy = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	読み込み済みデータから
 *
 *	@param	p_anm		アニメワーク
 *	@param	cp_mdl		モデルワーク
 *	@param	p_data		アニメデータバッファ
 *	@param	pallocator	アロケータ
 */
//-----------------------------------------------------------------------------
void FLD_3DObjAnmLoad_Data( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, void* p_data, NNSFndAllocator* pallocator )
{
	FLD_3DObjAnmDataLoad_Core( p_anm, cp_mdl, p_data, pallocator );
	p_anm->res_copy = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dアニメデータ破棄
 *
 *	@param	p_anm		アニメワーク
 *	@param	pallocator	アロケータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjAnmDelete( FLD_3DOBJ_ANM* p_anm, NNSFndAllocator* pallocator )
{
	if(p_anm->pResAnm){
		NNS_G3dFreeAnmObj( pallocator, p_anm->pAnmObj );
		if( p_anm->res_copy == FALSE ){
			sys_FreeMemoryEz( p_anm->pResAnm );
		}
	}
	memset( p_anm, 0, sizeof(FLD_3DOBJ_ANM) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループ再生
 *
 *	@param	p_anm	アニメオブジェクト
 *	@param	add		足す値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjAnmLoop( FLD_3DOBJ_ANM* p_anm, fx32 add )
{
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( p_anm->pAnmObj );
	
	if( add > 0 ){
		p_anm->frame = (p_anm->frame + add) % end_frame;
	}else{
		p_anm->frame = p_anm->frame + add;
		if( p_anm->frame < 0 ){
			p_anm->frame += end_frame;
		}
	}

	NNS_G3dAnmObjSetFrame( p_anm->pAnmObj, p_anm->frame );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループなし再生
 *
 *	@param	p_anm アニメワーク
 *	@param	add		足す値
 *
 *	@retval	TRUE	再生終了
 *	@retval	FALSE	再生途中
 */
//-----------------------------------------------------------------------------
BOOL FLD_3DObjAnmNoLoop( FLD_3DOBJ_ANM* p_anm, fx32 add )
{
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( p_anm->pAnmObj );
	BOOL ret = FALSE;

	if( add > 0 ){
		if( (p_anm->frame + add) < end_frame ){
			p_anm->frame += add;
		}else{
			p_anm->frame = end_frame;
			ret = TRUE;
		}
	}else{
		if( (p_anm->frame + add) >= 0 ){
			p_anm->frame += add;
		}else{
			p_anm->frame = 0;
			ret = TRUE;
		}
	}
	NNS_G3dAnmObjSetFrame( p_anm->pAnmObj, p_anm->frame );
	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	アニメ値設定
 *
 *	@param	p_anm	アニメオブジェ
 *	@param	num		設定値
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjAnmSet( FLD_3DOBJ_ANM* p_anm, fx32 num )
{
	p_anm->frame = num;
	NNS_G3dAnmObjSetFrame( p_anm->pAnmObj, num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメフレーム取得
 *
 *	@param	p_anm	アニメオブジェ
 *
 *	@return	フレーム数
 */
//-----------------------------------------------------------------------------
fx32 FLD_3DObjAnmGet( const FLD_3DOBJ_ANM* cp_anm )
{
	return cp_anm->frame;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画オブジェクト初期化
 *
 *	@param	p_draw	ワーク
 *	@param	p_mdl	モデルワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjInit( FLD_3DOBJ* p_draw, FLD_3DOBJ_MDL* p_mdl )
{
	memset( p_draw, 0, sizeof(FLD_3DOBJ) );
	NNS_G3dRenderObjInit( &p_draw->render, p_mdl->pModel );
	p_draw->draw_flg	= TRUE;
	p_draw->scale.x		= FX32_ONE;
	p_draw->scale.y		= FX32_ONE;
	p_draw->scale.z		= FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメデータをリンク
 *
 *	@param	p_draw	ワーク
 *	@param	p_anm	アニメワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjAddAnm( FLD_3DOBJ* p_draw, FLD_3DOBJ_ANM* p_anm )
{
	NNS_G3dRenderObjAddAnmObj( &p_draw->render, p_anm->pAnmObj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	モデル描画
 *
 *	@param	p_draw 描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjDraw( FLD_3DOBJ* p_draw )
{
	MtxFx33 mtx;
	MtxFx33 calc_mtx;

	if( p_draw->draw_flg ){
		// 回転行列作成
		MTX_Identity33( &mtx );
		MTX_RotX33( &calc_mtx, FX_SinIdx( p_draw->rota[FLD_3DROTA_WAY_X] ), FX_CosIdx( p_draw->rota[FLD_3DROTA_WAY_X] ) );
		MTX_Concat33( &calc_mtx, &mtx, &mtx );
		MTX_RotZ33( &calc_mtx, FX_SinIdx( p_draw->rota[FLD_3DROTA_WAY_Z] ), FX_CosIdx( p_draw->rota[FLD_3DROTA_WAY_Z] ) );
		MTX_Concat33( &calc_mtx, &mtx, &mtx );
		MTX_RotY33( &calc_mtx, FX_SinIdx( p_draw->rota[FLD_3DROTA_WAY_Y] ), FX_CosIdx( p_draw->rota[FLD_3DROTA_WAY_Y] ) );
		MTX_Concat33( &calc_mtx, &mtx, &mtx );

		simple_3DModelDraw( &p_draw->render, &p_draw->matrix, &mtx, &p_draw->scale );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ設定
 *
 *	@param	p_draw	ワーク
 *	@param	flag	フラグ
 *
 *	@return	none
 *
 *	flag
 *		TRUE	表示
 *		FALSE	非表示
 */
//-----------------------------------------------------------------------------
void FLD_3DObjSetDraw( FLD_3DOBJ* p_draw, BOOL flag )
{
	p_draw->draw_flg = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ取得
 *
 *	@param	cp_draw		ワーク
 *
 *	@retval	TRUE	表示
 *	@retval	FALSE	非表示
 */
//-----------------------------------------------------------------------------
BOOL FLD_3DObjGetDraw( const FLD_3DOBJ* cp_draw )
{
	return cp_draw->draw_flg;
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標設定
 *	
 *	@param	p_draw		ワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	z			ｚ座標
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjSetMatrix( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z )
{
	p_draw->matrix.x = x;
	p_draw->matrix.y = y;
	p_draw->matrix.z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標取得
 *
 *	@param	p_draw	ワーク
 *	@param	p_x		格納先
 *	@param	p_y		格納先
 *	@param	p_z		格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjGetMatrix( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z )
{
	*p_x = p_draw->matrix.x;
	*p_y = p_draw->matrix.y;
	*p_z = p_draw->matrix.z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡縮値設定
 *
 *	@param	p_draw	描画ワーク
 *	@param	x		ｘ拡縮値
 *	@param	y		ｙ拡縮値
 *	@param	z 		ｚ拡縮値
 *
 *	@return	noen
 */
//-----------------------------------------------------------------------------
void FLD_3DObjSetScale( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z )
{
	p_draw->scale.x = x;
	p_draw->scale.y = y;
	p_draw->scale.z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡縮値を取得
 *
 *	@param	p_draw	描画ワーク
 *	@param	p_x		ｘ座標取得先
 *	@param	p_y		ｙ座標取得先
 *	@param	p_z		ｚ座標取得先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_3DObjGetScale( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z )
{
	*p_x = p_draw->scale.x;
	*p_y = p_draw->scale.y;
	*p_z = p_draw->scale.z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転各設定
 *
 *	@param	p_draw	描画ワーク
 *	@param	rota	回転角
 *	@param	way		方向
 *
 *	@return	none
 *	way
 *		FLD_3DROTA_WAY_X		X軸回転
 *		FLD_3DROTA_WAY_Y		Y軸回転
 *		FLD_3DROTA_WAY_Z		Z軸回転
 */
//-----------------------------------------------------------------------------
void FLD_3DObjSetRota( FLD_3DOBJ* p_draw, u16 rota, u32 way )
{
	p_draw->rota[ way ] = rota;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ワーク	回転角取得
 *	
 *	@param	p_draw	描画ワーク
 *	@param	way		方向
 *
 *	@return	回転角
 *	way
 *		FLD_3DROTA_WAY_X		X軸回転
 *		FLD_3DROTA_WAY_Y		Y軸回転
 *		FLD_3DROTA_WAY_Z		Z軸回転
 */
//-----------------------------------------------------------------------------
u16 FLD_3DObjGetRota( FLD_3DOBJ* p_draw, u32 way )
{
	return p_draw->rota[ way ];
}


//----------------------------------------------------------------------------
/**
 *	@brief	アニメ読み込みCore関数
 *
 *	@param	p_anm		アニメワーク
 *	@param	cp_mdl		モデルワーク
 *	@param	p_data		アニメデータバッファ
 *	@param	pallocator	アロケータ
 */
//-----------------------------------------------------------------------------
static void FLD_3DObjAnmDataLoad_Core( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, void* p_data, NNSFndAllocator* pallocator )
{
	// アニメﾃﾞｰﾀ読み込み
	p_anm->pResAnm = p_data;

	//リソース取得
	p_anm->pOneResAnm = NNS_G3dGetAnmByIdx(p_anm->pResAnm,0);

	// アニメオブジェのメモリ確保
	p_anm->pAnmObj = NNS_G3dAllocAnmObj( 
			pallocator,
			p_anm->pOneResAnm,
			cp_mdl->pModel );

	// アニメオブジェ初期化
	NNS_G3dAnmObjInit(
		p_anm->pAnmObj,
		p_anm->pOneResAnm,
		cp_mdl->pModel,
		cp_mdl->pMdlTex );
}
