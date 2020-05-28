//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_world_text_data.h
 *	@brief		�}�Ӑ��E�e�L�X�g�f�[�^�@�ƃQ�[�������R�[�h�������N������f�[�^
 *	@author		tomoya takahashi	
 *	@data		2006.03.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_WORLD_TEXT_DATA_H__
#define __ZKN_WORLD_TEXT_DATA_H__

#undef GLOBAL
#ifdef	__ZKN_WORLD_TEXT_DATA_H_GLOBAL
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
//	�O����e�L�X�g�p���R�[�h
//=====================================
enum{
	ZKN_WORLD_TEXT_JAPAN,		// ���{
	ZKN_WORLD_TEXT_E,			// �A�����J
	ZKN_WORLD_TEXT_FRA,			// �t�����X
	ZKN_WORLD_TEXT_GER,			// �h�C�c
	ZKN_WORLD_TEXT_ITA,			// �C�^���A
	ZKN_WORLD_TEXT_SPA,			// �X�y�C��
	ZKN_WORLD_TEXT_NUM
};

#define ZKN_WORLD_TEXT_OUTWORLD_NUM	( ZKN_WORLD_TEXT_NUM-1  )	// �O�����ڃf�[�^�̐�
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

GLOBAL int ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( int lang_code );
GLOBAL int ZKN_WT_GetZKN_WORLD_TEXT_Code_LANG_Code( int world_text_code );
GLOBAL int ZKN_WT_GetMonsNo_TEXTVERPokeNum( int monsno );


#undef	GLOBAL
#endif		// __ZKN_WORLD_TEXT_DATA_H__

