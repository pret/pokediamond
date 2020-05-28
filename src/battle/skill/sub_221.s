
//============================================================================
/**
 *
 *@file		sub_221.s
 *@brief	戦闘シーケンス
 *			特性による状態異常回復シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_221:
	MESSAGE		TokuseiNoJoutaiijouMineMsg,TAG_NICK_TOKU_COND,SIDE_WORK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	STATUS_SET	SIDE_WORK,STATUS_NORMAL
	WAIT		MSG_WAIT
	IF			IF_FLAG_EQ,BUF_PARA_MSG_WORK,MSG_COND_NEMURI,RecoverNemuri
	IF			IF_FLAG_EQ,BUF_PARA_MSG_WORK,MSG_COND_KONRAN,RecoverKonran
	IF			IF_FLAG_EQ,BUF_PARA_MSG_WORK,MSG_COND_MEROMERO,RecoverMeromero
RecoverNormal:
	PSP_VALUE	VAL_SET,SIDE_WORK,ID_PSP_condition,0
	BRANCH		SUB_221_END
RecoverNemuri:
	PSP_VALUE	VAL_SET,SIDE_WORK,ID_PSP_condition,0
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_AKUMU
	BRANCH		SUB_221_END
RecoverKonran:
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_KONRAN
	BRANCH		SUB_221_END
RecoverMeromero:
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_MEROMERO
SUB_221_END:
	SEQ_END

