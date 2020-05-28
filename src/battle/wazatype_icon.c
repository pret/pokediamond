//==============================================================================
/**
 * @file	wazatype_icon.c
 * @brief	�Z�^�C�v�����ރA�C�R��
 * @author	matsuda
 * @date	2005.10.26(��)
 */
//==============================================================================
#include "common.h"
#include "system/clact_tool.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "battle\graphic\batt_obj_def.h"
#include "battle/battle_common.h"
#include "battle/wazatype_icon.h"


//==============================================================================
//	�f�[�^
//==============================================================================
//--------------------------------------------------------------
//	�Z�^�C�v
//--------------------------------------------------------------
///�Z�^�C�v����CGRID
ALIGN4 static const u32 WazaTypeCgrNo[] = {
	P_ST_TYPE_NORMAL_NCGR_BIN,
	P_ST_TYPE_FIGHT_NCGR_BIN,
	P_ST_TYPE_FLIGHT_NCGR_BIN,
	P_ST_TYPE_POISON_NCGR_BIN,
	P_ST_TYPE_GROUND_NCGR_BIN,
	P_ST_TYPE_ROCK_NCGR_BIN,
	P_ST_TYPE_INSECT_NCGR_BIN,
	P_ST_TYPE_GHOST_NCGR_BIN,
	P_ST_TYPE_STEEL_NCGR_BIN,
	P_ST_TYPE_QUES_NCGR_BIN,
	P_ST_TYPE_FIRE_NCGR_BIN,
	P_ST_TYPE_WATER_NCGR_BIN,
	P_ST_TYPE_GRASS_NCGR_BIN,
	P_ST_TYPE_ELE_NCGR_BIN,
	P_ST_TYPE_ESP_NCGR_BIN,
	P_ST_TYPE_ICE_NCGR_BIN,
	P_ST_TYPE_DRAGON_NCGR_BIN,
	P_ST_TYPE_EVIL_NCGR_BIN,
	P_ST_TYPE_STYLE_NCGR_BIN,
	P_ST_TYPE_BEAUTIFUL_NCGR_BIN,
	P_ST_TYPE_CUTE_NCGR_BIN,
	P_ST_TYPE_INTELLI_NCGR_BIN,
	P_ST_TYPE_STRONG_NCGR_BIN,
};

///�Z�^�C�v���̃p���b�g�I�t�Z�b�g�ԍ�
ALIGN4 static const u8 WazaTypePlttOffset[] = {
	0,	//NORMAL_TYPE
	0,	//BATTLE_TYPE
	1,	//HIKOU_TYPE
	1,	//POISON_TYPE
	0,	//JIMEN_TYPE
	0,	//IWA_TYPE
	2,	//MUSHI_TYPE
	1,	//GHOST_TYPE
	0,	//METAL_TYPE
	2,	//HATE_TYPE
	0,	//FIRE_TYPE
	1,	//WATER_TYPE
	2,	//KUSA_TYPE
	0,	//ELECTRIC_TYPE
	1,	//SP_TYPE
	1,	//KOORI_TYPE
	2,	//DRAGON_TYPE
	0,	//AKU_TYPE
	0,	//ICONTYPE_STYLE
	1,	//ICONTYPE_BEAUTIFUL
	1,	//ICONTYPE_CUTE
	2,	//ICONTYPE_INTELLI
	0,	//ICONTYPE_STRONG
};

//--------------------------------------------------------------
//	����
//--------------------------------------------------------------
///���ޖ���CGRID
ALIGN4 static const u32 WazaKindCgrNo[] = {
	P_ST_BUNRUI_BUTURI_NCGR_BIN,
	P_ST_BUNRUI_TOKUSYU_NCGR_BIN,
	P_ST_BUNRUI_HENKA_NCGR_BIN,
};

///���ޖ��̃p���b�g�I�t�Z�b�g�ԍ�
ALIGN4 static const u8 WazaKindPlttOffset[] = {
	0,		//KIND_BUTSURI
	1,		//KIND_TOKUSYU
	0,		//KIND_HENNKA
};



