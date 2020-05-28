//============================================================================
/**
 *
 *@file		be_092.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			092�@�������u�˂ނ�v��Ԃ̎��������ʂ̂���Z�i�u�˂ނ�v��ԂłȂ��ƋZ�͎��s����j�A
 *				 �R���̊m���œG���Ђ�܂���i�P�^�[���U���𕕂���j
 *
 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_092:
	//�˂ނ��Ԃ���Ȃ��Ƃ��́A���܂����܂��
	IF_PSP			IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI,Umakukimaran
	//�˂��Ƃ��甭���������т��ł́u���������˂Ă���v�������Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_WAZA_NO_TEMP,WAZANO_NEGOTO,BE_092_NEXT
	GOSUB			SUB_SEQ_SLEEPING
BE_092_NEXT:
	VALUE			VAL_BIT,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
