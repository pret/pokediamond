//============================================================================
/**
 *
 *@file		be_242.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			242�@�ЂƂO�ɏo���Z���o���B�i�_�u���o�g���ɂ��Ή��j
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_242:
	//�o����Z��I�����ċZ�̃V�[�P���X�փW�����v
	MANEKKO			Umakukimaran
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
