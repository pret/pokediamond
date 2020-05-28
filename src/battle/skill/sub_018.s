
//============================================================================
/**
 *
 *@file		sub_018.s
 *@brief	�퓬�V�[�P���X
 *			�˂ނ�V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.11.30
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_018:
	//�Z���ʂł̒ǉ��̎��͐�p�̃`�F�b�N������
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,NormalCheck
	//�����ӂ݂�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_HUMIN,TokuseiNoSleep
	//������邫�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_YARUKI,TokuseiNoSleep
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK	WazaKoukaCheckNext
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF				IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,WazaKoukaCheckNext
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoSleep
WazaKoukaCheckNext:
//���łɖ����Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_NEMURI,AlreadySleep
//�����ڂ�����������Ă���Ƃ��́A���킮�`�F�b�N�����Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_BOUON,WazaKoukaNoSawaguCheck
//���킪��Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,SawaguNoSleep
WazaKoukaNoSawaguCheck:
//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran
	BRANCH			NoWazaEffect
NormalCheck:
	//�����ӂ݂�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_HUMIN,TokuseiNoSleep
	//������邫�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_YARUKI,TokuseiNoSleep
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK				SUB_018_NEXT
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF							IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SUB_018_NEXT
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoSleep
SUB_018_NEXT:
	//�Ԑڒǉ��̏ꍇ�A���Ղ�`�F�b�N������
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,NoRinpun
	//�������Ղ�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RINPUN,Umakukimaran
NoRinpun:
//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�Ń��b�Z�[�W���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoAttackMsg
	ATTACK_MESSAGE
	SERVER_WAIT
NoAttackMsg:

//�����ǉ��̏ꍇ�A�݂����`�F�b�N�Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,NoMigawari
//�݂������o����Ă���Ƃ��́A���s����
	MIGAWARI_CHECK	SIDE_TSUIKA,Umakukimaran

NoMigawari:
//���łɖ����Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_NEMURI,AlreadySleep

//�����ڂ�����������Ă���Ƃ��́A���킮�`�F�b�N�����Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_BOUON,NoSawaguCheck
//���킪��Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,SawaguNoSleep
NoSawaguCheck:
//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran

//�����ǉ��̏ꍇ�A�ȉ��̃`�F�b�N�͕K�v�Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,NoWazaEffect

//�킴���͂���Ă���Ƃ��́A���܂����܂��ɂ���
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiNoSleep
//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�ŋZ�G�t�F�N�g���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT

NoWazaEffect:
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_NEMURI
	SERVER_WAIT
	//�Q�`�T�^�[���̗������擾
	RANDOM_GET		3,3
	PSP_VALUE_WORK	VAL_BIT,SIDE_TSUIKA,ID_PSP_condition,BUF_PARA_CALC_WORK
//�����ǉ��̏ꍇ�A��p���b�Z�[�W��
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiSleepMsg
NormalMsg:
	MESSAGE			SleepBeginMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			MsgAfter

TokuseiSleepMsg:
	MESSAGE			TokuseiSleepBeginM2MMsg,TAG_NICK_TOKU_NICK,SIDE_WORK,SIDE_CLIENT_WORK,SIDE_TSUIKA
MsgAfter:
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_SET		SIDE_TSUIKA,STATUS_NEMURI
	SERVER_WAIT
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_waza_kouka,WAZAKOUKA_KIE,KieOff
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_TSUIKA
	BRANCH			NextCheck
KieOff:
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_TSUIKA
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_TSUIKA_CLIENT
	GOSUB			SUB_SEQ_VANISH_OFF
NextCheck:
	SEQ_END

//�����Ŗh�����Ƃ�
TokuseiNoSleep:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
//�����ǉ��̏ꍇ�A��p���b�Z�[�W��
//	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiNoSleep2
//�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_018_RET
//�Z���ʂł̒ǉ��̎���AttackMessage���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,TokuseiNoAttackMessage
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
TokuseiNoAttackMessage:
	MESSAGE			TokuseiSleepNGMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_018_END
TokuseiNoSleep2:
	MESSAGE			TokuseiNoTokuseiM2MMsg,TAG_NICK_TOKU_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA,SIDE_WORK,SIDE_CLIENT_WORK
	BRANCH			SUB_018_END

//���܂����܂�Ȃ��Ƃ�
Umakukimaran:
//�Ԑڒǉ��A�����ǉ��A�Z���ʂł̒ǉ��̏ꍇ�́A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_018_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,SUB_018_RET
	WAIT			MSG_WAIT
	WAZA_PARAM_GET	ID_WTD_attackrange
	//�����I���Z�́A������Ȃ��������b�Z�[�W�ɂ���
	IF				IF_FLAG_EQ,BUF_PARA_CALC_WORK,RANGE_DOUBLE,Ataranakatta
	IF				IF_FLAG_EQ,BUF_PARA_CALC_WORK,RANGE_TRIPLE,Ataranakatta
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_018_RET
Ataranakatta:
	GOSUB			SUB_SEQ_ATARANAKATTA
	BRANCH			SUB_018_RET

//���łɖ����Ă���Ƃ�
AlreadySleep:
//�Ԑڒǉ��A�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_018_RET
	WAIT			MSG_WAIT
	MESSAGE			AlreadySleepMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_018_END

//���킮�Ŗ���Ȃ��Ƃ�
SawaguNoSleep:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
//�����������ł��鎞�́A��p���b�Z�[�W��
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_SAWAGU,SawaguMine
	WAIT			MSG_WAIT
	MESSAGE			NoisySleepNGMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_018_END
SawaguMine:
	WAIT			MSG_WAIT
	MESSAGE			SleepNGMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_018_END

//����҂̂܂���Ŗ���Ȃ��Ƃ�
ShinpiNoSleep:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_018_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
//	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_018_RET:
	SEQ_END

