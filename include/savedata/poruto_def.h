/**
 *	@file	poruto_def.h
 *	@brief	�|���g�f�[�^�@�萔��`�t�@�C��
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 */

#ifndef __H_PORUTO_DEF_H__
#define __H_PORUTO_DEF_H__

#define PORUTO_STOCK_MAX	(100)	///<�P�[�X�ɓ���Ă����鐔
#define PORUTO_PARAM_MAX	(255)	///<���̃p�����[�^MAX�l
#define PORUTO_PARAM_VMAX	(99)	///<���̃p�����[�^�`�����l
#define PORUTO_DATA_NULL	(0xFFFF)	///<�󂫗̈悪�Ȃ��Ƃ��ɕԂ�l
#define PORUTO_MILD_VALUE	(50)	///<�u�}�C���h�v�Ɣ��肳���l

///�|���g�Z�[�u�f�[�^�̃p�����[�^�Q��ID
typedef enum{
 PORUTO_PARAID_FLAVOR,
 PORUTO_PARAID_SPICY,
 PORUTO_PARAID_ASTR,
 PORUTO_PARAID_SWEET,
 PORUTO_PARAID_BITTER,
 PORUTO_PARAID_SOUR,
 PORUTO_PARAID_TASTE,
 PORUTO_PARAID_NUM,
}PORUTO_PARAID;

//��ID
typedef enum{
 PORUTO_FLAVOR_SPICY,	///<�h��
 PORUTO_FLAVOR_SP_AS,	///<���炵��
 PORUTO_FLAVOR_SP_SW,	///<���炠��
 PORUTO_FLAVOR_SP_BI,	///<����ɂ�
 PORUTO_FLAVOR_SP_SO,	///<���炷����
 PORUTO_FLAVOR_AS_SP,	///<���Ԃ���
 PORUTO_FLAVOR_ASTR,	///<�a��
 PORUTO_FLAVOR_AS_SW,	///<���Ԃ���
 PORUTO_FLAVOR_AS_BI,	///<���Ԃɂ�
 PORUTO_FLAVOR_AS_SO,	///<���Ԃ�����
 PORUTO_FLAVOR_SW_SP,	///<���܂���
 PORUTO_FLAVOR_SW_AS,	///<���܂���
 PORUTO_FLAVOR_SWEET,	///<�Â�
 PORUTO_FLAVOR_SW_BI,	///<���܂ɂ�
 PORUTO_FLAVOR_SW_SO,	///<���܂�����
 PORUTO_FLAVOR_BI_SP,	///<�ɂ�����
 PORUTO_FLAVOR_BI_AS,	///<�ɂ�����
 PORUTO_FLAVOR_BI_SW,	///<�ɂ�����
 PORUTO_FLAVOR_BITTER,	///<�ꂢ
 PORUTO_FLAVOR_BI_SO,	///<�ɂ�������
 PORUTO_FLAVOR_SO_SP,	///<�����ς���
 PORUTO_FLAVOR_SO_AS,	///<�����ς���
 PORUTO_FLAVOR_SO_SW,	///<�����ς���
 PORUTO_FLAVOR_SO_BI,	///<�����ςɂ�
 PORUTO_FLAVOR_SOUR,	///<�_���ς�
 PORUTO_FLAVOR_HEAVY,	///<�����Ă�
 PORUTO_FLAVOR_THICK,	///<���ǂ�
 PORUTO_FLAVOR_NGOOD,	///<�܂���
 PORUTO_FLAVOR_MILD,	///<�܂�₩
 PORUTO_FLAVOR_MAX,		///<���̎�ސ�
 PORUTO_FLAVOR_NULL,	///<�����l
}PORUTO_FLAVORID;

///���^�C�v
typedef enum{
 PORUTO_FTYPE_SPICY,	///<�h���n
 PORUTO_FTYPE_ASTR,		///<�a���n
 PORUTO_FTYPE_SWEET,	///<�Â��n
 PORUTO_FTYPE_BITTER,	///<�ꂢ�n
 PORUTO_FTYPE_SOUR,		///<�_���ς��n
 PORUTO_FTYPE_MIX,		///<�~�b�N�X
 PORUTO_FTYPE_MAX,
 PORUTO_FTYPE_NUM = 5,	///<��n���̐�
}PORUTO_FTYPE;

#endif	//__H_PORUTO_DEF_H__

