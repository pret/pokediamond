//============================================================================
/**
 *
 *@file		be_116.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			116　そのターンに敵から戦闘不能になるような攻撃を受けてもＨＰが必ず１残る。連続で出すと成功率が下がっていく
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_116:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_GUARD|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
