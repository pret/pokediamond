//============================================================================
/**
 *
 *@file		be_126.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			126　威力が確率で変わる、５％=10、１０％=30、２０％=50、３０％=70、２０％=90、１０％=110、５％=150。
 *				「あなをほる」状態の相手に使用すると倍のダメージを与える。
 *
 *@author	HisashiSogabe
 *@data		2006.02.01
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_126:
	//あなをほるをしている相手には2倍ダメージを与える
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_ANAWOHORU_HIT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_ANAWOHORU,BE_126_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_126_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MAGNITUDE|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	MAGNITUDE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
