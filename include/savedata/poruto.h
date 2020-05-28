/**
 *  @file	poruto.h
 *	@brief	�|���g�@�Z�[�u�f�[�^�\����`�@�O���[�o���w�b�_
 *	@date	06.02.28
 *	@author	Miyuki Iwasawa
 *	
 *	���f�[�^���̂��`����ӏ��ȊO�ł͎Q�Ƃ��Ă͂����܂���
 *	���z�|�C���^�o�R�Ńf�[�^�A�N�Z�X�ł���Ηǂ��ӏ��ł�
 *	savedata/poruto_util.h��include���Ă�������
 */

#ifndef __H_PORUTO_H__
#define __H_PORUTO_H__

///�|���g�f�[�^�^
//=============================================================
//	�O�����J���Ă��܂����A���ڍ\���̃����o�փA�N�Z�X���邱�Ƃ�
//	�����Ă��܂���B
//
//	�����o�A�N�Z�X��savedata/poruto_util.h�ɒ�`���ꂽ
//	�A�N�Z�X�n�֐�����Ă�������
//
//=============================================================
typedef struct _PORUTO_DATA{
 union{
	struct{		
	u8	flavor;		///<���̎��
	u8	spicy;		///<�h�ݒl
	u8	astringent;	///<�a�ݒl
	u8	sweet;		///<�Ö�
	u8	bitter;		///<�ꖡ
	u8	sour;		///<�_��
	u8	taste;		///<�|���l
	u8	pad_dmy;	///<�p�f�B���O�p�_�~�[
	};
	u8 param[8];
 };
}_PORUTO_DATA;

//============================================================
///�|���g�f�[�^�A�N�Z�X�n�֐�
//============================================================
#include "savedata/poruto_util.h"

#endif	//__H_PORUTO_H__
