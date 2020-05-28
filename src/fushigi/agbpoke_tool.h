#ifndef __AGBPOKE_TOOL_H__
#define __AGBPOKE_TOOL_H__

#define	MONSNO_AGB_TAMAGO	412

enum{
	ID_AGB_personal_rnd=0,		//������
	ID_AGB_id_no,			//ID�i���o�[
	ID_AGB_nickname,		//�j�b�N�l�[��
	ID_AGB_country_code,		//���R�[�h
	ID_AGB_fusei_tamago_flag,	//�f�[�^������ɂ��^�}�S��
	ID_AGB_poke_exist_flag,		//�|�P�����̑��݃t���O
	ID_AGB_egg_exist_flag,		//�|�P�����̑��݃t���O
	ID_AGB_oyaname,			//�e�̖��O
	ID_AGB_mark,			//�|�P�����ɂ���}�[�N
	ID_AGB_checksum,		//�`�F�b�N�T��
	ID_AGB_amari,   		//���҂̂��߂̗]��̈恩���̈ʒu��ύX����̂��֎~
					//���������̏��Ԃ�ύX����̂͋֎~�I�I

	ID_AGB_monsno,			//�����X�^�[�i���o�[
	ID_AGB_item,			//�����A�C�e��
	ID_AGB_waza1,			//�Z�P
	ID_AGB_waza2,			//�Z�Q
	ID_AGB_waza3,			//�Z�R
	ID_AGB_waza4,			//�Z�S
	ID_AGB_pp1,			//�Z�|�C���g1
	ID_AGB_pp2,			//�Z�|�C���g�Q
	ID_AGB_pp3,			//�Z�|�C���g�R
	ID_AGB_pp4,			//�Z�|�C���g�S
	ID_AGB_pp_count,		//�Z�|�C���g�A�b�v�J�E���^
	ID_AGB_style,			//�������悳
	ID_AGB_beautiful,		//��������
	ID_AGB_cute,			//���킢��
	ID_AGB_exp,			//�o���l
	ID_AGB_hp_exp,			//�q�b�g�|�C���g�w�͒l
	ID_AGB_pow_exp,			//�U���͓w�͒l
	ID_AGB_def_exp,			//�h��͓w�͒l
	ID_AGB_agi_exp,			//�f�����w�͒l
	ID_AGB_spepow_exp,		//����U���w�͒l
	ID_AGB_spedef_exp,		//����h��w�͒l
	ID_AGB_friend,			//�Ȃ��x
	ID_AGB_clever,			//��������
	ID_AGB_pokerus,			//�|�P���X
	ID_AGB_get_place,		//�ߊl�ꏊ
	ID_AGB_get_level,		//�ߊl���x��
	ID_AGB_get_cassette,		//�ߊl�J�Z�b�g
	ID_AGB_get_ball,		//�ߊl�{�[��
	ID_AGB_hp_rnd,			//�q�b�g�|�C���g�p���[����
	ID_AGB_pow_rnd,			//�U���̓p���[����
	ID_AGB_def_rnd,			//�h��̓p���[����
	ID_AGB_agi_rnd,			//�f�����p���[����
	ID_AGB_spepow_rnd,		//����U���p���[����
	ID_AGB_spedef_rnd,		//����h��p���[����
	ID_AGB_tamago_flag,		//���܂����ǂ����i0:�^�}�S����Ȃ�1:���܂�����j
	ID_AGB_speabi,			//����\�́i0:����\��1�@1:����\��2�j
	ID_AGB_strong,			//�����܂���
	ID_AGB_fur,			//�уd��
	ID_AGB_oyasex,			//�e�̐���
	ID_AGB_stylemedal,		//�������悳���_��
	ID_AGB_beautifulmedal,		//�����������_��
	ID_AGB_cutemedal,		//���킢�����_��
	ID_AGB_clevermedal,		//�����������_��
	ID_AGB_strongmedal,		//�����܂������_��
	ID_AGB_condition,		//�R���f�B�V����(��Ԉُ�j
	ID_AGB_level,			//���x��
	ID_AGB_hp,			//�q�b�g�|�C���g
	ID_AGB_hpmax,			//�q�b�g�|�C���g�}�b�N�X
	ID_AGB_pow,			//�U����
	ID_AGB_def,			//�h���
	ID_AGB_agi,			//�f����
	ID_AGB_spepow,			//����U��
	ID_AGB_spedef,			//����h��
	ID_AGB_mailid,			//�������[��
	ID_AGB_monsno_egg,		//�����X�^�[�i���o�[�i�^�}�S���ǂ������`�F�b�N����j
	ID_AGB_power_rnd,		//�p���[������u32�ň���
	ID_AGB_champ_ribbon,		//�`�����v���{���i�a������j
	ID_AGB_winning_ribbon, 		//�E�B�j���O���{���i�o�g���^���[LV50���������j
	ID_AGB_victory_ribbon, 		//�r�N�g���[���{���i�o�g���^���[LV100���������j
	ID_AGB_bromide_ribbon, 		//�u���}�C�h���{���i���p�قɎ���G������ꂽ�j
	ID_AGB_ganba_ribbon,	      	//����΃��{���i�w�͒l����ȏ�j
	ID_AGB_marine_ribbon,	      	//�}�������{���i�C�x���g�œ���j
	ID_AGB_land_ribbon,		//�����h���{���i�C�x���g�œ���j
	ID_AGB_sky_ribbon,		//�X�J�C���{���i�C�x���g�œ���j
	ID_AGB_country_ribbon,	  	//�J���g���[���{���i�C�x���g�œ���j
	ID_AGB_national_ribbon,	  	//�i�V���i�����{���i�C�x���g�œ���j
	ID_AGB_earth_ribbon,	      	//�A�[�X���{���i�C�x���g�œ���j
	ID_AGB_world_ribbon,	    	//���[���h���{���i�C�x���g�œ���j
	ID_AGB_amari_ribbon,		//���܂�
	ID_AGB_event_get_flag,		//�C�x���g�Ŕz�z���ꂽ���Ƃ������t���O
	ID_AGB_waza_have_check,		//�Z�������Ă��邩�`�F�b�N
	ID_AGB_ribbon_cnt,		//���{�������������Ă��邩�H
	ID_AGB_ribbon_bit,	 	//�擾���{���ɉ�����bit�𗧂ĂĕԂ��i�߹��ށj
	ID_AGB_pow_nocalc,		//�U���́i�f�I�L�V�X�v�Z�����Ȃ��j
	ID_AGB_def_nocalc,		//�h��́i�f�I�L�V�X�v�Z�����Ȃ��j
	ID_AGB_agi_nocalc,		//�f�����i�f�I�L�V�X�v�Z�����Ȃ��j
	ID_AGB_spepow_nocalc,	  	//����U���i�f�I�L�V�X�v�Z�����Ȃ��j
	ID_AGB_spedef_nocalc	  	//����h��i�f�I�L�V�X�v�Z�����Ȃ��j
};

