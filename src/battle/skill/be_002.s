//============================================================================
/**
 *
 *@file		be_002.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			002　毒の追加効果
 *
 *@author	HisashiSogabe
 *@data		2005.12.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_002:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_DOKU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
