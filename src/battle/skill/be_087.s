//============================================================================
/**
 *
 *@file		be_087.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			087�@�G�́u�ڂ�����v��A�����́u���������v�Ɋ֌W�Ȃ����x���Ɠ������l�̌Œ�_���[�W��^����
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_087:
	//�^�C�v�␳�v�Z�𖳎�����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//�_���[�W�������̃��x����
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_level,BUF_PARA_DAMAGE
	VALUE			VAL_MUL,BUF_PARA_DAMAGE,-1
	SEQ_END
