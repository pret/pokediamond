//============================================================================================
/**
 * @file	numfont.h
 * @brief	�����t�H���g
 * @author	taya
 * @date	2005.09.30
 */
//============================================================================================
#ifndef __NUMFONT_H__
#define __NUMFONT_H__

#include  "system\pm_str.h"

//------------------------------------------------------
/**
 *	�����t�H���g���̍\���̂̌^�錾�i���e�͔���J�j
 */
//------------------------------------------------------
typedef   struct _NUMFONT    NUMFONT;

//------------------------------------------------------
/**
 *	���l�`�惂�[�h
 */
//------------------------------------------------------
typedef enum {
	NUMFONT_MODE_LEFT = NUM_MODE_LEFT,		///< ���l
	NUMFONT_MODE_SPACE = NUM_MODE_SPACE,	///< �E�l�A����Ȃ������̓X�y�[�X����
	NUMFONT_MODE_ZERO = NUM_MODE_ZERO,		///< �E�l�A����Ȃ������̓[������
}NUMFONT_DRAW_MODE;

//------------------------------------------------------
/**
 *	�L�����
 */
//------------------------------------------------------
typedef enum {
	NUMFONT_MARK_SLASH,
	NUMFONT_MARK_LV,
	NUMFONT_MARK_NO,
	NUMFONT_MARK_ID,
	NUMFONT_MARK_MALE_LV,		// ���L����LV�̍����i�퓬�Q�[�W��p�j
	NUMFONT_MARK_FEMALE_LV,		// ���L����LV�̍����i�퓬�Q�[�W��p�j
	NUMFONT_MARK_BATTLE_LV,		// �Ō�Ƀh�b�g�����Ȃ�LV�i�퓬�Q�[�W��p�j
}NUMFONT_MARK;

//------------------------------------------------------
/**
 *	�������E�����i�萔�j
 */
//------------------------------------------------------
enum {
	NUMFONT_NUM_WIDTH = 8,		///< �����P�����̕�
	NUMFONT_MARK_WIDTH = 16,	///< �L���P���̕�
	NUMFONT_HEIGHT = 8,			///< ����
};

//------------------------------------------------------------------
/**
 * �����t�H���g�쐬
 *
 * @param   colLetter	�����F�ԍ�
 * @param   colShadow	�e�F�ԍ�
 * @param   colBack		�w�i�F�ԍ�
 * @param   heapID		�q�[�v�h�c
 *
 * @retval  NUMFONT*	�����t�H���g���̂ւ̃|�C���^�i���e�͔���J�j
 */
//------------------------------------------------------------------
extern NUMFONT*  NUMFONT_Create( u32 colLetter, u32 colShadow, u32 colBack, u32 heapID );


//------------------------------------------------------------------
/**
 * �����t�H���g�j��
 *
 * @param   numfont		�����t�H���g�|�C���^
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_Delete( NUMFONT* numfont );

//------------------------------------------------------------------
/**
 * �L���`��
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   mark		�L�����
 * @param   win			�`���E�B���h�E
 * @param   x			�`���w���W�i�h�b�g�j
 * @param   y			�`���x���W�i�h�b�g�j
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteMark( NUMFONT* numfont, NUMFONT_MARK mark, GF_BGL_BMPWIN* win, u32 x, u32 y );

//------------------------------------------------------------------
/**
 * ���l�`��
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   num			���l
 * @param   keta		�ő包��
 * @param   mode		���l�`�惂�[�h
 * @param   win			�`���E�B���h�E
 * @param   x			�`���w���W�i�h�b�g�j
 * @param   y			�`���x���W�i�h�b�g�j
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteNumber( NUMFONT* numfont, s32 num, u32 keta, NUMFONT_DRAW_MODE mode, GF_BGL_BMPWIN* win, u32 x, u32 y );

//------------------------------------------------------------------
/**
 * �L���E���l����ׂĕ`��
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   mark		�L�����
 * @param   num			���l
 * @param   keta		�ő包��
 * @param   mode		���l�`�惂�[�h
 * @param   win			�`���E�B���h�E
 * @param   x			�`���w���W�i�h�b�g�j
 * @param   y			�`���x���W�i�h�b�g�j
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteSet( NUMFONT* numfont, NUMFONT_MARK mark, s32 num, u32 keta, NUMFONT_DRAW_MODE mode, GF_BGL_BMPWIN* win, u32 x, u32 y );

//------------------------------------------------------------------
/**
 * ���l�`��(�w��o�b�t�@�ɑ΂��ăL�����N�^�f�[�^�̂ݏ�������)
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   num			���l
 * @param   keta		�ő包��
 * @param   mode		�`�����
 * @param   buf			�`���o�b�t�@
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteNumberCGXOnly( NUMFONT* numfont, s32 num, u32 keta, 
	NUMFONT_DRAW_MODE mode, void *buf);

//--------------------------------------------------------------
/**
 * @brief   �L���`��(�w��o�b�t�@�ɑ΂��ăL�����N�^�f�[�^�̂ݏ�������)
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   mark		�L���^�C�v
 * @param   buf			�W�J�o�b�t�@��ւ̃|�C���^
 *
 * @retval  
 *
 * buf�� �u(NUMFONT_MARK_WIDTH / 8) * (NUMFONT_HEIGHT / 8) * 32�v �̃T�C�Y���K�v�ł��B
 */
//--------------------------------------------------------------
extern void NUMFONT_WriteMarkCGXOnly( NUMFONT* numfont, NUMFONT_MARK mark, void *buf);

#endif
