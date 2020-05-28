//============================================================================
/**
 *
 *@file		be_248.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			248　先制技。対象ポケモンの技が攻撃技ならば、相手に大ダメージ。攻撃技でない場合失敗する。
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_248:
	HUIUCHI			Umakukimaran
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
