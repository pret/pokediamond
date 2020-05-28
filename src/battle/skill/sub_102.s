
//============================================================================
/**
 *
 *@file		sub_102.s
 *@brief	戦闘シーケンス
 *			ほろびのうたカウントダウンシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_102:
	MESSAGE		HorobinoutaCountMineMsg,TAG_NICK_NUM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	IF_PSP		IF_FLAG_BIT,SIDE_WORK,ID_PSP_waza_kouka,WAZAKOUKA_HOROBINOUTA,SUB_102_END
	GOSUB		SUB_SEQ_HP_CALC
SUB_102_END:
	SEQ_END
