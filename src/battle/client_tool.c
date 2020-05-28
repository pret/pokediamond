
//============================================================================================
/**
 * @file	client_tool.c
 * @bfief	戦闘クライアント用ツールプログラム
 * @author	HisashiSogabe
 * @date	05.07.21
 */
//============================================================================================

#include "common.h"

#include "system/procsys.h"
#include "system/gamedata.h"

#include "battle/battle_server.h"
#include "battle/client.h"
#include "battle/fight.h"
#include "battle/fight_tool.h"
#include "battle/server_tool.h"
#include "battle/client_tool.h"
#include "battle/ground.h"
#include "battle/scio.h"
#include "battle/tr_ai.h"
#include "battle/battle_id.h"
#include "battle/trtype_def.h"
#include "battle/wazano_def.h"

#include "poketool/poke_tool.h"
#include "poketool/tr_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"

#include "gflib/touchpanel.h"

#include "itemtool/item.h"
#include "itemtool/itemsym.h"
#include "itemtool/myitem.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/snd_tool.h"
#include "system/softsprite.h"
#include "system/gra_tool.h"
#include "system/snd_def.h"

#include "wazaeffect/we_sys.h"

#include "client_def.h"
#include "client_tool_def.h"

#include "b_plist.h"
#include "b_bag.h"
#include "gauge.h"
#include "battle/battle_tcb_pri.h"
#include "system/pm_str.h"
#include "system/msg_ds_icon.h"
#include "system/window.h"

#include "battle/graphic/batt_bg_def.h"

#include "wazaeffect/d_we.h"
#include "wazaeffect/d_tool.h"
#include "wazaeffect/ball_effect.h"
#include "wazaeffect/smptm_statuseffect.h"
#include "battle_input.h"

#include "msgdata/msg_fightmsg_dp.h"
#include "msgdata/msg_atkmsg.h"

#include "pokeanime/p_anm_sys.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "battle_snd_def.h"
#include "client_eff.h"

#include "battle/bc_common.h"
#include "temoti_gauge.h"
#include "system/arc_tool.h"
#include "poketool/pokegra/otherpoke.naix"

#ifdef PM_DEBUG
#include "debug/d_battle.h"
#endif PM_DEBUG

#define MSG_WINDOW_FADE		(7)		///<バッグ画面、ポケモンリスト画面に移行するときのメッセージウインドウのフェード値

//#define ENCOUNT_SKIP_ON				///<エンカウントエフェクトスキップ処理ON

//-----------------------------------------------------------------------------
//					プロトタイプ宣言
//-----------------------------------------------------------------------------

//技シーケンス系
void	CT_EncountEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_PokemonEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_ENCOUNT_PARAM *pep);
void	CT_PokemonEncountAppearSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_APPEAR_PARAM *pap);
void	CT_PokemonAppearSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_APPEAR_PARAM *pap);
void	CT_PokemonReturnSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_RETURN_PARAM *prp);
void	CT_PokemonInhaleSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_INHALE_PARAM *prp);
void	CT_TrainerEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_ENCOUNT_PARAM *tep);
void	CT_TrainerThrowSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_THROW_PARAM *ttp);
void	CT_TrainerOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_TrainerInSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_IN_PARAM *tip);
void	CT_HPGaugeInSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_IN_PARAM *hgip);
void	CT_HPGaugeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_CommandSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,COMMAND_SELECT_PARAM *csp);
void	CT_WazaSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_SELECT_PARAM *wsp);
void	CT_DirSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,DIR_SELECT_PARAM *dsp);
void	CT_ItemSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ITEM_SELECT_PARAM *isp);
void	CT_PokemonSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_SELECT_PARAM *psp);
void	CT_YesNoSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,YES_NO_SELECT_PARAM *ynsp);
void	CT_AttackMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ATTACK_MESSAGE_PARAM *amp);
void	CT_MessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *amp);
void	CT_WazaEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep);
void	CT_PokemonBlinkSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_HPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_CALC_PARAM *hgcp);
void	CT_EXPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,EXP_GAUGE_CALC_PARAM *egcp);
void	CT_KizetsuEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,KIZETSU_EFFECT_PARAM *kep);
void	CT_SePlaySet(BATTLE_WORK *bw,CLIENT_PARAM *cp,SE_PLAY_PARAM *spp);
void	CT_FadeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_PokemonVanishOnOff(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_VANISH_ON_OFF *pvoo);
void	CT_HPGaugeStatusSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_STATUS_SET_PARAM *hgssp);
void	CT_TrainerMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_MESSAGE_PARAM *tmp);
void	CT_ModosuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MODOSU_MESSAGE_PARAM *mmp);
void	CT_KuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,KURIDASU_MESSAGE_PARAM *kmp);
void	CT_EncountMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_EncountKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ENCOUNT_KURIDASU_MESSAGE_PARAM *ekmp);
void	CT_LevelUpEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_AlertMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ALERT_MESSAGE_PARAM *amp);
void	CT_HPGaugeRefreshSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_REFRESH_PARAM *hgrp);
void	CT_WazaWasureSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_WASURE_PARAM *wwp);
void	CT_MosaicSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MOSAIC_SET_PARAM *msp);
void	CT_BallGaugeEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
void	CT_BallGaugeEncountOut(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
void	CT_BallGaugeSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
void	CT_BallGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
void	CT_SioWaitMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_ChrPop(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep);
void	CT_SStoOAM(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_OAMtoSS(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_WinLoseMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_EscapeMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ESCAPE_MESSAGE_PARAM *emp);
void	CT_GiveUpMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
void	CT_MigawariChrSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep);
void	CT_WazaKoukaSESet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZAKOUKA_SE_PARAM *wsp);
void	CT_BGMPlay(BATTLE_WORK *bw,CLIENT_PARAM *cp,BGM_PLAY_PARAM *bpp);

//TCB系
static	void	TCB_PokemonEncount(TCB_PTR tcb,void *work);
static	void	TCB_PokemonEncountAppear(TCB_PTR tcb,void *work);
static	void	TCB_PokemonAppear(TCB_PTR tcb,void *work);
static	void	TCB_PokemonReturn(TCB_PTR tcb,void *work);
static	void	TCB_PokemonInhale(TCB_PTR tcb,void *work);
static	void	TCB_TrainerEncount(TCB_PTR tcb,void *work);
static	void	TCB_TrainerThrow(TCB_PTR tcb,void *work);
static	void	TCB_TrainerIn(TCB_PTR tcb,void *work);
static	void	TCB_TrainerOut(TCB_PTR tcb,void *work);
static	void	TCB_HPGaugeIn(TCB_PTR tcb,void *work);
static	void	TCB_HPGaugeOut(TCB_PTR tcb,void *work);
static	void	TCB_CommandSelect(TCB_PTR tcb,void *work);
static	void	TCB_CommandSelectAI(TCB_PTR tcb,void *work);
static	void	TCB_CommandSelectSIO(TCB_PTR tcb,void *work);
static	void	TCB_CommandSelectSafari(TCB_PTR tcb,void *work);
static	void	TCB_CommandSelectPokepark(TCB_PTR tcb,void *work);
static	void	TCB_WazaSelect(TCB_PTR tcb,void *work);
static	void	TCB_WazaSelectAI(TCB_PTR tcb,void *work);
static	void	TCB_WazaSelectSIO(TCB_PTR tcb,void *work);
static	void	TCB_DirSelect(TCB_PTR tcb,void *work);
static	void	TCB_DirSelectAI(TCB_PTR tcb,void *work);
static	void	TCB_DirSelectSIO(TCB_PTR tcb,void *work);
static	void	TCB_ItemSelect(TCB_PTR tcb,void *work);
static	void	TCB_ItemSelectAI(TCB_PTR tcb,void *work);
static	void	TCB_ItemSelectSIO(TCB_PTR tcb,void *work);
static	void	TCB_PokemonSelect(TCB_PTR tcb,void *work);
static	void	TCB_PokemonSelectAI(TCB_PTR tcb,void *work);
static	void	TCB_PokemonSelectSIO(TCB_PTR tcb,void *work);
static	void	TCB_YesNoSelect(TCB_PTR tcb,void *work);
static	void	TCB_YesNoSelectAI(TCB_PTR tcb,void *work);
static	void	TCB_YesNoSelectSIO(TCB_PTR tcb,void *work);
static	void	TCB_WazaEffect(TCB_PTR tcb,void *work);
static	void	TCB_PokemonBlink(TCB_PTR tcb,void *work);
static	void	TCB_HPGaugeCalc(TCB_PTR tcb,void *work);
static	void	TCB_EXPGaugeCalc(TCB_PTR tcb,void *work);
static	void	TCB_KizetsuEffect(TCB_PTR tcb,void *work);
static	void	TCB_FadeOut(TCB_PTR tcb,void *work);
static	void	TCB_PokemonVanishOnOff(TCB_PTR tcb,void *work);
static	void	TCB_LevelUpEffect(TCB_PTR tcb,void *work);

static	void	TCB_MessageWait(TCB_PTR tcb,void *work);
static	void	TCB_AlertMessageWait(TCB_PTR tcb,void *work);

static	void	TCB_EncountEffect(TCB_PTR tcb,void *work);
static	void	TCB_WazaWasure(TCB_PTR tcb,void *work);
static	void	TCB_MosaicSet(TCB_PTR tcb,void *work);

static	void	TCB_BallGaugeEncountSet(TCB_PTR tcb,void *work);
static	void	TCB_BallGaugeEncountOut(TCB_PTR tcb,void *work);

static	void	TCB_SStoOAM(TCB_PTR tcb,void *work);
static	void	TCB_OAMtoSS(TCB_PTR tcb,void *work);

//外部関数ツール系
void			CT_UISet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
u8				CT_CPClientTypeGet(CLIENT_PARAM *cp);
u8				CT_CPClientBootGet(CLIENT_PARAM *cp);
SOFT_SPRITE		*CT_CPSoftSpriteGet(CLIENT_PARAM *cp);
GAUGE_WORK		*CT_CPGaugeWorkGet(CLIENT_PARAM *cp);
CURSOR_SAVE		*CT_CursorSavePtrGet(CLIENT_PARAM *cp);
void			CT_CursorSaveClear(CLIENT_PARAM *cp);

//外部非公開ツール系
static	void		GaugeObjCreate(BATTLE_WORK *bw,int dir,int level,int hp,int hpmax);
static	void		NumCalc(int num,int *bit,int *buf);
static	SOFT_SPRITE	*CT_SoftSpriteAdd(BATTLE_WORK *bw,SOFT_SPRITE_MANAGER *ssm_p,SOFT_SPRITE_ARC *ssa,
									  int pos_x,int pos_y,int pos_z,int ofs_y,int height,int ofx,int shadow,int client_no,
									  SOFT_SPRITE_ANIME *anm_tbl,SOFT_SPRITE_MOVE_FUNC *move);
static	void		CT_ModosuMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MODOSU_MESSAGE_PARAM *mmp,MESSAGE_PARAM *mp);
static	void		CT_KuridasuMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,KURIDASU_MESSAGE_PARAM *kmp,MESSAGE_PARAM *mp);
static	void		CT_EncountMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *mp);
static	void		CT_EncountKuridasuMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,
													   ENCOUNT_KURIDASU_MESSAGE_PARAM *ekmp,MESSAGE_PARAM *mp);
static	void		CT_WinLoseMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *mp);
static	void		CT_EscapeMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,ESCAPE_MESSAGE_PARAM *emp,MESSAGE_PARAM *mp);
static	void		CT_GiveUpMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *mp);
static	CATS_ACT_PTR	CT_TrainerCLACTResourceLoad(BATTLE_WORK *bw,int type,int trtype,int id);
static	void		CT_WesCall(BATTLE_WORK *bw,CLIENT_PARAM *cp,WE_SYS_PTR wsp,WAZA_EFFECT_PARAM *wep);
static	void		CT_WazaPokeChangeParamMake(BATTLE_WORK *bw,WAZA_EFFECT_PARAM *wep,
											   WAZA_POKE_CHANGE_PARAM *wpcp,int client_no);

static	void		CT_WazaEffectGaugeShadowOnOffCheck(u8 *gauge,u8 *shadow,int eff_type,int eff_no,u16 waza_no);

//-----------------------------------------------------------------------------
//					定数定義
//-----------------------------------------------------------------------------

#define	SCROLL_TIME				(33)	///(44)	///<背景がスクロールする時間
#define	SCROLL_SPEED			(4)		///(3)		///<ポケモンがエンカウントしてくるときの背景スクロールのスピード
#define	ENCOUNT_SPEED			(8)		///(6)		///<ポケモンがエンカウントしてくるときのスピード
#define	ENCOUNT_START_WAIT		(28)	///(56)	///<エンカウントエフェクトが起動してから、地面のスクロールが始まるまでのウエイト
#define	TRAINER_IN_OUT_SPEED	(5)		///<トレーナーの出入りスピード

#define	AFF_SPEED				(0x20)	///<ポケモン登場エフェクトのポケモンが大きくなるスピード
#define	BLINK_WAIT				(2)		///<ダメージブリンクの間隔
#define	TP_WAIT					(10)	///<タッチパネルにタッチしてから次のシーケンスに移行するまでのウエイト
#define	ALERT_WAIT				(40)	///<アラートメッセージの表示ウエイト

#define	POKE_APPEAR_NORMAL_VOL	(127)	//ポケモン登場時の鳴き声音量（通常）
#define	POKE_APPEAR_BAD_VOL		(127)	//ポケモン登場時の鳴き声音量（状態異常や、HP減少時）
#define	POKE_KIZETSU_VOL		(127)	//ポケモン気絶時の鳴き声音量

#define	POKE_VOICE_PAN_FRONT	(WAZA_SE_PAN_R)		//ポケモン正面鳴き声のPAN設定
#define	POKE_VOICE_PAN_BACK		(WAZA_SE_PAN_L)		//ポケモン背面鳴き声のPAN設定

///2体目は鳴き声が被らないように少し遅らせて登場
#define ENCOUNT_DOUBLE_APPEAR_WAIT		(12)	//25

//-- ﾎﾞｰﾙ毎の変化後の指定色 --//
static const u16 BallHikariColor[] = {
	0x0000,			//dummy
	0x7297,			//マスターボール,
	0x3fff,			//ハイパーボール,
	0x7af0,			//スーパーボール,
	0x7adf,			//モンスターボール,
	0x53d7,			//サファリボール,
	0x67f5,			//ネットボール,
	0x7b2c,			//ダイブボール,
	0x2b7e,			//ネストボール,
	0x431f,			//リピートボール,
	0x7bdd,			//タイマーボール,
	0x2a3f,			//ゴージャスボール,
	0x293f,			//プレミアボール,
	0x45ce,			//ダークボール,
	0x731f,			//ヒールボール,
	0x7f51,			//クイックボール,
	0x151e,			//プレシャスボール,
};

//============================================================================================
/**
 *	エンカウントエフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	pep		ポケモンエンカウントパラメータ構造体
 */
//============================================================================================
void	CT_EncountEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_ENCOUNT_EFFECT	*tee;

	tee=(TCB_ENCOUNT_EFFECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_ENCOUNT_EFFECT));
	tee->bw=bw;
	tee->seq_no=0;
	tee->wait=0;
//	GF_BGL_ScrollSet(BattleWorkGF_BGL_INIGet(bw),GF_BGL_FRAME3_M,GF_BGL_SCROLL_X_DEC,SCROLL_SPEED*SCROLL_TIME);
	TCB_Add(TCB_EncountEffect,tee,0);
}

//============================================================================================
/**
 *	エンカウントポケモンをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	pep		ポケモンエンカウントパラメータ構造体
 */
//============================================================================================
void	CT_PokemonEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_ENCOUNT_PARAM *pep)
{
	int	col;
	SOFT_SPRITE_ARC	ssa;
	SOFT_SPRITE_MANAGER	*ssm;
	SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];
	TCB_POKEMON_ENCOUNT	*tpe;
	int	fight_type;
	u8	ofs_y;
	s8	height;
	s8	ofs_x;
	u8	shadow;

#if 0	//入力画面の常駐メッセージ書き換え用 2006.03.14(火) matsuda
		//作らないのでコメントアウト
	{
		STRBUF *nick_buf;
		nick_buf = STRBUF_Create(BUFLEN_POKEMON_NAME, HEAPID_BATTLE);
		STRBUF_SetStringCode(nick_buf, pep->nickname);
	}
#endif
	
	ssm=BattleWorkSoftSpriteManagerGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);

	tpe=(TCB_POKEMON_ENCOUNT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_ENCOUNT));
	tpe->seq_no=0;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		tpe->dir=PARA_FRONT;
		tpe->gw=BattleWorkGroundWorkGet(bw,GROUND_ENEMY);
		CATS_ObjectPosSetCap(tpe->gw->cap,EncountPosTable[cp->client_type&1][0],GROUND_ENEMY_Y);
	}
	else{
		tpe->dir=PARA_BACK;
		tpe->gw=BattleWorkGroundWorkGet(bw,GROUND_MINE);
		CATS_ObjectPosSetCap(tpe->gw->cap,EncountPosTable[cp->client_type&1][0],GROUND_MINE_Y);
	}
	if(pep->rare){
		col=PARA_RARE;
	}
	else{
		col=PARA_NORMAL;
	}
	PokeGraArcDataGet(&ssa,pep->monsno,pep->sex,tpe->dir,col,pep->form_no,pep->personal_rnd);
	ofs_y=PokeHeightGet(pep->monsno,pep->sex,tpe->dir,pep->form_no,pep->personal_rnd);
	ArchiveDataLoadOfs(&height,ARC_POKE_YOFS,0,pep->monsno,1);
	ArchiveDataLoadOfs(&ofs_x,ARC_POKE_SHADOW_OFX,0,pep->monsno,1);
	ArchiveDataLoadOfs(&shadow,ARC_POKE_SHADOW,0,pep->monsno,1);
	PokeAnmDataSet(&ssanm[0],pep->monsno);
	tpe->ss=cp->poke_ss=CT_SoftSpriteAdd(bw,ssm,&ssa,
										 EncountPosTable[cp->client_type][0],
										 EncountPosTable[cp->client_type][1],
										 EncountPosTable[cp->client_type][2],
										 ofs_y,
										 height,
										 ofs_x,
										 shadow,
										 cp->client_no,&ssanm[0],NULL);

	//正面は、色を変える
	if(tpe->dir==PARA_FRONT){
		SoftSpritePalFadeSet(tpe->ss,8,8,0,0x0000);
	}

	tpe->appear_pos=AppearPosTable[cp->client_type][POS_APPEAR];
	tpe->bw=bw;
	tpe->cp=cp;
	tpe->command_code=pep->command_code;
	tpe->client_no=cp->client_no;
	tpe->mons_no=pep->monsno;
	tpe->voice=pep->voice;
	tpe->client_type=cp->client_type;
	tpe->chr=PokeSeikakuGetRnd(pep->personal_rnd);
	tpe->rare=pep->rare;
	TCB_Add(TCB_PokemonEncount,tpe,0);
}

//============================================================================================
/**
 *	ポケモン出現エフェクトをセット（エンカウント時専用）
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	pap		ポケモン出現エフェクトパラメータ構造体
 */
//============================================================================================
void	CT_PokemonEncountAppearSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_APPEAR_PARAM *pap)
{
	int	col;
	TCB_POKEMON_APPEAR	*tpa;
	int	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	tpa=(TCB_POKEMON_APPEAR *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_APPEAR));

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		tpa->dir=PARA_FRONT;
	}
	else{
		tpa->dir=PARA_BACK;
	}
	if(pap->rare){
		col=PARA_RARE;
	}
	else{
		col=PARA_NORMAL;
	}
	PokeGraArcDataGet(&tpa->ssa,pap->monsno,pap->sex,tpa->dir,col,pap->form_no,pap->personal_rnd);
	tpa->ofs_y=PokeHeightGet(pap->monsno,pap->sex,tpa->dir,pap->form_no,pap->personal_rnd);
	ArchiveDataLoadOfs(&tpa->height,ARC_POKE_YOFS,0,pap->monsno,1);
	ArchiveDataLoadOfs(&tpa->ofs_x,ARC_POKE_SHADOW_OFX,0,pap->monsno,1);
	ArchiveDataLoadOfs(&tpa->shadow,ARC_POKE_SHADOW,0,pap->monsno,1);

	//入れ替えたのでカーソル位置記憶を初期化
	CT_CursorSaveClear(cp);
	
	tpa->bw=bw;
	tpa->cp=cp;
	tpa->seq_no=0;
	tpa->wait = 0;
	tpa->command_code=pap->command_code;
	tpa->client_no=cp->client_no;
	tpa->mons_no=pap->monsno;
	tpa->client_type = cp->client_type;
	tpa->voice=pap->voice;
	tpa->sel_mons_no=pap->sel_mons_no;
	tpa->chr=PokeSeikakuGetRnd(pap->personal_rnd);
	tpa->ballID=pap->ballID;
//	tpa->bms=cp->bms;
	tpa->rare=pap->rare;
	tpa->flag=POKEMON_APPEAR_KURIDASI;
	
	TCB_Add(TCB_PokemonEncountAppear,tpa,0);
}

//============================================================================================
/**
 *	ポケモン出現エフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	pap		ポケモン出現エフェクトパラメータ構造体
 */
//============================================================================================
void	CT_PokemonAppearSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_APPEAR_PARAM *pap)
{
	int	i;
	int	col;
	TCB_POKEMON_APPEAR	*tpa;
	int	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	tpa=(TCB_POKEMON_APPEAR *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_APPEAR));
	tpa->seq_no=0;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		tpa->dir=PARA_FRONT;
	}
	else{
		tpa->dir=PARA_BACK;
	}
	if(pap->rare){
		col=PARA_RARE;
	}
	else{
		col=PARA_NORMAL;
	}
	PokeGraArcDataGet(&tpa->ssa,pap->monsno,pap->sex,tpa->dir,col,pap->form_no,pap->personal_rnd);
	tpa->ofs_y=PokeHeightGet(pap->monsno,pap->sex,tpa->dir,pap->form_no,pap->personal_rnd);
	ArchiveDataLoadOfs(&tpa->height,ARC_POKE_YOFS,0,pap->monsno,1);
	ArchiveDataLoadOfs(&tpa->ofs_x,ARC_POKE_SHADOW_OFX,0,pap->monsno,1);
	ArchiveDataLoadOfs(&tpa->shadow,ARC_POKE_SHADOW,0,pap->monsno,1);

#if 0
	tpa->ss=cp->poke_ss=CT_SoftSpriteAdd(bw,ssm,&ssa,
										 AppearPosTable[cp->client_type][POS_APPEAR],
										 EncountPosTable[cp->client_type][1],
										 EncountPosTable[cp->client_type][2],
										 tpa->height,
										 cp->client_no,&ssanm[0],NULL);

	SoftSpriteParaSet(tpa->ss,SS_PARA_AFF_X,AFF_APPEAR_X_S);
	SoftSpriteParaSet(tpa->ss,SS_PARA_AFF_Y,AFF_APPEAR_Y_S);
#endif

	//入れ替えたのでカーソル位置記憶を初期化
	CT_CursorSaveClear(cp);
	
	tpa->bw=bw;
	tpa->cp=cp;
	tpa->command_code=pap->command_code;
	tpa->client_no=cp->client_no;
	tpa->mons_no=pap->monsno;
	tpa->client_type = cp->client_type;
	tpa->voice=pap->voice;
	tpa->sel_mons_no=pap->sel_mons_no;
	tpa->chr=PokeSeikakuGetRnd(pap->personal_rnd);
	tpa->ballID=pap->ballID;
	tpa->rare=pap->rare;
	tpa->flag=pap->flag;
	tpa->wait = 0;
	tpa->migawari_flag = pap->migawari_flag;

	for(i=0;i<CLIENT_MAX;i++){
		tpa->wep.mons_no[i]			=pap->wep_mons_no[i];
		tpa->wep.sex[i]				=pap->wep_sex[i];
		tpa->wep.rare[i]			=pap->wep_rare[i];
		tpa->wep.form_no[i]			=pap->wep_form_no[i];
		tpa->wep.personal_rnd[i]	=pap->wep_personal_rnd[i];
	}

	TCB_Add(TCB_PokemonAppear,tpa,0);
}

//============================================================================================
/**
 *	ポケモン引っ込めるエフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_PokemonReturnSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_RETURN_PARAM *prp)
{
	int					i;
	TCB_POKEMON_RETURN	*tpr;

	tpr=(TCB_POKEMON_RETURN *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_RETURN));
	tpr->bw=bw;
	tpr->cp=cp;
	tpr->ss=cp->poke_ss;
	tpr->command_code=prp->command_code;
	tpr->client_no=cp->client_no;
	tpr->client_type=cp->client_type;
	tpr->seq_no=0;
	tpr->height=prp->height;
	tpr->ballID=prp->ballID;
	tpr->migawari_flag=prp->migawari_flag;

	for(i=0;i<CLIENT_MAX;i++){
		tpr->wep.mons_no[i]			=prp->mons_no[i];
		tpr->wep.sex[i]				=prp->sex[i];
		tpr->wep.rare[i]			=prp->rare[i];
		tpr->wep.form_no[i]			=prp->form_no[i];
		tpr->wep.personal_rnd[i]	=prp->personal_rnd[i];
	}

	TCB_Add(TCB_PokemonReturn,tpr,0);
}

//============================================================================================
/**
 *	ポケモン引っ込めるエフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_PokemonInhaleSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_INHALE_PARAM *pip)
{
	TCB_POKEMON_INHALE	*tpi;

	tpi=(TCB_POKEMON_INHALE *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_INHALE));
	tpi->bw=bw;
	tpi->ss=cp->poke_ss;
	tpi->command_code=pip->command_code;
	tpi->client_no=cp->client_no;
	tpi->client_type=cp->client_type;
	tpi->seq_no=0;
	tpi->height=pip->height;

	SoftSpritePalFadeSet(tpi->ss,0,16,0,BallHikariColor[pip->ballID]);
	SoftSpriteParaSet(tpi->ss,SS_PARA_SHADOW_AFF_REQ,1);

	TCB_Add(TCB_PokemonInhale,tpi,0);
}

//============================================================================================
/**
 *	エンカウントトレーナー用セルアクターヘッダー
 */
//============================================================================================
static const TCATS_OBJECT_ADD_PARAM_S EncountTrainerObjParam = {
	0, 0, 0,		//x, y, z
	0, 0, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_ENCOUNT_TRAINER1,		//キャラ
		PLTTID_ENCOUNT_TRAINER1,		//パレット
		CELLID_ENCOUNT_TRAINER1,		//セル
		CELLANMID_ENCOUNT_TRAINER1,		//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	1,			//BGプライオリティ
	1,			//Vram転送フラグ
};

//============================================================================================
/**
 *	エンカウントトレーナーをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	tep		エンカウントトレーナーパラメータ構造体
 */
//============================================================================================
void	CT_TrainerEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_ENCOUNT_PARAM *tep)
{
	int	col;
	SOFT_SPRITE_ARC	ssa;
	SOFT_SPRITE_MANAGER	*ssm;
	TCB_TRAINER_ENCOUNT	*tte;
	u32	sex;
	int	type;

	ssm=BattleWorkSoftSpriteManagerGet(bw);

	tte=(TCB_TRAINER_ENCOUNT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_TRAINER_ENCOUNT));
	tte->seq_no=0;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		tte->dir=PARA_FRONT;
		tte->gw=BattleWorkGroundWorkGet(bw,GROUND_ENEMY);
		CATS_ObjectPosSetCap(tte->gw->cap,EncountPosTable[cp->client_type&1][0],GROUND_ENEMY_Y);
	}
	else{
		tte->dir=PARA_BACK;
		tte->gw=BattleWorkGroundWorkGet(bw,GROUND_MINE);
		CATS_ObjectPosSetCap(tte->gw->cap,EncountPosTable[cp->client_type&1][0],GROUND_MINE_Y);
	}
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)||
	  ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)&&(cp->client_type&CLIENT_ENEMY_FLAG))){
		type=cp->client_type;
	}
	else{
		type=cp->client_type&1;
	}

	sex=BattleWorkMySexGet(bw,cp->client_no);
	TrGraArcDataGet(&ssa,tep->trtype,tte->dir,sex);
#if 0
	tte->ss=cp->tr_ss=SoftSpriteAdd(ssm,&ssa,
									EncountPosTable[type][0],
									EncountPosTable[type][1],
									EncountPosTable[type][2],
									cp->client_no,
									NULL,
									NULL);
#endif
	tte->ss=cp->tr_ss=CT_SoftSpriteAdd(bw,ssm,&ssa,
									   EncountPosTable[type][0],
									   EncountPosTable[type][1],
									   EncountPosTable[type][2],
									   0,0,0,0,
									   cp->client_no,
									   NULL,
									   NULL);
	//背面で、サファリゾーン、ポケパークではないときは、CLACTリソースを先読みしておく
	if((tte->dir==PARA_BACK)&&
	  ((BattleWorkFightTypeGet(bw)&(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK))==0)){
		{
			int	trtype;
			int	id;

			trtype	=TrainerBTrTypeGet(tep->trtype);
			id		=cp->client_type>>1;

			tte->cap=cp->cap=CT_TrainerCLACTResourceLoad(bw,type,trtype,id);
		}
#if 0
		{
			CATS_SYS_PTR				csp;
			CATS_RES_PTR				crp;
			PALETTE_FADE_PTR			pfd;
			TCATS_OBJECT_ADD_PARAM_S	op;
			int							trtype;

			csp=BattleWorkCATS_SYS_PTRGet(bw);
			crp=BattleWorkCATS_RES_PTRGet(bw);
			pfd=BattleWorkPfdGet(bw);

			trtype=TrainerBTrTypeGet(tep->trtype);

			CATS_LoadResourceCharArc(csp,crp,ARC_BATT_OBJ,DTR1B_002_NCGR_BIN+trtype,1,
									 NNS_G2D_VRAM_TYPE_2DMAIN,CHARID_ENCOUNT_TRAINER1+(cp->client_type>>1));
			CATS_LoadResourcePlttWorkArc(pfd,FADE_MAIN_OBJ,csp,crp,ARC_BATT_OBJ,DTR1B_002_NCLR+trtype,0,1,
										 NNS_G2D_VRAM_TYPE_2DMAIN,PLTTID_ENCOUNT_TRAINER1+(cp->client_type>>1));
			CATS_LoadResourceCellArc(csp,crp,ARC_BATT_OBJ,DTR1B_002_NCER_BIN+trtype,1,
									 CELLID_ENCOUNT_TRAINER1+(cp->client_type>>1));
			CATS_LoadResourceCellAnmArc(csp,crp,ARC_BATT_OBJ,DTR1B_002_NANR_BIN+trtype,1,
										CELLANMID_ENCOUNT_TRAINER1+(cp->client_type>>1));

			op=EncountTrainerObjParam;
			op.id[CLACT_U_CHAR_RES]=CHARID_ENCOUNT_TRAINER1+(cp->client_type>>1);
			op.id[CLACT_U_PLTT_RES]=PLTTID_ENCOUNT_TRAINER1+(cp->client_type>>1);
			op.id[CLACT_U_CELL_RES]=CELLID_ENCOUNT_TRAINER1+(cp->client_type>>1);
			op.id[CLACT_U_CELLANM_RES]=CELLANMID_ENCOUNT_TRAINER1+(cp->client_type>>1);

			tte->cap=cp->cap=CATS_ObjectAdd_S(csp,crp,&op);
			CATS_ObjectPosSetCap(tte->cap,EncountPosTable[type][0],EncountPosTable[type][1]);
			CATS_ObjectUpdateCap(tte->cap);
		}
#endif
	}
#if 0
	else{
		{
			int	shadow_type;

			shadow_type=cp->client_type;
			if(shadow_type>CLIENT_TYPE_BB){
				shadow_type=shadow_type>>1;
			}
			SoftSpriteParaSet(tte->ss,SS_PARA_SHADOW_REQ,shadow_type);
			SoftSpriteParaSet(tte->ss,SS_PARA_SHADOW_OY,SHADOW_OFS);
		}
	}
#endif
	tte->appear_pos=AppearPosTable[type][POS_APPEAR];
	tte->bw=bw;
	tte->command_code=tep->command_code;
	tte->client_no=cp->client_no;
	tte->client_type = cp->client_type;
	tte->scroll_time = 0;
	if((tte->client_type==CLIENT_TYPE_AA)||(tte->client_type==CLIENT_TYPE_A)){
		//画面スクロール位置の初期化
		GF_BGL_ScrollSet(BattleWorkGF_BGL_INIGet(bw),GF_BGL_FRAME3_M,GF_BGL_SCROLL_X_DEC,SCROLL_SPEED*SCROLL_TIME);
	}
	TCB_Add(TCB_TrainerEncount,tte,0);
}

