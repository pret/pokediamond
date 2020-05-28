//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event_func.h
 *	@brief		�C�x���g�֐��̂����ꏊ
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_EVENT_FUNC_H__
#define __ZKN_EVENT_FUNC_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_EVENT_FUNC_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *
 *
 *			���ʂŎg����C�x���g�֐��������ɂ܂Ƃ߂܂��傤�B
 * 
 * 
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		���������[���A�v���P�[�V�����X�^�[�g
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�x���g�f�[�^��ZKN_EVENT_DATA.p_data��
//	�i�[���Ă����Ă��炤�\����
//=====================================
typedef struct {
	ZKN_APL_DATA*		p_apl;		// �n�߂�A�v���P�[�V�����f�[�^
	ZKN_PROC_SYS_PTR	p_proc;		// �v���b�N�V�X�e��
	ZKN_EVENT_SYS_PTR	p_event;	// �C�x���g�V�X�e��
} ZKN_EVENT_APL_START;
GLOBAL BOOL ZKN_EVENT_AplStart( ZKN_EVENT_WORK* p_work );


//-----------------------------------------------------------------------------
/**
 *		�O�̃A�v���P�[�V�����I���[�����̃A�v���P�[�V�����J�n
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�x���g�f�[�^��ZKN_EVENT_DATA.p_data��
//	�i�[���Ă����Ă��炤�\����
//=====================================
typedef struct {
	ZKN_APL_DATA*		p_apl;		// �n�߂�A�v���P�[�V�����f�[�^
	ZKN_PROC_SYS_PTR	p_proc;		// �v���b�N�V�X�e��
	ZKN_EVENT_SYS_PTR	p_event;	// �C�x���g�V�X�e��
} ZKN_EVENT_APL_CHANGE;
GLOBAL BOOL ZKN_EVENT_AplChange( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *		���̃A�v���P�[�V�����I���[���}�Ӕj��
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�x���g�f�[�^��ZKN_EVENT_DATA.p_data��
//	�i�[���Ă����Ă��炤�\����
//=====================================
typedef struct {
	ZKN_PROC_SYS_PTR	p_proc_m;		// �v���b�N�V�X�e��
	ZKN_PROC_SYS_PTR	p_proc_s;		// �v���b�N�V�X�e��
	ZKN_PROC_SYS_PTR	p_proc_mc;		// �v���b�N�V�X�e��
	ZKN_PROC_SYS_PTR	p_proc_sc;		// �v���b�N�V�X�e��
	BOOL*				p_delete_flag;	// �j���t���O
} ZKN_EVENT_APL_END_ZKN_DELETE;
GLOBAL BOOL ZKN_EVENT_AplEndZknDelete( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *	���̃A�v���P�[�V�����I��
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�x���g�f�[�^��ZKN_EVENT_DATA.p_data��
//	�i�[���Ă����Ă��炤�\����
//=====================================
typedef struct {
	// ������
	ZKN_PROC_SYS_PTR	p_proc;		// �v���b�N�V�X�e��
	ZKN_EVENT_SYS_PTR	p_event;	// �C�x���g�V�X�e��
} ZKN_EVENT_APL_END;
GLOBAL BOOL ZKN_EVENT_AplEnd( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *		main��ʃT�u��ʑS�ύX
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�x���g�f�[�^��ZKN_EVENT_DATA.p_data��
//	�i�[���Ă����Ă��炤�\����
//=====================================
typedef struct {
	ZKN_PROC_SYS_PTR	p_proc_m;		// �v���b�N�V�X�e��
	ZKN_PROC_SYS_PTR	p_proc_s;		// �v���b�N�V�X�e��
	ZKN_PROC_SYS_PTR	p_proc_mc;		// �v���b�N�V�X�e��
	ZKN_PROC_SYS_PTR	p_proc_sc;		// �v���b�N�V�X�e��
	
	ZKN_EVENT_SYS_PTR	p_event_m;		// �C�x���g�V�X�e��
	ZKN_EVENT_SYS_PTR	p_event_s;		// �C�x���g�V�X�e��
	ZKN_EVENT_SYS_PTR	p_event_mc;		// �C�x���g�V�X�e��
	ZKN_EVENT_SYS_PTR	p_event_sc;		// �C�x���g�V�X�e��

	ZKN_APL_DATA*		p_apl_m;		// �n�߂�A�v���P�[�V�����f�[�^
	ZKN_APL_DATA*		p_apl_s;		// �n�߂�A�v���P�[�V�����f�[�^
	ZKN_APL_DATA*		p_apl_mc;		// �n�߂�A�v���P�[�V�����f�[�^
	ZKN_APL_DATA*		p_apl_sc;		// �n�߂�A�v���P�[�V�����f�[�^
} ZKN_EVENT_APL_AllCHANGE;
GLOBAL BOOL ZKN_EVENT_AplAllChange( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *		main��ʃT�u���	�Q�ύX
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�x���g�f�[�^��ZKN_EVENT_DATA.p_data��
//	�i�[���Ă����Ă��炤�\����
//=====================================
typedef struct {
	ZKN_PROC_SYS_PTR	p_proc_m;		// �v���b�N�V�X�e��
	ZKN_PROC_SYS_PTR	p_proc_s;		// �v���b�N�V�X�e��
	
	ZKN_EVENT_SYS_PTR	p_event_m;		// �C�x���g�V�X�e��
	ZKN_EVENT_SYS_PTR	p_event_s;		// �C�x���g�V�X�e��

	ZKN_APL_DATA*		p_apl_m;		// �n�߂�A�v���P�[�V�����f�[�^
	ZKN_APL_DATA*		p_apl_s;		// �n�߂�A�v���P�[�V�����f�[�^
} ZKN_EVENT_APL_DOUBLE_CHANGE;
GLOBAL BOOL ZKN_EVENT_AplDoubleChange( ZKN_EVENT_WORK* p_work );



//-----------------------------------------------------------------------------
/**
 *		�e�A�v���P�[�V�����ɕύX����C�x���g�f�[�^�쐬�֐�
 */
//-----------------------------------------------------------------------------
GLOBAL void ZKN_EVENT_DeleteData( ZKN_EVENT_DATA* p_event_data );

// �\�[�g���
GLOBAL void ZKN_EVENT_MakeChangeSortSearch( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );

// �}�ӃV�X�e���I��
GLOBAL void ZKN_EVENT_MakeZukanEnd( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );

// �}�ӃT�u�R����
GLOBAL void ZKN_EVENT_MakeChangeZukanCommonSubOnly( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );

// �}�Ӊ��
GLOBAL void ZKN_EVENT_MakeChangeZukan( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeZukanOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );
GLOBAL void ZKN_EVENT_MakeChangeZukanNormalMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );
GLOBAL void ZKN_EVENT_MakeChangeZukanTextMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );

// ���������
GLOBAL void ZKN_EVENT_MakeChangeZukanGraphic(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );

// ���z���
GLOBAL void ZKN_EVENT_MakeChangeRange( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeRangeMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// ���������
GLOBAL void ZKN_EVENT_MakeChangeSound( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeSoundMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// �傫����׉�ʂ�
GLOBAL void ZKN_EVENT_MakeChangeBig( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeBigMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeBigWeightMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// �|�P�������X�g���
GLOBAL void ZKN_EVENT_MakeChangePokeList( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// �|�P�������X�g�̏��ʂ̂ݕύX
GLOBAL void ZKN_EVENT_MakeStartMainPokeList( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key );


#ifdef PM_DEBUG
// �������DEBUG�A�v����
GLOBAL void ZKN_EVENT_BigHeightDebugApl( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key );

// �������DEBUG�A�v�����獂����ׂɕ��A
GLOBAL void ZKN_EVENT_BigHeightDebugAplReturn( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key );
#endif


#undef	GLOBAL
#endif		// __ZKN_EVENT_FUNC_H__

