//==============================================================================
/**
 * @file	contest_cursor.c
 * @brief	�R���e�X�g����ʗp�J�[�\��
 * @author	matsuda
 * @date	2006.03.27(��)
 *
 * battle_cursor.c�̖��̈Ⴂ�B�I�[�o�[���C�̊֌W�Ŏg���Ȃ������̂ŕʖ��ɂ��ėp�ӂ���
 */
//==============================================================================
#include "common.h"
#include "battle\graphic\batt_obj_def.h"
#include "battle\graphic\batt_bg_def.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "battle/battle_tcb_pri.h"

#include "contest/contest_cursor.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�퓬�J�[�\���̃A�N�^�[�|�C���^�z��ԍ�
enum{
	CCURSOR_ACT_LU,		///<����J�[�\��
	CCURSOR_ACT_RU,		///<�E��J�[�\��
	CCURSOR_ACT_LD,		///<�����J�[�\��
	CCURSOR_ACT_RD,		///<�E���J�[�\��
	
	CCURSOR_ACT_EX,		///<���ʃJ�[�\��
	
	CCURSOR_ACT_NUM,	///<�퓬�J�[�\���̃A�N�^�[�g�p��
};

///�J�[�\��OBJUpdate��TCB�v���C�I���e�B
#define TCBPRI_CCURSOR					(40000)

//==============================================================================
//	�\���̒�`
//==============================================================================
///�퓬�J�[�\�����[�N
typedef struct _CCURSOR_WORK{
	CATS_ACT_PTR cap[CCURSOR_ACT_NUM];
	TCB_PTR update_tcb;
}CCURSOR_WORK;

//==============================================================================
//	�f�[�^
//==============================================================================
///AA�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S BCursorObjParam = {
	0, 0, 0,		//x, y, z
	0, 0, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		0,	//�L����
		0,	//�p���b�g
		0,	//�Z��
		0,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	0,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void CCURSOR_ObjectUpdate(TCB_PTR tcb, void *work);
void CCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
void CCURSOR_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
CCURSOR_PTR CCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
void CCURSOR_ActorDelete(CCURSOR_PTR cursor);
void CCURSOR_PosSetON(CCURSOR_PTR cursor, int left, int right, int top, int bottom);
void CCURSOR_ExPosSetON(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type);
void CCURSOR_OFF(CCURSOR_PTR cursor);



//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̃��\�[�X�����[�h����
 *
 * @param   csp			
 * @param   crp			
 * @param   pfd			
 * @param   char_id		�L����ID
 * @param   pal_id		�p���b�gID
 * @param   cell_id		�Z��ID
 * @param   anm_id		�A�j��ID
 */
