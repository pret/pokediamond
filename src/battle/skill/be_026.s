
//============================================================================
/**
 *
 *@file		be_026.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			026　技を使用した後の２ターン中（この間は操作不可能）に受けたダメージを倍にして返す
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_026:
	IF_PSP		IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//がまん終了時は、KEEPがおちた状態で回ってくるので、それを回避
	IF			IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER,SeqWazaAfter
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_GAMAN|ADD_STATUS_ATTACK
	SEQ_END
SeqWazaAfter:
	//ATTACKメッセージは表示しない
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_ATTACK_MSG
	SEQ_END

