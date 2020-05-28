//============================================================================
/**
 *
 *@file		be_057.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			057　対象の相手と同じ姿になる、技も敵と同じ技を使える（ＰＰは全て５）
 *
 *@author	HisashiSogabe
 *@data		2006.01.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_057:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HENSIN|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
