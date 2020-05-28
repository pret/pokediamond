//============================================================================
/**
 *
 *@file		be_034.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			034　戦闘終了後に使用したポケモンのレベル×攻撃回数×5のお金が手に入る
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_034:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_NEKONIKOBAN|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