//============================================================================================
/**
 *	トレーナー投げるエフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_TrainerThrowSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_THROW_PARAM *ttp)
{
	TCB_TRAINER_THROW	*ttt;

	ttt=(TCB_TRAINER_THROW *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_TRAINER_THROW));
	ttt->seq_no=0;

	ttt->bw=bw;
	ttt->command_code=ttp->command_code;
	ttt->type=ttp->type;
	ttt->client_no=cp->client_no;
	ttt->cp=cp;
	if(cp->client_type&CLIENT_ENEMY_FLAG){
		ttt->dir=PARA_FRONT;
		ttt->trtype=0;
	}
	else{
		{
			TRAINER_DATA	*trdata;

			trdata=BattleWorkTrainerDataGet(bw,cp->client_no);
			ttt->dir=PARA_BACK;
			ttt->trtype=TrainerBTrTypeGet(trdata->tr_type);
		}
	}


	TCB_Add(TCB_TrainerThrow,ttt,0);
}

//============================================================================================
/**
 *	トレーナー画面外エフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_TrainerOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_TRAINER_OUT	*tto;

	tto=(TCB_TRAINER_OUT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_TRAINER_OUT));
	tto->seq_no=0;

	tto->bw=bw;
	tto->command_code=cp->client_buffer[0];
	tto->client_no=cp->client_no;
	tto->cp=cp;
	if(cp->client_type&CLIENT_ENEMY_FLAG){
		tto->dir=PARA_FRONT;
	}
	else{
		tto->dir=PARA_BACK;
	}


	TCB_Add(TCB_TrainerOut,tto,0);
}

//============================================================================================
/**
 *	トレーナー画面内エフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_TrainerInSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_IN_PARAM *tip)
{
	int	col;
	SOFT_SPRITE_ARC	ssa;
	SOFT_SPRITE_MANAGER	*ssm;
	TCB_TRAINER_IN	*tti;
	u32	sex;

	ssm=BattleWorkSoftSpriteManagerGet(bw);

	tti=(TCB_TRAINER_IN *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_TRAINER_IN));
	tti->seq_no=0;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		tti->dir=PARA_FRONT;
	}
	else{
		tti->dir=PARA_BACK;
	}
	sex=BattleWorkMySexGet(bw,cp->client_no);
	TrGraArcDataGet(&ssa,tip->trtype,tti->dir,sex);
	tti->ss=cp->tr_ss=SoftSpriteAdd(ssm,&ssa,
									SlideInPosTable[cp->client_type][0],
									SlideInPosTable[cp->client_type][1],
									SlideInPosTable[cp->client_type][2],
									cp->client_no,
									NULL,
									NULL);
	tti->appear_pos=AppearPosTable[cp->client_type&1][tip->pos];
	tti->bw=bw;
	tti->command_code=tip->command_code;
	tti->client_no=cp->client_no;
	TCB_Add(TCB_TrainerIn,tti,0);
}

//============================================================================================
/**
 *	HPゲージ画面INエフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_HPGaugeInSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_IN_PARAM *hgip)
{
	GAUGE_WORK *gauge;
	
	gauge = &cp->gauge;
	MI_CpuClearFast(&gauge->param, sizeof(GAUGE_SUB_PARAM));
	gauge->bw = bw;
	gauge->client_no = cp->client_no;
	gauge->type = Gauge_TypeGet(cp->client_type, BattleWorkFightTypeGet(bw));
	gauge->command_code = hgip->command_code;
	gauge->hp = hgip->hp;
	gauge->hpmax = hgip->hpmax;
	gauge->level = hgip->level;
	gauge->sex = hgip->sex;
	gauge->damage = 0;
	gauge->exp = hgip->now_exp;
	gauge->max_exp = hgip->max_exp;
	gauge->sel_mons_no = hgip->sel_mons_no;
	gauge->status = hgip->status;
	gauge->getball = hgip->get_mark;
	gauge->in_wait = hgip->wait;
	gauge->safari_nokori = hgip->safari_ball;
	
	Gauge_EnableSet(gauge, CATS_ENABLE_FALSE);
	Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_ALL);

	gauge->tcb = TCB_Add(TCB_HPGaugeIn, gauge, TCBPRI_HP_GAUGE_IN);
}

//============================================================================================
/**
 *	HPゲージ画面OUTエフェクトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_HPGaugeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	GAUGE_WORK *gauge;
	
	gauge=&cp->gauge;
	MI_CpuClearFast(&gauge->param, sizeof(GAUGE_SUB_PARAM));
	gauge->bw=bw;
	gauge->client_no=cp->client_no;
	gauge->command_code=cp->client_buffer[0];

	Gauge_ScrollEffectSet(gauge, GAUGE_SCROLL_OUT);
	gauge->tcb = TCB_Add(TCB_HPGaugeOut, gauge, TCBPRI_HP_GAUGE_IN);
}

//============================================================================================
/**
 *	コマンド選択を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_CommandSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,COMMAND_SELECT_PARAM *csp)
{
	TCB_COMMAND_SELECT	*tcs;
	int					i,j;

	tcs=(TCB_COMMAND_SELECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_COMMAND_SELECT));
	MI_CpuClearFast(tcs, sizeof(TCB_COMMAND_SELECT));
	
	tcs->seq_no=0;
	tcs->wait=0;
	tcs->bw=bw;
	tcs->command_code=csp->command_code;
	tcs->client_no=cp->client_no;
	tcs->client_type = cp->client_type;
	tcs->gauge = &cp->gauge;
	tcs->sel_mons_no = csp->sel_mons_no;
	tcs->icon_hp = csp->icon_hp;
	tcs->icon_hpmax = csp->icon_hpmax;
	tcs->icon_status = csp->icon_status;
	
	for(i=0;i<2;i++){
		for(j=0;j<POKEMON_TEMOTI_MAX;j++){
			tcs->status[i][j]=csp->status[i][j];
		}
	}
	
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		if(csp->status[POKEPARTY_MINE][i] == COMSEL_STATUS_DEAD){
			tcs->motivation[i] = 0;	//瀕死の時は揺らさないようにモチベーション0
		}
		else{
			tcs->motivation[i] = csp->motivation[i];
		}
	}

#if 0	//移動 2006.06.30(金)
	if(BattleWorkMineEnemyCheck(bw, cp->client_no) == 0){
		//技選択画面の描画を早くする為に、ここで先に技番号やPPなどを
		//もらってデータをメモリに展開しておく 2006.05.12(金) by matsuda
		// ※曽我部さんの支持の元作業してます。
		BINPUT_WAZA_PARAM wazapara;
		int i;
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			wazapara.wazano[i] = csp->wazano[i];
			wazapara.pp[i] = csp->pp[i];
			wazapara.ppmax[i] = csp->ppmax[i];
		}
		BINPUT_WazaParaMemoryDecord(BattleWorkGF_BGL_BIPGet(bw), cp->client_type, &wazapara);
	}
#else
	{
		int i;
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			tcs->wazano[i] = csp->wazano[i];
			tcs->pp[i] = csp->pp[i];
			tcs->ppmax[i] = csp->ppmax[i];
		}
	}
#endif

	TCB_Add(cp->ui.UI_CommandSelect,tcs,0);
}

//============================================================================================
/**
 *	技選択を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_WazaSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_SELECT_PARAM *wsp)
{
	TCB_WAZA_SELECT	*tws;
	int i;
	
	tws=(TCB_WAZA_SELECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_WAZA_SELECT));

	tws->seq_no=0;
	tws->bw=bw;
	tws->command_code=cp->client_buffer[0];
	tws->client_no=cp->client_no;
	tws->client_type=cp->client_type;
	tws->gauge = &cp->gauge;
	tws->sel_mons_no = wsp->sel_mons_no;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		tws->wazano[i] = wsp->wazano[i];
		tws->pp[i] = wsp->pp[i];
		tws->ppmax[i] = wsp->ppmax[i];
	}
	tws->wazabit=wsp->wazabit;

	TCB_Add(cp->ui.UI_WazaSelect,tws,0);
}

//============================================================================================
/**
 *	攻撃対象選択を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_DirSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,DIR_SELECT_PARAM *dsp)
{
	TCB_DIR_SELECT	*tds;
	int i,client_set_max;
	u32	fight_type;
	u8	buf[CLIENT_TYPE_MAX];
	
	tds=(TCB_DIR_SELECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_DIR_SELECT));

	tds->seq_no=0;
	tds->bw=bw;
	tds->command_code=cp->client_buffer[0];
	tds->client_no=cp->client_no;
	tds->client_type = cp->client_type;
	tds->range=dsp->range;
	tds->gauge = &cp->gauge;
	tds->light_flag = dsp->flag;
	
	BattleClientTypeBufMake(bw,&buf[0]);
	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);
	for(i=0;i<client_set_max;i++){
		tds->dspp[i]=dsp->dspp[i];
	}

	TCB_Add(cp->ui.UI_DirSelect,tds,0);
}


//============================================================================================
/**
 *	道具選択を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_ItemSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ITEM_SELECT_PARAM *isp)
{
	TCB_ITEM_SELECT	*tis;
	int				i,j;

	tis=(TCB_ITEM_SELECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_ITEM_SELECT));
	tis->tps=(TCB_POKEMON_SELECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_SELECT));
	tis->tps->plist=sys_AllocMemory(HEAPID_BATTLE,sizeof(BPLIST_DATA));
	tis->tps->plist->pp=PokeParty_AllocPartyWork(HEAPID_BATTLE);

	tis->seq_no=0;
	tis->bw=bw;
	tis->command_code=isp->command_code;
	tis->client_no=cp->client_no;
	tis->client_type = cp->client_type;
	tis->enc_double = isp->enc_double;
	tis->waza_vanish = isp->waza_vanish;
	tis->waza_migawari = isp->waza_migawari;
	for(i=0;i<CLIENT_MAX;i++){
		tis->tps->sel_mons_no[i]=isp->sel_mons_no[i];
		for(j=0;j<POKEMON_TEMOTI_MAX;j++){
			tis->list_row[i][j]=isp->list_row[i][j];
		}
		tis->shutout_flag[i]=isp->shutout_flag[i];	// 技で使用不可
	}

	TCB_Add(cp->ui.UI_ItemSelect,tis,0);
}

//============================================================================================
/**
 *	ポケモン選択を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_PokemonSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_SELECT_PARAM *psp)
{
	TCB_POKEMON_SELECT	*tps;
	int					i,j;

	tps=(TCB_POKEMON_SELECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_SELECT));

	tps->seq_no=0;
	tps->bw=bw;
	tps->command_code=psp->command_code;
	tps->client_no=psp->client_no;
	tps->list_mode=psp->list_mode;
	tps->chg_waza=psp->chg_waza;
	tps->double_sel=psp->double_sel;
	tps->item=0;
	tps->no_reshuffle_client=psp->no_reshuffle_client;
	for(i=0;i<CLIENT_MAX;i++){
		tps->sel_mons_no[i]=psp->sel_mons_no[i];
		for(j=0;j<POKEMON_TEMOTI_MAX;j++){
			tps->list_row[i][j]=psp->list_row[i][j];
		}
	}

	TCB_Add(cp->ui.UI_PokemonSelect,tps,0);
}

//============================================================================================
/**
 *	Yes/No選択を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_YesNoSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,YES_NO_SELECT_PARAM *ynsp)
{
	TCB_YES_NO_SELECT	*tyns;

	tyns=(TCB_YES_NO_SELECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_YES_NO_SELECT));

	tyns->seq_no=0;
	tyns->bw=bw;
	tyns->command_code=ynsp->command_code;
	tyns->client_no=cp->client_no;
	tyns->gauge = &cp->gauge;
	tyns->msg_id=ynsp->msg_id;
	tyns->flag=ynsp->flag;
	tyns->waza_no=ynsp->waza_no;
	tyns->nickname=ynsp->nickname;
	
	TCB_Add(cp->ui.UI_YesNoSelect,tyns,0);
}

//============================================================================================
/**
 *	アタックメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	amp		アタックメッセージ用パラメータワーク構造体
 */
//============================================================================================
void	CT_AttackMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ATTACK_MESSAGE_PARAM *amp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	msg_m=BattleWorkAttackMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=amp->command_code;
	tmw->client_no=cp->client_no;

	mp.msg_id=ATKMSG_M_000+amp->waza_no*3;
	mp.msg_tag=TAG_NICK;
	mp.msg_para[0]=cp->client_no|(amp->sel_mons_no<<8);

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	メッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	mp		メッセージ用パラメータワーク構造体
 */
//============================================================================================
void	CT_MessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *mp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=cp->client_buffer[0];
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	技エフェクトを起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	wep		技エフェクト用パラメータワーク構造体
 */
//============================================================================================
#if 0
void	CT_WazaEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep)
{
	TCB_WAZA_EFFECT	*twe;
	WES_CALL_BTL_EX_PARAM wcbep;
	int i;
	int	callID;
	
	twe=(TCB_WAZA_EFFECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_WAZA_EFFECT));

	twe->seq_no=0;
	twe->bw=bw;
	twe->command_code=cp->client_buffer[0];
	twe->client_no=cp->client_no;
	twe->wsp=BattleWorkWE_SYS_PTRGet(bw);
	if((wep->flag==EFFTYPE_WAZA)&&((WT_WazaDataParaGet(wep->waza_no,ID_WTD_flag)&FLAG_PUT_GAUGE)==0)){
		twe->flag=1;
	}
	else{
		twe->flag=0;
	}

	/// 戦闘に渡す拡張引数
	if(wep->flag==EFFTYPE_WAZA){
		wcbep.eff_arc_id = ARC_WAZA_EFF;
		callID=wep->waza_no;
	}
	else{
		wcbep.eff_arc_id = ARC_WAZA_EFF_SUB;
		callID=wep->data;
	}
	wcbep.bgl  = BattleWorkGF_BGL_INIGet(bw);					///< BGL*
	wcbep.pfd  = BattleWorkPfdGet(bw);							///< PFD*
	wcbep.csp  = BattleWorkCATS_SYS_PTRGet(bw);					///< CSP*
	for(i = 0; i < CLIENT_MAX; i++){
		wcbep.excp[i] = BattleWorkExChrClientParamGet(bw, i);
		wcbep.mons_no[i] = wep->mons_no[i];
		wcbep.sex[i] = wep->sex[i];
		wcbep.rare[i] = wep->rare[i];
		wcbep.form_no[i] = wep->form_no[i];
		wcbep.personal_rnd[i] = wep->personal_rnd[i];
	}
	BattleClientTypeBufMake(bw, &(wcbep.client_type[0]));			///< クライアントType
	BattleSoftSpriteBufMake(bw, &(wcbep.ss[0]));					///< ソフトスプライト
	wcbep.fight_type = BattleWorkFightTypeGet(bw);					///< ファイトタイプ取得
	wcbep.perap_voice = BattleWorkPerapVoiceGet(bw, cp->client_no);	///< ペラップ
	wcbep.bg_area = BattleWorkBGAreaGet(bw);						///< BGエリア
	wcbep.pal_area = BattleWorkPalAreaGet(bw);						///< PALエリア
	
	///< 背景データ
	wcbep.haikei_data.arc_index = ARC_BATT_BG;
	wcbep.haikei_data.chr_id	= BATTLE_BG00_NCGR_BIN + BattleWorkBGIDGet(bw);
	wcbep.haikei_data.pal_id	= BATT_BG00_D_NCLR + BattleWorkBGIDGet(bw)*3;
	wcbep.haikei_data.scr_id	= BATTLE_BG00_NSCR_BIN;
	wcbep.haikei_data.pal_start	= 0;
	wcbep.haikei_data.pal_num	= 8;
	
	WES_Call_Ex(twe->wsp, wep, callID, &wcbep);

	TCB_Add(TCB_WazaEffect,twe,0);
}
#else
void	CT_WazaEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep)
{
	TCB_WAZA_EFFECT	*twe;
	
	twe=(TCB_WAZA_EFFECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_WAZA_EFFECT));

	twe->seq_no=0;
	twe->bw=bw;
	twe->cp=cp;
	twe->command_code=cp->client_buffer[0];
	twe->client_no=cp->client_no;
	twe->wsp=BattleWorkWE_SYS_PTRGet(bw);
	twe->wep=*wep;
	twe->ss=cp->poke_ss;

	if((wep->flag==EFFTYPE_STATUS)&&(wep->data==STATUS_ACTION_DOLL_ON)){
		cp->migawari_flag=1;
	}
	if((wep->flag==EFFTYPE_STATUS)&&(wep->data==STATUS_ACTION_DOLL_OFF)){
		cp->migawari_flag=0;
	}

	CT_WazaEffectGaugeShadowOnOffCheck(&twe->we_on_off_flag,&twe->we_shadow_flag,wep->flag,wep->data,wep->waza_no);

	TCB_Add(TCB_WazaEffect,twe,0);
}
#endif

//============================================================================================
/**
 *	ポケモンダメージブリンクアクションを起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_PokemonBlinkSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_POKEMON_BLINK	*tpb;

	tpb=(TCB_POKEMON_BLINK *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_BLINK));

	tpb->seq_no=0;
	tpb->bw=bw;
	tpb->ss=cp->poke_ss;
	tpb->client_no=cp->client_no;
	tpb->wait=0;

	TCB_Add(TCB_PokemonBlink,tpb,0);

}

//============================================================================================
/**
 *	HPゲージ計算を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_HPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_CALC_PARAM *hgcp)
{
	GAUGE_WORK *gauge;
	
	GF_ASSERT(cp->gauge.cap != NULL);
	
	gauge = &cp->gauge;
	MI_CpuClear8(&gauge->param, sizeof(GAUGE_SUB_PARAM));
	gauge->bw = bw;
	gauge->command_code = hgcp->command_code;
	gauge->client_no = cp->client_no;
	gauge->type = Gauge_TypeGet(cp->client_type, BattleWorkFightTypeGet(bw));
	gauge->hp = hgcp->hp;
	gauge->hpmax = hgcp->hpmax;
	gauge->damage = hgcp->damage;
	gauge->level = hgcp->level;
	
	if(hgcp->damage == JIBAKU_HP){
		gauge->hp = 0;
		gauge->damage = 0;
	}
	
	gauge->tcb = TCB_Add(TCB_HPGaugeCalc, gauge, TCBPRI_HP_GAUGE_CALC);
}

//============================================================================================
/**
 *	EXPゲージ計算を起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_EXPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,EXP_GAUGE_CALC_PARAM *egcp)
{
	GAUGE_WORK *gauge;
	
	GF_ASSERT(cp->gauge.cap != NULL);
	
	gauge = &cp->gauge;
	MI_CpuClear8(&gauge->param, sizeof(GAUGE_SUB_PARAM));
	gauge->bw = bw;
	gauge->command_code = egcp->command_code;
	gauge->client_no = cp->client_no;

	gauge->exp = egcp->now_exp;
	gauge->max_exp = egcp->max_exp;
	gauge->add_exp = egcp->next_exp - gauge->exp;
	
	if(cp->client_type == CLIENT_TYPE_AA){
		gauge->tcb = TCB_Add(TCB_EXPGaugeCalc, gauge, TCBPRI_HP_GAUGE_CALC);
		return;
	}
	else{
		SCIO_ServerQueClear(gauge->bw, gauge->client_no, gauge->command_code);
	}
}

//============================================================================================
/**
 *	気絶エフェクトを起動
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_KizetsuEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,KIZETSU_EFFECT_PARAM *kep)
{
	TCB_KIZETSU_EFFECT	*tke;
	int					i;

	tke=(TCB_KIZETSU_EFFECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_KIZETSU_EFFECT));

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		tke->dir=PARA_FRONT;
	}
	else{
		tke->dir=PARA_BACK;
	}

	tke->seq_no=0;
	tke->bw=bw;
	tke->cp=cp;
	tke->command_code=kep->command_code;
	tke->client_no=cp->client_no;
	tke->ss=cp->poke_ss;
	tke->monsno=kep->monsno;
	tke->sex=kep->sex;
	tke->form_no=kep->form_no;
	tke->personal_rnd=kep->personal_rnd;
	tke->migawari_flag=kep->migawari_flag;
	tke->henshin_flag=kep->henshin_flag;

	for(i=0;i<CLIENT_MAX;i++){
		tke->wep.mons_no[i]			=kep->wep_mons_no[i];
		tke->wep.sex[i]				=kep->wep_sex[i];
		tke->wep.rare[i]			=kep->wep_rare[i];
		tke->wep.form_no[i]			=kep->wep_form_no[i];
		tke->wep.personal_rnd[i]	=kep->wep_personal_rnd[i];
	}

	TCB_Add(TCB_KizetsuEffect,tke,0);
}

//============================================================================================
/**
 *	指定されたSEを鳴らす
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_SePlaySet(BATTLE_WORK *bw,CLIENT_PARAM *cp,SE_PLAY_PARAM *spp)
{
	int	pan;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		pan=WAZA_SE_PAN_R;
	}
	else{
		pan=WAZA_SE_PAN_L;
	}

	SCIO_ServerQueClear(bw,cp->client_no,spp->command_code);
	Snd_SePlayPan(spp->se_no,pan);
}

//============================================================================================
/**
 *	画面フェードアウトをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_FadeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_FADE_OUT	*tfo;

	tfo=(TCB_FADE_OUT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_FADE_OUT));

	tfo->seq_no=0;
	tfo->bw=bw;
	tfo->command_code=cp->client_buffer[0];
	tfo->client_no=cp->client_no;

	TCB_Add(TCB_FadeOut,tfo,0);
}

//============================================================================================
/**
 *	ポケモンのバニッシュフラグを制御
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 * @param[in]	pvoo	バニッシュフラグ用パラメータワーク構造体
 */
//============================================================================================
void	CT_PokemonVanishOnOff(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_VANISH_ON_OFF *pvoo)
{
	TCB_POKEMON_VANISH_ON_OFF	*tpvoo;
	int							i;

	tpvoo=(TCB_POKEMON_VANISH_ON_OFF *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_POKEMON_VANISH_ON_OFF));

	tpvoo->bw=bw;
	tpvoo->cp=cp;
	tpvoo->command_code=pvoo->command_code;
	tpvoo->client_no=cp->client_no;
	tpvoo->seq_no=0;
	tpvoo->sw=pvoo->sw;
	tpvoo->migawari_flag=pvoo->migawari_flag;

	for(i=0;i<CLIENT_MAX;i++){
		tpvoo->wep.mons_no[i]		=pvoo->wep_mons_no[i];
		tpvoo->wep.sex[i]			=pvoo->wep_sex[i];
		tpvoo->wep.rare[i]			=pvoo->wep_rare[i];
		tpvoo->wep.form_no[i]		=pvoo->wep_form_no[i];
		tpvoo->wep.personal_rnd[i]	=pvoo->wep_personal_rnd[i];
	}

	TCB_Add(TCB_PokemonVanishOnOff,tpvoo,0);
}

//============================================================================================
/**
 *	HPゲージに状態異常アイコンをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_HPGaugeStatusSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_STATUS_SET_PARAM *hgssp)
{
	GF_ASSERT(cp->gauge.cap != NULL);
	
	cp->gauge.status = hgssp->status;
	Gauge_PartsDraw(&cp->gauge, cp->gauge.hp, GAUGE_DRAW_STATUS);
	SCIO_ServerQueClear(bw,cp->client_no,hgssp->command_code);
}

//============================================================================================
/**
 *	トレーナーメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_TrainerMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_MESSAGE_PARAM *tmp)
{
	TCB_MESSAGE_WAIT	*tmw;
	int					tr_id;

	tr_id=BattleWorkTrainerIDGet(bw,cp->client_no);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=tmp->command_code;
	tmw->client_no=cp->client_no;

	tmw->msg_index=TrainerMSG_Print(bw,tr_id,cp->client_no,tmp->type,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	戻すメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_ModosuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MODOSU_MESSAGE_PARAM *mmp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	CT_ModosuMessageParamMake(bw,cp,mmp,&mp);

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=mmp->command_code;
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	繰り出すメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_KuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,KURIDASU_MESSAGE_PARAM *kmp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	CT_KuridasuMessageParamMake(bw,cp,kmp,&mp);

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=kmp->command_code;
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	エンカウントメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_EncountMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	CT_EncountMessageParamMake(bw,cp,&mp);

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=CL_ENCOUNT_MESSAGE;
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	エンカウント時の繰り出すメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_EncountKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ENCOUNT_KURIDASU_MESSAGE_PARAM *ekmp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	CT_EncountKuridasuMessageParamMake(bw,cp,ekmp,&mp);

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=ekmp->command_code;
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	レベルアップエフェクトを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_LevelUpEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_LEVEL_UP_EFFECT	*tlue;

	tlue=(TCB_LEVEL_UP_EFFECT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_LEVEL_UP_EFFECT));

	tlue->bw=bw;
	tlue->command_code=cp->client_buffer[0];
	tlue->client_no=cp->client_no;
	tlue->seq_no=0;
	tlue->gauge=&cp->gauge;

	TCB_Add(TCB_LevelUpEffect,tlue,0);
}

//============================================================================================
/**
 *	アラートメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_AlertMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ALERT_MESSAGE_PARAM *amp)
{
	TCB_ALERT_MESSAGE_WAIT	*tamw;
	MSGDATA_MANAGER			*msg_m;

	//アラートメッセージは自分制御のみ表示
	if(cp->client_boot==CLIENT_BOOT_NORMAL){
		msg_m=BattleWorkFightMsgGet(bw);

		tamw=(TCB_ALERT_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_ALERT_MESSAGE_WAIT));

		tamw->bw=bw;
		tamw->command_code=amp->command_code;
		tamw->client_no=cp->client_no;
		tamw->seq_no=0;

		tamw->msg_index=BattleMSG_Print(bw,msg_m,&amp->mp,BattleWorkConfigMsgSpeedGet(bw));

		TCB_Add(TCB_AlertMessageWait,tamw,0);
	}
	//AIは、返り値のみ
	else if(cp->client_boot==CLIENT_BOOT_AI){
		SCIO_AlertMessageEndSet(bw,cp->client_no);
		SCIO_ServerQueClear(bw,cp->client_no,amp->command_code);
	}
	else{
		//通信対戦時は、返り値はなし
		if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO)==0){
			SCIO_AlertMessageEndSet(bw,cp->client_no);
		}
		SCIO_ServerQueClear(bw,cp->client_no,amp->command_code);
	}
}

//============================================================================================
/**
 *	HPゲージを再描画
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_HPGaugeRefreshSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_REFRESH_PARAM *hgrp)
{
	GAUGE_WORK *gauge;
	
	gauge = &cp->gauge;
	MI_CpuClearFast(&gauge->param, sizeof(GAUGE_SUB_PARAM));
	gauge->bw = bw;
	gauge->client_no = cp->client_no;
	gauge->type = Gauge_TypeGet(cp->client_type, BattleWorkFightTypeGet(bw));
	gauge->command_code = hgrp->command_code;
	gauge->hp = hgrp->hp;
	gauge->hpmax = hgrp->hpmax;
	gauge->level = hgrp->level;
	gauge->sex = hgrp->sex;
	gauge->damage = 0;
	gauge->exp = hgrp->now_exp;
	gauge->max_exp = hgrp->max_exp;
	gauge->sel_mons_no = hgrp->sel_mons_no;
	gauge->status = hgrp->status;
	gauge->getball = hgrp->get_mark;
	gauge->safari_nokori = hgrp->safari_ball;
	
	Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_ALL ^ GAUGE_DRAW_EXP);

	SCIO_ServerQueClear(gauge->bw, gauge->client_no, gauge->command_code);
}

//============================================================================================
/**
 *	技忘れ処理を呼び出し
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_WazaWasureSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_WASURE_PARAM *wwp)
{
	TCB_WAZA_WASURE	*tww;

	tww=(TCB_WAZA_WASURE *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_WAZA_WASURE));

	tww->seq_no=0;
	tww->bw=bw;
	tww->command_code=wwp->command_code;
	tww->client_no=cp->client_no;
	tww->waza_no=wwp->waza_no;
	tww->sel_mons_no=wwp->sel_mons_no;

	TCB_Add(TCB_WazaWasure,tww,0);
}

//============================================================================================
/**
 *	ソフトウエアスプライトにモザイクをかける
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_MosaicSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MOSAIC_SET_PARAM *msp)
{
	TCB_MOSAIC_SET	*tms;

	tms=(TCB_MOSAIC_SET *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MOSAIC_SET));

	tms->seq_no=0;
	tms->bw=bw;
	tms->ss=cp->poke_ss;
	tms->command_code=msp->command_code;
	tms->client_no=cp->client_no;
	tms->mosaic=msp->mosaic;
	tms->wait=0;
	tms->wait_temp=msp->wait;

	TCB_Add(TCB_MosaicSet,tms,0);
}

//============================================================================================
/**
 *	ボールゲージを表示（エンカウント時）
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_BallGaugeEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp)
{
#if 0
	SCIO_ServerQueClear(bw,cp->client_no,bgp->command_code);
#else
	TCB_BALL_GAUGE	*tbg;
	int i;
	
	tbg=(TCB_BALL_GAUGE *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_BALL_GAUGE));

	tbg->seq_no=0;
	tbg->bw=bw;
	tbg->command_code=bgp->command_code;
	tbg->client_no=cp->client_no;
	tbg->client_type=cp->client_type;
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		tbg->status[i] = bgp->status[i];
	}
	
	tbg->encount_change = 0;
	TCB_Add(TCB_BallGaugeEncountSet,tbg,0);
#endif
}

//============================================================================================
/**
 *	ボールゲージを消す（エンカウント時）
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_BallGaugeEncountOut(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp)
{
#if 0
	SCIO_ServerQueClear(bw,cp->client_no,bgp->command_code);
#else
	TCB_BALL_GAUGE	*tbg;
	int i;
	
	tbg=(TCB_BALL_GAUGE *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_BALL_GAUGE));

	tbg->seq_no=0;
	tbg->bw=bw;
	tbg->command_code=bgp->command_code;
	tbg->client_no=cp->client_no;
	tbg->client_type=cp->client_type;

	//OUTには不要
//	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
//		tbg->status[i] = bgp->status[i];
//	}
	
	tbg->encount_change = 0;
	TCB_Add(TCB_BallGaugeEncountOut,tbg,0);
#endif
}

//============================================================================================
/**
 *	ボールゲージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_BallGaugeSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp)
{
	TCB_BALL_GAUGE	*tbg;
	int i;
	
	tbg=(TCB_BALL_GAUGE *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_BALL_GAUGE));

	tbg->seq_no=0;
	tbg->bw=bw;
	tbg->command_code=bgp->command_code;
	tbg->client_no=cp->client_no;
	tbg->client_type=cp->client_type;
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		tbg->status[i] = bgp->status[i];
	}
		
	tbg->encount_change = 1;
	TCB_Add(TCB_BallGaugeEncountSet,tbg,0);
}

//============================================================================================
/**
 *	ボールゲージを消す
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_BallGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp)
{
#if 0
	SCIO_ServerQueClear(bw,cp->client_no,bgp->command_code);
#else
	TCB_BALL_GAUGE	*tbg;
	int i;
	
	tbg=(TCB_BALL_GAUGE *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_BALL_GAUGE));

	tbg->seq_no=0;
	tbg->bw=bw;
	tbg->command_code=bgp->command_code;
	tbg->client_no=cp->client_no;
	tbg->client_type=cp->client_type;

	//OUTには不要
//	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
//		tbg->status[i] = bgp->status[i];
//	}
	
	tbg->encount_change = 1;
	TCB_Add(TCB_BallGaugeEncountOut,tbg,0);
#endif
}

//============================================================================================
/**
 *	通信待機メッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_SioWaitMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	MSGDATA_MANAGER			*msg_m;
	MESSAGE_PARAM			mp;

	//通信待機メッセージは自分制御のみ表示
	if(cp->client_boot==CLIENT_BOOT_NORMAL){
		msg_m=BattleWorkFightMsgGet(bw);

		mp.msg_id=TaikiMsg;
		mp.msg_tag=TAG_NONE;

		BattleMSG_Print(bw,msg_m,&mp,NULL);

		BattleWorkTimeIconSet(bw,TimeWaitIconAdd(BattleWorkGF_BGL_BMPWINGet(bw,TALK_WIN_NO),TALK_WIN_CGX_START));
	}
	SCIO_ServerQueClear(bw,cp->client_no,CL_SIO_WAIT_MESSAGE);
}

//============================================================================================
/**
 *	退避していたキャラを復帰
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_ChrPop(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep)
{
	WAZA_POKE_CHANGE_PARAM	wpcp;

	CT_WazaPokeChangeParamMake(bw,wep,&wpcp,cp->client_no);
	HenshinChrPop(&wpcp,HEAPID_BATTLE);

	SCIO_ServerQueClear(bw,cp->client_no,wep->command_code);
}

//--------------------------------------------------------------
/**
 * @brief   ソフトスプライトをOAMに変換
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
void	CT_SStoOAM(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_SS_TO_OAM	*tsto;
	
	tsto=(TCB_SS_TO_OAM *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_SS_TO_OAM));

	tsto->seq_no=0;
	tsto->bw=bw;
	tsto->cp=cp;
	tsto->command_code=cp->client_buffer[0];
	tsto->client_no=cp->client_no;
	tsto->ss=cp->poke_ss;

	TCB_Add(TCB_SStoOAM,tsto,0);
}

//--------------------------------------------------------------
/**
 * @brief   OAMをソフトスプライトに戻す
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
void	CT_OAMtoSS(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_OAM_TO_SS	*tots;
	
	tots=(TCB_OAM_TO_SS *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_OAM_TO_SS));

	tots->seq_no=0;
	tots->bw=bw;
	tots->cp=cp;
	tots->command_code=cp->client_buffer[0];
	tots->client_no=cp->client_no;
	tots->ss=cp->poke_ss;

	TCB_Add(TCB_OAMtoSS,tots,0);
}

//--------------------------------------------------------------
/**
 * @brief   通信対戦時の勝敗メッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
void	CT_WinLoseMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	CT_WinLoseMessageParamMake(bw,cp,&mp);

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=CL_WIN_LOSE_MESSAGE;
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//--------------------------------------------------------------
/**
 * @brief   通信対戦時のにげるメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
void	CT_EscapeMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ESCAPE_MESSAGE_PARAM *emp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	CT_EscapeMessageParamMake(bw,cp,emp,&mp);

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=CL_ESCAPE_MESSAGE;
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//--------------------------------------------------------------
/**
 * @brief   バトルタワーのリタイアメッセージを表示
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
void	CT_GiveUpMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TCB_MESSAGE_WAIT	*tmw;
	MSGDATA_MANAGER		*msg_m;
	MESSAGE_PARAM		mp;

	CT_GiveUpMessageParamMake(bw,cp,&mp);

	msg_m=BattleWorkFightMsgGet(bw);

	tmw=(TCB_MESSAGE_WAIT *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_MESSAGE_WAIT));

	tmw->bw=bw;
	tmw->command_code=CL_GIVEUP_MESSAGE;
	tmw->client_no=cp->client_no;

	tmw->msg_index=BattleMSG_Print(bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(bw));

	TCB_Add(TCB_MessageWait,tmw,0);
}

//============================================================================================
/**
 *	みがわりキャラをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_MigawariChrSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep)
{
	WAZA_POKE_CHANGE_PARAM	wpcp;

	CT_WazaPokeChangeParamMake(bw,wep,&wpcp,cp->client_no);
	MigawariChrSet(&wpcp,HEAPID_BATTLE);

	SCIO_ServerQueClear(bw,cp->client_no,wep->command_code);
}

//============================================================================================
/**
 *	技効果SEをセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_WazaKoukaSESet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZAKOUKA_SE_PARAM *wsp)
{
	int	pan;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		pan=WAZA_SE_PAN_R;
	}
	else{
		pan=WAZA_SE_PAN_L;
	}

	switch(wsp->kouka){
	case WAZA_HIT_NORMAL:
		Snd_SePlayPan(BSE_HIT_NORMAL,pan);
		break;
	case WAZA_HIT_BATSUGUN:
		Snd_SePlayPan(BSE_HIT_BATSUGUN,pan);
		break;
	case WAZA_HIT_IMAHITOTSU:
		Snd_SePlayPan(BSE_HIT_IMAHITOTSU,pan);
		break;
	}

	SCIO_ServerQueClear(bw,cp->client_no,wsp->command_code);
}

//============================================================================================
/**
 *	曲をセット
 *
 * @param[in]	bw		戦闘システム用ワーク構造体
 * @param[in]	cp		クライアント用パラメータワーク構造体
 */
