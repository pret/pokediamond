//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event.h
 *	@brief		�A�v���P�[�V�����ύX�@�}�ӏI���Ȃǂ̃C�x���g�Ǘ�
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __ZKN_EVENT_H__
#define __ZKN_EVENT_H__

#undef GLOBAL
#ifdef	__ZKN_EVENT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

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
//		�C�x���g�֐��ɓn�����\����
//=====================================
typedef struct {
	int seq;
	void* p_work;			// �C�x���g�������[�N
	void* p_data;			// �C�x���g�O������󂯎��f�[�^
} ZKN_EVENT_WORK;

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�C�x���g�֐��|�C���^
 *
 *	@param		���[�N
 *
 *	@retval		TRUE	�C�x���g�I��
 *	@retval		FALSE	�C�x���g���s
 *
 *
 */
//-----------------------------------------------------------------------------
typedef BOOL (*ZKN_EVENT_FUNC)( ZKN_EVENT_WORK*  p_work );


//-------------------------------------
//		�C�x���g�Ǘ��\����
//=====================================
typedef struct {
	int key_msk;			// �C�x���g���s�L�[�}�X�N
	ZKN_EVENT_FUNC func;	// ���s�C�x���g�֐�
	ZKN_EVENT_WORK work;	// �C�x���g���[�N
} ZKN_EVENT_DATA;


//-------------------------------------
//		�C�x���g�Ǘ��V�X�e��
//=====================================
typedef struct _ZKN_EVENT_SYS*			ZKN_EVENT_SYS_PTR;
typedef const struct _ZKN_EVENT_SYS*	CONST_ZKN_EVENT_SYS_PTR;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_EVENT_SYS_PTR ZKN_EVENT_MemoryAlloc( int heap );
GLOBAL void ZKN_EVENT_Init( ZKN_EVENT_SYS_PTR event, ZKN_EVENT_DATA* p_event_data, int event_num );
GLOBAL const ZKN_EVENT_DATA* ZKN_EVENT_Main( ZKN_EVENT_SYS_PTR event, int event_key );
GLOBAL BOOL ZKN_EVENT_DoCheck( ZKN_EVENT_SYS_PTR event );


#undef	GLOBAL
#endif		// __ZKN_EVENT_H__

