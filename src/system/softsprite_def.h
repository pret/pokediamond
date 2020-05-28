
//============================================================================================
/**
 * @file	softsprite_def.h
 * @bfief	�\�t�g�E�G�A�X�v���C�g���g�p�����\���v���O����
 * @author	HisashiSogabe
 * @date	05.06.08
 */
//============================================================================================

#include	"system/softsprite.h"

#ifndef __SOFTSPRITE_DEF_H_
#define __SOFTSPRITE_DEF_H_

///<�\���p�\���̐錾
struct soft_sprite
{
	u32						exist			:1;			///<�z�u�t���O�i0:���z�u�@1:�z�u�ς݁j
	u32						poly_id			:6;			///<�|���S��ID
	u32						make_req		:1;			///<�e�N�X�`��MAKE���N�G�X�g
	u32						pal_req			:1;			///<�p���b�gMAKE���N�G�X�g
	u32										:23;		///<���܂�

	SOFT_SPRITE_ARC			ssa;						///<�ǂݍ��ރL�����N�^�A�p���b�g�f�[�^�̃A�[�J�C�o���i�[�̈�
	SOFT_SPRITE_ARC			ssa_push;					///<�ǂݍ��ރL�����N�^�A�p���b�g�f�[�^�̃A�[�J�C�o���i�[�̈�i�X�^�b�N�j
	SOFT_SPRITE_PARAM		ssp;						///<�\�t�g�E�G�A�X�v���C�g�̃p�����[�^

	u8						anm_no;						///<�A�j���[�V�����i���o�[
	u8						anm_seq;					///<�A�j���[�V�����V�[�P���X�i���o�[
	u8						anm_wait;					///<�A�j���[�V�����E�G�C�g
	u8						anm_pat;					///<�A�j���[�V�����p�^�[���i���o�[

	u8						anm_loop[SS_ANM_SEQ_MAX];	///<�A�j���[�V�������[�v�J�E���^
	u8						dummy[2];

	SOFT_SPRITE_MOVE_FUNC	*move;						///<�\�t�g�X�v���C�g����֐�

	SOFT_SPRITE_SHADOW		sss;						///<�\�t�g�X�v���C�g�e�\����
	SOFT_SPRITE_SHADOW		sss_push;					///<�\�t�g�X�v���C�g�e�\���̑ޔ�̈�

	SOFT_SPRITE_ANIME		ssanm[SS_ANM_SEQ_MAX];		///<�A�j���[�V�����f�[�^
};

///<�\���p�}�l�[�W���\���̐錾
struct soft_sprite_manager
{
	SOFT_SPRITE				ss[SOFT_SPRITE_MAX];	///<�z�u�����X�v���C�g���Ǘ�����̈�
	NNSG2dImageProxy		imgp;					///<�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`����VRAM�����󂯎��摜�v���N�V
	NNSG2dImagePaletteProxy	pltp;					///<�\�t�g�E�G�A�X�v���C�g�̃e�N�X�`���p���b�g��VRAM�����󂯎��p���b�g�v���N�V
	int						heap_id;				///<�e�N�X�`����W�J���鎞�Ƀe���|�������m�ۂ���q�[�v�̈��ID

	u32						texture_trans_ofs;		///<�e�N�X�`���̓]����A�h���X�̃I�t�Z�b�g
	u32						texture_trans_size;		///<�e�N�X�`���f�[�^�]���T�C�Y
	u32						palette_trans_ofs;		///<�e�N�X�`���p���b�g�̓]����A�h���X�̃I�t�Z�b�g
	u32						palette_trans_size;		///<�e�N�X�`���p���b�g�f�[�^�]���T�C�Y

	u8						*dest_chr;				///<���z�e�N�X�`���W�J�̈�
	u16						*dest_col;				///<���z�e�N�X�`���p���b�g�W�J�̈�
	u16						*dest_col_temp;			///<���z�e�N�X�`���p���b�g�W�J�̈�

	NNSG2dCharacterData		cd_dest;
	NNSG2dPaletteData		pd_dest;

	u8						cnt;					///<�o�^�����\�t�g�E�G�A�X�v���C�g�̃J�E���^
	u8						texture_trans_req;		///<�e�N�X�`���]�����N�G�X�g�t���O
	u8						palette_trans_req;		///<�p���b�g�]�����N�G�X�g�t���O
	u8						mode;					///<�\�t�g�E�G�A�X�v���C�g�`�惂�[�h

	u32						ss_system_flag;			///<�\�t�g�E�G�A�X�v���C�g�V�X�e���t���O
};

#endif __POKEGRA_DEF_H_
