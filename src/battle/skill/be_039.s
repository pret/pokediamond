//============================================================================
/**
 *
 *@file		be_039.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			039 １ターン溜めて２ターン目で攻撃する
 *
 *@author	HisashiSogabe
 *@data		2005.11.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_039:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//2体に当たるときは、KEEPがおちた状態で回ってくるので、それを回避
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER,SeqWazaAfter
	//装備効果で溜めなくていい効果を持っているときは、技を発動
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_039_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_039_NEXT:
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//攻撃対象がいない時は、なにもしない
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_039_END
SeqWazaAfter:
	//急所に当たりやすくする
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
BE_039_END:
	//ため後の処理をまとめたサブルーチンをコール
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
