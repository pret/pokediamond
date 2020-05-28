/*---------------------------------------------------------------------------*
  Project:  PokemonDS
  File:     camera.c

  ��{�J�����V�X�e��

 *---------------------------------------------------------------------------*/

#include <nitro.h>
#include <nnsys.h>
# include "system.h"
#include "camera.h"
#include "calc3d.h"
#include "assert.h"

GXBufferMode	SwapBuffMode = GX_BUFFERMODE_W;		// �X���b�v�o�b�t�@���[�h

/*---------------------------------------------------------------------------*
	LookAt�\����
 *---------------------------------------------------------------------------*/
typedef struct
{
	VecFx32		camPos;					// �J�����̈ʒu(�����_)
	VecFx32		target;					// �J�����̏œ_(�������_)
	VecFx32		camUp;					// �J�����̏����

} GF_CAMERA_LOOKAT;

/*---------------------------------------------------------------------------*
	Vw3Persp�\����
 *---------------------------------------------------------------------------*/
typedef struct
{
	fx32		fovySin;			// ����p/2�̐������Ƃ����l
    fx32		fovyCos;			// ����p/2�̗]�����Ƃ����l
    fx32		aspect;				// �A�X�y�N�g��
    fx32		nearClip;			// ���_����near�N���b�v�ʂ܂ł̋���
    fx32		farClip;			// ���_����far�N���b�v�ʂ܂ł̋���

} GF_CAMERA_PERSP;

/*---------------------------------------------------------------------------*
	�J�����g���[�X�\����
 *---------------------------------------------------------------------------*/
typedef struct GF_CAMERA_TRACE_tag
{
	int HistNum;
	int CamPoint;
	int TargetPoint;
	int Delay;			//�x������
	BOOL UpdateFlg;		//�X�V�J�n�t���O
	BOOL ValidX;		//X�x����L���ɂ��邩�̃t���O
	BOOL ValidY;		//Y�x����L���ɂ��邩�̃t���O
	BOOL ValidZ;		//Z�x����L���ɂ��邩�̃t���O
	VecFx32 *HistPos;
}GF_CAMERA_TRACE;

/*---------------------------------------------------------------------------*
	�J�����\����
 *---------------------------------------------------------------------------*/
typedef struct GF_CAMERA_tag
{
	GF_CAMERA_PERSP		persp;
	GF_CAMERA_LOOKAT	lookat;

	fx32			Distance;
	CAMERA_ANGLE	Angle;
	u8				View;
	u16				PerspWay;
	VecFx32 BindTargetOld;
	const VecFx32 *BindTarget;
	BOOL XBind;
	BOOL YBind;
	BOOL ZBind;
	GF_CAMERA_TRACE *Trace;
} GF_CAMERA;

/*---------------------------------------------------------------------------*
	static�ϐ�
 *---------------------------------------------------------------------------*/
static GF_CAMERA_PTR 	GF_Camera = NULL;        // �J�����\���̃|�C���^

