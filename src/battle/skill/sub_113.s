
//============================================================================
/**
 *
 *@file		sub_113.s
 *@brief	�퓬�V�[�P���X
 *			�}�O�j�`���[�h�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.01
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_113:
	//�Z�G�t�F�N�g���o�Ă���ꍇ�́A�ȉ��̃��b�Z�[�W�n���X�L�b�v
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_WAZA_EFFECT,SUB_113_NEXT
	ATTACK_MESSAGE	
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			MagnitudeMsg,TAG_NUM,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_113_NEXT:
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_HAZURE,SUB_113_END
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
SUB_113_END:
	SEQ_END
