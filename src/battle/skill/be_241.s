//============================================================================
/**
 *
 *@file		be_241.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			241�@���肪�o�����Ƃ��Ă���U���Z���P�D�T�{�̈З͂ŏo���B�����ɍU���ł���ΐ����B�ł��Ȃ��ꍇ���s�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_241:
	//�o����Z��I�����ċZ�̃V�[�P���X�փW�����v
	SAKIDORI		Umakukimaran
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
