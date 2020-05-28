//============================================================================
/**
 *
 *@file		be_222.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			222　もっている木の実によって、技のタイプと威力が変わる。
 *				 １度使うと木の実は消える。持っていないときはノーマルタイプ。別途テーブル用意。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_222:
	SHIZENNOMEGUMI		Umakukimaran
	CRITICAL_CHECK
	DAMAGE_CALC
	//持っているアイテムを消す
//	PSP_VALUE			VAL_SET,SIDE_ATTACK,ID_PSP_item,0
	KILL_ITEM			SIDE_ATTACK
	SEQ_END

Umakukimaran:
	VALUE				VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
