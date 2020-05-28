
//============================================================================
/**
 *
 *@file		sub_160.s
 *@brief	戦闘シーケンス
 *			おいかぜ追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_160:
	IF			IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_ATTACK,SIDE_CONDITION_OIKAZE,Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		OikazeMineMsg,TAG_NONE_DIR,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	VALUE		VAL_BIT,BUF_PARA_SIDE_CONDITION_ATTACK,SIDE_CONDITION_OIKAZE
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
