
//============================================================================
/**
 *
 *@file		sub_201.s
 *@brief	�퓬�V�[�P���X
 *			�ŉ񕜑����A�C�e�����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_201:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemNoDokuMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	STATUS_SET		SIDE_WORK,STATUS_NORMAL
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_SET,SIDE_WORK,ID_PSP_condition,0
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END

