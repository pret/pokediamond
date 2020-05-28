/**
 *	@file	poru_oam.h
 *	@brief	�|���gOAM�I�u�W�F�N�g�R���g���[���[
 *	@author	Miyuki Iwasawa
 *	@date	06.03.29
 */

#ifndef __H_PORUTO_OAM_H__
#define __H_PORUTO_OAM_H___

#undef GLOBAL
#ifndef PORUTO_OAM_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

#include "savedata/poruto_def.h"

//=================================================
///�\���̒�`
//=================================================
#define PORUOAM_RESMAX	(4)
#define PORUOAM_DRAW_MAIN	(NNS_G2D_VRAM_TYPE_2DMAIN)
#define PORUOAM_DRAW_SUB	(NNS_G2D_VRAM_TYPE_2DSUB)
#define PORUOAM_DRAW_BOTH	(NNS_G2D_VRAM_TYPE_2DMAX)

typedef enum{
 PORUOAM_CGXOFS_AUTO,
 PORUOAM_CGXOFS_AREA,
 PORUOAM_CGXOFS_ADJUST,
}PORUOAM_CGXOFS;


typedef enum{
 PORUOAM_VT_MAIN,	//���C����ʂɕ`��
 PORUOAM_VT_SUB,	//�T�u��ʂɕ`��
}PORUOAM_VRAMTYPE;

typedef struct{
	u8	valid;
	u8	flavor;
	u16	resNo;
}PORUOAM_ACTWORK;

typedef struct{
	u16	workID;
	CATS_ACT_PTR	act;
}PORUTO_OAM;

typedef struct {
	int	heapID;
	int	cgx_transofs;	///<CGX�]���I�t�Z�b�g
	u16	res_max;
	u16	pal_num;
	u16	act_max;
	u16	vramType;

	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// �ȈՃ����_�[�f�[�^
	CLACT_HEADER_TBL_PTR	clh;		// �w�b�_�[
	CLACT_U_RES_MANAGER_PTR	resMan[PORUOAM_RESMAX];	///< ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_TBL * resObjTbl[PORUOAM_RESMAX];///< ���\�[�X�I�u�W�F�e�[�u��

	PORUOAM_ACTWORK* work;
}PORUOAM_MAN;

/**
 *	@brief	�|���g�A�N�^�[�@�}�l�[�W��������
 *
 *	@param	heapID	�q�[�vID
 *	@param	actmax	�m�ۂ���Z���A�N�^�[�̈�̌�
 *	@param	palmax	�|���g�p�ɐ�L����OBJ�p���b�g�̖{��
 *	@param	vramType	�`���ʎw��(PORUOAM_DRAW_MAIN/SUB/BOTH)
 *  @param	cgx_transofs	�L�����N�^�]���I�t�Z�b�g���[�h�w��
 *							(PORUOAM_CGXOFS�^	PORUOAM_CGXOFS_AUTO:0����ςݏグ�^
 *												PORUOAM_CGXOFS_AREA:�󂫗̈挟���^
 */
GLOBAL PORUOAM_MAN* PoruOam_SysInit(int heapID,u16 actmax,u16 palmax,
		u16 vramType,PORUOAM_CGXOFS cgx_transofs);

/**
 *	@brief	�|���g�A�N�^�[�@�}�l�[�W�����
 */
GLOBAL void PoruOam_SysRelease(PORUOAM_MAN* wk);


/**
 *	@brief	�|���gOAM�@�`�惁�C��
 */
GLOBAL void PoruOam_DrawMain(PORUOAM_MAN* wk);


/**
 *	@brief	�|���gOAM�ǉ�
 *
 *	@param	flavor	�|���g�̎��ID
 *	@param	x		X���W
 *	@param	y		Y���W
 *	@param	z		Z���W
 *	@param	bg_pri	BG�v���C�I���e�B
 *	@param	spri	�\�t�g�E�F�A�v���C�I���e�B
 *	@param	vram_type	PORUOAM_VRAMTYPE�^
 *						PORUOAM_VT_MAIN:���C�����
 *						PORUOAM_VT_SUB:�T�u���
 *
 *	���K��PoruOam_Del�֐��Ŕj�����邱��
 */
GLOBAL PORUTO_OAM* PoruOam_Add(PORUOAM_MAN* wk,PORUTO_FLAVORID flavor,
		u16 x,u16 y,u16 z,u8 bg_pri,u8 spri,PORUOAM_VRAMTYPE vtype);

/**
 *	@brief	�o�^�ς�OAM�̃|���g�̎�ނ�ύX����
 *	
 *	@param	flavor	�|���g�̎��ID
 */
GLOBAL void PoruOam_ChangeFlavor(PORUOAM_MAN*wk,PORUTO_OAM* oam,PORUTO_FLAVORID flavor);

/**
 *	@brief	�|���gOAM�폜
 */
GLOBAL void PoruOam_Del(PORUOAM_MAN* wk,PORUTO_OAM* oam);


#endif	//__H_PORTO_OAM_H__
