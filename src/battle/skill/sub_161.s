
//============================================================================
/**
 *
 *@file		sub_161.s
 *@brief	�퓬�V�[�P���X
 *			�C���t�@�C�g�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_161:
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	//�h���1�i�K��������Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_DEFDOWN
	GOSUB		SUB_SEQ_ABICNT_CALC
	//���h��1�i�K��������Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEDEFDOWN
	GOSUB		SUB_SEQ_ABICNT_CALC
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	SEQ_END
