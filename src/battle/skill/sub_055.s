
//============================================================================
/**
 *
 *@file		sub_055.s
 *@brief	�퓬�V�[�P���X
 *			�˂ނ�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_055:
	ATTACK_MESSAGE
	SERVER_WAIT
	//�����ӂ݂�������Ă���Ƃ��́A���s����
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_HUMIN,TokuseiNoSleep
	//������邫�������Ă���Ƃ��́A���s����
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_YARUKI,TokuseiNoSleep
	//���łɖ����Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI,AlreadySleep
	//�����ڂ�����������Ă���Ƃ��́A���킮�`�F�b�N�����Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_BOUON,NoSawaguCheck
	//���킪��Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,SawaguNoSleep
NoSawaguCheck:
	//HPMAX���擾
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	//HP�܂񂽂�Ȃ玸�s
	IF_PSP_WORK		IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_hp,BUF_PARA_HP_CALC_WORK,HP_Mantan
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//��Ԉُ�̎��́A��Ԉُ������
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI_OFF,StatusRecoverMessage
	MESSAGE			NemuruMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_NEXT
StatusRecoverMessage:
	STATUS_SET		SIDE_ATTACK,STATUS_NORMAL
	//�˂ނ�ȊO�̃t���O�𗎂Ƃ�
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI_OFF
	MESSAGE			NemuruRecoverMineMsg,TAG_NICK,SIDE_ATTACK
SUB_055_NEXT:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//2�^�[���˂ނ�i���݂̃^�[�����܂߂ĂR���Z�b�g�j
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_condition,3
	STATUS_SET		SIDE_ATTACK,STATUS_NEMURI
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP�v�Z�T�u���[�`����
	GOSUB			SUB_SEQ_HP_CALC
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI_OFF,StatusRecoverMessage
	MESSAGE			JikosaiseiMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_RET

TokuseiNoSleep:
	WAIT			MSG_WAIT
	MESSAGE			TokuseiSleepNGMineMsg,TAG_NICK_TOKU,SIDE_ATTACK,SIDE_ATTACK
	BRANCH			SUB_055_END
AlreadySleep:
	WAIT			MSG_WAIT
	MESSAGE			AlreadySleepMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_END
SawaguNoSleep:
//�����������ł��鎞�́A��p���b�Z�[�W��
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_SAWAGU,SawaguMine
	WAIT			MSG_WAIT
	MESSAGE			NoisySleepNGMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_END
SawaguMine:
	WAIT			MSG_WAIT
	MESSAGE			SleepNGMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_END
HP_Mantan:
	WAIT			MSG_WAIT
	MESSAGE			MantanMineMsg,TAG_NICK,SIDE_ATTACK
SUB_055_END:
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_055_RET:
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

