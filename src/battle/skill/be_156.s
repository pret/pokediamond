//============================================================================
/**
 *
 *@file		be_156.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			156 �g�p�����|�P�����́u�ڂ�����v���P�i�K�グ��{�u�܂邭�Ȃ�v��Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_156:
	//�u�܂邭�Ȃ�v�t���O�𗧂Ă�
	PSP_VALUE	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_MARUKUNARU
	//�u�ڂ�����v���P�i�K�グ��
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_DEFUP|ADD_STATUS_ATTACK
	SEQ_END
