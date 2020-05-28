//============================================================================
/**
 *
 *@file		be_092.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			092　自分が「ねむり」状態の時だけ効果のある技（「ねむり」状態でないと技は失敗する）、
 *				 ３割の確率で敵をひるませる（１ターン攻撃を封じる）
 *
 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_092:
	//ねむり状態じゃないときは、うまくきまらん
	IF_PSP			IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI,Umakukimaran
	//ねごとから発生したいびきでは「ぐうぐうねている」をださない
	IF				IF_FLAG_EQ,BUF_PARA_WAZA_NO_TEMP,WAZANO_NEGOTO,BE_092_NEXT
	GOSUB			SUB_SEQ_SLEEPING
BE_092_NEXT:
	VALUE			VAL_BIT,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
