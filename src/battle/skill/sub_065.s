
//============================================================================
/**
 *
 *@file		sub_065.s
 *@brief	�퓬�V�[�P���X
 *			�����ŋZ�������Ȃ��V�[�P���X
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_065:
	MESSAGE			HandouMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
