//============================================================================
/**
 *
 *@file		be_273.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			273�@�₯�ǂ̒ǉ����ʁ{���܂���B�Ԑڒǉ����ʊm�����݂āA���ꂼ��`�F�b�N����B
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_273:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_YAKEDO_HIRUMU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
