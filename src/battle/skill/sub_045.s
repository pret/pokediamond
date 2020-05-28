
//============================================================================
/**
 *
 *@file		sub_045.s
 *@brief	戦闘シーケンス
 *			テクスチャーシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_045:
	TEXTURE		Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		TextureMineMsg,TAG_NICK_TYPE,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

