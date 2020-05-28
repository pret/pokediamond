//============================================================================
/**
 *
 *@file		be_269.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			269　敵に与えたダメージの２分の１を自分が受ける
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_269:
	//特性すてみは、反動ダメージ系を受ける技の威力を2割増しする
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_269_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_269_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HANEKAERI3|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
