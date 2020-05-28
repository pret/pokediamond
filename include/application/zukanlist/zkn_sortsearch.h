//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sortsearch.h
 *	@brief		�����\�[�g�A�v���P�[�V����
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SORTSEARCH_H__
#define __ZKN_SORTSEARCH_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_SORTSEARCH_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�Z���N�g����
//=====================================
enum{
	ZKN_SORTSEARCH_SELECT_SORT,
	ZKN_SORTSEARCH_SELECT_NEME,
	ZKN_SORTSEARCH_SELECT_TYPE,
	ZKN_SORTSEARCH_SELECT_FORM,
	ZKN_SORTSEARCH_SELECT_NUM
};

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
GLOBAL void ZKN_SortSearchAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_SortSearchAplDelete( ZKN_APL_DATA* p_data );

// �t�F�[�h���[�h�擾
enum{
	ZKN_SORTSEARCH_FADENONE,
	ZKN_SORTSEARCH_FADEOUT,
	ZKN_SORTSEARCH_DO_MAIN,
	ZKN_SORTSEARCH_FADEIN,
	ZKN_SORTSEARCH_END_FADE,
};
#define ZKN_SORTSEARCH_FADECOUNT_MAX	( ZKN_FADE_SYNC_LONG_COMMON )
#define ZKN_SORTSEARCH_DO_MAIN_EFF_COUNT_MAX	( 32 )
GLOBAL int ZKN_SortSearchAplFadeModeGet( const ZKN_APL_DATA* cp_data );
GLOBAL int ZKN_SortSearchAplFadeModeCountGet( const ZKN_APL_DATA* cp_data );

// �I�����ߕύX
GLOBAL void ZKN_SortSearchAplSelectTypeSet( ZKN_APL_DATA* p_data, int type );
GLOBAL int ZKN_SortSearchAplSelectTypeGet( const ZKN_APL_DATA* cp_data );
// ������ߕύX
GLOBAL void ZKN_SortSearchAplSortTypeSet( ZKN_APL_DATA* p_data, int type );
GLOBAL int ZKN_SortSearchAplSortTypeGet( const ZKN_APL_DATA* cp_data );
// �Ȃ܂����ߕύX
GLOBAL void ZKN_SortSearchAplNameTypeSet( ZKN_APL_DATA* p_data, int type );
GLOBAL int ZKN_SortSearchAplNameTypeGet( const ZKN_APL_DATA* cp_data );
// �������ߕύX
enum{
	ZKN_SORTSEARCH_TYPE1,
	ZKN_SORTSEARCH_TYPE2,
	ZKN_SORTSEARCH_TYPENUM
};
GLOBAL void ZKN_SortSearchAplTypeTypeSet( ZKN_APL_DATA* p_data, int type, int no );
GLOBAL int ZKN_SortSearchAplTypeTypeGet( const ZKN_APL_DATA* cp_data, int no );
// �`�����ߕύX
GLOBAL void ZKN_SortSearchAplFormTypeSet( ZKN_APL_DATA* p_data, int type );
GLOBAL int ZKN_SortSearchAplFormTypeGet( const ZKN_APL_DATA* cp_data );
// ���X�g��ʂ֍s��
GLOBAL void ZKN_SortSearchAplReqListFade( ZKN_APL_DATA* p_data, BOOL do_sort );
GLOBAL BOOL ZKN_SortSearchAplSortDoFlagGet( const ZKN_APL_DATA* cp_data );


#undef	GLOBAL
#endif		// __ZKN_SORTSEARCH_H__

