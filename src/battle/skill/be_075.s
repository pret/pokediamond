//============================================================================
/**
 *
 *@file		be_075.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			075�@�P�^�[�����߂ĂQ�^�[���߂ōU������B�Ђ�ނ̒ǉ����ʁB�}���ɓ�����₷���B
 *
 *@author	HisashiSogabe
 *@data		2005.12.21
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_075:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//�������ʂŗ��߂Ȃ��Ă������ʂ������Ă���Ƃ��́A�Z�𔭓�
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_075_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_075_NEXT:
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//�U���Ώۂ����Ȃ����́A�Ȃɂ����Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_075_END
SeqWazaAfter:
	//�N���e�B�J���q�b�g���o���₷������
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
	//�Ђ�ޒǉ����ʂ��Z�b�g
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
BE_075_END:
	//���ߌ�̏������܂Ƃ߂��T�u���[�`�����R�[��
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
