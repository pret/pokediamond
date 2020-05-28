
//============================================================================
/**
 *
 *@file		sub_061.s
 *@brief	戦闘シーケンス
 *			技が外れた時のペナルティ処理
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_061:
	//特性マジックガードは、ダメージを受けない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_MAZIKKUGAADO,SUB_061_END
	IF				IF_FLAG_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NOHIT_PENALTY,SUB_061_END
	MESSAGE			TobigeriMissMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ダメージを半分に
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_DAMAGE
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//相手のHPMAXをゲット
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_hpmax,BUF_PARA_TEMP_WORK
	VALUE			VAL_MUL,BUF_PARA_TEMP_WORK,-1
	//HPMAXを半分に
	DAMAGE_DIV		BUF_PARA_TEMP_WORK,2
	//もし、ダメージ量が相手のHPMAXの1/2より大きい場合は、HPMAXの1/2に補正
	IF_WORK			IF_FLAG_NC,BUF_PARA_TEMP_WORK,BUF_PARA_HP_CALC_WORK,SUB_061_NEXT
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_TEMP_WORK
SUB_061_NEXT:
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP計算サブルーチンへ
	GOSUB			SUB_SEQ_HP_CALC
SUB_061_END:
	SEQ_END
