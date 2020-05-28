//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_world_text_sys.h
 *	@brieuf		�}�ӂ̊O����e�L�X�g�A�N�Z�X
 *	@author		tomoya takahashi
 *	@data		2006.02.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_WORLD_TEXT_SYS_H__
#define __ZKN_WORLD_TEXT_SYS_H__

#include "include/gflib/strbuf.h"

#undef GLOBAL
#ifdef	__ZKN_WORLD_TEXT_SYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define ZKN_WT_WORLD_TEXT_PAGE_NUM	( 1 )		// �e�L�X�g�f�[�^�̃y�[�W��
#define ZKN_WT_HOME_TEXT_PAGE_NUM	( 1 )		// �����e�L�X�g�f�[�^�̃y�[�W��

// �����e�L�X�g�f�[�^���O���̂Ƃ��Q�y�[�W�\���ɂȂ�\��������̂�
// ���̂悤�ɂ��Ă��܂�

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
GLOBAL void ZKN_WT_DeleteStrBuf( STRBUF* buf );

GLOBAL int ZKN_WT_LANG_Code_WORLD_TEXT_GMM_Idx( int country );
GLOBAL int ZKN_WT_WORLD_TEXT_GMM_Idx_LANG_Code( int country );

GLOBAL BOOL ZKN_WT_CheckWorldData( int monsno, int country );
GLOBAL STRBUF* ZKN_WT_GetPokeName( int monsno, int country, int heap );
GLOBAL STRBUF* ZKN_WT_GetPokeType( int monsno, int country, int heap );
GLOBAL STRBUF* ZKN_WT_GetText( int monsno, int country, int page, int heap );



#undef	GLOBAL
#endif		// __ZKN_WORLD_TEXT_SYS_H__

