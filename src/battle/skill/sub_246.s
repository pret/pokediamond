
//============================================================================
/**
 *
 *@file		sub_246.s
 *@brief	�퓬�V�[�P���X
 *			�Z�̔����V�[�P���X�i�^�����_���[�W��1/2�j
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_246:
	//�������������܂́A�͂˂�������󂯂Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_ISIATAMA,SUB_246_END
	//�����}�W�b�N�K�[�h�́A�͂˂�������󂯂Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_MAZIKKUGAADO,SUB_246_END
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//�l���Q���̂P��
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_HIT_DAMAGE
	//���łɃ_���[�W�ʂ�0�Ȃ�A�v�Z���Ȃ���0�̂܂܂ɂ���
	IF				IF_FLAG_EQ,BUF_PARA_HP_CALC_WORK,0,SUB_246_NEXT
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
SUB_246_NEXT:
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			HanekaeriMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_246_END:
	SEQ_END
