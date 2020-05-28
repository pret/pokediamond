/**
 *	@file	poruto_util.h
 *	@brief	�|���g�f�[�^�@�A�N�Z�X�n�֐���`�t�@�C��
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 *
 *	�����f�[�^�Q�Ƃ��s�v�̏ꏊ�ł́A���̃w�b�_�ɒ�`���ꂽ
 *	�@�A�N�Z�X�֐���ʂ��ăf�[�^������
 */

#ifndef __H_PORUTO_UTIL_H__
#define __H_PORUTO_UTIL_H__

#include "savedata/savedata_def.h"
#include "savedata/poruto_def.h"

//------------------------------------------------------------
/**
 * @brief	�|���g�Z�[�u�f�[�^�u���b�N�Ǘ��\���ւ̕s���S�^�|�C���^
 *
 * ���g�͌����Ȃ����ǃ|�C���^�o�R�ŎQ�Ƃ͂ł���
 */
//------------------------------------------------------------
typedef struct _PORUTO_BLOCK PORUTO_BLOCK;

//------------------------------------------------------------
/**
 * @brief	�|���g�f�[�^�Ǘ��\���ւ̕s���S�^�|�C���^
 *
 * ���g�͌����Ȃ����ǃ|�C���^�o�R�ŎQ�Ƃ͂ł���
 */
//------------------------------------------------------------
typedef struct _PORUTO_DATA PORUTO_DATA;


/**
 *	@brief	�Z�[�u�f�[�^�u���b�N�ւ̃|�C���^���擾
 */
extern PORUTO_BLOCK* SaveData_GetPorutoBlock(SAVEDATA* sv);

/**
 *	@brief	�|���g�Z�[�u�f�[�^�T�C�Y�擾
 */
extern int PORUTO_GetSaveWorkSize(void);

/**
 *	@brief	�|���g�f�[�^�z�񏉊���
 */
extern void PORUTO_Init(PORUTO_BLOCK* dat);

/**
 *	@brief	�|���g�Z�[�u�f�[�^�̋󂫗̈��T��
 *
 *	@retval	PORUTO_DATA_NULL	�󂫗̈悪�Ȃ�
 *	@retval "���̑�"			�󂫗̈��IndexNo
 */
extern u16 PORUTO_SearchNullData(PORUTO_BLOCK* block);

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^�󂫗̈�ɒǉ�����
 *
 *	@retval	PORUTO_DATA_NULL	�󂫗̈悪�Ȃ��Ēǉ��ł��Ȃ�����
 *	@retval "���̑�"			�ǉ������̈��index
 */
extern u16 PORUTO_AddData(PORUTO_BLOCK* block,PORUTO_DATA* dat);

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^����폜����(index�w��)
 *
 */
extern BOOL PORUTO_DelData(PORUTO_BLOCK* block,u16 idx);

/**
 *	@brief	�|���g�Z�[�u�f�[�^�𐮗�����
 *
 *	���f�[�^�z��̌��󂫂��l�߂�
 */
extern void PORUTO_DataAdjust(PORUTO_BLOCK* block);

/**
 *	@brief	�Z�[�u�f�[�^�̈�ɂ���L���ȃ|���g�f�[�^����Ԃ�
 */
