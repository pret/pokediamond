//============================================================================
/**
 *
 *@file		be_177.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			177　相手のどうぐと自分のどうぐを入れ替える
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_177:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TRICK|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
