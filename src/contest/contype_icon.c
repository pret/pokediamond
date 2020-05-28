//==============================================================================
/**
 * @file	contype_icon.c
 * @brief	�R���e�X�g�^�C�v�A�C�R��
 * @author	matsuda
 * @date	2005.12.02(��)
 */
//==============================================================================
#include "common.h"
#include "system/clact_tool.h"
#include "contype_icon.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "contest/graphic/contest_obj_def.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�R���e�X�g�^�C�v�A�C�R���Ŏg�p����p���b�g�{��
#define CTI_PLTT_NUM		(2)


//==============================================================================
//	�f�[�^
//==============================================================================
///�R���e�X�g�^�C�v����CGRID
ALIGN4 static const u32 ConTypeCgrNo[] = {
	CTYPE_STYLE_NCGR_BIN,			//CONTYPE_STYLE
	CTYPE_BEAUTIFUL_NCGR_BIN,		//CONTYPE_BEAUTIFUL
	CTYPE_CUTE_NCGR_BIN,			//CONTYPE_CUTE
	CTYPE_CLEVER_NCGR_BIN,			//CONTYPE_CLEVER
	CTYPE_STRONG_NCGR_BIN, 		//CONTYPE_STRONG
};

///�R���e�X�g�^�C�v���̃p���b�g�I�t�Z�b�g�ԍ�
ALIGN4 static const u8 ConTypePlttOffset[] = {
	1,		//CONTYPE_STYLE
	1,		//CONTYPE_BEAUTIFUL
	1,		//CONTYPE_CUTE
	1,		//CONTYPE_CLEVER
	1,		//CONTYPE_STRONG
};



//==============================================================================
//
//	�R���e�X�g�^�C�v�A�C�R��
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �w��R���e�X�g�^�C�v��CGRID���擾���܂�
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 * @retval  CGRID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_CgrIDGet(int con_type)
{
	GF_ASSERT(con_type < NELEMS(ConTypeCgrNo));
	return ConTypeCgrNo[con_type];
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃p���b�gID���擾���܂�
 * @retval  �p���b�gID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_PlttIDGet(void)
{
	return CONTEST_SUB_OBJ_NCLR;
}

//--------------------------------------------------------------
/**
 * @brief   �w��R���e�X�g�^�C�v�̃Z��ID���擾���܂�
 * @retval  �Z��ID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_CellIDGet(void)
{
	return CTYPE_STYLE_NCER_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   �w��R���e�X�g�^�C�v�̃Z���A�j��ID���擾���܂�
 * @retval  �Z���A�j��ID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 ConTypeIcon_CellAnmIDGet(void)
{
	return CTYPE_STYLE_NANR_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   �w��R���e�X�g�^�C�v�̃p���b�g�ԍ��I�t�Z�b�g���擾���܂�
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 * @retval  �p���b�g�ԍ��̃I�t�Z�b�g
 */
//--------------------------------------------------------------
u8 ConTypeIcon_PlttOffsetGet(int con_type)
{
	GF_ASSERT(con_type < NELEMS(ConTypePlttOffset));
	return ConTypePlttOffset[con_type];
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃A�[�J�C�uINDEX���擾���܂�
 * @retval  �A�[�J�C�uINDEX
 */
//--------------------------------------------------------------
u32 ConTypeIcon_ArcIDGet(void)
{
	return ARC_CONTEST_OBJ;
}




//--------------------------------------------------------------
/**
 * @brief   �w��R���e�X�g�^�C�v�̃L�������\�[�X�����[�h���܂�
 *
 * @param   csp				csp�ւ̃|�C���^
 * @param   crp				crp�ւ̃|�C���^
 * @param   vram_type		NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 * @param   char_id			�o�^����L����ID
 */
//--------------------------------------------------------------
void ConTypeIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int con_type, u32 char_id)
{
	CATS_LoadResourceCharArc(csp, crp, ConTypeIcon_ArcIDGet(), 
		ConTypeIcon_CgrIDGet(con_type), 1, vram_type, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃p���b�g�����[�h���܂�
 *
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   pltt_id		�o�^����p���b�gID
 *
 * �R���e�X�g�^�C�v�A�C�R���Ŏg�p����p���b�g�S�Ă��Z�b�g���܂��B
 */
//--------------------------------------------------------------
void ConTypeIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttArc(csp, crp, ConTypeIcon_ArcIDGet(), ConTypeIcon_PlttIDGet(), 1, 
		CTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃p���b�g���p���b�g���[�N�փ��[�h���܂�
 *
 * @param   PALETTE_FADE_PTR		�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req						���N�G�X�g�f�[�^�ԍ�(FADE_MAIN_BG��)
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   pltt_id		�o�^����p���b�gID
 *
 * �R���e�X�g�^�C�v�A�C�R���Ŏg�p����p���b�g�S�Ă��Z�b�g���܂��B
 */
//--------------------------------------------------------------
void ConTypeIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, req, csp, crp, 
		ConTypeIcon_ArcIDGet(), ConTypeIcon_PlttIDGet(), 0, 
		CTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃Z���ƃA�j�������[�h���܂�
 *
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   cell_id		�o�^����Z��ID
 * @param   anm_id		�o�^����A�j��ID
 *
 * �R���e�X�g�^�C�v�A�C�R�����ʂ̃Z���ƃA�j�������[�h���܂��B
 * �R���e�X�g�^�C�v�A�C�R���͑S�ăZ���ƃA�j�������ʂȂ̂ŁA1�����o�^���Ă�����OK�ł��B
 * (�����̃A�C�R���𐶐����鎞�ł��A�S�Ă����œo�^�����Z���A�A�j��ID���w�肷��悤�ɂ��܂�)
 */
//--------------------------------------------------------------
void ConTypeIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourceCellArc(csp, crp, ConTypeIcon_ArcIDGet(), ConTypeIcon_CellIDGet(), 
		1, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, ConTypeIcon_ArcIDGet(), ConTypeIcon_CellAnmIDGet(), 
		1, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃L�������\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   char_id		�������L����ID
 */
//--------------------------------------------------------------
void ConTypeIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id)
{
	CATS_FreeResourceChar(crp, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃p���b�g���\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   pltt_id		�������p���b�gID
 */
//--------------------------------------------------------------
void ConTypeIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id)
{
	CATS_FreeResourcePltt(crp, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���̃Z���A�A�j�����\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   char_id		�������Z��ID
 * @param   char_id		�������A�j��ID
 */
//--------------------------------------------------------------
void ConTypeIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}


//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���A�N�^�[�𐶐�����
 *
 * @param   csp				csp�ւ̃|�C���^
 * @param   crp				crp�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 * @param   obj_data		�A�N�^�[�w�b�_�ւ̃|�C���^
 *
 * @retval  ���������A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------
CATS_ACT_PTR ConTypeIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int con_type, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	obj_param = *obj_data;
	obj_param.pal = ConTypeIcon_PlttOffsetGet(con_type);
	
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R���A�N�^�[���폜
 * @param   cap		�A�N�^�[�|�C���^
 */
//--------------------------------------------------------------
void ConTypeIcon_ActorDelete(CATS_ACT_PTR cap)
{
	CATS_ActorPointerDelete_S(cap);
}


