
//============================================================================
/**
 *
 *@file		sub_239.s
 *@brief	�퓬�V�[�P���X
 *			�q�[���u���b�N�ŉ񕜂ł��Ȃ����b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_239:
	VALUE		VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KAIHUKUHUUZI
	MESSAGE		HealblockRecoverNGMineMsg,TAG_NICK_WAZA,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
