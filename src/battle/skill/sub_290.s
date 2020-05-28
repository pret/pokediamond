
//============================================================================
/**
 *
 *@file		sub_290.s
 *@brief	戦闘シーケンス
 *			ついばむでアイテムをなくすかチェックシーケンス
 *@author	HisashiSogabe
 *@data		2006.07.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_290:
	//ついばむからの発動は、アイテムをなくす処理を飛ばす
	IF				IF_FLAG_BIT,BUF_PARA_OSTF_STATUS_FLAG_ATTACK,OSTF_STATUS_FLAG_TSUIBAMU,SUB_290_END
	KILL_ITEM		SIDE_WORK
SUB_290_END:
	VALUE			VAL_NBIT,BUF_PARA_OSTF_STATUS_FLAG_ATTACK,OSTF_STATUS_FLAG_TSUIBAMU
	SEQ_END

