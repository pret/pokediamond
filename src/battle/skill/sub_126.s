
//============================================================================
/**
 *
 *@file		sub_126.s
 *@brief	�퓬�V�[�P���X
 *			MESSAGE_WORK�\���V�[�P���X�i�ǉ����ʈ����j
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_126:
//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�Ń��b�Z�[�W���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,SUB_126_NEXT
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
SUB_126_NEXT:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
