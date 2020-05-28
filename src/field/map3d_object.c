//============================================================================================
/**
 * @file	map3d_object.c
 * @bfief	マップ3Dオブジェクト（配置モデル）処理
 * @author	Nozomu Saitou
 *
 * 2005.12.18	field_encount.cからエンカウント判定部分を移動
 */
//============================================================================================

//#define DEBUG_EXP_DISP

#include "common.h"
#include "map3d_object.h"
#include "mapresource.h"
#include "mat_shp.h"
#include "field_light.h"

#ifdef DEBUG_EXP_DISP

static u8 DebugExpAddCnt = 0;
static u8 DebugExpDrawCnt = 0;

#endif

static void SetMap3DModel(	const int inID,
							const MAP_RESOURCE_PTR inMapResource,
							NNSG3dRenderObj* object_p,
							NNSG3dResMdl** model);
static void DrawModelQuick(	const NNSG3dResMdl* pResMdl,
							VecFx32* trans_p,
							MtxFx33* rot_p,
							VecFx32* scale_p,
							MSD_CONST_PTR inMatShpData,
							const int inObjID);

typedef	struct	{
	int	id;			//データＩＤ

	VecFx32  global;	//グローバル座標
	VecFx32  rotate;	//回転
	VecFx32  scale;		//スケール

	int		dummy[2];	//
}MAP3D_OBJECT_HEADER;

typedef	struct	MAP3D_OBJECT_DATA_tag{
	int	id;			//データＩＤ
	BOOL	valid;	//データの有効性
	BOOL	Vanish;	//バニッシュフラグ
	BOOL	RotateFlg;	//回転するかフラグ
	NNSG3dRenderObj	objectdata;
///	NNSG3dAnmObj*   objectanime;				//モデルアニメデータポインタ
	NNSG3dResMdl* 	objectmodel;				//モデリングデータポインタ

	VecFx32  global;	//グローバル座標
	VecFx32  rotate;	//回転
	VecFx32  scale;		//スケール
///	NNSG3dResTex*	p_defaultTex;	20060117del
}MAP3D_OBJECT_DATA;

typedef	struct	MAP3D_OBJECT_LIST_tag{
	MAP3D_OBJECT_DATA Map3DObjectData[MAP_READ_OBJ_3D_MAX];
}MAP3D_OBJECT_LIST;


//==============================================================================
/**
 * 3DOBJ初期化
 *
 * @param	inNum		作成個数
 * @param	inHeapID	ヒープID
 *
 * @return	M3DO_PTR	確保された3DOBJの先頭ポインタ
 */
//==============================================================================
M3DOL_PTR M3DO_AllocMap3DObjList(const u8 inHeapID)
{
	M3DOL_PTR obj_list_ptr;
	obj_list_ptr = sys_AllocMemory(inHeapID, sizeof(MAP3D_OBJECT_LIST));
	M3DO_CleanMap3DObjList(obj_list_ptr);
	return obj_list_ptr;
}

//==============================================================================
/**
 * 3DOBJ解放
 *
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 *
 * @return	none
 */
//==============================================================================
void M3DO_FreeMap3DObjList(M3DOL_PTR outMap3DObjList)
{
	sys_FreeMemoryEz(outMap3DObjList);
	outMap3DObjList = NULL;
}

//==============================================================================
/**
 * 3DOBJクリーン
 *
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 *
 * @return	none
 */
//==============================================================================
void M3DO_CleanMap3DObjList(M3DOL_PTR outMap3DObjList)
{
	u8 i;
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		VecFx32 init_data = {0,0,0};
		outMap3DObjList->Map3DObjectData[i].id			= 0;// =OFF
		outMap3DObjList->Map3DObjectData[i].valid		= FALSE;// データ無効
		outMap3DObjList->Map3DObjectData[i].Vanish		= FALSE;
		outMap3DObjList->Map3DObjectData[i].RotateFlg	= FALSE;
		outMap3DObjList->Map3DObjectData[i].global		= init_data;
		outMap3DObjList->Map3DObjectData[i].rotate		= init_data;
		outMap3DObjList->Map3DObjectData[i].scale		= init_data;
		outMap3DObjList->Map3DObjectData[i].objectmodel	= NULL;
	}
}

//==============================================================================
/**
 * 指定インデックスの3DOBJクリーン
 *
 * @param	inIndex				登録インデックス
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 *
 * @return	none
 */
