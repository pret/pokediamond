//============================================================================
/**
 *
 *@file		be_248.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			248�@�搧�Z�B�Ώۃ|�P�����̋Z���U���Z�Ȃ�΁A����ɑ�_���[�W�B�U���Z�łȂ��ꍇ���s����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_248:
	HUIUCHI			Umakukimaran
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
