
//============================================================================
/**
 *
 *@file		sub_192.s
 *@brief	�퓬�V�[�P���X
 *			������HP�񕜃V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_192:
	MESSAGE			TokuseiHPKaifukuMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP�v�Z�T�u���[�`����
	GOSUB			SUB_SEQ_HP_CALC
	SEQ_END
