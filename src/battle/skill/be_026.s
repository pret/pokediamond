
//============================================================================
/**
 *
 *@file		be_026.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			026�@�Z���g�p������̂Q�^�[�����i���̊Ԃ͑���s�\�j�Ɏ󂯂��_���[�W��{�ɂ��ĕԂ�
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_026:
	IF_PSP		IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//���܂�I�����́AKEEP����������Ԃŉ���Ă���̂ŁA��������
	IF			IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER,SeqWazaAfter
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_GAMAN|ADD_STATUS_ATTACK
	SEQ_END
SeqWazaAfter:
	//ATTACK���b�Z�[�W�͕\�����Ȃ�
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_ATTACK_MSG
	SEQ_END

