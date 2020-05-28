//============================================================================
/**
 *
 *@file		be_118.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			118　敵を「こんらん」状態にするが、かわりに「こうげき」を２段階上げてしまう
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_118:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_IBARU|ADD_STATUS_WAZAKOUKA|ADD_STATUS_DEFENCE
	SEQ_END
