
//============================================================================
/**
 *
 *@file		sub_257.s
 *@brief	�퓬�V�[�P���X
 *			�������Ƃ𕷂����ɂЂ�˂��͂��߂�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_257:
	WAIT		MSG_WAIT/2
	MESSAGE		HiruneMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//�ǉ��Ώۂ�AttackClient��ݒ�
	VALUE_WORK	VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_ATTACK_CLIENT
	//�Z���ʂɂ��ǉ����ʃt���O��ݒ�
	VALUE		VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA
	//�˂ނ�ǉ��V�[�P���X���R�[��
	GOSUB		SUB_SEQ_NEMURI
	SEQ_END
