
//============================================================================
/**
 *
 *@file		sub_220.s
 *@brief	戦闘シーケンス
 *			なげつける追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_220:
//	MESSAGE			NagetsukeruMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_WORK
//	SERVER_WAIT
//	WAIT			MSG_WAIT
	IF				IF_FLAG_EQ,BUF_PARA_NAGETSUKERU_SEQ_NO,0,SUB_220_END
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_hp,0,SUB_220_END
	//みがわりに当たっていたら実の効果なし
	MIGAWARI_CHECK	SIDE_DEFENCE,SUB_220_END
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_NAGETSUKERU_WORK
	GOSUB_WORK		BUF_PARA_NAGETSUKERU_SEQ_NO
SUB_220_END:
	SEQ_END
