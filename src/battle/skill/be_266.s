//============================================================================
/**
 *
 *@file		be_266.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			266　相手の場において、出てきたポケモンのＨＰで１/８分ダメージ。
 *				 分母は相性倍率により変化する。1/2なら1/16、1/4なら1/32、×２なら1/4、×４なら1/2。
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_266:
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_DEFENCE,SIDE_CONDITION_STEALTHROCK,Umakukimaran
	VALUE			VAL_BIT,BUF_PARA_SIDE_CONDITION_DEFENCE,SIDE_CONDITION_STEALTHROCK
	MESSAGE_PARAM	StealthrockMineMsg,TAG_NONE_DIR,SIDE_ATTACK_ENEMY
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
