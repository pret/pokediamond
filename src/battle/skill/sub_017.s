
//============================================================================
/**
 *
 *@file		sub_017.s
 *@brief	�퓬�V�[�P���X
 *			���[�v�q�b�g
 *@author	HisashiSogabe
 *@data		2005.11.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_017:
	//���b�Z�[�W���o���Ȃ��t���O�������Ă�����\�����Ȃ�
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_LOOP_HIT_MSG,SUB_017_END
	MESSAGE			RenzokuHitMsg,TAG_NUM,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_017_END:
	SEQ_END
