//============================================================================
/**
 *
 *@file		be_032.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			032�@�g�o���ő�l�̔����̒l�����񕜂���
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_032:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_JIKOSAISEI|ADD_STATUS_WAZAKOUKA
	SEQ_END
