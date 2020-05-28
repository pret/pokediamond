/**
 *	@file	mail.h
 *	@brief	���[���Z�[�u�f�[�^�\����`�@�O���[�o���w�b�_
 *	@date	06.01.12
 *	@author	Miyuki Iwasawa
 *
 *	���f�[�^���̂��`����ӏ��ȊO�ŎQ�Ƃ��Ă͂����܂���
 *	���z�|�C���^�o�R�Ńf�[�^�A�N�Z�X�ł���Ηǂ��ӏ��ł�
 *	savedata/mail_util.h��include���Ă�������
 */

#ifndef __MAIL_H__
#define __MAIL_H__

#include "system/gamedata.h"
//#include "system/buflen.h"
#include "system/pm_str.h"
#include "system/pms_data.h"

///�萔��`
#include "savedata/mail_def.h"
///���[���f�[�^�^
//=============================================================
//	�O�����J���Ă��܂����A���ڍ\���̃����o�փA�N�Z�X���邱�Ƃ�
//	�����Ă��܂���B
//
//	�����o�A�N�Z�X��savedata/mail_util.h�ɒ�`���ꂽ
//	�A�N�Z�X�n�֐�����Ă�������
//
//  size=56byte
//
//  �\���̃T�C�Y��4byte���E�ɍ��킹�邽�߁AMAIL_ICON�z��v�f����+1����
//  �p�f�B���O���s���Ă��܂�
//=============================================================
typedef struct _MAIL_DATA{
	u32	writerID;	//<�g���[�i�[ID 4
	u8	sex;	//<��l���̐��� 1
	u8	region;	//<���R�[�h 1
	u8	version;	//<�J�Z�b�g�o�[�W���� 1
	u8	design;	//<�f�U�C���i���o�[ 1
	STRCODE name[PERSON_NAME_SIZE+EOM_SIZE]; // 16
	MAIL_ICON	icon[MAILDAT_ICONMAX+1];	//<�A�C�R��NO�i�[�ꏊ[](3+1<padding>) 6+2=8
	PMS_DATA	msg[MAILDAT_MSGMAX];	//<���̓f�[�^
}_MAIL_DATA;


//=============================================================
/**
 *	���[���f�[�^�A�N�Z�X�n�֐�
 */
//=============================================================
#include "savedata/mail_util.h"
#endif	//__H_MAIL_H__