//==============================================================================
//
//	�Z�^�C�v�A�C�R��
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �w��Z�^�C�v��CGRID���擾���܂�
 * @param   waza_type		�Z�^�C�v(NORMAL_TYPE, FIRE_TYPE..���A���� ICONTYPE_???)
 * @retval  CGRID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_CgrIDGet(int waza_type)
{
	GF_ASSERT(waza_type < NELEMS(WazaTypeCgrNo));
	return WazaTypeCgrNo[waza_type];
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃p���b�gID���擾���܂�
 * @retval  �p���b�gID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_PlttIDGet(void)
{
	return ST_TYPE_NCLR;
}

//--------------------------------------------------------------
/**
 * @brief   �w��Z�^�C�v�̃Z��ID���擾���܂�
 * @retval  �Z��ID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_CellIDGet(void)
{
	return P_ST_TYPE_NORMAL_NCER_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   �w��Z�^�C�v�̃Z���A�j��ID���擾���܂�
 * @retval  �Z���A�j��ID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_CellAnmIDGet(void)
{
	return P_ST_TYPE_NORMAL_NANR_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   �w��Z�^�C�v�̃p���b�g�ԍ��I�t�Z�b�g���擾���܂�
 * @param   waza_type		�Z�^�C�v(NORMAL_TYPE, FIRE_TYPE..���A���� ICONTYPE_???)
 * @retval  �p���b�g�ԍ��̃I�t�Z�b�g
 */
//--------------------------------------------------------------
u8 WazaTypeIcon_PlttOffsetGet(int waza_type)
{
	GF_ASSERT(waza_type < NELEMS(WazaTypePlttOffset));
	return WazaTypePlttOffset[waza_type];
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃A�[�J�C�uINDEX���擾���܂�
 * @retval  �A�[�J�C�uINDEX
 */
//--------------------------------------------------------------
u32 WazaTypeIcon_ArcIDGet(void)
{
	return ARC_BATT_OBJ;
}




//--------------------------------------------------------------
/**
 * @brief   �w��Z�^�C�v�̃L�������\�[�X�����[�h���܂�
 *
 * @param   csp				csp�ւ̃|�C���^
 * @param   crp				crp�ւ̃|�C���^
 * @param   vram_type		NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   waza_type		�Z�^�C�v(NORMAL_TYPE, FIRE_TYPE..���A���� ICONTYPE_???)
 * @param   char_id			�o�^����L����ID
 */
//--------------------------------------------------------------
void WazaTypeIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int waza_type, u32 char_id)
{
	CATS_LoadResourceCharArc(csp, crp, WazaTypeIcon_ArcIDGet(), 
		WazaTypeIcon_CgrIDGet(waza_type), WAZATYPEICON_COMP_CHAR, vram_type, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃p���b�g�����[�h���܂�
 *
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   pltt_id		�o�^����p���b�gID
 *
 * �Z�^�C�v�A�C�R���Ŏg�p����p���b�g�S�Ă��Z�b�g���܂��B
 */
//--------------------------------------------------------------
void WazaTypeIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttArc(csp, crp, WazaTypeIcon_ArcIDGet(), WazaTypeIcon_PlttIDGet(), 
		WAZATYPEICON_COMP_PLTT, WTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃p���b�g���p���b�g���[�N�փ��[�h���܂�
 *
 * @param   PALETTE_FADE_PTR		�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req						���N�G�X�g�f�[�^�ԍ�(FADE_MAIN_BG��)
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   pltt_id		�o�^����p���b�gID
 *
 * �Z�^�C�v�A�C�R���Ŏg�p����p���b�g�S�Ă��Z�b�g���܂��B
 */
//--------------------------------------------------------------
void WazaTypeIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, req, csp, crp, 
		WazaTypeIcon_ArcIDGet(), WazaTypeIcon_PlttIDGet(), WAZATYPEICON_COMP_PLTT, 
		WTI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃Z���ƃA�j�������[�h���܂�
 *
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   cell_id		�o�^����Z��ID
 * @param   anm_id		�o�^����A�j��ID
 *
 * �Z�^�C�v�A�C�R�����ʂ̃Z���ƃA�j�������[�h���܂��B
 * �Z�^�C�v�A�C�R���͑S�ăZ���ƃA�j�������ʂȂ̂ŁA1�����o�^���Ă�����OK�ł��B
 * (�����̃A�C�R���𐶐����鎞�ł��A�S�Ă����œo�^�����Z���A�A�j��ID���w�肷��悤�ɂ��܂�)
 */
//--------------------------------------------------------------
void WazaTypeIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourceCellArc(csp, crp, WazaTypeIcon_ArcIDGet(), WazaTypeIcon_CellIDGet(), 
		WAZATYPEICON_COMP_CELL, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, WazaTypeIcon_ArcIDGet(), WazaTypeIcon_CellAnmIDGet(), 
		WAZATYPEICON_COMP_CELLANM, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃L�������\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   char_id		�������L����ID
 */
//--------------------------------------------------------------
void WazaTypeIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id)
{
	CATS_FreeResourceChar(crp, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃p���b�g���\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   pltt_id		�������p���b�gID
 */
//--------------------------------------------------------------
void WazaTypeIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id)
{
	CATS_FreeResourcePltt(crp, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���̃Z���A�A�j�����\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   char_id		�������Z��ID
 * @param   char_id		�������A�j��ID
 */
//--------------------------------------------------------------
void WazaTypeIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}


//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���A�N�^�[�𐶐�����
 *
 * @param   csp				csp�ւ̃|�C���^
 * @param   crp				crp�ւ̃|�C���^
 * @param   waza_type		�Z�^�C�v(NORMAL_TYPE, FIRE_TYPE..���A���� ICONTYPE_???)
 * @param   obj_data		�A�N�^�[�w�b�_�ւ̃|�C���^
 *
 * @retval  ���������A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------
CATS_ACT_PTR WazaTypeIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int waza_type, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	obj_param = *obj_data;
	obj_param.pal = WazaTypeIcon_PlttOffsetGet(waza_type);
	
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R���A�N�^�[���폜
 * @param   cap		�A�N�^�[�|�C���^
 */
//--------------------------------------------------------------
void WazaTypeIcon_ActorDelete(CATS_ACT_PTR cap)
{
	CATS_ActorPointerDelete_S(cap);
}










//==============================================================================
//
//	���ރA�C�R��
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �w��Z���ނ�CGRID���擾���܂�
 * @param   waza_kind		�Z����(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @retval  CGRID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_CgrIDGet(int waza_kind)
{
	GF_ASSERT(waza_kind < NELEMS(WazaKindCgrNo));
	return WazaKindCgrNo[waza_kind];
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃p���b�gID���擾���܂�
 * @retval  �p���b�gID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_PlttIDGet(void)
{
	return ST_TYPE_NCLR;
}

//--------------------------------------------------------------
/**
 * @brief   �w��Z���ނ̃Z��ID���擾���܂�
 * @retval  �Z��ID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_CellIDGet(void)
{
	return P_ST_TYPE_NORMAL_NCER_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   �w��Z���ނ̃Z���A�j��ID���擾���܂�
 * @retval  �Z���A�j��ID(ARC�̃f�[�^INDEX)
 */
//--------------------------------------------------------------
u32 WazaKindIcon_CellAnmIDGet(void)
{
	return P_ST_TYPE_NORMAL_NANR_BIN;
}

//--------------------------------------------------------------
/**
 * @brief   �w��Z���ނ̃p���b�g�ԍ��I�t�Z�b�g���擾���܂�
 * @param   waza_kind		�Z����(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @retval  �p���b�g�ԍ��̃I�t�Z�b�g
 */
//--------------------------------------------------------------
u8 WazaKindIcon_PlttOffsetGet(int waza_kind)
{
	GF_ASSERT(waza_kind < NELEMS(WazaKindPlttOffset));
	return WazaKindPlttOffset[waza_kind];
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃A�[�J�C�uINDEX���擾���܂�
 * @retval  �A�[�J�C�uINDEX
 */
//--------------------------------------------------------------
u32 WazaKindIcon_ArcIDGet(void)
{
	return ARC_BATT_OBJ;
}




//--------------------------------------------------------------
/**
 * @brief   �w��Z���ނ̃L�������\�[�X�����[�h���܂�
 *
 * @param   csp				csp�ւ̃|�C���^
 * @param   crp				crp�ւ̃|�C���^
 * @param   vram_type		NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   waza_kind		�Z����(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @param   char_id			�o�^����L����ID
 */
//--------------------------------------------------------------
void WazaKindIcon_CharResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, int waza_kind, u32 char_id)
{
	CATS_LoadResourceCharArc(csp, crp, WazaKindIcon_ArcIDGet(), 
		WazaKindIcon_CgrIDGet(waza_kind), WAZAKINDICON_COMP_CHAR, vram_type, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃p���b�g�����[�h���܂�
 *
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   pltt_id		�o�^����p���b�gID
 *
 * �Z���ރA�C�R���Ŏg�p����p���b�g�S�Ă��Z�b�g���܂��B
 */
//--------------------------------------------------------------
void WazaKindIcon_PlttResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttArc(csp, crp, WazaKindIcon_ArcIDGet(), WazaKindIcon_PlttIDGet(), 
		WAZAKINDICON_COMP_PLTT, WKI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃p���b�g���p���b�g���[�N�փ��[�h���܂�
 *
 * @param   PALETTE_FADE_PTR		�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req						���N�G�X�g�f�[�^�ԍ�(FADE_MAIN_BG��)
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   vram_type	NNS_G2D_VRAM_TYPE_2DMAIN��
 * @param   pltt_id		�o�^����p���b�gID
 *
 * �Z���ރA�C�R���Ŏg�p����p���b�g�S�Ă��Z�b�g���܂��B
 */
//--------------------------------------------------------------
void WazaKindIcon_PlttWorkResourceLoad(PALETTE_FADE_PTR pfd, FADEREQ req, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, NNS_G2D_VRAM_TYPE vram_type, u32 pltt_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, req, csp, crp, 
		WazaKindIcon_ArcIDGet(), WazaKindIcon_PlttIDGet(), WAZAKINDICON_COMP_PLTT, 
		WKI_PLTT_NUM, vram_type, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃Z���ƃA�j�������[�h���܂�
 *
 * @param   csp			csp�ւ̃|�C���^
 * @param   crp			crp�ւ̃|�C���^
 * @param   cell_id		�o�^����Z��ID
 * @param   anm_id		�o�^����A�j��ID
 *
 * �Z���ރA�C�R�����ʂ̃Z���ƃA�j�������[�h���܂��B
 * �Z���ރA�C�R���͑S�ăZ���ƃA�j�������ʂȂ̂ŁA1�����o�^���Ă�����OK�ł��B
 * (�����̃A�C�R���𐶐����鎞�ł��A�S�Ă����œo�^�����Z���A�A�j��ID���w�肷��悤�ɂ��܂�)
 */
//--------------------------------------------------------------
void WazaKindIcon_CellAnmResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourceCellArc(csp, crp, WazaKindIcon_ArcIDGet(), WazaKindIcon_CellIDGet(), 
		WAZAKINDICON_COMP_CELL, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, WazaKindIcon_ArcIDGet(), WazaKindIcon_CellAnmIDGet(), 
		WAZAKINDICON_COMP_CELLANM, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃L�������\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   char_id		�������L����ID
 */
//--------------------------------------------------------------
void WazaKindIcon_CharResourceFree(CATS_RES_PTR crp, u32 char_id)
{
	CATS_FreeResourceChar(crp, char_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃p���b�g���\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   pltt_id		�������p���b�gID
 */
//--------------------------------------------------------------
void WazaKindIcon_PlttResourceFree(CATS_RES_PTR crp, u32 pltt_id)
{
	CATS_FreeResourcePltt(crp, pltt_id);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���̃Z���A�A�j�����\�[�X��������܂�
 * @param   crp			crp�ւ̃|�C���^
 * @param   char_id		�������Z��ID
 * @param   char_id		�������A�j��ID
 */
//--------------------------------------------------------------
void WazaKindIcon_CellAnmResourceFree(CATS_RES_PTR crp, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}


//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���A�N�^�[�𐶐�����
 *
 * @param   csp				csp�ւ̃|�C���^
 * @param   crp				crp�ւ̃|�C���^
 * @param   waza_kind		�Z����(KIND_BUTURI or KIND_TOKUSYU or KIND_HENNKA)
 * @param   obj_data		�A�N�^�[�w�b�_�ւ̃|�C���^
 *
 * @retval  ���������A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------
CATS_ACT_PTR WazaKindIcon_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int waza_kind, 
	const TCATS_OBJECT_ADD_PARAM_S *obj_data)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	obj_param = *obj_data;
	obj_param.pal = WazaKindIcon_PlttOffsetGet(waza_kind);
	
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R���A�N�^�[���폜
 * @param   cap		�A�N�^�[�|�C���^
 */
//--------------------------------------------------------------
void WazaKindIcon_ActorDelete(CATS_ACT_PTR cap)
{
	CATS_ActorPointerDelete_S(cap);
}

