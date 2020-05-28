
//============================================================================================
/**
 * @file	client_tool.h
 * @bfief	戦闘クライアント用ツールプログラム
 * @author	HisashiSogabe
 * @date	05.07.21
 */
//============================================================================================

#ifndef __CLIENT_TOOL_H_
#define __CLIENT_TOOL_H_

#include	"battle/scio.h"
#include	"system/softsprite.h"
#include	"gauge.h"
#include 	"client_types.h"

extern	void		CT_EncountEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_PokemonEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_ENCOUNT_PARAM *pep);
extern	void		CT_PokemonEncountAppearSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_APPEAR_PARAM *pap);
extern	void		CT_PokemonAppearSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_APPEAR_PARAM *pap);
extern	void		CT_PokemonReturnSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_RETURN_PARAM *prp);
extern	void		CT_PokemonInhaleSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_INHALE_PARAM *prp);
extern	void		CT_TrainerEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_ENCOUNT_PARAM *tep);
extern	void		CT_TrainerThrowSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_THROW_PARAM *ttp);
extern	void		CT_TrainerOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_TrainerInSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_IN_PARAM *tip);
extern	void		CT_HPGaugeInSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_IN_PARAM *hgip);
extern	void		CT_HPGaugeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_CommandSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,COMMAND_SELECT_PARAM *csp);
extern	void		CT_WazaSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_SELECT_PARAM *wsp);
extern	void		CT_DirSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,DIR_SELECT_PARAM *dsp);
extern	void		CT_ItemSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ITEM_SELECT_PARAM *isp);
extern	void		CT_PokemonSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_SELECT_PARAM *psp);
extern	void		CT_YesNoSelectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,YES_NO_SELECT_PARAM *ynsp);
extern	void		CT_AttackMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ATTACK_MESSAGE_PARAM *amp);
extern	void		CT_MessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MESSAGE_PARAM *amp);
extern	void		CT_WazaEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep);
extern	void		CT_PokemonBlinkSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_HPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_CALC_PARAM *hgcp);
extern	void		CT_EXPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,EXP_GAUGE_CALC_PARAM *egcp);
extern	void		CT_KizetsuEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,KIZETSU_EFFECT_PARAM *kep);
extern	void		CT_SePlaySet(BATTLE_WORK *bw,CLIENT_PARAM *cp,SE_PLAY_PARAM *spp);
extern	void		CT_FadeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_PokemonVanishOnOff(BATTLE_WORK *bw,CLIENT_PARAM *cp,POKEMON_VANISH_ON_OFF *pvoo);
extern	void		CT_HPGaugeStatusSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_STATUS_SET_PARAM *hgssp);
extern	void		CT_TrainerMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,TRAINER_MESSAGE_PARAM *tmp);
extern	void		CT_ModosuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MODOSU_MESSAGE_PARAM *mmp);
extern	void		CT_KuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,KURIDASU_MESSAGE_PARAM *kmp);
extern	void		CT_EncountMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_EncountKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ENCOUNT_KURIDASU_MESSAGE_PARAM *ekmp);
extern	void		CT_LevelUpEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_AlertMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ALERT_MESSAGE_PARAM *amp);
extern	void		CT_HPGaugeRefreshSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,HP_GAUGE_REFRESH_PARAM *hgrp);
extern	void		CT_WazaWasureSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_WASURE_PARAM *wwp);
extern	void		CT_MosaicSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,MOSAIC_SET_PARAM *msp);
extern	void		CT_BallGaugeEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
extern	void		CT_BallGaugeEncountOut(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
extern	void		CT_BallGaugeSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
extern	void		CT_BallGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp,BALL_GAUGE_PARAM *bgp);
extern	void		CT_SioWaitMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_ChrPop(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep);
extern	void		CT_SStoOAM(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_OAMtoSS(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_WinLoseMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_EscapeMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,ESCAPE_MESSAGE_PARAM *emp);
extern	void		CT_GiveUpMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	void		CT_MigawariChrSet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZA_EFFECT_PARAM *wep);
extern	void		CT_WazaKoukaSESet(BATTLE_WORK *bw,CLIENT_PARAM *cp,WAZAKOUKA_SE_PARAM *wsp);
extern	void		CT_BGMPlay(BATTLE_WORK *bw,CLIENT_PARAM *cp,BGM_PLAY_PARAM *bpp);

extern	void		CT_UISet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
extern	u8			CT_CPClientTypeGet(CLIENT_PARAM *cp);
extern	u8			CT_CPClientBootGet(CLIENT_PARAM *cp);
extern	SOFT_SPRITE	*CT_CPSoftSpriteGet(CLIENT_PARAM *cp);
extern	GAUGE_WORK	*CT_CPGaugeWorkGet(CLIENT_PARAM *cp);
extern	CURSOR_SAVE *CT_CursorSavePtrGet(CLIENT_PARAM *cp);
extern	void		CT_CursorSaveClear(CLIENT_PARAM *cp);
extern	s16			CT_PokemonAppearPosGet(int client_type,int pos_id);

#endif __CLIENT_TOOL_H_
