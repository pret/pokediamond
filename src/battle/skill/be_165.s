//============================================================================
/**
 *
 *@file		be_165.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			165　相手が同じ技を２度続けて出せない状態にする「○○○○○は　いちゃもんを　つけられた！」
 *				（交代するまで効果は続く）同じ技を選ぼうとすると、
 *				「いちゃもん　つけられたので　つづけて　おなじ　わざが　だせない！」となって選べない
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_165:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ICHAMON|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
