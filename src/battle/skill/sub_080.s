
//============================================================================
/**
 *
 *@file		sub_080.s
 *@brief	�퓬�V�[�P���X
 *			�X�P�b�`�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_080:
	//�݂������o����Ă���Ƃ��́A���s����
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	SKETCH			Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	MESSAGE			SketchMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_078_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

