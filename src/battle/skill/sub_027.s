
//============================================================================
/**
 *
 *@file		sub_027.s
 *@brief	�퓬�V�[�P���X
 *			������̒ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_027:
	//�����}�O�}�̂�낢�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_MAGUMANOYOROI,TokuseiNoKoori
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK				SUB_027_NEXT
	//�V�󂪂͂�̎��́A������Ȃ�
	IF							IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,Umakukimaran
SUB_027_NEXT:
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

//���łɂ������Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_KOORI,AlreadyKoori

//������^�C�v�ɂ͌��ʂ��Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,KOORI_TYPE,Koukanai
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,KOORI_TYPE,Koukanai

//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran

//�킴���͂���Ă���Ƃ��́A���܂����܂��ɂ���
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiNoKoori

//���ڒǉ��̏ꍇ�AWAZAOUT�V�[�P���X�ŋZ�G�t�F�N�g���o���Ȃ��̂ŁA�����ŏo��
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
NoWazaEffect:
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_KOORI
	SERVER_WAIT
	//������t���O�𗧂Ă�
	PSP_VALUE		VAL_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_KOORI
	//���ߌn�t���O�𗎂Ƃ�
	KEEP_OFF		SIDE_TSUIKA
	MESSAGE			KooriMineMsg,TAG_NICK,SIDE_TSUIKA
	SERVER_WAIT
	STATUS_SET		SIDE_TSUIKA,STATUS_KOORI
	WAIT			MSG_WAIT
	SEQ_END

//���܂����܂�Ȃ��Ƃ�
Umakukimaran:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_027_RET

//���łɂ������Ă���Ƃ�
AlreadyKoori:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	//���󃁃b�Z�[�W���Ȃ�
//	MESSAGE			AlreadyKooriMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_027_END

//���������Ȃ��Ƃ�
Koukanai:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	MESSAGE			KoukanaiMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_027_END

//�����ł������h��
TokuseiNoKoori:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//���󃁃b�Z�[�W���Ȃ�
//	MESSAGE			MagumanoyoroiMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_027_END


//����҂̂܂���Ŗh���ꂽ�Ƃ�
ShinpiNoKoori:
//�Ԑڒǉ��̏ꍇ�A���b�Z�[�W���o���Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_027_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_027_RET:
	SEQ_END

