#ifndef __FNTSYS_H__
#define __FNTSYS_H__

#include "gflib\bg_system.h"
#include "gflib\msg_print.h"





//------------------------------------------------------------------
/**
 * �^�O�R�[�h�J�n�ӏ��̃|�C���^���󂯎��A�^�O��ރR�[�h��Ԃ�
 *
 * @param   str		������|�C���^
 *
 * @retval  u32		�^�O��ރR�[�h
 */
//------------------------------------------------------------------
extern u32  STRCODE_GetTagType( const STRCODE* str );

//------------------------------------------------------------------
/**
 * �^�O�R�[�h�J�n�ӏ��̃|�C���^���󂯎��A�^�O���e���P��Z�b�g�^�O�����ׂ�
 *
 * @param   str			������|�C���^
 *
 * @retval  BOOL		TRUE�Ȃ�P��Z�b�g�^�O
 */
//------------------------------------------------------------------
extern BOOL STRCODE_CheckWordSetTagType( const STRCODE* str );

//------------------------------------------------------------------
/**
 * �^�O�R�[�h�ӏ��̃|�C���^���󂯎��A�p�����[�^�l��ǂݎ���ĕԂ�
 *
 * @param   str			������|�C���^
 * @param   param_no	�p�����[�^�i���o�[�i0 org�j
 *
 * @retval  u32		�p�����[�^�l
 */
//------------------------------------------------------------------
extern u32  STRCODE_GetTagParam( const STRCODE* str, u32 param_no );

//------------------------------------------------------------------
/**
 * �^�O�R�[�h�J�n�ӏ��̃|�C���^���󂯎��A�p�����[�^�����X�L�b�v���ĕԂ�
 *
 * @param   str			������|�C���^
 *
 * @retval  STRCODE*	�p�����[�^���X�L�b�v��̃|�C���^
 */
//------------------------------------------------------------------
extern STRCODE*  STRCODE_SkipTag( const STRCODE* str );

#if 0
//---------------------------------------------------------------------------------------------
/*
 *	�����R�[�h�ϊ��@�|�P�����`�f�a->�|�P�����c�r
 *	���ʏ핶���A�I���A���s�A�g���K�[�҂��A�o�b�t�@���b�Z�[�W�ɑΉ�
 *
 * @param	c_id		���ԍ�(0:���{,1:....)
 * @param	agb_str		���͂���`�f�a������̃|�C���^
 * @param	ds_str		�o�͂���c�r������̃|�C���^
 *
 * @retval	ret		0:���Ȃ�,1:���ߕs�\�ȃR�[�h���������i�ϊ����s�j
 */
//---------------------------------------------------------------------------------------------
extern u8	GBAcode2DSuni(u8 c_id, u8 *agb_str, STRCODE *ds_str);

//---------------------------------------------------------------------------------------------
/*
 *	�����R�[�h�ϊ��@�|�P�����c�r->�|�P�����`�f�a
 *	���ʏ핶���A�I���A���s�A�g���K�[�҂��A�o�b�t�@���b�Z�[�W�ɑΉ�
 *
 * @param	c_id		���ԍ�(0:���{,1:....)
 * @param	ds_str		���͂���c�r������̃|�C���^
 * @param	agb_str		�o�͂���`�f�a������̃|�C���^
 *
 * @retval	ret		0:���Ȃ�,1:���ߕs�\�ȃR�[�h���������i�ϊ����s�j
 */
//---------------------------------------------------------------------------------------------
extern u8	DSuni2GBAcode(u8 c_id, STRCODE *ds_str, u8 *agb_str);
#endif
#ifdef PM_DEBUG
//---------------------------------------------------------------------------------------------
/*
 *	�����R�[�h�ϊ��@ASCII->�|�P�����c�o
 *	���ʏ핶���A�I���A���s�Ή�
 *	�@�g���K�[�҂��A�o�b�t�@���b�Z�[�W�A���̑��|�P��������R�[�h��Ή�
 *
 *	�f�o�b�O��p�ł��I
 * 
 * @param	c_id		���ԍ�(0:���{,1:....)�@��Ή�
 * @param	agb_str		���͂���ASCII������̃|�C���^
 * @param	ds_str		�o�͂���DS������̃|�C���^
 *
 * @retval	ret		0:���Ȃ�,1:���ߕs�\�ȃR�[�h���������i�ϊ����s�j
 */
//---------------------------------------------------------------------------------------------
extern u8	ASCIIcode2DSuni(u8 c_id, u8 *ascii_str, u16 *ds_str);
#endif	//PM_DEBUG

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
/* ������\������R�[�h�̒�` */
#include "strcode.h"


#define CR_				0xe000		/* ���s�R�[�h */




//=============================================================================================
//	���R�[�h
//=============================================================================================
//=============================================================================================
//=============================================================================================

