//============================================================================
/**
 *
 *@file		be_214.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			214　ＨＰが半分回復するが、そのターンは地面技が１倍で当たる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_214:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HANEYASUME|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	SEQ_END
