//============================================================================
/**
 *
 *@file		be_102.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			102　味方ポケモン全てのステータス異常を回復する
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_102:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_IYASINOSUZU|ADD_STATUS_WAZAKOUKA
	SEQ_END
