//============================================================================
/**
 *
 *@file		be_191.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			191�@������Ώۂ̃|�P�����Ɠ���ւ���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_191:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SKILLSWAP|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
