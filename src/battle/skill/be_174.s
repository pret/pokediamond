//============================================================================
/**
 *
 *@file		be_174.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			174　次に出す電気の技の威力が２倍になる。特殊防御力を１段階上げる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_174:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_JUUDEN|ADD_STATUS_WAZAKOUKA
	SEQ_END
