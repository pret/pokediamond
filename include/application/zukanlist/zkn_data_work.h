//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_data_work.h
 *	@brief		�}�Ӄf�[�^���[�N
 *	@author		tomoya takahashi
 *	@data		2006.07.13
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_DATA_WORK_H__
#define __ZKN_DATA_WORK_H__

#undef GLOBAL
#ifdef	__ZKN_DATA_WORK_H_GLOBAL
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
typedef struct _ZKN_DATA_WORK ZKN_DATA_WORK;
//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_DATA_WORK* ZKN_DW_Alloc( u32 heapID );
GLOBAL void ZKN_DW_Free( ZKN_DATA_WORK* p_zkn );

GLOBAL u32 ZKN_DW_GetListMonsNo( const ZKN_DATA_WORK* cp_zkn );
GLOBAL void ZKN_DW_SetListMonsNo( ZKN_DATA_WORK* p_zkn, u32 monsno );
GLOBAL u32 ZKN_DW_GetZknMode( const ZKN_DATA_WORK* cp_zkn );
GLOBAL void ZKN_DW_SetZknMode( ZKN_DATA_WORK* p_zkn, u32 zkn_mode );


#undef	GLOBAL
#endif		// __ZKN_DATA_WORK_H__

