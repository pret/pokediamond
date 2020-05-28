//============================================================================
/**
 *
 *@file		be_113.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			113　敵の回避率を、元に戻す。ゴーストタイプのポケモンにノーマルタイプ、かくとうタイプの攻撃が当たるようになる。
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_113:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MIYABURU|ADD_STATUS_WAZAKOUKA
	//タイプを無属性にする
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	SEQ_END
