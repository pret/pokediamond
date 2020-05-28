
//============================================================================
/**
 *
 *@file		sub_179.s
 *@brief	戦闘シーケンス
 *			もらいびシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_179:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_wkw_moraibi_flag,0,Already
	MESSAGE			MoraibiMineMsg,TAG_NICK_TOKU,SIDE_DEFENCE,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_wkw_moraibi_flag,1
	SEQ_END

Already:
	MESSAGE			TokuseiNoWazaMineMsg,TAG_NICK_TOKU_WAZA,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
