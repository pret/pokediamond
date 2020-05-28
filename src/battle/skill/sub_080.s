
//============================================================================
/**
 *
 *@file		sub_080.s
 *@brief	戦闘シーケンス
 *			スケッチシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_080:
	//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	SKETCH			Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	MESSAGE			SketchMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_078_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

