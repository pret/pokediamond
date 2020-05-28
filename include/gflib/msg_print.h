//=============================================================================================
/**
 * @file	msg_print.h
 * @brief	�r�b�g�}�b�v������\���p�V�X�e��
 * @author	tomo
 * @date	2004.10.28
 */
//=============================================================================================
#ifndef	__MSG_PRINT_H__
#define	__MSG_PRINT_H__

#include <nitro.h>
#include <nnsys.h>
#include "tcb.h"
#include "gflib\bg_system.h"
#include "gflib\strbuf.h"


#undef	GLOBAL
#ifdef	__MSG_PRINT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//---------------------------------------------------------------------------------------------
/**
	�萔��`
 */
//---------------------------------------------------------------------------------------------
typedef u16		STRCODE;

//---------------------------------------------------------------------------------------------
/// �F�ԍ��w�� PRINT �̂��߂̒萔�E�}�N����`

typedef u32		GF_PRINTCOLOR;

#define  GF_PRINTCOLOR_MASK			(0xff)
#define  GF_PRINTCOLOR_LETTER_SHIFT	(16)
#define  GF_PRINTCOLOR_SHADOW_SHIFT	(8)
#define  GF_PRINTCOLOR_GROUND_SHIFT	(0)

// GF_MSG_PrintColor �̈��� GF_PRINT_COLOR ���쐬���邽�߂̃}�N���i �����F�A�e�F�A�w�i�F�̏��ɔԍ���n�� �j
#define  GF_PRINTCOLOR_MAKE(letter, shadow, ground)	(GF_PRINTCOLOR)(	(((letter)&GF_PRINTCOLOR_MASK) << GF_PRINTCOLOR_LETTER_SHIFT)|\
																		(((shadow)&GF_PRINTCOLOR_MASK) << GF_PRINTCOLOR_SHADOW_SHIFT)|\
																		(((ground)&GF_PRINTCOLOR_MASK) << GF_PRINTCOLOR_GROUND_SHIFT)	)

// GF_PRINTCOLOR_MAKE �ō�����l����e�F�ԍ������o���}�N��
#define GF_PRINTCOLOR_GET_LETTER(c)		(((c)>>GF_PRINTCOLOR_LETTER_SHIFT)&GF_PRINTCOLOR_MASK)
#define GF_PRINTCOLOR_GET_SHADOW(c)		(((c)>>GF_PRINTCOLOR_SHADOW_SHIFT)&GF_PRINTCOLOR_MASK)
#define GF_PRINTCOLOR_GET_GROUND(c)		(((c)>>GF_PRINTCOLOR_GROUND_SHIFT)&GF_PRINTCOLOR_MASK)

//---------------------------------------------------------------------------------------------
///���b�Z�[�W�\��wait��`

#define	MSG_NO_PUT	(0xff)	//�f�B�X�v���C�]���Ȃ�
#define	MSG_ALLPUT	(0)		//�f�B�X�v���C�ꊇ�]��

//---------------------------------------------------------------------------------------------
///�t�H���g�f�[�^�쐬�v���O�����p�Ԃ�l��`

typedef enum {
	PRINT_RESULT_WRITE = 0,
	PRINT_RESULT_END,
	PRINT_RESULT_LOOP,
	PRINT_RESULT_COMMAND,
}PRINT_RESULT;


//---------------------------------------------------------------------------------------------
/// FntDataColorGe() �p���[�h��`
enum COLOR_GET_MODE {
	COLOR_F,
	COLOR_S,
	COLOR_B
};

///�\��������ݒ�\����
typedef struct mph_tag{
	union {
		const u16* msg;		//�\�����b�Z�[�W
		const STRBUF* strbuf;
	};
	GF_BGL_BMPWIN * bmpwin;	//BMP�E�B���h�E�f�[�^

	u8		msg_index;		//���b�Z�[�W�C���f�b�N�X

	u8		fnt_index;		//�g�p�t�H���gINDEX
	u8		start_x;		//�E�C���h�E���\���J�nX�I�t�Z�b�g
	u8		start_y;		//�E�C���h�E���\���J�nY�I�t�Z�b�g

	u8		write_x;	//�E�C���h�E���`��X�I�t�Z�b�g
	u8		write_y;	//�E�C���h�E���`��Y�I�t�Z�b�g
	u8		space_x;	//�����Ԋu
	u8		space_y;	//�����Ԋu

	u8		style;		//�t�H���g�X�^�C��
	u8		f_col;		//�����F�i���o�[
	u8		b_col;		//�w�i�F�i���o�[
	u8		s_col;		//�e�F�@�i���o�[

	u16		dot_tbl;	//�g��p�h�b�g�e�[�u��
	u8		dot_wy;		//�g�厞��Y���W�̕`��␳�l
	u8		dummy;

/*	4bit color mode
u8		style:4;	//�t�H���g�X�^�C��
u8		f_col:4;	//�����F�i���o�[
u8		b_col:4;	//�w�i�F�i���o�[
u8		s_col:4;	//�e�F�@�i���o�[
u8		work[2];	//�������킹�Œǉ�
*/
}MSG_PRINT_HEADER;

//---------------------------------------------------------------------------------------------
/**
 *	�\���V�X�e���g�p���[�N�\����
 */
//---------------------------------------------------------------------------------------------
#define MDH_WORKSIZE	(7)

// FALSE��Ԃ���Print�������p���BTRUE��Ԃ���Print�𒆒f����Callback���Ăё�����
typedef  BOOL (*pStrPrintCallBack)(MSG_PRINT_HEADER*, u16);

