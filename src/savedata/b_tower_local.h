/**
 *	@file	b_tower_local.h
 *	@brief	�o�g���^���[�@�Z�[�u�f�[�^�\���̒�`
 *	@author	Miyuki Iwasawa
 *	@date	06.04.18	
 */

#ifndef __H_BTOWER_LOCAL_H__
#define __H_BTOWER_LOCAL_H__

#include "savedata/b_tower_def.h"
#include "libdpw/dpw_bt.h"
#include "battle/battle_common.h"
#include "system/gamedata.h"
#include "gflib/gf_date.h"
#include "battle/b_tower_data.h"

/**
 * @brief	�o�g���^���[�v���C�i�s�f�[�^
 *
 * size=20byte
 * ����J�n���ɃN���A�����
*/
struct _BTLTOWER_PLAYWORK{
	u8	itemfix_f	:1;	///<�Œ�A�C�e�����ǂ����̃t���O
	u8	saved_f		:1;	///<�Z�[�u�ς݂��ǂ���
	u8	play_mode	:3;	///<���݂ǂ��Ƀ`�������W����?
	u8	partner		:3;	///<���ݒN�Ƒg��ł��邩?
	u8	dummy;			///<4byte���E�_�~�[

	u8	tower_round;		///<�o�g���^���[�����l�ځH

	u8	wifi_rec_down;		///<���������܂łɓ|���ꂽ�|�P������
	u16	wifi_rec_turn;		///<���������ɂ��������^�[����
	u16	wifi_rec_damage;	///<���������܂łɎ󂯂��_���[�W��

	u8	member_poke[BTOWER_STOCK_MEMBER_MAX];		///<�I�������|�P�����̈ʒu
	u16	trainer_no[BTOWER_STOCK_TRAINER_MAX];		///<�ΐ�g���[�i�[No�ۑ�
	
	u32	play_rnd_seed;	///<�^���[�v���C�ω������_���V�[�h�ۑ��ꏊ

	struct	_B_TOWER_PAREPOKE_PARAM	pare_poke;	///<AI�}���`�̃y�A�̃|�P�����Đ����ɕK�v�ȃp�����[�^
};

/**
 *	@brief	�o�g���^���[�@�X�R�A�f�[�^
 *
 *	size= 20+168+168=356byte
 *	�Q�[����ʂ��ĕۑ�&�Ǘ����Ă����A�v���C���[����
 */
struct _BTLTOWER_SCOREWORK{
	u16	btl_point;	///<�o�g���|�C���g
	u8	wifi_lose;	///<�A���s��J�E���g
	u8	wifi_rank;	///<WiFi�����N

	u32	day_rnd_seed;	///<�^���[�p���t�ω������_���V�[�h�ۑ��ꏊ
	
	union{
		struct{
		u16	silver_get:1;		///<�V���o�[�g���t�B�[�Q�b�g
		u16	gold_get:1;			///<�S�[���h�g���t�B�[�Q�b�g
		u16	silver_ready:1;		///<�V���o�[�Ⴆ�܂�
		u16	gold_ready:1;		///<�S�[���h�Ⴆ�܂�
		u16	wifi_lose_f:1;		///<wifi�A���s��t���O
		u16	wifi_update:1;		///<wifi���уA�b�v���[�h�t���O
		u16	wifi_poke_data:1;	///<wifi�|�P�����f�[�^�X�g�b�N�L��i�V�t���O
		u16	single_poke_data:1;	///<single�|�P�����f�[�^�X�g�b�N�L��i�V�t���O
		u16	single_record:1;	///<�V���O�����R�[�h���풆�t���O
		u16	double_record:1;	///<�_�u�����R�[�h���풆�t���O
		u16	multi_record:1;		///<�}���`���R�[�h���풆�t���O
		u16	cmulti_record:1;	///<�ʐM�}���`���R�[�h���풆�t���O
		u16	wifi_record:1;		///<Wifi���R�[�h���풆�t���O
		u16	copper_get:1;		///<�J�b�p�[�g���t�B�[�Q�b�g
		u16	copper_ready:1;		///<�J�b�p�[�Ⴆ�܂�
		u16	:1;	///<���E�_�~�[
		};
		u16	flags;
	};
	u16	padding;	///<4byte���E�_�~�[
	
