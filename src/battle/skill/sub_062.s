
//============================================================================
/**
 *
 *@file		sub_062.s
 *@brief	�퓬�V�[�P���X
 *			���������ߏ���
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_062:
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	//���������߃t���O�𗧂Ă�
	PSP_VALUE	VAL_BIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_KIAIDAME
	MESSAGE		KiaidameMineMsg,TAG_NICK,SIDE_TSUIKA
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END

