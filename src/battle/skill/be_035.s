//============================================================================
/**
 *
 *@file		be_035.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			035�@�T�^�[���̊ԁA�G�̓���U���̃_���[�W�𔼌�������A�g�p�����|�P��������サ�Ă��^�[�����͌��ʂ��󂯌p�����
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_035:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HIKARINOKABE|ADD_STATUS_WAZAKOUKA
	SEQ_END
