
//============================================================================
/**
 *
 *@file		sub_229.s
 *@brief	�퓬�V�[�P���X
 *			�T�t�@���]�[���ŗl�q������V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.04.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_229:
	MESSAGE_NO_DIR		SafariZoneYousumiMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT				MSG_WAIT
	SEQ_END
