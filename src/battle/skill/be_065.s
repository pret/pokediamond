//============================================================================
/**
 *
 *@file		be_065.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			065　５ターンの間、敵の物理攻撃のダメージを半減させる、使用したポケモンが交代してもターン分は効果が受け継がれる
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_065:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_RIHUREKUTAA|ADD_STATUS_WAZAKOUKA
	SEQ_END
