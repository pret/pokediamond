//============================================================================
/**
 *
 *@file		be_216.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			216　対象のポケモンの回避率を元に戻す。あくタイプのポケモンに、エスパータイプの攻撃が当たるようになる。
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_216:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MIRACLE_EYE|ADD_STATUS_WAZAKOUKA
	//タイプを無属性にする
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	SEQ_END
