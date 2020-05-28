
//============================================================================================
/**
 * @file	server.c
 * @bfief	�퓬�T�[�o�v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#include "common.h"

#include "battle/battle_server.h"
#include "battle/client.h"
#include "battle/client_tool.h"
#include "battle/fight.h"
#include "battle/fight_tool.h"
#include "battle/scio.h"
#include "battle/server.h"
#include "battle/server_tool.h"
#include "battle/skill_intp.h"
#include "battle/wazano_def.h"
#include "battle/tokusyu_def.h"
#include "battle/tr_ai.h"
#include "battle/tr_ai_def.h"

#include "poketool/monsno.h"
#include "poketool/poke_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/tr_tool.h"
#include "battle/trtype_def.h"

#include "application/pokelist.h"

#include "system/arc_tool.h"

#include "itemtool/item.h"
#include "itemtool/myitem.h"

#include "server_def.h"

#include "msgdata/msg_fightmsg_dp.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_command_battle.h"
#include "system/snd_tool.h"
#include "field/sysflag_def.h"

#include "bugfix.h"	//add by 2006.08.15

#ifdef PM_DEBUG
#ifdef DEBUG_ONLY_FOR_sogabe
//#define	ORDER_IGNORE_ONLY	//���ߖ������ĈႤ�Z���o�������ɂ���
#endif DEBUG_ONLY_FOR_sogabe
#endif PM_DEBUG

void	*ServerInit(BATTLE_WORK *bw);
int		ServerMain(BATTLE_WORK *battle_work,SERVER_PARAM *server_param);
void	ServerEnd(SERVER_PARAM *server_param);

void	ServerHitCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);

static	void	ServerPokemonParamGet(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�|�P�����p�����[�^���T�[�o���[�N�ɃQ�b�g
static	void	ServerEncountSet(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�G���J�E���g����
static	void	ServerTrainerMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�퓬���Ƀg���[�i�[���o�Ă��ă��b�Z�[�W�\��
static	void	ServerPokeAppearCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�|�P�����o�ꎞ�Ƀ`�F�b�N���鍀��
static	void	ServerCommandSelectInit(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�R�}���h�I������������
static	void	ServerCommandSelect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�R�}���h�I������
static	void	ServerAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�f�����v�Z����
static	void	ServerBeforeAct(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<����O����
static	void	ServerActionBranch(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<���앪�򏈗�
static	void	ServerFieldConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<��ɂ������Ă���퓬���ʃ`�F�b�N
static	void	ServerPokeConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N
static	void	ServerSideConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N�i���ɂ������Ă�����ʁj
static	void	ServerTurnEnd(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�퓬�^�[���I������
static	void	ServerFightCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�����������쏈��
static	void	ServerItemCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<����g�p����
static	void	ServerPokemonCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�|�P�����I������
static	void	ServerEscapeCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�ɂ��铮�쏈��

static	void	ServerSafariBallCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�T�t�@���Ń{�[�������鏈��
static	void	ServerSafariEsaCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�T�t�@���ŃG�T�����鏈��
static	void	ServerSafariDoroCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�T�t�@���Ńh�������鏈��
static	void	ServerSafariYousumiCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<�T�t�@���ŗl�q������

static	int		ServerBadgeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);	///<�o�b�W�`�F�b�N
static	BOOL	ServerPPCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<PP�`�F�b�N
static	BOOL	ServerDefenceCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�U���Ώۃ`�F�b�N
static	BOOL	ServerTypeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<TYPE�`�F�b�N
static	BOOL	ServerStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<��Ԉُ�`�F�b�N
static	BOOL	ServerTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�����`�F�b�N
static	BOOL	ServerSenseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�搧�n�̃A�C�e�����ʂ̃`�F�b�N
static	BOOL	ServerHitCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);	///<�������`�F�b�N
static	BOOL	ServerWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);	///<�Z���ʃ`�F�b�N
static	BOOL	ServerWazaKoyuuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�Z�ŗL�`�F�b�N

static	void	ServerWazaSequence(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�Z�V�[�P���X���s
static	void	ServerWazaBefore(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�Z�O����
static	void	ServerWazaOutCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�Z�����`�F�b�N
static	void	ServerAddStatusDirectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<�ǉ����ʃ`�F�b�N�i���ڒǉ��̂݁j
static	void	ServerWazaHazureMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<������Ȃ������n���b�Z�[�W�\��
static	void	ServerWazaOut(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�Z��������
static	void	ServerHPCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);					///<HP�v�Z
static	void	ServerWazaOutAfterMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<�Z���ł���̂��낢��ȃ��b�Z�[�W�\��
static	void	ServerAddStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�ǉ����ʃ`�F�b�N�i���ڒǉ��ȊO�j
static	void	ServerWazaOutAfterKouka(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�Z���ł���̂��낢��Ȍ��ʃ`�F�b�N
static	void	ServerRenzokuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�A���U���̃`�F�b�N
static	void	ServerSinkuroCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�����V���N���`�F�b�N
static	void	ServerKizetsuEffect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�C��G�t�F�N�g
static	void	ServerLoopCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�����̓�����Z�̃`�F�b�N
static	void	ServerJibakuEffect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<���΂��ɂ��C��G�t�F�N�g
static	void	ServerWazaHitAfterCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�Z���q�b�g������̃`�F�b�N
static	void	ServerGetExpEffect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�o���l�擾�G�t�F�N�g
static	void	ServerWazaNoBufferSet(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�Z�i���o�[���o�b�t�@�Ɋi�[
static	void	ServerWazaEnd(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�Z�V�[�P���X�I��
static	void	ServerPokeReshuffleAfter(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�|�P�������ꂩ����V�[�P���X
static	void	ServerWinLose(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�퓬���s�V�[�P���X
//static	void	ServerQueCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�T�[�o�L���[���`�F�b�N���ďI����҂�

static	void	ServerFightEnd(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<�퓬�I��
static	void	ServerFightEndWait(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�퓬�I���i�ʐM�ΐ펞�̑҂��j

static	BOOL	ServerReshuffleCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<����ւ��`�F�b�N
static	BOOL	ServerZenmetsuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�S�Ń`�F�b�N
static	BOOL	ServerDirSelectCheck(SERVER_PARAM *sp,u8 client_no,u32 fight_type,int *range,int waza_pos,u32 *dir); ///<�U���ΏۑI���`�F�b�N
static	void	ServerFlagOffReqAct(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�폜�v���̂������t���O�̍폜

static	BOOL	ServerKizetsuCheck(SERVER_PARAM *sp,int next_seq,int no_set_seq,int flag);	///<�C��`�F�b�N
static	BOOL	ServerGetExpCheck(SERVER_PARAM *sp,int next_seq,int no_set_seq);	///<�o���l�擾�`�F�b�N
static	void	ServerOumugaeshiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�I�E���������o�b�t�@�ւ̑���`�F�b�N
static	BOOL	ServerWazaHitAfterCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<�Z���q�b�g������̃`�F�b�N

//static	void	ServerQueCheckSet(SERVER_PARAM *sp,int next_seq,int wait);

static	BOOL	ServerCriticalMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�}���ɂ����������b�Z�[�W�\��
static	BOOL	ServerWazaStatusMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<�΂���₢�܂ЂƂȂǃ��b�Z�[�W�\��
static	BOOL	ServerIkariCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	ServerHirumaseruCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	ServerVanishCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<�����Ă���|�P�������ǂ����邩�`�F�b�N

///<�T�[�o�V�[�P���X�e�[�u��
static	const	svFunc	ServerSequenceTbl[]={
	ServerPokemonParamGet,		///<�|�P�����p�����[�^���T�[�o���[�N�ɃQ�b�g
	ServerEncountSet,			///<�G���J�E���g����
	ServerTrainerMessage,		///<�퓬���Ƀg���[�i�[���o�Ă��ă��b�Z�[�W�\��
	ServerPokeAppearCheck,		///<�|�P�����o�ꎞ�Ƀ`�F�b�N���鍀��
	ServerCommandSelectInit,	///<�R�}���h�I������������
	ServerCommandSelect,		///<�R�}���h�I������
	ServerAgiCalc,				///<�f�����v�Z����
	ServerBeforeAct,			///<����O����
	ServerActionBranch,			///<���앪�򏈗�
	ServerFieldConditionCheck,	///<��ɂ������Ă���퓬���ʃ`�F�b�N
	ServerPokeConditionCheck,	///<�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N
	ServerSideConditionCheck,	///<�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N�i���ɂ������Ă�����ʁj
	ServerTurnEnd,				///<�퓬�^�[���I������

	ServerFightCommand,			///<�����������쏈��
	ServerItemCommand,			///<����g�p����
	ServerPokemonCommand,		///<�|�P�����I������
	ServerEscapeCommand,		///<�ɂ��铮�쏈��

	ServerSafariBallCommand,	///<�T�t�@���Ń{�[�������鏈��
	ServerSafariEsaCommand,		///<�T�t�@���ŃG�T�����鏈��
	ServerSafariDoroCommand,	///<�T�t�@���Ńh�������鏈��
	ServerSafariYousumiCommand,	///<�T�t�@���ŗl�q������

	ServerWazaSequence,			///<�Z�V�[�P���X���s
	ServerWazaBefore,			///<�Z�O����
	ServerWazaOutCheck,			///<�Z�����`�F�b�N
	ServerAddStatusDirectCheck,	///<�ǉ����ʃ`�F�b�N�i���ڒǉ��̂݁j
	ServerWazaHazureMessage,	///<������Ȃ������n���b�Z�[�W�\��
	ServerWazaOut,				///<�Z��������
	ServerHPCalc,				///<HP�v�Z
	ServerWazaOutAfterMessage,	///<�Z���ł���̂��낢��ȃ��b�Z�[�W�\��
	ServerAddStatusCheck,		///<�ǉ����ʃ`�F�b�N�i���ڒǉ��ȊO�j
	ServerWazaOutAfterKouka,	///<�Z���ł���̂��낢��Ȍ��ʃ`�F�b�N
	ServerRenzokuCheck,			///<�A���U���̃`�F�b�N
	ServerSinkuroCheck,			///<�V���N���`�F�b�N
	ServerKizetsuEffect,		///<�C��G�t�F�N�g
	ServerLoopCheck,			///<�����̓�����Z�̃`�F�b�N
	ServerJibakuEffect,			///<���΂��ɂ��C��G�t�F�N�g
	ServerWazaHitAfterCheck,	///<�Z���q�b�g������̃`�F�b�N
	ServerGetExpEffect,			///<�o���l�擾�G�t�F�N�g
	ServerWazaNoBufferSet,		///<�Z�i���o�[���o�b�t�@�֊i�[
	ServerWazaEnd,				///<�Z�V�[�P���X�I��

	ServerPokeReshuffleAfter,	///<�|�P�������ꂩ����V�[�P���X

	ServerWinLose,				///<�퓬���s�V�[�P���X

//	ServerQueCheck,				///<�T�[�o�L���[���`�F�b�N���ďI����҂�

	ServerFightEnd,				///<�퓬�I��
	ServerFightEndWait,			///<�퓬�I���i�ʐM�ΐ펞�̑҂��j
};

//============================================================================================
/**
 * @param
 */
//============================================================================================
void	*ServerInit(BATTLE_WORK *bw)
{
	SERVER_PARAM	*sp;
	int				i;

	sp=sys_AllocMemory(HEAPID_BATTLE,sizeof(SERVER_PARAM));

	MI_CpuClearFast(sp,sizeof(SERVER_PARAM));

	ST_ServerWorkInit(sp);
	ST_ServerCounterWorkInit(bw,sp);

	//Wifi�̎��́AAI�����[�h����Ă��Ȃ��̂Ŗ���
	if(!CommStateIsWifiConnect()){
		WazaAIInit(bw,sp,NULL,NULL);
	}

	WT_WazaTableDataGet(&sp->AIWT.wtd);
	sp->AIWT.item=ItemDataTableLoad(HEAPID_BATTLE);

	return sp;
}

//============================================================================================
/**
 * @param
 */
//============================================================================================
int		ServerMain(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->fight_end_flag==0){
		if((BattleWorkWinLoseGet(bw))&&
		  ((BattleWorkWinLoseGet(bw)&FIGHT_ESCAPE_SELECT_PAUSE)==0)){
			sp->server_seq_no=SERVER_WIN_LOSE_NO;
		}
	}

	//���̎d�l�͂Ȃ��Ȃ�܂���
#if 0
	//����������Ԃ肪�������Ă������p���b�Z�[�W�\���V�[�P���X��
	if(sp->server_status_flag&SERVER_STATUS_FLAG_KATAYABURI){
		sp->server_status_flag&=SERVER_STATUS_FLAG_KATAYABURI_OFF;
		if(sp->server_seq_no==SERVER_WAZA_SEQUENCE_NO){
			ST_ServerSequenceLoadGosub(sp,ARC_SUB_SEQ,SUB_SEQ_KATAYABURI);
		}
		else{
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_KATAYABURI);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		}
	}
#endif

	ServerSequenceTbl[sp->server_seq_no](bw,sp);
	if(sp->server_seq_no==SERVER_FIGHT_END_WAIT_NO){			///<�퓬�I��
		return 1;
	}
	return 0;
}

//============================================================================================
/**
 * @param
 */
//============================================================================================
void	ServerEnd(SERVER_PARAM *server_param)
{
	//AI�̃������W�J����߂��̂ŁA�J�������͕K�v�Ȃ�
//	if(server_param->AISeqWork){
//		sys_FreeMemoryEz(server_param->AIWT.handle);
//		sys_FreeMemoryEz(server_param->AISeqWork);
//	}
	sys_FreeMemoryEz(server_param->AIWT.item);
	sys_FreeMemoryEz(server_param);
}

//============================================================================================
/**
 *	�������`�F�b�N�ƋZ���ʂɂ�閽���`�F�b�N������	
 *
 * @param
 */
//============================================================================================
void	ServerHitCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no)
{
	ServerHitCheck(bw,sp,attack,defence,waza_no);
	ServerWazaKoukaCheck(bw,sp,attack,defence,waza_no);
}

//============================================================================================
/**
 *	�|�P�����p�����[�^���T�[�o���[�N�ɃQ�b�g
 *
 * @param
 */
//============================================================================================
static	void	ServerPokemonParamGet(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(client_no=0;client_no<client_set_max;client_no++){
		ST_PokemonParamGet(bw,sp,client_no,sp->sel_mons_no[client_no]);
	}

	//�ΐ푊��̌���HP��ۑ�
	sp->hp_temp=sp->psp[CLIENT_NO_ENEMY].hp;

	sp->server_seq_no=SERVER_ENCOUNT_SET_NO;
}

//============================================================================================
/**
 *	�G���J�E���g����
 *
 * @param
 */
//============================================================================================
static	void	ServerEncountSet(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_POKEMON_ENCOUNT);
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	sp->next_server_seq_no=SERVER_TRAINER_MESSAGE_NO;
}

//============================================================================================
/**
 *	�퓬���Ƀg���[�i�[���o�Ă��ă��b�Z�[�W�\��
 *
 * @param
 */
//============================================================================================
static	void	ServerTrainerMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(ST_ServerTrainerMessageCheck(bw,sp)){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TRAINER_MESSAGE);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_POKE_APPEAR_CHECK_NO;
	}
	else{
		sp->server_seq_no=SERVER_POKE_APPEAR_CHECK_NO;
	}
	//�Z���ʔ����̂��߂̑f�����v�Z
	ST_ServerPSPAgiCalc(bw,sp);
}

//============================================================================================
/**
 *	�|�P�����o�ꎞ�Ƀ`�F�b�N���鍀��
 *
 * @param
 */
//============================================================================================
static	void	ServerPokeAppearCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;

	seq_no=ST_ServerPokeAppearCheck(bw,sp);

	if(seq_no){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	}
	else{
		//�Z���ʔ����̂��߂̑f�����v�Z�i�������ʂ̔����őf�������ς���Ă���ꍇ������̂ŁA�Čv�Z�j
		ST_ServerPSPAgiCalc(bw,sp);
		sp->server_seq_no=SERVER_COMMAND_SELECT_INIT_NO;
	}
}

//============================================================================================
/**
 *	�R�}���h�I������������
 *
 * @param
 */
//============================================================================================
static	void	ServerCommandSelectInit(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	
	for(client_no=0;client_no<client_set_max;client_no++){
		sp->com_seq_no[client_no]=0;
		//�����Ă����Ԃ��Ď����邽�߂ɁA�Z���ʃ��[�N���e���|�����ɃR�s�[
		sp->psp[client_no].waza_kouka_temp=sp->psp[client_no].waza_kouka;
	}

	//�R�}���h�I���Ń{�^�����X���C�h�C�������Ƃ��ɗ��Ƃ����t���O���Z�b�g
	BattleWorkCommandSelectFlagSet(bw,SLIDE_IN_BEFORE);

	sp->server_seq_no=SERVER_COMMAND_SELECT_NO;
}

//============================================================================================
// 	�R�}���h�I�������̃V�[�P���X�i���o�[
//============================================================================================
enum{
	SCSSEQ_COMMAND_SELECT_INIT=0,
	SCSSEQ_COMMAND_SELECT,
	SCSSEQ_WAZA_SELECT_INIT,
	SCSSEQ_WAZA_SELECT,
	SCSSEQ_DIR_SELECT_INIT,
	SCSSEQ_DIR_SELECT,
	SCSSEQ_ITEM_SELECT_INIT,
	SCSSEQ_ITEM_SELECT,
	SCSSEQ_POKEMON_SELECT_INIT,
	SCSSEQ_POKEMON_SELECT,
	SCSSEQ_ESCAPE_SELECT_INIT,
	SCSSEQ_ESCAPE_SELECT,
	SCSSEQ_COMMAND_SELECT_WAIT,
	SCSSEQ_COMMAND_SELECT_END,
	SCSSEQ_ALERT_MESSAGE_WAIT,
	SCSSEQ_WARUAGAKI_MESSAGE,
	SCSSEQ_SUBBG_WALL_PUT,
};

//============================================================================================
/**
 *	�R�}���h�I������
 *
 * @param
 */
//============================================================================================
static	void	ServerCommandSelect(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				client_no;
	int				client_set_max;
	int				fight_type;
	int				command_end_cnt;
	MESSAGE_PARAM	mp;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);
	command_end_cnt=0;

	for(client_no=0;client_no<client_set_max;client_no++){
		switch(sp->com_seq_no[client_no]){
		case SCSSEQ_COMMAND_SELECT_INIT:
			if((fight_type&FIGHT_TYPE_2vs2)&&
			  ((fight_type&FIGHT_TYPE_MULTI)==0)&&
			  ((client_no==2)&&(sp->com_seq_no[0]!=SCSSEQ_COMMAND_SELECT_END)||
			   (client_no==3)&&(sp->com_seq_no[1]!=SCSSEQ_COMMAND_SELECT_END))){
				break;
			}
			///<����ւ���|�P�����������Ȃ�ClientNo�́A�R�}���h�I���Ȃ�
			if(sp->no_reshuffle_client&No2Bit(client_no)){
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
				sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;	///<�Z�V�[�P���X�I��
				break;
			}
			else if(ST_ServerCommandSelectCheck(sp,client_no)==FALSE){
				//�R�}���h�I�����Ȃ���������PP�����炳�Ȃ��t���O�𗧂Ă�
				sp->otf[client_no].pp_dec_flag=1;
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
				sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_FIGHT_COMMAND_NO;
				break;
			}
			SCIO_CommandSelectSet(bw,sp,client_no,sp->sel_mons_no[client_no]);
			sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT;
		case SCSSEQ_COMMAND_SELECT:
			if(ST_ServerBufferResGet(sp,client_no)){
				sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]=sp->server_buffer[client_no][0];
				if(fight_type&FIGHT_TYPE_POKE_PARK){
					switch(ST_ServerBufferResGet(sp,client_no)){
					case SELECT_POKEPARK_BALL:
						sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
						sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_SAFARI_BALL_NO;
						break;
					case SELECT_POKEPARK_ESCAPE:
						sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
						sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_ESCAPE_COMMAND_NO;
						break;
					}
				}
				else if(fight_type&FIGHT_TYPE_SAFARI){
					switch(ST_ServerBufferResGet(sp,client_no)){
					case SELECT_SAFARI_BALL:
						sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
						sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_SAFARI_BALL_NO;
						break;
					case SELECT_SAFARI_ESA:
						sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
						sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_SAFARI_ESA_NO;
						break;
					case SELECT_SAFARI_DORO:
						sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
						sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_SAFARI_DORO_NO;
						break;
					case SELECT_SAFARI_ESCAPE:
						sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
						sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_ESCAPE_COMMAND_NO;
						break;
					case SELECT_SAFARI_YOUSUMI:
						sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
						sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_SAFARI_YOUSUMI_NO;
						break;
					}
				}
				else{
					switch(ST_ServerBufferResGet(sp,client_no)){
					case SELECT_FIGHT_COMMAND:
						if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_ALL)==0x0f){
							sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
							sp->ret_seq_no[client_no]=SCSSEQ_WARUAGAKI_MESSAGE;
						}
						///<�A���R�[�����󂯂Ă��鎞�́A�Z�I���Ȃ�
						else if(sp->psp[client_no].wkw.encore_wazano){
							sp->waza_no_pos[client_no]=sp->psp[client_no].wkw.encore_wazapos;
							sp->waza_no_select[client_no]=sp->psp[client_no].wkw.encore_wazano;
							sp->client_act_work[client_no][ACT_PARA_WORK]=0;
							sp->com_seq_no[client_no]=SCSSEQ_SUBBG_WALL_PUT;
							sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
						}
						else{
							sp->com_seq_no[client_no]=SCSSEQ_WAZA_SELECT_INIT;
						}
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_FIGHT_COMMAND_NO;
						break;
					case SELECT_ITEM_COMMAND:
						if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_NO_ITEM_USE){
							mp.msg_id=DouguAlertMsg;
							mp.msg_tag=TAG_NONE;
							SCIO_AlertMessageSet(bw,client_no,mp);
							sp->com_seq_no[client_no]=SCSSEQ_ALERT_MESSAGE_WAIT;
							sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
							OS_TPrintf("AlertMessage\n");
						}
						else{
							sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_ITEM_COMMAND_NO;
							sp->com_seq_no[client_no]=SCSSEQ_ITEM_SELECT_INIT;
						}
						break;
					case SELECT_POKEMON_COMMAND:
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_POKEMON_COMMAND_NO;
						sp->com_seq_no[client_no]=SCSSEQ_POKEMON_SELECT_INIT;
						break;
					case SELECT_ESCAPE_COMMAND:
						sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_ESCAPE_COMMAND_NO;
						sp->com_seq_no[client_no]=SCSSEQ_ESCAPE_SELECT_INIT;
						break;
#ifdef PM_DEBUG
					case SELECT_DEBUG_ESCAPE_COMMAND:
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ESCAPE);
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->next_server_seq_no=SERVER_FIGHT_END_NO;
						break;
					case SELECT_DEBUG_WIN_ESCAPE_COMMAND:
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WIN_ESCAPE);
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->next_server_seq_no=SERVER_FIGHT_END_NO;
						break;
