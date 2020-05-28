#ifndef _MAP_TOOL_H_
#define _MAP_TOOL_H_

#include "common.h"
#include "field_common.h"
#include "map3d_object.h"
#include "map_attr.h"
typedef struct MAP_TOOL_LIST_tag * MTL_PTR;
typedef struct MAP_TOOL_LIST_tag const * MTL_CONST_PTR;

typedef struct TARGET_RECT_tag{
	fx32 X1;
	fx32 Z1;
	fx32 X2;
	fx32 Z2;
}TARGET_RECT;

typedef enum {
	MAP_TOOL_MODE_GROUND,
	MAP_TOOL_MODE_UNDER,
}MAP_TOOL_MODE;

#define HIT_RES_TOO_HEIGH	(1)
#define HIT_RES_EQUAL		(0)
#define HIT_RES_TOO_LOW		(-1)

typedef u8 HEIGHT_TYPE;
#define	HEIGHT_FAIL		(0)
#define HEIGHT_NORMAL	(1)
#define HEIGHT_EXPAND	(2)



extern void SetUpMapToolList(MTL_CONST_PTR *outMapToolList, MAP_TOOL_MODE inMapMode);
extern BOOL GetHitAttr(const FIELDSYS_WORK *fsys, const int inX, const int inZ);
///extern BOOL GetHeightPack_old(FIELDSYS_WORK *fsys, VecFx32 *ioPos);
const fx32 GetHeightPack(	const FIELDSYS_WORK *fsys,
							const fx32 inNowHeight, const fx32 inX, const fx32 inZ,
							u8 *outCode);
extern u16 GetAttribute(const FIELDSYS_WORK *fsys, const int inX, const int inZ);
extern MATR GetAttributeLSB(const FIELDSYS_WORK *fsys, const int inX, const int inZ);
extern u8 GetAttributeHSB(const FIELDSYS_WORK *fsys, const int inX, const int inZ);
extern void MPTL_GetTargetRect(	const int inGridX, const int inGridZ,
								const int inDir, TARGET_RECT *outRect );
extern void MPTL_MakeTargetRect(	const int inGridX,const int inGridZ, 
									const int inOfsX, const inOfsZ,
									const u32 inW, const u32 inH,
									TARGET_RECT *outRect );
extern BOOL MPTL_Check3DObjIO(	const M3DO_CONST_PTR inObjData,
								const TARGET_RECT *inRect,
								const VecFx32 *inTrans);
extern BOOL MPTL_CheckHitWall(	const FIELDSYS_WORK *fsys,
								const VecFx32 *inVec,
								const int inGridX,
								const int inGridZ,
								s8 *outFlg);
extern BOOL MPTL_CheckHitWallEx(FIELDSYS_WORK *fsys,
								const VecFx32 *inVec,
								const int inGridX,
								const int inGridZ,
								s8 *outFlg);
extern BOOL MPTL_CheckMap3DObjInRect(	const FIELDSYS_WORK *fsys,
										const int inTargetObjID,
										const TARGET_RECT *inRect,
										M3DO_PTR *outObjData);
extern BOOL MPTL_CheckPluralMap3DObjInRect(	const FIELDSYS_WORK *fsys,
										const int* inTargetObjIDList,
										const u8 inListNum,
										const TARGET_RECT *inRect,
										M3DO_PTR *outObjData,
										int *outOnjID);

extern BOOL MPTL_CheckMap3DObj(	const FIELDSYS_WORK *fsys,
								const int inTargetObjID,
								M3DO_PTR *outObjData,
								int *outBlockIdx);
extern BOOL MPTL_CheckPluralMap3DObj(	const FIELDSYS_WORK *fsys,
										const int* inTargetObjIDList,
										const u8 inListNum,
										M3DO_PTR *outObjData,
										int *outOnjID);
extern void MPTL_CalcMapOffset(	const int inBlockIndex,
								const int inMapW,
								VecFx32 *outTrans);

#endif //_MAP_TOOL_H_
