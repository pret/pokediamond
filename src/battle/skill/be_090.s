//============================================================================
/**
 *
 *@file		be_090.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			090�@�G���Ō�Ɏg�p�����Z���A�Q�`�U��J��Ԃ��o������
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_090:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_ENCORE|ADD_STATUS_WAZAKOUKA
	SEQ_END