#endif
					case SELECT_CANCEL:
						if(fight_type&FIGHT_TYPE_SIO){
							SCIO_GaugeAnimeStop(bw,client_no);
							sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
							sp->com_seq_no[BattleWorkPartnerClientNoGet(bw,client_no)]=SCSSEQ_COMMAND_SELECT_INIT;
						}
						else if((fight_type&FIGHT_TYPE_2vs2)&&(client_no==2)){
							SCIO_GaugeAnimeStop(bw,client_no);
							sp->com_seq_no[0]=SCSSEQ_COMMAND_SELECT_INIT;
							sp->com_seq_no[2]=SCSSEQ_COMMAND_SELECT_INIT;
						}
						else{
							OS_Printf("�R�}���h�Z���N�g�ŁA�s����SELECT_CALCEL�I\n");
						}
						break;
					}
				}
			}
			break;
		case SCSSEQ_WAZA_SELECT_INIT:
			SCIO_WazaSelectSet(bw,sp,client_no);
			sp->com_seq_no[client_no]=SCSSEQ_WAZA_SELECT;
		case SCSSEQ_WAZA_SELECT:
			if(ST_ServerBufferResGet(sp,client_no)==SELECT_CANCEL){
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
			}
			else if(ST_ServerBufferResGet(sp,client_no)){
				if((sp->server_buffer[client_no][0]-1)==AI_ENEMY_ESCAPE){
					sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_ESCAPE_COMMAND_NO;
					sp->com_seq_no[client_no]=SCSSEQ_ESCAPE_SELECT_INIT;
					break;
				}
				else{
					if(ST_ServerWazaNGCheck(bw,sp,client_no,sp->server_buffer[client_no][0]-1,&mp)==FALSE){
						SCIO_AlertMessageSet(bw,client_no,mp);
						sp->com_seq_no[client_no]=SCSSEQ_ALERT_MESSAGE_WAIT;
						sp->ret_seq_no[client_no]=SCSSEQ_WAZA_SELECT_INIT;
					}
					else{
						//�Z�̃|�W�V�������Ԃ��Ă���
						sp->client_act_work[client_no][ACT_PARA_WORK]=sp->server_buffer[client_no][0];
						sp->waza_no_pos[client_no]=sp->server_buffer[client_no][0]-1;
						sp->waza_no_select[client_no]=sp->psp[client_no].waza[sp->waza_no_pos[client_no]];
						sp->com_seq_no[client_no]=SCSSEQ_DIR_SELECT_INIT;
					}
				}
			}
			break;
		case SCSSEQ_DIR_SELECT_INIT:
			{
				int	range;

				if(ServerDirSelectCheck(sp,client_no,fight_type,&range,
										sp->waza_no_pos[client_no],
										&sp->client_act_work[client_no][ACT_PARA_CLIENT_NO])){
					SCIO_DirSelectSet(bw,sp,range,client_no);
					sp->com_seq_no[client_no]=SCSSEQ_DIR_SELECT;
				}
				else{
					sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
				}
			}
			break;
		case SCSSEQ_DIR_SELECT:
			if(ST_ServerBufferResGet(sp,client_no)==SELECT_CANCEL){
				sp->com_seq_no[client_no]=SCSSEQ_WAZA_SELECT_INIT;
			}
			else if(ST_ServerBufferResGet(sp,client_no)){
				//�U���Ώۂ��Ԃ��Ă���
				sp->client_act_work[client_no][ACT_PARA_CLIENT_NO]=sp->server_buffer[client_no][0]-1;
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
			}
			break;
		case SCSSEQ_ITEM_SELECT_INIT:
			SCIO_ItemSelectSet(bw,sp,client_no);
			sp->com_seq_no[client_no]=SCSSEQ_ITEM_SELECT;
		case SCSSEQ_ITEM_SELECT:
			if(ST_ServerBufferResGet(sp,client_no)==SELECT_CANCEL){
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
			}
			else if(ST_ServerBufferResGet(sp,client_no)){
				{
					u32	*data;

					data=(u32 *)&sp->server_buffer[client_no][0];
					//�A�C�e���i���o�[�ƃy�[�W�i���o�[���Ԃ��Ă���
					sp->client_act_work[client_no][ACT_PARA_WORK]=data[0];
					sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
				}
			}
			break;
		case SCSSEQ_POKEMON_SELECT_INIT:
			{
				int	chg_waza;
				int	double_sel=NO_DOUBLE_SEL;
				int	partner_no;

				chg_waza=ST_ServerPokemonSelectCheck(bw,sp,client_no);
				if(((BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_C)||
				    (BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_D))&&
				   ((fight_type==FIGHT_TYPE_2vs2_TRAINER)||
					(fight_type==FIGHT_TYPE_2vs2_SIO)||
					(fight_type==FIGHT_TYPE_BATTLE_TOWER_2vs2)||
				   ((fight_type==FIGHT_TYPE_TAG_BATTLE)&&(BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_C)))){
					partner_no=BattleWorkPartnerClientNoGet(bw,client_no);
					if(sp->client_act_work[partner_no][ACT_PARA_ACT_NO]==SERVER_POKEMON_COMMAND_NO){
						double_sel=sp->client_act_work[partner_no][ACT_PARA_WORK];
					}
				}
				SCIO_PokemonSelectSet(bw,sp,client_no,BPL_MODE_NORMAL,chg_waza,double_sel);
				sp->com_seq_no[client_no]=SCSSEQ_POKEMON_SELECT;
			}
		case SCSSEQ_POKEMON_SELECT:
			if(ST_ServerBufferResGet(sp,client_no)==SELECT_CANCEL){
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
			}
			else if(ST_ServerBufferResGet(sp,client_no)){
				//�I�񂾃|�P�����̈ʒu���Ԃ��Ă���
				sp->client_act_work[client_no][ACT_PARA_WORK]=sp->server_buffer[client_no][0]-1;
				sp->reshuffle_sel_mons_no[client_no]=sp->server_buffer[client_no][0]-1;
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
				OS_TPrintf("client_no:%d r_sel_mons:%d\n",client_no,sp->reshuffle_sel_mons_no[client_no]);
			}
			break;
		case SCSSEQ_ESCAPE_SELECT_INIT:
			//�^���[�́A������߂邩����
			if(fight_type&FIGHT_TYPE_TOWER){
				SCIO_YesNoSelectSet(bw,sp,client_no,GiveUpMsg,YNTYPE_YES_NO,NULL,NULL);
				sp->com_seq_no[client_no]=SCSSEQ_ESCAPE_SELECT;
			}
			//�g���[�i�[��͓�����Ȃ�
			else if((fight_type&FIGHT_TYPE_TRAINER)&&((fight_type&FIGHT_TYPE_SIO)==0)){
				mp.msg_tag=TAG_NONE;
				mp.msg_id=TrainerEscapeMsg;
				SCIO_AlertMessageSet(bw,client_no,mp);
				sp->com_seq_no[client_no]=SCSSEQ_ALERT_MESSAGE_WAIT;
				sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
			}
			else if(ST_EscapeNGCheck(bw,sp,client_no,&mp)){
				SCIO_AlertMessageSet(bw,client_no,mp);
				sp->com_seq_no[client_no]=SCSSEQ_ALERT_MESSAGE_WAIT;
				sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
			}
			else{
				sp->com_seq_no[client_no]=SCSSEQ_ESCAPE_SELECT;
			}
			break;
		case SCSSEQ_ESCAPE_SELECT:
			if(fight_type&FIGHT_TYPE_TOWER){
				if(ST_ServerBufferResGet(sp,client_no)){
					if(ST_ServerBufferResGet(sp,client_no)==SELECT_CANCEL){
						sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_INIT;
					}
					else{
						sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
					}
				}
			}
			else{
				//�ɂ���ł́A�͂��^�������I���͖���
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
			}
			//2vs2�́A1�̖ڂ̓�����I���ŁA��������m��
			if((fight_type&FIGHT_TYPE_2vs2)&&
			  ((fight_type&FIGHT_TYPE_MULTI)==0)&&
			   (sp->com_seq_no[client_no]==SCSSEQ_COMMAND_SELECT_WAIT)){
				sp->com_seq_no[BattleWorkPartnerClientNoGet(bw,client_no)]=SCSSEQ_COMMAND_SELECT_WAIT;
			}
			break;
		case SCSSEQ_COMMAND_SELECT_WAIT:
			SCIO_GaugeAnimeStop(bw,client_no);
			if(fight_type==FIGHT_TYPE_2vs2_SIO){
				{
					int	pair_client;

					pair_client=BattleWorkPartnerClientNoGet(bw,client_no);
					if(sp->com_seq_no[pair_client]==SCSSEQ_COMMAND_SELECT_END){
						SCIO_SioWaitMessage(bw,client_no);
					}
				}
			}
			else{
				SCIO_SioWaitMessage(bw,client_no);
			}
			sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_END;
		case SCSSEQ_COMMAND_SELECT_END:
			command_end_cnt++;
			break;
		case SCSSEQ_ALERT_MESSAGE_WAIT:
			if(ST_ServerBufferResGet(sp,client_no)){
				//�N���C�A���g����̕ԓ��o�b�t�@���N���A
				ST_ServerBufferClear(sp,client_no);
				sp->com_seq_no[client_no]=sp->ret_seq_no[client_no];
			}
			break;
		case SCSSEQ_WARUAGAKI_MESSAGE:
			mp.msg_tag=TAG_NICK;
			mp.msg_id=WazaNGMineMsg;
			mp.msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
			SCIO_AlertMessageSet(bw,client_no,mp);
			sp->otf[client_no].waruagaki_flag=1;
			sp->com_seq_no[client_no]=SCSSEQ_ALERT_MESSAGE_WAIT;
			sp->ret_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
			break;
		case SCSSEQ_SUBBG_WALL_PUT:
			SCIO_SubBGWallPut(bw,client_no);
			sp->com_seq_no[client_no]=sp->ret_seq_no[client_no];
			break;
		}
	}
	if(command_end_cnt==client_set_max){
		sp->server_seq_no=SERVER_AGI_CALC_NO;
		//ListRow�̕��ёւ��`�F�b�N
		for(client_no=0;client_no<client_set_max;client_no++){
			if(sp->client_act_work[client_no][ACT_PARA_ACT_NO]==SERVER_POKEMON_COMMAND_NO){
				ST_ServerListRowChange(bw,sp,client_no,sp->reshuffle_sel_mons_no[client_no]);
			}
		}
	}
}

//============================================================================================
/**
 *	�f�����v�Z����
 *
 * @param
 */
//============================================================================================
static	void	ServerAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max;
	u32	fight_type;
	int	i,j;
	int	turn;
	int	flag;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);

	turn=0;
	//�T�t�@���]�[���A�|�P�p�[�N�͕K����������U
	if(fight_type&(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)){
		for(client_no=0;client_no<client_set_max;client_no++){	
			sp->client_agi_work[client_no]=client_no;
		}
	}
	else{
		if(fight_type&FIGHT_TYPE_SIO){
			for(client_no=0;client_no<client_set_max;client_no++){	
				if(sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]==SELECT_ESCAPE_COMMAND){
					turn=5;
					break;
				}
			}
		}
		else{
			if(sp->client_act_work[0][ACT_PARA_SELECT_COMMAND]==SELECT_ESCAPE_COMMAND){
				client_no=0;
				turn=5;
			}
			if(sp->client_act_work[2][ACT_PARA_SELECT_COMMAND]==SELECT_ESCAPE_COMMAND){
				client_no=2;
				turn=5;
			}
		}
		if(turn==5){
			sp->client_agi_work[0]=client_no;
			turn=1;
			for(i=0;i<client_set_max;i++){	
				if(i!=client_no){
					sp->client_agi_work[turn]=i;
					turn++;
				}
			}
		}
		else{
			for(client_no=0;client_no<client_set_max;client_no++){	
													//�Z�I���Ɠ�����ȊO�𒊏o
													//�Z�Ƃɂ���ȊO�͖������ɐ�U
				if((sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]==SELECT_ITEM_COMMAND)||
				   (sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]==SELECT_POKEMON_COMMAND)){
					sp->client_agi_work[turn]=client_no;
					turn++;
				}
			}
			for(client_no=0;client_no<client_set_max;client_no++){	
													//�Z�I���𒊏o
				if((sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]!=SELECT_ITEM_COMMAND)&&
				   (sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]!=SELECT_POKEMON_COMMAND)){
					sp->client_agi_work[turn]=client_no;
					turn++;
				}
			}
			for(i=0;i<client_set_max-1;i++){
				for(j=i+1;j<client_set_max;j++){
					{
						int	cl1;
						int	cl2;

						cl1=sp->client_agi_work[i];
						cl2=sp->client_agi_work[j];

						if(sp->client_act_work[cl1][ACT_PARA_SELECT_COMMAND]==
						   sp->client_act_work[cl2][ACT_PARA_SELECT_COMMAND]){
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
		}
	}
	sp->server_seq_no=SERVER_BEFORE_ACT_NO;
}

//============================================================================================
/**
 *	����O�����V�[�P���X�i���o�[
 */
//============================================================================================

enum{
	SBA_KIAI_PUNCH=0,			//�������p���`���b�Z�[�W�\���`�F�b�N
	SBA_IKARI,					//������A���I���`�F�b�N
	SBA_AGI_CALC,				//�Z���ʔ������Ԃ����߂�f�����`�F�b�N

	SBA_END
};

//============================================================================================
/**
 *	����O����
 *
 * @param
 */
//============================================================================================
static	void	ServerBeforeAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int ret;
	int	client_no;
	int	client_set_max;
	
	ret=0;
	client_set_max=BattleWorkClientSetMaxGet(bw);

	do{
		switch(sp->sba_seq_no){
		case SBA_KIAI_PUNCH:		//�������p���`���b�Z�[�W�\���`�F�b�N
			while(sp->sba_work<client_set_max){
				client_no=sp->client_agi_work[sp->sba_work];
				if(sp->no_reshuffle_client&No2Bit(client_no)){
					sp->sba_work++;
					continue;
				}
				sp->sba_work++;
				if(((sp->psp[client_no].condition&CONDITION_NEMURI)==0)&&
				    (ST_ServerSelectWazaGet(sp,client_no)==WAZANO_KIAIPANTI)&&
					(ST_ServerNamakeCheck(sp,client_no)==FALSE)&&
					(sp->otf[client_no].waruagaki_flag==0)){
					SCIO_BlankMessage(bw);
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_KIAIPUNCH_BEFORE);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					return;
				}
			}
			sp->sba_work=0;
			sp->sba_seq_no++;
			break;
		case SBA_IKARI:				//������A���I���`�F�b�N
			for(client_no=0;client_no<client_set_max;client_no++){
				//�������ԂŁA
				//�������A���őI�����Ă��Ȃ���΁A�������Ԃ�����
				if((sp->psp[client_no].condition2&CONDITION2_IKARI)&&(ST_ServerSelectWazaGet(sp,client_no)!=WAZANO_IKARI)){
					sp->psp[client_no].condition2&=CONDITION2_IKARI;
				}
			}
			sp->sba_seq_no++;
			break;
		case SBA_AGI_CALC:
			for(client_no=0;client_no<CLIENT_MAX;client_no++){
				sp->agi_rand[client_no]=gf_rand();	///<�f�����`�F�b�N�Ɏg�p���闐���l
			}
			sp->sba_seq_no++;
			break;
		case SBA_END:
			sp->sba_seq_no=0;
			ret=2;
			break;
		}
	}while(ret==0);
	if(ret==2){
		sp->server_seq_no=SERVER_ACTION_BRANCH_NO;
	}
}

//============================================================================================
/**
 *	���앪�򏈗�
 *
 * @param
 */
//============================================================================================
static	void	ServerActionBranch(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	//�Z���ʔ����̂��߂̑f�����v�Z
	ST_ServerPSPAgiCalc(bw,sp);

	if(sp->agi_cnt==client_set_max){
		sp->agi_cnt=0;
		sp->server_seq_no=SERVER_FIELD_CONDITION_CHECK_NO;
	}
	else{
		sp->server_seq_no=sp->client_act_work[sp->client_agi_work[sp->agi_cnt]][ACT_PARA_ACT_NO];
	}
}

//============================================================================================
/**
 *	��ɂ������Ă���퓬���ʃ`�F�b�N�p�V�[�P���X�i���o�[
 */
//============================================================================================

enum{
	FCC_REFLEC=0,	//���t���N�^�[���ʐ؂�
	FCC_HIKARI,		//�Ђ���̂��׌��ʐ؂�
	FCC_SHIROI,		//���낢������ʐ؂�
	FCC_SHINPI,		//����҂̂܂�����ʐ؂�
	FCC_OIKAZE,		//�����������ʐ؂�
	FCC_OMAZINAI,	//���܂��Ȃ����ʐ؂�
	FCC_NEGAIGOTO,	//�˂������Ɣ���
	FCC_AMAGOI,		//���܂������ʐ؂�
	FCC_SUNAARASHI,	//���Ȃ��炵���ʐ؂�
	FCC_NIHONBARE,	//�ɂق�΂���ʐ؂�
	FCC_ARARE,		//�������ʐ؂�
	FCC_HUKAIKIRI,	//�ӂ���������ʐ؂�
	FCC_JUURYOKU,	//���イ��傭���ʐ؂�
	FCC_END
};

//============================================================================================
/**
 *	��ɂ������Ă���퓬���ʃ`�F�b�N
 *
 * @param
 */
