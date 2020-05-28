//============================================================================
/**
 *
 *@file		be_262.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			262　敵に与えたダメージの３分の１を自分が受ける＋追加効果でまひになる
 *
 *@author	HisashiSogabe
 *@data		2006.04.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_262:
	//特性すてみは、反動ダメージ系を受ける技の威力を2割増しする
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_262_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_262_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_VOLT|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_PROB
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
