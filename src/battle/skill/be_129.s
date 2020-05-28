//============================================================================
/**
 *
 *@file		be_129.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			129　「しめつけ」「まきつき」等の連続技から抜け出すことが出来る。「やどりぎのタネ」「まきびし」からも解放される
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_129:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_KOUSOKUSPIN|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
