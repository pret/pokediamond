//==============================================================================================
/**
 * @file	opneing_bmp.c
 * @brief	�I�[�v�j���O BMP
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#include "common.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/wordset.h"
#include "opening_bmp.h"


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================
extern u8 TalkWinNumGet(void);


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define OP_FONT_KIND		(FONT_SYSTEM)	//�t�H���g���

//�u�ڂ�����@�Ƃ́H�v
#define WIN_SEL1_PX			(1)
#define WIN_SEL1_PY			(4)
#define WIN_SEL1_SX			(15)
#define WIN_SEL1_SY			(6)
#define WIN_SEL1_CGX		(1)

//����A�Q�[������
#define WIN_GUIDE_PX		(1)
#define WIN_GUIDE_PY		(2)
#define WIN_GUIDE_SX		(32)		// �^�b�`�p�l�����������肫���Ă��Ȃ������̂�29->32�ɕύX tomoya takahashi 2005/12/22
#define WIN_GUIDE_SY		(20)
#define WIN_GUIDE_CGX		(WIN_SEL1_CGX + WIN_SEL1_SX * WIN_SEL1_SY)
//1+15*6=91

//�u���Ƃ��̂��v
#define WIN_SEL2_PX			(12)
#define WIN_SEL2_PY			(8)
#define WIN_SEL2_SX			(8)
#define WIN_SEL2_SY			(4)
#define WIN_SEL2_CGX		(WIN_GUIDE_CGX + WIN_GUIDE_SX * WIN_GUIDE_SY)
//91+28*20=656

//�u�I�[�L�h��b�v
#define WIN_OOKIDO_PX		(2)
#define WIN_OOKIDO_PY		(19)
#define WIN_OOKIDO_SX		(27)
#define WIN_OOKIDO_SY		(4)
#define WIN_OOKIDO_CGX		(WIN_SEL2_CGX + WIN_SEL2_SX * WIN_SEL2_SY)
//656+8*4=688

//�u�͂��E�������v
#define WIN_YESNO_PX		(4)
#define WIN_YESNO_PY		(6)//(13)
#define WIN_YESNO_SX		(6)
#define WIN_YESNO_SY		(4)
#define WIN_YESNO_CGX		(WIN_OOKIDO_CGX + WIN_OOKIDO_SX * WIN_OOKIDO_SY)
//688+27*4=796

//�u��������ԁv
#define WIN_IDSEL_PX		(1)
#define WIN_IDSEL_PY		(4)//(13)
#define WIN_IDSEL_SX		(10)
#define WIN_IDSEL_SY		(4)
#define WIN_IDSEL_CGX		(WIN_YESNO_CGX + WIN_YESNO_SX * WIN_YESNO_SY)
//796+6*4=820

//���j���[�E�B���h�E�L����
#define OP_MENU_CGX_NUM		(1024-MENU_WIN_CGX_SIZ)

//��b�E�B���h�E�L����
#define	OP_TALKWIN_CGX_SIZE	(TALK_WIN_CGX_SIZ	)
//#define	OP_TALKWIN_CGX_NUM	(512 - OP_TALKWIN_CGX_SIZE)
#define	OP_TALKWIN_CGX_NUM	(OP_MENU_CGX_NUM - OP_TALKWIN_CGX_SIZE)


//==============================================================================================
//
//	�f�[�^
//
//==============================================================================================
static const BMPWIN_DAT OpeningBmpData[] =
{
	
	{	// 0:�u�ڂ�����@�Ƃ́H�v
		OP_FRM_FONT, WIN_SEL1_PX, WIN_SEL1_PY,
		WIN_SEL1_SX, WIN_SEL1_SY, OP_FONT_PAL, WIN_SEL1_CGX
	},	
	{	// 1:����A�Q�[������
		OP_FRM_FONT, WIN_GUIDE_PX, WIN_GUIDE_PY,
		WIN_GUIDE_SX, WIN_GUIDE_SY, OP_FONT_PAL, WIN_GUIDE_CGX
	},
	{	// 2:�u���Ƃ��̂��v
		OP_FRM_FONT, WIN_SEL2_PX, WIN_SEL2_PY,
		WIN_SEL2_SX, WIN_SEL2_SY, OP_FONT_PAL, WIN_SEL2_CGX
	},
	{	// 3:�u�I�[�L�h��b�v
		OP_FRM_FONT, WIN_OOKIDO_PX, WIN_OOKIDO_PY,
		WIN_OOKIDO_SX, WIN_OOKIDO_SY, OP_MSGFONT_PAL, WIN_OOKIDO_CGX
	},
	{	// 4:�u�͂��E�������v
		OP_FRM_FONT, WIN_YESNO_PX, WIN_YESNO_PY,
		WIN_YESNO_SX, WIN_YESNO_SY, OP_FONT_PAL, WIN_YESNO_CGX
	},
	{	// 5:�u��������ԁv
		OP_FRM_FONT, WIN_IDSEL_PX, WIN_IDSEL_PY,
		WIN_IDSEL_SX, WIN_IDSEL_SY, OP_FONT_PAL, WIN_IDSEL_CGX
	},
};


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void OpeningAddBmpWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );
void OpeningExitBmpWin( GF_BGL_BMPWIN* win );
void OpeningOffBmpWin( GF_BGL_BMPWIN* win );
u8 OpeningWriteMsg(OPENING_WORK* wk, GF_BGL_BMPWIN* win, int msg_id, u32 x, u32 y, u32 wait, u8 f_col, u8 s_col, u8 b_col, u8 font);
void OpeningWriteMenuWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );
void OpeningInitMenu( OPENING_WORK* wk, GF_BGL_BMPWIN* win, u8 y_max );
void OpeningSetMenuData( OPENING_WORK* wk, u8 no, u8 param, int msg_id  );
void OpeningTalkWinPut( GF_BGL_BMPWIN * win, WINTYPE wintype );


//==============================================================================================
//
//	�֐�
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
void OpeningAddBmpWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win )
{
	u8 i;
	const BMPWIN_DAT* dat =OpeningBmpData;

	//�r�b�g�}�b�v�ǉ�
	for( i=0; i < OPENING_BMPWIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( bgl, &win[i], &dat[i] );
		GF_BGL_BmpWinDataFill( &win[i], FBMP_COL_NULL );		//�h��Ԃ�
	}

	//�擪�L�������N���A(�X�N���[���N���A����Ă�Ƃ���́A���̃L�����Ŗ��܂�)
	//GF_BGL_CharFill( bgl, OP_FRM_FONT, 0, 1, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�r�b�g�}�b�v�E�B���h�E�j��	
 *
 * @param	win		�r�b�g�}�b�v�E�B���h�E
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningExitBmpWin( GF_BGL_BMPWIN* win )
{
	u16	i;

	for( i=0; i < OPENING_BMPWIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &win[i] );
	}
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�r�b�g�}�b�v�E�B���h�E�I�t
 *
 * @param	win		�r�b�g�}�b�v�E�B���h�E
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningOffBmpWin( GF_BGL_BMPWIN* win )
{
	u16	i;

	for( i=0; i < OPENING_BMPWIN_MAX; i++ ){
		GF_BGL_BmpWinOff( &win[i] );
	}
	return;
}

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
u8 OpeningWriteMsg(OPENING_WORK* wk, GF_BGL_BMPWIN* win, int msg_id, u32 x, u32 y, u32 wait, u8 f_col, u8 s_col, u8 b_col, u8 font)
{
#if 0
	GF_BGL_BmpWinDataFill( win, b_col );			//�h��Ԃ�
	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf );
	//return GF_STR_PrintSimple( win, OP_FONT_KIND, wk->msg_buf, x, y, wait, NULL );
	return GF_STR_PrintColor( win, OP_FONT_KIND, wk->msg_buf, x, y, wait, 
								GF_PRINTCOLOR_MAKE(f_col,s_col,b_col), NULL );
#else
	GF_BGL_BmpWinDataFill( win, b_col );			//�h��Ԃ�
	MSGMAN_GetString( wk->msgman, msg_id, wk->tmp_buf );

	//�o�^���ꂽ�P����g���ĕ�����W�J����
	WORDSET_ExpandStr( wk->wordset, wk->msg_buf, wk->tmp_buf );

	return GF_STR_PrintColor( win, font, wk->msg_buf, x, y, wait, 
								GF_PRINTCOLOR_MAKE(f_col,s_col,b_col), NULL );
#endif
}

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
void OpeningWriteMenuWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win )
{
	//���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet( bgl, OP_FRM_FONT, OP_MENU_CGX_NUM, OP_MENU_PAL, 0, HEAPID_OPENING );

	//���j���[�E�B���h�E��`��
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, OP_MENU_CGX_NUM, OP_MENU_PAL );

	return;
}

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
void OpeningInitMenu( OPENING_WORK* wk, GF_BGL_BMPWIN* win, u8 y_max )
{
	int i;

	for( i=0; i < OPENING_MENU_MAX ;i++ ){
		wk->Data[i].str	  = NULL;
		wk->Data[i].param = 0;
	}

	wk->MenuH.menu		= wk->Data;
	wk->MenuH.win		= win;
	wk->MenuH.font		= OP_FONT_KIND;
	wk->MenuH.x_max		= 1;
	wk->MenuH.y_max		= y_max;
	wk->MenuH.line_spc	= 0;
	wk->MenuH.c_disp_f	= 0;
	wk->MenuH.loop_f	= 0;			//��
	return;
}

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
void OpeningSetMenuData( OPENING_WORK* wk, u8 no, u8 param, int msg_id  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( no < OPENING_MENU_MAX, "���j���[���ڐ��I�[�o�[�I" );

	MSGMAN_GetString( wk->msgman, msg_id, wk->menu_buf[no] );

	wk->Data[ no ].str = (const void *)wk->menu_buf[no];
	wk->Data[ no ].param = param;
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�E�B���h�E�\��
 *
 * @param	win		BMP�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OpeningTalkWinPut( GF_BGL_BMPWIN * win, WINTYPE wintype )
{
	TalkWinGraphicSet( win->ini, GF_BGL_BmpWinGet_Frame(win), OP_TALKWIN_CGX_NUM,
						OP_TALKWIN_PAL, wintype, HEAPID_OPENING );

	GF_BGL_BmpWinDataFill( win, 15 );
	BmpTalkWinWrite( win, WINDOW_TRANS_ON, OP_TALKWIN_CGX_NUM, OP_TALKWIN_PAL );
	return;
}






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
 *
 * @return	"�����`�惋�[�`���̃C���f�b�N�X"
 */
//--------------------------------------------------------------
#define OPENING_TEMP_BUF_SIZE	(100)

