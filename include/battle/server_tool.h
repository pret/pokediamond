
//============================================================================================
/**
 * @file	server_tool.h
 * @bfief	戦闘サーバ用ツールプログラム
 * @author	HisashiSogabe
 * @date	05.05.26
 */
//============================================================================================

#ifndef __SERVER_TOOL_H_
#define __SERVER_TOOL_H_

#include "battle/scio.h"
#include "poketool/poke_tool.h"

//ST_ServerHitCountCheck用フラグ
#define	SHCC_NORMAL		(0)		//全体
#define	SHCC_SIDE		(1)		//側

//ST_ServerListRowChange用フラグ
#define	FB_FORWARD		(0)		//前衛
#define	FB_BACKWARD		(1)		//後衛

//ST_ServerSoubiAtkGet用フラグ
#define	ATK_CHECK_NORMAL	(0)	//チェックあり
#define	ATK_CHECK_NONE		(1)	//チェックなし
#define	ATK_CHECK_SHUTOUT	(2)	//シャットアウトだけチェックあり


//ST_ServerTokuseiCheck用フラグ
enum{
	STC_HAVE_MINE_SIDE=0,		//自分側が持っているかチェック
	STC_HAVE_MINE_SIDE_HP,		//自分側が持っているかチェック（HP0は無効）
	STC_HAVE_ENEMY_SIDE,		//相手側が持っているかチェック
	STC_HAVE_ENEMY_SIDE_HP,		//相手側が持っているかチェック（HP0は無効）
	STC_HAVE_ENEMY_SIDE_RET,	//相手側が持っているかチェックして持っていたClientNoを返す
	STC_HAVE_ALL,				//自分も含め持っているかチェック
	STC_HAVE_ALL_NOMINE,		//自分以外のポケモンが持っているかチェック
	STC_HAVE_ALL_NOMINE_RET,	//自分以外のポケモンが持っているかチェックして持っていたClientNoを返す
	STC_HAVE_ALL_HP,			//自分も含め持っているかチェック（HP0は無効）
	STC_HAVE_ALL_NOMINE_HP		//自分以外のポケモンが持っているかチェック（HP0は無効）
};


