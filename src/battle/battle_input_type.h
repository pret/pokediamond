//==============================================================================
/**
 * @file	battle_input_type.h
 * @brief	�퓬���͉�ʂ̊O���Ŏg�p�����\���̂̒�`�Ȃ�
 * @author	matsuda
 * @date	2006.05.11(��)
 */
//==============================================================================
#ifndef __BATTLE_INPUT_TYPE_H__
#define __BATTLE_INPUT_TYPE_H__


//==============================================================================
//	�\���̒�`
//==============================================================================
//--------------------------------------------------------------
//	SCENE���[�N
//--------------------------------------------------------------
///�R�}���h�I����ʍ\���p��Scene���[�N
typedef struct{
	u8 client_type;
	u8 client_no;
	u8 sel_mons_no;
	u8		icon_status;

	s16		icon_hp;				//���݂�HP
	u16		icon_hpmax;				//���݂�HPMAX
}BINPUT_SCENE_COMMAND;

///�Z�I����ʍ\���p��Scene���[�N
typedef struct{
	u16			wazano[WAZA_TEMOTI_MAX];		//wazano
	u8			pp[WAZA_TEMOTI_MAX];			//pp
	u8			ppmax[WAZA_TEMOTI_MAX];			//ppmax
	u8			client_type;					//
}BINPUT_SCENE_WAZA;

///�|�P�����I����ʍ\���p��Scene���[�N
typedef struct{
	DIR_SELECT_POKE_PARAM	dspp[CLIENT_MAX];
	u8			client_type;
	u8			pokesele_type;	///<�ΏۑI���^�C�v
}BINPUT_SCENE_POKE;

///�u�͂��E�������v�I����ʍ\���p��Scene���[�N
typedef struct{
	u16 waza_no;
	
	u16 dummy;		///<4�o�C�g���E�_�~�[
}BINPUT_SCENE_YESNO;



#endif	//__BATTLE_INPUT_TYPE_H__

