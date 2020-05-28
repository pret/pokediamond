
//============================================================================
/**
 *
 *@file		sub_142.s
 *@brief	戦闘シーケンス
 *			はたきおとすシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_142:
	//みがわりがいる場合は、失敗
	MIGAWARI_CHECK	SIDE_DEFENCE,SUB_142_END
	//特性マルチタイプは、うまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,SUB_142_END
	HATAKIOTOSU		SUB_142_END
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_142_END:
	SEQ_END

