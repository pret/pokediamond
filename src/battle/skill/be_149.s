//============================================================================
/**
 *
 *@file		be_149.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			149 ���ʍU���{�u������Ƃԁv�����Ă��鑊��ɂQ�{�̃_���[�W
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_149:
	//������ƂԂ����Ă��鑊��ɂ�2�{�_���[�W��^����
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SORAWOTOBU_HIT
	VALUE		VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	IF_PSP		IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_SORAWOTOBU,BE_149_END
	VALUE		VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_149_END:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
