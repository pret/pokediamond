//============================================================================
/**
 *
 *@file		be_146.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			146 追加効果で相手がひるむ＋そらをとぶ状態の相手に2倍ダメージ
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_146:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
	//そらをとぶをしている相手には2倍ダメージを与える
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SORAWOTOBU_HIT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU,BE_146_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_146_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
