//============================================================================
/**
 *
 *@file		be_159.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			159　２～５ターン騒ぎ続け、その間は誰も眠ることができない
 *
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_159:
	//攻撃継続中は、追加効果をしない
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_SAWAGU,BE_159_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SAWAGU|ADD_STATUS_WAZAKOUKA
BE_159_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
