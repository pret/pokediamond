//============================================================================
/**
 *
 *@file		be_097.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			097　自分が「ねむり」状態の時だけ効果のある技（「ねむり」状態でないと技は失敗する）、持っている技をランダムで使う
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_097:
//	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NEGOTO|ADD_STATUS_WAZAKOUKA
//	SEQ_END
	//ねむり状態じゃないときは、うまくきまらん
	IF_PSP			IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI,Umakukimaran
	GOSUB			SUB_SEQ_SLEEPING
	NEGOTO			Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
