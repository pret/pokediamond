//============================================================================
/**
 *
 *@file		be_225.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			225�@�R�^�[���̊ԁA�����̏�ɂ���|�P�����̑f�������Q�{�ɂ���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_225:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_OIKAZE|ADD_STATUS_WAZAKOUKA
	SEQ_END
