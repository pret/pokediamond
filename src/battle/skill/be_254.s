//============================================================================
/**
 *
 *@file		be_254.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			254�@�U����A�����̍ő�g�o�̂S���̂P���������󂯂�
 *
 *@author	HisashiSogabe
 *@data		2005.12.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_254:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_WARUAGAKI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
