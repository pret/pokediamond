//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_glb_state.c
 *@brief	フィールドオブジェに影響を与えるデータ郡
 *@author	tomoya takahashi
 *@data		2005.06.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "field_glb_state.h"

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


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------


//----------------------------------------------------------------------------
/**
 *
 *@brief	ライト・マテリアルのグローバルステートデータ
 *			保存領域を作成
 *
 *@param	none
 *
 *@return	GLST_DATA*	作成して、初期化したデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLST_DATA_PTR GLST_Init(void)
{
	GLST_DATA* p_data;
	p_data = sys_AllocMemory(HEAPID_FIELD, sizeof(GLST_DATA));
	MI_CpuClear32(p_data, sizeof(GLST_DATA));

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライト・マテリアルのグローバルステートデータ
 *			保存領域を開放
 *
 *@param	pGLST_Data		保存領域のポインタを格納している変数のアドレス
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_Delete(GLST_DATA_PTR* pGLST_Data)
{
	sys_FreeMemory(HEAPID_FIELD, *pGLST_Data);
	*pGLST_Data = NULL;
}


//-----------------------------------------------------------------------------
//
//	データの反映関数郡
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	設定情報をグローバルステートに設定
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	flag		何を反映させるのか
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_Reflect(GLST_DATA_PTR GLST_Data, int flag)
{
	int i;		// ループ用
	
	// ライト
	for(i=0;i<4;i++){
		if(flag & (1<<i)){		// フラグがたっているかチェック
			NNS_G3dGlbLightVector(i,
					GLST_Data->lightVec[i].x,
					GLST_Data->lightVec[i].y,
					GLST_Data->lightVec[i].z);
		}
		if(flag & (1<<(i+4))){	// フラグがたっているかチェック
			NNS_G3dGlbLightColor(i,
					GLST_Data->Color[i]);
		}
	}
	// マテリアル
	if(flag & (GLST_DIFF | GLST_AMB)){
		NNS_G3dGlbMaterialColorDiffAmb(
				GLST_Data->Diff,
				GLST_Data->Amb,
				GLST_Data->IsSetVtxColor);
	}
	if(flag & (GLST_SPEC | GLST_EMI)){
		NNS_G3dGlbMaterialColorSpecEmi(
				GLST_Data->Spec,
				GLST_Data->Emi,
				GLST_Data->IsShininess);
	}
	// ポリゴンアトリビュート
	if(flag >= GLST_LIGHT_FLAG){
		NNS_G3dGlbPolygonAttr( GLST_Data->LightFlag,
				GLST_Data->polyMode,
				GLST_Data->cullMode,
				GLST_Data->polygonID,
				GLST_Data->alpha,
				GLST_Data->misc);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	設定情報をモデルリソースに設定
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	pMdl	モデルリソース
 *@param	flag	何を反映させるのか
 *
 * ＊ライト（０～３）の設定は行わないので注意してください。
 * 
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_ReflectMdl(GLST_DATA_PTR GLST_Data, NNSG3dResMdl* pMdl, int flag)
{
	int i;		// ループ用
	
	// マテリアル
	if(flag & GLST_DIFF){
		NNS_G3dMdlSetMdlDiffAll(pMdl, GLST_Data->Diff);
	}
	if(flag & GLST_AMB){
		NNS_G3dMdlSetMdlAmbAll(pMdl, GLST_Data->Amb);
	}
	if(flag & GLST_SPEC){
		NNS_G3dMdlSetMdlSpecAll(pMdl, GLST_Data->Spec);
	}
	if(flag & GLST_EMI){
		NNS_G3dMdlSetMdlEmiAll(pMdl, GLST_Data->Emi);
	}
	// ポリゴンアトリビュート
	if(flag & GLST_LIGHT_FLAG){
		NNS_G3dMdlSetMdlLightEnableFlagAll(pMdl, GLST_Data->LightFlag);
	}
	if(flag & GLST_POLYGON_MODE){
		NNS_G3dMdlSetMdlPolygonModeAll(pMdl, GLST_Data->polyMode);
	}
	if(flag & GLST_CULL_MODE){
		NNS_G3dMdlSetMdlCullModeAll(pMdl, GLST_Data->cullMode);
	}
	if(flag & GLST_POLYGON_ID){
		NNS_G3dMdlSetMdlPolygonIDAll(pMdl, GLST_Data->polygonID);
	}
	if(flag & GLST_ALPHA){
		NNS_G3dMdlSetMdlAlphaAll(pMdl, GLST_Data->alpha);
	}
	if(flag & GLST_FOG){
		NNS_G3dMdlSetMdlFogEnableFlagAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_FOG);
	}
	if(flag & GLST_DEPTH_TEST){
		NNS_G3dMdlSetMdlDepthTestCondAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_DEPTHTEST_DECAL);
	}
	if(flag & GLST_1DOT){
		NNS_G3dMdlSetMdl1DotAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_DISP_1DOT);
	}
	if(flag & GLST_FAR_CLIP){
		NNS_G3dMdlSetMdlFarClipAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_FAR_CLIPPING);
	}
	if(flag & GLST_XLDEPTH_UPDATE){
		NNS_G3dMdlSetMdlXLDepthUpdateAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_XLU_DEPTH_UPDATE);
	}
}

//-----------------------------------------------------------------------------
//
//	データの取得関数郡
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	GXRgbを赤緑青に分解する
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	rgb			分解するデータ
 *@param	r,g,b		色を格納するポインタ
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void GLST_GetRGB(GXRgb dat, u8* r, u8* g, u8* b)
{
	*r = (dat >> 10)&0x1f;
	*g = (dat >> 5)&0x1f;
	*b = (dat >> 0)&0x1f;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトベクトルデータ取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *@param	lightID		取得するライトID
 *
 *@return	VecFx16		ベクトルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
VecFx16 GLST_GetLightVector(GLST_DATA_PTR GLST_Data, int lightID)
{
	return GLST_Data->lightVec[lightID];
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトカラーデータ取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *@param	lightID		取得するライトID
 *
 *@return	GXRgb	色データ
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetLightColor(GLST_DATA_PTR GLST_Data, int lightID)
{
	return GLST_Data->Color[lightID];
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ディフューズ色を取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *
 *@return	GXRgb	色データ	
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialDiff(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Diff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ディフューズ色を頂点カラーに使用しているか取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *
 *@return	BOOL		使用:TRUE	不使用:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL GLST_GetMaterialDiffVtxColor(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->IsSetVtxColor;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アンビエント色を取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *
 *@return	GXRgb	色データ
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialAmb(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Amb;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スペキュラー色を取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *
 *@return	GXRgb	色データ
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialSpec(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Spec;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	鏡面反射輝度テーブルを使用するか
 *
 *@param	GLST_Data	保存領域ポインタ
 *
 *@return	BOOL		使用:TRUE	不使用:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL GLST_GetMaterialSpecShininess(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->IsShininess;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	エミッション色を取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *
 *@return	GXRgb	色データ
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialEmi(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Emi;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	どのライトを反映させるか判別するフラグを取得
 *
 *@param	GLST_Data	保存領域ポインタ
 *
 *@return	int	ライトフラグ	(１～４ビットのオン/オフでチェック)
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlLightFlag(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->LightFlag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ポリゴンモードを取得
 *
 *@param	GLST_Data		保存領域ポインタ
 *
 *@return	GXPolygonMode	ポリゴンモード
 *
 *
 */
