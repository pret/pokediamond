#ifndef _POKEPARAM_H
#define _POKEPARAM_H

#define MONS_NAME_SIZE		10		// �|�P�������̒���
#define PERSON_NAME_SIZE 7

typedef struct
{
	u16	monsno;
	u16 item;
	u32	exp;
	u8	pp_count;
	u8	friend;
	u16	amari;
}PokemonPara1;

typedef struct
{
	u16	waza[4];
	u8	pp[4];								//12�o�C�g
}PokemonPara2;

typedef struct
{
	u8	hp_exp;
	u8	pow_exp;
	u8	def_exp;
	u8	agi_exp;
	u8	spepow_exp;
	u8	spedef_exp;
	u8	style;						//	�������悳
	u8	beautiful;					//	��������
	u8	cute;						//	���킢��
	u8	clever;						//�@��������
	u8	strong;						//	�����܂���
	u8	fur;						//	�щ�	12�o�C�g
}PokemonPara3;
	
typedef struct
{
	u32	pokerus		:8;
	u32	get_place	:8;				//	�߂܂����ꏊ
	u32	get_level	:7;				//	�߂܂������x��
	u32	get_cassette:4;				//	�߂܂����J�Z�b�g�i�J���[�o�[�W�����j
	u32	get_ball	:4;				//	�߂܂����{�[��
	u32	oyasex		:1;				//	�e�̐���
	
	u32	hp_rnd		:5;
	u32	pow_rnd		:5;
	u32	def_rnd		:5;
	u32	agi_rnd		:5;
	u32	spepow_rnd	:5;
	u32	spedef_rnd	:5;
	u32	tamago_flag	:1;				//	0:�^�}�S����Ȃ�1:�^�}�S����
	u32	speabi		:1;				//	����\�́i0:����\��1�@1:����\��2�j

	u32	stylemedal			:3;		//	�������悳�M��
	u32	beautifulmedal		:3;		//	���������M��
	u32	cutemedal			:3;		//	���킢���M��
	u32	clevermedal			:3;		//	���������M��
	u32	strongmedal			:3;		//	�����܂����M��
	u32	champ_ribbon		:1;		//	�`�����v���{��
	u32	winning_ribbon		:1;		//	�E�B�j���O���{��
	u32	victory_ribbon		:1;		//	�r�N�g���[���{��
	u32	bromide_ribbon		:1;		//	�u���}�C�h���{��
	u32	ganba_ribbon		:1;		//	����΃��{��
	u32	marine_ribbon		:1;		//	�}�������{��
	u32	land_ribbon			:1;		//	�����h���{��
	u32	sky_ribbon			:1;		//	�X�J�C���{��
	u32	country_ribbon		:1;		//	�J���g���[���{��
	u32	national_ribbon		:1;		//	�i�V���i�����{��
	u32	earth_ribbon		:1;		//	�A�[�X���{��
	u32	world_ribbon		:1;		//	���[���h���{��
	u32	amari_ribbon		:4;		//	���܂��Ă܂�
	u32	event_get_flag		:1;		//	�C�x���g�Ŕz�z���ꂽ���Ƃ������t���O
}PokemonPara4;

typedef struct
{
	u32	personal_rnd;
	u32	id_no;
	u8	nickname[MONS_NAME_SIZE];			//M_N_S=10
	u8	country_code;						//���R�[�h
	u8	fusei_tamago_flag	:1;				//�f�[�^�����񎞂̃^�}�S�t���O
	u8	poke_exist_flag		:1;				//�|�P�������݃t���O
	u8	egg_exist_flag		:1;				//�^�}�S�Ƃ��Ă̑��݃t���O
	u8	poke_no_move_flag	:1;				//�|�P�������ړ��ł��Ȃ��悤�ɂ��邽�߂̃t���O
											//�i�΃������[�{�b�N�X�p�j
	u8						:4;
	u8	oyaname[PERSON_NAME_SIZE];			//P_N_S=7
	u8	mark;								//�|�P�����ɂ���}�[�N�i�{�b�N�X�j
	u16	checksum;
	u16	amari;								//	���҂̂��߂̗]��̈�
											//32�o�C�g
	u8	paradata[sizeof(PokemonPara1)+
				 sizeof(PokemonPara2)+
				 sizeof(PokemonPara3)+
				 sizeof(PokemonPara4)];
}PokemonPasoParam;

#define BOX_NUM		(14)		//�{�b�N�X�̐�
#define BOX_X_MAX	(6)		///< ���ɉ��̃|�P������\�����邩
#define BOX_Y_MAX	(5)		///< �c�ɉ��̃|�P������\�����邩
#define BOX_POKE_NUM (BOX_X_MAX*BOX_Y_MAX)	///< �P�{�b�N�X�̃|�P�����ő吔
#define PM_TAIHI	(BOX_POKE_NUM*2)//BoxPMStruct�̈�Ԍ��
#define BOXNAME_MAX  (8)
#define	EOM_SIZE			1	// �I���R�[�h�̒���

typedef struct{
	u8 CurrentBoxNo;
	PokemonPasoParam	PPPBox[BOX_NUM][BOX_POKE_NUM];
	u8  BoxName[BOX_NUM][BOXNAME_MAX+EOM_SIZE];
	u8  BGNum[BOX_NUM];
}POKEBOX_SAVE_DATA;

#endif