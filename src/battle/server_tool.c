
//============================================================================================
/**
 * @file	server_tool.c
 * @bfief	戦闘サーバ用ツールプログラム
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
//	プロトタイプ宣言
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

//パラメータゲット系
int		ST_ServerParamDataGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no);

//パラメータセット系
void	ST_ServerOSTFStatusFlagSet(SERVER_PARAM *sp,int client_no,u32 value);
void	ST_ServerParamDataPut(BATTLE_WORK *bw,SERVER_PARAM *sp,int id,int client_no,int data);

//外部公開しない系
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
 *	PokemonParamをPokemonServerParamに読み込む
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	読み込むclient_no
 * @param[in]	sel_mons_no	読み込むPokemonParamの先頭からの位置
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

	//バトンタッチ効果の時は、初期化しない
	if((sp->server_status_flag&SERVER_STATUS_FLAG_BATON_TOUCH)==0){
		for(i=0;i<COND_MAX;i++){
			sp->psp[client_no].abiritycnt[i]=COND_NUM_DEFAULT;
		}
	}

	sp->psp[client_no].appear_check_flag=0;			//登場時天候系特性チェックをしたかどうか
	sp->psp[client_no].ikaku_flag=0;				//登場時いかくチェックしたかどうか
	sp->psp[client_no].trace_flag=0;				//登場時トレースチェックしたかどうか
	sp->psp[client_no].download_flag=0;				//登場時ダウンロードチェック
	sp->psp[client_no].kikenyochi_flag=0;			//登場時きけんよちチェック
	sp->psp[client_no].yochimu_flag=0;				//登場時よちむチェック
	sp->psp[client_no].slow_start_flag=0;			//登場時スロースタートチェック
	sp->psp[client_no].slow_start_end_flag=0;		//スロースタート終了チェック
	sp->psp[client_no].omitooshi_flag=0;			//登場時おみとおしチェック
	sp->psp[client_no].katayaburi_flag=0;			//登場時かたやぶりチェック
	sp->psp[client_no].pressure_flag=0;				//登場時プレッシャーチェック

	sp->psp[client_no].type1=			PokeParaGet(pp,ID_PARA_type1,			0);
	sp->psp[client_no].type2=			PokeParaGet(pp,ID_PARA_type2,			0);

	sp->psp[client_no].sex=				PokeSexGet(pp);
	sp->psp[client_no].rare=			PokeRareGet(pp);

	sp->psp[client_no].form_no=			PokeParaGet(pp,ID_PARA_form_no,			0);

	//サファリ、ポケパークなど、登場時に発動する特性を抑制するために0をセット
	//サファリ、ポケパークなど、状態異常のチェックを抑制するために0をセット
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

	//図鑑の高さ重さ情報ワークを確保
	zhgp=ZKN_HEIGHTGRAM_Alloc(HEAPID_BATTLE);
	//図鑑の高さ重さ情報をロード
	ZKN_HEIGHTGRAM_Load(zhgp,ZKN_HEIGHT_GRAM_TYPE_MAN,HEAPID_BATTLE);

	sp->psp[client_no].weight=ZKN_HEIGHTGRAM_GetGram(zhgp,sp->psp[client_no].monsno);

	//図鑑の高さ重さ情報を破棄
	ZKN_HEIGHTGRAM_Release(zhgp);
	//図鑑の高さ重さ情報ワークを開放
	ZKN_HEIGHTGRAM_Free(zhgp);

	PokeParaGet(pp,ID_PARA_nickname,&sp->psp[client_no].nickname[0]);
	PokeParaGet(pp,ID_PARA_oyaname,&sp->psp[client_no].oyaname[0]);

	sp->psp[client_no].hit_count=0;
	sp->psp[client_no].message_flag=0;

	//はたきおとされている時は、アイテムを持っていないことにする
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
 *	PokemonParamをPokemonServerParamに読み込む（レベルアップ時のリロード）
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	読み込むclient_no
 * @param[in]	sel_mons_no	読み込むPokemonParamの先頭からの位置
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

	//へんしんしているポケモンは以下のリロードはしない
	if((sp->psp[client_no].condition2&CONDITION2_HENSHIN)==0){
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			//ものまねしている技のリロードはしない
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
 *	シーケンスデータを読み込む
 *
 * @param[in]	sp		サーバ用パラメータワーク構造体
 * @param[in]	kind	読み込むアーカイブファイルの種類
 * @param[in]	index	読み込むデータのインデックス
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
 *	シーケンスデータを読み込む（サブルーチンジャンプ対応）
 *
 * @param[in]	sp		サーバ用パラメータワーク構造体
 * @param[in]	kind	読み込むアーカイブファイルの種類
 * @param[in]	index	読み込むデータのインデックス
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
 *	サブルーチンジャンプがあったかチェック
 *
 * @param[in]	sp		サーバ用パラメータワーク構造体
 *
 * @retval	TRUE:ジャンプなし　FALSE：ジャンプ前のアドレスにもどして、シーケンス続行
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
 *	サーバ命令キューにパラメータをセット
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	id			通信時の通信ID
 * @param[in]	client_no	サーバが命令をセットしたクライアントナンバー
 * @param[in]	index		命令コードのインデックス
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
	//サーバキューがあふれてはまずいので、ASSERTを出す
	GF_ASSERT_MSG(i<SERVER_QUE_MAX,"ServerQueSet:ServerQue Overflow!\n");
}

//============================================================================================
/**
 *	サーバ命令キューのリセット
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	id			通信時の通信ID
 * @param[in]	client_no	リセットしたいクライアントナンバー
 * @param[in]	index		リセットする命令コードのインデックス
 */
//============================================================================================
void	ST_ServerQueReset(SERVER_PARAM *sp,int id,int client_no,int index)
{
	int	i;

	//indexが０はありえないので、ASSERTを出す
	GF_ASSERT_MSG(index!=0,"ServerQueSet:index == 0\n");

	for(i=0;i<SERVER_QUE_MAX;i++){
		if(sp->ServerQue[id][client_no][i]==index){
			sp->ServerQue[id][client_no][i]=0;
			break;
		}
	}
	//サーバキューに対象がない状態でこの関数が呼ばれるのはまずいので、ASSERTを出す
	GF_ASSERT_MSG(i<SERVER_QUE_MAX,"ServerQueSet:ServerQue NotFound code=%d!\n",index);
}

//============================================================================================
/**
 *	サーバ命令キューが空かチェックする
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 *
 * @retval	TRUE:空　FALSE:空ではない
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
	//タイムアウトカウントをクリア
	if(data==0){
		sp->server_que_time_out=0;
	}
	return (data==0);
}

//============================================================================================
/**
 *	サーバ命令キュータイムアウトチェック
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 */
//============================================================================================
void	ST_ServerQueTimeOutCheck(SERVER_PARAM *sp)
{
	sp->server_que_time_out++;
	if(sp->server_que_time_out>SERVER_QUE_TIME_OUT){
		OS_Printf("サーバタイムアウト発生\n");
		CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
	}
}

//============================================================================================
/**
 *	server_bufferをクリアする
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	クリアするバッファのclient_no
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
 *	POKEMON_SERVER_PARAMから値を取得する
 *
 * @param[in]	sp		サーバパラメータワーク構造体
 * @param[in]	client	取得するClientNo
 * @param[in]	id		取得する値のインデックス
 * @param[in]	data	取得する値を格納するポインタ（intでは足りない文字列など）
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
		//特性マルチタイプは、装備道具によってタイプが変わる
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
		GF_ASSERT_MSG((0),"存在しないPSPパラメータです\n");
		break;
	}

	return 0;
}

//============================================================================================
/**
 *	POKEMON_SERVER_PARAMに値を格納する
 *
 * @param[in]	sp		サーバパラメータワーク構造体
 * @param[in]	client	格納するClientNo
 * @param[in]	id		格納する値のインデックス
 * @param[in]	data	格納する値へのポインタ
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
		GF_ASSERT_MSG((0),"Putできません\n");
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
		GF_ASSERT_MSG((0),"存在しないPSPパラメータです\n");
		break;
	}
}

//============================================================================================
/**
 *	POKEMON_SERVER_PARAMに値を加算する
 *
 * @param[in]	sp		サーバパラメータワーク構造体
 * @param[in]	client	加算するClientNo
 * @param[in]	id		加算される値のインデックス
 * @param[in]	value	加算する値
 */
//============================================================================================
void	ST_ServerPokemonServerParamAdd(SERVER_PARAM *sp,int client,int id,int value)
{
	ST_PokemonServerParamAdd(&sp->psp[client],id,value);
}

//============================================================================================
/**
 *	POKEMON_SERVER_PARAMに値を加算する
 *
 * @param[in]	psp		サーバ用ポケモンパラメータワーク構造体
 * @param[in]	id		加算する値のインデックス
 * @param[in]	value	加算する値へのポインタ
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
		GF_ASSERT_MSG((0),"存在しないPSPパラメータです\n");
		break;
	}
}

//============================================================================================
/**
 *	素早さを半減する装備効果テーブル
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
 *	ポケモンの素早さ計算
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	cl1			チェックするClientNoの1
 * @param[in]	cl2			チェックするClientNoの2
 * @param[in]	flag		技の先制プライオリティの有効(0)／無効(1)
 *
 * @retval	0:ソートの必要なし　1:ソートの必要あり　2:ソートの必要あり（素早さが同じだったので、ランダムで決定された）
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

	//HP0の奴は無条件に遅くする
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

	//特性たんじゅんを持っているときは、すばやさ上昇を倍
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

	//特殊能力のうてんきのポケモンが戦闘に出ているときはチェックをしない
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//特殊能力すいすいは、雨のとき素早さが倍
		//特殊能力ようりょくそは、晴れのとき素早さが倍
		if(((speabi1==TOKUSYU_SUISUI)&&(sp->field_condition&FIELD_CONDITION_AME_ALL))||
		   ((speabi1==TOKUSYU_YOURYOKUSO)&&(sp->field_condition&FIELD_CONDITION_HARE_ALL))){
			agi1*=2;
		}
		//特殊能力すいすいは、雨のとき素早さが倍
		//特殊能力ようりょくそは、晴れのとき素早さが倍
		if(((speabi2==TOKUSYU_SUISUI)&&(sp->field_condition&FIELD_CONDITION_AME_ALL))||
		   ((speabi2==TOKUSYU_YOURYOKUSO)&&(sp->field_condition&FIELD_CONDITION_HARE_ALL))){
			agi2*=2;
		}
	}

	//アイテムで努力値２倍の効果、すばやさDOWNを装備すると素早さを1/2にする
	for(i=0;i<NELEMS(ItemEqpAgiHalfTable);i++){
		if(ST_ItemParamGet(sp,sp->psp[cl1].item,ITEM_PRM_EQUIP)==ItemEqpAgiHalfTable[i]){
			agi1/=2;
			break;
		}
	}

	//アイテムでこだわり系を装備すると素早さを1.5倍にする
	if(eqp1==SOUBI_ONAZIWAZAONLYSUBAYASAUP){
		agi1=agi1*15/10;
	}

	//アイテムでメタモンが持つと素早さを2倍にする
	if((eqp1==SOUBI_METAMONSUBAYASAUP)&&(sp->psp[cl1].monsno==MONSNO_METAMON)){
		agi1*=2;
	}

	//特性はやあしは、状態異常で素早さを1.5倍にする
	if((speabi1==TOKUSYU_HAYAASI)&&(sp->psp[cl1].condition&CONDITION_BAD)){
		agi1=agi1*15/10;
	}
	else{
		//まひの時は、素早さを1/4にする
		if(sp->psp[cl1].condition&CONDITION_MAHI){
			agi1/=4;
		}
	}

	//特性スロースタートは、場にでてから5ターン以内は素早さを半分にする
	if((speabi1==TOKUSYU_SUROOSUTAATO)&&
	  ((sp->total_turn-sp->psp[cl1].wkw.slow_start_count)<5)){
		agi1/=2;
	}

	//特性かるわざは、アイテムをつかってしまうと素早さが倍になる
	if((speabi1==TOKUSYU_KARUWAZA)&&
	   (sp->psp[cl1].wkw.karuwaza_flag)&&
	   (sp->psp[cl1].item==0)){
		agi1*=2;
	}

	//技効果おいかぜを受けている時は、素早さを2倍に
	if(sp->side_condition[BattleWorkMineEnemyCheck(bw,cl1)]&SIDE_CONDITION_OIKAZE){
		agi1*=2;
	}

	//アイテムで先制攻撃の効果を装備すると先制攻撃にする
	if(eqp1==SOUBI_SENSEIKOUGEKI){
#ifdef PM_DEBUG
		if(((sp->agi_rand[cl1]%(100/atk1))==0)||sp->dbp.debug_flag&DEBUG_FLAG_SOUBI){
#else
		if((sp->agi_rand[cl1]%(100/atk1))==0){
#endif
			sensei1=1;
			//技のプライオリティを見ない時は、効果エフェクトの発動はなし
			if(flag==0){
				sp->psp[cl1].wkw.sensei_flag=1;
			}
		}
	}
	
	//装備効果で先制攻撃にする
	if(sp->psp[cl1].wkw.once_agi_up){
		sensei1=1;
	}

	//アイテムで後攻攻撃の効果を装備すると後攻攻撃にする
	if(eqp1==SOUBI_KOUKOUNINARU){
		koukou1=1;
	}

	//アイテムで努力値２倍の効果、すばやさDOWNを装備すると素早さを1/2にする
	for(i=0;i<NELEMS(ItemEqpAgiHalfTable);i++){
		if(ST_ItemParamGet(sp,sp->psp[cl2].item,ITEM_PRM_EQUIP)==ItemEqpAgiHalfTable[i]){
			agi2/=2;
			break;
		}
	}

	//アイテムでこだわり系を装備すると素早さを1.5倍にする
	if(eqp2==SOUBI_ONAZIWAZAONLYSUBAYASAUP){
		agi2=agi2*15/10;
	}

	//アイテムでメタモンが持つと素早さを2倍にする
	if((eqp2==SOUBI_METAMONSUBAYASAUP)&&(sp->psp[cl2].monsno==MONSNO_METAMON)){
		agi2*=2;
	}

	//特性はやあしは、状態異常で素早さを1.5倍にする
	if((speabi2==TOKUSYU_HAYAASI)&&(sp->psp[cl2].condition&CONDITION_BAD)){
		agi2=agi2*15/10;
	}
	else{
		//まひの時は、素早さを1/4にする
		if(sp->psp[cl2].condition&CONDITION_MAHI){
			agi2/=4;
		}
	}

	//特性スロースタートは、場にでてから5ターン以内は素早さを半分にする
	if((speabi2==TOKUSYU_SUROOSUTAATO)&&
	  ((sp->total_turn-sp->psp[cl2].wkw.slow_start_count)<5)){
		agi2/=2;
	}

	//特性かるわざは、アイテムをつかってしまうと素早さが倍になる
	if((speabi2==TOKUSYU_KARUWAZA)&&
	   (sp->psp[cl2].wkw.karuwaza_flag)&&
	   (sp->psp[cl2].item==0)){
		agi2*=2;
	}

	//技効果おいかぜを受けている時は、素早さを2倍に
	if(sp->side_condition[BattleWorkMineEnemyCheck(bw,cl2)]&SIDE_CONDITION_OIKAZE){
		agi2*=2;
	}

	//アイテムで先制攻撃の効果を装備すると先制攻撃にする
	if(eqp2==SOUBI_SENSEIKOUGEKI){
#ifdef PM_DEBUG
		if(((sp->agi_rand[cl2]%(100/atk2))==0)||sp->dbp.debug_flag&DEBUG_FLAG_SOUBI){
#else
		if((sp->agi_rand[cl2]%(100/atk2))==0){
#endif
			sensei2=1;
			//技のプライオリティを見ない時は、効果エフェクトの発動はなし
			if(flag==0){
				sp->psp[cl2].wkw.sensei_flag=1;
			}
		}
	}

	//装備効果で先制攻撃にする
	if(sp->psp[cl2].wkw.once_agi_up){
		sensei2=1;
	}

	//アイテムで後攻攻撃の効果を装備すると後攻攻撃にする
	if(eqp2==SOUBI_KOUKOUNINARU){
		koukou2=1;
	}

	//純粋な素早さパラメータをワークに格納
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
		//先制プライオリティが一緒の時は、せんせいのツメ、こうこうのしっぽ、あとだし、トリックルームの順で見る
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
 *	経験値を獲得できる権利フラグのクリア
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	クリアするクライアントナンバー
 */
//============================================================================================
void	ST_ServerGetExpRightFlagClear(SERVER_PARAM *sp,int client_no)
{
	sp->get_exp_right_flag[(client_no>>1)&1]=0;
}