//============================================================================================
static	void	ServerFieldConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	ret=0;
	int	dir;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	do{
		//�C��`�F�b�N
		if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
			return;
		}
		//�o���l�擾�`�F�b�N
		if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
			return;
		}
		//�S�Ń`�F�b�N
		if(ServerZenmetsuCheck(bw,sp)==TRUE){
			return;
		}

		switch(sp->fcc_seq_no){
		case FCC_REFLEC:	 //���t���N�^�[
			while(sp->fcc_work<2){
				dir=sp->fcc_work;
				if(sp->side_condition[dir]&SIDE_CONDITION_BUTSURIGUARD){
					if(--sp->scw[dir].butsuri_guard_count==0){
						sp->side_condition[dir]&=SIDE_CONDITION_BUTSURIGUARD_OFF;
						sp->waza_work=WAZANO_RIHUREKUTAA;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_KOUKA_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_work=ST_ServerDir2ClientNoGet(bw,sp,dir);
						ret=1;
					}
				}
				sp->fcc_work++;
				if(ret){
					break;
				}
			}
			if(ret==0){
				sp->fcc_seq_no++;
				sp->fcc_work=0;
			}
			break;
		case FCC_HIKARI: //�Ђ���̂���
			while(sp->fcc_work<2){
				dir=sp->fcc_work;
				if(sp->side_condition[dir]&SIDE_CONDITION_TOKUSYUGUARD){
					if(--sp->scw[dir].tokusyu_guard_count==0){
						sp->side_condition[dir]&=SIDE_CONDITION_TOKUSYUGUARD_OFF;
						sp->waza_work=WAZANO_HIKARINOKABE;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_KOUKA_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_work=ST_ServerDir2ClientNoGet(bw,sp,dir);
						ret=1;
					}
				}
				sp->fcc_work++;
				if(ret){
					break;
				}
			}
			if(ret==0){
				sp->fcc_seq_no++;
				sp->fcc_work=0;
			}
			break;
		case FCC_SHIROI: //���낢����
			while(sp->fcc_work<2){
				dir=sp->fcc_work;
				if(sp->side_condition[dir]&SIDE_CONDITION_SHIROIKIRI){
					if(--sp->scw[dir].shiroikiri_count==0){
						sp->side_condition[dir]&=SIDE_CONDITION_SHIROIKIRI_OFF;
						sp->waza_work=WAZANO_SIROIKIRI;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_KOUKA_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_work=ST_ServerDir2ClientNoGet(bw,sp,dir);
						ret=1;
					}
				}
				sp->fcc_work++;
				if(ret){
					break;
				}
			}
			if(ret==0){
				sp->fcc_seq_no++;
				sp->fcc_work=0;
			}
			break;
		case FCC_SHINPI: //����҂̂܂���
			while(sp->fcc_work<2){
				dir=sp->fcc_work;
				if(sp->side_condition[dir]&SIDE_CONDITION_SHINPI){
					if(--sp->scw[dir].shinpi_count==0){
						sp->side_condition[dir]&=SIDE_CONDITION_SHINPI_OFF;
						sp->client_work=sp->scw[dir].shinpi_client;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SHINPI_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_work=ST_ServerDir2ClientNoGet(bw,sp,dir);
						ret=1;
					}
				}
				sp->fcc_work++;
				if(ret){
					break;
				}
			}
			if(ret==0){
				sp->fcc_seq_no++;
				sp->fcc_work=0;
			}
			break;
		case FCC_OIKAZE:					//���������`�F�b�N
			while(sp->fcc_work<2){
				dir=sp->fcc_work;
				if(sp->side_condition[dir]&SIDE_CONDITION_OIKAZE){
					sp->side_condition[dir]-=1<<OIKAZE_SHIFT;
					if((sp->side_condition[dir]&SIDE_CONDITION_OIKAZE)==0){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_OIKAZE_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_work=ST_ServerDir2ClientNoGet(bw,sp,dir);
						ret=1;
					}
				}
				sp->fcc_work++;
				if(ret){
					break;
				}
			}
			if(ret==0){
				sp->fcc_seq_no++;
				sp->fcc_work=0;
			}
			break;
		case FCC_OMAZINAI:	//���܂��Ȃ����ʐ؂�
			while(sp->fcc_work<2){
				dir=sp->fcc_work;
				if(sp->side_condition[dir]&SIDE_CONDITION_OMAZINAI){
					sp->side_condition[dir]-=1<<OMAZINAI_SHIFT;
					if((sp->side_condition[dir]&SIDE_CONDITION_OMAZINAI)==0){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_OMAZINAI_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_work=ST_ServerDir2ClientNoGet(bw,sp,dir);
						ret=1;
					}
				}
				sp->fcc_work++;
				if(ret){
					break;
				}
			}
			if(ret==0){
				sp->fcc_seq_no++;
				sp->fcc_work=0;
			}
			break;
		case FCC_NEGAIGOTO:		//�˂������ƃ`�F�b�N
			while(sp->fcc_work<client_set_max){
				dir=sp->psp_agi_work[sp->fcc_work];
				if(sp->fcc.negaigoto_count[dir]){
					if(--sp->fcc.negaigoto_count[dir]==0){
						if(sp->psp[dir].hp){
							sp->client_work=dir;
							sp->mp.msg_tag=TAG_NICK;
							sp->mp.msg_id=NegaigotoMineMsg;
							sp->mp.msg_para[0]=dir|(sp->fcc.negaigoto_sel_mons[dir]<<8);
							sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[dir].hpmax,2);
							ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NEGAIGOTO);
							sp->next_server_seq_no=sp->server_seq_no;
							sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
							ret=1;
						}
					}
				}
				sp->fcc_work++;
				if(ret){
					break;
				}
			}
			if(ret==0){
				sp->fcc_seq_no++;
				sp->fcc_work=0;
			}
			break;
		case FCC_AMAGOI:					//���܂����`�F�b�N
			if(sp->field_condition&FIELD_CONDITION_AME_ALL){
				if(sp->field_condition&FIELD_CONDITION_AMEHURASHI){
					sp->mp.msg_id=AmagoiKeep1Msg;
					sp->mp.msg_tag=TAG_NONE;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				}
				else{
					if(--sp->fcc.weather_count==0){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_AMAGOI_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
					else{
						sp->mp.msg_id=AmagoiKeep1Msg;
						sp->mp.msg_tag=TAG_NONE;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
				}
				sp->temp_work=STATUS_WEATHER_RAIN;
				ret=1;
			}
			sp->fcc_seq_no++;
			break;
		case FCC_SUNAARASHI:					//���Ȃ��炵�`�F�b�N
			if(sp->field_condition&FIELD_CONDITION_SUNAARASHI_ALL){
				if(sp->field_condition&FIELD_CONDITION_SUNAOKOSHI){
					sp->mp.msg_id=SunaarashiKeepMsg;
					sp->mp.msg_tag=TAG_NONE;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				}
				else{
					if(--sp->fcc.weather_count==0){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SUNAARASHI_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
					else{
						sp->mp.msg_id=SunaarashiKeepMsg;
						sp->mp.msg_tag=TAG_NONE;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
				}
				sp->temp_work=STATUS_WEATHER_SAND;
				ret=1;
			}
			sp->fcc_seq_no++;
			break;
		case FCC_NIHONBARE:					//�ɂق�΂�`�F�b�N
			if(sp->field_condition&FIELD_CONDITION_HARE_ALL){
				if(sp->field_condition&FIELD_CONDITION_HIDERI){
					sp->mp.msg_id=NihonbareKeepMsg;
					sp->mp.msg_tag=TAG_NONE;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				}
				else{
					if(--sp->fcc.weather_count==0){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NIHONBARE_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
					else{
						sp->mp.msg_id=NihonbareKeepMsg;
						sp->mp.msg_tag=TAG_NONE;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
				}
				sp->temp_work=STATUS_WEATHER_SUN;
				ret=1;
			}
			sp->fcc_seq_no++;
			break;
		case FCC_ARARE:						//�����`�F�b�N
			if(sp->field_condition&FIELD_CONDITION_ARARE_ALL){
				if(sp->field_condition&FIELD_CONDITION_YUKIHURASHI){
					sp->mp.msg_id=ArareKeepMsg;
					sp->mp.msg_tag=TAG_NONE;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				}
				else{
					if(--sp->fcc.weather_count==0){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ARARE_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
					else{
						sp->mp.msg_id=ArareKeepMsg;
						sp->mp.msg_tag=TAG_NONE;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					}
				}
				sp->temp_work=STATUS_WEATHER_ICE;
				ret=1;
			}
			sp->fcc_seq_no++;
			break;
		case FCC_HUKAIKIRI:					//�ӂ�������`�F�b�N
			if(sp->field_condition&FIELD_CONDITION_HUKAIKIRI){
				sp->mp.msg_id=HukaiKiriMsg;
				sp->mp.msg_tag=TAG_NONE;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKOU_KEEP);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				sp->temp_work=STATUS_WEATHER_MIST;
				ret=1;
			}
			sp->fcc_seq_no++;
			break;
		case FCC_JUURYOKU:					//���イ��傭�`�F�b�N
			if(sp->field_condition&FIELD_CONDITION_JUURYOKU){
				sp->field_condition-=(1<<FIELD_JUURYOKU_SHIFT);
				if((sp->field_condition&FIELD_CONDITION_JUURYOKU)==0){
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_JUURYOKU_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->fcc_seq_no++;
			break;
		case FCC_END:
			ret=2;
			break;
		}
	}while(ret==0);

	if(ret==1){
		SCIO_BlankMessage(bw);
	}

	if(ret==2){
		sp->fcc_seq_no=0;
		sp->server_seq_no=SERVER_POKE_CONDITION_CHECK_NO;
	}
}

//============================================================================================
/**
 *	�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N�p�V�[�P���X�i���o�[
 */
//============================================================================================

enum{
//HP�񕜌n���Ƀ`�F�b�N���ċC�₵�ɂ�������
	POKE_CONDITION_CHECK_NEWOHARU=0,	//�˂��͂��HP��
	POKE_CONDITION_CHECK_AQUARING,		//�A�N�A�����O��HP��
	POKE_CONDITION_CHECK_SPEABI,		//������HP��
	POKE_CONDITION_CHECK_SOUBI,			//�������ʂ�HP��
	POKE_CONDITION_CHECK_TABENOKOSI,	//�������ʂ�HP�񕜁i���ׂ̂����̂݁j

	POKE_CONDITION_CHECK_YADORIGI,		//��ǂ肬�ŁAHP����
	POKE_CONDITION_CHECK_DOKU,			//�ǂ��̃_���[�W�`�F�b�N
	POKE_CONDITION_CHECK_DOKUDOKU,		//�ǂ��ǂ��̃_���[�W�`�F�b�N
	POKE_CONDITION_CHECK_YAKEDO,		//�₯�ǂ̃_���[�W�`�F�b�N
	POKE_CONDITION_CHECK_AKUMU,			//�����ނ̃_���[�W�`�F�b�N
	POKE_CONDITION_CHECK_NOROI,			//�̂낢�̃_���[�W�`�F�b�N
	POKE_CONDITION_CHECK_SHIME,			//���߂����n�̃_���[�W�`�F�b�N
	POKE_CONDITION_CHECK_NIGHTMARE,		//�i�C�g���A�̃_���[�W�`�F�b�N
	POKE_CONDITION_CHECK_SAWAGU,		//���킮���ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_ABARERU,		//���΂����ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_KANASHIBARI,	//���Ȃ��΂���ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_ENCORE,		//�A���R�[�����ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_LOCKON,		//���b�N�I�����ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_JUUDEN,		//���イ�ł񔭓��`�F�b�N
	POKE_CONDITION_CHECK_CHOUHATSU,		//���傤�͂��ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_DENZIHUYUU,	//�ł񂶂ӂ䂤���ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_HEALBLOCK,		//�q�[���u���b�N���ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_SHUTOUT,		//�V���b�g�A�E�g���ʐ؂�`�F�b�N
	POKE_CONDITION_CHECK_AKUBI,			//�����є����`�F�b�N
	POKE_CONDITION_CHECK_SOUBI2,		//�������ʂŉ�
	POKE_CONDITION_CHECK_SOUBI_DAMAGE,	//�������ʂŃ_���[�W
//	POKE_CONDITION_CHECK_SINKURO,		//�������ʂŃ_���[�W�ŏ�Ԉُ�ɂȂ�\��������̂Ń`�F�b�N
	POKE_CONDITION_CHECK_END,
};

//============================================================================================
/**
 *	�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N
 *
 * @param
 */
//============================================================================================
static	void	ServerPokeConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u8	ret=0;
	int	client_set_max;
	int	client_no;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	//�C��`�F�b�N
	if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
		return;
	}
	//�o���l�擾�`�F�b�N
	if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
		return;
	}
	//�S�Ń`�F�b�N
	if(ServerZenmetsuCheck(bw,sp)==TRUE){
		return;
	}

	while(sp->pcc_work<client_set_max){
		client_no=sp->psp_agi_work[sp->pcc_work];
		if(sp->no_reshuffle_client&No2Bit(client_no)){
			sp->pcc_work++;
			continue;
		}
		switch(sp->pcc_seq_no){
		//�˂��͂�
		case POKE_CONDITION_CHECK_NEWOHARU:
			if((sp->psp[client_no].waza_kouka&WAZAKOUKA_NEWOHARU)&&
			   (sp->psp[client_no].hp!=sp->psp[client_no].hpmax)&&
			   (sp->psp[client_no].hp!=0)){
				if(sp->psp[client_no].wkw.healblock_count){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HEALBLOCK_RECOVER_NG);
				}
				else{
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NEWOHARU);
				}
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�A�N�A�����O
		case POKE_CONDITION_CHECK_AQUARING:
			if((sp->psp[client_no].waza_kouka&WAZAKOUKA_AQUARING)&&
			   (sp->psp[client_no].hp!=sp->psp[client_no].hpmax)&&
			   (sp->psp[client_no].hp!=0)){
				if(sp->psp[client_no].wkw.healblock_count){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HEALBLOCK_RECOVER_NG);
				}
				else{
					sp->client_work=client_no;
					sp->waza_work=WAZANO_AKUARINGU;
					sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,16);
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZAKOUKA_HP_KAIFUKU);
				}
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//����\��
		case POKE_CONDITION_CHECK_SPEABI:
			if(ST_ServerPCCTokuseiCheck(sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�����A�C�e��
		case POKE_CONDITION_CHECK_SOUBI:
			if(ST_ServerSoubiItemCheck(bw,sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�������ʂ�HP�񕜁i���ׂ̂����̂݁j
		case POKE_CONDITION_CHECK_TABENOKOSI:
			if(ST_ServerSoubiItemTabenokosiCheck(bw,sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//��ǂ肬�̂���
		case POKE_CONDITION_CHECK_YADORIGI:
			if((sp->psp[client_no].waza_kouka&WAZAKOUKA_YADORARE)&&
			   (sp->psp[sp->psp[client_no].waza_kouka&WAZAKOUKA_YADORIGI].hp!=0)&&
			   //�����}�W�b�N�K�[�h�́A��ǂ肬�̂��˂̌��ʂ��󂯂Ȃ�
			   (ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_MAZIKKUGAADO)&&
			   (sp->psp[client_no].hp!=0)){
				sp->attack_client_work=sp->psp[client_no].waza_kouka&WAZAKOUKA_YADORIGI;
				sp->defence_client_work=client_no;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_YADORIGI_HP_DEC);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�ǂ��`�F�b�N
		case POKE_CONDITION_CHECK_DOKU:
			if((sp->psp[client_no].condition&CONDITION_DOKU)&&(sp->psp[client_no].hp!=0)){
				sp->client_work=client_no;
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,8);
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_DOKU_HP_DEC);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�ǂ��ǂ��`�F�b�N
		case POKE_CONDITION_CHECK_DOKUDOKU:
			if((sp->psp[client_no].condition&CONDITION_DOKUDOKU)&&(sp->psp[client_no].hp!=0)){
				sp->client_work=client_no;
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,16);
				if((sp->psp[client_no].condition&CONDITION_DOKUDOKU_CNT)!=CONDITION_DOKUDOKU_CNT){
					sp->psp[client_no].condition+=DOKUDOKU_COUNT;
				}
				sp->hp_calc_work*=((sp->psp[client_no].condition&CONDITION_DOKUDOKU_CNT)>>8);
				sp->hp_calc_work*=-1;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_DOKU_HP_DEC);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�₯�ǃ`�F�b�N
		case POKE_CONDITION_CHECK_YAKEDO:
			if((sp->psp[client_no].condition&CONDITION_YAKEDO)&&(sp->psp[client_no].hp!=0)){
				sp->client_work=client_no;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_YAKEDO_HP_DEC);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�����ރ`�F�b�N
		case POKE_CONDITION_CHECK_AKUMU:
			if((sp->psp[client_no].condition2&CONDITION2_AKUMU)&&(sp->psp[client_no].hp!=0)){
				if(sp->psp[client_no].condition&CONDITION_NEMURI){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_AKUMU_HP_DEC);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
				else{
					sp->psp[client_no].condition2&=CONDITION2_AKUMU_OFF;
				}
			}
			sp->pcc_seq_no++;
			break;
		//�̂낢�`�F�b�N
		case POKE_CONDITION_CHECK_NOROI:
			if((sp->psp[client_no].condition2&CONDITION2_NOROI)&&(sp->psp[client_no].hp!=0)){
				sp->client_work=client_no;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NOROI_HP_DEC);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//���ߌn�̋Z
		case POKE_CONDITION_CHECK_SHIME:
			if((sp->psp[client_no].condition2&CONDITION2_SHIME)&&(sp->psp[client_no].hp!=0)){
				sp->psp[client_no].condition2-=SHIME_COUNT;
				if(sp->psp[client_no].condition2&CONDITION2_SHIME){
					sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,16);
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SHIME_HP_DEC);
				}
				else{
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SHIME_END);
				}
				sp->waza_work=sp->psp[client_no].wkw.shime_wazano;
				sp->client_work=client_no;
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//�i�C�g���A�̃_���[�W�`�F�b�N
		case POKE_CONDITION_CHECK_NIGHTMARE:
			sp->temp_work=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_RET,client_no,TOKUSYU_NAITOMEA);
			if((sp->psp[client_no].condition&CONDITION_NEMURI)&&
			   (ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_MAZIKKUGAADO)&&
			   (sp->psp[client_no].hp!=0)&&
			   (sp->temp_work)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,8);
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NIGHTMARE);
				sp->server_status_flag|=SERVER_STATUS_FLAG_NO_BLINK;
				sp->client_work=client_no;
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//���킮�`�F�b�N
		case POKE_CONDITION_CHECK_SAWAGU:
			if(sp->psp[client_no].condition2&CONDITION2_SAWAGU){
				{
					u8	sleep_client;

					//�����Ă���|�P������������N����
					for(sleep_client=0;sleep_client<client_set_max;sleep_client++){
						if((sp->psp[sleep_client].condition&CONDITION_NEMURI)&&
						   (ST_ServerTokuseiGet(sp,sleep_client)!=TOKUSYU_BOUON)){
							sp->client_work=sleep_client;
							ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MEZAME);
							sp->next_server_seq_no=sp->server_seq_no;
							sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
							break;
						}
					}
					if(sleep_client!=client_set_max){
						ret=2;
						break;
					}
				}
				sp->psp[client_no].condition2-=SAWAGU_COUNT;
				if(ST_ServerWazaOutCheck(sp,client_no)){
					i=SUB_SEQ_SAWAGU_END;
					sp->psp[client_no].condition2&=CONDITION2_SAWAGU_OFF;
					sp->field_condition&=((No2Bit(client_no)<<FIELD_SAWAGU_SHIFT)^0xffffffff);
				}
				else if(sp->psp[client_no].condition2&CONDITION2_SAWAGU){
					i=SUB_SEQ_NOISY;
				}
				else{
					i=SUB_SEQ_SAWAGU_END;
					sp->psp[client_no].condition2&=CONDITION2_SAWAGU_OFF;
					sp->field_condition&=((No2Bit(client_no)<<FIELD_SAWAGU_SHIFT)^0xffffffff);
				}
				sp->client_work=client_no;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,i);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			if(ret!=2){
				sp->pcc_seq_no++;
			}
			break;
		//���΂��`�F�b�N
		case POKE_CONDITION_CHECK_ABARERU:
			if(sp->psp[client_no].condition2&CONDITION2_ABARERU){
				sp->psp[client_no].condition2-=ABARERU_COUNT;
				//�܂ЂōU�����o���Ȃ������Ƃ��́A���΂ꂨ���
				if(ST_ServerWazaOutCheck(sp,client_no)){
					sp->psp[client_no].condition2&=CONDITION2_ABARERU_OFF;
				}
				else if(((sp->psp[client_no].condition2&CONDITION2_ABARERU)==0)&&
						((sp->psp[client_no].condition2&CONDITION2_KONRAN)==0)){
					sp->tsuika_client=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ABARERU_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
#if 0
				//KEEP�������Ă���Ƃ��́A�����I�ɋZ���Ƃ߂��Ă���̂ŁA
				//�������Ȃ��悤�ɂ���
				else if(((sp->psp[client_no].condition2&CONDITION2_ABARERU)==0)&&
						 (sp->psp[client_no].condition2&CONDITION2_KEEP)){
					sp->psp[client_no].condition2&=CONDITION2_KEEP_OFF;
					if((sp->psp[client_no].condition2&CONDITION2_KONRAN)==0){
						sp->tsuika_client=client_no;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ABARERU_END);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						ret=1;
					}
				}
#endif
			}
			sp->pcc_seq_no++;
			break;
		//���Ȃ��΂�
		case POKE_CONDITION_CHECK_KANASHIBARI:
			if(sp->psp[client_no].wkw.kanashibari_wazano){
				//�Z�Y��ŁA���Ȃ��΂肳��Ă����Z���Ȃ��Ƃ��̏���
				for(i=0;i<WAZA_TEMOTI_MAX;i++){
					if(sp->psp[client_no].wkw.kanashibari_wazano==sp->psp[client_no].waza[i]){
						break;
					}
				}
				if(i==WAZA_TEMOTI_MAX){
					sp->psp[client_no].wkw.kanashibari_count=0;
				}
				if(sp->psp[client_no].wkw.kanashibari_count){
					sp->psp[client_no].wkw.kanashibari_count--;
				}
				else{
					sp->psp[client_no].wkw.kanashibari_wazano=0;
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_KANASIBARI_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//�A���R�[��
		case POKE_CONDITION_CHECK_ENCORE:
			if(sp->psp[client_no].wkw.encore_wazano){
				for(i=0;i<WAZA_TEMOTI_MAX;i++){
					if(sp->psp[client_no].wkw.encore_wazano==sp->psp[client_no].waza[i]){
						break;
					}
				}
				//�Z�Y��ŁA�A���R�[������Ă����Z���Ȃ��Ƃ��APP���Ȃ����̏���
				if((i==WAZA_TEMOTI_MAX)||((i!=WAZA_TEMOTI_MAX)&&(sp->psp[client_no].pp[i]==0))){
					sp->psp[client_no].wkw.encore_count=0;
				}
				if(sp->psp[client_no].wkw.encore_count){
					sp->psp[client_no].wkw.encore_count--;
				}
				else{
					sp->psp[client_no].wkw.encore_wazano=0;
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ENCORE_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//���b�N�I��
		case POKE_CONDITION_CHECK_LOCKON:
			if(sp->psp[client_no].waza_kouka&WAZAKOUKA_LOCKON){
				sp->psp[client_no].waza_kouka-=LOCKON_COUNT;
			}
			sp->pcc_seq_no++;
			break;
		//���イ�ł�
		case POKE_CONDITION_CHECK_JUUDEN:
			if(sp->psp[client_no].wkw.juuden_count){
				if(--sp->psp[client_no].wkw.juuden_count==0){
					sp->psp[client_no].waza_kouka&=WAZAKOUKA_JUUDEN_OFF;
				}
			}
			sp->pcc_seq_no++;
			break;
		//���傤�͂�
		case POKE_CONDITION_CHECK_CHOUHATSU:
			if(sp->psp[client_no].wkw.chouhatsu_count){
				sp->psp[client_no].wkw.chouhatsu_count--;
				if(sp->psp[client_no].wkw.chouhatsu_count==0){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_CHOUHATSU_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//�ł񂶂ӂ䂤
		case POKE_CONDITION_CHECK_DENZIHUYUU:
			if(sp->psp[client_no].wkw.denzihuyuu_count){
				sp->psp[client_no].wkw.denzihuyuu_count--;
				if(sp->psp[client_no].wkw.denzihuyuu_count==0){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_DENZIHUYUU_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//�q�[���u���b�N
		case POKE_CONDITION_CHECK_HEALBLOCK:
			if(sp->psp[client_no].wkw.healblock_count){
				sp->psp[client_no].wkw.healblock_count--;
				if(sp->psp[client_no].wkw.healblock_count==0){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HEALBLOCK_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//�V���b�g�A�E�g
		case POKE_CONDITION_CHECK_SHUTOUT:
			if(sp->psp[client_no].wkw.shutout_count){
				sp->psp[client_no].wkw.shutout_count--;
				if(sp->psp[client_no].wkw.shutout_count==0){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SHUTOUT_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//������
		case POKE_CONDITION_CHECK_AKUBI:
			if(sp->psp[client_no].waza_kouka&WAZAKOUKA_AKUBI){
				sp->psp[client_no].waza_kouka-=AKUBI_COUNT;
				if((sp->psp[client_no].waza_kouka&WAZAKOUKA_AKUBI)==0){
					sp->tsuika_client=client_no;
					sp->tsuika_type=ADD_STATUS_WAZA_KOUKA;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NEMURI);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//�����A�C�e��
		case POKE_CONDITION_CHECK_SOUBI2:
			{
				int	seq_no;

				if(ST_ServerSoubiItemConditionBadCheck(bw,sp,client_no,&seq_no)==TRUE){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
		//�������ʂŃ_���[�W
		case POKE_CONDITION_CHECK_SOUBI_DAMAGE:
			if(ST_ServerSoubiItemDamageCheck(bw,sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
#if 0
		//�������ʂŃ_���[�W�ŏ�Ԉُ�ɂȂ�\��������̂Ń`�F�b�N
		case POKE_CONDITION_CHECK_SINKURO:
			if((ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_SINKURO)&&
			   (client_no==sp->tsuika_client)&&
			   (sp->server_status_flag&SERVER_STATUS_FLAG_SINKURO_TSUIKA)){
				if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
					{
						int	cl1,cl2;

						cl1=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_RIGHT);
						cl2=BattleWorkEnemyClientNoGet(bw,client_no,BWECNG_SIDE_LEFT);

						if((((sp->psp[cl1].condition&CONDITION_BAD)==0)&&(sp->psp[cl1].hp))&&
						   (((sp->psp[cl2].condition&CONDITION_BAD)==0)&&(sp->psp[cl2].hp))){
							sp->tsuika_client=ST_ServerDirClientGet(bw,sp,client_no);
						}
						else if(((sp->psp[cl1].condition&CONDITION_BAD)==0)&&(sp->psp[cl1].hp)){
							sp->tsuika_client=cl1;
						}
						else{
							sp->tsuika_client=cl2;
						}
					}
				}
				else{
					sp->tsuika_client=ST_ServerDirClientGet(bw,sp,client_no);
				}
				sp->client_work=client_no;
				{
					int	seq_no;

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
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->pcc_seq_no++;
			break;
#endif
		case POKE_CONDITION_CHECK_END:
			sp->pcc_seq_no=0;
			sp->pcc_work++;
			break;
		}
		if(ret){
			SCIO_BlankMessage(bw);
			return;
		}
	}
	sp->pcc_seq_no=0;
	sp->pcc_work=0;
	sp->server_seq_no=SERVER_SIDE_CONDITION_CHECK_NO;
}

//============================================================================================
/**
 *	�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N�Q�p�V�[�P���X�i���o�[
 */
//============================================================================================

enum{
	SIDE_CONDITION_CHECK_MIRAIYOCHI=0,
	SIDE_CONDITION_CHECK_HOROBINOUTA,
	SIDE_CONDITION_CHECK_TRICKROOM,			//�������ɉe������̂ŁA���Ȃ炸�Ō�Ƀ`�F�b�N���邱�ƁI
//	SIDE_CONDITION_CHECK_DOUJOU_HANTEI,
};

//============================================================================================
/**
 *	�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N�i���ɂ������Ă�����ʁj
 *
 * @param
 */
//============================================================================================
static	void	ServerSideConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	client_set_max;
	int	client_no;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	//�C��`�F�b�N
	if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
		return;
	}
	//�ق�т̂����ŁA�f�����ő���̕�����ɋC�₵�����Ɍo���l������Ȃ��悤��TurnEnd�Ɉړ�
	//�o���l�擾�`�F�b�N
//	if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
//		return;
//	}
	//�ق�т̂����ŁA���������ɂ��邽�߂ɖ�Sync�̃`�F�b�N�͂Ȃ���
	//�S�Ń`�F�b�N
//	if(ServerZenmetsuCheck(bw,sp)==TRUE){
//		return;
//	}

	SCIO_BlankMessage(bw);

	switch(sp->scc_seq_no){
	case SIDE_CONDITION_CHECK_MIRAIYOCHI:
		while(sp->scc_work<client_set_max){
			client_no=sp->psp_agi_work[sp->scc_work];
			if(sp->no_reshuffle_client&No2Bit(client_no)){
				sp->scc_work++;
				continue;
			}
			sp->scc_work++;
			if(sp->fcc.miraiyochi_count[client_no]){
				if((--sp->fcc.miraiyochi_count[client_no]==0)&&(sp->psp[client_no].hp!=0)){
					sp->side_condition[BattleWorkMineEnemyCheck(bw,client_no)]&=SIDE_CONDITION_MIRAIYOCHI_OFF;
					sp->mp.msg_id=MiraiyochiDamageMineMsg;
					sp->mp.msg_tag=TAG_NICK_WAZA;
					sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
					sp->mp.msg_para[1]=sp->fcc.miraiyochi_wazano[client_no];
					sp->client_work=client_no;
					sp->attack_client_work=sp->fcc.miraiyochi_client_no[client_no];
					sp->waza_work=sp->fcc.miraiyochi_wazano[client_no];
					sp->hp_calc_work=sp->fcc.miraiyochi_damage[client_no];
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MIRAIYOCHI_DAMAGE);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					return;
				}
			}
		}
		sp->scc_seq_no++;
		sp->scc_work=0;
	case SIDE_CONDITION_CHECK_HOROBINOUTA:
		while(sp->scc_work<client_set_max){
			client_no=sp->psp_agi_work[sp->scc_work];
			if(sp->no_reshuffle_client&No2Bit(client_no)){
				sp->scc_work++;
				continue;
			}
			sp->scc_work++;
			//�ق�т̂���
			if(sp->psp[client_no].waza_kouka&WAZAKOUKA_HOROBINOUTA){
				if(sp->psp[client_no].wkw.horobinouta_count==0){
					sp->psp[client_no].waza_kouka&=WAZAKOUKA_HOROBINOUTA_OFF;
					sp->msg_work=sp->psp[client_no].wkw.horobinouta_count;
					sp->hp_calc_work=sp->psp[client_no].hp*-1;
					sp->server_status_flag|=SERVER_STATUS_FLAG_NO_BLINK;
				}
				else{
					sp->msg_work=sp->psp[client_no].wkw.horobinouta_count;
					sp->psp[client_no].wkw.horobinouta_count--;
				}
				sp->client_work=client_no;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HOROBINOUTA_COUNTDOWN);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				return;
			}
		}
		sp->scc_seq_no++;
		sp->scc_work=0;
	case SIDE_CONDITION_CHECK_TRICKROOM:					//�g���b�N���[�����ʐ؂�
		if(sp->field_condition&FIELD_CONDITION_TRICKROOM){
			sp->field_condition-=(1<<FIELD_TRICKROOM_SHIFT);
			if((sp->field_condition&FIELD_CONDITION_TRICKROOM)==0){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TRICKROOM_END);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				return;
			}
		}
		sp->scc_seq_no++;
		sp->scc_work=0;
		break;
	default:
		break;
	}
	sp->scc_seq_no=0;
	sp->scc_work=0;
	sp->server_seq_no=SERVER_TURN_END_NO;
}

//============================================================================================
/**
 *	�퓬�^�[���I������
 *
 * @param
 */
//============================================================================================
static	void	ServerTurnEnd(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//�o���l�擾�`�F�b�N
	if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
		return;
	}
	if(ServerZenmetsuCheck(bw,sp)==TRUE){
		return;
	}
	if(ServerReshuffleCheck(bw,sp)==TRUE){
		return;
	}

	sp->total_turn++;
	sp->sakidori_total_turn++;
	//�T�[�o���[�N�̏�����
	ST_ServerWorkInit(sp);
	ST_ServerOneTurnFlagInit(bw,sp);
	sp->server_seq_no=SERVER_TRAINER_MESSAGE_NO;
}

//============================================================================================
/**
 *	�����������쏈��
 *
 * @param
 */
//============================================================================================
static	void	ServerFightCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;

	flag=0;		//DefenceClient�����߂�flag

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		//WIFI�ڑ��ł́AAI���̂��Ă��Ȃ��̂ŁA�����_���ő����I��
		if(CommStateIsWifiConnect()){
			flag=1;
		}
	}
#endif PM_DEBUG

	sp->attack_client=sp->client_agi_work[sp->agi_cnt];
	//��邠�����t���O�������Ă����ꍇ�͂�邠�������Z�b�g
	if(sp->otf[sp->attack_client].waruagaki_flag){
		sp->waza_no_temp=WAZANO_WARUAGAKI;
		flag=1;
	}
	//�A���R�[�����󂯂Ă��鎞�́A�󂯂��Z�i���o�[���Z�b�g
	else if((sp->psp[sp->attack_client].wkw.encore_wazano)&&
			(sp->psp[sp->attack_client].wkw.encore_wazano==
			 sp->psp[sp->attack_client].waza[sp->psp[sp->attack_client].wkw.encore_wazapos])){
		sp->waza_no_temp=sp->psp[sp->attack_client].wkw.encore_wazano;
		flag=1;
	}
	//�A���R�[�����󂯂Ă���Z��Y�ꂽ��A���R�[��������
	else if((sp->psp[sp->attack_client].wkw.encore_wazano)&&
			(sp->psp[sp->attack_client].wkw.encore_wazano!=
			 sp->psp[sp->attack_client].waza[sp->psp[sp->attack_client].wkw.encore_wazapos])){
		sp->waza_no_temp=sp->psp[sp->attack_client].waza[sp->psp[sp->attack_client].wkw.encore_wazapos];
		sp->psp[sp->attack_client].wkw.encore_wazano=0;
		sp->psp[sp->attack_client].wkw.encore_wazapos=0;
		sp->psp[sp->attack_client].wkw.encore_count=0;
		flag=1;
	}
	//���ߋZ�n�̋Z���o���Ă����ꍇ�A�����œ����Ȃ��ꍇ�́A�O�^�[���̋Z�i���o�[���Z�b�g
	else if(ST_ServerCommandSelectCheck(sp,sp->attack_client)==FALSE){
		sp->waza_no_temp=sp->waza_no_keep[sp->attack_client];
	}
	//�I������Ă����Z��Y��Ă�����Defence���Ē��I����
	else if(sp->waza_no_select[sp->attack_client]!=
			sp->psp[sp->attack_client].waza[sp->waza_no_pos[sp->attack_client]]){
		sp->waza_no_temp=sp->psp[sp->attack_client].waza[sp->waza_no_pos[sp->attack_client]];
		flag=1;
	}
	else{
		sp->waza_no_temp=sp->psp[sp->attack_client].waza[sp->waza_no_pos[sp->attack_client]];
	}
	sp->waza_no_now=sp->waza_no_temp;
	sp->server_seq_no=SERVER_WAZA_BEFORE_NO;

	sp->defence_client=ST_ServerDefenceClientSet(bw,sp,sp->attack_client,sp->waza_no_temp,flag,0);

	SCIO_BlankMessage(bw);

	//�U���Ώۂ����Ȃ��̂ŁA�V�[�P���X�I���փW�����v�i���ƂŃ`�F�b�N�ɕύX�j
//	if(sp->defence_client==NONE_CLIENT_NO){
//		OS_TPrintf("�ΏۂȂ�: atk:%d def:%d\n",sp->attack_client,sp->defence_client);
//		sp->server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
//	}
}

//============================================================================================
/**
 *	����g�p����
 *
 * @param
 */
//============================================================================================
static	void	ServerItemCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ITEM_SELECT_RETURN_PARAM	*isrp;
	int							seq_no;

	sp->attack_client=sp->client_agi_work[sp->agi_cnt];
	sp->defence_client=ST_ServerDirClientGet(bw,sp,sp->attack_client);
	isrp=(ITEM_SELECT_RETURN_PARAM *)&sp->client_act_work[sp->attack_client][ACT_PARA_WORK];

	if(BattleWorkMineEnemyCheck(bw,sp->attack_client)){
		switch(sp->AIWT.AI_ITEM_TYPE[sp->attack_client>>1]){
		case ITEMTYPE_KAIHUKUNOKUSURI:
			seq_no=SUB_SEQ_TRUSE_KAIHUKUNOKUSURI;
			break;
		case ITEMTYPE_HP_KAIHUKU:
			seq_no=SUB_SEQ_TRUSE_RECV_HP;
			break;
		case ITEMTYPE_CONDITION_KAIHUKU:
			if((sp->AIWT.AI_ITEM_CONDITION[sp->attack_client>>1]&1)&&
			   (sp->AIWT.AI_ITEM_CONDITION[sp->attack_client>>1]&0x3e)){
				sp->msg_work=ITEM_USE_MSG_RECV_MULTI;
			}
			else{
				sp->msg_work=Bit2No(sp->AIWT.AI_ITEM_CONDITION[sp->attack_client>>1]);
			}
			seq_no=SUB_SEQ_TRUSE_RECV_CONDITION;
			break;
		case ITEMTYPE_ABIRITY_UP:
			sp->msg_work=sp->AIWT.AI_ITEM_CONDITION[sp->attack_client>>1];
			seq_no=SUB_SEQ_TRUSE_ABIRITY_UP;
			break;
		case ITEMTYPE_EFFECT_GUARD:
			seq_no=SUB_SEQ_TRUSE_EFFECT_GUARD;
			break;
		}
		sp->item_work=sp->AIWT.AI_ITEM_NO[sp->attack_client>>1];
	}
	else{
		switch(isrp->page){
		case BBAG_POKE_STRCV:	// ��ԉ񕜃|�P�b�g
		case BBAG_POKE_HPRCV:	// HP�񕜃|�P�b�g
		case BBAG_POKE_BATTLE:	// �퓬�p�|�P�b�g
			if((isrp->item_no==ITEM_PIPPININGYOU)||
			   (isrp->item_no==ITEM_ENEKONOSIPPO)){
				seq_no=SUB_SEQ_ITEM_ESCAPE;
			}
			else{
				seq_no=SUB_SEQ_ITEM_BATTLE_ITEM;
			}
			break;
		case BBAG_POKE_BALL:	// �{�[���|�P�b�g
			seq_no=SUB_SEQ_BALL_THROW;
			if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TRAINER)==0)&&
			   ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_GET_DEMO)==0)){
				MyItem_SubItem( BattleWorkMyItemGet(bw), isrp->item_no, 1, HEAPID_BATTLE );
				MyItem_BattleBagLastItemSet( BattleWorkBagCursorGet(bw), isrp->item_no, isrp->page );
			}
			break;
		}
		sp->item_work=isrp->item_no;
	}

	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	sp->next_server_seq_no=SERVER_WAZA_END_NO;
	//�Z�͔������Ă��Ȃ��̂ŁA���s�ɂ���
	sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI;
}

//============================================================================================
/**
 *	�|�P�����I������
 *
 * @param
 */
//============================================================================================
static	void	ServerPokemonCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_POKEMON_RESHUFFLE);
	sp->attack_client=sp->client_agi_work[sp->agi_cnt];
	sp->reshuffle_client=sp->attack_client;
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//	sp->next_server_seq_no=SERVER_POKE_RESHUFFLE_AFTER_NO;		///<�|�P�������ꂩ����V�[�P���X
	sp->next_server_seq_no=SERVER_WAZA_END_NO;
	sp->temp_work=0;	//��������̂��ꂩ���������l�����Ă���
	//�Z�͔������Ă��Ȃ��̂ŁA���s�ɂ���
	sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI;
}

