
//============================================================================
/**
 *
 *@file		sub_174.s
 *@brief	戦闘シーケンス
 *			ヒールブロックで技がだせないシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_174:
	VALUE		VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KAIHUKUHUUZI
	MESSAGE		HealblockNGMineMsg,TAG_NICK_WAZA_WAZA,SIDE_ATTACK,SIDE_WORK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
