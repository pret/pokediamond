//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_obj_list_func.c
 *	@brief		��R�̃V�X�e�����g�p����I�u�W�F���X�g�p�֐���錾
 *	@author		tomoya takahashi 
 *	@data		2005.09.30
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "system.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_poke_obj.h"

#define __IMC_OBJ_LIST_FUNC_H_GLOBAL
#include "include/application/imageClip/imc_obj_list_func.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

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


//-----------------------------------------------------------------------------
/**
*	�A�N�Z�T���ƃ|�P�����I�u�W�F�̕\���D�揇�ʁA�����蔻��A���W�ύX
*	���s���֐�
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\���D�揇�ʐݒ�
 *
 *	@param	work	�I�u�W�F���X�g���[�N
 *	@param	pri		�\���D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_Pri( IMC_OBJLIST* work, int pri )
{
	if( work->flag < IMC_OBJLIST_POKE ){
		// �A�N�Z�T��
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		IMC_ACCE_ObjDrawPrioritySet( acce, pri );
	}else{
		// �|�P����
		IMC_POKE* poke = work->obj_data;
		IMC_POKE_DrawPrioritySet( poke, pri );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l�������蔻��
 *
 *	@param	work	�I�u�W�F���X�g���[�N
 *	@param	x		����X
 *	@param	y		����Y
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_OBJLIST_ACCEPOKE_Hit( IMC_OBJLIST* work, int x, int y )
{
	if( work->flag < IMC_OBJLIST_POKE ){
		// �A�N�Z�T��
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		
		if(x == IMC_OBJ_LIST_FUNC_TP_NOW){
			return IMC_ACCE_ObjTpHit( acce );
		}else{
			return IMC_ACCE_ObjTpHitSelf( acce, x, y );
		}
	}	
	
	// �|�P����
	{
		IMC_POKE* poke = work->obj_data;

		if(x == IMC_OBJ_LIST_FUNC_TP_NOW){
			return IMC_POKE_TPHit( poke );
		}else{
			return IMC_POKE_TPHitSelf( poke, x, y );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ׂ����^�b�`�p�l�������蔻��
 *
 *	@param	work		�I�u�W�F���X�g���[�N
 *	@param	offs_x		���ォ��̃I�t�Z�b�g�����W
 *	@param	offs_y		���ォ��̃I�t�Z�b�g�����W 
 *	@param	drawData	�L�����N�^�f�[�^
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_OBJLIST_ACCEPOKE_HitEx( IMC_OBJLIST* work, int* offs_x, int* offs_y, NNSG2dCharacterData** drawData )
{
	NNSG2dCharacterData* char_data;

	if( work->flag == IMC_OBJLIST_ACCE ){
		// �A�N�Z�T��
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
	
		// �L�����N�^�f�[�^�擾
		char_data = drawData[ acce->accessorie_no ];

		return IMC_ACCE_ObjTpHitEx( acce, offs_x, offs_y, char_data );
	}	
	
	if( work->flag == IMC_OBJLIST_BG ){
		// BG�T���l�C��
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		int char_no = IMC_BG_THUMB_CHAR_CONT_ID( acce->accessorie_no );
	
		// �L�����N�^�f�[�^�擾
		char_data = drawData[ char_no ];

		return IMC_ACCE_ObjTpHitEx( acce, offs_x, offs_y, char_data );
	}	
	
	if( work->flag == IMC_OBJLIST_SND ){
		// ���T���l�C��
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		int char_no = IMC_SND_THUMB_CHAR_CONT_ID( acce->accessorie_no );
	
		// �L�����N�^�f�[�^�擾
		char_data = drawData[ char_no ];
	
		return IMC_ACCE_ObjTpHitEx( acce, offs_x, offs_y, char_data );
	}	
	
	// �|�P����
	{
		IMC_POKE* poke = work->obj_data;

		// �L�����N�^�f�[�^�擾
		char_data = drawData[ IMC_DRAW_POKE_CHAR_ID ];

		return IMC_POKE_TPHitEx( poke, offs_x, offs_y, char_data );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W�ݒ�
 *
 *	@param	work	�I�u�W�F�N�g���X�g���[�N
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_Mat( IMC_OBJLIST* work, int x, int y )
{
	if( work->flag < IMC_OBJLIST_POKE ){
		// �A�N�Z�T��
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		IMC_ACCE_ObjSetMat( acce, x, y );
	}else{
		// �|�P����
		IMC_POKE* poke = work->obj_data;
		int size_x, size_y;		// �T�C�Y
		// ������W�ɂ���
		IMC_POKE_SizeGet( poke, &size_x, &size_y );
		size_x /= 2;
		size_y /= 2;
		x += size_x;
		y += size_y;

		IMC_POKE_MatrixSet( poke, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W���擾
 *
 *	@param	obj		�I�u�W�F���[�N
 *	@param	x		�����W�i�[��
 *	@param	y		�����W�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_MatGet( IMC_OBJLIST* obj, int* x, int* y )
{
	if( obj->flag < IMC_OBJLIST_POKE ){
		// �A�N�Z�T��
		IMC_ACCESSORIE_OBJ* acce = obj->obj_data;
		IMC_ACCE_ObjGetMat( acce, x, y );
	}else{
		// �|�P����
		IMC_POKE* poke = obj->obj_data;
		int size_x, size_y;		// �T�C�Y
		
		IMC_POKE_MatrixGet( poke, x, y );

		// ������W�ɂ���
		IMC_POKE_SizeGet( poke, &size_x, &size_y );
		size_x /= 2;
		size_y /= 2;
		*x -= size_x;
		*y -= size_y;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�C�Y���擾
 *
 *	@param	obj		�I�u�W�F���[�N
 *	@param	x		���T�C�Y�i�[��
 *	@param	y		���T�C�Y�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_SizeGet( IMC_OBJLIST* obj, int* x, int* y )
{
	if( obj->flag < IMC_OBJLIST_POKE ){
		// �A�N�Z�T��
		IMC_ACCESSORIE_OBJ* acce = obj->obj_data;
		IMC_ACCE_ObjGetSize( acce, x, y );
	}else{
		// �|�P����
		IMC_POKE* poke = obj->obj_data;
		IMC_POKE_SizeGet( poke, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�H������ł悢�T�C�Y���擾
 *
 *	@param	obj		�I�u�W�F���[�N
 *	@param	x		���T�C�Y�i�[��
 *	@param	y		���T�C�Y�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_InSizeGet( IMC_OBJLIST* obj, int* x, int* y )
{
	if( obj->flag < IMC_OBJLIST_POKE ){
		// �A�N�Z�T��
		IMC_ACCESSORIE_OBJ* acce = obj->obj_data;
		IMC_ACCE_ObjInSizeGet( acce, x, y );
	}else{
		// �|�P����
		IMC_POKE* poke = obj->obj_data;
		IMC_POKE_InSizeGet( poke, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g���Ƒ����Z�ړ�������
 *	
 *	@param	top		���X�g�擪�|�C���^
 *	@param	x		����X���W
 *	@param	y		����Y���W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_ListMove( IMC_OBJLIST* top, int x, int y )
{
	IMC_OBJLIST* work;
	int mat_x, mat_y;

	
	work = top->next;
	while( work != top ){

		IMC_OBJLIST_ACCEPOKE_MatGet( work, &mat_x, &mat_y );

		mat_x += x;
		mat_y += y;
		
		IMC_OBJLIST_ACCEPOKE_Mat( work, mat_x, mat_y );
		
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g��`�擾�@�H������ł悢�T�C�Y�����炵�ς�
 *	
 *	@param	p_obj	���[�N
 *	@param	top		��
 *	@param	bottom	��
 *	@param	left	��
 *	@param	right	�E
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_GetObjRectSubInSize( IMC_OBJLIST* p_obj, int* top, int* bottom, int* left, int* right )
{
	int size_x,size_y;			// �I�u�W�F�N�g�T�C�YXY
	int mat_x, mat_y;			// �I�u�W�F�N�g���W
	int in_size_x, in_size_y;	// �H������ł悢�T�C�YXY


	IMC_OBJLIST_ACCEPOKE_SizeGet( p_obj, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( p_obj, &mat_x, &mat_y );
	IMC_OBJLIST_ACCEPOKE_InSizeGet( p_obj, &in_size_x, &in_size_y );
	
	*top	= mat_y + in_size_y;
	*bottom	= mat_y + size_y - in_size_y;
	*left	= mat_x + in_size_x;
	*right	= mat_x + size_x - in_size_x;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���S���W���擾����
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *	@param	x		�����W�i�[��
 *	@param	y		�����W�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_GetObjCenterMat( IMC_OBJLIST* p_obj, int* x, int* y )
{
	int size_x,size_y;			// �I�u�W�F�N�g�T�C�YXY
	int mat_x, mat_y;			// �I�u�W�F�N�g���W

	IMC_OBJLIST_ACCEPOKE_SizeGet( p_obj, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( p_obj, &mat_x, &mat_y );

	*x = mat_x + (size_x/2);
	*y = mat_y + (size_y/2);
}