//============================================================================================
void	CT_BGMPlay(BATTLE_WORK *bw,CLIENT_PARAM *cp,BGM_PLAY_PARAM *bpp)
{
	Snd_BgmPlay(bpp->bgm_no);

	SCIO_ServerQueClear(bw,cp->client_no,bpp->command_code);
}

//-----------------------------------------------------------------------------
//		TCBサブルーチン群
//-----------------------------------------------------------------------------
//============================================================================================
/**
 *	エンカウントポケモン動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonEncount(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_ENCOUNT	*tpe=(TCB_POKEMON_ENCOUNT *)work;
	WE_SYS_PTR			wsp=BattleWorkWE_SYS_PTRGet(tpe->bw);
	s16					x,y;

#ifdef ENCOUNT_SKIP_ON
	//スキップチェック
//	if((BattleWorkFightTypeGet(tpe->bw)&FIGHT_TYPE_SIO)==0){
//		if((sys.trg&PAD_BUTTON_A)&&(tpe->seq_no<3)){
//			tpe->seq_no=5;
//		}
//	}
	if((BattleWorkFightTypeGet(tpe->bw)&FIGHT_TYPE_SIO)==0){
		if((sys.trg&PAD_BUTTON_A)&&(tpe->seq_no<2)){
			tpe->seq_no=2;
		}
	}
#endif ENCOUNT_SKIP_ON

	switch(tpe->seq_no){
	case 0:
		tpe->wait=ENCOUNT_START_WAIT;
		tpe->seq_no++;
	case 1:
		if(--tpe->wait){
			break;
		}
		tpe->seq_no++;
	case 2:
		if(tpe->dir==PARA_FRONT){
			CATS_ObjectPosGetCap(tpe->gw->cap,&x,&y);
			if((tpe->client_type==CLIENT_TYPE_BB)||(tpe->client_type==CLIENT_TYPE_B)){
				if(x<GROUND_ENEMY_X){
					CATS_ObjectPosMoveCap(tpe->gw->cap,ENCOUNT_SPEED,0);
				}
				else{
					CATS_ObjectPosSetCap(tpe->gw->cap,GROUND_ENEMY_X,GROUND_ENEMY_Y);
				}
			}
			CATS_ObjectPosGetCap(tpe->gw->cap,&x,&y);
			if(tpe->client_type==CLIENT_TYPE_BB){
				SoftSpriteParaSet(tpe->ss,SS_PARA_POS_X,x);
			}
			else if(tpe->client_type==CLIENT_TYPE_B){
				x=SoftSpriteParaGet(tpe->ss,SS_PARA_POS_X)-x;
				x-=24;
				SoftSpriteParaCalc(tpe->ss,SS_PARA_POS_X,-x);
			}
			else if(tpe->client_type==CLIENT_TYPE_D){
				x=x-SoftSpriteParaGet(tpe->ss,SS_PARA_POS_X);
				x-=16;
				SoftSpriteParaCalc(tpe->ss,SS_PARA_POS_X,x);
			}
			if(SoftSpriteParaGet(tpe->ss,SS_PARA_POS_X)>=tpe->appear_pos){
				SoftSpriteAnimeSet(tpe->ss,1);
				SoftSpriteParaSet(tpe->ss,SS_PARA_SHADOW_Y_REQ,0);
				SoftSpriteParaSet(tpe->ss,SS_PARA_SHADOW_AFF_REQ,0);
				SoftSpriteParaSet(tpe->ss,SS_PARA_POS_X,tpe->appear_pos);
				PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpe->bw),tpe->ss,tpe->mons_no,tpe->dir,tpe->chr,PARA_HFLIP_OFF,tpe->client_no);

//				Snd_PMVoicePlayEx(tpe->voice,tpe->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,HEAPID_BATTLE);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpe->bw,tpe->client_no),
								 tpe->voice,tpe->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
				if((tpe->client_type==CLIENT_TYPE_BB)||(tpe->client_type==CLIENT_TYPE_B)){
					CATS_ObjectPosSetCap(tpe->gw->cap,GROUND_ENEMY_X,GROUND_ENEMY_Y);
				}
				SoftSpritePalFadeSet(tpe->ss,8,0,0,0x0000);
				tpe->seq_no++;
			}
		}
		else{
			CATS_ObjectPosGetCap(tpe->gw->cap,&x,&y);
			if((tpe->client_type==CLIENT_TYPE_AA)||(tpe->client_type==CLIENT_TYPE_A)){
				if(x>GROUND_MINE_X){
					CATS_ObjectPosMoveCap(tpe->gw->cap,-ENCOUNT_SPEED,0);
				}
				else{
					CATS_ObjectPosSetCap(tpe->gw->cap,GROUND_MINE_X,GROUND_MINE_Y);
				}
			}
			CATS_ObjectPosGetCap(tpe->gw->cap,&x,&y);
			if(tpe->client_type==CLIENT_TYPE_AA){
				SoftSpriteParaSet(tpe->ss,SS_PARA_POS_X,x);
			}
			else if(tpe->client_type==CLIENT_TYPE_A){
				x=x-SoftSpriteParaGet(tpe->ss,SS_PARA_POS_X);
				x-=24;
				SoftSpriteParaCalc(tpe->ss,SS_PARA_POS_X,x);
			}
			else if(tpe->client_type==CLIENT_TYPE_C){
				x=SoftSpriteParaGet(tpe->ss,SS_PARA_POS_X)-x;
				x-=16;
				SoftSpriteParaCalc(tpe->ss,SS_PARA_POS_X,-x);
			}
			if(SoftSpriteParaGet(tpe->ss,SS_PARA_POS_X)<=tpe->appear_pos){
				SoftSpriteParaSet(tpe->ss,SS_PARA_POS_X,tpe->appear_pos);
				PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpe->bw),tpe->ss,tpe->mons_no,tpe->dir,tpe->chr,PARA_HFLIP_OFF,tpe->client_no);
//				Snd_PMVoicePlayEx(tpe->voice,tpe->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,HEAPID_BATTLE);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpe->bw,tpe->client_no),
								 tpe->voice,tpe->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
				if((tpe->client_type==CLIENT_TYPE_AA)||(tpe->client_type==CLIENT_TYPE_A)){
					CATS_ObjectPosSetCap(tpe->gw->cap,GROUND_MINE_X,GROUND_MINE_Y);
				}
				tpe->seq_no++;
			}
		}
		break;
	case 3:
		if((PokeAnm_IsFinished(BattleWorkPokeAnmSysPTRGet(tpe->bw),tpe->client_no)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(tpe->ss)==FALSE)){
			if(tpe->rare){
				{
					WAZA_EFFECT_PARAM	wep;

					SCIO_EffectDataSet(tpe->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_REA,tpe->client_no,tpe->client_no,NULL);
					CT_WesCall(tpe->bw,tpe->cp,wsp,&wep);
				}
				tpe->seq_no=4;
			}
			else{
				tpe->seq_no=0xff;
			}
		}
		break;
	case 4:
		WES_Executed(wsp);
		if (IsWES_Executed(wsp) == FALSE){		///< Effect Commond End Check
			WES_Reset(wsp);						///< Sysmte Reset
			tpe->seq_no=0xff;
		}
		break;
	//スキップシーケンス
	case 5:
		if(tpe->dir==PARA_FRONT){
			SoftSpriteAnimeSet(tpe->ss,1);
			SoftSpriteParaSet(tpe->ss,SS_PARA_SHADOW_Y_REQ,0);
			SoftSpriteParaSet(tpe->ss,SS_PARA_SHADOW_AFF_REQ,0);
			SoftSpriteParaSet(tpe->ss,SS_PARA_POS_X,tpe->appear_pos);
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpe->bw),tpe->ss,tpe->mons_no,tpe->dir,tpe->chr,PARA_HFLIP_OFF,tpe->client_no);

			PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpe->bw,tpe->client_no),
							 tpe->voice,tpe->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			if((tpe->client_type==CLIENT_TYPE_BB)||(tpe->client_type==CLIENT_TYPE_B)){
				CATS_ObjectPosSetCap(tpe->gw->cap,GROUND_ENEMY_X,GROUND_ENEMY_Y);
			}
			SoftSpritePalFadeSet(tpe->ss,8,0,0,0x0000);
		}
		else{
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpe->bw),tpe->ss,tpe->mons_no,tpe->dir,tpe->chr,PARA_HFLIP_OFF,tpe->client_no);
			PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpe->bw,tpe->client_no),
							 tpe->voice,tpe->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			SoftSpriteParaSet(tpe->ss,SS_PARA_POS_X,tpe->appear_pos);
			if((tpe->client_type==CLIENT_TYPE_AA)||(tpe->client_type==CLIENT_TYPE_A)){
				CATS_ObjectPosSetCap(tpe->gw->cap,GROUND_MINE_X,GROUND_MINE_Y);
			}
		}
		tpe->seq_no=3;
		break;
	default:
		SCIO_ServerQueClear(tpe->bw,tpe->client_no,tpe->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	ポケモン登場エフェクトボールエフェクトテーブル
 */
//============================================================================================

const	u8	BallMoveEffectTable[]={
	EBMT_THROW_C,		///< 1匹の時
	EBMT_STAY_BB,
	EBMT_THROW_L,		///< 左に投げ落ちる
	EBMT_STAY_B,
	EBMT_THROW_R,		///< 右に投げ落ちる
	EBMT_STAY_D,
};

//============================================================================================
/**
 *	ポケモン登場エフェクト動作シーケンス用TCB（エンカウント時専用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonEncountAppear(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_APPEAR	*tpa=(TCB_POKEMON_APPEAR *)work;

	switch(tpa->seq_no){
	case 0:
		tpa->wait = 0;
		tpa->seq_no++;
		
	case 1:
		{
			TBALL_CUSTOM_PARAM bcp = { 0 };
			
			bcp.client_type = tpa->client_type;	
			bcp.pp = BattleWorkPokemonParamGet(tpa->bw, tpa->client_no, tpa->sel_mons_no);		
			tpa->bes = BallEffect_Init(HEAPID_BATTLE, &bcp);
			BallEffect_ResourceLoad(tpa->bes);
		}
		tpa->seq_no++;
		break;
		
	case 2:
//		if(BM_ModeGet(tpa->bms)!=EBMM_THROW){
		if(BM_ModeGet(tpa->cp->bms)!=EBMM_THROW){
			break;
		}
		
		if (BallEffect_IsLoadEnd(tpa->bes) != TRUE){
			break;
		}
		
//		if (BM_IsOpen(tpa->bms) == TRUE){
		if (BM_IsOpen(tpa->cp->bms) == TRUE){
			if(tpa->client_type == CLIENT_TYPE_C){
				//味方側2体目は鳴き声が被らないように少し遅らせて登場
				//(敵側2体目はボール投げエフェクトの方でやっている)
				tpa->wait++;
				if(tpa->wait >= ENCOUNT_DOUBLE_APPEAR_WAIT){
					tpa->wait = 0;
				}
				else{
					break;
				}
			}
			
			{	///< ポケモン生成 本来なら、case 1 が望ましい。
				SOFT_SPRITE_MANAGER	*ssm;
				SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];

				ssm=BattleWorkSoftSpriteManagerGet(tpa->bw);
				PokeAnmDataSet(&ssanm[0],tpa->mons_no);

				tpa->cp->poke_ss=CT_SoftSpriteAdd(tpa->bw,ssm,&tpa->ssa,
												  AppearPosTable[tpa->client_type][POS_APPEAR],
												  EncountPosTable[tpa->client_type][1],
												  EncountPosTable[tpa->client_type][2],
												  tpa->ofs_y,
												  tpa->height,
												  tpa->ofs_x,
												  tpa->shadow,
												  tpa->client_no,&ssanm[0],NULL);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_APPEAR_X_S);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_APPEAR_Y_S);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_Y_REQ,0);
				SoftSpriteParaSet(tpa->cp->poke_ss, SS_PARA_VANISH, TRUE);
			}
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,16,0,BallHikariColor[tpa->ballID]);
			SoftSpriteParaSet(tpa->cp->poke_ss, SS_PARA_VANISH, FALSE);
			BallEffect_ExecutedEz(tpa->bes);
			if(tpa->dir==PARA_FRONT){
				Snd_SePlayPan(BSE_BALL_OPEN,WAZA_SE_PAN_R);
			}
			else{
				Snd_SePlayPan(BSE_BALL_OPEN,WAZA_SE_PAN_L);
			}
			tpa->seq_no++;
		}
		break;
		
	case 3:
//		if(BM_EndCheck(tpa->bms) != TRUE){
		if(BM_EndCheck(tpa->cp->bms) != TRUE){
			tpa->seq_no++;
		}
		
	case 4:
		if((SoftSpriteParaGet(tpa->cp->poke_ss,SS_PARA_AFF_X)==AFF_APPEAR_X_B)
		&&(BallEffect_EndCheck(tpa->bes) == FALSE)){
			if(tpa->dir==PARA_FRONT){
				SoftSpriteAnimeSet(tpa->cp->poke_ss,1);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_AFF_REQ,0);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			else{
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpa->bw),
							  tpa->cp->poke_ss,tpa->mons_no,tpa->dir,tpa->chr,PARA_HFLIP_OFF,tpa->client_no);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,0,0,BallHikariColor[tpa->ballID]);
			tpa->seq_no = 5;
		}
		else if(SoftSpriteParaGet(tpa->cp->poke_ss,SS_PARA_AFF_X)>=AFF_APPEAR_X_B){
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_APPEAR_X_B);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_APPEAR_Y_B);	
			if(tpa->dir==PARA_FRONT){
				SoftSpriteAnimeSet(tpa->cp->poke_ss,1);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_AFF_REQ,0);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			else{
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpa->bw),
							  tpa->cp->poke_ss,tpa->mons_no,tpa->dir,tpa->chr,PARA_HFLIP_OFF,tpa->client_no);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,0,1,BallHikariColor[tpa->ballID]);
			tpa->seq_no = 5;
		}
		else {
			SoftSpriteParaCalc(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_SPEED);
			SoftSpriteParaCalc(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_SPEED);
			SoftSpriteOYCalc(tpa->cp->poke_ss,tpa->height);
		}
		break;
	case 5:
		if(BallEffect_EndCheck(tpa->bes) == FALSE){
			tpa->seq_no = 6;
		}
		break;
	case 6:
		if((PokeAnm_IsFinished(BattleWorkPokeAnmSysPTRGet(tpa->bw),tpa->client_no)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(tpa->cp->poke_ss)==FALSE)){
//			BM_Delete(tpa->bms);
			BM_Delete(tpa->cp->bms);
			tpa->cp->bms=NULL;
			BallEffect_FreeMemory(tpa->bes);
			if(tpa->rare){
				{
					WAZA_EFFECT_PARAM	wep;

					tpa->wsp=WES_Create(HEAPID_BATTLE);
					SCIO_EffectDataSet(tpa->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_REA,tpa->client_no,tpa->client_no,NULL);
					CT_WesCall(tpa->bw,tpa->cp,tpa->wsp,&wep);
				}
				tpa->seq_no=7;
			}
			else{
				tpa->seq_no=0xff;
			}
		}
		break;
	case 7:
		WES_Executed(tpa->wsp);
		if (IsWES_Executed(tpa->wsp) == FALSE){		///< Effect Commond End Check
			WES_Reset(tpa->wsp);						///< Sysmte Reset
			WES_Delete(tpa->wsp);						///< Sysmte Delete
			tpa->seq_no=0xff;
		}
		break;
	default:
		SCIO_ServerQueClear(tpa->bw,tpa->client_no,tpa->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
/*
	switch(tpa->seq_no){
	case 0:
		if(BM_ModeGet(tpa->bms)!=EBMM_THROW){
			break;
		}
		if(BM_EndCheck(tpa->bms)==TRUE){
			break;
		}
		BM_Delete(tpa->bms);
		{
			SOFT_SPRITE_MANAGER	*ssm;
			SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];

			ssm=BattleWorkSoftSpriteManagerGet(tpa->bw);
			PokeAnmDataSet(&ssanm[0],tpa->mons_no);

			tpa->cp->poke_ss=CT_SoftSpriteAdd(tpa->bw,ssm,&tpa->ssa,
											  AppearPosTable[tpa->client_type][POS_APPEAR],
											  EncountPosTable[tpa->client_type][1],
											  EncountPosTable[tpa->client_type][2],
											  tpa->ofs_y,
											  tpa->height,
											  tpa->client_no,&ssanm[0],NULL);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_APPEAR_X_S);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_APPEAR_Y_S);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,16,0,BallHikariColor[tpa->ballID]);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_Y_REQ,0);

			tpa->seq_no++;
		}
		break;
	case 1:
		{
			TBALL_CUSTOM_PARAM bcp = { 0 };

			bcp.client_type = tpa->client_type;	
			bcp.pp = BattleWorkPokemonParamGet(tpa->bw, tpa->client_no, tpa->sel_mons_no);		
			tpa->bes = BallEffect_Init(HEAPID_BATTLE, &bcp);
			BallEffect_ResourceLoad(tpa->bes);

			tpa->seq_no++;
		}
		break;
	case 2:
		BallEffect_ExecutedEz(tpa->bes);
		Snd_SePlay(BSE_BALL_OPEN);
		tpa->seq_no++;
		break;
	case 3:
		if((SoftSpriteParaGet(tpa->cp->poke_ss,SS_PARA_AFF_X)==AFF_APPEAR_X_B)
		&&(BallEffect_EndCheck(tpa->bes) == FALSE)){
			if(tpa->dir==PARA_FRONT){
				SoftSpriteAnimeSet(tpa->cp->poke_ss,1);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_AFF_REQ,0);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,HEAPID_BATTLE);
			}
			else{
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,HEAPID_BATTLE);
			}
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpa->bw),
							  tpa->cp->poke_ss,tpa->mons_no,tpa->dir,tpa->chr,PARA_HFLIP_OFF,tpa->client_no);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,0,0,BallHikariColor[tpa->ballID]);
			tpa->seq_no = 6;
		}
		else if(SoftSpriteParaGet(tpa->cp->poke_ss,SS_PARA_AFF_X)>=AFF_APPEAR_X_B){
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_APPEAR_X_B);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_APPEAR_Y_B);	
			if(tpa->dir==PARA_FRONT){
				SoftSpriteAnimeSet(tpa->cp->poke_ss,1);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_AFF_REQ,0);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,HEAPID_BATTLE);
			}
			else{
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,HEAPID_BATTLE);
			}
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpa->bw),
							  tpa->cp->poke_ss,tpa->mons_no,tpa->dir,tpa->chr,PARA_HFLIP_OFF,tpa->client_no);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,0,1,BallHikariColor[tpa->ballID]);
			tpa->seq_no = 4;
		}
		else {
			SoftSpriteParaCalc(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_SPEED);
			SoftSpriteParaCalc(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_SPEED);
			SoftSpriteOYCalc(tpa->cp->poke_ss,tpa->height);
		}
		break;
	case 4:
		if(BallEffect_EndCheck(tpa->bes) == FALSE){
			tpa->seq_no = 5;
		}
		break;
	case 5:
		if((PokeAnm_IsFinished(BattleWorkPokeAnmSysPTRGet(tpa->bw),tpa->client_no)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(tpa->cp->poke_ss)==FALSE)){
			SCIO_ServerQueClear(tpa->bw,tpa->client_no,tpa->command_code);
			BallEffect_FreeMemory(tpa->bes);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
*/
}
//============================================================================================
/**
 *	ポケモン登場エフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonAppear(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_APPEAR	*tpa=(TCB_POKEMON_APPEAR *)work;
	WE_SYS_PTR			wsp=BattleWorkWE_SYS_PTRGet(tpa->bw);

	switch(tpa->seq_no){
	case 0:
		{
			///< ボールOAM読み込み
			TBALL_MOVE_DATA bmd;

			bmd.type=BallMoveEffectTable[tpa->client_type];
			bmd.heap_id=HEAPID_BATTLE;
			bmd.id=tpa->client_no;
			bmd.ball_id=tpa->ballID;
			bmd.csp=BattleWorkCATS_SYS_PTRGet(tpa->bw);
			bmd.pfd=BattleWorkPfdGet(tpa->bw);
			bmd.bg_pri = BM_BG_PRI_BATTLE;
			bmd.surface = 0;

			if(tpa->flag==POKEMON_APPEAR_GET_FAILED){
				bmd.mode=EBMM_FAILURE;		///< 失敗専用
			}
			else{
				bmd.mode=EBMM_THROW;
			}

			tpa->bms=BM_Init(&bmd);
		}
		{
			///< ポケモン読み込み
			SOFT_SPRITE_MANAGER	*ssm;
			SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];

			ssm=BattleWorkSoftSpriteManagerGet(tpa->bw);
			PokeAnmDataSet(&ssanm[0],tpa->mons_no);

			tpa->cp->poke_ss=CT_SoftSpriteAdd(tpa->bw,ssm,&tpa->ssa,
											  AppearPosTable[tpa->client_type][POS_APPEAR],
											  EncountPosTable[tpa->client_type][1],
											  EncountPosTable[tpa->client_type][2],
											  tpa->ofs_y,
											  tpa->height,
											  tpa->ofs_x,
											  tpa->shadow,
											  tpa->client_no,&ssanm[0],NULL);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_APPEAR_X_S);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_APPEAR_Y_S);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_Y_REQ,0);
			SoftSpriteParaSet(tpa->cp->poke_ss, SS_PARA_VANISH, TRUE);
		}
		{
			///< OAM落とし
			tpa->ods = OAM_DropAll_Init(tpa->bw, HEAPID_BATTLE);
		}
		tpa->seq_no++;
		break;
		
	case 1:
		{
			///< ボール パーティクル読み込み
			TBALL_CUSTOM_PARAM bcp = { 0 };
			
			bcp.client_type = tpa->client_type;	
			bcp.pp = BattleWorkPokemonParamGet(tpa->bw, tpa->client_no, tpa->sel_mons_no);	
			bcp.ball_id = tpa->ballID;
				
			tpa->bes = BallEffect_Init(HEAPID_BATTLE, &bcp);
			BallEffect_ResourceLoad(tpa->bes);
		}
		tpa->seq_no++;
		break;
		
	case 2:
		if((BM_ModeGet(tpa->bms)!=EBMM_THROW)&&
		   (tpa->flag==POKEMON_APPEAR_KURIDASI)){
			break;
		}
		
		if (BallEffect_IsLoadEnd(tpa->bes) != TRUE){
			break;
		}
		
		if (BM_IsOpen(tpa->bms) == TRUE){
			OAM_DropAll_End(tpa->ods);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,16,0,BallHikariColor[tpa->ballID]);
			SoftSpriteParaSet(tpa->cp->poke_ss, SS_PARA_VANISH, FALSE);
			BallEffect_ExecutedEz(tpa->bes);
			if(tpa->dir==PARA_FRONT){
				Snd_SePlayPan(BSE_BALL_OPEN,WAZA_SE_PAN_R);
			}
			else{
				Snd_SePlayPan(BSE_BALL_OPEN,WAZA_SE_PAN_L);
			}
			tpa->seq_no++;
		}
		break;
		
	case 3:
		if(BM_EndCheck(tpa->bms) != TRUE){
			tpa->seq_no++;
		}
		
	case 4:
		if((SoftSpriteParaGet(tpa->cp->poke_ss,SS_PARA_AFF_X)==AFF_APPEAR_X_B)
		&&(BallEffect_EndCheck(tpa->bes) == FALSE)){
			if(tpa->dir==PARA_FRONT){
				SoftSpriteAnimeSet(tpa->cp->poke_ss,1);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_AFF_REQ,0);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			else{
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpa->bw),
							  tpa->cp->poke_ss,tpa->mons_no,tpa->dir,tpa->chr,PARA_HFLIP_OFF,tpa->client_no);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,0,0,BallHikariColor[tpa->ballID]);
			tpa->seq_no = 5;
		}
		else if(SoftSpriteParaGet(tpa->cp->poke_ss,SS_PARA_AFF_X)>=AFF_APPEAR_X_B){
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_APPEAR_X_B);
			SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_APPEAR_Y_B);	
			if(tpa->dir==PARA_FRONT){
				SoftSpriteAnimeSet(tpa->cp->poke_ss,1);
				SoftSpriteParaSet(tpa->cp->poke_ss,SS_PARA_SHADOW_AFF_REQ,0);
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_FRONT,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			else{
				PokeVoicePlaySet(BattleWorkPerapVoiceGet(tpa->bw,tpa->client_no),
								 tpa->voice,tpa->mons_no,POKE_VOICE_PAN_BACK,POKE_APPEAR_NORMAL_VOL,NULL,HEAPID_BATTLE);
			}
			PokePrgAnmDataSet(BattleWorkPokeAnmSysPTRGet(tpa->bw),
							  tpa->cp->poke_ss,tpa->mons_no,tpa->dir,tpa->chr,PARA_HFLIP_OFF,tpa->client_no);
			SoftSpritePalFadeSet(tpa->cp->poke_ss,16,0,1,BallHikariColor[tpa->ballID]);
			tpa->seq_no = 5;
		}
		else {
			SoftSpriteParaCalc(tpa->cp->poke_ss,SS_PARA_AFF_X,AFF_SPEED);
			SoftSpriteParaCalc(tpa->cp->poke_ss,SS_PARA_AFF_Y,AFF_SPEED);
			SoftSpriteOYCalc(tpa->cp->poke_ss,tpa->height);
		}
		break;
	case 5:
		if(BallEffect_EndCheck(tpa->bes) == FALSE){
			tpa->seq_no = 6;
		}
		break;
	case 6:
		if((PokeAnm_IsFinished(BattleWorkPokeAnmSysPTRGet(tpa->bw),tpa->client_no)==TRUE)&&
		   (SoftSpriteAnimeEndCheck(tpa->cp->poke_ss)==FALSE)){
			BM_Delete(tpa->bms);
			BallEffect_FreeMemory(tpa->bes);
			if(tpa->rare){
				{
					WAZA_EFFECT_PARAM	wep;

					SCIO_EffectDataSet(tpa->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_REA,tpa->client_no,tpa->client_no,NULL);
					CT_WesCall(tpa->bw,tpa->cp,wsp,&wep);
				}
				tpa->seq_no=7;
			}
			else{
				tpa->seq_no=8;
			}
		}
		break;
	case 7:
	case 9:
	case 11:
		WES_Executed(wsp);
		if (IsWES_Executed(wsp) == FALSE){		///< Effect Commond End Check
			WES_Reset(wsp);					///< Sysmte Reset
			tpa->seq_no++;
		}
		break;
	case 8:
		if(tpa->migawari_flag){
			{
				WAZA_EFFECT_PARAM		wep;
	
				SCIO_EffectDataSet(tpa->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_OUT,tpa->client_no,tpa->client_no,NULL);
				CT_WesCall(tpa->bw,tpa->cp,wsp,&wep);
			}
			tpa->seq_no++;
		}
		else{
			tpa->seq_no=0xff;
		}
		break;
	case 10:
		{
			WAZA_POKE_CHANGE_PARAM	wpcp;
			WAZA_EFFECT_PARAM		wep;

			CT_WazaPokeChangeParamMake(tpa->bw,&tpa->wep,&wpcp,tpa->client_no);
			MigawariChrSet(&wpcp,HEAPID_BATTLE);

			SCIO_EffectDataSet(tpa->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_IN,tpa->client_no,tpa->client_no,NULL);
			CT_WesCall(tpa->bw,tpa->cp,wsp,&wep);
			tpa->cp->migawari_flag=1;
		}
		tpa->seq_no++;
		break;
	default:
		SCIO_ServerQueClear(tpa->bw,tpa->client_no,tpa->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	ポケモン引っ込めるエフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonReturn(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_RETURN	*tpr=(TCB_POKEMON_RETURN *)work;
	WE_SYS_PTR			wsp=BattleWorkWE_SYS_PTRGet(tpr->bw);

	switch(tpr->seq_no){
	case 0:
		if(tpr->migawari_flag){
			{
				WAZA_EFFECT_PARAM	wep;

				SCIO_EffectDataSet(tpr->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_OUT,tpr->client_no,tpr->client_no,NULL);
				CT_WesCall(tpr->bw,tpr->cp,wsp,&wep);
			}
			tpr->seq_no++;
		}
		else{
			tpr->seq_no=4;
		}
		break;

	case 2:
		{
			WAZA_POKE_CHANGE_PARAM	wpcp;
			WAZA_EFFECT_PARAM		wep;

			CT_WazaPokeChangeParamMake(tpr->bw,&tpr->wep,&wpcp,tpr->client_no);
			HenshinChrPop(&wpcp,HEAPID_BATTLE);

			SCIO_EffectDataSet(tpr->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_IN,tpr->client_no,tpr->client_no,NULL);
			CT_WesCall(tpr->bw,tpr->cp,wsp,&wep);
			tpr->cp->migawari_flag=0;
		}
		tpr->seq_no++;
		break;
	//もろもろのエフェクト終了待ち
	case 1:
	case 3:
		WES_Executed(wsp);
		if (IsWES_Executed(wsp) == FALSE){		///< Effect Commond End Check
			WES_Reset(wsp);						///< Sysmte Reset
			tpr->seq_no++;
		}
		break;
	case 4:
		if(tpr->client_type&CLIENT_ENEMY_FLAG){
			{
				TBALL_MOVE_DATA bmd;
	
				bmd.type=BallMoveEffectTable[tpr->client_type];
				bmd.heap_id=HEAPID_BATTLE;
				bmd.mode=EBMM_CLOSE;
				bmd.id=tpr->client_no;
				bmd.ball_id=tpr->ballID;
				bmd.csp=BattleWorkCATS_SYS_PTRGet(tpr->bw);
				bmd.pfd=BattleWorkPfdGet(tpr->bw);
				bmd.bg_pri = BM_BG_PRI_BATTLE;
				bmd.surface = 0;
				tpr->bms=BM_Init(&bmd);
			}
		}
		tpr->seq_no=5;
		SoftSpritePalFadeSet(tpr->ss,0,16,0,BallHikariColor[tpr->ballID]);
		switch(tpr->client_type){
		case CLIENT_TYPE_AA:
		case CLIENT_TYPE_A:
		case CLIENT_TYPE_C:
			Snd_SePlayPan(BSE_BALL_OPEN,WAZA_SE_PAN_L);
			break;
		case CLIENT_TYPE_BB:
		case CLIENT_TYPE_B:
		case CLIENT_TYPE_D:
			Snd_SePlayPan(BSE_BALL_OPEN,WAZA_SE_PAN_R);
			break;
		}
		break;
	case 5:
		if(SoftSpritePalFadeExist(tpr->ss)==FALSE){
			tpr->seq_no++;
		}
		break;
	case 6:
		SoftSpriteParaCalc(tpr->ss,SS_PARA_AFF_X,-AFF_SPEED);
		SoftSpriteParaCalc(tpr->ss,SS_PARA_AFF_Y,-AFF_SPEED);
		SoftSpriteOYCalc(tpr->ss,tpr->height);
		if(SoftSpriteParaGet(tpr->ss,SS_PARA_AFF_X)<=AFF_APPEAR_X_S){
			SoftSpriteDel(tpr->ss);
			if(tpr->client_type&CLIENT_ENEMY_FLAG){
				tpr->seq_no=7;
			}
			else{
				tpr->seq_no=8;
			}
		}
		break;
	case 7:
		if(BM_EndCheck(tpr->bms)==FALSE){
			BM_Delete(tpr->bms);
			tpr->seq_no=8;
		}
		break;
	case 8:
		SCIO_ServerQueClear(tpr->bw,tpr->client_no,tpr->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	ポケモン吸い込むエフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonInhale(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_INHALE	*tpi=(TCB_POKEMON_INHALE *)work;

	switch(tpi->seq_no){
	case 0:
		SoftSpriteParaCalc(tpi->ss,SS_PARA_AFF_X,-AFF_SPEED);
		SoftSpriteParaCalc(tpi->ss,SS_PARA_AFF_Y,-AFF_SPEED);
		if(tpi->height){
			tpi->height--;
			SoftSpriteParaCalc(tpi->ss,SS_PARA_POS_Y,-1);
		}
		if(SoftSpriteParaGet(tpi->ss,SS_PARA_AFF_X)<=AFF_APPEAR_X_S){
			SoftSpriteDel(tpi->ss);
			tpi->seq_no++;
		}
		break;
	case 1:
		SCIO_ServerQueClear(tpi->bw,tpi->client_no,tpi->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}
//============================================================================================
/**
 *	エンカウントトレーナー動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_TrainerEncount(TCB_PTR tcb,void *work)
{
	TCB_TRAINER_ENCOUNT	*tte=(TCB_TRAINER_ENCOUNT *)work;
	s16					x,y;
	u32					fight_type;

#ifdef ENCOUNT_SKIP_ON
	//スキップチェック
//	if((BattleWorkFightTypeGet(tte->bw)&FIGHT_TYPE_SIO)==0){
//		if((sys.trg&PAD_BUTTON_A)&&(tte->seq_no<3)){
//			tte->seq_no=4;
//		}
//	}
	if((BattleWorkFightTypeGet(tte->bw)&FIGHT_TYPE_SIO)==0){
		if((sys.trg&PAD_BUTTON_A)&&(tte->seq_no<2)){
			tte->seq_no=2;
		}
	}
#endif ENCOUNT_SKIP_ON

	fight_type=BattleWorkFightTypeGet(tte->bw);

	if((tte->scroll_time<SCROLL_TIME)&&(tte->seq_no>=2)&&
	  ((tte->client_type==CLIENT_TYPE_AA)||(tte->client_type==CLIENT_TYPE_A))){
		GF_BGL_ScrollSet(BattleWorkGF_BGL_INIGet(tte->bw),GF_BGL_FRAME3_M,GF_BGL_SCROLL_X_INC,SCROLL_SPEED);
		tte->scroll_time++;
	}

	switch(tte->seq_no){
	case 0:
		tte->wait=ENCOUNT_START_WAIT;
		tte->seq_no++;
	case 1:
		if(--tte->wait){
			break;
		}
		tte->seq_no++;
	case 2:
		if(tte->dir==PARA_FRONT){
			CATS_ObjectPosGetCap(tte->gw->cap,&x,&y);
			if((tte->client_type==CLIENT_TYPE_BB)||(tte->client_type==CLIENT_TYPE_B)){
				if(x<GROUND_ENEMY_X){
					CATS_ObjectPosMoveCap(tte->gw->cap,ENCOUNT_SPEED,0);
				}
				else{
					CATS_ObjectPosSetCap(tte->gw->cap,GROUND_ENEMY_X,GROUND_ENEMY_Y);
				}
			}
			CATS_ObjectPosGetCap(tte->gw->cap,&x,&y);
			if((tte->client_type==CLIENT_TYPE_BB)||
			  ((tte->client_type==CLIENT_TYPE_B)&&
			  ((fight_type==FIGHT_TYPE_2vs2_TRAINER)||
			   (fight_type==FIGHT_TYPE_BATTLE_TOWER_2vs2)||
			   (fight_type==FIGHT_TYPE_2vs2_SIO)))){
				SoftSpriteParaSet(tte->ss,SS_PARA_POS_X,x);
			}
			else if(tte->client_type==CLIENT_TYPE_B){
				x=SoftSpriteParaGet(tte->ss,SS_PARA_POS_X)-x;
				x-=24;
				SoftSpriteParaCalc(tte->ss,SS_PARA_POS_X,-x);
			}
			else if(tte->client_type==CLIENT_TYPE_D){
				x=x-SoftSpriteParaGet(tte->ss,SS_PARA_POS_X);
				x-=16;
				SoftSpriteParaCalc(tte->ss,SS_PARA_POS_X,x);
			}
			if(SoftSpriteParaGet(tte->ss,SS_PARA_POS_X)>=tte->appear_pos){
				SoftSpriteParaSet(tte->ss,SS_PARA_POS_X,tte->appear_pos);
				if((tte->client_type==CLIENT_TYPE_BB)||(tte->client_type==CLIENT_TYPE_B)){
					CATS_ObjectPosSetCap(tte->gw->cap,GROUND_ENEMY_X,GROUND_ENEMY_Y);
				}
				tte->seq_no++;
			}
		}
		else{
			CATS_ObjectPosGetCap(tte->gw->cap,&x,&y);
			if((tte->client_type==CLIENT_TYPE_AA)||(tte->client_type==CLIENT_TYPE_A)){
				if(x>GROUND_MINE_X){
					CATS_ObjectPosMoveCap(tte->gw->cap,-ENCOUNT_SPEED,0);
				}
				else{
					CATS_ObjectPosSetCap(tte->gw->cap,GROUND_MINE_X,GROUND_MINE_Y);
				}
			}
			CATS_ObjectPosGetCap(tte->gw->cap,&x,&y);
			if((tte->client_type==CLIENT_TYPE_AA)||
			  ((tte->client_type==CLIENT_TYPE_A)&&
			  ((fight_type==FIGHT_TYPE_2vs2_TRAINER)||
			   (fight_type==FIGHT_TYPE_BATTLE_TOWER_2vs2)||
			   (fight_type==FIGHT_TYPE_TAG_BATTLE)||
			   (fight_type==FIGHT_TYPE_2vs2_SIO)))){
				SoftSpriteParaSet(tte->ss,SS_PARA_POS_X,x);
			}
			else if(tte->client_type==CLIENT_TYPE_A){
				x=x-SoftSpriteParaGet(tte->ss,SS_PARA_POS_X);
				x-=24;
				SoftSpriteParaCalc(tte->ss,SS_PARA_POS_X,x);
			}
			else if(tte->client_type==CLIENT_TYPE_C){
				x=SoftSpriteParaGet(tte->ss,SS_PARA_POS_X)-x;
				x-=16;
				SoftSpriteParaCalc(tte->ss,SS_PARA_POS_X,-x);
			}
			if(SoftSpriteParaGet(tte->ss,SS_PARA_POS_X)<=tte->appear_pos){
				SoftSpriteParaSet(tte->ss,SS_PARA_POS_X,tte->appear_pos);
				if((tte->client_type==CLIENT_TYPE_AA)||(tte->client_type==CLIENT_TYPE_A)){
					CATS_ObjectPosSetCap(tte->gw->cap,GROUND_MINE_X,GROUND_MINE_Y);
				}
				tte->seq_no++;
			}
		}
		break;
	case 3:
		SCIO_ServerQueClear(tte->bw,tte->client_no,tte->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	case 4:
		if(tte->dir==PARA_FRONT){
			SoftSpriteParaSet(tte->ss,SS_PARA_POS_X,tte->appear_pos);
			if((tte->client_type==CLIENT_TYPE_BB)||(tte->client_type==CLIENT_TYPE_B)){
				CATS_ObjectPosSetCap(tte->gw->cap,GROUND_ENEMY_X,GROUND_ENEMY_Y);
			}
		}
		else{
			SoftSpriteParaSet(tte->ss,SS_PARA_POS_X,tte->appear_pos);
			if((tte->client_type==CLIENT_TYPE_AA)||(tte->client_type==CLIENT_TYPE_A)){
				CATS_ObjectPosSetCap(tte->gw->cap,GROUND_MINE_X,GROUND_MINE_Y);
			}
		}		
		tte->seq_no=3;
		break;
	}
}

//============================================================================================
/**
 *	トレーナー投げるエフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
enum{
	SEQTT_TRAINER_THROW_INIT=0,
	SEQTT_TRAINER_THROW_START,
	SEQTT_TRAINER_THROW_OUT,
	SEQTT_TRAINER_THROW_ACT,
	SEQTT_TRAINER_THROW_ACT_WAIT,
	SEQTT_TRAINER_THROW_ACT_END,
	SEQTT_TRAINER_THROW_END,
};

static	void	TCB_TrainerThrow(TCB_PTR tcb,void *work)
{
	TCB_TRAINER_THROW	*ttt=(TCB_TRAINER_THROW *)work;
	s16					x,y;
	int					frame;
	u32					fight_type;
	s16					BallOfs[][5][2]={
										{
											{0xffff,0xffff},{-34, 4},{-28,-11},{50,-12},{0x7fff,0x7fff},	//男主人公
										},
										{
											{0xffff,0xffff},{-34, 4},{-28,-11},{50,-12},{0x7fff,0x7fff},	//女主人公
										},
										{
											{0xffff,0xffff},{-34, 4},{-28,-11},{50,-12},{0x7fff,0x7fff},	//ライバル
										},
										{
											{0xffff,0xffff},{-33,-6},{-28,-18},{50,-36},{0x7fff,0x7fff},	//モミ
										},
										{
											{0xffff,0xffff},{-33,-2},{-28,-18},{50,-28},{0x7fff,0x7fff},	//ゲン
										},
										{
											{0xffff,0xffff},{-34, 4},{-28,-11},{50,-12},{0x7fff,0x7fff},	//マイ
										},
										{
											{0xffff,0xffff},{-34, 4},{-28,-11},{50,-12},{0x7fff,0x7fff},	//バク
										},
										{
											{0xffff,0xffff},{-34, 4},{-23, -1},{50, -2},{0x7fff,0x7fff},	//ミル
										},
									};

	fight_type=BattleWorkFightTypeGet(ttt->bw);

	switch(ttt->seq_no){
	case SEQTT_TRAINER_THROW_INIT:
		if(ttt->type==TT_TYPE_ENCOUNT){
			ttt->seq_no=SEQTT_TRAINER_THROW_START;
		}
		else{
			{
				TBALL_MOVE_DATA bmd;

				switch(ttt->type){
				default:
				case TT_TYPE_SAFARI_BALL:
					bmd.type=EBMT_CAPTURE_BB;		///< 敵に投げる
					ttt->throw_type=EBMM_CAPTURE;
					bmd.ball_id=ITEM_SAFARIBOORU;
					break;
				case TT_TYPE_SAFARI_STONE:
					bmd.type=EBMT_THROW_E0_STONE;	///< 敵に投げる　石
					ttt->throw_type=EBMM_THROW;
					bmd.ball_id=BALL_EFF_STONE;
					break;
				case TT_TYPE_SAFARI_FOOD:
					bmd.type=EBMT_THROW_E0_FOOD;	///< 敵に投げる　エサ
					ttt->throw_type=EBMM_THROW;
					bmd.ball_id=BALL_EFF_FOOD;
					break;
				case TT_TYPE_PARK_BALL:
					bmd.type=EBMT_CAPTURE_BB;		///< 敵に投げる
					ttt->throw_type=EBMM_CAPTURE;
					bmd.ball_id=BALL_EFF_PARK_BALL;
					break;
				}
				bmd.heap_id=HEAPID_BATTLE;
				bmd.mode=EBMM_FREE;
				bmd.id=ttt->client_no;
				bmd.csp=BattleWorkCATS_SYS_PTRGet(ttt->bw);
				bmd.pfd=BattleWorkPfdGet(ttt->bw);
				bmd.surface = 0;
				bmd.bw=ttt->bw;
	
				ttt->cp->bms=BM_Init(&bmd);
				BM_BallSoftPriSet(ttt->cp->bms,100);
				BM_BallBgPriSet(ttt->cp->bms,2);
				BM_BallAnimeFlagSet(ttt->cp->bms,FALSE);

				ttt->cp->cap=CT_TrainerCLACTResourceLoad(ttt->bw,0,ttt->trtype,0);

				x=SoftSpriteParaGet(ttt->cp->tr_ss,SS_PARA_POS_X);
				y=SoftSpriteParaGet(ttt->cp->tr_ss,SS_PARA_POS_Y);
				CATS_ObjectPosSetCap(ttt->cp->cap,x,y);
				CATS_ObjectAnimeFrameSetCap(ttt->cp->cap,0);
				CATS_ObjectAnimeSeqSetCap(ttt->cp->cap,0);
				SoftSpriteParaSet(ttt->cp->tr_ss,SS_PARA_VANISH,1);
				ttt->seq_no=SEQTT_TRAINER_THROW_ACT;
			}
		}
		break;
	case SEQTT_TRAINER_THROW_START:
		if(ttt->dir==PARA_FRONT){
			SoftSpriteParaCalc(ttt->cp->tr_ss,SS_PARA_POS_X,TRAINER_IN_OUT_SPEED);
			if((SoftSpriteParaGet(ttt->cp->tr_ss,SS_PARA_POS_X)>=BALL_THROW_X_R)&&(BM_ModeGet(ttt->cp->bms)!=EBMM_THROW)){
				BM_BallEnable(ttt->cp->bms,CATS_ENABLE_TRUE);
				BM_ModeChange(ttt->cp->bms,EBMM_THROW);
//				ttt->cp->bms=NULL;
				if((fight_type&FIGHT_TYPE_2vs2)&&
				  ((fight_type&FIGHT_TYPE_MULTI)==0)){
					{
						CLIENT_PARAM *cp;

						cp=BattleWorkClientParamGet(ttt->bw,BattleWorkPartnerClientNoGet(ttt->bw,ttt->client_no));
						BM_BallEnable(cp->bms,CATS_ENABLE_TRUE);
						BM_ModeChange(cp->bms,EBMM_THROW);
						BM_BallWaitSet(cp->bms, ENCOUNT_DOUBLE_APPEAR_WAIT);
//						cp->bms=NULL;
					}
				}
			}
			else if(SoftSpriteParaGet(ttt->cp->tr_ss,SS_PARA_POS_X)>=FRAME_OUT_X_R){
				SoftSpriteDel(ttt->cp->tr_ss);
				ttt->cp->tr_ss=NULL;
				ttt->seq_no=SEQTT_TRAINER_THROW_END;
			}
		}
		else{
			x=SoftSpriteParaGet(ttt->cp->tr_ss,SS_PARA_POS_X);
			y=SoftSpriteParaGet(ttt->cp->tr_ss,SS_PARA_POS_Y);
			CATS_ObjectPosSetCap(ttt->cp->cap,x,y);
			CATS_ObjectAnimeFrameSetCap(ttt->cp->cap,0);
			CATS_ObjectAnimeSeqSetCap(ttt->cp->cap,0);
			ttt->seq_no=SEQTT_TRAINER_THROW_OUT;
			SoftSpriteDel(ttt->cp->tr_ss);
			ttt->cp->tr_ss=NULL;
		}
		break;
	case SEQTT_TRAINER_THROW_OUT:
		CATS_ObjectUpdateCap(ttt->cp->cap);
		CATS_ObjectPosMoveCap(ttt->cp->cap,-TRAINER_IN_OUT_SPEED,0);
		CATS_ObjectPosGetCap(ttt->cp->cap,&x,&y);
		if(ttt->cp->bms){
			frame=CATS_ObjectAnimeFrameGetCap(ttt->cp->cap);
			if(BallOfs[ttt->trtype][frame][0]!=0x7fff){
				BM_BallEnable(ttt->cp->bms,CATS_ENABLE_TRUE);
				BM_BallPosSet(ttt->cp->bms,x+BallOfs[ttt->trtype][frame][0],y+BallOfs[ttt->trtype][frame][1]);
//				if((frame==3)&&(ttt->cp->bms!=NULL)){
				if((frame==3)&&(BM_ModeGet(ttt->cp->bms)!=EBMM_THROW)){
					BM_ModeChange(ttt->cp->bms,EBMM_THROW);
					BM_BallAnimeFlagSet(ttt->cp->bms,TRUE);
//					ttt->cp->bms=NULL;
					if((fight_type&FIGHT_TYPE_2vs2)&&
					  ((fight_type&FIGHT_TYPE_MULTI)==0)){
						{
							CLIENT_PARAM *cp;

							cp=BattleWorkClientParamGet(ttt->bw,BattleWorkPartnerClientNoGet(ttt->bw,ttt->client_no));
							BM_BallPosSet(cp->bms,x+BallOfs[ttt->trtype][frame][0],y+BallOfs[ttt->trtype][frame][1]);
							BM_BallEnable(cp->bms,CATS_ENABLE_TRUE);
							BM_ModeChange(cp->bms,EBMM_THROW);
							BM_BallAnimeFlagSet(cp->bms,TRUE);
//							cp->bms=NULL;
						}
					}
				}
			}
		}
		if(x<=FRAME_OUT_X_L){
			{
				CATS_RES_PTR	crp;
				int				type;

				crp=BattleWorkCATS_RES_PTRGet(ttt->bw);
				type=BattleWorkClientTypeGet(ttt->bw,ttt->client_no)>>1;

				CATS_ActorPointerDelete_S(ttt->cp->cap);
				//リソース削除
				CATS_FreeResourceChar(crp,CHARID_ENCOUNT_TRAINER1+type);
				CATS_FreeResourcePltt(crp,PLTTID_ENCOUNT_TRAINER1+type);
				CATS_FreeResourceCell(crp,CELLID_ENCOUNT_TRAINER1+type);
				CATS_FreeResourceCellAnm(crp,CELLANMID_ENCOUNT_TRAINER1+type);
			}
			ttt->seq_no=SEQTT_TRAINER_THROW_END;
		}
		break;
	case SEQTT_TRAINER_THROW_ACT:
		CATS_ObjectUpdateCap(ttt->cp->cap);
		CATS_ObjectPosGetCap(ttt->cp->cap,&x,&y);
		frame=CATS_ObjectAnimeFrameGetCap(ttt->cp->cap);
		if(ttt->cp->bms!=NULL){
			if(BallOfs[ttt->trtype][frame][0]!=0x7fff){
				BM_BallPosSet(ttt->cp->bms,x+BallOfs[ttt->trtype][frame][0],y+BallOfs[ttt->trtype][frame][1]);
				if((frame==3)&&(BM_ModeGet(ttt->cp->bms)!=ttt->throw_type)){
					BM_ModeChange(ttt->cp->bms,ttt->throw_type);
					BM_BallBgPriSet(ttt->cp->bms,BM_BG_PRI_BATTLE);
					BM_BallAnimeFlagSet(ttt->cp->bms,TRUE);
					if(ttt->throw_type!=EBMM_CAPTURE){
						Snd_SePlay(BSE_SAFARI_THROW);
					}
				}
			}
		}
		if(frame==4){
			ttt->wait=8;
			ttt->seq_no=SEQTT_TRAINER_THROW_ACT_WAIT;
		}
		break;
	case SEQTT_TRAINER_THROW_ACT_WAIT:
		if(--ttt->wait==0){
			{
				CATS_RES_PTR	crp;

				crp=BattleWorkCATS_RES_PTRGet(ttt->bw);

				CATS_ActorPointerDelete_S(ttt->cp->cap);
				//リソース削除
				CATS_FreeResourceChar(crp,CHARID_ENCOUNT_TRAINER1);
				CATS_FreeResourcePltt(crp,PLTTID_ENCOUNT_TRAINER1);
				CATS_FreeResourceCell(crp,CELLID_ENCOUNT_TRAINER1);
				CATS_FreeResourceCellAnm(crp,CELLANMID_ENCOUNT_TRAINER1);
			}
			SoftSpriteParaSet(ttt->cp->tr_ss,SS_PARA_VANISH,0);
			if(ttt->throw_type==EBMM_CAPTURE){
				ttt->seq_no=SEQTT_TRAINER_THROW_END;
			}
			else{
				ttt->seq_no=SEQTT_TRAINER_THROW_ACT_END;
			}
		}
		break;
	case SEQTT_TRAINER_THROW_ACT_END:
		if(BM_EndCheck(ttt->cp->bms)==TRUE){
			break;
		}
		BM_Delete(ttt->cp->bms);
		ttt->cp->bms=NULL;
		ttt->seq_no=SEQTT_TRAINER_THROW_END;
		break;
	case SEQTT_TRAINER_THROW_END:
		SCIO_ServerQueClear(ttt->bw,ttt->client_no,ttt->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	トレーナー画面外エフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_TrainerOut(TCB_PTR tcb,void *work)
{
	TCB_TRAINER_OUT	*tto=(TCB_TRAINER_OUT *)work;

	switch(tto->seq_no){
	case 0:
		if(tto->dir==PARA_FRONT){
			SoftSpriteParaCalc(tto->cp->tr_ss,SS_PARA_POS_X,TRAINER_IN_OUT_SPEED);
			if(SoftSpriteParaGet(tto->cp->tr_ss,SS_PARA_POS_X)>=FRAME_OUT_X_R){
				tto->seq_no++;
			}
		}
		else{
			SoftSpriteParaCalc(tto->cp->tr_ss,SS_PARA_POS_X,-TRAINER_IN_OUT_SPEED);
			if(SoftSpriteParaGet(tto->cp->tr_ss,SS_PARA_POS_X)<=FRAME_OUT_X_L){
				tto->seq_no++;
			}
		}
		break;
	case 1:
		SoftSpriteDel(tto->cp->tr_ss);
		tto->cp->tr_ss=NULL;
		SCIO_ServerQueClear(tto->bw,tto->client_no,tto->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	トレーナー画面内エフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_TrainerIn(TCB_PTR tcb,void *work)
{
	TCB_TRAINER_IN	*tti=(TCB_TRAINER_IN *)work;

	switch(tti->seq_no){
	case 0:
		if(tti->dir==PARA_BACK){
			SoftSpriteParaCalc(tti->ss,SS_PARA_POS_X,TRAINER_IN_OUT_SPEED);
			if(SoftSpriteParaGet(tti->ss,SS_PARA_POS_X)>=tti->appear_pos){
				SoftSpriteParaSet(tti->ss,SS_PARA_POS_X,tti->appear_pos);
				tti->seq_no++;
			}
		}
		else{
			SoftSpriteParaCalc(tti->ss,SS_PARA_POS_X,-TRAINER_IN_OUT_SPEED);
			if(SoftSpriteParaGet(tti->ss,SS_PARA_POS_X)<=tti->appear_pos){
				SoftSpriteParaSet(tti->ss,SS_PARA_POS_X,tti->appear_pos);
				tti->seq_no++;
			}
		}
		break;
	case 1:
		SCIO_ServerQueClear(tti->bw,tti->client_no,tti->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	HPゲージ画面INエフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_HPGaugeIn(TCB_PTR tcb,void *work)
{
	GAUGE_WORK *gauge = work;
	
	switch(gauge->param.seq_no){
	case 0:
		if(gauge->in_wait > 0){
			gauge->in_wait--;
			break;
		}

		Gauge_ScrollEffectSet(gauge, GAUGE_SCROLL_IN);
		Gauge_EnableSet(gauge, CATS_ENABLE_TRUE);
		gauge->param.seq_no++;
		break;
	case 1:
		if(gauge->eff_wait_in_out == TRUE){
			gauge->param.seq_no++;
		}
		break;
	default:
		SCIO_ServerQueClear(gauge->bw, gauge->client_no, gauge->command_code);
		gauge->tcb = NULL;
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	HPゲージ画面INエフェクト動作シーケンス用TCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_HPGaugeOut(TCB_PTR tcb,void *work)
{
	GAUGE_WORK *gauge = work;
	
	switch(gauge->param.seq_no){
	case 0:
		if(gauge->eff_wait_in_out == TRUE){
			gauge->param.seq_no++;
		}
		break;
	default:
		SCIO_ServerQueClear(gauge->bw, gauge->client_no, gauge->command_code);
		gauge->tcb = NULL;
		TCB_Delete(tcb);
		//Gauge_ActorResourceDel(gauge);
		Gauge_EnableSet(gauge, CATS_ENABLE_FALSE);
		break;
	}
}

//============================================================================================
/**
 *	コマンド選択TCB用シーケンスナンバー
 */
