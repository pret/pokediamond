//============================================================================
/**
 *
 *@file		be_084.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			084�@���^�[���G�̂���g�o��D���A�D�������l���̂g�o���񕜂���i�Z���������|�P���������Ȃ��Ȃ��Ă��A���ʂ͎�������j
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_084:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_YADORIGI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
