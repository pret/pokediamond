//==============================================================================================
/**
 * @file	opneing_bmp.h
 * @brief	�I�[�v�j���O BMP
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#ifndef _OPENING_BMP_H_
#define _OPENING_BMP_H_

#include "opening_sys.h"


//==============================================================================================
//
//	��`
//
//==============================================================================================


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�r�b�g�}�b�v�ǉ�
 *
 * @param	ini		BGL�f�[�^
 * @param	win		�r�b�g�}�b�v�E�B���h�E
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningAddBmpWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );

//--------------------------------------------------------------
/**
 * @brief	�r�b�g�}�b�v�E�B���h�E�j��	
 *
 * @param	win		�r�b�g�}�b�v�E�B���h�E
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningExitBmpWin( GF_BGL_BMPWIN* win );

//--------------------------------------------------------------
/**
 * @brief	�r�b�g�}�b�v�E�B���h�E�I�t
 *
 * @param	win		�r�b�g�}�b�v�E�B���h�E
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningOffBmpWin( GF_BGL_BMPWIN* win );

//--------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�\��
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 * @param	win		�r�b�g�}�b�v�E�B���h�E
 * @param	msg_id	���b�Z�[�WID
 * @param	x		X���W(�h�b�g�P��)
 * @param	y		Y���W(�h�b�g�P��)
 * @param	wait	�����\���E�F�C�g
 * @param	f_col	�����F�i���o�[(�h��Ԃ��J���[�R�[�h)
 * @param	s_col	�e�F�i���o�[
 * @param	b_col	�w�i�F�i���o�[
 * @param	font	�t�H���g���
 *
 * @return	"�����`�惋�[�`���̃C���f�b�N�X"
 */
//--------------------------------------------------------------
extern u8 OpeningWriteMsg(OPENING_WORK* wk, GF_BGL_BMPWIN* win, int msg_id, u32 x, u32 y, u32 wait, u8 f_col, u8 s_col, u8 b_col, u8 font);

//--------------------------------------------------------------
/**
 * @brief	���j���[�E�B���h�E�\��
 *
 * @param	ini		BGL�f�[�^
 * @param	win		�r�b�g�}�b�v�E�B���h�E
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningWriteMenuWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[	�w�b�_�[�����ݒ�
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 * @param	y_max	���ڍő吔
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void OpeningInitMenu( OPENING_WORK* wk, GF_BGL_BMPWIN* win, u8 y_max );

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[	�f�[�^�Z�b�g
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 * @param	no		�Z�b�g����ꏊ(�߂�l)
 * @param	param	�߂�l
 * @param	msg_id	���b�Z�[�WID
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void OpeningSetMenuData( OPENING_WORK* wk, u8 no, u8 param, int msg_id  );

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�E�B���h�E�\��
 *
 * @param	win		BMP�f�[�^
 * @param	wintype	�E�B���h�E�^�C�v
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void OpeningTalkWinPut( GF_BGL_BMPWIN * win, WINTYPE wintype );


#endif //_OPENING_BMP_H_


