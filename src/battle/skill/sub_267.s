
//============================================================================
/**
 *
 *@file		sub_267.s
 *@brief	�퓬�V�[�P���X
 *			HP�񕜃A�C�e�����g�p�����V�[�P���X�i�ΐ�g���[�i�[�j
 *@author	HisashiSogabe
 *@data		2006.06.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_267:
	WAIT			MSG_WAIT/2
	SE_PLAY			SIDE_ATTACK,BSE_KAIHUKU
	MESSAGE			TrainerItemUseMsg,TAG_TRTYPE_TRNAME_ITEM,SIDE_ATTACK,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_RECOVER	SIDE_ATTACK
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_wkw_item_hp_recover,0,SUB_267_END
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_wkw_item_hp_recover,BUF_PARA_HP_CALC_WORK
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_item_hp_recover,0
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP�v�Z�T�u���[�`����
	GOSUB			SUB_SEQ_HP_CALC
SUB_267_END:
	SEQ_END
