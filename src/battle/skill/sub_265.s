
//============================================================================
/**
 *
 *@file		sub_265.s
 *@brief	�퓬�V�[�P���X
 *			��x�����������������鑕������
 *@author	HisashiSogabe
 *@data		2006.05.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_265:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemHitUpMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_SET,SIDE_WORK,ID_PSP_wkw_once_hit_up,1
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END
