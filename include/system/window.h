//============================================================================================
/**
 * @file	window.h
 * @brief	�E�B���h�E�\��
 * @author	Hiroyuki Nakamura
 * @date	2005.10.13
 */
//============================================================================================
#ifndef WINDOW_H
#define WINDOW_H
#undef GLOBAL
#ifdef WINDOW_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


// �Ŕ�
#define BOARD_TYPE_TOWN	(0)	// �^�E���}�b�v
#define	BOARD_TYPE_ROAD	(1)	// �W��
#define	BOARD_TYPE_POST	(2)	// �\�D
#define	BOARD_TYPE_INFO	(3)	// �f����

// �|�P�����E�B���h�E
#define	POKEWIN_CMD_NONE	( 0 )	// �R�}���h�Ȃ�
#define	POKEWIN_CMD_END		( 1 )	// �I���R�}���h
#define	POKEWIN_CMD_ANM		( 2 )	// �A�j���R�}���h
#define	POKEWIN_CMD_MOVE	( 3 )	// �A�j����


//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_

#include "poketool/poke_tool.h"

//============================================================================================
//	�萔��`
//============================================================================================
#define	MENU_WIN_CGX_SIZ	( 9 )		// ���j���[�E�B���h�E�̃L������
#define	TALK_WIN_CGX_SIZ	( 18+12 )		// ��b�E�B���h�E�̃L������
#define	BOARD_WIN_CGX_SIZ	( 18+12 )		// �ŔE�B���h�E�̃L������
#define	BOARD_MAP_CGX_SIZ	( 24 )		// �Ŕ̃}�b�v�̃L������
// ���ŔA���Ŕ̑S�L������
#define	BOARD_DATA_CGX_SIZ	( BOARD_WIN_CGX_SIZ + BOARD_MAP_CGX_SIZ )

enum {
	WINDOW_TRANS_ON = 0,
	WINDOW_TRANS_OFF
};

// ���j���[�E�B���h�E�̃^�C�v
enum {
	MENU_TYPE_SYSTEM = 0,	// �I���E�B���h�E�i�V�X�e���E�B���h�E�j
	MENU_TYPE_FIELD,		// �t�B�[���h���j���[
	MENU_TYPE_UG			// �n�����j���[
};




//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E�̃L�������Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	cgx			�L�����]���ʒu
 * @param	win_num		�E�B���h�E�ԍ�
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void MenuWinCgxSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 win_num, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E�p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 MenuWinPalArcGet(void);

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	cgx			�L�����]���ʒu
 * @param	pal			�p���b�g�ԍ�
 * @param	win_num		�E�B���h�E�ԍ�
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void MenuWinGraphicSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 win_num, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E��`��
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 * @param	win_cgx		�E�B���h�E�L�����ʒu
 * @param	pal			�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpMenuWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal );

//--------------------------------------------------------------------------------------------
/**
 *	���j���[�E�B���h�E���N���A
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpMenuWinClear( GF_BGL_BMPWIN * win, u8 trans_sw );

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�C���h�E�L�����̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	id		�E�B���h�EID
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 TalkWinCgxArcGet( u32 id );

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�C���h�E�p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	id		�E�B���h�EID
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 TalkWinPalArcGet( u32 id );

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�C���h�E�Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frm			BG�t���[���i���o�[(bg_sys)
 * @param	cgx			�L�����Z�b�g�ʒu
 * @param	pal			�g�p�p���b�g
 * @param	win_num		�E�B���h�E�ԍ�
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void TalkWinGraphicSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 win_num, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * ��b�E�B���h�E�̃J���[�O�̃h�b�g���w��J���[�ɕύX����
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���i���o�[(bg_sys)
 * @param	cgx			�L�����Z�b�g�ʒu
 * @param	cal			�ύX�J���[
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void TalkWinGraphicNullSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 col, u8 win_num, u32 heap );


//--------------------------------------------------------------------------------------------
/**
 * ��b�E�B���h�E�X�N���[���f�[�^���ABitmapWindow�Ɋ֘A�t����ꂽ
 * BG�t���[���̃X�N���[���o�b�t�@�ɃZ�b�g����
 *
 * @param   win			[in]BitmapWindow
 * @param   charno		cgx�f�[�^���Z�b�g����Ă���擪�L�����i���o
 * @param   palno		�X�N���[���쐬���Ɏg�p����p���b�g�i���o
 *
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpTalkWinScreenSet( GF_BGL_BMPWIN * win, u32 charno, u32 palno );


//--------------------------------------------------------------------------------------------
/**
 * ��b�E�B���h�E��`��
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 * @param	win_cgx		�E�B���h�E�L�����ʒu
 * @param	pal			�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpTalkWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal );

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�B���h�E���N���A
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpTalkWinClear( GF_BGL_BMPWIN * win, u8 trans_sw );



