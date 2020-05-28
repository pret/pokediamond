/**
 *	@file	fld_bmp.h
 *	@brief	�t�B�[���h���b�Z�[�W&���j���[�\���R���g���[��
 *	@author	GameFreak Inc.
 *	@date	04/12/17
 */

#ifndef _H_FLD_BMP_H_
#define _H_FLD_BMP_H_

///	�a�f�p���b�g��` 2005/09/15
//
//	0 �` 5  : �t�B�[���h�}�b�v�a�f�p
//  6       : �V��
//  7       : �n���E�C���h�E
//  8       : �ŔE�C���h�E�i�}�b�v�A�W���Ȃǁj
//  9       : �ŔE�C���h�E�i�g�A�t�H���g�j
//  10      : ���b�Z�[�W�E�C���h�E
//  11      : ���j���[�E�C���h�E
//  12      : ���b�Z�[�W�t�H���g
//  13      : �V�X�e���t�H���g
//	14		: ���g�p�i���[�J���C�Y�p�j
//	15		: �f�o�b�O�p�i���i�łł͖��g�p�j
#define FLD_WEATHER_PAL      (  6 )			//  �V��
#define FLD_PLACENAME_PAL    (  7 )         //  �n���E�C���h�E
#define FLD_BOARD1FRAME_PAL  (  8 )         //  �ŔE�C���h�E�i�}�b�v�A�W���Ȃǁj
#define FLD_BOARD2FRAME_PAL  (  9 )         //  �ŔE�C���h�E�i�g�A�t�H���g�j
#define FLD_MESFRAME_PAL     ( 10 )         //  ���b�Z�[�W�E�C���h�E
#define FLD_MENUFRAME_PAL    ( 11 )         //  ���j���[�E�C���h�E
#define FLD_MESFONT_PAL      ( 12 )         //  ���b�Z�[�W�t�H���g
#define FLD_SYSFONT_PAL	     ( 13 )         //  �V�X�e���t�H���g
#define FLD_LOCALIZE_PAL     ( 14 )         //	���g�p�i���[�J���C�Y�p�j
#define FLD_DEBUG_PAL        ( 15 )         //	�f�o�b�O�p�i���i�łł͖��g�p�j

/*********************************************************************************************
	���C����ʂ�CGX����U��		2006/01/12

		�E�B���h�E�g	�F	409 - 511
			��b�A���j���[�A�n���A�Ŕ�

		BMP�E�B���h�E�P	�F	297 - 408
			��b�i�ő�j�A�ŔA�c��{�[����

		BMP�E�B���h�E�Q	�F	55 - 296
			���j���[�i�ő�j�A�͂�/�������A�n��

*********************************************************************************************/

/*********************************************************************************************
	�E�B���h�E�g
*********************************************************************************************/
// ��b�E�B���h�E�L����
#define	TALK_WIN_CGX_SIZE	( 18+12 )
#define	TALK_WIN_CGX_NUM	( 1024 - TALK_WIN_CGX_SIZE )
#define	TALK_WIN_PAL		( 10 )

// ���j���[�E�B���h�E�L����
#define	MENU_WIN_CGX_SIZE	( 9 )
#define	MENU_WIN_CGX_NUM	( TALK_WIN_CGX_NUM - MENU_WIN_CGX_SIZE )
#define	MENU_WIN_PAL		( 11 )

// �n���E�B���h�E�L����
#define	PLACE_WIN_CGX_SIZE	( 10 )
#define	PLACE_WIN_CGX_NUM	( MENU_WIN_CGX_NUM - PLACE_WIN_CGX_SIZE )
#define	PLACE_WIN_PAL		( 7 )

// �ŔE�B���h�E�L����
#define	BOARD_WIN_CGX_SIZE	( 18+12 + 24 )
#define	BOARD_WIN_CGX_NUM	( PLACE_WIN_CGX_NUM - BOARD_WIN_CGX_SIZE )
#define	BOARD_WIN_PAL		( FLD_BOARD2FRAME_PAL )

/*********************************************************************************************
	BMP�E�B���h�E
*********************************************************************************************/
// ��b�E�B���h�E�i���C���j
#define	FLD_MSG_WIN_PX		( 2 )
#define	FLD_MSG_WIN_PY		( 19 )
#define	FLD_MSG_WIN_SX		( 27 )
#define	FLD_MSG_WIN_SY		( 4 )
#define	FLD_MSG_WIN_PAL		( FLD_MESFONT_PAL )
#define	FLD_MSG_WIN_CGX		( BOARD_WIN_CGX_NUM - ( FLD_MSG_WIN_SX * FLD_MSG_WIN_SY ) )

// �ŔE�B���h�E�i���C���j�i��b�Ɠ����ʒu�i��b��菬�����j�j
#define	FLD_BOARD_WIN_PX	( 9 )
#define	FLD_BOARD_WIN_PY	( 19 )
#define	FLD_BOARD_WIN_SX	( 20 )
#define	FLD_BOARD_WIN_SY	( 4 )
#define	FLD_BOARD_WIN_PAL	( FLD_BOARD2FRAME_PAL )
#define	FLD_BOARD_WIN_CGX	( FLD_MSG_WIN_CGX )

