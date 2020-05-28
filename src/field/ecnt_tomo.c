//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		ecnt_tomo.c
 *@brief	����G���J�E���g
 *@author	tomoya takahashi
 *@data		2005.07.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "field_event.h"
#include "fld_motion_bl.h"
#include "encount_effect_def.h"
#include "system/wipe.h"

#define	__ECNT_TOMO_H_GLOBAL
#include "ecnt_tomo.h"
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	���[�V�����u���[�p
//=====================================
#define MSBL00_ROTA_START	(64)		// ��]�������x
#define	MSBL00_ROTA_ADD		(48)		// ��]�����x
#define MSBL00_ROTA_COUNT	(40)		// ��]���Ă��鎞��
#define MSBL00_MSBLFADE_COUNT	(16)	// ���[�V�����u���[�W���ɂ�蔒�����Ă���
#define MSBL00_DIST_START	(FX32_ONE)				// �߂Â��������x
#define MSBL00_DIST_ADD		(FX32_CONST(0.90f))		// �����l
#define	MSBL00_CAMERA_IN_TIMING		(20)			// �J�������߂Â��͂��߂�^�C�~���O
#define MSBL00_FADEOUT_DIV			( 8 )
#define MSBL00_FADEOUT_SYNC			( 1 )
enum{
	MSBL00_START_EFFECT,	// �G�t�F�N�g�X�^�[�g
	MSBL00_FLASH_INIT,		// �ŏ��̃s�J�s�J�J�n
	MSBL00_FLASH_WAIT,		// �ŏ��̃s�J�s�J�I���҂�
	MSBL00_MOTION_INIT,		// ���[�V�����u���[����
	MSBL00_CAMERA_ROTA,		// �J������]
	MSBL00_FADE_OUT,		// �t�F�[�h�A�E�g
	MSBL00_END_WAIT,		// �I���܂ő҂�
	MSBL00_END_EFFECT		// �I��
};

//-------------------------------------
//	���[�V�����u���[01�p
//=====================================
enum{
	MSBL01_START_EFFECT,	// �G�t�F�N�g�X�^�[�g
	MSBL01_FLASH_INIT,		// �ŏ��̃s�J�s�J�J�n
	MSBL01_FLASH_WAIT,		// �ŏ��̃s�J�s�J�I���҂�
	MSBL01_MOTION_INIT,		// ���[�V�����u���[����
	MSBL01_MOTION,			// �J�����𓮂���
	MSBL01_FADE_OUT,		// �u���b�N�t�F�[�h�A�E�g
	MSBL01_END_WAIT,		// �I���܂ő҂�
	MSBL01_END_EFFECT		// �I��
};

#define MSBL01_CAMERA_SHIFT_INIT	(FX32_CONST(1.0f))	// �J�����V�t�g�̍ŏ��̋���
#define MSBL01_CAMERA_SHIFT_ADD		(FX32_CONST(24.0f))	//�J�����V�t�g�̉����l
#define MSBL01_CAMERA_COUNT_ADD		(8192)
#define MSBL01_END_COUNT			(40)
#define MSBL01_FADEOUT_DIV			( 8 )
#define MSBL01_FADEOUT_SYNC			( 1 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------


//-------------------------------------
//	���[�V�����u���[�\����
//=====================================
typedef struct{
	FLD_MOTION_BL_DATA_PTR	motion;
	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	u16				camera_rota;		// �J������]�p
	u16				camera_rota_add;	// ���̉�]���x
	fx32			camera_dist;		// �J��������
	fx32			camera_dist_add;	// �J���������̂����Â����x
	int				count;				// �����������ł̃J�E���^

	/* OBJ */
} MSBL00_WORK;

//-------------------------------------
//
//	���[�V�����u���[01�\����
//
//=====================================
typedef struct{
	FLD_MOTION_BL_DATA_PTR	motion;

	GF_CAMERA_PTR	camera;				// �J�����f�[�^
	VecFx32			camera_shift;		// �J�����V�t�g����
	fx32			camera_mv;			// �J�����ړ����x
	int				camera_count;		// �J�����G�t�F�N�g�p�J�E���^
	int				count;				// �e�������ł̃J�E���^
	
	/* OBJ */
} MSBL01_WORK;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�V�����u���[��]�G���J�E���g
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	*work	���[�N�|�C���^
 *
 *@return	none
 *
 * �G�t�F�N�g�̗���
 *
 * 1:�T�u��ʃu���b�N�A�E�g
 * 2:���C����ʂɃ��[�V�����u���[��������
 * 3:�J�����̏��������]������
 * 4:�ǂ�ǂ񑁂��Ȃ�
 * 5:�傫�ȃ����X�^�[�{�[��BG���o���B�i�P�T�t���[���j
 * 
 *
 */
//-----------------------------------------------------------------------------
void EncountEffectMotionBl00(TCB_PTR tcb, void *work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	MSBL00_WORK* task_w = eew->work;
	int add_num;

	switch(eew->seq){
	case MSBL00_START_EFFECT:	// ����������
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(MSBL00_WORK));
		memset( eew->work, 0, sizeof(MSBL00_WORK) );
		
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_OFF);
		
		eew->seq++;
		break;
		
	case MSBL00_FLASH_INIT:		// �ŏ��̃s�J�s�J�\��
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);

		eew->seq++;
		break;

	case MSBL00_FLASH_WAIT:
		if(eew->wait){
			eew->wait = 0;

			eew->seq++;
		}
		break;

	case MSBL00_MOTION_INIT:	// ���[�V�����u���[���g�p���鏀��
		task_w->motion = FLDMotionBl_Init(4, 15);
		

		// �J������]�̏���
		task_w->camera				= GFC_AllocCamera(HEAPID_FIELD);		// �J�����쐬
		GFC_CopyCamera(eew->fsw->camera_ptr, task_w->camera);	// �J�����R�s�[
		GFC_AttachCamera(task_w->camera);
		task_w->camera_rota_add		= MSBL00_ROTA_START;
		task_w->count				= MSBL00_ROTA_COUNT;
		task_w->camera_dist			= GFC_GetCameraDistance(task_w->camera);
		task_w->camera_dist_add		= MSBL00_DIST_START;
		eew->seq++;
		break;
		
	case MSBL00_CAMERA_ROTA:	// �J������]

		// ��]�p�ɑ����l��␳����i���̃J�����̊p�x�ł������܂������Ȃ��̂Œ��ӁI�I�j
		// �������ȕ␳�Ȃ̂ŁA�J�����̊p�x�ŁA��蒼���K�v����I�I
		add_num = FX_Mul(FX_SinIdx(task_w->camera_rota), (task_w->camera_rota_add*4)<<FX32_SHIFT) >> FX32_SHIFT;
		if(add_num < 0){		// �}�C�i�X���v���X�ɂ���
			add_num *= -1;
		}

		// �␳�l�{�������ޒl�𑫂�
		task_w->camera_rota += add_num + task_w->camera_rota_add;

		// ����������
		task_w->camera_rota_add += MSBL00_ROTA_ADD;
		
		{
			VecFx32	vect;
			vect.x = FX_SinIdx(task_w->camera_rota);
			vect.y = FX_CosIdx(task_w->camera_rota);
			vect.z = 0;
			GFC_SetCamUp(&vect, task_w->camera);
		}

		// �J���������X�ɂ���������
		if(task_w->count <= MSBL00_CAMERA_IN_TIMING){
			task_w->camera_dist -= task_w->camera_dist_add;
			task_w->camera_dist_add += MSBL00_DIST_ADD;
			GFC_SetCameraDistance(task_w->camera_dist, task_w->camera);
		}

		if(task_w->count < MSBL00_MSBLFADE_COUNT){
			FLDMotionBl_ParamChg(task_w->motion, 2, 16);
		}
		
		task_w->count--;
		if(task_w->count < 0){
			FLDMotionBl_ParamChg(task_w->motion, 0, 16);
			eew->seq++;
		}
		break;

	
	
	case MSBL00_FADE_OUT:		// BG�`��
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, MSBL00_FADEOUT_DIV, MSBL00_FADEOUT_SYNC, HEAPID_FIELD );

		eew->seq++;
		break;
		
	
	
	case MSBL00_END_WAIT:
		if( WIPE_SYS_EndCheck() ){
			eew->wait = 0;

			// ���ɖ߂�
			FLDMotionBl_Delete(&task_w->motion);
			GFC_PurgeCamera();				// �J�������蓖�ăt���[
			GFC_AttachCamera(eew->fsw->camera_ptr);
			GFC_FreeCamera(task_w->camera);	// �J�����j��

			// �u���C�g�l�X����
			G2_BlendNone();
			
			eew->seq++;
		}
		break;

	
	case MSBL00_END_EFFECT:		// ��n��
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}	
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�V�����u���[�u���G���J�E���g
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	*work	���[�N�|�C���^
 *
 *@return	none
 *
 * �G�t�F�N�g�̗���
 *
 * 1:���[�V�����u���[��������
 * 2:�J�������Ԃꂳ����
 * 3:�u���b�N�A�E�g
 *
 */
//-----------------------------------------------------------------------------
void EncountEffectMotionBl01(TCB_PTR tcb, void *work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	MSBL01_WORK* task_w = eew->work;
	VecFx32 shift_num;
	VecFx32 set_num;

	switch(eew->seq){
	case MSBL01_START_EFFECT:	// ����������
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(MSBL01_WORK));
		memset( eew->work, 0, sizeof(MSBL01_WORK) );
		
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_OFF);
		
		eew->seq++;
		break;

	case MSBL01_FLASH_INIT:		// �ŏ��̃s�J�s�J�\��
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);

		eew->seq++;
		break;

	case MSBL01_FLASH_WAIT:
		if(eew->wait){
			eew->wait = 0;

			eew->seq++;
		}
		break;


	case MSBL01_MOTION_INIT:	// ���[�V�����u���[���g�p���鏀��
	
		task_w->motion = FLDMotionBl_Init(2, 14);
		
		// �J�����ړ��̏���
		task_w->camera				= GFC_AllocCamera(HEAPID_FIELD);		// �J�����쐬
		GFC_CopyCamera(eew->fsw->camera_ptr, task_w->camera);	// �J�����R�s�[
		GFC_AttachCamera(task_w->camera);
		task_w->camera_mv	= MSBL01_CAMERA_SHIFT_INIT;
		task_w->camera_count= 0;
		task_w->count		= MSBL01_END_COUNT;
		eew->seq++;
		break;
		
		
	case MSBL01_MOTION:	// �J�����ړ�
		
		// �ړ�������
		shift_num.x = FX_SinIdx(task_w->camera_count);
		shift_num.x = FX_Mul(shift_num.x, task_w->camera_mv);
		shift_num.y = 0;
		shift_num.z = 0;

		set_num.x =	shift_num.x - task_w->camera_shift.x;
		set_num.y =	shift_num.y - task_w->camera_shift.y;
		set_num.z =	shift_num.z - task_w->camera_shift.z;
		
		// �ݒ�
		GFC_ShiftCamera(&set_num, task_w->camera);

		// �J�E���g
		task_w->camera_count += MSBL01_CAMERA_COUNT_ADD;
		if(task_w->camera_count >= 0x10000){
			task_w->camera_count = 0;
			task_w->camera_mv += MSBL01_CAMERA_SHIFT_ADD;
		}
		
		// �ړ�������������ۑ��i�Ō�Ɍ��ɖ߂����߁j
		task_w->camera_shift.x = shift_num.x;
		task_w->camera_shift.y = shift_num.y;
		task_w->camera_shift.z = shift_num.z;
		
		
		task_w->count--;
		if(task_w->count < 0){
			eew->seq++;
		}
		break;

	
	
	case MSBL01_FADE_OUT:		// �t�F�[�h�A�E�g
		//BG�ʂ����ɃJ�b�g
		ENC_BG_Cut_Start( eew );
		
		//�u���b�N�A�E�g
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, MSBL01_FADEOUT_DIV, MSBL01_FADEOUT_SYNC, HEAPID_FIELD );
		eew->seq++;
		break;
		
	
	
	case MSBL01_END_WAIT:
		if((ENC_HBlankEndCheck(eew) == TRUE) && ( WIPE_SYS_EndCheck() == TRUE )){
			// ���ɖ߂�
			FLDMotionBl_Delete(&task_w->motion);
			GFC_PurgeCamera();				// �J�������蓖�ăt���[
			GFC_AttachCamera(eew->fsw->camera_ptr);
			GFC_FreeCamera(task_w->camera);	// �J�����j��

			// �u���C�g�l�X����
			G2_BlendNone();
			
			eew->seq++;
		}
		break;

	
	case MSBL01_END_EFFECT:		// ��n��
		
		G2_SetBG0Offset(0, 0);
		G2_SetBG1Offset(0, 0);
		G2_SetBG2Offset(0, 0);
		G2_SetBG3Offset(0, 0);
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// �^�X�N�I�����
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//�^�X�N�I��
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}	
}
