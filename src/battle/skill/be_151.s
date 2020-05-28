//============================================================================
/**
 *
 *@file		be_151.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			151�@�P�^�[�����߂ĂQ�^�[���߂ōU������{�V�C���u�͂�v��Ԃ̎��͗��߂Ȃ��ōU�����o����B
 *				�u���߁v�̏ꍇ�͈З͂������B 
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_151:
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK	SeqWazaBefore
	//�V�󂪐����Ԃ̎��́A���߂����邱�ƂȂ��Z�𔭓�
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SeqWazaAfter
SeqWazaBefore:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//�������ʂŗ��߂Ȃ��Ă������ʂ������Ă���Ƃ��́A�Z�𔭓�
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_151_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_151_NEXT:
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//�U���Ώۂ����Ȃ����́A�Ȃɂ����Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_151_END
SeqWazaAfter:
	CRITICAL_CHECK
	DAMAGE_CALC
BE_151_END:
	//���ߌ�̏������܂Ƃ߂��T�u���[�`�����R�[��
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
