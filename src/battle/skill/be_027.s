//============================================================================
/**
 *
 *@file		be_027.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			027　２～３ターン連続で攻撃する（攻撃中は操作不可能）、効果が切れると自分が「こんらん」状態になってしまう
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_027:
	//攻撃継続中は、追加効果をしない
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_ABARERU,BE_027_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_ABARERU|ADD_STATUS_WAZAKOUKA
BE_027_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