/* ������\������R�[�h�̒�` */
#define S_MSG_			0xf0f7		/* �w��o�b�t�@�̃��b�Z�[�W�W�J(�C��)*/
#define	EXICON_			0xf0f8		/* �g���A�C�R��(�L�[�A�C�R��) */

#define I_MSG_			0xf0fd		/* �w��o�b�t�@�̃��b�Z�[�W�W�J(ID)	*/
#define CTRL_			0xf0fc		/* �t�H���g����R�}���h */

#define	NORMAL_WAIT_	0x25bc		/* "��"		�g���K�[�҂���MSG�G���A�N���A	*/
#define	SCROLL_WAIT_	0x25bd		/* "��"		�g���K�[�҂�����s�X�N���[�� */
#define	SIMPLE_WAIT_	0x25a0		/* "��"		�g���K�[�҂��̂� */

#define	C_FCOL_		0xf001		/* �t�H���g����T�u�R�}���h:�����F�ύX */
#define	C_BCOL_		0xf002		/* �t�H���g����T�u�R�}���h:�w�i�F�ύX */
#define C_SCOL_		0xf003		/* �t�H���g����T�u�R�}���h:�e�F�ύX */
#define C_ACOL_		0xf004		/* �t�H���g����T�u�R�}���h:�S�F�w��ύX(�p�����[�^��FBS�̏�) */
#define C_PAL_		0xf005		/* �t�H���g����T�u�R�}���h:�p���b�g�ύX */
#define C_FCHG_		0xf006		/* �t�H���g����T�u�R�}���h:�t�H���g�ύX */
#define C_FNML_		0xf007		/* �t�H���g����T�u�R�}���h:�t�H���g���A */
#define	C_WAIT_		0xf008		/* �t�H���g����T�u�R�}���h:�E�F�C�g�Z�b�g */
#define C_TRGWAIT_	0xf009		/* �t�H���g����T�u�R�}���h:�L�[�E�F�C�g */
#define C_SEWAIT_	0xf00a		/* �t�H���g����T�u�R�}���h:SE�̖�I���܂ő҂� */
#define C_MUSPLAY_	0xf00b		/* �t�H���g����T�u�R�}���h:BGM���Ȃ炷 */
#define C_EXFONT_	0xf00c		/* �t�H���g����T�u�R�}���h:�g���t�H���g�w�� */
#define C_XCHG_		0xf00d		/* �t�H���g����T�u�R�}���h:�\��X�ʒu�ړ� */
#define C_YCHG_		0xf00e		/* �t�H���g����T�u�R�}���h:�\��Y�ʒu�ړ� */
#define C_CLR_		0xf00f		/* �t�H���g����T�u�R�}���h:MSG�G���A�N���A */
#define C_SEPLAY_	0xf010		/* �t�H���g����T�u�R�}���h:SE���Ȃ炷 */

//�T�u�R�[�h0x11�`0x16	�͊C�O�ŃT�u�R�[�h
#define C_STRUT_	0xf011		/* �����P */
#define C_OFSX_		0xf012		/* �����P */
#define C_BLANK_	0xf013		/* �����P */
#define C_WIDTH_	0xf014		/* �����P */
#define C_LANG_JP	0xf015		/* �����Ȃ� */
#define C_LANG_DEF	0xf016		/* �����Ȃ� */

#define C_MUSPAUSE_	0xf017		/* �t�H���g����T�u�R�}���h:BGM��PAUSE */
#define C_MUSCONTINUE_	0xf018	/* �t�H���g����T�u�R�}���h:BGM��CONTINUE */

#define	C_FSIZCHG_		0xf019	/* �t�H���g�T�C�Y�ύX�i�h�b�g����j */
#define	C_FSIZCHG2_		0xf01a	/* �t�H���g�T�C�Y�ύX�i�h�b�g����i�Q�{�j�j */
#define	C_FSIZCHGEND_	0xf01b	/* �t�H���g�T�C�Y�ύX�I���i�h�b�g����j */

#define C_DCOL_			0xf01c	/* �t�H���g����T�u�R�}���h:�ꊇ�w��ύX(FS) */