//---------------------------------------------------------------------------
/**
 * @brief	�J�����ʒu�𒍎��_�A�����A�A���O������Z�o����
 * 
 * @param	camera_ptr	�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetCamPosByTarget_Dist_Ang(GF_CAMERA_PTR camera_ptr)
{
	u16 angle_x;
	//�p�˒n�ʂ���̌X���ɕϊ�
	angle_x = -camera_ptr->Angle.x;
	/*== �J�������W�����߂� ==*/
	camera_ptr->lookat.camPos.x = FX_Mul( FX_Mul( FX_SinIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.camPos.z = FX_Mul( FX_Mul( FX_CosIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.camPos.y = FX_Mul( FX_SinIdx( angle_x ), camera_ptr->Distance );

	/*== ���_����̋����ɂ��� ==*/
	VEC_Add(&camera_ptr->lookat.camPos,&camera_ptr->lookat.target,&camera_ptr->lookat.camPos);
	//camera_ptr->lookat.camPos.x += camera_ptr->lookat.target.x;
	//camera_ptr->lookat.camPos.y += camera_ptr->lookat.target.y;
	//camera_ptr->lookat.camPos.z += camera_ptr->lookat.target.z;
	
}

//---------------------------------------------------------------------------
/**
 * @brief	�����_���J�����ʒu�A�����A�A���O������Z�o����
 * 
 * @param	camera_ptr	�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetTargetByCamPos_Dist_Ang(GF_CAMERA_PTR camera_ptr)
{
	u16 angle_x;
	//�p�˒n�ʂ���̌X���ɕϊ�
	angle_x = -camera_ptr->Angle.x;
	camera_ptr->lookat.target.x = -FX_Mul( FX_Mul( FX_SinIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.target.z = -FX_Mul( FX_Mul( FX_CosIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.target.y = -FX_Mul( FX_SinIdx( angle_x ), camera_ptr->Distance );
	VEC_Add(&camera_ptr->lookat.target,&camera_ptr->lookat.camPos,&camera_ptr->lookat.target);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�������������ʏ���
 * 
 * @param	inPerspway	�p�[�X
 * @param	camera_ptr	�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void InitCameraCommon(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr){
	//����p�Z�b�g
	camera_ptr->PerspWay = inPerspWay;
	camera_ptr->persp.fovySin  = FX_SinIdx( inPerspWay );
	camera_ptr->persp.fovyCos  = FX_CosIdx( inPerspWay );
	//�A�X�y�N�g��Z�b�g
	camera_ptr->persp.aspect   = FX32_ONE * 4 / 3;
	//�j�A�E�t�@�[�N���b�v���Z�b�g
	camera_ptr->persp.nearClip = FX32_ONE * 150;
	camera_ptr->persp.farClip  = FX32_ONE * 900;

	//�J�����̏������ݒ�
	camera_ptr->lookat.camUp.x =  0;
	camera_ptr->lookat.camUp.y =  FX32_ONE;
	camera_ptr->lookat.camUp.z =  0;

	//�J�������߂炦��Ώە��̍��W�ւ̃|�C���^��������
	camera_ptr->BindTarget = NULL;
	
	camera_ptr->XBind = FALSE;
	camera_ptr->YBind = FALSE;
	camera_ptr->ZBind = FALSE;

	camera_ptr->Trace = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	�o�C���h����
 * 
 * @param	inCamera	�J�����|�C���^
 * @param	outVec		�o�C���h����
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void FixBindValid(GF_CAMERA_CONST_PTR inCamera, VecFx32 *outVec)
{
	if (inCamera->XBind == FALSE){
		outVec->x = 0;
	}
	if (inCamera->YBind == FALSE){
		outVec->y = 0;
	}
	if (inCamera->ZBind == FALSE){
		outVec->z = 0;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�g���[�X�f�[�^�̍X�V
 * 
 * @param	camera_ptr	�J�����|�C���^
 * @param	inVec		�o�b�t�@�Ɋi�[������W
 * @param	outVec		�K�p���W
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void UpdateTraceData(GF_CAMERA_CONST_PTR camera_ptr, const VecFx32 *inVec, VecFx32 *outVec)
{
	int *cam;
	int *target;
	if (camera_ptr->Trace==NULL){
		(*outVec) = (*inVec);
	}else{
		cam = &camera_ptr->Trace->CamPoint;
		target = &camera_ptr->Trace->TargetPoint;
		if (!camera_ptr->Trace->UpdateFlg){
			(*outVec) = (*inVec);
			if (*cam==camera_ptr->Trace->Delay){
				camera_ptr->Trace->UpdateFlg = TRUE;
			}
		}else{
			//�����f�[�^������W�擾
			(*outVec) = camera_ptr->Trace->HistPos[(*cam)];
		}
		//�Q�ƈʒu�X�V
		(*cam) = ((*cam)+1)%camera_ptr->Trace->HistNum;
		//�����ɐς�
		camera_ptr->Trace->HistPos[(*target)] = (*inVec);
		//���������ʒu�X�V
		(*target) = ((*target)+1)%camera_ptr->Trace->HistNum;
		
		//�g���[�X�f�[�^�̖������W���́A���̂܂܌��ݍ��W���̗p
		if (!camera_ptr->Trace->ValidX){	//����������
			outVec->x = inVec->x;
		}
		if (!camera_ptr->Trace->ValidY){	//����������
			outVec->y = inVec->y;
		}
		if (!camera_ptr->Trace->ValidZ){	//����������
			outVec->z = inVec->z;
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�g���[�X�\���̂̃A���P�[�V�����@�J�������Ώە��Ƀo�C���h�ς݂ł��邱��
 * 
 * @param	inHistNum		�o�b�t�@�T�C�Y
 * @param	inDelay			�x���x����
 * @param	inTraceMask		�g���[�X�}�X�N	camera.h�ɒ�`
 * @param	inHeapID		�q�[�vID
 * @param	ioCamera		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AllocTraceData(const int inHistNum, const int inDelay,
						const int inTraceMask, const int inHeapID,
						GF_CAMERA_PTR ioCamera)
{
	int i;
	GF_CAMERA_TRACE *trace;
	//�o�C���h����Ă��Ȃ���΁A�������Ȃ�
	if (ioCamera->BindTarget == NULL){
		return;
	}
	//�z��T�C�Y�̐������`�F�b�N
	GF_ASSERT((inDelay+1<=inHistNum)&&"�z�񐔂�����܂���");
	
	trace = sys_AllocMemory(inHeapID,sizeof(GF_CAMERA_TRACE));
	trace->HistPos = sys_AllocMemory(inHeapID,sizeof(VecFx32)*inHistNum);
	
	//�g���[�X�z��N���A
	for(i=0;i<inHistNum;i++){
		trace->HistPos[i].x = 0;
		trace->HistPos[i].y = 0;
		trace->HistPos[i].z = 0;
	}
	
	trace->HistNum = inHistNum;
	//�O�ԖڂɃJ�����Q�ƈʒu���Z�b�g
	trace->CamPoint = 0;
	//�Ώە��Q�ƈʒu�Z�b�g
	trace->TargetPoint = 0+inDelay;
	
	trace->Delay = inDelay;
	trace->UpdateFlg = FALSE;
	
	trace->ValidX = FALSE;
	trace->ValidY = FALSE;
	trace->ValidZ = FALSE;
	if (inTraceMask & CAM_TRACE_MASK_X){
		trace->ValidX = TRUE;
	}
	if (inTraceMask & CAM_TRACE_MASK_Y){
		trace->ValidY = TRUE;
	}
	if (inTraceMask & CAM_TRACE_MASK_Z){
		trace->ValidZ = TRUE;
	}
	
	ioCamera->Trace = trace;
}

//---------------------------------------------------------------------------
/**
 * @brief	�g���[�X�f�[�^�̉��
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_FreeTraceData(GF_CAMERA_PTR camera_ptr)
{
	if (camera_ptr->Trace!=NULL){
		sys_FreeMemoryEz(camera_ptr->Trace->HistPos);
		sys_FreeMemoryEz(camera_ptr->Trace);
		camera_ptr->Trace = NULL;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����쐬
 * 
 * @param	inHeapID		�q�[�vID
 * 
 * @return	GF_CAMERA_PTR	�J�����|�C���^
 */
//---------------------------------------------------------------------------
GF_CAMERA_PTR GFC_AllocCamera(const int inHeapID)
{
	GF_CAMERA_PTR camera_ptr;
	camera_ptr = sys_AllocMemory(inHeapID,sizeof(GF_CAMERA));
	return camera_ptr;
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�������
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_FreeCamera(GF_CAMERA_PTR camera_ptr)
{
	//�J�����{�̂̉��
	sys_FreeMemoryEz( camera_ptr );
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����R�s�[
 * 
 * @param	inCamera		�R�s�[���J�����|�C���^
 * @param	outCamera		�R�s�[��J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_CopyCamera(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera)
{
	*outCamera = (*inCamera);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����g���[�X�f�[�^�̃|�C���^�R�s�[
 * 
 * @param	inCamera		�R�s�[���J�����|�C���^
 * @param	outCamera		�R�s�[��J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_CopyCameraTracePtr(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera)
{
	outCamera->Trace = inCamera->Trace;
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����̃A�^�b�`(�J�����̗L����)
 * 
 * @param	camera_ptr	�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AttachCamera(GF_CAMERA_PTR camera_ptr)
{
	GF_Camera = camera_ptr;
}

//---------------------------------------------------------------------------
/**
 * @brief	�J������NULL���Z�b�g�i�A�^�b�`�����j
 * 
 * @param	none
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_PurgeCamera(void)
{
	GF_Camera = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�������f�֐��i�`�掞�ɌĂԁj
 * 
 * @param	none
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_CameraLookAt(void)
{
	if (GF_Camera == NULL){
		return;
	}
	
	//�J�������������o�C���h���Ă���Ȃ�D��I�ɂ��̍��W��߂炦��
	if (GF_Camera->BindTarget != NULL){
		//�ړ��������v�Z
		VecFx32 vec;
		VecFx32 dst_vec;
		VEC_Subtract(GF_Camera->BindTarget,&GF_Camera->BindTargetOld,&vec);

		FixBindValid(GF_Camera,&vec);
		UpdateTraceData(GF_Camera, &vec, &dst_vec);
		
		GFC_ShiftCamera(&dst_vec,GF_Camera);
		GF_Camera->BindTargetOld = *GF_Camera->BindTarget;
	}
	NNS_G3dGlbLookAt(&GF_Camera->lookat.camPos, &GF_Camera->lookat.camUp, &GF_Camera->lookat.target);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����̏������ݒ�
 * 
 * @param	inCamUp		�J�����������`�x�N�g��
 * @param	camera_ptr	�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCamUp(const VecFx32 *inCamUp,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.camUp = *inCamUp;
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�������o�C���h����Ώە����Z�b�g
 * 
 * @param	inTarget	�o�C���h�Ώۍ��W
 * @param	camera_ptr	�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_BindCameraTarget(const VecFx32 *inTarget, GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->BindTarget = inTarget;
	camera_ptr->BindTargetOld = *inTarget;
	camera_ptr->XBind = TRUE;
	camera_ptr->YBind = TRUE;
	camera_ptr->ZBind = TRUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�������o�C���h���Ă���Ώە���؂藣��
 * 
 * @param	camera_ptr	�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_PurgeCameraTarget(GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->BindTarget = NULL;
	camera_ptr->XBind = FALSE;
	camera_ptr->YBind = FALSE;
	camera_ptr->ZBind = FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	���݂̃J��������X���b�v�o�b�t�@���[�h���擾
 * 
 * @param	none
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
GXBufferMode GetBufferMode(void)
{
	if (GF_Camera!=NULL){
		if (GF_Camera->View == GF_CAMERA_PERSPECTIV){
			return GX_BUFFERMODE_W;
		}else{
			return GX_BUFFERMODE_Z;
		}
	}else{
		OS_Printf("ERROR:�o�b�t�@���[�h�擾���s");
		return GX_BUFFERMODE_W;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����̃N���b�v�p�����[�^���Z�b�g����
 * 
 * @param	near			�j�A�N���b�v�l
 * @param	far				�t�@�[�N���b�v�l
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraClip(const fx32 near,const fx32 far,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->persp.nearClip = near;
	camera_ptr->persp.farClip = far;
	GFC_SetCameraView(camera_ptr->View,camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����\���̂�������(�����_�A�����A�A���O�����g���ď�����)
 * 
 * @param	inTarget		�Ώے����_
 * @param	inDistance		�����_�܂ł̋���
 * @param	inAngle			�A���O��
 * @param	inPerspWay		�p�[�X
 * @param	inView			�ˉe���[�h
 * @param	inBindFlg		�����_�Ƃ̃o�C���h�L��
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_InitCameraTDA
( const VecFx32* inTarget,
  const fx32 inDistance,
  const CAMERA_ANGLE *inAngle,
  const u16 inPerspWay,
  const u8 inView,
  const BOOL inBindFlg,
  GF_CAMERA_PTR camera_ptr
)
{
	// �J�����̐ݒ�
	InitCameraCommon(inPerspWay,camera_ptr);
	
	//�����_���Z�b�g
	camera_ptr->lookat.target = *inTarget;
	
	//�����_����̃J�����ʒu�̋�����ݒ�
	camera_ptr->Distance = inDistance;

	//�A���O���Z�b�g
	camera_ptr->Angle = *inAngle;

	// �J�����̍��W���Z�b�g
	SetCamPosByTarget_Dist_Ang(camera_ptr);

	//�ˉe�Z�b�g
	GFC_SetCameraView(inView,camera_ptr);

	if (inBindFlg){
		//�J�����̕߂炦��Ώە����o�C���h
		camera_ptr->BindTarget = inTarget;
		camera_ptr->BindTargetOld = *inTarget;
		camera_ptr->XBind = TRUE;
		camera_ptr->YBind = TRUE;
		camera_ptr->ZBind = TRUE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����\���̂�������(�J�����ʒu�A�����A�A���O�����g���ď�����)
 * 
 * @param	inCamPos		�J�����ʒu
 * @param	inDistance		�����_�܂ł̋���
 * @param	inAngle			�A���O��
 * @param	inPerspWay		�p�[�X
 * @param	inView			�ˉe���[�h
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_InitCameraCDA
( const VecFx32* inCamPos,
  const fx32 inDistance,
  const CAMERA_ANGLE *inAngle,
  const u16 inPerspWay,
  const u8 inView,
  GF_CAMERA_PTR camera_ptr
)
{
	// �J�����̐ݒ�
	InitCameraCommon(inPerspWay,camera_ptr);

	//�J�����̍��W���Z�b�g
	camera_ptr->lookat.camPos = *inCamPos;
	
	//�J�����ʒu���璍���_�܂ł̋�����ݒ�
	camera_ptr->Distance = inDistance;

	//�A���O���Z�b�g
	camera_ptr->Angle = *inAngle;

	// �����_�̍��W���Z�b�g
	SetTargetByCamPos_Dist_Ang(camera_ptr);

	//�ˉe�Z�b�g
	GFC_SetCameraView(inView,camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����\���̂�������(�����_�A�J�����ʒu���g���ď������@Z����]���Ή�)
 * 
 * @param	inTarget		�Ώے����_
 * @param	inCamPos		�J�����ʒu
 * @param	inPerspWay		�p�[�X
 * @param	inView			�ˉe���[�h
 * @param	inBindFlg		�����_�Ƃ̃o�C���h�L��
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_InitCameraTC
( const VecFx32* inTarget,
  const VecFx32* inCamPos,
  const u16 inPerspWay,
  const u8 inView,
  const BOOL inBindFlg,
  GF_CAMERA_PTR camera_ptr
)
{
	VecFx32 dst;
	// �J�����̐ݒ�
	InitCameraCommon(inPerspWay,camera_ptr);
	
	//�����_���Z�b�g
	camera_ptr->lookat.target = *inTarget;

	//�J�����̍��W���Z�b�g
	camera_ptr->lookat.camPos = *inCamPos;
	
	//�����_����̃J�����ʒu�̋�����ݒ�
	VEC_Subtract(inCamPos, inTarget , &dst);
	camera_ptr->Distance = VEC_Mag(&dst); 

	//�A���O���Z�b�g
	{
		VecFx32 x_vec = {0,0,0};
		VecFx32 y_vec = {0,0,0};
		VecFx32 vec = {0,0,0};
		VecFx32 base_vec;
		base_vec.x = 0;
		base_vec.y = 0;
		base_vec.z = FX32_ONE;
		vec = dst;
		vec.y = 0;
		camera_ptr->Angle.y = GetRad(&base_vec, &vec );
		
		base_vec.x = FX32_ONE;
		base_vec.y = 0;
		base_vec.z = 0;
		vec.x = dst.z;
		vec.z = dst.y;
		vec.y = 0;
		camera_ptr->Angle.x = GetRad(&base_vec, &vec );

		camera_ptr->Angle.z = 0;

		OS_Printf("ANGGLE_%x,%x,%x\n",camera_ptr->Angle.x,camera_ptr->Angle.y,camera_ptr->Angle.z);
	}
	
	//�ˉe�Z�b�g
	GFC_SetCameraView(inView,camera_ptr);

	if (inBindFlg){
		//�J�����̕߂炦��Ώە����o�C���h
		camera_ptr->BindTarget = inTarget;
		camera_ptr->BindTargetOld = *inTarget;
		camera_ptr->XBind = TRUE;
		camera_ptr->YBind = TRUE;
		camera_ptr->ZBind = TRUE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�ˉe�Z�b�g
 * 
 * @param	inView			�ˉe���[�h
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraView(const u8 inView,GF_CAMERA_PTR camera_ptr)
{
	// �ˉe�`�F�b�N
	if( inView == GF_CAMERA_PERSPECTIV )
	{
		// �����ˉe
		NNS_G3dGlbPerspective
			(camera_ptr->persp.fovySin, camera_ptr->persp.fovyCos,
			 camera_ptr->persp.aspect, camera_ptr->persp.nearClip,
			 camera_ptr->persp.farClip);
		camera_ptr->View = GF_CAMERA_PERSPECTIV;
		SwapBuffMode = GX_BUFFERMODE_Z;//GX_BUFFERMODE_W;
	}
	else	//(inVew == SIMPLE_ORTHO)
	{
		fx32	height, width;			// �����ƕ�

		//-------- ���ˉe --------
		// �����ˉe�̐ݒ肩�琳�ˉe���Z�b�g
		// ���������߂�
		height = FX_Mul(FX_Div(camera_ptr->persp.fovySin, camera_ptr->persp.fovyCos), camera_ptr->Distance);
		// �������߂�
		width  = FX_Mul(height, camera_ptr->persp.aspect );

		NNS_G3dGlbOrtho(
			height,
			-height,
			-width,
			width,
			camera_ptr->persp.nearClip,
			camera_ptr->persp.farClip
		);
		camera_ptr->View = GF_CAMERA_ORTHO;
		SwapBuffMode = GX_BUFFERMODE_Z;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	����p�̃Z�b�g
 * 
 * @param	inPerspWay		�p�[�X
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->PerspWay = inPerspWay;

	/*== �ˉe�̊p�x���Z�b�g ==*/
	camera_ptr->persp.fovySin  = FX_SinIdx( camera_ptr->PerspWay );
	camera_ptr->persp.fovyCos  = FX_CosIdx( camera_ptr->PerspWay );

	GFC_SetCameraView(camera_ptr->View,camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	����p�̉��Z
 * 
 * @param	inPerspWay		���Z�p�[�X
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->PerspWay += inPerspWay;

	/*== �ˉe�̊p�x���Z�b�g ==*/
	camera_ptr->persp.fovySin  = FX_SinIdx( camera_ptr->PerspWay );
	camera_ptr->persp.fovyCos  = FX_CosIdx( camera_ptr->PerspWay );

	GFC_SetCameraView(camera_ptr->View,camera_ptr);
}
#if 0
//�J�����ʒu�̃Z�b�g
void SetCameraPos(const VecFx32* inCamPos)
{
	camera_ptr->lookat.camPos = *inCamPos;
}

//�����_�̃Z�b�g
void SetCameraTarget(const VecFx32* inTarget)
{
	camera_ptr->lookat.target = *inTarget;
}

//�����_���ړ�
void MoveTarget(const VecFx32 *inMoveVec)
{
	VEC_Add(&camera_ptr->lookat.target,&inMoveVec,&Gf_Camera.lookat.target);
}

//�J�����ʒu���ړ�
void MoveCameraPos(const VecFx32 *inMoveVec)
{
	VEC_Add(&camera_ptr->lookat.camPos,&inMoveVec,&camera_ptr->lookat.camPos);
}
#endif

//---------------------------------------------------------------------------
/**
 * @brief	�J�����ƒ����_�𓯎��ɕ��s�ړ�
 * 
 * @param	inMoveVec		�ړ��l
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_ShiftCamera(const VecFx32 *inMoveVec,GF_CAMERA_PTR camera_ptr)
{
	//�J��������ݒ�
	VEC_Add(&camera_ptr->lookat.camPos,inMoveVec,&camera_ptr->lookat.camPos);
	VEC_Add(&camera_ptr->lookat.target,inMoveVec,&camera_ptr->lookat.target);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����A���O���Z�b�g	���]
 * 
 * @param	inAngle			�A���O��
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle = *inAngle;
	SetTargetByCamPos_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����A���O���Z�b�g	���]
 * 
 * @param	inAngle			�A���O��
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle = *inAngle;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����A���O�����Z	���]
 * 
 * @param	inAngle			���Z�A���O��
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle.x += inAngle->x;
	camera_ptr->Angle.y += inAngle->y;
	camera_ptr->Angle.z += inAngle->z;
	SetTargetByCamPos_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����A���O�����Z	���]
 * 
 * @param	inAngle			���Z�A���O��
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle.x += inAngle->x;
	camera_ptr->Angle.y += inAngle->y;
	camera_ptr->Angle.z += inAngle->z;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J���������Z�b�g
 * 
 * @param	inDist			����
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Distance = inDist;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�����_�̍Đݒ�(�J�����̈ʒu������)
 * 
 * @param	inTargetVec			�����_
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_ReSetCameraTarget(const VecFx32 *inTargetVec,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.target = (*inTargetVec);
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����������Z
 * 
 * @param	inDist			���Z������
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Distance += inDist;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//////////////////////////////////
//�擾�֐�(�܂��S������Ă܂���)//
//////////////////////////////////

//---------------------------------------------------------------------------
/**
 * @brief	�ˉe�擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	u8				�ˉe���[�h
 */
//---------------------------------------------------------------------------
u8 GFC_GetCameraView(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->View;
}

//---------------------------------------------------------------------------
/**
 * @brief	����p�̎擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	u16				�p�[�X
 */
//---------------------------------------------------------------------------
u16 GFC_GetCameraPerspWay(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->PerspWay;
}

//---------------------------------------------------------------------------
/**
 * @brief	�����̎擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	fx32			����
 */
//---------------------------------------------------------------------------
fx32 GFC_GetCameraDistance(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->Distance;
}

//---------------------------------------------------------------------------
/**
 * @brief	�A���O���擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	CAMERA_ANGLE	�A���O��
 */
//---------------------------------------------------------------------------
CAMERA_ANGLE GFC_GetCameraAngle(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->Angle;
}

//---------------------------------------------------------------------------
/**
 * @brief	�����_�̎擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	VecFx32			�����_
 */
//---------------------------------------------------------------------------
VecFx32 GFC_GetLookTarget(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->lookat.target;
}

//---------------------------------------------------------------------------
/**
 * @brief	�J�����ʒu�̎擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	VecFx32			�J�����ʒu
 */
//---------------------------------------------------------------------------
VecFx32 GFC_GetCameraPos(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->lookat.camPos;
}

//---------------------------------------------------------------------------
/**
 * @brief	�t�@�[�擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	VecFx32			�t�@�[
 */
//---------------------------------------------------------------------------
fx32 GFC_GetCameraFar(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->persp.farClip;
}

//---------------------------------------------------------------------------
/**
 * @brief	�j�A�擾
 * 
 * @param	camera_ptr		�J�����|�C���^
 * 
 * @return	VecFx32			�j�A
 */
//---------------------------------------------------------------------------
fx32 GFC_GetCameraNear(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->persp.nearClip;
}

//�����_�̐ݒ�
void GFC_SetLookTarget(const VecFx32* t_pos, GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.target = *t_pos;
}

//�J�����ʒu�̐ݒ�
void GFC_SetCameraPos(const VecFx32* c_pos, GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.camPos = *c_pos;
}
