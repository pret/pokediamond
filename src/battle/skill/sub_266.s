
//============================================================================
/**
 *
 *@file		sub_266.s
 *@brief	�퓬�V�[�P���X
 *			����or���ꂩ��󂯂��_���[�W��Ԃ���������
 *@author	HisashiSogabe
 *@data		2006.05.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_266:
	//�������Ă��鑤���C�₵�Ă��鎞�́A�G�t�F�N�g�Ȃ��i�C�₵�Ă��Ă��������ʂ͔����j
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_hp,0,NoEffect
	STATUS_EFFECT	SIDE_DEFENCE,STATUS_ITEM_POKE
	SERVER_WAIT
NoEffect:
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP�v�Z�Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			ItemHitDamageM2MMsg,TAG_NICK_NICK_ITEM,SIDE_ATTACK,SIDE_DEFENCE,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
//	PSP_VALUE		VAL_SET,SIDE_DEFENCE,ID_PSP_item,0
	KILL_ITEM		SIDE_DEFENCE
	SEQ_END

