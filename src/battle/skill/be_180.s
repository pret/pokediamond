//============================================================================
/**
 *
 *@file		be_180.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			180�@�����̍T���|�P�����̋Z�������_���ŏo��
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_180:
	//�����_���ŏo����Z��I�����ċZ�̃V�[�P���X�փW�����v
	NEKONOTE		Umakukimaran
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
