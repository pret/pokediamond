#include <nitro.h>
#include <nnsys.h>

#include "common.h"
#include "camera.h"

#include "camera_move_test.h"

#ifdef PM_DEBUG

#define ANGLE_MOVE	(32)

BOOL CameraInput(GF_CAMERA_PTR camera_ptr)
{
	u8 view;
	fx32 dist;
	u16 persp_way;
	
	BOOL res = FALSE;
	CAMERA_ANGLE angle = {0,0,0,0};
	VecFx32 move = {0,0,0};
static int shift_count = 0;

	if (/*sys.cont & PAD_BUTTON_L*/1){
		if (sys.cont & PAD_BUTTON_B){			//カメラ回転（公転）
			if (sys.cont & PAD_KEY_UP){
				angle.x = ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_DOWN){
				angle.x = -ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_LEFT){
				angle.y = -ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_RIGHT){
				angle.y = ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}
		}
		else if (sys.cont & PAD_BUTTON_Y){		//カメラ回転（自転）
			if (sys.cont & PAD_KEY_UP){
				angle.x = ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_DOWN){
				angle.x = -ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_LEFT){
				angle.y = ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_RIGHT){
				angle.y = -ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}
		}
		else if (sys.cont & PAD_BUTTON_A){
			if (sys.cont & PAD_KEY_UP){			//カメラズームアウト
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				if (persp_way+64<0x4000){
					GFC_AddCameraPerspWay(64,camera_ptr);
				}
			}else if (sys.cont & PAD_KEY_DOWN){	//カメラズームイン
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				if ((u16)(persp_way-64)>0x0000){
					GFC_AddCameraPerspWay(-64,camera_ptr);
				}
			}else if (sys.cont & PAD_KEY_LEFT){
				GFC_AddCameraPerspWay(64,camera_ptr);
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				//カメラの中心にある2D画像が、崩れずに表示できる距離を求める
				//つぶれずに表示するためには、1Dot　＝　1Unitで計算すればよい
				//カメラが画面中心を見つめるとき、画面半分のサイズは、96Dot
				//表示させたい、カメラのパースを考え、96Dot　＝　96Unitになる距離にすればよい
				dist = FX_Div( FX_Mul( FX_CosIdx( persp_way ), FX_F32_TO_FX32(96) ),	
									 FX_SinIdx( persp_way ));
				GFC_SetCameraDistance(dist,camera_ptr);
			}else if(sys.cont & PAD_KEY_RIGHT){
				GFC_AddCameraPerspWay(-64,camera_ptr);
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				//カメラの中心にある2D画像が、崩れずに表示できる距離を求める
				//つぶれずに表示するためには、1Dot　＝　1Unitで計算すればよい
				//カメラが画面中心を見つめるとき、画面半分のサイズは、96Dot
				//表示させたい、カメラのパースを考え、96Dot　＝　96Unitになる距離にすればよい
				dist = FX_Div( FX_Mul( FX_CosIdx( persp_way ), FX_F32_TO_FX32(96) ),	
									 FX_SinIdx( persp_way ));					
				GFC_SetCameraDistance(dist,camera_ptr);
			}
		}
		else if (sys.cont & PAD_BUTTON_X){
			fx32 shift;
			if(sys.cont & PAD_BUTTON_R){
				shift = (FX32_ONE*1)/10;
			}else{
				shift = FX32_ONE;
			}
			if (sys.cont & PAD_KEY_UP){
				move.z -= shift;
				GFC_ShiftCamera(&move,camera_ptr);
			}else if (sys.cont & PAD_KEY_DOWN){
				move.z += shift;
				GFC_ShiftCamera(&move,camera_ptr);
			}else if (sys.cont & PAD_KEY_LEFT){
				move.x -= shift;
				GFC_ShiftCamera(&move,camera_ptr);
			}else if (sys.cont & PAD_KEY_RIGHT){
				move.x += shift;
				GFC_ShiftCamera(&move,camera_ptr);
			}
		}else if(sys.cont & PAD_BUTTON_R){
			fx32 near,far;
			if (sys.cont & PAD_KEY_UP){
				far = GFC_GetCameraFar(camera_ptr);
				near = GFC_GetCameraNear(camera_ptr);
				far += FX32_ONE;
				OS_Printf("far=%d\n",far/FX32_ONE);
				GFC_SetCameraClip(near,far,camera_ptr);
			}else if (sys.cont & PAD_KEY_DOWN){
				far = GFC_GetCameraFar(camera_ptr);
				near = GFC_GetCameraNear(camera_ptr);
				far -= FX32_ONE;
				OS_Printf("far=%d\n",far/FX32_ONE);
				GFC_SetCameraClip(near,far,camera_ptr);
			}else if(sys.cont & PAD_KEY_RIGHT){
				far = GFC_GetCameraFar(camera_ptr);
				near = GFC_GetCameraNear(camera_ptr);
				near += FX32_ONE;
				OS_Printf("near=%d\n",near/FX32_ONE);
				GFC_SetCameraClip(near,far,camera_ptr);
			}else if(sys.cont & PAD_KEY_LEFT){
				far = GFC_GetCameraFar(camera_ptr);
				near = GFC_GetCameraNear(camera_ptr);
				near -= FX32_ONE;
				OS_Printf("near=%d\n",near/FX32_ONE);
				GFC_SetCameraClip(near,far,camera_ptr);
			}
		}
		else if (sys.cont & PAD_KEY_UP){	//カメラを遠ざける
			GFC_AddCameraDistance(FX32_ONE,camera_ptr);
/**			
			{
				VecFx32 move = {0,FX32_ONE*8,0};
				GFC_ShiftCamera(&move, camera_ptr);
				shift_count++;
				OS_Printf("shift=%d",shift_count);
			}
*/			
		}else if (sys.cont & PAD_KEY_DOWN){	//カメラを近づける
			GFC_AddCameraDistance(-FX32_ONE,camera_ptr);
/**			
			{
				VecFx32 move = {0,-(FX32_ONE*8),0};
				GFC_ShiftCamera(&move, camera_ptr);
				shift_count--;
				OS_Printf("shift=%d",shift_count);
			}
*/
		}
		else if (sys.trg & PAD_BUTTON_SELECT){
			//射影取得
			view = GFC_GetCameraView(camera_ptr);
			view = ((view+1)%2);
			GFC_SetCameraView(view,camera_ptr);
		}
		
		res = TRUE;
	}

	return res;
}

#endif	//PM_DEBUG
