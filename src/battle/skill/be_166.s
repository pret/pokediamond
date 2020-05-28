//============================================================================
/**
 *
 *@file		be_166.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			166　相手の特殊攻撃を１段階あげて混乱状態にする
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_166:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ODATERU|ADD_STATUS_WAZAKOUKA|ADD_STATUS_DEFENCE
	SEQ_END
