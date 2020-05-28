#ifndef _CAMERA_H_
#define _CAMERA_H_

//�J�����g���[�X�}�X�N��`
#define CAM_TRACE_MASK_X	(1)
#define CAM_TRACE_MASK_Y	(2)
#define CAM_TRACE_MASK_Z	(4)
#define CAM_TRACE_MASK_ALL	(CAM_TRACE_MASK_X|CAM_TRACE_MASK_Y|CAM_TRACE_MASK_Z)

extern GXBufferMode	SwapBuffMode;
//---------------------------------------------------------
//			�萔��`
//---------------------------------------------------------
//---------------------------
//	�ˉe�t���O�萔
enum
{
	GF_CAMERA_PERSPECTIV,		// �����ˉe
	GF_CAMERA_ORTHO,			// ���ˉe
};

/*---------------------------------------------------------------------------*
	�J�����A���O���\����
 *---------------------------------------------------------------------------*/
typedef struct
{
	u16 x;
	u16 y;
	u16 z;
	u16 Dummy;
} CAMERA_ANGLE;

/*---------------------------------------------------------------------------*
	�J�����A���O���\����
 *---------------------------------------------------------------------------*/
//�J�����p�����[�^�\����
typedef	struct	{
//	VecFx32			*Position;
	fx32			Distance;
	CAMERA_ANGLE	Angle;
	u8				View;
	u16				PerspWay;
	u8				dummy;
}GF_CAMERA_PARAM;

typedef struct GF_CAMERA_tag * GF_CAMERA_PTR;
typedef struct GF_CAMERA_tag const * GF_CAMERA_CONST_PTR;

extern void GFC_AllocTraceData(	const int inHistNum, const int inDelay,
								const int inTraceMask, const int inHeapID,
								GF_CAMERA_PTR ioCamera);

extern void GFC_FreeTraceData(GF_CAMERA_PTR camera_ptr);

//�J�����쐬
extern GF_CAMERA_PTR GFC_AllocCamera(const int inHeapID);

//�J�������
extern void GFC_FreeCamera(GF_CAMERA_PTR camera_ptr);

//�J�����R�s�[
extern void GFC_CopyCamera(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera);
//�J�����g���[�X�f�[�^�̃|�C���^�R�s�[
extern void GFC_CopyCameraTracePtr(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera);
//�J�������f�֐��i�`�掞�ɌĂԁj
extern void GFC_CameraLookAt();
//�J�����̏������ݒ�
extern void GFC_SetCamUp(const VecFx32 *inCamUp,GF_CAMERA_PTR camera_ptr);
//�J����������
extern void GFC_InitCameraTDA( const VecFx32* inTarget,
						const fx32 inDistance,
						const CAMERA_ANGLE *inAngle,
						const u16 inPerspWay,
						const u8 inView,
						const BOOL inBindFlg,
						GF_CAMERA_PTR camera_ptr
					);
//�J����������
extern void GFC_InitCameraCDA( const VecFx32* inCamPos,
						const fx32 inDistance,
						const CAMERA_ANGLE *inAngle,
						const u16 inPerspWay,
						const u8 inView,
						GF_CAMERA_PTR camera_ptr
					);

//�J����������
extern void GFC_InitCameraTC( const VecFx32* inTarget,
							const VecFx32* inCamPos,
							const u16 inPerspWay,
							const u8 inView,
							const BOOL inbindFlg,
							GF_CAMERA_PTR camera_ptr
						);

//�J�����̃A�^�b�`(�J�����̗L����)
void GFC_AttachCamera(GF_CAMERA_PTR camera_ptr);
//�J�������o�C���h����Ώە����Z�b�g
void GFC_BindCameraTarget(const VecFx32 *inTarget, GF_CAMERA_PTR camera_ptr);
//�J�������o�C���h���Ă���Ώە���؂藣��
extern void GFC_PurgeCameraTarget(GF_CAMERA_PTR camera_ptr);
//���݂̃J��������X���b�v�o�b�t�@���[�h���擾
extern GXBufferMode GetBufferMode(void);
//�J������NULL���Z�b�g
extern void GFC_PurgeCamera(void);
//�ˉe�Z�b�g
extern void GFC_SetCameraView(const u8 inView,GF_CAMERA_PTR camera_ptr);
//����p�̃Z�b�g
extern void GFC_SetCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr);
//����p�̉��Z
extern void GFC_AddCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr);
//�J�����ƒ����_�𓯎��ɕ��s�ړ�
extern void GFC_ShiftCamera(const VecFx32 *inMoveVec,GF_CAMERA_PTR camera_ptr);
//�J�����A���O���Z�b�g	���]
extern void GFC_SetCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//�J�����A���O���Z�b�g�@���]
extern void GFC_SetCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//�J�����A���O�����Z�@���]
extern void GFC_AddCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//�J�����A���O�����Z�@���]
extern void GFC_AddCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//�J���������Z�b�g
extern void GFC_SetCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr);
//�����_�Đݒ�
extern void GFC_ReSetCameraTarget(const VecFx32 *inTargetVec,GF_CAMERA_PTR camera_ptr);
//�J�����������Z
extern void GFC_AddCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr);
//�J�����N���b�v���W�Z�b�g
extern void GFC_SetCameraClip(const fx32 near,const fx32 far,GF_CAMERA_PTR camera_ptr);
//�ˉe�擾
extern u8 GFC_GetCameraView(GF_CAMERA_CONST_PTR camera_ptr);
//����p�̎擾
extern u16 GFC_GetCameraPerspWay(GF_CAMERA_CONST_PTR camera_ptr);
//�����̎擾
extern fx32 GFC_GetCameraDistance(GF_CAMERA_CONST_PTR camera_ptr);
//�A���O���̎擾
extern CAMERA_ANGLE GFC_GetCameraAngle(GF_CAMERA_CONST_PTR camera_ptr);
//�����_�̎擾
extern VecFx32 GFC_GetLookTarget(GF_CAMERA_CONST_PTR camera_ptr);
//�J�����ʒu�̎擾
extern VecFx32 GFC_GetCameraPos(GF_CAMERA_CONST_PTR camera_ptr);
//�t�@�[�擾
extern fx32 GFC_GetCameraFar(GF_CAMERA_CONST_PTR camera_ptr);
//�j�A�擾
extern fx32 GFC_GetCameraNear(GF_CAMERA_CONST_PTR camera_ptr);
//�����_�̐ݒ�
extern void GFC_SetLookTarget(const VecFx32* t_pos, GF_CAMERA_PTR camera_ptr);
//�J�����ʒu�̐ݒ�
extern void GFC_SetCameraPos(const VecFx32* c_pos, GF_CAMERA_PTR camera_ptr);

#endif //_CAMERA_H_
