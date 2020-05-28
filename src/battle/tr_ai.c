
//============================================================================================
/**
 * @file	tr_ai.c
 * @bfief	�g���[�i�[AI�v���O�����i�A�h�o���X�̂��̂��ڐA�j
 * @author	HisashiSogabe
 * @date	06.04.25
 */
//============================================================================================

#include "common.h"

#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "battle/server_tool.h"
#include "battle/tr_ai.h"
#include "battle/tokusyu_def.h"
#include "battle/wazano_def.h"

#include "itemtool/item.h"

#include "poketool/monsno.h"
#include "poketool/waza_tool.h"

#include "tr_ai_def.h"
#include "tr_ai/tr_ai.dat"

#include "fight_def.h"		///<BattleWork�ւ̈ˑ��x�������\�[�X�Ȃ̂ŁA����
#include "server_def.h"		///<ServerParam�ւ̈ˑ��x�������\�[�X�Ȃ̂ŁA����

//MAKE�̈ˑ��֌W�Ɋ܂߂邽�߂�Include�i�{���͕K�v�Ȃ��j
#include "battle/tr_ai/tr_ai_seq.naix"

#ifdef DEBUG_ONLY_FOR_sogabe
//#define DEBUG_PRINT_AI		///<�퓬�p�f�o�b�O�v�����g��L���ɂ���
#endif

#ifdef DEBUG_ONLY_FOR_shimoyamada
//#define DEBUG_PRINT_AI		///<�퓬�p�f�o�b�O�v�����g��L���ɂ���
#endif

#define	WAZA_AI_CALC_MAX	(50)	///��x��AI�v�Z�ł���MAX�l

extern	u32	TrainerAITbl[];

//-----------------------------------------------------------------------------
//					�v���g�^�C�v�錾
//-----------------------------------------------------------------------------

void	WazaAIInit(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 point_bit);
void	WazaAIInit2(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 point_bit);
u8		WazaAIMain(BATTLE_WORK *bw,u8 client_no);
void	WazaNoStockClear(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no);
void	TokusyuNoSet(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 speabino);
void	TokusyuNoClear(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no);
void	SoubiItemSet(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u16 item_no);
void	SoubiItemClear(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no);

