
//============================================================================
/**
 *
 *@file		sub_039.s
 *@brief	�퓬�V�[�P���X
 *			������V�[�P���X�i�������U���j
 *@author	HisashiSogabe
 *@data		2005.12.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_039:
	MESSAGE			ConfusedMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_KONRAN
	SERVER_WAIT
	MESSAGE			KonranMsg2,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ߌn�̃t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_ATTACK
	//HP�P�őς���n�`�F�b�N
	HP1_CHECK		SIDE_ATTACK
	GOSUB			SUB_SEQ_HP_CALC
	GOSUB			SUB_SEQ_WAZA_STATUS_MSG
	SEQ_END
