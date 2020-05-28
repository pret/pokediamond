//============================================================================
/**
 *
 *@file		be_122.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			122　効果が確率で変わる。４０％=４０の威力、３０％=８０の威力、１０％=１２０の威力、２０％=敵1/4回復。
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_122:
	PRESENT			HPKaifuku
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

HPKaifuku:
	//HP操作対象をDefenceClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_DEFENCE_CLIENT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_PRESENT|ADD_STATUS_WAZAKOUKA
	//こうかないタイプでも回復するように、無属性にする
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	//技エフェクトを回復用に変える
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	SEQ_END
	
