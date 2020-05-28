//============================================================================================
/**
 * @file	bmp_cursor.h
 * @brief	BitmapWindow�Ƀ��j���[�I��p�̃J�[�\����`�悷��d�g��
 * @author	taya
 * @date	2006.01.12
 */
//============================================================================================
#ifndef __BMP_CURSOR_H__
#define __BMP_CURSOR_H__

#include "gflib\msg_print.h"

typedef struct _BMPCURSOR	BMPCURSOR;


//------------------------------------------------------------------
/**
 * Bitmap�J�[�\�����쐬
 *
 * @param   heapID		�쐬��q�[�v�h�c
 *
 * @retval  BMPCURSOR*		�쐬���ꂽ�J�[�\���I�u�W�F�N�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
extern BMPCURSOR* BMPCURSOR_Create( u32 heapID );

//------------------------------------------------------------------
/**
 * Bitmap�J�[�\����j��
 *
 * @param   bmpCursor		Bitmap�J�[�\���I�u�W�F�N�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
extern void BMPCURSOR_Delete( BMPCURSOR* bmpCursor );

//------------------------------------------------------------------
/**
 * Bitmap�J�[�\���̃J���[�ύX
 *
 * @param   bmpCursor		Bitmap�J�[�\���I�u�W�F�N�g�ւ̃|�C���^
 * @param   color			�J���[�l�iGF_PRINTCOLOR_MAKE�}�N�����g�p�j
 *
 */
//------------------------------------------------------------------
extern void BMPCURSOR_ChangeColor( BMPCURSOR* bmpCursor, GF_PRINTCOLOR color );

//------------------------------------------------------------------
/**
 * Bitmap�J�[�\����BitmapWindow�ɕ`�悷��
 *
 * @param   bmpCursor	Bitmap�J�[�\���I�u�W�F�N�g�ւ̃|�C���^
 * @param   win			BitmapWindow
 * @param   x			�`��w���W�i�h�b�g�P�ʁj
 * @param   y			�`��x���W�i�h�b�g�P�ʁj
 *
 */
//------------------------------------------------------------------
extern void BMPCURSOR_Print( const BMPCURSOR* bmpCursor, GF_BGL_BMPWIN* win, u32 x, u32 y );



#endif

