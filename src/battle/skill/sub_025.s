
//============================================================================
/**
 *
 *@file		sub_025.s
 *@brief	�퓬�V�[�P���X
 *			�₯�ǂ̒ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_025:
	//�����A�C�e���ł̒ǉ��̎��͐�p�̃`�F�b�N������
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_SOUBIITEM,NormalCheck
SoubiItemCheck:
	//�����݂��̃x�[���������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_MIZUNOBEERU,SEQ_025_END
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK	SoubiItemCheckNext
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF				IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SoubiItemCheckNext
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,SEQ_025_END
SoubiItemCheckNext:
	//�������Ղ�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
//	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RINPUN,SEQ_025_END
//���łɂ₯�ǂ𕉂��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_YAKEDO,SEQ_025_END
//�ق̂��^�C�v�ɂ͌��ʂ��Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,FIRE_TYPE,SEQ_025_END
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,FIRE_TYPE,SEQ_025_END
//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,SEQ_025_END
//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,SEQ_025_END
	BRANCH			NoWazaEffect
NormalCheck:
	//�����݂��̃x�[���������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_MIZUNOBEERU,TokuseiNoYakedo
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK	SUB_025_NEXT
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF							IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SUB_025_NEXT
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoYakedo
SUB_025_NEXT:
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
//���łɂ₯�ǂ𕉂��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_YAKEDO,AlreadyYakedo

//�ق̂��^�C�v�ɂ͌��ʂ��Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,FIRE_TYPE,Koukanai
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,FIRE_TYPE,Koukanai

//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran

//�����ǉ��̏ꍇ�A�ȉ��̃`�F�b�N�͕K�v�Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,NoWazaEffect

//�킴���͂���Ă���Ƃ��́A���܂����܂��ɂ���
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiNoYakedo

//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�ŋZ�G�t�F�N�g���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
NoWazaEffect:
//�����A�C�e�����ʂ̎��́A�A�C�e�������G�t�F�N�g���o��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_SOUBIITEM,NoItemEffect
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_ITEM_POKE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
NoItemEffect:
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_YAKEDO
	SERVER_WAIT
	//�₯�ǃt���O�𗧂Ă�
	PSP_VALUE		VAL_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_YAKEDO
//�����ǉ��̏ꍇ�A��p���b�Z�[�W��
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiYakedoMsg
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_SOUBIITEM,ItemYakedoMsg
NormalMsg:
	MESSAGE			YakedoMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			MsgAfter
TokuseiYakedoMsg:
	MESSAGE			TokuseiYakedoM2MMsg,TAG_NICK_TOKU_NICK,SIDE_WORK,SIDE_CLIENT_WORK,SIDE_TSUIKA
	BRANCH			MsgAfter
ItemYakedoMsg:
	MESSAGE			ItemYakedoMineMsg,TAG_NICK_ITEM,SIDE_TSUIKA,SIDE_WORK
MsgAfter:
	SERVER_WAIT
	STATUS_SET		SIDE_TSUIKA,STATUS_YAKEDO
	WAIT			MSG_WAIT
	//�����V���N���̂��߂ɒǉ����ʂ��������t���O�𗧂Ă�
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA,FlagOff
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA
	BRANCH			SEQ_025_END
FlagOff:
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA
SEQ_025_END:
	SEQ_END

//���܂����܂�Ȃ��Ƃ�
Umakukimaran:
//�Ԑڒǉ��A�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_025_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_025_RET
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_025_RET

//���łɂ₯�ǂ𕉂��Ă���Ƃ�
AlreadyYakedo:
//�Ԑڒǉ��A�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_025_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_025_RET
	WAIT			MSG_WAIT
	MESSAGE			AlreadyYakedoMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_025_END

//���������Ȃ��Ƃ�
Koukanai:
//�Ԑڒǉ��A�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_025_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_025_RET
	WAIT			MSG_WAIT
//�����ǉ��̏ꍇ�A��p���b�Z�[�W�ցi���̎d�l�͂Ȃ��Ȃ�܂����j
//	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiKoukanai
	MESSAGE			KoukanaiMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_025_END
//TokuseiKoukanai:
//	MESSAGE			TokuseiNoTypeM2MMsg,TAG_NICK_TOKU_NICK,SIDE_WORK,SIDE_CLIENT_WORK,SIDE_TSUIKA
//	BRANCH			SUB_025_END

//�����ł₯�ǂ�h��
TokuseiNoYakedo:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_025_RET
//�����ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
//	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiNoYakedo2
//�����ǉ��̏ꍇ�A��p���b�Z�[�W��
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_025_RET
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			MizunobeeruMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_025_END
TokuseiNoYakedo2:
	MESSAGE			TokuseiNoTokuseiM2MMsg,TAG_NICK_TOKU_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA,SIDE_WORK,SIDE_CLIENT_WORK
	BRANCH			SUB_025_END


//����҂̂܂���Ŗh���ꂽ�Ƃ�
ShinpiNoYakedo:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_025_RET
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_025_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
//	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_025_RET:
	SEQ_END

