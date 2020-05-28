
//============================================================================
/**
 *
 *@file		sub_280.s
 *@brief	戦闘シーケンス
 *			AttackClientとDefenceClientの復帰
 *@author	HisashiSogabe
 *@data		2006.07.01
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_280:
	VALUE_WORK	VAL_GET,BUF_PARA_ATTACK_CLIENT_TEMP,BUF_PARA_ATTACK_CLIENT
	VALUE_WORK	VAL_GET,BUF_PARA_DEFENCE_CLIENT_TEMP,BUF_PARA_DEFENCE_CLIENT
	SEQ_END

