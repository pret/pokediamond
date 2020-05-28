//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fight_text.h
 *	@brief		�}�Ӑ퓬��̃e�L�X�g�f�[�^�\���V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.03.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_FIGHT_TEXT_H__
#define __ZKN_FIGHT_TEXT_H__

#include "include/gflib/clact.h"
#include "include/system/palanm.h"
#include "include/gflib/bg_system.h"
#include "include/system/softsprite.h"

#include "include/application/zukanlist/zkn_zukan.h"

#undef GLOBAL
#ifdef	__ZKN_FIGHT_TEXT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
// ����Ă���^�X�N�̗D�揇��
#define ZKN_FIGHT_TCB_PRI		( 0 ) // �^�X�N�o�^���ꂽ�t���[���̓^�X�N�̃��C�����ʂ�Ȃ��悤�ɂ��Ă����K�v������܂�

// �|�P�����O���t�B�b�N���W
#define ZKN_FIGHT_POKEGRA_MAT_X	( ZKN_ZUKAN_POKEGRA_MAT_X )
#define ZKN_FIGHT_POKEGRA_MAT_Y	( ZKN_ZUKAN_POKEGRA_MAT_Y )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�Ӄt�@�C�g�e�L�X�g�\���^�X�N
//=====================================
typedef struct {
	GF_BGL_INI*			p_bgl;		// BGL	(BG�R���g���[���͍Đݒ肵�܂�)
	PALETTE_FADE_PTR	p_pfd;		// �p���b�g�t�F�[�h
	SOFT_SPRITE_MANAGER* p_ssm;		// �\�t�g�E�F�A�X�v���C�g
	int					heap;		// �g�p����q�[�v
	POKEMON_PARAM*		p_pp;		// �|�P�����p�����[�^
	int					pokenum_mode;// �|�P�����i���o�[���[�h
	// PM_NUMBER_SHINOU:�V���I�E   PM_NUMBER_ZENKOKU:�S��
	


/*	SOFT_SPRITE* p_ssp;				// �\�t�g�X�v���C�g�}�l�[�W��
	int monsno;//*/
} ZKN_FIGHT_TEXT_PARAM;

typedef struct _ZKN_FIGHT_TEXT_DRAW		ZKN_FIGHT_TEXT_DRAW;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
// �^�X�N����
// �u���b�N�A�E�g��Ԃœn���Ă�������
GLOBAL ZKN_FIGHT_TEXT_DRAW* ZKN_FIGHT_TextDrawReq( const ZKN_FIGHT_TEXT_PARAM* cp_param );

// �j��
// �Ă΂ꂽ�u�Ԃɔj������܂�
GLOBAL void ZKN_FIGHT_TextDrawDelete( ZKN_FIGHT_TEXT_DRAW* p_data );

// �t�F�[�h�C���܂Ŋ����������`�F�b�N
GLOBAL BOOL ZKN_FIGHT_TexDrawEndCheck( const ZKN_FIGHT_TEXT_DRAW* cp_data );

// �\�t�g�E�F�A�X�v���C�g���擾
GLOBAL SOFT_SPRITE* ZKN_FIGHT_TexDrawGetSsp( ZKN_FIGHT_TEXT_DRAW* p_data );

// �p���b�g�A�j��ONOFF�t���O
GLOBAL void ZKN_FIGHT_PalAnmFlagSet( ZKN_FIGHT_TEXT_DRAW* p_data, BOOL flag );
GLOBAL BOOL ZKN_FIGHT_PalAnmFlagGet( const ZKN_FIGHT_TEXT_DRAW* cp_data );

#undef	GLOBAL
#endif		// __ZKN_FIGHT_TEXT_H__

