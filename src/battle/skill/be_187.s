//============================================================================
/**
 *
 *@file		be_187.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			187　使用した次のターン終了時、使用した対象が場に残っていたならば、その対象は眠り状態になる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_187:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AKUBI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
