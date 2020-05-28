//============================================================================
/**
 *
 *@file		be_120.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			120　オスならメスに、メスならオスに１／２の確率で攻撃が出来ない状態になる
 *
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_120:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MEROMERO|ADD_STATUS_DEFENCE
	//追加するClientにAttackClientをセット
	VALUE_WORK	VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	SEQ_END