extern	void	ST_PokemonParamGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no);
extern	void	ST_PokemonParamReload(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no);
extern	void	ST_ServerSequenceLoad(SERVER_PARAM *server_param,int kind,int index);
extern	void	ST_ServerSequenceLoadGosub(SERVER_PARAM *sp,int	kind,int index);
extern	BOOL	ST_ServerSequencePushCheck(SERVER_PARAM *sp);
extern	void	ST_ServerQueSet(SERVER_PARAM *server_param,int id,int client_no,int index);
extern	void	ST_ServerQueReset(SERVER_PARAM *server_param,int id,int client_no,int index);
extern	BOOL	ST_ServerQueCheck(SERVER_PARAM *server_param);
extern	void	ST_ServerQueTimeOutCheck(SERVER_PARAM *sp);
extern	void	ST_ServerBufferClear(SERVER_PARAM *server_param,int client_no);
extern	int		ST_ServerPokemonServerParamGet(SERVER_PARAM *sp,int client,int id,void *data);
extern	void	ST_ServerPokemonServerParamPut(SERVER_PARAM *sp,int client,int id,const void *buf);
extern	void	ST_ServerPokemonServerParamAdd(SERVER_PARAM *sp,int client,int id,int value);
extern	void	ST_PokemonServerParamAdd(POKEMON_SERVER_PARAM *psp,int id,int value);
extern	u8		ST_ServerAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,int cl1,int cl2,int flag);
extern	void	ST_ServerGetExpRightFlagClear(SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerGetExpRightFlagSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerGetExpRightFlagReset(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerAddStatusDirectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
extern	BOOL	ST_ServerAddStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
extern	int		ST_ServerDefenceClientSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 waza_no,int flag,int set_range);
extern	void	ST_ServerDefenceClientTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 waza_no);
extern	BOOL	ST_ServerDefenceClientTokuseiAct(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	ST_PSPtoPPCopy(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerKeepOn(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerKeepOff(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	int		ST_ServerConditionNoGet(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerTrainerMessageCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	ST_ServerWorkInit(SERVER_PARAM *sp);
extern	void	ST_ServerCounterWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	ST_ServerReshuffleWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerKizetsuWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerOneTurnFlagInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	int		ST_ServerWaruagakiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_bit,int check_bit);
extern	BOOL	ST_ServerWazaNGCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int pos,MESSAGE_PARAM *mp);
extern	int		ST_ServerWazaPosGet(POKEMON_SERVER_PARAM *psp,u16 waza_no);
extern	int		ST_ServerTypeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int waza_no,int waza_type,int attack_client,int defence_client,int damage,u32 *flag);
extern	void	ST_AITypeCheck(SERVER_PARAM *sp,int waza_no,int waza_type,int spe_a,int spe_d,int eqp,int type1,int type2,u32 *flag);
extern	BOOL	ST_ServerWazaOutCheck(SERVER_PARAM *sp,int client_no);
extern	u8		ST_ServerHitCountCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int flag,int client_no);
extern	int		ST_ServerTagNickParaMake(SERVER_PARAM *sp,int client_no);
extern	u16		ST_ServerSelectWazaGet(SERVER_PARAM *sp,int client_no);
extern	int		ST_ServerTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int flag,int client_no,int speabi);
extern	BOOL	ST_TameWazaCheck(SERVER_PARAM *sp,int waza_no);
extern	BOOL	ST_ServerTypeCheckTableParaGet(int pos,u8 *type_w,u8 *type_p,u8 *value);
extern	int		ST_ServerTypeCheckTablePowerGet(u8 type_w,u8 type_p1,u8 type_p2);
extern	BOOL	ST_RendouWazaCheck(u16 waza_no);
extern	BOOL	ST_ServerWazaNoroiCheck(SERVER_PARAM *sp,u16 waza_no,int client_no);
extern	BOOL	ST_ServerDorobouItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerTrickItemCheck(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerHukitobasiCheck(SERVER_PARAM *sp);
extern	u8		ST_ServerTokuseiGet(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerKatayaburiTokuseiCheck(SERVER_PARAM *sp,int attack,int defence,int tokusei);
extern	BOOL	ST_ServerReshuffleCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	int		ST_ServerPartnerClientNoGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_EscapeNGCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,MESSAGE_PARAM *mp);
extern	BOOL	ST_EscapeActCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerNamakeCheck(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerSawaguCheck(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerHuuinCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
extern	BOOL	ST_ServerWazaKoukaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int waza_kouka);
extern	void	ST_ServerLoopInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	ST_ServerPSPAgiCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	BOOL	ST_ServerJuuryokuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
extern	BOOL	ST_ServerHealblockCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_no);
extern	void	ST_ServerTotteokiCountCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	int		ST_ServerWazaCountGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	int		ST_ServerDamageTokuseiCheck(SERVER_PARAM *sp,int attack,int defence);
extern	BOOL	ST_ServerPCCTokuseiCheck(SERVER_PARAM *sp,int client_no);
extern	int		ST_ServerDamageDiv(int data,int value);
extern	int		ST_ServerPokeAppearCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	int		ST_ServerDirClientGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerWazaHitTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
extern	BOOL	ST_ServerTokuseiStatusRecoverCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int act_flag);
extern	BOOL	ST_ServerTokuseiStatusRecoverReshuffleCheck(SERVER_PARAM *sp,int tokusei,int condition);
extern	BOOL	ST_ServerSinkuroCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int server_seq_no);
extern	BOOL	ST_ServerSoubiItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerSoubiItemTabenokosiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerSoubiItemConditionBadCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int *seq_no);
extern	BOOL	ST_ServerSoubiItemDamageCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	u16		ST_ServerSoubiItemNoGet(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerWazaEndCheck(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerWazaHitSoubiItemCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
extern	s32		ST_ServerSoubiEqpGet(SERVER_PARAM *sp,int client_no);
extern	s32		ST_ServerSoubiAtkGet(SERVER_PARAM *sp,int client_no,int flag);
extern	s32		ST_ServerShizennomegumiAtkGet(SERVER_PARAM *sp,int client_no);
extern	s32		ST_ServerShizennomegumiTypeGet(SERVER_PARAM *sp,int client_no);
extern	s32		ST_ServerTsuibamuEqpGet(SERVER_PARAM *sp,int client_no);
extern	s32		ST_ServerNagetsukeruEqpGet(SERVER_PARAM *sp,int client_no);
extern	s32		ST_ServerNagetsukeruAtkGet(SERVER_PARAM *sp,int client_no);
extern	int		ST_ServerPokemonSelectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerTsuibamuCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerNagetsukeruCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerMetronomeBeforeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	ST_ServerMetronomeAfterCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern int		ST_ServerPokeVoiceEffNoGet(SERVER_PARAM *sp,int client_no, int client_type, int encount);
extern	BOOL	ST_ServerCommandSelectCheck(SERVER_PARAM *sp,int client_no);
extern	void	ST_ServerPokemonGetParamSet(BATTLE_WORK *bw,SERVER_PARAM *sp,POKEMON_PARAM *pp);
extern	u8		ST_ServerBufferResGet(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerMigawariCheck(SERVER_PARAM *sp,int client_no);
extern	BOOL	ST_ServerPokeOneSelfCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	BOOL	ST_ServerPokeOneSelfCheckActPP(BATTLE_WORK *bw,POKEMON_PARAM *pp);
extern	BOOL	ST_ServerTenkiyaCheck(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	ST_ServerListRowInit(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	ST_ServerListRowChange(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int sel_mons_no);
extern	int		ST_WazaDamageCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,
								  int wazano,u32 side_cond,u32 field_cond,u16 pow,u8 type,u8 attack,u8 defence,u8 critical);
extern	int		ST_DamageLossCalc(SERVER_PARAM *sp,int damage);
extern	int		ST_CriticalCheck(SERVER_PARAM *sp,int attack,int defence,int critical_count,u32 side_condition);
extern	BOOL	ST_MonomaneNGCheck(u16 waza_no);
extern	BOOL	ST_YubiwohuruNGCheck(u16 waza_no);
extern	BOOL	ST_OumuEncoreNGCheck(SERVER_PARAM *sp,u16 waza_no);
extern	BOOL	ST_SakidoriNGCheck(SERVER_PARAM *sp,u16 waza_no);
extern	s32		ST_ItemParamGet(SERVER_PARAM *sp,u16 item_no,u16 param);
extern	int		ST_ServerDir2ClientNoGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int dir);
extern	void	ST_ServerTrickRoomAct(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	BOOL	ST_ServerStatusEffectMigawariCheck(SERVER_PARAM *sp,int client_no,int status);
extern	BOOL	ST_ServerWazaHitSoubiItemCheckTonbogaeri(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no);
extern	void	ST_ServerPressurePPDecCheck(SERVER_PARAM *sp,int attack,int defence);

extern	int		ST_ServerParamDataGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no);

extern	void	ST_ServerOSTFStatusFlagSet(SERVER_PARAM *sp,int client_no,u32 value);
extern	void	ST_ServerParamDataPut(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no,int data);

#endif __SERVER_TOOL_H_
