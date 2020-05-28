//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sys.h
 *	@brief		�}�ӃV�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SYS_H__
#define __ZKN_SYS_H__

#include "include/system/procsys.h"
#include "include/application/zukanlist/zkn_sys_static.h"
#include "include/application/zukanlist/zkn_data_work.h"

#undef GLOBAL
#ifdef	__ZKN_SYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-------------------------------------
//	�y�A�����g�f�[�^���[�N
//=====================================
typedef struct {
	const ZUKAN_WORK*	cp_zukansave_data;
	const MYSTATUS*		cp_hero_data;
	int time_zone;		// �}�ӂ��J�����Ƃ��̎��ԑ�
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
	ZKN_DATA_WORK* p_zkn_work;
} ZKN_PEARENT_DATA;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄv���b�N����
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT ZKN_ProcInit( PROC* proc, int* seq );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄv���b�N���C��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT ZKN_ProcMain( PROC* proc, int* seq );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄv���b�N�I��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT ZKN_ProcEnd( PROC* proc, int* seq );





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
//	�V�X�e���������f�[�^
//=====================================
typedef struct {
	const ZUKAN_WORK*	cp_zukansave_data;
	const MYSTATUS*		cp_hero_data;
	int time_zone;		// �}�ӂ��J�����Ƃ��̎��ԑ�
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
	ZKN_DATA_WORK* p_zkn_work;
} ZKN_SYS_INIT_DATA;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_SYS_SetUpDraw( int heap );
GLOBAL void ZKN_SYS_ReleaseDraw( void );
GLOBAL ZKN_SYS_PTR ZKN_SYS_Init( int heap, const ZKN_SYS_INIT_DATA* p_init );
GLOBAL BOOL ZKN_SYS_Main( ZKN_SYS_PTR zkn );
GLOBAL void ZKN_Vblank( ZKN_SYS_PTR zkn );


#undef	GLOBAL
#endif		// __ZKN_SYS_H__

