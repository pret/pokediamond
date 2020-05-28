//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_drawdata_define.h
 *	@brief		�C���[�W�N���b�v�`��f�[�^�萔�S
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_DRAWDATA_DEFINE_H__
#define __IMC_DRAWDATA_DEFINE_H__

#include "include/application/imageClip/imageclip.naix"
#include "include/system/arc_tool.dat"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_imageclip.h"
#include "include/msgdata/msg_imageclip_acce.h"
#include "include/msgdata/msg_imageclip_bg.h"
#include "include/application/imageClip/imc_itemid_define.h"


#undef GLOBAL
#ifdef	__IMC_DRAWDATA_DEFINE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
*	�I�u�W�F���X�g�p�I�u�W�F�N�g�f�[�^�萔
*/
//-----------------------------------------------------------------------------
enum{
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���I�u�W�F�N�g
	IMC_OBJLIST_BG,			// BG�T���l�C���I�u�W�F�N�g
	IMC_OBJLIST_SND,		// SND�T���l�C���I�u�W�F�N�g
	IMC_OBJLIST_POKE,		// �|�P�����I�u�W�F�N�g

	// �A�N�Z�T���@BG�T���l�C���@���T���l�C��
	// �͓����悤�ɊǗ����邽��
	// �|�P�����ȊO�ł̍ő吔���쐬
	IMC_OBJLIST_ACCE_MAX = IMC_OBJLIST_POKE,
};




//-----------------------------------------------------------------------------
/**
 *				�A�N�Z�T���p�萔�錾
*/
//-----------------------------------------------------------------------------
// �A�N�Z�T������\��
#define IMC_ACCE_GET_9_NUM	( 61 )	// 9���Ă�A�N�Z�T���̐�
#define IMC_ACCE_GET_1_NUM	( 39 )// 1�������ĂȂ��A�N�Z�T���̐�
#define IMC_ACCE_GET_1_START	( IMC_ACCE_GET_9_NUM )


//-------------------------------------
//	
//	�A�N�Z�T���o�^�ő吔
//	
//=====================================
#define IMC_SYS_ACCESSORIE_MAX				(700)					// �A�N�Z�T���o�^�ő吔

//-------------------------------------
//	
//	�A�N�Z�T��Link�f�[�^�A�[�J�C�u�f�[�^idx
//	
//=====================================
#define IMC_ACCESSORIE_PLTT_LINK	(NARC_imageclip_imc_ac_data_dat)

//-------------------------------------
//	
//	�p���b�g�t�@�C���萔
//	
//=====================================
#define	IMC_DRAW_ACCESSORIE_PLTT_FILENUM	(1)						// �p���b�g�t�@�C����
#define	IMC_DRAW_ACCESSORIE_PLTT_NUM		(3)						// �p���b�g�g�p��
#define IMC_DRAW_ACCESSORIE_PLTT_ID			(0)						// ���\�[�X�}�l�[�W���p���b�gID

//-------------------------------------
//	
//	�A�[�J�C�u�f�[�^�Q�Ɨp�}�N��
//	
//=====================================
#define IMC_DRAW_ACCESSORIE_PLTT_ARC	( NARC_imageclip_imgclip_access_NCLR )				// �p���b�g�A�[�J�C�u�擪
#define IMC_DRAW_ACCESSORIE_CHAR_ARC	( NARC_imageclip_imgclip_access_001_0_NCBR )			// �L�����N�^�A�[�J�C�u�擪

// �L�����N�^�A�[�J�C�u�t�@�C���i���o�[�擾
#define IMC_ACCE_ARC_NO_GET(x)		( (x) + IMC_DRAW_ACCESSORIE_CHAR_ARC )

//-------------------------------------
//	
//	�t�H���g�f�[�^�p
//	
//=====================================
#define IMC_ACCE_FONT_START		(imgclipacc_001)
#define IMC_ACCE_FONT_NOGET(x)	( (x)+IMC_ACCE_FONT_START )
//BG
#define IMC_BG_FONT_START		(imgclipback_00)
#define IMC_BG_FONT_NOGET(x)	( (x)+IMC_BG_FONT_START )



//-----------------------------------------------------------------------------
/**
*		BG�f�[�^
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
// BG�f�[�^��
//	
//=====================================
// ����ʗp
enum{
	IMC_BG_LEFT_00,
	IMC_BG_LEFT_01,
	IMC_BG_LEFT_MAX
};
// �t���[���p
enum{
	IMC_BG_FRAME_00,
	IMC_BG_FRAME_01,
	IMC_BG_MAX
};

//-------------------------------------
//	
//	�p���b�g�Ǘ��p
//	
//=====================================
#define IMC_BG_COLOR_NUM		(1)	// �g�p����p���b�g��1�|��


//-------------------------------------
//	
// �A�[�J�C�u�f�[�^�Ǘ��p
//	
//=====================================
// �A�[�J�C�u�t�@�C���J�n�ʒu
#define IMC_BG_RIGHT_ARC_S		(NARC_imageclip_imgclip_rback_00_NCGR)
#define IMC_BG_LEFT_ARC_S		(NARC_imageclip_imgclip_lback_00_NCGR)
#define IMC_BG_FRAME_ARC_S		(NARC_imageclip_imgclip_frame_00_NCGR)
#define IMC_BG_LEFT_FRAME_CL	(NARC_imageclip_imgclip_lback_frame_NCLR)

//-------------------------------------
//	
//	�A�[�J�C�u�f�[�^�擾�}�N��
//	
// �e�f�[�^�擾�}�N��
// �t�@�C�������炱�̏��ԂŃA�[�J�C�u����邽�߁A���̂悤�ɊǗ����Ă��܂��B
// �A�[�J�C�u���Ԃ��t�@�C�����ł͂Ȃ��C�ӂɕς���悤�Ȏ�������΁A���̕�����
// �ς���K�v������܂�
//	
//=====================================
// �E���
#define IMC_BG_RIGHT_CG_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S )
#define IMC_BG_RIGHT_CL_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S+1 )
#define IMC_BG_RIGHT_SC_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S+2 )
#define IMC_BG_RIGHT_SC_ANM_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S+3 )
// �����
#define IMC_BG_LEFT_CG_ARC_GET(x)	( ((x)*2)+IMC_BG_LEFT_ARC_S )
#define IMC_BG_LEFT_SC_ARC_GET(x)	( ((x)*2)+IMC_BG_LEFT_ARC_S+1 )
// �t���[�����
//#define IMC_BG_FRAME_CG_ARC_GET(x)	( IMC_BG_FRAME_ARC_S )
#define IMC_BG_FRAME_CG_ARC_GET(x)	( ((x)*2)+IMC_BG_FRAME_ARC_S )
//#define IMC_BG_FRAME_SC_ARC_GET(x)	( ((x))+IMC_BG_FRAME_ARC_S+1 )
#define IMC_BG_FRAME_SC_ARC_GET(x)	( ((x)*2)+IMC_BG_FRAME_ARC_S+1 )
// �T���l�C���p�f�[�^
//	�p���b�g��BG�ƈꏏ�̕����g�p����
//
//
#define IMC_BG_THUMB_CG_ARC_S		(NARC_imageclip_imgclip_rback_thumb_00_NCBR)	// �L�����N�^�f�[�^�A�[�J�C�u�t�@�C���擪�ԍ�
#define IMC_BG_THUMB_CG_ARC_GET(x)	( (x) + IMC_BG_THUMB_CG_ARC_S )					// �L�����N�^�f�[�^�A�[�J�C�u�t�@�C���ԍ����擾






//-----------------------------------------------------------------------------
/**
*		�{�b�N�X�f�[�^
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
// �{�b�N�X�̃t���[���̕�
//
//	�t���[�������́@�G�ŏ����Ă���t���[��
//	�̕�
//	
//=====================================
#define IMC_BOX_AREA_FRAME_WIDHT	(2)
#define IMC_BOX_AREA_FRAME_HEIGHT	(2)

//-------------------------------------
//	
//	�E�{�b�N�X�G���A
//	
//=====================================
#define IMC_RBOX_AREA_X			( 136 )	
#define IMC_RBOX_AREA_Y			( 16 )		
#define IMC_RBOX_AREA_WIDTH		( 112 )
#define IMC_RBOX_AREA_HEIGHT	( 129 )

// ����\�G���A
#define IMC_RBOX_AREA_X_MOVEOK		( IMC_RBOX_AREA_X + IMC_BOX_AREA_FRAME_WIDHT )	
#define IMC_RBOX_AREA_Y_MOVEOK		( IMC_RBOX_AREA_Y + IMC_BOX_AREA_FRAME_HEIGHT )
#define IMC_RBOX_AREA_WIDTH_MOVEOK	( IMC_RBOX_AREA_WIDTH - (IMC_BOX_AREA_FRAME_WIDHT*2) )
#define IMC_RBOX_AREA_HEIGHT_MOVEOK	( IMC_RBOX_AREA_HEIGHT - (IMC_BOX_AREA_FRAME_HEIGHT*2) )


//-------------------------------------
//	
//	���{�b�N�X�G���A
//	
//=====================================
#define IMC_LBOX_AREA_X	( 8 )	
#define IMC_LBOX_AREA_Y	( 16 )		
#define IMC_LBOX_AREA_WIDTH		( 112 )
#define IMC_LBOX_AREA_HEIGHT	( 129 )

// ����\�G���A
#define IMC_LBOX_AREA_X_MOVEOK		( IMC_LBOX_AREA_X + IMC_BOX_AREA_FRAME_WIDHT )	
#define IMC_LBOX_AREA_Y_MOVEOK		( IMC_LBOX_AREA_Y + IMC_BOX_AREA_FRAME_HEIGHT )
#define IMC_LBOX_AREA_WIDTH_MOVEOK	( IMC_LBOX_AREA_WIDTH - (IMC_BOX_AREA_FRAME_WIDHT*2) )
#define IMC_LBOX_AREA_HEIGHT_MOVEOK	( IMC_LBOX_AREA_HEIGHT - (IMC_BOX_AREA_FRAME_HEIGHT*2) )


// �O�ȊO�Ȃ�P��Ԃ�
#define IMC_NUM_0_CHECK(x)	( (x) ? 1 : 0 )

//-------------------------------------
//	
//	���{�b�N�X
//	���X�g�i�[������
//	
//=====================================
// �A�N�Z�T�����X�g
// �K�v�ȃ��X�g��
#define IMC_LBOX_ACCE_NEAD_LIST_NUM	( 14 )
// ���̒l�܂ł����X�g0
#define IMC_LBOX_ACCE_LIST00_END	( 5 )
// ���̒l�܂ł����X�g1
#define IMC_LBOX_ACCE_LIST01_END	( 11 )
// ���̒l�܂ł����X�g2
#define IMC_LBOX_ACCE_LIST02_END	( 17 )
// ���̒l�܂ł����X�g3
#define IMC_LBOX_ACCE_LIST03_END	( 21 )
// ���̒l�܂ł����X�g4
#define IMC_LBOX_ACCE_LIST04_END	( 28 )
// ���̒l�܂ł����X�g5
#define IMC_LBOX_ACCE_LIST05_END	( 33 )
// ���̒l�܂ł����X�g6
#define IMC_LBOX_ACCE_LIST06_END	( 38 )
// ���̒l�܂ł����X�g7
#define IMC_LBOX_ACCE_LIST07_END	( 42 )
// ���̒l�܂ł����X�g8
#define IMC_LBOX_ACCE_LIST08_END	( 49 )
// ���̒l�܂ł����X�g9
#define IMC_LBOX_ACCE_LIST09_END	( 55 )
// ���̒l�܂ł����X�g10
#define IMC_LBOX_ACCE_LIST10_END	( 60 )
// ���̒l�܂ł����X�g11
#define IMC_LBOX_ACCE_LIST11_END	( 71 )
// ���̒l�܂ł����X�g12
#define IMC_LBOX_ACCE_LIST12_END	( 91 )
// ���̒l�܂ł����X�g13
#define IMC_LBOX_ACCE_LIST13_END	( 99 )

// BG�T���l�C�����X�g
// ����ނ����X�g�ɕ����邩
#define IMC_LBOX_BG_ONE_LIST_NUM	(9)
// ���܂�̐�
#define IMC_LBOX_BG_REST_LIST_NUM	( (IMC_BG_RIGHT_MAX % IMC_LBOX_BG_ONE_LIST_NUM) )
// �K�v�ȃ��X�g��
#define IMC_LBOX_BG_NEAD_LIST_NUM	( (IMC_BG_RIGHT_MAX / IMC_LBOX_BG_ONE_LIST_NUM) + IMC_NUM_0_CHECK(IMC_LBOX_BG_REST_LIST_NUM) )

// ���T���l�C�����X�g
// ����ނ����X�g�ɕ����邩
#define IMC_LBOX_SND_ONE_LIST_NUM	(9)
#define IMC_LBOX_SND_NEAD_LIST_NUM	(1)


//-----------------------------------------------------------------------------
/**
*		�{�^���`��f�[�^�p
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�{�^����
//	
//=====================================
enum{
	IMC_BTTN_RET,		// ���p���b�g���߂���
	IMC_BTTN_RETB,		// ���p���b�g���߂����Ė߂�
	IMC_BTTN_ACE,		// �A�N�Z�T���ύX�Ɉڂ�
	IMC_BTTN_BG,		// BG�ύX�Ɉڂ�
//	IMC_BTTN_SND,		// ���ύX�Ɉڂ�
	IMC_BTTN_END,		// �I���
	IMC_BTTN_MAX		// <-�����L�����N�^��ID
};
#define IMC_BTTN_NORM_MAX (IMC_BTTN_END)

//-------------------------------------
//	
//	�p���b�g��`
//	
//=====================================
#define IMC_BTTN_ARC_FILE_PLTT	(NARC_imageclip_imgclip_button_NCLR)
#define IMC_BTTN_PLTT_LOAD_NUM	(3)
#define	IMC_BTTN_RES_MAN_PLTT	(0)	// ���\�[�X�}�l�[�W���ɓo�^����ID

// OK�����t�H���g�p
#define IMC_BTTN_ARC_FILE_PLTT_FONT		(NARC_imageclip_imgclip_button_font00_NCLR)
#define IMC_BTTN_PLTT_LOAD_NUM_FONT		(2)
#define IMC_BTTN_RES_MAN_PLTT_FONT	(1)	// ���\�[�X�}�l�[�W���ɓo�^����ID

//-------------------------------------
//	
//	�A�[�J�C�u�t�@�C���擾�p�}�N��
//	
//=====================================
// �L�����N�^.�Z���t�@�C��IDX�J�n�ʒu
#define IMC_BTTN_ARC_FILE_CELL	(NARC_imageclip_imgclip_button_00_NANR)
// �L�����N�^�B�Z���B�Z���A�j���擾�}�N��
#define IMC_BTTN_ARC_CANM_GET(x)	( ((x)*3) + IMC_BTTN_ARC_FILE_CELL + 0 )
#define IMC_BTTN_ARC_CELL_GET(x)	( ((x)*3) + IMC_BTTN_ARC_FILE_CELL + 1 )
#define IMC_BTTN_ARC_CHAR_GET(x)	( ((x)*3) + IMC_BTTN_ARC_FILE_CELL + 2 )


//-------------------------------------
//	
// �e��{�^�����W
// �e��{�^���T�C�Y
//	
//=====================================
// �e��{�^�����W
#define IMC_BTTN_Y		(144)
#define IMC_BTTN_RET_Y	(144)
#define IMC_BTTN_RET_X	(48)
#define IMC_BTTN_RETB_X	(8)
#define IMC_BTTN_ACE_X	(96)
#define IMC_BTTN_BG_X	(136)
#define IMC_BTTN_END_X	(184)

// �e��{�^���T�C�Y
#define IMC_BTTN_RET_SIZE_X		(40)
#define IMC_BTTN_RET_SIZE_Y		(32)
#define IMC_BTTN_NOR_SIZE_X		(42)
#define IMC_BTTN_NOR_SIZE_Y		(42)
#define IMC_BTTN_END_SIZE_X		(72)
#define IMC_BTTN_END_SIZE_Y		(42)

#define IMC_BTTN_HIT_Y_OFS	(8)
#define IMC_BTTN_HIT_Y_OFS_NOR_END	(12)

//-------------------------------------
//	
//	�I���{�^����
//	
//=====================================
enum{
	IMC_BTTN_ENDCK_CANCEL,	// �L�����Z��
	IMC_BTTN_ENDCK_END,		// �I���
	IMC_BTTN_ENDCK_MAX		// <-�����L�����N�^��ID
};

//-------------------------------------
//	
//	�A�[�J�C�u�t�@�C���擾�p�}�N��
//	
//=====================================
// �L�����N�^.�Z���t�@�C��IDX�J�n�ʒu
#define IMC_BTTN_ENDCK_ARC_FILE_CELL	(NARC_imageclip_imgclip_button_04_NANR)
// �L�����N�^�B�Z���B�Z���A�j���擾�}�N��
#define IMC_BTTN_ENDCK_ARC_CANM	( IMC_BTTN_ENDCK_ARC_FILE_CELL + 0 )
#define IMC_BTTN_ENDCK_ARC_CELL	( IMC_BTTN_ENDCK_ARC_FILE_CELL + 1 )
#define IMC_BTTN_ENDCK_ARC_CHAR	( IMC_BTTN_ENDCK_ARC_FILE_CELL + 2 )

// �e��{�^�����W
#define IMC_BTTN_ENDCK_Y				(144)
#define	IMC_BTTN_ENDCK_CHANCEL_X	(32)
#define IMC_BTTN_ENDCK_END_X		(168)

// �e��{�^���T�C�Y
#define IMC_BTTN_ENDCK_SIZE_X		(56)
#define IMC_BTTN_ENDCK_SIZE_Y		(32)


//-----------------------------------------------------------------------------
/**
*		�T�u�E�B���h�E�`��f�[�^�萔
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�w�i�A�[�J�C�u�f�[�^
//	
//=====================================
#define IMC_SUBWIN_CG_ARC	(NARC_imageclip_imgclip_top_00_NCGR)
#define IMC_SUBWIN_SC_ARC	(NARC_imageclip_imgclip_top_00_NSCR)
#define IMC_SUBWIN_PL_ARC	(NARC_imageclip_imgclip_top_00_NCLR)
#define IMC_SUBWIN_PL_NUM	(1)


//-------------------------------------
//	
//	�r�b�g�}�b�v�E�B���h�E�`����W
//	
//=====================================
#define IMC_SUBWIN_BMP_X		(2)		// �L�����P��
#define IMC_SUBWIN_BMP_Y		(19)
#define IMC_SUBWIN_BMP_SIZE_X	(27)
#define	IMC_SUBWIN_BMP_SIZE_Y	(4)		
#define IMC_SUBWIN_BMP_WAKU_PLTT_NO	(1)				// �t�H���g�g�g�p�p���b�g�ԍ�
#define IMC_SUBWIN_BMP_PLTT_NO	(2)				// �t�H���g�g�p�p���b�g�ԍ�

#define IMC_SUBWIN_BMP_FRAME_CHAR_OFS	(1)

// �����N�`��p
#define IMC_SUBWIN_RANKBMP_X		(2)		// �L�����P��
#define IMC_SUBWIN_RANKBMP_Y		(1)
#define IMC_SUBWIN_RANKBMP_SIZE_X	(27)
#define	IMC_SUBWIN_RANKBMP_SIZE_Y	(2)		
#define IMC_SUBWIN_RANKBMP_FRAME_CHAR_OFS	(IMC_SUBWIN_BMP_FRAME_CHAR_OFS +(IMC_SUBWIN_BMP_SIZE_X * IMC_SUBWIN_BMP_SIZE_Y) )

// �����`��p
#define IMC_SUBWIN_COUNTBMP_X		(10)		// �L�����P��
#define IMC_SUBWIN_COUNTBMP_Y		(8)
#define IMC_SUBWIN_COUNTBMP_SIZE_X	(14)
#define	IMC_SUBWIN_COUNTBMP_SIZE_Y	(4)		
#define IMC_SUBWIN_COUNTBMP_FRAME_CHAR_OFS	(IMC_SUBWIN_RANKBMP_FRAME_CHAR_OFS + (IMC_SUBWIN_RANKBMP_SIZE_X*IMC_SUBWIN_RANKBMP_SIZE_Y) )



//-----------------------------------------------------------------------------
/**
*	�E�{�b�N�X�v���C���[
*/
//-----------------------------------------------------------------------------
// BG�A�j���^�C�~���O
#define IMC_RBOX_PLAYER_BG_ANM_TIMING		(16)
#define IMC_RBOX_PLAYER_BG_ANM_FRAME		(1)


//-----------------------------------------------------------------------------
/**
*	�I�u�W�F�N�g���X�g�ő吔
*/
//-----------------------------------------------------------------------------
#define	IMC_OBJLIST_MAX	(IMC_SYS_ACCESSORIE_MAX + 1 + IMC_BG_RIGHT_MAX)
// ����
//	�A�N�Z�T��	�|�P�����P��	BG�T���l�C��
//	IMC_OBJLIST_TBL	�쐬�ȂǂɎg�p
//
//	�^�b�`�؂�őI�������肷��X�v���C�g�I�u�W�F�̐�



//-----------------------------------------------------------------------------
/**
*		�X�v���C�g�t�@�C���f�[�^��
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�X�v���C�g�V�X�e��
//	�쐬���ȂǂɎg�p����
//	�f�[�^�o�^�ő吔
//	
//=====================================
#define IMC_SPRITE_OBJ_NUM		(IMC_SYS_ACCESSORIE_MAX + IMC_BG_RIGHT_MAX)
#define	IMC_SPRITE_CHAR_NUM		(IMC_ACCE_MAX + IMC_BG_RIGHT_MAX)
#define	IMC_SPRITE_PLTT_NUM		(IMC_DRAW_ACCESSORIE_PLTT_FILENUM + IMC_BG_RIGHT_MAX)

//-------------------------------------
//	
//	�|�P�����I�u�W�F�͕ʃV�X�e��
//	�������A�L�����N�^�f�[�^��
//	�X�v���C�g�V�X�e���̕��ƈꏏ��
//	�Ǘ����邽�ߒ萔���쐬
//	���݃L�����N�^�f�[�^��ۑ����Ă������
//	�A�N�Z�T���@�|�P�����@BG�T���l�C��
//	
//=====================================
// �|�P�����p�L�����N�^�o�^ID
#define IMC_DRAW_POKE_CHAR_ID		(IMC_SPRITE_CHAR_NUM)	
// �|�P���������ꂽ�L�����N�^�f�[�^��
#define IMC_SPRITE_OBJ_CHAR_NUM	(IMC_DRAW_POKE_CHAR_ID + 1)				

//-------------------------------------
//	
//	�A�N�Z�T����
//	�L�����N�^�E�p���b�g�f�[�^���擾
//	����Ƃ���ID�i�v�f���j���擾
//	
//=====================================
#define IMC_ACCE_CHAR_CONT_ID(x)	( (x) )
#define IMC_ACCE_PLTT_CONT_ID(x)	( IMC_DRAW_ACCESSORIE_PLTT_ID)

//-------------------------------------
//	
//	BG�T���l�C����
//	�L�����N�^�E�p���b�g�f�[�^���擾
//	����Ƃ���ID�i�v�f���j���擾
//	
//=====================================
#define IMC_BG_THUMB_CHAR_CONT_ID(x)	( (x) + IMC_ACCE_MAX )
#define IMC_BG_THUMB_PLTT_CONT_ID(x)	( (x) + IMC_DRAW_ACCESSORIE_PLTT_FILENUM )	//�A�N�Z�T���p���b�g�P�{�����炷

//-------------------------------------
//	
//	SND�T���l�C����
//	�L�����N�^�E�p���b�g�f�[�^���擾
//	����Ƃ���ID�i�v�f���j���擾
//	
//=====================================
#define IMC_SND_THUMB_CHAR_CONT_ID(x)	( (x) + IMC_ACCE_MAX )
#define IMC_SND_THUMB_PLTT_CONT_ID(x)	( (x) + IMC_DRAW_ACCESSORIE_PLTT_FILENUM )	//�A�N�Z�T���p���b�g�P�{�����炷



//-------------------------------------
//	
//	�I���`�F�b�N��ʃE�B���h�E���j���[�p	
//	
//=====================================
#define IMC_ENDCHECK_YESNO_CHAR_OFFS	( 0 )	// YESNO�{�^���̃L�����N�^�I�t�Z�b�g
#define IMC_ENDCHECK_YESNO_PLTT_OFFS	( 5 )	// �g�p�p���b�g
#define IMC_ENDCHECK_YESNO_X			( 25 )	// X�L�����ʒu
#define IMC_ENDCHECK_YESNO_Y			( 4 )	// Y�L�����ʒu
#define IMC_ENDCHECK_WND_X				( 2 )	// X�L�����ʒu
#define IMC_ENDCHECK_WND_Y				( 1 )	// Y�L�����ʒu
#define IMC_ENDCHECK_WND_SIZX			( 27 )	// X�L�����T�C�Y
#define IMC_ENDCHECK_WND_SIZY			( 2 )	// Y�L�����T�C�Y
#define IMC_ENDCHECK_WND_PAL			( 7 )	// �g�p�p���b�g�ԍ�
#define IMC_ENDCHECK_WND_CHROFS			( 0+TOUCH_SW_USE_CHAR_NUM+TALK_WIN_CGX_SIZ )	// �g�p�L�����N�^�I�t�Z�b�g�@�L�����N�^�P��
#define IMC_ENDCHECK_WND_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )	// �J���[�}�X�N
#define IMC_ENDCHECK_WNDWAKU_PAL		( 8 )	// �g�p���b�g
#define IMC_ENDCHECK_WNDWAKU_CHROFS		(0+TOUCH_SW_USE_CHAR_NUM)	// �g�L�����N�^�I�t�Z�b�g

// �R���e�X�g�����p
#define IMC_CONTESTTEXT_WND_X				( 2 )	// X�L�����ʒu
#define IMC_CONTESTTEXT_WND_Y				( 19 )	// Y�L�����ʒu
#define IMC_CONTESTTEXT_WND_SIZX			( 27 )	// X�L�����T�C�Y
#define IMC_CONTESTTEXT_WND_SIZY			( 4 )	// Y�L�����T�C�Y

//-------------------------------------
//	�̪�ē���萔
//=====================================
#define IMC_SEENFADE_BRIGHTNESS_FADE_SYNC	(8)
#define IMC_SEENFADE_MOVE_ADD_X				(8)
#define IMC_SEENFADE_MOVE_ADD_Y				(5)
#define IMC_SEENFADE_MOVE_COUNT				(8)
#define IMC_SEENFADE_BG_MOVE_Y				( IMC_SEENFADE_MOVE_ADD_Y * IMC_SEENFADE_MOVE_COUNT )
#define IMC_SEENFADE_BTTNMOVE_DIS			(64)
#define IMC_SEENFADE_BTTNMOVE_ADD_Y			(8)
#define IMC_SEENFADE_BTTNMOVE_COUNT			(8)

// �I���`�F�b�N��ʂł̉E�{�b�N�X�O���t�B�b�N�̕`��ʒu
#define IMC_RBOX_END_SX						(IMC_RBOX_AREA_X - (IMC_SEENFADE_MOVE_ADD_X*IMC_SEENFADE_MOVE_COUNT))
#define IMC_RBOX_END_SY						(IMC_RBOX_AREA_Y + (IMC_SEENFADE_MOVE_ADD_Y*IMC_SEENFADE_MOVE_COUNT))


// �Z���A�N�^�[�Z�b�g�T�u�ʃT�[�t�F�[�X�ʒu
#define IMC_CLACT_SUB_SURFACE_Y	( 512*FX32_ONE )

//-------------------------------------
//	�R���e�X�g�f�[�^
//=====================================
#define IMC_POKE_MAT_CONTEST_Y_OFS	( -4 )


//-----------------------------------------------------------------------------
/**
*		�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------


#undef	GLOBAL
#endif		// IMC_DRAWDATA_DEFINE_H__

