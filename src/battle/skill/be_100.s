//============================================================================
/**
 *
 *@file		be_100.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			100�@�G�̍Ō�ɏo�����Z�̂o�o��2�`5�����_���Ō��炷
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_100:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_URAMI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
