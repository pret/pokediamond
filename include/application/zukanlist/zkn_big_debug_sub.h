//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big_debug_sub.h
 *	@brief		�������DEBUG�A�v��
 *	@author		tomoya takahashi	
 *	@data		2006.03.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef PM_DEBUG


#ifndef __ZKN_BIG_DEBUG_SUB_H__
#define __ZKN_BIG_DEBUG_SUB_H__

#undef GLOBAL
#ifdef	__ZKN_BIG_DEBUG_SUB_H_GLOBAL
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

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_BigDebugAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_BigDebugAplDelete( ZKN_APL_DATA* p_data );



#undef	GLOBAL
#endif		// __ZKN_BIG_DEBUG_SUB_H__

#endif		// PM_DEBUG
