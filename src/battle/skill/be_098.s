//============================================================================
/**
 *
 *@file		be_098.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			098�@���̋Z���g������ɓG�̃_���[�W�Ő퓬�s�\�ɂȂ�ƁA�G�̃|�P�������퓬�s�\�ɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_098:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MICHIDURE|ADD_STATUS_WAZAKOUKA
	SEQ_END