static	u8	WazaAIMainSingle(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	u8	WazaAIMainDouble(BATTLE_WORK *bw,SERVER_PARAM *sp);

static	void	WazaAISequence(BATTLE_WORK *bw,SERVER_PARAM *sp);

static	void	WazaNoStock(BATTLE_WORK *bw,SERVER_PARAM *sp);

static	void	AI_IF_RND_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_RND_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_RND_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_RND_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_INCDEC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HP_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HP_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HP_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_HP_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_COND(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_COND(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_COND2(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_COND2(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_WAZAKOUKA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_WAZAKOUKA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_SIDE_CONDITION(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_SIDE_CONDITION(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_BIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_BIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_WAZANO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_WAZANO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_TABLE_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_TABLE_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HAVE_DAMAGE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_HAVE_DAMAGE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_TURN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_IRYOKU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_COMP_POWER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_LAST_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_WAZA_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_WAZA_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_FIRST(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_FIRST(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_BENCH_COUNT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WAZANO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WAZASEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_TOKUSEI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_AISYOU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WAZA_AISYOU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_BENCH_COND(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_BENCH_COND(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WEATHER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_WAZA_SEQNO_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_WAZA_SEQNO_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_PARA_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_PARA_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_PARA_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_PARA_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_WAZA_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_WAZA_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HAVE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_HAVE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HAVE_WAZA_SEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_HAVE_WAZA_SEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_POKE_CHECK_STATE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_WAZA_CHECK_STATE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_ESCAPE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_SAFARI_ESCAPE_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_SAFARI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_SOUBIITEM(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_POKESEX(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_NEKODAMASI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_TAKUWAERU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_FIGHT_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_RECYCLE_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WORKWAZA_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WORKWAZA_POW(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WORKWAZA_SEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_MAMORU_COUNT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_GOSUB(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_AIEND(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_LEVEL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_CHOUHATSU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_CHOUHATSU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_MIKATA_ATTACK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_HAVE_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_HAVE_TOKUSEI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_ALREADY_MORAIBI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HAVE_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_FIELD_CONDITION_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_SIDE_CONDITION_COUNT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_BENCH_HPDEC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_BENCH_PPDEC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_NAGETSUKERU_IRYOKU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_PP_REMAIN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_TOTTEOKI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_WAZA_KIND(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_LAST_WAZA_KIND(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_AGI_RANK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_SLOWSTART_TURN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_BENCH_DAMAGE_MAX(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HAVE_BATSUGUN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_LAST_WAZA_DAMAGE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_STATUS_UP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_CHECK_STATUS_DIFF(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_CHECK_STATUS_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_CHECK_STATUS_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_CHECK_STATUS_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_COMP_POWER_WITH_PARTNER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IF_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_IFN_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	AI_GET_TOKUSEI(BATTLE_WORK *bw,SERVER_PARAM *sp);

static	void	AIPushAdrsSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int adrs);
static	BOOL	AIPopAdrsAct(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	int		AISeqDataRead(SERVER_PARAM *sp);
static	int		AISeqDataReadOfs(SERVER_PARAM *sp,int ofs);
static	void	AISeqInc(SERVER_PARAM *sp,int cnt);
static	u8		SideToClientNo(SERVER_PARAM *sp,u8 side);
static	s32		AICompPowerCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 *waza,s32 *damage,u16 item_no,u8 *power_rnd,
								int tokusei,int shutout,int loss_flag);
static	s32		AIWazaDamageCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza,u16 item_no,u8 *power_rnd,
								 int client_no,int tokusei,int shutout,u8 loss);
static	int		AIWazaTypeGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
static	int		AIWazaTypeGetPP(BATTLE_WORK *bw,SERVER_PARAM *sp,POKEMON_PARAM *pp,int waza_no);

static	void	AI_IF_CHECK_STATUS_GET(SERVER_PARAM *sp,int client_no,int *src,int *dest,int flag);


static	BOOL	ClientAIHorobinoutaCheck(SERVER_PARAM *sp,int client_no);
static	BOOL	ClientAIHusiginamamoriCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
static	BOOL	ClientAIKoukanaiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
static	BOOL	ClientAIBatsugunCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,u8 chkflag);
static	BOOL	ClientAIHPRecoverTokusyuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
static	BOOL	ClientAIWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,u32 wazakouka,u8 kakuritu);
static	BOOL	ClientAIShizenkaifukuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
static	BOOL	ClientAIStatusUpCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
static	BOOL	ClientAIPokeReshuffleAI(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
int				ClientAICommandSelectAI(BATTLE_WORK *bw,int client_no);
int				ClientAIPokeSelectAI(BATTLE_WORK *bw,int client_no);
int				ClientAIReshuffleSelMonsNoGet(BATTLE_WORK *bw,int client_no);
BOOL			ClientAIItemUseAI(BATTLE_WORK *bw,int client_no);

//-----------------------------------------------------------------------------
//		AI���߃e�[�u��
//-----------------------------------------------------------------------------
static	const aiFunc	AISequenceTbl[]={
	AI_IF_RND_UNDER,
	AI_IF_RND_OVER,
	AI_IF_RND_EQUAL,
	AI_IFN_RND_EQUAL,
	AI_INCDEC,
	AI_IF_HP_UNDER,
	AI_IF_HP_OVER,
	AI_IF_HP_EQUAL,
	AI_IFN_HP_EQUAL,
	AI_IF_COND,
	AI_IFN_COND,
	AI_IF_COND2,
	AI_IFN_COND2,
	AI_IF_WAZAKOUKA,
	AI_IFN_WAZAKOUKA,
	AI_IF_SIDE_CONDITION,
	AI_IFN_SIDE_CONDITION,
	AI_IF_UNDER,
	AI_IF_OVER,
	AI_IF_EQUAL,
	AI_IFN_EQUAL,
	AI_IF_BIT,
	AI_IFN_BIT,
	AI_IF_WAZANO,
	AI_IFN_WAZANO,
	AI_IF_TABLE_JUMP,
	AI_IFN_TABLE_JUMP,
	AI_IF_HAVE_DAMAGE_WAZA,
	AI_IFN_HAVE_DAMAGE_WAZA,
	AI_CHECK_TURN,
	AI_CHECK_TYPE,
	AI_CHECK_IRYOKU,
	AI_COMP_POWER,
	AI_CHECK_LAST_WAZA,
	AI_IF_WAZA_TYPE,
	AI_IFN_WAZA_TYPE,
	AI_IF_FIRST,
	AI_IFN_FIRST,
	AI_CHECK_BENCH_COUNT,
	AI_CHECK_WAZANO,
	AI_CHECK_WAZASEQNO,
	AI_CHECK_TOKUSEI,
	AI_CHECK_AISYOU,
	AI_CHECK_WAZA_AISYOU,
	AI_IF_BENCH_COND,
	AI_IFN_BENCH_COND,
	AI_CHECK_WEATHER,
	AI_IF_WAZA_SEQNO_JUMP,
	AI_IFN_WAZA_SEQNO_JUMP,
	AI_IF_PARA_UNDER,
	AI_IF_PARA_OVER,
	AI_IF_PARA_EQUAL,
	AI_IFN_PARA_EQUAL,
	AI_IF_WAZA_HINSHI,
	AI_IFN_WAZA_HINSHI,
	AI_IF_HAVE_WAZA,
	AI_IFN_HAVE_WAZA,
	AI_IF_HAVE_WAZA_SEQNO,
	AI_IFN_HAVE_WAZA_SEQNO,
	AI_IF_POKE_CHECK_STATE,
	AI_IF_WAZA_CHECK_STATE,
	AI_ESCAPE,
	AI_SAFARI_ESCAPE_JUMP,
	AI_SAFARI,
	AI_CHECK_ITEM,
	AI_CHECK_SOUBIITEM,
	AI_CHECK_POKESEX,
	AI_CHECK_NEKODAMASI,
	AI_CHECK_TAKUWAERU,
	AI_CHECK_FIGHT_TYPE,
	AI_CHECK_RECYCLE_ITEM,
	AI_CHECK_WORKWAZA_TYPE,
	AI_CHECK_WORKWAZA_POW,
	AI_CHECK_WORKWAZA_SEQNO,
	AI_CHECK_MAMORU_COUNT,
	AI_GOSUB,
	AI_JUMP,
	AI_AIEND,
	AI_IF_LEVEL,
	AI_IF_CHOUHATSU,
	AI_IFN_CHOUHATSU,
	AI_IF_MIKATA_ATTACK,
	AI_HAVE_TYPE,
	AI_HAVE_TOKUSEI,
	AI_IF_ALREADY_MORAIBI,
	AI_IF_HAVE_ITEM,
	AI_FIELD_CONDITION_CHECK,
	AI_CHECK_SIDE_CONDITION_COUNT,
	AI_IF_BENCH_HPDEC,
	AI_IF_BENCH_PPDEC,
	AI_CHECK_NAGETSUKERU_IRYOKU,
	AI_CHECK_PP_REMAIN,
	AI_IF_TOTTEOKI,
	AI_CHECK_WAZA_KIND,
	AI_CHECK_LAST_WAZA_KIND,
	AI_CHECK_AGI_RANK,
	AI_CHECK_SLOWSTART_TURN,
	AI_IF_BENCH_DAMAGE_MAX,
	AI_IF_HAVE_BATSUGUN,
	AI_IF_LAST_WAZA_DAMAGE_CHECK,
	AI_CHECK_STATUS_UP,
	AI_CHECK_STATUS_DIFF,
	AI_IF_CHECK_STATUS_UNDER,
	AI_IF_CHECK_STATUS_OVER,
	AI_IF_CHECK_STATUS_EQUAL,
	AI_COMP_POWER_WITH_PARTNER,
	AI_IF_HINSHI,
	AI_IFN_HINSHI,
	AI_GET_TOKUSEI,
};

//-------------------- AI�V�[�P���X�i���o�[�錾 ------------------------

enum{
	AI_SEQ_THINK_INIT=0,
	AI_SEQ_THINK,
	AI_SEQ_END,
};

//============================================================================================
/**
 *	AI�p���[�N�̏������i�ŏ���1�񂾂����������郏�[�N���w��j
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	AI���N������ClientNo
 * @param[in]	point_bit	�J��o���|�C���g�̏����l���ǂ����邩�t���O
 */
//============================================================================================
void	WazaAIInit(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 point_bit)
{
	int	i;
	int	cli;

	MI_CpuClear32(&sp->AIWT,sizeof(AI_WORK_TBL));

	if((bw->fight_type&FIGHT_TYPE_TRAINER)&&((bw->fight_type&FIGHT_TYPE_NO_ITEM_AI)==0)){
		for(cli=0;cli<CLIENT_MAX;cli++){
			if(cli&1){
				for(i=0;i<4;i++){
					if(bw->trainer_data[cli].use_item[i]!=0){
						sp->AIWT.AI_HAVEITEM[cli>>1][sp->AIWT.AI_ITEMCNT[cli>>1]]=bw->trainer_data[cli].use_item[i];
						sp->AIWT.AI_ITEMCNT[cli>>1]++;
					}
				}
			}
		}
	}
	//AI�V�[�P���X�v���O���������[�h
//	sp->AISeqWork=ArchiveDataLoadMalloc(ARC_TR_AI,0,HEAPID_BATTLE);
	sp->AISeqWork=TrainerAITbl;
}

//============================================================================================
/**
 *	AI�p���[�N�̏�����
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	AI���N������ClientNo
 * @param[in]	point_bit	�J��o���|�C���g�̏����l���ǂ����邩�t���O
 */
//============================================================================================
void	WazaAIInit2(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 point_bit)
{
	int	i;
	u8	wazabit;
	u8	*adr;

	adr=(u8 *)&sp->AIWT;

	for(i=0;i<XtOffset(AI_WORK_TBL *,AI_DEFENCE_USE_WAZA);i++){
		adr[i]=0;
	}

	for(i=0;i<4;i++){
		if(point_bit&1){
			sp->AIWT.AI_WAZAPOINT[i]=100;
		}
		else{
			sp->AIWT.AI_WAZAPOINT[i]=0;
		}
		point_bit=point_bit>>1;
	}

	wazabit=ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_ALL);

	for(i=0;i<4;i++){
		if(wazabit&No2Bit(i)){
			sp->AIWT.AI_WAZAPOINT[i]=0;
		}
		sp->AIWT.AI_DAMAGELOSS[i]=100-(gf_rand()%16);
	}

	sp->AIWT.PushAdrsCnt=0;

	//�o�g���^���[�͍ŋ��ɂ���
	if(bw->fight_type&FIGHT_TYPE_TOWER){
		sp->AIWT.AI_THINK_BIT=0x07;
	}
	//�ړ��|�P�����́A�ړ�AI�̂�
	else if(bw->fight_type&FIGHT_TYPE_MOVE){
		sp->AIWT.AI_THINK_BIT=AI_THINK_BIT_MV_POKE;
	}
	//�ŏ��̐퓬�́A�K�C�h�o�g��AI�̂�
	else if(bw->battle_status_flag&BATTLE_STATUS_FLAG_FIRST_BATTLE){
		sp->AIWT.AI_THINK_BIT=AI_THINK_BIT_GUIDE;
	}
	else{
		sp->AIWT.AI_THINK_BIT=bw->trainer_data[client_no].aibit;
	}

#ifdef PM_DEBUG
	//�f�o�b�O�̃I�[�g�o�g���͍ŋ��ɂ���
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		sp->AIWT.AI_THINK_BIT=0x07;
	}
#endif PM_DEBUG

	if(bw->fight_type&FIGHT_TYPE_2vs2){
		sp->AIWT.AI_THINK_BIT|=AI_THINK_BIT_DOUBLE;
	}
}

//============================================================================================
/**
 *	AI���C���V�[�P���X
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 * @param[in]	client_no	AI���N������ClientNo
 *
 * @retval	�J��o���Z�̃|�W�V����
 */
//============================================================================================
u8		WazaAIMain(BATTLE_WORK *bw,u8 client_no)
{
	u8	ret;
	SERVER_PARAM	*sp;

	sp=bw->server_param;

	//AI�v�Z���r������Ȃ���΁A������
	if((sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_CONTINUE)==0){
		sp->AIWT.AI_AttackClient=client_no;
		sp->AIWT.AI_DefenceClient=ST_ServerDirClientGet(bw,sp,client_no);

		WazaAIInit2(bw,sp,sp->AIWT.AI_AttackClient,0x0f);
	}

	if((bw->fight_type&FIGHT_TYPE_2vs2)==0){
		ret=WazaAIMainSingle(bw,sp);
	}
	else{
		ret=WazaAIMainDouble(bw,sp);
	}

	return ret;
}

//------------------------------------------------------------
//	�O�����J�֐��Q
//------------------------------------------------------------
//============================================================================================
/**
 *	AI�V�[�P���X�i�V���O���j
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static u8 WazaAIMainSingle(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u8	point[4];
	u8	poswork[4];
	u8	poscnt;
	u8	pos=0;
	u16 waza_no;

	WazaNoStock(bw,sp);

	while(sp->AIWT.AI_THINK_BIT){
		if(sp->AIWT.AI_THINK_BIT&1){
			if((sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_CONTINUE)==0){
				sp->AIWT.AI_SEQNO=AI_SEQ_THINK_INIT;
			}
			WazaAISequence(bw,sp);
		}
		sp->AIWT.AI_THINK_BIT=sp->AIWT.AI_THINK_BIT>>1;
		sp->AIWT.AI_THINK_NO++;
		sp->AIWT.AI_WAZAPOS=0;
	}
	if(sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_ESCAPE){
		pos=AI_ENEMY_ESCAPE;
	}
	else if(sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_SAFARI){
		pos=AI_ENEMY_SAFARI;
	}
	else{
		poscnt=1;
		point[0]=sp->AIWT.AI_WAZAPOINT[0];
		poswork[0]=0;
		for(i=1;i<4;i++){
			//�Z���Ȃ��Ƃ���́A����
			if(sp->psp[sp->AIWT.AI_AttackClient].waza[i]){
				if(point[0]==sp->AIWT.AI_WAZAPOINT[i]){
					point[poscnt]=sp->AIWT.AI_WAZAPOINT[i];
					poswork[poscnt++]=i;
				}
				if(point[0]<sp->AIWT.AI_WAZAPOINT[i]){
					poscnt=1;
					point[0]=sp->AIWT.AI_WAZAPOINT[i];
					poswork[0]=i;
				}
			}
		}
		pos=poswork[gf_rand()%poscnt];
	}

//#ifdef DEBUG_ONLY_FOR_shimoyamada
	OS_TPrintf("waza1:%d waza2:%d waza3:%d waza4:%d\n",
				sp->AIWT.AI_WAZAPOINT[0],
				sp->AIWT.AI_WAZAPOINT[1],
				sp->AIWT.AI_WAZAPOINT[2],
				sp->AIWT.AI_WAZAPOINT[3]);
//#endif

	sp->AIWT.AI_DirSelectClient[sp->AIWT.AI_AttackClient] = sp->AIWT.AI_DefenceClient;

	return pos;
}

//============================================================================================
/**
 *	AI�V�[�P���X�i�_�u���j
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static u8 WazaAIMainDouble(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client,	client_cnt, tb;
	s16	max_point[CLIENT_MAX];
	u8	client_wk[CLIENT_MAX];
	s8	pos[CLIENT_MAX];
	s16 point_max;
	u16	waza_no;
	s8	waza_pos;

	// �����ȊO�̑S�N���C�A���g�ɑ΂��ă`�F�b�N
	for(client = 0; client < CLIENT_MAX; client++){
		if(	(client == sp->AIWT.AI_AttackClient)
		||	(sp->psp[client].hp == 0)
		){
			pos[client] = -1;
			max_point[client] = -1;
			continue;
		}

		WazaAIInit2(bw,sp,sp->AIWT.AI_AttackClient,0x0f);

		sp->AIWT.AI_DefenceClient = client;

		if((client&1)!=(sp->AIWT.AI_AttackClient&1)){
			WazaNoStock(bw,sp);
		}

		sp->AIWT.AI_THINK_NO = 0;
		sp->AIWT.AI_WAZAPOS = 0;
		tb = sp->AIWT.AI_THINK_BIT;
		while(tb){
			if(tb & 1){
				if((sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_CONTINUE)==0){
					sp->AIWT.AI_SEQNO = AI_SEQ_THINK_INIT;
				}
				WazaAISequence(bw,sp);
			}
			tb >>= 1;
			sp->AIWT.AI_THINK_NO++;
			sp->AIWT.AI_WAZAPOS = 0;
		}

		if(sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_ESCAPE){
			pos[client] = AI_ENEMY_ESCAPE;
		}else if(sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_SAFARI){
			pos[client] = AI_ENEMY_SAFARI;
		}else{
			u8 point_wk[4];
			u8 pos_wk[4];
			int poscnt, p;

			point_wk[0] = sp->AIWT.AI_WAZAPOINT[0];
			pos_wk[0] = 0;
			poscnt = 1;

			for(p = 1; p < 4; p++){
				//�Z���Ȃ��Ƃ���́A����
				if(sp->psp[sp->AIWT.AI_AttackClient].waza[p]){
					if(point_wk[0] == sp->AIWT.AI_WAZAPOINT[p]){
						point_wk[poscnt] = sp->AIWT.AI_WAZAPOINT[p];
						pos_wk[poscnt] = p;
						poscnt++;
					}
					if(point_wk[0] < sp->AIWT.AI_WAZAPOINT[p]){
						point_wk[0] = sp->AIWT.AI_WAZAPOINT[p];
						pos_wk[0] = p;
						poscnt = 1;
					}
				}
			}
			pos[client] = pos_wk[gf_rand()%poscnt];
			max_point[client] = point_wk[0];

			// 100�������Ă��閡���U���͍s��Ȃ�
			if(client == (sp->AIWT.AI_AttackClient^2)){
				if(max_point[client] < 100){
					max_point[client] = -1;
				}
			}
		}
#ifdef DEBUG_ONLY_FOR_shimoyamada
		OS_TPrintf("attack:%d defence:%d\n",sp->AIWT.AI_AttackClient,client);
		OS_TPrintf("waza1:%d waza2:%d waza3:%d waza4:%d\n",
					sp->AIWT.AI_WAZAPOINT[0],
					sp->AIWT.AI_WAZAPOINT[1],
					sp->AIWT.AI_WAZAPOINT[2],
					sp->AIWT.AI_WAZAPOINT[3]);
#endif
	}

	point_max = max_point[0];
	client_wk[0] = 0;
	client_cnt = 1;
	for(client = 1; client < CLIENT_MAX; client++){
		if(point_max == max_point[client]){
			client_wk[client_cnt++] = client;
		}
		if(point_max < max_point[client]){
			point_max = max_point[client];
			client_wk[0] = client;
			client_cnt = 1;
		}
	}

	sp->AIWT.AI_DirSelectClient[sp->AIWT.AI_AttackClient] = client_wk[ (gf_rand() % client_cnt) ];
	waza_pos=pos[sp->AIWT.AI_DirSelectClient[sp->AIWT.AI_AttackClient]];
	waza_no=sp->psp[sp->AIWT.AI_AttackClient].waza[waza_pos];

	if(sp->AIWT.wtd[waza_no].attackrange==RANGE_TUBOWOTUKU){
		if(BattleWorkMineEnemyCheck(bw,sp->AIWT.AI_DirSelectClient[sp->AIWT.AI_AttackClient])==0){
			sp->AIWT.AI_DirSelectClient[sp->AIWT.AI_AttackClient] = sp->AIWT.AI_AttackClient;
		}
	}

	return waza_pos;

//	AI_ENEMY_RESHUFFLE
//	DefenceClient�ɓ���ւ������|�P������pos�����Ă���
//	SelMonsNo[client]�Ŏ����|�P�`�F�b�N
}

//============================================================================================
/**
 *	AI�V�[�P���X
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	sp			�T�[�o�p�p�����[�^���[�N�\����
 *
 * @retval	FALSE:AI�v�Z�r�� TRUE:�v�Z�I��
 */
//============================================================================================
static	void	WazaAISequence(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	while(sp->AIWT.AI_SEQNO!=AI_SEQ_END){
		switch(sp->AIWT.AI_SEQNO){
		case AI_SEQ_THINK_INIT:
			sp->AISeqAdrs=sp->AISeqWork[sp->AIWT.AI_THINK_NO];
			if(sp->psp[sp->AIWT.AI_AttackClient].pp[sp->AIWT.AI_WAZAPOS]==0){
				sp->AIWT.AI_WAZANO=0;
			}
			else{
				sp->AIWT.AI_WAZANO=sp->psp[sp->AIWT.AI_AttackClient].waza[sp->AIWT.AI_WAZAPOS];
			}
			sp->AIWT.AI_SEQNO++;
			break;
		case AI_SEQ_THINK:
			if(sp->AIWT.AI_WAZANO!=0){
				AISequenceTbl[sp->AISeqWork[sp->AISeqAdrs]](bw,sp);
			}
			else{
				sp->AIWT.AI_WAZAPOINT[sp->AIWT.AI_WAZAPOS]=0;
				sp->AIWT.AI_STATUSFLAG|=AI_STATUSFLAG_END;
			}
			if(sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_END){
				sp->AIWT.AI_WAZAPOS++;
				if((sp->AIWT.AI_WAZAPOS<4)&&((sp->AIWT.AI_STATUSFLAG&AI_STATUSFLAG_FINISH)==0)){
					sp->AIWT.AI_SEQNO=AI_SEQ_THINK_INIT;
				}
				else{
					sp->AIWT.AI_SEQNO++;
				}
				sp->AIWT.AI_STATUSFLAG&=AI_STATUSFLAG_END_OFF;
			}
			break;
		case AI_SEQ_END:
			break;
		}
	}
}

//--------------------- AI�R�}���h���[�`���Q ------------------------

//------------------------------------------------------------
//	�����_������
//------------------------------------------------------------

//IF_RND_UNDER		value,adrs
static	void	AI_IF_RND_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_RND_UNDER value:%d adrs:%d\n",value,adrs);
#endif

	if((gf_rand()%256)<value){
		AISeqInc(sp,adrs);
	}
}

//IF_RND_OVER			value,adrs
static	void	AI_IF_RND_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_RND_OVER value:%d adrs:%d\n",value,adrs);
#endif

	if((gf_rand()%256)>value){
		AISeqInc(sp,adrs);
	}
}

//IF_RND_EQUAL		value,adrs
static	void	AI_IF_RND_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_RND_EQUAL value:%d adrs:%d\n",value,adrs);
#endif

	if((gf_rand()%256)==value){
		AISeqInc(sp,adrs);
	}
}

//IFN_RND_EQUAL		value,adrs
static	void	AI_IFN_RND_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_RND_EQUAL value:%d adrs:%d\n",value,adrs);
#endif

	if((gf_rand()%256)!=value){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�|�C���g�����Z
//------------------------------------------------------------

//INCDEC				value
static	void	AI_INCDEC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("INCDEC value:%d\n",value);
#endif

	sp->AIWT.AI_WAZAPOINT[sp->AIWT.AI_WAZAPOS]+=value;

	if(sp->AIWT.AI_WAZAPOINT[sp->AIWT.AI_WAZAPOS]<0){
		sp->AIWT.AI_WAZAPOINT[sp->AIWT.AI_WAZAPOS]=0;
	}
}

//------------------------------------------------------------
//	HP�ł̕���
//------------------------------------------------------------

//IF_HP_UNDER			side,value,adrs
static	void	AI_IF_HP_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	u32	hp;
	int	side;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HP_UNDER side:%d value:%d adrs:%d\n",side,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	hp=sp->psp[client_no].hp*100/sp->psp[client_no].hpmax;

	if(hp<value){
		AISeqInc(sp,adrs);
	}
}

//IF_HP_OVER			side,value,adrs
static	void	AI_IF_HP_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	u32	hp;
	int	side;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HP_OVER side:%d value:%d adrs:%d\n",side,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	hp=sp->psp[client_no].hp*100/sp->psp[client_no].hpmax;

	if(hp>value){
		AISeqInc(sp,adrs);
	}
}

//IF_HP_EQUAL			side,value,adrs
static	void	AI_IF_HP_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	u32	hp;
	int	side;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HP_EQUAL side:%d value:%d adrs:%d\n",side,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	hp=sp->psp[client_no].hp*100/sp->psp[client_no].hpmax;

	if(hp==value){
		AISeqInc(sp,adrs);
	}
}

//IFN_HP_EQUAL			side,value,adrs
static	void	AI_IFN_HP_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	u32	hp;
	int	side;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_HP_EQUAL side:%d value:%d adrs:%d\n",side,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	hp=sp->psp[client_no].hp*100/sp->psp[client_no].hpmax;

	if(hp!=value){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	��Ԉُ���`�F�b�N
//------------------------------------------------------------
//IF_COND				side,condition,adrs
static	void	AI_IF_COND(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	condition;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition��ǂݍ���
	condition=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_COND side:%d condition:%08x adrs:%d\n",side,condition,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].condition&condition){
		AISeqInc(sp,adrs);
	}
}

//IFN_COND				side,condition,adrs
static	void	AI_IFN_COND(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	condition;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition��ǂݍ���
	condition=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_COND side:%d condition:%08x adrs:%d\n",side,condition,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if((sp->psp[client_no].condition&condition)==0){
		AISeqInc(sp,adrs);
	}
}

//IF_COND2			side,condition,adrs
static	void	AI_IF_COND2(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	condition2;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition2��ǂݍ���
	condition2=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_COND2 side:%d condition2:%08x adrs:%d\n",side,condition2,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].condition2&condition2){
		AISeqInc(sp,adrs);
	}
}

//IFN_COND2			side,condition,adrs
static	void	AI_IFN_COND2(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	condition2;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition2��ǂݍ���
	condition2=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_COND2 side:%d condition2:%08x adrs:%d\n",side,condition2,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if((sp->psp[client_no].condition2&condition2)==0){
		AISeqInc(sp,adrs);
	}
}

//IF_WAZAKOUKA		side,condition,adrs
static	void	AI_IF_WAZAKOUKA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	waza_kouka;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//waza_kouka��ǂݍ���
	waza_kouka=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_WAZAKOUKA side:%d waza_kouka:%08x adrs:%d\n",side,waza_kouka,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].waza_kouka&waza_kouka){
		AISeqInc(sp,adrs);
	}
}

//IFN_WAZAKOUKA		side,condition,adrs
static	void	AI_IFN_WAZAKOUKA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	waza_kouka;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//waza_kouka��ǂݍ���
	waza_kouka=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_WAZAKOUKA side:%d waza_kouka:%08x adrs:%d\n",side,waza_kouka,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if((sp->psp[client_no].waza_kouka&waza_kouka)==0){
		AISeqInc(sp,adrs);
	}
}

//IF_SIDE_CONDITION		side,condition,adrs
static	void	AI_IF_SIDE_CONDITION(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	condition;
	int	adrs;
	u8	dir;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition��ǂݍ���
	condition=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_SIDE_CONDITION side:%d condition:%08x adrs:%d\n",side,condition,adrs);
#endif

	client_no=SideToClientNo(sp,side);
	dir=BattleWorkMineEnemyCheck(bw,client_no);

	if(sp->side_condition[dir]&condition){
		AISeqInc(sp,adrs);
	}
}

//IFN_SIDE_CONDITION	side,condition,adrs
static	void	AI_IFN_SIDE_CONDITION(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	condition;
	int	adrs;
	u8	dir;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition��ǂݍ���
	condition=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_SIDE_CONDITION side:%d condition:%08x adrs:%d\n",side,condition,adrs);
#endif

	client_no=SideToClientNo(sp,side);
	dir=BattleWorkMineEnemyCheck(bw,client_no);

	if((sp->side_condition[dir]&condition)==0){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�v�Z���ʂɂ�镪��
//------------------------------------------------------------

//IF_UNDER			value,adrs
static	void	AI_IF_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_UNDER value:%d adrs:%d\n",value,adrs);
#endif

	if(sp->AIWT.AI_CALC_WORK<value){
		AISeqInc(sp,adrs);
	}
}

//IF_OVER				value,adrs
static	void	AI_IF_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_OVER value:%d adrs:%d\n",value,adrs);
#endif

	if(sp->AIWT.AI_CALC_WORK>value){
		AISeqInc(sp,adrs);
	}
}

//IF_EQUAL			value,adrs
static	void	AI_IF_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_EQUAL value:%d adrs:%d\n",value,adrs);
#endif

	if(sp->AIWT.AI_CALC_WORK==value){
		AISeqInc(sp,adrs);
	}
}

//IFN_EQUAL			value,adrs
static	void	AI_IFN_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_EQUAL value:%d adrs:%d\n",value,adrs);
#endif

	if(sp->AIWT.AI_CALC_WORK!=value){
		AISeqInc(sp,adrs);
	}
}

//IF_BIT			value,adrs
static	void	AI_IF_BIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_BIT value:%d adrs:%d\n",value,adrs);
#endif

	if(sp->AIWT.AI_CALC_WORK&value){
		AISeqInc(sp,adrs);
	}
}

//IFN_BIT			value,adrs
static	void	AI_IFN_BIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_BIT value:%d adrs:%d\n",value,adrs);
#endif

	if((sp->AIWT.AI_CALC_WORK&value)==0){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�Z�i���o�[�̃`�F�b�N�i���̋Z�i���o�[�����[�N�ɓ����j
//------------------------------------------------------------

//IF_WAZANO		wazano,adrs
static	void	AI_IF_WAZANO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	waza_no;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//waza_no��ǂݍ���
	waza_no=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_WAZANO waza_no:%d adrs:%d\n",waza_no,adrs);
#endif

	if(sp->AIWT.AI_WAZANO==waza_no){
		AISeqInc(sp,adrs);
	}
}

//IFN_WAZANO	wazano,adrs
static	void	AI_IFN_WAZANO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	waza_no;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//waza_no��ǂݍ���
	waza_no=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_WAZANO waza_no:%d adrs:%d\n",waza_no,adrs);
#endif

	if(sp->AIWT.AI_WAZANO!=waza_no){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�w�肳�ꂽ�e�[�u�����Q�Ƃ��Ĉ�v�A�s��v�ŕ���
//------------------------------------------------------------

//IF_TABLE_JUMP		tableadrs,jumpadrs	
static	void	AI_IF_TABLE_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	tbl_adrs;
	int	jump_adrs;
	int	data;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//tbl_adrs��ǂݍ���
	tbl_adrs=AISeqDataRead(sp);

	//jump_adrs��ǂݍ���
	jump_adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_TABLE_JUMP table_adrs:%d jump_adrs:%d\n",tbl_adrs,jump_adrs);
#endif

	while((data=AISeqDataReadOfs(sp,tbl_adrs))!=0xffffffff){
		if(sp->AIWT.AI_CALC_WORK==data){
			AISeqInc(sp,jump_adrs);
			break;
		}
		tbl_adrs++;
	}
}

//IFN_TABLE_JUMP	tableadrs,jumpadrs
static	void	AI_IFN_TABLE_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	tbl_adrs;
	int	jump_adrs;
	int	data;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//tbl_adrs��ǂݍ���
	tbl_adrs=AISeqDataRead(sp);

	//jump_adrs��ǂݍ���
	jump_adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_TABLE_JUMP table_adrs:%d jump_adrs:%d\n",tbl_adrs,jump_adrs);
#endif

	while((data=AISeqDataReadOfs(sp,tbl_adrs))!=0xffffffff){
		if(sp->AIWT.AI_CALC_WORK==data){
			return;
		}
		tbl_adrs++;
	}
	AISeqInc(sp,jump_adrs);
}

//------------------------------------------------------------
//	�������_���[�W�Z�������Ă��邩�`�F�b�N���ĕ���
//------------------------------------------------------------
//IF_HAVE_DAMAGE_WAZA		adrs
static	void	AI_IF_HAVE_DAMAGE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HAVE_DAMAGE_WAZA adrs:%d\n",adrs);
#endif

	for(i=0;i<4;i++){
		if((sp->psp[sp->AIWT.AI_AttackClient].waza[i]!=0)&&
		   (sp->AIWT.wtd[sp->psp[sp->AIWT.AI_AttackClient].waza[i]].damage)){
			break;
		}
	}

	if(i<4){
		AISeqInc(sp,adrs);
	}
}

static	void	AI_IFN_HAVE_DAMAGE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_HAVE_DAMAGE_WAZA adrs:%d\n",adrs);
#endif

	for(i=0;i<4;i++){
		if((sp->psp[sp->AIWT.AI_AttackClient].waza[i]!=0)&&
		   (sp->AIWT.wtd[sp->psp[sp->AIWT.AI_AttackClient].waza[i]].damage)){
			break;
		}
	}
	if(i==4){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�^�[���̃`�F�b�N�i�����^�[���ڂ������[�N�ɓ����j
//------------------------------------------------------------

//CHECK_TURN
static	void	AI_CHECK_TURN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_TURN\n");
#endif

	sp->AIWT.AI_CALC_WORK=sp->total_turn;
}

//------------------------------------------------------------
//	�^�C�v�̃`�F�b�N(�|�P�������邢�͋Z�̃^�C�v�����[�N�ɓ����j
//------------------------------------------------------------

//CHECK_TYPE			side
static	void	AI_CHECK_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_TYPE side:%d\n",side);
#endif

	switch(side){
	case CHECK_ATTACK_TYPE1:
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_AttackClient,ID_PSP_type1,NULL);
		break;
	case CHECK_DEFENCE_TYPE1:
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_DefenceClient,ID_PSP_type1,NULL);
		break;
	case CHECK_ATTACK_TYPE2:
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_AttackClient,ID_PSP_type2,NULL);
		break;
	case CHECK_DEFENCE_TYPE2:
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_DefenceClient,ID_PSP_type2,NULL);
		break;
	case CHECK_WAZA:
		sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->AIWT.AI_WAZANO].wazatype;
		break;
	case CHECK_ATTACK_FRIEND_TYPE1:
		client_no=BattleWorkPartnerClientNoGet(bw,sp->AIWT.AI_AttackClient);
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL);
		break;
	case CHECK_DEFENCE_FRIEND_TYPE1:
		client_no=BattleWorkPartnerClientNoGet(bw,sp->AIWT.AI_DefenceClient);
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL);
		break;
	case CHECK_ATTACK_FRIEND_TYPE2:
		client_no=BattleWorkPartnerClientNoGet(bw,sp->AIWT.AI_AttackClient);
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL);
		break;
	case CHECK_DEFENCE_FRIEND_TYPE2:
		client_no=BattleWorkPartnerClientNoGet(bw,sp->AIWT.AI_DefenceClient);
		sp->AIWT.AI_CALC_WORK=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL);
		break;
	default:
		GF_ASSERT(0);
		break;
	}
}

// HAVE_TYPE	side, type
static	void	AI_HAVE_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	type;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//type��ǂݍ���
	type=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("HAVE_TYPE side:%d type:%d\n",side,type);
#endif

	client_no=SideToClientNo(sp,side);

	if((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)==type)||
	   (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)==type)){
		sp->AIWT.AI_CALC_WORK=HAVE_YES;
	}
	else{
		sp->AIWT.AI_CALC_WORK=HAVE_NO;
	}
}

//------------------------------------------------------------
//	�U���Z���ǂ����̃`�F�b�N�i�Z�̈З͂����[�N�ɓ����)
//------------------------------------------------------------

//CHECK_IRYOKU
static	void	AI_CHECK_IRYOKU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_IRYOKU\n");
#endif

	sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->AIWT.AI_WAZANO].damage;
}

