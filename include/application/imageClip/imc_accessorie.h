//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_accessorie.h
 *	@brief		�A�N�Z�T���[�Ǘ��V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.20
 *
 * �A�N�Z�T�������X�g�ŊǗ�����V�X�e��
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ACCESSORIE_H__
#define __IMC_ACCESSORIE_H__

#include <nnsys.h>
#include "include/system/swsprite.h"
#include "touchpanel.h"

#undef GLOBAL
#ifdef	__IMC_ACCESSORIE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�A�N�Z�T���Ǘ��f�[�^
//	
//=====================================
typedef struct IMC_ACCESSORIE_OBJ_tag{
	int accessorie_no;			// �A�N�Z�T���i���o�[
	
	
	SWSP_OBJ_PTR drawObj;	// �\���f�[�^

} IMC_ACCESSORIE_OBJ;

//-------------------------------------
//	
//	�A�N�Z�T���Ǘ��\����
//	
//=====================================
typedef struct IMC_ACCESSORIE_OBJ_TBL_tag{

	IMC_ACCESSORIE_OBJ* obj_tbl;
	int					obj_num;

} IMC_ACCESSORIE_OBJ_TBL;

//-------------------------------------
//	
//	�A�N�Z�T���f�[�^�o�^�֐�
//	
//=====================================
typedef struct {
	IMC_ACCESSORIE_OBJ_TBL* objTbl;	// �I�u�W�F�N�g�e�[�u��
	SWSP_SYS_PTR	SWSPsys;	// �X�v���C�g�V�X�e���f�[�^
	SWSP_CHAR_PTR	SWSPchar;	// �L�����N�^�f�[�^
	SWSP_PLTT_PTR	SWSPpltt;	// �p���b�g�f�[�^
	int					m_x;	// ���W��
	int					m_y;	// ���W��
	u32					accessorie_no;	// �A�N�Z�T���i���o�[
	u32					pltt_offs;	// �p���b�g�I�t�Z�b�g
} IMC_ACCE_ADD;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�N�g�e�[�u�����쐬
 *
 *	@param	obj_num		�A�N�Z�T����
 *	@param	heap		�q�[�v��
 *
 *	@return	IMC_ACCESSORIE_OBJ_TBL*	�I�u�W�F�N�g�e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ_TBL* IMC_ACCE_ObjTblInit( int obj_num, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�N�g�e�[�u�����쐬
 *
 *	@param	obj_num		�A�N�Z�T����
 *	@param	heap		�q�[�v��
 *
 *	@return	IMC_ACCESSORIE_OBJ_TBL*	�I�u�W�F�N�g�e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjTblDelete( IMC_ACCESSORIE_OBJ_TBL* obj_tbl );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���쐬
 *
 *	@param	data	�I�u�W�F�N�g�o�^�f�[�^
 *
 *	@return	IMC_ACCESSORIE_OBJ*	�A�N�Z�T���I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAdd( IMC_ACCE_ADD* data );

//----------------------------------------------------------------------------
/**
 * ��BG�T���l�C���o�^�p
 *
 *	@brief	�A�N�Z�T���쐬		�A�N�Z�T���ȊO�̃X�v���C�g�I�u�W�F�p
 *
 *	@param	data	�I�u�W�F�N�g�o�^�f�[�^
 *
 *	@return	IMC_ACCESSORIE_OBJ*	�A�N�Z�T���I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAddBGThum( IMC_ACCE_ADD* data );

//----------------------------------------------------------------------------
/**
 * ��SND�T���l�C���o�^�p
 *
 *	@brief	�A�N�Z�T���쐬		�A�N�Z�T���ȊO�̃X�v���C�g�I�u�W�F�p
 *
 *	@param	data	�I�u�W�F�N�g�o�^�f�[�^
 *
 *	@return	IMC_ACCESSORIE_OBJ*	�A�N�Z�T���I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAddSNDThum( IMC_ACCE_ADD* data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g�f�[�^�j��
 *
 *	@param	obj		�j������I�u�W�F�N�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjDelete( IMC_ACCESSORIE_OBJ* obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�N�g�e�[�u�����̃A�N�Z�T���j��
 *
 *	@param	obj_tbl		�I�u�W�F�N�g�e�[�u��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjDeleteAll( IMC_ACCESSORIE_OBJ_TBL* obj_tbl );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W��ݒ�	�i�����ɃX�v���C�g���ړ��j
 *
 *	@param	obj	�A�N�Z�T���I�u�W�F
 *	@param	x	x���W
 *	@param	y	y���W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjSetMat( IMC_ACCESSORIE_OBJ* obj, s16 x, s16 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W���擾
 *
 *	@param	obj		�A�N�Z�T���I�u�W�F�N�g
 *	@param	x		�����W�擾��
 *	@param	y		�����W�擾��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjGetMat( IMC_ACCESSORIE_OBJ* obj, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�T�C�Y���擾
 *
 *	@param	obj		�A�N�Z�T���I�u�W�F�N�g
 *	@param	x		���T�C�Y�擾��
 *	@param	y		���T�C�Y�擾��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjGetSize( IMC_ACCESSORIE_OBJ* obj, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����s��
 *
 *	@param	obj		�I�u�W�F�N�g�f�[�^
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_ACCE_ObjTpHit( IMC_ACCESSORIE_OBJ* obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����ׂ����s��
 *
 *	@param	obj			�I�u�W�F�N�g�f�[�^
 *	@param	offs_x		���ォ��̃I�t�Z�b�g�����W
 *	@param	offs_y		���ォ��̃I�t�Z�b�g�����W
 *	@param	drawData	�`�F�b�N����L�����N�^�f�[�^
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����	�i�I�t�Z�b�g���W�s��j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_ACCE_ObjTpHitEx( IMC_ACCESSORIE_OBJ* obj, int* offs_x, int* offs_y, NNSG2dCharacterData* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����s��
 *
 *	@param	obj		�I�u�W�F�N�g�f�[�^
 *	@param	x		���肘���W
 *	@param	y		���肙���W
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_ACCE_ObjTpHitSelf( IMC_ACCESSORIE_OBJ* obj, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�̃A�N�Z�T���̕`��ON�@OFF�@�ݒ�
 *
 *	@param	obj		�A�N�Z�T���I�u�W�F�N�g�f�[�^
 *	@param	flag	ON�@OFF�@�t���O
 *			
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjListDrawSet( IMC_ACCESSORIE_OBJ* obj, BOOL flag );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�̕\���D�揇�ʂ�ݒ�
 *
 *	@param	obj			�A�N�Z�T���I�u�W�F
 *	@param	priority	�\���D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjDrawPrioritySet( IMC_ACCESSORIE_OBJ* obj, int priority );
GLOBAL int IMC_ACCE_ObjDrawPriorityGet( IMC_ACCESSORIE_OBJ* obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�H������ŗǂ��T�C�Y���擾
 *
 *	@param	obj		�I�u�W�F�N�g�f�[�^
 *	@param	ins_x	�H������ŗǂ��T�C�YX
 *	@param	ins_y	�H������ŗǂ��T�C�YY
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjInSizeGet( IMC_ACCESSORIE_OBJ* obj, int* ins_x, int* ins_y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�g�k�l��ݒ肷��
 *
 *	@param	obj			�A�N�Z�T���I�u�W�F
 *	@param	scale_x		���g�k�l
 *	@param	scale_y		���g�k�l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjScaleSet( IMC_ACCESSORIE_OBJ* obj, int scale_x, int scale_y );

#undef	GLOBAL
#endif		// __IMC_ACCESSORIE_H__

