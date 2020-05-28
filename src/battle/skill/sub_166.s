
//============================================================================
/**
 *
 *@file		sub_166.s
 *@brief	戦闘シーケンス
 *			ガードスワップシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_166:
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_abiritycnt_def,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_abiritycnt_def,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_abiritycnt_def,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_abiritycnt_def,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_abiritycnt_spedef,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_abiritycnt_spedef,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_abiritycnt_spedef,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_abiritycnt_spedef,BUF_PARA_CALC_WORK
	MESSAGE			GuardSwapMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
