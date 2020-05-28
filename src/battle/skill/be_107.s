//============================================================================
/**
 *
 *@file		be_107.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			107　敵が「ねむり」状態の時だけ効果のある技（「ねむり」状態でないと技は失敗する）、
 *				 敵ポケモンあくむ状態にする	
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_107:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AKUMU|ADD_STATUS_WAZAKOUKA
	SEQ_END