// �c��{�[�����i��b�Ɠ����ʒu�i��b��菬�����j�j
#define	FLD_BALL_WIN_PX		( 1 )
#define	FLD_BALL_WIN_PY		( 1 )
#define	FLD_BALL_WIN_SX		( 12 )
#define	FLD_BALL_WIN_SY		( 4 )
#define	FLD_BALL_WIN_PAL	( FLD_SYSFONT_PAL )
#define	FLD_BALL_WIN_CGX	( FLD_MSG_WIN_CGX )

// ���j���[�E�B���h�E�i���C���j
#define	FLD_MENU_WIN_PX		( 20 )
#define	FLD_MENU_WIN_PY		( 1 )
#define	FLD_MENU_WIN_SX		( 11 )
#define	FLD_MENU_WIN_SY		( 22 )
#define	FLD_MENU_WIN_PAL	( FLD_SYSFONT_PAL )
#define	FLD_MENU_WIN_CGX	( FLD_MSG_WIN_CGX - ( FLD_MENU_WIN_SX * FLD_MENU_WIN_SY ) )

// �͂�/�������E�B���h�E�i���C���j�i���j���[�Ɠ����ʒu�i���j���[��菬�����j�j
#define	FLD_YESNO_WIN_PX	( 25 )
#define	FLD_YESNO_WIN_PY	( 13 )
#define	FLD_YESNO_WIN_SX	( 6 )
#define	FLD_YESNO_WIN_SY	( 4 )
#define	FLD_YESNO_WIN_PAL	( FLD_SYSFONT_PAL )
#define	FLD_YESNO_WIN_CGX	( FLD_MSG_WIN_CGX - ( FLD_YESNO_WIN_SX * FLD_YESNO_WIN_SY ) )

// �n���E�B���h�E�i���j���[�Ɠ����ʒu�i���j���[��菬�����j�j
#define FLD_PLACE_WIN_PX	( 0 )
#define FLD_PLACE_WIN_PY	( 0 )
#define	FLD_PLACE_WIN_SX	( 32 )
#define	FLD_PLACE_WIN_SY	( 3 )
#define	FLD_PLACE_WIN_CGX	( FLD_MSG_WIN_CGX - ( FLD_PLACE_WIN_SX * FLD_PLACE_WIN_SY ) )



// ���b�Z�[�W�E�B���h�E�i�T�u�j
#define	FLD_MSG_WIN_S_PX	( 2  )
#define	FLD_MSG_WIN_S_PY	( 19 )
#define	FLD_MSG_WIN_S_PAL	( FLD_MESFONT_PAL )
//#define	FLD_MSG_WIN_S_CGX	( MENU_WIN_CGX_NUM - ( FLD_MSG_WIN_SX * FLD_MSG_WIN_SY ) )
#define	FLD_MSG_WIN_S_CGX	( 512 - ( FLD_MSG_WIN_SX * FLD_MSG_WIN_SY ) )

// �ŔE�B���h�E�i�T�u�j
#define	FLD_BOARD_WIN_S_PX	( 9 )
#define	FLD_BOARD_WIN_S_PY	( 19 )
#define	FLD_BOARD_WIN_S_SX	( 21 )
#define	FLD_BOARD_WIN_S_SY	( 4 )
#define	FLD_BOARD_WIN_S_PAL	( FLD_BOARD2FRAME_PAL )
#define	FLD_BOARD_WIN_S_CGX	( FLD_MSG_WIN_S_CGX )

// ���j���[�E�B���h�E�i�T�u�j
#define	FLD_MENU_WIN_S_PX	( 25 )
#define	FLD_MENU_WIN_S_PY	( 1 )
#define	FLD_MENU_WIN_S_SX	( 6 )
#define	FLD_MENU_WIN_S_SY	( 16 )
#define	FLD_MENU_WIN_S_PAL	( FLD_SYSFONT_PAL )
#define	FLD_MENU_WIN_S_CGX	( MENU_WIN_CGX_NUM - ( FLD_MENU_WIN_SX * FLD_MENU_WIN_SY ) )



///	�r�b�g�}�b�v�]���֐��p��`
//------------------------------------------------------------------
#define	FBMP_TRANS_OFF	(0)
#define	FBMP_TRANS_ON	(1)
///	�����\���]���֐��p��`
//------------------------------------------------------------------
#define	FBMPMSG_WAITON_SKIPOFF	(0)
#define	FBMPMSG_WAITON_SKIPON	(1)
#define	FBMPMSG_WAITOFF			(2)

//-------------------------------------------------------------------------
///	�����\���F��`(default)	-> gflib/fntsys.h�ֈړ�
//------------------------------------------------------------------

#define WINCLR_COL(col)	(((col)<<4)|(col))

//-------------------------------------------------------------------------
///	�����\���X�s�[�h��`(default)
//------------------------------------------------------------------
#define	FBMP_MSG_SPEED_SLOW		(8)
#define	FBMP_MSG_SPEED_NORMAL	(4)
#define	FBMP_MSG_SPEED_FAST		(1)


#endif	//_H_FLD_BMP_H_
