//============================================================================
/**
 *
 *@file		be_057.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			057�@�Ώۂ̑���Ɠ����p�ɂȂ�A�Z���G�Ɠ����Z���g����i�o�o�͑S�ĂT�j
 *
 *@author	HisashiSogabe
 *@data		2006.01.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_057:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HENSIN|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
