
//============================================================================================
/**
 * @file	poke_tool.h
 * @bfief	�|�P�����p�����[�^�c�[���S
 * @author	HisashiSogabe
 * @date	05.05.31
 */
//============================================================================================

#ifndef	__POKE_TOOL_H_
#define	__POKE_TOOL_H_

//	PokeGraArcDataGet�̈�����define��`�iPOKEMON_PARAM��ID_PARA_sex�ɓ����Ă��鐫�ʒ�`�j
#define	PARA_MALE		(0)		///<�I�X
#define	PARA_FEMALE		(1)		///<���X
#define	PARA_UNK		(2)		///<���ʂȂ�

#define	PARA_BACK		(0)		///<�w��
#define	PARA_FRONT		(2)		///<����

#define	PARA_NORMAL		(0)		///<�m�[�}���J���[
#define	PARA_RARE		(1)		///<���A�J���[

//PokePrgAnmDataSet�Ɋւ����`
#define	PARA_HFLIP_OFF	(0)		///<HFLIP�Ȃ�
#define	PARA_HFLIP_ON	(1)		///<HFLIP����

//�w�͒l�Ɋւ����`
#define	PARA_EXP_TOTAL_MAX	(510)		//6�̃p�����[�^�̍��v�l��MAX
#define	PARA_EXP_ITEM_MAX	(100)		//�A�C�e���ŏ㏸�ł�����E�l
#define	PARA_EXP_MAX		(255)		//6�̃p�����[�^��MAX

// �}�[�L���O�Ɋւ����`
#define POKEPARA_MARKING_ELEMS_MAX	(6)	///< �}�[�L���O�Ɏg�p����L���̑���

// �Z�o���e�[�u���Ɋւ����`
#define LEVELUPWAZA_OBOE_MAX	( 44     )	///<�i�Z20�{�I�[�R�[�h:1+4�o�C�g���E�␳:1�j* 2�o�C�g
#define LEVELUPWAZA_OBOE_END	( 0xffff )
#define LEVELUPWAZA_LEVEL_MASK  ( 0xfe00 )
#define LEVELUPWAZA_WAZA_MASK   ( 0x01ff )
#define LEVELUPWAZA_LEVEL_SHIFT (      9 )

//PokeItemSet��range������`
#define	ITEM_RANGE_NORMAL		(0)	//�ʏ�m��
#define	ITEM_RANGE_HUKUGAN		(1)	//�����ӂ�������ʊm��

//�o�g���^���[�ŏ����ɎQ���ł��Ȃ��|�P�����̎�ސ�
#define BTOWER_EXPOKE_NUM	(18)

//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_

#include	"system/softsprite.h"
#include	"savedata/mystatus.h"

//�|�P�����v���O�����A�j��
typedef struct POKE_ANIME_SYS_tag * POKE_ANM_SYS_PTR;
typedef struct PERAPVOICE PERAPVOICE;
typedef struct _POKEPARTY POKEPARTY;

//	������֘A�̒�����`
#include "system/gamedata.h"

//�p�[�\�i���f�[�^�̐F��`
enum{
	COLOR_RED=0,		//��
	COLOR_BLUE,			//��
	COLOR_YELLOW,		//��
	COLOR_GREEN,		//��
	COLOR_BLACK,		//��
	COLOR_BROWN,		//��
	COLOR_PERPLE,		//��
	COLOR_GRAY,			//�D
	COLOR_WHITE,		//��
	COLOR_PINK,			//��
};

//�Ȃ��v�Z
enum{
	FRIEND_LEVELUP=0,		//���x���A�b�v
	FRIEND_PARAEXP_ITEM,	//�w�͒l�A�C�e��	
	FRIEND_BATTLE_ITEM,		//�퓬���A�C�e��
	FRIEND_BOSS_BATTLE,		//�{�X�퓬	
	FRIEND_WAZA_MACHINE,	//�Z�}�V���g�p
	FRIEND_TSUREARUKI,		//�A�����	
	FRIEND_HINSHI,			//�m��
	FRIEND_DOKU_HINSHI,		//�łɂ��m��
	FRIEND_LEVEL30_HINSHI,	//���x����30�ȏ�̕m��
	FRIEND_CONTEST_VICTORY,	//�R���e�X�g�D��
};

///<�{�b�N�X�|�P�������̍\����
typedef struct pokemon_paso_param POKEMON_PASO_PARAM;
typedef struct pokemon_paso_param1 POKEMON_PASO_PARAM1;
typedef struct pokemon_paso_param2 POKEMON_PASO_PARAM2;
typedef struct pokemon_paso_param3 POKEMON_PASO_PARAM3;
typedef struct pokemon_paso_param4 POKEMON_PASO_PARAM4;

