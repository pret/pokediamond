
//============================================================================================
/**
 * @file	server.c
 * @bfief	戦闘サーバプログラム
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
//#define	ORDER_IGNORE_ONLY	//命令無視して違う技を出すだけにする
#endif DEBUG_ONLY_FOR_sogabe
#endif PM_DEBUG

void	*ServerInit(BATTLE_WORK *bw);
int		ServerMain(BATTLE_WORK *battle_work,SERVER_PARAM *server_param);
void	ServerEnd(SERVER_PARAM *server_param);

void	ServerHitCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);

static	void	ServerPokemonParamGet(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<ポケモンパラメータをサーバワークにゲット
static	void	ServerEncountSet(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<エンカウント処理
static	void	ServerTrainerMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<戦闘中にトレーナーが出てきてメッセージ表示
static	void	ServerPokeAppearCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<ポケモン登場時にチェックする項目
static	void	ServerCommandSelectInit(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<コマンド選択処理初期化
static	void	ServerCommandSelect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<コマンド選択処理
static	void	ServerAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<素早さ計算処理
static	void	ServerBeforeAct(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<動作前処理
static	void	ServerActionBranch(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<動作分岐処理
static	void	ServerFieldConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<場にかかっている戦闘効果チェック
static	void	ServerPokeConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<ポケモンにかかっている戦闘効果チェック
static	void	ServerSideConditionCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<ポケモンにかかっている戦闘効果チェック（側にかかっている効果）
static	void	ServerTurnEnd(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<戦闘ターン終了処理
static	void	ServerFightCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<たたかう動作処理
static	void	ServerItemCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<道具使用処理
static	void	ServerPokemonCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<ポケモン選択処理
static	void	ServerEscapeCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<にげる動作処理

static	void	ServerSafariBallCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<サファリでボール投げる処理
static	void	ServerSafariEsaCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<サファリでエサ投げる処理
static	void	ServerSafariDoroCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<サファリでドロ投げる処理
static	void	ServerSafariYousumiCommand(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<サファリで様子見処理

static	int		ServerBadgeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);	///<バッジチェック
static	BOOL	ServerPPCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<PPチェック
static	BOOL	ServerDefenceCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<攻撃対象チェック
static	BOOL	ServerTypeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<TYPEチェック
static	BOOL	ServerStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<状態異常チェック
static	BOOL	ServerTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<特性チェック
static	BOOL	ServerSenseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<先制系のアイテム効果のチェック
static	BOOL	ServerHitCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);	///<命中率チェック
static	BOOL	ServerWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);	///<技効果チェック
static	BOOL	ServerWazaKoyuuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<技固有チェック

static	void	ServerWazaSequence(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<技シーケンス実行
static	void	ServerWazaBefore(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<技前処理
static	void	ServerWazaOutCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<技発動チェック
static	void	ServerAddStatusDirectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<追加効果チェック（直接追加のみ）
static	void	ServerWazaHazureMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<当たらなかった系メッセージ表示
static	void	ServerWazaOut(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<技発動処理
static	void	ServerHPCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);					///<HP計算
static	void	ServerWazaOutAfterMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<技がでた後のいろいろなメッセージ表示
static	void	ServerAddStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<追加効果チェック（直接追加以外）
static	void	ServerWazaOutAfterKouka(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<技がでた後のいろいろな効果チェック
static	void	ServerRenzokuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<連続攻撃のチェック
static	void	ServerSinkuroCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<特性シンクロチェック
static	void	ServerKizetsuEffect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<気絶エフェクト
static	void	ServerLoopCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<複数体当たる技のチェック
static	void	ServerJibakuEffect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<じばくによる気絶エフェクト
static	void	ServerWazaHitAfterCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<技がヒットした後のチェック
static	void	ServerGetExpEffect(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<経験値取得エフェクト
static	void	ServerWazaNoBufferSet(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<技ナンバーをバッファに格納
static	void	ServerWazaEnd(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<技シーケンス終了
static	void	ServerPokeReshuffleAfter(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<ポケモンいれかえ後シーケンス
static	void	ServerWinLose(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<戦闘勝敗シーケンス
//static	void	ServerQueCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<サーバキューをチェックして終了を待つ

static	void	ServerFightEnd(BATTLE_WORK *bw,SERVER_PARAM *sp);				///<戦闘終了
static	void	ServerFightEndWait(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<戦闘終了（通信対戦時の待ち）

static	BOOL	ServerReshuffleCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<入れ替えチェック
static	BOOL	ServerZenmetsuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<全滅チェック
static	BOOL	ServerDirSelectCheck(SERVER_PARAM *sp,u8 client_no,u32 fight_type,int *range,int waza_pos,u32 *dir); ///<攻撃対象選択チェック
static	void	ServerFlagOffReqAct(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<削除要求のあったフラグの削除

static	BOOL	ServerKizetsuCheck(SERVER_PARAM *sp,int next_seq,int no_set_seq,int flag);	///<気絶チェック
static	BOOL	ServerGetExpCheck(SERVER_PARAM *sp,int next_seq,int no_set_seq);	///<経験値取得チェック
static	void	ServerOumugaeshiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<オウムがえしバッファへの代入チェック
static	BOOL	ServerWazaHitAfterCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp);	///<技がヒットした後のチェック

//static	void	ServerQueCheckSet(SERVER_PARAM *sp,int next_seq,int wait);

static	BOOL	ServerCriticalMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<急所にあたったメッセージ表示
static	BOOL	ServerWazaStatusMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);		///<ばつぐんやいまひとつなどメッセージ表示
static	BOOL	ServerIkariCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	ServerHirumaseruCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	ServerVanishCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);			///<消えているポケモンをどうするかチェック

///<サーバシーケンステーブル
static	const	svFunc	ServerSequenceTbl[]={
	ServerPokemonParamGet,		///<ポケモンパラメータをサーバワークにゲット
	ServerEncountSet,			///<エンカウント処理
	ServerTrainerMessage,		///<戦闘中にトレーナーが出てきてメッセージ表示
	ServerPokeAppearCheck,		///<ポケモン登場時にチェックする項目
	ServerCommandSelectInit,	///<コマンド選択処理初期化
	ServerCommandSelect,		///<コマンド選択処理
	ServerAgiCalc,				///<素早さ計算処理
	ServerBeforeAct,			///<動作前処理
	ServerActionBranch,			///<動作分岐処理
	ServerFieldConditionCheck,	///<場にかかっている戦闘効果チェック
	ServerPokeConditionCheck,	///<ポケモンにかかっている戦闘効果チェック
	ServerSideConditionCheck,	///<ポケモンにかかっている戦闘効果チェック（側にかかっている効果）
	ServerTurnEnd,				///<戦闘ターン終了処理

	ServerFightCommand,			///<たたかう動作処理
	ServerItemCommand,			///<道具使用処理
	ServerPokemonCommand,		///<ポケモン選択処理
	ServerEscapeCommand,		///<にげる動作処理

	ServerSafariBallCommand,	///<サファリでボール投げる処理
	ServerSafariEsaCommand,		///<サファリでエサ投げる処理
	ServerSafariDoroCommand,	///<サファリでドロ投げる処理
	ServerSafariYousumiCommand,	///<サファリで様子見処理

	ServerWazaSequence,			///<技シーケンス実行
	ServerWazaBefore,			///<技前処理
	ServerWazaOutCheck,			///<技発動チェック
	ServerAddStatusDirectCheck,	///<追加効果チェック（直接追加のみ）
	ServerWazaHazureMessage,	///<当たらなかった系メッセージ表示
	ServerWazaOut,				///<技発動処理
	ServerHPCalc,				///<HP計算
	ServerWazaOutAfterMessage,	///<技がでた後のいろいろなメッセージ表示
	ServerAddStatusCheck,		///<追加効果チェック（直接追加以外）
	ServerWazaOutAfterKouka,	///<技がでた後のいろいろな効果チェック
	ServerRenzokuCheck,			///<連続攻撃のチェック
	ServerSinkuroCheck,			///<シンクロチェック
	ServerKizetsuEffect,		///<気絶エフェクト
	ServerLoopCheck,			///<複数体当たる技のチェック
	ServerJibakuEffect,			///<じばくによる気絶エフェクト
	ServerWazaHitAfterCheck,	///<技がヒットした後のチェック
	ServerGetExpEffect,			///<経験値取得エフェクト
	ServerWazaNoBufferSet,		///<技ナンバーをバッファへ格納
	ServerWazaEnd,				///<技シーケンス終了

	ServerPokeReshuffleAfter,	///<ポケモンいれかえ後シーケンス

	ServerWinLose,				///<戦闘勝敗シーケンス

//	ServerQueCheck,				///<サーバキューをチェックして終了を待つ

	ServerFightEnd,				///<戦闘終了
	ServerFightEndWait,			///<戦闘終了（通信対戦時の待ち）
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

	//Wifiの時は、AIがロードされていないので無視
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

	//この仕様はなくなりました
#if 0
	//特性かたやぶりが発動していたら専用メッセージ表示シーケンスへ
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
	if(sp->server_seq_no==SERVER_FIGHT_END_WAIT_NO){			///<戦闘終了
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
	//AIのメモリ展開をやめたので、開放処理は必要なし
//	if(server_param->AISeqWork){
//		sys_FreeMemoryEz(server_param->AIWT.handle);
//		sys_FreeMemoryEz(server_param->AISeqWork);
//	}
	sys_FreeMemoryEz(server_param->AIWT.item);
	sys_FreeMemoryEz(server_param);
}

//============================================================================================
/**
 *	命中率チェックと技効果による命中チェックをする	
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
 *	ポケモンパラメータをサーバワークにゲット
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

	//対戦相手の現在HPを保存
	sp->hp_temp=sp->psp[CLIENT_NO_ENEMY].hp;

	sp->server_seq_no=SERVER_ENCOUNT_SET_NO;
}

//============================================================================================
/**
 *	エンカウント処理
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
 *	戦闘中にトレーナーが出てきてメッセージ表示
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
	//技効果発動のための素早さ計算
	ST_ServerPSPAgiCalc(bw,sp);
}

//============================================================================================
/**
 *	ポケモン登場時にチェックする項目
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
		//技効果発動のための素早さ計算（装備効果の発動で素早さが変わっている場合があるので、再計算）
		ST_ServerPSPAgiCalc(bw,sp);
		sp->server_seq_no=SERVER_COMMAND_SELECT_INIT_NO;
	}
}

//============================================================================================
/**
 *	コマンド選択処理初期化
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
		//消えている状態を監視するために、技効果ワークをテンポラリにコピー
		sp->psp[client_no].waza_kouka_temp=sp->psp[client_no].waza_kouka;
	}

	//コマンド選択でボタンがスライドインしたときに落とされるフラグをセット
	BattleWorkCommandSelectFlagSet(bw,SLIDE_IN_BEFORE);

	sp->server_seq_no=SERVER_COMMAND_SELECT_NO;
}

//============================================================================================
// 	コマンド選択処理のシーケンスナンバー
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
 *	コマンド選択処理
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
			///<入れ替えるポケモンを持たないClientNoは、コマンド選択なし
			if(sp->no_reshuffle_client&No2Bit(client_no)){
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
				sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;	///<技シーケンス終了
				break;
			}
			else if(ST_ServerCommandSelectCheck(sp,client_no)==FALSE){
				//コマンド選択しなかった時はPPを減らさないフラグを立てる
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
						///<アンコールを受けている時は、技選択なし
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
							OS_Printf("コマンドセレクトで、不正なSELECT_CALCEL！\n");
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
						//技のポジションが返ってくる
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
				//攻撃対象が返ってくる
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
					//アイテムナンバーとページナンバーが返ってくる
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
				//選んだポケモンの位置が返ってくる
				sp->client_act_work[client_no][ACT_PARA_WORK]=sp->server_buffer[client_no][0]-1;
				sp->reshuffle_sel_mons_no[client_no]=sp->server_buffer[client_no][0]-1;
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
				OS_TPrintf("client_no:%d r_sel_mons:%d\n",client_no,sp->reshuffle_sel_mons_no[client_no]);
			}
			break;
		case SCSSEQ_ESCAPE_SELECT_INIT:
			//タワーは、あきらめるか聞く
			if(fight_type&FIGHT_TYPE_TOWER){
				SCIO_YesNoSelectSet(bw,sp,client_no,GiveUpMsg,YNTYPE_YES_NO,NULL,NULL);
				sp->com_seq_no[client_no]=SCSSEQ_ESCAPE_SELECT;
			}
			//トレーナー戦は逃げれない
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
				//にげるでの、はい／いいえ選択は無し
				sp->com_seq_no[client_no]=SCSSEQ_COMMAND_SELECT_WAIT;
			}
			//2vs2は、1体目の逃げる選択で、逃げるを確定
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
				//クライアントからの返答バッファをクリア
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
		//ListRowの並び替えチェック
		for(client_no=0;client_no<client_set_max;client_no++){
			if(sp->client_act_work[client_no][ACT_PARA_ACT_NO]==SERVER_POKEMON_COMMAND_NO){
				ST_ServerListRowChange(bw,sp,client_no,sp->reshuffle_sel_mons_no[client_no]);
			}
		}
	}
}

//============================================================================================
/**
 *	素早さ計算処理
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
	//サファリゾーン、ポケパークは必ず自分が先攻
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
													//技選択と逃げる以外を抽出
													//技とにげる以外は無条件に先攻
				if((sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]==SELECT_ITEM_COMMAND)||
				   (sp->client_act_work[client_no][ACT_PARA_SELECT_COMMAND]==SELECT_POKEMON_COMMAND)){
					sp->client_agi_work[turn]=client_no;
					turn++;
				}
			}
			for(client_no=0;client_no<client_set_max;client_no++){	
													//技選択を抽出
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
 *	動作前処理シーケンスナンバー
 */
