
//============================================================================
/**
 *
 *@file		sub_284.s
 *@brief	�퓬�V�[�P���X
 *			������V�[�P���X�i�f�o�b�O�p���������j
 *@author	HisashiSogabe
 *@data		2006.07.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_284:
	SE_PLAY			SIDE_ATTACK,BSE_ESCAPE
Command:
	MESSAGE			EscapeMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	FADE_OUT
	SERVER_WAIT
	VALUE			VAL_BIT,BUF_PARA_WIN_LOSE_FLAG,FIGHT_WIN|FIGHT_ESCAPE_SELECT
	WIN_LOSE_SET
	SEQ_END
