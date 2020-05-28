//============================================================================================
/**
 * @file	bounding_box.h
 * @brief	3DÉÇÉfÉãÇÃÉJÉÅÉâì‡äOîªíËèàóù
 * @author	Nozomu Saito
 * @date	2005.10.28
 */
//============================================================================================

#ifndef __BOUNDING_BOX_H__
#define	__BOUNDING_BOX_H__

#include <nitro.h>
#include <nnsys.h>

typedef struct BOUNDING_BOX_tag{
	fx16 w;
	fx16 h;
	fx16 d;
	int ScaleW;
	int ScaleH;
	int ScaleD;
}BOUNDING_BOX;

u32	BB_CullingCheck3DModel(	const NNSG3dResMdl* model_p,
							const VecFx32* trans_p,
							const MtxFx33* rot_p,
							const VecFx32* scale_p );

u32	BB_CullingCheck3DModelNonResource(	const VecFx32* trans_p,
									const fx32 inBoxW,
									const fx32 inBoxH,
									const fx32 inBoxD
									/*const MtxFx33* rot_p*/
									/*const VecFx32* scale_p*/ );

u32	BB_CullingCheck3DModelNonResQuick(	const VecFx32* trans_p,
									const BOUNDING_BOX *inBox
									/*const MtxFx33* rot_p*/
									/*const VecFx32* scale_p*/ );

void BB_MakeBoundingBox(const fx32 inBoxW, const fx32 inBoxH, const fx32 inBoxD,
						BOUNDING_BOX *outBox);
#endif	//__BOUNDING_BOX_H__
