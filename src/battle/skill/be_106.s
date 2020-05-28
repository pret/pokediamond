//============================================================================
/**
 *
 *@file		be_106.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			106　敵を逃げられなくする。トレーナー戦ではいれかえができなくなる
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_106:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KUROIMANAZASHI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
