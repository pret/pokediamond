
//============================================================================
/**
 *
 *@file		sub_211.s
 *@brief	�퓬�V�[�P���X
 *			�\�͉񕜑����A�C�e�����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_211:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemAbiKaifukuMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END
