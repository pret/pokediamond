
//============================================================================
/**
 *
 *@file		sub_056.s
 *@brief	�퓬�V�[�P���X
 *			���킮�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_056:
	VALUE_WORK		VAL_SET,BUF_PARA_WAZA_NO_KEEP_ATTACK,BUF_PARA_WAZA_NO_NOW
	//�Q�`�T�̗����𐶐�
	RANDOM_GET		3,3
	//���킮�r�b�g�ɂȂ�悤�ɁA���V�t�g
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,SAWAGU_SHIFT
	//���킮�r�b�g�𗧂Ă�
	PSP_VALUE_WORK	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,BUF_PARA_CALC_WORK
	//���킢�ł���ClientNo�̃r�b�g�𗧂Ă�
	VALUE_WORK		VAL_TO_BIT,BUF_PARA_CALC_WORK,BUF_PARA_ATTACK_CLIENT
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,FIELD_SAWAGU_SHIFT
	VALUE_WORK		VAL_BIT,BUF_PARA_FIELD_CONDITION,BUF_PARA_CALC_WORK
	MESSAGE			SawaguMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
