//============================================================================
/**
 *
 *@file		be_226.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			226�@�G�A�����A������I�����Ď��s�B�����_���ŃX�e�[�^�X�̂����ꂩ�̒l�����[��Əグ��B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_226:
	//�݂������o����Ă���Ƃ��́A���s����
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran

	TUBOWOTUKU		Umakukimaran

	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
