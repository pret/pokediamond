//============================================================================
/**
 *
 *@file		be_146.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			146 �ǉ����ʂő��肪�Ђ�ށ{������Ƃԏ�Ԃ̑����2�{�_���[�W
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_146:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
	//������ƂԂ����Ă��鑊��ɂ�2�{�_���[�W��^����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SORAWOTOBU_HIT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU,BE_146_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_146_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
