//============================================================================
/**
 *
 *@file		be_158.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			158　先制攻撃で相手がひるむ　出てきた最初のターンにしか成功しない
 *
 *@author	HisashiSogabe
 *@data		2006.02.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_158:
	//最初のターンかどうか調べる
	IF_PSP_WORK		IF_FLAG_NE,SIDE_ATTACK,ID_PSP_wkw_nekodamashi_count,BUF_PARA_TOTAL_TURN,Umakukimaran
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