typedef struct pokemon_para_data11 POKEMON_PARA_DATA11;
typedef struct pokemon_para_data12 POKEMON_PARA_DATA12;
typedef struct pokemon_para_data13 POKEMON_PARA_DATA13;
typedef struct pokemon_para_data14 POKEMON_PARA_DATA14;
typedef struct pokemon_para_data15 POKEMON_PARA_DATA15;
typedef struct pokemon_para_data16 POKEMON_PARA_DATA16;
typedef struct pokemon_para_data21 POKEMON_PARA_DATA21;
typedef struct pokemon_para_data22 POKEMON_PARA_DATA22;
typedef struct pokemon_para_data23 POKEMON_PARA_DATA23;
typedef struct pokemon_para_data24 POKEMON_PARA_DATA24;
typedef struct pokemon_para_data25 POKEMON_PARA_DATA25;
typedef struct pokemon_para_data26 POKEMON_PARA_DATA26;
typedef struct pokemon_para_data31 POKEMON_PARA_DATA31;
typedef struct pokemon_para_data32 POKEMON_PARA_DATA32;
typedef struct pokemon_para_data33 POKEMON_PARA_DATA33;
typedef struct pokemon_para_data34 POKEMON_PARA_DATA34;
typedef struct pokemon_para_data35 POKEMON_PARA_DATA35;
typedef struct pokemon_para_data36 POKEMON_PARA_DATA36;
typedef struct pokemon_para_data41 POKEMON_PARA_DATA41;
typedef struct pokemon_para_data42 POKEMON_PARA_DATA42;
typedef struct pokemon_para_data43 POKEMON_PARA_DATA43;
typedef struct pokemon_para_data44 POKEMON_PARA_DATA44;
typedef struct pokemon_para_data45 POKEMON_PARA_DATA45;
typedef struct pokemon_para_data46 POKEMON_PARA_DATA46;

///<�{�b�N�X�|�P�������ȊO�̍\����
typedef struct pokemon_calc_param POKEMON_CALC_PARAM;

///<�莝���|�P�����̍\����
typedef struct pokemon_param POKEMON_PARAM;

///<�|�P�����p�����[�^�f�[�^�擾�̂��߂̃C���f�b�N�X
enum{
	ID_PARA_personal_rnd=0,						//������
	ID_PARA_pp_fast_mode,						//
	ID_PARA_ppp_fast_mode,						//
	ID_PARA_fusei_tamago_flag,					//�_���^�}�S�t���O
	ID_PARA_checksum,							//�`�F�b�N�T��

	ID_PARA_monsno,								//�����X�^�[�i���o�[
	ID_PARA_item,								//�����A�C�e���i���o�[
	ID_PARA_id_no,								//IDNo
	ID_PARA_exp,								//�o���l
	ID_PARA_friend,								//�Ȃ��x
	ID_PARA_speabino,							//����\��
	ID_PARA_mark,								//�|�P�����ɂ���}�[�N�i�{�b�N�X�j
	ID_PARA_country_code,						//���R�[�h
	ID_PARA_hp_exp,								//HP�w�͒l
	ID_PARA_pow_exp,							//�U���͓w�͒l
	ID_PARA_def_exp,							//�h��͓w�͒l
	ID_PARA_agi_exp,							//�f�����w�͒l
	ID_PARA_spepow_exp,							//���U�w�͒l
	ID_PARA_spedef_exp,							//���h�w�͒l
	ID_PARA_style,								//�������悳
	ID_PARA_beautiful,							//��������
	ID_PARA_cute,								//���킢��
	ID_PARA_clever,								//��������
	ID_PARA_strong,								//�����܂���
	ID_PARA_fur,								//�щ�
	ID_PARA_sinou_champ_ribbon,					//�V���I�E�`�����v���{��
	ID_PARA_sinou_battle_tower_ttwin_first,		//�V���I�E�o�g���^���[�^���[�^�C�N�[������1���
	ID_PARA_sinou_battle_tower_ttwin_second,	//�V���I�E�o�g���^���[�^���[�^�C�N�[������2���
	ID_PARA_sinou_battle_tower_2vs2_win50,		//�V���I�E�o�g���^���[�^���[�_�u��50�A��
	ID_PARA_sinou_battle_tower_aimulti_win50,	//�V���I�E�o�g���^���[�^���[AI�}���`50�A��
	ID_PARA_sinou_battle_tower_siomulti_win50,	//�V���I�E�o�g���^���[�^���[�ʐM�}���`50�A��
	ID_PARA_sinou_battle_tower_wifi_rank5,		//�V���I�E�o�g���^���[Wifi�����N�T����
	ID_PARA_sinou_syakki_ribbon,				//�V���I�E����������{��
	ID_PARA_sinou_dokki_ribbon,					//�V���I�E�ǂ������{��
	ID_PARA_sinou_syonbo_ribbon,				//�V���I�E�����ڃ��{��
	ID_PARA_sinou_ukka_ribbon,					//�V���I�E���������{��
	ID_PARA_sinou_sukki_ribbon,					//�V���I�E���������{��
	ID_PARA_sinou_gussu_ribbon,					//�V���I�E���������{��
	ID_PARA_sinou_nikko_ribbon,					//�V���I�E�ɂ������{��
	ID_PARA_sinou_gorgeous_ribbon,				//�V���I�E�S�[�W���X���{��
	ID_PARA_sinou_royal_ribbon,					//�V���I�E���C�������{��
	ID_PARA_sinou_gorgeousroyal_ribbon,			//�V���I�E�S�[�W���X���C�������{��
	ID_PARA_sinou_ashiato_ribbon,				//�V���I�E�������ƃ��{��
	ID_PARA_sinou_record_ribbon,				//�V���I�E���R�[�h���{��
	ID_PARA_sinou_history_ribbon,				//�V���I�E�q�X�g���[���{��
	ID_PARA_sinou_legend_ribbon,				//�V���I�E���W�F���h���{��
	ID_PARA_sinou_red_ribbon,					//�V���I�E���b�h���{��
	ID_PARA_sinou_green_ribbon,					//�V���I�E�O���[�����{��
	ID_PARA_sinou_blue_ribbon,					//�V���I�E�u���[���{��
	ID_PARA_sinou_festival_ribbon,				//�V���I�E�t�F�X�e�B�o�����{��
	ID_PARA_sinou_carnival_ribbon,				//�V���I�E�J�[�j�o�����{��
	ID_PARA_sinou_classic_ribbon,				//�V���I�E�N���V�b�N���{��
	ID_PARA_sinou_premiere_ribbon,				//�V���I�E�v���~�A���{��
	ID_PARA_sinou_amari_ribbon,					//���܂�

	ID_PARA_waza1,								//�����Z1
	ID_PARA_waza2,								//�����Z2
	ID_PARA_waza3,								//�����Z3
	ID_PARA_waza4,								//�����Z4
	ID_PARA_pp1,								//�����ZPP1
	ID_PARA_pp2,								//�����ZPP2
	ID_PARA_pp3,								//�����ZPP3
	ID_PARA_pp4,								//�����ZPP4
	ID_PARA_pp_count1,							//�����ZPP_COUNT1
	ID_PARA_pp_count2,							//�����ZPP_COUNT2
	ID_PARA_pp_count3,							//�����ZPP_COUNT3
	ID_PARA_pp_count4,							//�����ZPP_COUNT4
	ID_PARA_pp_max1,							//�����ZPPMAX1
	ID_PARA_pp_max2,							//�����ZPPMAX2
	ID_PARA_pp_max3,							//�����ZPPMAX3
	ID_PARA_pp_max4,							//�����ZPPMAX4
	ID_PARA_hp_rnd,								//HP����
	ID_PARA_pow_rnd,							//�U���͗���
	ID_PARA_def_rnd,							//�h��͗���
	ID_PARA_agi_rnd,							//�f��������
	ID_PARA_spepow_rnd,							//���U����
	ID_PARA_spedef_rnd,							//���h����
	ID_PARA_tamago_flag,						//�^�}�S�t���O
	ID_PARA_nickname_flag,						//�j�b�N�l�[�����������ǂ����t���O
	ID_PARA_stylemedal_normal,					//�������悳�M��(�m�[�}��)AGB�R���e�X�g
	ID_PARA_stylemedal_super,					//�������悳�M��(�X�[�p�[)AGB�R���e�X�g
	ID_PARA_stylemedal_hyper,					//�������悳�M��(�n�C�p�[)AGB�R���e�X�g
	ID_PARA_stylemedal_master,					//�������悳�M��(�}�X�^�[)AGB�R���e�X�g
	ID_PARA_beautifulmedal_normal,				//���������M��(�m�[�}��)AGB�R���e�X�g
	ID_PARA_beautifulmedal_super,				//���������M��(�X�[�p�[)AGB�R���e�X�g
	ID_PARA_beautifulmedal_hyper,				//���������M��(�n�C�p�[)AGB�R���e�X�g
	ID_PARA_beautifulmedal_master,				//���������M��(�}�X�^�[)AGB�R���e�X�g
	ID_PARA_cutemedal_normal,					//���킢���M��(�m�[�}��)AGB�R���e�X�g
	ID_PARA_cutemedal_super,					//���킢���M��(�X�[�p�[)AGB�R���e�X�g
	ID_PARA_cutemedal_hyper,					//���킢���M��(�n�C�p�[)AGB�R���e�X�g
	ID_PARA_cutemedal_master,					//���킢���M��(�}�X�^�[)AGB�R���e�X�g
	ID_PARA_clevermedal_normal,					//���������M��(�m�[�}��)AGB�R���e�X�g
	ID_PARA_clevermedal_super,					//���������M��(�X�[�p�[)AGB�R���e�X�g
	ID_PARA_clevermedal_hyper,					//���������M��(�n�C�p�[)AGB�R���e�X�g
	ID_PARA_clevermedal_master,					//���������M��(�}�X�^�[)AGB�R���e�X�g
	ID_PARA_strongmedal_normal,					//�����܂����M��(�m�[�}��)AGB�R���e�X�g
	ID_PARA_strongmedal_super,					//�����܂����M��(�X�[�p�[)AGB�R���e�X�g
	ID_PARA_strongmedal_hyper,					//�����܂����M��(�n�C�p�[)AGB�R���e�X�g
	ID_PARA_strongmedal_master,					//�����܂����M��(�}�X�^�[)AGB�R���e�X�g
	ID_PARA_champ_ribbon,						//�`�����v���{��
	ID_PARA_winning_ribbon,						//�E�B�j���O���{��
	ID_PARA_victory_ribbon,						//�r�N�g���[���{��
	ID_PARA_bromide_ribbon,						//�u���}�C�h���{��
	ID_PARA_ganba_ribbon,						//����΃��{��
	ID_PARA_marine_ribbon,						//�}�������{��
	ID_PARA_land_ribbon,						//�����h���{��
	ID_PARA_sky_ribbon,							//�X�J�C���{��
	ID_PARA_country_ribbon,						//�J���g���[���{��
	ID_PARA_national_ribbon,					//�i�V���i�����{��
	ID_PARA_earth_ribbon,						//�A�[�X���{��
	ID_PARA_world_ribbon,						//���[���h���{��
	ID_PARA_event_get_flag,						//�C�x���g�Ŕz�z���ꂽ���Ƃ������t���O
	ID_PARA_sex,								//����
	ID_PARA_form_no,							//�`��i���o�[�i�A���m�[���A�f�I�L�V�X�A�~�m���X�ȂǗp�j
	ID_PARA_dummy_p2_1,							//���܂�
	ID_PARA_dummy_p2_2,							//���܂�
	ID_PARA_dummy_p2_3,							//���܂�

	ID_PARA_nickname,							//�j�b�N�l�[��
	ID_PARA_nickname_code_flag,					//�j�b�N�l�[���iSTRCODE�g�p,nickname_flag���I���ɂ���j
	ID_PARA_nickname_buf,						//�j�b�N�l�[���iSTRBUF�g�p�j
	ID_PARA_nickname_buf_flag,					//�j�b�N�l�[���iSTRBUF�g�p,nickname_flag���I���ɂ���j
	ID_PARA_pref_code,							//�s���{���R�[�h
	ID_PARA_get_cassette,						//�߂܂����J�Z�b�g�i�J���[�o�[�W�����j
	ID_PARA_trial_stylemedal_normal,			//�������悳�M��(�m�[�}��)�g���C�A��
	ID_PARA_trial_stylemedal_super,				//�������悳�M��(�X�[�p�[)�g���C�A��
	ID_PARA_trial_stylemedal_hyper,				//�������悳�M��(�n�C�p�[)�g���C�A��
	ID_PARA_trial_stylemedal_master,			//�������悳�M��(�}�X�^�[)�g���C�A��
	ID_PARA_trial_beautifulmedal_normal,		//���������M��(�m�[�}��)�g���C�A��
	ID_PARA_trial_beautifulmedal_super,			//���������M��(�X�[�p�[)�g���C�A��
	ID_PARA_trial_beautifulmedal_hyper,			//���������M��(�n�C�p�[)�g���C�A��
	ID_PARA_trial_beautifulmedal_master,		//���������M��(�}�X�^�[)�g���C�A��
	ID_PARA_trial_cutemedal_normal,				//���킢���M��(�m�[�}��)�g���C�A��
	ID_PARA_trial_cutemedal_super,				//���킢���M��(�X�[�p�[)�g���C�A��
	ID_PARA_trial_cutemedal_hyper,				//���킢���M��(�n�C�p�[)�g���C�A��
	ID_PARA_trial_cutemedal_master,				//���킢���M��(�}�X�^�[)�g���C�A��
	ID_PARA_trial_clevermedal_normal,			//���������M��(�m�[�}��)�g���C�A��
	ID_PARA_trial_clevermedal_super,			//���������M��(�X�[�p�[)�g���C�A��
	ID_PARA_trial_clevermedal_hyper,			//���������M��(�n�C�p�[)�g���C�A��
	ID_PARA_trial_clevermedal_master,			//���������M��(�}�X�^�[)�g���C�A��
	ID_PARA_trial_strongmedal_normal,			//�����܂����M��(�m�[�}��)�g���C�A��
	ID_PARA_trial_strongmedal_super,			//�����܂����M��(�X�[�p�[)�g���C�A��
	ID_PARA_trial_strongmedal_hyper,			//�����܂����M��(�n�C�p�[)�g���C�A��
	ID_PARA_trial_strongmedal_master,			//�����܂����M��(�}�X�^�[)�g���C�A��
	ID_PARA_amari_ribbon,						//�]�胊�{��

	ID_PARA_oyaname,							//�e�̖��O
	ID_PARA_oyaname_buf,						//�e�̖��O�iSTRBUF�g�p�j
	ID_PARA_get_year,							//�߂܂����N
	ID_PARA_get_month,							//�߂܂�����
	ID_PARA_get_day,							//�߂܂�����
	ID_PARA_birth_year,							//���܂ꂽ�N
	ID_PARA_birth_month,						//���܂ꂽ��
	ID_PARA_birth_day,							//���܂ꂽ��
	ID_PARA_get_place,							//�߂܂����ꏊ
	ID_PARA_birth_place,						//���܂ꂽ�ꏊ
	ID_PARA_pokerus,							//�|�P���X
	ID_PARA_get_ball,							//�߂܂����{�[��
	ID_PARA_get_level,							//�߂܂������x��
	ID_PARA_oyasex,								//�e�̐���
	ID_PARA_get_ground_id,						//�߂܂����ꏊ�̒n�`�A�g���r���[�g�i�~�m�b�`�p�j
	ID_PARA_dummy_p4_1,							//���܂�

	ID_PARA_condition,							//�R���f�B�V����
	ID_PARA_level,								//���x��
	ID_PARA_cb_id,								//�J�X�^���{�[��ID
	ID_PARA_hp,									//HP
	ID_PARA_hpmax,								//HPMAX
	ID_PARA_pow,								//�U����
	ID_PARA_def,								//�h���
	ID_PARA_agi,								//�f����
	ID_PARA_spepow,								//���U
	ID_PARA_spedef,								//���h
	ID_PARA_mail_data,							//���[���f�[�^
	ID_PARA_cb_core,							//�J�X�^���{�[���f�[�^
	
