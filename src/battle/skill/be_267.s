//============================================================================
/**
 *
 *@file		be_267.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			267　録音した音量で混乱確率が変わる。
 *				 ランク１＝0％、ランク２＝10％、ランク３＝30％。音データがない、ぺラップ以外はランク１扱い。
 *
 *@author	HisashiSogabe
 *@data		2006.05.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_267:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_OSYABERI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