//============================================================================================
/**
 *	�ɂ��铮�쏈��
 *
 * @param
 */
//============================================================================================
static	void	ServerEscapeCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	sp->attack_client=sp->client_agi_work[sp->agi_cnt];

	//�G����100%�œ�����
	if((BattleWorkMineEnemyCheck(bw,sp->attack_client))&&
	  ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO)==0)){
		//�������Ȃ��Z���ʂ��󂯂Ă��鎞�́A�������Ȃ�
		if(sp->psp[sp->attack_client].condition2&(CONDITION2_SHIME|CONDITION2_KUROIMANAZASHI)){
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ENEMY_ESCAPE_NG);
			sp->skill_seq_no=0;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_WAZA_END_NO;
		}
		else{
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ENEMY_ESCAPE);
			sp->skill_seq_no=0;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_FIGHT_END_NO;
		}
	}
	else{
		if(ST_EscapeActCheck(bw,sp,sp->attack_client)){
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ESCAPE);
			sp->skill_seq_no=0;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_FIGHT_END_NO;
		}
		else{
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ESCAPE_NG);
			sp->skill_seq_no=0;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_WAZA_END_NO;
		}
	}
}

//============================================================================================
/**
 *	�T�t�@���Ń{�[�������鏈��
 *
 * @param
 */
//============================================================================================
static	void	ServerSafariBallCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	ball;

	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SAFARI_BALL_THROW);
	sp->attack_client=CLIENT_NO_MINE;
	sp->defence_client=CLIENT_NO_ENEMY;
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	sp->next_server_seq_no=SERVER_WAZA_END_NO;
	sp->item_work=ITEM_SAFARIBOORU;
	ball=BattleWorkSafariBallCountGet(bw)-1;
	BattleWorkSafariBallCountSet(bw,ball);
	SCIO_HPGaugeRefreshSet(bw,sp,CLIENT_NO_MINE);
}

//============================================================================================
/**
 *	�T�t�@���ŃG�T�����鏈��
 *
 * @param
 */
//============================================================================================
static	void	ServerSafariEsaCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_ESA_THROW);
	sp->attack_client=CLIENT_NO_MINE;
	sp->defence_client=CLIENT_NO_ENEMY;
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	sp->next_server_seq_no=SERVER_WAZA_END_NO;
	sp->temp_work=gf_rand()%SAFARI_ATARI;
	if(sp->safari_get_count<SAFARI_COUNT_MAX){
		sp->safari_get_count++;
	}
	//�哖����̎��́A�ߊl���̂ݏ㏸
	if(sp->temp_work!=0){
		if(sp->safari_escape_count<SAFARI_COUNT_MAX){
			sp->safari_escape_count++;
		}
	}
}

//============================================================================================
/**
 *	�T�t�@���Ńh�������鏈��
 *
 * @param
 */
//============================================================================================
static	void	ServerSafariDoroCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_DORO_THROW);
	sp->attack_client=CLIENT_NO_MINE;
	sp->defence_client=CLIENT_NO_ENEMY;
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	sp->next_server_seq_no=SERVER_WAZA_END_NO;
	sp->temp_work=gf_rand()%SAFARI_ATARI;
	if(sp->safari_escape_count){
		sp->safari_escape_count--;
	}
	//�哖����̎��́A�������̂݉��~
	if(sp->temp_work!=0){
		sp->msg_work=1;
		if(sp->safari_get_count){
			sp->safari_get_count--;
		}
	}
}

//============================================================================================
/**
 *	�T�t�@���ŗl�q������
 *
 * @param
 */
//============================================================================================
static	void	ServerSafariYousumiCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_YOUSUMI);
	sp->attack_client=CLIENT_NO_MINE;
	sp->defence_client=CLIENT_NO_ENEMY;
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	sp->next_server_seq_no=SERVER_WAZA_END_NO;
}

//============================================================================================
/**
 *	�o�b�W�`�F�b�N
 *
 * @param
 */
//============================================================================================
static	int	ServerBadgeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	int			i,j;
	u32			fight_type;
	u8			level=0;
	MYSTATUS	*status;

	fight_type=BattleWorkFightTypeGet(bw);
	status=BattleWorkMyStatusGet(bw,CLIENT_NO_MINE);

	//�o�b�W�`�F�b�N���Ȃ�FIGHT_TYPE���`�F�b�N
	if(fight_type&FIGHT_TYPE_NO_BADGE){
		return 0;
	}
	//�G���́A�o�b�W�`�F�b�N�Ȃ�
	if(BattleWorkMineEnemyCheck(bw,sp->attack_client)){
		return 0;
	}
	//�s���ȃ|�P�������`�F�b�N
//	if(HuseiPokemonCheck(AttackClient)){
//		return 0;
//	}
	//AI�}���`�ΐ�ŁA�p�[�g�i�[��������o�b�W�`�F�b�N�͂��Ȃ�
	if((fight_type&FIGHT_TYPE_AI)&&(BattleWorkClientTypeGet(bw,sp->attack_client)==CLIENT_TYPE_C)){
		return 0;
	}
	//�����̎����|�P������������o�b�W�`�F�b�N�͂��Ȃ�
	if((ST_ServerPokeOneSelfCheckAct(bw,sp))==TRUE){
		return 0;
	}
	//�R�}���h�I���̂Ȃ��Z�����łɏo���Ă���Ȃ�o�b�W�`�F�b�N�͂��Ȃ�
	if(ST_ServerCommandSelectCheck(sp,sp->attack_client)==FALSE){
		return 0;
	}
	//�o�b�W�����ׂĂ����Ă���Ȃ�`�F�b�N�͂��Ȃ�
//	if(MyStatus_GetBadgeFlag(status,BADGE_ID_C08)){
	if(MyStatus_GetBadgeCount(status)>=8){
		return 0;
	}
	
	level=10;
//	if(MyStatus_GetBadgeFlag(status,BADGE_ID_C02)){
	if(MyStatus_GetBadgeCount(status)>=2){
		level=30;
	}
//	if(MyStatus_GetBadgeFlag(status,BADGE_ID_C04)){
	if(MyStatus_GetBadgeCount(status)>=4){
		level=50;
	}
//	if(MyStatus_GetBadgeFlag(status,BADGE_ID_C06)){
	if(MyStatus_GetBadgeCount(status)>=6){
		level=70;
	}

	//�o�b�W�ŉ��ւ���Ă��郌�x���Ȃ炢�����Ƃ𕷂�
	if(sp->psp[sp->attack_client].level<=level){
		return 0;
	}

	i=((gf_rand()&0xff)*(sp->psp[sp->attack_client].level+level))>>8;

	if(i<level){
		return 0;
	}

	//�������I�����Ă����Ȃ�A�{���e�[�W�������Ȃ��悤�ɂ���
	if(sp->waza_no_now==WAZANO_IKARI){
		sp->psp[sp->attack_client].condition2&=CONDITION2_IKARI_OFF;
	}

	if((sp->psp[sp->attack_client].condition&CONDITION_NEMURI)&&
	  ((sp->waza_no_now==WAZANO_IBIKI)||(sp->waza_no_now==WAZANO_NEGOTO))){
		seq_no[0]=SUB_SEQ_ORDER_IGNORE_SLEEP;	//���ߖ����i�˂ނ�j
		return 1;
	}

	i=((gf_rand()&0xff)*(sp->psp[sp->attack_client].level+level))>>8;

#ifndef ORDER_IGNORE_ONLY
	if(i<level){
#endif ORDER_IGNORE_ONLY
		i=ST_ServerWaruagakiCheck(bw,sp,sp->attack_client,No2Bit(sp->waza_no_pos[sp->attack_client]),SSWC_ALL);
		if(i==0x0f){		//�o����Z���Ȃ�
			seq_no[0]=SUB_SEQ_NAMAKERU;		//���ߖ����i�Ȃ܂���j
			return 1;
		}
		do{
			j=gf_rand()&3;
		}while(i&No2Bit(j));
		sp->waza_no_pos[sp->attack_client]=j;
		sp->waza_no_temp=sp->psp[sp->attack_client].waza[sp->waza_no_pos[sp->attack_client]];
		sp->waza_no_now=sp->waza_no_temp;
		sp->defence_client=ST_ServerDefenceClientSet(bw,sp,sp->attack_client,sp->waza_no_temp,1,0);
		seq_no[0]=SUB_SEQ_ORDER_IGNORE;		//���ߖ���
		sp->waza_out_check_on_off|=BADGE_CHECK_OFF;
		return 2;
#ifndef ORDER_IGNORE_ONLY
	}
#endif ORDER_IGNORE_ONLY

	level=sp->psp[sp->attack_client].level-level;
	i=gf_rand()&0xff;

	if(((i<level)&&((sp->psp[sp->attack_client].condition&CONDITION_BAD)==0))&&
	    (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_YARUKI)&&
	    (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_HUMIN)&&
	    (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_RIIHUGAADO)){
		if((sp->field_condition&FIELD_CONDITION_SAWAGU)==0){
			seq_no[0]=SUB_SEQ_HIRUNE;				//���ߖ����i�Ђ�ˁj
			return 1;
		}
	}

	i-=level;

	if(i<level){
		sp->defence_client=sp->attack_client;
		sp->client_work=sp->defence_client;
		//�����ւ̍U���́A�͂������З͂S�O�Ōv�Z�����_���[�W
		sp->hp_calc_work=ST_WazaDamageCalc(bw,sp,
										   WAZANO_HATAKU,
										   0,
										   0,
										   40,
										   0,
										   sp->attack_client,
										   sp->attack_client,
										   1);
		sp->hp_calc_work=ST_DamageLossCalc(sp,sp->hp_calc_work);
		sp->hp_calc_work*=-1;
		seq_no[0]=SUB_SEQ_OWN_ATTACK;			//���ߖ����i�������U���j
		return 3;
	}

	seq_no[0]=SUB_SEQ_NAMAKERU;			//���ߖ����i�Ȃ܂���j

	return 1;
}


//============================================================================================
/**
 *	PP�`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerPPCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	decpp=1;
	int	pos;

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_NO_PP_DEC){
		return	FALSE;
	}
#endif PM_DEBUG

//����\�̓v���b�V���[��PP���{����
	if((sp->ostf[sp->attack_client].no_pressure_flag==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
		//�ӂ�����́ARANGE_DOUBLE�Ɠ�������������
		if(sp->waza_no_temp==WAZANO_HUUIN){
			decpp+=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,sp->attack_client,TOKUSYU_PURESSYAA);
		}
		else{
			switch(sp->AIWT.wtd[sp->waza_no_temp].attackrange){
			case RANGE_TRIPLE:
			case RANGE_FIELD:
				decpp+=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE_HP,sp->attack_client,TOKUSYU_PURESSYAA);
				break;
			case RANGE_DOUBLE:
			case RANGE_MAKIBISHI:
				decpp+=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,sp->attack_client,TOKUSYU_PURESSYAA);
				break;
			case RANGE_MINE_DOUBLE:
			case RANGE_MINE:
			case RANGE_TUBOWOTUKU:
			case RANGE_TEDASUKE:
				break;
			default:
				if((sp->attack_client!=sp->defence_client)&&
				   (ST_ServerTokuseiGet(sp,sp->defence_client)==TOKUSYU_PURESSYAA)){
					decpp++;
				}
				break;
			}
		}
	}

	pos=ST_ServerWazaPosGet(&sp->psp[sp->attack_client],sp->waza_no_temp);

	//��邠�����́APPCheck�͖���
	if((sp->otf[sp->attack_client].pp_dec_flag==0)&&(sp->otf[sp->attack_client].waruagaki_flag==0)){
		sp->otf[sp->attack_client].pp_dec_flag=1;
		if((sp->psp[sp->attack_client].pp[pos])&&(pos<WAZA_TEMOTI_MAX)){
			if(sp->psp[sp->attack_client].pp[pos]>decpp){
				sp->psp[sp->attack_client].pp[pos]-=decpp;
			}
			else{
				sp->psp[sp->attack_client].pp[pos]=0;
			}
			ST_PSPtoPPCopy(bw,sp,sp->attack_client);
		}
#ifdef PM_DEBUG
		else if(pos>=WAZA_TEMOTI_MAX){
			GF_ASSERT_MSG(0,"�莝���ɂȂ��Z��PP�����炻���Ƃ��Ă���I\n");
		}
#endif PM_DEBUG
		else{
			sp->waza_status_flag|=WAZA_STATUS_FLAG_PP_NONE;
		}
	}
	//PP���Ȃ��`�F�b�N
	else if((sp->psp[sp->attack_client].pp[pos]==0)&&
		   ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER)==0)&&
		   ((sp->psp[sp->attack_client].condition2&CONDITION2_KEEP)==0)&&
		   ((sp->psp[sp->attack_client].condition2&CONDITION2_ABARERU)==0)&&
			(pos<WAZA_TEMOTI_MAX)){
		sp->waza_status_flag|=WAZA_STATUS_FLAG_PP_NONE;
	}
	
	return FALSE;
}

//============================================================================================
/**
 *	�U���Ώۃ`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerDefenceCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret;

	ret=FALSE;

	//�U���Ώۂ����Ȃ��ꍇ�́A���̎|�̃��b�Z�[�W��\�����ďI���i���߃^�[���͏����j
	if(((sp->defence_client==NONE_CLIENT_NO)&&(ST_TameWazaCheck(sp,sp->waza_no_now)==FALSE))||
	   ((sp->defence_client==NONE_CLIENT_NO)&&
		(ST_TameWazaCheck(sp,sp->waza_no_now)==TRUE)&&
	   ((sp->psp[sp->attack_client].condition2&CONDITION2_KEEP)||
		(sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER)))){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NO_DEFENCE);
		sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		ret=TRUE;
	}

	return ret;
}

//============================================================================================
/**
 *	TYPE�`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerTypeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//�����I���̋Z�A�З͖��A�^�C�v�������A���ߋZ�n��1�^�[���ڂ́ATYPE�`�F�b�N�����Ȃ��A
	//�u�ł񂶂́v�́A�n�ʂɓ��ĂȂ��悤�ɂ��邽�߂ɁA�`�F�b�N����
//	if((WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_attackrange)!=RANGE_MINE)&&
//	   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage))&&
	if(((sp->AIWT.wtd[sp->waza_no_now].attackrange!=RANGE_MINE)&&
	    (sp->AIWT.wtd[sp->waza_no_now].attackrange!=RANGE_MINE_DOUBLE)&&
	    (sp->AIWT.wtd[sp->waza_no_now].damage)&&
	   ((sp->server_status_flag&SERVER_STATUS_FLAG_TYPE_NONE)==0)&&
	   ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0))||
	    (sp->waza_no_now==WAZANO_DENZIHA)){
		sp->damage=ST_ServerTypeCheck(bw,sp,sp->waza_no_now,sp->waza_type,sp->attack_client,sp->defence_client,sp->damage,&sp->waza_status_flag);
		if(sp->waza_status_flag&WAZA_STATUS_FLAG_KOUKANAI){
			sp->wocf[sp->attack_client].koukanai_flag=1;
		}
	}
	return FALSE;
}

//============================================================================================
/**
 *	��Ԉُ�`�F�b�N�̃V�[�P���X�i���o�[
 */
//============================================================================================
enum{
	SSC_INIT=0,		//�`�F�b�N������
	SSC_NEMURI,		//�˂ނ�`�F�b�N
	SSC_KOORI,		//������`�F�b�N
	SSC_NAMAKE,		//�Ȃ܂��`�F�b�N
	SSC_HANDOU,		//�͂�ǂ��`�F�b�N
	SSC_HIRUMU,		//�Ђ�ރ`�F�b�N
	SSC_KANASIBARI,	//���Ȃ��΂�`�F�b�N
	SSC_TYOUHATU,	//���傤�͂`�F�b�N
	SSC_HUUIN,		//�ӂ�����`�F�b�N
	SSC_JUURYOKU,	//���イ��傭�`�F�b�N
	SSC_HEALBLOCK,	//�q�[���u���b�N�`�F�b�N
	SSC_KONRAN,		//������`�F�b�N
	SSC_MAHI,		//�܂Ѓ`�F�b�N
	SSC_MEROMERO,	//���������`�F�b�N
	SSC_GAMAN,		//���܂�`�F�b�N
	SSC_MELT,		//�Ƃ���`�F�b�N
	SSC_END			//�`�F�b�N�G���h
};

enum{
	SSC_ACT_LOOP=0,			//�`�F�b�N�p��
	SSC_ACT_NO_WAZA_OUT,	//�Z�̔������ł��Ȃ�
	SSC_ACT_WAZA_SEQ,		//���b�Z�[�W�\���Ȃǂ̃V�[�P���X��
	SSC_ACT_END				//�`�F�b�N�̏I��
};

