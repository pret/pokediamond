//============================================================================
/**
 *
 *@file		be_223.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			223　「まもる」「みきり」をしている相手にのみ攻撃が当たり、まもる効果を解除する。
 *				 相手は、まもるは解除されるが内部的には成功したことになる。まもる作動後にフェイントの動作を実行。
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_223:
	FEINT			Umakukimaran
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_FEINT|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
