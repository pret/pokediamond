
//============================================================================
/**
 *
 *@file		sub_208.s
 *@brief	戦闘シーケンス
 *			ステータスアップ装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_208:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	VALUE			VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_POWUP-1
	VALUE_WORK		VAL_ADD,BUF_PARA_TSUIKA_PARA,BUF_PARA_MSG_WORK
	VALUE			VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_SOUBIITEM
	VALUE_WORK		VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_CLIENT_WORK
	GOSUB			SUB_SEQ_ABICNT_CALC
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END