//============================================================================================
enum{	//シーケンス番号
	CSSEQ_FAST_LOAD,
	CSSEQ_COMMAND_INIT,
	CSSEQ_COMMAND_MSG_WAIT,
	CSSEQ_COMMAND_INIT_WAIT,
	
	CSSEQ_COMMAND_SELECT_INIT,
	CSSEQ_COMMAND_SELECT,
	CSSEQ_COMMAND_SELECT_EFFWAIT,

	CSSEQ_COMMAND_SELECT_POKE_PARK_EFFWAIT,
	
	CSSEQ_FINISH,

#ifdef PM_DEBUG
	CSSEQ_DEBUG_TOOL_INIT,
	CSSEQ_DEBUG_TOOL_MAIN,
#endif
};

//============================================================================================
/**
 *	コマンド選択TCB（プレイヤー用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_CommandSelect(TCB_PTR tcb,void *work)
{
	TCB_COMMAND_SELECT	*tcs;
	GF_BGL_INI	*bgl;
	BI_PARAM_PTR bip;
	CLIENT_PARAM		*cp;
	u32					fight_type;
	int partner_client;
	GAUGE_WORK *partner_gauge;
	
	tcs=(TCB_COMMAND_SELECT *)work;
	bgl=BattleWorkGF_BGL_INIGet(tcs->bw);
	bip = BattleWorkGF_BGL_BIPGet(tcs->bw);
	cp=BattleWorkClientParamGet(tcs->bw,tcs->client_no);
	fight_type=BattleWorkFightTypeGet(tcs->bw);
	
	partner_client = BattleWorkPartnerClientNoGet(tcs->bw, tcs->client_no);
	if(partner_client != tcs->client_no){
		partner_gauge = BattleWorkGaugeWorkGet(tcs->bw, partner_client);
	}
	else{
		partner_gauge = NULL;
	}

#ifdef PM_DEBUG
	if((sys.cont&(PAD_BUTTON_L|PAD_BUTTON_Y))==(PAD_BUTTON_L|PAD_BUTTON_Y)){
		DebugSoftSpritePosPut(tcs->bw);
	}
#endif PM_DEBUG
	
	switch(tcs->seq_no){
	case CSSEQ_FAST_LOAD:
		{
			//技選択画面の描画を早くする為に、ここで先に技番号やPPなどを
			//もらってデータをメモリに展開しておく 2006.05.12(金) by matsuda
			// ※曽我部さんの支持の元作業してます。
			BINPUT_WAZA_PARAM wazapara;
			int i;
			for(i = 0; i < WAZA_TEMOTI_MAX; i++){
				wazapara.wazano[i] = tcs->wazano[i];
				wazapara.pp[i] = tcs->pp[i];
				wazapara.ppmax[i] = tcs->ppmax[i];
			}
			BINPUT_WazaParaMemoryDecord(BattleWorkGF_BGL_BIPGet(tcs->bw), 
				tcs->client_type, &wazapara);
		}
		tcs->seq_no++;
		//break;
	case CSSEQ_COMMAND_INIT:
		{
			MSGDATA_MANAGER		*msg_m;
			MESSAGE_PARAM		mp;

			msg_m=BattleWorkFightMsgGet(tcs->bw);

			//捕獲デモ
			if(fight_type&FIGHT_TYPE_GET_DEMO){
				switch(BattleWorkDemoSeqNoGet(tcs->bw)){
				case 0:
					mp.msg_tag=TAG_NICK;
					mp.msg_para[0]=tcs->client_no|(tcs->sel_mons_no<<8);
					mp.msg_id=DousuruMsg;
					BattleMSG_Print(tcs->bw,msg_m,&mp,0);
					tcs->seq_no = CSSEQ_COMMAND_INIT_WAIT;
					break;
				case 1:
					mp.msg_tag=TAG_NONE;
					mp.msg_id=GetdemoSupportMMsg1+BattleWorkMySexGet(tcs->bw,CLIENT_NO_MINE);
					tcs->index=BattleMSG_Print(tcs->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tcs->bw));
					tcs->seq_no = CSSEQ_COMMAND_MSG_WAIT;
					break;
				}
			}
			else{
				if(fight_type&FIGHT_TYPE_SAFARI){
					mp.msg_tag=TAG_TRNAME;
					mp.msg_para[0]=BattleWorkTrainerIDGet(tcs->bw,tcs->client_no);
					mp.msg_id=SafariDousuruMsg;
				}
				else if(fight_type&FIGHT_TYPE_POKE_PARK){
					mp.msg_tag=TAG_TRNAME;
					mp.msg_para[0]=BattleWorkTrainerIDGet(tcs->bw,tcs->client_no);
					mp.msg_id=ParkDousuruMsg;
				}
				else{
					mp.msg_tag=TAG_NICK;
					mp.msg_para[0]=tcs->client_no|(tcs->sel_mons_no<<8);
					mp.msg_id=DousuruMsg;
				}
				BattleMSG_Print(tcs->bw,msg_m,&mp,0);
				tcs->seq_no = CSSEQ_COMMAND_INIT_WAIT;
			}
		}
		break;
	case CSSEQ_COMMAND_MSG_WAIT:
		if(GF_MSG_PrintEndCheck(tcs->index)==0){
			tcs->seq_no = CSSEQ_COMMAND_INIT_WAIT;
		}
		break;
	case CSSEQ_COMMAND_INIT_WAIT:
		Gauge_AnimeStart(tcs->gauge);
		Poke_SinCurveSet(cp, tcs->bw);
		tcs->seq_no = CSSEQ_COMMAND_SELECT_INIT;
	case CSSEQ_COMMAND_SELECT_INIT:		///<画面作成
		if(BINPUT_EffectEndCheck(bip) == FALSE){
			break;
		}

		{
			BINPUT_SCENE_COMMAND bsc;
			
			bsc.client_no = tcs->client_no;
			bsc.client_type = tcs->client_type;
			bsc.sel_mons_no = tcs->sel_mons_no;
			bsc.icon_hp = tcs->icon_hp;
			bsc.icon_hpmax = tcs->icon_hpmax;
			bsc.icon_status = tcs->icon_status;
			if(cp->bip_flag){
				BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_DARK);
				if(BattleWorkBattleStatusFlagGet(tcs->bw) & BATTLE_STATUS_FLAG_FIRST_BATTLE){
					BINPUT_CreateBG(bip, BINPUT_TYPE_FIGHTONLY, FALSE, &bsc);
				}
				else if(BattleWorkFightTypeGet(tcs->bw) & FIGHT_TYPE_POKE_PARK){
					BINPUT_CreateBG(bip, BINPUT_TYPE_PARK, FALSE, &bsc);
				}
				else if(BattleWorkFightTypeGet(tcs->bw) & FIGHT_TYPE_SAFARI){
					BINPUT_CreateBG(bip, BINPUT_TYPE_A_SAFARI, FALSE, &bsc);
				}
				else if(bsc.client_type == CLIENT_TYPE_C 
						&& (BattleWorkFightTypeGet(tcs->bw) & FIGHT_TYPE_MULTI) == 0){
					BINPUT_CreateBG(bip, BINPUT_TYPE_A_2, FALSE, &bsc);
				}
				else{
					BINPUT_CreateBG(bip, BINPUT_TYPE_A, FALSE, &bsc);
				}
				BattleWorkCommandSelectFlagSet(tcs->bw, SLIDE_IN_AFTER);
			}
			else{
				if(BattleWorkBattleStatusFlagGet(tcs->bw) & BATTLE_STATUS_FLAG_FIRST_BATTLE){
					BINPUT_CreateBG(bip, BINPUT_COMMAND_IN_FIGHTONLY, FALSE, &bsc);
				}
				else if(BattleWorkFightTypeGet(tcs->bw) & FIGHT_TYPE_POKE_PARK){
					BINPUT_CreateBG(bip, BINPUT_COMMAND_IN_PARK, FALSE, &bsc);
				}
				else if(BattleWorkFightTypeGet(tcs->bw) & FIGHT_TYPE_SAFARI){
					BINPUT_CreateBG(bip, BINPUT_COMMAND_IN_SAFARI, FALSE, &bsc);
				}
				else if(bsc.client_type != CLIENT_TYPE_C){
					BINPUT_CreateBG(bip, BINPUT_COMMAND_IN, FALSE, &bsc);
				}
				else{
					BINPUT_CreateBG(bip, BINPUT_COMMAND_IN_2, FALSE, &bsc);
				}
				cp->bip_flag=1;
			}
			BINPUT_TemotiMotivationParamSet(bip, tcs->motivation);
			BINPUT_StockBallAnimeUpdate(bip, 
				tcs->status[POKEPARTY_MINE], tcs->status[POKEPARTY_ENEMY]);
			BINPUT_StockBallON(bip);
		}
		
		if(partner_gauge != NULL){
			Gauge_ColorBlackSet(partner_gauge);
		}
		
		tcs->seq_no = CSSEQ_COMMAND_SELECT;
		break;
	case CSSEQ_COMMAND_SELECT:
		//HP数値モード、バーモード切替(正規版機能です！デバッグ用じゃないよ！)
		if(sys.trg & PAD_BUTTON_START){
			CLIENT_PARAM	*cp;
			int i;
			for(i=0;i<BattleWorkClientSetMaxGet(tcs->bw);i++){
				cp=BattleWorkClientParamGet(tcs->bw,i);
				Gauge_NumModeChange(&cp->gauge);
			}
		}
		
#ifdef PM_DEBUG

		//HP表示数値切り替え
		if(sys.trg & PAD_BUTTON_SELECT){
			CLIENT_PARAM	*cp;
			int i;
			for(i=0;i<BattleWorkClientSetMaxGet(tcs->bw);i++){
				cp=BattleWorkClientParamGet(tcs->bw,i);
				Gauge_DebugHPPutFlagFlip(&cp->gauge);
				Gauge_PartsDraw(&cp->gauge, cp->gauge.hp, GAUGE_DRAW_ALL);
			}
		}
		//戦闘内デバッグ用パラメータ変更ツール
		if(((sys.cont&(PAD_BUTTON_L|PAD_BUTTON_R))==(PAD_BUTTON_L|PAD_BUTTON_R))&&
			(BattleWorkServerFlagGet(tcs->bw))){
			tcs->seq_no=CSSEQ_DEBUG_TOOL_INIT;
			return;
		}
#endif

		tcs->tp_ret = BINPUT_TouchCheck(bip);
		if(tcs->tp_ret != RECT_HIT_NONE){
			tcs->wait=TP_WAIT;
			Snd_SePlay(BSE_TP_DECIDE);
			tcs->seq_no = CSSEQ_COMMAND_SELECT_EFFWAIT;
		}
		break;
	case CSSEQ_COMMAND_SELECT_EFFWAIT:
		if(BINPUT_EffectEndCheck(bip) == TRUE
				|| tcs->tp_ret == SELECT_FIGHT_COMMAND){	//「たたかう」の場合は次の画面構築をすぐ出せるようにエフェクトの終了を待たずに進める
			switch(tcs->tp_ret){
			case SELECT_FIGHT_COMMAND:
				if(BattleWorkFightTypeGet(tcs->bw)&(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)){
					tcs->seq_no=CSSEQ_COMMAND_SELECT_POKE_PARK_EFFWAIT;
				}
				break;
			case SELECT_ITEM_COMMAND:
				BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
				BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);
				Gauge_ColorNormalSet(partner_gauge);
				Gauge_AnimeStop(tcs->gauge);
				Poke_SinCurveStop(cp);
				break;
			case SELECT_POKEMON_COMMAND:
				BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
				BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);
				Gauge_ColorNormalSet(partner_gauge);
				Gauge_AnimeStop(tcs->gauge);
				Poke_SinCurveStop(cp);
				break;
			case SELECT_ESCAPE_COMMAND:
#ifdef PM_DEBUG
				if(sys.cont&PAD_BUTTON_L){
					tcs->tp_ret = SELECT_DEBUG_WIN_ESCAPE_COMMAND;
				}
				else if((sys.cont&PAD_BUTTON_R)&&((fight_type&FIGHT_TYPE_SIO)==0)){
					tcs->tp_ret = SELECT_DEBUG_ESCAPE_COMMAND;
				}
				else if((BattleWorkEscCanCheck(tcs->bw,tcs->client_no)==TRUE)){
					Gauge_ColorNormalSet(partner_gauge);
					tcs->tp_ret = SELECT_CANCEL;
				}
//				else if((tcs->client_type == CLIENT_TYPE_C)&&
//					   ((fight_type&FIGHT_TYPE_MULTI)==0)){
//					Gauge_ColorNormalSet(partner_gauge);
//					tcs->tp_ret = SELECT_CANCEL;
//				}
#else
				if((BattleWorkEscCanCheck(tcs->bw,tcs->client_no)==TRUE)){
					Gauge_ColorNormalSet(partner_gauge);
					tcs->tp_ret = SELECT_CANCEL;
				}
//				if((tcs->client_type == CLIENT_TYPE_C)&&
//				  ((fight_type&FIGHT_TYPE_MULTI)==0)){
//					Gauge_ColorNormalSet(partner_gauge);
//					tcs->tp_ret = SELECT_CANCEL;
//				}
#endif
				BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
				break;
			default:
				GF_ASSERT_MSG(0 , "コマンド動作が設定されていません\n");
				break;
			}
			
			BINPUT_StockBallOFF(bip);
			tcs->seq_no = CSSEQ_FINISH;
		}
		break;
	case CSSEQ_COMMAND_SELECT_POKE_PARK_EFFWAIT:
		if(BINPUT_EffectEndCheck(bip) == TRUE ){
			BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
			BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);
			Gauge_ColorNormalSet(partner_gauge);
			Gauge_AnimeStop(tcs->gauge);
			Poke_SinCurveStop(cp);
			BINPUT_StockBallOFF(bip);
			tcs->seq_no = CSSEQ_FINISH;
		}
		break;
	case CSSEQ_FINISH:
		if(BINPUT_BackFadeExeCheck(bip) == TRUE){
			SCIO_CommandSelectReturnSet(tcs->bw,tcs->client_no,tcs->tp_ret);
			SCIO_ServerQueClear(tcs->bw,tcs->client_no,tcs->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
#ifdef PM_DEBUG
//戦闘内デバッグ用パラメータ変更ツール
	case CSSEQ_DEBUG_TOOL_INIT:
		DebugBattleInit(tcs->bw);
		tcs->seq_no=CSSEQ_DEBUG_TOOL_MAIN;
		break;
	case CSSEQ_DEBUG_TOOL_MAIN:
		if(DebugBattleMain(tcs->bw)==TRUE){
			tcs->seq_no=CSSEQ_COMMAND_SELECT;
		}
		break;
#endif PM_DEBUG
	}
}

//============================================================================================
/**
 *	コマンド選択TCB（AI用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_CommandSelectAI(TCB_PTR tcb,void *work)
{
	TCB_COMMAND_SELECT	*tcs=(TCB_COMMAND_SELECT *)work;
	int					command;

	//タッチパネルのボタンのスライドインが終了していないときは、AI計算を行わない（処理落ちするとガクつくため）
//	if(BattleWorkCommandSelectFlagGet(tcs->bw)==SLIDE_IN_BEFORE){
//		return;
//	}

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(tcs->bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		//通信接続では、子機側にAIがのっていないので、強制で攻撃を選択
//		if(CommStateIsWifiConnect()){
		if(BattleWorkFightTypeGet(tcs->bw)&FIGHT_TYPE_SIO){
			command=SELECT_FIGHT_COMMAND;
			SCIO_CommandSelectReturnSet(tcs->bw,tcs->client_no,command);

			SCIO_ServerQueClear(tcs->bw,tcs->client_no,tcs->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
			return;
		}
	}
#endif PM_DEBUG

	command=ClientAICommandSelectAI(tcs->bw,tcs->client_no);
	SCIO_CommandSelectReturnSet(tcs->bw,tcs->client_no,command);

	SCIO_ServerQueClear(tcs->bw,tcs->client_no,tcs->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	コマンド選択TCB（通信用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_CommandSelectSIO(TCB_PTR tcb,void *work)
{
	TCB_COMMAND_SELECT	*tcs=(TCB_COMMAND_SELECT *)work;

	SCIO_ServerQueClear(tcs->bw,tcs->client_no,tcs->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	サファリ用逃走率テーブル
 */
