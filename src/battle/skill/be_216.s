//============================================================================
/**
 *
 *@file		be_216.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			216�@�Ώۂ̃|�P�����̉�𗦂����ɖ߂��B�����^�C�v�̃|�P�����ɁA�G�X�p�[�^�C�v�̍U����������悤�ɂȂ�B
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_216:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MIRACLE_EYE|ADD_STATUS_WAZAKOUKA
	//�^�C�v�𖳑����ɂ���
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	SEQ_END
