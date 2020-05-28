//============================================================================
/**
 *
 *@file		be_160.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			160　自分の特殊防御を１段階上げる。３回までたくわえることができる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_160:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TAKUWAERU|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	SEQ_END