extern u16	PORUTO_GetDataNum(PORUTO_BLOCK* block);

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^����擾����(index�w��)
 *
 *	�������n���ꂽPORUTO_DATA�\���̌^�̈�ցA�Z�[�u�f�[�^���R�s�[���ĕԂ�
 */
extern void PORUTO_GetData(PORUTO_BLOCK* block,u16 idx,PORUTO_DATA* dest);

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^����擾����(index�w��/�������m�۔�)
 *
 *	��PORUTO_DATA�\���̌^�̈���m�ۂ��A�Z�[�u�f�[�^���R�s�[���ĕԂ�
 *	�@�Ăяo�����������I�ɉ�����邱�ƁI
 */
extern PORUTO_DATA* PORUTO_GetDataAlloc(PORUTO_BLOCK* block,u16 idx,int heapID);

//============================================================
/**
 *	�|���g�f�[�^�A�N�Z�X�n�֐�
 */
//============================================================
/**
 *	@brief	�|���g�f�[�^�T�C�Y�擾
 */
extern int PorutoData_GetWorkSize(void);

/**
 *	@brief	���̃|���g�f�[�^���L�����ǂ����Ԃ�
 */
extern BOOL PorutoData_IsEnable(PORUTO_DATA* dat);

/**
 *	@brief	�|���g�f�[�^���[�N�쐬
 */
extern PORUTO_DATA* PorutoData_AllocWork(int heapID);

/**
 *	@brief	�|���g�f�[�^�N���A
 */
extern void PorutoData_Clear(PORUTO_DATA* dat);

/**
 *	@brief	�|���g�f�[�^�R�s�[
 */
extern void PorutoData_Copy(PORUTO_DATA* src,PORUTO_DATA* dest);

/**
 *	@brief	�|���g�̃p�����[�^���擾
 *
 *	@param	dat
 *	@param	id	enum PORUTO_PARAID�^(poruto_def.h�Q��)
 *
 *	@return	u8:�擾�����p�����[�^
 */
extern u8 PorutoData_GetParam(PORUTO_DATA* dat,PORUTO_PARAID id);

/**
 *	@brief	�|���g�̃p�����[�^���Z�b�g
 *
 *	@param	dat
 *	@param	value	�Z�b�g�������f�[�^
 *	@param	id	enum PORUTO_PARAID�^(poruto_def.h�Q��)
 *
 */
extern void PorutoData_SetParam(PORUTO_DATA* dat,u8 valid,PORUTO_PARAID id);

/**
 *	@brief	���Ǝ|������|���g�̎�ނ����肵�A�p�����[�^���Z�b�g���ĕԂ�
 *
 *	@param	dat	PORUTO_DATA*:�p�����[�^���Z�b�g����|���g�f�[�^�^�\����
 *	@param	prm	u8[5]:5��ނ̖��l���i�[
 *	@param	taste	�|���l���i�[
 *	@param	mazui	�����I�ɕs�����|���g�ɂȂ邩�ǂ����H TRUE�Ȃ�܂����|���g
 *
 *	@return	PORUTO_FLAVORID	�쐬���ꂽ�|���g�̃t���o�[ID
 */
extern PORUTO_FLAVORID PorutoData_CalcParam(PORUTO_DATA* dat,u8 *prm,u8 taste,BOOL mazui);

/**
 *	@brief	�|���g�p�����[�^�擾(�z���)
 *
 *	���Ăяo�����Ńf�[�^�̎擾�ꏊ��p�ӂ���o�[�W����
 *	�@u8[PORUTO_PARAID_NUM] ���̃������G���A���K�v
 */
extern void PorutoData_GetParamArray(PORUTO_DATA* dat,u8* array);

/**
 *	@brief	�|���g�p�����[�^�擾(�z��,�������m�۔�)
 *
 *	���֐����ŕK�v�ȃo�b�t�@���擾���ĕԂ��o�[�W����
 *	�@�Ăяo�����Ŗ����I�ȃ�����������K�v
 */
extern u8* PorutoData_GetParamArrayMem(PORUTO_DATA* dat,int heapID);

/**
 *	@brief	�|���g�̃��x�����擾
 */
extern u8 PorutoData_GetLevel(PORUTO_DATA* dat);




//�f�o�b�O��p
#ifdef PM_DEBUG
/**
 *	@brief	�|���g�f�o�b�O�@�f�[�^�S������
 */
extern void PorutoDebug_AllDataDelete(PORUTO_BLOCK* block);
/**
 *	@brief	�|���g�f�o�b�O�@�e�L�g�[�ȃ|���g���w�肵�����ǉ�
 */
extern u16 PorutoDebug_AddRndData(PORUTO_BLOCK* block,u16 num);
#endif	//PM_DEBUG

#endif	//__H_PORUTO_UTIL_H__

