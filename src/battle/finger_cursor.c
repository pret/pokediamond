//==============================================================================
/**
 * @file	finger_cursor.c
 * @brief	�w�J�[�\��
 * @author	matsuda
 * @date	2006.06.13(��)
 */
//==============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "battle/battle_tcb_pri.h"

#include "battle/finger_cursor.h"
#include "src/demo/ev_pokeselect.naix"


//==============================================================================
//	�萔��`
//==============================================================================
///Sin�p�x���Z�l(����100�{)
#define FINGER_ADD_ANGLE		(10 * 100)
///Sin�ړ��ӂ蕝
#define FINGER_FURIHABA			(14)

///�^�b�`�A�j���������̍��W�I�t�Z�b�gY
#define FINGER_TOUCH_OFFSET_Y	(8)
///�^�b�`�A�j���������̍��W�߂�I�t�Z�b�gY
#define FINGER_TOUCH_BACK_Y		(2)
///�^�b�`�A�j��������O�̒�~�E�F�C�g
#define FINGER_TOUCH_ANIME_BEFORE_WAIT	(3)
///�^�b�`�A�j���������̃A�j���E�F�C�g
#define FINGER_TOUCH_ANIME_WAIT	(2)

//==============================================================================
//	�\���̒�`
//==============================================================================
///�w�J�[�\�����[�N
typedef struct _FINGER_WORK{
	CATS_ACT_PTR cap;
	TCB_PTR update_tcb;
	int x;
	int y;
	int angle;
	fx32 surface_y;
	
	s16 touch_wait;
	u8 touch_req;
	u8 touch_occurrence;
	
	u8 touch_anime_flag;
	u8 touch_anime_seq;
	u8 touch_anime_wait;
}FINGER_WORK;

//==============================================================================
//	�f�[�^
//==============================================================================
///AA�p�Q�[�W�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S FingerObjParam = {
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
void FINGER_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
void FINGER_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
FINGER_PTR FINGER_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
void FINGER_ActorDelete(FINGER_PTR finger);
void FINGER_PosSetON(FINGER_PTR finger, int x, int y);
void FINGER_OFF(FINGER_PTR finger);
static void FINGER_ObjectUpdate(TCB_PTR tcb, void *work);
static void FINGER_SubWorkClear(FINGER_PTR finger);



