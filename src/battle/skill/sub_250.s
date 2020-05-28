
//============================================================================
/**
 *
 *@file		sub_250.s
 *@brief	戦闘シーケンス
 *			おまじない終了メッセージ
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_250:
	MESSAGE		OmazinaiEndMineMsg,TAG_NONE_DIR,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
