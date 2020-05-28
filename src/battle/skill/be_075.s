//============================================================================
/**
 *
 *@file		be_075.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			075　１ターン溜めて２ターンめで攻撃する。ひるむの追加効果。急所に当たりやすい。
 *
 *@author	HisashiSogabe
 *@data		2005.12.21
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_075:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//装備効果で溜めなくていい効果を持っているときは、技を発動
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_075_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_075_NEXT:
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//攻撃対象がいない時は、なにもしない
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_075_END
SeqWazaAfter:
	//クリティカルヒットを出しやすくする
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
	//ひるむ追加効果をセット
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
BE_075_END:
	//ため後の処理をまとめたサブルーチンをコール
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
