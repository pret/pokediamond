
//============================================================================
/**
 *
 *@file		sub_161.s
 *@brief	戦闘シーケンス
 *			インファイトシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_161:
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	//防御を1段階下げるをセット
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_DEFDOWN
	GOSUB		SUB_SEQ_ABICNT_CALC
	//特防を1段階下げるをセット
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEDEFDOWN
	GOSUB		SUB_SEQ_ABICNT_CALC
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	SEQ_END
