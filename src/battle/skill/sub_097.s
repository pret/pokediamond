
//============================================================================
/**
 *
 *@file		sub_097.s
 *@brief	�퓬�V�[�P���X
 *			�̂낢�i�S�[�X�g�j�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_097:
	//�����ŊO�ꂽ�ꍇ�́A���܂����܂��
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_KIE_NOHIT,Umakukimaran
	//�݂���肪�����ꍇ�́A���܂����܂��
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//���łɂ̂���Ă��鎞�́A���܂����܂��
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_NOROI,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_NOROI
	//������HPMAX�̔������_���[�W�ɂ���
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP����Ώۂ�AttackClient��
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			NoroiM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
