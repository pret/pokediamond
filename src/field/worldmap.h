//=============================================================================
/**
 *	@brief	ワールドマップ制御ヘッダファイル
 *
 *	@param	none
 *	@retval	none
 */
//=============================================================================
#ifndef _WORLD_MAP_H_
#define _WORLD_MAP_H_

#include "worldmap_def.h"
///#include "field_3d_anime.h"
//--------------------------------------------------------------
//
// WORLD_MAPの内容を参照するためのインターフェース群
//
//--------------------------------------------------------------

extern WORLD_MAP_PTR WorldMapInit(void);
extern void WorldMapRelease(const WORLD_MAP_PTR world);


extern void SetUpWorldMatrix(const int zone_id, WORLD_MAP_PTR world);

extern u16 GetArcIndexFromBlockIndex(int index, const WORLD_MAP_PTR world);


extern int   GetWorldMapMatrixW(const WORLD_MAP_PTR world);
extern int   GetWorldMapMatrixH(const WORLD_MAP_PTR world);

extern u16 World_GetZoneIDFromMatrixXZ(const WORLD_MAP * world, int gx, int gz);
extern u16 World_GetZoneIDFromBlockIdx(const WORLD_MAP * world, const int inBlockIdx);

extern int GetZoneIDFromMatrixID(	const WORLD_MAP_PTR world,
									const int matrix_id,
									const int gx,
									const int gz,
									const int gw);
extern int GetHeightBaseFromMatrixID(const WORLD_MAP_PTR world,
									const int matrix_id,
									const int gx,
									const int gz,
									const int gw);
extern u8 GetWorldMatrixID(const WORLD_MAP_PTR world);
extern const u16 GetWorldMapArcIdx(const int Block, const WORLD_MAP_PTR world);
extern int GetZoneIDFromMatID(const int inMatID, const u16 inX, const u16 inZ);

//--------------------------------------------------------------
//	マップ書き換え特殊処理
//--------------------------------------------------------------
extern void World_Overwrite_L04(WORLD_MAP_PTR world);
extern void World_Overwrite_R224(WORLD_MAP_PTR world);

#endif	//_WORLD_MAP_H_


