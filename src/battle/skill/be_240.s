//============================================================================
/**
 *
 *@file		be_240.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			240　相手の攻撃が急所にあたらなくなる。場にいる間有効。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_240:
	IF			IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_ATTACK,SIDE_CONDITION_OMAZINAI,Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_OMAZINAI|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