//============================================================================================

enum{
	SBA_KIAI_PUNCH=0,			//きあいパンチメッセージ表示チェック
	SBA_IKARI,					//いかり連続選択チェック
	SBA_AGI_CALC,				//技効果発動順番を決める素早さチェック

	SBA_END
};

//============================================================================================
/**
 *	動作前処理
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
		case SBA_KIAI_PUNCH:		//きあいパンチメッセージ表示チェック
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
		case SBA_IKARI:				//いかり連続選択チェック
			for(client_no=0;client_no<client_set_max;client_no++){
				//いかり状態で、
				//いかりを連続で選択していなければ、いかり状態を解除
				if((sp->psp[client_no].condition2&CONDITION2_IKARI)&&(ST_ServerSelectWazaGet(sp,client_no)!=WAZANO_IKARI)){
					sp->psp[client_no].condition2&=CONDITION2_IKARI;
				}
			}
			sp->sba_seq_no++;
			break;
		case SBA_AGI_CALC:
			for(client_no=0;client_no<CLIENT_MAX;client_no++){
				sp->agi_rand[client_no]=gf_rand();	///<素早さチェックに使用する乱数値
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
 *	動作分岐処理
 *
 * @param
 */
//============================================================================================
static	void	ServerActionBranch(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_set_max;

	client_set_max=BattleWorkClientSetMaxGet(bw);

	//技効果発動のための素早さ計算
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
 *	場にかかっている戦闘効果チェック用シーケンスナンバー
 */
//============================================================================================

enum{
	FCC_REFLEC=0,	//リフレクター効果切れ
	FCC_HIKARI,		//ひかりのかべ効果切れ
	FCC_SHIROI,		//しろいきり効果切れ
	FCC_SHINPI,		//しんぴのまもり効果切れ
	FCC_OIKAZE,		//おいかぜ効果切れ
	FCC_OMAZINAI,	//おまじない効果切れ
	FCC_NEGAIGOTO,	//ねがいごと発動
	FCC_AMAGOI,		//あまごい効果切れ
	FCC_SUNAARASHI,	//すなあらし効果切れ
	FCC_NIHONBARE,	//にほんばれ効果切れ
	FCC_ARARE,		//あられ効果切れ
	FCC_HUKAIKIRI,	//ふかいきり効果切れ
	FCC_JUURYOKU,	//じゅうりょく効果切れ
	FCC_END
};

//============================================================================================
/**
 *	場にかかっている戦闘効果チェック
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
		//気絶チェック
		if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
			return;
		}
		//経験値取得チェック
		if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
			return;
		}
		//全滅チェック
		if(ServerZenmetsuCheck(bw,sp)==TRUE){
			return;
		}

		switch(sp->fcc_seq_no){
		case FCC_REFLEC:	 //リフレクター
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
		case FCC_HIKARI: //ひかりのかべ
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
		case FCC_SHIROI: //しろいきり
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
		case FCC_SHINPI: //しんぴのまもり
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
		case FCC_OIKAZE:					//おいかぜチェック
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
		case FCC_OMAZINAI:	//おまじない効果切れ
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
		case FCC_NEGAIGOTO:		//ねがいごとチェック
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
		case FCC_AMAGOI:					//あまごいチェック
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
		case FCC_SUNAARASHI:					//すなあらしチェック
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
		case FCC_NIHONBARE:					//にほんばれチェック
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
		case FCC_ARARE:						//あられチェック
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
		case FCC_HUKAIKIRI:					//ふかいきりチェック
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
		case FCC_JUURYOKU:					//じゅうりょくチェック
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
 *	ポケモンにかかっている戦闘効果チェック用シーケンスナンバー
 */
//============================================================================================

enum{
//HP回復系を先にチェックして気絶しにくくする
	POKE_CONDITION_CHECK_NEWOHARU=0,	//ねをはるでHP回復
	POKE_CONDITION_CHECK_AQUARING,		//アクアリングでHP回復
	POKE_CONDITION_CHECK_SPEABI,		//特性でHP回復
	POKE_CONDITION_CHECK_SOUBI,			//装備効果でHP回復
	POKE_CONDITION_CHECK_TABENOKOSI,	//装備効果でHP回復（たべのこしのみ）

	POKE_CONDITION_CHECK_YADORIGI,		//やどりぎで、HP増減
	POKE_CONDITION_CHECK_DOKU,			//どくのダメージチェック
	POKE_CONDITION_CHECK_DOKUDOKU,		//どくどくのダメージチェック
	POKE_CONDITION_CHECK_YAKEDO,		//やけどのダメージチェック
	POKE_CONDITION_CHECK_AKUMU,			//あくむのダメージチェック
	POKE_CONDITION_CHECK_NOROI,			//のろいのダメージチェック
	POKE_CONDITION_CHECK_SHIME,			//しめつけられ系のダメージチェック
	POKE_CONDITION_CHECK_NIGHTMARE,		//ナイトメアのダメージチェック
	POKE_CONDITION_CHECK_SAWAGU,		//さわぐ効果切れチェック
	POKE_CONDITION_CHECK_ABARERU,		//あばれる効果切れチェック
	POKE_CONDITION_CHECK_KANASHIBARI,	//かなしばり効果切れチェック
	POKE_CONDITION_CHECK_ENCORE,		//アンコール効果切れチェック
	POKE_CONDITION_CHECK_LOCKON,		//ロックオン効果切れチェック
	POKE_CONDITION_CHECK_JUUDEN,		//じゅうでん発動チェック
	POKE_CONDITION_CHECK_CHOUHATSU,		//ちょうはつ効果切れチェック
	POKE_CONDITION_CHECK_DENZIHUYUU,	//でんじふゆう効果切れチェック
	POKE_CONDITION_CHECK_HEALBLOCK,		//ヒールブロック効果切れチェック
	POKE_CONDITION_CHECK_SHUTOUT,		//シャットアウト効果切れチェック
	POKE_CONDITION_CHECK_AKUBI,			//あくび発動チェック
	POKE_CONDITION_CHECK_SOUBI2,		//装備効果で回復
	POKE_CONDITION_CHECK_SOUBI_DAMAGE,	//装備効果でダメージ
//	POKE_CONDITION_CHECK_SINKURO,		//装備効果でダメージで状態異常になる可能性があるのでチェック
	POKE_CONDITION_CHECK_END,
};

//============================================================================================
/**
 *	ポケモンにかかっている戦闘効果チェック
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

	//気絶チェック
	if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
		return;
	}
	//経験値取得チェック
	if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
		return;
	}
	//全滅チェック
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
		//ねをはる
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
		//アクアリング
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
		//特殊能力
		case POKE_CONDITION_CHECK_SPEABI:
			if(ST_ServerPCCTokuseiCheck(sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//装備アイテム
		case POKE_CONDITION_CHECK_SOUBI:
			if(ST_ServerSoubiItemCheck(bw,sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//装備効果でHP回復（たべのこしのみ）
		case POKE_CONDITION_CHECK_TABENOKOSI:
			if(ST_ServerSoubiItemTabenokosiCheck(bw,sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
		//やどりぎのたね
		case POKE_CONDITION_CHECK_YADORIGI:
			if((sp->psp[client_no].waza_kouka&WAZAKOUKA_YADORARE)&&
			   (sp->psp[sp->psp[client_no].waza_kouka&WAZAKOUKA_YADORIGI].hp!=0)&&
			   //特性マジックガードは、やどりぎのたねの効果を受けない
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
		//どくチェック
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
		//どくどくチェック
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
		//やけどチェック
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
		//あくむチェック
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
		//のろいチェック
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
		//しめ系の技
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
		//ナイトメアのダメージチェック
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
		//さわぐチェック
		case POKE_CONDITION_CHECK_SAWAGU:
			if(sp->psp[client_no].condition2&CONDITION2_SAWAGU){
				{
					u8	sleep_client;

					//眠っているポケモンがいたら起こす
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
		//あばれるチェック
		case POKE_CONDITION_CHECK_ABARERU:
			if(sp->psp[client_no].condition2&CONDITION2_ABARERU){
				sp->psp[client_no].condition2-=ABARERU_COUNT;
				//まひで攻撃が出せなかったときは、あばれおわる
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
				//KEEPが落ちているときは、強制的に技をとめられているので、
				//混乱しないようにする
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
		//かなしばり
		case POKE_CONDITION_CHECK_KANASHIBARI:
			if(sp->psp[client_no].wkw.kanashibari_wazano){
				//技忘れで、かなしばりされていた技がないときの処理
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
		//アンコール
		case POKE_CONDITION_CHECK_ENCORE:
			if(sp->psp[client_no].wkw.encore_wazano){
				for(i=0;i<WAZA_TEMOTI_MAX;i++){
					if(sp->psp[client_no].wkw.encore_wazano==sp->psp[client_no].waza[i]){
						break;
					}
				}
				//技忘れで、アンコールされていた技がないとき、PPがない時の処理
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
		//ロックオン
		case POKE_CONDITION_CHECK_LOCKON:
			if(sp->psp[client_no].waza_kouka&WAZAKOUKA_LOCKON){
				sp->psp[client_no].waza_kouka-=LOCKON_COUNT;
			}
			sp->pcc_seq_no++;
			break;
		//じゅうでん
		case POKE_CONDITION_CHECK_JUUDEN:
			if(sp->psp[client_no].wkw.juuden_count){
				if(--sp->psp[client_no].wkw.juuden_count==0){
					sp->psp[client_no].waza_kouka&=WAZAKOUKA_JUUDEN_OFF;
				}
			}
			sp->pcc_seq_no++;
			break;
		//ちょうはつ
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
		//でんじふゆう
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
		//ヒールブロック
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
		//シャットアウト
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
		//あくび
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
		//装備アイテム
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
		//装備効果でダメージ
		case POKE_CONDITION_CHECK_SOUBI_DAMAGE:
			if(ST_ServerSoubiItemDamageCheck(bw,sp,client_no)==TRUE){
				ret=1;
			}
			sp->pcc_seq_no++;
			break;
#if 0
		//装備効果でダメージで状態異常になる可能性があるのでチェック
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
 *	ポケモンにかかっている戦闘効果チェック２用シーケンスナンバー
 */
//============================================================================================

enum{
	SIDE_CONDITION_CHECK_MIRAIYOCHI=0,
	SIDE_CONDITION_CHECK_HOROBINOUTA,
	SIDE_CONDITION_CHECK_TRICKROOM,			//処理順に影響するので、かならず最後にチェックすること！
//	SIDE_CONDITION_CHECK_DOUJOU_HANTEI,
};

//============================================================================================
/**
 *	ポケモンにかかっている戦闘効果チェック（側にかかっている効果）
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

	//気絶チェック
	if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
		return;
	}
	//ほろびのうたで、素早さで相手の方が先に気絶した時に経験値が入らないようにTurnEndに移動
	//経験値取得チェック
//	if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
//		return;
//	}
	//ほろびのうたで、引き分けにするために毎Syncのチェックはなくす
	//全滅チェック
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
			//ほろびのうた
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
	case SIDE_CONDITION_CHECK_TRICKROOM:					//トリックルーム効果切れ
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
 *	戦闘ターン終了処理
 *
 * @param
 */
//============================================================================================
static	void	ServerTurnEnd(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//経験値取得チェック
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
	//サーバワークの初期化
	ST_ServerWorkInit(sp);
	ST_ServerOneTurnFlagInit(bw,sp);
	sp->server_seq_no=SERVER_TRAINER_MESSAGE_NO;
}

//============================================================================================
/**
 *	たたかう動作処理
 *
 * @param
 */
//============================================================================================
static	void	ServerFightCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;

	flag=0;		//DefenceClientを決めるflag

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		//WIFI接続では、AIがのっていないので、ランダムで相手を選択
		if(CommStateIsWifiConnect()){
			flag=1;
		}
	}