//============================================================================================
static	const	u8	SafariEscapeRateTable[][2]={
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
 *	コマンド選択TCB（サファリ用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_CommandSelectSafari(TCB_PTR tcb,void *work)
{
	TCB_COMMAND_SELECT	*tcs=(TCB_COMMAND_SELECT *)work;
	int					rate;
	u16					mons_no;
	u8					escape_count;

	escape_count=BattleWorkSafariEscapeCountGet(tcs->bw);
	mons_no=ST_ServerPokemonServerParamGet(BattleWorkServerParamGet(tcs->bw),tcs->client_no,ID_PSP_monsno,NULL);
	rate=PokePersonalParaGet(mons_no,ID_PER_escape);

	rate=rate*SafariEscapeRateTable[escape_count][0]/SafariEscapeRateTable[escape_count][1];

	if((gf_rand()%255)<=rate){
		SCIO_CommandSelectReturnSet(tcs->bw,tcs->client_no,SELECT_SAFARI_ESCAPE);
	}
	else{
		SCIO_CommandSelectReturnSet(tcs->bw,tcs->client_no,SELECT_SAFARI_YOUSUMI);
	}

	SCIO_ServerQueClear(tcs->bw,tcs->client_no,tcs->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	コマンド選択TCB（ポケパーク用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_CommandSelectPokepark(TCB_PTR tcb,void *work)
{
	TCB_COMMAND_SELECT	*tcs=(TCB_COMMAND_SELECT *)work;

	SCIO_CommandSelectReturnSet(tcs->bw,tcs->client_no,SELECT_POKEPARK_ESCAPE);
	SCIO_ServerQueClear(tcs->bw,tcs->client_no,tcs->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	技選択TCB（プレイヤー用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_WazaSelect(TCB_PTR tcb,void *work)
{
	TCB_WAZA_SELECT	*tws=(TCB_WAZA_SELECT *)work;
	GF_BGL_INI		*bgl=BattleWorkGF_BGL_INIGet(tws->bw);
	BI_PARAM_PTR bip;
	int partner_client;
	GAUGE_WORK *partner_gauge;
	CLIENT_PARAM *cp;
	
	bip = BattleWorkGF_BGL_BIPGet(tws->bw);
	cp=BattleWorkClientParamGet(tws->bw,tws->client_no);

	partner_client = BattleWorkPartnerClientNoGet(tws->bw, tws->client_no);
	if(partner_client != tws->client_no){
		partner_gauge = BattleWorkGaugeWorkGet(tws->bw, partner_client);
	}
	else{
		partner_gauge = NULL;
	}

	switch(tws->seq_no){
	case 0:		///<画面作成
		if(BINPUT_EffectEndCheck(bip) == FALSE){
			break;
		}
		
		{
			MSGDATA_MANAGER		*msg_m;
			MESSAGE_PARAM		mp;

			msg_m=BattleWorkFightMsgGet(tws->bw);
			mp.msg_tag=TAG_NICK;
			mp.msg_para[0]=tws->client_no|(tws->sel_mons_no<<8);
			mp.msg_id=DousuruMsg;
			BattleMSG_Print(tws->bw,msg_m,&mp,0);
		}
		BINPUT_StockBallOFF(bip);
		{
			BINPUT_SCENE_WAZA bsw;
			int i;

			for(i = 0; i < WAZA_TEMOTI_MAX; i++){
				bsw.wazano[i] = tws->wazano[i];
				bsw.pp[i] = tws->pp[i];
				bsw.ppmax[i] = tws->ppmax[i];
			}
			bsw.client_type = tws->client_type;

			BINPUT_CreateBG(bip, BINPUT_TYPE_WAZA, FALSE, &bsw);
		}
		tws->seq_no++;
		break;
	case 1:

#ifdef PM_DEBUG
		//技エフェクトデバッグメニュー
		if (sys.trg & PAD_BUTTON_START){
			//DT_MenuInit(HEAPID_BATTLE, tcs->bw, tcb, TCB_CommandSelect);
			DebugWazaEffectInit(HEAPID_BATTLE, tws->bw, tcb, TCB_WazaSelect);
			return;
		}
#endif

		tws->tp_ret = BINPUT_TouchCheck(bip);
		if(tws->tp_ret!=RECT_HIT_NONE){
			Snd_SePlay(BSE_TP_DECIDE);
			tws->seq_no++;
		}
		break;
	case 2:
		if(1){//BINPUT_EffectEndCheck(bip) == TRUE){
			if(tws->tp_ret != SELECT_CANCEL){
				if((BattleWorkFightTypeGet(tws->bw) & FIGHT_TYPE_2vs2) == 0){
					BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);
					Gauge_ColorNormalSet(partner_gauge);
					Gauge_AnimeStop(tws->gauge);
					Poke_SinCurveStop(cp);
				}
			}
			SCIO_WazaSelectReturnSet(tws->bw,tws->client_no,tws->tp_ret);
			tws->seq_no++;
		}
		break;
	case 3:
//		BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
		tws->seq_no++;
		//break;
	default:
		if(BINPUT_BackFadeExeCheck(bip) == TRUE){
			//捕獲デモ用にシーケンスナンバーを進めておく
			BattleWorkDemoSeqNoSet(tws->bw,1);
			SCIO_ServerQueClear(tws->bw,tws->client_no,tws->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
}

//============================================================================================
/**
 *	技選択TCB（AI用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_WazaSelectAI(TCB_PTR tcb,void *work)
{
	TCB_WAZA_SELECT	*tws=(TCB_WAZA_SELECT *)work;
	SERVER_PARAM	*sp;
	int				tp_ret;
	u32				fight_type;

	fight_type=BattleWorkFightTypeGet(tws->bw);
	sp=BattleWorkServerParamGet(tws->bw);

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(tws->bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		//通信接続では、子機側にAIがのっていないので、ランダムで技を選択
//		if(CommStateIsWifiConnect()){
		if(fight_type&FIGHT_TYPE_SIO){
			{
				int	i;
				int	waza[WAZA_TEMOTI_MAX];
				int	wazacnt;
	
				wazacnt=0;
	
				for(i=0;i<WAZA_TEMOTI_MAX;i++){
					if((tws->wazabit&No2Bit(i))==0){
						waza[wazacnt]=i+1;
						wazacnt++;
					}
				}
				tp_ret=waza[gf_rand()%wazacnt];
			}
			//攻撃対象の代入（DirSelectAIで代入される）
			ST_ServerParamDataPut(tws->bw,sp,ID_SP_dir_select_client,tws->client_no,1);

			SCIO_WazaSelectReturnSet(tws->bw,tws->client_no,tp_ret);

			SCIO_ServerQueClear(tws->bw,tws->client_no,tws->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
			return;
		}
	}
#endif PM_DEBUG

	if((fight_type&FIGHT_TYPE_AI_CALC)||
	   (BattleWorkBattleStatusFlagGet(tws->bw)&BATTLE_STATUS_FLAG_FIRST_BATTLE)||
	   (BattleWorkMineEnemyCheck(tws->bw,tws->client_no)==0)){
		//Wifiの時にここにくるのはおかしいので、ASSERTを出す
		GF_ASSERT(!CommStateIsWifiConnect());
		tp_ret=WazaAIMain(tws->bw,tws->client_no);
		//AI計算が途中なので、再度AIをコールする
		switch(tp_ret){
		//AI計算が途中なので、再度AIをコールする
		case WAZA_AI_CALC_CONTINUE:
			return;
			break;
		default:
			tp_ret++;
			break;
		}
	}
	else{
		{
			int	i;
			int	waza[WAZA_TEMOTI_MAX];
			int	wazacnt;

			wazacnt=0;

			for(i=0;i<WAZA_TEMOTI_MAX;i++){
				if((tws->wazabit&No2Bit(i))==0){
					waza[wazacnt]=i+1;
					wazacnt++;
				}
			}
			tp_ret=waza[gf_rand()%wazacnt];
		}
		//攻撃対象の代入（DirSelectAIで代入される）
		ST_ServerParamDataPut(tws->bw,sp,ID_SP_dir_select_client,tws->client_no,
							  ST_ServerDefenceClientSet(tws->bw,sp,tws->client_no,tws->wazano[tp_ret-1],1,NULL));
	}

	SCIO_WazaSelectReturnSet(tws->bw,tws->client_no,tp_ret);

	SCIO_ServerQueClear(tws->bw,tws->client_no,tws->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	技選択TCB（通信用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_WazaSelectSIO(TCB_PTR tcb,void *work)
{
	TCB_WAZA_SELECT	*tws=(TCB_WAZA_SELECT *)work;

	SCIO_ServerQueClear(tws->bw,tws->client_no,tws->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	攻撃対象選択TCB（プレイヤー用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_DirSelect(TCB_PTR tcb,void *work)
{
	TCB_DIR_SELECT	*tds=(TCB_DIR_SELECT *)work;
	GF_BGL_INI		*bgl=BattleWorkGF_BGL_INIGet(tds->bw);
	BI_PARAM_PTR bip;
	int partner_client;
	GAUGE_WORK *partner_gauge;
	CLIENT_PARAM *cp;

	cp=BattleWorkClientParamGet(tds->bw,tds->client_no);
	bip = BattleWorkGF_BGL_BIPGet(tds->bw);

	partner_client = BattleWorkPartnerClientNoGet(tds->bw, tds->client_no);
	if(partner_client != tds->client_no){
		partner_gauge = BattleWorkGaugeWorkGet(tds->bw, partner_client);
	}
	else{
		partner_gauge = NULL;
	}

	switch(tds->seq_no){
	case 0:		///<画面作成
		if(BINPUT_EffectEndCheck(bip) == FALSE){
			break;
		}

		{
			BINPUT_SCENE_POKE bsp;
			int i;
			
			for(i = 0; i < CLIENT_MAX; i++){
				bsp.dspp[i] = tds->dspp[i];
			}
			bsp.client_type = tds->client_type;
			bsp.pokesele_type = BINPUT_RangeBgTypeGet(tds->range, tds->client_type);
			
			BINPUT_CreateBG(bip, BINPUT_TYPE_POKE, FALSE, &bsp);
		}
		
		tds->seq_no++;
		break;
	case 1:
		tds->tp_ret = BINPUT_TouchCheck(bip);
		if(tds->tp_ret != RECT_HIT_NONE){
			Snd_SePlay(BSE_TP_DECIDE);
			tds->seq_no++;
		}
		break;
	case 2:
		if(1){//BINPUT_EffectEndCheck(bip) == TRUE){
			if(tds->tp_ret != SELECT_CANCEL){
				Gauge_AnimeStop(tds->gauge);
				Poke_SinCurveStop(cp);
				Gauge_ColorNormalSet(partner_gauge);
				if(tds->light_flag == TRUE){
					BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);
				}
			}
			tds->seq_no++;
		}
		break;
	case 3:
//		BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
		tds->seq_no++;
		//break;
	default:
		if(BINPUT_BackFadeExeCheck(bip) == TRUE){
			{
				u8	buf[CLIENT_TYPE_MAX];
				u32	fight_type;
				int	ret;

				ret=tds->tp_ret;
				fight_type=BattleWorkFightTypeGet(tds->bw);

				if(ret != SELECT_CANCEL){
					BattleClientNoBufMake(tds->bw,&buf[0]);
					if(fight_type&FIGHT_TYPE_2vs2){
						ret=buf[CLIENT_TYPE_A+(tds->tp_ret-1)]+1;
					}
					else{
						ret=buf[CLIENT_TYPE_AA+(tds->tp_ret-1)]+1;
					}
				}

				SCIO_DirSelectReturnSet(tds->bw,tds->client_no,ret);
				SCIO_ServerQueClear(tds->bw,tds->client_no,tds->command_code);
				sys_FreeMemoryEz(work);
				TCB_Delete(tcb);
			}
		}
		break;
	}
}

//============================================================================================
/**
 *	攻撃対象選択TCB（AI用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_DirSelectAI(TCB_PTR tcb,void *work)
{
	TCB_DIR_SELECT	*tds=(TCB_DIR_SELECT *)work;
	SERVER_PARAM	*sp;
	int	tp_ret;

	sp=BattleWorkServerParamGet(tds->bw);

//	tp_ret=ST_ServerDefenceClientSet(tds->bw,BattleWorkServerParamGet(tds->bw),tds->client_no,0,1,tds->range)+1;
	tp_ret=ST_ServerParamDataGet(tds->bw,sp,ID_SP_dir_select_client,tds->client_no)+1;
	GF_ASSERT_MSG(tp_ret<5,"tp_retが不正です:%d\n",tp_ret);

	SCIO_DirSelectReturnSet(tds->bw,tds->client_no,tp_ret);

	SCIO_ServerQueClear(tds->bw,tds->client_no,tds->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	攻撃対象選択TCB（通信用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_DirSelectSIO(TCB_PTR tcb,void *work)
{
	TCB_DIR_SELECT	*tds=(TCB_DIR_SELECT *)work;

	SCIO_ServerQueClear(tds->bw,tds->client_no,tds->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	道具選択シーケンスナンバー
 */
//============================================================================================
enum{
	SEQ_ITEM_SEL_INIT=0,
	SEQ_ITEM_SEL_WAIT,
	SEQ_ITEM_SEL_TASK_SET,
	SEQ_ITEM_SEL_MAIN,
	SEQ_ITEM_SEL_POKE_LIST_INIT,
	SEQ_ITEM_SEL_POKE_LIST_MAIN,
	SEQ_ITEM_SEL_END_INIT,
	SEQ_ITEM_SEL_END_WAIT,
	SEQ_ITEM_SEL_END,
	SEQ_ITEM_SEL_USE_MSG,
	SEQ_ITEM_SEL_USE_MSG_WAIT,
	SEQ_ITEM_SEL_BATTLE_EFFECT_INIT1,
	SEQ_ITEM_SEL_BATTLE_EFFECT_WAIT1,
	SEQ_ITEM_SEL_BATTLE_EFFECT_INIT2,
	SEQ_ITEM_SEL_BATTLE_EFFECT_WAIT2,
	SEQ_ITEM_SEL_BATTLE_EFFECT_MSG,
	SEQ_ITEM_SEL_BATTLE_EFFECT_MSG_WAIT,
	SEQ_ITEM_SEL_HPRCV_EFFECT_INIT1,
	SEQ_ITEM_SEL_HPRCV_EFFECT_WAIT1,
	SEQ_ITEM_SEL_HPRCV_EFFECT_INIT2,
	SEQ_ITEM_SEL_HPRCV_EFFECT_WAIT2,
	SEQ_ITEM_SEL_HPRCV_EFFECT_INIT3,
	SEQ_ITEM_SEL_HPRCV_EFFECT_WAIT3,
	SEQ_ITEM_SEL_HPRCV_EFFECT_MSG,
	SEQ_ITEM_SEL_HPRCV_EFFECT_MSG_WAIT,
	SEQ_ITEM_SEL_CONDRCV_EFFECT_INIT1,
	SEQ_ITEM_SEL_CONDRCV_EFFECT_WAIT1,
	SEQ_ITEM_SEL_CONDRCV_EFFECT_INIT2,
	SEQ_ITEM_SEL_CONDRCV_EFFECT_WAIT2,
	SEQ_ITEM_SEL_CONDRCV_EFFECT_MSG,
	SEQ_ITEM_SEL_CONDRCV_EFFECT_MSG_WAIT
};

enum{
	NEMURI_RCV=0,
	DOKU_RCV,
	YAKEDO_RCV,
	KOORI_RCV,
	MAHI_RCV,
	KONRAN_RCV,
	MEROMERO_RCV
};

//============================================================================================
/**
 *	道具選択TCB（プレイヤー用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_ItemSelect(TCB_PTR tcb,void *work)
{
	TCB_ITEM_SELECT	*tis=(TCB_ITEM_SELECT *)work;
	PALETTE_FADE_PTR	pfd;

	pfd=BattleWorkPfdGet(tis->bw);
	
	switch(tis->seq_no){
	case SEQ_ITEM_SEL_INIT:		//バッグ画面へのフェード
		//BIPが解放されるまえに必要な情報だけ取得
		tis->decend_key = BINPUT_CursorDecendGet(BattleWorkGF_BGL_BIPGet(tis->bw));
		
		MSG_DsIconFlashReq(BattleWorkMsgIconGet(tis->bw),MSG_DSI_REQ_STOP);
		PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0x0c00,BATTLE_BAGLIST_FADE_SPEED,0,MSG_WINDOW_FADE,0x0000);
		PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,BATTLE_BAGLIST_FADE_SPEED,0,16,0x0000);
		tis->seq_no++;
		break;
	case SEQ_ITEM_SEL_WAIT:
		if(PaletteFadeCheck(pfd)==0){	//輝度変更フェード終了待ちして色々削除
			{
				FightScreenTransition(tis->bw);

				tis->bag_buf=sys_AllocMemory(HEAPID_BATTLE,sizeof(BBAG_DATA));
				tis->bag_buf->bw=tis->bw;
				tis->bag_buf->myst=BattleWorkMyStatusGet(tis->bw,tis->client_no);
				tis->bag_buf->heap=HEAPID_BATTLE;
				tis->bag_buf->end_flg=0;
				tis->bag_buf->myitem=BattleWorkMyItemGet(tis->bw);
				tis->bag_buf->client_no=tis->client_no;
				tis->bag_buf->cursor_flg=tis->decend_key;
				tis->bag_buf->enc_double=tis->enc_double;
				tis->bag_buf->waza_vanish=tis->waza_vanish;
				tis->bag_buf->waza_migawari=tis->waza_migawari;
				tis->bag_buf->skill_item_use=tis->shutout_flag[tis->client_no];	// 技で使用不可
				BattleBag_TaskAdd( tis->bag_buf );
				tis->seq_no=SEQ_ITEM_SEL_MAIN;
			}
		}
		break;
	case SEQ_ITEM_SEL_TASK_SET:
		tis->bag_buf->cursor_flg=tis->decend_key;
		BattleBag_TaskAdd( tis->bag_buf );
		tis->seq_no++;
	case SEQ_ITEM_SEL_MAIN:
		if(tis->bag_buf->end_flg){
			tis->bag_buf->end_flg=0;
			tis->decend_key = tis->bag_buf->cursor_flg;
			if(tis->bag_buf->ret_item){
				switch(tis->bag_buf->ret_page){
				case BBAG_POKE_STRCV:	// 状態回復ポケット
				case BBAG_POKE_HPRCV:	// HP回復ポケット
					tis->seq_no=SEQ_ITEM_SEL_POKE_LIST_INIT;
					break;
				case BBAG_POKE_BATTLE:	// 戦闘用ポケット
				case BBAG_POKE_BALL:	// ボールポケット
					tis->seq_no=SEQ_ITEM_SEL_END_INIT;
					break;
				}
			}
			else{
				tis->seq_no=SEQ_ITEM_SEL_END_INIT;
			}
		}
		break;
	//ポケモンリスト画面へ
	case SEQ_ITEM_SEL_POKE_LIST_INIT:
		{
			int				i;
			int				cnt=0;
			int				client_no;
			POKEPARTY		*poke_party=BattleWorkPokePartyGet(tis->bw,tis->client_no);
			POKEMON_PARAM	*pp;

			if((BattleWorkFightTypeGet(tis->bw)&FIGHT_TYPE_2vs2)&&
			  ((BattleWorkFightTypeGet(tis->bw)&FIGHT_TYPE_MULTI)==0)){
				client_no=tis->client_no&1;
			}
			else{
				client_no=tis->client_no;
			}

			PokeParty_Init(tis->tps->plist->pp,TEMOTI_POKEMAX);

			for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
				pp=BattleWorkPokemonParamGet(tis->bw,client_no,tis->list_row[client_no][i]);
				PokeParty_Add(tis->tps->plist->pp,pp);
				tis->tps->plist->list_row[i]=tis->list_row[client_no][i];
			}

			tis->tps->plist->bw = tis->bw;
			tis->tps->plist->heap = HEAPID_BATTLE;
			tis->tps->plist->sel_poke = 0;
			tis->tps->plist->end_flg = 0;
			tis->tps->plist->chg_waza=0;
			tis->tps->plist->mode=BPL_MODE_ITEMUSE;	// 通常のポケモン選択
			tis->tps->plist->item=tis->bag_buf->ret_item;
			tis->tps->plist->bag_page=tis->bag_buf->ret_page;
			tis->tps->plist->client_no=tis->bag_buf->client_no;
			tis->tps->plist->cursor_flg = tis->decend_key;
			tis->tps->plist->fight_poke1 = tis->tps->sel_mons_no[tis->client_no];
			tis->tps->plist->fight_poke2 = tis->tps->sel_mons_no[BattleWorkPartnerClientNoGet(tis->bw,tis->client_no)];
			if(tis->client_type==CLIENT_TYPE_C){
				tis->tps->plist->skill_item_use[0]=tis->shutout_flag[BattleWorkPartnerClientNoGet(tis->bw,tis->client_no)];
				tis->tps->plist->skill_item_use[1]=tis->shutout_flag[tis->client_no];	// 技で使用不可
			}
			else{
				tis->tps->plist->skill_item_use[0]=tis->shutout_flag[tis->client_no];	// 技で使用不可
				tis->tps->plist->skill_item_use[1]=tis->shutout_flag[BattleWorkPartnerClientNoGet(tis->bw,tis->client_no)];
			}

			BattlePokeList_TaskAdd( tis->tps->plist );
			tis->seq_no++;
		}
		break;
	case SEQ_ITEM_SEL_POKE_LIST_MAIN:
		if(tis->tps->plist->end_flg){
			tis->decend_key = tis->tps->plist->cursor_flg;
			tis->tps->plist->end_flg=0;
			if(tis->tps->plist->sel_poke==BPL_SEL_EXIT){
				tis->seq_no=SEQ_ITEM_SEL_TASK_SET;
			}
			else{
				tis->seq_no=SEQ_ITEM_SEL_END_INIT;
			}
		}
		break;
	case SEQ_ITEM_SEL_END_INIT:
		FightScreenRecover(tis->bw);
		BINPUT_CursorDecendSet(BattleWorkGF_BGL_BIPGet(tis->bw), tis->decend_key);
		PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0x0c00,BATTLE_BAGLIST_FADE_SPEED,MSG_WINDOW_FADE,0,0x0000);
		PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,BATTLE_BAGLIST_FADE_SPEED,16,0,0x0000);
		tis->seq_no++;
		break;
	case SEQ_ITEM_SEL_END_WAIT:
		if(PaletteFadeCheck(pfd)==0){	//輝度変更フェード終了待ちして色々削除
			MSG_DsIconFlashReq(BattleWorkMsgIconGet(tis->bw),MSG_DSI_REQ_START);
	
			if(tis->bag_buf->ret_item){
				tis->seq_no=SEQ_ITEM_SEL_USE_MSG;
				switch(tis->bag_buf->ret_page){
				case BBAG_POKE_STRCV:	// 状態回復ポケット
					if((tis->bag_buf->ret_item==ITEM_GENKINOKAKERA)||
					   (tis->bag_buf->ret_item==ITEM_GENKINOKATAMARI)){
						tis->seq_no=SEQ_ITEM_SEL_END;
					}
					else if(((tis->tps->plist->sel_poke<2)&&
						    ((BattleWorkFightTypeGet(tis->bw)==FIGHT_TYPE_2vs2_TRAINER)||
							 (BattleWorkFightTypeGet(tis->bw)==FIGHT_TYPE_TAG_BATTLE)))||
						(tis->tps->plist->sel_poke<1)){
						if(tis->bag_buf->ret_item==ITEM_KAIHUKUNOKUSURI){
							if(BattleWorkConfigWazaEffectOnOffCheck(tis->bw)==TRUE){
								tis->next_seq_no=SEQ_ITEM_SEL_HPRCV_EFFECT_INIT1;
							}
							else{
								Snd_SePlayPan(BSE_KAIHUKU,WAZA_SE_PAN_L);
								tis->next_seq_no=SEQ_ITEM_SEL_HPRCV_EFFECT_INIT3;
							}
						}
						else{
							if(BattleWorkConfigWazaEffectOnOffCheck(tis->bw)==TRUE){
								tis->next_seq_no=SEQ_ITEM_SEL_CONDRCV_EFFECT_INIT1;
							}
							else{
								Snd_SePlayPan(BSE_KAIHUKU,WAZA_SE_PAN_L);
								tis->next_seq_no=SEQ_ITEM_SEL_CONDRCV_EFFECT_MSG;
							}
						}
					}
					else{
						tis->seq_no=SEQ_ITEM_SEL_END;
					}
					break;
				case BBAG_POKE_HPRCV:	// HP回復ポケット
					if((((tis->tps->plist->sel_poke<2)&&
					    ((BattleWorkFightTypeGet(tis->bw)==FIGHT_TYPE_2vs2_TRAINER)||
						 (BattleWorkFightTypeGet(tis->bw)==FIGHT_TYPE_TAG_BATTLE)))||
						 (tis->tps->plist->sel_poke<1))&&
						 (ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_HP_RCV,HEAPID_BATTLE))){
						if(BattleWorkConfigWazaEffectOnOffCheck(tis->bw)==TRUE){
							tis->next_seq_no=SEQ_ITEM_SEL_HPRCV_EFFECT_INIT1;
						}
						else{
							Snd_SePlayPan(BSE_KAIHUKU,WAZA_SE_PAN_L);
							tis->next_seq_no=SEQ_ITEM_SEL_HPRCV_EFFECT_INIT3;
						}
					}
					else{
						tis->seq_no=SEQ_ITEM_SEL_END;
					}
					break;
				case BBAG_POKE_BATTLE:	// 戦闘用ポケット
					if((tis->bag_buf->ret_item==ITEM_PIPPININGYOU)||
					   (tis->bag_buf->ret_item==ITEM_ENEKONOSIPPO)){
						tis->seq_no=SEQ_ITEM_SEL_END;
					}
					else{
						if(tis->bag_buf->ret_item==ITEM_EFEKUTOGAADO){
							if(BattleWorkConfigWazaEffectOnOffCheck(tis->bw)==TRUE){
								tis->next_seq_no=SEQ_ITEM_SEL_BATTLE_EFFECT_INIT2;
							}
							else{
								Snd_SePlayPan(BSE_KAIHUKU,WAZA_SE_PAN_L);
								tis->next_seq_no=SEQ_ITEM_SEL_BATTLE_EFFECT_MSG;
							}
						}
						else{
							if(BattleWorkConfigWazaEffectOnOffCheck(tis->bw)==TRUE){
								tis->next_seq_no=SEQ_ITEM_SEL_BATTLE_EFFECT_INIT1;
							}
							else{
								Snd_SePlayPan(BSE_KAIHUKU,WAZA_SE_PAN_L);
								tis->next_seq_no=SEQ_ITEM_SEL_BATTLE_EFFECT_MSG;
							}
						}
					}
					break;
				case BBAG_POKE_BALL:	// ボールポケット
					tis->seq_no=SEQ_ITEM_SEL_END;
					break;
				}
			}
			else{
				tis->seq_no=SEQ_ITEM_SEL_END;
			}
		}
		break;
	case SEQ_ITEM_SEL_END:
		{
			ITEM_SELECT_RETURN_PARAM	isrp;

			if(tis->bag_buf->ret_item==0){
				isrp.item_no=SELECT_CANCEL;
			}
			else{
				isrp.item_no=tis->bag_buf->ret_item;
				isrp.page=tis->bag_buf->ret_page;
				if((tis->bag_buf->ret_page==BBAG_POKE_STRCV)||
				   (tis->bag_buf->ret_page==BBAG_POKE_HPRCV)){
					isrp.sel_mons_no=SELECT_POKE_1+tis->tps->plist->list_row[tis->tps->plist->sel_poke];
				}
			}
			SCIO_ItemSelectReturnSet(tis->bw,tis->client_no,isrp);
			SCIO_ServerQueClear(tis->bw,tis->client_no,tis->command_code);
			sys_FreeMemoryEz(tis->tps->plist->pp);
			sys_FreeMemoryEz(tis->tps->plist);
			sys_FreeMemoryEz(tis->tps);
			sys_FreeMemoryEz(tis->bag_buf);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;

	//アイテム使用メッセージ
	case SEQ_ITEM_SEL_USE_MSG:
		{
			MSGDATA_MANAGER		*msg_m;
			MESSAGE_PARAM		mp;

			mp.msg_id=Dougu_UseMsg;
			mp.msg_tag=TAG_ITEM;
			mp.msg_para[0]=tis->bag_buf->ret_item;

			msg_m=BattleWorkFightMsgGet(tis->bw);
			tis->msg_index=BattleMSG_Print(tis->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tis->bw));
			tis->wait=MSG_WAIT;

			tis->seq_no++;
		}
		break;
	case SEQ_ITEM_SEL_USE_MSG_WAIT:
		if(GF_MSG_PrintEndCheck(tis->msg_index)==0){
			if(--tis->wait==0){
				tis->seq_no=tis->next_seq_no;
			}
		}
		break;
	
	//戦闘アイテム使用エフェクト
	case SEQ_ITEM_SEL_BATTLE_EFFECT_INIT1:
		{
			WAZA_EFFECT_PARAM	wep;

			SCIO_EffectDataSet(tis->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_ITEM_TR,tis->client_no,tis->client_no,NULL);
			CT_WesCall(tis->bw,BattleWorkClientParamGet(tis->bw,tis->client_no),BattleWorkWE_SYS_PTRGet(tis->bw),&wep);
		}
		tis->seq_no++;
		break;

	case SEQ_ITEM_SEL_HPRCV_EFFECT_INIT1:
	case SEQ_ITEM_SEL_CONDRCV_EFFECT_INIT1:
		{
			WAZA_EFFECT_PARAM	wep;
			int					client_no;

			client_no=tis->tps->plist->sel_poke*2;
			SCIO_EffectDataSet(tis->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_ITEM_TR,client_no,client_no,NULL);
			CT_WesCall(tis->bw,BattleWorkClientParamGet(tis->bw,client_no),BattleWorkWE_SYS_PTRGet(tis->bw),&wep);
		}
		tis->seq_no++;
		break;

	//ステータス上昇エフェクト
	case SEQ_ITEM_SEL_BATTLE_EFFECT_INIT2:
		{
			WAZA_EFFECT_PARAM	wep;

			if(tis->bag_buf->ret_item==ITEM_EFEKUTOGAADO){
				SCIO_EffectDataSet(tis->bw,NULL,&wep,EFFTYPE_WAZA,NULL,tis->client_no,tis->client_no,WAZANO_SIROIKIRI);
				CT_WesCall(tis->bw,BattleWorkClientParamGet(tis->bw,tis->client_no),BattleWorkWE_SYS_PTRGet(tis->bw),&wep);
			}
			else if(tis->bag_buf->ret_item==ITEM_KURITHIKATTAA){
				SCIO_EffectDataSet(tis->bw,NULL,&wep,EFFTYPE_WAZA,NULL,tis->client_no,tis->client_no,WAZANO_KIAIDAME);
				CT_WesCall(tis->bw,BattleWorkClientParamGet(tis->bw,tis->client_no),BattleWorkWE_SYS_PTRGet(tis->bw),&wep);
			}
			else{
				SCIO_EffectDataSet(tis->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_UP,tis->client_no,tis->client_no,NULL);
				CT_WesCall(tis->bw,BattleWorkClientParamGet(tis->bw,tis->client_no),BattleWorkWE_SYS_PTRGet(tis->bw),&wep);
			}
			tis->seq_no++;
		}
		break;
	case SEQ_ITEM_SEL_BATTLE_EFFECT_MSG:
		{
			MSGDATA_MANAGER		*msg_m;
			MESSAGE_PARAM		mp;

			mp.msg_id=Dougu_StatusUpMsg;
			mp.msg_tag=TAG_NICK_STAT;
			mp.msg_para[0]=tis->client_no|(tis->tps->sel_mons_no[tis->client_no]<<8);
			switch(tis->bag_buf->ret_item){
			case ITEM_PURASUPAWAA:
				mp.msg_para[1]=COND_POW;
				break;
			case ITEM_DHIFENDAA:
				mp.msg_para[1]=COND_DEF;
				break;
			case ITEM_SUPIIDAA:
				mp.msg_para[1]=COND_AGI;
				break;
			case ITEM_YOKUATAARU:
				mp.msg_para[1]=COND_HIT;
				break;
			case ITEM_SUPESYARUAPPU:
				mp.msg_para[1]=COND_SPEPOW;
				break;
			case ITEM_SUPESYARUGAADO:
				mp.msg_para[1]=COND_SPEDEF;
				break;
			case ITEM_EFEKUTOGAADO:
				mp.msg_id=Dougu_SiroikiriMsg;
				mp.msg_tag=TAG_NONE;
				break;
			case ITEM_KURITHIKATTAA:
				mp.msg_id=Dougu_KiaidameMsg;
				mp.msg_tag=TAG_NICK;
				break;
			}
			msg_m=BattleWorkFightMsgGet(tis->bw);
			tis->msg_index=BattleMSG_Print(tis->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tis->bw));
			tis->wait=MSG_WAIT;
		}
		tis->seq_no++;
		break;

	//HP回復エフェクト
	//状態異常回復エフェクト
	case SEQ_ITEM_SEL_HPRCV_EFFECT_INIT2:
	case SEQ_ITEM_SEL_CONDRCV_EFFECT_INIT2:
		{
			WAZA_EFFECT_PARAM	wep;
			int					client_no;

			client_no=tis->tps->plist->sel_poke*2;
			SCIO_EffectDataSet(tis->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_RECOVER,client_no,client_no,NULL);
			CT_WesCall(tis->bw,BattleWorkClientParamGet(tis->bw,client_no),BattleWorkWE_SYS_PTRGet(tis->bw),&wep);
		}
		tis->seq_no++;
		break;
	case SEQ_ITEM_SEL_HPRCV_EFFECT_INIT3:
		{
			GAUGE_WORK		*gauge;
			POKEMON_PARAM	*pp;
			int				client_no;
			int				sel_mons_no;

			client_no=tis->tps->plist->sel_poke*2;
			sel_mons_no=tis->tps->plist->list_row[tis->tps->plist->sel_poke];
	
			gauge = BattleWorkGaugeWorkGet(tis->bw,client_no);
			MI_CpuClear8(&gauge->param, sizeof(GAUGE_SUB_PARAM));
			gauge->type = Gauge_TypeGet(BattleWorkClientTypeGet(tis->bw,client_no),BattleWorkFightTypeGet(tis->bw));

			pp=BattleWorkPokemonParamGet(tis->bw,client_no,sel_mons_no);
			gauge->hp = PokeParaGet(pp,ID_PARA_hp,NULL)-tis->tps->plist->hp_rcv;
			gauge->hpmax = PokeParaGet(pp,ID_PARA_hpmax,NULL);
			gauge->damage = tis->tps->plist->hp_rcv;
			if(PokeParaGet(pp,ID_PARA_condition,NULL)==0){
				gauge->status = 0;
			}

			Gauge_InitCalcHP(gauge, gauge->damage);
		}
		tis->seq_no++;
		break;
	case SEQ_ITEM_SEL_HPRCV_EFFECT_WAIT3:
		{
			GAUGE_WORK		*gauge;
			int				client_no;

			client_no=tis->tps->plist->sel_poke*2;
			gauge = BattleWorkGaugeWorkGet(tis->bw,client_no);

			if(Gauge_CalcHP(gauge)==-1){
				Gauge_PartsDraw(gauge,NULL,GAUGE_DRAW_STATUS);
				tis->seq_no++;
			}
		}
		break;
	case SEQ_ITEM_SEL_HPRCV_EFFECT_MSG:
		{
			MSGDATA_MANAGER		*msg_m;
			MESSAGE_PARAM		mp;
			int					client_no;

			msg_m=BattleWorkFightMsgGet(tis->bw);
			client_no=tis->tps->plist->sel_poke*2;

			if(tis->tps->plist->hp_rcv){
				mp.msg_id=Dougu_HpkaihukuMsg;
				mp.msg_tag=TAG_NICK_NUM;
				mp.msg_para[0]=client_no|(tis->tps->sel_mons_no[client_no]<<8);
				mp.msg_para[1]=tis->tps->plist->hp_rcv;
			}
			else{
				mp.msg_id=Dougu_JoutaiKaihukuMsg;
				mp.msg_tag=TAG_NICK;
				mp.msg_para[0]=client_no|(tis->tps->sel_mons_no[client_no]<<8);
			}

			tis->msg_index=BattleMSG_Print(tis->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tis->bw));
			tis->wait=MSG_WAIT;

			tis->seq_no++;
		}
		break;

	case SEQ_ITEM_SEL_CONDRCV_EFFECT_MSG:
		{
			GAUGE_WORK		*gauge;
			int				client_no;
			MSGDATA_MANAGER	*msg_m;
			MESSAGE_PARAM	mp;
			int				item_prm;
			int				rcv_cnt=0;
			POKEMON_PARAM	*pp;
			int				sel_mons_no;

			client_no=tis->tps->plist->sel_poke*2;
			gauge = BattleWorkGaugeWorkGet(tis->bw,client_no);
			sel_mons_no=tis->tps->plist->list_row[tis->tps->plist->sel_poke];
			pp=BattleWorkPokemonParamGet(tis->bw,client_no,sel_mons_no);

			if(PokeParaGet(pp,ID_PARA_condition,NULL)==0){
				gauge->status = 0;
			}
			Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_STATUS);

			mp.msg_tag=TAG_NICK;
			mp.msg_para[0]=client_no|(tis->tps->sel_mons_no[client_no]<<8);

			// ねむり回復
			if(ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_SLEEP_RCV,HEAPID_BATTLE)){
				item_prm=NEMURI_RCV;
				rcv_cnt++;
			}
			// 毒回復
			if(ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_POISON_RCV,HEAPID_BATTLE)){
				item_prm=DOKU_RCV;
				rcv_cnt++;
			}
			// 火傷回復
			if(ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_BURN_RCV,HEAPID_BATTLE)){
				item_prm=YAKEDO_RCV;
				rcv_cnt++;
			}
			// 氷回復
			if(ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_ICE_RCV,HEAPID_BATTLE)){
				item_prm=KOORI_RCV;
				rcv_cnt++;
			}
			// 麻痺回復
			if(ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_PARALYZE_RCV,HEAPID_BATTLE)){
				item_prm=MAHI_RCV;
				rcv_cnt++;
			}
			// 混乱回復
			if(ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_PANIC_RCV,HEAPID_BATTLE)){
				item_prm=KONRAN_RCV;
				rcv_cnt++;
			}
			// メロメロ回復
			if(ItemParamGet(tis->bag_buf->ret_item,ITEM_PRM_MEROMERO_RCV,HEAPID_BATTLE)){
				item_prm=MEROMERO_RCV;
				rcv_cnt++;
			}
			if(rcv_cnt!=1){
				mp.msg_id=Dougu_NandemonaosiMsg;
			}
			else{
				switch(item_prm){
				case NEMURI_RCV:
					mp.msg_id=Dougu_NemurikaihukuMsg;
					break;
				case DOKU_RCV:
					mp.msg_id=Dougu_DokukaihukuMsg;
					break;
				case YAKEDO_RCV:
					mp.msg_id=Dougu_YakedokaihukuMsg;
					break;
				case KOORI_RCV:
					mp.msg_id=Dougu_KoorikaihukuMsg;
					break;
				case MAHI_RCV:
					mp.msg_id=Dougu_MahikaihukuMsg;
					break;
				case KONRAN_RCV:
					mp.msg_id=Dougu_KonrankaihukuMsg;
					break;
				case MEROMERO_RCV:
					mp.msg_id=Dougu_MeromerokaihukuMsg;
					break;
				}
			}
			msg_m=BattleWorkFightMsgGet(tis->bw);
			tis->msg_index=BattleMSG_Print(tis->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tis->bw));
			tis->wait=MSG_WAIT;
		}
		tis->seq_no++;
		break;

	//エフェクト終了待ち
	case SEQ_ITEM_SEL_BATTLE_EFFECT_WAIT1:
	case SEQ_ITEM_SEL_BATTLE_EFFECT_WAIT2:
	case SEQ_ITEM_SEL_HPRCV_EFFECT_WAIT1:
	case SEQ_ITEM_SEL_HPRCV_EFFECT_WAIT2:
	case SEQ_ITEM_SEL_CONDRCV_EFFECT_WAIT1:
	case SEQ_ITEM_SEL_CONDRCV_EFFECT_WAIT2:
		WES_Executed(BattleWorkWE_SYS_PTRGet(tis->bw));
		if (IsWES_Executed(BattleWorkWE_SYS_PTRGet(tis->bw)) == FALSE){		///< Effect Commond End Check
			WES_Reset(BattleWorkWE_SYS_PTRGet(tis->bw));					///< Sysmte Reset
			tis->seq_no++;
		}
		break;

	//メッセージ終了待ち
	case SEQ_ITEM_SEL_BATTLE_EFFECT_MSG_WAIT:
	case SEQ_ITEM_SEL_HPRCV_EFFECT_MSG_WAIT:
	case SEQ_ITEM_SEL_CONDRCV_EFFECT_MSG_WAIT:
		if(GF_MSG_PrintEndCheck(tis->msg_index)==0){
			if(--tis->wait==0){
				tis->seq_no=SEQ_ITEM_SEL_END;
			}
		}
		break;

	}
}

//============================================================================================
/**
 *	道具選択TCB（AI用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_ItemSelectAI(TCB_PTR tcb,void *work)
{
	TCB_ITEM_SELECT				*tis=(TCB_ITEM_SELECT *)work;
	ITEM_SELECT_RETURN_PARAM	isrp;

	//選択したアイテムは、AI用のワークに保持されているので、ここでは、ダミーの値を入れておく
	isrp.item_no=1;
	SCIO_ItemSelectReturnSet(tis->bw,tis->client_no,isrp);
	SCIO_ServerQueClear(tis->bw,tis->client_no,tis->command_code);
	sys_FreeMemoryEz(tis->tps->plist->pp);
	sys_FreeMemoryEz(tis->tps->plist);
	sys_FreeMemoryEz(tis->tps);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	道具選択TCB（通信用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_ItemSelectSIO(TCB_PTR tcb,void *work)
{
	TCB_ITEM_SELECT	*tis=(TCB_ITEM_SELECT *)work;

	SCIO_ServerQueClear(tis->bw,tis->client_no,tis->command_code);
	sys_FreeMemoryEz(tis->tps->plist->pp);
	sys_FreeMemoryEz(tis->tps->plist);
	sys_FreeMemoryEz(tis->tps);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	ポケモン選択TCB（プレイヤー用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonSelect(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_SELECT	*tps=(TCB_POKEMON_SELECT *)work;
	PALETTE_FADE_PTR	pfd;

	pfd=BattleWorkPfdGet(tps->bw);

	switch(tps->seq_no){
	case 0:		//リスト画面へのフェード
		//メッセージウインドをクリア
		{
			GF_BGL_BMPWIN	*win=BattleWorkGF_BGL_BMPWINGet(tps->bw,TALK_WIN_NO);

			GF_BGL_BmpWinDataFill(win,0xff);
			GF_BGL_BmpWinCgxOn(win);
		}

		//BIPが解放されるまえに必要な情報だけ取得
		tps->decend_key = BINPUT_CursorDecendGet(BattleWorkGF_BGL_BIPGet(tps->bw));

		MSG_DsIconFlashReq(BattleWorkMsgIconGet(tps->bw),MSG_DSI_REQ_STOP);
		PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0x0c00,BATTLE_BAGLIST_FADE_SPEED,0,MSG_WINDOW_FADE,0x0000);
		PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,BATTLE_BAGLIST_FADE_SPEED,0,16,0x0000);
		tps->seq_no++;
		break;
	case 1:
		if(PaletteFadeCheck(pfd)==0){	//輝度変更フェード終了待ちして色々削除
			{
				int				i;
				int				cnt=0;
				int				client_no;
				int				cli1,cli2;
				POKEPARTY		*poke_party;
				POKEMON_PARAM	*pp,*pp2;

				FightScreenTransition(tps->bw);

				tps->plist=sys_AllocMemory(HEAPID_BATTLE,sizeof(BPLIST_DATA));
				tps->plist->pp=PokeParty_AllocPartyWork(HEAPID_BATTLE);

				if(((BattleWorkFightTypeGet(tps->bw)&(FIGHT_TYPE_SIO|FIGHT_TYPE_MULTI))==(FIGHT_TYPE_SIO|FIGHT_TYPE_MULTI))||
					(BattleWorkFightTypeGet(tps->bw)==FIGHT_TYPE_BATTLE_TOWER_AI_MULTI)){
					if(BattleWorkClientTypeGet(tps->bw,tps->client_no)==CLIENT_TYPE_A){
						cli1=tps->client_no;
						cli2=BattleWorkPartnerClientNoGet(tps->bw,tps->client_no);
					}
					else{
						cli1=BattleWorkPartnerClientNoGet(tps->bw,tps->client_no);
						cli2=tps->client_no;
					}

					pp=PokemonParam_AllocWork(HEAPID_BATTLE);
					for(i=0;i<POKEMON_TEMOTI_MAX;i++){
						PokeParty_Add(tps->plist->pp,pp);
					}
					sys_FreeMemoryEz(pp);
			
					for(i=0;i<BattleWorkPokeCountGet(tps->bw,cli1);i++){
						pp=BattleWorkPokemonParamGet(tps->bw,cli1,tps->list_row[cli1][i]);
						pp2=PokeParty_GetMemberPointer(tps->plist->pp,i*2);
						PokeCopyPPtoPP(pp,pp2);
						tps->plist->list_row[i*2]=tps->list_row[cli1][i];
					}

					for(i=0;i<BattleWorkPokeCountGet(tps->bw,cli2);i++){
						pp=BattleWorkPokemonParamGet(tps->bw,cli2,tps->list_row[cli2][i]);
						pp2=PokeParty_GetMemberPointer(tps->plist->pp,i*2+1);
						PokeCopyPPtoPP(pp,pp2);
						tps->plist->list_row[i*2+1]=tps->list_row[cli2][i];
					}
					if(BattleWorkClientTypeGet(tps->bw,tps->client_no)==CLIENT_TYPE_C){
						tps->plist->sel_poke = 1;
					}
					else{
						tps->plist->sel_poke = 0;
					}
				}
				else{
					if((BattleWorkFightTypeGet(tps->bw)&FIGHT_TYPE_2vs2)&&
					  ((BattleWorkFightTypeGet(tps->bw)&FIGHT_TYPE_MULTI)==0)){
						client_no=tps->client_no&1;
					}
					else{
						client_no=tps->client_no;
					}
					if(BattleWorkClientTypeGet(tps->bw,tps->client_no)==CLIENT_TYPE_C){
						tps->plist->sel_poke = 1;
					}
					else{
						tps->plist->sel_poke = 0;
					}

					poke_party=BattleWorkPokePartyGet(tps->bw,tps->client_no);
			
					for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
						pp=BattleWorkPokemonParamGet(tps->bw,client_no,tps->list_row[client_no][i]);
						PokeParty_Add(tps->plist->pp,pp);
						tps->plist->list_row[i]=tps->list_row[client_no][i];
					}
				}

				tps->plist->bw = tps->bw;
				tps->plist->heap = HEAPID_BATTLE;
				tps->plist->end_flg = 0;
				tps->plist->chg_waza=tps->chg_waza;
				tps->plist->double_sel=tps->double_sel;
				tps->plist->mode=tps->list_mode;
				tps->plist->item=tps->item;
				tps->plist->client_no=tps->client_no;
				tps->plist->cursor_flg=tps->decend_key;
				if((tps->no_reshuffle_client&No2Bit(tps->client_no))==0){
					tps->plist->fight_poke1 = tps->sel_mons_no[tps->client_no];
				}
				else{
					tps->plist->fight_poke1 = NO_SEL_MONS;
				}
				if(BattleWorkFightTypeGet(tps->bw)&FIGHT_TYPE_MULTI){
					tps->plist->fight_poke2 = NO_SEL_MONS;
				}
				else if((tps->no_reshuffle_client&No2Bit(BattleWorkPartnerClientNoGet(tps->bw,tps->client_no)))==0){
					tps->plist->fight_poke2 = tps->sel_mons_no[BattleWorkPartnerClientNoGet(tps->bw,tps->client_no)];
				}
				else{
					tps->plist->fight_poke2 = NO_SEL_MONS;
				}
				
				BattlePokeList_TaskAdd( tps->plist );
				tps->seq_no++;
			}
		}
		break;
	case 2:
		if(tps->plist->end_flg){
			FightScreenRecover(tps->bw);
			BINPUT_CursorDecendSet(BattleWorkGF_BGL_BIPGet(tps->bw), tps->plist->cursor_flg);
			PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0x0c00,BATTLE_BAGLIST_FADE_SPEED,MSG_WINDOW_FADE,0,0x0000);
			PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,BATTLE_BAGLIST_FADE_SPEED,16,0,0x0000);
			tps->seq_no++;
		}
		break;
	case 3:
		if(PaletteFadeCheck(pfd)==0){	//輝度変更フェード終了待ちして色々削除
			MSG_DsIconFlashReq(BattleWorkMsgIconGet(tps->bw),MSG_DSI_REQ_START);
			if(tps->plist->sel_poke==BPL_SEL_EXIT){
				SCIO_PokemonSelectReturnSet(tps->bw,tps->client_no,SELECT_CANCEL);
			}
			else{
				SCIO_PokemonSelectReturnSet(tps->bw,tps->client_no,SELECT_POKE_1+tps->plist->list_row[tps->plist->sel_poke]);
			}
			SCIO_ServerQueClear(tps->bw,tps->client_no,tps->command_code);
			sys_FreeMemoryEz(tps->plist->pp);
			sys_FreeMemoryEz(tps->plist);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
}

//============================================================================================
/**
 *	ポケモン選択TCB（AI用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonSelectAI(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_SELECT	*tps=(TCB_POKEMON_SELECT *)work;
	int					pos;
	POKEPARTY			*poke_party;
	POKEMON_PARAM		*pp;
	int					client_no,client_pair_no;
	u32					fight_type;

	fight_type=BattleWorkFightTypeGet(tps->bw);

	client_no=tps->client_no;
	if((fight_type&FIGHT_TYPE_TAG)||
	   (fight_type&FIGHT_TYPE_MULTI)){
		client_pair_no=client_no;
	}
	else{
		client_pair_no=BattleWorkPartnerClientNoGet(tps->bw,client_no);
	}

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(tps->bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		//通信接続では、子機側にAIがのっていないので、先頭からサーチしてHPのあるポケモンを繰り出す
//		if(CommStateIsWifiConnect()){
		if(fight_type&FIGHT_TYPE_SIO){
			poke_party=BattleWorkPokePartyGet(tps->bw,tps->client_no);
			for(pos=0;pos<PokeParty_GetPokeCount(poke_party);pos++){
				pp=BattleWorkPokemonParamGet(tps->bw,tps->client_no,pos);
				if((PokeParaGet(pp,ID_PARA_hp,NULL))&&
				   (tps->sel_mons_no[client_no]!=pos)&&
				   (tps->sel_mons_no[client_pair_no]!=pos)){
					break;
				}
			}
			SCIO_PokemonSelectReturnSet(tps->bw,tps->client_no,SELECT_POKE_1+pos);
			SCIO_ServerQueClear(tps->bw,tps->client_no,tps->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
			return;
		}
	}
#endif PM_DEBUG

	pos=ClientAIReshuffleSelMonsNoGet(tps->bw,client_no);
	if(pos==6){
		pos=ClientAIPokeSelectAI(tps->bw,client_no);
		//AIが決めれなければ先頭からサーチしてHPのあるポケモンを繰り出す
		if(pos==6){
			poke_party=BattleWorkPokePartyGet(tps->bw,tps->client_no);
			for(pos=0;pos<PokeParty_GetPokeCount(poke_party);pos++){
				pp=BattleWorkPokemonParamGet(tps->bw,tps->client_no,pos);
				if((PokeParaGet(pp,ID_PARA_hp,NULL))&&
				   (tps->sel_mons_no[client_no]!=pos)&&
				   (tps->sel_mons_no[client_pair_no]!=pos)){
					break;
				}
			}
		}
	}
#ifdef PM_DEBUG
	if(DebugBattlePokemonReshuffle(tps->bw,tps->client_no,&pos)==FALSE){
		return;
	}
#endif
	SCIO_PokemonSelectReturnSet(tps->bw,tps->client_no,SELECT_POKE_1+pos);
	SCIO_ServerQueClear(tps->bw,tps->client_no,tps->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	ポケモン選択TCB（通信用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonSelectSIO(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_SELECT	*tps=(TCB_POKEMON_SELECT *)work;

	SCIO_ServerQueClear(tps->bw,tps->client_no,tps->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	Yes/No選択TCB（プレイヤー用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_YesNoSelect(TCB_PTR tcb,void *work)
{
	TCB_YES_NO_SELECT	*tyns = work;
	GF_BGL_INI	*bgl=BattleWorkGF_BGL_INIGet(tyns->bw);
	BI_PARAM_PTR bip = BattleWorkGF_BGL_BIPGet(tyns->bw);
	int partner_client;
	GAUGE_WORK *partner_gauge;
	CLIENT_PARAM *cp;
	
	enum{	//シーケンス番号
		CSSEQ_ESCAPE_SELECT_INIT,
		CSSEQ_ESCAPE_SELECT_WAIT,
		CSSEQ_ESCAPE_SELECT,
		CSSEQ_ESCAPE_SELECT_EFFWAIT,
		
		CSSEQ_FINISH,
	};

	cp=BattleWorkClientParamGet(tyns->bw,tyns->client_no);
	partner_client = BattleWorkPartnerClientNoGet(tyns->bw, tyns->client_no);
	if(partner_client != tyns->client_no){
		partner_gauge = BattleWorkGaugeWorkGet(tyns->bw, partner_client);
	}
	else{
		partner_gauge = NULL;
	}
	
	switch(tyns->seq_no){
	case CSSEQ_ESCAPE_SELECT_INIT:
		if(BINPUT_EffectEndCheck(bip) == FALSE){
			break;
		}

		if(tyns->msg_id){
			{
				GF_BGL_BMPWIN		*win;
				MSGDATA_MANAGER		*msg_m;
				MESSAGE_PARAM		mp;
	
				msg_m=BattleWorkFightMsgGet(tyns->bw);
				if(tyns->flag==YNTYPE_NICK_NAME){
					mp.msg_tag=TAG_NICK|TAG_NO_DIR;
					mp.msg_para[0]=tyns->nickname;
				}
				else{
					mp.msg_tag=TAG_NONE;
				}
				mp.msg_id=tyns->msg_id;
				tyns->msg_index=BattleMSG_Print(tyns->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tyns->bw));
			}
		}
		tyns->seq_no = CSSEQ_ESCAPE_SELECT_WAIT;
		break;
	case CSSEQ_ESCAPE_SELECT_WAIT:
		if((GF_MSG_PrintEndCheck(tyns->msg_index)==0)||(tyns->msg_id==NULL)){
			BINPUT_SCENE_YESNO bsy;
			
			BINPUT_StockBallOFF(bip);
			
			bsy.waza_no = tyns->waza_no;
			switch(tyns->flag){
			case YNTYPE_YES_NO:
			case YNTYPE_NICK_NAME:
				BINPUT_CreateBG(bip, BINPUT_TYPE_YESNO, FALSE, &bsy);
				break;
			case YNTYPE_WASURE:
				BINPUT_CreateBG(bip, BINPUT_TYPE_WASURERU, FALSE, &bsy);
				break;
			case YNTYPE_AKIRAME:
				BINPUT_CreateBG(bip, BINPUT_TYPE_AKIRAMERU, FALSE, &bsy);
				break;
			case YNTYPE_NEXT_POKEMON:
				BINPUT_CreateBG(bip, BINPUT_TYPE_NEXT_POKEMON, FALSE, &bsy);
				break;
			case YNTYPE_CHANGE_POKEMON:
				BINPUT_CreateBG(bip, BINPUT_TYPE_CHANGE_POKEMON, FALSE, &bsy);
				break;
			default:
				GF_ASSERT(0);
				break;
			}
			tyns->seq_no = CSSEQ_ESCAPE_SELECT;
		}
		break;
	case CSSEQ_ESCAPE_SELECT:
		tyns->tp_ret = BINPUT_TouchCheck(bip);
		if(tyns->tp_ret != RECT_HIT_NONE){
			Snd_SePlay(BSE_TP_DECIDE);
			tyns->seq_no = CSSEQ_ESCAPE_SELECT_EFFWAIT;
		}
		break;
	case CSSEQ_ESCAPE_SELECT_EFFWAIT:
		if(BINPUT_EffectEndCheck(bip) == TRUE){
			Gauge_AnimeStop(tyns->gauge);
			Poke_SinCurveStop(cp);
			Gauge_ColorNormalSet(partner_gauge);
			BINPUT_StockBallOFF(bip);
			BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
			if(tyns->tp_ret == TRUE){
				BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);
			}
			//tyns->tp_ret = SELECT_ESCAPE_COMMAND;
			tyns->seq_no = CSSEQ_FINISH;
		}
		break;

	case CSSEQ_FINISH:
		if(BINPUT_BackFadeExeCheck(bip) == TRUE){
			SCIO_CommandSelectReturnSet(tyns->bw,tyns->client_no,tyns->tp_ret);
			SCIO_ServerQueClear(tyns->bw,tyns->client_no,tyns->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
}

//============================================================================================
/**
 *	Yes/No選択TCB（AI用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_YesNoSelectAI(TCB_PTR tcb,void *work)
{
	TCB_YES_NO_SELECT	*tyns=(TCB_YES_NO_SELECT *)work;

	SCIO_ServerQueClear(tyns->bw,tyns->client_no,tyns->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	Yes/No選択TCB（通信用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_YesNoSelectSIO(TCB_PTR tcb,void *work)
{
	TCB_YES_NO_SELECT	*tyns=(TCB_YES_NO_SELECT *)work;

	SCIO_ServerQueClear(tyns->bw,tyns->client_no,tyns->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
}

//============================================================================================
/**
 *	技エフェクトTCB
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
enum{
	SEQ_WE_MIGAWARI_CHECK=0,
	SEQ_WE_MIGAWARI2POKE_WAIT,
	SEQ_WE_POKE_IN_SET,
	SEQ_WE_POKE_IN_WAIT,
	SEQ_WE_WAZA_EFFECT,
	SEQ_WE_WAZA_EFFECT_WAIT,
	SEQ_WE_POKE2MIGAWARI_SET,
	SEQ_WE_POKE2MIGAWARI_WAIT,
	SEQ_WE_MIGAWARI_IN_SET,
	SEQ_WE_MIGAWARI_IN_WAIT,
	SEQ_WE_WAZA_EFFECT_END
};
static	void	TCB_WazaEffect(TCB_PTR tcb,void *work)
{
	TCB_WAZA_EFFECT	*twe=(TCB_WAZA_EFFECT *)work;

	switch(twe->seq_no){
	case SEQ_WE_MIGAWARI_CHECK:
		if((twe->wep.migawari_flag)&&
		   (twe->wep.flag==EFFTYPE_WAZA)&&
		   (SoftSpriteParaGet(twe->ss,SS_PARA_VANISH)==0)){
			{
				WAZA_EFFECT_PARAM	wep;

				SCIO_EffectDataSet(twe->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_OUT,twe->client_no,twe->client_no,NULL);
				CT_WesCall(twe->bw,twe->cp,twe->wsp,&wep);
			}
			twe->seq_no=SEQ_WE_MIGAWARI2POKE_WAIT;
		}
		else{
			twe->seq_no=SEQ_WE_WAZA_EFFECT;
		}
		break;

	case SEQ_WE_POKE_IN_SET:
		{
			WAZA_POKE_CHANGE_PARAM	wpcp;
			WAZA_EFFECT_PARAM		wep;

			CT_WazaPokeChangeParamMake(twe->bw,&twe->wep,&wpcp,twe->client_no);
			HenshinChrPop(&wpcp,HEAPID_BATTLE);

			SCIO_EffectDataSet(twe->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_IN,twe->client_no,twe->client_no,NULL);
			CT_WesCall(twe->bw,twe->cp,twe->wsp,&wep);
			twe->cp->migawari_flag=0;
		}
		twe->seq_no++;
		break;

	case SEQ_WE_WAZA_EFFECT:
		BattleWorkPinchSEFlagSet(twe->bw,2);
		if(twe->we_on_off_flag){
			BattleWorkGaugeOff(twe->bw);
		}
		if(twe->we_shadow_flag){
			SoftSpriteSSSystemFlagSet(BattleWorkSoftSpriteManagerGet(twe->bw),SS_SYSTEM_FLAG_SHADOW_OFF);
		}
		CT_WesCall(twe->bw,twe->cp,twe->wsp,&twe->wep);
		twe->seq_no++;
		break;

	case SEQ_WE_POKE2MIGAWARI_SET:
		BattleWorkPinchSEFlagSet(twe->bw,0);
		if(twe->we_on_off_flag){
			BattleWorkGaugeOn(twe->bw);
		}
		if(twe->we_shadow_flag){
			SoftSpriteSSSystemFlagReset(BattleWorkSoftSpriteManagerGet(twe->bw),SS_SYSTEM_FLAG_SHADOW_OFF);
		}
		if((twe->wep.migawari_flag)&&
		   (twe->wep.flag==EFFTYPE_WAZA)&&
		   (SoftSpriteParaGet(twe->ss,SS_PARA_VANISH)==0)){
			{
				WAZA_EFFECT_PARAM	wep;

				SCIO_EffectDataSet(twe->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_OUT,twe->client_no,twe->client_no,NULL);
				CT_WesCall(twe->bw,twe->cp,twe->wsp,&wep);
			}
			twe->seq_no=SEQ_WE_POKE2MIGAWARI_WAIT;
		}
		else{
			twe->seq_no=SEQ_WE_WAZA_EFFECT_END;
		}
		break;

	case SEQ_WE_MIGAWARI_IN_SET:
		{
			WAZA_POKE_CHANGE_PARAM	wpcp;
			WAZA_EFFECT_PARAM		wep;

			CT_WazaPokeChangeParamMake(twe->bw,&twe->wep,&wpcp,twe->client_no);
			MigawariChrSet(&wpcp,HEAPID_BATTLE);

			SCIO_EffectDataSet(twe->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_IN,twe->client_no,twe->client_no,NULL);
			CT_WesCall(twe->bw,twe->cp,twe->wsp,&wep);
			twe->cp->migawari_flag=1;
		}
		twe->seq_no++;
		break;

	case SEQ_WE_WAZA_EFFECT_END:
		SCIO_ServerQueClear(twe->bw,twe->client_no,twe->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;

	//もろもろのエフェクト終了待ち
	case SEQ_WE_MIGAWARI2POKE_WAIT:
	case SEQ_WE_POKE_IN_WAIT:
	case SEQ_WE_WAZA_EFFECT_WAIT:
	case SEQ_WE_POKE2MIGAWARI_WAIT:
	case SEQ_WE_MIGAWARI_IN_WAIT:
		WES_Executed(twe->wsp);
		if (IsWES_Executed(twe->wsp) == FALSE){		///< Effect Commond End Check
			WES_Reset(twe->wsp);						///< Sysmte Reset
			twe->seq_no++;
		}
		break;
	}
}

//============================================================================================
/**
 *	ポケモンダメージブリンク
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonBlink(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_BLINK	*tpb=(TCB_POKEMON_BLINK *)work;
	int					vanish;

	if(tpb->seq_no<6){
		if(tpb->wait==0){
			tpb->wait=BLINK_WAIT;
			tpb->seq_no++;
			vanish=SoftSpriteParaGet(tpb->ss,SS_PARA_VANISH);
			vanish^=1;
			SoftSpriteParaSet(tpb->ss,SS_PARA_VANISH,vanish);
		}
		else{
			tpb->wait--;
		}
	}
	else{
		vanish=0;
		SoftSpriteParaSet(tpb->ss,SS_PARA_VANISH,vanish);
		SCIO_ServerQueClear(tpb->bw,tpb->client_no,CL_POKEMON_BLINK);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
	}
}

//============================================================================================
/**
 *	HPゲージ計算
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_HPGaugeCalc(TCB_PTR tcb,void *work)
{
	GAUGE_WORK *gauge = work;
	int calc_hp;

	switch(gauge->param.seq_no){
	case 0:
//		Gauge_PartsDraw(gauge, GAUGE_DRAW_HPBAR | GAUGE_DRAW_HPNUM);
		Gauge_InitCalcHP(gauge, gauge->damage);
		gauge->param.seq_no++;
		//break;
	case 1:
		calc_hp = Gauge_CalcHP(gauge);
		if(calc_hp == -1){
			gauge->param.seq_no++;
		}
		break;
	default:
		SCIO_ServerQueClear(gauge->bw, gauge->client_no, gauge->command_code);
		gauge->tcb = NULL;
		TCB_Delete(tcb);
		return;
	}
}

//============================================================================================
/**
 *	EXPゲージ計算
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
///最低でもこのフレーム分はEXP上昇SEを鳴らしてから止める
#define HP_GAUGE_SE_TIME		(8)
static	void	TCB_EXPGaugeCalc(TCB_PTR tcb,void *work)
{
	GAUGE_WORK *gauge = work;
	int calc_exp;
	
	switch(gauge->param.seq_no){
	case 0:
		gauge->se_wait = 0;
		Snd_SePlay(BSE_EXP_GET);
		Gauge_InitCalcEXP(gauge, gauge->add_exp);
		gauge->param.seq_no++;
		//break;
	case 1:
		if(gauge->se_wait < HP_GAUGE_SE_TIME){
			gauge->se_wait++;
		}
		
		calc_exp = Gauge_CalcEXP(gauge);
		if(calc_exp == -1){
			if(gauge->se_wait >= HP_GAUGE_SE_TIME){
				Snd_SeStopBySeqNo(BSE_EXP_GET, 0);
				gauge->param.seq_no = 100;
			}
			else{
				gauge->param.seq_no++;
			}
		}
		break;
	case 2:
		gauge->se_wait++;
		if(gauge->se_wait >= HP_GAUGE_SE_TIME){
			Snd_SeStopBySeqNo(BSE_EXP_GET, 0);
			gauge->param.seq_no = 100;
		}
		break;
	default:
		SCIO_ServerQueClear(gauge->bw, gauge->client_no, gauge->command_code);
		gauge->tcb = NULL;
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	気絶エフェクト
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_KizetsuEffect(TCB_PTR tcb,void *work)
{
	TCB_KIZETSU_EFFECT	*tke=(TCB_KIZETSU_EFFECT *)work;
	WE_SYS_PTR			wsp=BattleWorkWE_SYS_PTRGet(tke->bw);
	int	pos_y;
	int	height;

	switch(tke->seq_no){
	case 0:
		if(tke->migawari_flag){
			{
				WAZA_EFFECT_PARAM	wep;

				SCIO_EffectDataSet(tke->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_OUT,tke->client_no,tke->client_no,NULL);
				CT_WesCall(tke->bw,tke->cp,wsp,&wep);
			}
			tke->seq_no++;
		}
		else{
			tke->seq_no=4;
		}
		break;

	case 2:
		{
			WAZA_POKE_CHANGE_PARAM	wpcp;
			WAZA_EFFECT_PARAM		wep;

			CT_WazaPokeChangeParamMake(tke->bw,&tke->wep,&wpcp,tke->client_no);
			HenshinChrPop(&wpcp,HEAPID_BATTLE);

			SCIO_EffectDataSet(tke->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_IN,tke->client_no,tke->client_no,NULL);
			CT_WesCall(tke->bw,tke->cp,wsp,&wep);
			tke->cp->migawari_flag=0;
		}
		tke->seq_no++;
		break;
	//もろもろのエフェクト終了待ち
	case 1:
	case 3:
		WES_Executed(wsp);
		if (IsWES_Executed(wsp) == FALSE){		///< Effect Commond End Check
			WES_Reset(wsp);						///< Sysmte Reset
			tke->seq_no++;
		}
		break;
	case 4:
		{
			int	pan;

			if(tke->dir==PARA_FRONT){
				pan=POKE_VOICE_PAN_FRONT;
			}
			else{
				pan=POKE_VOICE_PAN_BACK;
			}
			PokeVoicePlaySet(BattleWorkPerapVoiceGet(tke->bw,tke->client_no),
							 PV_POKEDOWN,tke->monsno,pan,POKE_KIZETSU_VOL,tke->henshin_flag,HEAPID_BATTLE);
			tke->seq_no++;
		}
	case 5:
		if(Snd_PMVoicePlayCheck()==FALSE){
			tke->seq_no++;
		}
		break;
	case 6:
		if(tke->dir==PARA_FRONT){
			Snd_SePlayPan(BSE_POKE_DEAD,WAZA_SE_PAN_R);
		}
		else{
			Snd_SePlayPan(BSE_POKE_DEAD,WAZA_SE_PAN_L);
		}
		if(SoftSpriteParaGet(tke->ss,SS_PARA_SHADOW_HEIGHT)>0){
			tke->seq_no=7;
		}
		else{
			tke->seq_no=8;
		}
		break;
	case 7:
		height=SoftSpriteParaGet(tke->ss,SS_PARA_SHADOW_HEIGHT);
		height-=8;
		if(height<0){
			height=0;
		}
		SoftSpriteParaSet(tke->ss,SS_PARA_SHADOW_HEIGHT,height);
		if(height){
			break;
		}
		tke->seq_no++;
	case 8:
		height=PokeHeightGet(tke->monsno,tke->sex,tke->dir,tke->form_no,tke->personal_rnd);
		height=SOFT_SPRITE_SIZE_Y-height;
		SoftSpriteVisibleSet(tke->ss,0,0,SOFT_SPRITE_SIZE_X,height);
		tke->seq_no++;
		break;
	case 9:
		pos_y=SoftSpriteParaGet(tke->ss,SS_PARA_POS_Y);
		pos_y+=8;
		SoftSpriteParaSet(tke->ss,SS_PARA_POS_Y,pos_y);
		height=SoftSpriteParaGet(tke->ss,SS_PARA_OFS_SIZE_Y);
		height-=8;
		if(height<0){
			height=0;
		}
		SoftSpriteParaSet(tke->ss,SS_PARA_OFS_SIZE_Y,height);
		if(height==0){
			SoftSpriteDel(tke->ss);
			tke->seq_no++;
		}
		break;
	case 10:
		SCIO_ServerQueClear(tke->bw,tke->client_no,tke->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	画面フェードエフェクト
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_FadeOut(TCB_PTR tcb,void *work)
{
	TCB_FADE_OUT	*tfo=(TCB_FADE_OUT *)work;
	PALETTE_FADE_PTR	pfd;
	SOFT_SPRITE_MANAGER	*ssm_p;

	pfd=BattleWorkPfdGet(tfo->bw);
	ssm_p=BattleWorkSoftSpriteManagerGet(tfo->bw);

	switch(tfo->seq_no){
	case 0:
		MSG_DsIconFlashReq(BattleWorkMsgIconGet(tfo->bw),MSG_DSI_REQ_STOP);
		PaletteFadeReq(pfd,PF_BIT_NORMAL_ALL,0xffff,1,0,16,0x0000);
		SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
		Snd_BgmFadeOut(0,16);
		tfo->seq_no++;
	case 1:
		if(PaletteFadeCheck(pfd)==0){
			tfo->seq_no++;
		}
		break;
	case 2:
		SCIO_ServerQueClear(tfo->bw,tfo->client_no,tfo->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	ポケモンバニッシュ制御タスク
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_PokemonVanishOnOff(TCB_PTR tcb,void *work)
{
	TCB_POKEMON_VANISH_ON_OFF	*tpvoo;
	WE_SYS_PTR					wsp;

	tpvoo=(TCB_POKEMON_VANISH_ON_OFF *)work;
	wsp=BattleWorkWE_SYS_PTRGet(tpvoo->bw);

	switch(tpvoo->seq_no){
	case 0:
		if(tpvoo->cp->poke_ss){
			SoftSpriteParaSet(tpvoo->cp->poke_ss,SS_PARA_VANISH,tpvoo->sw);
			if(tpvoo->sw==SW_VANISH_ON){
				tpvoo->seq_no=0xff;
			}
			else{
				tpvoo->seq_no++;
			}
		}
		else{
			tpvoo->seq_no=0xff;
		}
		break;
	case 1:
		if((tpvoo->migawari_flag)&&(tpvoo->cp->migawari_flag==0)){
			{
				WAZA_EFFECT_PARAM		wep;
	
				SCIO_EffectDataSet(tpvoo->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_OUT,
								   tpvoo->client_no,tpvoo->client_no,NULL);
				CT_WesCall(tpvoo->bw,tpvoo->cp,wsp,&wep);
			}
			tpvoo->seq_no++;
		}
		else{
			tpvoo->seq_no=0xff;
		}
		break;
	case 3:
		{
			WAZA_POKE_CHANGE_PARAM	wpcp;
			WAZA_EFFECT_PARAM		wep;

			CT_WazaPokeChangeParamMake(tpvoo->bw,&tpvoo->wep,&wpcp,tpvoo->client_no);
			MigawariChrSet(&wpcp,HEAPID_BATTLE);

			SCIO_EffectDataSet(tpvoo->bw,NULL,&wep,EFFTYPE_STATUS,STATUS_EFF_MIGAWARI_IN,
							   tpvoo->client_no,tpvoo->client_no,NULL);
			CT_WesCall(tpvoo->bw,tpvoo->cp,wsp,&wep);
			tpvoo->cp->migawari_flag=1;
		}
		tpvoo->seq_no++;
		break;
	case 2:
	case 4:
		WES_Executed(wsp);
		if (IsWES_Executed(wsp) == FALSE){		///< Effect Commond End Check
			WES_Reset(wsp);					///< Sysmte Reset
			tpvoo->seq_no++;
		}
		break;
	default:
		SCIO_ServerQueClear(tpvoo->bw,tpvoo->client_no,tpvoo->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	レベルアップエフェクト
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_LevelUpEffect(TCB_PTR tcb,void *work)
{
	TCB_LEVEL_UP_EFFECT	*tlue=(TCB_LEVEL_UP_EFFECT *)work;

	switch(tlue->seq_no){
	case 0:
		Gauge_LevelUpEffectStart(tlue->gauge,&tlue->flag);
		Snd_SePlay(BSE_EXP_MAX);
		tlue->seq_no++;
		break;
	case 1:
		if(tlue->flag==TRUE){
			SCIO_ServerQueClear(tlue->bw,tlue->client_no,tlue->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
}

//============================================================================================
/**
 *	メッセージ表示まち
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_MessageWait(TCB_PTR tcb,void *work)
{
	TCB_MESSAGE_WAIT	*tmw=(TCB_MESSAGE_WAIT *)work;

	if(BattleWorkTimeIconGet(tmw->bw)){
		TimeWaitIconDel(BattleWorkTimeIconGet(tmw->bw));
		BattleWorkTimeIconSet(tmw->bw,NULL);
	}

	if(GF_MSG_PrintEndCheck(tmw->msg_index)==0){
		SCIO_ServerQueClear(tmw->bw,tmw->client_no,tmw->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
	}
}

//============================================================================================
/**
 *	メッセージ表示まち（アラートメッセージ専用）
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_AlertMessageWait(TCB_PTR tcb,void *work)
{
	TCB_ALERT_MESSAGE_WAIT	*tamw=(TCB_ALERT_MESSAGE_WAIT *)work;

	switch(tamw->seq_no){
	case 0:
		if(GF_MSG_PrintEndCheck(tamw->msg_index)==0){
			tamw->seq_no++;
			tamw->wait=0;
		}
		break;
	case 1:
		if(++tamw->wait==ALERT_WAIT){
			SCIO_AlertMessageEndSet(tamw->bw,tamw->client_no);
			SCIO_ServerQueClear(tamw->bw,tamw->client_no,tamw->command_code);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
}

//============================================================================================
/**
 *	エンカウントエフェクト
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	const	u8	EncountEffectTable[]={
	ECE_SPA_GRAVEL_001,			//砂利
	ECE_SPA_SANDS_001,			//砂浜
	ECE_SPA_GRASS_001,			//芝生
	ECE_SPA_POOL_BALL_001,		//水たまり
	ECE_SPA_ROCK_SURFACE_001,	//岩肌
	ECE_SPA_CAVE_001,			//洞窟
	ECE_SPA_SNOWFIELD_001,		//雪原
	ECE_SPA_WATER_001,			//水上
	ECE_SPA_ON_THE_ICE_001,		//氷上
	ECE_SPA_FLOOR_001,			//床
	ECE_SPA_BOG_001,			//沼地
	ECE_SPA_FLOOR_001,			//吊り橋（これ以降は、存在しなくなったけど念のため当たり障りのないエフェクトを呼ぶ）
	ECE_SPA_FLOOR_001,			//それ以外
};

static	const	int	EncountAfterColor[]={
	0x7fff,		//BG_ID_BASIC			//草原
	0x7fff,		//BG_ID_SEA				//海
	0x7fff,		//BG_ID_CITY			//街
	0x7fff,		//BG_ID_FOREST			//森林
	0x7fff,		//BG_ID_MOUNTAIN		//山岳
	0x7fff,		//BG_ID_SNOW_MOUNTAIN	//雪山
	0x7fff,		//BG_ID_ROOM_A			//室内Ａ
	0x7fff,		//BG_ID_ROOM_B			//室内Ｂ
	0x7fff,		//BG_ID_ROOM_C			//室内Ｃ
	0x0000,		//BG_ID_CAVE_A			//洞窟Ａ
	0x0000,		//BG_ID_CAVE_B			//洞窟Ｂ
	0x0000,		//BG_ID_CAVE_C			//洞窟Ｃ
};


enum{
	SEQ_ECE_INIT=0,
	SEQ_ECE_PARTICLE_SET,
	SEQ_ECE_MAIN,
	SEQ_ECE_END_CHECK,
	SEQ_ECE_END,
	SEQ_ECE_CANCEL_WITH_PARTICLE,
	SEQ_ECE_CANCEL
};

static	void	TCB_EncountEffect(TCB_PTR tcb,void *work)
{
	TCB_ENCOUNT_EFFECT	*tee=(TCB_ENCOUNT_EFFECT *)work;
	GF_BGL_INI			*bgl;
	PALETTE_FADE_PTR	pfd;
	int					ground_id;
	int					col;


	bgl=BattleWorkGF_BGL_INIGet(tee->bw);
	pfd=BattleWorkPfdGet(tee->bw);
	ground_id=BattleWorkGroundIDGet(tee->bw);
	col=EncountAfterColor[BattleWorkBGIDGet(tee->bw)];

//	if((tee->wait<SCROLL_TIME)&&(tee->seq_no<SEQ_ECE_END)){
//		GF_BGL_ScrollSet(bgl,GF_BGL_FRAME3_M,GF_BGL_SCROLL_X_INC,SCROLL_SPEED);
//	}

	tee->wait++;

#ifdef ENCOUNT_SKIP_ON
	//エフェクトのスキップチェック
	if((BattleWorkFightTypeGet(tee->bw)&FIGHT_TYPE_SIO)==0){
		if((sys.trg&PAD_BUTTON_A)&&(tee->seq_no<SEQ_ECE_END)){
			if(tee->seq_no<SEQ_ECE_MAIN){
				tee->seq_no=SEQ_ECE_CANCEL;
			}
			else{
				tee->seq_no=SEQ_ECE_CANCEL_WITH_PARTICLE;
			}
			PaletteFadeForceStop(pfd);
			return;
		}
	}
#endif ENCOUNT_SKIP_ON

	switch(tee->seq_no){
	case SEQ_ECE_INIT:
//		PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0x0400,0,16,0,0x0000);
		tee->seq_no++;
		break;
	case SEQ_ECE_PARTICLE_SET:
		if(PaletteFadeCheck(pfd)==0){
			{
				TEC_ADD_PARAM	tap;
	
				tee->ecem=ECEM_Init(HEAPID_BATTLE,NULL);
				
				tap.eff_no=EncountEffectTable[ground_id];
				tap.camera_type=GF_CAMERA_ORTHO;
				tee->ece[0]=ECEM_Load(tee->ecem,&tap);
	
				tap.eff_no=EncountEffectTable[ground_id]+1;
				tap.camera_type=GF_CAMERA_ORTHO;
				tee->ece[1]=ECEM_Load(tee->ecem,&tap);
	
				ECE_Call(tee->ece[0]);
				
				Snd_SePlay(BECEFF_GRASS_01);
	
				tee->seq_no++;
			}
		}
		break;
	case SEQ_ECE_MAIN:
//		if(tee->wait==20){
		if(tee->wait==10){
			PaletteFadeReq(pfd,PF_BIT_MAIN_BG,0xf3ff,0,0,16,col);
			PaletteFadeReq(pfd,PF_BIT_MAIN_OBJ,BATTLE_MAIN_OBJPAL_FADEBIT,0,0,16,col);
		}
//		if(tee->wait==41){
		if(tee->wait==20){
			ECE_Call(tee->ece[1]);
		}
//		if(tee->wait==46){					///< SE開始のタイミング
		if(tee->wait==23){					///< SE開始のタイミング
			Snd_SePlay(BECEFF_GRASS_02);
		}
//		if(tee->wait==56){
		if(tee->wait==28){
			MI_CpuCopy16(BattleWorkPushBGPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_BG),0x20*7);

			if(BattleWorkFightTypeGet(tee->bw)==FIGHT_TYPE_2vs2_YASEI){
				MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*5);
			}
			else if(BattleWorkFightTypeGet(tee->bw)&FIGHT_TYPE_2vs2){
				MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*7);
			}
			else if(BattleWorkFightTypeGet(tee->bw)&FIGHT_TYPE_TRAINER){
				MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*5);
			}
			else{
				MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*4);
			}
			PaletteFadeReq(pfd,PF_BIT_MAIN_BG,0xf3ff,0,16,0,col);
			PaletteFadeReq(pfd,PF_BIT_MAIN_OBJ,BATTLE_MAIN_OBJPAL_FADEBIT,0,16,0,col);
			PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,0,16,0,col);
		}
//		if(tee->wait==100){
		if(tee->wait==50){
			PaletteFadeReq(pfd,PF_BIT_MAIN_BG,0x0c00,0,16,0,0x0000);
			tee->seq_no++;
		}
		break;
	case SEQ_ECE_END_CHECK:
		if(ECE_EndCheck(tee->ece[1])==FALSE){
			ECEM_Free(tee->ecem);
			tee->seq_no++;
		}
		break;
	case SEQ_ECE_END:
		//メッセージウインドウDSアイコンパレットアニメスタート
		MSG_DsIconFlashReq(BattleWorkMsgIconGet(tee->bw),MSG_DSI_REQ_START);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	case SEQ_ECE_CANCEL_WITH_PARTICLE:
		ECEM_Skip(tee->ecem);
		ECEM_Free(tee->ecem);
		tee->seq_no++;
	case SEQ_ECE_CANCEL:
		MI_CpuCopy16(BattleWorkPushBGPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_BG),0x20*7);
		if(BattleWorkFightTypeGet(tee->bw)==FIGHT_TYPE_2vs2_YASEI){
			MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*5);
		}
		else if(BattleWorkFightTypeGet(tee->bw)&FIGHT_TYPE_2vs2){
			MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*7);
		}
		else if(BattleWorkFightTypeGet(tee->bw)&FIGHT_TYPE_TRAINER){
			MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*5);
		}
		else{
			MI_CpuCopy16(BattleWorkPushOBJPaletteGet(tee->bw),PaletteWorkDefaultWorkGet(pfd,FADE_MAIN_OBJ),0x20*4);
		}
		PaletteFadeReq(pfd,PF_BIT_MAIN_BG,0xffff,0,0,0,0x7fff);
		PaletteFadeReq(pfd,PF_BIT_MAIN_OBJ,BATTLE_MAIN_OBJPAL_FADEBIT,0,0,0,0xffff);
		PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,0,0,0,0x7fff);
		tee->seq_no=SEQ_ECE_END;
		break;
	}
}

//============================================================================================
/**
 *	技忘れ処理
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_WazaWasure(TCB_PTR tcb,void *work)
{
	TCB_WAZA_WASURE		*tww=(TCB_WAZA_WASURE *)work;
	PALETTE_FADE_PTR	pfd;

	pfd=BattleWorkPfdGet(tww->bw);

	switch(tww->seq_no){
	case 0:		//リスト画面へのフェード
//		MSG_DsIconFlashReq(BattleWorkMsgIconGet(tww->bw),MSG_DSI_REQ_STOP);
//		PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0x0c00,0,0,MSG_WINDOW_FADE,0x0000);
		PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,BATTLE_BAGLIST_FADE_SPEED,0,16,0x0000);
		tww->seq_no++;
		break;
	case 1:
		if(PaletteFadeCheck(pfd)==0){	//輝度変更フェード終了待ちして色々削除
			FightScreenTransition(tww->bw);

			tww->plist=sys_AllocMemory(HEAPID_BATTLE,sizeof(BPLIST_DATA));
			tww->plist->pp=BattleWorkPokePartyGet(tww->bw,tww->client_no);
			tww->plist->bw=tww->bw;
			tww->plist->heap=HEAPID_BATTLE;
			tww->plist->sel_poke=tww->sel_mons_no;
			tww->plist->chg_waza=tww->waza_no;
			tww->plist->end_flg=0;
			tww->plist->double_sel=0;
			tww->plist->mode=BPL_MODE_WAZASET;		// 技忘れ
			tww->plist->item=0;
			tww->plist->client_no=tww->client_no;
			tww->plist->cursor_flg=0;
				
			BattlePokeList_TaskAdd( tww->plist );
			tww->seq_no++;
		}
		break;
	case 2:
		if(tww->plist->end_flg){
			FightScreenRecover(tww->bw);
//			PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0x0c00,0,MSG_WINDOW_FADE,0,0x0000);
			PaletteFadeReq(pfd,PF_BIT_SUB_ALL,0xffff,BATTLE_BAGLIST_FADE_SPEED,16,0,0x0000);
			tww->seq_no++;
		}
		break;
	case 3:
		if(PaletteFadeCheck(pfd)==0){	//輝度変更フェード終了待ちして色々削除
//			MSG_DsIconFlashReq(BattleWorkMsgIconGet(tww->bw),MSG_DSI_REQ_START);
			if(tww->plist->sel_wp==BPL_SEL_WP_CANCEL){
				SCIO_PokemonSelectReturnSet(tww->bw,tww->client_no,SELECT_CANCEL);
			}
			else{
				SCIO_PokemonSelectReturnSet(tww->bw,tww->client_no,tww->plist->sel_wp+1);
			}
			SCIO_ServerQueClear(tww->bw,tww->client_no,tww->command_code);
			sys_FreeMemoryEz(tww->plist);
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
}

//============================================================================================
/**
 *	ソフトウエアスプライトにモザイクをかける
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_MosaicSet(TCB_PTR tcb,void *work)
{
	TCB_MOSAIC_SET	*tms=(TCB_MOSAIC_SET *)work;
	int				mosaic;

	switch(tms->seq_no){
	case 0:
		if(tms->wait==tms->wait_temp){
			tms->wait=0;
			mosaic=SoftSpriteParaGet(tms->ss,SS_PARA_MOSAIC);
			if(mosaic>tms->mosaic){
				mosaic--;
			}
			else if(mosaic<tms->mosaic){
				mosaic++;
			}
			SoftSpriteParaSet(tms->ss,SS_PARA_MOSAIC,mosaic);
			if(mosaic==tms->mosaic){
				tms->seq_no++;
			}
		}
		else{
			tms->wait++;
		}
		break;
	case 1:
		SCIO_ServerQueClear(tms->bw,tms->client_no,tms->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	手持ちゲージ：エンカウントIN
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_BallGaugeEncountSet(TCB_PTR tcb,void *work)
{
	TCB_BALL_GAUGE	*tbg=(TCB_BALL_GAUGE *)work;
	TEMOTI_SIDE side;
	BALL_IN_TYPE ball_in_type;
	
	if(BattleWorkMineEnemyCheck(tbg->bw, tbg->client_no) == 0){
		side = TEMOTI_MINE;
	}
	else{
		side = TEMOTI_ENEMY;
	}

	switch(tbg->seq_no){
	case 0:
		{
			TEMOTIGAUGE_PTR tg;
			BALL_IN_TYPE ball_in_type;
			BALL_POS_TYPE pos_type;
			
			if(tbg->encount_change == 0){
				ball_in_type = BALL_IN_TYPE_ENCOUNT;
				pos_type = BALL_POS_MIDDLE;
			}
			else{
				ball_in_type = BALL_IN_TYPE_CHANGE;
				switch(tbg->client_type){
				case CLIENT_TYPE_B:
					pos_type = BALL_POS_HIGH;
					break;
				case CLIENT_TYPE_D:
					pos_type = BALL_POS_LOW;
					break;
				default:
					pos_type = BALL_POS_MIDDLE;
					break;
				}
			}
			
			tg = TEMOTI_InEffectSet(tbg->status, side, ball_in_type, pos_type,
				BattleWorkCATS_SYS_PTRGet(tbg->bw), BattleWorkCATS_RES_PTRGet(tbg->bw));
			BattleWorkGF_BGL_TGSet(tbg->bw, side, tg);
		}
		tbg->seq_no++;
		break;
	case 1:
		if(TEMOTI_InEffectEndCheck(BattleWorkGF_BGL_TGGet(tbg->bw, side)) == TRUE){
//解放はOUTで			TEMOTI_EffectFree(tg);
			tbg->seq_no++;
		}
		break;
	default:
		SCIO_ServerQueClear(tbg->bw,tbg->client_no,tbg->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	手持ちゲージ：エンカウントOUT
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_BallGaugeEncountOut(TCB_PTR tcb,void *work)
{
	TCB_BALL_GAUGE	*tbg=(TCB_BALL_GAUGE *)work;
	TEMOTI_SIDE side;
	TEMOTIGAUGE_PTR tg;
	ARROW_OUT_TYPE arrow_out_type;
	BALL_OUT_TYPE ball_out_type;
	
	if(BattleWorkMineEnemyCheck(tbg->bw, tbg->client_no) == 0){
		side = TEMOTI_MINE;
	}
	else{
		side = TEMOTI_ENEMY;
	}
	tg = BattleWorkGF_BGL_TGGet(tbg->bw, side);
	
	switch(tbg->seq_no){
	case 0:
		if(tbg->encount_change == 0){
			arrow_out_type = ARROW_OUT_TYPE_SCROLL;
			ball_out_type = BALL_OUT_TYPE_ENCOUNT;
		}
		else{
			arrow_out_type = ARROW_OUT_TYPE_SPOT;
			ball_out_type = BALL_OUT_TYPE_CHANGE;
		}
		
		TEMOTI_OutEffectSet(tg, arrow_out_type, ball_out_type);
		tbg->seq_no++;
		break;
	case 1:
		if(TEMOTI_OutEffectEndCheck(tg) == TRUE){
			TEMOTI_EffectFree(tg);
			BattleWorkGF_BGL_TGSet(tbg->bw, side, NULL);
			tbg->seq_no++;
		}
		break;
	default:
		SCIO_ServerQueClear(tbg->bw,tbg->client_no,tbg->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	ソフトスプライト＞OAM変換
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
static	void	TCB_SStoOAM(TCB_PTR tcb,void *work)
{
	TCB_SS_TO_OAM	*tsto=(TCB_SS_TO_OAM *)work;
	
	switch(tsto->seq_no){
	case 0:
		GF_ASSERT(tsto->cp->ods == NULL);
		tsto->cp->ods = OAM_Drop_Init(tsto->bw, HEAPID_BATTLE, tsto->client_no);
		tsto->seq_no++;
		break;
		
	default:
		SCIO_ServerQueClear(tsto->bw,tsto->client_no,tsto->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	OAM＞ソフとスプライト変換
 *
 * @param[in]	tcb		TCBシステムワーク
 * @param[in]	work	ワークエリアポインタ
 */
//============================================================================================
#define TOTS_DELETE_WAIT	(5)		///< ウェイト
static	void	TCB_OAMtoSS(TCB_PTR tcb,void *work)
{
	TCB_OAM_TO_SS	*tots=(TCB_OAM_TO_SS *)work;
	
	GF_ASSERT(tots->cp->ods != NULL);
	
	///< Bの位置のポケモンは、DのSSPとのプライオリティの関係ですぐ消えるのはまずい
	if (OAM_Drop_ClientTypeGet(tots->cp->ods) == CLIENT_TYPE_B){
		if (tots->seq_no < TOTS_DELETE_WAIT){
			tots->seq_no++;
			return;
		}
	}
	
	OAM_Drop_End(tots->cp->ods, tots->client_no);
	tots->cp->ods = NULL;
	
	SCIO_ServerQueClear(tots->bw,tots->client_no,tots->command_code);
	sys_FreeMemoryEz(work);
	TCB_Delete(tcb);
	
#if 0
	switch(tots->seq_no){
	case 0:
		GF_ASSERT(tots->cp->ods != NULL);

		///< Bの位置のポケモンは、DのSSPとのプライオリティの関係ですぐ消えるのはまずい
		if (OAM_Drop_ClientTypeGet(tots->cp->ods) != CLIENT_TYPE_B){
			OAM_Drop_End(tots->cp->ods, tots->client_no);
			tots->cp->ods = NULL;
			tots->seq_no = 0xFF;
			break;
		}
		tots->seq_no++;
		break;
	
	case 1:
		tots->seq_no++;
		break;
	
	case 2:
		tots->seq_no++;
		break;
		
	case 3:
		OAM_Drop_End(tots->cp->ods, tots->client_no);
		tots->cp->ods = NULL;
		tots->seq_no++;
		break;
		
	default:
		SCIO_ServerQueClear(tots->bw,tots->client_no,tots->command_code);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
#endif
}

//-----------------------------------------------------------------------------
//		外部関数用ツール群
//-----------------------------------------------------------------------------
//============================================================================================
/**
 *	ユーザインタフェースセット
 *
 * @param[in]	bw		戦闘システムワークポインタ
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
void	CT_UISet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	int	fight_type=BattleWorkFightTypeGet(bw);

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
		if(fight_type&FIGHT_TYPE_SIO){
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				cp->ui.UI_CommandSelect=&TCB_CommandSelectSIO;
				cp->ui.UI_WazaSelect=&TCB_WazaSelectSIO;
				cp->ui.UI_DirSelect=&TCB_DirSelectSIO;
				cp->ui.UI_ItemSelect=&TCB_ItemSelectSIO;
				cp->ui.UI_PokemonSelect=&TCB_PokemonSelectSIO;
				cp->ui.UI_YesNoSelect=&TCB_YesNoSelectSIO;
				cp->client_boot=CLIENT_BOOT_SIO;
			}
			else{
				cp->ui.UI_CommandSelect=&TCB_CommandSelectAI;
				cp->ui.UI_WazaSelect=&TCB_WazaSelectAI;
				cp->ui.UI_DirSelect=&TCB_DirSelectAI;
				cp->ui.UI_ItemSelect=&TCB_ItemSelectAI;
				cp->ui.UI_PokemonSelect=&TCB_PokemonSelectAI;
				cp->ui.UI_YesNoSelect=&TCB_YesNoSelectAI;
				cp->client_boot=CLIENT_BOOT_AI;
			}
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelectAI;
			cp->ui.UI_WazaSelect=&TCB_WazaSelectAI;
			cp->ui.UI_DirSelect=&TCB_DirSelectAI;
			cp->ui.UI_ItemSelect=&TCB_ItemSelectAI;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelectAI;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelectAI;
			cp->client_boot=CLIENT_BOOT_AI;
		}
		return;
	}
#endif

	if(fight_type&FIGHT_TYPE_AI){
		if(cp->client_no){
			cp->ui.UI_CommandSelect=&TCB_CommandSelectAI;
			cp->ui.UI_WazaSelect=&TCB_WazaSelectAI;
			cp->ui.UI_DirSelect=&TCB_DirSelectAI;
			cp->ui.UI_ItemSelect=&TCB_ItemSelectAI;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelectAI;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelectAI;
			cp->client_boot=CLIENT_BOOT_AI;
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelect;
			cp->ui.UI_WazaSelect=&TCB_WazaSelect;
			cp->ui.UI_DirSelect=&TCB_DirSelect;
			cp->ui.UI_ItemSelect=&TCB_ItemSelect;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelect;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelect;
			cp->client_boot=CLIENT_BOOT_NORMAL;
		}
	}
	else if((fight_type&(FIGHT_TYPE_MULTI|FIGHT_TYPE_TOWER))==(FIGHT_TYPE_MULTI|FIGHT_TYPE_TOWER)){
		if(cp->client_type&CLIENT_ENEMY_FLAG){
			if(BattleWorkServerFlagGet(bw)){
				cp->ui.UI_CommandSelect=&TCB_CommandSelectAI;
				cp->ui.UI_WazaSelect=&TCB_WazaSelectAI;
				cp->ui.UI_DirSelect=&TCB_DirSelectAI;
				cp->ui.UI_ItemSelect=&TCB_ItemSelectAI;
				cp->ui.UI_PokemonSelect=&TCB_PokemonSelectAI;
				cp->ui.UI_YesNoSelect=&TCB_YesNoSelectAI;
				cp->client_boot=CLIENT_BOOT_AI;
			}
			else{
				cp->ui.UI_CommandSelect=&TCB_CommandSelectSIO;
				cp->ui.UI_WazaSelect=&TCB_WazaSelectSIO;
				cp->ui.UI_DirSelect=&TCB_DirSelectSIO;
				cp->ui.UI_ItemSelect=&TCB_ItemSelectSIO;
				cp->ui.UI_PokemonSelect=&TCB_PokemonSelectSIO;
				cp->ui.UI_YesNoSelect=&TCB_YesNoSelectSIO;
				cp->client_boot=CLIENT_BOOT_SIO;
			}
		}
		else if(cp->client_type!=BattleWorkClientTypeGet(bw,CommGetCurrentID()*2)){
			cp->ui.UI_CommandSelect=&TCB_CommandSelectSIO;
			cp->ui.UI_WazaSelect=&TCB_WazaSelectSIO;
			cp->ui.UI_DirSelect=&TCB_DirSelectSIO;
			cp->ui.UI_ItemSelect=&TCB_ItemSelectSIO;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelectSIO;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelectSIO;
			cp->client_boot=CLIENT_BOOT_SIO;
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelect;
			cp->ui.UI_WazaSelect=&TCB_WazaSelect;
			cp->ui.UI_DirSelect=&TCB_DirSelect;
			cp->ui.UI_ItemSelect=&TCB_ItemSelect;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelect;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelect;
			cp->client_boot=CLIENT_BOOT_NORMAL;
		}
	}
	else if(fight_type&FIGHT_TYPE_MULTI){
		if(cp->client_type!=BattleWorkClientTypeGet(bw,CommGetCurrentID())){
			cp->ui.UI_CommandSelect=&TCB_CommandSelectSIO;
			cp->ui.UI_WazaSelect=&TCB_WazaSelectSIO;
			cp->ui.UI_DirSelect=&TCB_DirSelectSIO;
			cp->ui.UI_ItemSelect=&TCB_ItemSelectSIO;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelectSIO;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelectSIO;
			cp->client_boot=CLIENT_BOOT_SIO;
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelect;
			cp->ui.UI_WazaSelect=&TCB_WazaSelect;
			cp->ui.UI_DirSelect=&TCB_DirSelect;
			cp->ui.UI_ItemSelect=&TCB_ItemSelect;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelect;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelect;
			cp->client_boot=CLIENT_BOOT_NORMAL;
		}
	}
	else if(fight_type&FIGHT_TYPE_SIO){
		if(cp->client_type&CLIENT_ENEMY_FLAG){
			cp->ui.UI_CommandSelect=&TCB_CommandSelectSIO;
			cp->ui.UI_WazaSelect=&TCB_WazaSelectSIO;
			cp->ui.UI_DirSelect=&TCB_DirSelectSIO;
			cp->ui.UI_ItemSelect=&TCB_ItemSelectSIO;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelectSIO;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelectSIO;
			cp->client_boot=CLIENT_BOOT_SIO;
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelect;
			cp->ui.UI_WazaSelect=&TCB_WazaSelect;
			cp->ui.UI_DirSelect=&TCB_DirSelect;
			cp->ui.UI_ItemSelect=&TCB_ItemSelect;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelect;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelect;
			cp->client_boot=CLIENT_BOOT_NORMAL;
		}
	}
	else if(fight_type&FIGHT_TYPE_POKE_PARK){
		if(cp->client_type&CLIENT_ENEMY_FLAG){
			cp->ui.UI_CommandSelect=&TCB_CommandSelectPokepark;
			cp->ui.UI_WazaSelect=NULL;
			cp->ui.UI_DirSelect=NULL;
			cp->ui.UI_ItemSelect=NULL;
			cp->ui.UI_PokemonSelect=NULL;
			cp->ui.UI_YesNoSelect=NULL;
			cp->client_boot=CLIENT_BOOT_AI;
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelect;
			cp->ui.UI_WazaSelect=NULL;
			cp->ui.UI_DirSelect=NULL;
			cp->ui.UI_ItemSelect=NULL;
			cp->ui.UI_PokemonSelect=NULL;
			cp->ui.UI_YesNoSelect=NULL;
			cp->client_boot=CLIENT_BOOT_NORMAL;
		}
	}
	else if(fight_type&FIGHT_TYPE_SAFARI){
		if(cp->client_type&CLIENT_ENEMY_FLAG){
			cp->ui.UI_CommandSelect=&TCB_CommandSelectSafari;
			cp->ui.UI_WazaSelect=NULL;
			cp->ui.UI_DirSelect=NULL;
			cp->ui.UI_ItemSelect=NULL;
			cp->ui.UI_PokemonSelect=NULL;
			cp->ui.UI_YesNoSelect=NULL;
			cp->client_boot=CLIENT_BOOT_AI;
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelect;
			cp->ui.UI_WazaSelect=NULL;
			cp->ui.UI_DirSelect=NULL;
			cp->ui.UI_ItemSelect=NULL;
			cp->ui.UI_PokemonSelect=NULL;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelect;
			cp->client_boot=CLIENT_BOOT_NORMAL;
		}
	}
	else{
		if(cp->client_type&CLIENT_ENEMY_FLAG){
			cp->ui.UI_CommandSelect=&TCB_CommandSelectAI;
			cp->ui.UI_WazaSelect=&TCB_WazaSelectAI;
			cp->ui.UI_DirSelect=&TCB_DirSelectAI;
			cp->ui.UI_ItemSelect=&TCB_ItemSelectAI;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelectAI;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelectAI;
			cp->client_boot=CLIENT_BOOT_AI;
		}
		else{
			cp->ui.UI_CommandSelect=&TCB_CommandSelect;
			cp->ui.UI_WazaSelect=&TCB_WazaSelect;
			cp->ui.UI_DirSelect=&TCB_DirSelect;
			cp->ui.UI_ItemSelect=&TCB_ItemSelect;
			cp->ui.UI_PokemonSelect=&TCB_PokemonSelect;
			cp->ui.UI_YesNoSelect=&TCB_YesNoSelect;
			cp->client_boot=CLIENT_BOOT_NORMAL;
		}
	}
}

//============================================================================================
/**
 *	client_type取得関数
 *
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
u8	CT_CPClientTypeGet(CLIENT_PARAM *cp)
{
	return cp->client_type;
}

//============================================================================================
/**
 *	client_boot取得関数
 *
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
u8	CT_CPClientBootGet(CLIENT_PARAM *cp)
{
	return cp->client_boot;
}

//============================================================================================
/**
 *	soft_sprite取得関数
 *
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
SOFT_SPRITE	*CT_CPSoftSpriteGet(CLIENT_PARAM *cp)
{
	if(cp->poke_ss){
		return cp->poke_ss;
	}
	else{
		return cp->tr_ss;
	}
}

//============================================================================================
/**
 *	gauge_work取得関数
 *
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
GAUGE_WORK		*CT_CPGaugeWorkGet(CLIENT_PARAM *cp)
{
	return &cp->gauge;
}

//--------------------------------------------------------------
/**
 * @brief   CURSOR_SAVEワークのポインタ取得
 *
 * @param   cp				クライアントワークポインタ
 *
 * @retval  CURSOR_SAVEワークのポインタ
 */
//--------------------------------------------------------------
CURSOR_SAVE * CT_CursorSavePtrGet(CLIENT_PARAM *cp)
{
	return &cp->cursor_save;
}

//--------------------------------------------------------------
/**
 * @brief   CURSOR_SAVEワークを初期化する
 * @param   cp		クライアントワークポインタ
 */
//--------------------------------------------------------------
void CT_CursorSaveClear(CLIENT_PARAM *cp)
{
	MI_CpuClear8(&cp->cursor_save, sizeof(CURSOR_SAVE));
}

//-----------------------------------------------------------------------------
//		外部非公開関数
//-----------------------------------------------------------------------------
//============================================================================================
/**
 *	SoftSpriteのセットと技エフェクト用キャラ展開とパラメータ取得をする関数
 *
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
static	SOFT_SPRITE	*CT_SoftSpriteAdd(BATTLE_WORK *bw,SOFT_SPRITE_MANAGER *ssm_p,SOFT_SPRITE_ARC *ssa,
							  int pos_x,int pos_y,int pos_z,int ofs_y,int height,int ofx,int shadow,int client_no,
							  SOFT_SPRITE_ANIME *anm_tbl,SOFT_SPRITE_MOVE_FUNC *move)
{
	SOFT_SPRITE	*ss;
	u8			*oam_temp=ExChrParamExChrBufferGet(BattleWorkExChrParamGet(bw),client_no);
	int			type;
	int			dir;
	
	type=BattleWorkClientTypeGet(bw,client_no);
	
	if (type & CLIENT_ENEMY_FLAG){
		dir = PARA_FRONT;
	}
	else {
		dir = PARA_BACK;
	}

	Ex_ChangesInto_BattlePokeData(ssa->arc_no,ssa->index_chr,HEAPID_BATTLE,oam_temp, ssa->personal_rnd, FALSE, dir, ssa->strike_mons);
	ExChrParamArcIDSet(BattleWorkExChrParamGet(bw),client_no,ssa->arc_no);
	ExChrParamPalIndexSet(BattleWorkExChrParamGet(bw),client_no,ssa->index_pal);
	ExChrParamHeightSet(BattleWorkExChrParamGet(bw),client_no,ofs_y);

	ss=SoftSpriteAddNum(ssm_p,ssa,pos_x,pos_y+ofs_y,pos_z,client_no,client_no,anm_tbl,move);

	if(type&CLIENT_ENEMY_FLAG){
		if(type>CLIENT_TYPE_BB){
			type=type>>1;
		}
		SoftSpriteParaSet(ss,SS_PARA_SHADOW_REQ,type);
		SoftSpriteParaSet(ss,SS_PARA_SHADOW_SIZE,shadow);
		SoftSpriteParaSet(ss,SS_PARA_SHADOW_Y,(pos_y+ofs_y)+(SHADOW_OFS-ofs_y));
		SoftSpriteParaSet(ss,SS_PARA_SHADOW_OX,ofx);
		SoftSpriteParaSet(ss,SS_PARA_SHADOW_OY,SHADOW_OFS-ofs_y);
		SoftSpriteParaSet(ss,SS_PARA_SHADOW_HEIGHT,height);
	}

	return ss;
}

//============================================================================================
/**
 *	FightTypeとメッセージ表示するClientから戻すメッセージのパラメータを生成する
 *
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
static	void	CT_ModosuMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MODOSU_MESSAGE_PARAM *mmp,MESSAGE_PARAM *mp)
{
	if(cp->client_type&CLIENT_ENEMY_FLAG){
		if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO){
			mp->msg_id=TuushinIrekaeMsg;
			mp->msg_tag=TAG_TRNAME_NICK;
			mp->msg_para[0]=cp->client_no;
			mp->msg_para[1]=cp->client_no|(mmp->sel_mons_no<<8);
		}
		else{
			mp->msg_id=IrekaeMsg2;
			mp->msg_tag=TAG_TRTYPE_TRNAME_NICK;
			mp->msg_para[0]=cp->client_no;
			mp->msg_para[1]=cp->client_no;
			mp->msg_para[2]=cp->client_no|(mmp->sel_mons_no<<8);
		}
	}
	else{
		//受けたダメージなどで、メッセージを変化
		if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)==0)&&
		   ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO)==0)){
			if(mmp->rate==0){
				mp->msg_id=IrekaeMsg_0;
			}
			else if(mmp->rate<25){
				mp->msg_id=IrekaeMsg_1;
			}
			else if(mmp->rate<50){
				mp->msg_id=IrekaeMsg_4;
			}
			else if(mmp->rate<75){
				mp->msg_id=IrekaeMsg_2;
			}
			else{
				mp->msg_id=IrekaeMsg_3;
			}
		}
		else{
			mp->msg_id=IrekaeMsg_1;
		}
		mp->msg_tag=TAG_NICK;
		mp->msg_para[0]=cp->client_no|(mmp->sel_mons_no<<8);
	}
}

//============================================================================================
/**
 *	FightTypeとメッセージ表示するClientから繰り出すメッセージのパラメータを生成する
 *
 * @param[in]	cp		クライアントワークポインタ
 */
//============================================================================================
static	void	CT_KuridasuMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,KURIDASU_MESSAGE_PARAM *kmp,MESSAGE_PARAM *mp)
{
	if(cp->client_type&CLIENT_ENEMY_FLAG){
		if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO)==0){
			mp->msg_id=KuridashiMsg;
			mp->msg_tag=TAG_TRTYPE_TRNAME_NICK;
			mp->msg_para[0]=cp->client_no;
			mp->msg_para[1]=cp->client_no;
			mp->msg_para[2]=cp->client_no|(kmp->sel_mons_no<<8);
		}
		else{
			mp->msg_id=TuushinKuridashiMsg;
			mp->msg_tag=TAG_TRNAME_NICK;
			mp->msg_para[0]=cp->client_no;
			mp->msg_para[1]=cp->client_no|(kmp->sel_mons_no<<8);
		}
	}
	else{
		//与えたダメージなどで、メッセージを変化
		if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)==0)&&
		   ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO)==0)){
			if(kmp->rate<100){
				mp->msg_id=AppearMsg_3;
			}
			else if(kmp->rate<325){
				mp->msg_id=AppearMsg_4;
			}
			else if(kmp->rate<550){
				mp->msg_id=AppearMsg_2;
			}
			else if(kmp->rate<775){
				mp->msg_id=AppearMsg_1;
			}
			else{
				mp->msg_id=AppearMsg_0;
			}
		}
		else{
			mp->msg_id=AppearMsg_0;
		}
		mp->msg_tag=TAG_NICK;
		mp->msg_para[0]=cp->client_no|(kmp->sel_mons_no<<8);
	}
}

