
//============================================================================
/**
 *
 *@file		sub_108.s
 *@brief	戦闘シーケンス
 *			メロメロで技を出すのに失敗シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_108:
	GOSUB		SUB_SEQ_MEROMERO_KEEP
	MESSAGE		MeromeroNoWazaMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//ため系フラグを落とす
	KEEP_OFF	SIDE_ATTACK
	SEQ_END
