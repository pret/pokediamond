
//============================================================================
/**
 *
 *@file		sub_147.s
 *@brief	戦闘シーケンス
 *			技の反動シーケンス（与えたダメージの1/3）
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_147:
	//特性いしあたまは、はねかえりを受けない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_ISIATAMA,SUB_147_END
	//特性マジックガードは、はねかえりを受けない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_MAZIKKUGAADO,SUB_147_END
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//値を３分の１に
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_HIT_DAMAGE
	//すでにダメージ量が0なら、計算しないで0のままにする
	IF				IF_FLAG_EQ,BUF_PARA_HP_CALC_WORK,0,SUB_147_NEXT
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,3
SUB_147_NEXT:
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			HanekaeriMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_147_END:
	SEQ_END
