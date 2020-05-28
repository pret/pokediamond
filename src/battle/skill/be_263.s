//============================================================================
/**
 *
 *@file		be_263.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			263　１ターン溜めて２ターンめで攻撃する＋「そらをとぶ」状態にする＋「まひ」の追加効果
 *
 *@author	HisashiSogabe
 *@data		2006.04.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_263:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//装備効果で溜めなくていい効果を持っているときは、技を発動
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_263_NEXT
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_263_NEXT:
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka_temp,WAZAKOUKA_SORAWOTOBU
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//これが必要かは微妙
	VANISH_ON_OFF	SIDE_ATTACK,SW_VANISH_ON
	//攻撃対象がいない時は、なにもしない
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_263_END
SeqWazaAfter:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_MAHI|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
BE_263_END:
	//姿を消す系のため技のフラグを落とす
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_KIE
	//ため後の処理をまとめたサブルーチンをコール
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
