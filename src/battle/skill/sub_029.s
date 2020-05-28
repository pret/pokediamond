
//============================================================================
/**
 *
 *@file		sub_029.s
 *@brief	戦闘シーケンス
 *			こおり状態が溶けたシーケンス
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_029:
	//こおりフラグを落とす
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_condition,CONDITION_KOORI
	MESSAGE		MeltMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	STATUS_SET	SIDE_WORK,STATUS_NORMAL
	WAIT		MSG_WAIT
	SEQ_END
