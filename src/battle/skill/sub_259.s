//============================================================================
/**
 *
 *@file		sub_259.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			���ߋZ�n�̗��߂���̏������܂Ƃ߂��T�u���[�`��
 *
 *@author	HisashiSogabe
 *@data		2005.11.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_259:
	//�Z�G�t�F�N�g�J�E���^���Z�b�g
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	//���߃t���O�𗎂Ƃ�
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP
	//���ߔ����t���O���Z�b�g
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER
	SEQ_END
