//============================================================================
/**
 *
 *@file		be_041.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			041�@�G�́u�ڂ�����v��A�����́u���������v�Ɋ֌W�Ȃ��S�O�̌Œ�_���[�W��^����
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_041:
	//���M�����[�V�����Ń��g���J�b�v�̏ꍇ�́A���܂����܂��ɂ���
	IF				IF_FLAG_BIT,BUF_PARA_REGULATION_FLAG,REGULATION_FLAG_LITTLE_CUP,Umakukimaran
	//�^�C�v�␳�v�Z�𖳎�����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//�_���[�W��40��
	VALUE			VAL_SET,BUF_PARA_DAMAGE,-40
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
