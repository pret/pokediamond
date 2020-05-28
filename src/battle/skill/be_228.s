//============================================================================
/**
 *
 *@file		be_228.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			228　攻撃した後、控えポケモンと入れ替わる。控えがいない場合は、入れ替え処理をしないで終了。おいうちも受ける。
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_228:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_TONBOGAERI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
