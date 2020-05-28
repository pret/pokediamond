
//============================================================================
/**
 *
 *@file		sub_251.s
 *@brief	戦闘シーケンス
 *			トリックルーム終了メッセージ
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_251:
	MESSAGE_NO_DIR	TrickRoomEndMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
