
//============================================================================
/**
 *
 *@file		sub_145.s
 *@brief	戦闘シーケンス
 *			リフレッシュシーケンス

 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_145:
	//どく、まひ、やけどになっていないなら、うまくきまらん
	IF_PSP		IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_KARAGENKI,Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE	VAL_SET,SIDE_ATTACK,ID_PSP_condition,0
	MESSAGE		RefleshMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	STATUS_SET	SIDE_ATTACK,STATUS_NORMAL
	WAIT		MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
