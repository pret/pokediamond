
//============================================================================
/**
 *
 *@file		sub_064.s
 *@brief	�퓬�V�[�P���X
 *			�͂�ǂ��ǉ����ʃV�[�P���X
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_064:
	//�͂�ǂ��t���O�𗧂Ă�
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_HANDOU
	VALUE_WORK		VAL_SET,BUF_PARA_WAZA_NO_KEEP_ATTACK,BUF_PARA_WAZA_NO_NOW
	//���݂̑��^�[������ێ��i�{�P�̎�����������ԂɂȂ�΂����j
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_wkw_handou_count,BUF_PARA_TOTAL_TURN
	SEQ_END

