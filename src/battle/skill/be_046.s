//============================================================================
/**
 *
 *@file		be_046.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			046　能力を下げる効果の技や追加効果を受けなくなる。
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_046:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SIROIKIRI|ADD_STATUS_WAZAKOUKA
	SEQ_END
