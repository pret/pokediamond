//============================================================================
/**
 *
 *@file		be_106.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			106�@�G�𓦂����Ȃ�����B�g���[�i�[��ł͂��ꂩ�����ł��Ȃ��Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_106:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KUROIMANAZASHI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
