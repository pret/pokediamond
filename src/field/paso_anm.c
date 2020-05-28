//=============================================================================
/**
 * @file	paso_anm.c
 * @bfief	�p�\�R���A�j��
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_3d_anime.h"

#include "fielddata/build_model/build_model_id.h"

#include "paso_anm_def.h"

#include "paso_anm.h"

//==============================================================================
/**
 * �p�\�R���A�j���[�V�����̃Z�b�g�A�b�v
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inEntryID	�o�^�h�c
 *
 * @retval  none
 */
//=============================================================================
void FLD_SCR_ANM_PASO_Setup( FIELDSYS_WORK * fsys, const u8 inEntryID )
{
	BOOL rc;
	M3DO_PTR obj_ptr;
	TARGET_RECT rect;
	int obj_id;
	int list[] = {	BMID_PC01,BMID_TABLE_L01,BMID_TABLE_L02,BMID_TABLE_L03};

	rc = MPTL_CheckPluralMap3DObj(	fsys,
									list,
									4,//<<����`���߂łƂ܂�̂Œ��l�����Ă���
									&obj_ptr,
									&obj_id);
	if (rc){
		NNSG3dResTex *tex;
		tex = GetMapResourceBmTexturePTR(fsys->MapResource);
		F3DASub_SetUpAnimation(	fsys->field_3d_anime,
								fsys->AnimeContMng,
								inEntryID,
								obj_id,
								M3DO_GetRenderObj(obj_ptr),
								M3DO_GetObjModel(obj_ptr),
								tex,2,
								1,		//���[�v1��
								FALSE);
	}else{
		GF_ASSERT_MSG(0,"�p�\�R������܂���");
	}
}

//==============================================================================
/**
 * �p�\�R���A�j���[�V�����i�p�\�R���N���j
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inEntryID	�o�^�h�c
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_PASO_PasoOnAnm( FIELDSYS_WORK * fsys, const u8 inEntryID )
{
	F3DASub_StartAnimation(fsys->AnimeContMng, inEntryID, PASO_ON);	//�p�\�R���N���A�j��
}

//==============================================================================
/**
 * �p�\�R���A�j���[�V�����i�p�\�R���I���j
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inEntryID	�o�^�h�c
 *
 * @retval  none
 */
//==============================================================================
void FLD_SCR_ANM_PASO_PasoOffAnm( FIELDSYS_WORK * fsys, const u8 inEntryID )
{
	F3DASub_StartAnimation(fsys->AnimeContMng, inEntryID, PASO_OFF);	//�p�\�R���I���A�j��
}
