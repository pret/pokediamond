//============================================================================
/**
 *
 *@file		be_047.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			047�@�N���e�B�J���q�b�g���o�₷���Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_047:
	//���łɂ��������߂��Ă��鎞�́A���܂����܂��ɂ���
	IF_PSP		IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KIAIDAME,Umakukimaran
	VALUE		VAL_BIT,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KIAIDAME|ADD_STATUS_ATTACK
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
