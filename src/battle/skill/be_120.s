//============================================================================
/**
 *
 *@file		be_120.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			120�@�I�X�Ȃ烁�X�ɁA���X�Ȃ�I�X�ɂP�^�Q�̊m���ōU�����o���Ȃ���ԂɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_120:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MEROMERO|ADD_STATUS_DEFENCE
	//�ǉ�����Client��AttackClient���Z�b�g
	VALUE_WORK	VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	SEQ_END
