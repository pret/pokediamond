//============================================================================
/**
 *
 *@file		be_208.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			208�@�U���A�h�䂪�オ��B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_208:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_BUILD_UP|ADD_STATUS_ATTACK
	SEQ_END