#endif PM_DEBUG

	sp->attack_client=sp->client_agi_work[sp->agi_cnt];
	//わるあがきフラグが立っていた場合はわるあがきをセット
	if(sp->otf[sp->attack_client].waruagaki_flag){
		sp->waza_no_temp=WAZANO_WARUAGAKI;
		flag=1;
	}
	//アンコールを受けている時は、受けた技ナンバーをセット
	else if((sp->psp[sp->attack_client].wkw.encore_wazano)&&
			(sp->psp[sp->attack_client].wkw.encore_wazano==
			 sp->psp[sp->attack_client].waza[sp->psp[sp->attack_client].wkw.encore_wazapos])){
		sp->waza_no_temp=sp->psp[sp->attack_client].wkw.encore_wazano;
		flag=1;
	}
	//アンコールを受けている技を忘れたらアンコールを解除
	else if((sp->psp[sp->attack_client].wkw.encore_wazano)&&
			(sp->psp[sp->attack_client].wkw.encore_wazano!=
			 sp->psp[sp->attack_client].waza[sp->psp[sp->attack_client].wkw.encore_wazapos])){
		sp->waza_no_temp=sp->psp[sp->attack_client].waza[sp->psp[sp->attack_client].wkw.encore_wazapos];
		sp->psp[sp->attack_client].wkw.encore_wazano=0;
		sp->psp[sp->attack_client].wkw.encore_wazapos=0;
		sp->psp[sp->attack_client].wkw.encore_count=0;
		flag=1;
	}
	//ため技系の技を出していた場合、反動で動けない場合は、前ターンの技ナンバーをセット
	else if(ST_ServerCommandSelectCheck(sp,sp->attack_client)==FALSE){
		sp->waza_no_temp=sp->waza_no_keep[sp->attack_client];
	}
	//選択されていた技を忘れていたらDefenceを再抽選する
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

	//攻撃対象がいないので、シーケンス終了へジャンプ（あとでチェックに変更）
