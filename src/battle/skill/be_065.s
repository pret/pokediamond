//============================================================================
/**
 *
 *@file		be_065.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			065�@�T�^�[���̊ԁA�G�̕����U���̃_���[�W�𔼌�������A�g�p�����|�P��������サ�Ă��^�[�����͌��ʂ��󂯌p�����
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_065:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_RIHUREKUTAA|ADD_STATUS_WAZAKOUKA
	SEQ_END
