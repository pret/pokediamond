//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sound.h
 *	@brief		�������A�v���P�[�V����
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SOUND_H__
#define __ZKN_SOUND_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_SOUND_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
// ������ʗp�t�F�[�h�J�E���g��
#define ZKN_SOUND_FADE_SYNC	( 3 )


//-------------------------------------
//	�|�P�O���\���ʒu
//=====================================
#define ZKN_SOUND_POKEGRA_DRAW_X	( 48 )
#define ZKN_SOUND_POKEGRA_DRAW_Y	( 64 )


//-------------------------------------
//	�t�F�[�h���[�h
//=====================================
enum{
	ZKN_SOUND_FADE_MODE_MY,
	ZKN_SOUND_FADE_MODE_OTHER,
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
GLOBAL void ZKN_SoundAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_SoundAplDelete( ZKN_APL_DATA* p_data );


// �t�F�[�h�A�E�g���̃|�P�O���ړ���
GLOBAL void ZKN_SoundPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y );
GLOBAL void ZKN_SoundFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode );
GLOBAL void ZKN_SoundFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync );


#undef	GLOBAL
#endif		// __ZKN_SOUND_H__

