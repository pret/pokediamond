
//============================================================================
/**
 *
 *@file		sub_286.s
 *@brief	戦闘シーケンス
 *			逃げる失敗シーケンス（移動ポケモン）
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_286:
	MESSAGE			EscapeNGMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
