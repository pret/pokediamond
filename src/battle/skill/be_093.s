//============================================================================
/**
 *
 *@file		be_093.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			093　自分のタイプを相手が使ってきた技の抵抗力に変える
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_093:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TEXTURE2|ADD_STATUS_WAZAKOUKA
	SEQ_END
