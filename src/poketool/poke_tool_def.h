
//============================================================================================
/**
 * @file	poke_tool_def.h
 * @bfief	�|�P�����p�����[�^�c�[���S
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#include	"battle/battle_common.h"
#include	"savedata/mail.h"
#include	"savedata/custom_ball.h"

#ifndef __POKE_TOOL_DEF_H_
#define __POKE_TOOL_DEF_H_

struct pokemon_paso_param1
{
	u16	monsno;								//02h	�����X�^�[�i���o�[
	u16 item;								//04h	�����A�C�e���i���o�[
	u32	id_no;								//08h	IDNo
	u32	exp;								//0ch	�o���l
	u8	friend;								//0dh	�Ȃ��x
	u8	speabino;							//0eh	����\��
	u8	mark;								//0fh	�|�P�����ɂ���}�[�N�i�{�b�N�X�j
	u8	country_code;						//10h	���R�[�h
	u8	hp_exp;								//11h	HP�w�͒l
	u8	pow_exp;							//12h	�U���͓w�͒l
	u8	def_exp;							//13h	�h��͓w�͒l
	u8	agi_exp;							//14h	�f�����w�͒l
	u8	spepow_exp;							//15h	���U�w�͒l
	u8	spedef_exp;							//16h	���h�w�͒l
	u8	style;								//17h	�������悳
	u8	beautiful;							//18h	��������
	u8	cute;								//19h	���킢��
	u8	clever;								//1ah	��������
	u8	strong;								//1bh	�����܂���
	u8	fur;								//1ch	�щ�
	u32	sinou_ribbon;						//20h	�V���I�E�n���{���i�r�b�g�t�B�[���h�ŃA�N�Z�X����ƃv���O�����������������̂ŁA�r�b�g�V�t�g�ɕύX�j
//�ȉ�����
#if 0
	u32	sinou_champ_ribbon					:1;	//�V���I�E�`�����v���{��
	u32	sinou_battle_tower_ttwin_first		:1;	//�V���I�E�o�g���^���[�^���[�^�C�N�[������1���
	u32	sinou_battle_tower_ttwin_second		:1;	//�V���I�E�o�g���^���[�^���[�^�C�N�[������1���
	u32	sinou_battle_tower_2vs2_win50		:1;	//�V���I�E�o�g���^���[�^���[�_�u��50�A��
	u32	sinou_battle_tower_aimulti_win50	:1;	//�V���I�E�o�g���^���[�^���[AI�}���`50�A��
	u32	sinou_battle_tower_siomulti_win50	:1;	//�V���I�E�o�g���^���[�^���[�ʐM�}���`50�A��
	u32	sinou_battle_tower_wifi_rank5		:1;	//�V���I�E�o�g���^���[Wifi�����N�T����
	u32	sinou_syakki_ribbon					:1;	//�V���I�E����������{��
	u32	sinou_dokki_ribbon					:1;	//�V���I�E�ǂ������{��
	u32	sinou_syonbo_ribbon					:1;	//�V���I�E�����ڃ��{��

	u32	sinou_ukka_ribbon					:1;	//�V���I�E���������{��
	u32	sinou_sukki_ribbon					:1;	//�V���I�E���������{��
	u32	sinou_gussu_ribbon					:1;	//�V���I�E���������{��
	u32	sinou_nikko_ribbon					:1;	//�V���I�E�ɂ������{��
	u32	sinou_gorgeous_ribbon				:1;	//�V���I�E�S�[�W���X���{��
	u32	sinou_royal_ribbon					:1;	//�V���I�E���C�������{��
	u32	sinou_gorgeousroyal_ribbon			:1;	//�V���I�E�S�[�W���X���C�������{��
	u32	sinou_ashiato_ribbon				:1;	//�V���I�E�������ƃ��{��
	u32	sinou_record_ribbon					:1;	//�V���I�E���R�[�h���{��
	u32	sinou_history_ribbon				:1;	//�V���I�E�q�X�g���[���{��

	u32	sinou_legend_ribbon					:1;	//�V���I�E���W�F���h���{��
	u32	sinou_red_ribbon					:1;	//�V���I�E���b�h���{��
	u32	sinou_green_ribbon					:1;	//�V���I�E�O���[�����{��
	u32	sinou_blue_ribbon					:1;	//�V���I�E�u���[���{��
	u32	sinou_festival_ribbon				:1;	//�V���I�E�t�F�X�e�B�o�����{��
	u32	sinou_carnival_ribbon				:1;	//�V���I�E�J�[�j�o�����{��
	u32	sinou_classic_ribbon				:1;	//�V���I�E�N���V�b�N���{��
	u32	sinou_premiere_ribbon				:1;	//�V���I�E�v���~�A���{��

	u32	sinou_amari_ribbon					:4;	//20h	���܂�
#endif
};
	
struct pokemon_paso_param2
{
	u16	waza[WAZA_TEMOTI_MAX];				//08h	�����Z
	u8	pp[WAZA_TEMOTI_MAX];				//0ch	�����ZPP
	u8	pp_count[WAZA_TEMOTI_MAX];			//10h	�����ZPP_COUNT
	u32	hp_rnd			:5;					//		HP����
	u32	pow_rnd			:5;					//		�U���͗���
	u32	def_rnd			:5;					//		�h��͗���
	u32	agi_rnd			:5;					//		�f��������
	u32	spepow_rnd		:5;					//		���U����
	u32	spedef_rnd		:5;					//		���h����
	u32	tamago_flag		:1;					//		�^�}�S�t���O�i0:�^�}�S����Ȃ��@1:�^�}�S����j
	u32	nickname_flag	:1;					//14h	�j�b�N�l�[�����������ǂ����t���O�i0:���Ă��Ȃ��@1:�����j

	u32	old_ribbon;							//18h	�ߋ���̃��{���n�i�r�b�g�t�B�[���h�ŃA�N�Z�X����ƃv���O�����������������̂ŁA�r�b�g�V�t�g�ɕύX�j
//�ȉ�����
#if 0
	u32	stylemedal_normal		:1;			//	�������悳�M��(�m�[�}��)(AGB�R���e�X�g)
	u32	stylemedal_super		:1;			//	�������悳�M��(�X�[�p�[)(AGB�R���e�X�g)
	u32	stylemedal_hyper		:1;			//	�������悳�M��(�n�C�p�[)(AGB�R���e�X�g)
	u32	stylemedal_master		:1;			//	�������悳�M��(�}�X�^�[)(AGB�R���e�X�g)
	u32	beautifulmedal_normal	:1;			//	���������M��(�m�[�}��)(AGB�R���e�X�g)
	u32	beautifulmedal_super	:1;			//	���������M��(�X�[�p�[)(AGB�R���e�X�g)
	u32	beautifulmedal_hyper	:1;			//	���������M��(�n�C�p�[)(AGB�R���e�X�g)
	u32	beautifulmedal_master	:1;			//	���������M��(�}�X�^�[)(AGB�R���e�X�g)
	u32	cutemedal_normal		:1;			//	���킢���M��(�m�[�}��)(AGB�R���e�X�g)
	u32	cutemedal_super			:1;			//	���킢���M��(�X�[�p�[)(AGB�R���e�X�g)
	u32	cutemedal_hyper			:1;			//	���킢���M��(�n�C�p�[)(AGB�R���e�X�g)
	u32	cutemedal_master		:1;			//	���킢���M��(�}�X�^�[)(AGB�R���e�X�g)
	u32	clevermedal_normal		:1;			//	���������M��(�m�[�}��)(AGB�R���e�X�g)
	u32	clevermedal_super		:1;			//	���������M��(�X�[�p�[)(AGB�R���e�X�g)
	u32	clevermedal_hyper		:1;			//	���������M��(�n�C�p�[)(AGB�R���e�X�g)
	u32	clevermedal_master		:1;			//	���������M��(�}�X�^�[)(AGB�R���e�X�g)
	u32	strongmedal_normal		:1;			//	�����܂����M��(�m�[�}��)(AGB�R���e�X�g)
	u32	strongmedal_super		:1;			//	�����܂����M��(�X�[�p�[)(AGB�R���e�X�g)
	u32	strongmedal_hyper		:1;			//	�����܂����M��(�n�C�p�[)(AGB�R���e�X�g)
	u32	strongmedal_master		:1;			//	�����܂����M��(�}�X�^�[)(AGB�R���e�X�g)

	u32	champ_ribbon	:1;					//		�`�����v���{��
	u32	winning_ribbon	:1;					//		�E�B�j���O���{��
	u32	victory_ribbon	:1;					//		�r�N�g���[���{��
	u32	bromide_ribbon	:1;					//		�u���}�C�h���{��
	u32	ganba_ribbon	:1;					//		����΃��{��
	u32	marine_ribbon	:1;					//		�}�������{��
	u32	land_ribbon		:1;					//		�����h���{��
	u32	sky_ribbon		:1;					//		�X�J�C���{��
	u32	country_ribbon	:1;					//		�J���g���[���{��
	u32	national_ribbon	:1;					//		�i�V���i�����{��
	u32	earth_ribbon	:1;					//		�A�[�X���{��
	u32	world_ribbon	:1;					//		���[���h���{��
#endif

	u8	event_get_flag	:1;					//		�C�x���g�Ŕz�z�������Ƃ������t���O
	u8	sex				:2;					//   	�|�P�����̐���
	u8	form_no			:5;					//19h	�`��i���o�[�i�A���m�[���A�f�I�L�V�X�A�~�m���X�ȂǗp�j
	u8	dummy_p2_1;							//1ah	���܂�
	u16	dummy_p2_2;							//1ch	���܂�
	u32	dummy_p2_3;							//20h	���܂�
};
	
struct pokemon_paso_param3
{
	STRCODE	nickname[MONS_NAME_SIZE+EOM_SIZE];	//16h	�j�b�N�l�[��(MONS_NAME_SIZE=10)+(EOM_SIZE=1)=11
	u8	pref_code;								//18h	�s���{���R�[�h
	u8	get_cassette;							//		�߂܂����J�Z�b�g�o�[�W����
	u64	new_ribbon;								//20h	�V���{���n�i�r�b�g�t�B�[���h�ŃA�N�Z�X����ƃv���O�����������������̂ŁA�r�b�g�V�t�g�ɕύX�j
//�ȉ�����
#if 0
	u32	trial_stylemedal_normal			:1;		//	�������悳�M��(�m�[�}��)(�g���C�A��)
	u32	trial_stylemedal_super			:1;		//	�������悳�M��(�X�[�p�[)(�g���C�A��)
	u32	trial_stylemedal_hyper			:1;		//	�������悳�M��(�n�C�p�[)(�g���C�A��)
	u32	trial_stylemedal_master			:1;		//	�������悳�M��(�}�X�^�[)(�g���C�A��)
	u32	trial_beautifulmedal_normal		:1;		//	���������M��(�m�[�}��)(�g���C�A��)
	u32	trial_beautifulmedal_super		:1;		//	���������M��(�X�[�p�[)(�g���C�A��)
	u32	trial_beautifulmedal_hyper		:1;		//	���������M��(�n�C�p�[)(�g���C�A��)
	u32	trial_beautifulmedal_master		:1;		//	���������M��(�}�X�^�[)(�g���C�A��)
	u32	trial_cutemedal_normal			:1;		//	���킢���M��(�m�[�}��)(�g���C�A��)
	u32	trial_cutemedal_super			:1;		//	���킢���M��(�X�[�p�[)(�g���C�A��)
	u32	trial_cutemedal_hyper			:1;		//	���킢���M��(�n�C�p�[)(�g���C�A��)
	u32	trial_cutemedal_master			:1;		//	���킢���M��(�}�X�^�[)(�g���C�A��)
	u32	trial_clevermedal_normal		:1;		//	���������M��(�m�[�}��)(�g���C�A��)
	u32	trial_clevermedal_super			:1;		//	���������M��(�X�[�p�[)(�g���C�A��)
	u32	trial_clevermedal_hyper			:1;		//	���������M��(�n�C�p�[)(�g���C�A��)
	u32	trial_clevermedal_master		:1;		//	���������M��(�}�X�^�[)(�g���C�A��)
	u32	trial_strongmedal_normal		:1;		//	�����܂����M��(�m�[�}��)(�g���C�A��)
	u32	trial_strongmedal_super			:1;		//	�����܂����M��(�X�[�p�[)(�g���C�A��)
	u32	trial_strongmedal_hyper			:1;		//	�����܂����M��(�n�C�p�[)(�g���C�A��)
	u32	trial_strongmedal_master		:1;		//	�����܂����M��(�}�X�^�[)(�g���C�A��)
	u32 amari_ribbon					:12;	//20h	���܂�
	u32	amari;									//20h	���܂�
#endif
};
	
struct pokemon_paso_param4
{
	STRCODE	oyaname[7+EOM_SIZE];				//10h	�e�̖��O(PERSON_NAME_SIZE=7)+(EOM_SIZE_=1)=8*2(STRCODE=u16)

	u8	get_year;								//11h	�߂܂����N
	u8	get_month;								//12h	�߂܂�����
	u8	get_day;								//13h	�߂܂�����
	u8	birth_year;								//14h	���܂ꂽ�N

	u8	birth_month;							//15h	���܂ꂽ��
	u8	birth_day;								//16h	���܂ꂽ��
	u16	get_place;								//18h	�߂܂����ꏊ

	u16	birth_place;							//1ah	���܂ꂽ�ꏊ
	u8	pokerus;								//1bh	�|�P���X
	u8	get_ball;								//1ch	�߂܂����{�[��

	u8	get_level		:7;						//1dh	�߂܂������x��
	u8	oyasex			:1;						//1dh	�e�̐���
	u8	get_ground_id;							//1eh	�߂܂����ꏊ�̒n�`�A�g���r���[�g�i�~�m�b�`�p�j
	u16	dummy_p4_1;								//20h	���܂�
};

struct pokemon_para_data11
{
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM4	ppp4;
};

struct pokemon_para_data12
{
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM3	ppp3;
};

struct pokemon_para_data13
{
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM4	ppp4;
};

struct pokemon_para_data14
{
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM2	ppp2;
};

struct pokemon_para_data15
{
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM3	ppp3;
};

struct pokemon_para_data16
{
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM2	ppp2;
};

struct pokemon_para_data21
{
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM4	ppp4;
};

struct pokemon_para_data22
{
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM3	ppp3;
};

struct pokemon_para_data23
{
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM4	ppp4;
};

struct pokemon_para_data24
{
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM1	ppp1;
};

struct pokemon_para_data25
{
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM3	ppp3;
};

struct pokemon_para_data26
{
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM1	ppp1;
};

struct pokemon_para_data31
{
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM4	ppp4;
};

struct pokemon_para_data32
{
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM2	ppp2;
};

struct pokemon_para_data33
{
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM4	ppp4;
};

struct pokemon_para_data34
{
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM1	ppp1;
};

struct pokemon_para_data35
{
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM2	ppp2;
};

struct pokemon_para_data36
{
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM1	ppp1;
};

struct pokemon_para_data41
{
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM3	ppp3;
};

struct pokemon_para_data42
{
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM2	ppp2;
};

struct pokemon_para_data43
{
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM3	ppp3;
};

struct pokemon_para_data44
{
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM1	ppp1;
};

struct pokemon_para_data45
{
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM1	ppp1;
	POKEMON_PASO_PARAM2	ppp2;
};

struct pokemon_para_data46
{
	POKEMON_PASO_PARAM4	ppp4;
	POKEMON_PASO_PARAM3	ppp3;
	POKEMON_PASO_PARAM2	ppp2;
	POKEMON_PASO_PARAM1	ppp1;
};

///<�{�b�N�X�|�P�������̍\���̐錾
struct pokemon_paso_param
{
	u32	personal_rnd;							//04h	������
	u16	pp_fast_mode		:1;					//06h	�Í��^�����^�`�F�b�N�T����������񂵂ɂ��āA���������������[�h
	u16	ppp_fast_mode		:1;					//06h	�Í��^�����^�`�F�b�N�T����������񂵂ɂ��āA���������������[�h
	u16	fusei_tamago_flag	:1;					//06h	�_���^�}�S�t���O
	u16						:13;				//06h
	u16	checksum;								//08h	�`�F�b�N�T��

	u8	paradata[sizeof(POKEMON_PASO_PARAM1)+
				 sizeof(POKEMON_PASO_PARAM2)+
				 sizeof(POKEMON_PASO_PARAM3)+
				 sizeof(POKEMON_PASO_PARAM4)];	//88h
};

///<�{�b�N�X�|�P�������ȊO�̍\���̐錾
struct pokemon_calc_param
{
	u32			condition;							//04h	�R���f�B�V����
	u8			level;								//05h	���x��
	u8			cb_id;								//06h	�J�X�^���{�[��ID
	u16			hp;									//08h	HP
	u16			hpmax;								//0ah	HPMAX
	u16			pow;								//0ch	�U����
	u16			def;								//0eh	�h���
	u16			agi;								//10h	�f����
	u16			spepow;								//12h	���U
	u16			spedef;								//14h	���h
	_MAIL_DATA	mail_data;							//3ch	�|�P�����ɂ������郁�[���f�[�^
	CB_CORE		cb_core;							//54h	�J�X�^���{�[��
};

///<�莝���|�P�����̍\���̐錾
struct	pokemon_param
{
	POKEMON_PASO_PARAM	ppp;				//88h
	POKEMON_CALC_PARAM	pcp;				//dch 220
};

///<�|�P�����p�[�\�i���f�[�^�̍\���̐錾
struct	pokemon_personal_data
{
	u8		basic_hp;			//��{�g�o
	u8		basic_pow;			//��{�U����
	u8		basic_def;			//��{�h���
	u8		basic_agi;			//��{�f����

	u8		basic_spepow;		//��{����U����
	u8		basic_spedef;		//��{����h���
	u8		type1;				//�����P
	u8		type2;				//�����Q

	u8		get_rate;			//�ߊl��
	u8		give_exp;			//���^�o���l

	u16		pains_hp	:2;		//���^�w�͒l�g�o
	u16		pains_pow	:2;		//���^�w�͒l�U����
	u16		pains_def	:2;		//���^�w�͒l�h���
	u16		pains_agi	:2;		//���^�w�͒l�f����
	u16		pains_spepow:2;		//���^�w�͒l����U����
	u16		pains_spedef:2;		//���^�w�͒l����h���
	u16					:4;		//���^�w�͒l�\��

	u16		item1;				//�A�C�e���P
	u16		item2;				//�A�C�e���Q

	u8		sex;				//���ʃx�N�g��
	u8		egg_birth;			//�^�}�S�̛z������
	u8		friend;				//�Ȃ��x�����l
	u8		grow;				//�����Ȑ�����

	u8		egg_group1;			//���Â���O���[�v1
	u8		egg_group2;			//���Â���O���[�v2
	u8		speabi1;			//����\�͂P
	u8		speabi2;			//����\�͂Q

	u8		escape;				//�����闦
	u8		color	:7;			//�F�i�}�ӂŎg�p�j
	u8		reverse	:1;			//���]�t���O
	u32		machine1;			//�Z�}�V���t���O�P
	u32		machine2;			//�Z�}�V���t���O�Q
	u32		machine3;			//�Z�}�V���t���O�Q
	u32		machine4;			//�Z�}�V���t���O�Q
};

struct pokemon_shinka_data{
	u16	ShinkaCond;
	u16	ShinkaData;
	u16	ShinkaMons;
};

struct pokemon_shinka_table{
	POKEMON_SHINKA_DATA	psd[7];
};

typedef struct{
	SOFT_SPRITE_ANIME	poke_f;
	SOFT_SPRITE_ANIME	poke_b[3];
	SOFT_SPRITE_ANIME	ssa[10];
}POKE_ANM_TABLE;

#endif __POKE_TOOL_DEF_H_
