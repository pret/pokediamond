
//============================================================================
/**
 *
 *@file		sub_017.s
 *@brief	戦闘シーケンス
 *			ループヒット
 *@author	HisashiSogabe
 *@data		2005.11.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_017:
	//メッセージを出さないフラグが立っていたら表示しない
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_LOOP_HIT_MSG,SUB_017_END
	MESSAGE			RenzokuHitMsg,TAG_NUM,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_017_END:
	SEQ_END