	ID_PARA_poke_exist,							//�|�P�������݃t���O
	ID_PARA_tamago_exist,						//�^�}�S���݃t���O

	ID_PARA_monsno_egg,							//�^�}�S���ǂ����������Ƀ`�F�b�N

	ID_PARA_power_rnd,							//�p���[������u32�ň���
	ID_PARA_nidoran_nickname,					//�����X�^�[�i���o�[���j�h�����̎���nickname_flag�������Ă��邩�`�F�b�N

	ID_PARA_type1,								//�|�P�����̃^�C�v�P���擾�i�A�E�X�A�}���`�^�C�v�`�F�b�N������j
	ID_PARA_type2,								//�|�P�����̃^�C�v�Q���擾�i�A�E�X�A�}���`�^�C�v�`�F�b�N������j

	ID_PARA_default_name,						//�|�P�����̃f�t�H���g��

	ID_PARA_end									//�p�����[�^��ǉ�����Ƃ��́A���������ɒǉ�
};

///<�|�P�����p�[�\�i���f�[�^�̍\����
typedef struct pokemon_personal_data POKEMON_PERSONAL_DATA;

///<�|�P�����p�[�\�i���f�[�^�擾�̂��߂̃C���f�b�N�X
enum{
	ID_PER_basic_hp=0,			//��{�g�o
	ID_PER_basic_pow,			//��{�U����
	ID_PER_basic_def,			//��{�h���
	ID_PER_basic_agi,			//��{�f����
	ID_PER_basic_spepow,		//��{����U����
	ID_PER_basic_spedef,		//��{����h���
	ID_PER_type1,				//�����P
	ID_PER_type2,				//�����Q
	ID_PER_get_rate,			//�ߊl��
	ID_PER_give_exp,			//���^�o���l
	ID_PER_pains_hp,			//���^�w�͒l�g�o
	ID_PER_pains_pow,			//���^�w�͒l�U����
	ID_PER_pains_def,			//���^�w�͒l�h���
	ID_PER_pains_agi,			//���^�w�͒l�f����
	ID_PER_pains_spepow,		//���^�w�͒l����U����
	ID_PER_pains_spedef,		//���^�w�͒l����h���
	ID_PER_item1,				//�A�C�e���P
	ID_PER_item2,				//�A�C�e���Q
	ID_PER_sex,					//���ʃx�N�g��
	ID_PER_egg_birth,			//�^�}�S�̛z������
	ID_PER_friend,				//�Ȃ��x�����l
	ID_PER_grow,				//�����Ȑ�����
	ID_PER_egg_group1,			//���Â���O���[�v1
	ID_PER_egg_group2,			//���Â���O���[�v2
	ID_PER_speabi1,				//����\�͂P
	ID_PER_speabi2,				//����\�͂Q
	ID_PER_escape,				//�����闦
	ID_PER_color,				//�F�i�}�ӂŎg�p�j
	ID_PER_reverse,				//���]�t���O
	ID_PER_machine1,			//�Z�}�V���t���O�P
	ID_PER_machine2,			//�Z�}�V���t���O�Q
	ID_PER_machine3,			//�Z�}�V���t���O�R
	ID_PER_machine4				//�Z�}�V���t���O�S
};

//	�|�P�����̐��ʒ�`�i�p�[�\�i����̃I�X���X�䗦�j(1�`253�ŃI�X���X�̔䗦���ς��j
#define	MONS_MALE		(0)				///<�I�X�̂�
#define	MONS_FEMALE		(254)			///<���X�̂�
#define	MONS_UNKNOWN	(255)			///<���ʂȂ�

#define	POW_RND			(32)		//PokeParaSet���g���Ƃ��Ƀp���[�����������_���łƂ邽�߂̒l
#define	RND_NO_SET		(0)			//PokeParaSet���g���Ƃ��Ɍ������������_���ŃZ�b�g���邽�߂̒l
#define	RND_SET			(1)			//PokeParaSet���g���Ƃ��Ɍ��������Œ�l�ŃZ�b�g���邽�߂̒l
#define	ID_NO_SET		(0)			//PokeParaSet���g���Ƃ���ID�������_���ŃZ�b�g���邽�߂̒l
#define	ID_SET			(1)			//PokeParaSet���g���Ƃ���ID���Œ�l�ŃZ�b�g���邽�߂̒l
#define	ID_NO_RARE		(2)			//PokeParaSet���g���Ƃ���ID���������Ƃ̑g�ݍ��킹�Ń��A���o�Ȃ��悤�ɂ���̒l
#define	NO_WAZA_SET		(0xffff)	//�Z�̃Z�b�g���ł��Ȃ������Ƃ��̕Ԃ�l
#define	SAME_WAZA_SET	(0xfffe)	//���łɊo���Ă����Z�̂Ƃ��̕Ԃ�l

///<�|�P�����i���f�[�^�̍\����
typedef struct pokemon_shinka_data POKEMON_SHINKA_DATA;

typedef struct pokemon_shinka_table POKEMON_SHINKA_TABLE;

enum{
	ID_EVO_Cond=0,
	ID_EVO_Data,
	ID_EVO_Mons
};

