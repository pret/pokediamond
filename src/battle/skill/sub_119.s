
//============================================================================
/**
 *
 *@file		sub_119.s
 *@brief	�퓬�V�[�P���X
 *			���񂵂̂�����V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_119:
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	//�U����1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_POWUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	//�h���1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_DEFUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	//�f������1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_AGIUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	//���U��1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEPOWUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	//���h��1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEDEFUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	SEQ_END
