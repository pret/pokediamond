//============================================================================
/**
 *
 *@file		be_222.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			222�@�����Ă���؂̎��ɂ���āA�Z�̃^�C�v�ƈЗ͂��ς��B
 *				 �P�x�g���Ɩ؂̎��͏�����B�����Ă��Ȃ��Ƃ��̓m�[�}���^�C�v�B�ʓr�e�[�u���p�ӁB
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_222:
	SHIZENNOMEGUMI		Umakukimaran
	CRITICAL_CHECK
	DAMAGE_CALC
	//�����Ă���A�C�e��������
//	PSP_VALUE			VAL_SET,SIDE_ATTACK,ID_PSP_item,0
	KILL_ITEM			SIDE_ATTACK
	SEQ_END

Umakukimaran:
	VALUE				VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