//------------------------------------------------------------
//	�З͂���ԍ������̃`�F�b�N
//------------------------------------------------------------

//COMP_POWER
static	void	AI_COMP_POWER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i=0,j,ok;
	s32	damage[4];
	int	flag;
	u8	power_rnd[6];

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("COMP_POWER flag:%d\n",flag);
#endif

	j=0;
	while(NoCompPowerSeqNo[j]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==NoCompPowerSeqNo[j]){
			break;
		}
		j++;
	}
	ok=0;
	while(OkCompPowerSeqNo[ok]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==OkCompPowerSeqNo[ok]){
			break;
		}
		ok++;
	}

	if((OkCompPowerSeqNo[ok]!=0xffff)||
	  ((sp->AIWT.wtd[sp->AIWT.AI_WAZANO].damage>1)&&(NoCompPowerSeqNo[j]==0xffff))){
		for(i=0;i<6;i++){
			power_rnd[i]=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_AttackClient,ID_PSP_hp_rnd+i,NULL);
		}
		AICompPowerCalc(bw,sp,sp->AIWT.AI_AttackClient,&sp->psp[sp->AIWT.AI_AttackClient].waza[0],&damage[0],
						sp->psp[sp->AIWT.AI_AttackClient].item,&power_rnd[0],
						ST_ServerTokuseiGet(sp,sp->AIWT.AI_AttackClient),
						sp->psp[sp->AIWT.AI_AttackClient].wkw.shutout_count,flag);
		for(i=0;i<4;i++){
			if(damage[i]>damage[sp->AIWT.AI_WAZAPOS]){
				break;
			}
		}
		if(i==4){
			sp->AIWT.AI_CALC_WORK=COMP_POWER_TOP;
		}
		else{
			sp->AIWT.AI_CALC_WORK=COMP_POWER_NOTOP;
		}
	}
	else{
		sp->AIWT.AI_CALC_WORK=COMP_POWER_NONE;
	}
}

//------------------------------------------------------------
//	�O�̃^�[���Ɏg�����Z�̃`�F�b�N�i�Z�̃i���o�[�����[�N�ɓ����j
//------------------------------------------------------------

//CHECK_LAST_WAZA	side
static	void	AI_CHECK_LAST_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_LAST_WAZA side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	sp->AIWT.AI_CALC_WORK=sp->waza_no_old[client_no];
}

//------------------------------------------------------------
//	�i�[���ꂽ�Z�̃^�C�v�`�F�b�N
//------------------------------------------------------------

//IF_WAZA_TYPE		type,adrs
static	void	AI_IF_WAZA_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	type;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//type��ǂݍ���
	type=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_WAZA_TYPE type:%d adrs:%d\n",type,adrs);
#endif

	if(type==sp->AIWT.AI_CALC_WORK){
		AISeqInc(sp,adrs);
	}
}

//IFN_WAZA_TYPE		type,adrs
static	void	AI_IFN_WAZA_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	type;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//type��ǂݍ���
	type=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_WAZA_TYPE type:%d adrs:%d\n",type,adrs);
#endif

	if(type!=sp->AIWT.AI_CALC_WORK){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�ǂ��炪��s���̃`�F�b�N
//------------------------------------------------------------

//IF_FIRST			side,adrs
static	void	AI_IF_FIRST(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_FIRST side:%d adrs:%d\n",side,adrs);
#endif

	if(ST_ServerAgiCalc(bw,sp,sp->AIWT.AI_AttackClient,sp->AIWT.AI_DefenceClient,1)==side){
		AISeqInc(sp,adrs);
	}
}

//IFN_FIRST			side,adrs
static	void	AI_IFN_FIRST(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_FIRST side:%d adrs:%d\n",side,adrs);
#endif

	if(ST_ServerAgiCalc(bw,sp,sp->AIWT.AI_AttackClient,sp->AIWT.AI_DefenceClient,1)!=side){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�T�������̂��邩�`�F�b�N�i�������[�N�ɓ����j
//------------------------------------------------------------

//CHECK_BENCH_COUNT			side
static	void	AI_CHECK_BENCH_COUNT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	POKEPARTY		*poke_party;
	POKEMON_PARAM	*pp;
	int	i;
	u8	client_no;
	u8	sel1,sel2;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_BENCH_COUNT side:%d\n",side);
#endif

	sp->AIWT.AI_CALC_WORK=0;

	client_no=SideToClientNo(sp,side);

	poke_party=BattleWorkPokePartyGet(bw,client_no);

	if(bw->fight_type&FIGHT_TYPE_2vs2){
		sel1=sp->sel_mons_no[client_no];
		sel2=sp->sel_mons_no[BattleWorkPartnerClientNoGet(bw,client_no)];
	}
	else{
		sel1=sel2=sp->sel_mons_no[client_no];
	}

	for(i=0;i<BattleWorkPokeCountGet(bw,client_no);i++){
		pp=PokeParty_GetMemberPointer(poke_party,i);
		if((i!=sel1)&&
		   (i!=sel2)&&
		   (PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
			sp->AIWT.AI_CALC_WORK++;
		}
	}
}

//------------------------------------------------------------
//	���݂̋Z�i���o�[�̃`�F�b�N
//------------------------------------------------------------

//CHECK_WAZANO
static	void	AI_CHECK_WAZANO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WAZANO\n");
#endif

	sp->AIWT.AI_CALC_WORK=sp->AIWT.AI_WAZANO;
}

//------------------------------------------------------------
//	���݂̋Z�i���o�[�̃V�[�P���X�i���o�[�̃`�F�b�N
//------------------------------------------------------------

//CHECK_WAZASEQNO
static	void	AI_CHECK_WAZASEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WAZASEQNO\n");
#endif

	sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect;
}

//------------------------------------------------------------
//	�Ƃ������̃`�F�b�N�i�Ƃ������i���o�[�����[�N�ɓ����j
//------------------------------------------------------------

//CHECK_TOKUSEI		side
static	void	AI_CHECK_TOKUSEI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	spe1,spe2;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_TOKUSEI side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	//�Z���ʂ��������󂯂Ă�����A�����͂Ȃ�
	if(sp->psp[client_no].waza_kouka&WAZAKOUKA_IEKI){
		sp->AIWT.AI_CALC_WORK=0;
	}
	else if((sp->AIWT.AI_AttackClient!=client_no)&&(side!=CHECK_ATTACK_FRIEND)){
		if(sp->AIWT.AI_TOKUSYUNO[client_no]){
			sp->AIWT.AI_CALC_WORK=sp->AIWT.AI_TOKUSYUNO[client_no];
		}
		else{
			if((sp->psp[client_no].speabino==TOKUSYU_KAGEHUMI)||
			   (sp->psp[client_no].speabino==TOKUSYU_ZIRYOKU)||
			   (sp->psp[client_no].speabino==TOKUSYU_ARIZIGOKU)){
				sp->AIWT.AI_CALC_WORK=sp->psp[client_no].speabino;
			}
			else{
				spe1=PokePersonalParaGet(sp->psp[client_no].monsno,ID_PER_speabi1);
				spe2=PokePersonalParaGet(sp->psp[client_no].monsno,ID_PER_speabi2);
				if((spe1)&&(spe2)){
					if(gf_rand()&1){
						sp->AIWT.AI_CALC_WORK=spe1;
					}
					else{
						sp->AIWT.AI_CALC_WORK=spe2;
					}
				}
				else if(spe1){
					sp->AIWT.AI_CALC_WORK=spe1;
				}
				else{
					sp->AIWT.AI_CALC_WORK=spe2;
				}
			}
		}
	}
	else{
		sp->AIWT.AI_CALC_WORK=sp->psp[client_no].speabino;
	}
}
//------------------------------------------------------------
//	�Ƃ����������Ă��邩�`�F�b�N
//------------------------------------------------------------
//CHECK_HAVE_TOKUSEI		side, abi
static	void	AI_HAVE_TOKUSEI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8 client_no;
	int side;
	int abi;
	int abino;
	int	spe1,spe2;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//abi��ǂݍ���
	abi=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_HAVE_TOKUSEI side:%d abi:%d\n",side,abi);
#endif

	client_no=SideToClientNo(sp,side);

	//�Z���ʂ��������󂯂Ă�����A�����͂Ȃ�
	if(sp->psp[client_no].waza_kouka&WAZAKOUKA_IEKI){
		abino=0;
	}
	else if((side==CHECK_DEFENCE)||(side==CHECK_DEFENCE_FRIEND)){
		if(sp->AIWT.AI_TOKUSYUNO[client_no]){
			abino=sp->AIWT.AI_TOKUSYUNO[client_no];
			sp->AIWT.AI_CALC_WORK=sp->AIWT.AI_TOKUSYUNO[client_no];
		}
		else{
			if((sp->psp[client_no].speabino==TOKUSYU_KAGEHUMI)||
			   (sp->psp[client_no].speabino==TOKUSYU_ZIRYOKU)||
			   (sp->psp[client_no].speabino==TOKUSYU_ARIZIGOKU)){
				abino=sp->psp[client_no].speabino;
			}
			else{
				spe1=PokePersonalParaGet(sp->psp[client_no].monsno,ID_PER_speabi1);
				spe2=PokePersonalParaGet(sp->psp[client_no].monsno,ID_PER_speabi2);
				if((spe1)&&(spe2)){
					// ��v�`�F�b�N�Ȃ̂Łc����Ă���΂ǂ���ł��n�j
					if((spe1!=abi)&&(spe2!=abi)){
						abino=spe1;
					}
					// �s���i�ǂ��炩����v�j�Ȃ�O�ɂ��Ă���
					else{
						abino=0;
					}
				}
				else if(spe1){
					abino=spe1;
				}
				else{
					abino=spe2;
				}
			}
		}
	}
	else{
		abino=sp->psp[client_no].speabino;
	}

	if(abino==0){
		sp->AIWT.AI_CALC_WORK=HAVE_UNKNOWN;
	}
	else if(abino==abi){
		sp->AIWT.AI_CALC_WORK=HAVE_YES;
	}
	else{
		sp->AIWT.AI_CALC_WORK=HAVE_NO;
	}
}

//------------------------------------------------------------
//	�����Ƒ���̑����`�F�b�N
//------------------------------------------------------------

//CHECK_AISYOU
static	void	AI_CHECK_AISYOU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u32	damage;
	u32	flag;
	u16	waza_no;
	int	type;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_AISYOU\n");
#endif

	sp->AIWT.AI_CALC_WORK=AISYOU_0BAI;

	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		damage=AISYOU_1BAI;
		flag=0;
		waza_no=sp->psp[sp->AIWT.AI_AttackClient].waza[i];
		type=AIWazaTypeGet(bw,sp,sp->AIWT.AI_AttackClient,waza_no);
		if(waza_no){
			damage=ST_ServerTypeCheck(bw,sp,waza_no,type,
									  sp->AIWT.AI_AttackClient,
									  sp->AIWT.AI_DefenceClient,
									  damage,
									  &flag);
			if(damage==AISYOU_15BAI*2){
				damage=AISYOU_2BAI;
			}
			else if(damage==AISYOU_15BAI*4){
				damage=AISYOU_4BAI;
			}
			else if(damage==AISYOU_15BAI/2){
				damage=AISYOU_1_2BAI;
			}
			else if(damage==AISYOU_15BAI/4){
				damage=AISYOU_1_4BAI;
			}
			if(flag&(WAZA_STATUS_FLAG_KOUKANAI|WAZA_STATUS_FLAG_JIMEN_NOHIT|
					 WAZA_STATUS_FLAG_DENZIHUYUU_NOHIT|WAZA_STATUS_FLAG_BATSUGUN_NOHIT)){
				damage=0;
			}
			if(sp->AIWT.AI_CALC_WORK<damage){
				sp->AIWT.AI_CALC_WORK=damage;
			}
		}
	}
}

//------------------------------------------------------------
//	�Z�̃^�C�v�Ƒ���̑������`�F�b�N
//------------------------------------------------------------
//CHECK_WAZA_AISYOU		aisyou,adrs
static	void	AI_CHECK_WAZA_AISYOU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	aisyou;
	int	adrs;
	u32	damage;
	u32	flag;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//aisyou��ǂݍ���
	aisyou=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WAZA_AISYOU aisyou:%d adrs:%d\n",aisyou,adrs);
#endif

	damage=AISYOU_1BAI;
	flag=0;
	damage=ST_ServerTypeCheck(bw,sp,
							  sp->AIWT.AI_WAZANO,AIWazaTypeGet(bw,sp,sp->AIWT.AI_AttackClient,sp->AIWT.AI_WAZANO),
							  sp->AIWT.AI_AttackClient,
							  sp->AIWT.AI_DefenceClient,
							  damage,
							  &flag);
	if(damage==AISYOU_15BAI*2){
		damage=AISYOU_2BAI;
	}
	else if(damage==AISYOU_15BAI*4){
		damage=AISYOU_4BAI;
	}
	else if(damage==AISYOU_15BAI/2){
		damage=AISYOU_1_2BAI;
	}
	else if(damage==AISYOU_15BAI/4){
		damage=AISYOU_1_4BAI;
	}
	if(flag&(WAZA_STATUS_FLAG_KOUKANAI|WAZA_STATUS_FLAG_JIMEN_NOHIT|
			 WAZA_STATUS_FLAG_DENZIHUYUU_NOHIT|WAZA_STATUS_FLAG_BATSUGUN_NOHIT)){
		damage=0;
	}

	if(damage==aisyou){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�T���̏�ԃ`�F�b�N
//------------------------------------------------------------

//IF_BENCH_COND		side,condition,adrs
static	void	AI_IF_BENCH_COND(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	POKEPARTY		*poke_party;
	POKEMON_PARAM	*pp;
	int	i;
	u8	client_no;
	u8	sel1,sel2;
	int	side;
	u32	condition;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition��ǂݍ���
	condition=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_BENCH_COND side:%d condition:%08x adrs:%d\n",side,condition,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(bw->fight_type&FIGHT_TYPE_2vs2){
		sel1=sp->sel_mons_no[client_no];
		sel2=sp->sel_mons_no[BattleWorkPartnerClientNoGet(bw,client_no)];
	}
	else{
		sel1=sel2=sp->sel_mons_no[client_no];
	}

	poke_party=BattleWorkPokePartyGet(bw,client_no);

	for(i=0;i<BattleWorkPokeCountGet(bw,client_no);i++){
		pp=PokeParty_GetMemberPointer(poke_party,i);
		if((i!=sel1)&&(i!=sel2)&&
		   (PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
		   (PokeParaGet(pp,ID_PARA_condition,NULL)&condition)){
			AISeqInc(sp,adrs);
			return;
		}
	}
}

//IFN_BENCH_COND		side,condition,adrs
static	void	AI_IFN_BENCH_COND(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	POKEPARTY		*poke_party;
	POKEMON_PARAM	*pp;
	int	i;
	u8	client_no;
	u8	sel1,sel2;
	int	side;
	u32	condition;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//condition��ǂݍ���
	condition=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_BENCH_COND side:%d condition:%08x adrs:%d\n",side,condition,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(bw->fight_type&FIGHT_TYPE_2vs2){
		sel1=sp->sel_mons_no[client_no];
		sel2=sp->sel_mons_no[BattleWorkPartnerClientNoGet(bw,client_no)];
	}
	else{
		sel1=sel2=sp->sel_mons_no[client_no];
	}

	poke_party=BattleWorkPokePartyGet(bw,client_no);

	for(i=0;i<BattleWorkPokeCountGet(bw,client_no);i++){
		pp=PokeParty_GetMemberPointer(poke_party,i);
		if((i!=sel1)&&(i!=sel2)&&
		   (PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
		  ((PokeParaGet(pp,ID_PARA_condition,NULL)&condition)==0)){
			AISeqInc(sp,adrs);
			return;
		}
	}
}

//------------------------------------------------------------
//	�V��`�F�b�N�i�V��i���o�[�����[�N�ɓ����j
//------------------------------------------------------------

//CHECK_WEATHER
static	void	AI_CHECK_WEATHER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WEATHER\n");
#endif

	sp->AIWT.AI_CALC_WORK=WEATHER_NONE;

	if(sp->field_condition&FIELD_CONDITION_AME_ALL){
		sp->AIWT.AI_CALC_WORK=WEATHER_AME;
	}
	if(sp->field_condition&FIELD_CONDITION_SUNAARASHI_ALL){
		sp->AIWT.AI_CALC_WORK=WEATHER_SUNAARASHI;
	}
	if(sp->field_condition&FIELD_CONDITION_HARE_ALL){
		sp->AIWT.AI_CALC_WORK=WEATHER_HARE;
	}
	if(sp->field_condition&FIELD_CONDITION_ARARE_ALL){
		sp->AIWT.AI_CALC_WORK=WEATHER_ARARE;
	}
	if(sp->field_condition&FIELD_CONDITION_HUKAIKIRI){
		sp->AIWT.AI_CALC_WORK=WEATHER_HUKAIKIRI;
	}
}

//------------------------------------------------------------
//	�Z�̃V�[�P���X�i���o�[���`�F�b�N���āA����
//------------------------------------------------------------

//IF_WAZA_SEQNO_JUMP	seqno,adrs
static	void	AI_IF_WAZA_SEQNO_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seqno;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//seqno��ǂݍ���
	seqno=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_WAZA_SEQNO_JUMP seqno:%d adrs:%d\n",seqno,adrs);
#endif

	if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==seqno){
		AISeqInc(sp,adrs);
	}
}

