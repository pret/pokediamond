
//============================================================================
/**
 *
 *@file		sub_108.s
 *@brief	�퓬�V�[�P���X
 *			���������ŋZ���o���̂Ɏ��s�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_108:
	GOSUB		SUB_SEQ_MEROMERO_KEEP
	MESSAGE		MeromeroNoWazaMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF	SIDE_ATTACK
	SEQ_END
