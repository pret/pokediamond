
//============================================================================
/**
 *
 *@file		sub_133.s
 *@brief	�퓬�V�[�P���X
 *			���傤�͂ŋZ�������Ȃ��V�[�P���X

 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_133:
	//���傤�͂J�E���^��-1����i�ŏ��̃^�[�������߂ɂ��Ă���̂Łj
//	PSP_VALUE		VAL_SUB,SIDE_ATTACK,ID_PSP_wkw_chouhatsu_count,1
	MESSAGE			ChouhatsuNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
