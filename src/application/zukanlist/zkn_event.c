//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event.c
 *	@brief		�A�v���P�[�V�����ύX�@�}�ӏI���Ȃǂ̃C�x���g�Ǘ�
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define	__ZKN_EVENT_H_GLOBAL
#include "include/application/zukanlist/zkn_event.h"

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

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//		�C�x���g�Ǘ��V�X�e��
//=====================================
typedef struct _ZKN_EVENT_SYS{
	ZKN_EVENT_DATA* p_event_data;	// �C�x���g�f�[�^
	int event_num;					// �C�x���g��
	ZKN_EVENT_DATA* p_event_do;		// ���s���̃C�x���g
} ZKN_EVENT_SYS;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static BOOL EventDoCheck( ZKN_EVENT_SYS_PTR event );
static ZKN_EVENT_DATA* EventStartCheck( ZKN_EVENT_SYS_PTR event, int event_key );
static void EventDataSet( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* cp_event_data );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃC�x���g���[�N�������m��
 *
 *	@param	heap	�g�p�q�[�v
 *
 *	@return	���[�N�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_EVENT_MemoryAlloc( int heap )
{
	ZKN_EVENT_SYS_PTR event;

	event = sys_AllocMemory( heap, sizeof(ZKN_EVENT_SYS) );
	GF_ASSERT( event );
	memset( event, 0, sizeof(ZKN_EVENT_SYS) );

	return event;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃC�x���g������
 *
 *	@param	event			�C�x���g���[�N
 *	@param	p_event_data	�C�x���g�f�[�^�e�[�u��
 *	@param	event_num		�C�x���g�f�[�^�e�[�u���v�f��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_Init( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* p_event_data, int event_num )
{
	GF_ASSERT( event );
	
	event->p_event_data		= p_event_data;
	event->event_num		= event_num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃC�x���g���C��
 *
 *	@param	event			�C�x���g���[�N
 *	@param	event_key		�C�x���g�L�[
 *
 *	@return	���s���̃C�x���g�e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
const ZKN_EVENT_DATA* ZKN_EVENT_Main( ZKN_EVENT_SYS_PTR event, int event_key )
{
	ZKN_EVENT_DATA* p_event_data;
	BOOL ret;
	
	GF_ASSERT( event );

	// ���s���̂��̂������Ƃ���
	// �������s���邩�`�F�b�N����
	if( EventDoCheck( event ) == FALSE ){

		// ���s�J�n�`�F�b�N
		p_event_data = EventStartCheck( event, event_key );
		if( p_event_data ){
			EventDataSet( event, p_event_data );
		}
	}

	// ���s
	if( EventDoCheck( event ) == TRUE ){
		
		// �C�x���g���s
		ret = event->p_event_do->func( &event->p_event_do->work );

		// �I���`�F�b�N
		if( ret == TRUE ){
			EventDataSet( event, NULL );
		}
	}

	return event->p_event_do;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g���s�����`�F�b�N
 *
 *	@param	event	�C�x���g
 *
 *	@retval	TRUE	�C�x���g��
 *	@retval FALSE	�C�x���g�Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_DoCheck( ZKN_EVENT_SYS_PTR event )
{
	GF_ASSERT(event);

	if( event->p_event_do ){
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
 *	@brief	�C�x���g���s�����`�F�b�N
 *
 *	@param	event	�C�x���g���[�N
 *
 *	@retval	TRUE	���s��
 *	@retval	FALSE	���s���Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL EventDoCheck( ZKN_EVENT_SYS_PTR event )
{
	if( event->p_event_do ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�J�n�`�F�b�N
 *
 *	@param	event		�C�x���g���[�N
 *	@param	event_key	�C�x���g�L�[
 *
 *	@return	�J�n����C�x���g�f�[�^�e�[�u��	�����Ƃ� NULL
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* EventStartCheck( ZKN_EVENT_SYS_PTR event, int event_key )
{
	int i;		// ���[�v�p

	for( i=0; i<event->event_num; i++ ){

		GF_ASSERT( event->p_event_data );
		
		if( event->p_event_data[ i ].key_msk & event_key ){

			return event->p_event_data + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�f�[�^�ݒ�
 *
 *	@param	event			�C�x���g���[�N
 *	@param	p_event_data	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void EventDataSet( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* p_event_data )
{
	event->p_event_do = p_event_data;

	// �V�[�P���X�f�[�^������
	if( event->p_event_do ){
		event->p_event_do->work.seq = 0;
	}
}
