
//============================================================================
/**
 *
 *@file		sub_071.s
 *@brief	�퓬�V�[�P���X
 *			���Ȃ��΂�ŋZ�������Ȃ��V�[�P���X

 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_071:
	//���ߋZ�����Ȃ��΂��Ă����ꍇ�́A�J�E���^��-1����K�v�Ȃ�
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,NoDecCounter
	//���Ȃ��΂�J�E���^��-1����i�ŏ��̃^�[�������߂ɂ��Ă���̂Łj
//	PSP_VALUE		VAL_SUB,SIDE_ATTACK,ID_PSP_wkw_kanashibari_count,1
NoDecCounter:
	MESSAGE			KanashibariNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
