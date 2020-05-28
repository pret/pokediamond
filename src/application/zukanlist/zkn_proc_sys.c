//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_proc_sys.c
 *	@brief		�}�ӏ�������V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define __ZKN_PROC_SYS_H_GLOBAL
#include "include/application/zukanlist/zkn_proc_sys.h"

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
//	�}�Ӄv���Z�X�V�X�e���̏����̗���
//=====================================
enum{
	ZKN_PROC_MAINSEQ_DO_INIT,			// �f�[�^�ύX�����̏�����
	ZKN_PROC_MAINSEQ_DRAW_INIT,			// �`�揈�����������t�F�[�h�C��
	ZKN_PROC_MAINSEQ_MAIN,				// ���C��
	ZKN_PROC_MAINSEQ_DRAW_DELETE,		// �`�揈���j�����t�F�[�h�A�E�g
	ZKN_PROC_MAINSEQ_DO_DELETE,			// �f�[�^�ύX�����j��
	ZKN_PROC_MAINSEQ_ALL_END,			// �S�Ă̏������I���܂���
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�V�X�e��
 */
//-----------------------------------------------------------------------------
typedef struct _ZKN_PROC_SYS{
	// �O���[�o���f�[�^
	void* p_glb_data;	// �Ǘ��҂���󂯎��O���[�o���f�[�^
	void* p_glb_draw;	// �Ǘ��҂���󂯎��O���[�o���f�[�^

	// �S�̂̏����̗���
	int	main_seq;

	// �f�[�^���́��X�V����
	ZKN_PROC_DO_DATA	do_data;						// �������[�N
	ZKN_PROC_DO_FUNC	do_func[ ZKN_PROC_FUNC_NUM ];	// �e�����֐�

	// �`�揈��
	ZKN_PROC_DRAW_DATA	draw_data;						// �������[�N
	ZKN_PROC_DRAW_FUNC	draw_func[ ZKN_PROC_FUNC_NUM ];	// �e�����֐�

	// ���̑�
	int heap;				// �g�p����q�[�v
} ZKN_PROC_SYS;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void InitProcDoData( ZKN_PROC_DO_DATA* data );
static void InitProcDrawData( ZKN_PROC_DRAW_DATA* data );

static int DoFuncProcDo( ZKN_PROC_DO_FUNC func, ZKN_PROC_DO_DATA* p_do_data, void* p_glb_data );
static int DoFuncProcDraw( ZKN_PROC_DRAW_FUNC func, void* p_glb_draw, ZKN_PROC_DRAW_DATA* p_draw_data, const void* cp_glb_data, const ZKN_PROC_DO_DATA* cp_do_data );

//-----------------------------------------------------------------------------
/**
 *
 *				������
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������m��
 *
 *	@param	heap	�q�[�v
 *
 *	@return	�m�ۂ��ď������ς݂̃v���Z�X�V�X�e��
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_PROC_MemoryAlloc( int heap )
{
	ZKN_PROC_SYS_PTR proc;

	proc = sys_AllocMemory( heap, sizeof(ZKN_PROC_SYS) );
	GF_ASSERT( proc );
	memset( proc, 0, sizeof(ZKN_PROC_SYS) );

	proc->main_seq = ZKN_PROC_MAINSEQ_ALL_END;
	proc->heap = heap;

	return proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����������
 *
 *	@param	proc		�v���Z�X�V�X�e��
 *	@param	cp_init		�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PROC_Init( ZKN_PROC_SYS_PTR proc, const ZKN_PROC_INIT* cp_init )
{
	GF_ASSERT( proc );
	GF_ASSERT( cp_init );

	// �I�����Ă��Ȃ��̂ɏ��������悤�Ƃ���
	GF_ASSERT( ZKN_PROC_EndCheck(proc) );

	// �v���Z�X�f�[�^�̑��
	proc->p_glb_data = cp_init->p_glb_data;		// �O���[�o���f�[�^
	proc->p_glb_draw = cp_init->p_glb_draw;		// �O���[�o���f�[�^
	proc->main_seq	 = ZKN_PROC_FUNC_INIT;		// ���C���V�[�P���X
	InitProcDoData( &proc->do_data );			// �f�[�^�ύX�����p���[�N
	proc->do_data.heap = proc->heap;
	InitProcDrawData( &proc->draw_data );		// �`�揈���p���[�N
	proc->draw_data.heap = proc->heap;

	// �֐��|�C���^���
	proc->do_func[ ZKN_PROC_FUNC_INIT ] = cp_init->cp_do_func[ ZKN_PROC_FUNC_INIT ];
	proc->do_func[ ZKN_PROC_FUNC_MAIN ] = cp_init->cp_do_func[ ZKN_PROC_FUNC_MAIN ];
	proc->do_func[ ZKN_PROC_FUNC_DELETE ] = cp_init->cp_do_func[ ZKN_PROC_FUNC_DELETE ];
	proc->draw_func[ ZKN_PROC_FUNC_INIT ] = cp_init->cp_draw_func[ ZKN_PROC_FUNC_INIT ];
	proc->draw_func[ ZKN_PROC_FUNC_MAIN ] = cp_init->cp_draw_func[ ZKN_PROC_FUNC_MAIN ];
	proc->draw_func[ ZKN_PROC_FUNC_DELETE ] = cp_init->cp_draw_func[ ZKN_PROC_FUNC_DELETE ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���C������
 *
 *	@param	proc	�v���Z�X�V�X�e��
 *
 *	@retval	ZKN_PROC_TRUE		�S�Ĕj�����ď������I���܂����B
 *	@retval	ZKN_PROC_FALSE		����
 *
 *
 */
//-----------------------------------------------------------------------------
int ZKN_PROC_Main( ZKN_PROC_SYS_PTR proc )
{
	int ret;

	GF_ASSERT( proc );

	switch( proc->main_seq ){

	//-------------------------------------
	// �f�[�^�ύX�����̏�����
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_INIT:			
		ret = DoFuncProcDo( proc->do_func[ ZKN_PROC_FUNC_INIT ], &proc->do_data, proc->p_glb_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
			proc->do_data.seq = 0;
		}
		break;
		
	//-------------------------------------
	// �`�揈�����������t�F�[�h�C��
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_INIT:			
		break;
		
	//-------------------------------------
	// ���C��
	//=====================================
	case ZKN_PROC_MAINSEQ_MAIN:				
		// �f�[�^�ύX
		ret = DoFuncProcDo( proc->do_func[ ZKN_PROC_FUNC_MAIN ], &proc->do_data, proc->p_glb_data );

		// �f�[�^�ύX���I���Ȃ�I���
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
			proc->do_data.seq = 0;
			proc->draw_data.seq = 0;
		}
		break;
		
	//-------------------------------------
	// �`�揈���j�����t�F�[�h�A�E�g
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_DELETE:		
		break;
		
	//-------------------------------------
	// �f�[�^�ύX�����j��
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_DELETE:			
		ret = DoFuncProcDo( proc->do_func[ ZKN_PROC_FUNC_DELETE ], &proc->do_data, proc->p_glb_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
		}
		break;
		
	//-------------------------------------
	//	�S�����ύX
	//=====================================
	case ZKN_PROC_MAINSEQ_ALL_END:			// �S�Ă̏������I���܂���
		return ZKN_PROC_TRUE;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT(0);
		break;
	}
	
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 *
 *	@param	proc	�v���Z�X�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		�S�Ĕj�����ď������I���܂����B
 *	@retval	ZKN_PROC_FALSE		����
 */
//-----------------------------------------------------------------------------
int ZKN_PROC_Draw( ZKN_PROC_SYS_PTR proc )
{
	int ret;

	GF_ASSERT( proc );

	switch( proc->main_seq ){

	//-------------------------------------
	// �f�[�^�ύX�����̏�����
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_INIT:			
		break;
		
	//-------------------------------------
	// �`�揈�����������t�F�[�h�C��
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_INIT:			
		ret = DoFuncProcDraw( proc->draw_func[ ZKN_PROC_FUNC_INIT ], proc->p_glb_draw, &proc->draw_data, proc->p_glb_data, &proc->do_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
			proc->draw_data.seq = 0;
		}
		break;
		
	//-------------------------------------
	// ���C��
	//=====================================
	case ZKN_PROC_MAINSEQ_MAIN:				
		
		// �`��
		DoFuncProcDraw( proc->draw_func[ ZKN_PROC_FUNC_MAIN ], proc->p_glb_draw, &proc->draw_data, proc->p_glb_data, &proc->do_data );
		break;
		
	//-------------------------------------
	// �`�揈���j�����t�F�[�h�A�E�g
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_DELETE:		
		ret = DoFuncProcDraw( proc->draw_func[ ZKN_PROC_FUNC_DELETE ], proc->p_glb_draw, &proc->draw_data, proc->p_glb_data, &proc->do_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
		}
		break;
		
	//-------------------------------------
	// �f�[�^�ύX�����j��
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_DELETE:			
		break;
		
	//-------------------------------------
	//	�S�����ύX
	//=====================================
	case ZKN_PROC_MAINSEQ_ALL_END:			// �S�Ă̏������I���܂���
		return ZKN_PROC_TRUE;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT(0);
		break;
	}
	
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C������lock
 *
 *	@param	proc	�v���b�N���C��
 *	@param	lock	����lock�t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_PROC_MoveLock( ZKN_PROC_SYS_PTR proc, BOOL lock )
{
	proc->do_data.lock = lock;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�����N�G�X�g���o��
 *
 *	@param	proc	�v���Z�X�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PROC_EndReq( ZKN_PROC_SYS_PTR proc )
{
	GF_ASSERT( proc );

	proc->do_data.end_req = TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I���`�F�b�N
 *
 *	@param	proc	�`�F�b�N����v���Z�X�V�X�e��
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	���s��
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_PROC_EndCheck( ZKN_PROC_SYS_PTR proc )
{
	GF_ASSERT( proc );

	if( proc->main_seq == ZKN_PROC_MAINSEQ_ALL_END ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�����삵�Ă��邩�`�F�b�N
 *
 *	@param	proc	�v���Z�X�V�X�e��
 *
 *	@retval	TRUE	���C�����쒆
 *	@retval	FALSE	����ȊO�̏��������Ă��܂�
 *
 *	���C������Ƃ̓t�F�[�h�C���I����̏����ł�
 */
//-----------------------------------------------------------------------------
BOOL ZKN_PROC_MainMoveCheck( ZKN_PROC_SYS_PTR proc )
{
	GF_ASSERT( proc );

	if( proc->main_seq == ZKN_PROC_MAINSEQ_MAIN ){
		return TRUE;
	}

	return FALSE;
}




//-----------------------------------------------------------------------------
/**
 *			�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�f�[�^�ύX�����p���[�N���g�p�O�̏�Ԃɂ���
 *
 *	@param	data	�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void InitProcDoData( ZKN_PROC_DO_DATA* data )
{
	data->seq = 0;
	data->p_work = NULL;
	data->end_req = FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��p���[�N���g�p�O�̏�Ԃɂ���
 *
 *	@param	data	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void InitProcDrawData( ZKN_PROC_DRAW_DATA* data )
{
	data->seq = 0;
	data->p_work = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�f�[�^�ύX�����@�֐����s
 *
 *	@param	func			�֐�
 *	@param	p_do_data		�f�[�^�ύX�������[�N
 *	@param	p_glb_data		�O���[�o���f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏�����
 *	@retval	ZKN_PROC_FALSE		����
 *
 *
 */
//-----------------------------------------------------------------------------
static int DoFuncProcDo( ZKN_PROC_DO_FUNC func, ZKN_PROC_DO_DATA* p_do_data, void* p_glb_data )
{
	int ret;
	
	GF_ASSERT( func );
	GF_ASSERT( p_do_data );
//	GF_ASSERT( p_glb_data );

	ret = func( p_do_data, p_glb_data );

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`�揈���֐������s
 *
 *	@param	func			�֐��|�C���^
 *	@param	p_glb_draw		�`��p�O���[�o���f�[�^
 *	@param	p_draw_data		�`�揈�����[�N
 *	@param	cp_glb_data		�O���[�o���f�[�^
 *	@param	cp_do_data		�������[�N 
 *
 *	@retval	ZKN_PROC_TRUE		�S�Ĕj�����ď������I���܂����B
 *	@retval	ZKN_PROC_FALSE		����
 *
 *
 */
//-----------------------------------------------------------------------------
static int DoFuncProcDraw( ZKN_PROC_DRAW_FUNC func, void* p_glb_draw,  ZKN_PROC_DRAW_DATA* p_draw_data, const void* cp_glb_data, const ZKN_PROC_DO_DATA* cp_do_data )
{
	int ret;
	
	GF_ASSERT( func );
	GF_ASSERT( p_draw_data );
	GF_ASSERT( cp_do_data );
//	GF_ASSERT( cp_glb_data );
//	GF_ASSERT( p_glb_draw );

	ret = func( p_glb_draw, p_draw_data, cp_glb_data, cp_do_data );

	return ret;
}
