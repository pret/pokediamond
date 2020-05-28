#ifndef _DIV_MAP_H_
#define _DIV_MAP_H_

#include "field_common.h"
#include "div_map_cont_def.h"
#include "worldmap.h"
#include "mapresource.h"
#include "field_glb_state.h"
#include "field_3d_anime.h"
#include "height_def.h"
#include "map3d_object.h"

typedef enum {
	MAP_LAOD_NONE,
	MAP_LOAD_RIGHT,
	MAP_LOAD_DOWN,
	MAP_LOAD_LEFT,
	MAP_LOAD_UP,
}MAP_LOAD_DIRECTION;

typedef enum {
	DML_LOAD_BLOCK,
	DML_LOAD_WAIT,
	DML_NONE,
	DML_FREE_WAIT,
}DML_SEQUENS;

//ブロックロード終了後のコールバック
typedef void (*DIV_LOAD_CALL_BACK)(	void *work, const int inBlockIndex, const M3DOL_PTR inObjList );

extern void DivMapBindTarget(VecFx32 const *inTarget, DMC_PTR outDivMapCont);
extern void DivMapPurgeTarget(DMC_PTR outDivMapCont);

extern DMC_PTR InitDivMap(	WORLD_MAP_PTR world,
							MAP_RESOURCE_PTR mapresource,
							FLD_3D_ANM_MNG_PTR inFld3DAnmPtr,
							const DIV_MAP_MODE inMode);
extern void LoadDivMap(	DMC_PTR outDivMapCont,
								const int x,
								const int z);
extern void DrawAroundBlock(DMC_CONST_PTR inDivMapCont,
							const GLST_DATA_PTR	glst_data);

extern void DivMapLoad_UpdateBlockData(const u8 inDirection, DMC_PTR ioDivMapCont);
extern void UpdateNowData(const int inGridX, const int inGridZ, DMC_PTR outDivMapCont);
extern BOOL CheckNextGridIO(const u8 inDirection, DMC_CONST_PTR inDivMapCont, int *outGrid);
extern void GetGridXZ(fx32 inX, fx32 inZ, int *outGridX, int *outGridZ);
/**
void GetGridXZFromGridNo(	DMC_CONST_PTR inDivMapCont,
							const int inGridNo,
							int *outGridX,
							int *outGridZ);
*/							
extern BOOL WaitMapFree(DMC_CONST_PTR inDivMapCont);
extern void DivMapLoad_FreeMap(DMC_PTR ioDivMapCont);
extern void DivMapLoadMain(	FIELDSYS_WORK *fsys, DMC_PTR ioDivMapCont);

extern void FreeDivMapCont(DMC_PTR outDivMapCont);

//extern u32 GetNowZone(DMC_CONST_PTR inDivMapCont);
//extern u32 GetZoneIDFromGrid(const int inGrid,DMC_CONST_PTR inDivMapCont);
///extern u32 GetBlockIdxFromGridXZ(const int inGridX, const int inGridZ, const int inMapBlockW);

//指定ローカルインデックスからＯＢＪリストを取得
extern void Get3DObjListFromLocalIdx(	const u8 inIdx,
										DMC_CONST_PTR inDivMapCont,
										M3DOL_PTR *outObjList);

//現在のブロックローカルインデックスを取得
extern u8 GetNowLocalIndex(DMC_CONST_PTR inDivMapCont);
//現在のブロックインデックスを取得
extern int GetNowBlockIndex(DMC_CONST_PTR inDivMapCont);
//ローカルインデックスからブロックインデックスを取得
extern int GetBlockIndexFromLocalIndex(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex);
//ブロックインデックスから地形オフセットを計算
extern u8 CalcPositionInBlockFromGridNo(const u32 inGridNo, const int inMapGridW);
extern u8 CalcLocalIdxFromBlockIdx(	const int inBlockIndex,
									const u8 inPosInBlock,
									DMC_CONST_PTR inDivMapCont);
extern BOOL CheckFourBlockIO(	DMC_CONST_PTR inDivMapCont,
								const int inX,
								const int inZ,
								u8 *outLocalIndex);

extern MHI_CONST_PTR GetDivMapHeightInfo(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex);
extern u16 const *GetDivMapAttribute(DMC_CONST_PTR inDivMapCont, const u8 inLocalIndex);

///extern void SetUpDivFuncList(FIELDSYS_WORK *fsys, const u8 inMode);

extern void DIVM_SetLoadCallBack( DMC_PTR outDivMapCont, DIV_LOAD_CALL_BACK call_back, void *work );
#ifdef PM_DEBUG
extern void SetDebugOutRangeFlg(void);
#endif

#endif //_DIV_MAP_H_