//=============================================================================================
//	�萔
//=============================================================================================
// C_FSIZCHG_�Ő��䂷��h�b�g�ʒu
#define	FSIZ_1PLUS_		( 0x0080 )	// 0000_0000_1000_0000
#define	FSIZ_2PLUS_		( 0x0440 )	// 0000_0010_0010_0000
#define	FSIZ_3PLUS_		( 0x0490 )	// 0000_0100_1001_0000
#define	FSIZ_4PLUS_		( 0x2490 )	// 0010_0100_1001_0000
#define	FSIZ_5PLUS_		( 0x1294 )	// 0001_0010_1001_0100
#define	FSIZ_6PLUS_		( 0x1554 )	// 0001_0101_0101_0100
#define	FSIZ_7PLUS_		( 0x3554 )	// 0011_0101_0101_0100
#define	FSIZ_8PLUS_		( 0x355c )	// 0011_0101_0101_1100
#define	FSIZ_9PLUS_		( 0x357c )	// 0011_0101_0111_1100
#define	FSIZ_10PLUS_	( 0x377c )	// 0011_0111_0111_1100
#define	FSIZ_11PLUS_	( 0x37fc )	// 0011_0111_1111_1100
#define	FSIZ_12PLUS_	( 0x3ffc )	// 0011_1111_1111_1100
#define	FSIZ_13PLUS_	( 0x7ffc )	// 0111_1111_1111_1100
#define	FSIZ_14PLUS_	( 0x7ffe )	// 0111_1111_1111_1110
#define	FSIZ_15PLUS_	( 0xfffe )	// 1111_1111_1111_1110
#define	FSIZ_16PLUS_	( 0xffff )	// 1111_1111_1111_1111

// �ʏ�̃t�H���g�J���[
#define	FBMP_COL_NULL		(0)
#define	FBMP_COL_BLACK		(1)
#define	FBMP_COL_BLK_SDW	(2)
#define	FBMP_COL_RED		(3)
#define	FBMP_COL_RED_SDW	(4)
#define	FBMP_COL_GREEN		(5)
#define	FBMP_COL_GRN_SDW	(6)
#define	FBMP_COL_BLUE		(7)
#define	FBMP_COL_BLU_SDW	(8)
#define	FBMP_COL_PINK		(9)
#define	FBMP_COL_PNK_SDW	(10)

#define	FBMP_COL_WHITE		(15)

//#define	FBMP_COL_WHT_SDW	(2)
//#define	FBMP_COL_YELLOW		(11)
//#define	FBMP_COL_YLW_SDW	(12)

// C_DCOL_�Ő��䂷��F ( (�����F<<4) + (�e�F) )
#define	DCOL_BLACK_		( ( FBMP_COL_BLACK << 4 ) + FBMP_COL_BLK_SDW )	// ��
//#define	DCOL_WHITE_		( ( FBMP_COL_WHITE << 4 ) + FBMP_COL_WHT_SDW )	// ��
#define	DCOL_BLUE_		( ( FBMP_COL_BLUE << 4 ) + FBMP_COL_BLU_SDW )	// ��
#define	DCOL_RED_		( ( FBMP_COL_RED << 4 ) + FBMP_COL_RED_SDW )	// ��
#define	DCOL_PINK_		( ( FBMP_COL_PINK << 4 ) + FBMP_COL_PNK_SDW )	// �s���N
//#define	DCOL_YELLOW_	( ( FBMP_COL_YELLOW << 4 ) + FBMP_COL_YLW_SDW )	// ��
#define	DCOL_GREEN_		( ( FBMP_COL_GREEN << 4 ) + FBMP_COL_GRN_SDW )	// ��



//============================================================================================
//	�C�V���c�[���@�e�X�g�R�[�h
//============================================================================================
#define	_CTRL_TAG		0xfffe			// �^�O�R�[�h

#define	NC_FONT_COL_	0xff00			// �t�H���g����R�[�h
#define	NC_FONT_SIZE_	0xff01			// �t�H���g����R�[�h
#define	NC_MOVE_		0xfe06			// ���쐧��R�[�h

#define	NC_FCOL_BLACK_	0x0000		// �����F�F��
#define	NC_FCOL_RED_	0x0001		// �����F�F��

#define	NC_FAFF_100_	0x0064		// �T�C�Y�F100��
#define	NC_FAFF_200_	0x00c8		// �T�C�Y�F200��

#define	NC_MV_CLEAR_	0xfe01			// �L�[�҂��N���A
#define	NC_MV_SCROLL_	0xfe00			// �L�[�҂��X�N���[��

#define NC_WORDSET_MASK		0xff00
#define NC_WORDSET			0x0100

#define NC_NOTE_ICON			(0x0200)	// ���ڃA�C�R��
#define NC_FORCE_WAIT			(0x0201)	// ���̕�����\������O�̋����E�F�C�g�t���[��
#define NC_CALLBACK_ARG			(0x0202)
#define NC_WRITEPOS_CHANGE_X	(0x0203)
#define NC_WRITEPOS_CHANGE_Y	(0x0204)

#define NC_ACTIVE_ICON_	0xff02

/*
001a ff08 0000 0001 �F�ύX�F��
001a ff08 0000 0000 �F�ύX�F��
001a ff08 0001 00c8 �T�C�Y�F200��
001a fe06 fe01 		�L�[�҂��N���A
001a fe06 fe00		�L�[�҂��X�N���[��
*/


#endif