//�|�P�����p�����[�^�擾�n�̒�`
enum{
	ID_POKEPARADATA11=0,	//0
	ID_POKEPARADATA12,		//1
	ID_POKEPARADATA13,		//2
	ID_POKEPARADATA14,		//3
	ID_POKEPARADATA15,		//4
	ID_POKEPARADATA16,		//5
	ID_POKEPARADATA21,		//6
	ID_POKEPARADATA22,		//7
	ID_POKEPARADATA23,		//8
	ID_POKEPARADATA24,		//9
	ID_POKEPARADATA25,		//10
	ID_POKEPARADATA26,		//11
	ID_POKEPARADATA31,		//12
	ID_POKEPARADATA32,		//13
	ID_POKEPARADATA33,		//14
	ID_POKEPARADATA34,		//15
	ID_POKEPARADATA35,		//16
	ID_POKEPARADATA36,		//17
	ID_POKEPARADATA41,		//18
	ID_POKEPARADATA42,		//19
	ID_POKEPARADATA43,		//20
	ID_POKEPARADATA44,		//21
	ID_POKEPARADATA45,		//22
	ID_POKEPARADATA46,		//23

	ID_POKEPARADATA51,		//24
	ID_POKEPARADATA52,		//25
	ID_POKEPARADATA53,		//26
	ID_POKEPARADATA54,		//27
	ID_POKEPARADATA55,		//28
	ID_POKEPARADATA56,		//29

	ID_POKEPARADATA61,		//30
	ID_POKEPARADATA62,		//31
};

enum{
	ID_POKEPARA1=0,
	ID_POKEPARA2,
	ID_POKEPARA3,
	ID_POKEPARA4,
};

enum{
	UNK_A=0,
	UNK_B,
	UNK_C,
	UNK_D,
	UNK_E,
	UNK_F,
	UNK_G,
	UNK_H,
	UNK_I,
	UNK_J,
	UNK_K,
	UNK_L,
	UNK_M,
	UNK_N,
	UNK_O,
	UNK_P,
	UNK_Q,
	UNK_R,
	UNK_S,
	UNK_T,
	UNK_U,
	UNK_V,
	UNK_W,
	UNK_X,
	UNK_Y,
	UNK_Z,
	UNK_ENC,
	UNK_QUE,
	UNK_END
};

//extern�錾
extern	void	PokeParaInit(POKEMON_PARAM *pp);
extern	void	PokePasoParaInit(POKEMON_PASO_PARAM *ppp);

extern	int		PokemonParam_GetWorkSize(void);
extern	POKEMON_PARAM	*PokemonParam_AllocWork(u32 heapID);

extern	BOOL	PokeParaFastModeOn(POKEMON_PARAM *pp);
extern	BOOL	PokeParaFastModeOff(POKEMON_PARAM *pp,BOOL flag);
extern	BOOL	PokePasoParaFastModeOn(POKEMON_PASO_PARAM *ppp);
extern	BOOL	PokePasoParaFastModeOff(POKEMON_PASO_PARAM *ppp,BOOL flag);

extern	void	PokeParaSet(POKEMON_PARAM *pp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id);
extern	void	PokePasoParaSet(POKEMON_PASO_PARAM *ppp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id);
extern	void	PokeParaSetChr(POKEMON_PARAM *,u16,u8,u8,u8);
extern	void	PokeParaSetSexChr(POKEMON_PARAM *,u16,u8,u8,u8,u8,u8);
extern	u32		PokeParaSexChrRndGet(u16 mons_no,u8 sex,u8 chr);
extern	void	PokeParaSetPowRnd(POKEMON_PARAM *,u16,u8,u32,u32);
extern	void	PokeParaSetPowRndBuf(POKEMON_PARAM *,u16,u8,u8*,u32);
extern	void	PokeParaSetParaExp(POKEMON_PARAM *,u16,u8,u8,u8);
extern	void	PokeParaSetBattleFrontier(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 chr,u8 pow,u8 expbit,u32 id);
extern	void	PokeParaCalc(POKEMON_PARAM *pp);
extern	void	PokeParaCalcLevelUp(POKEMON_PARAM *pp);

extern	u32		PokeParaGet(POKEMON_PARAM *pp,int id,void *buf);
//extern	u32		PokeParaGetFast(POKEMON_PARAM *pp,int id,void *buf);
extern	u32		PokePasoParaGet(POKEMON_PASO_PARAM *ppp,int id,void *buf);
//extern	u32		PokePasoParaGetFast(POKEMON_PASO_PARAM *ppp,int id,void *buf);
extern	void	PokeParaPut(POKEMON_PARAM *pp,int id,const void *buf);
//extern	void	PokeParaPutFast(POKEMON_PARAM *pp,int id,const void *buf);
extern	void	PokePasoParaPut(POKEMON_PASO_PARAM *ppp,int id,const void *buf);
//extern	void	PokePasoParaPutFast(POKEMON_PASO_PARAM *ppp,int id,const void *buf);
extern	void	PokeParaAdd(POKEMON_PARAM *pp,int id,int value);
//extern	void	PokeParaAddFast(POKEMON_PARAM *pp,int id,int value);
extern	void	PokePasoParaAdd(POKEMON_PASO_PARAM *ppp,int id,int value);
//extern	void	PokePasoParaAddFast(POKEMON_PASO_PARAM *ppp,int id,int value);

extern	u32		PokeParaPersonalParaGet(POKEMON_PARAM *pp,int para);
extern	u32		PokePasoParaPersonalParaGet(POKEMON_PASO_PARAM *ppp,int para);
extern	u32		PokeFormNoPersonalParaGet(int mons_no,int form_no,int para);

