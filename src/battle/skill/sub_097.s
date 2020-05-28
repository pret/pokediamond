
//============================================================================
/**
 *
 *@file		sub_097.s
 *@brief	戦闘シーケンス
 *			のろい（ゴースト）追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_097:
	//消えで外れた場合は、うまくきまらん
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_KIE_NOHIT,Umakukimaran
	//みがわりがいた場合は、うまくきまらん
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//すでにのろっている時は、うまくきまらん
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_NOROI,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_NOROI
	//自分のHPMAXの半分をダメージにする
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			NoroiM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