//============================================================================================
/**
 *	経験値を獲得できる権利フラグのセット
 *
 * @param[in]	bw			戦闘システムワーク構造体ポインタ
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	セットするクライアントナンバー
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
 *	経験値を獲得できる権利フラグのリセット
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	リセットするクライアントナンバー
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
 *	追加効果のチェック（直接追加のみ）
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[out]	seq_no		追加効果をするためのサブシーケンスナンバー
 */
//============================================================================================
BOOL	ST_ServerAddStatusDirectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret=FALSE;

	if(sp->add_status_flag_direct&ADD_STATUS_WAZAKOUKA){
		//技効果の追加は、100%起動
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_DIRECT,sp->add_status_flag_direct);
		sp->add_status_flag_direct=0;
		//はずれで失敗にする
		if((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0){
			ret=TRUE;
		}
	}
	else if(sp->add_status_flag_direct){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_DIRECT,sp->add_status_flag_direct);
		//気絶している相手には失敗させる
		if((sp->psp[sp->tsuika_client].hp)&&
		//技効果の追加ではずれを無視する指定がない時は、はずれで失敗にする
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
 *	追加効果のチェック（直接追加以外）
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[out]	seq_no		追加効果をするためのサブシーケンスナンバー
 */
//============================================================================================
BOOL	ST_ServerAddStatusCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret=FALSE;
	u16		kakuritsu;

	//技効果の追加は、100%起動
	if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//はずれで失敗にする
		if(((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
			ret=TRUE;
		}
	}
	//技効果の追加は、100%起動
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_NOHP){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//みがわりがいる場合は、失敗にする　はずれで失敗にする
		if((ST_ServerMigawariCheck(sp,sp->tsuika_client)==FALSE)&&
		   ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
			ret=TRUE;
		}
	}
	//技効果の追加は、100%起動
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_CHECK){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//気絶している相手には失敗させる みがわりがいる場合は、失敗にする　はずれで失敗にする
		if((sp->psp[sp->tsuika_client].hp)&&
		  (ST_ServerMigawariCheck(sp,sp->tsuika_client)==FALSE)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)){
			ret=TRUE;
		}
	}
	//技効果の追加は、100%起動
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_NOHIT){
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//気絶している相手には失敗させる
		if(sp->psp[sp->tsuika_client].hp){
			ret=TRUE;
		}
	}
	//技効果の追加は、100%起動
	else if(sp->add_status_flag_indirect&ADD_STATUS_WAZAKOUKA_PROB){
		//特殊能力てんのめぐみは、確率を倍にする
		if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_TENNOMEGUMI){
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect)*2;
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect*2;
		}
		else{
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect);
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect;
		}
		//間接で確率０はありえないので、アサート
		GF_ASSERT(kakuritsu!=0);
#ifdef PM_DEBUG
		if(((gf_rand()%100)<kakuritsu)||(sp->dbp.debug_flag&DEBUG_FLAG_ADD_STATUS)){
			//追加効果起動になったら、フラグをオンにする
			sp->server_status_flag|=SERVER_STATUS_FLAG_TSUIKA;
		}
#else
		if((gf_rand()%100)<kakuritsu){
			//追加効果起動になったら、フラグをオンにする
			sp->server_status_flag|=SERVER_STATUS_FLAG_TSUIKA;
		}
#endif
		seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
		sp->add_status_flag_indirect=0;
		//気絶している相手には失敗させる
		if(sp->psp[sp->tsuika_client].hp==0){
			sp->server_status_flag&=SERVER_STATUS_FLAG_TSUIKA_OFF;
		}
		ret=TRUE;
	}
	else if(sp->add_status_flag_indirect){
		//特殊能力てんのめぐみは、確率を倍にする
		if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_TENNOMEGUMI){
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect)*2;
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect*2;
		}
		else{
//			kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect);
			kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect;
		}
		//間接で確率０はありえないので、アサート
		GF_ASSERT(kakuritsu!=0);
#ifdef PM_DEBUG
		if(((gf_rand()%100)<kakuritsu)||(sp->dbp.debug_flag&DEBUG_FLAG_ADD_STATUS)){
			seq_no[0]=ST_ServerAddStatusParamSet(sp,ADD_STATUS_INDIRECT,sp->add_status_flag_indirect);
			sp->add_status_flag_indirect=0;
			//気絶している相手には失敗させる みがわりがいる場合は、失敗にする　はずれで失敗にする
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
			//気絶している相手には失敗させる みがわりがいる場合は、失敗にする　はずれで失敗にする
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
		//気絶している相手には失敗させる
		if(sp->psp[sp->tsuika_client].hp){
			ret=TRUE;
		}
	}

	return ret;
}

//============================================================================================
/**
 * @brief	攻撃対象をセット
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	attack		攻撃側ClientNo
 * @param[in]	waza_no		繰り出そうとしている技
 * @param[in]	flag		0:DirSelectでセットした値 1:対象をランダムで選択
 * @param[in]	range		waza_noが0の時に有効なRANGE値
 *
 * @retval	セットするClientNo
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
	//ゆびをふるなどで、対象を選ばずに技が出た時の処理
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
	//ゆびをふるなどで、対象を選ばずに技が出た時の処理
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
			//特性ノーマルスキンは、技タイプをノーマルにする
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
				//このゆびとまれがいるなら、そいつを選択
				if((sp->scw[dir].konoyubitomare_flag)&&(sp->psp[sp->scw[dir].konoyubitomare_client].hp)){
					defence=sp->scw[dir].konoyubitomare_client;
				}
				//両方いるなら、ランダムで選択
				else if((sp->psp[def[0]].hp)&&(sp->psp[def[1]].hp)){
					dir=gf_rand()&1;
					defence=def[dir];
#if 0	//チェック場所移動
					//技タイプがでんきで、特性ひらいしんを持っている奴がいたら、そいつを選択
					if((wazatype==ELECTRIC_TYPE)&&
					   (ST_ServerTokuseiGet(sp,defence)!=TOKUSYU_HIRAISIN)&&
					   (ST_ServerKatayaburiTokuseiCheck(sp,attack,def[dir^1],TOKUSYU_HIRAISIN)==TRUE)){
						defence=def[dir^1];
						sp->ostf[defence].hiraisin_flag=1;
					}
					//技タイプがみずで、特性よびみずを持っている奴がいたら、そいつを選択
					if((wazatype==WATER_TYPE)&&
					   (ST_ServerTokuseiGet(sp,defence)!=TOKUSYU_YOBIMIZU)&&
					   (ST_ServerKatayaburiTokuseiCheck(sp,attack,def[dir^1],TOKUSYU_YOBIMIZU)==TRUE)){
						defence=def[dir^1];
						sp->ostf[defence].yobimizu_flag=1;
					}
#endif
				}
				//どっちかなら、いる方を選択
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
			//特性ノーマルスキンは、技タイプをノーマルにする
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

			//このゆびとまれがいるなら、そいつを選択
			if((sp->scw[dir].konoyubitomare_flag)&&(sp->psp[sp->scw[dir].konoyubitomare_client].hp)){
				defence=sp->scw[dir].konoyubitomare_client;
			}
			else{
#if 0	//チェック場所移動
				//特性かたやぶりではないときは、ひらいしんとよびみずチェックをする
				if(ST_ServerTokuseiGet(sp,attack)!=TOKUSYU_KATAYABURI){
					//技タイプがでんきで、特性ひらいしんを持っている奴がいたら、そいつを選択
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
					//技タイプがみずで、特性よびみずを持っている奴がいたら、そいつを選択
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
					//攻撃対象が気絶していたら、違うClientにスイッチ
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
				//攻撃対象が気絶していたら、違うClientにスイッチ
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
 * @brief	攻撃対象を変える特性のチェック
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	attack		攻撃側ClientNo
 * @param[in]	waza_no		繰り出そうとしている技
 *
 * @retval	TRUE:攻撃対象が変わった　FALSE:攻撃対象そのまま
 */
