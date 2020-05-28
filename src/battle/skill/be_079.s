//============================================================================
/**
 *
 *@file		be_079.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			079　ＨＰの最大値の４分の１を使って自分の分身を作る（変身の変更を忘れずに）
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_079:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MIGAWARI|ADD_STATUS_WAZAKOUKA
	SEQ_END
