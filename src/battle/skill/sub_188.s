
//============================================================================
/**
 *
 *@file		sub_188.s
 *@brief	戦闘シーケンス
 *			へんしょくシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.22
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_188:
	MESSAGE			HensyokuMineMsg,TAG_NICK_TOKU_TYPE,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_type1,BUF_PARA_MSG_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_type2,BUF_PARA_MSG_WORK
	SEQ_END
