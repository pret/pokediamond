//============================================================================
/**
 *
 *@file		be_247.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			247�@����̓������y�ӂ݂�z�ɂ�����B�y�Ȃ܂��z�ɂ͂����Ȃ��B
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_247:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NAYAMINOTANE|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