extern	u32		PokePersonalParaGet(int mons_no,int para);

extern POKEMON_PERSONAL_DATA *PokePersonalPara_Open( int mons_no, int HeapID );
extern u32      PokePersonalPara_Get( POKEMON_PERSONAL_DATA *ppd, int para );
extern void     PokePersonalPara_Close( POKEMON_PERSONAL_DATA *ppd );

extern	u8		PokeParaNextLevelExpRatioGet(POKEMON_PARAM *pp);

extern	u32		PokeParaNextLevelExpGet(POKEMON_PARAM *pp);
extern	u32		PokePasoParaNextLevelExpGet(POKEMON_PASO_PARAM *ppp);

extern	u32		PokeParaLevelExpGet(POKEMON_PARAM *pp);
extern	u32		PokeLevelExpGet(int	mons_no,int level);
extern	u8		PokeSexGet(POKEMON_PARAM *pp);
extern	u8		PokePasoSexGet(POKEMON_PASO_PARAM *ppp);
extern	u8		PokeSexGetMonsNo(u16 monsno,u32 rnd);
extern	u8		PokeRareGet(POKEMON_PARAM *pp);
extern	u8		PokePasoRareGet(POKEMON_PASO_PARAM *ppp);
extern	u8		PokeRareGetPara(u32 id,u32 rnd);
extern	u32		PokeRareRndGet(u32 id);
extern  u8		PokeRareGetPara(u32 id,u32 rnd);

extern	u32		PokeParaLevelCalc(POKEMON_PARAM *pp);
extern	u32		PokePasoLevelCalc(POKEMON_PASO_PARAM *ppp);
extern	u32		PokeLevelCalc(u16 mons_no,u32 exp);

extern	u8		PokeSeikakuGet(POKEMON_PARAM *pp);
extern	u8		PokePasoSeikakuGet(POKEMON_PASO_PARAM *ppp);
extern	u8		PokeSeikakuGetRnd(u32 rnd);

extern	void	PokeGraArcDataGetPP(SOFT_SPRITE_ARC *ssa,POKEMON_PARAM *pp,u8 dir);
extern	void	PokeGraArcDataGetPPP(SOFT_SPRITE_ARC *ssa,POKEMON_PASO_PARAM *ppp,u8 dir);
extern	void	PokeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 mons_no,u8 sex,u8 dir,u8 col,u8 form_no,u32 rnd);
extern	u8		PokeParaHeightGet(POKEMON_PARAM *pp,u8 dir);
extern	u8		PokePasoParaHeightGet(POKEMON_PASO_PARAM *ppp,u8 dir);
extern	u8		PokeHeightGet(u16 mons_no,u8 sex,u8 dir,u8 form_no,u32 rnd);
extern	void	TrGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 trtype,u8 dir,u8 sex);
extern	void	TrTypeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 tr_type);
extern	void	PokeAnmDataSet(SOFT_SPRITE_ANIME *ssanm,u16 mons_no);
extern	void	PokePrgAnmDataSet(POKE_ANM_SYS_PTR pasp,SOFT_SPRITE *ss,u16 mons_no,int dir,int chr,int reverse,int index);

extern	u32		PokemonParamSizeGet(void);
extern	u32		PokemonPasoParamSizeGet(void);

extern	u8		PokeParaUnknownFormGet(POKEMON_PARAM *pp);
extern	u8		PokePasoParaUnknownFormGet(POKEMON_PASO_PARAM *ppp);
//extern	u8		PokemonUnknownFormGet(u32 rnd);

//extern	u32		PokemonPasoUnknownFormRndGet(int form);

extern	POKEMON_PASO_PARAM	*PPPPointerGet(POKEMON_PARAM *pp);

extern	u8		PokeLevelUpCheck(POKEMON_PARAM *pp);
extern	u16		PokeShinkaCheck(POKEPARTY *ppt,POKEMON_PARAM *pp,u8 type,u16 itemno,int *shinka_cond);
extern  u16     PokeSearchChild(const u16 monsno);
extern  u16 	PokeChildCheck( const u16 monsno );


extern	u16		PokeParaZenkokuNo2ShinouNo(POKEMON_PARAM *pp);
extern	u16		PokePasoParaZenkokuNo2ShinouNo(POKEMON_PASO_PARAM *ppp);
extern	u16		PokeZenkokuNo2ShinouNo(u16 mons_no);
extern	u16		PokeShinouNo2ZenkokuNo(u16 mons_no);

extern	void	PokeCopyPPtoPP(POKEMON_PARAM *pp_src,POKEMON_PARAM *pp_dest);
extern	void	PokeCopyPPPtoPPP(POKEMON_PASO_PARAM *ppp_src,POKEMON_PASO_PARAM *ppp_dest);
extern	void	PokeCopyPPtoPPP(POKEMON_PARAM *pp_src,POKEMON_PASO_PARAM *ppp_dest);

