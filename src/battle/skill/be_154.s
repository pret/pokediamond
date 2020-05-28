//============================================================================
/**
 *
 *@file		be_154.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			154　仲間のポケモンの数（自分も入れて最大６回）だけ敵を攻撃する、
 *				 戦闘不能や特殊状態（どく、ねむり等）のポケモンは数にいれない
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_154:
	//タイプを無属性にする
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	CRITICAL_CHECK
	HUKURODATAKI
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HUKURODATAKI|ADD_STATUS_WAZAKOUKA
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_LOOP_HIT_MSG
	SEQ_END
