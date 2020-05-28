
//============================================================================
/**
 *
 *@file		sub_050.s
 *@brief	戦闘シーケンス
 *			効果切れシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_050:
	MESSAGE_DIR		SIDE_WORK,WazaKoukaEndMineMsg,TAG_WAZA,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
