//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_right_box.c
 *	@brief		�E�̔�
 *	@author		tomoya takahashi
 *	@data		2005.09.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_obj_list_func.h"

#include "imc_calc.h"

#define	__IMC_RIGHT_BOX_H_GLOBAL
#include "include/application/imageClip/imc_right_box.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define IMC_RIGHT_BOX_ACCE_MAX	(10)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void ImcRightSetAcceList( IMC_RIGHT_BOX* p_data, IMC_OBJLIST* objList, BOOL top_bottom, NNSG2dCharacterData** SWSP_UPchar );
static void imcRbox_GetAcceEncSize( IMC_OBJLIST* objlist, int* enc_x, int* enc_y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�p�̈�쐬
 *
 *	@param	rbox		�E�{�b�N�X�p�f�[�^
 *	@param	init		�E�{�b�N�X�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_InitSys( IMC_RIGHT_BOX* rbox, IMC_RIGHT_BOX_INIT* init )
{
	// �`��f�[�^�쐬
	rbox->boxDraw.SWSP_drawSys	= init->SWSP_drawSys;
	rbox->boxDraw.SWSP_charData	= init->SWSP_charData;
	rbox->boxDraw.SWSP_plttData	= init->SWSP_plttData;
	rbox->boxDraw.accePlttOfsTbl= init->accePlttOfsTbl;
	rbox->boxDraw.SSM_drawSys	= init->SSM_drawSys;
	rbox->boxDraw.BG_Ini		= init->BG_Ini;
	rbox->boxDraw.acce			= init->acce;
	rbox->boxDraw.bg_no			= 0;

	// �V�X�e���f�[�^
	rbox->boxData.objListTbl = init->objListTbl;

	rbox->boxData.dummy.next = &rbox->boxData.dummy;
	rbox->boxData.dummy.prev = &rbox->boxData.dummy;
	rbox->boxData.dummy_poke.next = &rbox->boxData.dummy_poke;
	rbox->boxData.dummy_poke.prev = &rbox->boxData.dummy_poke;
	rbox->boxData.obj_count = 0;
	rbox->boxData.obj_count_max = init->acce_count_max;


	// �|�P�����I�u�W�F�쐬
	{
		IMC_OBJLIST* objList;
		objList = IMC_OBJLIST_MakeObjList( rbox->boxData.objListTbl, &rbox->boxDraw.poke, IMC_OBJLIST_POKE );

		// �擪�Ƀ��X�g�o�^
		IMC_OBJLIST_Set( objList, &rbox->boxData.dummy_poke );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�p�̈�j��
 *
 *	@param	rbox		�j������E�{�b�N�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_DeleteSys( IMC_RIGHT_BOX* rbox )
{
	// �|�P�����j��
	IMC_RBOX_DeletePoke( rbox );

	// ���X�g�j��
	IMC_RBOX_DeleteAccessorieAll( rbox );
	
	memset( rbox, 0, sizeof(IMC_RIGHT_BOX) );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����f�[�^�v���C���[�p�쐬
 *
 *	@param	rbox			�E�{�b�N�X�f�[�^
 *	@param	poke_para		�쐬����|�P�����̃|�P�����p�����[�^
 *	@param	arc_data		�A�[�J�C�u�t�@�C���f�[�^�i�[�̈�
 *	@param	x				x���W
 *	@param	y				y���W
 *	@param	pri				�\���D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_AddPokePlayer( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int x, int y, int pri, int heap )
{
	// �|�P�����f�[�^�쐬
	IMC_POKE_Init( &rbox->boxDraw.poke, rbox->boxDraw.SSM_drawSys, poke_para, arc_data, heap );

	// �\���D�揇��
	IMC_POKE_DrawPrioritySet( &rbox->boxDraw.poke, pri );

	// ���W
	IMC_POKE_MatrixSet( &rbox->boxDraw.poke, x, y );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����f�[�^�쐬
 *
 *	@param	rbox			�E�{�b�N�X�f�[�^
 *	@param	poke_para		�쐬����|�P�����̃|�P�����p�����[�^
 *	@param	arc_data		�A�[�J�C�u�t�@�C���f�[�^�i�[�̈�
 *	@param	heap
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_AddPoke( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap )
{
	// �|�P�����f�[�^�쐬
	IMC_POKE_Init( &rbox->boxDraw.poke, rbox->boxDraw.SSM_drawSys, poke_para, arc_data, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����ړ��ǉ�
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	poke	�|�P�����I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_MoveAddPoke( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* poke )
{
	// �|�P�����ナ�X�g�̍Ō�ɓo�^
	IMC_OBJLIST_Set(  poke, rbox->boxData.dummy_poke.prev);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ړ������邽�߃��X�g����폜
 *	
 *	@param	poke		�|�P�����I�u�W�F
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_MoveDeletePoke( IMC_OBJLIST* poke )
{
	// ���X�g����j��
	IMC_OBJLIST_Delete( poke );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����I�u�W�F�N�g�j��
 *
 *	@param	rbox	�E�{�b�N�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_DeletePoke( IMC_RIGHT_BOX* rbox )
{
	// �|�P�����f�[�^�j��
	IMC_POKE_Delete( &rbox->boxDraw.poke );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̐V�K�ǉ�
 *
 *	@param	rbox				�E�{�b�N�X�p�f�[�^
 *	@param	accessorie_no		�ǉ�����A�N�Z�T���i���o�[
 *	@param	x					X���W
 *	@param	y					Y���W
 *	@param	pri					�\���D�揇��
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s	�i�o�^�ő吔�ȏ�o�^���悤�Ƃ����j
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_AddAccessorieEasy( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, int pri )
{
	IMC_ACCE_ADD acce_add;
	IMC_ACCESSORIE_OBJ* acce_obj;
	
	// �ő�o�^���`�F�b�N
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// �A�N�Z�T����o�^���A���X�g�ɓo�^
		// �A�N�Z�T���o�^�f�[�^�쐬
		acce_add.objTbl		= rbox->boxDraw.acce;
		acce_add.SWSPsys	= rbox->boxDraw.SWSP_drawSys;
		acce_add.SWSPchar	= rbox->boxDraw.SWSP_charData[ accessorie_no ];
		acce_add.SWSPpltt	= rbox->boxDraw.SWSP_plttData[ IMC_DRAW_ACCESSORIE_PLTT_ID ];
		acce_add.m_x		= x;
		acce_add.m_y		= y;
		acce_add.accessorie_no = accessorie_no;
		acce_add.pltt_offs	= rbox->boxDraw.accePlttOfsTbl[ accessorie_no ];

		// �o�^
		acce_obj = IMC_ACCE_ObjAdd( &acce_add );

		// �\���D�揇�ʐݒ�
		IMC_ACCE_ObjDrawPrioritySet( acce_obj, pri );

		// ���X�g�I�u�W�F�쐬
		{
			IMC_OBJLIST* objList;

			objList = IMC_OBJLIST_MakeObjList( rbox->boxData.objListTbl, acce_obj, IMC_OBJLIST_ACCE );
			
			
			// ���X�g�̐擪�ɓo�^
			IMC_OBJLIST_Set( objList, &rbox->boxData.dummy );
		}

		//	�I�u�W�F�N�g���ǉ�
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̈ړ��ǉ�
 *
 *	@param	rbox		�E�{�b�N�X�p�f�[�^
 *	@param	acce_obj	�A�N�Z�T���f�[�^
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s	�i�o�^�ő吔�ȏ�o�^���悤�Ƃ����j
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_AddAccessorieMoveEasy( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj )
{
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// ���X�g�̐擪�ɓo�^
		IMC_OBJLIST_Set( acce_obj, &rbox->boxData.dummy );

		//	�I�u�W�F�N�g���ǉ�
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̐V�K�ǉ�
 *
 *	@param	rbox				�E�{�b�N�X�p�f�[�^
 *	@param	accessorie_no		�ǉ�����A�N�Z�T���i���o�[
 *	@param	x					X���W
 *	@param	y					Y���W
 *
 *	@retval	TRUE	����
 *	@retval FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_AddAccessorie( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, NNSG2dCharacterData** SWSP_UPchar )
{
	IMC_ACCE_ADD acce_add;
	IMC_ACCESSORIE_OBJ* acce_obj;
	
	// �ő�o�^���`�F�b�N
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// �A�N�Z�T����o�^���A���X�g�ɓo�^
		// �A�N�Z�T���o�^�f�[�^�쐬
		acce_add.objTbl		= rbox->boxDraw.acce;
		acce_add.SWSPsys	= rbox->boxDraw.SWSP_drawSys;
		acce_add.SWSPchar	= rbox->boxDraw.SWSP_charData[ accessorie_no ];
		acce_add.SWSPpltt	= rbox->boxDraw.SWSP_plttData[ IMC_DRAW_ACCESSORIE_PLTT_ID ];
		acce_add.m_x		= x;
		acce_add.m_y		= y;
		acce_add.accessorie_no = accessorie_no;
		acce_add.pltt_offs	= rbox->boxDraw.accePlttOfsTbl[ accessorie_no ];

		// �o�^
		acce_obj = IMC_ACCE_ObjAdd( &acce_add );

		// ���X�g�I�u�W�F�쐬
		{
			IMC_OBJLIST* objList;

			objList = IMC_OBJLIST_MakeObjList( rbox->boxData.objListTbl, acce_obj, IMC_OBJLIST_ACCE );
			
			
			// ���X�g�̐擪�ɓo�^
			ImcRightSetAcceList( rbox, objList, TRUE, SWSP_UPchar );
		}

		//	�I�u�W�F�N�g���ǉ�
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	[�ׂ��������@�C���[�W�N���b�v�쐬�V�X�e���ł͂��������Ă�]
 *	@brief	�A�N�Z�T���̈ړ��ǉ�
 *
 *	@param	rbox		�E�{�b�N�X�p�f�[�^
 *	@param	acce_obj	�A�N�Z�T���f�[�^
 *	@param	SWSP_UPchar			����p�L�����N�^�f�[�^
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s	�i�o�^�ő吔�ȏ�o�^���悤�Ƃ����j
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_AddAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj, NNSG2dCharacterData** SWSP_UPchar )
{
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// ���X�g�̐擪�ɓo�^
		ImcRightSetAcceList( rbox, acce_obj, TRUE, SWSP_UPchar );

		//	�I�u�W�F�N�g���ǉ�
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�j��
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	acce_obj	�j������A�N�Z�T��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_DeleteAccessorie( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj )
{
	// ���X�g����j��
	IMC_OBJLIST_Delete( acce_obj );
	
	// �A�N�Z�T���j��
	IMC_ACCE_ObjDelete( (IMC_ACCESSORIE_OBJ*)acce_obj->obj_data );

	// ���X�g��j��
	IMC_OBJLIST_DeleteObjList( acce_obj );
	
	//	�I�u�W�F�N�g���폜
	rbox->boxData.obj_count--;

	// �}�C�i�X�̒l�ɂȂ����炨������
	GF_ASSERT( rbox->boxData.obj_count >= 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ړ������邽�߂̃��X�g����̍폜
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	acce_obj	�ړ������邽�߂Ƀ��X�g����폜����A�N�Z�T���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_DeleteAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj )
{
	// ���X�g����j��
	IMC_OBJLIST_Delete( acce_obj );

	//	�I�u�W�F�N�g���폜
	rbox->boxData.obj_count--;
	// �}�C�i�X�̒l�ɂȂ����炨������
	GF_ASSERT( rbox->boxData.obj_count >= 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�^����Ă���A�N�Z�T���S�Ă��͂�
 *
 *	@param	rbox	�E�{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_DeleteAccessorieAll( IMC_RIGHT_BOX* rbox )
{
	IMC_OBJLIST_DeleteAll( &rbox->boxData.dummy );
	IMC_OBJLIST_DeleteAll( &rbox->boxData.dummy_poke );

	//	�I�u�W�F�N�g���폜
	rbox->boxData.obj_count = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X���̃X�v���C�g�ŕ\������Ă���I�u�W�F�N�g�𓮂���
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	x		�������l
 *	@param	y		�������l
 *	
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_ListMove( IMC_RIGHT_BOX* rbox, int x, int y )
{
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy, x, y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, x, y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����̏�̃A�N�Z�T���𓮂���
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_PokeUpListMove( IMC_RIGHT_BOX* rbox, int x, int y )
{
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, x, y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�{�b�N�X���X�g�̍��W��ݒ�
 *
 *	@param	rbox		�E�{�b�N�X
 *	@param	old_x		�O�͉�������ɂ��Ă����̂�
 *	@param	old_y
 *	@param	x			���ꂩ��͉�������ɂ���̂�
 *	@param	y 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_ListMatSet( IMC_RIGHT_BOX* rbox, int old_x, int old_y, int x, int y )
{
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy, -old_x, -old_y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy, x, y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, -old_x, -old_y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, x, y );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�̃A�N�Z�T���\���v���C�I���e�B��ݒ�
 *
 *	@param	rbox		�E�{�b�N�X 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_SetObjPriority( IMC_RIGHT_BOX* rbox )
{
	IMC_RBOX_SetObjPriorityMC( rbox, IMC_RBOX_ACCE_PRIORITY_START );
}
// �ׂ���
void IMC_RBOX_SetObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority )
{
	IMC_OBJLIST* work;

	// �擪����|�P�����܂�
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, priority );	
		}else{
			
			IMC_POKE_DrawPrioritySet( work->obj_data, priority );	
		}

		priority --;
			
		work = work->next;
	}

	priority -= 8;	// �����Ԋu��������@���`��h�~�̂���

	// �|�P�������牺
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, priority );	
		}else{
			
			IMC_POKE_DrawPrioritySet( work->obj_data, priority );	
		}

		priority --;
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�D�揇�ʑ����Z
 *
 *	@param	rbox
 *	@param	pri 
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_AddObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority )
{
	IMC_OBJLIST* work;
	int tmp_pri;

	// �擪����|�P�����܂�
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			tmp_pri = IMC_ACCE_ObjDrawPriorityGet( work->obj_data );
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}else{
			
			tmp_pri = IMC_POKE_DrawPriorityGet( work->obj_data );
			IMC_POKE_DrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}

		work = work->next;
	}

	// �|�P�������牺
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			tmp_pri = IMC_ACCE_ObjDrawPriorityGet( work->obj_data );
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}else{
			
			tmp_pri = IMC_POKE_DrawPriorityGet( work->obj_data );
			IMC_POKE_DrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}

		work = work->next;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l�����E�{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	rbox		�E�{�b�N�X�f�[�^
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_TPHit( IMC_RIGHT_BOX* rbox )
{
	TP_HIT_TBL	tp_hit;

	tp_hit.rect.top		= IMC_RBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_RBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK;

	return GF_TP_SingleHitCont( &tp_hit );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w����W���E�{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	rbox		�E�{�b�N�X�f�[�^
 *	@param	x			���肘���W
 *	@param	y			���肙���W
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_TPHitSelf( IMC_RIGHT_BOX* rbox, int x, int y )
{
	TP_HIT_TBL	tp_hit;

	tp_hit.rect.top		= IMC_RBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_RBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK;

	return GF_TP_SingleHitSelf( &tp_hit, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g���Ƃ̓����蔻����s��
 *
 *	@param	rbox	�E�{�b�N�X
 *
 *	@retval	��NULL	������A�N�Z�T��
 *	@retval	NULL	�Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_RBOX_TPHitObj( IMC_RIGHT_BOX* rbox )
{
	IMC_OBJLIST* work;
	BOOL	ret;

	// �擪�̃A�N�Z�T������
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		ret = IMC_OBJLIST_ACCEPOKE_Hit( work, IMC_OBJ_LIST_FUNC_TP_NOW, 0 );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}


	// �|�P�����̉��̃A�N�Z�T��
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		ret = IMC_OBJLIST_ACCEPOKE_Hit( work, IMC_OBJ_LIST_FUNC_TP_NOW, 0 );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}


	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����Ƃ̓����蔻����ׂ����s��
 *
 *	@param	rbox		�E�{�b�N�X
 *	@param	offset_x	�I�t�Z�b�g�����W
 *	@param	offset_y	�I�t�Z�b�g�����W
 *	@param	SWSP_UPchar	����L�����N�^�f�[�^�e�[�u��
 *
 *	@return	none
 *
 * �L�����N�^�f�[�^���Q�Ƃ��Ĕ����F�ł͂Ȃ����`�F�b�N
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_RBOX_TPHitObjEx( IMC_RIGHT_BOX* rbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar )
{
	IMC_OBJLIST* work;
	BOOL	ret;

	// �|�P�����̏�̃A�N�Z�T������
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		ret = IMC_OBJLIST_ACCEPOKE_HitEx( work, offset_x, offset_y, SWSP_UPchar );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}


	// �|�P�����̉��̃A�N�Z�T��
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		ret = IMC_OBJLIST_ACCEPOKE_HitEx( work, offset_x, offset_y, SWSP_UPchar );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG��\��
 *
 *	@param	rbox		�E�{�b�N�X
 *	@param	bg_num		�E�{�b�N�XBG�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_BGSet( IMC_RIGHT_BOX* rbox, int bg_num, int heap )
{
	IMC_BG_ADD add;
	
	// �o�^�f�[�^�ݒ�
	add.bg_ini		= rbox->boxDraw.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_RIGHT_CG_ARC_GET(bg_num);
	add.pltt_arc	= IMC_BG_RIGHT_CL_ARC_GET(bg_num);
	add.scrn_arc	= IMC_BG_RIGHT_SC_ARC_GET(bg_num);
	add.x			= IMC_RBOX_AREA_X;
	add.y			= IMC_RBOX_AREA_Y;
	add.frame		= GF_BGL_FRAME2_M;
	add.pltt_num	= IMC_RBOX_BG_PLTT_NUM;
	add.pltt_offs	= IMC_RBOX_BG_PLTT_OFFS;
	add.char_offs	= 0;
	add.heap		= heap;

	IMC_BG_MakaObj( &rbox->boxDraw.bg, &add );

	rbox->boxDraw.bg_no = bg_num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG���N���[������
 *
 *	@param	rbox		�E�{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_BGClean( IMC_RIGHT_BOX* rbox )
{
	IMC_BG_DeleteObj( &rbox->boxDraw.bg );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������W���擾
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_GetPokeMatrix( IMC_RIGHT_BOX* rbox, int* x, int* y )
{
	*x = SoftSpriteParaGet( rbox->boxDraw.poke.sprite, SS_PARA_POS_X );
	*y = SoftSpriteParaGet( rbox->boxDraw.poke.sprite, SS_PARA_POS_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ێ����Ă���A�N�Z�T�����擾
 *
 *	@param	rbox	�E�{�b�N�X
 *
 *	@return	�A�N�Z�T����
 */
//-----------------------------------------------------------------------------
int IMC_RBOX_GetNowHaveAcceNum( IMC_RIGHT_BOX* rbox )
{
	return rbox->boxData.obj_count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����̏�ɏ���Ă���A�N�Z�T�����H������ł���T�C�Y���擾
 *
 *	@param	rbox		�E�{�b�N�X���[�N
 *	@param	enc_x		�H������ł�T�C�Y��
 *	@param	enc_y		�H������ł�T�C�Y��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_GetPokeUpListEncSize( IMC_RIGHT_BOX* rbox, int* enc_x, int* enc_y )
{
	int enc_x_max;
	int enc_y_max;
	int enc_x_w;
	int enc_y_w;
	IMC_OBJLIST* work;

	work = rbox->boxData.dummy_poke.next;
	enc_x_max = 0;
	enc_y_max = 0;
	while( work != &rbox->boxData.dummy_poke ){
		imcRbox_GetAcceEncSize( work, &enc_x_w, &enc_y_w );

		if(MATH_ABS(enc_x_w) > MATH_ABS(enc_x_max) ){
			enc_x_max = enc_x_w;
		}
		if( MATH_ABS(enc_y_w) > MATH_ABS(enc_y_max) ){
			enc_y_max = enc_y_w;
		}

		work = work->next;
	}

	*enc_x = enc_x_max;
	*enc_y = enc_y_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�{�b�N�X�@�F�ݒ�
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	color	�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_SetObjColor( IMC_RIGHT_BOX* rbox, GXRgb color )
{
	IMC_OBJLIST* work;

	// �|�P�����̏�̃A�N�Z�T������
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			IMC_ACCESSORIE_OBJ* p_obj = work->obj_data;
			SWSP_SetSpriteDiffColor( p_obj->drawObj, color );
		}else{
			IMC_POKE* p_obj = work->obj_data;
			SoftSpriteParaSet( p_obj->sprite, SS_PARA_DIFF_R, (color >> 10) & 0x1f );
			SoftSpriteParaSet( p_obj->sprite, SS_PARA_DIFF_G, (color >> 5) & 0x1f );
			SoftSpriteParaSet( p_obj->sprite, SS_PARA_DIFF_B, (color >> 0) & 0x1f );
		}
		work = work->next;
	}

	// �|�P�����̉��̃A�N�Z�T��
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){
		IMC_ACCESSORIE_OBJ* p_obj = work->obj_data;
		SWSP_SetSpriteDiffColor( p_obj->drawObj, color );
		work = work->next;
	}
}







//----------------------------------------------------------------------------
/**
 *	@brief	�ォ���ɃA�N�Z�T����ݒ肷��
 *
 *	@param	p_data			�{�b�N�X�f�[�^
 *	@param	objList			�A�N�Z�T���f�[�^
 *	@param	top_bottom		TRUE�@�擪�@BOTTOM�@�Ō��
 *	@param	SWSP_UPchar			����p�L�����N�^�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ImcRightSetAcceList( IMC_RIGHT_BOX* p_data, IMC_OBJLIST* objList, BOOL top_bottom, NNSG2dCharacterData** SWSP_UPchar  )
{
	int i;
	int x;
	int y;
	int size_x;
	int size_y;
	int in_size_x;
	int in_size_y;
	int top;
	int bottom;
	int left;
	int right;
	int ch_x, ch_y;
	BOOL check;
	NNSG2dCharacterData* char_data;
	
	// ���W���擾
	IMC_OBJLIST_ACCEPOKE_MatGet( objList, &x, &y );

	// �T�C�Y���擾
	IMC_OBJLIST_ACCEPOKE_SizeGet( objList, &size_x, &size_y );

	// �H������ł悢�T�C�Y�擾
	IMC_OBJLIST_ACCEPOKE_InSizeGet( objList, &in_size_x, &in_size_y );

	top = y + in_size_y;
	bottom = y + size_y - in_size_y;
	left = x + in_size_x;
	right = x + size_x - in_size_x;

	
	// �L�����N�^�f�[�^�擾
	char_data = SWSP_UPchar[ IMC_DRAW_POKE_CHAR_ID ];
	
	// �|�P�����G���A�Ɉ��������邩�`�F�b�N
	// 16�_�`�F�b�N����
	check = FALSE;
	for( i=0; i<16; i++ ){
		IMC_CALC_HitPoint16Get( top, bottom, left, right, i, &ch_x, &ch_y );
		check  |= IMC_POKE_TPHitExSelf( &p_data->boxDraw.poke, ch_x, ch_y, char_data );
	}

	
	// �|�P�����̏�Ȃ�|�P�����̏ナ�X�g��
	if( check ){
		
		if( top_bottom ){
			// �擪�ɓo�^
			IMC_OBJLIST_Set( objList, &p_data->boxData.dummy_poke );
		}else{
			// �Ō���ɓo�^
			IMC_OBJLIST_Set( objList, p_data->boxData.dummy_poke.prev );
		}
	}else{

		if( top_bottom ){
			// �擪�ɓo�^
			IMC_OBJLIST_Set( objList, &p_data->boxData.dummy );
		}else{
			// �Ō���ɓo�^
			IMC_OBJLIST_Set( objList, p_data->boxData.dummy.prev );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���H�����݃T�C�Y�@�擾
 *
 *	@param	objlist		�A�N�Z�T�����X�g
 *	@param	enc_x		�H�����݂��T�C�Y
 *	@param	enc_y		�H�����݂��T�C�Y
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcRbox_GetAcceEncSize( IMC_OBJLIST* objlist, int* enc_x, int* enc_y )
{
	int size_x,size_y;			// �I�u�W�F�N�g�T�C�YXY
	int mat_x, mat_y;			// �I�u�W�F�N�g���W
	int in_size_x, in_size_y;	// �H������ł悢�T�C�YXY
	int top, bottom, left, right;// �㉺�E��
	int in_top, in_bottom, in_left, in_right;// �H�����ݏ㉺�E��

	IMC_OBJLIST_ACCEPOKE_SizeGet( objlist, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( objlist, &mat_x, &mat_y );
	IMC_OBJLIST_ACCEPOKE_InSizeGet( objlist, &in_size_x, &in_size_y );
	
	top		= mat_y + in_size_y;
	bottom	= mat_y + size_y - in_size_y;
	left	= mat_x + in_size_x;
	right	= mat_x + size_x - in_size_x;


	// �E�{�b�N�X��`�O�ɂǂ̂��炢�H������ł��邩���`�F�b�N
	// �v���X���H������ł���T�C�Y�@�}�C�i�X��OK
	in_left		= IMC_RBOX_AREA_X_MOVEOK - left;
	in_right	= right - (IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK);
	in_top		= IMC_RBOX_AREA_Y_MOVEOK - top;
	in_bottom	= bottom - (IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK);

	// �H������ł���T�C�Y��Ԃ�
	if( in_left > 0 ){
		*enc_x = in_left;
	}else if( in_right > 0 ){
		*enc_x = -in_right;
	}else{
		*enc_x = 0;
	}
	if( in_top > 0 ){
		*enc_y = in_top;
	}else if( in_bottom > 0 ){
		*enc_y = -in_bottom;
	}else{
		*enc_y = 0;
	}
}