//	if(sp->defence_client==NONE_CLIENT_NO){
//		OS_TPrintf("対象なし: atk:%d def:%d\n",sp->attack_client,sp->defence_client);
//		sp->server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
//	}
}

//============================================================================================
/**
 *	道具使用処理
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
		case BBAG_POKE_STRCV:	// 状態回復ポケット
		case BBAG_POKE_HPRCV:	// HP回復ポケット
		case BBAG_POKE_BATTLE:	// 戦闘用ポケット
			if((isrp->item_no==ITEM_PIPPININGYOU)||
			   (isrp->item_no==ITEM_ENEKONOSIPPO)){
				seq_no=SUB_SEQ_ITEM_ESCAPE;
			}
			else{
				seq_no=SUB_SEQ_ITEM_BATTLE_ITEM;
			}
			break;
		case BBAG_POKE_BALL:	// ボールポケット
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
	//技は発動していないので、失敗にする
	sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI;
}

//============================================================================================
/**
 *	ポケモン選択処理
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
//	sp->next_server_seq_no=SERVER_POKE_RESHUFFLE_AFTER_NO;		///<ポケモンいれかえ後シーケンス
	sp->next_server_seq_no=SERVER_WAZA_END_NO;
	sp->temp_work=0;	//自分からのいれかえを示す値を入れておく
	//技は発動していないので、失敗にする
	sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI;
}

//============================================================================================
/**
 *	にげる動作処理
 *
 * @param
 */
//============================================================================================
static	void	ServerEscapeCommand(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	sp->attack_client=sp->client_agi_work[sp->agi_cnt];

	//敵側は100%で逃げる
	if((BattleWorkMineEnemyCheck(bw,sp->attack_client))&&
	  ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO)==0)){
		//逃げられない技効果を受けている時は、逃げられない
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
 *	サファリでボール投げる処理
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
 *	サファリでエサ投げる処理
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
	//大当たりの時は、捕獲率のみ上昇
	if(sp->temp_work!=0){
		if(sp->safari_escape_count<SAFARI_COUNT_MAX){
			sp->safari_escape_count++;
		}
	}
}

//============================================================================================
/**
 *	サファリでドロ投げる処理
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
	//大当たりの時は、逃走率のみ下降
	if(sp->temp_work!=0){
		sp->msg_work=1;
		if(sp->safari_get_count){
			sp->safari_get_count--;
		}
	}
}

//============================================================================================
/**
 *	サファリで様子見処理
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
 *	バッジチェック
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

	//バッジチェックしないFIGHT_TYPEをチェック
	if(fight_type&FIGHT_TYPE_NO_BADGE){
		return 0;
	}
	//敵側は、バッジチェックなし
	if(BattleWorkMineEnemyCheck(bw,sp->attack_client)){
		return 0;
	}
	//不正なポケモンをチェック
//	if(HuseiPokemonCheck(AttackClient)){
//		return 0;
//	}
	//AIマルチ対戦で、パートナーだったらバッジチェックはしない
	if((fight_type&FIGHT_TYPE_AI)&&(BattleWorkClientTypeGet(bw,sp->attack_client)==CLIENT_TYPE_C)){
		return 0;
	}
	//自分の持ちポケモンだったらバッジチェックはしない
	if((ST_ServerPokeOneSelfCheckAct(bw,sp))==TRUE){
		return 0;
	}
	//コマンド選択のない技をすでに出しているならバッジチェックはしない
	if(ST_ServerCommandSelectCheck(sp,sp->attack_client)==FALSE){
		return 0;
	}
	//バッジをすべてもっているならチェックはしない
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

	//バッジで解禁されているレベルならいうことを聞く
	if(sp->psp[sp->attack_client].level<=level){
		return 0;
	}

	i=((gf_rand()&0xff)*(sp->psp[sp->attack_client].level+level))>>8;

	if(i<level){
		return 0;
	}

	//いかりを選択していたなら、ボルテージをあげないようにする
	if(sp->waza_no_now==WAZANO_IKARI){
		sp->psp[sp->attack_client].condition2&=CONDITION2_IKARI_OFF;
	}

	if((sp->psp[sp->attack_client].condition&CONDITION_NEMURI)&&
	  ((sp->waza_no_now==WAZANO_IBIKI)||(sp->waza_no_now==WAZANO_NEGOTO))){
		seq_no[0]=SUB_SEQ_ORDER_IGNORE_SLEEP;	//命令無視（ねむり）
		return 1;
	}

	i=((gf_rand()&0xff)*(sp->psp[sp->attack_client].level+level))>>8;

#ifndef ORDER_IGNORE_ONLY
	if(i<level){
#endif ORDER_IGNORE_ONLY
		i=ST_ServerWaruagakiCheck(bw,sp,sp->attack_client,No2Bit(sp->waza_no_pos[sp->attack_client]),SSWC_ALL);
		if(i==0x0f){		//出せる技がない
			seq_no[0]=SUB_SEQ_NAMAKERU;		//命令無視（なまける）
			return 1;
		}
		do{
			j=gf_rand()&3;
		}while(i&No2Bit(j));
		sp->waza_no_pos[sp->attack_client]=j;
		sp->waza_no_temp=sp->psp[sp->attack_client].waza[sp->waza_no_pos[sp->attack_client]];
		sp->waza_no_now=sp->waza_no_temp;
		sp->defence_client=ST_ServerDefenceClientSet(bw,sp,sp->attack_client,sp->waza_no_temp,1,0);
		seq_no[0]=SUB_SEQ_ORDER_IGNORE;		//命令無視
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
			seq_no[0]=SUB_SEQ_HIRUNE;				//命令無視（ひるね）
			return 1;
		}
	}

	i-=level;

	if(i<level){
		sp->defence_client=sp->attack_client;
		sp->client_work=sp->defence_client;
		//自分への攻撃は、はたくを威力４０で計算したダメージ
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
		seq_no[0]=SUB_SEQ_OWN_ATTACK;			//命令無視（自分を攻撃）
		return 3;
	}

	seq_no[0]=SUB_SEQ_NAMAKERU;			//命令無視（なまける）

	return 1;
}


//============================================================================================
/**
 *	PPチェック
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

//特殊能力プレッシャーはPPが倍減る
	if((sp->ostf[sp->attack_client].no_pressure_flag==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
		//ふういんは、RANGE_DOUBLEと同じ処理をする
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

	//わるあがきは、PPCheckは無視
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
			GF_ASSERT_MSG(0,"手持ちにない技のPPを減らそうとしている！\n");
		}
#endif PM_DEBUG
		else{
			sp->waza_status_flag|=WAZA_STATUS_FLAG_PP_NONE;
		}
	}
	//PPがないチェック
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
 *	攻撃対象チェック
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerDefenceCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret;

	ret=FALSE;

	//攻撃対象がいない場合は、その旨のメッセージを表示して終了（ためターンは除く）
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
 *	TYPEチェック
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerTypeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//自分選択の技、威力無、タイプ無属性、ため技系の1ターン目は、TYPEチェックをしない、
	//「でんじは」は、地面に当てないようにするために、チェックする
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
 *	状態異常チェックのシーケンスナンバー
 */
//============================================================================================
enum{
	SSC_INIT=0,		//チェック初期化
	SSC_NEMURI,		//ねむりチェック
	SSC_KOORI,		//こおりチェック
	SSC_NAMAKE,		//なまけチェック
	SSC_HANDOU,		//はんどうチェック
	SSC_HIRUMU,		//ひるむチェック
	SSC_KANASIBARI,	//かなしばりチェック
	SSC_TYOUHATU,	//ちょうはつチェック
	SSC_HUUIN,		//ふういんチェック
	SSC_JUURYOKU,	//じゅうりょくチェック
	SSC_HEALBLOCK,	//ヒールブロックチェック
	SSC_KONRAN,		//こんらんチェック
	SSC_MAHI,		//まひチェック
	SSC_MEROMERO,	//メロメロチェック
	SSC_GAMAN,		//がまんチェック
	SSC_MELT,		//とけるチェック
	SSC_END			//チェックエンド
};

enum{
	SSC_ACT_LOOP=0,			//チェック継続
	SSC_ACT_NO_WAZA_OUT,	//技の発動ができない
	SSC_ACT_WAZA_SEQ,		//メッセージ表示などのシーケンスへ
	SSC_ACT_END				//チェックの終了
};

