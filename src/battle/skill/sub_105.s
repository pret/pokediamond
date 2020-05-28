
//============================================================================
/**
 *
 *@file		sub_105.s
 *@brief	�퓬�V�[�P���X
 *			���΂�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_105:
	//�݂������o����Ă��鎞�́A���܂����܂��
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//�U���͂�MAX�܂ŏオ���Ă��Ȃ����́A���ʃX�^�[�g
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_abiritycnt_pow,12,SUB_105_ABICNT_START
	//���łɂ����񂵂Ă��Ȃ����́A�����X�^�[�g
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_105_KONRAN_START
	//MAX�ō����̎��́A���܂����܂��
	BRANCH			Umakukimaran
SUB_105_ABICNT_START:
	//�U����2�i�K�グ����Z�b�g
	VALUE			VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_POWUP2
	GOSUB			SUB_SEQ_ABICNT_CALC
	//���łɂ����񂵂Ă��鎞�́A���ʏI��
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_105_END
SUB_105_KONRAN_START:
	GOSUB			SUB_SEQ_KONRAN
SUB_105_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
