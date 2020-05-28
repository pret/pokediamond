//============================================================================
/**
 *
 *@file		be_023.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			023　敵ポケモンの「命中率」を１段階下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_023:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HITDOWN|ADD_STATUS_DEFENCE
	SEQ_END
