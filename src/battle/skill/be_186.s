//============================================================================
/**
 *
 *@file		be_186.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			186�@���t���N�^�[�A�Ђ���̂��ׂ��󂷁B
 *
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_186:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KAWARAWARI|ADD_STATUS_WAZAKOUKA_KAWARAWARI|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
