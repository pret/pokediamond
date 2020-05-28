
//============================================================================
/**
 *
 *@file		sub_047.s
 *@brief	�퓬�V�[�P���X
 *			�ǂ��ǂ��̒ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_047:
	//�ǂ��т��ł̒ǉ��̎��͐�p�̃`�F�b�N������
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DOKUBISI,SoubiItemCheckStart

Dokubisi:
	//�����߂񂦂��������Ă���Ƃ��́A���s����
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_MENEKI,TokuseiNoDoku
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK	NoRinpun
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF				IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,NoRinpun
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoDoku
	BRANCH			NoRinpun

SoubiItemCheckStart:
	//�����A�C�e���ł̒ǉ��̎��͐�p�̃`�F�b�N������
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_SOUBIITEM,NomalCheck
	//�����A�C�e���ł́A�h���ꂽ�n�̃��b�Z�[�W�͕\�����Ȃ��i�b��j
SoubiItemCheck:
	//�����߂񂦂��������Ă���Ƃ��́A���s����
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_MENEKI,SEQ_047_END
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK	SoubiItemCheckNext
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF				IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SoubiItemCheckNext
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,SEQ_047_END
SoubiItemCheckNext:
	//�������Ղ�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj�Ƃ肠��������
//	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RINPUN,Umakukimaran
//���łɂǂ����󂯂Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_DOKU,SEQ_047_END
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_DOKUDOKU,SEQ_047_END
//�ǂ��^�C�v�A�͂��˃^�C�v�ɂ͌��ʂ��Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,POISON_TYPE,SEQ_047_END
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,POISON_TYPE,SEQ_047_END
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,METAL_TYPE,SEQ_047_END
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,METAL_TYPE,SEQ_047_END
//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,SEQ_047_END
//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,SEQ_047_END
	BRANCH			NoWazaEffect
NomalCheck:
	//�����߂񂦂��������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_MENEKI,TokuseiNoDoku
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK				SUB_047_NEXT
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF							IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SUB_047_NEXT
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoDoku
SUB_047_NEXT:
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

//�݂������o����Ă���Ƃ��́A���s����
	MIGAWARI_CHECK	SIDE_TSUIKA,Umakukimaran

//���łɂǂ����󂯂Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_DOKU,AlreadyDoku
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_DOKUDOKU,AlreadyDoku

//�ǂ��^�C�v�A�͂��˃^�C�v�ɂ͌��ʂ��Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,POISON_TYPE,Koukanai
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,POISON_TYPE,Koukanai
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,METAL_TYPE,Koukanai
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,METAL_TYPE,Koukanai

//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran

//�킴���͂���Ă���Ƃ��́A���܂����܂��ɂ���
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiNoDoku

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
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_DOKU
	SERVER_WAIT
	//�ǂ��ǂ��t���O�𗧂Ă�
	PSP_VALUE		VAL_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_DOKUDOKU
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_SOUBIITEM,SoubiItemDokuDokuMsg
NormalDokuDokuMsg:
	MESSAGE			DokuDokuMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			MessageNext
SoubiItemDokuDokuMsg:
	MESSAGE			ItemDokuDokuMineMsg,TAG_NICK_ITEM,SIDE_TSUIKA,SIDE_WORK
MessageNext:
	SERVER_WAIT
	STATUS_SET		SIDE_TSUIKA,STATUS_DOKU
	WAIT			MSG_WAIT
	//�����V���N���̂��߂ɒǉ����ʂ��������t���O�𗧂Ă�
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA,FlagOff
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA
	BRANCH			SEQ_047_END
FlagOff:
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SINKURO_TSUIKA
SEQ_047_END:
	SEQ_END

//�����łǂ���h��
TokuseiNoDoku:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_047_RET
//�Z���ʂł̒ǉ��̎���AttackMessage�̕K�v�Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,TokuseiNoAttackMsg
//�ǂ��т��ł̒ǉ��̎���AttackMessage�̕K�v�Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DOKUBISI,TokuseiNoAttackMsg
	ATTACK_MESSAGE
	SERVER_WAIT
TokuseiNoAttackMsg:
	WAIT			MSG_WAIT
	MESSAGE			MenekiMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_047_END

//���܂����܂�Ȃ��Ƃ�
Umakukimaran:
//�Ԑڒǉ��A�Z���ʂł̒ǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_047_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,SUB_047_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DOKUBISI,SUB_047_RET
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_047_RET

//���łɂǂ����󂯂Ă���Ƃ�
AlreadyDoku:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_047_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DOKUBISI,SUB_047_RET
	WAIT			MSG_WAIT
	MESSAGE			AlreadyDokuMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_047_END

//���������Ȃ��Ƃ�
Koukanai:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_047_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DOKUBISI,SUB_047_RET
	WAIT			MSG_WAIT
	MESSAGE			KoukanaiMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_047_END

//����҂̂܂���Ŗh���ꂽ�Ƃ�
ShinpiNoDoku:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_047_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DOKUBISI,SUB_047_RET
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_047_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_047_RET:
	SEQ_END

