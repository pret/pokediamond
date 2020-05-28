//============================================================================
/**
 *
 *@file		be_254.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			254　攻撃後、自分の最大ＨＰの４分の１を自分が受ける
 *
 *@author	HisashiSogabe
 *@data		2005.12.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_254:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_WARUAGAKI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