//==============================================================================
void M3DO_CleanMap3DObj(const int inIndex, M3DOL_PTR outMap3DObjList)
{
	GF_ASSERT(inIndex<MAP_READ_OBJ_3D_MAX&&"インデックスオーバー");
	{
		VecFx32 init_data = {0,0,0};
		outMap3DObjList->Map3DObjectData[inIndex].id		= 0;// =OFF
		outMap3DObjList->Map3DObjectData[inIndex].valid		= FALSE;// データ無効
		outMap3DObjList->Map3DObjectData[inIndex].Vanish	= FALSE;
		outMap3DObjList->Map3DObjectData[inIndex].RotateFlg	= FALSE;
		outMap3DObjList->Map3DObjectData[inIndex].global	= init_data;
		outMap3DObjList->Map3DObjectData[inIndex].rotate	= init_data;
		outMap3DObjList->Map3DObjectData[inIndex].scale		= init_data;
		outMap3DObjList->Map3DObjectData[inIndex].objectmodel		= NULL;
	}
#ifdef DEBUG_EXP_DISP
	GF_ASSERT(DebugExpAddCnt!=0);
	DebugExpAddCnt--;
#endif
}


//==============================================================================
/**
 * 3DOBJロード
 *
 * @param	inMapResource		マップリソースポインタ
 * @param	inFileName			ファイル名
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 * @param	field_3d_anime_ptr	3Dアニメポインタ
 *
 * @return	none
 */
//==============================================================================
void M3DO_LoadArc3DObjData(	ARCHANDLE *ioHandle,
							const int inDataSize,
							const MAP_RESOURCE_PTR inMapResource,
							M3DOL_PTR outMap3DObjList,
							FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	MAP3D_OBJECT_HEADER * obj_dat = NULL;
	u32	obj_max;
	int i;
	//アーカイブデータ読み込み
	if (inDataSize != 0){
		obj_dat = sys_AllocMemoryLo(HEAPID_FIELD, inDataSize);
		ArchiveDataLoadByHandleContinue( ioHandle, inDataSize, obj_dat );
		obj_max = inDataSize / sizeof(MAP3D_OBJECT_HEADER);
	}else{
		obj_max = 0;
	}
#ifdef DEBUG_ONLY_FOR_saitou
		OS_Printf("local_print obj_max = %d\n",obj_max);
#endif
#ifdef PM_DEBUG
	if (obj_max>MAP_READ_OBJ_3D_MAX){
		OS_Printf("ERROR:OBJ_MAX_OVER obj_num = %d\n",obj_max);
		OS_Printf("%d,%d\n",inDataSize,sizeof(MAP3D_OBJECT_HEADER));
		GF_ASSERT(0);
	}
#endif

	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(outMap3DObjList->Map3DObjectData[i]);
		if(i < obj_max){
			ptr->id		    = obj_dat[i].id;		//ＩＤ
			ptr->valid		= TRUE;					//データ有効
			ptr->RotateFlg  = FALSE;				//回転無効
			ptr->global	    = obj_dat[i].global;	//座標
			ptr->rotate	    = obj_dat[i].rotate;	//回転
			ptr->scale	    = obj_dat[i].scale;		//スケール
#ifdef DEBUG_ONLY_FOR_saitou
		///OS_Printf("local_print obj_id = %d\n",obj_dat[i].id);
#endif
			// 読み込んだテクスチャリソースをセット
			SetMap3DModel(
					ptr->id,
					inMapResource,
					&(ptr->objectdata),
					&(ptr->objectmodel) );
			if (CheckResourceEntry(inMapResource, ptr->id) == FALSE){
				OS_Printf("ダミー表示のため、配置モデルIDを書き換えます%d→0\n",ptr->id);
				ptr->id = 0;
			}
			
#ifdef FOG_MDL_SET_CHECK
			NNS_G3dMdlSetMdlFogEnableFlagAll(ptr->objectmodel, TRUE);
#endif
			{
/**				
				F3DA_SetFld3DAnime(	ptr->id, 0, FALSE,
									&(ptr->objectdata),
									field_3d_anime_ptr);
*/									
				F3DA_SetFld3DAnimeEasy(	ptr->id,
										&(ptr->objectdata),
										field_3d_anime_ptr);
			}
		}else{
			VecFx32 init_data = {0,0,0};

			ptr->id		    = 0;		// =OFF
			ptr->valid		= FALSE;	//データ無効
			ptr->RotateFlg	= FALSE;
			ptr->global     = init_data;
			ptr->rotate     = init_data;
			ptr->scale	    = init_data;
		}
	}
	if( obj_dat != NULL ){
		sys_FreeMemoryEz( obj_dat );
	}

}

