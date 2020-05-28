
//============================================================================================
/**
 * @file	client.c
 * @bfief	戦闘クライアントプログラム
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#include "common.h"
#include "battle/battle_server.h"
#include "battle/fight.h"
#include "battle/client.h"
#include "battle/client_tool.h"
#include "battle/wazano_def.h"
#include "battle/tokusyu_def.h"
#include "battle/battle_id.h"

#include "system/window.h"

#include "communication/communication.h"

#include "client_def.h"
#include "gauge.h"
#include "client_eff.h"
#include "temoti_gauge.h"

//============================================================================================
/**
 * プロトタイプ宣言
 */
//============================================================================================

//外部公開関数群
CLIENT_PARAM	*ClientInit(BATTLE_WORK *bw,FIGHT_SYSTEM_BOOT_PARAM *fsbp);
void	ClientMain(BATTLE_WORK *battle_work,CLIENT_PARAM *client_param);
void	ClientEnd(BATTLE_WORK *bw,CLIENT_PARAM *cp,int mode);

void	ClientBMInit(BATTLE_WORK *battle_work,CLIENT_PARAM *client_param,int ballID,int sel_mons_no);

//関数ジャンプテーブル
static	void	ClientDummy(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEncountEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonEncountAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonReturn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonInhale(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerThrow(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerIn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeIn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientCommandSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientDirSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientItemSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientYesNoSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientAttackMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonBlinkSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEXPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClienKizetsuEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSePlaySet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientFadeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonVanishOnOff(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeStatusSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientModosuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEncountMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEncountKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientLevelUpEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientAlertMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPSPtoPPCopy(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerBGSlideIn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientGaugeAnimeStop(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaWasure(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientMosaicSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientFormChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBGChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSubBGWallPut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeEncountOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeResourceLoad(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeResourceDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientIncRecord(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSioWaitMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientChrPop(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSStoOAMCall(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientOAMtoSSCall(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWinLoseMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEscapeMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientGiveUpMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientMigawariChrSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaKoukaSESet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBGMPlay(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWinLoseSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBlankMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);

//外部非公開関数群
static	void	ClientCommandReset(CLIENT_PARAM *cp);

extern	const	u8	BallMoveEffectTable[];

//============================================================================================
/**
 * @param
 */
//============================================================================================
CLIENT_PARAM	*ClientInit(BATTLE_WORK *bw,FIGHT_SYSTEM_BOOT_PARAM *fsbp)
{
	CLIENT_PARAM	*cp;
	int				i;

	cp=sys_AllocMemory(HEAPID_BATTLE,sizeof(CLIENT_PARAM));
	MI_CpuClearFast(cp,sizeof(CLIENT_PARAM));

	cp->client_no=fsbp->client_no;
	cp->client_type=fsbp->client_type;

	//fight_tool.cに移動
#if 0
	//HPゲージ生成
	cp->gauge.bw = bw;
	cp->gauge.type = Gauge_TypeGet(cp->client_type, BattleWorkFightTypeGet(bw));
	Gauge_ActorResourceSet(&cp->gauge);
	Gauge_EnableSet(&cp->gauge, CATS_ENABLE_FALSE);
#endif
	
	return cp;
}

//============================================================================================
/**
 *	BM_Initを呼ぶ（最初のPOKEMON_APPEAR時にロックがかからないようにリソースを先読みしておく）
 *
 * @param	bw		戦闘システムワーク構造体
 * @param	cp		クライアントシステムワーク構造体
 * @param	ballID	セルセットするボールID
 * @param	ballID	セルセットするボールID
 */
//============================================================================================
void	ClientBMInit(BATTLE_WORK *bw,CLIENT_PARAM *cp,int ballID,int sel_mons_no)
{
	TBALL_MOVE_DATA bmd;
	s16				x,y;

	//サファリゾーン、ポケパークでは、先読みする必要なし
	if(BattleWorkFightTypeGet(bw)&(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)){
		return;
	}
	//トレーナー戦でなければ敵側の先読みする必要なし
	if((cp->client_type&CLIENT_ENEMY_FLAG)&&((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TRAINER)==0)){
		return;
	}

	bmd.type=BallMoveEffectTable[cp->client_type];
	bmd.heap_id=HEAPID_BATTLE;
	bmd.mode=EBMM_FREE;
	bmd.id=cp->client_no;
	bmd.ball_id=ballID;
	bmd.csp=BattleWorkCATS_SYS_PTRGet(bw);
	bmd.pfd=BattleWorkPfdGet(bw);
	bmd.surface = 0;
	bmd.bg_pri = BM_BG_PRI_BATTLE;

	cp->bms=BM_Init(&bmd);

	BM_BallSoftPriSet(cp->bms,100);
	BM_BallBgPriSet(cp->bms,2);
	BM_BallEnable(cp->bms,CATS_ENABLE_FALSE);
	BM_BallAnimeFlagSet(cp->bms,FALSE);
}

//============================================================================================
/**
 *	関数ジャンプテーブル
 */
//============================================================================================

static	const	clFunc	ClientFunctionTable[]={
	ClientDummy,
	ClientEncountEffect,
	ClientPokemonEncount,
	ClientPokemonEncountAppear,
	ClientPokemonAppear,
	ClientPokemonReturn,
	ClientPokemonInhale,
	ClientPokemonDelete,
	ClientTrainerEncount,
	ClientTrainerThrow,
	ClientTrainerOut,
	ClientTrainerIn,
	ClientHPGaugeIn,
	ClientHPGaugeOut,
	ClientCommandSelect,
	ClientWazaSelect,
	ClientDirSelect,
	ClientItemSelect,
	ClientPokemonSelect,
	ClientYesNoSelect,
	ClientAttackMessage,
	ClientMessage,
	ClientWazaEffect,
	ClientPokemonBlinkSet,
	ClientHPGaugeCalcSet,
	ClientEXPGaugeCalcSet,
	ClienKizetsuEffectSet,
	ClientSePlaySet,
	ClientFadeOutSet,
	ClientPokemonVanishOnOff,
	ClientHPGaugeStatusSet,
	ClientTrainerMessageSet,
	ClientModosuMessageSet,
	ClientKuridasuMessageSet,
	ClientEncountMessageSet,
	ClientEncountKuridasuMessageSet,
	ClientLevelUpEffectSet,
	ClientAlertMessageSet,
	ClientHPGaugeRefresh,
	ClientPSPtoPPCopy,
	ClientTrainerBGSlideIn,
	ClientGaugeAnimeStop,
	ClientPokemonRefresh,
	ClientWazaWasure,
	ClientMosaicSet,
	ClientFormChgSet,
	ClientBGChgSet,
	ClientSubBGWallPut,
	ClientBallGaugeEncountSet,
	ClientBallGaugeEncountOut,
	ClientBallGaugeSet,
	ClientBallGaugeOut,
	ClientBallGaugeResourceLoad,
	ClientBallGaugeResourceDelete,
	ClientIncRecord,
	ClientSioWaitMessage,
	ClientChrPop,
	ClientSStoOAMCall,
	ClientOAMtoSSCall,
	ClientWinLoseMessage,
	ClientEscapeMessage,
	ClientGiveUpMessage,
	ClientMigawariChrSet,
	ClientWazaKoukaSESet,
	ClientBGMPlay,
	ClientWinLoseSet,
	ClientBlankMessage,
};

//============================================================================================
/**
 * @param
 */
//============================================================================================
void	ClientMain(BATTLE_WORK *battle_work,CLIENT_PARAM *client_param)
{
	if(client_param->client_buffer[0]){
		ClientFunctionTable[client_param->client_buffer[0]](battle_work,client_param);
	}
}

//============================================================================================
/**
 * @param
 */
//============================================================================================
void	ClientEnd(BATTLE_WORK *bw,CLIENT_PARAM *cp,int mode)
{
	//名前入力をした後は、Gauge_ActorResourceDelを呼ぶ必要はなし
	if(mode!=BW_PROC_MODE_NAMEIN_AFTER){
		Gauge_ActorResourceDel(&cp->gauge);	//ゲージ削除
	}
	
	Poke_SinCurveStop(cp);

	sys_FreeMemoryEz(cp);
}

//============================================================================================
/**
 *	ダミー関数（関数テーブルナンバーは、1オリジンなので、ダミー関数を用意）
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientDummy(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
}

//============================================================================================
/**
 *	エンカウントエフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientEncountEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_EncountEffectSet(bw,cp);
	//エンカウントエフェクトは終了待ちの必要なし（のはず）
	SCIO_ServerQueClear(bw,cp->client_no,CL_ENCOUNT_EFFECT);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	エンカウント用のポケモンをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_ENCOUNT_PARAM	*pep=(POKEMON_ENCOUNT_PARAM *)&cp->client_buffer[0];

	CT_PokemonEncountSet(bw,cp,pep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモン出現エフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonEncountAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_APPEAR_PARAM	*pap=(POKEMON_APPEAR_PARAM *)&cp->client_buffer[0];

	CT_PokemonEncountAppearSet(bw,cp,pap);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモン出現エフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_APPEAR_PARAM	*pap=(POKEMON_APPEAR_PARAM *)&cp->client_buffer[0];

	CT_PokemonAppearSet(bw,cp,pap);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモン引っ込めるエフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonReturn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_RETURN_PARAM	*prp=(POKEMON_RETURN_PARAM *)&cp->client_buffer[0];

	CT_PokemonReturnSet(bw,cp,prp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモン吸い込むエフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonInhale(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_INHALE_PARAM	*pip=(POKEMON_INHALE_PARAM *)&cp->client_buffer[0];

	CT_PokemonInhaleSet(bw,cp,pip);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモンを削除
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	SoftSpriteDel(cp->poke_ss);
	SCIO_ServerQueClear(bw,cp->client_no,CL_POKEMON_DELETE);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	エンカウント用のトレーナーをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientTrainerEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_ENCOUNT_PARAM	*tep=(TRAINER_ENCOUNT_PARAM *)&cp->client_buffer[0];

	CT_TrainerEncountSet(bw,cp,tep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	トレーナー投げるエフェクトのセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientTrainerThrow(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_THROW_PARAM	*ttp=(TRAINER_THROW_PARAM *)&cp->client_buffer[0];

	CT_TrainerThrowSet(bw,cp,ttp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	トレーナー画面外エフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientTrainerOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_TrainerOutSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	トレーナー画面内エフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientTrainerIn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_IN_PARAM	*tip=(TRAINER_IN_PARAM *)&cp->client_buffer[0];

	CT_TrainerInSet(bw,cp,tip);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HPゲージ画面INエフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientHPGaugeIn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_IN_PARAM	*hgip=(HP_GAUGE_IN_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeInSet(bw,cp,hgip);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HPゲージ画面OUTエフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientHPGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_HPGaugeOutSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	コマンド選択を起動
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientCommandSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	COMMAND_SELECT_PARAM	*csp=(COMMAND_SELECT_PARAM *)&cp->client_buffer[0];

	//入れ替えできないClientNoをbwのメンバにセット（通信用）
	BattleWorkNoReshuffleClientSet(bw,csp->no_reshuffle_client);

	CT_CommandSelectSet(bw,cp,csp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	技選択を起動
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientWazaSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_SELECT_PARAM	*wsp=(WAZA_SELECT_PARAM *)&cp->client_buffer[0];

	CT_WazaSelectSet(bw,cp,wsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	攻撃対象選択を起動
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientDirSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	DIR_SELECT_PARAM	*dsp=(DIR_SELECT_PARAM *)&cp->client_buffer[0];

	CT_DirSelectSet(bw,cp,dsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	道具選択を起動
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientItemSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ITEM_SELECT_PARAM	*isp=(ITEM_SELECT_PARAM *)&cp->client_buffer[0];

	CT_ItemSelectSet(bw,cp,isp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモン選択を起動
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_SELECT_PARAM	*psp=(POKEMON_SELECT_PARAM *)&cp->client_buffer[0];

	CT_PokemonSelectSet(bw,cp,psp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	Yes/No選択を起動
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientYesNoSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	YES_NO_SELECT_PARAM	*ynsp=(YES_NO_SELECT_PARAM *)&cp->client_buffer[0];

	CT_YesNoSelectSet(bw,cp,ynsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	アタックメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientAttackMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ATTACK_MESSAGE_PARAM	*amp=(ATTACK_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_AttackMessageSet(bw,cp,amp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	メッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	MESSAGE_PARAM	*mp=(MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_MessageSet(bw,cp,mp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	技エフェクトを起動
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientWazaEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_EFFECT_PARAM	*wep=(WAZA_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_WazaEffectSet(bw,cp,wep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモンダメージブリンクアクションをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonBlinkSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	//バニッシュ状態の時はブリンクしない
	if(SoftSpriteParaGet(cp->poke_ss,SS_PARA_VANISH)==SW_VANISH_ON){
		SCIO_ServerQueClear(bw,cp->client_no,CL_POKEMON_BLINK);
	}
	else{
		CT_PokemonBlinkSet(bw,cp);
	}
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HPゲージ計算をセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientHPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_CALC_PARAM	*hgcp=(HP_GAUGE_CALC_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeCalcSet(bw,cp,hgcp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	EXPゲージ計算をセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientEXPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	EXP_GAUGE_CALC_PARAM	*egcp=(EXP_GAUGE_CALC_PARAM *)&cp->client_buffer[0];

	CT_EXPGaugeCalcSet(bw,cp,egcp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	気絶エフェクトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClienKizetsuEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	KIZETSU_EFFECT_PARAM	*kep=(KIZETSU_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_KizetsuEffectSet(bw,cp,kep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	指定されたSEを鳴らす
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientSePlaySet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	SE_PLAY_PARAM	*spp=(SE_PLAY_PARAM *)&cp->client_buffer[0];

	CT_SePlaySet(bw,cp,spp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	画面フェードアウトをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientFadeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_FadeOutSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモンバニッシュフラグのON/OFF
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonVanishOnOff(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_VANISH_ON_OFF	*pvoo=(POKEMON_VANISH_ON_OFF *)&cp->client_buffer[0];

	CT_PokemonVanishOnOff(bw,cp,pvoo);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HPゲージの状態異常アイコンの表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientHPGaugeStatusSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_STATUS_SET_PARAM	*hgssp=(HP_GAUGE_STATUS_SET_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeStatusSet(bw,cp,hgssp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	トレーナーメッセージの表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientTrainerMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_MESSAGE_PARAM	*tmp=(TRAINER_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_TrainerMessageSet(bw,cp,tmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	戻すメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientModosuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	MODOSU_MESSAGE_PARAM	*mmp=(MODOSU_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_ModosuMessageSet(bw,cp,mmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	繰り出すメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	KURIDASU_MESSAGE_PARAM	*kmp=(KURIDASU_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_KuridasuMessageSet(bw,cp,kmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	エンカウントメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientEncountMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_EncountMessageSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	エンカウント時の繰り出すメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientEncountKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ENCOUNT_KURIDASU_MESSAGE_PARAM	*ekmp=(ENCOUNT_KURIDASU_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_EncountKuridasuMessageSet(bw,cp,ekmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	レベルアップエフェクトを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientLevelUpEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_LevelUpEffectSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	アラートメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientAlertMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ALERT_MESSAGE_PARAM	*amp=(ALERT_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_AlertMessageSet(bw,cp,amp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HPゲージを再描画
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientHPGaugeRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_REFRESH_PARAM	*hgrp=(HP_GAUGE_REFRESH_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeRefreshSet(bw,cp,hgrp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	PSPから必要なデータをPPに書き戻す
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPSPtoPPCopy(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	PSP_TO_PP_COPY_PARAM	*ptpcp=(PSP_TO_PP_COPY_PARAM *)&cp->client_buffer[0];
	int						i;
	POKEMON_PARAM			*pp;

	pp=BattleWorkPokemonParamGet(bw,cp->client_no,ptpcp->sel_mons_no);

	//へんしん中は、HPとconditionのみ書き戻し
	if((ptpcp->condition2&CONDITION2_HENSHIN)==0){
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if((ptpcp->monomane_bit&No2Bit(i))==0){
				PokeParaPut(pp,ID_PARA_waza1+i,		(u8 *)&ptpcp->waza[i]);
				PokeParaPut(pp,ID_PARA_pp1+i,		(u8 *)&ptpcp->pp[i]);
			}
		}
		if((ptpcp->hatakiotosu&No2Bit(ptpcp->sel_mons_no))==0){
			PokeParaPut(pp,ID_PARA_item,	(u8 *)&ptpcp->item);
		}
	}

	PokeParaPut(pp,ID_PARA_hp,			(u8 *)&ptpcp->hp);
	PokeParaPut(pp,ID_PARA_condition,	(u8 *)&ptpcp->condition);

	SCIO_ServerQueClear(bw,cp->client_no,ptpcp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	タッチパネルにトレーナーBGをSlideIn
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientTrainerBGSlideIn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	u32				fight_type;
	BI_PARAM_PTR	bip;

	fight_type=BattleWorkFightTypeGet(bw);
	bip = BattleWorkGF_BGL_BIPGet(bw);

	if(cp->client_boot==CLIENT_BOOT_NORMAL){
		if((fight_type&FIGHT_TYPE_MULTI)||
		  (((fight_type&FIGHT_TYPE_MULTI)==0)&&(cp->client_type!=CLIENT_TYPE_C))){
			BINPUT_PlayerBG_ScrollX(bip, BIN_PLAYER_SCROLL_SP_X, 0);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,cp->client_buffer[0]);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ゲージのアニメーションをストップ
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientGaugeAnimeStop(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	Gauge_AnimeStop(&cp->gauge);
	Poke_SinCurveStop(cp);
	SCIO_ServerQueClear(bw,cp->client_no,cp->client_buffer[0]);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ポケモンの状態異常を直す
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientPokemonRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_REFRESH_PARAM	*prp=(POKEMON_REFRESH_PARAM *)&cp->client_buffer[0];
	POKEMON_PARAM			*pp;
	int						i,poke_count,speabi;
	u32						condition;

	condition=0;

	poke_count=BattleWorkPokeCountGet(bw,cp->client_no);

	for(i=0;i<poke_count;i++){
		pp=BattleWorkPokemonParamGet(bw,cp->client_no,i);
		if(prp->speabi==TOKUSYU_KATAYABURI){
			speabi=0;
		}
		else{
			speabi=PokeParaGet(pp,ID_PARA_speabino,NULL);
		}
		if((prp->waza_no!=WAZANO_IYASINOSUZU)||
		   ((prp->waza_no==WAZANO_IYASINOSUZU)&&(speabi!=TOKUSYU_BOUON))){
			PokeParaPut(pp,ID_PARA_condition,(u8 *)&condition);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,prp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	技忘れ処理を呼び出す
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientWazaWasure(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_WASURE_PARAM	*wwp=(WAZA_WASURE_PARAM *)&cp->client_buffer[0];

	CT_WazaWasureSet(bw,cp,wwp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ソフトウエアスプライトにモザイクをかける
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientMosaicSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	MOSAIC_SET_PARAM	*msp=(MOSAIC_SET_PARAM *)&cp->client_buffer[0];

	CT_MosaicSet(bw,cp,msp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	フォルムナンバーを変える
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientFormChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	FORM_CHG_PARAM	*fcp=(FORM_CHG_PARAM *)&cp->client_buffer[0];
	SOFT_SPRITE_ARC	ssa_src;
	SOFT_SPRITE_ARC	*ssa;
	int				pos_y;
	int				dir;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		dir=PARA_FRONT;
	}
	else{
		dir=PARA_BACK;
	}

	PokeGraArcDataGet(&ssa_src,fcp->mons_no,fcp->sex,dir,fcp->rare,fcp->form_no,fcp->personal_rnd);
	ssa=SoftSpriteArcPointerGetSS(cp->poke_ss);
	*ssa=ssa_src;
	SoftSpriteRecoverSS(cp->poke_ss);

	Ex_ChangesInto_BattlePokeData(ssa->arc_no,ssa->index_chr,HEAPID_BATTLE,
								  ExChrParamExChrBufferGet(BattleWorkExChrParamGet(bw),cp->client_no), fcp->personal_rnd, FALSE, dir, ssa->strike_mons);
	ExChrParamArcIDSet(BattleWorkExChrParamGet(bw),cp->client_no,ssa->arc_no);
	ExChrParamPalIndexSet(BattleWorkExChrParamGet(bw),cp->client_no,ssa->index_pal);

	pos_y=PokeHeightGet(fcp->mons_no,fcp->sex,dir,fcp->form_no,fcp->personal_rnd);
	ExChrParamHeightSet(BattleWorkExChrParamGet(bw),cp->client_no,pos_y);

	pos_y=CT_PokemonAppearPosGet(cp->client_type,POS_ID_Y)+pos_y;
	SoftSpriteParaSet(cp->poke_ss,SS_PARA_POS_Y,pos_y);

	SCIO_ServerQueClear(bw,cp->client_no,fcp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	地形OBJをBGに変える
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBGChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BattleWorkGroundBGChg(bw);
	SCIO_ServerQueClear(bw,cp->client_no,CL_BG_CHG);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	サブ画面の背景壁紙を表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientSubBGWallPut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	if(cp->client_boot==CLIENT_BOOT_NORMAL){
		{
			BI_PARAM_PTR	bip;
			int				partner_client;
			GAUGE_WORK		*partner_gauge;

			bip = BattleWorkGF_BGL_BIPGet(bw);

			BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
			BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);

			partner_client = BattleWorkPartnerClientNoGet(bw, cp->client_no);
			if(partner_client != cp->client_no){
				partner_gauge = BattleWorkGaugeWorkGet(bw, partner_client);
				Gauge_ColorNormalSet(partner_gauge);
			}
			Gauge_AnimeStop(&cp->gauge);
			BINPUT_StockBallOFF(bip);
			Poke_SinCurveStop(cp);
		}
	}
	SCIO_ServerQueClear(bw,cp->client_no,CL_SUBBG_WALL_PUT);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ボールゲージを表示（エンカウント時）
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBallGaugeEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	CT_BallGaugeEncountSet(bw,cp,bgp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ボールゲージを消す（エンカウント時）
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBallGaugeEncountOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	CT_BallGaugeEncountOut(bw,cp,bgp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ボールゲージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBallGaugeSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	//エンカウントじゃないボールゲージ表示は敵側のみ
	if(BattleWorkMineEnemyCheck(bw,cp->client_no)){
		CT_BallGaugeSet(bw,cp,bgp);
	}
	else{
		SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_SET);
	}
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ボールゲージを消す
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBallGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	//エンカウントじゃないボールゲージ消去は敵側のみ
	if(BattleWorkMineEnemyCheck(bw,cp->client_no)){
		CT_BallGaugeOut(bw,cp,bgp);
	}
	else{
		SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_OUT);
	}
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ボールゲージのリソースをロード
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBallGaugeResourceLoad(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CATS_SYS_PTR				csp;
	CATS_RES_PTR				crp;
	PALETTE_FADE_PTR			pfd;

	csp=BattleWorkCATS_SYS_PTRGet(bw);
	crp=BattleWorkCATS_RES_PTRGet(bw);
	pfd=BattleWorkPfdGet(bw);

	//リソースロードの関数を呼び出し
	TEMOTI_ResourceLoad(csp, crp, pfd);
	
	SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_RESOURCE_LOAD);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ボールゲージのリソースを消去
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBallGaugeResourceDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CATS_RES_PTR				crp;

	crp=BattleWorkCATS_RES_PTRGet(bw);

	//リソース消去の関数を呼び出し
	TEMOTI_ResourceFree(crp);
	
	SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_RESOURCE_DELETE);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	カウントアップワークのインクリメント
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientIncRecord(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	INC_RECORD_PARAM	*irp=(INC_RECORD_PARAM *)&cp->client_buffer[0];

	if(irp->flag==CLIENT_BOOT_TYPE_MINE){
		//自分制御のクライアントのみカウントアップ
		if(cp->client_boot==CLIENT_BOOT_NORMAL){
			BattleWorkIncRecord(bw,irp->id);
		}
	}
	else{
		//自分制御のクライアントではない時にカウントアップ
		if(cp->client_boot!=CLIENT_BOOT_NORMAL){
			BattleWorkIncRecord(bw,irp->id);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,irp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	通信待機メッセージの表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientSioWaitMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_SioWaitMessage(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	退避していたキャラの復帰
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientChrPop(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_EFFECT_PARAM	*wep=(WAZA_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_ChrPop(bw,cp,wep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	ソフトスプライトをOAMに変換
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientSStoOAMCall(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_SStoOAM(bw, cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	OAMをソフトスプライトに戻す
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientOAMtoSSCall(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_OAMtoSS(bw, cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	通信対戦時の勝敗メッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientWinLoseMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_WinLoseMessageSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	通信対戦時のにげるメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientEscapeMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ESCAPE_MESSAGE_PARAM	*emp=(ESCAPE_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_EscapeMessageSet(bw,cp,emp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	バトルタワーのリタイアメッセージを表示
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientGiveUpMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_GiveUpMessageSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	みがわりキャラをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientMigawariChrSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_EFFECT_PARAM	*wep=(WAZA_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_MigawariChrSet(bw,cp,wep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	技効果SEのセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientWazaKoukaSESet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZAKOUKA_SE_PARAM	*wsp=(WAZAKOUKA_SE_PARAM *)&cp->client_buffer[0];

	CT_WazaKoukaSESet(bw,cp,wsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	曲のセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBGMPlay(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BGM_PLAY_PARAM	*bpp=(BGM_PLAY_PARAM *)&cp->client_buffer[0];

	CT_BGMPlay(bw,cp,bpp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	win_lose_flagをセット
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientWinLoseSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WIN_LOSE_SET_PARAM	*wlsp=(WIN_LOSE_SET_PARAM *)&cp->client_buffer[0];
	POKEPARTY			*poke_party;
	POKEMON_PARAM		*pp;
	int	i;
	int	client_no;
	int	mine_hp=0;
	int	enemy_hp=0;
	u8	sio_id;

	//バトルタワーは、送られてきたwin_lose_flagをそのままセット
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TOWER){
		BattleWorkWinLoseSet(bw,wlsp->win_lose_flag);
	}
	else{
		for(client_no=0;client_no<BattleWorkClientSetMaxGet(bw);client_no++){
			poke_party=BattleWorkPokePartyGet(bw,client_no);
			for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
				pp=PokeParty_GetMemberPointer(poke_party,i);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
				   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)){
					if(BattleWorkMineEnemyCheck(bw,client_no)){
						enemy_hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
					}
					else{
						mine_hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
					}
				}
			}
		}
		if((mine_hp==0)&&(enemy_hp==0)){
			BattleWorkWinLoseSet(bw,FIGHT_DRAW);
		}
		else if(mine_hp==0){
			BattleWorkWinLoseSet(bw,FIGHT_LOSE);
		}
		else{
			BattleWorkWinLoseSet(bw,FIGHT_WIN);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,wlsp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	メッセージウインドウをクリア
 *
 * @param[in]	bw		戦闘システムワークのポインタ
 */
//============================================================================================
static	void	ClientBlankMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	GF_BGL_BMPWIN	*win=BattleWorkGF_BGL_BMPWINGet(bw,TALK_WIN_NO);

	GF_BGL_BmpWinDataFill(win,0xff);
	GF_BGL_BmpWinCgxOn(win);

	SCIO_ServerQueClear(bw,cp->client_no,CL_BLANK_MESSAGE);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	コマンド情報をリセット
 *
 * @param[in]	cp		クライアント用ワークのポインタ
 */
//============================================================================================
static	void	ClientCommandReset(CLIENT_PARAM *cp)
{
	cp->client_buffer[0]=0;
}

