
//============================================================================
/**
 *
 *@file		sub_015.s
 *@brief	�퓬�V�[�P���X
 *			�Ђ�ނŋZ�������Ȃ��V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.11.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_015:
	MESSAGE			HirumuMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_ATTACK
	//�����ӂ��̂�����́A�f����1�A�b�v
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_HUKUTUNOKOKORO,SUB_015_END
	VALUE			VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI
	VALUE			VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_AGIUP
	VALUE_WORK		VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_ABICNT_CALC
SUB_015_END:
	SEQ_END
