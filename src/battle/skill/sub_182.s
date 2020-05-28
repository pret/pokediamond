
//============================================================================
/**
 *
 *@file		sub_182.s
 *@brief	戦闘シーケンス
 *			でんきエンジンシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_182:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_abiritycnt_agi,12,MaxUp				
	STATUS_EFFECT	SIDE_DEFENCE,STATUS_EFF_UP
	SERVER_WAIT
	PSP_VALUE		VAL_ADD,SIDE_DEFENCE,ID_PSP_abiritycnt_agi,1
	VALUE			VAL_SET,BUF_PARA_MSG_WORK,COND_AGI
	MESSAGE			TokuseiStatusUpMineMsg,TAG_NICK_TOKU_STAT,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

MaxUp:
	MESSAGE			TokuseiHPKaifukuNGMineMsg,TAG_NICK_TOKU_WAZA,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

