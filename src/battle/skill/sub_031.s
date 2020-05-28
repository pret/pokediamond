
//============================================================================
/**
 *
 *@file		sub_031.s
 *@brief	�퓬�V�[�P���X
 *			�܂Ђ̒ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_031:
	//�������イ�Ȃ�������Ă���Ƃ��́A���s����i������Ԃ���`�F�b�N����̂ōŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_ZYUUNAN,TokuseiNoMahi
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK				SUB_031_NEXT
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF							IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SUB_031_NEXT
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoMahi
SUB_031_NEXT:
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
//���łɂ܂Ђ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_MAHI,AlreadyMahi

//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran

//�����ǉ��̏ꍇ�A�ȉ��̃`�F�b�N�͕K�v�Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,NoWazaEffect

//�킴���͂���Ă���Ƃ��́A���܂����܂��ɂ���
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiNoMahi

//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�ŋZ�G�t�F�N�g���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
NoWazaEffect:
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_MAHI
	SERVER_WAIT
	//�܂Ѓt���O�𗧂Ă�
	PSP_VALUE		VAL_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_MAHI
//�����ǉ��̏ꍇ�A��p���b�Z�[�W��
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiMahiMsg
NormalMsg:
	MESSAGE			MahiMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			MsgAfter
TokuseiMahiMsg:
	MESSAGE			TokuseiMahiM2MMsg,TAG_NICK_TOKU_NICK,SIDE_WORK,SIDE_CLIENT_WORK,SIDE_TSUIKA
MsgAfter:
	SERVER_WAIT
	STATUS_SET		SIDE_TSUIKA,STATUS_MAHI
	WAIT			MSG_WAIT
	//�����V���N���̂��߂ɒǉ����ʂ��������t���O�𗧂Ă�
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA,FlagOff
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA
	SEQ_END
FlagOff:
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA
	SEQ_END

//���܂����܂�Ȃ��Ƃ�
Umakukimaran:
//�Ԑڒǉ��A�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_031_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_031_RET
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_031_RET

//���łɂ܂Ђ��Ă���Ƃ�
AlreadyMahi:
//�Ԑڒǉ��A�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_031_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_031_RET
	WAIT			MSG_WAIT
	MESSAGE			AlreadyMahiMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_031_END

//���������Ȃ��Ƃ�
Koukanai:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_031_RET
	WAIT			MSG_WAIT
	MESSAGE			KoukanaiMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_031_END

//�����ł܂Ђ�h��
TokuseiNoMahi:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_031_RET
//�����ǉ��̏ꍇ�A��p���b�Z�[�W��
//	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiNoMahi2
//�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_031_RET
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			JuunanMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_031_END

TokuseiNoMahi2:
	MESSAGE			TokuseiNoTokuseiM2MMsg,TAG_NICK_TOKU_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA,SIDE_WORK,SIDE_CLIENT_WORK
	BRANCH			SUB_031_END

//����҂̂܂���Ŗh���ꂽ�Ƃ�
ShinpiNoMahi:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_031_RET
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_031_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_031_RET:
	SEQ_END

