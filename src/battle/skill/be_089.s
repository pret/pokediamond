//============================================================================
/**
 *
 *@file		be_089.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			089　敵の物理攻撃のダメージを倍にして返す（「すばやさ」に関係なく必ず後攻になる）
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_089:
	//タイプ補正計算を無視する
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	COUNTER
	SEQ_END
