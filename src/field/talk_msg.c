//============================================================================================
/**
 * @file	talk_msg.c
 * @brief	���b�Z�[�W�\������
 * @author	Hiroyuki Nakamura
 * @date	2004.10.28
 */
//============================================================================================
#define TALK_MSG_H_GLOBAL

#include "common.h"
#include "fntsys.h"

#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/pm_str.h"
#include "system/fontproc.h"
#include "system/arc_util.h"
#include "fld_bmp.h"
#include "system/lib_pack.h"
#include "system/pmfprint.h"
#include "system/window.h"

#include "talk_msg.h"
#include "fieldmap.h"
#include "system/palanm.h"


//============================================================================================
//	�V���{����`
//============================================================================================


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================




//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�\���V�X�e��������
 *
 * @param	type	�p���b�g�]���^�C�v
 * @param	init	���b�Z�[�W�v�����g�������t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMsgPrintInit( u32 type, u32 init )
{
	if( init == MSG_PRINT_INIT_ON ){
		MSG_PrintInit();
	}
	SystemFontPaletteLoad( type, FLD_MENU_WIN_PAL * 32, HEAPID_FIELD );
	TalkFontPaletteLoad( type, FLD_MSG_WIN_PAL * 32, HEAPID_FIELD );
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�pBMP�擾
 *
 * @param	ini		BGL�f�[�^
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	frmnum	BG�t���[��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldTalkBmpAdd( GF_BGL_INI * ini, GF_BGL_BMPWIN * win, u32 frmnum )
{
	if( frmnum == FLD_MBGFRM_FONT ){
		GF_BGL_BmpWinAdd(
			ini, win, FLD_MBGFRM_FONT, FLD_MSG_WIN_PX, FLD_MSG_WIN_PY,
			FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, FLD_MSG_WIN_PAL, FLD_MSG_WIN_CGX );
	}else{
		GF_BGL_BmpWinAdd(
			ini, win, FLD_SBGFRM_FONT, FLD_MSG_WIN_S_PX, FLD_MSG_WIN_S_PY,
			FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, FLD_MSG_WIN_S_PAL, FLD_MSG_WIN_S_CGX );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�E�B���h�E�\��
 *
 * @param	win		BMP�f�[�^
 * @param	cfg		�R���t�B�O�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldTalkWinPut( GF_BGL_BMPWIN * win, const CONFIG * cfg )
{
	TalkWinGraphicSet(
		win->ini, GF_BGL_BmpWinGet_Frame( win ),
		TALK_WIN_CGX_NUM, TALK_WIN_PAL, CONFIG_GetWindowType(cfg), HEAPID_FIELD );

	FieldTalkWinClear( win );

	BmpTalkWinWrite( win, WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALK_WIN_PAL );
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�E�B���h�E�̈�N���A
 *
 * @param   win		
 *
 */
//--------------------------------------------------------------------------------------------
void FieldTalkWinClear( GF_BGL_BMPWIN* win )
{
	GF_BGL_BmpWinDataFill( win, 15 );
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�X�^�[�g
 *
 * @param	win		BMP�f�[�^
 * @param	msg		���b�Z�[�W
 * @param	cfg		�R���t�B�O�f�[�^
 * @param	skip	�X�L�b�v���t���O
 *
 * @return	���b�Z�[�W�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u8 FieldTalkMsgStart( GF_BGL_BMPWIN * win, STRBUF * msg, const CONFIG * cfg, u8 skip )
{
	u8	idx;

	MsgPrintSkipFlagSet( skip );
	MsgPrintAutoFlagSet( MSG_AUTO_OFF );
	MsgPrintTouchPanelFlagSet( MSG_TP_OFF );
	idx = GF_STR_PrintSimple( win, FONT_TALK, msg, 0, 0, CONFIG_GetMsgPrintSpeed(cfg), NULL );

	return idx;
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�X�^�[�g(������Ɗg����)
 *
 * @param	win		BMP�f�[�^
 * @param	msg		���b�Z�[�W
 * @param	skip	�X�L�b�v���t���O
 *
 * @return	���b�Z�[�W�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u8 FieldTalkMsgStartEx( GF_BGL_BMPWIN * win, STRBUF * msg, int font, int msg_speed, u8 skip, int auto_flag )
{
	MsgPrintSkipFlagSet( skip );
	MsgPrintAutoFlagSet( auto_flag );
	MsgPrintTouchPanelFlagSet( MSG_TP_OFF );
	return GF_STR_PrintSimple( win, font, msg, 0, 0, msg_speed, NULL );
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h��b�I���҂�
 *
 * @param	msg_index	���b�Z�[�W�C���f�b�N�X
 *
 * @retval	"0 = ��b��"
 * @retval	"1 = �I��"
 */
//--------------------------------------------------------------------------------------------
u8 FldTalkMsgEndCheck( u8 msg_index )
{
	if( GF_MSG_PrintEndCheck( msg_index ) == 0 ){
		return 1;
	}
	return 0;
}




//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h�Ŕp�pBMP�擾
 *
 * @param	ini		BGL�f�[�^
 * @param	win		BMP�f�[�^�i�[�ꏊ
 * @param	type	�Ŕ^�C�v
 * @param	frmnum	BG�t���[��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldBoardBmpAdd( GF_BGL_INI * ini, GF_BGL_BMPWIN * win, u16 type, u16 frmnum )
{
	u16	px, sx;

	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
		px = FLD_BOARD_WIN_PX;
		sx = FLD_BOARD_WIN_SX;
	}else{
		px = FLD_MSG_WIN_PX;
		sx = FLD_MSG_WIN_SX;
	}

	if( frmnum == FLD_MBGFRM_FONT ){
		GF_BGL_BmpWinAdd(
			ini, win, FLD_MBGFRM_FONT, px, FLD_BOARD_WIN_PY,
			sx, FLD_BOARD_WIN_SY, FLD_BOARD_WIN_PAL, FLD_BOARD_WIN_CGX );
	}else{
		GF_BGL_BmpWinAdd(
			ini, win, FLD_SBGFRM_FONT, px, FLD_BOARD_WIN_S_PY,
			sx, FLD_BOARD_WIN_S_SY, FLD_BOARD_WIN_S_PAL, FLD_BOARD_WIN_S_CGX );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h�ŔE�B���h�E�\��
 *
 * @param	win		BMP�f�[�^
 * @param	type	�Ŕ^�C�v
 * @param	map		�}�b�v�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldBoardWinPut( GF_BGL_BMPWIN * win, u16 type, u16 map )
{
	BoardWinGraphicSet(
		win->ini, GF_BGL_BmpWinGet_Frame( win ),
		BOARD_WIN_CGX_NUM, BOARD_WIN_PAL, type, map, HEAPID_FIELD );

	GF_BGL_BmpWinDataFill( win, 15 );
	BmpBoardWinWrite( win, WINDOW_TRANS_ON, BOARD_WIN_CGX_NUM, BOARD_WIN_PAL, type );
}
