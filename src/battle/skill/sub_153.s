
//============================================================================
/**
 *
 *@file		sub_153.s
 *@brief	�퓬�V�[�P���X
 *			���������`�F�b�N�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_153:
	GOSUB			SUB_SEQ_AD_PUSH
SUB_153_LOOP:
	OIUCHI_CHECK	SUB_153_END
	//�������������́A�_���[�W���Q�{�ɂ���
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
	CRITICAL_CHECK
	DAMAGE_CALC
	TYPE_CHECK
	//AttackMsg���o��悤�Ƀt���O�𗎂Ƃ�
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_ATTACK_MSG
	//WazaEffect���o��悤�Ƀt���O�𗎂Ƃ�
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	ATTACK_MESSAGE
	SERVER_WAIT
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_HAZURE,OiuchiHazure
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	MIGAWARI_CHECK	SIDE_DEFENCE,Migawari

Normal:
	VALUE_WORK		VAL_SET,BUF_PARA_HP_CALC_WORK,BUF_PARA_DAMAGE
	VALUE_WORK		VAL_SET,BUF_PARA_BUTSURI_OSTF_DAMAGE_D,BUF_PARA_DAMAGE
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_DEFENCE_CLIENT
	GOSUB			SUB_SEQ_HP_CALC
	GOSUB			SUB_SEQ_CRITICAL_HIT
	GOSUB			SUB_SEQ_WAZA_STATUS_MSG
	//�C�₳�����炨��˂�`�F�b�N������
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_hp,0,OnnenCheck
	//�Z���q�b�g�������Ƀ`�F�b�N����������`�F�b�N
	WAZA_HIT_TOKUSEI_CHECK	SUB_153_SOUBI_ITEM
	GOSUB_WORK		BUF_PARA_TEMP_WORK

SUB_153_SOUBI_ITEM:
	//�Z���q�b�g�������Ƀ`�F�b�N���鑕���A�C�e�����`�F�b�N
	WAZA_HIT_SOUBI_ITEM_CHECK	SUB_153_NEXT
	GOSUB_WORK		BUF_PARA_TEMP_WORK

	BRANCH			SUB_153_NEXT

Migawari:
	GOSUB			SUB_SEQ_MIGAWARI_HIT
	BRANCH			SUB_153_NEXT

OiuchiHazure:
	WAIT			MSG_WAIT/2
	GOSUB			SUB_SEQ_WAZA_NO_HIT

SUB_153_NEXT:
	//�������������������AttackClient�ADefenceClient�Awaza_no_now���ς���Ă���̂ŁA���ɖ߂�
	GOSUB			SUB_SEQ_AD_POP
	VALUE_WORK		VAL_GET,BUF_PARA_WAZA_NO_TEMP,BUF_PARA_WAZA_NO_NOW
	BRANCH			SUB_153_LOOP

//����˂�`�F�b�N
OnnenCheck:
//	ONNEN			TokuseiCheck
//	MESSAGE			OnnenDamageMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_WORK
//	SERVER_WAIT
//	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_MICHIDURE_KIZETSU

TokuseiCheck:
	//�Z���q�b�g�������Ƀ`�F�b�N����������`�F�b�N�i���������ŋC�₪���肤��̂ŁA����˂�`�F�b�N�̂��Ƃɂ���j
	WAZA_HIT_TOKUSEI_CHECK	SoubiItemCheck
	GOSUB_WORK		BUF_PARA_TEMP_WORK

SoubiItemCheck:
	//�Z���q�b�g�������Ƀ`�F�b�N���鑕���A�C�e�����`�F�b�N
	WAZA_HIT_SOUBI_ITEM_CHECK	SUB_153_POP
	GOSUB_WORK		BUF_PARA_TEMP_WORK

SUB_153_POP:
	//�������������������AttackClient�ADefenceClient�Awaza_no_now���ς���Ă���̂ŁA���ɖ߂�
	GOSUB			SUB_SEQ_AD_POP
	VALUE_WORK		VAL_GET,BUF_PARA_WAZA_NO_TEMP,BUF_PARA_WAZA_NO_NOW

SUB_153_END:
	SEQ_END


