//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_bg.h
 *	@brief		BG�Ǘ��V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_BG_H__
#define __IMC_BG_H__

#include <nnsys.h>
#include "bg_system.h"

#undef GLOBAL
#ifdef	__IMC_BG_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define IMC_BG_SCR_OFS	(128)	// �X�N���[���L�����N�^�I�t�Z�b�g
#define IMC_BG_SCR_PLTT_OFS	(0x5)	// �X�N���[���p���b�g�I�t�Z�b�g
#define IMC_BG_SCR_MAT_SX	(0)		// �X�N���[���X�N���[���z�u�ʒu
#define IMC_BG_SCR_MAT_SY	(0)		// �X�N���[���X�N���[���z�u�ʒu

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	BG�f�[�^�\����	
//	
//=====================================
typedef struct {
	GF_BGL_INI* bg_ini;

	int arc_file;		// �A�[�J�C�u�t�@�C���i���o�[	
	int scrn_arc;		// �X�N���[���f�[�^�C���f�b�N�X
	
	int x;			// �X�N���[���\��t���L�����N�^�I�t�Z�b�g
	int y;			// �X�N���[���\��t���L�����N�^�I�t�Z�b�g
	int width_char;	// ��	�L�����N�^�P��
	int height_char;// ����	�L�����N�^�P��
	int frame;		// BG�t���[��
	int pltt_offs;	// �p���b�g�I�t�Z�b�g�i�ԍ��j
	int pltt_num;	// �p���b�g�{��
	int char_offs;	// �L�����N�^�I�t�Z�b�g	(�L�����N�^�P��)
} IMC_BG;

//-------------------------------------
//	
//	�o�^�f�[�^
//	
//=====================================
typedef struct {
	GF_BGL_INI* bg_ini;

	int arc_file;		// �A�[�J�C�u�t�@�C���i���o�[	
	int char_arc;		// �L�����N�^�f�[�^�C���f�b�N�X
	int pltt_arc;		// �p���b�g�f�[�^�C���f�b�N�X
	int scrn_arc;		// �X�N���[���f�[�^�C���f�b�N�X
	
	int x;		// ���W	(0~255)
	int y;		// ���W	(0~255)
	int frame;	// BG�t���[��
	int pltt_num;	// �]���p���b�g�{��
	int pltt_offs;	// �p���b�g�I�t�Z�b�g�i�ԍ��j
	int char_offs;	// �L�����N�^�I�t�Z�b�g

	int heap;			// �g�p����q�[�v
} IMC_BG_ADD;

//-------------------------------------
//	
//	BG�A�j���\����
//	
//=====================================
typedef struct {
	const IMC_BG*		bg;		// bg�f�[�^
	int scrn_arc01;		// �X�N���[���f�[�^�C���f�b�N�X
	int timing;			// �ύX�^�C�~���O
	int	count;			// �^�E���^
	int scrn_no;		// ���̃X�N���[��No
	int heap;			// �g�p����q�[�v
} IMC_BG_ANM;

//-------------------------------------
//	
//	BG�A�j���������f�[�^�\����
//	
//=====================================
typedef struct {
	const IMC_BG*		bg;			// bg�f�[�^
	int			scrn_arc;	// 2�t���[���ڂ�BG
	int			timing;		// �ύX�^�C�~���O
	int			heap;
} IMC_BG_ANM_INIT;




//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�f�[�^�̓o�^ & �V�K�ύX
 *
 *	@param	obj		BG�I�u�W�F
 *	@param	add		�o�^�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BG_MakaObj( IMC_BG* obj, IMC_BG_ADD* add );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�f�[�^�̔j��
 *
 *	@param	obj		BG�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BG_DeleteObj( IMC_BG* obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�A�j���[�V����������
 *
 *	@param	anm		�A�j��BG�f�[�^�i�[��
 *	@param	init	�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BG_AnmInit( IMC_BG_ANM* anm, IMC_BG_ANM_INIT* init );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�j���[�V�����X�V
 *
 *	@param	anm		�A�j���[�V����BG
 *	@param	frame	�i�߂�t���[���l
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BG_Anm( IMC_BG_ANM* anm, int frame );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�A�j�����I��������
 *
 *	@param	anm		�A�j���[�V����BG
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BG_AnmDelete( IMC_BG_ANM* anm );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG��Scroll�����܂��B
 *
 *	@param	obj		���\�����Ă���BG
 *	@param	scr_bg	�X�N���[����BG
 *	@param	scr_x	�X�N���[�������邘�l
 *	@param	scr_y	�X�N���[�������邙�l
 *	@param	scr_sync�X�N���[���Ɏg���V���N��
 *	@param	end_flg	�I�����m�t���O
 *
 *	@return	none
 *
 * �ŏI�I�ɂ�scr_bg�̕���BG����ʂɏo��悤�ɂȂ�܂�
 *
 * �܂�BG�f�[�^�z�u��
 * 256x256��
 * ����128~255�̕����ɃL�����N�^������悤�ɂȂ��Ă���K�v������܂��B
 *
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BG_ScrollReq( IMC_BG* obj, IMC_BG_ADD* scr_bg, int scr_x, int scr_y, int scr_sync, BOOL* end_flg );

#undef	GLOBAL
#endif		// __IMC_BG_H__