//============================================================================================
/**
 *	エンカウントメッセージのパラメータを生成する
 *
 * @param[in]	bw		戦闘システムワーク
 * @param[in]	cp		クライアントワークポインタ
 * @param[in]	mp		メッセージパラメータ
 */
//============================================================================================
static	void		CT_EncountMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *mp)
{
	u32	fight_type;
	int	cli1_no;
	int	cli2_no;

	fight_type=BattleWorkFightTypeGet(bw);

	if(fight_type&FIGHT_TYPE_2vs2){
		cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_B);
		cli2_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_D);
	}
	else{
		cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_BB);
		cli2_no=cli1_no;
	}

	if(fight_type&FIGHT_TYPE_SIO){
		if(fight_type&FIGHT_TYPE_TOWER){
			mp->msg_id=Trainer2Msg;
			mp->msg_tag=TAG_TRTYPE_TRNAME_TRTYPE_TRNAME;
			mp->msg_para[0]=cli1_no;
			mp->msg_para[1]=cli1_no;
			mp->msg_para[2]=cli2_no;
			mp->msg_para[3]=cli2_no;
		}
		else if(fight_type&FIGHT_TYPE_MULTI){
			mp->msg_id=TuushinMultiTrainerEncountMsg;
			mp->msg_tag=TAG_TRNAME_TRNAME;
			mp->msg_para[0]=cli1_no;
			mp->msg_para[1]=cli2_no;
		}
		else{
			mp->msg_id=TuushinTrainerEncountMsg;
			mp->msg_tag=TAG_TRNAME;
			mp->msg_para[0]=cli1_no;
		}
	}
	else{
		if((fight_type&FIGHT_TYPE_TAG)||
		   (fight_type&FIGHT_TYPE_MULTI)){
			mp->msg_id=Trainer2Msg;
			mp->msg_tag=TAG_TRTYPE_TRNAME_TRTYPE_TRNAME;
			mp->msg_para[0]=cli1_no;
			mp->msg_para[1]=cli1_no;
			mp->msg_para[2]=cli2_no;
			mp->msg_para[3]=cli2_no;
		}
		else{
			mp->msg_id=TrainerEncountMsg;
			mp->msg_tag=TAG_TRTYPE_TRNAME;
			mp->msg_para[0]=cli1_no;
			mp->msg_para[1]=cli1_no;
		}
	}
}

