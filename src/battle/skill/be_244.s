//============================================================================
/**
 *
 *@file		be_244.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			244�@����̖h��Ɠ��h�̃A�b�v��ԁi�㏸�E���~�ǂ�����j�Ǝ����̏�Ԃ����ꂩ����B
 *				 �����N���A�{�f�B�₵�낢����̓G�ɂ����팏�œ���ւ���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_244:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_GUARD_SWAP|ADD_STATUS_WAZAKOUKA
	SEQ_END
