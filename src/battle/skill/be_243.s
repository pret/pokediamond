//============================================================================
/**
 *
 *@file		be_243.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			243　相手の攻撃と特攻のアップ状態（上昇・下降どちらも）と自分の状態をいれかえる。
 *				 特性クリアボディやしろいきりの敵にも無常件で入れ替える。
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_243:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_POWER_SWAP|ADD_STATUS_WAZAKOUKA
	SEQ_END
