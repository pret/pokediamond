//============================================================================
/**
 *
 *@file		be_081.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			081　技を出した時、敵の攻撃が当たると技の威力が上がる
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_081:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_IKARI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
