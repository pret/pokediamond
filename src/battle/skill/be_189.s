//============================================================================
/**
 *
 *@file		be_189.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			189�@����̂g�o�|�����̂g�o���̃_���[�W��^����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_189:
	//�����HP���擾
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_hp,BUF_PARA_DAMAGE
	//������HP���擾
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hp,BUF_PARA_CALC_WORK
	//�����HP<=������HP�Ȃ�A���܂����܂��
	IF_WORK			IF_FLAG_NC,BUF_PARA_DAMAGE,BUF_PARA_CALC_WORK,Umakukimaran

	//�_���[�W�ʌv�Z
	VALUE_WORK		VAL_SUB,BUF_PARA_DAMAGE,BUF_PARA_CALC_WORK
	VALUE			VAL_MUL,BUF_PARA_DAMAGE,-1
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
