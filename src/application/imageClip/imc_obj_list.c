//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_obj_list.c
 *	@brief		�I�u�W�F�N�g���X�g	�\���D�揇�ʁ@�^�b�`�p�l������D�揇�ʂȂǂ��Ǘ�
 *	@author		tomoya takahashi 
 *	@data		2005.09.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define	__IMC_OBJLIST_H_GLOBAL
#include "include/application/imageClip/imc_obj_list.h"

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

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���X�g�e�[�u����������
 *
 *	@param	tbl		�I�u�W�F���X�g�e�[�u�����Ԃ̃|�C���^
 *	@param	num		�Ǘ��������I�u�W�F�N�g��
 *	@param	heap	�g�p����q�[�vID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_TblInit( IMC_OBJLIST_TBL* tbl, int num, int heap )
{	
	tbl->plist = sys_AllocMemory( heap, sizeof(IMC_OBJLIST) * num );
	GF_ASSERT( tbl->plist );
	memset( tbl->plist, 0, sizeof(IMC_OBJLIST) * num );
	tbl->num	= num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���X�g�e�[�u���̔j��
 *
 *	@param	tbl		�I�u�W�F�N�g���X�g�e�[�u�����Ԃ̃|�C���^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_TblDelete( IMC_OBJLIST_TBL* tbl )
{
	sys_FreeMemoryEz( tbl->plist );
	tbl->plist = NULL;
	tbl->num = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���X�g�f�[�^�쐬
 *
 *	@param	tbl		�I�u�W�F���X�g�e�[�u��
 *	@param	work	�I�u�W�F���[�N
 *	@param	flag	�I�u�W�F�̒萔	�i�d�����Ӂj
 *
 *	@return	IMC_OBJLIST*	�I�u�W�F���X�g
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_OBJLIST_MakeObjList( IMC_OBJLIST_TBL* tbl, void* work, int flag )
{
	int i;
	
	GF_ASSERT( tbl->plist );
	GF_ASSERT( tbl->num );

	for(i=0; i<tbl->num; i++){
		if(tbl->plist[ i ].obj_data == NULL){
			break;
		}
	}
	GF_ASSERT( tbl->num > i );

	tbl->plist[ i ].obj_data	= work;
	tbl->plist[ i ].flag		= flag; 

	return (tbl->plist + i);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���X�g�f�[�^�j��
 *
 *	@param	obj		�j������I�u�W�F���X�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_DeleteObjList( IMC_OBJLIST* obj )
{
	memset( obj,0,sizeof(IMC_OBJLIST) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g�ɐݒ肷��	
 *
 *	@param	work			�f�[�^��ݒ肷�郏�[�N
 *	@param	dummy			�O�̃f�[�^
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_Set( IMC_OBJLIST* work, IMC_OBJLIST* prev )
{
	work->next = prev->next;
	prev->next->prev = work;
	work->prev = prev;
	prev->next = work;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g����폜
 *
 *	@param	obj		�폜���郊�X�g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_Delete( IMC_OBJLIST* obj )
{
	obj->prev->next = obj->next;
	obj->next->prev = obj->prev;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�擪�_�~�[�f�[�^�ɂȂ����Ă���t�@�C����S�Ĕj������
 *
 *	@param	dummy	�_�~�[�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_DeleteAll( IMC_OBJLIST* dummy )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* next;

	work = dummy->next;
	while( work != dummy ){
		next = work->next;
		
		IMC_OBJLIST_Delete( work );
		IMC_OBJLIST_DeleteObjList( work );

		work = next;
	}
}
