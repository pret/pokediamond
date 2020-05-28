//============================================================================
/**
 *
 *@file		be_114.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			114　この技を使用した時に戦闘に出ていたポケモンは３ターン後に戦闘不能になる
 *				 （１度ポケモンを引っ込めると効果は解除される）
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_114:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HOROBINOUTA|ADD_STATUS_WAZAKOUKA
	SEQ_END
