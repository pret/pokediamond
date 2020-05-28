//============================================================================
/**
 *
 *@file		be_175.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			175　５ターンの間、相手は攻撃技しか出せなくなる。
 *				 他の技を選ぼうとすると「○○○○○は　ちょうはつ　されて　○○○○○○○　がだせない！」となる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_175:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_CHOUHATSU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
