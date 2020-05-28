
//============================================================================
/**
 *
 *@file		sub_075.s
 *@brief	戦闘シーケンス
 *			うまくきまらんメッセージを出す

 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_075:
	MESSAGE			UmakukimaranMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessageを無効にするためにこのフラグを立てる
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