#if 0
#define	POKE2VS2_OK		0				//2��2�퓬�\
#define	POKE2VS2_ONE	1				//1�̂����|�P���������Ȃ�
#define	POKE2VS2_NOTWO	2				//�킦��|�P������2�̂��Ȃ�

//StatusRecover�֐����ǂ�����Ă΂ꂽ�̂����w������t���O

#define		CALL_FIELD	0
#define		CALL_BATTLE	1

//�i������
enum{
	LEVELUP_SHINKA=0,		//���x���A�b�v�ɂ��i��
	TUUSHIN_SHINKA,			//�ʐM�ɂ��i��
	ITEM_SHINKA,			//�A�C�e���ɂ��i��
	ITEM_SHINKA_CHECK		//�A�C�e���ɂ��i���i����炸�̂����𑕔����Ă��Ă��`�F�b�N�͂���j
};

#define	SHINKA_FRIEND		220		//�i���ɕK�v�ȂȂ��x

#define	SHINKA_CANCEL_OFF	0
#define	SHINKA_CANCEL_ON	1

#define	SHINKA_BGM_RESTART_ON	0x00	//�i���f������̕��A����BGMStart��������
#define	SHINKA_BGM_RESTART_OFF	0x80	//�i���f������̕��A����BGMStart�������Ȃ�


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
	FRIEND_LEVEL30_HINSHI	//���x����30�ȏ�̕m��
};

//�w�͒l�Ɋւ����`

#define	PARA_EXP_TOTAL_MAX	510		//6�̃p�����[�^�̍��v�l�̃}�b�N�X
#define	PARA_EXP_MAX		100		//6�̃p�����[�^�̃}�b�N�X

#endif

//�|�P�����p�����[�^�擾�n�̒�`
enum{
	ID_AGB_POKEPARADATA11=0,
	ID_AGB_POKEPARADATA12,
	ID_AGB_POKEPARADATA13,
	ID_AGB_POKEPARADATA14,
	ID_AGB_POKEPARADATA15,
	ID_AGB_POKEPARADATA16,
	ID_AGB_POKEPARADATA21,
	ID_AGB_POKEPARADATA22,
	ID_AGB_POKEPARADATA23,
	ID_AGB_POKEPARADATA24,
	ID_AGB_POKEPARADATA25,
	ID_AGB_POKEPARADATA26,
	ID_AGB_POKEPARADATA31,
	ID_AGB_POKEPARADATA32,
	ID_AGB_POKEPARADATA33,
	ID_AGB_POKEPARADATA34,
	ID_AGB_POKEPARADATA35,
	ID_AGB_POKEPARADATA36,
	ID_AGB_POKEPARADATA41,
	ID_AGB_POKEPARADATA42,
	ID_AGB_POKEPARADATA43,
	ID_AGB_POKEPARADATA44,
	ID_AGB_POKEPARADATA45,
	ID_AGB_POKEPARADATA46
};

enum{
	ID_AGB_POKEPARA1=0,
	ID_AGB_POKEPARA2,
	ID_AGB_POKEPARA3,
	ID_AGB_POKEPARA4
};

#if 0

//�|�P�����ߊl���
#define	POS_EVENT_EGG	253		//���񂹂�o�[����ɂ��炤�^�}�S
#define	POS_CABLEKOUKAN	254		//�Q�[��������
#define	POS_EVENTHAIHU	255		//�C�x���g�ł̔z�z

//���o���
enum{
	TASTE_KARAI=0,
	TASTE_SIBUI,
	TASTE_AMAI,
	TASTE_NIGAI,
	TASTE_SUPPAI
};

//HitCountCheckFlag
#define	HCC_NORMAL		0		//�����ɈȊO�ŏ�ɂ���|�P�����̐�
#define	HCC_ATTACK		1		//Attack���ɂ���|�P�����̐�
#define	HCC_DEFENCE		2		//Defence���ɂ���|�P�����̐�

#endif

extern int ChangeAGBPoke2DPPoke(int agbpoke);
extern int GBAcode2DSuni(int c_id, u8 *agb_str, u16 *ds_str);
extern u32 AgbPokePasoParaGet(PokemonPasoParam *PPP,int id,u8 *buf);
extern void AgbPokePasoParaPut(PokemonPasoParam *PPP,int id,const u8 *buf);
extern u32 AgbPokePasoLevelCalc(PokemonPasoParam *ppp);


#endif	// __AGBPOKE_TOOL_H__
/*  */
