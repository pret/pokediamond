//============================================================================
/**
 *
 *@file		be_046.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			046�@�\�͂���������ʂ̋Z��ǉ����ʂ��󂯂Ȃ��Ȃ�B
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_046:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SIROIKIRI|ADD_STATUS_WAZAKOUKA
	SEQ_END
