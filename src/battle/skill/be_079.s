//============================================================================
/**
 *
 *@file		be_079.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			079�@�g�o�̍ő�l�̂S���̂P���g���Ď����̕��g�����i�ϐg�̕ύX��Y�ꂸ�Ɂj
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_079:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MIGAWARI|ADD_STATUS_WAZAKOUKA
	SEQ_END
