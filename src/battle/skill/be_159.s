//============================================================================
/**
 *
 *@file		be_159.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			159�@�Q�`�T�^�[�����������A���̊Ԃ͒N�����邱�Ƃ��ł��Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_159:
	//�U���p�����́A�ǉ����ʂ����Ȃ�
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_SAWAGU,BE_159_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SAWAGU|ADD_STATUS_WAZAKOUKA
BE_159_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
