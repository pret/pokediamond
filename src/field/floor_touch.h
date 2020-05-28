//============================================================================================
/**
 * @file	floor_touch.h
 * @brief	3Dè∞ñ É^ÉbÉ`èàóù
 * @author	saito
 * @date	2006.02.21
 *
 */
//============================================================================================
#ifndef _FLOOR_TOUCH_H_
#define _FLOOR_TOUCH_H_

#include "common.h"

typedef struct TP_TO_3D_tag * TP_TO_3D_PTR;

extern TP_TO_3D_PTR FTouch_AllocUnderGroundTP(const GF_CAMERA_PTR camea_ptr);
extern void FTouch_SetUpTpTo3DParam(TP_TO_3D_PTR	outParam, const GF_CAMERA_PTR camera_ptr);
extern void FTouch_FreeUnderGroundTP(TP_TO_3D_PTR *ptr);
extern VecFx32 FTouch_CalcTpXYTo3D(const u16 inX, const u16 inY, const TP_TO_3D_PTR inParam);

#endif //_FLOOR_TOUCH_H_
