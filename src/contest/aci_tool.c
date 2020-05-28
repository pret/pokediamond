//==============================================================================
/**
 * @file	aci_tool.c
 * @brief	actin_input.c�Ŏg�p����c�[��(actin_input.c�̃V�X�e���Ɉˑ����Ȃ����̌���)
 * @author	matsuda
 * @date	2005.12.02(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "con_tool.h"
#include "actin_id.h"
#include "aci_tool.h"



//==============================================================================
//	�A�N�^�[�w�b�_
//==============================================================================
///�R���n�[�g�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S SubHeartJudgeObjParam = {
	SUB_HEART_JUDGE_POS_X, SUB_HEART_JUDGE_POS_Y, 0,		//x, y, z
	0, ACTINSUB_SOFTPRI_HEART_JUDGE, PALOFS_SUB_HEART_32,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_SUB_HEART_32,	//�L����
		PLTTID_OBJ_COMMON_SUB,	//�p���b�g
		CELLID_SUB_HEART_32,	//�Z��
		CELLANMID_SUB_HEART_32,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTINSUB_BGPRI_HEART_JUDGE,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///AP�l�n�[�g�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S AppHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTINSUB_SOFTPRI_APP_HEART, PALOFS_SUB_HEART_8,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_SUB_HEART_8,	//�L����
		PLTTID_OBJ_COMMON_SUB,	//�p���b�g
		CELLID_SUB_HEART_8,	//�Z��
		CELLANMID_SUB_HEART_8,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTINSUB_BGPRI_APP_HEART,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�W�Q�l�n�[�g�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S ObstructHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTINSUB_SOFTPRI_APP_HEART, PALOFS_SUB_HEART_BLACK_8,	//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_SUB_HEART_8,	//�L����
		PLTTID_OBJ_COMMON_SUB,	//�p���b�g
		CELLID_SUB_HEART_8,	//�Z��
		CELLANMID_SUB_HEART_8,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	ACTINSUB_BGPRI_APP_HEART,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};




//--------------------------------------------------------------
/**
 * @brief   �R���n�[�g�̃��\�[�X�o�^
 *
 * @param   csp			
 * @param   crp			
 * @param   judge_no	�R��NO
 *
 * @retval  ���������A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ACIT_SubHeartJudgeResourceSet(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//���\�[�X���[�h
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART32_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, CHARID_SUB_HEART_32);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART32_NCER_BIN, 1, 
		CELLID_SUB_HEART_32);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART32_NANR_BIN,
		1, CELLANMID_SUB_HEART_32);
}

//--------------------------------------------------------------
/**
 * @brief   �R���n�[�g�̃A�N�^�[�o�^
 *
 * @param   csp			
 * @param   crp			
 * @param   judge_no	�R��NO
 *
 * @retval  ���������A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
CATS_ACT_PTR ACIT_SubHeartJudgeActorAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, int judge_no)
{
	CATS_ACT_PTR sub_heart_judge_cap;
	
	//�A�N�^�[����
	sub_heart_judge_cap = CATS_ObjectAdd_S(csp, crp, &SubHeartJudgeObjParam);
	CATS_ObjectPosSetCap_SubSurface(sub_heart_judge_cap, 
		SUB_HEART_JUDGE_POS_X + SUB_HEART_JUDGE_POS_X_SPACE * judge_no, 
		SUB_HEART_JUDGE_POS_Y + SUB_HEART_JUDGE_POS_Y_SPACE * judge_no,
		ACTIN_SUB_ACTOR_DISTANCE);
	CATS_ObjectUpdate(sub_heart_judge_cap->act);
	return sub_heart_judge_cap;
}

//--------------------------------------------------------------
/**
 * @brief   �R���n�[�g�̃��\�[�X���폜����
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void ACIT_SubHeartJudgeResourceFree(CATS_RES_PTR crp)
{
	CATS_FreeResourceChar(crp, CHARID_SUB_HEART_32);
	CATS_FreeResourceCell(crp, CELLID_SUB_HEART_32);
	CATS_FreeResourceCellAnm(crp, CELLANMID_SUB_HEART_32);
}

//--------------------------------------------------------------
/**
 * @brief   �R���n�[�g�̃A�N�^�[���폜����(���\�[�X���A�N�^�[)
 *
 * @param   sub_heart_judge_cap		�R���A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ACIT_SubHeartJudgeActorDel(CATS_ACT_PTR sub_heart_judge_cap)
{
	CATS_ActorPointerDelete_S(sub_heart_judge_cap);
}

//--------------------------------------------------------------
/**
 * @brief   AP�l�n�[�g�̃��\�[�X�����[�h����
 *
 * @param   csp			
 * @param   crp			
 */
//--------------------------------------------------------------
void ACIT_AppHeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//���\�[�X���[�h
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART8_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, CHARID_SUB_HEART_8);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART8_NCER_BIN, 1, 
		CELLID_SUB_HEART_8);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART8_NANR_BIN,
		1, CELLANMID_SUB_HEART_8);
}

//--------------------------------------------------------------
/**
 * @brief   AP�l�n�[�g�A�N�^�[�𐶐�����
 *
 * @param   csp		
 * @param   crp		
 * @param   x			���WX
 * @param   y			���WY
 * @param   ap_point	AP�l
 *
 * @retval  ���������A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
CATS_ACT_PTR ACIT_AppHeartActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int x, int y, int ap_point)
{
	CATS_ACT_PTR heart_cap;

	//�A�N�^�[����
	if(ap_point >= 0){
		heart_cap = CATS_ObjectAdd_S(csp, crp, &AppHeartObjParam);
	}
	else{
		heart_cap = CATS_ObjectAdd_S(csp, crp, &ObstructHeartObjParam);
	}
	CATS_ObjectPosSetCap_SubSurface(heart_cap, x, y, ACTIN_SUB_ACTOR_DISTANCE);
	CATS_ObjectUpdate(heart_cap->act);
	return heart_cap;
}

//--------------------------------------------------------------
/**
 * @brief   AP�l�n�[�g�A�N�^�[���폜����
 * @param   heart_cap		AP�l�n�[�g�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ACIT_AppHeartActorDel(CATS_ACT_PTR heart_cap)
{
	CATS_ActorPointerDelete_S(heart_cap);
}

//--------------------------------------------------------------
/**
 * @brief   AP�l�n�[�g�̃��\�[�X���������
 * @param   crp		
 */
//--------------------------------------------------------------
void ACIT_AppHeartResourceFree(CATS_RES_PTR crp)
{
	CATS_FreeResourceChar(crp, CHARID_SUB_HEART_8);
	CATS_FreeResourceCell(crp, CELLID_SUB_HEART_8);
	CATS_FreeResourceCellAnm(crp, CELLANMID_SUB_HEART_8);
}
