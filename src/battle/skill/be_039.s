//============================================================================
/**
 *
 *@file		be_039.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			039 �P�^�[�����߂ĂQ�^�[���ڂōU������
 *
 *@author	HisashiSogabe
 *@data		2005.11.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_039:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//2�̂ɓ�����Ƃ��́AKEEP����������Ԃŉ���Ă���̂ŁA��������
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER,SeqWazaAfter
	//�������ʂŗ��߂Ȃ��Ă������ʂ������Ă���Ƃ��́A�Z�𔭓�
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_039_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_039_NEXT:
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//�U���Ώۂ����Ȃ����́A�Ȃɂ����Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_039_END
SeqWazaAfter:
	//�}���ɓ�����₷������
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
BE_039_END:
	//���ߌ�̏������܂Ƃ߂��T�u���[�`�����R�[��
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
