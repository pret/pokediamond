
//============================================================================
/**
 *
 *@file		sub_286.s
 *@brief	�퓬�V�[�P���X
 *			�����鎸�s�V�[�P���X�i�ړ��|�P�����j
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_286:
	MESSAGE			EscapeNGMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
