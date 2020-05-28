//============================================================================
/**
 *
 *@file		be_188.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			188　対象が所持道具を持っていない状態にします。戦闘終了後道具は元に戻る。
 *				（この状態の時にぬすむを使用しても必ず失敗する）
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_188:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HATAKIOTOSU|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