//============================================================================================
void	ST_ServerDefenceClientTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,u16 waza_no)
{
	int		dir;
	int		client;
	int		defence;
	int		wazatype;
	int		client_set_max;

	//対象がいなければ、チェックなし
	if(sp->defence_client==NONE_CLIENT_NO){
		return;
	}

	//特性ノーマルスキンは、技タイプがノーマルなので、チェックなし
	//特性かたやぶりは、関係なく技がでるので、チェックなし
	if((ST_ServerTokuseiGet(sp,attack)==TOKUSYU_NOOMARUSUKIN)||
	   (ST_ServerTokuseiGet(sp,attack)==TOKUSYU_KATAYABURI)){
		return;
	}
	dir=BattleWorkMineEnemyCheck(bw,attack)^1;
	//このゆびとまれを優先するので、チェックなし
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

	//技タイプがでんきで、特性ひらいしんを持っている奴がいたら、そいつを選択
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
	//技タイプがみずで、特性よびみずを持っている奴がいたら、そいつを選択
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
 * @brief	攻撃対象を変える特性の起動
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 *
 * @retval	TRUE:攻撃対象が変わった　FALSE:攻撃対象そのまま
 */
//============================================================================================
BOOL	ST_ServerDefenceClientTokuseiAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	BOOL	ret=FALSE;

	//ひらいしんチェック
	if(((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
	    (sp->ostf[sp->defence_client].hiraisin_flag)){
	    sp->ostf[sp->defence_client].hiraisin_flag=0;
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_HIRAISIN);
		sp->next_server_seq_no=sp->server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		ret=TRUE;
	}
	//よびみずチェック
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
 *	PokemonServerParamから必要なデータのみPokemonParamに書き戻す
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	読み書きするclient_no
 */
//============================================================================================
void	ST_PSPtoPPCopy(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	//アイテムを持っていないなら、AI用のワークをクリアしておく
	if(sp->psp[client_no].item==0){
		SoubiItemClear(sp,client_no);
	}
	SCIO_PSPtoPPCopy(bw,sp,client_no);
}

//============================================================================================
/**
 *	ため系のフラグを立てる
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	フラグを立てるclient_no
 */
//============================================================================================
void	ST_ServerKeepOn(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	sp->psp[client_no].condition2|=CONDITION2_KEEP;
	sp->waza_no_keep[client_no]=sp->waza_no_now;
}

//============================================================================================
/**
 *	ため系のフラグを落とす
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	フラグを落とすclient_no
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
 *	コンディションから、状態異常ナンバーを返す
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	状態異常をチェックするclient_no
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
 *	戦闘中にトレーナーが出てきて表示するメッセージチェックのシーケンスナンバー
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
 *	戦闘中にトレーナーが出てきて表示するメッセージチェック
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	sp		サーバ用パラメータワーク構造体
 */
//============================================================================================
BOOL	ST_ServerTrainerMessageCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	fight_type;
	int	tr_id;
	int seq_no;

	fight_type=BattleWorkFightTypeGet(bw);

	//通信対戦、バトルタワーは、判定しない
	if(fight_type&(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)){
		return FALSE;
	}
	//トレーナー戦ではなければ、判定しない
	if((fight_type&FIGHT_TYPE_TRAINER)==0){
		return FALSE;
	}

	//2vs2は、判定しない
	if(fight_type&FIGHT_TYPE_2vs2){
		return FALSE;
	}

	tr_id=BattleWorkTrainerIDGet(bw,CLIENT_NO_ENEMY);
	seq_no=SEQ_STMC_FIRST_DAMAGE;

	do{
		switch(seq_no){
		//戦闘中：相手ポケモンに最初のダメージを与えたとき（複数体もっていても最初の1体にだけ表示）
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
		//戦闘中：相手ポケモンのＨＰ半分以下
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
		//戦闘中：相手ポケモンが残り１匹
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
		//戦闘中：相手ポケモンが残り１匹でＨＰ半分以下
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
 *	ServerWorkの初期化
 *
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
 */
//============================================================================================
void	ST_ServerWorkInit(SERVER_PARAM *sp)
{
	int	client_no;

	sp->damage=0;							///<技によるダメージワーク
	sp->critical=1;							///<クリティカルヒットワーク
	sp->critical_count=0;					///<クリティカルチェックに使用するクリティカルの出やすさ倍率ワーク
	sp->damage_power=0;						///<技による攻撃力ワーク
	sp->damage_value=10;					///<技によるダメージ倍率ワーク
	sp->waza_type=0;						///<技タイプワーク
	sp->waza_eff_cnt=0;						///<技エフェクトカウンタ

	sp->waza_status_flag=0;					///<技が当たったことで変化するフラグ

	sp->kizetsu_client=NONE_CLIENT_NO;		///<気絶したClientNoを初期化

	sp->add_status_flag_direct=0;			///<直接追加効果フラグ
	sp->add_status_flag_indirect=0;			///<間接追加効果フラグ
	sp->add_status_flag_tokusei=0;			///<特性による追加効果フラグ
	sp->tsuika_type=ADD_STATUS_NONE;		///<追加効果の種類（直接、間接、特性）
	sp->tsuika_para=ADD_COND_NONE;			///<追加効果の種類（ねむる、まひとか）
	sp->tsuika_client=NONE_CLIENT_NO;		///<追加効果をするクライアント

	sp->renzoku_count=0;					///<連続攻撃用カウンタ
	sp->renzoku_count_temp=0;				///<連続攻撃用カウンタ（表示用）
	sp->client_loop=0;						///<複数体当たる技カウンタ
	sp->loop_flag=0;						///<ループをしたフラグ
	sp->swoam_type=0;						///<ServerWazaOutAfterMessage用タイプナンバー格納ワーク
	sp->waza_out_check_on_off=0;			///<HITCHECK有無フラグ
	sp->loop_hit_check=0;					///<ループした時のHITCHECK有無フラグ

	sp->fcc_seq_no=0;						///<FieldConditionCheck用シーケンスナンバー格納ワーク
	sp->pcc_seq_no=0;						///<PokeConditionCheck用シーケンスナンバー格納ワーク
	sp->scc_seq_no=0;						///<SideConditionCheck用シーケンスナンバー格納ワーク
	sp->sba_seq_no=0;						///<ServerBeforeAct用シーケンスナンバー格納ワーク
	sp->swhac_seq_no=0;						///<ServerWazaHitAfterCheck用シーケンスナンバー格納ワーク
	sp->swoam_seq_no=0;						///<ServerWazaOutAfterMessage用シーケンスナンバー格納ワーク
	sp->swoak_seq_no=0;						///<ServerWazaOutAfterKouka用シーケンスナンバー格納ワーク
	sp->wb_seq_no=0;						///<WazaBeforeのシーケンスナンバー
	sp->woc_seq_no=0;						///<WazaOutCheckのシーケンスナンバー
	sp->ssc_seq_no=0;						///<ServerStatusCheckのシーケンスナンバー
	sp->stc_seq_no=0;						///<ServerTokuseiCheckのシーケンスナンバー

	sp->server_status_flag&=SERVER_STATUS_FLAG_ATTACK_TURN;	//自分のターンだけ有効なフラグを初期化
	sp->server_status_flag2&=SERVER_STATUS_FLAG2_ATTACK_TURN;	//自分のターンだけ有効なフラグを初期化

	sp->magnitude=0;						///<マグニチュードの大きさ

	for(client_no=0;client_no<CLIENT_MAX;client_no++){
		MI_CpuClearFast(&sp->ostf[client_no],sizeof(ONE_SELF_TURN_FLAG));		//自分のターンのみ生存可能なワーク群
		sp->ai_reshuffle_sel_mons_no[client_no]=6;
	}

}

//============================================================================================
/**
 *	カウンタワークの初期化
 *
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
 */
//============================================================================================
void	ST_ServerCounterWorkInit(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	fight_type;
	int	i;

	for(i=0;i<CLIENT_MAX;i++){
		sp->waza_no_hit_client[i]=NONE_CLIENT_NO;
		sp->reshuffle_sel_mons_no[i]=6;
		sp->agi_rand[i]=gf_rand();	///<素早さチェックに使用する乱数値
	}

	sp->okodukai_value=1;		///<お小遣いの倍率ワーク

	sp->sakidori_total_turn=1;	///<さきどり用のトータルターンカウンタ

	fight_type=BattleWorkFightTypeGet(bw);

	if((fight_type&FIGHT_TYPE_2vs2)==0){
		sp->no_reshuffle_client|=No2Bit(CLIENT_NO_MINE2);
		sp->no_reshuffle_client|=No2Bit(CLIENT_NO_ENEMY2);
	}

	sp->safari_get_count=	SAFARI_COUNT_FLAT;		///<サファリの捕獲率カウンタ
	sp->safari_escape_count=SAFARI_COUNT_FLAT;		///<サファリの逃走率カウンタ
}

//============================================================================================
/**
 *	サーバワークの初期化（ポケモン入れ替え時）
 *
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
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
			//「くろいまなざし」、「クモのす」をかけたやつが入れ替わったら、効果を解除
			if((sp->psp[i].condition2&CONDITION2_KUROIMANAZASHI)&&(sp->psp[i].wkw.manazashi_client_no==client_no)){
				sp->psp[i].condition2&=CONDITION2_KUROIMANAZASHI_OFF;
			}
			//ロックオンをかけたやつが入れ替えかわったら、効果を解除
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
			//ロックオンをかけたやつがバトンタッチしたら、カウンタを元に戻して効果を継続
			if((sp->psp[i].waza_kouka&WAZAKOUKA_LOCKON)&&(sp->psp[i].wkw.lockon_client_no==client_no)){
				sp->psp[i].waza_kouka&=WAZAKOUKA_LOCKON_OFF;
				sp->psp[i].waza_kouka|=(LOCKON_COUNT*2);
			}
		}
	}

	for(i=0;i<client_set_max;i++){
	//「メロメロ」をかけたやつが入れ替わったら、効果を解除
		if(sp->psp[i].condition2&(No2Bit(client_no)<<MEROMERO_SHIFT)){
			sp->psp[i].condition2&=((No2Bit(client_no)<<MEROMERO_SHIFT)^0xffffffff);
		}
	//しめ系の技をかけたやつが入れ替わったら、効果を解除
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

	sp->psp[client_no].wkw.nekodamashi_count=sp->total_turn+1;		//ネコだましカウンタ初期化
	sp->psp[client_no].wkw.slow_start_count=sp->total_turn+1;		//スロースタートカウンタ初期化
	//なまけるターン（奇数・偶数）をセット
	sp->psp[client_no].wkw.namake_bit=(sp->total_turn+1)&1;

	sp->waza_no_mamoru[client_no]=0;					///<1ターン前に繰り出されていた技が発動したかどうか（まもる専用）
	sp->waza_no_hit[client_no]=0;						///<1ターン前に繰り出されていた技が受けたかどうか
	sp->waza_no_hit_client[client_no]=NONE_CLIENT_NO;	///<1ターン前に繰り出されていた技を発動したClientNo
	sp->waza_no_hit_type[client_no]=0;					///<1ターン前にヒットした技のタイプ
	sp->waza_no_old[client_no]=0;						///<1ターン前に繰り出されていた技
	sp->waza_no_oumu[client_no]=0;						///<直前に受けた技を格納（オウムがえし用）
	sp->waza_no_oumu_hit[client_no][0]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_oumu_hit[client_no][1]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_oumu_hit[client_no][2]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_oumu_hit[client_no][3]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_sketch[client_no]=0;					///<スケッチ用の技ナンバーワーク
#if GB002_060815_FIX
	sp->waza_no_texture2[client_no]=0;					///<1ターン前に繰り出されていた技が受けたかどうか（テクスチャー２専用）
	sp->waza_no_texture2_client[client_no]=0;			///<1ターン前に繰り出されていた技を発動したClient（テクスチャー２専用）
	sp->waza_no_texture2_type[client_no]=0;				///<1ターン前に繰り出されていた技のタイプ（テクスチャー２専用）
#endif //GB002_060815_FIX
#if GB003_060815_FIX
	sp->waza_no_metronome[client_no]=0;					///<メトロノーム用技ワーク
#endif //GB003_060815_FIX

#if B1371_060815_FIX
	sp->field_condition&=((No2Bit(client_no)<<FIELD_SAWAGU_SHIFT)^0xffffffff);	//さわぐフラグを落とす
#endif B1371_060815_FIX

	//パワートリックフラグが立っている場合は、攻撃と防御の値を入れ替える
	if(sp->psp[client_no].waza_kouka&WAZAKOUKA_POWER_TRICK){
		i=sp->psp[client_no].pow;
		sp->psp[client_no].pow=sp->psp[client_no].def;
		sp->psp[client_no].def=i;
	}

///<気絶時の確認をしている時に入れ替え時の不具合を発見したので
///<相手のワークをクリアするように修正（GB版と同じ仕様になります）
	for(i=0;i<client_set_max;i++){
		if((i!=client_no)&&(BattleWorkMineEnemyCheck(bw,i)!=BattleWorkMineEnemyCheck(bw,client_no))){
			sp->waza_no_oumu[i]=0;
		}
		sp->waza_no_oumu_hit[i][client_no]=0;
	}

	WazaNoStockClear(sp,client_no);		//AI用の技ナンバーストックワークをクリア
	TokusyuNoClear(sp,client_no);		//AI用の特性ナンバーワークをクリア
	SoubiItemClear(sp,client_no);		//AI用の装備アイテムナンバーワークをクリア
}

//============================================================================================
/**
 *	サーバワークの初期化（ポケモン気絶時）
 *
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
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

	//「くろいまなざし」、「クモのす」をかけたやつが気絶したら、効果を解除
	for(i=0;i<client_set_max;i++){
		if((sp->psp[i].condition2&CONDITION2_KUROIMANAZASHI)&&(sp->psp[i].wkw.manazashi_client_no==client_no)){
			sp->psp[i].condition2&=CONDITION2_KUROIMANAZASHI_OFF;
		}
	//「メロメロ」をかけたやつが入れ替わったら、効果を解除
		if(sp->psp[i].condition2&(No2Bit(client_no)<<MEROMERO_SHIFT)){
			sp->psp[i].condition2&=((No2Bit(client_no)<<MEROMERO_SHIFT)^0xffffffff);
		}
	//しめ系の技をかけたやつが入れ替わったら、効果を解除
		if((sp->psp[i].condition2&CONDITION2_SHIME)&&(sp->psp[i].wkw.shime_client_no==client_no)){
			sp->psp[i].condition2&=CONDITION2_SHIME_OFF;
		}
	}

	//そのターンにかかっていた効果系を全て初期化
	adr=(u8 *)&sp->psp[client_no].wkw;
	for(i=0;i<sizeof(WAZA_KOUKA_WORK);i++){
		adr[i]=0;
	}

	adr=(u8 *)&sp->otf[client_no];
	for(i=0;i<sizeof(ONE_TURN_FLAG);i++){
		adr[i]=0;
	}

	sp->psp[client_no].wkw.nekodamashi_count=sp->total_turn+1;		//ネコだましカウンタ初期化
	sp->psp[client_no].wkw.slow_start_count=sp->total_turn+1;		//スロースタートカウンタ初期化
	//なまけるターン（奇数・偶数）をセット
	sp->psp[client_no].wkw.namake_bit=(sp->total_turn+1)&1;

	sp->waza_no_mamoru[client_no]=0;						///<1ターン前に繰り出されていた技が発動したかどうか（まもる専用）
	sp->waza_no_hit[client_no]=0;						///<1ターン前に繰り出されていた技が受けたかどうか
	sp->waza_no_hit_client[client_no]=NONE_CLIENT_NO;	///<1ターン前に繰り出されていた技を発動したClientNo
	sp->waza_no_hit_type[client_no]=0;					///<1ターン前にヒットした技のタイプ
	sp->waza_no_old[client_no]=0;						///<1ターン前に繰り出されていた技
	sp->waza_no_oumu[client_no]=0;						///<直前に受けた技を格納（オウムがえし用）
	sp->waza_no_oumu_hit[client_no][0]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_oumu_hit[client_no][1]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_oumu_hit[client_no][2]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_oumu_hit[client_no][3]=0;				///<直前に受けた技を格納（2vs2時のオウムがえし用）
	sp->waza_no_sketch[client_no]=0;					///<スケッチ用の技ナンバーワーク
#if GB002_060815_FIX
	sp->waza_no_texture2[client_no]=0;					///<1ターン前に繰り出されていた技が受けたかどうか（テクスチャー２専用）
	sp->waza_no_texture2_client[client_no]=0;			///<1ターン前に繰り出されていた技を発動したClient（テクスチャー２専用）
	sp->waza_no_texture2_type[client_no]=0;				///<1ターン前に繰り出されていた技のタイプ（テクスチャー２専用）
#endif //GB002_060815_FIX
#if GB003_060815_FIX
	sp->waza_no_metronome[client_no]=0;					///<メトロノーム用技ワーク
#endif //GB003_060815_FIX

#if B1371_060815_FIX
	sp->field_condition&=((No2Bit(client_no)<<FIELD_SAWAGU_SHIFT)^0xffffffff);	//さわぐフラグを落とす
#endif B1371_060815_FIX

///<気絶時の確認をしている時に入れ替え時の不具合を発見したので
///<相手のワークをクリアするように修正（GB版と同じ仕様になります）
	for(i=0;i<client_set_max;i++){
		if((i!=client_no)&&(BattleWorkMineEnemyCheck(bw,i)!=BattleWorkMineEnemyCheck(bw,client_no))){
			sp->waza_no_oumu[i]=0;
		}
		sp->waza_no_oumu_hit[i][client_no]=0;
	}

	//入れ替えおいうちで気絶している場合は、いれかえフラグが立ちっぱなしなので、落とす
	sp->client_status[client_no]&=CLIENT_STATUS_POKE_RESHUFFLE_OFF;

	WazaNoStockClear(sp,client_no);		//AI用の技ナンバーストックワークをクリア
	TokusyuNoClear(sp,client_no);		//AI用の特性ナンバーワークをクリア
	SoubiItemClear(sp,client_no);		//AI用の装備アイテムナンバーワークをクリア
}

//============================================================================================
/**
 *	１ターンだけ有効なフラグを初期化
 *
 * @param[in]	sp		サーバパラメータの構造体ポインタ
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
		//眠っている時に出した、ため技系は、ためをはずす（ねごと対策）
		if((sp->psp[client_no].condition&CONDITION_NEMURI)&&(sp->psp[client_no].condition2&CONDITION2_KEEP)){
			ST_ServerKeepOff(bw,sp,client_no);
		}
		if((sp->psp[client_no].condition&CONDITION_NEMURI)&&(sp->psp[client_no].condition2&CONDITION2_ABARERU)){
			sp->psp[client_no].condition2&=CONDITION2_ABARERU_OFF;
		}
	}
	//このゆびとまれフラグもクリア
	sp->scw[0].konoyubitomare_flag=0;
	sp->scw[1].konoyubitomare_flag=0;
}

//============================================================================================
/**
 *	わるあがきになるかチェック
 *
 * @param[in]	bw				戦闘システム用ワーク構造体
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	チェックするClientNo
 * @param[in]	check_bit	チェックする項目（battle_common.hに定義）
 */
//============================================================================================
int		ST_ServerWaruagakiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int waza_bit,int check_bit)
{
	int	pos;
	int	eqp;

	eqp=ST_ServerSoubiEqpGet(sp,client_no);

	for(pos=0;pos<4;pos++){
		//わざがない
		if((sp->psp[client_no].waza[pos]==0)&&(check_bit&SSWC_WAZA_NONE)){
			waza_bit|=No2Bit(pos);
		}
		//PPがない
		if((sp->psp[client_no].pp[pos]==0)&&(check_bit&SSWC_PP_NONE)){
			waza_bit|=No2Bit(pos);
		}
		//かなしばりされてる
		if((sp->psp[client_no].waza[pos]==sp->psp[client_no].wkw.kanashibari_wazano)&&(check_bit&SSWC_KANASHIBARI)){
			waza_bit|=No2Bit(pos);
		}
		//いちゃもんをつけられている
		if((sp->psp[client_no].waza[pos]==sp->waza_no_old[client_no])&&(check_bit&SSWC_ICHAMON)&&
		   (sp->psp[client_no].condition2&CONDITION2_ICHAMON)){
			waza_bit|=No2Bit(pos);
		}
		//ちょうはつされている
		if((sp->psp[client_no].wkw.chouhatsu_count)&&(check_bit&SSWC_CHOUHATSU)&&
//	   	   (WT_WazaDataParaGet(sp->psp[client_no].waza[pos],ID_WTD_damage)==0)){
	   	   (sp->AIWT.wtd[sp->psp[client_no].waza[pos]].damage==0)){
			waza_bit|=No2Bit(pos);
		}
		//ふういんされている
		if((ST_ServerHuuinCheck(bw,sp,client_no,sp->psp[client_no].waza[pos]))&&(check_bit&SSWC_HUUIN)){
			waza_bit|=No2Bit(pos);
		}
		//じゅうりょくを受けている
		if((ST_ServerJuuryokuCheck(bw,sp,client_no,sp->psp[client_no].waza[pos]))&&(check_bit&SSWC_JUURYOKU)){
			waza_bit|=No2Bit(pos);
		}
		//ヒールブロックを受けている
		if((ST_ServerHealblockCheck(bw,sp,client_no,sp->psp[client_no].waza[pos]))&&(check_bit&SSWC_HEALBLOCK)){
			waza_bit|=No2Bit(pos);
		}
		//アンコール
		if((sp->psp[client_no].wkw.encore_wazano)&&(sp->psp[client_no].wkw.encore_wazano!=sp->psp[client_no].waza[pos])){
			waza_bit|=No2Bit(pos);
		}
		//こだわりハチマキチェック
		if(((eqp==SOUBI_ONAZIWAZAONLY)||(eqp==SOUBI_ONAZIWAZAONLYSUBAYASAUP)||(eqp==SOUBI_ONAZIAWZAONLYTOKUSYUUP))&&
		    (check_bit&SSWC_KODAWARI)){
			//技忘れでこだわりハチマキ系のワークに格納した技が消えていないかチェック
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
 *	選択した技を出すことが出来るかチェック
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	waza_no		ポジションを取得する技ナンバー
 *
 * @retval	TRUE:出せる　FALSE:出せない
 */
//============================================================================================
BOOL	ST_ServerWazaNGCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no,int pos,MESSAGE_PARAM *mp)
{
	BOOL	ret;

	ret=TRUE;

	//かなしばりチェック
	if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_KANASHIBARI)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=KanashibariNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//いちゃもんチェック
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_ICHAMON)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK;
		mp->msg_id=IchamonNGMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		ret=FALSE;
	}
	//ちょうはつチェック
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_CHOUHATSU)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=ChouhatsuNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//ふういんチェック
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_HUUIN)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=HuuinNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//じゅうりょくチェック
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_JUURYOKU)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA;
		mp->msg_id=JuuryokuNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//ヒールブロックチェック
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_HEALBLOCK)&No2Bit(pos)){
		mp->msg_tag=TAG_NICK_WAZA_WAZA;
		mp->msg_id=HealblockNGMineMsg;
		mp->msg_para[0]=ST_ServerTagNickParaMake(sp,client_no);
		mp->msg_para[1]=WAZANO_KAIHUKUHUUZI;
		mp->msg_para[2]=sp->psp[client_no].waza[pos];
		ret=FALSE;
	}
	//こだわりハチマキチェック
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_KODAWARI)&No2Bit(pos)){
		mp->msg_tag=TAG_ITEM_WAZA;
		mp->msg_id=ItemOnaziWazaOnlyMsg;
		mp->msg_para[0]=sp->psp[client_no].item;
		mp->msg_para[1]=sp->psp[client_no].wkw.kodawari_wazano;
		ret=FALSE;
	}
	//PPチェック（これは、かならず最後にする）
	else if(ST_ServerWaruagakiCheck(bw,sp,client_no,0,SSWC_PP_NONE)&No2Bit(pos)){
		mp->msg_tag=TAG_NONE;
		mp->msg_id=PPNoneMsg;
		ret=FALSE;
	}

	return ret;
}

//============================================================================================
/**
 *	技のポジションを取得
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	waza_no		ポジションを取得する技ナンバー
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
 *	技とポケモンの相性チェック用相性テーブル
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
	{NORMAL_TYPE,	IWA_TYPE,		IMAHITOTSU},	// NORMAL で IWA に攻撃すると、
													// 威力０．５倍
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
 *	効果ないポケモンの相性を当てる技効果のチェック
 *
 * @param[in]	sp				サーバパラメータの構造体ポインタ
 * @param[in]	attack_client	攻撃側ClientNo
 * @param[in]	defence_client	防御側ClientNo
 * @param[in]	pos				TypeCheckTableのIndex
 *
 * @retval	FALSE:当たる　TRUE:効果ないままでOK
 */
