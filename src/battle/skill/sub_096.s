
//============================================================================
/**
 *
 *@file		sub_096.s
 *@brief	�퓬�V�[�P���X
 *			�̂낢�i�m�[�}���j�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_096:
	//�f������1�i�K��������Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_AGIDOWN
	GOSUB		SUB_SEQ_ABICNT_CALC
	//����ȍ~�́AATTACK_MESSAGE��WAZA_EFFECT�͏o�Ȃ��悤�ɂ���
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_ATTACK_MSG|SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	//�U����1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_POWUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	//�h���1�i�K�グ����Z�b�g
	VALUE		VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_DEFUP
	GOSUB		SUB_SEQ_ABICNT_CALC
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG
	VALUE		VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK
	SEQ_END
