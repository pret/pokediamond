//============================================================================
/**
 *
 *@file		be_090.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			090　敵が最後に使用した技を、２～６回繰り返し出させる
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_090:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ENCORE|ADD_STATUS_WAZAKOUKA
	SEQ_END
