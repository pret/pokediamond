
//============================================================================
/**
 *
 *@file		sub_061.s
 *@brief	�퓬�V�[�P���X
 *			�Z���O�ꂽ���̃y�i���e�B����
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_061:
	//�����}�W�b�N�K�[�h�́A�_���[�W���󂯂Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_MAZIKKUGAADO,SUB_061_END
	IF				IF_FLAG_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NOHIT_PENALTY,SUB_061_END
	MESSAGE			TobigeriMissMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//�_���[�W�𔼕���
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_DAMAGE
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//�����HPMAX���Q�b�g
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_hpmax,BUF_PARA_TEMP_WORK
	VALUE			VAL_MUL,BUF_PARA_TEMP_WORK,-1
	//HPMAX�𔼕���
	DAMAGE_DIV		BUF_PARA_TEMP_WORK,2
	//�����A�_���[�W�ʂ������HPMAX��1/2���傫���ꍇ�́AHPMAX��1/2�ɕ␳
	IF_WORK			IF_FLAG_NC,BUF_PARA_TEMP_WORK,BUF_PARA_HP_CALC_WORK,SUB_061_NEXT
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_TEMP_WORK
SUB_061_NEXT:
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP�v�Z�T�u���[�`����
	GOSUB			SUB_SEQ_HP_CALC
SUB_061_END:
	SEQ_END
