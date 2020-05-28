//==============================================================================
/**
 * @file	d_tool.h
 * @brief	�퓬�p�f�o�b�O���
 * @author	goto
 * @date	2005.10.25(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/fontproc.h"
#include "system/pm_str.h"

#include "str_tool.h"
#include "wazaeffect/we_mana.h"
#include "system/snd_tool.h"
#include "system/msgdata.h"


#include "system/bmp_list.h"
#include "ball_effect.h"
#include "battle_particle.h"

#include "d_tool.h"
#include "d_we.h"
#include "ball_effect.h"


//--------------------------------------------------------------
/**
 * @brief	�E�B���h�E�̍쐬
 *
 * @param	bgl	
 * @param	win	
 * @param	frm	
 * @param	x	
 * @param	y	
 * @param	sx	
 * @param	sy	
 * @param	pal	
 * @param	ofs	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DT_WinAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, u8 frm, u8 x, u8 y, u8 sx, u8 sy, u8 pal, u16 ofs)
{
	GF_BGL_BmpWinAdd(bgl, win, frm, x, y, sx, sy, pal, ofs);
}


//--------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�̈揉����
 *
 * @param	bgl	
 * @param	index
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DT_MsgClear(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win)
{
	GF_BGL_BmpWinDataFill(win, 0x11);
	GF_BGL_ScrClear(bgl, BATTLE_FRAME_EFFECT);
}


//--------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�\��
 *
 * @param	bgl
 * @param	index	
 * @param	str	
 * @param	x
 * @param	y
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DT_MsgPrint(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, STRBUF* str, u16 x, u16 y, int flag)
{	
	MSG_PRINT_HEADER	mph;
	STRBUF* strbuf = (STRBUF*)str;
	
	mph.msg			= (const u16*)strbuf;	///< ������
	mph.bmpwin		= win;					///< �`��E�B���h�E
	mph.msg_index	= 0;					///< ���b�Z�[�W�C���f�b�N�X(�C�}�C�`��
	mph.fnt_index	= FONT_SYSTEM;			///< �t�H���g

	mph.start_x		= x;					///< �E�C���h�E���\���J�n�w�I�t�Z�b�g
	mph.start_y		= y;					///< �E�C���h�E���\���J�n�x�I�t�Z�b�g
	mph.write_x		= x;					///< �E�C���h�E���`��w�I�t�Z�b�g(�����l��start_x�Ɠ���)
	mph.write_y		= y;					///< �E�C���h�E���`��x�I�t�Z�b�g(�����l��start_y�Ɠ���)
	mph.space_x		= 0;					///< �����Ԋu�w
	mph.space_y		= 0;					///< �����Ԋu�x
	mph.style		= 0;					///< �t�H���g�X�^�C��
	if (flag == 1){
		mph.f_col	= 4;					///< �����F�i���o�[
		mph.b_col	= 1;					///< �w�i�F�i���o�[
		mph.s_col	= 2;					///< �e�F�@�i���o�[
	}
	else if (flag == 2){
		mph.f_col	= 6;					///< �����F�i���o�[
		mph.b_col	= 1;					///< �w�i�F�i���o�[
		mph.s_col	= 1;					///< �e�F�@�i���o�[
	}
	else {
		mph.f_col	= 3;					///< �����F�i���o�[
		mph.b_col	= 1;					///< �w�i�F�i���o�[
		mph.s_col	= 1;					///< �e�F�@�i���o�[
	}
	mph.dot_tbl		= 0;					///< �g��p�h�b�g�e�[�u��
	mph.dot_wy		= 0;					///< �g�厞��Y���W�̕`��␳�l	

	GF_STR_Print( &mph, 0, NULL );
}