//==============================================================================
/**
 * 3DOBJ描画
 *
 * @param	inOffset			描画オフセット
 * @param	inMapResource		マップリソース
 * @param	inLightValid		ライト有無
 * @param	glst_data			グローバルステート
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 *
 * @return	none
 */
//==============================================================================
void M3DO_DrawMap3DObj(	const VecFx32 *inOffset,
						const MAP_RESOURCE_PTR inMapResource,
						const BOOL inLightValid,
						const GLST_DATA_PTR	glst_data,
						M3DOL_PTR ioMap3DObjList)
{
	//オブジェクト３Ｄ描画
	
	int	i;
	VecFx32 obj_trans;
	MtxFx33 rot={FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(ioMap3DObjList->Map3DObjectData[i]);
		if( ptr->valid != FALSE ){
			if (ptr->Vanish){	//バニッシュチェック
				continue;
			}
			//
			// カリングチェック
			// 
			// モデルのボックステストデータセット

			//↓回転行列の計算はしないことにする（回転はサポートしない）
			///VecFx32_to_MtxFx33( &rot, &(inDivMapCont->BlockNodeList[inLocalIndex]->ObjData[i].rotate));
			obj_trans = ptr->global;
			obj_trans.x += inOffset->x;
			obj_trans.z += inOffset->z;
			//カリングチェック
			if (BB_CullingCheck3DModel(	ptr->objectmodel,
										&(obj_trans),
										&rot,
										&(ptr->scale) ) ) 
			{
				MSD_CONST_PTR mat_shp_data;
				u16 num;
				mat_shp_data = GetMatShpDataPtr(inMapResource);
					
				if (inLightValid == TRUE){
					//マテリアル変更
					GLST_ReflectMdl(glst_data,
									ptr->objectmodel,
									FIELD_LIGHT_MASK);
				}
				GetMatShpNum(	ptr->id,
								mat_shp_data,
								&num);
				if ( num == 0 ){
					simple_3DModelDraw( &(ptr->objectdata),
								    	&(obj_trans),
										&rot,
										&(ptr->scale));
				}else{
					DrawModelQuick( ptr->objectmodel,
									&obj_trans,
									&rot,
									&(ptr->scale),
									mat_shp_data,
									ptr->id);
				}
			}
		}
	}
}

//==============================================================================
/**
 * 取得関数　回転ベクトルへのポインタ
 *
 * @param	inMap3DObjData		3DOBJへのポインタ
 *
 * @return	VecFx32				回転ベクトルへのポインタ
 */
//==============================================================================
VecFx32 *M3DO_GetRotateVecPtr(M3DO_PTR inMap3DObjData)
{
	return (&inMap3DObjData->rotate);
}

//==============================================================================
/**
 * 取得関数　グローバル座標
 *
 * @param	inMap3DObjData		3DOBJへのポインタ
 *
 * @return	VecFx32				グローバル座標
 */
//==============================================================================
VecFx32 M3DO_GetGlobalVec(M3DO_CONST_PTR inMap3DObjData)
{
	return inMap3DObjData->global;
}
//==============================================================================
/**
 * セット関数　グローバル座標
 *
 * @param	outMap3DObjData		3DOBJへのポインタ
 * @param	inVec				グローバル座標
 *
 * @return	none
 */
//==============================================================================
void M3DO_SetGlobalVec(M3DO_PTR outMap3DObjData, const VecFx32 *inVec)
{
	outMap3DObjData->global = (*inVec);
}

//==============================================================================
/**
 * セット関数　バニッシュフラグセット
 *
 * @param	outMap3DObjData		3DOBJへのポインタ
 * @param	inVanish				バニッシュフラグ
 *
 * @return	none
 */
//==============================================================================
void M3DO_SetVanish(M3DO_PTR outMap3DObjData, const BOOL inVanish)
{
	outMap3DObjData->Vanish = inVanish;
}

//==============================================================================
/**
 * 取得関数　ID
 *
 * @param	inMap3DObjData		3DOBJへのポインタ
 *
 * @return	int					ID
 */
//==============================================================================
int M3DO_GetObjID(M3DO_CONST_PTR inMap3DObjData)
{
	return inMap3DObjData->id;
}

//==============================================================================
/**
 * 取得関数　レンダーOBJデータへのポインタ
 *
 * @param	inMap3DObjData		3DOBJへのポインタ
 *
 * @return	NNSG3dRenderObj*	レンダーOBJデータへのポインタ
 */
