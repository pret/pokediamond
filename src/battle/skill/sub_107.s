
//============================================================================
/**
 *
 *@file		sub_107.s
 *@brief	戦闘シーケンス
 *			メロメロ継続中シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_107:
	MESSAGE			MeromeroM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_MEROMERO
	SERVER_WAIT
	SEQ_END
