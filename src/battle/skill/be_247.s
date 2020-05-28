//============================================================================
/**
 *
 *@file		be_247.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			247　相手の特性を【ふみん】にかえる。【なまけ】にはきかない。
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_247:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NAYAMINOTANE|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
