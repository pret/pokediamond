
//============================================================================
/**
 *
 *@file		sub_235.s
 *@brief	�퓬�V�[�P���X
 *			���Ȃ��炵���I���������b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_235:
	VALUE		VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SUNAARASHI
	MESSAGE		SunaarashiEndMsg,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
