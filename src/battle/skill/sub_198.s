
//============================================================================
/**
 *
 *@file		sub_198.s
 *@brief	�퓬�V�[�P���X
 *			HP�񕜑����A�C�e�����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_198:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			ItemHPKaifukuMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END

