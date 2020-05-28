//==============================================================================
/**
 * @file	client_eff.c
 * @brief	クライアント系のエフェクト動作
 * @author	matsuda
 * @date	2006.04.11(火)
 */
//==============================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/gamedata.h"

#include "battle/battle_server.h"
#include "battle/client.h"
#include "battle/fight.h"
#include "battle/fight_tool.h"
#include "battle/server_tool.h"
#include "battle/ground.h"
#include "battle/scio.h"

#include "poketool/poke_tool.h"
#include "poketool/tr_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"

#include "gflib/touchpanel.h"

#include "itemtool/itemsym.h"
#include "itemtool/myitem.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/snd_tool.h"
#include "system/softsprite.h"
#include "system/gra_tool.h"

#include "wazaeffect/we_sys.h"

#include "client_def.h"
#include "client_tool_def.h"

#include "b_plist.h"
#include "b_bag.h"
#include "gauge.h"
#include "battle/battle_tcb_pri.h"
#include "system/pm_str.h"
#include "system/msg_ds_icon.h"

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

#include "battle_snd_def.h"

#include "client_eff.h"



//==============================================================================
//	定数定義
//==============================================================================
///ゲージSinカーブの秒加算値
#define POKEYURE_SIN_SEC_ADD		(20)
///ゲージSinカーブのふり幅Y(fx32)
#define POKEYURE_SIN_FURIHABA_Y		(0x1800)	//(2 << FX32_SHIFT)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void PokeSinCurveMain(TCB_PTR tcb, void *work);


//==============================================================================
//	選択中のポケモンの揺れ
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ポケモンのSinカーブエフェクトをセットする
 * @param   cp		クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
void Poke_SinCurveSet(CLIENT_PARAM *cp, BATTLE_WORK *bw)
{
	if(cp->sin_tcb != NULL){
		return;
	}
	if(BattleWorkFightTypeGet(bw) & (FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)){
		return;
	}
	cp->sin_sec = 180;
	cp->sin_tcb = TCB_Add(PokeSinCurveMain, cp, TCBPRI_HP_POKEYURE_SIN_CURVE);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンのSinカーブエフェクトを停止させる
 * @param   cp		クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
void Poke_SinCurveStop(CLIENT_PARAM *cp)
{
	if(cp->sin_tcb == NULL){
		return;
	}

	TCB_Delete(cp->sin_tcb);
	cp->sin_tcb = NULL;

	cp->sin_sec = 0;
	SoftSpriteParaSet(cp->poke_ss, SS_PARA_POS_OY, 0);
}

//--------------------------------------------------------------
/**
 * @brief   ポケモンのSinカーブメイン動作
 * @param   tcb			TCBへのポインタ
 * @param   cp			クライアント用パラメータワーク構造体
 */
//--------------------------------------------------------------
static void PokeSinCurveMain(TCB_PTR tcb, void *work)
{
	CLIENT_PARAM *cp = work;
	int offset_y;
	
	cp->sin_sec += POKEYURE_SIN_SEC_ADD;
	if(cp->sin_sec >= 360){
		cp->sin_sec -= 360;
	}
	
	offset_y = FX_Mul(Sin360(cp->sin_sec), POKEYURE_SIN_FURIHABA_Y) / FX32_ONE;
	SoftSpriteParaSet(cp->poke_ss, SS_PARA_POS_OY, offset_y);//MATH_ABS(offset_y));
}

