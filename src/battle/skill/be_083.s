//============================================================================
/**
 *
 *@file		be_083.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			083�@�S�Ă̋Z�̒����烉���_���łP�Z���o��
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_083:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//�����_���ŏo����Z��I�����ċZ�̃V�[�P���X�փW�����v
	YUBIWOHURU
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL
