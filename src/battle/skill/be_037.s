//============================================================================
/**
 *
 *@file		be_037.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			037�@�˂ނ�@�g�o��S�񕜂��āA�������Q�^�[�����点��
 *
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_037:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NEMURU|ADD_STATUS_WAZAKOUKA
	SEQ_END
