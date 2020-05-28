//============================================================================
/**
 *
 *@file		be_224.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			224　相手が木の実を持っているとき、攻撃すると自分に木の実の効果を発揮させる。
 *				 ダメージ処理後、木の実をチェックして実行。別シート【道具追加技】の参照。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_224:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_TSUIBAMU|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
