//============================================================================
/**
 *
 *@file		be_193.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			193�@�ǂ��A�܂ЁA�₯�ǂ�����
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_193:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_REFRESH|ADD_STATUS_WAZAKOUKA
	SEQ_END

