
//============================================================================
/**
 *
 *@file		sub_126.s
 *@brief	戦闘シーケンス
 *			MESSAGE_WORK表示シーケンス（追加効果扱い）
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_126:
//直接追加の場合、WAZAOUTシーケンスでメッセージを出さないので、ここで出す
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,SUB_126_NEXT
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
SUB_126_NEXT:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
