//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan.h
 *	@brief		�}�ӃT�u���
 *	@author		tomoya takahashi	
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ZUKAN_H__
#define __ZKN_ZUKAN_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#include "include/application/zukanlist/zkn_zukan_common.h"

#undef GLOBAL
#ifdef	__ZKN_ZUKAN_H_GLOBAL
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
	ZKN_ZUKAN_FADE_MODE_CHPOKELIST,	// �|�P���X�g�Ƃ̍s����
	ZKK_ZUKAN_FADE_MODE_NORMAL,		// �ʏ�
	ZKK_ZUKAN_FADE_MODE_OTHER,		// ���̑���ʂ�
};

// �|�P�������X�g���W
#define ZKN_ZUKAN_POKELIST_MAT_IX	( 172 )
#define ZKN_ZUKAN_POKELIST_MAT_IY	( 32 )

// �|�P�����O���t�B�b�N���W
#define ZKN_ZUKAN_POKEGRA_MAT_X	( 48 )
#define ZKN_ZUKAN_POKEGRA_MAT_Y	( 72 )


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�Ӊ�ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^

	int poke_gra_move_x;					// �|�P�O�������
	int poke_gra_move_y;					// �|�P�O�������

	// �}�ӃR�����A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;
	int					fade_mode;			// �t�F�[�h���[�h

	int zukan_page;		// �\���}�Ӄy�[�W

	BOOL mons_snd_req;	// �|�P�����̐����N�G�X�g
} ZKN_ZUKAN_GLB;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_ZukanAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_ZukanAplDelete( ZKN_APL_DATA* p_data );

GLOBAL BOOL ZKN_ZukanAplPageAdd( ZKN_ZUKAN_GLB* p_data, int add );
GLOBAL BOOL ZKN_ZukanAplPageSet( ZKN_ZUKAN_GLB* p_data, int set );


// �ߊl�}�Ӊ�ʗp
GLOBAL GF_BGL_BMPWIN* ZknZukanPokeTypeTextBmpMake( ZKN_FONTOAM_SYS_PTR p_fontoamsys, int mons_no, int heap );
GLOBAL int ZknZukanClactTypeNoChg( int type );
GLOBAL void ZknZukanSetUpFontBg_Minute( GF_BGL_BMPWIN* p_bmp, int monsno, int heap, int page, u32 color_msk );

// �`�|�P�������W
#define ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_X	( -58 )
#define ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_Y	( -8 )
#define ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCX	( 16 )
#define ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCY	( 2 )
#define ZKN_ZUKAN_POKETYPE_TEXT_TBL_SEQ	( 0x11 )

// �^�C�v�A�j���V�[�P���X
enum{
	ZKN_ZUKAN_POKETYPE_NORMAL = 0,
};

#undef	GLOBAL
#endif		// __ZKN_ZUKAN_H__

