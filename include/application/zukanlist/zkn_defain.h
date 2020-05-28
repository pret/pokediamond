//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_defain.h
 *	@brief		�}�Ӓ萔��`
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_DEFAIN_H__
#define __ZKN_DEFAIN_H__


//-----------------------------------------------------------------------------
/**
 *			BG ��`
 */
//-----------------------------------------------------------------------------
#define ZKN_BG_FRM_FONT_M		( GF_BGL_FRAME1_M )	// ������
#define ZKN_BG_FRM_UTIL_M		( GF_BGL_FRAME2_M )	// ���[�e�B���e�B
#define ZKN_BG_FRM_BACK_M		( GF_BGL_FRAME3_M )	// �w�i
#define ZKN_BG_FRM_UTIL_S		( GF_BGL_FRAME1_S )	// ���[�e�B���e�B
#define ZKN_BG_FRM_AFFINE_S		( GF_BGL_FRAME3_S )	// �A�t�B����
#define ZKN_BG_FRM_BACK_S		( GF_BGL_FRAME2_S )	// �w�i

#define ZKN_BG_FONT_COLOR		( 0 )		// �t�H���g�p�J���[�p���b�g
#define ZKN_BG_FONT_COLOR_MSK	( GF_PRINTCOLOR_MAKE(2,1,0) )		// �t�H���g�p�J���[�p���b�g
#define ZKN_BG_FONT_COLOR2_MSK	( GF_PRINTCOLOR_MAKE(4,3,0) )		// �t�H���g�p�J���[�p���b�g

#define ZKN_BG_FIGHT_FONT_COLOR		( 0xc )		// �t�H���g�p�J���[�p���b�g
#define ZKN_BG_FIGHT_FONT_COLOR_MSK	( GF_PRINTCOLOR_MAKE(2,1,0) )		// �t�H���g�p�J���[�p���b�g
#define ZKN_BG_FIGHT_FONT_COLOR2_MSK	( GF_PRINTCOLOR_MAKE(3,4,0) )		// �t�H���g�p�J���[�p���b�g


// ������ʃr�b�g�}�b�v
#define ZKN_BG_FONTBMP_CX	( 32 )
#define ZKN_BG_FONTBMP_CY	( 32 )

//-----------------------------------------------------------------------------
/**
 *			OAM ��`
 */
//-----------------------------------------------------------------------------
#define OAM_OAM_MAIN_S					(0)				// ���C����� OAM�g�p�̈�J�n
#define OAM_OAM_MAIN_E					(128)			// ���C����� OAM�g�p�̈�I��
#define OAM_AFF_MAIN_S					(0)				// ���C����� �A�t�B���g�p�̈�J�n
#define OAM_AFF_MAIN_E					(32)			// ���C����� �A�t�B���g�p�̈�I��
#define OAM_OAM_SUB_S					(0)				// �T�u��� OAM�g�p�̈�J�n
#define OAM_OAM_SUB_E					(128)			// �T�u��� OAM�g�p�̈�I��
#define OAM_AFF_SUB_S					(0)				// �T�u��� �A�t�B���g�p�̈�J�n
#define OAM_AFF_SUB_E					(32)			// �T�u��� �A�t�B���g�p�̈�I��
#define OAM_CHAR_ENTRY_NUM				(32)			// �L�����N�^�}�l�[�W���G���g���[��
#define OAM_CHAR_VRAMTRANS_MAIN_SIZE	(0x14000)		// ���C����� �L�����N�^�}�l�[�W��Vram�Ǘ��̈�
#define OAM_CHAR_VRAMTRANS_SUB_SIZE		(0x4000)		// �T�u��� �L�����N�^�}�l�[�W��Vram�Ǘ��̈�
#define OAM_PLTT_ENTRY_NUM				(32)			// �p���b�g�}�l�[�W���G���g���[��

// �Z���A�N�^�[�p
#define ZKN_CLACT_SET_WORK_NUM		( 128 )	// �Z���A�N�^�[�Z�b�g���[�N��
#define ZKN_CLACT_RES_MANAGER_NUM	( 4 )	// ���\�[�X�}�l�[�W���̐�
#define ZKN_CLACT_RES_DATA_TBL_NUM	( 32 )	// �e���\�[�X�}�l�[�W���ɓo�^�ł���f�[�^��

