//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_sub.h
 *	@brief		�}�ӃT�u�A�v���P�[�V����
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_SUB_H__
#define __ZKN_ZUKAN_SUB_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_SUB_H_GLOBAL
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
GLOBAL void ZKN_ZukanSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanSubAplDelete( ZKN_APL_DATA* p_data );


#undef	GLOBAL
#endif		// __ZKN_ZUKAN_SUB_H__

