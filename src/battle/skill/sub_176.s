
//============================================================================
/**
 *
 *@file		sub_176.s
 *@brief	戦闘シーケンス
 *			あたらなかったメッセージを出す

 *@author	HisashiSogabe
 *@data		2006.07.11
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_176:
	MESSAGE			DoubleNoHitMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessageを無効にするためにこのフラグを立てる
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
