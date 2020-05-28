//==============================================================================
/**
 * @file	font_obj.h
 * @brief	�t�H���g��OBJ�ŕ\������
 * @author	matsuda
 * @date	2005.10.17(��)
 */
//==============================================================================
#ifndef __FONT_OBJ_H__
#define __FONT_OBJ_H__

#include "system/fontproc.h"
#include "system/clact_tool.h"
#include "system/fontproc.h"
#include "gflib/msg_print.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�t�H���gOBJ�Ŏg�p�o����ő�A�N�^�[��
#define FONTOBJ_ACTOR_MAX		(8)	//����32�Ȃ�8�����256�h�b�g�s���̂ŁA�Ƃ肠����8��

///�t�H���gOBJ��OAM�T�C�Y��`
enum{
	FONTOBJ_OAMSIZE_32x16,	///<32x16�`���OAM���g�p
};

///X���W�̃Z�b�g�A�擾���@
enum{
	FONTOBJ_POS_LEFT,
	FONTOBJ_POS_CENTER,
	FONTOBJ_POS_RIGHT,
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�t�H���gOBJ�쐬��A�����p�����[�^(�t�H���gOBJ�p�̃A�N�^�[���[�N)
typedef struct{
	u8 use_oam;			///<�g�p���Ă���OAM��(�A�N�^�[��)
	u8 type_dot;		///<1��OAM�̉����h�b�g��
	u16 font_len;		///<������̃h�b�g��
	s16 x;				///<X���W(���[���W)
	s16 y;				///<Y���W(���S���W)
	CATS_ACT_PTR cap[FONTOBJ_ACTOR_MAX];

	u16 start_charid;	///<�L�����}�l�[�W���[�o�^�J�nID
	u16 start_palid;	///<�p���b�g�}�l�[�W���[�o�^�J�nID
	u16 start_cellid;	///<�Z���}�l�[�W���[�o�^�J�nID
	u16 start_anmid;	///<�Z���A�j���}�l�[�W���[�o�^�J�nID
}FONTOBJ_ACTWORK;

///�t�H���gOBJ�쐬�ɕK�v�ȃf�[�^
typedef struct{
	FONTOBJ_ACTWORK *fa;

	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	FONT_TYPE font;
	const STRBUF* str;
	u32 margin;
	GF_PRINTCOLOR print_color;

	NNS_G2D_VRAM_TYPE d_area;
	int oam_size;
	u32 max_oam;
	int oam_fix;
	int soft_pri;
	int bg_pri;
	int pal_offset;		///<�p���b�g�ԍ��I�t�Z�b�g
	
	int heap_id;

	u16 start_charid;	///<�L�����}�l�[�W���[�o�^�J�nID
	u16 start_palid;	///<�p���b�g�}�l�[�W���[�o�^�J�nID
	u16 start_cellid;	///<�Z���}�l�[�W���[�o�^�J�nID
	u16 start_anmid;	///<�Z���A�j���}�l�[�W���[�o�^�J�nID
}FONTOBJ_CREATE_DATA;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void FontOBJ_Create(const FONTOBJ_CREATE_DATA *fcd);
extern void FontOBJ_Delete(CATS_RES_PTR crp, FONTOBJ_ACTWORK *fa, int not_pal_free);
extern void FontOBJ_PosSet(FONTOBJ_ACTWORK *fa, int set_type, s16 x, s16 y);
extern void FontOBJ_PosGet(FONTOBJ_ACTWORK *fa, int get_type, s16 *x, s16 *y);
extern void FontOBJ_Enable(FONTOBJ_ACTWORK *fa, int enable);


//==============================================================================
//	inline��`
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �t�H���gOBJ���쐬���܂�
 *
 * @param   fa				�t�H���gOBJ�������A�A�N�^�[��񂪂����ɑ������܂�
 * @param   bgl				BGL�f�[�^
 * @param   csp				
 * @param   crp				
 * @param   font			�t�H���g�^�C�v(FONT_SYSTEM��)
 * @param   str				�����f�[�^
 * @param   margin			�����Ԋu
 * @param   print_color		�����̐F���
 * @param   d_area			Vram�]���ʒu(NNS_G2D_VRAM_TYPE_2DMAIN or NNS_G2D_VRAM_TYPE_2DSUB)
 * @param   oam_size		�t�H���gOBJ�Ɏg�p����OAM�`��(FONTOBJ_OAMSIZE_32x16��)
 * @param   max_oam			�t�H���gOBJ�쐬�Ɏg�p���Ă����ő�OAM��(1�`FONTOBJ_ACTOR_MAX)
 * @param   oam_fix			TRUE=��ɍő������OAM�Ƃ��̕��̃L�����̈���g�p����
 *                          (����������Ȃ��������͑S�ċ󔒂Ŗ��߂܂�)
 *                          FALSE=max_oam�͈̔͂̒��ŕK�v�ȕ������g�p���܂�
 * @param   soft_pri		�A�N�^�[�\�t�g�v���C�I���e�B
 * @param   bg_pri			�A�N�^�[BG�v���C�I���e�B
 * @param   pal_offset		�p���b�g�ԍ��I�t�Z�b�g
 * @param   heap_id			�q�[�vID�B�֐����ňꎞ�I�Ƀ��������m�ۂ���ۂɎg�p���܂�
 *                          (�֐�����o�鎞�ɂ͉������Ă��܂�)
 * @param   start_charid	�t�H���gOBJ�쐬���A�L�����}�l�[�W���ɓo�^����J�nID
 *                          (����ID�ԍ�����A�����ɕK�v��OAM�����A�A�Ԃœo�^���܂�)
 * @param   start_palid		�p���b�g�}�l�[�W���ɓo�^����J�nID(�ڍא�����start_charid�Ɠ����ł�)
 * @param   start_cellid	�Z���}�l�[�W���ɓo�^����J�nID(�ڍא�����start_charid�Ɠ����ł�)
 * @param   start_anmid		�Z���A�j���}�l�[�W���ɓo�^����J�nID(�ڍא�����start_charid�Ɠ����ł�)
 *
 *
 *
 * ���ɓo�^�ς݂̃p���b�g�����p����`�ł���ꍇ�́A���̓o�^�ς݂̊Ǘ�ID��n���Ă�������
 * 
 * 8x8�t�H���g�ɂ͖��Ή��ł��B
 *
 */
//--------------------------------------------------------------
inline void FontOBJ_CreateInline(FONTOBJ_ACTWORK *fa, GF_BGL_INI *bgl, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, FONT_TYPE font, const STRBUF* str, u32 margin, GF_PRINTCOLOR print_color, 
	NNS_G2D_VRAM_TYPE d_area, int oam_size, u32 max_oam, int oam_fix,int soft_pri,int bg_pri, 
	int pal_offset, int heap_id, s32 start_charid, s32 start_palid, 
	s32 start_cellid, s32 start_anmid)
{
	FONTOBJ_CREATE_DATA fcd;
	
	fcd.fa = fa;

	fcd.bgl = bgl;
	fcd.csp = csp;
	fcd.crp = crp;

	fcd.font = font;
	fcd.str = str;
	fcd.margin = margin;
	fcd.print_color = print_color;

	fcd.d_area = d_area;
	fcd.oam_size = oam_size;
	fcd.max_oam = max_oam;
	fcd.oam_fix = oam_fix;
	fcd.soft_pri = soft_pri;
	fcd.bg_pri = bg_pri;
	fcd.pal_offset = pal_offset;
	
	fcd.heap_id = heap_id;

	fcd.start_charid = start_charid;
	fcd.start_palid = start_palid;
	fcd.start_cellid = start_cellid;
	fcd.start_anmid = start_anmid;

	FontOBJ_Create(&fcd);
}

#endif	//__FONT_OBJ_H__
