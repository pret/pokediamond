
//============================================================================
/**
 *
 *@file		sub_285.s
 *@brief	戦闘シーケンス
 *			特性プレッシャー発動メッセージ
 *@author	HisashiSogabe
 *@data		2006.07.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_285:
	MESSAGE			PressureMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
