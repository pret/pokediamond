
//============================================================================
/**
 *
 *@file		sub_120.s
 *@brief	戦闘シーケンス
 *			はらだいこシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_120:
	//すでに攻撃力がMAXの時はうまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_abiritycnt_pow,12,Umakukimaran
	//HPMAXを取得して半分にする
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//現在HPがHPMAXの半分ない時はうまくきまらん
	IF_PSP_WORK		IF_FLAG_NC,SIDE_ATTACK,ID_PSP_hp,BUF_PARA_HP_CALC_WORK,Umakukimaran

	GOSUB			SUB_SEQ_WAZA_OUT_EFF

	//攻撃をMAX
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_abiritycnt_pow,12
	//HPをHPMAXの半分量減らす
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	//AttackClientをHP操作対象に
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP計算サブルーチンへ
	GOSUB			SUB_SEQ_HP_CALC

	STATUS_EFFECT	SIDE_ATTACK,STATUS_EFF_UP
	SERVER_WAIT
	MESSAGE			HaradaikoMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

