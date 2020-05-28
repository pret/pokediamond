//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fontoam.h
 *	@brief		�ӂ����OAM�쐬�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.01.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_FONTOAM_H__
#define __ZKN_FONTOAM_H__

#include "include/gflib/bg_system.h"
#include "include/system/fontoam.h"
#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"

#undef GLOBAL
#ifdef	__ZKN_FONTOAM_H_GLOBAL
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
//-------------------------------------
//	
//	�}�Ӄt�H���gOAM�f�[�^
//	
//=====================================
typedef struct {
	FONTOAM_OBJ_PTR p_fontoam;
	CHAR_MANAGER_ALLOCDATA char_data;
} ZKN_FONTOAM_DATA;

//-------------------------------------
//	
//	�}�Ӄt�H���gOAM�V�X�e��
//	
//=====================================
typedef struct _ZKN_FONTOAM_SYS* ZKN_FONTOAM_SYS_PTR;
typedef const struct _ZKN_FONTOAM_SYS* CONST_ZKN_FONTOAM_SYS_PTR;

//-------------------------------------
//	
//	�}�Ӄt�H���gOAM�V�X�e���������֐�
//	
//=====================================
typedef struct {
	CLACT_SET_PTR clact_set;	// �g�p����Z���A�N�^�[�Z�b�g
	GF_BGL_INI*		p_bg;		// bg�V�X�e��
	int work_num;		// �o�^�ő吔
	int heap;			// �q�[�v
} ZKN_FONTOAM_SYS_INIT;


//-------------------------------------
//	
//	�t�H���g�f�[�^�o�^�\����
//	
//=====================================
typedef struct {
	ZKN_FONTOAM_SYS_PTR zkn_fontoam;	// fontoam�V�X�e��
	const GF_BGL_BMPWIN*	p_bmp;		// �r�b�g�}�b�v�f�[�^
	const NNSG2dImagePaletteProxy* pltt;// �Z���Q�Ɛ�p���b�g�v���N�V
	CONST_CLACT_WORK_PTR	parent;		// �e�̃A�N�^�[		����Ȃ��Ƃ�NULL	�i�{�^���Ȃǁj
	int					x;				// �o�^�����W		�e�A�N�^�[������Ƃ��͐e����̃I�t�Z�b�g�����W	(dot�P��)
	int					y;				// �o�^�����W		�e�A�N�^�[������Ƃ��͐e����̃I�t�Z�b�g�����W	(dot�P��)
	int					bg_pri;			// bg�D�揇��
	int					soft_pri;		// �\�t�g�D�揇��
	int					draw_area;		// �\����
	/*
		NNS_G2D_VRAM_TYPE_2DMAIN    �Q�c�O���t�B�b�N�X�G���W���`�p
		NNS_G2D_VRAM_TYPE_2DSUB     �Q�c�O���t�B�b�N�X�G���W���a�p*/
	int					heap;			// �g�p����q�[�v	
} ZKN_FONTOAM_INIT;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_FONTOAM_SYS_PTR ZKN_FONTOAM_InitSys( const ZKN_FONTOAM_SYS_INIT* cp_init );
GLOBAL void ZKN_FONTOAM_DeleteSys( ZKN_FONTOAM_SYS_PTR fontoam_sys );

GLOBAL ZKN_FONTOAM_DATA* ZKN_FONTOAM_Make( const ZKN_FONTOAM_INIT* cp_init );
GLOBAL ZKN_FONTOAM_DATA* ZKN_FONTOAM_MakeCharOfs( const ZKN_FONTOAM_INIT* cp_init, int char_size );
GLOBAL void ZKN_FONTOAM_Delete( ZKN_FONTOAM_DATA* p_fontoam );
GLOBAL void ZKN_FONTOAM_DeleteAll( ZKN_FONTOAM_SYS_PTR fontoam_sys );

GLOBAL GF_BGL_BMPWIN* ZKN_FONTOAM_GetBmp( ZKN_FONTOAM_SYS_PTR fontoam_sys, int bmp_x, int bmp_y );
GLOBAL void ZKN_FONTOAM_DeleteBmp( GF_BGL_BMPWIN* win );
GLOBAL void ZKN_FONTOAM_PrintBmpStr( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, u32 dataid, u32 msgid, int bmp_x, int bmp_y );
GLOBAL void ZKN_FONTOAM_PrintBmpStrBuf( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, STRBUF* str, int bmp_x, int bmp_y );



#undef	GLOBAL
#endif		// __ZKN_FONTOAM_H__

