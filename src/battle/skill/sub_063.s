
//============================================================================
/**
 *
 *@file		sub_063.s
 *@brief	�퓬�V�[�P���X
 *			�Z�̔����V�[�P���X�i�^�����_���[�W��1/4�j
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_063:
	//�������������܂́A�͂˂�������󂯂Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_ISIATAMA,SUB_063_END
	//�����}�W�b�N�K�[�h�́A�͂˂�������󂯂Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_MAZIKKUGAADO,SUB_063_END
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//�l���S���̂P��
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_HIT_DAMAGE
	//���łɃ_���[�W�ʂ�0�Ȃ�A�v�Z���Ȃ���0�̂܂܂ɂ���
	IF				IF_FLAG_EQ,BUF_PARA_HP_CALC_WORK,0,SUB_063_NEXT
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,4
SUB_063_NEXT:
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			HanekaeriMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_063_END:
	SEQ_END