	u16	tower_stage[5];		///<�o�g���^���[����

	//WiFi�`�������W�f�[�^
	u16	wifi_score;	///<WiFi����
	//WiFi�|�P�����f�[�^�X�g�b�N
	struct _B_TOWER_POKEMON	wifi_poke[3];
	//�g���[�i�[���[�h�p�V���O���f�[�^�X�g�b�N
	struct _B_TOWER_POKEMON	single_poke[3];
	
};

/**
 *	@brief	�o�g���^���[ �v���C���[���b�Z�[�W�f�[�^
 *
 *	8*4=32byte
 */
struct _BTLTOWER_PLAYER_MSG{
	PMS_DATA	msg[4];	///<�����p���b�Z�[�W
};


/**
 *	@brief	�o�g���^���[ WIFI �v���C���[�f�[�^
 *
 *	56*3+60=228byte
 */
struct _BTLTOWER_WIFI_PLAYER{
	struct _B_TOWER_POKEMON	poke[3];
	
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];	//�g���[�i�[��((PERSON_NAME_SIZE:7)+(EOM_SIZE:1))*(STRCODE:u16)=16

	u8	casette_version;					//�J�Z�b�gversion
	u8	lang_version;						//����o�[�W����
	u8	country_code;						//���R�[�h
	u8	address;							//�Z��ł���Ƃ���

	u32	id_no;								//IDNo	

	u16	leader_word[4];						//���[�_�[���b�Z�[�W

	union{
		struct{
		u8	ngname_f:1;						//NG�l�[���t���O
		u8	gender:1;						//����
		u8			:6;						//���܂�6bit
		};
		u8	flags;
	};
	u8	tr_type;							//�g���[�i�[�^�C�v
	u16	appear_word[4];						//�o�ꃁ�b�Z�[�W	
	u16	win_word[4];						//�������b�Z�[�W	
	u16	lose_word[4];						//�s�ރ��b�Z�[�W	

	u16	result;								//����
};


/**
 *	@brief	�o�g���^���[ WIFI DL�f�[�^
 *
 *	280byte+1596(228*7)byte+1020(34*30)byte=2836byte
 */
struct _BTLTOWER_WIFI_DATA{
	GF_DATE	day;	///<DL�������t4byte
	u8		flags[BTOWER_ROOM_DATA_FLAGS_LEN];	///<DL�ς݃t���O�G���A(2000bit)
	u8		player_data_f;	///<�v���C���[�f�[�^���L�����ǂ����H
	u8		leader_data_f;	///<���[�_�[�f�[�^���L�����ǂ����H

	//DL�f�[�^�̃��[��ID
	u8	player_room;	///<�v���C���[�f�[�^���[��No
	u8	player_rank;	///<�v���C���[�f�[�^���[�������N
	u8	leader_room;	///<���[�_�[�f�[�^���[��No
	u8	leader_rank;	///<���[�_�[�f�[�^���[�������N

	///�v���C���[�f�[�^
	struct _BTLTOWER_WIFI_PLAYER player[BTOWER_STOCK_WIFI_PLAYER_MAX];
	///���[�_�[�f�[�^
	struct _B_TOWER_LEADER_DATA leader[BTOWER_STOCK_WIFI_LEADER_MAX];
};

/**
 *	@brief	�o�g���^���[�@WiFi DL�f�[�^
 */
struct _BTLTOWER_SAVEWORK{
	//�v���C�f�[�^
	struct _BTLTOWER_PLAYWORK	play;
	//�X�R�A�f�[�^
	struct _BTLTOWER_SCOREWORK	score;
	//WiFi �v���C���[���b�Z�[�W�f�[�^
	struct _BTLTOWER_PLAYER_MSG	player_msg;
	//WiFi �f�[�^
	struct _BTLTOWER_WIFI_DATA	wifi;
};

#endif	//__H_BTOWER_LOCAL_H__