//============================================================================================
/**
 *	状態異常チェック
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
		case SSC_INIT:		//チェック初期化
			//みちづれフラグをOFF
			sp->psp[sp->attack_client].condition2&=CONDITION2_MICHIDURE_OFF;
			//おんねんフラグをOFF
			sp->psp[sp->attack_client].waza_kouka&=WAZAKOUKA_ONNEN_OFF;
			sp->ssc_seq_no++;
			break;
		case SSC_NEMURI:		//ねむりチェック
			//眠っているときは、起きるチェック
			if(sp->psp[sp->attack_client].condition&CONDITION_NEMURI){
				{
					int	cnt;
		
					//騒がしい状態で、自分が特性ぼうおんを持っていないときは起きる
					if((sp->field_condition&FIELD_CONDITION_SAWAGU)&&
					   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_BOUON)){
						sp->client_work=sp->attack_client;
						ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_MEZAME);
						sp->next_server_seq_no=sp->server_seq_no;
						sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
						ret=SSC_ACT_WAZA_SEQ;
					}
					else{
						//ねごとの派生では、ねむりカウンタのDECをしない
						if(((sp->waza_no_now!=WAZANO_NEGOTO)&&(sp->waza_no_temp==WAZANO_NEGOTO))==0){
							//特殊能力はやおきは、はやくねむりからさめる
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
								//ねごとといびきは、寝ていても技が出せるので無視する
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
		case SSC_KOORI:		//こおりチェック
			//凍っているときは、とけるチェック
			if(sp->psp[sp->attack_client].condition&CONDITION_KOORI){
				//5分の1の確率で溶ける
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
		case SSC_NAMAKE:		//なまけチェック
			if(ST_ServerNamakeCheck(sp,sp->attack_client)==TRUE){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_NAMAKE);
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//				sp->next_server_seq_no=SERVER_WAZA_END_NO;
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				ret=SSC_ACT_NO_WAZA_OUT;
			}
			sp->ssc_seq_no++;
			break;
		case SSC_HANDOU:		//はんどうチェック
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
		case SSC_HIRUMU:		//ひるむチェック
			//ひるんでいる時は技が出せない
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
		case SSC_KANASIBARI:	//かなしばりチェック
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
		case SSC_TYOUHATU:	//ちょうはつチェック
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
		case SSC_HUUIN:		//ふういんチェック
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
		case SSC_JUURYOKU:	//じゅうりょくチェック
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
		case SSC_HEALBLOCK:	//ヒールブロックチェック
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
		case SSC_KONRAN:		//こんらんチェック
			sp->ssc_seq_no++;
			if(sp->psp[sp->attack_client].condition2&CONDITION2_KONRAN){		//こんらんチェック
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
						//自分への攻撃は、わるあがきを威力４０で計算したダメージ（特性テクニシャンを発動させないため）
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
		case SSC_MAHI:		//まひチェック
			if((sp->psp[sp->attack_client].condition&CONDITION_MAHI)&&
				//特性マジックガードは、まひの効果をうけない
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
		case SSC_MEROMERO:	//メロメロチェック
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
		case SSC_GAMAN:		//がまんチェック
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
		case SSC_MELT:		//とけるチェック
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
		case SSC_END:		//チェックエンド
			sp->ssc_seq_no=SSC_INIT;
			ret=SSC_ACT_END;
			break;
		}
	}while(ret==SSC_ACT_LOOP);

	ST_PSPtoPPCopy(bw,sp,sp->attack_client);

	if(ret==SSC_ACT_NO_WAZA_OUT){
		//技の起動に失敗しているなら、複数体に当たるチェックをしないフラグを立てる
		sp->server_status_flag|=SERVER_STATUS_FLAG_NO_DOUBLE_CHECK;
		//技の起動に失敗しているなら、失敗フラグを立てる
		sp->waza_status_flag|=WAZA_STATUS_FLAG_SIPPAI;
	}
	return (ret!=SSC_ACT_END);
}
	
//============================================================================================
/**
 *	特性チェックのシーケンスナンバー
 */
//============================================================================================
enum{
	STC_DAMAGE=0,		//ダメージを受け止める特性チェック
	STC_END
};

enum{
	STC_ACT_LOOP=0,			//チェック継続
	STC_ACT_WAZA_SEQ,		//メッセージ表示などのシーケンスへ
	STC_ACT_END				//チェックの終了
};

