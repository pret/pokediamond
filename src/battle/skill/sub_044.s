
//============================================================================
/**
 *
 *@file		sub_044.s
 *@brief	�퓬�V�[�P���X
 *			���΂��ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_044:
	//�Q�`�R�̗����𐶐�
	RANDOM_GET		1,2
	//���΂��r�b�g�ɂȂ�悤�ɁA���V�t�g
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,ABARERU_SHIFT
	//���΂��r�b�g�𗧂Ă�
	PSP_VALUE_WORK	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,BUF_PARA_CALC_WORK
	VALUE_WORK		VAL_SET,BUF_PARA_WAZA_NO_KEEP_ATTACK,BUF_PARA_WAZA_NO_NOW
	SEQ_END