//IFN_WAZA_SEQNO_JUMP	seqno,adrs
static	void	AI_IFN_WAZA_SEQNO_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seqno;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//seqno��ǂݍ���
	seqno=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_WAZA_SEQNO_JUMP seqno:%d adrs:%d\n",seqno,adrs);
#endif

	if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect!=seqno){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�����⑊��̃p�����[�^�ω��l���Q�Ƃ��ĕ���
//------------------------------------------------------------

//IF_PARA_UNDER		side,para,value,adrs
static	void	AI_IF_PARA_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	para;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//para��ǂݍ���
	para=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_PARA_UNDER side:%d para:%d value:%d adrs:%d\n",side,para,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].abiritycnt[para]<value){
		AISeqInc(sp,adrs);
	}
}

//IF_PARA_OVER		side,para,value,adrs
static	void	AI_IF_PARA_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	para;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//para��ǂݍ���
	para=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_PARA_OVER side:%d para:%d value:%d adrs:%d\n",side,para,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].abiritycnt[para]>value){
		AISeqInc(sp,adrs);
	}
}

//IF_PARA_EQUAL		side,para,value,adrs
static	void	AI_IF_PARA_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	para;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//para��ǂݍ���
	para=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_PARA_EQUAL side:%d para:%d value:%d adrs:%d\n",side,para,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].abiritycnt[para]==value){
		AISeqInc(sp,adrs);
	}
}

//IFN_PARA_EQUAL	side,para,value,adrs
static	void	AI_IFN_PARA_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	para;
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//para��ǂݍ���
	para=AISeqDataRead(sp);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_PARA_EQUAL side:%d para:%d value:%d adrs:%d\n",side,para,value,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].abiritycnt[para]!=value){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�Z�̃_���[�W�v�Z�����đ��肪�m���ɂȂ邩�`�F�b�N���ĕ���
//------------------------------------------------------------

//IF_WAZA_HINSHI		flag,adrs
static	void	AI_IF_WAZA_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	loss_flag;
	int	adrs;
	int	loss;
	int	no,ok;
	u32	damage;
	u8	power_rnd[6];

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//flag��ǂݍ���
	loss_flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_WAZA_HINSHI flag:%d adrs:%d\n",loss_flag,adrs);
#endif

	if(loss_flag==LOSS_CALC_ON){
		loss=sp->AIWT.AI_DAMAGELOSS[sp->AIWT.AI_WAZAPOS];
	}
	else{
		loss=100;
	}

	no=0;
	while(NoCompPowerSeqNo[no]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==NoCompPowerSeqNo[no]){
			break;
		}
		no++;
	}
	ok=0;
	while(OkCompPowerSeqNo[ok]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==OkCompPowerSeqNo[ok]){
			break;
		}
		ok++;
	}
	if((OkCompPowerSeqNo[ok]!=0xffff)||
	  ((sp->AIWT.wtd[sp->AIWT.AI_WAZANO].damage>1)&&(NoCompPowerSeqNo[no]==0xffff))){
		for(i=0;i<6;i++){
			power_rnd[i]=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_AttackClient,ID_PSP_hp_rnd+i,NULL);
		}

		damage=AIWazaDamageCalc(bw,sp,sp->AIWT.AI_WAZANO,sp->psp[sp->AIWT.AI_AttackClient].item,&power_rnd[0],
								sp->AIWT.AI_AttackClient,ST_ServerTokuseiGet(sp,sp->AIWT.AI_AttackClient),
								sp->psp[sp->AIWT.AI_AttackClient].wkw.shutout_count,loss);
		if(sp->psp[sp->AIWT.AI_DefenceClient].hp<=damage){
			AISeqInc(sp,adrs);
		}
	}
}

//IFN_WAZA_HINSHI		flag,adrs
static	void	AI_IFN_WAZA_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	loss_flag;
	int	adrs;
	int	loss;
	int	no,ok;
	u32	damage;
	u8	power_rnd[6];

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//loss_flag��ǂݍ���
	loss_flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_WAZA_HINSHI flag:%d adrs:%d\n",loss_flag,adrs);
#endif

	if(loss_flag==LOSS_CALC_ON){
		loss=sp->AIWT.AI_DAMAGELOSS[sp->AIWT.AI_WAZAPOS];
	}
	else{
		loss=100;
	}

	no=0;
	while(NoCompPowerSeqNo[no]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==NoCompPowerSeqNo[no]){
			break;
		}
		no++;
	}
	ok=0;
	while(OkCompPowerSeqNo[ok]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==OkCompPowerSeqNo[ok]){
			break;
		}
		ok++;
	}

	if((OkCompPowerSeqNo[ok]!=0xffff)||
	  ((sp->AIWT.wtd[sp->AIWT.AI_WAZANO].damage>1)&&(NoCompPowerSeqNo[no]==0xffff))){
		for(i=0;i<6;i++){
			power_rnd[i]=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_AttackClient,ID_PSP_hp_rnd+i,NULL);
		}

		damage=AIWazaDamageCalc(bw,sp,sp->AIWT.AI_WAZANO,sp->psp[sp->AIWT.AI_AttackClient].item,&power_rnd[0],
								sp->AIWT.AI_AttackClient,ST_ServerTokuseiGet(sp,sp->AIWT.AI_AttackClient),
								sp->psp[sp->AIWT.AI_AttackClient].wkw.shutout_count,loss);
		if(sp->psp[sp->AIWT.AI_DefenceClient].hp>damage){
			AISeqInc(sp,adrs);
		}
	}
}

//------------------------------------------------------------
//	����̋Z�������Ă��邩�̃`�F�b�N�����ĕ���
//------------------------------------------------------------
//IF_HAVE_WAZA		side,wazano,adrs
static	void	AI_IF_HAVE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u8	client_no;
	int	side;
	int	wazano;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//wazano��ǂݍ���
	wazano=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HAVE_WAZA side:%d wazano:%d adrs:%d\n",side,wazano,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	switch(side){
	case CHECK_ATTACK:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if(sp->psp[client_no].waza[i]==wazano){
				break;
			}
		}
		if(i<WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	case CHECK_ATTACK_FRIEND:
		if(sp->psp[client_no].hp==0){
			break;
		}
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if(sp->psp[client_no].waza[i]==wazano){
				break;
			}
		}
		if(i<WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	case CHECK_DEFENCE:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if(sp->AIWT.AI_DEFENCE_USE_WAZA[client_no][i]==wazano){
				break;
			}
		}
		if(i<WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	default:
		OS_Printf("�����ɂ���̂́A��������\n");
		break;
	}
}

//IFN_HAVE_WAZA		side,wazano,adrs
static	void	AI_IFN_HAVE_WAZA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u8	client_no;
	int	side;
	int	wazano;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//wazano��ǂݍ���
	wazano=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_HAVE_WAZA side:%d wazano:%d adrs:%d\n",side,wazano,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	switch(side){
	case CHECK_ATTACK:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if(sp->psp[client_no].waza[i]==wazano){
				break;
			}
		}
		if(i==WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	case CHECK_ATTACK_FRIEND:
		if(sp->psp[client_no].hp==0){
			break;
		}
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if(sp->psp[client_no].waza[i]==wazano){
				break;
			}
		}
		if(i==WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	case CHECK_DEFENCE:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if(sp->AIWT.AI_DEFENCE_USE_WAZA[client_no][i]==wazano){
				break;
			}
		}
		if(i==WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	default:
		OS_Printf("�����ɂ���̂́A��������\n");
		break;
	}
}

//------------------------------------------------------------
//	����̋Z�V�[�P���X�������Ă��邩�̃`�F�b�N�����ĕ���
//------------------------------------------------------------
//IF_HAVE_WAZA_SEQNO		side,seqno,adrs
static	void	AI_IF_HAVE_WAZA_SEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u8	client_no;
	int	side;
	int	seqno;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//seqno��ǂݍ���
	seqno=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HAVE_WAZA_SEQNO side:%d seqno:%d adrs:%d\n",side,seqno,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	switch(side){
	case CHECK_ATTACK:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if((sp->psp[client_no].waza[i])&&
			   (sp->AIWT.wtd[sp->psp[client_no].waza[i]].battleeffect==seqno)){
				break;
			}
		}
		if(i<WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	case CHECK_DEFENCE:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if((sp->AIWT.AI_DEFENCE_USE_WAZA[client_no][i])&&
			   (sp->AIWT.wtd[sp->AIWT.AI_DEFENCE_USE_WAZA[client_no][i]].battleeffect==seqno)){
				break;
			}
		}
		if(i<WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	default:
		OS_Printf("�����ɂ���̂́A��������\n");
		break;
	}
}

//IFN_HAVE_WAZA_SEQNO		side,seqno,adrs
static	void	AI_IFN_HAVE_WAZA_SEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u8	client_no;
	int	side;
	int	seqno;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//seqno��ǂݍ���
	seqno=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_HAVE_WAZA_SEQNO side:%d seqno:%d adrs:%d\n",side,seqno,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	switch(side){
	case CHECK_ATTACK:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if((sp->psp[client_no].waza[i])&&
			   (sp->AIWT.wtd[sp->psp[client_no].waza[i]].battleeffect==seqno)){
				break;
			}
		}
		if(i==WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	case CHECK_DEFENCE:
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if((sp->AIWT.AI_DEFENCE_USE_WAZA[client_no][i])&&
			   (sp->AIWT.wtd[sp->AIWT.AI_DEFENCE_USE_WAZA[client_no][i]].battleeffect==seqno)){
				break;
			}
		}
		if(i==WAZA_TEMOTI_MAX){
			AISeqInc(sp,adrs);
		}
		break;
	default:
		OS_Printf("�����ɂ���̂́A��������\n");
		break;
	}
}

//------------------------------------------------------------
//	�|�P�����̏�Ԃ��`�F�b�N�����ĕ���i���Ȃ��΂�Ƃ��A�A���R�[���Ƃ��j
//------------------------------------------------------------

//IF_POKE_CHECK_STATE		side,id,adrs
static	void	AI_IF_POKE_CHECK_STATE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	id;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//id��ǂݍ���
	id=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_POKE_CHECK_STATE side:%d id:%d adrs:%d\n",side,id,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	switch(id){
	case STATE_KANASIBARI:
		if(sp->psp[client_no].wkw.kanashibari_count){
			AISeqInc(sp,adrs);
		}
		break;
	case STATE_ENCORE:
		if(sp->psp[client_no].wkw.encore_count){
			AISeqInc(sp,adrs);
		}
		break;
	default:
		OS_Printf("�����ɂ���̂͂�������\n");
		break;
	}
}

//------------------------------------------------------------
//	�Z�̏�Ԃ��`�F�b�N�����ĕ���
//------------------------------------------------------------

//IF_WAZA_CHECK_STATE		id,adrs
static	void	AI_IF_WAZA_CHECK_STATE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	id;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//id��ǂݍ���
	id=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_WAZA_CHECK_STATE id:%d adrs:%d\n",id,adrs);
#endif

	switch(id){
	case STATE_KANASIBARI:
		if(sp->psp[sp->AIWT.AI_AttackClient].wkw.kanashibari_wazano==sp->AIWT.AI_WAZANO){
			AISeqInc(sp,adrs);
		}
		break;
	case STATE_ENCORE:
		if(sp->psp[sp->AIWT.AI_AttackClient].wkw.encore_wazano==sp->AIWT.AI_WAZANO){
			AISeqInc(sp,adrs);
		}
		break;
	default:
		OS_Printf("�����ɂ���̂͂�������\n");
		break;
	}
}

//------------------------------------------------------------
//	�ɂ�������񂽂�
//------------------------------------------------------------
//ESCAPE
static	void	AI_ESCAPE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("ESCAPE\n");
#endif

	sp->AIWT.AI_STATUSFLAG|=(AI_STATUSFLAG_END|AI_STATUSFLAG_ESCAPE|AI_STATUSFLAG_FINISH);
}

//------------------------------------------------------------
//	�T�t�@���]�[���ł̓�����m�����v�Z���ē�����Ƃ��̃A�h���X���w��
//------------------------------------------------------------
//SAFARI_ESCAPE_JUMP
static	void	AI_SAFARI_ESCAPE_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
//�T�t�@���́AAI�ł͂Ȃ��AClient�v���O�����Ɉڍs
#if 0
	u8	rate;
	u8	rnd;
	
	rate=BattleWork_P[SAFARI_ESCAPE_COUNT]*5;
	rnd=pp_rand()%100;

	if(rnd<rate)
		AISeqAdrs=(u8 *)((AISeqAdrs[1]<< 0)|
						 (AISeqAdrs[2]<< 8)|
						 (AISeqAdrs[3]<<16)|
						 (AISeqAdrs[4]<<24));
	else
		AISeqAdrs+=5;
#endif
}

//------------------------------------------------------------
//	�T�t�@���]�[���ł̓���A�N�V������I��
//------------------------------------------------------------

//SAFARI
static	void	AI_SAFARI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
//�T�t�@���́AAI�ł͂Ȃ��AClient�v���O�����Ɉڍs
#if 0
	AIWT->AI_STATUSFLAG|=(AI_STATUSFLAG_END|AI_STATUSFLAG_SAFARI|AI_STATUSFLAG_FINISH);
#endif
}

//------------------------------------------------------------
//		�����A�C�e���̃`�F�b�N
//------------------------------------------------------------

//CHECK_ITEM		side
static	void	AI_CHECK_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_ITEM side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

#if 0
	if(sp->AIWT.AI_AttackClient!=client_no){
		sp->AIWT.AI_CALC_WORK=sp->AIWT.AI_SOUBIITEM[client_no];
	}
	else{
		sp->AIWT.AI_CALC_WORK=sp->psp[client_no].item;
	}
#endif
	//�d�l�ύX�i���邢���ǁAAI�ɂ΂炷�j
	sp->AIWT.AI_CALC_WORK=sp->psp[client_no].item;
}

//------------------------------------------------------------
//		�����A�C�e���̃`�F�b�N
//------------------------------------------------------------

//CHECK_SOUBIITEM		side
static	void	AI_CHECK_SOUBIITEM(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_SOUBIITEM side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->AIWT.AI_AttackClient!=client_no){
//		sp->AIWT.AI_CALC_WORK=ItemParamGet(sp->AIWT.AI_SOUBIITEM[client_no],ITEM_PRM_EQUIP,HEAPID_BATTLE);
		sp->AIWT.AI_CALC_WORK=ST_ItemParamGet(sp,sp->AIWT.AI_SOUBIITEM[client_no],ITEM_PRM_EQUIP);
	}
	else{
//		sp->AIWT.AI_CALC_WORK=ItemParamGet(sp->psp[client_no].item,ITEM_PRM_EQUIP,HEAPID_BATTLE);
		sp->AIWT.AI_CALC_WORK=ST_ItemParamGet(sp,sp->psp[client_no].item,ITEM_PRM_EQUIP);
	}
}


//IF_HAVE_ITEM		side, item, adrs
static	void	AI_IF_HAVE_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u16 item_no;
	u8	client_no;
	int	side;
	int	item;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//item��ǂݍ���
	item=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HAVE_ITEM side:%d item:%d adrs:%d\n",side,item,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if((client_no&1)==(sp->AIWT.AI_AttackClient&1)){
		item_no=sp->psp[client_no].item;
	}
	else{
		item_no=sp->AIWT.AI_SOUBIITEM[client_no];
	}

	if(item_no==item){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	FIELD_CONDITION�`�F�b�N
//------------------------------------------------------------
//FIELD_CONDITION_CHECK	flag,adrs
static	void	AI_FIELD_CONDITION_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u32	flag;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("FIELD_CONDITION_CHECK flag:0x%08x adrs:%d\n",flag,adrs);
#endif

	if(sp->field_condition&flag){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	SIDE_CONDITION�̃J�E���g���擾
//------------------------------------------------------------
//CHECK_SIDE_CONDITION_COUNT	side,flag
static	void	AI_CHECK_SIDE_CONDITION_COUNT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	u32	flag;
	u8	dir;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_SIDE_CONDITION_COUNT side:%d flag:%08x\n",side,flag);
#endif

	client_no=SideToClientNo(sp,side);
	dir=BattleWorkMineEnemyCheck(bw,client_no);

	switch(flag){
	case SIDE_CONDITION_MAKIBISHI:
		sp->AIWT.AI_CALC_WORK=sp->scw[dir].makibisi_count;
		break;
	case SIDE_CONDITION_DOKUBISHI:
		sp->AIWT.AI_CALC_WORK=sp->scw[dir].dokubisi_count;
		break;
	}
}

//------------------------------------------------------------
//	�T���|�P������HP�������`�F�b�N
//
//	@param	side	�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	@param	adrs	HP���������|�P�������������̂Ƃѐ�
//
//------------------------------------------------------------
//IF_BENCH_HPDEC		side,adrs
static	void	AI_IF_BENCH_HPDEC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8				client_no;
	int				side;
	int				adrs;
	int				i;
	POKEMON_PARAM	*pp;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_BENCH_HPDEC side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	for(i=0;i<BattleWorkPokeCountGet(bw,client_no);i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		if(i!=sp->sel_mons_no[client_no]){
			if(PokeParaGet(pp,ID_PARA_hp,NULL)!=PokeParaGet(pp,ID_PARA_hpmax,NULL)){
				AISeqInc(sp,adrs);
				break;
			}
		}
	}
}

//------------------------------------------------------------
//	�T���|�P������PP�������`�F�b�N
//
//	@param	side	�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	@param	adrs	PP���������|�P�������������̂Ƃѐ�
//
//------------------------------------------------------------
//IF_BENCH_PPDEC		side,adrs
static	void	AI_IF_BENCH_PPDEC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8				client_no;
	int				side;
	int				adrs;
	int				i,j;
	POKEMON_PARAM	*pp;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_BENCH_HPDEC side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	for(i=0;i<BattleWorkPokeCountGet(bw,client_no);i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		if(i!=sp->sel_mons_no[client_no]){
			for(j=0;j<WAZA_TEMOTI_MAX;j++){
				if(PokeParaGet(pp,ID_PARA_pp1+j,NULL)!=PokeParaGet(pp,ID_PARA_pp_max1+j,NULL)){
					AISeqInc(sp,adrs);
					break;
				}
			}
			if(j!=WAZA_TEMOTI_MAX){
				break;
			}
		}
	}
}

//------------------------------------------------------------
//	�����A�C�e���̂Ȃ�����З͂��擾
//------------------------------------------------------------
//	DEF_CMD		CHECK_NAGETSUKERU_IRYOKU	side
static	void	AI_CHECK_NAGETSUKERU_IRYOKU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8				client_no;
	int				side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_NAGETSUKERU_IRYOKU side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	sp->AIWT.AI_CALC_WORK=ST_ServerNagetsukeruAtkGet(sp,client_no);
}

