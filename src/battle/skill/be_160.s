//============================================================================
/**
 *
 *@file		be_160.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			160�@�����̓���h����P�i�K�グ��B�R��܂ł����킦�邱�Ƃ��ł���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_160:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TAKUWAERU|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	SEQ_END
