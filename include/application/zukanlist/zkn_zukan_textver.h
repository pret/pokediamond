//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_textver.h
 *	@brief		�}�ӌ���o�[�W����
 *	@author		tomoya takahashi
 *	@data		2006.02.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_TEXTVER_H__
#define __ZKN_ZUKAN_TEXTVER_H__

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_TEXTVER_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
enum{
	ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST,	// �|�P���X�g�Ƃ̍s����
	ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL,		// �ʏ�
	ZKK_ZUKANTEXTVER_FADE_MODE_OTHER,		// ���̑���ʂ�
};

// �|�P�������X�g���W
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_IX	( 172 )
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_IY	( 32 )

// �|�P�����O���t�B�b�N���W
#define ZKN_ZUKANTEXTVER_POKEGRA_MAT_X	( 48 )
#define ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y	( 72 )


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
GLOBAL void ZKN_ZukanTextverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanTextverAplDelete( ZKN_APL_DATA* p_data );


// �A�v���f�[�^�O���ύX�֐�
GLOBAL void ZKN_ZukanTextverPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y );
GLOBAL void ZKN_ZukanTextverFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode );

// ���̃y�[�W��
GLOBAL BOOL ZKN_ZukanTexverPageAdd( ZKN_APL_DATA* p_data );
GLOBAL BOOL ZKN_ZukanTexverPageSet( ZKN_APL_DATA* p_data, int page );

// ���R�[�h�ݒ�
GLOBAL void ZKN_ZukanTexverTypeSet( ZKN_APL_DATA* p_data, int lang );

#undef	GLOBAL
#endif		// __ZKN_ZUKAN_TEXTVER_H__

