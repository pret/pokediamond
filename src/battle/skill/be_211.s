//============================================================================
/**
 *
 *@file		be_211.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			211�@���U�A���h���オ��B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_211:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MEISOU|ADD_STATUS_ATTACK
	SEQ_END
