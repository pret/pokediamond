
//============================================================================
/**
 *
 *@file		sub_138.s
 *@brief	戦闘シーケンス
 *			ばかぢからシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_138:
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	//攻撃を1段階下げるをセット
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_POWDOWN
	GOSUB		SUB_SEQ_ABICNT_CALC
	//防御を1段階下げるをセット
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_DEFDOWN
	GOSUB		SUB_SEQ_ABICNT_CALC
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	SEQ_END
