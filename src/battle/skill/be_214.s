//============================================================================
/**
 *
 *@file		be_214.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			214�@�g�o�������񕜂��邪�A���̃^�[���͒n�ʋZ���P�{�œ�����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_214:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HANEYASUME|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	SEQ_END
