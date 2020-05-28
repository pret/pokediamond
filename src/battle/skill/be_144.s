//============================================================================
/**
 *
 *@file		be_144.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			144　敵の特殊攻撃のダメージを倍にして返す（「すばやさ」に関係なく必ず後攻になる）
 *			
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_144:
	//タイプ補正計算を無視する
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	MIRROR_CORT
	SEQ_END
