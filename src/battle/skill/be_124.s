//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			124�@�T�^�[���̊ԁA�����ԁi�ǂ��E�}�q���j�ɂȂ�Ȃ��Ȃ�A�g�p�����|�P��������サ�Ă��^�[�����͌��ʂ��󂯌p�����
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_124:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SHINPI|ADD_STATUS_WAZAKOUKA
	SEQ_END
