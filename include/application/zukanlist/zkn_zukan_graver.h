//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_graver.h
 *	@brief		�}�ӃO���t�B�b�N�o�[�W����
 *	@author		tomoya takahashi
 *	@data		2006.02.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_GRAVER_H__
#define __ZKN_ZUKAN_GRAVER_H__

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_GRAVER_H_GLOBAL
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
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_ZukanGraverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanGraverAplDelete( ZKN_APL_DATA* p_data );


// �`��^�C�v��ύX����
GLOBAL BOOL ZKN_ZukanGraverDrawTypeAdd( ZKN_APL_DATA* p_data, int num );

#undef	GLOBAL
#endif		// __ZKN_ZUKAN_GRAVER_H__