typedef struct {
	MSG_PRINT_HEADER		mph;
	pStrPrintCallBack		call_back;
	u8		userwork[MDH_WORKSIZE];//���[�U�[���[�N
	u8		sw;			//����X�C�b�`
	u8		seq;		//�V�[�P���X
	u8		wait:7;		//�����`��E�F�C�g(0:�ꊇ�`)
	u8		wait_flg:1;	//�E�F�C�g�t���O 0=�ꊇ�\��, 1=�P�������\��
	u8		waitwork;	//���[�N(�E�F�C�g)
	u8		scrwork;	//���[�N(�X�N���[��)
	u8		msg_index;	//���b�Z�[�W�C���f�b�N�X
	u8		callback_cont_flag;	// �A���R�[���o�b�N�Ăяo���t���O
	u16		callback_arg;	// �R�[���o�b�N�֐��Ɉ����n���l
//	void * trg_wk;
	void * disp_icon;	//�����ʕύX�A�C�R��
}MSG_DATA_HEADER;

//---------------------------------------------------------------------------------------------
/**
 *	�\�������f�[�^�\���́i�N���C�A���g�ݒ�j
 */
//---------------------------------------------------------------------------------------------
typedef struct {
u8		size_x;		//�t�H���gX�T�C�Y�w��
u8		size_y;		//�t�H���gY�T�C�Y�w��
u8		space_x;	//�����Ԋu(�����ݒ�)
u8		space_y;	//�����Ԋu(�����ݒ�)
u8		style;	//�t�H���g�X�^�C��(�����ݒ�)
u8		f_col;	//�����F�i���o�[
u8		b_col;	//�w�i�F�i���o�[
u8		s_col;	//�e�F�@�i���o�[
//u8		work[2];	//�������킹�Œǉ�
}MSG_FONT_HEADER;


//---------------------------------------------------------------------------------------------
/**
 *	�����f�[�^�i�[�\����
 */
//---------------------------------------------------------------------------------------------
typedef struct {
u8		data[0x20*4];
u8		size_x;	//�\��X�T�C�Y
u8		size_y;	//�\��Y�T�C�Y
}MSG_FONT_DATA;



//---------------------------------------------------------------------------------------------
/**
 *	�����\���V�X�e���������֐�(���[�U�[�ݒ�)
 *
 * @param	�t�H���g�֐��Q�w�b�_
 *
 */
//---------------------------------------------------------------------------------------------
GLOBAL void	MSG_PrintSysInit( const MSG_FONT_HEADER* header );





extern u8 GF_STR_PrintSimple( GF_BGL_BMPWIN* win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait, pStrPrintCallBack callback );

extern u8 GF_STR_PrintColor(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, pStrPrintCallBack call_back );

extern u8 GF_STR_PrintExpand(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, u32 xspc, u32 yspc, pStrPrintCallBack  call_back );

extern u8 GF_STR_Print( const MSG_PRINT_HEADER* mph_p, u32 wait, pStrPrintCallBack call_back );



//=============================================================================================
//�����\���V�X�e���֐�
//=============================================================================================
//---------------------------------------------------------------------------------------------
/**
 *	�����\���������֐�
 *
 * @param	�Ȃ�
 *
 * @retval	�Ȃ�
 */
//---------------------------------------------------------------------------------------------
GLOBAL void	MSG_PrintInit(void);
//---------------------------------------------------------------------------------------------
/*
 *	�����f�[�^�ݒ�
 *
 * @param	radrs		�ǂݍ��݃f�[�^�J�n�A�h���X
 * @param	wadrs		�������݃f�[�^�o�b�t�@�A�h���X
 *
 * @retval	none
 */
//---------------------------------------------------------------------------------------------
GLOBAL void FntDataSet8x8_2bit(u32 radrs,u32 wadrs);

//---------------------------------------------------------------------------------------------
/*
 *	FntDataSet8x8_2bit ���ĂԑO�ɁA�F�ԍ����Z�b�g���Ă����i�������̂��߁j
 *
 * @param	col_f	�����F�ԍ�
 * @param	col_b	�w�i�F�ԍ�
 * @param	col_s	�e�F�ԍ�
 */
//---------------------------------------------------------------------------------------------
GLOBAL void FntDataColorSet(u8 col_f, u8 col_b, u8 col_s);

GLOBAL void FntDataColorBackUp(u8* col_f, u8* col_b, u8* col_s);
GLOBAL void FntDataColorRecover(u8* col_f, u8* col_b, u8* col_s);
//---------------------------------------------------------------------------------------------
/*
 *	FntDataColorSet �Őݒ肵���F�ԍ����擾
 *
 * @param	mode	���[�h�ienum COLOR_GET_MODE : msg_print.h�j
 *
 * @retval	�F�ԍ�
 */
//---------------------------------------------------------------------------------------------
GLOBAL u8 FntDataColorGet(u8 mode);







//---------------------------------------------------------------------------------------------
/*
 * �I���`�F�b�N�֐�
 *
 * @param	msg_index	���b�Z�[�W�C���f�b�N�X
 *
 * @retval	0	�I��
 * @retval	1	������
 */
//---------------------------------------------------------------------------------------------
GLOBAL u8 GF_MSG_PrintEndCheck( u8 msg_index );

//---------------------------------------------------------------------------------------------
/*
 * �P�������Ƃ̕\���^�X�N�������I�ɒ�~����
 *
 * @param	msg_index	���b�Z�[�W�C���f�b�N�X
 */
//---------------------------------------------------------------------------------------------
GLOBAL void GF_STR_PrintForceStop( u8 msg_index );



GLOBAL void GF_MSG_PrintDispIcon( MSG_DATA_HEADER * mdh, u16 px, u16 py, u16 pat );




#undef	GLOBAL
#endif	/*	__MSG_PRINT_H__ */