#define ZKN_CLACT_RES_OBJ_NUM_DEF	( 4 )	// ���\�[�X�̎�ނ͂قƂ�ǂ��S�ł��傤

// FONTOAM
#define ZKN_FONTOAM_WORK_NUM	( 16 )	// FONTOAM���[�N��

#define ZKN_FOTNOAM_COLOR	( GF_PRINTCOLOR_MAKE(3,2,1) )


// �e��ʂ̃��\�[�X�Ǘ�ID�萔
#define ZKN_POKELIST_SUB_RES_ID_OFS		( 1000 )
#define ZKN_ZUKAN_COMMON_RES_ID_OFS		( 2000 )
#define ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS	( 2100 )
#define ZKN_DRAWGLB_POKENAME_TBL_RES_ID	( 3000 )
#define ZKN_ZUKAN_FOOT_RES_ID	( 4000 )
#define ZKN_ZUKAN_SUB_RES_ID	( 5000 )
#define ZKN_RANGE_RES_ID		( 6000 )
#define ZKN_BIG_WEIGHT_RES_ID	( 7000 )
#define ZKN_BIG_WEIGHT_ICON_RES_ID	( 8000 )
#define ZKN_BIG_SUB_RES_ID		( 9000 )
#define ZKN_SOUND_SUB_RES_ID		( 10000 )
#define ZKN_SOUND_RES_ID		( 11000 )
#define ZKN_CUSOR_RES_ID		( 12000 )
#define ZKN_GRAPHIC_SUB_RES_ID		( 13000 )
#define ZKN_GRAPHIC_RES_ID		( 14000 )
#define ZKN_SORTSEARCH_RES_ID		( 15000 )
#define ZKN_SORTSEARCHSUB_RES_ID	( 16000 )
#define ZKN_ZUKAN_POKETYPE_RES_ID	( 17000 )


// �e��ʂ̎g�p�p���b�g��
#define ZKN_DRAWGLB_POKENAME_TBL_PLTT_LOAD	(1)
#define ZKN_POKELIST_TBL_PLTT_LOAD	(12)
#define ZKN_POKELIST_SUB_TBL_PLTT_LOAD	(12)
#define ZKN_ZUKAN_FOOT_PLTT_LOAD	(1)
#define ZKN_ZUKAN_COMMON_PLTT_LOAD	(1) 
#define ZKN_ZUKAN_COMMON_PLTT_SUB_LOAD	(6) 
#define ZKN_ZUKAN_PLTT_LOAD	(5) 
#define ZKN_BIG_PLTT_LOAD	(5) 
#define ZKN_BIG_WEIGHT_PLTT_LOAD	(3) 
#define ZKN_SOUNDSUB_PLTT_LOAD	(3) 
#define ZKN_SOUND_PLTT_LOAD	(1) 
#define ZKN_CURSOR_PLTT_LOAD	(1) 
#define ZKN_GRAPHIC_PLTT_LOAD	(1) 

//-----------------------------------------------------------------------------
/**
 *			�|�P�����O���t�B�b�N
 */
//-----------------------------------------------------------------------------
#define ZKN_POKEGRA_TEX_SIZE	(0x8000)	// �|�P����4�̕�
#define ZKN_POKEGRA_PLTT_SIZE	(0x80)


//-----------------------------------------------------------------------------
/**
 *			�\�t�g�E�F�A�X�v���C�g
 */
//-----------------------------------------------------------------------------
#define ZKN_SWSP_OBJNUM		(8)
#define ZKN_SWSP_CHARNUM	(8)
#define ZKN_SWSP_PLTTNUM	(8)


//-----------------------------------------------------------------------------
/**
 *			�u���C�g�l�X
 */
//-----------------------------------------------------------------------------
#define ZKN_BRIGHTNESS_MSK_ALL	(GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD) 
#define ZKN_BRIGHTNESS_MSK_PLANE2DEF (GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD) 

#define ZKN_FADE_SYNC_COMMON	( 1 )
#define ZKN_FADE_SYNC_LONG_COMMON	( 4 )

#endif		// __ZKN_DEFAIN_H__

