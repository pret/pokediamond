
//============================================================================
/**
 *
 *@file		sub_215.s
 *@brief	�퓬�V�[�P���X
 *			�_���[�W�����A�C�e�����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_215:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			ItemDamageMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

