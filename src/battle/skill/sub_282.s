
//============================================================================
/**
 *
 *@file		sub_282.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			���܂񔭓����ɍU���Ώۂ����Ȃ��V�[�P���X
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_282:
//���܂񂪂Ƃ��ꂽ
	MESSAGE			GamanOverMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���߃t���O�𗎂Ƃ�
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP
	MESSAGE			NoPokemonMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

