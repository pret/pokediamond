//============================================================================
/**
 *
 *@file		be_035.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			035　５ターンの間、敵の特殊攻撃のダメージを半減させる、使用したポケモンが交代してもターン分は効果が受け継がれる
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_035:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HIKARINOKABE|ADD_STATUS_WAZAKOUKA
	SEQ_END