//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\���̃��\�[�X�����[�h����
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
void FINGER_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp, 
		ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_psel_cursol_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DSUB, pal_id);
	CATS_LoadResourceCharArc(csp, crp, ARC_EV_POKESELECT_GRA, 
		NARC_ev_pokeselect_psel_cursol_NCGR, 0, NNS_G2D_VRAM_TYPE_2DSUB, char_id);
	CATS_LoadResourceCellArc(csp, crp, ARC_EV_POKESELECT_GRA, 
		NARC_ev_pokeselect_psel_cursol_NCER, 0, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_EV_POKESELECT_GRA, 
		NARC_ev_pokeselect_psel_cursol_NANR, 0, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\���̃��\�[�X���������
 *
 * @param   crp			
 * @param   char_id		�L����ID
 * @param   pal_id		�p���b�gID
 * @param   cell_id		�Z��ID
 * @param   anm_id		�A�j��ID
 */
//--------------------------------------------------------------
void FINGER_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceChar(crp, char_id);
	CATS_FreeResourcePltt(crp, pal_id);
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\���̃A�N�^�[�𐶐����܂�
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
 * @retval  �������ꂽ�w�J�[�\�����[�N�̃|�C���^
 *
 * �w�J�[�\�����[�N�̐�����Update�pTCB�̐����������ɍs���܂�
 * �������͕\��OFF�ɂȂ��Ă��܂��B
 */
//--------------------------------------------------------------
FINGER_PTR FINGER_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri)
{
	FINGER_WORK *finger;
	TCATS_OBJECT_ADD_PARAM_S obj_head;
	
	obj_head = FingerObjParam;
	obj_head.id[CLACT_U_CHAR_RES] = char_id;
	obj_head.id[CLACT_U_PLTT_RES] = pal_id;
	obj_head.id[CLACT_U_CELL_RES] = cell_id;
	obj_head.id[CLACT_U_CELLANM_RES] = anm_id;
	obj_head.pri = soft_pri;
	obj_head.bg_pri = bg_pri;
	
	finger = sys_AllocMemory(heap_id, sizeof(FINGER_WORK));
	MI_CpuClear8(finger, sizeof(FINGER_WORK));
	
	finger->cap = CATS_ObjectAdd_S(csp, crp, &obj_head);
	CATS_ObjectEnableCap(finger->cap, CATS_ENABLE_FALSE);
	
	finger->surface_y = SUB_SURFACE_Y;
	finger->update_tcb = TCB_Add(FINGER_ObjectUpdate, finger, TCBPRI_FINGER);
	return finger;
}

//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\���A�N�^�[���폜���܂�
 *
 * @param   finger		�w�J�[�\�����[�N�ւ̃|�C���^
 *
 * �w�J�[�\�����[�N�̉���ƁAUpdate�pTCB�̍폜���s���܂�
 */
//--------------------------------------------------------------
void FINGER_ActorDelete(FINGER_PTR finger)
{
	CATS_ActorPointerDelete_S(finger->cap);
	
	TCB_Delete(finger->update_tcb);
	sys_FreeMemoryEz(finger);
}

//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�(�T�[�t�F�[�X�w��)
 *
 * @param   finger		�w�J�[�\�����[�N�ւ̃|�C���^
 * @param   left		�����W
 * @param   right		�E���W
 * @param   top			����W
 * @param   bottom		�����W
 */
//--------------------------------------------------------------
void FINGER_PosSetON_Surface(FINGER_PTR finger, int x, int y, fx32 surface_y)
{
	FINGER_SubWorkClear(finger);
	
	finger->x = x;
	finger->y = y;
	finger->surface_y = surface_y;
	CATS_ObjectPosSetCap_SubSurface(finger->cap, x, y, surface_y);
	CATS_ObjectEnableCap(finger->cap, CATS_ENABLE_TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\���̍��W�Z�b�g�ƕ\����ON���s���܂�
 *
 * @param   finger		�w�J�[�\�����[�N�ւ̃|�C���^
 * @param   left		�����W
 * @param   right		�E���W
 * @param   top			����W
 * @param   bottom		�����W
 */
//--------------------------------------------------------------
void FINGER_PosSetON(FINGER_PTR finger, int x, int y)
{
	FINGER_PosSetON_Surface(finger, x, y, SUB_SURFACE_Y);
}

//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\����S�ĕ\��OFF����
 * @param   finger		�w�J�[�\�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void FINGER_OFF(FINGER_PTR finger)
{
	CATS_ObjectEnableCap(finger->cap, CATS_ENABLE_FALSE);
	FINGER_SubWorkClear(finger);
}

//--------------------------------------------------------------
/**
 * @brief   �w�J�[�\���Ƀ^�b�`�A�j�����N�G�X�g�𔭍s����
 *
 * @param   finger		�w�J�[�\�����[�N�ւ̃|�C���^
 * @param   wait		�^�b�`�A�j���𔭓�����܂ł̃E�F�C�g
 *
 * �^�b�`�A�j���������������ǂ����́AFINGER_TouchAnimeCheck�Ŋm�F�o���܂��B
 * �^�b�`�A�j����wait��0�ɂȂ��Ă��āA�Ȃ�����Sin�J�[�u�ړ��ň�ԉ����w���Ă��鎞�ɔ������܂��B
 */
//--------------------------------------------------------------
void FINGER_TouchReq(FINGER_PTR finger, int wait)
{
	finger->touch_wait = wait;
}

//--------------------------------------------------------------
/**
 * @brief   �^�b�`�A�j���������������`�F�b�N
 *
 * @param   finger		�w�J�[�\�����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:���������B�@FALSE:�������Ă��Ȃ�
 */
//--------------------------------------------------------------
BOOL FINGER_TouchAnimeCheck(FINGER_PTR finger)
{
	return finger->touch_occurrence;
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���A�j��Update����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�J�[�\�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void FINGER_ObjectUpdate(TCB_PTR tcb, void *work)
{
	FINGER_WORK *finger = work;
	
	if(finger->touch_occurrence == TRUE){
		finger->touch_occurrence = FALSE;
	}
	
	if(finger->touch_wait > 0){
		finger->touch_wait--;
		if(finger->touch_wait == 0){
			finger->touch_req = TRUE;
		}
	}
	
	if(CATS_ObjectEnableGetCap(finger->cap) == CATS_ENABLE_FALSE){
		return;
	}
	
	//Sin�J�[�u�ړ�
	if(finger->touch_anime_flag == FALSE){
		int offset_y;
		
		finger->angle += FINGER_ADD_ANGLE;
		if(finger->angle >= 180*100){
			finger->angle -= 180*100;
			if(finger->touch_req == TRUE){
				finger->touch_anime_flag = TRUE;
				finger->touch_req = FALSE;
			}
		}
		
		if(finger->touch_anime_flag == FALSE){
			offset_y = FX_Mul(Sin360(finger->angle / 100), FINGER_FURIHABA << FX32_SHIFT) 
				/ FX32_ONE;
			CATS_ObjectPosSetCap_SubSurface(finger->cap, finger->x, finger->y - offset_y,
				finger->surface_y);
		}
	}
	
	//�^�b�`�A�j��
	if(finger->touch_anime_flag == TRUE){
		switch(finger->touch_anime_seq){
		case 0:
			finger->touch_anime_wait++;
			if(finger->touch_anime_wait > FINGER_TOUCH_ANIME_BEFORE_WAIT){
				finger->touch_anime_wait = 0;
				finger->touch_anime_seq++;
			}
			break;
		case 1:
			CATS_ObjectPosSetCap_SubSurface(finger->cap, finger->x, 
				finger->y + FINGER_TOUCH_OFFSET_Y, finger->surface_y);
			finger->touch_occurrence = TRUE;
			finger->touch_anime_seq++;
			break;
		case 2:
			finger->touch_anime_wait++;
			if(finger->touch_anime_wait > FINGER_TOUCH_ANIME_WAIT){
				CATS_ObjectPosSetCap_SubSurface(finger->cap, finger->x, 
					finger->y + FINGER_TOUCH_BACK_Y, finger->surface_y);
				finger->touch_anime_wait = 0;
				finger->touch_anime_seq++;
			}
			break;
		case 3:
			finger->touch_anime_wait++;
			if(finger->touch_anime_wait > FINGER_TOUCH_ANIME_WAIT){
				FINGER_OFF(finger);
				finger->touch_anime_wait = 0;
				finger->touch_anime_seq++;
			}
			break;
		default:
			break;
		}
	}
	
	CATS_ObjectUpdateCap(finger->cap);
}

//--------------------------------------------------------------
/**
 * @brief   �F�X�ȃT�u�p�����[�^���N���A����
 * @param   finger		�w�J�[�\�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void FINGER_SubWorkClear(FINGER_PTR finger)
{
	finger->angle = 0;
	finger->touch_anime_flag = FALSE;
	finger->touch_anime_seq = 0;
	finger->touch_anime_wait = 0;
}
