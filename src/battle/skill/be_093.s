//============================================================================
/**
 *
 *@file		be_093.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			093�@�����̃^�C�v�𑊎肪�g���Ă����Z�̒�R�͂ɕς���
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_093:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TEXTURE2|ADD_STATUS_WAZAKOUKA
	SEQ_END
