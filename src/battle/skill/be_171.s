//============================================================================
/**
 *
 *@file		be_171.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			171　まひしている相手には倍のダメージを与えるが、まひが治る
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_171:
	//みがわりがいる場合は、まひチェックをスルー
	MIGAWARI_CHECK	SIDE_DEFENCE,BE_171_NEXT
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_MAHI,BE_171_MAHI
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	BRANCH			BE_171_NEXT
BE_171_MAHI:
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_NOMAHI|ADD_STATUS_WAZAKOUKA
BE_171_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