//------------------------------------------------------------
//	�c��PP���擾
//------------------------------------------------------------
//	DEF_CMD		CHECK_PP_REMAIN
static	void	AI_CHECK_PP_REMAIN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	sp->AIWT.AI_CALC_WORK=sp->psp[sp->AIWT.AI_AttackClient].pp[sp->AIWT.AI_WAZAPOS];
}

//------------------------------------------------------------
//	�Ƃ��Ă����`�F�b�N
//------------------------------------------------------------
//IF_TOTTEOKI		side,adrs
static	void	AI_IF_TOTTEOKI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	adrs;
	int	count;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_TOTTEOKI side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideToClientNo(sp,side);
	count=ST_ServerWazaCountGet(bw,sp,client_no);

	//�����Ă���Z���o���؂��Ă��Ȃ����A�����Ă���Z��2�ȏ�Ȃ��ꍇ�͎��s
	if((sp->psp[client_no].wkw.totteoki_count>=(count-1))&&(count>1)){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�Z�̕��ރ`�F�b�N
//------------------------------------------------------------
//CHECK_WAZA_KIND
static	void	AI_CHECK_WAZA_KIND(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WAZA_KIND\n");
#endif

//	sp->AIWT.AI_CALC_WORK=WT_WazaDataParaGet(sp->AIWT.AI_WAZANO,ID_WTD_kind);
	sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->AIWT.AI_WAZANO].kind;
}

//------------------------------------------------------------
//	���肪�Ō�ɏo�����Z�̕��ރ`�F�b�N
//------------------------------------------------------------
//CHECK_LAST_WAZA_KIND
static	void	AI_CHECK_LAST_WAZA_KIND(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_LAST_WAZA_KIND\n");
#endif

//	sp->AIWT.AI_CALC_WORK=WT_WazaDataParaGet(sp->waza_no_old[sp->AIWT.AI_DefenceClient],ID_WTD_kind);
	sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->waza_no_old[sp->AIWT.AI_DefenceClient]].kind;
}

//------------------------------------------------------------
//	�f�����Ŏw�肵���������ʂ��`�F�b�N
//------------------------------------------------------------
//CHECK_AGI_RANK		side
static	void	AI_CHECK_AGI_RANK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i,j;
	int	no[CLIENT_MAX];
	int	cl1,cl2;
	int	client_set_max;
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	client_no=SideToClientNo(sp,side);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_AGI_RANK side:%d\n",side);
#endif

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(i=0;i<client_set_max;i++){
		no[i]=i;
	}

	for(i=0;i<client_set_max-1;i++){
		for(j=i+1;j<client_set_max;j++){
			cl1=no[i];
			cl2=no[j];
			if(ST_ServerAgiCalc(bw,sp,cl1,cl2,1)){
				no[i]=cl2;
				no[j]=cl1;
			}
		}
	}
	for(i=0;i<client_set_max;i++){
		if(no[i]==client_no){
			sp->AIWT.AI_CALC_WORK=i;
			break;
		}
	}
}

//------------------------------------------------------------
//	�X���[�X�^�[�g���^�[���ڂ�
//------------------------------------------------------------
//CHECK_SLOWSTART_TURN	side
static	void	AI_CHECK_SLOWSTART_TURN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	client_no=SideToClientNo(sp,side);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_SLOWSTART_TURN side:%d\n",side);
#endif

	sp->AIWT.AI_CALC_WORK=sp->total_turn-sp->psp[client_no].wkw.nekodamashi_count;
}

//------------------------------------------------------------
//	�T���ɂ�������_���[�W��^���邩�ǂ����`�F�b�N�i����ɓ��삵�Ă܂���A�T���|�P�����̃p�����[�^��n���Ă��܂���j
//------------------------------------------------------------
//IF_BENCH_DAMAGE_MAX		flag,adrs
static	void	AI_IF_BENCH_DAMAGE_MAX(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				i,j;
	int				flag;
	int				adrs;
	int				client_no;
	s32				max_damage;
	s32				ret_damage;
	s32				damage[4];
	u16				waza[4];
	u8				power_rnd[6];
	POKEMON_PARAM	*pp;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_BENCH_DAMAGE_MAX flag:%d adrs:%d\n",flag,adrs);
#endif

	client_no=sp->AIWT.AI_AttackClient;

	for(i=0;i<6;i++){
		power_rnd[i]=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_hp_rnd+i,NULL);
	}
	max_damage=AICompPowerCalc(bw,sp,sp->AIWT.AI_AttackClient,&sp->psp[client_no].waza[0],&damage[0],
							   sp->psp[client_no].item,&power_rnd[0],
							   ST_ServerTokuseiGet(sp,client_no),
							   sp->psp[client_no].wkw.shutout_count,flag);
	for(i=0;i<BattleWorkPokeCountGet(bw,client_no);i++){
		if(i!=sp->sel_mons_no[client_no]){
			pp=BattleWorkPokemonParamGet(bw,client_no,i);
			if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
				for(j=0;j<WAZA_TEMOTI_MAX;j++){
					waza[j]=PokeParaGet(pp,ID_PARA_waza1+j,NULL);
				}
				for(j=0;j<6;j++){
					power_rnd[j]=PokeParaGet(pp,ID_PARA_hp_rnd+j,NULL);
				}
				ret_damage=AICompPowerCalc(bw,sp,sp->AIWT.AI_AttackClient,&waza[0],&damage[0],
										   PokeParaGet(pp,ID_PARA_item,NULL),&power_rnd[0],
										   PokeParaGet(pp,ID_PARA_speabino,NULL),0,flag);
				if(ret_damage>max_damage){
					AISeqInc(sp,adrs);
					break;
				}
			}
		}
	}
}

//------------------------------------------------------------
//
//	���Q�̋Z�������Ă��邩�`�F�b�N
//
//	@param	adrs	�����Ă����Ƃ��̂Ƃѐ�
//
//------------------------------------------------------------
//IF_HAVE_BATSUGUN		adrs
static	void	AI_IF_HAVE_BATSUGUN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HAVE_BATSUGUN adrs:%d\n",adrs);
#endif

	if(ClientAIBatsugunCheck(bw,sp,sp->AIWT.AI_AttackClient,1)==TRUE){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�w�肵������̍Ō�ɏo�����Z�Ǝ����̋Z�Ƃ̃_���[�W���`�F�b�N
//------------------------------------------------------------
//IF_LAST_WAZA_DAMAGE_CHECK	side,flag,adrs
static	void	AI_IF_LAST_WAZA_DAMAGE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	side;
	int	flag;
	int	adrs;
	int	client_no;
	int	loss;
	s32	max_damage;
	s32	ret_damage;
	s32	damage[4];
	u8	power_rnd[6];

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_LAST_WAZA_DAMAGE_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	for(i=0;i<6;i++){
		power_rnd[i]=ST_ServerPokemonServerParamGet(sp,sp->AIWT.AI_AttackClient,ID_PSP_hp_rnd+i,NULL);
	}

	max_damage=AICompPowerCalc(bw,sp,sp->AIWT.AI_AttackClient,&sp->psp[sp->AIWT.AI_AttackClient].waza[0],&damage[0],
							   sp->psp[sp->AIWT.AI_AttackClient].item,&power_rnd[0],
							   ST_ServerTokuseiGet(sp,sp->AIWT.AI_AttackClient),
							   sp->psp[sp->AIWT.AI_AttackClient].wkw.shutout_count,flag);

	client_no=SideToClientNo(sp,side);

	if(flag==LOSS_CALC_ON){
		loss=sp->AIWT.AI_DAMAGELOSS[sp->AIWT.AI_WAZAPOS];
	}
	else{
		loss=100;
	}

	ret_damage=AIWazaDamageCalc(bw,sp,sp->waza_no_old[client_no],sp->psp[client_no].item,&power_rnd[0],client_no,
								ST_ServerTokuseiGet(sp,client_no),sp->psp[client_no].wkw.shutout_count,loss);

	if(ret_damage>max_damage){
		AISeqInc(sp,adrs);
	}
}
//------------------------------------------------------------
//	�w�肵������̃X�e�[�^�X�㏸���̒l���擾
//------------------------------------------------------------
//CHECK_STATUS_UP		side
static	void	AI_CHECK_STATUS_UP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_STATUS_UP side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);
	sp->AIWT.AI_CALC_WORK=0;

	for(i=COND_HP;i<COND_MAX;i++){
		if(sp->psp[client_no].abiritycnt[i]>6){
			sp->AIWT.AI_CALC_WORK+=sp->psp[client_no].abiritycnt[i]-6;
		}
	}
}

//------------------------------------------------------------
//	�w�肵������Ƃ̃X�e�[�^�X�������擾
//------------------------------------------------------------
//CHECK_STATUS_DIFF		side,flag
static	void	AI_CHECK_STATUS_DIFF(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_STATUS_DIFF side:%d flag:%d\n",side,flag);
#endif

	client_no=SideToClientNo(sp,side);

	sp->AIWT.AI_CALC_WORK=sp->psp[client_no].abiritycnt[flag]-sp->psp[sp->AIWT.AI_AttackClient].abiritycnt[flag];
}
//------------------------------------------------------------
//	�w�肵������Ƃ̃X�e�[�^�X���`�F�b�N���ĕ���
//------------------------------------------------------------
//��������
//IF_CHECK_STATUS_UNDER		side,flag,adrs
//��������
//IF_CHECK_STATUS_OVER		side,flag,adrs
//�����l
//IF_CHECK_STATUS_EQUAL		side,flag,adrs
static	void	AI_IF_CHECK_STATUS_UNDER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	adrs;
	int	client_no;
	int	src;
	int	dest;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_CHECK_STATUS_UNDER side:%d flag:%d adrs:%d\n",side,flag,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	AI_IF_CHECK_STATUS_GET(sp,client_no,&src,&dest,flag);

	if(src<dest){
		AISeqInc(sp,adrs);
	}
}

static	void	AI_IF_CHECK_STATUS_OVER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	adrs;
	int	client_no;
	int	src;
	int	dest;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_CHECK_STATUS_UNDER side:%d flag:%d adrs:%d\n",side,flag,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	AI_IF_CHECK_STATUS_GET(sp,client_no,&src,&dest,flag);

	if(src>dest){
		AISeqInc(sp,adrs);
	}
}

static	void	AI_IF_CHECK_STATUS_EQUAL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	adrs;
	int	client_no;
	int	src;
	int	dest;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_CHECK_STATUS_UNDER side:%d flag:%d adrs:%d\n",side,flag,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	AI_IF_CHECK_STATUS_GET(sp,client_no,&src,&dest,flag);

	if(src==dest){
		AISeqInc(sp,adrs);
	}
}

static	void	AI_IF_CHECK_STATUS_GET(SERVER_PARAM *sp,int client_no,int *src,int *dest,int flag)
{
	switch(flag){
	case COND_HP:
		src[0]=sp->psp[sp->AIWT.AI_AttackClient].hp;
		dest[0]=sp->psp[client_no].hp;
		break;
	case COND_POW:
		src[0]=sp->psp[sp->AIWT.AI_AttackClient].pow;
		dest[0]=sp->psp[client_no].pow;
		break;
	case COND_DEF:
		src[0]=sp->psp[sp->AIWT.AI_AttackClient].def;
		dest[0]=sp->psp[client_no].def;
		break;
	case COND_SPEPOW:
		src[0]=sp->psp[sp->AIWT.AI_AttackClient].spepow;
		dest[0]=sp->psp[client_no].spepow;
		break;
	case COND_SPEDEF:
		src[0]=sp->psp[sp->AIWT.AI_AttackClient].spedef;
		dest[0]=sp->psp[client_no].spedef;
		break;
	case COND_AGI:
		src[0]=sp->psp[sp->AIWT.AI_AttackClient].agi;
		dest[0]=sp->psp[client_no].agi;
		break;
	default:
		GF_ASSERT_MSG(0,"UNKNOWN FLAG\n"); 
		break;
	}
}
//------------------------------------------------------------
//
//	�З͂���ԍ������̃`�F�b�N�i�p�[�g�i�[���܂ށj
//
//	@param		flag	�_���[�W���X�v�Z�̂Ԃꂠ��Ȃ��t���O
//
//------------------------------------------------------------
//COMP_POWER_WITH_PARTNER		flag
static	void	AI_COMP_POWER_WITH_PARTNER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i=0,j,ok;
	s32	max_damage;
	s32	damage[4];
	int	flag;
	u8	power_rnd[6];
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//flag��ǂݍ���
	flag=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("COMP_POWER_WITH_PARTNER flag:%d\n",flag);
#endif

	j=0;
	while(NoCompPowerSeqNo[j]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==NoCompPowerSeqNo[j]){
			break;
		}
		j++;
	}
	ok=0;
	while(OkCompPowerSeqNo[ok]!=0xffff){
		if(sp->AIWT.wtd[sp->AIWT.AI_WAZANO].battleeffect==OkCompPowerSeqNo[ok]){
			break;
		}
		ok++;
	}

	if((OkCompPowerSeqNo[ok]!=0xffff)||
	  ((sp->AIWT.wtd[sp->AIWT.AI_WAZANO].damage>1)&&(NoCompPowerSeqNo[j]==0xffff))){
		client_no=sp->AIWT.AI_AttackClient;
		for(j=0;j<2;j++){
			for(i=0;i<6;i++){
				power_rnd[i]=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_hp_rnd+i,NULL);
			}
			AICompPowerCalc(bw,sp,client_no,&sp->psp[client_no].waza[0],&damage[0],
							sp->psp[client_no].item,&power_rnd[0],
							ST_ServerTokuseiGet(sp,client_no),
							sp->psp[client_no].wkw.shutout_count,flag);
			//�p�[�g�i�[���`�F�b�N���邽�߂ɁAClientNo���擾
			client_no=BattleWorkPartnerClientNoGet(bw,sp->AIWT.AI_AttackClient);
			if(j==0){
				max_damage=damage[sp->AIWT.AI_WAZAPOS];
			}
			for(i=0;i<4;i++){
				if(damage[i]>max_damage){
					break;
				}
			}
			if(i==4){
				sp->AIWT.AI_CALC_WORK=COMP_POWER_TOP;
			}
			else{
				//�g�b�v����Ȃ��Ɣ��f���ꂽ��A�p�[�g�i�[���݂�K�v�͂Ȃ��̂ŁA���[�v���甲����
				sp->AIWT.AI_CALC_WORK=COMP_POWER_NOTOP;
				break;
			}
		}
	}
	else{
		sp->AIWT.AI_CALC_WORK=COMP_POWER_NONE;
	}
}

//------------------------------------------------------------
//
//	�w�肵�����肪�m�����`�F�b�N���ĕ���
//
//	@param		side	�`�F�b�N���鑊��iCHECK_ATTACK�ACHECK_DEFENCE�͎w��ł��܂���i�m�������肦�Ȃ��j�j
//	@param		adrs	�`�F�b�N���ʂł̕����iIF_HINSHI�F�m���������� IFN_HINSHI�F�m������Ȃ������Ƃ��j
//
//------------------------------------------------------------
//IF_HINSHI		side,adrs
static	void	AI_IF_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	adrs;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_HINSHI side:%d adrs:%d\n",side,adrs);
#endif

	GF_ASSERT_MSG(side!=CHECK_ATTACK,"SIDE SET ERROR:CHECK_ATTACK\n");
	GF_ASSERT_MSG(side!=CHECK_DEFENCE,"SIDE SET ERROR:CHECK_DEFENCE\n");

	client_no=SideToClientNo(sp,side);

	if(sp->no_reshuffle_client&No2Bit(client_no)){
		AISeqInc(sp,adrs);
	}
}

//IFN_HINSHI	side,adrs
static	void	AI_IFN_HINSHI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	adrs;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_HINSHI side:%d adrs:%d\n",side,adrs);
#endif

	GF_ASSERT_MSG(side!=CHECK_ATTACK,"SIDE SET ERROR:CHECK_ATTACK\n");
	GF_ASSERT_MSG(side!=CHECK_DEFENCE,"SIDE SET ERROR:CHECK_DEFENCE\n");

	client_no=SideToClientNo(sp,side);

	if((sp->no_reshuffle_client&No2Bit(client_no))==0){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//		�|�P�����̐��ʂ̃`�F�b�N
//------------------------------------------------------------

//CHECK_POKESEX		side
static	void	AI_CHECK_POKESEX(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_POKESEX side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	sp->AIWT.AI_CALC_WORK=sp->psp[client_no].sex;
}

//------------------------------------------------------------
//		�˂����܂��J�E���^�̃`�F�b�N
//------------------------------------------------------------

//CHECK_NEKODAMASI	side
static	void	AI_CHECK_NEKODAMASI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_NEKODAMASI side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].wkw.nekodamashi_count<sp->total_turn){
		sp->AIWT.AI_CALC_WORK=0;
	}
	else{
		sp->AIWT.AI_CALC_WORK=1;
	}
}

//------------------------------------------------------------
//		�����킦��J�E���^�̃`�F�b�N
//------------------------------------------------------------

//CHECK_TAKUWAERU		side
static	void	AI_CHECK_TAKUWAERU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_TAKUWAERU side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	sp->AIWT.AI_CALC_WORK=sp->psp[client_no].wkw.takuwaeru_count;
}

//------------------------------------------------------------
//		�퓬�^�C�v�̃`�F�b�N
//------------------------------------------------------------

//CHECK_FIGHT_TYPE
static	void	AI_CHECK_FIGHT_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_FIGHT_TYPE\n");
#endif

	sp->AIWT.AI_CALC_WORK=bw->fight_type;
}

//------------------------------------------------------------
//		���T�C�N���ł���A�C�e���̃`�F�b�N
//------------------------------------------------------------

//CHECK_RECYCLE_ITEM	side
static	void	AI_CHECK_RECYCLE_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_RECYCLE_ITEM side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	sp->AIWT.AI_CALC_WORK=sp->recycle_item[client_no];
}

//------------------------------------------------------------
//	���[�N�ɓ����Ă���Z�i���o�[�̃^�C�v���`�F�b�N
//------------------------------------------------------------

//CHECK_WORKWAZA_TYPE
static	void	AI_CHECK_WORKWAZA_TYPE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WORKWAZA_TYPE\n");
#endif

	sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->AIWT.AI_CALC_WORK].wazatype;
}

//------------------------------------------------------------
//	���[�N�ɓ����Ă���Z�i���o�[�̈З͂��`�F�b�N
//------------------------------------------------------------

//CHECK_WORKWAZA_POW
static	void	AI_CHECK_WORKWAZA_POW(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WORKWAZA_POW\n");
#endif

	sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->AIWT.AI_CALC_WORK].damage;
}

//------------------------------------------------------------
//	���[�N�ɓ����Ă���Z�i���o�[�̃V�[�P���X�i���o�[���`�F�b�N
//------------------------------------------------------------

