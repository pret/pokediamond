//============================================================================
/**
 *
 *@file		be_261.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			261　２～５ターンの間ダメージを与える。その間、相手は逃げられない＋ダイビング中の相手に2倍ダメージ
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_261:
	//ダイビングをしている相手には2倍ダメージを与える
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_DAIBINGU_HIT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_DAIBINGU,BE_261_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_261_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SHIME|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_CHECK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
