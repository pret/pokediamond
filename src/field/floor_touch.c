//============================================================================================
/**
 * @file	floor_touch.c
 * @brief	3D床面タッチ処理
 * @author	saito
 * @date	2006.02.21
 *
 */
//============================================================================================
#include "floor_touch.h"

#define		W_HALF_SIZE	(128)
#define		H_HALF_SIZE	(96)

//static GRID_POINT MakeGridPointFromVecFx32(const VecFx32 inPoint );

typedef struct TP_TO_3D_tag
{
//	u16 AngleX	//X軸カメラアングル
	u16 HView;	// 垂直視野角/2
	u16 WView;	// 水平視野角/2
	VecFx32	CamPos;	// カメラ位置ベクトル
	VecFx32 Norm;	//平面の法線ベクトル
	fx32 Numer;	//法線ベクトルとカメラ位置ベクトルの内積
	MtxFx43 AngleRotMat;	//カメラアングル回転行列

	GF_CAMERA_PTR CameraPtr;
	VecFx32 Target;
}TP_TO_3D;

#if 0
static TP_TO_3D_PTR	TpTo3D = NULL;

TP_TO_3D_PTR FTouch_GetTpTo3DPtr(void)
{
    return TpTo3D;
}
#endif

#if 0
static GRID_POINT MakeGridPointFromVecFx32(const VecFx32 inPoint )
{
	GRID_POINT grid;
	//グリッドにする
	
	grid.x=inPoint.x / (16*FX32_ONE);
	grid.z=inPoint.z / (16*FX32_ONE);

	return grid;
}
#endif

VecFx32 FTouch_CalcTpXYTo3D(const u16 inX, const u16 inY, const TP_TO_3D_PTR inParam)
{
	s8 z,x;
	VecFx32 vec;
	VecFx32 target_vec;

	u8 pos_y,pos_x;
	u16 rot_x,rot_y;

	//ｙ＝0の平面との交点なのでセットしてしまう
	target_vec.y = 0;
	
	vec = GFC_GetLookTarget(inParam->CameraPtr);
	{	
		MtxFx43 mat;	//汎用行列変数
		VecFx32 dst_vec;
		VecFx32 base={0,0,-FX32_ONE};

		if (inY<H_HALF_SIZE){
			pos_y = H_HALF_SIZE-inY;
			rot_x = inParam->HView*pos_y/H_HALF_SIZE;
		}else{
			pos_y = inY-H_HALF_SIZE;
			rot_x = inParam->HView*pos_y/H_HALF_SIZE;
			rot_x*=(-1);
		}
		if (inX<W_HALF_SIZE){
			pos_x = W_HALF_SIZE-inX;
			rot_y = inParam->WView*pos_x/W_HALF_SIZE;
		}else{
			pos_x = inX-W_HALF_SIZE;
			rot_y = inParam->WView*pos_x/W_HALF_SIZE;
			rot_y*=(-1);
		}

		
		{
			MTX_RotX43(&mat, FX_SinIdx(rot_x), FX_CosIdx(rot_x) );
			MTX_MultVec43(&base, &mat, &dst_vec);
			MTX_RotY43(&mat, FX_SinIdx(rot_y), FX_CosIdx(rot_y) );
			MTX_MultVec43(&dst_vec, &mat, &dst_vec);

			MTX_MultVec43(&dst_vec, &inParam->AngleRotMat, &dst_vec);
			//平面との交点を求める
			{
				VecFx32 cross_point;
				fx32 t;
				fx32 denom;
				denom = VEC_DotProduct(&inParam->Norm,&dst_vec);
				t= -( FX_Div(inParam->Numer, denom));
//				OS_Printf("t=%x\n",t);
				VEC_MultAdd(t,&dst_vec,&inParam->CamPos,&cross_point);
//				OS_Printf("cross= %x,%x,%x\n",cross_point.x,cross_point.y,cross_point.z);
				target_vec.x = vec.x+(cross_point.x);
				target_vec.z = vec.z+(cross_point.z);

				return target_vec;
			}
		}
	}
	
}

TP_TO_3D_PTR FTouch_AllocUnderGroundTP(const GF_CAMERA_PTR camera_ptr)
{
	TP_TO_3D_PTR ptr;
	ptr = sys_AllocMemory(HEAPID_FIELD,sizeof(TP_TO_3D));
	FTouch_SetUpTpTo3DParam(ptr, camera_ptr);
	return ptr;
}

void FTouch_SetUpTpTo3DParam(TP_TO_3D_PTR	outParam, const GF_CAMERA_PTR camera_ptr)
{
	CAMERA_ANGLE ang;
	ang = GFC_GetCameraAngle(camera_ptr);
	outParam->HView = GFC_GetCameraPerspWay(camera_ptr);

	//アスペクト比4：3の時の水平視野角/2を求める
	{
		fx32 tan;
		tan = FX_Div(FX_SinIdx(outParam->HView),FX_CosIdx(outParam->HView));
		tan = tan*4/3;
		outParam->WView = FX_AtanIdx(tan);
	}
	{
		VecFx32 n = {0,FX32_ONE,0};
		VecFx32 cam_pos,target;
		cam_pos = GFC_GetCameraPos(camera_ptr);
		target = GFC_GetLookTarget(camera_ptr);
		VEC_Subtract( &cam_pos,
					  &target,
					  &outParam->CamPos);
		outParam->Norm = n;
		outParam->Numer = VEC_DotProduct(&n,&outParam->CamPos);
	}
	MTX_RotX43(&outParam->AngleRotMat, FX_SinIdx(ang.x), FX_CosIdx(ang.x) );
	outParam->CameraPtr = camera_ptr;
}

void FTouch_FreeUnderGroundTP(TP_TO_3D_PTR *ptr)
{
	
    if((*ptr)==NULL){
		OS_Printf("２度呼ばれている可能性あり\n");
		return;
	}
	GF_ASSERT((*ptr)!=NULL&&"すでにNULLです");
	sys_FreeMemoryEz((*ptr));
	(*ptr) = NULL;
}