//============================================================================================
/**
 *	��Ԉُ�`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	battle_effect;
	int	ret;

//	battle_effect=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_battleeffect);
	battle_effect=sp->AIWT.wtd[sp->waza_no_now].battleeffect;

	ret=SSC_ACT_LOOP;
	
	do{
		switch(sp->ssc_seq_no){
		case SSC_INIT:		//�`�F�b�N������
			//�݂��Â�t���O��OFF
			sp->psp[sp->attack_client].condition2&=CONDITION2_MICHIDURE_OFF;
			//����˂�t���O��OFF
			sp->psp[sp->attack_client].waza_kouka&=WAZAKOUKA_ONNEN_OFF;
			sp->ssc_seq_no++;
			break;
		case SSC_NEMURI:		//�˂ނ�`�F�b�N
			//�����Ă���Ƃ��́A�N����`�F�b�N
			if(sp->psp[sp->attack_client].condition&CONDITION_NEMURI){
				{
					int	cnt;
		
					//����������ԂŁA�����������ڂ�����������Ă��Ȃ��Ƃ��͋N����
					if((sp->field_condition&FIELD_CONDITION_SAWAGU)&&
					   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_BOUON)){
						sp->client_work=sp->attack_client;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MEZAME);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						ret=SSC_ACT_WAZA_SEQ;
					}
					else{
						//�˂��Ƃ̔h���ł́A�˂ނ�J�E���^��DEC�����Ȃ�
						if(((sp->waza_no_now!=WAZANO_NEGOTO)&&(sp->waza_no_temp==WAZANO_NEGOTO))==0){
							//����\�͂͂₨���́A�͂₭�˂ނ肩�炳�߂�
							if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_HAYAOKI){
								cnt=2;
							}
							else{
								cnt=1;
							}
							if((sp->psp[sp->attack_client].condition&CONDITION_NEMURI)<cnt){
								sp->psp[sp->attack_client].condition&=CONDITION_NEMURI_OFF;
							}
							else{
								sp->psp[sp->attack_client].condition-=cnt;
							}
							if(sp->psp[sp->attack_client].condition&CONDITION_NEMURI){
								//�˂��ƂƂ��т��́A�Q�Ă��Ă��Z���o����̂Ŗ�������
								if((sp->waza_no_now!=WAZANO_IBIKI)&&(sp->waza_no_temp!=WAZANO_NEGOTO)){
									ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SLEEPING);
									sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//									sp->next_server_seq_no=SERVER_WAZA_END_NO;
									sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
									ret=SSC_ACT_WAZA_SEQ;
								}
							}
							else{
								sp->client_work=sp->attack_client;
								ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MEZAME);
								sp->next_server_seq_no=sp->server_seq_no;
								sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
								ret=SSC_ACT_WAZA_SEQ;
							}
						}
					}
				}
			}
			sp->ssc_seq_no++;
			break;
		case SSC_KOORI:		//������`�F�b�N
			//�����Ă���Ƃ��́A�Ƃ���`�F�b�N
			if(sp->psp[sp->attack_client].condition&CONDITION_KOORI){
				//5����1�̊m���ŗn����
				if(gf_rand()%5!=0){
					if((battle_effect!=125)&&(battle_effect!=253)){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_FREEZING);
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//						sp->next_server_seq_no=SERVER_WAZA_END_NO;
						sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
						ret=SSC_ACT_NO_WAZA_OUT;
					}
				}
				else{
					sp->client_work=sp->attack_client;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MELT);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=SSC_ACT_WAZA_SEQ;
				}
			}
			sp->ssc_seq_no++;
			break;
		case SSC_NAMAKE:		//�Ȃ܂��`�F�b�N
			if(ST_ServerNamakeCheck(sp,sp->attack_client)==TRUE){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NAMAKE);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_HANDOU:		//�͂�ǂ��`�F�b�N
			if(sp->psp[sp->attack_client].condition2&CONDITION2_HANDOU){
				sp->psp[sp->attack_client].condition2&=CONDITION2_HANDOU_OFF;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HANDOU_NOHIT);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_HIRUMU:		//�Ђ�ރ`�F�b�N
			//�Ђ��ł��鎞�͋Z���o���Ȃ�
			if(sp->psp[sp->attack_client].condition2&CONDITION2_HIRUMU){
				sp->psp[sp->attack_client].condition2&=CONDITION2_HIRUMU_OFF;
				sp->wocf[sp->attack_client].hirumu_flag=1;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HIRUMU_WAZA_NO_HIT);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_KANASIBARI:	//���Ȃ��΂�`�F�b�N
			if(sp->psp[sp->attack_client].wkw.kanashibari_wazano==sp->waza_no_temp){
				sp->wocf[sp->attack_client].kanashibari_flag=1;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_KANASIBARI_NG);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_TYOUHATU:	//���傤�͂`�F�b�N
//			if((sp->psp[sp->attack_client].wkw.chouhatsu_count)&&(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage)==0)){
			if((sp->psp[sp->attack_client].wkw.chouhatsu_count)&&(sp->AIWT.wtd[sp->waza_no_now].damage==0)){
				sp->wocf[sp->attack_client].chouhatsu_flag=1;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_CHOUHATSU_NG);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_HUUIN:		//�ӂ�����`�F�b�N
			if(ST_ServerHuuinCheck(bw,sp,sp->attack_client,sp->waza_no_now)){
				sp->wocf[sp->attack_client].huuin_flag=1;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HUUIN_NG);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_JUURYOKU:	//���イ��傭�`�F�b�N
			if(ST_ServerJuuryokuCheck(bw,sp,sp->attack_client,sp->waza_no_now)){
				sp->wocf[sp->attack_client].juuryoku_flag=1;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_JUURYOKU_NG);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_HEALBLOCK:	//�q�[���u���b�N�`�F�b�N
			if(ST_ServerHealblockCheck(bw,sp,sp->attack_client,sp->waza_no_now)){
				sp->wocf[sp->attack_client].healblock_flag=1;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HEALBLOCK_NG);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_KONRAN:		//������`�F�b�N
			sp->ssc_seq_no++;
			if(sp->psp[sp->attack_client].condition2&CONDITION2_KONRAN){		//������`�F�b�N
				sp->psp[sp->attack_client].condition2-=KONRAN_COUNT;
				if(sp->psp[sp->attack_client].condition2&CONDITION2_KONRAN){
					if(gf_rand()&1){
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_CONFUSE);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						ret=SSC_ACT_WAZA_SEQ;
					}
					else{
						sp->wocf[sp->attack_client].konran_flag=1;
						sp->defence_client=sp->attack_client;
						sp->client_work=sp->defence_client;
						//�����ւ̍U���́A��邠�������З͂S�O�Ōv�Z�����_���[�W�i�����e�N�j�V�����𔭓������Ȃ����߁j
						sp->hp_calc_work=ST_WazaDamageCalc(
												bw,sp,
												WAZANO_WARUAGAKI,
												0,
												0,
												40,
												0,
												sp->attack_client,
												sp->attack_client,
												1);
						sp->hp_calc_work=ST_DamageLossCalc(sp,sp->hp_calc_work);
						sp->hp_calc_work*=-1;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_CONFUSE_MINE_ATTACK);
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->next_server_seq_no=SERVER_KIZETSU_EFFECT_NO;
						ret=SSC_ACT_NO_WAZA_OUT;
					}
				}
				else{
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_CONFUSE_END);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=SSC_ACT_WAZA_SEQ;
				}
			}
			break;
		case SSC_MAHI:		//�܂Ѓ`�F�b�N
			if((sp->psp[sp->attack_client].condition&CONDITION_MAHI)&&
				//�����}�W�b�N�K�[�h�́A�܂Ђ̌��ʂ������Ȃ�
			   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)){
				if(gf_rand()%4==0){
					sp->wocf[sp->attack_client].mahi_flag=1;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_PARALYSIS);
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//					sp->next_server_seq_no=SERVER_WAZA_END_NO;
					sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
					ret=SSC_ACT_NO_WAZA_OUT;
				}
			}
			sp->ssc_seq_no++;
			break;
		case SSC_MEROMERO:	//���������`�F�b�N
			if(sp->psp[sp->attack_client].condition2&CONDITION2_MEROMERO){
				sp->client_work=Bit2No((sp->psp[sp->attack_client].condition2&CONDITION2_MEROMERO)>>MEROMERO_SHIFT);
				if(gf_rand()&1){
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MEROMERO_KEEP);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=SSC_ACT_WAZA_SEQ;
				}
				else{
					sp->wocf[sp->attack_client].meromero_flag=1;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MEROMERO_NG);
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//					sp->next_server_seq_no=SERVER_WAZA_END_NO;
					sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
					ret=SSC_ACT_NO_WAZA_OUT;
				}
			}
			sp->ssc_seq_no++;
			break;
		case SSC_GAMAN:		//���܂�`�F�b�N
			sp->ssc_seq_no++;
			if(sp->psp[sp->attack_client].condition2&CONDITION2_GAMAN){
				sp->psp[sp->attack_client].condition2-=GAMAN_COUNT;
				if((sp->psp[sp->attack_client].condition2&CONDITION2_GAMAN)==0){
					if(sp->store_damage[sp->attack_client]){
						sp->damage=sp->store_damage[sp->attack_client]*2;
						if(sp->psp[sp->client_no_hit[sp->attack_client]].hp){
							sp->defence_client=sp->client_no_hit[sp->attack_client];
						}
						else{
							sp->defence_client=ST_ServerDirClientGet(bw,sp,sp->attack_client);
							if(sp->psp[sp->defence_client].hp==0){
								ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_GAMAN_NO_DEFENCE);
								sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
								sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
								ret=SSC_ACT_WAZA_SEQ;
								break;
							}
						}
					}
				}
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_GAMAN_AFTER);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=SSC_ACT_WAZA_SEQ;
			}
			break;
		case SSC_MELT:		//�Ƃ���`�F�b�N
			if(sp->psp[sp->attack_client].condition&CONDITION_KOORI){
				if((battle_effect==125)||(battle_effect==253)){
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_MELT);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=SSC_ACT_WAZA_SEQ;
				}
			}
			sp->ssc_seq_no++;
			break;
		case SSC_END:		//�`�F�b�N�G���h
			sp->ssc_seq_no=SSC_INIT;
			ret=SSC_ACT_END;
			break;
		}
	}while(ret==SSC_ACT_LOOP);

	ST_PSPtoPPCopy(bw,sp,sp->attack_client);

	if(ret==SSC_ACT_NO_WAZA_OUT){
		//�Z�̋N���Ɏ��s���Ă���Ȃ�A�����̂ɓ�����`�F�b�N�����Ȃ��t���O�𗧂Ă�
		sp->server_status_flag|=SERVER_STATUS_FLAG_NO_DOUBLE_CHECK;
		//�Z�̋N���Ɏ��s���Ă���Ȃ�A���s�t���O�𗧂Ă�
		sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI;
	}
	return (ret!=SSC_ACT_END);
}
	
//============================================================================================
/**
 *	�����`�F�b�N�̃V�[�P���X�i���o�[
 */
//============================================================================================
enum{
	STC_DAMAGE=0,		//�_���[�W���󂯎~�߂�����`�F�b�N
	STC_END
};

enum{
	STC_ACT_LOOP=0,			//�`�F�b�N�p��
	STC_ACT_WAZA_SEQ,		//���b�Z�[�W�\���Ȃǂ̃V�[�P���X��
	STC_ACT_END				//�`�F�b�N�̏I��
};

//============================================================================================
/**
 *	�����`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	ret;
	int	seq_no;

	ret=STC_ACT_LOOP;

	do{
		switch(sp->stc_seq_no){
		case STC_DAMAGE:
			//�����Ń_���[�W���󂯎~�߂�`�F�b�N
			seq_no=ST_ServerDamageTokuseiCheck(sp,sp->attack_client,sp->defence_client);
			if(((seq_no)&&((sp->waza_status_flag&WAZA_STATUS_FLAG_HAZURE)==0))||
				(seq_no==SUB_SEQ_BOUON)){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				//�Z�̋N���Ɏ��s���Ă���Ȃ�A���s�t���O�𗧂Ă�
				//sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK;
				sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI;
				ret=STC_ACT_WAZA_SEQ;
			}
			sp->stc_seq_no++;
			break;
		case STC_END:
			sp->stc_seq_no=0;
			ret=STC_ACT_END;
			break;
		}
	}while(ret==STC_ACT_LOOP);
	
	return (ret!=STC_ACT_END);
}

//============================================================================================
/**
 *	�搧�n�̃A�C�e�����ʂ̃`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerSenseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_SENSEI_CHECK);
	sp->next_server_seq_no=sp->server_seq_no;
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;

	return TRUE;
}

//============================================================================================
/**
 *	abiritycnt�ɂ�閽�����ω��e�[�u��
 */
//============================================================================================

typedef struct{
	u8	kakeru;
	u8	waru;
}HitProbabilityTable;

static	const	HitProbabilityTable	HPT[]={
	{
	33,100			// 0.33
	},
	{
	36,100			//  0.36
	},
	{
	43,100			//  0.43
	},
	{
	50,100			//  0.50
	},
	{
	60,100			//  0.60
	},
	{
	75,100			//  0.75
	},
	{
	1,1				//  1.00
	},
	{
	133,100			//  1.33
	},
	{
	166,100			//  1.66
	},
	{
	2,1				//  2.00
	},
	{
	233,100			//  2.33
	},
	{
	133,50			//  2.66
	},
	{
	3,1				//  3.00
	},
};

//============================================================================================
/**
 *	�������`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerHitCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no)
{
	u16		hit;
	s8		value;
	s8		cond_hit,cond_avoid;
	int		eqp;
	int		atk;
	u8		wazatype;
	u8		wazakind;

	//�ߊl�f���́A100%����
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_GET_DEMO){
		return FALSE;
	}

	//�����m�[�}���X�L���́A�^�C�v���m�[�}����
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(sp->waza_type){
		wazatype=sp->waza_type;
	}
	else{
//		wazatype=WT_WazaDataParaGet(waza_no,ID_WTD_wazatype);
		wazatype=sp->AIWT.wtd[waza_no].wazatype;
	}
//	wazakind=WT_WazaDataParaGet(waza_no,ID_WTD_kind);
	wazakind=sp->AIWT.wtd[waza_no].kind;

	cond_hit=sp->psp[attack].abiritycnt[COND_HIT]-6;
	cond_avoid=6-sp->psp[defence].abiritycnt[COND_AVOID];

	//�������񂶂��������Ă���Ƃ��́A�q�b�g���㏸��{
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_TANZYUN){
		cond_hit*=2;
	}

	//�������񂶂��������Ă���Ƃ��́A��𗦏㏸��{
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TANZYUN)==TRUE){
		cond_avoid*=2;
	}

	//�����Ă�˂�������Ă���Ƃ��́A�q�b�g�����t���b�g��
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TENNEN)==TRUE){
		cond_hit=0;
	}

	//�����Ă�˂�������Ă���Ƃ��́A��𗦂��t���b�g��
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_TENNEN){
		cond_avoid=0;
	}

	//�݂�Ԃ�A�����킯��A�~���N���A�C���ʂ̂���Ƃ��́A�㏸���Ă����𗦂����ɖ߂�
	if(((sp->psp[defence].condition2&CONDITION2_MIYABURU)||(sp->psp[defence].waza_kouka&WAZAKOUKA_MIRACLE_EYE))&&
		(cond_avoid<0)){
		cond_avoid=0;
	}

	value=6+cond_avoid+cond_hit;

	if(value<0){
		value=0;
	}
	if(value>12){
		value=12;
	}

//	hit=WT_WazaDataParaGet(waza_no,ID_WTD_hitprobability);
	hit=sp->AIWT.wtd[waza_no].hitprobability;

	//������0�́A�G�N�Z����Łu�|�v�Ȃ̂Ő�΂ɓ�����
	if(hit==0){
		return FALSE;
	}

	//���ߋZ�n��1�^�[���ڂ́A�������Ɋ֌W�Ȃ��Z�𔭓�
	if(sp->server_status_flag&SERVER_STATUS_FLAG_TAME){
		return FALSE;
	}

	//�ʂ̖������v�Z�����Ă��鎞�́A�������̌v�Z�͂��Ȃ�
	if(sp->server_status_flag&SERVER_STATUS_FLAG_OTHER_HIT_CALC){
		return FALSE;
	}

	//����\�͂̂��Ă񂫂́A�`�F�b�N�����Ȃ�
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//����̂Ƃ��A���݂Ȃ�͖�������50%�ɂ���
//		if((sp->field_condition&FIELD_CONDITION_HARE_ALL)&&(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)==152)){
		if((sp->field_condition&FIELD_CONDITION_HARE_ALL)&&(sp->AIWT.wtd[waza_no].battleeffect==152)){
			hit=50;
		}
	}

	hit*=HPT[value].kakeru;
	hit/=HPT[value].waru;

	//����\�͂ӂ�����́A���������R�O���A�b�v
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_HUKUGAN){
		hit=hit*130/100;
	}

	//����\�͂̂��Ă񂫂́A�`�F�b�N�����Ȃ�
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//����\�͂��Ȃ�����́A���������Q�O���_�E���i���Ȃ��炵�̎��Ɂj
		if(sp->field_condition&FIELD_CONDITION_SUNAARASHI_ALL){
			if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_SUNAGAKURE)==TRUE){
				hit=hit*80/100;
			}
		}
		//�����Ⴊ����́A���������Q�O���_�E���i�����̎��Ɂj
		if(sp->field_condition&FIELD_CONDITION_ARARE_ALL){
			if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_YUKIGAKURE)==TRUE){
				hit=hit*80/100;
			}
		}
		//�V�󂪂ӂ�������̎��́A��������6/10�ɂ���
		if(sp->field_condition&FIELD_CONDITION_HUKAIKIRI){
			hit=hit*6/10;
		}
	}

	//����\�͂͂肫��́A�����U���̖��������Q�O���_�E��
	if((ST_ServerTokuseiGet(sp,attack)==TOKUSYU_HARIKIRI)&&(wazakind==KIND_BUTSURI)){
		hit=hit*80/100;
	}

	//�������ǂ肠���́A�������̖��������T�O���_�E��
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TIDORIASI)==TRUE)&&
	   (sp->psp[defence].condition2&CONDITION2_KONRAN)){
		hit=hit*50/100;
	}

	eqp=ST_ServerSoubiEqpGet(sp,defence);
	atk=ST_ServerSoubiAtkGet(sp,defence,ATK_CHECK_NORMAL);

	//�A�C�e���Ŗ������_�E���̌��ʂ̂�����̂́A���������_�E��
	if(eqp==SOUBI_MEITYUURITUDOWN){
		hit=hit*(100-atk)/100;
	}

	eqp=ST_ServerSoubiEqpGet(sp,attack);
	atk=ST_ServerSoubiAtkGet(sp,attack,ATK_CHECK_NORMAL);

	//�A�C�e���Ŗ������A�b�v�̌��ʂ̂�����̂́A���������A�b�v
	if(eqp==SOUBI_MEITYUUUP){
		hit=hit*(100+atk)/100;
	}

	//�A�C�e���Ō�U�̂Ƃ��A�������A�b�v�̌��ʂ̂�����̂́A���������A�b�v
	if((eqp==SOUBI_KOUKOUNOTOKIMEITYUUUP)&&(ST_ServerWazaEndCheck(sp,defence)==TRUE)){
		hit=hit*(100+atk)/100;
	}

	//�������ʂň�x�����������A�b�v�́A��������20%�A�b�v
	if(sp->psp[attack].wkw.once_hit_up){
		sp->psp[attack].wkw.once_hit_up=0;
		hit=hit*120/100;
	}

	//���イ��傭���́A��������10/6�{�ɃA�b�v
	if(sp->field_condition&FIELD_CONDITION_JUURYOKU){
		hit=hit*10/6;
	}

	if((gf_rand()%100)+1>hit){
		sp->waza_status_flag|=WAZA_STATUS_FLAG_NOHIT;
	}
	return FALSE;
}

//============================================================================================
/**
 *	�Z���ʃ`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no)
{
	//���ߋZ�n��1�^�[���ڂ́A�Z�𔭓�������̂ŁA�`�F�b�N�̕K�v�Ȃ�
	if(sp->server_status_flag&SERVER_STATUS_FLAG_TAME){
		return FALSE;
	}

	//�܂��邪�A�D�揇�ʓI�ɍŏ��
	//�Z�ɂ܂���t���O�������Ă��āAmamoru_flag�������Ă���΁A�܂���
//	if((sp->otf[defence].mamoru_flag)&&(WT_WazaDataParaGet(waza_no,ID_WTD_flag)&FLAG_MAMORU)){
	if((sp->otf[defence].mamoru_flag)&&(sp->AIWT.wtd[waza_no].flag&FLAG_MAMORU)){
		//�̂낢�Ńm�[�}����������A�܂���𖳎�
		if((waza_no!=WAZANO_NOROI)||(ST_ServerWazaNoroiCheck(sp,waza_no,attack)==TRUE)){
			if((ST_TameWazaCheck(sp,waza_no)==FALSE)||(sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER)){
				ST_ServerKeepOff(bw,sp,attack);
				sp->waza_status_flag|=WAZA_STATUS_FLAG_MAMORU_NOHIT;
				return FALSE;
			}
		}
	}

	//�ʏ�̖������v�Z�ł͂Ȃ������ꍇ�́A���b�N�I���A�m�[�K�[�h�`�F�b�N�����Ȃ�
	if((sp->server_status_flag&SERVER_STATUS_FLAG_OTHER_HIT_CALC)==0){
		//���b�N�I�����ʂ��������Ă���Ƃ��A�����m�[�K�[�h�������Ă���|�P�����ɑ΂��ẮA�K������
		if(((sp->psp[defence].waza_kouka&WAZAKOUKA_LOCKON)&&
		    (sp->psp[defence].wkw.lockon_client_no==attack))||
		    (ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOGAADO)||
		    (ST_ServerTokuseiGet(sp,sp->defence_client)==TOKUSYU_NOOGAADO)){
			//�������v�Z�ł̂͂���𗎂Ƃ�
			sp->waza_status_flag&=WAZA_STATUS_FLAG_NOHIT_OFF;
			return FALSE;
		}
	}
	//����\�͂̂��Ă񂫂́A�`�F�b�N�����Ȃ�
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//�J�̂Ƃ��A���݂Ȃ�͕K������
//		if((sp->field_condition&FIELD_CONDITION_AME_ALL)&&(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)==152)){
		if((sp->field_condition&FIELD_CONDITION_AME_ALL)&&(sp->AIWT.wtd[waza_no].battleeffect==152)){
			sp->waza_status_flag&=WAZA_STATUS_FLAG_NOHIT_OFF;
		}
		//�����̂Ƃ��A�ӂԂ��͕K������
//		if((sp->field_condition&FIELD_CONDITION_ARARE_ALL)&&(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)==260)){
		if((sp->field_condition&FIELD_CONDITION_ARARE_ALL)&&(sp->AIWT.wtd[waza_no].battleeffect==260)){
			sp->waza_status_flag&=WAZA_STATUS_FLAG_NOHIT_OFF;
		}
	}

	//���b�N�I�����ʂœ������Ă���ꍇ�́A��ɂ��Ȃ��`�F�b�N�͂��Ȃ�
	if(((sp->waza_status_flag&WAZA_STATUS_FLAG_LOCK_ON)==0)&&
	//�܂��т��n�́A�`�F�b�N���Ȃ�
		(sp->AIWT.wtd[sp->waza_no_now].attackrange!=RANGE_MAKIBISHI)){
		if(
			//������ƂԁA���Ȃ��ق�A�_�C�r���O�A�V���h�E�_�C�u���́A������Ȃ��i����̋Z�������āj
			(
			((sp->server_status_flag&SERVER_STATUS_FLAG_SORAWOTOBU_HIT)==0)&&
			(sp->psp[defence].waza_kouka&WAZAKOUKA_SORAWOTOBU)
			)||
			(sp->psp[defence].waza_kouka&WAZAKOUKA_SHADOW_DIVE)
			 ||
			(
			((sp->server_status_flag&SERVER_STATUS_FLAG_ANAWOHORU_HIT)==0)&&
			(sp->psp[defence].waza_kouka&WAZAKOUKA_ANAWOHORU)
			)||
			(
			((sp->server_status_flag&SERVER_STATUS_FLAG_DAIBINGU_HIT)==0)&&
			(sp->psp[defence].waza_kouka&WAZAKOUKA_DAIBINGU)
			)){
			sp->waza_status_flag|=WAZA_STATUS_FLAG_KIE_NOHIT;
		}
	}
	return FALSE;
}

//============================================================================================
/**
 *	�Z�ŗL�`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerWazaKoyuuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	client_no;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	//�Ώۂ����Ȃ���΁A�`�F�b�N�Ȃ�
	if(sp->defence_client==NONE_CLIENT_NO){
		return FALSE;
	}

	//�}�W�b�N�R�[�g�`�F�b�N
	if(((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
	    (sp->otf[sp->defence_client].magic_cort_flag)&&
//	    (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_MAGICCORT)){
	    (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_MAGICCORT)){
	    sp->otf[sp->defence_client].magic_cort_flag=0;
		sp->waza_no_mamoru[sp->attack_client]=0;
		sp->waza_no_old[sp->attack_client]=sp->waza_no_temp;
		sp->waza_no_last=sp->waza_no_temp;
		sp->server_status_flag|=SERVER_STATUS_FLAG_NO_WAZANO_SET;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MAGIC_CORT);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		ST_ServerPressurePPDecCheck(sp,sp->defence_client,sp->attack_client);
		return TRUE;
	}
	//�悱�ǂ�`�F�b�N
	for(i=0;i<client_set_max;i++){
		client_no=sp->psp_agi_work[i];
		if(((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		    (sp->otf[client_no].yokodori_flag)&&
//		    (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_flag)&FLAG_YOKODORI)){
		    (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_YOKODORI)){
			sp->client_work=client_no;
		    sp->otf[client_no].yokodori_flag=0;
			if((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0){
				sp->waza_no_mamoru[sp->attack_client]=0;
				sp->waza_no_old[sp->attack_client]=sp->waza_no_temp;
				sp->waza_no_last=sp->waza_no_temp;
				sp->server_status_flag|=SERVER_STATUS_FLAG_NO_WAZANO_SET;
			}
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_YOKODORI);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			ST_ServerPressurePPDecCheck(sp,client_no,sp->attack_client);
			return TRUE;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 *	�Z�V�[�P���X���s
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaSequence(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(SkillIntp(bw,sp)==TRUE){
		sp->skill_seq_no=0;
		sp->server_seq_no=sp->next_server_seq_no;
	}
}

//============================================================================================
/**
 *	�Z�O�����`�F�b�N�V�[�P���X
 *
 * @param
 */
//============================================================================================
enum{
	SEQ_SENSEI_CHECK=0,
	SEQ_STATUS_CHECK,
	SEQ_BADGE_CHECK,
	SEQ_PP_CHECK,
	SEQ_DEFENCE_CHECK,
	SEQ_WAZAKOYUU_CHECK,
	SEQ_DEFENCE_CHANGE_CHECK
};

