
//============================================================================
/**
 *
 *@file		sub_141.s
 *@brief	�퓬�V�[�P���X
 *			�����уV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_141:
	//�����ӂ݂�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_HUMIN,TokuseiUmakukimaran
	//������邫�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_YARUKI,TokuseiUmakukimaran
	//�V�󖳌��n�̓����́A�V��`�F�b�N�𖳎�
	NOOTENKI_CHECK				SUB_141_NEXT
	//�V�󂪂͂ꂶ��Ȃ��Ƃ��́A�������[�t�K�[�h�`�F�b�N�����Ȃ�
	IF							IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SUB_141_NEXT
	//�������[�t�K�[�h�������Ă���Ƃ��́A���s����i������Ԃ�`�F�b�N�̂��߂ɍŏ�ʁj
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiUmakukimaran
SUB_141_NEXT:

	ATTACK_MESSAGE
	SERVER_WAIT
NoAttackMsg:
//�݂������o����Ă���Ƃ��́A���s����
	MIGAWARI_CHECK	SIDE_TSUIKA,Umakukimaran
//�����ڂ�����������Ă���Ƃ��́A���킮�`�F�b�N�����Ȃ�
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_BOUON,NoSawaguCheck
//���킪��Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,Umakukimaran
NoSawaguCheck:
//���łɏ�Ԉُ�ɂȂ��Ă���ꍇ�́A���s����
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran
//����҂̂܂���Ŏ���Ă���ꍇ�́A���s����
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiUmakukimaran
//�������ŊO��Ă���ꍇ�́A���܂����܂��
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

	AKUBI			Umakukimaran

	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	MESSAGE			AkubiM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_TSUIKA
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

//�����Ŗh�����Ƃ�
TokuseiUmakukimaran:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			TokuseiUmakukimaranMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_141_END

//���܂����܂�Ȃ��Ƃ�
Umakukimaran:
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_141_RET

//����҂̂܂���Ŗh������
ShinpiUmakukimaran:
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_141_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessage�𖳌��ɂ��邽�߂ɂ��̃t���O�𗧂Ă�
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_141_RET:
	SEQ_END

