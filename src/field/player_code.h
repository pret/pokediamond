//******************************************************************************
/**
 *
 * @file	player_code.h
 * @brief	���@�V���{���Q�Ɓ@���X�N���v�g�Q�ƃA���@�̂�enum�֎~
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#ifndef PLAYER_CODE_H_FILE
#define PLAYER_CODE_H_FILE

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	���@�`��
//--------------------------------------------------------------
#define HERO_FORM_NORMAL 		(0x00)							///<2��
#define HERO_FORM_CYCLE			(0x01)							///<���]��
#define HERO_FORM_SWIM			(0x02)							///<�g���
//�ȉ��`�掯�� ���ۂɂ͐ݒ肳��Ȃ�
#define HERO_DRAWFORM_SP		(0x03)							///<��`�Z
#define HERO_DRAWFORM_WATER		(0x04)							///<������
#define HERO_DRAWFORM_CONTEST	(0x05)							///<�R���e�X�g
#define HERO_DRAWFORM_FISHING	(0x06)							///<�ނ�
#define HERO_DRAWFORM_POKETCH	(0x07)							///<�|�P�b�`
#define HERO_DRAWFORM_SAVE		(0x08)							///<�Z�[�u
#define HERO_DRAWFORM_BANZAI	(0x09)							///<����

#define HERO_FORM_MAX (HERO_FORM_SWIM+1)

//���]�Ԃ͈��ނɂȂ�܂���
#define HERO_FORM_CYCLE_R (HERO_FORM_CYCLE)
#define HERO_FORM_CYCLE_D (HERO_FORM_CYCLE)

//--------------------------------------------------------------
///	���N�G�X�g
//--------------------------------------------------------------
#define HERO_REQBIT_NON			(0)							///<���N�G�X�g�Ȃ�
#define HERO_REQBIT_NORMAL		(1<<0)						///<�Q���ړ��ɕύX
#define HERO_REQBIT_CYCLE		(1<<1)						///<���]�Ԉړ��ɕύX
#define HERO_REQBIT_SWIM		(1<<2)						///<�g���ړ��ɕύX
#define HERO_REQBIT_UNDER_OFF	(1<<3)						///<��������𖳌��ɂ���
#define HERO_REQBIT_WATER		(1<<4)						///<�����莩�@�ɕύX����
#define HERO_REQBIT_FISHING		(1<<5)						///<�ނ莩�@�֕\���ύX
#define HERO_REQBIT_POKETCH		(1<<6)						///<�|�P�b�`���@�֕\���ύX
#define HERO_REQBIT_SAVE		(1<<7)						///<�Z�[�u���@�֕\���ύX
#define HERO_REQBIT_BANZAI		(1<<8)						///<���Ύ��@�֕\���ύX

#define HERO_REQBIT_MAX			(9)							///<���N�G�X�g����

#endif //PLAYER_CODE_H_FILE
