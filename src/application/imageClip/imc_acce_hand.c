//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_acce_hand.c
 *	@brief		�C���[�W�N���b�v �A�N�Z�T���n���h �V�X�e��
 *				�A�N�Z�T�����샂�[�h���̃n���h�V�X�e���ł�
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "tcb.h"
#include "include/system/lib_pack.h"
#include "include/system/heapdefine.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_obj_list_func.h"
#include "include/application/imageClip/imc_snd_def.h"
#include <string.h>

#define __IMC_ACCE_HAND_H_GLOBAL
#include "include/application/imageClip/imc_acce_hand.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define	IMC_ACCE_HAND_PRI		(0)	// ���񂾃A�N�Z�T���̗D�揇��


//-------------------------------------
//	
//	���{�b�N�X�ԋp�^�X�N�p
//	
//=====================================
#define IMC_ACCE_HAND_LBOX_RET_SYNC	(4)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�A�N�Z�T���n���h�@�\����
//	
//=====================================
typedef struct {
	IMC_DRAW_DATA* drawData;	// �`��f�[�^�\����
	IMC_RIGHT_BOX*	rbox;		// �E�{�b�N�X�\����
	IMC_LEFT_BOX*	lbox;		// ���{�b�N�X�\����
	IMC_SUBWIN*		subwin;		// �T�u�E�B���h�E�\����

	IMC_OBJLIST* obj;			// �����Ă�I�u�W�F�N�g�f�[�^
	int offset_x;				// ���ォ��̃I�t�Z�b�g�����W
	int offset_y;				// ���ォ��̃I�t�Z�b�g�����W
	s16 from_x;					// �������Ƃ��̍��W
	s16 from_y;
	u8	from;					// �������ꏊ	
	u8	from_list;				// �������ꏊ�̃��X�g�i���o�[

	// �|�P�������g��
	int last_x;
	int last_y;
	BOOL poketouch;		// �|�P�����ɐU��邱�Ƃ��o���邩�ǂ���

	u32 push_flg;

} IMC_ACCE_HAND;

//-------------------------------------
//	
//	���{�b�N�X�ԋp�G�t�F�N�g�^�X�N
//	
//=====================================
typedef struct {
	IMC_LEFT_BOX*	lbox;	// ���{�b�N�X�\����
	IMC_OBJLIST* obj;		// �����Ă�I�u�W�F�N�g�f�[�^
	int one_x;		// 1sync�ɓ����l
	int one_y;		// 1sync�ɓ����l
	int targ_x;		// �^�[�Q�b�g�����W
	int targ_y;		// �^�[�Q�b�g�����W
	int lbox_mode;	// �o�^�捶�{�b�N�X�A�N�Z�T�����[�h
	int list_no;	// �o�^�捶�{�b�N�X�A�N�Z�T�����X�gNo
	int count;		// �㉽�񓮂���
	int* p_left_state;	// ���{�b�N�X�X�e�[�^�X
	u32* p_new_push_flg;// �A�N�Z�T���߂蒆�ɐV�����v�b�V����������
} IMC_ACCE_HAND_EFE_LBOX_RET;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void imcAcceHandPushFunc( IMC_HAND* hand );
static void imcAcceHandPopFunc( IMC_HAND* hand );
static void imcAcceHandPushIngFunc( IMC_HAND* hand );

static void setAcceHandAcce( IMC_ACCE_HAND* hand, IMC_OBJLIST* obj, int from, int offset_x, int offset_y, int pri );
static void cleanAcceHandAcce( IMC_ACCE_HAND* hand );

static void imcSubWinMsgPrint( IMC_ACCE_HAND* hand );


// �|�P�����p
static void imcAcceHandPopForPokeFunc( IMC_HAND* hand );
static void imcAcceHandPushIngForPokeFunc( IMC_HAND* hand );

static void imcAcceHandGetObjRect( IMC_HAND* hand, int* top, int* bottom, int* left, int* right );
static void imcAcceHandGetObjRectSubInSize( IMC_HAND* hand, int* top, int* bottom, int* left, int* right );
static void imcAcceHandSetPokeMatrix( IMC_HAND* hand, int x, int y );


static void imcAcceHandBgDummyPop( IMC_HAND* hand );
static void imcAcceHandBgDummy( IMC_HAND* hand );
static void imcBGHandRefFunc( IMC_HAND* hand );


//-------------------------------------
//	
//	����^�X�N�n
//	
//=====================================
// ���{�b�N�X�ɖ߂�
static void imcAcceHandIconLboxRetStart( IMC_ACCE_HAND* acce_hand, int sync, int targ_x, int targ_y, int acce_mode, int list_no );
static void imcAcceHandIconLboxRetTsk( TCB_PTR tcb, void* work );


static void imcAcceHandSameThingHave( IMC_ACCE_HAND* acce_hand );
static void imcAcceHandTakaOff( IMC_ACCE_HAND* acce_hand );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���n���h�쐬
 *
 *	@param	hand		�n���h�\����
 *	@param	rbox		�E�{�b�N�X�\����
 *	@param	lbox		���{�b�N�X�\����
 *	@param	drawData	�`��f�[�^�\����
 *	@param	subwin		�T�u�E�B���h�E�\����
 *	@param	poketouch	�|�P�����ɂӂ�邩�ǂ���
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_HAND_Init( IMC_HAND* hand, IMC_RIGHT_BOX* rbox, IMC_LEFT_BOX* lbox, IMC_DRAW_DATA* drawData, IMC_SUBWIN* subwin, BOOL poketouch )
{
	IMC_ACCE_HAND* acce_hand;
	
	// �n���h�\���̏�����
	IMC_HAND_Init( hand );

	// ���[�N�쐬
	hand->hand_w = sys_AllocMemory( HEAPID_IMAGECLIP_DATA, sizeof( IMC_ACCE_HAND ) );
	memset( hand->hand_w, 0, sizeof( IMC_ACCE_HAND ) );
	acce_hand = hand->hand_w;

	acce_hand->rbox = rbox;
	acce_hand->lbox = lbox;
	acce_hand->drawData = drawData;
	acce_hand->subwin	= subwin;
	acce_hand->poketouch = poketouch;

	// �֐��ݒ�
	hand->push		= imcAcceHandPushFunc;
	hand->pop		= imcAcceHandPopFunc;
	hand->push_ing	= imcAcceHandPushIngFunc;
	hand->dest		= IMC_ACCE_HAND_Delete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���n���h�j��
 *
 *	@param	hand	�n���h�\����
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_HAND_Delete( IMC_HAND* hand )
{
	// ���[�N�j��
	sys_FreeMemoryEz( hand->hand_w );

	// ������
	IMC_HAND_Init( hand );
}




//-----------------------------------------------------------------------------
/**
*		�v���C�x�[�g�֐�
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������Ƃ��̓���
 *
 *	@param	hand	�n���h�\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPushFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	IMC_OBJLIST* obj;			// �I�u�W�F�N�g�f�[�^
	BOOL ret;
	int offset_x, offset_y;		// ���ォ��̃I�t�Z�b�g�l
	int set_list;				// �A�N�Z�T����ݒ肷�郊�X�gNo
	int draw_pri;
	
	// �E�{�b�N�X�ɓ����Ă��邩�`�F�b�N
	ret = IMC_RBOX_TPHit( acce_hand->rbox );
	if( ret ){

		// �A�N�Z�T����G���Ă邩�`�F�b�N
		obj = IMC_RBOX_TPHitObjEx( acce_hand->rbox, &offset_x, &offset_y, acce_hand->drawData->SWSP_UPchar );

		if( obj ){
			// �擾�����̂��|�P�����̂Ƃ�
			// poketouch�����o���݂�
			// ����֎~�Ȃ�G��Ȃ��������Ƃɂ���
			if( obj->flag == IMC_OBJLIST_POKE ){
				if( acce_hand->poketouch == FALSE ){
					obj = NULL;
				}
			}
		}

		if( (obj != NULL) ){
			
			if( obj->flag == IMC_OBJLIST_ACCE ){
				// �A�N�Z�T���؂藣��
				IMC_RBOX_DeleteAccessorieMove( acce_hand->rbox, obj );
				draw_pri = IMC_ACCE_HAND_PRI;

			}else{

				// �|�P��������OFF�Ȃ�|�P�����𓮂������Ƃ͂��Ȃ�
				// �|�P�����؂藣��
				IMC_RBOX_MoveDeletePoke( obj );
				draw_pri = IMC_POKE_DrawPriorityGet( obj->obj_data );	// �\���D�揇�ʂ��܂̒ʂ�
				// ���W���擾
				IMC_OBJLIST_ACCEPOKE_MatGet( obj, &acce_hand->last_x, &acce_hand->last_y );
			}
			
			// �\���D�揇�ʂ̍Đݒ�
			IMC_RBOX_SetObjPriority( acce_hand->rbox );
			
			// �o�^
			setAcceHandAcce( acce_hand, obj, IMC_ACCE_HAND_FROM_RBOX,
					offset_x, offset_y,  draw_pri );

			// BG�D�揇�ʂ̐ݒ�
			IMC_DRAW_WndMaskObjMoveSet();
		}
	}else{

		// ���{�b�N�X�ɓ����Ă��邩�`�F�b�N
		ret = IMC_LBOX_TPHit( acce_hand->lbox );
		if( ret ){

			// �A�N�Z�T����G���Ă邩�`�F�b�N
			obj = IMC_LBOX_TPHitAccessorieEx( acce_hand->lbox, &offset_x, &offset_y, acce_hand->drawData->SWSP_UPchar );
			if( obj != NULL ){
				
				// �A�N�Z�T���؂藣��
				IMC_LBOX_DeleteAccessorieMove( obj );
				
				// �\���D�揇�ʂ̍Đݒ�
				IMC_LBOX_SetAccessoriePriority( acce_hand->lbox );
			
				setAcceHandAcce( acce_hand, obj, IMC_ACCE_HAND_FROM_LBOX, 
						offset_x, offset_y, IMC_ACCE_HAND_PRI );	

				// BG�D�揇�ʂ̐ݒ�
				IMC_DRAW_WndMaskObjMoveSet();
			}
		}
	}

	if( acce_hand->obj ){
		int se = IMC_SE_HAVE_SAMETHING;
		// �����Ƃ��̓���֐��ݒ�
		// �������ςȂ�����֐��ݒ�
		switch( acce_hand->obj->flag ){
		case IMC_OBJLIST_ACCE:
			hand->pop		= imcAcceHandPopFunc; 
			hand->push_ing	= imcAcceHandPushIngFunc; 
			break;
		case IMC_OBJLIST_BG:
			hand->pop		= imcAcceHandBgDummyPop; 
			hand->push_ing	= imcAcceHandBgDummy;
			imcBGHandRefFunc( hand );	// BG���f
			se = IMC_SE_BG_CHANGE;
			break;
		case IMC_OBJLIST_POKE:
			hand->pop		= imcAcceHandPopForPokeFunc; 
			hand->push_ing	= imcAcceHandPushIngForPokeFunc; 
			break;
		default:
			break;
		}
	
		// ���������񂾉�
		Snd_SePlay( se );
		
		// �������Ƃ��̃G�t�F�N�g
//		imcAcceHandSameThingHave( acce_hand );
		
		imcSubWinMsgPrint( acce_hand );
	}
}

// �w�i�p�_�~�[
static void imcAcceHandBgDummy( IMC_HAND* hand )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�pPOP�֐�
 */
//-----------------------------------------------------------------------------
static void imcAcceHandBgDummyPop( IMC_HAND* hand )
{
	IMC_ACCE_HAND* bg_hand = hand->hand_w;
	

	// �^�b�`�����I�u�W�F������Ȃ�
	// ���̃i���o�[��BG���E�p���b�g�ɔ��f
	if( bg_hand->obj ){

		// �I�u�W�F�̃^�C�v��BG�ł��邱�Ƃ��`�F�b�N
		GF_ASSERT( bg_hand->obj->flag == IMC_OBJLIST_BG );
	
		// ���{�b�N�X�ԋp�^�X�N����
		imcAcceHandIconLboxRetStart( bg_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, bg_hand->from_x, bg_hand->from_y, bg_hand->obj->flag, bg_hand->from_list );

		// �󂯌p������
		cleanAcceHandAcce( bg_hand );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���������̓���
 *
 *	@param	hand	�n���h�\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPopFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int	acce_list_no;				// �A�N�Z�T�����X�g�i���o�[
	int ret;
	int top, bottom, left, right;	// �e���W
	int size_x, size_y;				// �T�C�Y
	int x,y;						// ���W
	BOOL check;						// �ǉ��`�F�b�N

	// �I�u�W�F�N�g������Ƃ�
	if( acce_hand->obj ){
		// ��`�f�[�^�擾
		imcAcceHandGetObjRectSubInSize( hand, &top, &bottom, &left, &right );
		
		// �E�{�b�N�X�ɓ����Ă��邩�`�F�b�N
		// �ǂ������o�Ă����炾��
		ret = IMC_RBOX_TPHitSelf( acce_hand->rbox, left, top );
		ret += IMC_RBOX_TPHitSelf( acce_hand->rbox, right, top );
		ret += IMC_RBOX_TPHitSelf( acce_hand->rbox, left, bottom );
		ret += IMC_RBOX_TPHitSelf( acce_hand->rbox, right, bottom );

		if( ret >= 4 ){

			// ���̍��W�ŉE�{�b�N�X�ɂ���
			check = IMC_RBOX_AddAccessorieMove( acce_hand->rbox, acce_hand->obj, acce_hand->drawData->SWSP_UPchar );
			if( check == FALSE ){		// �o�^���s�Ȃ獶�ɖ߂�
				x = acce_hand->from_x;
				y = acce_hand->from_y;
				
				// ���{�b�N�X�ɕԋp����G�t�F�N�g�̉�
				Snd_SePlay( IMC_SE_RET_LBOX );

				// �R�����g�\��
				IMC_SUBWIN_SetBmpWin( acce_hand->subwin, ARC_MSG, NARC_msg_imageclip_dat, imgclip_ng0002 );
			
				// ���{�b�N�X�ԋp�^�X�N����
				imcAcceHandIconLboxRetStart( acce_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, x, y, acce_hand->obj->flag, acce_hand->from_list );

			}else{
				
				// �\���D�揇�ʂ̍Đݒ�
				IMC_RBOX_SetObjPriority( acce_hand->rbox );
				// BG�D�揇�ʂ̐ݒ�
				IMC_DRAW_WndMaskNormalSet();
				acce_hand->push_flg = FALSE;

				// �E�{�b�N�X�ɂ�������
				Snd_SePlay( IMC_SE_ON_RBOX );
			}

		}else{
			// ���p���b�g����
			IMC_ACCESSORIE_OBJ* acce_obj = acce_hand->obj->obj_data;	// �����ɂ̓A�N�Z�T�������u���Ȃ�

			// �H������ł悢�T�C�Y���l�����Ȃ�
			imcAcceHandGetObjRect( hand, &top, &bottom, &left, &right );

			// ���{�b�N�X�ɓ����Ă��邩�`�F�b�N
			ret = IMC_LBOX_TPHitSelf( acce_hand->lbox, left, top );
			ret += IMC_LBOX_TPHitSelf( acce_hand->lbox, right, bottom );
			if( ret < 2 ){
				
				// from�����p���b�g�Ȃ�
				// ���p���b�g�ɂ����Ƃ��̍��W������
				if( acce_hand->from == IMC_ACCE_HAND_FROM_RBOX ){
					IMC_OBJLIST_ACCEPOKE_SizeGet( acce_hand->obj, &size_x, &size_y );

					// ���{�b�N�X�K���Ȉʒu�ɖ߂�
					x = (IMC_LBOX_AREA_X_MOVEOK) + (gf_mtRand() % (IMC_LBOX_AREA_WIDTH_MOVEOK - size_x) );
					y = (IMC_LBOX_AREA_Y_MOVEOK) + (gf_mtRand() % (IMC_LBOX_AREA_HEIGHT_MOVEOK - size_y) );
				}else{

					x = acce_hand->from_x;
					y = acce_hand->from_y;
				}

				// ���{�b�N�X�ɕԋp����G�t�F�N�g�̉�
				Snd_SePlay( IMC_SE_RET_LBOX );
			}else{
				
				// ���̍��W���擾
				IMC_OBJLIST_ACCEPOKE_MatGet( acce_hand->obj, &x, &y );

				// ��������
				Snd_SePlay( IMC_SE_TAKE_OFF );
			}

			// �E���痈���A�N�Z�T���̎��̓��X�g�i���o�[���擾
			if( acce_hand->from == IMC_ACCE_HAND_FROM_RBOX){
				acce_hand->from_list = IMC_LBOX_GetListNo( acce_hand->obj->flag, acce_obj->accessorie_no, acce_hand->lbox->boxData.p_item_buff );
			}

			// ���{�b�N�X�ԋp�^�X�N����
			imcAcceHandIconLboxRetStart( acce_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, x, y, acce_hand->obj->flag, acce_hand->from_list );

		}

		// �������Ƃ��̃G�t�F�N�g
//		imcAcceHandTakaOff( acce_hand );

		// �󂯌p������
		cleanAcceHandAcce( acce_hand );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brieof	�������ςȂ����̓���
 *
 *	@param	hand		�n���h�\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPushIngFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int x, y;

	// �A�N�Z�T���������Ă���Ƃ��́A�^�b�`�p�l���̈ʒu��
	// �A�N�Z�T���𓮂���
	if( acce_hand->obj != NULL ){

		// ���W�̐��������`�F�b�N
		if( (sys.tp_x != 0xffff) &&
			(sys.tp_x != 0xffff) ){
		
			x = sys.tp_x - acce_hand->offset_x;
			y = sys.tp_y - acce_hand->offset_y;

			IMC_OBJLIST_ACCEPOKE_Mat( acce_hand->obj, x, y );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������Ƃ��̓���	�|�P���������Ă�Ƃ��悤
 *
 *	@param	hand		�n���h�\���� 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPopForPokeFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	BOOL ret1, ret2;
	int size_x,size_y;			// �I�u�W�F�N�g�T�C�YXY

	// �I�u�W�F�N�g������Ƃ�
	if( acce_hand->obj ){

		// ���̍��W�ŉE�{�b�N�X�ɂ���
		IMC_RBOX_MoveAddPoke( acce_hand->rbox, acce_hand->obj );

		// �\���D�揇�ʂ̍Đݒ�
		IMC_RBOX_SetObjPriority( acce_hand->rbox );


		// BG�D�揇�ʂ̐ݒ�
		IMC_DRAW_WndMaskNormalSet();
		acce_hand->push_flg = FALSE;

		// �������Ƃ��̃G�t�F�N�g
//		imcAcceHandTakaOff( acce_hand );

		// ��������
		Snd_SePlay( IMC_SE_TAKE_OFF );

		cleanAcceHandAcce( acce_hand );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brieof	�������ςȂ����̓���	�|�P���������Ă�Ƃ��悤
 *
 *	@param	hand	�n���h�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandPushIngForPokeFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int size_x, size_y;
	int x,y;
	int area_x, area_y;
	int in_s_x, in_s_y;	// �H������ł��Ă悢�T�C�Y

	// �A�N�Z�T���������Ă���Ƃ��́A�^�b�`�p�l���̈ʒu��
	// �A�N�Z�T���𓮂���
	if( acce_hand->obj != NULL ){

		// ���W�̐��������`�F�b�N
		if( (sys.tp_x != 0xffff) &&
			(sys.tp_x != 0xffff) ){
			
			// �H������ł悢�T�C�Y���擾
			IMC_OBJLIST_ACCEPOKE_InSizeGet( acce_hand->obj, &in_s_x, &in_s_y );

			// �T�C�Y���擾
			IMC_OBJLIST_ACCEPOKE_SizeGet( acce_hand->obj, &size_x, &size_y );
			// �V���W���v�Z
			x = sys.tp_x - acce_hand->offset_x;
			y = sys.tp_y - acce_hand->offset_y;

			// �������蔻��G���A���쐬
			area_x = x + in_s_x;
			area_y = y + in_s_y;
			size_x -= in_s_x;
			size_y -= in_s_y;

			// ���W���E�{�b�N�X���ɂȂ�悤�ɂ���
			if( area_x <= IMC_RBOX_AREA_X_MOVEOK){
				x = IMC_RBOX_AREA_X_MOVEOK - in_s_x;
			}else{
				if( x + size_x >= (IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK) ){
					x = (IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK) - size_x;
				}
			}
			if( area_y <= IMC_RBOX_AREA_Y_MOVEOK){
				y = IMC_RBOX_AREA_Y_MOVEOK - in_s_y;
			}else{
				if( y + size_y >= (IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK) ){
					y = (IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK) - size_y;
				}
			}
			
			// ���W�ݒ�
			imcAcceHandSetPokeMatrix( hand, x, y );

			// ���̈ʒu�ŃA�N�Z�T�����H�����܂Ȃ����`�F�b�N
			IMC_RBOX_GetPokeUpListEncSize( acce_hand->rbox,
					&in_s_x, &in_s_y );

			// ��̐H������ł���T�C�Y���������čĐݒ�
			x += in_s_x;
			y += in_s_y;
			imcAcceHandSetPokeMatrix( hand, x, y );
		}
	}
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ύX�n���h�֐�	�������Ƃ�
 *
 *	@param	hand	�n���h�\����
 *
 *	@return	none
 *
 * 
 *
 */
//-----------------------------------------------------------------------------
static void imcBGHandPopFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* bg_hand = hand->hand_w;
	IMC_ACCESSORIE_OBJ* acce;	// �A�N�Z�T���[�I�u�W�F
	int acce_list_no;
	
	// �^�b�`�����I�u�W�F������Ȃ�
	// ���̃i���o�[��BG���E�p���b�g�ɔ��f
	if( bg_hand->obj ){
		
		// �I�u�W�F�̃^�C�v��BG�ł��邱�Ƃ��`�F�b�N
		GF_ASSERT( bg_hand->obj->flag == IMC_OBJLIST_BG );
		
		// �A�N�Z�T���f�[�^���
		acce = bg_hand->obj->obj_data;

		// �E�p���b�g���ɂ�����BG�𔽉f
		if( IMC_RBOX_TPHitSelf( bg_hand->rbox, hand->old_x, hand->old_y ) ){

			// �A�N�Z�T���i���o�[��BG���E�p���b�g�ɐݒ�
			IMC_RBOX_BGClean( bg_hand->rbox );
			IMC_RBOX_BGSet( bg_hand->rbox, acce->accessorie_no, HEAPID_IMAGECLIP_DRAW );

			// BG�ύX������
			Snd_SePlay( IMC_SE_BG_CHANGE );
		}else{

			// ���{�b�N�X�ɖ߂���
			Snd_SePlay( IMC_SE_RET_LBOX );
		}
		
		// ���{�b�N�X�ԋp�^�X�N����
		imcAcceHandIconLboxRetStart( bg_hand, IMC_ACCE_HAND_LBOX_RET_SYNC, bg_hand->from_x, bg_hand->from_y, bg_hand->obj->flag, bg_hand->from_list );
		
		// �������Ƃ��̃G�t�F�N�g
//		imcAcceHandTakaOff( bg_hand );
		
		// �󂯌p������
		cleanAcceHandAcce( bg_hand );
	}
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ύX�n���h�֐�	�������Ƃ�
 *
 *	@param	hand	�n���h�\����
 *
 *	@return	none
 *
 * 
 *
 */
//-----------------------------------------------------------------------------
static void imcBGHandRefFunc( IMC_HAND* hand )
{
	IMC_ACCE_HAND* bg_hand = hand->hand_w;
	IMC_ACCESSORIE_OBJ* acce;	// �A�N�Z�T���[�I�u�W�F
	int acce_list_no;
	
	// �^�b�`�����I�u�W�F������Ȃ�
	// ���̃i���o�[��BG���E�p���b�g�ɔ��f
	if( bg_hand->obj ){
		
		// �I�u�W�F�̃^�C�v��BG�ł��邱�Ƃ��`�F�b�N
		GF_ASSERT( bg_hand->obj->flag == IMC_OBJLIST_BG );
		
		// �A�N�Z�T���f�[�^���
		acce = bg_hand->obj->obj_data;


		// �A�N�Z�T���i���o�[��BG���E�p���b�g�ɐݒ�
		IMC_RBOX_BGClean( bg_hand->rbox );
		IMC_RBOX_BGSet( bg_hand->rbox, acce->accessorie_no, HEAPID_IMAGECLIP_DRAW );

		// �������Ƃ��̃G�t�F�N�g
//		imcAcceHandTakaOff( bg_hand );
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g�̓o�^
 *
 *	@param	hand		�n���h�f�[�^
 *	@param	obj			�o�^�I�u�W�F�N�g
 *	@param	from		���������ꏊ
 *	@param	offset_x	���ォ��̃I�t�Z�b�g���W
 *	@param	offset_y	���ォ��̃I�t�Z�b�g���W
 *	@param	pri			�\���D�揇��
 *
 *	@return	none
 *
 *	form
 *		enum{
 *			IMC_ACCE_HAND_FROM_LBOX,		// ���{�b�N�X
 * 			IMC_ACCE_HAND_FROM_RBOX,		// �E�{�b�N�X
 *		};
 *
 */
//-----------------------------------------------------------------------------
static void setAcceHandAcce( IMC_ACCE_HAND* hand, IMC_OBJLIST* obj, int from, int offset_x, int offset_y, int pri )
{
	int pos_x, pos_y;
	IMC_OBJLIST_ACCEPOKE_MatGet( obj, &pos_x, &pos_y );
	
	hand->obj		= obj;
	hand->from_x	= pos_x;
	hand->from_y	= pos_y;
	hand->from		= from;
	hand->offset_x	= offset_x;
	hand->offset_y	= offset_y;

	if( from == IMC_ACCE_HAND_FROM_LBOX ){
		// ���{�b�N�X���炫�����̂Ȃ�
		// ���̃��[�h��ݒ�
		hand->from_list	= IMC_LBOX_GetCurrentNo( hand->lbox, hand->obj->flag );	// �J�����g���X�gNo
	}else{
		// �E���痈�����̂̓f�t�H���g�ł���
		hand->from_list	= 0;
	}

	// �n���h�v�b�V���n�m
	hand->push_flg = TRUE;

	// �D�揇�ʂ��ŏ�ɂ���
	IMC_OBJLIST_ACCEPOKE_Pri( obj, pri );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���n���h�̃A�N�Z�T���f�[�^���̂ݏ�����
 *
 *	@param	hand	�A�N�Z�T���n���h�\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanAcceHandAcce( IMC_ACCE_HAND* hand )
{
	hand->obj		= NULL;
	hand->from_x	= 0;
	hand->from_y	= 0;
	hand->from		= 0;
	hand->from_list	= 0;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�n���h�\���^�C�ɓo�^����Ă���I�u�W�F�N�g�̋�`�T�C�Y���擾����
 *	
 *	@param	hand		�n���h�\����
 *	@param	top			����W
 *	@param	bottom		�����W
 *	@param	left		�����W
 *	@param	right		�E���W	
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandGetObjRect( IMC_HAND* hand, int* top, int* bottom, int* left, int* right )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	int size_x,size_y;			// �I�u�W�F�N�g�T�C�YXY
	int mat_x, mat_y;			// �I�u�W�F�N�g���W

	IMC_OBJLIST_ACCEPOKE_SizeGet( acce_hand->obj, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( acce_hand->obj, &mat_x, &mat_y );
	
	*top	= mat_y;
	*bottom	= mat_y + size_y;
	*left	= mat_x;
	*right	= mat_x + size_x;
}


//----------------------------------------------------------------------------
/**
 * ���H������ł悢�T�C�Y�����炷		�E�p���b�g�p
 *
 *	@brief	�n���h�\���^�C�ɓo�^����Ă���I�u�W�F�N�g�̋�`�T�C�Y���擾����
 *	
 *	@param	hand		�n���h�\����
 *	@param	top			����W
 *	@param	bottom		�����W
 *	@param	left		�����W
 *	@param	right		�E���W	
 *
 *	@return	none
 *	
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandGetObjRectSubInSize( IMC_HAND* hand, int* top, int* bottom, int* left, int* right )
{
	IMC_ACCE_HAND* acce_hand		= hand->hand_w;
	IMC_OBJLIST_GetObjRectSubInSize( acce_hand->obj, top, bottom, left, right );
}


//-------------------------------------
//	
//	����^�X�N�n
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�ւ̃A�N�Z�T���ԋp�G�t�F�N�g�^�X�N�J�n�֐�
 *	
 *	@param	acce_hand		�A�N�Z�T���n���h�\����
 *	@param	sync			���V���N�œ�������
 *	@param	targ_x			�ԋp����W��
 *	@param	targ_y			�ԋp����W��
 *	@param	acce_mode		�A�N�Z�T�����[�h
 *	@param	list_no			�A�N�Z�T�����X�g�ԍ�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandIconLboxRetStart( IMC_ACCE_HAND* acce_hand, int sync, int targ_x, int targ_y, int acce_mode, int list_no )
{
	TCB_PTR tcb;
	IMC_ACCE_HAND_EFE_LBOX_RET* work;
	int x, y;

	tcb = PMDS_taskAdd( imcAcceHandIconLboxRetTsk, sizeof(IMC_ACCE_HAND_EFE_LBOX_RET), 0, HEAPID_IMAGECLIP_DATA );

	work = TCB_GetWork( tcb );

	work->lbox		= acce_hand->lbox;
	work->obj		= acce_hand->obj;
	work->count		= sync;
	work->targ_x	= targ_x;
	work->targ_y	= targ_y;
	work->lbox_mode	= acce_mode;
	work->list_no	= list_no;
	work->p_left_state = &acce_hand->lbox->boxData.state;
	work->p_new_push_flg = &acce_hand->push_flg;
	
	// �P�V���N�ɓ������l���擾
	IMC_OBJLIST_ACCEPOKE_MatGet( acce_hand->obj, &x, &y );
	
	work->one_x		= (work->targ_x - x) / sync;
	work->one_y		= (work->targ_y - y) / sync;

	// �A�N�Z�T�����͂Ȃ���
	acce_hand->push_flg = FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�ւ̃A�N�Z�T���ԋp�G�t�F�N�g�^�X�N
 *
 *	@param	tcb		tcb�|�C���^
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandIconLboxRetTsk( TCB_PTR tcb, void* work )
{
	IMC_ACCE_HAND_EFE_LBOX_RET* tsk_w = work;
	int x, y;			// ���W

	// ���{�b�N�X���t�F�[�h���͂Ƃ߂�
	if( *tsk_w->p_left_state == IMC_LBOX_STATE_FADE ){
		return ;
	}
	
	IMC_OBJLIST_ACCEPOKE_MatGet( tsk_w->obj, &x, &y );

	x += tsk_w->one_x;
	y += tsk_w->one_y;

	tsk_w->count--;

	// �I���`�F�b�N
	if(tsk_w->count < 0){
		IMC_OBJLIST_ACCEPOKE_Mat( tsk_w->obj, tsk_w->targ_x, tsk_w->targ_y );

		// ���̍��W�ō��{�b�N�X�ɂ���
		IMC_LBOX_AddAccessorieMove(
				tsk_w->lbox,
				tsk_w->lbox_mode,
				tsk_w->list_no,
				tsk_w->obj	);
		
		
		// �\���D�揇�ʂ̍Đݒ�
		IMC_LBOX_SetAccessoriePriority( tsk_w->lbox );

		// BG�D�揇�ʂ̐ݒ�
		// ���������p���b�g�ɖ߂��Ă���Ԃ�
		// �V�������̂��肪����ł�����
		// �}�X�N�`�F���W���s��Ȃ�
		if( *(tsk_w->p_new_push_flg) == FALSE ){
			IMC_DRAW_WndMaskNormalSet();
		}
		
		// �I��
		PMDS_taskDel( tcb );
	}else{

		// ���W�ݒ�
		IMC_OBJLIST_ACCEPOKE_Mat( tsk_w->obj, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����������Ƃ��̊֐�
 *
 *	@param	acce_hand	�����������n���h�\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandSameThingHave( IMC_ACCE_HAND* acce_hand )
{
	if( acce_hand->obj->flag < IMC_OBJLIST_POKE ){
		
		IMC_ACCE_ObjScaleSet( acce_hand->obj->obj_data, 
				FX32_ONE + 0x200,
				FX32_ONE + 0x200);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����G�t�F�N�g�̊֐�
 *
 *	@param	acce_hand	���ꂩ������������������n���h�\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcAcceHandTakaOff( IMC_ACCE_HAND* acce_hand )
{
	if( acce_hand->obj->flag < IMC_OBJLIST_POKE ){
		
		IMC_ACCE_ObjScaleSet( acce_hand->obj->obj_data, 
				FX32_ONE,
				FX32_ONE);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief		�T�u�E�B���h�E�ɍ��ێ����Ă��镨�̃��b�Z�[�W���o��
 *
 *	@param	hand �A�N�Z�T���n���h�\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcSubWinMsgPrint( IMC_ACCE_HAND* hand )
{
	// �A�N�Z�T��
	if( hand->obj->flag == IMC_OBJLIST_ACCE ){
		IMC_ACCESSORIE_OBJ* acce = hand->obj->obj_data;
		
		IMC_SUBWIN_SetBmpWin( hand->subwin, ARC_MSG, NARC_msg_imageclip_acce_dat, acce->accessorie_no );
		
	// BG
	}else if( hand->obj->flag == IMC_OBJLIST_BG ){
		IMC_ACCESSORIE_OBJ* acce = hand->obj->obj_data;
		
		IMC_SUBWIN_SetBmpWin( hand->subwin, ARC_MSG, NARC_msg_imageclip_bg_dat, acce->accessorie_no );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������W��ݒ肷��
 *
 *	@param	hand	�A�N�Z�T���n���h
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcAcceHandSetPokeMatrix( IMC_HAND* hand, int x, int y )
{
	IMC_ACCE_HAND* acce_hand = hand->hand_w;
	IMC_OBJLIST_ACCEPOKE_Mat( acce_hand->obj, x, y );

	// �ړ�������������
	// �E�{�b�N�X�̃|�P�����̏�̃A�N�Z�T����������
	IMC_RBOX_PokeUpListMove( acce_hand->rbox, 
			x - acce_hand->last_x, y - acce_hand->last_y );

	acce_hand->last_x = x;
	acce_hand->last_y = y;
}
