
//============================================================================
/**
 *
 *@file		sub_046.s
 *@brief	�퓬�V�[�P���X
 *			�������������V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_046:
	ATTACK_MESSAGE
	SERVER_WAIT
	//HPMAX��ǂݍ���
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	//HPMAX�𔼕���
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_KAIFUKU
	SEQ_END
