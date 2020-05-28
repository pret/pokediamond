
//============================================================================
/**
 *
 *@file		sub_033.s
 *@brief	戦闘シーケンス
 *			ゆめくいシーケンス
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_033:
	//ヒールブロックを受けている時は回復動作なし
	IF_PSP			IF_FLAG_NE,SIDE_ATTACK,ID_PSP_wkw_healblock_count,0,Healblock
	//ダメージ量を半分に
	VALUE_WORK	VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_HIT_DAMAGE
	//すでにダメージ量が0なら、計算しないで0のままにする
	IF				IF_FLAG_EQ,BUF_PARA_HP_CALC_WORK,0,SUB_033_NEXT
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//装備効果で吸い取る系の威力アップは、威力アップ
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_ATTACK,SOUBI_KYUSYUURYOKUUP,SUB_033_NEXT
	SOUBI_ATK_GET	SIDE_ATTACK,BUF_PARA_CALC_WORK
	VALUE			VAL_ADD,BUF_PARA_CALC_WORK,100
	VALUE_WORK		VAL_MUL,BUF_PARA_HP_CALC_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_DIV,BUF_PARA_HP_CALC_WORK,100
SUB_033_NEXT:
	//HP操作対象をAttackClientに
	VALUE_WORK	VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//半分回復のために符号反転
	VALUE		VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	GOSUB		SUB_SEQ_HP_CALC
	MESSAGE		YumekuiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
SUB_033_END:
	SEQ_END

Healblock:
	VALUE		VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KAIHUKUHUUZI
	MESSAGE		HealblockRecoverNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
