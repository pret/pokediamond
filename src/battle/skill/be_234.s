//============================================================================
/**
 *
 *@file		be_234.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			234�@�����̎󂯂Ă����Ԉُ�i�ǂ��A�ǂ��ǂ��A�˂ނ�A�܂ЁA�₯�ǁj���A�G�A������I��ő���𓯂���Ԃɂ���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_234:
	SURIKOMI	Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SURIKOMI|ADD_STATUS_DEFENCE
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