//============================================================================================
/**
 *	特性チェック
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
			//特性でダメージを受け止めるチェック
			seq_no=ST_ServerDamageTokuseiCheck(sp,sp->attack_client,sp->defence_client);
			if(((seq_no)&&((sp->waza_status_flag&WAZA_STATUS_FLAG_HAZURE)==0))||
				(seq_no==SUB_SEQ_BOUON)){
				ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,seq_no);
				sp->next_server_seq_no=sp->server_seq_no;
				sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
				//技の起動に失敗しているなら、失敗フラグを立てる
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
 *	先制系のアイテム効果のチェック
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
 *	abiritycntによる命中率変化テーブル
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
 *	命中率チェック
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

	//捕獲デモは、100%命中
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_GET_DEMO){
		return FALSE;
	}

	//特性ノーマルスキンは、タイプをノーマルに
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

	//特性たんじゅんを持っているときは、ヒット率上昇を倍
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_TANZYUN){
		cond_hit*=2;
	}

	//特性たんじゅんを持っているときは、回避率上昇を倍
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TANZYUN)==TRUE){
		cond_avoid*=2;
	}

	//特性てんねんを持っているときは、ヒット率をフラットに
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TENNEN)==TRUE){
		cond_hit=0;
	}

	//特性てんねんを持っているときは、回避率をフラットに
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_TENNEN){
		cond_avoid=0;
	}

	//みやぶる、かぎわける、ミラクルアイ効果のあるときは、上昇している回避率を元に戻す
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

	//命中率0は、エクセル上で「－」なので絶対に当たる
	if(hit==0){
		return FALSE;
	}

	//ため技系の1ターン目は、命中率に関係なく技を発動
	if(sp->server_status_flag&SERVER_STATUS_FLAG_TAME){
		return FALSE;
	}

	//別の命中率計算をしている時は、こっちの計算はしない
	if(sp->server_status_flag&SERVER_STATUS_FLAG_OTHER_HIT_CALC){
		return FALSE;
	}

	//特殊能力のうてんきは、チェックをしない
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//晴れのとき、かみなりは命中率を50%にする
//		if((sp->field_condition&FIELD_CONDITION_HARE_ALL)&&(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)==152)){
		if((sp->field_condition&FIELD_CONDITION_HARE_ALL)&&(sp->AIWT.wtd[waza_no].battleeffect==152)){
			hit=50;
		}
	}

	hit*=HPT[value].kakeru;
	hit/=HPT[value].waru;

	//特殊能力ふくがんは、命中率を３０％アップ
	if(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_HUKUGAN){
		hit=hit*130/100;
	}

	//特殊能力のうてんきは、チェックをしない
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//特殊能力すながくれは、命中率を２０％ダウン（すなあらしの時に）
		if(sp->field_condition&FIELD_CONDITION_SUNAARASHI_ALL){
			if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_SUNAGAKURE)==TRUE){
				hit=hit*80/100;
			}
		}
		//特性雪がくれは、命中率を２０％ダウン（あられの時に）
		if(sp->field_condition&FIELD_CONDITION_ARARE_ALL){
			if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_YUKIGAKURE)==TRUE){
				hit=hit*80/100;
			}
		}
		//天候がふかいきりの時は、命中率を6/10にする
		if(sp->field_condition&FIELD_CONDITION_HUKAIKIRI){
			hit=hit*6/10;
		}
	}

	//特殊能力はりきりは、物理攻撃の命中率を２０％ダウン
	if((ST_ServerTokuseiGet(sp,attack)==TOKUSYU_HARIKIRI)&&(wazakind==KIND_BUTSURI)){
		hit=hit*80/100;
	}

	//特性ちどりあしは、混乱中の命中率を５０％ダウン
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TIDORIASI)==TRUE)&&
	   (sp->psp[defence].condition2&CONDITION2_KONRAN)){
		hit=hit*50/100;
	}

	eqp=ST_ServerSoubiEqpGet(sp,defence);
	atk=ST_ServerSoubiAtkGet(sp,defence,ATK_CHECK_NORMAL);

	//アイテムで命中率ダウンの効果のあるものは、命中率をダウン
	if(eqp==SOUBI_MEITYUURITUDOWN){
		hit=hit*(100-atk)/100;
	}

	eqp=ST_ServerSoubiEqpGet(sp,attack);
	atk=ST_ServerSoubiAtkGet(sp,attack,ATK_CHECK_NORMAL);

	//アイテムで命中率アップの効果のあるものは、命中率をアップ
	if(eqp==SOUBI_MEITYUUUP){
		hit=hit*(100+atk)/100;
	}

	//アイテムで後攻のとき、命中率アップの効果のあるものは、命中率をアップ
	if((eqp==SOUBI_KOUKOUNOTOKIMEITYUUUP)&&(ST_ServerWazaEndCheck(sp,defence)==TRUE)){
		hit=hit*(100+atk)/100;
	}

	//装備効果で一度だけ命中率アップは、命中率を20%アップ
	if(sp->psp[attack].wkw.once_hit_up){
		sp->psp[attack].wkw.once_hit_up=0;
		hit=hit*120/100;
	}

	//じゅうりょく中は、命中率を10/6倍にアップ
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
 *	技効果チェック
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no)
{
	//ため技系の1ターン目は、技を発動させるので、チェックの必要なし
	if(sp->server_status_flag&SERVER_STATUS_FLAG_TAME){
		return FALSE;
	}

	//まもるが、優先順位的に最上位
	//技にまもるフラグが立っていて、mamoru_flagがたっていれば、まもる
//	if((sp->otf[defence].mamoru_flag)&&(WT_WazaDataParaGet(waza_no,ID_WTD_flag)&FLAG_MAMORU)){
	if((sp->otf[defence].mamoru_flag)&&(sp->AIWT.wtd[waza_no].flag&FLAG_MAMORU)){
		//のろいでノーマルだったら、まもるを無視
		if((waza_no!=WAZANO_NOROI)||(ST_ServerWazaNoroiCheck(sp,waza_no,attack)==TRUE)){
			if((ST_TameWazaCheck(sp,waza_no)==FALSE)||(sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER)){
				ST_ServerKeepOff(bw,sp,attack);
				sp->waza_status_flag|=WAZA_STATUS_FLAG_MAMORU_NOHIT;
				return FALSE;
			}
		}
	}

	//通常の命中率計算ではなかった場合は、ロックオン、ノーガードチェックをしない
	if((sp->server_status_flag&SERVER_STATUS_FLAG_OTHER_HIT_CALC)==0){
		//ロックオン効果がかかっているとき、特性ノーガードを持っているポケモンに対しては、必ず命中
		if(((sp->psp[defence].waza_kouka&WAZAKOUKA_LOCKON)&&
		    (sp->psp[defence].wkw.lockon_client_no==attack))||
		    (ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOGAADO)||
		    (ST_ServerTokuseiGet(sp,sp->defence_client)==TOKUSYU_NOOGAADO)){
			//命中率計算でのはずれを落とす
			sp->waza_status_flag&=WAZA_STATUS_FLAG_NOHIT_OFF;
			return FALSE;
		}
	}
	//特殊能力のうてんきは、チェックをしない
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//雨のとき、かみなりは必ず命中
//		if((sp->field_condition&FIELD_CONDITION_AME_ALL)&&(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)==152)){
		if((sp->field_condition&FIELD_CONDITION_AME_ALL)&&(sp->AIWT.wtd[waza_no].battleeffect==152)){
			sp->waza_status_flag&=WAZA_STATUS_FLAG_NOHIT_OFF;
		}
		//あられのとき、ふぶきは必ず命中
//		if((sp->field_condition&FIELD_CONDITION_ARARE_ALL)&&(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)==260)){
		if((sp->field_condition&FIELD_CONDITION_ARARE_ALL)&&(sp->AIWT.wtd[waza_no].battleeffect==260)){
			sp->waza_status_flag&=WAZA_STATUS_FLAG_NOHIT_OFF;
		}
	}

	//ロックオン効果で当たっている場合は、場にいないチェックはしない
	if(((sp->waza_status_flag&WAZA_STATUS_FLAG_LOCK_ON)==0)&&
	//まきびし系は、チェックしない
		(sp->AIWT.wtd[sp->waza_no_now].attackrange!=RANGE_MAKIBISHI)){
		if(
			//そらをとぶ、あなをほる、ダイビング、シャドウダイブ中は、当たらない（特定の技を除いて）
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
 *	技固有チェック
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

	//対象がいなければ、チェックなし
	if(sp->defence_client==NONE_CLIENT_NO){
		return FALSE;
	}

	//マジックコートチェック
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
	//よこどりチェック
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
 *	技シーケンス実行
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
 *	技前処理チェックシーケンス
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
 *	技前処理
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaBefore(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	switch(sp->wb_seq_no){
	case SEQ_SENSEI_CHECK:
		ServerSenseiCheck(bw,sp);			///<先制系のアイテム効果のチェック
		sp->wb_seq_no++;
		return;
		break;
	case SEQ_STATUS_CHECK:
		if((sp->waza_out_check_on_off&STATUS_CHECK_OFF)==0){
			if(ServerStatusCheck(bw,sp)==TRUE){			///<状態異常チェック
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
					switch(ret){			///<バッジチェック
					case 1:		//いうことを聞かずに技をださない系
//						sp->next_server_seq_no=SERVER_WAZA_END_NO;
						sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
						break;
					case 2:		//いうことを聞かずに別の技を出す
						sp->next_server_seq_no=sp->server_seq_no;
						break;
					case 3:		//命令を無視して自分を攻撃
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
			if(ServerPPCheck(bw,sp)==TRUE){				///<PPチェック
				return;
			}
		}
		sp->wb_seq_no++;
	case SEQ_DEFENCE_CHECK:
		if(ServerDefenceCheck(bw,sp)==TRUE){			///<攻撃対象チェック
			return;
		}
		sp->wb_seq_no++;
	case SEQ_WAZAKOYUU_CHECK:
		if((sp->waza_out_check_on_off&WAZAKOYUU_CHECK_OFF)==0){
			if(ServerWazaKoyuuCheck(bw,sp)==TRUE){		///<技固有チェック
				return;
			}
		}
		sp->wb_seq_no++;
	case SEQ_DEFENCE_CHANGE_CHECK:
		ST_ServerDefenceClientTokuseiCheck(bw,sp,sp->attack_client,sp->waza_no_now);
		sp->wb_seq_no=0;
	}
	//技が出せない系のフラグが立っている場合は、はずれメッセージシーケンスへ
	if(sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT){
		sp->server_seq_no=SERVER_WAZA_HAZURE_MESSAGE_NO;
	}
	else{
		sp->server_status_flag2|=SERVER_STATUS_FLAG2_WAZA_OUT;
		ST_ServerSequenceLoad(sp,ARC_WAZA_SEQ,sp->waza_no_now);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		sp->next_server_seq_no=SERVER_WAZA_OUT_CHECK_NO;
		//とっておきカウントを計算
		ST_ServerTotteokiCountCalc(bw,sp);
	}
	//メトロノームチェック
	ST_ServerMetronomeBeforeCheck(bw,sp);
}

//============================================================================================
/**
 *	技発動チェックのシーケンスナンバー
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
 *	技発動チェック
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaOutCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{

	switch(sp->woc_seq_no){
	//パワフルハーブで、ためターンがスルーされてここまできてしまうので、再度NONE_CLIENT_NOチェックをする
	case SEQ_DEFENCE_CHECK2:
		sp->woc_seq_no++;
		if(ServerDefenceCheck(bw,sp)==TRUE){			///<攻撃対象チェック
			return;
		}
	//DefenceClientを変更する特性のチェック
	case SEQ_DEFENCE_CHANGE_ACT:
		sp->woc_seq_no++;
		if(ST_ServerDefenceClientTokuseiAct(bw,sp)==TRUE){
			return;
		}
	case SEQ_HIT_CHECK:
		if(((sp->waza_out_check_on_off&HIT_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerHitCheck(bw,sp,sp->attack_client,sp->defence_client,sp->waza_no_now)==TRUE){		///<命中率チェック
				return;
			}
		}
		sp->woc_seq_no++;
	case SEQ_WAZAKOUKA_CHECK:
		if(((sp->waza_out_check_on_off&WAZAKOUKA_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerWazaKoukaCheck(bw,sp,sp->attack_client,sp->defence_client,sp->waza_no_now)==TRUE){		///<技効果チェック
				return;
			}
		}
		sp->woc_seq_no++;
	case SEQ_TYPE_CHECK:
		if(((sp->waza_out_check_on_off&TYPE_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerTypeCheck(bw,sp)==TRUE){			///<TYPEチェック
				return;
			}
		}
		sp->woc_seq_no++;
	case SEQ_TOKUSEI_CHECK:
		if(((sp->waza_out_check_on_off&TOKUSEI_CHECK_OFF)==0)&&(sp->defence_client!=NONE_CLIENT_NO)){
			if(ServerTokuseiCheck(bw,sp)==TRUE){		///<特性チェック
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
 *	追加効果チェック（直接追加のみ）
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
 *	当たらなかった系メッセージ表示
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaHazureMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//技の起動に失敗していると、このフラグが立っているので、以降のチェックはしない
	if(sp->waza_status_flag&WAZA_STATUS_FLAG_SIPPAI){
		sp->server_seq_no=SERVER_LOOP_CHECK_NO;
	}
	//PPがない時
	else if(sp->waza_status_flag&WAZA_STATUS_FLAG_PP_NONE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_PP_NONE);
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
//		sp->next_server_seq_no=SERVER_WAZA_END_NO;
		sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
	}
	//連続攻撃系でのはずれは、連続をやめる
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
 *	技後処理
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
 *	HP計算処理
 *
 * @param
 */
