
//============================================================================
/**
 *
 *@file		sub_281.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			�U���Ώۂ����Ȃ��ē�����Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.07.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_281:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			NoPokemonMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
