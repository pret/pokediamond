
//============================================================================
/**
 *
 *@file		sub_048.s
 *@brief	�퓬�V�[�P���X
 *			�˂��ɂ��΂�̒ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_048:
	//�U�������|�P�����̃��x�����擾
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_level,BUF_PARA_CALC_WORK
	//���̒l��5�{��
	VALUE			VAL_MUL,BUF_PARA_CALC_WORK,5
	//�G���͉��Z���Ȃ�
	SIDE_CHECK		SIDE_ATTACK,SIDE_ENEMY,SUB_048_NEXT
	//�˂��ɂ��΂�J�E���^�[�ɉ��Z
	VALUE_WORK		VAL_ADD,BUF_PARA_KOBAN_COUNTER,BUF_PARA_CALC_WORK
SUB_048_NEXT:
	MESSAGE			NekonikobanMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