//============================================================================================
/**
 *	�Z�O����
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaBefore(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	switch(sp->wb_seq_no){
	case SEQ_SENSEI_CHECK:
		ServerSenseiCheck(bw,sp);			///<�搧�n�̃A�C�e�����ʂ̃`�F�b�N
		sp->wb_seq_no++;
		return;
		break;
	case SEQ_STATUS_CHECK:
		if((sp->waza_out_check_on_off&STATUS_CHECK_OFF)==0){
			if(ServerStatusCheck(bw,sp)==TRUE){			///<��Ԉُ�`�F�b�N
				return;
			}
		}
		sp->wb_seq_no++;
	case SEQ_BADGE_CHECK:
		{
			int	ret;
			int	seq_no;

			if((sp->waza_out_check_on_off&BADGE_CHECK_OFF)==0){
				ret=ServerBadgeCheck(bw,sp,&seq_no);
				if(ret){
					switch(ret){			///<�o�b�W�`�F�b�N
					case 1:		//�������Ƃ𕷂����ɋZ�������Ȃ��n
//						sp->next_server_seq_no=SERVER_WAZA_END_NO;
						sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
						break;
					case 2:		//�������Ƃ𕷂����ɕʂ̋Z���o��
						sp->next_server_seq_no=sp->server_seq_no;
						break;
					case 3:		//���߂𖳎����Ď������U��
						sp->next_server_seq_no=SERVER_KIZETSU_EFFECT_NO;
						break;
					}
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
					return;
				}
			}
		}
		sp->wb_seq_no++;
	case SEQ_PP_CHECK:
		if((sp->waza_out_check_on_off&PP_CHECK_OFF)==0){
			if(ServerPPCheck(bw,sp)==TRUE){				///<PP�`�F�b�N
				return;
			}
		}
		sp->wb_seq_no++;
	case SEQ_DEFENCE_CHECK:
		if(ServerDefenceCheck(bw,sp)==TRUE){			///<�U���Ώۃ`�F�b�N
			return;
		}
		sp->wb_seq_no++;
	case SEQ_WAZAKOYUU_CHECK:
		if((sp->waza_out_check_on_off&WAZAKOYUU_CHECK_OFF)==0){
			if(ServerWazaKoyuuCheck(bw,sp)==TRUE){		///<�Z�ŗL�`�F�b�N
				return;
			}
		}
		sp->wb_seq_no++;
	case SEQ_DEFENCE_CHANGE_CHECK:
		ST_ServerDefenceClientTokuseiCheck(bw,sp,sp->attack_client,sp->waza_no_now);
		sp->wb_seq_no=0;
	}
	//�Z���o���Ȃ��n�̃t���O�������Ă���ꍇ�́A�͂��ꃁ�b�Z�[�W�V�[�P���X��
	if(sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT){
		sp->server_seq_no=SERVER_WAZA_HAZURE_MESSAGE_NO;
	}
	else{
		sp->server_status_flag2|=SERVER_STATUS_FLAG2_WAZA_OUT;
		ST_ServerSequenceLoad(sp,ARC_WAZA_SEQ,sp->waza_no_now);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_WAZA_OUT_CHECK_NO;
		//�Ƃ��Ă����J�E���g���v�Z
		ST_ServerTotteokiCountCalc(bw,sp);
	}
	//���g���m�[���`�F�b�N
	ST_ServerMetronomeBeforeCheck(bw,sp);
}

//============================================================================================
/**
 *	�Z�����`�F�b�N�̃V�[�P���X�i���o�[
 */
//============================================================================================
enum{
	SEQ_DEFENCE_CHECK2=0,
	SEQ_DEFENCE_CHANGE_ACT,
	SEQ_HIT_CHECK,
	SEQ_WAZAKOUKA_CHECK,
	SEQ_TYPE_CHECK,
	SEQ_TOKUSEI_CHECK,
	SEQ_CHECK_END
};

//============================================================================================
/**
 *	�Z�����`�F�b�N
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaOutCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{

	switch(sp->woc_seq_no){
	//�p���t���n�[�u�ŁA���߃^�[�����X���[����Ă����܂ł��Ă��܂��̂ŁA�ēxNONE_CLIENT_NO�`�F�b�N������
	case SEQ_DEFENCE_CHECK2:
		sp->woc_seq_no++;
		if(ServerDefenceCheck(bw,sp)==TRUE){			///<�U���Ώۃ`�F�b�N
			return;
		}
	//DefenceClient��ύX��������̃`�F�b�N
	case SEQ_DEFENCE_CHANGE_ACT:
		sp->woc_seq_no++;
		if(ST_ServerDefenceClientTokuseiAct(bw,sp)==TRUE){
			return;
		}
	case SEQ_HIT_CHECK:
		if(((sp->waza_out_check_on_off&HIT_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerHitCheck(bw,sp,sp->attack_client,sp->defence_client,sp->waza_no_now)==TRUE){		///<�������`�F�b�N
				return;
			}
		}
		sp->woc_seq_no++;
	case SEQ_WAZAKOUKA_CHECK:
		if(((sp->waza_out_check_on_off&WAZAKOUKA_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerWazaKoukaCheck(bw,sp,sp->attack_client,sp->defence_client,sp->waza_no_now)==TRUE){		///<�Z���ʃ`�F�b�N
				return;
			}
		}
		sp->woc_seq_no++;
	case SEQ_TYPE_CHECK:
		if(((sp->waza_out_check_on_off&TYPE_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerTypeCheck(bw,sp)==TRUE){			///<TYPE�`�F�b�N
				return;
			}
		}
		sp->woc_seq_no++;
	case SEQ_TOKUSEI_CHECK:
		if(((sp->waza_out_check_on_off&TOKUSEI_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerTokuseiCheck(bw,sp)==TRUE){		///<�����`�F�b�N
				return;
			}
		}
		sp->woc_seq_no++;
	case SEQ_CHECK_END:
		sp->woc_seq_no=0;
		break;
	}
	sp->server_seq_no=SERVER_ADD_STATUS_DIRECT_CHECK_NO;
}

//============================================================================================
/**
 *	�ǉ����ʃ`�F�b�N�i���ڒǉ��̂݁j
 *
 * @param
 */
//============================================================================================
static	void	ServerAddStatusDirectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;

	if(ST_ServerAddStatusDirectCheck(bw,sp,&seq_no)==TRUE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_WAZA_HAZURE_MESSAGE_NO;
		return;
	}
	else{
		sp->server_seq_no=SERVER_WAZA_HAZURE_MESSAGE_NO;
	}
}

//============================================================================================
/**
 *	������Ȃ������n���b�Z�[�W�\��
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaHazureMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//�Z�̋N���Ɏ��s���Ă���ƁA���̃t���O�������Ă���̂ŁA�ȍ~�̃`�F�b�N�͂��Ȃ�
	if(sp->waza_status_flag&WAZA_STATUS_FLAG_SIPPAI){
		sp->server_seq_no=SERVER_LOOP_CHECK_NO;
	}
	//PP���Ȃ���
	else if(sp->waza_status_flag&WAZA_STATUS_FLAG_PP_NONE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_PP_NONE);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//		sp->next_server_seq_no=SERVER_WAZA_END_NO;
		sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
	}
	//�A���U���n�ł̂͂���́A�A������߂�
	else if((sp->loop_flag)&&(sp->waza_status_flag&WAZA_STATUS_FLAG_NOHIT)){
		sp->waza_status_flag&=WAZA_STATUS_FLAG_NOHIT_OFF;
		sp->waza_status_flag|=WAZA_STATUS_FLAG_RENZOKU_NOHIT;
		sp->server_seq_no=SERVER_WAZA_OUT_AFTER_MESSAGE_NO;
	}
	else if(sp->waza_status_flag&WAZA_STATUS_FLAG_HAZURE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_NO_HIT);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_KIZETSU_EFFECT_NO;
	}
	else{
		sp->server_seq_no=SERVER_WAZA_OUT_NO;
	}
}

//============================================================================================
/**
 *	�Z�㏈��
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaOut(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_OUT);
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	sp->next_server_seq_no=SERVER_HP_CALC_NO;
}

//============================================================================================
/**
 *	HP�v�Z����
 *
 * @param
 */
//============================================================================================
static	void	ServerHPCalc(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	eqp;
	int	atk;

	//�ꌂ�K�E�̎��́AHPMAX���_���[�W�ɑ��
	if(sp->waza_status_flag&WAZA_STATUS_FLAG_ICHIGEKI){
		sp->damage=sp->psp[sp->defence_client].hpmax*-1;
	}
	if(sp->damage){
		eqp=ST_ServerSoubiEqpGet(sp,sp->defence_client);
		atk=ST_ServerSoubiAtkGet(sp,sp->defence_client,ATK_CHECK_NORMAL);

		//�o�O�ł͂Ȃ����ǁA���邩�Ȃ����𔻒f���邽��
		GF_ASSERT_MSG(sp->damage<0,"�_���[�W���{�ł�\n");

		//�p�[�e�B�A�^�b�N�������񐔂��J�E���g�A�b�v
		if(BattleWorkMineEnemyCheck(bw,sp->attack_client)==BattleWorkMineEnemyCheck(bw,sp->defence_client)){
			SCIO_IncRecord(bw,sp->attack_client,CLIENT_BOOT_TYPE_MINE,RECID_TEMOTI_MAKIZOE);
		}

		//�Ō�ɓ��Ă�ClientNo���p�o�b�t�@�Ɋi�[
		sp->client_no_hit[sp->defence_client]=sp->attack_client;

		//�݂����`�F�b�N
		if((sp->psp[sp->defence_client].condition2&CONDITION2_MIGAWARI)&&(sp->damage<0)){
			if((sp->psp[sp->defence_client].wkw.migawari_hp+sp->damage)<=0){
				sp->ostf[sp->attack_client].kaigara_damage+=(sp->psp[sp->defence_client].wkw.migawari_hp*-1);
				sp->psp[sp->defence_client].condition2&=CONDITION2_MIGAWARI_OFF;
				sp->hit_damage=sp->psp[sp->defence_client].wkw.migawari_hp*-1;
				sp->psp[sp->defence_client].wkw.migawari_hp=0;
			}
			else{
				sp->ostf[sp->attack_client].kaigara_damage+=sp->damage;
				sp->psp[sp->defence_client].wkw.migawari_hp+=sp->damage;
				sp->hit_damage=sp->damage;
			}
			sp->ostf[sp->defence_client].status_flag|=OSTF_STATUS_FLAG_MIGAWARI_HIT;
			sp->client_work=sp->defence_client;
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MIGAWARI_HIT);
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_WAZA_OUT_AFTER_MESSAGE_NO;
		}
		else{
			//�݂˂����`�F�b�N
//			if(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_battleeffect)==101){
			if(sp->AIWT.wtd[sp->waza_no_now].battleeffect==101){
				//�C�₵�Ă��܂����́A�P�c���悤�ɂ���
				if((sp->psp[sp->defence_client].hp+sp->damage)<=0){
					sp->damage=(sp->psp[sp->defence_client].hp-1)*-1;
				}
			}
			//�Z�̂��炦�邪�������Ă��鎞�́A�A�C�e���̃`�F�b�N�����Ȃ�
			if(sp->otf[sp->defence_client].koraeru_flag==0){
				//�A�C�e�����炦��`�F�b�N
#ifdef PM_DEBUG
				if((eqp==SOUBI_HPITIDETAERU)&&(((gf_rand()%100)<atk)||(sp->dbp.debug_flag&DEBUG_FLAG_SOUBI))){
#else
				if((eqp==SOUBI_HPITIDETAERU)&&((gf_rand()%100)<atk)){
#endif
					sp->ostf[sp->defence_client].item_koraeru_flag=1;
				}
				if((eqp==SOUBI_HPMAXDEITIGEKISISINAI)&&(sp->psp[sp->defence_client].hp==sp->psp[sp->defence_client].hpmax)){
					sp->ostf[sp->defence_client].item_koraeru_flag=1;
				}
			}
			//���炦��`�F�b�N
			if((sp->otf[sp->defence_client].koraeru_flag)||(sp->ostf[sp->defence_client].item_koraeru_flag)){
				//�C�₵�Ă��܂����́A�P�c���悤�ɂ���
				if((sp->psp[sp->defence_client].hp+sp->damage)<=0){
					sp->damage=(sp->psp[sp->defence_client].hp-1)*-1;
					if(sp->otf[sp->defence_client].koraeru_flag){
						sp->waza_status_flag|=WAZA_STATUS_FLAG_KORAETA;
					}
					else{
						sp->waza_status_flag|=WAZA_STATUS_FLAG_ITEM_KORAETA;
					}
				}
			}
			//���܂�p�̃_���[�W�X�g�b�N���[�N�ɑ�������
			sp->store_damage[sp->defence_client]+=sp->damage;
	
			//�U�����󂯂��J�E���^���J�E���g�A�b�v
			if(sp->psp[sp->defence_client].hit_count<255){
				sp->psp[sp->defence_client].hit_count++;
			}
//			if(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_kind)==KIND_BUTSURI){
			if(sp->AIWT.wtd[sp->waza_no_now].kind==KIND_BUTSURI){
				sp->otf[sp->defence_client].butsuri_otf_damage[sp->attack_client]=sp->damage;
				sp->otf[sp->defence_client].butsuri_otf_client=sp->attack_client;
				sp->otf[sp->defence_client].butsuri_otf_client_bit|=No2Bit(sp->attack_client);
				sp->ostf[sp->defence_client].butsuri_ostf_damage=sp->damage;
				sp->ostf[sp->defence_client].butsuri_ostf_client=sp->attack_client;
			}
//			else if(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_kind)==KIND_TOKUSYU){
			else if(sp->AIWT.wtd[sp->waza_no_now].kind==KIND_TOKUSYU){
				sp->otf[sp->defence_client].tokusyu_otf_damage[sp->attack_client]=sp->damage;
				sp->otf[sp->defence_client].tokusyu_otf_client=sp->attack_client;
				sp->otf[sp->defence_client].tokusyu_otf_client_bit|=No2Bit(sp->attack_client);
				sp->ostf[sp->defence_client].tokusyu_ostf_damage=sp->damage;
				sp->ostf[sp->defence_client].tokusyu_ostf_client=sp->attack_client;
			}
			//��������_���[�W�͎��ۂɂg�o�����炵�����ۗʂŌv�Z
			if((sp->psp[sp->defence_client].hp+sp->damage)<=0){
				sp->ostf[sp->attack_client].kaigara_damage+=(sp->psp[sp->defence_client].hp*-1);
			}
			else{
				sp->ostf[sp->attack_client].kaigara_damage+=sp->damage;
			}
			sp->otf[sp->defence_client].last_otf_damage=sp->damage;
			sp->otf[sp->defence_client].last_otf_client=sp->attack_client;
			///<HP�v�Z����
			sp->client_work=sp->defence_client;
			sp->hp_calc_work=sp->damage;
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HP_CALC);
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_WAZA_OUT_AFTER_MESSAGE_NO;
			//�Z�������������Ƃ������t���O�𗧂Ă�
			sp->server_status_flag|=SERVER_STATUS_FLAG_WAZA_HIT;
		}
	}
	else{
		sp->server_seq_no=SERVER_WAZA_OUT_AFTER_MESSAGE_NO;
	}
}

//============================================================================================
/**
 *	�Z���ł���̂��낢��ȃ��b�Z�[�W�\��
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaOutAfterMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	switch(sp->swoam_type){
	case SWOAM_NORMAL:
		switch(sp->swoam_seq_no){
		case 0:
			sp->swoam_seq_no++;
			if(ServerCriticalMessage(bw,sp)==TRUE){
				return;
			}
		case 1:
			sp->swoam_seq_no++;
			if(ServerWazaStatusMessage(bw,sp)==TRUE){
				return;
			}
		case 2:
			{
				int	seq_no;

				sp->swoam_seq_no++;
				if((ST_ServerAddStatusCheck(bw,sp,&seq_no)==TRUE)&&((sp->waza_status_flag&WAZA_STATUS_FLAG_HAZURE)==0)){
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					return;
				}
			}
		case 3:
			sp->swoam_seq_no++;
			if(ServerIkariCheck(bw,sp)==TRUE){
				return;
			}
		case 4:
			{
				int	seq_no;
	
				sp->swoam_seq_no++;
				if(ST_ServerWazaHitTokuseiCheck(bw,sp,&seq_no)==TRUE){
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					return;
				}
			}
		case 5:
			sp->swoam_seq_no++;
			if(ServerHirumaseruCheck(bw,sp)==TRUE){
				return;
			}
		default:
			break;
		}
		break;
	case SWOAM_LOOP:
		switch(sp->swoam_seq_no){
		case 0:
			sp->swoam_seq_no++;
			if(ServerCriticalMessage(bw,sp)==TRUE){
				return;
			}
		case 1:
			{
				int	seq_no;

				sp->swoam_seq_no++;
				if((ST_ServerAddStatusCheck(bw,sp,&seq_no)==TRUE)&&((sp->waza_status_flag&WAZA_STATUS_FLAG_HAZURE)==0)){
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					return;
				}
			}
		case 2:
			sp->swoam_seq_no++;
			if(ServerIkariCheck(bw,sp)==TRUE){
				return;
			}
		case 3:
			{
				int	seq_no;
	
				sp->swoam_seq_no++;
				if(ST_ServerWazaHitTokuseiCheck(bw,sp,&seq_no)==TRUE){
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					return;
				}
			}
		case 4:
			sp->swoam_seq_no++;
			if(ServerWazaStatusMessage(bw,sp)==TRUE){
				return;
			}
		case 5:
			sp->swoam_seq_no++;
			if(ServerHirumaseruCheck(bw,sp)==TRUE){
				return;
			}
		default:
			break;
		}
		break;
	}
	sp->swoam_seq_no=0;
	sp->server_seq_no=SERVER_WAZA_OUT_AFTER_KOUKA_NO;
}

//============================================================================================
/**
 *	�ǉ����ʃ`�F�b�N�i���ڒǉ��ȊO�j�i��̊֐��̒��ɋz���j
 *
 * @param
 */
//============================================================================================
static	void	ServerAddStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
#if 0
	int	seq_no;

	if((ST_ServerAddStatusCheck(bw,sp,&seq_no)==TRUE)&&((sp->waza_status_flag&WAZA_STATUS_FLAG_HAZURE)==0)){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_WAZA_OUT_AFTER_KOUKA_NO;
		return;
	}
	else{
		sp->server_seq_no=SERVER_WAZA_OUT_AFTER_KOUKA_NO;
	}
#endif
}

//============================================================================================
/**
 *	�Z���ł���̂��낢��Ȍ��ʃ`�F�b�N
 *
 * @param
 */
//============================================================================================
enum{
//	SWOAK_SEQ_WAZA_HIT_TOKUSEI=0,
	SWOAK_SEQ_VANISH_ON_OFF=0,
	SWOAK_SEQ_SINKURO_CHECK,
	SWOAK_SEQ_POKE_APPEAR_CHECK,
//	SWOAK_SEQ_TOKUSEI_RECOVER_ATTACK,
//	SWOAK_SEQ_TOKUSEI_RECOVER_DEFENCE,
	SWOAK_SEQ_SOUBI_ITEM_ATTACK,
	SWOAK_SEQ_SOUBI_ITEM_DEFENCE,
	SWOAK_SEQ_WAZA_HIT_SOUBI_ITEM,
	SWOAK_SEQ_MELT_ICE,
	SWOAK_SEQ_SOUBI_ITEM_CONDITION_BAD
};

static	void	ServerWazaOutAfterKouka(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	switch(sp->swoak_seq_no){
#if 0
	case SWOAK_SEQ_WAZA_HIT_TOKUSEI:
		{
			int	seq_no;

			sp->swoak_seq_no++;
			if(ST_ServerWazaHitTokuseiCheck(bw,sp,&seq_no)==TRUE){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				return;
			}
		}
#endif
	case SWOAK_SEQ_VANISH_ON_OFF:
		{
			int	ret=0;
			while(sp->swoak_work<BattleWorkClientSetMaxGet(bw)){
				//wazakouka�t���O(��\����\���Ɂj
				if(((sp->psp[sp->swoak_work].waza_kouka&WAZAKOUKA_KIE)==0)&&
				    (sp->psp[sp->swoak_work].waza_kouka_temp&WAZAKOUKA_KIE)){
				    sp->psp[sp->swoak_work].waza_kouka_temp&=WAZAKOUKA_KIE_OFF;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_VANISH_OFF);
					sp->client_work=sp->swoak_work;
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
				sp->swoak_work++;
				if(ret){
					return;
				}
			}
		}
		sp->swoak_seq_no++;
		sp->swoak_work=0;
	case SWOAK_SEQ_SINKURO_CHECK:
		sp->swoak_seq_no++;
		if(ST_ServerSinkuroCheck(bw,sp,sp->server_seq_no)==TRUE){
			return;
		}
	//�o�g���^�b�`��Ƃ�ڂ�����œ��ꂩ�������������p
	case SWOAK_SEQ_POKE_APPEAR_CHECK:
		{
			int	seq_no;

			seq_no=ST_ServerPokeAppearCheck(bw,sp);

			if(seq_no){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				return;
			}
		}
		sp->swoak_seq_no++;
#if 0
	case SWOAK_SEQ_TOKUSEI_RECOVER_ATTACK:
		sp->swoak_seq_no++;
		if(ST_ServerTokuseiStatusRecoverCheck(bw,sp,sp->attack_client,0)==TRUE){
			return;
		}
	case SWOAK_SEQ_TOKUSEI_RECOVER_DEFENCE:
		sp->swoak_seq_no++;
		if(sp->defence_client!=NONE_CLIENT_NO){
			if(ST_ServerTokuseiStatusRecoverCheck(bw,sp,sp->defence_client,0)==TRUE){
				return;
			}
		}
#endif
	case SWOAK_SEQ_SOUBI_ITEM_ATTACK:
		sp->swoak_seq_no++;
		if(ST_ServerSoubiItemCheck(bw,sp,sp->attack_client)==TRUE){
			return;
		}
	case SWOAK_SEQ_SOUBI_ITEM_DEFENCE:
		sp->swoak_seq_no++;
		if(sp->defence_client!=NONE_CLIENT_NO){
			if(ST_ServerSoubiItemCheck(bw,sp,sp->defence_client)==TRUE){
				return;
			}
		}
	case SWOAK_SEQ_WAZA_HIT_SOUBI_ITEM:
		{
			int	seq_no;

			sp->swoak_seq_no++;
			if(ST_ServerWazaHitSoubiItemCheck(bw,sp,&seq_no)==TRUE){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				return;
			}
		}
	case SWOAK_SEQ_MELT_ICE:
		{
			int	wazatype;
			
			//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
			if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOMARUSUKIN){
				wazatype=NORMAL_TYPE;
			}
			else if(sp->waza_type){
				wazatype=sp->waza_type;
			}
			else{
				wazatype=sp->AIWT.wtd[sp->waza_no_now].wazatype;
			}

			sp->swoak_seq_no++;
			if(sp->defence_client!=NONE_CLIENT_NO){
				if((sp->psp[sp->defence_client].condition&CONDITION_KOORI)&&
				  ((sp->waza_status_flag&WAZA_STATUS_FLAG_RENZOKU_NOHIT)==0)&&
				   (sp->defence_client!=sp->attack_client)&&
				  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||(sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
				   (sp->psp[sp->defence_client].hp)&&
				   (wazatype==FIRE_TYPE)){	
					sp->client_work=sp->defence_client;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MELT);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					return;
				}
			}
		}
	case SWOAK_SEQ_SOUBI_ITEM_CONDITION_BAD:
		{
			int client_no;
			int	ret=0;
			int	seq_no;

			while(sp->swoak_work<BattleWorkClientSetMaxGet(bw)){
				client_no=sp->psp_agi_work[sp->swoak_work];
				if(sp->no_reshuffle_client&No2Bit(client_no)){
					sp->swoak_work++;
					continue;
				}
				sp->swoak_work++;
				if(ST_ServerSoubiItemConditionBadCheck(bw,sp,client_no,&seq_no)==TRUE){
					sp->client_work=client_no;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
					break;
				}
			}
			if(ret==0){
				sp->swoak_seq_no++;
				sp->swoak_work=0;
			}
		}
		break;
	default:
		break;
	}
	sp->swoak_seq_no=0;
	sp->swoak_work=0;
//	sp->server_seq_no=SERVER_SINKURO_CHECK_NO;
	sp->server_seq_no=SERVER_RENZOKU_CHECK_NO;
}

//============================================================================================
/**
 *	�V���N���`�F�b�N�i�ꏊ�ړ��j
 *
 * @param
 */
//============================================================================================
static	void	ServerSinkuroCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
#if 0
	if(ST_ServerSinkuroCheck(bw,sp,SERVER_RENZOKU_CHECK_NO)==TRUE){
		return;
	}
	else{
		sp->server_seq_no=SERVER_RENZOKU_CHECK_NO;
	}
#endif
}

//============================================================================================
/**
 *	�A���U���̃`�F�b�N
 *
 * @param
 */
