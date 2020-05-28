
//============================================================================
/**
 *
 *@file		sub_024.s
 *@brief	戦闘シーケンス
 *			HP吸い取りシーケンス
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_024:
	//ダメージ量を半分に
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_HIT_DAMAGE
	//すでにダメージ量が0なら、計算しないで0のままにする
	IF				IF_FLAG_EQ,BUF_PARA_HP_CALC_WORK,0,SUITORI_0
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
SUITORI_0:
	//装備効果で吸い取る系の威力アップは、威力アップ
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_ATTACK,SOUBI_KYUSYUURYOKUUP,SUB_024_NEXT
	SOUBI_ATK_GET	SIDE_ATTACK,BUF_PARA_CALC_WORK
	VALUE			VAL_ADD,BUF_PARA_CALC_WORK,100
	VALUE_WORK		VAL_MUL,BUF_PARA_HP_CALC_WORK,BUF_PARA_CALC_WORK
	VALUE			VAL_DIV,BUF_PARA_HP_CALC_WORK,100
SUB_024_NEXT:
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//ヘドロえきをもっている相手からは、ダメージ
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_DEFENCE,TOKUSYU_HEDOROEKI,Hedoroeki
Normal:
	//ヒールブロックを受けている時は回復動作なし
	IF_PSP			IF_FLAG_NE,SIDE_ATTACK,ID_PSP_wkw_healblock_count,0,Healblock
	//半分回復のために符号反転
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			SuckMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
Healblock:
	VALUE			VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KAIHUKUHUUZI
	MESSAGE			HealblockRecoverNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Hedoroeki:
	//マジックガードをもっている場合はヘドロダメージなし
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_MAZIKKUGAADO,SUB_024_END
	//半分ダメージ
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			HedoroekiMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_024_END:
	SEQ_END
