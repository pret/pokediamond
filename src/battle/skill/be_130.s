//============================================================================
/**
 *
 *@file		be_130.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			130�@�Œ�_���[�W�Q�O
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_130:
	//���M�����[�V�����Ń��g���J�b�v�̏ꍇ�́A���܂����܂��ɂ���
	IF				IF_FLAG_BIT,BUF_PARA_REGULATION_FLAG,REGULATION_FLAG_LITTLE_CUP,Umakukimaran
	//�^�C�v�␳�v�Z�𖳎�����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//�_���[�W��20��
	VALUE			VAL_SET,BUF_PARA_DAMAGE,-20
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
