//============================================================================
/**
 *
 *@file		be_205.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			205�@����̍U���A�h�䂪������B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_205:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KUSUGURU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
