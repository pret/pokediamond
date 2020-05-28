//=============================================================================
/**
 * @file	map_attr.h
 * @brief
 * @date	2005.12.15
 * @author	tamada GAME FREAK inc.
 */
//=============================================================================

#ifndef	__MAP_ATTR_H__
#define	__MAP_ATTR_H__

//=============================================================================
//=============================================================================
typedef u8 MATR;


//=============================================================================
//
//		アトリビュート判定関数
//
//
//	速度を考えてインライン関数定義されるものもある。
//=============================================================================
//--------------------------------------------------------------
//--------------------------------------------------------------
extern BOOL MATR_IsGrass(MATR matr);
extern BOOL MATR_IsLongGrass(MATR matr);
extern BOOL MATR_IsCounter(MATR matr);
extern BOOL MATR_IsDoor(MATR matr);
extern BOOL MATR_IsRightMat(MATR matr);
extern BOOL MATR_IsLeftMat(MATR matr);
extern BOOL MATR_IsUpMat(MATR matr);
extern BOOL MATR_IsDownMat(MATR matr);
extern BOOL MATR_IsRightNoArrowMat(MATR matr);
extern BOOL MATR_IsLeftNoArrowMat(MATR matr);
extern BOOL MATR_IsUpNoArrowMat(MATR matr);
extern BOOL MATR_IsDownNoArrowMat(MATR matr);
extern BOOL MATR_IsWater(MATR matr);
extern BOOL MATR_IsSand(MATR matr);
extern BOOL MATR_IsShoal(MATR matr);
extern BOOL MATR_IsJumpUp(MATR matr);
extern BOOL MATR_IsJumpDown(MATR matr);
extern BOOL MATR_IsJumpLeft(MATR matr);
extern BOOL MATR_IsJumpRight(MATR matr);
extern BOOL MATR_IsPC(MATR matr);
extern BOOL MATR_IsMap(MATR matr);
extern BOOL MATR_IsWaterHeightLv1(MATR matr);
extern BOOL MATR_IsWaterHeightLv2(MATR matr);
extern BOOL MATR_IsWaterHeightLv3(MATR matr);
extern BOOL MATR_IsWaterNoIn(MATR matr);
extern BOOL MATR_IsEscalator(MATR matr);
extern BOOL MATR_IsEscalatorNonRet(MATR matr);
extern BOOL MATR_IsRightStairs(MATR matr);
extern BOOL MATR_IsLeftStairs(MATR matr);
extern BOOL MATR_IsIce(MATR matr);
extern BOOL MATR_IsRockClimV(MATR matr);
extern BOOL MATR_IsRockClimH(MATR matr);
extern BOOL MATR_IsLittleBookRack01(MATR matr);
extern BOOL MATR_IsLittleBookRack02(MATR matr);
extern BOOL MATR_IsBookRack01(MATR matr);
extern BOOL MATR_IsBookRack02(MATR matr);
extern BOOL MATR_IsPot(MATR matr);
extern BOOL MATR_IsTrashBox(MATR matr);
extern BOOL MATR_IsShopBookRack01(MATR matr);
extern BOOL MATR_IsShopBookRack02(MATR matr);
extern BOOL MATR_IsShopBookRack03(MATR matr);
extern BOOL MATR_IsBluePrint(MATR matr);
extern BOOL MATR_IsSwamp(MATR matr);
extern BOOL MATR_IsSwampDeep(MATR matr);
extern BOOL MATR_IsSwampGrass(MATR matr);
extern BOOL MATR_IsSwampGrassDeep(MATR matr);
extern BOOL MATR_IsSnow(MATR matr);
extern BOOL MATR_IsMostShallowSnow(MATR matr);
extern BOOL MATR_IsShallowSnow(MATR matr);
extern BOOL MATR_IsSnowDeep(MATR matr);
extern BOOL MATR_IsSnowDeepMost(MATR matr);
extern BOOL MATR_IsShiftingSand(MATR matr);
extern BOOL MATR_IsShiftingSandUpper(MATR matr);
extern BOOL MATR_IsShiftingSandLower(MATR matr);
extern BOOL MATR_IsTakeOffLeft(MATR matr);
extern BOOL MATR_IsTakeOffRight(MATR matr);
extern BOOL MATR_IsDunFloor(MATR matr);
extern BOOL MATR_IsWaterFall(MATR matr);
extern BOOL MATR_IsBumpPost(MATR matr);
extern BOOL MATR_IsBadMoveUpCheck(MATR matr);
extern BOOL MATR_IsBadMoveDownCheck(MATR matr);
extern BOOL MATR_IsBadMoveLeftCheck(MATR matr);
extern BOOL MATR_IsBadMoveRightCheck(MATR matr);
extern BOOL MATR_IsPoolCheck(MATR matr);
extern BOOL MATR_IsEncount(MATR matr);
extern BOOL MATR_IsWaterEnc(MATR matr);
extern BOOL MATR_IsTV(MATR matr);
extern BOOL MATR_IsReflect(MATR matr);
extern BOOL MATR_IsForceMoveRight(MATR matr);
extern BOOL MATR_IsForceMoveLeft(MATR matr);
extern BOOL MATR_IsForceMoveUp(MATR matr);
extern BOOL MATR_IsForceMoveDown(MATR matr);
extern BOOL MATR_IsWarpPoint(MATR matr);
extern BOOL MATR_IsBridgeFlag(MATR matr);
extern BOOL MATR_IsBridge(MATR matr);
extern BOOL MATR_IsBridgeGround(MATR matr);
extern BOOL MATR_IsBridgeWater(MATR matr);
extern BOOL MATR_IsBridgeSand(MATR matr);
extern BOOL MATR_IsBridgeSnowShallow(MATR matr);
extern BOOL MATR_IsBridgeV(MATR matr);
extern BOOL MATR_IsBridgeH(MATR matr);
extern BOOL MATR_IsNotAttr(MATR matr);
#endif	//__MAP_ATTR_H__
