
//============================================================================
/**
 *
 *@file		be_086.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			086　相手が直前に出した技を数ターン使えなくする（変身の変更を忘れずに）
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_086:
	VALUE	VAL_BIT,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KANASIBARI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