//============================================================================================
/**
 *	エンカウント時の繰り出しメッセージのパラメータを生成する
 *
 * @param[in]	bw		戦闘システムワーク
 * @param[in]	cp		クライアントワークポインタ
 * @param[in]	ekmp	エンカウント時の繰り出しメッセージパラメータ
 * @param[in]	mp		メッセージパラメータ
 */
//============================================================================================
static	void		CT_EncountKuridasuMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,
													   ENCOUNT_KURIDASU_MESSAGE_PARAM *ekmp,MESSAGE_PARAM *mp)
{
	u32	fight_type;
	int	cli1_no;
	int	cli2_no;

	fight_type=BattleWorkFightTypeGet(bw);

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		if(fight_type&FIGHT_TYPE_2vs2){
			cli1_no=cp->client_no;
			cli2_no=BattleWorkPartnerClientNoGet(bw,cp->client_no);
		}
		else{
			cli1_no=cp->client_no;
			cli2_no=cli1_no;
		}
	
		if(fight_type&FIGHT_TYPE_SIO){
			if(fight_type&FIGHT_TYPE_TOWER){
				mp->msg_id=KuridashiMsg4;
				mp->msg_tag=TAG_TRTYPE_TRNAME_NICKx2;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no;
				mp->msg_para[2]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[3]=cli2_no;
				mp->msg_para[4]=cli2_no;
				mp->msg_para[5]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else if(fight_type&FIGHT_TYPE_MULTI){
				mp->msg_id=TuushinKuridashiMultiMsg;
				mp->msg_tag=TAG_TRNAME_NICK_TRNAME_NICK;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[2]=cli2_no;
				mp->msg_para[3]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else if(fight_type&FIGHT_TYPE_2vs2){
				mp->msg_id=TuushinKuridashi2vs2Msg;
				mp->msg_tag=TAG_TRNAME_NICK_NICK;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[2]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else{
				mp->msg_id=TuushinKuridashiMsg;
				mp->msg_tag=TAG_TRNAME_NICK;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
			}
		}
		else{
			if((fight_type&FIGHT_TYPE_TAG)||
			   (fight_type&FIGHT_TYPE_MULTI)){
				mp->msg_id=KuridashiMsg4;
				mp->msg_tag=TAG_TRTYPE_TRNAME_NICKx2;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no;
				mp->msg_para[2]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[3]=cli2_no;
				mp->msg_para[4]=cli2_no;
				mp->msg_para[5]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else if(fight_type&FIGHT_TYPE_2vs2){
				mp->msg_id=Kuridashi2vs2Msg;
				mp->msg_tag=TAG_TRTYPE_TRNAME_NICK_NICK;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no;
				mp->msg_para[2]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[3]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else{
				mp->msg_id=KuridashiMsg;
				mp->msg_tag=TAG_TRTYPE_TRNAME_NICK;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no;
				mp->msg_para[2]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
			}
		}
	}
	else{
		if(fight_type&FIGHT_TYPE_SIO){
			{
				u8	sio_id=CommGetCurrentID();

				if(fight_type&FIGHT_TYPE_MULTI){
					switch(CommGetStandNo(sio_id)){
					case 0:
					case 3:
						cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_C);
						cli2_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_A);
						break;
					case 1:
					case 2:
						cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_A);
						cli2_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_C);
						break;
					}
				}
				else if(fight_type&FIGHT_TYPE_2vs2){
					cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_A);
					cli2_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_C);
				}
				else{
					cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_AA);
					cli2_no=cli1_no;
				}
			}
		}
		else if(fight_type&FIGHT_TYPE_MULTI){
			cli1_no=BattleWorkPartnerClientNoGet(bw,cp->client_no);
			cli2_no=cp->client_no;
		}
		else if(fight_type&FIGHT_TYPE_2vs2){
			cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_A);
			cli2_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_C);
		}
		else{
			cli1_no=cp->client_no;
			cli2_no=cli1_no;
		}
	
		if(fight_type&FIGHT_TYPE_SIO){
			if(fight_type&FIGHT_TYPE_MULTI){
				mp->msg_id=TuushinAppearMultiMsg;
				mp->msg_tag=TAG_TRNAME_NICK_NICK;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[2]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else if(fight_type&FIGHT_TYPE_2vs2){
				mp->msg_id=Appear2vs2Msg;
				mp->msg_tag=TAG_NICK_NICK;
				mp->msg_para[0]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[1]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else{
				mp->msg_id=AppearMsg_0;
				mp->msg_tag=TAG_NICK;
				mp->msg_para[0]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
			}
		}
		else{
			if(fight_type&FIGHT_TYPE_MULTI){
				mp->msg_id=AppearMsg3;
				mp->msg_tag=TAG_TRTYPE_TRNAME_NICK_NICK;
				mp->msg_para[0]=cli1_no;
				mp->msg_para[1]=cli1_no;
				mp->msg_para[2]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[3]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else if(fight_type&FIGHT_TYPE_2vs2){
				mp->msg_id=Appear2vs2Msg;
				mp->msg_tag=TAG_NICK_NICK;
				mp->msg_para[0]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
				mp->msg_para[1]=cli2_no|(ekmp->sel_mons_no[cli2_no]<<8);
			}
			else{
				mp->msg_id=AppearMsg_0;
				mp->msg_tag=TAG_NICK;
				mp->msg_para[0]=cli1_no|(ekmp->sel_mons_no[cli1_no]<<8);
			}
		}
	}
}

//============================================================================================
/**
 *	通信対戦時の勝敗メッセージのパラメータを生成する
 *
 * @param[in]	bw		戦闘システムワーク
 * @param[in]	cp		クライアントワークポインタ
 * @param[in]	mp		メッセージパラメータ
 */
//============================================================================================
static	void	CT_WinLoseMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *mp)
{
	u32	fight_type;
	int	cli1_no;
	int	cli2_no;
	int	win_lose_flag;

	fight_type=BattleWorkFightTypeGet(bw);
	win_lose_flag=BattleWorkWinLoseGet(bw);

	if(fight_type&FIGHT_TYPE_2vs2){
		cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_B);
		cli2_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_D);
	}
	else{
		cli1_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_BB);
		cli2_no=cli1_no;
	}

	switch(win_lose_flag){
	case FIGHT_WIN:
		if(fight_type&FIGHT_TYPE_MULTI){
			mp->msg_id=TuushinWinMsg2;
			mp->msg_tag=TAG_TRNAME_TRNAME;
			mp->msg_para[0]=cli1_no;
			mp->msg_para[1]=cli2_no;
		}
		else{
			mp->msg_id=TuushinWinMsg;
			mp->msg_tag=TAG_TRNAME;
			mp->msg_para[0]=cli1_no;
		}
		break;
	case FIGHT_LOSE:
		if(fight_type&FIGHT_TYPE_MULTI){
			mp->msg_id=TuushinLoseMsg2;
			mp->msg_tag=TAG_TRNAME_TRNAME;
			mp->msg_para[0]=cli1_no;
			mp->msg_para[1]=cli2_no;
		}
		else{
			mp->msg_id=TuushinLoseMsg;
			mp->msg_tag=TAG_TRNAME;
			mp->msg_para[0]=cli1_no;
		}
		break;
	case FIGHT_DRAW:
		if(fight_type&FIGHT_TYPE_MULTI){
			mp->msg_id=TuushinDrawMsg2;
			mp->msg_tag=TAG_TRNAME_TRNAME;
			mp->msg_para[0]=cli1_no;
			mp->msg_para[1]=cli2_no;
		}
		else{
			mp->msg_id=TuushinDrawMsg;
			mp->msg_tag=TAG_TRNAME;
			mp->msg_para[0]=cli1_no;
		}
		break;
	}
}