//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���\���^�X�N�ǉ�
 *
 * @param	win		��b�E�B���h�E��BMP
 * @param	cgxpos	��b�E�B���h�E�g�L�����iTalkWinGraphicSet�Ȃǁj�̓]���ʒu
 *
 * @return	�ҋ@�A�C�R���̃��[�N
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * TimeWaitIconAdd( GF_BGL_BMPWIN * win, u32 cgxpos );

//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���\���^�X�N�폜���N�G�X�g
 *
 * @param	work	�ҋ@�A�C�R���̃��[�N
 *
 * @return	none
 *
 *	work���폜����܂�
 */
//--------------------------------------------------------------------------------------------
GLOBAL void TimeWaitIconDel( void * work );

//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���\���^�X�N�폜���N�G�X�g
 *
 * @param	work	�ҋ@�A�C�R���̃��[�N
 *
 * @return	none
 *
 *	work���폜����܂�  SCR�͏��������܂���
 */
//--------------------------------------------------------------------------------------------
GLOBAL void TimeWaitIconTaskDel( void * work );


//--------------------------------------------------------------------------------------------
/**
 * �ŔE�C���h�E�Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frm			BG�t���[���i���o�[(bg_sys)
 * @param	cgx			�L�����Z�b�g�ʒu
 * @param	pal			�g�p�p���b�g
 * @param	type		�Ŕ^�C�v
 * @param	map			�}�b�v�ԍ��i�^�E���}�b�v�A�W���j
 * @param	heap		�q�[�vID
 *
 * @return	none
 *
 *	type = *_POST, *_INFO �̏ꍇ�́Amap = 0 �ŗǂ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BoardWinGraphicSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 type, u16 map, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * �ŔE�B���h�E��`��
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 * @param	win_cgx		�E�B���h�E�L�����ʒu
 * @param	pal			�p���b�g
 * @param	type		�Ŕ^�C�v
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpBoardWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal, u8 type );

//--------------------------------------------------------------------------------------------
/**
 *	�ŔE�B���h�E���N���A
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	type		�Ŕ^�C�v
 * @param	trans_sw	�]���X�C�b�`
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpBoardWinClear( GF_BGL_BMPWIN * win, u8 type, u8 trans_sw );

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E�\���i�ԍ��A���ʎw��j
 *
 * @param	bgl		BGL�f�[�^
 * @param	frm		�\��BG�t���[��
 * @param	px		�\��X���W
 * @param	py		�\��Y���W
 * @param	pal		�E�B���h�E�p���b�g
 * @param	cgx		�E�B���h�E�L����
 * @param	mons	�|�P�����ԍ�
 * @param	sex		�|�P�����̐���
 * @param	heap	�q�[�vID
 *
 * @return	�R�}���h�̃|�C���^
 *
 *	�\�����W�́A�g���܂߂Ȃ��l���w�肷�邱��
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 * PokeWindowPut(
				GF_BGL_INI * bgl, u8 frm, u8 px, u8 py,
				u8 pal, u16 cgx, u16 mons, u8 sex, int heap );

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E�\���iPOKEMON_PARAM�w��j
 *
 * @param	bgl		BGL�f�[�^
 * @param	frm		�\��BG�t���[��
 * @param	px		�\��X���W
 * @param	py		�\��Y���W
 * @param	pal		�E�B���h�E�p���b�g
 * @param	cgx		�E�B���h�E�L����
 * @param	pp		POKEMON_PARAM
 * @param	heap	�q�[�vID
 *
 * @return	�R�}���h�̃|�C���^
 *
 *	�\�����W�́A�g���܂߂Ȃ��l���w�肷�邱��
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 * PokeWindowPutPP(
				GF_BGL_INI * bgl, u8 frm, u8 px, u8 py,
				u8 pal, u16 cgx, POKEMON_PARAM * pp, int heap );


#endif	__ASM_NO_DEF_

#undef GLOBAL
#endif	// WINDOW_H
