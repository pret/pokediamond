
//============================================================================
/**
 *
 *@file		sub_030.s
 *@brief	戦闘シーケンス
 *			出す技によってこおり状態が溶けたシーケンス
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_030:
	//こおりフラグを落とす
	PSP_VALUE	VAL_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_KOORI
	MESSAGE		WazaMeltMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	STATUS_SET	SIDE_ATTACK,STATUS_NORMAL
	WAIT		MSG_WAIT
	SEQ_END
