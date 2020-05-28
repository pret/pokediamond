//============================================================================
/**
 *
 *@file		be_152.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			152　まひの追加効果＋天気が「あめ」状態のときに使用すると必ず命中。
 *				「はれ」だと命中率が50％。空を飛んでいる敵に攻撃できます。
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_152:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_MAHI|ADD_STATUS_DEFENCE
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SORAWOTOBU_HIT
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
