//============================================================================
/**
 *
 *@file		be_030.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			030�@�����̂����Ă���Z�̂ǂꂩ�̃^�C�v�Ɏ����̃^�C�v��ς���
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_030:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TEXTURE|ADD_STATUS_WAZAKOUKA
	SEQ_END
