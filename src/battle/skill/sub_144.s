
//============================================================================
/**
 *
 *@file		sub_144.s
 *@brief	�퓬�V�[�P���X
 *			�ӂ�����ŋZ�������Ȃ��V�[�P���X

 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_144:
	MESSAGE			HuuinNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
