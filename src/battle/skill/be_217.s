//============================================================================
/**
 *
 *@file		be_217.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			217�@�˂ނ��Ԃ̑���ɔ{�̃_���[�W��^���邪�A�˂ނ��Ԃ�����B�y�����z�̃o�[�W�����Ⴂ�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_217:
	//�݂���肪����ꍇ�́A�˂ނ�`�F�b�N���X���[
	MIGAWARI_CHECK	SIDE_DEFENCE,BE_217_NEXT
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_NEMURI,BE_217_NEMURI
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,10
	BRANCH			BE_217_NEXT
BE_217_NEMURI:
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_NONEMURI|ADD_STATUS_WAZAKOUKA
BE_217_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