//==============================================================================
NNSG3dRenderObj *M3DO_GetRenderObj(M3DO_CONST_PTR inMap3DObjData)
{
	return (NNSG3dRenderObj *)(&(inMap3DObjData->objectdata));
}

//==============================================================================
/**
 * 取得関数　モデリングデータへのポインタ
 *
 * @param	inMap3DObjData		3DOBJへのポインタ
 *
 * @return	NNSG3dResMdl*		モデリングデータへのポインタ
 */
//==============================================================================
NNSG3dResMdl *M3DO_GetObjModel(M3DO_CONST_PTR inMap3DObjData)
{
	return inMap3DObjData->objectmodel;
}

//==============================================================================
/**
 * インデックスで指定したマップ3DOBJのポインタを返す
 *
 * @param	inMap3DObjList		3DOBJの先頭のポインタ
 * @param	inIndex				インデックス
 *
 * @return	NNSG3dResMdl*		モデリングデータへのポインタ
 */
//==============================================================================
M3DO_PTR M3DO_GetMap3DObjData(M3DOL_PTR inMap3DObjList, const u8 inIndex)
{
	return &inMap3DObjList->Map3DObjectData[inIndex];
}

//==============================================================================
/**
 * 指定したOBJIDをもつ3DOBJを返す関数（始めにヒットした1つのみ返す）
 *
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 * @param	inObjID				OBJID
 *
 * @return	M3DO_PTR			オブジェクトポインタ
 */
//==============================================================================
M3DO_PTR M3DO_GetMap3DObjDataFromID(M3DOL_PTR inMap3DObjList, const int inObjID)
{
	M3DO_PTR ptr;
	int i;
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		ptr = &inMap3DObjList->Map3DObjectData[i];
		if (ptr->id == inObjID){
			return ptr;
		}
	}
	return NULL;
}

//==============================================================================
/**
 * 指定した登録インデックスのDOBJを返す関数
 *
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 * @param	inIndex				登録インデックス
 *
 * @return	M3DO_PTR			オブジェクトポインタ
 */
