//============================================================================
/**
 *
 *@file		be_239.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			239　相手の特性を無効にする。必ず失敗する特性を用意する必要があるかも。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_239:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_IEKI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
