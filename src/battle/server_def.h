
//============================================================================================
/**
 * @file	server_def.h
 * @bfief	�퓬�T�[�o�v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#include	"battle/battle_common.h"
#include	"itemtool/item.h"
#include	"poketool/poke_tool.h"
#include	"poketool/waza_tool_def.h"
#include	"wazaeffect/ball_effect.h"
#include	"battle/wazano_def.h"
#include	"system/fontoam.h"

#ifndef __SERVER_DEF_H_
#define __SERVER_DEF_H_

///<client_act_work�̍ő�l
#define	ACT_PARA_MAX	(4)

///<�Z�V�[�P���X�p�i�[���[�N�̃T�C�Y�i�~�S�Ńo�C�g���ɂȂ�܂��j
#define	SKILL_SEQ_MAX		(400)

///<�Z�V�[�P���X�̃X�^�b�N�̍ő�l
#define	SKILL_SEQ_STACK	(4)

///<client_act_work�̒��g
enum{
	ACT_PARA_ACT_NO=0,		///<����i���o�[
	ACT_PARA_CLIENT_NO,		///<����ΏۃN���C�A���g�i���o�[
	ACT_PARA_WORK,			///<����i���o�[�p���[�N�i���������Ȃ�A�g�p����킴�̈ʒu�A�|�P��������ւ��Ȃ�A����ւ���i���o�[�j
	ACT_PARA_SELECT_COMMAND	///<�I�������R�}���h�i���o�[
};

///<�Z���ʗp���[�N�\���̐錾
struct waza_kouka_work{
	u32		kanashibari_count		: 3;		///<���Ȃ��΂�J�E���^
	u32		encore_count			: 3;		///<�A���R�[���J�E���^
	u32		juuden_count			: 2;		///<���イ�ł�J�E���^
	u32		chouhatsu_count			: 3;		///<���傤�͂J�E���^
	u32		success_count			: 2;		///<�܂���A���炦�邪���������J�E���^
	u32		horobinouta_count		: 2;		///<�ق�т̂����J�E���^
	u32		korogaru_count			: 3;		///<���낪��J�E���^
	u32		renzokugiri_count		: 3;		///<��񂼂�����J�E���^
	u32		takuwaeru_count			: 3;		///<�����킦��J�E���^
	u32		takuwaeru_def_count		: 3;		///<�����킦��J�E���^�i�h��A�b�v�j
	u32		takuwaeru_spedef_count	: 3;		///<�����킦��J�E���^�i���h�A�b�v�j
	u32		namake_bit				: 1;		///<�Ȃ܂��r�b�g
	u32		moraibi_flag			: 1;		///<���炢�уt���O

	u32		lockon_client_no		: 2;		///<���b�N�I�����ꂽClientNo
	u32		monomane_bit			: 4;		///<���̂܂˃r�b�g
	u32		shime_client_no			: 2;		///<���߂���ClientNo
	u32		manazashi_client_no		: 2;		///<���낢�܂Ȃ���������ClientNo
	u32		totteoki_count			: 3;		///<�Ƃ��Ă����p�Z���o�����t���O
	u32		denzihuyuu_count		: 3;		///<�ł񂶂ӂ䂤�J�E���^
	u32		healblock_count			: 3;		///<�q�[���u���b�N�J�E���^
	u32		shutout_count			: 3;		///<�V���b�g�A�E�g�J�E���^
	u32		karuwaza_flag			: 1;		///<����킴�t���O
	u32		metronome_work			: 4;		///<���g���m�[�����[�N
	u32		once_hit_up				: 1;		///<�������ʂň�x��������UP�t���O
	u32		once_agi_up				: 1;		///<�������ʂň�x�����搧�U���t���O
	u32		sensei_flag				: 1;		///<���񂹂��̂ߔ����t���O
	u32		sakidori_flag			: 1;		///<�����ǂ�t���O
	u32								: 1;

	int		handou_count;						///<�������󂯂��퓬�^�[�����i�[�i�{�P�̃^�[���̎������������󂯂�΂悢�j
	int		nekodamashi_count;					///<�������󂯂��퓬�^�[�����i�[�i�{�P�̃^�[���̎������������󂯂�΂悢�j
	int		slow_start_count;					///<�������󂯂��퓬�^�[�����i�[�i�{�P�̃^�[���̎������������󂯂�΂悢�j
	int		sakidori_count;						///<�������󂯂��퓬�^�[�����i�[�i�{�P�̃^�[���̎������������󂯂�΂悢�j
	int		migawari_hp;						///<�݂�����HP
	u32		henshin_rnd;						///<�ւ񂵂�p�̌������i�A���m�[����p�b�`�[���̌`�󌈂߂Ɏg�p�j

	u16		kanashibari_wazano;					///<���Ȃ��΂肳�ꂽ�Z�i���o�[
	u16		shime_wazano;						///<���߂���ꂽ�Z�i���o�[
	u16		encore_wazano;						///<�A���R�[�����ꂽ�Z�i���o�[
	u16		encore_wazapos;						///<�A���R�[�����ꂽ�Z�̈ʒu
	u16		totteoki_wazano[WAZA_TEMOTI_MAX];	///<�Ƃ��Ă����p�Z�i���o�[�i�[���[�N
	u16		kodawari_wazano;					///<�������n�`�}�L�p�Z�i���o�[�i�[���[�N
	u16		henshin_sex;						///<�ւ񂵂�p���ʊi�[���[�N

	int		item_hp_recover;					///<�A�C�e��HP�񕜗�
};

///<�莝���|�P�����̃T�[�o�p�\���̐錾
struct pokemon_server_param
{
	u16	monsno;								//02h
	u16	pow;								//04h

	u16	def;								//06h
	u16	agi;								//08h

	u16	spepow;								//0ah
	u16	spedef;								//0ch

	u16	waza[WAZA_TEMOTI_MAX];				//14h
	
	u32	hp_rnd			:5;
	u32	pow_rnd			:5;
	u32	def_rnd			:5;
	u32	agi_rnd			:5;
	u32	spepow_rnd		:5;
	u32	spedef_rnd		:5;
	u32	tamago_flag		:1;					//18h	0:�^�}�S����Ȃ�1:�^�}�S����
	u32	nickname_flag	:1;					//18h	�j�b�N�l�[�����������ǂ����t���O�i0:���Ă��Ȃ��@1:�����j

	s8	abiritycnt[POKEMON_ABIRITY_MAX];	//20h

	int	weight;								//24h

	u8	type1;								//25h
	u8	type2;								//26h
	u8	form_no				:5;				//27h
	u8	rare				:1;				//27h
	u8						:2;				//27h
	u8	speabino;							//28h
											//���������͂ւ񂵂�p�p�����[�^
											//�ړ��͌���
											
	u32	appear_check_flag	:1;				//2ch	�o�ꎞ�V��n�����`�F�b�N���������ǂ���
	u32	ikaku_flag			:1;				//2ch	�o�ꎞ�������`�F�b�N�������ǂ���
	u32	trace_flag			:1;				//2ch	�o�ꎞ�g���[�X�`�F�b�N�������ǂ���
	u32	download_flag		:1;				//2ch	�o�ꎞ�_�E�����[�h�`�F�b�N
	u32	kikenyochi_flag		:1;				//2ch	�o�ꎞ������悿�`�F�b�N
	u32	yochimu_flag		:1;				//2ch	�o�ꎞ�悿�ރ`�F�b�N
	u32	slow_start_flag		:1;				//2ch	�o�ꎞ�X���[�X�^�[�g�`�F�b�N
	u32	slow_start_end_flag	:1;				//2ch	�X���[�X�^�[�g�I���`�F�b�N
	u32	omitooshi_flag		:1;				//2ch	�o�ꎞ���݂Ƃ����`�F�b�N
	u32	katayaburi_flag		:1;				//2ch	�o�ꎞ������Ԃ�`�F�b�N
	u32	pressure_flag		:1;				//2ch	�o�ꎞ�v���b�V���[�`�F�b�N
	u32						:21;			//2ch

	u8	pp[WAZA_TEMOTI_MAX];				//30h

	u8	pp_count[WAZA_TEMOTI_MAX];			//34h

	u8	level;								//35h
	u8	friend;								//36h
	u16	nickname[MONS_NAME_SIZE+EOM_SIZE];	//4ch	(MONS_NAME_SIZE=10)+(EOM_SIZE=1)=11*2

	s32	hp;									//40h
	u32	hpmax;								//54h

	u16	oyaname[PERSON_NAME_SIZE+EOM_SIZE];	//64h	(PERSON_NAME_SIZE=7)+(EOM_SIZE=1)=8*2

	u32	exp;								//68h
	u32	personal_rnd;						//6ch
	u32	condition;							//70h
	u32	condition2;							//74h
	u32	id_no;								//78h

	u16 item;								//7ah
	u16 dummy;								//7ch

	u8	hit_count;							//7dh	�U�����󂯂���
	u8	message_flag;						//7eh	TRAINER_MESSAGE����p�t���O
	u8	sex		:4;							//7fh
	u8	oyasex	:4;							//7fh	�e�̐���
	u8	get_ball;							//80h	�ߊl�{�[��

	u32 waza_kouka;							//84h �Z���ʃt���O���[�N
	u32 waza_kouka_temp;					//88h �Z���ʃt���O�ޔ����[�N
	WAZA_KOUKA_WORK	wkw;					//	  �Z���ʗp���[�N
};

///<FieldCondition�p�J�E���^�\���̐錾
struct field_condition_count{
	u32		weather_count;						///<�V��ω��p�J�E���^

	u8		miraiyochi_count[CLIENT_MAX];		///<�݂炢�悿�J�E���^
	u8		negaigoto_count[CLIENT_MAX];		///<�˂������ƃJ�E���^

	u16		miraiyochi_wazano[CLIENT_MAX];		///<�݂炢�悿�Z�i���o�[���[�N
	int		miraiyochi_client_no[CLIENT_MAX];	///<�݂炢�悿����ClientNo
	s32		miraiyochi_damage[CLIENT_MAX];		///<�݂炢�悿�_���[�W

	u8		negaigoto_sel_mons[CLIENT_MAX];		///<�˂������Ƃ������|�P�����̎莝���̈ʒu
};

///<SideCondition�p���[�N�\���̐錾
struct side_condition_work{
	u32		butsuri_guard_client	: 2;		///<�����K�[�h���ʂ𔭐�������ClientNo���i�[
	u32		butsuri_guard_count		: 3;		///<�����K�[�h���ʃJ�E���^
	u32		tokusyu_guard_client	: 2;		///<����K�[�h���ʂ𔭐�������ClientNo���i�[
	u32		tokusyu_guard_count		: 3;		///<����K�[�h���ʃJ�E���^
	u32		shiroikiri_client		: 2;		///<���낢������ʂ𔭐�������ClientNo���i�[
	u32		shiroikiri_count		: 3;		///<���낢������ʃJ�E���^
	u32		shinpi_client			: 2;		///<����҂̂܂�����ʂ𔭐�������ClientNo���i�[
	u32		shinpi_count			: 3;		///<����҂̂܂�����ʃJ�E���^

	u32		konoyubitomare_flag		: 1;		///<���̂�тƂ܂�t���O
	u32		konoyubitomare_client	: 2;		///<���̂�тƂ܂�𔭓�����ClientNo
	u32		hatakiotosu_item		: 6;		///<�͂������Ƃ�����Ă���SelMonsNo��bit�Ŋi�[
	u32		oikaze_count			: 3;		///<���������J�E���^

	u32		makibisi_count			: 2;		///<�܂��т��J�E���^
	u32		dokubisi_count			: 2;		///<�ǂ��т��J�E���^
	u32								:28;
};

///<OneTurnFlag�p���[�N�\���̐錾
struct one_turn_flag{
	u32		waruagaki_flag		:1;		//��邠�����t���O
	u32		pp_dec_flag			:1;		//PP�����炵���t���O
	u32		mamoru_flag			:1;		//�܂���t���O
	u32		tedasuke_flag		:1;		//�Ă������t���O
	u32		magic_cort_flag		:1;
	u32		yokodori_flag		:1;
	u32		haneyasume_flag		:1;
	u32		escape_flag			:2;		//�ɂ����t���O�i����or����������ʁj
	u32		koraeru_flag		:1;		///<���炦��t���O
	u32							:22;
	int		butsuri_otf_damage[CLIENT_MAX];		///<�_���[�W�ʁi�����U��)
	int		butsuri_otf_client;					///<�����U�������N���C�A���g
	int		butsuri_otf_client_bit;				///<�����U�������N���C�A���g
	int		tokusyu_otf_damage[CLIENT_MAX];		///<�_���[�W�ʁi����U��)
	int		tokusyu_otf_client;					///<����U�������N���C�A���g
	int		tokusyu_otf_client_bit;				///<����U�������N���C�A���g
	int		last_otf_damage;					///<�_���[�W�ʁi�Ō�Ɏ󂯂��U��)
	int		last_otf_client;					///<�Ō�ɍU�������N���C�A���g
	int		dameoshi_damage;					///<�_���[�W�ʁi���߂����p)
};

///<OneSelfTurnFlag�p���[�N�\���̐錾
struct one_self_turn_flag{
	u32		no_pressure_flag	:1;		///<�����v���b�V���[�̌��ʂ��󂯂Ȃ�
	u32		hiraisin_flag		:1;		///<�����Ђ炢����̌��ʂ�����
	u32		yobimizu_flag		:1;		///<������т݂��̂̌��ʂ�����
	u32		katayaburi_flag		:1;		///<����������Ԃ�̌��ʂ�����
	u32		trickroom_flag		:1;		///<�g���b�N���[������
	u32		item_koraeru_flag	:1;		///<���炦��t���O�i����������ʁj
	u32		korogaru_count		:3;		///<���낪��J�E���g�i���g���m�[������Ŏg�p�j
	u32							:23;	///<�X�e�[�^�X�㏸���~�G�t�F�N�g�𔭓�
	int		butsuri_ostf_damage;		///<�_���[�W�ʁi�����U��)
	int		butsuri_ostf_client;		///<�����U�������N���C�A���g
	int		tokusyu_ostf_damage;		///<�_���[�W�ʁi����U��)
	int		tokusyu_ostf_client;		///<����U�������N���C�A���g
	int		status_flag;				///<�X�e�[�^�X�t���O�ibattle_server.h��define��`�j
	int		kaigara_damage;				///<��������̂����p�_���[�W��
};

///<SkillIntp�Ŏg�p�����^�X�N�p���[�N�ւ̃|�C���^
struct	tcb_skill_intp_work{
	BATTLE_WORK				*bw;
	SERVER_PARAM			*sp;
	BMS_PTR					bms;
	CATS_ACT_PTR			cap[2];				///<�T���|�P�������x���A�b�v�p�A�C�R���\��
	FONTOAM_OBJ_PTR			fop;				///<�T���|�P�������x���A�b�v�p�A�C�R���\��
	CHAR_MANAGER_ALLOCDATA	cma;
	int						flag;
	int						seq_no;
	int						ballID;				///<�|�P�����Q�b�g���̓�����{�[��ID
	int						work[8];
	void					*work_p[2];			///<�ėp���[�N�|�C���^
};

//���x���A�b�v���ɑޔ����Ă����p�����[�^
typedef struct{
	int	para[6];
}PUSH_POKEMON_PARAM;

//���b�Z�[�W�\���p�p�����[�^�\����
struct	message_param_data
{
	int	msg_id;
	int	msg_tag;
	int	msg_para[6];
};

//�Z�̔�����W�������ʂ������t���O
struct waza_out_check_flag
{
	u32	mahi_flag		:1;		//�܂ЂŋZ�������Ȃ�
	u32	koukanai_flag	:1;		//���ʂ��Ȃ��Z������
	u32	huuin_flag		:1;		//�ӂ����񂳂�ċZ�������Ȃ�
	u32	meromero_flag	:1;		//���������ŋZ�������Ȃ�
	u32	kanashibari_flag:1;		//���Ȃ��΂�ŋZ�������Ȃ�
	u32	chouhatsu_flag	:1;		//���傤�͂���ċZ�������Ȃ�
	u32	hirumu_flag		:1;		//�Ђ��ŋZ�������Ȃ�
	u32	konran_flag		:1;		//�����񂵂Ď������U��
	u32	juuryoku_flag	:1;		//���イ��傭�ŋZ�������Ȃ�
	u32	healblock_flag	:1;		//�q�[���u���b�N�ŋZ�������Ȃ�
	u32					:21;
};

//=========================================================================
//	AI�p�̍\���̐錾
//=========================================================================

struct ai_work_tbl{
	u8	AI_SEQNO;
	u8	AI_WAZAPOS;
	u16	AI_WAZANO;

	s8	AI_WAZAPOINT[4];

	int	AI_CALC_WORK;
	u32	AI_THINK_BIT;

	u8	AI_STATUSFLAG;
	u8	AI_THINK_NO;
	u8	AI_ALL_WAZA_CHECK_LOOP_CNT;
	u8	AI_ALL_WAZA_CHECK_PUSH_POS;

	u8	*AI_ALL_WAZA_CHECK_LOOP_ADRS;
	u8	AI_DAMAGELOSS[4];
										//���������́AAI�`�F�b�N�̂��тɃN���A����
	u16	AI_DEFENCE_USE_WAZA[4][4];

	u8	AI_TOKUSYUNO[4];
	u16	AI_SOUBIITEM[4];

	u16	AI_HAVEITEM[2][4];

	u32	PushAdrsBuf[8];

	u8	PushAdrsCnt;
	u8	AI_ITEMCNT[2];
	u8	AI_AttackClient;
	u8	AI_DefenceClient;

	u8	AI_ITEM_TYPE[2];
	u8	AI_ITEM_CONDITION[2];

	u16	AI_ITEM_NO[2];

	u8	AI_DirSelectClient[CLIENT_MAX];			//AI�őI�������U���Ώ�

	WAZA_TABLE_DATA	wtd[WAZANO_MAX+1];			//�Z�e�[�u���p�̃t�@�C���n���h��
	ITEMDATA		*item;						//�A�C�e���e�[�u��

	u16				AI_CALC_COUNT[CLIENT_MAX];		//�v�Z���s������
	u16				AI_CALC_CONTINUE[CLIENT_MAX];	//�v�Z�r�����ǂ���
};

//�f�o�b�O�c�[���p�\����
#ifdef PM_DEBUG
typedef struct{
	MSGDATA_MANAGER		*msg_m;			
	GF_BGL_BMPWIN		*win;
	STRBUF				*msg_buf;

	u8					seq_no;
	u8					sub_seq_no;
	u8					page;
	u8					pos;

	u32					debug_flag;

	u8					server_buffer_clear[CLIENT_MAX];///<server_buffer�̃N���A���������s���Ă��邩�Ď�

	u32					yubihuru_waza[7];				///<��т��ӂ�f�o�b�O�p�̋Z�i���o�[�i�[���[�N

	u16					yubihuru_no;					///<��т��ӂ�f�o�b�O�p�̃V�[�P���X�i���o�[�i�[���[�N
	u8					cur_pos_keta;
	u8					client_no;						///<�|�P�����p�����[�^���쎞�̑Ώۂ��i�[

	u8					sel_mons;
	u8					osyaberi_rank;					///<������ׂ胉���N�Œ�
	u16					dummy;
}DEBUG_BATTLE_PARAM;
#endif

///<�T�[�o�p�p�����[�^�\���̐錾
struct server_param{
	u8		com_seq_no[CLIENT_MAX];						///<�R�}���h�Z���N�g�V�[�P���X�ł̃V�[�P���X�i���o�[�i�[���[�N
	u8		ret_seq_no[CLIENT_MAX];						///<ALERT_MESSAGE_WAIT�I�����̖߂��V�[�P���X�i���o�[�i�[���[�N
	int		server_seq_no;								///<�T�[�o�V�[�P���X�i���o�[���[�N
	int		next_server_seq_no;							///<���ݎ��s���Ă���V�[�P���X�̎��ɐ��ڂ���V�[�P���X�i���o�[���i�[���郏�[�N
	int		fcc_seq_no;									///<FieldConditionCheck�p�V�[�P���X�i���o�[�i�[���[�N
	int		fcc_work;									///<FieldConditionCheck�Ŕėp�I�Ɏg�p���郏�[�N
	int		pcc_seq_no;									///<PokeConditionCheck�p�V�[�P���X�i���o�[�i�[���[�N
	int		pcc_work;									///<PokeConditionCheck�Ŕėp�I�Ɏg�p���郏�[�N
	int		scc_seq_no;									///<SideConditionCheck�p�V�[�P���X�i���o�[�i�[���[�N
	int		scc_work;									///<SideConditionCheck�Ŕėp�I�Ɏg�p���郏�[�N
	int		sba_seq_no;									///<ServerBeforeAct�p�V�[�P���X�i���o�[�i�[���[�N
	int		sba_work;									///<ServerBeforeAct�Ŕėp�I�Ɏg�p���郏�[�N
	int		swhac_seq_no;								///<ServerWazaHitAfterCheck�p�V�[�P���X�i���o�[�i�[���[�N
	int		swhac_work;									///<ServerWazaHitAfterCheck�p�Ŕėp�I�Ɏg�p���郏�[�N
	int		swoam_type;									///<ServerWazaOutAfterMessage�p�^�C�v�i���o�[�i�[���[�N
	int		swoam_seq_no;								///<ServerWazaOutAfterMessage�p�V�[�P���X�i���o�[�i�[���[�N
	int		swoak_seq_no;								///<ServerWazaOutAfterKouka�p�V�[�P���X�i���o�[�i�[���[�N
	int		swoak_work;									///<ServerWazaOutAfterKouka�Ŕėp�I�Ɏg�p���郏�[�N
	int		wb_seq_no;									///<WazaBefore�̃V�[�P���X�i���o�[
	int		woc_seq_no;									///<WazaOutCheck�̃V�[�P���X�i���o�[
	int		ssc_seq_no;									///<ServerStatusCheck�̃V�[�P���X�i���o�[
	int		stc_seq_no;									///<ServerTokuseiCheck�̃V�[�P���X�i���o�[
	int		spac_seq_no;								///<ServerPokeAppearCheck�̃V�[�P���X�i���o�[
	int		svc_work;									///<ServerVanishCheck�Ŕėp�I�Ɏg�p���郏�[�N

	int		waza_seq_adrs;								///<�Z�V�[�P���X�A�h���X
	int		attack_client;
	int		attack_client_temp;
	int		defence_client;
	int		defence_client_temp;
	int		kizetsu_client;								///<�C�₵���N���C�A���g
	int		reshuffle_client;							///<����ւ�������N���C�A���g
	int		reshuffle_client_temp;						///<����ւ�������N���C�A���g�i�ޔ�p�j
	int		tokusei_client;								///<�����`�F�b�N�����Ď����Ă����N���C�A���g
	int		magic_cort_client;							///<�}�W�b�N�R�[�g�p�N���C�A���g�ޔ����[�N
	int		tsuika_type;								///<�ǉ����ʂ̎�ށi���ځA�ԐځA�����j
	int		tsuika_para;								///<�ǉ����ʂ̎�ށi�˂ނ�A�܂ЂƂ��j
	int		tsuika_flag;								///<�ǉ����ʂ̃t���O
	int		tsuika_client;								///<�ǉ����ʂ�����N���C�A���g
	int		push_client;								///<�ޔ�p�N���C�A���g�i�[���[�N
	int		get_exp;									///<�l������o���l�i�[���[�N
	int		gakusyuu_get_exp;							///<�w�K���u�������Ă���|�P�������l������o���l�i�[���[�N
	u32		get_exp_right_flag[2];						///<�o���l���l�����錠�������|�P�����t���O
	int		skill_arc_kind;								///<�Z�V�[�P���X�̎�ށiARC_BE_SEQ�AARC_SUB_SEQ�Ȃǁj
	int		skill_arc_index;							///<�Z�V�[�P���X�̃C���f�b�N�X
	int		skill_seq_no;								///<�Z�V�[�P���X�̌��݈ʒu
	int		push_count;									///<PUSH�J�E���^
	int		push_skill_arc_kind[SKILL_SEQ_STACK];		///<�Z�V�[�P���X�̎�ށiARC_BE_SEQ�AARC_SUB_SEQ�ȂǁjPUSH�̈�
	int		push_skill_arc_index[SKILL_SEQ_STACK];		///<�Z�V�[�P���X�̃C���f�b�N�XPUSH�̈�
	int		push_skill_seq_no[SKILL_SEQ_STACK];			///<�Z�V�[�P���X�̌��݈ʒuPUSH�̈�
	int		agi_cnt;									///<�f�������̉��Ԗڂ��������J�E���^
	int		wait_cnt;									///<WS_WAIT�R�}���h�p�̃J�E���^
	MESSAGE_PARAM	mp;									///<MESSAGE_WORK�Ŏg�p�����MsgID�i�[���[�N
	int		client_work;								///<���b�Z�[�W�\���pClientNo�p�����[�^�i�[���[�N
	int		attack_client_work;							///<���b�Z�[�W�\���pAttackClientNo�p�����[�^�i�[���[�N
	int		defence_client_work;						///<���b�Z�[�W�\���pDefenceClientNo�p�����[�^�i�[���[�N
	int		waza_work;									///<���b�Z�[�W�\���pWazaNo�p�����[�^�i�[���[�N
	int		item_work;									///<���b�Z�[�W�\���pItemNo�p�����[�^�i�[���[�N
	int		tokusei_work;								///<���b�Z�[�W�\���pTokuseiNo�p�����[�^�i�[���[�N
	int		msg_work;									///<���b�Z�[�W�\���p�����[�^�i�[���[�N
	int		calc_work;									///<�Z�V�[�P���X�p�v�Z���[�N
	int		temp_work;									///<�Z�V�[�P���X�p�ėp���[�N
	u32		client_status[CLIENT_MAX];					///<ClientStatusFlag
	u32		koban_counter;								///<�˂��ɂ��΂�J�E���^�[
	int		total_turn;									///<���^�[����
	int		total_hinshi[CLIENT_MAX];					///<���m����
	int		total_damage[CLIENT_MAX];					///<���_���[�W��
	int		sakidori_total_turn;						///<���^�[�����i�����ǂ�p�j

	TCB_SKILL_INTP_WORK		*tsiw;						///<SkillIntp�Ŏg�p�����^�X�N�p���[�N�ւ̃|�C���^
	void	*work;										///<�ėp�I�Ɏg�p�����Alloc�����������ւ̃|�C���^

	u32						field_condition;			///<��ɂ�����퓬���ʃt���O���[�N
	FIELD_CONDITION_COUNT	fcc;						///<��ɂ�����퓬���ʃJ�E���^���[�N

	u32					side_condition[2];				///<���݂��̏�ɂ�����퓬���ʃt���O���[�N
	SIDE_CONDITION_WORK	scw[2];							///<���݂��̏�ɂ�����퓬���ʃ��[�N

	ONE_TURN_FLAG		otf[CLIENT_MAX];				///<�P�^�[���̂ݐ����\�ȃt���O
	ONE_SELF_TURN_FLAG	ostf[CLIENT_MAX];				///<�����̃^�[���̂ݐ����\�ȃt���O
	WAZA_OUT_CHECK_FLAG	wocf[CLIENT_MAX];				///<�Z�̔�����W�������ʂ������t���O

	AI_WORK_TBL	AIWT;									///<�g���[�i�[AI�p���[�N�\����
	u32		*AISeqWork;									///<�g���[�i�[AI�V�[�P���X�i�[���[�N�ւ̃|�C���^
	u32		AISeqAdrs;									///<�g���[�i�[AI�V�[�P���X�i�[���[�N�ւ̃|�C���^

	u32		server_status_flag;							///<�T�[�o�X�e�[�^�X�t���O�i�Z�V�[�P���X�ɉe�����y�ڂ��j
	u32		server_status_flag2;						///<�T�[�o�X�e�[�^�X�t���O�i�Z�V�[�P���X�ɉe�����y�ڂ��j

	int		damage;										///<�_���[�W��
	int		hit_damage;									///<�_���[�W�ʁi���ۂɂg�o�����炵���ʁj
	int		critical_count;								///<�N���e�B�J���`�F�b�N�Ɏg�p����N���e�B�J���̏o�₷���{�����[�N
	int		critical;									///<�N���e�B�J���q�b�g���[�N
	int		damage_power;								///<�Z�ɂ��U���̓��[�N
	int		damage_value;								///<�Z�ɂ��_���[�W�{�����[�N
	int		hp_calc_work;								///<HP�v�Z�p���[�N
	int		waza_type;									///<�Z�^�C�v���[�N
	int		waza_eff_cnt;								///<�Z�G�t�F�N�g�J�E���^
	int		okodukai_value;								///<���������̔{�����[�N
	u32		waza_status_flag;							///<�Z�������������Ƃŕω�����t���O
	u32		add_status_flag_direct;						///<�ǉ����ʃt���O�i���ځj
	u32		add_status_flag_indirect;					///<�ǉ����ʃt���O�i�Ԑځj
	u32		add_status_flag_tokusei;					///<�ǉ����ʃt���O�i�����j
	u8		renzoku_count;								///<�A���U���p�J�E���^
	u8		renzoku_count_temp;							///<�A���U���p�J�E���^�i�\���p�j
	u8		client_loop;								///<�����̓�����Z�J�E���^
	u8		hukurodataki_count;							///<�ӂ��낾�����̃J�E���^

	u32		loop_flag;									///<���[�v�������t���O
	u32		waza_out_check_on_off;						///<HITCHECK�L���t���O
	u32		loop_hit_check;								///<���[�v��������HITCHECK�L���t���O

	u32		condition2_off_req[CLIENT_MAX];				///<psp�\���̂�condition2�t���O�̍폜�v��

	u8		sel_mons_no[CLIENT_MAX];					///<�莝���̉��Ԗڂ��J��o���Ă��邩���i�[
	u8		reshuffle_sel_mons_no[CLIENT_MAX];			///<�莝���̉��Ԗڂ��J��o�������i�[
	u8		ai_reshuffle_sel_mons_no[CLIENT_MAX];		///<�莝���̉��Ԗڂ��J��o�������i�[�iAI���I���������́j
	u32		client_act_work[CLIENT_MAX][ACT_PARA_MAX];	///<�N���C�A���g�̓���i���o�[�Ɠ���Ώۂ��i�[
	u8		client_agi_work[CLIENT_MAX];				///<���΂₳���ɃN���C�A���gNo���i�[
	u8		psp_agi_work[CLIENT_MAX];					///<���΂₳���ɃN���C�A���gNo���i�[�i�����ɑf�����̒l�݂̂Ŕ��f�j
	u32		psp_agi_point[CLIENT_MAX];					///<�f�������i�[
	u8		ServerQue[ID_MAX][CLIENT_MAX][SERVER_QUE_MAX];		///<�N���C�A���g�ւ̖��߃L���[���[�N
	u8		server_buffer[CLIENT_MAX][BUF_SIZE];		///<�N���C�A���g����̉����i�[���[�N

	int		SkillSeqWork[SKILL_SEQ_MAX];				///<�Z�V�[�P���X�i�[���[�N

	POKEMON_SERVER_PARAM	psp[CLIENT_MAX];			///<�莝���|�P�����̃T�[�o�p�\����

	u32		waza_no_temp;								///<�J��o�����Z
	u32		waza_no_now;								///<���݌J��o����Ă���Z�i��т��ӂ邩��h���ȂǂŁA�X�V�����j
	u32		waza_no_last;								///<���O�ɌJ��o����Ă����Z
	u32		waza_no_keep[CLIENT_MAX];					///<���ߌn�̋Z���i�[
	
	u16		waza_no_mamoru[CLIENT_MAX];					///<1�^�[���O�ɌJ��o����Ă����Z�������������ǂ����i�܂���p�j
	u16		waza_no_hit[CLIENT_MAX];					///<1�^�[���O�ɌJ��o����Ă����Z���󂯂����ǂ���
	u16		waza_no_hit_client[CLIENT_MAX];				///<1�^�[���O�ɌJ��o����Ă����Z�𔭓�����ClientNo
	u16		waza_no_hit_type[CLIENT_MAX];				///<1�^�[���O�ɌJ��o����Ă����Z�𔭓�����ClientNo
	u16		waza_no_old[CLIENT_MAX];					///<1�^�[���O�ɌJ��o����Ă����Z
	u16		waza_no_oumu[CLIENT_MAX];					///<���O�Ɏ󂯂��Z���i�[�i�I�E���������p�j
	u16		waza_no_oumu_hit[CLIENT_MAX][CLIENT_MAX];	///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	u16		waza_no_sketch[CLIENT_MAX];					///<�X�P�b�`�p�̋Z�i���o�[���[�N
	u16		waza_no_select[CLIENT_MAX];					///<�I�������Z�i���o�[���[�N
	u16		waza_no_pos[CLIENT_MAX];					///<�I�������Z�i���o�[�̈ʒu
	u16		waza_no_texture2[CLIENT_MAX];				///<1�^�[���O�ɌJ��o����Ă����Z���󂯂����ǂ����i�e�N�X�`���[�Q��p�j
	u16		waza_no_texture2_client[CLIENT_MAX];		///<1�^�[���O�ɌJ��o����Ă����Z�𔭓�����Client�i�e�N�X�`���[�Q��p�j
	u16		waza_no_texture2_type[CLIENT_MAX];			///<1�^�[���O�ɌJ��o����Ă����Z�̃^�C�v�i�e�N�X�`���[�Q��p�j
	u16		waza_no_metronome[CLIENT_MAX];				///<���g���m�[���p�Z���[�N
	
	int		store_damage[CLIENT_MAX];					///<���܂�p�̃_���[�W�X�g�b�N���[�N

	int		client_no_hit[CLIENT_MAX];					///<�Z���Ō�ɓ��Ă�ClientNo���i�[

	int		client_no_agi;								///<CLIENT_NO_GET_AGI�Ŏg�p�����p���[�N

	u8		no_reshuffle_client;						///<����ւ���|�P�����������Ȃ�ClientNo���r�b�g�Ŋi�[
	u8		level_up_pokemon;							///<���x���A�b�v�����|�P�����̎莝���̈ʒu���r�b�g�Ŋi�[
	u16		que_check_wait;								///<ServerQueCheck���WAIT

	u16		agi_rand[CLIENT_MAX];						///<�f�����`�F�b�N�Ɏg�p���闐���l

	int		nagetsukeru_work;							///<�Ȃ�����p���[�N
	int		nagetsukeru_seq_no;							///<�Ȃ�����p�ǉ����ʂƂѐ惏�[�N

	u8		safari_get_count;							///<�T�t�@���̕ߊl���J�E���^
	u8		safari_escape_count;						///<�T�t�@���̓������J�E���^
	u8		escape_count;								///<�������I��������
	u8		fight_end_flag;								///<�퓬�I���t���O

	u8		magnitude;									///<�}�O�j�`���[�h�̑傫��
	u8		weather_check_flag;							///<�t�B�[���h�V��`�F�b�N�t���O
	s16		hp_temp;									///<�ΐ푊���HP��ۑ�
	
	u16		recycle_item[CLIENT_MAX];					///<���T�C�N���p�A�C�e�����[�N

	u8		list_row[CLIENT_MAX][POKEMON_TEMOTI_MAX];	///<�|�P�����̕��я����[�N

	int		jingle_flag;								///<�o���l�l��BGM�t���O

	int		server_que_time_out;						///<ServerQueCheck�ł̃^�C���A�E�g�J�E���^

#ifdef PM_DEBUG
	DEBUG_BATTLE_PARAM		dbp;						///<�f�o�b�O�c�[���p�p�����[�^
#endif
};

#endif __SERVER_DEF_H_
