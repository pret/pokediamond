
//============================================================================
/**
 *
 *@file		sub_100.s
 *@brief	戦闘シーケンス
 *			みやぶる追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_100:
	PSP_VALUE	VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_MIYABURU
	MESSAGE		MiyaburuM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