//============================================================================================
static	void	ServerHPCalc(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	eqp;
	int	atk;

	//一撃必殺の時は、HPMAXをダメージに代入
	if(sp->waza_status_flag&WAZA_STATUS_FLAG_ICHIGEKI){
		sp->damage=sp->psp[sp->defence_client].hpmax*-1;
	}
	if(sp->damage){
		eqp=ST_ServerSoubiEqpGet(sp,sp->defence_client);
		atk=ST_ServerSoubiAtkGet(sp,sp->defence_client,ATK_CHECK_NORMAL);

		//バグではないけど、あるかないかを判断するため
		GF_ASSERT_MSG(sp->damage<0,"ダメージが＋です\n");

		//パーティアタックをした回数をカウントアップ
		if(BattleWorkMineEnemyCheck(bw,sp->attack_client)==BattleWorkMineEnemyCheck(bw,sp->defence_client)){
			SCIO_IncRecord(bw,sp->attack_client,CLIENT_BOOT_TYPE_MINE,RECID_TEMOTI_MAKIZOE);
		}

		//最後に当てたClientNoを専用バッファに格納
		sp->client_no_hit[sp->defence_client]=sp->attack_client;

		//みがわりチェック
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
			//みねうちチェック
//			if(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_battleeffect)==101){
			if(sp->AIWT.wtd[sp->waza_no_now].battleeffect==101){
				//気絶してしまう時は、１残すようにする
				if((sp->psp[sp->defence_client].hp+sp->damage)<=0){
					sp->damage=(sp->psp[sp->defence_client].hp-1)*-1;
				}
			}
			//技のこらえるが成功している時は、アイテムのチェックをしない
			if(sp->otf[sp->defence_client].koraeru_flag==0){
				//アイテムこらえるチェック
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
			//こらえるチェック
			if((sp->otf[sp->defence_client].koraeru_flag)||(sp->ostf[sp->defence_client].item_koraeru_flag)){
				//気絶してしまう時は、１残すようにする
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
			//がまん用のダメージストックワークに足しこみ
			sp->store_damage[sp->defence_client]+=sp->damage;
	
			//攻撃を受けたカウンタをカウントアップ
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
			//かいがらダメージは実際にＨＰを減らした実際量で計算
			if((sp->psp[sp->defence_client].hp+sp->damage)<=0){
				sp->ostf[sp->attack_client].kaigara_damage+=(sp->psp[sp->defence_client].hp*-1);
			}
			else{
				sp->ostf[sp->attack_client].kaigara_damage+=sp->damage;
			}
			sp->otf[sp->defence_client].last_otf_damage=sp->damage;
			sp->otf[sp->defence_client].last_otf_client=sp->attack_client;
			///<HP計算処理
			sp->client_work=sp->defence_client;
			sp->hp_calc_work=sp->damage;
			ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HP_CALC);
			sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
			sp->next_server_seq_no=SERVER_WAZA_OUT_AFTER_MESSAGE_NO;
			//技が当たったことを示すフラグを立てる
			sp->server_status_flag|=SERVER_STATUS_FLAG_WAZA_HIT;
		}
	}
	else{
		sp->server_seq_no=SERVER_WAZA_OUT_AFTER_MESSAGE_NO;
	}
}

//============================================================================================
/**
 *	技がでた後のいろいろなメッセージ表示
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
 *	追加効果チェック（直接追加以外）（上の関数の中に吸収）
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
 *	技がでた後のいろいろな効果チェック
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
				//wazakoukaフラグ(非表示を表示に）
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
	//バトンタッチやとんぼがえりで入れかえがあった時用
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
			
			//特性ノーマルスキンは、技タイプをノーマルにする
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
 *	シンクロチェック（場所移動）
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
 *	連続攻撃のチェック
 *
 * @param
 */
