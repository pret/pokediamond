//============================================================================
/**
 *
 *@file		be_027.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			027�@�Q�`�R�^�[���A���ōU������i�U�����͑���s�\�j�A���ʂ��؂��Ǝ������u������v��ԂɂȂ��Ă��܂�
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_027:
	//�U���p�����́A�ǉ����ʂ����Ȃ�
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_ABARERU,BE_027_NEXT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_ABARERU|ADD_STATUS_WAZAKOUKA
BE_027_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
