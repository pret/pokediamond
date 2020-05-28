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
		if (sys.cont & PAD_BUTTON_B){			//�J������]�i���]�j
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
		else if (sys.cont & PAD_BUTTON_Y){		//�J������]�i���]�j
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
			if (sys.cont & PAD_KEY_UP){			//�J�����Y�[���A�E�g
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				if (persp_way+64<0x4000){
					GFC_AddCameraPerspWay(64,camera_ptr);
				}
			}else if (sys.cont & PAD_KEY_DOWN){	//�J�����Y�[���C��
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				if ((u16)(persp_way-64)>0x0000){
					GFC_AddCameraPerspWay(-64,camera_ptr);
				}
			}else if (sys.cont & PAD_KEY_LEFT){
				GFC_AddCameraPerspWay(64,camera_ptr);
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				//�J�����̒��S�ɂ���2D�摜���A���ꂸ�ɕ\���ł��鋗�������߂�
				//�Ԃꂸ�ɕ\�����邽�߂ɂ́A1Dot�@���@1Unit�Ōv�Z����΂悢
				//�J��������ʒ��S�����߂�Ƃ��A��ʔ����̃T�C�Y�́A96Dot
				//�\�����������A�J�����̃p�[�X���l���A96Dot�@���@96Unit�ɂȂ鋗���ɂ���΂悢
				dist = FX_Div( FX_Mul( FX_CosIdx( persp_way ), FX_F32_TO_FX32(96) ),	
									 FX_SinIdx( persp_way ));
				GFC_SetCameraDistance(dist,camera_ptr);
			}else if(sys.cont & PAD_KEY_RIGHT){
				GFC_AddCameraPerspWay(-64,camera_ptr);
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				//�J�����̒��S�ɂ���2D�摜���A���ꂸ�ɕ\���ł��鋗�������߂�
				//�Ԃꂸ�ɕ\�����邽�߂ɂ́A1Dot�@���@1Unit�Ōv�Z����΂悢
				//�J��������ʒ��S�����߂�Ƃ��A��ʔ����̃T�C�Y�́A96Dot
				//�\�����������A�J�����̃p�[�X���l���A96Dot�@���@96Unit�ɂȂ鋗���ɂ���΂悢
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
		else if (sys.cont & PAD_KEY_UP){	//�J��������������
			GFC_AddCameraDistance(FX32_ONE,camera_ptr);
/**			
			{
				VecFx32 move = {0,FX32_ONE*8,0};
				GFC_ShiftCamera(&move, camera_ptr);
				shift_count++;
				OS_Printf("shift=%d",shift_count);
			}
*/			
		}else if (sys.cont & PAD_KEY_DOWN){	//�J�������߂Â���
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
			//�ˉe�擾
			view = GFC_GetCameraView(camera_ptr);
			view = ((view+1)%2);
			GFC_SetCameraView(view,camera_ptr);
		}
		
		res = TRUE;
	}

	return res;
}

#endif	//PM_DEBUG