//============================================================================================
static	void	ServerRenzokuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->renzoku_count_temp){
		//気絶したポケモンがいた場合、眠ってしまった場合、命中率チェックで外れた場合は、チェックを終了
		if((sp->kizetsu_client==NONE_CLIENT_NO)&&
		  ((sp->psp[sp->attack_client].condition&CONDITION_NEMURI)==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_RENZOKU_NOHIT)==0)){
			if(--sp->renzoku_count){
				sp->loop_flag=1;
				ST_ServerLoopInit(bw,sp);
				//技エフェクトを再度出すようにする
				sp->server_status_flag&=SERVER_STATUS_FLAG_NO_WAZA_EFFECT_OFF;
				//ループする時にチェックするWazaOutCheckをビットで指定
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
 *	気絶エフェクト
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
 *	複数体当たる技のチェック
 *
 * @param
 */
//============================================================================================
static	void	ServerLoopCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//マジックコートによって、AttackとDefenceが入れ替わっていたら元に戻す
	if(sp->server_status_flag2&SERVER_STATUS_FLAG2_MAGIC_CORT_A_D){
		sp->server_status_flag2&=SERVER_STATUS_FLAG2_MAGIC_CORT_A_D_OFF;
		sp->defence_client=sp->attack_client;
		sp->attack_client=sp->magic_cort_client;
	}

#if B1370_060815_FIX
	//オウム返しワークへの格納（複数体当たる技用の格納なので、移動は厳禁）
	ServerOumugaeshiCheck(bw,sp);
#endif B1370_060815_FIX

//	if((WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_attackrange)==RANGE_DOUBLE)&&
	if((sp->AIWT.wtd[sp->waza_no_now].attackrange==RANGE_DOUBLE)&&
		   ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_DOUBLE_CHECK)==0)&&
			(sp->client_loop<BattleWorkClientSetMaxGet(bw))){
		//ループする時にチェックするWazaOutCheckをビットで指定
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
		//ループする時にチェックするWazaOutCheckをビットで指定
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
 *	じばくによる気絶エフェクト
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
 *	技がヒットした後のチェック
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
 *	経験値取得エフェクト
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
 *	技ナンバーをバッファに格納
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
	//特性ノーマルスキンは、タイプをノーマルに
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

	//Attackの代入
	eqp_a=ST_ServerSoubiEqpGet(sp,sp->attack_client);
	if((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)||
	   (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
		//装備アイテム「こだわりはちまき」は、技の発動でワークへ代入
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

	//1ターン前に繰り出していた技として格納（フラグが立っている時は格納しない
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
		//Defenceの代入
		eqp_d=ST_ServerSoubiEqpGet(sp,sp->defence_client);
		if((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)||
		   (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
			//装備アイテム「こだわりはちまき」は、技の発動でワークへ代入
			if((eqp_d!=SOUBI_ONAZIWAZAONLY)&&
			   (eqp_d!=SOUBI_ONAZIWAZAONLYSUBAYASAUP)&&
			   (eqp_d!=SOUBI_ONAZIAWZAONLYTOKUSYUUP)){
				sp->psp[sp->defence_client].wkw.kodawari_wazano=0;
			}
		}

		//1ターン前に繰り出していた技として格納（フラグが立っている時は格納しない
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
				//テクスチャー２ワークは、格納するレンジを限定する
				switch(sp->AIWT.wtd[sp->waza_no_now].attackrange){
				case RANGE_MINE:		//自分選択
				case RANGE_MINE_DOUBLE:	//自分２体選択
				case RANGE_FIELD:		//場にかかる
				case RANGE_MAKIBISHI:	//まきびし専用
				case RANGE_TEDASUKE:	//てだすけ専用
				case RANGE_TUBOWOTUKU:	//つぼをつく専用
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

	//オウム返しワークへの格納（技が外れた場合用の格納なので、移動は厳禁）
	ServerOumugaeshiCheck(bw,sp);

	//メトロノームチェック
	ST_ServerMetronomeAfterCheck(bw,sp);

	sp->server_seq_no=SERVER_WAZA_END_NO;
}

//============================================================================================
/**
 *	技シーケンス終了
 *
 * @param
 */
//============================================================================================
static	void	ServerWazaEnd(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;
	u32	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	//サファリゾーン、ポケパークでは、以下の処理は必要なし
	if((fight_type&(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK))==0){
		//再度リカバー系の特性のチェックをする
		if(ST_ServerTokuseiStatusRecoverCheck(bw,sp,sp->attack_client,0)==TRUE){
			return;
		}
		//攻撃対象がいない場合もあるのでチェックする
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

	//トリックルーム発動時は、最初からにする
	if(sp->ostf[sp->attack_client].trickroom_flag){
		ST_ServerTrickRoomAct(bw,sp);
		//技効果発動のための素早さ計算
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
 *	ポケモンいれかえ後シーケンス
 *
 * @param
 */
//============================================================================================
static	void	ServerPokeReshuffleAfter(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;

	//状態異常直し系をチェック
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
 *	戦闘勝敗シーケンス
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
 *	サーバキューをチェックして終了を待つ
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
 *	戦闘終了
 *
 * @param
 */
//============================================================================================
static	void	ServerFightEnd(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	POKEPARTY	*ppt;
	u32	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	//ポケルス感染チェック
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
 *	戦闘終了（通信対戦時の待ち）
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
 *	ServerQueCheckに移行するためのパラメータセット
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	next_seq	ServerQueCheck後に移行するシーケンスナンバー
 *	@param[in]	wait		ServerQueCheck後のWAIT
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
 *	入れ替えチェック
 *
 * @param
 */
//============================================================================================
static	const int	PosTable[]={
	0,0,0,0,3,3,
};

//============================================================================================
/**
 *	入れ替えチェック
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
			//ダブルノックダウンなら1体目だけをチェック
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
						sp->no_reshuffle_client|=No2Bit(client_no);	///<入れ替えるポケモンを持たないClientNoをビットで格納
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
						sp->no_reshuffle_client|=No2Bit(client_no);	///<入れ替えるポケモンを持たないClientNoをビットで格納
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
			//ダブルノックダウンなら1体目だけをチェック
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
//技の終わりで全滅チェックをしなくなったので、ここでのセットでは無意味になった（気絶した瞬間にセットに変更）
#if 0
					//気絶しているクライアントのclient_act_workにWAZA_ENDをセット
					//技シーケンスが動作しないようにする
					sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;
#endif
					if(hp_total==0){
						sp->no_reshuffle_client|=No2Bit(client_no);	///<入れ替えるポケモンを持たないClientNoをビットで格納
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
	
//技の終わりで全滅チェックをしなくなったので、ここでのセットでは無意味になった（気絶した瞬間にセットに変更）
					//気絶しているクライアントのclient_act_workにWAZA_ENDをセット
					//技シーケンスが動作しないようにする
//					sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;
	
					if(hp==0){
						sp->no_reshuffle_client|=No2Bit(client_no);	///<入れ替えるポケモンを持たないClientNoをビットで格納
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
		//対戦ルールによって入れ替え方式を変える
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
 *	全滅チェック
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
		//AIマルチ戦では、自分側だけで勝敗を決める
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
 *	攻撃対象選択チェック
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerDirSelectCheck(SERVER_PARAM *sp,u8 client_no,u32 fight_type,int *range,int waza_pos,u32 *dir)
{
//	*range=WT_WazaDataParaGet(sp->psp[client_no].waza[waza_pos],ID_WTD_attackrange);
	//のろいの時は、繰り出すClientをみて、rangeを変化
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
 *	技シーケンスで削除要求のあったフラグをすべて削除
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
		//condition2フラグ
		sp->psp[client_no].condition2&=(sp->condition2_off_req[client_no]^0xffffffff);
		sp->condition2_off_req[client_no]=0;
		//wazakoukaフラグ(非表示を表示に）
//		if((sp->psp[client_no].waza_kouka&WAZAKOUKA_KIE)==0){
//			SCIO_PokemonVanishOnOff(bw,client_no,SW_VANISH_OFF);
//		}
	}

	sp->waza_no_hit[sp->attack_client]=0;
	sp->waza_no_texture2[sp->attack_client]=0;
}

//============================================================================================
/**
 *	気絶チェック
 *
 * @param[in]	sp			サーバパラメータ構造体
 * @param[in]	next_seq	次に移動するシーケンスナンバー
 * @param[in]	no_set_seq	気絶していなかったときにセットするシーケンスナンバー
 * @param[in]	flag		みちづれチェックの有無
 *
 * @retval	FALSE:気絶なし　TRUE:気絶あり
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
		//気絶しているクライアントのclient_act_workにWAZA_ENDをセット
		//技シーケンスが動作しないようにする
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
 *	経験値取得チェック
 *
 * @param[in]	sp			サーバパラメータ構造体
 * @param[in]	next_seq	次に移動するシーケンスナンバー
 * @param[in]	no_set_seq	取得しないときにセットするシーケンスナンバー
 *
 * @retval	FALSE:取得なし　TRUE:取得あり
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
 *	オウムがえし用ワークへの代入チェック
 *
 * @param[in]	bw			戦闘システムパラメータ構造体
 * @param[in]	sp			サーバパラメータ構造体
 */
//============================================================================================
static	void	ServerOumugaeshiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;
	int	wazatype;
	u8	eqp_d;

	//特性ノーマルスキンは、タイプをノーマルに
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

	//オウムフラグが立っているか
	if((flag&FLAG_OUMUGAESI)&&
	//セットしないフラグは立っていないか？
	  ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0)&&
	//攻撃対象は正常か？
	  (sp->defence_client!=NONE_CLIENT_NO)&&
	//AttackMessageを見たか
	  (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
		sp->waza_no_oumu[sp->defence_client]=sp->waza_no_temp;	//直前に出していたバッファに代入
		sp->waza_no_oumu_hit[sp->defence_client][sp->attack_client]=
			sp->waza_no_temp;	//2vs2のときに受けた側のバッファに代入
	}

	if(sp->defence_client!=NONE_CLIENT_NO){
		//Defenceの代入
		eqp_d=ST_ServerSoubiEqpGet(sp,sp->defence_client);
		if((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)||
		   (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
			//装備アイテム「こだわりはちまき」は、技の発動でワークへ代入
			if((eqp_d!=SOUBI_ONAZIWAZAONLY)&&
			   (eqp_d!=SOUBI_ONAZIWAZAONLYSUBAYASAUP)&&
			   (eqp_d!=SOUBI_ONAZIAWZAONLYTOKUSYUUP)){
				sp->psp[sp->defence_client].wkw.kodawari_wazano=0;
			}
		}

		//1ターン前に繰り出していた技として格納（フラグが立っている時は格納しない
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
				//テクスチャー２ワークは、格納するレンジを限定する
				switch(sp->AIWT.wtd[sp->waza_no_now].attackrange){
				case RANGE_MINE:		//自分選択
				case RANGE_MINE_DOUBLE:	//自分２体選択
				case RANGE_FIELD:		//場にかかる
				case RANGE_MAKIBISHI:	//まきびし専用
				case RANGE_TEDASUKE:	//てだすけ専用
				case RANGE_TUBOWOTUKU:	//つぼをつく専用
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
 *	オウムがえし用ワークへの代入チェック
 *
 * @param[in]	bw			戦闘システムパラメータ構造体
 * @param[in]	sp			サーバパラメータ構造体
 */
//============================================================================================
static	void	ServerOumugaeshiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;

//	flag=WT_WazaDataParaGet(sp->waza_no_temp,ID_WTD_flag);
	flag=sp->AIWT.wtd[sp->waza_no_temp].flag;

	//オウムフラグが立っているか
	if((flag&FLAG_OUMUGAESI)&&
	//セットしないフラグは立っていないか？
	  ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZANO_SET)==0)&&
	//攻撃対象は正常か？
	  (sp->defence_client!=NONE_CLIENT_NO)&&
	//AttackMessageを見たか
	  (sp->server_status_flag2&SERVER_STATUS_FLAG2_ATTACK_MSG)){
		sp->waza_no_oumu[sp->defence_client]=sp->waza_no_temp;	//直前に出していたバッファに代入
		sp->waza_no_oumu_hit[sp->defence_client][sp->attack_client]=
			sp->waza_no_temp;	//2vs2のときに受けた側のバッファに代入
	}
}
#endif //B1370_060815_FIX

//============================================================================================
/**
 *	急所にあたったメッセージ表示
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
 *	ばつぐんやいまひとつなどメッセージ表示
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerWazaStatusMessage(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret;

	ret=FALSE;

	if(sp->waza_status_flag){
		//連続攻撃の場合は、最後にメッセージを出す
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
 *	いかりがヒットした後のチェックシーケンスナンバー
 */
//============================================================================================
enum{
	SIC_IKARI_ATTACK_CHECK=0,
	SIC_IKARI_DEFENCE_CHECK,
	SIC_END
};

//============================================================================================
/**
 *	技がヒットした後のいかりチェック
 *
 * @param
 */
//============================================================================================
static	BOOL	ServerIkariCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret;
	
	ret=FALSE;

	//攻撃対象がいなければ、チェックなし
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
 *	技がヒットした後のおうじゃのしるしチェック
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
 *	消えているポケモンをどうするかチェック
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
 *	技がヒットした後のチェックシーケンスナンバー
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
 *	技がヒットした後のチェック
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

	//気絶チェック
	if(ServerKizetsuCheck(sp,sp->server_seq_no,sp->server_seq_no,SKC_MICHIDURE_OFF)==TRUE){
		return TRUE;
	}
	//経験値取得チェック
//	if(ServerGetExpCheck(sp,sp->server_seq_no,sp->server_seq_no)==TRUE){
//		return TRUE;
//	}
	//全滅チェック
//	if(ServerZenmetsuCheck(bw,sp)==TRUE){
//		return TRUE;
//	}

	do{
		switch(sp->swhac_seq_no){
		case SWHAC_IKARI_ATTACK_CHECK:
			//いかり状態で、いかりを出していない時は、いかり状態解除
			if((sp->psp[sp->attack_client].condition2&CONDITION2_IKARI)&&(sp->waza_no_now!=WAZANO_IKARI)){
				sp->psp[sp->attack_client].condition2&=CONDITION2_IKARI_OFF;
			}
			sp->swhac_seq_no++;
			break;
		case SWHAC_SOUBI_HPKAIHUKUDAMEEZIRITU:
			if(sp->defence_client!=NONE_CLIENT_NO){
				if((eqp==SOUBI_HPKAIHUKUDAMEEZIRITU)&&
				   //とんぼがえり入れ替えでは、発動なし
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
				//特性マジックガードはダメージなし
			   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
			   //とんぼがえり入れ替えでは、発動なし
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


