//============================================================================================
/**
 * @file	field_camera.c
 * @bfief	�t�B�[���h�J����
 * @author	GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "camera.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "worldmap.h"
#include "fieldsys.h"

#include "field_camera.h"

#define FIELD_CAMERA_DELAY	(6)
#define FIELD_CAMERA_TRACE_BUFF	(FIELD_CAMERA_DELAY+1)

typedef	struct	{
	fx32			Distance;
	CAMERA_ANGLE	Angle;
	u8				View;
	u16				PerspWay;
	fx32			Near;
	fx32			Far;
}FLD_CAMERA_PARAM;

static const FLD_CAMERA_PARAM FieldCameraData[] = {
	{							//	0	�ʏ�
		0x29aec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	1	���W��
		0x29aec1,
		{
			-0x309e,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	2	�ŏ��̌�
		0x20374c,
		{
			-0x26de,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x770,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	3	�|�W��
		0x29aec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	4	�����i���ˉe�j
		0x61b89b,
		{
			-0x239e,0,0
		},
		GF_CAMERA_ORTHO,
		0x0281,
		FX32_ONE * 150,
		FX32_ONE * 1735
	},

	{							//	5	�e���K���U���R��
		0x13c805,
		{
			-0x29fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0c01,
		FX32_ONE * 10,
		FX32_ONE * 1008
	},

	{							//	6	�e���K���U���O���1
		0x3628df,
		{
			-0x33fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0481,
		FX32_ONE * 115,
		FX32_ONE * 1221
	},

	{							//	7	�e���K���U���O���2
		0x29aec1,
		{
			-0x29fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 153,
		FX32_ONE * 1031
	},

	{							//	8	�ΎR��
		0x296ec1,
		{
			-0x321d,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0701,
		FX32_ONE * 150,
		FX32_ONE * 1034
	},

	{							//	9	��W��
		0x1659ac,
		{
			-0x1cdd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0ab0,
		FX32_ONE * 150,
		FX32_ONE * 900
	},

	{							//	10	�i���W��
		0x4b25b1,
		{
			-0x2b3d,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0341,
		FX32_ONE * 150,
		FX32_ONE * 1746
	},

	{							//	11	�i�M�T�V�e�B/223�Ԑ���/�`�����s�I�����[�O
		0x2a3d55,
		{
			-0x291d,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 230,
		FX32_ONE * 1127
	},

	{							//	12	���A
		0x23e93f,
		{
			-0x2cfd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x06c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},

	{							//	13	�z�R
		0x20374c,
		{
			-0x21fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0770,
		FX32_ONE * 150,
		FX32_ONE * 900
	},

	{							//	14	�͂��܂�̂�
		0xa9765,
		{
			-0x37bc,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x1501,
		FX32_ONE * 10,
		FX32_ONE * 1008
	},

	{							//	15	�G�C�`�ΐ�p�J����
		0x28dedf,
		{
			-0x26de,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x5f0,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
};



//==============================================================================
/**
 * �t�B�[���h��ōs���J�����ݒ�
 *
 * @param   Hero			��ɃG���A�؂�ւ����ɑΉ������J�������ݒ肳���
 * @param	repw			�t�B�[���h�V�X�e���|�C���^
 * @param   AreaCamera		��ɃG���A�؂�ւ����ɑΉ������J�������ݒ肳���
 * @param	inDelayFlg		�����x�����s�����ǂ����̃t���O
 *
 * @retval  none		
 */
//==============================================================================
void FieldCameraInit(	const VecFx32 *inTarget,
						FIELDSYS_WORK * repw,
						const int AreaCamera,
						const BOOL inDelayFlg)
{

	//�J�����Z�b�g
	const VecFx32 *target = inTarget;
	const FLD_CAMERA_PARAM * camera_param = &FieldCameraData[AreaCamera];

	GF_ASSERT(AreaCamera < NELEMS(FieldCameraData));

	repw->camera_ptr = GFC_AllocCamera(HEAPID_FIELD);//�t�B�[���h�J�����������m��
	
	//�J�����Z�b�g
	GFC_InitCameraTDA( target,
				camera_param->Distance,	// ����
				&camera_param->Angle,	//
				camera_param->PerspWay,	// ���ˉe�̊p�x
				camera_param->View,
				TRUE,
				repw->camera_ptr
				);
	//�J�����̗L����
	GFC_AttachCamera(repw->camera_ptr);
	//�j�A�E�t�@�[�ݒ�
	GFC_SetCameraClip(camera_param->Near, camera_param->Far,repw->camera_ptr);
	
	if (inDelayFlg){
		//�J�����g���[�X�f�[�^�Z�b�g�A�b�v
		GFC_AllocTraceData(	FIELD_CAMERA_TRACE_BUFF, FIELD_CAMERA_DELAY,
							CAM_TRACE_MASK_Y, HEAPID_FIELD, repw->camera_ptr);
	}
}

//==============================================================================
/**
 * �t�B�[���h��J�����̉��
 *
 * @param   repw		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void FieldCameraEnd(FIELDSYS_WORK * repw)
{
	GFC_PurgeCamera();						//�J�����̐؂藣���i�������j
		
	GFC_FreeTraceData(repw->camera_ptr);	//�J�����g���[�X�f�[�^���
	GFC_FreeCamera(repw->camera_ptr);		//�t�B�[���h�J�������������
}
