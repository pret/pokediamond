//============================================================================
/**
 *
 *@file		be_246.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			246�@�З͍͂������A���̂R�̋Z���o���Ă��Ȃ��ƊO���B
 *				 �R�o������͏�ɂ���ԁA�L���B���݂̎莝���̋Z��S�ďo���؂�ΗL���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_246:
	TOTTEOKI		Umakukimaran
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
