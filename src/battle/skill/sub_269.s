
//============================================================================
/**
 *
 *@file		sub_269.s
 *@brief	�퓬�V�[�P���X
 *			�\�̓A�b�v�A�C�e�����g�p�����V�[�P���X�i�ΐ�g���[�i�[�j
 *@author	HisashiSogabe
 *@data		2006.06.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_269:
	WAIT			MSG_WAIT/2
	SE_PLAY			SIDE_ATTACK,BSE_KAIHUKU
	MESSAGE			TrainerItemUseMsg,TAG_TRTYPE_TRNAME_ITEM,SIDE_ATTACK,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_RECOVER	SIDE_ATTACK
	MESSAGE			ItemCondUp1MineMsg,TAG_NICK_ITEM_STAT,SIDE_ATTACK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
