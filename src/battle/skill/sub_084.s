
//============================================================================
/**
 *
 *@file		sub_084.s
 *@brief	�퓬�V�[�P���X
 *			����݃V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_084:
	//�������ŊO��Ă��鎞�́A���܂����܂��ɂ���
	IF			IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	URAMI		Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		UramiMineMsg,TAG_NICK_WAZA_NUM,SIDE_DEFENCE,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
