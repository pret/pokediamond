//============================================================================
/**
 *
 *@file		be_253.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			253　敵に与えたダメージの３分の１を自分が受ける＋追加効果でやけどになる＋こおり状態がとける。
 *				 自分がこおり状態でも技が出せる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_253:
	//特性すてみは、反動ダメージ系を受ける技の威力を2割増しする
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_253_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_253_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HEAT_ATTACK|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_PROB
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
