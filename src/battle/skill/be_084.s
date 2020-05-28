//============================================================================
/**
 *
 *@file		be_084.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			084　毎ターン敵のからＨＰを奪い、奪った数値分のＨＰが回復する（技をかけたポケモンがいなくなっても、効果は持続する）
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_084:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_YADORIGI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
