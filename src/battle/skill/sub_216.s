
//============================================================================
/**
 *
 *@file		sub_216.s
 *@brief	�퓬�V�[�P���X
 *			����ɂ����������A�C�e�����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_216:
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_item,BUF_PARA_TEMP_WORK
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_item,BUF_PARA_TEMP_WORK
	PSP_VALUE		VAL_SET,SIDE_DEFENCE,ID_PSP_item,0
	SEQ_END

