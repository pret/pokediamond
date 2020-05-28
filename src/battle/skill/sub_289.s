
//============================================================================
/**
 *
 *@file		sub_289.s
 *@brief	戦闘シーケンス
 *			トレーナーがかいふくのくすりを使用したシーケンス
 *@author	HisashiSogabe
 *@data		2006.07.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_289:
	STATUS_SET		SIDE_ATTACK,STATUS_NORMAL
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_condition,0
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KONRAN
	JUMP			SUB_SEQ_TRUSE_RECV_HP
