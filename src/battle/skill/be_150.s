//============================================================================
/**
 *
 *@file		be_150.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			150 追加効果で相手がひるむ＋ちいさくなる状態の相手に2倍ダメージ
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_150:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
	//ちいさくなるをしている相手には2倍ダメージを与える
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_CHIISAKUNARU,BE_150_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_150_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
