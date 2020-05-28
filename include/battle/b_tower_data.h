//============================================================================================
/**
 * @file	b_tower_data.h
 * @bfief	�o�g���^���[�p��`
 * @author	HisashiSogabe/Miyuki Iwasawa
 * @date	06.04.20
 */
//============================================================================================

#ifndef __B_TOWER_H_
#define __B_TOWER_H_

//============================================================================================
/**
 *	�����f�[�^
 */
//============================================================================================

//�o�g���^���[�����p�g���[�i�[�f�[�^�\����
//�g���[�i�[���A��b�f�[�^�́Agmm�ŊǗ��i�g���[�i�[ID����擾�j
typedef struct{
	u16		tr_type;				//�g���[�i�[�^�C�v
	u16		use_poke_cnt;			//�g�p�\�|�P������	
	u16		use_poke_table[1];		//�g�p�\�|�P����INDEX�e�[�u���i�ϒ��j
}B_TOWER_TRAINER_ROM_DATA;

//�o�g���^���[�����p�|�P�����f�[�^�\����
typedef struct{
	u16		mons_no;				//�����X�^�[�i���o�[
	u16		waza[WAZA_TEMOTI_MAX];	//�����Z
	u8		exp_bit;				//�w�͒l�U�蕪���r�b�g
	u8		chr;					//���i
	u16		item_no;				//��������
	u16		dummy;					//4�o�C�g���E�␳
}B_TOWER_POKEMON_ROM_DATA;

//============================================================================================
/**
 *	Wifi�f�[�^
 */
//============================================================================================
/**
 * @biref	�^���[�p�|�P�����f�[�^�^
 * �Z�[�u�f�[�^�Ƃ���肷��̂�savedata/b_tower.h��typedef��`��؂�
 * �s���S�|�C���^�ł����ł���悤�ɂ��Ă���
 */
struct _B_TOWER_POKEMON{
	union{
		struct{
			u16	mons_no:11;	///<�����X�^�[�i���o�[
			u16	form_no:5;	///<�����X�^�[�i���o�[
		};
		u16	mons_param;
	};
	u16	item_no;	///<��������

	u16	waza[WAZA_TEMOTI_MAX];		///<�����Z

	u32	id_no;					///<IDNo
	u32	personal_rnd;			///<������

	union{
		struct{
		u32	hp_rnd		:5;		///<HP�p���[����
		u32	pow_rnd		:5;		///<POW�p���[����
		u32	def_rnd		:5;		///<DEF�p���[����
		u32	agi_rnd		:5;		///<AGI�p���[����
		u32	spepow_rnd	:5;		///<SPEPOW�p���[����
		u32	spedef_rnd	:5;		///<SPEDEF�p���[����
		u32	ngname_f	:1;		///<NG�l�[���t���O
		u32				:1;		//1ch �]��
		};
		u32 power_rnd;
	};

	union{
		struct{
		u8	hp_exp;				///<HP�w�͒l
		u8	pow_exp;			///<POW�w�͒l
		u8	def_exp;			///<DEF�w�͒l
		u8	agi_exp;			///<AGI�w�͒l
		u8	spepow_exp;			///<SPEPOW�w�͒l
		u8	spedef_exp;			///<SPEDEF�w�͒l
		};
		u8 exp[6];
	};
	union{
		struct{
		u8	pp_count0:2;	///<�Z1�|�C���g�A�b�v
		u8	pp_count1:2;	///<�Z2�|�C���g�A�b�v
		u8	pp_count2:2;	///<�Z3�|�C���g�A�b�v
		u8	pp_count3:2;	///<�Z4�|�C���g�A�b�v
		};
		u8 pp_count;
	};

	u8	country_code;			///<���R�[�h

	u8	tokusei;				///<����
	u8	natuki;				///<�Ȃ��x

	///�j�b�N�l�[�� ((MONS_NAME_SIZE:10)+(EOM_SIZE:1))*(STRCODE:u16)=22
	STRCODE	nickname[MONS_NAME_SIZE+EOM_SIZE];
};

//�^���[�g���[�i�[�f�[�^
typedef struct _B_TOWER_TRAINER{
	u32		player_id;	///<�g���[�i�[��ID
	u16		tr_type;	///<�g���[�i�[�^�C�v
	u16		dummy;		///<�_�~�[
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];
	
	u16		appear_word[4];						//�o�ꃁ�b�Z�[�W	
	u16		win_word[4];						//�������b�Z�[�W	
	u16		lose_word[4];						//�s�ރ��b�Z�[�W
}B_TOWER_TRAINER;

//�o�g���^���[�@�ΐ푊��f�[�^�\����
struct _B_TOWER_PARTNER_DATA{
	B_TOWER_TRAINER	bt_trd;			//�g���[�i�[�f�[�^
	struct _B_TOWER_POKEMON	btpwd[4];		//�����|�P�����f�[�^
};


/**
 * @brief	Wifi�o�g���^���[���[�_�[�f�[�^�\����
 * �Z�[�u�f�[�^�Ƃ���肷��̂�savedata/b_tower.h��typedef��`��؂�
 * �s���S�|�C���^�ł����ł���悤�ɂ��Ă���
 */
struct _B_TOWER_LEADER_DATA{
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];	//�g���[�i�[��((PERSON_NAME_SIZE:7)+(EOM_SIZE:1))*(STRCODE:u16)=16

	u8		casette_version;				//�J�Z�b�g�o�[�W����
	u8		lang_version;					//����o�[�W����
	u8		country_code;					//���R�[�h
	u8		address;						//�Z��ł���Ƃ���

	u8		id_no[4];						//!< �v���C���[ID(u32�^�����\���̃T�C�Y��34�ɂ��邽��u8[4]�ɂ��Ă���)
//	u32		id_no;							//IDNo	

	u16		leader_word[4];					//���[�_�[���b�Z�[�W

	union{
		struct{
			u8	ngname_f:1;	//NG�l�[���t���O(on�Ȃ�NG�l�[��)
			u8	gender	:1;	//����
			u8			:6;	//���܂�6bit
		};
		u8	flags;
	};
	u8	padding;							///<�p�f�B���O
};

/**
 *	@biref	�^���[AI�}���`�y�A�̕ۑ����K�v�ȃ|�P�����p�����[�^
 *
 * �Z�[�u�f�[�^�Ƃ���肷��̂�savedata/b_tower.h��typedef��`��؂�
 * �s���S�|�C���^�ł����ł���悤�ɂ��Ă���
 */
struct _B_TOWER_PAREPOKE_PARAM{
	u32	poke_id;	///<�|�P������id�ۑ�
	u16	poke_no[BTOWER_STOCK_PAREPOKE_MAX];	///<�^���[�f�[�^���|�P�����f�[�^�Q��index0-999
	u32	poke_rnd[BTOWER_STOCK_PAREPOKE_MAX];	///<�|�P�����̌������ۑ�
};

#endif __B_TOWER_H_
