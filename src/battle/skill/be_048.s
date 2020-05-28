//============================================================================
/**
 *
 *@file		be_048.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			048　敵に与えたダメージの４分の１を自分が受ける
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_048:
	//特性すてみは、反動ダメージ系を受ける技の威力を2割増しする
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_048_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_048_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HANEKAERI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
