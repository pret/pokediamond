//============================================================================
/**
 *
 *@file		be_113.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			113�@�G�̉�𗦂��A���ɖ߂��B�S�[�X�g�^�C�v�̃|�P�����Ƀm�[�}���^�C�v�A�����Ƃ��^�C�v�̍U����������悤�ɂȂ�B
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_113:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MIYABURU|ADD_STATUS_WAZAKOUKA
	//�^�C�v�𖳑����ɂ���
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE
	SEQ_END
