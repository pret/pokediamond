
//============================================================================
/**
 *
 *@file		sub_173.s
 *@brief	戦闘シーケンス
 *			ヒールブロックシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_173:
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_wkw_healblock_count,0,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_HEALBLOCK
	PSP_VALUE		VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_healblock_count,HEALBLOCK_COUNT
	MESSAGE			HealblockMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE			KimaranMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END

