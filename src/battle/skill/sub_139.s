
//============================================================================
/**
 *
 *@file		sub_139.s
 *@brief	戦闘シーケンス
 *			マジックコート発動シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_139:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE			MagicCortGuardMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	MAGIC_CORT_A_D
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	SEQ_END
