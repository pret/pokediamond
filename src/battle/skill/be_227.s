//============================================================================
/**
 *
 *@file		be_227.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			227�@��U�̂Ƃ��G����Ō�Ɏ󂯂��_���[�W��1.5�{�ŕԂ��B���̃^�[���U�����󂯂Ă��Ȃ��Ǝ��s�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_227:
	METALMIRROR		Umakukimaran
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