//==============================================================================
M3DO_PTR M3DO_GetMap3DObjDataFromIndex(M3DOL_PTR inMap3DObjList, const int inIndex)
{
	M3DO_PTR ptr;
	GF_ASSERT(inIndex<MAP_READ_OBJ_3D_MAX&&"インデックスオーバーです");
	
	ptr = &inMap3DObjList->Map3DObjectData[inIndex];
	
	GF_ASSERT(ptr->valid&&"データは無効です");

	return ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * モデルセット
 *
 * @param	inID			モデルＩＤ
 * @param	inMapResource	マップリソースポインタ
 * @param	* object_p		モデルオブジェクトポインタ
 * @param	** model		モデルデータへのポインタのポインタ
 * @param	** pp_res_tex	テクスチャリソースへのポインタのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetMap3DModel(	const int inID,
							const MAP_RESOURCE_PTR inMapResource,
							NNSG3dRenderObj* object_p,
							NNSG3dResMdl** model)
{
	///simple_3DModelSetResFileAlready(object_p,model,GetMapResourceModelRes(inID,inMapResource));
	NNSG3dResFileHeader** resFile = GetMapResourceModelRes(inID,inMapResource);
	*model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
	NNS_G3dRenderObjInit(object_p, *model);
}

//==============================================================================
/**
 * 3DOBJ高速描画
 *
 * @param	pResMdl			リソース
 * @param	trans_p			移動座標
 * @param	rot_p			回転マトリクス
 * @param	scale_p			拡縮マトリクス
 * @param	inMatShpData	マットシェイプデータ
 * @param	inObjID			OBJID
 *
 * @return	none
 */
//==============================================================================
static void DrawModelQuick(	const NNSG3dResMdl* pResMdl,
							VecFx32* trans_p,
							MtxFx33* rot_p,
							VecFx32* scale_p,
							MSD_CONST_PTR inMatShpData,
							const int inObjID)
{
	u8 i;
	u16 num;
	u16 idx;
	u8 mat_id;
	BOOL send_flg;
	MAT_SHP const *mat_shp;
	//↓カリングチェック後にすぐに描画するならば、すでにセット済みなので不要

	// 位置設定
	NNS_G3dGlbSetBaseTrans(trans_p);	
	// 角度設定
	NNS_G3dGlbSetBaseRot(rot_p);
	// スケール設定
	NNS_G3dGlbSetBaseScale(scale_p);
	
	NNS_G3dGlbFlush();	//マトリクス反映

	GetMatShpNumAndIdx(	inObjID,
						inMatShpData,
						&num,
						&idx);
	mat_shp = GetMatShp(idx, inMatShpData);
	mat_id = 0xff;
	send_flg = TRUE;
	for(i=0;i<num;i++){
		if (mat_id != mat_shp[i].matID){
			mat_id = mat_shp[i].matID;
			send_flg = TRUE;
		}else{
			send_flg = FALSE;
		}
		NNS_G3dDraw1Mat1Shp(pResMdl,
							mat_id,//matID,
							mat_shp[i].shpID,//shpID,
							send_flg//sendMat
							);
		
	}
	//↓ジオメトリコマンドバッファが設定されていないので、不要
	//NNS_G3dGeFlushBuffer();
}

//==============================================================================
/**
 * 拡張マップ3DOBJのセット
 *
 * @param	outMap3DObjList		3DOBJリストへのポインタ
 * @param	inMapResource		マップリソースポインタ
 * @param	inObjID				OBJID
 * @param	inTrans				位置座標
 * @param	inRotate			回転
 * @param	field_3d_anime_ptr	アニメポインタ
 *
 * @return	u8				登録インデックス
 */
//==============================================================================
u8 M3DO_SetMap3DObjExp(	M3DOL_PTR outMap3DObjList,
						const MAP_RESOURCE_PTR inMapResource,
						const int inObjID,
						const VecFx32 *inTrans,
						const VecFx32 *inRotate,
						FLD_3D_ANM_MNG_PTR field_3d_anime_ptr)
{
	u8 i;
	VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};

	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(outMap3DObjList->Map3DObjectData[i]);
		if (ptr->valid == FALSE){
			ptr->valid = TRUE;	//データの有効性
			ptr->global = (*inTrans);	//グローバル座標
			//回転
			if (inRotate != NULL){
				ptr->RotateFlg = TRUE;
				ptr->rotate = (*inRotate);
			}else{
				ptr->RotateFlg = FALSE;
			}
			ptr->scale = scale;		//スケール
			ptr->id = inObjID;
			SetMap3DModel(
					ptr->id,
					inMapResource,
					&(ptr->objectdata),
					&(ptr->objectmodel) );
			//アニメセット
			F3DA_SetFld3DAnime(	ptr->id, 0, FALSE,
								&(ptr->objectdata),
								field_3d_anime_ptr);
#ifdef DEBUG_EXP_DISP
			DebugExpAddCnt++;
#endif
			return i;
		}
	}
	
	GF_ASSERT(0&&"登録失敗");
	return MAP_READ_OBJ_3D_MAX;
}

//==============================================================================
/**
 * 拡張マップ3DOBJの描画
 *
 * @param	inMap3DObjList	3DOBJリストへのポインタ
 * @param	inMapResource	マップリソースポインタ
 *
 * @return	none
 */
//==============================================================================
void M3DO_DrawMap3DObjExp(M3DOL_PTR inMap3DObjList, const MAP_RESOURCE_PTR inMapResource)
{
	u8 i;
	MtxFx33 rot={FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};

#ifdef DEBUG_EXP_DISP
	DebugExpDrawCnt = 0;
#endif
	
	for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
		M3DO_PTR ptr;
		ptr = &(inMap3DObjList->Map3DObjectData[i]);
		if ( ptr->valid ){
			if (ptr->Vanish){	//バニッシュチェック
				continue;
			}
			{
				MSD_CONST_PTR mat_shp_data;
				u16 num;
				mat_shp_data = GetMatShpDataPtr(inMapResource);
					
				GetMatShpNum(	ptr->id,
								mat_shp_data,
								&num);
				if (ptr->RotateFlg){
						VecFx32_to_MtxFx33( &rot, &ptr->rotate);
					}
				if ( num == 0 ){	
					simple_3DModelDraw( &(ptr->objectdata),
								    	&(ptr->global),
										&rot,
										&(ptr->scale) );
				}else{
					DrawModelQuick( ptr->objectmodel,
									&ptr->global,
									&rot,
									&(ptr->scale),
									mat_shp_data,
									ptr->id);
				}
#ifdef DEBUG_EXP_DISP				
				DebugExpDrawCnt++;
#endif				
			}
		}
	}

#ifdef DEBUG_EXP_DISP
	if (sys.trg & PAD_BUTTON_L){
		OS_Printf("add_draw:%d,%d\n",DebugExpAddCnt,DebugExpDrawCnt);
	}
#endif
}
