//==============================================================================================
/**
 * @file	opneing_obj.h
 * @brief	�I�[�v�j���O OBJ
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#ifndef _OPENING_OBJ_H_
#define _OPENING_OBJ_H_

#include "system/clact_tool.h"


//==============================================================================================
//
//	��`
//
//==============================================================================================
//CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define RESOURCE_NUM					(4)

#define OPENING_ACT_MAX					(3)

#define OPENING_ACT_START				(0)

//���\�[�X�}�l�[�W���[�I�u�W�F�N�g�i���o�[
enum{
	OP_RES_OBJ_HAKASE = 0,
	OP_RES_OBJ_RIVAL,

	OP_RES_OBJ_MAX,						//�ő吔
};


//==============================================================================================
//
//	�\���̐錾
//
//==============================================================================================
typedef struct OPENING_OBJ_WORK_tag
{
	CLACT_SET_PTR 			ClactSet;						//�Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	RendData;						//�ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	ResMan[RESOURCE_NUM];			//���\�[�X�}�l�[�W��

	CLACT_U_RES_OBJ_PTR 	ResObjTbl[2][RESOURCE_NUM];		//���\�[�X�I�u�W�F�e�[�u��(�㉺���)

	CLACT_WORK_PTR			ClActWork[OPENING_ACT_MAX];		//�Z���A�N�^�[���[�N�|�C���^�z��
}OPENING_OBJ_WORK;


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[������
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningInitCellActor( OPENING_OBJ_WORK *wk );

//--------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[���Z�b�g
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
//extern void OpeningSetActor( OPENING_OBJ_WORK *wk );
extern void OpeningSetActor( OPENING_OBJ_WORK *wk, u32 index, u32 data_no, u32 anm_no );

//--------------------------------------------------------------
/**
 * @brief	2D�Z���I�u�W�F�N�g���
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningRereaseCellObject(OPENING_OBJ_WORK *wk);

//--------------------------------------------------------------
/**
 * @brief	�o�j�b�V������
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *@param	flag	�`��t���O	0:��`��	1:�����_���`��	
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningClactVanish(OPENING_OBJ_WORK *wk, int no, int flag);

//--------------------------------------------------------------
/**
 * @brief	�ړ�
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
extern VecFx32 OpeningClactMove(OPENING_OBJ_WORK *wk, int no, int spd);

//--------------------------------------------------------------
/**
 * @brief	�������W�Z�b�g
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningClactMoveInit(OPENING_OBJ_WORK *wk, int no );

//--------------------------------------------------------------
/**
 * @brief	���W�Z�b�g
 *
 * @param	wk		OPENING_OBJ_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
extern void OpeningClactPosSet(OPENING_OBJ_WORK *wk, int no, int x, int y );


#endif //_OPENING_OBJ_H_


