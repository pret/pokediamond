//============================================================================
/**
 *
 *@file		be_025.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			025　敵と自分のポケモンのステータス（のうりょく）の異常を元に戻す
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_025:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_KUROIKIRI|ADD_STATUS_WAZAKOUKA
	SEQ_END
