//============================================================================
/**
 *
 *@file		be_179.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			179�@�˂������Ƃ��������̃^�[���I�����A�����̂g�o�̔����̒l���񕜂���B�|�P����������ւ���Ă����ʂ�����
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_179:
	NEGAIGOTO		Umakukimaran
	SEQ_END

Umakukimaran:
	VALUE			VAL_SET,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
