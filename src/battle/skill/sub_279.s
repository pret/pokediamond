
//============================================================================
/**
 *
 *@file		sub_279.s
 *@brief	戦闘シーケンス
 *			AttackClientとDefenceClientの退避
 *@author	HisashiSogabe
 *@data		2006.07.01
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_279:
	VALUE_WORK	VAL_GET,BUF_PARA_ATTACK_CLIENT,BUF_PARA_ATTACK_CLIENT_TEMP
	VALUE_WORK	VAL_GET,BUF_PARA_DEFENCE_CLIENT,BUF_PARA_DEFENCE_CLIENT_TEMP
	SEQ_END

