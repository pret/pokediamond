
//============================================================================
/**
 *
 *@file		sub_019.s
 *@brief	戦闘シーケンス
 *			めざめるシーケンス
 *@author	HisashiSogabe
 *@data		2005.11.30
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_019:
	//特性ぼうおんを持っている時は、さわぐチェックをしない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_WORK,TOKUSYU_BOUON,SEQ_NO_SAWAGU_CHECK
	IF				IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,SEQ_NO_SAWAGU_CHECK
	MESSAGE			WakeupSawaguMineMsg,TAG_NICK,SIDE_WORK
	BRANCH			SUB_019_END
SEQ_NO_SAWAGU_CHECK:
	MESSAGE			WakeupMineMsg,TAG_NICK,SIDE_WORK
SUB_019_END:
	SERVER_WAIT
	STATUS_SET		SIDE_WORK,STATUS_NORMAL
	WAIT			MSG_WAIT
	//ねむりとあくむフラグを落とす
	PSP_VALUE		VAL_NBIT,SIDE_WORK,ID_PSP_condition,CONDITION_NEMURI
	PSP_VALUE		VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_AKUMU
	SEQ_END