//============================================================================================
static	BOOL	ST_KoukanaiCheck(SERVER_PARAM *sp,int attack_client,int defence_client,int pos)
{
	BOOL	ret;
	int		eqp;

	eqp=ST_ServerSoubiEqpGet(sp,defence_client);

	ret=TRUE;

	//ねをはるチェック
	//装備効果すばやさDOWN
	if((eqp==SOUBI_SUBAYASADOWN)||(sp->psp[defence_client].waza_kouka&WAZAKOUKA_NEWOHARU)){
		//ひこうにヒット
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}
	//はねやすめチェック
	if(sp->otf[defence_client].haneyasume_flag){
		//ひこうにヒット(1倍であてる）
		if(TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE){
			ret=FALSE;
		}
	}
	//じゅうりょくチェック
	if(sp->field_condition&FIELD_CONDITION_JUURYOKU){
		//ひこうにヒット
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}
	//ミラクルアイチェック
	if(sp->psp[defence_client].waza_kouka&WAZAKOUKA_MIRACLE_EYE){
		//あくにヒット
		if((TypeCheckTable[pos][POKE_TYPE]==AKU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	技とポケモンの相性チェック
 *
 * @param[in]	bw				戦闘システム用ワーク構造体
 * @param[in]	sp				サーバパラメータの構造体ポインタ
 * @param[in]	waza_no			チェックする技
 * @param[in]	attack_client	攻撃側ClientNo
 * @param[in]	defence_client	防御側ClientNo
 * @param[out]	damage			蓄積されているダメージ
 * @param[out]	flag			チェック結果のフラグを格納するワーク
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
	
	//わるあがきは、無属性なのでTypeCheckしない
	if(waza_no==WAZANO_WARUAGAKI){
		return damage;
	}

	eqp_a=ST_ServerSoubiEqpGet(sp,attack_client);
	atk_a=ST_ServerSoubiAtkGet(sp,attack_client,ATK_CHECK_NORMAL);
	eqp_d=ST_ServerSoubiEqpGet(sp,defence_client);
	atk_d=ST_ServerSoubiAtkGet(sp,defence_client,ATK_CHECK_NORMAL);

	//特性ノーマルスキンは、技タイプをノーマルにする
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
		//特性てきおうりょくは、タイプ一致した時、1.5倍を2倍にする
		if(ST_ServerTokuseiGet(sp,attack_client)==TOKUSYU_TEKIOURYOKU){
			damage*=2;
		}
		else{
			damage=damage*15/10;
		}
	}

	//特殊効果ふゆうには、じめんタイプの技は当たらない（装備効果で素早さDOWNはヒットする）
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack_client,defence_client,TOKUSYU_HUYUU)==TRUE)&&
  	   (wazatype==JIMEN_TYPE)&&
	   (eqp_d!=SOUBI_SUBAYASADOWN)){
		flag[0]|=WAZA_STATUS_FLAG_JIMEN_NOHIT;
	}
	//技効果でんじふゆうには、じめんタイプの技は当たらない（じゅうりょく中は、でんじふゆうを無効にする）
	//（装備効果で素早さDOWNはヒットする）
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
				//みやぶるチェックor特性きもったまを持っている
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

	//特殊能力ふしぎなまもりは、効果が抜群しか当たらない
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
				//特性フィルター、ハードロックは、抜群で当たった時、ダメージを3/4にする
				if((ST_ServerKatayaburiTokuseiCheck(sp,attack_client,defence_client,TOKUSYU_FIRUTAA)==TRUE)||
				   (ST_ServerKatayaburiTokuseiCheck(sp,attack_client,defence_client,TOKUSYU_HAADOROKKU)==TRUE)){
					damage=ST_ServerDamageDiv(damage*3,4);
				}
				//装備効果で抜群を威力％分アップする
				if(eqp_a==SOUBI_BATUGUNIRYOKUUP){
					damage=damage*(100+atk_a)/100;
				}
			}
			if((flag[0]&WAZA_STATUS_FLAG_IMAHITOTSU)&&(waza_damage)){
				//特性いろめがねは、いまひとつの0.5を1に、0.25を0.5にする
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
 *	技とポケモンの相性チェック（AI用）
 *
 * @param[in]	bw				戦闘システム用ワーク構造体
 * @param[in]	sp				サーバパラメータの構造体ポインタ
 * @param[in]	waza_no			チェックする技
 * @param[in]	attack_client	攻撃側ClientNo
 * @param[in]	defence_client	防御側ClientNo
 * @param[out]	flag			チェック結果のフラグを格納するワーク
 */
//============================================================================================
void	ST_AITypeCheck(SERVER_PARAM *sp,int waza_no,int waza_type,int spe_a,int spe_d,int eqp,int type1,int type2,u32 *flag)
{
	int	i;
	u8	wazatype;

	//わるあがきは、無属性なのでTypeCheckしない
	if(waza_no==WAZANO_WARUAGAKI){
		return;
	}

	//特性ノーマルスキンは、技タイプをノーマルにする
	if(spe_a==TOKUSYU_NOOMARUSUKIN){
		wazatype=NORMAL_TYPE;
	}
	else if(waza_type){
		wazatype=waza_type;
	}
	else{
		wazatype=sp->AIWT.wtd[waza_no].wazatype;
	}

	//特殊効果ふゆうには、じめんタイプの技は当たらない（装備効果で素早さDOWNはヒットする）
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
				//みやぶるチェックor特性きもったまを持っている
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

	//特殊能力ふしぎなまもりは、効果が抜群しか当たらない
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
 *	効果ないポケモンの相性を当てる技効果のチェック
 *
 * @param[in]	sp				サーバパラメータの構造体ポインタ
 * @param[in]	eqp				装備効果
 * @param[in]	pos				TypeCheckTableのIndex
 *
 * @retval	FALSE:当たる　TRUE:効果ないままでOK
 */
//============================================================================================
static	BOOL	ST_AIKoukanaiCheck(SERVER_PARAM *sp,int eqp,int pos)
{
	BOOL	ret;

	ret=TRUE;

	//装備効果すばやさDOWN
	if(eqp==SOUBI_SUBAYASADOWN){
		//ひこうにヒット
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}
	//じゅうりょくチェック
	if(sp->field_condition&FIELD_CONDITION_JUURYOKU){
		//ひこうにヒット
		if((TypeCheckTable[pos][POKE_TYPE]==HIKOU_TYPE)&&
		   (TypeCheckTable[pos][POWER]==KOUKANAI)){
			ret=FALSE;
		}
	}

	return ret;
}

//============================================================================================
/**
 *	ポケモンと技のタイプの相性でフラグをセット
 *
 * @param[in]	client_no	技を繰り出すClientNo
 * @param[in]	power		相性を示す威力
 * @param[out]	flag		フラグをセットするワーク
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
 *	技の発動を妨げられたかチェック
 *
 * @param[in]	sp	サーバパラメータの構造体ポインタ
 *
 * @retval	FALSE:妨げられていない　TRUE:妨げられた
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
 *	攻撃を当てることの出来るポケモンが何体いるかチェック
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	flag		チェック対象フラグ
 * @param[in]	client_no	チェック対象ClientNo
 *
 * @retval	ポケモンの数
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
 *	メッセージ表示パラメータのニックネームデータを生成
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	生成対象ClientNo
 *
 * @retval	生成したパラメータ
 */
//============================================================================================
int		ST_ServerTagNickParaMake(SERVER_PARAM *sp,int client_no)
{
	return (client_no|(sp->sel_mons_no[client_no]<<8));
}

//============================================================================================
/**
 *	選択した技ナンバーを取得
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	取得するClientNo
 *
 * @retval	選択した技ナンバー
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
 *	特性を持ったポケモンがいるかチェック
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	flag		チェックの種類
 * @param[in]	client_no	チェックするClientNo（チェックの種類により意味が変化）
 * @param[in]	speabi		チェックする特性ナンバー
 *
 * @retval	持っていたポケモン数
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
	case STC_HAVE_MINE_SIDE:	//自分側が持っているかチェック
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)==BattleWorkMineEnemyCheck(bw,client_no))&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_MINE_SIDE_HP:	//自分側が持っているかチェック（HP0は無効）
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)==BattleWorkMineEnemyCheck(bw,client_no))&&
			   (sp->psp[no].hp)&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ENEMY_SIDE:	//相手側が持っているかチェック
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)!=BattleWorkMineEnemyCheck(bw,client_no))&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ENEMY_SIDE_HP:	//相手側が持っているかチェック（HP0は無効）
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)!=BattleWorkMineEnemyCheck(bw,client_no))&&
			   (sp->psp[no].hp)&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ENEMY_SIDE_RET:	//相手側が持っているかチェックして持っていたClientNoを返す
		for(no=0;no<client_set_max;no++){
			if((BattleWorkMineEnemyCheck(bw,no)!=BattleWorkMineEnemyCheck(bw,client_no))&&
			   (sp->psp[no].hp)&&
			   (ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt|=No2Bit(no);
			}
		}
		break;
	case STC_HAVE_ALL:			//自分も含め持っているかチェック
		for(no=0;no<client_set_max;no++){
			if(ST_ServerTokuseiGet(sp,no)==speabi){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ALL_NOMINE:	//自分以外のポケモンが持っているかチェック
		for(no=0;no<client_set_max;no++){
			if((no!=client_no)&&(ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ALL_NOMINE_RET:	//自分以外のポケモンが持っているかチェックして持っていたClientNoを返す
		for(no=0;no<client_set_max;no++){
			if((no!=client_no)&&(ST_ServerTokuseiGet(sp,no)==speabi)){
				cnt=no+1;
				break;
			}
		}
		break;
	case STC_HAVE_ALL_HP:			//自分も含め持っているかチェック（HP0は無効）
		for(no=0;no<client_set_max;no++){
			if((ST_ServerTokuseiGet(sp,no)==speabi)&&(sp->psp[no].hp)){
				cnt++;
			}
		}
		break;
	case STC_HAVE_ALL_NOMINE_HP:	//自分以外のポケモンが持っているかチェック（HP0は無効）
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
 *	ため技を選択しているかチェック
 *
 * @param[in]	waza_no		チェックする技ナンバー
 *
 * @retval	TRUE：ため技　FALSE:ため技じゃない
 */
//============================================================================================
BOOL	ST_TameWazaCheck(SERVER_PARAM *sp,int waza_no)
{
	switch(sp->AIWT.wtd[waza_no].battleeffect){
	case 26:	//がまん
	case 39:	//かまいたち
	case 75:	//ゴッドバード
	case 145:	//ロケット頭突き
	case 151:	//ソーラービーム
	case 155:	//そらをとぶ
	case 255:	//ダイビング
	case 256:	//あなをほる
	case 263:	//とびはねる
	case 272:	//シャドーダイブ
		return TRUE;
		break;
	}

	return FALSE;
}

//============================================================================================
/**
 *	TypeCheckTableのパラメータを取得
 *
 * @param[in]	pos		テーブルのインデックス
 * @param[in]	type_w	技タイプ格納先
 * @param[in]	type_p	ポケモンタイプ格納先
 * @param[in]	value	type_wとtype_pの相性
 *
 * @retval	FALSE:テーブルをオーバー　TRUE:テーブルないから取得
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
 *	TypeCheckTableからパワーを取得
 *
 * @param[in]	type_w	技タイプ
 * @param[in]	type_p1	ポケモンタイプ
 * @param[in]	type_p2	ポケモンタイプ
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
 *	違う技へ派生する技のチェック
 *
 * @param[in]	waza_no	チェックする技ナンバー
 *
 * @retval	FALSE:派生技ではない　TRUE:派生技
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
 *	繰り出そうとしているのろいが、ノーマルか、ゴーストかチェック
 *
 * @param[in]	sp			サーバワーク構造体
 * @param[in]	waza_no		チェックする技ナンバー
 * @param[in]	client_no	繰り出そうとしているClientNo
 *
 * @retval	FALSE:ノーマル　TRUE:ゴースト
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
 *	どろぼうできるアイテムかチェック
 *
 * @param[in]	sp			サーバワーク構造体
 * @param[in]	client_no	どろぼうされるClientNo
 *
 * @retval	FALSE:できない　TRUE:できる
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
 *	トリックできるアイテムかチェック
 *
 * @param[in]	sp			サーバワーク構造体
 * @param[in]	client_no	トリックをしているClientNo
 *
 * @retval	FALSE:できない　TRUE:できる
 */
//============================================================================================
BOOL	ST_ServerTrickItemCheck(SERVER_PARAM *sp,int client_no)
{
	return (ItemMailCheck(sp->psp[client_no].item)==FALSE);
}

//============================================================================================
/**
 *	ふきとばし成否判定
 *
 * @param[in]	sp			サーバワーク構造体
 *
 * @retval	FALSE:できない　TRUE:できる
 */
//============================================================================================
BOOL	ST_ServerHukitobasiCheck(SERVER_PARAM *sp)
{
	BOOL	ret;

	ret=FALSE;

	//出した側のレベルが高ければ、100%成功
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
 *	特性取得（技「いえき」の効果も反映して取得）
 *
 * @param[in]	psp			ポケモンサーバワーク構造体
 *
 * @retval	特性ナンバー
 */
//============================================================================================
u8	ST_ServerTokuseiGet(SERVER_PARAM *sp,int client_no)
{
	//いえき発動中は、特性無効（マルチタイプは除外）
	if((sp->psp[client_no].waza_kouka&WAZAKOUKA_IEKI)&&(sp->psp[client_no].speabino!=TOKUSYU_MARUTITAIPU)){
		return 0;
	}
	//じゅうりょく発動中は、ふゆうは無効
	else if((sp->field_condition&FIELD_CONDITION_JUURYOKU)&&(sp->psp[client_no].speabino==TOKUSYU_HUYUU)){
		return 0;
	}
	//ねをはる発動中は、ふゆうは無効
	else if((sp->psp[client_no].waza_kouka&WAZAKOUKA_NEWOHARU)&&(sp->psp[client_no].speabino==TOKUSYU_HUYUU)){
		return 0;
	}
	else{
		return sp->psp[client_no].speabino;
	}
}

//============================================================================================
/**
 *	特性かたやぶりを反映してチェック
 *
 * @param[in]	sp			サーバワーク構造体
 * @param[in]	attack		攻撃側
 * @param[in]	defence		防御側
 * @param[in]	tokusei		チェックする特性
 *
 * @retval	FALSE:かたやぶりで特性が無効　TRUE：かたやぶり関係ない
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
 *	入れ替えるポケモンがいるかチェック
 *
 * @param[in]	bw			戦闘システムワーク構造体
 * @param[in]	sp			サーバワーク構造体
 * @param[in]	client_no	チェックするClientNo
 *
 * @retval	FALSE:いない　TRUE:いる
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
	//ダブル
	else if(fight_type&FIGHT_TYPE_2vs2){
		start=0;
		end=poke_count;
		rnd_max=poke_count;
		cntmax=1;
		selmons1=sp->sel_mons_no[client_no];
		selmons2=sp->sel_mons_no[BattleWorkPartnerClientNoGet(bw,client_no)];
	}
	//シングル
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
 *	戦闘から逃げられるかをチェックする（逃げるコマンドが成立するかどうか）
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	@param[in]	mp			アラートメッセージのパラメータを格納する構造体
 *	
 *	@retval	FALSE:逃げられる　TRUE:逃げられない
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

	//アイテムで必ず逃げられるの装備効果は100%逃げれる
	if((eqp==SOUBI_KANARAZUNIGERARERU)||
	//必ず逃げれるFIGHT_TYPEはチェックしない
	   (fight_type&FIGHT_TYPE_ESCAPE)||
	//特殊能力にげあしは必ず逃げれるのでチェックしない
	   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_NIGEASI)){
		return 0;
	}

	dir=BattleWorkMineEnemyCheck(bw,client_no);
	client_set_max=BattleWorkClientSetMaxGet(bw);

	//特性かげふみからは逃げられない（お互いがかげふみの時は例外）
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
	//特性ありじごくからは逃げられない
	if((i=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_ARIZIGOKU))){
		if((sp->field_condition&FIELD_CONDITION_JUURYOKU)==0){
			//特性ふゆう、飛行タイプには、特性ありじごくは効果が無い
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
	//特性ありじごくからは逃げられない
	if((i=ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_NOMINE,client_no,TOKUSYU_ARIZIGOKU))&&
		//特性ふゆう、飛行タイプには、特性ありじごくは効果が無い
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
	//特性じりょくから鋼タイプのポケモンは逃げられない
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

	//しめつけられている、くろいまなざしをうけている、ねをはっている時は逃げられない
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
	//戦闘タイプがガイドバトルの時は逃げられない
	if(FightType&FIGHT_TYPE_GUIDE){
		ServerWork[5]=1;
		return 1;
	}
#endif
	return	FALSE;
}

//============================================================================================
/**
 *	戦闘から逃げられるかをチェックする（逃げるコマンド成立後）
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	
 *	@retval	TRUE:逃げられる　FALSE:逃げられない
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

	//アイテムで必ず逃げられるの装備効果は100%逃げれる
	if(eqp==SOUBI_KANARAZUNIGERARERU){
		sp->otf[client_no].escape_flag=1;
		ret=TRUE;
	}
	//100%逃げれるFIGHT_TYPEをチェック
	else if(fight_type&FIGHT_TYPE_ESCAPE){
		ret=TRUE;
	}
	//特殊能力にげあしは100%逃げれる
	else if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_NIGEASI){
		sp->otf[client_no].escape_flag=2;
		ret=TRUE;
	}
	else{
		//相手の方が早ければ逃げるを選択した回数が多いほど逃げやすくする
		if(sp->psp[client_no].agi<sp->psp[client_no^1].agi){
			escape=sp->psp[client_no].agi*128/sp->psp[client_no^1].agi+sp->escape_count*30;
			if(escape>(gf_rand()%256)){
				ret=TRUE;
			}
		}
		//自分の方が早ければ100%逃げれる
		else{
			ret=TRUE;
		}
		//逃げるに失敗したカウンタをカウントアップ
		if(ret==FALSE){
			SCIO_IncRecord(bw,client_no,CLIENT_BOOT_TYPE_MINE,RECID_NIGERU_SIPPAI);
		}
		sp->escape_count++;
	}
	return ret;
}

//============================================================================================
/**
 *	なまけチェック
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	
 *	@retval	FALSE:なまけない　TRUE:なまける
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
 *	さわぐチェック
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	
 *	@retval	FALSE:しずか　TRUE:さわがしい
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
 *	ふういんチェック
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	@param[in]	waza_no		チェックするWazaNo
 *	
 *	@retval	FALSE:ふういんされていない　TRUE:ふういんされている
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
 *	場にいるポケモンに技効果が発動しているかチェック
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	waza_kouka	チェックする技効果
 *	
 *	@retval	FALSE:効果が発動していない　TRUE:効果が発動
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
 *	ループ系の技でループする時に初期化するワーク
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
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
 *	素早さによる技発動順番のためのワークを生成
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
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
 *	じゅうりょくチェックテーブル
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
 *	じゅうりょくチェック
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	@param[in]	waza_no		チェックするWazaNo
 *	
 *	@retval	FALSE:じゅうりょくの影響をうけない　TRUE:じゅうりょくの影響をうける
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
 *	ヒールブロックチェックテーブル
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
 *	ヒールブロックチェック
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	@param[in]	waza_no		チェックするWazaNo
 *	
 *	@retval	FALSE:ヒールブロックの影響をうけない　TRUE:ヒールブロックの影響をうける
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
 *	とっておきカウント計算
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 */
//============================================================================================
void	ST_ServerTotteokiCountCalc(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	pos;

	//とっておきは、カウントしない
	//とっておきカウントがMAXなら、カウントしない
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
 *	技をいくつもっているかカウント
 *
 *	@param[in]	bw			戦闘システム構造体のポインタ
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	カウントするClientNo
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
 *	ダメージを回避する特性のチェック用データテーブル
 */
//============================================================================================
//ぼうおんテーブル
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
 *	ダメージを回避する特性のチェック
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	attack		攻撃するClientNo
 *	@param[in]	defence		防御するClientNo
 */
//============================================================================================
int		ST_ServerDamageTokuseiCheck(SERVER_PARAM *sp,int attack,int defence)
{
	int	seq_no;
	int	wazatype;

	seq_no=0;

	//特性ノーマルスキンは、技タイプをノーマルにする
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

	//ちくでんチェック
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TIKUDEN)==TRUE){
		if((wazatype==ELECTRIC_TYPE)&&(attack!=defence)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[defence].hpmax,4);
			seq_no=SUB_SEQ_TOKUSEI_HP_KAIFUKU;
		}
	}
	//ちょすいチェック
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TYOSUI)==TRUE){
		if((wazatype==WATER_TYPE)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage))){
		   (sp->AIWT.wtd[sp->waza_no_now].damage)){
			sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[defence].hpmax,4);
			seq_no=SUB_SEQ_TOKUSEI_HP_KAIFUKU;
		}
	}
	//もらいびチェック
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_MORAIBI)==TRUE){
		if((wazatype==FIRE_TYPE)&&
		  ((sp->psp[defence].condition&CONDITION_KOORI)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
//		   (WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage))){
		  ((sp->AIWT.wtd[sp->waza_no_now].damage)||(sp->waza_no_now==WAZANO_ONIBI))){
			seq_no=SUB_SEQ_MORAIBI;
		}
	}
	//ぼうおんチェック
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
	//でんきエンジンチェック	
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_DENKIENZIN)==TRUE){
		if((wazatype==ELECTRIC_TYPE)&&(attack!=defence)){
			seq_no=SUB_SEQ_DENKIENZIN;
		}
	}
	//かんそうはだチェック
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
 *	ターンチェック時の特性のチェック
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 */
//============================================================================================
BOOL	ST_ServerPCCTokuseiCheck(SERVER_PARAM *sp,int client_no)
{
	BOOL	ret;
	int		seq_no;

	ret=FALSE;

	switch(ST_ServerTokuseiGet(sp,client_no)){
	//かそく
	case TOKUSYU_KASOKU:
		if((sp->psp[client_no].hp)&&
		   (sp->psp[client_no].abiritycnt[COND_AGI]<12)&&
		   //出てきた最初のターンは、かそくを無視
		   (sp->psp[client_no].wkw.nekodamashi_count!=sp->total_turn+1)){
			sp->tsuika_para=ADD_COND2_AGIUP;
			sp->tsuika_type=ADD_STATUS_TOKUSEI;
			sp->tsuika_client=client_no;
			seq_no=SUB_SEQ_ABICNT_CALC;
			ret=TRUE;
		}
		break;
	//だっぴ
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
 *	ダメージ計算用の割り算を行う（割った結果が０の時は、1or-1補正をする
 *
 *	@param[in]	data	割られる数
 *	@param[in]	value	割る数
 *
 *	@retval	商
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
//			ST_ServerPokeAppearCheckのシーケンスナンバー
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
 *	ポケモン登場時のチェックをおこなう
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 *
 * @retval	チェックに引っかかった時に起動するSUB_SEQ_NO
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
		//天候チェック
		case SPAC_WEATHER:
			if(sp->weather_check_flag==0){
				switch(BattleWorkWeatherGet(bw)){
				case WEATHER_SYS_RAIN:			// 雨
				case WEATHER_SYS_STRAIN:		// 大雨
				case WEATHER_SYS_SPARK:			// 大雨
					seq_no=SUB_SEQ_FIELD_AME;
					ret=SPAC_WAZA_SEQ;
					break;
				case WEATHER_SYS_SNOW:			// 雪
				case WEATHER_SYS_SNOWSTORM:		// 吹雪
				case WEATHER_SYS_SNOWSTORM_H:	// 猛吹雪
					seq_no=SUB_SEQ_FIELD_ARARE;
					ret=SPAC_WAZA_SEQ;
					break;
				case WEATHER_SYS_SANDSTORM:		// BG使用砂嵐
					seq_no=SUB_SEQ_FIELD_SUNAARASHI;
					ret=SPAC_WAZA_SEQ;
					break;
				case WEATHER_SYS_MIST1:			// 霧払いの霧
				case WEATHER_SYS_MIST2:			// 霧払いの霧
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
		//特性トレースチェック
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
					//特性あめふらし
					case TOKUSYU_AMEHURASI:
						sp->psp[client_no].appear_check_flag=1;
						if((sp->field_condition&FIELD_CONDITION_AMEHURASHI)==0){
							seq_no=SUB_SEQ_AMEHURASI;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					//特性すなおこし
					case TOKUSYU_SUNAOKOSI:
						sp->psp[client_no].appear_check_flag=1;
						if((sp->field_condition&FIELD_CONDITION_SUNAOKOSHI)==0){
							seq_no=SUB_SEQ_SUNAOKOSI;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					//特性ひでり
					case TOKUSYU_HIDERI:
						sp->psp[client_no].appear_check_flag=1;
						if((sp->field_condition&FIELD_CONDITION_HIDERI)==0){
							seq_no=SUB_SEQ_HIDERI;
							ret=SPAC_WAZA_SEQ;
						}
						break;
					//特性ゆきふらし
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
		//特性いかくチェック
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
		//特性ダウンロードチェック
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
		//特性きけんよち
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
										//特性きけんよちは、効果抜群、一撃必殺の技に対して警告メッセージを出す
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
		//特性よちむ
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
									//威力１
									case 1:
//										switch(WT_WazaDataParaGet(waza_no,ID_WTD_battleeffect)){
										switch(sp->AIWT.wtd[waza_no].battleeffect){
										//一撃必殺
										case 38:
											if((pow_temp<150)||
											  ((pow_temp==150)&&(gf_rand()&1))){
												pow_temp=150;
												sp->waza_work=waza_no;
											}
											break;
										//カウンター
										//ミラーコート
										//あだうち
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
						//見つからなかった場合は、持っている技からランダムで選択
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
		//特性おみとおし
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
		//特性スロースタート
		case SPAC_SLOWSTART:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				//初回ターンと効果切れターンにメッセージ
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
		//特性かたやぶり
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
		//特性プレッシャー
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
		//特性てんきや
		case SPAC_TENKIYA:
			if(ST_ServerTenkiyaCheck(bw,sp)==TRUE){
				seq_no=SUB_SEQ_TENKIYA;
				ret=SPAC_WAZA_SEQ;
			}
			else{
				sp->spac_seq_no++;
			}
			break;
		//装備効果お金2倍
		case SPAC_OKANE2BAI:
			for(i=0;i<client_set_max;i++){
				client_no=sp->psp_agi_work[i];
				if(ST_ItemParamGet(sp,sp->psp[client_no].item,ITEM_PRM_EQUIP)==SOUBI_OKANENIBAI){
					sp->okodukai_value=2;	///<お小遣いの倍率ワーク
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
		//チェック終了
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
 *	相手側2体のうち1体をランダムで選択（1vs1の時は素直に相手側を選択）
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	チェックするClientNo
 *
 * @retval	選択したClientNo
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
 *	技がヒットした時にチェックする特性
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	seq_no		発動した時のseq_noを代入するポインタワーク
 *
 * @retval	TRUE:特性発動　FALSE:特性不発
 */
//============================================================================================
BOOL	ST_ServerWazaHitTokuseiCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int *seq_no)
{
	BOOL	ret;

	ret=FALSE;

	//攻撃対象がいなければ、チェックなし
	if(sp->defence_client==NONE_CLIENT_NO){
		return ret;
	}

	//みがわりでは不発
	if(ST_ServerMigawariCheck(sp,sp->defence_client)==TRUE){
		return ret;
	}

	switch(ST_ServerTokuseiGet(sp,sp->defence_client)){
	//せいでんき
	case TOKUSYU_SEIDENKI:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //とんぼがえり入れ替えでは、発動なし
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
		   //とんぼがえり入れ替えでは、発動なし
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
	//へんしょく
	case TOKUSYU_HENSYOKU:
		{
			u8	wazatype;

			//特性ノーマルスキンは、技タイプをノーマルにする
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
				//とんぼがえり入れ替えでは、発動なし
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
	//さめはだ
	case TOKUSYU_SAMEHADA:
		if((sp->psp[sp->attack_client].hp)&&
			//特性マジックガードは、さめはだの効果を受けない
		   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //とんぼがえり入れ替えでは、発動なし
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
	//ほうし
	case TOKUSYU_HOUSI:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		  //とんぼがえり入れ替えでは、発動なし
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
		   //とんぼがえり入れ替えでは、発動なし
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
	//どくのとげ
	case TOKUSYU_DOKUNOTOGE:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //とんぼがえり入れ替えでは、発動なし
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
		   //とんぼがえり入れ替えでは、発動なし
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
	//ほのおのからだ
	case TOKUSYU_HONOONOKARADA:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		   (sp->psp[sp->attack_client].condition==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //とんぼがえり入れ替えでは、発動なし
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
		   //とんぼがえり入れ替えでは、発動なし
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
	//メロメロボディ
	case TOKUSYU_MEROMEROBODHI:
#ifdef PM_DEBUG
		if((sp->psp[sp->attack_client].hp)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_MEROMERO)==0)&&
		  ((sp->waza_status_flag&WAZA_STATUS_FLAG_NO_OUT)==0)&&
		  ((sp->server_status_flag&SERVER_STATUS_FLAG_TAME)==0)&&
		   //とんぼがえり入れ替えでは、発動なし
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
		   //とんぼがえり入れ替えでは、発動なし
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
	//ゆうばく
	case TOKUSYU_YUUBAKU:
		if((sp->defence_client==sp->kizetsu_client)&&
			//特性マジックガードは、ゆうばくの効果を受けない
		   (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_MAZIKKUGAADO)&&
		   //特性しめりけがいる時は、ゆうばくできない
		   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_SIMERIKE)==0)&&
		   //とんぼがえり入れ替えでは、発動なし
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
 *	技がヒットした時にチェックする特性（スキルスワップなどで、特性が入れ替わって状態異常を直すチェック）
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	チェックするClientNo
 * @param[in]	act_flag	動作フラグ（0:必要なワークにすべて代入　1:シーケンスナンバー類の代入はしない）
 *
 * @retval	TRUE:特性発動　FALSE:特性不発
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
		//どろぼうやトリックでアイテムを入手した時にフラグを立てる
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
 *	入れ替え時に状態異常を直す特性をチェック
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	tokusei		チェックする特性
 * @param[in]	condition	チェックする状態異常
 *
 * @retval	TRUE:特性発動　FALSE:特性不発
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
 *	技がヒットした時にチェックする特性（シンクロのみ）
 *
 * @param[in]	bw				戦闘システム用ワーク構造体
 * @param[in]	sp				サーバ用パラメータワーク構造体
 * @param[in]	server_seq_no	sp->next_server_seq_noにセットするナンバー
 *
 * @retval	TRUE:特性発動　FALSE:特性不発
 */
//============================================================================================
BOOL	ST_ServerSinkuroCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int server_seq_no)
{
	BOOL	ret;
	int		seq_no;

	ret=FALSE;

	//防御側チェック
	if((ST_ServerTokuseiGet(sp,sp->defence_client)==TOKUSYU_SINKURO)&&
	   (sp->defence_client!=NONE_CLIENT_NO)&&
	   (sp->defence_client==sp->tsuika_client)&&
	   (sp->server_status_flag&SERVER_STATUS_FLAG_SINKURO_TSUIKA)){
		sp->client_work=sp->defence_client;
		sp->tsuika_client=sp->attack_client;
		ret=TRUE;
	}
	//攻撃側チェック
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

	//てんきやもタイミングはいっしょなのでチェックする
	ret=ST_ServerTenkiyaCheck(bw,sp);
	if(ret==TRUE){
		ST_ServerSequenceLoad(sp,ARC_SUB_SEQ,SUB_SEQ_TENKIYA);
		sp->next_server_seq_no=server_seq_no;
		sp->server_seq_no=SERVER_WAZA_SEQUENCE_NO;
		return ret;
	}

	//チェックするタイミングは同じなので、装備アイテム「あかいいと」もチェック
	//防御側チェック
	if((ST_ServerSoubiEqpGet(sp,sp->defence_client)==SOUBI_MEROMERODETEKIMOMEROMERO)&&
	   (sp->defence_client!=NONE_CLIENT_NO)&&
	   (sp->defence_client==sp->tsuika_client)&&
	   (sp->ostf[sp->defence_client].status_flag&OSTF_STATUS_FLAG_MEROMERO)){
		sp->client_work=sp->defence_client;
		sp->tsuika_client=sp->attack_client;
		ret=TRUE;
	}
	//攻撃側チェック
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
 *	ターンチェック時の装備アイテム効果のチェック
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	FALSE:なにもなし	TRUE:装備効果発動
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
 *	ターンチェック時の装備アイテム効果のチェック（たべのこし、くろいヘドロ）
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	FALSE:なにもなし	TRUE:装備効果発動
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
			//特性マジックガードはダメージなし
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
 *	装備アイテム効果のチェック（状態異常系を直す奴のみ）
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	@param[in]	seq_no		起動するシーケンスナンバー
 *
 *	@retval	FALSE:なにもなし	TRUE:装備効果発動
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
			//特性くいしんぼは、早い段階で起動するように
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
 *	装備アイテム効果のチェック（ダメージ系）
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	装備アイテムナンバー
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
			//特性マジックガードはダメージなし
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
 *	装備アイテムナンバーの取得
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	装備アイテムナンバー
 */
//============================================================================================
u16	ST_ServerSoubiItemNoGet(SERVER_PARAM *sp,int client_no)
{
	//特性ぶきようは、アイテムを使いこなせない
	if((ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_BUKIYOU)){
		return 0;
	}
	//シャットアウトの技効果発動中は、アイテムが使えない
	if(sp->psp[client_no].wkw.shutout_count){
		return 0;
	}
	
	return sp->psp[client_no].item;
}

//============================================================================================
/*
 *	チェック対象が動作を終了しているかチェック
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	FALSE:まだ動作していない　TRUE:動作終了
 */
//============================================================================================
BOOL	ST_ServerWazaEndCheck(SERVER_PARAM *sp,int client_no)
{
	return (sp->client_act_work[client_no][ACT_PARA_ACT_NO]==SERVER_WAZA_END_NO);
}

//============================================================================================
/**
 *	技がヒットした時にチェックする装備効果
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[out]	seq_no		シーケンスナンバー格納ワーク
 *
 * @retval	TRUE:装備効果発動　FALSE:装備効果不発
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

	//攻撃対象がいない場合は、チェックなし
	if(sp->defence_client==NONE_CLIENT_NO){
		return ret;
	}

	//みがわりでは不発
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
		   //はたきおとすは除外
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
			//特性マジックガードには不発
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
			//特性マジックガードには不発
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
 *	装備効果ナンバーを取得
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	装備効果ナンバーを取得するClientNo
 *
 * @retval	装備効果ナンバー
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
 *	装備効果威力を取得
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	装備効果威力を取得するClientNo
 * @param[in]	flag		技効果を判断しなくていいかどうかフラグ（0:判断する　1:判断しない）
 *
 * @retval	装備効果威力
 */
//============================================================================================
s32	ST_ServerSoubiAtkGet(SERVER_PARAM *sp,int client_no,int flag)
{
	u16		item_no;

	switch(flag){
	case ATK_CHECK_NORMAL:	//チェックあり
		item_no=ST_ServerSoubiItemNoGet(sp,client_no);
		break;
	case ATK_CHECK_SHUTOUT:	//シャットアウトだけチェックあり
		if(sp->psp[client_no].wkw.shutout_count){
			return 0;
		}
	case ATK_CHECK_NONE:	//チェックなし
		item_no=sp->psp[client_no].item;
		break;
	}

//	return ItemParamGet(item_no,ITEM_PRM_ATTACK,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,item_no,ITEM_PRM_ATTACK);
}

//============================================================================================
/**
 *	しぜんのめぐみ威力を取得
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	威力を取得するClientNo
 *
 * @retval	しぜんのめぐみ威力
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
 *	しぜんのめぐみタイプを取得
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	タイプを取得するClientNo
 *
 * @retval	しぜんのめぐみタイプ
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
 *	ついばむ効果ナンバーを取得
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	ついばむ効果ナンバーを取得するClientNo
 *
 * @retval	ついばむ効果ナンバー
 */
//============================================================================================
s32	ST_ServerTsuibamuEqpGet(SERVER_PARAM *sp,int client_no)
{
	u16	item_no;
	int	eqp;

	//ついばむは、技効果でアイテム使えない状況を判断しなくていいので、直接取る
//	item_no=ST_ServerSoubiItemNoGet(sp,client_no);
	item_no=sp->psp[client_no].item;
//	eqp=ItemParamGet(item_no,ITEM_PRM_TUIBAMU_EFF,HEAPID_BATTLE);
	eqp=ST_ItemParamGet(sp,item_no,ITEM_PRM_TUIBAMU_EFF);

#if 0
	if(eqp){
		//特性ねんちゃくは、ついばめない
		if(ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,TOKUSYU_NENTYAKU)==TRUE){
			eqp=0;
		}
	}
#endif

	return eqp;
}

//============================================================================================
/**
 *	なげつける効果ナンバーを取得
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	なげつける効果ナンバーを取得するClientNo
 *
 * @retval	なげつける効果ナンバー
 */
//============================================================================================
s32	ST_ServerNagetsukeruEqpGet(SERVER_PARAM *sp,int client_no)
{
	//シャットアウトの技効果発動中は、アイテムが使えない
	if(sp->psp[client_no].wkw.shutout_count){
		return 0;
	}

//	return ItemParamGet(sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_EFF,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_EFF);
}

//============================================================================================
/**
 *	なげつける威力を取得
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	威力を取得するClientNo
 *
 * @retval	なげつける威力
 */
//============================================================================================
s32	ST_ServerNagetsukeruAtkGet(SERVER_PARAM *sp,int client_no)
{
	//シャットアウトの技効果発動中は、アイテムが使えない
	if(sp->psp[client_no].wkw.shutout_count){
		return 0;
	}

//	return ItemParamGet(sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_ATC,HEAPID_BATTLE);
	return ST_ItemParamGet(sp,sp->psp[client_no].item,ITEM_PRM_NAGETUKERU_ATC);
}

//============================================================================================
/**
 *	ポケモン入れ替えが可能かチェック
 *
 * @param[in]	bw			戦闘システム用ワーク構造体
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	チェックするClientNo
 *
 * @retval	入れ替えできない技効果の技ナンバー
 */
//============================================================================================
int		ST_ServerPokemonSelectCheck(BATTLE_WORK *bw,SERVER_PARAM *sp,int client_no)
{
	int	wazano;

	wazano=0;

	//装備効果でかならず入れ替われる効果の場合は、入れ替われる
	if(ST_ServerSoubiEqpGet(sp,client_no)==SOUBI_KANARAZUIREKAWARERU){
		return 0;
	}

	//しめつける系、くろいまなざし、ねをはるは、入れ替えできない
	if((sp->psp[client_no].condition2&(CONDITION2_SHIME|CONDITION2_KUROIMANAZASHI))||
	   (sp->psp[client_no].waza_kouka&WAZAKOUKA_NEWOHARU)){
		wazano=1;
	}

	//相手が特性かげふみ、じりょくを持っているときは、入れ替えできない
	if( ((ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_KAGEHUMI)&&
		 (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_KAGEHUMI)))||
	   (((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL)==METAL_TYPE)||
		 (ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL)==METAL_TYPE))&&
		 (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ENEMY_SIDE_HP,client_no,TOKUSYU_ZIRYOKU))) ){
		wazano=1;
	}
	//相手が特性ありじごくを持っているときは、入れ替えできない
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
 *	ついばむ効果のチェック
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	FALSE:なにもなし	TRUE:ついばむ効果発動
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

	//みがわりからは、ついばめない
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
		//装備しているものが木の実なら、ついばむことだけは発動
		if(ItemNutsCheck(sp->psp[client_no].item)==TRUE){
			ret=TRUE;
		}
		break;
	}

	if(ret==TRUE){
		//特性ぶきよう、技効果シャットアウトは、アイテムの効果を発揮できない
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
 *	なげつける効果のチェック
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	FALSE:なにもなし	TRUE:なげつける効果発動
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

	//威力のないアイテムは、発動できない
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

	//さしおさえられている時は、装備効果の発動なし
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
 *	メトロノームチェック（技を出す前チェック）
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 */
//============================================================================================
void	ST_ServerMetronomeBeforeCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//同じ技を出し続けると威力アップのチェック（継続技系は除外）
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
 *	メトロノームチェック（技を出した後チェック）
 *
 *	@param[in]	bw			戦闘システム用ワーク構造体
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 */
//============================================================================================
void	ST_ServerMetronomeAfterCheck(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//同じ技を出し続けると威力アップのチェック（継続技系は除外）
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
 *	ポケモンのやる気をチェックして、鳴き声パターンを取得
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *	@param[in]	client_no	チェックするClientType
 *	@param[in]	encount		TRUE:エンカウント登場時
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
 *	コマンド選択する条件か調べる
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするClientNo
 *
 *	@retval	FALSE:コマンド選択なし　TRUE:コマンド選択あり
 */
//============================================================================================
BOOL	ST_ServerCommandSelectCheck(SERVER_PARAM *sp,int client_no)
{
	BOOL	ret=TRUE;

	///<反動の時は、コマンド選択なし
	if((sp->psp[client_no].condition2&CONDITION2_HANDOU)||
	///<あばれている最中は、コマンド選択なし
	   (sp->psp[client_no].condition2&CONDITION2_ABARERU)||
	///<さわいでいる最中は、コマンド選択なし
	   (sp->psp[client_no].condition2&CONDITION2_SAWAGU)||
	///<ため系の技の時は、コマンド選択なし
	   (sp->psp[client_no].condition2&CONDITION2_KEEP)){
		ret=FALSE;
	}

	return ret;
}

//============================================================================================
/**
 *	ポケモン捕獲情報のセット
 *
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
 *	@param[in]	pp	セットするPOKEMON_PARAM構造体
 */
//============================================================================================
void	ST_ServerPokemonGetParamSet(BATTLE_WORK *bw,SERVER_PARAM *sp,POKEMON_PARAM *pp)
{
	MYSTATUS	*status;
	int			place;
	int			ground_id;
	int			ballID;

	//MYSTATUSを取得
	status=BattleWorkMyStatusGet(bw,CLIENT_NO_MINE);

	//地域名IDを取得
	place=BattleWorkPlaceIDGet(bw);

	//地形アトリビュートを取得
	ground_id=BattleWorkGroundIDGet(bw);

	//ポケパークでは、捕獲ボールを変更しない
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
 *	クライアントからの返答を取り出す
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	取り出すクライアントナンバー
 */
//============================================================================================
u8	ST_ServerBufferResGet(SERVER_PARAM *sp,int client_no)
{
	return sp->server_buffer[client_no][0];
}

//============================================================================================
/**
 *	みがわりでふせげるかチェック
 *
 *	@param[in]	sp			サーバパラメータ構造体のポインタ
 *	@param[in]	client_no	チェックするクライアントナンバー
 *
 *　@retval FALSE:防がない　TRUE:防ぐ
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
 *	自分のポケモンかチェック
 *
 *	@param[in]	bw	戦闘システムワーク構造体のポインタ
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
 *
 *　@retval FALSE:他人のポケモン　TRUE:自分のポケモン
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
 *	自分のポケモンかチェック
 *
 *	@param[in]	bw	戦闘システムワーク構造体のポインタ
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
 *
 *　@retval FALSE:他人のポケモン　TRUE:自分のポケモン
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
 *	特性てんきやチェック（ポケモン名：チェリシュも同様の動きをするのであわせてチェック）
 *
 *	@param[in]	bw	戦闘システムワーク構造体のポインタ
 *	@param[in]	sp	サーバパラメータ構造体のポインタ
 *
 *　@retval FALSE:てんきやなし　TRUE:てんきや発動
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
 *	ListRowの初期化をする
 *
 * @param[in]	bw			戦闘パラメータの構造体ポインタ
 * @param[in]	sp			サーバパラメータの構造体ポインタ
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
 *	ListRowの入れ替えをする
 *
 * @param[in]	bw			戦闘パラメータの構造体ポインタ
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	入れ替え対象ClientNo
 * @param[in]	sel_mons_no	入れ替え対象ポケモン位置
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

	//先頭といれかえる
	work=sp->list_row[client_no][fb_flag];
	sp->list_row[client_no][fb_flag]=sp->list_row[client_no][pos];
	sp->list_row[client_no][pos]=work;
}

//============================================================================================
/**
 * 構造体定義
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
 *	装備効果による技タイプ攻撃力アップテーブル
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
 *	abiritycntによるパラメータ増減テーブル
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
 *	特性てつのこぶし用テーブル
 */
//============================================================================================
static	const	u16	TetsunoKobushiTable[]={
	WAZANO_REITOUPANTI,		//れいとうパンチ
	WAZANO_HONOONOPANTI,	//ほのおのパンチ
	WAZANO_KAMINARIPANTI,	//かみなりパンチ
	WAZANO_MAHHAPANTI,		//マッハパンチ
	WAZANO_KIAIPANTI,		//きあいパンチ
	WAZANO_PIYOPIYOPANTI,	//ピヨピヨパンチ
	WAZANO_BAKURETUPANTI,	//ばくれつパンチ
	WAZANO_AAMUHANMAA,		//アームハンマー
	WAZANO_MEGATONPANTI,	//メガトンパンチ
	WAZANO_RENZOKUPANTI,	//れんぞくパンチ
	WAZANO_KOMETTOPANTI,	//コメットパンチ
	WAZANO_SYADOOPANTI,		//シャドーパンチ
	WAZANO_DOREINPANTI,		//ドレインパンチ
	WAZANO_BARETTOPANTI,	//バレットパンチ
	WAZANO_SUKAIAPPAA,		//スカイアッパー
};

//============================================================================================
/**
 *	技のダメージ計算をする。
 *
 * @param[in]	pspa		技を出したポケモンの構造体のポインタ
 * @param[in]	pspd		技を受けるポケモンの構造体のポインタ
 * @param[in]	wazano		計算する技ナンバー
 * @param[in]	side_cond	場にかかっている効果
 * @param[in]	pow			技の威力(0:テーブルを参照　0以外:その値を参照)
 * @param[in]	type		技のタイプ(0:テーブルを参照　0以外:その値を参照)
 * @param[in]	attack		攻撃側のクライアントナンバー
 * @param[in]	defence		防御側のクライアントナンバー
 * @param[in]	critical	急所に当たったかどうか(1:通常　2以上:クリティカル）
 *
 *	@retval	計算結果のダメージ量
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

	//特性ノーマルスキンは、技タイプをノーマルにする
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
	wazapow=wazapow*sp->damage_value/10;	//技によるダメージ倍率ワークによる威力アップ計算

	//じゅうでん中は雷属性はダメージ2倍
	if((sp->psp[attack].waza_kouka&WAZAKOUKA_JUUDEN)&&
	   (wazatype==ELECTRIC_TYPE)){	
		wazapow*=2;
	}

	//てだすけ中はダメージ1.5倍
	if(sp->otf[attack].tedasuke_flag){	
		wazapow=wazapow*15/10;
	}

	//特性テクニシャンは、威力50以下の技を1.5倍にする（わるあがきは、除外）
	if((wdcp_a.speabino==TOKUSYU_TEKUNISYAN)&&
	   (wazano!=WAZANO_WARUAGAKI)&&
	   (wazapow<=60)){
		wazapow=wazapow*15/10;
	}

	wazakind=sp->AIWT.wtd[wazano].kind;

	//特性ちからもちは、ヨガパワーは、攻撃力を倍
	if((wdcp_a.speabino==TOKUSYU_TIKARAMOTI)||(wdcp_a.speabino==TOKUSYU_YOGAPAWAA)){
		pokepow=pokepow*2;
	}

	//特性スロースタートは、場にでてから5ターン以内は、攻撃力を半分にする
	if((wdcp_a.speabino==TOKUSYU_SUROOSUTAATO)&&
	  ((ST_ServerParamDataGet(bw,sp,ID_SP_total_turn,NULL)-
		ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_wkw_slow_start_count,NULL))<5)){
		pokepow/=2;
	}

	//アイテムで技タイプによる威力アップの装備効果のときは、威力％分攻撃力アップ
	for(i=0;i<NELEMS(SoubiItemWazaTypePowUpTbl);i++){
		if((wdcp_a.eqp==SoubiItemWazaTypePowUpTbl[i][0])&&(wazatype==SoubiItemWazaTypePowUpTbl[i][1])){
			wazapow=wazapow*(100+wdcp_a.atc)/100;
			break;
		}
	}

	//アイテムで同じ技しかだせないの装備効果のときは、攻撃力1.5倍アップ
	if(wdcp_a.eqp==SOUBI_ONAZIWAZAONLY){
		pokepow=pokepow*150/100;
	}
	//アイテムで同じ技しかだせないの装備効果のときは、特攻1.5倍アップ
	if(wdcp_a.eqp==SOUBI_ONAZIAWZAONLYTOKUSYUUP){
		pokespepow=pokespepow*150/100;
	}

	//アイテムで特攻＆特防を1.5倍の装備効果のときは、特攻＆特防1.5倍アップ
	if((wdcp_a.eqp==SOUBI_TOKUKOUTOKUBOUUP)&&
	  ((fight_type&FIGHT_TYPE_TOWER)==0)&&
	  ((wdcp_a.monsno==MONSNO_RATHIOSU)||(wdcp_a.monsno==MONSNO_RATHIASU))){
		pokespepow=pokespepow*150/100;
	}

	//アイテムで特攻＆特防を1.5倍の装備効果のときは、特攻＆特防1.5倍アップ
	if((wdcp_d.eqp==SOUBI_TOKUKOUTOKUBOUUP)&&
	  ((fight_type&FIGHT_TYPE_TOWER)==0)&&
	  ((wdcp_d.monsno==MONSNO_RATHIOSU)||(wdcp_d.monsno==MONSNO_RATHIASU))){
		pokespedef=pokespedef*150/100;
	}

	//アイテムでパールルが持つと特攻を2倍の装備効果のときは、特攻2倍アップ
	if((wdcp_a.eqp==SOUBI_PAARURUTOKUKOUNIBAI)&&
	   (wdcp_a.monsno==MONSNO_PAARURU)){
		pokespepow*=2;
	}

	//アイテムでパールルが持つと特防を2倍の装備効果のときは、特防2倍アップ
	if((wdcp_d.eqp==SOUBI_PAARURUTOKUBOUNIBAI)&&
	   (wdcp_d.monsno==MONSNO_PAARURU)){
		pokespedef*=2;
	}

	//アイテムでピカチュウが持つと威力2倍の装備効果のときは、威力2倍アップ
	if((wdcp_a.eqp==SOUBI_PIKATYUUTOKUKOUNIBAI)&&
	   (wdcp_a.monsno==MONSNO_PIKATYUU)){
		wazapow*=2;
	}

	//アイテムでメタモンが持つと防御力を2倍の装備効果のときは、防御力2倍アップ
	if((wdcp_d.eqp==SOUBI_METAMONDATOBOUGYORYOKUUP)&&
	   (wdcp_d.monsno==MONSNO_METAMON)){
		pokedef*=2;
	}

	//アイテムでカラカラ、ガラガラが持つと攻撃力を2倍の装備効果のときは、攻撃力2倍アップ
	if((wdcp_a.eqp==SOUBI_KARAGARADATOKOUGEKINIBAI)&&
	  ((wdcp_a.monsno==MONSNO_KARAKARA)||
	   (wdcp_a.monsno==MONSNO_GARAGARA))){
		pokepow*=2;
	}

	//アイテムでディアルガが持つと技の威力を1.5倍
	if((wdcp_a.eqp==SOUBI_DORAGONHAGANEUP)&&
	  ((wazatype==DRAGON_TYPE)||(wazatype==METAL_TYPE))&&
	   (wdcp_a.monsno==MONSNO_IA)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//アイテムでパルキアが持つと技の威力を1.5倍
	if((wdcp_a.eqp==SOUBI_DORAGONMIZUUP)&&
	  ((wazatype==DRAGON_TYPE)||(wazatype==WATER_TYPE))&&
	   (wdcp_a.monsno==MONSNO_EA)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//アイテムで、物理攻撃の威力をアップの時は、威力をアップ
	if((wdcp_a.eqp==SOUBI_BUTURIIRYOKUUP)&&(wazakind==KIND_BUTSURI)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//アイテムで、特殊攻撃の威力をアップの時は、威力をアップ
	if((wdcp_a.eqp==SOUBI_TOKUSYUIRYOKUUP)&&(wazakind==KIND_TOKUSYU)){
		wazapow=wazapow*(100+wdcp_a.atc)/100;
	}

	//特殊能力あついしぼうは、ほのお、こおりにつよい
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_ATUISIBOU)==TRUE)&&
	  ((wazatype==FIRE_TYPE)||(wazatype==KOORI_TYPE))){
		wazapow/=2;
	}

	//特殊能力はりきりは、攻撃力1.5倍アップ
	if(wdcp_a.speabino==TOKUSYU_HARIKIRI){
		pokepow=pokepow*150/100;
	}

	//特殊能力こんじょうは、状態異常のときに攻撃力1.5倍アップ
	if((wdcp_a.speabino==TOKUSYU_KONZYOU)&&(wdcp_a.condition)){
		pokepow=pokepow*150/100;
	}

	//特殊能力ふしぎなうろこは、状態異常のときに防御力1.5倍アップ
	if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_HUSIGINAUROKO)==TRUE)&&(wdcp_d.condition)){
		pokedef=pokedef*150/100;
	}

	//特殊能力プラス、マイナスはお互いが場にいると特殊攻撃力を1.5倍アップ
	if((wdcp_a.speabino==TOKUSYU_PURASU)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_MINE_SIDE_HP,attack,TOKUSYU_MAINASU))){
		pokespepow=pokespepow*150/100;
	}
	if((wdcp_a.speabino==TOKUSYU_MAINASU)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_MINE_SIDE_HP,attack,TOKUSYU_PURASU))){
		pokespepow=pokespepow*150/100;
	}

	//技効果どろあそびは、電気系の技の威力を半減
	if((wazatype==ELECTRIC_TYPE)&&(ST_ServerWazaKoukaCheck(bw,sp,WAZAKOUKA_DOROASOBI))){
		wazapow/=2;
	}

	//技効果みずあそびは、炎系の技の威力を半減
	if((wazatype==FIRE_TYPE)&&(ST_ServerWazaKoukaCheck(bw,sp,WAZAKOUKA_MIZUASOBI))){
		wazapow/=2;
	}

	//特殊能力しんりょくはHP1/3以下で草タイプの威力を1.5倍にする
	if((wazatype==KUSA_TYPE)&&(wdcp_a.speabino==TOKUSYU_SINRYOKU)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}

	//特殊能力もうかはHP1/3以下で炎タイプの威力を1.5倍にする
	if((wazatype==FIRE_TYPE)&&(wdcp_a.speabino==TOKUSYU_MOUKA)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}

	//特殊能力げきりゅうはHP1/3以下で水タイプの威力を1.5倍にする
	if((wazatype==WATER_TYPE)&&(wdcp_a.speabino==TOKUSYU_GEKIRYUU)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}
	//特殊能力むしのしらせはHP1/3以下で虫タイプの威力を1.5倍にする
	if((wazatype==MUSHI_TYPE)&&(wdcp_a.speabino==TOKUSYU_MUSINOSIRASE)&&(wdcp_a.hp<=(wdcp_a.hpmax/3))){
		wazapow=wazapow*150/100;
	}
	//特性たいねつは、炎系の技の威力を半減
	if((wazatype==FIRE_TYPE)&&(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TAINETU)==TRUE)){
		wazapow/=2;
	}
	//特性かんそうはだは、炎系の技の威力を25%増
	if((wazatype==FIRE_TYPE)&&(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_KANSOUHADA)==TRUE)){
		wazapow=wazapow*125/100;
	}
	//特性たんじゅんは、能力変化値を倍
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
	//特性たんじゅんは、能力変化値を倍
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

	//特性てんねんは、能力変化値をフラット
	if(ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_TENNEN)==TRUE){
		condpow=0;
		condspepow=0;
	}
	//特性てんねんは、能力変化値をフラット
	if(wdcp_a.speabino==TOKUSYU_TENNEN){
		conddef=0;
		condspedef=0;
	}

	condpow+=6;
	conddef+=6;
	condspepow+=6;
	condspedef+=6;

	//特性とうそうしんは、性別が一緒だったら1.25倍にする
	if((wdcp_a.speabino==TOKUSYU_TOUSOUSIN)&&
	   (wdcp_a.sex==wdcp_d.sex)&&(wdcp_a.sex!=PARA_UNK)&&(wdcp_d.sex!=PARA_UNK)){
		wazapow=wazapow*125/100;
	}
	//特性とうそうしんは、性別が違ったら0.75倍にする
	if((wdcp_a.speabino==TOKUSYU_TOUSOUSIN)&&
	   (wdcp_a.sex!=wdcp_d.sex)&&(wdcp_a.sex!=PARA_UNK)&&(wdcp_d.sex!=PARA_UNK)){
		wazapow=wazapow*75/100;
	}

	//特性てつのこぶしは、パンチ系の技の威力を1.2倍にする
	for(i=0;i<NELEMS(TetsunoKobushiTable);i++){
		if((TetsunoKobushiTable[i]==wazano)&&(wdcp_a.speabino==TOKUSYU_TETUNOKOBUSI)){
			wazapow=wazapow*12/10;
			break;
		}
	}

	//天候チェック（のうてんきのポケモンが戦闘に出ている場合は天候チェックしない）
	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//特性サンパワーは、はれの時、特攻を1.5倍にする
		if((field_cond&FIELD_CONDITION_HARE_ALL)&&(wdcp_a.speabino==TOKUSYU_SANPAWAA)){
			pokespepow=pokespepow*15/10;
		}
		//岩タイプは、すなあらしの時、特防を1.5倍にする
		if((field_cond&FIELD_CONDITION_SUNAARASHI_ALL)&&
		  ((wdcp_d.type1==IWA_TYPE)||(wdcp_d.type2==IWA_TYPE))){
			pokespedef=pokespedef*15/10;
		}
		//特性フラワーギフトは、天候が晴れのとき、自分と味方の攻撃と特防を1.5倍する。
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

	//「じばく」「だいばくはつ」は、防御力を半分にして計算する
	if(sp->AIWT.wtd[wazano].battleeffect==7){
		pokedef=pokedef/2;
	}

	if(wazakind==KIND_BUTSURI){	//物理攻撃
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

		//特殊能力こんじょうは、状態異常で攻撃力をあげるのでこの判定は無視
		if((wdcp_a.condition&CONDITION_YAKEDO)&&(wdcp_a.speabino!=TOKUSYU_KONZYOU)){
			damage/=2;
		}

		//戦闘効果186はガードの影響を受けない
		if(((side_cond&SIDE_CONDITION_BUTSURIGUARD)!=0)&&(critical==1)&&(sp->AIWT.wtd[wazano].battleeffect!=186)){
			if((fight_type&FIGHT_TYPE_2vs2)&&(ST_ServerHitCountCheck(bw,sp,SHCC_SIDE,defence)==2)){
				damage=damage*2/3;
			}
			else{
				damage/=2;
			}
		}
	}
	else if(wazakind==KIND_TOKUSYU){			//特殊攻撃
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

		//戦闘効果186はガードの影響を受けない
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

	//天候チェック（のうてんきのポケモンが戦闘に出ている場合は天候チェックしない）
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

	//特殊能力もらいびチェック
	if((ST_ServerPokemonServerParamGet(sp,attack,ID_PSP_wkw_moraibi_flag,NULL))&&(wazatype==FIRE_TYPE)){
		damage=damage*15/10;
	}

	return	damage+2;
}

// =================================================================
// void	WS_DAMAGE_LOSS
// 概要  : ダメージ計算で求めた値を85%～100%の範囲で調整する
// 引数  : none
// 戻り値: none
// =================================================================
int		ST_DamageLossCalc(SERVER_PARAM *sp,int damage)
{
#ifdef PM_DEBUG
	//デバッグモードでダメージ固定フラグが立っている場合は、LossCalcはしない
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
 *	クリティカルヒットがでる確率テーブル
 */
//============================================================================================
static	const	u8	CriticalTable[]={
	16,8,4,3,2
};

//============================================================================================
/**
 *	急所に当たるかどうかのチェック
 *
 * @param[in]	sp				サーバパラメータ構造体のポインタ
 * @param[in]	attack			攻撃側ClientNo
 * @param[in]	defence			防御側ClientNo
 * @param[in]	critical_count	クリティカルヒットの倍率を変動させるワーク
 *
 * @retval	1:ダメージ倍率1倍	2:ダメージ倍率2倍
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
		 //特性きょううんは、急所ヒット段階を１アップする
		 (speabi==TOKUSYU_KYOUUN)+
		 (2*((eqp==SOUBI_RAKKIIDATOKYUUSYONIATARIYASUI)&&(monsno==MONSNO_RAKKII)))+
		 (2*((eqp==SOUBI_KAMONEGIKYUUSYOATARIYASUI)&&(monsno==MONSNO_KAMONEGI)));

	if(work>4){
		work=4;
	}

	if(gf_rand()%CriticalTable[work]==0){
		//特性カブトアーマー、シェルアーマーがあるときは急所にあたらない
		if((ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_KABUTOAAMAA)==FALSE)&&
		   (ST_ServerKatayaburiTokuseiCheck(sp,attack,defence,TOKUSYU_SHERUAAMAA)==FALSE)&&
		  ((side_condition&SIDE_CONDITION_OMAZINAI)==0)&&
		  ((waza_kouka&WAZAKOUKA_NOCRITICAL)==0)){
			ret=2;
		}
	}

	//特性スナイパーは、急所倍率を3倍にする
	if((ret==2)&&(ST_ServerTokuseiGet(sp,attack)==TOKUSYU_SUNAIPAA)){
		ret=3;
	}

	return ret;
}

//============================================================================================
/**
 * 特殊な技テーブル
 */
//============================================================================================
#define	MONOMANE_NG_TBL_END	(0xfffe)
#define	WAZA_OUT_NG_TBL_END	(0xffff)

static	const u16 WazaOutNGTbl[]={
	WAZANO_YUBIWOHURU,			// ゆびをふる
	WAZANO_WARUAGAKI,			// わるあがき
	WAZANO_SUKETTI,				// スケッチ
	WAZANO_MONOMANE,			// ものまね
	WAZANO_OSYABERI,			// おしゃべり
	MONOMANE_NG_TBL_END,		// ものまねできないテーブルのエンド
	WAZANO_NEGOTO,				// ねごと
	WAZANO_NEKONOTE,			// ねこのて
	WAZANO_OUMUGAESI,			// オウムがえし
	WAZANO_KAUNTAA,				// カウンター
	WAZANO_MIRAAKOOTO,			// ミラーコート
	WAZANO_MAMORU,				// まもる
	WAZANO_MIKIRI,				// みきり
	WAZANO_KORAERU,				// こらえる
	WAZANO_MITIDURE,			// みちづれ
	WAZANO_DOROBOU,				// どろぼう
	WAZANO_KONOYUBITOMARE,		// このゆびとまれ
	WAZANO_YOKODORI,			// よこどり
	WAZANO_TEDASUKE,			// てだすけ
	WAZANO_HOSIGARU,			// ほしがる
	WAZANO_TORIKKU,				// トリック
	WAZANO_KIAIPANTI,			// きあいパンチ
	WAZANO_FEINTO,				// フェイント
	WAZANO_MANEKKO,				// まねっこ
	WAZANO_SAKIDORI,			// さきどり
	WAZANO_SURIKAE,				// すりかえ
	WAZA_OUT_NG_TBL_END
};

//============================================================================================
/**
 *	ものまねできる技かチェック
 *
 * @param[in]	waza_no		チェックする技ナンバー
 *
 * @retval	FALSE:できない　TRUE:できる
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
 *	ゆびをふるでだせる技かチェック
 *
 * @param[in]	waza_no		チェックする技ナンバー
 *
 * @retval	FALSE:出せない　TRUE:出せる
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
 *	オウムがえしで返せるか、アンコール出来る技かチェック用技ナンバーテーブル
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
 *	オウムがえしで返せるか、アンコール出来る技かチェック
 *
 * @param[in]	waza_no		チェックする技ナンバー
 *
 * @retval	FALSE:出せない　TRUE:出せる
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
 *	さきどり成功する技かチェック用技ナンバーテーブル
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
 *	さきどり成功する技かチェック
 *
 * @param[in]	waza_no		チェックする技ナンバー
 *
 * @retval	FALSE:出せない　TRUE:出せる
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
 *	アイテムパラメータの取得
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	item_no		取得したいアイテムナンバー
 * @param[in]	param		取得したいパラメータのID
 *
 * @retval	値
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
 *	dirパラメータからClientNoを取得
 *
 * @param[in]	bw		戦闘システム構造体ポインタ
 * @param[in]	sp		サーバパラメータの構造体ポインタ
 * @param[in]	dir		取得したいClientNoの向き
 *
 * @retval	値
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
 *	トリックルーム効果
 *
 * @param[in]	bw		戦闘システム構造体ポインタ
 * @param[in]	sp		サーバパラメータの構造体ポインタ
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
 *	みがわりがいるかチェックして、STATUS_EFFECTが発動できるか判断用テーブル
 */
//============================================================================================
static	const	int	MigawariOKStatusEffect[]={
	STATUS_EFF_MIGAWARI_OUT,	///< o画面外に
	STATUS_EFF_MIGAWARI_IN,		///< o画面内に
	STATUS_EFF_ITEM_POUCH,		///< oエネコしっぽとピッピ人形
	STATUS_WEATHER_MIST,		///< 天候 霧
	STATUS_WEATHER_RAIN,		///< 天候 雨
	STATUS_WEATHER_ICE,			///< 天候 あられ
	STATUS_WEATHER_SAND,		///< 天候 砂あらし
	STATUS_WEATHER_SUN,			///< 天候 ひざし
	STATUS_ACTION_DOLL_ON,		///< o動き みがわりおちてくる
	STATUS_ACTION_DOLL_OFF,		///< 動き みがわりOFF
};

//============================================================================================
/**
 *	みがわりがいるかチェックして、STATUS_EFFECTが発動できるか判断
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	チェックしたいClientNo
 * @param[in]	status		チェックしたいSTATUS_EFFECTナンバー
 *
 * @retval	FALSE:発動できない　TRUE:発動できる
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
 *	攻撃がヒットした時にチェックする装備効果（とんぼがえり限定）
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	チェックしたいClientNo
 * @param[in]	status		チェックしたいSTATUS_EFFECTナンバー
 *
 * @retval	FALSE:発動できない　TRUE:発動できる
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
		//特性マジックガードはダメージなし
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
		//特性マジックガードには不発
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
 *	攻撃対象がプレッシャーを持っているかチェックしてPPを減らす
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	attack		攻撃側ClientNo
 * @param[in]	defence		防御側ClientNo
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
//			パラメータゲット系
//============================================================================================
//============================================================================================
/**
 *	SERVER_PARAM構造体のメンバの値を取得
 *
 * @param[in]	bw			戦闘パラメータの構造体ポインタ
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	id			取得したいメンバのインデックス
 * @param[in]	client_no	取得したいメンバのClientNo（必要な場合）
 *
 * @retval	値
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
	GF_ASSERT_MSG((0),"定義されていないIDです\n");
	return 0;
}

//============================================================================================
//			パラメータセット系
//============================================================================================
//============================================================================================
/**
 *	ostf_status_flagをセット
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	client_no	セットするClientNo
 * @param[in]	value		セットする値
 */
//============================================================================================
void	ST_ServerOSTFStatusFlagSet(SERVER_PARAM *sp,int client_no,u32 value)
{
	sp->ostf[client_no].status_flag|=value;
}

//============================================================================================
/**
 *	SERVER_PARAMのメンバに値をセット
 *
 * @param[in]	bw			戦闘パラメータの構造体ポインタ
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	id			セットしたいメンバのインデックス
 * @param[in]	client_no	セットしたいメンバのClientNo（必要な場合）
 * @param[in]	data		セットする値
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
		GF_ASSERT_MSG((0),"定義されていないIDです\n");
		break;
	}
}

//============================================================================================
//			外部公開しない系
//============================================================================================
//============================================================================================
//			追加効果動作をするシーケンスナンバーテーブル
//============================================================================================
static const int AddStatusSeqNoTable[]=
{
	NULL,		//ダミー
	SUB_SEQ_NEMURI,				//ねむり
	SUB_SEQ_DOKU,				//毒
	SUB_SEQ_YAKEDO,				//やけど
	SUB_SEQ_KOORI,				//こおり
	SUB_SEQ_MAHI,				//まひ
	SUB_SEQ_DOKUDOKU,			//どくどく
	SUB_SEQ_KONRAN,				//こんらん
	SUB_SEQ_HIRUMU,				//ひるむ
	SUB_SEQ_NEMURU,				//ねむる
	SUB_SEQ_SAWAGU,				//さわぐ
	SUB_SEQ_NEKONIKOBAN,		//ねこにこばん
	SUB_SEQ_KEEP,				//ため系の技
	SUB_SEQ_SHIME,				//しめ系の技
	SUB_SEQ_HANEKAERI,			//はねかえり系の技(1/4)
	SUB_SEQ_ABICNT_CALC,		//攻撃力アップ
	SUB_SEQ_ABICNT_CALC,		//防御力アップ
	SUB_SEQ_ABICNT_CALC,		//素早さアップ
	SUB_SEQ_ABICNT_CALC,		//特攻アップ
	SUB_SEQ_ABICNT_CALC,		//特防アップ
	SUB_SEQ_ABICNT_CALC,		//命中率アップ
	SUB_SEQ_ABICNT_CALC,		//回避率アップ
	SUB_SEQ_ABICNT_CALC,		//攻撃力ダウン
	SUB_SEQ_ABICNT_CALC,		//防御力ダウン
	SUB_SEQ_ABICNT_CALC,		//素早さダウン
	SUB_SEQ_ABICNT_CALC,		//特攻ダウン
	SUB_SEQ_ABICNT_CALC,		//特防ダウン
	SUB_SEQ_ABICNT_CALC,		//命中率ダウン
	SUB_SEQ_ABICNT_CALC,		//回避率ダウン
	SUB_SEQ_HANDOU,				//はんどう
	SUB_SEQ_IKARI,				//いかり
	SUB_SEQ_DOROBOU,			//どろぼう
	SUB_SEQ_KUROIMANAZASI,		//くろいまなざし
	SUB_SEQ_AKUMU,				//あくむ
	SUB_SEQ_GENSHINOCHIKARA,	//げんしのちから
	SUB_SEQ_KOUSOKUSPIN,		//こうそくスピン
	SUB_SEQ_NO_MAHI,			//まひをなおす
	SUB_SEQ_BAKADIKARA,			//ばかぢから
	SUB_SEQ_HANEKAERI2,			//はねかえり系の技(1/3)
	SUB_SEQ_ABICNT_CALC,		//攻撃力アップ(2段階）
	SUB_SEQ_ABICNT_CALC,		//防御力アップ(2段階）
	SUB_SEQ_ABICNT_CALC,		//素早さアップ(2段階）
	SUB_SEQ_ABICNT_CALC,		//特攻アップ(2段階）
	SUB_SEQ_ABICNT_CALC,		//特防アップ(2段階）
	SUB_SEQ_ABICNT_CALC,		//命中率アップ(2段階）
	SUB_SEQ_ABICNT_CALC,		//回避率アップ(2段階）
	SUB_SEQ_ABICNT_CALC,		//攻撃力ダウン(2段階）
	SUB_SEQ_ABICNT_CALC,		//防御力ダウン(2段階）
	SUB_SEQ_ABICNT_CALC,		//素早さダウン(2段階）
	SUB_SEQ_ABICNT_CALC,		//特攻ダウン(2段階）
	SUB_SEQ_ABICNT_CALC,		//特防ダウン(2段階）
	SUB_SEQ_ABICNT_CALC,		//命中率ダウン(2段階）
	SUB_SEQ_ABICNT_CALC,		//回避率ダウン(2段階）
	SUB_SEQ_ABARERU,			//あばれる
	SUB_SEQ_HATAKIOTOSU,		//はたきおとす
	SUB_SEQ_COSMO_POWER,		//コスモパワー（複数アップ（abiritycnt系））
	SUB_SEQ_BUILD_UP,			//ビルドアップ（複数アップ（abiritycnt系））
	SUB_SEQ_KUSUGURU,			//くすぐる（複数ダウン（abiritycnt系））
	SUB_SEQ_MEISOU,				//めいそう（複数アップ（abiritycnt系））
	SUB_SEQ_RYUUNOMAI,			//りゅうのまい（複数アップ（abiritycnt系））
	SUB_SEQ_SUITORI,			//HPすいとり系
	SUB_SEQ_YUMEKUI,			//ゆめくい
	SUB_SEQ_KUROIKIRI,			//くろいきり
	SUB_SEQ_GAMAN,				//がまん
	SUB_SEQ_WARUAGAKI,			//わるあがき
	SUB_SEQ_TEXTURE,			//テクスチャ
	SUB_SEQ_JIKOSAISEI,			//じこさいせい
	SUB_SEQ_HIKARINOKABE,		//ひかりのかべ
	SUB_SEQ_RIHUREKUTAA,		//リフレクター
	SUB_SEQ_SIROIKIRI,			//しろいきり
	SUB_SEQ_KIAIDAME,			//きあいだめ
	SUB_SEQ_MONOMANE,			//ものまね
	SUB_SEQ_YADORIGI,			//やどりぎのたね
	SUB_SEQ_KANASIBARI,			//かなしばり
	SUB_SEQ_ENCORE,				//アンコール
	SUB_SEQ_ITAMIWAKE,			//いたみわけ
	SUB_SEQ_TEXTURE2,			//テクスチャ２
	SUB_SEQ_LOCKON,				//ロックオン
	SUB_SEQ_SKETCH,				//スケッチ
	SUB_SEQ_FEINT,				//フェイント
	SUB_SEQ_MICHIDURE,			//みちづれ
	SUB_SEQ_URAMI,				//うらみ
	SUB_SEQ_GUARD,				//まもる、みきる、こらえるなど
	SUB_SEQ_IYASINOSUZU,		//いやしのすず
	SUB_SEQ_MIGAWARI,			//みがわり
	SUB_SEQ_HUKITOBASI,			//ふきとばし
	SUB_SEQ_HENSIN,				//へんしん
	SUB_SEQ_CHIISAKUNARU,		//ちいさくなる
	SUB_SEQ_NORMAL_NOROI,		//のろい（ノーマル）
	SUB_SEQ_GHOST_NOROI,		//のろい（ゴースト）
	SUB_SEQ_ADD_MESSAGE_WORK,	//メッセージ表示
	SUB_SEQ_MIYABURU,			//みやぶる
	SUB_SEQ_HOROBINOUTA,		//ほろびのうた
	SUB_SEQ_TENKOU,				//天候系
	SUB_SEQ_IBARU,				//いばる
	SUB_SEQ_MEROMERO,			//メロメロ
	SUB_SEQ_SHINPI,				//しんぴのまもり
	SUB_SEQ_PRESENT,			//プレゼント
	SUB_SEQ_MAGNITUDE,			//マグニチュード
	SUB_SEQ_BATONTOUCH,			//バトンタッチ
	SUB_SEQ_HARADAIKO,			//はらだいこ
	SUB_SEQ_TELEPORT,			//テレポート
	SUB_SEQ_HUKURODATAKI,		//ふくろだたき
	SUB_SEQ_TAKUWAERU,			//たくわえる
	SUB_SEQ_NOMIKOMU,			//のみこむ
	SUB_SEQ_ICHAMON,			//いちゃもん
	SUB_SEQ_ODATERU,			//おだてる
	SUB_SEQ_OKIMIYAGE,			//おきみやげ
	SUB_SEQ_JUUDEN,				//じゅうでん
	SUB_SEQ_CHOUHATSU,			//ちょうはつ
	SUB_SEQ_TRICK,				//トリック
	SUB_SEQ_NARIKIRI,			//なりきり
	SUB_SEQ_KAWARAWARI,			//かわらわり
	SUB_SEQ_AKUBI,				//あくび
	SUB_SEQ_SKILLSWAP,			//スキルスワップ
	SUB_SEQ_REFRESH,			//リフレッシュ
	SUB_SEQ_HANEYASUME,			//はねやすめ
	SUB_SEQ_NO_NEMURI,			//めざましビンタ
	SUB_SEQ_JUURYOKU,			//じゅうりょく
	SUB_SEQ_MIRACLE_EYE,		//ミラクルアイ
	SUB_SEQ_IYASINONEGAI,		//いやしのねがい
	SUB_SEQ_OIKAZE,				//おいかぜ
	SUB_SEQ_INFIGHT,			//インファイト
	SUB_SEQ_POWER_TRICK,		//パワートリック
	SUB_SEQ_IEKI,				//いえき
	SUB_SEQ_OMAZINAI,			//おまじない
	SUB_SEQ_POWER_SWAP,			//パワースワップ
	SUB_SEQ_GUARD_SWAP,			//ガードスワップ
	SUB_SEQ_NAYAMINOTANE,		//なやみのたね
	SUB_SEQ_HEART_SWAP,			//ハートスワップ
	SUB_SEQ_HEAT_ATTACK,		//ヒートアタック
	SUB_SEQ_KIRIHARAI,			//きりはらい
	SUB_SEQ_HEALBLOCK,			//ヒールブロック
	SUB_SEQ_TONBOGAERI,			//とんぼがえり
	SUB_SEQ_SHUTOUT,			//シャットアウト
	SUB_SEQ_TSUIBAMU,			//ついばむ
	SUB_SEQ_NAGETSUKERU,		//なげつける
	SUB_SEQ_VOLT,				//ボルテッカー
	SUB_SEQ_HANEKAERI3,			//はねかえり系の技(1/2)
	SUB_SEQ_YAKEDO_HIRUMU,		//やけど＋ひるむの追加効果
	SUB_SEQ_KOORI_HIRUMU,		//こおり＋ひるむの追加効果
	SUB_SEQ_MAHI_HIRUMU,		//まひ＋ひるむの追加効果
	SUB_SEQ_OSYABERI,			//おしゃべりの追加効果
	SUB_SEQ_MIKADUKINOMAI,		//みかづきのまい追加効果
	SUB_SEQ_SURIKOMI,			//すりこみ追加効果
};

//============================================================================================
/**
 *	追加効果をするためのパラメータをセット
 *
 * @param[in]	sp		サーバパラメータの構造体ポインタ
 * @param[in]	type	追加効果のタイプ
 * @param[in]	flag	追加効果の種類
 *
 * @retval	追加効果動作をするシーケンスナンバー
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
		OS_TPrintf("ST_ServerAddStausParamSet:ここにくるのはおかしい->%08x\n",flag);
	}

	GF_ASSERT_MSG(NELEMS(AddStatusSeqNoTable)>(flag&ADD_STATUS_MASK),"存在しないSUB_SEQ_NOです");

	return AddStatusSeqNoTable[flag&ADD_STATUS_MASK];
}

//============================================================================================
/**
 *	ポケモンと技のタイプの相性でフラグをセット
 *
 * @param[in]	client_no	技を繰り出すClientNo
 * @param[in]	power		相性を示す威力
 * @param[in]	damage		蓄積されているダメージ
 * @param[in]	waza_damage	技の威力
 * @param[out]	flag		フラグをセットするワーク
 */
//============================================================================================
static	int	ST_TypeCheckCalc(SERVER_PARAM *sp,int client_no,int power,int damage,int waza_damage,u32 *flag)
{
	//タイプによる補正計算
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
 *	ため技が発動するターンなのかチェック（ため技以外は強制的に発動扱い）
 *
 * @param[in]	waza_no		チェックする技ナンバー
 *
 * @retval	TRUE：発動　FALSE:ためるターン
 */
//============================================================================================
static BOOL	ST_TameWazaTurnCheck(SERVER_PARAM *sp,int waza_no)
{
	switch(sp->AIWT.wtd[waza_no].battleeffect){
	case 26:	//がまん
	case 39:	//かまいたち
	case 75:	//ゴッドバード
	case 145:	//ロケット頭突き
	case 151:	//ソーラービーム
	case 155:	//そらをとぶ
	case 255:	//ダイビング
	case 256:	//あなをほる
	case 263:	//とびはねる
	case 273:	//シャドーダイブ
		return (sp->server_status_flag&SERVER_STATUS_FLAG_TAME_AFTER);
		break;
	}

	return TRUE;
}

//============================================================================================
/**
 *	ポケモンナンバーと特性をチェックして取得すべきタイプを返す
 *
 * @param[in]	sp		サーバワーク構造体
 * @param[in]	client	取得するClientNo
 * @param[in]	id		取得するタイプ（ID_PSP_type1 or ID_PSP_type2）
 *
 * @retval	TRUE：発動　FALSE:ためるターン
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
	
	//アウスが特性マルチタイプを持っているときは、装備道具によってタイプを変える
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
 *	技ナンバーストック用ワークの初期化
 *
 * @param[in]	sp			サーバ用パラメータワーク構造体
 * @param[in]	client_no	クリアするClientNo
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
 *	AI用特性ワークをクリア
 *
 * @param[in]	sp			サーバシステム構造体
 * @param[in]	client_no	クリアするClientNo
 */
//=========================================================================
static	void	TokusyuNoClear(SERVER_PARAM *sp,u8 client_no)
{
	sp->AIWT.AI_TOKUSYUNO[client_no]=0;
}

//=========================================================================
/**
 *	AI用装備アイテムワークをクリア
 *
 * @param[in]	sp			サーバシステム構造体
 * @param[in]	client_no	クリアするClientNo
 */
//=========================================================================
static	void	SoubiItemClear(SERVER_PARAM *sp,u8 client_no)
{
	sp->AIWT.AI_SOUBIITEM[client_no]=0;
}

//=========================================================================
/**
 *	トレースできる特性かチェックして発動できるかを返す
 *
 * @param[in]	sp		サーバシステム構造体
 * @param[in]	def1	チェック対象ClientNo
 * @param[in]	def2	チェック対象ClientNo
 *
 * @retval	発動対象ClientNo
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
 *	きけんよちで除外する戦闘効果ナンバーテーブル
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
 *	きけんよちで除外する戦闘効果ナンバーを調べる
 *
 * @param[in]	sp			サーバパラメータの構造体ポインタ
 * @param[in]	waza_no		チェックする技ナンバー
 *
 * @retval	FALSE:除外しない TRUE:除外する
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
 * 特殊な技のタイプを取得
 *
 * @param[in]	bw			戦闘システムワーク構造体のポインタ
 * @param[in]	sp			サーバシステムワーク構造体のポインタ
 * @param[in]	client_no	技を使用するClientNo
 * @param[in]	waza_no		タイプを取得する技ナンバー
 *
 * @retval	技タイプ
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

