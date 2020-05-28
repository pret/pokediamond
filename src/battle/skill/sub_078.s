
//============================================================================
/**
 *
 *@file		sub_078.s
 *@brief	戦闘シーケンス
 *			テクスチャー２シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_078:
	TEXTURE2	Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		TextureMineMsg,TAG_NICK_TYPE,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

