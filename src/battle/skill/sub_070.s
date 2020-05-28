
//============================================================================
/**
 *
 *@file		sub_070.s
 *@brief	戦闘シーケンス
 *			かなしばり効果発動シーケンス

 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_070:
	//命中率で外れている時は、うまくきまらんにする
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	KANASIBARI		Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	MESSAGE			KanashibariMineMsg,TAG_NICK_WAZA,SIDE_DEFENCE,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
