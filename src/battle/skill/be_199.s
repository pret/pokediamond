//============================================================================
/**
 *
 *@file		be_199.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			199�@���ׂẴ|�P������������ԂɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_199:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KONRAN|ADD_STATUS_DEFENCE
	SEQ_END
