//============================================================================
/**
 *
 *@file		be_166.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			166�@����̓���U�����P�i�K�����č�����Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_166:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ODATERU|ADD_STATUS_WAZAKOUKA|ADD_STATUS_DEFENCE
	SEQ_END
