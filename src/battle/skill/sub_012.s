
//============================================================================
/**
 *
 *@file		sub_012.s
 *@brief	�퓬�V�[�P���X
 *			AbirityCount�n�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_012:
	//������Ԃ�`�F�b�N�̂��߂ɏ�Ɉړ�
	ABICNT_CALC		AbirityCountNoCalc,AbirityCountNoAct,Umakukimaran
//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�Ń��b�Z�[�W���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoAttackMsg
	ATTACK_MESSAGE
	SERVER_WAIT
NoAttackMsg:
//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�ŋZ�G�t�F�N�g���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
NoWazaEffect:
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG,NoStatusEffect
	STATUS_EFFECT_WORK	SIDE_TSUIKA,BUF_PARA_TEMP_WORK
	SERVER_WAIT
	//�G�t�F�N�g�̘A���`�F�b�N�̃t���O���Ȃ��ꍇ�́A�t���O���Ă͂Ȃ�
	IF				IF_FLAG_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK,NoStatusEffect
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG
NoStatusEffect:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
//�オ�肫���Ă���or�����肫���Ă���or�����ŕω��Ȃ���
AbirityCountNoCalc:
//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�Ń��b�Z�[�W���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,AbirityCountNoCalcNext
	ATTACK_MESSAGE
	SERVER_WAIT
AbirityCountNoCalcNext:
	//�A�T�[�g���b�Z�[�W��\���t���O�������Ă�����A��\��
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_DIRECT_MSG,AbirityCountNoAct
	WAIT			MSG_WAIT
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
//�Ԑڒǉ��ŁA���Ƀ��b�Z�[�W�\���̕K�v�Ȃ�
AbirityCountNoAct:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
