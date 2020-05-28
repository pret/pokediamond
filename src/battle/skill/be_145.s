//============================================================================
/**
 *
 *@file		be_145.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			145　１ターン溜めて２ターンめで攻撃する、１ターンめに使用したポケモンの「ぼうぎょ」が１段階上がる
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_145:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//装備効果で溜めなくていい効果を持っているときは、技を発動
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_145_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_DEFUP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_145_NEXT:
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN_ROCKET
	//攻撃対象がいない時は、なにもしない
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_145_END
SeqWazaAfter:
	CRITICAL_CHECK
	DAMAGE_CALC
BE_145_END:
	//ため後の処理をまとめたサブルーチンをコール
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