//============================================================================================
static	void	ServerRenzokuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->renzoku_count_temp){
		//�C�₵���|�P�����������ꍇ�A�����Ă��܂����ꍇ�A�������`�F�b�N�ŊO�ꂽ�ꍇ�́A�`�F�b�N���I��
		if((sp->kizetsu_client==NONE_CLIENT_NO)&&
		  ((sp->psp[sp->attack_client].condition&CONDITION_NEMURI)==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_RENZOKU_NOHIT)==0)){
			if(--sp->renzoku_count){
				sp->loop_flag=1;
				ST_ServerLoopInit(bw,sp);
				//�Z�G�t�F�N�g���ēx�o���悤�ɂ���
				sp->server_status_flag&=SERVER_STATUS_FLAG_NO_WAZA_EFFECT_OFF;
				//���[�v���鎞�Ƀ`�F�b�N����WazaOutCheck���r�b�g�Ŏw��
				sp->waza_out_check_on_off=sp->loop_hit_check;
				ST_ServerSequenceLoad(sp,ARC_WAZA_SEQ,sp->waza_no_now);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				sp->next_server_seq_no=SERVER_WAZA_OUT_CHECK_NO;
			}
			else{
				sp->msg_work=sp->renzoku_count_temp;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_LOOP_HIT);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				sp->next_server_seq_no=SERVER_KIZETSU_EFFECT_NO;
			}
		}
		else{
			if((sp->kizetsu_client!=NONE_CLIENT_NO)||
			   (sp->psp[sp->attack_client].condition&CONDITION_NEMURI)){
				sp->msg_work=sp->renzoku_count_temp-sp->renzoku_count+1;
			}
			else{
				sp->msg_work=sp->renzoku_count_temp-sp->renzoku_count;
			}
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_LOOP_HIT);
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_KIZETSU_EFFECT_NO;
		}
		SCIO_BlankMessage(bw);
	}
	else{
		sp->server_seq_no=SERVER_KIZETSU_EFFECT_NO;
	}
}

//============================================================================================
/**
 *	�C��G�t�F�N�g
 *
 * @param
 */
//============================================================================================
static	void	ServerKizetsuEffect(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->server_status_flag&SERVER_STATUS_FLAG_KIZETSU){
		ServerKizetsuCheck(sp,SERVER_KIZETSU_EFFECT_NO,SERVER_KIZETSU_EFFECT_NO,SKC_MICHIDURE_ON);
	}
	else{
		sp->server_seq_no=SERVER_LOOP_CHECK_NO;
	}
}

//============================================================================================
/**
 *	�����̓�����Z�̃`�F�b�N
 *
 * @param
 */
//============================================================================================
static	void	ServerLoopCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//�}�W�b�N�R�[�g�ɂ���āAAttack��Defence������ւ���Ă����猳�ɖ߂�
	if(sp->server_status_flag2&SERVER_STATUS_FLAG2_MAGIC_CORT_A_D){
		sp->server_status_flag2&=SERVER_STATUS_FLAG2_MAGIC_CORT_A_D_OFF;
		sp->defence_client=sp->attack_client;
		sp->attack_client=sp->magic_cort_client;
	}

#if B1370_060815_FIX
	//�I�E���Ԃ����[�N�ւ̊i�[�i�����̓�����Z�p�̊i�[�Ȃ̂ŁA�ړ��͌��ցj
	ServerOumugaeshiCheck(bw,sp);
#endif B1370_060815_FIX

//	if((WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_attackrange)==RANGE_DOUBLE)&&
	if((sp->AIWT.wtd[sp->waza_no_now].attackrange==RANGE_DOUBLE)&&
		   ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_DOUBLE_CHECK)==0)&&
			(sp->client_loop<BattleWorkClientSetMaxGet(bw))){
		//���[�v���鎞�Ƀ`�F�b�N����WazaOutCheck���r�b�g�Ŏw��
		sp->waza_out_check_on_off=DOUBLE_HIT_OFF;
		{
			int	client_no;
			int	client_set_max=BattleWorkClientSetMaxGet(bw);
			CLIENT_PARAM *cp=BattleWorkClientParamGet(bw,sp->attack_client);
			u8	flag=CT_CPClientTypeGet(cp);

			do{
				client_no=sp->psp_agi_work[sp->client_loop++];
				if(((sp->no_reshuffle_client&No2Bit(client_no))==0)&&(sp->psp[client_no].hp)){
					cp=BattleWorkClientParamGet(bw,client_no);
					if( ((flag&CLIENT_ENEMY_FLAG)&&((CT_CPClientTypeGet(cp)&CLIENT_ENEMY_FLAG)==0))||
						((flag&CLIENT_ENEMY_FLAG)==0)&&(CT_CPClientTypeGet(cp)&CLIENT_ENEMY_FLAG)){
						ST_ServerLoopInit(bw,sp);
						sp->defence_client=client_no;
						sp->server_seq_no=SERVER_WAZA_BEFORE_NO;
						break;
					}
				}
			}while(sp->client_loop<BattleWorkClientSetMaxGet(bw));
		}
		SCIO_BlankMessage(bw);
	}
//	else if((WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_attackrange)==RANGE_TRIPLE)&&
	else if((sp->AIWT.wtd[sp->waza_no_now].attackrange==RANGE_TRIPLE)&&
		   ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_DOUBLE_CHECK)==0)&&
			(sp->client_loop<BattleWorkClientSetMaxGet(bw))){
		//���[�v���鎞�Ƀ`�F�b�N����WazaOutCheck���r�b�g�Ŏw��
		sp->waza_out_check_on_off=DOUBLE_HIT_OFF;
		{
			int	client_no;
			int	client_set_max=BattleWorkClientSetMaxGet(bw);

			do{
				client_no=sp->psp_agi_work[sp->client_loop++];
				if(((sp->no_reshuffle_client&No2Bit(client_no))==0)&&(sp->psp[client_no].hp)){
					if(client_no!=sp->attack_client){
						ST_ServerLoopInit(bw,sp);
						sp->defence_client=client_no;
						sp->server_seq_no=SERVER_WAZA_BEFORE_NO;
						break;
					}
				}
			}while(sp->client_loop<BattleWorkClientSetMaxGet(bw));
		}
		SCIO_BlankMessage(bw);
	}
	else{
		sp->server_seq_no=SERVER_JIBAKU_EFFECT_NO;
	}
}

//============================================================================================
/**
 *	���΂��ɂ��C��G�t�F�N�g
 *
 * @param
 */
//============================================================================================
static	void	ServerJibakuEffect(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->server_status_flag&SERVER_STATUS_FLAG_JIBAKU_MASK){
		sp->kizetsu_client=Bit2No((sp->server_status_flag&SERVER_STATUS_FLAG_JIBAKU_MASK)>>SERVER_STATUS_FLAG_JIBAKU_SHIFT);
		sp->server_status_flag&=SERVER_STATUS_FLAG_JIBAKU_MASK_OFF;
//		sp->server_status_flag2|=No2Bit(sp->kizetsu_client)<<SERVER_STATUS_FLAG2_GET_EXP_SHIFT;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_JIBAKU_KIZETSU);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_WAZA_HIT_AFTER_CHECK_NO;
	}
	else{
		sp->server_seq_no=SERVER_WAZA_HIT_AFTER_CHECK_NO;
	}
}

//============================================================================================
/**
 *	�Z���q�b�g������̃`�F�b�N
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaHitAfterCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(ServerWazaHitAfterCheckAct(bw,sp)==TRUE){
		return;
	}
//	sp->server_seq_no=SERVER_GET_EXP_EFFECT_NO;
	sp->server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
}

//============================================================================================
/**
 *	�o���l�擾�G�t�F�N�g
 *
 * @param
 */
//============================================================================================
static	void	ServerGetExpEffect(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
#if 0
	if(sp->server_status_flag2&SERVER_STATUS_FLAG2_GET_EXP){
		ServerGetExpCheck(sp,SERVER_GET_EXP_EFFECT_NO,SERVER_WAZA_NO_BUFFER_SET_NO);
	}
	else{
		sp->server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
	}
#endif
}

//============================================================================================
/**
 *	�Z�i���o�[���o�b�t�@�Ɋi�[
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaNoBufferSet(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
#if B1370_060815_FIX
	u8	eqp_a;
#else //B1370_060815_FIX
	int	wazatype;
	u8	eqp_a;
	u8	eqp_d;
#endif //B1370_060815_FIX

#if B1370_060815_FIX == 0
	//�����m�[�}���X�L���́A�^�C�v���m�[�}����
	if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(sp->waza_type){
		wazatype=sp->waza_type;
	}
	else{
		wazatype=sp->AIWT.wtd[sp->waza_no_now].wazatype;
	}
#endif //B1370_060815_FIX

	//Attack�̑��
	eqp_a=ST_ServerSoubiEqpGet(sp,sp->attack_client);
	if((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)||
	   (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
		//�����A�C�e���u�������͂��܂��v�́A�Z�̔����Ń��[�N�֑��
		if((eqp_a==SOUBI_ONAZIWAZAONLY)||
		   (eqp_a==SOUBI_ONAZIWAZAONLYSUBAYASAUP)||
		   (eqp_a==SOUBI_ONAZIAWZAONLYTOKUSYUUP)){
			if((sp->waza_no_temp==WAZANO_WARUAGAKI)||
			  ((sp->waza_no_temp==WAZANO_BATONTATTI)&&(sp->server_status_flag2&SERVER_STATUS_FLAG2_WAZA_OUT))){
				;
			}
			else{
				sp->psp[sp->attack_client].wkw.kodawari_wazano=sp->waza_no_temp;
			}
		}
		else{
			sp->psp[sp->attack_client].wkw.kodawari_wazano=0;
		}
	}

	//1�^�[���O�ɌJ��o���Ă����Z�Ƃ��Ċi�[�i�t���O�������Ă��鎞�͊i�[���Ȃ�
	if((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0){
		if(sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG){
			sp->waza_no_mamoru[sp->attack_client]=sp->waza_no_now;
			sp->waza_no_last=sp->waza_no_temp;
		}
		else{
			sp->waza_no_mamoru[sp->attack_client]=0;
			sp->waza_no_last=0;
		}
		if(sp->server_status_flag2&SERVER_STATUS_FLAG2_WAZA_OUT){
			sp->waza_no_old[sp->attack_client]=sp->waza_no_temp;
		}
		else{
			sp->waza_no_old[sp->attack_client]=0;
		}
	}

	if(sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG){
		sp->waza_no_sketch[sp->attack_client]=sp->waza_no_temp;
	}

#if B1370_060815_FIX == 0
	if(sp->defence_client!=NONE_CLIENT_NO){
		//Defence�̑��
		eqp_d=ST_ServerSoubiEqpGet(sp,sp->defence_client);
		if((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)||
		   (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
			//�����A�C�e���u�������͂��܂��v�́A�Z�̔����Ń��[�N�֑��
			if((eqp_d!=SOUBI_ONAZIWAZAONLY)&&
			   (eqp_d!=SOUBI_ONAZIWAZAONLYSUBAYASAUP)&&
			   (eqp_d!=SOUBI_ONAZIAWZAONLYTOKUSYUUP)){
				sp->psp[sp->defence_client].wkw.kodawari_wazano=0;
			}
		}

		//1�^�[���O�ɌJ��o���Ă����Z�Ƃ��Ċi�[�i�t���O�������Ă��鎞�͊i�[���Ȃ�
		if((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0){
			if(sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG){
				sp->waza_no_hit[sp->defence_client]=sp->waza_no_now;
				sp->waza_no_hit_client[sp->defence_client]=sp->attack_client;
				sp->waza_no_hit_type[sp->defence_client]=wazatype;
				sp->waza_no_last=sp->waza_no_temp;
			}
			else{
				sp->waza_no_hit[sp->defence_client]=0;
				sp->waza_no_hit_client[sp->defence_client]=NONE_CLIENT_NO;
				sp->waza_no_hit_type[sp->defence_client]=0;
				sp->waza_no_last=0;
			}
			if((sp->server_status_flag2&SERVER_STATUS_FLAG2_WAZA_OUT)&&
			  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
				//�e�N�X�`���[�Q���[�N�́A�i�[���郌���W�����肷��
				switch(sp->AIWT.wtd[sp->waza_no_now].attackrange){
				case RANGE_MINE:		//�����I��
				case RANGE_MINE_DOUBLE:	//�����Q�̑I��
				case RANGE_FIELD:		//��ɂ�����
				case RANGE_MAKIBISHI:	//�܂��т���p
				case RANGE_TEDASUKE:	//�Ă�������p
				case RANGE_TUBOWOTUKU:	//�ڂ�����p
					sp->waza_no_texture2[sp->defence_client]=0;
					sp->waza_no_texture2_client[sp->defence_client]=NONE_CLIENT_NO;
					sp->waza_no_texture2_type[sp->defence_client]=0;
					break;
				default:
					sp->waza_no_texture2[sp->defence_client]=sp->waza_no_now;
					sp->waza_no_texture2_client[sp->defence_client]=sp->attack_client;
					sp->waza_no_texture2_type[sp->defence_client]=wazatype;
					break;
				}
			}
			else{
				sp->waza_no_texture2[sp->defence_client]=0;
				sp->waza_no_texture2_client[sp->defence_client]=NONE_CLIENT_NO;
				sp->waza_no_texture2_type[sp->defence_client]=0;
			}
		}
	}
#endif //B1370_060815_FIX

	//�I�E���Ԃ����[�N�ւ̊i�[�i�Z���O�ꂽ�ꍇ�p�̊i�[�Ȃ̂ŁA�ړ��͌��ցj
	ServerOumugaeshiCheck(bw,sp);

	//���g���m�[���`�F�b�N
	ST_ServerMetronomeAfterCheck(bw,sp);

	sp->server_seq_no=SERVER_WAZA_END_NO;
}

//============================================================================================
/**
 *	�Z�V�[�P���X�I��
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaEnd(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;
	u32	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	//�T�t�@���]�[���A�|�P�p�[�N�ł́A�ȉ��̏����͕K�v�Ȃ�
	if((fight_type&(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK))==0){
		//�ēx���J�o�[�n�̓����̃`�F�b�N������
		if(ST_ServerTokuseiStatusRecoverCheck(bw,sp,sp->attack_client,0)==TRUE){
			return;
		}
		//�U���Ώۂ����Ȃ��ꍇ������̂Ń`�F�b�N����
		if((sp->defence_client!=NONE_CLIENT_NO)&&(ST_ServerTokuseiStatusRecoverCheck(bw,sp,sp->defence_client,0)==TRUE)){
			return;
		}

		if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
			return;
		}

		if(ServerZenmetsuCheck(bw,sp)==TRUE){
			return;
		}

		seq_no=ST_ServerPokeAppearCheck(bw,sp);
		if(seq_no){
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			return;
		}
		if(ServerVanishCheck(bw,sp)==TRUE){
			return;
		}
		ServerFlagOffReqAct(bw,sp);
	}

	sp->client_act_work[sp->client_agi_work[sp->agi_cnt]][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;

	//�g���b�N���[���������́A�ŏ�����ɂ���
	if(sp->ostf[sp->attack_client].trickroom_flag){
		ST_ServerTrickRoomAct(bw,sp);
		//�Z���ʔ����̂��߂̑f�����v�Z
		ST_ServerPSPAgiCalc(bw,sp);
		sp->agi_cnt=0;
	}
	else{
		sp->agi_cnt++;
	}

	ST_ServerWorkInit(sp);

	sp->server_seq_no=SERVER_ACTION_BRANCH_NO;
}

//============================================================================================
/**
 *	�|�P�������ꂩ����V�[�P���X
 *
 * @param
 */
//============================================================================================
static	void	ServerPokeReshuffleAfter(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;

	//��Ԉُ풼���n���`�F�b�N
	if(ST_ServerSoubiItemConditionBadCheck(bw,sp,sp->attack_client,&seq_no)==TRUE){
		sp->client_work=sp->attack_client;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		return;
	}
	sp->server_seq_no=SERVER_WAZA_END_NO;
}

//============================================================================================
/**
 *	�퓬���s�V�[�P���X
 *
 * @param
 */
//============================================================================================
static	void	ServerWinLose(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(BattleWorkWinLoseGet(bw)&FIGHT_ESCAPE_SELECT){
		sp->server_seq_no=SERVER_FIGHT_END_NO;
	}
	else if((BattleWorkWinLoseGet(bw)==FIGHT_LOSE)||(BattleWorkWinLoseGet(bw)==FIGHT_DRAW)){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_FIGHT_LOSE);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_FIGHT_END_NO;
	}
	else if(BattleWorkWinLoseGet(bw)==FIGHT_WIN){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_FIGHT_WIN);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_FIGHT_END_NO;
	}
	else if((BattleWorkWinLoseGet(bw)==FIGHT_POKE_GET)||(BattleWorkWinLoseGet(bw)==FIGHT_ESCAPE)){
		sp->server_seq_no=SERVER_FIGHT_END_NO;
	}
	sp->fight_end_flag=1;
}

//============================================================================================
/**
 *	�T�[�o�L���[���`�F�b�N���ďI����҂�
 *
 * @param
 */
//============================================================================================
static	void	ServerQueCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(ST_ServerQueCheck(sp)){
		if(sp->que_check_wait){
			sp->que_check_wait--;
		}
		else{
			sp->server_seq_no=sp->next_server_seq_no;
		}
	}
}

//============================================================================================
/**
 *	�퓬�I��
 *
 * @param
 */
//============================================================================================
static	void	ServerFightEnd(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	POKEPARTY	*ppt;
	u32	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	//�|�P���X�����`�F�b�N
	if((fight_type&FIGHT_TYPE_SIO)==0){
		ppt=BattleWorkPokePartyGet(bw,CLIENT_NO_MINE);
		PokerusSetCheck(ppt);
		PokerusCatchCheck(ppt);
	}

	if(fight_type&FIGHT_TYPE_SIO){
		CommSendFixData(CB_EXIT_BATTLE);
	}

	sp->server_seq_no=SERVER_FIGHT_END_WAIT_NO;
}

//============================================================================================
/**
 *	�퓬�I���i�ʐM�ΐ펞�̑҂��j
 *
 * @param
 */
//============================================================================================
static	void	ServerFightEndWait(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
}

#if 0
//============================================================================================
/**
 *	ServerQueCheck�Ɉڍs���邽�߂̃p�����[�^�Z�b�g
 *
 *	@param[in]	sp			�T�[�o�p�����[�^�\���̂̃|�C���^
 *	@param[in]	next_seq	ServerQueCheck��Ɉڍs����V�[�P���X�i���o�[
 *	@param[in]	wait		ServerQueCheck���WAIT
 */
//============================================================================================
static	void	ServerQueCheckSet(SERVER_PARAM *sp,int next_seq,int wait)
{
	sp->server_seq_no=SERVER_QUE_CHECK_NO;
	sp->next_server_seq_no=next_seq;
	sp->que_check_wait=wait;
}
#endif

//============================================================================================
/**
 *	����ւ��`�F�b�N
 *
 * @param
 */
//============================================================================================
static	const int	PosTable[]={
	0,0,0,0,3,3,
};