//CHECK_WORKWAZA_SEQNO
static	void	AI_CHECK_WORKWAZA_SEQNO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_WORKWAZA_SEQNO\n");
#endif

	sp->AIWT.AI_CALC_WORK=sp->AIWT.wtd[sp->AIWT.AI_CALC_WORK].battleeffect;
}

//------------------------------------------------------------
//	�܂���J�E���^���`�F�b�N
//------------------------------------------------------------

//CHECK_MAMORU_COUNT		side
static	void	AI_CHECK_MAMORU_COUNT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("CHECK_MAMORU_COUNT side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	//�O�̃^�[���ɂ܂���n���o���Ă��Ȃ��Ȃ�A�J�E���^��0
	if((sp->waza_no_mamoru[client_no]!=WAZANO_MAMORU)&&
	   (sp->waza_no_mamoru[client_no]!=WAZANO_MIKIRI)&&
	   (sp->waza_no_mamoru[client_no]!=WAZANO_KORAERU)){
		sp->AIWT.AI_CALC_WORK=0;
	}
	else{
		sp->AIWT.AI_CALC_WORK=sp->psp[client_no].wkw.success_count;
	}
}

//------------------------------------------------------------
//	�ėp�I�Ȗ��ߌQ
//------------------------------------------------------------
//GOSUB		adrs
static	void	AI_GOSUB(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("GOSUB adrs:%d\n",adrs);
#endif

	AIPushAdrsSet(bw,sp,adrs);
}

//JUMP		adrs
static	void	AI_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("JUMP adrs:%d\n",adrs);
#endif

	AISeqInc(sp,adrs);
}

//AIEND
static	void	AI_AIEND(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

#ifdef DEBUG_PRINT_AI
	OS_Printf("AIEND\n");
#endif

	if(AIPopAdrsAct(bw,sp)==TRUE){
		return;
	}
	sp->AIWT.AI_STATUSFLAG|=AI_STATUSFLAG_END;
}

//------------------------------------------------------------
//	���݂��̃��x�����`�F�b�N���ĕ���
//------------------------------------------------------------

//IF_LEVEL		value,adrs
static	void	AI_IF_LEVEL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	value;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//value��ǂݍ���
	value=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_LEVEL value:%d adrs:%d\n",value,adrs);
#endif

	switch(value){
	case LEVEL_ATTACK:
		if(sp->psp[sp->AIWT.AI_AttackClient].level>sp->psp[sp->AIWT.AI_DefenceClient].level){
			AISeqInc(sp,adrs);
		}
		break;
	case LEVEL_DEFENCE:
		if(sp->psp[sp->AIWT.AI_AttackClient].level<sp->psp[sp->AIWT.AI_DefenceClient].level){
			AISeqInc(sp,adrs);
		}
		break;
	case LEVEL_EQUAL:
		if(sp->psp[sp->AIWT.AI_AttackClient].level==sp->psp[sp->AIWT.AI_DefenceClient].level){
			AISeqInc(sp,adrs);
		}
		break;
	default:
		OS_Printf("�����ɂ���̂́A��������\n");
		break;
	}
}

//------------------------------------------------------------
//	������Ԃ��`�F�b�N���ĕ���
//------------------------------------------------------------

//IF_CHOUHATSU	adrs
static	void	AI_IF_CHOUHATSU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_CHOUHATSU adrs:%d\n",adrs);
#endif

	if(sp->psp[sp->AIWT.AI_DefenceClient].wkw.chouhatsu_count){
		AISeqInc(sp,adrs);
	}
}

//IFN_CHOUHATSU	adrs
static	void	AI_IFN_CHOUHATSU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IFN_CHOUHATSU adrs:%d\n",adrs);
#endif

	if(sp->psp[sp->AIWT.AI_DefenceClient].wkw.chouhatsu_count==0){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�U���Ώۂ��������ǂ����`�F�b�N���ĕ���
//------------------------------------------------------------

// IF_MIKATA_ATTACK	adrs
static	void AI_IF_MIKATA_ATTACK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_MIKATA_ATTACK adrs:%d\n",adrs);
#endif

	if((sp->AIWT.AI_AttackClient&1)==(sp->AIWT.AI_DefenceClient&1)){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	���łɁu���炢�сv�Ńp���[�A�b�v��Ԃɂ��邩�`�F�b�N���ĕ���
//------------------------------------------------------------
//IF_ALREADY_MORAIBI		side, adrs
static	void	AI_IF_ALREADY_MORAIBI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

	//adrs��ǂݍ���
	adrs=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("IF_ALREADY_MORAIBI side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideToClientNo(sp,side);

	if(sp->psp[client_no].wkw.moraibi_flag){
		AISeqInc(sp,adrs);
	}
}

//------------------------------------------------------------
//	�Z���ʂ��l�����ē������擾�i�ړ��|�P������p�j
//------------------------------------------------------------
//GET_TOKUSEI		side
static	void	AI_GET_TOKUSEI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	AISeqInc(sp,1);

	//side��ǂݍ���
	side=AISeqDataRead(sp);

#ifdef DEBUG_PRINT_AI
	OS_Printf("GET_TOKUSEI side:%d\n",side);
#endif

	client_no=SideToClientNo(sp,side);

	sp->AIWT.AI_CALC_WORK=ST_ServerTokuseiGet(sp,client_no);
}
//--------------------- AI�p�T�u���[�`���Q ------------------------

static	void	AIPushAdrsSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int adrs)
{
	sp->AIWT.PushAdrsBuf[sp->AIWT.PushAdrsCnt++]=sp->AISeqAdrs;
	AISeqInc(sp,adrs);

	//�J�E���^�[�̃I�[�o�[�t���[���Ď�
	GF_ASSERT(sp->AIWT.PushAdrsCnt<=8);
}

static	BOOL	AIPopAdrsAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->AIWT.PushAdrsCnt){
		sp->AIWT.PushAdrsCnt--;
		sp->AISeqAdrs=sp->AIWT.PushAdrsBuf[sp->AIWT.PushAdrsCnt];
		return TRUE;
	}
	else{
		return FALSE;
	}
}

//------------------------------------------------------------
//	�O������J�Ȋ֐��Q
//------------------------------------------------------------
static	void	WazaNoStock(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;

	for(i=0;i<4;i++){
		if(sp->AIWT.AI_DEFENCE_USE_WAZA[sp->AIWT.AI_DefenceClient][i]==sp->waza_no_old[sp->AIWT.AI_DefenceClient]){
			break;
		}
		if(sp->AIWT.AI_DEFENCE_USE_WAZA[sp->AIWT.AI_DefenceClient][i]==0){
			sp->AIWT.AI_DEFENCE_USE_WAZA[sp->AIWT.AI_DefenceClient][i]=sp->waza_no_old[sp->AIWT.AI_DefenceClient];
			break;
		}
	}
}

//============================================================================================
/**
 *	�V�[�P���X�f�[�^���[�N����f�[�^�����[�h
 *
 * @param[in]	sp	�T�[�o���[�N�\����
 */
//============================================================================================
static	int		AISeqDataRead(SERVER_PARAM *sp)
{
	int	data;

	data=sp->AISeqWork[sp->AISeqAdrs];
	sp->AISeqAdrs++;

	return	data;
}

//============================================================================================
/**
 *	�V�[�P���X�f�[�^���[�N����f�[�^�����[�h
 *
 * @param[in]	sp	�T�[�o���[�N�\����
 * @param[in]	ofs	���[�h����z��ւ̃I�t�Z�b�g
 */
//============================================================================================
static	int		AISeqDataReadOfs(SERVER_PARAM *sp,int ofs)
{
	return sp->AISeqWork[sp->AISeqAdrs+ofs];
}

//============================================================================================
/**
 *	�V�[�P���X�f�[�^�C���f�b�N�X���C���N�������g
 *
 * @param[in]	sp	�T�[�o���[�N�\����
 * @param[in]	cnt	�C���N�������g���鐔
 */
//============================================================================================
static	void	AISeqInc(SERVER_PARAM *sp,int cnt)
{
	sp->AISeqAdrs+=cnt;
}

//============================================================================================
/**
 *	�`�F�b�N����ClientNo���擾
 *
 * @param[in]	sp		�T�[�o���[�N�\����
 * @param[in]	side	�擾������ClientNo
 */
//============================================================================================
static u8 SideToClientNo(SERVER_PARAM *sp,u8 side)
{
	u8 clientno;

	switch(side){
	case CHECK_ATTACK:
		clientno=sp->AIWT.AI_AttackClient;
		break;
	case CHECK_DEFENCE:
	default:
		clientno=sp->AIWT.AI_DefenceClient;
		break;
	case CHECK_ATTACK_FRIEND:
		clientno=sp->AIWT.AI_AttackClient^2;
		break;
	case CHECK_DEFENCE_FRIEND:
		clientno=sp->AIWT.AI_DefenceClient^2;
		break;
	}
	return clientno;
}

//============================================================================================
/**
 *	CompPower�v�Z������
 *
 *	@param[in]	bw			�퓬�V�X�e�����[�N�\����
 *	@param[in]	sp			�T�[�o�[�V�X�e�����[�N�\����
 *	@param[in]	attack		�U����ClientNo
 *	@param[in]	waza		�Z�i���o�[�i�[���[�N
 *	@param[out]	damage		�_���[�W�ʊi�[���[�N
 *	@param[in]	item_no		�����A�C�e��
 *	@param[in]	power_rnd	�p���[�����i�[���[�N
 *	@param[in]	tokusei		����
 *	@param[in]	shutout		�V���b�g�A�E�g����
 *	@param[in]	loss_flag	�_���[�W���X�̌v�Z�̗L��
 *
 * @retval	�ő�_���[�W�̒l
 */
//============================================================================================
static s32 AICompPowerCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 *waza,s32 *damage,u16 item_no,u8 *power_rnd,
						   int tokusei,int shutout,int loss_flag)
{
	int	i,j;
	int	ok;
	int	dir;
	int	pow,type;
	u32	flag;
	s32	max_damage;
	u8	loss;

	max_damage=0;

	for(i=0;i<4;i++){
		j=0;
		while(NoCompPowerSeqNo[j]!=0xffff){
			if(sp->AIWT.wtd[waza[i]].battleeffect==NoCompPowerSeqNo[j]){
				break;
			}
			j++;
		}
		ok=0;
		while(OkCompPowerSeqNo[ok]!=0xffff){
			if(sp->AIWT.wtd[waza[i]].battleeffect==OkCompPowerSeqNo[ok]){
				break;
			}
			ok++;
		}
		if((OkCompPowerSeqNo[ok]!=0xffff)||
		  ((waza[i]!=0)&&
		   (NoCompPowerSeqNo[j]==0xffff)&&
		   (sp->AIWT.wtd[waza[i]].damage>1))){
			if(loss_flag==LOSS_CALC_ON){
				loss=sp->AIWT.AI_DAMAGELOSS[i];
			}
			else{
				loss=100;
			}
			damage[i]=AIWazaDamageCalc(bw,sp,waza[i],item_no,power_rnd,attack,
									   tokusei,shutout,loss);
		}
		else{
			damage[i]=0;
		}
	}

	for(i=0;i<4;i++){
		if(max_damage<damage[i]){
			max_damage=damage[i];
		}
	}

	return max_damage;
}

//============================================================================================
/**
 *	��������З̓e�[�u��
 */
//============================================================================================

enum{
	KT_WEIGHT=0,
	KT_POWER,
	KT_MAX
};

static	const	u16	KetaguriTable[][KT_MAX]={
	{   100,    20},
	{   250,    40},
	{   500,    60},
	{  1000,    80},
	{  2000,   100},
	{0xffff,0xffff},
};

//============================================================================================
/**
 *	�Z�̃_���[�W�ʌv�Z������
 *
 *	@param[in]	bw			�퓬�V�X�e�����[�N�\����
 *	@param[in]	sp			�T�[�o�[�V�X�e�����[�N�\����
 *	@param[in]	waza		�Z�i���o�[
 *	@param[in]	item_no		�����A�C�e��
 *	@param[in]	power_rnd	�p���[�����i�[���[�N
 *	@param[in]	client_no	�U����ClientNo
 *	@param[in]	tokusei		����
 *	@param[in]	shutout		�V���b�g�A�E�g����
 *	@param[in]	loss		�_���[�W���X�l
 *
 * @retval	�ő�_���[�W�̒l
 */
