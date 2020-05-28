//============================================================================
/**
 *
 *@file		be_263.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			263�@�P�^�[�����߂ĂQ�^�[���߂ōU������{�u������Ƃԁv��Ԃɂ���{�u�܂Ёv�̒ǉ�����
 *
 *@author	HisashiSogabe
 *@data		2006.04.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_263:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP,SeqWazaAfter
	//�������ʂŗ��߂Ȃ��Ă������ʂ������Ă���Ƃ��́A�Z�𔭓�
	SOUBI_CHECK		SOUBI_HAVE,SIDE_ATTACK,SOUBI_2TURNWAZAWO1TURN,BE_263_NEXT
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KEEP|ADD_STATUS_ATTACK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_BEFORE
	SEQ_END
BE_263_NEXT:
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka_temp,WAZAKOUKA_SORAWOTOBU
	GOSUB			SUB_SEQ_EQPITEM_2TURNWO1TURN
	//���ꂪ�K�v���͔���
	VANISH_ON_OFF	SIDE_ATTACK,SW_VANISH_ON
	//�U���Ώۂ����Ȃ����́A�Ȃɂ����Ȃ�
	IF				IF_FLAG_EQ,BUF_PARA_DEFENCE_CLIENT,NONE_CLIENT_NO,BE_263_END
SeqWazaAfter:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_MAHI|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
BE_263_END:
	//�p�������n�̂��ߋZ�̃t���O�𗎂Ƃ�
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_KIE
	//���ߌ�̏������܂Ƃ߂��T�u���[�`�����R�[��
	GOSUB			SUB_SEQ_TAME_AFTER
	SEQ_END
