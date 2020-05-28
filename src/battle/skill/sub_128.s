
//============================================================================
/**
 *
 *@file		sub_128.s
 *@brief	�퓬�V�[�P���X
 *			�����Ă�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_128:
	//�݂������o����Ă��鎞�́A���܂����܂��
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//���U��MAX�܂ŏオ���Ă��Ȃ����́A���ʃX�^�[�g
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_abiritycnt_spepow,12,SUB_128_ABICNT_START
	//���łɂ����񂵂Ă��Ȃ����́A�����X�^�[�g
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_128_KONRAN_START
	//MAX�ō����̎��́A���܂����܂��
	BRANCH			Umakukimaran
SUB_128_ABICNT_START:
	//���U��1�i�K�グ����Z�b�g
	VALUE			VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_SPEPOWUP
	GOSUB			SUB_SEQ_ABICNT_CALC
	//���łɂ����񂵂Ă��鎞�́A���ʏI��
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_KONRAN,SUB_128_END
SUB_128_KONRAN_START:
	GOSUB			SUB_SEQ_KONRAN
SUB_128_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
