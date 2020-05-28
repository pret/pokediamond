//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big.h
 *	@brief		�傫������׉��
 *	@author		tomoya takahashi	
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_BIG_H__
#define __ZKN_BIG_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_BIG_H_GLOBAL
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
GLOBAL void ZKN_BigAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_BigAplDelete( ZKN_APL_DATA* p_data );



#ifdef PM_DEBUG
// �}�ӑ傫������׃f�o�b�N�p
GLOBAL void ZKN_BigAplPokeGraScaleSet( ZKN_APL_DATA* p_data, short scale );
GLOBAL void ZKN_BigAplHeroGraScaleSet( ZKN_APL_DATA* p_data, short scale );
GLOBAL void ZKN_BigAplPokeGraYofsSet( ZKN_APL_DATA* p_data, short yofs );
GLOBAL void ZKN_BigAplHeroGraYofsSet( ZKN_APL_DATA* p_data, short yofs );
#endif


#undef	GLOBAL
#endif		// __ZKN_BIG_H__

