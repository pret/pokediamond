//============================================================================================
/**
 * @file	demo_trade_3d.h
 * @brief	ポケモン交換デモ（3Dオブジェクト描画）
 * @author	taya
 * @date	2006.04.13
 */
//============================================================================================
#ifndef __DEMO_TRADE_3D_H__
#define __DEMO_TRADE_3D_H__

enum {
	DT3D_ALPHA_MAX = 31,
};


typedef		struct _DT3DMAN		DT3DMAN;
typedef		struct _DT3DOBJ		DT3DOBJ;


extern DT3DMAN* DT3DMAN_Create( u32 objMax, fx32 targetX, fx32 targetY, fx32 targetZ );
extern void DT3DMAN_Delete( DT3DMAN* wk );
extern void DT3DMAN_Draw( DT3DMAN* wk );
extern DT3DOBJ* DT3D_AddObj( DT3DMAN* man, int id, u32 arcID, u32 datID, fx32 xpos, fx32 ypos, fx32 zpos, BOOL drawFlag );
extern void DT3D_DeleteObj( DT3DOBJ* obj );
extern void DT3D_GetObjPos( const DT3DOBJ* obj, VecFx32* dst );
extern void DT3D_SetObjPos( DT3DOBJ* obj, const VecFx32* pos );
extern void DT3D_GetObjRot( const DT3DOBJ* obj, VecFx16* dst );
extern void DT3D_SetObjRot( DT3DOBJ* obj, const VecFx16* rot );
extern void DT3D_SetObjDrawFlag( DT3DOBJ* obj, BOOL flag );
extern void DT3D_SetObjAlpha( DT3DOBJ* obj, int alpha );
extern void DT3D_SetObjScale( DT3DOBJ* obj, fx32 scale );
extern BOOL DT3D_CheckObjVisible( DT3DOBJ* obj );

extern void DT3D_GetCameraPos( DT3DMAN* wk, VecFx32* pos );
extern void DT3D_SetCameraPos( DT3DMAN* wk, const VecFx32* pos );
extern void DT3D_SetCameraAngleRev( DT3DMAN* wk, const CAMERA_ANGLE* angle );
extern void DT3D_GetCameraAngle( DT3DMAN* wk, CAMERA_ANGLE* angle );
extern void DT3D_AddCameraAngleRot( DT3DMAN* wk, const CAMERA_ANGLE* angle );
extern void DT3D_SetCameraDistance( DT3DMAN* wk, fx32 distance );
extern void DT3D_SetCameraView( DT3DMAN* wk, u8 view );
extern void DT3D_SetCameraParse( DT3DMAN* wk, u16 parse );


#endif
