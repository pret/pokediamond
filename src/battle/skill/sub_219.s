
//============================================================================
/**
 *
 *@file		sub_219.s
 *@brief	戦闘シーケンス
 *			ついばむ追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_219:
	TSUIBAMU		SUB_219_NEXT,SUB_219_END
	MESSAGE			TsuibamuMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
//	PSP_VALUE		VAL_SET,SIDE_DEFENCE,ID_PSP_item,0
	KILL_ITEM		SIDE_DEFENCE
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//効果のない木の実は、ついばむだけで終了
	IF				IF_FLAG_EQ,BUF_PARA_TEMP_WORK,0,SUB_219_END
	GOSUB_WORK		BUF_PARA_TEMP_WORK
SUB_219_END:
	SEQ_END

SUB_219_NEXT:
	MESSAGE			TokuseiNoWazaMineMsg,TAG_NICK_TOKU_WAZA,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
