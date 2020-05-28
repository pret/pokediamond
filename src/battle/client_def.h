
//============================================================================================
/**
 * @file	client_def.h
 * @bfief	�퓬�N���C�A���g�v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#ifndef __CLIENT_DEF_H_
#define __CLIENT_DEF_H_

#include	"system/softsprite.h"
#include	"gauge.h"
#include 	"client_types.h"

///<�N���C�A���g�p���[�U�C���^�[�t�F�[�X�\���̐錾
typedef struct
{
	TCB_FUNC	UI_CommandSelect;		///<�R�}���h�I��
	TCB_FUNC	UI_WazaSelect;			///<�Z�I��
	TCB_FUNC	UI_DirSelect;			///<�U���ΏۑI��
	TCB_FUNC	UI_ItemSelect;			///<�A�C�e���I��
	TCB_FUNC	UI_PokemonSelect;		///<�|�P�����I��
	TCB_FUNC	UI_YesNoSelect;			///<Yes/No�I��
}USER_INTERFACE;

///<�N���C�A���g�p�p�����[�^�\���̐錾
struct client_param
{
	USER_INTERFACE	ui;
	CATS_ACT_PTR	cap;
	SOFT_SPRITE		*tr_ss;
	SOFT_SPRITE		*poke_ss;
	GF_BGL_BMPWIN	*win;
	GAUGE_WORK		gauge;		///<HP�Q�[�W
	CURSOR_SAVE		cursor_save;
	BMS_PTR			bms;
	OAM_DROP_SYS*	ods;		///< OAM �ϊ�
	void			*time_icon;					//�ʐM�ҋ@���b�Z�[�W�^�C�}�[�A�C�R���p�^�X�N
	u8				client_buffer[BUF_SIZE];
	u8				client_no;
	u8				client_type;
	u8				client_boot;
	u8				bip_flag;
	
	TCB_PTR			sin_tcb;	///<�I�𒆂̃|�P�����̗h�ꐧ��^�X�N
	u16				sin_sec;	///<�I�𒆂̃|�P�����̗h��F�b

	int				migawari_flag;
};

#endif __CLIENT_DEF_H_