extern	void	PokeWazaOboe(POKEMON_PARAM *pp);
extern	void	PokePasoWazaOboe(POKEMON_PASO_PARAM *ppp);
extern	u16		PokeWazaSet(POKEMON_PARAM *pp,u16 wazano);
extern	u16		PokePasoWazaSet(POKEMON_PASO_PARAM *ppp,u16 wazano);
extern	void	PokeWazaOboeOshidashi(POKEMON_PARAM *pp,u16 wazano);
extern	void	PokePasoWazaOboeOshidashi(POKEMON_PASO_PARAM *ppp,u16 wazano);
extern	void	PokeWazaSetPos(POKEMON_PARAM *pp,u16 wazano,u8 pos);
extern	void	PokePasoWazaSetPos(POKEMON_PASO_PARAM *ppp,u16 wazano,u8 pos);
extern	u16		PokeWazaOboeCheck(POKEMON_PARAM *pp,int *cnt,u16 *wazano);
extern int PokeOboeruWazaAllGet( int monsno, int form, u16 *wazalist );

extern	void	PokeParaWazaDelPos(POKEMON_PARAM *pp,u32 pos);

extern	s8		PokeParaLikeTasteCheck(POKEMON_PARAM *pp,int taste);
extern	s8		PokePasoParaLikeTasteCheck(POKEMON_PASO_PARAM *ppp,int taste);
extern	s8		PokeLikeTasteCheck(u32 rnd,int taste);

extern	void	PokeParaWazaReplace(POKEMON_PARAM *pp,int src_pos,int dest_pos);
extern	void	PokePasoParaWazaReplace(POKEMON_PASO_PARAM *ppp,int src_pos,int dest_pos);
extern	void	PokeReplace(POKEMON_PASO_PARAM *ppp,POKEMON_PARAM *pp);

typedef struct _POKEPARTY POKEPARTY;

extern	u8		GetStockPokeMaxLevel(POKEPARTY *ppt);
extern	void	PokerusSetCheck(POKEPARTY *ppt);
extern	u8		PokerusCheck(POKEPARTY *ppt,u8 check_bit);
extern	u8		PokerusedCheck(POKEPARTY *ppt,u8 check_bit);
extern	void	PokerusCounterDec(POKEPARTY *ppt,s32 day);
extern	void	PokerusCatchCheck(POKEPARTY *ppt);

extern	BOOL	PokeParaPokerusCheck(POKEMON_PARAM *pp);
extern	BOOL	PokePasoParaPokerusCheck(POKEMON_PASO_PARAM *ppp);
extern	BOOL	PokeParaPokerusedCheck(POKEMON_PARAM *pp);
extern	BOOL	PokePasoParaPokerusedCheck(POKEMON_PASO_PARAM *ppp);

extern	void	PokeParaAusuFormChange(POKEMON_PARAM *pp);
extern	void	PokePasoParaAusuFormChange(POKEMON_PASO_PARAM *ppp);
extern	u8		AusuTypeGet(u16	item_param);

extern	void	PokeWazaOboeDataGet(int monsno,u16 *wot);
extern	void	PokeFormNoWazaOboeDataGet(int monsno,int form_no,u16 *wot);
extern	BOOL	PokeParaWazaHaveCheck(POKEMON_PARAM *pp,u16 waza_no);

extern	void	PokeVoicePlaySet(PERAPVOICE *p_voice,int voice,u16 monsno,int pan,int vol,int flag,int heapID);

extern	void	PokeParaGetInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
extern	void	PokePasoParaGetInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
extern	void	PokeParaBirthInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
extern	void	PokePasoParaBirthInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);

extern	void	PokeItemSet(POKEMON_PARAM *pp,u32 fight_type,int range);

extern	BOOL	PokeParaWazaMachineCheck(POKEMON_PARAM *pp,u8 machine_no);
extern	BOOL	PokePasoParaWazaMachineCheck(POKEMON_PASO_PARAM *pp,u8 machine_no);
extern	BOOL	PokeWazaMachineCheck(u16 mons_no,int form_no,u8 machine_no);

extern	void	PokeParaSpeabiSet(POKEMON_PARAM *pp);
extern	void	PokePasoParaSpeabiSet(POKEMON_PASO_PARAM *ppp);

extern	void	PokeParaPersonalRndChange(POKEMON_PARAM *pp,u32 personal_rnd);

extern	s8		PokeChrAbiTableGet(u8 chr,u8 cond);

extern	void	FriendCalc(POKEMON_PARAM *pp,u8 id,u16 placeID);

extern	u32		PokePersonal_LevelCalc( POKEMON_PERSONAL_DATA* personalData, u16 monsno, u32 exp );
extern	u8		PokePersonal_SexGet( POKEMON_PERSONAL_DATA* personalData, u16 monsno, u32 rnd );

extern	u32		No2Bit(int no);
extern	int		Bit2No(u32 bit);

extern BOOL BattleTowerExPokeCheck_MonsNo( u16 mons );
extern BOOL BattleTowerExPokeCheck_PokePara( POKEMON_PARAM * pp );
extern u16 BattleTowerExPoke_MonsNoGet(u8 idx);

extern BOOL	PokemonOyaCheckPP( POKEMON_PARAM* pp, MYSTATUS* my, int heapID );
extern BOOL	PokemonOyaCheckPPP( POKEMON_PASO_PARAM* ppp, MYSTATUS* my, int heapID );

extern	int	TrainerBTrTypeGet(int trtype);

extern void PokePara_CustomBallDataInit( POKEMON_PARAM * pp );
extern void PokePasoPara_RecoverPP( POKEMON_PASO_PARAM* ppp );

#endif

#endif	__POKE_TOOL_H_