//============================================================================================
/**
 *	通信対戦時のにげるメッセージのパラメータを生成する
 *
 * @param[in]	bw		戦闘システムワーク
 * @param[in]	cp		クライアントワークポインタ
 * @param[in]	emp		逃げるメッセージパラメータ
 * @param[in]	mp		メッセージパラメータ
 */
//============================================================================================
static	void	CT_EscapeMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,ESCAPE_MESSAGE_PARAM *emp,MESSAGE_PARAM *mp)
{
	int	client_no;
	int	mine_escape=0;
	int	enemy_escape=0;

//	GF_ASSERT(emp->escape_flag!=0);
	
	for(client_no=0;client_no<BattleWorkClientSetMaxGet(bw);client_no++){
		if(emp->escape_flag&No2Bit(client_no)){
			if(BattleWorkMineEnemyCheck(bw,client_no)){
				enemy_escape++;
			}
			else{
				mine_escape++;
			}
		}
	}

	if((mine_escape)&&(enemy_escape)){
		mp->msg_id=EscapeMsg;
		mp->msg_tag=TAG_NONE;
		BattleWorkWinLoseSet(bw,FIGHT_DRAW|FIGHT_ESCAPE_SELECT|FIGHT_ESCAPE_SELECT_PAUSE);
	}
	else if(mine_escape){
		mp->msg_id=EscapeMsg;
		mp->msg_tag=TAG_NONE;
		BattleWorkWinLoseSet(bw,FIGHT_LOSE|FIGHT_ESCAPE_SELECT|FIGHT_ESCAPE_SELECT_PAUSE);
	}
	else{
		if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI){
			mp->msg_id=TuushinEscapeMsg2;
			mp->msg_tag=TAG_TRNAME_TRNAME;
			mp->msg_para[0]=BattleWorkClientNoGet(bw,CLIENT_TYPE_B);
			mp->msg_para[1]=BattleWorkClientNoGet(bw,CLIENT_TYPE_D);
		}
		else if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
			mp->msg_id=TuushinEscapeMsg;
			mp->msg_tag=TAG_TRNAME;
			mp->msg_para[0]=BattleWorkClientNoGet(bw,CLIENT_TYPE_B);
		}
		else{
			mp->msg_id=TuushinEscapeMsg;
			mp->msg_tag=TAG_TRNAME;
			mp->msg_para[0]=BattleWorkClientNoGet(bw,CLIENT_TYPE_BB);
		}
		BattleWorkWinLoseSet(bw,FIGHT_WIN|FIGHT_ESCAPE_SELECT|FIGHT_ESCAPE_SELECT_PAUSE);
	}
}

//============================================================================================
/**
 *	バトルタワーのリタイアメッセージのパラメータを生成する
 *
 * @param[in]	bw		戦闘システムワーク
 * @param[in]	cp		クライアントワークポインタ
 * @param[in]	mp		メッセージパラメータ
 */
//============================================================================================
static	void	CT_GiveUpMessageParamMake(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *mp)
{
	mp->msg_id=GiveUpMsg2;
	mp->msg_tag=TAG_TRNAME;

	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO){
		if(CommGetStandNo(CommGetCurrentID())){
			mp->msg_para[0]=BattleWorkClientNoGet(bw,CLIENT_TYPE_C);
		}
		else{
			mp->msg_para[0]=BattleWorkClientNoGet(bw,CLIENT_TYPE_A);
		}
	}
	else{
		mp->msg_para[0]=cp->client_no;
	}
	BattleWorkWinLoseSet(bw,FIGHT_LOSE|FIGHT_ESCAPE_SELECT|FIGHT_ESCAPE_SELECT_PAUSE);
}

//============================================================================================
/**
 *	トレーナーキャラのCLACTリソースのロード
 *
 * @param[in]	bw		戦闘システム構造体
 * @param[in]	type	client_type
 * @param[in]	trtype	トレーナータイプ
 * @param[in]	id		CLACTリソースIDへのオフセット
 */
//============================================================================================
static	CATS_ACT_PTR	CT_TrainerCLACTResourceLoad(BATTLE_WORK *bw,int type,int trtype,int id)
{
	CATS_SYS_PTR				csp;
	CATS_RES_PTR				crp;
	PALETTE_FADE_PTR			pfd;
	TCATS_OBJECT_ADD_PARAM_S	op;
	CATS_ACT_PTR				cap;

	csp=BattleWorkCATS_SYS_PTRGet(bw);
	crp=BattleWorkCATS_RES_PTRGet(bw);
	pfd=BattleWorkPfdGet(bw);

	CATS_LoadResourceCharArc(csp,crp,ARC_BATT_OBJ,DTR1B_002_NCGR_BIN+trtype,1,
							 NNS_G2D_VRAM_TYPE_2DMAIN,CHARID_ENCOUNT_TRAINER1+id);
	CATS_LoadResourcePlttWorkArc(pfd,FADE_MAIN_OBJ,csp,crp,ARC_BATT_OBJ,DTR1B_002_NCLR+trtype,0,1,
								 NNS_G2D_VRAM_TYPE_2DMAIN,PLTTID_ENCOUNT_TRAINER1+id);
	CATS_LoadResourceCellArc(csp,crp,ARC_BATT_OBJ,DTR1B_002_NCER_BIN+trtype,1,
							 CELLID_ENCOUNT_TRAINER1+id);
	CATS_LoadResourceCellAnmArc(csp,crp,ARC_BATT_OBJ,DTR1B_002_NANR_BIN+trtype,1,
								CELLANMID_ENCOUNT_TRAINER1+id);

	op=EncountTrainerObjParam;
	op.id[CLACT_U_CHAR_RES]=CHARID_ENCOUNT_TRAINER1+id;
	op.id[CLACT_U_PLTT_RES]=PLTTID_ENCOUNT_TRAINER1+id;
	op.id[CLACT_U_CELL_RES]=CELLID_ENCOUNT_TRAINER1+id;
	op.id[CLACT_U_CELLANM_RES]=CELLANMID_ENCOUNT_TRAINER1+id;

	cap=CATS_ObjectAdd_S(csp,crp,&op);
	CATS_ObjectPosSetCap(cap,EncountPosTable[type][0],EncountPosTable[type][1]);
	CATS_ObjectUpdateCap(cap);

	return cap;
}

//============================================================================================
/**
 *	トレーナーキャラのCLACTリソースのロード
 *
 * @param[in]	bw		戦闘システム構造体
 * @param[in]	type	client_type
 * @param[in]	trtype	トレーナータイプ
 * @param[in]	id		CLACTリソースIDへのオフセット
 */
//============================================================================================
static	void	CT_WesCall(BATTLE_WORK *bw,CLIENT_PARAM *cp,WE_SYS_PTR wsp,WAZA_EFFECT_PARAM *wep)
{
	WES_CALL_BTL_EX_PARAM wcbep;
	int i;
	int	callID;

	/// 戦闘に渡す拡張引数
	if(wep->flag==EFFTYPE_WAZA){
		wcbep.eff_arc_id = ARC_WAZA_EFF;
		callID=wep->waza_no;
	}
	else{
		wcbep.eff_arc_id = ARC_WAZA_EFF_SUB;
		callID=wep->data;
	}
	wcbep.bgl  = BattleWorkGF_BGL_INIGet(bw);					///< BGL*
	wcbep.pfd  = BattleWorkPfdGet(bw);							///< PFD*
	wcbep.csp  = BattleWorkCATS_SYS_PTRGet(bw);					///< CSP*
	for(i = 0; i < CLIENT_MAX; i++){
		wcbep.excp[i] = BattleWorkExChrClientParamGet(bw, i);
		wcbep.mons_no[i] = wep->mons_no[i];
		wcbep.sex[i] = wep->sex[i];
		wcbep.rare[i] = wep->rare[i];
		wcbep.form_no[i] = wep->form_no[i];
		wcbep.personal_rnd[i] = wep->personal_rnd[i];
		wcbep.waza_kouka[i] = wep->waza_kouka[i];
	}
	BattleClientTypeBufMake(bw, &(wcbep.client_type[0]));			///< クライアントType
	BattleSoftSpriteBufMake(bw, &(wcbep.ss[0]));					///< ソフトスプライト
	wcbep.fight_type = BattleWorkFightTypeGet(bw);					///< ファイトタイプ取得
	wcbep.perap_voice = BattleWorkPerapVoiceGet(bw, cp->client_no);	///< ペラップ
	wcbep.bg_area = BattleWorkBGAreaGet(bw);						///< BGエリア
	wcbep.pal_area = BattleWorkPalAreaGet(bw);						///< PALエリア
	
	///< 背景データ
	wcbep.haikei_data.arc_index = ARC_BATT_BG;
	wcbep.haikei_data.chr_id	= BATTLE_BG00_NCGR_BIN + BattleWorkBGIDGet(bw);
	wcbep.haikei_data.pal_id	= BATT_BG00_D_NCLR + BattleWorkBGIDGet(bw)*3+BattleWorkTimeZoneOffsetGet(bw);
	wcbep.haikei_data.scr_id	= BATTLE_BG00_NSCR_BIN;
	wcbep.haikei_data.pal_start	= 0;
	wcbep.haikei_data.pal_num	= 8;
	
	WES_Call_Ex(wsp, wep, callID, &wcbep);
}

//============================================================================================
/**
 *	WAZA_POKE_CHANGE_PARAM構造体の生成
 *
 * @param[in]	bw			戦闘システム構造体
 * @param[in]	wep			WAZA_POKE_CHANGE_PARAM構造体を生成するためのパラメータ
 * @param[in]	wpcp		生成したWAZA_POKE_CHANGE_PARAM構造体データ格納先
 * @param[in]	client_no	生成するClientNo
 */
//============================================================================================
static	void	CT_WazaPokeChangeParamMake(BATTLE_WORK *bw,WAZA_EFFECT_PARAM *wep,WAZA_POKE_CHANGE_PARAM *wpcp,int client_no)
{
	int	i;

	wpcp->at_client_no=client_no;
	wpcp->df_client_no=client_no;

	for(i=0;i<CLIENT_MAX;i++){
		wpcp->excp[i]			=BattleWorkExChrClientParamGet(bw,i);
		wpcp->mons_no[i]		=wep->mons_no[i];
		wpcp->sex[i]			=wep->sex[i];
		wpcp->rare[i]			=wep->rare[i];
		wpcp->form_no[i]		=wep->form_no[i];
		wpcp->personal_rnd[i]	=wep->personal_rnd[i];
	}
	BattleClientTypeBufMake(bw, &(wpcp->client_type[0]));			///< クライアントType
	BattleSoftSpriteBufMake(bw, &(wpcp->ss[0]));					///< ソフトスプライト
}

//============================================================================================
/**
 *	エフェクト発動時のHPゲージと影のオンオフを制御
 *
 * @param[out]	gauge		HPゲージON/OFFフラグ
 * @param[out]	shadow		影ON/OFFフラグ
 * @param[in]	eff_type	エフェクト種類
 * @param[in]	eff_no		エフェクトナンバー
 * @param[in]	waza_no		技エフェクト時の技ナンバー
 */
//============================================================================================
static	void	CT_WazaEffectGaugeShadowOnOffCheck(u8 *gauge,u8 *shadow,int eff_type,int eff_no,u16 waza_no)
{
	if(eff_type==EFFTYPE_WAZA){
		if((WT_WazaDataParaGet(waza_no,ID_WTD_flag)&FLAG_PUT_GAUGE)==0){
			gauge[0]=1;
		}
		else{
			gauge[0]=0;
		}
		if(WT_WazaDataParaGet(waza_no,ID_WTD_flag)&FLAG_DEL_SHADOW){
			shadow[0]=1;
		}
		else{
			shadow[0]=0;
		}
	}
	else{
		switch(eff_no){
		case STATUS_WEATHER_MIST:
		case STATUS_WEATHER_RAIN:
		case STATUS_WEATHER_ICE:
		case STATUS_WEATHER_SUN:
		case STATUS_WEATHER_SAND:
		case STATUS_DAMAGE_AKUMU:
		case STATUS_DAMAGE_YADORIGI:
		case STATUS_DAMAGE_MAKITUKU:
		case STATUS_DAMAGE_HONOO:
		case STATUS_DAMAGE_KARA:
		case STATUS_DAMAGE_SUNA:
			gauge[0]=1;
			shadow[0]=0;
			break;
		case STATUS_DAMAGE_MAGUMA:
		case STATUS_DAMAGE_UZUSIO:
			gauge[0]=1;
			shadow[0]=1;
			break;
		default:
			gauge[0]=0;
			shadow[0]=0;
			break;
		}
	}
}