//--------------------------------------------------------------
void CCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp, 
		ARC_BATT_OBJ, BATTLE_CURSOR_OAM_SUB_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DSUB, pal_id);
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, BATTLE_CURSOR_OAM_SUB_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, char_id);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, BATTLE_CURSOR_OAM_SUB_NCER_BIN, 1, 
		cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		BATTLE_CURSOR_OAM_SUB_NANR_BIN, 1, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̃��\�[�X���������
 *
 * @param   crp			
 * @param   char_id		�L����ID
 * @param   pal_id		�p���b�gID
 * @param   cell_id		�Z��ID
 * @param   anm_id		�A�j��ID
 */
//--------------------------------------------------------------
void CCURSOR_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceChar(crp, char_id);
	CATS_FreeResourcePltt(crp, pal_id);
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̃A�N�^�[�𐶐����܂�
 *
 * @param   csp		
 * @param   crp		
 * @param   heap_id		�q�[�vID
 * @param   char_id		�L����ID
 * @param   pal_id		�p���b�gID
 * @param   cell_id		�Z��ID
 * @param   anm_id		�A�j��ID
 * @param   soft_pri	�\�t�g�v���C�I���e�B
 * @param   bg_pri		BG�v���C�I���e�B
 *
 * @retval  �������ꂽ�퓬�J�[�\�����[�N�̃|�C���^
 *
 * �퓬�J�[�\�����[�N�̐�����Update�pTCB�̐����������ɍs���܂�
 * �������͕\��OFF�ɂȂ��Ă��܂��B
 */
//--------------------------------------------------------------
CCURSOR_PTR CCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri)
{
	CCURSOR_WORK *cursor;
	TCATS_OBJECT_ADD_PARAM_S obj_head;
	int i;
	
	obj_head = BCursorObjParam;
	obj_head.id[CLACT_U_CHAR_RES] = char_id;
	obj_head.id[CLACT_U_PLTT_RES] = pal_id;
	obj_head.id[CLACT_U_CELL_RES] = cell_id;
	obj_head.id[CLACT_U_CELLANM_RES] = anm_id;
	obj_head.pri = soft_pri;
	obj_head.bg_pri = bg_pri;
	
	cursor = sys_AllocMemory(heap_id, sizeof(CCURSOR_WORK));
	MI_CpuClear8(cursor, sizeof(CCURSOR_WORK));
	
	for(i = 0; i < CCURSOR_ACT_NUM; i++){
		cursor->cap[i] = CATS_ObjectAdd_S(csp, crp, &obj_head);
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_FALSE);
	}
	
	cursor->update_tcb = TCB_Add(CCURSOR_ObjectUpdate, cursor, TCBPRI_CCURSOR);
	return cursor;
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���A�N�^�[���폜���܂�
 *
 * @param   cursor		�퓬�J�[�\�����[�N�ւ̃|�C���^
 *
 * �퓬�J�[�\�����[�N�̉���ƁAUpdate�pTCB�̍폜���s���܂�
 */
//--------------------------------------------------------------
void CCURSOR_ActorDelete(CCURSOR_PTR cursor)
{
	int i;
	
	for(i = 0; i < CCURSOR_ACT_NUM; i++){
		CATS_ActorPointerDelete_S(cursor->cap[i]);
	}
	
	TCB_Delete(cursor->update_tcb);
	sys_FreeMemoryEz(cursor);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�(�S�ČʂɎw��)
 *
 * @param   cursor		�퓬�J�[�\�����[�N�ւ̃|�C���^
 * @param   left		�����W
 * @param   right		�E���W
 * @param   top			����W
 * @param   bottom		�����W
 */
//--------------------------------------------------------------
void CCURSOR_IndividualPosSetON_Surface(CCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y, fx32 surface_y)
{
	int i;
	
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_LU], lu_x, lu_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_RU], ru_x, ru_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_LD], ld_x, ld_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_RD], rd_x, rd_y, surface_y);

	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_LU], CCURSOR_ANMTYPE_LU);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_RU], CCURSOR_ANMTYPE_RU);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_LD], CCURSOR_ANMTYPE_LD);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_RD], CCURSOR_ANMTYPE_RD);

	for(i = 0; i < CCURSOR_ACT_EX; i++){
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_TRUE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�(�S�ČʂɎw��)
 *
 * @param   cursor		�퓬�J�[�\�����[�N�ւ̃|�C���^
 * @param   left		�����W
 * @param   right		�E���W
 * @param   top			����W
 * @param   bottom		�����W
 */
//--------------------------------------------------------------
void CCURSOR_IndividualPosSetON(CCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y)
{
	CCURSOR_IndividualPosSetON_Surface(cursor, lu_x, lu_y, ru_x, ru_y, ld_x, ld_y, rd_x, rd_y,
		SUB_SURFACE_Y);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�(��`�Ŏw��)
 *
 * @param   cursor		�퓬�J�[�\�����[�N�ւ̃|�C���^
 * @param   left		�����W
 * @param   right		�E���W
 * @param   top			����W
 * @param   bottom		�����W
 */
//--------------------------------------------------------------
void CCURSOR_PosSetON(CCURSOR_PTR cursor, int left, int right, int top, int bottom)
{
	CCURSOR_IndividualPosSetON(cursor, left, top, right, top, left, bottom, right, bottom);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�(��`�Ŏw��)
 *
 * @param   cursor		�퓬�J�[�\�����[�N�ւ̃|�C���^
 * @param   left		�����W
 * @param   right		�E���W
 * @param   top			����W
 * @param   bottom		�����W
 */
//--------------------------------------------------------------
void CCURSOR_PosSetON_Surface(CCURSOR_PTR cursor, int left, int right, int top, int bottom,
	fx32 surface_y)
{
	CCURSOR_IndividualPosSetON_Surface(cursor, left, top, right, top, left, bottom, right, bottom,
		surface_y);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̓��ʃJ�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�
 *
 * @param   cursor			�퓬�J�[�\�����[�N�ւ̃|�C���^
 * @param   x				���WX
 * @param   y				���WY
 * @param   anm_type		�A�j���^�C�v(CCURSOR_ANMTYPE_???)
 */
//--------------------------------------------------------------
void CCURSOR_ExPosSetON_Surface(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type,
	fx32 surface_y)
{
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_EX], x, y, surface_y);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_EX], anm_type);
	CATS_ObjectEnableCap(cursor->cap[CCURSOR_ACT_EX], CATS_ENABLE_TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̓��ʃJ�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�
 *
 * @param   cursor			�퓬�J�[�\�����[�N�ւ̃|�C���^
 * @param   x				���WX
 * @param   y				���WY
 * @param   anm_type		�A�j���^�C�v(CCURSOR_ANMTYPE_???)
 */
//--------------------------------------------------------------
void CCURSOR_ExPosSetON(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type)
{
	CCURSOR_ExPosSetON_Surface(cursor, x, y, anm_type, SUB_SURFACE_Y);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\����S�ĕ\��OFF����
 * @param   cursor		�퓬�J�[�\�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void CCURSOR_OFF(CCURSOR_PTR cursor)
{
	int i;
	
	for(i = 0; i < CCURSOR_ACT_NUM; i++){
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_FALSE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�J�[�\���̓��ʃJ�[�\���̂ݕ\��OFF����
 * @param   cursor		�퓬�J�[�\�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void CCURSOR_ExOFF(CCURSOR_PTR cursor)
{
	CATS_ObjectEnableCap(cursor->cap[CCURSOR_ACT_EX], CATS_ENABLE_FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���A�j��Update����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�J�[�\�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void CCURSOR_ObjectUpdate(TCB_PTR tcb, void *work)
{
	CCURSOR_WORK *cursor = work;
	int i;
	
	if(CATS_ObjectEnableGetCap(cursor->cap[CCURSOR_ACT_LU]) == CATS_ENABLE_FALSE){
		return;
	}
	
	for(i = 0; i < CCURSOR_ACT_EX; i++){
		CATS_ObjectUpdateCap(cursor->cap[i]);
	}
	if(CATS_ObjectEnableGetCap(cursor->cap[CCURSOR_ACT_EX]) == CATS_ENABLE_TRUE){
		CATS_ObjectUpdateCap(cursor->cap[CCURSOR_ACT_EX]);
	}
}

