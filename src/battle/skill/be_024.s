//============================================================================
/**
 *
 *@file		be_024.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			024�@�G�|�P�����́u��𗦁v���P�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_024:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AVOIDDOWN|ADD_STATUS_DEFENCE
	SEQ_END
