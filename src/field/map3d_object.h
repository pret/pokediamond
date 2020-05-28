//============================================================================================
/**
 * @file	map3d_object.h
 * @bfief	マップ3Dオブジェクト（配置モデル）処理
 * @author	Nozomu Saitou
 *
 * 2005.12.18	field_encount.cからエンカウント判定部分を移動
 */
//============================================================================================

#ifndef	_MAP3D_OBJECT_H_
#define _MAP3D_OBJECT_H_

#include "mapresource_def.h"
#include "field_3d_anime.h"
#include "field_glb_state.h"
#include "system/arc_tool.h"
#define MAP_READ_OBJ_3D_MAX (32)	//1ブロック32個のＯＢＪ

typedef struct MAP3D_OBJECT_DATA_tag * M3DO_PTR;
typedef struct MAP3D_OBJECT_DATA_tag const * M3DO_CONST_PTR;
typedef struct MAP3D_OBJECT_LIST_tag * M3DOL_PTR;

extern M3DOL_PTR M3DO_AllocMap3DObjList(const u8 inHeapID);
extern void M3DO_FreeMap3DObjList(M3DOL_PTR outMap3DObjList);
extern void M3DO_CleanMap3DObjList(M3DOL_PTR outMap3DObjList);
extern void M3DO_CleanMap3DObj(const int inIndex, M3DOL_PTR outMap3DObjList);
extern VecFx32 *M3DO_GetRotateVecPtr(M3DO_PTR inMap3DObjData);
extern VecFx32 M3DO_GetGlobalVec(M3DO_CONST_PTR inMap3DObjData);
extern void M3DO_SetGlobalVec(M3DO_PTR outMap3DObjData, const VecFx32 *inVec);
extern void M3DO_SetVanish(M3DO_PTR outMap3DObjData, const BOOL inVanish);
extern int M3DO_GetObjID(M3DO_CONST_PTR inMap3DObjData);
extern NNSG3dRenderObj *M3DO_GetRenderObj(M3DO_CONST_PTR inMap3DObjData);
extern NNSG3dResMdl *M3DO_GetObjModel(M3DO_CONST_PTR inMap3DObjData);
extern M3DO_PTR M3DO_GetMap3DObjData(M3DOL_PTR inMap3DObjList, const u8 inIndex);
extern void M3DO_SetMap3DObjAnimeFlg(M3DO_PTR outMap3DObjData, BOOL inAnime);

extern void M3DO_LoadArc3DObjData(	ARCHANDLE *ioHandle,
									const int inDataSize,
									const MAP_RESOURCE_PTR inMapResource,
									M3DOL_PTR outMap3DObjList,
									FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void M3DO_DrawMap3DObj(	const VecFx32 *inOffset,
								const MAP_RESOURCE_PTR inMapResource,
								const BOOL inLightValid,
								const GLST_DATA_PTR	glst_data,
								M3DOL_PTR ioMap3DObjData);
extern M3DO_PTR M3DO_GetMap3DObjDataFromID(	M3DOL_PTR inMap3DObjList,
											const int inObjID);
extern M3DO_PTR M3DO_GetMap3DObjDataFromIndex(M3DOL_PTR inMap3DObjList,
											const int inIndex);

extern u8 M3DO_SetMap3DObjExp(	M3DOL_PTR outMap3DObjList,
								const MAP_RESOURCE_PTR inMapResource,
								const int inObjID,
								const VecFx32 *inTrans,
								const VecFx32 *inRotate,
								FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);

extern void M3DO_DrawMap3DObjExp(M3DOL_PTR inMap3DObjList, const MAP_RESOURCE_PTR inMapResource);

#endif //_MAP3D_OBJECT_H_
