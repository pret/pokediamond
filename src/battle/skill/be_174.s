//============================================================================
/**
 *
 *@file		be_174.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			174�@���ɏo���d�C�̋Z�̈З͂��Q�{�ɂȂ�B����h��͂��P�i�K�グ��B
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_174:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_JUUDEN|ADD_STATUS_WAZAKOUKA
	SEQ_END
