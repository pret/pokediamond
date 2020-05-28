//============================================================================
/**
 *
 *@file		be_003.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			003　敵に与えたダメージの半分の数値だけＨＰが回復する
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_003:
	//技効果を追加してシーケンスを発動
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SUITORI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
