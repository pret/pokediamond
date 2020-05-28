
//============================================================================================
/**
 * @file	server_tool.c
 * @bfief	�퓬�T�[�o�p�c�[���v���O����
 * @author	HisashiSogabe
 * @date	05.05.26
 */
//============================================================================================

#include "common.h"

#include "battle/battle_server.h"
#include "battle/fight_tool.h"
#include "battle/server.h"
#include "battle/server_tool.h"
#include "battle/client_tool.h"
#include "battle/tokusyu_def.h"
#include "battle/wazano_def.h"
#include "battle/attr_def.h"

#include "field/weather_no.h"

#include "msgdata/msg_fightmsg_dp.h"

#include "poketool/poke_tool.h"
#include "poketool/tr_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"

#include "application/app_tool.h"
#include "application/zukanlist/zkn_fight_text.h"
#include "application/zukanlist/zkn_height_gram.h"

#include "communication/communication.h"

#include "itemtool/item.h"

#include "system/arc_tool.h"
#include "system/snd_tool.h"
#include "system/pm_rtc.h"

#include "gflib/strbuf_family.h"

#include "server_def.h"
#include "tr_ai_def.h"

#include "bugfix.h"	//add by 2006.08.15

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

void	ST_PokemonParamGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no);
void	ST_PokemonParamReload(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no);
void	ST_ServerSequenceLoad(SERVER_PARAM *sp,int kind,int index);
void	ST_ServerSequenceLoadGosub(SERVER_PARAM *sp,int	kind,int index);
BOOL	ST_ServerSequencePushCheck(SERVER_PARAM *sp);
void	ST_ServerQueSet(SERVER_PARAM *sp,int id,int client_no,int index);
void	ST_ServerQueReset(SERVER_PARAM *sp,int id,int client_no,int index);
BOOL	ST_ServerQueCheck(SERVER_PARAM *sp);
void	ST_ServerQueTimeOutCheck(SERVER_PARAM *sp);
void	ST_ServerBufferClear(SERVER_PARAM *sp,int client_no);
int		ST_ServerPokemonServerParamGet(SERVER_PARAM *sp,int client,int id,void *data);
void	ST_ServerPokemonServerParamPut(SERVER_PARAM *sp,int client,int id,const void *buf);
void	ST_ServerPokemonServerParamAdd(SERVER_PARAM *sp,int client,int id,int value);
void	ST_PokemonServerParamAdd(POKEMON_SERVER_PARAM *psp,int id,int value);
u8		ST_ServerAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,int cl1,int cl2,int flag);
void	ST_ServerGetExpRightFlagClear(SERVER_PARAM *sp,int client_no);
void	ST_ServerGetExpRightFlagSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
void	ST_ServerGetExpRightFlagReset(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerAddStatusDirectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
BOOL	ST_ServerAddStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
int		ST_ServerDefenceClientSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 waza_no,int flag,int set_range);
void	ST_ServerDefenceClientTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 waza_no);
BOOL	ST_ServerDefenceClientTokuseiAct(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	ST_PSPtoPPCopy(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
void	ST_ServerKeepOn(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
void	ST_ServerKeepOff(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
int		ST_ServerConditionNoGet(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerTrainerMessageCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	ST_ServerWorkInit(SERVER_PARAM *sp);
void	ST_ServerCounterWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	ST_ServerReshuffleWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
void	ST_ServerKizetsuWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
void	ST_ServerOneTurnFlagInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
int		ST_ServerWaruagakiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_bit,int check_bit);
BOOL	ST_ServerWazaNGCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int pos,MESSAGE_PARAM *mp);
int		ST_ServerWazaPosGet(POKEMON_SERVER_PARAM *psp,u16 waza_no);
int		ST_ServerTypeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int waza_no,int waza_type,int attack_client,int defence_client,int damage,u32 *flag);
void	ST_AITypeCheck(SERVER_PARAM *sp,int waza_no,int waza_type,int spe_a,int spe_d,int eqp,int type1,int type2,u32 *flag);
BOOL	ST_ServerWazaOutCheck(SERVER_PARAM *sp,int client_no);
u8		ST_ServerHitCountCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int flag,int client_no);
int		ST_ServerTagNickParaMake(SERVER_PARAM *sp,int client_no);
u16		ST_ServerSelectWazaGet(SERVER_PARAM *sp,int client_no);
int		ST_ServerTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int flag,int client_no,int speabi);
BOOL	ST_TameWazaCheck(SERVER_PARAM *sp,int waza_no);
BOOL	ST_ServerTypeCheckTableParaGet(int pos,u8 *type_w,u8 *type_p,u8 *value);
int		ST_ServerTypeCheckTablePowerGet(u8 type_w,u8 type_p1,u8 type_p2);
BOOL	ST_RendouWazaCheck(u16 waza_no);
BOOL	ST_ServerWazaNoroiCheck(SERVER_PARAM *sp,u16 waza_no,int client_no);
BOOL	ST_ServerDorobouItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerTrickItemCheck(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerHukitobasiCheck(SERVER_PARAM *sp);
u8		ST_ServerTokuseiGet(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerKatayaburiTokuseiCheck(SERVER_PARAM *sp,int attack,int defence,int tokusei);
BOOL	ST_ServerReshuffleCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_EscapeNGCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,MESSAGE_PARAM *mp);
BOOL	ST_EscapeActCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerNamakeCheck(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerSawaguCheck(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerHuuinCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
BOOL	ST_ServerWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int waza_kouka);
void	ST_ServerLoopInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	ST_ServerPSPAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);
BOOL	ST_ServerJuuryokuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
BOOL	ST_ServerHealblockCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
void	ST_ServerTotteokiCountCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);
int		ST_ServerWazaCountGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
int		ST_ServerDamageTokuseiCheck(SERVER_PARAM *sp,int attack,int defence);
BOOL	ST_ServerPCCTokuseiCheck(SERVER_PARAM *sp,int client_no);
int		ST_ServerDamageDiv(int data,int value);
int		ST_ServerPokeAppearCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
int		ST_ServerDirClientGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerWazaHitTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
BOOL	ST_ServerTokuseiStatusRecoverCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int act_flag);
BOOL	ST_ServerTokuseiStatusRecoverReshuffleCheck(SERVER_PARAM *sp,int tokusei,int condition);
BOOL	ST_ServerSinkuroCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int server_seq_no);
BOOL	ST_ServerSoubiItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerSoubiItemTabenokosiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerSoubiItemConditionBadCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int *seq_no);
BOOL	ST_ServerSoubiItemDamageCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
u16		ST_ServerSoubiItemNoGet(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerWazaEndCheck(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerWazaHitSoubiItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
s32		ST_ServerSoubiEqpGet(SERVER_PARAM *sp,int client_no);
s32		ST_ServerSoubiAtkGet(SERVER_PARAM *sp,int client_no,int flag);
s32		ST_ServerShizennomegumiAtkGet(SERVER_PARAM *sp,int client_no);
s32		ST_ServerShizennomegumiTypeGet(SERVER_PARAM *sp,int client_no);
s32		ST_ServerTsuibamuEqpGet(SERVER_PARAM *sp,int client_no);
s32		ST_ServerNagetsukeruEqpGet(SERVER_PARAM *sp,int client_no);
s32		ST_ServerNagetsukeruAtkGet(SERVER_PARAM *sp,int client_no);
int		ST_ServerPokemonSelectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerTsuibamuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerNagetsukeruCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
void	ST_ServerMetronomeBeforeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	ST_ServerMetronomeAfterCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
int		ST_ServerPokeVoiceEffNoGet(SERVER_PARAM *sp,int client_no, int client_type, int encount);
BOOL	ST_ServerCommandSelectCheck(SERVER_PARAM *sp,int client_no);
void	ST_ServerPokemonGetParamSet(BATTLE_WORK *bw,SERVER_PARAM *sp,POKEMON_PARAM *pp);
u8		ST_ServerBufferResGet(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerMigawariCheck(SERVER_PARAM *sp,int client_no);
BOOL	ST_ServerPokeOneSelfCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp);
BOOL	ST_ServerPokeOneSelfCheckActPP(BATTLE_WORK *bw,POKEMON_PARAM *pp);
BOOL	ST_ServerTenkiyaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	ST_ServerListRowInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
void	ST_ServerListRowChange(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no);
int		ST_WazaDamageCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,
						  int wazano,u32 side_cond,u32 field_cond,u16 pow,u8 type,u8 attack,u8 defence,u8 critical);
int		ST_DamageLossCalc(SERVER_PARAM *sp,int damage);
int		ST_CriticalCheck(SERVER_PARAM *sp,int attack,int defence,int critical_count,u32 side_condition);
BOOL	ST_MonomaneNGCheck(u16 waza_no);
BOOL	ST_YubiwohuruNGCheck(u16 waza_no);
BOOL	ST_OumuEncoreNGCheck(SERVER_PARAM *sp,u16 waza_no);
BOOL	ST_SakidoriNGCheck(SERVER_PARAM *sp,u16 waza_no);
s32		ST_ItemParamGet(SERVER_PARAM *sp,u16 item_no,u16 param);
int		ST_ServerDir2ClientNoGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int dir);
void	ST_ServerTrickRoomAct(BATTLE_WORK *bw,SERVER_PARAM *sp);
BOOL	ST_ServerStatusEffectMigawariCheck(SERVER_PARAM *sp,int client_no,int status);
BOOL	ST_ServerWazaHitSoubiItemCheckTonbogaeri(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
void	ST_ServerPressurePPDecCheck(SERVER_PARAM *sp,int attack,int defence);

//�p�����[�^�Q�b�g�n
int		ST_ServerParamDataGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no);

//�p�����[�^�Z�b�g�n
void	ST_ServerOSTFStatusFlagSet(SERVER_PARAM *sp,int client_no,u32 value);
void	ST_ServerParamDataPut(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no,int data);

//�O�����J���Ȃ��n
static	BOOL	ST_KoukanaiCheck(SERVER_PARAM *sp,int attack_client,int defence_client,int pos);
static	int		ST_ServerAddStatusParamSet(SERVER_PARAM *sp,int type,u32 flag);
static	int		ST_TypeCheckCalc(SERVER_PARAM *sp,int attack,int power,int damage,int waza_damage,u32 *flag);
static	BOOL	ST_AIKoukanaiCheck(SERVER_PARAM *sp,int eqp,int pos);
static	void	ST_AITypeCheckCalc(int power,u32 *flag);
static	BOOL	ST_TameWazaTurnCheck(SERVER_PARAM *sp,int waza_no);
static	u8		ST_ServerTypeGet(SERVER_PARAM *sp,int client,int id);
static	void	WazaNoStockClear(SERVER_PARAM *sp,u8 client_no);
static	void	TokusyuNoClear(SERVER_PARAM *sp,u8 client_no);
static	void	SoubiItemClear(SERVER_PARAM *sp,u8 client_no);
static	int		ST_ServerTraceClientNoGet(SERVER_PARAM *sp,int def1,int def2);
static	BOOL	ST_ServerKikenyochiWazaSeqCheck(SERVER_PARAM *sp,int waza_no);
#if B1366_060815_FIX
static	int		ST_AIWazaTypeGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
#endif //B1366_060815_FIX

//============================================================================================
/**
 *	PokemonParam��PokemonServerParam�ɓǂݍ���
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�ǂݍ���client_no
 * @param[in]	sel_mons_no	�ǂݍ���PokemonParam�̐擪����̈ʒu
 */
//============================================================================================
void	ST_PokemonParamGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no)
{
	POKEMON_PARAM		*pp=BattleWorkPokemonParamGet(bw,client_no,sel_mons_no);
	int					i;
	int					dir;
	ZKN_HEIGHT_GRAM_PTR	zhgp;

	sp->psp[client_no].monsno=			PokeParaGet(pp,ID_PARA_monsno,			0);
	sp->psp[client_no].pow=				PokeParaGet(pp,ID_PARA_pow,				0);
	sp->psp[client_no].def=				PokeParaGet(pp,ID_PARA_def,				0);
	sp->psp[client_no].agi=				PokeParaGet(pp,ID_PARA_agi,				0);
	sp->psp[client_no].spepow=			PokeParaGet(pp,ID_PARA_spepow,			0);
	sp->psp[client_no].spedef=			PokeParaGet(pp,ID_PARA_spedef,			0);

	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		sp->psp[client_no].waza[i]=		PokeParaGet(pp,ID_PARA_waza1+i,			0);
		sp->psp[client_no].pp[i]=		PokeParaGet(pp,ID_PARA_pp1+i,			0);
		sp->psp[client_no].pp_count[i]=	PokeParaGet(pp,ID_PARA_pp_count1+i,		0);
	}

	sp->psp[client_no].hp_rnd=			PokeParaGet(pp,ID_PARA_hp_rnd,			0);
	sp->psp[client_no].pow_rnd=			PokeParaGet(pp,ID_PARA_pow_rnd,			0);
	sp->psp[client_no].def_rnd=			PokeParaGet(pp,ID_PARA_def_rnd,			0);
	sp->psp[client_no].agi_rnd=			PokeParaGet(pp,ID_PARA_agi_rnd,			0);
	sp->psp[client_no].spepow_rnd=		PokeParaGet(pp,ID_PARA_spepow_rnd,		0);
	sp->psp[client_no].spedef_rnd=		PokeParaGet(pp,ID_PARA_spedef_rnd,		0);

	sp->psp[client_no].tamago_flag=		PokeParaGet(pp,ID_PARA_tamago_flag,		0);
	sp->psp[client_no].nickname_flag=	PokeParaGet(pp,ID_PARA_nickname_flag,	0);

	//�o�g���^�b�`���ʂ̎��́A���������Ȃ�
	if((sp->server_status_flag&SERVER_STATUS_FLAG_BATON_TOUCH)==0){
		for(i=0;i<COND_MAX;i++){
			sp->psp[client_no].abiritycnt[i]=COND_NUM_DEFAULT;
		}
	}

	sp->psp[client_no].appear_check_flag=0;			//�o�ꎞ�V��n�����`�F�b�N���������ǂ���
	sp->psp[client_no].ikaku_flag=0;				//�o�ꎞ�������`�F�b�N�������ǂ���
	sp->psp[client_no].trace_flag=0;				//�o�ꎞ�g���[�X�`�F�b�N�������ǂ���
	sp->psp[client_no].download_flag=0;				//�o�ꎞ�_�E�����[�h�`�F�b�N
	sp->psp[client_no].kikenyochi_flag=0;			//�o�ꎞ������悿�`�F�b�N
	sp->psp[client_no].yochimu_flag=0;				//�o�ꎞ�悿�ރ`�F�b�N
	sp->psp[client_no].slow_start_flag=0;			//�o�ꎞ�X���[�X�^�[�g�`�F�b�N
	sp->psp[client_no].slow_start_end_flag=0;		//�X���[�X�^�[�g�I���`�F�b�N
	sp->psp[client_no].omitooshi_flag=0;			//�o�ꎞ���݂Ƃ����`�F�b�N
	sp->psp[client_no].katayaburi_flag=0;			//�o�ꎞ������Ԃ�`�F�b�N
	sp->psp[client_no].pressure_flag=0;				//�o�ꎞ�v���b�V���[�`�F�b�N

	sp->psp[client_no].type1=			PokeParaGet(pp,ID_PARA_type1,			0);
	sp->psp[client_no].type2=			PokeParaGet(pp,ID_PARA_type2,			0);

	sp->psp[client_no].sex=				PokeSexGet(pp);
	sp->psp[client_no].rare=			PokeRareGet(pp);

	sp->psp[client_no].form_no=			PokeParaGet(pp,ID_PARA_form_no,			0);

	//�T�t�@���A�|�P�p�[�N�ȂǁA�o�ꎞ�ɔ������������}�����邽�߂�0���Z�b�g
	//�T�t�@���A�|�P�p�[�N�ȂǁA��Ԉُ�̃`�F�b�N��}�����邽�߂�0���Z�b�g
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_NO_TOKUSEI){
		sp->psp[client_no].speabino=	0;
		sp->psp[client_no].condition=	0;
	}
	else{
		sp->psp[client_no].speabino=	PokeParaGet(pp,ID_PARA_speabino,		0);
		sp->psp[client_no].condition=	PokeParaGet(pp,ID_PARA_condition,		0);
	}

	sp->psp[client_no].level=			PokeParaGet(pp,ID_PARA_level,			0);
	sp->psp[client_no].friend=			PokeParaGet(pp,ID_PARA_friend,			0);


	sp->psp[client_no].hp=				PokeParaGet(pp,ID_PARA_hp,				0);
	sp->psp[client_no].hpmax=			PokeParaGet(pp,ID_PARA_hpmax,			0);

	sp->psp[client_no].exp=				PokeParaGet(pp,ID_PARA_exp,				0);
	sp->psp[client_no].personal_rnd=	PokeParaGet(pp,ID_PARA_personal_rnd,	0);
	sp->psp[client_no].id_no=			PokeParaGet(pp,ID_PARA_id_no,			0);
	sp->psp[client_no].item=			PokeParaGet(pp,ID_PARA_item,			0);
	sp->psp[client_no].oyasex=			PokeParaGet(pp,ID_PARA_oyasex,			0);
	sp->psp[client_no].get_ball=		PokeParaGet(pp,ID_PARA_get_ball,		0);

	//�}�ӂ̍����d����񃏁[�N���m��
	zhgp=ZKN_HEIGHTGRAM_Alloc(HEAPID_BATTLE);
	//�}�ӂ̍����d���������[�h
	ZKN_HEIGHTGRAM_Load(zhgp,ZKN_HEIGHT_GRAM_TYPE_MAN,HEAPID_BATTLE);

	sp->psp[client_no].weight=ZKN_HEIGHTGRAM_GetGram(zhgp,sp->psp[client_no].monsno);

	//�}�ӂ̍����d������j��
	ZKN_HEIGHTGRAM_Release(zhgp);
	//�}�ӂ̍����d����񃏁[�N���J��
	ZKN_HEIGHTGRAM_Free(zhgp);

	PokeParaGet(pp,ID_PARA_nickname,&sp->psp[client_no].nickname[0]);
	PokeParaGet(pp,ID_PARA_oyaname,&sp->psp[client_no].oyaname[0]);

	sp->psp[client_no].hit_count=0;
	sp->psp[client_no].message_flag=0;

	//�͂������Ƃ���Ă��鎞�́A�A�C�e���������Ă��Ȃ����Ƃɂ���
	dir=BattleWorkMineEnemyCheck(bw,client_no);
	if(sp->scw[dir].hatakiotosu_item&No2Bit(sp->sel_mons_no[client_no])){
		sp->psp[client_no].item=0;
		sp->psp[client_no].wkw.karuwaza_flag=0;
	}
	else{
		if(sp->psp[client_no].item){
			sp->psp[client_no].wkw.karuwaza_flag=1;
		}
	}
}

//============================================================================================
/**
 *	PokemonParam��PokemonServerParam�ɓǂݍ��ށi���x���A�b�v���̃����[�h�j
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�ǂݍ���client_no
 * @param[in]	sel_mons_no	�ǂݍ���PokemonParam�̐擪����̈ʒu
 */
//============================================================================================
void	ST_PokemonParamReload(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no)
{
	POKEMON_PARAM	*pp=BattleWorkPokemonParamGet(bw,client_no,sel_mons_no);
	int				i;
	int				dir;

	sp->psp[client_no].pow=				PokeParaGet(pp,ID_PARA_pow,				0);
	sp->psp[client_no].def=				PokeParaGet(pp,ID_PARA_def,				0);
	sp->psp[client_no].agi=				PokeParaGet(pp,ID_PARA_agi,				0);
	sp->psp[client_no].spepow=			PokeParaGet(pp,ID_PARA_spepow,			0);
	sp->psp[client_no].spedef=			PokeParaGet(pp,ID_PARA_spedef,			0);
	sp->psp[client_no].level=			PokeParaGet(pp,ID_PARA_level,			0);
	sp->psp[client_no].friend=			PokeParaGet(pp,ID_PARA_friend,			0);
	sp->psp[client_no].hp=				PokeParaGet(pp,ID_PARA_hp,				0);
	sp->psp[client_no].hpmax=			PokeParaGet(pp,ID_PARA_hpmax,			0);

	//�ւ񂵂񂵂Ă���|�P�����͈ȉ��̃����[�h�͂��Ȃ�
	if((sp->psp[client_no].condition2&CONDITION2_HENSHIN)==0){
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			//���̂܂˂��Ă���Z�̃����[�h�͂��Ȃ�
			if((sp->psp[client_no].wkw.monomane_bit&No2Bit(i))==0){
				sp->psp[client_no].waza[i]=		PokeParaGet(pp,ID_PARA_waza1+i,			0);
				sp->psp[client_no].pp[i]=		PokeParaGet(pp,ID_PARA_pp1+i,			0);
				sp->psp[client_no].pp_count[i]=	PokeParaGet(pp,ID_PARA_pp_count1+i,		0);
			}
		}
		sp->psp[client_no].exp=				PokeParaGet(pp,ID_PARA_exp,				0);
	}
}

//============================================================================================
/**
 *	�V�[�P���X�f�[�^��ǂݍ���
 *
 * @param[in]	sp		�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	kind	�ǂݍ��ރA�[�J�C�u�t�@�C���̎��
 * @param[in]	index	�ǂݍ��ރf�[�^�̃C���f�b�N�X
 */
//============================================================================================
void	ST_ServerSequenceLoad(SERVER_PARAM *sp,int	kind,int index)
{
	GF_ASSERT(ArchiveDataSizeGet(kind,index)<SKILL_SEQ_MAX*4);
	sp->skill_arc_kind=kind;
	sp->skill_arc_index=index;
	sp->skill_seq_no=0;
	ArchiveDataLoad(&sp->SkillSeqWork,kind,index);
}

//============================================================================================
/**
 *	�V�[�P���X�f�[�^��ǂݍ��ށi�T�u���[�`���W�����v�Ή��j
 *
 * @param[in]	sp		�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	kind	�ǂݍ��ރA�[�J�C�u�t�@�C���̎��
 * @param[in]	index	�ǂݍ��ރf�[�^�̃C���f�b�N�X
 */
//============================================================================================
void	ST_ServerSequenceLoadGosub(SERVER_PARAM *sp,int	kind,int index)
{
	GF_ASSERT(ArchiveDataSizeGet(kind,index)<SKILL_SEQ_MAX*4);
	GF_ASSERT(sp->push_count<SKILL_SEQ_STACK);
	sp->push_skill_arc_kind[sp->push_count]	=sp->skill_arc_kind;
	sp->push_skill_arc_index[sp->push_count]=sp->skill_arc_index;
	sp->push_skill_seq_no[sp->push_count]	=sp->skill_seq_no;
	sp->push_count++;
	sp->skill_arc_kind=kind;
	sp->skill_arc_index=index;
	sp->skill_seq_no=0;
	ArchiveDataLoad(&sp->SkillSeqWork,kind,index);
}

//============================================================================================
/**
 *	�T�u���[�`���W�����v�����������`�F�b�N
 *
 * @param[in]	sp		�T�[�o�p�p�����[�^���[�N�\����
 *
 * @retval	TRUE:�W�����v�Ȃ��@FALSE�F�W�����v�O�̃A�h���X�ɂ��ǂ��āA�V�[�P���X���s
 */
//============================================================================================
BOOL	ST_ServerSequencePushCheck(SERVER_PARAM *sp)
{
	if(sp->push_count){
		sp->push_count--;
		ST_ServerSequenceLoad(sp,sp->push_skill_arc_kind[sp->push_count],sp->push_skill_arc_index[sp->push_count]);
		sp->skill_seq_no=sp->push_skill_seq_no[sp->push_count];
		return FALSE;
	}
	else{
		return TRUE;
	}
}

//============================================================================================
/**
 *	�T�[�o���߃L���[�Ƀp�����[�^���Z�b�g
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	id			�ʐM���̒ʐMID
 * @param[in]	client_no	�T�[�o�����߂��Z�b�g�����N���C�A���g�i���o�[
 * @param[in]	index		���߃R�[�h�̃C���f�b�N�X
 */
//============================================================================================
void	ST_ServerQueSet(SERVER_PARAM *sp,int id,int client_no,int index)
{
	int	i;

	for(i=0;i<SERVER_QUE_MAX;i++){
		if(sp->ServerQue[id][client_no][i]==0){
			sp->ServerQue[id][client_no][i]=index;
			break;
		}
	}
//	OS_Printf("id:%d client_no:%d no:%d index:%d\n",id,client_no,i,index);
	//�T�[�o�L���[�����ӂ�Ă͂܂����̂ŁAASSERT���o��
	GF_ASSERT_MSG(i<SERVER_QUE_MAX,"ServerQueSet:ServerQue Overflow!\n");
}

//============================================================================================
/**
 *	�T�[�o���߃L���[�̃��Z�b�g
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	id			�ʐM���̒ʐMID
 * @param[in]	client_no	���Z�b�g�������N���C�A���g�i���o�[
 * @param[in]	index		���Z�b�g���閽�߃R�[�h�̃C���f�b�N�X
 */
//============================================================================================
void	ST_ServerQueReset(SERVER_PARAM *sp,int id,int client_no,int index)
{
	int	i;

	//index���O�͂��肦�Ȃ��̂ŁAASSERT���o��
	GF_ASSERT_MSG(index!=0,"ServerQueSet:index == 0\n");

	for(i=0;i<SERVER_QUE_MAX;i++){
		if(sp->ServerQue[id][client_no][i]==index){
			sp->ServerQue[id][client_no][i]=0;
			break;
		}
	}
	//�T�[�o�L���[�ɑΏۂ��Ȃ���Ԃł��̊֐����Ă΂��̂͂܂����̂ŁAASSERT���o��
	GF_ASSERT_MSG(i<SERVER_QUE_MAX,"ServerQueSet:ServerQue NotFound code=%d!\n",index);
}

//============================================================================================
/**
 *	�T�[�o���߃L���[���󂩃`�F�b�N����
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 *
 * @retval	TRUE:��@FALSE:��ł͂Ȃ�
 */
//============================================================================================
BOOL	ST_ServerQueCheck(SERVER_PARAM *sp)
{
	int	id,client_no,cnt;
	int	data=0;

	for(id=0;id<ID_MAX;id++){
		for(client_no=0;client_no<CLIENT_MAX;client_no++){
			for(cnt=0;cnt<SERVER_QUE_MAX;cnt++){
				data+=sp->ServerQue[id][client_no][cnt];
			}
		}
	}
	//�^�C���A�E�g�J�E���g���N���A
	if(data==0){
		sp->server_que_time_out=0;
	}
	return (data==0);
}

//============================================================================================
/**
 *	�T�[�o���߃L���[�^�C���A�E�g�`�F�b�N
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
void	ST_ServerQueTimeOutCheck(SERVER_PARAM *sp)
{
	sp->server_que_time_out++;
	if(sp->server_que_time_out>SERVER_QUE_TIME_OUT){
		OS_Printf("�T�[�o�^�C���A�E�g����\n");
		CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
	}
}

//============================================================================================
/**
 *	server_buffer���N���A����
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�N���A����o�b�t�@��client_no
 */
//============================================================================================
void	ST_ServerBufferClear(SERVER_PARAM *sp,int client_no)
{
	int	i;

	for(i=0;i<BUF_SIZE;i++){
		sp->server_buffer[client_no][i]=0;
	}
}

//============================================================================================
/**
 *	POKEMON_SERVER_PARAM����l���擾����
 *
 * @param[in]	sp		�T�[�o�p�����[�^���[�N�\����
 * @param[in]	client	�擾����ClientNo
 * @param[in]	id		�擾����l�̃C���f�b�N�X
 * @param[in]	data	�擾����l���i�[����|�C���^�iint�ł͑���Ȃ�������Ȃǁj
 */
//============================================================================================
int		ST_ServerPokemonServerParamGet(SERVER_PARAM *sp,int client,int id,void *data)
{
	POKEMON_SERVER_PARAM *psp;

	psp=&sp->psp[client];

	switch(id){
	case ID_PSP_monsno:
		return psp->monsno;
		break;
	case ID_PSP_pow:
		return psp->pow;
		break;
	case ID_PSP_def:
		return psp->def;
		break;
	case ID_PSP_agi:
		return psp->agi;
		break;
	case ID_PSP_spepow:
		return psp->spepow;
		break;
	case ID_PSP_spedef:
		return psp->spedef;
		break;
	case ID_PSP_waza1:
	case ID_PSP_waza2:
	case ID_PSP_waza3:
	case ID_PSP_waza4:
		return psp->waza[id-ID_PSP_waza1];
		break;
	case ID_PSP_hp_rnd:
		return psp->hp_rnd;
		break;
	case ID_PSP_pow_rnd:
		return psp->pow_rnd;
		break;
	case ID_PSP_def_rnd:
		return psp->def_rnd;
		break;
	case ID_PSP_agi_rnd:
		return psp->agi_rnd;
		break;
	case ID_PSP_spepow_rnd:
		return psp->spepow_rnd;
		break;
	case ID_PSP_spedef_rnd:
		return psp->spedef_rnd;
		break;
	case ID_PSP_tamago_flag:
		return psp->tamago_flag;
		break;
	case ID_PSP_nickname_flag:
		return psp->nickname_flag;
		break;
	case ID_PSP_abiritycnt_hp:
	case ID_PSP_abiritycnt_pow:
	case ID_PSP_abiritycnt_def:
	case ID_PSP_abiritycnt_agi:
	case ID_PSP_abiritycnt_spepow:
	case ID_PSP_abiritycnt_spedef:
	case ID_PSP_abiritycnt_hit:
	case ID_PSP_abiritycnt_avoid:
		return psp->abiritycnt[id-ID_PSP_abiritycnt_hp];
		break;
	case ID_PSP_speabino:
		return psp->speabino;
		break;
	case ID_PSP_type1:
	case ID_PSP_type2:
		//�����}���`�^�C�v�́A��������ɂ���ă^�C�v���ς��
		return ST_ServerTypeGet(sp,client,id);
		break;
	case ID_PSP_sex:
		return psp->sex;
		break;
	case ID_PSP_rare:
		return psp->rare;
		break;
	case ID_PSP_pp1:
	case ID_PSP_pp2:
	case ID_PSP_pp3:
	case ID_PSP_pp4:
		return psp->pp[id-ID_PSP_pp1];
		break;
	case ID_PSP_pp_count1:
	case ID_PSP_pp_count2:
	case ID_PSP_pp_count3:
	case ID_PSP_pp_count4:
		return psp->pp_count[id-ID_PSP_pp_count1];
		break;
	case ID_PSP_pp_max1:
	case ID_PSP_pp_max2:
	case ID_PSP_pp_max3:
	case ID_PSP_pp_max4:
		return WT_PPMaxGet(psp->waza[id-ID_PSP_pp_max1],psp->pp_count[id-ID_PSP_pp_max1]);
		break;
	case ID_PSP_level:
		return psp->level;
		break;
	case ID_PSP_friend:
		return psp->friend;
		break;
	case ID_PSP_nickname:
		{
			int	i;
			u16	*buf=data;

			for(i=0;i<MONS_NAME_SIZE+EOM_SIZE;i++){
				buf[i]=psp->nickname[i];
			}
		}
		break;
	case ID_PSP_nickname_buf:
		STRBUF_SetStringCode((STRBUF*)data, psp->nickname);
		break;
	case ID_PSP_hp:
		return psp->hp;
		break;
	case ID_PSP_hpmax:
		return psp->hpmax;
		break;
	case ID_PSP_oyaname:
		{
			int	i;
			u16	*buf=data;

			for(i=0;i<MONS_NAME_SIZE+EOM_SIZE;i++){
				buf[i]=psp->oyaname[i];
			}
		}
		break;
	case ID_PSP_exp:
		return psp->exp;
		break;
	case ID_PSP_personal_rnd:
		return psp->personal_rnd;
		break;
	case ID_PSP_condition:
		return psp->condition;
		break;
	case ID_PSP_condition2:
		return psp->condition2;
		break;
	case ID_PSP_id_no:
		return psp->id_no;
		break;
	case ID_PSP_item:
		return psp->item;
		break;
	case ID_PSP_hit_count:
		return psp->hit_count;
		break;
	case ID_PSP_message_flag:
		return psp->message_flag;
		break;
	case ID_PSP_oyasex:
		return psp->oyasex;
		break;
	case ID_PSP_waza_kouka:
		return psp->waza_kouka;
		break;
	case ID_PSP_waza_kouka_temp:
		return psp->waza_kouka_temp;
		break;
	case ID_PSP_wkw_kanashibari_count:
		return psp->wkw.kanashibari_count;
		break;
	case ID_PSP_wkw_encore_count:
		return psp->wkw.encore_count;
		break;
	case ID_PSP_wkw_juuden_count:
		return psp->wkw.juuden_count;
		break;
	case ID_PSP_wkw_chouhatsu_count:
		return psp->wkw.chouhatsu_count;
		break;
	case ID_PSP_wkw_success_count:
		return psp->wkw.success_count;
		break;
	case ID_PSP_wkw_horobinouta_count:
		return psp->wkw.horobinouta_count;
		break;
	case ID_PSP_wkw_korogaru_count:
		return psp->wkw.korogaru_count;
		break;
	case ID_PSP_wkw_renzokugiri_count:
		return psp->wkw.renzokugiri_count;
		break;
	case ID_PSP_wkw_takuwaeru_count:
		return psp->wkw.takuwaeru_count;
		break;
	case ID_PSP_wkw_takuwaeru_def_count:
		return psp->wkw.takuwaeru_def_count;
		break;
	case ID_PSP_wkw_takuwaeru_spedef_count:
		return psp->wkw.takuwaeru_spedef_count;
		break;
	case ID_PSP_wkw_namake_bit:
		return psp->wkw.namake_bit;
		break;
	case ID_PSP_wkw_moraibi_flag:
		return psp->wkw.moraibi_flag;
		break;
	case ID_PSP_wkw_lockon_client_no:
		return psp->wkw.lockon_client_no;
		break;
	case ID_PSP_wkw_monomane_bit:
		return psp->wkw.monomane_bit;
		break;
	case ID_PSP_wkw_shime_client_no:
		return psp->wkw.shime_client_no;
		break;
	case ID_PSP_wkw_manazashi_client_no:
		return psp->wkw.manazashi_client_no;
		break;
	case ID_PSP_wkw_totteoki_count:
		return psp->wkw.totteoki_count;
		break;
	case ID_PSP_wkw_denzihuyuu_count:
		return psp->wkw.denzihuyuu_count;
		break;
	case ID_PSP_wkw_healblock_count:
		return psp->wkw.healblock_count;
		break;
	case ID_PSP_wkw_shutout_count:
		return psp->wkw.shutout_count;
		break;
	case ID_PSP_wkw_karuwaza_flag:
		return psp->wkw.karuwaza_flag;
		break;
	case ID_PSP_wkw_metronome_work:
		return psp->wkw.metronome_work;
		break;
	case ID_PSP_wkw_once_hit_up:
		return psp->wkw.once_hit_up;
		break;
	case ID_PSP_wkw_once_agi_up:
		return psp->wkw.once_agi_up;
		break;
	case ID_PSP_wkw_sensei_flag:
		return psp->wkw.sensei_flag;
		break;
	case ID_PSP_wkw_handou_count:
		return psp->wkw.handou_count;
		break;
	case ID_PSP_wkw_nekodamashi_count:
		return psp->wkw.nekodamashi_count;
		break;
	case ID_PSP_wkw_slow_start_count:
		return psp->wkw.slow_start_count;
		break;
	case ID_PSP_wkw_migawari_hp:
		return psp->wkw.migawari_hp;
		break;
	case ID_PSP_wkw_henshin_rnd:
		return psp->wkw.henshin_rnd;
		break;
	case ID_PSP_wkw_kanashibari_wazano:
		return psp->wkw.kanashibari_wazano;
		break;
	case ID_PSP_wkw_encore_wazano:
		return psp->wkw.encore_wazano;
		break;
	case ID_PSP_wkw_shime_wazano:
		return psp->wkw.shime_wazano;
		break;
	case ID_PSP_wkw_item_hp_recover:
		return psp->wkw.item_hp_recover;
		break;
	case ID_PSP_slow_start_flag:
		return psp->slow_start_flag;
		break;
	case ID_PSP_slow_start_end_flag:
		return psp->slow_start_end_flag;
		break;
	case ID_PSP_work:
		return ST_ServerPokemonServerParamGet(sp,client,sp->temp_work,data);
		break;
	default:
		GF_ASSERT_MSG((0),"���݂��Ȃ�PSP�p�����[�^�ł�\n");
		break;
	}

	return 0;
}

//============================================================================================
/**
 *	POKEMON_SERVER_PARAM�ɒl���i�[����
 *
 * @param[in]	sp		�T�[�o�p�����[�^���[�N�\����
 * @param[in]	client	�i�[����ClientNo
 * @param[in]	id		�i�[����l�̃C���f�b�N�X
 * @param[in]	data	�i�[����l�ւ̃|�C���^
 */
//============================================================================================
void	ST_ServerPokemonServerParamPut(SERVER_PARAM *sp,int client,int id,const void *buf)
{
	int	i;
	u32	*buf32=(u32 *)buf;
	u16	*buf16=(u16 *)buf;
	s16	*bufs16=(s16 *)buf;
	u8	*buf8=(u8 *)buf;
	s8	*bufs8=(s8 *)buf;
	POKEMON_SERVER_PARAM	*psp=&sp->psp[client];

	switch(id){
	case ID_PSP_monsno:
		psp->monsno=buf16[0];
		break;
	case ID_PSP_pow:
		psp->pow=buf16[0];
		break;
	case ID_PSP_def:
		psp->def=buf16[0];
		break;
	case ID_PSP_agi:
		psp->agi=buf16[0];
		break;
	case ID_PSP_spepow:
		psp->spepow=buf16[0];
		break;
	case ID_PSP_spedef:
		psp->spedef=buf16[0];
		break;
	case ID_PSP_waza1:
	case ID_PSP_waza2:
	case ID_PSP_waza3:
	case ID_PSP_waza4:
		psp->waza[id-ID_PSP_waza1]=buf16[0];
		break;
	case ID_PSP_hp_rnd:
		psp->hp_rnd=buf8[0];
		break;
	case ID_PSP_pow_rnd:
		psp->pow_rnd=buf8[0];
		break;
	case ID_PSP_def_rnd:
		psp->def_rnd=buf8[0];
		break;
	case ID_PSP_agi_rnd:
		psp->agi_rnd=buf8[0];
		break;
	case ID_PSP_spepow_rnd:
		psp->spepow_rnd=buf8[0];
		break;
	case ID_PSP_spedef_rnd:
		psp->spedef_rnd=buf8[0];
		break;
	case ID_PSP_tamago_flag:
		psp->tamago_flag=buf8[0];
		break;
	case ID_PSP_nickname_flag:
		psp->nickname_flag=buf8[0];
		break;
	case ID_PSP_abiritycnt_hp:
	case ID_PSP_abiritycnt_pow:
	case ID_PSP_abiritycnt_def:
	case ID_PSP_abiritycnt_agi:
	case ID_PSP_abiritycnt_spepow:
	case ID_PSP_abiritycnt_spedef:
	case ID_PSP_abiritycnt_hit:
	case ID_PSP_abiritycnt_avoid:
		psp->abiritycnt[id-ID_PSP_abiritycnt_hp]=bufs8[0];
		break;
	case ID_PSP_speabino:
		psp->speabino=buf8[0];
		break;
	case ID_PSP_type1:
		psp->type1=buf8[0];
		break;
	case ID_PSP_type2:
		psp->type2=buf8[0];
		break;
	case ID_PSP_sex:
		psp->sex=buf8[0];
		break;
	case ID_PSP_rare:
		psp->rare=buf8[0];
		break;
	case ID_PSP_pp1:
	case ID_PSP_pp2:
	case ID_PSP_pp3:
	case ID_PSP_pp4:
		psp->pp[id-ID_PSP_pp1]=buf8[0];
		break;
	case ID_PSP_pp_count1:
	case ID_PSP_pp_count2:
	case ID_PSP_pp_count3:
	case ID_PSP_pp_count4:
		psp->pp_count[id-ID_PSP_pp_count1]=buf8[0];
		break;
	case ID_PSP_pp_max1:
	case ID_PSP_pp_max2:
	case ID_PSP_pp_max3:
	case ID_PSP_pp_max4:
		GF_ASSERT_MSG((0),"Put�ł��܂���\n");
		break;
	case ID_PSP_level:
		psp->level=buf8[0];
		break;
	case ID_PSP_friend:
		psp->friend=buf8[0];
		break;
	case ID_PSP_nickname:
		{
			int	i;
			for(i=0;i<MONS_NAME_SIZE+EOM_SIZE;i++){
				psp->nickname[i]=buf16[i];
			}
		}
		break;
	case ID_PSP_hp:
		psp->hp=bufs16[0];
		break;
	case ID_PSP_hpmax:
		psp->hpmax=buf16[0];
		break;
	case ID_PSP_oyaname:
		{
			int	i;

			for(i=0;i<MONS_NAME_SIZE+EOM_SIZE;i++){
				psp->oyaname[i]=buf16[i];
			}
		}
		break;
	case ID_PSP_exp:
		psp->exp=buf32[0];
		break;
	case ID_PSP_personal_rnd:
		psp->personal_rnd=buf32[0];
		break;
	case ID_PSP_condition:
		psp->condition=buf32[0];
		break;
	case ID_PSP_condition2:
		psp->condition2=buf32[0];
		break;
	case ID_PSP_id_no:
		psp->id_no=buf32[0];
		break;
	case ID_PSP_item:
		psp->item=buf16[0];
		break;
	case ID_PSP_hit_count:
		psp->hit_count=buf8[0];
		break;
	case ID_PSP_message_flag:
		psp->message_flag=buf8[0];
		break;
	case ID_PSP_oyasex:
		psp->oyasex=buf8[0];
		break;
	case ID_PSP_waza_kouka:
		psp->waza_kouka=buf32[0];
		break;
	case ID_PSP_waza_kouka_temp:
		psp->waza_kouka_temp=buf32[0];
		break;
	case ID_PSP_wkw_kanashibari_count:
		psp->wkw.kanashibari_count=buf8[0];
		break;
	case ID_PSP_wkw_encore_count:
		psp->wkw.encore_count=buf8[0];
		break;
	case ID_PSP_wkw_juuden_count:
		psp->wkw.juuden_count=buf8[0];
		break;
	case ID_PSP_wkw_chouhatsu_count:
		psp->wkw.chouhatsu_count=buf8[0];
		break;
	case ID_PSP_wkw_success_count:
		psp->wkw.success_count=buf8[0];
		break;
	case ID_PSP_wkw_horobinouta_count:
		psp->wkw.horobinouta_count=buf8[0];
		break;
	case ID_PSP_wkw_korogaru_count:
		psp->wkw.korogaru_count=buf8[0];
		break;
	case ID_PSP_wkw_renzokugiri_count:
		psp->wkw.renzokugiri_count=buf8[0];
		break;
	case ID_PSP_wkw_takuwaeru_count:
		psp->wkw.takuwaeru_count=buf8[0];
		break;
	case ID_PSP_wkw_takuwaeru_def_count:
		psp->wkw.takuwaeru_def_count=buf8[0];
		break;
	case ID_PSP_wkw_takuwaeru_spedef_count:
		psp->wkw.takuwaeru_spedef_count=buf8[0];
		break;
	case ID_PSP_wkw_namake_bit:
		psp->wkw.namake_bit=buf8[0];
		break;
	case ID_PSP_wkw_moraibi_flag:
		psp->wkw.moraibi_flag=buf8[0];
		break;
	case ID_PSP_wkw_lockon_client_no:
		psp->wkw.lockon_client_no=buf8[0];
		break;
	case ID_PSP_wkw_monomane_bit:
		psp->wkw.monomane_bit=buf8[0];
		break;
	case ID_PSP_wkw_shime_client_no:
		psp->wkw.shime_client_no=buf8[0];
		break;
	case ID_PSP_wkw_manazashi_client_no:
		psp->wkw.manazashi_client_no=buf8[0];
		break;
	case ID_PSP_wkw_totteoki_count:
		psp->wkw.totteoki_count=buf8[0];
		break;
	case ID_PSP_wkw_denzihuyuu_count:
		psp->wkw.denzihuyuu_count=buf8[0];
		break;
	case ID_PSP_wkw_healblock_count:
		psp->wkw.healblock_count=buf8[0];
		break;
	case ID_PSP_wkw_shutout_count:
		psp->wkw.shutout_count=buf8[0];
		break;
	case ID_PSP_wkw_karuwaza_flag:
		psp->wkw.karuwaza_flag=buf8[0];
		break;
	case ID_PSP_wkw_metronome_work:
		psp->wkw.metronome_work=buf8[0];
		break;
	case ID_PSP_wkw_once_hit_up:
		psp->wkw.once_hit_up=buf8[0];
		break;
	case ID_PSP_wkw_once_agi_up:
		psp->wkw.once_agi_up=buf8[0];
		break;
	case ID_PSP_wkw_sensei_flag:
		psp->wkw.sensei_flag=buf8[0];
		break;
	case ID_PSP_wkw_handou_count:
		psp->wkw.handou_count=buf32[0];
		break;
	case ID_PSP_wkw_nekodamashi_count:
		psp->wkw.nekodamashi_count=buf32[0];
		break;
	case ID_PSP_wkw_slow_start_count:
		psp->wkw.slow_start_count=buf32[0];
		break;
	case ID_PSP_wkw_migawari_hp:
		psp->wkw.migawari_hp=buf32[0];
		break;
	case ID_PSP_wkw_henshin_rnd:
		psp->wkw.henshin_rnd=buf32[0];
		break;
	case ID_PSP_wkw_kanashibari_wazano:
		psp->wkw.kanashibari_wazano=buf16[0];
		break;
	case ID_PSP_wkw_encore_wazano:
		psp->wkw.encore_wazano=buf16[0];
		break;
	case ID_PSP_wkw_shime_wazano:
		psp->wkw.shime_wazano=buf16[0];
		break;
	case ID_PSP_wkw_item_hp_recover:
		psp->wkw.item_hp_recover=buf32[0];
		break;
	case ID_PSP_slow_start_flag:
		psp->slow_start_flag=buf8[0];
		break;
	case ID_PSP_slow_start_end_flag:
		psp->slow_start_end_flag=buf8[0];
		break;
	case ID_PSP_work:
		ST_ServerPokemonServerParamPut(sp,client,sp->temp_work,buf);
		break;
	default:
		GF_ASSERT_MSG((0),"���݂��Ȃ�PSP�p�����[�^�ł�\n");
		break;
	}
}

//============================================================================================
/**
 *	POKEMON_SERVER_PARAM�ɒl�����Z����
 *
 * @param[in]	sp		�T�[�o�p�����[�^���[�N�\����
 * @param[in]	client	���Z����ClientNo
 * @param[in]	id		���Z�����l�̃C���f�b�N�X
 * @param[in]	value	���Z����l
 */
//============================================================================================
void	ST_ServerPokemonServerParamAdd(SERVER_PARAM *sp,int client,int id,int value)
{
	ST_PokemonServerParamAdd(&sp->psp[client],id,value);
}

//============================================================================================
/**
 *	POKEMON_SERVER_PARAM�ɒl�����Z����
 *
 * @param[in]	psp		�T�[�o�p�|�P�����p�����[�^���[�N�\����
 * @param[in]	id		���Z����l�̃C���f�b�N�X
 * @param[in]	value	���Z����l�ւ̃|�C���^
 */
//============================================================================================
void	ST_PokemonServerParamAdd(POKEMON_SERVER_PARAM *psp,int id,int value)
{
	int	i;

	switch(id){
	case ID_PSP_pow:
		psp->pow+=value;
		break;
	case ID_PSP_def:
		psp->def+=value;
		break;
	case ID_PSP_agi:
		psp->agi+=value;
		break;
	case ID_PSP_spepow:
		psp->spepow+=value;
		break;
	case ID_PSP_spedef:
		psp->spedef+=value;
		break;
	case ID_PSP_hp_rnd:
		psp->hp_rnd+=value;
		break;
	case ID_PSP_pow_rnd:
		psp->pow_rnd+=value;
		break;
	case ID_PSP_def_rnd:
		psp->def_rnd+=value;
		break;
	case ID_PSP_agi_rnd:
		psp->agi_rnd+=value;
		break;
	case ID_PSP_spepow_rnd:
		psp->spepow_rnd+=value;
		break;
	case ID_PSP_spedef_rnd:
		psp->spedef_rnd+=value;
		break;
	case ID_PSP_abiritycnt_hp:
	case ID_PSP_abiritycnt_pow:
	case ID_PSP_abiritycnt_def:
	case ID_PSP_abiritycnt_agi:
	case ID_PSP_abiritycnt_spepow:
	case ID_PSP_abiritycnt_spedef:
	case ID_PSP_abiritycnt_hit:
	case ID_PSP_abiritycnt_avoid:
		if(psp->abiritycnt[id-ID_PSP_abiritycnt_hp]+value<0){
			psp->abiritycnt[id-ID_PSP_abiritycnt_hp]=0;
		}
		else if(psp->abiritycnt[id-ID_PSP_abiritycnt_hp]+value>12){
			psp->abiritycnt[id-ID_PSP_abiritycnt_hp]=12;
		}
		else{
			psp->abiritycnt[id-ID_PSP_abiritycnt_hp]+=value;
		}
		break;
	case ID_PSP_pp1:
	case ID_PSP_pp2:
	case ID_PSP_pp3:
	case ID_PSP_pp4:
		{
			int	ppmax;

			ppmax=WT_PPMaxGet(psp->waza[id-ID_PSP_pp1],psp->pp_count[id-ID_PSP_pp1]);

			if(psp->pp[id-ID_PSP_pp1]+value>ppmax){
				psp->pp[id-ID_PSP_pp1]=ppmax;
			}
			else{
				psp->pp[id-ID_PSP_pp1]+=value;
			}
		}
		break;
	case ID_PSP_pp_count1:
	case ID_PSP_pp_count2:
	case ID_PSP_pp_count3:
	case ID_PSP_pp_count4:
		psp->pp_count[id-ID_PSP_pp_count1]+=value;
		break;
	case ID_PSP_level:
		psp->level+=value;
		break;
	case ID_PSP_friend:
		if((psp->friend+value)>FRIEND_MAX){
			psp->friend=FRIEND_MAX;
		}
		else{
			psp->friend+=value;
		}
		break;
	case ID_PSP_hp:
		if(psp->hp+value>psp->hpmax){
			psp->hp=psp->hpmax;
		}
		else{
			psp->hp+=value;
		}
		break;
	case ID_PSP_hpmax:
		psp->hpmax+=value;
		break;
	case ID_PSP_exp:
		psp->exp+=value;
		break;
	case ID_PSP_personal_rnd:
		psp->personal_rnd+=value;
		break;
	case ID_PSP_wkw_kanashibari_count:
		psp->wkw.kanashibari_count+=value;
		break;
	case ID_PSP_wkw_encore_count:
		psp->wkw.encore_count+=value;
		break;
	case ID_PSP_wkw_juuden_count:
		psp->wkw.juuden_count+=value;
		break;
	case ID_PSP_wkw_chouhatsu_count:
		psp->wkw.chouhatsu_count+=value;
		break;
	case ID_PSP_wkw_success_count:
		psp->wkw.success_count+=value;
		break;
	case ID_PSP_wkw_horobinouta_count:
		psp->wkw.horobinouta_count+=value;
		break;
	case ID_PSP_wkw_korogaru_count:
		psp->wkw.korogaru_count+=value;
		break;
	case ID_PSP_wkw_renzokugiri_count:
		psp->wkw.renzokugiri_count+=value;
		break;
	case ID_PSP_wkw_takuwaeru_count:
		psp->wkw.takuwaeru_count+=value;
		break;
	case ID_PSP_wkw_takuwaeru_def_count:
		psp->wkw.takuwaeru_def_count+=value;
		break;
	case ID_PSP_wkw_takuwaeru_spedef_count:
		psp->wkw.takuwaeru_spedef_count+=value;
		break;
	case ID_PSP_wkw_totteoki_count:
		psp->wkw.totteoki_count+=value;
		break;
	case ID_PSP_wkw_denzihuyuu_count:
		psp->wkw.denzihuyuu_count+=value;
		break;
	case ID_PSP_wkw_healblock_count:
		psp->wkw.healblock_count+=value;
		break;
	case ID_PSP_wkw_handou_count:
		psp->wkw.handou_count+=value;
		break;
	case ID_PSP_wkw_nekodamashi_count:
		psp->wkw.nekodamashi_count+=value;
		break;
	case ID_PSP_wkw_slow_start_count:
		psp->wkw.slow_start_count+=value;
		break;
	case ID_PSP_wkw_migawari_hp:
		psp->wkw.migawari_hp+=value;
		break;
	case ID_PSP_wkw_item_hp_recover:
		psp->wkw.item_hp_recover+=value;
		break;
	case ID_PSP_slow_start_flag:
		psp->slow_start_flag+=value;
		break;
	case ID_PSP_slow_start_end_flag:
		psp->slow_start_end_flag+=value;
		break;
	default:
		GF_ASSERT_MSG((0),"���݂��Ȃ�PSP�p�����[�^�ł�\n");
		break;
	}
}

//============================================================================================
/**
 *	�f�����𔼌����鑕�����ʃe�[�u��
 */
//============================================================================================
static	const	u8	ItemEqpAgiHalfTable[]={
	SOUBI_DORYOKUTINIBAI,
	SOUBI_SUBAYASADOWN,
	SOUBI_HPDORYOKUTIUP,
	SOUBI_KOUGEKIDORYOKUTIUP,
	SOUBI_BOUGYODORYOKUTIUP,
	SOUBI_SUBAYASADORYOKUTIUP,
	SOUBI_TOKUKOUDORYOKUTIUP,
	SOUBI_TOKUBOUDORYOKUTIUP,
};

//============================================================================================
/**
 *	�|�P�����̑f�����v�Z
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	cl1			�`�F�b�N����ClientNo��1
 * @param[in]	cl2			�`�F�b�N����ClientNo��2
 * @param[in]	flag		�Z�̐搧�v���C�I���e�B�̗L��(0)�^����(1)
 *
 * @retval	0:�\�[�g�̕K�v�Ȃ��@1:�\�[�g�̕K�v����@2:�\�[�g�̕K�v����i�f�����������������̂ŁA�����_���Ō��肳�ꂽ�j
 */
//============================================================================================
u8	ST_ServerAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,int cl1,int cl2,int flag)
{
	u8	ret=0;
	u32	agi1,agi2;
	u16	wazano1=0,wazano2=0;
	u8	eqp1;
	u8	atk1;
	u8	eqp2;
	u8	atk2;
	s8	attackpri1=0;
	s8	attackpri2=0;
	u8	sensei1=0,sensei2=0;
	u8	koukou1=0,koukou2=0;
	int	command1;
	int	command2;
	int	wazapos1;
	int	wazapos2;
	int	speabi1;
	int	speabi2;
	int	cond_agi1;
	int	cond_agi2;
	int	i;

	//HP0�̓z�͖������ɒx������
	if((sp->psp[cl1].hp==0)&&(sp->psp[cl2].hp)){
		return 1;
	}
	if((sp->psp[cl1].hp)&&(sp->psp[cl2].hp==0)){
		return 0;
	}

	speabi1=ST_ServerTokuseiGet(sp,cl1);
	speabi2=ST_ServerTokuseiGet(sp,cl2);

	eqp1=ST_ServerSoubiEqpGet(sp,cl1);
	atk1=ST_ServerSoubiAtkGet(sp,cl1,ATK_CHECK_NORMAL);
	eqp2=ST_ServerSoubiEqpGet(sp,cl2);
	atk2=ST_ServerSoubiAtkGet(sp,cl2,ATK_CHECK_NORMAL);

	cond_agi1=sp->psp[cl1].abiritycnt[COND_AGI];
	cond_agi2=sp->psp[cl2].abiritycnt[COND_AGI];

	//�������񂶂��������Ă���Ƃ��́A���΂₳�㏸��{
	if(ST_ServerTokuseiGet(sp,cl1)==TOKUSYU_TANZYUN){
		cond_agi1=6+((cond_agi1-6)*2);
		if(cond_agi1>12){
			cond_agi1=12;
		}
		if(cond_agi1<0){
			cond_agi1=0;
		}
	}
	if(ST_ServerTokuseiGet(sp,cl2)==TOKUSYU_TANZYUN){
		cond_agi2=6+((cond_agi2-6)*2);
		if(cond_agi2>12){
			cond_agi2=12;
		}
		if(cond_agi2<0){
			cond_agi2=0;
		}
	}
	
	agi1=sp->psp[cl1].agi*CondChgTable[cond_agi1][0]/
						  CondChgTable[cond_agi1][1];

	agi2=sp->psp[cl2].agi*CondChgTable[cond_agi2][0]/
						  CondChgTable[cond_agi2][1];

	//����\�͂̂��Ă񂫂̃|�P�������퓬�ɏo�Ă���Ƃ��̓`�F�b�N�����Ȃ�
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//����\�͂��������́A�J�̂Ƃ��f�������{
		//����\�͂悤��傭���́A����̂Ƃ��f�������{
		if(((speabi1==TOKUSYU_SUISUI)&&(sp->field_condition&FIELD_CONDITION_AME_ALL))||
		   ((speabi1==TOKUSYU_YOURYOKUSO)&&(sp->field_condition&FIELD_CONDITION_HARE_ALL))){
			agi1*=2;
		}
		//����\�͂��������́A�J�̂Ƃ��f�������{
		//����\�͂悤��傭���́A����̂Ƃ��f�������{
		if(((speabi2==TOKUSYU_SUISUI)&&(sp->field_condition&FIELD_CONDITION_AME_ALL))||
		   ((speabi2==TOKUSYU_YOURYOKUSO)&&(sp->field_condition&FIELD_CONDITION_HARE_ALL))){
			agi2*=2;
		}
	}

	//�A�C�e���œw�͒l�Q�{�̌��ʁA���΂₳DOWN�𑕔�����Ƒf������1/2�ɂ���
	for(i=0;i<NELEMS(ItemEqpAgiHalfTable);i++){
		if(ST_ItemParamGet(sp,sp->psp[cl1].item,ITEM_PRM_EQUIP)==ItemEqpAgiHalfTable[i]){
			agi1/=2;
			break;
		}
	}

	//�A�C�e���ł������n�𑕔�����Ƒf������1.5�{�ɂ���
	if(eqp1==SOUBI_ONAZIWAZAONLYSUBAYASAUP){
		agi1=agi1*15/10;
	}

	//�A�C�e���Ń��^���������Ƒf������2�{�ɂ���
	if((eqp1==SOUBI_METAMONSUBAYASAUP)&&(sp->psp[cl1].monsno==MONSNO_METAMON)){
		agi1*=2;
	}

	//�����͂₠���́A��Ԉُ�őf������1.5�{�ɂ���
	if((speabi1==TOKUSYU_HAYAASI)&&(sp->psp[cl1].condition&CONDITION_BAD)){
		agi1=agi1*15/10;
	}
	else{
		//�܂Ђ̎��́A�f������1/4�ɂ���
		if(sp->psp[cl1].condition&CONDITION_MAHI){
			agi1/=4;
		}
	}

	//�����X���[�X�^�[�g�́A��ɂłĂ���5�^�[���ȓ��͑f�����𔼕��ɂ���
	if((speabi1==TOKUSYU_SUROOSUTAATO)&&
	  ((sp->total_turn-sp->psp[cl1].wkw.slow_start_count)<5)){
		agi1/=2;
	}

	//��������킴�́A�A�C�e���������Ă��܂��Ƒf�������{�ɂȂ�
	if((speabi1==TOKUSYU_KARUWAZA)&&
	   (sp->psp[cl1].wkw.karuwaza_flag)&&
	   (sp->psp[cl1].item==0)){
		agi1*=2;
	}

	//�Z���ʂ����������󂯂Ă��鎞�́A�f������2�{��
	if(sp->side_condition[BattleWorkMineEnemyCheck(bw,cl1)]&SIDE_CONDITION_OIKAZE){
		agi1*=2;
	}

	//�A�C�e���Ő搧�U���̌��ʂ𑕔�����Ɛ搧�U���ɂ���
	if(eqp1==SOUBI_SENSEIKOUGEKI){
#ifdef PM_DEBUG
		if(((sp->agi_rand[cl1]%(100/atk1))==0)||sp->dbp.debug_flag&DEBUG_FLAG_SOUBI){
#else
		if((sp->agi_rand[cl1]%(100/atk1))==0){
#endif
			sensei1=1;
			//�Z�̃v���C�I���e�B�����Ȃ����́A���ʃG�t�F�N�g�̔����͂Ȃ�
			if(flag==0){
				sp->psp[cl1].wkw.sensei_flag=1;
			}
		}
	}
	
	//�������ʂŐ搧�U���ɂ���
	if(sp->psp[cl1].wkw.once_agi_up){
		sensei1=1;
	}

	//�A�C�e���Ō�U�U���̌��ʂ𑕔�����ƌ�U�U���ɂ���
	if(eqp1==SOUBI_KOUKOUNINARU){
		koukou1=1;
	}

	//�A�C�e���œw�͒l�Q�{�̌��ʁA���΂₳DOWN�𑕔�����Ƒf������1/2�ɂ���
	for(i=0;i<NELEMS(ItemEqpAgiHalfTable);i++){
		if(ST_ItemParamGet(sp,sp->psp[cl2].item,ITEM_PRM_EQUIP)==ItemEqpAgiHalfTable[i]){
			agi2/=2;
			break;
		}
	}

	//�A�C�e���ł������n�𑕔�����Ƒf������1.5�{�ɂ���
	if(eqp2==SOUBI_ONAZIWAZAONLYSUBAYASAUP){
		agi2=agi2*15/10;
	}

	//�A�C�e���Ń��^���������Ƒf������2�{�ɂ���
	if((eqp2==SOUBI_METAMONSUBAYASAUP)&&(sp->psp[cl2].monsno==MONSNO_METAMON)){
		agi2*=2;
	}

	//�����͂₠���́A��Ԉُ�őf������1.5�{�ɂ���
	if((speabi2==TOKUSYU_HAYAASI)&&(sp->psp[cl2].condition&CONDITION_BAD)){
		agi2=agi2*15/10;
	}
	else{
		//�܂Ђ̎��́A�f������1/4�ɂ���
		if(sp->psp[cl2].condition&CONDITION_MAHI){
			agi2/=4;
		}
	}

	//�����X���[�X�^�[�g�́A��ɂłĂ���5�^�[���ȓ��͑f�����𔼕��ɂ���
	if((speabi2==TOKUSYU_SUROOSUTAATO)&&
	  ((sp->total_turn-sp->psp[cl2].wkw.slow_start_count)<5)){
		agi2/=2;
	}

	//��������킴�́A�A�C�e���������Ă��܂��Ƒf�������{�ɂȂ�
	if((speabi2==TOKUSYU_KARUWAZA)&&
	   (sp->psp[cl2].wkw.karuwaza_flag)&&
	   (sp->psp[cl2].item==0)){
		agi2*=2;
	}

	//�Z���ʂ����������󂯂Ă��鎞�́A�f������2�{��
	if(sp->side_condition[BattleWorkMineEnemyCheck(bw,cl2)]&SIDE_CONDITION_OIKAZE){
		agi2*=2;
	}

	//�A�C�e���Ő搧�U���̌��ʂ𑕔�����Ɛ搧�U���ɂ���
	if(eqp2==SOUBI_SENSEIKOUGEKI){
#ifdef PM_DEBUG
		if(((sp->agi_rand[cl2]%(100/atk2))==0)||sp->dbp.debug_flag&DEBUG_FLAG_SOUBI){
#else
		if((sp->agi_rand[cl2]%(100/atk2))==0){
#endif
			sensei2=1;
			//�Z�̃v���C�I���e�B�����Ȃ����́A���ʃG�t�F�N�g�̔����͂Ȃ�
			if(flag==0){
				sp->psp[cl2].wkw.sensei_flag=1;
			}
		}
	}

	//�������ʂŐ搧�U���ɂ���
	if(sp->psp[cl2].wkw.once_agi_up){
		sensei2=1;
	}

	//�A�C�e���Ō�U�U���̌��ʂ𑕔�����ƌ�U�U���ɂ���
	if(eqp2==SOUBI_KOUKOUNINARU){
		koukou2=1;
	}

	//�����ȑf�����p�����[�^�����[�N�Ɋi�[
	sp->psp_agi_point[cl1]=agi1;
	sp->psp_agi_point[cl2]=agi2;

	if(flag==0){
		command1=sp->client_act_work[cl1][ACT_PARA_SELECT_COMMAND];
		command2=sp->client_act_work[cl2][ACT_PARA_SELECT_COMMAND];
		wazapos1=sp->waza_no_pos[cl1];
		wazapos2=sp->waza_no_pos[cl2];
		if(command1==SELECT_FIGHT_COMMAND){
			if(sp->otf[cl1].waruagaki_flag){
				wazano1=WAZANO_WARUAGAKI;
			}
			else{
				wazano1=ST_ServerPokemonServerParamGet(sp,cl1,ID_PSP_waza1+wazapos1,NULL);
			}
		}
		if(command2==SELECT_FIGHT_COMMAND){
			if(sp->otf[cl2].waruagaki_flag){
				wazano2=WAZANO_WARUAGAKI;
			}
			else{
				wazano2=ST_ServerPokemonServerParamGet(sp,cl2,ID_PSP_waza1+wazapos2,NULL);
			}
		}
//		attackpri1=WT_WazaDataParaGet(wazano1,ID_WTD_attackpri);
//		attackpri2=WT_WazaDataParaGet(wazano2,ID_WTD_attackpri);
		attackpri1=sp->AIWT.wtd[wazano1].attackpri;
		attackpri2=sp->AIWT.wtd[wazano2].attackpri;
	}

	if(attackpri1==attackpri2){
		//�搧�v���C�I���e�B���ꏏ�̎��́A���񂹂��̃c���A���������̂����ہA���Ƃ����A�g���b�N���[���̏��Ō���
		if((sensei1)&&(sensei2)){
			if(agi1<agi2){
				ret=1;
			}
			else if((agi1==agi2)&&(gf_rand()&1)){
				ret=2;
			}
		}
		else if((sensei1==0)&&(sensei2)){
			ret=1;
		}
		else if((sensei1)&&(sensei2==0)){
			ret=0;
		}
		else if((koukou1)&&(koukou2)){
			if(agi1>agi2){
				ret=1;
			}
			else if((agi1==agi2)&&(gf_rand()&1)){
				ret=2;
			}
		}
		else if((koukou1)&&(koukou2==0)){
			ret=1;
		}
		else if((koukou1==0)&&(koukou2)){
			ret=0;
		}
		else if((speabi1==TOKUSYU_ATODASI)&&(speabi2==TOKUSYU_ATODASI)){
			if(agi1>agi2){
				ret=1;
			}
			else if((agi1==agi2)&&(gf_rand()&1)){
				ret=2;
			}
		}
		else if((speabi1==TOKUSYU_ATODASI)&&(speabi2!=TOKUSYU_ATODASI)){
			ret=1;
		}
		else if((speabi1!=TOKUSYU_ATODASI)&&(speabi2==TOKUSYU_ATODASI)){
			ret=0;
		}
		else if(sp->field_condition&FIELD_CONDITION_TRICKROOM){
			if(agi1>agi2){
				ret=1;
			}
			if((agi1==agi2)&&(gf_rand()&1)){
				ret=2;
			}
		}
		else{
			if(agi1<agi2){
				ret=1;
			}
			if((agi1==agi2)&&(gf_rand()&1)){
				ret=2;
			}
		}
	}
	else if(attackpri1<attackpri2){
		ret=1;
	}

	return	ret;
}

//============================================================================================
/**
 *	�o���l���l���ł��錠���t���O�̃N���A
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�N���A����N���C�A���g�i���o�[
 */
//============================================================================================
void	ST_ServerGetExpRightFlagClear(SERVER_PARAM *sp,int client_no)
{
	sp->get_exp_right_flag[(client_no>>1)&1]=0;
}

//============================================================================================
/**
 *	�o���l���l���ł��錠���t���O�̃Z�b�g
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\���̃|�C���^
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�Z�b�g����N���C�A���g�i���o�[
 */
//============================================================================================
void	ST_ServerGetExpRightFlagSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	no;
	u32	fight_type;

	no=CLIENT_NO_MINE;
	fight_type=BattleWorkFightTypeGet(bw);

	while(no<=CLIENT_NO_MINE2){
		if( ((sp->no_reshuffle_client&No2Bit(no))==0) && 
			((sp->no_reshuffle_client&No2Bit(client_no))==0) &&
			(sp->psp[client_no].hp) ){
			sp->get_exp_right_flag[(client_no>>1)&1]|=No2Bit(sp->sel_mons_no[no]);
		}
		no+=2;
		if((fight_type==FIGHT_TYPE_2vs2_YASEI)||(fight_type==FIGHT_TYPE_AI_MULTI)){
			break;
		}
	}
}

//============================================================================================
/**
 *	�o���l���l���ł��錠���t���O�̃��Z�b�g
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	���Z�b�g����N���C�A���g�i���o�[
 */
//============================================================================================
void	ST_ServerGetExpRightFlagReset(SERVER_PARAM *sp,int client_no)
{
	int	no;

	no=CLIENT_NO_MINE;

	while(no<=CLIENT_NO_MINE2){
		if( ((sp->no_reshuffle_client&No2Bit(no))==0) && ((sp->no_reshuffle_client&No2Bit(client_no))==0) ){
			sp->get_exp_right_flag[(client_no>>1)&1]&=(No2Bit(sp->sel_mons_no[no])^0xffffffff);
		}
		no+=2;
	}
}

//============================================================================================
/**
 *	�ǉ����ʂ̃`�F�b�N�i���ڒǉ��̂݁j
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[out]	seq_no		�ǉ����ʂ����邽�߂̃T�u�V�[�P���X�i���o�[
 */
//============================================================================================
BOOL	ST_ServerAddStatusDirectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret=FALSE;

	if(sp->add_status_flag_direct&ADD_STATUS_WAZAKOUKA){
		//�Z���ʂ̒ǉ��́A100%�N��
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_DIRECT,sp->add_status_flag_direct);
		sp->add_status_flag_direct=0;
		//�͂���Ŏ��s�ɂ���
		if((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0){
			ret=TRUE;
		}
	}
	else if(sp->add_status_flag_direct){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_DIRECT,sp->add_status_flag_direct);
		//�C�₵�Ă��鑊��ɂ͎��s������
		if((sp->psp[sp->tsuika_client].hp)&&
		//�Z���ʂ̒ǉ��ł͂���𖳎�����w�肪�Ȃ����́A�͂���Ŏ��s�ɂ���
		  (((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)||
		   ((sp->add_status_flag_direct&ADD_STATUS_WAZAKOUKA_KAWARAWARI)&&
		    (sp->waza_status_flag&WAZA_STATUS_FLAG_KAWARAWARI))||
		   ((sp->add_status_flag_direct&ADD_STATUS_WAZAKOUKA_NOHIT)&&
		    (sp->waza_status_flag&WAZA_STATUS_FLAG_NOHIT_CHG)))){
			ret=TRUE;
		}
		sp->add_status_flag_direct=0;
	}

	return ret;
}

//============================================================================================
/**
 *	�ǉ����ʂ̃`�F�b�N�i���ڒǉ��ȊO�j
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[out]	seq_no		�ǉ����ʂ����邽�߂̃T�u�V�[�P���X�i���o�[
 */
//============================================================================================
BOOL	ST_ServerAddStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret=FALSE;
	u16		kakuritsu;

	//�Z���ʂ̒ǉ��́A100%�N��
	if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//�͂���Ŏ��s�ɂ���
		if(((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
			ret=TRUE;
		}
	}
	//�Z���ʂ̒ǉ��́A100%�N��
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_NOHP){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//�݂���肪����ꍇ�́A���s�ɂ���@�͂���Ŏ��s�ɂ���
		if((ST_ServerMigawariCheck(sp,sp->tsuika_client)==FALSE)&&
		   ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
			ret=TRUE;
		}
	}
	//�Z���ʂ̒ǉ��́A100%�N��
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_CHECK){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//�C�₵�Ă��鑊��ɂ͎��s������ �݂���肪����ꍇ�́A���s�ɂ���@�͂���Ŏ��s�ɂ���
		if((sp->psp[sp->tsuika_client].hp)&&
		  (ST_ServerMigawariCheck(sp,sp->tsuika_client)==FALSE)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
			ret=TRUE;
		}
	}
	//�Z���ʂ̒ǉ��́A100%�N��
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_NOHIT){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//�C�₵�Ă��鑊��ɂ͎��s������
		if(sp->psp[sp->tsuika_client].hp){
			ret=TRUE;
		}
	}
	//�Z���ʂ̒ǉ��́A100%�N��
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_PROB){
		//����\�͂Ă�̂߂��݂́A�m����{�ɂ���
		if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_TENNOMEGUMI){
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect)*2;
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect*2;
		}
		else{
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect);
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect;
		}
		//�ԐڂŊm���O�͂��肦�Ȃ��̂ŁA�A�T�[�g
		GF_ASSERT(kakuritsu!=0);
#ifdef PM_DEBUG
		if(((gf_rand()%100)<kakuritsu)||(sp->dbp.debug_flag&DEBUG_FLAG_ADD_STATUS)){
			//�ǉ����ʋN���ɂȂ�����A�t���O���I���ɂ���
			sp->server_status_flag|=SERVER_STATUS_FLAG_TSUIKA;
		}
#else
		if((gf_rand()%100)<kakuritsu){
			//�ǉ����ʋN���ɂȂ�����A�t���O���I���ɂ���
			sp->server_status_flag|=SERVER_STATUS_FLAG_TSUIKA;
		}
#endif
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//�C�₵�Ă��鑊��ɂ͎��s������
		if(sp->psp[sp->tsuika_client].hp==0){
			sp->server_status_flag&=SERVER_STATUS_FLAG_TSUIKA_OFF;
		}
		ret=TRUE;
	}
	else if(sp->add_status_flag_indirect){
		//����\�͂Ă�̂߂��݂́A�m����{�ɂ���
		if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_TENNOMEGUMI){
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect)*2;
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect*2;
		}
		else{
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect);
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect;
		}
		//�ԐڂŊm���O�͂��肦�Ȃ��̂ŁA�A�T�[�g
		GF_ASSERT(kakuritsu!=0);
#ifdef PM_DEBUG
		if(((gf_rand()%100)<kakuritsu)||(sp->dbp.debug_flag&DEBUG_FLAG_ADD_STATUS)){
			seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
			sp->add_status_flag_indirect=0;
			//�C�₵�Ă��鑊��ɂ͎��s������ �݂���肪����ꍇ�́A���s�ɂ���@�͂���Ŏ��s�ɂ���
			if((sp->psp[sp->tsuika_client].hp)&&
			   (ST_ServerMigawariCheck(sp,sp->tsuika_client)==FALSE)&&
			   (sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0){
				ret=TRUE;
			}
		}
#else
		if((gf_rand()%100)<kakuritsu){
			seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
			sp->add_status_flag_indirect=0;
			//�C�₵�Ă��鑊��ɂ͎��s������ �݂���肪����ꍇ�́A���s�ɂ���@�͂���Ŏ��s�ɂ���
			if((sp->psp[sp->tsuika_client].hp)&&
			   (ST_ServerMigawariCheck(sp,sp->tsuika_client)==FALSE)&&
			   (sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0){
				ret=TRUE;
			}
		}
#endif PM_DEBUG
	}
	else if(sp->add_status_flag_tokusei){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_TOKUSEI,sp->add_status_flag_tokusei);
		sp->add_status_flag_tokusei=0;
		//�C�₵�Ă��鑊��ɂ͎��s������
		if(sp->psp[sp->tsuika_client].hp){
			ret=TRUE;
		}
	}

	return ret;
}

//============================================================================================
/**
 * @brief	�U���Ώۂ��Z�b�g
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	attack		�U����ClientNo
 * @param[in]	waza_no		�J��o�����Ƃ��Ă���Z
 * @param[in]	flag		0:DirSelect�ŃZ�b�g�����l 1:�Ώۂ������_���őI��
 * @param[in]	range		waza_no��0�̎��ɗL����RANGE�l
 *
 * @retval	�Z�b�g����ClientNo
 */
//============================================================================================
int		ST_ServerDefenceClientSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 waza_no,int flag,int set_range)
{
	int	defence;
	int	range;

	defence=NONE_CLIENT_NO;

	if(waza_no){
//		range=WT_WazaDataParaGet(waza_no,ID_WTD_attackrange);
		range=sp->AIWT.wtd[waza_no].attackrange;
	}
	else{
		range=set_range;
	}

	if(range==RANGE_DOUBLE){
		{
			int	client_no;
			int	client_set_max=BattleWorkClientSetMaxGet(bw);
			CLIENT_PARAM *cp=BattleWorkClientParamGet(bw,attack);
			u8	flag=CT_CPClientTypeGet(cp);

			for(sp->client_loop=0;sp->client_loop<client_set_max;sp->client_loop++){
				client_no=sp->psp_agi_work[sp->client_loop];
				if(sp->psp[client_no].hp!=0){
					cp=BattleWorkClientParamGet(bw,client_no);
					if( ((flag&CLIENT_ENEMY_FLAG)&&((CT_CPClientTypeGet(cp)&CLIENT_ENEMY_FLAG)==0))||
						((flag&CLIENT_ENEMY_FLAG)==0)&&(CT_CPClientTypeGet(cp)&CLIENT_ENEMY_FLAG)){
						defence=client_no;
						break;
					}
				}
			}
			if(sp->client_loop!=client_set_max){
				sp->client_loop++;
			}
		}
	}
	else if(range==RANGE_TRIPLE){
		{
			int	client_no;
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);

			for(sp->client_loop=0;sp->client_loop<client_set_max;sp->client_loop++){
				client_no=sp->psp_agi_work[sp->client_loop];
				if(sp->psp[client_no].hp!=0){
					if(client_no!=attack){
						defence=client_no;
						break;
					}
				}
			}
			if(sp->client_loop!=client_set_max){
				sp->client_loop++;
			}
		}
	}
	//��т��ӂ�ȂǂŁA�Ώۂ�I�΂��ɋZ���o�����̏���
	else if((range==RANGE_TUBOWOTUKU)&&(flag==1)){
		{
			int	fight_type;

			fight_type=BattleWorkFightTypeGet(bw);

			if((fight_type&FIGHT_TYPE_2vs2)&&((gf_rand()%2)==0)){
				defence=BattleWorkPartnerClientNoGet(bw,attack);
				if(sp->psp[defence].hp==0){
					defence=attack;
				}
			}
			else{
				defence=attack;
			}
		}
	}
	//��т��ӂ�ȂǂŁA�Ώۂ�I�΂��ɋZ���o�����̏���
	else if((range==RANGE_SAKIDORI)&&(flag==1)){
		defence=ST_ServerDirClientGet(bw,sp,attack);
	}
	else if(range==RANGE_MAKIBISHI){
		defence=ST_ServerDirClientGet(bw,sp,attack);
	}
	else if((range==RANGE_MINE)||(range==RANGE_MINE_DOUBLE)||(range==RANGE_NONE)||(range==RANGE_FIELD)){
		defence=attack;
	}
	else if(range==RANGE_TEDASUKE){
		{
			int	fight_type;

			fight_type=BattleWorkFightTypeGet(bw);

			if(fight_type&FIGHT_TYPE_2vs2){
				defence=BattleWorkPartnerClientNoGet(bw,attack);
			}
			else{
				defence=attack;
			}
		}
	}
	else if(range==RANGE_TUBOWOTUKU){
		{
			int	fight_type;

			fight_type=BattleWorkFightTypeGet(bw);

			if(fight_type&FIGHT_TYPE_2vs2){
				defence=sp->client_act_work[attack][ACT_PARA_CLIENT_NO];
				if(sp->psp[defence].hp==0){
					defence=attack;
				}
			}
			else{
				defence=attack;
			}
		}
	}
	else if((range==RANGE_RANDOM)||(flag==1)){
		{
			int	fight_type;
			int	dir;
			int	def[2];
//			int	wazatype;

			fight_type=BattleWorkFightTypeGet(bw);
			dir=BattleWorkMineEnemyCheck(bw,attack)^1;
			def[0]=BattleWorkEnemyClientNoGet(bw,attack,BWECNG_SIDE_RIGHT);
			def[1]=BattleWorkEnemyClientNoGet(bw,attack,BWECNG_SIDE_LEFT);

#if 0
			//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
			if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_NOOMARUSUKIN){
				wazatype=NORMAL_TYPE;
			}
			else if(sp->waza_type){
				wazatype=sp->waza_type;
			}
			else{
				wazatype=sp->AIWT.wtd[waza_no].wazatype;
			}
#endif

			if(fight_type&FIGHT_TYPE_2vs2){
				//���̂�тƂ܂ꂪ����Ȃ�A������I��
				if((sp->scw[dir].konoyubitomare_flag)&&(sp->psp[sp->scw[dir].konoyubitomare_client].hp)){
					defence=sp->scw[dir].konoyubitomare_client;
				}
				//��������Ȃ�A�����_���őI��
				else if((sp->psp[def[0]].hp)&&(sp->psp[def[1]].hp)){
					dir=gf_rand()&1;
					defence=def[dir];
#if 0	//�`�F�b�N�ꏊ�ړ�
					//�Z�^�C�v���ł񂫂ŁA�����Ђ炢����������Ă���z��������A������I��
					if((wazatype==ELECTRIC_TYPE)&&
					   (ST_ServerTokuseiGet(sp,defence)!=TOKUSYU_HIRAISIN)&&
					   (ST_ServerKatayaburiTokuseiCheck(sp,attack,def[dir^1],TOKUSYU_HIRAISIN)==TRUE)){
						defence=def[dir^1];
						sp->ostf[defence].hiraisin_flag=1;
					}
					//�Z�^�C�v���݂��ŁA������т݂��������Ă���z��������A������I��
					if((wazatype==WATER_TYPE)&&
					   (ST_ServerTokuseiGet(sp,defence)!=TOKUSYU_YOBIMIZU)&&
					   (ST_ServerKatayaburiTokuseiCheck(sp,attack,def[dir^1],TOKUSYU_YOBIMIZU)==TRUE)){
						defence=def[dir^1];
						sp->ostf[defence].yobimizu_flag=1;
					}
#endif
				}
				//�ǂ������Ȃ�A�������I��
				else if(sp->psp[def[0]].hp){
					defence=def[0];
				}
				else if(sp->psp[def[1]].hp){
					defence=def[1];
				}
			}
			else{
				if(sp->psp[attack^1].hp){
					defence=attack^1;
				}
			}
		}
	}
	else{
		{
			int	dir;
			int	def_no;
			int	client_set_max;
//			int	wazatype;

			dir=BattleWorkMineEnemyCheck(bw,attack)^1;
			def_no=sp->client_act_work[attack][ACT_PARA_CLIENT_NO];
			client_set_max=BattleWorkClientSetMaxGet(bw);

#if 0
			//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
			if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_NOOMARUSUKIN){
				wazatype=NORMAL_TYPE;
			}
			else if(sp->waza_type){
				wazatype=sp->waza_type;
			}
			else{
				wazatype=sp->AIWT.wtd[waza_no].wazatype;
			}
#endif

			//���̂�тƂ܂ꂪ����Ȃ�A������I��
			if((sp->scw[dir].konoyubitomare_flag)&&(sp->psp[sp->scw[dir].konoyubitomare_client].hp)){
				defence=sp->scw[dir].konoyubitomare_client;
			}
			else{
#if 0	//�`�F�b�N�ꏊ�ړ�
				//����������Ԃ�ł͂Ȃ��Ƃ��́A�Ђ炢����Ƃ�т݂��`�F�b�N������
				if(ST_ServerTokuseiGet(sp,attack)!=TOKUSYU_KATAYABURI){
					//�Z�^�C�v���ł񂫂ŁA�����Ђ炢����������Ă���z��������A������I��
					if((wazatype==ELECTRIC_TYPE)&&
					   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE_HP,attack,TOKUSYU_HIRAISIN))){
						for(def_no=0;def_no<client_set_max;def_no++){
							defence=sp->psp_agi_work[def_no];
							if((ST_ServerTokuseiGet(sp,defence)==TOKUSYU_HIRAISIN)&&
							   (sp->psp[defence].hp)&&
							   (attack!=defence)){
								break;
							}
						}
						if(defence!=sp->client_act_work[attack][ACT_PARA_CLIENT_NO]){
							sp->ostf[defence].hiraisin_flag=1;
						}
					}
					//�Z�^�C�v���݂��ŁA������т݂��������Ă���z��������A������I��
					else if((wazatype==WATER_TYPE)&&
							(ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE_HP,attack,TOKUSYU_YOBIMIZU))){
						for(def_no=0;def_no<client_set_max;def_no++){
							defence=sp->psp_agi_work[def_no];
							if((ST_ServerTokuseiGet(sp,defence)==TOKUSYU_YOBIMIZU)&&
							   (sp->psp[defence].hp)&&
							   (attack!=defence)){
								break;
							}
						}
						if(defence!=sp->client_act_work[attack][ACT_PARA_CLIENT_NO]){
							sp->ostf[defence].yobimizu_flag=1;
						}
					}
					//�U���Ώۂ��C�₵�Ă�����A�ႤClient�ɃX�C�b�`
					else if(sp->psp[def_no].hp){
						defence=def_no;
					}
					else{
						def_no=ST_ServerDirClientGet(bw,sp,attack);
						if(sp->psp[def_no].hp){
							defence=def_no;
						}
					}
				}
#endif
				//�U���Ώۂ��C�₵�Ă�����A�ႤClient�ɃX�C�b�`
//				else if(sp->psp[def_no].hp){
				if(sp->psp[def_no].hp){
					defence=def_no;
				}
				else{
					def_no=ST_ServerDirClientGet(bw,sp,attack);
					if(sp->psp[def_no].hp){
						defence=def_no;
					}
				}
			}
		}
	}

	return defence;
}

//============================================================================================
/**
 * @brief	�U���Ώۂ�ς�������̃`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	attack		�U����ClientNo
 * @param[in]	waza_no		�J��o�����Ƃ��Ă���Z
 *
 * @retval	TRUE:�U���Ώۂ��ς�����@FALSE:�U���Ώۂ��̂܂�
 */
//============================================================================================
void	ST_ServerDefenceClientTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 waza_no)
{
	int		dir;
	int		client;
	int		defence;
	int		wazatype;
	int		client_set_max;

	//�Ώۂ����Ȃ���΁A�`�F�b�N�Ȃ�
	if(sp->defence_client==NONE_CLIENT_NO){
		return;
	}

	//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���Ȃ̂ŁA�`�F�b�N�Ȃ�
	//����������Ԃ�́A�֌W�Ȃ��Z���ł�̂ŁA�`�F�b�N�Ȃ�
	if((ST_ServerTokuseiGet(sp,attack)==TOKUSYU_NOOMARUSUKIN)||
	   (ST_ServerTokuseiGet(sp,attack)==TOKUSYU_KATAYABURI)){
		return;
	}
	dir=BattleWorkMineEnemyCheck(bw,attack)^1;
	//���̂�тƂ܂��D�悷��̂ŁA�`�F�b�N�Ȃ�
	if((sp->scw[dir].konoyubitomare_flag)&&(sp->psp[sp->scw[dir].konoyubitomare_client].hp)){
		return;
	}

#if B1366_060815_FIX
	wazatype=ST_AIWazaTypeGet(bw,sp,attack,waza_no);
	if(wazatype==0){
		wazatype=sp->AIWT.wtd[waza_no].wazatype;
	}
#else //B1366_060815_FIX
	if(sp->waza_type){
		wazatype=sp->waza_type;
	}
	else{
		wazatype=sp->AIWT.wtd[waza_no].wazatype;
	}
#endif //B1366_060815_FIX

	client_set_max=BattleWorkClientSetMaxGet(bw);

	//�Z�^�C�v���ł񂫂ŁA�����Ђ炢����������Ă���z��������A������I��
	if((wazatype==ELECTRIC_TYPE)&&
	  ((sp->AIWT.wtd[waza_no].attackrange==RANGE_NORMAL)||
	   (sp->AIWT.wtd[waza_no].attackrange==RANGE_RANDOM))&&
	  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE_HP,attack,TOKUSYU_HIRAISIN))){
		for(client=0;client<client_set_max;client++){
			defence=sp->psp_agi_work[client];
			if((ST_ServerTokuseiGet(sp,defence)==TOKUSYU_HIRAISIN)&&
			   (sp->psp[defence].hp)&&
			   (attack!=defence)){
				break;
			}
		}
		if(defence!=sp->defence_client){
			sp->ostf[defence].hiraisin_flag=1;
			sp->defence_client=defence;
		}
	}
	//�Z�^�C�v���݂��ŁA������т݂��������Ă���z��������A������I��
	else if((wazatype==WATER_TYPE)&&
		   ((sp->AIWT.wtd[waza_no].attackrange==RANGE_NORMAL)||
			(sp->AIWT.wtd[waza_no].attackrange==RANGE_RANDOM))&&
		   ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
			(ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE_HP,attack,TOKUSYU_YOBIMIZU))){
		for(client=0;client<client_set_max;client++){
			defence=sp->psp_agi_work[client];
			if((ST_ServerTokuseiGet(sp,defence)==TOKUSYU_YOBIMIZU)&&
			   (sp->psp[defence].hp)&&
			   (attack!=defence)){
				break;
			}
		}
		if(defence!=sp->defence_client){
			sp->ostf[defence].yobimizu_flag=1;
			sp->defence_client=defence;
		}
	}
}

//============================================================================================
/**
 * @brief	�U���Ώۂ�ς�������̋N��
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 *
 * @retval	TRUE:�U���Ώۂ��ς�����@FALSE:�U���Ώۂ��̂܂�
 */
//============================================================================================
BOOL	ST_ServerDefenceClientTokuseiAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret=FALSE;

	//�Ђ炢����`�F�b�N
	if(((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
	    (sp->ostf[sp->defence_client].hiraisin_flag)){
	    sp->ostf[sp->defence_client].hiraisin_flag=0;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HIRAISIN);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		ret=TRUE;
	}
	//��т݂��`�F�b�N
	if(((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
	    (sp->ostf[sp->defence_client].yobimizu_flag)){
	    sp->ostf[sp->defence_client].yobimizu_flag=0;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HIRAISIN);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		ret=TRUE;
	}

	return ret;
}

//============================================================================================
/**
 *	PokemonServerParam����K�v�ȃf�[�^�̂�PokemonParam�ɏ����߂�
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�ǂݏ�������client_no
 */
//============================================================================================
void	ST_PSPtoPPCopy(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	//�A�C�e���������Ă��Ȃ��Ȃ�AAI�p�̃��[�N���N���A���Ă���
	if(sp->psp[client_no].item==0){
		SoubiItemClear(sp,client_no);
	}
	SCIO_PSPtoPPCopy(bw,sp,client_no);
}

//============================================================================================
/**
 *	���ߌn�̃t���O�𗧂Ă�
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�t���O�𗧂Ă�client_no
 */
//============================================================================================
void	ST_ServerKeepOn(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	sp->psp[client_no].condition2|=CONDITION2_KEEP;
	sp->waza_no_keep[client_no]=sp->waza_no_now;
}

//============================================================================================
/**
 *	���ߌn�̃t���O�𗎂Ƃ�
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�t���O�𗎂Ƃ�client_no
 */
//============================================================================================
void	ST_ServerKeepOff(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	sp->psp[client_no].condition2&=CONDITION2_KEEP_OFF;
	sp->psp[client_no].condition2&=CONDITION2_GAMAN_OFF;
	sp->psp[client_no].waza_kouka&=WAZAKOUKA_KIE_OFF;
	sp->psp[client_no].wkw.korogaru_count=0;
	sp->psp[client_no].wkw.renzokugiri_count=0;
}

//============================================================================================
/**
 *	�R���f�B�V��������A��Ԉُ�i���o�[��Ԃ�
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	��Ԉُ���`�F�b�N����client_no
 */
//============================================================================================
int		ST_ServerConditionNoGet(SERVER_PARAM *sp,int client_no)
{
	if(sp->psp[client_no].condition&CONDITION_NEMURI){
		return STATUS_NEMURI;
	}
	else if(sp->psp[client_no].condition&CONDITION_DOKU){
		return STATUS_DOKU;
	}
	else if(sp->psp[client_no].condition&CONDITION_YAKEDO){
		return STATUS_YAKEDO;
	}
	else if(sp->psp[client_no].condition&CONDITION_KOORI){
		return STATUS_KOORI;
	}
	else if(sp->psp[client_no].condition&CONDITION_MAHI){
		return STATUS_MAHI;
	}
	else if(sp->psp[client_no].condition&CONDITION_DOKUDOKU){
		return STATUS_DOKU;
	}
	return STATUS_NORMAL;
}

//============================================================================================
/**
 *	�퓬���Ƀg���[�i�[���o�Ă��ĕ\�����郁�b�Z�[�W�`�F�b�N�̃V�[�P���X�i���o�[
 */
//============================================================================================
enum{
	SEQ_STMC_FIRST_DAMAGE=0,
	SEQ_STMC_HP_HALF,
	SEQ_STMC_POKE_LAST,
	SEQ_STMC_POKE_LAST_HP_HALF,
	SEQ_STMC_END
};

//============================================================================================
/**
 *	�퓬���Ƀg���[�i�[���o�Ă��ĕ\�����郁�b�Z�[�W�`�F�b�N
 *
 * @param[in]	bw		�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp		�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
BOOL	ST_ServerTrainerMessageCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	fight_type;
	int	tr_id;
	int seq_no;

	fight_type=BattleWorkFightTypeGet(bw);

	//�ʐM�ΐ�A�o�g���^���[�́A���肵�Ȃ�
	if(fight_type&(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)){
		return FALSE;
	}
	//�g���[�i�[��ł͂Ȃ���΁A���肵�Ȃ�
	if((fight_type&FIGHT_TYPE_TRAINER)==0){
		return FALSE;
	}

	//2vs2�́A���肵�Ȃ�
	if(fight_type&FIGHT_TYPE_2vs2){
		return FALSE;
	}

	tr_id=BattleWorkTrainerIDGet(bw,CLIENT_NO_ENEMY);
	seq_no=SEQ_STMC_FIRST_DAMAGE;

	do{
		switch(seq_no){
		//�퓬���F����|�P�����ɍŏ��̃_���[�W��^�����Ƃ��i�����̂����Ă��Ă��ŏ���1�̂ɂ����\���j
		case SEQ_STMC_FIRST_DAMAGE:
			if((sp->psp[CLIENT_NO_ENEMY].hit_count==1)&&
//			  ((sp->psp[CLIENT_NO_ENEMY].message_flag&TRAINER_MESSAGE_FLAG_FIRST_DAMAGE)==0)){
			  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_FIRST_DAMAGE_MSG)==0)){
				if(TT_TrainerMessageCheck(tr_id,TRMSG_FIGHT_FIRST_DAMAGE,HEAPID_BATTLE)){
//					sp->psp[CLIENT_NO_ENEMY].message_flag|=TRAINER_MESSAGE_FLAG_FIRST_DAMAGE;
					sp->server_status_flag2|=SERVER_STATUS_FLAG2_FIRST_DAMAGE_MSG;
					sp->msg_work=TRMSG_FIGHT_FIRST_DAMAGE;
					return TRUE;
				}
			}
			seq_no++;
			break;
		//�퓬���F����|�P�����̂g�o�����ȉ�
		case SEQ_STMC_HP_HALF:
			if((sp->psp[CLIENT_NO_ENEMY].message_flag&TRAINER_MESSAGE_FLAG_POKE_HP_HALF)==0){
				if(sp->psp[CLIENT_NO_ENEMY].hp<=(sp->psp[CLIENT_NO_ENEMY].hpmax/2)){
					if(TT_TrainerMessageCheck(tr_id,TRMSG_FIGHT_POKE_HP_HALF,HEAPID_BATTLE)){
						sp->psp[CLIENT_NO_ENEMY].message_flag|=TRAINER_MESSAGE_FLAG_POKE_HP_HALF;
						sp->msg_work=TRMSG_FIGHT_POKE_HP_HALF;
						return TRUE;
					}
				}
			}
			seq_no++;
			break;
		//�퓬���F����|�P�������c��P�C
		case SEQ_STMC_POKE_LAST:
			if((sp->psp[CLIENT_NO_ENEMY].message_flag&TRAINER_MESSAGE_FLAG_POKE_LAST)==0){
				{
					int	i;
					int	cnt;
					POKEPARTY		*poke_party;
					POKEMON_PARAM	*pp;

					poke_party=BattleWorkPokePartyGet(bw,CLIENT_NO_ENEMY);
					cnt=0;
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=PokeParty_GetMemberPointer(poke_party,i);
						if(PokeParaGet(pp,ID_PARA_hp,NULL)){
							cnt++;
						}
					}
					if(cnt==1){
						if(TT_TrainerMessageCheck(tr_id,TRMSG_FIGHT_POKE_LAST,HEAPID_BATTLE)){
							sp->psp[CLIENT_NO_ENEMY].message_flag|=TRAINER_MESSAGE_FLAG_POKE_LAST;
							sp->msg_work=TRMSG_FIGHT_POKE_LAST;
							return TRUE;
						}
					}
				}
			}
			seq_no++;
			break;
		//�퓬���F����|�P�������c��P�C�łg�o�����ȉ�
		case SEQ_STMC_POKE_LAST_HP_HALF:
			if((sp->psp[CLIENT_NO_ENEMY].message_flag&TRAINER_MESSAGE_FLAG_POKE_LAST_HP_HALF)==0){
				{
					int	i;
					int	cnt;
					POKEPARTY		*poke_party;
					POKEMON_PARAM	*pp;

					poke_party=BattleWorkPokePartyGet(bw,CLIENT_NO_ENEMY);
					cnt=0;
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=PokeParty_GetMemberPointer(poke_party,i);
						if(PokeParaGet(pp,ID_PARA_hp,NULL)){
							cnt++;
						}
					}
					if((cnt==1)&&(sp->psp[CLIENT_NO_ENEMY].hp<=(sp->psp[CLIENT_NO_ENEMY].hpmax/2))){
						if(TT_TrainerMessageCheck(tr_id,TRMSG_FIGHT_POKE_LAST_HP_HALF,HEAPID_BATTLE)){
							sp->psp[CLIENT_NO_ENEMY].message_flag|=TRAINER_MESSAGE_FLAG_POKE_LAST_HP_HALF;
							sp->msg_work=TRMSG_FIGHT_POKE_LAST_HP_HALF;
							return TRUE;
						}
					}
				}
			}
			seq_no++;
			break;
		case SEQ_STMC_END:
			break;
		}
	}while(seq_no!=SEQ_STMC_END);

	return FALSE;
}

//============================================================================================
/**
 *	ServerWork�̏�����
 *
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerWorkInit(SERVER_PARAM *sp)
{
	int	client_no;

	sp->damage=0;							///<�Z�ɂ��_���[�W���[�N
	sp->critical=1;							///<�N���e�B�J���q�b�g���[�N
	sp->critical_count=0;					///<�N���e�B�J���`�F�b�N�Ɏg�p����N���e�B�J���̏o�₷���{�����[�N
	sp->damage_power=0;						///<�Z�ɂ��U���̓��[�N
	sp->damage_value=10;					///<�Z�ɂ��_���[�W�{�����[�N
	sp->waza_type=0;						///<�Z�^�C�v���[�N
	sp->waza_eff_cnt=0;						///<�Z�G�t�F�N�g�J�E���^

	sp->waza_status_flag=0;					///<�Z�������������Ƃŕω�����t���O

	sp->kizetsu_client=NONE_CLIENT_NO;		///<�C�₵��ClientNo��������

	sp->add_status_flag_direct=0;			///<���ڒǉ����ʃt���O
	sp->add_status_flag_indirect=0;			///<�Ԑڒǉ����ʃt���O
	sp->add_status_flag_tokusei=0;			///<�����ɂ��ǉ����ʃt���O
	sp->tsuika_type=ADD_STATUS_NONE;		///<�ǉ����ʂ̎�ށi���ځA�ԐځA�����j
	sp->tsuika_para=ADD_COND_NONE;			///<�ǉ����ʂ̎�ށi�˂ނ�A�܂ЂƂ��j
	sp->tsuika_client=NONE_CLIENT_NO;		///<�ǉ����ʂ�����N���C�A���g

	sp->renzoku_count=0;					///<�A���U���p�J�E���^
	sp->renzoku_count_temp=0;				///<�A���U���p�J�E���^�i�\���p�j
	sp->client_loop=0;						///<�����̓�����Z�J�E���^
	sp->loop_flag=0;						///<���[�v�������t���O
	sp->swoam_type=0;						///<ServerWazaOutAfterMessage�p�^�C�v�i���o�[�i�[���[�N
	sp->waza_out_check_on_off=0;			///<HITCHECK�L���t���O
	sp->loop_hit_check=0;					///<���[�v��������HITCHECK�L���t���O

	sp->fcc_seq_no=0;						///<FieldConditionCheck�p�V�[�P���X�i���o�[�i�[���[�N
	sp->pcc_seq_no=0;						///<PokeConditionCheck�p�V�[�P���X�i���o�[�i�[���[�N
	sp->scc_seq_no=0;						///<SideConditionCheck�p�V�[�P���X�i���o�[�i�[���[�N
	sp->sba_seq_no=0;						///<ServerBeforeAct�p�V�[�P���X�i���o�[�i�[���[�N
	sp->swhac_seq_no=0;						///<ServerWazaHitAfterCheck�p�V�[�P���X�i���o�[�i�[���[�N
	sp->swoam_seq_no=0;						///<ServerWazaOutAfterMessage�p�V�[�P���X�i���o�[�i�[���[�N
	sp->swoak_seq_no=0;						///<ServerWazaOutAfterKouka�p�V�[�P���X�i���o�[�i�[���[�N
	sp->wb_seq_no=0;						///<WazaBefore�̃V�[�P���X�i���o�[
	sp->woc_seq_no=0;						///<WazaOutCheck�̃V�[�P���X�i���o�[
	sp->ssc_seq_no=0;						///<ServerStatusCheck�̃V�[�P���X�i���o�[
	sp->stc_seq_no=0;						///<ServerTokuseiCheck�̃V�[�P���X�i���o�[

	sp->server_status_flag&=SERVER_STATUS_FLAG_ATTACK_TURN;	//�����̃^�[�������L���ȃt���O��������
	sp->server_status_flag2&=SERVER_STATUS_FLAG2_ATTACK_TURN;	//�����̃^�[�������L���ȃt���O��������

	sp->magnitude=0;						///<�}�O�j�`���[�h�̑傫��

	for(client_no=0;client_no<CLIENT_MAX;client_no++){
		MI_CpuClearFast(&sp->ostf[client_no],sizeof(ONE_SELF_TURN_FLAG));		//�����̃^�[���̂ݐ����\�ȃ��[�N�Q
		sp->ai_reshuffle_sel_mons_no[client_no]=6;
	}

}

//============================================================================================
/**
 *	�J�E���^���[�N�̏�����
 *
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerCounterWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	fight_type;
	int	i;

	for(i=0;i<CLIENT_MAX;i++){
		sp->waza_no_hit_client[i]=NONE_CLIENT_NO;
		sp->reshuffle_sel_mons_no[i]=6;
		sp->agi_rand[i]=gf_rand();	///<�f�����`�F�b�N�Ɏg�p���闐���l
	}

	sp->okodukai_value=1;		///<���������̔{�����[�N

	sp->sakidori_total_turn=1;	///<�����ǂ�p�̃g�[�^���^�[���J�E���^

	fight_type=BattleWorkFightTypeGet(bw);

	if((fight_type&FIGHT_TYPE_2vs2)==0){
		sp->no_reshuffle_client|=No2Bit(CLIENT_NO_MINE2);
		sp->no_reshuffle_client|=No2Bit(CLIENT_NO_ENEMY2);
	}

	sp->safari_get_count=	SAFARI_COUNT_FLAT;		///<�T�t�@���̕ߊl���J�E���^
	sp->safari_escape_count=SAFARI_COUNT_FLAT;		///<�T�t�@���̓������J�E���^
}

//============================================================================================
/**
 *	�T�[�o���[�N�̏������i�|�P��������ւ����j
 *
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerReshuffleWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int				i;
	int				client_set_max;
	u32				fight_type;
	u8				*adr;
	WAZA_KOUKA_WORK	wkw_temp;

	wkw_temp=sp->psp[client_no].wkw;
	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);
	sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;

	if((sp->server_status_flag&SERVER_STATUS_FLAG_BATON_TOUCH)==0){
		for(i=0;i<client_set_max;i++){
			//�u���낢�܂Ȃ����v�A�u�N���̂��v���������������ւ������A���ʂ�����
			if((sp->psp[i].condition2&CONDITION2_KUROIMANAZASHI)&&(sp->psp[i].wkw.manazashi_client_no==client_no)){
				sp->psp[i].condition2&=CONDITION2_KUROIMANAZASHI_OFF;
			}
			//���b�N�I�����������������ւ����������A���ʂ�����
			if((sp->psp[i].waza_kouka&WAZAKOUKA_LOCKON)&&(sp->psp[i].wkw.lockon_client_no==client_no)){
				sp->psp[i].waza_kouka&=WAZAKOUKA_LOCKON_OFF;
				sp->psp[i].wkw.lockon_client_no=0;
			}
		}
		sp->psp[client_no].condition2=0;
		sp->psp[client_no].waza_kouka=0;
	}
	else{
		sp->psp[client_no].condition2&=CONDITION2_BATON_TOUCH_ON;
		sp->psp[client_no].waza_kouka&=WAZAKOUKA_BATON_TOUCH_ON;
		for(i=0;i<client_set_max;i++){
			//���b�N�I��������������o�g���^�b�`������A�J�E���^�����ɖ߂��Č��ʂ��p��
			if((sp->psp[i].waza_kouka&WAZAKOUKA_LOCKON)&&(sp->psp[i].wkw.lockon_client_no==client_no)){
				sp->psp[i].waza_kouka&=WAZAKOUKA_LOCKON_OFF;
				sp->psp[i].waza_kouka|=(LOCKON_COUNT*2);
			}
		}
	}

	for(i=0;i<client_set_max;i++){
	//�u���������v���������������ւ������A���ʂ�����
		if(sp->psp[i].condition2&(No2Bit(client_no)<<MEROMERO_SHIFT)){
			sp->psp[i].condition2&=((No2Bit(client_no)<<MEROMERO_SHIFT)^0xffffffff);
		}
	//���ߌn�̋Z���������������ւ������A���ʂ�����
		if((sp->psp[i].condition2&CONDITION2_SHIME)&&(sp->psp[i].wkw.shime_client_no==client_no)){
			sp->psp[i].condition2&=CONDITION2_SHIME_OFF;
		}
	}

	adr=(u8 *)&sp->psp[client_no].wkw;
	for(i=0;i<sizeof(WAZA_KOUKA_WORK);i++){
		adr[i]=0;
	}
	if(sp->server_status_flag&SERVER_STATUS_FLAG_BATON_TOUCH){
		sp->psp[client_no].wkw.migawari_hp=			wkw_temp.migawari_hp;
		sp->psp[client_no].wkw.lockon_client_no=	wkw_temp.lockon_client_no;
		sp->psp[client_no].wkw.horobinouta_count=	wkw_temp.horobinouta_count;
		sp->psp[client_no].wkw.manazashi_client_no=	wkw_temp.manazashi_client_no;
		sp->psp[client_no].wkw.denzihuyuu_count=	wkw_temp.denzihuyuu_count;
		sp->psp[client_no].wkw.shutout_count=		wkw_temp.shutout_count;
		sp->psp[client_no].wkw.healblock_count=		wkw_temp.healblock_count;
	}

	sp->psp[client_no].wkw.nekodamashi_count=sp->total_turn+1;		//�l�R���܂��J�E���^������
	sp->psp[client_no].wkw.slow_start_count=sp->total_turn+1;		//�X���[�X�^�[�g�J�E���^������
	//�Ȃ܂���^�[���i��E�����j���Z�b�g
	sp->psp[client_no].wkw.namake_bit=(sp->total_turn+1)&1;

	sp->waza_no_mamoru[client_no]=0;					///<1�^�[���O�ɌJ��o����Ă����Z�������������ǂ����i�܂����p�j
	sp->waza_no_hit[client_no]=0;						///<1�^�[���O�ɌJ��o����Ă����Z���󂯂����ǂ���
	sp->waza_no_hit_client[client_no]=NONE_CLIENT_NO;	///<1�^�[���O�ɌJ��o����Ă����Z�𔭓�����ClientNo
	sp->waza_no_hit_type[client_no]=0;					///<1�^�[���O�Ƀq�b�g�����Z�̃^�C�v
	sp->waza_no_old[client_no]=0;						///<1�^�[���O�ɌJ��o����Ă����Z
	sp->waza_no_oumu[client_no]=0;						///<���O�Ɏ󂯂��Z���i�[�i�I�E���������p�j
	sp->waza_no_oumu_hit[client_no][0]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_oumu_hit[client_no][1]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_oumu_hit[client_no][2]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_oumu_hit[client_no][3]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_sketch[client_no]=0;					///<�X�P�b�`�p�̋Z�i���o�[���[�N
#if GB002_060815_FIX
	sp->waza_no_texture2[client_no]=0;					///<1�^�[���O�ɌJ��o����Ă����Z���󂯂����ǂ����i�e�N�X�`���[�Q��p�j
	sp->waza_no_texture2_client[client_no]=0;			///<1�^�[���O�ɌJ��o����Ă����Z�𔭓�����Client�i�e�N�X�`���[�Q��p�j
	sp->waza_no_texture2_type[client_no]=0;				///<1�^�[���O�ɌJ��o����Ă����Z�̃^�C�v�i�e�N�X�`���[�Q��p�j
#endif //GB002_060815_FIX
#if GB003_060815_FIX
	sp->waza_no_metronome[client_no]=0;					///<���g���m�[���p�Z���[�N
#endif //GB003_060815_FIX

#if B1371_060815_FIX
	sp->field_condition&=((No2Bit(client_no)<<FIELD_SAWAGU_SHIFT)^0xffffffff);	//���킮�t���O�𗎂Ƃ�
#endif B1371_060815_FIX

	//�p���[�g���b�N�t���O�������Ă���ꍇ�́A�U���Ɩh��̒l�����ւ���
	if(sp->psp[client_no].waza_kouka&WAZAKOUKA_POWER_TRICK){
		i=sp->psp[client_no].pow;
		sp->psp[client_no].pow=sp->psp[client_no].def;
		sp->psp[client_no].def=i;
	}

///<�C�⎞�̊m�F�����Ă��鎞�ɓ���ւ����̕s��𔭌������̂�
///<����̃��[�N���N���A����悤�ɏC���iGB�łƓ����d�l�ɂȂ�܂��j
	for(i=0;i<client_set_max;i++){
		if((i!=client_no)&&(BattleWorkMineEnemyCheck(bw,i)!=BattleWorkMineEnemyCheck(bw,client_no))){
			sp->waza_no_oumu[i]=0;
		}
		sp->waza_no_oumu_hit[i][client_no]=0;
	}

	WazaNoStockClear(sp,client_no);		//AI�p�̋Z�i���o�[�X�g�b�N���[�N���N���A
	TokusyuNoClear(sp,client_no);		//AI�p�̓����i���o�[���[�N���N���A
	SoubiItemClear(sp,client_no);		//AI�p�̑����A�C�e���i���o�[���[�N���N���A
}

//============================================================================================
/**
 *	�T�[�o���[�N�̏������i�|�P�����C�⎞�j
 *
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerKizetsuWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int				i;
	int				client_set_max;
	u8				*adr;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(i=COND_HP;i<COND_MAX;i++){
		sp->psp[client_no].abiritycnt[i]=6;
	}

	sp->psp[client_no].condition2=0;
	sp->psp[client_no].waza_kouka=0;

	//�u���낢�܂Ȃ����v�A�u�N���̂��v������������C�₵����A���ʂ�����
	for(i=0;i<client_set_max;i++){
		if((sp->psp[i].condition2&CONDITION2_KUROIMANAZASHI)&&(sp->psp[i].wkw.manazashi_client_no==client_no)){
			sp->psp[i].condition2&=CONDITION2_KUROIMANAZASHI_OFF;
		}
	//�u���������v���������������ւ������A���ʂ�����
		if(sp->psp[i].condition2&(No2Bit(client_no)<<MEROMERO_SHIFT)){
			sp->psp[i].condition2&=((No2Bit(client_no)<<MEROMERO_SHIFT)^0xffffffff);
		}
	//���ߌn�̋Z���������������ւ������A���ʂ�����
		if((sp->psp[i].condition2&CONDITION2_SHIME)&&(sp->psp[i].wkw.shime_client_no==client_no)){
			sp->psp[i].condition2&=CONDITION2_SHIME_OFF;
		}
	}

	//���̃^�[���ɂ������Ă������ʌn��S�ď�����
	adr=(u8 *)&sp->psp[client_no].wkw;
	for(i=0;i<sizeof(WAZA_KOUKA_WORK);i++){
		adr[i]=0;
	}

	adr=(u8 *)&sp->otf[client_no];
	for(i=0;i<sizeof(ONE_TURN_FLAG);i++){
		adr[i]=0;
	}

	sp->psp[client_no].wkw.nekodamashi_count=sp->total_turn+1;		//�l�R���܂��J�E���^������
	sp->psp[client_no].wkw.slow_start_count=sp->total_turn+1;		//�X���[�X�^�[�g�J�E���^������
	//�Ȃ܂���^�[���i��E�����j���Z�b�g
	sp->psp[client_no].wkw.namake_bit=(sp->total_turn+1)&1;

	sp->waza_no_mamoru[client_no]=0;						///<1�^�[���O�ɌJ��o����Ă����Z�������������ǂ����i�܂����p�j
	sp->waza_no_hit[client_no]=0;						///<1�^�[���O�ɌJ��o����Ă����Z���󂯂����ǂ���
	sp->waza_no_hit_client[client_no]=NONE_CLIENT_NO;	///<1�^�[���O�ɌJ��o����Ă����Z�𔭓�����ClientNo
	sp->waza_no_hit_type[client_no]=0;					///<1�^�[���O�Ƀq�b�g�����Z�̃^�C�v
	sp->waza_no_old[client_no]=0;						///<1�^�[���O�ɌJ��o����Ă����Z
	sp->waza_no_oumu[client_no]=0;						///<���O�Ɏ󂯂��Z���i�[�i�I�E���������p�j
	sp->waza_no_oumu_hit[client_no][0]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_oumu_hit[client_no][1]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_oumu_hit[client_no][2]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_oumu_hit[client_no][3]=0;				///<���O�Ɏ󂯂��Z���i�[�i2vs2���̃I�E���������p�j
	sp->waza_no_sketch[client_no]=0;					///<�X�P�b�`�p�̋Z�i���o�[���[�N
#if GB002_060815_FIX
	sp->waza_no_texture2[client_no]=0;					///<1�^�[���O�ɌJ��o����Ă����Z���󂯂����ǂ����i�e�N�X�`���[�Q��p�j
	sp->waza_no_texture2_client[client_no]=0;			///<1�^�[���O�ɌJ��o����Ă����Z�𔭓�����Client�i�e�N�X�`���[�Q��p�j
	sp->waza_no_texture2_type[client_no]=0;				///<1�^�[���O�ɌJ��o����Ă����Z�̃^�C�v�i�e�N�X�`���[�Q��p�j
#endif //GB002_060815_FIX
#if GB003_060815_FIX
	sp->waza_no_metronome[client_no]=0;					///<���g���m�[���p�Z���[�N
#endif //GB003_060815_FIX

#if B1371_060815_FIX
	sp->field_condition&=((No2Bit(client_no)<<FIELD_SAWAGU_SHIFT)^0xffffffff);	//���킮�t���O�𗎂Ƃ�
#endif B1371_060815_FIX

///<�C�⎞�̊m�F�����Ă��鎞�ɓ���ւ����̕s��𔭌������̂�
///<����̃��[�N���N���A����悤�ɏC���iGB�łƓ����d�l�ɂȂ�܂��j
	for(i=0;i<client_set_max;i++){
		if((i!=client_no)&&(BattleWorkMineEnemyCheck(bw,i)!=BattleWorkMineEnemyCheck(bw,client_no))){
			sp->waza_no_oumu[i]=0;
		}
		sp->waza_no_oumu_hit[i][client_no]=0;
	}

	//����ւ����������ŋC�₵�Ă���ꍇ�́A���ꂩ���t���O���������ςȂ��Ȃ̂ŁA���Ƃ�
	sp->client_status[client_no]&=CLIENT_STATUS_POKE_RESHUFFLE_OFF;

	WazaNoStockClear(sp,client_no);		//AI�p�̋Z�i���o�[�X�g�b�N���[�N���N���A
	TokusyuNoClear(sp,client_no);		//AI�p�̓����i���o�[���[�N���N���A
	SoubiItemClear(sp,client_no);		//AI�p�̑����A�C�e���i���o�[���[�N���N���A
}

//============================================================================================
/**
 *	�P�^�[�������L���ȃt���O��������
 *
 * @param[in]	sp		�T�[�o�p�����[�^�̍\���̃|�C���^
 */
//============================================================================================
void	ST_ServerOneTurnFlagInit(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;

	for(client_no=0;client_no<CLIENT_MAX;client_no++){
		MI_CpuClearFast(&sp->otf[client_no],sizeof(ONE_TURN_FLAG));
		MI_CpuClearFast(&sp->wocf[client_no],sizeof(WAZA_OUT_CHECK_FLAG));
		sp->psp[client_no].condition2&=CONDITION2_HIRUMU_OFF;
		if(sp->psp[client_no].wkw.handou_count+1<sp->total_turn){
			sp->psp[client_no].condition2&=CONDITION2_HANDOU_OFF;
		}
		//�����Ă��鎞�ɏo�����A���ߋZ�n�́A���߂��͂����i�˂��Ƒ΍�j
		if((sp->psp[client_no].condition&CONDITION_NEMURI)&&(sp->psp[client_no].condition2&CONDITION2_KEEP)){
			ST_ServerKeepOff(bw,sp,client_no);
		}
		if((sp->psp[client_no].condition&CONDITION_NEMURI)&&(sp->psp[client_no].condition2&CONDITION2_ABARERU)){
			sp->psp[client_no].condition2&=CONDITION2_ABARERU_OFF;
		}
	}
	//���̂�тƂ܂�t���O���N���A
	sp->scw[0].konoyubitomare_flag=0;
	sp->scw[1].konoyubitomare_flag=0;
}

//============================================================================================
/**
 *	��邠�����ɂȂ邩�`�F�b�N
 *
 * @param[in]	bw				�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�`�F�b�N����ClientNo
 * @param[in]	check_bit	�`�F�b�N���鍀�ځibattle_common.h�ɒ�`�j
 */
//============================================================================================
int		ST_ServerWaruagakiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_bit,int check_bit)
{
	int	pos;
	int	eqp;

	eqp=ST_ServerSoubiEqpGet(sp,client_no);

	for(pos=0;pos<4;pos++){
		//�킴���Ȃ�
		if((sp->psp[client_no].waza[pos]==0)&&(check_bit&SSWC_WAZA_NONE)){
			waza_bit|=No2Bit(pos);
		}
		//PP���Ȃ�
		if((sp->psp[client_no].pp[pos]==0)&&(check_bit&SSWC_PP_NONE)){
			waza_bit|=No2Bit(pos);
		}
		//���Ȃ��΂肳��Ă�
		if((sp->psp[client_no].waza[pos]==sp->psp[client_no].wkw.kanashibari_wazano)&&(check_bit&SSWC_KANASHIBARI)){
			waza_bit|=No2Bit(pos);
		}
		//���������������Ă���
		if((sp->psp[client_no].waza[pos]==sp->waza_no_old[client_no])&&(check_bit&SSWC_ICHAMON)&&
		   (sp->psp[client_no].condition2&CONDITION2_ICHAMON)){
			waza_bit|=No2Bit(pos);
		}
		//���傤�͂���Ă���
		if((sp->psp[client_no].wkw.chouhatsu_count)&&(check_bit&SSWC_CHOUHATSU)&&
//	   	   (WT_WazaDataParaGet(sp->psp[client_no].waza[pos],ID_WTD_damage)==0)){
	   	   (sp->AIWT.wtd[sp->psp[client_no].waza[pos]].damage==0)){
			waza_bit|=No2Bit(pos);
		}
		//�ӂ����񂳂�Ă���
		if((ST_ServerHuuinCheck(bw,sp,client_no,sp->psp[client_no].waza[pos]))&&(check_bit&SSWC_HUUIN)){
			waza_bit|=No2Bit(pos);
		}
		//���イ��傭���󂯂Ă���
		if((ST_ServerJuuryokuCheck(bw,sp,client_no,sp->psp[client_no].waza[pos]))&&(check_bit&SSWC_JUURYOKU)){
			waza_bit|=No2Bit(pos);
		}
		//�q�[���u���b�N���󂯂Ă���
		if((ST_ServerHealblockCheck(bw,sp,client_no,sp->psp[client_no].waza[pos]))&&(check_bit&SSWC_HEALBLOCK)){
			waza_bit|=No2Bit(pos);
		}
		//�A���R�[��
		if((sp->psp[client_no].wkw.encore_wazano)&&(sp->psp[client_no].wkw.encore_wazano!=sp->psp[client_no].waza[pos])){
			waza_bit|=No2Bit(pos);
		}
		//�������n�`�}�L�`�F�b�N
		if(((eqp==SOUBI_ONAZIWAZAONLY)||(eqp==SOUBI_ONAZIWAZAONLYSUBAYASAUP)||(eqp==SOUBI_ONAZIAWZAONLYTOKUSYUUP))&&
		    (check_bit&SSWC_KODAWARI)){
			//�Z�Y��ł������n�`�}�L�n�̃��[�N�Ɋi�[�����Z�������Ă��Ȃ����`�F�b�N
			if(ST_ServerWazaPosGet(&sp->psp[client_no],sp->psp[client_no].wkw.kodawari_wazano)==WAZA_TEMOTI_MAX){
				sp->psp[client_no].wkw.kodawari_wazano=0;
			}
			else{
				if((sp->psp[client_no].wkw.kodawari_wazano)&&
				   (sp->psp[client_no].wkw.kodawari_wazano!=sp->psp[client_no].waza[pos])){
					waza_bit|=No2Bit(pos);
				}
			}
		}
	}
	return waza_bit;
}

//============================================================================================
/**
 *	�I�������Z���o�����Ƃ��o���邩�`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	waza_no		�|�W�V�������擾����Z�i���o�[
 *
 * @retval	TRUE:�o����@FALSE:�o���Ȃ�
 */
//============================================================================================
BOOL	ST_ServerWazaNGCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int pos,MESSAGE_PARAM *mp)
{
	BOOL	ret;

	ret=TRUE;

	//���Ȃ��΂�`�F�b�N
	if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_KANASHIBARI)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=KanashibariNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//���������`�F�b�N
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_ICHAMON)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK;
		mp->msg_id=IchamonNGMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		ret=FALSE;
	}
	//���傤�͂`�F�b�N
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_CHOUHATSU)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=ChouhatsuNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//�ӂ�����`�F�b�N
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_HUUIN)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=HuuinNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//���イ��傭�`�F�b�N
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_JUURYOKU)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=JuuryokuNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//�q�[���u���b�N�`�F�b�N
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_HEALBLOCK)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA_WAZA;
		mp->msg_id=HealblockNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=WAZANO_KAIHUKUHUUZI;
		mp->msg_para[2]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//�������n�`�}�L�`�F�b�N
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_KODAWARI)&No2Bit(pos)){
		mp->msg_tag=TAG_ITEM_WAZA;
		mp->msg_id=ItemOnaziWazaOnlyMsg;
		mp->msg_para[0]=sp->psp[client_no].item;
		mp->msg_para[1]=sp->psp[client_no].wkw.kodawari_wazano;
		ret=FALSE;
	}
	//PP�`�F�b�N�i����́A���Ȃ炸�Ō�ɂ���j
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_PP_NONE)&No2Bit(pos)){
		mp->msg_tag=TAG_NONE;
		mp->msg_id=PPNoneMsg;
		ret=FALSE;
	}

	return ret;
}

//============================================================================================
/**
 *	�Z�̃|�W�V�������擾
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	waza_no		�|�W�V�������擾����Z�i���o�[
 */
//============================================================================================
int	ST_ServerWazaPosGet(POKEMON_SERVER_PARAM *psp,u16 waza_no)
{
	int	pos;

	for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
		if(psp->waza[pos]==waza_no){
			break;
		}
	}

	return pos;
}

//============================================================================================
/**
 *	�Z�ƃ|�P�����̑����`�F�b�N�p�����e�[�u��
 */
//============================================================================================
#define	KOUKANAI	(0)
#define	IMAHITOTSU	(5)
#define	BATSUGUN	(20)

enum{
	WAZA_TYPE=0,
	POKE_TYPE,
	POWER
};

static	const	u8	TypeCheckTable[][3]={
	{NORMAL_TYPE,	IWA_TYPE,		IMAHITOTSU},	// NORMAL �� IWA �ɍU������ƁA
													// �З͂O�D�T�{
	{NORMAL_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{FIRE_TYPE,		FIRE_TYPE,		IMAHITOTSU},
	{FIRE_TYPE,		WATER_TYPE,		IMAHITOTSU},
	{FIRE_TYPE,		KUSA_TYPE,		BATSUGUN},	
	{FIRE_TYPE,		KOORI_TYPE,		BATSUGUN},	
	{FIRE_TYPE,		MUSHI_TYPE,		BATSUGUN},
	{FIRE_TYPE,		IWA_TYPE,		IMAHITOTSU},
	{FIRE_TYPE,		DRAGON_TYPE,	IMAHITOTSU},
	{FIRE_TYPE,		METAL_TYPE,		BATSUGUN},

	{WATER_TYPE,	FIRE_TYPE,		BATSUGUN},
	{WATER_TYPE,	WATER_TYPE,		IMAHITOTSU},
	{WATER_TYPE,	KUSA_TYPE,		IMAHITOTSU},
	{WATER_TYPE,	JIMEN_TYPE,		BATSUGUN},
	{WATER_TYPE,	IWA_TYPE,		BATSUGUN},
	{WATER_TYPE,	DRAGON_TYPE,	IMAHITOTSU},

	{ELECTRIC_TYPE,	WATER_TYPE,		BATSUGUN},
	{ELECTRIC_TYPE,	ELECTRIC_TYPE,	IMAHITOTSU},
	{ELECTRIC_TYPE,	KUSA_TYPE,		IMAHITOTSU},
	{ELECTRIC_TYPE,	JIMEN_TYPE,		KOUKANAI},
	{ELECTRIC_TYPE,	HIKOU_TYPE,		BATSUGUN},
	{ELECTRIC_TYPE,	DRAGON_TYPE,	IMAHITOTSU},

	{KUSA_TYPE,		FIRE_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		WATER_TYPE,		BATSUGUN},
	{KUSA_TYPE,		KUSA_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		POISON_TYPE,	IMAHITOTSU},
	{KUSA_TYPE,		JIMEN_TYPE,		BATSUGUN},
	{KUSA_TYPE,		HIKOU_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		MUSHI_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		IWA_TYPE,		BATSUGUN},
	{KUSA_TYPE,		DRAGON_TYPE,	IMAHITOTSU},
	{KUSA_TYPE,		METAL_TYPE,		IMAHITOTSU},

	{KOORI_TYPE,	WATER_TYPE,		IMAHITOTSU},
	{KOORI_TYPE,	KUSA_TYPE,		BATSUGUN},
	{KOORI_TYPE,	KOORI_TYPE,		IMAHITOTSU},
	{KOORI_TYPE,	JIMEN_TYPE,		BATSUGUN},
	{KOORI_TYPE,	HIKOU_TYPE,		BATSUGUN},
	{KOORI_TYPE,	DRAGON_TYPE,	BATSUGUN},
	{KOORI_TYPE,	METAL_TYPE,		IMAHITOTSU},
	{KOORI_TYPE,	FIRE_TYPE,		IMAHITOTSU},

	{BATTLE_TYPE,	NORMAL_TYPE,	BATSUGUN},
	{BATTLE_TYPE,	KOORI_TYPE,		BATSUGUN},
	{BATTLE_TYPE,	POISON_TYPE,	IMAHITOTSU},
	{BATTLE_TYPE,	HIKOU_TYPE,		IMAHITOTSU},
	{BATTLE_TYPE,	SP_TYPE,		IMAHITOTSU},
	{BATTLE_TYPE,	MUSHI_TYPE,		IMAHITOTSU},
	{BATTLE_TYPE,	IWA_TYPE,		BATSUGUN},
	{BATTLE_TYPE,	AKU_TYPE,		BATSUGUN},
	{BATTLE_TYPE,	METAL_TYPE,		BATSUGUN},

	{POISON_TYPE,	KUSA_TYPE,		BATSUGUN},
	{POISON_TYPE,	POISON_TYPE,	IMAHITOTSU},
	{POISON_TYPE,	JIMEN_TYPE,		IMAHITOTSU},
	{POISON_TYPE,	IWA_TYPE,		IMAHITOTSU},
	{POISON_TYPE,	GHOST_TYPE,		IMAHITOTSU},
	{POISON_TYPE,	METAL_TYPE,		KOUKANAI},

	{JIMEN_TYPE,	FIRE_TYPE,		BATSUGUN},
	{JIMEN_TYPE,	ELECTRIC_TYPE,	BATSUGUN},
	{JIMEN_TYPE,	KUSA_TYPE,		IMAHITOTSU},
	{JIMEN_TYPE,	POISON_TYPE,	BATSUGUN},
	{JIMEN_TYPE,	HIKOU_TYPE,		KOUKANAI},
	{JIMEN_TYPE,	MUSHI_TYPE,		IMAHITOTSU},
	{JIMEN_TYPE,	IWA_TYPE,		BATSUGUN},
	{JIMEN_TYPE,	METAL_TYPE,		BATSUGUN},

	{HIKOU_TYPE,	ELECTRIC_TYPE,	IMAHITOTSU},
	{HIKOU_TYPE,	KUSA_TYPE,		BATSUGUN},
	{HIKOU_TYPE,	BATTLE_TYPE,	BATSUGUN},
	{HIKOU_TYPE,	MUSHI_TYPE,		BATSUGUN},
	{HIKOU_TYPE,	IWA_TYPE,		IMAHITOTSU},
	{HIKOU_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{SP_TYPE,		BATTLE_TYPE,	BATSUGUN},
	{SP_TYPE,		POISON_TYPE,	BATSUGUN},
	{SP_TYPE,		SP_TYPE,		IMAHITOTSU},
	{SP_TYPE,		AKU_TYPE,		KOUKANAI},
	{SP_TYPE,		METAL_TYPE,		IMAHITOTSU},	

	{MUSHI_TYPE,	FIRE_TYPE,		IMAHITOTSU},
	{MUSHI_TYPE,	KUSA_TYPE,		BATSUGUN},
	{MUSHI_TYPE,	BATTLE_TYPE,	IMAHITOTSU},
	{MUSHI_TYPE,	POISON_TYPE,	IMAHITOTSU},
	{MUSHI_TYPE,	HIKOU_TYPE,		IMAHITOTSU},
	{MUSHI_TYPE,	SP_TYPE,		BATSUGUN},
	{MUSHI_TYPE,	GHOST_TYPE,		IMAHITOTSU},
	{MUSHI_TYPE,	AKU_TYPE,		BATSUGUN},
	{MUSHI_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{IWA_TYPE,		FIRE_TYPE,		BATSUGUN},
	{IWA_TYPE,		KOORI_TYPE,		BATSUGUN},
	{IWA_TYPE,		BATTLE_TYPE,	IMAHITOTSU},
	{IWA_TYPE,		JIMEN_TYPE,		IMAHITOTSU},
	{IWA_TYPE,		HIKOU_TYPE,		BATSUGUN},
	{IWA_TYPE,		MUSHI_TYPE,		BATSUGUN},
	{IWA_TYPE,		METAL_TYPE,		IMAHITOTSU},

	{GHOST_TYPE,	NORMAL_TYPE,	KOUKANAI},
	{GHOST_TYPE,	SP_TYPE,		BATSUGUN},
	{GHOST_TYPE,	AKU_TYPE,		IMAHITOTSU},
	{GHOST_TYPE,	METAL_TYPE,		IMAHITOTSU},
	{GHOST_TYPE,	GHOST_TYPE,		BATSUGUN},	

	{DRAGON_TYPE,	DRAGON_TYPE,	BATSUGUN},
	{DRAGON_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{AKU_TYPE,		BATTLE_TYPE,	IMAHITOTSU},
	{AKU_TYPE,		SP_TYPE,		BATSUGUN},
	{AKU_TYPE,		GHOST_TYPE,		BATSUGUN},
	{AKU_TYPE,		AKU_TYPE,		IMAHITOTSU},
	{AKU_TYPE,		METAL_TYPE,		IMAHITOTSU},

	{METAL_TYPE,	FIRE_TYPE,		IMAHITOTSU},
	{METAL_TYPE,	WATER_TYPE,		IMAHITOTSU},
	{METAL_TYPE,	ELECTRIC_TYPE,	IMAHITOTSU},
	{METAL_TYPE,	KOORI_TYPE,		BATSUGUN},
	{METAL_TYPE,	IWA_TYPE,		BATSUGUN},
	{METAL_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{0xfe,			0xfe,			KOUKANAI},	// miyaburi check

	{NORMAL_TYPE,	GHOST_TYPE,		KOUKANAI},
	{BATTLE_TYPE,	GHOST_TYPE,		KOUKANAI},

	{0xff,			0xff,			KOUKANAI},
};


//============================================================================================
/**
 *	���ʂȂ��|�P�����̑����𓖂Ă�Z���ʂ̃`�F�b�N
 *
 * @param[in]	sp				�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	attack_client	�U����ClientNo
 * @param[in]	defence_client	�h�䑤ClientNo
 * @param[in]	pos				TypeCheckTable��Index
 *
 * @retval	FALSE:������@TRUE:���ʂȂ��܂܂�OK
 */
//============================================================================================
static	BOOL	ST_KoukanaiCheck(SERVER_PARAM *sp,int attack_client,int defence_client,int pos)
{
	BOOL	ret;
	int		eqp;

	eqp=ST_ServerSoubiEqpGet(sp,defence_client);

	ret=TRUE;

	//�˂��͂�`�F�b�N
	//�������ʂ��΂₳DOWN
	if((eqp==SOUBI_SUBAYASADOWN)||(sp->psp[defence_client].waza_kouka&WAZAKOUKA_NEWOHARU)){
		//�Ђ����Ƀq�b�g
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}
	//�͂˂₷�߃`�F�b�N
	if(sp->otf[defence_client].haneyasume_flag){
		//�Ђ����Ƀq�b�g(1�{�ł��Ă�j
		if(TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE){
			ret=FALSE;
		}
	}
	//���イ��傭�`�F�b�N
	if(sp->field_condition&FIELD_CONDITION_JUURYOKU){
		//�Ђ����Ƀq�b�g
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}
	//�~���N���A�C�`�F�b�N
	if(sp->psp[defence_client].waza_kouka&WAZAKOUKA_MIRACLE_EYE){
		//�����Ƀq�b�g
		if((TypeCheckTable[pos][POKE_TYPE]==AKU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	�Z�ƃ|�P�����̑����`�F�b�N
 *
 * @param[in]	bw				�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp				�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	waza_no			�`�F�b�N����Z
 * @param[in]	attack_client	�U����ClientNo
 * @param[in]	defence_client	�h�䑤ClientNo
 * @param[out]	damage			�~�ς���Ă���_���[�W
 * @param[out]	flag			�`�F�b�N���ʂ̃t���O���i�[���郏�[�N
 */
//============================================================================================
int	ST_ServerTypeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int waza_no,int waza_type,int attack_client,int defence_client,int damage,u32 *flag)
{
	int	i;
	int	bairitu;
	u8	wazatype;
	u32	waza_damage;
	u8	eqp_a;
	u8	eqp_d;
	u8	atk_a;
	u8	atk_d;

	bairitu=1;
	
	//��邠�����́A�������Ȃ̂�TypeCheck���Ȃ�
	if(waza_no==WAZANO_WARUAGAKI){
		return damage;
	}

	eqp_a=ST_ServerSoubiEqpGet(sp,attack_client);
	atk_a=ST_ServerSoubiAtkGet(sp,attack_client,ATK_CHECK_NORMAL);
	eqp_d=ST_ServerSoubiEqpGet(sp,defence_client);
	atk_d=ST_ServerSoubiAtkGet(sp,defence_client,ATK_CHECK_NORMAL);

	//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
	if(ST_ServerTokuseiGet(sp,attack_client)==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(waza_type){
		wazatype=waza_type;
	}
	else{
//		wazatype=WT_WazaDataParaGet(waza_no,ID_WTD_wazatype);
		wazatype=sp->AIWT.wtd[waza_no].wazatype;
	}

//	waza_damage=WT_WazaDataParaGet(waza_no,ID_WTD_damage);
	waza_damage=sp->AIWT.wtd[waza_no].damage;

	if(((sp->server_status_flag&SERVER_STATUS_FLAG_TYPE_FLAT)==0)&&
	   ((ST_ServerPokemonServerParamGet(sp,attack_client,ID_PSP_type1,NULL)==wazatype)||
		(ST_ServerPokemonServerParamGet(sp,attack_client,ID_PSP_type2,NULL)==wazatype))){
		//�����Ă�������傭�́A�^�C�v��v�������A1.5�{��2�{�ɂ���
		if(ST_ServerTokuseiGet(sp,attack_client)==TOKUSYU_TEKIOURYOKU){
			damage*=2;
		}
		else{
			damage=damage*15/10;
		}
	}

	//������ʂӂ䂤�ɂ́A���߂�^�C�v�̋Z�͓�����Ȃ��i�������ʂőf����DOWN�̓q�b�g����j
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack_client,defence_client,TOKUSYU_HUYUU)==TRUE)&&
  	   (wazatype==JIMEN_TYPE)&&
	   (eqp_d!=SOUBI_SUBAYASADOWN)){
		flag[0]|=WAZA_STATUS_FLAG_JIMEN_NOHIT;
	}
	//�Z���ʂł񂶂ӂ䂤�ɂ́A���߂�^�C�v�̋Z�͓�����Ȃ��i���イ��傭���́A�ł񂶂ӂ䂤�𖳌��ɂ���j
	//�i�������ʂőf����DOWN�̓q�b�g����j
	else if((sp->psp[defence_client].wkw.denzihuyuu_count)&&
		   ((sp->psp[defence_client].waza_kouka&WAZAKOUKA_NEWOHARU)==0)&&
			(wazatype==JIMEN_TYPE)&&
			(eqp_d!=SOUBI_SUBAYASADOWN)){
		flag[0]|=WAZA_STATUS_FLAG_DENZIHUYUU_NOHIT;
	}
	else{
		i=0;
		while(TypeCheckTable[i][WAZA_TYPE]!=0xff){
			if(TypeCheckTable[i][WAZA_TYPE]==0xfe){
				//�݂�Ԃ�`�F�b�Nor�������������܂������Ă���
				if((sp->psp[defence_client].condition2&CONDITION2_MIYABURU)||
				   (ST_ServerTokuseiGet(sp,attack_client)==TOKUSYU_KIMOTTAMA)){
					break;
				}
				else{
					i++;
					continue;
				}
			}
			if(TypeCheckTable[i][WAZA_TYPE]==wazatype){
				if(TypeCheckTable[i][POKE_TYPE]==ST_ServerPokemonServerParamGet(sp,defence_client,ID_PSP_type1,NULL)){
					if(ST_KoukanaiCheck(sp,attack_client,defence_client,i)==TRUE){
						damage=ST_TypeCheckCalc(sp,attack_client,TypeCheckTable[i][POWER],damage,waza_damage,flag);
						if(TypeCheckTable[i][POWER]==BATSUGUN){
							bairitu*=2;
						}
					}
				}
				if((TypeCheckTable[i][POKE_TYPE]==ST_ServerPokemonServerParamGet(sp,defence_client,ID_PSP_type2,NULL))&&
				   (ST_ServerPokemonServerParamGet(sp,defence_client,ID_PSP_type1,NULL)!=
					ST_ServerPokemonServerParamGet(sp,defence_client,ID_PSP_type2,NULL))){
					if(ST_KoukanaiCheck(sp,attack_client,defence_client,i)==TRUE){
						damage=ST_TypeCheckCalc(sp,attack_client,TypeCheckTable[i][POWER],damage,waza_damage,flag);
						if(TypeCheckTable[i][POWER]==BATSUGUN){
							bairitu*=2;
						}
					}
				}
			}
			i++;
		}
	}

	//����\�͂ӂ����Ȃ܂���́A���ʂ����Q����������Ȃ�
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack_client,defence_client,TOKUSYU_HUSIGINAMAMORI)==TRUE)&&
	   (ST_TameWazaTurnCheck(sp,waza_no))&&
	 (((flag[0]&WAZA_STATUS_FLAG_BATSUGUN)==0)||
	  ((flag[0]&WAZA_STATUS_FLAG_SOUSAI)==WAZA_STATUS_FLAG_SOUSAI))&&
	   (waza_damage)){
		flag[0]|=WAZA_STATUS_FLAG_BATSUGUN_NOHIT;
	}
	else{
		if(((sp->server_status_flag&SERVER_STATUS_FLAG_TYPE_FLAT)==0)&&
		   ((sp->server_status_flag&SERVER_STATUS_FLAG_TYPE_NONE)==0)){
			if((flag[0]&WAZA_STATUS_FLAG_BATSUGUN)&&(waza_damage)){
				//�����t�B���^�[�A�n�[�h���b�N�́A���Q�œ����������A�_���[�W��3/4�ɂ���
				if((ST_ServerKatayaburiTokuseiCheck(sp,attack_client,defence_client,TOKUSYU_FIRUTAA)==TRUE)||
				   (ST_ServerKatayaburiTokuseiCheck(sp,attack_client,defence_client,TOKUSYU_HAADOROKKU)==TRUE)){
					damage=ST_ServerDamageDiv(damage*3,4);
				}
				//�������ʂŔ��Q���З́����A�b�v����
				if(eqp_a==SOUBI_BATUGUNIRYOKUUP){
					damage=damage*(100+atk_a)/100;
				}
			}
			if((flag[0]&WAZA_STATUS_FLAG_IMAHITOTSU)&&(waza_damage)){
				//��������߂��˂́A���܂ЂƂ�0.5��1�ɁA0.25��0.5�ɂ���
				if(ST_ServerTokuseiGet(sp,attack_client)==TOKUSYU_IROMEGANE){
					damage*=2;
				}
			}
		}
		else{
			flag[0]&=WAZA_STATUS_FLAG_BATSUGUN_OFF;
			flag[0]&=WAZA_STATUS_FLAG_IMAHITOTSU_OFF;
		}
	}

	return damage;
}

//============================================================================================
/**
 *	�Z�ƃ|�P�����̑����`�F�b�N�iAI�p�j
 *
 * @param[in]	bw				�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp				�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	waza_no			�`�F�b�N����Z
 * @param[in]	attack_client	�U����ClientNo
 * @param[in]	defence_client	�h�䑤ClientNo
 * @param[out]	flag			�`�F�b�N���ʂ̃t���O���i�[���郏�[�N
 */
//============================================================================================
void	ST_AITypeCheck(SERVER_PARAM *sp,int waza_no,int waza_type,int spe_a,int spe_d,int eqp,int type1,int type2,u32 *flag)
{
	int	i;
	u8	wazatype;

	//��邠�����́A�������Ȃ̂�TypeCheck���Ȃ�
	if(waza_no==WAZANO_WARUAGAKI){
		return;
	}

	//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
	if(spe_a==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(waza_type){
		wazatype=waza_type;
	}
	else{
		wazatype=sp->AIWT.wtd[waza_no].wazatype;
	}

	//������ʂӂ䂤�ɂ́A���߂�^�C�v�̋Z�͓�����Ȃ��i�������ʂőf����DOWN�̓q�b�g����j
	if((spe_a!=TOKUSYU_KATAYABURI)&&
	   (spe_d==TOKUSYU_HUYUU)&&
  	   (wazatype==JIMEN_TYPE)&&
	  ((sp->field_condition&FIELD_CONDITION_JUURYOKU)==0)&&
	   (eqp!=SOUBI_SUBAYASADOWN)){
		flag[0]|=WAZA_STATUS_FLAG_KOUKANAI;
	}
	else{
		i=0;
		while(TypeCheckTable[i][WAZA_TYPE]!=0xff){
			if(TypeCheckTable[i][WAZA_TYPE]==0xfe){
				//�݂�Ԃ�`�F�b�Nor�������������܂������Ă���
				if(spe_a==TOKUSYU_KIMOTTAMA){
					break;
				}
				else{
					i++;
					continue;
				}
			}
			if(TypeCheckTable[i][WAZA_TYPE]==wazatype){
				if(TypeCheckTable[i][POKE_TYPE]==type1){
					if(ST_AIKoukanaiCheck(sp,eqp,i)==TRUE){
						ST_AITypeCheckCalc(TypeCheckTable[i][POWER],flag);
					}
				}
				if((TypeCheckTable[i][POKE_TYPE]==type2)&&(type1!=type2)){
					if(ST_AIKoukanaiCheck(sp,eqp,i)==TRUE){
						ST_AITypeCheckCalc(TypeCheckTable[i][POWER],flag);
					}
				}
			}
			i++;
		}
	}

	//����\�͂ӂ����Ȃ܂���́A���ʂ����Q����������Ȃ�
	if((spe_a!=TOKUSYU_KATAYABURI)&&
	   (spe_d==TOKUSYU_HUSIGINAMAMORI)&&
	   (ST_TameWazaTurnCheck(sp,waza_no))&&
	 (((flag[0]&WAZA_STATUS_FLAG_BATSUGUN)==0)||
	  ((flag[0]&WAZA_STATUS_FLAG_SOUSAI)==WAZA_STATUS_FLAG_SOUSAI))){
		flag[0]|=WAZA_STATUS_FLAG_KOUKANAI;
	}

	return;
}

//============================================================================================
/**
 *	���ʂȂ��|�P�����̑����𓖂Ă�Z���ʂ̃`�F�b�N
 *
 * @param[in]	sp				�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	eqp				��������
 * @param[in]	pos				TypeCheckTable��Index
 *
 * @retval	FALSE:������@TRUE:���ʂȂ��܂܂�OK
 */
//============================================================================================
static	BOOL	ST_AIKoukanaiCheck(SERVER_PARAM *sp,int eqp,int pos)
{
	BOOL	ret;

	ret=TRUE;

	//�������ʂ��΂₳DOWN
	if(eqp==SOUBI_SUBAYASADOWN){
		//�Ђ����Ƀq�b�g
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}
	//���イ��傭�`�F�b�N
	if(sp->field_condition&FIELD_CONDITION_JUURYOKU){
		//�Ђ����Ƀq�b�g
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	�|�P�����ƋZ�̃^�C�v�̑����Ńt���O���Z�b�g
 *
 * @param[in]	client_no	�Z���J��o��ClientNo
 * @param[in]	power		�����������З�
 * @param[out]	flag		�t���O���Z�b�g���郏�[�N
 */
//============================================================================================
static	void	ST_AITypeCheckCalc(int power,u32 *flag)
{
	switch(power){
	case KOUKANAI:
		flag[0]|=WAZA_STATUS_FLAG_KOUKANAI;
		flag[0]&=WAZA_STATUS_FLAG_IMAHITOTSU_OFF;
		flag[0]&=WAZA_STATUS_FLAG_BATSUGUN_OFF;
		break;
	case IMAHITOTSU:
		if(flag[0]&WAZA_STATUS_FLAG_BATSUGUN){
			flag[0]&=WAZA_STATUS_FLAG_BATSUGUN_OFF;
		}
		else{
			flag[0]|=WAZA_STATUS_FLAG_IMAHITOTSU;
		}
		break;
	case BATSUGUN:
		if(flag[0]&WAZA_STATUS_FLAG_IMAHITOTSU){
			flag[0]&=WAZA_STATUS_FLAG_IMAHITOTSU_OFF;
		}
		else{
			flag[0]|=WAZA_STATUS_FLAG_BATSUGUN;
		}
		break;
	}

	return;
}

//============================================================================================
/**
 *	�Z�̔�����W����ꂽ���`�F�b�N
 *
 * @param[in]	sp	�T�[�o�p�����[�^�̍\���̃|�C���^
 *
 * @retval	FALSE:�W�����Ă��Ȃ��@TRUE:�W����ꂽ
 */
//============================================================================================
BOOL	ST_ServerWazaOutCheck(SERVER_PARAM *sp,int client_no)
{
	if( (sp->wocf[client_no].mahi_flag)||
		(sp->wocf[client_no].koukanai_flag)||
		(sp->wocf[client_no].huuin_flag)||
		(sp->wocf[client_no].meromero_flag)||
		(sp->wocf[client_no].kanashibari_flag)||
		(sp->wocf[client_no].chouhatsu_flag)||
		(sp->wocf[client_no].hirumu_flag)||
		(sp->wocf[client_no].juuryoku_flag)||
		(sp->wocf[client_no].konran_flag)){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

//============================================================================================
/**
 *	�U���𓖂Ă邱�Ƃ̏o����|�P���������̂��邩�`�F�b�N
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	flag		�`�F�b�N�Ώۃt���O
 * @param[in]	client_no	�`�F�b�N�Ώ�ClientNo
 *
 * @retval	�|�P�����̐�
 */
//============================================================================================
u8		ST_ServerHitCountCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int flag,int client_no)
{
	int	no;
	u8	count;
	int	client_set_max;

	count=0;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	switch(flag){
	case SHCC_NORMAL:
		for(no=0;no<client_set_max;no++){
			if((no!=client_no)&&(sp->psp[no].hp)){
				count++;
			}
		}
		break;
	case SHCC_SIDE:
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)==BattleWorkMineEnemyCheck(bw,client_no))&&(sp->psp[no].hp)){
				count++;
			}
		}
		break;
	}
	return count;
}

//============================================================================================
/**
 *	���b�Z�[�W�\���p�����[�^�̃j�b�N�l�[���f�[�^�𐶐�
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�����Ώ�ClientNo
 *
 * @retval	���������p�����[�^
 */
//============================================================================================
int		ST_ServerTagNickParaMake(SERVER_PARAM *sp,int client_no)
{
	return (client_no|(sp->sel_mons_no[client_no]<<8));
}

//============================================================================================
/**
 *	�I�������Z�i���o�[���擾
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	�I�������Z�i���o�[
 */
//============================================================================================
u16		ST_ServerSelectWazaGet(SERVER_PARAM *sp,int client_no)
{
	u16	wazano;

	wazano=0;

	if((sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]==SELECT_FIGHT_COMMAND)&&
	   (sp->client_act_work[client_no][ACT_PARA_WORK])){
		wazano=sp->psp[client_no].waza[sp->client_act_work[client_no][ACT_PARA_WORK]-1];
	}
	return wazano;
}

//============================================================================================
/**
 *	�������������|�P���������邩�`�F�b�N
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	flag		�`�F�b�N�̎��
 * @param[in]	client_no	�`�F�b�N����ClientNo�i�`�F�b�N�̎�ނɂ��Ӗ����ω��j
 * @param[in]	speabi		�`�F�b�N��������i���o�[
 *
 * @retval	�����Ă����|�P������
 */
//============================================================================================
int		ST_ServerTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int flag,int client_no,int speabi)
{
	int	cnt;
	int	no;
	int	client_set_max;

	cnt=0;
	client_set_max=BattleWorkClientSetMaxGet(bw);

	switch(flag){
	case STC_HAVE_MINE_SIDE:	//�������������Ă��邩�`�F�b�N
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)==BattleWorkMineEnemyCheck(bw,client_no))&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_MINE_SIDE_HP:	//�������������Ă��邩�`�F�b�N�iHP0�͖����j
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)==BattleWorkMineEnemyCheck(bw,client_no))&&
			   (sp->psp[no].hp)&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ENEMY_SIDE:	//���葤�������Ă��邩�`�F�b�N
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)!=BattleWorkMineEnemyCheck(bw,client_no))&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ENEMY_SIDE_HP:	//���葤�������Ă��邩�`�F�b�N�iHP0�͖����j
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)!=BattleWorkMineEnemyCheck(bw,client_no))&&
			   (sp->psp[no].hp)&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ENEMY_SIDE_RET:	//���葤�������Ă��邩�`�F�b�N���Ď����Ă���ClientNo��Ԃ�
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)!=BattleWorkMineEnemyCheck(bw,client_no))&&
			   (sp->psp[no].hp)&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt|=No2Bit(no);
			}
		}
		break;
	case STC_HAVE_ALL:			//�������܂ߎ����Ă��邩�`�F�b�N
		for(no=0;no<client_set_max;no++){
			if(ST_ServerTokuseiGet(sp,no)==speabi){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ALL_NOMINE:	//�����ȊO�̃|�P�����������Ă��邩�`�F�b�N
		for(no=0;no<client_set_max;no++){
			if((no!=client_no)&&(ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ALL_NOMINE_RET:	//�����ȊO�̃|�P�����������Ă��邩�`�F�b�N���Ď����Ă���ClientNo��Ԃ�
		for(no=0;no<client_set_max;no++){
			if((no!=client_no)&&(ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt=no+1;
				break;
			}
		}
		break;
	case STC_HAVE_ALL_HP:			//�������܂ߎ����Ă��邩�`�F�b�N�iHP0�͖����j
		for(no=0;no<client_set_max;no++){
			if((ST_ServerTokuseiGet(sp,no)==speabi)&&(sp->psp[no].hp)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ALL_NOMINE_HP:	//�����ȊO�̃|�P�����������Ă��邩�`�F�b�N�iHP0�͖����j
		for(no=0;no<client_set_max;no++){
			if((no!=client_no)&&(ST_ServerTokuseiGet(sp,no)==speabi)&&(sp->psp[no].hp)){
				cnt++;
			}
		}
		break;
	}

	return cnt;
}

//============================================================================================
/**
 *	���ߋZ��I�����Ă��邩�`�F�b�N
 *
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 *
 * @retval	TRUE�F���ߋZ�@FALSE:���ߋZ����Ȃ�
 */
//============================================================================================
BOOL	ST_TameWazaCheck(SERVER_PARAM *sp,int waza_no)
{
	switch(sp->AIWT.wtd[waza_no].battleeffect){
	case 26:	//���܂�
	case 39:	//���܂�����
	case 75:	//�S�b�h�o�[�h
	case 145:	//���P�b�g���˂�
	case 151:	//�\�[���[�r�[��
	case 155:	//������Ƃ�
	case 255:	//�_�C�r���O
	case 256:	//���Ȃ��ق�
	case 263:	//�Ƃт͂˂�
	case 272:	//�V���h�[�_�C�u
		return TRUE;
		break;
	}

	return FALSE;
}

//============================================================================================
/**
 *	TypeCheckTable�̃p�����[�^���擾
 *
 * @param[in]	pos		�e�[�u���̃C���f�b�N�X
 * @param[in]	type_w	�Z�^�C�v�i�[��
 * @param[in]	type_p	�|�P�����^�C�v�i�[��
 * @param[in]	value	type_w��type_p�̑���
 *
 * @retval	FALSE:�e�[�u�����I�[�o�[�@TRUE:�e�[�u���Ȃ�����擾
 *
 */
//============================================================================================
BOOL	ST_ServerTypeCheckTableParaGet(int pos,u8 *type_w,u8 *type_p,u8 *value)
{
	BOOL	ret;

	ret=TRUE;

	if(pos>=NELEMS(TypeCheckTable)){
		pos=gf_rand()%(NELEMS(TypeCheckTable));
		ret=FALSE;
	}
	type_w[0]=TypeCheckTable[pos][WAZA_TYPE];
	type_p[0]=TypeCheckTable[pos][POKE_TYPE];
	value[0]=TypeCheckTable[pos][POWER];

	return ret;
}

//============================================================================================
/**
 *	TypeCheckTable����p���[���擾
 *
 * @param[in]	type_w	�Z�^�C�v
 * @param[in]	type_p1	�|�P�����^�C�v
 * @param[in]	type_p2	�|�P�����^�C�v
 *
 * @retval	power
 *
 */
//============================================================================================
int	ST_ServerTypeCheckTablePowerGet(u8 type_w,u8 type_p1,u8 type_p2)
{
	int	i;
	int	damage;

	i=0;
	damage=AISYOU_1BAI;

	while(TypeCheckTable[i][WAZA_TYPE]!=0xff){
		if(TypeCheckTable[i][WAZA_TYPE]==type_w){
			if(TypeCheckTable[i][POKE_TYPE]==type_p1){
				damage=damage*TypeCheckTable[i][POWER]/10;
			}
			if((TypeCheckTable[i][POKE_TYPE]==type_p2)&&(type_p1!=type_p2)){
				damage=damage*TypeCheckTable[i][POWER]/10;
			}
		}
		i++;
	}

	return damage;
}

//============================================================================================
/**
 *	�Ⴄ�Z�֔h������Z�̃`�F�b�N
 *
 * @param[in]	waza_no	�`�F�b�N����Z�i���o�[
 *
 * @retval	FALSE:�h���Z�ł͂Ȃ��@TRUE:�h���Z
 */
//============================================================================================
BOOL	ST_RendouWazaCheck(u16 waza_no)
{
	if((waza_no==0)||
	   (waza_no==WAZANO_NEGOTO)||
	   (waza_no==WAZANO_MANEKKO)||
	   (waza_no==WAZANO_NEKONOTE)||
	   (waza_no==WAZANO_SAKIDORI)||
	   (waza_no==WAZANO_OUMUGAESI)||
	   (waza_no==WAZANO_YUBIWOHURU)){
		return TRUE;
	}
	return FALSE;
}

//============================================================================================
/**
 *	�J��o�����Ƃ��Ă���̂낢���A�m�[�}�����A�S�[�X�g���`�F�b�N
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 * @param[in]	client_no	�J��o�����Ƃ��Ă���ClientNo
 *
 * @retval	FALSE:�m�[�}���@TRUE:�S�[�X�g
 */
//============================================================================================
BOOL	ST_ServerWazaNoroiCheck(SERVER_PARAM *sp,u16 waza_no,int client_no)
{
	return ((waza_no==WAZANO_NOROI)&&
		   ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)==GHOST_TYPE)||
			(ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)==GHOST_TYPE)));
}

//============================================================================================
/**
 *	�ǂ�ڂ��ł���A�C�e�����`�F�b�N
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�ǂ�ڂ������ClientNo
 *
 * @retval	FALSE:�ł��Ȃ��@TRUE:�ł���
 */
//============================================================================================
BOOL	ST_ServerDorobouItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	int		dir;

	ret=FALSE;

	dir=BattleWorkMineEnemyCheck(bw,client_no);

	if((sp->psp[client_no].item)&&
	  ((sp->scw[dir].hatakiotosu_item&No2Bit(sp->sel_mons_no[client_no]))==0)&&
	   (ItemMailCheck(sp->psp[client_no].item)==FALSE)){
		ret=TRUE;
	}

	return ret;
}

//============================================================================================
/**
 *	�g���b�N�ł���A�C�e�����`�F�b�N
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�g���b�N�����Ă���ClientNo
 *
 * @retval	FALSE:�ł��Ȃ��@TRUE:�ł���
 */
//============================================================================================
BOOL	ST_ServerTrickItemCheck(SERVER_PARAM *sp,int client_no)
{
	return (ItemMailCheck(sp->psp[client_no].item)==FALSE);
}

//============================================================================================
/**
 *	�ӂ��Ƃ΂����۔���
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 *
 * @retval	FALSE:�ł��Ȃ��@TRUE:�ł���
 */
//============================================================================================
BOOL	ST_ServerHukitobasiCheck(SERVER_PARAM *sp)
{
	BOOL	ret;

	ret=FALSE;

	//�o�������̃��x����������΁A100%����
	if(sp->psp[sp->attack_client].level>=sp->psp[sp->defence_client].level){
		ret=TRUE;
	}
	else{
		{
			int	level;

			level=(((gf_rand()&0xff)*(sp->psp[sp->attack_client].level+sp->psp[sp->defence_client].level))>>8)+1;

			if(level>(sp->psp[sp->defence_client].level/4)){
				ret=TRUE;
			}
		}
	}

	return ret;
}

//============================================================================================
/**
 *	�����擾�i�Z�u�������v�̌��ʂ����f���Ď擾�j
 *
 * @param[in]	psp			�|�P�����T�[�o���[�N�\����
 *
 * @retval	�����i���o�[
 */
//============================================================================================
u8	ST_ServerTokuseiGet(SERVER_PARAM *sp,int client_no)
{
	//�������������́A���������i�}���`�^�C�v�͏��O�j
	if((sp->psp[client_no].waza_kouka&WAZAKOUKA_IEKI)&&(sp->psp[client_no].speabino!=TOKUSYU_MARUTITAIPU)){
		return 0;
	}
	//���イ��傭�������́A�ӂ䂤�͖���
	else if((sp->field_condition&FIELD_CONDITION_JUURYOKU)&&(sp->psp[client_no].speabino==TOKUSYU_HUYUU)){
		return 0;
	}
	//�˂��͂锭�����́A�ӂ䂤�͖���
	else if((sp->psp[client_no].waza_kouka&WAZAKOUKA_NEWOHARU)&&(sp->psp[client_no].speabino==TOKUSYU_HUYUU)){
		return 0;
	}
	else{
		return sp->psp[client_no].speabino;
	}
}

//============================================================================================
/**
 *	����������Ԃ�𔽉f���ă`�F�b�N
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	attack		�U����
 * @param[in]	defence		�h�䑤
 * @param[in]	tokusei		�`�F�b�N�������
 *
 * @retval	FALSE:������Ԃ�œ����������@TRUE�F������Ԃ�֌W�Ȃ�
 */
//============================================================================================
BOOL	ST_ServerKatayaburiTokuseiCheck(SERVER_PARAM *sp,int attack,int defence,int tokusei)
{
	BOOL	ret;

	ret=FALSE;

	if(ST_ServerTokuseiGet(sp,attack)!=TOKUSYU_KATAYABURI){
		if(ST_ServerTokuseiGet(sp,defence)==tokusei){
			ret=TRUE;
		}
	}
	else{
		if((ST_ServerTokuseiGet(sp,defence)==tokusei)&&(sp->ostf[attack].katayaburi_flag==0)){
			sp->ostf[attack].katayaburi_flag=1;
			sp->server_status_flag|=SERVER_STATUS_FLAG_KATAYABURI;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	����ւ���|�P���������邩�`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:���Ȃ��@TRUE:����
 */
//============================================================================================
BOOL	ST_ServerReshuffleCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	BOOL			ret;
	POKEPARTY		*poke_p;
	POKEMON_PARAM	*pp;
	int				poke_count;
	int				cnt=0,cntmax,i,start,end,rnd_max;
	int				selmons1,selmons2;
	u32				fight_type;

	ret=FALSE;
	fight_type=BattleWorkFightTypeGet(bw);
	poke_p=BattleWorkPokePartyGet(bw,client_no);
	poke_count=BattleWorkPokeCountGet(bw,client_no);

	if((fight_type&FIGHT_TYPE_MULTI)||
	  ((fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
		start=0;
		end=poke_count;
		rnd_max=poke_count;
		cntmax=1;
		selmons1=sp->sel_mons_no[client_no];
		selmons2=sp->sel_mons_no[client_no];
	}
	//�_�u��
	else if(fight_type&FIGHT_TYPE_2vs2){
		start=0;
		end=poke_count;
		rnd_max=poke_count;
		cntmax=1;
		selmons1=sp->sel_mons_no[client_no];
		selmons2=sp->sel_mons_no[BattleWorkPartnerClientNoGet(bw,client_no)];
	}
	//�V���O��
	else{
		start=0;
		end=poke_count;
		rnd_max=poke_count;
		cntmax=1;
		selmons1=sp->sel_mons_no[client_no];
		selmons2=sp->sel_mons_no[client_no];
	}

	for(i=start;i<end;i++){
		pp=PokeParty_GetMemberPointer(poke_p,i);
		if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
		   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
		   (PokeParaGet(pp,ID_PARA_hp,NULL))&&
		   (selmons1!=i)&&(selmons2!=i)){
			cnt++;
		}
	}
	if(cnt>=cntmax){
		ret=TRUE;
	}

	return ret;
}

//============================================================================================
/**
 *	�퓬���瓦�����邩���`�F�b�N����i������R�}���h���������邩�ǂ����j
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	@param[in]	mp			�A���[�g���b�Z�[�W�̃p�����[�^���i�[����\����
 *	
 *	@retval	FALSE:��������@TRUE:�������Ȃ�
 */
//============================================================================================
BOOL	ST_EscapeNGCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,MESSAGE_PARAM *mp)
{
	int	i;
	int	client_set_max;
	u8	dir;
	int	eqp;
	u32	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	eqp=ST_ServerSoubiEqpGet(sp,client_no);

	//�A�C�e���ŕK����������̑������ʂ�100%�������
	if((eqp==SOUBI_KANARAZUNIGERARERU)||
	//�K���������FIGHT_TYPE�̓`�F�b�N���Ȃ�
	   (fight_type&FIGHT_TYPE_ESCAPE)||
	//����\�͂ɂ������͕K���������̂Ń`�F�b�N���Ȃ�
	   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_NIGEASI)){
		return 0;
	}

	dir=BattleWorkMineEnemyCheck(bw,client_no);
	client_set_max=BattleWorkClientSetMaxGet(bw);

	//���������ӂ݂���͓������Ȃ��i���݂��������ӂ݂̎��͗�O�j
	if((i=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE_HP,client_no,TOKUSYU_KAGEHUMI))&&
	   (ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_KAGEHUMI)){
		if(mp==NULL){
			return TRUE;
		}
		mp->msg_tag=TAG_NICK_TOKU;
		mp->msg_id=TokuseiEscapeNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,i);
		mp->msg_para[1]=TOKUSYU_KAGEHUMI;
		return TRUE;
	}
	//�������肶��������͓������Ȃ�
	if((i=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_ARIZIGOKU))){
		if((sp->field_condition&FIELD_CONDITION_JUURYOKU)==0){
			//�����ӂ䂤�A��s�^�C�v�ɂ́A�������肶�����͌��ʂ�����
			if((ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_HUYUU)&&
			   (sp->psp[client_no].wkw.denzihuyuu_count==0)&&
			  ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)!=HIKOU_TYPE)&&
			   (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)!=HIKOU_TYPE))){
				if(mp==NULL){
					return TRUE;
				}
				mp->msg_tag=TAG_NICK_TOKU;
				mp->msg_id=TokuseiEscapeNGMineMsg;
				mp->msg_para[0]=ST_ServerTagNickParaMake(sp,i);
				mp->msg_para[1]=TOKUSYU_ARIZIGOKU;
				return TRUE;
			}
		}
		else{
			if(mp==NULL){
				return TRUE;
			}
			mp->msg_tag=TAG_NICK_TOKU;
			mp->msg_id=TokuseiEscapeNGMineMsg;
			mp->msg_para[0]=ST_ServerTagNickParaMake(sp,i);
			mp->msg_para[1]=TOKUSYU_ARIZIGOKU;
			return TRUE;
		}
	}
#if 0
	//�������肶��������͓������Ȃ�
	if((i=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE,client_no,TOKUSYU_ARIZIGOKU))&&
		//�����ӂ䂤�A��s�^�C�v�ɂ́A�������肶�����͌��ʂ�����
	   (ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_HUYUU)&&
	   (sp->psp[client_no].wkw.denzihuyuu_count==0)&&
	  ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)!=HIKOU_TYPE)&&
	   (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)!=HIKOU_TYPE))){
		if(mp==NULL){
			return TRUE;
		}
		mp->msg_tag=TAG_NICK_TOKU;
		mp->msg_id=TokuseiEscapeNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,i);
		mp->msg_para[1]=TOKUSYU_ARIZIGOKU;
		return TRUE;
	}
#endif
	//��������傭����|�^�C�v�̃|�P�����͓������Ȃ�
	if((i=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_ZIRYOKU))&&
	  ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)==METAL_TYPE)||
	   (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)==METAL_TYPE))){
		if(mp==NULL){
			return TRUE;
		}
		mp->msg_tag=TAG_NICK_TOKU;
		mp->msg_id=TokuseiEscapeNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,i);
		mp->msg_para[1]=TOKUSYU_ZIRYOKU;
		return TRUE;
	}

	//���߂����Ă���A���낢�܂Ȃ����������Ă���A�˂��͂��Ă��鎞�͓������Ȃ�
	if((sp->psp[client_no].condition2&(CONDITION2_SHIME|CONDITION2_KUROIMANAZASHI))||
	   (sp->psp[client_no].waza_kouka&WAZAKOUKA_NEWOHARU)){
		if(mp==NULL){
			return TRUE;
		}
		mp->msg_tag=TAG_NONE;
		mp->msg_id=EscapeNGMsg1;
		return TRUE;
	}

#if 0
	//�퓬�^�C�v���K�C�h�o�g���̎��͓������Ȃ�
	if(FightType&FIGHT_TYPE_GUIDE){
		ServerWork[5]=1;
		return 1;
	}
#endif
	return	FALSE;
}

//============================================================================================
/**
 *	�퓬���瓦�����邩���`�F�b�N����i������R�}���h������j
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	
 *	@retval	TRUE:��������@FALSE:�������Ȃ�
 */
//============================================================================================
BOOL	ST_EscapeActCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	u8		escape;
	int		eqp;
	u8		escape_range;
	u32		fight_type;

	fight_type=BattleWorkFightTypeGet(bw);
	eqp=ST_ServerSoubiEqpGet(sp,client_no);
	ret=FALSE;

	//�A�C�e���ŕK����������̑������ʂ�100%�������
	if(eqp==SOUBI_KANARAZUNIGERARERU){
		sp->otf[client_no].escape_flag=1;
		ret=TRUE;
	}
	//100%�������FIGHT_TYPE���`�F�b�N
	else if(fight_type&FIGHT_TYPE_ESCAPE){
		ret=TRUE;
	}
	//����\�͂ɂ�������100%�������
	else if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_NIGEASI){
		sp->otf[client_no].escape_flag=2;
		ret=TRUE;
	}
	else{
		//����̕���������Γ������I�������񐔂������قǓ����₷������
		if(sp->psp[client_no].agi<sp->psp[client_no^1].agi){
			escape=sp->psp[client_no].agi*128/sp->psp[client_no^1].agi+sp->escape_count*30;
			if(escape>(gf_rand()%256)){
				ret=TRUE;
			}
		}
		//�����̕����������100%�������
		else{
			ret=TRUE;
		}
		//������Ɏ��s�����J�E���^���J�E���g�A�b�v
		if(ret==FALSE){
			SCIO_IncRecord(bw,client_no,CLIENT_BOOT_TYPE_MINE,RECID_NIGERU_SIPPAI);
		}
		sp->escape_count++;
	}
	return ret;
}

//============================================================================================
/**
 *	�Ȃ܂��`�F�b�N
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	
 *	@retval	FALSE:�Ȃ܂��Ȃ��@TRUE:�Ȃ܂���
 */
//============================================================================================
BOOL	ST_ServerNamakeCheck(SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;

	ret=FALSE;

	if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_NAMAKE){
		if(sp->psp[client_no].wkw.namake_bit!=(sp->total_turn&1)){
			ret=TRUE;
		}
	}
	
	return ret;
}

//============================================================================================
/**
 *	���킮�`�F�b�N
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	
 *	@retval	FALSE:�������@TRUE:���킪����
 */
//============================================================================================
BOOL	ST_ServerSawaguCheck(SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;

	ret=FALSE;

	if(ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_BOUON){
		if(sp->field_condition&FIELD_CONDITION_SAWAGU){
			ret=TRUE;
		}
	}
	return ret;
}

//============================================================================================
/**
 *	�ӂ�����`�F�b�N
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	@param[in]	waza_no		�`�F�b�N����WazaNo
 *	
 *	@retval	FALSE:�ӂ����񂳂�Ă��Ȃ��@TRUE:�ӂ����񂳂�Ă���
 */
//============================================================================================
BOOL	ST_ServerHuuinCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no)
{
	int		client;
	int		client_set_max;
	int		dir;
	int		pos;
	BOOL	ret;

	ret=FALSE;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	dir=BattleWorkMineEnemyCheck(bw,client_no);

	for(client=0;client<client_set_max;client++){
		if((dir!=BattleWorkMineEnemyCheck(bw,client))&&(sp->psp[client].waza_kouka&WAZAKOUKA_HUUIN)){
			for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
				if(waza_no==sp->psp[client].waza[pos]){
					break;
				}
			}
			if(pos!=WAZA_TEMOTI_MAX){
				ret=TRUE;
			}
		}
	}

	return ret;
}

//============================================================================================
/**
 *	��ɂ���|�P�����ɋZ���ʂ��������Ă��邩�`�F�b�N
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	waza_kouka	�`�F�b�N����Z����
 *	
 *	@retval	FALSE:���ʂ��������Ă��Ȃ��@TRUE:���ʂ�����
 */
//============================================================================================
BOOL	ST_ServerWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int waza_kouka)
{
	int		client_no;
	int		client_set_max;
	BOOL	ret;

	ret=FALSE;
	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(client_no=0;client_no<client_set_max;client_no++){
		if(sp->psp[client_no].waza_kouka&waza_kouka){
			ret=TRUE;
			break;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	���[�v�n�̋Z�Ń��[�v���鎞�ɏ��������郏�[�N
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerLoopInit(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	sp->waza_status_flag=0;
//	sp->damage_value=10;
	sp->critical=1;
#if	GB001_060815_FIX
	sp->server_status_flag&=(SERVER_STATUS_FLAG_NO_WAZANO_SET^0xffffffff);
#endif	//GB001_060815_FIX
}

//============================================================================================
/**
 *	�f�����ɂ��Z�������Ԃ̂��߂̃��[�N�𐶐�
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerPSPAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max;
	int	i,j;
	int	cl1,cl2;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(client_no=0;client_no<client_set_max;client_no++){
		sp->psp_agi_work[client_no]=client_no;
	}
	for(i=0;i<client_set_max-1;i++){
		for(j=i+1;j<client_set_max;j++){
			cl1=sp->psp_agi_work[i];
			cl2=sp->psp_agi_work[j];
			if(ST_ServerAgiCalc(bw,sp,cl1,cl2,1)){
				sp->psp_agi_work[i]=cl2;
				sp->psp_agi_work[j]=cl1;
			}
		}
	}
}

//============================================================================================
/**
 *	���イ��傭�`�F�b�N�e�[�u��
 */
//============================================================================================
static	const	u16	JuuryokuWazaTable[]={
	WAZANO_SORAWOTOBU,
	WAZANO_TOBIHANERU,
	WAZANO_TOBIGERI,
	WAZANO_TOBIHIZAGERI,
	WAZANO_HANERU,
	WAZANO_DENZIHUYUU,
};

//============================================================================================
/**
 *	���イ��傭�`�F�b�N
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	@param[in]	waza_no		�`�F�b�N����WazaNo
 *	
 *	@retval	FALSE:���イ��傭�̉e���������Ȃ��@TRUE:���イ��傭�̉e����������
 */
//============================================================================================
BOOL	ST_ServerJuuryokuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no)
{
	int		no;
	BOOL	ret;

	ret=FALSE;

	if(sp->field_condition&FIELD_CONDITION_JUURYOKU){
		for(no=0;no<NELEMS(JuuryokuWazaTable);no++){
			if(JuuryokuWazaTable[no]==waza_no){
				ret=TRUE;
				break;
			}
		}
	}

	return ret;
}

//============================================================================================
/**
 *	�q�[���u���b�N�`�F�b�N�e�[�u��
 */
//============================================================================================
static	const	u16	HealblockWazaTable[]={
	WAZANO_ZIKOSAISEI,
	WAZANO_TAMAGOUMI,
	WAZANO_NEMURU,
	WAZANO_MIRUKUNOMI,
	WAZANO_ASANOHIZASI,
	WAZANO_KOUGOUSEI,
	WAZANO_TUKINOHIKARI,
	WAZANO_NOMIKOMU,
	WAZANO_KAIHUKUSIREI,
	WAZANO_NAMAKERU,
	WAZANO_HANEYASUME,
	WAZANO_MIKADUKINOMAI,
	WAZANO_IYASINONEGAI,
	WAZANO_NEGAIGOTO,
};

//============================================================================================
/**
 *	�q�[���u���b�N�`�F�b�N
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	@param[in]	waza_no		�`�F�b�N����WazaNo
 *	
 *	@retval	FALSE:�q�[���u���b�N�̉e���������Ȃ��@TRUE:�q�[���u���b�N�̉e����������
 */
//============================================================================================
BOOL	ST_ServerHealblockCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no)
{
	int		no;
	BOOL	ret;

	ret=FALSE;

	if(sp->psp[client_no].wkw.healblock_count){
		OS_TPrintf("wazano:%d\n",waza_no);
		for(no=0;no<NELEMS(HealblockWazaTable);no++){
			if(HealblockWazaTable[no]==waza_no){
				ret=TRUE;
				break;
			}
		}
	}

	return ret;
}

//============================================================================================
/**
 *	�Ƃ��Ă����J�E���g�v�Z
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerTotteokiCountCalc(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	pos;

	//�Ƃ��Ă����́A�J�E���g���Ȃ�
	//�Ƃ��Ă����J�E���g��MAX�Ȃ�A�J�E���g���Ȃ�
	if((sp->waza_no_temp==WAZANO_TOTTEOKI)||(sp->psp[sp->attack_client].wkw.totteoki_count==WAZA_TEMOTI_MAX)){
		return;
	}

	for(pos=0;pos<sp->psp[sp->attack_client].wkw.totteoki_count;pos++){
		if(sp->psp[sp->attack_client].wkw.totteoki_wazano[pos]==sp->waza_no_temp){
			return;
		}
	}
	sp->psp[sp->attack_client].wkw.totteoki_wazano[pos]=sp->waza_no_temp;
	sp->psp[sp->attack_client].wkw.totteoki_count++;
}

//============================================================================================
/**
 *	�Z�����������Ă��邩�J�E���g
 *
 *	@param[in]	bw			�퓬�V�X�e���\���̂̃|�C���^
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�J�E���g����ClientNo
 */
//============================================================================================
int		ST_ServerWazaCountGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	count;

	for(count=0;count<WAZA_TEMOTI_MAX;count++){
		if(sp->psp[client_no].waza[count]==0){
			break;
		}
	}

	return count;
}

//============================================================================================
/**
 *	�_���[�W�������������̃`�F�b�N�p�f�[�^�e�[�u��
 */
//============================================================================================
//�ڂ�����e�[�u��
static	u16	BouonWazaTable[]={
	WAZANO_NAKIGOE,
	WAZANO_HOERU,
	WAZANO_UTAU,
	WAZANO_TYOUONPA,
	WAZANO_IYANAOTO,
	WAZANO_IBIKI,
	WAZANO_SAWAGU,
	WAZANO_KINZOKUON,
	WAZANO_KUSABUE,
	WAZANO_HAIPAABOISU,
	WAZANO_MUSINOSAZAMEKI,
	WAZANO_OSYABERI,
};

//============================================================================================
/**
 *	�_���[�W�������������̃`�F�b�N
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	attack		�U������ClientNo
 *	@param[in]	defence		�h�䂷��ClientNo
 */
//============================================================================================
int		ST_ServerDamageTokuseiCheck(SERVER_PARAM *sp,int attack,int defence)
{
	int	seq_no;
	int	wazatype;

	seq_no=0;

	//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(sp->waza_type){
		wazatype=sp->waza_type;
	}
	else{
//		wazatype=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_wazatype);
		wazatype=sp->AIWT.wtd[sp->waza_no_now].wazatype;
	}

	//�����ł�`�F�b�N
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TIKUDEN)==TRUE){
		if((wazatype==ELECTRIC_TYPE)&&(attack!=defence)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[defence].hpmax,4);
			seq_no=SUB_SEQ_TOKUSEI_HP_KAIFUKU;
		}
	}
	//���傷���`�F�b�N
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TYOSUI)==TRUE){
		if((wazatype==WATER_TYPE)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage))){
		   (sp->AIWT.wtd[sp->waza_no_now].damage)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[defence].hpmax,4);
			seq_no=SUB_SEQ_TOKUSEI_HP_KAIFUKU;
		}
	}
	//���炢�у`�F�b�N
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_MORAIBI)==TRUE){
		if((wazatype==FIRE_TYPE)&&
		  ((sp->psp[defence].condition&CONDITION_KOORI)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage))){
		  ((sp->AIWT.wtd[sp->waza_no_now].damage)||(sp->waza_no_now==WAZANO_ONIBI))){
			seq_no=SUB_SEQ_MORAIBI;
		}
	}
	//�ڂ�����`�F�b�N
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_BOUON)==TRUE){
		{
			int	no;

			for(no=0;no<NELEMS(BouonWazaTable);no++){
				if(BouonWazaTable[no]==sp->waza_no_now){
					seq_no=SUB_SEQ_BOUON;
					break;
				}
			}
		}
	}
	//�ł񂫃G���W���`�F�b�N	
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_DENKIENZIN)==TRUE){
		if((wazatype==ELECTRIC_TYPE)&&(attack!=defence)){
			seq_no=SUB_SEQ_DENKIENZIN;
		}
	}
	//���񂻂��͂��`�F�b�N
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_KANSOUHADA)==TRUE){
		if((wazatype==WATER_TYPE)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage))){
		   (sp->AIWT.wtd[sp->waza_no_now].damage)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[defence].hpmax,4);
			seq_no=SUB_SEQ_TOKUSEI_HP_KAIFUKU;
		}
	}

	return seq_no;
}

//============================================================================================
/**
 *	�^�[���`�F�b�N���̓����̃`�F�b�N
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 */
//============================================================================================
BOOL	ST_ServerPCCTokuseiCheck(SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	int		seq_no;

	ret=FALSE;

	switch(ST_ServerTokuseiGet(sp,client_no)){
	//������
	case TOKUSYU_KASOKU:
		if((sp->psp[client_no].hp)&&
		   (sp->psp[client_no].abiritycnt[COND_AGI]<12)&&
		   //�o�Ă����ŏ��̃^�[���́A�������𖳎�
		   (sp->psp[client_no].wkw.nekodamashi_count!=sp->total_turn+1)){
			sp->tsuika_para=ADD_COND2_AGIUP;
			sp->tsuika_type=ADD_STATUS_TOKUSEI;
			sp->tsuika_client=client_no;
			seq_no=SUB_SEQ_ABICNT_CALC;
			ret=TRUE;
		}
		break;
	//������
	case TOKUSYU_DAPPI:
#ifdef PM_DEBUG
		if((sp->psp[client_no].condition&CONDITION_BAD)&&
		   (sp->psp[client_no].hp)&&
		   ((gf_rand()%10<3)||(sp->dbp.debug_flag&DEBUG_FLAG_TOKUSYU))){
#else
		if((sp->psp[client_no].condition&CONDITION_BAD)&&
		   (sp->psp[client_no].hp)&&
		   (gf_rand()%10<3)){
#endif
			if(sp->psp[client_no].condition&CONDITION_NEMURI){
				sp->msg_work=MSG_COND_NEMURI;
			}
			else if(sp->psp[client_no].condition&CONDITION_DOKUALL){
				sp->msg_work=MSG_COND_DOKU;
			}
			else if(sp->psp[client_no].condition&CONDITION_YAKEDO){
				sp->msg_work=MSG_COND_YAKEDO;
			}
			else if(sp->psp[client_no].condition&CONDITION_MAHI){
				sp->msg_work=MSG_COND_MAHI;
			}
			else{
				sp->msg_work=MSG_COND_KOORI;
			}
			sp->client_work=client_no;
			seq_no=SUB_SEQ_DAPPI;
			ret=TRUE;
		}
		break;
	default:
		break;
	}
	if(ret==TRUE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	}

	return ret;
}

//============================================================================================
/**
 *	�_���[�W�v�Z�p�̊���Z���s���i���������ʂ��O�̎��́A1or-1�␳������
 *
 *	@param[in]	data	�����鐔
 *	@param[in]	value	���鐔
 *
 *	@retval	��
 */
//============================================================================================
int		ST_ServerDamageDiv(int data,int value)
{
	int	zero_flag;

	if(data<0){
		zero_flag=-1;
	}
	else{
		zero_flag=1;
	}

	data/=value;

	if(data==0){
		data=zero_flag;
	}

	return data;
}

//============================================================================================
//			ST_ServerPokeAppearCheck�̃V�[�P���X�i���o�[
//============================================================================================
enum{
	SPAC_WEATHER=0,
	SPAC_TRACE,
	SPAC_WEATHER_TOKUSEI,
	SPAC_IKAKU,
	SPAC_DOWNLOAD,
	SPAC_KIKENYOCHI,
	SPAC_YOCHIMU,
	SPAC_OMITOOSHI,
	SPAC_SLOWSTART,
	SPAC_KATAYABURI,
	SPAC_PRESSURE,
	SPAC_TENKIYA,
	SPAC_OKANE2BAI,
	SPAC_CONDITION_BAD_TOKUSEI,
	SPAC_CONDITION_BAD,
	SPAC_END
};

enum{
	SPAC_LOOP=0,
	SPAC_WAZA_SEQ,
	SPAC_CHECK_END
};

//============================================================================================
/**
 *	�|�P�����o�ꎞ�̃`�F�b�N�������Ȃ�
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 *
 * @retval	�`�F�b�N�Ɉ��������������ɋN������SUB_SEQ_NO
 */
//============================================================================================
int	ST_ServerPokeAppearCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i,j;
	int	seq_no;
	int	ret;
	int	client_no;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	seq_no=0;
	ret=SPAC_LOOP;

	do{
		switch(sp->spac_seq_no){
		//�V��`�F�b�N
		case SPAC_WEATHER:
			if(sp->weather_check_flag==0){
				switch(BattleWorkWeatherGet(bw)){
				case WEATHER_SYS_RAIN:			// �J
				case WEATHER_SYS_STRAIN:		// ��J
				case WEATHER_SYS_SPARK:			// ��J
					seq_no=SUB_SEQ_FIELD_AME;
					ret=SPAC_WAZA_SEQ;
					break;
				case WEATHER_SYS_SNOW:			// ��
				case WEATHER_SYS_SNOWSTORM:		// ����
				case WEATHER_SYS_SNOWSTORM_H:	// �Ґ���
					seq_no=SUB_SEQ_FIELD_ARARE;
					ret=SPAC_WAZA_SEQ;
					break;
				case WEATHER_SYS_SANDSTORM:		// BG�g�p����
					seq_no=SUB_SEQ_FIELD_SUNAARASHI;
					ret=SPAC_WAZA_SEQ;
					break;
				case WEATHER_SYS_MIST1:			// �������̖�
				case WEATHER_SYS_MIST2:			// �������̖�
					seq_no=SUB_SEQ_FIELD_HUKAIKIRI;
					ret=SPAC_WAZA_SEQ;
					break;
				}
				if(ret==SPAC_WAZA_SEQ){
					sp->weather_check_flag=1;
				}
			}
			sp->spac_seq_no++;
			break;
		//�����g���[�X�`�F�b�N
		case SPAC_TRACE:
			{
				int	def1,def2;
				
				for(i=0;i<client_set_max;i++){
					client_no=sp->psp_agi_work[i];
					def1=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_RIGHT);
					def2=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_LEFT);
					sp->defence_client_work=ST_ServerTraceClientNoGet(sp,def1,def2);
					if((sp->psp[client_no].trace_flag==0)&&
					   (sp->defence_client_work!=NONE_CLIENT_NO)&&
					   (sp->psp[client_no].hp)&&
					   (sp->psp[sp->defence_client_work].hp)&&
					   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_TOREESU)){
						sp->psp[client_no].trace_flag=1;
						sp->client_work=client_no;
						seq_no=SUB_SEQ_TRACE;
						ret=SPAC_WAZA_SEQ;
						break;
					}
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		
		case SPAC_WEATHER_TOKUSEI:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].appear_check_flag==0)&&
				   (sp->psp[client_no].hp)){
					switch(ST_ServerTokuseiGet(sp,client_no)){
					//�������߂ӂ炵
					case TOKUSYU_AMEHURASI:
						sp->psp[client_no].appear_check_flag=1;
						if((sp->field_condition&FIELD_CONDITION_AMEHURASHI)==0){
							seq_no=SUB_SEQ_AMEHURASI;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					//�������Ȃ�����
					case TOKUSYU_SUNAOKOSI:
						sp->psp[client_no].appear_check_flag=1;
						if((sp->field_condition&FIELD_CONDITION_SUNAOKOSHI)==0){
							seq_no=SUB_SEQ_SUNAOKOSI;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					//�����Ђł�
					case TOKUSYU_HIDERI:
						sp->psp[client_no].appear_check_flag=1;
						if((sp->field_condition&FIELD_CONDITION_HIDERI)==0){
							seq_no=SUB_SEQ_HIDERI;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					//�����䂫�ӂ炵
					case TOKUSYU_YUKIHURASI:
						sp->psp[client_no].appear_check_flag=1;
						if((sp->field_condition&FIELD_CONDITION_YUKIHURASHI)==0){
							seq_no=SUB_SEQ_YUKIHURASI;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					}
				}
				if(ret==SPAC_WAZA_SEQ){
					sp->client_work=client_no;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�����������`�F�b�N
		case SPAC_IKAKU:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].ikaku_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_IKAKU)){
					sp->psp[client_no].ikaku_flag=1;
					sp->client_work=client_no;
					seq_no=SUB_SEQ_IKAKU;
					ret=SPAC_WAZA_SEQ;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�����_�E�����[�h�`�F�b�N
		case SPAC_DOWNLOAD:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].download_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_DAUNROODO)){
					{
						int	no;
						int	def,spedef;

						def=0;
						spedef=0;

						for(no=0;no<client_set_max;no++){
							if((BattleWorkMineEnemyCheck(bw,client_no)!=BattleWorkMineEnemyCheck(bw,no))&&
							  ((sp->psp[no].condition2&CONDITION2_MIGAWARI)==0)&&
							   (sp->psp[no].hp)){
								def+=sp->psp[no].def*
									 CondChgTable[sp->psp[no].abiritycnt[COND_DEF]][0]/
									 CondChgTable[sp->psp[no].abiritycnt[COND_DEF]][1];
								spedef+=sp->psp[no].spedef*
									 CondChgTable[sp->psp[no].abiritycnt[COND_SPEDEF]][0]/
									 CondChgTable[sp->psp[no].abiritycnt[COND_SPEDEF]][1];
							}
						}
						sp->psp[client_no].download_flag=1;
						if((def+spedef)!=0){
							if(def>=spedef){
								sp->tsuika_para=ADD_COND2_SPEPOWUP;
							}
							else{
								sp->tsuika_para=ADD_COND2_POWUP;
							}
							sp->tsuika_type=ADD_STATUS_TOKUSEI;
							sp->tsuika_client=client_no;
							seq_no=SUB_SEQ_ABICNT_CALC;
							ret=SPAC_WAZA_SEQ;
							break;
						}
					}
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//����������悿
		case SPAC_KIKENYOCHI:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].kikenyochi_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KIKENYOTI)){
					sp->psp[client_no].kikenyochi_flag=1;
					{
						int	no,pos;
						u16	waza_no;
						u32	flag;

						for(no=0;no<client_set_max;no++){
							if((BattleWorkMineEnemyCheck(bw,client_no)!=BattleWorkMineEnemyCheck(bw,no))&&(sp->psp[no].hp)){
								for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
									waza_no=sp->psp[no].waza[pos];
									if(waza_no){
										flag=0;
										sp->damage=ST_ServerTypeCheck(bw,sp,waza_no,NULL,no,client_no,sp->damage,&flag);
										//����������悿�́A���ʔ��Q�A�ꌂ�K�E�̋Z�ɑ΂��Čx�����b�Z�[�W���o��
										if(((flag&WAZA_STATUS_FLAG_KOUKANAI)==0)&&
											(ST_ServerKikenyochiWazaSeqCheck(sp,waza_no)==FALSE)&&
										   ((flag&WAZA_STATUS_FLAG_BATSUGUN)||
										   ((sp->AIWT.wtd[waza_no].battleeffect==38)&&
											(sp->psp[client_no].level<=sp->psp[no].level)))){
											ret=SPAC_WAZA_SEQ;
											break;
										}
									}
								}
								if(ret==SPAC_WAZA_SEQ){
									break;
								}
							}
						}
						if(ret==SPAC_WAZA_SEQ){
							sp->client_work=client_no;
							seq_no=SUB_SEQ_KIKENYOCHI;
						}
						break;
					}
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�����悿��
		case SPAC_YOCHIMU:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].yochimu_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_YOTIMU)){
					sp->psp[client_no].yochimu_flag=1;
					{
						int	no,pos;
						u16	waza_no;
						u32	pow,pow_temp;
						int	hp;

						pow_temp=0;
						hp=0;

						for(no=0;no<client_set_max;no++){
							if((BattleWorkMineEnemyCheck(bw,client_no)!=BattleWorkMineEnemyCheck(bw,no))&&(sp->psp[no].hp)){
								hp+=sp->psp[no].hp;
								for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
									waza_no=sp->psp[no].waza[pos];
//									pow=WT_WazaDataParaGet(waza_no,ID_WTD_damage);
									pow=sp->AIWT.wtd[waza_no].damage;
									switch(pow){
									//�З͂P
									case 1:
//										switch(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)){
										switch(sp->AIWT.wtd[waza_no].battleeffect){
										//�ꌂ�K�E
										case 38:
											if((pow_temp<150)||
											  ((pow_temp==150)&&(gf_rand()&1))){
												pow_temp=150;
												sp->waza_work=waza_no;
											}
											break;
										//�J�E���^�[
										//�~���[�R�[�g
										//��������
										case 89:
										case 144:
										case 227:
											if((pow_temp<120)||
											  ((pow_temp==120)&&(gf_rand()&1))){
												pow_temp=120;
												sp->waza_work=waza_no;
											}
											break;
										default:
											if((pow_temp<80)||
											  ((pow_temp==80)&&(gf_rand()&1))){
												pow_temp=80;
												sp->waza_work=waza_no;
											}
											break;
										}
										break;
									default:
										if((pow_temp<pow)||
										  ((pow_temp==pow)&&(gf_rand()&1))){
											pow_temp=pow;
											sp->waza_work=waza_no;
										}
										break;
									}
								}
							}
						}
						if(pow_temp){
							sp->client_work=client_no;
							seq_no=SUB_SEQ_YOCHIMU;
							ret=SPAC_WAZA_SEQ;
						}
						//������Ȃ������ꍇ�́A�����Ă���Z���烉���_���őI��
						else if(hp){
							no=ST_ServerDirClientGet(bw,sp,client_no);
							pos=ST_ServerWazaCountGet(bw,sp,no);
							sp->waza_work=sp->psp[no].waza[gf_rand()%pos];
							sp->client_work=client_no;
							seq_no=SUB_SEQ_YOCHIMU;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					}
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�������݂Ƃ���
		case SPAC_OMITOOSHI:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].omitooshi_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_OMITOOSI)){
					sp->psp[client_no].omitooshi_flag=1;
					if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
						{
							int	def[2];

							def[0]=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_RIGHT);
							def[1]=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_LEFT);

							if((sp->psp[def[0]].hp)&&(sp->psp[def[0]].item)&&
							   (sp->psp[def[1]].hp)&&(sp->psp[def[1]].item)){
								sp->item_work=sp->psp[def[gf_rand()&1]].item;
								ret=SPAC_WAZA_SEQ;
							}
							else if((sp->psp[def[0]].hp)&&(sp->psp[def[0]].item)){
								sp->item_work=sp->psp[def[0]].item;
								ret=SPAC_WAZA_SEQ;
							}
							else if((sp->psp[def[1]].hp)&&(sp->psp[def[1]].item)){
								sp->item_work=sp->psp[def[1]].item;
								ret=SPAC_WAZA_SEQ;
							}
						}
					}
					else{
						if((sp->psp[client_no^1].hp)&&(sp->psp[client_no^1].item)){
							sp->item_work=sp->psp[client_no^1].item;
							ret=SPAC_WAZA_SEQ;
						}
					}
				}
				if(ret==SPAC_WAZA_SEQ){
					sp->client_work=client_no;
					seq_no=SUB_SEQ_OMITOOSHI;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�����X���[�X�^�[�g
		case SPAC_SLOWSTART:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				//����^�[���ƌ��ʐ؂�^�[���Ƀ��b�Z�[�W
				if((sp->psp[client_no].slow_start_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_SUROOSUTAATO)&&
				   (sp->total_turn<=sp->psp[client_no].wkw.slow_start_count)){
					sp->psp[client_no].slow_start_flag=1;
					sp->client_work=client_no;
					seq_no=SUB_SEQ_SLOWSTART;
					ret=SPAC_WAZA_SEQ;
					break;
				}
				if((sp->psp[client_no].slow_start_end_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_SUROOSUTAATO)&&
				  ((sp->total_turn-sp->psp[client_no].wkw.slow_start_count)==5)){
					sp->psp[client_no].slow_start_end_flag=1;
					sp->client_work=client_no;
					seq_no=SUB_SEQ_SLOWSTART_END;
					ret=SPAC_WAZA_SEQ;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//����������Ԃ�
		case SPAC_KATAYABURI:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].katayaburi_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KATAYABURI)){
					sp->psp[client_no].katayaburi_flag=1;
					sp->client_work=client_no;
					seq_no=SUB_SEQ_KATAYABURI;
					ret=SPAC_WAZA_SEQ;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�����v���b�V���[
		case SPAC_PRESSURE:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if((sp->psp[client_no].pressure_flag==0)&&
				   (sp->psp[client_no].hp)&&
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_PURESSYAA)){
					sp->psp[client_no].pressure_flag=1;
					sp->client_work=client_no;
					seq_no=SUB_SEQ_PRESSURE;
					ret=SPAC_WAZA_SEQ;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�����Ă񂫂�
		case SPAC_TENKIYA:
			if(ST_ServerTenkiyaCheck(bw,sp)==TRUE){
				seq_no=SUB_SEQ_TENKIYA;
				ret=SPAC_WAZA_SEQ;
			}
			else{
				sp->spac_seq_no++;
			}
			break;
		//�������ʂ���2�{
		case SPAC_OKANE2BAI:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if(ST_ItemParamGet(sp,sp->psp[client_no].item,ITEM_PRM_EQUIP)==SOUBI_OKANENIBAI){
					sp->okodukai_value=2;	///<���������̔{�����[�N
				}
			}
			sp->spac_seq_no++;
			break;
		case SPAC_CONDITION_BAD_TOKUSEI:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if(ST_ServerTokuseiStatusRecoverCheck(bw,sp,client_no,1)==TRUE){
					seq_no=SUB_SEQ_TOKUSEI_CONDITION_RECOVER;
					ret=SPAC_WAZA_SEQ;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		case SPAC_CONDITION_BAD:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if(ST_ServerSoubiItemConditionBadCheck(bw,sp,client_no,&seq_no)==TRUE){
					sp->client_work=client_no;
					ret=SPAC_WAZA_SEQ;
					break;
				}
			}
			if(i==client_set_max){
				sp->spac_seq_no++;
			}
			break;
		//�`�F�b�N�I��
		case SPAC_END:
			sp->spac_seq_no=0;
			ret=SPAC_CHECK_END;
			break;
		}
	}while(ret==SPAC_LOOP);

	return seq_no;
}

//============================================================================================
/**
 *	���葤2�̂̂���1�̂������_���őI���i1vs1�̎��͑f���ɑ��葤��I���j
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	�I������ClientNo
 */
//============================================================================================
int	ST_ServerDirClientGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	u32	fight_type;
	int	defence;
	int	def[2];
	int	i;

	fight_type=BattleWorkFightTypeGet(bw);

	if(fight_type&FIGHT_TYPE_2vs2){
		def[0]=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_RIGHT);
		def[1]=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_LEFT);
		i=gf_rand()&1;
		defence=def[i];
		if(sp->psp[defence].hp==0){
			defence=def[i^1];
		}
	}
	else{
		defence=client_no^1;
	}

	return defence;
}

//============================================================================================
/**
 *	�Z���q�b�g�������Ƀ`�F�b�N�������
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	seq_no		������������seq_no��������|�C���^���[�N
 *
 * @retval	TRUE:���������@FALSE:�����s��
 */
//============================================================================================
BOOL	ST_ServerWazaHitTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret;

	ret=FALSE;

	//�U���Ώۂ����Ȃ���΁A�`�F�b�N�Ȃ�
	if(sp->defence_client==NONE_CLIENT_NO){
		return ret;
	}

	//�݂����ł͕s��
	if(ST_ServerMigawariCheck(sp,sp->defence_client)==TRUE){
		return ret;
	}

	switch(ST_ServerTokuseiGet(sp,sp->defence_client)){
	//�����ł�
	case TOKUSYU_SEIDENKI:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		  ((gf_rand()%10<3)||(sp->dbp.debug_flag&DEBUG_FLAG_TOKUSYU))){
#else
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		   (gf_rand()%10<3)){
#endif
			sp->tsuika_type=ADD_STATUS_TOKUSEI;
			sp->tsuika_client=sp->attack_client;
			sp->client_work=sp->defence_client;
			seq_no[0]=SUB_SEQ_MAHI;
			ret=TRUE;
		}
		break;
	//�ւ񂵂傭
	case TOKUSYU_HENSYOKU:
		{
			u8	wazatype;

			//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
			if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOMARUSUKIN){
				wazatype=NORMAL_TYPE;
			}
			else if(sp->waza_type){
				wazatype=sp->waza_type;
			}
			else{
//				wazatype=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_wazatype);
				wazatype=sp->AIWT.wtd[sp->waza_no_now].wazatype;
			}

			if((sp->psp[sp->defence_client].hp)&&
			  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
			   (sp->waza_no_now!=WAZANO_WARUAGAKI)&&
			  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
			   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
				//�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
			  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
//			   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage))&&
			   (sp->AIWT.wtd[sp->waza_no_now].damage)&&
			   (ST_ServerPokemonServerParamGet(sp,sp->defence_client,ID_PSP_type1,NULL)!=wazatype)&&
			   (ST_ServerPokemonServerParamGet(sp,sp->defence_client,ID_PSP_type2,NULL)!=wazatype)){
				seq_no[0]=SUB_SEQ_HENSYOKU;
				sp->msg_work=wazatype;
				ret=TRUE;
			}
		}
		break;
	//���߂͂�
	case TOKUSYU_SAMEHADA:
		if((sp->psp[sp->attack_client].hp)&&
			//�����}�W�b�N�K�[�h�́A���߂͂��̌��ʂ��󂯂Ȃ�
		   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)){
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*-1,8);
			sp->client_work=sp->attack_client;
			seq_no[0]=SUB_SEQ_SAMEHADA;
			ret=TRUE;
		}
		break;
	//�ق���
	case TOKUSYU_HOUSI:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		  //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		  ((gf_rand()%10<3)||(sp->dbp.debug_flag&DEBUG_FLAG_TOKUSYU))){
#else
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		   (gf_rand()%10<3)){
#endif
			switch(gf_rand()%3){
			case 0:
			default:
				seq_no[0]=SUB_SEQ_DOKU;
				break;
			case 1:
				seq_no[0]=SUB_SEQ_MAHI;
				break;
			case 2:
				seq_no[0]=SUB_SEQ_NEMURI;
				break;
			}
			sp->tsuika_type=ADD_STATUS_TOKUSEI;
			sp->tsuika_client=sp->attack_client;
			sp->client_work=sp->defence_client;
			ret=TRUE;
		}
		break;
	//�ǂ��̂Ƃ�
	case TOKUSYU_DOKUNOTOGE:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		  ((gf_rand()%10<3)||(sp->dbp.debug_flag&DEBUG_FLAG_TOKUSYU))){
#else
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		   (gf_rand()%10<3)){
#endif
			sp->tsuika_type=ADD_STATUS_TOKUSEI;
			sp->tsuika_client=sp->attack_client;
			sp->client_work=sp->defence_client;
			seq_no[0]=SUB_SEQ_DOKU;
			ret=TRUE;
		}
		break;
	//�ق̂��̂��炾
	case TOKUSYU_HONOONOKARADA:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		  ((gf_rand()%10<3)||(sp->dbp.debug_flag&DEBUG_FLAG_TOKUSYU))){
#else
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		   (gf_rand()%10<3)){
#endif
			sp->tsuika_type=ADD_STATUS_TOKUSEI;
			sp->tsuika_client=sp->attack_client;
			sp->client_work=sp->defence_client;
			seq_no[0]=SUB_SEQ_YAKEDO;
			ret=TRUE;
		}
		break;
	//���������{�f�B
	case TOKUSYU_MEROMEROBODHI:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_MEROMERO)==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		   (sp->psp[sp->defence_client].hp)&&
		  ((gf_rand()%10<3)||(sp->dbp.debug_flag&DEBUG_FLAG_TOKUSYU))){
#else
		if((sp->psp[sp->attack_client].hp)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_MEROMERO)==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)&&
		   (sp->psp[sp->defence_client].hp)&&
		   (gf_rand()%10<3)){
#endif
			sp->tsuika_type=ADD_STATUS_TOKUSEI;
			sp->tsuika_client=sp->attack_client;
			sp->client_work=sp->defence_client;
			seq_no[0]=SUB_SEQ_MEROMERO;
			ret=TRUE;
		}
		break;
	//�䂤�΂�
	case TOKUSYU_YUUBAKU:
		if((sp->defence_client==sp->kizetsu_client)&&
			//�����}�W�b�N�K�[�h�́A�䂤�΂��̌��ʂ��󂯂Ȃ�
		   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
		   //�������߂肯�����鎞�́A�䂤�΂��ł��Ȃ�
		   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_SIMERIKE)==0)&&
		   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
		   (sp->psp[sp->attack_client].hp)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)){
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*-1,4);
			sp->client_work=sp->attack_client;
			seq_no[0]=SUB_SEQ_YUUBAKU;
			ret=TRUE;
		}
		break;
	default:
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	�Z���q�b�g�������Ƀ`�F�b�N��������i�X�L���X���b�v�ȂǂŁA����������ւ���ď�Ԉُ�𒼂��`�F�b�N�j
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 * @param[in]	act_flag	����t���O�i0:�K�v�ȃ��[�N�ɂ��ׂđ���@1:�V�[�P���X�i���o�[�ނ̑���͂��Ȃ��j
 *
 * @retval	TRUE:���������@FALSE:�����s��
 */
//============================================================================================
BOOL	ST_ServerTokuseiStatusRecoverCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int act_flag)
{
	BOOL	ret;

	ret=FALSE;

	switch(ST_ServerTokuseiGet(sp,client_no)){
	case TOKUSYU_MENEKI:
		if(sp->psp[client_no].condition&CONDITION_DOKUALL){
			sp->msg_work=MSG_COND_DOKU;
			ret=TRUE;
		}
		break;
	case TOKUSYU_MAIPEESU:
		if(sp->psp[client_no].condition2&CONDITION2_KONRAN){
			sp->msg_work=MSG_COND_KONRAN;
			ret=TRUE;
		}
		break;
	case TOKUSYU_ZYUUNAN:
		if(sp->psp[client_no].condition&CONDITION_MAHI){
			sp->msg_work=MSG_COND_MAHI;
			ret=TRUE;
		}
		break;
	case TOKUSYU_HUMIN:
	case TOKUSYU_YARUKI:
		if(sp->psp[client_no].condition&CONDITION_NEMURI){
			sp->msg_work=MSG_COND_NEMURI;
			ret=TRUE;
		}
		break;
	case TOKUSYU_MIZUNOBEERU:
		if(sp->psp[client_no].condition&CONDITION_YAKEDO){
			sp->msg_work=MSG_COND_YAKEDO;
			ret=TRUE;
		}
		break;
	case TOKUSYU_MAGUMANOYOROI:
		if(sp->psp[client_no].condition&CONDITION_KOORI){
			sp->msg_work=MSG_COND_KOORI;
			ret=TRUE;
		}
		break;
	case TOKUSYU_DONKAN:
		if(sp->psp[client_no].condition2&CONDITION2_MEROMERO){
			sp->msg_work=MSG_COND_MEROMERO;
			ret=TRUE;
		}
		break;
	case TOKUSYU_KARUWAZA:
		//�ǂ�ڂ���g���b�N�ŃA�C�e������肵�����Ƀt���O�𗧂Ă�
		if(sp->psp[client_no].item){
			sp->psp[client_no].wkw.karuwaza_flag=1;
		}
		break;
	}
	if(ret==TRUE){
		sp->client_work=client_no;
		sp->tokusei_work=ST_ServerTokuseiGet(sp,client_no);
		if(act_flag==0){
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TOKUSEI_CONDITION_RECOVER);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	����ւ����ɏ�Ԉُ�𒼂��������`�F�b�N
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	tokusei		�`�F�b�N�������
 * @param[in]	condition	�`�F�b�N�����Ԉُ�
 *
 * @retval	TRUE:���������@FALSE:�����s��
 */
//============================================================================================
BOOL	ST_ServerTokuseiStatusRecoverReshuffleCheck(SERVER_PARAM *sp,int tokusei,int condition)
{
	BOOL	ret;

	ret=FALSE;

	switch(tokusei){
	case TOKUSYU_MENEKI:
		if(condition&CONDITION_DOKUALL){
			ret=TRUE;
		}
		break;
	case TOKUSYU_ZYUUNAN:
		if(condition&CONDITION_MAHI){
			ret=TRUE;
		}
		break;
	case TOKUSYU_HUMIN:
	case TOKUSYU_YARUKI:
		if(condition&CONDITION_NEMURI){
			ret=TRUE;
		}
		break;
	case TOKUSYU_MIZUNOBEERU:
		if(condition&CONDITION_YAKEDO){
			ret=TRUE;
		}
		break;
	case TOKUSYU_MAGUMANOYOROI:
		if(condition&CONDITION_KOORI){
			ret=TRUE;
		}
		break;
	}

	return ret;
}

//============================================================================================
/**
 *	�Z���q�b�g�������Ƀ`�F�b�N��������i�V���N���̂݁j
 *
 * @param[in]	bw				�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp				�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	server_seq_no	sp->next_server_seq_no�ɃZ�b�g����i���o�[
 *
 * @retval	TRUE:���������@FALSE:�����s��
 */
//============================================================================================
BOOL	ST_ServerSinkuroCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int server_seq_no)
{
	BOOL	ret;
	int		seq_no;

	ret=FALSE;

	//�h�䑤�`�F�b�N
	if((ST_ServerTokuseiGet(sp,sp->defence_client)==TOKUSYU_SINKURO)&&
	   (sp->defence_client!=NONE_CLIENT_NO)&&
	   (sp->defence_client==sp->tsuika_client)&&
	   (sp->server_status_flag&SERVER_STATUS_FLAG_SINKURO_TSUIKA)){
		sp->client_work=sp->defence_client;
		sp->tsuika_client=sp->attack_client;
		ret=TRUE;
	}
	//�U�����`�F�b�N
	else if((ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_SINKURO)&&
	   (sp->attack_client==sp->tsuika_client)&&
	   (sp->server_status_flag&SERVER_STATUS_FLAG_SINKURO_TSUIKA)){
		sp->client_work=sp->attack_client;
		sp->tsuika_client=sp->defence_client;
		ret=TRUE;
	}

	if(ret==TRUE){
		if(sp->psp[sp->client_work].condition&CONDITION_DOKUALL){
			seq_no=SUB_SEQ_DOKU;
		}
		else if(sp->psp[sp->client_work].condition&CONDITION_YAKEDO){
			seq_no=SUB_SEQ_YAKEDO;
		}
		else{
			seq_no=SUB_SEQ_MAHI;
		}
		sp->tsuika_type=ADD_STATUS_TOKUSEI;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->next_server_seq_no=server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;

		return ret;
	}

	//�Ă񂫂���^�C�~���O�͂�������Ȃ̂Ń`�F�b�N����
	ret=ST_ServerTenkiyaCheck(bw,sp);
	if(ret==TRUE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKIYA);
		sp->next_server_seq_no=server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		return ret;
	}

	//�`�F�b�N����^�C�~���O�͓����Ȃ̂ŁA�����A�C�e���u���������Ɓv���`�F�b�N
	//�h�䑤�`�F�b�N
	if((ST_ServerSoubiEqpGet(sp,sp->defence_client)==SOUBI_MEROMERODETEKIMOMEROMERO)&&
	   (sp->defence_client!=NONE_CLIENT_NO)&&
	   (sp->defence_client==sp->tsuika_client)&&
	   (sp->ostf[sp->defence_client].status_flag&OSTF_STATUS_FLAG_MEROMERO)){
		sp->client_work=sp->defence_client;
		sp->tsuika_client=sp->attack_client;
		ret=TRUE;
	}
	//�U�����`�F�b�N
	else if((ST_ServerSoubiEqpGet(sp,sp->attack_client)==SOUBI_MEROMERODETEKIMOMEROMERO)&&
	   (sp->attack_client==sp->tsuika_client)&&
	   (sp->ostf[sp->attack_client].status_flag&OSTF_STATUS_FLAG_MEROMERO)){
		sp->client_work=sp->attack_client;
		sp->tsuika_client=sp->defence_client;
		ret=TRUE;
	}

	if(ret==TRUE){
		seq_no=SUB_SEQ_MEROMERO;
		sp->tsuika_type=ADD_STATUS_SOUBIITEM;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->next_server_seq_no=server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;

		return ret;
	}

	return FALSE;
}

//============================================================================================
/**
 *	�^�[���`�F�b�N���̑����A�C�e�����ʂ̃`�F�b�N
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	FALSE:�Ȃɂ��Ȃ�	TRUE:�������ʔ���
 */
//============================================================================================
BOOL	ST_ServerSoubiItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	int		seq_no;
	int		eqp;
	int		atk;

	ret=FALSE;

	eqp=ST_ServerSoubiEqpGet(sp,client_no);
	atk=ST_ServerSoubiAtkGet(sp,client_no,ATK_CHECK_NORMAL);

	if(sp->psp[client_no].hp){
		switch(eqp){
		case SOUBI_HPKAIHUKU:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=atk;
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				ret=TRUE;
			}
			break;
		case SOUBI_HPKAIHUKUHIRITU:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*atk,100);
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				ret=TRUE;
			}
			break;
		case SOUBI_MAHINAOSI:
			if(sp->psp[client_no].condition&CONDITION_MAHI){
				seq_no=SUB_SEQ_EQPITEM_NO_MAHI;
				ret=TRUE;
			}
			break;
		case SOUBI_NEMUKEZAMASI:
			if(sp->psp[client_no].condition&CONDITION_NEMURI){
				seq_no=SUB_SEQ_EQPITEM_NO_NEMURI;
				ret=TRUE;
			}
			break;
		case SOUBI_DOKUKESI:
			if(sp->psp[client_no].condition&CONDITION_DOKUALL){
				seq_no=SUB_SEQ_EQPITEM_NO_DOKU;
				ret=TRUE;
			}
			break;
		case SOUBI_YAKEDONAOSI:
			if(sp->psp[client_no].condition&CONDITION_YAKEDO){
				seq_no=SUB_SEQ_EQPITEM_NO_YAKEDO;
				ret=TRUE;
			}
			break;
		case SOUBI_KOORINAOSI:
			if(sp->psp[client_no].condition&CONDITION_KOORI){
				seq_no=SUB_SEQ_EQPITEM_NO_KOORI;
				ret=TRUE;
			}
			break;
		case SOUBI_PPKAIHUKU:
			{
				int	pos;

				for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
					if((sp->psp[client_no].waza[pos])&&
					   (sp->psp[client_no].pp[pos]==0)){
						break;
					}
				}
				if(pos!=WAZA_TEMOTI_MAX){
					ST_PokemonServerParamAdd(&sp->psp[client_no],ID_PSP_pp1+pos,atk);
					ST_PSPtoPPCopy(bw,sp,client_no);
					sp->waza_work=sp->psp[client_no].waza[pos];
					seq_no=SUB_SEQ_EQPITEM_PP_KAIHUKU;
					ret=TRUE;
				}
			}
			break;
		case SOUBI_KONRANNAOSI:
			if(sp->psp[client_no].condition2&CONDITION2_KONRAN){
				seq_no=SUB_SEQ_EQPITEM_NO_KONRAN;
				ret=TRUE;
			}
			break;
		case SOUBI_ZYOUTAIIZYOUNAOSI:
			if((sp->psp[client_no].condition&CONDITION_BAD)||
			   (sp->psp[client_no].condition2&CONDITION2_KONRAN)){
				if(sp->psp[client_no].condition&CONDITION_MAHI){
					seq_no=SUB_SEQ_EQPITEM_NO_MAHI;
				}
				if(sp->psp[client_no].condition&CONDITION_NEMURI){
					seq_no=SUB_SEQ_EQPITEM_NO_NEMURI;
				}
				if(sp->psp[client_no].condition&CONDITION_DOKUALL){
					seq_no=SUB_SEQ_EQPITEM_NO_DOKU;
				}
				if(sp->psp[client_no].condition&CONDITION_YAKEDO){
					seq_no=SUB_SEQ_EQPITEM_NO_YAKEDO;
				}
				if(sp->psp[client_no].condition&CONDITION_KOORI){
					seq_no=SUB_SEQ_EQPITEM_NO_KOORI;
				}
				if(sp->psp[client_no].condition2&CONDITION2_KONRAN){
					seq_no=SUB_SEQ_EQPITEM_NO_KONRAN;
				}
				if((sp->psp[client_no].condition&CONDITION_BAD)&&
				   (sp->psp[client_no].condition2&CONDITION2_KONRAN)){
					seq_no=SUB_SEQ_EQPITEM_NO_JOUTAIIJOU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_KARAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_KARAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_KARAI)==DISLIKE_TASTE){
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_SIBUIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_SIBUI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_SIBUI)==DISLIKE_TASTE){
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_AMAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_AMAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_AMAI)==DISLIKE_TASTE){
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_NIGAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_NIGAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_NIGAI)==DISLIKE_TASTE){
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_SUPPAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_SUPPAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_SUPPAI)==DISLIKE_TASTE){
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_KOUGEKIUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_POW]<12)){
				sp->msg_work=COND_POW;
				seq_no=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_BOUGYOUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_DEF]<12)){
				sp->msg_work=COND_DEF;
				seq_no=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_SUBAYASAUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_AGI]<12)){
				sp->msg_work=COND_AGI;
				seq_no=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_TOKUKOUUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_SPEPOW]<12)){
				sp->msg_work=COND_SPEPOW;
				seq_no=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_TOKUBOUUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_SPEDEF]<12)){
				sp->msg_work=COND_SPEDEF;
				seq_no=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_KURITHIKARUUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			  ((sp->psp[client_no].condition2&CONDITION2_KIAIDAME)==0)){
				seq_no=SUB_SEQ_EQPITEM_CRITICALUP;
				ret=TRUE;
			}
			break;
		case SOUBI_NOURYOKURNDUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk)){
				{
					int	i;

					for(i=0;i<5;i++){
						if(sp->psp[client_no].abiritycnt[COND_POW+i]<12){
							break;
						}
					}
					if(i!=5){
						do{
							i=gf_rand()%5;
						}while(sp->psp[client_no].abiritycnt[COND_POW+i]==12);
						sp->msg_work=COND_POW+i;
						seq_no=SUB_SEQ_EQPITEM_CONDUP_MAX;
						ret=TRUE;
					}
				}
			}
			break;
		case SOUBI_NOURYOKUKAIHUKU:
			{
				int	i;

				for(i=0;i<COND_MAX;i++){
					if(sp->psp[client_no].abiritycnt[i]<6){
						sp->psp[client_no].abiritycnt[i]=6;
						ret=TRUE;
					}
				}
				if(ret==TRUE){
					seq_no=SUB_SEQ_EQPITEM_ABIRITY_KAIHUKU;
				}
			}
			break;
		case SOUBI_MEROMERONAOSI:
			if(sp->psp[client_no].condition2&CONDITION2_MEROMERO){
				sp->msg_work=MSG_COND_MEROMERO;
				seq_no=SUB_SEQ_EQPITEM_NO_MEROMERO;
				ret=TRUE;
			}
			break;
		case SOUBI_ITIDODAKEMEITYUUUP:
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk)){
				seq_no=SUB_SEQ_EQPITEM_ONCE_HIT_UP;
				ret=TRUE;
			}
			break;
		case SOUBI_ITIDODAKESENSEI:
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk)){
				sp->psp[client_no].wkw.once_agi_up=1;
			}
			break;
		default:
			break;
		}
		if(ret==TRUE){
			sp->client_work=client_no;
			sp->item_work=ST_ServerSoubiItemNoGet(sp,client_no);
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	�^�[���`�F�b�N���̑����A�C�e�����ʂ̃`�F�b�N�i���ׂ̂����A���낢�w�h���j
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	FALSE:�Ȃɂ��Ȃ�	TRUE:�������ʔ���
 */
//============================================================================================
BOOL	ST_ServerSoubiItemTabenokosiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	int		seq_no;
	int		eqp;
	int		atk;

	ret=FALSE;

	eqp=ST_ServerSoubiEqpGet(sp,client_no);
	atk=ST_ServerSoubiAtkGet(sp,client_no,ATK_CHECK_NORMAL);

	if(sp->psp[client_no].hp){
		switch(eqp){
		case SOUBI_HPKAIHUKUMAITURN:
			if(sp->psp[client_no].hp<(sp->psp[client_no].hpmax)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,16);
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKUMAITURN;
				ret=TRUE;
			}
			break;
		case SOUBI_DOKUKAIHUKU:
			if((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)==POISON_TYPE)||
			   (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)==POISON_TYPE)){
				if(sp->psp[client_no].hp<(sp->psp[client_no].hpmax)){
					sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,16);
					seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKUMAITURN;
					ret=TRUE;
				}
			}
			//�����}�W�b�N�K�[�h�̓_���[�W�Ȃ�
			else if(ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_MAZIKKUGAADO){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,8);
				seq_no=SUB_SEQ_EQPITEM_DAMAGE;
				ret=TRUE;
			}
			break;
		default:
			break;
		}
		if(ret==TRUE){
			sp->client_work=client_no;
			sp->item_work=ST_ServerSoubiItemNoGet(sp,client_no);
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		}
	}
	return ret;
}

//============================================================================================
/**
 *	�����A�C�e�����ʂ̃`�F�b�N�i��Ԉُ�n�𒼂��z�̂݁j
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	@param[in]	seq_no		�N������V�[�P���X�i���o�[
 *
 *	@retval	FALSE:�Ȃɂ��Ȃ�	TRUE:�������ʔ���
 */
//============================================================================================
BOOL	ST_ServerSoubiItemConditionBadCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int *seq_no)
{
	BOOL	ret;
	u16		item_no;
	int		eqp;
	int		atk;

	ret=FALSE;

	eqp=ST_ServerSoubiEqpGet(sp,client_no);
	atk=ST_ServerSoubiAtkGet(sp,client_no,ATK_CHECK_NORMAL);

	if(sp->psp[client_no].hp){
		switch(eqp){
		case SOUBI_HPKAIHUKU:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=atk;
				seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				ret=TRUE;
			}
			break;
		case SOUBI_HPKAIHUKUHIRITU:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*atk,100);
				seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				ret=TRUE;
			}
			break;
		case SOUBI_MAHINAOSI:
			if(sp->psp[client_no].condition&CONDITION_MAHI){
				seq_no[0]=SUB_SEQ_EQPITEM_NO_MAHI;
				ret=TRUE;
			}
			break;
		case SOUBI_NEMUKEZAMASI:
			if(sp->psp[client_no].condition&CONDITION_NEMURI){
				seq_no[0]=SUB_SEQ_EQPITEM_NO_NEMURI;
				ret=TRUE;
			}
			break;
		case SOUBI_DOKUKESI:
			if(sp->psp[client_no].condition&CONDITION_DOKUALL){
				seq_no[0]=SUB_SEQ_EQPITEM_NO_DOKU;
				ret=TRUE;
			}
			break;
		case SOUBI_YAKEDONAOSI:
			if(sp->psp[client_no].condition&CONDITION_YAKEDO){
				seq_no[0]=SUB_SEQ_EQPITEM_NO_YAKEDO;
				ret=TRUE;
			}
			break;
		case SOUBI_KOORINAOSI:
			if(sp->psp[client_no].condition&CONDITION_KOORI){
				seq_no[0]=SUB_SEQ_EQPITEM_NO_KOORI;
				ret=TRUE;
			}
			break;
		case SOUBI_PPKAIHUKU:
			{
				int	pos;

				for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
					if((sp->psp[client_no].waza[pos])&&
					   (sp->psp[client_no].pp[pos]==0)){
						break;
					}
				}
				if(pos!=WAZA_TEMOTI_MAX){
					ST_PokemonServerParamAdd(&sp->psp[client_no],ID_PSP_pp1+pos,atk);
					ST_PSPtoPPCopy(bw,sp,client_no);
					sp->waza_work=sp->psp[client_no].waza[pos];
					seq_no[0]=SUB_SEQ_EQPITEM_PP_KAIHUKU;
					ret=TRUE;
				}
			}
			break;
		case SOUBI_KONRANNAOSI:
			if(sp->psp[client_no].condition2&CONDITION2_KONRAN){
				seq_no[0]=SUB_SEQ_EQPITEM_NO_KONRAN;
				ret=TRUE;
			}
			break;
		case SOUBI_ZYOUTAIIZYOUNAOSI:
			if((sp->psp[client_no].condition&CONDITION_BAD)||
			   (sp->psp[client_no].condition2&CONDITION2_KONRAN)){
				if(sp->psp[client_no].condition&CONDITION_MAHI){
					seq_no[0]=SUB_SEQ_EQPITEM_NO_MAHI;
				}
				if(sp->psp[client_no].condition&CONDITION_NEMURI){
					seq_no[0]=SUB_SEQ_EQPITEM_NO_NEMURI;
				}
				if(sp->psp[client_no].condition&CONDITION_DOKUALL){
					seq_no[0]=SUB_SEQ_EQPITEM_NO_DOKU;
				}
				if(sp->psp[client_no].condition&CONDITION_YAKEDO){
					seq_no[0]=SUB_SEQ_EQPITEM_NO_YAKEDO;
				}
				if(sp->psp[client_no].condition&CONDITION_KOORI){
					seq_no[0]=SUB_SEQ_EQPITEM_NO_KOORI;
				}
				if(sp->psp[client_no].condition2&CONDITION2_KONRAN){
					seq_no[0]=SUB_SEQ_EQPITEM_NO_KONRAN;
				}
				if((sp->psp[client_no].condition&CONDITION_BAD)&&
				   (sp->psp[client_no].condition2&CONDITION2_KONRAN)){
					seq_no[0]=SUB_SEQ_EQPITEM_NO_JOUTAIIJOU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_NOURYOKUKAIHUKU:
			{
				int	i;

				for(i=0;i<COND_MAX;i++){
					if(sp->psp[client_no].abiritycnt[i]<6){
						sp->psp[client_no].abiritycnt[i]=6;
						ret=TRUE;
					}
				}
				if(ret==TRUE){
					seq_no[0]=SUB_SEQ_EQPITEM_ABIRITY_KAIHUKU;
				}
			}
			break;
		case SOUBI_MEROMERONAOSI:
			if(sp->psp[client_no].condition2&CONDITION2_MEROMERO){
				sp->msg_work=MSG_COND_MEROMERO;
				seq_no[0]=SUB_SEQ_EQPITEM_NO_MEROMERO;
				ret=TRUE;
			}
			break;
		case SOUBI_ITIDODAKEMEITYUUUP:
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk)){
				seq_no[0]=SUB_SEQ_EQPITEM_ONCE_HIT_UP;
				ret=TRUE;
			}
			break;
		case SOUBI_ITIDODAKESENSEI:
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk)){
				sp->psp[client_no].wkw.once_agi_up=1;
			}
			break;
		case SOUBI_KARAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_KARAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_KARAI)==DISLIKE_TASTE){
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_SIBUIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_SIBUI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_SIBUI)==DISLIKE_TASTE){
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_AMAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_AMAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_AMAI)==DISLIKE_TASTE){
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_NIGAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_NIGAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_NIGAI)==DISLIKE_TASTE){
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_SUPPAIKONRAN:
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/2)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,atk);
				sp->msg_work=TASTE_SUPPAI;
				if(PokeLikeTasteCheck(sp->psp[client_no].personal_rnd,TASTE_SUPPAI)==DISLIKE_TASTE){
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
				}
				else{
					seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
				}
				ret=TRUE;
			}
			break;
		case SOUBI_KOUGEKIUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_POW]<12)){
				sp->msg_work=COND_POW;
				seq_no[0]=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_BOUGYOUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_DEF]<12)){
				sp->msg_work=COND_DEF;
				seq_no[0]=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_SUBAYASAUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_AGI]<12)){
				sp->msg_work=COND_AGI;
				seq_no[0]=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_TOKUKOUUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_SPEPOW]<12)){
				sp->msg_work=COND_SPEPOW;
				seq_no[0]=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_TOKUBOUUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			   (sp->psp[client_no].abiritycnt[COND_SPEDEF]<12)){
				sp->msg_work=COND_SPEDEF;
				seq_no[0]=SUB_SEQ_EQPITEM_CONDUP;
				ret=TRUE;
			}
			break;
		case SOUBI_KURITHIKARUUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if((sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk))&&
			  ((sp->psp[client_no].condition2&CONDITION2_KIAIDAME)==0)){
				seq_no[0]=SUB_SEQ_EQPITEM_CRITICALUP;
				ret=TRUE;
			}
			break;
		case SOUBI_NOURYOKURNDUP:
			//������������ڂ́A�����i�K�ŋN������悤��
			if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KUISINBOU){
				atk/=2;
			}
			if(sp->psp[client_no].hp<=(sp->psp[client_no].hpmax/atk)){
				{
					int	i;

					for(i=0;i<5;i++){
						if(sp->psp[client_no].abiritycnt[COND_POW+i]<12){
							break;
						}
					}
					if(i!=5){
						do{
							i=gf_rand()%5;
						}while(sp->psp[client_no].abiritycnt[COND_POW+i]==12);
						sp->msg_work=COND_POW+i;
						seq_no[0]=SUB_SEQ_EQPITEM_CONDUP_MAX;
						ret=TRUE;
					}
				}
			}
			break;
		default:
			break;
		}
		if(ret==TRUE){
//			sp->client_work=client_no;
			sp->item_work=ST_ServerSoubiItemNoGet(sp,client_no);
//			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
//			sp->next_server_seq_no=sp->server_seq_no;
//			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		}
	}

	return ret;
}

//============================================================================================
/*
 *	�����A�C�e�����ʂ̃`�F�b�N�i�_���[�W�n�j
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	�����A�C�e���i���o�[
 */
//============================================================================================
BOOL	ST_ServerSoubiItemDamageCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	int		seq_no;
	u16		item_no;
	int		eqp;
	int		atk;

	ret=FALSE;

	eqp=ST_ServerSoubiEqpGet(sp,client_no);
	atk=ST_ServerSoubiAtkGet(sp,client_no,ATK_CHECK_NORMAL);

	if(sp->psp[client_no].hp){
		switch(eqp){
		case SOUBI_TEKINIMOTASERUTOMOUDOKU:
			sp->tsuika_client=client_no;
			sp->tsuika_type=ADD_STATUS_SOUBIITEM;
			seq_no=SUB_SEQ_DOKUDOKU;
			ret=TRUE;
			break;
		case SOUBI_TTEKINIMOTASERUTOYAKEDO:
			sp->tsuika_client=client_no;
			sp->tsuika_type=ADD_STATUS_SOUBIITEM;
			seq_no=SUB_SEQ_YAKEDO;
			ret=TRUE;
			break;
		case SOUBI_TEKINIMOTASETEDAMEEZI:
			//�����}�W�b�N�K�[�h�̓_���[�W�Ȃ�
			if(ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_MAZIKKUGAADO){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,atk);
				seq_no=SUB_SEQ_EQPITEM_DAMAGE;
				ret=TRUE;
			}
			break;
		default:
			break;
		}
		if(ret==TRUE){
			sp->client_work=client_no;
			sp->item_work=ST_ServerSoubiItemNoGet(sp,client_no);
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		}
	}
	return ret;
}

//============================================================================================
/*
 *	�����A�C�e���i���o�[�̎擾
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	�����A�C�e���i���o�[
 */
//============================================================================================
u16	ST_ServerSoubiItemNoGet(SERVER_PARAM *sp,int client_no)
{
	//�����Ԃ��悤�́A�A�C�e�����g�����Ȃ��Ȃ�
	if((ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_BUKIYOU)){
		return 0;
	}
	//�V���b�g�A�E�g�̋Z���ʔ������́A�A�C�e�����g���Ȃ�
	if(sp->psp[client_no].wkw.shutout_count){
		return 0;
	}
	
	return sp->psp[client_no].item;
}

//============================================================================================
/*
 *	�`�F�b�N�Ώۂ�������I�����Ă��邩�`�F�b�N
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	FALSE:�܂����삵�Ă��Ȃ��@TRUE:����I��
 */
//============================================================================================
BOOL	ST_ServerWazaEndCheck(SERVER_PARAM *sp,int client_no)
{
	return (sp->client_act_work[client_no][ACT_PARA_ACT_NO]==SERVER_WAZA_END_NO);
}

//============================================================================================
/**
 *	�Z���q�b�g�������Ƀ`�F�b�N���鑕������
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[out]	seq_no		�V�[�P���X�i���o�[�i�[���[�N
 *
 * @retval	TRUE:�������ʔ����@FALSE:�������ʕs��
 */
//============================================================================================
BOOL	ST_ServerWazaHitSoubiItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret;
	u16		item_no;
	int		eqp;
	int		atk;
	int		dir;

	ret=FALSE;

	//�U���Ώۂ����Ȃ��ꍇ�́A�`�F�b�N�Ȃ�
	if(sp->defence_client==NONE_CLIENT_NO){
		return ret;
	}

	//�݂����ł͕s��
	if(ST_ServerMigawariCheck(sp,sp->defence_client)==TRUE){
		return ret;
	}

	eqp=ST_ServerSoubiEqpGet(sp,sp->defence_client);
	atk=ST_ServerSoubiAtkGet(sp,sp->defence_client,ATK_CHECK_NORMAL);
	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);

	switch(eqp){
	case SOUBI_TEKINIMOTASETEDAMEEZI:
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].item==0)&&
		  ((sp->scw[dir].hatakiotosu_item&No2Bit(sp->sel_mons_no[sp->attack_client]))==0)&&
		   //�͂������Ƃ��͏��O
		   (sp->waza_no_now!=WAZANO_HATAKIOTOSU)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_DAGEKI)){
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)){
			seq_no[0]=SUB_SEQ_EQPITEM_KUTTUKI;
			ret=TRUE;
		}
		break;
	case SOUBI_BUTURIDEKOUGEKI:
		if((sp->psp[sp->attack_client].hp)&&
			//�����}�W�b�N�K�[�h�ɂ͕s��
		   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
#if B1368_060815_FIX
		  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
#endif //B1368_060815_FIX
		   (sp->ostf[sp->defence_client].butsuri_ostf_damage)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*-1,atk);
			seq_no[0]=SUB_SEQ_EQPITEM_HIT_DAMAGE;
			ret=TRUE;
		}
		break;
	case SOUBI_TOKUSYUDEKOUGEKI:
		if((sp->psp[sp->attack_client].hp)&&
			//�����}�W�b�N�K�[�h�ɂ͕s��
		   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*-1,atk);
			seq_no[0]=SUB_SEQ_EQPITEM_HIT_DAMAGE;
			ret=TRUE;
		}
		break;
	case SOUBI_BATUGUNKAIHUKU:
		if((sp->psp[sp->defence_client].hp)&&
		   (sp->waza_status_flag&WAZA_STATUS_FLAG_BATSUGUN)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax,atk);
			seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			sp->client_work=sp->defence_client;
			sp->item_work=sp->psp[sp->defence_client].item;
			ret=TRUE;
		}
		break;
	default:
		break;
	}
#if 0
	if(ret==TRUE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	}
#endif

	return ret;
}

//============================================================================================
/**
 *	�������ʃi���o�[���擾
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�������ʃi���o�[���擾����ClientNo
 *
 * @retval	�������ʃi���o�[
 */
//============================================================================================
s32	ST_ServerSoubiEqpGet(SERVER_PARAM *sp,int client_no)
{
	u16		item_no;

	item_no=ST_ServerSoubiItemNoGet(sp,client_no);

//	return ItemParamGet(item_no,ITEM_PRM_EQUIP,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,item_no,ITEM_PRM_EQUIP);
}

//============================================================================================
/**
 *	�������ʈЗ͂��擾
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�������ʈЗ͂��擾����ClientNo
 * @param[in]	flag		�Z���ʂ𔻒f���Ȃ��Ă������ǂ����t���O�i0:���f����@1:���f���Ȃ��j
 *
 * @retval	�������ʈЗ�
 */
//============================================================================================
s32	ST_ServerSoubiAtkGet(SERVER_PARAM *sp,int client_no,int flag)
{
	u16		item_no;

	switch(flag){
	case ATK_CHECK_NORMAL:	//�`�F�b�N����
		item_no=ST_ServerSoubiItemNoGet(sp,client_no);
		break;
	case ATK_CHECK_SHUTOUT:	//�V���b�g�A�E�g�����`�F�b�N����
		if(sp->psp[client_no].wkw.shutout_count){
			return 0;
		}
	case ATK_CHECK_NONE:	//�`�F�b�N�Ȃ�
		item_no=sp->psp[client_no].item;
		break;
	}

//	return ItemParamGet(item_no,ITEM_PRM_ATTACK,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,item_no,ITEM_PRM_ATTACK);
}

//============================================================================================
/**
 *	������̂߂��݈З͂��擾
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�З͂��擾����ClientNo
 *
 * @retval	������̂߂��݈З�
 */
//============================================================================================
s32	ST_ServerShizennomegumiAtkGet(SERVER_PARAM *sp,int client_no)
{
	u16	item_no;

	item_no=ST_ServerSoubiItemNoGet(sp,client_no);

//	return ItemParamGet(item_no,ITEM_PRM_SIZENNOMEGUMI_ATC,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,item_no,ITEM_PRM_SIZENNOMEGUMI_ATC);
}

//============================================================================================
/**
 *	������̂߂��݃^�C�v���擾
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�^�C�v���擾����ClientNo
 *
 * @retval	������̂߂��݃^�C�v
 */
//============================================================================================
s32	ST_ServerShizennomegumiTypeGet(SERVER_PARAM *sp,int client_no)
{
	u16	item_no;

	item_no=ST_ServerSoubiItemNoGet(sp,client_no);

//	return ItemParamGet(item_no,ITEM_PRM_SIZENNOMEGUMI_TYPE,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,item_no,ITEM_PRM_SIZENNOMEGUMI_TYPE);
}

//============================================================================================
/**
 *	���΂ތ��ʃi���o�[���擾
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	���΂ތ��ʃi���o�[���擾����ClientNo
 *
 * @retval	���΂ތ��ʃi���o�[
 */
//============================================================================================
s32	ST_ServerTsuibamuEqpGet(SERVER_PARAM *sp,int client_no)
{
	u16	item_no;
	int	eqp;

	//���΂ނ́A�Z���ʂŃA�C�e���g���Ȃ��󋵂𔻒f���Ȃ��Ă����̂ŁA���ڎ��
//	item_no=ST_ServerSoubiItemNoGet(sp,client_no);
	item_no=sp->psp[client_no].item;
//	eqp=ItemParamGet(item_no,ITEM_PRM_TUIBAMU_EFF,HEAPID_BATTLE);
	eqp=ST_ItemParamGet(sp,item_no,ITEM_PRM_TUIBAMU_EFF);

#if 0
	if(eqp){
		//�����˂񂿂Ⴍ�́A���΂߂Ȃ�
		if(ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,TOKUSYU_NENTYAKU)==TRUE){
			eqp=0;
		}
	}
#endif

	return eqp;
}

//============================================================================================
/**
 *	�Ȃ�������ʃi���o�[���擾
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�Ȃ�������ʃi���o�[���擾����ClientNo
 *
 * @retval	�Ȃ�������ʃi���o�[
 */
//============================================================================================
s32	ST_ServerNagetsukeruEqpGet(SERVER_PARAM *sp,int client_no)
{
	//�V���b�g�A�E�g�̋Z���ʔ������́A�A�C�e�����g���Ȃ�
	if(sp->psp[client_no].wkw.shutout_count){
		return 0;
	}

//	return ItemParamGet(sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_EFF,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_EFF);
}

//============================================================================================
/**
 *	�Ȃ�����З͂��擾
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�З͂��擾����ClientNo
 *
 * @retval	�Ȃ�����З�
 */
//============================================================================================
s32	ST_ServerNagetsukeruAtkGet(SERVER_PARAM *sp,int client_no)
{
	//�V���b�g�A�E�g�̋Z���ʔ������́A�A�C�e�����g���Ȃ�
	if(sp->psp[client_no].wkw.shutout_count){
		return 0;
	}

//	return ItemParamGet(sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_ATC,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_ATC);
}

//============================================================================================
/**
 *	�|�P��������ւ����\���`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e���p���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	����ւ��ł��Ȃ��Z���ʂ̋Z�i���o�[
 */
//============================================================================================
int		ST_ServerPokemonSelectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	wazano;

	wazano=0;

	//�������ʂł��Ȃ炸����ւ�����ʂ̏ꍇ�́A����ւ���
	if(ST_ServerSoubiEqpGet(sp,client_no)==SOUBI_KANARAZUIREKAWARERU){
		return 0;
	}

	//���߂���n�A���낢�܂Ȃ����A�˂��͂�́A����ւ��ł��Ȃ�
	if((sp->psp[client_no].condition2&(CONDITION2_SHIME|CONDITION2_KUROIMANAZASHI))||
	   (sp->psp[client_no].waza_kouka&WAZAKOUKA_NEWOHARU)){
		wazano=1;
	}

	//���肪���������ӂ݁A����傭�������Ă���Ƃ��́A����ւ��ł��Ȃ�
	if( ((ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_KAGEHUMI)&&
		 (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_KAGEHUMI)))||
	   (((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)==METAL_TYPE)||
		 (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)==METAL_TYPE))&&
		 (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_ZIRYOKU))) ){
		wazano=1;
	}
	//���肪�������肶�����������Ă���Ƃ��́A����ւ��ł��Ȃ�
	if((((ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_HUYUU)&&
	 	 (sp->psp[client_no].wkw.denzihuyuu_count==0)&&
		 (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)!=HIKOU_TYPE)&&
		 (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)!=HIKOU_TYPE))||
	     (sp->field_condition&FIELD_CONDITION_JUURYOKU))&&
		 (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_ARIZIGOKU))){
		wazano=1;
	}

	return wazano;
}

//============================================================================================
/**
 *	���΂ތ��ʂ̃`�F�b�N
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	FALSE:�Ȃɂ��Ȃ�	TRUE:���΂ތ��ʔ���
 */
//============================================================================================
BOOL	ST_ServerTsuibamuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	int		seq_no;
	int		eqp;
	int		atk;

	ret=FALSE;
	seq_no=0;

	eqp=ST_ServerTsuibamuEqpGet(sp,client_no);
	atk=ST_ServerSoubiAtkGet(sp,client_no,ATK_CHECK_NONE);

	//�݂���肩��́A���΂߂Ȃ�
	if(ST_ServerMigawariCheck(sp,sp->defence_client)==TRUE){
		return ret;
	}

	switch(eqp){
	case TUIBAMU_HPKAIHUKU:
		if(sp->psp[sp->attack_client].hp!=sp->psp[sp->attack_client].hpmax){
			sp->hp_calc_work=atk;
			seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
		}
		ret=TRUE;
		break;
	case TUIBAMU_HPKAIHUKUHIRITU:
		if(sp->psp[sp->attack_client].hp!=sp->psp[sp->attack_client].hpmax){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*atk,100);
			seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
		}
		ret=TRUE;
		break;
	case TUIBAMU_MAHINAOSI:
		if(sp->psp[sp->attack_client].condition&CONDITION_MAHI){
			seq_no=SUB_SEQ_EQPITEM_NO_MAHI;
		}
		ret=TRUE;
		break;
	case TUIBAMU_NEMUKEZAMASI:
		if(sp->psp[sp->attack_client].condition&CONDITION_NEMURI){
			seq_no=SUB_SEQ_EQPITEM_NO_NEMURI;
		}
		ret=TRUE;
		break;
	case TUIBAMU_DOKUKESI:
		if(sp->psp[sp->attack_client].condition&CONDITION_DOKUALL){
			seq_no=SUB_SEQ_EQPITEM_NO_DOKU;
		}
		ret=TRUE;
		break;
	case TUIBAMU_YAKEDONAOSI:
		if(sp->psp[sp->attack_client].condition&CONDITION_YAKEDO){
			seq_no=SUB_SEQ_EQPITEM_NO_YAKEDO;
		}
		ret=TRUE;
		break;
	case TUIBAMU_KOORINAOSI:
		if(sp->psp[sp->attack_client].condition&CONDITION_KOORI){
			seq_no=SUB_SEQ_EQPITEM_NO_KOORI;
		}
		ret=TRUE;
		break;
	case TUIBAMU_PPKAIHUKU:
		{
			int	pp_sub;
			int	pos;
			int	max;
			int	max_pos;

			max=0;

			for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
				if(sp->psp[sp->attack_client].waza[pos]){
					pp_sub=WT_PPMaxGet(sp->psp[sp->attack_client].waza[pos],sp->psp[sp->attack_client].pp_count[pos])-
						   sp->psp[sp->attack_client].pp[pos];
					if(pp_sub>max){
						max=pp_sub;
						max_pos=pos;
					}
				}
			}
			ST_PokemonServerParamAdd(&sp->psp[sp->attack_client],ID_PSP_pp1+max_pos,atk);
			ST_PSPtoPPCopy(bw,sp,sp->attack_client);
			sp->waza_work=sp->psp[sp->attack_client].waza[max_pos];
			seq_no=SUB_SEQ_EQPITEM_PP_KAIHUKU;
		}
		ret=TRUE;
		break;
	case TUIBAMU_KONRANNAOSI:
		if(sp->psp[sp->attack_client].condition2&CONDITION2_KONRAN){
			seq_no=SUB_SEQ_EQPITEM_NO_KONRAN;
		}
		ret=TRUE;
		break;
	case TUIBAMU_ZYOUTAIIZYOUNAOSI:
		if((sp->psp[sp->attack_client].condition&CONDITION_BAD)||
		   (sp->psp[sp->attack_client].condition2&CONDITION2_KONRAN)){
			if(sp->psp[sp->attack_client].condition&CONDITION_MAHI){
				seq_no=SUB_SEQ_EQPITEM_NO_MAHI;
			}
			if(sp->psp[sp->attack_client].condition&CONDITION_NEMURI){
				seq_no=SUB_SEQ_EQPITEM_NO_NEMURI;
			}
			if(sp->psp[sp->attack_client].condition&CONDITION_DOKUALL){
				seq_no=SUB_SEQ_EQPITEM_NO_DOKU;
			}
			if(sp->psp[sp->attack_client].condition&CONDITION_YAKEDO){
				seq_no=SUB_SEQ_EQPITEM_NO_YAKEDO;
			}
			if(sp->psp[sp->attack_client].condition&CONDITION_KOORI){
				seq_no=SUB_SEQ_EQPITEM_NO_KOORI;
			}
			if(sp->psp[sp->attack_client].condition2&CONDITION2_KONRAN){
				seq_no=SUB_SEQ_EQPITEM_NO_KONRAN;
			}
			if((sp->psp[sp->attack_client].condition&CONDITION_BAD)&&
			   (sp->psp[sp->attack_client].condition2&CONDITION2_KONRAN)){
				seq_no=SUB_SEQ_EQPITEM_NO_JOUTAIIJOU;
			}
		}
		ret=TRUE;
		break;
	case TUIBAMU_KARAIKONRAN:
		if(sp->psp[sp->attack_client].hp!=sp->psp[sp->attack_client].hpmax){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax,atk);
			sp->msg_work=TASTE_KARAI;
			if(PokeLikeTasteCheck(sp->psp[sp->attack_client].personal_rnd,TASTE_KARAI)==DISLIKE_TASTE){
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
		}
		ret=TRUE;
		break;
	case TUIBAMU_SIBUIKONRAN:
		if(sp->psp[sp->attack_client].hp!=sp->psp[sp->attack_client].hpmax){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax,atk);
			sp->msg_work=TASTE_SIBUI;
			if(PokeLikeTasteCheck(sp->psp[sp->attack_client].personal_rnd,TASTE_SIBUI)==DISLIKE_TASTE){
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
		}
		ret=TRUE;
		break;
	case TUIBAMU_AMAIKONRAN:
		if(sp->psp[sp->attack_client].hp!=sp->psp[sp->attack_client].hpmax){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax,atk);
			sp->msg_work=TASTE_AMAI;
			if(PokeLikeTasteCheck(sp->psp[sp->attack_client].personal_rnd,TASTE_AMAI)==DISLIKE_TASTE){
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
		}
		ret=TRUE;
		break;
	case TUIBAMU_NIGAIKONRAN:
		if(sp->psp[sp->attack_client].hp!=sp->psp[sp->attack_client].hpmax){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax,atk);
			sp->msg_work=TASTE_NIGAI;
			if(PokeLikeTasteCheck(sp->psp[sp->attack_client].personal_rnd,TASTE_NIGAI)==DISLIKE_TASTE){
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
		}
		ret=TRUE;
		break;
	case TUIBAMU_SUPPAIKONRAN:
		if(sp->psp[sp->attack_client].hp!=sp->psp[sp->attack_client].hpmax){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax,atk);
			sp->msg_work=TASTE_SUPPAI;
			if(PokeLikeTasteCheck(sp->psp[sp->attack_client].personal_rnd,TASTE_SUPPAI)==DISLIKE_TASTE){
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
		}
		ret=TRUE;
		break;
	case TUIBAMU_KOUGEKIUP:
		if(sp->psp[sp->attack_client].abiritycnt[COND_POW]<12){
			sp->msg_work=COND_POW;
			seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		ret=TRUE;
		break;
	case TUIBAMU_BOUGYOUP:
		if(sp->psp[sp->attack_client].abiritycnt[COND_DEF]<12){
			sp->msg_work=COND_DEF;
			seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		ret=TRUE;
		break;
	case TUIBAMU_SUBAYASAUP:
		if(sp->psp[sp->attack_client].abiritycnt[COND_AGI]<12){
			sp->msg_work=COND_AGI;
			seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		ret=TRUE;
		break;
	case TUIBAMU_TOKUKOUUP:
		if(sp->psp[sp->attack_client].abiritycnt[COND_SPEPOW]<12){
			sp->msg_work=COND_SPEPOW;
			seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		ret=TRUE;
		break;
	case TUIBAMU_TOKUBOUUP:
		if(sp->psp[sp->attack_client].abiritycnt[COND_SPEDEF]<12){
			sp->msg_work=COND_SPEDEF;
			seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		ret=TRUE;
		break;
	case TUIBAMU_NOURYOKURNDUP:
		{
			int	i;

			for(i=0;i<5;i++){
				if(sp->psp[sp->attack_client].abiritycnt[COND_POW+i]<12){
					break;
				}
			}
			if(i!=5){
				do{
					i=gf_rand()%5;
				}while(sp->psp[sp->attack_client].abiritycnt[COND_POW+i]==12);
				sp->msg_work=COND_POW+i;
				seq_no=SUB_SEQ_EQPITEM_CONDUP_MAX;
			}
		}
		ret=TRUE;
		break;
	case TUIBAMU_KURITHIKARUUP:
		if((sp->psp[sp->attack_client].condition2&CONDITION2_KIAIDAME)==0){
			seq_no=SUB_SEQ_EQPITEM_CRITICALUP;
		}
		ret=TRUE;
		break;
	case TUIBAMU_ITIDODAKEMEITYUUUP:
		seq_no=SUB_SEQ_EQPITEM_ONCE_HIT_UP;
		ret=TRUE;
		break;
	default:
		//�������Ă�����̂��؂̎��Ȃ�A���΂ނ��Ƃ����͔���
		if(ItemNutsCheck(sp->psp[client_no].item)==TRUE){
			ret=TRUE;
		}
		break;
	}

	if(ret==TRUE){
		//�����Ԃ��悤�A�Z���ʃV���b�g�A�E�g�́A�A�C�e���̌��ʂ𔭊��ł��Ȃ�
		if(((ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_BUKIYOU))||
			(sp->psp[sp->attack_client].waza_kouka&WAZAKOUKA_SHUTOUT)){
			sp->temp_work=0;
		}
		else{
			sp->temp_work=seq_no;
		}
		sp->item_work=sp->psp[client_no].item;
		sp->ostf[sp->attack_client].status_flag|=OSTF_STATUS_FLAG_TSUIBAMU;
	}

	return ret;
}

//============================================================================================
/**
 *	�Ȃ�������ʂ̃`�F�b�N
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	FALSE:�Ȃɂ��Ȃ�	TRUE:�Ȃ�������ʔ���
 */
//============================================================================================
BOOL	ST_ServerNagetsukeruCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	seq_no;
	int	eqp;
	int	atk;

	eqp=ST_ServerNagetsukeruEqpGet(sp,client_no);
	atk=ST_ServerSoubiAtkGet(sp,client_no,ATK_CHECK_SHUTOUT);
	sp->damage_power=ST_ServerNagetsukeruAtkGet(sp,client_no);
	sp->nagetsukeru_seq_no=0;
	sp->tsuika_type=0;

	//�З͂̂Ȃ��A�C�e���́A�����ł��Ȃ�
	if(sp->damage_power==0){
		return FALSE;
	}

	switch(eqp){
	case NAGETUKERU_HPKAIHUKU:
//		if(sp->psp[sp->defence_client].hp!=sp->psp[sp->defence_client].hpmax){
			sp->nagetsukeru_work=atk;
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
//		}
		break;
	case NAGETUKERU_HPKAIHUKUHIRITU:
//		if(sp->psp[sp->defence_client].hp!=sp->psp[sp->defence_client].hpmax){
			sp->nagetsukeru_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax*atk,100);
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
//		}
		break;
	case NAGETUKERU_MAHINAOSI:
		if(sp->psp[sp->defence_client].condition&CONDITION_MAHI){
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_MAHI;
		}
		break;
	case NAGETUKERU_NEMUKEZAMASI:
		if(sp->psp[sp->defence_client].condition&CONDITION_NEMURI){
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_NEMURI;
		}
		break;
	case NAGETUKERU_DOKUKESI:
		if(sp->psp[sp->defence_client].condition&CONDITION_DOKUALL){
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_DOKU;
		}
		break;
	case NAGETUKERU_YAKEDONAOSI:
		if(sp->psp[sp->defence_client].condition&CONDITION_YAKEDO){
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_YAKEDO;
		}
		break;
	case NAGETUKERU_KOORINAOSI:
		if(sp->psp[sp->defence_client].condition&CONDITION_KOORI){
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_KOORI;
		}
		break;
	case NAGETUKERU_PPKAIHUKU:
		{
			int	pp_sub;
			int	pos;
			int	max;
			int	max_pos;

			max=0;

			for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
				if(sp->psp[sp->defence_client].waza[pos]){
					pp_sub=WT_PPMaxGet(sp->psp[sp->defence_client].waza[pos],sp->psp[sp->defence_client].pp_count[pos])-
						   sp->psp[sp->defence_client].pp[pos];
					if(pp_sub>max){
						max=pp_sub;
						max_pos=pos;
					}
				}
			}
			if(max){
				ST_PokemonServerParamAdd(&sp->psp[sp->defence_client],ID_PSP_pp1+max_pos,atk);
				ST_PSPtoPPCopy(bw,sp,sp->defence_client);
				sp->waza_work=sp->psp[sp->defence_client].waza[max_pos];
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_PP_KAIHUKU;
			}
		}
		break;
	case NAGETUKERU_KONRANNAOSI:
		if(sp->psp[sp->defence_client].condition2&CONDITION2_KONRAN){
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_KONRAN;
		}
		break;
	case NAGETUKERU_ZYOUTAIIZYOUNAOSI:
		if((sp->psp[sp->defence_client].condition&CONDITION_BAD)||
		   (sp->psp[sp->defence_client].condition2&CONDITION2_KONRAN)){
			if(sp->psp[sp->defence_client].condition&CONDITION_MAHI){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_MAHI;
			}
			if(sp->psp[sp->defence_client].condition&CONDITION_NEMURI){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_NEMURI;
			}
			if(sp->psp[sp->defence_client].condition&CONDITION_DOKUALL){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_DOKU;
			}
			if(sp->psp[sp->defence_client].condition&CONDITION_YAKEDO){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_YAKEDO;
			}
			if(sp->psp[sp->defence_client].condition&CONDITION_KOORI){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_KOORI;
			}
			if(sp->psp[sp->defence_client].condition2&CONDITION2_KONRAN){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_KONRAN;
			}
			if((sp->psp[sp->defence_client].condition&CONDITION_BAD)&&
			   (sp->psp[sp->defence_client].condition2&CONDITION2_KONRAN)){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_JOUTAIIJOU;
			}
		}
		break;
	case NAGETUKERU_KARAIKONRAN:
//		if(sp->psp[sp->defence_client].hp!=sp->psp[sp->defence_client].hpmax){
			sp->nagetsukeru_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax,atk);
			sp->msg_work=TASTE_KARAI;
			if(PokeLikeTasteCheck(sp->psp[sp->defence_client].personal_rnd,TASTE_KARAI)==DISLIKE_TASTE){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
//		}
		break;
	case NAGETUKERU_SIBUIKONRAN:
//		if(sp->psp[sp->defence_client].hp!=sp->psp[sp->defence_client].hpmax){
			sp->nagetsukeru_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax,atk);
			sp->msg_work=TASTE_SIBUI;
			if(PokeLikeTasteCheck(sp->psp[sp->defence_client].personal_rnd,TASTE_SIBUI)==DISLIKE_TASTE){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
//		}
		break;
	case NAGETUKERU_AMAIKONRAN:
//		if(sp->psp[sp->defence_client].hp!=sp->psp[sp->defence_client].hpmax){
			sp->nagetsukeru_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax,atk);
			sp->msg_work=TASTE_AMAI;
			if(PokeLikeTasteCheck(sp->psp[sp->defence_client].personal_rnd,TASTE_AMAI)==DISLIKE_TASTE){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
//		}
		break;
	case NAGETUKERU_NIGAIKONRAN:
//		if(sp->psp[sp->defence_client].hp!=sp->psp[sp->defence_client].hpmax){
			sp->nagetsukeru_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax,atk);
			sp->msg_work=TASTE_NIGAI;
			if(PokeLikeTasteCheck(sp->psp[sp->defence_client].personal_rnd,TASTE_NIGAI)==DISLIKE_TASTE){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
//		}
		break;
	case NAGETUKERU_SUPPAIKONRAN:
//		if(sp->psp[sp->defence_client].hp!=sp->psp[sp->defence_client].hpmax){
			sp->nagetsukeru_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax,atk);
			sp->msg_work=TASTE_SUPPAI;
			if(PokeLikeTasteCheck(sp->psp[sp->defence_client].personal_rnd,TASTE_SUPPAI)==DISLIKE_TASTE){
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU_KONRAN;
			}
			else{
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_HP_KAIHUKU;
			}
//		}
		break;
	case NAGETUKERU_NOURYOKUKAIHUKU:
		{
			int	i;

			for(i=0;i<COND_MAX;i++){
				if(sp->psp[sp->defence_client].abiritycnt[i]<6){
					sp->psp[sp->defence_client].abiritycnt[i]=6;
					sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_ABIRITY_KAIHUKU;
				}
			}
		}
		break;
	case NAGETUKERU_MEROMERONAOSI:
		if(sp->psp[sp->defence_client].condition2&CONDITION2_MEROMERO){
			sp->msg_work=MSG_COND_MEROMERO;
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_NO_MEROMERO;
		}
		break;
	case NAGETUKERU_HIRUMASERU:
		sp->tsuika_client=client_no;
		sp->tsuika_type=ADD_STATUS_INDIRECT;
		sp->nagetsukeru_seq_no=SUB_SEQ_HIRUMU;
		break;
	case NAGETUKERU_MAHINISURU:
		sp->tsuika_client=client_no;
		sp->tsuika_type=ADD_STATUS_INDIRECT;
		sp->nagetsukeru_seq_no=SUB_SEQ_MAHI;
		break;
	case NAGETUKERU_DOKUNISURU:
		sp->tsuika_client=client_no;
		sp->tsuika_type=ADD_STATUS_INDIRECT;
		sp->nagetsukeru_seq_no=SUB_SEQ_DOKU;
		break;
	case NAGETUKERU_MOUDOKUNISURU:
		sp->tsuika_client=client_no;
		sp->tsuika_type=ADD_STATUS_INDIRECT;
		sp->nagetsukeru_seq_no=SUB_SEQ_DOKUDOKU;
		break;
	case NAGETUKERU_YAKEDONISURU:
		sp->tsuika_client=client_no;
		sp->tsuika_type=ADD_STATUS_INDIRECT;
		sp->nagetsukeru_seq_no=SUB_SEQ_YAKEDO;
		break;
	case NAGETUKERU_KOUGEKIUP:
		if(sp->psp[sp->defence_client].abiritycnt[COND_POW]<12){
			sp->msg_work=COND_POW;
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		break;
	case NAGETUKERU_BOUGYOUP:
		if(sp->psp[sp->defence_client].abiritycnt[COND_DEF]<12){
			sp->msg_work=COND_DEF;
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		break;
	case NAGETUKERU_SUBAYASAUP:
		if(sp->psp[sp->defence_client].abiritycnt[COND_AGI]<12){
			sp->msg_work=COND_AGI;
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		break;
	case NAGETUKERU_TOKUKOUUP:
		if(sp->psp[sp->defence_client].abiritycnt[COND_SPEPOW]<12){
			sp->msg_work=COND_SPEPOW;
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		break;
	case NAGETUKERU_TOKUBOUUP:
		if(sp->psp[sp->defence_client].abiritycnt[COND_SPEDEF]<12){
			sp->msg_work=COND_SPEDEF;
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_CONDUP;
		}
		break;
	case NAGETUKERU_NOURYOKURNDUP:
		{
			int	i;

			for(i=0;i<5;i++){
				if(sp->psp[sp->defence_client].abiritycnt[COND_POW+i]<12){
					break;
				}
			}
			if(i!=5){
				do{
					i=gf_rand()%5;
				}while(sp->psp[sp->defence_client].abiritycnt[COND_POW+i]==12);
				sp->msg_work=COND_POW+i;
				sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_CONDUP_MAX;
			}
		}
		break;
	case NAGETUKERU_KURITHIKARUUP:
		if((sp->psp[sp->defence_client].condition2&CONDITION2_KIAIDAME)==0){
			sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_CRITICALUP;
		}
		break;
	case NAGETUKERU_ITIDODAKEMEITYUUUP:
		sp->nagetsukeru_seq_no=SUB_SEQ_EQPITEM_ONCE_HIT_UP;
		break;
	default:
		break;
	}

	//�������������Ă��鎞�́A�������ʂ̔����Ȃ�
	if(sp->psp[sp->defence_client].waza_kouka&WAZAKOUKA_SHUTOUT){
		sp->nagetsukeru_seq_no=0;
	}
	else{
		sp->item_work=sp->psp[client_no].item;
		if((sp->tsuika_type==0)&&(sp->nagetsukeru_seq_no)){
			sp->ostf[sp->attack_client].status_flag|=OSTF_STATUS_FLAG_TSUIBAMU;
		}
		sp->client_work=sp->defence_client;
	}

	return TRUE;
}

//============================================================================================
/**
 *	���g���m�[���`�F�b�N�i�Z���o���O�`�F�b�N�j
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerMetronomeBeforeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//�����Z���o��������ƈЗ̓A�b�v�̃`�F�b�N�i�p���Z�n�͏��O�j
	if(ST_ServerSoubiEqpGet(sp,sp->attack_client)==SOUBI_ONAZIWAZANOIRYOKUUP){
		if(((sp->psp[sp->attack_client].condition2&CONDITION2_ABARERU)==0)&&
		   ((sp->psp[sp->attack_client].condition2&CONDITION2_SAWAGU)==0)&&
		   ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER)==0)&&
		   ((sp->psp[sp->attack_client].condition2&CONDITION2_KEEP)==0)){
			if(sp->waza_no_metronome[sp->attack_client]==sp->waza_no_temp){
				if(sp->psp[sp->attack_client].wkw.metronome_work<10){
					sp->psp[sp->attack_client].wkw.metronome_work++;
				}
			}
			else{
				sp->psp[sp->attack_client].wkw.metronome_work=0;
				sp->waza_no_metronome[sp->attack_client]=sp->waza_no_temp;
			}
		}
	}
	else{
		sp->psp[sp->attack_client].wkw.metronome_work=0;
	}
	OS_Printf("no:%d metro_count:%d\n",sp->attack_client,sp->psp[sp->attack_client].wkw.metronome_work);
}

//============================================================================================
/**
 *	���g���m�[���`�F�b�N�i�Z���o������`�F�b�N�j
 *
 *	@param[in]	bw			�퓬�V�X�e���p���[�N�\����
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	ST_ServerMetronomeAfterCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//�����Z���o��������ƈЗ̓A�b�v�̃`�F�b�N�i�p���Z�n�͏��O�j
	if(ST_ServerSoubiEqpGet(sp,sp->attack_client)==SOUBI_ONAZIWAZANOIRYOKUUP){
		if((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)&&
		   (sp->waza_no_metronome[sp->attack_client]==sp->waza_no_temp)&&
		   (sp->psp[sp->attack_client].wkw.metronome_work)&&
		   (sp->ostf[sp->attack_client].korogaru_count==0)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_ABARERU)==0)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_SAWAGU)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER)==0)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_KEEP)==0)){
			sp->psp[sp->attack_client].wkw.metronome_work--;
		}
	}
	else{
		sp->psp[sp->attack_client].wkw.metronome_work=0;
	}
}

//============================================================================================
/**
 *	�|�P�����̂��C���`�F�b�N���āA�����p�^�[�����擾
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *	@param[in]	client_no	�`�F�b�N����ClientType
 *	@param[in]	encount		TRUE:�G���J�E���g�o�ꎞ
 */
//============================================================================================
int		ST_ServerPokeVoiceEffNoGet(SERVER_PARAM *sp,int client_no, int client_type, int encount)
{
	int	ptn;
	int	col;
	int half;
	
	if(encount == TRUE && (client_type == CLIENT_TYPE_A || client_type == CLIENT_TYPE_B)){
		half = TRUE;
	}
	else{
		half = FALSE;
	}

	ptn=PV_NORMAL;
	if(half == TRUE){
		ptn = PV_NORMAL;//PV_HALF;
	}
	
	col=GetHPGaugeDottoColor(sp->psp[client_no].hp,sp->psp[client_no].hpmax,GAUGE_HP_DOTTOMAX);
	
	if((sp->psp[client_no].condition&CONDITION_BAD)||
	   ((col!=HP_DOTTO_MAX)&&(col!=HP_DOTTO_GREEN))){
		
		if(half == TRUE){
			ptn = PV_PINCHNORMAL;//PV_PINCHHALF;
		}
		else{
			ptn=PV_PINCHNORMAL;
		}
	}

	return ptn;
}

//============================================================================================
/**
 *	�R�}���h�I��������������ׂ�
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����ClientNo
 *
 *	@retval	FALSE:�R�}���h�I���Ȃ��@TRUE:�R�}���h�I������
 */
//============================================================================================
BOOL	ST_ServerCommandSelectCheck(SERVER_PARAM *sp,int client_no)
{
	BOOL	ret=TRUE;

	///<�����̎��́A�R�}���h�I���Ȃ�
	if((sp->psp[client_no].condition2&CONDITION2_HANDOU)||
	///<���΂�Ă���Œ��́A�R�}���h�I���Ȃ�
	   (sp->psp[client_no].condition2&CONDITION2_ABARERU)||
	///<���킢�ł���Œ��́A�R�}���h�I���Ȃ�
	   (sp->psp[client_no].condition2&CONDITION2_SAWAGU)||
	///<���ߌn�̋Z�̎��́A�R�}���h�I���Ȃ�
	   (sp->psp[client_no].condition2&CONDITION2_KEEP)){
		ret=FALSE;
	}

	return ret;
}

//============================================================================================
/**
 *	�|�P�����ߊl���̃Z�b�g
 *
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	pp	�Z�b�g����POKEMON_PARAM�\����
 */
//============================================================================================
void	ST_ServerPokemonGetParamSet(BATTLE_WORK *bw,SERVER_PARAM *sp,POKEMON_PARAM *pp)
{
	MYSTATUS	*status;
	int			place;
	int			ground_id;
	int			ballID;

	//MYSTATUS���擾
	status=BattleWorkMyStatusGet(bw,CLIENT_NO_MINE);

	//�n�於ID���擾
	place=BattleWorkPlaceIDGet(bw);

	//�n�`�A�g���r���[�g���擾
	ground_id=BattleWorkGroundIDGet(bw);

	//�|�P�p�[�N�ł́A�ߊl�{�[����ύX���Ȃ�
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_POKE_PARK){
		ballID=PokeParaGet(pp,ID_PARA_get_ball,NULL);
	}
	else{
		ballID=sp->item_work;
	}

	PokeParaGetInfoSet(pp,status,ballID,place,ground_id,HEAPID_BATTLE);
}

//============================================================================================
/**
 *	�N���C�A���g����̕ԓ������o��
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	���o���N���C�A���g�i���o�[
 */
//============================================================================================
u8	ST_ServerBufferResGet(SERVER_PARAM *sp,int client_no)
{
	return sp->server_buffer[client_no][0];
}

//============================================================================================
/**
 *	�݂����łӂ����邩�`�F�b�N
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	client_no	�`�F�b�N����N���C�A���g�i���o�[
 *
 *�@@retval FALSE:�h���Ȃ��@TRUE:�h��
 */
//============================================================================================
BOOL	ST_ServerMigawariCheck(SERVER_PARAM *sp,int client_no)
{
	BOOL	ret=FALSE;

//	if((sp->ostf[client_no].status_flag&OSTF_STATUS_FLAG_MIGAWARI_HIT)||
//	   (sp->psp[client_no].condition2&CONDITION2_MIGAWARI)){
//		ret=TRUE;
//	}
	if(sp->ostf[client_no].status_flag&OSTF_STATUS_FLAG_MIGAWARI_HIT){
		ret=TRUE;
	}

	return ret;
}

//============================================================================================
/**
 *	�����̃|�P�������`�F�b�N
 *
 *	@param[in]	bw	�퓬�V�X�e�����[�N�\���̂̃|�C���^
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 *
 *�@@retval FALSE:���l�̃|�P�����@TRUE:�����̃|�P����
 */
//============================================================================================
BOOL	ST_ServerPokeOneSelfCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	MYSTATUS		*status;
	u32				id;
	u32				sex;
	const STRCODE	*name;

	status=BattleWorkMyStatusGet(bw,CLIENT_NO_MINE);
	id=MyStatus_GetID(status);
	sex=MyStatus_GetMySex(status);
	name=MyStatus_GetMyName(status);

	if((id==sp->psp[sp->attack_client].id_no)&&
	   (sex==sp->psp[sp->attack_client].oyasex)&&
	   (PM_strncmp(name,&sp->psp[sp->attack_client].oyaname[0],PERSON_NAME_SIZE)==0)){
		return TRUE;
	}

	return FALSE;
}

//============================================================================================
/**
 *	�����̃|�P�������`�F�b�N
 *
 *	@param[in]	bw	�퓬�V�X�e�����[�N�\���̂̃|�C���^
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 *
 *�@@retval FALSE:���l�̃|�P�����@TRUE:�����̃|�P����
 */
//============================================================================================
BOOL	ST_ServerPokeOneSelfCheckActPP(BATTLE_WORK *bw,POKEMON_PARAM *pp)
{
	MYSTATUS		*status;
	u32				id;
	u32				sex;
	const STRCODE	*name;
	STRCODE			oyaname[PERSON_NAME_SIZE+EOM_SIZE];

	status=BattleWorkMyStatusGet(bw,CLIENT_NO_MINE);
	id=MyStatus_GetID(status);
	sex=MyStatus_GetMySex(status);
	name=MyStatus_GetMyName(status);
	PokeParaGet(pp,ID_PARA_oyaname,&oyaname[0]);

	if((id==PokeParaGet(pp,ID_PARA_id_no,NULL))&&
	   (sex==PokeParaGet(pp,ID_PARA_oyasex,NULL))&&
	   (PM_strncmp(name,&oyaname[0],PERSON_NAME_SIZE)==0)){
		return TRUE;
	}

	return FALSE;
}

//============================================================================================
/**
 *	�����Ă񂫂�`�F�b�N�i�|�P�������F�`�F���V�������l�̓���������̂ł��킹�ă`�F�b�N�j
 *
 *	@param[in]	bw	�퓬�V�X�e�����[�N�\���̂̃|�C���^
 *	@param[in]	sp	�T�[�o�p�����[�^�\���̂̃|�C���^
 *
 *�@@retval FALSE:�Ă񂫂�Ȃ��@TRUE:�Ă񂫂┭��
 */
//============================================================================================
BOOL	ST_ServerTenkiyaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int		i;
	int		form_no;
	BOOL	ret=FALSE;

	for(i=0;i<BattleWorkClientSetMaxGet(bw);i++){
		sp->client_work=sp->psp_agi_work[i];
		if((sp->psp[sp->client_work].monsno==MONSNO_POWARUN)&&
		   (sp->psp[sp->client_work].hp)&&
		   (ST_ServerTokuseiGet(sp,sp->client_work)==TOKUSYU_TENKIYA)){
			if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
			   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
				if(((sp->field_condition&FIELD_CONDITION_TENKI_CHG)==0)&&
					(sp->psp[sp->client_work].type1!=NORMAL_TYPE)&&
					(sp->psp[sp->client_work].type2!=NORMAL_TYPE)){
					sp->psp[sp->client_work].type1=NORMAL_TYPE;
					sp->psp[sp->client_work].type2=NORMAL_TYPE;
					sp->psp[sp->client_work].form_no=FORMNO_POWARUN_NORMAL;
					ret=TRUE;
					break;
				}
				else if((sp->field_condition&FIELD_CONDITION_HARE_ALL)&&
						(sp->psp[sp->client_work].type1!=FIRE_TYPE)&&
						(sp->psp[sp->client_work].type2!=FIRE_TYPE)){
					sp->psp[sp->client_work].type1=FIRE_TYPE;
					sp->psp[sp->client_work].type2=FIRE_TYPE;
					sp->psp[sp->client_work].form_no=FORMNO_POWARUN_SUN;
					ret=TRUE;
					break;
				}
				else if((sp->field_condition&FIELD_CONDITION_AME_ALL)&&
						(sp->psp[sp->client_work].type1!=WATER_TYPE)&&
						(sp->psp[sp->client_work].type2!=WATER_TYPE)){
					sp->psp[sp->client_work].type1=WATER_TYPE;
					sp->psp[sp->client_work].type2=WATER_TYPE;
					sp->psp[sp->client_work].form_no=FORMNO_POWARUN_RAIN;
					ret=TRUE;
					break;
				}
				else if((sp->field_condition&FIELD_CONDITION_ARARE_ALL)&&
						(sp->psp[sp->client_work].type1!=KOORI_TYPE)&&
						(sp->psp[sp->client_work].type2!=KOORI_TYPE)){
					sp->psp[sp->client_work].type1=KOORI_TYPE;
					sp->psp[sp->client_work].type2=KOORI_TYPE;
					sp->psp[sp->client_work].form_no=FORMNO_POWARUN_SNOW;
					ret=TRUE;
					break;
				}
			}
			else{
				if((sp->psp[sp->client_work].type1!=NORMAL_TYPE)&&
				   (sp->psp[sp->client_work].type2!=NORMAL_TYPE)){
					sp->psp[sp->client_work].type1=NORMAL_TYPE;
					sp->psp[sp->client_work].type2=NORMAL_TYPE;
					sp->psp[sp->client_work].form_no=FORMNO_POWARUN_NORMAL;
					ret=TRUE;
					break;
				}
			}
		}
		if((sp->psp[sp->client_work].monsno==MONSNO_THERISYU)&&
		   (sp->psp[sp->client_work].hp)){
			if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
			   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
				if(((sp->field_condition&FIELD_CONDITION_TENKI_CHG)==0)&&
					(sp->psp[sp->client_work].form_no==FORMNO_THERISYU_SUN)){
					sp->psp[sp->client_work].form_no=FORMNO_THERISYU_NORMAL;
					ret=TRUE;
					break;
				}
				else if((sp->field_condition&FIELD_CONDITION_HARE_ALL)&&
						(sp->psp[sp->client_work].form_no==FORMNO_THERISYU_NORMAL)){
					sp->psp[sp->client_work].form_no=FORMNO_THERISYU_SUN;
					ret=TRUE;
					break;
				}
				else if((sp->field_condition&FIELD_CONDITION_AME_ALL)&&
						(sp->psp[sp->client_work].form_no==FORMNO_THERISYU_SUN)){
					sp->psp[sp->client_work].form_no=FORMNO_THERISYU_NORMAL;
					ret=TRUE;
					break;
				}
				else if((sp->field_condition&FIELD_CONDITION_ARARE_ALL)&&
						(sp->psp[sp->client_work].form_no==FORMNO_THERISYU_SUN)){
					sp->psp[sp->client_work].form_no=FORMNO_THERISYU_NORMAL;
					ret=TRUE;
					break;
				}
			}
			else{
				if(sp->psp[sp->client_work].form_no==FORMNO_THERISYU_SUN){
					sp->psp[sp->client_work].form_no=FORMNO_THERISYU_NORMAL;
					ret=TRUE;
					break;
				}
			}
		}
		if((sp->psp[sp->client_work].monsno==MONSNO_AUSU)&&
		   (sp->psp[sp->client_work].hp)){
			form_no=AusuTypeGet(ItemParamGet(sp->psp[sp->client_work].item,ITEM_PRM_EQUIP,HEAPID_BATTLE));
			if(sp->psp[sp->client_work].form_no!=form_no){
				sp->psp[sp->client_work].form_no=form_no;
				ret=TRUE;
				break;
			}
		}
	}

	return ret;
}

//============================================================================================
/**
 *	ListRow�̏�����������
 *
 * @param[in]	bw			�퓬�p�����[�^�̍\���̃|�C���^
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 *
 */
//============================================================================================
void	ST_ServerListRowInit(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	pos;

	for(client_no=0;client_no<BattleWorkClientSetMaxGet(bw);client_no++){
		for(pos=0;pos<POKEMON_TEMOTI_MAX;pos++){
			sp->list_row[client_no][pos]=pos;
		}
		ST_ServerListRowChange(bw,sp,client_no,sp->sel_mons_no[client_no]);
	}
}

//============================================================================================
/**
 *	ListRow�̓���ւ�������
 *
 * @param[in]	bw			�퓬�p�����[�^�̍\���̃|�C���^
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	����ւ��Ώ�ClientNo
 * @param[in]	sel_mons_no	����ւ��Ώۃ|�P�����ʒu
 *
 */
//============================================================================================
void	ST_ServerListRowChange(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no)
{
	int	pos;
	int	work;
	int	fb_flag;
	u32	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	if(((fight_type&FIGHT_TYPE_2vs2)&&((fight_type&(FIGHT_TYPE_MULTI|FIGHT_TYPE_TAG))==0))||
	   ((fight_type&FIGHT_TYPE_TAG)&&((BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG)==0))){
		if((BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_C)||
		   (BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_D)){
			fb_flag=FB_BACKWARD;
		}
		else{
			fb_flag=FB_FORWARD;
		}
		client_no&=1;
	}
	else{
		fb_flag=FB_FORWARD;
	}
	
	for(pos=0;pos<POKEMON_TEMOTI_MAX;pos++){
		if(sp->list_row[client_no][pos]==sel_mons_no){
			break;
		}
	}

	//�擪�Ƃ��ꂩ����
	work=sp->list_row[client_no][fb_flag];
	sp->list_row[client_no][fb_flag]=sp->list_row[client_no][pos];
	sp->list_row[client_no][pos]=work;
}

//============================================================================================
/**
 * �\���̒�`
 */
//============================================================================================

typedef struct{
	u16	monsno;
	s16 hp;

	u16	hpmax;
	u16	dummy;

	int	eqp;
	int	atc;

	u32 condition;

	u8	speabino;
	u8	sex;
	u8	type1;
	u8	type2;
}WAZA_DAMAGE_CALC_PARAM;

//============================================================================================
/**
 *	�������ʂɂ��Z�^�C�v�U���̓A�b�v�e�[�u��
 */
//============================================================================================
static	const u8 SoubiItemWazaTypePowUpTbl[][2]={
	{SOUBI_MUSIIRYOKUUP,		MUSHI_TYPE},
	{SOUBI_HAGANEIRYOKUUP,		METAL_TYPE},
	{SOUBI_ZIMENUP,				JIMEN_TYPE},
	{SOUBI_IWAUP,				IWA_TYPE},
	{SOUBI_KUSAUP,				KUSA_TYPE},
	{SOUBI_AKUUP,				AKU_TYPE},
	{SOUBI_KAKUTOUUP,			BATTLE_TYPE},
	{SOUBI_DENKIUP,				ELECTRIC_TYPE},
	{SOUBI_MIZUUP,				WATER_TYPE},
	{SOUBI_TORIUP,				HIKOU_TYPE},
	{SOUBI_DOKUBARIUP,			POISON_TYPE},
	{SOUBI_KOORIUP,				KOORI_TYPE},
	{SOUBI_GOOSUTOUP,			GHOST_TYPE},
	{SOUBI_ESUPAAUP,			SP_TYPE},
	{SOUBI_HONOOUP,				FIRE_TYPE},
	{SOUBI_DORAGONUP,			DRAGON_TYPE},
	{SOUBI_NOOMARUUP,			NORMAL_TYPE},
	{SOUBI_AUSUHONOOUP,			FIRE_TYPE},
	{SOUBI_AUSUMIZUUP,			WATER_TYPE},
	{SOUBI_AUSUDENKIUP,			ELECTRIC_TYPE},
	{SOUBI_AUSUKUSAUP,			KUSA_TYPE},
	{SOUBI_AUSUKOORIUP,			KOORI_TYPE},
	{SOUBI_AUSUKAKUTOUUP,		BATTLE_TYPE},
	{SOUBI_AUSUDOKUBARIUP,		POISON_TYPE},
	{SOUBI_AUSUZIMENUP,			JIMEN_TYPE},
	{SOUBI_AUSUTORIUP,			HIKOU_TYPE},
	{SOUBI_AUSUESUPAAUP,		SP_TYPE},
	{SOUBI_AUSUMUSIIRYOKUUP,	MUSHI_TYPE},
	{SOUBI_AUSUIWAUP,			IWA_TYPE},
	{SOUBI_AUSUGOOSUTOUP,		GHOST_TYPE},
	{SOUBI_AUSUDORAGONUP,		DRAGON_TYPE},
	{SOUBI_AUSUAKUUP,			AKU_TYPE},
	{SOUBI_AUSUHAGANEIRYOKUUP,	METAL_TYPE},
};

//============================================================================================
/**
 *	abiritycnt�ɂ��p�����[�^�����e�[�u��
 */
//============================================================================================
const	u8	CondChgTable[][2]={
		{10,40},
		{10,35},
		{10,30},
		{10,25},
		{10,20},
		{10,15},
		{10,10},
		{15,10},
		{20,10},
		{25,10},
		{30,10},
		{35,10},
		{40,10},
};

//============================================================================================
/**
 *	�����Ă̂��Ԃ��p�e�[�u��
 */
//============================================================================================
static	const	u16	TetsunoKobushiTable[]={
	WAZANO_REITOUPANTI,		//�ꂢ�Ƃ��p���`
	WAZANO_HONOONOPANTI,	//�ق̂��̃p���`
	WAZANO_KAMINARIPANTI,	//���݂Ȃ�p���`
	WAZANO_MAHHAPANTI,		//�}�b�n�p���`
	WAZANO_KIAIPANTI,		//�������p���`
	WAZANO_PIYOPIYOPANTI,	//�s���s���p���`
	WAZANO_BAKURETUPANTI,	//�΂���p���`
	WAZANO_AAMUHANMAA,		//�A�[���n���}�[
	WAZANO_MEGATONPANTI,	//���K�g���p���`
	WAZANO_RENZOKUPANTI,	//��񂼂��p���`
	WAZANO_KOMETTOPANTI,	//�R���b�g�p���`
	WAZANO_SYADOOPANTI,		//�V���h�[�p���`
	WAZANO_DOREINPANTI,		//�h���C���p���`
	WAZANO_BARETTOPANTI,	//�o���b�g�p���`
	WAZANO_SUKAIAPPAA,		//�X�J�C�A�b�p�[
};

//============================================================================================
/**
 *	�Z�̃_���[�W�v�Z������B
 *
 * @param[in]	pspa		�Z���o�����|�P�����̍\���̂̃|�C���^
 * @param[in]	pspd		�Z���󂯂�|�P�����̍\���̂̃|�C���^
 * @param[in]	wazano		�v�Z����Z�i���o�[
 * @param[in]	side_cond	��ɂ������Ă������
 * @param[in]	pow			�Z�̈З�(0:�e�[�u�����Q�Ɓ@0�ȊO:���̒l���Q��)
 * @param[in]	type		�Z�̃^�C�v(0:�e�[�u�����Q�Ɓ@0�ȊO:���̒l���Q��)
 * @param[in]	attack		�U�����̃N���C�A���g�i���o�[
 * @param[in]	defence		�h�䑤�̃N���C�A���g�i���o�[
 * @param[in]	critical	�}���ɓ����������ǂ���(1:�ʏ�@2�ȏ�:�N���e�B�J���j
 *
 *	@retval	�v�Z���ʂ̃_���[�W��
 */
//============================================================================================
int	ST_WazaDamageCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,
					  int wazano,u32 side_cond,u32 field_cond,u16 pow,u8 type,u8 attack,u8 defence,u8 critical)
{

	int	i;
	s32	damage=0;
	s32	damage2=0;
	u8	wazatype;
	u8	wazakind;
	u16	pokepow;
	u16	pokedef;
	u16	pokespepow;
	u16	pokespedef;
	s8	condpow;
	s8	conddef;
	s8	condspepow;
	s8	condspedef;
	u8	level;
	u16	wazapow;
	u16	item;
	u32	fight_type;
	WAZA_DAMAGE_CALC_PARAM	wdcp_a;
	WAZA_DAMAGE_CALC_PARAM	wdcp_d;

	GF_ASSERT(((critical==1)||(critical>1))&&"WT_WazaDamageCalc:critical != 1 or 2\n");

	pokepow=			ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_pow,				NULL);
	pokedef=			ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_def,				NULL);
	pokespepow=			ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_spepow,				NULL);
	pokespedef=			ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_spedef,			NULL);
	condpow=			ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_abiritycnt_pow,		NULL)-6;
	conddef=			ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_abiritycnt_def,	NULL)-6;
	condspepow=			ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_abiritycnt_spepow,	NULL)-6;
	condspedef=			ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_abiritycnt_spedef,	NULL)-6;
	level=				ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_level,				NULL);
	wdcp_a.monsno=		ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_monsno,				NULL);
	wdcp_d.monsno=		ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_monsno,			NULL);
	wdcp_a.hp=			ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_hp,					NULL);
	wdcp_d.hp=			ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_hp,				NULL);
	wdcp_a.hpmax=		ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_hpmax,				NULL);
	wdcp_d.hpmax=		ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_hpmax,				NULL);
	wdcp_a.condition=	ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_condition,			NULL);
	wdcp_d.condition=	ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_condition,			NULL);
	wdcp_a.speabino=	ST_ServerTokuseiGet(sp,attack);
	wdcp_d.speabino=	ST_ServerTokuseiGet(sp,defence);
	wdcp_a.sex=			ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_sex,				NULL);
	wdcp_d.sex=			ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_sex,				NULL);
	wdcp_a.type1=		ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_type1,				NULL);
	wdcp_d.type1=		ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_type1,				NULL);
	wdcp_a.type2=		ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_type2,				NULL);
	wdcp_d.type2=		ST_ServerPokemonServerParamGet(sp,defence,ID_PSP_type2,				NULL);

	item=ST_ServerSoubiItemNoGet(sp,attack);
//	wdcp_a.eqp=ItemParamGet(item,ITEM_PRM_EQUIP,HEAPID_BATTLE);
//	wdcp_a.atc=ItemParamGet(item,ITEM_PRM_ATTACK,HEAPID_BATTLE);
	wdcp_a.eqp=ST_ItemParamGet(sp,item,ITEM_PRM_EQUIP);
	wdcp_a.atc=ST_ItemParamGet(sp,item,ITEM_PRM_ATTACK);
	item=ST_ServerSoubiItemNoGet(sp,defence);
//	wdcp_d.eqp=ItemParamGet(item,ITEM_PRM_EQUIP,HEAPID_BATTLE);
//	wdcp_d.atc=ItemParamGet(item,ITEM_PRM_ATTACK,HEAPID_BATTLE);
	wdcp_d.eqp=ST_ItemParamGet(sp,item,ITEM_PRM_EQUIP);
	wdcp_d.atc=ST_ItemParamGet(sp,item,ITEM_PRM_ATTACK);

	fight_type=BattleWorkFightTypeGet(bw);

	if(pow==0){
		wazapow=sp->AIWT.wtd[wazano].damage;
	}
	else{
		wazapow=pow;
	}

	//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
	if(wdcp_a.speabino==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(type==0){
		wazatype=sp->AIWT.wtd[wazano].wazatype;
	}
	else{
		wazatype=type&0x3f;
	}

	GF_ASSERT_MSG(sp->damage_value>=10,"damage_value Under 10!\n");
	wazapow=wazapow*sp->damage_value/10;	//�Z�ɂ��_���[�W�{�����[�N�ɂ��З̓A�b�v�v�Z

	//���イ�ł񒆂͗������̓_���[�W2�{
	if((sp->psp[attack].waza_kouka&WAZAKOUKA_JUUDEN)&&
	   (wazatype==ELECTRIC_TYPE)){	
		wazapow*=2;
	}

	//�Ă��������̓_���[�W1.5�{
	if(sp->otf[attack].tedasuke_flag){	
		wazapow=wazapow*15/10;
	}

	//�����e�N�j�V�����́A�З�50�ȉ��̋Z��1.5�{�ɂ���i��邠�����́A���O�j
	if((wdcp_a.speabino==TOKUSYU_TEKUNISYAN)&&
	   (wazano!=WAZANO_WARUAGAKI)&&
	   (wazapow<=60)){
		wazapow=wazapow*15/10;
	}

	wazakind=sp->AIWT.wtd[wazano].kind;

	//��������������́A���K�p���[�́A�U���͂�{
	if((wdcp_a.speabino==TOKUSYU_TIKARAMOTI)||(wdcp_a.speabino==TOKUSYU_YOGAPAWAA)){
		pokepow=pokepow*2;
	}

	//�����X���[�X�^�[�g�́A��ɂłĂ���5�^�[���ȓ��́A�U���͂𔼕��ɂ���
	if((wdcp_a.speabino==TOKUSYU_SUROOSUTAATO)&&
	  ((ST_ServerParamDataGet(bw,sp,ID_SP_total_turn,NULL)-
		ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_wkw_slow_start_count,NULL))<5)){
		pokepow/=2;
	}

	//�A�C�e���ŋZ�^�C�v�ɂ��З̓A�b�v�̑������ʂ̂Ƃ��́A�З́����U���̓A�b�v
	for(i=0;i<NELEMS(SoubiItemWazaTypePowUpTbl);i++){
		if((wdcp_a.eqp==SoubiItemWazaTypePowUpTbl[i][0])&&(wazatype==SoubiItemWazaTypePowUpTbl[i][1])){
			wazapow=wazapow*(100+wdcp_a.atc)/100;
			break;
		}
	}

	//�A�C�e���œ����Z���������Ȃ��̑������ʂ̂Ƃ��́A�U����1.5�{�A�b�v
	if(wdcp_a.eqp==SOUBI_ONAZIWAZAONLY){
		pokepow=pokepow*150/100;
	}
	//�A�C�e���œ����Z���������Ȃ��̑������ʂ̂Ƃ��́A���U1.5�{�A�b�v
	if(wdcp_a.eqp==SOUBI_ONAZIAWZAONLYTOKUSYUUP){
		pokespepow=pokespepow*150/100;
	}

	//�A�C�e���œ��U�����h��1.5�{�̑������ʂ̂Ƃ��́A���U�����h1.5�{�A�b�v
	if((wdcp_a.eqp==SOUBI_TOKUKOUTOKUBOUUP)&&
	  ((fight_type&FIGHT_TYPE_TOWER)==0)&&
	  ((wdcp_a.monsno==MONSNO_RATHIOSU)||(wdcp_a.monsno==MONSNO_RATHIASU))){
		pokespepow=pokespepow*150/100;
	}

	//�A�C�e���œ��U�����h��1.5�{�̑������ʂ̂Ƃ��́A���U�����h1.5�{�A�b�v
	if((wdcp_d.eqp==SOUBI_TOKUKOUTOKUBOUUP)&&
	  ((fight_type&FIGHT_TYPE_TOWER)==0)&&
	  ((wdcp_d.monsno==MONSNO_RATHIOSU)||(wdcp_d.monsno==MONSNO_RATHIASU))){
		pokespedef=pokespedef*150/100;
	}

	//�A�C�e���Ńp�[���������Ɠ��U��2�{�̑������ʂ̂Ƃ��́A���U2�{�A�b�v
	if((wdcp_a.eqp==SOUBI_PAARURUTOKUKOUNIBAI)&&
	   (wdcp_a.monsno==MONSNO_PAARURU)){
		pokespepow*=2;
	}

	//�A�C�e���Ńp�[���������Ɠ��h��2�{�̑������ʂ̂Ƃ��́A���h2�{�A�b�v
	if((wdcp_d.eqp==SOUBI_PAARURUTOKUBOUNIBAI)&&
	   (wdcp_d.monsno==MONSNO_PAARURU)){
		pokespedef*=2;
	}

	//�A�C�e���Ńs�J�`���E�����ƈЗ�2�{�̑������ʂ̂Ƃ��́A�З�2�{�A�b�v
	if((wdcp_a.eqp==SOUBI_PIKATYUUTOKUKOUNIBAI)&&
	   (wdcp_a.monsno==MONSNO_PIKATYUU)){
		wazapow*=2;
	}

	//�A�C�e���Ń��^���������Ɩh��͂�2�{�̑������ʂ̂Ƃ��́A�h���2�{�A�b�v
	if((wdcp_d.eqp==SOUBI_METAMONDATOBOUGYORYOKUUP)&&
	   (wdcp_d.monsno==MONSNO_METAMON)){
		pokedef*=2;
	}

	//�A�C�e���ŃJ���J���A�K���K�������ƍU���͂�2�{�̑������ʂ̂Ƃ��́A�U����2�{�A�b�v
	if((wdcp_a.eqp==SOUBI_KARAGARADATOKOUGEKINIBAI)&&
	  ((wdcp_a.monsno==MONSNO_KARAKARA)||
	   (wdcp_a.monsno==MONSNO_GARAGARA))){
		pokepow*=2;
	}

	//�A�C�e���Ńf�B�A���K�����ƋZ�̈З͂�1.5�{
	if((wdcp_a.eqp==SOUBI_DORAGONHAGANEUP)&&
	  ((wazatype==DRAGON_TYPE)||(wazatype==METAL_TYPE))&&
	   (wdcp_a.monsno==MONSNO_IA)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//�A�C�e���Ńp���L�A�����ƋZ�̈З͂�1.5�{
	if((wdcp_a.eqp==SOUBI_DORAGONMIZUUP)&&
	  ((wazatype==DRAGON_TYPE)||(wazatype==WATER_TYPE))&&
	   (wdcp_a.monsno==MONSNO_EA)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//�A�C�e���ŁA�����U���̈З͂��A�b�v�̎��́A�З͂��A�b�v
	if((wdcp_a.eqp==SOUBI_BUTURIIRYOKUUP)&&(wazakind==KIND_BUTSURI)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//�A�C�e���ŁA����U���̈З͂��A�b�v�̎��́A�З͂��A�b�v
	if((wdcp_a.eqp==SOUBI_TOKUSYUIRYOKUUP)&&(wazakind==KIND_TOKUSYU)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//����\�͂������ڂ��́A�ق̂��A������ɂ悢
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_ATUISIBOU)==TRUE)&&
	  ((wazatype==FIRE_TYPE)||(wazatype==KOORI_TYPE))){
		wazapow/=2;
	}

	//����\�͂͂肫��́A�U����1.5�{�A�b�v
	if(wdcp_a.speabino==TOKUSYU_HARIKIRI){
		pokepow=pokepow*150/100;
	}

	//����\�͂��񂶂傤�́A��Ԉُ�̂Ƃ��ɍU����1.5�{�A�b�v
	if((wdcp_a.speabino==TOKUSYU_KONZYOU)&&(wdcp_a.condition)){
		pokepow=pokepow*150/100;
	}

	//����\�͂ӂ����Ȃ��낱�́A��Ԉُ�̂Ƃ��ɖh���1.5�{�A�b�v
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_HUSIGINAUROKO)==TRUE)&&(wdcp_d.condition)){
		pokedef=pokedef*150/100;
	}

	//����\�̓v���X�A�}�C�i�X�͂��݂�����ɂ���Ɠ���U���͂�1.5�{�A�b�v
	if((wdcp_a.speabino==TOKUSYU_PURASU)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_MINE_SIDE_HP,attack,TOKUSYU_MAINASU))){
		pokespepow=pokespepow*150/100;
	}
	if((wdcp_a.speabino==TOKUSYU_MAINASU)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_MINE_SIDE_HP,attack,TOKUSYU_PURASU))){
		pokespepow=pokespepow*150/100;
	}

	//�Z���ʂǂ날���т́A�d�C�n�̋Z�̈З͂𔼌�
	if((wazatype==ELECTRIC_TYPE)&&(ST_ServerWazaKoukaCheck(bw,sp,WAZAKOUKA_DOROASOBI))){
		wazapow/=2;
	}

	//�Z���ʂ݂������т́A���n�̋Z�̈З͂𔼌�
	if((wazatype==FIRE_TYPE)&&(ST_ServerWazaKoukaCheck(bw,sp,WAZAKOUKA_MIZUASOBI))){
		wazapow/=2;
	}

	//����\�͂����傭��HP1/3�ȉ��ő��^�C�v�̈З͂�1.5�{�ɂ���
	if((wazatype==KUSA_TYPE)&&(wdcp_a.speabino==TOKUSYU_SINRYOKU)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}

	//����\�͂�������HP1/3�ȉ��ŉ��^�C�v�̈З͂�1.5�{�ɂ���
	if((wazatype==FIRE_TYPE)&&(wdcp_a.speabino==TOKUSYU_MOUKA)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}

	//����\�͂�����イ��HP1/3�ȉ��Ő��^�C�v�̈З͂�1.5�{�ɂ���
	if((wazatype==WATER_TYPE)&&(wdcp_a.speabino==TOKUSYU_GEKIRYUU)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}
	//����\�͂ނ��̂��点��HP1/3�ȉ��Œ��^�C�v�̈З͂�1.5�{�ɂ���
	if((wazatype==MUSHI_TYPE)&&(wdcp_a.speabino==TOKUSYU_MUSINOSIRASE)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}
	//���������˂́A���n�̋Z�̈З͂𔼌�
	if((wazatype==FIRE_TYPE)&&(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TAINETU)==TRUE)){
		wazapow/=2;
	}
	//�������񂻂��͂��́A���n�̋Z�̈З͂�25%��
	if((wazatype==FIRE_TYPE)&&(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_KANSOUHADA)==TRUE)){
		wazapow=wazapow*125/100;
	}
	//�������񂶂��́A�\�͕ω��l��{
	if(wdcp_a.speabino==TOKUSYU_TANZYUN){
		condpow*=2;
		if(condpow<-6){
			condpow=-6;
		}
		if(condpow>6){
			condpow=6;
		}
		condspepow*=2;
		if(condspepow<-6){
			condspepow=-6;
		}
		if(condspepow>6){
			condspepow=6;
		}
	}
	//�������񂶂��́A�\�͕ω��l��{
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TANZYUN)==TRUE){
		conddef*=2;
		if(conddef<-6){
			conddef=-6;
		}
		if(conddef>6){
			conddef=6;
		}
		condspedef*=2;
		if(condspedef<-6){
			condspedef=-6;
		}
		if(condspedef>6){
			condspedef=6;
		}
	}

	//�����Ă�˂�́A�\�͕ω��l���t���b�g
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TENNEN)==TRUE){
		condpow=0;
		condspepow=0;
	}
	//�����Ă�˂�́A�\�͕ω��l���t���b�g
	if(wdcp_a.speabino==TOKUSYU_TENNEN){
		conddef=0;
		condspedef=0;
	}

	condpow+=6;
	conddef+=6;
	condspepow+=6;
	condspedef+=6;

	//�����Ƃ���������́A���ʂ��ꏏ��������1.25�{�ɂ���
	if((wdcp_a.speabino==TOKUSYU_TOUSOUSIN)&&
	   (wdcp_a.sex==wdcp_d.sex)&&(wdcp_a.sex!=PARA_UNK)&&(wdcp_d.sex!=PARA_UNK)){
		wazapow=wazapow*125/100;
	}
	//�����Ƃ���������́A���ʂ��������0.75�{�ɂ���
	if((wdcp_a.speabino==TOKUSYU_TOUSOUSIN)&&
	   (wdcp_a.sex!=wdcp_d.sex)&&(wdcp_a.sex!=PARA_UNK)&&(wdcp_d.sex!=PARA_UNK)){
		wazapow=wazapow*75/100;
	}

	//�����Ă̂��Ԃ��́A�p���`�n�̋Z�̈З͂�1.2�{�ɂ���
	for(i=0;i<NELEMS(TetsunoKobushiTable);i++){
		if((TetsunoKobushiTable[i]==wazano)&&(wdcp_a.speabino==TOKUSYU_TETUNOKOBUSI)){
			wazapow=wazapow*12/10;
			break;
		}
	}

	//�V��`�F�b�N�i�̂��Ă񂫂̃|�P�������퓬�ɏo�Ă���ꍇ�͓V��`�F�b�N���Ȃ��j
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//�����T���p���[�́A�͂�̎��A���U��1.5�{�ɂ���
		if((field_cond&FIELD_CONDITION_HARE_ALL)&&(wdcp_a.speabino==TOKUSYU_SANPAWAA)){
			pokespepow=pokespepow*15/10;
		}
		//��^�C�v�́A���Ȃ��炵�̎��A���h��1.5�{�ɂ���
		if((field_cond&FIELD_CONDITION_SUNAARASHI_ALL)&&
		  ((wdcp_d.type1==IWA_TYPE)||(wdcp_d.type2==IWA_TYPE))){
			pokespedef=pokespedef*15/10;
		}
		//�����t�����[�M�t�g�́A�V�󂪐���̂Ƃ��A�����Ɩ����̍U���Ɠ��h��1.5�{����B
		if((field_cond&FIELD_CONDITION_HARE_ALL)&&
		   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_MINE_SIDE_HP,attack,TOKUSYU_HURAWAAGIHUTO))){
			pokepow=pokepow*15/10;
		}
		if((field_cond&FIELD_CONDITION_HARE_ALL)&&
		   (ST_ServerTokuseiGet(sp,attack)!=TOKUSYU_KATAYABURI)&&
		   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_MINE_SIDE_HP,defence,TOKUSYU_HURAWAAGIHUTO))){
			pokespedef=pokespedef*15/10;
		}
	}

	//�u���΂��v�u�����΂��͂v�́A�h��͂𔼕��ɂ��Čv�Z����
	if(sp->AIWT.wtd[wazano].battleeffect==7){
		pokedef=pokedef/2;
	}

	if(wazakind==KIND_BUTSURI){	//�����U��
		if(critical>1){
			if(condpow>6){
				damage=pokepow*CondChgTable[condpow][0];
				damage/=CondChgTable[condpow][1];
			}
			else{
				damage=pokepow;
			}
		}
		else{
			damage=pokepow*CondChgTable[condpow][0];
			damage/=CondChgTable[condpow][1];
		}

		damage*=wazapow;
		damage*=(level*2/5+2);

		if(critical>1){
			if(conddef<6){
				damage2=pokedef*CondChgTable[conddef][0];
				damage2/=CondChgTable[conddef][1];
			}
			else{
				damage2=pokedef;
			}
		}
		else{
			damage2=pokedef*CondChgTable[conddef][0];
			damage2/=CondChgTable[conddef][1];
		}

		damage/=damage2;
		damage/=50;

		//����\�͂��񂶂傤�́A��Ԉُ�ōU���͂�������̂ł��̔���͖���
		if((wdcp_a.condition&CONDITION_YAKEDO)&&(wdcp_a.speabino!=TOKUSYU_KONZYOU)){
			damage/=2;
		}

		//�퓬����186�̓K�[�h�̉e�����󂯂Ȃ�
		if(((side_cond&SIDE_CONDITION_BUTSURIGUARD)!=0)&&(critical==1)&&(sp->AIWT.wtd[wazano].battleeffect!=186)){
			if((fight_type&FIGHT_TYPE_2vs2)&&(ST_ServerHitCountCheck(bw,sp,SHCC_SIDE,defence)==2)){
				damage=damage*2/3;
			}
			else{
				damage/=2;
			}
		}
	}
	else if(wazakind==KIND_TOKUSYU){			//����U��
		if(critical>1){
			if(condspepow>6){
				damage=pokespepow*CondChgTable[condspepow][0];
				damage/=CondChgTable[condspepow][1];
			}
			else{
				damage=pokespepow;
			}
		}
		else{
			damage=pokespepow*CondChgTable[condspepow][0];
			damage/=CondChgTable[condspepow][1];
		}

		damage*=wazapow;
		damage*=(level*2/5+2);

		if(critical>1){
			if(condspedef<6){
				damage2=pokespedef*CondChgTable[condspedef][0];
				damage2/=CondChgTable[condspedef][1];
			}
			else{
				damage2=pokespedef;
			}
		}
		else{
			damage2=pokespedef*CondChgTable[condspedef][0];
			damage2/=CondChgTable[condspedef][1];
		}

		damage/=damage2;
		damage/=50;

		//�퓬����186�̓K�[�h�̉e�����󂯂Ȃ�
		if(((side_cond&SIDE_CONDITION_TOKUSYUGUARD)!=0)&&(critical==1)&&(sp->AIWT.wtd[wazano].battleeffect!=186)){
			if((fight_type&FIGHT_TYPE_2vs2)&&(ST_ServerHitCountCheck(bw,sp,SHCC_SIDE,defence)==2)){
				damage=damage*2/3;
			}
			else{
				damage/=2;
			}
		}

	}

	if((fight_type&FIGHT_TYPE_2vs2)&&
	   (sp->AIWT.wtd[wazano].attackrange==RANGE_DOUBLE)&&
	   (ST_ServerHitCountCheck(bw,sp,SHCC_SIDE,defence)==2)){
		damage=damage*3/4;
	}
	if((fight_type&FIGHT_TYPE_2vs2)&&
	   (sp->AIWT.wtd[wazano].attackrange==RANGE_TRIPLE)&&
	   (ST_ServerHitCountCheck(bw,sp,SHCC_NORMAL,defence)>=2)){
		damage=damage*3/4;
	}

	//�V��`�F�b�N�i�̂��Ă񂫂̃|�P�������퓬�ɏo�Ă���ꍇ�͓V��`�F�b�N���Ȃ��j
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		if(field_cond&FIELD_CONDITION_AME_ALL){
			switch(wazatype){
				case FIRE_TYPE:
					damage/=2;
					break;
				case WATER_TYPE:
					damage=damage*15/10;
					break;
			}
		}

		if((field_cond&FIELD_CONDITION_NO_SOLAR)&&(wazano==WAZANO_SOORAABIIMU)){
			damage/=2;
		}
		if(field_cond&FIELD_CONDITION_HARE_ALL){
			switch(wazatype){
				case FIRE_TYPE:
					damage=damage*15/10;
					break;
				case WATER_TYPE:
					damage/=2;
					break;
			}
		}
	}

	//����\�͂��炢�у`�F�b�N
	if((ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_wkw_moraibi_flag,NULL))&&(wazatype==FIRE_TYPE)){
		damage=damage*15/10;
	}

	return	damage+2;
}

// =================================================================
// void	WS_DAMAGE_LOSS
// �T�v  : �_���[�W�v�Z�ŋ��߂��l��85%�`100%�͈̔͂Œ�������
// ����  : none
// �߂�l: none
// =================================================================
int		ST_DamageLossCalc(SERVER_PARAM *sp,int damage)
{
#ifdef PM_DEBUG
	//�f�o�b�O���[�h�Ń_���[�W�Œ�t���O�������Ă���ꍇ�́ALossCalc�͂��Ȃ�
	if(sp->dbp.debug_flag&DEBUG_FLAG_DAMAGE_LOCK){
		return damage;
	}
#endif

	if(damage){
		damage*=(100-(gf_rand()%16));
		damage/=100;
		if(damage==0){
			damage=1;
		}
	}

	return damage;
}

//============================================================================================
/**
 *	�N���e�B�J���q�b�g���ł�m���e�[�u��
 */
//============================================================================================
static	const	u8	CriticalTable[]={
	16,8,4,3,2
};

//============================================================================================
/**
 *	�}���ɓ����邩�ǂ����̃`�F�b�N
 *
 * @param[in]	sp				�T�[�o�p�����[�^�\���̂̃|�C���^
 * @param[in]	attack			�U����ClientNo
 * @param[in]	defence			�h�䑤ClientNo
 * @param[in]	critical_count	�N���e�B�J���q�b�g�̔{����ϓ������郏�[�N
 *
 * @retval	1:�_���[�W�{��1�{	2:�_���[�W�{��2�{
 */
//============================================================================================
int		ST_CriticalCheck(SERVER_PARAM *sp,int attack,int defence,int critical_count,u32 side_condition)
{
	u16		work;
	u16		item;
	int		eqp;
	u16		monsno;
	u32		condition2;
	u32		waza_kouka;
	int		ret=1;
	int		speabi;

	item=ST_ServerSoubiItemNoGet(sp,attack);
//	eqp=ItemParamGet(item,ITEM_PRM_EQUIP,HEAPID_BATTLE);
	eqp=ST_ItemParamGet(sp,item,ITEM_PRM_EQUIP);

	monsno=sp->psp[attack].monsno;
	condition2=sp->psp[attack].condition2;
	waza_kouka=sp->psp[defence].waza_kouka;
	speabi=sp->psp[attack].speabino;

	work=(((condition2&CONDITION2_KIAIDAME)!=0)*2)+
		 (eqp==SOUBI_KYUUSYONIATARIYASUI)+
		 critical_count+
		 //�������傤����́A�}���q�b�g�i�K���P�A�b�v����
		 (speabi==TOKUSYU_KYOUUN)+
		 (2*((eqp==SOUBI_RAKKIIDATOKYUUSYONIATARIYASUI)&&(monsno==MONSNO_RAKKII)))+
		 (2*((eqp==SOUBI_KAMONEGIKYUUSYOATARIYASUI)&&(monsno==MONSNO_KAMONEGI)));

	if(work>4){
		work=4;
	}

	if(gf_rand()%CriticalTable[work]==0){
		//�����J�u�g�A�[�}�[�A�V�F���A�[�}�[������Ƃ��͋}���ɂ�����Ȃ�
		if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_KABUTOAAMAA)==FALSE)&&
		   (ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_SHERUAAMAA)==FALSE)&&
		  ((side_condition&SIDE_CONDITION_OMAZINAI)==0)&&
		  ((waza_kouka&WAZAKOUKA_NOCRITICAL)==0)){
			ret=2;
		}
	}

	//�����X�i�C�p�[�́A�}���{����3�{�ɂ���
	if((ret==2)&&(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_SUNAIPAA)){
		ret=3;
	}

	return ret;
}

//============================================================================================
/**
 * ����ȋZ�e�[�u��
 */
//============================================================================================
#define	MONOMANE_NG_TBL_END	(0xfffe)
#define	WAZA_OUT_NG_TBL_END	(0xffff)

static	const u16 WazaOutNGTbl[]={
	WAZANO_YUBIWOHURU,			// ��т��ӂ�
	WAZANO_WARUAGAKI,			// ��邠����
	WAZANO_SUKETTI,				// �X�P�b�`
	WAZANO_MONOMANE,			// ���̂܂�
	WAZANO_OSYABERI,			// ������ׂ�
	MONOMANE_NG_TBL_END,		// ���̂܂˂ł��Ȃ��e�[�u���̃G���h
	WAZANO_NEGOTO,				// �˂���
	WAZANO_NEKONOTE,			// �˂��̂�
	WAZANO_OUMUGAESI,			// �I�E��������
	WAZANO_KAUNTAA,				// �J�E���^�[
	WAZANO_MIRAAKOOTO,			// �~���[�R�[�g
	WAZANO_MAMORU,				// �܂���
	WAZANO_MIKIRI,				// �݂���
	WAZANO_KORAERU,				// ���炦��
	WAZANO_MITIDURE,			// �݂��Â�
	WAZANO_DOROBOU,				// �ǂ�ڂ�
	WAZANO_KONOYUBITOMARE,		// ���̂�тƂ܂�
	WAZANO_YOKODORI,			// �悱�ǂ�
	WAZANO_TEDASUKE,			// �Ă�����
	WAZANO_HOSIGARU,			// �ق�����
	WAZANO_TORIKKU,				// �g���b�N
	WAZANO_KIAIPANTI,			// �������p���`
	WAZANO_FEINTO,				// �t�F�C���g
	WAZANO_MANEKKO,				// �܂˂���
	WAZANO_SAKIDORI,			// �����ǂ�
	WAZANO_SURIKAE,				// ���肩��
	WAZA_OUT_NG_TBL_END
};

//============================================================================================
/**
 *	���̂܂˂ł���Z���`�F�b�N
 *
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 *
 * @retval	FALSE:�ł��Ȃ��@TRUE:�ł���
 */
//============================================================================================
BOOL	ST_MonomaneNGCheck(u16 waza_no)
{
	int	i;

	i=0;

	while(WazaOutNGTbl[i]!=MONOMANE_NG_TBL_END){
		if(WazaOutNGTbl[i]==waza_no){
			break;
		}
		i++;
	}
	return (WazaOutNGTbl[i]==MONOMANE_NG_TBL_END);
}

//============================================================================================
/**
 *	��т��ӂ�ł�����Z���`�F�b�N
 *
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 *
 * @retval	FALSE:�o���Ȃ��@TRUE:�o����
 */
//============================================================================================
BOOL	ST_YubiwohuruNGCheck(u16 waza_no)
{
	int	i;

	i=0;

	while(WazaOutNGTbl[i]!=WAZA_OUT_NG_TBL_END){
		if(WazaOutNGTbl[i]==waza_no){
			break;
		}
		i++;
	}
	return (WazaOutNGTbl[i]==WAZA_OUT_NG_TBL_END);
}

//============================================================================================
/**
 *	�I�E���������ŕԂ��邩�A�A���R�[���o����Z���`�F�b�N�p�Z�i���o�[�e�[�u��
 */
//============================================================================================

static	const	u16		WazaOumuEncoreNGCheckTable[]={
	WAZANO_HENSIN,
	WAZANO_MONOMANE,
	WAZANO_SUKETTI,
	WAZANO_OUMUGAESI,
	WAZANO_ANKOORU,
	WAZANO_WARUAGAKI,
};

//============================================================================================
/**
 *	�I�E���������ŕԂ��邩�A�A���R�[���o����Z���`�F�b�N
 *
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 *
 * @retval	FALSE:�o���Ȃ��@TRUE:�o����
 */
//============================================================================================
BOOL	ST_OumuEncoreNGCheck(SERVER_PARAM *sp,u16 waza_no)
{
	int	i;

	i=0;

	while(i<NELEMS(WazaOumuEncoreNGCheckTable)){
//		if(WT_WazaDataParaGet(WazaOumuEncoreNGCheckTable[i],ID_WTD_battleeffect)==
//		   WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)){
		if(sp->AIWT.wtd[WazaOumuEncoreNGCheckTable[i]].battleeffect==sp->AIWT.wtd[waza_no].battleeffect){
			break;
		}
		i++;
	}

	return (i==NELEMS(WazaOumuEncoreNGCheckTable));
}

//============================================================================================
/**
 *	�����ǂ萬������Z���`�F�b�N�p�Z�i���o�[�e�[�u��
 */
//============================================================================================

static	const	u16		SakidoriNGCheckTable[]={
	WAZANO_KAUNTAA,
	WAZANO_MIRAAKOOTO,
	WAZANO_DOROBOU,
	WAZANO_HOSIGARU,
	WAZANO_KIAIPANTI,
	WAZANO_OSYABERI,
};

//============================================================================================
/**
 *	�����ǂ萬������Z���`�F�b�N
 *
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 *
 * @retval	FALSE:�o���Ȃ��@TRUE:�o����
 */
//============================================================================================
BOOL	ST_SakidoriNGCheck(SERVER_PARAM *sp,u16 waza_no)
{
	int	i;

	i=0;

	while(i<NELEMS(SakidoriNGCheckTable)){
		if(sp->AIWT.wtd[SakidoriNGCheckTable[i]].battleeffect==sp->AIWT.wtd[waza_no].battleeffect){
			break;
		}
		i++;
	}

	return (i==NELEMS(SakidoriNGCheckTable));
}

//============================================================================================
/**
 *	�A�C�e���p�����[�^�̎擾
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	item_no		�擾�������A�C�e���i���o�[
 * @param[in]	param		�擾�������p�����[�^��ID
 *
 * @retval	�l
 */
//============================================================================================
s32	ST_ItemParamGet(SERVER_PARAM *sp,u16 item_no,u16 param)
{
	ITEMDATA	*item_data;
	u16			index;

	index=GetItemIndex(item_no,ITEM_GET_DATA);
	item_data=GetItemDataPointer(sp->AIWT.item,index);

	return ItemBufParamGet(item_data,param);
}

//============================================================================================
/**
 *	dir�p�����[�^����ClientNo���擾
 *
 * @param[in]	bw		�퓬�V�X�e���\���̃|�C���^
 * @param[in]	sp		�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	dir		�擾������ClientNo�̌���
 *
 * @retval	�l
 */
//============================================================================================
int		ST_ServerDir2ClientNoGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int dir)
{
	int	client_no;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(client_no=0;client_no<client_set_max;client_no++){
		if(BattleWorkMineEnemyCheck(bw,client_no)==dir){
			break;
		}
	}

	return client_no;
}

//============================================================================================
/**
 *	�g���b�N���[������
 *
 * @param[in]	bw		�퓬�V�X�e���\���̃|�C���^
 * @param[in]	sp		�T�[�o�p�����[�^�̍\���̃|�C���^
 */
//============================================================================================
void	ST_ServerTrickRoomAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i,j;
	int	cl1;
	int	cl2;
	int	flag;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(i=0;i<client_set_max-1;i++){
		for(j=i+1;j<client_set_max;j++){
			cl1=sp->client_agi_work[i];
			cl2=sp->client_agi_work[j];
			if(sp->client_act_work[cl1][ACT_PARA_SELECT_COMMAND]==sp->client_act_work[cl2][ACT_PARA_SELECT_COMMAND]){
				if(sp->client_act_work[cl1][ACT_PARA_SELECT_COMMAND]==SELECT_FIGHT_COMMAND){
					flag=0;
				}
				else{
					flag=1;
				}
				if(ST_ServerAgiCalc(bw,sp,cl1,cl2,flag)){
					sp->client_agi_work[i]=cl2;
					sp->client_agi_work[j]=cl1;
				}
			}
		}
	}
}

//============================================================================================
/**
 *	�݂���肪���邩�`�F�b�N���āASTATUS_EFFECT�������ł��邩���f�p�e�[�u��
 */
//============================================================================================
static	const	int	MigawariOKStatusEffect[]={
	STATUS_EFF_MIGAWARI_OUT,	///< o��ʊO��
	STATUS_EFF_MIGAWARI_IN,		///< o��ʓ���
	STATUS_EFF_ITEM_POUCH,		///< o�G�l�R�����ۂƃs�b�s�l�`
	STATUS_WEATHER_MIST,		///< �V�� ��
	STATUS_WEATHER_RAIN,		///< �V�� �J
	STATUS_WEATHER_ICE,			///< �V�� �����
	STATUS_WEATHER_SAND,		///< �V�� �����炵
	STATUS_WEATHER_SUN,			///< �V�� �Ђ���
	STATUS_ACTION_DOLL_ON,		///< o���� �݂���肨���Ă���
	STATUS_ACTION_DOLL_OFF,		///< ���� �݂����OFF
};

//============================================================================================
/**
 *	�݂���肪���邩�`�F�b�N���āASTATUS_EFFECT�������ł��邩���f
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�`�F�b�N������ClientNo
 * @param[in]	status		�`�F�b�N������STATUS_EFFECT�i���o�[
 *
 * @retval	FALSE:�����ł��Ȃ��@TRUE:�����ł���
 */
//============================================================================================
BOOL	ST_ServerStatusEffectMigawariCheck(SERVER_PARAM *sp,int client_no,int status)
{
	int		i;
	BOOL	ret=FALSE;

	if((sp->psp[client_no].condition2&CONDITION2_MIGAWARI)||
	   (sp->psp[client_no].waza_kouka&WAZAKOUKA_KIE)){
		for(i=0;i<NELEMS(MigawariOKStatusEffect);i++){
			if(MigawariOKStatusEffect[i]==status){
				ret=TRUE;
				break;
			}
		}
	}
	else{
		ret=TRUE;
	}

	return ret;
}

//============================================================================================
/**
 *	�U�����q�b�g�������Ƀ`�F�b�N���鑕�����ʁi�Ƃ�ڂ��������j
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�`�F�b�N������ClientNo
 * @param[in]	status		�`�F�b�N������STATUS_EFFECT�i���o�[
 *
 * @retval	FALSE:�����ł��Ȃ��@TRUE:�����ł���
 */
//============================================================================================
BOOL	ST_ServerWazaHitSoubiItemCheckTonbogaeri(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret;
	int		client_no;
	int		eqp_a;
	int		atk_a;
	int		eqp_d;
	int		atk_d;
	int		dir;
	
	ret=FALSE;

	eqp_a=ST_ServerSoubiEqpGet(sp,sp->attack_client);
	atk_a=ST_ServerSoubiAtkGet(sp,sp->attack_client,ATK_CHECK_NORMAL);

	eqp_d=ST_ServerSoubiEqpGet(sp,sp->defence_client);
	atk_d=ST_ServerSoubiAtkGet(sp,sp->defence_client,ATK_CHECK_NORMAL);

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);

	if((eqp_a==SOUBI_HPKAIHUKUDAMEEZIRITU)&&
	   (sp->server_status_flag&SERVER_STATUS_FLAG_WAZA_HIT)&&
       (sp->ostf[sp->attack_client].kaigara_damage)&&
	   (sp->attack_client!=sp->defence_client)&&
	   (sp->psp[sp->attack_client].hp<sp->psp[sp->attack_client].hpmax)&&
	   (sp->psp[sp->attack_client].hp)){
		sp->hp_calc_work=ST_ServerDamageDiv(sp->ostf[sp->attack_client].kaigara_damage*-1,atk_a);
		sp->client_work=sp->attack_client;
		seq_no[0]=SUB_SEQ_EQPITEM_HP_KAIHUKUMAITURN;
		ret=TRUE;
	}

	if((eqp_a==SOUBI_WAZAIRYOKUUPHPMAINASU)&&
		//�����}�W�b�N�K�[�h�̓_���[�W�Ȃ�
	   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
	   (sp->server_status_flag&SERVER_STATUS_FLAG_WAZA_HIT)&&
	   (sp->AIWT.wtd[sp->waza_no_now].kind!=KIND_HENKA)&&
	   (sp->psp[sp->attack_client].hp)){
		sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*-1,10);
		sp->client_work=sp->attack_client;
		seq_no[0]=SUB_SEQ_EQPITEM_HP_MAINASU;
		ret=TRUE;
	}

	if((eqp_d==SOUBI_BUTURIDEKOUGEKI)&&
	   (sp->psp[sp->attack_client].hp)&&
		//�����}�W�b�N�K�[�h�ɂ͕s��
	   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
	   (sp->ostf[sp->defence_client].butsuri_ostf_damage)){
		sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*-1,atk_d);
		seq_no[0]=SUB_SEQ_EQPITEM_HIT_DAMAGE;
		ret=TRUE;
	}
	if((eqp_d==SOUBI_TEKINIMOTASETEDAMEEZI)&&
	   (sp->psp[sp->attack_client].hp)&&
	   (sp->psp[sp->attack_client].item==0)&&
	  ((sp->scw[dir].hatakiotosu_item&No2Bit(sp->sel_mons_no[sp->attack_client]))==0)&&
	  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
	   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
	   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_DAGEKI)){
		seq_no[0]=SUB_SEQ_EQPITEM_KUTTUKI;
		ret=TRUE;
	}

	return ret;
}

//============================================================================================
/**
 *	�U���Ώۂ��v���b�V���[�������Ă��邩�`�F�b�N����PP�����炷
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	attack		�U����ClientNo
 * @param[in]	defence		�h�䑤ClientNo
 */
//============================================================================================
void	ST_ServerPressurePPDecCheck(SERVER_PARAM *sp,int attack,int defence)
{
	if((ST_ServerTokuseiGet(sp,defence)==TOKUSYU_PURESSYAA)&&
	   (defence!=NONE_CLIENT_NO)&&
	   (sp->psp[attack].pp[sp->waza_no_pos[attack]])){
		sp->psp[attack].pp[sp->waza_no_pos[attack]]--;
	}
}

//============================================================================================
//			�p�����[�^�Q�b�g�n
//============================================================================================
//============================================================================================
/**
 *	SERVER_PARAM�\���̂̃����o�̒l���擾
 *
 * @param[in]	bw			�퓬�p�����[�^�̍\���̃|�C���^
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	id			�擾�����������o�̃C���f�b�N�X
 * @param[in]	client_no	�擾�����������o��ClientNo�i�K�v�ȏꍇ�j
 *
 * @retval	�l
 */
//============================================================================================
int		ST_ServerParamDataGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no)
{
	int	dir;

	switch(id){
	case ID_SP_side_condition:
		dir=BattleWorkMineEnemyCheck(bw,client_no);
		return sp->side_condition[dir];
		break;
	case ID_SP_shiroikiri_count:
		dir=BattleWorkMineEnemyCheck(bw,client_no);
		return sp->scw[dir].shiroikiri_count;
		break;
	case ID_SP_sel_mons_no:
		return sp->sel_mons_no[client_no];
		break;
	case ID_SP_total_turn:
		return sp->total_turn;
		break;
	case ID_SP_level_up_pokemon:
		return sp->level_up_pokemon;
		break;
	case ID_SP_safari_escape_count:
		return sp->safari_escape_count;
		break;
	case ID_SP_total_hinshi:
		return sp->total_hinshi[client_no];
		break;
	case ID_SP_total_damage:
		return sp->total_damage[client_no];
		break;
	case ID_SP_act_no:
		return sp->client_act_work[client_no][ACT_PARA_ACT_NO];
		break;
	case ID_SP_ai_defence_client:
		return sp->AIWT.AI_DefenceClient;
		break;
	case ID_SP_no_reshuffle_client:
		return sp->no_reshuffle_client;
		break;
	case ID_SP_dir_select_client:
		return sp->AIWT.AI_DirSelectClient[client_no];
		break;
	case ID_SP_act_work:
		return sp->client_act_work[client_no][ACT_PARA_WORK];
		break;
	}
	GF_ASSERT_MSG((0),"��`����Ă��Ȃ�ID�ł�\n");
	return 0;
}

//============================================================================================
//			�p�����[�^�Z�b�g�n
//============================================================================================
//============================================================================================
/**
 *	ostf_status_flag���Z�b�g
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	client_no	�Z�b�g����ClientNo
 * @param[in]	value		�Z�b�g����l
 */
//============================================================================================
void	ST_ServerOSTFStatusFlagSet(SERVER_PARAM *sp,int client_no,u32 value)
{
	sp->ostf[client_no].status_flag|=value;
}

//============================================================================================
/**
 *	SERVER_PARAM�̃����o�ɒl���Z�b�g
 *
 * @param[in]	bw			�퓬�p�����[�^�̍\���̃|�C���^
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	id			�Z�b�g�����������o�̃C���f�b�N�X
 * @param[in]	client_no	�Z�b�g�����������o��ClientNo�i�K�v�ȏꍇ�j
 * @param[in]	data		�Z�b�g����l
 */
//============================================================================================
void	ST_ServerParamDataPut(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no,int data)
{
	int	dir;

	switch(id){
	case ID_SP_side_condition:
		dir=BattleWorkMineEnemyCheck(bw,client_no);
		sp->side_condition[dir]=data;
		break;
	case ID_SP_shiroikiri_count:
		dir=BattleWorkMineEnemyCheck(bw,client_no);
		sp->scw[dir].shiroikiri_count=data;
		break;
	case ID_SP_sel_mons_no:
		sp->sel_mons_no[client_no]=data;
		break;
	case ID_SP_total_turn:
		sp->total_turn=data;
		break;
	case ID_SP_ai_defence_client:
		sp->AIWT.AI_DefenceClient=data;
		break;
	case ID_SP_dir_select_client:
		sp->AIWT.AI_DirSelectClient[client_no]=data;
		break;
	default:
		GF_ASSERT_MSG((0),"��`����Ă��Ȃ�ID�ł�\n");
		break;
	}
}

//============================================================================================
//			�O�����J���Ȃ��n
//============================================================================================
//============================================================================================
//			�ǉ����ʓ��������V�[�P���X�i���o�[�e�[�u��
//============================================================================================
static const int AddStatusSeqNoTable[]=
{
	NULL,		//�_�~�[
	SUB_SEQ_NEMURI,				//�˂ނ�
	SUB_SEQ_DOKU,				//��
	SUB_SEQ_YAKEDO,				//�₯��
	SUB_SEQ_KOORI,				//������
	SUB_SEQ_MAHI,				//�܂�
	SUB_SEQ_DOKUDOKU,			//�ǂ��ǂ�
	SUB_SEQ_KONRAN,				//������
	SUB_SEQ_HIRUMU,				//�Ђ��
	SUB_SEQ_NEMURU,				//�˂ނ�
	SUB_SEQ_SAWAGU,				//���킮
	SUB_SEQ_NEKONIKOBAN,		//�˂��ɂ��΂�
	SUB_SEQ_KEEP,				//���ߌn�̋Z
	SUB_SEQ_SHIME,				//���ߌn�̋Z
	SUB_SEQ_HANEKAERI,			//�͂˂�����n�̋Z(1/4)
	SUB_SEQ_ABICNT_CALC,		//�U���̓A�b�v
	SUB_SEQ_ABICNT_CALC,		//�h��̓A�b�v
	SUB_SEQ_ABICNT_CALC,		//�f�����A�b�v
	SUB_SEQ_ABICNT_CALC,		//���U�A�b�v
	SUB_SEQ_ABICNT_CALC,		//���h�A�b�v
	SUB_SEQ_ABICNT_CALC,		//�������A�b�v
	SUB_SEQ_ABICNT_CALC,		//��𗦃A�b�v
	SUB_SEQ_ABICNT_CALC,		//�U���̓_�E��
	SUB_SEQ_ABICNT_CALC,		//�h��̓_�E��
	SUB_SEQ_ABICNT_CALC,		//�f�����_�E��
	SUB_SEQ_ABICNT_CALC,		//���U�_�E��
	SUB_SEQ_ABICNT_CALC,		//���h�_�E��
	SUB_SEQ_ABICNT_CALC,		//�������_�E��
	SUB_SEQ_ABICNT_CALC,		//��𗦃_�E��
	SUB_SEQ_HANDOU,				//�͂�ǂ�
	SUB_SEQ_IKARI,				//������
	SUB_SEQ_DOROBOU,			//�ǂ�ڂ�
	SUB_SEQ_KUROIMANAZASI,		//���낢�܂Ȃ���
	SUB_SEQ_AKUMU,				//������
	SUB_SEQ_GENSHINOCHIKARA,	//���񂵂̂�����
	SUB_SEQ_KOUSOKUSPIN,		//���������X�s��
	SUB_SEQ_NO_MAHI,			//�܂Ђ��Ȃ���
	SUB_SEQ_BAKADIKARA,			//�΂�������
	SUB_SEQ_HANEKAERI2,			//�͂˂�����n�̋Z(1/3)
	SUB_SEQ_ABICNT_CALC,		//�U���̓A�b�v(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//�h��̓A�b�v(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//�f�����A�b�v(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//���U�A�b�v(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//���h�A�b�v(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//�������A�b�v(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//��𗦃A�b�v(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//�U���̓_�E��(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//�h��̓_�E��(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//�f�����_�E��(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//���U�_�E��(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//���h�_�E��(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//�������_�E��(2�i�K�j
	SUB_SEQ_ABICNT_CALC,		//��𗦃_�E��(2�i�K�j
	SUB_SEQ_ABARERU,			//���΂��
	SUB_SEQ_HATAKIOTOSU,		//�͂������Ƃ�
	SUB_SEQ_COSMO_POWER,		//�R�X���p���[�i�����A�b�v�iabiritycnt�n�j�j
	SUB_SEQ_BUILD_UP,			//�r���h�A�b�v�i�����A�b�v�iabiritycnt�n�j�j
	SUB_SEQ_KUSUGURU,			//��������i�����_�E���iabiritycnt�n�j�j
	SUB_SEQ_MEISOU,				//�߂������i�����A�b�v�iabiritycnt�n�j�j
	SUB_SEQ_RYUUNOMAI,			//��イ�̂܂��i�����A�b�v�iabiritycnt�n�j�j
	SUB_SEQ_SUITORI,			//HP�����Ƃ�n
	SUB_SEQ_YUMEKUI,			//��߂���
	SUB_SEQ_KUROIKIRI,			//���낢����
	SUB_SEQ_GAMAN,				//���܂�
	SUB_SEQ_WARUAGAKI,			//��邠����
	SUB_SEQ_TEXTURE,			//�e�N�X�`��
	SUB_SEQ_JIKOSAISEI,			//������������
	SUB_SEQ_HIKARINOKABE,		//�Ђ���̂���
	SUB_SEQ_RIHUREKUTAA,		//���t���N�^�[
	SUB_SEQ_SIROIKIRI,			//���낢����
	SUB_SEQ_KIAIDAME,			//����������
	SUB_SEQ_MONOMANE,			//���̂܂�
	SUB_SEQ_YADORIGI,			//��ǂ肬�̂���
	SUB_SEQ_KANASIBARI,			//���Ȃ��΂�
	SUB_SEQ_ENCORE,				//�A���R�[��
	SUB_SEQ_ITAMIWAKE,			//�����݂킯
	SUB_SEQ_TEXTURE2,			//�e�N�X�`���Q
	SUB_SEQ_LOCKON,				//���b�N�I��
	SUB_SEQ_SKETCH,				//�X�P�b�`
	SUB_SEQ_FEINT,				//�t�F�C���g
	SUB_SEQ_MICHIDURE,			//�݂��Â�
	SUB_SEQ_URAMI,				//�����
	SUB_SEQ_GUARD,				//�܂���A�݂���A���炦��Ȃ�
	SUB_SEQ_IYASINOSUZU,		//���₵�̂���
	SUB_SEQ_MIGAWARI,			//�݂����
	SUB_SEQ_HUKITOBASI,			//�ӂ��Ƃ΂�
	SUB_SEQ_HENSIN,				//�ւ񂵂�
	SUB_SEQ_CHIISAKUNARU,		//���������Ȃ�
	SUB_SEQ_NORMAL_NOROI,		//�̂낢�i�m�[�}���j
	SUB_SEQ_GHOST_NOROI,		//�̂낢�i�S�[�X�g�j
	SUB_SEQ_ADD_MESSAGE_WORK,	//���b�Z�[�W�\��
	SUB_SEQ_MIYABURU,			//�݂�Ԃ�
	SUB_SEQ_HOROBINOUTA,		//�ق�т̂���
	SUB_SEQ_TENKOU,				//�V��n
	SUB_SEQ_IBARU,				//���΂�
	SUB_SEQ_MEROMERO,			//��������
	SUB_SEQ_SHINPI,				//����҂̂܂���
	SUB_SEQ_PRESENT,			//�v���[���g
	SUB_SEQ_MAGNITUDE,			//�}�O�j�`���[�h
	SUB_SEQ_BATONTOUCH,			//�o�g���^�b�`
	SUB_SEQ_HARADAIKO,			//�͂炾����
	SUB_SEQ_TELEPORT,			//�e���|�[�g
	SUB_SEQ_HUKURODATAKI,		//�ӂ��낾����
	SUB_SEQ_TAKUWAERU,			//�����킦��
	SUB_SEQ_NOMIKOMU,			//�݂̂���
	SUB_SEQ_ICHAMON,			//���������
	SUB_SEQ_ODATERU,			//�����Ă�
	SUB_SEQ_OKIMIYAGE,			//�����݂₰
	SUB_SEQ_JUUDEN,				//���イ�ł�
	SUB_SEQ_CHOUHATSU,			//���傤�͂�
	SUB_SEQ_TRICK,				//�g���b�N
	SUB_SEQ_NARIKIRI,			//�Ȃ肫��
	SUB_SEQ_KAWARAWARI,			//�������
	SUB_SEQ_AKUBI,				//������
	SUB_SEQ_SKILLSWAP,			//�X�L���X���b�v
	SUB_SEQ_REFRESH,			//���t���b�V��
	SUB_SEQ_HANEYASUME,			//�͂˂₷��
	SUB_SEQ_NO_NEMURI,			//�߂��܂��r���^
	SUB_SEQ_JUURYOKU,			//���イ��傭
	SUB_SEQ_MIRACLE_EYE,		//�~���N���A�C
	SUB_SEQ_IYASINONEGAI,		//���₵�̂˂���
	SUB_SEQ_OIKAZE,				//��������
	SUB_SEQ_INFIGHT,			//�C���t�@�C�g
	SUB_SEQ_POWER_TRICK,		//�p���[�g���b�N
	SUB_SEQ_IEKI,				//������
	SUB_SEQ_OMAZINAI,			//���܂��Ȃ�
	SUB_SEQ_POWER_SWAP,			//�p���[�X���b�v
	SUB_SEQ_GUARD_SWAP,			//�K�[�h�X���b�v
	SUB_SEQ_NAYAMINOTANE,		//�Ȃ�݂̂���
	SUB_SEQ_HEART_SWAP,			//�n�[�g�X���b�v
	SUB_SEQ_HEAT_ATTACK,		//�q�[�g�A�^�b�N
	SUB_SEQ_KIRIHARAI,			//����͂炢
	SUB_SEQ_HEALBLOCK,			//�q�[���u���b�N
	SUB_SEQ_TONBOGAERI,			//�Ƃ�ڂ�����
	SUB_SEQ_SHUTOUT,			//�V���b�g�A�E�g
	SUB_SEQ_TSUIBAMU,			//���΂�
	SUB_SEQ_NAGETSUKERU,		//�Ȃ�����
	SUB_SEQ_VOLT,				//�{���e�b�J�[
	SUB_SEQ_HANEKAERI3,			//�͂˂�����n�̋Z(1/2)
	SUB_SEQ_YAKEDO_HIRUMU,		//�₯�ǁ{�Ђ�ނ̒ǉ�����
	SUB_SEQ_KOORI_HIRUMU,		//������{�Ђ�ނ̒ǉ�����
	SUB_SEQ_MAHI_HIRUMU,		//�܂Ё{�Ђ�ނ̒ǉ�����
	SUB_SEQ_OSYABERI,			//������ׂ�̒ǉ�����
	SUB_SEQ_MIKADUKINOMAI,		//�݂��Â��̂܂��ǉ�����
	SUB_SEQ_SURIKOMI,			//���肱�ݒǉ�����
};

//============================================================================================
/**
 *	�ǉ����ʂ����邽�߂̃p�����[�^���Z�b�g
 *
 * @param[in]	sp		�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	type	�ǉ����ʂ̃^�C�v
 * @param[in]	flag	�ǉ����ʂ̎��
 *
 * @retval	�ǉ����ʓ��������V�[�P���X�i���o�[
 */
//============================================================================================
static	int		ST_ServerAddStatusParamSet(SERVER_PARAM *sp,int type,u32 flag)
{
	sp->tsuika_type=type;
	sp->tsuika_para=flag&ADD_STATUS_MASK;
	sp->tsuika_flag=flag&(ADD_STATUS_MASK^0xffffffff);

	if(flag&ADD_STATUS_ATTACK){
		sp->tsuika_client=sp->attack_client;
	}
	else if(flag&ADD_STATUS_DEFENCE){
		sp->tsuika_client=sp->defence_client;
	}
	else if((flag&ADD_STATUS_WAZAKOUKA)||(flag&ADD_STATUS_WAZAKOUKA_NOHIT)){
		sp->tsuika_client=0;
	}
	else{
		OS_TPrintf("ST_ServerAddStausParamSet:�����ɂ���̂͂�������->%08x\n",flag);
	}

	GF_ASSERT_MSG(NELEMS(AddStatusSeqNoTable)>(flag&ADD_STATUS_MASK),"���݂��Ȃ�SUB_SEQ_NO�ł�");

	return AddStatusSeqNoTable[flag&ADD_STATUS_MASK];
}

//============================================================================================
/**
 *	�|�P�����ƋZ�̃^�C�v�̑����Ńt���O���Z�b�g
 *
 * @param[in]	client_no	�Z���J��o��ClientNo
 * @param[in]	power		�����������З�
 * @param[in]	damage		�~�ς���Ă���_���[�W
 * @param[in]	waza_damage	�Z�̈З�
 * @param[out]	flag		�t���O���Z�b�g���郏�[�N
 */
//============================================================================================
static	int	ST_TypeCheckCalc(SERVER_PARAM *sp,int client_no,int power,int damage,int waza_damage,u32 *flag)
{
	//�^�C�v�ɂ��␳�v�Z
	if(((sp->server_status_flag&SERVER_STATUS_FLAG_TYPE_FLAT)==0)&&
	   ((sp->server_status_flag&SERVER_STATUS_FLAG_TYPE_NONE)==0)&&
		(damage)){
		damage=ST_ServerDamageDiv(damage*power,10);
	}
	switch(power){
	case KOUKANAI:
		flag[0]|=WAZA_STATUS_FLAG_KOUKANAI;
		flag[0]&=WAZA_STATUS_FLAG_IMAHITOTSU_OFF;
		flag[0]&=WAZA_STATUS_FLAG_BATSUGUN_OFF;
		break;
	case IMAHITOTSU:
//		if(((waza_damage)&&(flag[0]&WAZA_STATUS_FLAG_HAZURE)==0)){
		if(waza_damage){
			if(flag[0]&WAZA_STATUS_FLAG_BATSUGUN){
				flag[0]&=WAZA_STATUS_FLAG_BATSUGUN_OFF;
			}
			else{
				flag[0]|=WAZA_STATUS_FLAG_IMAHITOTSU;
			}
		}
		break;
	case BATSUGUN:
//		if((waza_damage)&&((flag[0]&WAZA_STATUS_FLAG_HAZURE)==0)){
		if(waza_damage){
			if(flag[0]&WAZA_STATUS_FLAG_IMAHITOTSU){
				flag[0]&=WAZA_STATUS_FLAG_IMAHITOTSU_OFF;
			}
			else{
				flag[0]|=WAZA_STATUS_FLAG_BATSUGUN;
			}
		}
		break;
	}

	return damage;
}

//============================================================================================
/**
 *	���ߋZ����������^�[���Ȃ̂��`�F�b�N�i���ߋZ�ȊO�͋����I�ɔ��������j
 *
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 *
 * @retval	TRUE�F�����@FALSE:���߂�^�[��
 */
//============================================================================================
static BOOL	ST_TameWazaTurnCheck(SERVER_PARAM *sp,int waza_no)
{
	switch(sp->AIWT.wtd[waza_no].battleeffect){
	case 26:	//���܂�
	case 39:	//���܂�����
	case 75:	//�S�b�h�o�[�h
	case 145:	//���P�b�g���˂�
	case 151:	//�\�[���[�r�[��
	case 155:	//������Ƃ�
	case 255:	//�_�C�r���O
	case 256:	//���Ȃ��ق�
	case 263:	//�Ƃт͂˂�
	case 273:	//�V���h�[�_�C�u
		return (sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER);
		break;
	}

	return TRUE;
}

//============================================================================================
/**
 *	�|�P�����i���o�[�Ɠ������`�F�b�N���Ď擾���ׂ��^�C�v��Ԃ�
 *
 * @param[in]	sp		�T�[�o���[�N�\����
 * @param[in]	client	�擾����ClientNo
 * @param[in]	id		�擾����^�C�v�iID_PSP_type1 or ID_PSP_type2�j
 *
 * @retval	TRUE�F�����@FALSE:���߂�^�[��
 */
//============================================================================================
static	u8	 ST_ServerTypeGet(SERVER_PARAM *sp,int client,int id)
{
	u8	type;

	if(id==ID_PSP_type1){
		type=sp->psp[client].type1;
	}
	else if(id==ID_PSP_type2){
		type=sp->psp[client].type2;
	}
	else{
		GF_ASSERT(0);
	}
	
	//�A�E�X�������}���`�^�C�v�������Ă���Ƃ��́A��������ɂ���ă^�C�v��ς���
	if((sp->psp[client].monsno==MONSNO_AUSU)&&
	   (sp->psp[client].speabino==TOKUSYU_MARUTITAIPU)){
//		switch(ItemParamGet(sp->psp[client].item,ITEM_PRM_EQUIP,HEAPID_BATTLE)){
		switch(ST_ItemParamGet(sp,sp->psp[client].item,ITEM_PRM_EQUIP)){
		case SOUBI_AUSUHONOOUP:
			type=FIRE_TYPE;
			break;
		case SOUBI_AUSUMIZUUP:
			type=WATER_TYPE;
			break;
		case SOUBI_AUSUDENKIUP:
			type=ELECTRIC_TYPE;
			break;
		case SOUBI_AUSUKUSAUP:
			type=KUSA_TYPE;
			break;
		case SOUBI_AUSUKOORIUP:
			type=KOORI_TYPE;
			break;
		case SOUBI_AUSUKAKUTOUUP:
			type=BATTLE_TYPE;
			break;
		case SOUBI_AUSUDOKUBARIUP:
			type=POISON_TYPE;
			break;
		case SOUBI_AUSUZIMENUP:
			type=JIMEN_TYPE;
			break;
		case SOUBI_AUSUTORIUP:
			type=HIKOU_TYPE;
			break;
		case SOUBI_AUSUESUPAAUP:
			type=SP_TYPE;
			break;
		case SOUBI_AUSUMUSIIRYOKUUP:
			type=MUSHI_TYPE;
			break;
		case SOUBI_AUSUIWAUP:
			type=IWA_TYPE;
			break;
		case SOUBI_AUSUGOOSUTOUP:	
			type=GHOST_TYPE;
			break;
		case SOUBI_AUSUDORAGONUP:	
			type=DRAGON_TYPE;
			break;
		case SOUBI_AUSUAKUUP:	
			type=AKU_TYPE;
			break;
		case SOUBI_AUSUHAGANEIRYOKUUP:	
			type=METAL_TYPE;
			break;
		default:
			type=NORMAL_TYPE;
			break;
		}
	}

	return type;
}

//============================================================================================
/**
 *	�Z�i���o�[�X�g�b�N�p���[�N�̏�����
 *
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	�N���A����ClientNo
 */
//============================================================================================
static	void	WazaNoStockClear(SERVER_PARAM *sp,u8 client_no)
{
	int	i;

	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		sp->AIWT.AI_DEFENCE_USE_WAZA[client_no][i]=0;
	}
}

//=========================================================================
/**
 *	AI�p�������[�N���N���A
 *
 * @param[in]	sp			�T�[�o�V�X�e���\����
 * @param[in]	client_no	�N���A����ClientNo
 */
//=========================================================================
static	void	TokusyuNoClear(SERVER_PARAM *sp,u8 client_no)
{
	sp->AIWT.AI_TOKUSYUNO[client_no]=0;
}

//=========================================================================
/**
 *	AI�p�����A�C�e�����[�N���N���A
 *
 * @param[in]	sp			�T�[�o�V�X�e���\����
 * @param[in]	client_no	�N���A����ClientNo
 */
//=========================================================================
static	void	SoubiItemClear(SERVER_PARAM *sp,u8 client_no)
{
	sp->AIWT.AI_SOUBIITEM[client_no]=0;
}

//=========================================================================
/**
 *	�g���[�X�ł���������`�F�b�N���Ĕ����ł��邩��Ԃ�
 *
 * @param[in]	sp		�T�[�o�V�X�e���\����
 * @param[in]	def1	�`�F�b�N�Ώ�ClientNo
 * @param[in]	def2	�`�F�b�N�Ώ�ClientNo
 *
 * @retval	�����Ώ�ClientNo
 */
//=========================================================================
static	int	ST_ServerTraceClientNoGet(SERVER_PARAM *sp,int def1,int def2)
{
	int	ret=NONE_CLIENT_NO;

	if((sp->psp[def1].speabino!=TOKUSYU_TENKIYA)&&
	   (sp->psp[def1].speabino!=TOKUSYU_TOREESU)&&
	   (sp->psp[def1].speabino!=TOKUSYU_MARUTITAIPU)&&
	   (sp->psp[def2].speabino!=TOKUSYU_TENKIYA)&&
	   (sp->psp[def2].speabino!=TOKUSYU_TOREESU)&&
	   (sp->psp[def2].speabino!=TOKUSYU_MARUTITAIPU)){
		if(gf_rand()&1){
			ret=def2;
		}
		else{
			ret=def1;
		}
	}
	else if((sp->psp[def1].speabino!=TOKUSYU_TENKIYA)&&
	 	    (sp->psp[def1].speabino!=TOKUSYU_TOREESU)&&
	 	    (sp->psp[def1].speabino!=TOKUSYU_MARUTITAIPU)){
		ret=def1;
	}
	else if((sp->psp[def2].speabino!=TOKUSYU_TENKIYA)&&
	 	    (sp->psp[def2].speabino!=TOKUSYU_TOREESU)&&
	 	    (sp->psp[def2].speabino!=TOKUSYU_MARUTITAIPU)){
		ret=def2;
	}
	return ret;
}

//============================================================================================
/**
 *	������悿�ŏ��O����퓬���ʃi���o�[�e�[�u��
 */
//============================================================================================
static	const	u16	KikenyochiNGWazaSeqTable[]={
	41,
	87,
	88,
	89,
	144,
	227,
};

//============================================================================================
/**
 *	������悿�ŏ��O����퓬���ʃi���o�[�𒲂ׂ�
 *
 * @param[in]	sp			�T�[�o�p�����[�^�̍\���̃|�C���^
 * @param[in]	waza_no		�`�F�b�N����Z�i���o�[
 *
 * @retval	FALSE:���O���Ȃ� TRUE:���O����
 */
//============================================================================================
static	BOOL	ST_ServerKikenyochiWazaSeqCheck(SERVER_PARAM *sp,int waza_no)
{
	int	i;

	for(i=0;i<NELEMS(KikenyochiNGWazaSeqTable);i++){
		if(KikenyochiNGWazaSeqTable[i]==sp->AIWT.wtd[waza_no].battleeffect){
			return TRUE;
		}
	}
	return FALSE;
}

#if B1366_060815_FIX
//============================================================================================
/**
 * ����ȋZ�̃^�C�v���擾
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\���̂̃|�C���^
 * @param[in]	sp			�T�[�o�V�X�e�����[�N�\���̂̃|�C���^
 * @param[in]	client_no	�Z���g�p����ClientNo
 * @param[in]	waza_no		�^�C�v���擾����Z�i���o�[
 *
 * @retval	�Z�^�C�v
 */
//============================================================================================
static	int		ST_AIWazaTypeGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no)
{
	int	type;

	switch(waza_no){
	case WAZANO_SIZENNOMEGUMI:
		type=ST_ServerShizennomegumiTypeGet(sp,client_no);
		break;
	case WAZANO_SABAKINOTUBUTE:
		switch(ST_ServerSoubiEqpGet(sp,client_no)){
		case SOUBI_AUSUKAKUTOUUP:
			type=BATTLE_TYPE;
			break;
		case SOUBI_AUSUTORIUP:
			type=HIKOU_TYPE;
			break;
		case SOUBI_AUSUDOKUBARIUP:
			type=POISON_TYPE;
			break;
		case SOUBI_AUSUZIMENUP:
			type=JIMEN_TYPE;
			break;
		case SOUBI_AUSUIWAUP:
			type=IWA_TYPE;
			break;
		case SOUBI_AUSUMUSIIRYOKUUP:
			type=MUSHI_TYPE;
			break;
		case SOUBI_AUSUGOOSUTOUP:
			type=GHOST_TYPE;
			break;
		case SOUBI_AUSUHAGANEIRYOKUUP:
			type=METAL_TYPE;
			break;
		case SOUBI_AUSUHONOOUP:
			type=FIRE_TYPE;
			break;
		case SOUBI_AUSUMIZUUP:
			type=WATER_TYPE;
			break;
		case SOUBI_AUSUKUSAUP:
			type=KUSA_TYPE;
			break;
		case SOUBI_AUSUDENKIUP:
			type=ELECTRIC_TYPE;
			break;
		case SOUBI_AUSUESUPAAUP:
			type=SP_TYPE;
			break;
		case SOUBI_AUSUKOORIUP:
			type=KOORI_TYPE;
			break;
		case SOUBI_AUSUDORAGONUP:
			type=DRAGON_TYPE;
			break;
		case SOUBI_AUSUAKUUP:
			type=AKU_TYPE;
			break;
		default:
			type=0;
			break;
		}
		break;
	case WAZANO_MEZAMERUPAWAA:
		type=	((sp->psp[client_no].hp_rnd&1)		>>0)|
				((sp->psp[client_no].pow_rnd&1)		<<1)|
				((sp->psp[client_no].def_rnd&1)		<<2)|
				((sp->psp[client_no].agi_rnd&1)		<<3)|
				((sp->psp[client_no].spepow_rnd&1)	<<4)|
				((sp->psp[client_no].spedef_rnd&1)	<<5);

		type=(type*15/63)+1;

		if(type>=HATE_TYPE){
			type++;
		}
		break;
	case WAZANO_WHEZAABOORU:
		if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
		   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
			if(sp->field_condition&FIELD_CONDITION_TENKI){
				if(sp->field_condition&FIELD_CONDITION_AME_ALL){
					type=WATER_TYPE;
				}
				if(sp->field_condition&FIELD_CONDITION_SUNAARASHI_ALL){
					type=IWA_TYPE;
				}
				if(sp->field_condition&FIELD_CONDITION_HARE_ALL){
					type=FIRE_TYPE;
				}
				if(sp->field_condition&FIELD_CONDITION_ARARE_ALL){
					type=KOORI_TYPE;
				}
			}
		}
		break;
	default:
		type=0;
		break;
	}

	return type;
}
#endif //B1366_060815_FIX