//============================================================================================
static	s32	AIWazaDamageCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza,u16 item_no,u8 *power_rnd,int client_no,int tokusei,int shutout,u8 loss)
{
	int	dir;
	int	pow;
	int	type;
	int	typetmp;
	u32 flag;
	s32	damage;

	dir=BattleWorkMineEnemyCheck(bw,sp->AIWT.AI_DefenceClient);
	damage=0;
	pow=0;
	type=0;
	flag=0;

	//�З͂ƃ^�C�v������Ȍv�Z�ɂ�����
	switch(waza){
	case WAZANO_SIZENNOMEGUMI:
		if((tokusei!=TOKUSYU_BUKIYOU)&&(shutout==0)){
//			pow=ItemParamGet(item_no,ITEM_PRM_SIZENNOMEGUMI_ATC,HEAPID_BATTLE);
			pow=ST_ItemParamGet(sp,item_no,ITEM_PRM_SIZENNOMEGUMI_ATC);
			if(pow){
//				type=ItemParamGet(item_no,ITEM_PRM_SIZENNOMEGUMI_TYPE,HEAPID_BATTLE);
				type=ST_ItemParamGet(sp,item_no,ITEM_PRM_SIZENNOMEGUMI_TYPE);
			}
			else{
				type=0;
			}
		}
		break;
	case WAZANO_SABAKINOTUBUTE:
		if((tokusei!=TOKUSYU_BUKIYOU)&&(shutout==0)){
			pow=0;
//			switch(ItemParamGet(item_no,ITEM_PRM_EQUIP,HEAPID_BATTLE)){
			switch(ST_ItemParamGet(sp,item_no,ITEM_PRM_EQUIP)){
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
		}
		break;
	case WAZANO_MEZAMERUPAWAA:
		pow=((power_rnd[0]&2)	>>1)|
			((power_rnd[1]&2)	>>0)|
			((power_rnd[2]&2)	<<1)|
			((power_rnd[3]&2)	<<2)|
			((power_rnd[4]&2)	<<3)|
			((power_rnd[5]&2)	<<4);
		type=((power_rnd[0]&1)	>>0)|
			 ((power_rnd[1]&1)	<<1)|
			 ((power_rnd[2]&1)	<<2)|
			 ((power_rnd[3]&1)	<<3)|
			 ((power_rnd[4]&1)	<<4)|
			 ((power_rnd[5]&1)	<<5);

		pow=pow*40/63+30;
		type=(type*15/63)+1;

		if(type>=HATE_TYPE){
			type++;
		}
		break;
	case WAZANO_ZYAIROBOORU:
		pow=1+25*sp->psp_agi_point[sp->AIWT.AI_DefenceClient]/sp->psp_agi_point[client_no];
		if(pow>150){
			pow=150;
		}
		type=0;
		break;
	case WAZANO_RYUUNOIKARI:
		damage=40;
		break;
	case WAZANO_TIKYUUNAGE:
	case WAZANO_NAITOHEDDO:
		damage=sp->psp[client_no].level;
		break;
	case WAZANO_SAIKOWHEEBU:
		damage=sp->psp[client_no].level*(gf_rand()%11+5)/10;
		break;
	case WAZANO_ONGAESI:
		pow=sp->psp[client_no].friend*10/25;
		type=0;
		break;
	case WAZANO_YATUATARI:
		pow=(FRIEND_MAX-sp->psp[client_no].friend)*10/25;
		type=0;
		break;
	case WAZANO_MAGUNITYUUDO:
		pow=gf_rand()%100;
		if(pow<5){
			pow=10;
		}
		else if(pow<15){
			pow=30;
		}
		else if(pow<35){
			pow=50;
		}
		else if(pow<65){
			pow=70;
		}
		else if(pow<85){
			pow=90;
		}
		else if(pow<95){
			pow=110;
		}
		else{
			pow=150;
		}
		type=0;
		break;
	case WAZANO_SONIKKUBUUMU:
		damage=20;
		break;
	case WAZANO_KETAGURI:
	case WAZANO_KUSAMUSUBI:
		{
			int	cnt;

			cnt=0;

			while(KetaguriTable[cnt][KT_WEIGHT]!=0xffff){
				if(KetaguriTable[cnt][KT_WEIGHT]>=sp->psp[sp->AIWT.AI_DefenceClient].weight){
					break;
				}
				cnt++;
			}

			if(KetaguriTable[cnt][KT_WEIGHT]!=0xffff){
				pow=KetaguriTable[cnt][KT_POWER];
			}
			else{
				pow=120;
			}
		}
		break;
	default:
		pow=0;
		type=0;
		break;
	}

	if(damage==0){
		damage=ST_WazaDamageCalc(bw,sp,
							 	 waza,
								 sp->side_condition[dir],
								 sp->field_condition,
								 pow,
								 type,
								 client_no,
								 sp->AIWT.AI_DefenceClient,
								 1);
	}
	else{
		sp->server_status_flag|=SERVER_STATUS_FLAG_TYPE_FLAT;
	}
	damage=ST_ServerTypeCheck(bw,sp,
							  waza,
							  type,
							  client_no,
							  sp->AIWT.AI_DefenceClient,
							  damage,
							  &flag);
	sp->server_status_flag&=SERVER_STATUS_FLAG_TYPE_FLAT_OFF;
	if(flag&(WAZA_STATUS_FLAG_KOUKANAI|WAZA_STATUS_FLAG_JIMEN_NOHIT|
			 WAZA_STATUS_FLAG_DENZIHUYUU_NOHIT|WAZA_STATUS_FLAG_BATSUGUN_NOHIT)){
		damage=0;
	}
	else{
		damage=ST_ServerDamageDiv(damage*loss,100);
	}

	return damage;
}

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
static	int		AIWazaTypeGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no)
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
static	int		AIWazaTypeGetPP(BATTLE_WORK *bw,SERVER_PARAM *sp,POKEMON_PARAM *pp,int waza_no)
{
	int	type;

	switch(waza_no){
	case WAZANO_SIZENNOMEGUMI:
		type=ST_ItemParamGet(sp,PokeParaGet(pp,ID_PARA_item,NULL),ITEM_PRM_SIZENNOMEGUMI_TYPE);
		break;
	case WAZANO_SABAKINOTUBUTE:
		switch(ST_ItemParamGet(sp,PokeParaGet(pp,ID_PARA_item,NULL),ITEM_PRM_EQUIP)){
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
		type=	((PokeParaGet(pp,ID_PARA_hp_rnd,	NULL)&1)	>>0)|
				((PokeParaGet(pp,ID_PARA_pow_rnd,	NULL)&1)	<<1)|
				((PokeParaGet(pp,ID_PARA_def_rnd,	NULL)&1)	<<2)|
				((PokeParaGet(pp,ID_PARA_agi_rnd,	NULL)&1)	<<3)|
				((PokeParaGet(pp,ID_PARA_spepow_rnd,NULL)&1)	<<4)|
				((PokeParaGet(pp,ID_PARA_spedef_rnd,NULL)&1)	<<5);

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
//----------------------------------------------------------
//			AI���[�`��
//----------------------------------------------------------
//============================================================================================
/**
 *	�ق�т̂����J�E���^�`�F�b�N
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIHorobinoutaCheck(SERVER_PARAM *sp,int client_no)
{
	if((sp->psp[client_no].waza_kouka&WAZAKOUKA_HOROBINOUTA)&&
	   (sp->psp[client_no].wkw.horobinouta_count==0)){
		sp->ai_reshuffle_sel_mons_no[client_no]=6;
		return TRUE;
	}
	return FALSE;
}

//============================================================================================
/**
 *	�ӂ����Ȃ܂���`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIHusiginamamoriCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	i,j;
	u16	wazano;
	int	type;
	u32	flag;
	POKEMON_PARAM	*pp;

	//2vs2�̓`�F�b�N���Ȃ�
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
		return FALSE;
	}

	if(sp->psp[client_no^1].speabino==TOKUSYU_HUSIGINAMAMORI){
		for(i=0;i<4;i++){
			wazano=sp->psp[client_no].waza[i];
			type=AIWazaTypeGet(bw,sp,client_no,wazano);
			if(wazano){
				flag=0;
				ST_ServerTypeCheck(bw,sp,wazano,type,client_no,client_no^1,0,&flag);
				if(flag&WAZA_STATUS_FLAG_BATSUGUN){
					return FALSE;
				}
			}
		}
		for(i=0;i<BattleWorkPokeCountGet(bw,client_no);i++){
			pp=BattleWorkPokemonParamGet(bw,client_no,i);
			if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
			   (i!=sp->sel_mons_no[client_no])){
				for(j=0;j<WAZA_TEMOTI_MAX;j++){
					wazano=PokeParaGet(pp,ID_PARA_waza1+j,NULL);
					type=AIWazaTypeGetPP(bw,sp,pp,wazano);
					if(wazano){
						flag=0;
						ST_AITypeCheck(sp,wazano,type,
									   PokeParaGet(pp,ID_PARA_speabino,NULL),
									   ST_ServerTokuseiGet(sp,client_no^1),
									   ST_ServerSoubiEqpGet(sp,client_no^1),
									   ST_ServerPokemonServerParamGet(sp,client_no^1,ID_PSP_type1,NULL),
									   ST_ServerPokemonServerParamGet(sp,client_no^1,ID_PSP_type2,NULL),
									   &flag);
						if(flag&WAZA_STATUS_FLAG_BATSUGUN){
							if((gf_rand()%3)<2){
								sp->ai_reshuffle_sel_mons_no[client_no]=i;
								return TRUE;
							}
						}
					}
				}
			}
		}
//2vs2�̓`�F�b�N���Ȃ��̂ŁA���̃��[�`���ł͂Ȃ��͂�
#if 0
		if((FightType&FIGHT_TYPE_TAG)||(FightType&FIGHT_TYPE_TOWER_MULTI)){
			if((ClientNo&2)==0){
				start_no=0;
				end_no=3;
			}
			else{
				start_no=3;
				end_no=6;
			}
		}
		else{
			start_no=0;
			end_no=6;
		}
		if(MineEnemyCheck(ClientNo)==SIDE_MINE){
			PP=&PokeParaMine[0];
		}
		else{
			PP=&PokeParaEnemy[0];
		}
		for(i=start_no;i<end_no;i++){
			if((PokeParaGet(&PP[i],ID_hp)!=0)&&
			   (PokeParaGet(&PP[i],ID_monsno_egg)!=0)&&
			   (PokeParaGet(&PP[i],ID_monsno_egg)!=MONSNO_TAMAGO)&&
			   (i!=SelMonsNo[ClientNo])){
				monsno=PokeParaGet(&PP[i],ID_monsno);
				if(PokeParaGet(&PP[i],ID_speabi))
					speabino=PPD[monsno].speabi2;
				else
					speabino=PPD[monsno].speabi1;
				clientno=ClientNoGet(clienttype);
				for(j=0;j<4;j++){
					wazano=PokeParaGet(&PP[i],ID_waza1+j);
					if(wazano){
						flag=TypeCheckAct2(wazano,
										   PSP[clientno].monsno,
										   PSP[clientno].speabino);
						if(flag&WAZASTATUSFLAG_BATSUGUN){
							if((pp_rand()%3)<2){
								BattleWork_P[AI_RESHUFFLE_SELNO+ClientNo]=i;
								BSS_SELECT_RETURN_SET(BSS_CLIENT,BSS_SELECT_RETURN_POKE,0);
								return 1;
							}
						}
					}
				}
			}
		}
#endif
	}
	return FALSE;
}

//============================================================================================
/**
 *	���o�Ă���|�P���������ʂȂ��̋Z���������Ă��Ȃ��ꍇ�̌��`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIKoukanaiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	i,j;
	u8	cl1,cl2;
	u8	no1,no2;
	u16	wazano;
	int	type;
	u32	flag;
	int	start_no,end_no;
	int	waza_cnt;
	POKEMON_PARAM	*pp;

	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
		cl1=CLIENT_NO_MINE;
		cl2=CLIENT_NO_MINE2;
	}
	else{
		cl1=CLIENT_NO_MINE;
		cl2=CLIENT_NO_MINE;
	}

	waza_cnt=0;
	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		wazano=sp->psp[client_no].waza[i];
		type=AIWazaTypeGet(bw,sp,client_no,wazano);
		if((wazano)&&(sp->AIWT.wtd[wazano].damage)){
			waza_cnt++;
			flag=0;
			if(sp->psp[cl1].hp){
				ST_ServerTypeCheck(bw,sp,wazano,type,client_no,cl1,0,&flag);
			}
			if((flag&WAZA_STATUS_FLAG_KOUKANAI)==0){
				return FALSE;
			}
			flag=0;
			if(sp->psp[cl2].hp){
				ST_ServerTypeCheck(bw,sp,wazano,type,client_no,cl2,0,&flag);
			}
			if((flag&WAZA_STATUS_FLAG_KOUKANAI)==0){
				return FALSE;
			}
		}
	}
	//�U���Z��2�ȏ㎝���Ă��Ȃ��ꍇ�́A���ꂩ���Ȃ��i�˂΂�n�̃|�P�����Ɣ��f�j
	if(waza_cnt<2){
		return FALSE;
	}

	no1=client_no;
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)||
	   (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)){
		no2=no1;
	}
	else{
		no2=BattleWorkPartnerClientNoGet(bw,client_no);
	}

	start_no=0;
	end_no=BattleWorkPokeCountGet(bw,client_no);

	//���Q�`�F�b�N
	for(i=start_no;i<end_no;i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
		   (i!=sp->sel_mons_no[no1])&&(i!=sp->sel_mons_no[no2])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
			for(j=0;j<WAZA_TEMOTI_MAX;j++){
				wazano=PokeParaGet(pp,ID_PARA_waza1+j,NULL);
				type=AIWazaTypeGetPP(bw,sp,pp,wazano);
				if((wazano)&&(sp->AIWT.wtd[wazano].damage)){
					flag=0;
					if(sp->psp[cl1].hp){
						ST_AITypeCheck(sp,wazano,type,
									   PokeParaGet(pp,ID_PARA_speabino,NULL),
									   ST_ServerTokuseiGet(sp,cl1),
									   ST_ServerSoubiEqpGet(sp,cl1),
									   ST_ServerPokemonServerParamGet(sp,cl1,ID_PSP_type1,NULL),
									   ST_ServerPokemonServerParamGet(sp,cl1,ID_PSP_type2,NULL),
									   &flag);
					}
					if(flag&WAZA_STATUS_FLAG_BATSUGUN){
						if((gf_rand()%3)<2){
							sp->ai_reshuffle_sel_mons_no[client_no]=i;
							return TRUE;
						}

					}
					flag=0;
					if(sp->psp[cl2].hp){
						ST_AITypeCheck(sp,wazano,type,
									   PokeParaGet(pp,ID_PARA_speabino,NULL),
									   ST_ServerTokuseiGet(sp,cl2),
									   ST_ServerSoubiEqpGet(sp,cl2),
									   ST_ServerPokemonServerParamGet(sp,cl2,ID_PSP_type1,NULL),
									   ST_ServerPokemonServerParamGet(sp,cl2,ID_PSP_type2,NULL),
									   &flag);
					}
					if(flag&WAZA_STATUS_FLAG_BATSUGUN){
						if((gf_rand()%3)<2){
							sp->ai_reshuffle_sel_mons_no[client_no]=i;
							return TRUE;
						}

					}
				}
			}
		}
	}
	//���{�`�F�b�N
	for(i=start_no;i<end_no;i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
		   (i!=sp->sel_mons_no[no1])&&(i!=sp->sel_mons_no[no2])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
			for(j=0;j<WAZA_TEMOTI_MAX;j++){
				wazano=PokeParaGet(pp,ID_PARA_waza1+j,NULL);
				type=AIWazaTypeGetPP(bw,sp,pp,wazano);
				if((wazano)&&(sp->AIWT.wtd[wazano].damage)){
					flag=0;
					if(sp->psp[cl1].hp){
						ST_AITypeCheck(sp,wazano,type,
									   PokeParaGet(pp,ID_PARA_speabino,NULL),
									   ST_ServerTokuseiGet(sp,cl1),
									   ST_ServerSoubiEqpGet(sp,cl1),
									   ST_ServerPokemonServerParamGet(sp,cl1,ID_PSP_type1,NULL),
									   ST_ServerPokemonServerParamGet(sp,cl1,ID_PSP_type2,NULL),
									   &flag);
					}
					if(flag==0){
						if((gf_rand()%2)==0){
							sp->ai_reshuffle_sel_mons_no[client_no]=i;
							return TRUE;
						}

					}
					flag=0;
					if(sp->psp[cl2].hp){
						ST_AITypeCheck(sp,wazano,type,
									   PokeParaGet(pp,ID_PARA_speabino,NULL),
									   ST_ServerTokuseiGet(sp,cl2),
									   ST_ServerSoubiEqpGet(sp,cl2),
									   ST_ServerPokemonServerParamGet(sp,cl2,ID_PSP_type1,NULL),
									   ST_ServerPokemonServerParamGet(sp,cl2,ID_PSP_type2,NULL),
									   &flag);
					}
					if(flag==0){
						if((gf_rand()%2)==0){
							sp->ai_reshuffle_sel_mons_no[client_no]=i;
							return TRUE;
						}

					}
				}
			}
		}
	}
	return FALSE;
}

//============================================================================================
/**
 *	���o�Ă���|�P���������ʔ��Q�̋Z�������Ă���ꍇ�͌�サ�Ȃ��`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 * @param[in]	chkflag		1�̂Ƃ������Ă��邩�����`�F�b�N���Ȃ�
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIBatsugunCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,u8 chkflag)
{
	int	i;
	u32	flag;
	u8	clientno;
	u8	clienttype;
	u16	wazano;
	int	type;

	clienttype=BattleWorkClientTypeGet(bw,client_no)^1;
	clientno=BattleWorkClientNoGet(bw,clienttype);

	if((sp->no_reshuffle_client&No2Bit(clientno))==0){
		for(i=0;i<4;i++){
			wazano=sp->psp[client_no].waza[i];
			type=AIWazaTypeGet(bw,sp,client_no,wazano);
			if(wazano){
				flag=0;
				ST_ServerTypeCheck(bw,sp,wazano,type,client_no,clientno,0,&flag);
				if(flag&WAZA_STATUS_FLAG_BATSUGUN){
					if(chkflag){
						return TRUE;
					}
					else{
						if(gf_rand()%10!=0){
							return TRUE;
						}
					}
				}
			}
		}
	}
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)==0){
		return FALSE;
	}
	clientno=BattleWorkPartnerClientNoGet(bw,clientno);
	if((sp->no_reshuffle_client&No2Bit(clientno))==0){
		for(i=0;i<4;i++){
			wazano=sp->psp[client_no].waza[i];
			type=AIWazaTypeGet(bw,sp,client_no,wazano);
			if(wazano){
				flag=0;
				ST_ServerTypeCheck(bw,sp,wazano,type,client_no,clientno,0,&flag);
				if(flag&WAZA_STATUS_FLAG_BATSUGUN){
					if(chkflag){
						return TRUE;
					}
					else{
						if(gf_rand()%10!=0){
							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}

//============================================================================================
/**
 *	�_���[�W�Z�ɑ΂���HP�񕜂�������������Ă���|�P�����̃`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIHPRecoverTokusyuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	i;
	u8	no1,no2;
	u8	wazatype;
	u8	speabino;
	u8	chkspeabino;
	int	start_no,end_no;
	POKEMON_PARAM	*pp;

	if((ClientAIBatsugunCheck(bw,sp,client_no,1))&&(gf_rand()%3!=0)){
		return FALSE;
	}

	if(sp->waza_no_hit[client_no]==0){
		return FALSE;
	}
//	if(WT_WazaDataParaGet(sp->waza_no_hit[client_no],ID_WTD_damage)==0){
	if(sp->AIWT.wtd[sp->waza_no_hit[client_no]].damage==0){
		return FALSE;
	}

//	wazatype=WT_WazaDataParaGet(sp->waza_no_hit[client_no],ID_WTD_wazatype);
	wazatype=sp->AIWT.wtd[sp->waza_no_hit[client_no]].wazatype;

	if(wazatype==FIRE_TYPE){
		chkspeabino=TOKUSYU_MORAIBI;
	}
	else if(wazatype==WATER_TYPE){
		chkspeabino=TOKUSYU_TYOSUI;
	}
	else if(wazatype==ELECTRIC_TYPE){
		chkspeabino=TOKUSYU_TIKUDEN;
	}
	else{
		return FALSE;
	}

	if(ST_ServerTokuseiGet(sp,client_no)==chkspeabino){
		return FALSE;
	}

	no1=client_no;
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)||
	   (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)){
		no2=no1;
	}
	else{
		no2=BattleWorkPartnerClientNoGet(bw,client_no);
	}

	start_no=0;
	end_no=BattleWorkPokeCountGet(bw,client_no);

	for(i=start_no;i<end_no;i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
		   (i!=sp->sel_mons_no[no1])&&(i!=sp->sel_mons_no[no2])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
			speabino=PokeParaGet(pp,ID_PARA_speabino,NULL);
			if((chkspeabino==speabino)&&(gf_rand()&1)){
				sp->ai_reshuffle_sel_mons_no[client_no]=i;
				return TRUE;
			}
		}
	}
	return FALSE;
}

//============================================================================================
/**
 *	�Z���ʃ`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 * @param[in]	wazakouka	�`�F�b�N����Z����
 * @param[in]	kakuritu	���ꂩ����m��
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,u32 wazakouka,u8 kakuritu)
{
	int	i,j;
	u8	no1,no2;
	u16	wazano;
	int	type;
	u32	flag;
	int	start_no,end_no;
	POKEMON_PARAM	*pp;

	if((sp->waza_no_hit[client_no]==0)||
	   (sp->waza_no_hit_client[client_no]==NONE_CLIENT_NO)){
		return FALSE;
	}
//	if(WT_WazaDataParaGet(sp->waza_no_hit[client_no],ID_WTD_damage)==0){
	if(sp->AIWT.wtd[sp->waza_no_hit[client_no]].damage==0){
		return FALSE;
	}

	no1=client_no;
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)||
	   (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)){
		no2=no1;
	}
	else{
		no2=BattleWorkPartnerClientNoGet(bw,client_no);
	}

	start_no=0;
	end_no=BattleWorkPokeCountGet(bw,client_no);

	for(i=start_no;i<end_no;i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
		   (i!=sp->sel_mons_no[no1])&&(i!=sp->sel_mons_no[no2])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
			flag=0;
			type=AIWazaTypeGet(bw,sp,sp->waza_no_hit_client[client_no],sp->waza_no_hit[client_no]);
			ST_AITypeCheck(sp,sp->waza_no_hit[client_no],type,
						   ST_ServerTokuseiGet(sp,sp->waza_no_hit_client[client_no]),
						   PokeParaGet(pp,ID_PARA_speabino,NULL),
						   ST_ItemParamGet(sp,PokeParaGet(pp,ID_PARA_item,NULL),ITEM_PRM_EQUIP),
						   PokeParaGet(pp,ID_PARA_type1,NULL),
						   PokeParaGet(pp,ID_PARA_type2,NULL),
						   &flag);
			if(flag&wazakouka){
				for(j=0;j<WAZA_TEMOTI_MAX;j++){
					wazano=PokeParaGet(pp,ID_PARA_waza1+j,NULL);
					type=AIWazaTypeGetPP(bw,sp,pp,wazano);
					if(wazano){
						flag=0;
						ST_AITypeCheck(sp,wazano,type,
									   PokeParaGet(pp,ID_PARA_speabino,NULL),
									   ST_ServerTokuseiGet(sp,sp->waza_no_hit_client[client_no]),
									   ST_ServerSoubiEqpGet(sp,sp->waza_no_hit_client[client_no]),
									   ST_ServerPokemonServerParamGet(sp,sp->waza_no_hit_client[client_no],ID_PSP_type1,NULL),
									   ST_ServerPokemonServerParamGet(sp,sp->waza_no_hit_client[client_no],ID_PSP_type2,NULL),
									   &flag);
						if(flag&WAZA_STATUS_FLAG_BATSUGUN){
							if((gf_rand()%kakuritu)==0){
								sp->ai_reshuffle_sel_mons_no[client_no]=i;
								return TRUE;
							}

						}
					}
				}
			}
		}
	}
	return FALSE;
}

//============================================================================================
/**
 *	���o�Ă���|�P�����������Ă��Ă����񂩂��ӂ��������Ă���ꍇ�̃`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIShizenkaifukuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	if(((sp->psp[client_no].condition&CONDITION_NEMURI)==0)||
		(ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_SIZENKAIHUKU)||
		(sp->psp[client_no].hp<(sp->psp[client_no].hpmax/2))){
		return FALSE;
	}

	if(sp->waza_no_hit[client_no]==0){
		if(gf_rand()&1){
			sp->ai_reshuffle_sel_mons_no[client_no]=6;
			return TRUE;
		}
	}
//	if(WT_WazaDataParaGet(sp->waza_no_hit[client_no],ID_WTD_damage)==0){
	if(sp->AIWT.wtd[sp->waza_no_hit[client_no]].damage==0){
		if(gf_rand()&1){
			sp->ai_reshuffle_sel_mons_no[client_no]=6;
			return 1;
		}
	}

	if(ClientAIWazaKoukaCheck(bw,sp,client_no,WAZA_STATUS_FLAG_KOUKANAI,1)){
		return TRUE;
	}
	if(ClientAIWazaKoukaCheck(bw,sp,client_no,WAZA_STATUS_FLAG_IMAHITOTSU,1)){
		return TRUE;
	}

	if(gf_rand()&1){
		sp->ai_reshuffle_sel_mons_no[client_no]=6;
		return TRUE;
	}
	return FALSE;
}

//============================================================================================
/**
 *	���o�Ă���|�P�����̃X�e�[�^�X�A�b�v�g�[�^����4�ȏ�͌�サ�Ȃ��`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:4�����@TRUE:4�ȏ�
 */
//============================================================================================
static	BOOL	ClientAIStatusUpCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	i;
	u8	cnt;

	cnt=0;

	for(i=COND_HP;i<COND_MAX;i++){
		if(sp->psp[client_no].abiritycnt[i]>6)
			cnt+=sp->psp[client_no].abiritycnt[i]-6;
	}

	return (cnt>=4);
}

//============================================================================================
/**
 *	�|�P��������ւ�AI
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	client_no	�`�F�b�N����ClientNo
 *
 * @retval	FALSE:���ꂩ���Ȃ��@TRUE:���ꂩ����
 */
//============================================================================================
static	BOOL	ClientAIPokeReshuffleAI(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	i;
	int	cnt;
	u8	no1,no2,selected;
	int	start_no,end_no;
	POKEMON_PARAM	*pp;

	if((sp->psp[client_no].condition2&(CONDITION2_SHIME|CONDITION2_KUROIMANAZASHI))||
	   (sp->psp[client_no].waza_kouka&WAZAKOUKA_NEWOHARU)||
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE,client_no,TOKUSYU_KAGEHUMI))||
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE,client_no,TOKUSYU_ARIZIGOKU))||
	  ((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE,client_no,TOKUSYU_ZIRYOKU)&&
	  ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)==METAL_TYPE)||
	  ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)==METAL_TYPE)))))){
		return FALSE;
	}

	cnt=0;

	no1=client_no;
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)||
	   (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)){
		no2=no1;
	}
	else{
		no2=BattleWorkPartnerClientNoGet(bw,client_no);
	}

	start_no=0;
	end_no=BattleWorkPokeCountGet(bw,client_no);

	for(i=start_no;i<end_no;i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
		   (i!=sp->sel_mons_no[no1])&&(i!=sp->sel_mons_no[no2])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
			cnt++;
		}
	}
	if(cnt){
		if(ClientAIHorobinoutaCheck(sp,client_no)){
			return TRUE;
		}
		if(ClientAIHusiginamamoriCheck(bw,sp,client_no)){
			return TRUE;
		}
		if(ClientAIKoukanaiCheck(bw,sp,client_no)){
			return TRUE;
		}
		if(ClientAIHPRecoverTokusyuCheck(bw,sp,client_no)){
			return TRUE;
		}
		if(ClientAIShizenkaifukuCheck(bw,sp,client_no)){
			return TRUE;
		}
		if(ClientAIBatsugunCheck(bw,sp,client_no,0)){
			return FALSE;
		}
		if(ClientAIStatusUpCheck(bw,sp,client_no)){
			return FALSE;
		}
		if(ClientAIWazaKoukaCheck(bw,sp,client_no,WAZA_STATUS_FLAG_KOUKANAI,2)){
			return TRUE;
		}
		if(ClientAIWazaKoukaCheck(bw,sp,client_no,WAZA_STATUS_FLAG_IMAHITOTSU,3)){
			return TRUE;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 *	�R�}���h�I��AI
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	client_no	�I������ClientNo
 *
 * @retval	�I�������R�}���h
 */
