//============================================================================
/**
 *
 *@file		be_250.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			250�@�����Ƒ���̕⏕���ʂ�S�ē���ւ���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_250:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HEART_SWAP|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