//-----------------------------------------------------------------------------
GXPolygonMode GLST_GetMdlPolyMode(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->polyMode;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	カリングモードを取得
 *
 *@param	GLST_Data		保存領域ポインタ
 *
 *@return	GXCull			カリングモード
 *
 *
 */
//-----------------------------------------------------------------------------
GXCull GLST_GetMdlCullMode(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->cullMode;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ポリゴンIDを取得
 *
 *@param	GLST_Data		保存領域ポインタ
 *
 *@return	int				ポリゴンID
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlPolyID(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->polygonID;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	α値を取得
 *
 *@param	GLST_Data		保存領域ポインタ
 *
 *@return	int				α値
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlAlpha(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->alpha;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	その他フラグを取得
 *
 *@param	GLST_Data		保存領域ポインタ
 *
 *@return	int				misc	その他のフラグ
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlMisc(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->misc;
}
//-----------------------------------------------------------------------------
//
//	データの設定関数郡
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトベクトル設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	lightID		ライト番号	(0～3)
 *@param	x,y,z		ベクトルの値
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_LightVector(GLST_DATA_PTR GLST_Data, int lightID, fx16 x, fx16 y, fx16 z)
{
	GLST_Data->lightVec[lightID].x = x;
	GLST_Data->lightVec[lightID].y = y;
	GLST_Data->lightVec[lightID].z = z;

	// 反映
	NNS_G3dGlbLightVector(lightID,
					GLST_Data->lightVec[lightID].x,
					GLST_Data->lightVec[lightID].y,
					GLST_Data->lightVec[lightID].z);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトカラー設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	lightID		ライト番号	(0～3)
 *@param	rgb			ライトの値
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_LightColor(GLST_DATA_PTR GLST_Data, int lightID, GXRgb rgb)
{
	GLST_Data->Color[lightID] = rgb;
	
	// 反映
	NNS_G3dGlbLightColor(lightID,
			GLST_Data->Color[lightID]);
			
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ディフューズ設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	rgb				色
 *@param	IsSetVtxColor	頂点カラーとしてしようするか
 *@param	setDiffAmb		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialDiff(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsSetVtxColor, BOOL setDiffAmb)
{
	GLST_Data->Diff=rgb;
	GLST_Data->IsSetVtxColor = IsSetVtxColor;

	if(setDiffAmb == TRUE){
		GLST_Reflect(GLST_Data, GLST_DIFF);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アンビエント設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	rgb				色
 *@param	setDiffAmb		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialAmb(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setDiffAmb)
{
	GLST_Data->Amb = rgb;

	if(setDiffAmb == TRUE){
		GLST_Reflect(GLST_Data, GLST_AMB);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スペキュラー設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	rgb				色
 *@param	IsShininess		鏡面反射輝度テーブルのディセーブル/イネーブルフラグ
 *@param	setSpecEmi		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialSpec(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsShininess, BOOL setSpecEmi)
{
	GLST_Data->Spec = rgb;
	GLST_Data->IsShininess = IsShininess;

	if(setSpecEmi == TRUE){
		GLST_Reflect(GLST_Data, GLST_SPEC);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	エミッション設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	rgb				色
 *@param	setSpecEmi		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialEmi(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setSpecEmi)
{
	GLST_Data->Emi = rgb;

	if(setSpecEmi == TRUE){
		GLST_Reflect(GLST_Data, GLST_EMI);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ライトフラグ設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	light			どのライトの設定か
 *@param	on_off			ライトを点灯:TRUE	ライトを消灯:FALSE
 *@param	setPolyAttr		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlLightFlag(GLST_DATA_PTR GLST_Data, int light, BOOL on_off, BOOL setPolyAttr)
{
	if(on_off == TRUE){
		if(GLST_Data->LightFlag & light){
			return;
		}
	}else{
		if(!(GLST_Data->LightFlag & light)){
			return;
		}
	}
	
	GLST_Data->LightFlag ^= light;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_LIGHT_FLAG);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ポリゴンモード設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	polyMode		ポリゴンモード
 *@param	setPolyAttr		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlPolyMode(GLST_DATA_PTR GLST_Data, GXPolygonMode polyMode, BOOL setPolyAttr)
{
	GLST_Data->polyMode = polyMode;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_POLYGON_MODE);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	カリングモード設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	cullMode		カリングモード
 *@param	setPolyAttr		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlCullMode(GLST_DATA_PTR GLST_Data, GXCull cullMode, BOOL setPolyAttr)
{
	GLST_Data->cullMode = cullMode;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_CULL_MODE);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ポリゴンID設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	polygonID		ポリゴンID
 *@param	setPolyAttr		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlPolyID(GLST_DATA_PTR GLST_Data, int polygonID, BOOL setPolyAttr)
{
	GLST_Data->polygonID = polygonID;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_POLYGON_ID);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	アルファ設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	alpha			α値
 *@param	setPolyAttr		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlAlpha(GLST_DATA_PTR GLST_Data, int alpha, BOOL setPolyAttr)
{
	GLST_Data->alpha = alpha;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_ALPHA);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	その他のフラグ設定	
 *
 *@param	GLDT_Data	グローバルな状態
 *@param	flag			フラグの値（各フラグの論理和）
 *@param	on_off			フラグを立てるのか(TRUE)、おろすのか(FALSE)
 *@param	setPolyAttr		反映させるか	TRUE:反映させる
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlMisc(GLST_DATA_PTR GLST_Data, int flag, BOOL on_off, BOOL setPolyAttr)
{
	if(on_off == TRUE){
		if(GLST_Data->misc & flag){
			return;
		}
	}else{
		if(!(GLST_Data->misc & flag)){
			return;
		}
	}

	GLST_Data->misc ^= flag;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_LIGHT_FLAG);
	}
}
