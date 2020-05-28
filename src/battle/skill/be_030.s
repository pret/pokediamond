//============================================================================
/**
 *
 *@file		be_030.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			030　自分のもっている技のどれかのタイプに自分のタイプを変える
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_030:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TEXTURE|ADD_STATUS_WAZAKOUKA
	SEQ_END
