//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_hblank.c
 *	@brief		�t�B�[���hHBlank�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.04.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define	__FIELD_HBLANK_H_GLOBAL
#include "field_hblank.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//
//	H�u�����N���ԓ��ɓ��삷��I�u�W�F�N�g��
//
//=====================================
#define FIELD_HBLANK_WORK_NUM	 ( 2 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	H�u�����N���ԃ��[�N
//=====================================
typedef struct _FIELD_HBLANK_OBJ{
	u32	status;
	void* p_work;
	FLDHBLANK_FUNC func;
};

//-------------------------------------
//	H�u�����N���ԊǗ��V�X�e��
//=====================================
typedef struct _FIELD_HBLANK_SYS{
	u32	status;
	FIELD_HBLANK_OBJ work[ FIELD_HBLANK_WORK_NUM ];
} ;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void FldHblank_InitSys( FIELD_HBLANK_SYS* p_sys );
static void FldHblank_InitObj( FIELD_HBLANK_OBJ* p_obj );
static void Field_Sys_HBlank( void* p_work );
static void Field_Sys_DummyCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work );

static FIELD_HBLANK_OBJ* FldHblank_GetCleanObj( FIELD_HBLANK_SYS* p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	�y�Ǘ��V�X�e���z�������֐�
 *	@param	heap 
 *	@return	�쐬�����y�Ǘ��V�X�e���z
 */
//-----------------------------------------------------------------------------
FIELD_HBLANK_SYS* FLDHBLANK_SYS_Init( u32 heap )
{
	FIELD_HBLANK_SYS* p_sys;

	// �������m��
	p_sys = sys_AllocMemory( heap, sizeof(FIELD_HBLANK_SYS) );
	FldHblank_InitSys( p_sys );

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�y�Ǘ��V�X�e���z�j������
 *	@param	p_sys	�y�Ǘ��V�X�e���z
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_SYS_Delete( FIELD_HBLANK_SYS* p_sys )
{
	if( p_sys == NULL ){ return ; }
	
	// HBlank���荞�݂̉���
	if( p_sys->status == FIELD_HBLANK_STATE_DO ){
		FLDHBLANK_SYS_Stop( p_sys );
	}

	// �Ǘ��f�[�^�N���[��
	FldHblank_InitSys( p_sys );
	
	// �S�̃��[�N�j��
	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�y�Ǘ��V�X�e���zHBlank����	�X�^�[�g�@HBLANK���荞�ݐݒ�
 *	@param	p_sys	�y�Ǘ��V�X�e���z
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_SYS_Start( FIELD_HBLANK_SYS* p_sys )
{
	BOOL result;
	result = sys_HBlankIntrSet( Field_Sys_HBlank, p_sys );
	// �ݒ莸�s
	GF_ASSERT( result == TRUE );

	p_sys->status = FIELD_HBLANK_STATE_DO;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�y�Ǘ��V�X�e���zHBlank�����I��	HBLANK���荞�݂̉���
 *	@param	p_sys	�y�Ǘ��V�X�e���z
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_SYS_Stop( FIELD_HBLANK_SYS* p_sys )
{
	BOOL result;
	result = sys_HBlankIntrSet( NULL, NULL );
	// �ݒ莸�s
	GF_ASSERT( result == TRUE );

	p_sys->status = FIELD_HBLANK_STATE_STANDBY;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�y�Ǘ��V�X�e���z�̏�Ԃ��擾
 *	@param	cp_sys	�y�Ǘ��V�X�e���z
 *
 *	@return	FIELD_HBLANK_STATE_STANDBY	�J�n�҂�
 *	@return	FIELD_HBLANK_STATE_DO		���s��
 */
//-----------------------------------------------------------------------------
u32 FLDHBLANK_SYS_GetState( const FIELD_HBLANK_SYS* cp_sys )
{
	return cp_sys->status;
}

//-----------------------------------------------------------------------------
/**
 *					�y�I�u�W�F�N�g�z�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�y�I�u�W�F�N�g�z�o�^
 *	@param	p_sys		�y�Ǘ��V�X�e���z
 *	@param	func		�R�[���o�b�N�֐�
 *	@param	p_work		���[�N
 *
 *	@return	�쐬���ꂽ�y�I�u�W�F�N�g�z	NULL�̎����s�i�ő吔�o�^�ς݁j
 */
//-----------------------------------------------------------------------------
FIELD_HBLANK_OBJ* FLDHBLANK_OBJ_Add( FIELD_HBLANK_SYS* p_sys, FLDHBLANK_FUNC func, void* p_work )
{
	FIELD_HBLANK_OBJ* p_obj;
	p_obj = FldHblank_GetCleanObj( p_sys );
	// �o�^���s�@�@�ő吔�𒴂����o�^�����悤�Ƃ��܂���
	GF_ASSERT( p_obj );
	if( p_obj ){
		p_obj->p_work	= p_work;
		p_obj->func		= func;
		p_obj->status	= FIELD_HBLANK_STATE_DO;
	}
	return p_obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�y�I�u�W�F�N�g�z�j��
 *	@param	p_obj	�y�I�u�W�F�N�g�z
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_OBJ_Delete( FIELD_HBLANK_OBJ* p_obj )
{
	FldHblank_InitObj( p_obj );
}



//-----------------------------------------------------------------------------
/**
 *		���[�J���֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����[�N������
 *	@param	p_sys	�Ǘ��V�X�e��
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldHblank_InitSys( FIELD_HBLANK_SYS* p_sys )
{
	int i;
	memset( p_sys, 0, sizeof(FIELD_HBLANK_SYS) );
	p_sys->status = FIELD_HBLANK_STATE_STANDBY;
	for( i=0; i<FIELD_HBLANK_WORK_NUM; i++ ){
		FldHblank_InitObj( &p_sys->work[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g���[�N������
 *	@param	p_obj	�I�u�W�F�N�g
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldHblank_InitObj( FIELD_HBLANK_OBJ* p_obj )
{
	// ���̏��������s���Ă���Ƃ���H�u�����N���Ԃ����邱�Ƃ��l��
	// ���[�N�̏���������ԉ��ɂ���
	p_obj->status = FIELD_HBLANK_STATE_STANDBY;
	p_obj->func	  = Field_Sys_DummyCallBack;
	p_obj->p_work = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N�֐�
 *	@param	p_work	���[�N
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Field_Sys_HBlank( void* p_work )
{
	int i;
	FIELD_HBLANK_SYS* p_sys = p_work;

	for( i=0; i<FIELD_HBLANK_WORK_NUM; i++ ){
		p_sys->work[i].func( &p_sys->work[i], p_sys->work[i].p_work );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�[���o�b�N�֐��������p�@�_�~�[�R�[���o�b�N
 *	@param	p_obj		�I�u�W�F
 *	@param	p_work		���[�N
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Field_Sys_DummyCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	�󂢂Ă���I�u�W�F�N�g���[�N���擾
 *
 *	@param	p_sys	�V�X�e�����[�N
 *
 *	@return	�I�u�W�F�N�g���[�N	NULL�@�ő吔�g�p��
 */
//-----------------------------------------------------------------------------
static FIELD_HBLANK_OBJ* FldHblank_GetCleanObj( FIELD_HBLANK_SYS* p_sys )
{
	int i;
	for( i=0; i<FIELD_HBLANK_WORK_NUM; i++ ){
		if( p_sys->work[i].status == FIELD_HBLANK_STATE_STANDBY ){
			return &p_sys->work[i];
		}
	}
	return NULL;
}

