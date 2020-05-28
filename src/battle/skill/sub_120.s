
//============================================================================
/**
 *
 *@file		sub_120.s
 *@brief	�퓬�V�[�P���X
 *			�͂炾�����V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_120:
	//���łɍU���͂�MAX�̎��͂��܂����܂��
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_abiritycnt_pow,12,Umakukimaran
	//HPMAX���擾���Ĕ����ɂ���
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	DAMAGE_DIV		BUF_PARA_HP_CALC_WORK,2
	//����HP��HPMAX�̔����Ȃ����͂��܂����܂��
	IF_PSP_WORK		IF_FLAG_NC,SIDE_ATTACK,ID_PSP_hp,BUF_PARA_HP_CALC_WORK,Umakukimaran

	GOSUB			SUB_SEQ_WAZA_OUT_EFF

	//�U����MAX
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_abiritycnt_pow,12
	//HP��HPMAX�̔����ʌ��炷
	VALUE			VAL_MUL,BUF_PARA_HP_CALC_WORK,-1
	//AttackClient��HP����Ώۂ�
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//�_���[�W�G�t�F�N�g�œ_�ł��Ȃ��t���O�𗧂Ă�
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP�v�Z�T�u���[�`����
	GOSUB			SUB_SEQ_HP_CALC

	STATUS_EFFECT	SIDE_ATTACK,STATUS_EFF_UP
	SERVER_WAIT
	MESSAGE			HaradaikoMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