//============================================================================================
int	ClientAICommandSelectAI(BATTLE_WORK *bw,int client_no)
{
	int	i;
	u8	no1,no2;
	u32	fight_type;
	int start_no,end_no;
	POKEMON_PARAM	*pp;
	SERVER_PARAM	*sp;

	sp=bw->server_param;

	fight_type=BattleWorkFightTypeGet(bw);

	if((fight_type&FIGHT_TYPE_TRAINER)||((BattleWorkMineEnemyCheck(bw,client_no)==0))){
		if(ClientAIPokeReshuffleAI(bw,sp,client_no)){
			if(sp->ai_reshuffle_sel_mons_no[client_no]==6){
				if((i=ClientAIPokeSelectAI(bw,client_no))==6){

					no1=client_no;
					if((fight_type&FIGHT_TYPE_TAG)||
					   (fight_type&FIGHT_TYPE_MULTI)){
						no2=no1;
					}
					else{
						no2=BattleWorkPartnerClientNoGet(bw,client_no);
					}

					start_no=0;
					end_no=BattleWorkPokeCountGet(bw,client_no);

					for(i=start_no;i<end_no;i++){
						pp=BattleWorkPokemonParamGet(bw,client_no,i);
						if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
						   (i!=sp->sel_mons_no[no1])&&(i!=sp->sel_mons_no[no2])&&
						   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
						   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
							break;
						}
					}
				}
				sp->ai_reshuffle_sel_mons_no[client_no]=i;
			}
//			sp->reshuffle_sel_mons_no[client_no]=sp->ai_reshuffle_sel_mons_no[client_no];
			return SELECT_POKEMON_COMMAND;
		}
		if(ClientAIItemUseAI(bw,client_no)){
			return SELECT_ITEM_COMMAND;
		}
	}
	return SELECT_FIGHT_COMMAND;
}

//============================================================================================
/**
 *	�|�P�����I��AI
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	client_no	�I������ClientNo
 *
 * @retval	�I�������|�P�����̃|�W�V����
 */
//============================================================================================
int	ClientAIPokeSelectAI(BATTLE_WORK *bw,int client_no)
{
	int	i,j;
	u8	clientno;
	u8	psp_type1;
	u8	psp_type2;
	u8	type1;
	u8	type2;
	u16	monsno;
	u16	wazano;
	int	type;
	u8	checkbit;
	u8	damage;
	u8	damagetmp;
	u8	topselmons=6;
	u8	no1,no2;
	u32	flag;
	int	start_no,end_no;
	POKEMON_PARAM	*pp;
	SERVER_PARAM	*sp;

	sp=bw->server_param;

	no1=client_no;
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)||
	   (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)){
		no2=no1;
	}
	else{
		no2=BattleWorkPartnerClientNoGet(bw,client_no);
	}
	clientno=ST_ServerDirClientGet(bw,sp,client_no);

	start_no=0;
	end_no=BattleWorkPokeCountGet(bw,client_no);

	checkbit=0;
	while(checkbit!=0x3f){
		damagetmp=0;
		topselmons=6;
		for(i=start_no;i<end_no;i++){
			pp=BattleWorkPokemonParamGet(bw,client_no,i);
			monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
			if((monsno!=0)&&
			   (monsno!=MONSNO_TAMAGO)&&
			   (PokeParaGet(pp,ID_PARA_hp,NULL))&&
			  ((checkbit&No2Bit(i))==0)&&
			   (sp->sel_mons_no[no1]!=i)&&
			   (sp->sel_mons_no[no2]!=i)&&
			   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
			   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
				psp_type1=ST_ServerPokemonServerParamGet(sp,clientno,ID_PSP_type1,NULL);
				psp_type2=ST_ServerPokemonServerParamGet(sp,clientno,ID_PSP_type2,NULL);
				type1=PokeParaGet(pp,ID_PARA_type1,NULL);
				type2=PokeParaGet(pp,ID_PARA_type2,NULL);
				damage=ST_ServerTypeCheckTablePowerGet(type1,psp_type1,psp_type2);
				damage+=ST_ServerTypeCheckTablePowerGet(type2,psp_type1,psp_type2);
				if(damagetmp<damage){
					damagetmp=damage;
					topselmons=i;
				}
			}
			else{
				checkbit|=No2Bit(i);
			}
		}
		if(topselmons!=6){
			pp=BattleWorkPokemonParamGet(bw,client_no,topselmons);
			for(i=0;i<WAZA_TEMOTI_MAX;i++){
				wazano=PokeParaGet(pp,ID_PARA_waza1+i,NULL);
				type=AIWazaTypeGetPP(bw,sp,pp,wazano);
				if(wazano){
					flag=0;
					ST_AITypeCheck(sp,wazano,type,
								   PokeParaGet(pp,ID_PARA_speabino,NULL),
								   ST_ServerTokuseiGet(sp,clientno),
								   ST_ServerSoubiEqpGet(sp,clientno),
								   ST_ServerPokemonServerParamGet(sp,clientno,ID_PSP_type1,NULL),
								   ST_ServerPokemonServerParamGet(sp,clientno,ID_PSP_type2,NULL),
								   &flag);
					if(flag&WAZA_STATUS_FLAG_BATSUGUN){
						break;
					}
				}
			}
			if(i==WAZA_TEMOTI_MAX){
				checkbit|=No2Bit(topselmons);
			}
			else{
				return topselmons;
			}
		}
		else{
			checkbit=0x3f;
		}
	}

	damagetmp=0;
	topselmons=6;

	for(i=start_no;i<end_no;i++){
		pp=BattleWorkPokemonParamGet(bw,client_no,i);
		monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
		if((monsno!=0)&&
		   (monsno!=MONSNO_TAMAGO)&&
		   (PokeParaGet(pp,ID_PARA_hp,NULL))&&
		   (sp->sel_mons_no[no1]!=i)&&(sp->sel_mons_no[no2]!=i)&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no1])&&
		   (i!=sp->ai_reshuffle_sel_mons_no[no2])){
			for(j=0;j<WAZA_TEMOTI_MAX;j++){
				wazano=PokeParaGet(pp,ID_PARA_waza1+j,NULL);
				type=AIWazaTypeGetPP(bw,sp,pp,wazano);
				if((wazano)&&(sp->AIWT.wtd[wazano].damage!=1)){
					damage=ST_WazaDamageCalc(bw,sp,
											 wazano,
											 sp->side_condition[BattleWorkMineEnemyCheck(bw,clientno)],
											 sp->field_condition,
											 0,
											 0,
											 client_no,
											 clientno,
											 1);
					flag=0;
					damage=ST_ServerTypeCheck(bw,sp,
											  wazano,
											  type,
											  client_no,
											  clientno,
											  damage,
											  &flag);
					if(flag&(WAZA_STATUS_FLAG_KOUKANAI|WAZA_STATUS_FLAG_JIMEN_NOHIT|
							 WAZA_STATUS_FLAG_DENZIHUYUU_NOHIT|WAZA_STATUS_FLAG_BATSUGUN_NOHIT)){
						damage=0;
					}
				}
				if(damagetmp<damage){
					damagetmp=damage;
					topselmons=i;
				}
			}
		}
	}
	return topselmons;
}

//============================================================================================
/**
 *	AI���I�������|�P�����̈ʒu���擾
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	�I�������|�P�����̃|�W�V����
 */
//============================================================================================
int	ClientAIReshuffleSelMonsNoGet(BATTLE_WORK *bw,int client_no)
{
	return bw->server_param->ai_reshuffle_sel_mons_no[client_no];
}

//============================================================================================
/**
 *	�A�C�e���g�pAI
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	sp			�T�[�o�V�X�e�����[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	�I�������|�P�����̃|�W�V����
 */
//============================================================================================
BOOL	ClientAIItemUseAI(BATTLE_WORK *bw,int client_no)
{
	int				i;
	u8				monscnt=0;
	u16				itemno;
	u8				para;
	BOOL			ret;
	u8				*adr;
	POKEPARTY		*ppt;
	POKEMON_PARAM	*pp;
	SERVER_PARAM	*sp;

	sp=bw->server_param;
	sp->AIWT.AI_ITEM_CONDITION[client_no>>1]=0;

	ret=FALSE;

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		return ret;
	}
#endif PM_DEBUG

	//AI�}���`�̎��A�p�[�g�i�[�̓A�C�e�����g�p���Ȃ�
	if(((bw->fight_type&FIGHT_TYPE_AI_MULTI)==FIGHT_TYPE_AI_MULTI)&&
		(BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_C)){
		return ret;
	}

	//�V���b�g�A�E�g���ꂽ�|�P�����ɂ́A�A�C�e�����g���Ȃ�
	if(sp->psp[client_no].waza_kouka&WAZAKOUKA_SHUTOUT){
		return ret;
	}

	ppt=BattleWorkPokePartyGet(bw,client_no);

	for(i=0;i<PokeParty_GetPokeCount(ppt);i++){
		pp=PokeParty_GetMemberPointer(ppt,i);
		if((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
		   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
			monscnt++;
		}
	}

	for(i=0;i<4;i++){
		if((i==0)||(monscnt<=sp->AIWT.AI_ITEMCNT[client_no>>1]-i+1)){
			itemno=sp->AIWT.AI_HAVEITEM[client_no>>1][i];
			if(itemno==0){
				continue;
			}
			if(itemno==ITEM_KAIHUKUNOKUSURI){
				if((sp->psp[client_no].hp<(sp->psp[client_no].hpmax/4))&&(sp->psp[client_no].hp)){
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_KAIHUKUNOKUSURI;
					ret=TRUE;
				}
			}
//			else if(ItemParamGet(itemno,ITEM_PRM_HP_RCV,HEAPID_BATTLE)){
//				para=ItemParamGet(itemno,ITEM_PRM_HP_RCV_POINT,HEAPID_BATTLE);
			else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_HP_RCV)){
				para=ST_ItemParamGet(sp,itemno,ITEM_PRM_HP_RCV_POINT);
				if(para){
					if((sp->psp[client_no].hp)&&
					  ((sp->psp[client_no].hp<(sp->psp[client_no].hpmax/4))||
					  ((sp->psp[client_no].hpmax-sp->psp[client_no].hp)>para))){
						sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_HP_KAIHUKU;
						ret=TRUE;
					}
				}
			}
			//�����
//			else if(ItemParamGet(itemno,ITEM_PRM_SLEEP_RCV,HEAPID_BATTLE)){
			else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_SLEEP_RCV)){
				if(sp->psp[client_no].condition&CONDITION_NEMURI){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]|=No2Bit(ITEM_USE_MSG_RECV_NEMURI);
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_CONDITION_KAIHUKU;
					ret=TRUE;
				}
			}
			// �ŉ�
//			else if(ItemParamGet(itemno,ITEM_PRM_POISON_RCV,HEAPID_BATTLE)){
			else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_POISON_RCV)){
				if((sp->psp[client_no].condition&CONDITION_DOKU)||
				   (sp->psp[client_no].condition&CONDITION_DOKUDOKU)){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]|=No2Bit(ITEM_USE_MSG_RECV_DOKU);
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_CONDITION_KAIHUKU;
					ret=TRUE;
				}
			}
			// �Ώ���
//			else if(ItemParamGet(itemno,ITEM_PRM_BURN_RCV,HEAPID_BATTLE)){
			else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_BURN_RCV)){
				if(sp->psp[client_no].condition&CONDITION_YAKEDO){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]|=No2Bit(ITEM_USE_MSG_RECV_YAKEDO);
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_CONDITION_KAIHUKU;
					ret=TRUE;
				}
			}
			// �X��
//			else if(ItemParamGet(itemno,ITEM_PRM_ICE_RCV,HEAPID_BATTLE)){
			else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_ICE_RCV)){
				if(sp->psp[client_no].condition&CONDITION_KOORI){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]|=No2Bit(ITEM_USE_MSG_RECV_KOORI);
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_CONDITION_KAIHUKU;
					ret=TRUE;
				}
			}
			// ��჉�
//			else if(ItemParamGet(itemno,ITEM_PRM_PARALYZE_RCV,HEAPID_BATTLE)){
			else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_PARALYZE_RCV)){
				if(sp->psp[client_no].condition&CONDITION_MAHI){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]|=No2Bit(ITEM_USE_MSG_RECV_MAHI);
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_CONDITION_KAIHUKU;
					ret=TRUE;
				}
			}
			// ������
//			else if(ItemParamGet(itemno,ITEM_PRM_PANIC_RCV,HEAPID_BATTLE)){
			else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_PANIC_RCV)){
				if(sp->psp[client_no].condition2&CONDITION2_KONRAN){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]|=No2Bit(ITEM_USE_MSG_RECV_KONRAN);
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_CONDITION_KAIHUKU;
					ret=TRUE;
				}
			}
			else if((sp->psp[client_no].wkw.nekodamashi_count-sp->total_turn)>=0){
				// �U���̓A�b�v
//				if(ItemParamGet(itemno,ITEM_PRM_ATTACK_UP,HEAPID_BATTLE)){
				if(ST_ItemParamGet(sp,itemno,ITEM_PRM_ATTACK_UP)){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]=COND_POW;
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_ABIRITY_UP;
					ret=TRUE;
				}
				// �h��̓A�b�v
//				else if(ItemParamGet(itemno,ITEM_PRM_DEFENCE_UP,HEAPID_BATTLE)){
				else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_DEFENCE_UP)){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]=COND_DEF;
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_ABIRITY_UP;
					ret=TRUE;
				}
				// ���U�A�b�v
//				else if(ItemParamGet(itemno,ITEM_PRM_SP_ATTACK_UP,HEAPID_BATTLE)){
				else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_SP_ATTACK_UP)){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]=COND_SPEPOW;
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_ABIRITY_UP;
					ret=TRUE;
				}
				// ���h�A�b�v
//				else if(ItemParamGet(itemno,ITEM_PRM_SP_DEFENCE_UP,HEAPID_BATTLE)){
				else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_SP_DEFENCE_UP)){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]=COND_SPEDEF;
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_ABIRITY_UP;
					ret=TRUE;
				}
				// �f�����A�b�v
//				else if(ItemParamGet(itemno,ITEM_PRM_AGILITY_UP,HEAPID_BATTLE)){
				else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_AGILITY_UP)){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]=COND_AGI;
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_ABIRITY_UP;
					ret=TRUE;
				}
				// �������A�b�v
//				else if(ItemParamGet(itemno,ITEM_PRM_HIT_UP,HEAPID_BATTLE)){
				else if(ST_ItemParamGet(sp,itemno,ITEM_PRM_HIT_UP)){
					sp->AIWT.AI_ITEM_CONDITION[client_no>>1]=COND_HIT;
					sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_ABIRITY_UP;
					ret=TRUE;
				}
				// �\�̓K�[�h
//				else if((ItemParamGet(itemno,ITEM_PRM_ABILITY_GUARD,HEAPID_BATTLE))&&
				else if((ST_ItemParamGet(sp,itemno,ITEM_PRM_ABILITY_GUARD))&&
					   ((sp->side_condition[1]&SIDE_CONDITION_SHIROIKIRI)==0)){
						sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_EFFECT_GUARD;
						ret=TRUE;
				}
			}
			else{
				sp->AIWT.AI_ITEM_TYPE[client_no>>1]=ITEMTYPE_UNKOWN;
			}
			if(ret==TRUE){
				sp->AIWT.AI_ITEM_NO[client_no>>1]=itemno;
				sp->AIWT.AI_HAVEITEM[client_no>>1][i]=0;
			}
		}
	}
	return ret;
}

