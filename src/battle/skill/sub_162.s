
//============================================================================
/**
 *
 *@file		sub_162.s
 *@brief	戦闘シーケンス
 *			パワートリックシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_162:
	PSP_VALUE		VAL_XOR,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_POWER_TRICK
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_pow,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_def,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_pow,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_def,BUF_PARA_CALC_WORK
	MESSAGE			PowerTrickMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
