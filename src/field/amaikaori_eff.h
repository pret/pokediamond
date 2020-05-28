//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		amaikaori_eff.h
 *	@brief		�Â�����G�t�F�N�g
 *	@author		tomoya takahashi
 *	@data		2006.05.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __AMAIKAORI_EFF_H__
#define __AMAIKAORI_EFF_H__

#include "fieldsys.h"
#include "fieldmap_func.h"

#undef GLOBAL
#ifdef	__AMAIKAORI_EFF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

#ifdef PM_DEBUG
//#define FIELD_AMAIKAORI_DEBUG	// �f�o�b�N�@�\ON
#endif


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�Â�����C�x���g
//=====================================
typedef struct _EVENT_AMAIKAORI_EFF_WORK EVENT_AMAIKAORI_EFF_WORK;
GLOBAL u32 FLDMAP_Amaikaori_WorkSize( void );


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�Â�����C�x���g�@���䕔��	���[�N�̂͂������܂��@�m�ۂ͊O
 *
 *	@param	event	�C�x���g���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL FLDMAP_AmaikaoriEvent( GMEVENT_CONTROL * event );






//-----------------------------------------------------------------------------
/**
 *	�G�t�F�N�g�֐�
 */
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLDMAP_Amaikaori_Start( FIELDSYS_WORK* fsys );
GLOBAL FLDMAPFUNC_WORK* FLDMAP_AmaikaoriEndEff_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_Amaikaori_End( FLDMAPFUNC_WORK* p_eff );
GLOBAL BOOL FLDMAP_Amaikaori_EndCheck( FLDMAPFUNC_WORK* p_eff );

#ifdef FIELD_AMAIKAORI_DEBUG
GLOBAL void AmaikaoriDebugMain( TCB_PTR tcb, void* p_work );
#endif


#undef	GLOBAL
#endif		// __AMAIKAORI_EFF_H__