//============================================================================================
/**
 *	����ւ��`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerReshuffleCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret=FALSE;
	int		client_no;
	int		client_set_max;
	u32		fight_type;
	int		seq_no;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);
	seq_no=sp->server_seq_no;

	for(client_no=0;client_no<client_set_max;client_no++){
		sp->client_status[client_no]&=CLIENT_STATUS_POKE_RESHUFFLE_OFF;
		if(((fight_type&FIGHT_TYPE_2vs2)&&((fight_type&(FIGHT_TYPE_MULTI|FIGHT_TYPE_TAG))==0))||
		   ((fight_type&FIGHT_TYPE_TAG)&&((BattleWorkMineEnemyCheck(bw,client_no))==0))){
			//�_�u���m�b�N�_�E���Ȃ�1�̖ڂ������`�F�b�N
			if((sp->psp[client_no].hp==0)&&(sp->psp[client_no^2].hp==0)&&(client_no&2)){
				continue;
			}
			if(sp->psp[client_no].hp==0){
				{
					int	i;
					int	hp;
					int	hp_total=0;
					int	cnt=0;
					POKEPARTY		*poke_party;
					POKEMON_PARAM	*pp;
					CLIENT_PARAM	*cp;

					poke_party=BattleWorkPokePartyGet(bw,client_no);
					cp=BattleWorkClientParamGet(bw,client_no);
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=PokeParty_GetMemberPointer(poke_party,i);
						if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
						   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
							if(hp=PokeParaGet(pp,ID_PARA_hp,NULL)){
								cnt++;
								if(sp->sel_mons_no[client_no^2]!=i){
									hp_total+=hp;
								}
							}
						}
					}
					if(hp_total==0){
						sp->no_reshuffle_client|=No2Bit(client_no);	///<����ւ���|�P�����������Ȃ�ClientNo���r�b�g�Ŋi�[
						sp->sel_mons_no[client_no]=POKEMON_TEMOTI_MAX;
					}
					else{
						sp->next_server_seq_no=seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_status[client_no]|=CLIENT_STATUS_POKE_RESHUFFLE;
					}
				}
			}
		}
		else{
			if(sp->psp[client_no].hp==0){
				{
					int	i;
					int	hp=0;
					POKEPARTY		*poke_party;
					POKEMON_PARAM	*pp;
					CLIENT_PARAM	*cp;

					poke_party=BattleWorkPokePartyGet(bw,client_no);
					cp=BattleWorkClientParamGet(bw,client_no);
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=PokeParty_GetMemberPointer(poke_party,i);
						if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
						   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
							hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
						}
					}
	
					if(hp==0){
						sp->no_reshuffle_client|=No2Bit(client_no);	///<����ւ���|�P�����������Ȃ�ClientNo���r�b�g�Ŋi�[
						sp->sel_mons_no[client_no]=POKEMON_TEMOTI_MAX;
					}
					else{
						sp->next_server_seq_no=seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_status[client_no]|=CLIENT_STATUS_POKE_RESHUFFLE;
					}
				}
			}
		}
	}
#if 0
	if((fight_type&FIGHT_TYPE_2vs2)&&((fight_type&FIGHT_TYPE_MULTI)==0)){
		for(client_no=0;client_no<client_set_max;client_no++){
			sp->client_status[client_no]&=CLIENT_STATUS_POKE_RESHUFFLE_OFF;
			//�_�u���m�b�N�_�E���Ȃ�1�̖ڂ������`�F�b�N
			if((sp->psp[client_no].hp==0)&&(sp->psp[client_no^2].hp==0)&&(client_no&2)){
				continue;
			}
			if(sp->psp[client_no].hp==0){
				{
					int	i;
					int	hp;
					int	hp_total=0;
					int	cnt=0;
					POKEPARTY		*poke_party;
					POKEMON_PARAM	*pp;
					CLIENT_PARAM	*cp;

					poke_party=BattleWorkPokePartyGet(bw,client_no);
					cp=BattleWorkClientParamGet(bw,client_no);
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=PokeParty_GetMemberPointer(poke_party,i);
						if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
						   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
							if(hp=PokeParaGet(pp,ID_PARA_hp,NULL)){
								cnt++;
								if(sp->sel_mons_no[client_no^2]!=i){
									hp_total+=hp;
								}
							}
						}
					}
//�Z�̏I���őS�Ń`�F�b�N�����Ȃ��Ȃ����̂ŁA�����ł̃Z�b�g�ł͖��Ӗ��ɂȂ����i�C�₵���u�ԂɃZ�b�g�ɕύX�j
#if 0
					//�C�₵�Ă���N���C�A���g��client_act_work��WAZA_END���Z�b�g
					//�Z�V�[�P���X�����삵�Ȃ��悤�ɂ���
					sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;
#endif
					if(hp_total==0){
						sp->no_reshuffle_client|=No2Bit(client_no);	///<����ւ���|�P�����������Ȃ�ClientNo���r�b�g�Ŋi�[
					}
					else{
						sp->next_server_seq_no=seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_status[client_no]|=CLIENT_STATUS_POKE_RESHUFFLE;
					}
				}
			}
		}
	}
	else{
		for(client_no=0;client_no<client_set_max;client_no++){
			sp->client_status[client_no]&=CLIENT_STATUS_POKE_RESHUFFLE_OFF;
			if(sp->psp[client_no].hp==0){
				{
					int	i;
					int	hp=0;
					POKEPARTY		*poke_party;
					POKEMON_PARAM	*pp;
					CLIENT_PARAM	*cp;

					poke_party=BattleWorkPokePartyGet(bw,client_no);
					cp=BattleWorkClientParamGet(bw,client_no);
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=PokeParty_GetMemberPointer(poke_party,i);
						if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
						   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
							hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
						}
					}
	
//�Z�̏I���őS�Ń`�F�b�N�����Ȃ��Ȃ����̂ŁA�����ł̃Z�b�g�ł͖��Ӗ��ɂȂ����i�C�₵���u�ԂɃZ�b�g�ɕύX�j
					//�C�₵�Ă���N���C�A���g��client_act_work��WAZA_END���Z�b�g
					//�Z�V�[�P���X�����삵�Ȃ��悤�ɂ���
//					sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;
	
					if(hp==0){
						sp->no_reshuffle_client|=No2Bit(client_no);	///<����ւ���|�P�����������Ȃ�ClientNo���r�b�g�Ŋi�[
					}
					else{
						sp->next_server_seq_no=seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						sp->client_status[client_no]|=CLIENT_STATUS_POKE_RESHUFFLE;
					}
				}
			}
		}
	}
#endif
	if(sp->server_seq_no==SERVER_WAZA_SEQUENCE_NO){
		//�ΐ탋�[���ɂ���ē���ւ�������ς���
		if(((fight_type&FIGHT_TYPE_NO_IREKAE)==0)&&
			(BattleWorkConfigBattleRuleGet(bw)==BATTLERULE_IREKAE)&&
		  (((sp->client_status[CLIENT_NO_MINE]&CLIENT_STATUS_POKE_RESHUFFLE)==0)||
		   ((sp->client_status[CLIENT_NO_ENEMY]&CLIENT_STATUS_POKE_RESHUFFLE)==0))&&
			(ST_ServerReshuffleCheck(bw,sp,CLIENT_NO_MINE))){
			if(sp->client_status[CLIENT_NO_MINE]&CLIENT_STATUS_POKE_RESHUFFLE){
				sp->temp_work=0;
			}
			else{
				sp->temp_work=1;
			}
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_POKEMON_IREKAE);
		}
		else{
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_POKEMON_LIST);
		}
		ret=TRUE;
	}
	return ret;
}

//============================================================================================
/**
 *	�S�Ń`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerZenmetsuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int		client_no;
	int		client_set_max;
	u32		fight_type;
	u8		win_lose_flag;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);
	win_lose_flag=0;

	for(client_no=0;client_no<client_set_max;client_no++){
		//AI�}���`��ł́A�����������ŏ��s�����߂�
		if(((fight_type==FIGHT_TYPE_AI_MULTI)||
//		    (fight_type==FIGHT_TYPE_BATTLE_TOWER_AI_MULTI)||
		    (fight_type==FIGHT_TYPE_2vs2_YASEI))&&
			(BattleWorkMineEnemyCheck(bw,client_no)==0)){
			if(BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_A){	
				if(sp->psp[client_no].hp==0){
					{
						int	i;
						int	hp=0;
						POKEPARTY		*poke_party;
						POKEMON_PARAM	*pp;
						CLIENT_PARAM	*cp;
		
						poke_party=BattleWorkPokePartyGet(bw,client_no);
						cp=BattleWorkClientParamGet(bw,client_no);
		
						for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
							pp=PokeParty_GetMemberPointer(poke_party,i);
							if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
							   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
								hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
							}
						}
						if(hp==0){
							win_lose_flag|=FIGHT_LOSE;
						}
					}
				}
			}
		}
		else if((fight_type&FIGHT_TYPE_MULTI)||((fight_type&FIGHT_TYPE_TAG)&&(BattleWorkMineEnemyCheck(bw,client_no)))){
			if(sp->psp[client_no].hp==0){
				{
					int	i;
					int	hp=0;
					POKEPARTY		*poke_party1;
					POKEPARTY		*poke_party2;
					POKEMON_PARAM	*pp;
					CLIENT_PARAM	*cp;
	
					poke_party1=BattleWorkPokePartyGet(bw,client_no);
					poke_party2=BattleWorkPokePartyGet(bw,BattleWorkPartnerClientNoGet(bw,client_no));
					cp=BattleWorkClientParamGet(bw,client_no);
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party1);i++){
						pp=PokeParty_GetMemberPointer(poke_party1,i);
						if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
						   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
							hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
						}
					}
					for(i=0;i<PokeParty_GetPokeCount(poke_party2);i++){
						pp=PokeParty_GetMemberPointer(poke_party2,i);
						if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
						   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
							hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
						}
					}
	
					if(hp==0){
						if(CT_CPClientTypeGet(cp)&CLIENT_ENEMY_FLAG){
							win_lose_flag|=FIGHT_WIN;
						}
						else{
							win_lose_flag|=FIGHT_LOSE;
						}
					}
				}
			}
		}
		else{
			if(sp->psp[client_no].hp==0){
				{
					int	i;
					int	hp=0;
					POKEPARTY		*poke_party;
					POKEMON_PARAM	*pp;
					CLIENT_PARAM	*cp;
	
					poke_party=BattleWorkPokePartyGet(bw,client_no);
					cp=BattleWorkClientParamGet(bw,client_no);
	
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=PokeParty_GetMemberPointer(poke_party,i);
						if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
						   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
							hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
						}
					}
	
					if(hp==0){
						if(CT_CPClientTypeGet(cp)&CLIENT_ENEMY_FLAG){
							win_lose_flag|=FIGHT_WIN;
						}
						else{
							win_lose_flag|=FIGHT_LOSE;
						}
					}
				}
			}
		}
	}
	if(((win_lose_flag==FIGHT_WIN)&&(fight_type&FIGHT_TYPE_TRAINER)&&((fight_type&FIGHT_TYPE_SIO)==0))||
	   ((win_lose_flag==FIGHT_WIN)&&(fight_type&FIGHT_TYPE_TOWER)&&((fight_type&FIGHT_TYPE_SIO)==0))){
		{
			TRAINER_DATA	*td;

			td=BattleWorkTrainerDataGet(bw,CLIENT_NO_ENEMY);

			switch(td->tr_type){
			case TRTYPE_LEADER1:
			case TRTYPE_LEADER2:
			case TRTYPE_LEADER3:
			case TRTYPE_LEADER4:
			case TRTYPE_LEADER5:
			case TRTYPE_LEADER6:
			case TRTYPE_LEADER7:
			case TRTYPE_LEADER8:
			case TRTYPE_KUROTUGU:
				Snd_BgmPlay(SEQ_WINTGYM);
				break;
			case TRTYPE_CHAMPION:
				Snd_BgmPlay(SEQ_WINCHAMP);
				break;
			case TRTYPE_GINGALEADER1:
			case TRTYPE_GINGALEADER2:
			case TRTYPE_GINGALEADER3:
			case TRTYPE_GINGAM:
			case TRTYPE_GINGAW:
				Snd_BgmPlay(SEQ_WINGINGA);
				break;
			case TRTYPE_GINGALBOSS:
				Snd_BgmPlay(SEQ_WINAKAGI);
				break;
			case TRTYPE_BIGFOUR1:
			case TRTYPE_BIGFOUR2:
			case TRTYPE_BIGFOUR3:
			case TRTYPE_BIGFOUR4:
				Snd_BgmPlay(SEQ_WINTENNO);
				break;
			default:
				Snd_BgmPlay(SEQ_WINTRAIN);
				break;
			}
		}
		BattleWorkPinchSEFlagSet(bw,2);
	}

	if(win_lose_flag){
		BattleWorkWinLoseSet(bw,win_lose_flag);
	}

	return (win_lose_flag!=0);
}

//============================================================================================
/**
 *	�U���ΏۑI���`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerDirSelectCheck(SERVER_PARAM *sp,u8 client_no,u32 fight_type,int *range,int waza_pos,u32 *dir)
{
//	*range=WT_WazaDataParaGet(sp->psp[client_no].waza[waza_pos],ID_WTD_attackrange);
	//�̂낢�̎��́A�J��o��Client���݂āArange��ω�
	if((sp->psp[client_no].waza[waza_pos]==WAZANO_NOROI)&&
	   (ST_ServerWazaNoroiCheck(sp,sp->psp[client_no].waza[waza_pos],client_no)==FALSE)){
		*range=RANGE_MINE;
	}
	else{
		*range=sp->AIWT.wtd[sp->psp[client_no].waza[waza_pos]].attackrange;
	}

	if(fight_type&FIGHT_TYPE_2vs2){
		return TRUE;
	}
	else{
		if(*range&RANGE_MINE_DIR){
			*dir=client_no;
		}
		else{
			*dir=client_no^1;
		}
		return FALSE;
	}
}

//============================================================================================
/**
 *	�Z�V�[�P���X�ō폜�v���̂������t���O�����ׂč폜
 *
 * @param
 */
//============================================================================================
static	void	ServerFlagOffReqAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(client_no=0;client_no<client_set_max;client_no++){
		//condition2�t���O
		sp->psp[client_no].condition2&=(sp->condition2_off_req[client_no]^0xffffffff);
		sp->condition2_off_req[client_no]=0;
		//wazakouka�t���O(��\����\���Ɂj
//		if((sp->psp[client_no].waza_kouka&WAZAKOUKA_KIE)==0){
//			SCIO_PokemonVanishOnOff(bw,client_no,SW_VANISH_OFF);
//		}
	}

	sp->waza_no_hit[sp->attack_client]=0;
	sp->waza_no_texture2[sp->attack_client]=0;
}

//============================================================================================
/**
 *	�C��`�F�b�N
 *
 * @param[in]	sp			�T�[�o�p�����[�^�\����
 * @param[in]	next_seq	���Ɉړ�����V�[�P���X�i���o�[
 * @param[in]	no_set_seq	�C�₵�Ă��Ȃ������Ƃ��ɃZ�b�g����V�[�P���X�i���o�[
 * @param[in]	flag		�݂��Â�`�F�b�N�̗L��
 *
 * @retval	FALSE:�C��Ȃ��@TRUE:�C�₠��
 */
//============================================================================================
static	BOOL	ServerKizetsuCheck(SERVER_PARAM *sp,int next_seq,int no_set_seq,int flag)
{
	int	no;
	int	client_bit;

	no=0;
	client_bit=No2Bit(sp->psp_agi_work[no])<<SERVER_STATUS_FLAG_KIZETSU_SHIFT;

	if(sp->server_status_flag&SERVER_STATUS_FLAG_KIZETSU){
		while((sp->server_status_flag&client_bit)==0){
			no++;
			client_bit=No2Bit(sp->psp_agi_work[no])<<SERVER_STATUS_FLAG_KIZETSU_SHIFT;
		}
		sp->server_status_flag&=(client_bit^0xffffffff);
		sp->kizetsu_client=Bit2No(client_bit>>SERVER_STATUS_FLAG_KIZETSU_SHIFT);
//		sp->server_status_flag2|=No2Bit(sp->kizetsu_client)<<SERVER_STATUS_FLAG2_GET_EXP_SHIFT;
		if(flag==SKC_MICHIDURE_OFF){
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_KIZETSU);
		}
		else{
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MICHIDURE_KIZETSU);
		}
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=next_seq;
		//�C�₵�Ă���N���C�A���g��client_act_work��WAZA_END���Z�b�g
		//�Z�V�[�P���X�����삵�Ȃ��悤�ɂ���
		sp->client_act_work[sp->kizetsu_client][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;
		return TRUE;
	}
	else{
		sp->server_seq_no=no_set_seq;
		return FALSE;
	}
}

//============================================================================================
/**
 *	�o���l�擾�`�F�b�N
 *
 * @param[in]	sp			�T�[�o�p�����[�^�\����
 * @param[in]	next_seq	���Ɉړ�����V�[�P���X�i���o�[
 * @param[in]	no_set_seq	�擾���Ȃ��Ƃ��ɃZ�b�g����V�[�P���X�i���o�[
 *
 * @retval	FALSE:�擾�Ȃ��@TRUE:�擾����
 */
//============================================================================================
static	BOOL	ServerGetExpCheck(SERVER_PARAM *sp,int next_seq,int no_set_seq)
{
	if(sp->server_status_flag2&SERVER_STATUS_FLAG2_GET_EXP){
		{
			int	client_bit;

			client_bit=1<<SERVER_STATUS_FLAG2_GET_EXP_SHIFT;

			while((sp->server_status_flag2&client_bit)==0){
				client_bit=client_bit<<1;
			}
			sp->server_status_flag2&=(client_bit^0xffffffff);
			sp->kizetsu_client=Bit2No(client_bit>>SERVER_STATUS_FLAG2_GET_EXP_SHIFT);
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_GET_EXP);
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=next_seq;
		}
		return TRUE;
	}
	else{
		sp->server_seq_no=no_set_seq;
		return FALSE;
	}
}

#if B1370_060815_FIX
//============================================================================================
/**
 *	�I�E���������p���[�N�ւ̑���`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e���p�����[�^�\����
 * @param[in]	sp			�T�[�o�p�����[�^�\����
 */
//============================================================================================
static	void	ServerOumugaeshiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;
	int	wazatype;
	u8	eqp_d;

	//�����m�[�}���X�L���́A�^�C�v���m�[�}����
	if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(sp->waza_type){
		wazatype=sp->waza_type;
	}
	else{
		wazatype=sp->AIWT.wtd[sp->waza_no_now].wazatype;
	}

//	flag=WT_WazaDataParaGet(sp->waza_no_temp,ID_WTD_flag);
	flag=sp->AIWT.wtd[sp->waza_no_temp].flag;

	//�I�E���t���O�������Ă��邩
	if((flag&FLAG_OUMUGAESI)&&
	//�Z�b�g���Ȃ��t���O�͗����Ă��Ȃ����H
	  ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0)&&
	//�U���Ώۂ͐��킩�H
	  (sp->defence_client!=NONE_CLIENT_NO)&&
	//AttackMessage��������
	  (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
		sp->waza_no_oumu[sp->defence_client]=sp->waza_no_temp;	//���O�ɏo���Ă����o�b�t�@�ɑ��
		sp->waza_no_oumu_hit[sp->defence_client][sp->attack_client]=
			sp->waza_no_temp;	//2vs2�̂Ƃ��Ɏ󂯂����̃o�b�t�@�ɑ��
	}

	if(sp->defence_client!=NONE_CLIENT_NO){
		//Defence�̑��
		eqp_d=ST_ServerSoubiEqpGet(sp,sp->defence_client);
		if((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)||
		   (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
			//�����A�C�e���u�������͂��܂��v�́A�Z�̔����Ń��[�N�֑��
			if((eqp_d!=SOUBI_ONAZIWAZAONLY)&&
			   (eqp_d!=SOUBI_ONAZIWAZAONLYSUBAYASAUP)&&
			   (eqp_d!=SOUBI_ONAZIAWZAONLYTOKUSYUUP)){
				sp->psp[sp->defence_client].wkw.kodawari_wazano=0;
			}
		}

		//1�^�[���O�ɌJ��o���Ă����Z�Ƃ��Ċi�[�i�t���O�������Ă��鎞�͊i�[���Ȃ�
		if((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0){
			if(sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG){
				sp->waza_no_hit[sp->defence_client]=sp->waza_no_now;
				sp->waza_no_hit_client[sp->defence_client]=sp->attack_client;
				sp->waza_no_hit_type[sp->defence_client]=wazatype;
				sp->waza_no_last=sp->waza_no_temp;
			}
			else{
				sp->waza_no_hit[sp->defence_client]=0;
				sp->waza_no_hit_client[sp->defence_client]=NONE_CLIENT_NO;
				sp->waza_no_hit_type[sp->defence_client]=0;
				sp->waza_no_last=0;
			}
			if((sp->server_status_flag2&SERVER_STATUS_FLAG2_WAZA_OUT)&&
			  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
				//�e�N�X�`���[�Q���[�N�́A�i�[���郌���W�����肷��
				switch(sp->AIWT.wtd[sp->waza_no_now].attackrange){
				case RANGE_MINE:		//�����I��
				case RANGE_MINE_DOUBLE:	//�����Q�̑I��
				case RANGE_FIELD:		//��ɂ�����
				case RANGE_MAKIBISHI:	//�܂��т���p
				case RANGE_TEDASUKE:	//�Ă�������p
				case RANGE_TUBOWOTUKU:	//�ڂ�����p
					sp->waza_no_texture2[sp->defence_client]=0;
					sp->waza_no_texture2_client[sp->defence_client]=NONE_CLIENT_NO;
					sp->waza_no_texture2_type[sp->defence_client]=0;
					break;
				default:
					sp->waza_no_texture2[sp->defence_client]=sp->waza_no_now;
					sp->waza_no_texture2_client[sp->defence_client]=sp->attack_client;
					sp->waza_no_texture2_type[sp->defence_client]=wazatype;
					break;
				}
			}
			else{
				sp->waza_no_texture2[sp->defence_client]=0;
				sp->waza_no_texture2_client[sp->defence_client]=NONE_CLIENT_NO;
				sp->waza_no_texture2_type[sp->defence_client]=0;
			}
		}
	}
}
#else //B1370_060815_FIX
//============================================================================================
/**
 *	�I�E���������p���[�N�ւ̑���`�F�b�N
 *
 * @param[in]	bw			�퓬�V�X�e���p�����[�^�\����
 * @param[in]	sp			�T�[�o�p�����[�^�\����
 */
//============================================================================================
static	void	ServerOumugaeshiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;

//	flag=WT_WazaDataParaGet(sp->waza_no_temp,ID_WTD_flag);
	flag=sp->AIWT.wtd[sp->waza_no_temp].flag;

	//�I�E���t���O�������Ă��邩
	if((flag&FLAG_OUMUGAESI)&&
	//�Z�b�g���Ȃ��t���O�͗����Ă��Ȃ����H
	  ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0)&&
	//�U���Ώۂ͐��킩�H
	  (sp->defence_client!=NONE_CLIENT_NO)&&
	//AttackMessage��������
	  (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
		sp->waza_no_oumu[sp->defence_client]=sp->waza_no_temp;	//���O�ɏo���Ă����o�b�t�@�ɑ��
		sp->waza_no_oumu_hit[sp->defence_client][sp->attack_client]=
			sp->waza_no_temp;	//2vs2�̂Ƃ��Ɏ󂯂����̃o�b�t�@�ɑ��
	}
}
#endif //B1370_060815_FIX

//============================================================================================
/**
 *	�}���ɂ����������b�Z�[�W�\��
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerCriticalMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_CRITICAL_HIT);
	sp->next_server_seq_no=sp->server_seq_no;
	sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;

	return TRUE;
}

//============================================================================================
/**
 *	�΂���₢�܂ЂƂȂǃ��b�Z�[�W�\��
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerWazaStatusMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret;

	ret=FALSE;

	if(sp->waza_status_flag){
		//�A���U���̏ꍇ�́A�Ō�Ƀ��b�Z�[�W���o��
		if(sp->renzoku_count_temp){
			if((sp->kizetsu_client!=NONE_CLIENT_NO)||
			   (sp->renzoku_count==1)||
			   (sp->waza_status_flag&WAZA_STATUS_FLAG_RENZOKU_NOHIT)){
				ret=TRUE;
			}
		}
		else{
			ret=TRUE;
		}
	}
	if(ret==TRUE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_STATUS_MSG);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
	}
	return ret;
}

//============================================================================================
/**
 *	�����肪�q�b�g������̃`�F�b�N�V�[�P���X�i���o�[
 */
//============================================================================================
enum{
	SIC_IKARI_ATTACK_CHECK=0,
	SIC_IKARI_DEFENCE_CHECK,
	SIC_END
};

//============================================================================================
/**
 *	�Z���q�b�g������̂�����`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerIkariCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret;
	
	ret=FALSE;

	//�U���Ώۂ����Ȃ���΁A�`�F�b�N�Ȃ�
	if(sp->defence_client==NONE_CLIENT_NO){
		return ret;
	}

	if((sp->psp[sp->defence_client].condition2&CONDITION2_IKARI)&&
	  ((sp->waza_status_flag&WAZA_STATUS_FLAG_RENZOKU_NOHIT)==0)&&
	   (sp->defence_client!=sp->attack_client)&&
	   (sp->psp[sp->defence_client].hp)&&
	  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||(sp->ostf[sp->defence_client].tokusyu_ostf_damage))){
		if(sp->psp[sp->defence_client].abiritycnt[COND_POW]<12){
			sp->psp[sp->defence_client].abiritycnt[COND_POW]++;
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_IKARI_VOLTAGE_UP);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			ret=TRUE;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	�Z���q�b�g������̂�������̂��邵�`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerHirumaseruCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret=FALSE;
	int		eqp;
	int		atk;

	eqp=ST_ServerSoubiEqpGet(sp,sp->attack_client);
	atk=ST_ServerSoubiAtkGet(sp,sp->attack_client,ATK_CHECK_NORMAL);

	if(sp->defence_client!=NONE_CLIENT_NO){
#ifdef PM_DEBUG
		if((eqp==SOUBI_HIRUMASERU)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
		 (((gf_rand()%100)<atk)||(sp->dbp.debug_flag&DEBUG_FLAG_SOUBI))&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_OUZYANOSIRUSI)&&
		   (sp->psp[sp->defence_client].hp)){
#else
		if((eqp==SOUBI_HIRUMASERU)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->ostf[sp->defence_client].butsuri_ostf_damage)||
		   (sp->ostf[sp->defence_client].tokusyu_ostf_damage))&&
		  ((gf_rand()%100)<atk)&&
		   (sp->AIWT.wtd[sp->waza_no_now].flag&FLAG_OUZYANOSIRUSI)&&
		   (sp->psp[sp->defence_client].hp)){
#endif
			sp->tsuika_client=sp->defence_client;
			sp->tsuika_type=ADD_STATUS_INDIRECT;
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HIRUMU);
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			ret=TRUE;
		}
	}
	return ret;
}

//============================================================================================
/**
 *	�����Ă���|�P�������ǂ����邩�`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerVanishCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret=FALSE;

	while(sp->svc_work<BattleWorkClientSetMaxGet(bw)){
		if(((sp->psp[sp->svc_work].waza_kouka&WAZAKOUKA_KIE)==0)&&
			(sp->psp[sp->svc_work].waza_kouka_temp&WAZAKOUKA_KIE)){
		    sp->psp[sp->svc_work].waza_kouka_temp&=WAZAKOUKA_KIE_OFF;
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_VANISH_OFF);
			sp->client_work=sp->svc_work;
			sp->next_server_seq_no=sp->server_seq_no;
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			ret=TRUE;
		}
		sp->svc_work++;
		if(ret==TRUE){
			break;
		}
	}
	if(ret==FALSE){
		sp->svc_work=0;
	}
	return ret;
}

//============================================================================================
/**
 *	�Z���q�b�g������̃`�F�b�N�V�[�P���X�i���o�[
 */
//============================================================================================
enum{
	SWHAC_IKARI_ATTACK_CHECK=0,
	SWHAC_SOUBI_HPKAIHUKUDAMEEZIRITU,
	SWHAC_SOUBI_WAZAIRYOKUUPHPMAINASU,
	SWHAC_END
};

//============================================================================================
/**
 *	�Z���q�b�g������̃`�F�b�N
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerWazaHitAfterCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	ret;
	int	client_no;
	int	client_set_max;
	int	eqp;
	int	atk;
	
	ret=0;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	eqp=ST_ServerSoubiEqpGet(sp,sp->attack_client);
	atk=ST_ServerSoubiAtkGet(sp,sp->attack_client,ATK_CHECK_NORMAL);

	//�C��`�F�b�N
	if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
		return TRUE;
	}
	//�o���l�擾�`�F�b�N
//	if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
//		return TRUE;
//	}
	//�S�Ń`�F�b�N
//	if(ServerZenmetsuCheck(bw,sp)==TRUE){
//		return TRUE;
//	}

	do{
		switch(sp->swhac_seq_no){
		case SWHAC_IKARI_ATTACK_CHECK:
			//�������ԂŁA��������o���Ă��Ȃ����́A�������ԉ���
			if((sp->psp[sp->attack_client].condition2&CONDITION2_IKARI)&&(sp->waza_no_now!=WAZANO_IKARI)){
				sp->psp[sp->attack_client].condition2&=CONDITION2_IKARI_OFF;
			}
			sp->swhac_seq_no++;
			break;
		case SWHAC_SOUBI_HPKAIHUKUDAMEEZIRITU:
			if(sp->defence_client!=NONE_CLIENT_NO){
				if((eqp==SOUBI_HPKAIHUKUDAMEEZIRITU)&&
				   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
				  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
				   (sp->server_status_flag&SERVER_STATUS_FLAG_WAZA_HIT)&&
			       (sp->ostf[sp->attack_client].kaigara_damage)&&
				   (sp->attack_client!=sp->defence_client)&&
				   (sp->psp[sp->attack_client].hp<sp->psp[sp->attack_client].hpmax)&&
				   (sp->psp[sp->attack_client].hp)){
					sp->hp_calc_work=ST_ServerDamageDiv(sp->ostf[sp->attack_client].kaigara_damage*-1,atk);
					sp->client_work=sp->attack_client;
					ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_EQPITEM_HP_KAIHUKUMAITURN);
					sp->next_server_seq_no=sp->server_seq_no;
					sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
					ret=1;
				}
			}
			sp->swhac_seq_no++;
			break;
		case SWHAC_SOUBI_WAZAIRYOKUUPHPMAINASU:
			if((eqp==SOUBI_WAZAIRYOKUUPHPMAINASU)&&
				//�����}�W�b�N�K�[�h�̓_���[�W�Ȃ�
			   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
			   //�Ƃ�ڂ��������ւ��ł́A�����Ȃ�
			  ((sp->server_status_flag2&SERVER_STATUS_FLAG2_TONBOGAERI)==0)&&
			   (sp->server_status_flag&SERVER_STATUS_FLAG_WAZA_HIT)&&
//				(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_kind)!=KIND_HENKA)&&
				(sp->AIWT.wtd[sp->waza_no_now].kind!=KIND_HENKA)&&
				(sp->psp[sp->attack_client].hp)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*-1,10);
				sp->client_work=sp->attack_client;
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_EQPITEM_HP_MAINASU);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				ret=1;
			}
			sp->swhac_seq_no++;
			break;
		case SWHAC_END:
			sp->swhac_seq_no=0;
			sp->swhac_work=0;
			ret=2;
			break;
		}
	}while(ret==0);

	return (ret==1);
}


