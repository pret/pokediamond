//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fontoam.h
 *	@brief		OAM���g�p����������`��V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.10.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FONTOAM_H__
#define __FONTOAM_H__

#include <nnsys.h>
#include "clact.h"

#undef GLOBAL
#ifdef	__FONTOAM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif
//-----------------------------------------------------------------------------
/**
 *
 * OAM�t�H���g�V�X�e������
 *
 * ��{�I�Ȏg�p���@
 *
 * �P�F�V�X�e�����[�N�i��{�j�쐬
 *		FONTOAM_SYS_PTR FONTOAM_SysInit( int workNum, int heap );
 *
 * �Q�F�\��t����r�b�g�}�b�v�f�[�^�쐬
 *
 * �R�FOAM�t�H���g�쐬
 *		FOTNOAM_OBJ_PTR	FONTOAM_Init( const FONTOAM_INIT* fontoam_init );
 *
 * �S�FOAM�t�H���g�𓮂���
 *		FONTOAM_SetMat();�ȂǃZ���A�N�^�[�ɂ��鑀��֐��̉�]�A�g��k���ȊO�͗p�ӂ���Ă��܂��B
 *
 * �T�FOAM�t�H���g�̔j��
 *		FONTOAM_Delete( FONTOAM_OBJ_PTR fontoam );
 *
 * �U�FOAM�t�H���g�V�X�e�����[�N�̔j��
 *		FONTOAM_SysDelete( FONTOAM_SYS_PTR fntoam_sys );
 *
 *
 */
//-----------------------------------------------------------------------------

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
//	1OAM�t�H���g�f�[�^
//	
//=====================================
typedef struct _FONTOAM_OBJ*		FONTOAM_OBJ_PTR;
typedef const struct _FONTOAM_OBJ*	CONST_FONTOAM_OBJ_PTR;

//-------------------------------------
//	
//	�V�X�e���f�[�^
//	
//=====================================
typedef struct _FONTOAM_SYSTEM*			FONTOAM_SYS_PTR;
typedef const struct _FONTOAM_SYSTEM*	CONST_FONTOAM_SYS_PTR;


//-------------------------------------
//	
//	�t�H���g�f�[�^�o�^�\����
//	
//=====================================
typedef struct {
	CONST_FONTOAM_SYS_PTR	fontoam_sys;// �t�H���g�V�X�e���f�[�^
	const GF_BGL_BMPWIN* bmp;			// �\��t����r�b�g�}�b�v�f�[�^
	CLACT_SET_PTR		clact_set;		// �Z���A�N�^�[�Z�b�g
	const NNSG2dImagePaletteProxy* pltt;// �Z���Q�Ɛ�p���b�g�v���N�V
	CONST_CLACT_WORK_PTR	parent;		// �e�̃A�N�^�[		����Ȃ��Ƃ�NULL	�i�{�^���Ȃǁj
	int					char_ofs;		// �L�����N�^�f�[�^�]���I�t�Z�b�g
	int					x;				// �o�^�����W		�e�A�N�^�[������Ƃ��͐e����̃I�t�Z�b�g�����W	(dot�P��)
	int					y;				// �o�^�����W		�e�A�N�^�[������Ƃ��͐e����̃I�t�Z�b�g�����W	(dot�P��)
	int					bg_pri;			// bg�D�揇��
	int					soft_pri;		// �\�t�g�D�揇��
	int					draw_area;		// �\����
	/*
		NNS_G2D_VRAM_TYPE_2DMAIN    �Q�c�O���t�B�b�N�X�G���W���`�p
		NNS_G2D_VRAM_TYPE_2DSUB     �Q�c�O���t�B�b�N�X�G���W���a�p*/
	int					heap;			// �g�p����q�[�v	
} FONTOAM_INIT;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�V�X�e���̍쐬
 *
 *	@param	workNum		�Ǘ����镶����
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	FONTOAM_SYS_PTR		�쐬����OAM�t�H���g�V�X�e���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_SYS_PTR FONTOAM_SysInit( int workNum, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�V�X�e���̔j��
 *
 *	@param	fntoam_sys	OAM�t�H���g�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SysDelete( FONTOAM_SYS_PTR fntoam_sys );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�쐬
 *
 *	@param	fontoam_init	OAM�t�H���g�쐬�f�[�^
 *
 *	@return	FONTOAM_OBJ_PTR	OAM�t�H���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_OBJ_PTR FONTOAM_Init( const FONTOAM_INIT* fontoam_init );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g�j��
 *
 *	@param	fontoam 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_Delete( FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�r�b�g�}�b�v�E�B���h�E��OAM�t�H���g�V�X�e���ŕ\�����邽�߂ɕK�v�ȃL�����N�^�f�[�^�T�C�Y���擾
 *
 *	@param	bmp		�r�b�g�}�b�v�f�[�^
 *	@param	draw_area	�`��G���A
 *	@param	heap	�g�p����q�[�v
 *
 *	@return	�\�����邽�߂ɕK�v�ȃL�����N�^�T�C�Y
	
	draw_area
		NNS_G2D_VRAM_TYPE_2DMAIN    �Q�c�O���t�B�b�N�X�G���W���`�p
		NNS_G2D_VRAM_TYPE_2DSUB     �Q�c�O���t�B�b�N�X�G���W���a�p
 *	
 *	char_manager���g�p���Ă���Ƃ��́A���̃T�C�Y��
 *	���Vram�̈���m�ۂ��Ă����K�v�����邽�ߍ쐬
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int FONTOAM_NeedCharSize( const GF_BGL_BMPWIN* bmp, int draw_area,  int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g���W��ݒ�
 *
 *	@param	fontoam		OAM�t�H���g
 *	@param	x			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *	@param	y			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetMat( FONTOAM_OBJ_PTR fontoam, int x, int y );

//----------------------------------------------------------------------------
/**
 * ���e�Z���A�N�^�[��ݒ肵�Ă��Ȃ��ꍇ�͎g�p���Ă��Ӗ�������܂���B
 *	
 *	@brief	�e�A�N�^�[�̍��W�ʒu�Ɉʒu�����킹��
 *
 *	@param	fontoam 
 *
 *	@return
 *
 * ���e�Z���A�N�^�[�̈ʒu��ύX�����Ƃ��ɌĂ�ł��������B
 *	�@�e�ɍ��킹�ĕ����������܂�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_ReflectParentMat( FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�t�H���g���W���擾
 *
 *	@param	fontoam		OAM�t�H���g
 *	@param	x			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *	@param	y			�����W		�e�A�N�^�[������Ƃ��̓I�t�Z�b�g���W
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_GetMat( CONST_FONTOAM_OBJ_PTR fontoam, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\��/��\���ݒ�
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *	@param	flag		�\��/��\���t���O
 *
 *	@return	none
 *
 * flag
 *	TRUE	�\��
 *	FALSE	��\��
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetDrawFlag( FONTOAM_OBJ_PTR fontoam, BOOL flag );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\��/��\�����擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@retval	TRUE	�\����
 *	@retval	FALSE	��\����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL FONTOAM_GetDrawFlag( CONST_FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ʂƂ̗D�揇�ʂ�ݒ�
 *
 *	@param	fontoam	OAM�t�H���g�f�[�^
 *	@param	pri		BG�Ƃ̗D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetBGPriority( FONTOAM_OBJ_PTR fontoam, u8 pri );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ʂƂ̕`��D�揇�ʂ��擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@return	BG�ʂƂ̗D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int FONTOAM_GetBGPriority( CONST_FONTOAM_OBJ_PTR fontoam );

//-----------------------------------------------------------------------------
/**
 *	@brief	�`��D�揇�ʂ�ݒ�
 *
 *	@param	fontoam		OAM�t�H���g�f�[�^
 *	@param	pri			�\���D�揇��
 *				
 * 
 *	@return	none
 */
 //----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetDrawPriority( FONTOAM_OBJ_PTR fontoam, u32 pri );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��D�揇�ʂ��擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@return	u32			�`��D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 FONTOAM_GetDrawPriority( CONST_FONTOAM_OBJ_PTR fontoam );

//-----------------------------------------------------------------------------
/**
 * ��OAM�����̃p���b�g�i���o�[������悤�ɂȂ�܂��B
 *
 *	@brief				�p���b�g�i���o�[��ύX
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *	@param	pltt_no		�ݒ�p���b�g�i���o�[
 * 
 *	@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetPaletteNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no );
GLOBAL void FONTOAM_SetPaletteNoAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�i���o�[�擾
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *
 *	@return	u32			���̃p���b�g�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 FONTOAM_GetPaletteNo( CONST_FONTOAM_OBJ_PTR fontoam );

//-----------------------------------------------------------------------------
/**
 * ��OAM�A�g���r���[�g�ɐݒ肳��Ă���p���b�g�i���o�[�ɉ��Z����܂��B
 *	 �����AOAM�A�g���r���[�g�̃J���[�p���b�gNo���Q�ŃI�t�Z�b�g�ɂQ��
 *	 �ݒ肷��ƁA�S�̃J���[�p���b�g���Q�Ƃ���悤�ɂȂ�܂�
 * 
 *	@brief	�p���b�g�I�t�Z�b�g��ݒ�
 *
 *	@param	fontoam		OAM�t�H���g�I�u�W�F
 *	@param	pltt_ofs	�p���b�g�I�t�Z�b�g
 * 
 *	@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetPaletteOffset( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs );
GLOBAL void FONTOAM_SetPaletteOffsetAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�I�t�Z�b�g�l�擾
 *
 *	@param	fontoam	OAM�t�H���g�I�u�W�F
 *
 *	@return	u32		���̃p���b�g�I�t�Z�b�g�l
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 FONTOAM_GetPaletteOffset( CONST_FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ�
 *
 *	@param	fontoam	OAM�t�H���g�I�u�W�F
 *	@param	flag	�t���O	TRUE�����U�C�NON	FALSE�����U�C�NOFF
 *
 *	@return	none
 *
 * ���U�C�NOFF�̎��ł��A�j�g���L�����N�^�Ń��U�C�NON�ɂ���OAM��
 * ���U�C�N���������ĕ`�悳��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetMosaic( FONTOAM_OBJ_PTR fontoam, BOOL flag );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ��Ԃ��擾
 *
 *	@param	fontoam	OAM�t�H���g�I�u�W�F
 *
 *	@retval	TRUE	���U�C�N��ON
 *	@retval	FALSE	���U�C�N��OFF	�i�j�g���L�����N�^�Őݒ肵�Ă�Ƃ��͔��f�����j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL FONTOAM_GetMosaic( CONST_FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g���[�h�̐ݒ�
 *
 *	@param	fontoam		�t�H���gOAM
 *	@param	objmode		�I�u�W�F���[�h
 *
 *	@return	none
 *
	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
	GX_OAM_MODE_XLU			������OBJ 
	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_ObjModeSet( FONTOAM_OBJ_PTR fontoam, GXOamMode objmode );

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F���[�h�̎擾
 *
 *	@param	fontoam		FONTOAM
 *	@param	objmode		�I�u�W�F���[�h
 *
 *	@retval	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 *	@retval	GX_OAM_MODE_XLU			������OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 */
//-----------------------------------------------------------------------------
GXOamMode FONTOAM_ObjModeGet( CONST_FONTOAM_OBJ_PTR fontoam, GXOamMode objmode );




//-----------------------------------------------------------------------------
/**
 *		FONTOAM	�ׂ���������o�[�W����
 */
//-----------------------------------------------------------------------------
typedef struct _FONTOAM_OAM_DATA_SET* FONTOAM_OAM_DATA_PTR;
typedef const struct _FONTOAM_OAM_DATA_SET* CONST_FONTOAM_OAM_DATA_PTR;

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^�쐬
 *
 *	@param	bmp		�f�[�^�쐬���r�b�g�}�b�v
 *	@param	heap	�q�[�v
 *
 *	@return	�����f�[�^
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_OAM_DATA_PTR FONTOAM_OAMDATA_Make( const GF_BGL_BMPWIN* bmp, int heap );
//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^�̔j��
 *
 *	@param	oamdata	�t�H���gOAM�����f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_OAMDATA_Free( FONTOAM_OAM_DATA_PTR oamdata );
//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^����]���ɕK�v���L�����N�^�T�C�Y���擾
 *
 *	@param	oamdata		�t�H���gOAM�����f�[�^
 *	@param	draw_area	�`��G���A
 *
 *	@return	�K�v���L�����N�^�T�C�Y
 */
//-----------------------------------------------------------------------------
GLOBAL int FONTOAM_OAMDATA_NeedCharSize( CONST_FONTOAM_OAM_DATA_PTR oamdata, int draw_area );

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�����f�[�^���g�p���ăt�H���gOAM�̍쐬
 *
 *	@param	fontoam_init		�ӂ����OAM �쐬�f�[�^
 *	@param	oamdata				OAM�����f�[�^
 *
 *	@return	�쐬���ꂽ�t�H���gOAM
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_OBJ_PTR FONTOAM_OAMDATA_Init( const FONTOAM_INIT* fontoam_init, CONST_FONTOAM_OAM_DATA_PTR oamdata );
//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�H���g�j��
 *
 *	@param	fontoam 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_OAMDATA_Delete( FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�̃r�b�g�}�b�v�f�[�^��ύX����
 *
 *	@param	fontoam		�ύX����FONTOAM
 *	@param	oamdata		OAM�����f�[�^
 *	@param	bmp			�r�b�g�}�b�v 
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 *	�����ӓ_
 *		�r�b�g�}�b�v�̑傫�����������K�v������܂��B
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_OAMDATA_ResetBmp( FONTOAM_OBJ_PTR fontoam, CONST_FONTOAM_OAM_DATA_PTR oamdata, const GF_BGL_BMPWIN* bmp, int heap );


//-----------------------------------------------------------------------------
/**
 *		FONTOAM�Ƃ͖��֌W�ł����A�ėp�I�Ɏg�p�ł���֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BMP�̃L�����N�^�f�[�^��OAM�̃T�C�Y�Ő؂���
 *
 *	@param	bmp				�r�b�g�}�b�v�f�[�^
 *	@param	oam_csx			OAM�̉��T�C�Y	�i�L�����N�^�P�ʁj
 *	@param	oam_csy			OAM�̏c�T�C�Y	�i�L�����N�^�P�ʁj
 *	@param	bmp_cmx			�r�b�g�}�b�v�؂��荶�゘���W	�i�L�����N�^�P�ʁj
 *	@param	bmp_cmy			�r�b�g�}�b�v�؂��荶�゙���W	�i�L�����N�^�P�ʁj
 *	@param	char_buff		�o�͐�L�����N�^�o�b�t�@ (oam_csx * oam_csy)*32byte�@�T�C�Y�ȏ�̗̈�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_BmpCutOamSize( const GF_BGL_BMPWIN* cp_bmp, int oam_csx, int oam_csy, int bmp_cmx, int bmp_cmy, char* char_buff );



#undef	GLOBAL
#endif		// __FONTOAM_H__

