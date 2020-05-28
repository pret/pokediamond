
//============================================================================
/**
 *
 *@file		sub_164.s
 *@brief	戦闘シーケンス
 *			おまじないシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_164:
	VALUE		VAL_SET,BUF_PARA_CALC_WORK,5<<OMAZINAI_SHIFT
	VALUE_WORK	VAL_BIT,BUF_PARA_SIDE_CONDITION_ATTACK,BUF_PARA_CALC_WORK
	MESSAGE		OmazinaiMineMsg,TAG_NONE_DIR,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
