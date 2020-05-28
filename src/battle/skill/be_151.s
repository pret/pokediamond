//============================================================================
/**
 *
 *@file		be_151.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			151　１ターン溜めて２ターンめで攻撃する＋天気が「はれ」状態の時は溜めないで攻撃が出来る。
 *				「あめ」の場合は威力が半減。 
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_151:
	//天候無効系の特性は、天候チェックを無視
	NOOTENKI_CHECK	SeqWazaBefore
	//天候が晴れ状態の時は、ためをすることなく技を発動
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SeqWazaAfter
SeqWazaBefore:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//装備効果で溜めなくていい効果を持っているときは、技を発動
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_151_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_151_NEXT:
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//攻撃対象がいない時は、なにもしない
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_151_END
SeqWazaAfter:
	CRITICAL_CHECK
	DAMAGE_CALC
BE_151_END:
	//ため後の処理をまとめたサブルーチンをコール
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
